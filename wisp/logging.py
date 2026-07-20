"""
wisp.logging — one-call logging setup for the CLI and library.

Console always; rotating file log at ~/.wisp/wisp.log unless disabled.
Every wisp module logs through logging.getLogger("wisp.<area>") so
`--verbose` lights the whole engine up at DEBUG in one flag.
"""

from __future__ import annotations

import logging
import logging.handlers
from pathlib import Path

LOG_PATH = Path.home() / ".wisp" / "wisp.log"
_configured = False


def setup_logging(verbose: bool = False, log_file: bool = True) -> None:
    """Idempotent logging setup. verbose=True -> DEBUG, else INFO."""
    global _configured
    level = logging.DEBUG if verbose else logging.INFO

    root = logging.getLogger("wisp")
    root.setLevel(level)

    if _configured:
        # Re-invocation just adjusts the level (e.g. tests flip verbose)
        for h in root.handlers:
            h.setLevel(level)
        return

    console = logging.StreamHandler()
    console.setLevel(level)
    console.setFormatter(logging.Formatter(
        "%(asctime)s [%(levelname)s] %(name)s: %(message)s",
        datefmt="%H:%M:%S"))
    root.addHandler(console)

    if log_file:
        try:
            LOG_PATH.parent.mkdir(parents=True, exist_ok=True)
            fh = logging.handlers.RotatingFileHandler(
                LOG_PATH, maxBytes=8 * 1024 * 1024, backupCount=2,
                encoding="utf-8")
            fh.setLevel(logging.DEBUG)   # file always captures DEBUG
            fh.setFormatter(logging.Formatter(
                "%(asctime)s [%(levelname)s] %(name)s: %(message)s"))
            root.addHandler(fh)
        except OSError:
            pass   # unwritable home dir — console-only is fine

    root.propagate = False
    _configured = True


def get_logger(area: str) -> logging.Logger:
    """logging.getLogger('wisp.<area>') with the wisp namespace enforced."""
    name = area if area.startswith("wisp") else f"wisp.{area}"
    return logging.getLogger(name)
