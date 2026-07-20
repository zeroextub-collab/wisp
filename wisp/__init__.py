"""
WISP — Stream what shouldn't run.

Universal MoE inference engine: GPU VRAM -> System RAM -> NVMe SSD.

    from wisp import WispEngine

    engine = WispEngine("./models/glm-5.2/")
    print(engine.generate("Write a sorting algorithm", max_tokens=500))

    for token in engine.stream("Explain transformers"):
        print(token, end="", flush=True)
"""

__version__ = "1.0.0"
__author__ = "Saksham (Zero_planck)"


def __getattr__(name):
    # Lazy import so `wisp --version`, `wisp profile`, and `wisp convert`
    # work before the C extension is built.
    if name == "WispEngine":
        from .runtime.engine import WispEngine
        return WispEngine
    raise AttributeError(f"module 'wisp' has no attribute {name!r}")


__all__ = ["WispEngine", "__version__", "__author__"]
