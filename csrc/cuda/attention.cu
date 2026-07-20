/*
 * attention.cu — decode-step attention over the fp16 KV cache.
 *
 * One generic three-phase implementation serves both attention families:
 *
 *   GQA : Q [n_heads, head_dim] vs K/V [seq, n_kv_heads, head_dim];
 *         head h reads kv-head h / (n_heads / n_kv_heads).
 *
 *   MLA (absorbed form, true compressed cache):
 *         cache entry = [c_kv (kv_lora) | k_rope (qk_rope)] with kv_heads=1.
 *         The query is pre-absorbed (q_eff = W_UK^T q_nope ++ q_rope), the
 *         "value" read is the first kv_lora dims of the SAME cache entry
 *         (V pointer == K pointer), and the per-head context vector is
 *         later expanded through W_UV by wisp_gpu_mla_out.
 *
 * Phases: (1) scores  — one warp per cached position,
 *         (2) softmax — one block per head,
 *         (3) mix     — threads own value dims, iterate positions.
 *
 * KV cost check (GLM-5.2): one MLA entry = (kv_lora 512 + qk_rope 64)
 * fp16 = 1,152 bytes/layer -> 61 layers = ~70 KB per token. That is the
 * compressed cache that makes 1M-token context feasible in RAM; a
 * materialized K/V cache would be ~5 MB/token and is deliberately NOT
 * what this file implements.
 *
 * TODO: Add the real KDA (Kimi Delta Attention) path once the Kimi K3
 * technical report publishes July 27, 2026. KDA is hybrid linear
 * attention replacing quadratic attention in a subset of layers
 * (6.3x faster decoding at 1M context). Until then the engine routes
 * "KDA" models through the GQA phases below as a placeholder.
 */

#include <cuda_runtime.h>
#include <cuda_fp16.h>
#include <stdint.h>

#include "../core/wisp_engine.h"

/* --------------------------------------------------------------------- *
 * RoPE (neox / rotate-half convention, matches the Python drafter)
 * x layout: [n_heads, head_stride]; the rotary window is
 * [rope_off, rope_off + rope_dim) within each head.
 * --------------------------------------------------------------------- */
__global__ void rope_kernel(float* __restrict__ x, int head_stride,
                            int rope_off, int rope_dim, int pos,
                            float theta) {
    int h = blockIdx.x;
    int half = rope_dim / 2;
    float* v = x + (size_t)h * head_stride + rope_off;

    for (int i = threadIdx.x; i < half; i += blockDim.x) {
        float freq = __powf(theta, -2.0f * (float)i / (float)rope_dim);
        float ang = (float)pos * freq;
        float c, s;
        __sincosf(ang, &s, &c);
        float a = v[i], b = v[i + half];
        v[i]        = a * c - b * s;
        v[i + half] = b * c + a * s;
    }
}

extern "C" void wisp_gpu_rope(float* x, int n_heads, int head_stride,
                              int rope_off, int rope_dim, int pos,
                              float theta, cudaStream_t s) {
    if (n_heads <= 0 || rope_dim <= 0) return;
    rope_kernel<<<n_heads, 64, 0, s>>>(x, head_stride, rope_off,
                                       rope_dim, pos, theta);
}

/* --------------------------------------------------------------------- *
 * Phase 1: scores[h][t] = scale * dot(q[h], K[t][kv(h)])
 * grid: (n_heads, ceil(seq / warps_per_block)); one warp per position.
 * --------------------------------------------------------------------- */
#define ATTN_THREADS 128
#define WARPS_PER_BLOCK (ATTN_THREADS / 32)

__global__ void attn_scores_kernel(const float* __restrict__ q,
                                   const __half* __restrict__ K,
                                   float* __restrict__ scores,
                                   int seq, int kv_heads, int k_dim,
                                   int group, float scale, int max_seq) {
    int h = blockIdx.x;
    int warp = threadIdx.x >> 5;
    int lane = threadIdx.x & 31;
    int t = blockIdx.y * WARPS_PER_BLOCK + warp;
    if (t >= seq) return;

    int kvh = h / group;
    const float* qh = q + (size_t)h * k_dim;
    const __half* kt = K + ((size_t)t * kv_heads + kvh) * k_dim;

    float dot = 0.0f;
    for (int d = lane; d < k_dim; d += 32)
        dot += qh[d] * __half2float(kt[d]);

    #pragma unroll
    for (int off = 16; off > 0; off >>= 1)
        dot += __shfl_down_sync(0xffffffff, dot, off);

    if (lane == 0)
        scores[(size_t)h * max_seq + t] = dot * scale;
}

