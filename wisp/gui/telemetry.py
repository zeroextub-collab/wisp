"""
wisp.gui.telemetry — pure parsing of the server's /v1/stats payload.

Deliberately free of Qt imports. The widgets are thin renderers over
these functions, which means the interesting logic (unit handling,
missing-field tolerance, percentage math) is testable headlessly and
without PySide6 installed at all.

CAPACITY NOTE: /v1/stats reports what is *used* (vram_used_gb,
ram_used_gb) but not what is *available* — the engine has no reason to
know. Denominators come from SystemProfiler on this machine, which is
sound because the GUI starts the server in its own process. Both sides
use decimal GB (bytes / 1e9): the server divides by 1e9, so dividing
profiler bytes by 2**30 instead would silently overstate every bar by
about 7%.
"""

from __future__ import annotations

import shutil
from dataclasses import dataclass, field
from pathlib import Path

GB = 1e9          # decimal, matching wisp/server/app.py
PLACEHOLDER = "—"


def _f(value, default=0.0) -> float:
    try:
        if value is None:
            return default
        return float(value)
    except (TypeError, ValueError):
        return default


def _i(value, default=0) -> int:
    try:
        if value is None:
            return default
        return int(value)
    except (TypeError, ValueError):
        return default


@dataclass
class TierCapacities:
    """Denominators for the tier bars, in decimal GB."""
    vram_gb: float = 0.0
    ram_gb: float = 0.0
    nvme_gb: float = 0.0

    @classmethod
    def detect(cls, model_dir: str | Path | None = None) -> "TierCapacities":
        """Read totals from the hardware profile, plus the free space on
        whichever volume holds the model."""
        vram = ram = nvme = 0.0
        try:
            from ..system.profiler import SystemProfiler
            p = SystemProfiler().get()
            if p.gpus:
                idx = max(p.primary_gpu_index, 0)
                vram = p.gpus[idx].vram_total_bytes / GB
            ram = p.total_ram_bytes / GB
        except Exception:
            pass
        try:
            probe = Path(model_dir) if model_dir else Path(".")
            while not probe.exists() and probe != probe.parent:
                probe = probe.parent
            nvme = shutil.disk_usage(probe).total / GB
        except Exception:
            pass
        return cls(vram_gb=vram, ram_gb=ram, nvme_gb=nvme)


@dataclass
class TierUsage:
    """One tier bar: used/total in GB plus a 0-100 percentage."""
    label: str
    used_gb: float = 0.0
    total_gb: float = 0.0
    percent: int = 0
    detail: str = PLACEHOLDER


@dataclass
class StatsSnapshot:
    """Everything the right-hand panels render."""
    online: bool = False
    tok_per_sec: float = 0.0
    hit_rate: float = 0.0
    vram_hits: int = 0
    ram_hits: int = 0
    ssd_hits: int = 0
    observations: int = 0
    experts_tracked: int = 0
    sessions: int = 0
    prewarmed: int = 0
    tiers: list = field(default_factory=list)


def tier_percent(used_gb: float, total_gb: float) -> int:
    if total_gb <= 0:
        return 0
    return max(0, min(100, int(round(used_gb / total_gb * 100))))


def format_tier(label: str, used_gb: float, total_gb: float,
                show_usage: bool = True) -> TierUsage:
    """One tier bar. show_usage=False is the NVMe case: capacity is
    known but per-tier live usage is not reported, so claiming a
    number there would be inventing one."""
    if total_gb <= 0:
        return TierUsage(label, used_gb, total_gb, 0, PLACEHOLDER)
    if not show_usage:
        return TierUsage(label, 0.0, total_gb, 0,
                         f"{total_gb:.1f} GB capacity")
    return TierUsage(label, used_gb, total_gb,
                     tier_percent(used_gb, total_gb),
                     f"{used_gb:.1f}/{total_gb:.1f} GB")


def parse_stats(payload: dict | None,
                capacities: TierCapacities | None = None) -> StatsSnapshot:
    """
    Turn a /v1/stats response into a render-ready snapshot.

    Tolerant by construction: a server that is still loading, a payload
    missing `learning_cache`, or None (request failed) all produce a
    valid offline snapshot rather than raising into the Qt event loop.
    """
    caps = capacities or TierCapacities()
    if not isinstance(payload, dict):
        return StatsSnapshot(
            online=False,
            tiers=[format_tier("VRAM", 0.0, caps.vram_gb),
                   format_tier("RAM", 0.0, caps.ram_gb),
                   format_tier("NVMe", 0.0, caps.nvme_gb,
                               show_usage=False)])

    hits = payload.get("cache_hits") or {}
    vram_hits = _i(hits.get("vram_hits"))
    ram_hits = _i(hits.get("ram_hits"))
    ssd_hits = _i(hits.get("ssd_hits"))
    total_lookups = vram_hits + ram_hits + ssd_hits

    # Prefer the engine's own hit_rate; derive it when absent so the
    # panel still says something true.
    if "hit_rate" in hits:
        hit_rate = _f(hits.get("hit_rate"))
    elif total_lookups:
        hit_rate = (vram_hits + ram_hits) / total_lookups
    else:
        hit_rate = 0.0

    lc = payload.get("learning_cache") or {}

    return StatsSnapshot(
        online=True,
        tok_per_sec=_f(payload.get("tok_per_sec")),
        hit_rate=hit_rate,
        vram_hits=vram_hits,
        ram_hits=ram_hits,
        ssd_hits=ssd_hits,
        observations=total_lookups,
        experts_tracked=_i(lc.get("experts_tracked")),
        sessions=_i(lc.get("sessions")),
        prewarmed=_i(payload.get("prewarmed_experts")),
        tiers=[
            format_tier("VRAM", _f(payload.get("vram_used_gb")),
                        caps.vram_gb),
            format_tier("RAM", _f(payload.get("ram_used_gb")),
                        caps.ram_gb),
            format_tier("NVMe", 0.0, caps.nvme_gb, show_usage=False),
        ],
    )


def format_stat_lines(snap: StatsSnapshot,
                      tokens_this_session: int = 0) -> list[tuple[str, str]]:
    """(label, value) pairs for StatsPanel. Everything reads as an em
    dash until the server actually answers — never a fake zero."""
    if not snap.online:
        return [("Tokens/sec", PLACEHOLDER),
                ("Cache hit rate", PLACEHOLDER),
                ("Tokens generated", str(tokens_this_session)
                 if tokens_this_session else PLACEHOLDER),
                ("Expert lookups", PLACEHOLDER),
                ("Experts tracked", PLACEHOLDER),
                ("Pre-warmed", PLACEHOLDER)]
    return [
        ("Tokens/sec", f"{snap.tok_per_sec:.2f}"),
        ("Cache hit rate", f"{snap.hit_rate * 100:.1f}%"),
        ("Tokens generated", f"{tokens_this_session:,}"),
        ("Expert lookups", f"{snap.observations:,}"),
        ("Experts tracked", f"{snap.experts_tracked:,}"),
        ("Pre-warmed", f"{snap.prewarmed:,}"),
    ]
