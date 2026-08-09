/*
 * wisp_engine.h — master header for the WISP C hot-path engine.
 *
 * Contains, in order:
 *   1. Error codes + error context + check macros (mandatory pattern)
 *   2. Cross-platform threading (wisp_mutex_t / wisp_cond_t) — NEVER use
 *      pthread_* or CRITICAL_SECTION directly in any wisp C file
 *   3. CUDA compatibility shim (WISP_NO_CUDA builds run the same sources)
 *   4. Model config + expert blob format (mirrors wisp/converter/partitioner.py)
 *   5. Engine / KV-cache structs
 *   6. Public engine API (what the pybind11 bindings call)
 *   7. GPU kernel launcher interface (implemented in csrc/cuda/*.cu)
 */

#pragma once

#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

/* Real CUDA headers must be included OUTSIDE any extern "C" block:
 * cuda_fp16.h declares C++ operator overloads (__half/__half2), which
 * cannot legally take C linkage. The WISP_NO_CUDA shim below is plain C
 * and stays inside the block.
 *
 * cuda_fp16.h (and __half itself) is C++-only. Plain-C translation units
 * see wisp_half as uint16_t — raw fp16 bits, identical size/alignment/
 * layout to __half, so pointers are ABI-compatible across the C engine,
 * the C++ bindings, and the CUDA kernels. The C side never does fp16
 * arithmetic directly; it converts via wisp_half_to_float(). */
#ifndef WISP_NO_CUDA
    #include <cuda_runtime.h>
    #ifdef __cplusplus
        #include <cuda_fp16.h>
        typedef __half wisp_half;
    #else
        typedef uint16_t wisp_half;
    #endif
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* ======================================================================= *
 * 1. Error handling — MANDATORY IN ALL C FILES
 * ======================================================================= */

typedef enum {
    WISP_OK               = 0,
    WISP_ERR_OOM          = 1,   /* Out of memory (RAM or VRAM)             */
    WISP_ERR_IO           = 2,   /* SSD read failure                        */
    WISP_ERR_CUDA         = 3,   /* CUDA API error                          */
    WISP_ERR_INVALID_ARG  = 4,   /* Bad function argument                   */
    WISP_ERR_EXPERT_MISS  = 5,   /* Expert not found in any tier            */
    WISP_ERR_MODEL        = 6,   /* Model file corrupt or missing           */
    WISP_ERR_TIMEOUT      = 7,   /* Transfer timeout                        */
} WispError;

/* Error context struct — always populated on error */
typedef struct {
    WispError   code;
    char        message[512];
    const char* file;
    int         line;
} WispErrCtx;

#define WISP_ERR_SET(ctx, c, ...) do {                               \
    (ctx)->code = (c);                                               \
    snprintf((ctx)->message, 512, __VA_ARGS__);                      \
    (ctx)->file = __FILE__;                                          \
    (ctx)->line = __LINE__;                                          \
} while (0)

#define WISP_CHECK_CUDA(call, ctx) do {                              \
    cudaError_t _e = (call);                                         \
    if (_e != cudaSuccess) {                                         \
        (ctx)->code = WISP_ERR_CUDA;                                 \
        snprintf((ctx)->message, 512, "CUDA error: %s",              \
                 cudaGetErrorString(_e));                            \
        (ctx)->file = __FILE__;                                      \
        (ctx)->line = __LINE__;                                      \
        return WISP_ERR_CUDA;                                        \
    }                                                                \
} while (0)

/* Same check for functions that return a pointer (NULL on failure). */
#define WISP_CHECK_CUDA_NULL(call, ctx) do {                         \
    cudaError_t _e = (call);                                         \
    if (_e != cudaSuccess) {                                         \
        (ctx)->code = WISP_ERR_CUDA;                                 \
        snprintf((ctx)->message, 512, "CUDA error: %s",              \
                 cudaGetErrorString(_e));                            \
        (ctx)->file = __FILE__;                                      \
        (ctx)->line = __LINE__;                                      \
        return NULL;                                                 \
    }                                                                \
} while (0)

