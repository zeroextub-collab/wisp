# Contributing to WISP

Thanks for wanting to make massive models run on small machines.

## Adding a New Model

The runtime is universal — supporting a new MoE family is (mostly) a
Python adapter:

1. Create `wisp/models/yourmodel.py`, subclassing `ModelAdapter`
   (see `wisp/models/glm52.py` for the shape of a complete adapter).
2. Fill in **every** `@property`: layer count, experts/layer, top-K,
   expert size, dense size, attention type, tokenizer specials, drafter.
   Mark estimated values with a comment — measured beats estimated.
3. Add the architecture numbers to `wisp/models/constants.py`
   (they're the single source of truth; adapters read from there).
4. Register the name spellings in `wisp/models/registry.py`.
5. If the HF tensor names differ from the DeepSeek-style default,
   override `canonical_dense_name()` / `expert_weight_pattern` so the
   converter can map them onto WISP's canonical layout.
6. Add a test to `tests/test_adapters.py` asserting the lookup math
   (`top_k x num_layers`) and identity fields.
7. Run `pytest tests/ -v`, then submit the PR with a link to the
   architecture source (paper, config.json, technical report).

New attention mechanisms (like KDA) additionally need a kernel path in
`csrc/cuda/attention.cu` + a CPU equivalent in `csrc/core/wisp_engine.c`
— open an issue first so we can plan it together.

## Adding a CUDA Kernel

1. Kernels live in `csrc/cuda/*.cu`, one file per concern
   (attention, routing, matmul, dequant, KV, speculative, multi-GPU).
2. Declare the `extern "C"` launcher in `csrc/core/wisp_engine.h`
   (section 7) — the C engine calls launchers, never kernels.
3. Every GPU op needs a CPU (OpenMP) twin in `wisp_engine.c` so the
   CPU-only build stays complete. The `DISPATCH` macro picks at runtime.
4. Threading uses `wisp_mutex_t` / `wisp_cond_t` ONLY (never raw
   pthread / CRITICAL_SECTION — see `wisp_engine.h` section 2).
5. Error handling uses `WispErrCtx` + the `WISP_CHECK_*` macros —
   no silent failures, no crashes.
6. Must compile under MSVC and gcc/clang, CUDA 12.0+ and 13.x,
   for `CMAKE_CUDA_ARCHITECTURES 75-120`.

## Running Tests

```bash
pytest tests/ -v
```

The C-engine tests (`test_lru_cache`, `test_double_buffer`, the
byte-layout cross-check) skip automatically if the extension isn't
built — a full run should show **0 skipped** on a working setup.

## Building the C Engine

Windows (x64 Native Tools Command Prompt for VS, CUDA 12.0+/13.x):

```
pip install -e .
```

Linux (gcc/clang + CUDA toolkit on PATH):

```
pip install -e .
```

CPU-only (no CUDA toolkit anywhere):

```
WISP_NO_CUDA=1 pip install -e .
```

Notes:
- A previously built engine in `wisp/` is reused; set `WISP_REBUILD=1`
  to force recompilation.
- If the Visual Studio CMake generator can't find CUDA, either copy the
  CUDA `MSBuildExtensions` into VS's `BuildCustomizations` (needs admin)
  or build with Ninja from a vcvars64 shell — see the README.

## Code Style

- Python: standard library logging via `wisp.logging.get_logger`,
  actionable error messages (say what broke AND what command fixes it).
- C: the existing files are the style guide — error contexts everywhere,
  comments explain *why*, ASCII-art math where it earns its place.
- The critical formula appears in many places on purpose:
  `lookups/token = top_K x num_layers`. If your change touches
  performance math, keep it consistent everywhere.
