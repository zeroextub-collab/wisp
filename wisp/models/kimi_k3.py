"""
wisp.models.kimi_k3 — Kimi K3 (2.8T, KDA hybrid linear attention,
896 experts/layer, top-16 routing, 1M-token context).

CONFIRMED (official Moonshot sources, July 2026):
  - 2.8 trillion total parameters
  - 896 experts per layer
  - top-16 routing (active experts per layer per token)
  - KDA (Kimi Delta Attention) hybrid linear attention
  - 1,000,000-token context window

ESTIMATED (until the technical report + weights drop July 27, 2026):
  - 94 layers  -> expert lookups per token = 16 x 94 = 1,504
  - expert size int4 ~21 MB; dense ~12 GB; disk ~1.4 TB int4
  - hidden 8192, vocab 160,000

# TODO: Replace with full KDA implementation
# once technical report publishes July 27, 2026
# KDA = hybrid linear attention, replaces quadratic attention
# in a subset of layers for 6.3x faster decoding at 1M context
# (until then the engine runs KDA layers as a GQA forward pass)

# TODO: Implement Quantile Balancing router
# once technical report publishes July 27, 2026
# K3 uses Stable LatentMoE with Quantile Balancing for routing,
# which replaces standard top-K softmax routing.
# Standard top-K routing used as placeholder
"""

from __future__ import annotations

from .base_adapter import ModelAdapter
from . import constants as C


class KimiK3Adapter(ModelAdapter):

    @property
    def name(self) -> str: return "Kimi-K3"

    @property
    def family(self) -> str: return "kimi_k3"

    @property
    def hf_model_id(self) -> str:
        return C.HF_MODEL_ID["kimi_k3"]     # anticipated HF repo

    @property
    def total_parameters(self) -> int: return C.TOTAL_PARAMETERS["kimi_k3"]

    @property
    def num_layers(self) -> int:
        return C.NUM_LAYERS["kimi_k3"]      # ESTIMATED — update July 27

    @property
    def num_experts_per_layer(self) -> int:
        return C.NUM_EXPERTS_PER_LAYER["kimi_k3"]   # CONFIRMED: 896

    @property
    def num_shared_experts(self) -> int:
        return C.NUM_SHARED_EXPERTS["kimi_k3"]      # estimated

    @property
    def top_k_routing(self) -> int:
        return C.TOP_K_ROUTING["kimi_k3"]           # CONFIRMED: 16

    @property
    def expert_size_bytes(self) -> int:
        return C.EXPERT_SIZE_INT4["kimi_k3"]        # estimated ~21 MB

    @property
    def dense_layer_size_bytes(self) -> int:
        return C.DENSE_SIZE["kimi_k3"]              # estimated ~12 GB

    @property
    def hidden_size(self) -> int: return C.HIDDEN_SIZE["kimi_k3"]

    @property
    def attention_type(self) -> str:
        # CONFIRMED: KDA. The engine maps "KDA" onto its GQA forward pass
        # as a placeholder until the July 27 technical report.
        return C.ATTENTION_TYPE["kimi_k3"]

    @property
    def vocab_size(self) -> int: return C.VOCAB_SIZE["kimi_k3"]

    @property
    def has_native_mtp(self) -> bool: return False

    @property
    def drafter_hf_id(self) -> str:
        return C.DRAFTER_HF_ID["kimi_k3"]           # moonshotai/Kimi-K2

    @property
    def default_acceptance_rate(self) -> float:
        return C.DEFAULT_ACCEPTANCE_RATE["kimi_k3"]  # 0.42

    @property
    def mtp_k(self) -> int:
        return 3

    def get_drafter_config(self) -> dict:
        # Kimi K2 as same-family drafter via the dense drafter path
        # (same fallback machinery as the DeepSeek distill drafters).
        return {
            "type": "same_family",
            "hf_id": self.drafter_hf_id,
            "dtype": "int4",
            "k": self.mtp_k,
            "acceptance": self.default_acceptance_rate,
        }
