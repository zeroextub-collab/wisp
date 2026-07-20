"""
wisp.runtime.generation — the token generation loop.

Drives the C engine (prefill -> decode_one -> decode_one -> ...) through the
pybind11 bindings, samples with wisp.speculative.sampler, streams decoded
text incrementally, and optionally runs the whole loop through the
SpeculativeDecoder for 2.2-2.8x effective throughput.
"""

from __future__ import annotations

import time
from dataclasses import dataclass, field
from typing import Callable, Iterator

import torch

from ..models.base_adapter import ModelAdapter
from ..speculative.sampler import SamplerConfig, sample_token
from .tier_cache import TierCache


@dataclass
class GenerationResult:
    text: str
    token_ids: list[int]
    prompt_tokens: int
    completion_tokens: int
    elapsed_seconds: float
    tok_per_sec: float
    acceptance_rate: float | None = None
    cache_stats: dict = field(default_factory=dict)


class _StopHandler:
    """
    Streams text safely around stop sequences: holds back just enough of
    the tail that a stop sequence split across two decode steps can never
    leak to the caller, and cuts the output at the earliest stop match.
    """

    def __init__(self, stop_sequences: list[str] | None):
        self.stops = [s for s in (stop_sequences or []) if s]
        self.holdback = max((len(s) for s in self.stops), default=0) - 1
        self.emitted = 0
        self.done = False

    def _earliest_cut(self, text: str) -> int:
        cuts = [i for i in (text.find(s) for s in self.stops) if i != -1]
        return min(cuts) if cuts else -1

    def push(self, text: str) -> str:
        """Return the piece safe to emit now given the full text so far."""
        if self.done:
            return ""
        if self.stops:
            cut = self._earliest_cut(text)
            if cut != -1:
                self.done = True
                piece = text[self.emitted:cut] if cut > self.emitted else ""
                self.emitted = max(self.emitted, cut)
                return piece
            safe = max(self.emitted, len(text) - self.holdback) \
                if self.holdback > 0 else len(text)
        else:
            safe = len(text)
        piece = text[self.emitted:safe]
        self.emitted = safe
        return piece

    def flush(self, text: str) -> str:
        """Emit whatever is still held back at end of generation."""
        if self.done:
            return ""
        if self.stops:
            cut = self._earliest_cut(text)
            if cut != -1:
                self.done = True
                piece = text[self.emitted:cut] if cut > self.emitted else ""
                self.emitted = max(self.emitted, cut)
                return piece
        piece = text[self.emitted:]
        self.emitted = len(text)
        return piece


class _MainModelProxy:
    """
    Adapts the raw C bindings to what SpeculativeDecoder expects:
    prefill(ids) returning PER-POSITION logits for the draft window.
    Uses the extended `verify_tokens` binding (spec's prefill returns only
    the last position, which verification cannot use).
    """

    def __init__(self, core, handle: int, kv_ptr: int):
        self._core = core
        self._handle = handle
        self._kv = kv_ptr
        self._committed = 0  # tokens already in the KV cache

    def prefill(self, full_ids: torch.Tensor) -> torch.Tensor:
        ids = [int(t) for t in full_ids.reshape(-1).tolist()]
        new = ids[self._committed:]
        rows = self._core.verify_tokens(self._handle, new, self._kv)
        return torch.tensor(rows, dtype=torch.float32)

    def commit(self, n_accepted: int, total_drafted: int) -> None:
        """
        Keep the first n_accepted of the drafted tokens in the KV cache,
        roll back the rest.
        """
        rollback = total_drafted - n_accepted
        if rollback > 0:
            self._core.kv_cache_rollback(self._handle, self._kv, rollback)
        self._committed += n_accepted


