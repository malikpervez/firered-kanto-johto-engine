#!/usr/bin/env python3
"""Pallet Town from scratch: draws every tile, then writes what `pae` builds the tilesets and the map from.

Nothing here comes from an existing tileset: grass, paths, water, trees, flowers, fences, signs, the two houses and
Oak's lab are drawn below, pixel by pixel, in three palettes made for them.

Palettes (the seams decide them): from Route 1 and Route 21 only one palette slot is free, so everything in Pallet's
top seven rows uses palette A and everything in its bottom seven rows palette B. A and B share their first ten
colours (outline, greens, path, wood, white, grey); A adds the roof reds and window blue, B the water blues and the
flower pink. Palette C is the lab's.

Run from the repository root:  python3 project/art/pallet-from-scratch/make_art.py
It writes sheets/*.png, spec.json, grid.txt, border.txt and legend.json next to itself; then:
  pae tileset build project/art/pallet-from-scratch/spec.json -p engine
  pae map paint PalletTown_Frlg project/art/pallet-from-scratch/grid.txt project/art/pallet-from-scratch/legend.json \
      --names project/art/pallet-from-scratch/names.json --border project/art/pallet-from-scratch/border.txt -p engine
"""
import json
import random
from pathlib import Path

import numpy as np
from PIL import Image

HERE = Path(__file__).resolve().parent

SHARED = [(112, 176, 80), (24, 40, 32), (40, 88, 56), (72, 136, 64), (112, 176, 80), (168, 216, 112),
          (200, 168, 104), (232, 208, 144), (128, 80, 48), (248, 248, 232), (152, 160, 168)]
A = SHARED + [(136, 40, 40), (200, 64, 56), (240, 120, 96), (88, 144, 208), (248, 216, 88)]
B = SHARED + [(40, 96, 176), (72, 144, 216), (160, 208, 248), (232, 104, 136), (248, 216, 88)]
C = [(0, 0, 0), (32, 40, 48), (40, 88, 104), (64, 136, 152), (120, 192, 200), (152, 160, 168), (248, 248, 232),
     (248, 248, 248), (136, 96, 64), (40, 96, 176), (72, 144, 216), (160, 208, 248), (120, 128, 136),
     (72, 136, 64), (112, 176, 80), (248, 216, 88)]
# colour names (palette A/B indices)
OUT, DARK, MID, LIGHT, HI, PATH, PATHL, WOOD, WHITE, GREY = 1, 2, 3, 4, 5, 6, 7, 8, 9, 10
ROOFD, ROOF, ROOFL, WIN, YEL = 11, 12, 13, 14, 15          # A
WATD, WAT, WATL, PINK = 11, 12, 13, 14                     # B


def rgba(idx: np.ndarray, pal) -> Image.Image:
    """Index image -> RGBA (index 0 transparent)."""
    out = np.zeros(idx.shape + (4,), np.uint8)
    for i, c in enumerate(pal):
        if i:
            out[idx == i] = (*c, 255)
    return Image.fromarray(out, "RGBA")


# ---------------------------------------------------------------- ground (palette A/B colours 1-10, plus B extras)
def grass(seed: int) -> np.ndarray:
    r = random.Random(seed)
    t = np.full((16, 16), LIGHT, np.uint8)
    for _ in range(4):  # little tufts: a highlight over two shadow strokes
        x, y = r.randrange(0, 14), r.randrange(1, 15)
        t[y - 1, x + 1] = HI
        t[y, x] = MID
        t[y, x + 2] = MID
    for _ in range(3):
        t[r.randrange(16), r.randrange(16)] = HI
    return t


