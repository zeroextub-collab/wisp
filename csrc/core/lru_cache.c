/*
 * lru_cache.c — O(1) LRU with hash table. See lru_cache.h for the API.
 *
 * Recency list:  head = MRU, tail = LRU. Eviction pops the tail.
 * Hash table:    key = layer_id * LRU_MAX_EXPERTS_PER_LAYER + expert_id,
 *                fibonacci-hashed into a power-of-two table with chaining.
 */

#include <stdlib.h>
#include "lru_cache.h"

/* ----------------------------------------------------------------------- */
static uint32_t lru_hash(uint32_t layer, uint32_t expert, uint32_t mask) {
    uint64_t key = (uint64_t)layer * LRU_MAX_EXPERTS_PER_LAYER + expert;
    /* Fibonacci hashing — excellent spread for sequential keys */
    return (uint32_t)((key * 11400714819323198485ull) >> 32) & mask;
}

static uint32_t next_pow2(uint32_t v) {
    v--;
    v |= v >> 1; v |= v >> 2; v |= v >> 4; v |= v >> 8; v |= v >> 16;
    return v + 1;
}

/* --- unlocked internals ------------------------------------------------- */

static void list_detach(LRUCache* c, LRUNode* n) {
    if (n->prev) n->prev->next = n->next; else c->head = n->next;
    if (n->next) n->next->prev = n->prev; else c->tail = n->prev;
    n->prev = n->next = NULL;
}

static void list_push_front(LRUCache* c, LRUNode* n) {
    n->prev = NULL;
    n->next = c->head;
    if (c->head) c->head->prev = n;
    c->head = n;
    if (!c->tail) c->tail = n;
}

static void table_insert(LRUCache* c, LRUNode* n) {
    uint32_t slot = lru_hash(n->layer_id, n->expert_id, c->table_mask);
    n->hnext = c->table[slot];
    c->table[slot] = n;
}

static void table_remove(LRUCache* c, LRUNode* n) {
    uint32_t slot = lru_hash(n->layer_id, n->expert_id, c->table_mask);
    LRUNode** pp = &c->table[slot];
    while (*pp) {
        if (*pp == n) { *pp = n->hnext; n->hnext = NULL; return; }
        pp = &(*pp)->hnext;
    }
}

static LRUNode* table_find(LRUCache* c, uint32_t layer, uint32_t expert) {
    uint32_t slot = lru_hash(layer, expert, c->table_mask);
    LRUNode* n = c->table[slot];
    while (n) {
        if (n->layer_id == layer && n->expert_id == expert) return n;
        n = n->hnext;
    }
    return NULL;
}

static void detach_unlocked(LRUCache* c, LRUNode* n) {
    list_detach(c, n);
    table_remove(c, n);
    c->used_bytes -= n->size_bytes;
    c->count--;
}

/* --- public API --------------------------------------------------------- */

WispError lru_init(LRUCache* c, uint64_t cap, WispTier tier, WispErrCtx* err) {
    WISP_CHECK_NULL(c, err, "lru_init: cache");
    memset(c, 0, sizeof(*c));
    c->capacity_bytes = cap;
    c->tier = tier;

    /* Size the table for the worst case: capacity / smallest plausible
     * expert (1 MB), min 1024 slots, power of two. */
    uint64_t want = cap / (1024 * 1024);
    if (want < 1024) want = 1024;
    if (want > (1u << 22)) want = 1u << 22;
    c->table_size = next_pow2((uint32_t)want);
    c->table_mask = c->table_size - 1;
    c->table = (LRUNode**)calloc(c->table_size, sizeof(LRUNode*));
    WISP_CHECK_NULL(c->table, err, "lru_init: hash table");

    wisp_mutex_init(&c->mutex);
    return WISP_OK;
}

void lru_destroy(LRUCache* c) {
    if (!c) return;
    wisp_mutex_lock(&c->mutex);
    LRUNode* n = c->head;
    while (n) {
        LRUNode* next = n->next;
        free(n);
        n = next;
    }
    free(c->table);
    c->table = NULL;
    c->head = c->tail = NULL;
    c->count = 0;
    c->used_bytes = 0;
    wisp_mutex_unlock(&c->mutex);
    wisp_mutex_destroy(&c->mutex);
}

LRUNode* lru_get(LRUCache* c, uint32_t layer, uint32_t expert) {
    wisp_mutex_lock(&c->mutex);
    LRUNode* n = table_find(c, layer, expert);
    wisp_mutex_unlock(&c->mutex);
    return n;   /* NULL = miss */
}

void lru_touch(LRUCache* c, LRUNode* node) {
    if (!node) return;
    wisp_mutex_lock(&c->mutex);
    list_detach(c, node);
    list_push_front(c, node);
    node->last_access_ns = wisp_now_ns();
    wisp_mutex_unlock(&c->mutex);
}

