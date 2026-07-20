/*
 * matmul.cu — fp16-weight GEMV (the decode workhorse) plus the small
 * elementwise kernels the forward pass composes: RMSNorm, residual add,
 * SwiGLU, weighted accumulation, embedding lookup.
 *
 * Decode-time inference is GEMV-bound: y = W @ x with W fp16 [rows, cols]
 * and x fp32. One block per output row, 256 threads striding the columns,
 * warp + shared reduction. Weights are read as __half2 pairs where
 * alignment allows for full memory throughput.
 */

#include <cuda_runtime.h>
#include <cuda_fp16.h>
#include <stdint.h>

#include "../core/wisp_engine.h"

#define GEMV_THREADS 256

/* --------------------------------------------------------------------- */
__device__ static float block_reduce_sum(float v) {
    __shared__ float warp_sums[GEMV_THREADS / 32];
    int lane = threadIdx.x & 31;
    int warp = threadIdx.x >> 5;

    #pragma unroll
    for (int off = 16; off > 0; off >>= 1)
        v += __shfl_down_sync(0xffffffff, v, off);

    if (lane == 0) warp_sums[warp] = v;
    __syncthreads();

    v = (threadIdx.x < blockDim.x / 32) ? warp_sums[lane] : 0.0f;
    if (warp == 0) {
        #pragma unroll
        for (int off = 16; off > 0; off >>= 1)
            v += __shfl_down_sync(0xffffffff, v, off);
    }
    return v;   /* valid in thread 0 */
}

/* --------------------------------------------------------------------- */
__global__ void gemv_f16_kernel(const __half* __restrict__ W,
                                const float* __restrict__ x,
                                float* __restrict__ y,
                                int rows, int cols) {
    int r = blockIdx.x;
    if (r >= rows) return;
    const __half* row = W + (size_t)r * cols;

    float acc = 0.0f;
    for (int c = threadIdx.x; c < cols; c += blockDim.x)
        acc += __half2float(row[c]) * x[c];

    acc = block_reduce_sum(acc);
    if (threadIdx.x == 0) y[r] = acc;
}

extern "C" void wisp_gpu_gemv_f16(const wisp_half* W, const float* x,
                                  float* y, int rows, int cols,
                                  cudaStream_t s) {
    if (rows <= 0 || cols <= 0) return;
    gemv_f16_kernel<<<rows, GEMV_THREADS, 0, s>>>(
        (const __half*)W, x, y, rows, cols);
}

/* y = W^T @ x : one block per output column, threads stride the rows. */
__global__ void gemv_t_f16_kernel(const __half* __restrict__ W,
                                  const float* __restrict__ x,
                                  float* __restrict__ y,
                                  int rows, int cols) {
    int c = blockIdx.x;
    if (c >= cols) return;

    float acc = 0.0f;
    for (int r = threadIdx.x; r < rows; r += blockDim.x)
        acc += __half2float(W[(size_t)r * cols + c]) * x[r];

    acc = block_reduce_sum(acc);
    if (threadIdx.x == 0) y[c] = acc;
}

extern "C" void wisp_gpu_gemv_t_f16(const wisp_half* W, const float* x,
                                    float* y, int rows, int cols,
                                    cudaStream_t s) {
    if (rows <= 0 || cols <= 0) return;
    gemv_t_f16_kernel<<<cols, GEMV_THREADS, 0, s>>>(
        (const __half*)W, x, y, rows, cols);
}

/* --------------------------------------------------------------------- */
__global__ void rmsnorm_kernel(const float* __restrict__ x,
                               const __half* __restrict__ w,
                               float* __restrict__ y,
                               int n, float eps) {
    /* Single block: reduce sum of squares, then scale. Safe in-place
     * (y == x) because every write happens after the __syncthreads()
     * that finalizes the reduction. */
    float ss = 0.0f;
    for (int i = threadIdx.x; i < n; i += blockDim.x)
        ss += x[i] * x[i];
    ss = block_reduce_sum(ss);

    __shared__ float scale;
    if (threadIdx.x == 0)
        scale = rsqrtf(ss / (float)n + eps);
    __syncthreads();

    for (int i = threadIdx.x; i < n; i += blockDim.x)
        y[i] = x[i] * scale * __half2float(w[i]);
}

