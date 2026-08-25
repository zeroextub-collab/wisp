# WISP

> Stream what shouldn't run.

[![Tests](https://img.shields.io/badge/tests-197%20passing-brightgreen)]()
[![Version](https://img.shields.io/badge/version-2.0.0-blue)]()
[![CUDA](https://img.shields.io/badge/CUDA-12.0%2B%20%7C%2013.x-76b900)]()
[![Python](https://img.shields.io/badge/python-3.10%2B-blue)]()
[![DGX Spark](https://img.shields.io/badge/DGX_Spark-unified_memory-blueviolet)]()
[![ROCm](https://img.shields.io/badge/ROCm-7.0%2B_detection-red)]()
[![License](https://img.shields.io/badge/license-MIT-green)]()
[![Models](https://img.shields.io/badge/models-GLM--5.2%20%7C%20DeepSeek%20%7C%20Mixtral%20%7C%20Kimi%20K3%20%7C%20Qwen3-orange)]()

WISP runs the largest open-source AI models ever built
on the hardware sitting on your desk.

A 744B parameter frontier model. A 671B reasoning engine.
A 2.8 trillion parameter behemoth, weights already public.

Not a slow demo. Not quantized to uselessness.
The full model, at full frontier intelligence,
streaming expert weights across GPU VRAM, system RAM,
and your NVMe SSD in real time.

---

## v2.0 — What Just Shipped

Five updates. Where something is detected but not benchmarked, or wired
but not run on real weights, this section says so.

**Kimi K3 — KDA complete, names still unverified.**
The KDA kernel is implemented in CUDA with a matching pure-PyTorch
fallback, the converter maps KDA projection weights into the dense
file, and the C forward pass branches by layer type. The recurrence:

```
qn, kn = q/||q||, k/||k||       L2-normalized per head
b      = sigmoid(W_beta x)      per-channel write gate, in (0,1)
u      = S^T kn                 what memory currently holds at this key
S      = S + b * kn (v - u)^T   write the PREDICTION ERROR
o      = S^T qn                 read, using the new state
y      = silu(g) * o            output gate
```

Numerically verified at head_dim 32, 100 and 200. The 200 case covers
the partial-thread-block barrier path, where a mistake hangs the GPU
rather than returning a wrong number. What is **not** verified is the
checkpoint's tensor names — no K3 checkpoint has been converted with
this code. `wisp inspect` prints the names a checkpoint really uses and
`WISP_KDA_NAMES` maps them, so that gap is closable without a code
change. See [KDA](#kda--kimi-delta-attention) below.

**Qwen3-235B and Qwen3-2.4T adapters.**
GQA-based, not MLA. The adapter reads `num_hidden_layers`,
`num_experts`, `num_experts_per_tok` and `moe_intermediate_size` from
`config.json` at conversion time rather than hardcoding them, so an
architecture revision does not need an adapter revision. Qwen3-235B:
top-8 of 128 experts across 94 MoE layers = **752 lookups/token**.
Qwen3-2.4T's real config is not public yet, so its figures come from
placeholder constants and are marked estimated.

**Desktop GUI — `wisp-gui`.**
A native desktop app, not a wrapper around the CLI: it hosts the same
`WispServer` in a background thread on a private loopback port and
talks to it over the OpenAI API, so the path it exercises is the one
Cursor and Open WebUI use. Live tier monitor, tok/s counter, cache hit
rate, streaming chat. No new inference path.

**DGX Spark — unified memory mode.**
Detected automatically, and only when all three of aarch64, a
GB10-class device name, and a ~128GB reported pool agree. The 3-tier
hierarchy collapses to 2: unified pool (128GB, 273 GB/s) → NVMe SSD.
Two NVLinked Sparks are detected as a 256GB pool. **Detection and tier
planning are implemented; no Spark has been benchmarked.**

**AMD Radeon AI PRO R9700 — ROCm detection.**
Detected via `rocm-smi`: 32GB GDDR6, 640 GB/s, gfx1201. `wisp doctor`
reports the card and the tier planner sizes for it, including multiple
cards pooling. **Detection only** — WISP's compute kernels are CUDA and
inference does not run on an R9700 yet. The HIP port is v2.1.

---

## The Numbers

| Model | Parameters | Active/token | Lookups/token | Disk (int4) | Status |
|-------|-----------|-------------|--------------|-------------|--------|
| GLM-5.2 | 744B | 40B | 488 | ~370 GB | ✅ Ready |
| DeepSeek-V3 | 671B | 37B | 464 | ~340 GB | ✅ Ready |
| DeepSeek-R1 | 671B | 37B | 464 | ~340 GB | ✅ Ready |
| Mixtral-8x7B | 47B | 13B | 64 | 26.6 GB* | ✅ **Verified end-to-end** |
| Mixtral-8x22B | 141B | 39B | 112 | ~90 GB | ✅ Ready |
| Kimi K3 | 2.8T | 104B | 1,488 | ~1.4 TB | ⚠️ KDA wired, names unverified |
| Qwen3-235B-A22B | 235B | 22B | 752 | ~130 GB | ✅ Ready |
| Qwen3-2.4T | 2.4T | ~22B est. | config-driven | ~1.2 TB est. | ✅ Adapter ready — weights pending |
| GLM-5.3 | TBD | TBD | TBD | TBD | 🔜 Day-0 stub |

*Measured from a real conversion — every expert file verified.
"Verified end-to-end" means: downloaded, converted, and generated
real tokens through the full C + CUDA engine on consumer hardware.

---

> **July 2026 — The Biggest Week in Open Source AI**
>
> Kimi K3 (2.8T parameters) dropped July 17 — the largest
> open source model ever released.
> Qwen3.8 (2.4T parameters) announced July 19 — open weights
> coming soon.
> WISP was built for exactly this moment.
> Both are MoE models. Both stream with WISP.

---

## How It Works

Every MoE (Mixture-of-Experts) model activates only
a small fraction of its parameters for each token.
GLM-5.2 activates ~5.4%. Kimi K3 activates 3.7% (104B of 2.8T).
WISP exploits this with a self-organizing 3-tier cache:

```
Token arrives
    ↓
Model's own router selects which experts to activate
    ↓
WISP checks VRAM first  → instant if hit
    ↓
Then RAM                → one PCIe copy if hit
    ↓
Then NVMe SSD           → streams if cold
    ↓
LRU cache promotes hot experts upward automatically
After 10-15 min: high cache hit rate, self-organized
(measured: 68.8% hit rate after only 80 tokens)
No configuration. No preset modes. Fully automatic.
```

### Absorbed MLA Attention

GLM-5.2 and DeepSeek use Multi-head Latent Attention (MLA).
WISP implements true absorbed MLA — the KV cache stores the
compressed `c_kv` latent instead of expanded K,V tensors.
Result: **~70KB per token** KV cache instead of ~5MB.
This is what makes 1M-token context feasible in RAM.

### KDA — Kimi Delta Attention

Kimi K3 runs linear attention in 69 of its 93 layers. Instead of a KV
cache that grows with the conversation, each head carries a fixed
`[d_k, d_v]` state matrix updated by a delta rule:

```
qn, kn = q/||q||, k/||k||     L2-normalized per head
b      = sigmoid(W_beta x)    per-channel write gate, in (0,1)
u      = S^T kn               what memory currently holds at this key
S      = S + b * kn (v - u)^T write the PREDICTION ERROR
o      = S^T qn               read, using the new state
y      = silu(g) * o          output gate
```

Three details carry the whole thing:

**It writes `v - u`, not `v`.** That is what makes it a *delta* rule —
the state is corrected by exactly the amount it was wrong by, so
re-writing a key that is already stored is a no-op instead of doubling
it. Plain linear attention (`S += v k^T`) accumulates and saturates.

**q and k are L2-normalized**, which bounds the update. Without it the
state diverges: measured at `inf` within 200 tokens at moderate input
scale. A constant-size state is worthless if its contents blow up.

**The read happens after the write**, so a token can see its own value.
Reading first makes the first token of every conversation emit exactly
zero.

Cost is O(n) in sequence length and **memory is constant** — that is the
property that makes 1M-token context tractable at all.

WISP implements KDA as a CUDA kernel with a matching pure-PyTorch
fallback for CPU-only mode. The kernel normalizes internally rather than
trusting its callers, so the C engine, the Python bindings and the
fallback cannot drift apart. Tests assert the two paths agree
numerically at head_dim 32, 100 and 200, that prefill lands on the same
state as sequential decode, that repeated writes converge on the stored
value, that the state stays bounded over 2,000 tokens, and that batch
entries do not contaminate each other. The other 24 K3 layers are Gated
MLA and already run through WISP's absorbed-MLA path.

**Status — read this before converting K3.** The kernel is implemented
and numerically verified, the converter maps KDA projections into the
dense weight file, and the C engine takes a per-layer KDA branch when
those projections load. What is *not* verified is the checkpoint's
tensor NAMES: the technical report describes the mechanism, not the
layout, and no K3 checkpoint has been converted with this code yet.

So the names are a wide net plus an escape hatch rather than a guess:

```bash
wisp inspect --source ./k3-shards --model kimi-k3
```

prints the tensor names the checkpoint actually uses and marks which
KDA projections matched. If any are unmatched, map them by hand and
convert without patching WISP:

```bash
WISP_KDA_NAMES='{"beta": "<real_name>"}' wisp convert --model kimi-k3 ...
```

`wisp convert` also reports its match count and refuses to be quiet
about a shortfall — an unmatched projection drops that layer onto the
GQA path, and the output is wrong rather than merely slow. Sending the
real names to the issue tracker gets them into the defaults for
everyone else.

### Double-Buffer Async Pipeline

While the GPU computes token N (2-8ms),
the C engine loads token N+1's predicted experts from SSD
into pinned RAM, and the transfer stream moves them to VRAM
(0.1-0.3ms) — fully hidden inside the compute window.
GPU never waits on predicted experts. Works on all consumer
hardware. No GPUDirect Storage required.

### Speculative Decoding

Same-family small models draft 3 tokens simultaneously.
The main model verifies all 3 in one parallel forward pass.
At 39-55% acceptance rate: 2.2-2.8x effective throughput.
Zero quality loss — the rejection-sampling scheme provably
preserves the main model's output distribution (Leviathan 2023).

### Display Auto-Detection

WISP detects whether your monitor is on the GPU or the
motherboard (via the driver itself) and reserves VRAM
accordingly. Move the monitor to the motherboard port →
WISP auto-detects → full VRAM dedicated to inference.
Override anytime with `--display-mode gpu|igpu|auto`.

### Learning Cache — it gets faster the more you use it

WISP records which experts your sessions actually activate, in
`{model_dir}/.wisp_usage`. On the next startup the hottest ones are
queued for pre-warming before the first token is generated.

```
session 1   cold start; the LRU discovers your domain
session 2   last session's top experts pre-warmed at startup
session 7   near-instant warm start
```

Expert selection happens inside the C router, so the engine keeps a
ring-buffer log of every (layer, expert) access that the runtime drains
every 10 tokens — that stream feeds both the next-token prefetch
predictor and the cross-session cache. Measured on a real Mixtral run:
12 tokens produced 768 expert observations and 238 tracked experts, of
which 107 were pre-warmed on the following startup.

```bash
wisp cache --model ./models/glm-5.2/ --show    # what it has learned
wisp cache --model ./models/glm-5.2/ --reset   # start over
```

Ranking blends frequency with a recency decay, so a cache trained on
three weeks of Rust adapts when you switch to prose instead of staying
stuck on the old domain. The file is plain JSON — inspect it, diff it,
or delete it.

### OpenAI-Compatible API Server

```bash
wisp serve --model ./models/glm-5.2/ --port 8080
```

Anything that speaks the OpenAI API now speaks to WISP — Cursor,
Continue.dev, Open WebUI, LM Studio frontends, the `openai` package:

```python
from openai import OpenAI
client = OpenAI(base_url="http://localhost:8080/v1", api_key="wisp")
client.chat.completions.create(
    model="glm-5.2",
    messages=[{"role": "user", "content": "Write a quicksort"}],
    stream=True,
)
```

`/v1/chat/completions` (streaming + non-streaming), `/v1/models`,
`/health`, and `/v1/stats` for WISP's own numbers (tok/s, tier hit
breakdown, learning-cache state). Streaming is genuinely incremental —
the engine's generator runs on a worker thread feeding the event loop,
so the first token reaches the client as soon as it exists rather than
after the whole completion. Prompts are rendered with each family's own
chat template. Requests are serialized: one engine, one KV cache, so
concurrent decoding would interleave two conversations.

Install the extra: `pip install -e '.[server]'`

### Stability Guarantees

- System RAM is never allowed to fill: `max(6GB, 25%)` is
  always reserved for the OS, and a runtime watermark evicts
  RAM-tier experts past 80% usage (SSD stays authoritative,
  so eviction is always safe).
- VRAM planning is hard-capped at 75% of the card, and the
  allocator degrades gracefully (evict-and-retry) if the
  driver's real ceiling is lower than the plan.

---

## Desktop GUI

`wisp-gui` is a native desktop app that connects to the `wisp serve`
API server running locally.

```bash
pip install -e '.[gui]'
wisp-gui
```

Point it at your converted model directory. The GUI starts `wisp serve`
internally on a private loopback port.

Features:
- Token stream with live tok/s counter
- Tier monitor: VRAM / RAM / NVMe usage live from `/v1/stats`
- Cache hit rate and expert observation count
- Temperature, max_tokens, system prompt controls
- Dark theme

Three columns: model + generation controls on the left, chat in the
middle, live tier and engine monitors on the right. The tier bars show
VRAM and RAM occupancy against this machine's real capacities, refreshed
every two seconds.

The GUI is not a wrapper around the CLI — it never shells out or parses
terminal output. It hosts the very same `WispServer` in a background
thread and talks to it over the OpenAI API, so the path it exercises is
byte-for-byte the one Cursor and Open WebUI use. Closing the window
shuts the server down cooperatively, which is what lets the learning
cache persist.

Screenshots welcome — open a GitHub Issue to submit yours.

---

## Performance

*First verified on: R7 9800X3D | RTX 5070 12GB |
32GB DDR5-6000 | PCIe 4.0 NVMe*

| Model | Cold | Warm | Hot | +MTP Effective |
|-------|------|------|-----|----------------|
| Mixtral-8x7B | **0.75 tok/s** ✅ measured | est. 2-5 tok/s* | est. 5-10 tok/s* | est. ~2x* |
| GLM-5.2 | est. 0.7 tok/s* | est. 5.5 tok/s* | est. 8.5 tok/s* | est. ~14 tok/s* |
| DeepSeek-V3/R1 | est. 0.8 tok/s* | est. 5.8 tok/s* | est. 9.0 tok/s* | est. ~14.5 tok/s* |
| Kimi K3 | est. 0.2 tok/s* | est. 3 tok/s* | est. 6 tok/s* | est. ~10 tok/s* |

*Cold = empty cache, first run. Warm = 15 min same domain.
Hot = repeated patterns, cache fully warmed.
MTP = with speculative decoding active.
\* = estimated from physics (expert size × lookups ÷ transfer
bandwidth); real benchmarks land in v2.1. **Measured Mixtral
data (2026-07-19):** 81 tokens at 0.75 tok/s from a completely
cold engine, 68.8% cache hit rate after 80 tokens; a 300-token
cold run averaged 0.56 tok/s on an earlier engine build. We do
not publish a bold number we didn't measure.*

### Why Mixtral is Slower Than GLM-5.2 (yes, slower)

Mixtral 8x7B experts = **99MB each** (measured).
GLM-5.2 experts = **17.5MB each** — 5.7× smaller.

Cold decode is transfer-bound: every uncached expert crosses
PCIe or comes off the NVMe. Smaller experts = less data per
token = faster streaming and faster cache warm-up. Mixtral is
WISP's proving ground; GLM-5.2's fine-grained experts are
where the architecture truly sings.

---

## Quick Start

```bash
git clone https://github.com/zeroextub-collab/wisp
cd wisp
pip install -e .            # builds the C + CUDA engine (see Installation)
wisp doctor                 # confirm the toolchain found everything

wisp convert --model glm-5.2 --output ./models/
wisp chat --model ./models/glm-5.2/
```

```bash
# Desktop GUI
pip install -e '.[gui]'
wisp-gui
```

> **Not on PyPI yet.** WISP builds a CUDA extension against your local
> toolchain, so it installs from source today — `pip install wisp-engine`
> will not work. (Note also that the name `wisp` on PyPI belongs to an
> unrelated project.) Prebuilt wheels are tracked in the roadmap.

---

## Requirements

| Component | Minimum | Recommended |
|-----------|---------|-------------|
| RAM | 16 GB | 32 GB+ |
| NVMe SSD | PCIe 3.0, 300 GB free | PCIe 5.0, 2 TB dedicated |
| GPU | None (CPU-only works) | RTX 3080+ / 8 GB+ VRAM |
| CUDA | 12.0+ | 12.8+ (required for RTX 50 series) |
| Python | 3.10+ | 3.11 |
| OS | Windows 10+ / Ubuntu 20.04+ | Windows 11 / Ubuntu 22.04 |

---

## Installation

### Windows (x64 Native Tools Command Prompt)

```powershell
git clone https://github.com/zeroextub-collab/wisp
cd wisp
powershell -File scripts\install.ps1
```

### Linux

```bash
git clone https://github.com/zeroextub-collab/wisp
cd wisp
bash scripts/install.sh
```

### Manual

```bash
pip install torch --index-url https://download.pytorch.org/whl/cu128
pip install -e .
wisp doctor   # verify everything works
```

---

## Usage

```bash
# Convert a model (downloads + converts to WISP format,
# resumable, SHA256-verified, integrity-checked at the end)
wisp convert --model glm-5.2 --output ./models/

# One-shot inference
wisp run --model ./models/glm-5.2/ \
         --prompt "Write a Python web scraper" \
         --stream

# Interactive chat (/clear /stats /quit)
wisp chat --model ./models/glm-5.2/

# Benchmark your hardware (cold -> warm -> hot)
wisp benchmark --model ./models/glm-5.2/ --runs 3

# Check system compatibility
wisp doctor

# Show tier allocation for your hardware (works pre-download)
wisp info --model glm-5.2

# Print the tensor names a checkpoint actually uses, and which of them
# WISP matched (use before converting an unreleased/unverified model)
wisp inspect --source ./shards --model kimi-k3

# Verify model integrity, expert file by expert file
wisp verify --model ./models/glm-5.2/

# Share a converted model so others skip re-conversion
wisp upload --model ./models/glm-5.2/ --repo you/glm-5.2-wisp
```

### GUI

```bash
pip install -e '.[gui]'
wisp-gui
```

Opens the desktop app; point it at a converted model directory.

### Python API

```python
from wisp import WispEngine

engine = WispEngine("./models/glm-5.2/")

# Streaming
for token in engine.stream("Explain quantum entanglement"):
    print(token, end="", flush=True)

# One-shot
result = engine.generate("Write a sorting algorithm",
                         max_new_tokens=500,
                         temperature=0.7)
print(result)
```

---

## Multi-GPU Support

WISP automatically detects and configures multiple GPUs.
Zero manual configuration needed.

| Setup | Strategy | Best For |
|-------|----------|---------|
| Single GPU 8-12GB | Dense + expert LRU cache | Getting started |
| Single GPU 24GB+ | Dense + large expert cache | GLM-5.2 smooth |
| Dual GPU same size | GPU0 dense, GPU1 pure cache | 2× cache hits |
| Dual GPU diff sizes | Bigger=dense, smaller=overflow | Flexible |
| 3+ GPUs | Pipeline parallelism | Maximum throughput |

### NVIDIA Stacked Setups (projected)

| Setup | Combined VRAM | GLM-5.2 | Kimi K3 |
|-------|--------------|---------|---------|
| 2× RTX 4090 | 48GB | Smooth warm | Feasible |
| 4× RTX 4090 | 96GB | Near full cache | Good |
| 4× RTX 6000 Ada | 192GB | Full expert cache | Strong |

### AMD Radeon AI PRO R9700 (ROCm auto-detection in v2.0. Full HIP compute kernels: v2.1)

The R9700 is purpose-built for exactly what WISP does:
32GB GDDR6 per card, dual-slot blower for dense stacking,
PCIe 5.0, 1531 TOPS INT4.

| R9700 Stack | Combined VRAM | GLM-5.2 Coverage | Projected tok/s |
|-------------|--------------|-----------------|----------------|
| 1× R9700 | 32GB | Dense + 1,257 experts | 8-12 |
| 2× R9700 | 64GB | Dense + 3,085 experts | 18-25 |
| 4× R9700 | 128GB | Dense + 6,741 experts | 38-52 |

> **Note:** WISP now *detects* the R9700 through ROCm — `wisp doctor`
> reports the card, its VRAM, and the gfx1201 target, and the tier
> planner sizes for it. It does **not** run on it: the compute kernels
> are CUDA and the HIP port is separate work. All R9700 throughput
> figures above remain projections from the tier math, not measurements.
> `scripts/install_rocm.sh` sets up detection. Contributions welcome.

---

## Hardware Platforms

### NVIDIA CUDA — All Consumer GPUs

Standard 3-tier mode: VRAM → RAM → NVMe.
RTX 3080+ recommended. RTX 5070 (12GB) verified on Mixtral-8x7B.
CUDA 12.0+ | 13.x supported. CUDA 12.8+ required for RTX 50 series.

This is the only path that has been run end-to-end on real weights.

### NVIDIA DGX Spark — Unified Memory Mode

Grace Blackwell GB10. 128GB coherent LPDDR5x unified memory.
273 GB/s bandwidth. ARM64 (aarch64). $4,699.

WISP detects DGX Spark automatically and switches to unified mode:
- CPU and GPU share the same physical memory — no PCIe copy
- Expert cache: one 128GB pool instead of separate VRAM + RAM tiers
- Two DGX Sparks via NVLink: 256GB combined pool
- GLM-5.2 (744B): most experts fit in the 128GB pool
- Kimi K3 (2.8T): two-DGX NVLink path

Detection requires all three of aarch64, a GB10-class device name, and
a ~128GB reported pool — any one alone is not enough. The RAM→VRAM copy
that the double buffer exists to hide simply does not happen; prefetch
from NVMe still matters.

```bash
wisp doctor   # shows "DGX Spark detected — unified memory mode"
```

**Detection and tier planning are implemented; no Spark has been
benchmarked.** The figures above are hardware specifications, not WISP
measurements.

### AMD Radeon AI PRO R9700 — ROCm

32GB GDDR6. 640 GB/s. 1531 TOPS INT4. PCIe 5.0. $1,299.
Dual-slot blower — built for dense multi-GPU stacking.

WISP v2.0 detects R9700 via `rocm-smi` and sets auto-config.
Full ROCm compute kernels (HIP port of CUDA kernels): v2.1.
ROCm contributions welcome — see [CONTRIBUTING.md](CONTRIBUTING.md).

Setup: `scripts/install_rocm.sh` (Ubuntu) or `install_rocm.ps1`
(Windows). Both are detection-only; they do not make inference run on
the card.

---

## Architecture

```
User prompt
    ↓
WISP CLI / Python API
    ↓
Auto-Config Engine
  (profiles hardware once, calculates optimal tier split,
   detects display on GPU/iGPU, sets safe VRAM/RAM budgets)
    ↓
Universal Runtime (C + CUDA)
  ├── Double-Buffer Async Prefetch
  │     hides SSD transfer inside GPU compute time
  ├── 3-Tier LRU Cache
  │     VRAM (fastest) → RAM (fast) → SSD (cold)
  │     scratch-ring serving + hit-gated promotion:
  │     cool experts never churn the VRAM cache
  ├── Speculative Decoding
  │     same-family drafter → 2.2-2.8x throughput
  ├── Multi-GPU Router
  │     auto-selects: single / dual / pipeline strategy
  └── RAM Watermark Monitor
        evicts experts past 80% RAM — the desktop never starves
    ↓
The model's own router drives expert selection.
WISP just delivers them as fast as possible.
```

Three layers, one job each: **Python** orchestrates (download,
convert, configure — things that run once), **C** owns the hot
path (64-1,488 expert fetches per token, cache coordination,
prefetch threads), **CUDA** owns the math (absorbed MLA / GQA /
KDA attention, int4 dequant, fused SwiGLU FFN, router top-K).
The engine is model-agnostic: adapters map every family onto
one canonical weight layout at conversion time, so adding a model
is one adapter file — not a new engine.

On a coherent-memory machine the tier planner emits a two-tier
plan instead (unified pool → NVMe); nothing else in the stack
changes.

---

## Roadmap

### v1.0 — Shipped (August 1, 2026)
- Universal 3-tier MoE streaming engine (C + CUDA)
- Mixtral-8x7B and 8x22B full support — end-to-end verified
- GLM-5.2 (744B), DeepSeek-V3/R1 (671B) adapters
- Absorbed MLA attention (~70KB/token KV cache)
- KDA linear attention kernel (CUDA + PyTorch fallback)
- Double-buffer async prefetch pipeline
- Speculative decoding (39-55% acceptance, 2.2-2.8x throughput)
- OpenAI-compatible API server (`wisp serve`)
- Learning cache (cross-session expert pre-warming)
- Display auto-detection (VRAM conflict prevention)
- Multi-GPU support (single / dual / pipeline)
- 121 tests

### v2.0 — Shipping Now (August 2026)
- [x] Kimi K3 (2.8T): KDA converter weight mapping + C forward pass
      branch. Kernel numerically verified; checkpoint tensor names
      still unverified, with `wisp inspect` and `WISP_KDA_NAMES` as
      the escape hatch
- [x] Qwen3-235B and Qwen3-2.4T adapters
- [x] Desktop GUI (`wisp-gui`) — OpenAI client + live dashboard
- [x] DGX Spark unified memory mode (auto-detected, not benchmarked)
- [x] AMD R9700 ROCm detection + auto-config (detection only)
- 197 tests

### v2.1 — Next
- GLM-5.3 day-0 support (adapter stubbed, 24-48hr turnaround)
- Full ROCm compute kernels (HIP port — AMD R9700 full speed)
- Terminal UI dashboard
- Prebuilt wheels on PyPI, so `pip install wisp-engine` works without a
  local CUDA toolchain
- Warm/hot benchmark numbers from the community

### v3.0 — Community Driven
- Generic MoE adapter (any HuggingFace MoE model)
- GPUDirect Storage (Linux, datacenter GPUs)
- macOS / Metal backend
- Plugin system for community model profiles

### Still unmeasured — help wanted
- Real GLM-5.2 benchmark numbers
- Real DeepSeek-V3 benchmark numbers
- Warm/hot steady-state Mixtral numbers (long runs)
- A Kimi K3 conversion against real weights, to confirm the KDA
  tensor names WISP currently infers (`wisp inspect` prints them)
- A DGX Spark run, to replace the unified-mode projections

### Kimi K3 — where it stands

Architecture is confirmed (technical report arXiv:2607.24653):
93 layers = 69 KDA + 24 Gated MLA in a 3:1 interleave, 896 experts
per layer, top-16, 104B active. The 24 Gated MLA layers map onto
WISP's existing absorbed-MLA path; the 69 KDA layers run through the
CUDA linear-attention kernel shipped in v2.0.

What is **not** confirmed: the checkpoint's tensor names for the six
KDA projections. WISP matches a list of plausible spellings and the
converter prints how many it matched — if that count is 0, it says so
loudly, because the run would otherwise produce a model that loads
and generates nonsense. This resolves the first time anyone converts
real K3 weights.

---

## Credits

WISP would not exist without Colibrì.

**JustVugg** built Colibrì in July 2026 — a 2,400-line
pure-C engine that proved a 744B parameter model could
run on 25GB of consumer RAM by streaming expert weights
from disk. Before Colibrì, everyone said this was
impossible. After Colibrì, we built WISP.

**jlnsrk** converted the GLM-5.2 weights to a format
the community could actually use.

**matey-0 (Mateo Grgić)** fixed the MTP head from int4
(0-4% acceptance) to int8 (39-59% acceptance) —
turning speculative decoding from broken to genuinely
useful.

→ github.com/JustVugg/colibri

WISP shares zero code with Colibrì.
Complete independent reimplementation.
JustVugg showed us what was possible.

### Research

- Leviathan et al. 2023 — Speculative Decoding
- GLM team — GLM-5.2 and IndexShare MoE architecture
- DeepSeek team — DeepSeek-V3/R1 MoE + Multi-head Latent Attention
- Moonshot AI — *Kimi K3: Open Frontier Intelligence*
  ([arXiv:2607.24653](https://arxiv.org/abs/2607.24653)) — KDA hybrid
  linear attention, Stable LatentMoE routing
- The llama.cpp community — proof that consumer hardware
  deserves frontier models

Full tribute: [CREDITS.md](CREDITS.md)

---

## Contributing

See [CONTRIBUTING.md](CONTRIBUTING.md) for how to add new
model adapters, CUDA kernels, and platform support.

Community priorities:
- ROCm HIP kernel port (AMD R9700 full compute)
- GUI improvements and screenshots
- DGX Spark benchmarks
- Real benchmark submissions from different hardware
- Kimi K3 tensor names from a real checkpoint (`wisp inspect`)
- Model integrity verification improvements

---

## License

MIT License — see [LICENSE](LICENSE).

Built by **Saksham (Zero_planck)**
github.com/zeroextub-collab/wisp
