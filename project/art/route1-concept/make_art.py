#!/usr/bin/env python3
"""Route 1 after the concept art (concept.png, made with image generation): the country road north out of Pallet
Town toward Viridian City, built from the kit (project/art/kit) and a few pieces of its own.

The route is 50x40 blocks, as before, so its joins stay where they were: Viridian's road meets the top at columns
22-25, Pallet's road the bottom at columns 24-25. Between forest walls: a dirt road through three ledges (with
stone steps where the road goes down them), tall grass on both sides, a rest shelter by a pond with lily pads and
reeds, a stream crossed by a little bridge on a side path, and a wooden arch where the road leaves Pallet.

Its own tileset has the shelter and the arch (Kanto Buildings Remakes v0.3, ../packs/buildings_v0.3), in Viridian's
houses' palette (bank 7); bank 8 is the kit's plants palette.

Run from the repository root:  python3 project/art/route1-concept/make_art.py
It writes sheets/, the palette, spec.json, grid.txt, border.txt and legend.json next to itself; build.sh turns them
into the game's tileset and map with pae.
"""
import json
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "kit"))
import buildings
import fields
import kit

HERE = Path(__file__).resolve().parent
LEDGE_INTO_FOREST = "\u0142"  # (a ledge block beside the forest: its middle piece)
MAP_W, MAP_H = 50, 40
SECONDARY = "gTileset_Route1Concept"

# ---------------------------------------------------------------- the shelter and the arch (bank 7)
# from the remakes pack (buildings.REMAKES), in Viridian's houses' palette; Pallet has it too (its windmill's, bank
# 10), so Pallet's road north shows the arch across the join in its own colours
SHELTER = buildings.load(buildings.REMAKES / "route1_rest_shelter")
ARCH = buildings.load(buildings.REMAKES / "route1_arch")
assert SHELTER.palette == ARCH.palette, "the shelter and the arch share bank 7"
BANK = {"route": 7}
PALS = {"route": SHELTER.palette}


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
    for y in (9, 17, 26):  # (the road's own steps: on its dirt, which runs up to them)
        put("y", 24, y)
        put("z", 25, y)
    # tall grass (never right under a ledge: you land on lawn)
    # (rows 0-6 are what Viridian shows across the join: no tall grass there, its palette has no slot in Viridian)
    put("g", 11, 7, 9, 2)
    put("g", 29, 7, 10, 2)
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
    put("~", 10, 33, 3, 3)  # it ends in a little pool under the forest, reeds in its middle
    put("r", 11, 34)
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
    for x, y in ((11, 11), (21, 14), (22, 15), (18, 21), (22, 29), (30, 34), (33, 34), (5, 29), (8, 34)):
        put(",", x, y)
    for x, y in ((4, 33), (5, 34), (8, 29)):
        put("*", x, y)
    for x, y in ((33, 5), (34, 5), (34, 6)):  # flowers on the plain verge under the north fence, east of the road
        put("*", x, y)
    for x, y in ((14, 5), (17, 6)):  # and a few in the lawn west of it
        put(",", x, y)
    # where the road leaves Pallet: a fence with an arch over the road
    put("#", 13, 35, 10, 1)
    put("#", 27, 35, 13, 1)
    put("A", 23, 34, 4, 2)
    # the ledges run on into the forest walls (their middle piece, not a rounded end with lawn before the trees)
    for x, y in ((10, 9), (39, 9), (39, 17), (39, 26)):
        assert g[y][x] == "_" and "T" in (g[y][x - 1], g[y][x + 1])
        put(LEDGE_INTO_FOREST, x, y)
    signs = {"RouteSign": (23, 33)}
    for x, y in signs.values():
        put("S", x, y)
    return g, signs


# ---------------------------------------------------------------- sheets and spec
def main() -> None:
    g, signs = layout()
    kit.check_forest(g)
    kit.check_water(g)
    base = kit.primary(HERE)  # the kit: the primary tileset every map shares
    spec_mt = list(base["metatiles"])
    own = kit.Sheet("route", PALS["route"], BANK["route"], HERE, HERE, cols=4)
    own.add("shelter", SHELTER.idx, tileset="secondary", ground="grass", solid=True)
    # the road goes under the arch (its middle two columns); its top row is drawn over the player
    # (on the lawn, the road's two blocks under its middle with their edges, so only the road shows under it)
    own.add("arch", ARCH.idx, tileset="secondary", ground=["grass", "dirt#7", "dirt#13", "grass"] * 2, solid=True,
            open=["1,0", "2,0", "1,1", "2,1"], over_rows=1)
    spec_mt += own.write()
    # the road's steps through the ledges, on its dirt (the kit's are on the lawn)
    steps = kit.Sheet("steps_dirt", kit.P0, 0, HERE, HERE, cols=2)
    steps.add("steps_dirt_W", fields.steps(2), tileset="secondary", ground="dirt#7")
    steps.add("steps_dirt_E", fields.steps(8), tileset="secondary", ground="dirt#13")
    spec_mt += steps.write()
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
    # (the dirt first: the ground kit/settle.py gives a piece standing by the road is the road's group's first)
    legend = {":": None, **dict(kit.LEGEND, P="shelter")}
    # the road runs on through the arch, over its steps and onto the bridge's planks without its edge, and on from
    # Viridian's cobbles (no lawn rim across the road where they meet)
    legend.update({"=": {"auto": "cobble", "joins": ":"}, "A": {"name": "arch", "joins": ":"},
                   "y": {"name": "steps_dirt_W", "joins": ":"}, "z": {"name": "steps_dirt_E", "joins": ":"},
                   "d": {"auto": "dock", "joins": ":"},
                   LEDGE_INTO_FOREST: {"name": "ledge#10", "joins": "_"}})
    (HERE / "legend.json").write_text(json.dumps(legend, indent=1) + "\n")
    (HERE / "signs.json").write_text(json.dumps(signs, indent=1) + "\n")
    print(f"{len(spec_mt)} metatiles in the spec; grid {MAP_W}x{MAP_H}")


if __name__ == "__main__":
    main()
