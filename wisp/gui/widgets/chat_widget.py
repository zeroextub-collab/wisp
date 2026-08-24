"""
wisp.gui.widgets.chat_widget — chat transcript + streaming client.

Talks to the local server exactly the way Cursor or Open WebUI would:
POST /v1/chat/completions with stream=true, then parse the SSE frames.
Nothing here knows about WispEngine, which is the point — if this path
works, so does every other OpenAI-compatible client.

Two implementation notes worth keeping:

* HTTP goes through QNetworkAccessManager, never a blocking client. A
  synchronous request on the GUI thread would freeze the window for the
  whole generation, and WISP generations run tens of seconds.
* Bubbles are drawn with QTextBlockFormat rather than re-rendered HTML.
  Re-emitting a bubble as HTML on every token is O(n^2) in message
  length; inserting into an already-formatted block is a flat append, so
  a long reply streams as smoothly as a short one.
"""

from __future__ import annotations

import json

from PySide6.QtCore import QByteArray, Qt, QTimer, QUrl, Signal
from PySide6.QtGui import (QColor, QTextBlockFormat, QTextCharFormat,
                           QTextCursor)
from PySide6.QtNetwork import (QNetworkAccessManager, QNetworkReply,
                               QNetworkRequest)
from PySide6.QtWidgets import (QHBoxLayout, QLabel, QPlainTextEdit,
                               QPushButton, QTextBrowser, QVBoxLayout,
                               QWidget)

USER_BG = QColor("#1e3a5f")
ASSISTANT_BG = QColor("#232323")
SYSTEM_BG = QColor("#2a2410")
TEXT_FG = QColor("#e0e0e0")
DIM_FG = QColor("#8a8a8a")


