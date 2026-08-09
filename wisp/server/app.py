"""
wisp.server.app — OpenAI-compatible HTTP API in front of WispEngine.

    wisp serve ./models/glm-5.2/ --port 8080

Anything that speaks the OpenAI API then speaks to WISP: Cursor,
Continue.dev, Open WebUI, the `openai` Python package, and so on.

    from openai import OpenAI
    client = OpenAI(base_url="http://localhost:8080/v1", api_key="wisp")

Endpoints
    GET  /health          liveness
    GET  /v1/models       OpenAI model listing
    POST /v1/chat/completions   streaming and non-streaming
    GET  /v1/stats        WISP-specific: tok/s, tier hits, learning cache

DESIGN NOTES
* FastAPI/uvicorn/pydantic are optional. This module imports cleanly
  without them so `import wisp.server.app` never explodes; the CLI turns
  a missing dependency into an install hint instead of a traceback.
* Streaming is genuinely incremental. The engine's generator runs on a
  worker thread and pushes into a queue that the event loop drains, so
  the first token reaches the client as soon as it exists. Collecting
  the whole completion and *then* yielding it would satisfy the schema
  while defeating the entire point — at WISP's token rates a user would
  stare at nothing for a minute and get one burst.
* One engine, one request at a time. WispEngine holds a single KV cache
  and a shared expert cache; concurrent decoding would interleave two
  conversations into the same state. A lock serializes requests, which
  is honest for a single-GPU local server.
"""

from __future__ import annotations

import asyncio
import json
import queue
import threading
import time
import uuid
from pathlib import Path
from typing import AsyncIterator, Optional

try:
    from fastapi import FastAPI, HTTPException
    from fastapi.middleware.cors import CORSMiddleware
    from fastapi.responses import StreamingResponse
    from pydantic import BaseModel, Field
    HAS_FASTAPI = True
except ImportError:                                   # optional extra
    HAS_FASTAPI = False

    class BaseModel:                                  # type: ignore
        """Placeholder so the module still imports and the request
        schema below stays readable when FastAPI is absent."""

    def Field(default=None, **_kwargs):               # type: ignore
        return default


INSTALL_HINT = (
    "The WISP API server needs FastAPI and uvicorn:\n"
    "    pip install fastapi uvicorn\n"
    "or install the extra:\n"
    "    pip install 'wisp-engine[server]'"
)


# --------------------------------------------------------------------------
# OpenAI-compatible schema
# --------------------------------------------------------------------------

class ChatMessage(BaseModel):
    role: str
    content: str


class ChatCompletionRequest(BaseModel):
    model: str
    messages: list
    max_tokens: Optional[int] = 512
    temperature: Optional[float] = 0.7
    top_p: Optional[float] = 0.9
    top_k: Optional[int] = 0
    stream: Optional[bool] = False
    stop: Optional[list] = None
    repetition_penalty: Optional[float] = 1.0
    # Accepted for client compatibility; WISP's sampler does not
    # implement them, and silently ignoring is better than 422-ing a
    # request that Cursor or Open WebUI sends by default.
    presence_penalty: Optional[float] = 0.0
    frequency_penalty: Optional[float] = 0.0
    n: Optional[int] = 1
    user: Optional[str] = None


# --------------------------------------------------------------------------
# Prompt templating
# --------------------------------------------------------------------------

