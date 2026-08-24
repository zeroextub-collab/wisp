"""
wisp.gui.theme — one dark stylesheet for the whole application.

Terminal-meets-dashboard: near-black ground, a single light-blue accent
carrying every interactive state, and monospace anywhere a number might
be compared against another number.
"""

BG          = "#1a1a1a"
BG_PANEL    = "#202020"
BG_INPUT    = "#2a2a2a"
BORDER      = "#333333"
TEXT        = "#e0e0e0"
TEXT_DIM    = "#8a8a8a"
ACCENT      = "#4fc3f7"
ACCENT_DARK = "#2b8fbd"
GREEN       = "#66bb6a"
RED         = "#ef5350"
MONO        = "Consolas, 'JetBrains Mono', 'DejaVu Sans Mono', monospace"

DARK_STYLESHEET = f"""
QWidget {{
    background-color: {BG};
    color: {TEXT};
    font-family: -apple-system, 'Segoe UI', Roboto, sans-serif;
    font-size: 13px;
}}
QFrame#Panel {{
    background-color: {BG_PANEL};
    border: 1px solid {BORDER};
    border-radius: 6px;
}}
QLabel#SectionTitle {{
    color: {TEXT_DIM};
    font-size: 11px;
    font-weight: 600;
    letter-spacing: 1px;
    padding: 2px 0;
}}
QLabel#StatKey   {{ color: {TEXT_DIM}; font-family: {MONO}; font-size: 12px; }}
QLabel#StatValue {{ color: {ACCENT};   font-family: {MONO}; font-size: 12px;
                    font-weight: 600; }}
QLabel#TierLabel {{ color: {TEXT};     font-family: {MONO}; font-size: 12px; }}
QLabel#TierDetail{{ color: {TEXT_DIM}; font-family: {MONO}; font-size: 11px; }}
QLabel#StatusOnline  {{ color: {GREEN}; font-weight: 600; }}
QLabel#StatusOffline {{ color: {TEXT_DIM}; font-weight: 600; }}

QPushButton {{
    background-color: {BG_INPUT};
    border: 1px solid {BORDER};
    border-radius: 5px;
    padding: 7px 14px;
    color: {TEXT};
}}
QPushButton:hover:!disabled  {{ border-color: {ACCENT}; color: {ACCENT}; }}
QPushButton:pressed          {{ background-color: #1f1f1f; }}
QPushButton:disabled         {{ color: #5a5a5a; border-color: #2a2a2a; }}
QPushButton#StartButton {{
    background-color: {GREEN}; color: #10240f; border: none;
    font-weight: 600;
}}
QPushButton#StartButton:hover:!disabled {{ background-color: #7bcc7f; }}
QPushButton#StopButton {{
    background-color: {RED}; color: #2a0b0a; border: none;
    font-weight: 600;
}}
QPushButton#StopButton:hover:!disabled {{ background-color: #f4736f; }}
QPushButton#SendButton {{
    background-color: {ACCENT}; color: #05202b; border: none;
    font-weight: 600; min-width: 84px;
}}
QPushButton#SendButton:hover:!disabled {{ background-color: #7fd4fa; }}

QLineEdit, QPlainTextEdit, QTextBrowser, QSpinBox, QComboBox {{
    background-color: {BG_INPUT};
    border: 1px solid {BORDER};
    border-radius: 5px;
    padding: 5px;
    color: {TEXT};
    selection-background-color: {ACCENT_DARK};
}}
QLineEdit:focus, QPlainTextEdit:focus, QSpinBox:focus {{
    border-color: {ACCENT};
}}
QTextBrowser#ChatView {{
    background-color: #141414;
    font-family: {MONO};
    font-size: 13px;
    padding: 10px;
}}
QPlainTextEdit#ChatInput {{ font-family: {MONO}; font-size: 13px; }}

QProgressBar {{
    background-color: {BG_INPUT};
    border: 1px solid {BORDER};
    border-radius: 4px;
    height: 10px;
    text-align: center;
    color: transparent;
}}
QProgressBar::chunk {{ background-color: {ACCENT}; border-radius: 3px; }}

QSlider::groove:horizontal {{
    background: {BG_INPUT}; height: 4px; border-radius: 2px;
}}
QSlider::handle:horizontal {{
    background: {ACCENT}; width: 13px; margin: -5px 0; border-radius: 6px;
}}
QSlider::sub-page:horizontal {{ background: {ACCENT_DARK}; border-radius: 2px; }}

QScrollBar:vertical {{
    background: {BG}; width: 9px; margin: 0;
}}
QScrollBar::handle:vertical {{
    background: #3a3a3a; border-radius: 4px; min-height: 24px;
}}
QScrollBar::handle:vertical:hover {{ background: #4a4a4a; }}
QScrollBar::add-line, QScrollBar::sub-line {{ height: 0; }}
QToolTip {{
    background-color: {BG_INPUT}; color: {TEXT};
    border: 1px solid {ACCENT}; padding: 4px;
}}
"""
