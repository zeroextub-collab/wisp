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
 * THE RECURRENCE (identical in the CUDA and PyTorch paths — enforced by
 * tests/test_kda.py, which diffs the two)
 *
 *     qn = q / ||q||, kn = k / ||k||        L2, per head, over d_k
 *     b  = sigmoid(W_beta x)                per-channel write gate, (0,1)
 *     u  = S^T kn                           what memory currently holds
 *                                           at this key
 *     S  = S + b (.) kn (v - u)^T           write the PREDICTION ERROR
 *     o  = S^T qn                           read, with the new state
 *     y  = silu(g) (.) o                    output gate
 *
 * WHY IT IS WRITTEN THIS WAY — three properties, each load-bearing:
 *
 * 1. It writes (v - u), not v. That is what makes it a *delta* rule: the
 *    state is corrected by exactly the amount it was wrong by, so
 *    re-writing a key that is already stored is a no-op instead of
 *    doubling it. Plain linear attention (S += v k^T) accumulates and
 *    saturates; this does not.
 *
 * 2. q and k are L2-normalized. With ||kn|| = 1 and b in (0,1) the
 *    update is a gated projection along kn, so the state is corrected
 *    toward v rather than scaled by an unbounded factor, and the
 *    recurrence cannot blow up. Without normalization the effective
 *    decay is unbounded and the state diverges — measured: inf within
 *    200 tokens at input scale 3. Normalization happens INSIDE this
 *    kernel rather than at the call site precisely so that no caller
 *    can forget it.
 *
 * 3. o is read AFTER the write, so token t can see its own value.
 *    Read-before-write makes the first token of every conversation emit
 *    exactly zero, which no attention variant does.
 *
 * State layout: [batch, heads, d_k, d_v], indexed
 *   state[((b * H + h) * d_k + dk) * d_v + dv]
 * One thread owns one (b, h, dv) column and walks d_k.
 */

#include <cuda_runtime.h>
#include <cuda_fp16.h>
#include <stdint.h>
#include <math.h>

#include "../core/wisp_engine.h"

/* Largest d_k the fused prefill kernel can hold in per-thread local
 * memory. Beyond this the launcher falls back to looping the decode
 * kernel, which is slower but has no size limit and shares the exact
 * same arithmetic. Real head dims are 64-128; K3 sits at 7168/64 = 112. */
#define KDA_MAX_DK 512
#define KDA_THREADS 128
#define KDA_NORM_EPS 1e-12f

__device__ __forceinline__ float kda_sigmoid(float x) {
    return 1.0f / (1.0f + __expf(-x));
}

__device__ __forceinline__ float kda_silu(float x) {
    return x / (1.0f + __expf(-x));
}

/* Block-wide reciprocal L2 norm of an fp16 vector.
 *
 * EVERY thread in the block must call this — it contains __syncthreads().
 * Threads whose dv is past the end of d_v participate here and only then
 * drop out. Getting that ordering wrong is a hang, not a wrong answer. */
