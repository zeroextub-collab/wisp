"""
wisp.cli — the `wisp` command.

    wisp convert   --model glm-5.2 --output ./models/ [--quant int4]
    wisp run       --model ./models/glm-5.2/ --prompt "..." [--stream]
    wisp chat      --model ./models/glm-5.2/
    wisp profile   [--refresh]
    wisp benchmark --model ./models/glm-5.2/ --tokens 100
    wisp info      --model ./models/glm-5.2/
"""

from __future__ import annotations

import sys
import time
from pathlib import Path

import click

# Windows consoles often default to cp1252, which cannot encode the WISP
# banner's box-drawing characters. Force UTF-8 with replacement so the CLI
# never crashes on cosmetic output, whatever the terminal codepage.
for _stream in (sys.stdout, sys.stderr):
    try:
        _stream.reconfigure(encoding="utf-8", errors="replace")
    except (AttributeError, OSError, ValueError):
        pass

from . import __version__
from .models import constants as C
from .models.registry import get_adapter, supported_models
from .system.auto_config import AutoConfig, TierConfig
from .system.profiler import SystemProfiler, SystemProfile

BANNER = r"""
═══════════════════════════════════════════════════════
  ██     ██ ██  ███████  ██████
  ██     ██ ██  ██      ██    ██
  ██  █  ██ ██  ███████ ██████
  ██ ███ ██ ██       ██ ██
   ███ ███  ██  ███████ ██
  Stream what shouldn't run.
═══════════════════════════════════════════════════════"""


def _gb(n: int | float) -> str:
    return f"{n / C.GB:.1f} GB"


def print_startup_display(profile: SystemProfile, adapter,
                          config: TierConfig, load_seconds: float | None = None):
    click.echo(BANNER)
    click.echo("  System:")
    for g in profile.gpus:
        click.echo(f"    GPU {g.index} : {g.name} — {_gb(g.vram_total_bytes)} VRAM")
    if profile.gpus:
        if getattr(profile, "display_on_gpu", True):
            reserved = getattr(profile, "display_reserved_bytes",
                               1_500_000_000)
            click.echo(f"    Display: on GPU ⚠️  ({_gb(reserved)} reserved)")
            click.echo(f"             → for full VRAM: move monitor to "
                       f"motherboard/iGPU port")
        else:
            click.echo("    Display: on iGPU ✅ (full VRAM available)")
    if not profile.gpus:
        click.echo("    GPU   : none (CPU-only mode)")
    click.echo(f"    RAM   : {_gb(profile.available_ram_bytes)} available")
    click.echo(f"    NVMe  : PCIe {profile.nvme_pcie_gen_estimate}.0 — "
               f"{profile.nvme_speed_bytes_per_sec / 1e9:.1f} GB/s")
    click.echo(f"    CPU   : {profile.cpu_name} — {profile.cpu_threads} threads")
    click.echo("")
    if adapter.family == "kimi_k3":
        # Architecture CONFIRMED by the technical report (arXiv:2607.24653).
        # Kernel + converter mapping are in; tensor NAMES are the last
        # unverified piece and only real weights can settle them.
        active_b = adapter.active_parameters_per_token // 1_000_000_000
        click.echo("  Model : Kimi K3 (2.8T total / "
                   f"{active_b}B active, int4)")
        click.echo(f"    Layers      : {adapter.num_layers}  |  "
                   f"Experts/layer: {adapter.num_experts_per_layer}  |  "
                   f"Top-K: {adapter.top_k_routing}")
        click.echo(f"    Lookups/token: "
                   f"{adapter.total_expert_lookups_per_token:,}  |  "
                   f"Sparsity: {adapter.expert_sparsity}x expert-level")
        click.echo(f"    Attention   : {adapter.attention_pattern}")
        click.echo("                  75% KDA / 25% Gated MLA "
                   "(confirmed arXiv:2607.24653)")
        click.echo("                  KDA kernel implemented; converter "
                   "maps the projections")
        click.echo(click.style(
            "    NOTE: KDA tensor names are unverified against released "
            "weights — if", fg="yellow"))
        click.echo(click.style(
            "          `wisp convert` reports 0 KDA projections mapped, "
            "those layers fall", fg="yellow"))
        click.echo(click.style(
            "          back to GQA and output will be wrong.",
            fg="yellow"))
    else:
        click.echo(f"  Model : {adapter.name} "
                   f"({adapter.total_parameters // 1_000_000_000}B, int4)")
        click.echo(f"    Layers      : {adapter.num_layers}  |  "
                   f"Experts/layer: {adapter.num_experts_per_layer}")
        click.echo(f"    Top-K       : {adapter.top_k_routing}   |  "
                   f"Lookups/token: {adapter.total_expert_lookups_per_token}")
        if adapter.attention_type == "GQA" and \
                getattr(adapter, "num_attention_heads", 0):
            click.echo(f"    Attention   : GQA "
                       f"({adapter.num_attention_heads}Q / "
                       f"{adapter.num_kv_heads}KV heads)")
    click.echo(f"    Expert size : {adapter.expert_size_bytes / C.MB:.1f} MB  |  "
               f"Dense: {_gb(adapter.dense_layer_size_bytes)}")
    click.echo(f"    Bytes/token (cold): "
               f"{adapter.bytes_per_cold_token / C.GB:.2f} GB")
    click.echo("")
    click.echo("  Tier Allocation:")
    if profile.gpu_count > 0:
        if getattr(profile, "display_on_gpu", True):
            click.echo(f"    Display mode: GPU ⚠️  (auto-detected, "
                       f"{_gb(getattr(profile, 'display_reserved_bytes', 0))}"
                       f" reserved)")
        else:
            click.echo("    Display mode: iGPU ✅ (full VRAM for inference)")
        click.echo(f"    GPU VRAM  : {_gb(adapter.dense_layer_size_bytes)} dense"
                   f"  +  {config.vram_expert_count:,} expert cache slots")
    else:
        click.echo(f"    RAM(dense): {_gb(adapter.dense_layer_size_bytes)} "
                   f"(no GPU — dense layers in RAM)")
    ram_bytes = config.ram_expert_count * adapter.expert_size_bytes
    click.echo(f"    System RAM: {config.ram_expert_count:,} expert cache slots"
               f"  ({_gb(ram_bytes)})")
    if config.ssd_expert_count == 0:
        click.echo(f"    NVMe SSD  : 0 experts ← entire model in silicon")
        click.echo("")
        click.echo("  ⭐ Special: ENTIRE expert set fits in VRAM + RAM")
        click.echo("     After first load: zero SSD reads ever.")
        click.echo("     This is WISP's fastest possible mode.")
    else:
        click.echo(f"    NVMe SSD  : {config.ssd_expert_count:,} "
                   f"cold experts")
    click.echo("")
    click.echo(f"  Drafter : {config.drafter_id}  ({config.drafter_location})")
    click.echo(f"    Expected acceptance : {config.expected_acceptance:.0%}")
    click.echo(f"    Draft K             : {adapter.mtp_k} tokens")
    click.echo("")
    click.echo("  Performance Estimates:")
    click.echo(f"    Cold start : ~{config.estimated_cold_toks:.1f}  tok/s")
    click.echo(f"    Warm cache : ~{config.estimated_warm_toks:.1f}  tok/s")
    click.echo(f"    Hot cache  : ~{config.estimated_hot_toks:.1f}  tok/s")
    click.echo(f"    +MTP eff.  : ~{config.estimated_mtp_toks:.1f} tok/s "
               f"effective output")
    click.echo("═══════════════════════════════════════════════════════")
    if load_seconds is not None:
        click.echo(f"  Ready. Model loaded in {load_seconds:.1f}s")
    click.echo(f"  wisp v{__version__}  |  github.com/zeroextub-collab/wisp")
    click.echo("═══════════════════════════════════════════════════════")


