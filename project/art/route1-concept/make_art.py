#!/usr/bin/env python3
"""Route 1 after the concept art (concept.png, made with image generation): the country road north out of Pallet
Town toward Viridian City, built from the kit (project/art/kit) and a few pieces of its own.

The route is 50x40 blocks, as before, so its joins stay where they were: Viridian's road meets the top at columns
22-25, Pallet's road the bottom at columns 24-25. Between pine forest walls: a dirt road through three ledges (with
stone steps where the road goes down them), tall grass on both sides, a rest shelter by a pond with lily pads and
reeds, a stream crossed by a little bridge on a side path, and a wooden arch where the road leaves Pallet.

Its own tileset has the shelter (in its own palette, bank 7) and the arch (in the kit's wood palette, bank 2, so
Pallet can show it across the join); bank 8 is the kit's plants palette.

Run from the repository root:  python3 project/art/route1-concept/make_art.py
It writes sheets/, the palette, spec.json, grid.txt, border.txt and legend.json next to itself; build.sh turns them
into the game's tileset and map with pae.
"""
import json
import sys
from pathlib import Path

import numpy as np

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "kit"))
import kit

HERE = Path(__file__).resolve().parent
MAP_W, MAP_H = 50, 40
SECONDARY = "gTileset_Route1Concept"

# ---------------------------------------------------------------- palette (bank 7)
PR = [(0, 0, 0), (32, 24, 24), (72, 44, 28), (112, 70, 40), (156, 104, 60), (200, 148, 92), (236, 196, 140),
      (56, 88, 56), (88, 128, 72), (136, 168, 96), (96, 96, 104), (150, 150, 150), (200, 200, 192),
      (240, 232, 208), (176, 56, 48), (232, 200, 96)]
R_OUT, W0, W1, W2, W3, W4, M0, M1, M2, S0, S1, S2, CRM, RED, BRASS = range(1, 16)
BANK = {"route": 7}
PALS = {"route": PR}


def _post(t, x0, x1, y0, y1):
    t[y0:y1, x0:x1] = W2
    t[y0:y1, x0 + 1] = W3
    t[y0:y1, x1 - 2] = W1
    t[y0:y1, x0] = R_OUT
    t[y0:y1, x1 - 1] = R_OUT
    for y in range(y0 + 3, y1, 5):  # grain
        t[y, x0 + 2:x1 - 2] = W1


def shelter() -> np.ndarray:
    """A wooden rest shelter, 3x3 blocks: a shingle roof with moss on it over two posts and a bench."""
    t = np.zeros((48, 48), np.uint8)
    # the shadow under the roof and the back wall of planks
    t[22:38, 4:44] = W1
    for y in range(22, 38, 4):
        t[y, 4:44] = W0
    t[22:30, 4:44][t[22:30, 4:44] == W1] = W0  # deeper shade right under the roof
    # posts
    _post(t, 3, 9, 18, 45)
    _post(t, 39, 45, 18, 45)
    # the bench: a backrest and a seat on short legs
    t[28:31, 10:38] = W3
    t[28, 10:38] = W4
    t[30, 10:38] = W1
    t[34:37, 9:39] = W3
    t[34, 9:39] = W4
    t[36, 9:39] = W1
    t[37, 9:39] = R_OUT
    for lx in (11, 36):
        t[37:42, lx:lx + 2] = W1
        t[37:42, lx - 1] = R_OUT
        t[37:42, lx + 2] = R_OUT
    t[27, 10:38] = R_OUT
    t[31, 10:38] = R_OUT
    t[33, 9:39] = R_OUT
    # the ground under it: a stone floor
    t[42:46, 2:46] = S1
    t[42, 2:46] = S2
    for x in range(2, 46, 6):
        t[42:46, x] = S0
    t[46, 2:46] = R_OUT
    # roof: shingles in rows, the ridge at the top, overhanging the posts; moss on its left
    for y in range(2, 22):
        inset = max(0, 8 - y)
        x0, x1 = inset, 48 - inset
        row = (y - 2) // 4
        for x in range(x0, x1):
            k = (x + (2 if row % 2 else 0)) % 5
            ty = (y - 2) % 4
            c = W2
            if ty == 3 or k == 0:
                c = W1
            elif ty == 0:
                c = W3
            if (x * 3 + y * 7) % 23 < 4 and x < 30:
                c = M1 if ty else M2  # moss
            if x > 38 and c == W3:
                c = W2
            t[y, x] = c
        t[y, x0] = R_OUT
        t[y, x1 - 1] = R_OUT
    t[1, 7:41] = R_OUT
    t[2:4, 7:41] = W4  # the ridge board
    t[4, 6:42] = W1
    t[21, 0:48] = R_OUT
    t[20, 1:47] = W1
    return t


