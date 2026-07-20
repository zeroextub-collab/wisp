"""
wisp.speculative.sampler — temperature / top-k / top-p sampling.

One sampling implementation shared by the main generation loop and the
drafter, so draft and verify distributions never diverge on filtering.
"""

from __future__ import annotations

from dataclasses import dataclass

import torch
import torch.nn.functional as F


@dataclass
class SamplerConfig:
    temperature: float = 0.7
    top_k:       int = 0        # 0 = disabled
    top_p:       float = 1.0    # 1.0 = disabled
    repetition_penalty: float = 1.0


def apply_repetition_penalty(logits: torch.Tensor,
                             prev_ids: list[int],
                             penalty: float) -> torch.Tensor:
    if penalty == 1.0 or not prev_ids:
        return logits
    logits = logits.clone()
    ids = torch.tensor(sorted(set(prev_ids)), dtype=torch.long,
                       device=logits.device)
    vals = logits[..., ids]
    logits[..., ids] = torch.where(vals > 0, vals / penalty, vals * penalty)
    return logits


def filter_logits(logits: torch.Tensor, top_k: int = 0,
                  top_p: float = 1.0) -> torch.Tensor:
    """Standard nucleus + top-k filtering (masked positions -> -inf)."""
    logits = logits.clone()
    vocab = logits.shape[-1]

    if top_k > 0:
        k = min(top_k, vocab)
        kth = torch.topk(logits, k, dim=-1).values[..., -1, None]
        logits[logits < kth] = float("-inf")

    if 0.0 < top_p < 1.0:
        sorted_logits, sorted_idx = torch.sort(logits, descending=True, dim=-1)
        probs = F.softmax(sorted_logits, dim=-1)
        cum = torch.cumsum(probs, dim=-1)
        remove = cum - probs > top_p          # keep first token past threshold
        sorted_logits[remove] = float("-inf")
        logits = torch.full_like(logits, float("-inf")).scatter(
            -1, sorted_idx, sorted_logits)

    return logits


def sample_token(logits: torch.Tensor,
                 config: SamplerConfig,
                 prev_ids: list[int] | None = None) -> int:
    """
    Sample one token id from raw logits [vocab] or [1, vocab].
    temperature == 0 -> greedy argmax.
    """
    if logits.dim() == 2:
        logits = logits[-1]
    logits = logits.float()

    if prev_ids:
        logits = apply_repetition_penalty(
            logits, prev_ids, config.repetition_penalty)

    if config.temperature <= 0.0:
        return int(torch.argmax(logits).item())

    logits = logits / max(config.temperature, 1e-6)
    logits = filter_logits(logits, config.top_k, config.top_p)
    probs = F.softmax(logits, dim=-1)
    if not torch.isfinite(probs).all() or probs.sum() <= 0:
        return int(torch.argmax(logits).item())  # degenerate filter — greedy
    return int(torch.multinomial(probs, num_samples=1).item())
