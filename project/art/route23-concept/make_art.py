#!/usr/bin/env python3
"""Route 23 after its concept (draw_plan.py and plan_stage1.txt): the road to the Pokémon League, from the League gate
through the badge gates to Victory Road and up to Indigo Plateau (see draw_plan.py). It is 24x160 blocks, as before;
Indigo Plateau's road meets the top edge (columns 10-13, offset 0) and Route 22's woods are below the bottom edge.

The pieces: the kit's, its cliffs for Victory Road's cliff and Route 2's cave mouth for its two mouths, in the cliffs'
palette (bank 7), as Routes 10 and 20 have them; Route 12's north gatehouse for the League gate's back (its doorway
only: the double door below it is the map's bottom edge, shut), in Saffron's buildings palette (bank 9).

Run from the repository root:  python3 project/art/route23-concept/make_art.py
It writes sheets/, the palettes, spec.json, grid.txt, border.txt, legend.json and doors.json next to itself; build.sh
turns them into the game's tileset and map with pae.
"""
import json
import sys
from collections import deque
from pathlib import Path

import numpy as np
from PIL import Image

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "kit"))
import buildings
import cliffs
import kit

HERE = Path(__file__).resolve().parent
ART = HERE.parent
SECONDARY = "gTileset_Route23Concept"
MAP_W, MAP_H = 24, 160
CLIFF_BANK, GATE_BANK = 7, 9
WATER = "~"
SOLID = set("T#bRoklSBcw_~vrsqQYH") | cliffs.SOLID
TOP = [(x, 0) for x in range(10, 14)]           # Indigo Plateau's road
GATE_FOLDER = buildings.REMAKES / "route12_gate"  # the League gate's back: Route 12's north gatehouse
# the badge gates, south first: (west column, top row) of each pass; the guard in its east column on the pass's third
# row, the triggers across the three blocks beside him on that row and the next
GATES = [(8, 138), (8, 120), (8, 102), (8, 84), (8, 56), (8, 46), (4, 36)]
BADGES = ["Cascade", "Thunder", "Rainbow", "Soul", "Marsh", "Volcano", "Earth"]
HIDDEN = [(20, 128), (2, 110), (21, 92), (2, 63), (21, 64), (2, 53), (21, 43), (3, 5)]
LAKE_SOUTH, LAKE_NORTH = (11, 81), (11, 63)     # the lake's shores


def guard(i):
    x0, y0 = GATES[i]
    return x0 + 3, y0 + 2


def triggers(i):
    x0, y0 = GATES[i]
    return [(x0 + k, y0 + 2 + r) for r in (0, 1) for k in range(3)]


def _pack(folder: Path) -> tuple[buildings.Building, list[tuple[int, int]]]:
    meta = json.loads((folder / f"{folder.name}.json").read_text())
    with Image.open(folder / f"{folder.name}.png") as im:
        idx, flat = np.array(im, np.uint8), im.getpalette()[:48]
    ds = [tuple(d) for d in meta["door_blocks"]]
    return buildings.Building(folder.name, idx, [tuple(flat[i:i + 3]) for i in range(0, 48, 3)], ds[0],
                              folder / f"{folder.name}_door.png"), ds


MOUTH = _pack(ART / "route2-concept/buildings/diglett_cave")[0]
GATE, GATE_DOORS = _pack(GATE_FOLDER)
DOORWAY = [d for d in GATE_DOORS if d[1] == 0]   # the gatehouse's back doorway, entered walking south


def plan() -> list[list[str]]:
    rows = (HERE / "plan_stage1.txt").read_text().split("\n")[:MAP_H]
    g = [list(r) for r in rows]
    assert len(g) == MAP_H and all(len(r) == MAP_W for r in g), "the plan is 24x160"
    return g


