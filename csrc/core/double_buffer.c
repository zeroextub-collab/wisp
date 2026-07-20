/*
 * double_buffer.c — double-buffer async prefetch pipeline + the
 * cross-platform thread wrapper used by every wisp background thread.
 */

#include <stdlib.h>
#include "double_buffer.h"

/* ----------------------------------------------------------------------- *
 * Cross-platform thread create/join (declared in wisp_engine.h)
 * ----------------------------------------------------------------------- */
#ifdef _WIN32

typedef struct { wisp_thread_fn fn; void* arg; } ThreadTrampoline;

static DWORD WINAPI win_thread_entry(LPVOID p) {
    ThreadTrampoline* t = (ThreadTrampoline*)p;
    wisp_thread_fn fn = t->fn;
    void* arg = t->arg;
    free(t);
    fn(arg);
    return 0;
}

int wisp_thread_create(wisp_thread_t* t, wisp_thread_fn fn, void* arg) {
    ThreadTrampoline* tr = (ThreadTrampoline*)malloc(sizeof(*tr));
    if (!tr) return -1;
    tr->fn = fn;
    tr->arg = arg;
    *t = CreateThread(NULL, 0, win_thread_entry, tr, 0, NULL);
    if (*t == NULL) { free(tr); return -1; }
    return 0;
}

void wisp_thread_join(wisp_thread_t t) {
    WaitForSingleObject(t, INFINITE);
    CloseHandle(t);
}

#else

int wisp_thread_create(wisp_thread_t* t, wisp_thread_fn fn, void* arg) {
    return pthread_create(t, NULL, fn, arg);
}

void wisp_thread_join(wisp_thread_t t) {
    pthread_join(t, NULL);
}

#endif

/* ----------------------------------------------------------------------- *
 * DoubleBuffer
 * ----------------------------------------------------------------------- */

WispError double_buffer_init(DoubleBuffer* db, size_t buf_size,
                             cudaStream_t compute, cudaStream_t transfer,
                             WispErrCtx* err) {
    WISP_CHECK_NULL(db, err, "double_buffer_init: db");
    if (buf_size == 0) {
        WISP_ERR_SET(err, WISP_ERR_INVALID_ARG,
                     "double_buffer_init: buf_size must be > 0");
        return WISP_ERR_INVALID_ARG;
    }
    memset(db, 0, sizeof(*db));
    db->buf_size = buf_size;
    db->active = 0;
    db->filling = 1;
    db->compute_stream = compute;
    db->transfer_stream = transfer;

    for (int i = 0; i < 2; i++) {
        WISP_CHECK_CUDA(
            cudaHostAlloc(&db->buf[i], buf_size, cudaHostAllocDefault), err);
    }
    WISP_CHECK_CUDA(cudaEventCreate(&db->transfer_done), err);
    WISP_CHECK_CUDA(cudaEventCreate(&db->compute_done), err);

    wisp_mutex_init(&db->mutex);
    wisp_cond_init(&db->swap_ready);
    return WISP_OK;
}

void double_buffer_destroy(DoubleBuffer* db) {
    if (!db) return;
    for (int i = 0; i < 2; i++) {
        if (db->buf[i]) { cudaFreeHost(db->buf[i]); db->buf[i] = NULL; }
    }
    if (db->transfer_done) cudaEventDestroy(db->transfer_done);
    if (db->compute_done) cudaEventDestroy(db->compute_done);
    wisp_mutex_destroy(&db->mutex);
}

void* double_buffer_reserve(DoubleBuffer* db, uint32_t layer,
                            uint32_t expert, size_t size) {
    wisp_mutex_lock(&db->mutex);
    ExpertBatch* b = &db->batch[db->filling];

    size_t used = 0;
    if (b->count > 0)
        used = b->offset[b->count - 1] + b->size[b->count - 1];

    if (b->count >= WISP_MAX_BATCH_EXPERTS || used + size > db->buf_size) {
        wisp_mutex_unlock(&db->mutex);
        return NULL;    /* full this cycle — caller uses the sync path     */
    }

    int i = b->count++;
    b->layer_id[i] = layer;
    b->expert_id[i] = expert;
    b->offset[i] = used;
    b->size[i] = size;
    db->fill_in_progress = 1;

    void* ptr = (char*)db->buf[db->filling] + used;
    wisp_mutex_unlock(&db->mutex);
    return ptr;
}

