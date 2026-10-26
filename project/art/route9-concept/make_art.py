#!/usr/bin/env python3
"""Route 9 after its concept (draw_plan.py and plan_stage1.txt): the hill road east from Cerulean to Rock Tunnel
(see draw_plan.py). It is 60x28 blocks (old Route 9 was 65x60); its joins: Cerulean's road east the left edge at rows
8-10 (Cerulean's 28-30, offset -20), Route 10 the right edge at rows 17-19 (Route 10's 17-19, offset 0), where old
Route 10's lawn by its west edge is open.

The pieces: the kit's and its cliffs (bank 7). Bank 8 is the kit's plants palette; 9-12 stay free for the seams to
old Route 10 (not rebuilt yet).

Run from the repository root:  python3 project/art/route9-concept/make_art.py
It writes sheets/, the palette, spec.json, grid.txt, border.txt and legend.json next to itself; build.sh turns them
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
SECONDARY = "gTileset_Route9Concept"
MAP_W, MAP_H = 60, 28
CLIFF_BANK = 7
WEST = [(0, y) for y in range(8, 11)]
EAST = [(MAP_W - 1, y) for y in range(17, 20)]
TREE = (9, 9)  # the tree to cut, in the neck (more than 8 blocks in: the game hides one nearer the edge you come in by)
# the trainers the plan is made for (build.sh places them): (x, y, the ways they look, sight, on the road). The
# gorge's two look across the whole road; no one else sees it
TRAINERS = {"Alicia": (13, 6, "down", 3, True), "Chris": (19, 6, "down", 3, True),
            "Jeremy": (19, 15, "up left", 4, False), "Brent": (13, 17, "down", 2, False),
            "Conner": (28, 20, "right", 3, False), "Drew": (30, 23, "right", 5, False),
            "Brice": (48, 22, "left right", 1, False), "Caitlin": (43, 9, "right", 4, False),
            "Alan": (50, 10, "down", 1, False)}
STEP = {"left": (-1, 0), "right": (1, 0), "up": (0, -1), "down": (0, 1)}
SOLID = set("T#bRoklSBcw_~vr") | cliffs.SOLID  # (ledges are hopped going south only)


def plan() -> list[list[str]]:
    rows = (HERE / "plan_stage1.txt").read_text().split("\n")[:MAP_H]
    g = [list(r) for r in rows]
    assert len(g) == MAP_H and all(len(r) == MAP_W for r in g), "the plan is 60x28"
    return g


def reachable(g, starts, blocked=frozenset()) -> set[tuple[int, int]]:
    """The blocks you can walk to from ``starts`` (ledges hopped going south only)."""
    seen, todo = set(starts), deque(starts)
    while todo:
        x, y = todo.popleft()
        for dx, dy in ((1, 0), (-1, 0), (0, 1), (0, -1)):
            nx, ny = x + dx, y + dy
            if not (0 <= nx < MAP_W and 0 <= ny < MAP_H) or (nx, ny) in seen or (nx, ny) in blocked:
                continue
            c = g[ny][nx]
            if c == "_":
                land = (nx, ny + 1)
                if dy == 1 and ny + 1 < MAP_H and g[ny + 1][nx] not in SOLID and land not in seen | set(blocked):
                    seen.add(land)
                    todo.append(land)
                continue
            if c in SOLID:
                continue
            seen.add((nx, ny))
            todo.append((nx, ny))
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


def check(g) -> None:
    """The route's rules: only its two roads open onto the edges; the tree closes the way in, and with it cut
    everything walkable is reached, and Cerulean is reached back from Route 10; the gorge's two trainers can't be
    passed without a battle, and no one else sees the road; the sign can be read."""
    edge = {(x, y) for y in range(MAP_H) for x in range(MAP_W) if x in (0, MAP_W - 1) or y in (0, MAP_H - 1)}
    assert {xy for xy in edge if g[xy[1]][xy[0]] not in SOLID} == set(WEST + EAST), "only the two roads open"
    people = {t[:2] for t in TRAINERS.values()}
    assert all(x <= 8 for x, _ in reachable(g, WEST, people | {TREE})), "the tree must close the way in"
    assert TREE[0] > 8, "the game would hide the tree as you come in from Cerulean"
    walk = {(x, y) for y in range(MAP_H) for x in range(MAP_W) if g[y][x] not in SOLID} - people
    every = reachable(g, WEST, people)
    assert walk <= every, f"blocks you can't reach: {sorted(walk - every)[:8]}"
    assert set(WEST) <= reachable(g, EAST, people), "Cerulean can't be reached back from Route 10"
    road = {(x, y) for y in range(MAP_H) for x in range(MAP_W) if g[y][x] in ":="}
    for name, (x, y, facings, n, on_road) in TRAINERS.items():
        seen = sight(g, x, y, facings, n)
        if on_road:
            assert not set(EAST) & reachable(g, WEST, people | seen), f"{name} can be passed without a battle"
        else:
            assert not seen & road, f"{name} sees the road at {sorted(seen & road)[:3]}"
    for y in range(MAP_H):
        for x in range(MAP_W):
            if g[y][x] == "S":
                assert (x, y + 1) in every, f"the sign at ({x},{y}) can't be read"


def main() -> None:
    g = plan()
    cliffs.layout(g)
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
    (HERE / "border.txt").write_text("TT\nTT\n")
    legend = dict(kit.LEGEND)
    legend.update(cliffs.legend(char_of))
    (HERE / "legend.json").write_text(json.dumps(legend, indent=1) + "\n")
    print(f"{len(spec_mt)} metatiles in the spec; grid {MAP_W}x{MAP_H}")


if __name__ == "__main__":
    main()
