#!/usr/bin/env python3
"""Pallet Town after the concept art (concept.png, made with image generation): every tile drawn here (the trees in
trees.py), nothing taken from an existing tileset.

The town is 32x28 blocks: a pine forest around it, two log houses with fenced yards, cobblestone roads, a windmill
in a flower garden, Oak's lab with its greenhouse, a pond with a wooden dock (and the way south to Route 21), the sea
below a cliff in the east, and a stone well.

Six palettes, each made for what uses it:
  bank 0  ground: grass, pines, dirt, cobblestones, rocks
  bank 1  water: pond and sea, their banks, cliff rocks (drawn in water.py, animated in eight frames)
  bank 2  wood and roofs: the houses, fences, the dock, signs, the windmill, the well, barrels, the boat
  bank 3  trees: the pines, round trees and bushes (drawn in trees.py)
  bank 7  the lab: metal roof, siding, glass, the greenhouse plants
  bank 8  plants: flowers, lamps

Run from the repository root:  python3 project/art/pallet-concept/make_art.py
It writes sheets/*.png, the palettes, spec.json, grid.txt, border.txt, legend.json and events.json next to itself;
build.sh turns them into the game's tilesets and map with pae.
"""
import json
import math
import random
from pathlib import Path

import numpy as np
from PIL import Image

import trees
import water

HERE = Path(__file__).resolve().parent
MAP_W, MAP_H = 32, 28

# ---------------------------------------------------------------- palettes
P0 = [(0, 0, 0), (24, 32, 32), (24, 64, 56), (40, 96, 64), (56, 120, 64), (88, 160, 72), (120, 192, 88),
      (168, 216, 112), (112, 72, 48), (176, 128, 80), (216, 176, 120), (96, 96, 96), (144, 144, 136),
      (192, 192, 176), (72, 48, 40), (240, 240, 224)]
OUT, PD, PM, GD, GM, GL, GH, SD, SM, SL, KD, KM, KL, TR, CR = range(1, 16)


P2 = [(0, 0, 0), (40, 24, 24), (88, 48, 32), (136, 80, 48), (184, 120, 72), (224, 168, 112), (120, 32, 32),
      (176, 56, 48), (224, 96, 72), (248, 152, 120), (40, 56, 96), (96, 144, 200), (176, 216, 240),
      (240, 232, 208), (120, 120, 128), (184, 184, 184)]
D_OUT, WOD, WOM, WOL, WOH, RFD, RFM, RFL, RFH, NWD, NWM, NWL, CRM, STG, STL = range(1, 16)

P3 = [(0, 0, 0), (24, 32, 40), (64, 80, 96), (96, 112, 128), (144, 160, 168), (192, 200, 208), (152, 144, 120),
      (200, 192, 168), (232, 228, 208), (40, 64, 80), (120, 176, 184), (200, 236, 236), (40, 96, 56),
      (88, 152, 72), (72, 120, 88), (248, 248, 240)]
L_OUT, MTD, MTM, MTL, MTH, SID, SIM, SIL, LWD, GLA, GLH, PLD, PLM, DRG, LWH = range(1, 16)

P4 = [(0, 0, 0), (24, 32, 32), (32, 80, 48), (56, 128, 64), (104, 176, 80), (160, 208, 104), (208, 64, 64),
      (240, 136, 168), (248, 208, 72), (240, 144, 64), (144, 104, 200), (104, 152, 232), (248, 248, 240),
      (56, 56, 64), (248, 232, 160), (96, 64, 40)]
F_OUT, LFD, LFM, LFL, LFH, RED, PINK, YEL, ORG, PUR, BLU, WHT, IRON, GLOW, TRUNK = range(1, 16)

BANK = {"ground": 0, "water": 1, "wood": 2, "trees": 3, "lab": 7, "plants": 8}
PALS = {"ground": P0, "water": water.PW, "wood": P2, "trees": trees.PT, "lab": P3, "plants": P4}


def rgba(idx: np.ndarray, pal) -> np.ndarray:
    out = np.zeros(idx.shape + (4,), np.uint8)
    for i, c in enumerate(pal):
        if i:
            out[idx == i] = (*c, 255)
    return out


def edge_of(mask: np.ndarray) -> np.ndarray:
    """Pixels of ``mask`` with a 4-neighbour outside it (the outline)."""
    p = np.pad(mask, 1)
    inner = p[:-2, 1:-1] & p[2:, 1:-1] & p[1:-1, :-2] & p[1:-1, 2:]
    return mask & ~inner


def ellipse(h, w, cx, cy, rx, ry) -> np.ndarray:
    yy, xx = np.mgrid[0:h, 0:w]
    return ((xx + 0.5 - cx) / rx) ** 2 + ((yy + 0.5 - cy) / ry) ** 2 <= 1.0


def wobble(seed: int, n: int = 16, lo: int = 1, hi: int = 3) -> list[int]:
    """A smooth-ish random edge line (the same for a given seed)."""
    r = random.Random(seed)
    v = [r.randint(lo, hi) for _ in range(n)]
    return [max(lo, min(hi, round((v[i - 1] + 2 * v[i] + v[(i + 1) % n]) / 4))) for i in range(n)]