/* --------------------------------------------------------------------- *
 * Phase 2: in-place softmax over scores[h][0..seq)
 * --------------------------------------------------------------------- */
__global__ void attn_softmax_kernel(float* __restrict__ scores,
                                    int seq, int max_seq) {
    int h = blockIdx.x;
    float* sc = scores + (size_t)h * max_seq;

    __shared__ float red[ATTN_THREADS / 32];
    int lane = threadIdx.x & 31;
    int warp = threadIdx.x >> 5;

    /* max */
    float m = -1e30f;
    for (int t = threadIdx.x; t < seq; t += blockDim.x)
        m = fmaxf(m, sc[t]);
    #pragma unroll
    for (int off = 16; off > 0; off >>= 1)
        m = fmaxf(m, __shfl_down_sync(0xffffffff, m, off));
    if (lane == 0) red[warp] = m;
    __syncthreads();
    if (warp == 0) {
        m = (lane < ATTN_THREADS / 32) ? red[lane] : -1e30f;
        #pragma unroll
        for (int off = 16; off > 0; off >>= 1)
            m = fmaxf(m, __shfl_down_sync(0xffffffff, m, off));
        if (lane == 0) red[0] = m;
    }
    __syncthreads();
    m = red[0];
    __syncthreads();

    /* exp + sum */
    float sum = 0.0f;
    for (int t = threadIdx.x; t < seq; t += blockDim.x) {
        float e = __expf(sc[t] - m);
        sc[t] = e;
        sum += e;
    }
    #pragma unroll
    for (int off = 16; off > 0; off >>= 1)
        sum += __shfl_down_sync(0xffffffff, sum, off);
    if (lane == 0) red[warp] = sum;
    __syncthreads();
    if (warp == 0) {
        sum = (lane < ATTN_THREADS / 32) ? red[lane] : 0.0f;
        #pragma unroll
        for (int off = 16; off > 0; off >>= 1)
            sum += __shfl_down_sync(0xffffffff, sum, off);
        if (lane == 0) red[0] = sum;
    }
    __syncthreads();
    float inv = 1.0f / (red[0] > 0.0f ? red[0] : 1.0f);

    for (int t = threadIdx.x; t < seq; t += blockDim.x)
        sc[t] *= inv;
}

/* --------------------------------------------------------------------- *
 * Phase 3: out[h][d] = sum_t scores[h][t] * V[t][kv(h)][d]
 * v_stride handles the MLA aliasing (V == K but entries are k_dim wide).
 * --------------------------------------------------------------------- */
__global__ void attn_mix_kernel(const float* __restrict__ scores,
                                const __half* __restrict__ V,
                                float* __restrict__ out,
                                int seq, int kv_heads, int v_dim,
                                int v_stride, int group, int max_seq) {
    int h = blockIdx.x;
    int kvh = h / group;
    const float* sc = scores + (size_t)h * max_seq;
    float* oh = out + (size_t)h * v_dim;

    for (int d = threadIdx.x; d < v_dim; d += blockDim.x) {
        float acc = 0.0f;
        for (int t = 0; t < seq; t++) {
            const __half* vt = V + ((size_t)t * kv_heads + kvh) * v_stride;
            acc += sc[t] * __half2float(vt[d]);
        }
        oh[d] = acc;
    }
}

