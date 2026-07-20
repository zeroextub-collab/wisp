#!/usr/bin/env bash
# WISP one-command install — Linux (Ubuntu 20.04+).
# Detects CUDA; falls back to a CPU-only engine build when absent.
set -euo pipefail

echo "═══════════════════════════════════════════════"
echo "  WISP installer — stream what shouldn't run"
echo "═══════════════════════════════════════════════"

# --- Python ---------------------------------------------------------------
PY=python3
if ! command -v "$PY" >/dev/null 2>&1; then
    echo "  [x] python3 not found. Install Python 3.10+ first."
    exit 1
fi
PYVER=$("$PY" -c 'import sys; print(f"{sys.version_info[0]}.{sys.version_info[1]}")')
if ! "$PY" -c 'import sys; sys.exit(0 if sys.version_info >= (3, 10) else 1)'; then
    echo "  [x] Python $PYVER found — WISP needs 3.10+."
    exit 1
fi
echo "  [ok] Python $PYVER"

# --- CMake ----------------------------------------------------------------
if ! command -v cmake >/dev/null 2>&1; then
    echo "  [..] Installing cmake..."
    if command -v apt-get >/dev/null 2>&1; then
        sudo apt-get update -qq && sudo apt-get install -y -qq cmake build-essential
    else
        echo "  [x] cmake missing and apt-get unavailable. Install CMake 3.20+ manually."
        exit 1
    fi
fi
echo "  [ok] $(cmake --version | head -n1)"

# --- CUDA detection -------------------------------------------------------
if command -v nvcc >/dev/null 2>&1; then
    CUDA_VER=$(nvcc --version | grep -oP 'release \K[0-9]+\.[0-9]+' | head -n1)
    echo "  [ok] CUDA toolkit $CUDA_VER"
    if [ "$(printf '%s\n' "12.0" "$CUDA_VER" | sort -V | head -n1)" != "12.0" ]; then
        echo "  [!] CUDA $CUDA_VER < 12.0 — building CPU-only engine."
        export WISP_NO_CUDA=1
    fi
else
    echo "  [!] No CUDA toolkit found — building CPU-only engine."
    echo "      (Install CUDA 12.0+ and re-run for GPU acceleration.)"
    export WISP_NO_CUDA=1
fi

# --- Install --------------------------------------------------------------
SCRIPT_DIR=$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)
REPO_DIR=$(dirname "$SCRIPT_DIR")

echo "  [..] Installing PyTorch (cu128 — covers RTX 40/50 series)..."
if [ -z "${WISP_NO_CUDA:-}" ]; then
    "$PY" -m pip install torch --index-url https://download.pytorch.org/whl/cu128 \
        || "$PY" -m pip install torch
else
    "$PY" -m pip install torch
fi

echo "  [..] Installing Python dependencies..."
"$PY" -m pip install --upgrade pip >/dev/null
"$PY" -m pip install -r "$REPO_DIR/requirements.txt"

echo "  [..] Building WISP (this compiles the C engine)..."
"$PY" -m pip install -e "$REPO_DIR"

echo ""
echo "  [..] Verifying installation..."
wisp doctor || true

echo ""
echo "  [ok] WISP installed."
echo ""
echo "  Next steps:"
echo "    wisp profile                                # benchmark this machine"
echo "    wisp convert --model glm-5.2 --output ./models/"
echo "    wisp chat --model ./models/glm-5.2/"
