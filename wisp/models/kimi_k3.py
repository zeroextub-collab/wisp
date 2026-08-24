"""
wisp.models.kimi_k3 — Kimi K3
(2.8T total / 104B active, hybrid KDA + Gated MLA, 93 layers,
896 experts/layer, top-16 routing, 1,048,576-token context).

CONFIRMED — official technical report, arXiv:2607.24653
("Kimi K3: Open Frontier Intelligence", Moonshot AI, July 2026):

  - 2.8 trillion total parameters, 104B activated per token (104.2B)
  - 896 routed experts per layer, 16 active per token
  - 2 shared experts (always active)
  - 93 layers = 69 KDA + 24 Gated MLA
        23 blocks of [3x KDA + 1x Gated MLA], plus one final Gated MLA
        so the last layer is always global attention.
        -> 75% KDA layers, 25% Gated MLA layers (69/93 = 74%, 24/93 = 26%)
  - hidden size 7,168 (router projects to a 3,584 latent before dispatch)
  - 1,048,576-token context window
  - Stable LatentMoE routing

  Expert lookups per token: 16 x 93 = 1,488.

  TWO SPARSITY NUMBERS, both correct, often confused:
    56x at the EXPERT level    (896 experts / 16 active)
    27x at the PARAMETER level (2.8T total / 104B active)
  They differ because the dense path — attention, embeddings, the 2
  shared experts — runs for every token regardless of routing.

STILL ESTIMATED (not published in the report):
  - expert size int4 ~17.5 MB (derived: hidden 7168 is identical to
    GLM-5.2's, and 83,328 experts at that size reproduces Moonshot's
    published ~1.4 TB int4 footprint)
  - dense ~12 GB; vocab 160,000

WHAT THIS MEANS FOR WISP
  The hybrid attention is the interesting part. 24 of 93 layers are
  Gated MLA with a compressed latent KV — which is exactly the absorbed
  MLA path WISP already implements for GLM-5.2 and DeepSeek. Only the
  69 KDA layers need genuinely new work. KDA keeps a constant-size
  recurrent state instead of a growing KV cache, so K3's memory profile
  at 1M context should be *better* than a pure-MLA model of the same
  depth once implemented.

# TODO: Implement the KDA (Kimi Delta Attention) forward pass.
# Architecture is now confirmed (arXiv:2607.24653): linear attention
# with a constant-size recurrent state, interleaved 3:1 with Gated MLA.
# Until the kernel lands, the engine routes ALL K3 layers through its
# GQA path as a placeholder — K3 will not produce correct output yet.
# The 24 Gated MLA layers can move to WISP's existing absorbed-MLA
# path first; that is the cheaper half of the work.

# TODO: Implement Stable LatentMoE routing (Quantile Balancing).
# The report confirms the router projects each token to a 3,584-dim
# latent (half of hidden) before expert dispatch, replacing standard
# top-K softmax gating. Standard top-K is used as a placeholder.
"""

from __future__ import annotations

from pathlib import Path

from .base_adapter import ModelAdapter
from . import constants as C


