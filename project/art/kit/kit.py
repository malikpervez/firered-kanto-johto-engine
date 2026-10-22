"""The kit: the building blocks every rebuilt map shares, drawn here (and in trees.py, fields.py) or taken from
native pixel packs (lawn.py, water.py, tall_grass/), and built
into one primary tileset, gTileset_PalletConcept_General.

Each map's make_art.py puts ``primary_entries()`` first in its spec, unchanged, then its own secondary tileset's
pieces, so every map's build makes the same primary tileset: a map's secondary tiles may then use the primary's
tiles, and rebuilding one map never breaks another. Change the kit, then rebuild every map (project/art/build_all.sh).

Banks (palettes):
  0  ground: grass, dirt, cobblestones, dressed-stone paving (paving/, a native pixel pack), rocks, stumps; ledges,
     steps, lily pads and reeds (fields.py,
     the last two drawn over the pond's water), and the tall grass sprite drawn over the player's feet
  1  water: the pond and the sea, its cliff and the sea rocks (native pixel packs in pond/ and sea/, put together
     in water.py), animated in eight frames
  2  wood: fences, the dock, signs, barrels, crates, the boat, the well (and buildings drawn in wood)
  3  trees: the pines, round trees and bushes (trees.py)
  4  tall grass: tall_grass/ (drawn natively at 16x16, made with another AI from a brief) and the sprites over
     the player's feet in it
  5  the Pokémon Center, 6  the Poké Mart: buildings every town shares (buildings/, native pixel packs; buildings.py),
     each in its own palette, with drawn door frames
  8  plants: flowers and lamps. The primary uses it, so every map's secondary tileset has the kit's plants
     palette at bank 8 (``SECONDARY_BANKS``); banks 7, 9-12 are the map's own.
"""
import math
import random
from pathlib import Path

import numpy as np
from PIL import Image

import autotile
import buildings
import fields
import lawn
import trees
import water

KIT = Path(__file__).resolve().parent
PRIMARY = "gTileset_PalletConcept_General"

P0 = [(0, 0, 0), (24, 32, 32), (40, 96, 56), (48, 112, 60), (56, 120, 64), (88, 160, 72), (120, 192, 88),
      (168, 216, 112), (112, 72, 48), (176, 128, 80), (216, 176, 120), (96, 96, 96), (144, 144, 136),
      (192, 192, 176), (72, 48, 40), (240, 240, 224)]
OUT, G0, G1, GD, GM, GL, GH, SD, SM, SL, KD, KM, KL, TR, CR = range(1, 16)  # six greens
# the lawn (lawn/<option>/, lawn.py): its six greens take the six green slots
LAWN = "B_Lush_Emerald"
P0[G0:GH + 1] = lawn.greens(LAWN)

P2 = [(0, 0, 0), (40, 24, 24), (88, 48, 32), (136, 80, 48), (184, 120, 72), (224, 168, 112), (120, 32, 32),
      (176, 56, 48), (224, 96, 72), (248, 152, 120), (40, 56, 96), (96, 144, 200), (176, 216, 240),
      (240, 232, 208), (120, 120, 128), (184, 184, 184)]
D_OUT, WOD, WOM, WOL, WOH, RFD, RFM, RFL, RFH, NWD, NWM, NWL, CRM, STG, STL = range(1, 16)

P4 = [(0, 0, 0), (24, 32, 32), (32, 80, 48), (56, 128, 64), (104, 176, 80), (160, 208, 104), (208, 64, 64),
      (240, 136, 168), (248, 208, 72), (240, 144, 64), (144, 104, 200), (104, 152, 232), (248, 248, 240),
      (56, 56, 64), (248, 232, 160), (96, 64, 40)]
F_OUT, LFD, LFM, LFL, LFH, RED, PINK, YEL, ORG, PUR, BLU, WHT, IRON, GLOW, TRUNK = range(1, 16)

# tall grass (tall_grass/: tiles drawn natively at 16x16, with the grass the game draws over the player's feet):
# its own palette. Its ground (the pack's two ground colours) shows the lawn's own texture instead, so a patch sits in
# the lawn: the lawn's greens take those two slots and the three free ones (the darkest folds into the next)
PTG_PACK = [(255, 0, 255), (120, 192, 88), (88, 160, 72), (184, 232, 144), (136, 200, 104), (64, 144, 56), (40, 112, 48),
       (32, 136, 96), (24, 96, 72), (56, 88, 24), (32, 56, 24), (240, 240, 224), (232, 200, 96), (0, 0, 0), (0, 0, 0),
       (0, 0, 0)]
