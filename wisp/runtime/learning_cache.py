"""
wisp.runtime.learning_cache — cross-session expert usage tracking.

WISP's LRU tiers learn which experts matter *during* a session and then
forget everything when the process exits. This closes that loop: usage
is written to `{model_dir}/.wisp_usage`, and on the next startup the
hottest experts are warmed before the first token is generated.

    session 1   cold start; the LRU discovers your domain
    session 2   last session's top experts pre-warmed at startup
    session 7   near-instant warm start

The idea is Colibrì's `.coli_usage`, generalized: per-model rather than
hardcoded to GLM-5.2, ranked by frequency rather than mere presence, and
with a recency term so a cache that learned "coding" adapts when you
switch to prose instead of staying stuck.

FORMAT: JSON, not a packed binary. It is a few hundred KB read once per
process, so the speed difference is irrelevant, and being able to
`cat .wisp_usage` — or delete it — is worth more than the microseconds.

THREADING: record_hit() is called from the generation loop and takes no
lock; it only bumps an int in a dict, which is atomic enough under
CPython's GIL for a statistics counter. All locking is confined to
save(), which runs off the hot path.
"""

from __future__ import annotations

import json
import threading
import time
from collections import defaultdict
from dataclasses import dataclass
from pathlib import Path

from ..logging import get_logger

log = get_logger("runtime.learning_cache")

USAGE_FORMAT_VERSION = 1


@dataclass
class ExpertUsageRecord:
    """Usage stats for one expert, accumulated across every session."""
    layer_id:  int
    expert_id: int
    hit_count: int = 0
    last_used: float = 0.0     # unix timestamp
    sessions:  int = 0         # how many sessions touched this expert