extern "C" void wisp_gpu_rmsnorm(const float* x, const wisp_half* w,
                                 float* y, int n, float eps,
                                 cudaStream_t s) {
    if (n <= 0) return;
    rmsnorm_kernel<<<1, GEMV_THREADS, 0, s>>>(x, (const __half*)w, y, n, eps);
}

/* --------------------------------------------------------------------- */
__global__ void residual_add_kernel(float* x, const float* d, int n) {
    int i = blockIdx.x * blockDim.x + threadIdx.x;
    if (i < n) x[i] += d[i];
}

extern "C" void wisp_gpu_residual_add(float* x, const float* d, int n,
                                      cudaStream_t s) {
    if (n <= 0) return;
    int blocks = (n + 255) / 256;
    residual_add_kernel<<<blocks, 256, 0, s>>>(x, d, n);
}

__global__ void swiglu_kernel(const float* g, const float* u, float* o,
                              int n) {
    int i = blockIdx.x * blockDim.x + threadIdx.x;
    if (i < n) {
        float gv = g[i];
        float silu = gv / (1.0f + __expf(-gv));
        o[i] = silu * u[i];
    }
}

extern "C" void wisp_gpu_swiglu(const float* g, const float* u, float* o,
                                int n, cudaStream_t s) {
    if (n <= 0) return;
    int blocks = (n + 255) / 256;
    swiglu_kernel<<<blocks, 256, 0, s>>>(g, u, o, n);
}

__global__ void scale_accum_kernel(float* acc, const float* x, float w,
                                   int n) {
    int i = blockIdx.x * blockDim.x + threadIdx.x;
    if (i < n) acc[i] += w * x[i];
}

extern "C" void wisp_gpu_scale_accum(float* acc, const float* x, float w,
                                     int n, cudaStream_t s) {
    if (n <= 0) return;
    int blocks = (n + 255) / 256;
    scale_accum_kernel<<<blocks, 256, 0, s>>>(acc, x, w, n);
}

/* --------------------------------------------------------------------- *
 * Fused SwiGLU FFN front half: h[r] = silu(Wg[r]·x) * (Wu[r]·x).
 * Replaces three launches (gate gemv, up gemv, swiglu) with one — both
 * dot products share every x[] load, and the activation happens in
 * registers. The down projection stays a plain gemv.
 * --------------------------------------------------------------------- */
__global__ void swiglu_ffn_kernel(const __half* __restrict__ Wg,
                                  const __half* __restrict__ Wu,
                                  const float* __restrict__ x,
                                  float* __restrict__ h,
                                  int inter, int cols) {
    int r = blockIdx.x;
    if (r >= inter) return;
    const __half* wg = Wg + (size_t)r * cols;
    const __half* wu = Wu + (size_t)r * cols;

    float g = 0.0f, u = 0.0f;
    for (int c = threadIdx.x; c < cols; c += blockDim.x) {
        float xv = x[c];
        g += __half2float(wg[c]) * xv;
        u += __half2float(wu[c]) * xv;
    }

    float g_sum = block_reduce_sum(g);
    __shared__ float s_g;
    if (threadIdx.x == 0) s_g = g_sum;
    __syncthreads();                 /* warp_sums reuse barrier */
    float u_sum = block_reduce_sum(u);

    if (threadIdx.x == 0) {
        float gv = s_g;
        float silu = gv / (1.0f + __expf(-gv));
        h[r] = silu * u_sum;
    }
}

extern "C" void wisp_gpu_swiglu_ffn(const wisp_half* Wg, const wisp_half* Wu,
                                    const float* x, float* h,
                                    int inter, int cols, cudaStream_t s) {
    if (inter <= 0 || cols <= 0) return;
    swiglu_ffn_kernel<<<inter, GEMV_THREADS, 0, s>>>(
        (const __half*)Wg, (const __half*)Wu, x, h, inter, cols);
}

__global__ void embed_lookup_kernel(const __half* __restrict__ table,
                                    int token, float* __restrict__ x,
                                    int hidden) {
    int i = blockIdx.x * blockDim.x + threadIdx.x;
    if (i < hidden)
        x[i] = __half2float(table[(size_t)token * hidden + i]);
}

extern "C" void wisp_gpu_embed_lookup(const wisp_half* table, int token,
                                      float* x, int hidden,
                                      cudaStream_t s) {
    if (hidden <= 0) return;
    int blocks = (hidden + 255) / 256;
    embed_lookup_kernel<<<blocks, 256, 0, s>>>(
        (const __half*)table, token, x, hidden);
}