LAWN_IN_PTG = {G0: 1, G1: 1, GD: 2, GM: 13, GL: 14, GH: 15}
PTG = list(PTG_PACK)
for _g, _slot in LAWN_IN_PTG.items():
    PTG[_slot] = P0[_g]
BANK = {"ground": 0, "water": 1, "wood": 2, "trees": 3, "tallgrass": 4, "center": 5, "mart": 6, "plants": 8}
PALS = {"ground": P0, "water": water.PW, "wood": P2, "trees": trees.PT, "tallgrass": PTG,
        "center": buildings.CENTER.palette, "mart": buildings.MART.palette, "plants": P4}
# the shared buildings, by their names in the spec; a map animates their doors with ``pae door add --frames``
SHARED_BUILDINGS = {"pokemon_center": (buildings.CENTER, "center"), "poke_mart": (buildings.MART, "mart")}
# the two kinds, staggered in a field ("g" in the legend): two fronds (B), and a sprig with flowers (C); each has
# its own sprite over the player's feet, so the leaves over them are always the block's own
TALL_GRASS = {"tall_grass": "B", "tall_grass_flowers": "C"}
TALL_GRASS_FLOOR = {"B": "lawn_a", "C": "lawn_b"}  # the lawn tile each kind's ground shows
SECONDARY_BANKS = {8: "plants"}  # banks the primary uses from the secondary tileset

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

# ---------------------------------------------------------------- forest pieces
# (mask, corners) of the forest's inside-corner pieces in the kit: every map's together (a map checks its own are
# here with ``forest_corners``; add new ones here, then rebuild every map)
FOREST_CORNERS = [(15, 1), (15, 2), (15, 6), (15, 4), (15, 8), (7, 1), (7, 2), (13, 4), (14, 4)]


def forest_corners(g, char: str = "T") -> set[tuple[int, int]]:
    """(mask, corners) of the forest's 2x2 cells in grid ``g`` with an inside corner (as pae map paint works them
    out)."""
    h, w = len(g), len(g[0])

    def forest(cx, cy):
        return all(not (0 <= y < h and 0 <= x < w) or g[y][x] == char
                   for y in range(cy, cy + 2) for x in range(cx, cx + 2))
    out = set()
    for cy in range(0, h, 2):
        for cx in range(0, w, 2):
            if not forest(cx, cy):
                continue
            mask = sum(bit for bit, (dx, dy) in ((1, (0, -1)), (2, (1, 0)), (4, (0, 1)), (8, (-1, 0)))
                       if forest(cx + 2 * dx, cy + 2 * dy))
            diagonals = ((1, (1, -1), 3), (2, (1, 1), 6), (4, (-1, 1), 12), (8, (-1, -1), 9))
            corners = sum(bit for bit, (dx, dy), sides in diagonals
                          if mask & sides == sides and not forest(cx + 2 * dx, cy + 2 * dy))
            if corners:
                out.add((mask, corners))
    return out


def check_forest(g, char: str = "T") -> None:
    missing = forest_corners(g, char) - set(FOREST_CORNERS)
    if missing:
        raise SystemExit(f"the forest needs inside-corner pieces the kit doesn't have: {sorted(missing)}; "
                         "add them to kit.FOREST_CORNERS and rebuild every map")


# (mask, corners) of the inside-corner pieces of the pond and the sea in the kit: every map's together
# (``check_water``)
WATER_CORNERS = {"pond": [(11, 8), (13, 8), (14, 2), (14, 4), (15, 1), (15, 4), (15, 8), (15, 2), (15, 10)],
                 "sea": []}
# the legend characters that are each water (lily pads and reeds join the pond, the sea rocks the sea); the first is
# the plain water, the others are drawn as they are
WATER = {"pond": ("~", "v", "r"), "sea": ("s", "q", "Q")}


def water_corners(g, kind: str) -> set[tuple[int, int]]:
    """(mask, corners) of the plain ``kind`` water blocks in grid ``g`` with an inside corner, as pae map paint works
    them out."""
    h, w = len(g), len(g[0])
    chars = WATER[kind]

    def water_at(x, y):
        return not (0 <= y < h and 0 <= x < w) or g[y][x] in chars
    out = set()
    for y in range(h):
        for x in range(w):
            if g[y][x] not in chars:
                continue
            mask = sum(bit for bit, (dx, dy) in ((1, (0, -1)), (2, (1, 0)), (4, (0, 1)), (8, (-1, 0)))
                       if water_at(x + dx, y + dy))
            corners = sum(bit for bit, (dx, dy), sides in ((1, (1, -1), 3), (2, (1, 1), 6), (4, (-1, 1), 12),
                                                           (8, (-1, -1), 9))
                          if mask & sides == sides and not water_at(x + dx, y + dy))
            if corners and g[y][x] == chars[0]:
                out.add((mask, corners))
            if g[y][x] != chars[0] and mask != 15:
                raise SystemExit(f"({x},{y}): '{g[y][x]}' needs {kind} all round it (it is drawn in open water)")
    return out