extern "C" void wisp_gpu_attention(const float* q, const wisp_half* Kc,
                                   const wisp_half* Vc, float* out,
                                   float* score_scratch, int seq_len,
                                   int n_heads, int kv_heads, int k_dim,
                                   int v_dim, float scale,
                                   cudaStream_t s) {
    if (seq_len <= 0 || n_heads <= 0) return;
    int group = n_heads / (kv_heads > 0 ? kv_heads : 1);
    if (group <= 0) group = 1;
    int v_stride = (Vc == Kc) ? k_dim : v_dim;
    /* score_scratch rows are max 32768 positions (engine allocation) */
    const int max_seq = 32768;

    dim3 sgrid(n_heads, (seq_len + WARPS_PER_BLOCK - 1) / WARPS_PER_BLOCK);
    attn_scores_kernel<<<sgrid, ATTN_THREADS, 0, s>>>(
        q, (const __half*)Kc, score_scratch, seq_len, kv_heads, k_dim,
        group, scale, max_seq);
    attn_softmax_kernel<<<n_heads, ATTN_THREADS, 0, s>>>(
        score_scratch, seq_len, max_seq);
    attn_mix_kernel<<<n_heads, ATTN_THREADS, 0, s>>>(
        score_scratch, (const __half*)Vc, out, seq_len, kv_heads, v_dim,
        v_stride, group, max_seq);
}

/* --------------------------------------------------------------------- *
 * MLA absorb: q_eff[h] = W_UK[h]^T @ q_nope[h] ++ q_rope[h]
 * kv_b rows per head: qk_nope K-up rows, then v_dim V-up rows.
 * --------------------------------------------------------------------- */
__global__ void mla_absorb_q_kernel(const __half* __restrict__ kv_b,
                                    const float* __restrict__ q,
                                    float* __restrict__ q_eff,
                                    int qk_nope, int qk_rope, int v_dim,
                                    int kv_lora) {
    int h = blockIdx.x;
    int head_rows = qk_nope + v_dim;
    int qs = qk_nope + qk_rope;
    int es = kv_lora + qk_rope;
    const __half* wuk = kv_b + (size_t)h * head_rows * kv_lora;
    const float* qh = q + (size_t)h * qs;
    float* eh = q_eff + (size_t)h * es;

    for (int c = threadIdx.x; c < kv_lora; c += blockDim.x) {
        float acc = 0.0f;
        for (int d = 0; d < qk_nope; d++)
            acc += __half2float(wuk[(size_t)d * kv_lora + c]) * qh[d];
        eh[c] = acc;
    }
    for (int d = threadIdx.x; d < qk_rope; d += blockDim.x)
        eh[kv_lora + d] = qh[qk_nope + d];
}

extern "C" void wisp_gpu_mla_absorb_q(const wisp_half* kv_b, const float* q,
                                      float* q_eff, int n_heads,
                                      int qk_nope, int qk_rope, int v_dim,
                                      int kv_lora, cudaStream_t s) {
    if (n_heads <= 0) return;
    mla_absorb_q_kernel<<<n_heads, ATTN_THREADS, 0, s>>>(
        (const __half*)kv_b, q, q_eff, qk_nope, qk_rope, v_dim, kv_lora);
}

/* MLA out: out_v[h] = W_UV[h] @ attn_c[h] */
__global__ void mla_out_kernel(const __half* __restrict__ kv_b,
                               const float* __restrict__ attn_c,
                               float* __restrict__ out,
                               int qk_nope, int v_dim, int kv_lora) {
    int h = blockIdx.x;
    int head_rows = qk_nope + v_dim;
    const __half* wuv = kv_b
        + ((size_t)h * head_rows + qk_nope) * kv_lora;
    const float* ch = attn_c + (size_t)h * kv_lora;
    float* oh = out + (size_t)h * v_dim;

    for (int d = threadIdx.x; d < v_dim; d += blockDim.x) {
        float acc = 0.0f;
        for (int c = 0; c < kv_lora; c++)
            acc += __half2float(wuv[(size_t)d * kv_lora + c]) * ch[c];
        oh[d] = acc;
    }
}

extern "C" void wisp_gpu_mla_out(const wisp_half* kv_b, const float* attn_c,
                                 float* out, int n_heads, int qk_nope,
                                 int v_dim, int kv_lora, cudaStream_t s) {
    if (n_heads <= 0) return;
    mla_out_kernel<<<n_heads, ATTN_THREADS, 0, s>>>(
        (const __half*)kv_b, attn_c, out, qk_nope, v_dim, kv_lora);
}
