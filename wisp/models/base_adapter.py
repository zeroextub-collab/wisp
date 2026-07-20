"""
wisp.models.base_adapter
========================

One adapter per model family. Encapsulates everything model-specific so the
runtime is universal: architecture numbers, tokenizer handling, weight
loading, tensor-name mapping (HuggingFace -> wisp canonical), and drafter
selection.

The C engine never sees HF tensor names — the converter writes a canonical
layout (see `canonical_dense_name` / `expert_weight_pattern`) that every
family maps into. That is what makes the hot path model-agnostic.
"""

from __future__ import annotations

import json
import re
from abc import ABC, abstractmethod
from pathlib import Path

import torch
from tokenizers import Tokenizer as HFTokenizer


class ModelAdapter(ABC):
    """
    One adapter per model family.
    Encapsulates everything model-specific so the runtime is universal.
    """

    def __init__(self) -> None:
        self._tokenizer: HFTokenizer | None = None
        self._tokenizer_config: dict = {}
        self._dense: dict[str, torch.Tensor] = {}

    # ------------------------------------------------------------------ #
    # Identity
    # ------------------------------------------------------------------ #
    @property
    @abstractmethod
    def name(self) -> str: ...

    @property
    @abstractmethod
    def family(self) -> str:
        """Registry key, e.g. 'glm52'. Used for constants lookup + manifest."""
        ...

    @property
    @abstractmethod
    def hf_model_id(self) -> str: ...

    # ------------------------------------------------------------------ #
    # Architecture
    # ------------------------------------------------------------------ #
    @property
    @abstractmethod
    def total_parameters(self) -> int: ...

    @property
    @abstractmethod
    def num_layers(self) -> int: ...

    @property
    @abstractmethod
    def num_experts_per_layer(self) -> int: ...

    @property
    @abstractmethod
    def num_shared_experts(self) -> int: ...

    @property
    @abstractmethod
    def top_k_routing(self) -> int: ...

    @property
    def total_expert_count(self) -> int:
        return self.num_experts_per_layer * self.num_layers

    @property
    def total_expert_lookups_per_token(self) -> int:
        # CORRECT formula: top_k PER LAYER x num_layers
        return self.top_k_routing * self.num_layers

    @property
    @abstractmethod
    def expert_size_bytes(self) -> int: ...

    @property
    @abstractmethod
    def dense_layer_size_bytes(self) -> int: ...

    @property
    @abstractmethod
    def hidden_size(self) -> int: ...

    @property
    @abstractmethod
    def attention_type(self) -> str: ...  # "MLA" | "GQA" | "MHA"

    @property
    @abstractmethod
    def vocab_size(self) -> int: ...

    @property
    def bytes_per_cold_token(self) -> int:
        return self.expert_size_bytes * self.total_expert_lookups_per_token

    # ------------------------------------------------------------------ #
    # Speculative decoding
    # ------------------------------------------------------------------ #
    @property
    @abstractmethod
    def has_native_mtp(self) -> bool: ...

    @property
    @abstractmethod
    def drafter_hf_id(self) -> str: ...

    @property
    @abstractmethod
    def default_acceptance_rate(self) -> float: ...

    @property
    def mtp_k(self) -> int:
        return 3  # Default draft length; override per model if needed

    # ------------------------------------------------------------------ #
    # Tokenizer (shared implementation — HuggingFace `tokenizers` only)
    # ------------------------------------------------------------------ #
    def load_tokenizer(self, model_dir: Path) -> HFTokenizer:
        """
        Load tokenizer from converted model directory.
        Looks for: model_dir/tokenizer/tokenizer.json
        Falls back to: model_dir/tokenizer.json
        """
        model_dir = Path(model_dir)
        candidates = [
            model_dir / "tokenizer" / "tokenizer.json",
            model_dir / "tokenizer.json",
        ]
        for path in candidates:
            if path.exists():
                self._tokenizer = HFTokenizer.from_file(str(path))
                cfg_path = path.parent / "tokenizer_config.json"
                if cfg_path.exists():
                    with open(cfg_path, encoding="utf-8") as f:
                        self._tokenizer_config = json.load(f)
                return self._tokenizer
        raise FileNotFoundError(
            f"No tokenizer.json found under {model_dir} "
            f"(looked in tokenizer/ and model root). Run `wisp convert` first."
        )

    def _require_tokenizer(self) -> HFTokenizer:
        if self._tokenizer is None:
            raise RuntimeError(
                "Tokenizer not loaded — call adapter.load_tokenizer(model_dir) first."
            )
        return self._tokenizer

    def tokenize(self, text: str) -> list[int]:
        """
        Encode text to token IDs.
        Always prepend BOS token if model requires it.
        Never truncate — caller handles context length.
        """
        tok = self._require_tokenizer()
        ids = tok.encode(text, add_special_tokens=False).ids
        bos = self.bos_token_id
        if bos >= 0 and (not ids or ids[0] != bos):
            ids = [bos] + ids
        return ids

    def detokenize(self, token_ids: list[int]) -> str:
        """
        Decode token IDs to text.
        Skip special tokens (BOS, EOS, PAD) in output.
        Handle incomplete UTF-8 sequences gracefully (tokenizers replaces
        invalid partial sequences with U+FFFD; we strip trailing ones so a
        streaming caller can retry with more tokens).
        """
        tok = self._require_tokenizer()
        text = tok.decode(token_ids, skip_special_tokens=True)
        return text.rstrip("�")

    def _special_token_id(self, *names: str) -> int:
        tok = self._require_tokenizer()
        # 1. tokenizer_config.json declared specials
        for key in ("bos_token", "eos_token", "pad_token"):
            val = self._tokenizer_config.get(key)
            if isinstance(val, dict):
                val = val.get("content")
            if val:
                tid = tok.token_to_id(val)
                if tid is not None and any(n in key for n in names):
                    return tid
        # 2. common literal spellings
        for candidate in names:
            tid = tok.token_to_id(candidate)
            if tid is not None:
                return tid
        return -1

    @property
    def bos_token_id(self) -> int:
        return self._special_token_id("bos", "<s>", "<|begin_of_text|>", "[gMASK]", "<sop>")

    @property
    def eos_token_id(self) -> int:
        return self._special_token_id(
            "eos", "</s>", "<|end_of_text|>", "<|endoftext|>", "<|im_end|>", "<|eot_id|>"
        )

    # ------------------------------------------------------------------ #
    # Weight layout mapping (HF -> wisp canonical)
    # ------------------------------------------------------------------ #
    # Canonical dense names the converter writes and the C engine reads:
    #   embed_tokens, final_norm, lm_head
    #   layers.{i}.input_norm / post_norm / router / router_bias
    #   layers.{i}.attn.{q_proj,k_proj,v_proj,o_proj}                (GQA/MHA)
    #   layers.{i}.attn.{q_a_proj,q_a_norm,q_b_proj,
    #                    kv_a_proj,kv_a_norm,kv_b_proj,o_proj}       (MLA)
    #   layers.{i}.shared.{gate,up,down}
    #
    # Expert tensors match `expert_weight_pattern` and are packed into
    # experts/L{layer:03d}_E{expert:05d}.bin by the partitioner.

    @property
    def expert_weight_pattern(self) -> re.Pattern:
        """Regex with named groups: layer, expert, proj (gate|up|down)."""
        return re.compile(
            r"model\.layers\.(?P<layer>\d+)\.mlp\.experts\.(?P<expert>\d+)"
            r"\.(?P<proj>gate_proj|up_proj|down_proj)\.weight"
        )

    def normalize_expert_proj(self, proj: str) -> str:
        """
        Map a family-specific expert matrix name onto the canonical
        gate_proj / up_proj / down_proj trio the .bin format stores.
        Default families already use canonical names; Mixtral maps
        w1/w3/w2 here.
        """
        return proj

    # --- model-agnostic partitioning hooks ---------------------------- #
    def is_dense_tensor(self, key: str) -> bool:
        """True if a checkpoint tensor belongs to the dense layers
        (resident), False if it belongs to a routed expert (streamed)."""
        return self.expert_weight_pattern.match(key) is None

    def get_expert_key(self, layer_idx: int, expert_idx: int) -> list[str]:
        """The checkpoint tensor keys of one expert, in canonical
        gate/up/down order."""
        base = f"model.layers.{layer_idx}.mlp.experts.{expert_idx}"
        return [f"{base}.gate_proj.weight",
                f"{base}.up_proj.weight",
                f"{base}.down_proj.weight"]

    def get_router_key(self, layer_idx: int) -> str:
        """The checkpoint tensor key of a layer's router/gate matrix."""
        return f"model.layers.{layer_idx}.mlp.gate.weight"

    def canonical_dense_name(self, hf_name: str) -> str | None:
        """
        Map a HuggingFace tensor name to the wisp canonical dense name.
        Return None for tensors that are neither dense nor experts
        (e.g. rotary inv_freq buffers) — those are dropped.
        DeepSeek-style naming is the default; families override as needed.
        """
        n = hf_name
        simple = {
            "model.embed_tokens.weight": "embed_tokens",
            "model.norm.weight": "final_norm",
            "lm_head.weight": "lm_head",
        }
        if n in simple:
            return simple[n]

        m = re.match(r"model\.layers\.(\d+)\.(.+)", n)
        if not m:
            return None
        i, rest = m.group(1), m.group(2)
        table = {
            "input_layernorm.weight":                       f"layers.{i}.input_norm",
            "post_attention_layernorm.weight":              f"layers.{i}.post_norm",
            "mlp.gate.weight":                              f"layers.{i}.router",
            "mlp.gate.e_score_correction_bias":             f"layers.{i}.router_bias",
            "mlp.shared_experts.gate_proj.weight":          f"layers.{i}.shared.gate",
            "mlp.shared_experts.up_proj.weight":            f"layers.{i}.shared.up",
            "mlp.shared_experts.down_proj.weight":          f"layers.{i}.shared.down",
            # Dense-MLP early layers (DeepSeek V3 layer 0-2, GLM layer 0)
            "mlp.gate_proj.weight":                         f"layers.{i}.shared.gate",
            "mlp.up_proj.weight":                           f"layers.{i}.shared.up",
            "mlp.down_proj.weight":                         f"layers.{i}.shared.down",
            # MLA attention
            "self_attn.q_a_proj.weight":                    f"layers.{i}.attn.q_a_proj",
            "self_attn.q_a_layernorm.weight":               f"layers.{i}.attn.q_a_norm",
            "self_attn.q_b_proj.weight":                    f"layers.{i}.attn.q_b_proj",
            "self_attn.kv_a_proj_with_mqa.weight":          f"layers.{i}.attn.kv_a_proj",
            "self_attn.kv_a_layernorm.weight":              f"layers.{i}.attn.kv_a_norm",
            "self_attn.kv_b_proj.weight":                   f"layers.{i}.attn.kv_b_proj",
            # GQA/MHA attention
            "self_attn.q_proj.weight":                      f"layers.{i}.attn.q_proj",
            "self_attn.k_proj.weight":                      f"layers.{i}.attn.k_proj",
            "self_attn.v_proj.weight":                      f"layers.{i}.attn.v_proj",
            "self_attn.o_proj.weight":                      f"layers.{i}.attn.o_proj",
        }
        return table.get(rest)

    # ------------------------------------------------------------------ #
    # Weight loading (converted layout)
    # ------------------------------------------------------------------ #
    def load_dense_layers(self, model_dir: Path,
                          device: str) -> dict[str, torch.Tensor]:
        """Load canonical dense weights (fp16 safetensors) onto `device`."""
        from safetensors.torch import load_file

        path = Path(model_dir) / "dense" / "model_dense.safetensors"
        if not path.exists():
            raise FileNotFoundError(
                f"Dense weights not found at {path}. Run `wisp convert` first."
            )
        self._dense = load_file(str(path), device=device)
        return self._dense

    def load_expert_raw(self, model_dir: Path,
                        layer_idx: int,
                        expert_idx: int) -> bytes:
        """Read one packed expert blob exactly as stored on SSD."""
        path = (Path(model_dir) / "experts"
                / f"L{layer_idx:03d}_E{expert_idx:05d}.bin")
        if not path.exists():
            raise FileNotFoundError(
                f"Expert file missing: {path.name}\n"
                f"The model at {model_dir} may be corrupted or the "
                f"conversion was interrupted.\n"
                f"Check it:  wisp verify --model {model_dir}\n"
                f"Repair it: wisp convert --model {self.family} "
                f"--output {Path(model_dir).parent} (resumes)")
        return path.read_bytes()

    def router_forward(self,
                       hidden_states: torch.Tensor,
                       layer_idx: int = 0
                       ) -> tuple[torch.Tensor, list[int]]:
        """
        Python-side routing (used for prefetch prediction; the C engine has
        its own router kernel on the hot path).
        Returns (router_weights, selected_expert_indices).
        """
        key = f"layers.{layer_idx}.router"
        if key not in self._dense:
            raise RuntimeError(
                f"Router weights for layer {layer_idx} not loaded — "
                f"call load_dense_layers() first."
            )
        gate = self._dense[key].to(hidden_states.dtype)
        logits = hidden_states @ gate.T                      # [.., n_experts]
        bias_key = f"layers.{layer_idx}.router_bias"
        if bias_key in self._dense:
            logits = logits + self._dense[bias_key].to(logits.dtype)
        probs = torch.softmax(logits.float(), dim=-1)
        top_w, top_i = torch.topk(probs, self.top_k_routing, dim=-1)
        top_w = top_w / top_w.sum(dim=-1, keepdim=True)      # renormalize
        return top_w, top_i.flatten().tolist()

    # ------------------------------------------------------------------ #
    # Drafter
    # ------------------------------------------------------------------ #
    @abstractmethod
    def get_drafter_config(self) -> dict: ...
