"""
wisp.system.profiler — one-time hardware detection + benchmark.

Profiles GPUs (via torch.cuda), RAM (psutil), NVMe sequential read speed
(512MB benchmark), and CPU capabilities (py-cpuinfo). Caches the result to
~/.wisp/system_profile.json and re-profiles after 7 days.
"""

from __future__ import annotations

import json
import platform
import subprocess
import tempfile
import time
from dataclasses import dataclass, asdict
from pathlib import Path

import psutil
import torch


def detect_display_on_gpu(gpu_index: int = 0) -> bool:
    """
    Detects whether the primary display is connected to the GPU or to
    the motherboard (iGPU).

    Returns True if display is on GPU (VRAM must be reserved for it),
    False if display is on iGPU (full VRAM free for inference).

    Uses `nvidia-smi --query-gpu=display_active` — identical on Windows
    and Linux, and authoritative: the driver itself reports whether it is
    scanning out a display. Any failure (no nvidia-smi, no GPU, weird
    driver) falls back to True — reserving VRAM we didn't need to is
    recoverable, driving the desktop out of memory is not.
    """
    import shutil as _shutil

    nvsmi = _shutil.which("nvidia-smi")
    if not nvsmi and platform.system() == "Windows":
        candidate = (r"C:\Windows\System32\nvidia-smi.exe")
        nvsmi = candidate if Path(candidate).exists() else None
    if not nvsmi:
        return True   # can't tell — safe assumption

    try:
        result = subprocess.run(
            [nvsmi, "--query-gpu=display_active",
             "--format=csv,noheader,nounits", f"--id={gpu_index}"],
            capture_output=True, text=True, timeout=5)
        return result.stdout.strip().lower().startswith("enabled")
    except Exception:
        # If detection fails assume display is on GPU —
        # better safe than a black screen.
        return True


DISPLAY_RESERVED_BYTES = 1_500_000_000   # WDDM/compositor when on-GPU

# --------------------------------------------------------------------------
# Alternative accelerator platforms
# --------------------------------------------------------------------------
DGX_SPARK_UNIFIED_GB = 128        # GB10 coherent LPDDR5x pool
DGX_SPARK_BANDWIDTH_GB_S = 273
R9700_VRAM_GB = 32                # RDNA4 Navi 48, 256-bit GDDR6
R9700_BANDWIDTH_GB_S = 640
R9700_GFX_TARGET = "gfx1201"


def _run(cmd: list[str], timeout: float = 5.0) -> str:
    """Run a probe command, returning '' on any failure. Detection must
    never raise into engine startup."""
    try:
        r = subprocess.run(cmd, capture_output=True, text=True,
                           timeout=timeout)
        return r.stdout or ""
    except (OSError, subprocess.SubprocessError, ValueError):
        return ""


def detect_dgx_spark(gpu_index: int = 0) -> dict | None:
    """
    Identify an NVIDIA DGX Spark (GB10 Grace Blackwell).

    Why WISP cares: Spark's 128GB is *coherent* — the CPU and GPU address
    the same physical memory. WISP's VRAM and RAM tiers are the same pool
    there, so the usual three tiers collapse to two (unified -> NVMe) and
    the RAM->VRAM copy that the double buffer exists to hide simply does
    not happen. Prefetch from NVMe still matters.

    All three checks must agree; any single one has false positives.
    Returns None on anything that is not a Spark.
    """
    if platform.machine().lower() not in ("aarch64", "arm64"):
        return None

    name = _run(["nvidia-smi", "--query-gpu=name",
                 "--format=csv,noheader", f"--id={gpu_index}"]).strip()
    if not name:
        return None
    lowered = name.lower()
    if not ("gb10" in lowered or "grace blackwell" in lowered
            or "dgx spark" in lowered):
        return None

    # The unified pool is reported as GPU memory. Accept a wide band —
    # drivers report usable rather than nameplate capacity.
    mem_raw = _run(["nvidia-smi", "--query-gpu=memory.total",
                    "--format=csv,noheader,nounits",
                    f"--id={gpu_index}"]).strip().splitlines()
    total_mb = 0
    if mem_raw:
        try:
            total_mb = int(float(mem_raw[0].strip()))
        except ValueError:
            total_mb = 0
    if not (90_000 <= total_mb <= 160_000):
        return None

    return {
        "type": "dgx_spark",
        "name": name,
        "unified_memory_gb": DGX_SPARK_UNIFIED_GB,
        "bandwidth_gb_s": DGX_SPARK_BANDWIDTH_GB_S,
        "two_node": False,
        "nodes": 1,
    }


