"""
wisp.system.auto_config — calculates the optimal 3-tier split for
(this hardware, this model) with zero user configuration.

Dense layer placement rule (explicit, non-negotiable):
  - GPU present : dense layers -> VRAM first; expert cache gets the REMAINDER.
                  RAM tier holds EXPERTS ONLY.
  - CPU-only    : dense layers -> RAM first; expert cache gets the remainder.

All performance math uses the correct per-token formula:
  bytes_per_token = expert_size_bytes x top_K x num_layers
"""

from __future__ import annotations

from dataclasses import dataclass, asdict

from .profiler import SystemProfile
from ..models.base_adapter import ModelAdapter
from ..models import constants as C


@dataclass
class GPUStrategy:
    mode:      str              # cpu_only | single | dual_same | dual_diff | pipeline
    primary:   int = -1
    secondary: int | None = None
    gpus:      list[int] | None = None


@dataclass
class TierConfig:
    vram_expert_count:   int
    ram_expert_count:    int
    ssd_expert_count:    int
    gpu_strategy:        str
    primary_gpu:         int
    secondary_gpu:       int | None
    drafter_id:          str
    drafter_location:    str
    drafter_dtype:       str
    expected_acceptance: float
    omp_thread_count:    int
    estimated_cold_toks: float
    estimated_warm_toks: float
    estimated_hot_toks:  float
    estimated_mtp_toks:  float
    # Platform shape. "3tier" is the classic VRAM/RAM/SSD split;
    # "unified" is DGX Spark, where VRAM and RAM are one pool.
    tier_mode:           str = "3tier"
    backend:             str = "cuda"
    unified_pool_gb:     float = 0.0
    bandwidth_gb_s:      float = 0.0
    vendor:              str = "nvidia"
    gfx_target:          str = ""

    def to_dict(self) -> dict:
        return asdict(self)


def pick_gpu_strategy(gpus: list) -> GPUStrategy:
    """Auto-select multi-GPU strategy. Never asks the user."""
    if len(gpus) == 0:
        return GPUStrategy("cpu_only")
    if len(gpus) == 1:
        return GPUStrategy("single", primary=0)
    if len(gpus) == 2:
        vram0 = gpus[0].vram_total_bytes
        vram1 = gpus[1].vram_total_bytes
        ratio = max(vram0, vram1) / max(min(vram0, vram1), 1)
        if ratio < 1.3:
            return GPUStrategy("dual_same", primary=0, secondary=1)
        p = 0 if vram0 >= vram1 else 1
        return GPUStrategy("dual_diff", primary=p, secondary=1 - p)
    return GPUStrategy("pipeline", primary=0, gpus=list(range(len(gpus))))


def select_drafter_config(free_vram_bytes: int, drafter_id: str,
                          drafter_type: str) -> dict:
    """
    VRAM drafter fit logic:
      fp16 fits -> VRAM fp16 (best acceptance)
      int4 fits -> VRAM int4
      else      -> CPU int4 (still wins vs no speculation)
    """
    fp16_size = C.DRAFTER_SIZE_FP16.get(drafter_id, 4 * C.GB)
    int4_size = C.DRAFTER_SIZE_INT4.get(drafter_id, 1 * C.GB)
    buffer = C.VRAM_SAFETY_BUFFER

    if drafter_type == "native_mtp":
        # Native MTP heads are small and always live beside the dense layers.
        if free_vram_bytes > int4_size + buffer:
            return {"id": drafter_id, "location": "vram",
                    "dtype": "int8", "acceptance": 0.49}
        return {"id": drafter_id, "location": "cpu",
                "dtype": "int8", "acceptance": 0.45}

    if free_vram_bytes > fp16_size + buffer:
        return {"id": drafter_id, "location": "vram",
                "dtype": "fp16", "acceptance": 0.52}
    if free_vram_bytes > int4_size + buffer:
        return {"id": drafter_id, "location": "vram",
                "dtype": "int4", "acceptance": 0.47}
    return {"id": drafter_id, "location": "cpu",
            "dtype": "int4", "acceptance": 0.38}


