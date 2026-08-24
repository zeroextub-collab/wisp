"""
End-to-end wiring tests for Kimi K3's hybrid backbone.

These cover the two pieces that used to be missing — the converter
mapping KDA projections, and the C engine having a per-layer KDA branch —
plus the removal of the July-27 date guard.

What they deliberately do NOT claim: that K3 produces correct output.
No K3 checkpoint has been converted with this code, and the KDA tensor
names are inferred rather than verified. These tests prove the plumbing
is connected and self-consistent, not that the model runs.
"""

from __future__ import annotations

import json

import pytest
import torch
from safetensors.torch import save_file

from wisp.converter.manifest import ModelManifest
from wisp.converter.partitioner import Partitioner
from wisp.models.registry import get_adapter
from wisp.runtime.kda_layer import KDALayer

try:
    import wisp._wisp_core as _core
    HAS_ENGINE = True
except (ImportError, OSError):
    _core = None
    HAS_ENGINE = False


# --------------------------------------------------------------------------
# Layer typing agrees between adapter, runtime and the confirmed report
# --------------------------------------------------------------------------

def test_adapter_and_runtime_agree_on_layer_types():
    """The converter and the engine must never disagree about which
    layers are KDA — they share one definition."""
    a = get_adapter("kimi-k3")
    for i in range(a.num_layers):
        assert a.is_kda_layer(i) == KDALayer.is_kda_layer(i, a.num_layers)
    kda = sum(a.is_kda_layer(i) for i in range(a.num_layers))
    assert kda == 69                      # arXiv:2607.24653
    assert a.num_layers - kda == 24
    assert a.layer_type(0) == "kda"
    assert a.layer_type(3) == "gated_mla"
    assert a.layer_type(a.num_layers - 1) == "gated_mla"


def test_kda_tensor_names_map_to_canonical_dense():
    a = get_adapter("kimi-k3")
    # KDA layer -> kda.* namespace
    assert a.canonical_dense_name(
        "model.layers.0.attention.beta.weight") == "layers.0.kda.beta"
    assert a.canonical_dense_name(
        "model.layers.0.attention.wq_b.weight") == "layers.0.kda.gate"
    # An MLA layer keeps the ordinary attention mapping
    assert a.canonical_dense_name(
        "model.layers.3.self_attn.q_proj.weight") == "layers.3.attn.q_proj"
    # Unknown leaves are not silently swallowed
    assert a.canonical_dense_name(
        "model.layers.0.attention.nonsense.weight") is None


# --------------------------------------------------------------------------
# TASK 1 — converter maps KDA weights and records them in the manifest
# --------------------------------------------------------------------------

def test_kimi_k3_converter_maps_kda_weights(tmp_path):
    """Run the real Partitioner over a synthetic K3-shaped shard and
    confirm KDA projections land in the dense file and the manifest."""
    adapter = get_adapter("kimi-k3")
    src = tmp_path / "src"
    out = tmp_path / "out"
    src.mkdir()

    hidden = 32
    tensors = {
        "model.embed_tokens.weight": torch.zeros(8, hidden, dtype=torch.float16),
        "model.norm.weight": torch.ones(hidden, dtype=torch.float16),
        "lm_head.weight": torch.zeros(8, hidden, dtype=torch.float16),
    }
    # layer 0 = KDA, layer 3 = Gated MLA
    for leaf in ("q_proj", "k_proj", "v_proj", "o_proj", "beta", "gate"):
        tensors[f"model.layers.0.attention.{leaf}.weight"] = \
            torch.randn(hidden, hidden, dtype=torch.float16)
    tensors["model.layers.3.self_attn.q_proj.weight"] = \
        torch.randn(hidden, hidden, dtype=torch.float16)
    for layer in (0, 3):
        tensors[f"model.layers.{layer}.input_layernorm.weight"] = \
            torch.ones(hidden, dtype=torch.float16)
        tensors[f"model.layers.{layer}.post_attention_layernorm.weight"] = \
            torch.ones(hidden, dtype=torch.float16)
        tensors[f"model.layers.{layer}.mlp.gate.weight"] = \
            torch.randn(4, hidden, dtype=torch.float16)
        for e in range(2):
            for proj in ("gate_proj", "up_proj", "down_proj"):
                tensors[
                    f"model.layers.{layer}.mlp.experts.{e}.{proj}.weight"
                ] = torch.randn(8, hidden, dtype=torch.float16)
    save_file(tensors, str(src / "model-00001-of-00001.safetensors"))
    (src / "tokenizer.json").write_text(json.dumps({"version": "t"}))

    manifest = Partitioner(adapter, src, out, group_size=16).run()

    # KDA projections went into the dense file, under kda.* names
    from safetensors import safe_open
    with safe_open(str(out / "dense" / "model_dense.safetensors"),
                   framework="pt") as f:
        keys = set(f.keys())
    assert "layers.0.kda.beta" in keys
    assert "layers.0.kda.gate" in keys
    assert "layers.0.kda.q_proj" in keys
    # The MLA layer did NOT get a kda namespace
    assert not any(k.startswith("layers.3.kda.") for k in keys)

    # ...and the manifest advertises where they live and which layers
    saved = json.loads((out / "manifest.json").read_text(encoding="utf-8"))
    assert "kda_weights_dir" in saved["files"]
    kda = saved["architecture"]["kda"]
    assert kda["enabled"] is True
    assert kda["num_kda_layers"] == 69
    assert kda["num_mla_layers"] == 24
    assert 0 in kda["kda_layer_indices"]
    assert 3 not in kda["kda_layer_indices"]
    # Honest about provenance
    assert kda["tensor_names_verified"] is False
    assert manifest.files["kda_weights_dir"]


