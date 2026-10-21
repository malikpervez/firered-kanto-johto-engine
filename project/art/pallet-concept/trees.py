"""The concept Pallet's trees, in their own palette (bank 3). Pines fill their 2x2 block, with a darker row behind
them, so a forest reads as a solid wall like the game's own trees; their tiers end in rows of rounded lobes of
needles, each lit like a ball from the upper left and stippled between shades. Round leafy trees and bushes are
built from lit clumps of leaves, with soft shadows on the grass under them. make_art.py puts them on the "trees"
sheet."""
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


TIERS = [(0, 8, 7.0, 2.6), (3, 14, 10.5, 3.0), (8, 21, 13.2, 3.2), (14, 29, 14.8, 3.5)]
# (top, bottom, half width, lobe radius) of a 32px pine: neighbours nearly touch, and it stays inside its cell
BAYER = [[0.0, 0.5], [0.75, 0.25]]


def _shade_d(levels, v, x, y):
    """A shade for ``v`` (0 dark .. 1 light), stippled between two shades the way the game's own trees are."""
    f = min(max(v, 0.0), 0.999) * len(levels)
    i = int(f)
    if f - i > BAYER[y % 2][x % 2] + 0.25 and i + 1 < len(levels):
        i += 1
    return levels[i]


def pine_layer(t, owner, cx, base_y, scale=1.0, dark=0, wrap=True, seed=0, tier_id0=0):
    """Draw one pine into ``t``: tiers whose lower edges are rows of rounded, drooping lobes of needles; each lobe
    lit like a ball from the upper left, stippled between shades. ``owner`` records each pixel's tier (and lobe)."""
    h, w = t.shape
    for k in range(len(TIERS) - 1, -1, -1):  # bottom tier first: upper tiers overlap it
        top, bot, hw, lr = TIERS[k]
        top = base_y + (top - 29) * scale
        bot = base_y + (bot - 29) * scale
        hw, lr = hw * scale, lr * scale
        n = max(2, int(round(2 * hw / (1.7 * lr))))
        mid = (n - 1) / 2
        # symmetric: the outer lobes a little smaller and lower, the same on both sides
        lobes = [(cx - hw + lr + i * (2 * hw - 2 * lr) / (n - 1), bot - lr + 0.2 * lr * (abs(i - mid) / mid) ** 2,
                  lr * (1 - 0.18 * (abs(i - mid) / mid) ** 3)) for i in range(n)]
        for y in range(int(math.floor(top)), int(math.ceil(bot + 1)) + 1):
            for xi in range(int(cx - hw - 2), int(cx + hw + 3)):
                x = xi % w if wrap else xi
                if not (0 <= x < w and 0 <= y < h):
                    continue
                px, py = xi + 0.5, y + 0.5
                kk = (py - top) / max(1.0, bot - lr - top)
                body = abs(px - cx) <= min(hw * (0.15 + 0.85 * min(1.0, kk)) - lr * 0.6, hw - lr) and py <= bot - lr
                best = None
                for j, (lx, ly, r) in enumerate(lobes):
                    d = ((px - lx) / r) ** 2 + ((py - ly) / (r * 0.9)) ** 2
                    if d <= 1.0 and py >= ly - r * 0.2 and (best is None or ly > best[2]):
                        best = (j, d, ly, lx, r)
                if best is None and not body:
                    continue
                u = (px - cx) / max(hw, 1)
                light = 0.60 - 0.30 * u
                if best is not None:  # a lobe: round shading of its own
                    j, d, ly, lx, r = best
                    nx, ny = (px - lx) / r, (py - ly) / (r * 0.9)
                    light += -0.22 * ny - 0.12 * nx + 0.08
                    owner[y, x] = tier_id0 + (k + 1) * 32 + j + 1
                else:  # the tier's upper part, in the shadow of the tier above
                    light -= 0.22 + 0.10 * (1 - kk)
                    owner[y, x] = tier_id0 + (k + 1) * 32
                light += (_hash(x, y, seed + k) - 0.5) * 0.12
                level = _shade_d(PINE, light, x, y)
                if dark:
                    level = PINE[max(0, PINE.index(level) - dark)]
                t[y, x] = level
    return t


