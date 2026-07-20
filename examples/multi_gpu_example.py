"""
examples/multi_gpu_example.py — WISP's automatic multi-GPU strategies.

There is nothing to configure: the system profiler detects every GPU and
the auto-config engine picks the strategy. This example just makes the
decision visible so you can see what your machine got.

  1 GPU              -> "single":    dense layers + expert LRU on GPU 0
  2 GPUs, same size  -> "dual_same": GPU 1 becomes a pure expert cache
  2 GPUs, different  -> "dual_diff": bigger GPU takes dense, smaller
                                     takes expert overflow
  3+ GPUs            -> "pipeline":  layer ranges across GPUs via NCCL
"""

from wisp import WispEngine
from wisp.system import SystemProfiler

MODEL_DIR = "./models/glm-5.2/"


def main() -> None:
    profile = SystemProfiler().get()
    print(f"Detected {profile.gpu_count} GPU(s):")
    for g in profile.gpus:
        print(f"  GPU {g.index}: {g.name} "
              f"({g.vram_total_bytes / 1024**3:.1f} GB)")

    with WispEngine(MODEL_DIR) as engine:
        cfg = engine.config
        print(f"\nAuto-selected strategy : {cfg.gpu_strategy}")
        print(f"Primary GPU            : {cfg.primary_gpu}")
        print(f"Secondary GPU          : {cfg.secondary_gpu}")
        print(f"VRAM expert slots      : {cfg.vram_expert_count:,}")
        print(f"RAM expert slots       : {cfg.ram_expert_count:,}")
        print(f"SSD cold experts       : {cfg.ssd_expert_count:,}")

        # Generation is identical regardless of strategy — the tiers are
        # invisible to the API.
        print("\n" + engine.generate(
            "In one paragraph: why do MoE models suit consumer hardware?",
            max_tokens=200,
        ))


if __name__ == "__main__":
    main()