def path(mask: int, seed: int = 7) -> np.ndarray:
    """Dirt path; a soft grass rim on each side whose neighbour isn't path (mask bits 1 N, 2 E, 4 S, 8 W)."""
    r = random.Random(seed + mask)
    t = np.full((16, 16), PATH, np.uint8)
    for _ in range(10):
        t[r.randrange(16), r.randrange(16)] = PATHL
    for _ in range(3):
        t[r.randrange(16), r.randrange(16)] = WOOD
    g = grass(seed * 3 + mask)
    wob = [r.choice((1, 2, 2, 3)) for _ in range(16)]
    for y in range(16):
        for x in range(16):
            d = []
            if not mask & 1: d.append(y - wob[x])
            if not mask & 4: d.append(15 - y - wob[(x + 5) % 16])
            if not mask & 8: d.append(x - wob[(y + 3) % 16])
            if not mask & 2: d.append(15 - x - wob[(y + 9) % 16])
            if d and min(d) < 0:
                t[y, x] = g[y, x]
            elif d and min(d) == 0:
                t[y, x] = MID  # the grass lip
    return t


def water(mask: int, frame: int = 0) -> np.ndarray:
    """Pond water; a sandy bank (and grass beyond) on each side whose neighbour isn't water."""
    r = random.Random(11)
    t = np.full((16, 16), WAT, np.uint8)
    for y in range(16):  # gentle wave lines
        for x in range(16):
            if (x + 2 * y + frame * 2) % 16 in (0, 1) and y % 4 == 1:
                t[y, x] = WATL
            elif (x + 2 * y + 5 + frame * 2) % 16 == 0 and y % 4 == 3:
                t[y, x] = WATD
    g = grass(41 + mask)
    for y in range(16):
        for x in range(16):
            d = []
            if not mask & 1: d.append(y)
            if not mask & 4: d.append(15 - y)
            if not mask & 8: d.append(x)
            if not mask & 2: d.append(15 - x)
            if not d:
                continue
            k = min(d) - (r.random() < 0.3)
            if k < 1:
                t[y, x] = g[y, x]
            elif k < 3:
                t[y, x] = PATHL if k == 1 else PATH  # sand
            elif k == 3:
                t[y, x] = WATL  # foam
    return t


def flowers(seed: int, petal: int = None) -> np.ndarray:
    """Two flowers on grass: a plus of petals around a yellow middle, with leaves."""
    petal = PINK if petal is None else petal
    t = grass(seed)
    r = random.Random(seed)
    shape = ["..P..", ".PPP.", "PPYPP", ".PPP.", "..P.."]
    for cx, cy in ((4 + r.randrange(0, 2), 4 + r.randrange(0, 2)), (11 + r.randrange(-1, 1), 11 + r.randrange(-1, 1))):
        t[cy + 3, cx - 2] = MID
        t[cy + 3, cx + 2] = MID
        t[cy + 2, cx - 3] = DARK
        t[cy + 2, cx + 3] = DARK
        for j, row in enumerate(shape):
            for i, ch in enumerate(row):
                if ch != ".":
                    yy, xx = cy - 2 + j, cx - 2 + i
                    if 0 <= yy < 16 and 0 <= xx < 16:
                        t[yy, xx] = YEL if ch == "Y" else petal
        t[cy - 1, cx - 1] = WHITE if petal == PINK else WATL  # a glint
    return t


def fence() -> np.ndarray:
    t = grass(23)
    for y in (5, 10):  # two rails
        t[y - 1, :] = OUT
        t[y, :] = WHITE
        t[y + 1, :] = GREY
    for px in (2, 12):  # posts
        t[2:14, px - 1] = OUT
        t[2:14, px + 2] = OUT
        t[2:13, px:px + 2] = WHITE
        t[2:13, px + 1] = GREY
        t[2, px - 1:px + 3] = OUT
        t[13, px - 1:px + 3] = OUT
        t[14, px:px + 2] = MID
    return t


def sign() -> np.ndarray:
    t = grass(29)
    t[9:15, 7:9] = WOOD  # post
    t[9:15, 6] = OUT
    t[9:15, 9] = OUT
    t[15, 6:10] = MID
    t[2:10, 2:14] = WOOD  # board
    t[2, 2:14] = OUT
    t[9, 2:14] = OUT
    t[2:10, 1] = OUT
    t[2:10, 14] = OUT
    t[3, 3:13] = PATHL
    for y in (5, 7):  # writing
        t[y, 4:12:2] = PATHL
    return t


