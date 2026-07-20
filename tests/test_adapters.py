"""
Tests for model adapters, the registry, the critical expert-lookup math,
and the int4 quantization bit-format contract (Python pack <-> C unpack).
"""

import struct

import pytest
import torch

from wisp.converter.manifest import ModelManifest, expert_filename
from wisp.converter.partitioner import (EXPERT_HEADER, EXPERT_MAGIC,
                                        EXPERT_MAT_HEADER, write_expert_file)
from wisp.converter.quantizer import (dequantize_int4, quantization_error,
                                      quantize_int4)
from wisp.models.registry import (adapter_from_model_dir, get_adapter,
                                  supported_models)

# The compiled C engine is optional: it is absent in CI (and on any
# machine that hasn't run `pip install -e .`), and on Windows it can be
# present-but-unloadable when an OS application-control policy blocks
# unsigned DLLs — that surfaces as OSError, not ImportError.
try:
    import wisp._wisp_core as _core
    HAS_ENGINE = True
except (ImportError, OSError):
    _core = None
    HAS_ENGINE = False


# --------------------------------------------------------------------------
# The critical math — get this wrong and every estimate is wrong
# --------------------------------------------------------------------------

def test_glm52_expert_lookup_math():
    a = get_adapter("glm-5.2")
    assert a.top_k_routing == 8
    assert a.num_layers == 61
    assert a.total_expert_lookups_per_token == 488          # 8 x 61
    assert a.expert_size_bytes == 18_350_080
    assert a.bytes_per_cold_token == 18_350_080 * 488       # ~8.54 GB
    assert a.total_expert_count == 256 * 61                 # 15,616


def test_deepseek_lookup_math():
    for name in ("deepseek-v3", "deepseek-r1"):
        a = get_adapter(name)
        assert a.top_k_routing == 8
        assert a.num_layers == 58
        assert a.total_expert_lookups_per_token == 464      # 8 x 58


def test_adapter_identities():
    glm = get_adapter("glm-5.2")
    assert glm.name == "GLM-5.2"
    assert glm.attention_type == "MLA"
    assert glm.has_native_mtp is True
    assert glm.get_drafter_config()["type"] == "native_mtp"

    v3 = get_adapter("deepseek-v3")
    r1 = get_adapter("deepseek-r1")
    assert v3.name == "DeepSeek-V3"
    assert r1.name == "DeepSeek-R1"
    assert v3.drafter_hf_id == r1.drafter_hf_id            # shared drafter
    assert r1.get_drafter_config()["type"] == "same_family"


def test_kimi_k3_confirmed_architecture():
    a = get_adapter("kimi-k3")
    assert a.name == "Kimi-K3"
    assert a.total_parameters == 2_800_000_000_000
    assert a.num_experts_per_layer == 896          # CONFIRMED
    assert a.top_k_routing == 16                   # CONFIRMED
    assert a.num_layers == 94                      # estimated until July 27
    assert a.total_expert_lookups_per_token == 1504   # 16 x 94
    assert a.attention_type == "KDA"               # GQA placeholder in engine
    assert a.has_native_mtp is False
    assert a.drafter_hf_id == "moonshotai/Kimi-K2"
    assert a.default_acceptance_rate == pytest.approx(0.42)
    assert a.get_drafter_config()["type"] == "same_family"


