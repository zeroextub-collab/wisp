"""
wisp.converter.partitioner — split HF checkpoint shards into the wisp layout:

    <output>/
      manifest.json
      config.json                       (copied HF config)
      dense/model_dense.safetensors     (fp16, canonical names)
      experts/L{layer:03d}_E{expert:05d}.bin
      tokenizer/tokenizer.json (+ config, specials)

EXPERT .BIN FORMAT (little-endian) — mirrored EXACTLY by
csrc/core/wisp_engine.c:read_expert_ssd(). Change one, change both.

    offset  size  field
    0       u32   magic         = 0x57455850  ("PXEW" on disk, LE)
    4       u32   version       = 1
    8       u32   layer_id
    12      u32   expert_id
    16      u32   group_size
    20      u32   n_mats        = 3  (gate, up, down — in that order)
    24      3 x { u32 rows; u32 cols;
                  u64 packed_bytes; u64 scales_bytes; u64 zeros_bytes; }  (32 B each)
    120     blobs, in order per matrix: packed, scales, zeros

Weights inside each matrix are flattened row-major; int4 packing and group
layout are defined in quantizer.py.
"""

from __future__ import annotations

import json
import shutil
import struct
from pathlib import Path

import torch
from safetensors import safe_open
from safetensors.torch import save_file
from tqdm import tqdm

from ..models.base_adapter import ModelAdapter
from .manifest import ModelManifest, expert_filename
from .quantizer import quantize_int4, QuantizedTensor

EXPERT_MAGIC = 0x57455850
EXPERT_FORMAT_VERSION = 1
EXPERT_HEADER = struct.Struct("<6I")          # magic, ver, layer, expert, gsize, nmats
EXPERT_MAT_HEADER = struct.Struct("<2I3Q")    # rows, cols, packed, scales, zeros
PROJ_ORDER = ("gate_proj", "up_proj", "down_proj")

TOKENIZER_FILES = (
    "tokenizer.json", "tokenizer_config.json", "special_tokens_map.json",
)


def write_expert_file(path: Path, layer: int, expert: int,
                      mats: dict[str, QuantizedTensor]) -> int:
    """Serialize one expert (gate/up/down int4) to its .bin blob."""
    missing = [p for p in PROJ_ORDER if p not in mats]
    if missing:
        raise ValueError(
            f"Expert L{layer}/E{expert} incomplete — missing {missing}. "
            f"Checkpoint shards are likely corrupt or partially downloaded."
        )
    ordered = [mats[p] for p in PROJ_ORDER]

    header = EXPERT_HEADER.pack(
        EXPERT_MAGIC, EXPERT_FORMAT_VERSION, layer, expert,
        ordered[0].group_size, len(ordered),
    )
    mat_headers = b"".join(
        EXPERT_MAT_HEADER.pack(
            qt.rows, qt.cols,
            qt.packed.numel(),
            qt.scales.numel() * 2,
            qt.zeros.numel() * 2,
        )
        for qt in ordered
    )
    tmp = path.with_suffix(".bin.tmp")
    with open(tmp, "wb") as f:
        f.write(header)
        f.write(mat_headers)
        for qt in ordered:
            f.write(qt.packed.cpu().numpy().tobytes())
            f.write(qt.scales.cpu().numpy().tobytes())
            f.write(qt.zeros.cpu().numpy().tobytes())
    tmp.replace(path)
    return path.stat().st_size