def tree() -> np.ndarray:
    """A round 2x2 tree on grass."""
    t = np.zeros((32, 32), np.uint8)
    g = np.block([[grass(51), grass(52)], [grass(53), grass(54)]])
    t[:] = g
    yy, xx = np.mgrid[0:32, 0:32]
    cx, cy = 15.5, 13.0
    d = np.hypot((xx - cx) / 15.0, (yy - cy) / 13.5)
    bumps = 0.06 * np.sin(np.arctan2(yy - cy, xx - cx) * 7)
    inside = d < 1.0 + bumps
    t[inside] = MID
    t[inside & (yy > cy + 3) & (d > 0.55)] = DARK  # shade on the lower half
    hi = np.hypot((xx - 11) / 6.5, (yy - 8) / 5.0) < 1.0
    t[inside & hi] = LIGHT
    t[inside & (np.hypot((xx - 10) / 3.0, (yy - 7) / 2.2) < 1.0)] = HI
    for (bx, by) in ((20, 10), (7, 15), (17, 18)):  # leaf clumps
        t[inside & (np.hypot(xx - bx, yy - by) < 2.2)] = LIGHT
    edge = inside & ~np.roll(inside, 1, 0) | inside & ~np.roll(inside, -1, 0) | inside & ~np.roll(inside, 1, 1) | \
        inside & ~np.roll(inside, -1, 1)
    t[edge] = OUT
    t[27:31, 13:19] = WOOD  # trunk
    t[27:31, 12] = OUT
    t[27:31, 19] = OUT
    t[31, 13:19] = OUT
    t[28:31, 17] = DARK
    return t


# ---------------------------------------------------------------- buildings
def house() -> np.ndarray:
    """5x5 blocks; the door is block (1, 4). Palette A. 0 = transparent (the grass shows)."""
    t = np.zeros((80, 80), np.uint8)
    # walls
    t[34:79, 4:76] = WHITE
    for y in range(38, 78, 5):  # siding
        t[y, 5:75] = GREY
    t[34:79, 4] = OUT
    t[34:79, 75] = OUT
    t[78, 4:76] = OUT
    t[74:78, 5:75] = GREY  # foundation
    t[74, 5:75] = OUT
    # roof: overhanging, with shingle rows
    for y in range(4, 38):
        inset = max(0, (14 - y)) // 2
        x0, x1 = 1 + inset, 79 - inset
        t[y, x0:x1] = ROOF
        if (y - 4) % 6 == 5:
            t[y, x0:x1] = ROOFD
        t[y, x0] = OUT
        t[y, x1 - 1] = OUT
    for y in range(4, 11):  # ridge light
        t[y, 18 + (10 - y):62 - (10 - y)] = ROOFL
    t[3, 12:68] = OUT
    for y in range(4, 10):
        t[y, 12 - (y - 3)] = OUT
        t[y, 67 + (y - 3)] = OUT
    t[36, 1:79] = OUT  # eave
    t[37, 3:77] = ROOFD
    # chimney
    t[0:14, 56:64] = GREY
    t[0:14, 56] = OUT
    t[0:14, 63] = OUT
    t[0, 56:64] = OUT
    t[1:3, 57:63] = WHITE
    # windows
    for wx in (38, 56):
        t[46:60, wx:wx + 14] = OUT
        t[47:59, wx + 1:wx + 13] = WIN
        t[47:50, wx + 1:wx + 13] = WHITE
        t[52, wx + 1:wx + 13] = OUT
        t[47:59, wx + 7] = OUT
        t[53:55, wx + 2:wx + 4] = WHITE
        t[60, wx - 1:wx + 15] = GREY
    # door at block (1, 4): x 16-31, y 64-79, with a little awning in the block above
    t[59:61, 15:33] = ROOFD
    t[58, 15:33] = OUT
    t[61:78, 18:30] = OUT
    t[62:78, 19:29] = WOOD
    t[62:78, 24] = OUT
    t[69:71, 26:28] = YEL
    t[62, 19:29] = PATHL
    t[78, 17:31] = PATH  # doorstep
    t[79, 17:31] = OUT
    # flower box
    t[60:63, 38:52] = WOOD
    t[59, 39:51:3] = PINK if False else ROOFL
    return t


