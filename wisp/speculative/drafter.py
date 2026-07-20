"""
wisp.speculative.drafter — drafter model loader + forward pass.

Two drafter kinds:

  DenseDrafter  — a small same-family dense model (e.g. DeepSeek-R1-Distill-
                  Qwen-1.5B) run entirely in torch. Implements a full
                  Qwen2/Llama-style decoder: RMSNorm, GQA attention with
                  RoPE, SwiGLU MLP, tied-or-separate lm_head, incremental
                  KV cache. Small enough that torch is fast enough.

  NativeMTPDrafter — GLM-5.2's built-in multi-token-prediction head
                  (matey-0's int8 fix). A single transformer block that
                  reads the main model's embedding table: much cheaper than
                  a separate model, and distribution-matched by construction.

Both expose the same surface the verifier needs:
    prefill(input_ids) / decode_one(input_ids) -> logits [vocab]
    reset() — clear KV cache between requests
"""

from __future__ import annotations

import json
import math
from pathlib import Path

import torch
import torch.nn.functional as F
from safetensors.torch import load_file


# --------------------------------------------------------------------------- #
# Shared building blocks
# --------------------------------------------------------------------------- #
def rms_norm(x: torch.Tensor, weight: torch.Tensor,
             eps: float = 1e-6) -> torch.Tensor:
    dtype = x.dtype
    x = x.float()
    x = x * torch.rsqrt(x.pow(2).mean(-1, keepdim=True) + eps)
    return (x * weight.float()).to(dtype)


def build_rope_cache(head_dim: int, max_pos: int, theta: float,
                     device: torch.device) -> tuple[torch.Tensor, torch.Tensor]:
    inv_freq = 1.0 / (theta ** (
        torch.arange(0, head_dim, 2, device=device).float() / head_dim))
    t = torch.arange(max_pos, device=device).float()
    freqs = torch.outer(t, inv_freq)                    # [max_pos, head_dim/2]
    return freqs.cos(), freqs.sin()


def apply_rope(x: torch.Tensor, cos: torch.Tensor,
               sin: torch.Tensor, pos: int) -> torch.Tensor:
    """x: [seq, heads, head_dim]; rotate-half (neox) convention."""
    seq = x.shape[0]
    c = cos[pos:pos + seq].unsqueeze(1)                 # [seq, 1, hd/2]
    s = sin[pos:pos + seq].unsqueeze(1)
    x1, x2 = x.chunk(2, dim=-1)
    return torch.cat([x1 * c - x2 * s, x2 * c + x1 * s], dim=-1)


