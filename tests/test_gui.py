"""
Tests for the desktop GUI.

Split in two deliberately:

  * The logic tests import nothing from Qt. All /v1/stats handling lives
    in wisp.gui.telemetry precisely so it can be verified without a
    display, a QApplication, or PySide6 installed at all.
  * The widget tests construct real widgets under Qt's "offscreen"
    platform and skip cleanly when PySide6 is absent, so CI stays green
    on a headless runner without Qt.
"""

from __future__ import annotations

import os

import pytest

# Must be set before QApplication exists, hence module import time.
os.environ.setdefault("QT_QPA_PLATFORM", "offscreen")

from wisp.gui.telemetry import (PLACEHOLDER, TierCapacities, format_stat_lines,
                                format_tier, parse_stats, tier_percent)
from wisp.gui.theme import DARK_STYLESHEET

try:
    from PySide6.QtWidgets import QApplication
    HAS_QT = True
except ImportError:
    HAS_QT = False

requires_qt = pytest.mark.skipif(not HAS_QT, reason="PySide6 not installed")


SAMPLE_STATS = {
    "tok_per_sec": 0.75,
    "cache_hits": {"vram_hits": 1725, "ram_hits": 2106,
                   "ssd_hits": 1737, "hit_rate": 0.688},
    "vram_used_gb": 9.0,
    "ram_used_gb": 11.0,
    "learning_cache": {"status": "active", "experts_tracked": 238,
                       "total_hits": 12345, "sessions": 7},
    "prewarmed_experts": 107,
}
CAPS = TierCapacities(vram_gb=12.0, ram_gb=32.0, nvme_gb=500.0)


# --------------------------------------------------------------------------
# Import safety and theme
# --------------------------------------------------------------------------

def test_gui_imports_without_display():
    """`import wisp.gui` must never require Qt — the package __init__ is
    empty so that CLI-only installs are unaffected."""
    import wisp.gui
    assert wisp.gui is not None


def test_theme_string_is_valid():
    assert isinstance(DARK_STYLESHEET, str)
    assert DARK_STYLESHEET.strip()
    # Balanced braces, or Qt silently drops the rest of the sheet.
    assert DARK_STYLESHEET.count("{") == DARK_STYLESHEET.count("}")
    for token in ("#1a1a1a", "#4fc3f7", "#e0e0e0", "#2a2a2a", "#333333"):
        assert token in DARK_STYLESHEET, f"missing {token}"


def test_telemetry_has_no_qt_dependency():
    """The parsing layer must stay importable with Qt uninstalled."""
    import sys
    import wisp.gui.telemetry as t
    assert not any(m.startswith("PySide6") for m in vars(t).values()
                   if isinstance(m, str))
    assert "PySide6" not in getattr(sys.modules[t.__name__], "__file__", "")


# --------------------------------------------------------------------------
# Stats parsing
# --------------------------------------------------------------------------

def test_stats_parse():
    snap = parse_stats(SAMPLE_STATS, CAPS)
    assert snap.online is True
    assert snap.tok_per_sec == pytest.approx(0.75)
    assert snap.hit_rate == pytest.approx(0.688)
    assert snap.observations == 1725 + 2106 + 1737
    assert snap.experts_tracked == 238
    assert snap.prewarmed == 107
    labels = [t.label for t in snap.tiers]
    assert labels == ["VRAM", "RAM", "NVMe"]


def test_stats_parse_tier_percentages():
    snap = parse_stats(SAMPLE_STATS, CAPS)
    vram, ram, nvme = snap.tiers
    assert vram.percent == 75           # 9.0 / 12.0
    assert vram.detail == "9.0/12.0 GB"
    assert ram.percent == 34            # 11.0 / 32.0
    # NVMe reports capacity only — the engine exposes no live disk usage,
    # so a filled bar there would be fabricated.
    assert nvme.percent == 0
    assert "capacity" in nvme.detail


def test_stats_parse_handles_offline():
    snap = parse_stats(None, CAPS)
    assert snap.online is False
    assert snap.tok_per_sec == 0.0
    assert len(snap.tiers) == 3
    assert all(v == PLACEHOLDER for _, v in format_stat_lines(snap))


