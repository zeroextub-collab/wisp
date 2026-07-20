/*
 * mem_pool.c — pinned host slab pool + tracked VRAM budget allocator.
 */

#include <stdlib.h>
#include "mem_pool.h"

/* ----------------------------------------------------------------------- *
 * PinnedPool
 * ----------------------------------------------------------------------- */

WispError pinned_pool_init(PinnedPool* p, size_t slab_size, int count,
                           WispErrCtx* err) {
    WISP_CHECK_NULL(p, err, "pinned_pool_init: pool");
    if (slab_size == 0 || count <= 0) {
        WISP_ERR_SET(err, WISP_ERR_INVALID_ARG,
                     "pinned_pool_init: slab_size=%zu count=%d",
                     slab_size, count);
        return WISP_ERR_INVALID_ARG;
    }
    memset(p, 0, sizeof(*p));
    p->slab_size = slab_size;
    p->total_slabs = count;

    p->all = (PinnedSlab*)calloc((size_t)count, sizeof(PinnedSlab));
    WISP_CHECK_NULL(p->all, err, "pinned_pool_init: slab records");

    for (int i = 0; i < count; i++) {
        cudaError_t e = cudaHostAlloc(&p->all[i].ptr, slab_size,
                                      cudaHostAllocDefault);
        if (e != cudaSuccess) {
            /* Roll back what we allocated so far */
            for (int j = 0; j < i; j++) cudaFreeHost(p->all[j].ptr);
            free(p->all);
            p->all = NULL;
            WISP_ERR_SET(err, WISP_ERR_OOM,
                         "pinned_pool_init: cudaHostAlloc failed at slab "
                         "%d/%d (%s)", i, count, cudaGetErrorString(e));
            return WISP_ERR_OOM;
        }
        p->all[i].next = p->free_list;
        p->free_list = &p->all[i];
    }
    p->free_slabs = count;

    wisp_mutex_init(&p->mutex);
    wisp_cond_init(&p->slab_freed);
    return WISP_OK;
}

void pinned_pool_destroy(PinnedPool* p) {
    if (!p || !p->all) return;
    for (int i = 0; i < p->total_slabs; i++) {
        if (p->all[i].ptr) cudaFreeHost(p->all[i].ptr);
    }
    free(p->all);
    p->all = NULL;
    p->free_list = NULL;
    p->free_slabs = 0;
    wisp_mutex_destroy(&p->mutex);
}

void* pinned_pool_alloc(PinnedPool* p, int blocking) {
    wisp_mutex_lock(&p->mutex);
    while (!p->free_list) {
        if (!blocking) {
            wisp_mutex_unlock(&p->mutex);
            return NULL;
        }
        wisp_cond_wait(&p->slab_freed, &p->mutex);
    }
    PinnedSlab* s = p->free_list;
    p->free_list = s->next;
    s->next = NULL;
    p->free_slabs--;
    void* ptr = s->ptr;
    wisp_mutex_unlock(&p->mutex);
    return ptr;
}

void pinned_pool_free(PinnedPool* p, void* ptr) {
    if (!ptr) return;
    wisp_mutex_lock(&p->mutex);
    /* Find the slab record for this pointer (small pool — linear is fine
     * and only runs off the hot path, on release). */
    for (int i = 0; i < p->total_slabs; i++) {
        if (p->all[i].ptr == ptr) {
            p->all[i].next = p->free_list;
            p->free_list = &p->all[i];
            p->free_slabs++;
            wisp_cond_signal(&p->slab_freed);
            break;
        }
    }
    wisp_mutex_unlock(&p->mutex);
}

/* ----------------------------------------------------------------------- *
 * Tracked VRAM budget
 * ----------------------------------------------------------------------- */

void vram_budget_init(VramBudget* b, size_t budget_bytes) {
    b->budget_bytes = budget_bytes;
    b->used_bytes = 0;
    wisp_mutex_init(&b->mutex);
}

void vram_budget_destroy(VramBudget* b) {
    wisp_mutex_destroy(&b->mutex);
}

void* wisp_vram_alloc(VramBudget* b, size_t size, WispErrCtx* err) {
    wisp_mutex_lock(&b->mutex);
    if (b->used_bytes + size > b->budget_bytes) {
        wisp_mutex_unlock(&b->mutex);
        return NULL;   /* over budget — caller evicts LRU and retries */
    }
    b->used_bytes += size;   /* reserve first so racing allocs stay honest */
    wisp_mutex_unlock(&b->mutex);

    void* ptr = NULL;
    cudaError_t e = cudaMalloc(&ptr, size);
    if (e != cudaSuccess || !ptr) {
        wisp_mutex_lock(&b->mutex);
        b->used_bytes -= size;
        wisp_mutex_unlock(&b->mutex);
#ifndef WISP_NO_CUDA
        if (e == cudaErrorMemoryAllocation) {
            /* Physical VRAM exhausted below our logical budget — the
             * driver, desktop compositor, KV cache, and CUDA context all
             * eat memory our accounting can't see. This is NOT fatal:
             * return NULL with err untouched so the caller evicts an LRU
             * expert and retries, exactly like a budget overflow. The
             * error state must be cleared for later cudaMalloc calls. */
            cudaGetLastError();
            return NULL;
        }
#endif
        if (e != cudaSuccess) {
            WISP_ERR_SET(err, WISP_ERR_CUDA,
                         "wisp_vram_alloc: cudaMalloc(%zu) failed: %s",
                         size, cudaGetErrorString(e));
        }
        return NULL;
    }
    return ptr;
}

void wisp_vram_free(VramBudget* b, void* ptr, size_t size) {
    if (!ptr) return;
    cudaFree(ptr);
    wisp_mutex_lock(&b->mutex);
    b->used_bytes = (b->used_bytes >= size) ? b->used_bytes - size : 0;
    wisp_mutex_unlock(&b->mutex);
}

size_t wisp_vram_budget_used(VramBudget* b) {
    wisp_mutex_lock(&b->mutex);
    size_t used = b->used_bytes;
    wisp_mutex_unlock(&b->mutex);
    return used;
}