#define WISP_CHECK_NULL(ptr, ctx, msg) do {                          \
    if ((ptr) == NULL) {                                             \
        (ctx)->code = WISP_ERR_OOM;                                  \
        snprintf((ctx)->message, 512, "NULL pointer: %s", (msg));    \
        (ctx)->file = __FILE__;                                      \
        (ctx)->line = __LINE__;                                      \
        return WISP_ERR_OOM;                                         \
    }                                                                \
} while (0)

/*
 * OOM / failure policy (implemented in wisp_engine.c / lru_cache.c):
 *   VRAM OOM : evict LRU expert to RAM, retry allocation
 *   RAM OOM  : evict LRU expert to SSD (drop copy — SSD is authoritative)
 *   SSD IO   : return WISP_ERR_IO, engine logs and skips token
 *   CUDA err : return WISP_ERR_CUDA, Python layer catches and reports
 */

/* ======================================================================= *
 * 2. Cross-platform threading — use ONLY these in wisp C files
 * ======================================================================= */

#ifdef _WIN32
    #ifndef WIN32_LEAN_AND_MEAN
    #define WIN32_LEAN_AND_MEAN
    #endif
    #ifndef NOMINMAX
    #define NOMINMAX
    #endif
    #include <windows.h>
    typedef CRITICAL_SECTION wisp_mutex_t;
    typedef CONDITION_VARIABLE wisp_cond_t;
    #define wisp_mutex_init(m)    InitializeCriticalSection(m)
    #define wisp_mutex_lock(m)    EnterCriticalSection(m)
    #define wisp_mutex_unlock(m)  LeaveCriticalSection(m)
    #define wisp_mutex_destroy(m) DeleteCriticalSection(m)
    #define wisp_cond_init(c)     InitializeConditionVariable(c)
    #define wisp_cond_wait(c,m)   SleepConditionVariableCS(c, m, INFINITE)
    #define wisp_cond_signal(c)   WakeConditionVariable(c)
    #define wisp_cond_broadcast(c) WakeAllConditionVariable(c)
    typedef HANDLE wisp_thread_t;
#else
    #include <pthread.h>
    typedef pthread_mutex_t wisp_mutex_t;
    typedef pthread_cond_t  wisp_cond_t;
    #define wisp_mutex_init(m)    pthread_mutex_init(m, NULL)
    #define wisp_mutex_lock(m)    pthread_mutex_lock(m)
    #define wisp_mutex_unlock(m)  pthread_mutex_unlock(m)
    #define wisp_mutex_destroy(m) pthread_mutex_destroy(m)
    #define wisp_cond_init(c)     pthread_cond_init(c, NULL)
    #define wisp_cond_wait(c,m)   pthread_cond_wait(c, m)
    #define wisp_cond_signal(c)   pthread_cond_signal(c)
    #define wisp_cond_broadcast(c) pthread_cond_broadcast(c)
    typedef pthread_t wisp_thread_t;
#endif

/* Thread spawn/join wrapper (implemented in double_buffer.c) */
typedef void* (*wisp_thread_fn)(void*);
int  wisp_thread_create(wisp_thread_t* t, wisp_thread_fn fn, void* arg);
void wisp_thread_join(wisp_thread_t t);

/* Monotonic nanoseconds (implemented in wisp_engine.c) */
uint64_t wisp_now_ns(void);

/* ======================================================================= *
 * 3. CUDA compatibility shim
 *    GPU build : the real CUDA runtime is included above (pre-extern-C).
 *    WISP_NO_CUDA build : provide host-memory stand-ins with identical
 *    signatures, so every .c file compiles unchanged. "Device" pointers
 *    are host pointers; async copies are memcpy; streams/events are no-ops.
 * ======================================================================= */