# ---------------------------------------------------------------- ground (bank 0)
def grass(seed: int, daisies: int = 0, clover: bool = False) -> np.ndarray:
    r = random.Random(seed)
    t = np.full((16, 16), GL, np.uint8)
    for _ in range(18):  # fine texture
        t[r.randrange(16), r.randrange(16)] = GM
    for _ in range(5):
        t[r.randrange(16), r.randrange(16)] = GH
    for _ in range(4):  # tufts: two dark blades under a lit tip
        x, y = r.randrange(1, 14), r.randrange(2, 15)
        t[y, x] = GD
        t[y, x + 2] = GD
        t[y - 1, x] = GM
        t[y - 1, x + 1] = GH
        t[y - 1, x + 2] = GM
        t[y - 2, x + 1] = GH
    if clover:
        for _ in range(2):
            x, y = r.randrange(2, 13), r.randrange(2, 13)
            for dx, dy in ((0, 0), (1, 0), (0, 1), (1, 1), (-1, 0), (0, -1)):
                t[y + dy, x + dx] = GM
            t[y, x] = GH
            t[y + 2, x + 1] = GD
    for _ in range(daisies):
        x, y = r.randrange(2, 14), r.randrange(2, 14)
        t[y, x] = SL
        for dx, dy in ((1, 0), (-1, 0), (0, 1), (0, -1)):
            t[y + dy, x + dx] = CR
        t[y + 2, x] = GD
    return t


def _torus_cells(seed: int, n: int, size: int = 16):
    """Voronoi cells on a size x size torus: (cell id, distance to own centre, gap) per pixel."""
    r = random.Random(seed)
    pts = []
    while len(pts) < n:  # spread the stones out
        p = (r.uniform(0, size), r.uniform(0, size))
        if all(min(abs(p[0] - q[0]), size - abs(p[0] - q[0])) ** 2 + min(abs(p[1] - q[1]), size - abs(p[1] - q[1])) ** 2
               > (size / math.sqrt(n) * 0.8) ** 2 for q in pts):
            pts.append(p)
    cid = np.zeros((size, size), np.int32)
    gap = np.zeros((size, size), bool)
    rel = np.zeros((size, size, 2), np.float32)
    for y in range(size):
        for x in range(size):
            ds = []
            for i, (px, py) in enumerate(pts):
                dx = (x + 0.5 - px + size / 2) % size - size / 2
                dy = (y + 0.5 - py + size / 2) % size - size / 2
                ds.append((dx * dx + dy * dy, i, dx, dy))
            ds.sort()
            cid[y, x] = ds[0][1]
            rel[y, x] = ds[0][2:]
            gap[y, x] = math.sqrt(ds[1][0]) - math.sqrt(ds[0][0]) < 1.0
    return cid, gap, rel


COBBLE = _torus_cells(7, 11)
EDGE_SEED = {1: 101, 2: 202, 4: 303, 8: 404}


def _cut(t: np.ndarray, mask: int, seed: int, lip: int, lo: int = 1, hi: int = 3) -> np.ndarray:
    """Make the sides whose neighbour differs transparent beyond a wobbly line, with a lip colour on the line.
    The line depends only on the side, so a quadrant looks the same in every variant that cuts the same sides."""
    t = t.copy()
    for bit, seed_off in EDGE_SEED.items():
        if mask & bit:
            continue
        wob = wobble(seed + seed_off, 16, lo, hi)
        for i in range(16):
            d = wob[i]
            if bit == 1:
                t[:d, i] = 0
                t[d, i] = lip if t[d, i] else 0
            elif bit == 4:
                t[16 - d:, i] = 0
                t[15 - d, i] = lip if t[15 - d, i] else 0
            elif bit == 8:
                t[i, :d] = 0
                t[i, d] = lip if t[i, d] else 0
            else:
                t[i, 16 - d:] = 0
                t[i, 15 - d] = lip if t[i, 15 - d] else 0
    return t


def cobble(mask: int) -> np.ndarray:
    cid, gap, rel = COBBLE
    r = random.Random(5)
    tint = {i: r.random() < 0.3 for i in range(11)}
    t = np.zeros((16, 16), np.uint8)
    for y in range(16):
        for x in range(16):
            if gap[y, x]:
                t[y, x] = KD
                continue
            dx, dy = rel[y, x]
            v = -(dx + dy)
            if v > 1.6:
                t[y, x] = KL
            elif v < -1.9:
                t[y, x] = KD
            else:
                t[y, x] = SL if tint[int(cid[y, x])] and v > -0.5 else KM
    return _cut(t, mask, 11, KD)


def dirt(mask: int) -> np.ndarray:
    r = random.Random(17)
    t = np.full((16, 16), SM, np.uint8)
    for _ in range(26):
        t[r.randrange(16), r.randrange(16)] = SL
    for _ in range(10):
        t[r.randrange(16), r.randrange(16)] = SD
    for _ in range(2):  # pebbles
        x, y = r.randrange(1, 14), r.randrange(1, 14)
        t[y, x:x + 2] = KM
        t[y + 1, x:x + 2] = KD
        t[y, x] = KL
    return _cut(t, mask, 23, SD)


def rock(seed: int, big: bool) -> np.ndarray:
    t = np.zeros((16, 16), np.uint8)
    m = ellipse(16, 16, 8, 9.5 if big else 11, 6.5 if big else 4.5, 5 if big else 3.5)
    t[m] = KM
    t[m & ellipse(16, 16, 6, 7.5 if big else 10, 4 if big else 2.5, 3 if big else 2)] = KL
    t[m & ~ellipse(16, 16, 7, 8.5 if big else 10.5, 6.5 if big else 4.5, 5 if big else 3.5)] = KD
    t[edge_of(m)] = OUT
    if big:
        t[9, 9:12] = KD  # a crack
        t[10, 11] = KD
    return t


