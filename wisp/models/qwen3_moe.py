"""
wisp.models.qwen3_moe — Qwen3 MoE family (235B-A22B and the 2.4T model).

One adapter serves both: the architecture is identical and only the
depth differs, so everything that varies is read from the checkpoint's
config.json at conversion time rather than hardcoded per size.

CONFIRMED for Qwen3-235B-A22B (verified against the published
config.json on the model repo, 2026-08):
    hidden_size            4096
    num_hidden_layers      94
    num_experts            128
    num_experts_per_tok    8       -> 94 x 8 = 752 lookups/token
    moe_intermediate_size  1536
    num_attention_heads    64
    num_key_value_heads    4       -> GQA, 16 query heads per KV head
    vocab_size             151936
    decoder_sparse_step    1  and  mlp_only_layers []  -> every layer is MoE

TWO CORRECTIONS worth recording, because both are easy to assume wrong:

  * Qwen3 MoE has NO shared expert. Qwen2-MoE had one
    (`shared_expert_gate` / `shared_expert_intermediate_size`); Qwen3
    dropped it, and the key is simply absent from the config. WISP
    therefore treats these as pure routed MoE, like Mixtral.
  * hidden_size is 4096, not 7168. 7168 is GLM-5.2 / Kimi K3.

Attention is ordinary GQA with a compressed-KV-free layout — the same
path Mixtral takes, NOT DeepSeek's absorbed MLA. Nothing here needs the
latent projections.

The 2.4T variant ("Qwen3.8") is the same architecture scaled deeper.
Its config is not published yet, so its constants are marked estimated
and `from_config()` will overwrite them from the real config.json the
moment weights land.
"""

from __future__ import annotations

import json
import re
from pathlib import Path

from .base_adapter import ModelAdapter
from . import constants as C


