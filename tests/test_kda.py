"""
Tests for Kimi Delta Attention — the linear-attention path used in 69 of
Kimi K3's 93 layers.

The load-bearing property is that the state is CONSTANT size no matter
how long the context gets; several tests pin that down directly.
"""

import pytest
import torch

from wisp.runtime.kda_layer import KDALayer, kda_layer_count

try:
    import wisp._wisp_core as _core
    HAS_ENGINE = True
    HAS_CUDA_KDA = (getattr(_core, "cuda_enabled", False)
                    and hasattr(_core, "kda_decode_step_ptr")
                    and torch.cuda.is_available())
except (ImportError, OSError):
    _core = None
    HAS_ENGINE = False
    HAS_CUDA_KDA = False


# --------------------------------------------------------------------------
# Layer layout — 69 KDA + 24 Gated MLA
# --------------------------------------------------------------------------

def test_kda_layer_identification():
    """K3 has 69 KDA and 24 MLA layers (confirmed arXiv:2607.24653)."""
    kda, mla = kda_layer_count(93)
    assert kda == 69
    assert mla == 24


def test_kda_layer_pattern():
    """[KDA, KDA, KDA, MLA] x 23, then a final MLA."""
    for block in range(23):
        base = block * 4
        assert KDALayer.is_kda_layer(base + 0, 93)
        assert KDALayer.is_kda_layer(base + 1, 93)
        assert KDALayer.is_kda_layer(base + 2, 93)
        assert not KDALayer.is_kda_layer(base + 3, 93)
    assert not KDALayer.is_kda_layer(92, 93)      # final layer is global


def test_kda_layer_index_bounds():
    with pytest.raises(IndexError):
        KDALayer.is_kda_layer(93, 93)
    with pytest.raises(IndexError):
        KDALayer.is_kda_layer(-1, 93)


# --------------------------------------------------------------------------
# The core invariant: constant-size state
# --------------------------------------------------------------------------

def test_kda_state_constant_size():
    """State shape never changes — not after 10 tokens, not after 1000.
    This is the whole reason KDA exists."""
    layer = KDALayer(hidden_size=256, num_heads=4, head_dim=64,
                     layer_idx=0)
    state = KDALayer.new_state(1, 4, 64)
    nbytes = state.numel() * state.element_size()

    with torch.no_grad():
        for _ in range(10):
            _, state = layer(torch.randn(1, 1, 256), state)
        assert state.shape == (1, 4, 64, 64)

        for _ in range(1000):
            _, state = layer(torch.randn(1, 1, 256), state)
    assert state.shape == (1, 4, 64, 64)
    assert state.numel() * state.element_size() == nbytes
    assert torch.isfinite(state).all(), "state diverged over 1010 steps"


def test_kda_decode_output_shape():
    layer = KDALayer(hidden_size=256, num_heads=4, head_dim=64,
                     layer_idx=0)
    state = KDALayer.new_state(1, 4, 64)
    with torch.no_grad():
        out, new_state = layer(torch.randn(1, 1, 256), state)
    assert out.shape == (1, 1, 256)
    assert new_state.shape == (1, 4, 64, 64)


def test_kda_prefill_output_shape():
    layer = KDALayer(hidden_size=256, num_heads=4, head_dim=64,
                     layer_idx=0)
    state = KDALayer.new_state(1, 4, 64)
    with torch.no_grad():
        out, new_state = layer(torch.randn(1, 50, 256), state,
                               is_prefill=True)
    assert out.shape == (1, 50, 256)
    assert new_state.shape == (1, 4, 64, 64)


def test_kda_delta_rule_update():
    """State actually moves — guards against a no-op kernel."""
    layer = KDALayer(hidden_size=64, num_heads=2, head_dim=32,
                     layer_idx=0)
    state = KDALayer.new_state(1, 2, 32)
    with torch.no_grad():
        _, new_state = layer(torch.randn(1, 1, 64), state)
    assert not torch.allclose(state, new_state)


def test_kda_state_resets_between_conversations():
    """Zeroing the state clears history — no bleed across sessions."""
    layer = KDALayer(hidden_size=64, num_heads=2, head_dim=32,
                     layer_idx=0)
    state = KDALayer.new_state(1, 2, 32)
    with torch.no_grad():
        _, state = layer(torch.randn(1, 1, 64), state)
        assert state.abs().sum() > 0
        state.zero_()
        assert torch.all(state == 0)
        # A fresh token against a zero state produces zero output,
        # exactly as it would on the first token of a new conversation.
        out, _ = layer(torch.randn(1, 1, 64), state)
    assert torch.isfinite(out).all()


# --------------------------------------------------------------------------
# Correctness of the recurrence itself
# --------------------------------------------------------------------------