def stump() -> np.ndarray:
    t = np.zeros((16, 16), np.uint8)
    side = ellipse(16, 16, 8, 10.5, 6, 4.5)
    t[side] = TR
    top = ellipse(16, 16, 8, 8, 6, 3.5)
    t[top] = SL
    t[ellipse(16, 16, 8, 8, 3.5, 2)] = SM
    t[ellipse(16, 16, 8, 8, 1.5, 1)] = SL
    t[edge_of(side | top)] = OUT
    t[edge_of(top) & ~edge_of(side | top)] = SD
    t[11:14, 4] = SD
    t[12:15, 11] = SD
    return t


# ---------------------------------------------------------------- wood (bank 2)
def fence(mask: int) -> np.ndarray:
    """Wooden post-and-rail fence, joined toward the neighbours that are fence (1 N, 2 E, 4 S, 8 W)."""
    t = np.zeros((16, 16), np.uint8)

    def rail(y0, x0, x1):
        t[y0, x0:x1] = WOL
        t[y0 + 1, x0:x1] = WOM
        t[y0 + 2, x0:x1] = D_OUT
    if mask & 8:
        rail(5, 0, 7)
        rail(10, 0, 7)
    if mask & 2:
        rail(5, 9, 16)
        rail(10, 9, 16)
    if mask & 1:
        t[0:4, 7] = WOL
        t[0:4, 8] = WOD
    if mask & 4:
        t[12:16, 7] = WOL
        t[12:16, 8] = WOD
    # the post
    t[3:14, 6:10] = WOM
    t[3:14, 6] = WOL
    t[3:14, 9] = WOD
    t[3:14, 5] = D_OUT
    t[3:14, 10] = D_OUT
    t[2, 6:10] = D_OUT
    t[3, 6:10] = WOH
    t[14, 6:10] = D_OUT
    t[8, 7] = WOD  # grain
    return t


def planks(mask: int) -> np.ndarray:
    """Dock boards (horizontal); dark beams and posts on the sides that face water."""
    t = np.zeros((16, 16), np.uint8)
    for y in range(16):
        row = y % 4
        t[y, :] = (WOL, WOM, WOM, WOD)[row]
    for y0, seam in ((0, 5), (4, 12), (8, 2), (12, 9)):
        t[y0:y0 + 3, seam] = WOD
        t[y0 + 1, (seam + 3) % 16] = D_OUT  # nails
    if not mask & 1:
        t[0, :] = D_OUT
        t[1, :] = WOH
    if not mask & 8:
        t[:, 0] = D_OUT
        t[:, 1] = WOD
    if not mask & 2:
        t[:, 15] = D_OUT
        t[:, 14] = WOD
    if not mask & 4:
        t[12, :] = D_OUT
        t[13:16, :] = WOD
        for px in (2, 12):
            t[13:16, px:px + 2] = WOM
            t[13:16, px] = WOL
        t[15, :] = D_OUT
    return t


def sign() -> np.ndarray:
    t = np.zeros((16, 16), np.uint8)
    t[9:15, 7:9] = WOM
    t[9:15, 7] = WOL
    t[9:15, 6] = D_OUT
    t[9:15, 9] = D_OUT
    t[15, 6:10] = D_OUT
    t[2:10, 1:15] = WOL
    t[3:9, 2:14] = WOM
    t[2, 1:15] = D_OUT
    t[10, 1:15] = D_OUT
    t[2:11, 0] = D_OUT
    t[2:11, 15] = D_OUT
    t[3, 2:14] = WOH
    for y in (5, 7):
        t[y, 3:13] = WOD
        t[y, 3 + (y % 3):13:4] = WOM
    t[9, 2:14] = WOD
    return t


def barrel() -> np.ndarray:
    t = np.zeros((16, 16), np.uint8)
    body = ellipse(16, 16, 8, 9, 6, 6.5)
    t[body] = WOM
    yy, xx = np.indices((16, 16))
    t[body & (xx < 6)] = WOL
    t[body & (xx > 10)] = WOD
    t[body & ((yy == 5) | (yy == 12))] = STG
    t[body & ((yy == 5) | (yy == 12)) & (xx < 6)] = STL
    top = ellipse(16, 16, 8, 4, 5, 2.2)
    t[top] = WOD
    t[ellipse(16, 16, 8, 4, 3.5, 1.2)] = WOM
    t[edge_of(body | top)] = D_OUT
    return t


def crate() -> np.ndarray:
    t = np.zeros((16, 16), np.uint8)
    t[3:15, 2:14] = WOM
    t[3:5, 2:14] = WOL
    t[3:15, 2:4] = WOL
    t[3:15, 12:14] = WOD
    t[13:15, 2:14] = WOD
    for i in range(9):  # the cross brace
        t[5 + i, 4 + i] = WOD
        t[5 + i, 11 - i] = WOD
    t[2, 2:14] = D_OUT
    t[15, 2:14] = D_OUT
    t[2:16, 1] = D_OUT
    t[2:16, 14] = D_OUT
    t[1, 3:13] = WOH
    return t


def boat() -> np.ndarray:
    t = np.zeros((16, 32), np.uint8)
    hull = ellipse(16, 32, 16, 8, 14.5, 6.5)
    t[hull] = WOM
    inner = ellipse(16, 32, 16, 7.5, 11.5, 4)
    t[inner] = WOD
    t[hull & ~ellipse(16, 32, 16, 6.5, 14.5, 6.5)] = WOD
    t[4:12, 11:13] = WOL  # seats
    t[4:12, 20:22] = WOL
    t[edge_of(hull)] = D_OUT
    t[edge_of(inner)] = D_OUT
    t[3, 6:26] = WOH * (t[3, 6:26] > 0)
    t[8, 0:4] = WOL  # an oar
    t[7:10, 0:2] = WOM
    return t


