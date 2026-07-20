"""
wisp.converter.downloader — shard-by-shard, resumable HuggingFace downloads.

Frontier MoE checkpoints are 300GB-1.4TB. This downloader:
  - lists the repo's files (with sizes + LFS hashes) up front,
  - checks disk space BEFORE writing a byte,
  - downloads shard by shard with byte-level resume,
  - verifies each shard's SHA256 against the hub's LFS record,
  - records rich checkpoint state (download_state.json) after every
    shard so a killed process resumes exactly where it stopped,
  - can stream completed shards to the converter (`download_iter`) so
    partitioning starts before the download finishes.
"""

from __future__ import annotations

import hashlib
import shutil
import time
from datetime import datetime, timezone
from pathlib import Path
from typing import Iterator

from huggingface_hub import HfApi, hf_hub_download
from tqdm import tqdm

from ..logging import get_logger
from ..system import cache as wisp_cache

log = get_logger("converter.downloader")

MAX_RETRIES = 5
RETRY_BASE_DELAY = 2.0  # seconds — doubles each retry

# Weight shards stream through the pipeline; support files download first.
SHARD_PATTERN = ".safetensors"
SUPPORT_FILES = [
    "*.safetensors.index.json",
    "config.json",
    "generation_config.json",
    "tokenizer.json",
    "tokenizer_config.json",
    "special_tokens_map.json",
]


def _now_iso() -> str:
    return datetime.now(timezone.utc).strftime("%Y-%m-%dT%H:%M:%SZ")


def _state_name(repo_id: str) -> str:
    return "download_state_" + repo_id.replace("/", "__") + ".json"


def _sha256_of(path: Path, chunk: int = 8 * 1024 * 1024) -> str:
    h = hashlib.sha256()
    with open(path, "rb") as f:
        while block := f.read(chunk):
            h.update(block)
    return h.hexdigest()


