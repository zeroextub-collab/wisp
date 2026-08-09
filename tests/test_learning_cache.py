"""
Tests for the cross-session learning cache (.wisp_usage).

The promise is "gets faster the more you use it", which decomposes into:
usage survives a restart, accumulates across sessions, ranks hot experts
correctly, and never corrupts the file if a write is interrupted.
"""

import json
import time

import pytest

from wisp.runtime.learning_cache import LearningCache, ExpertUsageRecord


def test_learning_cache_empty_start(tmp_path):
    lc = LearningCache(tmp_path)
    assert lc.load() == 0
    assert lc.get_hot_experts(top_n=100) == []
    assert lc.get_stats()["status"] == "empty"


def test_learning_cache_records_hits(tmp_path):
    lc = LearningCache(tmp_path)
    lc.load()
    lc.record_hit(5, 147)
    lc.record_hit(5, 147)
    lc.record_hit(12, 88)
    assert lc.session_hits[(5, 147)] == 2
    assert lc.session_hits[(12, 88)] == 1


def test_learning_cache_save_and_reload(tmp_path):
    lc1 = LearningCache(tmp_path)
    lc1.load()
    for _ in range(100):
        lc1.record_hit(5, 147)
    for _ in range(50):
        lc1.record_hit(12, 88)
    assert lc1.save() is True

    lc2 = LearningCache(tmp_path)
    assert lc2.load() == 2
    hot = lc2.get_hot_experts(top_n=10)
    assert hot[0] == (5, 147)      # most used first
    assert hot[1] == (12, 88)


def test_learning_cache_top_n_respects_limit(tmp_path):
    lc = LearningCache(tmp_path)
    lc.load()
    for i in range(100):
        lc.record_hit(0, i)
    lc.save()

    lc2 = LearningCache(tmp_path)
    lc2.load()
    assert len(lc2.get_hot_experts(top_n=10)) == 10
    assert lc2.get_hot_experts(top_n=0) == []


def test_learning_cache_accumulates_across_sessions(tmp_path):
    """Hit counts and session counts both grow run over run."""
    for _ in range(3):
        lc = LearningCache(tmp_path)
        lc.load()
        lc.record_hit(0, 0)
        lc.save()

    lc = LearningCache(tmp_path)
    lc.load()
    assert lc.records[(0, 0)].hit_count == 3
    assert lc.records[(0, 0)].sessions == 3


def test_learning_cache_ranking_is_by_frequency(tmp_path):
    lc = LearningCache(tmp_path)
    lc.load()
    lc.record_hit(1, 1, count=5)
    lc.record_hit(2, 2, count=50)
    lc.record_hit(3, 3, count=500)
    lc.save()

    lc2 = LearningCache(tmp_path)
    lc2.load()
    assert lc2.get_hot_experts(3) == [(3, 3), (2, 2), (1, 1)]


def test_learning_cache_recency_breaks_frequency_ties(tmp_path):
    """An expert used today should outrank an equally-used one from
    months ago — that is what lets the cache follow a domain switch."""
    lc = LearningCache(tmp_path)
    now = time.time()
    lc.records[(0, 1)] = ExpertUsageRecord(0, 1, hit_count=100,
                                           last_used=now, sessions=1)
    lc.records[(0, 2)] = ExpertUsageRecord(0, 2, hit_count=100,
                                           last_used=now - 120 * 86400,
                                           sessions=1)
    hot = lc.get_hot_experts(2, recency_weight=0.5)
    assert hot[0] == (0, 1)


def test_learning_cache_max_tracked_caps_file(tmp_path):
    """The file cannot grow without bound; the coldest entries drop."""
    lc = LearningCache(tmp_path, max_tracked=50)
    lc.load()
    for i in range(200):
        lc.record_hit(0, i, count=i + 1)   # expert i used i+1 times
    lc.save()

    with open(tmp_path / ".wisp_usage", encoding="utf-8") as f:
        data = json.load(f)
    assert len(data["experts"]) == 50
    # The survivors are the hottest ones
    kept = {e["expert_id"] for e in data["experts"]}
    assert 199 in kept and 0 not in kept


def test_learning_cache_reset(tmp_path):
    lc = LearningCache(tmp_path)
    lc.load()
    lc.record_hit(0, 0)
    lc.save()
    assert (tmp_path / ".wisp_usage").exists()

    lc.reset()
    assert not (tmp_path / ".wisp_usage").exists()
    assert LearningCache(tmp_path).load() == 0


def test_learning_cache_atomic_write(tmp_path):
    """The published file is always complete, valid JSON — writes go to
    a temp file and are renamed into place."""
    lc = LearningCache(tmp_path)
    lc.load()
    for i in range(1000):
        lc.record_hit(i % 61, i % 256)
    lc.save()

    with open(tmp_path / ".wisp_usage", encoding="utf-8") as f:
        data = json.load(f)
    assert data["version"] == 1
    assert "experts" in data
    # No temp file left behind
    assert list(tmp_path.glob("*.tmp")) == []


def test_learning_cache_survives_corrupt_file(tmp_path):
    """A truncated or garbage file must degrade to a cold start, never
    crash the engine on startup."""
    (tmp_path / ".wisp_usage").write_text("{not valid json", encoding="utf-8")
    lc = LearningCache(tmp_path)
    assert lc.load() == 0
    lc.record_hit(1, 1)
    assert lc.save() is True          # and it recovers the file
    assert LearningCache(tmp_path).load() == 1


def test_learning_cache_ignores_foreign_version(tmp_path):
    (tmp_path / ".wisp_usage").write_text(
        json.dumps({"version": 999, "experts": [
            {"layer_id": 0, "expert_id": 0, "hit_count": 5}]}),
        encoding="utf-8")
    assert LearningCache(tmp_path).load() == 0


def test_learning_cache_save_is_noop_when_clean(tmp_path):
    lc = LearningCache(tmp_path)
    lc.load()
    assert lc.save() is False          # nothing recorded, nothing written
    assert not (tmp_path / ".wisp_usage").exists()


def test_learning_cache_bulk_record(tmp_path):
    """record_hits() is what the engine-log drain calls."""
    lc = LearningCache(tmp_path)
    lc.load()
    n = lc.record_hits([(1, 2), (1, 2), (3, 4)])
    assert n == 3
    assert lc.session_hits[(1, 2)] == 2
    lc.save()
    assert LearningCache(tmp_path).load() == 2


def test_learning_cache_stats(tmp_path):
    lc = LearningCache(tmp_path)
    lc.load()
    lc.record_hit(7, 42, count=99)
    lc.record_hit(1, 1, count=1)
    lc.save()

    lc2 = LearningCache(tmp_path)
    lc2.load()
    stats = lc2.get_stats()
    assert stats["status"] == "active"
    assert stats["experts_tracked"] == 2
    assert stats["total_hits"] == 100
    assert stats["top_expert"].layer_id == 7
    assert stats["top_expert"].expert_id == 42
