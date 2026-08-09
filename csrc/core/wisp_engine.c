/*
 * wisp_engine.c — engine lifecycle, the expert-fetch hot path, and the
 * full token forward pass (MLA + GQA), with both GPU dispatch and an
 * OpenMP CPU fallback compiled from the same source.
 *
 * Layout of this file:
 *   1.  Platform: monotonic clock, fp16 conversion, WISP_NO_CUDA shim
 *   2.  Tiny JSON + safetensors readers (for manifest.json / dense weights)
 *   3.  Expert blob parsing + SSD reads
 *   4.  CPU math ops (OpenMP)
 *   5.  Dispatch ops (GPU kernel or CPU op, chosen at runtime)
 *   6.  Tier plumbing: RAM/VRAM put-with-eviction, expert_fetch, prefetch
 *   7.  Forward pass: attention (MLA absorbed / GQA), router, expert FFN
 *   8.  Public API: create/destroy, kv cache, prefill/decode/verify, stats
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

#ifdef _OPENMP
#include <omp.h>
#endif

#include "wisp_engine.h"
#include "lru_cache.h"
#include "double_buffer.h"
#include "mem_pool.h"

/* ======================================================================= *
 * 1. Platform
 * ======================================================================= */

#ifdef _WIN32
uint64_t wisp_now_ns(void) {
    static LARGE_INTEGER freq = {0};
    LARGE_INTEGER now;
    if (freq.QuadPart == 0) QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&now);
    return (uint64_t)((double)now.QuadPart * 1e9 / (double)freq.QuadPart);
}
#else
#include <time.h>
uint64_t wisp_now_ns(void) {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (uint64_t)ts.tv_sec * 1000000000ull + (uint64_t)ts.tv_nsec;
}
#endif

float wisp_half_to_float(uint16_t h) {
    uint32_t sign = (uint32_t)(h & 0x8000) << 16;
    uint32_t exp = (h >> 10) & 0x1F;
    uint32_t mant = h & 0x3FF;
    uint32_t bits;
    if (exp == 0) {
        if (mant == 0) {
            bits = sign;                       /* +-0 */
        } else {                               /* subnormal */
            exp = 127 - 15 + 1;
            while (!(mant & 0x400)) { mant <<= 1; exp--; }
            mant &= 0x3FF;
            bits = sign | (exp << 23) | (mant << 13);
        }
    } else if (exp == 31) {
        bits = sign | 0x7F800000 | (mant << 13);   /* inf/nan */
    } else {
        bits = sign | ((exp - 15 + 127) << 23) | (mant << 13);
    }
    float f;
    memcpy(&f, &bits, 4);
    return f;
}

uint16_t wisp_float_to_half(float f) {
    uint32_t bits;
    memcpy(&bits, &f, 4);
    uint32_t sign = (bits >> 16) & 0x8000;
    int32_t exp = (int32_t)((bits >> 23) & 0xFF) - 127 + 15;
    uint32_t mant = bits & 0x7FFFFF;
    if (exp <= 0) {
        if (exp < -10) return (uint16_t)sign;          /* underflow -> 0 */
        mant |= 0x800000;
        uint32_t shift = (uint32_t)(14 - exp);
        return (uint16_t)(sign | (mant >> shift));
    }
    if (exp >= 31) return (uint16_t)(sign | 0x7C00);   /* overflow -> inf */
    return (uint16_t)(sign | (uint32_t)(exp << 10) | (mant >> 13));
}

static float halfbits_to_float(const wisp_half* p, size_t i) {
    const uint16_t* u = (const uint16_t*)p;
    return wisp_half_to_float(u[i]);
}

/* --- WISP_NO_CUDA shim: host memory stand-ins ------------------------- */
#ifdef WISP_NO_CUDA
const char* cudaGetErrorString(cudaError_t e) {
    (void)e; return "cuda-disabled build";
}
cudaError_t cudaMalloc(void** p, size_t n) {
    *p = malloc(n); return *p ? cudaSuccess : 1;
}
cudaError_t cudaFree(void* p) { free(p); return cudaSuccess; }
cudaError_t cudaHostAlloc(void** p, size_t n, unsigned int flags) {
    (void)flags; *p = malloc(n); return *p ? cudaSuccess : 1;
}
cudaError_t cudaFreeHost(void* p) { free(p); return cudaSuccess; }
cudaError_t cudaMemcpy(void* d, const void* s, size_t n, cudaMemcpyKind k) {
    (void)k; memcpy(d, s, n); return cudaSuccess;
}
cudaError_t cudaMemcpyAsync(void* d, const void* s, size_t n,
                            cudaMemcpyKind k, cudaStream_t st) {
    (void)k; (void)st; memcpy(d, s, n); return cudaSuccess;
}
cudaError_t cudaMemsetAsync(void* p, int v, size_t n, cudaStream_t s) {
    (void)s; memset(p, v, n); return cudaSuccess;
}
cudaError_t cudaStreamCreate(cudaStream_t* s) { *s = NULL; return cudaSuccess; }
cudaError_t cudaStreamDestroy(cudaStream_t s) { (void)s; return cudaSuccess; }
cudaError_t cudaStreamSynchronize(cudaStream_t s) { (void)s; return cudaSuccess; }
cudaError_t cudaEventCreate(cudaEvent_t* e) { *e = NULL; return cudaSuccess; }
cudaError_t cudaEventDestroy(cudaEvent_t e) { (void)e; return cudaSuccess; }
cudaError_t cudaEventRecord(cudaEvent_t e, cudaStream_t s) {
    (void)e; (void)s; return cudaSuccess;
}
cudaError_t cudaEventSynchronize(cudaEvent_t e) { (void)e; return cudaSuccess; }
cudaError_t cudaSetDevice(int d) { (void)d; return 1; }  /* no devices */
#endif

/* ======================================================================= *
 * 2. Tiny JSON + safetensors readers
 * ======================================================================= */

static char* read_entire_file(const char* path, size_t* out_size) {
    FILE* f = fopen(path, "rb");
    if (!f) return NULL;
    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    fseek(f, 0, SEEK_SET);
    if (size < 0) { fclose(f); return NULL; }
    char* buf = (char*)malloc((size_t)size + 1);
    if (!buf) { fclose(f); return NULL; }
    size_t got = fread(buf, 1, (size_t)size, f);
    fclose(f);
    if (got != (size_t)size) { free(buf); return NULL; }
    buf[size] = '\0';
    if (out_size) *out_size = (size_t)size;
    return buf;
}

/* Find `"key"` and return a pointer just past the following ':'. */
static const char* json_value_of(const char* json, const char* key) {
    char pat[128];
    snprintf(pat, sizeof(pat), "\"%s\"", key);
    const char* p = strstr(json, pat);
    if (!p) return NULL;
    p += strlen(pat);
    while (*p && *p != ':') p++;
    if (*p != ':') return NULL;
    p++;
    while (*p && isspace((unsigned char)*p)) p++;
    return p;
}

static double json_double(const char* json, const char* key, double dflt) {
    const char* p = json_value_of(json, key);
    if (!p) return dflt;
    return strtod(p, NULL);
}

static int64_t json_int(const char* json, const char* key, int64_t dflt) {
    const char* p = json_value_of(json, key);
    if (!p) return dflt;
    return (int64_t)strtod(p, NULL);   /* tolerates 1e9-style numbers */
}

static int json_string(const char* json, const char* key,
                       char* out, size_t out_size) {
    const char* p = json_value_of(json, key);
    if (!p || *p != '"') return 0;
    p++;
    size_t i = 0;
    while (*p && *p != '"' && i + 1 < out_size) out[i++] = *p++;
    out[i] = '\0';
    return 1;
}

/* --- safetensors ------------------------------------------------------- */

typedef struct {
    FILE* f;
    char* header;          /* JSON header (owned)                          */
    uint64_t data_start;   /* file offset where tensor data begins         */
} StFile;

static int st_open(StFile* st, const char* path) {
    memset(st, 0, sizeof(*st));
    st->f = fopen(path, "rb");
    if (!st->f) return 0;
    uint8_t len_le[8];
    if (fread(len_le, 1, 8, st->f) != 8) { fclose(st->f); return 0; }
    uint64_t hlen = 0;
    for (int i = 7; i >= 0; i--) hlen = (hlen << 8) | len_le[i];
    if (hlen == 0 || hlen > (1ull << 31)) { fclose(st->f); return 0; }
    st->header = (char*)malloc(hlen + 1);
    if (!st->header) { fclose(st->f); return 0; }
    if (fread(st->header, 1, hlen, st->f) != hlen) {
        free(st->header); fclose(st->f); return 0;
    }
    st->header[hlen] = '\0';
    st->data_start = 8 + hlen;
    return 1;
}

static void st_close(StFile* st) {
    if (st->f) fclose(st->f);
    free(st->header);
    memset(st, 0, sizeof(*st));
}

/* Locate a tensor by exact name. Returns 1 and fills offsets/shape. */
static int st_find(const StFile* st, const char* name,
                   uint64_t* off, uint64_t* nbytes,
                   int64_t shape[8], int* ndim) {
    char pat[512];
    snprintf(pat, sizeof(pat), "\"%s\":", name);
    const char* p = strstr(st->header, pat);
    if (!p) return 0;
    const char* obj = strchr(p + strlen(pat), '{');
    if (!obj) return 0;
    const char* end = strchr(obj, '}');
    if (!end) return 0;

    /* shape */
    *ndim = 0;
    const char* sh = strstr(obj, "\"shape\"");
    if (sh && sh < end) {
        sh = strchr(sh, '[');
        if (sh && sh < end) {
            sh++;
            while (*sh != ']' && *ndim < 8) {
                shape[(*ndim)++] = strtoll(sh, (char**)&sh, 10);
                while (*sh == ',' || isspace((unsigned char)*sh)) sh++;
            }
        }
    }
    /* data_offsets */
    const char* d = strstr(obj, "\"data_offsets\"");
    if (!d || d > end) return 0;
    d = strchr(d, '[');
    if (!d) return 0;
    d++;
    uint64_t a = strtoull(d, (char**)&d, 10);
    while (*d == ',' || isspace((unsigned char)*d)) d++;
    uint64_t b = strtoull(d, NULL, 10);
    *off = a;
    *nbytes = b - a;
    return 1;
}

/* ======================================================================= *
 * 3. Expert blob parsing + SSD reads
 * ======================================================================= */

WispError wisp_expert_parse_header(const void* blob, size_t blob_size,
                                   WispExpertMeta* meta, WispErrCtx* err) {
    WISP_CHECK_NULL(blob, err, "expert_parse_header: blob");
    if (blob_size < sizeof(WispExpertHeader)) {
        WISP_ERR_SET(err, WISP_ERR_MODEL,
                     "expert blob too small: %zu bytes", blob_size);
        return WISP_ERR_MODEL;
    }
    const WispExpertHeader* h = (const WispExpertHeader*)blob;
    if (h->magic != WISP_EXPERT_MAGIC || h->version != WISP_EXPERT_VERSION ||
        h->n_mats != WISP_EXPERT_NMATS) {
        WISP_ERR_SET(err, WISP_ERR_MODEL,
                     "expert blob corrupt: magic=%08x version=%u n_mats=%u",
                     h->magic, h->version, h->n_mats);
        return WISP_ERR_MODEL;
    }
    size_t off = sizeof(WispExpertHeader);
    for (int m = 0; m < WISP_EXPERT_NMATS; m++) {
        meta->rows[m] = h->mats[m].rows;
        meta->cols[m] = h->mats[m].cols;
        meta->packed_off[m] = off; off += h->mats[m].packed_bytes;
        meta->scales_off[m] = off; off += h->mats[m].scales_bytes;
        meta->zeros_off[m]  = off; off += h->mats[m].zeros_bytes;
    }
    meta->group_size = h->group_size;
    meta->total_bytes = off;
    meta->valid = 1;
    if (off > blob_size) {
        WISP_ERR_SET(err, WISP_ERR_MODEL,
                     "expert blob truncated: needs %zu, have %zu",
                     off, blob_size);
        meta->valid = 0;
        return WISP_ERR_MODEL;
    }
    return WISP_OK;
}

