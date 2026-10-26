#!/usr/bin/env python3
"""Route 17 after its concept (draw_plan.py and plan_stage1.txt): Cycling Road, the downhill run from Route 16's
heights to Route 18's shore (see draw_plan.py). It is 36x120 blocks (old Route 17 was 33x158); its joins: Route 16's
road down (its columns 12-17) at the top edge, the same columns (offset 0), and Route 18's road (its columns 8-16)
below the bottom edge, at columns 14-22 (offset 6, as before).

The pieces: the kit's, and the track drawn here (route17_track.py) in its own palette (bank 7), every piece a slope
the bike runs down by itself. Bank 8 is the kit's plants palette; 9-12 stay free for the seam to old Route 18,
whose strip in this route (the bottom seven rows) is sea, fences and cobblestones only.

Run from the repository root:  python3 project/art/route17-concept/make_art.py
It writes sheets/, the palette, spec.json, grid.txt, border.txt and legend.json next to itself; build.sh turns them
into the game's tileset and map with pae.
"""
import json
import sys
from collections import deque
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "kit"))
sys.path.insert(0, str(Path(__file__).resolve().parent))
import autotile
import kit
import route17_track

HERE = Path(__file__).resolve().parent
SECONDARY = "gTileset_Route17Concept"
MAP_W, MAP_H = 36, 120
TRACK_BANK = 7
NORTH = [(x, 0) for x in range(12, 18)]
SOUTH = [(x, MAP_H - 1) for x in range(14, 23)]
SOLID = set("T#bRoklSBcw_~vrsqQ")
TRACK = {"t": None, "i": "line", "a": "arrow", "x": "check"}  # the track's characters, and their paint
SLOPE = "MB_CYCLING_ROAD_PULL_DOWN"
# the people: the bikers (local ids 0-9), where they stand, which ways they look and how far (those who walk up and
# down or round look a block ahead, whichever way they face), and the Pokémon about (10-12)
ROUND = ("NESW", 1)
BIKERS = [(13, 24, ROUND), (22, 30, ROUND), (4, 48, ROUND), (21, 42, ROUND), (8, 50, ("EW", 5)), (12, 70, ("E", 4)),
          (23, 72, ("W", 3)), (13, 88, ROUND), (31, 91, ROUND), (21, 98, ROUND)]
MIDDLE = (16, 19)        # the middle lane's columns: in no biker's sight from the start line to the lagoon
MONS = [(29, 94), (4, 53), (5, 12)]   # Gulpin (the east rest stop), Grimer (the west one), Houndour (the clearing)
# the hidden items (not underfoot: face them and press A), each by a block a rider can stop on
HIDDEN = {"rare_candy": (31, 13), "full_restore": (2, 54), "pp_up": (33, 86), "max_revive": (8, 46),
          "max_elixir": (30, 112)}
STRIP = 7                # the rows of this route old Route 18 draws (and Route 16 draws of its top)


def plan() -> list[list[str]]:
    rows = (HERE / "plan_stage1.txt").read_text().split("\n")[:MAP_H]
    g = [list(r) for r in rows]
    assert len(g) == MAP_H and all(len(r) == MAP_W for r in g), "the plan is 36x120"
    return g


def reachable(g, starts) -> set[tuple[int, int]]:
    seen, todo = set(starts), deque(starts)
    while todo:
        x, y = todo.popleft()
        for n in ((x + 1, y), (x - 1, y), (x, y + 1), (x, y - 1)):
            if 0 <= n[0] < MAP_W and 0 <= n[1] < MAP_H and n not in seen and g[n[1]][n[0]] not in SOLID:
                seen.add(n)
                todo.append(n)
    return seen


def sight(g, x, y, dirs, n) -> set[tuple[int, int]]:
    out = set()
    for d in dirs:
        dx, dy = {"N": (0, -1), "E": (1, 0), "S": (0, 1), "W": (-1, 0)}[d]
        for k in range(1, n + 1):
            c = (x + dx * k, y + dy * k)
            if g[c[1]][c[0]] in SOLID:
                break
            out.add(c)
    return out


def masks(g, chars) -> dict[tuple[int, int], tuple[int, int]]:
    """Each block of ``chars``: its neighbours of the same (1 N, 2 E, 4 S, 8 W) and its inside corners, as pae map
    paint works them out (the track joins the cobblestones; map edges count as the same)."""
    group = set(chars)

    def same(x, y):
        return not (0 <= y < MAP_H and 0 <= x < MAP_W) or g[y][x] in group
    out = {}
    for y in range(MAP_H):
        for x in range(MAP_W):
            if g[y][x] not in chars:
                continue
            m = sum(bit for bit, (dx, dy) in ((1, (0, -1)), (2, (1, 0)), (4, (0, 1)), (8, (-1, 0)))
                    if same(x + dx, y + dy))
            c = sum(bit for bit, (dx, dy), sides in ((1, (1, -1), 3), (2, (1, 1), 6), (4, (-1, 1), 12),
                                                     (8, (-1, -1), 9))
                    if m & sides == sides and not same(x + dx, y + dy))
            out[(x, y)] = (m, c)
    return out