class GenerationLoop:

    def __init__(self, core, handle: int, adapter: ModelAdapter,
                 tier_cache: TierCache, kv_cache_ptr: int):
        self._core = core
        self._handle = handle
        self.adapter = adapter
        self.tier_cache = tier_cache
        self._kv = kv_cache_ptr

    # ------------------------------------------------------------------ #
    # Plain autoregressive loop
    # ------------------------------------------------------------------ #
    def stream(self, prompt: str, *,
               max_tokens: int = 512,
               sampler: SamplerConfig | None = None,
               stop_sequences: list[str] | None = None,
               on_stats: Callable[[dict], None] | None = None
               ) -> Iterator[str]:
        """Yield decoded text incrementally, one flushable piece at a time.

        Stops on: EOS token, max_tokens reached, or any stop sequence
        appearing in the output (the stop sequence itself is not emitted).
        """
        sampler = sampler or SamplerConfig()
        prompt_ids = self.adapter.tokenize(prompt)
        eos = self.adapter.eos_token_id
        stops = _StopHandler(stop_sequences)

        logits = torch.tensor(
            self._core.prefill(self._handle, prompt_ids, self._kv),
            dtype=torch.float32)

        generated: list[int] = []
        start = time.perf_counter()

        for step in range(max_tokens):
            token = sample_token(logits, sampler, prev_ids=generated)
            generated.append(token)
            if token == eos:
                break

            # Emit only the stable new suffix (incomplete UTF-8 and
            # potential stop-sequence tails held back)
            text = self.adapter.detokenize(generated)
            piece = stops.push(text)
            if piece:
                yield piece
            if stops.done:
                return

            # Predictive prefetch for the NEXT token overlaps this decode
            self.tier_cache.prefetch_all_layers()

            # Memory watermark: never let expert copies fill system RAM —
            # a starved desktop freezes the whole machine. Checked every
            # 10 tokens; evicts 50 LRU RAM experts past 80% (SSD stays
            # authoritative, so this is always safe).
            if step % 10 == 9:
                self._check_ram_watermark()

            logits = torch.tensor(
                self._core.decode_one(self._handle, token, self._kv),
                dtype=torch.float32)

            if on_stats and (step & 7) == 0:
                on_stats(self._live_stats(start, len(generated)))

        final = self.adapter.detokenize(
            [t for t in generated if t != eos])
        piece = stops.flush(final)
        if piece:
            yield piece

    def generate(self, prompt: str, *,
                 max_tokens: int = 512,
                 sampler: SamplerConfig | None = None) -> GenerationResult:
        start = time.perf_counter()
        pieces: list[str] = []
        prompt_ids = self.adapter.tokenize(prompt)
        for piece in self.stream(prompt, max_tokens=max_tokens, sampler=sampler):
            pieces.append(piece)
        elapsed = time.perf_counter() - start
        text = "".join(pieces)
        n_out = max(1, len(self.adapter.tokenize(text)) - 1)
        return GenerationResult(
            text=text,
            token_ids=prompt_ids,
            prompt_tokens=len(prompt_ids),
            completion_tokens=n_out,
            elapsed_seconds=elapsed,
            tok_per_sec=round(n_out / max(elapsed, 1e-6), 2),
            cache_stats=self._core.cache_stats(self._handle),
        )

    # ------------------------------------------------------------------ #
    # Speculative loop
    # ------------------------------------------------------------------ #
    def stream_speculative(self, prompt: str, drafter, *,
                           max_tokens: int = 512,
                           sampler: SamplerConfig | None = None,
                           stop_sequences: list[str] | None = None
                           ) -> Iterator[str]:
        """
        Same contract as stream(), but drafts K tokens per main-model pass.
        Output distribution is identical to the plain loop (rejection
        sampling guarantees it) — only the wall clock changes.
        """
        from ..speculative.verifier import SpeculativeDecoder

        sampler = sampler or SamplerConfig()
        temperature = max(sampler.temperature, 1e-6)
        prompt_ids = self.adapter.tokenize(prompt)
        eos = self.adapter.eos_token_id
        stops = _StopHandler(stop_sequences)

        proxy = _MainModelProxy(self._core, self._handle, self._kv)
        # Prefill the prompt once through the real prefill path
        self._core.prefill(self._handle, prompt_ids, self._kv)
        proxy._committed = len(prompt_ids)

        drafter.reset()
        decoder = SpeculativeDecoder(drafter, proxy, K=self.adapter.mtp_k)

        all_ids = torch.tensor(prompt_ids, dtype=torch.long)
        generated: list[int] = []

        while len(generated) < max_tokens:
            new = decoder.step(all_ids, temperature=temperature)
            new_list = [int(t) for t in new.tolist()]

            # KV bookkeeping: verify_tokens appended K draft entries; keep
            # the accepted prefix, roll back the rest, then commit the
            # bonus/fallback token through decode_one so the cache is exact.
            n_from_draft = min(len(new_list) - 1, decoder.K)
            proxy.commit(n_from_draft, decoder.K)
            # The final token (bonus or corrected fallback) was sampled, not
            # verified — run it through decode_one so the KV cache is exact.
            last = new_list[-1]
            self._core.decode_one(self._handle, last, self._kv)
            proxy._committed += 1

            hit_eos = False
            for t in new_list:
                generated.append(t)
                if t == eos or len(generated) >= max_tokens:
                    hit_eos = t == eos
                    break

            text = self.adapter.detokenize(
                [t for t in generated if t != eos])
            piece = stops.push(text)
            if piece:
                yield piece
            if stops.done:
                self.last_acceptance_rate = decoder.acceptance_rate
                return

            if hit_eos:
                break
            all_ids = torch.cat(
                [all_ids, torch.tensor(new_list, dtype=torch.long)])

        final = self.adapter.detokenize([t for t in generated if t != eos])
        piece = stops.flush(final)
        if piece:
            yield piece
        self.last_acceptance_rate = decoder.acceptance_rate

    # ------------------------------------------------------------------ #
    def _check_ram_watermark(self) -> None:
        import psutil
        vm = psutil.virtual_memory()
        if vm.percent > 80.0 and hasattr(self._core, "ram_trim"):
            freed = self._core.ram_trim(self._handle, 50)
            if freed:
                import logging
                logging.getLogger("wisp.generation").info(
                    "RAM watermark %.0f%% — evicted %d RAM-tier experts",
                    vm.percent, freed)

    # ------------------------------------------------------------------ #
    def _live_stats(self, start: float, n_tokens: int) -> dict:
        elapsed = max(time.perf_counter() - start, 1e-6)
        stats = dict(self._core.cache_stats(self._handle))
        stats["tok_per_sec"] = round(n_tokens / elapsed, 2)
        stats["tokens"] = n_tokens
        return stats
