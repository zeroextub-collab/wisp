"""
wisp.models.mixtral_8x22b — Mixtral 8x22B Instruct
(141B, GQA 48Q/8KV, 56 layers, 8 experts/layer, top-2).

Expert lookups per token: 2 x 56 = 112.

STORAGE: 448 experts x ~224MB int4 = ~100GB — does NOT fit in RAM;
this one genuinely needs the SSD tier. Dense layers are ~18GB, larger
than typical consumer VRAM, so on <24GB GPUs WISP runs the hybrid mode
(dense on GPU up to budget, experts computed where they land).

Drafter: Mixtral 8x7B drafts for 8x22B — same family, same tokenizer.

Tensor naming, expert .bin layout, and all partitioning hooks are
inherited from the 8x7B adapter — same Mistral family, bigger shapes.
"""

from __future__ import annotations

from .mixtral_8x7b import Mixtral8x7BAdapter
from . import constants as C


class Mixtral8x22BAdapter(Mixtral8x7BAdapter):

    num_attention_heads = 48
    num_kv_heads = 8              # 8 KV heads serve 48 query heads (x6)
    intermediate_size = 16384
    max_position_embeddings = 65536

    @property
    def name(self) -> str: return "Mixtral-8x22B-Instruct"

    @property
    def family(self) -> str: return "mixtral_8x22b"

    @property
    def hf_model_id(self) -> str: return C.HF_MODEL_ID["mixtral_8x22b"]

    @property
    def total_parameters(self) -> int:
        return C.TOTAL_PARAMETERS["mixtral_8x22b"]

    @property
    def num_layers(self) -> int: return C.NUM_LAYERS["mixtral_8x22b"]

    @property
    def num_experts_per_layer(self) -> int:
        return C.NUM_EXPERTS_PER_LAYER["mixtral_8x22b"]

    @property
    def num_shared_experts(self) -> int:
        return C.NUM_SHARED_EXPERTS["mixtral_8x22b"]

    @property
    def top_k_routing(self) -> int:
        return C.TOP_K_ROUTING["mixtral_8x22b"]

    @property
    def expert_size_bytes(self) -> int:
        return C.EXPERT_SIZE_INT4["mixtral_8x22b"]

    @property
    def dense_layer_size_bytes(self) -> int:
        return C.DENSE_SIZE["mixtral_8x22b"]

    @property
    def hidden_size(self) -> int: return C.HIDDEN_SIZE["mixtral_8x22b"]

    @property
    def vocab_size(self) -> int: return C.VOCAB_SIZE["mixtral_8x22b"]

    @property
    def drafter_hf_id(self) -> str:
        return C.DRAFTER_HF_ID["mixtral_8x22b"]

    @property
    def default_acceptance_rate(self) -> float:
        return C.DEFAULT_ACCEPTANCE_RATE["mixtral_8x22b"]
