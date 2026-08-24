"""
wisp.gui.widgets.tier_monitor — the three-tier memory bars.

Renders VRAM / RAM / NVMe as progress bars fed by /v1/stats. All parsing
lives in wisp.gui.telemetry; this file is presentation only, which is
why it can be trusted without a display to test it against.

NVMe deliberately shows capacity with no fill: the engine reports how
much VRAM and RAM the tiers hold, but nothing equivalent for cold
experts on disk. Drawing a plausible-looking bar there would be making
a number up.
"""

from __future__ import annotations

from PySide6.QtCore import Qt
from PySide6.QtWidgets import (QFrame, QHBoxLayout, QLabel, QProgressBar,
                               QVBoxLayout, QWidget)

from ..telemetry import PLACEHOLDER, TierCapacities, TierUsage, parse_stats


class _TierRow(QWidget):
    """One labelled bar."""

    def __init__(self, label: str, parent=None):
        super().__init__(parent)
        layout = QVBoxLayout(self)
        layout.setContentsMargins(0, 0, 0, 0)
        layout.setSpacing(3)

        header = QHBoxLayout()
        header.setContentsMargins(0, 0, 0, 0)
        self.name = QLabel(label)
        self.name.setObjectName("TierLabel")
        self.detail = QLabel(PLACEHOLDER)
        self.detail.setObjectName("TierDetail")
        self.detail.setAlignment(Qt.AlignRight | Qt.AlignVCenter)
        header.addWidget(self.name)
        header.addStretch(1)
        header.addWidget(self.detail)

        self.bar = QProgressBar()
        self.bar.setRange(0, 100)
        self.bar.setValue(0)
        self.bar.setTextVisible(False)

        layout.addLayout(header)
        layout.addWidget(self.bar)

    def apply(self, usage: TierUsage) -> None:
        self.bar.setValue(usage.percent)
        self.detail.setText(usage.detail)


class TierMonitor(QFrame):
    """VRAM / RAM / NVMe occupancy, refreshed from /v1/stats."""

    def __init__(self, capacities: TierCapacities | None = None,
                 parent=None):
        super().__init__(parent)
        self.setObjectName("Panel")
        self.capacities = capacities or TierCapacities()

        layout = QVBoxLayout(self)
        layout.setContentsMargins(12, 10, 12, 12)
        layout.setSpacing(10)

        title = QLabel("TIER MONITOR")
        title.setObjectName("SectionTitle")
        layout.addWidget(title)

        self.rows = {name: _TierRow(name) for name in
                     ("VRAM", "RAM", "NVMe")}
        for row in self.rows.values():
            layout.addWidget(row)
        layout.addStretch(1)

        self.set_capacities(self.capacities)

    # ------------------------------------------------------------------ #
    def set_capacities(self, capacities: TierCapacities) -> None:
        """Re-detect denominators (e.g. after the model path changes, so
        NVMe reflects the volume the model actually lives on)."""
        self.capacities = capacities
        self.update_from_stats(None)

    def update_from_stats(self, payload: dict | None) -> None:
        """Apply a /v1/stats payload, or None when the server is down."""
        snapshot = parse_stats(payload, self.capacities)
        self.apply_snapshot(snapshot)

    def apply_snapshot(self, snapshot) -> None:
        for usage in snapshot.tiers:
            row = self.rows.get(usage.label)
            if row is not None:
                row.apply(usage)
