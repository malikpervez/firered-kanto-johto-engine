#!/usr/bin/env python3
"""Route 15 after its concept (draw_plan.py and plan_stage1.txt): the way east out of Fuchsia, two roads through the
woods to Route 14 (see draw_plan.py). It is 80x24 blocks (old Route 15 was 96x32); its joins: Fuchsia's main street
(its rows 20-23) at the left edge, rows 4-7 (offset -16, was -15: the road moved a row up), and Route 14's road (its
rows 51-54) at the right edge, rows 14-17 (offset -37, as before).

The pieces: the kit's, and Route 16's Cycling Road gatehouse (route16-concept/route16_buildings.py) in Saffron's
buildings' palette (bank 7 here). Bank 8 is the kit's plants palette; 9-12 stay free for the seam to old Route 14,
whose strip in this route (the right seven columns) is forest, lawn and dirt only.

Run from the repository root:  python3 project/art/route15-concept/make_art.py
It writes sheets/, the palette, spec.json, grid.txt, border.txt, legend.json and doors.json next to itself; build.sh
turns them into the game's tileset and map with pae.
"""
import json
import sys
from collections import deque
from pathlib import Path

import numpy as np
from PIL import Image

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "kit"))
sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "route16-concept"))
import buildings
import kit
import route16_buildings

HERE = Path(__file__).resolve().parent
SECONDARY = "gTileset_Route15Concept"
MAP_W, MAP_H = 80, 24
GATE_BANK = 7
WEST = [(0, y) for y in range(4, 8)]
EAST = [(MAP_W - 1, y) for y in range(14, 18)]
SOLID = set("T#bRoklSBcw_~vrsqQC")  # (ledges, "_", count as walls: they only drop you south)
IN_EAST, IN_WEST = "MB_EAST_ARROW_WARP", "MB_WEST_ARROW_WARP"
# the gatehouse: its letter in the plan, its pack, its bank, its doorways (the left one entered walking east)
BUILDINGS = {"C": (route16_buildings.OUT / "cycling_gate", GATE_BANK, [IN_EAST, IN_WEST])}
HALL = ((9, 5), (16, 5))    # the gatehouse's hall: doorway to doorway
# the trainers (local ids 1-10, 12-13), where they stand, which ways they look and how far (the walkers look a
# block ahead, whichever way they face)
ROUND = ("NESW", 1)
TRAINERS = [(24, 10, ROUND), (34, 15, ("W", 5)), (42, 16, ("N", 2)), (41, 10, ROUND), (30, 4, ("S", 2)),
            (54, 4, ("SE", 2)), (60, 15, ("NS", 1)), (40, 2, ROUND), (64, 4, ("S", 2)), (55, 2, ROUND),
            (47, 10, ("S", 1)), (48, 10, ("S", 1))]
ITEM = (76, 5)              # the TM, at the lookout
MONS = [(58, 13), (26, 2), (37, 3), (50, 2), (62, 13), (28, 18), (48, 18), (65, 19), (17, 3), (44, 13)]
STRIP = 7                   # the columns of this route old Route 14 draws


def load(letter: str) -> tuple[buildings.Building, list[tuple[int, int]]]:
    folder = BUILDINGS[letter][0]
    meta = json.loads((folder / f"{folder.name}.json").read_text())
    with Image.open(folder / f"{folder.name}.png") as im:
        idx, flat = np.array(im, np.uint8), im.getpalette()[:48]
    ds = [tuple(d) for d in meta["door_blocks"]]
    return buildings.Building(folder.name, idx, [tuple(flat[i:i + 3]) for i in range(0, 48, 3)], ds[0],
                              folder / f"{folder.name}_door.png"), ds


def plan() -> list[list[str]]:
    rows = (HERE / "plan_stage1.txt").read_text().split("\n")[:MAP_H]
    g = [list(r) for r in rows]
    assert len(g) == MAP_H and all(len(r) == MAP_W for r in g), "the plan is 80x24"
    return g


def doors(g) -> list[tuple[int, int]]:
    b, ds = load("C")
    bw, bh = b.idx.shape[1] // 16, b.idx.shape[0] // 16
    cells = {(x, y) for y, r in enumerate(g) for x, c in enumerate(r) if c == "C"}
    x0, y0 = min(cells)
    assert cells == {(x0 + i, y0 + j) for i in range(bw) for j in range(bh)}, "C isn't the gatehouse's footprint"
    out = [(x0 + dx, y0 + dy) for dx, dy in ds]
    assert out == list(HALL), f"the gatehouse's doorways are at {out}"
    return out


def reachable(g, starts, hall=True) -> set[tuple[int, int]]:
    """Blocks you can walk to from ``starts``; the doorways are open ground, joined through the hall."""
    hop = {HALL[0]: [HALL[1]], HALL[1]: [HALL[0]]} if hall else {}
    seen, todo = set(starts), deque(starts)
    while todo:
        x, y = todo.popleft()
        for n in [(x + 1, y), (x - 1, y), (x, y + 1), (x, y - 1)] + hop.get((x, y), []):
            if not (0 <= n[0] < MAP_W and 0 <= n[1] < MAP_H) or n in seen:
                continue
            if g[n[1]][n[0]] in SOLID and n not in HALL:
                continue
            seen.add(n)
            todo.append(n)
    return seen


