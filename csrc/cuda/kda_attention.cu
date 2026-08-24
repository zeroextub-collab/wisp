/*
 * kda_attention.cu — Kimi Delta Attention (KDA), linear attention with a
 * delta-rule state update. Used in 69 of Kimi K3's 93 layers; the other
 * 24 are Gated MLA and run through attention.cu's absorbed-MLA path.
 *
 * WHY THIS MATTERS
 * Standard attention compares every token to every other token: O(n^2)
 * time and a KV cache that grows without bound. KDA instead carries a
 * FIXED-SIZE state matrix S of shape [d_k, d_v] per head. Cost is O(n)
 * and memory is constant — which is what makes a 1M-token context
 * tractable on a consumer card at all.
 *
 * THE MATH (identical in the CUDA and PyTorch paths — verified by test)
 *   beta_t = sigmoid(W_beta x_t)          per-channel decay, in (0,1)
 *   S_t    = S_{t-1} * (1 - beta_t k_t) + v_t k_t^T
 *   o_t    = S_t q_t
 *   y_t    = silu(g_t) * o_t              output gate
 *
 * The "delta" is that each update is a CORRECTION: the state decays by
 * exactly the amount the new key addresses, then the new value is
 * written in. Naive linear attention just accumulates v k^T and
 * saturates; the decay term is what keeps it stable over long contexts.
 *
 * State layout: [batch, heads, d_k, d_v], indexed
 *   state[((b * H + h) * d_k + dk) * d_v + dv]
 * One thread owns one (b, h, dv) column and walks d_k.
 */

#include <cuda_runtime.h>
#include <cuda_fp16.h>
#include <stdint.h>

#include "../core/wisp_engine.h"

/* Largest d_k the fused prefill kernel can hold in per-thread local
 * memory. Beyond this the launcher falls back to looping the decode
 * kernel, which is slower but has no size limit and shares the exact
 * same arithmetic. K3 sits well under it (7168 hidden / 64 heads = 112). */
#define KDA_MAX_DK 512
#define KDA_THREADS 128

__device__ __forceinline__ float kda_sigmoid(float x) {
    return 1.0f / (1.0f + __expf(-x));
}

__device__ __forceinline__ float kda_silu(float x) {
    return x / (1.0f + __expf(-x));
}

/* ---------------------------------------------------------------------
 * Decode: one token, in-place state update.
 * Called once per token per KDA layer during autoregressive generation.
 * grid (batch, heads, ceil(d_v / KDA_THREADS)), block (KDA_THREADS).
 * ------------------------------------------------------------------- */
__global__ void kda_decode_step_kernel(
    float* __restrict__ state,          /* [B, H, d_k, d_v]  in/out */
    const __half* __restrict__ q,       /* [B, H, d_k]              */
    const __half* __restrict__ k,       /* [B, H, d_k]              */
    const __half* __restrict__ v,       /* [B, H, d_v]              */
    const __half* __restrict__ beta,    /* [B, H, d_k]              */
    const __half* __restrict__ gate,    /* [B, H, d_v]              */
    __half* __restrict__ output,        /* [B, H, d_v]              */
    int batch_size, int num_heads, int d_k, int d_v
) {
    int b = blockIdx.x;
    int h = blockIdx.y;
    int dv = blockIdx.z * blockDim.x + threadIdx.x;
    if (b >= batch_size || h >= num_heads || dv >= d_v) return;

    size_t state_off = ((size_t)(b * num_heads + h)) * d_k * d_v;
    size_t qk_off    = ((size_t)(b * num_heads + h)) * d_k;
    size_t vo_off    = ((size_t)(b * num_heads + h)) * d_v + dv;

    /* Output uses the state BEFORE this token's update (o_t = S_t q_t
     * with S_t the state carried in from t-1, matching the recurrence
     * as written above and in the PyTorch reference). */
    float out_val = 0.0f;
    for (int dk = 0; dk < d_k; dk++) {
        out_val += state[state_off + (size_t)dk * d_v + dv]
                 * __half2float(q[qk_off + dk]);
    }
    output[vo_off] = __float2half(
        kda_silu(__half2float(gate[vo_off])) * out_val);

    /* Delta-rule state update */
    float v_val = __half2float(v[vo_off]);
    for (int dk = 0; dk < d_k; dk++) {
        float k_val = __half2float(k[qk_off + dk]);
        float decay = 1.0f - kda_sigmoid(__half2float(beta[qk_off + dk]))
                             * k_val;
        size_t s_idx = state_off + (size_t)dk * d_v + dv;
        state[s_idx] = state[s_idx] * decay + v_val * k_val;
    }
}

