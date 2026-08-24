#!/usr/bin/env bash
# Install AMD ROCm for WISP's R9700 detection (Ubuntu).
#
# SCOPE: this makes `wisp doctor` see your Radeon AI PRO R9700 and size
# it correctly. It does NOT make inference run on it — WISP's compute
# kernels are CUDA, and the HIP port is separate work. Install this if
# you want WISP to report your hardware accurately, or to prepare for
# ROCm support landing.
set -euo pipefail

echo "═══════════════════════════════════════════════"
echo "  WISP — ROCm setup for AMD Radeon AI PRO R9700"
echo "═══════════════════════════════════════════════"
echo
echo "  NOTE: detection only. WISP inference still requires CUDA."
echo

if [ "$(uname -s)" != "Linux" ]; then
    echo "  [x] This script is for Linux. On Windows use install_rocm.ps1."
    exit 1
fi
if ! command -v lsb_release >/dev/null 2>&1; then
    sudo apt-get update -qq && sudo apt-get install -y -qq lsb-release
fi

CODENAME=$(lsb_release -cs)
VERSION=$(lsb_release -rs)
case "$VERSION" in
    20.04|22.04|24.04) echo "  [ok] Ubuntu $VERSION ($CODENAME)" ;;
    *) echo "  [!] Ubuntu $VERSION is not an officially supported ROCm"
       echo "      release (20.04 / 22.04 / 24.04). Continuing anyway." ;;
esac

echo "  [..] Adding the AMD ROCm repository..."
sudo mkdir -p --mode=0755 /etc/apt/keyrings
wget -qO- https://repo.radeon.com/rocm/rocm.gpg.key \
    | sudo gpg --dearmor -o /etc/apt/keyrings/rocm.gpg
echo "deb [arch=amd64 signed-by=/etc/apt/keyrings/rocm.gpg] \
https://repo.radeon.com/rocm/apt/latest $CODENAME main" \
    | sudo tee /etc/apt/sources.list.d/rocm.list > /dev/null
sudo apt-get update -qq

echo "  [..] Installing rocm-hip-sdk and rocm-opencl..."
sudo apt-get install -y rocm-hip-sdk rocm-opencl

# gfx1201 (R9700) is native on ROCm 7.0+. On earlier drivers the override
# below makes HIP fall back to a compatible target rather than refusing
# to enumerate the device at all.
if ! grep -q "HSA_OVERRIDE_GFX_VERSION" /etc/environment 2>/dev/null; then
    echo "  [..] Setting HSA_OVERRIDE_GFX_VERSION=11.0.0 for older drivers"
    echo 'HSA_OVERRIDE_GFX_VERSION=11.0.0' | sudo tee -a /etc/environment > /dev/null
fi

if ! groups "$USER" | grep -qE '\brender\b'; then
    echo "  [..] Adding $USER to the render/video groups (needs re-login)"
    sudo usermod -aG render,video "$USER"
fi

echo
echo "  [ok] ROCm installed. Log out and back in, then run:"
echo "         rocm-smi --showproductname"
echo "         wisp doctor"
