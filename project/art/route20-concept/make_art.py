#!/usr/bin/env python3
"""Route 20 after its concept (draw_plan.py and plan_stage1.txt): the sea route west from Route 19 to Cinnabar
Island, past the Seafoam Islands (see draw_plan.py). It is 120x20 blocks, as before; its joins stay where they were:
Cinnabar's sea at the left edge (offset 0) and Route 19's sea (its rows 41-59) at the right edge, rows 0-18 (offset
-41).

The pieces: the kit's, its cliffs for the islands and Route 2's cave mouth for Seafoam's two mouths, in the cliffs'
palette (bank 7), as Route 10 has them for Rock Tunnel's.

Run from the repository root:  python3 project/art/route20-concept/make_art.py
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
import buildings
import cliffs
import kit

HERE = Path(__file__).resolve().parent
ART = HERE.parent
SECONDARY = "gTileset_Route20Concept"
MAP_W, MAP_H = 120, 20
CLIFF_BANK = 7
EAST = [(MAP_W - 1, y) for y in range(0, 19)]
WEST = [(0, y) for y in range(MAP_H)]
SEA = "s"
SOLID = set("T#bRoklSBcw_~vrsqQY") | cliffs.SOLID
# the people (local ids 1-11): the swimmers in the water, the picnickers, Roger and the camper on land; where they
# are, which ways they look and how far (the lookers-about and wanderers look round)
ROUND = ("NESW", 1)
IN_WATER = [(8, 11, ("NS", 3)), (34, 7, ("S", 4)), (23, 10, ROUND), (111, 9, ROUND), (106, 11, ROUND),
            (93, 10, ("NESW", 5)), (48, 12, ROUND)]
ON_LAND = [(12, 5, ("S", 1)), (43, 9, ROUND), (84, 15, ("W", 2)), (64, 14, ("EW", 1))]
STARDUST = (23, 6)
SANDBARS = [(12, 4), (22, 5), (42, 10), (93, 15)]


def _mouth() -> buildings.Building:
    """Route 2's cave mouth (its pack names its door ``door_blocks``, which the kit's loader doesn't read)."""
    folder = ART / "route2-concept/buildings/diglett_cave"
    meta = json.loads((folder / "diglett_cave.json").read_text())
    with Image.open(folder / "diglett_cave.png") as im:
        idx, flat = np.array(im, np.uint8), im.getpalette()[:48]
    return buildings.Building("diglett_cave", idx, [tuple(flat[i:i + 3]) for i in range(0, 48, 3)],
                              tuple(meta["door_blocks"][0]), folder / "diglett_cave_door.png")


def _face_mouth() -> buildings.Building:
    """The mouth cut into the cliff's face: the face's middle columns (two blocks tall, straight sides, no grass) with
    Route 2's mouth's opening in them, its door on the bottom row (the cliff's top runs on over it)."""
    full = _mouth()
    idx = np.concatenate([cliffs.pack(f"face/{n}.png") for n in ("middle_1", "middle_2", "middle_3") * 2], axis=1)
    hole = (slice(2, 32), slice(26, 70))  # the opening and its rim, from the mouth's bottom two rows
    idx[hole] = full.idx[48:80][hole]
    return buildings.Building(full.name, idx, full.palette, (full.door[0], 1), full.door_frames)


MOUTH = _face_mouth()


def plan() -> list[list[str]]:
    rows = (HERE / "plan_stage1.txt").read_text().split("\n")[:MAP_H]
    g = [list(r) for r in rows]
    assert len(g) == MAP_H and all(len(r) == MAP_W for r in g), "the plan is 120x20"
    return g


def doors(g) -> list[tuple[int, int]]:
    """The two mouths' doors, west first."""
    bw, bh = MOUTH.idx.shape[1] // 16, MOUTH.idx.shape[0] // 16
    cells = {(x, y) for y, r in enumerate(g) for x, c in enumerate(r) if c == "Y"}
    found = []
    while cells:
        x0, y0 = min(cells)
        foot = {(x0 + i, y0 + j) for i in range(bw) for j in range(bh)}
        assert foot <= cells, f"Y at ({x0},{y0}) isn't its footprint"
        cells -= foot
        found.append((x0 + MOUTH.door[0], y0 + MOUTH.door[1]))
    return sorted(found)


def reachable(g, starts, surf=False) -> set[tuple[int, int]]:
    seen, todo = set(starts), deque(starts)
    while todo:
        x, y = todo.popleft()
        for n in ((x + 1, y), (x - 1, y), (x, y + 1), (x, y - 1)):
            if not (0 <= n[0] < MAP_W and 0 <= n[1] < MAP_H) or n in seen:
                continue
            c = g[n[1]][n[0]]
            if c in SOLID and not (surf and c == SEA):
                continue
            seen.add(n)
            todo.append(n)
    return seen