__device__ __forceinline__ float kda_block_rnorm(
        const __half* __restrict__ vec, int n, float* scratch) {
    float acc = 0.0f;
    for (int i = threadIdx.x; i < n; i += blockDim.x) {
        float x = __half2float(vec[i]);
        acc += x * x;
    }
    scratch[threadIdx.x] = acc;
    __syncthreads();
    for (int s = blockDim.x >> 1; s > 0; s >>= 1) {
        if (threadIdx.x < s) scratch[threadIdx.x] += scratch[threadIdx.x + s];
        __syncthreads();
    }
    float total = scratch[0];
    __syncthreads();          /* everyone has read before scratch is reused */
    return rsqrtf(total + KDA_NORM_EPS);
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
    __shared__ float red[KDA_THREADS];

    int b = blockIdx.x;
    int h = blockIdx.y;
    int dv = blockIdx.z * blockDim.x + threadIdx.x;

    size_t state_off = ((size_t)(b * num_heads + h)) * d_k * d_v;
    size_t qk_off    = ((size_t)(b * num_heads + h)) * d_k;
    size_t vo_off    = ((size_t)(b * num_heads + h)) * d_v + dv;

    /* Block-uniform: all threads reach both barriers. */
    float q_scale = kda_block_rnorm(q + qk_off, d_k, red);
    float k_scale = kda_block_rnorm(k + qk_off, d_k, red);

    if (dv >= d_v) return;              /* only now is it safe to leave */

    /* u = S^T kn — what the memory currently returns for this key. */
    float u = 0.0f;
    for (int dk = 0; dk < d_k; dk++)
        u += state[state_off + (size_t)dk * d_v + dv]
             * (__half2float(k[qk_off + dk]) * k_scale);

    float err = __half2float(v[vo_off]) - u;

    /* Fused write-then-read: S += b (.) kn err^T, then o = S^T qn. One
     * pass over d_k does both, and the read necessarily sees the
     * post-write state. */
    float out_val = 0.0f;
    for (int dk = 0; dk < d_k; dk++) {
        float kn = __half2float(k[qk_off + dk]) * k_scale;
        float bt = kda_sigmoid(__half2float(beta[qk_off + dk]));
        size_t s_idx = state_off + (size_t)dk * d_v + dv;
        float s = state[s_idx] + bt * kn * err;
        state[s_idx] = s;
        out_val += s * (__half2float(q[qk_off + dk]) * q_scale);
    }

    output[vo_off] = __float2half(
        kda_silu(__half2float(gate[vo_off])) * out_val);
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
    __shared__ float red[KDA_THREADS];

    int b = blockIdx.x;
    int h = blockIdx.y;
    int dv = blockIdx.z * blockDim.x + threadIdx.x;
    if (d_k > KDA_MAX_DK) return;   /* launcher guarantees this; uniform */

    int active = (dv < d_v);
    size_t state_off = ((size_t)(b * num_heads + h)) * d_k * d_v;

    float s[KDA_MAX_DK];
    if (active) {
        for (int dk = 0; dk < d_k; dk++)
            s[dk] = state_in ? state_in[state_off + (size_t)dk * d_v + dv]
                             : 0.0f;
    }

    for (int t = 0; t < seq_len; t++) {
        size_t qk_off = (((size_t)(b * seq_len + t)) * num_heads + h)
                        * (size_t)d_k;
        size_t vo_off = (((size_t)(b * seq_len + t)) * num_heads + h)
                        * (size_t)d_v + dv;

        /* Barriers first — inactive threads must participate. */
        float q_scale = kda_block_rnorm(q + qk_off, d_k, red);
        float k_scale = kda_block_rnorm(k + qk_off, d_k, red);
        if (!active) continue;

        float u = 0.0f;
        for (int dk = 0; dk < d_k; dk++)
            u += s[dk] * (__half2float(k[qk_off + dk]) * k_scale);

        float err = __half2float(v[vo_off]) - u;

        float out_val = 0.0f;
        for (int dk = 0; dk < d_k; dk++) {
            float kn = __half2float(k[qk_off + dk]) * k_scale;
            float bt = kda_sigmoid(__half2float(beta[qk_off + dk]));
            s[dk] += bt * kn * err;
            out_val += s[dk] * (__half2float(q[qk_off + dk]) * q_scale);
        }
        output[vo_off] = __float2half(
            kda_silu(__half2float(gate[vo_off])) * out_val);
    }

    if (active) {
        for (int dk = 0; dk < d_k; dk++)
            state_out[state_off + (size_t)dk * d_v + dv] = s[dk];
    }
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
    if (!state || !q || !k || !v || !beta || !gate || !output)
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
    if (!state_out || !q || !k || !v || !beta || !gate || !output)
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
     * launch per (batch, timestep).
     *
     * The decode kernel expects [B, H, ...] slices while the prefill
     * inputs are [B, T, H, ...], so the batch dimension has to be peeled
     * off explicitly — striding by t alone would silently feed batch 0's
     * token t+1 in as batch 1's token t. */
    size_t state_stride = (size_t)num_heads * d_k * d_v;
    size_t qk_tok       = (size_t)num_heads * d_k;
    size_t vo_tok       = (size_t)num_heads * d_v;
    size_t state_bytes  = (size_t)batch_size * state_stride * sizeof(float);

    /* The kernel path reads state_in and writes state_out; this path
     * updates state_out in place, so seed it first. */
    if (!state_in) {
        cudaError_t ce = cudaMemsetAsync(state_out, 0, state_bytes, stream);
        if (ce != cudaSuccess) return ce;
    } else if (state_in != state_out) {
        cudaError_t ce = cudaMemcpyAsync(state_out, state_in, state_bytes,
                                         cudaMemcpyDeviceToDevice, stream);
        if (ce != cudaSuccess) return ce;
    }

    for (int b = 0; b < batch_size; b++) {
        for (int t = 0; t < seq_len; t++) {
            size_t qk = ((size_t)b * seq_len + t) * qk_tok;
            size_t vo = ((size_t)b * seq_len + t) * vo_tok;
            cudaError_t e = wisp_kda_decode_step(
                state_out + (size_t)b * state_stride,
                q + qk, k + qk, v + vo, beta + qk, gate + vo, output + vo,
                /*batch=*/1, num_heads, d_k, d_v, stream);
            if (e != cudaSuccess) return e;
        }
    }
    return cudaSuccess;
}

