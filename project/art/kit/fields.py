"""The kit's pieces for routes: tall grass (and the sprite the game draws over the player's feet in it), ledges you
hop down, stone steps through them, and lily pads and reeds for ponds. All in the ground palette (bank 0).

Tall grass is darker than the lawn: tufts of blades in two staggered rows, each blade dark at its root, lit at its
tip (light from the left). It tiles every 16 pixels. The sprite's frames are the tall grass itself, so it blends:
frame 0 is the front tufts (rows 9-15) the player stands behind; frame 1 the same tufts pushed apart; frames 2-4
the tufts settling while two bits of leaf fly up and fade (the game plays 1, 2, 3, 4, 0).

A ledge is an earth bank facing south under a grass lip, with its shadow on the grass below; the ends round off
(edge variants by the neighbours that are ledge too: 2 east, 8 west). Index 0 is transparent: the grass shows.
"""
import random

import numpy as np

# ground palette (kit.P0) indices
OUT, G0, G1, GD, GM, GL, GH, SD, SM, SL, KD, KM, KL, TR, CR = range(1, 16)
BAYER = [[0, 8, 2, 10], [12, 4, 14, 6], [3, 11, 1, 9], [15, 7, 13, 5]]

# a clump of tall grass, 8x8, drawn by hand: three pointed blades lit on the left, outlined, dark at the root
# (. transparent, o outline, d dark, m mid, l lit, h tip)
CLUMP = ["...h....",
         ".h.lo.h.",
         ".lolmolo",
         "olmlmomo",
         "olmmmmmo",
         ".olmmmdo",
         ".odmmddo",
         "..oddd o"]
# pushed apart as someone walks in (the sprite's frame 1)
PARTED = ["........",
          "........",
          "h......h",
          "lo....ol",
          "olo..olo",
          ".olmmlo.",
          ".odmmdo.",
          "..oddo.."]
INK = {"o": G0, "d": GD, "m": GM, "l": GL, "h": GH}
BACK = [(0, 0), (8, 0)]  # top-left corners of the clumps: the back row, then the front row over it
FRONT = [(4, 8), (12, 8)]


def _stamp(t, art, x0, y0, top=0):
    for j, row in enumerate(art):
        for i, ch in enumerate(row):
            if ch in INK and y0 + j >= top:
                t[(y0 + j) % 16, (x0 + i) % 16] = INK[ch]


def _ground() -> np.ndarray:
    t = np.zeros((16, 16), np.uint8)
    for y in range(16):
        for x in range(16):
            t[y, x] = GD if BAYER[y % 4][x % 4] > 10 else G1
    return t


def tall_grass(variant: int = 0) -> np.ndarray:
    """One block of tall grass; variants flip a back clump (the front row, which the sprite copies, stays)."""
    t = _ground()
    for k, (x0, y0) in enumerate(BACK):
        art = [r[::-1] for r in CLUMP] if (variant == 1 and k == 0) or (variant == 2 and k == 1) else CLUMP
        _stamp(t, art, x0, y0)
    for x0, y0 in FRONT:
        _stamp(t, CLUMP, x0, y0)
    return t


def tall_grass_fx() -> np.ndarray:
    """The sprite over the player's feet: five 16x16 frames side by side (16x80)."""
    full = tall_grass()
    frames = []
    f0 = np.zeros((16, 16), np.uint8)
    f0[9:] = full[9:]
    # 1: the front clumps pushed apart
    f1 = np.zeros((16, 16), np.uint8)
    f1[13:] = _ground()[13:]
    for x0, y0 in FRONT:
        _stamp(f1, PARTED, x0, y0)
    frames += [f0, f1]
    leaves = [((4, 7), (11, 6)), ((3, 4), (12, 3)), ((2, 1), (13, 1))]
    for i, pts in enumerate(leaves):
        f = np.zeros((16, 16), np.uint8)
        f[10 + (i == 0):] = full[10 + (i == 0):]
        for (x, y) in pts:
            c = (GH, GL, GM)[i]
            f[y, x] = c
            f[y, x + 1] = c if i < 2 else 0
            if i == 0:
                f[y + 1, x] = GL
        frames.append(f)
    return np.concatenate(frames, axis=1)


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