def _open_engine(model_path: str, **kwargs):
    from .runtime.engine import WispEngine
    t0 = time.perf_counter()
    engine = WispEngine(model_path, **kwargs)
    load_s = time.perf_counter() - t0
    print_startup_display(engine.profile, engine.adapter,
                          engine.config, load_s)
    # Learning cache state — the "gets faster with use" signal
    records = getattr(engine, "learned_records", 0)
    if records:
        sessions = engine.learning_cache.get_stats().get("sessions", 0)
        click.echo(f"  Learning cache: {engine.prewarmed_experts:,} hot "
                   f"experts pre-warming from {records:,} tracked "
                   f"(session {sessions + 1})")
    else:
        click.echo("  Learning cache: empty (first run — it learns as "
                   "you use it)")
    return engine


_display_mode_option = click.option(
    "--display-mode", type=click.Choice(["auto", "gpu", "igpu"]),
    default="auto", show_default=True,
    help="Where the monitor is: auto-detect, force GPU (reserve 1.5GB "
         "VRAM), or force iGPU (use full VRAM).")


# --------------------------------------------------------------------------- #
@click.group()
@click.version_option(__version__, prog_name="wisp")
@click.option("--verbose", is_flag=True,
              help="Debug-level logging on the console.")
@click.option("--no-log-file", is_flag=True,
              help="Disable the ~/.wisp/wisp.log file log.")
def main(verbose: bool, no_log_file: bool):
    """WISP — stream what shouldn't run. Universal MoE inference engine."""
    from .logging import setup_logging
    setup_logging(verbose=verbose, log_file=not no_log_file)


# --------------------------------------------------------------------------- #
@main.command()
@click.option("--model", "model_name", required=True,
              help=f"Model to convert: {', '.join(supported_models())}")
@click.option("--output", "output_dir", required=True, type=click.Path(),
              help="Directory to write the converted model into.")
@click.option("--quant", default="int4", type=click.Choice(["int4"]),
              show_default=True, help="Expert weight quantization.")
@click.option("--source", default=None, type=click.Path(exists=True),
              help="Use already-downloaded HF shards instead of downloading.")
@click.option("--group-size", default=C.DEFAULT_QUANT_GROUP_SIZE,
              show_default=True, help="Quantization group size.")
