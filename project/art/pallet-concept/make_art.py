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
import props

HERE = Path(__file__).resolve().parent
MAP_W, MAP_H = 32, 28
COBBLE_TO_DOOR, COBBLE_TO_DOCK = "\u00e7", "\u00c7"  # (cobble pieces forced: N-S through, and plain)

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
    # the forest closes the sea on the east (the map's border is forest): the sea draws its cliff against it instead
    # of running off the edge into the border's trees. The sea is two blocks wide now, too narrow for its rocks
    # (they stand only in open sea).
    put("T", 30, 2, 2, 24)
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
    for x, y in ((20, 16), (22, 16), (16, 13), (25, 10), (27, 22)):  # (25,10): behind the sea-view bench, not in front
        # (and not on 25,9, where the bench's replay test stands)
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
    put("E", 25, 20)
    put("c", 19, 20)
    put("O", 23, 23, 2, 1)
    # rocks and details
    for x, y in ((12, 24), (27, 6), (13, 25), (27, 25), (2, 10), (27, 19)):
        put("o", x, y)
    for x, y in ((3, 6), (13, 4), (21, 9), (24, 9), (2, 3), (9, 25), (14, 24), (6, 25)):
        put(",", x, y)
    for x, y in ((5, 7), (22, 7)):  # flowers in the yards' corners
        put("*", x, y)
    # the forest along the south edge, either side of the channel: its trees end in their trunks on the grass (pieces
    # of the forest by the sides that are forest, the edge open) where Route 21 North, below, has open grass and its
    # own trees, instead of its canopy running off the edge cut flat
    for x0, ch in ((16, "\u00b9"), (22, "\u00b2"), (24, "\u00b3"), (26, "\u00b3"), (28, "\u00b3"), (30, "\u00bc")):
        put(ch, x0, 26, 2, 2)
    # signs (bg events); the houses' stand in the fence beside the gate, read from the road
    signs = {"PlayersHouseSign": (6, 8), "RivalsHouseSign": (17, 8), "OaksLabSign": (19, 16),
             "TownSign": (13, 11), "TrainerTips": (10, 20)}
    for x, y in signs.values():
        put("S", x, y)
    # the cobbles run on without their grass edge where they meet a door's step (your house, your rival's, the lab)
    # and the dock's planks (the road straight onto the pier)
    for x, y in ((7, 8), (18, 8), (21, 16)):
        put(COBBLE_TO_DOOR, x, y)
    for x, y in ((21, 18), (22, 18)):
        put(COBBLE_TO_DOCK, x, y)
    return g, signs


# the town props (Kanto Town Props v0.1, kit/props.py): (piece, x, y of its top-left block, the ground under it)
PROPS = [("fingerpost", 13, 2, "grass"),  # by the road north to Route 1
         ("bench_wood_east", 26, 9, "grass")]  # looking out to sea
SOLID = set("T#bRoklSBEcwO~sqHJWL\u00b9\u00b2\u00b3\u00bc")  # what a prop can't stand on


def main() -> None:
    g, signs = layout()
    prop_legend, prop_grounds = props.place(g, PROPS, SOLID)
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
    dockside = sheet("dockside", "wood", cols=4)  # the dock's crate, barrels and boat over the ground they stand on
    dockside.add("crate@dock#6", kit.crate(), tileset="secondary", ground="dock#6", solid=True)
    dockside.add("barrel@dock#14", kit.barrel(), tileset="secondary", ground="dock#14", solid=True)
    dockside.add("barrel@dock#12", kit.barrel(), tileset="secondary", ground="dock#12", solid=True)
    dockside.add("boat_moored", kit.boat(), tileset="secondary", ground="pond#15", solid=True, elevation=1)
    spec_mt += dockside.write()
    prop_entries, prop_anims = props.pieces(HERE, HERE, prop_grounds)
    spec_mt += prop_entries
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
            "animations": base["animations"] + prop_anims,
            "metatiles": spec_mt}
    (HERE / "spec.json").write_text(json.dumps(spec, indent=1) + "\n")
    (HERE / "grid.txt").write_text("".join("".join(r) + "\n" for r in g))
    (HERE / "border.txt").write_text("TT\nTT\n")
    legend = dict(kit.LEGEND, H="house_red", J="house_blue", W="windmill", L="lab")
    # the dirt runs straight on into the cobbles (the road north, the road to the well, the track past the lab) with
    # no strip of grass between them; the well stands in its yard's dirt
    legend[":"] = {"auto": "dirt", "joins": "="}
    legend["w"] = {"name": "well", "joins": "="}
    # on the dock: the crate and the barrels stand on the planks they replace (the dock's corner and edge pieces),
    # and the boat in open water beside the pier; the dock and the pond run on round them
    legend["c"] = {"name": "crate@dock#6", "joins": "d"}
    legend["B"] = {"name": "barrel@dock#14", "joins": "d"}
    legend["E"] = {"name": "barrel@dock#12", "joins": "d"}
    legend["O"] = {"name": "boat_moored", "joins": "~", "elevation": 1}
    for ch, mask in (("\u00b9", 8), ("\u00b2", 2), ("\u00b3", 10), ("\u00bc", 11)):  # the south forest's edge
        legend[ch] = {"name": f"forest#{mask}", "joins": "T"}
    legend[COBBLE_TO_DOOR] = {"name": "cobble#5", "joins": "="}
    legend[COBBLE_TO_DOCK] = {"name": "cobble#15", "joins": "="}
    legend.update(prop_legend)
    (HERE / "legend.json").write_text(json.dumps(legend, indent=1) + "\n")
    (HERE / "signs.json").write_text(json.dumps(signs, indent=1) + "\n")
    print(f"{len(spec_mt)} metatiles in the spec; grid {MAP_W}x{MAP_H}")


if __name__ == "__main__":
    main()
