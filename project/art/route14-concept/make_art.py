#!/usr/bin/env python3
"""Route 14 after its concept (draw_plan.py and plan_stage1.txt): down the coast from Route 13 to where Route 15
turns west for Fuchsia (see draw_plan.py). It is 26x62 blocks, as before; its joins: Route 13's path (its columns
20-22) at the top edge, columns 16-19 (offset -4, as before), and Route 15's low road (its rows 14-17) at the left
edge, rows 50-53 (offset 36, was 37: the road moved a row up to sit on the forest's grid).

The pieces are all the kit's: the route has nothing of its own. Bank 7 is left empty and 9-12 free for the seam to
old Route 13, whose strip in this route (the top seven rows) was forest and dirt only (Route 13 is the kit's now).

Run from the repository root:  python3 project/art/route14-concept/make_art.py
It writes the palette, spec.json, grid.txt, border.txt and legend.json next to itself; build.sh turns them into the
game's tileset and map with pae.
"""
import json
import sys
from collections import deque
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "kit"))
import kit

HERE = Path(__file__).resolve().parent
SECONDARY = "gTileset_Route14Concept"
MAP_W, MAP_H = 26, 62
NORTH = [(x, 0) for x in range(16, 20)]
WEST = [(0, y) for y in range(50, 54)]
SOLID = set("T#bRoklSBcw_~vrsqQC")  # (ledges, "_", count as walls: they only drop you south)
# the trainers (local ids 1-10, 14-15), where they stand, which ways they look and how far (the wanderers look a
# block round)
ROUND = ("NESW", 1)
TRAINERS = [(4, 28, ("E", 2)), (15, 31, ROUND), (2, 17, ("E", 4)), (19, 23, ("N", 3)), (4, 38, ("E", 2)),
            (14, 52, ("E", 2)), (16, 15, ("EW", 1)), (2, 12, ("E", 1)), (5, 44, ("NS", 1)), (13, 45, ROUND),
            (12, 49, ("S", 1)), (13, 49, ("S", 1))]
# the trees to cut (local ids 11-13): the maze's short cut, the dell's way in, the berry garden's way in
CUT = [(19, 16), (15, 42), (12, 54)]
MONS = [(18, 42)]           # the Shroomish, in the dell
SIGNS = [(15, 8)]
HIDDEN = [(21, 9), (15, 56)]  # the Zinc by the shore at the maze's start, the Pinap Berry in the berry garden
STRIP = 7                   # the rows of this route old Route 13 draws


def plan() -> list[list[str]]:
    rows = (HERE / "plan_stage1.txt").read_text().split("\n")[:MAP_H]
    g = [list(r) for r in rows]
    assert len(g) == MAP_H and all(len(r) == MAP_W for r in g), "the plan is 26x62"
    return g


def reachable(g, starts, cut=True) -> set[tuple[int, int]]:
    """Blocks you can walk to from ``starts``; with ``cut`` False the trees to cut stand in the way."""
    block = set() if cut else set(CUT)
    seen, todo = set(starts), deque(starts)
    while todo:
        x, y = todo.popleft()
        for n in [(x + 1, y), (x - 1, y), (x, y + 1), (x, y - 1)]:
            if not (0 <= n[0] < MAP_W and 0 <= n[1] < MAP_H) or n in seen:
                continue
            if g[n[1]][n[0]] in SOLID or n in block:
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
            if g[c[1]][c[0]] in SOLID or c in CUT:
                break
            out.add(c)
    return out


def check(g) -> None:
    """The route's rules: only Route 13's path and Route 15's road open onto the edges; everything walkable is
    reached from Route 13's side; without cutting, Route 15's road is still reached (the maze's short cut is only a
    short cut), but the dell and the berry garden aren't; the trees stand more than 8 blocks from the edges you come
    in by (KR-45: Route 13's at the top, Route 15's at the left); every trainer, Pokémon and tree stands on open
    ground and each trainer sees some of the way; the signs can be read and the hidden items are on open ground; the
    top seven rows, which old Route 13 drew, are forest and dirt only (kept from then)."""
    edge = {(x, y) for y in range(MAP_H) for x in range(MAP_W) if x in (0, MAP_W - 1) or y in (0, MAP_H - 1)}
    assert {xy for xy in edge if g[xy[1]][xy[0]] not in SOLID} == set(NORTH + WEST), "only the two roads open"
    walk = {(x, y) for y in range(MAP_H) for x in range(MAP_W) if g[y][x] not in SOLID}
    every = reachable(g, NORTH)
    assert walk <= every and set(WEST) <= every, f"blocks you can't reach: {sorted(walk - every)[:8]}"
    uncut = reachable(g, NORTH, cut=False)
    assert set(WEST) <= uncut, "the way south needs no tree cut"
    assert (18, 42) not in uncut and (12, 57) not in uncut, "the dell and the garden are behind their trees"
    assert (19, 17) in uncut, "the maze's short cut is only a short cut"
    for x, y in CUT:
        assert x > 8 and y > 6, f"the game would hide the tree at ({x},{y}) (KR-45)"
    people = [(x, y) for x, y, _ in TRAINERS] + MONS
    assert len(set(people + CUT)) == len(people + CUT), "two events on one block"
    for x, y, look in TRAINERS:
        assert (x, y) in walk, f"the trainer at ({x},{y}) stands on open ground"
        assert sight(g, x, y, *look) - set(people), f"the trainer at ({x},{y}) sees nothing"
    assert all(xy in walk for xy in MONS + CUT + HIDDEN), "the Pokémon, trees and hidden items on open ground"
    for x, y in SIGNS:
        assert g[y][x] == "S" and (x, y + 1) in walk, f"the sign at ({x},{y}) can't be read"
    strip = {g[y][x] for y in range(STRIP) for x in range(MAP_W)}
    assert strip <= set("T:"), f"old Route 13's strip: {strip}"


def main() -> None:
    g = plan()
    kit.check_forest(g)
    kit.check_water(g)
    kit.check_paving(g)
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
    (HERE / "border.txt").write_text("ss\nss\n")
    # the pier's planks run on from the crossroads' dirt with no lawn strip between (the dock edges only on the sea)
    (HERE / "legend.json").write_text(json.dumps(dict(kit.LEGEND, d={"auto": "dock", "joins": ":"}), indent=1) + "\n")
    print(f"{len(spec_mt)} metatiles in the spec; grid {MAP_W}x{MAP_H}")


if __name__ == "__main__":
    main()
