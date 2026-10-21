"""The concept Pallet's water, in its own palette (bank 1), animated in eight frames.

Open water: a deep blue with darker patches, rows of wave crests (a bright crest over its lit face, a shadowed
trough above it) that drift sideways and bob, and sparkles that flash in turn. Every frame tiles with its
neighbours (all of it repeats every 16 pixels), and frame 8 would be frame 0 again, so the loop is seamless.

Shores: where a block's neighbour isn't water, the pond shows an earth bank under a grass lip (transparent, so the
grass ground shows), then a foam line whose gaps run along the shore, then shallow, lighter water. The sea shows
a rocky cliff instead, with surf at its foot. Each side's line depends only on that side, so a quadrant looks the
same in every variant that opens the same sides (fewer tiles).
"""
import math
import random

import numpy as np

PW = [(0, 0, 0), (16, 24, 40), (96, 64, 40), (152, 112, 72), (200, 168, 112), (24, 48, 104), (32, 72, 144),
      (48, 104, 184), (72, 136, 208), (112, 172, 228), (120, 196, 212), (208, 236, 244), (248, 248, 248),
      (72, 72, 88), (120, 120, 128), (176, 176, 168)]
W_OUT, BD, BM, BL, W0, W1, W2, W3, W4, W5, FOAM, SPARK, RD, RM, RL = range(1, 16)
FRAMES = 8
EDGE_SEED = {1: 101, 2: 202, 4: 303, 8: 404}

# wave rows: (base y, phase, amplitude, long crest or small ripple); they drift a block every FRAMES frames
WAVES = [(3.5, 0.00, 0.8, True), (11.5, 0.55, 0.9, True), (7.5, 0.30, 0.5, False), (15.5, 0.80, 0.5, False)]
FLECKS = {(2, 1), (9, 2), (14, 6), (5, 8), (11, 10), (1, 13), (7, 14), (13, 15), (4, 4), (10, 6)}
SPARKLES = [[(3, 3, 0), (12, 7, 4)], [(9, 2, 2), (4, 10, 6)], [(13, 12, 1), (7, 6, 5)]]


def _wobble(seed: int, lo: int, hi: int) -> list[int]:
    r = random.Random(seed)
    v = [r.randint(lo, hi) for _ in range(16)]
    return [max(lo, min(hi, round((v[i - 1] + 2 * v[i] + v[(i + 1) % 16]) / 4))) for i in range(16)]


def open_water(frame: int, variant: int = 0) -> np.ndarray:
    t = np.full((16, 16), W2, np.uint8)
    f = frame / FRAMES
    for y in range(16):
        for x in range(16):
            if (x, y) in FLECKS:
                t[y, x] = W1  # flecks of deeper water
            for y0, ph, amp, long_ in WAVES:
                line = y0 + amp * math.sin(2 * math.pi * (x / 16 + ph - f)) + 0.3 * math.sin(2 * math.pi * (f * 2 + ph))
                d = (y + 0.5 - line + 8) % 16 - 8
                c = math.cos(2 * math.pi * (x / 16 + ph * 3 - 2 * f))
                if c < (0.15 if long_ else 0.6):
                    continue
                if -0.5 <= d < 0.5:
                    t[y, x] = W4 if c > (0.7 if long_ else 0.9) else W3  # the crest, brightest in the middle
                elif long_ and 0.5 <= d < 1.5:
                    t[y, x] = W3  # its lit face
                elif long_ and -1.5 <= d < -0.5 and c > 0.4:
                    t[y, x] = W1  # the trough behind it
    for sx, sy, ph in SPARKLES[variant % len(SPARKLES)]:
        stage = (frame + ph) % FRAMES
        if stage == 0:
            t[sy, sx] = W5
        elif stage == 1:
            t[sy, sx] = SPARK
            for dx, dy in ((1, 0), (-1, 0), (0, 1), (0, -1)):
                t[(sy + dy) % 16, (sx + dx) % 16] = W5
        elif stage == 2:
            t[sy, sx] = W4
    return t


def _sides(mask: int, kind: str):
    """For each side whose neighbour isn't water: (bit, the cut line along it)."""
    lo, hi = (1, 2) if kind == "pond" else (0, 1)
    return [(bit, _wobble((31 if kind == "pond" else 57) + off, lo, hi)) for bit, off in EDGE_SEED.items()
            if not mask & bit]


def shore(mask: int, frame: int, kind: str = "pond", variant: int = 0) -> np.ndarray:
    t = open_water(frame, variant)
    rank = np.zeros((16, 16), np.int8)  # what wins where two shores meet: land > bank > foam > shallow > water
    out = t.copy()
    rng = random.Random(9)
    rock_tone = [rng.choice((RM, RM, RL, RD)) for _ in range(16)]
    for bit, cut in _sides(mask, kind):
        for i in range(16):
            for k in range(16):  # k: how far in from this side
                y, x = {1: (k, i), 4: (15 - k, i), 8: (i, k), 2: (i, 15 - k)}[bit]
                d = k - cut[i]
                if kind == "pond":
                    if d < 0:
                        val, r = 0, 5
                    elif bit == 1 and d < 4:  # the north bank: we see its face
                        val, r = (BL, BM, BM, BD)[d], 4
                    elif d == 0:
                        val, r = BL if bit == 4 else BM, 4
                    elif (bit == 1 and d == 4) or (bit != 1 and d == 1):
                        gap = (i + (frame if bit in (1, 8) else -frame)) % 6 == 0
                        val, r = (t[y, x] if gap else FOAM), 3
                    elif (bit == 1 and d in (5, 6)) or (bit != 1 and d in (2, 3)):
                        val, r = (W5 if (i + k + frame) % 3 else W4), 2
                    else:
                        continue
                else:
                    if d < 0:
                        val, r = 0, 5
                    elif d < 4:  # the cliff: an earth face with a lit lip, streaked
                        val = BL if d == 0 else (BD if (i + d) % 5 == 0 or d == 3 else BM)
                        r = 4
                    elif d == 4:  # rocks at its foot
                        val, r = (RL if i % 4 == 0 else rock_tone[i] if rock_tone[i] != RL else RM), 4
                    elif d == 5:
                        val, r = W_OUT, 4  # the waterline in the rock's shadow
                    elif d == 6:  # surf at its foot
                        splash = (i + frame) % 4
                        val, r = (SPARK if splash == 0 else FOAM if splash in (1, 2) else W4), 3
                    elif d == 7:
                        val, r = (W5 if (i + frame) % 2 else W4), 2
                    else:
                        continue
                if r > rank[y, x]:
                    rank[y, x] = r
                    out[y, x] = val
    return out
