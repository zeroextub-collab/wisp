"""
wisp.converter.quantizer — group-wise int4 quantization utilities.

The packing here MUST stay bit-compatible with the CUDA dequant kernel in
csrc/cuda/expert_loader.cu:

    dequant:  value = (nibble - 8) * scale + zero
    packing:  two int4 values per byte, LOW nibble = even index,
              HIGH nibble = odd index
    groups :  `group_size` consecutive elements (flattened row-major)
              share one fp16 scale and one fp16 zero

Quantization scheme (asymmetric, centered):
    zero  = (max + min) / 2
    scale = (max - min) / 15          (15 = int4 range steps)
    q     = clamp(round((x - zero) / scale) + 8, 0, 15)
"""

from __future__ import annotations

from dataclasses import dataclass

import torch


@dataclass
class QuantizedTensor:
    packed: torch.Tensor   # uint8, ceil(n/2) bytes, low nibble first
    scales: torch.Tensor   # fp16, one per group
    zeros:  torch.Tensor   # fp16, one per group
    rows:   int
    cols:   int
    group_size: int

    @property
    def n_elements(self) -> int:
        return self.rows * self.cols

    @property
    def nbytes(self) -> int:
        return (self.packed.numel()
                + self.scales.numel() * 2
                + self.zeros.numel() * 2)


def quantize_int4(weight: torch.Tensor, group_size: int = 64) -> QuantizedTensor:
    """Group-wise asymmetric int4 quantization of a 2D weight matrix."""
    if weight.dim() != 2:
        raise ValueError(f"quantize_int4 expects 2D weight, got {tuple(weight.shape)}")
    if group_size <= 0:
        raise ValueError(f"group_size must be positive, got {group_size}")

    rows, cols = weight.shape
    flat = weight.detach().to(torch.float32).reshape(-1)
    n = flat.numel()

    # Pad to a whole number of groups (pad values echo the last element so
    # they never widen the final group's range)
    n_groups = (n + group_size - 1) // group_size
    padded = n_groups * group_size
    if padded != n:
        flat = torch.cat([flat, flat[-1].repeat(padded - n)])

    groups = flat.view(n_groups, group_size)
    gmax = groups.max(dim=1).values
    gmin = groups.min(dim=1).values
    zeros = (gmax + gmin) / 2.0
    scales = (gmax - gmin) / 15.0
    scales = torch.clamp(scales, min=1e-8)  # all-constant group -> avoid /0

    q = torch.round((groups - zeros.unsqueeze(1)) / scales.unsqueeze(1)) + 8
    q = torch.clamp(q, 0, 15).to(torch.uint8).reshape(-1)[:n]

    # Pack two nibbles per byte: low nibble = even index, high = odd index
    if n % 2 != 0:
        q = torch.cat([q, torch.zeros(1, dtype=torch.uint8)])
    lo = q[0::2]
    hi = q[1::2]
    packed = (lo | (hi << 4)).contiguous()

    return QuantizedTensor(
        packed=packed,
        scales=scales.to(torch.float16).contiguous(),
        zeros=zeros.to(torch.float16).contiguous(),
        rows=rows, cols=cols, group_size=group_size,
    )


def dequantize_int4(qt: QuantizedTensor) -> torch.Tensor:
    """Exact inverse of the packing above — mirrors the CUDA kernel math."""
    n = qt.n_elements
    packed = qt.packed
    lo = (packed & 0x0F).to(torch.int32)
    hi = (packed >> 4).to(torch.int32)
    q = torch.empty(packed.numel() * 2, dtype=torch.int32)
    q[0::2] = lo
    q[1::2] = hi
    q = q[:n]

    idx = torch.arange(n)
    g = idx // qt.group_size
    scales = qt.scales.to(torch.float32)[g]
    zeros = qt.zeros.to(torch.float32)[g]
    out = (q.to(torch.float32) - 8.0) * scales + zeros
    return out.view(qt.rows, qt.cols).to(torch.float16)


def quantization_error(weight: torch.Tensor, group_size: int = 64) -> float:
    """Mean absolute reconstruction error — sanity metric for `wisp convert`."""
    qt = quantize_int4(weight, group_size)
    recon = dequantize_int4(qt).to(torch.float32)
    return (weight.to(torch.float32) - recon).abs().mean().item()
