#!/usr/bin/env python3
"""Route 10 after its concept (draw_plan.py and plan_stage1.txt): down the east of the mountains from Route 9 to
Lavender, Rock Tunnel under them (see draw_plan.py). It is 38x60 blocks (old Route 10 was 38x90), as wide as before;
its joins: Route 9's road the left edge at rows 17-19 (offset 0), Lavender's road north the bottom at columns 16-20
(Lavender's 12-16, offset 4).

The pieces: the kit's, the Pokémon Center (the kit's), its cliffs and Route 2's cave mouth for Rock Tunnel's two
mouths in the cliffs' palette (bank 7), and the Power Plant (Kanto Buildings Remakes v0.3, ../packs/buildings_v0.3:
15x8 blocks, its door at 7,7) in Pewter's stone palette (bank 9). Bank 8 is the kit's plants palette; 10-12 stay free for the seam to
Lavender (not rebuilt yet).

Run from the repository root:  python3 project/art/route10-concept/make_art.py
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
SECONDARY = "gTileset_Route10Concept"
MAP_W, MAP_H = 38, 60
CLIFF_BANK, PLANT_BANK = 7, 9
WEST = [(0, y) for y in range(17, 20)]
SOUTH = [(x, MAP_H - 1) for x in range(16, 21)]
TREES = [(20, 11), (21, 11), (22, 11), (23, 11)]  # the young trees to cut, closing the meadow
MEADOW = (24, 5)
ISLAND = (28, 42)
# the trainers the plan is made for (build.sh places them): (x, y, the ways they look, sight). None sees the road
TRAINERS = {"Heidi": (22, 13, "down", 2), "Mark": (27, 22, "left", 5),
            "Carol": (28, 50, "up down left right", 2), "Clark": (5, 50, "up down left right", 1),
            "Herman": (26, 57, "left right", 2), "Trent": (6, 57, "left", 2)}
HERMAN_WALK = range(24, 29)  # Herman wanders left and right along row 57
STEP = {"left": (-1, 0), "right": (1, 0), "up": (0, -1), "down": (0, 1)}
WATER = set("~")
SOLID = set("T#bRoklSBcw_~vrYZX") | cliffs.SOLID

# the Power Plant, from the remakes pack: four sawtooth halls, a boiler annex, two stacks and a sealed loading shutter;
# one door (its personnel entrance), at 7,7
PLANT = buildings.load(buildings.REMAKES / "power_plant")


def _mouth() -> buildings.Building:
    """Route 2's cave mouth (its pack names its door ``door_blocks``, which the kit's loader doesn't read)."""
    folder = ART / "route2-concept/buildings/diglett_cave"
    meta = json.loads((folder / "diglett_cave.json").read_text())
    with Image.open(folder / "diglett_cave.png") as im:
        idx, flat = np.array(im, np.uint8), im.getpalette()[:48]
    return buildings.Building("diglett_cave", idx, [tuple(flat[i:i + 3]) for i in range(0, 48, 3)],
                              tuple(meta["door_blocks"][0]), folder / "diglett_cave_door.png")


MOUTH = _mouth()
CENTER = kit.SHARED_BUILDINGS["pokemon_center"][0]


def plan() -> list[list[str]]:
    rows = (HERE / "plan_stage1.txt").read_text().split("\n")[:MAP_H]
    g = [list(r) for r in rows]
    assert len(g) == MAP_H and all(len(r) == MAP_W for r in g), "the plan is 38x60"
    return g


def doors(g) -> dict[str, list[tuple[int, int]]]:
    """Each building's doors: the caves' two mouths (both Y), the Center's, the plant's."""
    out = {}
    for letter, b in (("Y", MOUTH), ("Z", CENTER), ("X", PLANT)):
        bw, bh = b.idx.shape[1] // 16, b.idx.shape[0] // 16
        cells = {(x, y) for y, r in enumerate(g) for x, c in enumerate(r) if c == letter}
        found = []
        while cells:
            x0, y0 = min(cells, key=lambda c: (c[1], c[0]))
            foot = {(x0 + i, y0 + j) for i in range(bw) for j in range(bh)}
            assert foot <= cells, f"{letter} at ({x0},{y0}) isn't its footprint"
            cells -= foot
            found.append((x0 + b.door[0], y0 + b.door[1]))
        out[letter] = sorted(found, key=lambda d: d[1])
    return out


