"""
wisp.models.constants
=====================

Single source of truth for every measured / estimated architecture number
WISP relies on. All sizes are bytes unless the name says otherwise.

CRITICAL MATH (used everywhere — do not "simplify"):

    expert lookups per token = TOP_K_ROUTING[family] x NUM_LAYERS[family]
    bytes per cold token     = EXPERT_SIZE_INT4[family] x lookups_per_token

    GLM-5.2:     8 x 61 = 488 lookups -> 18,350,080 x 488 = ~8.54 GB/token
    DeepSeek-V3: 8 x 58 = 464 lookups
    DeepSeek-R1: 8 x 58 = 464 lookups
    Kimi K3:     16 x 94 = 1,504 lookups (top-16 CONFIRMED by Moonshot,
                 July 2026; layer count estimated until the technical
                 report drops July 27)
"""

from __future__ import annotations

# ---------------------------------------------------------------------------
# Unit helpers
# ---------------------------------------------------------------------------
KB = 1024
MB = 1024 * KB
GB = 1024 * MB
TB = 1024 * GB

# ---------------------------------------------------------------------------
# Expert sizes (int4 quantized, one expert = gate + up + down projections)
# ---------------------------------------------------------------------------
EXPERT_SIZE_INT4: dict[str, int] = {
    "glm52":       18_350_080,  # 17.5 MB — measured by Colibrì community
    "deepseek_v3": 17_825_792,  # ~17.0 MB — estimated (similar arch to GLM)
    "deepseek_r1": 17_825_792,  # Same as V3
    "kimi_k3":     22_020_096,  # ~21.0 MB — estimated (larger hidden dim)
    "mixtral_8x7b":  99_090_552,   # MEASURED from real conversion 2026-07-19
                                   # (176.2M params x 0.5625 B/param + header)
    "mixtral_8x22b": 169_869_552,  # computed: 302.0M params x 0.5625 + header
}

# ---------------------------------------------------------------------------
# Dense (non-expert) weights: attention, embeddings, shared experts, norms.
# These ALWAYS load to GPU VRAM first (or RAM in CPU-only mode).
# ---------------------------------------------------------------------------
DENSE_SIZE: dict[str, int] = {
    "glm52":       9_900_000_000,   # 9.9 GB — measured by Colibrì
    "deepseek_v3": 9_500_000_000,   # Estimated
    "deepseek_r1": 9_500_000_000,   # Same as V3
    "kimi_k3":    12_000_000_000,   # Estimated (larger model)
    "mixtral_8x7b":   3_211_293_768,   # MEASURED (fp16 dense safetensors)
    "mixtral_8x22b": 10_700_000_000,   # computed from architecture (~10.7 GB)
}

NUM_LAYERS: dict[str, int] = {
    "glm52":       61,
    "deepseek_v3": 58,
    "deepseek_r1": 58,
    "kimi_k3":     94,   # ESTIMATED — update when tech report drops July 27
    "mixtral_8x7b":  32,
    "mixtral_8x22b": 56,
}

TOP_K_ROUTING: dict[str, int] = {
    "glm52":       8,
    "deepseek_v3": 8,
    "deepseek_r1": 8,
    "kimi_k3":     16,   # CONFIRMED — official Moonshot sources, July 2026
    "mixtral_8x7b":  2,
    "mixtral_8x22b": 2,
}

NUM_EXPERTS_PER_LAYER: dict[str, int] = {
    "glm52":       256,
    "deepseek_v3": 256,
    "deepseek_r1": 256,
    "kimi_k3":     896,  # CONFIRMED — official Moonshot sources, July 2026
    "mixtral_8x7b":  8,
    "mixtral_8x22b": 8,
}

NUM_SHARED_EXPERTS: dict[str, int] = {
    "glm52":       2,
    "deepseek_v3": 1,
    "deepseek_r1": 1,
    "kimi_k3":     1,   # Estimated
    "mixtral_8x7b":  0,   # pure routed MoE — no shared experts
    "mixtral_8x22b": 0,
}

