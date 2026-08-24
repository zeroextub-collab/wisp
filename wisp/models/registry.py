"""
wisp.models.registry — model name / family -> adapter resolution.

Accepts CLI spellings ("glm-5.2"), family keys ("glm52"), and full HF ids.
"""

from __future__ import annotations

import json
from pathlib import Path

from .base_adapter import ModelAdapter
from .glm52 import GLM52Adapter
from .deepseek_v3 import DeepSeekV3Adapter
from .deepseek_r1 import DeepSeekR1Adapter
from .kimi_k3 import KimiK3Adapter
from .mixtral_8x7b import Mixtral8x7BAdapter
from .mixtral_8x22b import Mixtral8x22BAdapter
from .qwen3_moe import Qwen3MoEAdapter, Qwen3_2_4T_Adapter

_ADAPTERS: dict[str, type[ModelAdapter]] = {
    # family keys
    "glm52":         GLM52Adapter,
    "deepseek_v3":   DeepSeekV3Adapter,
    "deepseek_r1":   DeepSeekR1Adapter,
    "kimi_k3":       KimiK3Adapter,
    "mixtral_8x7b":  Mixtral8x7BAdapter,
    "mixtral_8x22b": Mixtral8x22BAdapter,
    "qwen3_235b":    Qwen3MoEAdapter,
    "qwen3_2_4t":    Qwen3_2_4T_Adapter,
    # CLI spellings
    "glm-5.2":       GLM52Adapter,
    "glm5.2":        GLM52Adapter,
    "deepseek-v3":   DeepSeekV3Adapter,
    "deepseek-r1":   DeepSeekR1Adapter,
    "kimi-k3":       KimiK3Adapter,
    "mixtral-8x7b":  Mixtral8x7BAdapter,
    "mixtral-8x22b": Mixtral8x22BAdapter,
    "qwen3-235b":       Qwen3MoEAdapter,
    "qwen3-235b-a22b":  Qwen3MoEAdapter,
    "qwen3-moe":        Qwen3MoEAdapter,
    "qwen3-2.4t":       Qwen3_2_4T_Adapter,
    "qwen3.8":          Qwen3_2_4T_Adapter,
    # HF ids
    "zai-org/glm-5.2":          GLM52Adapter,
    "deepseek-ai/deepseek-v3":  DeepSeekV3Adapter,
    "deepseek-ai/deepseek-r1":  DeepSeekR1Adapter,
    "moonshotai/kimi-k3":       KimiK3Adapter,
    "mistralai/mixtral-8x7b-instruct-v0.1":  Mixtral8x7BAdapter,
    "mistralai/mixtral-8x22b-instruct-v0.1": Mixtral8x22BAdapter,
    "qwen/qwen3-235b-a22b":                 Qwen3MoEAdapter,
    "qwen/qwen3-2.4t":                      Qwen3_2_4T_Adapter,
}


def supported_models() -> list[str]:
    return ["glm-5.2", "deepseek-v3", "deepseek-r1", "kimi-k3",
            "mixtral-8x7b", "mixtral-8x22b", "qwen3-235b", "qwen3-2.4t"]


def get_adapter(name: str) -> ModelAdapter:
    """Resolve a model name to a fresh adapter instance."""
    key = name.strip().lower()
    cls = _ADAPTERS.get(key)
    if cls is None:
        raise ValueError(
            f"Unknown model '{name}'. Supported: {', '.join(supported_models())}."
        )
    return cls()


def adapter_from_model_dir(model_dir: str | Path) -> ModelAdapter:
    """Resolve the adapter for an already-converted model directory."""
    manifest_path = Path(model_dir) / "manifest.json"
    if not manifest_path.exists():
        raise FileNotFoundError(
            f"No manifest.json in {model_dir} — not a converted wisp model. "
            f"Run `wisp convert` first."
        )
    with open(manifest_path, encoding="utf-8") as f:
        manifest = json.load(f)
    family = manifest.get("model_family")
    if not family:
        raise ValueError(f"manifest.json in {model_dir} has no model_family field.")
    return get_adapter(family)