# the dressed-stone paving (paving/, a native pixel pack in the ground palette: autotile.py), its inside corners in
# the kit (every map's together: ``check_paving``) and its pieces that meet other roads ("to_cobble_N": cobble on the
# north half, paving on the south)
PAVING = KIT / "paving"
PAVING_CORNERS = [(11, 1), (11, 8), (15, 3), (15, 4), (15, 8)]
PAVING_CHARS = ("p", "n")  # the legend characters that are paving (the plain stone, and a map's joins to cobble)
PAVING_JOINS = [f"to_{m}_{d}" for m in ("cobble", "dirt") for d in "NESW"]
_paving: dict[str, np.ndarray] = {}


def paving_piece(name: str) -> np.ndarray:
    if name not in _paving:
        _paving[name] = autotile.load(PAVING / f"{name}.png", P0)
    return _paving[name]


def check_paving(g, joins: str = "") -> None:
    """The paving's inside corners in ``g`` are the kit's; ``joins``: a map's characters that count as paving for
    their neighbours (e.g. stairs it opens onto)."""
    missing = autotile.corners_in(g, PAVING_CHARS + tuple(joins), "p") - set(PAVING_CORNERS)
    if missing:
        raise SystemExit(f"the paving needs inside-corner pieces the kit doesn't have: {sorted(missing)}; "
                         "add them to kit.PAVING_CORNERS and rebuild every map")


def check_water(g) -> None:
    for kind in WATER:
        missing = water_corners(g, kind) - set(WATER_CORNERS[kind])
        if missing:
            raise SystemExit(f"the {kind} needs inside-corner pieces the kit doesn't have: {sorted(missing)}; "
                             "add them to kit.WATER_CORNERS and rebuild every map")