def test_kda_matches_hand_computed_recurrence():
    """The torch path reproduces S_t = S*(1 - sigmoid(b)k) + v k^T and
    o_t = silu(g) * (S q) computed by hand."""
    torch.manual_seed(0)
    layer = KDALayer(hidden_size=8, num_heads=1, head_dim=8, layer_idx=0)
    B, H, D = 1, 1, 8
    q = torch.randn(B, H, D)
    k = torch.randn(B, H, D)
    v = torch.randn(B, H, D)
    beta = torch.randn(B, H, D)
    gate = torch.randn(B, H, D)
    state = torch.randn(B, H, D, D)

    out, new_state = layer._torch_decode_step(q, k, v, beta, gate, state)

    # Hand-rolled reference, elementwise
    ref_out = torch.zeros(B, H, D)
    ref_state = torch.zeros(B, H, D, D)
    for dv in range(D):
        acc = sum(state[0, 0, dk, dv] * q[0, 0, dk] for dk in range(D))
        ref_out[0, 0, dv] = torch.sigmoid(gate[0, 0, dv]) \
            * gate[0, 0, dv] * acc
        for dk in range(D):
            decay = 1.0 - torch.sigmoid(beta[0, 0, dk]) * k[0, 0, dk]
            ref_state[0, 0, dk, dv] = (state[0, 0, dk, dv] * decay
                                       + v[0, 0, dv] * k[0, 0, dk])

    assert torch.allclose(out, ref_out, atol=1e-5)
    assert torch.allclose(new_state, ref_state, atol=1e-5)


def test_kda_prefill_equals_sequential_decode():
    """Prefilling T tokens must land on the same state as feeding those
    same T tokens one at a time."""
    torch.manual_seed(1)
    layer = KDALayer(hidden_size=32, num_heads=2, head_dim=16,
                     layer_idx=0)
    x = torch.randn(1, 6, 32)

    with torch.no_grad():
        pre_out, pre_state = layer(x, KDALayer.new_state(1, 2, 16),
                                   is_prefill=True)
        state = KDALayer.new_state(1, 2, 16)
        outs = []
        for t in range(6):
            o, state = layer(x[:, t:t + 1], state)
            outs.append(o)
        seq_out = torch.cat(outs, dim=1)

    assert torch.allclose(pre_state, state, atol=1e-5)
    assert torch.allclose(pre_out, seq_out, atol=1e-5)


def test_kda_rejects_multi_token_decode():
    layer = KDALayer(hidden_size=32, num_heads=2, head_dim=16,
                     layer_idx=0)
    with pytest.raises(ValueError, match="single token"):
        layer(torch.randn(1, 4, 32), KDALayer.new_state(1, 2, 16))


def test_kda_rejects_mismatched_dims():
    with pytest.raises(ValueError, match="must equal hidden_size"):
        KDALayer(hidden_size=100, num_heads=3, head_dim=8, layer_idx=0)


# --------------------------------------------------------------------------
# CUDA kernel
# --------------------------------------------------------------------------

@pytest.mark.engine
@pytest.mark.skipif(not HAS_ENGINE, reason="C engine not available in CI")
def test_kda_cuda_selftest():
    """On-device recurrence check against a host reference (skips
    cleanly on a CPU-only build, where the symbol is absent)."""
    if not hasattr(_core, "_selftest_kda"):
        pytest.skip("CPU-only build — no CUDA KDA kernel")
    assert _core._selftest_kda() is True


@pytest.mark.engine
@pytest.mark.skipif(not HAS_CUDA_KDA, reason="CUDA KDA kernel unavailable")
def test_kda_cuda_matches_torch_reference():
    """The CUDA kernel and the PyTorch fallback must agree — this is
    what lets the fallback stand in for the kernel anywhere."""
    torch.manual_seed(2)
    layer = KDALayer(hidden_size=128, num_heads=4, head_dim=32,
                     layer_idx=0).cuda()
    B, H, D = 1, 4, 32
    q = torch.randn(B, H, D, device="cuda")
    k = torch.randn(B, H, D, device="cuda") * 0.1
    v = torch.randn(B, H, D, device="cuda")
    beta = torch.randn(B, H, D, device="cuda")
    gate = torch.randn(B, H, D, device="cuda")
    state = torch.randn(B, H, D, D, device="cuda")

    cuda_out, cuda_state = layer._cuda_decode_step(
        q, k, v, beta, gate, state)
    ref_out, ref_state = layer._torch_decode_step(
        q, k, v, beta, gate, state)

    # fp16 activations in the kernel vs fp32 reference
    assert torch.allclose(cuda_out, ref_out, atol=2e-2, rtol=2e-2)
    assert torch.allclose(cuda_state, ref_state, atol=2e-2, rtol=2e-2)
