"""The concept Pallet's trees, in their own palette (bank 3): pines of drooping, needled tiers lit from the upper
left (with a darker row of pines behind them in the forest), round leafy trees and bushes built from lit clumps of
leaves, and soft shadows on the grass under them. make_art.py puts them on the "trees" sheet."""
import math
import random

import numpy as np

PT = [(0, 0, 0), (16, 24, 32), (24, 48, 48), (32, 72, 64), (40, 96, 72), (56, 128, 80), (72, 152, 88),
      (120, 184, 104), (56, 40, 32), (96, 64, 48), (144, 104, 64), (40, 88, 48), (64, 120, 56), (96, 156, 64),
      (148, 196, 92), (64, 136, 64)]
T_OUT, SH0, PN1, PN2, PN3, PN4, PN5, BK1, BK2, BK3, LF1, LF2, LF3, LF4, GSH = range(1, 16)
PINE = [SH0, PN1, PN2, PN3, PN4, PN5]
LEAF = [PN1, LF1, LF2, LF3, LF4]


def _hash(x, y, seed=0):
    v = (x * 374761393 + y * 668265263 + seed * 2147483647) & 0xFFFFFFFF
    v = (v ^ (v >> 13)) * 1274126177 & 0xFFFFFFFF
    return ((v ^ (v >> 16)) & 0xFFFF) / 65535.0


def _shade(levels, v):
    v = min(max(v, 0.0), 0.999)
    return levels[int(v * len(levels))]


def pine_layer(t, owner, cx, base_y, scale=1.0, dark=0, wrap=True, seed=0, tier_id0=0):
    """Draw one pine (tiers of drooping, needled branches) into ``t``; ``owner`` records which tier owns a pixel."""
    h, w = t.shape
    tiers = [(1, 8, 4.5), (5, 13, 7.5), (9, 18, 10.5), (14, 23, 13.0), (19, 28, 15.0)]
    for k in range(len(tiers) - 1, -1, -1):  # bottom tier first: upper tiers overlap it
        top, bot, hw = tiers[k]
        top = base_y + (top - 28) * scale
        bot = base_y + (bot - 28) * scale
        hw *= scale
        for y in range(int(math.floor(top)), int(math.ceil(bot + 3 * scale)) + 1):
            for xi in range(int(cx - hw - 2), int(cx + hw + 3)):
                x = xi % w if wrap else xi
                if not (0 <= x < w and 0 <= y < h):
                    continue
                dx = xi + 0.5 - cx
                kk = (y + 0.5 - top) / max(1.0, bot - top)
                half = hw * (0.18 + 0.82 * min(1.0, kk))
                if abs(dx) > half:
                    continue
                # the lower edge droops into points (needle bunches)
                droop = 2.4 * scale * abs(math.sin(math.pi * (dx + 0.7 * k) / (4.2 * scale)))
                yb = bot + 2.6 * scale - droop - 1.2 * (abs(dx) / max(half, 1)) ** 2
                if y + 0.5 > yb:
                    continue
                u = dx / max(half, 1)
                v = (y + 0.5 - top) / max(1.0, yb - top)
                light = 0.47 - 0.40 * u + 0.20 * v
                if v < 0.28:  # under the tier above
                    light -= 0.30 * (0.28 - v) / 0.28 + 0.1
                # needles: strands sloping down and out from the trunk
                strand = ((int(abs(dx)) + 2 * y + k) % 4)
                light += (-0.05 if strand == 0 else 0.03 if strand == 2 else 0)
                light += (_hash(x, y, seed) - 0.5) * 0.14
                tip = abs(math.sin(math.pi * (dx + 0.7 * k) / (4.2 * scale))) > 0.8
                if yb - (y + 0.5) < 1.6 and tip and u < 0.5:
                    light += 0.2  # lit needle tips
                level = _shade(PINE, light)
                if dark:
                    level = PINE[max(0, PINE.index(level) - dark)]
                t[y, x] = level
                owner[y, x] = tier_id0 + k + 1
    return t


def outline(t, owner, colour=T_OUT, soft=PN1):
    """Dark outline on the lower/right sides, a softer one on the upper/left; dark rims under each tier."""
    h, w = t.shape
    inside = owner > 0
    out = t.copy()
    for y in range(h):
        for x in range(w):
            if not inside[y, x]:
                continue
            below = y + 1 >= h or not inside[y + 1, x]
            right = x + 1 >= w or not inside[y, x + 1]
            above = y == 0 or not inside[y - 1, x]
            left = x == 0 or not inside[y, x - 1]
            if below or right:
                out[y, x] = colour
            elif above or left:
                out[y, x] = soft if t[y, x] not in (SH0,) else colour
            elif y > 0 and inside[y - 1, x] and owner[y - 1, x] != owner[y, x]:
                out[y, x] = T_OUT if owner[y - 1, x] < owner[y, x] else SH0  # under an upper tier: its shadow
            elif y > 1 and inside[y - 2, x] and owner[y - 2, x] != owner[y, x] and owner[y - 1, x] == owner[y, x]:
                out[y, x] = SH0
    return out