class KimiK3Adapter(ModelAdapter):

    # Hybrid attention layout (CONFIRMED — arXiv:2607.24653)
    num_kda_layers = 69           # 74% of the backbone — linear attention
    num_mla_layers = 24           # 26% — global attention, compressed KV
    attention_block_ratio = "3:1"  # 3 KDA per 1 Gated MLA, + 1 final MLA
    router_latent_dim = 3584      # half of hidden; Stable LatentMoE

    @property
    def name(self) -> str: return "Kimi-K3"

    @property
    def family(self) -> str: return "kimi_k3"

    @property
    def hf_model_id(self) -> str:
        return C.HF_MODEL_ID["kimi_k3"]

    @property
    def total_parameters(self) -> int:
        return C.TOTAL_PARAMETERS["kimi_k3"]          # CONFIRMED: 2.8T

    @property
    def active_parameters_per_token(self) -> int:
        # CONFIRMED: 104B (104.2B) activated per token — 27x parameter
        # sparsity. Our pre-report estimate said ~50B; the real figure is
        # roughly double, because 2 shared experts and the full attention
        # stack run on every token.
        return C.ACTIVE_PARAMETERS["kimi_k3"]

    @property
    def num_layers(self) -> int:
        # CONFIRMED: 93 (69 KDA + 24 Gated MLA). Pre-report estimate: 94.
        return C.NUM_LAYERS["kimi_k3"]

    @property
    def num_experts_per_layer(self) -> int:
        return C.NUM_EXPERTS_PER_LAYER["kimi_k3"]     # CONFIRMED: 896

    @property
    def num_shared_experts(self) -> int:
        return C.NUM_SHARED_EXPERTS["kimi_k3"]        # CONFIRMED: 2

    @property
    def top_k_routing(self) -> int:
        return C.TOP_K_ROUTING["kimi_k3"]             # CONFIRMED: 16

    @property
    def expert_size_bytes(self) -> int:
        return C.EXPERT_SIZE_INT4["kimi_k3"]          # derived ~17.5 MB

    @property
    def dense_layer_size_bytes(self) -> int:
        return C.DENSE_SIZE["kimi_k3"]                # estimated ~12 GB

    @property
    def hidden_size(self) -> int:
        return C.HIDDEN_SIZE["kimi_k3"]               # CONFIRMED: 7168

    @property
    def attention_type(self) -> str:
        # "KDA" selects the hybrid family. The engine currently maps it
        # onto its GQA forward pass as a placeholder — see the TODOs in
        # this module's docstring.
        return C.ATTENTION_TYPE["kimi_k3"]

    @property
    def attention_pattern(self) -> str:
        # CONFIRMED: 75% KDA layers, 25% Gated MLA layers, interleaved
        # 3:1 with a final global-attention layer.
        return C.ATTENTION_PATTERN["kimi_k3"]

    @property
    def vocab_size(self) -> int: return C.VOCAB_SIZE["kimi_k3"]

    @property
    def has_native_mtp(self) -> bool: return False

    @property
    def drafter_hf_id(self) -> str:
        return C.DRAFTER_HF_ID["kimi_k3"]             # moonshotai/Kimi-K2

    @property
    def default_acceptance_rate(self) -> float:
        return C.DEFAULT_ACCEPTANCE_RATE["kimi_k3"]   # 0.42

    @property
    def mtp_k(self) -> int:
        return 3

    # ------------------------------------------------------------------ #
    # Hybrid layer dispatch
    # ------------------------------------------------------------------ #
    def layer_type(self, layer_idx: int) -> str:
        """
        "kda" or "gated_mla" for a given layer.

        23 blocks of [KDA, KDA, KDA, Gated MLA] plus one final Gated MLA,
        so the last layer is always global attention: 69 KDA + 24 MLA
        over 93 layers (CONFIRMED, arXiv:2607.24653). Shares its
        definition with wisp.runtime.kda_layer.KDALayer.is_kda_layer so
        the converter and the runtime can never disagree.
        """
        from ..runtime.kda_layer import KDALayer
        return ("kda" if KDALayer.is_kda_layer(layer_idx, self.num_layers)
                else "gated_mla")

    def is_kda_layer(self, layer_idx: int) -> bool:
        return self.layer_type(layer_idx) == "kda"

    # Projections a KDA layer needs beyond the usual q/k/v/o. `beta` is
    # the per-channel decay of the delta rule, `gate` the SiLU output
    # gate. See wisp/runtime/kda_layer.py for the recurrence itself.
    #
    # WARNING — these tensor names are NOT verified against released
    # weights. The technical report describes the mechanism, not the
    # checkpoint layout, and no K3 checkpoint has been converted with
    # this code yet. The three layers of defence, in order:
    #   1. kda_module_names x kda_tensor_aliases — a wide net over the
    #      spellings published linear-attention checkpoints actually use.
    #   2. $WISP_KDA_NAMES — an explicit map, so a user whose checkpoint
    #      falls outside the net converts without patching WISP.
    #   3. `wisp inspect` prints the real names and marks what matched,
    #      and `wisp convert` reports its match count and refuses to be
    #      quiet about a shortfall.
    # An unmatched projection silently drops that layer onto the GQA
    # path, so the failure mode is a model that loads, verifies, and
    # generates nonsense. Everything here exists to make that loud.
    kda_projection_names = ("q_proj", "k_proj", "v_proj", "o_proj",
                            "beta", "gate")

    # Every spelling seen across published linear-attention checkpoints
    # (DeltaNet, GLA, Gated DeltaNet, RWKV-family, Mamba-style mixers).
    # Matching is case-insensitive and ignores a leading "w"/"W".
    kda_tensor_aliases = {
        "q_proj": ("q_proj", "wq", "wq_a", "q_a_proj", "query_proj",
                   "q", "to_q"),
        "k_proj": ("k_proj", "wk", "wk_a", "k_a_proj", "key_proj",
                   "k", "to_k"),
        "v_proj": ("v_proj", "wv", "wv_a", "v_a_proj", "value_proj",
                   "v", "to_v"),
        "o_proj": ("o_proj", "wo", "out_proj", "output_proj", "proj_out",
                   "to_out", "dense"),
        "beta": ("beta", "beta_proj", "b_proj", "k_b", "decay_proj",
                 "decay", "a_proj", "alpha_proj", "forget_proj",
                 "f_proj", "dt_proj", "w_beta"),
        "gate": ("gate", "gate_proj", "g_proj", "wq_b", "output_gate",
                 "out_gate", "g", "to_gate"),
    }

    # The module that holds them. K3's own name is unknown; these are the
    # names linear-attention blocks actually ship under.
    kda_module_names = ("attention", "self_attn", "attn", "linear_attn",
                        "linear_attention", "kda", "mixer", "token_mixer",
                        "delta_net", "deltanet", "seq_mixer")

    @classmethod
    def kda_name_overrides(cls) -> dict:
        """User-supplied name map, from $WISP_KDA_NAMES.

        The escape hatch for the case this adapter cannot guess: when the
        real checkpoint spells its projections in a way none of the
        aliases above cover, a user can convert without patching WISP.
        Accepts inline JSON or a path to a JSON file, mapping canonical
        name -> checkpoint leaf name:

            WISP_KDA_NAMES='{"beta": "w_decay", "gate": "w_gate"}'

        `wisp inspect <model_dir>` prints the leaf names actually present,
        which is where the right-hand side comes from.
        """
        import json
        import os
        raw = os.environ.get("WISP_KDA_NAMES", "").strip()
        if not raw:
            return {}
        try:
            if not raw.startswith("{"):
                raw = Path(raw).read_text(encoding="utf-8")
            mapping = json.loads(raw)
            if not isinstance(mapping, dict):
                raise ValueError("expected a JSON object")
            unknown = set(mapping) - set(cls.kda_projection_names)
            if unknown:
                raise ValueError(
                    f"unknown KDA projection(s) {sorted(unknown)}; "
                    f"valid keys: {list(cls.kda_projection_names)}")
            return {k: str(v) for k, v in mapping.items()}
        except Exception as e:
            raise ValueError(
                f"WISP_KDA_NAMES is not usable: {e}") from e

    def canonical_dense_name(self, hf_name: str) -> str | None:
        """
        Map a K3 checkpoint tensor onto WISP's canonical dense layout.

        KDA projections are DENSE weights — resident per layer, like any
        attention matrix — so they ride in dense/model_dense.safetensors
        beside everything else rather than in a parallel directory. That
        keeps one loader, one file, one format.

        Matching is deliberately generous: an unmatched KDA projection
        does not fail loudly at load time, it silently drops the layer
        onto the GQA path and produces fluent nonsense. Better to accept
        a name that turns out to be something else — that shows up as a
        shape mismatch, which is loud.
        """
        import re as _re
        m = _re.match(
            r"model\.layers\.(\d+)\.([A-Za-z_0-9]+)\.(.+?)"
            r"(?:\.weight)?$", hf_name)
        if not m:
            return super().canonical_dense_name(hf_name)

        layer, module, leaf = int(m.group(1)), m.group(2), m.group(3)
        if (module.lower() not in self.kda_module_names
                or not self.is_kda_layer(layer)):
            return super().canonical_dense_name(hf_name)

        canonical = self._match_kda_leaf(leaf)
        if canonical:
            return f"layers.{layer}.kda.{canonical}"
        return super().canonical_dense_name(hf_name)

    @classmethod
    def _match_kda_leaf(cls, leaf: str) -> str | None:
        """Canonical projection name for a checkpoint leaf, or None.

        Order matters: an explicit override always wins, so a user can
        correct a wrong guess as well as supply a missing one."""
        overrides = cls.kda_name_overrides()
        norm = leaf.lower().strip(". ")
        for canonical, want in overrides.items():
            if norm == want.lower().strip(". "):
                return canonical
        # Overridden projections are claimed by the override alone —
        # otherwise an alias could re-match the name the user replaced.
        for canonical, aliases in cls.kda_tensor_aliases.items():
            if canonical in overrides:
                continue
            for alias in aliases:
                if norm == alias or norm == "w" + alias:
                    return canonical
        return None

    def manifest_extras(self) -> dict:
        """Recorded in manifest.json so the engine knows, per layer,
        which attention path to take without re-deriving the pattern."""
        return {
            "kda": {
                "enabled": True,
                "pattern": "3x KDA + 1x GatedMLA, final layer always MLA",
                "num_kda_layers": self.num_kda_layers,
                "num_mla_layers": self.num_mla_layers,
                "kda_layer_indices": [i for i in range(self.num_layers)
                                      if self.is_kda_layer(i)],
                "projections": list(self.kda_projection_names),
                "router_latent_dim": self.router_latent_dim,
                "tensor_names_verified": False,
            }
        }

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
