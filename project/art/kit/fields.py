"""The kit's pieces for routes: ledges you hop down, stone steps through them, and lily pads and reeds for ponds.
All in the ground palette (bank 0). (Tall grass is drawn natively in tall_grass/, in its own palette: see kit.py.)

A ledge is an earth bank facing south under a grass lip, with its shadow on the grass below; the ends round off
(edge variants by the neighbours that are ledge too: 2 east, 8 west). Index 0 is transparent: the grass shows.
"""
import random

import numpy as np

# ground palette (kit.P0) indices
OUT, G0, G1, GD, GM, GL, GH, SD, SM, SL, KD, KM, KL, TR, CR = range(1, 16)
BAYER = [[0, 8, 2, 10], [12, 4, 14, 6], [3, 11, 1, 9], [15, 7, 13, 5]]

def _wobble(seed: int, lo: int, hi: int) -> list[int]:
    r = random.Random(seed)
    v = [r.randint(lo, hi) for _ in range(16)]
    return [max(lo, min(hi, round((v[i - 1] + 2 * v[i] + v[(i + 1) % 16]) / 4))) for i in range(16)]


def ledge(mask: int) -> np.ndarray:
    """A south-facing earth bank (the player hops down it going south): a grass overhang, the earth face, a dark
    foot and its shadow on the grass below."""
    t = np.zeros((16, 16), np.uint8)
    lip = _wobble(61, 3, 4)  # where the grass overhang ends and the face begins
    foot = _wobble(67, 12, 13)  # the face's foot
    for x in range(16):
        # the ends round off: the bank gets lower toward a side that isn't ledge
        inset = 0
        if not mask & 8 and x < 6:
            inset = (6 - x) * 3 // 2
        if not mask & 2 and x > 9:
            inset = max(inset, (x - 9) * 3 // 2)
        y0, y1 = lip[x] + inset, foot[x]
        if y1 - y0 < 2:
            continue
        t[y0 - 2, x] = GH if (x + y0) % 3 else GL  # the grass overhang, lit along its edge
        t[y0 - 1, x] = GL
        t[y0, x] = GM if x % 4 else GD  # blades hanging over the face
        for y in range(y0 + 1, y1):
            d = (y - y0) / max(1, y1 - y0)
            c = SL if d < 0.2 else SM if d < 0.65 else SD
            if (x * 5 + y * 3) % 11 == 0 and 0.25 < d < 0.95:
                c = SD  # streaks in the earth
            if (x * 7 + y) % 13 == 0 and d < 0.5:
                c = SL
            if (x * 3 + y * 5) % 17 == 0 and 0.4 < d < 0.8:
                c = KM  # a pebble
            t[y, x] = c
        t[y1, x] = OUT
        for y in (y1 + 1, y1 + 2):  # its shadow on the grass below
            if y < 16 and (y == y1 + 1 or BAYER[y % 4][x % 4] > 7):
                t[y, x] = G0
    r = random.Random(71)
    for _ in range(6):  # longer blades hanging over the lip
        x = r.randrange(16)
        y0 = lip[x]
        if t[y0 + 1, x] in (SL, SM):
            t[y0 + 1, x] = GD
    return t


def steps(mask: int) -> np.ndarray:
    """Stone steps down through a ledge (walkable both ways); low walls of earth on the sides that are ledge."""
    t = np.zeros((16, 16), np.uint8)
    for k, y0 in enumerate((2, 6, 10)):
        t[y0:y0 + 4, 1:15] = KM
        t[y0, 1:15] = KL  # the lit tread edge
        t[y0 + 3, 1:15] = KD
        for x in range(2 + 3 * k % 4, 15, 5):
            t[y0 + 1:y0 + 3, x] = KD  # joints between the stones
    t[14, 1:15] = G0  # the bottom step's shadow
    for side, xs in ((8, range(0, 2)), (2, range(14, 16))):
        for x in xs:
            if mask & side:  # more steps that way: the stones go on
                t[2:14, x] = t[2:14, 7]
            else:  # a low stone wall against the ledge's end
                t[1:15, x] = KD
                t[1, x] = KL
    t[1, 2 if not mask & 8 else 0:14 if not mask & 2 else 16] = OUT
    return t


def lily() -> np.ndarray:
    """Lily pads with a cream flower, over water (the water shows through)."""
    t = np.zeros((16, 16), np.uint8)
    yy, xx = np.mgrid[0:16, 0:16]
    for cx, cy, r, notch in ((5.5, 6, 4.6, 1), (11.5, 11.5, 3.6, -1), (12.5, 3.5, 2.4, 1)):
        pad = (xx + 0.5 - cx) ** 2 + ((yy + 0.5 - cy) * 1.3) ** 2 <= r * r
        cut = (np.abs(yy + 0.5 - cy) < 0.8) & ((xx + 0.5 - cx) * notch > 0)
        pad &= ~cut
        t[pad] = GM
        t[pad & ((xx + 0.5 - cx) + (yy + 0.5 - cy) < -1)] = GL
        p = np.pad(pad, 1)
        edge = pad & ~(p[:-2, 1:-1] & p[2:, 1:-1] & p[1:-1, :-2] & p[1:-1, 2:])
        t[edge & (yy + 0.5 > cy)] = G0
        t[edge & (yy + 0.5 <= cy)] = GD
    # a flower on the big pad
    for dx, dy in ((0, -1), (-1, 0), (1, 0), (0, 1), (-1, -1), (1, -1)):
        t[5 + dy, 5 + dx] = CR
    t[5, 5] = SL
    return t


def reeds() -> np.ndarray:
    """Reeds and cattails standing in the water."""
    t = np.zeros((16, 16), np.uint8)
    for x, top, head in ((3, 2, True), (5, 5, False), (7, 1, True), (10, 4, False), (12, 3, True), (9, 7, False)):
        for y in range(top, 15):
            t[y, x] = GM if y < 11 else GD
        t[top, x] = GL
        if head:
            t[top + 1:top + 5, x] = TR
            t[top + 1:top + 5, x + 1 if x < 15 else x] = SD
            t[top, x] = GL
    for x in range(2, 14):  # the ripple where they stand
        if x % 3:
            t[15, x] = G0
    # leaves bending off the stems
    for x, y, d in ((5, 8, -1), (10, 9, 1), (7, 10, 1)):
        t[y, x + d] = GM
        t[y - 1, x + 2 * d] = GL
    return t
