"""
WISP package build.

    pip install -e .            # builds the C/CUDA extension via CMake
    WISP_NO_CUDA=1 pip install -e .   # CPU-only build (no CUDA toolkit)

If CMake or a compiler is missing the Python layer still installs;
the engine raises a clear build-instructions error on first use.
"""

import os
import subprocess
import sys
from pathlib import Path

from setuptools import Extension, find_packages, setup
from setuptools.command.build_ext import build_ext

ROOT = Path(__file__).parent.resolve()


class CMakeExtension(Extension):
    def __init__(self, name: str):
        super().__init__(name, sources=[])


class CMakeBuild(build_ext):
    def _prebuilt_engine(self) -> Path | None:
        """An already-compiled extension in the source tree (from a prior
        `pip install -e .` or a manual CMake build)."""
        for candidate in sorted((ROOT / "wisp").glob("_wisp_core*")):
            if candidate.suffix in (".pyd", ".so"):
                return candidate
        return None

    def build_extension(self, ext: CMakeExtension) -> None:
        import shutil

        out_dir = Path(self.get_ext_fullpath(ext.name)).parent.resolve()
        out_dir.mkdir(parents=True, exist_ok=True)

        # Reuse a prebuilt engine unless a rebuild is explicitly requested.
        # This keeps a GPU-built engine from being silently replaced by a
        # weaker build (e.g. a CPU-only fallback in an env without the
        # CUDA/MSVC integration on PATH). Set WISP_REBUILD=1 to force.
        prebuilt = self._prebuilt_engine()
        if prebuilt and not os.environ.get("WISP_REBUILD"):
            print(f"  [WISP] Reusing prebuilt C engine: {prebuilt.name} "
                  f"(set WISP_REBUILD=1 to recompile)")
            shutil.copy2(prebuilt, out_dir / prebuilt.name)
            return

        build_dir = Path(self.build_temp) / "wisp_cmake"
        build_dir.mkdir(parents=True, exist_ok=True)

        cfg = "Debug" if self.debug else "Release"
        cmake_args = [
            f"-DCMAKE_BUILD_TYPE={cfg}",
            f"-DPython3_EXECUTABLE={sys.executable}",
            f"-DCMAKE_LIBRARY_OUTPUT_DIRECTORY={out_dir}",
            f"-DCMAKE_LIBRARY_OUTPUT_DIRECTORY_{cfg.upper()}={out_dir}",
        ]
        if os.environ.get("WISP_NO_CUDA"):
            cmake_args.append("-DWISP_NO_CUDA=ON")
        if os.environ.get("WISP_HAS_NCCL"):
            cmake_args.append("-DWISP_HAS_NCCL=ON")

        try:
            subprocess.run(["cmake", str(ROOT)] + cmake_args,
                           cwd=build_dir, check=True)
            subprocess.run(
                ["cmake", "--build", ".", "--config", cfg, "--parallel"],
                cwd=build_dir, check=True)
        except (subprocess.CalledProcessError, FileNotFoundError) as e:
            if prebuilt:
                print(f"  [WISP] CMake build failed ({e}); falling back to "
                      f"the prebuilt engine {prebuilt.name}.")
                shutil.copy2(prebuilt, out_dir / prebuilt.name)
                return
            raise RuntimeError(
                "WISP C engine build failed and no prebuilt engine was "
                "found.\n"
                f"Reason: {e}\n"
                "Fix one of:\n"
                "  1. Install CMake 3.20+ and a C++ toolchain "
                "(MSVC C++ workload on Windows, gcc/clang on Linux)\n"
                "  2. Install CUDA 12.0+ for GPU builds — or set "
                "WISP_NO_CUDA=1 for a CPU-only engine\n"
                "  3. On Windows, run from an 'x64 Native Tools' prompt "
                "so cl.exe is on PATH\n"
                "then re-run: pip install -e ."
            ) from e

        # Multi-config generators (Visual Studio) drop the artifact in a
        # per-config subdir CMake sometimes appends — normalize.
        if not any(out_dir.glob("_wisp_core*")):
            for found in build_dir.rglob("_wisp_core*"):
                if found.suffix in (".pyd", ".so"):
                    shutil.copy2(found, out_dir / found.name)
                    break


with open(ROOT / "README.md", encoding="utf-8") as f:
    long_description = f.read()

with open(ROOT / "requirements.txt", encoding="utf-8") as f:
    requirements = [
        line.strip() for line in f
        if line.strip() and not line.startswith("#")
    ]

setup(
    name="wisp-engine",
    version="1.0.0",
    description="Stream what shouldn't run. Universal MoE inference engine.",
    long_description=long_description,
    long_description_content_type="text/markdown",
    author="Saksham (Zero_planck)",
    url="https://github.com/zeroextub-collab/wisp",
    license="MIT",
    python_requires=">=3.10",
    packages=find_packages(include=["wisp", "wisp.*"]),
    package_data={"wisp": ["*.pyd", "*.so"]},
    ext_modules=[CMakeExtension("wisp._wisp_core")],
    cmdclass={"build_ext": CMakeBuild},
    install_requires=requirements,
    extras_require={
        "dev": ["pytest>=7.0"],
        "server": ["fastapi>=0.111.0", "uvicorn>=0.30.0"],
        # The GUI hosts the server in-process, so it pulls the server
        # extra in with it rather than failing at Start Server time.
        "gui": ["PySide6>=6.7.0", "fastapi>=0.111.0", "uvicorn>=0.30.0"],
        "all": ["pytest>=7.0", "fastapi>=0.111.0", "uvicorn>=0.30.0",
                "PySide6>=6.7.0"],
    },
    entry_points={
        "console_scripts": [
            "wisp = wisp.cli:main",
        ],
        "gui_scripts": [
            "wisp-gui = wisp.gui.app:main",
        ],
    },
    classifiers=[
        "Development Status :: 4 - Beta",
        "Intended Audience :: Developers",
        "License :: OSI Approved :: MIT License",
        "Programming Language :: Python :: 3.10",
        "Programming Language :: Python :: 3.11",
        "Programming Language :: Python :: 3.12",
        "Programming Language :: C",
        "Programming Language :: C++",
        "Environment :: GPU :: NVIDIA CUDA :: 12",
        "Operating System :: Microsoft :: Windows",
        "Operating System :: POSIX :: Linux",
        "Topic :: Scientific/Engineering :: Artificial Intelligence",
        "Topic :: Software Development :: Libraries :: Python Modules",
    ],
)
