# WISP one-command install — Windows 10/11 PowerShell.
# Detects CUDA; falls back to a CPU-only engine build when absent.
$ErrorActionPreference = "Stop"

Write-Host "==============================================="
Write-Host "  WISP installer - stream what shouldn't run"
Write-Host "==============================================="

# --- Python ---------------------------------------------------------------
$py = Get-Command python -ErrorAction SilentlyContinue
if (-not $py) {
    Write-Host "  [x] python not found. Install Python 3.10+ from python.org first."
    exit 1
}
$pyver = & python -c "import sys; print(f'{sys.version_info[0]}.{sys.version_info[1]}')"
$ok = & python -c "import sys; print(1 if sys.version_info >= (3, 10) else 0)"
if ($ok -ne "1") {
    Write-Host "  [x] Python $pyver found - WISP needs 3.10+."
    exit 1
}
Write-Host "  [ok] Python $pyver"

# --- CMake ----------------------------------------------------------------
$cmake = Get-Command cmake -ErrorAction SilentlyContinue
if (-not $cmake) {
    Write-Host "  [x] cmake not found. Install CMake 3.20+ (winget install Kitware.CMake)"
    Write-Host "      plus Visual Studio Build Tools, then re-run this script."
    exit 1
}
Write-Host "  [ok] $((cmake --version) | Select-Object -First 1)"

# --- CUDA detection -------------------------------------------------------
$nvcc = Get-Command nvcc -ErrorAction SilentlyContinue
if ($nvcc) {
    $cudaLine = (& nvcc --version) | Select-String "release"
    Write-Host "  [ok] CUDA toolkit: $cudaLine"
    if ($cudaLine -match "release (\d+)\.") {
        if ([int]$Matches[1] -lt 12) {
            Write-Host "  [!] CUDA < 12.0 - building CPU-only engine."
            $env:WISP_NO_CUDA = "1"
        }
    }
} else {
    Write-Host "  [!] No CUDA toolkit found - building CPU-only engine."
    Write-Host "      (Install CUDA 12.0+ and re-run for GPU acceleration.)"
    $env:WISP_NO_CUDA = "1"
}

# --- Install --------------------------------------------------------------
$repoDir = Split-Path -Parent $PSScriptRoot

if (-not $env:WISP_NO_CUDA) {
    Write-Host "  [..] Installing PyTorch (cu128 - covers RTX 40/50 series)..."
    & python -m pip install torch --index-url https://download.pytorch.org/whl/cu128
    if ($LASTEXITCODE -ne 0) { & python -m pip install torch }
} else {
    & python -m pip install torch
}

Write-Host "  [..] Installing Python dependencies..."
& python -m pip install --upgrade pip | Out-Null
& python -m pip install -r (Join-Path $repoDir "requirements.txt")
if ($LASTEXITCODE -ne 0) { exit 1 }

Write-Host "  [..] Building WISP (this compiles the C engine)..."
& python -m pip install -e $repoDir
if ($LASTEXITCODE -ne 0) { exit 1 }

Write-Host ""
Write-Host "  [..] Verifying installation..."
& wisp doctor

Write-Host ""
Write-Host "  [ok] WISP installed." -ForegroundColor Green
Write-Host ""
Write-Host "  Next steps:"
Write-Host "    wisp profile                                # benchmark this machine"
Write-Host "    wisp convert --model glm-5.2 --output ./models/"
Write-Host "    wisp chat --model ./models/glm-5.2/"
