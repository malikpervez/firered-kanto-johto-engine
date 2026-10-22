"""The kit's trees, in their own palette (bank 3): the Sunlit Broadleaf pack (broadleaf/, native pixel art made
with another AI from a brief, v0.4; the kit keeps its trees, forest cells, palette and notes, not its previews and
sources). Every tree is 32x32, a 2x2 block cell on the even grid: forest cells in 47 shapes, each in three crown
variants that can be mixed (their outer five pixels are the same), and three standalone trees. Transparent pixels
show the ground under them. The pack has no bush: the bushes are drawn here, in the pack's colours. make_art.py
puts them on the "trees" sheet."""
import math
import random
from pathlib import Path

import numpy as np

import autotile

HERE = Path(__file__).resolve().parent / "broadleaf"
VARIANTS = ("a", "b", "c")
STANDALONE = {"round_tree": "round_crown", "offset_tree": "offset_crown", "broad_tree": "broad_crown"}


def _palette() -> list[tuple[int, int, int]]:
    out = []
    for line in (HERE / "palette.gpl").read_text().splitlines():
        parts = line.split()
        if len(parts) >= 3 and all(p.isdigit() for p in parts[:3]):
            out.append(tuple(int(p) for p in parts[:3]))
    return out[:16]


PT = _palette()  # index 0 is transparent


def forest(mask: int = 15, corners: int = 0, variant: str = "a") -> np.ndarray:
    """The forest cell whose neighbouring cells are forest at ``mask`` (1 north, 2 east, 4 south, 8 west, as pae map
    paint counts them), with inside corners ``corners`` (1 NE, 2 SE, 4 SW, 8 NW: both sides forest, the diagonal
    not). The pack numbers its shapes by the neighbours outside the forest instead, diagonals from 16."""
    shape = (~mask & 15) | (corners << 4)
    return autotile.load(HERE / "forest" / variant / f"mask_{shape:03d}.png", PT)


def tree(name: str) -> np.ndarray:
    """A standalone tree (a name in ``STANDALONE``)."""
    return autotile.load(HERE / "trees" / f"{STANDALONE[name]}.png", PT)


# the bushes: drawn in these colours, then each takes the pack's nearest
_BUSH = {1: (16, 24, 32), 2: (32, 72, 64), 3: (40, 88, 48), 4: (64, 120, 56), 5: (96, 156, 64), 6: (148, 196, 92),
         7: (64, 136, 64)}
B_OUT, B_DARK, LF1, LF2, LF3, LF4, GSH = range(1, 8)
LEAF = [B_DARK, LF1, LF2, LF3, LF4]


def _hash(x, y, seed=0):
    v = (x * 374761393 + y * 668265263 + seed * 2147483647) & 0xFFFFFFFF
    v = (v ^ (v >> 13)) * 1274126177 & 0xFFFFFFFF
    return ((v ^ (v >> 16)) & 0xFFFF) / 65535.0


def _shade(levels, v):
    v = min(max(v, 0.0), 0.999)
    return levels[int(v * len(levels))]


def ground_shadow(t, cx, cy, rx, ry):
    h, w = t.shape
    for y in range(h):
        for x in range(w):
            d = ((x + 0.5 - cx) / rx) ** 2 + ((y + 0.5 - cy) / ry) ** 2
            if t[y, x] == 0 and d <= 1.0 and (d < 0.6 or (x + y) % 2 == 0):
                t[y, x] = GSH


def _clusters(rng, n, cx, cy, rx, ry, rmin, rmax):
    out = []
    for _ in range(n):
        a = rng.uniform(0, 2 * math.pi)
        rr = math.sqrt(rng.uniform(0, 1))
        out.append((cx + rr * rx * math.cos(a), cy + rr * ry * math.sin(a), rng.uniform(rmin, rmax)))
    return sorted(out, key=lambda c: c[1])  # back (top) first, front (bottom) last


def leafy(t, owner, clusters, seed, levels=LEAF, centre=None):
    h, w = t.shape
    gcx, gcy, grad = centre or (w / 2, h / 2, w / 2)
    for i, (ccx, ccy, r) in enumerate(clusters):
        for y in range(max(0, int(ccy - r - 1)), min(h, int(ccy + r + 2))):
            for x in range(max(0, int(ccx - r - 1)), min(w, int(ccx + r + 2))):
                nx, ny = (x + 0.5 - ccx) / r, (y + 0.5 - ccy) / r
                d = nx * nx + ny * ny
                bump = 0.12 * math.sin(math.atan2(ny, nx) * 6 + i)
                if d > (1 + bump) ** 2:
                    continue
                nz = math.sqrt(max(0.0, 1 - min(d, 1)))
                gx, gy = (x + 0.5 - gcx) / grad, (y + 0.5 - gcy) / grad
                light = 0.5 + 0.22 * (-0.55 * nx - 0.65 * ny + 0.5 * nz) + 0.3 * (-0.5 * gx - 0.7 * gy)
                light += (_hash(x, y, seed + i) - 0.5) * 0.22
                if ((x + y * 2 + i) % 5 == 0):
                    light -= 0.1  # leaf texture
                t[y, x] = _shade(levels, light)
                owner[y, x] = i + 1
    return t


def leaf_outline(t, owner):
    """The crown's silhouette outlined; inside, a front clump's top edge catches light and the clump behind it
    gets its shadow."""
    h, w = t.shape
    inside = owner > 0
    out = t.copy()
    for y in range(h):
        for x in range(w):
            if not inside[y, x]:
                continue
            nb = [(y + 1 >= h or not inside[y + 1, x]), (x + 1 >= w or not inside[y, x + 1]),
                  (y == 0 or not inside[y - 1, x]), (x == 0 or not inside[y, x - 1])]
            if nb[0] or nb[1]:
                out[y, x] = B_OUT
            elif nb[2] or nb[3]:
                out[y, x] = LF1 if (nb[3] and not nb[2]) else B_OUT if y > h * 0.4 else LF1
            elif owner[y + 1, x] > owner[y, x] and owner[y + 1, x] != owner[y, x]:
                out[y, x] = B_DARK  # behind a clump in front
            elif owner[y - 1, x] < owner[y, x]:
                out[y, x] = LF4 if t[y, x] in (LF3, LF4) else LF3  # a clump's lit top edge
    return out


def _nearest(rgb) -> int:
    return min(range(1, 16), key=lambda i: sum((a - b) ** 2 for a, b in zip(PT[i], rgb)))


def bush(seed: int = 2) -> np.ndarray:
    t = np.zeros((16, 16), np.uint8)
    owner = np.zeros((16, 16), np.int32)
    ground_shadow(t, 8.5, 14, 7, 1.8)
    rng = random.Random(seed)
    cl = _clusters(rng, 14, 8, 9, 4.8, 3.2, 2.0, 2.8)
    leafy(t, owner, cl, seed, centre=(8, 9, 6))
    t = leaf_outline(t, owner)
    lut = np.array([0] + [_nearest(_BUSH[i]) for i in range(1, 8)], np.uint8)
    return lut[t]
