"""
wisp.models.mixtral_8x7b — Mixtral 8x7B Instruct
(47B, GQA 32Q/8KV, 32 layers, 8 experts/layer, top-2).

Expert lookups per token: 2 x 32 = 64.

THE KEY INSIGHT for WISP: total experts = 8 x 32 = 256, at 99,090,552 B
int4 each (MEASURED 2026-07-19) = ~25.4GB — on a 32GB machine the
ENTIRE expert set fits in VRAM + system RAM. After the
first pass there are zero SSD reads, ever: this is WISP's fastest
possible operating mode (~15-25 tok/s warm, ~35-45 effective with the
Mistral-7B drafter) and the ideal end-to-end test model.

TENSOR NAMING — the Mistral family differs from GLM/DeepSeek:
  Dense  : model.layers.{i}.self_attn.{q,k,v,o}_proj.weight
           model.layers.{i}.input_layernorm.weight / post_attention_...
           model.embed_tokens.weight / model.norm.weight / lm_head.weight
  Experts: model.layers.{i}.block_sparse_moe.experts.{j}.{w1,w2,w3}.weight
           w1 = gate_proj (SiLU branch), w2 = down_proj, w3 = up_proj
  Router : model.layers.{i}.block_sparse_moe.gate.weight

The expert .bin layout is IDENTICAL to GLM/DeepSeek — 120-byte header +
canonical [gate | up | down] int4 blobs (i.e. w1, w3, w2 in that order);
the C engine's silu(gate)*up @ down math is naming-agnostic.
"""

from __future__ import annotations

import re

from .base_adapter import ModelAdapter
from . import constants as C

_MIXTRAL_PROJ_MAP = {"w1": "gate_proj", "w3": "up_proj", "w2": "down_proj"}


class Mixtral8x7BAdapter(ModelAdapter):

    # GQA geometry (used by the info display + manifest extras)
    num_attention_heads = 32
    num_kv_heads = 8              # 8 KV heads serve 32 query heads (x4)
    intermediate_size = 14336
    max_position_embeddings = 32768

    @property
    def name(self) -> str: return "Mixtral-8x7B-Instruct"

    @property
    def family(self) -> str: return "mixtral_8x7b"

    @property
    def hf_model_id(self) -> str: return C.HF_MODEL_ID["mixtral_8x7b"]

    @property
    def total_parameters(self) -> int:
        return C.TOTAL_PARAMETERS["mixtral_8x7b"]

    @property
    def num_layers(self) -> int: return C.NUM_LAYERS["mixtral_8x7b"]

    @property
    def num_experts_per_layer(self) -> int:
        return C.NUM_EXPERTS_PER_LAYER["mixtral_8x7b"]

    @property
    def num_shared_experts(self) -> int:
        return C.NUM_SHARED_EXPERTS["mixtral_8x7b"]   # 0 — pure routed MoE

    @property
    def top_k_routing(self) -> int: return C.TOP_K_ROUTING["mixtral_8x7b"]

    @property
    def expert_size_bytes(self) -> int:
        return C.EXPERT_SIZE_INT4["mixtral_8x7b"]

    @property
    def dense_layer_size_bytes(self) -> int:
        return C.DENSE_SIZE["mixtral_8x7b"]

    @property
    def hidden_size(self) -> int: return C.HIDDEN_SIZE["mixtral_8x7b"]

    @property
    def attention_type(self) -> str:
        return C.ATTENTION_TYPE["mixtral_8x7b"]       # "GQA"

    @property
    def vocab_size(self) -> int: return C.VOCAB_SIZE["mixtral_8x7b"]

    @property
    def has_native_mtp(self) -> bool: return False

    @property
    def drafter_hf_id(self) -> str: return C.DRAFTER_HF_ID["mixtral_8x7b"]

    @property
    def default_acceptance_rate(self) -> float:
        return C.DEFAULT_ACCEPTANCE_RATE["mixtral_8x7b"]

    def get_drafter_config(self) -> dict:
        return {
            "type": "same_family",
            "hf_id": self.drafter_hf_id,
            "dtype": "int4",
            "k": self.mtp_k,
            "acceptance": self.default_acceptance_rate,
        }

    # ------------------------------------------------------------------ #
    # Mistral tensor naming
    # ------------------------------------------------------------------ #
    @property
    def expert_weight_pattern(self) -> re.Pattern:
        return re.compile(
            r"model\.layers\.(?P<layer>\d+)\.block_sparse_moe\.experts"
            r"\.(?P<expert>\d+)\.(?P<proj>w1|w2|w3)\.weight"
        )

    def normalize_expert_proj(self, proj: str) -> str:
        return _MIXTRAL_PROJ_MAP[proj]

    def canonical_dense_name(self, hf_name: str) -> str | None:
        # Attention / norms / embeddings follow the Llama-style names the
        # base mapping already covers; only the router key is Mistral's.
        m = re.match(
            r"model\.layers\.(\d+)\.block_sparse_moe\.gate\.weight",
            hf_name)
        if m:
            return f"layers.{m.group(1)}.router"
        return super().canonical_dense_name(hf_name)

    def is_dense_tensor(self, key: str) -> bool:
        return "block_sparse_moe.experts" not in key

    def get_expert_key(self, layer_idx: int, expert_idx: int) -> list[str]:
        base = (f"model.layers.{layer_idx}.block_sparse_moe"
                f".experts.{expert_idx}")
        return [f"{base}.w1.weight",   # gate_proj
                f"{base}.w2.weight",   # down_proj
                f"{base}.w3.weight"]   # up_proj

    def get_router_key(self, layer_idx: int) -> str:
        return f"model.layers.{layer_idx}.block_sparse_moe.gate.weight"