#ifdef WISP_NO_CUDA
    typedef uint16_t wisp_half;              /* raw fp16 bits on CPU        */
    typedef int cudaError_t;
    #define cudaSuccess 0
    typedef void* cudaStream_t;
    typedef void* cudaEvent_t;
    typedef enum {
        cudaMemcpyHostToDevice = 1,
        cudaMemcpyDeviceToHost = 2,
        cudaMemcpyDeviceToDevice = 3,
    } cudaMemcpyKind;
    #define cudaHostAllocDefault 0

    const char* cudaGetErrorString(cudaError_t e);
    cudaError_t cudaMalloc(void** p, size_t n);
    cudaError_t cudaFree(void* p);
    cudaError_t cudaHostAlloc(void** p, size_t n, unsigned int flags);
    cudaError_t cudaFreeHost(void* p);
    cudaError_t cudaMemcpy(void* dst, const void* src, size_t n, cudaMemcpyKind k);
    cudaError_t cudaMemcpyAsync(void* dst, const void* src, size_t n,
                                cudaMemcpyKind k, cudaStream_t s);
    cudaError_t cudaMemsetAsync(void* p, int v, size_t n, cudaStream_t s);
    cudaError_t cudaStreamCreate(cudaStream_t* s);
    cudaError_t cudaStreamDestroy(cudaStream_t s);
    cudaError_t cudaStreamSynchronize(cudaStream_t s);
    cudaError_t cudaEventCreate(cudaEvent_t* e);
    cudaError_t cudaEventDestroy(cudaEvent_t e);
    cudaError_t cudaEventRecord(cudaEvent_t e, cudaStream_t s);
    cudaError_t cudaEventSynchronize(cudaEvent_t e);
    cudaError_t cudaSetDevice(int d);
#endif

/* fp16 <-> fp32 host-side conversion (implemented in wisp_engine.c;
 * needed by the OpenMP CPU math path on every platform). */
float wisp_half_to_float(uint16_t h);
uint16_t wisp_float_to_half(float f);

/* ======================================================================= *
 * 4. Expert blob format — MUST mirror wisp/converter/partitioner.py
 * ======================================================================= */

#define WISP_EXPERT_MAGIC   0x57455850u
#define WISP_EXPERT_VERSION 1u
#define WISP_EXPERT_NMATS   3          /* gate, up, down — in that order   */

/* Accesses before a RAM-tier expert earns a VRAM cache slot */
#define WISP_PROMOTE_HITS   3

#pragma pack(push, 1)
typedef struct {
    uint32_t rows;
    uint32_t cols;
    uint64_t packed_bytes;
    uint64_t scales_bytes;
    uint64_t zeros_bytes;
} WispExpertMat;

typedef struct {
    uint32_t magic;
    uint32_t version;
    uint32_t layer_id;
    uint32_t expert_id;
    uint32_t group_size;
    uint32_t n_mats;
    WispExpertMat mats[WISP_EXPERT_NMATS];
} WispExpertHeader;                    /* exactly 120 bytes on disk        */
#pragma pack(pop)

/* Byte offsets of each blob inside an expert file, derived from a header. */
typedef struct {
    size_t packed_off[WISP_EXPERT_NMATS];
    size_t scales_off[WISP_EXPERT_NMATS];
    size_t zeros_off[WISP_EXPERT_NMATS];
    uint32_t rows[WISP_EXPERT_NMATS];
    uint32_t cols[WISP_EXPERT_NMATS];
    uint32_t group_size;
    size_t total_bytes;
    int valid;
} WispExpertMeta;

WispError wisp_expert_parse_header(const void* blob, size_t blob_size,
                                   WispExpertMeta* meta, WispErrCtx* err);

/* ======================================================================= *
 * 5. Model config + engine structs
 * ======================================================================= */

typedef enum { WISP_ATTN_MLA = 0, WISP_ATTN_GQA = 1, WISP_ATTN_MHA = 2 }
    WispAttnType;

typedef struct {
    int num_layers;
    int n_experts;           /* routed experts per layer                    */
    int n_shared_experts;
    int top_k;
    int hidden;
    int vocab;
    int moe_inter;           /* routed expert intermediate size             */
    int shared_inter;        /* shared expert intermediate size             */
    WispAttnType attn_type;
    int n_heads;
    int n_kv_heads;          /* GQA only                                    */
    int head_dim;            /* GQA only                                    */
    int q_lora;              /* MLA only                                    */
    int kv_lora;             /* MLA only                                    */
    int qk_nope;             /* MLA only                                    */
    int qk_rope;             /* MLA only                                    */
    int v_head_dim;          /* MLA only                                    */
    float rope_theta;
    float rms_eps;
    int group_size;          /* int4 quant group size                       */
    size_t expert_size_bytes;
    int64_t max_pos;
} WispModelConfig;

