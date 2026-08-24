"""Tests for wisp.system.profiler + auto_config tier math."""

import json

import pytest

from wisp.models import constants as C
from wisp.models.registry import get_adapter
from wisp.system.auto_config import AutoConfig, pick_gpu_strategy
from wisp.system.profiler import GPUProfile, SystemProfile, SystemProfiler


# --------------------------------------------------------------------------
# Profiler internals
# --------------------------------------------------------------------------

def test_detect_ram_returns_positive_values():
    ram = SystemProfiler()._detect_ram()
    assert ram["total"] > 0
    assert 0 < ram["available"] <= ram["total"]


def test_detect_cpu_fields():
    cpu = SystemProfiler()._detect_cpu()
    assert cpu["cores"] >= 1
    assert cpu["threads"] >= cpu["cores"]
    assert isinstance(cpu["avx2"], bool)
    assert isinstance(cpu["avx512"], bool)
    assert cpu["name"]


def test_nvme_benchmark_small(tmp_path, monkeypatch):
    import tempfile
    monkeypatch.setattr(tempfile, "tempdir", str(tmp_path))
    result = SystemProfiler()._benchmark_nvme(size_bytes=8 * 1024 * 1024)
    assert result["speed"] > 0
    assert result["gen"] in (2, 3, 4, 5)
    assert list(tmp_path.glob("*.wispbench")) == []  # cleaned up


def test_profile_cache_roundtrip(tmp_path, monkeypatch):
    cache = tmp_path / "system_profile.json"
    monkeypatch.setattr(SystemProfiler, "CACHE_PATH", cache)
    monkeypatch.setattr(
        SystemProfiler, "_benchmark_nvme",
        lambda self, size_bytes=0: {"speed": 6_000_000_000, "gen": 4})

    p1 = SystemProfiler().get(force_refresh=True)
    assert cache.exists()
    saved = json.loads(cache.read_text())
    assert saved["nvme_speed_bytes_per_sec"] == 6_000_000_000

    # Second call must come from cache (same profiled_at timestamp)
    p2 = SystemProfiler().get()
    assert p2.profiled_at == p1.profiled_at
    assert isinstance(p2.gpus, list)
    for g in p2.gpus:
        assert isinstance(g, GPUProfile)


# --------------------------------------------------------------------------
# Tier allocation math
# --------------------------------------------------------------------------

def _fake_profile(gpus, ram_available=26 * 1024**3,
                  nvme=6_000_000_000) -> SystemProfile:
    return SystemProfile(
        gpus=gpus, gpu_count=len(gpus),
        primary_gpu_index=0 if gpus else -1,
        total_ram_bytes=32 * 1024**3, available_ram_bytes=ram_available,
        nvme_speed_bytes_per_sec=nvme, nvme_pcie_gen_estimate=4,
        cpu_name="Test CPU", cpu_cores=8, cpu_threads=16,
        cpu_has_avx2=True, cpu_has_avx512=False,
        os_platform="test", profiled_at=0.0,
    )


def _gpu(index=0, vram_gb=12) -> GPUProfile:
    return GPUProfile(index=index, name=f"Test GPU {index}",
                      vram_total_bytes=vram_gb * 1024**3,
                      vram_free_bytes=vram_gb * 1024**3,
                      cuda_major=8, cuda_minor=9, memory_bw_gb_s=500.0)