def test_mixtral_8x7b_complete():
    adapter = get_adapter("mixtral-8x7b")

    # Architecture
    assert adapter.name == "Mixtral-8x7B-Instruct"
    assert adapter.num_layers == 32
    assert adapter.num_experts_per_layer == 8
    assert adapter.top_k_routing == 2
    assert adapter.total_expert_lookups_per_token == 64      # 2 x 32
    assert adapter.total_expert_count == 256
    assert adapter.attention_type == "GQA"
    assert adapter.num_kv_heads == 8
    assert adapter.num_attention_heads == 32
    assert adapter.num_shared_experts == 0
    assert adapter.has_native_mtp is False

    # THE key insight: ALL experts fit in a 32GB system's RAM.
    # 99,090,552 B/expert MEASURED from the real 2026-07-19 conversion
    # (the pre-conversion 56MB estimate was wrong by 43MB/expert).
    assert adapter.expert_size_bytes == 99_090_552
    total_expert_bytes = (adapter.total_expert_count
                          * adapter.expert_size_bytes)
    assert total_expert_bytes < 26 * 1024**3      # ~25.4GB — fits in 32GB

    # Tensor naming (Mistral family)
    assert adapter.is_dense_tensor("model.embed_tokens.weight")
    assert adapter.is_dense_tensor(
        "model.layers.0.self_attn.q_proj.weight")
    assert not adapter.is_dense_tensor(
        "model.layers.0.block_sparse_moe.experts.3.w1.weight")

    # Expert keys
    keys = adapter.get_expert_key(0, 3)
    assert len(keys) == 3
    assert "block_sparse_moe.experts.3.w1" in keys[0]
    assert "block_sparse_moe.experts.3.w2" in keys[1]
    assert "block_sparse_moe.experts.3.w3" in keys[2]

    # Router key
    assert "layers.5.block_sparse_moe.gate" in adapter.get_router_key(5)


def test_mixtral_partitioning_hooks():
    """The regex + normalization the partitioner actually uses."""
    adapter = get_adapter("mixtral-8x7b")
    m = adapter.expert_weight_pattern.match(
        "model.layers.12.block_sparse_moe.experts.5.w3.weight")
    assert m and (int(m.group("layer")), int(m.group("expert"))) == (12, 5)
    # w1/w3/w2 normalize onto the canonical .bin order gate/up/down
    assert adapter.normalize_expert_proj("w1") == "gate_proj"
    assert adapter.normalize_expert_proj("w3") == "up_proj"
    assert adapter.normalize_expert_proj("w2") == "down_proj"
    # router maps into the canonical dense layout
    assert adapter.canonical_dense_name(
        "model.layers.7.block_sparse_moe.gate.weight") == "layers.7.router"
    # attention tensors ride the shared Llama-style mapping
    assert adapter.canonical_dense_name(
        "model.layers.7.self_attn.q_proj.weight") == "layers.7.attn.q_proj"


def test_mixtral_8x22b_complete():
    adapter = get_adapter("mixtral-8x22b")
    assert adapter.name == "Mixtral-8x22B-Instruct"
    assert adapter.num_layers == 56
    assert adapter.num_experts_per_layer == 8
    assert adapter.top_k_routing == 2
    assert adapter.total_expert_lookups_per_token == 112     # 2 x 56
    assert adapter.total_expert_count == 448
    assert adapter.num_attention_heads == 48
    assert adapter.num_kv_heads == 8
    # 8x22B experts do NOT fit in RAM — needs the SSD tier
    total_expert_bytes = (adapter.total_expert_count
                          * adapter.expert_size_bytes)
    assert total_expert_bytes > 16 * 1024**3
    # drafts via its little sibling
    assert adapter.drafter_hf_id == "mistralai/Mixtral-8x7B-Instruct-v0.1"


def test_gqa_kv_head_ratio():
    adapter = get_adapter("mixtral-8x7b")
    ratio = adapter.num_attention_heads // adapter.num_kv_heads
    assert ratio == 4      # 32Q / 8KV = 4 queries per KV head
    big = get_adapter("mixtral-8x22b")
    assert big.num_attention_heads // big.num_kv_heads == 6