def doors(g) -> dict:
    bw, bh = MOUTH.idx.shape[1] // 16, MOUTH.idx.shape[0] // 16
    cells = {(x, y) for y, r in enumerate(g) for x, c in enumerate(r) if c == "Y"}
    mouths = []
    while cells:
        x0, y0 = min(cells, key=lambda c: (c[1], c[0]))
        foot = {(x0 + i, y0 + j) for i in range(bw) for j in range(bh)}
        assert foot <= cells, f"Y at ({x0},{y0}) isn't its footprint"
        cells -= foot
        mouths.append((x0 + MOUTH.door[0], y0 + MOUTH.door[1]))
    n = {(x, y) for y, r in enumerate(g) for x, c in enumerate(r) if c == "H"}
    x0, y0 = min(n)
    assert n == {(x0 + i, y0 + j) for i in range(4) for j in range(4)}, "H isn't the gatehouse's footprint"
    return {"Y": sorted(mouths), "H": [(x0 + dx, y0 + dy) for dx, dy in DOORWAY]}


def reachable(g, starts, blocked=frozenset(), surf=False) -> set[tuple[int, int]]:
    seen, todo = set(starts), deque(starts)
    while todo:
        x, y = todo.popleft()
        for n in ((x + 1, y), (x - 1, y), (x, y + 1), (x, y - 1)):
            if not (0 <= n[0] < MAP_W and 0 <= n[1] < MAP_H) or n in seen or n in blocked:
                continue
            c = g[n[1]][n[0]]
            if c in SOLID and not (surf and c == WATER):
                continue
            seen.add(n)
            todo.append(n)
    return seen


def check(g, d) -> None:
    """The route's rules: only Indigo Plateau's road opens onto an edge; out of the League gate's doorway, by Surf
    (the lake), the gates and Victory Road's way in are reached, and its way out isn't: its yard, the lane and the cliff
    top's meadow are reached from Indigo Plateau's road and from the way out only; the lake can't be crossed on foot;
    each gate closes the road: with its guard and its first row of triggers in the way, nothing north of it is
    reached; the guard stands in the pass's east column, the triggers are open ground; the sign can be read, the hidden
    items are on open ground."""
    walk = {(x, y) for y in range(MAP_H) for x in range(MAP_W) if g[y][x] not in SOLID}
    edge = {(x, y) for x, y in walk if x in (0, MAP_W - 1) or y in (0, MAP_H - 1)}
    assert edge == set(TOP), f"only Indigo Plateau's road opens: {sorted(edge - set(TOP))[:6]}"
    (inx, iny), (outx, outy) = d["Y"]
    gate_out = [(x, y - 1) for x, y in d["H"]]
    south = reachable(g, gate_out, surf=True)
    north = reachable(g, TOP)
    assert (inx, iny + 1) in south and (outx, outy + 1) not in south, "Victory Road's way in from the gates, not out"
    assert (outx, outy + 1) in north and not north & south, "the way out leads up to Indigo Plateau only"
    assert walk <= south | north, f"blocks you can't reach: {sorted(walk - south - north)[:8]}"
    assert LAKE_NORTH not in reachable(g, gate_out), "the lake is crossed by Surf"
    for i, badge in enumerate(BADGES):
        gx, gy = guard(i)
        x0, y0 = GATES[i]
        assert (gx, gy) in walk and set(triggers(i)) <= walk, f"the {badge} gate's guard and triggers on open ground"
        first_row = {(x0 + k, gy) for k in range(3)}
        beyond = (x0, y0 - 1)  # the block north of the pass
        assert beyond in walk and beyond not in reachable(g, gate_out, first_row | {(gx, gy)}, surf=True), \
            f"the {badge} gate doesn't close the road"
        assert all((x, gy + 2) in walk for x, _ in triggers(i)[:3]), f"the {badge} gate: room to be sent back"
    for y in range(MAP_H):
        for x in range(MAP_W):
            if g[y][x] == "S":
                assert (x, y + 1) in walk, f"the sign at ({x},{y}) can't be read"
    assert all(xy in walk for xy in HIDDEN), "the hidden items on open ground"
    assert any("g" in r for r in g), "tall grass (the route has land encounters)"


