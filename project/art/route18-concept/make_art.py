#!/usr/bin/env python3
"""Route 18 after its concept (draw_plan.py and plan_stage1.txt): the end of Cycling Road, the shore road to the
gatehouse and Fuchsia (see draw_plan.py). It is 60x20 blocks, as before; its joins: Route 17's road (its columns
14-22) at the top edge, columns 8-16 (offset -6, as before), and Fuchsia's west road (its rows 18-20) at the right
edge, rows 8-10 (offset -10, as before).

The pieces: the kit's, and Route 16's Cycling Road gatehouse (route16-concept/route16_buildings.py) in Saffron's
buildings' palette (bank 7 here). Bank 8 is the kit's plants palette; 9-12 stay free for the seam to old Fuchsia, whose
strip in this route (the right seven columns) is forest, lawn, road and hedges only.

Run from the repository root:  python3 project/art/route18-concept/make_art.py
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
SECONDARY = "gTileset_Route18Concept"
MAP_W, MAP_H = 60, 20
GATE_BANK = 7
NORTH = [(x, 0) for x in range(8, 17)]
EAST = [(MAP_W - 1, y) for y in range(8, 11)]
SOLID = set("T#bRoklSBcw_~vrsqQC")
IN_EAST, IN_WEST = "MB_EAST_ARROW_WARP", "MB_WEST_ARROW_WARP"
# the gatehouse: its letter in the plan, its pack, its bank, its doorways (the left one entered walking east)
BUILDINGS = {"C": (route16_buildings.OUT / "cycling_gate", GATE_BANK, [IN_EAST, IN_WEST])}
HALL = ((41, 9), (48, 9))   # the gatehouse's hall: doorway to doorway
# the rockers (local ids 1-3), where they stand, which ways they look and how far; the Pokémon about (4-7)
ROCKERS = [(38, 13, "W", 4), (31, 14, "NESW", 1), (23, 12, "E", 6)]
MONS = [(31, 6), (33, 7), (36, 7), (39, 6)]   # a Kecleon, two Dodrio, a Kecleon
STRIP = 7                   # the columns of this route old Fuchsia draws


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
    assert len(g) == MAP_H and all(len(r) == MAP_W for r in g), "the plan is 60x20"
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
    """The route's rules: only Route 17's road and Fuchsia's open onto the edges; with the hall walked through,
    everything walkable is reached, and without it Fuchsia's side doesn't reach Cycling Road's: the gatehouse is the
    only way (its bike rule); the rockers wait in the grass and none of them sees the road; the Pokémon stand on
    open ground; both doorways can be walked into and every sign read; the strip old Fuchsia draws is forest, lawn,
    road and hedges only."""
    edge = {(x, y) for y in range(MAP_H) for x in range(MAP_W) if x in (0, MAP_W - 1) or y in (0, MAP_H - 1)}
    assert {xy for xy in edge if g[xy[1]][xy[0]] not in SOLID} == set(NORTH + EAST), "only the two roads open"
    walk = {(x, y) for y in range(MAP_H) for x in range(MAP_W) if g[y][x] not in SOLID}
    every = reachable(g, NORTH)
    assert walk <= every and set(EAST) <= every, f"blocks you can't reach: {sorted(walk - every)[:8]}"
    assert not reachable(g, EAST, hall=False) & set(NORTH), "the gatehouse must be the only way"
    road = {(x, y) for x, y in walk if g[y][x] == "="}
    for x, y, dirs, n in ROCKERS:
        assert g[y][x] == "g", f"the rocker at ({x},{y}) waits in the grass"
        seen = sight(g, x, y, dirs, n)
        assert not seen & road, f"the rocker at ({x},{y}) sees the road at {sorted(seen & road)[:3]}"
    assert all((x, y) in walk for x, y in MONS), "the Pokémon stand on open ground"
    (wx, wy), (ex, ey) = d
    assert (wx - 1, wy) in walk and (ex + 1, ey) in walk, "the doorways can't be walked into"
    for y in range(MAP_H):
        for x in range(MAP_W):
            if g[y][x] == "S":
                assert (x, y + 1) in walk, f"the sign at ({x},{y}) can't be read"
    strip = {g[y][x] for y in range(MAP_H) for x in range(MAP_W - STRIP, MAP_W)}
    assert strip <= set("T.=b"), f"old Fuchsia's strip: {strip}"


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
