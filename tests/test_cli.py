"""CLI tests via click's CliRunner — no model weights required."""

import pytest
from click.testing import CliRunner

from wisp.cli import main


@pytest.fixture()
def runner():
    return CliRunner()


def test_version(runner):
    result = runner.invoke(main, ["--version"])
    assert result.exit_code == 0
    assert "2.0.0" in result.output


def test_info_by_model_name_kimi_k3(runner):
    result = runner.invoke(main, ["info", "--model", "kimi-k3"])
    assert result.exit_code == 0, result.output
    # Confirmed architecture (arXiv:2607.24653) shown without hedging
    assert "104B active" in result.output
    assert "896" in result.output              # experts/layer
    assert "1,488" in result.output            # lookups/token = 16 x 93
    assert "56x expert-level" in result.output  # 896 / 16
    assert "KDA" in result.output and "GatedMLA" in result.output
    # The kernel exists now; what must still be stated plainly is that
    # the tensor NAMES are unverified, since a silent mismatch means
    # wrong output rather than a crash.
    assert "KDA kernel implemented" in result.output
    assert "unverified" in result.output


def test_info_by_model_name_qwen3(runner):
    result = runner.invoke(main, ["info", "--model", "qwen3-235b"])
    assert result.exit_code == 0, result.output
    assert "Qwen3-235B-A22B" in result.output
    assert "128" in result.output              # experts per layer
    assert "752" in result.output              # lookups/token = 94 x 8
    assert "GQA" in result.output


def test_info_by_model_name_glm(runner):
    result = runner.invoke(main, ["info", "--model", "glm-5.2"])
    assert result.exit_code == 0, result.output
    assert "Lookups/token: 488" in result.output
    assert "Tier Allocation" in result.output


def test_info_unknown_model_fails_cleanly(runner):
    result = runner.invoke(main, ["info", "--model", "gpt-oss-999"])
    assert result.exit_code != 0
    assert "Unknown model" in result.output


def test_doctor_runs(runner):
    result = runner.invoke(main, ["doctor"])
    assert result.exit_code == 0, result.output
    assert "WISP System Doctor" in result.output
    assert "Python:" in result.output
    assert "C engine:" in result.output
    assert "Model storage:" in result.output


def test_convert_kimi_k3_no_longer_date_blocked(runner, tmp_path):
    """The July-27 guard is gone: K3 weights and the technical report are
    both public. Conversion now fails only for ordinary reasons (no
    weights on disk / no network), never because of a calendar check."""
    result = runner.invoke(
        main, ["convert", "--model", "kimi-k3", "--output", str(tmp_path)])
    assert "July 27" not in result.output
    assert "unlocks" not in result.output
    # The unverified-tensor-name warning must still be shown, because
    # getting that wrong silently produces wrong output.
    assert "KDA projection names" in result.output


def test_run_requires_existing_model_dir(runner):
    result = runner.invoke(
        main, ["run", "--model", "./no/such/dir", "--prompt", "hi"])
    assert result.exit_code != 0


def test_mixtral_wisp_info(runner):
    result = runner.invoke(main, ["info", "--model", "mixtral-8x7b"])
    assert result.exit_code == 0, result.output
    assert "GQA" in result.output
    assert "64" in result.output               # lookups per token
    assert "Mixtral-8x7B-Instruct" in result.output
    # The all-in-silicon banner appears exactly when the tier math puts
    # zero experts on SSD — that depends on RAM free at run time, so
    # assert the display AGREES with the computed allocation instead of
    # hardcoding one machine state.
    from wisp.models.registry import get_adapter
    from wisp.system.auto_config import AutoConfig
    from wisp.system.profiler import SystemProfiler
    cfg = AutoConfig().calculate(SystemProfiler().get(),
                                 get_adapter("mixtral-8x7b"))
    if cfg.ssd_expert_count == 0:
        assert "silicon" in result.output.lower()
        assert "fastest possible mode" in result.output
    else:
        assert f"{cfg.ssd_expert_count:,}" in result.output


def test_package_metadata_exports():
    import wisp
    assert wisp.__version__ == "2.0.0"
    assert wisp.__author__ == "Saksham (Zero_planck)"