def test_manifest_roundtrip_preserves_kda_block(tmp_path):
    ModelManifest.build(get_adapter("kimi-k3"), quant_dtype="int4",
                        group_size=64).save(tmp_path)
    loaded = ModelManifest.load(tmp_path)
    assert loaded.architecture["kda"]["num_kda_layers"] == 69
    assert loaded.files["kda_weights_dir"] == "dense/"


def test_non_hybrid_models_have_no_kda_block(tmp_path):
    """Adding hybrid support must not change other families' manifests."""
    ModelManifest.build(get_adapter("glm-5.2"), quant_dtype="int4",
                        group_size=64).save(tmp_path)
    loaded = ModelManifest.load(tmp_path)
    assert "kda" not in loaded.architecture


# --------------------------------------------------------------------------
# TASK 2 — the C engine has a per-layer KDA branch
# --------------------------------------------------------------------------

def test_kimi_k3_c_layer_config_has_kda_flag():
    """The per-layer struct carries the KDA flag, slot index, and the two
    extra projection pointers the recurrence needs."""
    header = (pytest.importorskip("pathlib").Path("csrc/core/wisp_engine.h")
              .read_text(encoding="utf-8"))
    for field in ("int is_kda_layer;", "int kda_slot;",
                  "wisp_half* kda_beta;", "wisp_half* kda_gate;"):
        assert field in header, f"missing {field} in WispLayerWeights"
    # Engine-level state pool
    for field in ("float* kda_state;", "int    kda_layer_count;"):
        assert field in header, f"missing {field} in WispEngine"


def test_c_forward_pass_branches_on_kda():
    from pathlib import Path
    src = Path("csrc/core/wisp_engine.c").read_text(encoding="utf-8")
    assert "run_kda_attention" in src
    # The branch must be inside run_attention, before the MLA/GQA split
    assert "if (w->is_kda_layer" in src
    # State must reset with the KV cache or history leaks between chats
    idx = src.index("void wisp_kv_cache_clear")
    assert "wisp_kda_reset_state" in src[idx:idx + 900]


@pytest.mark.engine
@pytest.mark.skipif(not HAS_ENGINE, reason="C engine not available in CI")
def test_kda_kernel_still_self_tests_after_wiring():
    """The recurrence must still be numerically right after the engine
    integration — this is the same on-device check as test_kda.py."""
    if not hasattr(_core, "_selftest_kda"):
        pytest.skip("CPU-only build — no CUDA KDA kernel")
    assert _core._selftest_kda() is True


# --------------------------------------------------------------------------
# TASK 3 — the date guard is gone
# --------------------------------------------------------------------------

def test_kimi_k3_date_guard_removed():
    """`wisp info --model kimi-k3` must not mention being blocked or a
    release date — those have passed."""
    from click.testing import CliRunner
    from wisp.cli import main

    result = CliRunner().invoke(main, ["info", "--model", "kimi-k3"])
    assert result.exit_code == 0, result.output
    lowered = result.output.lower()
    for banned in ("blocked", "july 27", "unlocks", "drop july"):
        assert banned not in lowered, f"stale guard text: {banned!r}"


def test_kimi_k3_convert_not_calendar_blocked(tmp_path):
    from click.testing import CliRunner
    from wisp.cli import main

    result = CliRunner().invoke(
        main, ["convert", "--model", "kimi-k3", "--output", str(tmp_path)])
    assert "July 27" not in result.output