def arch() -> np.ndarray:
    """A wooden arch over the road, 4x2 blocks: two posts and a beam under a little red roof, lanterns hanging from
    it. The road goes under it (columns 1-2); its top row is drawn over the player. In the kit's wood palette
    (bank 2), which Pallet has too: Pallet's road north looks at it across the join without a palette of its own."""
    from kit import CRM as K_CRM, D_OUT, RFD, RFH, RFL, RFM, STG, STL, WOD, WOH, WOL, WOM
    t = np.zeros((32, 64), np.uint8)

    def post(x0, x1, y0, y1):
        t[y0:y1, x0:x1] = WOM
        t[y0:y1, x0 + 1] = WOL
        t[y0:y1, x1 - 2] = WOD
        t[y0:y1, x0] = D_OUT
        t[y0:y1, x1 - 1] = D_OUT
        for y in range(y0 + 3, y1, 5):  # grain
            t[y, x0 + 2:x1 - 2] = WOD
    post(4, 12, 8, 31)
    post(52, 60, 8, 31)
    for px in (4, 52):  # stone footings
        t[27:31, px - 1:px + 9] = STG
        t[27, px - 1:px + 9] = STL
        t[31, px - 1:px + 9] = D_OUT
    # the beam
    t[7:13, 0:64] = WOM
    t[7, 0:64] = WOH
    t[8, 0:64] = WOL
    t[12, 0:64] = WOD
    t[13, 0:64] = D_OUT
    t[6, 0:64] = D_OUT
    for x in (0, 63):
        t[6:14, x] = D_OUT
    for x in range(6, 64, 10):  # pegs
        t[9:11, x] = WOD
        t[9, x] = WOH
    # a little red roof over it, in rows of shingles
    for y in range(0, 6):
        x0, x1 = 6 - y, 58 + y
        t[y, x0:x1] = RFM if y % 2 else RFL
        for x in range(x0 + (y % 2) * 2, x1, 4):
            t[y, x] = RFD
        t[y, x0] = D_OUT
        t[y, x1 - 1] = D_OUT
    t[0, 6:58] = D_OUT
    t[1, 8:56] = RFH
    # a lantern hanging from each side of the beam
    for lx in (14, 47):
        t[14:16, lx + 1] = D_OUT
        t[16:21, lx:lx + 3] = WOH
        t[17:20, lx + 1] = K_CRM
        t[16, lx:lx + 3] = D_OUT
        t[21, lx:lx + 3] = D_OUT
    return t