def reachable(g, starts, blocked=frozenset(), surf=False) -> set[tuple[int, int]]:
    seen, todo = set(starts), deque(starts)
    while todo:
        x, y = todo.popleft()
        for n in ((x + 1, y), (x - 1, y), (x, y + 1), (x, y - 1)):
            if not (0 <= n[0] < MAP_W and 0 <= n[1] < MAP_H) or n in seen or n in blocked:
                continue
            c = g[n[1]][n[0]]
            if c in SOLID and not (surf and c in WATER):
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
    """The route's rules: only Route 9's road and Lavender's open onto the edges; from Route 9 you reach the north
    clearing (the Center, Rock Tunnel's north mouth) and, with the young trees cut, the meadow, and by water the plant's
    island, but not the south valley, which is reached from Lavender (Rock Tunnel's south mouth); everything walkable is
    reached one way or the other; no trainer sees the road; the doors can be walked into and the signs read."""
    edge = {(x, y) for y in range(MAP_H) for x in range(MAP_W) if x in (0, MAP_W - 1) or y in (0, MAP_H - 1)}
    assert {xy for xy in edge if g[xy[1]][xy[0]] not in SOLID} == set(WEST + SOUTH), "only the two roads open"
    people = {t[:2] for t in TRAINERS.values()}
    north = reachable(g, WEST, people | set(TREES))
    assert MEADOW not in north, "the young trees must close the meadow"
    cut = reachable(g, WEST, people)
    assert MEADOW in cut and ISLAND not in cut, "the meadow opens when the trees are cut; the island is only by water"
    wet = reachable(g, WEST, people, surf=True)
    assert ISLAND in wet, "the plant's island must be reached by water"
    south = reachable(g, SOUTH, people, surf=True)
    assert not set(SOUTH) & wet and not set(WEST) & south, "the mountains must part the north from the south"
    walk = {(x, y) for y in range(MAP_H) for x in range(MAP_W) if g[y][x] not in SOLID} - people
    assert walk <= wet | south, f"blocks you can't reach: {sorted(walk - wet - south)[:8]}"
    (north_mouth, south_mouth), (center,), (plant,) = d["Y"], d["Z"], d["X"]
    for (x, y), side in ((north_mouth, north), (center, north), (plant, wet), (south_mouth, south)):
        assert (x, y + 1) in side, f"the door at ({x},{y}) can't be walked into"
    road = {(x, y) for y in range(MAP_H) for x in range(MAP_W) if g[y][x] == ":"}
    for name, (x, y, facings, n) in TRAINERS.items():
        spots = [(hx, y) for hx in HERMAN_WALK] if name == "Herman" else [(x, y)]
        seen = set().union(*(sight(g, sx, sy, facings, n) for sx, sy in spots))
        assert not seen & road, f"{name} sees the road at {sorted(seen & road)[:3]}"
    for y in range(MAP_H):
        for x in range(MAP_W):
            if g[y][x] == "S":
                assert (x, y + 1) in wet | south, f"the sign at ({x},{y}) can't be read"


def main() -> None:
    g = plan()
    d = doors(g)
    cliffs.layout(g, roof="Y")  # the caves' mouths stand against the cliffs: their tops run down to them, with no face
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
    sh = kit.Sheet(PLANT.name, PLANT.palette, PLANT_BANK, HERE, HERE, cols=PLANT.idx.shape[1] // 16)
    sh.add(PLANT.name, PLANT.idx, tileset="secondary", **PLANT.entry())
    spec_mt += sh.write()
    for e in spec_mt:  # sheets put "w"/"h" on everything; drop the 1x1 ones for readability
        if e["w"] == 1 and e["h"] == 1:
            del e["w"], e["h"]
    kit.write_palette(HERE / f"palette_{CLIFF_BANK}.pal", cliffs.PAL)
    kit.write_palette(HERE / f"palette_{PLANT_BANK}.pal", PLANT.palette)
    spec = {"version": "hns", "primary": kit.PRIMARY, "secondary": SECONDARY,
            "palettes": {"primary": base["palettes"],
                         "secondary": [f"palette_{CLIFF_BANK}.pal", base["secondary_palettes"][8],
                                       f"palette_{PLANT_BANK}.pal"]},
            "reserve": {"primary": base["reserve"]},
            "animations": base["animations"],
            "field_effects": base["field_effects"],
            "metatiles": spec_mt}
    (HERE / "spec.json").write_text(json.dumps(spec, indent=1) + "\n")
    (HERE / "grid.txt").write_text("".join("".join(r) + "\n" for r in g))
    (HERE / "border.txt").write_text("TT\nTT\n")
    legend = dict(kit.LEGEND, Y={"name": MOUTH.name, "joins": "C"}, Z="pokemon_center", X=PLANT.name)
    assert not set("YZX") & set(cliffs.legend(char_of)), "a building's letter is one of the cliffs'"
    legend.update(cliffs.legend(char_of))
    (HERE / "legend.json").write_text(json.dumps(legend, indent=1) + "\n")
    (HERE / "doors.json").write_text(json.dumps(d, indent=1) + "\n")
    print(f"{len(spec_mt)} metatiles in the spec; grid {MAP_W}x{MAP_H}; doors {d}")


if __name__ == "__main__":
    main()