def convert(model_name: str, output_dir: str, quant: str,
            source: str | None, group_size: int):
    """Download + convert a model into the wisp 3-tier layout.

    The download is resumable (per-shard checkpoints + SHA256 verify),
    conversion streams shard-by-shard as they arrive, and the result is
    verified expert-by-expert before the success message.
    """
    import shutil as _shutil
    from .converter.downloader import ShardDownloader
    from .converter.partitioner import Partitioner, verify_converted_model

    adapter = get_adapter(model_name)
    if adapter.family == "kimi_k3":
        # Weights and the technical report are both public now, so the
        # date guard is gone. What is still unverified is the KDA tensor
        # NAMING — say so before someone spends a 1.4TB download finding
        # out. The converter reports how many projections matched.
        click.echo(click.style(
            "  NOTE: K3 KDA projection names are not yet verified against "
            "released weights.\n"
            "  wisp convert reports how many matched; if it reports 0, "
            "KDA layers fall back\n"
            "  to the GQA path and output will be wrong. Please open an "
            "issue with the real names.", fg="yellow"))

    out = Path(output_dir) / model_name.lower()
    out_root = Path(output_dir)
    out_root.mkdir(parents=True, exist_ok=True)

    # 1. Disk space FIRST — converted output, plus the HF shards when
    #    we're downloading them too (they coexist until cleanup).
    disk_needed = C.DISK_SIZE_INT4.get(adapter.family, 0)
    factor = 1.05 if source else 2.1
    free = _shutil.disk_usage(out_root).free
    if disk_needed and free < disk_needed * factor:
        raise click.ClickException(
            f"{adapter.name} needs ~{disk_needed * factor / C.GB:.0f}GB "
            f"here (converted output"
            f"{'' if source else ' + downloaded shards'}), you have "
            f"{free / C.GB:.0f}GB free. Free space or choose a different "
            f"output path.")

    click.echo(f"  [WISP] Converting {adapter.name} -> {out}")
    partitioner = Partitioner(adapter, source or (out_root /
                              f"_hf_{adapter.family}"), out,
                              group_size=group_size)

    # 2+3. Download shard-by-shard, converting each as it lands.
    if source:
        manifest = partitioner.run()
    else:
        src = out_root / f"_hf_{adapter.family}"
        downloader = ShardDownloader(adapter.hf_model_id, src)
        manifest = partitioner.run(shard_paths=downloader.download_iter())

    # 5. Verify every expert file the manifest promises.
    click.echo("  [WISP] Verifying converted model...")
    ok, expected, problems = verify_converted_model(out)
    if problems:
        for p in problems[:10]:
            click.echo(f"  [WISP]   problem: {p}")
        raise click.ClickException(
            f"Verification failed: {ok}/{expected} experts OK, "
            f"{len(problems)} problems. Re-run `wisp convert` to repair "
            f"(downloads and conversion both resume).")
    click.echo(f"  [WISP] Verification: {ok:,}/{expected:,} experts OK ✅")

    # 6. Final summary.
    total_bytes = sum(f.stat().st_size for f in out.rglob("*")
                      if f.is_file())
    click.echo(f"\n  {adapter.name} ready at {out}")
    click.echo(f"  {total_bytes / C.GB:.1f} GB | {ok:,} experts | "
               f"Ready to run:")
    click.echo(f"    wisp chat --model {out}")
    return manifest


# --------------------------------------------------------------------------- #
@main.command()
@click.option("--model", "model_path", required=True,
              type=click.Path(exists=True), help="Converted model directory.")
@click.option("--prompt", required=True, help="Prompt text.")
@click.option("--max-tokens", default=512, show_default=True)
@click.option("--temperature", default=0.7, show_default=True)
@click.option("--top-p", default=1.0, show_default=True)
@click.option("--top-k", default=0, show_default=True)
@click.option("--repetition-penalty", default=1.0, show_default=True)
@click.option("--stop", "stop_sequences", multiple=True,
              help="Stop sequence (repeatable).")
@click.option("--stream", "stream_out", is_flag=True,
              help="Print tokens as they generate.")
@click.option("--show-stats", is_flag=True,
              help="Show detailed cache stats after generation.")
@click.option("--no-speculative", is_flag=True,
              help="Disable speculative decoding.")
@_display_mode_option
def run(model_path: str, prompt: str, max_tokens: int, temperature: float,
        top_p: float, top_k: int, repetition_penalty: float,
        stop_sequences: tuple[str, ...], stream_out: bool,
        show_stats: bool, no_speculative: bool, display_mode: str):
    """Run one-shot inference."""
    engine = _open_engine(model_path, use_speculative=not no_speculative,
                          display_mode=display_mode)
    try:
        kwargs = dict(max_tokens=max_tokens, temperature=temperature,
                      top_p=top_p, top_k=top_k,
                      repetition_penalty=repetition_penalty,
                      stop_sequences=list(stop_sequences) or None)
        t0 = time.perf_counter()
        pieces: list[str] = []
        if stream_out:
            for piece in engine.stream(prompt, **kwargs):
                click.echo(piece, nl=False)
                pieces.append(piece)
            click.echo("")
        else:
            text = engine.generate(prompt, **kwargs)
            pieces.append(text)
            click.echo(text)

        elapsed = time.perf_counter() - t0
        n_tokens = max(1, len(engine.adapter.tokenize("".join(pieces))) - 1)
        click.echo(f"\n  [WISP] {n_tokens} tokens in {elapsed:.1f}s "
                   f"= {n_tokens / max(elapsed, 1e-6):.2f} tok/s")
        if show_stats:
            s = engine.cache_stats()
            click.echo(f"  [stats] engine tok/s: {engine.tok_per_sec():.2f}"
                       f"  |  hit rate: {s.get('hit_rate', 0):.1%}  "
                       f"(vram {s.get('vram_hits', 0):,} / "
                       f"ram {s.get('ram_hits', 0):,} / "
                       f"ssd {s.get('ssd_hits', 0):,})")
    finally:
        engine.close()


