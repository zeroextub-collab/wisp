"""
wisp.hub — HuggingFace Hub upload preparation for converted models.

Converting a frontier MoE takes hours of download + quantization; a
converted model is just files. This module lets anyone who converted one
share it, so the next person with slow internet skips the whole pipeline:

    wisp upload --model ./models/glm-5.2/ --repo you/glm-5.2-wisp

We validate, write a model card, and print the exact upload command —
the actual transfer runs through huggingface-cli so credentials and
resumable large-file handling stay HF's problem, not ours.
"""

from __future__ import annotations

from pathlib import Path

from .converter.manifest import ModelManifest
from .logging import get_logger

log = get_logger("hub")

MODEL_CARD_TEMPLATE = """\
---
license: {license}
library_name: wisp
tags:
- wisp
- mixture-of-experts
- int4
- streaming-inference
base_model: {hf_model_id}
---

# {model_name} — WISP format

Pre-converted **{model_name}** ({params_b}B parameters) in the
[WISP](https://github.com/zeroextub-collab/wisp) 3-tier streaming
layout: int4 expert blobs + fp16 dense weights, ready to run on
consumer hardware without re-conversion.

## Use it

```bash
pip install wisp-engine
huggingface-cli download {repo_id} --local-dir ./models/{dir_name}
wisp verify --model ./models/{dir_name}     # integrity check
wisp chat --model ./models/{dir_name}
```

## What's inside

| Path | Contents |
|------|----------|
| `manifest.json` | Architecture + quantization + file layout |
| `dense/model_dense.safetensors` | Attention, embeddings, shared experts, norms (fp16) |
| `experts/L###_E#####.bin` | {n_experts:,} routed experts, int4 group-{group_size} |
| `tokenizer/` | HuggingFace tokenizer files |

Architecture: {n_layers} layers x {experts_per_layer} experts, top-{top_k}
routing -> {lookups} expert lookups per token.

Converted with `wisp convert` v{wisp_version}. Original weights:
[{hf_model_id}](https://huggingface.co/{hf_model_id}) — all model
licenses and usage terms of the original apply.
"""


class WispHubUploader:
    """
    Prepares a WISP-format model for HuggingFace Hub upload.
    Users who convert a model can optionally share it so others
    don't have to re-convert.
    """

    def __init__(self, model_dir: str | Path):
        self.model_dir = Path(model_dir)

    # ------------------------------------------------------------------ #
    def validate(self) -> ModelManifest:
        """Structure check — refuses to prepare a broken upload."""
        from .converter.partitioner import verify_converted_model

        if not (self.model_dir / "manifest.json").exists():
            raise FileNotFoundError(
                f"{self.model_dir} is not a converted WISP model "
                f"(no manifest.json).\n"
                f"Convert first: wisp convert --model <name> "
                f"--output {self.model_dir.parent}")

        manifest = ModelManifest.load(self.model_dir)
        ok, expected, problems = verify_converted_model(self.model_dir)
        if problems:
            preview = "\n  ".join(problems[:5])
            raise RuntimeError(
                f"Refusing to prepare a corrupted model for upload — "
                f"{ok}/{expected} experts OK, "
                f"{len(problems)} problems:\n  {preview}\n"
                f"Repair first: wisp convert --model "
                f"{manifest.model_family} --output "
                f"{self.model_dir.parent} (resumes)")
        log.info("upload validation ok: %d experts", ok)
        return manifest

    # ------------------------------------------------------------------ #
    def write_model_card(self, manifest: ModelManifest,
                         repo_id: str) -> Path | None:
        """Write README.md into the model dir (never overwrites one)."""
        card_path = self.model_dir / "README.md"
        if card_path.exists():
            log.info("model card already exists, leaving it untouched")
            return None
        arch = manifest.architecture
        card = MODEL_CARD_TEMPLATE.format(
            license="other",
            hf_model_id=manifest.hf_model_id,
            model_name=manifest.model_name,
            params_b=manifest.total_parameters // 1_000_000_000,
            repo_id=repo_id,
            dir_name=self.model_dir.name,
            n_experts=manifest.performance["total_expert_count"],
            group_size=manifest.quantization["group_size"],
            n_layers=arch["num_layers"],
            experts_per_layer=arch["num_experts_per_layer"],
            top_k=arch["top_k_routing"],
            lookups=arch["total_expert_lookups_per_token"],
            wisp_version=manifest.wisp_convert_version,
        )
        card_path.write_text(card, encoding="utf-8")
        return card_path

    # ------------------------------------------------------------------ #
    def prepare_upload(self, repo_id: str) -> str:
        """
        Validate, write the model card, and return the upload command.
        The command is returned (and printed by the CLI) rather than
        executed — pushing hundreds of GB is a decision the user runs
        themselves, with their own HF credentials.
        """
        manifest = self.validate()
        card = self.write_model_card(manifest, repo_id)
        if card:
            log.info("model card written: %s", card)
        return (f"huggingface-cli upload {repo_id} {self.model_dir} "
                f"--repo-type model")
