"""
Tests for the generation loop — driven end-to-end through GenerationLoop
with a scripted fake core, so the sampling, streaming, stop-sequence, and
termination logic is exercised without weights or the C engine.
"""

import pytest
import torch

from wisp.runtime.generation import GenerationLoop, _StopHandler
from wisp.runtime.tier_cache import TierCache
from wisp.speculative.sampler import SamplerConfig

VOCAB = 100
EOS = 99


class FakeAdapter:
    """Tokens 0-25 <-> letters a-z; EOS = 99."""

    eos_token_id = EOS
    mtp_k = 3

    def tokenize(self, text):
        return [ord(c) - ord("a") for c in text if "a" <= c <= "z"]

    def detokenize(self, ids):
        return "".join(chr(ord("a") + t) for t in ids
                       if 0 <= t < 26)


class FakeCore:
    """Plays back a scripted token sequence as one-hot logits."""

    def __init__(self, script):
        self.script = list(script)
        self.pos = 0
        self.decode_calls = 0

    def _next_logits(self):
        logits = [0.0] * VOCAB
        tok = self.script[self.pos] if self.pos < len(self.script) else EOS
        self.pos += 1
        logits[tok] = 100.0
        return logits

    def prefill(self, handle, ids, kv):
        return self._next_logits()

    def decode_one(self, handle, token, kv):
        self.decode_calls += 1
        return self._next_logits()

    def expert_prefetch_hint(self, handle, layer, experts):
        pass

    def cache_stats(self, handle):
        return {"vram_hits": 0, "ram_hits": 0, "ssd_hits": 0,
                "hit_rate": 0.0}


def make_loop(script):
    core = FakeCore(script)
    adapter = FakeAdapter()
    tc = TierCache(core, 0, num_layers=2, top_k=2)
    return GenerationLoop(core, 0, adapter, tc, kv_cache_ptr=0), core


def toks(text):
    return [ord(c) - ord("a") for c in text]


GREEDY = SamplerConfig(temperature=0.0)


# --------------------------------------------------------------------------
# Core loop behavior
# --------------------------------------------------------------------------

def test_stream_emits_scripted_text_and_stops_on_eos():
    loop, core = make_loop(toks("hello") + [EOS])
    out = "".join(loop.stream("hi", max_tokens=50, sampler=GREEDY))
    assert out == "hello"
    # EOS must never require an extra decode after it was sampled
    assert core.pos <= len(core.script) + 1


def test_stream_respects_max_tokens():
    loop, _ = make_loop(toks("abcdefghij"))
    out = "".join(loop.stream("x", max_tokens=3, sampler=GREEDY))
    assert out == "abc"


def test_stop_sequence_cuts_before_match():
    loop, _ = make_loop(toks("helloworld") + [EOS])
    out = "".join(loop.stream("x", max_tokens=50, sampler=GREEDY,
                              stop_sequences=["owo"]))
    assert out == "hell"          # cut at the earliest match, not emitted
    assert "owo" not in out


def test_stop_sequence_never_leaks_partial_match():
    """A stop split across decode steps must not stream out first."""
    loop, _ = make_loop(toks("abstop") + [EOS])
    pieces = list(loop.stream("x", max_tokens=50, sampler=GREEDY,
                              stop_sequences=["stop"]))
    assert "".join(pieces) == "ab"
    for p in pieces:
        assert "stop" not in p


def test_stream_without_stops_streams_incrementally():
    loop, _ = make_loop(toks("abcd") + [EOS])
    pieces = list(loop.stream("x", max_tokens=50, sampler=GREEDY))
    assert len(pieces) >= 2       # genuinely streaming, not one blob
    assert "".join(pieces) == "abcd"


# --------------------------------------------------------------------------
# _StopHandler unit behavior
# --------------------------------------------------------------------------

def test_stop_handler_holdback_and_flush():
    h = _StopHandler(["END"])
    assert h.push("hel") == "h"           # holds back len("END")-1 = 2
    assert h.push("hello") == "el"
    assert h.flush("hello") == "lo"       # flush releases the tail
    assert not h.done


def test_stop_handler_cuts_at_earliest_stop():
    h = _StopHandler(["XX", "YY"])
    piece = h.push("abYYcdXX")
    assert piece == "ab"
    assert h.done
    assert h.push("abYYcdXXmore") == ""   # nothing after done


def test_stop_handler_no_stops_passthrough():
    h = _StopHandler(None)
    assert h.push("abc") == "abc"
    assert h.push("abcdef") == "def"
    assert h.flush("abcdef") == ""


# --------------------------------------------------------------------------
# Engine-level parameter plumbing (no C engine needed)
# --------------------------------------------------------------------------

def test_sampler_config_carries_all_generation_params():
    cfg = SamplerConfig(temperature=0.5, top_k=40, top_p=0.9,
                        repetition_penalty=1.1)
    assert cfg.temperature == 0.5
    assert cfg.top_k == 40
    assert cfg.top_p == pytest.approx(0.9)
    assert cfg.repetition_penalty == pytest.approx(1.1)


def test_prefetch_observe_predict_cycle():
    """The tier cache learns router picks and predicts hot experts."""
    core = FakeCore([EOS])
    tc = TierCache(core, 0, num_layers=1, top_k=2)
    for _ in range(5):
        tc.observe(0, [3, 7])
    tc.observe(0, [1, 7])
    predicted = tc.predict(0)
    assert predicted[0] == 7          # most frequent first
    assert 3 in predicted
