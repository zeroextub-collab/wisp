"""wisp.runtime — the engine, tier cache coordinator, and generation loop."""

from .tier_cache import CacheStats, PyLRU, TierCache

__all__ = ["CacheStats", "PyLRU", "TierCache", "WispEngine"]


def __getattr__(name):
    # WispEngine imports the C extension; keep it lazy.
    if name == "WispEngine":
        from .engine import WispEngine
        return WispEngine
    raise AttributeError(f"module 'wisp.runtime' has no attribute {name!r}")
