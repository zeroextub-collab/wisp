"""
wisp.runtime.engine — WispEngine, the main Python API.

    from wisp import WispEngine
    engine = WispEngine("./models/glm-5.2/")
    print(engine.generate("Explain quantum entanglement simply"))
    for piece in engine.stream("Explain transformers"):
        print(piece, end="", flush=True)

Python never calls CUDA directly — everything on the hot path goes through
the C extension (wisp._wisp_core) built from csrc/.
"""

from __future__ import annotations

from pathlib import Path
from typing import Iterator

from ..converter.manifest import ModelManifest
from ..models.registry import adapter_from_model_dir
from ..speculative.sampler import SamplerConfig
from ..system.auto_config import AutoConfig, TierConfig
from ..system.profiler import SystemProfiler, SystemProfile
from .generation import GenerationLoop, GenerationResult
from .tier_cache import TierCache

_BUILD_HELP = (
    "The wisp C engine (wisp._wisp_core) is not built.\n"
    "Build it with:\n"
    "    pip install -e .          (uses CMake + your CUDA toolkit)\n"
    "or, from the repo root:\n"
    "    cmake -B build -DCMAKE_BUILD_TYPE=Release && cmake --build build\n"
    "CPU-only build (no CUDA): add -DWISP_NO_CUDA=ON."
)


def apply_display_mode(profile: SystemProfile, mode: str) -> SystemProfile:
    """
    Override the auto-detected display routing when the user knows
    better: 'gpu' forces the 1.5GB display reserve, 'igpu' zeroes it,
    'auto' (default) trusts detection.
    """
    from ..system.profiler import DISPLAY_RESERVED_BYTES
    if mode == "gpu":
        profile.display_on_gpu = True
        profile.display_reserved_bytes = DISPLAY_RESERVED_BYTES
    elif mode == "igpu":
        profile.display_on_gpu = False
        profile.display_reserved_bytes = 0
    elif mode != "auto":
        raise ValueError(
            f"display_mode must be 'auto', 'gpu', or 'igpu' — got "
            f"{mode!r}")
    return profile


def _load_core():
    try:
        from wisp import _wisp_core  # type: ignore
        return _wisp_core
    except ImportError as e:
        raise RuntimeError(_BUILD_HELP) from e


