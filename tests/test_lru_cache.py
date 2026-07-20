"""
Tests for the LRU cache — both the pure-Python shadow LRU used for
prefetch prediction (wisp.runtime.tier_cache.PyLRU) and, when the C
extension is built, the real C implementation via its self-test.
"""

import pytest

from wisp.runtime.tier_cache import PyLRU


# --------------------------------------------------------------------------
# PyLRU (mirrors the C semantics)
# --------------------------------------------------------------------------

def test_put_get_touch_order():
    lru = PyLRU(capacity=3)
    for e in (0, 1, 2):
        assert lru.put((0, e)) is None
    assert len(lru) == 3

    # Access expert 0 -> MRU; LRU is now expert 1
    assert lru.get((0, 0)) is True
    evicted = lru.put((0, 3))
    assert evicted is not None and evicted[0] == (0, 1)
    assert (0, 1) not in lru
    assert (0, 0) in lru


def test_miss_returns_none():
    lru = PyLRU(capacity=2)
    assert lru.get((5, 5)) is None
    lru.put((1, 1))
    assert lru.get((1, 2)) is None


def test_duplicate_put_updates_without_growth():
    lru = PyLRU(capacity=2)
    lru.put((0, 0), "a")
    lru.put((0, 1), "b")
    assert lru.put((0, 0), "c") is None      # update, no eviction
    assert len(lru) == 2
    assert lru.get((0, 0)) == "c"
    # (0, 0) is MRU now, so inserting evicts (0, 1)
    ev = lru.put((0, 2), "d")
    assert ev[0] == (0, 1)


def test_evict_pops_lru_end():
    lru = PyLRU(capacity=3)
    for e in range(3):
        lru.put((0, e))
    key, _ = lru.evict()
    assert key == (0, 0)
    key, _ = lru.evict()
    assert key == (0, 1)
    lru.evict()
    assert lru.evict() is None               # empty


def test_zero_capacity_rejects_everything():
    lru = PyLRU(capacity=0)
    assert lru.put((0, 0), "x") == ((0, 0), "x")
    assert len(lru) == 0


def test_negative_capacity_raises():
    with pytest.raises(ValueError):
        PyLRU(capacity=-1)


# --------------------------------------------------------------------------
# C implementation (O(1) hash + doubly-linked list) via its self-test
# --------------------------------------------------------------------------

def test_c_lru_selftest():
    core = pytest.importorskip(
        "wisp._wisp_core", exc_type=ImportError,
        reason="C engine unavailable (not built, or blocked by an OS "
               "application-control policy) — run `pip install -e .`")
    assert core._selftest_lru() is True
