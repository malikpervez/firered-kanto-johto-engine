#!/usr/bin/env python3
"""Route 21 after its concept (draw_plan.py, plan_north.txt and plan_south.txt): the sea route south from Pallet Town
to Cinnabar Island, in two maps of 24x50 blocks (see draw_plan.py). Their joins stay where they were: Pallet's river
at the top of the north map (columns 7-10, offset -11), the two maps across their whole width, Cinnabar below the
south map (offset 0).

The pieces are the kit's only, so the two maps share one secondary tileset, which holds nothing of its own.

Run from the repository root:  python3 project/art/route21-concept/make_art.py
It writes the palette, spec.json, grid_north.txt, grid_south.txt, border.txt and legend.json next to itself; build.sh turns them
into the game's tileset and maps with pae.
"""
import json
import sys
from collections import deque
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "kit"))
import kit

HERE = Path(__file__).resolve().parent
SECONDARY = "gTileset_Route21Concept"
MAP_W, MAP_H = 24, 50
WATER = set("s~")
SOLID = set("T#bRoklSBcw_~vrsqQ")
RIVER = [(x, 0) for x in range(7, 11)]           # Pallet's river, at the north map's top
LANE = [(x, MAP_H - 1) for x in range(0, 4)]      # the sea lane down Cinnabar's west side, at the south map's foot
ROUND = ("NESW", 1)
# the people and the Pokémon: where they are, which ways they look and how far, in the water or on land
NORTH = {"water": [(12, 44, ("NESW", 4)), (14, 35, ("S", 3)), (15, 35, ("S", 3)), (20, 38, ROUND)],
         "land": [(6, 25, ("N", 3)), (16, 29, ("S", 3)), (19, 3, ("W", 2)), (4, 11, ROUND), (19, 7, ROUND)]}
SOUTH = {"water": [(15, 24, ("EW", 3)), (15, 38, ("W", 3)), (10, 29, ROUND)],
         "land": [(15, 8, ("E", 3)), (8, 15, ("W", 3))]}
PEARL = (18, 41)                                 # hidden on the north map's sandbar


def plan(name: str) -> list[list[str]]:
    rows = (HERE / f"plan_{name}.txt").read_text().split("\n")[:MAP_H]
    g = [list(r) for r in rows]
    assert len(g) == MAP_H and all(len(r) == MAP_W for r in g), "each plan is 24x50"
    return g


# the woods' cells at the south map's foot drawn as named forest pieces (top-left block -> character), and the pieces
FOOT = {(14, 48): "5", (16, 48): "1", (18, 48): "2", (20, 48): "3", (22, 48): "4"}
FOOT_PIECE = {"1": "forest#11", "2": "forest#11~1", "3": "forest#11~2", "4": "forest#11", "5": "forest#15.2"}


def reachable(g, starts, surf=False) -> set[tuple[int, int]]:
    seen, todo = set(starts), deque(starts)
    while todo:
        x, y = todo.popleft()
        for n in ((x + 1, y), (x - 1, y), (x, y + 1), (x, y - 1)):
            if not (0 <= n[0] < MAP_W and 0 <= n[1] < MAP_H) or n in seen:
                continue
            c = g[n[1]][n[0]]
            if c in SOLID and not (surf and c in WATER):
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
            if ch in SOLID and not (water and ch in WATER):
                break
            out.add(c)
    return out


def check(n, s) -> None:
    """The route's rules: from Pallet's river, by Surf, every beach, islet and sandbar of both maps is reached, and the
    lane to Cinnabar; on foot, nothing leaves either map but the north map's river banks under Pallet's woods (the
    woods stop them); the south map's foot is woods and sea only, Cinnabar's town island behind it; the swimmers and
    Corphish are in the water, the fishers and the meadows' Pokémon on land, each sees some of the way (the fishers
    out over the water); the Pearl is on the sandbar; both maps have tall grass (the route has land encounters)."""
    both = n + s  # the south map stacked under the north, as the join puts them
    walk = {(x, y) for y in range(2 * MAP_H) for x in range(MAP_W) if both[y][x] not in SOLID}
    surf = {(x, y) for y in range(2 * MAP_H) for x in range(MAP_W)
            if both[y][x] in WATER or both[y][x] not in SOLID}
    seen, todo = set(RIVER), deque(RIVER)
    while todo:
        x, y = todo.popleft()
        for c in ((x + 1, y), (x - 1, y), (x, y + 1), (x, y - 1)):
            if c in surf and c not in seen:
                seen.add(c)
                todo.append(c)
    assert walk <= seen, f"blocks you can't reach: {sorted(walk - seen)[:8]}"
    assert all((x, y + MAP_H) in seen for x, y in LANE), "the lane to Cinnabar"
    top = {(x, 0) for x in range(MAP_W)} & walk
    assert top <= {(6, 0), (11, 0)}, f"land at the top: {sorted(top)}"
    assert not {(x, 2 * MAP_H - 1) for x in range(MAP_W)} & walk, "land at the foot"
    assert set(s[MAP_H - 1][4:]) == {"T"} and set(s[MAP_H - 1][:4]) == {"s"}, "Cinnabar's woods and its lane"
    for g, people in ((n, NORTH), (s, SOUTH)):
        spots = [(x, y) for x, y, _ in people["water"] + people["land"]]
        assert len(set(spots)) == len(spots), "two on one block"
        for x, y, look in people["water"]:
            assert g[y][x] == "s" and sight(g, x, y, *look, True), f"({x},{y}) in the water"
        for x, y, look in people["land"]:
            assert g[y][x] not in SOLID and sight(g, x, y, *look, True), f"({x},{y}) on land"
        assert any("g" in r for r in g), "tall grass"
    assert n[PEARL[1]][PEARL[0]] == ".", "the Pearl on the sandbar"


def main() -> None:
    n, s = plan("north"), plan("south")
    for g in (n, s):
        kit.check_forest(g)
        kit.check_water(g)
    check(n, s)
    base = kit.primary(HERE)  # the kit: the primary tileset every map shares
    spec_mt = list(base["metatiles"])
    for e in spec_mt:  # sheets put "w"/"h" on everything; drop the 1x1 ones for readability
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
    (HERE / "grid_north.txt").write_text("".join("".join(r) + "\n" for r in n))
    # the woods at the south map's foot end over Cinnabar's lawn above its Gym (Cinnabar's columns 16-23): there their
    # cells show trunks on grass (no forest south), and the cell beside them, whose woods go on into Cinnabar's, turns
    # an inside corner; pae counts off the map as more forest, so these are named (part of the forest for the rest)
    for (x0, y0), ch in FOOT.items():
        for dx in (0, 1):
            for dy in (0, 1):
                assert s[y0 + dy][x0 + dx] == "T", f"the woods' foot at ({x0},{y0})"
                s[y0 + dy][x0 + dx] = ch
    (HERE / "grid_south.txt").write_text("".join("".join(r) + "\n" for r in s))
    (HERE / "border.txt").write_text("ss\nss\n")
    # Pallet's river runs out into the sea: one water with it, so neither draws a shore across the mouth
    legend = dict(kit.LEGEND, **{"~": {"auto": "pond", "joins": "s", "elevation": 1}})
    legend.update({ch: {"name": FOOT_PIECE[ch], "joins": "T"} for ch in FOOT.values()})
    (HERE / "legend.json").write_text(json.dumps(legend, indent=1) + "\n")
    print(f"{len(spec_mt)} metatiles in the spec; two grids {MAP_W}x{MAP_H}")


if __name__ == "__main__":
    main()