# --------------------------------------------------------------------------- #
# Dense drafter (Qwen2 / Llama-family layout)
# --------------------------------------------------------------------------- #
class DenseDrafter:

    def __init__(self, model_dir: str | Path, device: str = "cuda",
                 dtype: torch.dtype = torch.float16):
        self.dir = Path(model_dir)
        self.device = torch.device(
            device if (device != "cuda" or torch.cuda.is_available()) else "cpu")
        self.dtype = dtype if self.device.type == "cuda" else torch.float32

        cfg_path = self.dir / "config.json"
        if not cfg_path.exists():
            raise FileNotFoundError(f"Drafter config.json missing at {cfg_path}")
        with open(cfg_path, encoding="utf-8") as f:
            cfg = json.load(f)

        self.n_layers  = cfg["num_hidden_layers"]
        self.n_heads   = cfg["num_attention_heads"]
        self.n_kv      = cfg.get("num_key_value_heads", self.n_heads)
        self.hidden    = cfg["hidden_size"]
        self.head_dim  = cfg.get("head_dim", self.hidden // self.n_heads)
        self.vocab     = cfg["vocab_size"]
        self.eps       = cfg.get("rms_norm_eps", 1e-6)
        self.max_pos   = min(cfg.get("max_position_embeddings", 32768), 32768)
        theta          = cfg.get("rope_theta", 10000.0)

        self.w = self._load_weights()
        self.cos, self.sin = build_rope_cache(
            self.head_dim, self.max_pos, theta, self.device)
        self.reset()

    def _load_weights(self) -> dict[str, torch.Tensor]:
        shards = sorted(self.dir.glob("*.safetensors"))
        if not shards:
            raise FileNotFoundError(
                f"No .safetensors in {self.dir} — download the drafter first "
                f"(wisp does this automatically on first run)."
            )
        w: dict[str, torch.Tensor] = {}
        for shard in shards:
            for k, v in load_file(str(shard)).items():
                w[k] = v.to(self.device, self.dtype)
        if "lm_head.weight" not in w:  # tied embeddings
            w["lm_head.weight"] = w["model.embed_tokens.weight"]
        return w

    # ------------------------------------------------------------------ #
    def reset(self) -> None:
        self.k_cache = [
            torch.zeros(0, self.n_kv, self.head_dim,
                        device=self.device, dtype=self.dtype)
            for _ in range(self.n_layers)]
        self.v_cache = [
            torch.zeros(0, self.n_kv, self.head_dim,
                        device=self.device, dtype=self.dtype)
            for _ in range(self.n_layers)]
        self.pos = 0

    @property
    def seq_len(self) -> int:
        return self.pos

    # ------------------------------------------------------------------ #
    def _forward(self, ids: torch.Tensor) -> torch.Tensor:
        """ids: [seq] new tokens. Returns logits for the LAST position."""
        w = self.w
        seq = ids.shape[0]
        x = w["model.embed_tokens.weight"][ids]           # [seq, hidden]

        for i in range(self.n_layers):
            p = f"model.layers.{i}."
            h = rms_norm(x, w[p + "input_layernorm.weight"], self.eps)

            q = h @ w[p + "self_attn.q_proj.weight"].T
            k = h @ w[p + "self_attn.k_proj.weight"].T
            v = h @ w[p + "self_attn.v_proj.weight"].T
            if p + "self_attn.q_proj.bias" in w:
                q = q + w[p + "self_attn.q_proj.bias"]
                k = k + w[p + "self_attn.k_proj.bias"]
                v = v + w[p + "self_attn.v_proj.bias"]

            q = q.view(seq, self.n_heads, self.head_dim)
            k = k.view(seq, self.n_kv, self.head_dim)
            v = v.view(seq, self.n_kv, self.head_dim)
            q = apply_rope(q, self.cos, self.sin, self.pos)
            k = apply_rope(k, self.cos, self.sin, self.pos)

            self.k_cache[i] = torch.cat([self.k_cache[i], k], dim=0)
            self.v_cache[i] = torch.cat([self.v_cache[i], v], dim=0)
            K, V = self.k_cache[i], self.v_cache[i]       # [total, kv, hd]

            rep = self.n_heads // self.n_kv
            Kx = K.repeat_interleave(rep, dim=1)          # [total, heads, hd]
            Vx = V.repeat_interleave(rep, dim=1)

            # [heads, seq, total]
            scores = torch.einsum("shd,thd->hst", q, Kx) / math.sqrt(self.head_dim)
            total = K.shape[0]
            causal = torch.arange(total, device=self.device)[None, :] > \
                     (self.pos + torch.arange(seq, device=self.device))[:, None]
            scores = scores.masked_fill(causal[None], float("-inf"))
            attn = F.softmax(scores.float(), dim=-1).to(self.dtype)
            out = torch.einsum("hst,thd->shd", attn, Vx).reshape(seq, -1)
            x = x + out @ w[p + "self_attn.o_proj.weight"].T

            h = rms_norm(x, w[p + "post_attention_layernorm.weight"], self.eps)
            gate = h @ w[p + "mlp.gate_proj.weight"].T
            up   = h @ w[p + "mlp.up_proj.weight"].T
            x = x + (F.silu(gate) * up) @ w[p + "mlp.down_proj.weight"].T

        self.pos += seq
        h = rms_norm(x[-1:], w["model.norm.weight"], self.eps)
        return (h @ w["lm_head.weight"].T).float().squeeze(0)   # [vocab]

    # ------------------------------------------------------------------ #
    @torch.no_grad()
    def prefill(self, input_ids: torch.Tensor) -> torch.Tensor:
        ids = input_ids.reshape(-1).to(self.device)
        new = ids[self.pos:]
        if new.numel() == 0:  # everything already cached — recompute last
            self.pos -= 1
            for i in range(self.n_layers):
                self.k_cache[i] = self.k_cache[i][:-1]
                self.v_cache[i] = self.v_cache[i][:-1]
            new = ids[-1:]
        return self._forward(new)

    @torch.no_grad()
    def decode_one(self, input_ids: torch.Tensor) -> torch.Tensor:
        """The verifier passes the FULL id sequence; we consume the tail."""
        return self.prefill(input_ids)


# --------------------------------------------------------------------------- #
# Native MTP drafter (GLM-5.2 int8 head)
# --------------------------------------------------------------------------- #
class NativeMTPDrafter:
    """
    GLM-5.2's multi-token-prediction head: one transformer block over the
    main model's token embeddings, projected back to vocab. Stored int8 with
    per-row fp16 scales (matey-0's format); dequantized to fp16 on load
    (the head is ~1GB — it lives resident, never streamed).
    """

    def __init__(self, model_dir: str | Path, device: str = "cuda"):
        self.dir = Path(model_dir)
        self.device = torch.device(
            device if (device != "cuda" or torch.cuda.is_available()) else "cpu")
        self.dtype = torch.float16 if self.device.type == "cuda" else torch.float32

        mtp_path = self.dir / "mtp" / "mtp_head_int8.safetensors"
        if not mtp_path.exists():
            raise FileNotFoundError(
                f"Native MTP head missing at {mtp_path}. "
                f"Convert with the MTP head repo (matey-0/GLM-5.2-mtp-int8) "
                f"or run without --speculative."
            )
        raw = load_file(str(mtp_path))
        self.w = self._dequant(raw)

        dense = self.dir / "dense" / "model_dense.safetensors"
        # Only the embedding table + lm_head are needed from the main model.
        from safetensors import safe_open
        with safe_open(str(dense), framework="pt", device="cpu") as f:
            self.embed = f.get_tensor("embed_tokens").to(self.device, self.dtype)
            self.lm_head = f.get_tensor("lm_head").to(self.device, self.dtype)
        self.hidden = self.embed.shape[1]
        self.eps = 1e-6
        self.reset()

    def _dequant(self, raw: dict[str, torch.Tensor]) -> dict[str, torch.Tensor]:
        out: dict[str, torch.Tensor] = {}
        for name, t in raw.items():
            if name.endswith(".scales"):
                continue
            scale_key = name + ".scales"
            if t.dtype == torch.int8 and scale_key in raw:
                scales = raw[scale_key].to(torch.float32)
                out[name] = (t.to(torch.float32)
                             * scales.unsqueeze(-1)).to(self.device, self.dtype)
            else:
                out[name] = t.to(self.device, self.dtype)
        return out

    def reset(self) -> None:
        self._history = torch.zeros(0, dtype=torch.long, device=self.device)

    @property
    def seq_len(self) -> int:
        return int(self._history.shape[0])

    @torch.no_grad()
    def _head_forward(self, ids: torch.Tensor) -> torch.Tensor:
        """One block over the last few token embeddings -> next-token logits."""
        w = self.w
        window = ids[-8:]                                  # MTP context window
        x = self.embed[window]                             # [win, hidden]

        h = rms_norm(x, w["norm1.weight"], self.eps)
        q = h @ w["attn.q.weight"].T
        k = h @ w["attn.k.weight"].T
        v = h @ w["attn.v.weight"].T
        d = q.shape[-1]
        scores = (q @ k.T) / math.sqrt(d)
        mask = torch.triu(torch.ones_like(scores, dtype=torch.bool), diagonal=1)
        scores = scores.masked_fill(mask, float("-inf"))
        attn = F.softmax(scores.float(), dim=-1).to(self.dtype)
        x = x + (attn @ v) @ w["attn.o.weight"].T

        h = rms_norm(x, w["norm2.weight"], self.eps)
        gate = h @ w["mlp.gate.weight"].T
        up   = h @ w["mlp.up.weight"].T
        x = x + (F.silu(gate) * up) @ w["mlp.down.weight"].T

        h = rms_norm(x[-1:], w["final_norm.weight"], self.eps)
        return (h @ self.lm_head.T).float().squeeze(0)

    @torch.no_grad()
    def prefill(self, input_ids: torch.Tensor) -> torch.Tensor:
        self._history = input_ids.reshape(-1).to(self.device)
        return self._head_forward(self._history)

    @torch.no_grad()
    def decode_one(self, input_ids: torch.Tensor) -> torch.Tensor:
        return self.prefill(input_ids)


# --------------------------------------------------------------------------- #
# Loader
# --------------------------------------------------------------------------- #
def load_drafter(drafter_config: dict, model_dir: str | Path,
                 location: str = "vram"):
    """
    Instantiate the right drafter for a converted model.

    drafter_config comes from adapter.get_drafter_config();
    location comes from the AutoConfig VRAM fit logic ("vram" | "cpu").
    """
    device = "cuda" if location == "vram" else "cpu"
    kind = drafter_config.get("type", "same_family")

    if kind == "native_mtp":
        return NativeMTPDrafter(model_dir, device=device)

    drafter_dir = Path(model_dir) / "drafter"
    if not drafter_dir.exists():
        from ..converter.downloader import download_model
        print(f"  [WISP] Fetching drafter {drafter_config['hf_id']} "
              f"(first run only)...")
        download_model(drafter_config["hf_id"], drafter_dir)
    return DenseDrafter(drafter_dir, device=device)
