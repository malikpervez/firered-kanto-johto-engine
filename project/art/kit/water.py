"""The kit's water, in its own palette (bank 1), animated in eight frames, from two native pixel packs made with
another AI from a brief: the pond (pond/, "gentle ripples", an earth bank) and the sea (sea/, "staggered swells",
a rocky cliff, and two sea rocks). Each has open water in three variants, the shores and outer corners on each side,
four inside corners and a one-block pool, each 16x16 in eight frames. Land is transparent: the grass shows.

Each shore keeps to the outer 6 pixels of its side and the rest is the open water, so any block of a pond or the
sea is put together from them, as autotile.py does for every such pack.
"""
from pathlib import Path

import numpy as np
from PIL import Image

import autotile

HERE = Path(__file__).resolve().parent
PW = [(0, 0, 0), (16, 24, 40), (96, 64, 40), (152, 112, 72), (200, 168, 112), (24, 48, 104), (32, 72, 144),
      (48, 104, 184), (72, 136, 208), (112, 172, 228), (120, 196, 212), (208, 236, 244), (248, 248, 248),
      (72, 72, 88), (120, 120, 128), (176, 176, 168)]
FRAMES = 8
_strips: dict[tuple[str, str], np.ndarray] = {}


def _strip(pack: str, name: str) -> np.ndarray:
    """A piece's eight frames as palette indices (PW; 0 transparent)."""
    if (pack, name) not in _strips:
        with Image.open(HERE / pack / f"{name}.png") as im:
            a = np.array(im.convert("RGBA"))
        lut = {c: i for i, c in enumerate(PW) if i}
        out = np.zeros(a.shape[:2], np.uint8)
        for y in range(a.shape[0]):
            for x in range(a.shape[1]):
                r, g, b, al = (int(v) for v in a[y, x])
                if al:
                    if (r, g, b) not in lut:
                        raise SystemExit(f"{pack}/{name}.png: ({r},{g},{b}) is not in the water palette")
                    out[y, x] = lut[(r, g, b)]
        _strips[pack, name] = out
    return _strips[pack, name]


def frame(pack: str, name: str, k: int) -> np.ndarray:
    """Frame ``k`` of a pack's piece as it was drawn (e.g. the sea's "rock_a")."""
    return _strip(pack, name)[:, 16 * k:16 * k + 16].copy()


def piece(pack: str, mask: int, k: int, variant: int = 0, corners: int = 0) -> np.ndarray:
    """The block of ``pack`` ("pond" or "sea") whose water neighbours are ``mask`` (1 N, 2 E, 4 S, 8 W), with inside
    corners ``corners`` (1 NE, 2 SE, 4 SW, 8 NW: both sides water, the diagonal land), at frame ``k``
    (autotile.py)."""
    return autotile.compose(lambda name: frame(pack, name, k), mask, variant, corners)
