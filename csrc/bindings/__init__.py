# csrc/bindings is a C++ source directory, not a Python package.
# This file exists so tooling that walks csrc/ (linters, cmake glob
# checks) treats the directory consistently. The built extension is
# importable as `wisp._wisp_core`.
