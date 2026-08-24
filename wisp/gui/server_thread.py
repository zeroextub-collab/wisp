"""
wisp.gui.server_thread — runs the WISP API server inside the GUI process.

The GUI is an OpenAI API client. Rather than shelling out to `wisp serve`
and scraping its stdout, it hosts the very same WispServer app on a
private loopback port and talks HTTP to it. One code path serves both
the CLI and the GUI, and there is no output parsing to break.

Two details that make threading here non-obvious:

* uvicorn.run() installs signal handlers, which only works on the main
  thread — calling it from a worker raises ValueError. We build
  uvicorn.Config/Server by hand and neuter install_signal_handlers.
* Shutdown is cooperative: setting `should_exit` lets uvicorn close its
  sockets and run the app's lifespan shutdown, which is what persists
  the learning cache. Killing the thread would lose that.
"""

from __future__ import annotations

import socket
import threading
from pathlib import Path


def find_free_port(host: str = "127.0.0.1") -> int:
    """Ask the OS for an unused port. Inherently racy — the port is free
    when we look and bound moments later — but it is the standard trick
    and the window is small on loopback."""
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.bind((host, 0))
        return int(s.getsockname()[1])


class ServerThread:
    """
    Owns the lifecycle of an in-process WISP API server.

    start() returns immediately; the model loads on the server's own
    lifespan startup, so the UI stays responsive while a multi-GB model
    is read. Poll `is_ready()` (or just let the stats timer discover it).
    """

    def __init__(self, model_dir: str | Path, host: str = "127.0.0.1",
                 port: int | None = None):
        self.model_dir = str(model_dir)
        self.host = host
        self.port = port or find_free_port(host)
        self._server = None
        self._thread: threading.Thread | None = None
        self._error: BaseException | None = None

    # ------------------------------------------------------------------ #
    @property
    def base_url(self) -> str:
        return f"http://{self.host}:{self.port}"

    @property
    def api_base(self) -> str:
        return f"{self.base_url}/v1"

    @property
    def error(self) -> BaseException | None:
        """Whatever killed the server thread, if anything."""
        return self._error

    def is_running(self) -> bool:
        return self._thread is not None and self._thread.is_alive()

    def is_ready(self) -> bool:
        """True once uvicorn reports the socket is up. The model may
        still be loading — /v1/stats answers 503 until it is not."""
        return bool(self._server is not None
                    and getattr(self._server, "started", False))

    # ------------------------------------------------------------------ #
    def start(self) -> None:
        if self.is_running():
            return
        try:
            import uvicorn
            from ..server.app import HAS_FASTAPI, INSTALL_HINT, WispServer
        except ImportError as e:                      # pragma: no cover
            raise ImportError(
                "The WISP GUI needs the server extra:\n"
                "    pip install 'wisp-engine[server]'") from e
        if not HAS_FASTAPI:
            raise ImportError(INSTALL_HINT)

        wisp_server = WispServer(model_dir=self.model_dir, host=self.host,
                                 port=self.port)
        config = uvicorn.Config(wisp_server.app, host=self.host,
                                port=self.port, log_level="warning",
                                access_log=False)
        server = uvicorn.Server(config)
        # Signal handlers are a main-thread-only facility.
        server.install_signal_handlers = lambda: None
        self._server = server
        self._error = None

        def _run():
            try:
                server.run()
            except BaseException as exc:              # noqa: BLE001
                self._error = exc

        self._thread = threading.Thread(target=_run, daemon=True,
                                        name="wisp-server")
        self._thread.start()

    def stop(self, timeout: float = 10.0) -> None:
        """Ask uvicorn to wind down and wait. The wait matters: the
        app's shutdown hook calls engine.shutdown(), which is what writes
        .wisp_usage for the next session."""
        if self._server is not None:
            self._server.should_exit = True
        if self._thread is not None:
            self._thread.join(timeout=timeout)
            if self._thread.is_alive():
                # Daemon thread; the process can still exit cleanly.
                self._error = TimeoutError(
                    f"server did not stop within {timeout}s")
        self._thread = None
        self._server = None