def detect_dgx_spark_dual(gpu_index: int = 0) -> dict | None:
    """A Spark, plus whether a second one is NVLink-attached (256GB).

    Two Sparks are how a 2.8T model like Kimi K3 gets most of its experts
    into silicon at all, so the distinction is worth probing.
    """
    spark = detect_dgx_spark(gpu_index)
    if spark is None:
        return None

    count = len([ln for ln in _run(
        ["nvidia-smi", "--query-gpu=name", "--format=csv,noheader"]
    ).splitlines() if ln.strip()])
    topo = _run(["nvidia-smi", "topo", "-m"]).upper()
    linked = ("NV" in topo and count >= 2)

    if count >= 2 and linked:
        spark["two_node"] = True
        spark["nodes"] = 2
        spark["unified_memory_gb"] = DGX_SPARK_UNIFIED_GB * 2
        spark["bandwidth_gb_s"] = DGX_SPARK_BANDWIDTH_GB_S
    return spark


def detect_amd_gpu() -> dict | None:
    """
    Identify an AMD Radeon AI PRO R9700 via ROCm.

    DETECTION ONLY. WISP's compute kernels are CUDA; nothing here makes
    them run on ROCm. What this buys today is that `wisp doctor` can say
    "I see your R9700 and here is where support stands" instead of
    reporting no GPU at all. The HIP port is a separate piece of work.
    """
    out = _run(["rocm-smi", "--showproductname"])
    if not out:
        return None
    lowered = out.lower()
    if "r9700" not in lowered.replace(" ", ""):
        return None

    count = sum(1 for line in out.splitlines()
                if "r9700" in line.lower().replace(" ", ""))
    count = max(count, 1)

    version = ""
    ver_out = _run(["rocm-smi", "--version"])
    for line in ver_out.splitlines():
        if any(ch.isdigit() for ch in line):
            version = line.strip()
            break

    return {
        "type": "amd_r9700",
        "vendor": "amd",
        "vram_gb": R9700_VRAM_GB,
        "bandwidth_gb_s": R9700_BANDWIDTH_GB_S,
        "rocm_version": version,
        "count": count,
        "gfx_target": R9700_GFX_TARGET,
        "compute_supported": False,   # detection only in this release
    }


@dataclass
class GPUProfile:
    index:              int
    name:               str
    vram_total_bytes:   int
    vram_free_bytes:    int
    cuda_major:         int
    cuda_minor:         int
    memory_bw_gb_s:     float


@dataclass
class SystemProfile:
    gpus:                       list[GPUProfile]
    gpu_count:                  int
    primary_gpu_index:          int
    total_ram_bytes:            int
    available_ram_bytes:        int
    nvme_speed_bytes_per_sec:   int
    nvme_pcie_gen_estimate:     int
    cpu_name:                   str
    cpu_cores:                  int
    cpu_threads:                int
    cpu_has_avx2:               bool
    cpu_has_avx512:             bool
    os_platform:                str
    profiled_at:                float
    # Display routing: when the monitor hangs off the GPU, the desktop
    # compositor permanently owns a slice of VRAM that expert-cache math
    # must not count. Defaults are the SAFE assumption for old caches.
    display_on_gpu:             bool = True
    display_reserved_bytes:     int = DISPLAY_RESERVED_BYTES
    # Alternative platforms. Defaults keep every existing cached profile
    # loadable and every existing code path unchanged.
    accelerator:                str = "cuda"   # cuda | unified | rocm | cpu
    unified_memory_gb:          float = 0.0
    unified_bandwidth_gb_s:     float = 0.0
    amd_gpu:                    dict | None = None