/* Self-test: run the recurrence on a tiny known input and check the
 * result against the same recurrence computed on the host in double
 * precision. Exposed to pytest so the CUDA math is verified on real
 * hardware, not only against the PyTorch mirror. Returns 1 on success. */
int wisp_selftest_kda(void) {
    const int B = 1, H = 1, DK = 4, DV = 4, T = 3;
    size_t n_state = (size_t)B * H * DK * DV;

    __half hq[T * DK], hk[T * DK], hb[T * DK];
    __half hv[T * DV], hg[T * DV];
    double dq[T * DK], dkk[T * DK], db[T * DK], dvv[T * DV], dg[T * DV];

    for (int t = 0; t < T; t++) {
        for (int i = 0; i < DK; i++) {
            dq[t * DK + i]  = 0.1 * (i + 1) * (t + 1);
            dkk[t * DK + i] = 0.2 * (t + 1) + 0.05 * i;
            db[t * DK + i]  = 0.3 * i - 0.4;
            hq[t * DK + i] = __float2half((float)dq[t * DK + i]);
            hk[t * DK + i] = __float2half((float)dkk[t * DK + i]);
            hb[t * DK + i] = __float2half((float)db[t * DK + i]);
        }
        for (int j = 0; j < DV; j++) {
            dvv[t * DV + j] = 1.0 + t - 0.25 * j;
            dg[t * DV + j]  = 0.5 + 0.5 * j;
            hv[t * DV + j] = __float2half((float)dvv[t * DV + j]);
            hg[t * DV + j] = __float2half((float)dg[t * DV + j]);
        }
    }

    /* Host reference — the exact recurrence in the header comment. */
    double ref_state[16] = {0};
    double ref_out[T * DV];
    for (int t = 0; t < T; t++) {
        double qn2 = 0.0, kn2 = 0.0;
        for (int i = 0; i < DK; i++) {
            qn2 += dq[t * DK + i] * dq[t * DK + i];
            kn2 += dkk[t * DK + i] * dkk[t * DK + i];
        }
        double qs = 1.0 / sqrt(qn2 + 1e-12);
        double ks = 1.0 / sqrt(kn2 + 1e-12);

        for (int j = 0; j < DV; j++) {
            double u = 0.0;
            for (int i = 0; i < DK; i++)
                u += ref_state[i * DV + j] * (dkk[t * DK + i] * ks);
            double err = dvv[t * DV + j] - u;

            double o = 0.0;
            for (int i = 0; i < DK; i++) {
                double kn = dkk[t * DK + i] * ks;
                double bt = 1.0 / (1.0 + exp(-db[t * DK + i]));
                ref_state[i * DV + j] += bt * kn * err;
                o += ref_state[i * DV + j] * (dq[t * DK + i] * qs);
            }
            double g = dg[t * DV + j];
            ref_out[t * DV + j] = (g / (1.0 + exp(-g))) * o;
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
            double tol = 0.02 * fabs(want) + 0.02;
            if (fabs(got - want) > tol) ok = 0;
        }
        for (int i = 0; i < (int)n_state && ok; i++) {
            if (fabs((double)host_state[i] - ref_state[i]) > 0.02) ok = 0;
        }
        /* The very first token must produce a NON-ZERO output. A kernel
         * that read the state before writing it would emit exactly zero
         * here and otherwise look correct. */
        if (ok) {
            int nonzero = 0;
            for (int i = 0; i < DV; i++)
                if (fabs((double)__half2float(host_out[i])) > 1e-4)
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