def sight(g, x, y, dirs, n, water) -> set[tuple[int, int]]:
    out = set()
    for d in dirs:
        dx, dy = {"N": (0, -1), "E": (1, 0), "S": (0, 1), "W": (-1, 0)}[d]
        for k in range(1, n + 1):
            c = (x + dx * k, y + dy * k)
            if not (0 <= c[0] < MAP_W and 0 <= c[1] < MAP_H):
                break
            ch = g[c[1]][c[0]]
            if ch in SOLID and not (water and ch == SEA):
                break
            out.add(c)
    return out


def check(g, d) -> None:
    """The route's rules: there is nothing to walk on at the edges (the route is crossed by Surf); by Surf from Route
    19's side, every island and sandbar, both caves' mouths and Cinnabar's side are reached; each mouth's door can be
    walked into from the shore below it, and the two islands' shores aren't joined on foot; the swimmers are in the
    water, the people on land, each sees some of the way; the Stardust is on a sandbar; the signs can be read."""
    walk = {(x, y) for y in range(MAP_H) for x in range(MAP_W) if g[y][x] not in SOLID}
    assert not {(x, y) for x, y in walk if x in (0, MAP_W - 1) or y in (0, MAP_H - 1)}, "land on an edge"
    surfing = reachable(g, [EAST[9]], surf=True)
    assert walk <= surfing and set(WEST) & surfing, f"blocks you can't reach: {sorted(walk - surfing)[:8]}"
    (wx, wy), (ex, ey) = d
    west_shore, east_shore = reachable(g, [(wx, wy + 1)]), reachable(g, [(ex, ey + 1)])
    assert not west_shore & east_shore, "the islands' shores are apart"
    assert all(xy not in west_shore | east_shore for xy in SANDBARS), "the sandbars are their own"
    people = [(x, y) for x, y, _ in IN_WATER + ON_LAND]
    assert len(set(people)) == len(people), "two on one block"
    for x, y, look in IN_WATER:
        assert g[y][x] == SEA and sight(g, x, y, *look, True), f"the swimmer at ({x},{y}) in the water"
    for x, y, look in ON_LAND:
        assert (x, y) in walk and sight(g, x, y, *look, False), f"the person at ({x},{y}) on land"
    assert STARDUST in walk, "the Stardust on a sandbar"
    for y in range(MAP_H):
        for x in range(MAP_W):
            if g[y][x] == "S":
                assert (x, y + 1) in walk, f"the sign at ({x},{y}) can't be read"


def main() -> None:
    g = plan()
    d = doors(g)
    cliffs.layout(g, roof="Y")  # the mouths stand against the cliffs: their tops run down to them, with no face
    for y in range(MAP_H):  # the face runs on unbroken either side of a mouth (no ends beside it)
        for x in range(MAP_W):
            if g[y][x] == "}" and g[y][x + 1] == "Y":
                g[y][x] = next(c for c in cliffs.MIDDLES if c != g[y][x - 1])
            elif g[y][x] == "{" and g[y][x - 1] == "Y":
                g[y][x] = next(c for c in cliffs.MIDDLES if c != g[y][x + 1])
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
    for e in spec_mt:  # sheets put "w"/"h" on everything; drop the 1x1 ones for readability
        if e["w"] == 1 and e["h"] == 1:
            del e["w"], e["h"]
    kit.write_palette(HERE / f"palette_{CLIFF_BANK}.pal", cliffs.PAL)
    spec = {"version": "hns", "primary": kit.PRIMARY, "secondary": SECONDARY,
            "palettes": {"primary": base["palettes"],
                         "secondary": [f"palette_{CLIFF_BANK}.pal", base["secondary_palettes"][8]]},
            "reserve": {"primary": base["reserve"]},
            "animations": base["animations"],
            "field_effects": base["field_effects"],
            "metatiles": spec_mt}
    (HERE / "spec.json").write_text(json.dumps(spec, indent=1) + "\n")
    (HERE / "grid.txt").write_text("".join("".join(r) + "\n" for r in g))
    (HERE / "border.txt").write_text("ss\nss\n")
    legend = dict(kit.LEGEND, Y={"name": MOUTH.name, "joins": "C"})
    assert "Y" not in cliffs.legend(char_of), "the mouth's letter is one of the cliffs'"
    legend.update(cliffs.legend(char_of))
    (HERE / "legend.json").write_text(json.dumps(legend, indent=1) + "\n")
    (HERE / "doors.json").write_text(json.dumps({"Y": d}, indent=1) + "\n")
    print(f"{len(spec_mt)} metatiles in the spec; grid {MAP_W}x{MAP_H}; doors {d}")


if __name__ == "__main__":
    main()
