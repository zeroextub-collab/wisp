"""
wisp.runtime.tier_cache — Python coordinator over the C tier caches.

The real LRU caches (VRAM / RAM) live in C (csrc/core/lru_cache.c) because
they sit on the 488-lookups-per-token hot path. This module:

  1. wraps the C cache introspection API (stats / clear),
  2. keeps a pure-Python shadow LRU (`PyLRU`) of recent expert usage that
     powers next-token prefetch prediction WITHOUT a C round-trip, and
  3. turns predictions into `expert_prefetch_hint` calls on the transfer
     stream so the double buffer fills while the GPU computes.
"""

from __future__ import annotations

from collections import OrderedDict, Counter
from dataclasses import dataclass


@dataclass
class CacheStats:
    vram_hits: int
    ram_hits: int
    ssd_hits: int
    hit_rate: float

    @property
    def total(self) -> int:
        return self.vram_hits + self.ram_hits + self.ssd_hits


class PyLRU:
    """
    O(1) least-recently-used map, capacity-bounded by entry count.
    Pure-Python mirror of the C cache semantics (see csrc/core/lru_cache.c)
    used for prefetch prediction and for unit-testing the eviction rules.
    """

    def __init__(self, capacity: int):
        if capacity < 0:
            raise ValueError(f"capacity must be >= 0, got {capacity}")
        self.capacity = capacity
        self._map: OrderedDict = OrderedDict()

    def __len__(self) -> int:
        return len(self._map)

    def __contains__(self, key) -> bool:
        return key in self._map

    def get(self, key):
        """Hit -> value + move to MRU. Miss -> None."""
        if key not in self._map:
            return None
        self._map.move_to_end(key)
        return self._map[key]

    def put(self, key, value=True):
        """Insert/update; returns the evicted (key, value) or None."""
        evicted = None
        if key in self._map:
            self._map.move_to_end(key)
            self._map[key] = value
            return None
        if self.capacity == 0:
            return (key, value)
        if len(self._map) >= self.capacity:
            evicted = self._map.popitem(last=False)   # LRU end
        self._map[key] = value
        return evicted

    def evict(self):
        """Pop and return the LRU entry, or None if empty."""
        if not self._map:
            return None
        return self._map.popitem(last=False)

    def keys(self):
        return list(self._map.keys())


class TierCache:
    """Bridges Python-side prediction with the C engine's real caches."""

    HISTORY_WINDOW = 64  # tokens of expert-usage history kept per layer

    def __init__(self, core, handle: int, num_layers: int, top_k: int,
                 learning_cache=None):
        self._core = core
        self._handle = handle
        self.num_layers = num_layers
        self.top_k = top_k
        self.learning_cache = learning_cache
        # Per-layer recency + frequency of expert activations
        self._recent: list[PyLRU] = [
            PyLRU(self.HISTORY_WINDOW) for _ in range(num_layers)]
        self._freq: list[Counter] = [Counter() for _ in range(num_layers)]
        self.dropped_observations = 0

    # ------------------------------------------------------------------ #
    # C cache passthrough
    # ------------------------------------------------------------------ #
    def stats(self) -> CacheStats:
        d = self._core.cache_stats(self._handle)
        return CacheStats(
            vram_hits=d["vram_hits"],
            ram_hits=d["ram_hits"],
            ssd_hits=d["ssd_hits"],
            hit_rate=d["hit_rate"],
        )

    def clear(self) -> None:
        self._core.cache_clear(self._handle)
        for lru in self._recent:
            lru._map.clear()
        for c in self._freq:
            c.clear()

    # ------------------------------------------------------------------ #
    # Prediction + prefetch
    # ------------------------------------------------------------------ #
    def observe(self, layer_idx: int, expert_ids: list[int]) -> None:
        """Record which experts the router actually picked this token."""
        lru = self._recent[layer_idx]
        freq = self._freq[layer_idx]
        for e in expert_ids:
            lru.put(e)
            freq[e] += 1

    def drain_engine_log(self) -> int:
        """
        Pull the experts that actually fired out of the C engine and feed
        them to both the prefetch predictor and the learning cache.

        Expert selection happens inside the C router kernel, so without
        this the Python side never learns anything: predict() would run
        on an empty frequency table forever and every prefetch hint
        would be empty. Returns the number of accesses ingested.
        """
        if not hasattr(self._core, "drain_expert_log"):
            return 0
        try:
            drained = self._core.drain_expert_log(self._handle, 0)
        except Exception:
            return 0

        hits = drained.get("hits", [])
        self.dropped_observations += int(drained.get("dropped", 0))
        if not hits:
            return 0

        for layer, expert in hits:
            if 0 <= layer < self.num_layers:
                self._recent[layer].put(expert)
                self._freq[layer][expert] += 1
        if self.learning_cache is not None:
            self.learning_cache.record_hits(hits)
        return len(hits)

    def predict(self, layer_idx: int) -> list[int]:
        """
        Predict next-token experts for a layer: most-frequent recent experts
        first (MoE routing is heavily sticky within a domain — this is the
        same effect that drives the 85-92% warm hit rate).
        """
        freq = self._freq[layer_idx]
        if not freq:
            return []
        ranked = [e for e, _ in freq.most_common(self.top_k * 2)]
        return ranked[: self.top_k * 2]

    def prefetch_all_layers(self) -> None:
        """Fire async prefetch hints for every layer's predicted experts."""
        for layer in range(self.num_layers):
            predicted = self.predict(layer)
            if predicted:
                self._core.expert_prefetch_hint(self._handle, layer, predicted)
