/*
 * multi_gpu.cu — NCCL pipeline synchronization for 3+ GPU mode.
 *
 * Pipeline parallelism: each GPU owns a contiguous range of transformer
 * layers; the [hidden] activation vector hops GPU -> GPU between stages
 * via ncclSend/ncclRecv on the compute stream.
 *
 * NCCL is optional at build time (Linux-first; not shipped on Windows).
 * Compile with -DWISP_HAS_NCCL and link nccl to enable; without it every
 * entry point reports "unavailable" and the engine falls back to
 * single-GPU + secondary-GPU-as-expert-cache strategies, which need no
 * peer transport.
 */

#include <cuda_runtime.h>
#include <stdint.h>
#include <string.h>

#include "../core/wisp_engine.h"

/* WISP_USE_NCCL is the documented public switch; WISP_HAS_NCCL kept as
 * an alias for existing build scripts. Either enables the NCCL path. */
#if defined(WISP_USE_NCCL) && !defined(WISP_HAS_NCCL)
#define WISP_HAS_NCCL
#endif

/* ----------------------------------------------------------------------- *
 * Peer-to-peer transport — works WITHOUT NCCL (2-GPU strategies).
 *
 * dual_same / dual_diff strategies move expert blobs and the [hidden]
 * activation vector between exactly two GPUs. cudaMemcpyPeerAsync covers
 * that completely (falling back to a staged host copy when the driver
 * reports no P2P link); NCCL is only required for the 3+ GPU pipeline's
 * collective setup.
 * ----------------------------------------------------------------------- */

extern "C" int wisp_peer_enable(int dev_a, int dev_b) {
    int can_ab = 0, can_ba = 0;
    if (cudaDeviceCanAccessPeer(&can_ab, dev_a, dev_b) != cudaSuccess ||
        cudaDeviceCanAccessPeer(&can_ba, dev_b, dev_a) != cudaSuccess)
        return -1;
    if (!can_ab || !can_ba) return 0;   /* no P2P link — staged copies */

    int prev = -1;
    cudaGetDevice(&prev);
    cudaSetDevice(dev_a);
    cudaError_t ea = cudaDeviceEnablePeerAccess(dev_b, 0);
    cudaSetDevice(dev_b);
    cudaError_t eb = cudaDeviceEnablePeerAccess(dev_a, 0);
    cudaSetDevice(prev);
    /* Already-enabled is success, not failure */
    if ((ea != cudaSuccess && ea != cudaErrorPeerAccessAlreadyEnabled) ||
        (eb != cudaSuccess && eb != cudaErrorPeerAccessAlreadyEnabled))
        return -1;
    return 1;                            /* direct P2P active */
}

extern "C" int wisp_peer_copy_async(void* dst, int dst_dev,
                                    const void* src, int src_dev,
                                    size_t n, cudaStream_t s) {
    /* cudaMemcpyPeerAsync handles both the direct-P2P and the
     * driver-staged (through host) case transparently. */
    return cudaMemcpyPeerAsync(dst, dst_dev, src, src_dev, n, s)
           == cudaSuccess ? 0 : -1;
}

#ifdef WISP_HAS_NCCL
#include <nccl.h>

#define WISP_PIPELINE_MAX_GPUS 8

typedef struct {
    ncclComm_t comms[WISP_PIPELINE_MAX_GPUS];
    int devices[WISP_PIPELINE_MAX_GPUS];
    int n;
    int rank_of_current;   /* stage index bound to the calling context */
    int initialized;
} PipelineState;

static PipelineState g_pipe = {0};

extern "C" int wisp_nccl_available(void) { return 1; }

extern "C" int wisp_pipeline_init(const int* gpu_indices, int n) {
    if (n < 2 || n > WISP_PIPELINE_MAX_GPUS) return -1;
    if (g_pipe.initialized) return 0;

    memcpy(g_pipe.devices, gpu_indices, (size_t)n * sizeof(int));
    g_pipe.n = n;

    /* Single-process multi-device init */
    if (ncclCommInitAll(g_pipe.comms, n, gpu_indices) != ncclSuccess)
        return -1;
    g_pipe.initialized = 1;
    return 0;
}

extern "C" void wisp_pipeline_shutdown(void) {
    if (!g_pipe.initialized) return;
    for (int i = 0; i < g_pipe.n; i++)
        ncclCommDestroy(g_pipe.comms[i]);
    memset(&g_pipe, 0, sizeof(g_pipe));
}

extern "C" int wisp_pipeline_send_activation(const float* x, int n,
                                             int peer_stage,
                                             cudaStream_t s) {
    if (!g_pipe.initialized || peer_stage < 0 || peer_stage >= g_pipe.n)
        return -1;
    int dev = -1;
    cudaGetDevice(&dev);
    int rank = -1;
    for (int i = 0; i < g_pipe.n; i++)
        if (g_pipe.devices[i] == dev) { rank = i; break; }
    if (rank < 0) return -1;
    return ncclSend(x, (size_t)n, ncclFloat32, peer_stage,
                    g_pipe.comms[rank], s) == ncclSuccess ? 0 : -1;
}

extern "C" int wisp_pipeline_recv_activation(float* x, int n,
                                             int peer_stage,
                                             cudaStream_t s) {
    if (!g_pipe.initialized || peer_stage < 0 || peer_stage >= g_pipe.n)
        return -1;
    int dev = -1;
    cudaGetDevice(&dev);
    int rank = -1;
    for (int i = 0; i < g_pipe.n; i++)
        if (g_pipe.devices[i] == dev) { rank = i; break; }
    if (rank < 0) return -1;
    return ncclRecv(x, (size_t)n, ncclFloat32, peer_stage,
                    g_pipe.comms[rank], s) == ncclSuccess ? 0 : -1;
}

#else /* !WISP_HAS_NCCL — honest stubs, engine falls back automatically */

extern "C" int wisp_nccl_available(void) { return 0; }

extern "C" int wisp_pipeline_init(const int* gpu_indices, int n) {
    (void)gpu_indices; (void)n;
    return -1;
}

extern "C" void wisp_pipeline_shutdown(void) {}

extern "C" int wisp_pipeline_send_activation(const float* x, int n,
                                             int peer_stage,
                                             cudaStream_t s) {
    (void)x; (void)n; (void)peer_stage; (void)s;
    return -1;
}

extern "C" int wisp_pipeline_recv_activation(float* x, int n,
                                             int peer_stage,
                                             cudaStream_t s) {
    (void)x; (void)n; (void)peer_stage; (void)s;
    return -1;
}

#endif /* WISP_HAS_NCCL */