def format_messages(messages, model_name: str) -> str:
    """
    Render chat messages into the prompt format the model was tuned on.

    Note none of these emit a literal BOS token: the adapter's
    tokenize() prepends one, and a second would shift every position.
    """
    name = (model_name or "").lower()

    def get(m, attr):
        return getattr(m, attr, None) if not isinstance(m, dict) \
            else m.get(attr)

    parts: list[str] = []
    if "glm" in name:
        for m in messages:
            role, content = get(m, "role"), get(m, "content")
            parts.append(f"[{str(role).upper()}]\n{content}")
        parts.append("[ASSISTANT]")
        return "\n".join(parts)

    if "deepseek" in name:
        tag = {"system": "<｜System｜>", "user": "<｜User｜>",
               "assistant": "<｜Assistant｜>"}
        for m in messages:
            role, content = get(m, "role"), get(m, "content")
            parts.append(f"{tag.get(role, '')}{content}")
        parts.append("<｜Assistant｜>")
        return "".join(parts)

    if "mixtral" in name or "mistral" in name:
        # Mistral instruct: system text is folded into the first [INST].
        system = " ".join(str(get(m, "content")) for m in messages
                          if get(m, "role") == "system")
        for m in messages:
            role, content = get(m, "role"), get(m, "content")
            if role == "user":
                body = f"{system}\n\n{content}" if system else content
                system = ""
                parts.append(f"[INST] {body} [/INST]")
            elif role == "assistant":
                parts.append(f" {content}</s>")
        return "".join(parts)

    for m in messages:
        parts.append(f"{get(m, 'role')}: {get(m, 'content')}")
    parts.append("assistant:")
    return "\n".join(parts)


# --------------------------------------------------------------------------
# Server
# --------------------------------------------------------------------------

