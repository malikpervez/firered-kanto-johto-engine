#!/usr/bin/env python3
"""Route 24 after its concept (draw_plan.py and plan_stage1.txt): Nugget Bridge, north out of Cerulean (see
draw_plan.py). It is 30x22 blocks, as before, and its exits stay where its neighbours meet it: Cerulean's bridge road
meets the bottom at columns 16-19; Route 25 the top at its west path (columns 7-10), the bridge (16-19) and its east
path (24-25).

The pieces are all the kit's: the route has no tileset of its own to speak of (bank 7 is blank, bank 8 the kit's
plants palette), so 7 and 9-12 are free for the seam to Route 25 (not rebuilt yet).

Run from the repository root:  python3 project/art/route24-concept/make_art.py
It writes palette_7.pal, spec.json, grid.txt, border.txt and legend.json next to itself; build.sh turns them into
the game's tileset and map with pae.
"""
import json
import sys
from collections import deque
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "kit"))
import kit

HERE = Path(__file__).resolve().parent
SECONDARY = "gTileset_Route24Concept"
MAP_W, MAP_H = 30, 22
SOUTH = [(x, MAP_H - 1) for x in range(16, 20)]
NORTH = [(x, 0) for x in (7, 8, 9, 10, 16, 17, 18, 19, 24, 25)]
WATER = set("~vr")
SOLID = set("T#bRoklSBcw_~vr")
# the people the plan is made for (build.sh places them so): the bridge's five trainers, each at a side looking
# across it and seeing all of its width (x, y, facing, sight), the Rocket and his triggers, and Shane on the shore
TRAINERS = [(19, 19, "left", 3), (16, 17, "right", 3), (19, 15, "left", 3), (16, 13, "right", 3), (19, 11, "left", 3)]
ROCKET, ROCKET_GATE = (18, 8), [(16, 8), (17, 8), (19, 8)]
SHANE = (8, 12, "up", 4)
STEP = {"left": (-1, 0), "right": (1, 0), "up": (0, -1), "down": (0, 1)}


def plan() -> list[list[str]]:
    rows = (HERE / "plan_stage1.txt").read_text().split("\n")[:MAP_H]
    g = [list(r) for r in rows]
    assert len(g) == MAP_H and all(len(r) == MAP_W for r in g), "the plan is 30x22"
    return g


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


def sight(g, x, y, facing, n) -> set[tuple[int, int]]:
    out = set()
    dx, dy = STEP[facing]
    for k in range(1, n + 1):
        c = (x + dx * k, y + dy * k)
        if not (0 <= c[0] < MAP_W and 0 <= c[1] < MAP_H) or g[c[1]][c[0]] in SOLID:
            break
        out.add(c)
    return out


def check(g) -> None:
    """The route's rules:
    - only its exits open onto the edges (Cerulean's bridge road; Route 25's west path, bridge and east path);
    - the bridge can't be crossed past any of its five trainers unseen, nor past the Rocket without his triggers;
    - the west shore and the east meadow are off Route 25's paths (and the shore off the lake, by Surf);
    - the pond at the bridge's foot (Cerulean's water east of its bridge) is reached from nowhere here, even by Surf;
    - everything walkable is reached from an exit."""
    edge = {(x, y) for y in range(MAP_H) for x in range(MAP_W) if x in (0, MAP_W - 1) or y in (0, MAP_H - 1)}
    assert {xy for xy in edge if g[xy[1]][xy[0]] not in SOLID} == set(SOUTH + NORTH), "only the exits open"
    people = {(x, y) for x, y, _, _ in TRAINERS} | {ROCKET, SHANE[:2]}
    seen = set().union(*(sight(g, *t) for t in TRAINERS))
    walk = {(x, y) for y in range(MAP_H) for x in range(MAP_W) if g[y][x] not in SOLID} - people
    for x, y, _, _ in TRAINERS:
        across = {(bx, y) for bx in range(16, 20) if (bx, y) in walk}
        assert across <= seen, f"the bridge's row {y} can be crossed unseen at {sorted(across - seen)}"
    north_of_bridge = reachable(g, [SOUTH[0]], people | seen | set(ROCKET_GATE))
    assert not set(NORTH) & north_of_bridge, "the bridge can be crossed past its trainers or the Rocket"
    everywhere = reachable(g, SOUTH + NORTH, people)
    assert walk <= everywhere, f"blocks you can't reach: {sorted(walk - everywhere)[:8]}"
    pond = {(x, y) for x in range(21, 28) for y in range(15, MAP_H)}
    by_sea = reachable(g, SOUTH + NORTH, people, surf=True)
    assert not pond & by_sea, "the pond at the bridge's foot can be surfed into from here"
    shore, meadow = (6, 4), (24, 9)
    assert shore in reachable(g, [(8, 0)], people) and meadow in reachable(g, [(24, 0)], people)
    assert not {shore, meadow} & reachable(g, [SOUTH[0]], people | seen | set(ROCKET_GATE) | set(NORTH)), \
        "the shore or the meadow is reached from the bridge"


def main() -> None:
    g = plan()
    kit.check_forest(g)
    kit.check_water(g)
    check(g)
    base = kit.primary(HERE)  # the kit: the primary tileset every map shares
    spec_mt = list(base["metatiles"])
    for e in spec_mt:
        if e["w"] == 1 and e["h"] == 1:
            del e["w"], e["h"]
    kit.write_palette(HERE / "palette_7.pal", [(0, 0, 0)] * 16)  # (nothing uses bank 7: the seams may)
    spec = {"version": "hns", "primary": kit.PRIMARY, "secondary": SECONDARY,
            "palettes": {"primary": base["palettes"], "secondary": ["palette_7.pal", base["secondary_palettes"][8]]},
            "reserve": {"primary": base["reserve"]},
            "animations": base["animations"],
            "field_effects": base["field_effects"],
            "metatiles": spec_mt}
    (HERE / "spec.json").write_text(json.dumps(spec, indent=1) + "\n")
    (HERE / "grid.txt").write_text("".join("".join(r) + "\n" for r in g))
    (HERE / "border.txt").write_text("~~\n~~\n")
    (HERE / "legend.json").write_text(json.dumps(dict(kit.LEGEND), indent=1) + "\n")
    print(f"{len(spec_mt)} metatiles in the spec; grid {MAP_W}x{MAP_H}")


if __name__ == "__main__":
    main()
