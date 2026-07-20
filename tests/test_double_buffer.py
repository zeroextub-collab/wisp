"""
Tests for the double-buffer async prefetch pipeline (C implementation).

The C self-test exercises the full contract:
  - contiguous reservation accounting in the filling buffer
  - capacity rejection (falls back to sync path, never overflows)
  - tick() swapping active/filling and handing over the filled batch
  - a real producer thread filling across several tick cycles
  - all producer writes landing inside pinned-buffer bounds
"""

import pytest


def _core():
    return pytest.importorskip(
        "wisp._wisp_core", exc_type=ImportError,
        reason="C engine unavailable (not built, or blocked by an OS "
               "application-control policy) — run `pip install -e .`")


def test_double_buffer_selftest():
    core = _core()
    assert core._selftest_double_buffer() is True


def test_double_buffer_selftest_is_repeatable():
    """Init/destroy cycles must not leak or corrupt state."""
    core = _core()
    for _ in range(5):
        assert core._selftest_double_buffer() is True