TOTAL_PARAMETERS: dict[str, int] = {
    "glm52":       744_000_000_000,
    "deepseek_v3": 671_000_000_000,
    "deepseek_r1": 671_000_000_000,
    "kimi_k3":   2_800_000_000_000,
    "mixtral_8x7b":   46_700_000_000,
    "mixtral_8x22b": 141_000_000_000,
}

HIDDEN_SIZE: dict[str, int] = {
    "glm52":       7168,
    "deepseek_v3": 7168,
    "deepseek_r1": 7168,
    "kimi_k3":     8192,  # Estimated
    "mixtral_8x7b":  4096,
    "mixtral_8x22b": 6144,
}

VOCAB_SIZE: dict[str, int] = {
    "glm52":       151_552,
    "deepseek_v3": 129_280,
    "deepseek_r1": 129_280,
    "kimi_k3":     160_000,  # Estimated
    "mixtral_8x7b":  32_000,
    "mixtral_8x22b": 32_000,
}

ATTENTION_TYPE: dict[str, str] = {
    "glm52":       "MLA",
    "deepseek_v3": "MLA",
    "deepseek_r1": "MLA",
    # KDA (Kimi Delta Attention) — CONFIRMED. Hybrid linear attention;
    # runs as a GQA placeholder in the engine until the July 27 tech
    # report publishes the full mechanism.
    "kimi_k3":     "KDA",
    "mixtral_8x7b":  "GQA",   # 32 query heads / 8 KV heads
    "mixtral_8x22b": "GQA",   # 48 query heads / 8 KV heads
}

MAX_POSITION_EMBEDDINGS: dict[str, int] = {
    "glm52":       1_048_576,
    "deepseek_v3":   163_840,
    "deepseek_r1":   163_840,
    "kimi_k3":     1_000_000,  # CONFIRMED — 1M-token context window
    "mixtral_8x7b":     32_768,
    "mixtral_8x22b":    65_536,
}

# ---------------------------------------------------------------------------
# Hugging Face model ids
# ---------------------------------------------------------------------------
HF_MODEL_ID: dict[str, str] = {
    "glm52":       "zai-org/GLM-5.2",
    "deepseek_v3": "deepseek-ai/DeepSeek-V3",
    "deepseek_r1": "deepseek-ai/DeepSeek-R1",
    "kimi_k3":     "moonshotai/Kimi-K3",
    "mixtral_8x7b":  "mistralai/Mixtral-8x7B-Instruct-v0.1",
    "mixtral_8x22b": "mistralai/Mixtral-8x22B-Instruct-v0.1",
}

# ---------------------------------------------------------------------------
# Speculative decoding — same-family drafters
# ---------------------------------------------------------------------------
DRAFTER_HF_ID: dict[str, str] = {
    # GLM-5.2 uses the native int8 MTP head fixed by matey-0 (Mateo Grgić):
    # int4 head gave 0-4% acceptance; int8 restores 39-59%.
    "glm52":       "matey-0/GLM-5.2-mtp-int8",
    "deepseek_v3": "deepseek-ai/DeepSeek-R1-Distill-Qwen-1.5B",
    "deepseek_r1": "deepseek-ai/DeepSeek-R1-Distill-Qwen-1.5B",
    # Kimi K2 (1T) drafts for K3 when available; runs through the dense
    # drafter path (same fallback as the DeepSeek distill drafters).
    "kimi_k3":     "moonshotai/Kimi-K2",
    "mixtral_8x7b":  "mistralai/Mistral-7B-Instruct-v0.3",
    # Mixtral 8x7B drafts for 8x22B — same family, same tokenizer
    "mixtral_8x22b": "mistralai/Mixtral-8x7B-Instruct-v0.1",
}