# ---------------------------------------------------------------- layout
def layout() -> tuple[list[list[str]], dict]:
    g = [["T" for _ in range(MAP_W)] for _ in range(MAP_H)]

    def put(ch, x0, y0, w=1, h=1):
        for y in range(y0, y0 + h):
            for x in range(x0, x0 + w):
                g[y][x] = ch

    put(".", 10, 4, 30, 32)  # the route between its forest walls (columns 0-9 and 40-49)
    # the road: wide where it meets Viridian's, then two blocks down through the ledges to Pallet's
    put(":", 22, 0, 4, 6)
    put(":", 23, 6, 3, 2)
    put(":", 24, 8, 2, 32)
    # bends and passing places in the road
    put(":", 23, 13, 1, 3)
    put(":", 26, 21, 1, 3)
    put(":", 23, 30, 1, 2)
    # fences along the top
    put("#", 10, 4, 11, 1)
    put("#", 29, 4, 11, 1)
    # the three ledges (steps where the road goes down them)
    put("_", 10, 9, 30, 1)
    put("_", 20, 17, 20, 1)
    put("_", 10, 26, 30, 1)
    for y in (9, 17, 26):
        put("h", 24, y, 2, 1)
    # tall grass (never right under a ledge: you land on lawn)
    put("g", 11, 5, 9, 3)
    put("g", 29, 5, 10, 3)
    put("g", 27, 11, 12, 5)
    put("g", 27, 19, 12, 7)
    put("g", 28, 28, 11, 5)
    put("g", 16, 28, 6, 3)
    # the rest stop: the shelter by a pond with lily pads and reeds
    put("P", 13, 10, 3, 3)
    put("~", 11, 13, 9, 3)
    put("~", 12, 16, 6, 1)
    put("v", 13, 14)
    put("v", 17, 14)
    put("v", 15, 15)
    put("r", 12, 15)  # reeds (and lily pads) only grow in open water: a cell with water on all four sides
    put("r", 18, 14)
    # the stream from the pond west, then south, and the side path over it on a little bridge
    put("~", 10, 16, 2, 1)
    put("~", 10, 17, 2, 18)
    put(":", 12, 31, 12, 2)
    put("d", 10, 31, 2, 2)
    put(".", 4, 28, 6, 8)  # a clearing in the forest across the bridge
    put(":", 6, 31, 4, 2)
    # trees, bushes, rocks, stumps and flowers
    put("R", 20, 19, 2, 2)
    put("R", 14, 21, 2, 2)
    put("R", 20, 6, 2, 2)
    put("R", 27, 6, 2, 2)
    for x, y in ((21, 10), (17, 12), (12, 18), (19, 23), (37, 34), (13, 34), (30, 16), (39, 27)):
        put("b", x, y)
    for x, y in ((18, 11), (22, 24), (38, 16), (16, 25), (27, 34)):
        put("o", x, y)
    for x, y in ((38, 10), (12, 24), (35, 27), (20, 34)):
        put("k", x, y)
    for x, y in ((16, 11), (19, 11), (20, 12), (16, 19), (17, 19), (21, 22), (22, 33), (26, 33), (26, 32),
                 (13, 25), (36, 33), (14, 28)):
        put("*", x, y)
    for x, y in ((11, 11), (21, 14), (22, 15), (18, 21), (21, 29), (30, 34), (33, 34), (5, 29), (8, 34)):
        put(",", x, y)
    for x, y in ((4, 33), (5, 34), (8, 29)):
        put("*", x, y)
    # where the road leaves Pallet: a fence with an arch over the road
    put("#", 10, 35, 13, 1)
    put("#", 27, 35, 13, 1)
    put("A", 23, 34, 4, 2)
    signs = {"RouteSign": (23, 33)}
    for x, y in signs.values():
        put("S", x, y)
    return g, signs


# ---------------------------------------------------------------- sheets and spec
def main() -> None:
    g, signs = layout()
    kit.check_forest(g)
    base = kit.primary(HERE)  # the kit: the primary tileset every map shares
    spec_mt = list(base["metatiles"])
    own = kit.Sheet("route", PR, BANK["route"], HERE, HERE, cols=3)
    own.add("shelter", shelter(), tileset="secondary", ground="grass", solid=True)
    spec_mt += own.write()
    wood = kit.Sheet("route_wood", kit.P2, kit.BANK["wood"], HERE, HERE, cols=4)
    wood.add("arch", arch(), tileset="secondary", ground="dirt#15", solid=True, open=["1,0", "2,0", "1,1", "2,1"],
             over_rows=1)
    spec_mt += wood.write()
    for e in spec_mt:  # sheets put "w"/"h" on everything; drop the 1x1 ones for readability
        if e["w"] == 1 and e["h"] == 1:
            del e["w"], e["h"]
    for name, pal in PALS.items():
        kit.write_palette(HERE / f"palette_{name}.pal", pal)
    spec = {"version": "hns", "primary": kit.PRIMARY, "secondary": SECONDARY,
            "palettes": {"primary": base["palettes"],
                         "secondary": ["palette_route.pal", base["secondary_palettes"][8]]},
            "reserve": {"primary": base["reserve"]},
            "animations": base["animations"],
            "field_effects": base["field_effects"],
            "metatiles": spec_mt}
    (HERE / "spec.json").write_text(json.dumps(spec, indent=1) + "\n")
    (HERE / "grid.txt").write_text("".join("".join(r) + "\n" for r in g))
    (HERE / "border.txt").write_text("TT\nTT\n")
    legend = dict(kit.LEGEND, P="shelter", A="arch")
    (HERE / "legend.json").write_text(json.dumps(legend, indent=1) + "\n")
    (HERE / "signs.json").write_text(json.dumps(signs, indent=1) + "\n")
    print(f"{len(spec_mt)} metatiles in the spec; grid {MAP_W}x{MAP_H}")


if __name__ == "__main__":
    main()
