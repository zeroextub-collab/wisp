# csrc/CMakeLists.txt — builds the wisp._wisp_core extension.
#
# GPU build (default when a CUDA toolkit is found):
#   core C + CUDA kernels + bindings, OpenMP enabled.
# CPU-only build:
#   -DWISP_NO_CUDA=ON  -> same core C sources compile against the
#   host-memory shim in wisp_engine.c; no .cu files, no CUDA dependency.

cmake_minimum_required(VERSION 3.20)

option(WISP_NO_CUDA "Build without CUDA (CPU-only engine)" OFF)
option(WISP_HAS_NCCL "Link NCCL for 3+ GPU pipeline mode" OFF)

# --------------------------------------------------------------------------
# Dependencies
# --------------------------------------------------------------------------
find_package(Python3 COMPONENTS Interpreter Development.Module REQUIRED)

# pybind11: prefer the pip-installed package's cmake dir
execute_process(
    COMMAND "${Python3_EXECUTABLE}" -m pybind11 --cmakedir
    OUTPUT_VARIABLE PYBIND11_CMAKE_DIR
    OUTPUT_STRIP_TRAILING_WHITESPACE
    RESULT_VARIABLE PYBIND11_LOOKUP_RESULT
)
if(PYBIND11_LOOKUP_RESULT EQUAL 0)
    list(APPEND CMAKE_PREFIX_PATH "${PYBIND11_CMAKE_DIR}")
endif()
find_package(pybind11 CONFIG REQUIRED)

find_package(OpenMP)

if(NOT WISP_NO_CUDA)
    # Target every consumer generation from Turing through Blackwell.
    # sm_120 = RTX 5070/5080/5090 (Blackwell) — supported natively by
    # CUDA 12.8+ / 13.x toolkits. Must be set BEFORE enable_language(CUDA).
    set(CMAKE_CUDA_ARCHITECTURES 75 80 86 89 90 120)

    include(CheckLanguage)
    check_language(CUDA)
    if(CMAKE_CUDA_COMPILER)
        enable_language(CUDA)
        # Minimum 12.0; newer toolkits (12.8, 13.3, ...) satisfy this —
        # find_package version args are minimums, never exact pins.
        find_package(CUDAToolkit 12.0 REQUIRED)
    else()
        message(STATUS "No CUDA compiler found — falling back to CPU-only "
                       "build (WISP_NO_CUDA=ON)")
        set(WISP_NO_CUDA ON)
    endif()
endif()

# --------------------------------------------------------------------------
# Sources
# --------------------------------------------------------------------------
set(WISP_CORE_SOURCES
    core/wisp_engine.c
    core/lru_cache.c
    core/double_buffer.c
    core/mem_pool.c
)

set(WISP_CUDA_SOURCES
    cuda/expert_loader.cu
    cuda/attention.cu
    cuda/router.cu
    cuda/matmul.cu
    cuda/kv_cache.cu
    cuda/speculative.cu
    cuda/multi_gpu.cu
)

if(WISP_NO_CUDA)
    pybind11_add_module(_wisp_core
        bindings/wisp_bindings.cpp
        ${WISP_CORE_SOURCES}
    )
    target_compile_definitions(_wisp_core PRIVATE WISP_NO_CUDA)
else()
    pybind11_add_module(_wisp_core
        bindings/wisp_bindings.cpp
        ${WISP_CORE_SOURCES}
        ${WISP_CUDA_SOURCES}
    )
    target_link_libraries(_wisp_core PRIVATE CUDA::cudart)
    set_target_properties(_wisp_core PROPERTIES
        CUDA_SEPARABLE_COMPILATION ON
    )
    # NCCL (3+ GPU pipeline collectives). Auto-detected; CMake ships no
    # FindNCCL module, so probe the library + header directly. The 2-GPU
    # strategies use cudaMemcpyPeerAsync and never need NCCL.
    find_library(NCCL_LIBRARY nccl
                 HINTS $ENV{NCCL_ROOT}/lib $ENV{NCCL_HOME}/lib)
    find_path(NCCL_INCLUDE_DIR nccl.h
              HINTS $ENV{NCCL_ROOT}/include $ENV{NCCL_HOME}/include)
    if(WISP_HAS_NCCL OR (NCCL_LIBRARY AND NCCL_INCLUDE_DIR))
        if(NCCL_LIBRARY AND NCCL_INCLUDE_DIR)
            message(STATUS "NCCL found: ${NCCL_LIBRARY}")
            target_include_directories(_wisp_core PRIVATE ${NCCL_INCLUDE_DIR})
            target_link_libraries(_wisp_core PRIVATE ${NCCL_LIBRARY})
        else()
            target_link_libraries(_wisp_core PRIVATE nccl)
        endif()
        target_compile_definitions(_wisp_core PRIVATE
            WISP_HAS_NCCL WISP_USE_NCCL)
    else()
        message(STATUS "NCCL not found — 3+ GPU pipeline disabled "
                       "(2-GPU peer copies still available)")
    endif()
endif()

target_include_directories(_wisp_core PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

if(OpenMP_C_FOUND)
    target_link_libraries(_wisp_core PRIVATE OpenMP::OpenMP_C)
endif()
if(OpenMP_CXX_FOUND)
    target_link_libraries(_wisp_core PRIVATE OpenMP::OpenMP_CXX)
endif()

# --------------------------------------------------------------------------
# Compiler flags — MSVC and gcc/clang both supported
# --------------------------------------------------------------------------
if(MSVC)
    target_compile_options(_wisp_core PRIVATE
        $<$<COMPILE_LANGUAGE:C>:/O2 /W3>
        $<$<COMPILE_LANGUAGE:CXX>:/O2 /W3 /EHsc>
    )
    target_compile_definitions(_wisp_core PRIVATE _CRT_SECURE_NO_WARNINGS)
else()
    target_compile_options(_wisp_core PRIVATE
        $<$<COMPILE_LANGUAGE:C>:-O3 -Wall -Wextra>
        $<$<COMPILE_LANGUAGE:CXX>:-O3 -Wall -Wextra>
    )
endif()

# Threads: pthreads on POSIX (Windows uses the Win32 API directly)
if(NOT WIN32)
    find_package(Threads REQUIRED)
    target_link_libraries(_wisp_core PRIVATE Threads::Threads)
endif()

# Install straight into the wisp package directory
install(TARGETS _wisp_core LIBRARY DESTINATION wisp)
