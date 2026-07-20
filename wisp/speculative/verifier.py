"""
wisp.speculative.verifier — same-family speculative decoding
(Leviathan et al. 2023, "Fast Inference from Transformers via Speculative
Decoding").

The drafter generates K tokens; the main model verifies all K positions in
one parallel pass; rejection sampling keeps the output distribution EXACTLY
equal to the main model's — speculation never changes what the model says,
only how fast it says it. Net speedup: 2.2-2.8x at 45-55% acceptance.
"""

from __future__ import annotations

import torch
import torch.nn.functional as F


class SpeculativeDecoder:
    """
    Same-family speculative decoding (Leviathan et al. 2023).
    Drafter generates K tokens, main model verifies in one parallel pass.
    Net speedup: 2.2-2.8x on 45-55% acceptance rate.

    `drafter_engine` needs: decode_one(ids) -> logits [vocab]
    `main_engine`   needs: prefill(ids) -> logits [seq, vocab]
                           (per-position logits for the whole sequence)
    """

    def __init__(self, drafter_engine, main_engine, K: int = 3):
        self.drafter = drafter_engine
        self.main = main_engine
        self.K = K
        self.total_drafted = 0
        self.total_accepted = 0

    @property
    def acceptance_rate(self) -> float:
        if self.total_drafted == 0:
            return 0.0
        return self.total_accepted / self.total_drafted

    def step(self, input_ids: torch.Tensor,
             kv_cache=None, temperature: float = 1.0) -> torch.Tensor:
        """
        Returns 1 to K+1 new verified tokens (1D tensor).
        """
        # Step 1: Drafter generates K draft tokens (fast, small model)
        draft_tokens: list[torch.Tensor] = []
        draft_probs:  list[torch.Tensor] = []
        draft_ids = input_ids.clone()

        with torch.no_grad():
            for _ in range(self.K):
                logits = self.drafter.decode_one(draft_ids)
                probs = F.softmax(logits / max(temperature, 1e-6), dim=-1)
                token = torch.multinomial(probs, num_samples=1)
                draft_tokens.append(token.cpu())
                draft_probs.append(probs.cpu())
                draft_ids = torch.cat(
                    [draft_ids, token.to(draft_ids.device)], dim=-1)

        # Step 2: Main model verifies ALL K positions in ONE forward pass
        full_ids = torch.cat(
            [input_ids] + [t.to(input_ids.device) for t in draft_tokens],
            dim=-1)

        with torch.no_grad():
            main_logits = self.main.prefill(full_ids)   # [seq, vocab]
            main_probs = F.softmax(
                main_logits / max(temperature, 1e-6), dim=-1).cpu()

        # Step 3: Sequential rejection sampling
        accepted: list[torch.Tensor] = []
        n_input = input_ids.shape[-1]

        for i, (draft_tok, draft_p) in enumerate(zip(draft_tokens, draft_probs)):
            # Main model's distribution at this position:
            # logits at index (n_input + i - 1) predict token (n_input + i)
            main_p = main_probs[n_input + i - 1]

            tok_idx = int(draft_tok.item())
            accept_prob = min(
                1.0,
                (main_p[tok_idx] / (draft_p[tok_idx] + 1e-10)).item()
            )

            if torch.rand(1).item() < accept_prob:
                accepted.append(draft_tok)
                self.total_accepted += 1
            else:
                # Reject: sample from corrected distribution, then stop.
                # max(p_main - p_draft, 0) renormalized is exactly the
                # residual distribution that keeps the output == main model.
                corrected = torch.clamp(main_p - draft_p, min=0.0)
                corrected_sum = corrected.sum()
                if corrected_sum < 1e-10:
                    corrected = main_p  # fallback to main distribution
                else:
                    corrected = corrected / corrected_sum
                fallback = torch.multinomial(corrected, num_samples=1)
                accepted.append(fallback)
                self.total_drafted += self.K
                return torch.cat(accepted, dim=-1)

        # All K accepted — sample one bonus token from the main model's
        # distribution at the last position (free: already computed).
        bonus_probs = main_probs[-1]
        bonus = torch.multinomial(bonus_probs, num_samples=1)
        accepted.append(bonus)
        self.total_drafted += self.K

        return torch.cat(accepted, dim=-1)
