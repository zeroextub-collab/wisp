"""Tests for speculative decoding: sampler + rejection-sampling verifier."""

import pytest
import torch

from wisp.speculative.sampler import (SamplerConfig, filter_logits,
                                      sample_token)
from wisp.speculative.verifier import SpeculativeDecoder

VOCAB = 16


# --------------------------------------------------------------------------
# Sampler
# --------------------------------------------------------------------------

def test_greedy_at_zero_temperature():
    logits = torch.zeros(VOCAB)
    logits[7] = 5.0
    cfg = SamplerConfig(temperature=0.0)
    assert sample_token(logits, cfg) == 7


def test_top_k_masks_tail():
    logits = torch.arange(VOCAB, dtype=torch.float32)
    filtered = filter_logits(logits, top_k=3)
    kept = torch.isfinite(filtered).nonzero().flatten().tolist()
    assert kept == [13, 14, 15]


def test_top_p_keeps_nucleus():
    logits = torch.full((VOCAB,), -100.0)
    logits[0], logits[1] = 10.0, 9.0     # ~73% and ~27% of the mass
    filtered = filter_logits(logits, top_p=0.5)
    assert torch.isfinite(filtered[0])
    # token 0 alone crosses 0.5, but the first token past the threshold
    # is kept by convention — everything after must be masked
    assert not torch.isfinite(filtered[5:]).any()


def test_sampling_respects_distribution():
    torch.manual_seed(0)
    logits = torch.full((VOCAB,), -100.0)
    logits[3] = 10.0
    cfg = SamplerConfig(temperature=1.0)
    draws = {sample_token(logits, cfg) for _ in range(20)}
    assert draws == {3}


def test_repetition_penalty_discourages_repeats():
    logits = torch.zeros(VOCAB)
    logits[2] = 2.0
    logits[9] = 1.9
    cfg = SamplerConfig(temperature=0.0, repetition_penalty=2.0)
    # Without history, 2 wins; after emitting 2, the penalty flips it to 9
    assert sample_token(logits, cfg, prev_ids=[]) == 2
    assert sample_token(logits, cfg, prev_ids=[2]) == 9


# --------------------------------------------------------------------------
# Verifier fakes
# --------------------------------------------------------------------------

class FakeDrafter:
    """Always emits `peak_token` with ~all probability mass."""

    def __init__(self, peak_token: int):
        self.peak = peak_token

    def decode_one(self, ids: torch.Tensor) -> torch.Tensor:
        logits = torch.full((VOCAB,), -20.0)
        logits[self.peak] = 20.0
        return logits

    def reset(self):
        pass


class FakeMain:
    """Per-position logits with a fixed peak (possibly != drafter's)."""

    def __init__(self, peak_token: int):
        self.peak = peak_token
        self.calls = 0

    def prefill(self, ids: torch.Tensor) -> torch.Tensor:
        self.calls += 1
        seq = ids.shape[-1]
        logits = torch.full((seq, VOCAB), -20.0)
        logits[:, self.peak] = 20.0
        return logits


# --------------------------------------------------------------------------
# Verifier behavior
# --------------------------------------------------------------------------

def test_agreeing_models_accept_all_drafts_plus_bonus():
    torch.manual_seed(42)
    dec = SpeculativeDecoder(FakeDrafter(peak_token=5),
                             FakeMain(peak_token=5), K=3)
    out = dec.step(torch.tensor([1, 2]), temperature=1.0)
    # All K accepted + 1 bonus token
    assert out.numel() == 4
    assert out.tolist() == [5, 5, 5, 5]
    assert dec.total_accepted == 3
    assert dec.acceptance_rate == pytest.approx(1.0)


def test_disagreeing_models_reject_and_correct():
    torch.manual_seed(42)
    dec = SpeculativeDecoder(FakeDrafter(peak_token=5),
                             FakeMain(peak_token=9), K=3)
    out = dec.step(torch.tensor([1, 2]), temperature=1.0)
    # First draft rejected -> exactly one token, sampled from the
    # corrected distribution max(p_main - p_draft, 0), which peaks at 9
    assert out.numel() == 1
    assert out.item() == 9
    assert dec.total_accepted == 0
    assert dec.acceptance_rate == 0.0


def test_verification_is_one_parallel_pass():
    torch.manual_seed(0)
    main = FakeMain(peak_token=5)
    dec = SpeculativeDecoder(FakeDrafter(peak_token=5), main, K=3)
    dec.step(torch.tensor([1, 2, 3]), temperature=1.0)
    assert main.calls == 1        # K positions verified in ONE forward pass


def test_output_never_exceeds_k_plus_one():
    torch.manual_seed(7)
    for K in (1, 2, 3, 5):
        dec = SpeculativeDecoder(FakeDrafter(5), FakeMain(5), K=K)
        out = dec.step(torch.tensor([0]), temperature=1.0)
        assert 1 <= out.numel() <= K + 1


def test_acceptance_rate_accumulates_across_steps():
    torch.manual_seed(3)
    dec = SpeculativeDecoder(FakeDrafter(5), FakeMain(5), K=2)
    ids = torch.tensor([0])
    for _ in range(4):
        new = dec.step(ids, temperature=1.0)
        ids = torch.cat([ids, new])
    assert dec.total_drafted == 8            # 4 steps x K=2
    assert 0.0 <= dec.acceptance_rate <= 1.0