# --------------------------------------------------------------------------- #
@main.command()
@click.option("--model", "model_path", required=True,
              type=click.Path(exists=True), help="Converted model directory.")
@click.option("--max-tokens", default=1024, show_default=True)
@click.option("--temperature", default=0.7, show_default=True)
@_display_mode_option
def chat(model_path: str, max_tokens: int, temperature: float,
         display_mode: str):
    """Interactive chat session.

    Commands: /clear (reset history), /stats (cache statistics),
    /quit or /exit or Ctrl+C to leave. Keeps the last 10 turns; when the
    context passes 80% of the KV budget, the oldest turns are trimmed
    automatically.
    """
    MAX_TURNS = 10
    engine = _open_engine(model_path, display_mode=display_mode)
    history: list[tuple[str, str]] = []
    click.echo("\n  Chat ready. Commands: /clear  /stats  /quit\n")

    def _build_prompt(user: str) -> str:
        # Trim to the last MAX_TURNS, then keep trimming oldest turns
        # while the token count exceeds 80% of the KV budget (leaving
        # headroom for the reply).
        while len(history) > MAX_TURNS:
            history.pop(0)
        budget = int(engine.max_seq_len * 0.8) - max_tokens
        while True:
            transcript = "".join(
                f"User: {u}\nAssistant: {a}\n" for u, a in history)
            prompt = f"{transcript}User: {user}\nAssistant:"
            if len(engine.adapter.tokenize(prompt)) <= budget or not history:
                return prompt
            history.pop(0)
            click.echo(click.style(
                "  [WISP] Context 80% full — trimmed oldest turn.",
                fg="yellow"))

    try:
        while True:
            try:
                user = click.prompt(click.style("WISP", fg="cyan"),
                                    prompt_suffix="> ")
            except (EOFError, KeyboardInterrupt, click.Abort):
                break
            cmd = user.strip().lower()
            if cmd in ("/exit", "/quit"):
                break
            if cmd == "/clear":
                history.clear()
                engine.reset_session()
                click.echo("  [WISP] Session cleared.")
                continue
            if cmd == "/stats":
                s = engine.cache_stats()
                click.echo(f"  [stats] tok/s: {engine.tok_per_sec():.2f}  |  "
                           f"hit rate: {s.get('hit_rate', 0):.1%}  "
                           f"(vram {s.get('vram_hits', 0):,} / "
                           f"ram {s.get('ram_hits', 0):,} / "
                           f"ssd {s.get('ssd_hits', 0):,})  |  "
                           f"vram used: {engine.vram_used_bytes() / C.GB:.2f} GB"
                           f"  |  ram used: "
                           f"{engine.ram_used_bytes() / C.GB:.2f} GB")
                continue
            if not user.strip():
                continue

            prompt = _build_prompt(user)
            click.echo(click.style("wisp", fg="magenta") + "> ", nl=False)
            reply_pieces: list[str] = []
            for piece in engine.stream(prompt, max_tokens=max_tokens,
                                       temperature=temperature,
                                       stop_sequences=["\nUser:"]):
                click.echo(piece, nl=False)
                reply_pieces.append(piece)
            click.echo("\n")
            history.append((user, "".join(reply_pieces)))
    finally:
        engine.close()
        click.echo("  [WISP] Bye.")


# --------------------------------------------------------------------------- #
@main.command()
@click.option("--refresh", is_flag=True, help="Force re-profile (clears cache).")
def profile(refresh: bool):
    """Profile this machine's hardware (cached 7 days)."""
    p = SystemProfiler().get(force_refresh=refresh)
    click.echo(BANNER)
    click.echo("  Hardware profile:")
    for g in p.gpus:
        click.echo(f"    GPU {g.index} : {g.name} — {_gb(g.vram_total_bytes)} "
                   f"(free {_gb(g.vram_free_bytes)}), "
                   f"SM {g.cuda_major}.{g.cuda_minor}, "
                   f"~{g.memory_bw_gb_s:.0f} GB/s")
    if not p.gpus:
        click.echo("    GPU   : none detected (CPU-only mode available)")
    click.echo(f"    RAM   : {_gb(p.total_ram_bytes)} total, "
               f"{_gb(p.available_ram_bytes)} available")
    click.echo(f"    NVMe  : {p.nvme_speed_bytes_per_sec / 1e9:.2f} GB/s "
               f"sequential (PCIe {p.nvme_pcie_gen_estimate}.0 estimate)")
    click.echo(f"    CPU   : {p.cpu_name}")
    click.echo(f"            {p.cpu_cores} cores / {p.cpu_threads} threads"
               f"  |  AVX2: {'yes' if p.cpu_has_avx2 else 'no'}"
               f"  |  AVX-512: {'yes' if p.cpu_has_avx512 else 'no'}")
    click.echo(f"    OS    : {p.os_platform}")
    click.echo(f"\n  Cached at {SystemProfiler.CACHE_PATH}")


