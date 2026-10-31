#!/usr/bin/env python3
"""Route 19 after its concept (draw_plan.py and plan_stage1.txt): the sea route south from Fuchsia (see draw_plan.py).
It is 24x60 blocks, as before; its joins stay where they were: Fuchsia's beach path (its columns 18-29) at the top
edge, columns 6-17 (offset -12), and Route 20's sea (its rows 0-18) at the left edge, rows 41-59 (offset 41).

The pieces are all the kit's: the route has nothing of its own. The sea is the kit's, surfable.

Run from the repository root:  python3 project/art/route19-concept/make_art.py
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
SECONDARY = "gTileset_Route19Concept"
MAP_W, MAP_H = 24, 60
NORTH = [(x, 0) for x in range(6, 18)]  # (Fuchsia's path: 12 wide, its columns 18-29)
WEST = [(0, y) for y in range(41, 60)]
SOLID = set("T#bRoklSBcw_~vrsqQ")  # (the sea, "s", is walked on only by Surf)
SEA = "s"
# the swimmers (local ids 1-12): the two resting on the beach (they look along it), the rest in the water; where
# they are, which ways they look and how far (the lookers-about look round)
ROUND = ("NESW", 1)
ON_LAND = [(6, 8, ("E", 3)), (17, 8, ("W", 3))]
IN_WATER = [(12, 18, ("NESW", 3)), (18, 33, ROUND), (8, 29, ROUND), (16, 22, ("EW", 6)), (11, 47, ROUND),
            (14, 48, ROUND), (12, 49, ROUND), (9, 48, ROUND), (8, 41, ("S", 1)), (9, 41, ("S", 1))]
WINGULL = (8, 54)
SIGNS = [(12, 4)]
ISLETS = [(15, 29), (4, 52)]


def plan() -> list[list[str]]:
    rows = (HERE / "plan_stage1.txt").read_text().split("\n")[:MAP_H]
    g = [list(r) for r in rows]
    assert len(g) == MAP_H and all(len(r) == MAP_W for r in g), "the plan is 24x60"
    return g


def reachable(g, starts, surf=False) -> set[tuple[int, int]]:
    """Blocks you can reach from ``starts``, walking, or walking and surfing."""
    seen, todo = set(starts), deque(starts)
    while todo:
        x, y = todo.popleft()
        for n in [(x + 1, y), (x - 1, y), (x, y + 1), (x, y - 1)]:
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


def check(g) -> None:
    """The route's rules: on foot, only Fuchsia's path opens onto an edge, and the beach and the jetty are reached
    from it; by Surf, the islets and Route 20's sea (the left edge, rows 41-59) are reached too, and the sea touches
    no other edge but the open ones and the border; the swimmers on the beach stand on open ground, those in the
    water are in it, and each sees some of the way; the Wingull is on its island; the sign can be read."""
    walk = {(x, y) for y in range(MAP_H) for x in range(MAP_W) if g[y][x] not in SOLID}
    edge_walk = {(x, y) for x, y in walk if x in (0, MAP_W - 1) or y in (0, MAP_H - 1)}
    assert edge_walk == set(NORTH), f"only Fuchsia's path opens: {sorted(edge_walk - set(NORTH))[:6]}"
    on_foot = reachable(g, NORTH)
    assert (11, 15) in on_foot, "the jetty is reached on foot"
    surfing = reachable(g, NORTH, surf=True)
    assert walk <= surfing, f"blocks you can't reach: {sorted(walk - surfing)[:8]}"
    assert set(WEST) <= surfing and all(g[y][x] == SEA for x, y in WEST), "Route 20's sea is reached by Surf"
    assert all(xy in surfing and xy not in on_foot for xy in ISLETS), "the islets are reached only by Surf"
    people = [(x, y) for x, y, _ in ON_LAND + IN_WATER] + [WINGULL]
    assert len(set(people)) == len(people), "two on one block"
    for x, y, look in ON_LAND:
        assert (x, y) in walk and sight(g, x, y, *look, False) - set(people), f"the swimmer at ({x},{y}) on the beach"
    for x, y, look in IN_WATER:
        assert g[y][x] == SEA and sight(g, x, y, *look, True) - set(people), f"the swimmer at ({x},{y}) in the water"
    assert WINGULL in walk and WINGULL in surfing and WINGULL not in on_foot, "the Wingull on its island"
    for x, y in SIGNS:
        assert g[y][x] == "S" and (x, y + 1) in on_foot, f"the sign at ({x},{y}) can't be read"


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
