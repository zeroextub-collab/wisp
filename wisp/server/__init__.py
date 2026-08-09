"""wisp.server — OpenAI-compatible HTTP API for WispEngine."""

from .app import HAS_FASTAPI, INSTALL_HINT, WispServer, format_messages

__all__ = ["WispServer", "format_messages", "HAS_FASTAPI", "INSTALL_HINT"]
