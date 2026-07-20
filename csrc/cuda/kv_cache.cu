/*
 * kv_cache.cu — KV cache writes.
 *
 * The cache lives in device memory as fp16:
 *   K: [max_seq, kv_heads, k_dim] per layer
 *   V: [max_seq, kv_heads, v_dim] per layer (absent for MLA — the value
 *      read aliases the first kv_lora dims of the K entry)
 *
 * Reads happen inside attention.cu; the only write is the per-token
 * append below. "Clear" and "rollback" are pure length bookkeeping on the
 * host side (wisp_kv_cache_clear / wisp_kv_cache_rollback) — stale device
 * data past `len` is never read, so it never needs zeroing.
 */

#include <cuda_runtime.h>
#include <cuda_fp16.h>
#include <stdint.h>

#include "../core/wisp_engine.h"

__global__ void kv_append_kernel(__half* __restrict__ K,
                                 __half* __restrict__ V,
                                 const float* __restrict__ k,
                                 const float* __restrict__ v,
                                 int pos, int kv_heads,
                                 int k_dim, int v_dim) {
    int nk = kv_heads * k_dim;
    int nv = kv_heads * v_dim;
    int i = blockIdx.x * blockDim.x + threadIdx.x;

    if (i < nk)
        K[(size_t)pos * nk + i] = __float2half(k[i]);
    if (V != nullptr && v != nullptr && i < nv)
        V[(size_t)pos * nv + i] = __float2half(v[i]);
}

extern "C" void wisp_gpu_kv_append(wisp_half* K, wisp_half* V,
                                   const float* k, const float* v,
                                   int pos, int kv_heads, int k_dim,
                                   int v_dim, cudaStream_t s) {
    if (kv_heads <= 0 || k_dim <= 0) return;
    int n = kv_heads * (k_dim > v_dim ? k_dim : v_dim);
    int blocks = (n + 255) / 256;
    kv_append_kernel<<<blocks, 256, 0, s>>>(
        (__half*)K, (__half*)V, k, v, pos, kv_heads, k_dim, v_dim);
}