void double_buffer_fill_done(DoubleBuffer* db) {
    wisp_mutex_lock(&db->mutex);
    db->fill_in_progress = 0;
    wisp_cond_signal(&db->swap_ready);
    wisp_mutex_unlock(&db->mutex);
}

ExpertBatch* double_buffer_tick(DoubleBuffer* db,
                                ExpertBatch* current_batch,
                                ExpertBatch* next_batch) {
    /* 1. Wait for any writer still filling (rare — fills finish inside
     *    the compute window by design). */
    wisp_mutex_lock(&db->mutex);
    while (db->fill_in_progress) {
        wisp_cond_wait(&db->swap_ready, &db->mutex);
    }

    /* 2. Ensure the in-flight pinned->VRAM transfer for the filling
     *    buffer has fully drained before the GPU consumes it. */
    cudaEventRecord(db->transfer_done, db->transfer_stream);
    cudaEventSynchronize(db->transfer_done);

    /* 3. Swap roles. */
    int was_filling = db->filling;
    db->filling = db->active;
    db->active = was_filling;

    /* 4. Hand the freshly-active batch to the GPU side, reset filling. */
    if (current_batch) *current_batch = db->batch[db->active];
    db->batch[db->filling].count = 0;
    if (next_batch) *next_batch = db->batch[db->filling];

    ExpertBatch* out = &db->batch[db->active];
    wisp_mutex_unlock(&db->mutex);
    return out;
}

/* ----------------------------------------------------------------------- *
 * Self-test — exercised by tests/test_double_buffer.py via the bindings.
 * Simulates a producer thread filling buffers while the "GPU" side ticks.
 * Returns 1 on success.
 * ----------------------------------------------------------------------- */

typedef struct {
    DoubleBuffer* db;
    int rounds;
    int produced;
} ProducerArgs;

static void* producer_thread(void* p) {
    ProducerArgs* a = (ProducerArgs*)p;
    for (int r = 0; r < a->rounds; r++) {
        for (uint32_t e = 0; e < 4; e++) {
            void* dst = double_buffer_reserve(a->db, 0, e, 256);
            if (dst) {
                memset(dst, (int)(e + 1), 256);
                a->produced++;
            }
        }
        double_buffer_fill_done(a->db);
    }
    return NULL;
}

int wisp_selftest_double_buffer(void) {
    WispErrCtx err = {0};
    DoubleBuffer db;

    if (double_buffer_init(&db, 4096, NULL, NULL, &err) != WISP_OK) return 0;

    /* Reserve accounting: offsets must be contiguous, no overlap */
    void* p0 = double_buffer_reserve(&db, 1, 10, 1000);
    void* p1 = double_buffer_reserve(&db, 1, 11, 1000);
    if (!p0 || !p1) goto fail;
    if ((char*)p1 - (char*)p0 != 1000) goto fail;

    /* Capacity limit respected */
    if (double_buffer_reserve(&db, 1, 12, 4096) != NULL) goto fail;
    double_buffer_fill_done(&db);

    /* Tick swaps: the batch we filled becomes active */
    ExpertBatch cur, nxt;
    ExpertBatch* active = double_buffer_tick(&db, &cur, &nxt);
    if (!active || active->count != 2) goto fail;
    if (cur.count != 2 || nxt.count != 0) goto fail;
    if (active->expert_id[0] != 10 || active->expert_id[1] != 11) goto fail;

    /* Threaded producer across several tick cycles */
    ProducerArgs args = { &db, 8, 0 };
    wisp_thread_t t;
    if (wisp_thread_create(&t, producer_thread, &args) != 0) goto fail;
    for (int r = 0; r < 8; r++) {
        double_buffer_tick(&db, NULL, NULL);
    }
    wisp_thread_join(t);
    if (args.produced == 0) goto fail;

    /* Data written by producer landed inside pinned memory bounds */
    ExpertBatch* last = double_buffer_tick(&db, NULL, NULL);
    for (int i = 0; i < last->count; i++) {
        if (last->offset[i] + last->size[i] > db.buf_size) goto fail;
    }

    double_buffer_destroy(&db);
    return 1;

fail:
    double_buffer_destroy(&db);
    return 0;
}
