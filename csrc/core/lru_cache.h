/*
 * lru_cache.h — O(1) LRU cache with hash-table lookup.
 *
 * One instance per tier (VRAM, RAM). Keys are (layer_id, expert_id);
 * values are tier-resident pointers to packed expert blobs. Every
 * operation is O(1): doubly-linked recency list + open-hashing table.
 *
 * Thread safety: callers hold the cache's mutex around compound
 * operations (get-then-promote); single calls lock internally.
 */

#pragma once

#include <stdint.h>
#include <stddef.h>
#include "wisp_engine.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum { TIER_VRAM = 0, TIER_RAM = 1, TIER_SSD = 2 } WispTier;

typedef struct LRUNode {
    uint32_t        layer_id;
    uint32_t        expert_id;
    void*           data_ptr;       /* Pointer into tier's memory          */
    size_t          size_bytes;
    uint64_t        last_access_ns; /* Monotonic nanoseconds               */
    uint32_t        hits;           /* Access count — gates VRAM promotion */
    struct LRUNode* prev;           /* More recently used                  */
    struct LRUNode* next;           /* Less recently used                  */
    struct LRUNode* hnext;          /* Hash chain                          */
} LRUNode;

typedef struct LRUCache {
    LRUNode*    head;               /* Most recently used                  */
    LRUNode*    tail;               /* Least recently used (evict first)   */
    uint64_t    capacity_bytes;
    uint64_t    used_bytes;
    uint32_t    count;
    WispTier    tier;
    /* Hash table for O(1) lookup: key = layer_id * MAX_EXPERTS + expert_id */
    LRUNode**   table;
    uint32_t    table_size;         /* Power of 2                          */
    uint32_t    table_mask;         /* table_size - 1                      */
    wisp_mutex_t mutex;
} LRUCache;

#define LRU_MAX_EXPERTS_PER_LAYER 4096u

/* All operations are O(1) */
WispError lru_init   (LRUCache* c, uint64_t cap, WispTier tier, WispErrCtx* err);
void      lru_destroy(LRUCache* c);                 /* frees nodes, NOT data */
LRUNode*  lru_get    (LRUCache* c, uint32_t layer, uint32_t expert); /* NULL = miss */
WispError lru_put    (LRUCache* c, uint32_t layer, uint32_t expert,
                      void* data, size_t size, WispErrCtx* err);
LRUNode*  lru_evict  (LRUCache* c);  /* Remove LRU node, return it (caller frees/moves data, then lru_node_free) */
void      lru_touch  (LRUCache* c, LRUNode* node);  /* Move to MRU position */
void      lru_remove (LRUCache* c, LRUNode* node);  /* Detach a specific node */
void      lru_node_free(LRUNode* node);             /* Free a detached node   */
void      lru_clear  (LRUCache* c, void (*free_data)(void* data, void* ctx),
                      void* ctx);

/* True if inserting `size` bytes would exceed capacity. */
int lru_would_overflow(const LRUCache* c, size_t size);

#ifdef __cplusplus
}
#endif
