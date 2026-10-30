#!/usr/bin/env python3
"""Indigo Plateau after its concept (draw_plan.py and plan_stage1.txt): the Pokémon League's mountaintop (see
draw_plan.py). It is 24x20 blocks, as before; Route 23's road leaves the bottom edge (columns 10-13, offset 0) and
League West Pass's road meets the left edge (rows 9-11, offset 0).

The pieces: the kit's; the Pokémon League (Kanto Buildings Remakes v0.3, ../packs/buildings_v0.3) in its own palette
(bank 7).
Bank 8 is the kit's plants palette; 9-12 stay free for the seam to old League West Pass.

Run from the repository root:  python3 project/art/indigo-concept/make_art.py
It writes sheets/, the palettes, spec.json, grid.txt, border.txt, legend.json and doors.json next to
itself; build.sh turns them into the game's tileset and map with pae.
"""
import json
import sys
from collections import deque
from pathlib import Path

import numpy as np
from PIL import Image

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "kit"))
import buildings
import kit
import props

HERE = Path(__file__).resolve().parent
SECONDARY = "gTileset_IndigoConcept"
MAP_W, MAP_H = 24, 20
LEAGUE_BANK = 7
SOLID = set("T#bRoklSBcw_~vrsqQL")
# the town props (Kanto Town Props v0.1, kit/props.py): (piece, x, y of its top-left block, the ground under it):
# statues either side of the League's forecourt, flower tubs beside its door
PROPS = [("statue_guardian", 8, 14, "paving#15"), ("statue_guardian", 14, 14, "paving#15"),
         ("flower_tub", 8, 12, "paving#15"), ("flower_tub", 15, 12, "paving#15")]
WEST = [(0, y) for y in range(9, 12)]
SOUTH = [(x, MAP_H - 1) for x in range(10, 14)]
WORKERS = [(2, 9), (2, 10), (2, 11)]  # across the west road until the game is won
CREDITS = (11, 12)                     # where the credits' rival and Oak stand, before the door


def league() -> buildings.Building:
    folder = buildings.REMAKES / "pokemon_league"
    meta = json.loads((folder / "pokemon_league.json").read_text())
    with Image.open(folder / "pokemon_league.png") as im:
        idx, flat = np.array(im, np.uint8), im.getpalette()[:48]
    d = meta["door_blocks"][0] if "door_blocks" in meta else meta["door_block"]
    return buildings.Building("pokemon_league", idx, [tuple(flat[i:i + 3]) for i in range(0, 48, 3)], tuple(d),
                              folder / "pokemon_league_door.png")


def plan() -> list[list[str]]:
    rows = (HERE / "plan_stage1.txt").read_text().split("\n")[:MAP_H]
    g = [list(r) for r in rows]
    assert len(g) == MAP_H and all(len(r) == MAP_W for r in g), "the plan is 24x20"
    return g


def door(g, b) -> tuple[int, int]:
    bw, bh = b.idx.shape[1] // 16, b.idx.shape[0] // 16
    cells = {(x, y) for y, r in enumerate(g) for x, c in enumerate(r) if c == "L"}
    x0, y0 = min(cells)
    assert cells == {(x0 + i, y0 + j) for i in range(bw) for j in range(bh)}, "L isn't the League's footprint"
    return x0 + b.door[0], y0 + b.door[1]


def reachable(g, starts, blocked=frozenset()) -> set[tuple[int, int]]:
    seen, todo = set(starts), deque(starts)
    while todo:
        x, y = todo.popleft()
        for n in ((x + 1, y), (x - 1, y), (x, y + 1), (x, y - 1)):
            if not (0 <= n[0] < MAP_W and 0 <= n[1] < MAP_H) or n in seen or n in blocked:
                continue
            if g[n[1]][n[0]] in SOLID:
                continue
            seen.add(n)
            todo.append(n)
    return seen


def check(g, d) -> None:
    """The mountaintop's rules: only Route 23's road and League West Pass's open onto the edges; everything walkable
    is reached from Route 23's road; the League's door can be walked into, and the credits' spot before it is open;
    the workers stand across the west road, so with them there League West Pass isn't reached (until the game is
    won), without them it is."""
    walk = {(x, y) for y in range(MAP_H) for x in range(MAP_W) if g[y][x] not in SOLID}
    edge = {(x, y) for x, y in walk if x in (0, MAP_W - 1) or y in (0, MAP_H - 1)}
    assert edge == set(WEST + SOUTH), f"only the two roads open: {sorted(edge ^ set(WEST + SOUTH))}"
    every = reachable(g, SOUTH)
    assert walk <= every, f"blocks you can't reach: {sorted(walk - every)[:8]}"
    x, y = d
    assert (x, y + 1) in every and CREDITS in every, "the League's door and the credits' spot"
    assert set(WORKERS) <= walk and not set(WEST) & reachable(g, SOUTH, set(WORKERS)), "the workers close the road"


def main() -> None:
    b = league()
    g = plan()
    prop_legend, prop_grounds = props.place(g, PROPS, SOLID, joins="p")
    d = door(g, b)
    kit.check_forest(g)
    kit.check_water(g)
    kit.check_paving(g, "".join(prop_legend))
    check(g, d)
    base = kit.primary(HERE)  # the kit: the primary tileset every map shares
    spec_mt = list(base["metatiles"])
    sh = kit.Sheet(b.name, b.palette, LEAGUE_BANK, HERE, HERE, cols=b.idx.shape[1] // 16)
    sh.add(b.name, b.idx, tileset="secondary", ground="grass", solid=True, open=[f"{b.door[0]},{b.door[1]}"],
           behaviors={f"{b.door[0]},{b.door[1]}": "MB_ANIMATED_DOOR"})
    spec_mt += sh.write()
    prop_entries, prop_anims = props.pieces(HERE, HERE, prop_grounds)
    spec_mt += prop_entries
    for e in spec_mt:  # sheets put "w"/"h" on everything; drop the 1x1 ones for readability
        if e["w"] == 1 and e["h"] == 1:
            del e["w"], e["h"]
    kit.write_palette(HERE / f"palette_{LEAGUE_BANK}.pal", b.palette)
    spec = {"version": "hns", "primary": kit.PRIMARY, "secondary": SECONDARY,
            "palettes": {"primary": base["palettes"],
                         "secondary": [f"palette_{LEAGUE_BANK}.pal", base["secondary_palettes"][8]]},
            "reserve": {"primary": base["reserve"]},
            "animations": base["animations"] + prop_anims,
            "field_effects": base["field_effects"],
            "metatiles": spec_mt}
    (HERE / "spec.json").write_text(json.dumps(spec, indent=1) + "\n")
    (HERE / "grid.txt").write_text("".join("".join(r) + "\n" for r in g))
    (HERE / "border.txt").write_text("TT\nTT\n")
    (HERE / "legend.json").write_text(json.dumps(dict(kit.LEGEND, L=b.name, **prop_legend), indent=1) + "\n")
    (HERE / "doors.json").write_text(json.dumps({"L": [d]}, indent=1) + "\n")
    print(f"{len(spec_mt)} metatiles in the spec; grid {MAP_W}x{MAP_H}; door {d}")


if __name__ == "__main__":
    main()
