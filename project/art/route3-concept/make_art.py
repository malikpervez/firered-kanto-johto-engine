#!/usr/bin/env python3
"""Route 3 after its concept (draw_plan.py and plan_stage1.txt): the mountain road east from Pewter (see
draw_plan.py). It is 84x20 blocks, as before, and its exits stay where its neighbours meet it: Pewter's road east
meets the left edge at rows 9-12, Route 4's road the top at columns 68-75.

The pieces: the kit's and its cliffs (cliffs.py, bank 7). Bank 8 is the kit's plants palette; 9-12 stay free for the
seam to Route 4 (not rebuilt yet).

Run from the repository root:  python3 project/art/route3-concept/make_art.py
It writes sheets/, palette_7.pal, spec.json, grid.txt, border.txt and legend.json next to itself; build.sh turns them
into the game's tileset and map with pae.
"""
import json
import sys
from collections import deque
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "kit"))
import cliffs
import kit

HERE = Path(__file__).resolve().parent
SECONDARY = "gTileset_Route3Concept"
MAP_W, MAP_H = 84, 20
CLIFF_BANK = 7
WEST, NORTH = [(0, y) for y in range(9, 13)], [(x, 0) for x in range(68, 76)]
FIELD = (18, 9, 40, 15)  # the tall grass across the valley floor
SOLID = set("T#bRoklSBcw_~vr") | cliffs.SOLID  # (ledges are hopped going south only)
# Pewter's forest carried on over the join (columns 0-1, rows 13-18): whole trees on Pewter's 2x2 grid, which is a
# row off this map's (the join is 15 rows down), so they are stamped here by name, not drawn by "auto" on this grid
# (which cut the top one in half under the road): the top one, the middle one, the last one over the plateau
JOIN_TREES = {"\u24e3": (13, "forest#12"), "\u24e4": (15, "forest#13"), "\u24e5": (17, "forest#9")}
SOLID |= set(JOIN_TREES)


def plan() -> list[list[str]]:
    rows = (HERE / "plan_stage1.txt").read_text().split("\n")[:MAP_H]
    g = [list(r) for r in rows]
    assert len(g) == MAP_H and all(len(r) == MAP_W for r in g), "the plan is 84x20"
    return g


def reachable(g, start, blocked=frozenset()) -> set[tuple[int, int]]:
    """The blocks you can walk to from ``start`` (ledges hopped going south only)."""
    seen, todo = {start}, deque([start])
    while todo:
        x, y = todo.popleft()
        for dx, dy in ((1, 0), (-1, 0), (0, 1), (0, -1)):
            nx, ny = x + dx, y + dy
            if not (0 <= nx < MAP_W and 0 <= ny < MAP_H) or (nx, ny) in seen or (nx, ny) in blocked:
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


def check(g) -> None:
    """The route's rules: only its two exits open onto the edges; everything walkable is reached from Pewter's road;
    the way north is through the tall grass (it can't be walked round), from the high path too (its way on is down its
    ledge into the grass)."""
    edge = {(x, y) for y in range(MAP_H) for x in range(MAP_W) if x in (0, MAP_W - 1) or y in (0, MAP_H - 1)}
    assert {xy for xy in edge if g[xy[1]][xy[0]] not in SOLID} == set(WEST + NORTH), "only the exits open"
    walk = {(x, y) for y in range(MAP_H) for x in range(MAP_W) if g[y][x] not in SOLID}
    every = reachable(g, WEST[0])
    assert walk <= every, f"blocks you can't reach: {sorted(walk - every)[:8]}"
    x0, y0, x1, y1 = FIELD
    grass = {(x, y) for x in range(x0, x1 + 1) for y in range(y0, y1 + 1) if g[y][x] == "g"}
    assert not set(NORTH) & reachable(g, WEST[0], grass), "the tall grass can be walked round"
    assert not set(NORTH) & reachable(g, (20, 5), grass), "the high path goes round the grass"


def main() -> None:
    g = plan()
    cliffs.layout(g)
    g[7][0] = g[8][0] = "P"  # the face over the way in runs on into Pewter's (no rounded end at the join)
    for ch, (y, _) in JOIN_TREES.items():
        for yy in (y, y + 1):
            g[yy][0] = g[yy][1] = ch
    kit.check_forest(g)
    kit.check_water(g)
    check(g)
    base = kit.primary(HERE)  # the kit: the primary tileset every map shares
    spec_mt = list(base["metatiles"])
    rock = kit.Sheet("rock_cliff", cliffs.PAL, CLIFF_BANK, HERE, HERE)
    char_of = cliffs.add(rock, g, extras=())
    spec_mt += rock.write()
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
    (HERE / "border.txt").write_text("CC\nCC\n".replace("C", cliffs.TOP[0]))
    legend = dict(kit.LEGEND)
    legend.update(cliffs.legend(char_of))
    legend.update({ch: {"name": name} for ch, (_, name) in JOIN_TREES.items()})
    (HERE / "legend.json").write_text(json.dumps(legend, indent=1) + "\n")
    print(f"{len(spec_mt)} metatiles in the spec; grid {MAP_W}x{MAP_H}")


if __name__ == "__main__":
    main()
