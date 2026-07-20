/*
 * wisp_bindings.cpp — pybind11 bridge, exposed as wisp._wisp_core.
 *
 * Python never calls CUDA directly; everything routes through here into
 * csrc/core + csrc/cuda. The binding surface below is the contract with
 * wisp/runtime/engine.py — keep both sides in lockstep.
 *
 * Handles are opaque integers mapped to WispEngine* / WispKVCache* in
 * process-local registries, so Python never holds raw pointers it could
 * misuse across processes.
 */

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <mutex>
#include <stdexcept>
#include <unordered_map>
#include <vector>

#include "../core/wisp_engine.h"

namespace py = pybind11;

/* ------------------------------------------------------------------ */
/* Handle registries                                                    */
/* ------------------------------------------------------------------ */

static std::mutex g_registry_mutex;
static std::unordered_map<int, WispEngine*> g_engines;
static std::unordered_map<int64_t, WispKVCache*> g_kv_caches;
static int g_next_engine_handle = 1;
static int64_t g_next_kv_handle = 1;

static WispEngine* engine_of(int handle) {
    std::lock_guard<std::mutex> lock(g_registry_mutex);
    auto it = g_engines.find(handle);
    if (it == g_engines.end())
        throw std::invalid_argument(
            "invalid wisp engine handle " + std::to_string(handle));
    return it->second;
}

static WispKVCache* kv_of(int64_t handle) {
    std::lock_guard<std::mutex> lock(g_registry_mutex);
    auto it = g_kv_caches.find(handle);
    if (it == g_kv_caches.end())
        throw std::invalid_argument(
            "invalid wisp kv-cache handle " + std::to_string(handle));
    return it->second;
}

[[noreturn]] static void raise_wisp(const WispErrCtx& err) {
    std::string msg = "wisp engine error [" + std::to_string(err.code) +
                      "]: " + err.message;
    if (err.file)
        msg += " (" + std::string(err.file) + ":" +
               std::to_string(err.line) + ")";
    throw std::runtime_error(msg);
}

/* ------------------------------------------------------------------ */
/* Module                                                               */
/* ------------------------------------------------------------------ */