# --------------------------------------------------------------------------
# wisp verify / wisp upload — on a fabricated miniature model
# --------------------------------------------------------------------------

@pytest.fixture()
def mini_model(tmp_path):
    """A structurally valid 2-layer x 2-expert converted model."""
    import json
    import torch
    from safetensors.torch import save_file
    from wisp.converter.manifest import ModelManifest, expert_filename
    from wisp.converter.partitioner import write_expert_file
    from wisp.converter.quantizer import quantize_int4
    from wisp.models.registry import get_adapter

    root = tmp_path / "mini-glm"
    (root / "experts").mkdir(parents=True)
    (root / "dense").mkdir()
    (root / "tokenizer").mkdir()

    m = ModelManifest.build(get_adapter("glm-5.2"),
                            quant_dtype="int4", group_size=16)
    m.architecture["num_layers"] = 2
    m.architecture["num_experts_per_layer"] = 2
    m.performance["total_expert_count"] = 4
    m.save(root)

    torch.manual_seed(0)
    for layer in range(2):
        for expert in range(2):
            mats = {
                p: quantize_int4(torch.randn(8, 16), 16)
                for p in ("gate_proj", "up_proj", "down_proj")
            }
            write_expert_file(root / "experts"
                              / expert_filename(layer, expert),
                              layer, expert, mats)
    save_file({"embed_tokens": torch.zeros(4, 4, dtype=torch.float16)},
              str(root / "dense" / "model_dense.safetensors"))
    (root / "tokenizer" / "tokenizer.json").write_text(
        json.dumps({"version": "test"}))
    return root


def test_verify_passes_on_intact_model(runner, mini_model):
    result = runner.invoke(main, ["verify", "--model", str(mini_model)])
    assert result.exit_code == 0, result.output
    assert "4/4 OK" in result.output
    assert "PASSED" in result.output
    assert "Dense layers: OK" in result.output
    assert "Tokenizer: OK" in result.output


def test_verify_flags_missing_expert(runner, mini_model):
    (mini_model / "experts" / "L001_E00001.bin").unlink()
    result = runner.invoke(main, ["verify", "--model", str(mini_model)])
    assert result.exit_code != 0
    assert "MISSING: L001_E00001.bin" in result.output
    assert "FAILED" in result.output
    assert "wisp convert" in result.output      # repair instruction


def test_verify_flags_truncated_expert(runner, mini_model):
    victim = mini_model / "experts" / "L000_E00000.bin"
    victim.write_bytes(victim.read_bytes()[:200])   # > header, wrong size
    result = runner.invoke(main, ["verify", "--model", str(mini_model)])
    assert result.exit_code != 0
    assert "SIZE MISMATCH" in result.output


def test_upload_prepares_card_and_command(runner, mini_model):
    result = runner.invoke(main, [
        "upload", "--model", str(mini_model),
        "--repo", "tester/mini-glm-wisp"])
    assert result.exit_code == 0, result.output
    assert "huggingface-cli upload tester/mini-glm-wisp" in result.output
    card = (mini_model / "README.md").read_text(encoding="utf-8")
    assert "library_name: wisp" in card
    assert "GLM-5.2" in card


def test_upload_refuses_corrupt_model(runner, mini_model):
    (mini_model / "experts" / "L000_E00001.bin").unlink()
    result = runner.invoke(main, [
        "upload", "--model", str(mini_model),
        "--repo", "tester/broken"])
    assert result.exit_code != 0
    assert "corrupted" in result.output.lower()
    assert not (mini_model / "README.md").exists()   # no card written


def test_logging_setup_idempotent():
    import logging as stdlib_logging
    from wisp.logging import setup_logging, get_logger, LOG_PATH

    setup_logging(verbose=False)
    n_handlers = len(stdlib_logging.getLogger("wisp").handlers)
    setup_logging(verbose=True)    # re-invocation must not duplicate
    assert len(stdlib_logging.getLogger("wisp").handlers) == n_handlers
    assert stdlib_logging.getLogger("wisp").level == stdlib_logging.DEBUG

    log = get_logger("test")
    assert log.name == "wisp.test"
    log.debug("logging smoke test")
    assert LOG_PATH.parent.exists()
