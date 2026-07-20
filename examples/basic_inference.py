"""
examples/basic_inference.py — the simplest possible WISP program.

Prerequisite: a converted model directory, e.g.
    wisp convert --model glm-5.2 --output ./models/
"""

from wisp import WispEngine

MODEL_DIR = "./models/glm-5.2/"


def main() -> None:
    # WispEngine profiles your hardware on first run (cached 7 days),
    # calculates the VRAM/RAM/SSD tier split automatically, and loads
    # dense layers to the GPU. No configuration needed.
    with WispEngine(MODEL_DIR) as engine:
        result = engine.generate(
            "Explain quantum entanglement in simple terms",
            max_new_tokens=300,
            temperature=0.7,
        )
        print(result)

        # The tier caches warmed up during that generation — a second
        # request in the same domain is noticeably faster.
        stats = engine.cache_stats()
        print(f"\n--- cache: {stats['hit_rate']:.1%} hit rate "
              f"(vram {stats['vram_hits']:,} / ram {stats['ram_hits']:,} / "
              f"ssd {stats['ssd_hits']:,}) ---")


if __name__ == "__main__":
    main()
