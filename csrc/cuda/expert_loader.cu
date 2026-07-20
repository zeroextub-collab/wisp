/*
 * expert_loader.cu — int4 -> fp16 dequantization on the GPU.
 *
 * Dequantizing on-device avoids burning CPU cycles on 8.5 GB/token of
 * cold-path weight traffic: packed int4 blobs move over PCIe as-is
 * (half the bytes of fp8, a quarter of fp16) and expand only in VRAM.
 *
 * Bit format (must match wisp/converter/quantizer.py EXACTLY):
 *   two int4 values per byte: LOW nibble = even index, HIGH = odd
 *   groups of `group_size` consecutive flattened elements share one
 *   fp16 scale and one fp16 zero
 *   value = (nibble - 8) * scale + zero
 */

#include <cuda_runtime.h>
#include <cuda_fp16.h>
#include <stdint.h>

#include "../core/wisp_engine.h"

/* Dequantize int4 packed weights -> fp16 on GPU (avoids CPU overhead).
 * Two int4 values packed per byte: low nibble first, high nibble second. */
__global__ void dequant_int4_fp16_kernel(
    const uint8_t* __restrict__ packed,   /* Input: n_elements/2 bytes    */
    const __half*  __restrict__ scales,   /* Per-group scale factors      */
    const __half*  __restrict__ zeros,    /* Per-group zero points        */
    __half*        __restrict__ output,   /* Output: n_elements fp16      */
    int n_elements,
    int group_size
) {
    int idx = blockIdx.x * blockDim.x + threadIdx.x;
    if (idx >= n_elements) return;

    /* Unpack nibble */
    uint8_t byte_val = packed[idx >> 1];
    int nibble = (idx & 1) ? (byte_val >> 4) : (byte_val & 0x0F);

    /* Dequantize: val = (nibble - 8) * scale + zero */
    int g = idx / group_size;
    float scale = __half2float(scales[g]);
    float zero  = __half2float(zeros[g]);
    output[idx] = __float2half((float)(nibble - 8) * scale + zero);
}

/* Launch dequant for one expert matrix on the given CUDA stream */
extern "C" cudaError_t launch_dequant_expert(
    const uint8_t*   d_packed,
    const wisp_half* d_scales,
    const wisp_half* d_zeros,
    wisp_half*       d_output,
    int              n_elements,
    int              group_size,
    cudaStream_t     stream
) {
    if (n_elements <= 0 || group_size <= 0) return cudaErrorInvalidValue;
    const int THREADS = 256;
    int blocks = (n_elements + THREADS - 1) / THREADS;
    dequant_int4_fp16_kernel<<<blocks, THREADS, 0, stream>>>(
        d_packed, (const __half*)d_scales, (const __half*)d_zeros,
        (__half*)d_output, n_elements, group_size
    );
    return cudaGetLastError();
}

/* Async load: host pinned -> device, then dequant in place on stream.
 * Used by the double-buffer pipeline when staging predicted experts. */
extern "C" cudaError_t async_load_expert(
    const uint8_t*   h_packed,       /* Pinned host memory (int4 packed) */
    const wisp_half* h_scales,       /* Pinned host scales               */
    const wisp_half* h_zeros,        /* Pinned host zeros                */
    uint8_t*         d_packed_tmp,   /* Temp device buffer for packed    */
    wisp_half*       d_scales_tmp,   /* Temp device buffer for scales    */
    wisp_half*       d_zeros_tmp,    /* Temp device buffer for zeros     */
    wisp_half*       d_output,       /* Final fp16 expert weights        */
    int              n_elements,
    int              group_size,
    cudaStream_t     stream
) {
    if (n_elements <= 0 || group_size <= 0) return cudaErrorInvalidValue;
    int n_groups = (n_elements + group_size - 1) / group_size;
    size_t packed_bytes = ((size_t)n_elements + 1) / 2;
    size_t scale_bytes  = (size_t)n_groups * sizeof(__half);

    cudaError_t e;
    e = cudaMemcpyAsync(d_packed_tmp, h_packed, packed_bytes,
                        cudaMemcpyHostToDevice, stream);
    if (e != cudaSuccess) return e;
    e = cudaMemcpyAsync(d_scales_tmp, h_scales, scale_bytes,
                        cudaMemcpyHostToDevice, stream);
    if (e != cudaSuccess) return e;
    e = cudaMemcpyAsync(d_zeros_tmp, h_zeros, scale_bytes,
                        cudaMemcpyHostToDevice, stream);
    if (e != cudaSuccess) return e;

    return launch_dequant_expert(d_packed_tmp, d_scales_tmp, d_zeros_tmp,
                                 d_output, n_elements, group_size, stream);
}
