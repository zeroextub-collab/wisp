"""
wisp.runtime.kda_layer — Kimi Delta Attention as a torch module.

KDA is linear attention with a delta-rule state update. Instead of a KV
cache that grows with the conversation, each head carries a fixed
[d_k, d_v] state matrix:

    beta_t = sigmoid(W_beta x_t)      per-channel decay, in (0, 1)
    S_t    = S_{t-1} * (1 - beta_t k_t) + v_t k_t^T
    o_t    = S_t q_t
    y_t    = silu(g_t) * o_t          output gate

The decay term is what makes it a *delta* rule: the state is reduced by
exactly the amount the incoming key addresses before the new value is
written, so it corrects rather than accumulates. Plain linear attention
(S += v k^T) saturates over long contexts; this does not.

Kimi K3 uses KDA in 69 of its 93 layers, interleaved 3:1 with Gated MLA
(which WISP already runs through its absorbed-MLA path). Because the
state is constant-size, memory at 1M context is bounded by depth, not
by sequence length — that is the property the whole design is buying.

Two execution paths, kept arithmetically identical and cross-checked
against each other by tests/test_kda.py:
  * CUDA   — csrc/cuda/kda_attention.cu via the pointer bindings
  * PyTorch — pure-tensor fallback for CPU-only mode

SCOPE: this module and its kernel are complete and tested. K3 end-to-end
inference additionally needs KDA projection weights in the converted
model (the converter does not map them yet) and a branch in the C
forward pass; see the TODOs in wisp/models/kimi_k3.py.
"""

from __future__ import annotations

import torch
import torch.nn as nn
import torch.nn.functional as F


class _RMSNorm(nn.Module):
    """RMSNorm written out rather than nn.RMSNorm, which only exists in
    torch >= 2.4 while WISP supports >= 2.3."""

    def __init__(self, dim: int, eps: float = 1e-6):
        super().__init__()
        self.weight = nn.Parameter(torch.ones(dim))
        self.eps = eps

    def forward(self, x: torch.Tensor) -> torch.Tensor:
        dtype = x.dtype
        xf = x.float()
        xf = xf * torch.rsqrt(xf.pow(2).mean(-1, keepdim=True) + self.eps)
        return (xf * self.weight.float()).to(dtype)


def _core_or_none():
    """The compiled engine, or None when it is absent/unloadable."""
    try:
        import wisp._wisp_core as core
        return core
    except (ImportError, OSError):
        return None