# ---------------------------------------------------------------- sheets and spec
class Sheet:
    """Cells of one palette packed into an image, with spec entries for them. The image goes in ``out``/sheets;
    the spec names it relative to ``spec_dir``."""

    def __init__(self, name: str, pal, bank: int, out: Path, spec_dir: Path, cols: int = 16):
        self.name, self.pal, self.bank, self.cols = name, pal, bank, cols
        self.out, self.rel = out, Path(os_relpath(out, spec_dir))
        self.cells: list[tuple[str, np.ndarray, dict]] = []

    def add(self, name, idx, **entry):
        self.cells.append((name, idx, entry))

    def write(self, frames: list[list[np.ndarray]] | None = None) -> list[dict]:
        # rows of 16 px; bigger cells go on their own rows
        (self.out / "sheets").mkdir(exist_ok=True)
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
            Image.fromarray(rgba(canvas, self.pal), "RGBA").save(self.out / fn)
        for (name, idx, entry), (px, py) in zip(self.cells, place):
            e = {"name": name, "image": self.path(f"sheets/{self.name}.png"), "x": px, "y": py,
                 "w": idx.shape[1] // 16, "h": idx.shape[0] // 16, "banks": [self.bank]}
            e.update(entry)
            out.append(e)
        return out

    def path(self, rel: str) -> str:
        return (self.rel / rel).as_posix()


def os_relpath(a: Path, b: Path) -> str:
    import os
    return os.path.relpath(a, b)


def _tall_grass(fn: str) -> np.ndarray:
    """A picture from tall_grass/ as indices of PTG (its colours must be the pack's; transparent is 0), its ground
    showing the lawn tile under it (in each 16-pixel frame, so the sprite over the player's feet matches the block)."""
    with Image.open(KIT / "tall_grass" / fn) as im:
        a = np.array(im.convert("RGBA"))
    out = np.zeros(a.shape[:2], np.uint8)
    lut = {c: i for i, c in enumerate(PTG_PACK) if i}  # the pack's colours (its ground is then the lawn's)
    for y in range(a.shape[0]):
        for x in range(a.shape[1]):
            r, g, b, al = (int(v) for v in a[y, x])
            if al:
                if (r, g, b) not in lut:
                    raise SystemExit(f"tall_grass/{fn}: ({r},{g},{b}) at {x},{y} is not in the tall grass palette")
                out[y, x] = lut[(r, g, b)]
    floor = lawn.tiles(LAWN, P0)[TALL_GRASS_FLOOR[fn[0]]]
    floor = np.vectorize(lambda i: LAWN_IN_PTG.get(i, 0))(np.tile(floor, (1, out.shape[1] // 16)))
    ground = (out == 1) | (out == 2)  # the pack's two ground colours
    out[ground] = floor[ground]
    return out


def write_palette(path: Path, pal) -> None:
    with open(path, "w") as f:
        f.write("JASC-PAL\r\n0100\r\n16\r\n" + "".join(f"{r} {g} {b}\r\n" for r, g, b in pal))


def primary(spec_dir: Path) -> dict:
    """The kit's part of a map's spec: its metatiles (all primary), palettes, animations and reserved tiles. Draws
    the sheets and palettes into the kit's folder; the spec (in ``spec_dir``) names them from there."""
    spec_dir = Path(spec_dir)

    def sheet(name, pal, cols=16):
        return Sheet(name, PALS[pal], BANK[pal], KIT, spec_dir, cols)
    spec_mt = []
    # ground
    ground = sheet("ground", "ground")
    lawns = lawn.tiles(LAWN, P0)
    ground.add("grass", lawns["lawn_a"], tileset="primary")  # the ground under paths and things
    for name, t in lawns.items():  # the lawn, scattered ("." in the legend), and with daisies (",")
        ground.add(name, t, tileset="primary")
    for m in range(16):
        ground.add(f"cobble#{m}", cobble(m), tileset="primary", ground="grass")
    for m in range(16):
        ground.add(f"dirt#{m}", dirt(m), tileset="primary", ground="grass")
    for m in range(16):  # the dressed-stone paving (paving/)
        ground.add(f"paving#{m}", autotile.compose(paving_piece, m), tileset="primary", ground="grass")
    for v in (1, 2):
        ground.add(f"paving#15~{v}", autotile.compose(paving_piece, 15, v), tileset="primary", ground="grass")
    for m, c in PAVING_CORNERS:
        ground.add(f"paving#{m}.{c}", autotile.compose(paving_piece, m, 0, c), tileset="primary", ground="grass")
    for name in PAVING_JOINS:
        ground.add(f"paving_{name}", paving_piece(name), tileset="primary", ground="grass")
    ground.add("rock", rock(1, True), tileset="primary", ground="grass", solid=True)
    ground.add("stump", stump(), tileset="primary", ground="grass", solid=True)
    spec_mt += ground.write()
    # water, animated: the pond and the sea from their packs (water.py)
    sheet_w = sheet("water", "water")
    cells = []  # (name, kind, the block at frame k)
    for kind in WATER:
        for m in range(16):
            cells.append((f"{kind}#{m}", kind, lambda k, kind=kind, m=m: water.piece(kind, m, k)))
        for v in (1, 2):  # open water with its sparkles elsewhere
            cells.append((f"{kind}#15~{v}", kind, lambda k, kind=kind, v=v: water.piece(kind, 15, k, v)))
        for m, c in WATER_CORNERS[kind]:  # inside corners
            cells.append((f"{kind}#{m}.{c}", kind, lambda k, kind=kind, m=m, c=c: water.piece(kind, m, k, 0, c)))
    for piece in ("rock_a", "rock_b"):  # rocks standing in the sea, with surf round them
        cells.append((f"sea#15+{piece}", "sea", lambda k, piece=piece: water.frame("sea", piece, k)))
    for name, kind, block in cells:
        extra = {"solid": True} if kind == "sea" else {}
        sheet_w.add(name, block(0), tileset="primary", ground="grass", behavior="MB_POND_WATER",
                    elevation=1, **extra)
    frames = [[block(f) for _, _, block in cells] for f in range(1, water.FRAMES)]
    spec_mt += sheet_w.write(frames)
    # wood
    wood = sheet("wood", "wood")
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
    plants = sheet("plants", "plants")
    for i, cols in enumerate(((RED, PINK, YEL), (PUR, WHT, PINK), (YEL, ORG, RED), (BLU, WHT, PUR))):
        plants.add(f"flowers{i + 1}", flowers(10 + i, cols), tileset="primary", ground="grass")
    plants.add("lamp", lamp(), tileset="primary", ground="grass", solid=True)
    spec_mt += plants.write()
    tree_sheet = sheet("trees", "trees")
    for m in range(16):  # forest#mask: a 2x2 pine for each way the forest goes on (paint picks it per cell)
        tree_sheet.add(f"forest#{m}", trees.pine(m), tileset="primary", solid=True, ground="grass")
    for m, c in FOREST_CORNERS:  # forest#mask.corners: where an inside corner opens onto the map
        tree_sheet.add(f"forest#{m}.{c}", trees.pine(m, c), tileset="primary", solid=True, ground="grass")
    tree_sheet.add("round_tree", trees.round_tree(), tileset="primary", ground="grass", solid=True)
    tree_sheet.add("bush", trees.bush(2), tileset="primary", ground="grass", solid=True)
    spec_mt += tree_sheet.write()
    # route pieces (fields.py): tall grass, ledges, steps, lily pads and reeds
    tall = sheet("tall_grass", "tallgrass")
    for name, v in TALL_GRASS.items():
        tall.add(name, _tall_grass(f"{v}_tile_16x16.png"), tileset="primary", behavior="MB_TALL_GRASS")
    spec_mt += tall.write()
    field = sheet("fields", "ground")
    for m in (0, 2, 8, 10):  # ledges join east-west only
        field.add(f"ledge#{m}", fields.ledge(m), tileset="primary", ground="grass", solid=True,
                  behavior="MB_JUMP_SOUTH")
    for m in range(16):  # steps by their neighbours east and west (stairs more than a row tall: the same steps)
        field.add(f"steps#{m}", fields.steps(m & 10), tileset="primary", ground="grass")
    field.add("pond#15+lily", fields.lily(), tileset="primary", ground="pond#15", behavior="MB_POND_WATER",
              elevation=1)
    field.add("pond#15+reeds", fields.reeds(), tileset="primary", ground="pond#15", behavior="MB_POND_WATER",
              elevation=1, solid=True)
    spec_mt += field.write()
    for name, (b, pal) in SHARED_BUILDINGS.items():  # the Pokémon Center and the Poké Mart
        sh = sheet(name, pal, cols=b.idx.shape[1] // 16)
        sh.add(name, b.idx, tileset="primary", **b.entry())
        spec_mt += sh.write()
    (KIT / "sheets").mkdir(exist_ok=True)
    for name, v in TALL_GRASS.items():
        Image.fromarray(rgba(_tall_grass(f"{v}_feet_80x16.png"), PTG), "RGBA").save(KIT / f"sheets/{name}_fx.png")
    for name, pal in PALS.items():
        write_palette(KIT / f"palette_{name}.pal", pal)
    rel = Path(os_relpath(KIT, spec_dir))
    return {
        "metatiles": spec_mt,
        "palettes": [(rel / f"palette_{n}.pal").as_posix()
                     for n in ("ground", "water", "wood", "trees", "tallgrass", "center", "mart")],
        "secondary_palettes": {b: (rel / f"palette_{n}.pal").as_posix() for b, n in SECONDARY_BANKS.items()},
        "reserve": [[434, 441]],
        "animations": [{"name": "Water", "image": (rel / "sheets/water.png").as_posix(),
                        "frames": [(rel / f"sheets/water_f{k}.png").as_posix() for k in range(1, water.FRAMES)],
                        "speed": 10}],  # 10 game frames (about 160 ms) a frame, as the pond pack's
        "field_effects": {"tall_grass": {"image": (rel / "sheets/tall_grass_fx.png").as_posix(), "bank": 4,
                                         "tileset": "primary",
                                         "metatiles": {n: (rel / f"sheets/{n}_fx.png").as_posix()
                                                       for n in TALL_GRASS if n != "tall_grass"}}},
    }


# the legend characters every map shares
LEGEND = {
    "T": {"auto": "forest"},
    ".": {"pick": list(lawn.PLAIN)},
    ",": "lawn_flowers",
    "=": {"auto": "cobble"}, ":": {"auto": "dirt"},
    "~": {"auto": "pond", "elevation": 1}, "s": {"auto": "sea", "elevation": 1},
    "#": {"auto": "fence"}, "d": {"auto": "dock"},
    "*": {"pick": ["flowers1", "flowers2", "flowers3", "flowers4"]},
    "b": "bush", "o": "rock", "k": "stump", "l": "lamp", "S": "sign", "B": "barrel", "c": "crate", "O": "boat",
    "w": "well", "R": "round_tree",
    "g": {"pick": ["tall_grass", "tall_grass_flowers"], "order": "checker"},
    "_": {"auto": "ledge"}, "h": {"auto": "steps"},
    "v": {"auto": "pond", "joins": "~", "with": "lily", "elevation": 1},
    "r": {"auto": "pond", "joins": "~", "with": "reeds", "elevation": 1},
    "p": {"auto": "paving"},
    "q": {"auto": "sea", "joins": "s", "with": "rock_a", "elevation": 1},
    "Q": {"auto": "sea", "joins": "s", "with": "rock_b", "elevation": 1},
}
