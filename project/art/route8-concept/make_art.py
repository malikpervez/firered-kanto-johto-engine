#!/usr/bin/env python3
"""Route 8 after its concept (draw_plan.py and plan_stage1.txt): the road west from Lavender to Saffron's east gate
(see draw_plan.py). It is 60x30 blocks (old Route 8 was 68x40); its joins: Lavender's street the right edge at rows
13-15 (Lavender's 9-11, offset 4), Saffron beyond the left edge (offset -15), whose gate door (Saffron row 27) is
level with the gate's door here (row 12), as it was with the old route's (row 21, offset -6).

The pieces: the kit's, Viridian's pond keeper's house (the Underground Path's hut) in Viridian's houses' palette
(bank 9), and Route 2's south forest gate (Saffron's gate) in its own palette (bank 7). Bank 8 is the kit's plants
palette; 10-12 stay free for the seam to Lavender (from the kit: it needs none).

Run from the repository root:  python3 project/art/route8-concept/make_art.py
It writes sheets/, the palettes, spec.json, grid.txt, border.txt, legend.json and doors.json next to itself;
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
import kit

HERE = Path(__file__).resolve().parent
ART = HERE.parent
SECONDARY = "gTileset_Route8Concept"
MAP_W, MAP_H = 60, 30
GATE_BANK, HOUSE_BANK = 7, 9
EAST = [(MAP_W - 1, y) for y in range(13, 16)]
SOLID = set("T#bRoklSBcw_~vrUF")
# the buildings: their letters in the plan, their packs, their banks, and what their doors do (the gate's two open
# together)
BUILDINGS = {"U": (ART / "viridian-concept/buildings/house_pond_keeper", HOUSE_BANK, ["MB_ANIMATED_DOOR"]),
             "F": (ART / "route2-concept/buildings/forest_gate_south", GATE_BANK,
                   ["MB_ANIMATED_DOOR", "MB_ANIMATED_DOOR"])}
TREES = [(36, 9), (46, 23)]  # the trees to cut: the berry garden's gap, the meadow's
GARDEN = {(x, y) for y in range(6, 9) for x in range(31, 41)}
MEADOW = {(x, y) for y in range(24, 28) for x in range(37, 58)}
# the trainers the plan is made for (build.sh places them so): (x, y, the ways they look, sight). Rich and Stan watch
# the race over the rail (the bushes stop their sight: you talk to them); none of them sees the road
TRAINERS = {"Julia": (55, 19, "left", 6), "Rich": (23, 6, "right", 3), "Glenn": (44, 20, "up down left right", 4),
            "Paige": (29, 19, "left", 3), "Leslie": (29, 20, "right", 6), "Andrea": (29, 21, "left", 3),
            "Megan": (29, 22, "right", 6), "Stan": (23, 8, "up down left right", 1),
            "Aidan": (8, 21, "right", 4), "Eli": (51, 9, "down", 1), "Anne": (52, 9, "down", 1)}
# the bikers ride the track's outer edge round and round, clockwise (sight 1 whichever way they face); a walker's
# range is at most 15 each way, so the loop is 16x9
LOOP = ({(x, y) for x in range(28, 44) for y in (3, 11)} | {(x, y) for y in range(3, 12) for x in (28, 43)})
BIKERS = {"Ricardo": (28, 3), "Jaren": (43, 11)}
ROAD = {(x, y) for y in range(13, 16) for x in range(7, MAP_W)}
STEP = {"left": (-1, 0), "right": (1, 0), "up": (0, -1), "down": (0, 1)}


def load(letter: str) -> tuple[buildings.Building, list[tuple[int, int]]]:
    """A building and its doors (``door_blocks``, or the older packs' one ``door_block``)."""
    folder = BUILDINGS[letter][0]
    meta = json.loads((folder / f"{folder.name}.json").read_text())
    with Image.open(folder / f"{folder.name}.png") as im:
        idx, flat = np.array(im, np.uint8), im.getpalette()[:48]
    ds = [tuple(d) for d in meta["door_blocks"]] if "door_blocks" in meta else [tuple(meta["door_block"])]
    return buildings.Building(folder.name, idx, [tuple(flat[i:i + 3]) for i in range(0, 48, 3)], ds[0],
                              folder / f"{folder.name}_door.png"), ds


def plan() -> list[list[str]]:
    rows = (HERE / "plan_stage1.txt").read_text().split("\n")[:MAP_H]
    g = [list(r) for r in rows]
    assert len(g) == MAP_H and all(len(r) == MAP_W for r in g), "the plan is 60x30"
    return g


def doors(g) -> dict[str, list[tuple[int, int]]]:
    out = {}
    for letter in BUILDINGS:
        b, ds = load(letter)
        bw, bh = b.idx.shape[1] // 16, b.idx.shape[0] // 16
        cells = {(x, y) for y, r in enumerate(g) for x, c in enumerate(r) if c == letter}
        x0, y0 = min(cells)
        assert cells == {(x0 + i, y0 + j) for i in range(bw) for j in range(bh)}, f"{letter} isn't its footprint"
        out[letter] = [(x0 + dx, y0 + dy) for dx, dy in ds]
    return out


def reachable(g, starts, blocked=frozenset()) -> set[tuple[int, int]]:
    seen, todo = set(starts), deque(starts)
    while todo:
        x, y = todo.popleft()
        for n in ((x + 1, y), (x - 1, y), (x, y + 1), (x, y - 1)):
            if not (0 <= n[0] < MAP_W and 0 <= n[1] < MAP_H) or n in seen or n in blocked:
                continue
            if g[n[1]][n[0]] in SOLID:
                continue
            seen.add(n)
            todo.append(n)
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


def check(g, d) -> None:
    """The route's rules: only Lavender's street opens onto the edges (the gate is a building, Saffron reached through
    it); no block you can walk to is within 7 of the left edge (the camera would show old Saffron, which has no seam);
    the trees close the berry garden and the meadow, and with them cut everything walkable is reached; they stand more
    than 8 blocks from the right edge; the road from Lavender to the gate is all cobbles and in no trainer's sight
    (the bikers', round their whole loop, included); every door can be walked into from below, the sign read."""
    edge = {(x, y) for y in range(MAP_H) for x in range(MAP_W) if x in (0, MAP_W - 1) or y in (0, MAP_H - 1)}
    assert {xy for xy in edge if g[xy[1]][xy[0]] not in SOLID} == set(EAST), "only Lavender's street opens"
    people = {t[:2] for t in TRAINERS.values()} | set(BIKERS.values())
    walk = {(x, y) for y in range(MAP_H) for x in range(MAP_W) if g[y][x] not in SOLID}
    assert min(x for x, _ in walk) >= 7, "a block within 7 of the left edge: old Saffron would show"
    closed = reachable(g, EAST, people | set(TREES))
    assert not closed & (GARDEN | MEADOW), "the trees must close the garden and the meadow"
    every = reachable(g, EAST, people)
    assert walk - people <= every, f"blocks you can't reach: {sorted(walk - people - every)[:8]}"
    assert all(x < MAP_W - 9 for x, _ in TREES), "the game would hide a tree near Lavender's edge"
    assert LOOP <= {xy for xy in walk if g[xy[1]][xy[0]] == ":"}, "the bikers' loop isn't all track"
    assert all(g[y][x] == "=" for x, y in ROAD), "the road isn't all cobbles"
    seen = set().union(*(sight(g, *t) for t in TRAINERS.values()))
    seen |= set().union(*(sight(g, x, y, "up down left right", 1) for x, y in LOOP))
    assert not ROAD & seen, f"the road is in a trainer's sight at {sorted(ROAD & seen)[:4]}"
    for letter in BUILDINGS:
        for x, y in d[letter]:
            assert (x, y + 1) in every, f"the door of {letter} at ({x},{y}) can't be walked into"
    for y in range(MAP_H):
        for x in range(MAP_W):
            if g[y][x] == "S":
                assert (x, y + 1) in every, f"the sign at ({x},{y}) can't be read"


def main() -> None:
    g = plan()
    d = doors(g)
    kit.check_forest(g)
    kit.check_water(g)
    check(g, d)
    base = kit.primary(HERE)  # the kit: the primary tileset every map shares
    spec_mt = list(base["metatiles"])
    pals = {}
    for letter, (folder, bank, behaviors) in BUILDINGS.items():
        b, ds = load(letter)
        pals.setdefault(bank, b.palette)
        assert pals[bank] == b.palette, f"{b.name}: its palette isn't the one bank {bank} has"
        bw, bh = b.idx.shape[1] // 16, b.idx.shape[0] // 16
        open_, behavior = [], {}
        for (dx, dy), mb in zip(ds, behaviors):
            open_.append(f"{dx},{dy}")
            behavior[f"{dx},{dy}"] = mb
        sh = kit.Sheet(b.name, b.palette, bank, HERE, HERE, cols=bw)
        sh.add(b.name, b.idx, tileset="secondary", ground="grass", solid=True, open=open_, behaviors=behavior)
        spec_mt += sh.write()
    for e in spec_mt:  # sheets put "w"/"h" on everything; drop the 1x1 ones for readability
        if e["w"] == 1 and e["h"] == 1:
            del e["w"], e["h"]
    for bank, pal in pals.items():
        kit.write_palette(HERE / f"palette_{bank}.pal", pal)
    spec = {"version": "hns", "primary": kit.PRIMARY, "secondary": SECONDARY,
            "palettes": {"primary": base["palettes"],
                         "secondary": [f"palette_{GATE_BANK}.pal", base["secondary_palettes"][8],
                                       f"palette_{HOUSE_BANK}.pal"]},
            "reserve": {"primary": base["reserve"]},
            "animations": base["animations"],
            "field_effects": base["field_effects"],
            "metatiles": spec_mt}
    (HERE / "spec.json").write_text(json.dumps(spec, indent=1) + "\n")
    (HERE / "grid.txt").write_text("".join("".join(r) + "\n" for r in g))
    (HERE / "border.txt").write_text("TT\nTT\n")
    legend = dict(kit.LEGEND, **{k: load(k)[0].name for k in BUILDINGS})
    (HERE / "legend.json").write_text(json.dumps(legend, indent=1) + "\n")
    (HERE / "doors.json").write_text(json.dumps(d, indent=1) + "\n")
    print(f"{len(spec_mt)} metatiles in the spec; grid {MAP_W}x{MAP_H}; doors {d}")


if __name__ == "__main__":
    main()
