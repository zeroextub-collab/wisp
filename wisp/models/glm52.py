"""
wisp.models.glm52 — GLM-5.2 (744B, MLA, 61 layers, 256 experts/layer, top-8).

Expert lookups per token: 8 x 61 = 488.
Cold-token cost: 18,350,080 x 488 = ~8.54 GB read from SSD.
Drafter: native int8 MTP head (matey-0's fix — int4 gave 0-4% acceptance,
int8 restores 39-59%).
"""

from __future__ import annotations

from .base_adapter import ModelAdapter
from . import constants as C


class GLM52Adapter(ModelAdapter):

    @property
    def name(self) -> str: return "GLM-5.2"

    @property
    def family(self) -> str: return "glm52"

    @property
    def hf_model_id(self) -> str: return C.HF_MODEL_ID["glm52"]

    @property
    def total_parameters(self) -> int: return C.TOTAL_PARAMETERS["glm52"]

    @property
    def num_layers(self) -> int: return C.NUM_LAYERS["glm52"]

    @property
    def num_experts_per_layer(self) -> int: return C.NUM_EXPERTS_PER_LAYER["glm52"]

    @property
    def num_shared_experts(self) -> int: return C.NUM_SHARED_EXPERTS["glm52"]

    @property
    def top_k_routing(self) -> int: return C.TOP_K_ROUTING["glm52"]

    @property
    def expert_size_bytes(self) -> int: return C.EXPERT_SIZE_INT4["glm52"]

    @property
    def dense_layer_size_bytes(self) -> int: return C.DENSE_SIZE["glm52"]

    @property
    def hidden_size(self) -> int: return C.HIDDEN_SIZE["glm52"]

    @property
    def attention_type(self) -> str: return C.ATTENTION_TYPE["glm52"]

    @property
    def vocab_size(self) -> int: return C.VOCAB_SIZE["glm52"]

    @property
    def has_native_mtp(self) -> bool: return True

    @property
    def drafter_hf_id(self) -> str:
        # Native int8 MTP head from the Colibrì community (matey-0)
        return C.DRAFTER_HF_ID["glm52"]

    @property
    def default_acceptance_rate(self) -> float:
        return C.DEFAULT_ACCEPTANCE_RATE["glm52"]

    def get_drafter_config(self) -> dict:
        return {
            "type": "native_mtp",
            "hf_id": self.drafter_hf_id,
            "dtype": "int8",
            "k": self.mtp_k,
            "acceptance": self.default_acceptance_rate,
        }