class Partitioner:
    """Streams checkpoint shards one at a time — never loads the full model."""

    def __init__(self, adapter: ModelAdapter,
                 source_dir: str | Path, output_dir: str | Path,
                 group_size: int = 64):
        self.adapter = adapter
        self.source_dir = Path(source_dir)
        self.output_dir = Path(output_dir)
        self.group_size = group_size
        self.expert_dir = self.output_dir / "experts"
        self.dense_dir = self.output_dir / "dense"
        self.tokenizer_dir = self.output_dir / "tokenizer"
        # Expert matrices accumulate per (layer, expert) until complete,
        # then flush to disk — bounded by one shard's worth of experts.
        self._pending: dict[tuple[int, int], dict[str, QuantizedTensor]] = {}
        self._dense: dict[str, torch.Tensor] = {}
        self._experts_written = 0
        self._expert_bytes = 0
        self._kda_tensors = 0
        self._dropped: list[str] = []

    # ------------------------------------------------------------------ #
    def run(self, shard_paths=None) -> ModelManifest:
        """
        Partition the checkpoint. `shard_paths` may be any iterable of
        shard Paths — including ShardDownloader.download_iter(), which
        lets conversion overlap the remaining download (no need for all
        shards up front). Defaults to globbing source_dir.
        """
        for d in (self.output_dir, self.expert_dir,
                  self.dense_dir, self.tokenizer_dir):
            d.mkdir(parents=True, exist_ok=True)

        if shard_paths is None:
            shard_paths = sorted(self.source_dir.glob("*.safetensors"))
            if not shard_paths:
                raise FileNotFoundError(
                    f"No .safetensors shards in {self.source_dir}. "
                    f"Download the model first (wisp convert does this "
                    f"for you).")

        print(f"  [WISP] Partitioning -> {self.output_dir}")
        pattern = self.adapter.expert_weight_pattern
        self._expert_bar = tqdm(
            total=self.adapter.total_expert_count,
            unit="expert", desc="  experts", leave=False)
        try:
            for shard in shard_paths:
                self._process_shard(Path(shard), pattern)
            self._flush_complete_experts(force=True)
        finally:
            self._expert_bar.close()
            self._expert_bar = None

        self._save_dense()
        self._copy_tokenizer()
        self._copy_config()
        manifest = self._write_manifest()

        print(f"  [WISP] Done: {self._experts_written} experts "
              f"({self._expert_bytes / 1e9:.1f} GB int4), "
              f"{len(self._dense)} dense tensors.")
        if self._dropped:
            print(f"  [WISP] Dropped {len(self._dropped)} non-weight tensors "
                  f"(rotary buffers etc.)")
        if hasattr(self.adapter, "is_kda_layer"):
            # Loud on mismatch: KDA tensor names are unverified against
            # released weights, so silence here would mean the engine
            # quietly falls back to GQA and produces wrong output.
            expected = (self.adapter.num_kda_layers
                        * len(self.adapter.kda_projection_names))
            print(f"  [WISP] KDA projections mapped: "
                  f"{self._kda_tensors}/{expected}")
            if self._kda_tensors == 0:
                print("  [WISP] WARNING: no KDA tensors matched. The "
                      "checkpoint uses names this adapter does not know; "
                      "KDA layers will fall back to the GQA path and "
                      "output will be WRONG. Report the real names at "
                      "github.com/zeroextub-collab/wisp/issues")
            elif self._kda_tensors < expected:
                print(f"  [WISP] WARNING: only {self._kda_tensors} of "
                      f"{expected} KDA tensors matched — partial mapping.")
        return manifest

    # ------------------------------------------------------------------ #
    def _process_shard(self, shard: Path, pattern) -> None:
        with safe_open(str(shard), framework="pt", device="cpu") as f:
            for name in f.keys():
                m = pattern.match(name)
                if m:
                    layer = int(m.group("layer"))
                    expert = int(m.group("expert"))
                    # Families name expert matrices differently (Mixtral:
                    # w1/w3/w2) — normalize onto canonical gate/up/down so
                    # every .bin has the same layout the C engine expects.
                    proj = self.adapter.normalize_expert_proj(
                        m.group("proj"))
                    tensor = f.get_tensor(name)
                    qt = quantize_int4(tensor, self.group_size)
                    self._pending.setdefault((layer, expert), {})[proj] = qt
                    continue
                canonical = self.adapter.canonical_dense_name(name)
                if canonical is not None:
                    self._dense[canonical] = (
                        f.get_tensor(name).to(torch.float16).contiguous())
                    if ".kda." in canonical:
                        self._kda_tensors += 1
                else:
                    self._dropped.append(name)
        self._flush_complete_experts()

    def _flush_complete_experts(self, force: bool = False) -> None:
        done_keys = [
            k for k, mats in self._pending.items()
            if all(p in mats for p in PROJ_ORDER)
        ]
        for layer, expert in done_keys:
            mats = self._pending.pop((layer, expert))
            path = self.expert_dir / expert_filename(layer, expert)
            self._expert_bytes += write_expert_file(path, layer, expert, mats)
            self._experts_written += 1
            if getattr(self, "_expert_bar", None) is not None:
                self._expert_bar.update(1)
        if force and self._pending:
            incomplete = sorted(self._pending.keys())[:5]
            raise RuntimeError(
                f"{len(self._pending)} experts never completed across all "
                f"shards (first few: {incomplete}). The download is likely "
                f"missing shards — re-run `wisp convert` to resume it."
            )

    # ------------------------------------------------------------------ #
    def _save_dense(self) -> None:
        if not self._dense:
            raise RuntimeError(
                "No dense tensors found — the adapter's canonical_dense_name "
                "mapping does not match this checkpoint's tensor names."
            )
        save_file(self._dense, str(self.dense_dir / "model_dense.safetensors"))

    def _copy_tokenizer(self) -> None:
        copied = 0
        for fname in TOKENIZER_FILES:
            src = self.source_dir / fname
            if src.exists():
                shutil.copy2(src, self.tokenizer_dir / fname)
                copied += 1
        if copied == 0:
            raise FileNotFoundError(
                f"No tokenizer files found in {self.source_dir} — "
                f"expected at least tokenizer.json."
            )

    def _copy_config(self) -> None:
        src = self.source_dir / "config.json"
        if src.exists():
            shutil.copy2(src, self.output_dir / "config.json")

    # ------------------------------------------------------------------ #
    def _write_manifest(self) -> ModelManifest:
        extra = {}
        cfg_path = self.output_dir / "config.json"
        if cfg_path.exists():
            with open(cfg_path, encoding="utf-8") as f:
                hf_cfg = json.load(f)
            for src_key, dst_key in (
                ("intermediate_size",        "intermediate_size"),
                ("moe_intermediate_size",    "moe_intermediate_size"),
                ("num_attention_heads",      "num_attention_heads"),
                ("num_key_value_heads",      "num_kv_heads"),
                ("max_position_embeddings",  "max_position_embeddings"),
                ("rope_theta",               "rope_theta"),
                ("rms_norm_eps",             "rms_norm_eps"),
                ("q_lora_rank",              "q_lora_rank"),
                ("kv_lora_rank",             "kv_lora_rank"),
                ("qk_nope_head_dim",         "qk_nope_head_dim"),
                ("qk_rope_head_dim",         "qk_rope_head_dim"),
                ("v_head_dim",               "v_head_dim"),
            ):
                if src_key in hf_cfg and hf_cfg[src_key] is not None:
                    extra[dst_key] = hf_cfg[src_key]

        manifest = ModelManifest.build(
            self.adapter,
            quant_dtype="int4",
            group_size=self.group_size,
            architecture_extra=extra,
        )
        manifest.save(self.output_dir)
        return manifest