class ChatWidget(QWidget):
    """Transcript, input box, and the SSE client that fills them."""

    generation_started = Signal()
    generation_finished = Signal()
    token_received = Signal(str)
    error_occurred = Signal(str)

    def __init__(self, parent=None):
        super().__init__(parent)
        self._net = QNetworkAccessManager(self)
        self._reply = None
        self._buffer = b""
        self._streaming = False
        self._stream_started = False
        self._assistant_text = ""
        self._history: list[dict] = []

        # Endpoint + sampling settings, pushed in by the main window.
        self.api_base = ""
        self.model_name = "wisp"
        self.temperature = 0.7
        self.max_tokens = 512
        self.system_prompt = ""

        layout = QVBoxLayout(self)
        layout.setContentsMargins(0, 0, 0, 0)
        layout.setSpacing(8)

        self.view = QTextBrowser()
        self.view.setObjectName("ChatView")
        self.view.setOpenExternalLinks(True)
        layout.addWidget(self.view, 1)

        self.typing = QLabel("")
        self.typing.setObjectName("TierDetail")
        layout.addWidget(self.typing)

        row = QHBoxLayout()
        row.setSpacing(8)
        self.input = QPlainTextEdit()
        self.input.setObjectName("ChatInput")
        self.input.setPlaceholderText(
            "Message the model...   (Ctrl+Enter to send)")
        self.input.setFixedHeight(74)          # ~3 lines
        self.send_button = QPushButton("Send")
        self.send_button.setObjectName("SendButton")
        self.send_button.setFixedHeight(74)
        self.send_button.clicked.connect(self.on_send_clicked)
        row.addWidget(self.input, 1)
        row.addWidget(self.send_button)
        layout.addLayout(row)

        # Animated three-dot indicator while the model is thinking.
        self._dots = 0
        self._typing_timer = QTimer(self)
        self._typing_timer.setInterval(400)
        self._typing_timer.timeout.connect(self._tick_typing)

        self.set_enabled(False)

    # ------------------------------------------------------------------ #
    # Configuration
    # ------------------------------------------------------------------ #
    def configure(self, api_base: str, model_name: str) -> None:
        self.api_base = (api_base or "").rstrip("/")
        self.model_name = model_name

    def set_enabled(self, enabled: bool) -> None:
        """Input stays dead until a server is actually up."""
        self.input.setEnabled(enabled)
        self.send_button.setEnabled(enabled)
        if not enabled:
            self.send_button.setText("Send")

    def clear(self) -> None:
        self.abort()
        self._history.clear()
        self.view.clear()

    # ------------------------------------------------------------------ #
    # Transcript rendering
    # ------------------------------------------------------------------ #
    def _append_block(self, text: str, background: QColor, alignment,
                      prefix: str = "",
                      foreground: QColor = TEXT_FG) -> None:
        cursor = self.view.textCursor()
        cursor.movePosition(QTextCursor.End)

        block = QTextBlockFormat()
        block.setBackground(background)
        block.setAlignment(alignment)
        block.setTopMargin(6)
        block.setBottomMargin(6)
        # Keep each bubble off the opposite edge so alignment reads.
        if alignment == Qt.AlignRight:
            block.setLeftMargin(70)
            block.setRightMargin(10)
        else:
            block.setLeftMargin(10)
            block.setRightMargin(70)

        char = QTextCharFormat()
        char.setForeground(foreground)

        cursor.insertBlock(block, char)
        if prefix:
            dim = QTextCharFormat()
            dim.setForeground(DIM_FG)
            cursor.insertText(prefix, dim)
        cursor.insertText(text, char)
        self.view.setTextCursor(cursor)
        self._scroll_to_end()

    def _scroll_to_end(self) -> None:
        bar = self.view.verticalScrollBar()
        bar.setValue(bar.maximum())

    def add_user_message(self, text: str) -> None:
        self._append_block(text, USER_BG, Qt.AlignRight, "you  ")

    def begin_assistant_message(self) -> None:
        self._append_block("", ASSISTANT_BG, Qt.AlignLeft, "wisp  ")
        self._stream_started = True

    def append_assistant_token(self, text: str) -> None:
        """Flat append into the open bubble — no re-render."""
        cursor = self.view.textCursor()
        cursor.movePosition(QTextCursor.End)
        char = QTextCharFormat()
        char.setForeground(TEXT_FG)
        cursor.insertText(text, char)
        self.view.setTextCursor(cursor)
        self._scroll_to_end()

    def add_system_note(self, text: str) -> None:
        self._append_block(text, SYSTEM_BG, Qt.AlignLeft, "",
                           foreground=DIM_FG)

    # ------------------------------------------------------------------ #
    # Typing indicator
    # ------------------------------------------------------------------ #
    def _tick_typing(self) -> None:
        self._dots = (self._dots + 1) % 4
        self.typing.setText("generating" + "." * self._dots)

    def _start_typing(self) -> None:
        self._dots = 0
        self.typing.setText("generating")
        self._typing_timer.start()

    def _stop_typing(self) -> None:
        self._typing_timer.stop()
        self.typing.setText("")

    # ------------------------------------------------------------------ #
    # Sending
    # ------------------------------------------------------------------ #
    def on_send_clicked(self) -> None:
        if self._streaming:
            self.abort()
            return
        text = self.input.toPlainText().strip()
        if not text:
            return
        self.input.clear()
        self.send_message(text)

    def build_payload(self, prompt: str) -> dict:
        """The exact JSON body an OpenAI client would send."""
        messages = []
        if self.system_prompt.strip():
            messages.append({"role": "system",
                             "content": self.system_prompt.strip()})
        messages.extend(self._history)
        messages.append({"role": "user", "content": prompt})
        return {
            "model": self.model_name,
            "messages": messages,
            "max_tokens": int(self.max_tokens),
            "temperature": float(self.temperature),
            "stream": True,
        }

    def send_message(self, prompt: str) -> None:
        if not self.api_base:
            self.error_occurred.emit("No server running.")
            return
        payload = self.build_payload(prompt)
        self.add_user_message(prompt)
        self._history.append({"role": "user", "content": prompt})
        self._assistant_text = ""
        self._stream_started = False
        self._buffer = b""

        request = QNetworkRequest(QUrl(f"{self.api_base}/chat/completions"))
        request.setHeader(QNetworkRequest.ContentTypeHeader,
                          "application/json")
        request.setRawHeader(b"Accept", b"text/event-stream")
        # Meaningless locally, but real clients send it and keeping the
        # header makes this request shape identical to theirs.
        request.setRawHeader(b"Authorization", b"Bearer wisp")

        body = QByteArray(json.dumps(payload).encode("utf-8"))
        self._reply = self._net.post(request, body)
        self._reply.readyRead.connect(self._on_ready_read)
        self._reply.finished.connect(self._on_finished)
        self._reply.errorOccurred.connect(self._on_error)

        self._streaming = True
        self.send_button.setText("Stop")
        self._start_typing()
        self.generation_started.emit()

    def abort(self) -> None:
        if self._reply is not None:
            self._reply.abort()

    # ------------------------------------------------------------------ #
    # SSE parsing
    # ------------------------------------------------------------------ #
    def _on_ready_read(self) -> None:
        if self._reply is None:
            return
        self._buffer += bytes(self._reply.readAll())
        # Frames are newline-delimited and a read can land mid-line, so
        # the tail stays buffered until the rest of it arrives.
        while b"\n" in self._buffer:
            line, self._buffer = self._buffer.split(b"\n", 1)
            self._handle_sse_line(line.strip())

    def _handle_sse_line(self, raw: bytes) -> None:
        if not raw or not raw.startswith(b"data:"):
            return
        data = raw[5:].strip()
        if data == b"[DONE]":
            return
        try:
            chunk = json.loads(data.decode("utf-8"))
        except (ValueError, UnicodeDecodeError):
            return

        if isinstance(chunk.get("error"), dict):
            self.error_occurred.emit(
                str(chunk["error"].get("message", "unknown error")))
            return

        for choice in chunk.get("choices", []):
            piece = (choice.get("delta") or {}).get("content")
            if not piece:
                continue
            if not self._stream_started:
                self._stop_typing()
                self.begin_assistant_message()
            self._assistant_text += piece
            self.append_assistant_token(piece)
            self.token_received.emit(piece)

    def _on_error(self, code) -> None:
        if code == QNetworkReply.OperationCanceledError:
            return                      # user pressed Stop
        message = self._reply.errorString() if self._reply else str(code)
        self.error_occurred.emit(message)

    def _on_finished(self) -> None:
        if self._buffer:
            self._handle_sse_line(self._buffer.strip())
            self._buffer = b""
        if self._assistant_text:
            self._history.append({"role": "assistant",
                                  "content": self._assistant_text})
        elif self._streaming:
            self.add_system_note("(no output)")

        self._streaming = False
        self._stop_typing()
        self.send_button.setText("Send")
        if self._reply is not None:
            self._reply.deleteLater()
            self._reply = None
        self.generation_finished.emit()

    # ------------------------------------------------------------------ #
    def keyPressEvent(self, event):        # noqa: N802  (Qt naming)
        if (event.key() in (Qt.Key_Return, Qt.Key_Enter)
                and event.modifiers() & Qt.ControlModifier):
            self.on_send_clicked()
            return
        super().keyPressEvent(event)
