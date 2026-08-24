"""
wisp.converter.manifest — manifest.json read/write for converted models.

Every converted model directory carries a manifest describing architecture,
quantization, file layout, and performance constants. The Python runtime and
the C engine both parse this file — keep the schema stable.
"""

from __future__ import annotations

import json
from dataclasses import dataclass, field
from datetime import datetime, timezone
from pathlib import Path

from ..models.base_adapter import ModelAdapter

WISP_VERSION = "2.0.0"
MANIFEST_FILENAME = "manifest.json"
EXPERT_NAMING = "L{layer:03d}_E{expert:05d}.bin"


@dataclass
class ModelManifest:
    wisp_version:   str
    model_family:   str
    model_name:     str
    hf_model_id:    str
    total_parameters: int
    architecture:   dict
    quantization:   dict
    performance:    dict
    files:          dict
    mtp:            dict
    drafter:        dict
    created_at:     str = field(
        default_factory=lambda: datetime.now(timezone.utc)
        .strftime("%Y-%m-%dT%H:%M:%SZ"))
    wisp_convert_version: str = WISP_VERSION

    # ------------------------------------------------------------------ #
    def to_dict(self) -> dict:
        return {
            "wisp_version":         self.wisp_version,
            "model_family":         self.model_family,
            "model_name":           self.model_name,
            "hf_model_id":          self.hf_model_id,
            "total_parameters":     self.total_parameters,
            "architecture":         self.architecture,
            "quantization":         self.quantization,
            "performance":          self.performance,
            "files":                self.files,
            "mtp":                  self.mtp,
            "drafter":              self.drafter,
            "created_at":           self.created_at,
            "wisp_convert_version": self.wisp_convert_version,
        }

    def save(self, model_dir: str | Path) -> Path:
        path = Path(model_dir) / MANIFEST_FILENAME
        tmp = path.with_suffix(".json.tmp")
        with open(tmp, "w", encoding="utf-8") as f:
            json.dump(self.to_dict(), f, indent=2)
        tmp.replace(path)
        return path

    # ------------------------------------------------------------------ #
    @classmethod
    def load(cls, model_dir: str | Path) -> "ModelManifest":
        path = Path(model_dir) / MANIFEST_FILENAME
        if not path.exists():
            raise FileNotFoundError(
                f"No {MANIFEST_FILENAME} in {model_dir} — run `wisp convert` first."
            )
        with open(path, encoding="utf-8") as f:
            d = json.load(f)
        required = ("model_family", "architecture", "quantization",
                    "performance", "files")
        missing = [k for k in required if k not in d]
        if missing:
            raise ValueError(
                f"Corrupt manifest at {path}: missing fields {missing}"
            )
        return cls(
            wisp_version         = d.get("wisp_version", WISP_VERSION),
            model_family         = d["model_family"],
            model_name           = d.get("model_name", d["model_family"]),
            hf_model_id          = d.get("hf_model_id", ""),
            total_parameters     = d.get("total_parameters", 0),
            architecture         = d["architecture"],
            quantization         = d["quantization"],
            performance          = d["performance"],
            files                = d["files"],
            mtp                  = d.get("mtp", {"available": False}),
            drafter              = d.get("drafter", {}),
            created_at           = d.get("created_at", ""),
            wisp_convert_version = d.get("wisp_convert_version", WISP_VERSION),
        )

    # ------------------------------------------------------------------ #
    @classmethod
    def build(cls, adapter: ModelAdapter, *,
              quant_dtype: str, group_size: int,
              architecture_extra: dict | None = None,
              mtp_available: bool | None = None) -> "ModelManifest":
        """Construct a manifest from an adapter + conversion settings."""
        extras = {}
        if hasattr(adapter, "manifest_extras"):
            extras = adapter.manifest_extras() or {}

        arch = {
            "attention_type":                 adapter.attention_type,
            "num_layers":                     adapter.num_layers,
            "num_experts_per_layer":          adapter.num_experts_per_layer,
            "num_shared_experts":             adapter.num_shared_experts,
            "top_k_routing":                  adapter.top_k_routing,
            "total_expert_lookups_per_token": adapter.total_expert_lookups_per_token,
            "hidden_size":                    adapter.hidden_size,
            "vocab_size":                     adapter.vocab_size,
        }
        if architecture_extra:
            arch.update(architecture_extra)
        arch.update(extras)

        drafter_cfg = adapter.get_drafter_config()
        native = adapter.has_native_mtp if mtp_available is None else mtp_available

        return cls(
            wisp_version     = WISP_VERSION,
            model_family     = adapter.family,
            model_name       = adapter.name,
            hf_model_id      = adapter.hf_model_id,
            total_parameters = adapter.total_parameters,
            architecture     = arch,
            quantization     = {
                "weight_dtype": quant_dtype,
                "scale_dtype":  "float16",
                "zero_dtype":   "float16",
                "group_size":   group_size,
            },
            performance      = {
                "expert_size_bytes":        adapter.expert_size_bytes,
                "dense_layer_size_bytes":   adapter.dense_layer_size_bytes,
                "total_expert_count":       adapter.total_expert_count,
                "bytes_per_token_all_cold": adapter.bytes_per_cold_token,
            },
            files            = {
                "dense_layers":  "dense/model_dense.safetensors",
                "expert_dir":    "experts/",
                "expert_naming": EXPERT_NAMING,
                "tokenizer_dir": "tokenizer/",
                "config":        "config.json",
                # Hybrid-attention families (Kimi K3) keep their KDA
                # projections here too: they are dense per-layer weights
                # like any attention matrix, so they ride in the same
                # safetensors file rather than a parallel directory.
                # One loader, one format.
                "kda_weights_dir": "dense/",
            },
            mtp              = {
                "available":       native,
                "type":            "native_int8" if native else "none",
                "file":            "mtp/mtp_head_int8.bin" if native else "",
                "draft_k":         adapter.mtp_k,
                "acceptance_rate": adapter.default_acceptance_rate,
            },
            drafter          = {
                "hf_id": drafter_cfg["hf_id"],
                "type":  drafter_cfg["type"],
            },
        )


def expert_filename(layer: int, expert: int) -> str:
    return EXPERT_NAMING.format(layer=layer, expert=expert)
