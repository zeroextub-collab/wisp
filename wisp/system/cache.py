"""
wisp.system.cache — small JSON cache utilities under ~/.wisp/.

Used for the system profile, per-model tier configs, and download state.
All writes are atomic (temp file + rename) so a killed process never leaves
a half-written cache behind.
"""

from __future__ import annotations

import hashlib
import json
import time
from pathlib import Path

WISP_HOME = Path.home() / ".wisp"


def wisp_home() -> Path:
    WISP_HOME.mkdir(parents=True, exist_ok=True)
    return WISP_HOME


def cache_path(name: str) -> Path:
    return wisp_home() / name


def save_json(name: str, data: dict) -> Path:
    """Atomically write a JSON cache file under ~/.wisp/."""
    path = cache_path(name)
    tmp = path.with_suffix(path.suffix + ".tmp")
    with open(tmp, "w", encoding="utf-8") as f:
        json.dump(data, f, indent=2)
    tmp.replace(path)
    return path


def load_json(name: str, max_age_seconds: float | None = None) -> dict | None:
    """Read a JSON cache file; None if missing, corrupt, or expired."""
    path = cache_path(name)
    if not path.exists():
        return None
    if max_age_seconds is not None:
        age = time.time() - path.stat().st_mtime
        if age > max_age_seconds:
            return None
    try:
        with open(path, encoding="utf-8") as f:
            return json.load(f)
    except (json.JSONDecodeError, OSError):
        return None


def invalidate(name: str) -> bool:
    path = cache_path(name)
    if path.exists():
        path.unlink()
        return True
    return False


def tier_config_cache_name(model_dir: str | Path) -> str:
    """Stable per-model-directory cache filename for TierConfig."""
    digest = hashlib.sha1(str(Path(model_dir).resolve()).encode()).hexdigest()[:12]
    return f"tier_config_{digest}.json"
