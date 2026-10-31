#!/usr/bin/env python3
"""Route 25 after its concept (draw_plan.py and plan_stage1.txt): Cerulean's cape, a road east under a rock ridge to
Bill's Sea Cottage (see draw_plan.py). It is 70x24 blocks; its only exits are where Route 24 meets its bottom: the
west path (columns 7-10), the bridge (16-19) and the east path (24-25).

The pieces: the kit's, its cliffs (cliffs.py) in bank 7, and Viridian's pond keeper's house for the cottage, in
Viridian's houses' palette (bank 9). Bank 8 is the kit's plants palette; 10-12 stay free for the seams. Route 24 is
the kit's alone, so the seam between them needs no palette of either's own.

Run from the repository root:  python3 project/art/route25-concept/make_art.py
It writes sheets/, the palettes, spec.json, grid.txt, border.txt, legend.json and doors.json next to itself;
build.sh turns them into the game's tileset and map with pae.
"""
import json
import sys
from collections import deque
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "kit"))
import buildings
import cliffs
import kit

HERE = Path(__file__).resolve().parent
SECONDARY = "gTileset_Route25Concept"
MAP_W, MAP_H = 70, 24
CLIFF_BANK, HOUSE_BANK = 7, 9
COTTAGE = buildings.load(HERE.parent / "viridian-concept/buildings/house_pond_keeper")
SOUTH = [(x, MAP_H - 1) for x in (7, 8, 9, 10, 16, 17, 18, 19, 24, 25)]
BRIDGE = (17, MAP_H - 1)
WATER = set("~vr")
SOLID = set("T#bRoklSBcw_~vrsqQH") | cliffs.SOLID  # (ledges are hopped going south only)
# the people the plan is made for (build.sh places them so): the trainers (x, y, the ways they look, sight)...
TRAINERS = {"Franklin": (6, 8, "right", 4), "Joey": (28, 8, "down", 2), "Wayne": (47, 8, "down", 2),
            "Dan": (35, 13, "up down left right", 2), "Kelsey": (39, 12, "right", 2), "Nob": (44, 12, "up", 3),
            "Flint": (41, 8, "down", 3), "Chad": (40, 16, "left right", 2), "Haley": (55, 8, "down", 3)}
NECKS = {"Joey": 28, "Wayne": 47}  # the two who hold the road's necks (their columns)
CUT_TREE = (34, 7)                 # in the garden's gate
# ...and the others who stand in the way: the TM's ball, the couple at the lookout, Swablu, Spearow, Butterfree
OTHERS = [(36, 5), (57, 9), (57, 10), (12, 5), (56, 6), (47, 16)]
STEP = {"left": (-1, 0), "right": (1, 0), "up": (0, -1), "down": (0, 1)}


def plan() -> list[list[str]]:
    rows = (HERE / "plan_stage1.txt").read_text().split("\n")[:MAP_H]
    g = [list(r) for r in rows]
    assert len(g) == MAP_H and all(len(r) == MAP_W for r in g), "the plan is 70x24"
    return g


def doors(g) -> dict[str, list[tuple[int, int]]]:
    """The cottage's door."""
    b = COTTAGE
    bw, bh = b.idx.shape[1] // 16, b.idx.shape[0] // 16
    cells = {(x, y) for y, r in enumerate(g) for x, c in enumerate(r) if c == "H"}
    x0, y0 = min(cells)
    assert cells == {(x0 + i, y0 + j) for i in range(bw) for j in range(bh)}, "the cottage isn't its footprint"
    return {"H": [(x0 + b.door[0], y0 + b.door[1])]}


def reachable(g, starts, blocked=frozenset()) -> set[tuple[int, int]]:
    """The blocks you can walk to from ``starts``, not through ``blocked`` (ledges hopped going south only)."""
    seen, todo = set(starts), deque(starts)
    while todo:
        x, y = todo.popleft()
        for dx, dy in ((1, 0), (-1, 0), (0, 1), (0, -1)):
            nx, ny = x + dx, y + dy
            if not (0 <= nx < MAP_W and 0 <= ny < MAP_H) or (nx, ny) in seen or (nx, ny) in blocked:
                continue
            c = g[ny][nx]
            if c == "_":
                if dy == 1 and ny + 1 < MAP_H and g[ny + 1][nx] not in SOLID and (nx, ny + 1) not in blocked:
                    seen.add((nx, ny + 1))
                    todo.append((nx, ny + 1))
                continue
            if c in SOLID:
                continue
            seen.add((nx, ny))
            todo.append((nx, ny))
    return seen


def sight(g, x, y, facings, n, blocked) -> set[tuple[int, int]]:
    """The blocks a trainer at (x, y) sees, looking each of ``facings`` (a ledge doesn't stop it, as in the game)."""
    out = set()
    for facing in facings.split():
        dx, dy = STEP[facing]
        for k in range(1, n + 1):
            c = (x + dx * k, y + dy * k)
            if not (0 <= c[0] < MAP_W and 0 <= c[1] < MAP_H) or c in blocked or g[c[1]][c[0]] in SOLID - {"_"}:
                break
            out.add(c)
    return out


