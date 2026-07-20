# WISP top-level build.
#
#   cmake -B build -DCMAKE_BUILD_TYPE=Release
#   cmake --build build --config Release
#
# CPU-only (no CUDA toolkit required):
#   cmake -B build -DWISP_NO_CUDA=ON
#
# The extension lands in build/csrc/ as _wisp_core.*; `pip install -e .`
# drives this same build via setup.py and copies it into wisp/.

cmake_minimum_required(VERSION 3.20)

project(wisp
    VERSION 1.0.0
    DESCRIPTION "WISP — universal MoE inference over a 3-tier memory hierarchy"
    LANGUAGES C CXX
)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

add_subdirectory(csrc)