# --------------------------------------------------------------------------- #
@main.command()
@click.option("--model", "model_path", required=True,
              type=click.Path(exists=True))
@click.option("--tokens", default=50, show_default=True,
              help="Tokens to generate per run.")
@click.option("--runs", default=3, show_default=True,
              help="Benchmark runs (run 1 = cold, later runs = warm/hot).")
@click.option("--prompt", default="Write a detailed explanation of how "
              "mixture-of-experts language models route tokens.",
              show_default=False)
@_display_mode_option
def benchmark(model_path: str, tokens: int, runs: int, prompt: str,
              display_mode: str):
    """Benchmark this model on this hardware (cold -> warm -> hot)."""
    engine = _open_engine(model_path, display_mode=display_mode)
    click.echo(f"\n  Benchmarking {engine.adapter.name} on this hardware...\n")
    per_run: list[tuple[float, float]] = []
    try:
        engine.clear_expert_cache()
        prev_hits = {"vram_hits": 0, "ram_hits": 0, "ssd_hits": 0}
        for r in range(1, max(runs, 1) + 1):
            label = "" if r == 1 else "  [cache now warmer]"
            click.echo(f"  Run {r}/{runs}:{label}")
            n_pre, pre_s = engine.prefill_benchmark(prompt)
            click.echo(f"    Prefill: {n_pre} tokens in {pre_s:.1f}s "
                       f"= {n_pre / max(pre_s, 1e-6):.1f} tok/s")
            res = engine.generate_detailed(prompt, max_tokens=tokens)
            s = engine.cache_stats()
            dv = s["vram_hits"] - prev_hits["vram_hits"]
            dr = s["ram_hits"] - prev_hits["ram_hits"]
            ds = s["ssd_hits"] - prev_hits["ssd_hits"]
            prev_hits = {k: s[k] for k in prev_hits}
            total = max(1, dv + dr + ds)
            click.echo(f"    Decode : {res.completion_tokens} tokens, "
                       f"{res.tok_per_sec:.2f} tok/s avg")
            click.echo(f"    Cache hits: VRAM {dv / total:.0%} | "
                       f"RAM {dr / total:.0%} | SSD {ds / total:.0%}")
            hit_rate = (dv + dr) / total
            per_run.append((res.tok_per_sec, hit_rate))

        cold = per_run[0][0]
        warm = per_run[1][0] if len(per_run) > 1 else cold
        hot = per_run[-1][0]
        acc = engine.adapter.default_acceptance_rate
        k = engine.adapter.mtp_k
        click.echo("\n  Summary:")
        click.echo(f"    Cold tok/s:  {cold:.2f}")
        if len(per_run) > 1:
            click.echo(f"    Warm tok/s:  {warm:.2f}")
        if len(per_run) > 2:
            click.echo(f"    Hot tok/s:   {hot:.2f} (run {len(per_run)})")
        click.echo(f"    With MTP:    ~{hot * (1 + acc * k):.1f} effective")
        click.echo(f"    Expert cache hit rate: "
                   f"{per_run[min(1, len(per_run) - 1)][1]:.0%} warm, "
                   f"{per_run[-1][1]:.0%} hot")
    finally:
        engine.close()


# --------------------------------------------------------------------------- #
@main.command()
@click.option("--model", "model_ref", required=True,
              help="Converted model directory, or a model name "
                   f"({', '.join(supported_models())}).")
@_display_mode_option
def info(model_ref: str, display_mode: str):
    """Show tier allocation + performance estimates without loading weights.

    Accepts either a converted model directory (reads its manifest) or a
    bare model name — useful for planning hardware before converting.
    """
    import copy
    from .models.registry import adapter_from_model_dir
    from .runtime.engine import apply_display_mode
    if Path(model_ref).exists():
        adapter = adapter_from_model_dir(model_ref)
    else:
        try:
            adapter = get_adapter(model_ref)
        except ValueError as e:
            raise click.ClickException(str(e))
    p = SystemProfiler().get()
    apply_display_mode(p, display_mode)
    config = AutoConfig().calculate(p, adapter)
    print_startup_display(p, adapter, config)

    # When the display eats VRAM, show what moving it would unlock — but
    # ONLY if it actually would. The 75% safety cap is often the stricter
    # constraint (e.g. a 12GB card: 75% = 9.0GB vs 12 - 2.0 display/base
    # = 10.1GB), in which case re-cabling the monitor buys nothing and
    # advertising a gain would be a lie.
    if p.gpu_count > 0 and getattr(p, "display_on_gpu", False):
        alt = copy.deepcopy(p)
        apply_display_mode(alt, "igpu")
        alt_cfg = AutoConfig().calculate(alt, adapter)
        gain = alt_cfg.vram_expert_count - config.vram_expert_count
        click.echo("")
        if gain > 0:
            click.echo("  Switch to iGPU/motherboard display for:")
            click.echo(f"    GPU VRAM  : {alt_cfg.vram_expert_count:,} "
                       f"expert slots (+{gain})")
            click.echo(f"    System RAM: {alt_cfg.ram_expert_count:,} "
                       f"expert slots")
            click.echo(f"    NVMe SSD  : {alt_cfg.ssd_expert_count:,} "
                       f"cold experts")
        else:
            click.echo("  Moving the display to an iGPU port would not "
                       "add expert slots here —")
            click.echo("  the 75% VRAM safety cap binds before the "
                       "display reserve does.")


