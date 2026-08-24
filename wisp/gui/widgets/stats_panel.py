"""
wisp.gui.widgets.stats_panel — live engine numbers.

Every value reads as an em dash until the server actually answers. A
dashboard that shows 0.00 tok/s when it simply has not heard from the
engine is lying quietly, and this one is meant to be looked at while
debugging performance.
"""

from __future__ import annotations

from PySide6.QtCore import Qt
from PySide6.QtWidgets import (QFrame, QGridLayout, QLabel, QVBoxLayout)

from ..telemetry import (PLACEHOLDER, TierCapacities, format_stat_lines,
                         parse_stats)

_ROWS = ("Tokens/sec", "Cache hit rate", "Tokens generated",
         "Expert lookups", "Experts tracked", "Pre-warmed")


class StatsPanel(QFrame):
    """Rolling tok/s, cache hit rate, session token count, learning-cache
    state — refreshed on the same 2s timer as the tier monitor."""

    def __init__(self, parent=None):
        super().__init__(parent)
        self.setObjectName("Panel")
        self.tokens_this_session = 0

        outer = QVBoxLayout(self)
        outer.setContentsMargins(12, 10, 12, 12)
        outer.setSpacing(8)

        title = QLabel("ENGINE STATS")
        title.setObjectName("SectionTitle")
        outer.addWidget(title)

        grid = QGridLayout()
        grid.setContentsMargins(0, 0, 0, 0)
        grid.setHorizontalSpacing(8)
        grid.setVerticalSpacing(6)
        grid.setColumnStretch(0, 1)

        self.values: dict[str, QLabel] = {}
        for row, key in enumerate(_ROWS):
            key_label = QLabel(key)
            key_label.setObjectName("StatKey")
            value_label = QLabel(PLACEHOLDER)
            value_label.setObjectName("StatValue")
            value_label.setAlignment(Qt.AlignRight | Qt.AlignVCenter)
            grid.addWidget(key_label, row, 0)
            grid.addWidget(value_label, row, 1)
            self.values[key] = value_label

        outer.addLayout(grid)

        self.breakdown = QLabel(PLACEHOLDER)
        self.breakdown.setObjectName("TierDetail")
        self.breakdown.setWordWrap(True)
        outer.addWidget(self.breakdown)
        outer.addStretch(1)

    # ------------------------------------------------------------------ #
    def add_tokens(self, count: int = 1) -> None:
        """Counted here rather than read from the server: /v1/stats has
        no per-session token total, and the GUI is the only thing that
        knows what 'this session' means."""
        self.tokens_this_session += count

    def reset_session(self) -> None:
        self.tokens_this_session = 0

    def update_from_stats(self, payload: dict | None,
                          capacities: TierCapacities | None = None) -> None:
        self.apply_snapshot(parse_stats(payload, capacities))

    # Alias matching the spec's StatsPanel.update() naming.
    def update(self, payload: dict | None = None) -> None:      # noqa: A003
        if payload is None:
            super().update()
            return
        self.update_from_stats(payload)

    def apply_snapshot(self, snapshot) -> None:
        for key, value in format_stat_lines(snapshot,
                                            self.tokens_this_session):
            label = self.values.get(key)
            if label is not None:
                label.setText(value)
        if snapshot.online and snapshot.observations:
            self.breakdown.setText(
                f"VRAM {snapshot.vram_hits:,} · RAM {snapshot.ram_hits:,}"
                f" · SSD {snapshot.ssd_hits:,}")
        elif snapshot.online:
            self.breakdown.setText("no expert lookups yet")
        else:
            self.breakdown.setText(PLACEHOLDER)
