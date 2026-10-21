"""The concept Pallet's grass: one seamless field 64x64 pixels (4x4 blocks), painted as a pattern so it doesn't
repeat every block. In the ground palette (bank 0) with six greens:

* soft patches, lighter and darker, stippled where they meet;
* tufts of blades, each blade dark at its root and lit at its tip, leaning a little, packed close;
* a few clover leaves, dark gaps between tufts, and specks of light.

Everything is drawn on a torus (it wraps around both ways), so the four edges of the field meet seamlessly.
"""
import math
import random

import numpy as np

SIZE = 64  # pixels: 4x4 blocks
# ground palette (make_art.P0) indices for the greens, darkest first, and the daisy colours
G0, G1, GD, GM, GL, GH = 2, 3, 4, 5, 6, 7
SL, CR = 10, 15
GREENS = [G0, G1, GD, GM, GL, GH]
BAYER = [[0, 8, 2, 10], [12, 4, 14, 6], [3, 11, 1, 9], [15, 7, 13, 5]]


def _field() -> np.ndarray:
    """Soft light/dark patches (periodic over the field)."""
    yy, xx = np.mgrid[0:SIZE, 0:SIZE] / SIZE * 2 * math.pi
    f = (0.45 * np.sin(xx + 0.7) * np.sin(yy * 2 + 1.3) + 0.35 * np.sin(2 * xx - yy + 2.1)
         + 0.25 * np.sin(3 * yy + xx * 2 + 0.4) + 0.15 * np.sin(5 * xx + 3 * yy))
    return f / 1.2


def field(daisies: bool = False, seed: int = 7) -> np.ndarray:
    r = random.Random(seed)
    f = _field()
    t = np.zeros((SIZE, SIZE), np.uint8)
    for y in range(SIZE):
        for x in range(SIZE):
            v = 0.80 + 0.13 * f[y, x]  # 0..1 over the greens: mostly GL, GM in the darker patches
            lv = v * (len(GREENS) - 1)
            i = int(lv)
            if (lv - i) * 16 > BAYER[y % 4][x % 4]:
                i += 1
            t[y, x] = GREENS[max(2, min(5, i))]

    def put(x, y, c):
        t[y % SIZE, x % SIZE] = c
    # tufts of blades: roots dark, tips lit, leaning outward from the tuft's middle
    for _ in range(70):
        x0, y0 = r.randrange(SIZE), r.randrange(SIZE)
        lit = f[y0, x0] > -0.2
        for b in range(r.choice((2, 3, 3, 4))):
            bx = x0 + (b - 1)
            lean = -1 if bx < x0 else 1 if bx > x0 + 1 else 0
            h = r.choice((2, 3, 3, 4))
            for k in range(h):
                xx = bx + (lean if k >= h - 1 and h > 2 else 0)
                c = GD if k == 0 else GM if k < h - 1 else (GH if lit else GL)
                put(xx, y0 - k, c)
        put(x0, y0 + 1, G1)  # the shadow at the tuft's foot
        put(x0 + 1, y0 + 1, GD)
    # clover: three round leaves
    for _ in range(6):
        x0, y0 = r.randrange(SIZE), r.randrange(SIZE)
        for dx, dy in ((0, 0), (1, 0), (0, 1), (1, 1), (-1, 1), (-1, 2), (0, 2), (2, 1), (2, 2), (1, 2)):
            put(x0 + dx, y0 + dy, GM)
        put(x0, y0, GL)
        put(x0 - 1, y0 + 1, GL)
        put(x0 + 2, y0 + 1, GL)
        put(x0, y0 + 3, GD)
        put(x0 + 1, y0 + 3, GD)
    # specks of light
    for _ in range(40):
        put(r.randrange(SIZE), r.randrange(SIZE), GH)
    if daisies:
        for _ in range(14):
            x0, y0 = r.randrange(SIZE), r.randrange(SIZE)
            put(x0, y0 + 2, GD)  # its stem's shadow
            for dx, dy in ((1, 0), (-1, 0), (0, 1), (0, -1)):
                put(x0 + dx, y0 + dy, CR)
            put(x0, y0, SL)
    return t


def blocks(t: np.ndarray) -> list[np.ndarray]:
    """The field cut into its 16 blocks (row by row), as the 4x4 stamp's pieces."""
    return [t[by * 16:(by + 1) * 16, bx * 16:(bx + 1) * 16] for by in range(4) for bx in range(4)]