def test_stats_parse_survives_partial_payload():
    """A server still loading answers without learning_cache; a 503 body
    is not a dict at all. Neither may raise into the Qt event loop."""
    for payload in ({}, {"tok_per_sec": 1.0}, {"cache_hits": None},
                    {"detail": "Model is still loading"}):
        snap = parse_stats(payload, CAPS)
        assert snap.online is True
        assert isinstance(snap.observations, int)
    assert parse_stats("not a dict", CAPS).online is False


def test_stats_derives_hit_rate_when_absent():
    snap = parse_stats(
        {"cache_hits": {"vram_hits": 6, "ram_hits": 2, "ssd_hits": 2}}, CAPS)
    assert snap.hit_rate == pytest.approx(0.8)     # (6+2)/10


def test_tier_percent_clamps_and_guards_zero():
    assert tier_percent(5.0, 10.0) == 50
    assert tier_percent(50.0, 10.0) == 100         # clamped
    assert tier_percent(-1.0, 10.0) == 0
    assert tier_percent(1.0, 0.0) == 0             # no divide-by-zero


def test_format_tier_unknown_capacity():
    tier = format_tier("VRAM", 3.0, 0.0)
    assert tier.percent == 0
    assert tier.detail == PLACEHOLDER


def test_format_stat_lines_online():
    lines = dict(format_stat_lines(parse_stats(SAMPLE_STATS, CAPS), 42))
    assert lines["Tokens/sec"] == "0.75"
    assert lines["Cache hit rate"] == "68.8%"
    assert lines["Tokens generated"] == "42"
    assert lines["Expert lookups"] == "5,568"
    assert lines["Pre-warmed"] == "107"


def test_capacities_detect_is_safe():
    """Must return a usable object even for a path that does not exist."""
    caps = TierCapacities.detect("Z:/definitely/not/here")
    assert caps.vram_gb >= 0 and caps.ram_gb >= 0 and caps.nvme_gb >= 0


# --------------------------------------------------------------------------
# Server thread plumbing (no Qt, no server started)
# --------------------------------------------------------------------------

def test_server_thread_allocates_a_free_port():
    from wisp.gui.server_thread import ServerThread, find_free_port
    port = find_free_port()
    assert 1024 < port < 65536
    st = ServerThread("some/model", port=port)
    assert st.base_url == f"http://127.0.0.1:{port}"
    assert st.api_base.endswith("/v1")
    assert st.is_running() is False
    assert st.is_ready() is False
    st.stop()          # stopping something never started must not raise


# --------------------------------------------------------------------------
# Widgets (offscreen)
# --------------------------------------------------------------------------

@pytest.fixture(scope="module")
def qapp():
    if not HAS_QT:
        pytest.skip("PySide6 not installed")
    app = QApplication.instance() or QApplication([])
    yield app


@requires_qt
def test_stats_panel_update_with_mock_json(qapp):
    """The spec's StatsPanel.update() path, against a mock payload."""
    from wisp.gui.widgets.stats_panel import StatsPanel
    panel = StatsPanel()
    assert panel.values["Tokens/sec"].text() == PLACEHOLDER

    panel.add_tokens(42)
    panel.update(SAMPLE_STATS)
    assert panel.values["Tokens/sec"].text() == "0.75"
    assert panel.values["Cache hit rate"].text() == "68.8%"
    assert panel.values["Tokens generated"].text() == "42"
    assert panel.values["Experts tracked"].text() == "238"
    assert "VRAM 1,725" in panel.breakdown.text()

    panel.update_from_stats(None)
    assert panel.values["Tokens/sec"].text() == PLACEHOLDER


@requires_qt
def test_tier_monitor_reflects_payload(qapp):
    from wisp.gui.widgets.tier_monitor import TierMonitor
    monitor = TierMonitor(CAPS)
    assert monitor.rows["VRAM"].bar.value() == 0

    monitor.update_from_stats(SAMPLE_STATS)
    assert monitor.rows["VRAM"].bar.value() == 75
    assert monitor.rows["RAM"].bar.value() == 34
    assert monitor.rows["VRAM"].detail.text() == "9.0/12.0 GB"

    monitor.update_from_stats(None)
    assert monitor.rows["VRAM"].bar.value() == 0