class LearningCache:
    """
    Tracks which experts fire, so the next run can start warm.

        cache = LearningCache(model_dir)
        cache.load()                       # startup
        cache.record_hit(layer, expert)    # during inference
        hot = cache.get_hot_experts(500)   # -> [(layer, expert), ...]
        cache.save()                       # shutdown
    """

    USAGE_FILE = ".wisp_usage"

    def __init__(self, model_dir: Path | str, max_tracked: int = 5000):
        self.model_dir = Path(model_dir)
        self.usage_file = self.model_dir / self.USAGE_FILE
        self.max_tracked = max_tracked
        self.records: dict[tuple[int, int], ExpertUsageRecord] = {}
        self.session_hits: dict[tuple[int, int], int] = defaultdict(int)
        self._lock = threading.Lock()
        self._dirty = False

    # ------------------------------------------------------------------ #
    def load(self) -> int:
        """Read usage from disk. Returns the number of records loaded, 0
        if the file is missing or unreadable — a corrupt usage file is
        never fatal, it just means starting cold."""
        if not self.usage_file.exists():
            return 0
        try:
            with open(self.usage_file, encoding="utf-8") as f:
                data = json.load(f)
            if data.get("version") != USAGE_FORMAT_VERSION:
                log.info("ignoring .wisp_usage written by another "
                         "version (%s)", data.get("version"))
                return 0
            for rec in data.get("experts", []):
                key = (int(rec["layer_id"]), int(rec["expert_id"]))
                self.records[key] = ExpertUsageRecord(
                    layer_id=key[0],
                    expert_id=key[1],
                    hit_count=int(rec.get("hit_count", 0)),
                    last_used=float(rec.get("last_used", 0.0)),
                    sessions=int(rec.get("sessions", 1)),
                )
            log.debug("loaded %d expert records", len(self.records))
            return len(self.records)
        except (json.JSONDecodeError, OSError, KeyError, TypeError,
                ValueError) as e:
            log.warning("could not read %s (%s) — starting cold",
                        self.usage_file, e.__class__.__name__)
            self.records.clear()
            return 0

    def save(self) -> bool:
        """Merge this session's hits into the persistent record and write
        atomically. Returns True if anything was written."""
        if not self._dirty:
            return False
        now = time.time()

        with self._lock:
            for (layer_id, expert_id), hits in self.session_hits.items():
                key = (layer_id, expert_id)
                rec = self.records.get(key)
                if rec is None:
                    rec = ExpertUsageRecord(layer_id=layer_id,
                                            expert_id=expert_id)
                    self.records[key] = rec
                rec.hit_count += hits
                rec.last_used = now
                rec.sessions += 1

            # Cap the file: keep the most-used experts, drop the tail.
            kept = sorted(self.records.values(),
                          key=lambda r: r.hit_count,
                          reverse=True)[:self.max_tracked]
            payload = {
                "version": USAGE_FORMAT_VERSION,
                "model_dir": str(self.model_dir),
                "last_updated": now,
                "total_sessions": max((r.sessions for r in kept),
                                      default=0),
                "experts": [
                    {"layer_id": r.layer_id,
                     "expert_id": r.expert_id,
                     "hit_count": r.hit_count,
                     "last_used": r.last_used,
                     "sessions": r.sessions}
                    for r in kept
                ],
            }
            self.session_hits.clear()
            self._dirty = False

        try:
            self.usage_file.parent.mkdir(parents=True, exist_ok=True)
            tmp = self.usage_file.with_suffix(".wisp_usage.tmp")
            with open(tmp, "w", encoding="utf-8") as f:
                json.dump(payload, f, indent=2)
            tmp.replace(self.usage_file)   # atomic on POSIX and Windows
            log.debug("saved %d expert records", len(payload["experts"]))
            return True
        except OSError as e:
            log.warning("could not write %s (%s) — usage not persisted",
                        self.usage_file, e)
            return False

    # ------------------------------------------------------------------ #
    def record_hit(self, layer_id: int, expert_id: int,
                   count: int = 1) -> None:
        """Note that an expert fired. Hot path: no lock, no I/O."""
        self.session_hits[(layer_id, expert_id)] += count
        self._dirty = True

    def record_hits(self, pairs) -> int:
        """Bulk version for draining the engine's access log."""
        n = 0
        for layer_id, expert_id in pairs:
            self.session_hits[(layer_id, expert_id)] += 1
            n += 1
        if n:
            self._dirty = True
        return n

    # ------------------------------------------------------------------ #
    def get_hot_experts(self, top_n: int,
                        recency_weight: float = 0.3
                        ) -> list[tuple[int, int]]:
        """
        The `top_n` experts most worth pre-warming, hottest first.

        Score blends raw frequency with a recency decay so a model used
        heavily for one domain last month loses ground to what you are
        actually doing now. recency_weight=0 is pure frequency, 1.0 is
        fully recency-scaled.
        """
        if top_n <= 0 or not self.records:
            return []
        now = time.time()
        scored = []
        for rec in self.records.values():
            age_days = max(0.0, (now - rec.last_used) / 86400.0)
            recency = 1.0 / (1.0 + age_days * 0.1)
            score = rec.hit_count * ((1.0 - recency_weight)
                                     + recency * recency_weight)
            # layer/expert included for a deterministic tie-break
            scored.append((score, rec.layer_id, rec.expert_id))
        scored.sort(key=lambda t: (-t[0], t[1], t[2]))
        return [(l, e) for _, l, e in scored[:top_n]]

    def get_stats(self) -> dict:
        """Summary for `wisp cache --show` and the startup banner."""
        if not self.records:
            return {"status": "empty", "experts_tracked": 0,
                    "total_hits": 0, "sessions": 0, "top_expert": None}
        total_hits = sum(r.hit_count for r in self.records.values())
        return {
            "status": "active",
            "experts_tracked": len(self.records),
            "total_hits": total_hits,
            "sessions": max(r.sessions for r in self.records.values()),
            "top_expert": max(self.records.values(),
                              key=lambda r: r.hit_count),
        }

    def reset(self) -> None:
        """Forget everything, on disk and in memory."""
        self.records.clear()
        self.session_hits.clear()
        self._dirty = False
        if self.usage_file.exists():
            try:
                self.usage_file.unlink()
            except OSError as e:
                log.warning("could not delete %s: %s", self.usage_file, e)