def check(g, d) -> None:
    """The route's rules:
    - only Route 24's three ways in open onto the edges;
    - the cottage is reached from the bridge only through the two necks, and neither can be passed unseen: each is
      all in its trainer's sight; past them it is reached;
    - the garden is reached only by cutting the tree in its gate;
    - the trail below is reached from the road down its ledges and from the landing along Route 24's east path, but
      the road can't be reached from it (the ledges are one way);
    - everything walkable is reached from an exit; the cottage's door can be walked into, its sign read."""
    edge = {(x, y) for y in range(MAP_H) for x in range(MAP_W) if x in (0, MAP_W - 1) or y in (0, MAP_H - 1)}
    assert {xy for xy in edge if g[xy[1]][xy[0]] not in SOLID} == set(SOUTH), "only Route 24's ways in open"
    people = {t[:2] for t in TRAINERS.values()} | {CUT_TREE} | set(OTHERS)
    walk = {(x, y) for y in range(MAP_H) for x in range(MAP_W) if g[y][x] not in SOLID} - people
    (door,) = d["H"]
    front = (door[0], door[1] + 1)
    assert front in walk, "the cottage's door can't be walked into"
    for name, col in NECKS.items():
        x, y, facings, n = TRAINERS[name]
        neck = {(col, ny) for ny in range(4, 14) if (col, ny) in walk}  # the meadow's rows (the trail is below)
        assert neck <= sight(g, x, y, facings, n, people), f"{name}'s neck can be passed unseen"
    neck_sight = set().union(*(sight(g, *TRAINERS[name], people) for name in NECKS))
    assert front not in reachable(g, [BRIDGE], people | neck_sight), "the cottage is reached past the necks unseen"
    town = reachable(g, SOUTH, people)
    assert front in town, "the cottage can't be reached"
    garden = reachable(g, [(32, 5)], people)
    assert not garden & town and garden <= reachable(g, SOUTH, people - {CUT_TREE}), "the tree must close the garden"
    trail = (40, 17)
    assert trail in reachable(g, [(36, 13)], people), "the ledges must lead down to the trail"
    from_trail = reachable(g, [trail], people | neck_sight)
    assert (24, 15) in from_trail and not {(36, 13), front} & from_trail, "the trail must lead back west only"
    assert walk <= town | garden, f"blocks you can't reach: {sorted(walk - town - garden)[:8]}"
    for y in range(MAP_H):
        for x in range(MAP_W):
            if g[y][x] == "S":
                assert (x, y + 1) in walk, f"the sign at ({x},{y}) can't be read"


def main() -> None:
    g = plan()
    d = doors(g)
    cliffs.layout(g)
    kit.check_forest(g)
    kit.check_water(g)
    check(g, d)
    base = kit.primary(HERE)  # the kit: the primary tileset every map shares
    spec_mt = list(base["metatiles"])
    rock = kit.Sheet("rock_cliff", cliffs.PAL, CLIFF_BANK, HERE, HERE)
    char_of = cliffs.add(rock, g, extras=())
    spec_mt += rock.write()
    sh = kit.Sheet(COTTAGE.name, COTTAGE.palette, HOUSE_BANK, HERE, HERE, cols=COTTAGE.idx.shape[1] // 16)
    sh.add(COTTAGE.name, COTTAGE.idx, tileset="secondary", **COTTAGE.entry())
    spec_mt += sh.write()
    for e in spec_mt:  # sheets put "w"/"h" on everything; drop the 1x1 ones for readability
        if e["w"] == 1 and e["h"] == 1:
            del e["w"], e["h"]
    kit.write_palette(HERE / f"palette_{CLIFF_BANK}.pal", cliffs.PAL)
    kit.write_palette(HERE / f"palette_{HOUSE_BANK}.pal", COTTAGE.palette)
    spec = {"version": "hns", "primary": kit.PRIMARY, "secondary": SECONDARY,
            "palettes": {"primary": base["palettes"],
                         "secondary": [f"palette_{CLIFF_BANK}.pal", base["secondary_palettes"][8],
                                       f"palette_{HOUSE_BANK}.pal"]},
            "reserve": {"primary": base["reserve"]},
            "animations": base["animations"],
            "field_effects": base["field_effects"],
            "metatiles": spec_mt}
    (HERE / "spec.json").write_text(json.dumps(spec, indent=1) + "\n")
    (HERE / "grid.txt").write_text("".join("".join(r) + "\n" for r in g))
    (HERE / "border.txt").write_text("TT\nTT\n")
    legend = dict(kit.LEGEND, H=COTTAGE.name)
    assert "H" not in cliffs.legend(char_of), "the cottage's letter is one of the cliffs'"
    legend.update(cliffs.legend(char_of))
    legend["d"] = {"auto": "dock", "joins": ":"}  # the road runs onto the bridge's planks without an edge between
    (HERE / "legend.json").write_text(json.dumps(legend, indent=1) + "\n")
    (HERE / "doors.json").write_text(json.dumps(d, indent=1) + "\n")
    print(f"{len(spec_mt)} metatiles in the spec; grid {MAP_W}x{MAP_H}; doors {d}")


if __name__ == "__main__":
    main()