/* Dense weights for one layer — device pointers (fp16). NULL when the
 * tensor does not exist for this family/layer. */
typedef struct {
    wisp_half* input_norm;
    wisp_half* post_norm;
    wisp_half* router;        /* [n_experts, hidden]                        */
    wisp_half* router_bias;   /* [n_experts] or NULL                        */
    wisp_half* shared_gate;   /* [shared_inter, hidden]                     */
    wisp_half* shared_up;
    wisp_half* shared_down;   /* [hidden, shared_inter]                     */
    /* GQA/MHA */
    wisp_half* q_proj;
    wisp_half* k_proj;
    wisp_half* v_proj;
    /* MLA */
    wisp_half* q_a_proj;
    wisp_half* q_a_norm;
    wisp_half* q_b_proj;
    wisp_half* kv_a_proj;
    wisp_half* kv_a_norm;
    wisp_half* kv_b_proj;     /* [n_heads*(qk_nope+v_dim), kv_lora]         */
    /* both */
    wisp_half* o_proj;
    int is_dense_mlp;         /* early layers with no routed experts        */
    int shared_inter;         /* rows of shared_gate (per-layer actual)     */
} WispLayerWeights;

/* KV cache. Layout per layer: K [max_seq, kv_heads, k_dim] fp16 and
 * V [max_seq, kv_heads, v_dim] fp16, both in one device allocation.
 * MLA (absorbed): kv_heads=1, k_dim = kv_lora + qk_rope, v_dim = 0 (the
 * value read IS the first kv_lora dims of K — true MLA compressed cache). */
typedef struct {
    wisp_half* base;          /* single device allocation                   */
    size_t k_layer_stride;    /* elements per layer in K region             */
    size_t v_layer_stride;
    wisp_half* v_base;        /* NULL for MLA (V aliases K)                 */
    int max_seq;
    int len;                  /* tokens currently cached                    */
    int kv_heads;
    int k_dim;
    int v_dim;
} WispKVCache;

/* Forward declarations of subsystem structs (full defs in their headers) */
struct LRUCache;
struct DoubleBuffer;
struct PinnedPool;
struct PrefetchQueue;
struct VramBudget;