/* Byte-layout cross-check for the test suite: read an expert .bin from
 * disk, parse it with the engine's real header parser, and dequantize
 * the first n values of matrix `mat` with the engine's exact int4 math
 * ((nibble - 8) * scale + zero, low nibble first, groups of group_size).
 * tests/test_adapters.py compares the result against the Python-side
 * dequantizer to prove packer, C reader, and dequant all agree. */
WispError wisp_debug_expert_probe(const char* path, int mat, int n,
                                  float* out_values,
                                  WispExpertMeta* out_meta,
                                  WispErrCtx* err) {
    WISP_CHECK_NULL(path, err, "debug_probe: path");
    WISP_CHECK_NULL(out_values, err, "debug_probe: output");
    if (mat < 0 || mat >= WISP_EXPERT_NMATS || n <= 0) {
        WISP_ERR_SET(err, WISP_ERR_INVALID_ARG,
                     "debug_probe: mat=%d n=%d", mat, n);
        return WISP_ERR_INVALID_ARG;
    }
    size_t size = 0;
    char* blob = read_entire_file(path, &size);
    if (!blob) {
        WISP_ERR_SET(err, WISP_ERR_IO, "debug_probe: cannot read %s", path);
        return WISP_ERR_IO;
    }
    WispExpertMeta meta;
    WispError e = wisp_expert_parse_header(blob, size, &meta, err);
    if (e != WISP_OK) { free(blob); return e; }

    size_t total = (size_t)meta.rows[mat] * meta.cols[mat];
    if ((size_t)n > total) n = (int)total;

    const uint8_t* packed = (const uint8_t*)blob + meta.packed_off[mat];
    const uint16_t* scales = (const uint16_t*)(blob + meta.scales_off[mat]);
    const uint16_t* zeros = (const uint16_t*)(blob + meta.zeros_off[mat]);
    for (int i = 0; i < n; i++) {
        uint8_t byte = packed[i >> 1];
        int nib = (i & 1) ? (byte >> 4) : (byte & 0x0F);
        size_t g = (size_t)i / meta.group_size;
        float scale = wisp_half_to_float(scales[g]);
        float zero = wisp_half_to_float(zeros[g]);
        out_values[i] = (float)(nib - 8) * scale + zero;
    }
    if (out_meta) *out_meta = meta;
    free(blob);
    return WISP_OK;
}

static size_t read_expert_ssd(const char* model_path, uint32_t layer,
                              uint32_t expert, void* dst, size_t max_bytes,
                              WispErrCtx* err) {
    char path[1200];
    snprintf(path, sizeof(path), "%s/experts/L%03u_E%05u.bin",
             model_path, layer, expert);
    FILE* f = fopen(path, "rb");
    if (!f) {
        WISP_ERR_SET(err, WISP_ERR_IO, "expert file missing: %s", path);
        return 0;
    }
    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    fseek(f, 0, SEEK_SET);
    if (size <= 0 || (size_t)size > max_bytes) {
        fclose(f);
        WISP_ERR_SET(err, WISP_ERR_IO,
                     "expert file %s size %ld exceeds staging %zu",
                     path, size, max_bytes);
        return 0;
    }
    size_t got = fread(dst, 1, (size_t)size, f);
    fclose(f);
    if (got != (size_t)size) {
        WISP_ERR_SET(err, WISP_ERR_IO,
                     "short read on %s: %zu of %ld", path, got, size);
        return 0;
    }
    return got;
}

/* ======================================================================= *
 * 4. CPU math ops (OpenMP)
 * ======================================================================= */

/* NOTE: MSVC ships OpenMP 2.0, whose C-mode canonical form requires the
 * loop index declared OUTSIDE the for-init. The for-control variable is
 * implicitly private per the OpenMP spec, so this is safe. */
static void cpu_gemv_f16(const wisp_half* W, const float* x, float* y,
                         int rows, int cols) {
    int r;
    #pragma omp parallel for schedule(static)
    for (r = 0; r < rows; r++) {
        const uint16_t* row = (const uint16_t*)W + (size_t)r * cols;
        float acc = 0.f;
        for (int c = 0; c < cols; c++)
            acc += wisp_half_to_float(row[c]) * x[c];
        y[r] = acc;
    }
}

static void cpu_gemv_t_f16(const wisp_half* W, const float* x, float* y,
                           int rows, int cols) {
    int c;
    #pragma omp parallel for schedule(static)
    for (c = 0; c < cols; c++) {
        const uint16_t* w = (const uint16_t*)W;
        float acc = 0.f;
        for (int r = 0; r < rows; r++)
            acc += wisp_half_to_float(w[(size_t)r * cols + c]) * x[r];
        y[c] = acc;
    }
}

static void cpu_rmsnorm(const float* x, const wisp_half* w, float* y,
                        int n, float eps) {
    double ss = 0.0;
    for (int i = 0; i < n; i++) ss += (double)x[i] * x[i];
    float scale = (float)(1.0 / sqrt(ss / n + eps));
    for (int i = 0; i < n; i++)
        y[i] = x[i] * scale * halfbits_to_float(w, i);
}

static void cpu_residual_add(float* x, const float* d, int n) {
    for (int i = 0; i < n; i++) x[i] += d[i];
}

static void cpu_swiglu(const float* g, const float* u, float* o, int n) {
    for (int i = 0; i < n; i++) {
        float s = g[i] / (1.f + expf(-g[i]));   /* silu */
        o[i] = s * u[i];
    }
}

static void cpu_scale_accum(float* acc, const float* x, float w, int n) {
    for (int i = 0; i < n; i++) acc[i] += w * x[i];
}

static void cpu_embed_lookup(const wisp_half* table, int token, float* x,
                             int hidden) {
    const uint16_t* row = (const uint16_t*)table + (size_t)token * hidden;
    for (int i = 0; i < hidden; i++) x[i] = wisp_half_to_float(row[i]);
}

/* Neox-style rotary: pairs (i, i + rope_dim/2) within the rope window. */
static void cpu_rope(float* x, int n_heads, int head_stride, int rope_off,
                     int rope_dim, int pos, float theta) {
    int half = rope_dim / 2;
    for (int h = 0; h < n_heads; h++) {
        float* v = x + (size_t)h * head_stride + rope_off;
        for (int i = 0; i < half; i++) {
            float freq = powf(theta, -2.0f * (float)i / (float)rope_dim);
            float ang = (float)pos * freq;
            float c = cosf(ang), s = sinf(ang);
            float a = v[i], b = v[i + half];
            v[i] = a * c - b * s;
            v[i + half] = b * c + a * s;
        }
    }
}

/* Two-pass attention over the fp16 KV cache.
 * K layout: [seq, kv_heads, k_dim]. V: [seq, kv_heads, v_dim]; when
 * V == K the value read is the first v_dim dims of the K entry (MLA). */
static void cpu_attention(const float* q, const wisp_half* K,
                          const wisp_half* V, float* out, float* scores,
                          int seq, int n_heads, int kv_heads,
                          int k_dim, int v_dim, float scale) {
    int group = n_heads / (kv_heads > 0 ? kv_heads : 1);
    int v_stride = (V == K) ? k_dim : v_dim;
    int h;
    #pragma omp parallel for schedule(static)
    for (h = 0; h < n_heads; h++) {
        int kvh = h / (group > 0 ? group : 1);
        const float* qh = q + (size_t)h * k_dim;
        float* sc = scores + (size_t)h * seq;

        float maxv = -1e30f;
        for (int t = 0; t < seq; t++) {
            const uint16_t* kt = (const uint16_t*)K
                + ((size_t)t * kv_heads + kvh) * k_dim;
            float dot = 0.f;
            for (int d = 0; d < k_dim; d++)
                dot += qh[d] * wisp_half_to_float(kt[d]);
            sc[t] = dot * scale;
            if (sc[t] > maxv) maxv = sc[t];
        }
        float denom = 0.f;
        for (int t = 0; t < seq; t++) {
            sc[t] = expf(sc[t] - maxv);
            denom += sc[t];
        }
        float inv = 1.f / (denom > 0.f ? denom : 1.f);

        float* oh = out + (size_t)h * v_dim;
        for (int d = 0; d < v_dim; d++) oh[d] = 0.f;
        for (int t = 0; t < seq; t++) {
            const uint16_t* vt = (const uint16_t*)V
                + ((size_t)t * kv_heads + kvh) * v_stride;
            float w = sc[t] * inv;
            for (int d = 0; d < v_dim; d++)
                oh[d] += w * wisp_half_to_float(vt[d]);
        }
    }
}

static void cpu_kv_append(wisp_half* K, wisp_half* V, const float* k,
                          const float* v, int pos, int kv_heads,
                          int k_dim, int v_dim) {
    uint16_t* kd = (uint16_t*)K + (size_t)pos * kv_heads * k_dim;
    for (int i = 0; i < kv_heads * k_dim; i++)
        kd[i] = wisp_float_to_half(k[i]);
    if (V && v && v_dim > 0) {
        uint16_t* vd = (uint16_t*)V + (size_t)pos * kv_heads * v_dim;
        for (int i = 0; i < kv_heads * v_dim; i++)
            vd[i] = wisp_float_to_half(v[i]);
    }
}

static void cpu_router_topk(const wisp_half* W, const wisp_half* bias,
                            const float* x, float* logits, int n_experts,
                            int hidden, int top_k, int* out_idx,
                            float* out_w) {
    cpu_gemv_f16(W, x, logits, n_experts, hidden);
    if (bias) {
        for (int e = 0; e < n_experts; e++)
            logits[e] += halfbits_to_float(bias, e);
    }
    /* softmax */
    float maxv = -1e30f;
    for (int e = 0; e < n_experts; e++)
        if (logits[e] > maxv) maxv = logits[e];
    float denom = 0.f;
    for (int e = 0; e < n_experts; e++) {
        logits[e] = expf(logits[e] - maxv);
        denom += logits[e];
    }
    for (int e = 0; e < n_experts; e++) logits[e] /= denom;
    /* top-k selection sort (k is tiny: 4-8) */
    float wsum = 0.f;
    for (int k = 0; k < top_k; k++) {
        int best = -1;
        float bestv = -1.f;
        for (int e = 0; e < n_experts; e++) {
            int taken = 0;
            for (int j = 0; j < k; j++)
                if (out_idx[j] == e) { taken = 1; break; }
            if (!taken && logits[e] > bestv) { bestv = logits[e]; best = e; }
        }
        out_idx[k] = best;
        out_w[k] = bestv;
        wsum += bestv;
    }
    if (wsum > 0.f)
        for (int k = 0; k < top_k; k++) out_w[k] /= wsum;   /* renormalize */
}

/* Fused int4 dequant + gemv straight from a packed expert matrix.
 * dequant: value = (nibble - 8) * scale + zero; low nibble = even index. */
static void cpu_gemv_int4(const uint8_t* packed, const uint16_t* scales,
                          const uint16_t* zeros, const float* x, float* y,
                          int rows, int cols, int gs) {
    int r;
    #pragma omp parallel for schedule(static)
    for (r = 0; r < rows; r++) {
        size_t base = (size_t)r * cols;
        float acc = 0.f;
        for (int c = 0; c < cols; c++) {
            size_t idx = base + c;
            uint8_t byte = packed[idx >> 1];
            int nib = (idx & 1) ? (byte >> 4) : (byte & 0x0F);
            size_t g = idx / (size_t)gs;
            float scale = wisp_half_to_float(scales[g]);
            float zero  = wisp_half_to_float(zeros[g]);
            acc += ((float)(nib - 8) * scale + zero) * x[c];
        }
        y[r] = acc;
    }
}