PYBIND11_MODULE(_wisp_core, m) {
    m.doc() = "WISP C hot-path engine (3-tier MoE streaming)";

    /* --- Engine lifecycle ------------------------------------------ */
    m.def("engine_create",
          [](const std::string& model_path,
             int64_t vram_expert_budget_bytes,
             int64_t ram_expert_budget_bytes,
             const std::vector<int>& gpu_indices,
             int omp_threads) -> int {
              WispErrCtx err = {};
              WispEngine* eng;
              {
                  py::gil_scoped_release release;
                  eng = wisp_engine_create(
                      model_path.c_str(),
                      vram_expert_budget_bytes > 0
                          ? (size_t)vram_expert_budget_bytes : 0,
                      ram_expert_budget_bytes > 0
                          ? (size_t)ram_expert_budget_bytes : 0,
                      gpu_indices.data(), (int)gpu_indices.size(),
                      omp_threads, &err);
              }
              if (!eng) raise_wisp(err);
              std::lock_guard<std::mutex> lock(g_registry_mutex);
              int handle = g_next_engine_handle++;
              g_engines[handle] = eng;
              return handle;
          },
          py::arg("model_path"),
          py::arg("vram_expert_budget_bytes"),
          py::arg("ram_expert_budget_bytes"),
          py::arg("gpu_indices"),
          py::arg("omp_threads"));

    m.def("engine_destroy", [](int handle) {
        WispEngine* eng = nullptr;
        {
            std::lock_guard<std::mutex> lock(g_registry_mutex);
            auto it = g_engines.find(handle);
            if (it == g_engines.end()) return;
            eng = it->second;
            g_engines.erase(it);
        }
        py::gil_scoped_release release;
        wisp_engine_destroy(eng);
    }, py::arg("handle"));

    /* --- Token generation ------------------------------------------ */
    m.def("prefill",
          [](int handle, const std::vector<int>& token_ids,
             int64_t kv_cache_ptr) -> std::vector<float> {
              WispEngine* eng = engine_of(handle);
              WispKVCache* kv = kv_of(kv_cache_ptr);
              std::vector<float> logits((size_t)eng->cfg.vocab);
              WispErrCtx err = {};
              WispError e;
              {
                  py::gil_scoped_release release;
                  e = wisp_prefill(eng, token_ids.data(),
                                   (int)token_ids.size(), kv,
                                   logits.data(), &err);
              }
              if (e != WISP_OK) raise_wisp(err);
              return logits;
          },
          py::arg("handle"), py::arg("token_ids"), py::arg("kv_cache_ptr"));

    m.def("decode_one",
          [](int handle, int token_id,
             int64_t kv_cache_ptr) -> std::vector<float> {
              WispEngine* eng = engine_of(handle);
              WispKVCache* kv = kv_of(kv_cache_ptr);
              std::vector<float> logits((size_t)eng->cfg.vocab);
              WispErrCtx err = {};
              WispError e;
              {
                  py::gil_scoped_release release;
                  e = wisp_decode_one(eng, token_id, kv,
                                      logits.data(), &err);
              }
              if (e != WISP_OK) raise_wisp(err);
              return logits;
          },
          py::arg("handle"), py::arg("token_id"), py::arg("kv_cache_ptr"));

    /* Speculative extension: per-position logits for a draft window. */
    m.def("verify_tokens",
          [](int handle, const std::vector<int>& token_ids,
             int64_t kv_cache_ptr) -> std::vector<std::vector<float>> {
              WispEngine* eng = engine_of(handle);
              WispKVCache* kv = kv_of(kv_cache_ptr);
              size_t n = token_ids.size();
              size_t vocab = (size_t)eng->cfg.vocab;
              std::vector<float> flat(n * vocab);
              WispErrCtx err = {};
              WispError e;
              {
                  py::gil_scoped_release release;
                  e = wisp_verify_tokens(eng, token_ids.data(), (int)n,
                                         kv, flat.data(), &err);
              }
              if (e != WISP_OK) raise_wisp(err);
              std::vector<std::vector<float>> rows(n);
              for (size_t i = 0; i < n; i++)
                  rows[i].assign(flat.begin() + i * vocab,
                                 flat.begin() + (i + 1) * vocab);
              return rows;
          },
          py::arg("handle"), py::arg("token_ids"), py::arg("kv_cache_ptr"));

    /* --- KV cache management --------------------------------------- */
    m.def("kv_cache_alloc",
          [](int handle, int max_seq_len) -> int64_t {
              WispEngine* eng = engine_of(handle);
              WispErrCtx err = {};
              WispKVCache* kv;
              {
                  py::gil_scoped_release release;
                  kv = wisp_kv_cache_alloc(eng, max_seq_len, &err);
              }
              if (!kv) raise_wisp(err);
              std::lock_guard<std::mutex> lock(g_registry_mutex);
              int64_t h = g_next_kv_handle++;
              g_kv_caches[h] = kv;
              return h;
          },
          py::arg("handle"), py::arg("max_seq_len"));

    m.def("kv_cache_free", [](int handle, int64_t kv_cache_ptr) {
        WispEngine* eng = engine_of(handle);
        WispKVCache* kv = nullptr;
        {
            std::lock_guard<std::mutex> lock(g_registry_mutex);
            auto it = g_kv_caches.find(kv_cache_ptr);
            if (it == g_kv_caches.end()) return;
            kv = it->second;
            g_kv_caches.erase(it);
        }
        wisp_kv_cache_free(eng, kv);
    }, py::arg("handle"), py::arg("kv_cache_ptr"));

    m.def("kv_cache_clear", [](int handle, int64_t kv_cache_ptr) {
        wisp_kv_cache_clear(engine_of(handle), kv_of(kv_cache_ptr));
    }, py::arg("handle"), py::arg("kv_cache_ptr"));

    m.def("kv_cache_rollback",
          [](int handle, int64_t kv_cache_ptr, int n_tokens) {
              wisp_kv_cache_rollback(engine_of(handle),
                                     kv_of(kv_cache_ptr), n_tokens);
          },
          py::arg("handle"), py::arg("kv_cache_ptr"), py::arg("n_tokens"));

    /* --- Cache introspection ---------------------------------------- */
    m.def("cache_stats", [](int handle) {
        WispEngine* eng = engine_of(handle);
        uint64_t v, r, s;
        double rate;
        wisp_cache_stats(eng, &v, &r, &s, &rate);
        py::dict d;
        d["vram_hits"] = (int64_t)v;
        d["ram_hits"] = (int64_t)r;
        d["ssd_hits"] = (int64_t)s;
        d["hit_rate"] = rate;
        return d;
    }, py::arg("handle"));

    m.def("cache_clear", [](int handle) {
        WispEngine* eng = engine_of(handle);
        py::gil_scoped_release release;
        wisp_cache_clear_all(eng);
    }, py::arg("handle"));

    m.def("ram_trim", [](int handle, int count) -> int {
        WispEngine* eng = engine_of(handle);
        py::gil_scoped_release release;
        return wisp_ram_trim(eng, count);
    }, py::arg("handle"), py::arg("count"));

    /* --- Expert management ------------------------------------------ */
    m.def("expert_prefetch_hint",
          [](int handle, int layer_idx, const std::vector<int>& expert_ids) {
              WispEngine* eng = engine_of(handle);
              wisp_expert_prefetch_hint(eng, layer_idx, expert_ids.data(),
                                        (int)expert_ids.size());
          },
          py::arg("handle"), py::arg("layer_idx"), py::arg("expert_ids"));

    /* --- System info ------------------------------------------------- */
    m.def("get_vram_used_bytes", [](int handle) -> int64_t {
        return (int64_t)wisp_vram_used(engine_of(handle));
    }, py::arg("handle"));

    m.def("get_ram_used_bytes", [](int handle) -> int64_t {
        return (int64_t)wisp_ram_used(engine_of(handle));
    }, py::arg("handle"));

    m.def("get_tok_per_sec", [](int handle) -> double {
        return wisp_tok_per_sec(engine_of(handle));
    }, py::arg("handle"));

    /* --- Self-tests (pytest hooks) ----------------------------------- */
    m.def("_selftest_lru", []() -> bool {
        return wisp_selftest_lru() == 1;
    });
    m.def("_selftest_double_buffer", []() -> bool {
        py::gil_scoped_release release;
        return wisp_selftest_double_buffer() == 1;
    });

    /* Byte-layout cross-check: parse + dequantize an expert .bin with the
     * C engine's own code so tests can diff it against the Python packer. */
    m.def("_debug_expert_probe",
          [](const std::string& path, int mat, int n) {
              std::vector<float> vals((size_t)(n > 0 ? n : 1));
              WispExpertMeta meta = {};
              WispErrCtx err = {};
              WispError e = wisp_debug_expert_probe(
                  path.c_str(), mat, n, vals.data(), &meta, &err);
              if (e != WISP_OK) raise_wisp(err);
              size_t total = (size_t)meta.rows[mat] * meta.cols[mat];
              if ((size_t)n > total) vals.resize(total);
              py::dict d;
              d["rows"] = std::vector<int>{
                  (int)meta.rows[0], (int)meta.rows[1], (int)meta.rows[2]};
              d["cols"] = std::vector<int>{
                  (int)meta.cols[0], (int)meta.cols[1], (int)meta.cols[2]};
              d["group_size"] = (int)meta.group_size;
              d["total_bytes"] = (int64_t)meta.total_bytes;
              d["values"] = vals;
              return d;
          },
          py::arg("path"), py::arg("mat"), py::arg("n"));

    m.attr("__version__") = "1.0.0";
#ifdef WISP_NO_CUDA
    m.attr("cuda_enabled") = false;
#else
    m.attr("cuda_enabled") = true;
#endif
}