typedef struct WispEngine {
    /* identity + config */
    char model_path[1024];
    WispModelConfig cfg;
    int use_gpu;
    int gpu_indices[8];
    int gpu_count;
    int omp_threads;

    /* dense weights */
    wisp_half* embed_tokens;   /* [vocab, hidden]                           */
    wisp_half* final_norm;     /* [hidden]                                  */
    wisp_half* lm_head;        /* [vocab, hidden]                           */
    WispLayerWeights* layers;  /* [num_layers]                              */

    /* tier caches (defined in lru_cache.h) */
    struct LRUCache* vram_cache;
    struct LRUCache* ram_cache;
    struct VramBudget* vram_budget;
    int experts_on_gpu;        /* 0 = hybrid: experts run on CPU (OpenMP)   */

    /* IO pipeline */
    struct DoubleBuffer* double_buf;
    struct PinnedPool* pinned_pool;
    struct PrefetchQueue* prefetch;
    size_t max_expert_bytes;

    /* per-layer expert shape metadata (parsed once) */
    WispExpertMeta* expert_meta;   /* [num_layers]                          */

    /* Scratch-ring expert serving. Measured on the first real Mixtral
     * runs (2026-07-19): force-promoting every RAM hit into a VRAM tier
     * smaller than the per-token working set thrashes — each hit costs
     * an H2D copy PLUS an evicted victim's D2H copy (~25ms round trip),
     * capping decode at ~0.6 tok/s. Cool experts are instead served
     * through a small ring of persistent device buffers (H2D only, no
     * cache insert, no eviction); an expert earns a real VRAM slot only
     * after WISP_PROMOTE_HITS accesses prove it hot. */
    void*  scratch_ring[16];
    int    scratch_slots;          /* top_k + 2, capped at 16               */
    int    scratch_pos;

    /* CUDA streams */
    cudaStream_t compute_stream;
    cudaStream_t transfer_stream;

    /* activation / scratch buffers (device; fp32 unless noted) */
    float* buf_x;              /* [hidden]                                  */
    float* buf_norm;           /* [hidden]                                  */
    float* buf_attn_a;         /* projections scratch A                     */
    float* buf_attn_b;         /* projections scratch B                     */
    float* buf_attn_c;         /* projections scratch C                     */
    float* buf_attn_out;       /* [hidden]                                  */
    float* buf_scores;         /* [n_heads, max_seq] attention scratch      */
    float* buf_gate;           /* [inter]                                   */
    float* buf_up;             /* [inter]                                   */
    float* buf_h;              /* [inter]                                   */
    float* buf_ffn;            /* [hidden] expert accumulation              */
    float* buf_logits;         /* [vocab]                                   */
    float* host_logits;        /* pinned [vocab]                            */
    wisp_half* buf_dq_gate;    /* dequantized expert weights (fp16)         */
    wisp_half* buf_dq_up;
    wisp_half* buf_dq_down;
    float* buf_router_logits;  /* [n_experts]                               */
    int*   host_topk_idx;      /* pinned [top_k]                            */
    float* host_topk_w;        /* pinned [top_k]                            */

    /* host-side scratch for the CPU / hybrid expert math (always present) */
    float* hs_x;               /* [hidden]  x_norm mirror                   */
    float* hs_ffn;             /* [hidden]  expert accumulator              */
    float* hs_gate;            /* [inter]                                   */
    float* hs_up;              /* [inter]                                   */
    float* hs_h;               /* [inter]                                   */
    float* hs_y;               /* [hidden]                                  */

    /* Expert access log. Routing happens down here in C, so without
     * this the Python layer is blind to which experts actually fired —
     * its prefetch predictor and the cross-session learning cache would
     * both be guessing. Each fetch appends a packed (layer << 16 |
     * expert) word to a ring buffer that Python drains periodically.
     * Written under stats_mutex, which the fetch path already takes,
     * so logging costs no extra lock. */
    uint32_t* access_log;
    int       access_log_cap;
    int       access_log_count;    /* valid entries, <= cap            */
    int       access_log_head;     /* next write slot                  */
    uint64_t  access_log_dropped;  /* lost to wrap-around              */

    /* stats */
    wisp_mutex_t stats_mutex;
    uint64_t vram_hits;
    uint64_t ram_hits;
    uint64_t ssd_hits;
    uint64_t token_times_ns[32];   /* ring buffer of recent decode stamps   */
    int token_time_head;
    int token_time_count;

    WispErrCtx last_err;
} WispEngine;

/* ======================================================================= *
 * 6. Public engine API (called by csrc/bindings/wisp_bindings.cpp)
 * ======================================================================= */

WispEngine* wisp_engine_create(const char* model_path,
                               size_t vram_expert_budget_bytes,
                               size_t ram_expert_budget_bytes,
                               const int* gpu_indices, int gpu_count,
                               int omp_threads,
                               WispErrCtx* err);
void wisp_engine_destroy(WispEngine* eng);

WispKVCache* wisp_kv_cache_alloc(WispEngine* eng, int max_seq_len,
                                 WispErrCtx* err);
void wisp_kv_cache_free(WispEngine* eng, WispKVCache* kv);
void wisp_kv_cache_clear(WispEngine* eng, WispKVCache* kv);
void wisp_kv_cache_rollback(WispEngine* eng, WispKVCache* kv, int n_tokens);

/* Prefill a prompt; logits for the LAST token land in out_logits[vocab]. */
WispError wisp_prefill(WispEngine* eng, const int* token_ids, int n_tokens,
                       WispKVCache* kv, float* out_logits, WispErrCtx* err);

/* Decode a single token (the innermost loop). */
WispError wisp_decode_one(WispEngine* eng, int token_id,
                          WispKVCache* kv, float* out_logits, WispErrCtx* err);

/* Speculative verification: run n draft tokens through the model,
 * capturing logits at EVERY position -> out_logits[n * vocab]. */
WispError wisp_verify_tokens(WispEngine* eng, const int* token_ids,
                             int n_tokens, WispKVCache* kv,
                             float* out_logits, WispErrCtx* err);