/* MLA absorb: q_eff[h] = W_UK[h]^T @ q_nope[h], rope dims copied through.
 * kv_b layout: rows grouped per head: qk_nope K-up rows then v_dim V-up. */
static void cpu_mla_absorb_q(const wisp_half* kv_b, const float* q,
                             float* q_eff, int n_heads, int qk_nope,
                             int qk_rope, int v_dim, int kv_lora) {
    int head_rows = qk_nope + v_dim;
    int qs = qk_nope + qk_rope;         /* q head stride                   */
    int es = kv_lora + qk_rope;         /* q_eff head stride               */
    int h;
    #pragma omp parallel for schedule(static)
    for (h = 0; h < n_heads; h++) {
        const uint16_t* wuk = (const uint16_t*)kv_b
            + (size_t)h * head_rows * kv_lora;
        const float* qh = q + (size_t)h * qs;
        float* eh = q_eff + (size_t)h * es;
        for (int c = 0; c < kv_lora; c++) {
            float acc = 0.f;
            for (int d = 0; d < qk_nope; d++)
                acc += wisp_half_to_float(wuk[(size_t)d * kv_lora + c]) * qh[d];
            eh[c] = acc;
        }
        for (int d = 0; d < qk_rope; d++)
            eh[kv_lora + d] = qh[qk_nope + d];
    }
}

/* MLA out: out_v[h] = W_UV[h] @ attn_c[h]. */
static void cpu_mla_out(const wisp_half* kv_b, const float* attn_c,
                        float* out, int n_heads, int qk_nope, int v_dim,
                        int kv_lora) {
    int head_rows = qk_nope + v_dim;
    int h;
    #pragma omp parallel for schedule(static)
    for (h = 0; h < n_heads; h++) {
        const uint16_t* wuv = (const uint16_t*)kv_b
            + ((size_t)h * head_rows + qk_nope) * kv_lora;
        const float* ch = attn_c + (size_t)h * kv_lora;
        float* oh = out + (size_t)h * v_dim;
        for (int d = 0; d < v_dim; d++) {
            float acc = 0.f;
            for (int c = 0; c < kv_lora; c++)
                acc += wisp_half_to_float(wuv[(size_t)d * kv_lora + c]) * ch[c];
            oh[d] = acc;
        }
    }
}

/* ======================================================================= *
 * 5. Dispatch ops — GPU kernel when eng->use_gpu, else the CPU op.
 * ======================================================================= */

#ifndef WISP_NO_CUDA
#define DISPATCH(eng, gpu_call, cpu_call) \
    do { if ((eng)->use_gpu) { gpu_call; } else { cpu_call; } } while (0)
#else
#define DISPATCH(eng, gpu_call, cpu_call) do { cpu_call; } while (0)
#endif

static void op_gemv(WispEngine* e, const wisp_half* W, const float* x,
                    float* y, int rows, int cols) {
    DISPATCH(e, wisp_gpu_gemv_f16(W, x, y, rows, cols, e->compute_stream),
             cpu_gemv_f16(W, x, y, rows, cols));
}

static void op_rmsnorm(WispEngine* e, const float* x, const wisp_half* w,
                       float* y, int n) {
    DISPATCH(e, wisp_gpu_rmsnorm(x, w, y, n, e->cfg.rms_eps, e->compute_stream),
             cpu_rmsnorm(x, w, y, n, e->cfg.rms_eps));
}

static void op_residual(WispEngine* e, float* x, const float* d, int n) {
    DISPATCH(e, wisp_gpu_residual_add(x, d, n, e->compute_stream),
             cpu_residual_add(x, d, n));
}

static void op_swiglu(WispEngine* e, const float* g, const float* u,
                      float* o, int n) {
    DISPATCH(e, wisp_gpu_swiglu(g, u, o, n, e->compute_stream),
             cpu_swiglu(g, u, o, n));
}

/* Fused SwiGLU front half: h = silu(Wg@x) * (Wu@x). One kernel launch on
 * GPU; the CPU path composes the same three steps (its cost is dominated
 * by the fp16 loads either way). */
static void op_swiglu_ffn(WispEngine* e, const wisp_half* Wg,
                          const wisp_half* Wu, const float* x, float* h,
                          int inter, int cols) {
#ifndef WISP_NO_CUDA
    if (e->use_gpu) {
        wisp_gpu_swiglu_ffn(Wg, Wu, x, h, inter, cols, e->compute_stream);
        return;
    }
#endif
    cpu_gemv_f16(Wg, x, e->buf_gate, inter, cols);
    cpu_gemv_f16(Wu, x, e->buf_up, inter, cols);
    cpu_swiglu(e->buf_gate, e->buf_up, h, inter);
}

static void op_scale_accum(WispEngine* e, float* acc, const float* x,
                           float w, int n) {
    DISPATCH(e, wisp_gpu_scale_accum(acc, x, w, n, e->compute_stream),
             cpu_scale_accum(acc, x, w, n));
}

static void op_embed(WispEngine* e, int token, float* x) {
    DISPATCH(e, wisp_gpu_embed_lookup(e->embed_tokens, token, x,
                                      e->cfg.hidden, e->compute_stream),
             cpu_embed_lookup(e->embed_tokens, token, x, e->cfg.hidden));
}

static void op_rope(WispEngine* e, float* x, int n_heads, int stride,
                    int off, int dim, int pos) {
    DISPATCH(e, wisp_gpu_rope(x, n_heads, stride, off, dim, pos,
                              e->cfg.rope_theta, e->compute_stream),
             cpu_rope(x, n_heads, stride, off, dim, pos, e->cfg.rope_theta));
}

static void op_attention(WispEngine* e, const float* q, const wisp_half* K,
                         const wisp_half* V, float* out, int seq,
                         int n_heads, int kv_heads, int k_dim, int v_dim,
                         float scale) {
    DISPATCH(e, wisp_gpu_attention(q, K, V, out, e->buf_scores, seq, n_heads,
                                   kv_heads, k_dim, v_dim, scale,
                                   e->compute_stream),
             cpu_attention(q, K, V, out, e->buf_scores, seq, n_heads,
                           kv_heads, k_dim, v_dim, scale));
}

static void op_kv_append(WispEngine* e, wisp_half* K, wisp_half* V,
                         const float* k, const float* v, int pos,
                         int kv_heads, int k_dim, int v_dim) {
    DISPATCH(e, wisp_gpu_kv_append(K, V, k, v, pos, kv_heads, k_dim, v_dim,
                                   e->compute_stream),
             cpu_kv_append(K, V, k, v, pos, kv_heads, k_dim, v_dim));
}

/* Device/host memory helpers — "device" means host memory when !use_gpu. */
static void* eng_alloc(WispEngine* e, size_t n, WispErrCtx* err) {
    void* p = NULL;
#ifndef WISP_NO_CUDA
    if (e->use_gpu) {
        cudaError_t ce = cudaMalloc(&p, n);
        if (ce != cudaSuccess) {
            WISP_ERR_SET(err, WISP_ERR_OOM,
                         "device alloc %zu failed: %s", n,
                         cudaGetErrorString(ce));
            return NULL;
        }
        cudaMemsetAsync(p, 0, n, e->compute_stream);
        return p;
    }
#endif
    (void)e;
    p = calloc(1, n);
    if (!p) WISP_ERR_SET(err, WISP_ERR_OOM, "host alloc %zu failed", n);
    return p;
}

static void eng_free(WispEngine* e, void* p) {
    if (!p) return;
#ifndef WISP_NO_CUDA
    if (e->use_gpu) { cudaFree(p); return; }
#endif
    (void)e;
    free(p);
}

static int eng_h2d(WispEngine* e, void* dst, const void* src, size_t n) {
#ifndef WISP_NO_CUDA
    if (e->use_gpu)
        return cudaMemcpy(dst, src, n, cudaMemcpyHostToDevice) == cudaSuccess;
#endif
    (void)e;
    memcpy(dst, src, n);
    return 1;
}

static int eng_d2h(WispEngine* e, void* dst, const void* src, size_t n) {
#ifndef WISP_NO_CUDA
    if (e->use_gpu)
        return cudaMemcpy(dst, src, n, cudaMemcpyDeviceToHost) == cudaSuccess;
#endif
    (void)e;
    memcpy(dst, src, n);
    return 1;
}

static void eng_sync(WispEngine* e) {
#ifndef WISP_NO_CUDA
    if (e->use_gpu) cudaStreamSynchronize(e->compute_stream);
#endif
    (void)e;
}

/* ======================================================================= *
 * 6. Tier plumbing
 * ======================================================================= */

static void free_ram_payload(void* data, void* ctx) {
    (void)ctx;
    free(data);
}

/* Insert into the RAM cache, evicting LRU entries to make room.
 * RAM OOM policy: evicted experts are simply dropped — the SSD copy is
 * authoritative, so demotion to SSD is a free() away. */
static WispError ram_put_evicting(WispEngine* eng, uint32_t layer,
                                  uint32_t expert, void* data, size_t size,
                                  WispErrCtx* err) {
    LRUCache* ram = eng->ram_cache;
    if (size > ram->capacity_bytes) {
        free(data);   /* cache too small for even one expert — skip tier */
        return WISP_OK;
    }
    while (lru_would_overflow(ram, size)) {
        LRUNode* victim = lru_evict(ram);
        if (!victim) break;
        free(victim->data_ptr);
        lru_node_free(victim);
    }
    return lru_put(ram, layer, expert, data, size, err);
}

/* Allocate VRAM for an expert blob, evicting VRAM-LRU entries back to the
 * RAM tier until the allocation fits. Returns NULL when it cannot fit at
 * all (err set only on real CUDA failure). */
static void* vram_alloc_evicting(WispEngine* eng, size_t size,
                                 WispErrCtx* err) {
    for (;;) {
        void* p = wisp_vram_alloc(eng->vram_budget, size, err);
        if (p) return p;
        if (err->code == WISP_ERR_CUDA) return NULL;

        LRUNode* victim = lru_evict(eng->vram_cache);
        if (!victim) return NULL;   /* nothing left to evict */

        /* Copy the victim back to RAM so a future hit stays warm */
        void* host_copy = malloc(victim->size_bytes);
        if (host_copy) {
            if (eng_d2h(eng, host_copy, victim->data_ptr,
                        victim->size_bytes)) {
                WispErrCtx tmp = {0};
                ram_put_evicting(eng, victim->layer_id, victim->expert_id,
                                 host_copy, victim->size_bytes, &tmp);
            } else {
                free(host_copy);
            }
        }
        wisp_vram_free(eng->vram_budget, victim->data_ptr,
                       victim->size_bytes);
        lru_node_free(victim);
    }
}

/* Records a tier hit AND appends to the expert access log. Both happen
 * under the one lock the fetch path already takes, so the log is free
 * beyond a couple of stores. */
static void stat_hit_logged(WispEngine* eng, int tier,
                            uint32_t layer, uint32_t expert) {
    wisp_mutex_lock(&eng->stats_mutex);
    if (tier == 0) eng->vram_hits++;
    else if (tier == 1) eng->ram_hits++;
    else eng->ssd_hits++;

    if (eng->access_log && eng->access_log_cap > 0) {
        eng->access_log[eng->access_log_head] =
            ((layer & 0xFFFFu) << 16) | (expert & 0xFFFFu);
        eng->access_log_head =
            (eng->access_log_head + 1) % eng->access_log_cap;
        if (eng->access_log_count < eng->access_log_cap)
            eng->access_log_count++;
        else
            eng->access_log_dropped++;   /* oldest entry overwritten */
    }
    wisp_mutex_unlock(&eng->stats_mutex);
}