class Qwen3MoEAdapter(ModelAdapter):
    """Qwen3-235B-A22B by default; `from_config()` retargets it to any
    Qwen3 MoE checkpoint, including the 2.4T model."""

    # GQA geometry (overridden by from_config when a checkpoint is read)
    num_attention_heads = 64
    num_kv_heads = 4
    intermediate_size = 12288          # dense MLP width (non-MoE layers)
    moe_intermediate_size = 1536       # per-expert width
    max_position_embeddings = 32768
    _variant = "qwen3_235b"

    # ------------------------------------------------------------------ #
    # Config-driven construction
    # ------------------------------------------------------------------ #
    @classmethod
    def from_config(cls, config_path: str | Path) -> "Qwen3MoEAdapter":
        """
        Build an adapter from a checkpoint's config.json.

        Depth, expert count and routing all come from the file, which is
        what lets one class cover 235B and 2.4T without either being
        hardcoded. Missing keys keep the 235B defaults.
        """
        adapter = cls()
        path = Path(config_path)
        if path.is_dir():
            path = path / "config.json"
        if not path.exists():
            return adapter
        with open(path, encoding="utf-8") as f:
            cfg = json.load(f)
        adapter.apply_config(cfg)
        return adapter

    def apply_config(self, cfg: dict) -> None:
        """Overlay a parsed config.json onto this adapter instance."""
        self._cfg = dict(cfg)
        g = cfg.get
        self._num_layers = int(g("num_hidden_layers", self.num_layers))
        self._num_experts = int(g("num_experts",
                                  g("num_local_experts",
                                    self.num_experts_per_layer)))
        self._top_k = int(g("num_experts_per_tok", self.top_k_routing))
        self._hidden = int(g("hidden_size", self.hidden_size))
        self._vocab = int(g("vocab_size", self.vocab_size))
        self.num_attention_heads = int(g("num_attention_heads",
                                         self.num_attention_heads))
        self.num_kv_heads = int(g("num_key_value_heads", self.num_kv_heads))
        self.moe_intermediate_size = int(g("moe_intermediate_size",
                                           self.moe_intermediate_size))
        self.intermediate_size = int(g("intermediate_size",
                                       self.intermediate_size))
        self.max_position_embeddings = int(g("max_position_embeddings",
                                             self.max_position_embeddings))
        # Which layers are actually MoE: `mlp_only_layers` lists dense
        # ones, `decoder_sparse_step` thins them out. Both default to
        # "every layer is MoE" on Qwen3-235B.
        self._mlp_only_layers = set(g("mlp_only_layers", []) or [])
        self._sparse_step = int(g("decoder_sparse_step", 1) or 1)
        # Qwen3 dropped Qwen2-MoE's shared expert; trust the config.
        self._shared_experts = (
            1 if g("shared_expert_intermediate_size") else 0)

    def __init__(self):
        super().__init__()
        self._cfg: dict = {}
        self._num_layers = C.NUM_LAYERS["qwen3_235b"]
        self._num_experts = C.NUM_EXPERTS_PER_LAYER["qwen3_235b"]
        self._top_k = C.TOP_K_ROUTING["qwen3_235b"]
        self._hidden = C.HIDDEN_SIZE["qwen3_235b"]
        self._vocab = C.VOCAB_SIZE["qwen3_235b"]
        self._mlp_only_layers: set[int] = set()
        self._sparse_step = 1
        self._shared_experts = C.NUM_SHARED_EXPERTS["qwen3_235b"]

    # ------------------------------------------------------------------ #
    # Identity
    # ------------------------------------------------------------------ #
    @property
    def name(self) -> str:
        return ("Qwen3-2.4T" if self._variant == "qwen3_2_4t"
                else "Qwen3-235B-A22B")

    @property
    def family(self) -> str: return self._variant

    @property
    def hf_model_id(self) -> str: return C.HF_MODEL_ID[self._variant]

    @property
    def total_parameters(self) -> int:
        return C.TOTAL_PARAMETERS[self._variant]

    @property
    def num_layers(self) -> int: return self._num_layers

    @property
    def num_experts_per_layer(self) -> int: return self._num_experts

    @property
    def num_shared_experts(self) -> int:
        return self._shared_experts        # 0 — Qwen3 has no shared expert

    @property
    def top_k_routing(self) -> int: return self._top_k

    @property
    def hidden_size(self) -> int: return self._hidden

    @property
    def vocab_size(self) -> int: return self._vocab

    @property
    def attention_type(self) -> str:
        return "GQA"                       # not MLA — no latent KV

    @property
    def expert_size_bytes(self) -> int:
        """Derived from the actual shapes rather than a table: three
        [moe_intermediate, hidden] matrices at int4 plus fp16 scales and
        zeros, which is 0.5625 bytes per weight at group 64."""
        params = 3 * self.moe_intermediate_size * self.hidden_size
        return int(params * 0.5625) + 120  # + expert .bin header

    @property
    def dense_layer_size_bytes(self) -> int:
        return C.DENSE_SIZE[self._variant]

    @property
    def has_native_mtp(self) -> bool: return False

    @property
    def drafter_hf_id(self) -> str: return C.DRAFTER_HF_ID[self._variant]

    @property
    def default_acceptance_rate(self) -> float:
        return C.DEFAULT_ACCEPTANCE_RATE[self._variant]

    # ------------------------------------------------------------------ #
    # MoE layout
    # ------------------------------------------------------------------ #
    def is_moe_layer(self, layer_idx: int) -> bool:
        """Qwen3 can interleave dense MLP layers among the MoE ones. On
        235B every layer is MoE, but the rule is read from config so a
        future checkpoint that thins them out is handled."""
        if layer_idx in self._mlp_only_layers:
            return False
        step = max(self._sparse_step, 1)
        return (layer_idx % step) == 0

    @property
    def num_moe_layers(self) -> int:
        return sum(1 for i in range(self.num_layers) if self.is_moe_layer(i))

    @property
    def total_expert_count(self) -> int:
        return self.num_moe_layers * self.num_experts_per_layer

    @property
    def total_expert_lookups_per_token(self) -> int:
        """Only MoE layers route, so this counts them rather than every
        layer: 94 x 8 = 752 on Qwen3-235B, where all 94 are MoE."""
        return self.num_moe_layers * self.top_k_routing

    # ------------------------------------------------------------------ #
    # Tensor naming — standard HuggingFace Qwen3 layout
    # ------------------------------------------------------------------ #
    @property
    def expert_weight_pattern(self) -> re.Pattern:
        return re.compile(
            r"model\.layers\.(?P<layer>\d+)\.mlp\.experts\.(?P<expert>\d+)"
            r"\.(?P<proj>gate_proj|up_proj|down_proj)\.weight")

    def get_expert_key(self, layer_idx: int, expert_idx: int) -> list[str]:
        base = f"model.layers.{layer_idx}.mlp.experts.{expert_idx}"
        return [f"{base}.gate_proj.weight",
                f"{base}.up_proj.weight",
                f"{base}.down_proj.weight"]

    def get_router_key(self, layer_idx: int) -> str:
        return f"model.layers.{layer_idx}.mlp.gate.weight"

    def canonical_dense_name(self, hf_name: str) -> str | None:
        # Qwen3's shared expert exists only on older Qwen2-MoE
        # checkpoints; map it if present so such a model still converts.
        m = re.match(r"model\.layers\.(\d+)\.mlp\.shared_expert\."
                     r"(gate_proj|up_proj|down_proj)\.weight", hf_name)
        if m:
            leaf = {"gate_proj": "gate", "up_proj": "up",
                    "down_proj": "down"}[m.group(2)]
            return f"layers.{m.group(1)}.shared.{leaf}"
        return super().canonical_dense_name(hf_name)

    def get_drafter_config(self) -> dict:
        return {
            "type": "same_family",
            "hf_id": self.drafter_hf_id,
            "dtype": "int4",
            "k": self.mtp_k,
            "acceptance": self.default_acceptance_rate,
        }

    def manifest_extras(self) -> dict:
        return {
            "num_attention_heads": self.num_attention_heads,
            "num_kv_heads": self.num_kv_heads,
            "moe_intermediate_size": self.moe_intermediate_size,
            "num_moe_layers": self.num_moe_layers,
            "config_driven": True,
        }


class Qwen3_2_4T_Adapter(Qwen3MoEAdapter):
    """The 2.4T Qwen3 MoE ("Qwen3.8").

    Same architecture, greater depth. Its config.json is not public yet,
    so the constants here are ESTIMATED and `from_config()` replaces them
    with real values at conversion time.
    """

    _variant = "qwen3_2_4t"

    def __init__(self):
        super().__init__()
        self._num_layers = C.NUM_LAYERS["qwen3_2_4t"]
        self._num_experts = C.NUM_EXPERTS_PER_LAYER["qwen3_2_4t"]
        self._top_k = C.TOP_K_ROUTING["qwen3_2_4t"]
        self._hidden = C.HIDDEN_SIZE["qwen3_2_4t"]
        self._vocab = C.VOCAB_SIZE["qwen3_2_4t"]
        self._shared_experts = C.NUM_SHARED_EXPERTS["qwen3_2_4t"]