class ShardDownloader:

    def __init__(self, repo_id: str, local_dir: str | Path,
                 revision: str = "main", token: str | None = None,
                 verify_hashes: bool = True):
        self.repo_id = repo_id
        self.revision = revision
        self.token = token
        self.verify_hashes = verify_hashes
        self.local_dir = Path(local_dir)
        self.local_dir.mkdir(parents=True, exist_ok=True)
        self.api = HfApi(token=token)
        self._file_meta: dict[str, dict] = {}

    # ------------------------------------------------------------------ #
    # Repo inspection
    # ------------------------------------------------------------------ #
    def fetch_file_list(self) -> tuple[list[str], list[str]]:
        """Returns (shard_files, support_files) with size/hash metadata
        cached for the space check and SHA verification."""
        import fnmatch
        info = self.api.model_info(
            self.repo_id, revision=self.revision, files_metadata=True)
        shards, support = [], []
        for sib in info.siblings or []:
            name = sib.rfilename
            self._file_meta[name] = {
                "size": getattr(sib, "size", None) or 0,
                "sha256": (getattr(sib, "lfs", None) or {}).get("sha256")
                if isinstance(getattr(sib, "lfs", None), dict)
                else getattr(getattr(sib, "lfs", None), "sha256", None),
            }
            if name.endswith(SHARD_PATTERN):
                shards.append(name)
            elif any(fnmatch.fnmatch(name, p) for p in SUPPORT_FILES):
                support.append(name)
        if not shards:
            raise RuntimeError(
                f"No .safetensors shards found in {self.repo_id}. "
                f"Is the repo published yet?")
        return sorted(shards), sorted(support)

    def total_download_bytes(self, files: list[str]) -> int:
        return sum(self._file_meta.get(f, {}).get("size", 0) for f in files)

    def check_disk_space(self, needed_bytes: int, margin: float = 1.05) -> None:
        """Error out BEFORE downloading if the target disk can't hold it."""
        if needed_bytes <= 0:
            return   # hub gave no sizes — nothing to check against
        free = shutil.disk_usage(self.local_dir).free
        needed = int(needed_bytes * margin)
        if free < needed:
            raise RuntimeError(
                f"{self.repo_id} needs ~{needed / 1e9:.0f} GB "
                f"(incl. {int((margin - 1) * 100)}% margin); "
                f"{self.local_dir} has {free / 1e9:.0f} GB free. "
                f"Free space or choose a different output path.")

    # ------------------------------------------------------------------ #
    # State checkpointing
    # ------------------------------------------------------------------ #
    def _load_state(self, total_shards: int) -> dict:
        state = wisp_cache.load_json(_state_name(self.repo_id)) or {}
        if "completed_shards" not in state:
            # migrate the v1 {"done": [...]} format
            state = {
                "model_id": self.repo_id,
                "total_shards": total_shards,
                "completed_shards": state.get("done", []),
                "bytes_downloaded": 0,
                "started_at": state.get("started_at", _now_iso()),
                "last_updated": _now_iso(),
            }
        state["model_id"] = self.repo_id
        state["total_shards"] = total_shards
        return state

    def _save_state(self, state: dict) -> None:
        state["last_updated"] = _now_iso()
        wisp_cache.save_json(_state_name(self.repo_id), state)

    # ------------------------------------------------------------------ #
    # Download
    # ------------------------------------------------------------------ #
    def download_iter(self) -> Iterator[Path]:
        """
        Download everything, yielding each SHARD's local path the moment
        it is complete + verified — the converter consumes this so
        partitioning overlaps the remaining download.
        """
        shards, support = self.fetch_file_list()
        self.check_disk_space(
            self.total_download_bytes(shards + support))

        state = self._load_state(len(shards))
        done = set(state["completed_shards"])
        done = {s for s in done if (self.local_dir / s).exists()}

        # Support files first (tiny; tokenizer needed early)
        for f in support:
            if not (self.local_dir / f).exists():
                self._download_one(f)

        todo = [s for s in shards if s not in done]
        if done and todo:
            print(f"  [WISP] Resuming download: {len(done)}/{len(shards)} "
                  f"shards complete, continuing from {todo[0]}...")
        elif not todo:
            print(f"  [WISP] All {len(shards)} shards already downloaded.")

        # Yield already-complete shards first so conversion can resume too
        for s in shards:
            if s in done:
                yield self.local_dir / s

        for filename in todo:
            path = self._download_one(filename)
            self._verify_shard(filename, path)
            done.add(filename)
            state["completed_shards"] = sorted(done)
            state["bytes_downloaded"] = sum(
                (self.local_dir / s).stat().st_size
                for s in done if (self.local_dir / s).exists())
            self._save_state(state)
            log.info("shard complete %s (%d/%d)", filename,
                     len(done), len(shards))
            yield path

    def download_all(self) -> Path:
        """Download every file; returns the local directory."""
        n = 0
        total_start = time.perf_counter()
        for _ in tqdm(self.download_iter(), unit="shard", desc="  shards"):
            n += 1
        elapsed = time.perf_counter() - total_start
        log.info("download finished: %d shards in %.0fs", n, elapsed)
        return self.local_dir

    # Back-compat alias used by drafter auto-fetch
    def download(self, **_ignored) -> Path:
        return self.download_all()

    # ------------------------------------------------------------------ #
    def _download_one(self, filename: str) -> Path:
        last_err: Exception | None = None
        for attempt in range(MAX_RETRIES):
            try:
                path = hf_hub_download(
                    repo_id=self.repo_id,
                    filename=filename,
                    revision=self.revision,
                    local_dir=str(self.local_dir),
                    token=self.token,
                )
                return Path(path)
            except KeyboardInterrupt:
                raise
            except Exception as e:  # network hiccups, 5xx, timeouts
                last_err = e
                delay = RETRY_BASE_DELAY * (2 ** attempt)
                print(f"  [WISP] {filename}: attempt {attempt + 1}/"
                      f"{MAX_RETRIES} failed ({e.__class__.__name__}: {e}). "
                      f"Retrying in {delay:.0f}s...")
                time.sleep(delay)
        raise RuntimeError(
            f"Failed to download {filename} from {self.repo_id} after "
            f"{MAX_RETRIES} attempts: {last_err}")

    def _verify_shard(self, filename: str, path: Path) -> None:
        """SHA256 against the hub's LFS record; corrupt -> delete + error
        (a re-run redownloads just that shard)."""
        if not self.verify_hashes:
            return
        expected = self._file_meta.get(filename, {}).get("sha256")
        if not expected:
            return   # non-LFS or hub omitted the hash
        actual = _sha256_of(path)
        if actual != expected:
            path.unlink(missing_ok=True)
            raise RuntimeError(
                f"SHA256 mismatch on {filename}: expected {expected[:16]}…, "
                f"got {actual[:16]}…. Shard deleted — re-run to redownload.")
        log.debug("sha256 ok: %s", filename)


def download_model(repo_id: str, local_dir: str | Path,
                   token: str | None = None) -> Path:
    """Convenience wrapper: full resumable download of a model repo."""
    return ShardDownloader(repo_id, local_dir, token=token).download_all()
