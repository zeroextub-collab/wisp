#!/usr/bin/env python
"""
scripts/benchmark.py — standalone WISP benchmark harness.

Richer than `wisp benchmark`: runs cold / warm / hot passes, per-pass
cache-tier breakdowns, optional speculative comparison, and writes a
JSON report you can diff across hardware or WISP versions.

    python scripts/benchmark.py --model ./models/glm-5.2/ --tokens 100
    python scripts/benchmark.py --model ./models/glm-5.2/ \
        --tokens 200 --report bench_report.json --compare-speculative
"""

from __future__ import annotations

import argparse
import json
import platform
import sys
import time
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent.parent))

from wisp import WispEngine, __version__  # noqa: E402

PROMPTS = {
    "code":    "Write a Python function that finds the longest common "
               "subsequence of two strings, with tests.",
    "math":    "Prove that the square root of 2 is irrational, step by step.",
    "writing": "Write a short story about a lighthouse keeper who receives "
               "a message in a bottle.",
}


def run_pass(engine: WispEngine, name: str, prompt: str,
             tokens: int) -> dict:
    t0 = time.perf_counter()
    result = engine.generate_detailed(prompt, max_tokens=tokens)
    elapsed = time.perf_counter() - t0
    stats = engine.cache_stats()
    row = {
        "pass": name,
        "tokens": result.completion_tokens,
        "seconds": round(elapsed, 2),
        "tok_per_sec": result.tok_per_sec,
        "vram_hits": stats.get("vram_hits", 0),
        "ram_hits": stats.get("ram_hits", 0),
        "ssd_hits": stats.get("ssd_hits", 0),
        "hit_rate": round(stats.get("hit_rate", 0.0), 4),
    }
    print(f"  [{name:>5}] {row['tok_per_sec']:6.2f} tok/s | "
          f"hit rate {row['hit_rate']:.1%} | "
          f"vram {row['vram_hits']:,} / ram {row['ram_hits']:,} / "
          f"ssd {row['ssd_hits']:,}")
    return row


def main() -> int:
    ap = argparse.ArgumentParser(description="WISP benchmark harness")
    ap.add_argument("--model", required=True, help="Converted model dir")
    ap.add_argument("--tokens", type=int, default=100)
    ap.add_argument("--domain", choices=sorted(PROMPTS), default="code")
    ap.add_argument("--report", default=None, help="Write JSON report here")
    ap.add_argument("--compare-speculative", action="store_true",
                    help="Also benchmark with speculative decoding on")
    args = ap.parse_args()

    prompt = PROMPTS[args.domain]
    print(f"\n  WISP {__version__} benchmark — {args.model}")
    print(f"  Domain: {args.domain} | tokens/pass: {args.tokens}\n")

    engine = WispEngine(args.model, use_speculative=False)
    passes = []
    try:
        print("  Pass 1/3 — cold (caches cleared)")
        engine.clear_expert_cache()
        passes.append(run_pass(engine, "cold", prompt, args.tokens))

        print("  Pass 2/3 — warm (caches self-organized once)")
        passes.append(run_pass(engine, "warm", prompt, args.tokens))

        print("  Pass 3/3 — hot (repeated domain)")
        passes.append(run_pass(engine, "hot", prompt, args.tokens))

        if args.compare_speculative:
            print("  Bonus — speculative decoding")
            t0 = time.perf_counter()
            pieces = list(engine.stream(prompt, max_tokens=args.tokens,
                                        use_speculative=True))
            elapsed = time.perf_counter() - t0
            n = max(1, len(engine.adapter.tokenize("".join(pieces))) - 1)
            spec_rate = round(n / elapsed, 2)
            print(f"  [ spec] {spec_rate:6.2f} tok/s effective")
            passes.append({"pass": "speculative", "tokens": n,
                           "seconds": round(elapsed, 2),
                           "tok_per_sec": spec_rate})
    finally:
        engine.close()

    report = {
        "wisp_version": __version__,
        "model": str(args.model),
        "domain": args.domain,
        "tokens_per_pass": args.tokens,
        "platform": platform.platform(),
        "timestamp": time.strftime("%Y-%m-%dT%H:%M:%SZ", time.gmtime()),
        "passes": passes,
    }
    if args.report:
        Path(args.report).write_text(json.dumps(report, indent=2),
                                     encoding="utf-8")
        print(f"\n  Report written to {args.report}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