int wisp_drain_expert_log(WispEngine* eng, uint32_t* out, int max_out,
                          uint64_t* dropped_out) {
    if (!eng || !out || max_out <= 0) return 0;
    wisp_mutex_lock(&eng->stats_mutex);
    int n = eng->access_log_count;
    if (n > max_out) n = max_out;
    /* Oldest-first: the ring's tail is head - count (mod cap). */
    int start = (eng->access_log_head - eng->access_log_count
                 + eng->access_log_cap * 2) % eng->access_log_cap;
    for (int i = 0; i < n; i++)
        out[i] = eng->access_log[(start + i) % eng->access_log_cap];
    if (dropped_out) *dropped_out = eng->access_log_dropped;
    eng->access_log_count = 0;
    eng->access_log_head = 0;
    eng->access_log_dropped = 0;
    wisp_mutex_unlock(&eng->stats_mutex);
    return n;
}

/* Serve an expert blob through the scratch ring: one H2D copy into a
 * persistent device buffer, no cache insertion, no eviction. The ring
 * holds top_k+2 slots so every expert of the current layer stays valid
 * simultaneously. Returns the device pointer, or NULL on CUDA failure. */
static void* scratch_serve(WispEngine* eng, const void* host_src,
                           size_t n, WispErrCtx* err) {
    void* slot = eng->scratch_ring[eng->scratch_pos];
    eng->scratch_pos = (eng->scratch_pos + 1) % eng->scratch_slots;
#ifndef WISP_NO_CUDA
    cudaError_t ce = cudaMemcpyAsync(slot, host_src, n,
                                     cudaMemcpyHostToDevice,
                                     eng->transfer_stream);
    cudaStreamSynchronize(eng->transfer_stream);
    if (ce != cudaSuccess) {
        WISP_ERR_SET(err, WISP_ERR_CUDA, "scratch H2D failed: %s",
                     cudaGetErrorString(ce));
        return NULL;
    }
#else
    memcpy(slot, host_src, n);
    (void)err;
#endif
    return slot;
}

/*
 * expert_fetch — called top_k x num_layers times per token
 * (488 for GLM-5.2). This IS the hot path.
 */
void* wisp_expert_fetch(WispEngine* eng, uint32_t layer_id,
                        uint32_t expert_id, WispErrCtx* err) {
    /* 1. VRAM hit (fastest — return immediately) */
    if (eng->experts_on_gpu) {
        LRUNode* node = lru_get(eng->vram_cache, layer_id, expert_id);
        if (node) {
            lru_touch(eng->vram_cache, node);
            stat_hit_logged(eng, 0, layer_id, expert_id);
            return node->data_ptr;
        }
    }

    /* 2. RAM hit — promote to VRAM (or serve directly in CPU/hybrid mode) */
    LRUNode* node = lru_get(eng->ram_cache, layer_id, expert_id);
    if (node) {
        lru_touch(eng->ram_cache, node);
        stat_hit_logged(eng, 1, layer_id, expert_id);
        /* Prefetched blobs may not have populated the layer meta yet */
        if (!eng->expert_meta[layer_id].valid) {
            if (wisp_expert_parse_header(node->data_ptr, node->size_bytes,
                                         &eng->expert_meta[layer_id],
                                         err) != WISP_OK)
                return NULL;
        }
        if (!eng->experts_on_gpu) return node->data_ptr;

        /* Promotion policy: an expert earns a real VRAM slot (possibly
         * evicting a colder one) only after it has proven hot. Cool
         * experts ride the scratch ring — one H2D, zero churn. */
        node->hits++;
        if (node->hits < WISP_PROMOTE_HITS)
            return scratch_serve(eng, node->data_ptr,
                                 node->size_bytes, err);

        void* vram_ptr = vram_alloc_evicting(eng, node->size_bytes, err);
        if (!vram_ptr) {
            if (err->code == WISP_ERR_CUDA) return NULL;
            /* Can't place it — serve from scratch rather than fail */
            err->code = WISP_OK;
            return scratch_serve(eng, node->data_ptr,
                                 node->size_bytes, err);
        }
#ifndef WISP_NO_CUDA
        cudaError_t pe = cudaMemcpyAsync(vram_ptr, node->data_ptr,
                                         node->size_bytes,
                                         cudaMemcpyHostToDevice,
                                         eng->transfer_stream);
        /* Source is pageable RAM owned by the LRU — drain before anyone
         * can evict/free it under the in-flight copy. */
        cudaStreamSynchronize(eng->transfer_stream);
        if (pe != cudaSuccess) {
            wisp_vram_free(eng->vram_budget, vram_ptr, node->size_bytes);
            WISP_ERR_SET(err, WISP_ERR_CUDA, "RAM->VRAM promote failed: %s",
                         cudaGetErrorString(pe));
            return NULL;
        }
#else
        memcpy(vram_ptr, node->data_ptr, node->size_bytes);
#endif
        if (lru_put(eng->vram_cache, layer_id, expert_id, vram_ptr,
                    node->size_bytes, err) != WISP_OK) {
            wisp_vram_free(eng->vram_budget, vram_ptr, node->size_bytes);
            return NULL;
        }
        return vram_ptr;
    }

    /* 3. SSD miss — read from disk through the staging buffer */
    void* staging = eng->pinned_pool
        ? pinned_pool_alloc(eng->pinned_pool, /*blocking=*/1)
        : malloc(eng->max_expert_bytes);
    if (!staging) {
        WISP_ERR_SET(err, WISP_ERR_OOM,
                     "expert staging alloc failed (%zu bytes)",
                     eng->max_expert_bytes);
        return NULL;
    }

    size_t n = read_expert_ssd(eng->model_path, layer_id, expert_id,
                               staging, eng->max_expert_bytes, err);
    if (n == 0) {
        if (eng->pinned_pool) pinned_pool_free(eng->pinned_pool, staging);
        else free(staging);
        return NULL;   /* err already set by read_expert_ssd */
    }
    stat_hit_logged(eng, 2, layer_id, expert_id);

    /* Parse layer meta on first sight (all experts in a layer share shape) */
    if (!eng->expert_meta[layer_id].valid) {
        if (wisp_expert_parse_header(staging, n, &eng->expert_meta[layer_id],
                                     err) != WISP_OK) {
            if (eng->pinned_pool) pinned_pool_free(eng->pinned_pool, staging);
            else free(staging);
            return NULL;
        }
    }

    /* Keep a host copy in the RAM tier for future hits */
    void* ram_copy = malloc(n);
    if (ram_copy) {
        memcpy(ram_copy, staging, n);
        WispErrCtx tmp = {0};
        ram_put_evicting(eng, layer_id, expert_id, ram_copy, n, &tmp);
    }

    if (!eng->experts_on_gpu) {
        /* CPU/hybrid mode: the RAM copy is the working copy */
        if (eng->pinned_pool) pinned_pool_free(eng->pinned_pool, staging);
        else free(staging);
        LRUNode* rn = lru_get(eng->ram_cache, layer_id, expert_id);
        if (rn) return rn->data_ptr;
        WISP_ERR_SET(err, WISP_ERR_OOM,
                     "expert L%u/E%u: RAM tier rejected blob (%zu bytes)",
                     layer_id, expert_id, n);
        return NULL;
    }

    /* GPU mode: claim a VRAM cache slot only when FREE budget exists —
     * a cold-from-SSD expert has not earned an eviction. Otherwise it
     * rides the scratch ring; its RAM copy warms future hits. */
    void* vram_ptr = wisp_vram_alloc(eng->vram_budget, n, err);
    if (!vram_ptr && err->code == WISP_ERR_CUDA) {
        if (eng->pinned_pool) pinned_pool_free(eng->pinned_pool, staging);
        else free(staging);
        return NULL;
    }
    if (!vram_ptr) {
        void* served = scratch_serve(eng, staging, n, err);
        if (eng->pinned_pool) pinned_pool_free(eng->pinned_pool, staging);
        else free(staging);
        return served;
    }
#ifndef WISP_NO_CUDA
    cudaError_t ce = cudaMemcpyAsync(vram_ptr, staging, n,
                                     cudaMemcpyHostToDevice,
                                     eng->transfer_stream);
    /* The pinned staging buffer must stay valid until the copy drains */
    cudaStreamSynchronize(eng->transfer_stream);
    if (ce != cudaSuccess) {
        if (eng->pinned_pool) pinned_pool_free(eng->pinned_pool, staging);
        else free(staging);
        wisp_vram_free(eng->vram_budget, vram_ptr, n);
        WISP_ERR_SET(err, WISP_ERR_CUDA, "expert H2D failed: %s",
                     cudaGetErrorString(ce));
        return NULL;
    }
#else
    memcpy(vram_ptr, staging, n);
#endif
    if (eng->pinned_pool) pinned_pool_free(eng->pinned_pool, staging);
    else free(staging);

    if (lru_put(eng->vram_cache, layer_id, expert_id, vram_ptr, n,
                err) != WISP_OK) {
        wisp_vram_free(eng->vram_budget, vram_ptr, n);
        return NULL;
    }
    return vram_ptr;
}

/* --- prefetch queue + worker ------------------------------------------- */

#define PREFETCH_RING 1024

typedef struct PrefetchQueue {
    uint32_t layer[PREFETCH_RING];
    uint32_t expert[PREFETCH_RING];
    int head, tail, count;
    int shutdown;
    wisp_mutex_t mutex;
    wisp_cond_t nonempty;
    wisp_thread_t worker;
    int worker_running;
    WispEngine* eng;
} PrefetchQueue;

static void* prefetch_worker(void* arg) {
    PrefetchQueue* q = (PrefetchQueue*)arg;
    WispEngine* eng = q->eng;
    void* staging = malloc(eng->max_expert_bytes);
    if (!staging) return NULL;

    for (;;) {
        wisp_mutex_lock(&q->mutex);
        while (q->count == 0 && !q->shutdown)
            wisp_cond_wait(&q->nonempty, &q->mutex);
        if (q->shutdown && q->count == 0) {
            wisp_mutex_unlock(&q->mutex);
            break;
        }
        uint32_t layer = q->layer[q->head];
        uint32_t expert = q->expert[q->head];
        q->head = (q->head + 1) % PREFETCH_RING;
        q->count--;
        wisp_mutex_unlock(&q->mutex);

        /* Already resident anywhere? Then the hint is satisfied. */
        if (eng->experts_on_gpu &&
            lru_get(eng->vram_cache, layer, expert)) continue;
        if (lru_get(eng->ram_cache, layer, expert)) continue;

        /* Warm the RAM tier. Promotion to VRAM happens on first real use,
         * which keeps the prefetch thread off the VRAM allocator locks. */
        WispErrCtx err = {0};
        size_t n = read_expert_ssd(eng->model_path, layer, expert,
                                   staging, eng->max_expert_bytes, &err);
        if (n == 0) continue;   /* IO problems are non-fatal on prefetch */
        if (!eng->expert_meta[layer].valid)
            wisp_expert_parse_header(staging, n, &eng->expert_meta[layer],
                                     &err);
        void* copy = malloc(n);
        if (!copy) continue;
        memcpy(copy, staging, n);
        ram_put_evicting(eng, layer, expert, copy, n, &err);
    }
    free(staging);
    return NULL;
}

static PrefetchQueue* prefetch_start(WispEngine* eng) {
    PrefetchQueue* q = (PrefetchQueue*)calloc(1, sizeof(PrefetchQueue));
    if (!q) return NULL;
    q->eng = eng;
    wisp_mutex_init(&q->mutex);
    wisp_cond_init(&q->nonempty);
    if (wisp_thread_create(&q->worker, prefetch_worker, q) == 0) {
        q->worker_running = 1;
    }
    return q;
}

static void prefetch_stop(PrefetchQueue* q) {
    if (!q) return;
    wisp_mutex_lock(&q->mutex);
    q->shutdown = 1;
    wisp_cond_broadcast(&q->nonempty);
    wisp_mutex_unlock(&q->mutex);
    if (q->worker_running) wisp_thread_join(q->worker);
    wisp_mutex_destroy(&q->mutex);
    free(q);
}

