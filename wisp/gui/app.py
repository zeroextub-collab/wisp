"""
wisp.gui.app — desktop GUI entry point (`wisp-gui`).

The GUI is an OpenAI API client that happens to host its own server:
it runs the same WispServer the `wisp serve` command runs, in a thread,
on a private loopback port, and talks HTTP to it. No subprocess, no
stdout parsing — if the GUI works, every other OpenAI client works too,
because it is using the identical surface.

    wisp-gui
    wisp-gui ./models/mixtral-8x7b        # pre-fill the model path
"""

from __future__ import annotations

import sys

MISSING_QT = (
    "The WISP desktop GUI needs PySide6 and the server extra:\n"
    "    pip install 'wisp-engine[gui,server]'\n"
    "or:\n"
    "    pip install PySide6 fastapi uvicorn"
)


def main(argv: list[str] | None = None) -> int:
    """Launch the window. Returns a process exit code."""
    argv = list(sys.argv[1:] if argv is None else argv)

    try:
        from PySide6.QtWidgets import QApplication
    except ImportError:
        print(MISSING_QT, file=sys.stderr)
        return 1

    from .main_window import WispMainWindow
    from .theme import DARK_STYLESHEET

    model_dir = None
    for arg in argv:
        if not arg.startswith("-"):
            model_dir = arg
            break

    app = QApplication.instance() or QApplication(["wisp-gui"])
    app.setApplicationName("WISP")
    app.setApplicationDisplayName("WISP")
    app.setStyleSheet(DARK_STYLESHEET)

    window = WispMainWindow(model_dir=model_dir)
    window.show()
    # aboutToQuit also fires on Cmd+Q / taskbar close, where closeEvent
    # may not run — the server must come down either way.
    app.aboutToQuit.connect(window.stop_server)
    return app.exec()


if __name__ == "__main__":
    raise SystemExit(main())
