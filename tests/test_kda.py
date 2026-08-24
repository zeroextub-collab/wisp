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
        # A fresh token against a zero state behaves exactly like the
        # first token of a new conversation: a real, finite output that
        # depends only on this token.
        out, after = layer(torch.randn(1, 1, 64), state)
    assert torch.isfinite(out).all()
    assert after.abs().sum() > 0


# --------------------------------------------------------------------------
# Correctness of the recurrence itself
# --------------------------------------------------------------------------

def test_kda_matches_hand_computed_recurrence():
    """The torch path reproduces the documented recurrence computed by
    hand, element by element:

        u = S^T kn ; S += b * kn (v-u)^T ; o = silu(g) * (S^T qn)
    """
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

    qn = q[0, 0] / q[0, 0].norm()
    kn = k[0, 0] / k[0, 0].norm()
    b = torch.sigmoid(beta[0, 0])

    ref_state = state.clone()
    ref_out = torch.zeros(B, H, D)
    for dv in range(D):
        u = sum(state[0, 0, dk, dv] * kn[dk] for dk in range(D))
        err = v[0, 0, dv] - u
        acc = 0.0
        for dk in range(D):
            ref_state[0, 0, dk, dv] = state[0, 0, dk, dv] + b[dk] * kn[dk] * err
            acc = acc + ref_state[0, 0, dk, dv] * qn[dk]
        ref_out[0, 0, dv] = torch.sigmoid(gate[0, 0, dv]) * gate[0, 0, dv] * acc

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
    k = torch.randn(B, H, D, device="cuda")
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


# --------------------------------------------------------------------------
# Regressions. Each of these caught a real defect in the first KDA kernel;
# all three would have produced a K3 that loads fine and generates garbage.
# --------------------------------------------------------------------------

def test_kda_first_token_is_not_zero():
    """The output must be read AFTER the state is written.

    Reading first means the first token of every conversation attends to
    an all-zero state and emits exactly 0.0 — no attention variant does
    that, and it is invisible unless you look at token 0 specifically.
    """
    torch.manual_seed(3)
    layer = KDALayer(hidden_size=64, num_heads=2, head_dim=32, layer_idx=0)
    state = KDALayer.new_state(1, 2, 32)
    with torch.no_grad():
        out, _ = layer(torch.randn(1, 1, 64), state)
    assert out.abs().max() > 1e-6, "token 0 produced an all-zero output"


def test_kda_stable_over_long_context():
    """The state stays bounded over a long context at a realistic input
    scale.

    The pre-normalization recurrence hit inf inside 200 tokens here. A
    constant-size state is worthless if its CONTENTS diverge, so this
    asserts a hard bound, not just isfinite.
    """
    torch.manual_seed(4)
    layer = KDALayer(hidden_size=64, num_heads=2, head_dim=32, layer_idx=0)
    state = KDALayer.new_state(1, 2, 32)
    with torch.no_grad():
        for step in range(2000):
            _, state = layer(torch.randn(1, 1, 64) * 3.0, state)
            if step % 500 == 0:
                assert torch.isfinite(state).all(), f"diverged at {step}"
    assert torch.isfinite(state).all()
    assert state.abs().max() < 1e3, (
        f"state grew to {state.abs().max().item():.3e} — the recurrence "
        f"is not contractive")


def test_kda_delta_rule_converges():
    """Writing the same (k, v) repeatedly drives the memory read at that
    key TOWARD v, and the error shrinks monotonically.

    This is what separates a delta rule from plain accumulation: it
    writes the prediction error, so a repeated write is self-limiting
    instead of doubling the stored value. If someone replaces the update
    with `S += v k^T`, the error here grows without bound.
    """
    torch.manual_seed(5)
    layer = KDALayer(hidden_size=32, num_heads=1, head_dim=32, layer_idx=0)
    B, H, D = 1, 1, 32
    k = torch.randn(B, H, D)
    v = torch.randn(B, H, D)
    q = k.clone()                       # query the same slot we write
    beta = torch.zeros(B, H, D)         # sigmoid(0) = 0.5
    gate = torch.full((B, H, D), 4.0)   # silu(4) ~= 3.93, non-zero
    state = KDALayer.new_state(B, H, D)

    kn = k / k.norm(dim=-1, keepdim=True)
    errors = []
    with torch.no_grad():
        for _ in range(12):
            _, state = layer._torch_decode_step(q, k, v, beta, gate, state)
            u = torch.einsum("bhkv,bhk->bhv", state, kn)
            errors.append((v - u).abs().max().item())

    assert errors[-1] < errors[0], "error did not shrink"
    assert all(b <= a + 1e-6 for a, b in zip(errors, errors[1:])),         f"error not monotonic: {errors}"
    assert errors[-1] < 1e-2, f"did not converge to v: {errors[-1]:.4f}"


def test_kda_scale_invariant_in_q_and_k():
    """q and k are L2-normalized inside the recurrence, so scaling either
    must not change the output. This is what the CUDA kernel does
    internally; if the torch path ever stops matching, this fails."""
    torch.manual_seed(6)
    layer = KDALayer(hidden_size=32, num_heads=2, head_dim=16, layer_idx=0)
    B, H, D = 1, 2, 16
    q, k = torch.randn(B, H, D), torch.randn(B, H, D)
    v, beta = torch.randn(B, H, D), torch.randn(B, H, D)
    gate = torch.randn(B, H, D)
    state = torch.randn(B, H, D, D) * 0.1

    with torch.no_grad():
        a_out, a_state = layer._torch_decode_step(
            q, k, v, beta, gate, state)
        b_out, b_state = layer._torch_decode_step(
            q * 50.0, k * 0.02, v, beta, gate, state)

    assert torch.allclose(a_out, b_out, atol=1e-4)
    assert torch.allclose(a_state, b_state, atol=1e-4)


