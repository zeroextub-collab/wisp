/*
 * speculative.cu — GPU-side pieces of speculative verification.
 *
 * The rejection-sampling CONTROL FLOW lives in Python (verifier.py) where
 * it stays exactly faithful to Leviathan et al.; these kernels remove the
 * bandwidth-heavy parts from the host: temperature softmax over a 150k
 * vocabulary and the per-draft acceptance-probability gather.
 */

#include <cuda_runtime.h>
#include <cuda_fp16.h>
#include <stdint.h>

#include "../core/wisp_engine.h"

#define SPEC_THREADS 256

/* Single-block temperature softmax: probs = softmax(logits / T).
 * A 151k vocab is ~600 iterations per phase for one block — microseconds,
 * and single-block keeps it a one-launch primitive with no scratch. */
__global__ void softmax_temp_kernel(const float* __restrict__ logits,
                                    float* __restrict__ probs,
                                    int n, float inv_temp) {
    __shared__ float red[SPEC_THREADS / 32];
    __shared__ float s_max, s_sum;
    int lane = threadIdx.x & 31;
    int warp = threadIdx.x >> 5;

    float m = -1e30f;
    for (int i = threadIdx.x; i < n; i += blockDim.x)
        m = fmaxf(m, logits[i] * inv_temp);
    #pragma unroll
    for (int off = 16; off > 0; off >>= 1)
        m = fmaxf(m, __shfl_down_sync(0xffffffff, m, off));
    if (lane == 0) red[warp] = m;
    __syncthreads();
    if (warp == 0) {
        m = (lane < SPEC_THREADS / 32) ? red[lane] : -1e30f;
        #pragma unroll
        for (int off = 16; off > 0; off >>= 1)
            m = fmaxf(m, __shfl_down_sync(0xffffffff, m, off));
        if (lane == 0) s_max = m;
    }
    __syncthreads();

    float sum = 0.0f;
    for (int i = threadIdx.x; i < n; i += blockDim.x) {
        float e = __expf(logits[i] * inv_temp - s_max);
        probs[i] = e;
        sum += e;
    }
    #pragma unroll
    for (int off = 16; off > 0; off >>= 1)
        sum += __shfl_down_sync(0xffffffff, sum, off);
    if (lane == 0) red[warp] = sum;
    __syncthreads();
    if (warp == 0) {
        sum = (lane < SPEC_THREADS / 32) ? red[lane] : 0.0f;
        #pragma unroll
        for (int off = 16; off > 0; off >>= 1)
            sum += __shfl_down_sync(0xffffffff, sum, off);
        if (lane == 0) s_sum = sum;
    }
    __syncthreads();

    float inv = 1.0f / (s_sum > 0.0f ? s_sum : 1.0f);
    for (int i = threadIdx.x; i < n; i += blockDim.x)
        probs[i] *= inv;
}

extern "C" void wisp_gpu_softmax_temp(const float* logits, float* probs,
                                      int n, float temperature,
                                      cudaStream_t s) {
    if (n <= 0) return;
    float inv_temp = 1.0f / (temperature > 1e-6f ? temperature : 1e-6f);
    softmax_temp_kernel<<<1, SPEC_THREADS, 0, s>>>(logits, probs, n,
                                                   inv_temp);
}

/* Parallel acceptance gather across all K draft positions:
 *   accept_probs[k] = min(1, p_main[k][tok_k] / p_draft[k][tok_k])
 * main_probs / draft_probs: [K, vocab]; draft_tokens: [K]. */
__global__ void verify_batch_kernel(const float* __restrict__ main_probs,
                                    const float* __restrict__ draft_probs,
                                    const int* __restrict__ draft_tokens,
                                    int K, int vocab,
                                    float* __restrict__ accept_probs) {
    int k = blockIdx.x * blockDim.x + threadIdx.x;
    if (k >= K) return;
    int tok = draft_tokens[k];
    if (tok < 0 || tok >= vocab) {
        accept_probs[k] = 0.0f;
        return;
    }
    float pm = main_probs[(size_t)k * vocab + tok];
    float pd = draft_probs[(size_t)k * vocab + tok];
    float a = pm / (pd + 1e-10f);
    accept_probs[k] = a < 1.0f ? a : 1.0f;
}

extern "C" void wisp_gpu_verify_batch(const float* main_probs,
                                      const float* draft_probs,
                                      const int* draft_tokens, int K,
                                      int vocab, float* accept_probs,
                                      cudaStream_t s) {
    if (K <= 0 || vocab <= 0) return;
    int blocks = (K + 31) / 32;
    verify_batch_kernel<<<blocks, 32, 0, s>>>(
        main_probs, draft_probs, draft_tokens, K, vocab, accept_probs);
}

/* Sequential acceptance scan, fully on-GPU (no CPU round trip):
 * given per-position acceptance probabilities and pre-drawn uniforms,
 * emit n_accepted and the first rejected position (-1 = all accepted).
 * Leviathan rejection is inherently sequential in K, but K <= 8 — a
 * single thread walking K floats costs nanoseconds and keeps the whole
 * draft->verify->accept chain on-device. */
__global__ void verify_scan_kernel(const float* __restrict__ accept_probs,
                                   const float* __restrict__ rand_u,
                                   int K,
                                   int* __restrict__ n_accepted,
                                   int* __restrict__ first_reject) {
    if (threadIdx.x != 0 || blockIdx.x != 0) return;
    int accepted = 0;
    int reject = -1;
    for (int k = 0; k < K; k++) {
        if (rand_u[k] < accept_probs[k]) {
            accepted++;
        } else {
            reject = k;
            break;
        }
    }
    *n_accepted = accepted;
    *first_reject = reject;
}

extern "C" void wisp_gpu_verify_scan(const float* accept_probs,
                                     const float* rand_u, int K,
                                     int* n_accepted, int* first_reject,
                                     cudaStream_t s) {
    if (K <= 0) return;
    verify_scan_kernel<<<1, 1, 0, s>>>(accept_probs, rand_u, K,
                                       n_accepted, first_reject);
}