void wisp_expert_prefetch_hint(WispEngine* eng, int layer_idx,
                               const int* expert_ids, int n) {
    if (!eng || !eng->prefetch || layer_idx < 0 ||
        layer_idx >= eng->cfg.num_layers) return;
    PrefetchQueue* q = eng->prefetch;
    wisp_mutex_lock(&q->mutex);
    for (int i = 0; i < n && q->count < PREFETCH_RING; i++) {
        if (expert_ids[i] < 0 || expert_ids[i] >= eng->cfg.n_experts) continue;
        q->layer[q->tail] = (uint32_t)layer_idx;
        q->expert[q->tail] = (uint32_t)expert_ids[i];
        q->tail = (q->tail + 1) % PREFETCH_RING;
        q->count++;
    }
    wisp_cond_signal(&q->nonempty);
    wisp_mutex_unlock(&q->mutex);
}

/* ======================================================================= *
 * 7. Forward pass
 * ======================================================================= */

static wisp_half* kv_k_layer(WispKVCache* kv, int layer) {
    return kv->base + (size_t)layer * kv->k_layer_stride;
}

static wisp_half* kv_v_layer(WispKVCache* kv, int layer) {
    if (!kv->v_base) return NULL;
    return kv->v_base + (size_t)layer * kv->v_layer_stride;
}

static WispError run_attention(WispEngine* eng, int layer, WispKVCache* kv,
                               WispErrCtx* err) {
    WispModelConfig* c = &eng->cfg;
    WispLayerWeights* w = &eng->layers[layer];
    int pos = kv->len;   /* the token being processed sits at this index  */

    if (c->attn_type == WISP_ATTN_MLA) {
        int qs = c->qk_nope + c->qk_rope;
        int k_dim = c->kv_lora + c->qk_rope;
        float scale = 1.0f / sqrtf((float)qs);

        /* q = q_b(rmsnorm(q_a(x)))  — or a straight q_proj for families
         * without the q low-rank path */
        float* q = eng->buf_attn_b;
        if (w->q_a_proj) {
            op_gemv(eng, w->q_a_proj, eng->buf_norm, eng->buf_attn_a,
                    c->q_lora, c->hidden);
            if (w->q_a_norm)
                op_rmsnorm(eng, eng->buf_attn_a, w->q_a_norm,
                           eng->buf_attn_a, c->q_lora);
            op_gemv(eng, w->q_b_proj, eng->buf_attn_a, q,
                    c->n_heads * qs, c->q_lora);
        } else if (w->q_proj) {
            op_gemv(eng, w->q_proj, eng->buf_norm, q,
                    c->n_heads * qs, c->hidden);
        } else {
            WISP_ERR_SET(err, WISP_ERR_MODEL,
                         "layer %d: no query projection weights", layer);
            return WISP_ERR_MODEL;
        }
        op_rope(eng, q, c->n_heads, qs, c->qk_nope, c->qk_rope, pos);

        /* kv_a = [c_kv | k_rope]; norm c_kv; rope k_rope */
        float* kv_a = eng->buf_attn_a;
        op_gemv(eng, w->kv_a_proj, eng->buf_norm, kv_a, k_dim, c->hidden);
        if (w->kv_a_norm)
            op_rmsnorm(eng, kv_a, w->kv_a_norm, kv_a, c->kv_lora);
        op_rope(eng, kv_a + c->kv_lora, 1, c->qk_rope, 0, c->qk_rope, pos);

        /* True MLA compressed cache: one entry = [c_kv | k_rope] */
        op_kv_append(eng, kv_k_layer(kv, layer), NULL, kv_a, NULL,
                     pos, 1, k_dim, 0);

        /* Absorbed attention */
        float* q_eff = eng->buf_attn_c;
        DISPATCH(eng,
                 wisp_gpu_mla_absorb_q(w->kv_b_proj, q, q_eff, c->n_heads,
                                       c->qk_nope, c->qk_rope, c->v_head_dim,
                                       c->kv_lora, eng->compute_stream),
                 cpu_mla_absorb_q(w->kv_b_proj, q, q_eff, c->n_heads,
                                  c->qk_nope, c->qk_rope, c->v_head_dim,
                                  c->kv_lora));

        float* attn_c = eng->buf_attn_b;   /* reuse: q consumed by absorb */
        op_attention(eng, q_eff, kv_k_layer(kv, layer),
                     kv_k_layer(kv, layer), attn_c, pos + 1,
                     c->n_heads, 1, k_dim, c->kv_lora, scale);

        float* out_v = eng->buf_attn_a;    /* reuse: kv_a consumed         */
        DISPATCH(eng,
                 wisp_gpu_mla_out(w->kv_b_proj, attn_c, out_v, c->n_heads,
                                  c->qk_nope, c->v_head_dim, c->kv_lora,
                                  eng->compute_stream),
                 cpu_mla_out(w->kv_b_proj, attn_c, out_v, c->n_heads,
                             c->qk_nope, c->v_head_dim, c->kv_lora));

        op_gemv(eng, w->o_proj, out_v, eng->buf_attn_out,
                c->hidden, c->n_heads * c->v_head_dim);
    } else {
        /* GQA / MHA */
        int hd = c->head_dim;
        float scale = 1.0f / sqrtf((float)hd);
        float* q = eng->buf_attn_a;
        float* k = eng->buf_attn_b;
        float* v = eng->buf_attn_c;
        op_gemv(eng, w->q_proj, eng->buf_norm, q, c->n_heads * hd, c->hidden);
        op_gemv(eng, w->k_proj, eng->buf_norm, k, c->n_kv_heads * hd, c->hidden);
        op_gemv(eng, w->v_proj, eng->buf_norm, v, c->n_kv_heads * hd, c->hidden);
        op_rope(eng, q, c->n_heads, hd, 0, hd, pos);
        op_rope(eng, k, c->n_kv_heads, hd, 0, hd, pos);

        op_kv_append(eng, kv_k_layer(kv, layer), kv_v_layer(kv, layer),
                     k, v, pos, c->n_kv_heads, hd, hd);

        float* attn = eng->buf_attn_b;     /* reuse: k appended            */
        op_attention(eng, q, kv_k_layer(kv, layer), kv_v_layer(kv, layer),
                     attn, pos + 1, c->n_heads, c->n_kv_heads, hd, hd, scale);

        op_gemv(eng, w->o_proj, attn, eng->buf_attn_out,
                c->hidden, c->n_heads * hd);
    }
    return WISP_OK;
}

/* Run one routed expert's FFN on the GPU: dequant int4 -> fp16, then
 * gate/up/down gemvs, accumulating weight * result into buf_ffn. */
#ifndef WISP_NO_CUDA
static WispError gpu_expert_ffn(WispEngine* eng, int layer, void* blob,
                                float weight, WispErrCtx* err) {
    WispExpertMeta* m = &eng->expert_meta[layer];
    const uint8_t* base = (const uint8_t*)blob;
    wisp_half* dq[3] = { eng->buf_dq_gate, eng->buf_dq_up, eng->buf_dq_down };
    for (int i = 0; i < 3; i++) {
        WISP_CHECK_CUDA(
            launch_dequant_expert(base + m->packed_off[i],
                                  (const wisp_half*)(base + m->scales_off[i]),
                                  (const wisp_half*)(base + m->zeros_off[i]),
                                  dq[i],
                                  (int)(m->rows[i] * m->cols[i]),
                                  (int)m->group_size,
                                  eng->compute_stream),
            err);
    }
    int inter = (int)m->rows[0];
    op_swiglu_ffn(eng, eng->buf_dq_gate, eng->buf_dq_up, eng->buf_norm,
                  eng->buf_h, inter, (int)m->cols[0]);
    op_gemv(eng, eng->buf_dq_down, eng->buf_h, eng->buf_attn_a,
            (int)m->rows[2], (int)m->cols[2]);
    op_scale_accum(eng, eng->buf_ffn, eng->buf_attn_a, weight,
                   (int)m->rows[2]);
    return WISP_OK;
}
#endif

/* CPU fused-int4 expert FFN into a HOST accumulator. */
static WispError cpu_expert_ffn(WispEngine* eng, int layer, void* blob,
                                const float* x_norm_h, float* ffn_h,
                                float weight, WispErrCtx* err) {
    WispExpertMeta* m = &eng->expert_meta[layer];
    const uint8_t* base = (const uint8_t*)blob;
    int inter = (int)m->rows[0];

    cpu_gemv_int4(base + m->packed_off[0],
                  (const uint16_t*)(base + m->scales_off[0]),
                  (const uint16_t*)(base + m->zeros_off[0]),
                  x_norm_h, eng->hs_gate, inter, (int)m->cols[0],
                  (int)m->group_size);
    cpu_gemv_int4(base + m->packed_off[1],
                  (const uint16_t*)(base + m->scales_off[1]),
                  (const uint16_t*)(base + m->zeros_off[1]),
                  x_norm_h, eng->hs_up, inter, (int)m->cols[1],
                  (int)m->group_size);
    cpu_swiglu(eng->hs_gate, eng->hs_up, eng->hs_h, inter);
    cpu_gemv_int4(base + m->packed_off[2],
                  (const uint16_t*)(base + m->scales_off[2]),
                  (const uint16_t*)(base + m->zeros_off[2]),
                  eng->hs_h, eng->hs_y, (int)m->rows[2], (int)m->cols[2],
                  (int)m->group_size);
    cpu_scale_accum(ffn_h, eng->hs_y, weight, (int)m->rows[2]);
    (void)err;
    return WISP_OK;
}

static WispError run_moe(WispEngine* eng, int layer, WispErrCtx* err) {
    WispModelConfig* c = &eng->cfg;
    WispLayerWeights* w = &eng->layers[layer];

    /* Router — softmax + top-k + renormalize. Result must land on the host
     * because the host drives expert fetches. */
    int* idx = eng->host_topk_idx;
    float* wts = eng->host_topk_w;
#ifndef WISP_NO_CUDA
    if (eng->use_gpu) {
        wisp_gpu_router_topk(w->router, w->router_bias, eng->buf_norm,
                             eng->buf_router_logits, c->n_experts, c->hidden,
                             c->top_k, idx, wts, eng->compute_stream);
        cudaStreamSynchronize(eng->compute_stream);
    } else
#endif
    {
        cpu_router_topk(w->router, w->router_bias, eng->buf_norm,
                        eng->buf_router_logits, c->n_experts, c->hidden,
                        c->top_k, idx, wts);
    }

    /* Zero the accumulator(s) */
#ifndef WISP_NO_CUDA
    if (eng->use_gpu)
        cudaMemsetAsync(eng->buf_ffn, 0, (size_t)c->hidden * 4,
                        eng->compute_stream);
    else
#endif
        memset(eng->buf_ffn, 0, (size_t)c->hidden * 4);

    /* Shared experts run dense-resident, always */
    if (w->shared_gate && w->shared_up && w->shared_down) {
        int si = w->shared_inter;
        op_swiglu_ffn(eng, w->shared_gate, w->shared_up, eng->buf_norm,
                      eng->buf_h, si, c->hidden);
        op_gemv(eng, w->shared_down, eng->buf_h, eng->buf_attn_a,
                c->hidden, si);
        op_scale_accum(eng, eng->buf_ffn, eng->buf_attn_a, 1.0f, c->hidden);
    }

    /* Routed experts */
    int hybrid = eng->use_gpu && !eng->experts_on_gpu;
    if (hybrid || !eng->use_gpu) {
        const float* xh;
        float* fh;
        if (hybrid) {
            eng_sync(eng);
            if (!eng_d2h(eng, eng->hs_x, eng->buf_norm,
                         (size_t)c->hidden * 4)) {
                WISP_ERR_SET(err, WISP_ERR_CUDA, "hybrid x_norm D2H failed");
                return WISP_ERR_CUDA;
            }
            memset(eng->hs_ffn, 0, (size_t)c->hidden * 4);
            xh = eng->hs_x;
            fh = eng->hs_ffn;
        } else {
            xh = eng->buf_norm;
            fh = eng->buf_ffn;
        }
        for (int k = 0; k < c->top_k; k++) {
            if (idx[k] < 0) continue;
            void* blob = wisp_expert_fetch(eng, (uint32_t)layer,
                                           (uint32_t)idx[k], err);
            if (!blob) {
                if (err->code == WISP_ERR_IO) continue;  /* skip, log later */
                return err->code;
            }
            WispError e = cpu_expert_ffn(eng, layer, blob, xh,
                                         fh, wts[k], err);
            if (e != WISP_OK) return e;
        }
        if (hybrid) {
            /* Merge host expert results into the device accumulator */
            if (!eng_h2d(eng, eng->buf_attn_a, eng->hs_ffn,
                         (size_t)c->hidden * 4)) {
                WISP_ERR_SET(err, WISP_ERR_CUDA, "hybrid ffn H2D failed");
                return WISP_ERR_CUDA;
            }
            op_scale_accum(eng, eng->buf_ffn, eng->buf_attn_a, 1.0f,
                           c->hidden);
        }
    }
#ifndef WISP_NO_CUDA
    else {
        /* Full-GPU path: fetch all blobs first so the transfer stream can
         * batch, then sync it once, then compute. */
        void* blobs[64];
        int kept[64];
        int nb = 0;
        for (int k = 0; k < c->top_k && k < 64; k++) {
            if (idx[k] < 0) continue;
            void* b = wisp_expert_fetch(eng, (uint32_t)layer,
                                        (uint32_t)idx[k], err);
            if (!b) {
                if (err->code == WISP_ERR_IO) continue;
                return err->code;
            }
            blobs[nb] = b;
            kept[nb] = k;
            nb++;
        }
        cudaStreamSynchronize(eng->transfer_stream);
        for (int i = 0; i < nb; i++) {
            WispError e = gpu_expert_ffn(eng, layer, blobs[i],
                                         wts[kept[i]], err);
            if (e != WISP_OK) return e;
        }
    }
#endif
    return WISP_OK;
}