def test_kda_batch_entries_are_independent():
    """One sequence in a batch must not influence another. The state is
    indexed [B, H, d_k, d_v] and the kernel maps batch onto grid.x, so a
    stride mistake here shows up as cross-talk, not as a crash."""
    torch.manual_seed(7)
    layer = KDALayer(hidden_size=32, num_heads=2, head_dim=16, layer_idx=0)
    x_solo = torch.randn(1, 4, 32)
    x_other = torch.randn(1, 4, 32) * 10.0

    with torch.no_grad():
        solo_out, solo_state = layer(
            x_solo, KDALayer.new_state(1, 2, 16), is_prefill=True)
        pair_out, pair_state = layer(
            torch.cat([x_other, x_solo], dim=0),
            KDALayer.new_state(2, 2, 16), is_prefill=True)

    assert torch.allclose(pair_out[1], solo_out[0], atol=1e-5)
    assert torch.allclose(pair_state[1], solo_state[0], atol=1e-5)


@pytest.mark.engine
@pytest.mark.skipif(not HAS_CUDA_KDA, reason="CUDA KDA kernel unavailable")
def test_kda_cuda_prefill_matches_decode():
    """The prefill kernel scans the whole prompt in one launch while the
    decode kernel does one token per launch. They must land on the same
    state and emit the same tokens, or a prompt and its continuation
    disagree about history."""
    torch.manual_seed(8)
    layer = KDALayer(hidden_size=128, num_heads=4, head_dim=32,
                     layer_idx=0).cuda()
    x = torch.randn(1, 7, 128, device="cuda")

    with torch.no_grad():
        pre_out, pre_state = layer(
            x, KDALayer.new_state(1, 4, 32, device="cuda"),
            is_prefill=True)
        state = KDALayer.new_state(1, 4, 32, device="cuda")
        outs = []
        for t in range(7):
            o, state = layer(x[:, t:t + 1], state)
            outs.append(o)

    assert torch.allclose(pre_state, state, atol=2e-2, rtol=2e-2)
    assert torch.allclose(pre_out, torch.cat(outs, dim=1),
                          atol=2e-2, rtol=2e-2)


@pytest.mark.engine
@pytest.mark.skipif(not HAS_CUDA_KDA, reason="CUDA KDA kernel unavailable")
@pytest.mark.parametrize("head_dim", [32, 100, 200])
def test_kda_cuda_handles_partial_thread_block(head_dim):
    """d_v that is not a multiple of the 128-thread block.

    The kernel L2-normalizes q and k with a block-wide reduction, so
    every thread has to reach __syncthreads() BEFORE the out-of-range
    ones drop out. Get that ordering wrong and the kernel deadlocks
    rather than returning a wrong answer, which is why these dims are
    tested explicitly: 32 (under one block), 100 (partial single block),
    200 (two blocks, second one partial).
    """
    torch.manual_seed(9)
    layer = KDALayer(hidden_size=head_dim * 2, num_heads=2,
                     head_dim=head_dim, layer_idx=0).cuda()
    state = KDALayer.new_state(1, 2, head_dim, device="cuda")
    x = torch.randn(1, 1, head_dim * 2, device="cuda")

    with torch.no_grad():
        cuda_out, cuda_state = layer(x, state)
        cpu_layer = KDALayer(hidden_size=head_dim * 2, num_heads=2,
                             head_dim=head_dim, layer_idx=0)
        cpu_layer.load_state_dict(
            {k: v.cpu() for k, v in layer.state_dict().items()})
        ref_out, ref_state = cpu_layer(x.cpu(), state.cpu())

    assert torch.isfinite(cuda_out).all()
    assert torch.allclose(cuda_out.cpu(), ref_out, atol=2e-2, rtol=2e-2)
    assert torch.allclose(cuda_state.cpu(), ref_state, atol=2e-2, rtol=2e-2)


@pytest.mark.engine
@pytest.mark.skipif(not HAS_CUDA_KDA, reason="CUDA KDA kernel unavailable")
def test_kda_cuda_batch_entries_are_independent():
    """Batch maps onto grid.x and indexes the state; a stride mistake
    shows up as one sequence contaminating another, not as a crash."""
    torch.manual_seed(10)
    layer = KDALayer(hidden_size=64, num_heads=2, head_dim=32,
                     layer_idx=0).cuda()
    x_solo = torch.randn(1, 5, 64, device="cuda")
    x_other = torch.randn(1, 5, 64, device="cuda") * 10.0

    with torch.no_grad():
        solo_out, solo_state = layer(
            x_solo, KDALayer.new_state(1, 2, 32, device="cuda"),
            is_prefill=True)
        pair_out, pair_state = layer(
            torch.cat([x_other, x_solo], dim=0),
            KDALayer.new_state(2, 2, 32, device="cuda"), is_prefill=True)

    assert torch.allclose(pair_out[1], solo_out[0], atol=2e-2, rtol=2e-2)
    assert torch.allclose(pair_state[1], solo_state[0], atol=2e-2, rtol=2e-2)
