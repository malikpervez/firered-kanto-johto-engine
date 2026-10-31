#!/usr/bin/env python3
"""Route 4 after its concept (draw_plan.py and plan_stage1.txt): round Mt. Moon (see draw_plan.py). It is 108x20
blocks, as before, and its exits stay where its neighbours meet it: Route 3's road meets the bottom at columns 8-15,
Cerulean's road the right edge at rows 10-13 (Cerulean's 17-20).

The pieces: the kit's, the Pokémon Center (the kit's), its cliffs (cliffs.py) and Route 2's cave mouth for Mt. Moon's
two mouths: the mouth is drawn in the cliffs' own palette, so both are bank 7. Bank 8 is the kit's plants palette;
9-12 stay free for the seam to Cerulean (not rebuilt yet).

Run from the repository root:  python3 project/art/route4-concept/make_art.py
It writes sheets/, palette_7.pal, spec.json, grid.txt, border.txt, legend.json and doors.json next to itself;
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
SECONDARY = "gTileset_Route4Concept"
MAP_W, MAP_H = 108, 20
CLIFF_BANK = 7
SOUTH, EAST = [(x, MAP_H - 1) for x in range(8, 16)], [(MAP_W - 1, y) for y in range(10, 14)]


def _mouth() -> buildings.Building:
    """Route 2's cave mouth (its pack names its door ``door_blocks``, which the kit's loader doesn't read)."""
    folder = HERE.parent / "route2-concept/buildings/diglett_cave"
    meta = json.loads((folder / "diglett_cave.json").read_text())
    with Image.open(folder / "diglett_cave.png") as im:
        idx, flat = np.array(im, np.uint8), im.getpalette()[:48]
    return buildings.Building("diglett_cave", idx, [tuple(flat[i:i + 3]) for i in range(0, 48, 3)],
                              tuple(meta["door_blocks"][0]), folder / "diglett_cave_door.png")


MOUTH = _mouth()
# the far mouth is set into the plateau: only the mouth's face (its bottom two rows), the cliff's own top above it
FACE = buildings.Building("diglett_cave_face", MOUTH.idx[48:], MOUTH.palette, (MOUTH.door[0], MOUTH.door[1] - 3),
                          MOUTH.door_frames)
SOLID = set("T#bRoklSBcw_~vrZXY") | cliffs.SOLID  # (ledges are hopped going south only)


def plan() -> list[list[str]]:
    rows = (HERE / "plan_stage1.txt").read_text().split("\n")[:MAP_H]
    g = [list(r) for r in rows]
    assert len(g) == MAP_H and all(len(r) == MAP_W for r in g), "the plan is 108x20"
    return g


def doors(g) -> dict[str, list[tuple[int, int]]]:
    """The Center's door and the two mouths' (west to east)."""
    out = {}
    for letter, b in (("Z", kit.SHARED_BUILDINGS["pokemon_center"][0]), ("X", MOUTH), ("Y", FACE)):
        bw, bh = b.idx.shape[1] // 16, b.idx.shape[0] // 16
        cells = {(x, y) for y, r in enumerate(g) for x, c in enumerate(r) if c == letter}
        tops = sorted((x, y) for x, y in cells if (x - 1, y) not in cells and (x, y - 1) not in cells)
        for x0, y0 in tops:
            assert {(x0 + i, y0 + j) for i in range(bw) for j in range(bh)} <= cells, f"{letter} at ({x0},{y0})"
            out.setdefault(letter, []).append((x0 + b.door[0], y0 + b.door[1]))
        assert len(tops) * bw * bh == len(cells), f"{letter}: the plan's footprints aren't {bw}x{bh}"
    return out


def reachable(g, starts) -> set[tuple[int, int]]:
    """The blocks you can walk to from ``starts`` (ledges hopped going south only)."""
    seen, todo = set(starts), deque(starts)
    while todo:
        x, y = todo.popleft()
        for dx, dy in ((1, 0), (-1, 0), (0, 1), (0, -1)):
            nx, ny = x + dx, y + dy
            if not (0 <= nx < MAP_W and 0 <= ny < MAP_H) or (nx, ny) in seen:
                continue
            c = g[ny][nx]
            if c == "_":
                if dy == 1 and ny + 1 < MAP_H and g[ny + 1][nx] not in SOLID:
                    seen.add((nx, ny + 1))
                    todo.append((nx, ny + 1))
                continue
            if c in SOLID:
                continue
            seen.add((nx, ny))
            todo.append((nx, ny))
    return seen


def check(g, d) -> None:
    """The route's rules: only its two exits open onto the edges; the mountain divides it (the near mouth and the
    Center are reached from Route 3's road, the far mouth's shelf from nowhere but the cave); the shelf's way on is
    down its ledge to the road to Cerulean, and the shelf can't be reached from Cerulean; everything walkable is
    reached from one of the exits or the far mouth."""
    edge = {(x, y) for y in range(MAP_H) for x in range(MAP_W) if x in (0, MAP_W - 1) or y in (0, MAP_H - 1)}
    assert {xy for xy in edge if g[xy[1]][xy[0]] not in SOLID} == set(SOUTH + EAST), "only the exits open"
    (center,), (near,), (far,) = d["Z"], d["X"], d["Y"]
    below = lambda p: (p[0], p[1] + 1)
    west, east = reachable(g, [SOUTH[0]]), reachable(g, [EAST[0]])
    shelf = reachable(g, [below(far)])
    assert below(center) in west and below(near) in west, "the Center and the near mouth are off Route 3's road"
    assert not west & east, "the mountain must divide the route"
    assert below(far) not in east, "the far mouth must not be reached from Cerulean"
    assert set(EAST) <= shelf, "the shelf's way on must reach Cerulean"
    walk = {(x, y) for y in range(MAP_H) for x in range(MAP_W) if g[y][x] not in SOLID}
    assert walk <= west | east | shelf, f"blocks you can't reach: {sorted(walk - west - east - shelf)[:8]}"
    for y in range(MAP_H):
        for x in range(MAP_W):
            if g[y][x] == "S":
                assert (x, y + 1) in walk, f"the sign at ({x},{y}) can't be read"


def main() -> None:
    g = plan()
    d = doors(g)
    cliffs.layout(g, roof="Y")  # the far mouth stands against the cliff: its top runs down to it, with no face
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
    sh = kit.Sheet(FACE.name, FACE.palette, CLIFF_BANK, HERE, HERE, cols=FACE.idx.shape[1] // 16)
    dx, dy = FACE.door
    sh.add(FACE.name, FACE.idx, tileset="secondary", ground="grass", solid=True, open=[f"{dx},{dy}"],
           behaviors={f"{dx},{dy}": "MB_NON_ANIMATED_DOOR"})
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
    (HERE / "border.txt").write_text("TT\nTT\n")
    legend = dict(kit.LEGEND, Z="pokemon_center", X=MOUTH.name, Y={"name": FACE.name, "joins": "C"})
    assert not set("ZXY") & set(cliffs.legend(char_of)), "a building's letter is one of the cliffs'"
    legend.update(cliffs.legend(char_of))
    legend[":"] = {"auto": "dirt", "joins": "="}  # the road's dirt runs into Cerulean's cobbles with no grass rim
    (HERE / "legend.json").write_text(json.dumps(legend, indent=1) + "\n")
    (HERE / "doors.json").write_text(json.dumps(d, indent=1) + "\n")
    print(f"{len(spec_mt)} metatiles in the spec; grid {MAP_W}x{MAP_H}; doors {d}")


if __name__ == "__main__":
    main()