def outline(t, owner, colour=T_OUT, soft=PN1, wrap=False, edges=None):
    """Dark outline on the lower/right sides, a softer one on the upper/left; under each tier the dark rim of the
    tier above's shadow, and a dark crease along the bottom of each lobe (``owner``: tier * 32 + lobe)."""
    h, w = t.shape
    inside = owner > 0
    tier = owner // 32
    out = t.copy()
    for y in range(h):
        for x in range(w):
            if not inside[y, x]:
                continue
            xr, xl = ((x + 1) % w, (x - 1) % w) if wrap else (x + 1, x - 1)
            e = edges or {}
            below = (y + 1 >= h and not e.get("s")) or (y + 1 < h and not inside[y + 1, x])
            right = (xr >= w and not e.get("e")) or (xr < w and not inside[y, xr])
            above = (y == 0 and not e.get("n")) or (y > 0 and not inside[y - 1, x])
            left = (xl < 0 and not e.get("w")) or (xl >= 0 and not inside[y, xl])
            if below or right:
                out[y, x] = colour
            elif above or left:
                out[y, x] = soft if t[y, x] != SH0 else colour
            elif tier[y - 1, x] != tier[y, x] and tier[y - 1, x] < tier[y, x]:
                out[y, x] = colour  # just under an upper tier
            elif y > 1 and tier[y - 2, x] < tier[y, x] and tier[y - 1, x] == tier[y, x]:
                out[y, x] = SH0
            elif y + 1 < h and tier[y + 1, x] == tier[y, x] and owner[y + 1, x] != owner[y, x] \
                    and owner[y + 1, x] % 32 == 0:
                out[y, x] = SH0  # a lobe's lower edge over the shaded tier body behind it
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


def pine(mask: int = 15) -> np.ndarray:
    """A pine filling a 2x2 cell of forest. ``mask`` says which way the forest goes on (1 north, 2 east, 4 south,
    8 west): toward more forest a darker row of pines stands behind it and the gaps are the dark forest floor;
    toward open ground the gaps stay clear (the grass shows) and the trees show their own outline."""
    t = np.zeros((32, 32), np.uint8)
    owner = np.zeros((32, 32), np.int32)
    closed = {"n": bool(mask & 1), "e": bool(mask & 2), "s": bool(mask & 4), "w": bool(mask & 8)}
    bo = np.zeros_like(owner)
    if closed["w"]:  # the back row: half of a pine between this cell and the next, on each forested side
        pine_layer(t, bo, 0.0, 26, scale=0.8, dark=1, wrap=False, seed=7)
    if closed["e"]:
        pine_layer(t, bo, 32.0, 26, scale=0.8, dark=1, wrap=False, seed=7)
    t = np.where(bo > 0, outline(t, bo, edges=closed), t).astype(np.uint8)
    trunk(t, 16, 28, 32, force=True)
    pine_layer(t, owner, 16.0, 29, seed=3)
    t = outline(t, owner)
    # the gaps: clear where they open onto open ground, the dark forest floor where trees close them in
    reach = np.zeros((32, 32), bool)
    todo = [(y, x) for y in range(32) for x in range(32) if t[y, x] == 0 and (  # near an open side counts as open
        (y < 3 and not closed["n"]) or (y > 28 and not closed["s"]) or (x < 3 and not closed["w"])
        or (x > 28 and not closed["e"]))]
    for y, x in todo:
        reach[y, x] = True
    while todo:
        y, x = todo.pop()
        for yy, xx in ((y + 1, x), (y - 1, x), (y, x + 1), (y, x - 1)):
            if 0 <= yy < 32 and 0 <= xx < 32 and not reach[yy, xx] and t[yy, xx] == 0:
                reach[yy, xx] = True
                todo.append((yy, xx))
    for y in range(32):
        for x in range(32):
            if t[y, x] == 0 and not reach[y, x]:
                t[y, x] = T_OUT if (y > 26 and (x + y) % 2) or y > 29 else SH0
    if not closed["s"]:
        shade = np.zeros_like(t)
        ground_shadow(shade, 16.5, 30.0, 14, 2.2)
        t[(t == 0) & (shade > 0)] = GSH
    return t


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
    for row, (y, n, spread, r) in enumerate(((4.5, 4, 7.0, 3.4), (7.5, 6, 10.0, 3.6), (10.5, 7, 11.5, 3.7),
                                             (13.5, 7, 12.0, 3.6), (16.5, 6, 10.5, 3.4), (19.0, 4, 7.0, 3.0))):
        for i in range(n):
            x = 16 + (i - (n - 1) / 2) * (2 * spread / max(1, n - 1)) + rng.uniform(-0.8, 0.8)
            cl.append((x, y + rng.uniform(-0.8, 0.8) + 0.9 * abs(i - (n - 1) / 2) ** 1.3 * (row == 0),
                       r + rng.uniform(-0.4, 0.4)))
    cl.append((16, 2.6, 3.0))
    cl.sort(key=lambda c: c[1])
    leafy(t, owner, cl, 11, centre=(16, 12, 13))
    return leaf_outline(t, owner)


def bush(seed: int = 2) -> np.ndarray:
    t = np.zeros((16, 16), np.uint8)
    owner = np.zeros((16, 16), np.int32)
    ground_shadow(t, 8.5, 14, 7, 1.8)
    rng = random.Random(seed)
    cl = _clusters(rng, 14, 8, 9, 4.8, 3.2, 2.0, 2.8)
    leafy(t, owner, cl, seed, centre=(8, 9, 6))
    return leaf_outline(t, owner)
