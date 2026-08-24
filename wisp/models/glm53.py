"""
wisp.models.glm53 — GLM-5.3 readiness stub.

GLM-5.3 adapter. Architecture not yet published.
Inherits GLM-5.2 layout as a baseline.
Will be updated the day weights are released.
Estimated day-0 turnaround: 24-48 hours.

WHY A STUB IS WORTH SHIPPING
Day-0 support is mostly a naming and plumbing problem, not a research
one: the registry entry, the CLI spelling, the manifest fields and the
tier math all have to exist and agree before anyone can convert
anything. Having them in place means the release-day change is a handful
of constants once config.json is public, rather than a new adapter
written under time pressure.

WHAT IT DELIBERATELY WILL NOT DO
`wisp info --model glm-5.3` works, because planning hardware against a
GLM-5.2-shaped baseline is genuinely useful. `convert()` raises instead
of running: converting against guessed architecture would produce a
model directory that looks valid, passes verification, and generates
garbage — the worst possible failure mode, discovered only after a
370GB download.
"""

from __future__ import annotations

from .glm52 import GLM52Adapter
from . import constants as C


class GLM53Adapter(GLM52Adapter):
    """GLM-5.3, pre-release. Every number here is inherited from GLM-5.2
    and is a PLACEHOLDER until Zhipu publishes the real architecture."""

    # Set True in the same commit that fills in the real constants.
    architecture_published = False

    @property
    def name(self) -> str:
        return "GLM-5.3 (pre-release)"

    @property
    def family(self) -> str:
        return "glm53"

    @property
    def hf_model_id(self) -> str:
        return C.HF_MODEL_ID["glm53"]

    # ------------------------------------------------------------------ #
    def convert(self, *args, **kwargs):
        """Refuse to convert against a guessed architecture."""
        raise NotImplementedError(
            "GLM-5.3 weights are not yet released. "
            "Adapter inherits GLM-5.2 as a starting point. "
            "Converting against a guessed architecture would produce a "
            "model that looks valid and generates garbage. "
            "Check github.com/zeroextub-collab/wisp for updates.")

    def manifest_extras(self) -> dict:
        return {
            "architecture_published": self.architecture_published,
            "baseline": "glm52",
            "note": ("placeholder architecture inherited from GLM-5.2; "
                     "not valid for conversion"),
        }
