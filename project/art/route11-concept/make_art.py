#!/usr/bin/env python3
"""Route 11 after its concept (draw_plan.py and plan_stage1.txt): the road east out of Vermilion to the gatehouse
before Route 12 (see draw_plan.py). It is 60x32 blocks (old Route 11 was 72x40); its joins stay where its
neighbours meet it: Vermilion's main street the left edge at rows 14-17 (offset -3, Vermilion's 11-14), Route 12's
road the right edge at rows 17-19 (offset 27, Route 12's 44-46).

The pieces: the kit's, its cliffs and Route 2's cave mouth for Diglett's Cave, both in the cliffs' palette (bank 7),
and Route 2's south forest gate for the gatehouse in its own palette (bank 9). Bank 8 is the kit's plants palette;
10-12 stay free for the seam to Route 12 (not rebuilt yet).

Run from the repository root:  python3 project/art/route11-concept/make_art.py
It writes sheets/, the palettes, spec.json, grid.txt, border.txt, legend.json and doors.json next to itself;
build.sh turns them into the game's tileset and map with pae.
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
SECONDARY = "gTileset_Route11Concept"
MAP_W, MAP_H = 60, 32
CLIFF_BANK, GATE_BANK = 7, 9
WEST = [(0, y) for y in range(14, 18)]
EAST = [(MAP_W - 1, y) for y in range(17, 20)]
GATE = ART / "route2-concept/buildings/forest_gate_south"
# the trainers the plan is made for (build.sh places them; their sights are the map's): (x, y, the ways they look,
# sight). None of them sees the road
TRAINERS = {"Eddie": (34, 6, "down left", 4), "Hugo": (24, 22, "up down left right", 1),
            "Dillon": (40, 10, "up left", 4), "Dave": (14, 22, "up down left right", 1),
            "Jasper": (28, 24, "up down left right", 1), "Darian": (44, 6, "up down left right", 1),
            "Braxton": (47, 12, "left right", 4), "Yasu": (36, 24, "up down", 1),
            "Dirk": (40, 22, "up down left right", 1), "Bernie": (20, 25, "left right", 6)}
ROAD = {(x, y) for y in range(14, 18) for x in range(0, 48)} | {(x, y) for y in range(17, 20) for x in range(44, 60)}
STEP = {"left": (-1, 0), "right": (1, 0), "up": (0, -1), "down": (0, 1)}
SOLID = set("T#bRoklSBcw_~vrYX") | cliffs.SOLID


def _mouth() -> buildings.Building:
    """Route 2's cave mouth (its pack names its door ``door_blocks``, which the kit's loader doesn't read)."""
    folder = ART / "route2-concept/buildings/diglett_cave"
    meta = json.loads((folder / "diglett_cave.json").read_text())
    with Image.open(folder / "diglett_cave.png") as im:
        idx, flat = np.array(im, np.uint8), im.getpalette()[:48]
    return buildings.Building("diglett_cave", idx, [tuple(flat[i:i + 3]) for i in range(0, 48, 3)],
                              tuple(meta["door_blocks"][0]), folder / "diglett_cave_door.png")


def _gate() -> tuple[buildings.Building, list[tuple[int, int]]]:
    meta = json.loads((GATE / f"{GATE.name}.json").read_text())
    with Image.open(GATE / f"{GATE.name}.png") as im:
        idx, flat = np.array(im, np.uint8), im.getpalette()[:48]
    ds = [tuple(d) for d in meta["door_blocks"]]
    return buildings.Building(GATE.name, idx, [tuple(flat[i:i + 3]) for i in range(0, 48, 3)], ds[0],
                              GATE / f"{GATE.name}_door.png"), ds


MOUTH = _mouth()


def plan() -> list[list[str]]:
    rows = (HERE / "plan_stage1.txt").read_text().split("\n")[:MAP_H]
    g = [list(r) for r in rows]
    assert len(g) == MAP_H and all(len(r) == MAP_W for r in g), "the plan is 60x32"
    return g