# --------------------------------------------------------------------------- #
@main.command()
@click.option("--model", "model_path", required=True,
              type=click.Path(exists=True), help="Converted model directory.")
@click.option("--host", default="127.0.0.1", show_default=True,
              help="Interface to bind.")
@click.option("--port", default=8080, show_default=True,
              help="Port to listen on.")
@click.option("--public", is_flag=True,
              help="Bind 0.0.0.0 — reachable from your network.")
def serve(model_path: str, host: str, port: int, public: bool):
    """Start an OpenAI-compatible API server.

    \b
    Works with Cursor, Continue.dev, Open WebUI, and any OpenAI client:
      from openai import OpenAI
      client = OpenAI(base_url="http://localhost:8080/v1", api_key="wisp")
    """
    from .server.app import HAS_FASTAPI, INSTALL_HINT, WispServer

    if not HAS_FASTAPI:
        raise click.ClickException(INSTALL_HINT)

    if public:
        host = "0.0.0.0"
        click.echo(click.style(
            "  WARNING: --public serves on all interfaces with no "
            "authentication.\n"
            "  Anyone who can reach this port can use your GPU and read "
            "your model.\n"
            "  Only do this on a network you trust.", fg="yellow"))

    click.echo("  Starting WISP API server")
    click.echo(f"    Model  : {model_path}")
    click.echo(f"    Listen : http://{host}:{port}")
    click.echo(f"    OpenAI : http://{'localhost' if host in ('127.0.0.1', '0.0.0.0') else host}:{port}/v1")
    click.echo("    Ctrl+C to stop\n")

    WispServer(model_dir=model_path, host=host, port=port).run()


# --------------------------------------------------------------------------- #
@main.command()
@click.option("--model", "model_path", required=True,
              type=click.Path(exists=True), help="Converted model directory.")
@click.option("--show", is_flag=True, help="Show usage statistics.")
@click.option("--reset", is_flag=True, help="Clear all learned usage.")
@click.option("--top", default=10, show_default=True,
              help="How many hot experts to list with --show.")
def cache(model_path: str, show: bool, reset: bool, top: int):
    """Inspect or clear the learning cache for a model.

    WISP records which experts your sessions activate and pre-warms the
    hottest ones on the next startup, so the engine gets faster the more
    you use it. This is that data.
    """
    from .runtime.learning_cache import LearningCache

    lc = LearningCache(Path(model_path))
    lc.load()

    if reset:
        lc.reset()
        click.echo(f"  Learning cache cleared for {model_path}")
        click.echo("  The next run starts cold and relearns.")
        return

    stats = lc.get_stats()
    if stats["status"] == "empty":
        click.echo("  Learning cache: empty")
        click.echo("  Run some inference and it will start learning "
                   "which experts your work activates.")
        return

    click.echo(f"  Learning cache for {Path(model_path).name}")
    click.echo(f"    Experts tracked : {stats['experts_tracked']:,}")
    click.echo(f"    Total hits      : {stats['total_hits']:,}")
    click.echo(f"    Sessions        : {stats['sessions']}")
    t = stats["top_expert"]
    click.echo(f"    Hottest expert  : L{t.layer_id:03d}_E{t.expert_id:05d}"
               f"  ({t.hit_count:,} hits)")

    if show and top > 0:
        click.echo(f"\n    Top {top} experts (pre-warmed at startup):")
        for i, (layer, expert) in enumerate(
                lc.get_hot_experts(top_n=top), start=1):
            rec = lc.records[(layer, expert)]
            click.echo(f"      {i:>3}. L{layer:03d}_E{expert:05d}"
                       f"  {rec.hit_count:>8,} hits")


# --------------------------------------------------------------------------- #
@main.command()
@click.option("--model", "model_path", required=True,
              type=click.Path(exists=True), help="Converted model directory.")