DEFAULT_ACCEPTANCE_RATE: dict[str, float] = {
    "glm52":       0.49,
    "deepseek_v3": 0.48,
    "deepseek_r1": 0.48,
    "kimi_k3":     0.42,
    "mixtral_8x7b":  0.41,
    "mixtral_8x22b": 0.38,
}

# Approximate drafter footprints for the VRAM fit logic (bytes).
DRAFTER_SIZE_FP16: dict[str, int] = {
    "matey-0/GLM-5.2-mtp-int8":                    1_200 * MB,  # int8 head, fp16 slot
    "deepseek-ai/DeepSeek-R1-Distill-Qwen-1.5B":   3_600 * MB,
    "moonshotai/Kimi-K2":                          2_000 * GB,  # 1T model — never fits VRAM
    "mistralai/Mistral-7B-Instruct-v0.3":         14_500 * MB,
    "mistralai/Mixtral-8x7B-Instruct-v0.1":       93_000 * MB,
}

DRAFTER_SIZE_INT4: dict[str, int] = {
    "matey-0/GLM-5.2-mtp-int8":                      600 * MB,
    "deepseek-ai/DeepSeek-R1-Distill-Qwen-1.5B":     800 * MB,
    "moonshotai/Kimi-K2":                            550 * GB,  # -> CPU path
    "mistralai/Mistral-7B-Instruct-v0.3":          3_900 * MB,
    "mistralai/Mixtral-8x7B-Instruct-v0.1":       24_000 * MB,
}

# ---------------------------------------------------------------------------
# On-disk footprint of a fully converted int4 model (README-published)
# ---------------------------------------------------------------------------
DISK_SIZE_INT4: dict[str, int] = {
    "glm52":       370 * GB,
    "deepseek_v3": 340 * GB,
    "deepseek_r1": 340 * GB,
    "kimi_k3":    1400 * GB,   # ~1.4 TB estimated
    "mixtral_8x7b":   27 * GB,   # MEASURED 26.6 GB (3.2 dense + 25.4 experts)
    "mixtral_8x22b":  90 * GB,   # computed: 76 GB experts + 10.7 GB dense
}

# ---------------------------------------------------------------------------
# Quantization defaults
# ---------------------------------------------------------------------------
DEFAULT_QUANT_GROUP_SIZE = 64
DEFAULT_WEIGHT_DTYPE = "int4"

# ---------------------------------------------------------------------------
# Tier allocation buffers
# ---------------------------------------------------------------------------
# BASE VRAM headroom: CUDA context + KV-cache growth + activation
# scratch + safety margin. The desktop compositor's slice is handled
# separately and dynamically: AutoConfig adds profile.display_reserved_
# bytes (1.5GB when the monitor is on the GPU, 0 when it's on the iGPU
# — auto-detected via nvidia-smi display_active). Measured on the first
# real Mixtral run 2026-07-19: a flat 500MB alone OOM'd at ~78 of a
# budgeted 91 slots with the display on-GPU. The allocator also evicts
# on OOM now, so this sets the *plan*, not a hard cliff.
VRAM_SAFETY_BUFFER = 500 * MB
RAM_OS_BUFFER = 4 * GB             # Left for OS + drafter overhead

# Empirical serving speeds used by the auto-config estimator (tok/s).
VRAM_HIT_TOKS = 22.0
RAM_HIT_TOKS = 4.5


def expert_lookups_per_token(family: str) -> int:
    """top_K x num_layers — the number a single generated token costs."""
    return TOP_K_ROUTING[family] * NUM_LAYERS[family]


def bytes_per_cold_token(family: str) -> int:
    """Bytes read from SSD for one fully-cold token."""
    return EXPERT_SIZE_INT4[family] * expert_lookups_per_token(family)


def total_expert_count(family: str) -> int:
    return NUM_EXPERTS_PER_LAYER[family] * NUM_LAYERS[family]