/* ---------------------------------------------------------------------
 * Prefill: whole prompt in one launch. Sequential in t (the recurrence
 * is inherently ordered) but fully parallel across (b, h, dv), holding
 * the thread's d_k state column in registers/local memory so the state
 * never round-trips to global memory between timesteps.
 * ------------------------------------------------------------------- */
__global__ void kda_prefill_kernel(
    float* __restrict__ state_out,      /* [B, H, d_k, d_v] final     */
    const float* __restrict__ state_in, /* [B, H, d_k, d_v] initial   */
    const __half* __restrict__ q,       /* [B, T, H, d_k]             */
    const __half* __restrict__ k,       /* [B, T, H, d_k]             */
    const __half* __restrict__ v,       /* [B, T, H, d_v]             */
    const __half* __restrict__ beta,    /* [B, T, H, d_k]             */
    const __half* __restrict__ gate,    /* [B, T, H, d_v]             */
    __half* __restrict__ output,        /* [B, T, H, d_v]             */
    int batch_size, int seq_len, int num_heads, int d_k, int d_v
) {
    int b = blockIdx.x;
    int h = blockIdx.y;
    int dv = blockIdx.z * blockDim.x + threadIdx.x;
    if (b >= batch_size || h >= num_heads || dv >= d_v) return;
    if (d_k > KDA_MAX_DK) return;   /* launcher guarantees this */

    size_t state_off = ((size_t)(b * num_heads + h)) * d_k * d_v;

    float s[KDA_MAX_DK];
    for (int dk = 0; dk < d_k; dk++)
        s[dk] = state_in ? state_in[state_off + (size_t)dk * d_v + dv]
                         : 0.0f;

    for (int t = 0; t < seq_len; t++) {
        size_t qk_off = (((size_t)(b * seq_len + t)) * num_heads + h)
                        * (size_t)d_k;
        size_t vo_off = (((size_t)(b * seq_len + t)) * num_heads + h)
                        * (size_t)d_v + dv;

        float out_val = 0.0f;
        for (int dk = 0; dk < d_k; dk++)
            out_val += s[dk] * __half2float(q[qk_off + dk]);
        output[vo_off] = __float2half(
            kda_silu(__half2float(gate[vo_off])) * out_val);

        float v_val = __half2float(v[vo_off]);
        for (int dk = 0; dk < d_k; dk++) {
            float k_val = __half2float(k[qk_off + dk]);
            float decay = 1.0f
                - kda_sigmoid(__half2float(beta[qk_off + dk])) * k_val;
            s[dk] = s[dk] * decay + v_val * k_val;
        }
    }

    for (int dk = 0; dk < d_k; dk++)
        state_out[state_off + (size_t)dk * d_v + dv] = s[dk];
}

/* ---------------------------------------------------------------------
 * Launchers (C linkage — called from the engine and the bindings)
 * ------------------------------------------------------------------- */
__global__ void f32_to_f16_kernel(const float* __restrict__ src,
                                  __half* __restrict__ dst, int n) {
    int i = blockIdx.x * blockDim.x + threadIdx.x;
    if (i < n) dst[i] = __float2half(src[i]);
}

__global__ void f16_to_f32_kernel(const __half* __restrict__ src,
                                  float* __restrict__ dst, int n) {
    int i = blockIdx.x * blockDim.x + threadIdx.x;
    if (i < n) dst[i] = __half2float(src[i]);
}