class SystemProfiler:
    CACHE_PATH = Path.home() / ".wisp" / "system_profile.json"
    CACHE_MAX_AGE_SECONDS = 7 * 86400  # Re-profile after 7 days

    def get(self, force_refresh: bool = False) -> SystemProfile:
        if not force_refresh and self.CACHE_PATH.exists():
            try:
                age = time.time() - self.CACHE_PATH.stat().st_mtime
                if age < self.CACHE_MAX_AGE_SECONDS:
                    with open(self.CACHE_PATH, encoding="utf-8") as f:
                        d = json.load(f)
                    if "display_on_gpu" not in d:
                        raise KeyError("pre-display-detection cache")
                    d["gpus"] = [GPUProfile(**g) for g in d["gpus"]]
                    return SystemProfile(**d)
            except (json.JSONDecodeError, TypeError, KeyError):
                pass  # Corrupt or outdated cache — fresh benchmark
        profile = self._run_benchmark()
        self._save(profile)
        return profile

    def _run_benchmark(self) -> SystemProfile:
        print("  [WISP] Profiling system (one-time, ~10 seconds)...")
        gpus = self._detect_gpus()
        ram  = self._detect_ram()
        nvme = self._benchmark_nvme()
        cpu  = self._detect_cpu()
        display_on_gpu = detect_display_on_gpu(0) if gpus else False

        spark = detect_dgx_spark_dual()
        amd = detect_amd_gpu() if spark is None else None
        if spark:
            accelerator = "unified"
            unified_gb = float(spark["unified_memory_gb"])
            unified_bw = float(spark["bandwidth_gb_s"])
            # A Spark drives no desktop off a discrete card, so the
            # display reserve that exists for WDDM does not apply.
            display_on_gpu = False
        elif amd:
            accelerator = "rocm"
            unified_gb = unified_bw = 0.0
        else:
            accelerator = "cuda" if gpus else "cpu"
            unified_gb = unified_bw = 0.0

        return SystemProfile(
            accelerator              = accelerator,
            unified_memory_gb        = unified_gb,
            unified_bandwidth_gb_s   = unified_bw,
            amd_gpu                  = amd,
            display_on_gpu           = display_on_gpu,
            display_reserved_bytes   = (DISPLAY_RESERVED_BYTES
                                        if display_on_gpu else 0),
            gpus                     = gpus,
            gpu_count                = len(gpus),
            primary_gpu_index        = 0 if gpus else -1,
            total_ram_bytes          = ram["total"],
            available_ram_bytes      = ram["available"],
            nvme_speed_bytes_per_sec = nvme["speed"],
            nvme_pcie_gen_estimate   = nvme["gen"],
            cpu_name                 = cpu["name"],
            cpu_cores                = cpu["cores"],
            cpu_threads              = cpu["threads"],
            cpu_has_avx2             = cpu["avx2"],
            cpu_has_avx512           = cpu["avx512"],
            os_platform              = platform.system().lower(),
            profiled_at              = time.time(),
        )

    def _detect_gpus(self) -> list[GPUProfile]:
        if not torch.cuda.is_available():
            return []
        gpus = []
        for i in range(torch.cuda.device_count()):
            p = torch.cuda.get_device_properties(i)
            free, total = torch.cuda.mem_get_info(i)
            # memory_clock_rate is kHz, bus width in bits; DDR doubles the rate
            clock_khz = getattr(p, "memory_clock_rate", 0)
            bus_bits  = getattr(p, "memory_bus_width", 0)
            bw_gb_s   = clock_khz * 1000 * 2 * bus_bits / 8 / 1e9
            gpus.append(GPUProfile(
                index            = i,
                name             = p.name,
                vram_total_bytes = p.total_memory,
                vram_free_bytes  = free,
                cuda_major       = p.major,
                cuda_minor       = p.minor,
                memory_bw_gb_s   = round(bw_gb_s, 1),
            ))
        return gpus

    def _detect_ram(self) -> dict:
        vm = psutil.virtual_memory()
        return {"total": vm.total, "available": vm.available}

    def _benchmark_nvme(self, size_bytes: int = 512 * 1024 * 1024) -> dict:
        """Sequential read benchmark with best-effort OS cache bypass."""
        chunk = b"\x00" * (4 * 1024 * 1024)
        with tempfile.NamedTemporaryFile(delete=False, suffix=".wispbench") as f:
            written = 0
            while written < size_bytes:
                f.write(chunk)
                written += len(chunk)
            path = f.name

        # Attempt to flush OS page cache (Linux only, needs root; best effort)
        try:
            if platform.system() == "Linux":
                subprocess.run(["sync"], check=False)
                with open("/proc/sys/vm/drop_caches", "w") as dc:
                    dc.write("1")
        except (OSError, PermissionError):
            pass

        start = time.perf_counter()
        with open(path, "rb") as f:
            while f.read(4 * 1024 * 1024):
                pass
        elapsed = max(time.perf_counter() - start, 1e-6)
        Path(path).unlink(missing_ok=True)

        speed = int(size_bytes / elapsed)
        gen = 5 if speed > 10_000_000_000 else \
              4 if speed >  5_000_000_000 else \
              3 if speed >  2_000_000_000 else 2
        return {"speed": speed, "gen": gen}

    def _detect_cpu(self) -> dict:
        try:
            import cpuinfo  # py-cpuinfo
            info = cpuinfo.get_cpu_info()
        except Exception:
            info = {}
        flags = info.get("flags", [])
        return {
            "name":    info.get("brand_raw", platform.processor() or "Unknown CPU"),
            "cores":   psutil.cpu_count(logical=False) or 1,
            "threads": psutil.cpu_count(logical=True) or 1,
            "avx2":    "avx2" in flags,
            "avx512":  "avx512f" in flags,
        }

    def _save(self, profile: SystemProfile) -> None:
        self.CACHE_PATH.parent.mkdir(parents=True, exist_ok=True)
        tmp = self.CACHE_PATH.with_suffix(".json.tmp")
        with open(tmp, "w", encoding="utf-8") as f:
            json.dump(asdict(profile), f, indent=2)
        tmp.replace(self.CACHE_PATH)