@requires_qt
def test_chat_widget_builds_openai_payload(qapp):
    from wisp.gui.widgets.chat_widget import ChatWidget
    chat = ChatWidget()
    chat.configure("http://127.0.0.1:9999/v1", "mixtral-8x7b")
    chat.temperature = 0.25
    chat.max_tokens = 128
    chat.system_prompt = "Be terse."

    payload = chat.build_payload("hello")
    assert payload["model"] == "mixtral-8x7b"
    assert payload["stream"] is True
    assert payload["temperature"] == pytest.approx(0.25)
    assert payload["max_tokens"] == 128
    assert payload["messages"][0] == {"role": "system",
                                      "content": "Be terse."}
    assert payload["messages"][-1] == {"role": "user", "content": "hello"}


@requires_qt
def test_chat_widget_parses_sse_stream(qapp):
    """Feed real SSE frames through the parser, including a split line,
    and confirm the transcript assembles correctly."""
    from wisp.gui.widgets.chat_widget import ChatWidget
    chat = ChatWidget()
    chat.configure("http://127.0.0.1:9999/v1", "m")

    def frame(content):
        import json as _json
        return ("data: " + _json.dumps(
            {"choices": [{"delta": {"content": content},
                          "finish_reason": None}]}) + "\n").encode()

    chat._buffer = b""
    payload = frame("def ") + frame("sieve") + frame("(n):")
    # Deliver in two chunks that split mid-frame — the parser must hold
    # the partial line rather than dropping or corrupting it.
    split = len(payload) // 2
    for piece in (payload[:split], payload[split:]):
        chat._buffer += piece
        while b"\n" in chat._buffer:
            line, chat._buffer = chat._buffer.split(b"\n", 1)
            chat._handle_sse_line(line.strip())

    assert chat._assistant_text == "def sieve(n):"
    assert "def sieve(n):" in chat.view.toPlainText()


@requires_qt
def test_chat_widget_ignores_done_and_junk(qapp):
    from wisp.gui.widgets.chat_widget import ChatWidget
    chat = ChatWidget()
    for line in (b"", b": keepalive", b"data: [DONE]",
                 b"data: {not json}", b"event: ping"):
        chat._handle_sse_line(line)          # must not raise
    assert chat._assistant_text == ""


@requires_qt
def test_chat_widget_surfaces_stream_error(qapp):
    from wisp.gui.widgets.chat_widget import ChatWidget
    chat = ChatWidget()
    seen = []
    chat.error_occurred.connect(seen.append)
    chat._handle_sse_line(
        b'data: {"error": {"message": "VRAM exhausted"}}')
    assert seen == ["VRAM exhausted"]


@requires_qt
def test_chat_widget_disabled_until_server_up(qapp):
    from wisp.gui.widgets.chat_widget import ChatWidget
    chat = ChatWidget()
    assert chat.send_button.isEnabled() is False
    chat.set_enabled(True)
    assert chat.send_button.isEnabled() is True


@requires_qt
def test_main_window_constructs_and_starts_offline(qapp):
    from wisp.gui.main_window import WispMainWindow
    window = WispMainWindow()
    try:
        assert window.stop_button.isEnabled() is False
        assert window.start_button.isEnabled() is True
        assert window.status_label.text() == "● Offline"
        assert window.port_value.text() == "—"
        assert window.chat.send_button.isEnabled() is False
        # Slider carries hundredths; the label shows the real value.
        window.temp_slider.setValue(105)
        assert "1.05" in window.temp_label.text()
        assert window.chat.temperature == pytest.approx(1.05)
        window.tokens_spin.setValue(1024)
        assert window.chat.max_tokens == 1024
    finally:
        window.close()


@requires_qt
def test_main_window_stop_without_start_is_safe(qapp):
    from wisp.gui.main_window import WispMainWindow
    window = WispMainWindow()
    try:
        window.stop_server()          # no server was ever started
        assert window.server is None
    finally:
        window.close()