def lab() -> np.ndarray:
    """7x5 blocks; the door is block (3, 4). Rows 0-3 palette C, row 4 palette B (B indices there)."""
    t = np.zeros((80, 112), np.uint8)
    c = {"out": 1, "roofd": 2, "roof": 3, "roofl": 4, "shade": 5, "wall": 6, "walll": 7, "brick": 8,
         "wind": 9, "win": 10, "winl": 11, "metal": 12}
    t[30:64, 3:109] = c["wall"]
    t[30:64, 3] = c["out"]
    t[30:64, 108] = c["out"]
    for y in range(34, 64, 6):
        t[y, 4:108] = c["shade"]
    # roof: flat with a raised rim
    t[6:30, 1:111] = c["roof"]
    for y in range(8, 30, 5):
        t[y, 2:110] = c["roofd"]
    t[6:9, 1:111] = c["roofl"]
    t[5, 1:111] = c["out"]
    t[6:30, 0] = c["out"]
    t[6:30, 111] = c["out"]
    t[29, 0:112] = c["out"]
    # roof lights and an antenna
    for wx in (14, 40, 66):
        t[12:20, wx:wx + 18] = c["out"]
        t[13:19, wx + 1:wx + 17] = c["winl"]
        t[13:15, wx + 1:wx + 17] = c["walll"]
    t[0:6, 92:94] = c["metal"]
    t[0, 88:98] = c["metal"]
    t[1, 89:97] = c["out"]
    # upper windows (row 2-3)
    for wx in (8, 26, 70, 88):
        t[38:56, wx:wx + 14] = c["out"]
        t[39:55, wx + 1:wx + 13] = c["win"]
        t[39:43, wx + 1:wx + 13] = c["winl"]
        t[49:55, wx + 1:wx + 13] = c["wind"]
        t[39:55, wx + 7] = c["out"]
    # sign plate over the door
    t[44:58, 42:70] = c["out"]
    t[45:57, 43:69] = c["walll"]
    for y in (48, 51, 54):
        t[y, 46:66:2] = c["wind"]
    # bottom row (y 64-79): palette B indices
    t[64:80, 3:109] = WHITE
    t[64:80, 3] = OUT
    t[64:80, 108] = OUT
    t[64, 3:109] = GREY
    t[74:80, 4:108] = GREY
    t[74, 4:108] = OUT
    t[79, 3:109] = OUT
    for wx in (10, 28, 72, 90):  # low windows
        t[66:73, wx:wx + 12] = OUT
        t[67:72, wx + 1:wx + 11] = WAT
        t[67:69, wx + 1:wx + 11] = WATL
    # door at block (3, 4): x 48-63
    t[64:80, 49:63] = OUT
    t[65:79, 50:62] = WATD
    t[65:79, 55:57] = OUT
    t[66:70, 51:54] = WATL
    t[66:70, 58:61] = WATL
    t[79, 48:64] = PATH
    return t