class AutoConfig:

    def _unified_config(self, profile: SystemProfile,
                        model) -> TierConfig:
        """Tier plan for a coherent-memory machine (DGX Spark)."""
        es = model.expert_size_bytes
        pool_bytes = int(getattr(profile, "unified_memory_gb", 0) * 1e9)
        dense = model.dense_layer_size_bytes
        # One OS reserve, not the separate VRAM buffer + RAM buffer:
        # there is only one pool to starve.
        reserve = max(8 * 1024**3, int(pool_bytes * 0.10))
        usable = max(0, pool_bytes - dense - reserve)
        pooled_experts = min(usable // es, model.total_expert_count)
        ssd_experts = max(0, model.total_expert_count - pooled_experts)

        bytes_per_token = es * model.top_k_routing * model.num_layers
        nvme = max(profile.nvme_speed_bytes_per_sec, 1)
        cold_toks = nvme / bytes_per_token
        hit_rate = min(0.98, pooled_experts / max(model.total_expert_count, 1))
        # Everything resident is served at unified-memory bandwidth —
        # no PCIe hop — so warm and hot converge much sooner than on a
        # discrete card.
        pool_toks = (getattr(profile, "unified_bandwidth_gb_s", 0) * 1e9
                     / bytes_per_token)
        warm_toks = hit_rate * pool_toks + (1 - hit_rate) * cold_toks
        hot_toks = warm_toks * 1.15
        acc = model.default_acceptance_rate

        drafter_cfg = select_drafter_config(
            free_vram_bytes=usable,
            drafter_id=model.drafter_hf_id,
            drafter_type=model.get_drafter_config()["type"])

        return TierConfig(
            vram_expert_count   = int(pooled_experts),
            ram_expert_count    = 0,       # same physical memory
            ssd_expert_count    = int(ssd_experts),
            gpu_strategy        = "unified",
            primary_gpu         = 0,
            secondary_gpu       = None,
            drafter_id          = drafter_cfg["id"],
            drafter_location    = drafter_cfg["location"],
            drafter_dtype       = drafter_cfg["dtype"],
            expected_acceptance = drafter_cfg["acceptance"],
            omp_thread_count    = profile.cpu_threads,
            estimated_cold_toks = round(cold_toks, 2),
            estimated_warm_toks = round(warm_toks, 2),
            estimated_hot_toks  = round(hot_toks, 2),
            estimated_mtp_toks  = round(
                hot_toks * (1.0 + acc * float(model.mtp_k)), 2),
            tier_mode           = "unified",
            backend             = "unified",
            unified_pool_gb     = float(
                getattr(profile, "unified_memory_gb", 0)),
            bandwidth_gb_s      = float(
                getattr(profile, "unified_bandwidth_gb_s", 0)),
            vendor              = "nvidia",
        )

    def calculate(self, profile: SystemProfile,
                  model: ModelAdapter) -> TierConfig:
        es    = model.expert_size_bytes
        nl    = model.num_layers
        topk  = model.top_k_routing
        total = model.total_expert_count

        # Dense layers always claim their tier first.
        # The VRAM buffer is dynamic: 500MB base (CUDA context, KV
        # growth, scratch) + 1.5GB when the monitor is detected on the
        # GPU (0 when it's on the iGPU — full VRAM for inference).
        dense = model.dense_layer_size_bytes

        # ---- DGX Spark: unified memory ------------------------------- #
        # CPU and GPU share one coherent pool, so the VRAM/RAM boundary
        # WISP normally plans around does not physically exist. Two tiers
        # remain: unified pool -> NVMe. There is no RAM->VRAM copy to
        # hide, and no desktop compositor competing for the card.
        if getattr(profile, "accelerator", "cuda") == "unified":
            return self._unified_config(profile, model)

        BUFFER = (C.VRAM_SAFETY_BUFFER
                  + getattr(profile, "display_reserved_bytes", 0))

        # RAM must NEVER fill completely — a starved desktop compositor
        # freezes/blacks the whole machine (observed live 2026-07-19 on
        # the Mixtral validation runs). Reserve max(6GB, 25% of total)
        # for the OS, always.
        total_ram = profile.total_ram_bytes
        OS_BUFFER = max(6 * 1024**3, int(total_ram * 0.25))

        # Hard VRAM ceiling: WISP (dense + expert cache) never plans past
        # 75% of the card, whatever the display routing says.
        MAX_VRAM_FRACTION = 0.75

        if profile.gpu_count > 0:
            vram_total = profile.gpus[profile.primary_gpu_index].vram_total_bytes
            vram_cap = int(vram_total * MAX_VRAM_FRACTION)
            usable = min(vram_cap, vram_total - BUFFER)
            vram_for_experts = max(0, usable - dense)
            ram_reserved = OS_BUFFER
        else:
            # CPU-only: dense layers live in RAM instead
            vram_for_experts = 0
            ram_reserved = OS_BUFFER + dense

        vram_experts = vram_for_experts // es

        ram_for_experts = max(0, profile.available_ram_bytes - ram_reserved)
        ram_experts = ram_for_experts // es

        # Multi-GPU: secondary GPUs contribute pure expert cache
        strategy = pick_gpu_strategy(profile.gpus)
        if strategy.mode in ("dual_same", "dual_diff") and strategy.secondary is not None:
            sec_vram = profile.gpus[strategy.secondary].vram_total_bytes
            vram_experts += max(0, sec_vram - BUFFER) // es
        elif strategy.mode == "pipeline" and strategy.gpus:
            # Each pipeline stage holds its layer slice's dense weights;
            # remaining VRAM across all GPUs becomes expert cache.
            extra = 0
            for g in strategy.gpus[1:]:
                extra += max(0, profile.gpus[g].vram_total_bytes
                             - dense // len(strategy.gpus) - BUFFER)
            vram_experts += extra // es

        vram_experts = min(vram_experts, total)
        ram_experts = min(ram_experts, max(0, total - vram_experts))
        ssd_experts = max(0, total - vram_experts - ram_experts)

        # ------------------------------------------------------------ #
        # Performance math — the correct per-token bytes formula
        # ------------------------------------------------------------ #
        bytes_per_token = es * topk * nl
        nvme_speed = max(profile.nvme_speed_bytes_per_sec, 1)
        cold_toks = nvme_speed / bytes_per_token

        # Cache hit rate empirical formula (saturates at 93%)
        silicon = vram_experts + ram_experts
        hit_rate = min(0.93, 0.35 + (silicon / max(total, 1)) * 10.0)
        hit_rate = max(0.0, hit_rate)

        warm_toks = (hit_rate * 0.35 * C.VRAM_HIT_TOKS +
                     hit_rate * 0.65 * C.RAM_HIT_TOKS +
                     (1 - hit_rate) * cold_toks)
        hot_toks = warm_toks * 1.5

        acc = model.default_acceptance_rate
        mtp_effective = hot_toks * (1.0 + acc * float(model.mtp_k))

        drafter_cfg = select_drafter_config(
            free_vram_bytes=vram_for_experts,
            drafter_id=model.drafter_hf_id,
            drafter_type=model.get_drafter_config()["type"],
        )

        return TierConfig(
            vram_expert_count   = int(vram_experts),
            ram_expert_count    = int(ram_experts),
            ssd_expert_count    = int(ssd_experts),
            gpu_strategy        = strategy.mode,
            primary_gpu         = strategy.primary,
            secondary_gpu       = strategy.secondary,
            drafter_id          = drafter_cfg["id"],
            drafter_location    = drafter_cfg["location"],
            drafter_dtype       = drafter_cfg["dtype"],
            expected_acceptance = drafter_cfg["acceptance"],
            omp_thread_count    = profile.cpu_threads,
            estimated_cold_toks = round(cold_toks, 2),
            estimated_warm_toks = round(warm_toks, 2),
            estimated_hot_toks  = round(hot_toks, 2),
            estimated_mtp_toks  = round(mtp_effective, 2),
            tier_mode           = "3tier",
            backend             = ("rocm"
                                   if getattr(profile, "accelerator", "")
                                   == "rocm" else "cuda"),
            vendor              = ("amd"
                                   if getattr(profile, "amd_gpu", None)
                                   else "nvidia"),
            gfx_target          = ((profile.amd_gpu or {}).get(
                                       "gfx_target", "")
                                   if getattr(profile, "amd_gpu", None)
                                   else ""),
        )