def verify(model_path: str):
    """Check a converted model's integrity, expert file by expert file."""
    from .converter.manifest import ModelManifest
    from .converter.partitioner import verify_converted_model

    manifest = ModelManifest.load(model_path)
    n_total = manifest.performance.get("total_expert_count", 0)
    click.echo(f"  Verifying {manifest.model_name} — {n_total:,} experts...")

    ok, expected, problems = verify_converted_model(model_path,
                                                    progress=True)
    click.echo(f"  Experts: {ok:,}/{expected:,} OK")

    dense = Path(model_path) / manifest.files["dense_layers"]
    if dense.exists():
        click.echo(f"  Dense layers: OK ({dense.stat().st_size / C.GB:.2f} GB)")
    tok = Path(model_path) / manifest.files["tokenizer_dir"] / "tokenizer.json"
    if tok.exists():
        click.echo("  Tokenizer: OK")

    if problems:
        click.echo("")
        for p in problems[:20]:
            click.echo(f"  {p} ❌")
        if len(problems) > 20:
            click.echo(f"  ... and {len(problems) - 20} more")
        click.echo(f"\n  Model integrity: FAILED ❌")
        click.echo(f"  Repair: wisp convert --model {manifest.model_family} "
                   f"--output {Path(model_path).parent}  (resumes, only "
                   f"redoes what's broken)")
        raise SystemExit(1)
    click.echo("\n  Model integrity: PASSED ✅")


# --------------------------------------------------------------------------- #
@main.command()
@click.option("--model", "model_path", required=True,
              type=click.Path(exists=True), help="Converted model directory.")
@click.option("--repo", "repo_id", required=True,
              help="Target HF repo, e.g. your-username/glm-5.2-wisp")
def upload(model_path: str, repo_id: str):
    """Prepare a converted model for HuggingFace Hub sharing.

    Validates integrity, writes a model card, and prints the upload
    command — so people with slow internet can download a
    pre-converted model instead of re-converting.
    """
    from .hub import WispHubUploader

    uploader = WispHubUploader(model_path)
    try:
        cmd = uploader.prepare_upload(repo_id)
    except (FileNotFoundError, RuntimeError) as e:
        raise click.ClickException(str(e))
    click.echo(f"  Model validated and card written. To upload, run:\n")
    click.echo(f"    huggingface-cli login   (once)")
    click.echo(f"    {cmd}")
    click.echo(f"\n  This pushes the full converted model "
               f"(hundreds of GB) — make sure you have the bandwidth "
               f"and the original model's license permits redistribution.")


# --------------------------------------------------------------------------- #
@main.command()
@click.option("--models-dir", default="./models",
              type=click.Path(), show_default=True,
              help="Where converted models will live (for the space check).")
