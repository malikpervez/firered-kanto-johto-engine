"""Blocks from 16-piece native pixel packs (made with another AI from a brief): the pond and the sea (water.py), the
dressed-stone paving (paving/) and the rocky cliffs (Route 22's). A pack has the material in three variants
(center, center_b, center_c), its edge on each side (N, E, S, W: the outside ground is on that side), its outer
corners (NE, SE, SW, NW), its inside corners (in_NE, ...: the outside ground only diagonally) and a one-block piece
(single), each 16x16.

Each edge keeps to the outer 6 pixels of its side and the rest is the material, so any block is put together from
them: the material, then the band of each side that has outside ground (its outer corners from the corner pieces
where two sides meet it), then an inside corner where both sides are the material but the diagonal isn't.
"""
from pathlib import Path

import numpy as np
from PIL import Image

PIECES = ("center", "center_b", "center_c", "N", "NE", "E", "SE", "S", "SW", "W", "NW",
          "in_NE", "in_SE", "in_SW", "in_NW", "single")
SIDES = {1: ("N", np.s_[0:6, :]), 2: ("E", np.s_[:, 10:16]), 4: ("S", np.s_[10:16, :]), 8: ("W", np.s_[:, 0:6])}
OUTER = {(1, 2): ("NE", np.s_[0:6, 10:16]), (4, 2): ("SE", np.s_[10:16, 10:16]),
         (4, 8): ("SW", np.s_[10:16, 0:6]), (1, 8): ("NW", np.s_[0:6, 0:6])}
INNER = {1: ("in_NE", np.s_[0:6, 10:16]), 2: ("in_SE", np.s_[10:16, 10:16]),
         4: ("in_SW", np.s_[10:16, 0:6]), 8: ("in_NW", np.s_[0:6, 0:6])}


def compose(get, mask: int, variant: int = 0, corners: int = 0) -> np.ndarray:
    """The block whose neighbours of the same material are ``mask`` (1 N, 2 E, 4 S, 8 W), with inside corners
    ``corners`` (1 NE, 2 SE, 4 SW, 8 NW: both sides the material, the diagonal not). ``get(piece)`` gives a piece's
    16x16 palette indices."""
    if mask == 0:
        return get("single").copy()
    t = get(("center", "center_b", "center_c")[variant % 3]).copy()
    for bit, (name, region) in SIDES.items():
        if not mask & bit:
            t[region] = get(name)[region]
    for (a, b), (name, region) in OUTER.items():
        if not mask & a and not mask & b:
            t[region] = get(name)[region]
    for bit, (name, region) in INNER.items():
        if corners & bit:
            t[region] = get(name)[region]
    return t


def load(path: Path, palette) -> np.ndarray:
    """A pack's picture as indices of ``palette`` (by colour; transparent pixels are 0)."""
    with Image.open(path) as im:
        a = np.array(im.convert("RGBA"))
    lut = {tuple(c): i for i, c in enumerate(palette) if i}
    out = np.zeros(a.shape[:2], np.uint8)
    for y in range(a.shape[0]):
        for x in range(a.shape[1]):
            r, g, b, al = (int(v) for v in a[y, x])
            if al:
                if (r, g, b) not in lut:
                    raise SystemExit(f"{path}: ({r},{g},{b}) is not in its palette")
                out[y, x] = lut[(r, g, b)]
    return out


def corners_in(g, chars, plain=None) -> set[tuple[int, int]]:
    """(mask, corners) of the blocks of ``chars`` in grid ``g`` (its first, or ``plain``, the plain material) with
    an inside corner, as pae map paint works them out (map edges count as the material)."""
    h, w = len(g), len(g[0])
    plain = plain or chars[0]

    def same(x, y):
        return not (0 <= y < h and 0 <= x < w) or g[y][x] in chars
    out = set()
    for y in range(h):
        for x in range(w):
            if g[y][x] != plain:
                continue
            mask = sum(bit for bit, (dx, dy) in ((1, (0, -1)), (2, (1, 0)), (4, (0, 1)), (8, (-1, 0)))
                       if same(x + dx, y + dy))
            corners = sum(bit for bit, (dx, dy), sides in ((1, (1, -1), 3), (2, (1, 1), 6), (4, (-1, 1), 12),
                                                           (8, (-1, -1), 9))
                          if mask & sides == sides and not same(x + dx, y + dy))
            if corners:
                out.add((mask, corners))
    return out
