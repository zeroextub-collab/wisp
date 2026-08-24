"""
wisp.gui.main_window — the three-column desktop shell.

    [ controls 300px ][      chat      ][ monitors 280px ]

The window owns the server lifecycle and a single 2s QTimer that polls
/v1/stats and fans the result out to both right-hand panels. Chat has
its own connection because it is a long-lived stream, not a poll.
"""

from __future__ import annotations

import json
from pathlib import Path

from PySide6.QtCore import Qt, QTimer, QUrl
from PySide6.QtNetwork import QNetworkAccessManager, QNetworkRequest
from PySide6.QtWidgets import (QComboBox, QFileDialog, QFrame, QHBoxLayout,
                               QLabel, QLineEdit, QMainWindow, QMessageBox,
                               QPlainTextEdit, QPushButton, QSlider,
                               QSpinBox, QVBoxLayout, QWidget)

from .. import __version__
from .server_thread import ServerThread
from .telemetry import TierCapacities, parse_stats
from .theme import DARK_STYLESHEET
from .widgets.chat_widget import ChatWidget
from .widgets.stats_panel import StatsPanel
from .widgets.tier_monitor import TierMonitor

POLL_INTERVAL_MS = 2000


class WispMainWindow(QMainWindow):
    """Model controls, chat, and live tier/stat monitors."""

    def __init__(self, model_dir: str | None = None, parent=None):
        super().__init__(parent)
        self.setWindowTitle(f"WISP {__version__} — stream what shouldn't run")
        self.resize(1280, 820)
        self.setStyleSheet(DARK_STYLESHEET)

        self.server: ServerThread | None = None
        self._net = QNetworkAccessManager(self)
        self._stats_inflight = False

        root = QWidget()
        layout = QHBoxLayout(root)
        layout.setContentsMargins(12, 12, 12, 12)
        layout.setSpacing(12)
        layout.addWidget(self._build_left_panel(model_dir))
        layout.addWidget(self._build_center_panel(), 1)
        layout.addWidget(self._build_right_panel())
        self.setCentralWidget(root)

        self.poll_timer = QTimer(self)
        self.poll_timer.setInterval(POLL_INTERVAL_MS)
        self.poll_timer.timeout.connect(self.poll_stats)

        self._refresh_capacities()
        self._set_server_state(False)

    # ------------------------------------------------------------------ #
    # Panels
    # ------------------------------------------------------------------ #
    def _build_left_panel(self, model_dir: str | None) -> QWidget:
        panel = QFrame()
        panel.setObjectName("Panel")
        panel.setFixedWidth(300)
        layout = QVBoxLayout(panel)
        layout.setContentsMargins(12, 12, 12, 12)
        layout.setSpacing(10)

        title = QLabel("MODEL")
        title.setObjectName("SectionTitle")
        layout.addWidget(title)

        self.model_edit = QLineEdit(model_dir or "")
        self.model_edit.setPlaceholderText("path to a converted model")
        layout.addWidget(self.model_edit)

        browse = QPushButton("Browse...")
        browse.clicked.connect(self.browse_model)
        layout.addWidget(browse)

        port_row = QHBoxLayout()
        port_label = QLabel("Port")
        port_label.setObjectName("StatKey")
        self.port_value = QLabel("—")
        self.port_value.setObjectName("StatValue")
        self.port_value.setAlignment(Qt.AlignRight | Qt.AlignVCenter)
        self.port_value.setToolTip(
            "Assigned automatically when the server starts. Point any "
            "OpenAI client at http://127.0.0.1:PORT/v1")
        port_row.addWidget(port_label)
        port_row.addStretch(1)
        port_row.addWidget(self.port_value)
        layout.addLayout(port_row)

        self.start_button = QPushButton("Start Server")
        self.start_button.setObjectName("StartButton")
        self.start_button.clicked.connect(self.start_server)
        layout.addWidget(self.start_button)

        self.stop_button = QPushButton("Stop Server")
        self.stop_button.setObjectName("StopButton")
        self.stop_button.clicked.connect(self.stop_server)
        layout.addWidget(self.stop_button)

        self.status_label = QLabel("● Offline")
        self.status_label.setObjectName("StatusOffline")
        layout.addWidget(self.status_label)

        layout.addSpacing(6)
        gen_title = QLabel("GENERATION")
        gen_title.setObjectName("SectionTitle")
        layout.addWidget(gen_title)

        self.temp_label = QLabel("Temperature   0.70")
        self.temp_label.setObjectName("StatKey")
        layout.addWidget(self.temp_label)
        self.temp_slider = QSlider(Qt.Horizontal)
        # Qt sliders are integer-only; store hundredths and divide.
        self.temp_slider.setRange(0, 150)
        self.temp_slider.setSingleStep(5)
        self.temp_slider.setPageStep(5)
        self.temp_slider.setValue(70)
        self.temp_slider.valueChanged.connect(self._on_temperature_changed)
        layout.addWidget(self.temp_slider)

        tokens_label = QLabel("Max tokens")
        tokens_label.setObjectName("StatKey")
        layout.addWidget(tokens_label)
        self.tokens_spin = QSpinBox()
        self.tokens_spin.setRange(64, 8192)
        self.tokens_spin.setSingleStep(64)
        self.tokens_spin.setValue(512)
        self.tokens_spin.valueChanged.connect(self._push_generation_settings)
        layout.addWidget(self.tokens_spin)

        system_label = QLabel("System prompt (optional)")
        system_label.setObjectName("StatKey")
        layout.addWidget(system_label)
        self.system_edit = QPlainTextEdit()
        self.system_edit.setFixedHeight(90)
        self.system_edit.setPlaceholderText("You are a helpful assistant.")
        self.system_edit.textChanged.connect(self._push_generation_settings)
        layout.addWidget(self.system_edit)

        layout.addStretch(1)
        clear_button = QPushButton("Clear chat")
        clear_button.clicked.connect(lambda: self.chat.clear())
        layout.addWidget(clear_button)
        return panel

    def _build_center_panel(self) -> QWidget:
        self.chat = ChatWidget()
        self.chat.token_received.connect(self._on_token)
        self.chat.error_occurred.connect(self._on_chat_error)
        return self.chat

    def _build_right_panel(self) -> QWidget:
        container = QWidget()
        container.setFixedWidth(280)
        layout = QVBoxLayout(container)
        layout.setContentsMargins(0, 0, 0, 0)
        layout.setSpacing(12)
        self.tier_monitor = TierMonitor()
        self.stats_panel = StatsPanel()
        layout.addWidget(self.tier_monitor)
        layout.addWidget(self.stats_panel)
        layout.addStretch(1)
        return container

    # ------------------------------------------------------------------ #
    # Settings plumbing
    # ------------------------------------------------------------------ #
    def _on_temperature_changed(self, value: int) -> None:
        self.temp_label.setText(f"Temperature   {value / 100:.2f}")
        self._push_generation_settings()

    def _push_generation_settings(self) -> None:
        self.chat.temperature = self.temp_slider.value() / 100.0
        self.chat.max_tokens = self.tokens_spin.value()
        self.chat.system_prompt = self.system_edit.toPlainText()

    def _refresh_capacities(self) -> None:
        """Tier denominators follow the selected model — NVMe capacity
        is the volume that model lives on, not wherever the GUI runs."""
        caps = TierCapacities.detect(self.model_edit.text().strip() or None)
        self.tier_monitor.set_capacities(caps)
        self.capacities = caps

    def browse_model(self) -> None:
        chosen = QFileDialog.getExistingDirectory(
            self, "Select a converted WISP model directory",
            self.model_edit.text().strip() or str(Path.home()))
        if chosen:
            self.model_edit.setText(chosen)
            self._refresh_capacities()

    # ------------------------------------------------------------------ #
    # Server lifecycle
    # ------------------------------------------------------------------ #
    def _set_server_state(self, online: bool) -> None:
        self.start_button.setEnabled(not online)
        self.stop_button.setEnabled(online)
        self.model_edit.setEnabled(not online)
        self.chat.set_enabled(online)
        if online:
            self.status_label.setText("● Online")
            self.status_label.setObjectName("StatusOnline")
        else:
            self.status_label.setText("● Offline")
            self.status_label.setObjectName("StatusOffline")
        # Re-apply the sheet so the objectName swap actually repaints.
        self.status_label.style().unpolish(self.status_label)
        self.status_label.style().polish(self.status_label)

    def start_server(self) -> None:
        model_dir = self.model_edit.text().strip()
        if not model_dir or not Path(model_dir).is_dir():
            QMessageBox.warning(
                self, "No model selected",
                "Choose a converted model directory first.\n\n"
                "Convert one with:\n"
                "    wisp convert --model glm-5.2 --output ./models/")
            return
        if not (Path(model_dir) / "manifest.json").exists():
            QMessageBox.warning(
                self, "Not a WISP model",
                f"{model_dir}\n\nhas no manifest.json, so it is not a "
                f"converted model.\n\nRun `wisp convert` first, or "
                f"`wisp verify --model <dir>` to check an existing one.")
            return

        self._refresh_capacities()
        try:
            self.server = ServerThread(model_dir)
            self.server.start()
        except ImportError as e:
            QMessageBox.critical(self, "Missing dependency", str(e))
            self.server = None
            return

        self.port_value.setText(str(self.server.port))
        self.chat.configure(self.server.api_base, Path(model_dir).name)
        self._push_generation_settings()
        self.stats_panel.reset_session()
        self._set_server_state(True)
        self.chat.add_system_note(
            f"Server starting on {self.server.base_url} — the model loads "
            f"in the background; stats appear once it is ready.")
        self.poll_timer.start()

    def stop_server(self) -> None:
        self.poll_timer.stop()
        self.chat.abort()
        if self.server is not None:
            # Blocking join is deliberate: the shutdown hook is what
            # writes .wisp_usage, and losing it silently would undo the
            # learning cache for that session.
            self.server.stop()
            self.server = None
        self.port_value.setText("—")
        self._set_server_state(False)
        self.tier_monitor.update_from_stats(None)
        self.stats_panel.update_from_stats(None, self.capacities)

    # ------------------------------------------------------------------ #
    # Stats polling
    # ------------------------------------------------------------------ #
    def poll_stats(self) -> None:
        if self.server is None or self._stats_inflight:
            return
        if self.server.error is not None:
            self._on_server_died(self.server.error)
            return
        self._stats_inflight = True
        request = QNetworkRequest(QUrl(f"{self.server.api_base}/stats"))
        reply = self._net.get(request)
        reply.finished.connect(lambda: self._on_stats_reply(reply))

    def _on_stats_reply(self, reply) -> None:
        self._stats_inflight = False
        payload = None
        try:
            if reply.error() == reply.NetworkError.NoError:
                payload = json.loads(bytes(reply.readAll()).decode("utf-8"))
        except (ValueError, UnicodeDecodeError):
            payload = None
        finally:
            reply.deleteLater()

        # A 503 while the model loads is normal, not an outage; parse_stats
        # turns anything unusable into a clean offline snapshot.
        snapshot = parse_stats(payload, self.capacities)
        self.tier_monitor.apply_snapshot(snapshot)
        self.stats_panel.apply_snapshot(snapshot)

    def _on_server_died(self, error: BaseException) -> None:
        self.poll_timer.stop()
        self._set_server_state(False)
        self.port_value.setText("—")
        self.chat.add_system_note(f"Server stopped: {error}")
        self.server = None

    # ------------------------------------------------------------------ #
    def _on_token(self, _piece: str) -> None:
        self.stats_panel.add_tokens(1)

    def _on_chat_error(self, message: str) -> None:
        self.chat.add_system_note(f"Error: {message}")

    def closeEvent(self, event):           # noqa: N802  (Qt naming)
        """Always take the server down with the window — an orphaned
        uvicorn thread would keep the GPU allocated."""
        try:
            self.stop_server()
        finally:
            super().closeEvent(event)