def sight(g, x, y, dirs, n) -> set[tuple[int, int]]:
    out = set()
    for d in dirs:
        dx, dy = {"N": (0, -1), "E": (1, 0), "S": (0, 1), "W": (-1, 0)}[d]
        for k in range(1, n + 1):
            c = (x + dx * k, y + dy * k)
            if g[c[1]][c[0]] in SOLID:
                break
            out.add(c)
    return out


def check(g, d) -> None:
    """The route's rules: only Fuchsia's road and Route 14's open onto the edges; with the hall walked through,
    everything walkable is reached from Fuchsia's side, and without it Route 14's side doesn't reach Fuchsia's: the
    gatehouse is the only way; the high road's ledges are one way, so the high road is reached from the low road
    without them (by the slope at its east end); every trainer and Pokémon stands on open ground, the TM can be
    picked up, both doorways can be walked into and the sign read; the strip old Route 14 draws is forest, lawn and
    dirt only."""
    edge = {(x, y) for y in range(MAP_H) for x in range(MAP_W) if x in (0, MAP_W - 1) or y in (0, MAP_H - 1)}
    assert {xy for xy in edge if g[xy[1]][xy[0]] not in SOLID} == set(WEST + EAST), "only the two roads open"
    walk = {(x, y) for y in range(MAP_H) for x in range(MAP_W) if g[y][x] not in SOLID}
    every = reachable(g, WEST)
    assert walk <= every and set(EAST) <= every, f"blocks you can't reach: {sorted(walk - every)[:8]}"
    assert not reachable(g, EAST, hall=False) & set(WEST), "the gatehouse must be the only way"
    assert (40, 5) in reachable(g, EAST, hall=False), "the high road is reached from the low road"
    for x, y, look in TRAINERS:
        assert (x, y) in walk, f"the trainer at ({x},{y}) stands on open ground"
        sight(g, x, y, *look)
    assert all((x, y) in walk for x, y in MONS + [ITEM]), "the Pokémon and the TM stand on open ground"
    (wx, wy), (ex, ey) = d
    assert (wx - 1, wy) in walk and (ex + 1, ey) in walk, "the doorways can't be walked into"
    for y in range(MAP_H):
        for x in range(MAP_W):
            if g[y][x] == "S":
                assert (x, y + 1) in walk, f"the sign at ({x},{y}) can't be read"
    strip = {g[y][x] for y in range(MAP_H) for x in range(MAP_W - STRIP, MAP_W)}
    assert strip <= set("T.:R"), f"old Route 14's strip: {strip}"


def main() -> None:
    route16_buildings.gate()
    g = plan()
    d = doors(g)
    kit.check_forest(g)
    kit.check_water(g)
    kit.check_paving(g)
    check(g, d)
    base = kit.primary(HERE)  # the kit: the primary tileset every map shares
    spec_mt = list(base["metatiles"])
    b, ds = load("C")
    open_ = [f"{dx},{dy}" for dx, dy in ds]
    behavior = {f"{dx},{dy}": mb for (dx, dy), mb in zip(ds, BUILDINGS["C"][2])}
    sh = kit.Sheet(b.name, b.palette, GATE_BANK, HERE, HERE, cols=b.idx.shape[1] // 16)
    sh.add(b.name, b.idx, tileset="secondary", ground="grass", solid=True, open=open_, behaviors=behavior)
    spec_mt += sh.write()
    for e in spec_mt:  # sheets put "w"/"h" on everything; drop the 1x1 ones for readability
        if e["w"] == 1 and e["h"] == 1:
            del e["w"], e["h"]
    kit.write_palette(HERE / f"palette_{GATE_BANK}.pal", b.palette)
    spec = {"version": "hns", "primary": kit.PRIMARY, "secondary": SECONDARY,
            "palettes": {"primary": base["palettes"],
                         "secondary": [f"palette_{GATE_BANK}.pal", base["secondary_palettes"][8]]},
            "reserve": {"primary": base["reserve"]},
            "animations": base["animations"],
            "field_effects": base["field_effects"],
            "metatiles": spec_mt}
    (HERE / "spec.json").write_text(json.dumps(spec, indent=1) + "\n")
    (HERE / "grid.txt").write_text("".join("".join(r) + "\n" for r in g))
    (HERE / "border.txt").write_text("ss\nss\n")
    legend = dict(kit.LEGEND, C=b.name)
    (HERE / "legend.json").write_text(json.dumps(legend, indent=1) + "\n")
    (HERE / "doors.json").write_text(json.dumps({"C": d}, indent=1) + "\n")
    print(f"{len(spec_mt)} metatiles in the spec; grid {MAP_W}x{MAP_H}; doorways {d}")


if __name__ == "__main__":
    main()
