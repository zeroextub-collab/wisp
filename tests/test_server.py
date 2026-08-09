"""
Tests for the OpenAI-compatible API server.

The bar is not "returns 200" — it is that a real OpenAI client would
accept the payloads, that streaming actually streams rather than
buffering the whole completion, and that prompts get the chat template
the model was trained on.
"""

import json
from unittest.mock import MagicMock

import pytest

from wisp.server.app import HAS_FASTAPI, format_messages

if HAS_FASTAPI:
    from fastapi.testclient import TestClient
    from wisp.server.app import WispServer

pytestmark = pytest.mark.skipif(
    not HAS_FASTAPI, reason="fastapi/uvicorn not installed")


# --------------------------------------------------------------------------
# Prompt templating — pure, testable without an engine
# --------------------------------------------------------------------------

def test_format_messages_mixtral():
    msgs = [{"role": "user", "content": "Hello"}]
    prompt = format_messages(msgs, "mixtral-8x7b")
    assert "[INST]" in prompt and "[/INST]" in prompt
    # The tokenizer adds BOS; a literal one here would double it.
    assert "<s>" not in prompt


def test_format_messages_mixtral_folds_system_into_first_turn():
    msgs = [{"role": "system", "content": "Be terse."},
            {"role": "user", "content": "Hi"}]
    prompt = format_messages(msgs, "mixtral-8x7b")
    assert prompt.count("[INST]") == 1
    assert "Be terse." in prompt


def test_format_messages_glm():
    msgs = [{"role": "system", "content": "S"},
            {"role": "user", "content": "U"}]
    prompt = format_messages(msgs, "glm-5.2")
    assert "[SYSTEM]" in prompt and "[USER]" in prompt
    assert prompt.rstrip().endswith("[ASSISTANT]")


def test_format_messages_deepseek():
    prompt = format_messages([{"role": "user", "content": "U"}],
                             "deepseek-v3")
    assert "｜User｜" in prompt
    assert prompt.endswith("<｜Assistant｜>")


def test_format_messages_accepts_objects_and_dicts():
    obj = MagicMock(role="user", content="Hey")
    assert "Hey" in format_messages([obj], "mixtral-8x7b")
    assert "Hey" in format_messages([{"role": "user", "content": "Hey"}],
                                    "mixtral-8x7b")


# --------------------------------------------------------------------------
# HTTP surface
# --------------------------------------------------------------------------

@pytest.fixture()
def mock_engine():
    eng = MagicMock()
    eng.generate.return_value = "def sieve(n): pass"
    eng.stream.return_value = iter(["def ", "sieve", "(n):", " pass"])
    eng.tok_per_sec.return_value = 4.2
    eng.vram_used_bytes.return_value = 9_500_000_000
    eng.ram_used_bytes.return_value = 12_000_000_000
    eng.cache_stats.return_value = {"vram_hits": 100, "ram_hits": 50,
                                    "ssd_hits": 10, "hit_rate": 0.94}
    eng.adapter.tokenize.side_effect = lambda t: list(range(len(t.split())))
    eng.prewarmed_experts = 571
    top = MagicMock(layer_id=5, expert_id=147, hit_count=9001)
    eng.learning_cache.get_stats.return_value = {
        "status": "active", "experts_tracked": 500,
        "total_hits": 12345, "sessions": 7, "top_expert": top}
    return eng


@pytest.fixture()
def client(mock_engine, tmp_path):
    server = WispServer(model_dir=str(tmp_path / "mixtral-8x7b"),
                        engine=mock_engine)
    return TestClient(server.app)


def test_health(client):
    r = client.get("/health")
    assert r.status_code == 200
    assert r.json()["status"] == "ok"


def test_list_models(client):
    r = client.get("/v1/models")
    assert r.status_code == 200
    data = r.json()
    assert data["object"] == "list"
    assert len(data["data"]) == 1
    assert data["data"][0]["object"] == "model"
    assert data["data"][0]["owned_by"] == "wisp"


def test_chat_completion_non_streaming(client):
    r = client.post("/v1/chat/completions", json={
        "model": "mixtral-8x7b",
        "messages": [{"role": "user", "content": "Write a sieve"}],
        "stream": False, "max_tokens": 100})
    assert r.status_code == 200
    d = r.json()
    assert d["object"] == "chat.completion"
    assert d["choices"][0]["finish_reason"] == "stop"
    assert d["choices"][0]["message"]["content"] == "def sieve(n): pass"