def trunk(t, cx, y0, y1, force=False):
    for y in range(y0, y1):
        for x in range(cx - 2, cx + 2):
            if force or t[y, x] in (0, GSH):
                t[y, x] = [BK1, BK3, BK2, BK1][x - (cx - 2)]
        if (y * 3) % 5 == 0:
            t[y, cx - 1] = BK2
    t[y1 - 1, cx - 3] = BK1  # roots
    t[y1 - 1, cx + 2] = BK1
    side = t[y0:y1, cx - 3]
    side[(side == 0) | force] = T_OUT
    side = t[y0:y1, cx + 2]
    side[(side == 0) | force] = T_OUT


def ground_shadow(t, cx, cy, rx, ry):
    h, w = t.shape
    for y in range(h):
        for x in range(w):
            d = ((x + 0.5 - cx) / rx) ** 2 + ((y + 0.5 - cy) / ry) ** 2
            if t[y, x] == 0 and d <= 1.0 and (d < 0.6 or (x + y) % 2 == 0):
                t[y, x] = GSH


def pine(dense: bool) -> np.ndarray:
    t = np.zeros((32, 32), np.uint8)
    owner = np.zeros((32, 32), np.int32)
    if dense:
        t[:] = SH0
        for y in range(32):
            for x in range(32):
                if y > 22 and (x + y) % 2 == 0 or y > 27:
                    t[y, x] = T_OUT
        # the row behind, half a cell over: darker, partly hidden
        bo = np.zeros_like(owner)
        for cx in (0.0, 32.0):
            pine_layer(t, bo, cx, 16, scale=0.85, dark=2, wrap=True, seed=7)
        t = outline(t, bo, T_OUT, SH0) if False else t
    else:
        ground_shadow(t, 16.5, 29.5, 13, 2.6)
    trunk(t, 16, 26, 31, force=dense)
    pine_layer(t, owner, 16.0, 28, seed=3)
    main = outline(t, owner)
    if not dense:
        main[(owner == 0) & (t == 0)] = 0
    return main


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
                out[y, x] = T_OUT
            elif nb[2] or nb[3]:
                out[y, x] = LF1 if (nb[3] and not nb[2]) else T_OUT if y > h * 0.4 else LF1
            elif owner[y + 1, x] > owner[y, x] and owner[y + 1, x] != owner[y, x]:
                out[y, x] = PN1  # behind a clump in front
            elif owner[y - 1, x] < owner[y, x]:
                out[y, x] = LF4 if t[y, x] in (LF3, LF4) else LF3  # a clump's lit top edge
    return out


def round_tree() -> np.ndarray:
    t = np.zeros((32, 32), np.uint8)
    owner = np.zeros((32, 32), np.int32)
    ground_shadow(t, 16.5, 29.5, 12, 2.6)
    trunk(t, 16, 21, 31)
    for y in range(17, 23):  # two boughs
        t[y, 16 - (22 - y) // 2 - 2] = BK2 if t[y, 16 - (22 - y) // 2 - 2] == 0 else t[y, 16 - (22 - y) // 2 - 2]
    rng = random.Random(5)
    cl = []
    for row, (y, n, spread, r) in enumerate(((6.0, 4, 8.5, 4.6), (10.5, 5, 11.0, 4.9), (15.0, 5, 11.5, 4.8),
                                             (18.5, 3, 7.5, 4.2))):
        for i in range(n):
            x = 16 + (i - (n - 1) / 2) * (2 * spread / max(1, n - 1)) + rng.uniform(-0.8, 0.8)
            cl.append((x, y + rng.uniform(-0.8, 0.8) + 0.9 * abs(i - (n - 1) / 2) ** 1.3 * (row == 0),
                       r + rng.uniform(-0.4, 0.4)))
    cl.append((16, 3.6, 3.8))
    cl.sort(key=lambda c: c[1])
    leafy(t, owner, cl, 11, centre=(16, 12, 13))
    return leaf_outline(t, owner)


def bush(seed: int = 2) -> np.ndarray:
    t = np.zeros((16, 16), np.uint8)
    owner = np.zeros((16, 16), np.int32)
    ground_shadow(t, 8.5, 14, 7, 1.8)
    rng = random.Random(seed)
    cl = _clusters(rng, 9, 8, 9, 4.5, 3, 2.6, 3.6)
    leafy(t, owner, cl, seed, centre=(8, 9, 6))
    return leaf_outline(t, owner)