def test_gqa_kv_expansion():
    """KV heads expand to match Q heads (the semantics the CUDA/CPU
    attention implements via index grouping: kv_head = q_head // ratio,
    equivalent to repeat_interleave without materializing the copy)."""
    num_q_heads, num_kv_heads, head_dim, seq_len = 32, 8, 128, 10
    ratio = num_q_heads // num_kv_heads      # 4

    kv = torch.randn(seq_len, num_kv_heads, head_dim)
    kv_expanded = kv.repeat_interleave(ratio, dim=1)
    assert kv_expanded.shape == (seq_len, num_q_heads, head_dim)
    # Index-grouping equivalence — what the engine's kernels compute
    for q_head in range(num_q_heads):
        assert torch.equal(kv_expanded[:, q_head], kv[:, q_head // ratio])


def test_registry_resolution_and_errors():
    assert set(supported_models()) == {"glm-5.2", "deepseek-v3",
                                       "deepseek-r1", "kimi-k3",
                                       "mixtral-8x7b", "mixtral-8x22b"}
    assert get_adapter("GLM-5.2").family == "glm52"
    assert get_adapter("zai-org/GLM-5.2").family == "glm52"
    assert get_adapter("kimi_k3").family == "kimi_k3"
    assert get_adapter("moonshotai/Kimi-K3").family == "kimi_k3"
    with pytest.raises(ValueError, match="Unknown model"):
        get_adapter("gpt-oss-999")
    with pytest.raises(FileNotFoundError):
        adapter_from_model_dir("/nonexistent/model/dir")


def test_expert_tensor_pattern():
    a = get_adapter("deepseek-v3")
    m = a.expert_weight_pattern.match(
        "model.layers.12.mlp.experts.207.gate_proj.weight")
    assert m and (int(m.group("layer")), int(m.group("expert")),
                  m.group("proj")) == (12, 207, "gate_proj")
    assert a.expert_weight_pattern.match(
        "model.layers.12.mlp.shared_experts.gate_proj.weight") is None
    # shared experts are dense
    assert a.canonical_dense_name(
        "model.layers.12.mlp.shared_experts.gate_proj.weight"
    ) == "layers.12.shared.gate"


# --------------------------------------------------------------------------
# int4 quantization contract
# --------------------------------------------------------------------------

def test_quantize_roundtrip_error_is_small():
    torch.manual_seed(0)
    w = torch.randn(64, 128) * 0.02
    qt = quantize_int4(w, group_size=64)
    recon = dequantize_int4(qt)
    err = (w - recon.float()).abs().max().item()
    # int4 with 15 steps per group: max error <= half a step
    step = (w.view(-1, 64).max(1).values - w.view(-1, 64).min(1).values) / 15
    assert err <= step.max().item() * 0.51 + 1e-6
    assert quantization_error(w) < 0.005


def test_quantize_packing_low_nibble_first():
    # Constant groups quantize exactly: value = zero, nibble = 8
    w = torch.full((2, 64), 1.0)
    qt = quantize_int4(w, group_size=64)
    assert qt.packed[0].item() == 0x88          # two nibbles of 8
    assert dequantize_int4(qt).allclose(w.half())


def test_quantize_rejects_bad_input():
    with pytest.raises(ValueError):
        quantize_int4(torch.randn(4), group_size=64)      # 1D
    with pytest.raises(ValueError):
        quantize_int4(torch.randn(4, 4), group_size=0)


# --------------------------------------------------------------------------
# Expert .bin format (must match csrc/core/wisp_engine.c exactly)
# --------------------------------------------------------------------------

def test_expert_file_layout(tmp_path):
    torch.manual_seed(1)
    hidden, inter, gs = 32, 16, 16
    mats = {
        "gate_proj": quantize_int4(torch.randn(inter, hidden), gs),
        "up_proj":   quantize_int4(torch.randn(inter, hidden), gs),
        "down_proj": quantize_int4(torch.randn(hidden, inter), gs),
    }
    path = tmp_path / expert_filename(3, 42)
    size = write_expert_file(path, 3, 42, mats)
    assert path.exists() and path.stat().st_size == size

    blob = path.read_bytes()
    magic, ver, layer, expert, group, nmats = EXPERT_HEADER.unpack_from(blob)
    assert (magic, ver, layer, expert, group, nmats) == \
           (EXPERT_MAGIC, 1, 3, 42, gs, 3)

    # Walk the three mat headers; blobs must tile the file exactly
    off = EXPERT_HEADER.size + 3 * EXPERT_MAT_HEADER.size
    assert EXPERT_HEADER.size + 3 * EXPERT_MAT_HEADER.size == 120
    for i, key in enumerate(("gate_proj", "up_proj", "down_proj")):
        rows, cols, pb, sb, zb = EXPERT_MAT_HEADER.unpack_from(
            blob, EXPERT_HEADER.size + i * EXPERT_MAT_HEADER.size)
        qt = mats[key]
        assert (rows, cols) == (qt.rows, qt.cols)
        assert pb == qt.packed.numel()
        off += pb + sb + zb
    assert off == len(blob)


@pytest.mark.engine
@pytest.mark.skipif(not HAS_ENGINE,
                    reason="C engine not available in CI")
def test_c_engine_reads_python_packed_expert(tmp_path):
    """
    The three-way byte-layout contract: Python packer -> C header parser
    -> C int4 dequant must agree bit-for-bit with the Python dequantizer.
    Exercises the REAL C engine code via the _debug_expert_probe binding.
    """
    core = _core

    torch.manual_seed(7)
    hidden, inter, gs = 32, 16, 16
    mats = {
        "gate_proj": quantize_int4(torch.randn(inter, hidden), gs),
        "up_proj":   quantize_int4(torch.randn(inter, hidden), gs),
        "down_proj": quantize_int4(torch.randn(hidden, inter), gs),
    }
    path = tmp_path / expert_filename(5, 123)
    write_expert_file(path, 5, 123, mats)

    for mat_idx, key in enumerate(("gate_proj", "up_proj", "down_proj")):
        probe = core._debug_expert_probe(str(path), mat_idx, 64)
        qt = mats[key]
        assert probe["rows"][mat_idx] == qt.rows
        assert probe["cols"][mat_idx] == qt.cols
        assert probe["group_size"] == gs
        assert probe["total_bytes"] == path.stat().st_size

        c_vals = torch.tensor(probe["values"])
        py_vals = dequantize_int4(qt).flatten()[:len(c_vals)].float()
        # C computes fp32 from fp16 scale/zero; Python rounds through
        # fp16 output — agreement within one fp16 ulp of these magnitudes
        assert torch.allclose(c_vals, py_vals, atol=5e-3), \
            f"{key}: C dequant diverges from Python dequant"


def test_expert_file_rejects_incomplete(tmp_path):
    qt = quantize_int4(torch.randn(8, 8), group_size=8)
    with pytest.raises(ValueError, match="missing"):
        write_expert_file(tmp_path / "x.bin", 0, 0, {"gate_proj": qt})


# --------------------------------------------------------------------------
# Manifest
# --------------------------------------------------------------------------

def test_manifest_roundtrip(tmp_path):
    a = get_adapter("glm-5.2")
    m = ModelManifest.build(a, quant_dtype="int4", group_size=64)
    m.save(tmp_path)

    loaded = ModelManifest.load(tmp_path)
    assert loaded.model_family == "glm52"
    arch = loaded.architecture
    assert arch["total_expert_lookups_per_token"] == 488
    assert loaded.performance["bytes_per_token_all_cold"] == \
           18_350_080 * 488
    assert loaded.files["expert_naming"] == "L{layer:03d}_E{expert:05d}.bin"
    assert loaded.mtp["available"] is True

    # And the registry can resolve an adapter from the directory
    assert adapter_from_model_dir(tmp_path).family == "glm52"


def test_manifest_missing_dir_raises(tmp_path):
    with pytest.raises(FileNotFoundError):
        ModelManifest.load(tmp_path / "nope")