class WispServer:
    """OpenAI-compatible API server wrapping a single WispEngine."""

    def __init__(self, model_dir: str, host: str = "127.0.0.1",
                 port: int = 8080, engine=None):
        if not HAS_FASTAPI:
            raise ImportError(INSTALL_HINT)
        self.model_dir = Path(model_dir)
        self.host = host
        self.port = port
        self.engine = engine
        self.model_name = self.model_dir.name
        self._gen_lock = threading.Lock()
        self.app = self._build_app()

    # ------------------------------------------------------------------ #
    def _load_engine(self):
        if self.engine is not None:
            return
        from ..runtime.engine import WispEngine
        print(f"  Loading {self.model_name}...")
        self.engine = WispEngine(str(self.model_dir))
        print(f"  Ready — http://{self.host}:{self.port}/v1")

    def _require_engine(self):
        if self.engine is None:
            raise HTTPException(503, "Model is still loading")
        return self.engine

    def _count_tokens(self, text: str) -> int:
        """Real token count via the model's tokenizer, not word count —
        clients bill and budget against these numbers."""
        try:
            return len(self.engine.adapter.tokenize(text))
        except Exception:
            return max(1, len(text) // 4)

    # ------------------------------------------------------------------ #
    def _build_app(self):
        from contextlib import asynccontextmanager

        @asynccontextmanager
        async def lifespan(_app):
            self._load_engine()
            yield
            if self.engine is not None:
                # Persists the learning cache for the next run.
                self.engine.shutdown()

        app = FastAPI(title="WISP API",
                      description="OpenAI-compatible API for WISP",
                      version="1.0.0",
                      lifespan=lifespan)
        app.add_middleware(CORSMiddleware, allow_origins=["*"],
                           allow_methods=["*"], allow_headers=["*"])

        @app.get("/health")
        async def health():
            return {"status": "ok", "model": self.model_name,
                    "engine_loaded": self.engine is not None}

        @app.get("/v1/models")
        async def list_models():
            return {
                "object": "list",
                "data": [{
                    "id": self.model_name,
                    "object": "model",
                    "created": int(time.time()),
                    "owned_by": "wisp",
                    "permission": [],
                    "root": self.model_name,
                    "parent": None,
                }],
            }

        @app.get("/v1/stats")
        async def stats():
            eng = self._require_engine()
            out = {
                "tok_per_sec": eng.tok_per_sec(),
                "cache_hits": eng.cache_stats(),
                "vram_used_gb": eng.vram_used_bytes() / 1e9,
                "ram_used_gb": eng.ram_used_bytes() / 1e9,
            }
            lc = getattr(eng, "learning_cache", None)
            if lc is not None:
                s = dict(lc.get_stats())
                top = s.pop("top_expert", None)
                if top is not None:
                    s["top_expert"] = {
                        "layer_id": top.layer_id,
                        "expert_id": top.expert_id,
                        "hit_count": top.hit_count,
                    }
                out["learning_cache"] = s
                out["prewarmed_experts"] = getattr(
                    eng, "prewarmed_experts", 0)
            return out

        @app.post("/v1/chat/completions")
        async def chat_completions(request: ChatCompletionRequest):
            eng = self._require_engine()
            prompt = format_messages(request.messages, self.model_name)
            if request.stream:
                return StreamingResponse(
                    self._stream_sse(prompt, request),
                    media_type="text/event-stream",
                    headers={"Cache-Control": "no-cache",
                             "Connection": "keep-alive",
                             "X-Accel-Buffering": "no"})
            return await self._complete(prompt, request)

        return app

    # ------------------------------------------------------------------ #
    def _gen_kwargs(self, request) -> dict:
        return {
            "max_new_tokens": request.max_tokens or 512,
            "temperature": (request.temperature
                            if request.temperature is not None else 0.7),
            "top_p": request.top_p if request.top_p is not None else 1.0,
            "top_k": request.top_k or 0,
            "repetition_penalty": request.repetition_penalty or 1.0,
            "stop_sequences": list(request.stop) if request.stop else None,
        }

    async def _iter_tokens(self, prompt: str,
                           request) -> AsyncIterator[str]:
        """
        Bridge the engine's blocking generator to async, one piece at a
        time. A worker thread pushes into a queue; the event loop pulls
        from it, so tokens reach the client while generation continues.
        """
        q: "queue.Queue[object]" = queue.Queue(maxsize=64)
        SENTINEL = object()
        kwargs = self._gen_kwargs(request)

        def _worker():
            try:
                with self._gen_lock:
                    for piece in self.engine.stream(prompt, **kwargs):
                        q.put(piece)
            except Exception as exc:                  # surfaced below
                q.put(exc)
            finally:
                q.put(SENTINEL)

        thread = threading.Thread(target=_worker, daemon=True)
        thread.start()
        loop = asyncio.get_event_loop()
        while True:
            item = await loop.run_in_executor(None, q.get)
            if item is SENTINEL:
                break
            if isinstance(item, Exception):
                raise item
            yield item

    async def _stream_sse(self, prompt: str,
                          request) -> AsyncIterator[str]:
        """Server-sent events in OpenAI's chunk format."""
        cid = f"chatcmpl-{uuid.uuid4().hex[:24]}"
        created = int(time.time())

        def chunk(delta: dict, finish=None) -> str:
            payload = {
                "id": cid,
                "object": "chat.completion.chunk",
                "created": created,
                "model": request.model,
                "choices": [{"index": 0, "delta": delta,
                             "finish_reason": finish}],
            }
            return f"data: {json.dumps(payload)}\n\n"

        yield chunk({"role": "assistant", "content": ""})
        try:
            async for piece in self._iter_tokens(prompt, request):
                yield chunk({"content": piece})
        except Exception as exc:
            # The response has already begun, so the status code is
            # committed; report inside the stream rather than dying mute.
            yield (f"data: {json.dumps({'error': {'message': str(exc), 'type': exc.__class__.__name__}})}\n\n")
            yield "data: [DONE]\n\n"
            return
        yield chunk({}, finish="stop")
        yield "data: [DONE]\n\n"

    async def _complete(self, prompt: str, request):
        """Non-streaming completion."""
        kwargs = self._gen_kwargs(request)
        loop = asyncio.get_event_loop()

        def _run():
            with self._gen_lock:
                return self.engine.generate(prompt, **kwargs)

        text = await loop.run_in_executor(None, _run)
        prompt_tokens = self._count_tokens(prompt)
        completion_tokens = self._count_tokens(text)
        return {
            "id": f"chatcmpl-{uuid.uuid4().hex[:24]}",
            "object": "chat.completion",
            "created": int(time.time()),
            "model": request.model,
            "choices": [{
                "index": 0,
                "message": {"role": "assistant", "content": text},
                "finish_reason": "stop",
            }],
            "usage": {
                "prompt_tokens": prompt_tokens,
                "completion_tokens": completion_tokens,
                "total_tokens": prompt_tokens + completion_tokens,
            },
        }

    # ------------------------------------------------------------------ #
    def run(self):
        import uvicorn
        uvicorn.run(self.app, host=self.host, port=self.port,
                    log_level="info")
