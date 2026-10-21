"""The kit's pond water, from a native pixel pack (pond/: made with another AI from a brief, "option C, gentle
ripples"): open water in three sparkle variants, the eight shores and outer corners of a pond, four inside corners
and a one-block pool, each 16x16 in eight frames, in the water palette (bank 1). Land is transparent.

Each shore keeps to the outer 6 pixels of its side and the rest is the open water, so any block of a pond is put
together from them: open water, then the band of each side that has land (its outer corners from the corner pieces
where two sides meet land), then an inside corner where both sides are water but the diagonal isn't.
"""
from pathlib import Path

import numpy as np
from PIL import Image

import water

HERE = Path(__file__).resolve().parent / "pond"
FRAMES = 8
_strips: dict[str, np.ndarray] = {}


def _strip(name: str) -> np.ndarray:
    """A piece's eight frames as palette indices (water.PW; 0 transparent)."""
    if name not in _strips:
        with Image.open(HERE / f"{name}.png") as im:
            a = np.array(im.convert("RGBA"))
        lut = {c: i for i, c in enumerate(water.PW) if i}
        out = np.zeros(a.shape[:2], np.uint8)
        for y in range(a.shape[0]):
            for x in range(a.shape[1]):
                r, g, b, al = (int(v) for v in a[y, x])
                if al:
                    if (r, g, b) not in lut:
                        raise SystemExit(f"pond/{name}.png: ({r},{g},{b}) is not in the water palette")
                    out[y, x] = lut[(r, g, b)]
        _strips[name] = out
    return _strips[name]


def _frame(name: str, k: int) -> np.ndarray:
    return _strip(name)[:, 16 * k:16 * k + 16]


SIDES = {1: ("N", np.s_[0:6, :]), 2: ("E", np.s_[:, 10:16]), 4: ("S", np.s_[10:16, :]), 8: ("W", np.s_[:, 0:6])}
OUTER = {(1, 2): ("NE", np.s_[0:6, 10:16]), (4, 2): ("SE", np.s_[10:16, 10:16]),
         (4, 8): ("SW", np.s_[10:16, 0:6]), (1, 8): ("NW", np.s_[0:6, 0:6])}
INNER = {1: ("in_NE", np.s_[0:6, 10:16]), 2: ("in_SE", np.s_[10:16, 10:16]),
         4: ("in_SW", np.s_[10:16, 0:6]), 8: ("in_NW", np.s_[0:6, 0:6])}


def piece(mask: int, frame: int, variant: int = 0, corners: int = 0) -> np.ndarray:
    """The pond block whose water neighbours are ``mask`` (1 N, 2 E, 4 S, 8 W), with inside corners ``corners``
    (1 NE, 2 SE, 4 SW, 8 NW: both sides water, the diagonal land), at ``frame``."""
    if mask == 0:
        return _frame("single", frame).copy()
    t = _frame(("center", "center_b", "center_c")[variant % 3], frame).copy()
    for bit, (name, region) in SIDES.items():
        if not mask & bit:
            t[region] = _frame(name, frame)[region]
    for (a, b), (name, region) in OUTER.items():
        if not mask & a and not mask & b:
            t[region] = _frame(name, frame)[region]
    for bit, (name, region) in INNER.items():
        if corners & bit:
            t[region] = _frame(name, frame)[region]
    return t
