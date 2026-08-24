# WISP — ROCm setup for AMD Radeon AI PRO R9700 (Windows).
#
# SCOPE: detection only. WISP's compute kernels are CUDA; this makes
# `wisp doctor` recognise and size your R9700, not run inference on it.
#
# AMD does not ship a silent/unattended Windows ROCm installer, so this
# script cannot fully automate the install — it checks what you have and
# takes you to the right download.
$ErrorActionPreference = "Stop"

Write-Host "==============================================="
Write-Host "  WISP - ROCm setup for AMD Radeon AI PRO R9700"
Write-Host "==============================================="
Write-Host ""
Write-Host "  NOTE: detection only. WISP inference still requires CUDA." -ForegroundColor Yellow
Write-Host ""

$rocmSmi = Get-Command rocm-smi -ErrorAction SilentlyContinue
if ($rocmSmi) {
    Write-Host "  [ok] rocm-smi found: $($rocmSmi.Source)"
    & rocm-smi --showproductname
    Write-Host ""
    Write-Host "  ROCm is already installed. Run: wisp doctor"
    exit 0
}

Write-Host "  [x] rocm-smi not found — ROCm is not installed."
Write-Host ""
Write-Host "  Windows ROCm requires 6.4+ (7.0+ for native gfx1201)."
Write-Host "  AMD provides no unattended installer, so please:"
Write-Host "    1. Download the ROCm/HIP SDK for Windows"
Write-Host "    2. Run the installer and reboot"
Write-Host "    3. Re-run this script to verify, then: wisp doctor"
Write-Host ""

$url = "https://www.amd.com/en/developer/resources/rocm-hub/hip-sdk.html"
Write-Host "  Opening $url"
Start-Process $url