static WispError run_dense_mlp(WispEngine* eng, int layer) {
    /* Early layers in DeepSeek/GLM have a plain dense MLP (stored under
     * the shared.* canonical names). */
    WispModelConfig* c = &eng->cfg;
    WispLayerWeights* w = &eng->layers[layer];
    int si = w->shared_inter;
    op_swiglu_ffn(eng, w->shared_gate, w->shared_up, eng->buf_norm,
                  eng->buf_h, si, c->hidden);
    op_gemv(eng, w->shared_down, eng->buf_h, eng->buf_ffn, c->hidden, si);
    return WISP_OK;
}

/* One full decoder step for one token. Logits (fp32, host) optional. */
static WispError decode_step(WispEngine* eng, WispKVCache* kv, int token,
                             float* out_logits, WispErrCtx* err) {
    WispModelConfig* c = &eng->cfg;
    if (token < 0 || token >= c->vocab) {
        WISP_ERR_SET(err, WISP_ERR_INVALID_ARG,
                     "token id %d out of range [0, %d)", token, c->vocab);
        return WISP_ERR_INVALID_ARG;
    }
    if (kv->len >= kv->max_seq) {
        WISP_ERR_SET(err, WISP_ERR_INVALID_ARG,
                     "KV cache full (%d tokens)", kv->max_seq);
        return WISP_ERR_INVALID_ARG;
    }

    op_embed(eng, token, eng->buf_x);

    for (int layer = 0; layer < c->num_layers; layer++) {
        WispLayerWeights* w = &eng->layers[layer];

        /* Attention block */
        op_rmsnorm(eng, eng->buf_x, w->input_norm, eng->buf_norm, c->hidden);
        WispError e = run_attention(eng, layer, kv, err);
        if (e != WISP_OK) return e;
        op_residual(eng, eng->buf_x, eng->buf_attn_out, c->hidden);

        /* FFN block */
        op_rmsnorm(eng, eng->buf_x, w->post_norm, eng->buf_norm, c->hidden);
        if (w->is_dense_mlp) {
            e = run_dense_mlp(eng, layer);
        } else {
            e = run_moe(eng, layer, err);
        }
        if (e != WISP_OK) return e;
        op_residual(eng, eng->buf_x, eng->buf_ffn, c->hidden);
    }

    kv->len++;

    if (out_logits) {
        op_rmsnorm(eng, eng->buf_x, eng->final_norm, eng->buf_norm,
                   c->hidden);
        op_gemv(eng, eng->lm_head, eng->buf_norm, eng->buf_logits,
                c->vocab, c->hidden);
        eng_sync(eng);
        if (!eng_d2h(eng, out_logits, eng->buf_logits,
                     (size_t)c->vocab * 4)) {
            WISP_ERR_SET(err, WISP_ERR_CUDA, "logits D2H failed");
            return WISP_ERR_CUDA;
        }
    }

    /* tok/s ring */
    wisp_mutex_lock(&eng->stats_mutex);
    eng->token_times_ns[eng->token_time_head] = wisp_now_ns();
    eng->token_time_head = (eng->token_time_head + 1) % 32;
    if (eng->token_time_count < 32) eng->token_time_count++;
    wisp_mutex_unlock(&eng->stats_mutex);
    return WISP_OK;
}

/* ======================================================================= *
 * 8. Public API
 * ======================================================================= */

static WispError load_manifest(WispEngine* eng, WispErrCtx* err) {
    char path[1200];
    snprintf(path, sizeof(path), "%s/manifest.json", eng->model_path);
    char* json = read_entire_file(path, NULL);
    if (!json) {
        WISP_ERR_SET(err, WISP_ERR_MODEL, "cannot read %s", path);
        return WISP_ERR_MODEL;
    }
    WispModelConfig* c = &eng->cfg;
    c->num_layers   = (int)json_int(json, "num_layers", 0);
    c->n_experts    = (int)json_int(json, "num_experts_per_layer", 0);
    c->n_shared_experts = (int)json_int(json, "num_shared_experts", 1);
    c->top_k        = (int)json_int(json, "top_k_routing", 8);
    c->hidden       = (int)json_int(json, "hidden_size", 0);
    c->vocab        = (int)json_int(json, "vocab_size", 0);
    c->moe_inter    = (int)json_int(json, "moe_intermediate_size", 2048);
    c->shared_inter = (int)json_int(json, "intermediate_size",
                                    c->moe_inter * c->n_shared_experts);
    c->n_heads      = (int)json_int(json, "num_attention_heads", 128);
    c->n_kv_heads   = (int)json_int(json, "num_kv_heads", c->n_heads);
    c->q_lora       = (int)json_int(json, "q_lora_rank", 1536);
    c->kv_lora      = (int)json_int(json, "kv_lora_rank", 512);
    c->qk_nope      = (int)json_int(json, "qk_nope_head_dim", 128);
    c->qk_rope      = (int)json_int(json, "qk_rope_head_dim", 64);
    c->v_head_dim   = (int)json_int(json, "v_head_dim", 128);
    c->rope_theta   = (float)json_double(json, "rope_theta", 10000.0);
    c->rms_eps      = (float)json_double(json, "rms_norm_eps", 1e-6);
    c->group_size   = (int)json_int(json, "group_size", 64);
    c->expert_size_bytes =
        (size_t)json_int(json, "expert_size_bytes", 18350080);
    c->max_pos      = json_int(json, "max_position_embeddings", 131072);

    char attn[16] = {0};
    json_string(json, "attention_type", attn, sizeof(attn));
    if (strcmp(attn, "GQA") == 0) c->attn_type = WISP_ATTN_GQA;
    else if (strcmp(attn, "MHA") == 0) c->attn_type = WISP_ATTN_MHA;
    /* TODO: Replace with full KDA implementation once the Kimi K3
     * technical report publishes July 27, 2026. KDA = hybrid linear
     * attention replacing quadratic attention in a subset of layers
     * (6.3x faster decoding at 1M context). GQA placeholder for now. */
    else if (strcmp(attn, "KDA") == 0) c->attn_type = WISP_ATTN_GQA;
    else c->attn_type = WISP_ATTN_MLA;
    if (c->attn_type != WISP_ATTN_MLA && c->head_dim == 0)
        c->head_dim = c->hidden / (c->n_heads > 0 ? c->n_heads : 1);
    free(json);

    if (c->num_layers <= 0 || c->hidden <= 0 || c->vocab <= 0 ||
        c->n_experts < 0) {
        WISP_ERR_SET(err, WISP_ERR_MODEL,
                     "manifest invalid: layers=%d hidden=%d vocab=%d",
                     c->num_layers, c->hidden, c->vocab);
        return WISP_ERR_MODEL;
    }
    return WISP_OK;
}

/* Load one tensor from the dense safetensors file to engine memory.
 * Returns NULL quietly when the tensor doesn't exist (optional weights);
 * sets *rows to shape[0] when requested. */
static wisp_half* load_tensor(WispEngine* eng, StFile* st, const char* name,
                              int* rows, WispErrCtx* err) {
    uint64_t off, nbytes;
    int64_t shape[8];
    int ndim = 0;
    if (!st_find(st, name, &off, &nbytes, shape, &ndim)) return NULL;

    void* host = malloc(nbytes);
    if (!host) {
        WISP_ERR_SET(err, WISP_ERR_OOM, "staging %llu bytes for %s",
                     (unsigned long long)nbytes, name);
        return NULL;
    }
#ifdef _WIN32
    _fseeki64(st->f, (long long)(st->data_start + off), SEEK_SET);
#else
    fseeko(st->f, (off_t)(st->data_start + off), SEEK_SET);
#endif
    if (fread(host, 1, nbytes, st->f) != nbytes) {
        free(host);
        WISP_ERR_SET(err, WISP_ERR_IO, "short read for tensor %s", name);
        return NULL;
    }
    wisp_half* dev = (wisp_half*)eng_alloc(eng, nbytes, err);
    if (!dev) { free(host); return NULL; }
    if (!eng_h2d(eng, dev, host, nbytes)) {
        free(host);
        eng_free(eng, dev);
        WISP_ERR_SET(err, WISP_ERR_CUDA, "H2D failed for tensor %s", name);
        return NULL;
    }
    free(host);
    if (rows && ndim > 0) *rows = (int)shape[0];
    return dev;
}

