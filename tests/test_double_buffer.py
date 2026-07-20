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

# Optional compiled engine — see the note in tests/test_adapters.py.
try:
    import wisp._wisp_core as _core
    HAS_ENGINE = True
except (ImportError, OSError):
    _core = None
    HAS_ENGINE = False

requires_engine = pytest.mark.skipif(
    not HAS_ENGINE, reason="C engine not available in CI")


@pytest.mark.engine
@requires_engine
def test_double_buffer_selftest():
    assert _core._selftest_double_buffer() is True


@pytest.mark.engine
@requires_engine
def test_double_buffer_selftest_is_repeatable():
    """Init/destroy cycles must not leak or corrupt state."""
    for _ in range(5):
        assert _core._selftest_double_buffer() is True