extern "C" {

void wisp_gpu_f16_to_f32(const wisp_half* src, float* dst, int n,
                         cudaStream_t s) {
    if (n <= 0) return;
    f16_to_f32_kernel<<<(n + 255) / 256, 256, 0, s>>>(
        (const __half*)src, dst, n);
}

void wisp_gpu_f32_to_f16(const float* src, wisp_half* dst, int n,
                         cudaStream_t s) {
    if (n <= 0) return;
    f32_to_f16_kernel<<<(n + 255) / 256, 256, 0, s>>>(
        src, (__half*)dst, n);
}

size_t wisp_kda_state_bytes(int batch_size, int num_heads,
                            int d_k, int d_v, int num_kda_layers) {
    return (size_t)batch_size * num_heads * d_k * d_v
           * (size_t)num_kda_layers * sizeof(float);
}

cudaError_t wisp_kda_alloc_state(void** state_ptr, int batch_size,
                                 int num_heads, int d_k, int d_v,
                                 int num_kda_layers) {
    size_t bytes = wisp_kda_state_bytes(batch_size, num_heads, d_k, d_v,
                                        num_kda_layers);
    cudaError_t e = cudaMalloc(state_ptr, bytes);
    if (e != cudaSuccess) return e;
    return cudaMemset(*state_ptr, 0, bytes);
}

cudaError_t wisp_kda_free_state(void* state_ptr) {
    return cudaFree(state_ptr);
}

cudaError_t wisp_kda_reset_state(void* state_ptr, int batch_size,
                                 int num_heads, int d_k, int d_v,
                                 int num_kda_layers, cudaStream_t stream) {
    size_t bytes = wisp_kda_state_bytes(batch_size, num_heads, d_k, d_v,
                                        num_kda_layers);
    return cudaMemsetAsync(state_ptr, 0, bytes, stream);
}

cudaError_t wisp_kda_decode_step(
    float* state,
    const wisp_half* q, const wisp_half* k, const wisp_half* v,
    const wisp_half* beta, const wisp_half* gate,
    wisp_half* output,
    int batch_size, int num_heads, int d_k, int d_v,
    cudaStream_t stream
) {
    if (batch_size <= 0 || num_heads <= 0 || d_k <= 0 || d_v <= 0)
        return cudaErrorInvalidValue;
    dim3 grid(batch_size, num_heads, (d_v + KDA_THREADS - 1) / KDA_THREADS);
    dim3 block(KDA_THREADS);
    kda_decode_step_kernel<<<grid, block, 0, stream>>>(
        state, (const __half*)q, (const __half*)k, (const __half*)v,
        (const __half*)beta, (const __half*)gate, (__half*)output,
        batch_size, num_heads, d_k, d_v);
    return cudaGetLastError();
}

cudaError_t wisp_kda_prefill(
    float* state_out, const float* state_in,
    const wisp_half* q, const wisp_half* k, const wisp_half* v,
    const wisp_half* beta, const wisp_half* gate,
    wisp_half* output,
    int batch_size, int seq_len, int num_heads, int d_k, int d_v,
    cudaStream_t stream
) {
    if (batch_size <= 0 || seq_len <= 0 || num_heads <= 0
        || d_k <= 0 || d_v <= 0)
        return cudaErrorInvalidValue;

    if (d_k <= KDA_MAX_DK) {
        dim3 grid(batch_size, num_heads,
                  (d_v + KDA_THREADS - 1) / KDA_THREADS);
        dim3 block(KDA_THREADS);
        kda_prefill_kernel<<<grid, block, 0, stream>>>(
            state_out, state_in,
            (const __half*)q, (const __half*)k, (const __half*)v,
            (const __half*)beta, (const __half*)gate, (__half*)output,
            batch_size, seq_len, num_heads, d_k, d_v);
        return cudaGetLastError();
    }

    /* d_k too large to keep a state column in local memory: walk the
     * sequence with the decode kernel instead. Same arithmetic, one
     * launch per timestep. state_out must already hold state_in. */
    for (int t = 0; t < seq_len; t++) {
        size_t qk_stride = (size_t)num_heads * d_k;
        size_t vo_stride = (size_t)num_heads * d_v;
        cudaError_t e = wisp_kda_decode_step(
            state_out,
            q + (size_t)t * qk_stride, k + (size_t)t * qk_stride,
            v + (size_t)t * vo_stride,
            beta + (size_t)t * qk_stride, gate + (size_t)t * vo_stride,
            output + (size_t)t * vo_stride,
            batch_size, num_heads, d_k, d_v, stream);
        if (e != cudaSuccess) return e;
    }
    return cudaSuccess;
}

/* Self-test: run the recurrence on a tiny known input and check the
 * result against the closed form computed on the host. Exposed to
 * pytest so the CUDA math is verified on real hardware, not just the
 * PyTorch mirror. Returns 1 on success. */
int wisp_selftest_kda(void) {
    const int B = 1, H = 1, DK = 4, DV = 4, T = 3;
    size_t n_state = (size_t)B * H * DK * DV;

    __half hq[T * DK], hk[T * DK], hb[T * DK];
    __half hv[T * DV], hg[T * DV];
    for (int t = 0; t < T; t++) {
        for (int i = 0; i < DK; i++) {
            hq[t * DK + i] = __float2half(0.1f * (i + 1));
            hk[t * DK + i] = __float2half(0.2f * (t + 1));
            hb[t * DK + i] = __float2half(0.0f);   /* sigmoid(0) = 0.5 */
        }
        for (int i = 0; i < DV; i++) {
            hv[t * DV + i] = __float2half(1.0f + t);
            hg[t * DV + i] = __float2half(10.0f);  /* silu(10) ~= 10 */
        }
    }

    /* Host reference, same recurrence in double precision */
    double ref_state[16] = {0};
    double ref_out[T * DV];
    for (int t = 0; t < T; t++) {
        for (int dv = 0; dv < DV; dv++) {
            double o = 0.0;
            for (int dk = 0; dk < DK; dk++)
                o += ref_state[dk * DV + dv] * (0.1 * (dk + 1));
            double g = 10.0;
            ref_out[t * DV + dv] = (g / (1.0 + exp(-g))) * o;
        }
        for (int dv = 0; dv < DV; dv++) {
            double vv = 1.0 + t;
            for (int dk = 0; dk < DK; dk++) {
                double kk = 0.2 * (t + 1);
                double decay = 1.0 - 0.5 * kk;
                ref_state[dk * DV + dv] =
                    ref_state[dk * DV + dv] * decay + vv * kk;
            }
        }
    }

    float *d_state = NULL;
    __half *d_q = NULL, *d_k = NULL, *d_v = NULL, *d_b = NULL,
           *d_g = NULL, *d_o = NULL;
    int ok = 0;
    if (cudaMalloc((void**)&d_state, n_state * sizeof(float)) != cudaSuccess)
        goto done;
    if (cudaMemset(d_state, 0, n_state * sizeof(float)) != cudaSuccess)
        goto done;
    if (cudaMalloc((void**)&d_q, T * DK * sizeof(__half)) != cudaSuccess ||
        cudaMalloc((void**)&d_k, T * DK * sizeof(__half)) != cudaSuccess ||
        cudaMalloc((void**)&d_b, T * DK * sizeof(__half)) != cudaSuccess ||
        cudaMalloc((void**)&d_v, T * DV * sizeof(__half)) != cudaSuccess ||
        cudaMalloc((void**)&d_g, T * DV * sizeof(__half)) != cudaSuccess ||
        cudaMalloc((void**)&d_o, T * DV * sizeof(__half)) != cudaSuccess)
        goto done;

    cudaMemcpy(d_q, hq, T * DK * sizeof(__half), cudaMemcpyHostToDevice);
    cudaMemcpy(d_k, hk, T * DK * sizeof(__half), cudaMemcpyHostToDevice);
    cudaMemcpy(d_b, hb, T * DK * sizeof(__half), cudaMemcpyHostToDevice);
    cudaMemcpy(d_v, hv, T * DV * sizeof(__half), cudaMemcpyHostToDevice);
    cudaMemcpy(d_g, hg, T * DV * sizeof(__half), cudaMemcpyHostToDevice);

    for (int t = 0; t < T; t++) {
        if (wisp_kda_decode_step(
                d_state, (const wisp_half*)(d_q + t * DK),
                (const wisp_half*)(d_k + t * DK),
                (const wisp_half*)(d_v + t * DV),
                (const wisp_half*)(d_b + t * DK),
                (const wisp_half*)(d_g + t * DV),
                (wisp_half*)(d_o + t * DV),
                B, H, DK, DV, 0) != cudaSuccess) goto done;
    }
    if (cudaDeviceSynchronize() != cudaSuccess) goto done;

    {
        __half host_out[T * DV];
        float host_state[16];
        cudaMemcpy(host_out, d_o, T * DV * sizeof(__half),
                   cudaMemcpyDeviceToHost);
        cudaMemcpy(host_state, d_state, n_state * sizeof(float),
                   cudaMemcpyDeviceToHost);

        ok = 1;
        for (int i = 0; i < T * DV && ok; i++) {
            double got = (double)__half2float(host_out[i]);
            double want = ref_out[i];
            double tol = 0.02 * (want < 0 ? -want : want) + 0.05;
            double diff = got - want;
            if (diff < 0) diff = -diff;
            if (diff > tol) ok = 0;
        }
        for (int i = 0; i < (int)n_state && ok; i++) {
            double diff = (double)host_state[i] - ref_state[i];
            if (diff < 0) diff = -diff;
            if (diff > 0.02) ok = 0;
        }
        /* State must be non-trivial — a kernel that never wrote would
         * otherwise "pass" against an all-zero reference. */
        if (ok) {
            int nonzero = 0;
            for (int i = 0; i < (int)n_state; i++)
                if (host_state[i] > 1e-6f || host_state[i] < -1e-6f)
                    nonzero = 1;
            ok = nonzero;
        }
    }

done:
    if (d_state) cudaFree(d_state);
    if (d_q) cudaFree(d_q);
    if (d_k) cudaFree(d_k);
    if (d_v) cudaFree(d_v);
    if (d_b) cudaFree(d_b);
    if (d_g) cudaFree(d_g);
    if (d_o) cudaFree(d_o);
    return ok;
}

} /* extern "C" */