def test_openai_python_client_schema(client):
    """Every field the openai package dereferences must be present."""
    r = client.post("/v1/chat/completions", json={
        "model": "mixtral-8x7b",
        "messages": [{"role": "user", "content": "Hi"}]})
    d = r.json()
    for key in ("id", "object", "created", "model", "choices", "usage"):
        assert key in d, f"missing top-level {key}"
    choice = d["choices"][0]
    for key in ("index", "message", "finish_reason"):
        assert key in choice, f"missing choice.{key}"
    assert set(choice["message"]) >= {"role", "content"}
    for key in ("prompt_tokens", "completion_tokens", "total_tokens"):
        assert key in d["usage"], f"missing usage.{key}"
    assert d["usage"]["total_tokens"] == (
        d["usage"]["prompt_tokens"] + d["usage"]["completion_tokens"])
    assert d["id"].startswith("chatcmpl-")


def test_usage_counts_use_real_tokenizer(client, mock_engine):
    client.post("/v1/chat/completions", json={
        "model": "mixtral-8x7b",
        "messages": [{"role": "user", "content": "one two three"}]})
    assert mock_engine.adapter.tokenize.called


def test_chat_completion_streaming_sse_format(client):
    r = client.post("/v1/chat/completions", json={
        "model": "mixtral-8x7b",
        "messages": [{"role": "user", "content": "Hello"}],
        "stream": True})
    assert r.status_code == 200
    assert "text/event-stream" in r.headers["content-type"]

    lines = [l for l in r.text.split("\n") if l.startswith("data: ")]
    assert lines[-1] == "data: [DONE]"

    payloads = [json.loads(l[6:]) for l in lines if l != "data: [DONE]"]
    assert payloads[0]["choices"][0]["delta"]["role"] == "assistant"
    content = "".join(p["choices"][0]["delta"].get("content", "")
                      for p in payloads)
    assert content == "def sieve(n): pass"
    assert payloads[-1]["choices"][0]["finish_reason"] == "stop"
    for p in payloads:
        assert p["object"] == "chat.completion.chunk"


def test_streaming_is_incremental_not_buffered(mock_engine, tmp_path):
    """Each engine piece must become its own SSE chunk. Collecting the
    whole generation and emitting it at the end would pass a naive
    content check while making streaming useless at WISP's token rates.
    """
    pieces = [f"tok{i} " for i in range(12)]
    mock_engine.stream.return_value = iter(pieces)
    server = WispServer(model_dir=str(tmp_path / "mixtral-8x7b"),
                        engine=mock_engine)
    with TestClient(server.app) as c:
        r = c.post("/v1/chat/completions", json={
            "model": "mixtral-8x7b",
            "messages": [{"role": "user", "content": "go"}],
            "stream": True})
    payloads = [json.loads(l[6:]) for l in r.text.split("\n")
                if l.startswith("data: ") and l != "data: [DONE]"]
    content_chunks = [p for p in payloads
                      if p["choices"][0]["delta"].get("content")]
    assert len(content_chunks) == len(pieces)


def test_stats_endpoint(client):
    r = client.get("/v1/stats")
    assert r.status_code == 200
    d = r.json()
    assert d["tok_per_sec"] == pytest.approx(4.2)
    assert d["cache_hits"]["vram_hits"] == 100
    assert d["learning_cache"]["experts_tracked"] == 500
    assert d["learning_cache"]["top_expert"]["expert_id"] == 147
    assert d["prewarmed_experts"] == 571


def test_generation_params_forwarded(client, mock_engine):
    client.post("/v1/chat/completions", json={
        "model": "mixtral-8x7b",
        "messages": [{"role": "user", "content": "Hi"}],
        "max_tokens": 123, "temperature": 0.25, "top_p": 0.5,
        "stop": ["\n\n"]})
    kwargs = mock_engine.generate.call_args.kwargs
    assert kwargs["max_new_tokens"] == 123
    assert kwargs["temperature"] == pytest.approx(0.25)
    assert kwargs["top_p"] == pytest.approx(0.5)
    assert kwargs["stop_sequences"] == ["\n\n"]


def test_openai_only_params_are_tolerated(client):
    """presence/frequency_penalty and n are sent by real clients; the
    server must accept them rather than 422."""
    r = client.post("/v1/chat/completions", json={
        "model": "mixtral-8x7b",
        "messages": [{"role": "user", "content": "Hi"}],
        "presence_penalty": 0.5, "frequency_penalty": 0.5,
        "n": 1, "user": "saksham"})
    assert r.status_code == 200


def test_engine_error_surfaces_in_stream(mock_engine, tmp_path):
    """If generation dies mid-stream the client is told, not left
    hanging on a silent truncation."""
    def _boom():
        yield "partial"
        raise RuntimeError("VRAM exhausted")
    mock_engine.stream.return_value = _boom()
    server = WispServer(model_dir=str(tmp_path / "m"), engine=mock_engine)
    with TestClient(server.app) as c:
        r = c.post("/v1/chat/completions", json={
            "model": "m", "messages": [{"role": "user", "content": "x"}],
            "stream": True})
    assert "VRAM exhausted" in r.text
    assert r.text.rstrip().endswith("data: [DONE]")