def doors(g) -> dict[str, list[tuple[int, int]]]:
    """The cave's door and the gatehouse's two."""
    out = {}
    for letter, (b, ds) in (("Y", (MOUTH, [MOUTH.door])), ("X", _gate())):
        bw, bh = b.idx.shape[1] // 16, b.idx.shape[0] // 16
        cells = {(x, y) for y, r in enumerate(g) for x, c in enumerate(r) if c == letter}
        x0, y0 = min(cells)
        assert cells == {(x0 + i, y0 + j) for i in range(bw) for j in range(bh)}, f"{letter} isn't its footprint"
        out[letter] = [(x0 + dx, y0 + dy) for dx, dy in ds]
    return out


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


def sight(g, x, y, facings, n) -> set[tuple[int, int]]:
    out = set()
    for facing in facings.split():
        dx, dy = STEP[facing]
        for k in range(1, n + 1):
            c = (x + dx * k, y + dy * k)
            if not (0 <= c[0] < MAP_W and 0 <= c[1] < MAP_H) or g[c[1]][c[0]] in SOLID:
                break
            out.add(c)
    return out


def check(g, d) -> None:
    """The route's rules: only its two roads open onto the edges; everything walkable is reached from them; the road
    is in no trainer's sight; the doors can be walked into from below and the sign read."""
    edge = {(x, y) for y in range(MAP_H) for x in range(MAP_W) if x in (0, MAP_W - 1) or y in (0, MAP_H - 1)}
    assert {xy for xy in edge if g[xy[1]][xy[0]] not in SOLID} == set(WEST + EAST), "only the two roads open"
    people = {t[:2] for t in TRAINERS.values()}
    walk = {(x, y) for y in range(MAP_H) for x in range(MAP_W) if g[y][x] not in SOLID}
    road = reachable(g, WEST, people)
    assert set(EAST) <= road and walk - people <= road, f"blocks you can't reach: {sorted(walk - people - road)[:8]}"
    seen = set().union(*(sight(g, *t) for t in TRAINERS.values()))
    assert not ROAD & seen, f"the road is in a trainer's sight at {sorted(ROAD & seen)[:4]}"
    for letter, ds in d.items():
        for x, y in ds:
            assert (x, y + 1) in road, f"the door of {letter} at ({x},{y}) can't be walked into"
    for y in range(MAP_H):
        for x in range(MAP_W):
            if g[y][x] == "S":
                assert (x, y + 1) in road, f"the sign at ({x},{y}) can't be read"


def main() -> None:
    g = plan()
    d = doors(g)
    cliffs.layout(g, roof="Y")  # the cave's mouth stands against the ridge: its top runs down to it, with no face
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
    sh.add(MOUTH.name, MOUTH.idx, tileset="secondary", ground="grass", solid=True, open=[f"{dx},{dy}"],
           behaviors={f"{dx},{dy}": "MB_NON_ANIMATED_DOOR"})  # an open mouth: you walk in, as in Route 2
    spec_mt += sh.write()
    gate, gds = _gate()
    sh = kit.Sheet(gate.name, gate.palette, GATE_BANK, HERE, HERE, cols=gate.idx.shape[1] // 16)
    sh.add(gate.name, gate.idx, tileset="secondary", ground="grass", solid=True,
           open=[f"{x},{y}" for x, y in gds], behaviors={f"{x},{y}": "MB_ANIMATED_DOOR" for x, y in gds})
    spec_mt += sh.write()
    for e in spec_mt:  # sheets put "w"/"h" on everything; drop the 1x1 ones for readability
        if e["w"] == 1 and e["h"] == 1:
            del e["w"], e["h"]
    kit.write_palette(HERE / f"palette_{CLIFF_BANK}.pal", cliffs.PAL)
    kit.write_palette(HERE / f"palette_{GATE_BANK}.pal", gate.palette)
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
    legend = dict(kit.LEGEND, Y={"name": MOUTH.name, "joins": "C"}, X=gate.name)
    assert not set("YX") & set(cliffs.legend(char_of)), "a building's letter is one of the cliffs'"
    legend.update(cliffs.legend(char_of))
    (HERE / "legend.json").write_text(json.dumps(legend, indent=1) + "\n")
    (HERE / "doors.json").write_text(json.dumps(d, indent=1) + "\n")
    print(f"{len(spec_mt)} metatiles in the spec; grid {MAP_W}x{MAP_H}; doors {d}")


if __name__ == "__main__":
    main()
