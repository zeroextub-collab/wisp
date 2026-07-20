/*
 * double_buffer.h — the double-buffer async prefetch pipeline.
 *
 * While the GPU computes token N (2-8 ms per layer batch), a background
 * prefetch thread loads token N+1's predicted experts from SSD into the
 * FILLING pinned buffer and stages them toward VRAM on the transfer
 * stream. The pinned->VRAM copy (0.1-0.3 ms) hides completely inside the
 * compute window, so the GPU never waits on the SSD for predicted experts.
 *
 *   [Token N   GPU compute:  ████████████████████ 6ms  ]
 *   [Token N+1 SSD->pinRAM:  ████ 1.5ms               ]
 *   [Token N+1 pinRAM->VRAM:      ██ 0.3ms            ]
 */

#pragma once

#include <stdint.h>
#include <stddef.h>
#include "wisp_engine.h"

#ifdef __cplusplus
extern "C" {
#endif

/* A batch of experts staged for one token */
#define WISP_MAX_BATCH_EXPERTS 64

typedef struct {
    uint32_t layer_id[WISP_MAX_BATCH_EXPERTS];
    uint32_t expert_id[WISP_MAX_BATCH_EXPERTS];
    size_t   offset[WISP_MAX_BATCH_EXPERTS];   /* into the pinned buffer   */
    size_t   size[WISP_MAX_BATCH_EXPERTS];
    int      count;
} ExpertBatch;

typedef struct DoubleBuffer {
    void*           buf[2];           /* Two pinned host buffers (A and B) */
    size_t          buf_size;         /* Bytes per buffer                  */
    int             active;           /* GPU is consuming this one (0/1)   */
    int             filling;          /* CPU is filling this one (1/0)     */
    ExpertBatch     batch[2];         /* What each buffer currently holds  */
    cudaStream_t    compute_stream;   /* Stream 0: GPU attention + FFN     */
    cudaStream_t    transfer_stream;  /* Stream 1: async RAM->VRAM memcpy  */
    cudaEvent_t     transfer_done;    /* Filling->VRAM transfer complete   */
    cudaEvent_t     compute_done;     /* GPU compute batch complete        */
    /* Threading — cross-platform (wisp_mutex_t maps to CRITICAL_SECTION
     * on Windows, pthread_mutex_t elsewhere; see wisp_engine.h) */
    wisp_mutex_t    mutex;
    wisp_cond_t     swap_ready;
    int             fill_in_progress; /* filling buffer is being written   */
} DoubleBuffer;

/* Lifecycle. buf_size should be top_k x max_expert_bytes. */
WispError double_buffer_init(DoubleBuffer* db, size_t buf_size,
                             cudaStream_t compute, cudaStream_t transfer,
                             WispErrCtx* err);
void double_buffer_destroy(DoubleBuffer* db);

/* Reserve `size` bytes in the FILLING buffer for (layer, expert).
 * Returns the staging pointer, or NULL when the buffer is full this
 * cycle (caller falls back to the synchronous path — never fatal). */
void* double_buffer_reserve(DoubleBuffer* db, uint32_t layer,
                            uint32_t expert, size_t size);

/* Mark the filling buffer complete for this token cycle. */
void double_buffer_fill_done(DoubleBuffer* db);

/* Called every token generation step: waits for the in-flight transfer,
 * swaps active/filling, resets the new filling batch. Returns the batch
 * the GPU may now consume (contents of the freshly-active buffer). */
ExpertBatch* double_buffer_tick(DoubleBuffer* db,
                                ExpertBatch* current_batch,
                                ExpertBatch* next_batch);

#ifdef __cplusplus
}
#endif
