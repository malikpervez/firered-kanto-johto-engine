#!/usr/bin/env python3
"""Route 13 after its concept (draw_plan.py and plan_stage1.txt): the coast road west from Silence Bridge, Route
12's boardwalk, to Route 14 (see draw_plan.py). It is 104x32 blocks, as before; its joins stay where they were:
Route 12's boardwalk (its columns 21-24) at the top edge, columns 86-89 (offset 65), and Route 14's way in (its columns
16-19) at the bottom edge, columns 20-23 (offset 4).

The pieces are all the kit's: the route has nothing of its own. Both neighbours are from the kit (Route 12 is rebuilt
with it: old Route 12 had no tile slots left for a seam to it), so no strip has to keep to few palettes.

Run from the repository root:  python3 project/art/route13-concept/make_art.py
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
SECONDARY = "gTileset_Route13Concept"
MAP_W, MAP_H = 104, 32
NORTH = [(x, 0) for x in range(86, 90)]
SOUTH = [(x, MAP_H - 1) for x in range(20, 24)]
SOLID = set("T#bRoklSBcw_~vrsqQC")  # (ledges, "_", count as walls: they only drop you south)
# the trainers (local ids 1-10), where they stand, which ways they look and how far (the wanderers look a block
# round)
ROUND = ("NESW", 1)
TRAINERS = [(66, 23, ROUND), (78, 22, ROUND), (72, 24, ROUND), (61, 15, ("S", 3)), (62, 15, ("S", 3)),
            (45, 17, ("S", 1)), (84, 19, ("W", 3)), (16, 25, ("N", 3)), (12, 19, ("E", 3)), (30, 19, ROUND)]
CUT = [(44, 7)]             # the tree to cut (local id 11): the nook's way in
MONS = [(6, 19), (7, 19), (46, 3)]  # Nidorino and Nidorina face to face, the Seedot in the nook
SIGNS = [(84, 15), (24, 17), (42, 21)]
HIDDEN = [(39, 23)]         # the PP Up, just left of the lamp post


def plan() -> list[list[str]]:
    rows = (HERE / "plan_stage1.txt").read_text().split("\n")[:MAP_H]
    g = [list(r) for r in rows]
    assert len(g) == MAP_H and all(len(r) == MAP_W for r in g), "the plan is 104x32"
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
    """The route's rules: only Route 12's boardwalk and Route 14's way in open onto the edges; everything walkable
    is reached from the boardwalk; without cutting, Route 14 is still reached, but the nook isn't; the upland meadow
    is reached without the ledges; every trainer, Pokémon and tree stands on open ground and each trainer sees some
    of the way; the signs can be read, the hidden item is on open ground just left of the lamp post; the tree stands
    more than 8 blocks from the edges you come in by (KR-45)."""
    edge = {(x, y) for y in range(MAP_H) for x in range(MAP_W) if x in (0, MAP_W - 1) or y in (0, MAP_H - 1)}
    assert {xy for xy in edge if g[xy[1]][xy[0]] not in SOLID} == set(NORTH + SOUTH), "only the two ways open"
    walk = {(x, y) for y in range(MAP_H) for x in range(MAP_W) if g[y][x] not in SOLID}
    every = reachable(g, NORTH)
    assert walk <= every and set(SOUTH) <= every, f"blocks you can't reach: {sorted(walk - every)[:8]}"
    uncut = reachable(g, NORTH, cut=False)
    assert set(SOUTH) <= uncut, "the way to Route 14 needs no tree cut"
    assert (46, 3) not in uncut, "the nook is behind its tree"
    assert (20, 10) in uncut, "the upland meadow is reached without the ledges"
    assert g[22][40] == "l" and g[23][40] == "l" and HIDDEN[0] == (39, 23), "the PP Up is just left of the post"
    people = [(x, y) for x, y, _ in TRAINERS] + MONS
    assert len(set(people + CUT)) == len(people + CUT), "two events on one block"
    for x, y, look in TRAINERS:
        assert (x, y) in walk, f"the trainer at ({x},{y}) stands on open ground"
        assert sight(g, x, y, *look) - set(people), f"the trainer at ({x},{y}) sees nothing"
    assert all(xy in walk for xy in MONS + CUT + HIDDEN), "the Pokémon, trees and hidden items on open ground"
    for x, y in SIGNS:
        assert g[y][x] == "S" and (x, y + 1) in walk, f"the sign at ({x},{y}) can't be read"
    for x, y in CUT:
        assert 6 < y < MAP_H - 7, f"the game would hide the tree at ({x},{y}) (KR-45)"


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
    (HERE / "legend.json").write_text(json.dumps(dict(kit.LEGEND), indent=1) + "\n")
    print(f"{len(spec_mt)} metatiles in the spec; grid {MAP_W}x{MAP_H}")


if __name__ == "__main__":
    main()