def doctor(models_dir: str):
    """Diagnose this machine's readiness to run WISP."""
    import platform as _platform
    import shutil as _shutil
    import subprocess as _subprocess

    OK, WARN, BAD = "✅", "⚠️ ", "❌"

    click.echo("  WISP System Doctor")
    click.echo("  " + "═" * 18 + "\n")

    # --- Software stack --------------------------------------------------
    py = _platform.python_version()
    py_ok = sys.version_info >= (3, 10)
    click.echo(f"  Python:     {py} {OK if py_ok else BAD}"
               + ("" if py_ok else "  (need 3.10+)"))

    try:
        import torch
        tv = torch.__version__
        blackwell = any("RTX 50" in g.name
                        for g in SystemProfiler().get().gpus)
        sm120_ok = "sm_120" in (torch.cuda.get_arch_list()
                                if torch.cuda.is_available() else [])
        if blackwell and not sm120_ok:
            click.echo(f"  PyTorch:    {tv} {WARN} (cu128+ recommended for "
                       f"Blackwell/RTX 50-series GPUs)")
        else:
            click.echo(f"  PyTorch:    {tv} {OK}")
    except ImportError:
        click.echo(f"  PyTorch:    not installed {BAD}")

    nvcc = _shutil.which("nvcc")
    if not nvcc:
        import glob as _glob
        hits = _glob.glob(r"C:\Program Files\NVIDIA GPU Computing Toolkit"
                          r"\CUDA\v*\bin\nvcc.exe") + \
               _glob.glob("/usr/local/cuda*/bin/nvcc")
        nvcc = hits[-1] if hits else None
    if nvcc:
        try:
            out = _subprocess.run([nvcc, "--version"], capture_output=True,
                                  text=True, timeout=15).stdout
            ver = next((l.split("release")[-1].split(",")[0].strip()
                        for l in out.splitlines() if "release" in l), "?")
            click.echo(f"  CUDA/nvcc:  {ver} {OK}  ({nvcc})")
        except Exception:
            click.echo(f"  CUDA/nvcc:  found but not runnable {WARN}")
    else:
        click.echo(f"  CUDA/nvcc:  not found {WARN} (CPU-only builds still "
                   f"work: WISP_NO_CUDA=1)")

    try:
        from wisp import _wisp_core
        click.echo(f"  C engine:   loaded {OK} "
                   f"(cuda_enabled: {_wisp_core.cuda_enabled})")
    except ImportError as e:
        if "Application Control" in str(e):
            click.echo(f"  C engine:   BLOCKED by Windows Smart App "
                       f"Control {BAD}")
            click.echo("              SAC blocks unsigned locally-built "
                       "DLLs. To run WISP:")
            click.echo("              Windows Security → App & browser "
                       "control → Smart App")
            click.echo("              Control settings → Off. "
                       "(Warning: turning SAC off is")
            click.echo("              permanent until Windows is "
                       "reinstalled — your call.)")
        else:
            click.echo(f"  C engine:   NOT BUILT {BAD} — "
                       f"run `pip install -e .`")

    # --- Hardware --------------------------------------------------------
    p = SystemProfiler().get()
    click.echo("\n  Hardware:")
    for g in p.gpus:
        click.echo(f"    GPU:      {g.name} "
                   f"{_gb(g.vram_total_bytes)} {OK}")

    # --- Alternative platforms -------------------------------------------
    if getattr(p, "accelerator", "cuda") == "unified":
        pool = p.unified_memory_gb
        click.echo("")
        click.echo(f"  DGX Spark detected — unified memory mode {OK}")
        click.echo(f"    {pool:.0f}GB coherent pool available for expert "
                   f"cache")
        click.echo(f"    Memory bandwidth: {p.unified_bandwidth_gb_s:.0f} "
                   f"GB/s")
        click.echo("    Tier hierarchy: unified pool → NVMe SSD "
                   "(2 tiers, not 3)")
        click.echo("    CPU and GPU share the same memory, so there is no "
                   "PCIe copy")
        click.echo("    between tiers and no display reserve to subtract.")
    elif getattr(p, "amd_gpu", None):
        amd = p.amd_gpu
        click.echo("")
        click.echo(f"  AMD GPU detected {WARN}")
        click.echo(f"    {amd['count']}x Radeon AI PRO R9700 — "
                   f"{amd['vram_gb']}GB each "
                   f"({amd['vram_gb'] * amd['count']}GB total), "
                   f"{amd['gfx_target']}")
        if amd.get("rocm_version"):
            click.echo(f"    ROCm: {amd['rocm_version']}")
        click.echo("    DETECTION ONLY: WISP's compute kernels are CUDA. "
                   "Your card is")
        click.echo("    recognised and sized correctly, but inference "
                   "will not run on it")
        click.echo("    until the HIP port lands. CPU-only mode works "
                   "today.")

    # --- Display routing -------------------------------------------------
    if p.gpus:
        g0 = p.gpus[0]
        reserved = getattr(p, "display_reserved_bytes", 0)
        click.echo("\n  Display detection:")
        if getattr(p, "display_on_gpu", True):
            click.echo(f"    Primary display on: {g0.name} (GPU) {WARN}")
            click.echo(f"    VRAM reserved for display: {_gb(reserved)}")
            click.echo(f"    VRAM available for WISP:   "
                       f"{_gb(g0.vram_total_bytes - reserved)}")
            click.echo("")
            click.echo("    Tip: Move monitor to a motherboard/iGPU port "
                       "for full")
            click.echo(f"    {_gb(g0.vram_total_bytes)} dedicated to "
                       f"inference (or override per-run with "
                       f"--display-mode igpu).")
        else:
            click.echo(f"    Primary display on: iGPU {OK}")
            click.echo(f"    VRAM reserved for display: 0 GB")
            click.echo(f"    VRAM available for WISP:   "
                       f"{_gb(g0.vram_total_bytes)}")
            click.echo("    Maximum performance mode.")
    if not p.gpus:
        click.echo(f"    GPU:      none {WARN} (CPU-only mode, ~0.05 tok/s)")
    ram_ok = p.total_ram_bytes >= 16 * C.GB
    click.echo(f"    RAM:      {_gb(p.available_ram_bytes)} available "
               f"{OK if ram_ok else WARN}")
    nvme_ok = p.nvme_speed_bytes_per_sec >= 2_000_000_000
    click.echo(f"    NVMe:     {p.nvme_speed_bytes_per_sec / 1e9:.2f} GB/s "
               f"{OK if nvme_ok else WARN}")

    # --- Model storage ---------------------------------------------------
    target = Path(models_dir)
    probe = target if target.exists() else Path(".")
    free = _shutil.disk_usage(probe).free
    click.echo(f"\n  Model storage:")
    click.echo(f"    {target.resolve()} — {free / C.GB:.0f} GB free")
    recommendations: list[str] = []
    for family, disk in C.DISK_SIZE_INT4.items():
        name = get_adapter(family).name
        if free >= disk:
            click.echo(f"    {name} needs {disk / C.GB:.0f}GB — OK {OK}")
        else:
            click.echo(f"    {name} needs {disk / C.GB:.0f}GB — "
                       f"NOT ENOUGH SPACE {BAD}")
            if family == "kimi_k3":
                recommendations.append(
                    "For Kimi K3: add a 2TB dedicated NVMe drive")
            else:
                recommendations.append(
                    f"For {name}: free {(disk - free) / C.GB:.0f}GB more")

    try:
        import torch
        if (p.gpus and any("RTX 50" in g.name for g in p.gpus)
                and "sm_120" not in (torch.cuda.get_arch_list()
                                     if torch.cuda.is_available() else [])):
            recommendations.append(
                "Upgrade torch: pip install torch "
                "--index-url https://download.pytorch.org/whl/cu128")
    except ImportError:
        recommendations.append("Install PyTorch 2.3+")

    if recommendations:
        click.echo("\n  Recommendation:")
        for r in recommendations:
            click.echo(f"    {r}")
    else:
        click.echo(f"\n  All checks green — ready to stream. {OK}")


if __name__ == "__main__":
    sys.exit(main())
