/*
 * mem_pool.h — memory pools for the hot path.
 *
 * PinnedPool : fixed-size pinned host slabs (cudaHostAlloc) for SSD
 *              staging. Fixed slab size = max expert bytes, free-list
 *              recycling, O(1) alloc/free, thread-safe.
 *
 * VRAM allocation for expert blobs goes through wisp_vram_alloc /
 * wisp_vram_free — a thin tracked wrapper over cudaMalloc so the engine
 * can enforce its expert budget and answer get_vram_used_bytes().
 */

#pragma once

#include <stdint.h>
#include <stddef.h>
#include "wisp_engine.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct PinnedSlab {
    void* ptr;
    struct PinnedSlab* next;   /* free list link */
} PinnedSlab;

typedef struct PinnedPool {
    size_t       slab_size;
    int          total_slabs;
    int          free_slabs;
    PinnedSlab*  free_list;
    PinnedSlab*  all;          /* array of total_slabs slab records */
    wisp_mutex_t mutex;
    wisp_cond_t  slab_freed;
} PinnedPool;

/* Preallocate `count` pinned slabs of `slab_size` bytes each. */
WispError pinned_pool_init(PinnedPool* p, size_t slab_size, int count,
                           WispErrCtx* err);
void pinned_pool_destroy(PinnedPool* p);

/* O(1). If `blocking`, waits until a slab frees; else returns NULL when
 * the pool is exhausted. */
void* pinned_pool_alloc(PinnedPool* p, int blocking);
void  pinned_pool_free(PinnedPool* p, void* ptr);

/* ----------------------------------------------------------------------- *
 * Tracked VRAM allocation (device memory; host malloc in WISP_NO_CUDA)
 * ----------------------------------------------------------------------- */

/* Tagged, not anonymous: wisp_engine.h forward-declares
 * `struct VramBudget` so WispEngine can hold a pointer without pulling
 * in this header. An anonymous typedef would make those two names
 * DIFFERENT types — the compiler reinterprets the pointer silently
 * (MSVC C4133) and the code only works by coincidence of layout. */
typedef struct VramBudget {
    size_t       budget_bytes;
    size_t       used_bytes;
    wisp_mutex_t mutex;
} VramBudget;

void  vram_budget_init(VramBudget* b, size_t budget_bytes);
void  vram_budget_destroy(VramBudget* b);

/* Returns NULL (no err set) when the allocation would exceed the budget —
 * caller responds by evicting from the VRAM LRU and retrying. Sets err
 * only on a real CUDA failure. */
void* wisp_vram_alloc(VramBudget* b, size_t size, WispErrCtx* err);
void  wisp_vram_free(VramBudget* b, void* ptr, size_t size);
size_t wisp_vram_budget_used(VramBudget* b);

#ifdef __cplusplus
}
#endif