def well() -> np.ndarray:
    t = np.zeros((32, 32), np.uint8)
    ring = ellipse(32, 32, 16, 22, 11, 7.5)
    hole = ellipse(32, 32, 16, 20.5, 7.5, 4)
    t[ring] = STG
    yy, xx = np.indices((32, 32))
    t[ring & ((yy + (xx // 4) % 2 * 2) % 4 == 0)] = D_OUT * 0 + STL
    t[ring & ((xx + (yy // 3) * 2) % 5 == 0)] = D_OUT
    t[hole] = NWD
    t[ellipse(32, 32, 14, 21.5, 3.5, 1.5)] = NWM
    t[edge_of(ring)] = D_OUT
    t[edge_of(hole)] = D_OUT
    # posts and a little roof
    for px in (5, 25):
        t[6:22, px:px + 2] = WOM
        t[6:22, px] = WOL
        t[6:22, px - 1] = D_OUT
        t[6:22, px + 2] = D_OUT
    for y in range(0, 8):
        x0, x1 = 8 - y, 24 + y
        t[y, max(0, x0):min(32, x1)] = RFM if y % 3 else RFD
        t[y, max(0, x0)] = D_OUT
        t[y, min(31, x1 - 1)] = D_OUT
    t[0, 8:24] = D_OUT
    t[8, 0:32] = D_OUT
    t[1:3, 10:22] = RFL
    t[9:11, 7:25] = WOD  # the crossbar and bucket rope
    t[11:15, 16] = WOD
    t[14:17, 14:19] = WOM
    t[14:17, 14] = D_OUT
    t[14:17, 18] = D_OUT
    return t


def house() -> np.ndarray:
    """A log house with a red roof, 5x5 blocks; the door is block (1, 4)."""
    t = np.zeros((80, 80), np.uint8)
    yy, xx = np.indices((80, 80))
    # roof: front slope with standing seams, overhanging the walls, gables at the sides
    for y in range(4, 40):
        inset = max(0, 9 - (y - 4)) // 1
        x0, x1 = 2 + inset, 78 - inset
        t[y, x0:x1] = RFM
        for x in range(x0, x1):
            if (x - 2) % 6 == 0:
                t[y, x] = RFD
            elif (x - 2) % 6 == 1:
                t[y, x] = RFL
        t[y, x0] = D_OUT
        t[y, x1 - 1] = D_OUT
    t[4, 11:69] = D_OUT
    t[5, 11:69] = RFH
    t[6, 10:70] = RFL
    for y in range(26, 40):  # the lower roof catches less light
        t[y, 3:77][t[y, 3:77] == RFL] = RFM
    t[38, 2:78] = RFD
    t[39, 1:79] = D_OUT
    t[40, 3:77] = WOD  # eave shadow
    # chimney
    t[0:18, 58:67] = STG
    t[0:18, 58] = D_OUT
    t[0:18, 66] = D_OUT
    t[0, 58:67] = D_OUT
    t[1:3, 59:66] = STL
    for y in range(4, 18, 4):
        t[y, 59:66] = D_OUT
        t[y + 1:y + 3, 59 + (y // 4) % 2 * 3] = D_OUT
    # walls: stacked logs
    t[41:76, 4:76] = WOM
    for y in range(41, 76):
        k = (y - 41) % 5
        if k == 0:
            t[y, 4:76] = WOH
        elif k == 1:
            t[y, 4:76] = WOL
        elif k == 4:
            t[y, 4:76] = WOD
    for y in range(41, 76, 5):  # log ends at the corners
        for cx in (5, 74):
            t[y:y + 4, cx - 1:cx + 2] = WOL
            t[y + 1:y + 3, cx] = WOD
    t[41:76, 3] = D_OUT
    t[41:76, 76] = D_OUT
    # windows with cream frames and shutters
    for wx in (40, 58):
        t[46:62, wx - 1:wx + 15] = D_OUT
        t[47:61, wx:wx + 14] = CRM
        t[48:60, wx + 2:wx + 12] = NWM
        t[48:52, wx + 2:wx + 12] = NWL
        t[48:60, wx + 6:wx + 8] = CRM
        t[53:55, wx + 2:wx + 12] = CRM
        t[56:59, wx + 3:wx + 5] = NWD
        t[61:63, wx - 1:wx + 15] = WOD
        t[62, wx:wx + 14] = RFL  # flower box
        t[61, wx + 1:wx + 13:3] = RFH
    # door at block (1, 4): x 16-31, y 64-79; a small porch roof over it
    t[57:60, 14:34] = RFM
    t[57, 14:34] = D_OUT
    t[60, 14:34] = D_OUT
    t[58, 15:33] = RFL
    t[61:78, 18:30] = D_OUT
    t[62:78, 19:29] = WOD
    t[62:78, 23:25] = D_OUT
    for y in range(64, 78, 4):
        t[y, 19:23] = WOM
        t[y, 25:29] = WOM
    t[70:72, 26:28] = STL
    # foundation stones
    t[75:79, 3:77] = STG
    for x in range(3, 77, 6):
        t[75:79, x] = D_OUT
    t[75, 3:77] = STL
    t[79, 3:77] = D_OUT
    t[75:80, 17:31] = STL  # doorstep
    t[79, 17:31] = D_OUT
    return t


def windmill() -> np.ndarray:
    """5x6 blocks: a white tower with a red cap and four sails; the door is block (2, 5)."""
    t = np.zeros((96, 80), np.uint8)
    yy, xx = np.indices((96, 80))
    # tower: tapering, white boards
    top_y, bot_y = 34, 92
    body = np.zeros((96, 80), bool)
    for y in range(top_y, bot_y):
        k = (y - top_y) / (bot_y - top_y)
        half = 13 + 8 * k
        body[y, int(40 - half):int(40 + half)] = True
    t[body] = CRM
    t[body & (xx > 46)] = STL
    t[body & (xx > 53)] = STG
    t[body & (xx < 32)] = STL * 0 + CRM
    t[body & ((yy - top_y) % 6 == 5)] = STL
    t[body & ((yy - top_y) % 6 == 5) & (xx > 50)] = STG
    t[edge_of(body)] = D_OUT
    # stone base
    t[86:92, 17:63] = STG
    t[86, 17:63] = STL
    for x in range(17, 63, 5):
        t[86:92, x] = D_OUT
    t[92, 17:63] = D_OUT
    # window and door
    t[46:56, 36:44] = D_OUT
    t[47:55, 37:43] = NWM
    t[47:50, 37:43] = NWL
    t[51, 37:43] = D_OUT
    t[78:93, 33:47] = D_OUT
    t[79:93, 34:46] = WOD
    t[79:93, 39:41] = D_OUT
    t[78, 35:45] = WOM
    # cap: red dome
    cap = ellipse(96, 80, 40, 36, 17, 13) & (yy < 38)
    t[cap] = RFM
    t[cap & (xx < 36) & (yy < 31)] = RFL
    t[cap & (xx < 30) & (yy < 28)] = RFH
    t[cap & (xx > 46)] = RFD
    t[edge_of(cap)] = D_OUT
    t[37:39, 22:58] = D_OUT
    t[36, 24:56] = RFD
    # sails: an X of lattice blades around the hub (each pixel asks which blade it lies on)
    hx, hy = 40, 30
    for ang in (45, 135, 225, 315):
        a = math.radians(ang)
        ux, uy = math.cos(a), math.sin(a)
        rx_, ry_ = xx + 0.5 - hx, yy + 0.5 - hy
        s_ = rx_ * ux + ry_ * uy
        w_ = -rx_ * uy + ry_ * ux
        on = (s_ >= 5) & (s_ <= 38)
        spar = on & (np.abs(w_) <= 1.0)
        sail = on & (w_ > 1.0) & (w_ <= 7.5) & (s_ >= 11)
        rim = sail & ((w_ > 6.5) | (s_ > 37) | (s_ < 12))
        lattice = sail & ~rim & ((np.abs((s_ % 6.5) - 3.25) > 2.6) | (np.abs(w_ - 4.2) < 0.55))
        t[sail] = np.where(w_[sail] < 4.5, CRM, STL)
        t[lattice] = WOM
        t[rim] = D_OUT
        t[spar] = WOD
        t[spar & (np.abs(w_) > 0.5)] = D_OUT
    hub = ellipse(96, 80, hx, hy, 4, 4)
    t[hub] = RFM
    t[ellipse(96, 80, hx - 1, hy - 1, 2, 2)] = RFH
    t[edge_of(hub)] = D_OUT
    return t


def lab() -> np.ndarray:
    """Oak's lab, 9x5 blocks: a 6-block house with a grey metal roof and a 3-block greenhouse; door at (3, 4)."""
    t = np.zeros((80, 144), np.uint8)
    yy, xx = np.indices((80, 144))
    # main roof
    for y in range(4, 36):
        inset = max(0, 8 - (y - 4))
        x0, x1 = 1 + inset, 97 - inset
        t[y, x0:x1] = MTM
        for x in range(x0, x1):
            if (x - 1) % 8 == 0:
                t[y, x] = MTD
            elif (x - 1) % 8 == 1:
                t[y, x] = MTL
        t[y, x0] = L_OUT
        t[y, x1 - 1] = L_OUT
    t[4, 9:89] = L_OUT
    t[5, 9:89] = MTH
    t[6:8, 8:90] = MTL
    t[34, 1:97] = MTD
    t[35, 0:98] = L_OUT
    # vent chimney
    t[0:14, 78:86] = MTD
    t[0, 77:87] = L_OUT
    t[1:3, 78:86] = MTH
    t[0:14, 77] = L_OUT
    t[0:14, 86] = L_OUT
    # walls: white siding
    t[36:76, 2:96] = SIL
    for y in range(36, 76):
        if (y - 36) % 4 == 3:
            t[y, 2:96] = SIM
    t[36:38, 2:96] = SID
    t[36:76, 1] = L_OUT
    t[36:76, 96] = L_OUT
    # upper windows
    for wx in (6, 20, 68, 82):
        t[40:52, wx - 1:wx + 9] = L_OUT
        t[41:51, wx:wx + 8] = GLA
        t[41:44, wx:wx + 8] = GLH
        t[41:51, wx + 3:wx + 5] = LWD
        t[52, wx - 2:wx + 10] = SID
    # lower windows
    for wx in (6, 24, 70, 84):
        t[57:70, wx - 1:wx + 11] = L_OUT
        t[58:69, wx:wx + 10] = GLA
        t[58:61, wx:wx + 10] = GLH
        t[63, wx:wx + 10] = L_OUT
        t[58:69, wx + 4:wx + 6] = L_OUT
        t[70, wx - 2:wx + 12] = SID
    # sign over the door
    t[40:50, 34:62] = L_OUT
    t[41:49, 35:61] = LWH
    for x in range(38, 58, 3):
        t[43:47, x:x + 2] = MTD
    # double glass door at block (3, 4): x 48-63
    t[56:78, 46:66] = L_OUT
    t[57:78, 47:65] = DRG
    t[58:76, 49:55] = GLA
    t[58:76, 57:63] = GLA
    t[58:62, 49:55] = GLH
    t[58:62, 57:63] = GLH
    t[57:78, 55:57] = L_OUT
    t[66, 53:55] = MTH
    t[66, 57:59] = MTH
    # foundation
    t[75:79, 1:97] = MTM
    t[75, 1:97] = MTL
    t[79, 1:97] = L_OUT
    t[76:80, 46:66] = SIM  # the step
    t[79, 46:66] = L_OUT
    # greenhouse: glass panes in white frames, plants inside
    gx0, gx1 = 97, 143
    t[14:79, gx0:gx1] = GLA
    for y in range(14, 30):  # sloped glass roof
        t[y, gx0:gx1] = GLH if (y // 2) % 3 else GLA
    plant = np.zeros((80, 144), bool)
    r = random.Random(9)
    for _ in range(26):
        cx, cy = r.uniform(gx0 + 3, gx1 - 3), r.uniform(42, 74)
        plant |= ellipse(80, 144, cx, cy, r.uniform(2.5, 4.5), r.uniform(2.5, 4))
    plant &= (yy > 36) & (xx > gx0) & (xx < gx1)
    t[plant] = PLM
    t[plant & ((xx + yy) % 4 == 0)] = PLD
    t[edge_of(plant)] = PLD
    for y in (30, 46, 62):  # frame
        t[y:y + 2, gx0:gx1] = LWH
    for x in range(gx0, gx1, 11):
        t[14:79, x:x + 2] = LWH
    t[76:79, gx0:gx1] = MTM  # planter wall
    t[76, gx0:gx1] = MTL
    t[13, gx0:gx1] = L_OUT
    t[14:80, gx1] = L_OUT
    t[79, gx0:gx1 + 1] = L_OUT
    for y in range(14, 30):
        t[y, gx1 - 1] = L_OUT
    return t


# ---------------------------------------------------------------- plants (bank 8)
def flowers(seed: int, colours) -> np.ndarray:
    """A dense flower bed: leafy clumps under round blooms (petals around a bright middle)."""
    t = np.zeros((16, 16), np.uint8)
    r = random.Random(seed)
    for _ in range(7):  # leaves
        x, y = r.randrange(0, 15), r.randrange(2, 16)
        t[y, x] = LFM
        t[y, min(15, x + 1)] = LFD
        if y > 0:
            t[y - 1, x] = LFL
    spots = [(2, 2), (7, 1), (12, 3), (4, 7), (10, 7), (14, 9), (1, 11), (7, 12), (12, 13)]
    for i, (x, y) in enumerate(spots):
        x = (x + r.randint(-1, 1)) % 16
        y = max(1, min(14, y + r.randint(-1, 0)))
        c = colours[i % len(colours)]
        t[min(15, y + 2), x] = LFD
        for dx, dy in ((0, 0), (1, 0), (-1, 0), (0, 1), (0, -1), (1, 1)):
            if 0 <= x + dx < 16 and 0 <= y + dy < 16:
                t[y + dy, x + dx] = c
        t[min(15, y + 1), min(15, x + 1)] = LFD if c != PUR else PUR
        t[y, x] = YEL if c not in (YEL, ORG) else WHT
    return t


def lamp() -> np.ndarray:
    t = np.zeros((32, 16), np.uint8)
    t[10:29, 7:9] = IRON
    t[10:29, 6] = F_OUT
    t[10:29, 9] = F_OUT
    t[28:31, 4:12] = IRON
    t[28, 4:12] = F_OUT
    t[31, 4:12] = F_OUT
    t[28:31, 3] = F_OUT
    t[28:31, 12] = F_OUT
    # lantern
    t[3:10, 4:12] = F_OUT
    t[4:9, 5:11] = GLOW
    t[4:9, 8] = IRON
    t[5:7, 6] = WHT
    t[1:3, 5:11] = IRON
    t[0, 6:10] = F_OUT
    t[1, 5] = F_OUT
    t[1, 10] = F_OUT
    t[10, 5:11] = IRON
    return t


# ---------------------------------------------------------------- layout
def layout() -> tuple[list[list[str]], dict]:
    g = [["." for _ in range(MAP_W)] for _ in range(MAP_H)]

    def put(ch, x0, y0, w=1, h=1):
        for y in range(y0, y0 + h):
            for x in range(x0, x0 + w):
                g[y][x] = ch

    def rect_fence(x0, y0, x1, y1, gaps=()):
        for x in range(x0, x1 + 1):
            for y in (y0, y1):
                if (x, y) not in gaps:
                    g[y][x] = "#"
        for y in range(y0, y1 + 1):
            for x in (x0, x1):
                if (x, y) not in gaps:
                    g[y][x] = "#"
    # forest: top, bottom, west; pines down the east side of the yards
    put("T", 0, 0, MAP_W, 2)
    put("T", 0, 26, MAP_W, 2)
    put("T", 0, 0, 2, MAP_H)
    put("T", 24, 2, 2, 6)
    # the sea under the cliff
    put("s", 28, 2, 4, 24)
    # the way north (Route 1)
    put(":", 14, 0, 2, 9)
    # yards and houses
    rect_fence(4, 2, 12, 8, gaps={(7, 8)})
    rect_fence(16, 2, 23, 8, gaps={(18, 8)})
    put("H", 6, 3, 5, 5)
    put("H", 17, 3, 5, 5)
    for x, y in ((5, 3), (11, 3), (22, 3), (11, 7)):
        put("b", x, y)
    for x, y in ((5, 5), (5, 6), (11, 5), (22, 5), (22, 6)):
        put("*", x, y)
    # roads
    put("=", 7, 8)
    put("=", 18, 8)
    put("=", 5, 9, 16, 2)
    put("=", 14, 11, 2, 12)
    put("=", 8, 21, 6, 2)
    put("=", 16, 17, 10, 2)
    put("=", 21, 16)
    put(":", 26, 17, 2, 2)
    # windmill in its flower garden
    rect_fence(2, 13, 12, 19, gaps={(5, 19)})
    put("W", 3, 11, 5, 6)
    put("*", 8, 14, 4, 5)
    put("*", 3, 17, 5, 2)
    put(":", 5, 17, 1, 3)
    put(":", 5, 20)
    # the well on its patch of dirt
    put(":", 4, 21, 4, 4)
    put("w", 5, 22, 2, 2)
    put("R", 2, 21, 2, 2)
    put("R", 9, 23, 2, 2)
    put("k", 3, 24)
    # Oak's lab
    put("L", 18, 11, 9, 5)
    put("R", 16, 11, 2, 2)
    put("l", 17, 14, 1, 2)
    put("l", 4, 9, 1, 2)
    put("l", 27, 13, 1, 2)
    put("l", 13, 17, 1, 2)
    for x, y in ((20, 16), (22, 16), (16, 13), (27, 9), (27, 22)):
        put("b", x, y)
    # the pond and its dock; the channel south (Route 21)
    put("~", 16, 20, 11, 6)
    put("~", 18, 26, 4, 2)
    for x in list(range(16, 21)) + list(range(23, 27)):
        put("#", x, 19)
    put("d", 21, 19, 2, 1)
    put("d", 19, 20, 7, 2)
    put("d", 21, 22, 2, 3)
    put("B", 24, 20)
    put("B", 25, 20)
    put("c", 19, 20)
    put("O", 23, 23, 2, 1)
    # rocks and details
    for x, y in ((12, 24), (27, 6), (13, 25), (27, 25), (2, 10), (27, 19)):
        put("o", x, y)
    for x, y in ((3, 6), (13, 4), (21, 9), (24, 9), (2, 3), (9, 25), (14, 24), (6, 25)):
        put(",", x, y)
    # signs (bg events)
    signs = {"PlayersHouseSign": (5, 7), "RivalsHouseSign": (22, 7), "OaksLabSign": (19, 16),
             "TownSign": (13, 11), "TrainerTips": (10, 20)}
    for x, y in signs.values():
        put("S", x, y)
    return g, signs


# ---------------------------------------------------------------- sheets and spec
class Sheet:
    """Cells of one palette packed into an image, with spec entries for them."""

    def __init__(self, name: str, pal: str, cols: int = 16):
        self.name, self.pal, self.cols = name, pal, cols
        self.cells: list[tuple[str, np.ndarray, dict]] = []

    def add(self, name, idx, **entry):
        self.cells.append((name, idx, entry))

    def write(self, frames: list[list[np.ndarray]] | None = None) -> list[dict]:
        # rows of 16 px; bigger cells go on their own rows
        x = y = rowh = 0
        place = []
        width = self.cols * 16
        for name, idx, entry in self.cells:
            h, w = idx.shape
            if x + w > width:
                x, y, rowh = 0, y + rowh, 0
            place.append((x, y))
            x += w
            rowh = max(rowh, h)
        total_h = y + rowh
        out = []
        for k, im in enumerate([None] + (frames or [])):
            canvas = np.zeros((total_h, width), np.uint8)
            for i, ((name, idx, entry), (px, py)) in enumerate(zip(self.cells, place)):
                cell = idx if im is None else im[i]
                canvas[py:py + cell.shape[0], px:px + cell.shape[1]] = cell
            fn = f"sheets/{self.name}.png" if im is None else f"sheets/{self.name}_f{k}.png"
            Image.fromarray(rgba(canvas, PALS[self.pal]), "RGBA").save(HERE / fn)
        for (name, idx, entry), (px, py) in zip(self.cells, place):
            e = {"name": name, "image": f"sheets/{self.name}.png", "x": px, "y": py,
                 "w": idx.shape[1] // 16, "h": idx.shape[0] // 16, "banks": [BANK[self.pal]]}
            e.update(entry)
            out.append(e)
        return out


def main() -> None:
    (HERE / "sheets").mkdir(exist_ok=True)
    spec_mt = []
    # ground (primary)
    ground = Sheet("ground", "ground")
    for i, kw in enumerate(({}, {"clover": True}, {}, {"daisies": 2})):
        ground.add("grass" if i == 0 else f"grass{i + 1}", grass(3 + i * 11, **kw), tileset="primary")
    ground.add("grass_daisies", grass(61, daisies=4), tileset="primary")
    for m in range(16):
        ground.add(f"cobble#{m}", cobble(m), tileset="primary", ground="grass")
    for m in range(16):
        ground.add(f"dirt#{m}", dirt(m), tileset="primary", ground="grass")
    ground.add("rock", rock(1, True), tileset="primary", ground="grass", solid=True)
    ground.add("stump", stump(), tileset="primary", ground="grass", solid=True)
    spec_mt += ground.write()
    # water (primary), animated (water.py)
    sheet_w = Sheet("water", "water")
    cells = []  # (name, kind, mask, variant)
    for kind in ("pond", "sea"):
        for m in range(16):
            cells.append((f"{kind}#{m}", kind, m, 0))
        cells += [(f"{kind}#15~{v}", kind, 15, v) for v in (1, 2)]  # open water with its sparkles elsewhere
    for name, kind, m, v in cells:
        extra = {"solid": True} if kind == "sea" else {}
        sheet_w.add(name, water.shore(m, 0, kind, v), tileset="primary", ground="grass", behavior="MB_POND_WATER",
                    elevation=1, **extra)
    frames = [[water.shore(m, f, kind, v) for _, kind, m, v in cells] for f in range(1, water.FRAMES)]
    spec_mt += sheet_w.write(frames)
    # wood (primary: small things; secondary: buildings)
    wood = Sheet("wood", "wood")
    for m in range(16):
        wood.add(f"fence#{m}", fence(m), tileset="primary", ground="grass", solid=True)
    for m in range(16):
        wood.add(f"dock#{m}", planks(m), tileset="primary", ground="pond#15")
    wood.add("sign", sign(), tileset="primary", ground="grass", solid=True)
    wood.add("barrel", barrel(), tileset="primary", ground="dock#15", solid=True)
    wood.add("crate", crate(), tileset="primary", ground="dock#15", solid=True)
    wood.add("boat", boat(), tileset="primary", ground="pond#15", solid=True, elevation=1)
    wood.add("well", well(), tileset="primary", ground="dirt#15", solid=True)
    spec_mt += wood.write()
    plants = Sheet("plants", "plants")
    for i, cols in enumerate(((RED, PINK, YEL), (PUR, WHT, PINK), (YEL, ORG, RED), (BLU, WHT, PUR))):
        plants.add(f"flowers{i + 1}", flowers(10 + i, cols), tileset="primary", ground="grass")
    plants.add("lamp", lamp(), tileset="primary", ground="grass", solid=True)
    spec_mt += plants.write()
    tree_sheet = Sheet("trees", "trees")
    for m in range(16):  # forest#mask: a 2x2 pine for each way the forest goes on (paint picks it per cell)
        tree_sheet.add(f"forest#{m}", trees.pine(m), tileset="primary", solid=True, ground="grass")
    tree_sheet.add("round_tree", trees.round_tree(), tileset="primary", ground="grass", solid=True)
    tree_sheet.add("bush", trees.bush(2), tileset="primary", ground="grass", solid=True)
    spec_mt += tree_sheet.write()
    big = Sheet("buildings", "wood", cols=10)
    big.add("house", house(), tileset="secondary", ground="grass", solid=True, open=["1,4"],
            behaviors={"1,4": "MB_ANIMATED_DOOR"})
    big.add("windmill", windmill(), tileset="secondary", ground="grass", solid=True)
    spec_mt += big.write()
    labs = Sheet("lab", "lab", cols=9)
    labs.add("lab", lab(), tileset="secondary", ground="grass", solid=True, open=["3,4"],
             behaviors={"3,4": "MB_ANIMATED_DOOR"})
    spec_mt += labs.write()
    for e in spec_mt:  # sheets put "w"/"h" on everything; drop the 1x1 ones for readability
        if e["w"] == 1 and e["h"] == 1:
            del e["w"], e["h"]
    for name, pal in PALS.items():
        with open(HERE / f"palette_{name}.pal", "w") as f:
            f.write("JASC-PAL\r\n0100\r\n16\r\n" + "".join(f"{r} {g} {b}\r\n" for r, g, b in pal))
    spec = {"version": "hns", "primary": "gTileset_PalletConcept_General", "secondary": "gTileset_PalletConcept",
            "palettes": {"primary": ["palette_ground.pal", "palette_water.pal", "palette_wood.pal",
                                     "palette_trees.pal"],
                         "secondary": ["palette_lab.pal", "palette_plants.pal"]},
            "reserve": {"primary": [[434, 441]]},
            "animations": [{"name": "Water", "image": "sheets/water.png",
                            "frames": [f"sheets/water_f{k}.png" for k in range(1, water.FRAMES)], "speed": 16}],
            "metatiles": spec_mt}
    (HERE / "spec.json").write_text(json.dumps(spec, indent=1) + "\n")
    g, signs = layout()
    (HERE / "grid.txt").write_text("".join("".join(r) + "\n" for r in g))
    (HERE / "border.txt").write_text("TT\nTT\n")
    legend = {
        "T": {"auto": "forest"},
        ".": {"pick": ["grass", "grass", "grass2", "grass3", "grass", "grass4"]},
        ",": "grass_daisies",
        "=": {"auto": "cobble"}, ":": {"auto": "dirt"},
        "~": {"auto": "pond", "elevation": 1}, "s": {"auto": "sea", "elevation": 1},
        "#": {"auto": "fence"}, "d": {"auto": "dock"},
        "*": {"pick": ["flowers1", "flowers2", "flowers3", "flowers4"]},
        "b": "bush", "o": "rock", "k": "stump", "l": "lamp", "S": "sign", "B": "barrel", "c": "crate", "O": "boat",
        "w": "well", "R": "round_tree", "H": "house", "W": "windmill", "L": "lab",
    }
    (HERE / "legend.json").write_text(json.dumps(legend, indent=1) + "\n")
    (HERE / "signs.json").write_text(json.dumps(signs, indent=1) + "\n")
    print(f"{len(spec_mt)} metatiles in the spec; grid {MAP_W}x{MAP_H}")


if __name__ == "__main__":
    main()