static WispError load_dense(WispEngine* eng, WispErrCtx* err) {
    char path[1200];
    snprintf(path, sizeof(path), "%s/dense/model_dense.safetensors",
             eng->model_path);
    StFile st;
    if (!st_open(&st, path)) {
        WISP_ERR_SET(err, WISP_ERR_MODEL,
                     "cannot open dense weights: %s", path);
        return WISP_ERR_MODEL;
    }

    eng->embed_tokens = load_tensor(eng, &st, "embed_tokens", NULL, err);
    eng->final_norm   = load_tensor(eng, &st, "final_norm", NULL, err);
    eng->lm_head      = load_tensor(eng, &st, "lm_head", NULL, err);
    if (!eng->embed_tokens || !eng->final_norm || !eng->lm_head) {
        st_close(&st);
        if (err->code == WISP_OK)
            WISP_ERR_SET(err, WISP_ERR_MODEL,
                         "dense file missing embed_tokens/final_norm/lm_head");
        return WISP_ERR_MODEL;
    }

    eng->layers = (WispLayerWeights*)calloc(
        (size_t)eng->cfg.num_layers, sizeof(WispLayerWeights));
    WISP_CHECK_NULL(eng->layers, err, "layer weight table");

    char name[256];
    for (int i = 0; i < eng->cfg.num_layers; i++) {
        WispLayerWeights* w = &eng->layers[i];
        #define LT(field, fmt) do {                                        \
            snprintf(name, sizeof(name), fmt, i);                          \
            w->field = load_tensor(eng, &st, name, NULL, err);             \
            if (err->code != WISP_OK) { st_close(&st); return err->code; } \
        } while (0)
        LT(input_norm,  "layers.%d.input_norm");
        LT(post_norm,   "layers.%d.post_norm");
        LT(router,      "layers.%d.router");
        LT(router_bias, "layers.%d.router_bias");
        LT(q_proj,      "layers.%d.attn.q_proj");
        LT(k_proj,      "layers.%d.attn.k_proj");
        LT(v_proj,      "layers.%d.attn.v_proj");
        LT(q_a_proj,    "layers.%d.attn.q_a_proj");
        LT(q_a_norm,    "layers.%d.attn.q_a_norm");
        LT(q_b_proj,    "layers.%d.attn.q_b_proj");
        LT(kv_a_proj,   "layers.%d.attn.kv_a_proj");
        LT(kv_a_norm,   "layers.%d.attn.kv_a_norm");
        LT(kv_b_proj,   "layers.%d.attn.kv_b_proj");
        LT(o_proj,      "layers.%d.attn.o_proj");
        #undef LT

        snprintf(name, sizeof(name), "layers.%d.shared.gate", i);
        int srows = 0;
        w->shared_gate = load_tensor(eng, &st, name, &srows, err);
        snprintf(name, sizeof(name), "layers.%d.shared.up", i);
        w->shared_up = load_tensor(eng, &st, name, NULL, err);
        snprintf(name, sizeof(name), "layers.%d.shared.down", i);
        w->shared_down = load_tensor(eng, &st, name, NULL, err);
        if (err->code != WISP_OK) { st_close(&st); return err->code; }
        w->shared_inter = srows > 0 ? srows : eng->cfg.shared_inter;
        w->is_dense_mlp = (w->router == NULL);

        if (!w->input_norm || !w->post_norm || !w->o_proj) {
            st_close(&st);
            WISP_ERR_SET(err, WISP_ERR_MODEL,
                         "layer %d: missing required dense tensors", i);
            return WISP_ERR_MODEL;
        }
        if (w->is_dense_mlp && !w->shared_gate) {
            st_close(&st);
            WISP_ERR_SET(err, WISP_ERR_MODEL,
                         "layer %d: no router and no dense MLP weights", i);
            return WISP_ERR_MODEL;
        }
    }
    st_close(&st);
    return WISP_OK;
}

static WispError alloc_buffers(WispEngine* eng, WispErrCtx* err) {
    WispModelConfig* c = &eng->cfg;

    /* One conservative size for the three projection scratch buffers */
    int max_proj = c->hidden;
    int cand[6];
    cand[0] = c->n_heads * (c->qk_nope + c->qk_rope);
    cand[1] = c->n_heads * (c->kv_lora + c->qk_rope);
    cand[2] = c->n_heads * c->v_head_dim;
    cand[3] = c->n_heads * c->kv_lora;
    cand[4] = c->q_lora;
    cand[5] = (c->attn_type != WISP_ATTN_MLA)
        ? c->n_heads * c->head_dim : 0;
    for (int i = 0; i < 6; i++) if (cand[i] > max_proj) max_proj = cand[i];

    int max_inter = c->moe_inter;
    for (int i = 0; i < c->num_layers; i++)
        if (eng->layers[i].shared_inter > max_inter)
            max_inter = eng->layers[i].shared_inter;

    size_t F = sizeof(float);
    #define AL(buf, n) do {                                                \
        eng->buf = (float*)eng_alloc(eng, (size_t)(n) * F, err);           \
        if (!eng->buf) return WISP_ERR_OOM;                                \
    } while (0)
    AL(buf_x, c->hidden);
    AL(buf_norm, c->hidden);
    AL(buf_attn_a, max_proj);
    AL(buf_attn_b, max_proj);
    AL(buf_attn_c, max_proj);
    AL(buf_attn_out, c->hidden);
    AL(buf_gate, max_inter);
    AL(buf_up, max_inter);
    AL(buf_h, max_inter);
    AL(buf_ffn, c->hidden);
    AL(buf_logits, c->vocab);
    AL(buf_router_logits, c->n_experts > 0 ? c->n_experts : 1);
    #undef AL

    /* Attention score scratch: worst case n_heads x max_pos, bounded to
     * 32K positions (the kv alloc enforces the real max_seq anyway). */
    int64_t score_pos = c->max_pos < 32768 ? c->max_pos : 32768;
    eng->buf_scores = (float*)eng_alloc(
        eng, (size_t)c->n_heads * (size_t)score_pos * F, err);
    if (!eng->buf_scores) return WISP_ERR_OOM;

    /* Dequant scratch (largest expert matrix, fp16) */
    if (eng->experts_on_gpu) {
        size_t mat = (size_t)max_inter * (size_t)c->hidden * 2;
        eng->buf_dq_gate = (wisp_half*)eng_alloc(eng, mat, err);
        eng->buf_dq_up   = (wisp_half*)eng_alloc(eng, mat, err);
        eng->buf_dq_down = (wisp_half*)eng_alloc(eng, mat, err);
        if (!eng->buf_dq_gate || !eng->buf_dq_up || !eng->buf_dq_down)
            return WISP_ERR_OOM;
    }

    /* Host-side outputs + CPU expert scratch */
#ifndef WISP_NO_CUDA
    if (eng->use_gpu) {
        WISP_CHECK_CUDA(cudaHostAlloc((void**)&eng->host_logits,
                                      (size_t)c->vocab * F,
                                      cudaHostAllocDefault), err);
        WISP_CHECK_CUDA(cudaHostAlloc((void**)&eng->host_topk_idx,
                                      (size_t)(c->top_k > 0 ? c->top_k : 1)
                                      * sizeof(int),
                                      cudaHostAllocDefault), err);
        WISP_CHECK_CUDA(cudaHostAlloc((void**)&eng->host_topk_w,
                                      (size_t)(c->top_k > 0 ? c->top_k : 1)
                                      * F, cudaHostAllocDefault), err);
    } else
#endif
    {
        eng->host_logits = (float*)calloc((size_t)c->vocab, F);
        eng->host_topk_idx = (int*)calloc(
            (size_t)(c->top_k > 0 ? c->top_k : 1), sizeof(int));
        eng->host_topk_w = (float*)calloc(
            (size_t)(c->top_k > 0 ? c->top_k : 1), F);
        WISP_CHECK_NULL(eng->host_logits, err, "host logits");
        WISP_CHECK_NULL(eng->host_topk_idx, err, "host topk idx");
        WISP_CHECK_NULL(eng->host_topk_w, err, "host topk weights");
    }

    eng->hs_x    = (float*)calloc((size_t)c->hidden, F);
    eng->hs_ffn  = (float*)calloc((size_t)c->hidden, F);
    eng->hs_gate = (float*)calloc((size_t)max_inter, F);
    eng->hs_up   = (float*)calloc((size_t)max_inter, F);
    eng->hs_h    = (float*)calloc((size_t)max_inter, F);
    eng->hs_y    = (float*)calloc((size_t)c->hidden, F);
    WISP_CHECK_NULL(eng->hs_x, err, "host scratch x");
    WISP_CHECK_NULL(eng->hs_ffn, err, "host scratch ffn");
    WISP_CHECK_NULL(eng->hs_gate, err, "host scratch gate");
    WISP_CHECK_NULL(eng->hs_up, err, "host scratch up");
    WISP_CHECK_NULL(eng->hs_h, err, "host scratch h");
    WISP_CHECK_NULL(eng->hs_y, err, "host scratch y");
    return WISP_OK;
}

WispEngine* wisp_engine_create(const char* model_path,
                               size_t vram_expert_budget_bytes,
                               size_t ram_expert_budget_bytes,
                               const int* gpu_indices, int gpu_count,
                               int omp_threads,
                               WispErrCtx* err) {
    if (!model_path || !err) return NULL;
    err->code = WISP_OK;

    WispEngine* eng = (WispEngine*)calloc(1, sizeof(WispEngine));
    if (!eng) {
        WISP_ERR_SET(err, WISP_ERR_OOM, "engine alloc failed");
        return NULL;
    }
    snprintf(eng->model_path, sizeof(eng->model_path), "%s", model_path);
    wisp_mutex_init(&eng->stats_mutex);

    eng->omp_threads = omp_threads > 0 ? omp_threads : 1;
#ifdef _OPENMP
    omp_set_num_threads(eng->omp_threads);
#endif

    eng->gpu_count = gpu_count > 8 ? 8 : (gpu_count < 0 ? 0 : gpu_count);
    for (int i = 0; i < eng->gpu_count; i++)
        eng->gpu_indices[i] = gpu_indices[i];

#ifndef WISP_NO_CUDA
    if (eng->gpu_count > 0 &&
        cudaSetDevice(eng->gpu_indices[0]) == cudaSuccess) {
        eng->use_gpu = 1;
    }
#endif

    if (load_manifest(eng, err) != WISP_OK) goto fail;

    /* Staging size: real files carry scales/zeros/header on top of the
     * nominal packed size — 1.25x + 4KB covers group_size >= 32. */
    eng->max_expert_bytes =
        eng->cfg.expert_size_bytes + eng->cfg.expert_size_bytes / 4 + 4096;

    eng->experts_on_gpu =
        eng->use_gpu && vram_expert_budget_bytes >= eng->max_expert_bytes;

    /* Tier caches */
    eng->vram_cache = (LRUCache*)calloc(1, sizeof(LRUCache));
    eng->ram_cache = (LRUCache*)calloc(1, sizeof(LRUCache));
    eng->vram_budget = (VramBudget*)calloc(1, sizeof(VramBudget));
    if (!eng->vram_cache || !eng->ram_cache || !eng->vram_budget) {
        WISP_ERR_SET(err, WISP_ERR_OOM, "cache structs alloc failed");
        goto fail;
    }
    if (lru_init(eng->vram_cache,
                 eng->experts_on_gpu ? vram_expert_budget_bytes : 0,
                 TIER_VRAM, err) != WISP_OK) goto fail;
    if (lru_init(eng->ram_cache, ram_expert_budget_bytes,
                 TIER_RAM, err) != WISP_OK) goto fail;
    vram_budget_init(eng->vram_budget,
                     eng->experts_on_gpu ? vram_expert_budget_bytes : 0);

    eng->expert_meta = (WispExpertMeta*)calloc(
        (size_t)eng->cfg.num_layers, sizeof(WispExpertMeta));
    if (!eng->expert_meta) {
        WISP_ERR_SET(err, WISP_ERR_OOM, "expert meta alloc failed");
        goto fail;
    }

    /* Expert access log: sized for ~16 tokens of lookups so a runtime
     * that drains every 10 tokens never loses an entry. Non-fatal if it
     * cannot be allocated — the engine just stops reporting usage. */
    eng->access_log_cap = eng->cfg.top_k * eng->cfg.num_layers * 16;
    if (eng->access_log_cap < 4096) eng->access_log_cap = 4096;
    if (eng->access_log_cap > 1 << 20) eng->access_log_cap = 1 << 20;
    eng->access_log = (uint32_t*)calloc((size_t)eng->access_log_cap,
                                        sizeof(uint32_t));
    if (!eng->access_log) eng->access_log_cap = 0;

#ifndef WISP_NO_CUDA
    if (eng->use_gpu) {
        if (cudaStreamCreate(&eng->compute_stream) != cudaSuccess ||
            cudaStreamCreate(&eng->transfer_stream) != cudaSuccess) {
            WISP_ERR_SET(err, WISP_ERR_CUDA, "stream creation failed");
            goto fail;
        }
        eng->pinned_pool = (PinnedPool*)calloc(1, sizeof(PinnedPool));
        if (!eng->pinned_pool ||
            pinned_pool_init(eng->pinned_pool, eng->max_expert_bytes, 4,
                             err) != WISP_OK) {
            free(eng->pinned_pool);
            eng->pinned_pool = NULL;   /* fall back to malloc staging */
            err->code = WISP_OK;
        }
        eng->double_buf = (DoubleBuffer*)calloc(1, sizeof(DoubleBuffer));
        if (eng->double_buf &&
            double_buffer_init(eng->double_buf,
                               eng->max_expert_bytes *
                               (size_t)(eng->cfg.top_k > 0
                                        ? eng->cfg.top_k : 1),
                               eng->compute_stream, eng->transfer_stream,
                               err) != WISP_OK) {
            free(eng->double_buf);
            eng->double_buf = NULL;
            err->code = WISP_OK;
        }
    }
#endif

    if (load_dense(eng, err) != WISP_OK) goto fail;
    if (alloc_buffers(eng, err) != WISP_OK) goto fail;

    /* Scratch ring for churn-free serving of cool experts */
    if (eng->experts_on_gpu) {
        eng->scratch_slots = eng->cfg.top_k + 2;
        if (eng->scratch_slots > 16) eng->scratch_slots = 16;
        for (int i = 0; i < eng->scratch_slots; i++) {
            eng->scratch_ring[i] =
                eng_alloc(eng, eng->max_expert_bytes, err);
            if (!eng->scratch_ring[i]) goto fail;
        }
    }

    eng->prefetch = prefetch_start(eng);

    return eng;

fail:
    wisp_engine_destroy(eng);
    return NULL;
}