def verify_converted_model(model_dir: str | Path, progress: bool = False
                           ) -> tuple[int, int, list[str]]:
    """
    Post-conversion integrity check: every expert file the manifest
    promises must exist, be non-trivially sized, and match its siblings
    (all experts in a family share one shape, so their file sizes must
    agree). Also checks the dense weights and tokenizer.

    Returns (ok_count, expected_count, problems).
    """
    model_dir = Path(model_dir)
    manifest = ModelManifest.load(model_dir)
    arch = manifest.architecture
    n_layers = arch["num_layers"]
    n_experts = arch["num_experts_per_layer"]
    expected = manifest.performance.get(
        "total_expert_count", n_layers * n_experts)

    problems: list[str] = []
    dense = model_dir / manifest.files["dense_layers"]
    if not dense.exists():
        problems.append(f"dense weights missing: {dense}")
    tok = model_dir / manifest.files["tokenizer_dir"] / "tokenizer.json"
    if not tok.exists():
        problems.append(f"tokenizer missing: {tok}")

    expert_dir = model_dir / manifest.files["expert_dir"]
    ok = 0
    ref_size: int | None = None
    layer_iter = range(n_layers)
    if progress:
        layer_iter = tqdm(layer_iter, unit="layer", desc="  verify")
    for layer in layer_iter:
        layer_missing: list[str] = []
        layer_found = 0
        for expert in range(n_experts):
            path = expert_dir / expert_filename(layer, expert)
            if not path.exists():
                # Dense-MLP early layers legitimately have NO experts at
                # all; a layer with SOME experts but not all is corrupt.
                layer_missing.append(path.name)
                continue
            layer_found += 1
            size = path.stat().st_size
            if size < 120:   # smaller than the header — corrupt
                problems.append(f"CORRUPT (too small): {path.name}")
                continue
            if ref_size is None:
                ref_size = size
            elif abs(size - ref_size) > ref_size * 0.01:
                # All experts of a family share one shape; allow <1%
                # slack for group-count rounding, flag anything more.
                problems.append(
                    f"SIZE MISMATCH: {path.name} is "
                    f"{size / 1e6:.1f}MB, expected "
                    f"{ref_size / 1e6:.1f}MB")
                continue
            ok += 1
        if 0 < layer_found < n_experts:
            problems.extend(f"MISSING: {name}" for name in layer_missing)

    if ok == 0:
        problems.append("no expert files found at all")
    return ok, expected, problems
