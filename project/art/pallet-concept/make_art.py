#!/usr/bin/env python3
"""Pallet Town after the concept art (concept.png, made with image generation): every tile drawn from scratch,
nothing taken from an existing tileset. The pieces every map shares come from the kit (../kit/kit.py); this file
draws the town's own ground and lays it out.

The town is 32x28 blocks: a forest around it, two houses with fenced yards (buildings/), cobblestone roads, a windmill
in a flower garden, Oak's lab with its greenhouse, a pond with a wooden dock (and the way south to Route 21), the sea
below a cliff in the east, and a stone well.

Its palettes (banks 0-3 and 8 are the kit's):
  bank 7  Oak's lab (Kanto Buildings Remakes v0.3, ../packs/buildings_v0.3): metal roof, siding, glass, the greenhouse
  bank 9  the houses: one palette for both (buildings/, Pallet Houses Pack v0.5, a native pixel pack)
  bank 10 the windmill (the same remakes pack), in Viridian's houses' palette

Run from the repository root:  python3 project/art/pallet-concept/make_art.py
It writes sheets/*.png, the palettes, spec.json, grid.txt, border.txt, legend.json and events.json next to itself;
build.sh turns them into the game's tilesets and map with pae.
"""
import json
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "kit"))
import buildings
import kit

HERE = Path(__file__).resolve().parent
MAP_W, MAP_H = 32, 28

# ---------------------------------------------------------------- palettes and buildings (the kit has the rest)
BANK = {"lab": 7, "plants": 8, "houses": 9, "windmill": 10}
# the two houses, from a native pixel pack: one palette for both (the town has one palette slot for them)
HOUSES = {roof: buildings.load(HERE / "buildings" / f"{roof}_house") for roof in ("red", "blue")}
assert HOUSES["red"].palette == HOUSES["blue"].palette, "the two houses must share one palette"
# Oak's lab and the windmill, from the remakes pack (buildings.REMAKES): the lab in its own palette, the windmill in
# Viridian's houses' (Route 1's shelter and arch have it too, so the join to Route 1 shows them in it)
LAB = buildings.load(buildings.REMAKES / "pokemon_lab")
WINDMILL = buildings.load(buildings.REMAKES / "pallet_windmill")
PALS = {"lab": LAB.palette, "houses": HOUSES["red"].palette, "windmill": WINDMILL.palette}


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
    # forest: top, bottom, west; trees down the east side of the yards
    put("T", 0, 0, MAP_W, 2)
    put("T", 0, 26, MAP_W, 2)
    put("T", 0, 0, 2, MAP_H)
    put("T", 24, 2, 2, 6)
    # the sea under the cliff
    put("s", 28, 2, 4, 24)
    for x, y, rock in ((30, 5, "q"), (29, 13, "Q"), (31, 21, "q")):  # rocks standing in it
        put(rock, x, y)
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
    kit.check_water(g)
    base = kit.primary(HERE)  # the kit: the primary tileset every map shares
    spec_mt = list(base["metatiles"])

    def sheet(name, pal, cols=16):
        return kit.Sheet(name, PALS.get(pal) or kit.PALS[pal], BANK.get(pal, kit.BANK.get(pal)), HERE, HERE, cols)
    homes = sheet("houses", "houses", cols=10)
    for roof, b in HOUSES.items():  # your house and your rival's (buildings/): solid but the door, which animates
        homes.add(f"house_{roof}", b.idx, tileset="secondary", **b.entry())
    spec_mt += homes.write()
    big = sheet("buildings", "windmill", cols=5)
    big.add("windmill", WINDMILL.idx, tileset="secondary", ground="grass", solid=True)
    spec_mt += big.write()
    labs = sheet("lab", "lab", cols=9)
    labs.add("lab", LAB.idx, tileset="secondary", **LAB.entry())
    spec_mt += labs.write()
    for e in spec_mt:  # sheets put "w"/"h" on everything; drop the 1x1 ones for readability
        if e["w"] == 1 and e["h"] == 1:
            del e["w"], e["h"]
    for name, pal in PALS.items():
        kit.write_palette(HERE / f"palette_{name}.pal", pal)
    spec = {"version": "hns", "primary": kit.PRIMARY, "secondary": "gTileset_PalletConcept",
            "palettes": {"primary": base["palettes"],
                         "secondary": ["palette_lab.pal", base["secondary_palettes"][8], "palette_houses.pal",
                                       "palette_windmill.pal"]},
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
