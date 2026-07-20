"""
wisp.models.deepseek_r1 — DeepSeek-R1 (671B reasoning, MLA, 58 layers, top-8).

Architecturally identical to DeepSeek-V3 (same base); differs in identity,
HF id, and chat behavior (reasoning traces). Shares the V3 drafter.
"""

from __future__ import annotations

from .deepseek_v3 import DeepSeekV3Adapter
from . import constants as C


class DeepSeekR1Adapter(DeepSeekV3Adapter):

    @property
    def name(self) -> str: return "DeepSeek-R1"

    @property
    def family(self) -> str: return "deepseek_r1"

    @property
    def hf_model_id(self) -> str: return C.HF_MODEL_ID["deepseek_r1"]

    @property
    def total_parameters(self) -> int: return C.TOTAL_PARAMETERS["deepseek_r1"]

    @property
    def num_layers(self) -> int: return C.NUM_LAYERS["deepseek_r1"]

    @property
    def num_experts_per_layer(self) -> int: return C.NUM_EXPERTS_PER_LAYER["deepseek_r1"]

    @property
    def num_shared_experts(self) -> int: return C.NUM_SHARED_EXPERTS["deepseek_r1"]

    @property
    def top_k_routing(self) -> int: return C.TOP_K_ROUTING["deepseek_r1"]

    @property
    def expert_size_bytes(self) -> int: return C.EXPERT_SIZE_INT4["deepseek_r1"]

    @property
    def dense_layer_size_bytes(self) -> int: return C.DENSE_SIZE["deepseek_r1"]

    @property
    def drafter_hf_id(self) -> str: return C.DRAFTER_HF_ID["deepseek_r1"]

    @property
    def default_acceptance_rate(self) -> float:
        return C.DEFAULT_ACCEPTANCE_RATE["deepseek_r1"]
