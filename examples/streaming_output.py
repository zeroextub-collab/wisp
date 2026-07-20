"""
examples/streaming_output.py — print tokens as they generate.

Streaming matters more on WISP than on datacenter engines: cold tokens
can take a second-plus each while the cache organizes, so showing text
immediately is the difference between "working" and "frozen".
"""

import time

from wisp import WispEngine

MODEL_DIR = "./models/glm-5.2/"


def main() -> None:
    with WispEngine(MODEL_DIR) as engine:
        prompt = "Write a Python web scraper that extracts article titles."

        start = time.perf_counter()
        n_chars = 0
        for piece in engine.stream(prompt, max_tokens=600, temperature=0.7):
            print(piece, end="", flush=True)
            n_chars += len(piece)
        elapsed = time.perf_counter() - start

        print(f"\n\n--- {n_chars} chars in {elapsed:.1f}s | "
              f"engine reports {engine.tok_per_sec():.2f} tok/s ---")


if __name__ == "__main__":
    main()