def test_dense_layers_claim_vram_first():
    """Dense layers claim VRAM first; the expert cache gets what remains
    under the 75% hard cap (WISP never plans past 3/4 of the card)."""
    adapter = get_adapter("glm-5.2")
    # GLM dense (9.9GB) exceeds a 12GB card's 75% cap (9GB) -> the cap
    # correctly yields ZERO vram expert slots on that card; use a 24GB
    # card to exercise the dense-first-then-experts split.
    cfg = AutoConfig().calculate(_fake_profile([_gpu(vram_gb=24)]), adapter)

    vram_bytes = 24 * 1024**3
    cap = int(vram_bytes * 0.75)
    expected_max = ((cap - adapter.dense_layer_size_bytes)
                    // adapter.expert_size_bytes)
    assert 0 < cfg.vram_expert_count <= expected_max
    assert cfg.ram_expert_count > 0
    total = (cfg.vram_expert_count + cfg.ram_expert_count
             + cfg.ssd_expert_count)
    assert total == adapter.total_expert_count

    # And the 12GB case: cap < dense -> no VRAM experts, engine runs
    # hybrid (experts from RAM) instead of overcommitting the card.
    small = AutoConfig().calculate(_fake_profile([_gpu(vram_gb=12)]), adapter)
    assert small.vram_expert_count == 0


def test_cpu_only_dense_layers_go_to_ram():
    adapter = get_adapter("glm-5.2")
    ram = 26 * 1024**3
    cfg = AutoConfig().calculate(_fake_profile([], ram_available=ram), adapter)
    assert cfg.gpu_strategy == "cpu_only"
    assert cfg.vram_expert_count == 0
    # RAM experts must fit in what remains AFTER dense + OS buffer
    remaining = ram - adapter.dense_layer_size_bytes - 4 * 1024**3
    assert cfg.ram_expert_count <= max(0, remaining) // adapter.expert_size_bytes


def test_cold_token_math_uses_lookups_formula():
    """cold tok/s = nvme_speed / (expert_size x top_k x layers)."""
    adapter = get_adapter("glm-5.2")
    nvme = 6_000_000_000
    cfg = AutoConfig().calculate(
        _fake_profile([_gpu()], nvme=nvme), adapter)
    bytes_per_token = (adapter.expert_size_bytes
                       * adapter.top_k_routing * adapter.num_layers)
    assert bytes_per_token == 18_350_080 * 8 * 61
    assert cfg.estimated_cold_toks == pytest.approx(
        nvme / bytes_per_token, rel=0.01)


def test_display_detection():
    from wisp.system.profiler import detect_display_on_gpu
    # Must return a bool without crashing, whatever the machine
    result = detect_display_on_gpu(0)
    assert isinstance(result, bool)
    # Never hardcode which port the monitor is on (it moved mid-launch
    # week and broke the first version of this test) — assert agreement
    # with the driver's own answer instead.
    import shutil
    import subprocess
    nvsmi = shutil.which("nvidia-smi")
    if nvsmi:
        out = subprocess.run(
            [nvsmi, "--query-gpu=display_active",
             "--format=csv,noheader,nounits", "--id=0"],
            capture_output=True, text=True, timeout=10).stdout
        expected = out.strip().lower().startswith("enabled")
        assert result is expected


def test_auto_buffer_calculation():
    from wisp.system.profiler import SystemProfiler

    profile = SystemProfiler().get()
    if profile.display_on_gpu:
        # Display on GPU -> at least 1.5GB reserved for the compositor
        assert profile.display_reserved_bytes >= 1_500_000_000
    else:
        assert profile.display_reserved_bytes == 0

    # The reserve must flow into the tier math: forcing igpu mode frees
    # VRAM, so the expert count can only go up (or stay equal).
    import copy
    from wisp.runtime.engine import apply_display_mode
    adapter = get_adapter("mixtral-8x7b")
    auto_cfg = AutoConfig().calculate(profile, adapter)
    igpu_profile = apply_display_mode(copy.deepcopy(profile), "igpu")
    igpu_cfg = AutoConfig().calculate(igpu_profile, adapter)

    # Freeing the display reserve can never COST slots.
    assert igpu_cfg.vram_expert_count >= auto_cfg.vram_expert_count

    # It only ADDS slots when the display reserve is the binding
    # constraint. The 75% safety cap is stricter on most cards — e.g.
    # 12GB: cap 9.0GB vs 12 - 2.0 (display + base) = 10.1GB — so equality
    # here is correct behaviour, not a regression.
    if profile.gpu_count > 0 and profile.display_on_gpu:
        vram = profile.gpus[profile.primary_gpu_index].vram_total_bytes
        cap = int(vram * 0.75)
        display_limited = vram - (C.VRAM_SAFETY_BUFFER
                                  + profile.display_reserved_bytes)
        if display_limited < cap:      # reserve binds -> real gain
            assert igpu_cfg.vram_expert_count > auto_cfg.vram_expert_count


# --------------------------------------------------------------------------
# Alternative platforms: DGX Spark (unified memory) and AMD ROCm
# --------------------------------------------------------------------------

def test_detect_dgx_spark_returns_none_on_x86(monkeypatch):
    """The arch check short-circuits before any subprocess runs."""
    import platform as _platform
    from wisp.system import profiler as prof
    monkeypatch.setattr(_platform, "machine", lambda: "x86_64")
    called = []
    monkeypatch.setattr(prof, "_run",
                        lambda *a, **k: called.append(a) or "")
    assert prof.detect_dgx_spark() is None
    assert called == [], "must not shell out on a non-ARM machine"


def test_detect_dgx_spark_structure(monkeypatch):
    import platform as _platform
    from wisp.system import profiler as prof
    monkeypatch.setattr(_platform, "machine", lambda: "aarch64")

    def fake_run(cmd, timeout=5.0):
        joined = " ".join(cmd)
        if "--query-gpu=name" in joined:
            return "NVIDIA GB10 Grace Blackwell Superchip"
        if "memory.total" in joined:
            return "131072"
        return ""
    monkeypatch.setattr(prof, "_run", fake_run)

    spark = prof.detect_dgx_spark()
    assert spark is not None
    assert spark["type"] == "dgx_spark"
    assert spark["unified_memory_gb"] == 128
    assert spark["bandwidth_gb_s"] == 273
    assert spark["two_node"] is False


def test_detect_dgx_spark_rejects_ordinary_arm_gpu(monkeypatch):
    """ARM alone is not a Spark — a Jetson must not be mistaken for one."""
    import platform as _platform
    from wisp.system import profiler as prof
    monkeypatch.setattr(_platform, "machine", lambda: "aarch64")
    monkeypatch.setattr(prof, "_run",
                        lambda cmd, timeout=5.0:
                        "NVIDIA Jetson AGX Orin"
                        if "name" in " ".join(cmd) else "32768")
    assert prof.detect_dgx_spark() is None


def test_detect_dgx_spark_dual_detects_nvlink(monkeypatch):
    import platform as _platform
    from wisp.system import profiler as prof
    monkeypatch.setattr(_platform, "machine", lambda: "aarch64")

    def fake_run(cmd, timeout=5.0):
        joined = " ".join(cmd)
        if "topo" in joined:
            return "GPU0 GPU1 | GPU0 X NV1 | GPU1 NV1 X"
        if "--query-gpu=name" in joined:
            return "NVIDIA GB10" + chr(10) + "NVIDIA GB10"
        if "memory.total" in joined:
            return "131072"
        return ""
    monkeypatch.setattr(prof, "_run", fake_run)

    spark = prof.detect_dgx_spark_dual()
    assert spark["two_node"] is True
    assert spark["nodes"] == 2
    assert spark["unified_memory_gb"] == 256


def test_dgx_spark_auto_config_uses_unified_mode():
    """Unified mode collapses the tiers: one pool, no RAM tier."""
    profile = _fake_profile([_gpu(vram_gb=128)])
    profile.accelerator = "unified"
    profile.unified_memory_gb = 128.0
    profile.unified_bandwidth_gb_s = 273.0

    cfg = AutoConfig().calculate(profile, get_adapter("glm-5.2"))
    assert cfg.tier_mode == "unified"
    assert cfg.backend == "unified"
    assert cfg.gpu_strategy == "unified"
    assert cfg.ram_expert_count == 0        # same physical memory
    assert cfg.unified_pool_gb == 128.0
    assert cfg.vram_expert_count > 0
    total = (cfg.vram_expert_count + cfg.ram_expert_count
             + cfg.ssd_expert_count)
    assert total == get_adapter("glm-5.2").total_expert_count


def test_dgx_spark_dual_holds_more_experts():
    """256GB must plan more resident experts than 128GB."""
    adapter = get_adapter("glm-5.2")
    single = _fake_profile([_gpu(vram_gb=128)])
    single.accelerator = "unified"
    single.unified_memory_gb = 128.0
    single.unified_bandwidth_gb_s = 273.0
    dual = _fake_profile([_gpu(vram_gb=128)])
    dual.accelerator = "unified"
    dual.unified_memory_gb = 256.0
    dual.unified_bandwidth_gb_s = 273.0

    a = AutoConfig().calculate(single, adapter)
    b = AutoConfig().calculate(dual, adapter)
    assert b.vram_expert_count > a.vram_expert_count
    assert b.ssd_expert_count < a.ssd_expert_count


def test_detect_amd_gpu_returns_none_when_rocm_smi_missing(monkeypatch):
    from wisp.system import profiler as prof

    def boom(cmd, timeout=5.0):
        raise FileNotFoundError("rocm-smi")
    monkeypatch.setattr(prof, "_run",
                        lambda *a, **k: "")     # _run swallows OSError
    assert prof.detect_amd_gpu() is None


def test_detect_amd_gpu_structure(monkeypatch):
    from wisp.system import profiler as prof
    monkeypatch.setattr(prof, "_run", lambda cmd, timeout=5.0:
                        "GPU[0] : Card Series: Radeon AI PRO R9700"
                        if "showproductname" in " ".join(cmd)
                        else "ROCm version: 7.0.1")
    amd = prof.detect_amd_gpu()
    assert amd is not None
    assert amd["type"] == "amd_r9700"
    assert amd["vram_gb"] == 32
    assert amd["bandwidth_gb_s"] == 640
    assert amd["gfx_target"] == "gfx1201"
    assert amd["count"] == 1
    # Honest about what detection actually buys
    assert amd["compute_supported"] is False


def test_amd_multi_gpu_pools_vram(monkeypatch):
    from wisp.system import profiler as prof
    monkeypatch.setattr(prof, "_run", lambda cmd, timeout=5.0:
                        ("GPU[0] : Card Series: Radeon AI PRO R9700" + chr(10) +
                         "GPU[1] : Card Series: Radeon AI PRO R9700")
                        if "showproductname" in " ".join(cmd) else "")
    amd = prof.detect_amd_gpu()
    assert amd["count"] == 2
    assert amd["vram_gb"] * amd["count"] == 64


def test_rocm_profile_tags_backend():
    profile = _fake_profile([_gpu(vram_gb=32)])
    profile.accelerator = "rocm"
    profile.amd_gpu = {"gfx_target": "gfx1201", "count": 1,
                       "vram_gb": 32, "bandwidth_gb_s": 640}
    cfg = AutoConfig().calculate(profile, get_adapter("mixtral-8x7b"))
    assert cfg.backend == "rocm"
    assert cfg.vendor == "amd"
    assert cfg.gfx_target == "gfx1201"


def test_default_profile_is_plain_cuda():
    """Adding platforms must not disturb the ordinary NVIDIA path."""
    cfg = AutoConfig().calculate(_fake_profile([_gpu()]),
                                 get_adapter("mixtral-8x7b"))
    assert cfg.tier_mode == "3tier"
    assert cfg.backend == "cuda"
    assert cfg.vendor == "nvidia"


def test_gpu_strategy_selection():
    assert pick_gpu_strategy([]).mode == "cpu_only"
    assert pick_gpu_strategy([_gpu()]).mode == "single"
    assert pick_gpu_strategy([_gpu(0, 12), _gpu(1, 12)]).mode == "dual_same"
    s = pick_gpu_strategy([_gpu(0, 8), _gpu(1, 24)])
    assert s.mode == "dual_diff"
    assert s.primary == 1          # bigger GPU takes the dense layers
    assert pick_gpu_strategy([_gpu(i) for i in range(3)]).mode == "pipeline"