class WispEngine:
    """
    Universal MoE inference engine over the 3-tier memory hierarchy.
    One instance per converted model directory.
    """

    def __init__(self, model_path: str | Path, *,
                 max_seq_len: int = 8192,
                 use_speculative: bool = True,
                 force_profile_refresh: bool = False,
                 display_mode: str = "auto"):
        self.model_path = Path(model_path)
        self.manifest = ModelManifest.load(self.model_path)
        self.adapter = adapter_from_model_dir(self.model_path)
        self.adapter.load_tokenizer(self.model_path)

        self.profile: SystemProfile = SystemProfiler().get(
            force_refresh=force_profile_refresh)
        apply_display_mode(self.profile, display_mode)
        self.config: TierConfig = AutoConfig().calculate(
            self.profile, self.adapter)

        self._core = _load_core()
        es = self.manifest.performance["expert_size_bytes"]
        gpu_indices = self._gpu_indices()
        self._handle = self._core.engine_create(
            str(self.model_path),
            int(self.config.vram_expert_count * es),
            int(self.config.ram_expert_count * es),
            gpu_indices,
            int(self.config.omp_thread_count),
        )
        self._kv = self._core.kv_cache_alloc(self._handle, max_seq_len)
        self.max_seq_len = max_seq_len

        self.tier_cache = TierCache(
            self._core, self._handle,
            num_layers=self.adapter.num_layers,
            top_k=self.adapter.top_k_routing)
        self._loop = GenerationLoop(
            self._core, self._handle, self.adapter,
            self.tier_cache, self._kv)

        self._drafter = None
        # CPU-only detection: either the extension was built WISP_NO_CUDA,
        # or no GPU exists at runtime. Speculation defaults off there —
        # the torch drafter would dominate the budget.
        self.cuda_enabled = (
            bool(getattr(self._core, "cuda_enabled", False))
            and self.profile.gpu_count > 0)
        if not self.cuda_enabled and use_speculative:
            print("  [WISP] Running CPU-only mode — expect roughly "
                  "0.05-0.5 tok/s on frontier MoE models; speculative "
                  "decoding disabled (enable per-call if you have a "
                  "CPU drafter).")
            use_speculative = False
        self.use_speculative = use_speculative
        self._closed = False

    def _gpu_indices(self) -> list[int]:
        if self.config.gpu_strategy == "cpu_only":
            return []
        if self.config.gpu_strategy == "pipeline":
            return list(range(self.profile.gpu_count))
        idx = [self.config.primary_gpu]
        if self.config.secondary_gpu is not None:
            idx.append(self.config.secondary_gpu)
        return idx

    # ------------------------------------------------------------------ #
    # Drafter (lazy — only loaded when speculation is actually used)
    # ------------------------------------------------------------------ #
    def _get_drafter(self):
        if self._drafter is None:
            from ..speculative.drafter import load_drafter
            self._drafter = load_drafter(
                self.adapter.get_drafter_config(),
                self.model_path,
                location=self.config.drafter_location)
        return self._drafter

    # ------------------------------------------------------------------ #
    # Public API
    # ------------------------------------------------------------------ #
    def generate(self, prompt: str, *,
                 max_tokens: int = 512,
                 max_new_tokens: int | None = None,
                 temperature: float = 0.7,
                 top_k: int = 0,
                 top_p: float = 1.0,
                 repetition_penalty: float = 1.0,
                 stop_sequences: list[str] | None = None,
                 use_speculative: bool | None = None) -> str:
        """One-shot generation; returns the completed text.

        `max_new_tokens` is an alias for `max_tokens` (HF-style naming);
        when both are given, max_new_tokens wins.
        """
        pieces = list(self.stream(
            prompt, max_tokens=max_tokens, max_new_tokens=max_new_tokens,
            temperature=temperature, top_k=top_k, top_p=top_p,
            repetition_penalty=repetition_penalty,
            stop_sequences=stop_sequences,
            use_speculative=use_speculative))
        return "".join(pieces)

    def stream(self, prompt: str, *,
               max_tokens: int = 512,
               max_new_tokens: int | None = None,
               temperature: float = 0.7,
               top_k: int = 0,
               top_p: float = 1.0,
               repetition_penalty: float = 1.0,
               stop_sequences: list[str] | None = None,
               use_speculative: bool | None = None) -> Iterator[str]:
        """Streaming generation; yields text pieces as tokens land."""
        self._check_open()
        if max_new_tokens is not None:
            max_tokens = max_new_tokens
        sampler = SamplerConfig(
            temperature=temperature, top_k=top_k, top_p=top_p,
            repetition_penalty=repetition_penalty)

        speculative = (self.use_speculative
                       if use_speculative is None else use_speculative)
        self.reset_session()

        if speculative:
            try:
                drafter = self._get_drafter()
            except (FileNotFoundError, RuntimeError) as e:
                print(f"  [WISP] Speculative decoding unavailable "
                      f"({e.__class__.__name__}); falling back to plain "
                      f"decoding.")
                speculative = False

        if speculative:
            yield from self._loop.stream_speculative(
                prompt, drafter, max_tokens=max_tokens, sampler=sampler,
                stop_sequences=stop_sequences)
        else:
            yield from self._loop.stream(
                prompt, max_tokens=max_tokens, sampler=sampler,
                stop_sequences=stop_sequences)

    def prefill_benchmark(self, prompt: str) -> tuple[int, float]:
        """Time a bare prefill pass. Returns (n_prompt_tokens, seconds)."""
        import time
        self._check_open()
        self.reset_session()
        ids = self.adapter.tokenize(prompt)
        t0 = time.perf_counter()
        self._core.prefill(self._handle, ids, self._kv)
        return len(ids), time.perf_counter() - t0

    def generate_detailed(self, prompt: str, *,
                          max_tokens: int = 512,
                          temperature: float = 0.7) -> GenerationResult:
        """Generation with timing + cache statistics attached."""
        self._check_open()
        self.reset_session()
        return self._loop.generate(
            prompt, max_tokens=max_tokens,
            sampler=SamplerConfig(temperature=temperature))

    # ------------------------------------------------------------------ #
    # Introspection
    # ------------------------------------------------------------------ #
    def cache_stats(self) -> dict:
        self._check_open()
        return dict(self._core.cache_stats(self._handle))

    def vram_used_bytes(self) -> int:
        self._check_open()
        return self._core.get_vram_used_bytes(self._handle)

    def ram_used_bytes(self) -> int:
        self._check_open()
        return self._core.get_ram_used_bytes(self._handle)

    def tok_per_sec(self) -> float:
        self._check_open()
        return self._core.get_tok_per_sec(self._handle)

    # ------------------------------------------------------------------ #
    # Lifecycle
    # ------------------------------------------------------------------ #
    def reset_session(self) -> None:
        """Clear the KV cache for a fresh prompt (expert caches stay warm —
        that is the whole point of the tier system)."""
        self._core.kv_cache_clear(self._handle, self._kv)

    def clear_expert_cache(self) -> None:
        self._check_open()
        self._core.cache_clear(self._handle)
        self.tier_cache.clear()

    def close(self) -> None:
        if self._closed:
            return
        self._core.kv_cache_free(self._handle, self._kv)
        self._core.engine_destroy(self._handle)
        self._closed = True

    def _check_open(self) -> None:
        if self._closed:
            raise RuntimeError(
                "This WispEngine has been closed (close() was called or "
                "the context manager exited). Create a new one: "
                "WispEngine(model_path).")

    def __enter__(self) -> "WispEngine":
        return self

    def __exit__(self, *exc) -> None:
        self.close()

    def __del__(self):
        try:
            self.close()
        except Exception:
            pass
