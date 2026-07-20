/*
 * router.cu — expert routing: router GEMV -> softmax -> top-k -> renorm.
 *
 * The selection result must land on the HOST (the host drives SSD/RAM/VRAM
 * expert fetches), so the launcher stages [idx | weights] through a tiny
 * persistent device buffer and copies it back on the compute stream. The
 * caller synchronizes the stream before reading — one sync per layer,
 * which the fetch pipeline needs anyway.
 *
 * The returned weights are the renormalized top-K gate values; the engine
 * computes  expert_output = sum_k gate_weight_k * expert_k(x)  with them.
 *
 * TODO: Implement Quantile Balancing routing (Stable LatentMoE) for
 * Kimi K3 once the technical report publishes July 27, 2026. It replaces
 * the standard top-K softmax below for that family; until then K3 routes
 * through this kernel as a placeholder.
 */

#include <cuda_runtime.h>
#include <cuda_fp16.h>
#include <stdint.h>

#include "../core/wisp_engine.h"

#define ROUTER_THREADS 256
#define ROUTER_MAX_TOPK 64

/* logits[e] = dot(router_row_e, x) + bias[e]; one block per expert row. */
__global__ void router_gemv_kernel(const __half* __restrict__ W,
                                   const __half* __restrict__ bias,
                                   const float* __restrict__ x,
                                   float* __restrict__ logits,
                                   int n_experts, int hidden) {
    int e = blockIdx.x;
    if (e >= n_experts) return;
    const __half* row = W + (size_t)e * hidden;

    __shared__ float warp_sums[ROUTER_THREADS / 32];
    float acc = 0.0f;
    for (int c = threadIdx.x; c < hidden; c += blockDim.x)
        acc += __half2float(row[c]) * x[c];

    int lane = threadIdx.x & 31;
    int warp = threadIdx.x >> 5;
    #pragma unroll
    for (int off = 16; off > 0; off >>= 1)
        acc += __shfl_down_sync(0xffffffff, acc, off);
    if (lane == 0) warp_sums[warp] = acc;
    __syncthreads();
    if (warp == 0) {
        acc = (lane < ROUTER_THREADS / 32) ? warp_sums[lane] : 0.0f;
        #pragma unroll
        for (int off = 16; off > 0; off >>= 1)
            acc += __shfl_down_sync(0xffffffff, acc, off);
        if (lane == 0) {
            float b = bias ? __half2float(bias[e]) : 0.0f;
            logits[e] = acc + b;
        }
    }
}

/* Single block: softmax over n_experts, then serial top-k (k <= 8 in
 * practice — a k-pass argmax over a few hundred probabilities is faster
 * than any fancy selection at this size), then renormalize the winners.
 * Output layout in `staging`: k ints (as float bits? no — separate halves):
 * staging[0..k) = indices reinterpret as int, staging[k..2k) = weights. */
__global__ void router_topk_kernel(float* __restrict__ logits,
                                   int n_experts, int top_k,
                                   int* __restrict__ out_idx,
                                   float* __restrict__ out_w) {
    __shared__ float red[ROUTER_THREADS / 32];
    __shared__ float s_max, s_sum;
    int lane = threadIdx.x & 31;
    int warp = threadIdx.x >> 5;

    /* max */
    float m = -1e30f;
    for (int e = threadIdx.x; e < n_experts; e += blockDim.x)
        m = fmaxf(m, logits[e]);
    #pragma unroll
    for (int off = 16; off > 0; off >>= 1)
        m = fmaxf(m, __shfl_down_sync(0xffffffff, m, off));
    if (lane == 0) red[warp] = m;
    __syncthreads();
    if (warp == 0) {
        m = (lane < ROUTER_THREADS / 32) ? red[lane] : -1e30f;
        #pragma unroll
        for (int off = 16; off > 0; off >>= 1)
            m = fmaxf(m, __shfl_down_sync(0xffffffff, m, off));
        if (lane == 0) s_max = m;
    }
    __syncthreads();

    /* exp + sum */
    float sum = 0.0f;
    for (int e = threadIdx.x; e < n_experts; e += blockDim.x) {
        float v = __expf(logits[e] - s_max);
        logits[e] = v;
        sum += v;
    }
    #pragma unroll
    for (int off = 16; off > 0; off >>= 1)
        sum += __shfl_down_sync(0xffffffff, sum, off);
    if (lane == 0) red[warp] = sum;
    __syncthreads();
    if (warp == 0) {
        sum = (lane < ROUTER_THREADS / 32) ? red[lane] : 0.0f;
        #pragma unroll
        for (int off = 16; off > 0; off >>= 1)
            sum += __shfl_down_sync(0xffffffff, sum, off);
        if (lane == 0) s_sum = sum;
    }
    __syncthreads();

    if (threadIdx.x == 0) {
        float inv = 1.0f / (s_sum > 0.0f ? s_sum : 1.0f);
        float wsum = 0.0f;
        for (int k = 0; k < top_k; k++) {
            int best = -1;
            float bestv = -1.0f;
            for (int e = 0; e < n_experts; e++) {
                bool taken = false;
                for (int j = 0; j < k; j++)
                    if (out_idx[j] == e) { taken = true; break; }
                if (!taken && logits[e] > bestv) {
                    bestv = logits[e];
                    best = e;
                }
            }
            out_idx[k] = best;
            out_w[k] = bestv * inv;
            wsum += bestv * inv;
        }
        if (wsum > 0.0f)
            for (int k = 0; k < top_k; k++)
                out_w[k] /= wsum;              /* renormalize the winners */
    }
}

extern "C" void wisp_gpu_router_topk(const wisp_half* W,
                                     const wisp_half* bias,
                                     const float* x, float* logits_scratch,
                                     int n_experts, int hidden, int top_k,
                                     int* out_idx, float* out_w,
                                     cudaStream_t s) {
    if (n_experts <= 0 || top_k <= 0) return;
    if (top_k > ROUTER_MAX_TOPK) top_k = ROUTER_MAX_TOPK;

    /* Tiny persistent device staging for the selection result. The engine
     * runs one router per layer sequentially on a single compute stream,
     * so a process-wide buffer is race-free. */
    static int* d_idx = nullptr;
    static float* d_w = nullptr;
    if (!d_idx) {
        cudaMalloc(&d_idx, ROUTER_MAX_TOPK * sizeof(int));
        cudaMalloc(&d_w, ROUTER_MAX_TOPK * sizeof(float));
        if (!d_idx || !d_w) return;
    }

    router_gemv_kernel<<<n_experts, ROUTER_THREADS, 0, s>>>(
        (const __half*)W, (const __half*)bias, x, logits_scratch,
        n_experts, hidden);
    router_topk_kernel<<<1, ROUTER_THREADS, 0, s>>>(
        logits_scratch, n_experts, top_k, d_idx, d_w);

    cudaMemcpyAsync(out_idx, d_idx, (size_t)top_k * sizeof(int),
                    cudaMemcpyDeviceToHost, s);
    cudaMemcpyAsync(out_w, d_w, (size_t)top_k * sizeof(float),
                    cudaMemcpyDeviceToHost, s);
    /* Caller synchronizes the stream before reading out_idx/out_w. */
}
