"""
wisp.models.deepseek_v3 — DeepSeek-V3 (671B, MLA, 58 layers, 256 experts, top-8).

Expert lookups per token: 8 x 58 = 464.
Drafter: DeepSeek-R1-Distill-Qwen-1.5B (same tokenizer family, int4 ~800MB).
"""

from __future__ import annotations

from .base_adapter import ModelAdapter
from . import constants as C


class DeepSeekV3Adapter(ModelAdapter):

    @property
    def name(self) -> str: return "DeepSeek-V3"

    @property
    def family(self) -> str: return "deepseek_v3"

    @property
    def hf_model_id(self) -> str: return C.HF_MODEL_ID["deepseek_v3"]

    @property
    def total_parameters(self) -> int: return C.TOTAL_PARAMETERS["deepseek_v3"]

    @property
    def num_layers(self) -> int: return C.NUM_LAYERS["deepseek_v3"]

    @property
    def num_experts_per_layer(self) -> int: return C.NUM_EXPERTS_PER_LAYER["deepseek_v3"]

    @property
    def num_shared_experts(self) -> int: return C.NUM_SHARED_EXPERTS["deepseek_v3"]

    @property
    def top_k_routing(self) -> int: return C.TOP_K_ROUTING["deepseek_v3"]

    @property
    def expert_size_bytes(self) -> int: return C.EXPERT_SIZE_INT4["deepseek_v3"]

    @property
    def dense_layer_size_bytes(self) -> int: return C.DENSE_SIZE["deepseek_v3"]

    @property
    def hidden_size(self) -> int: return C.HIDDEN_SIZE["deepseek_v3"]

    @property
    def attention_type(self) -> str: return C.ATTENTION_TYPE["deepseek_v3"]

    @property
    def vocab_size(self) -> int: return C.VOCAB_SIZE["deepseek_v3"]

    @property
    def has_native_mtp(self) -> bool: return False

    @property
    def drafter_hf_id(self) -> str: return C.DRAFTER_HF_ID["deepseek_v3"]

    @property
    def default_acceptance_rate(self) -> float:
        return C.DEFAULT_ACCEPTANCE_RATE["deepseek_v3"]

    def get_drafter_config(self) -> dict:
        return {
            "type": "same_family",
            "hf_id": self.drafter_hf_id,
            "dtype": "int4",
            "k": self.mtp_k,
            "acceptance": self.default_acceptance_rate,
        }