class KDALayer(nn.Module):
    """
    One Kimi Delta Attention layer.

    forward(x, kda_state, is_prefill) -> (output, new_state)

    `kda_state` is [batch, heads, head_dim, head_dim] and comes back the
    same shape every time — that invariant is the point, and it is what
    test_kda_state_constant_size pins down.
    """

    def __init__(self, hidden_size: int, num_heads: int, head_dim: int,
                 layer_idx: int):
        super().__init__()
        if hidden_size <= 0 or num_heads <= 0 or head_dim <= 0:
            raise ValueError(
                f"KDALayer needs positive dims, got hidden_size="
                f"{hidden_size}, num_heads={num_heads}, "
                f"head_dim={head_dim}")
        if num_heads * head_dim != hidden_size:
            raise ValueError(
                f"num_heads * head_dim must equal hidden_size: "
                f"{num_heads} * {head_dim} != {hidden_size}")

        self.hidden_size = hidden_size
        self.num_heads = num_heads
        self.head_dim = head_dim
        self.layer_idx = layer_idx

        # x -> q, k, v, beta (decay), gate. Bias-free, as in K3.
        self.q_proj = nn.Linear(hidden_size, hidden_size, bias=False)
        self.k_proj = nn.Linear(hidden_size, hidden_size, bias=False)
        self.v_proj = nn.Linear(hidden_size, hidden_size, bias=False)
        self.beta_proj = nn.Linear(hidden_size, hidden_size, bias=False)
        self.gate_proj = nn.Linear(hidden_size, hidden_size, bias=False)
        self.o_proj = nn.Linear(hidden_size, hidden_size, bias=False)

        self.norm = _RMSNorm(hidden_size)

    # ------------------------------------------------------------------ #
    # Layer-type dispatch
    # ------------------------------------------------------------------ #
    @classmethod
    def is_kda_layer(cls, layer_idx: int, total_layers: int = 93) -> bool:
        """
        True when layer `layer_idx` is KDA rather than Gated MLA.

        K3's backbone is 23 blocks of [KDA, KDA, KDA, Gated MLA] followed
        by one final Gated MLA, so the last layer is always global
        attention. For 93 layers that yields exactly 69 KDA and 24 MLA
        (confirmed, arXiv:2607.24653).
        """
        if layer_idx < 0 or layer_idx >= total_layers:
            raise IndexError(
                f"layer_idx {layer_idx} out of range for "
                f"{total_layers} layers")
        if layer_idx == total_layers - 1:
            return False              # final layer is always global MLA
        return (layer_idx % 4) != 3

    @classmethod
    def new_state(cls, batch: int, num_heads: int, head_dim: int,
                  device=None, dtype=torch.float32) -> torch.Tensor:
        """Zeroed KDA state. Kept fp32 regardless of activation dtype —
        it is a running accumulator and fp16 drifts over long contexts."""
        return torch.zeros(batch, num_heads, head_dim, head_dim,
                           device=device, dtype=dtype)

    # ------------------------------------------------------------------ #
    def forward(self, x: torch.Tensor, kda_state: torch.Tensor,
                is_prefill: bool = False
                ) -> tuple[torch.Tensor, torch.Tensor]:
        B, T, H = x.shape
        if H != self.hidden_size:
            raise ValueError(
                f"expected hidden_size {self.hidden_size}, got {H}")
        if not is_prefill and T != 1:
            raise ValueError(
                f"decode expects a single token (T=1), got T={T}; "
                f"pass is_prefill=True for a full sequence")

        xn = self.norm(x)
        shape = (B, T, self.num_heads, self.head_dim)
        q = self.q_proj(xn).view(shape)
        k = self.k_proj(xn).view(shape)
        v = self.v_proj(xn).view(shape)
        beta = self.beta_proj(xn).view(shape)
        gate = self.gate_proj(xn).view(shape)

        if is_prefill:
            out, new_state = self._prefill(q, k, v, beta, gate, kda_state)
        else:
            out, new_state = self._decode_step(
                q.squeeze(1), k.squeeze(1), v.squeeze(1),
                beta.squeeze(1), gate.squeeze(1), kda_state)
            out = out.unsqueeze(1)

        out = out.reshape(B, T, self.hidden_size).to(x.dtype)
        return self.o_proj(out), new_state

    # ------------------------------------------------------------------ #
    def _use_cuda(self, state: torch.Tensor) -> bool:
        core = _core_or_none()
        return (core is not None
                and getattr(core, "cuda_enabled", False)
                and hasattr(core, "kda_decode_step_ptr")
                and state.is_cuda)

    def _decode_step(self, q, k, v, beta, gate, state):
        """One token. [B,H,D] in, [B,H,D] out plus the updated state."""
        if self._use_cuda(state):
            return self._cuda_decode_step(q, k, v, beta, gate, state)
        return self._torch_decode_step(q, k, v, beta, gate, state)

    def _torch_decode_step(self, q, k, v, beta, gate, state):
        """Reference implementation — mirrors kda_decode_step_kernel."""
        st = state.float()
        qf, kf, vf = q.float(), k.float(), v.float()
        decay = torch.sigmoid(beta.float())

        # Output from the state carried in (before this token's update)
        out = torch.einsum("bhkv,bhk->bhv", st, qf)
        out = F.silu(gate.float()) * out

        # Delta rule: S = S * (1 - beta*k) + v k^T
        decay_k = decay * kf                                   # [B,H,d_k]
        new_state = (st - torch.einsum("bhkv,bhk->bhkv", st, decay_k)
                     + torch.einsum("bhv,bhk->bhkv", vf, kf))
        return out, new_state

    def _cuda_decode_step(self, q, k, v, beta, gate, state):
        core = _core_or_none()
        B, H, Dk = q.shape
        Dv = v.shape[-1]

        st = state.detach().clone().contiguous().float()
        qh = q.detach().half().contiguous()
        kh = k.detach().half().contiguous()
        vh = v.detach().half().contiguous()
        bh = beta.detach().half().contiguous()
        gh = gate.detach().half().contiguous()
        out = torch.empty(B, H, Dv, dtype=torch.float16,
                          device=q.device)

        core.kda_decode_step_ptr(
            st.data_ptr(), qh.data_ptr(), kh.data_ptr(), vh.data_ptr(),
            bh.data_ptr(), gh.data_ptr(), out.data_ptr(),
            B, H, Dk, Dv)
        return out.float(), st

    def _prefill(self, q, k, v, beta, gate, initial_state):
        """Whole prompt. The recurrence is ordered in t, so this is a
        scan either way; CUDA does it in one launch per (b,h,dv) column
        instead of one launch per token."""
        if self._use_cuda(initial_state):
            return self._cuda_prefill(q, k, v, beta, gate, initial_state)

        B, T = q.shape[0], q.shape[1]
        state = initial_state.float()
        outs = []
        for t in range(T):
            o, state = self._torch_decode_step(
                q[:, t], k[:, t], v[:, t], beta[:, t], gate[:, t], state)
            outs.append(o)
        return torch.stack(outs, dim=1), state

    def _cuda_prefill(self, q, k, v, beta, gate, initial_state):
        core = _core_or_none()
        B, T, H, Dk = q.shape
        Dv = v.shape[-1]

        st_in = initial_state.detach().contiguous().float()
        st_out = st_in.clone()
        qh = q.detach().half().contiguous()
        kh = k.detach().half().contiguous()
        vh = v.detach().half().contiguous()
        bh = beta.detach().half().contiguous()
        gh = gate.detach().half().contiguous()
        out = torch.empty(B, T, H, Dv, dtype=torch.float16,
                          device=q.device)

        core.kda_prefill_ptr(
            st_out.data_ptr(), st_in.data_ptr(),
            qh.data_ptr(), kh.data_ptr(), vh.data_ptr(),
            bh.data_ptr(), gh.data_ptr(), out.data_ptr(),
            B, T, H, Dk, Dv)
        return out.float(), st_out


def kda_layer_count(total_layers: int = 93) -> tuple[int, int]:
    """(kda_layers, mla_layers) for a K3-style backbone."""
    kda = sum(1 for i in range(total_layers)
              if KDALayer.is_kda_layer(i, total_layers))
    return kda, total_layers - kda