WispError lru_put(LRUCache* c, uint32_t layer, uint32_t expert,
                  void* data, size_t size, WispErrCtx* err) {
    WISP_CHECK_NULL(data, err, "lru_put: data");
    wisp_mutex_lock(&c->mutex);

    LRUNode* existing = table_find(c, layer, expert);
    if (existing) {
        /* Replace payload in place, refresh recency */
        c->used_bytes -= existing->size_bytes;
        existing->data_ptr = data;
        existing->size_bytes = size;
        existing->last_access_ns = wisp_now_ns();
        c->used_bytes += size;
        list_detach(c, existing);
        list_push_front(c, existing);
        wisp_mutex_unlock(&c->mutex);
        return WISP_OK;
    }

    LRUNode* n = (LRUNode*)calloc(1, sizeof(LRUNode));
    if (!n) {
        wisp_mutex_unlock(&c->mutex);
        WISP_ERR_SET(err, WISP_ERR_OOM, "lru_put: node alloc failed");
        return WISP_ERR_OOM;
    }
    n->layer_id = layer;
    n->expert_id = expert;
    n->data_ptr = data;
    n->size_bytes = size;
    n->last_access_ns = wisp_now_ns();

    list_push_front(c, n);
    table_insert(c, n);
    c->used_bytes += size;
    c->count++;

    wisp_mutex_unlock(&c->mutex);
    return WISP_OK;
}

LRUNode* lru_evict(LRUCache* c) {
    wisp_mutex_lock(&c->mutex);
    LRUNode* victim = c->tail;
    if (victim) detach_unlocked(c, victim);
    wisp_mutex_unlock(&c->mutex);
    return victim;  /* caller moves/frees victim->data_ptr, then lru_node_free */
}

void lru_remove(LRUCache* c, LRUNode* node) {
    if (!node) return;
    wisp_mutex_lock(&c->mutex);
    detach_unlocked(c, node);
    wisp_mutex_unlock(&c->mutex);
}

void lru_node_free(LRUNode* node) {
    free(node);
}

void lru_clear(LRUCache* c, void (*free_data)(void* data, void* ctx),
               void* ctx) {
    wisp_mutex_lock(&c->mutex);
    LRUNode* n = c->head;
    while (n) {
        LRUNode* next = n->next;
        if (free_data) free_data(n->data_ptr, ctx);
        free(n);
        n = next;
    }
    c->head = c->tail = NULL;
    c->count = 0;
    c->used_bytes = 0;
    memset(c->table, 0, c->table_size * sizeof(LRUNode*));
    wisp_mutex_unlock(&c->mutex);
}

int lru_would_overflow(const LRUCache* c, size_t size) {
    return c->used_bytes + size > c->capacity_bytes;
}

/* ----------------------------------------------------------------------- *
 * Self-test — exercised by tests/test_lru_cache.py via the bindings.
 * Returns 1 on success, 0 on the first failed invariant.
 * ----------------------------------------------------------------------- */
int wisp_selftest_lru(void) {
    WispErrCtx err = {0};
    LRUCache c;
    static int payload[8];

    if (lru_init(&c, 3 * sizeof(int), TIER_RAM, &err) != WISP_OK) return 0;

    /* Fill to capacity: 3 entries of sizeof(int) */
    for (uint32_t i = 0; i < 3; i++) {
        if (lru_put(&c, 0, i, &payload[i], sizeof(int), &err) != WISP_OK)
            goto fail;
    }
    if (c.count != 3) goto fail;

    /* Hit expert 0 -> becomes MRU; LRU is now expert 1 */
    LRUNode* n0 = lru_get(&c, 0, 0);
    if (!n0 || n0->expert_id != 0) goto fail;
    lru_touch(&c, n0);

    /* Miss returns NULL */
    if (lru_get(&c, 0, 99) != NULL) goto fail;
    if (lru_get(&c, 7, 0) != NULL) goto fail;

    /* Evict pops expert 1 (least recently used) */
    LRUNode* victim = lru_evict(&c);
    if (!victim || victim->expert_id != 1) goto fail;
    lru_node_free(victim);
    if (c.count != 2) goto fail;

    /* Overflow check + accounting */
    if (lru_would_overflow(&c, sizeof(int)) != 0) goto fail;   /* 2/3 used */
    if (lru_put(&c, 1, 5, &payload[3], sizeof(int), &err) != WISP_OK) goto fail;
    if (lru_would_overflow(&c, sizeof(int)) != 1) goto fail;   /* 3/3 used */
    if (c.used_bytes != 3 * sizeof(int)) goto fail;

    /* Duplicate put replaces, does not grow */
    if (lru_put(&c, 1, 5, &payload[4], sizeof(int), &err) != WISP_OK) goto fail;
    if (c.count != 3) goto fail;
    LRUNode* n5 = lru_get(&c, 1, 5);
    if (!n5 || n5->data_ptr != &payload[4]) goto fail;

    /* Eviction order after touches: MRU=(1,5), then (0,0), tail=(0,2) */
    victim = lru_evict(&c);
    if (!victim || !(victim->layer_id == 0 && victim->expert_id == 2)) goto fail;
    lru_node_free(victim);

    /* Clear empties everything */
    lru_clear(&c, NULL, NULL);
    if (c.count != 0 || c.used_bytes != 0) goto fail;
    if (lru_get(&c, 0, 0) != NULL) goto fail;

    lru_destroy(&c);
    return 1;

fail:
    lru_destroy(&c);
    return 0;
}
