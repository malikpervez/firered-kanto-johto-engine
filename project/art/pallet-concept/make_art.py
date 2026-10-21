#!/usr/bin/env python3
"""Pallet Town after the concept art (concept.png, made with image generation): every tile drawn from scratch,
nothing taken from an existing tileset. The pieces every map shares come from the kit (../kit/kit.py); this file
draws the town's own.

The town is 32x28 blocks: a pine forest around it, two houses with fenced yards (houses.py), cobblestone roads, a windmill
in a flower garden, Oak's lab with its greenhouse, a pond with a wooden dock (and the way south to Route 21), the sea
below a cliff in the east, and a stone well.

Its palettes (banks 0-3 and 8 are the kit's):
  bank 2  wood (the kit's): the windmill
  bank 7  the lab: metal roof, siding, glass, the greenhouse plants
  bank 9  the houses: plaster, clay roof tiles in red and blue, glass (drawn in houses.py)

Run from the repository root:  python3 project/art/pallet-concept/make_art.py
It writes sheets/*.png, the palettes, spec.json, grid.txt, border.txt, legend.json and events.json next to itself;
build.sh turns them into the game's tilesets and map with pae.
"""
import json
import math
import random
import sys
from pathlib import Path

import numpy as np

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "kit"))
import houses
import kit
from kit import CRM, D_OUT, NWL, NWM, RFD, RFH, RFL, RFM, STG, STL, WOD, WOM, edge_of, ellipse

HERE = Path(__file__).resolve().parent
MAP_W, MAP_H = 32, 28

# ---------------------------------------------------------------- palettes (the town's own; the kit has the rest)
P3 = [(0, 0, 0), (24, 32, 40), (64, 80, 96), (96, 112, 128), (144, 160, 168), (192, 200, 208), (152, 144, 120),
      (200, 192, 168), (232, 228, 208), (40, 64, 80), (120, 176, 184), (200, 236, 236), (40, 96, 56),
      (88, 152, 72), (72, 120, 88), (248, 248, 240)]
L_OUT, MTD, MTM, MTL, MTH, SID, SIM, SIL, LWD, GLA, GLH, PLD, PLM, DRG, LWH = range(1, 16)

BANK = {"lab": 7, "plants": 8, "houses": 9}
PALS = {"lab": P3, "houses": houses.PH}


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
    put("J", 17, 3, 5, 5)
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
    for x, y in ((5, 7), (22, 7)):  # flowers in the yards' corners
        put("*", x, y)
    # signs (bg events); the houses' stand in the fence beside the gate, read from the road
    signs = {"PlayersHouseSign": (6, 8), "RivalsHouseSign": (17, 8), "OaksLabSign": (19, 16),
             "TownSign": (13, 11), "TrainerTips": (10, 20)}
    for x, y in signs.values():
        put("S", x, y)
    return g, signs


def main() -> None:
    g, signs = layout()
    kit.check_forest(g)
    kit.check_pond(g)
    base = kit.primary(HERE)  # the kit: the primary tileset every map shares
    spec_mt = list(base["metatiles"])

    def sheet(name, pal, cols=16):
        return kit.Sheet(name, PALS.get(pal) or kit.PALS[pal], BANK.get(pal, kit.BANK.get(pal)), HERE, HERE, cols)
    homes = sheet("houses", "houses", cols=10)
    for roof in ("red", "blue"):  # your house and your rival's (houses.py)
        homes.add(f"house_{roof}", houses.house(roof), tileset="secondary", ground="grass", solid=True, open=["1,4"],
                  behaviors={"1,4": "MB_ANIMATED_DOOR"})
    spec_mt += homes.write()
    big = sheet("buildings", "wood", cols=5)
    big.add("windmill", windmill(), tileset="secondary", ground="grass", solid=True)
    spec_mt += big.write()
    labs = sheet("lab", "lab", cols=9)
    labs.add("lab", lab(), tileset="secondary", ground="grass", solid=True, open=["3,4"],
             behaviors={"3,4": "MB_ANIMATED_DOOR"})
    spec_mt += labs.write()
    for e in spec_mt:  # sheets put "w"/"h" on everything; drop the 1x1 ones for readability
        if e["w"] == 1 and e["h"] == 1:
            del e["w"], e["h"]
    for name, pal in PALS.items():
        kit.write_palette(HERE / f"palette_{name}.pal", pal)
    spec = {"version": "hns", "primary": kit.PRIMARY, "secondary": "gTileset_PalletConcept",
            "palettes": {"primary": base["palettes"],
                         "secondary": ["palette_lab.pal", base["secondary_palettes"][8], "palette_houses.pal"]},
            "reserve": {"primary": base["reserve"]},
            "animations": base["animations"],
            "metatiles": spec_mt}
    (HERE / "spec.json").write_text(json.dumps(spec, indent=1) + "\n")
    (HERE / "grid.txt").write_text("".join("".join(r) + "\n" for r in g))
    (HERE / "border.txt").write_text("TT\nTT\n")
    legend = dict(kit.LEGEND, H="house_red", J="house_blue", W="windmill", L="lab")
    (HERE / "legend.json").write_text(json.dumps(legend, indent=1) + "\n")
    (HERE / "signs.json").write_text(json.dumps(signs, indent=1) + "\n")
    print(f"{len(spec_mt)} metatiles in the spec; grid {MAP_W}x{MAP_H}")


if __name__ == "__main__":
    main()
