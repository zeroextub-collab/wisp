"""wisp.speculative — same-family speculative decoding."""

from .sampler import SamplerConfig, sample_token, filter_logits
from .verifier import SpeculativeDecoder

__all__ = [
    "SamplerConfig", "sample_token", "filter_logits",
    "SpeculativeDecoder",
]