void wisp_engine_destroy(WispEngine* eng) {
    if (!eng) return;
    prefetch_stop(eng->prefetch);

    if (eng->vram_cache) {
        /* Free VRAM payloads through the budget tracker */
        LRUNode* victim;
        while ((victim = lru_evict(eng->vram_cache)) != NULL) {
            if (eng->vram_budget)
                wisp_vram_free(eng->vram_budget, victim->data_ptr,
                               victim->size_bytes);
            lru_node_free(victim);
        }
        lru_destroy(eng->vram_cache);
        free(eng->vram_cache);
    }
    if (eng->ram_cache) {
        lru_clear(eng->ram_cache, free_ram_payload, NULL);
        lru_destroy(eng->ram_cache);
        free(eng->ram_cache);
    }
    if (eng->vram_budget) {
        vram_budget_destroy(eng->vram_budget);
        free(eng->vram_budget);
    }
    if (eng->double_buf) {
        double_buffer_destroy(eng->double_buf);
        free(eng->double_buf);
    }
    if (eng->pinned_pool) {
        pinned_pool_destroy(eng->pinned_pool);
        free(eng->pinned_pool);
    }

    eng_free(eng, eng->embed_tokens);
    eng_free(eng, eng->final_norm);
    eng_free(eng, eng->lm_head);
    if (eng->layers) {
        for (int i = 0; i < eng->cfg.num_layers; i++) {
            WispLayerWeights* w = &eng->layers[i];
            eng_free(eng, w->input_norm);  eng_free(eng, w->post_norm);
            eng_free(eng, w->router);      eng_free(eng, w->router_bias);
            eng_free(eng, w->shared_gate); eng_free(eng, w->shared_up);
            eng_free(eng, w->shared_down);
            eng_free(eng, w->q_proj);      eng_free(eng, w->k_proj);
            eng_free(eng, w->v_proj);      eng_free(eng, w->q_a_proj);
            eng_free(eng, w->q_a_norm);    eng_free(eng, w->q_b_proj);
            eng_free(eng, w->kv_a_proj);   eng_free(eng, w->kv_a_norm);
            eng_free(eng, w->kv_b_proj);   eng_free(eng, w->o_proj);
        }
        free(eng->layers);
    }
    free(eng->expert_meta);
    free(eng->access_log);

    eng_free(eng, eng->buf_x);        eng_free(eng, eng->buf_norm);
    eng_free(eng, eng->buf_attn_a);   eng_free(eng, eng->buf_attn_b);
    eng_free(eng, eng->buf_attn_c);   eng_free(eng, eng->buf_attn_out);
    eng_free(eng, eng->buf_scores);   eng_free(eng, eng->buf_gate);
    eng_free(eng, eng->buf_up);       eng_free(eng, eng->buf_h);
    eng_free(eng, eng->buf_ffn);      eng_free(eng, eng->buf_logits);
    eng_free(eng, eng->buf_dq_gate);  eng_free(eng, eng->buf_dq_up);
    eng_free(eng, eng->buf_dq_down);  eng_free(eng, eng->buf_router_logits);
    for (int i = 0; i < eng->scratch_slots; i++)
        eng_free(eng, eng->scratch_ring[i]);

#ifndef WISP_NO_CUDA
    if (eng->use_gpu) {
        if (eng->host_logits) cudaFreeHost(eng->host_logits);
        if (eng->host_topk_idx) cudaFreeHost(eng->host_topk_idx);
        if (eng->host_topk_w) cudaFreeHost(eng->host_topk_w);
        if (eng->compute_stream) cudaStreamDestroy(eng->compute_stream);
        if (eng->transfer_stream) cudaStreamDestroy(eng->transfer_stream);
    } else
#endif
    {
        free(eng->host_logits);
        free(eng->host_topk_idx);
        free(eng->host_topk_w);
    }
    free(eng->hs_x);   free(eng->hs_ffn); free(eng->hs_gate);
    free(eng->hs_up);  free(eng->hs_h);   free(eng->hs_y);

    wisp_mutex_destroy(&eng->stats_mutex);
    free(eng);
}

/* --- KV cache ----------------------------------------------------------- */

WispKVCache* wisp_kv_cache_alloc(WispEngine* eng, int max_seq_len,
                                 WispErrCtx* err) {
    if (max_seq_len <= 0) {
        WISP_ERR_SET(err, WISP_ERR_INVALID_ARG,
                     "max_seq_len must be > 0, got %d", max_seq_len);
        return NULL;
    }
    WispModelConfig* c = &eng->cfg;
    WispKVCache* kv = (WispKVCache*)calloc(1, sizeof(WispKVCache));
    if (!kv) {
        WISP_ERR_SET(err, WISP_ERR_OOM, "kv struct alloc failed");
        return NULL;
    }
    kv->max_seq = max_seq_len;

    if (c->attn_type == WISP_ATTN_MLA) {
        kv->kv_heads = 1;
        kv->k_dim = c->kv_lora + c->qk_rope;
        kv->v_dim = 0;   /* V aliases the first kv_lora dims of K */
    } else {
        kv->kv_heads = c->n_kv_heads;
        kv->k_dim = c->head_dim;
        kv->v_dim = c->head_dim;
    }
    kv->k_layer_stride =
        (size_t)max_seq_len * kv->kv_heads * kv->k_dim;
    kv->v_layer_stride =
        (size_t)max_seq_len * kv->kv_heads * kv->v_dim;

    size_t total = ((size_t)c->num_layers *
                    (kv->k_layer_stride + kv->v_layer_stride)) * 2;
    kv->base = (wisp_half*)eng_alloc(eng, total, err);
    if (!kv->base) {
        free(kv);
        return NULL;
    }
    kv->v_base = kv->v_dim > 0
        ? kv->base + (size_t)c->num_layers * kv->k_layer_stride
        : NULL;
    kv->len = 0;
    return kv;
}

void wisp_kv_cache_free(WispEngine* eng, WispKVCache* kv) {
    if (!kv) return;
    eng_free(eng, kv->base);
    free(kv);
}

void wisp_kv_cache_clear(WispEngine* eng, WispKVCache* kv) {
    (void)eng;
    if (kv) kv->len = 0;
}

void wisp_kv_cache_rollback(WispEngine* eng, WispKVCache* kv, int n_tokens) {
    (void)eng;
    if (!kv || n_tokens <= 0) return;
    kv->len = kv->len >= n_tokens ? kv->len - n_tokens : 0;
}

/* --- generation entry points -------------------------------------------- */

WispError wisp_prefill(WispEngine* eng, const int* token_ids, int n_tokens,
                       WispKVCache* kv, float* out_logits, WispErrCtx* err) {
    WISP_CHECK_NULL(eng, err, "prefill: engine");
    WISP_CHECK_NULL(kv, err, "prefill: kv cache");
    if (n_tokens <= 0) {
        WISP_ERR_SET(err, WISP_ERR_INVALID_ARG, "prefill: empty prompt");
        return WISP_ERR_INVALID_ARG;
    }
    for (int i = 0; i < n_tokens; i++) {
        int want_logits = (i == n_tokens - 1) && out_logits;
        WispError e = decode_step(eng, kv, token_ids[i],
                                  want_logits ? out_logits : NULL, err);
        if (e != WISP_OK) return e;
    }
    return WISP_OK;
}

WispError wisp_decode_one(WispEngine* eng, int token_id,
                          WispKVCache* kv, float* out_logits,
                          WispErrCtx* err) {
    WISP_CHECK_NULL(eng, err, "decode_one: engine");
    WISP_CHECK_NULL(kv, err, "decode_one: kv cache");
    return decode_step(eng, kv, token_id, out_logits, err);
}

WispError wisp_verify_tokens(WispEngine* eng, const int* token_ids,
                             int n_tokens, WispKVCache* kv,
                             float* out_logits, WispErrCtx* err) {
    WISP_CHECK_NULL(eng, err, "verify: engine");
    WISP_CHECK_NULL(kv, err, "verify: kv cache");
    WISP_CHECK_NULL(out_logits, err, "verify: output buffer");
    for (int i = 0; i < n_tokens; i++) {
        WispError e = decode_step(eng, kv, token_ids[i],
                                  out_logits + (size_t)i * eng->cfg.vocab,
                                  err);
        if (e != WISP_OK) return e;
    }
    return WISP_OK;
}

/* --- stats --------------------------------------------------------------- */

void wisp_cache_stats(WispEngine* eng, uint64_t* vram_hits,
                      uint64_t* ram_hits, uint64_t* ssd_hits,
                      double* hit_rate) {
    wisp_mutex_lock(&eng->stats_mutex);
    uint64_t v = eng->vram_hits, r = eng->ram_hits, s = eng->ssd_hits;
    wisp_mutex_unlock(&eng->stats_mutex);
    if (vram_hits) *vram_hits = v;
    if (ram_hits) *ram_hits = r;
    if (ssd_hits) *ssd_hits = s;
    uint64_t total = v + r + s;
    if (hit_rate) *hit_rate = total ? (double)(v + r) / (double)total : 0.0;
}

void wisp_cache_clear_all(WispEngine* eng) {
    if (eng->vram_cache) {
        LRUNode* victim;
        while ((victim = lru_evict(eng->vram_cache)) != NULL) {
            wisp_vram_free(eng->vram_budget, victim->data_ptr,
                           victim->size_bytes);
            lru_node_free(victim);
        }
    }
    if (eng->ram_cache) lru_clear(eng->ram_cache, free_ram_payload, NULL);
    wisp_mutex_lock(&eng->stats_mutex);
    eng->vram_hits = eng->ram_hits = eng->ssd_hits = 0;
    wisp_mutex_unlock(&eng->stats_mutex);
}

int wisp_ram_trim(WispEngine* eng, int count) {
    if (!eng || !eng->ram_cache || count <= 0) return 0;
    int freed = 0;
    for (int i = 0; i < count; i++) {
        LRUNode* victim = lru_evict(eng->ram_cache);
        if (!victim) break;
        free(victim->data_ptr);
        lru_node_free(victim);
        freed++;
    }
    return freed;
}

size_t wisp_vram_used(WispEngine* eng) {
    return eng->vram_budget ? wisp_vram_budget_used(eng->vram_budget) : 0;
}

size_t wisp_ram_used(WispEngine* eng) {
    return eng->ram_cache ? (size_t)eng->ram_cache->used_bytes : 0;
}

double wisp_tok_per_sec(WispEngine* eng) {
    wisp_mutex_lock(&eng->stats_mutex);
    int n = eng->token_time_count;
    double rate = 0.0;
    if (n >= 2) {
        int newest = (eng->token_time_head + 31) % 32;
        int oldest = (eng->token_time_head + 32 - n) % 32;
        uint64_t span = eng->token_times_ns[newest]
                      - eng->token_times_ns[oldest];
        if (span > 0) rate = (double)(n - 1) * 1e9 / (double)span;
    }
    wisp_mutex_unlock(&eng->stats_mutex);
    return rate;
}
