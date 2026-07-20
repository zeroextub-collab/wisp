# Credits

WISP would not exist without Colibrì.

## Colibrì — The Inspiration

**JustVugg** built Colibrì in July 2026 — a 2,400-line pure-C engine
that proved a 744B parameter model could run on 25GB of consumer RAM
by streaming expert weights from disk. Before Colibrì, everyone said
this was impossible. After Colibrì, we built WISP.

**jlnsrk** converted the GLM-5.2 weights to a format the community
could actually use, enabling the entire local MoE movement.

**matey-0 (Mateo Grgić)** discovered that the MTP head needed to run
at int8 (not int4), fixing speculative decoding from 0-4% acceptance
to 39-59% — turning it from broken to genuinely useful.

GitHub: https://github.com/JustVugg/colibri

WISP shares zero code with Colibrì. It is a complete independent
reimplementation — universal model support, CUDA acceleration,
multi-GPU strategies, automatic configuration. JustVugg showed us
what was possible.

## WISP

Built by **Saksham (Zero_planck)**
GitHub: https://github.com/zeroextub-collab/wisp

## Research

- **Leviathan, Kalman, Matias (2023)** — *Fast Inference from
  Transformers via Speculative Decoding*: the rejection-sampling
  scheme in `wisp/speculative/verifier.py`.
- **Dai et al. (2024)** — the DeepSeek MoE architecture: fine-grained
  experts, shared experts, and the routing design WISP's tier system
  is built around.
- **DeepSeek-AI** — Multi-head Latent Attention and the absorbed-
  projection inference trick that makes the compressed KV cache in
  `csrc/cuda/attention.cu` practical.
- **GLM team** — GLM-5.2 and the IndexShare architecture.
- **Moonshot AI** — Kimi K3, KDA hybrid linear attention, and
  Stable LatentMoE with Quantile Balancing.
- **The llama.cpp community** — years of proof that consumer hardware
  deserves frontier models.