/* Expert fetch — THE hot path (488 calls/token for GLM-5.2). Returns a
 * tier-resident pointer to the packed expert blob, or NULL (err set). */
void* wisp_expert_fetch(WispEngine* eng, uint32_t layer_id,
                        uint32_t expert_id, WispErrCtx* err);

/* Async prefetch hint (from the Python router predictor). */
void wisp_expert_prefetch_hint(WispEngine* eng, int layer_idx,
                               const int* expert_ids, int n);

/* Introspection */
void wisp_cache_stats(WispEngine* eng, uint64_t* vram_hits,
                      uint64_t* ram_hits, uint64_t* ssd_hits,
                      double* hit_rate);
void wisp_cache_clear_all(WispEngine* eng);
/* Evict up to `count` LRU experts from the RAM tier (SSD stays
 * authoritative — this is a pure free). Used by the runtime's memory
 * watermark to keep system RAM from filling completely. */
int  wisp_ram_trim(WispEngine* eng, int count);

/* Drain the expert access log into `out` (packed layer<<16|expert).
 * Returns the number written; clears the log. `dropped_out` receives
 * the running count of entries lost to ring wrap-around, so the caller
 * can tell a complete record from a sampled one. */
int  wisp_drain_expert_log(WispEngine* eng, uint32_t* out, int max_out,
                           uint64_t* dropped_out);
size_t wisp_vram_used(WispEngine* eng);
size_t wisp_ram_used(WispEngine* eng);
double wisp_tok_per_sec(WispEngine* eng);

/* Self-tests (exposed to pytest through the bindings) */
int wisp_selftest_lru(void);
int wisp_selftest_double_buffer(void);
#ifndef WISP_NO_CUDA
int wisp_selftest_kda(void);   /* verifies the KDA recurrence on-device */
#endif

/* Byte-layout cross-check (exposed to pytest): parse an expert .bin
 * written by wisp/converter/partitioner.py and dequantize the first
 * `n` values of matrix `mat` with the engine's own int4 math, so the
 * packer -> C reader -> dequant chain is verified end to end. */
WispError wisp_debug_expert_probe(const char* path, int mat, int n,
                                  float* out_values,
                                  WispExpertMeta* out_meta,
                                  WispErrCtx* err);

/* ======================================================================= *
 * 7. GPU kernel launcher interface — implemented in csrc/cuda/*.cu.
 *    Only referenced when WISP_NO_CUDA is not defined.
 * ======================================================================= */
#ifndef WISP_NO_CUDA

/* matmul.cu */
void wisp_gpu_gemv_f16(const wisp_half* W, const float* x, float* y,
                       int rows, int cols, cudaStream_t s);
void wisp_gpu_gemv_t_f16(const wisp_half* W, const float* x, float* y,
                         int rows, int cols, cudaStream_t s); /* y = W^T x */
void wisp_gpu_rmsnorm(const float* x, const wisp_half* w, float* y,
                      int n, float eps, cudaStream_t s);
void wisp_gpu_residual_add(float* x, const float* delta, int n,
                           cudaStream_t s);
void wisp_gpu_swiglu(const float* gate, const float* up, float* out,
                     int n, cudaStream_t s);
void wisp_gpu_swiglu_ffn(const wisp_half* Wg, const wisp_half* Wu,
                         const float* x, float* h, int inter, int cols,
                         cudaStream_t s);   /* fused gate+up+silu*up */
void wisp_gpu_scale_accum(float* acc, const float* x, float w, int n,
                          cudaStream_t s);
void wisp_gpu_embed_lookup(const wisp_half* table, int token, float* x,
                           int hidden, cudaStream_t s);

/* attention.cu */
void wisp_gpu_rope(float* x, int n_heads, int head_stride, int rope_off,
                   int rope_dim, int pos, float theta, cudaStream_t s);
void wisp_gpu_attention(const float* q, const wisp_half* Kcache,
                        const wisp_half* Vcache, float* out,
                        float* score_scratch, int seq_len, int n_heads,
                        int kv_heads, int k_dim, int v_dim, float scale,
                        cudaStream_t s);
void wisp_gpu_mla_absorb_q(const wisp_half* kv_b, const float* q,
                           float* q_eff, int n_heads, int qk_nope,
                           int qk_rope, int v_dim, int kv_lora,
                           cudaStream_t s);