def check(g) -> None:
    """The route's rules: only the two roads open onto the edges; everything walkable is reached from the top; the
    track runs unbroken from the start line to the finish line, every block of it reached; every biker and Pokémon
    stands on open ground, and the middle lane is in no biker's sight from the start line to the lagoon; every sign can be read and every hidden item found from flat ground (not the slope, which
    would carry a rider away); paint is only where the track goes on all round; the strips the neighbours draw are
    their kinds of ground only (Route 16's: forest and road; old Route 18's: sea, fences and cobblestones)."""
    edge = {(x, y) for y in range(MAP_H) for x in range(MAP_W) if x in (0, MAP_W - 1) or y in (0, MAP_H - 1)}
    assert {xy for xy in edge if g[xy[1]][xy[0]] not in SOLID} == set(NORTH + SOUTH), "only the two roads open"
    walk = {(x, y) for y in range(MAP_H) for x in range(MAP_W) if g[y][x] not in SOLID}
    every = reachable(g, NORTH)
    assert walk <= every, f"blocks you can't reach: {sorted(walk - every)[:8]}"
    assert set(SOUTH) <= every, "the road must run through to Route 18"
    track = {(x, y) for x, y in walk if g[y][x] in TRACK}
    rows = sorted({y for _, y in track})
    assert rows == list(range(rows[0], rows[-1] + 1)), "the track must run unbroken"
    assert all(g[rows[0]][x] == "x" for x in range(12, 24)) and all(g[rows[-1]][x] == "x" for x in range(12, 24)), \
        "the track starts and finishes at its chequered lines"
    flat = walk - track
    for x, y, _ in BIKERS:
        assert (x, y) in walk, f"the biker at ({x},{y}) stands on open ground"
    seen = set().union(*(sight(g, x, y, *look) for x, y, look in BIKERS))
    lagoon = min(y for y in range(MAP_H) if g[y][MIDDLE[0]] == "#")
    middle = {(x, y) for x in range(MIDDLE[0], MIDDLE[1] + 1) for y in range(rows[0], lagoon)}
    assert not seen & middle, f"the middle lane is in a biker's sight at {sorted(seen & middle)[:4]}"
    for x, y in MONS:
        assert (x, y) in flat, f"the Pokémon at ({x},{y}) stands on flat ground"
    for y in range(MAP_H):
        for x in range(MAP_W):
            if g[y][x] == "S":
                assert (x, y + 1) in flat, f"the sign at ({x},{y}) must be read from flat ground"
    for name, (x, y) in HIDDEN.items():
        assert (x, y) in flat, f"{name}: hidden on flat ground"
        assert any(n in flat for n in ((x + 1, y), (x - 1, y), (x, y + 1), (x, y - 1))), f"{name} can't be found"
    m = masks(g, set(TRACK) | {"="})
    for (x, y), (mask, corners) in m.items():
        if g[y][x] in ("i", "a"):
            assert mask == 15 and not corners, f"paint at ({x},{y}) must be where the track goes on all round"
    top = {g[y][x] for y in range(STRIP) for x in range(MAP_W)}
    bottom = {g[y][x] for y in range(MAP_H - STRIP, MAP_H) for x in range(MAP_W)}
    assert top <= {"T", "="} and bottom <= {"s", "#", "="}, f"the strips: {top}, {bottom}"


def track_pieces(g) -> list[tuple[str, object]]:
    """The track's pieces: one per way it goes on, its inside corners and the paint the plan has."""
    out = [(f"track#{m}", route17_track.piece(m)) for m in range(16)]
    m = masks(g, set(TRACK) | {"="})
    done = set()
    for (x, y), (mask, corners) in sorted(m.items()):
        mark = TRACK.get(g[y][x])
        if g[y][x] == "=":
            continue
        name = f"track#{mask}" + (f"+{mark}" if mark else f".{corners}" if corners else "")
        if (mark or corners) and name not in done:
            done.add(name)
            out.append((name, route17_track.piece(mask, 0 if mark else corners, mark)))
    return out


def main() -> None:
    g = plan()
    kit.check_forest(g)
    kit.check_water(g)
    kit.check_paving(g)
    check(g)
    base = kit.primary(HERE)  # the kit: the primary tileset every map shares
    spec_mt = list(base["metatiles"])
    sh = kit.Sheet("track", route17_track.PAL, TRACK_BANK, HERE, HERE)
    for name, idx in track_pieces(g):
        sh.add(name, idx, tileset="secondary", behavior=SLOPE)
    spec_mt += sh.write()
    for e in spec_mt:  # sheets put "w"/"h" on everything; drop the 1x1 ones for readability
        if e["w"] == 1 and e["h"] == 1:
            del e["w"], e["h"]
    kit.write_palette(HERE / f"palette_{TRACK_BANK}.pal", route17_track.PAL)
    spec = {"version": "hns", "primary": kit.PRIMARY, "secondary": SECONDARY,
            "palettes": {"primary": base["palettes"],
                         "secondary": [f"palette_{TRACK_BANK}.pal", base["secondary_palettes"][8]]},
            "reserve": {"primary": base["reserve"]},
            "animations": base["animations"],
            "field_effects": base["field_effects"],
            "metatiles": spec_mt}
    (HERE / "spec.json").write_text(json.dumps(spec, indent=1) + "\n")
    (HERE / "grid.txt").write_text("".join("".join(r) + "\n" for r in g))
    (HERE / "border.txt").write_text("ss\nss\n")
    legend = dict(kit.LEGEND)
    for c, mark in TRACK.items():
        legend[c] = {"auto": "track", "joins": "="} | ({"with": mark} if mark else {})
    (HERE / "legend.json").write_text(json.dumps(legend, indent=1) + "\n")
    print(f"{len(spec_mt)} metatiles in the spec ({len(sh.cells)} track pieces); grid {MAP_W}x{MAP_H}")


if __name__ == "__main__":
    main()