def main() -> None:
    g = plan()
    d = doors(g)
    cliffs.layout(g, roof="Y")  # the mouths stand against the cliff: its top runs down to them, with no face
    kit.check_forest(g)
    kit.check_water(g)
    check(g, d)
    assert MOUTH.palette == cliffs.PAL, "the cave mouth isn't in the cliffs' palette"
    base = kit.primary(HERE)  # the kit: the primary tileset every map shares
    spec_mt = list(base["metatiles"])
    rock = kit.Sheet("rock_cliff", cliffs.PAL, CLIFF_BANK, HERE, HERE)
    char_of = cliffs.add(rock, g, roof="Y", extras=())
    spec_mt += rock.write()
    sh = kit.Sheet(MOUTH.name, MOUTH.palette, CLIFF_BANK, HERE, HERE, cols=MOUTH.idx.shape[1] // 16)
    dx, dy = MOUTH.door
    # the mouths' raised tops (their top three rows) are set in the cliff top: the gaps round their rim show the
    # cliff's own top (by the first mouth's phase) rather than grass
    (mx, my) = min(((x, y) for y, r in enumerate(g) for x, c in enumerate(r) if c == "Y"), key=lambda c: (c[1], c[0]))
    idx = MOUTH.idx.copy()
    for by in range(3):
        for bx in range(idx.shape[1] // 16):
            cell = idx[by * 16:(by + 1) * 16, bx * 16:(bx + 1) * 16]
            rock = cliffs.top(1 + (mx + bx) % 3 + 3 * ((my + by) % 3), 0)
            cell[cell == 0] = rock[cell == 0]
    sh.add(MOUTH.name, idx, tileset="secondary", ground="grass", solid=True, open=[f"{dx},{dy}"],
           behaviors={f"{dx},{dy}": "MB_NON_ANIMATED_DOOR"})  # an open mouth: you walk in
    spec_mt += sh.write()
    gs = kit.Sheet(GATE.name, GATE.palette, GATE_BANK, HERE, HERE, cols=GATE.idx.shape[1] // 16)
    gs.add(GATE.name, GATE.idx, tileset="secondary", ground="grass", solid=True,
           open=[f"{x},{y}" for x, y in DOORWAY], behaviors={f"{x},{y}": "MB_SOUTH_ARROW_WARP" for x, y in DOORWAY})
    spec_mt += gs.write()
    for e in spec_mt:  # sheets put "w"/"h" on everything; drop the 1x1 ones for readability
        if e["w"] == 1 and e["h"] == 1:
            del e["w"], e["h"]
    kit.write_palette(HERE / f"palette_{CLIFF_BANK}.pal", cliffs.PAL)
    kit.write_palette(HERE / f"palette_{GATE_BANK}.pal", GATE.palette)
    spec = {"version": "hns", "primary": kit.PRIMARY, "secondary": SECONDARY,
            "palettes": {"primary": base["palettes"],
                         "secondary": [f"palette_{CLIFF_BANK}.pal", base["secondary_palettes"][8],
                                       f"palette_{GATE_BANK}.pal"]},
            "reserve": {"primary": base["reserve"]},
            "animations": base["animations"],
            "field_effects": base["field_effects"],
            "metatiles": spec_mt}
    (HERE / "spec.json").write_text(json.dumps(spec, indent=1) + "\n")
    (HERE / "grid.txt").write_text("".join("".join(r) + "\n" for r in g))
    (HERE / "border.txt").write_text("TT\nTT\n")
    legend = dict(kit.LEGEND, Y={"name": MOUTH.name, "joins": "C"}, H=GATE.name)
    assert not {"Y", "H"} & set(cliffs.legend(char_of)), "a letter of the route's is one of the cliffs'"
    legend.update(cliffs.legend(char_of))
    (HERE / "legend.json").write_text(json.dumps(legend, indent=1) + "\n")
    (HERE / "doors.json").write_text(json.dumps(d, indent=1) + "\n")
    print(f"{len(spec_mt)} metatiles in the spec; grid {MAP_W}x{MAP_H}; doors {d}")


if __name__ == "__main__":
    main()