void wisp_gpu_mla_out(const wisp_half* kv_b, const float* attn_c,
                      float* out, int n_heads, int qk_nope, int v_dim,
                      int kv_lora, cudaStream_t s);

/* router.cu */
void wisp_gpu_router_topk(const wisp_half* W, const wisp_half* bias,
                          const float* x, float* logits_scratch,
                          int n_experts, int hidden, int top_k,
                          int* out_idx, float* out_w, cudaStream_t s);

/* kv_cache.cu */
void wisp_gpu_kv_append(wisp_half* K, wisp_half* V, const float* k,
                        const float* v, int pos, int kv_heads,
                        int k_dim, int v_dim, cudaStream_t s);

/* expert_loader.cu */
cudaError_t launch_dequant_expert(const uint8_t* d_packed,
                                  const wisp_half* d_scales,
                                  const wisp_half* d_zeros,
                                  wisp_half* d_output,
                                  int n_elements, int group_size,
                                  cudaStream_t stream);
cudaError_t async_load_expert(const uint8_t* h_packed,
                              const wisp_half* h_scales,
                              const wisp_half* h_zeros,
                              uint8_t* d_packed_tmp,
                              wisp_half* d_scales_tmp,
                              wisp_half* d_zeros_tmp,
                              wisp_half* d_output,
                              int n_elements, int group_size,
                              cudaStream_t stream);

/* speculative.cu */
void wisp_gpu_softmax_temp(const float* logits, float* probs, int n,
                           float temperature, cudaStream_t s);
void wisp_gpu_verify_batch(const float* main_probs, const float* draft_probs,
                           const int* draft_tokens, int K, int vocab,
                           float* accept_probs, cudaStream_t s);
void wisp_gpu_verify_scan(const float* accept_probs, const float* rand_u,
                          int K, int* n_accepted, int* first_reject,
                          cudaStream_t s);   /* on-GPU acceptance scan */

/* kda_attention.cu — Kimi Delta Attention (69 of K3's 93 layers).
 * State is [batch, heads, d_k, d_v] per layer and CONSTANT in sequence
 * length; that is the whole point of linear attention. */
size_t wisp_kda_state_bytes(int batch_size, int num_heads, int d_k,
                            int d_v, int num_kda_layers);
cudaError_t wisp_kda_alloc_state(void** state_ptr, int batch_size,
                                 int num_heads, int d_k, int d_v,
                                 int num_kda_layers);
cudaError_t wisp_kda_free_state(void* state_ptr);
cudaError_t wisp_kda_reset_state(void* state_ptr, int batch_size,
                                 int num_heads, int d_k, int d_v,
                                 int num_kda_layers, cudaStream_t stream);
cudaError_t wisp_kda_decode_step(float* state,
                                 const wisp_half* q, const wisp_half* k,
                                 const wisp_half* v, const wisp_half* beta,
                                 const wisp_half* gate, wisp_half* output,
                                 int batch_size, int num_heads,
                                 int d_k, int d_v, cudaStream_t stream);
cudaError_t wisp_kda_prefill(float* state_out, const float* state_in,
                             const wisp_half* q, const wisp_half* k,
                             const wisp_half* v, const wisp_half* beta,
                             const wisp_half* gate, wisp_half* output,
                             int batch_size, int seq_len, int num_heads,
                             int d_k, int d_v, cudaStream_t stream);

/* multi_gpu.cu */
int  wisp_nccl_available(void);
int  wisp_pipeline_init(const int* gpu_indices, int n);
void wisp_pipeline_shutdown(void);
int  wisp_pipeline_send_activation(const float* x, int n, int peer_stage,
                                   cudaStream_t s);
int  wisp_pipeline_recv_activation(float* x, int n, int peer_stage,
                                   cudaStream_t s);
int  wisp_peer_enable(int dev_a, int dev_b);   /* 2-GPU P2P, no NCCL */
int  wisp_peer_copy_async(void* dst, int dst_dev, const void* src,
                          int src_dev, size_t n, cudaStream_t s);

#endif /* !WISP_NO_CUDA */

#ifdef __cplusplus
}
#endif