def main() -> None:
    sheets = HERE / "sheets"
    sheets.mkdir(exist_ok=True)
    cells = {}  # name -> 16x16 index array (ground sheet, palette B view: shared colours + B extras)
    cells["grass"] = grass(1)
    cells["grass2"] = grass(2)
    cells["grass3"] = grass(3)
    for m in range(16):
        cells[f"path#{m}"] = path(m)
        cells[f"water#{m}"] = water(m)
    cells["flowers"] = flowers(5)
    cells["flowers2"] = flowers(6, WHITE)
    cells["fence"] = fence()
    cells["sign"] = sign()
    order = list(cells)
    cols = 16
    rows = -(-len(order) // cols) + 2
    ground = np.zeros((rows * 16, cols * 16), np.uint8)
    pos = {}
    for i, n in enumerate(order):
        x, y = (i % cols) * 16, (i // cols) * 16
        ground[y:y + 16, x:x + 16] = cells[n]
        pos[n] = (x, y)
    ty = (-(-len(order) // cols)) * 16
    ground[ty:ty + 32, 0:32] = tree()
    pos["tree"] = (0, ty)
    rgba(ground, B).save(sheets / "ground.png")  # B: shared colours, and the water/flower colours
    h = house()
    rgba(h, A).save(sheets / "house.png")
    lb = lab()
    top = rgba(lb[:64], C)
    bottom = rgba(lb[64:], B)
    im = Image.new("RGBA", (112, 80))
    im.paste(top, (0, 0))
    im.paste(bottom, (0, 64))
    im.save(sheets / "lab.png")
    # palettes as JASC files
    for name, pal in (("a", A), ("b", B), ("c", C)):
        with open(HERE / f"palette_{name}.pal", "w") as f:
            f.write("JASC-PAL\r\n0100\r\n16\r\n" + "".join(f"{r} {g} {b}\r\n" for r, g, b in pal))
    mt = []
    for n in order:
        x, y = pos[n]
        e = {"name": n, "tileset": "primary", "image": "sheets/ground.png", "x": x, "y": y}
        if n.startswith("water"):
            e.update(behavior="MB_POND_WATER", elevation=1)
        if n in ("fence", "sign"):
            e["solid"] = True
        mt.append(e)
    mt.append({"name": "tree", "tileset": "primary", "image": "sheets/ground.png", "x": pos["tree"][0],
               "y": pos["tree"][1], "w": 2, "h": 2, "solid": True})
    mt.append({"name": "house", "tileset": "secondary", "image": "sheets/house.png", "w": 5, "h": 5, "ground": "grass",
               "solid": True, "open": ["1,4"], "behaviors": {"1,4": "MB_ANIMATED_DOOR"}, "banks": [0]})
    mt.append({"name": "lab", "tileset": "secondary", "image": "sheets/lab.png", "w": 7, "h": 5, "ground": "grass",
               "solid": True, "open": ["3,4"], "behaviors": {"3,4": "MB_ANIMATED_DOOR"}, "banks": [7],
               "row_banks": {"4": [1]}})
    spec = {"version": "hns", "primary": "gTileset_PalletScratch_General", "secondary": "gTileset_PalletScratch",
            "palettes": {"primary": ["palette_a.pal", "palette_b.pal"], "secondary": ["palette_c.pal"]},
            "reserve": {"primary": [[434, 441]]}, "metatiles": mt}
    (HERE / "spec.json").write_text(json.dumps(spec, indent=1) + "\n")
    grid = """\
TTTTTTTTTTTT==TTTTTTTTTT
TTTTTTTTTTTT==TTTTTTTTTT
TT..........==........TT
TT...HHHHH..==RRRRR...TT
TT...HHHHH..==RRRRR...TT
TT...HHHHH..==RRRRR...TT
TT...HHHHH..==RRRRR...TT
TT..SHHHHH..=SRRRRR...TT
TT....==========......TT
TT.........==LLLLLLL..TT
TT.........==LLLLLLL..TT
TT...ffffS.==LLLLLLL..TT
TT...fffff.==LLLLLLL..TT
TT...fffff.==LLLLLLL..TT
TT...S.....======.....TT
TT.....wwww...........TT
TT.....wwww..FFFSFFF..TT
TT.....wwww...........TT
TTTTTT.wwww.TTTTTTTTTTTT
TTTTTT.wwww.TTTTTTTTTTTT
"""
    (HERE / "grid.txt").write_text(grid)
    (HERE / "border.txt").write_text("TT\nTT\n")
    legend = {"T": "tree", ".": {"pick": ["grass", "grass", "grass2", "grass3"]}, "=": {"auto": "path"},
              "w": {"auto": "water", "elevation": 1}, "f": {"pick": ["flowers", "flowers2"]}, "F": "fence",
              "S": "sign", "H": "house", "R": "house", "L": "lab"}
    (HERE / "legend.json").write_text(json.dumps(legend, indent=1) + "\n")
    print(f"{len(mt)} metatiles; sheets in {sheets}")


if __name__ == "__main__":
    main()
