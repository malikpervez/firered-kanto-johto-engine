#!/usr/bin/env python3
"""Vermilion City after its concept (draw_plan.py and plan_stage1.txt): the harbour city (see draw_plan.py). It is
60x42 blocks (old Vermilion was 71x78), and its joins stay where its neighbours meet it: Route 6's road the top at
columns 32-34 (offset -8), Route 11's the right edge at rows 11-14 (its 14-17, offset -3); the S.S. Anne's gangway
is the pier's end (37-39 on the bottom row).

The pieces: the kit's, the Pokémon Center and the Mart (the kit's), Viridian's Gym (every Gym looks the same outside, as
in FireRed) and its Trainer School (the Fan Club) in Viridian's buildings' palette (bank 7), and Viridian's three houses in its houses' palette (bank 9).
Bank 8 is the kit's plants palette; 10-12 stay free for the seam to Route 11 (not rebuilt yet).

Run from the repository root:  python3 project/art/vermilion-concept/make_art.py
It writes sheets/, the palettes, spec.json, grid.txt, border.txt, legend.json and doors.json next to itself;
build.sh turns them into the game's tileset and map with pae.
"""
import json
import sys
from collections import deque
from pathlib import Path

import numpy as np

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "kit"))
import buildings
import kit

HERE = Path(__file__).resolve().parent
ART = HERE.parent
SECONDARY = "gTileset_VermilionConcept"
MAP_W, MAP_H = 60, 42
CITY_BANK, HOUSE_BANK = 7, 9
VB = ART / "viridian-concept/buildings"
# the buildings: their letters in the plan, where each comes from and its palette's bank
OWN = {"K": (VB / "trainer_school", CITY_BANK), "W": (VB / "viridian_gym", CITY_BANK),
       "X": (VB / "house_gardener", HOUSE_BANK), "H": (VB / "house_family", HOUSE_BANK),
       "U": (VB / "house_pond_keeper", HOUSE_BANK)}
SHARED = {"Z": "pokemon_center", "L": "poke_mart"}
CUT_TREE = (15, 15)                            # the tree to cut, in the Gym yard's gate
NORTH = [(x, 0) for x in range(32, 35)]
EAST = [(MAP_W - 1, y) for y in range(11, 15)]
GANGWAY = [(x, MAP_H - 1) for x in range(37, 40)]  # the S.S. Anne's warps, at the pier's end
# the gangway's blocks: the pier's planks (their pieces: open to the pier and off the map's edge) that warp you onto
# the ship as you step on them; the pier joins them
GANGWAY_PIECES = {"J": "dock#7", "G": "dock#15", "Y": "dock#13"}
FERRY = (39, MAP_H - 2)                        # the ferry sailor, his ticket check on 37-38 before him
WATER = set("~vr")
SOLID = set("T#bRoklSBcwO_~vrZLKWXHU")


def plan() -> list[list[str]]:
    rows = (HERE / "plan_stage1.txt").read_text().split("\n")[:MAP_H]
    g = [list(r) for r in rows]
    assert len(g) == MAP_H and all(len(r) == MAP_W for r in g), "the plan is 60x42"
    return g


def load(letter: str) -> buildings.Building:
    if letter in SHARED:
        return kit.SHARED_BUILDINGS[SHARED[letter]][0]
    return buildings.load(OWN[letter][0])


def doors(g) -> dict[str, list[tuple[int, int]]]:
    """Each building's door."""
    out = {}
    for letter in list(SHARED) + list(OWN):
        b = load(letter)
        bw, bh = b.idx.shape[1] // 16, b.idx.shape[0] // 16
        cells = {(x, y) for y, r in enumerate(g) for x, c in enumerate(r) if c == letter}
        x0, y0 = min(cells)
        assert cells == {(x0 + i, y0 + j) for i in range(bw) for j in range(bh)}, f"{letter} isn't its footprint"
        out[letter] = [(x0 + b.door[0], y0 + b.door[1])]
    return out


def reachable(g, starts, blocked=(), surf=False) -> set[tuple[int, int]]:
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


def check(g, d) -> None:
    """The town's rules: only its three ways out open onto the edges (Route 6's road, Route 11's, the S.S. Anne's
    gangway); with the tree standing, the town is everything walkable but the Gym's yard, which the tree opens; the
    pier leads to the gangway, past the ferry sailor's ticket check; every door can be walked into from the block
    below it, every sign read from it; the harbour can be surfed from the promenade."""
    edge = {(x, y) for y in range(MAP_H) for x in range(MAP_W) if x in (0, MAP_W - 1) or y in (0, MAP_H - 1)}
    assert {xy for xy in edge if g[xy[1]][xy[0]] not in SOLID} == set(NORTH + EAST + GANGWAY), "only the ways out"
    people = {CUT_TREE, FERRY}
    town = reachable(g, NORTH, people)
    assert set(EAST + GANGWAY) <= town, "Route 11's road and the gangway must be reached from Route 6's"
    walk = {(x, y) for y in range(MAP_H) for x in range(MAP_W) if g[y][x] not in SOLID} - people
    yard = reachable(g, [(15, 16)], people)
    assert not yard & town and yard <= reachable(g, NORTH, {FERRY}), "the tree must close the Gym's yard"
    assert walk <= town | yard, f"blocks you can't reach: {sorted(walk - town - yard)[:8]}"
    assert all((x, MAP_H - 2) in town for x in (37, 38)), "the ticket check is before the gangway"
    for letter, ds in d.items():
        for x, y in ds:
            assert (x, y + 1) in walk, f"the door of {letter} at ({x},{y}) can't be walked into"
    for y in range(MAP_H):
        for x in range(MAP_W):
            if g[y][x] == "S":
                assert (x, y + 1) in walk, f"the sign at ({x},{y}) can't be read"
    assert (30, 30) in reachable(g, NORTH, people, surf=True), "the harbour must be surfed from the town"


def main() -> None:
    g = plan()
    d = doors(g)
    kit.check_forest(g)
    kit.check_water(g)
    check(g, d)
    base = kit.primary(HERE)  # the kit: the primary tileset every map shares
    spec_mt = list(base["metatiles"])
    pals = {}
    for letter, (folder, bank) in OWN.items():
        b = load(letter)
        pals.setdefault(bank, b.palette)
        if pals[bank] != b.palette:
            raise SystemExit(f"{folder.name}: its palette isn't the one bank {bank} has")
        sh = kit.Sheet(b.name, b.palette, bank, HERE, HERE, cols=b.idx.shape[1] // 16)
        sh.add(b.name, b.idx, tileset="secondary", **b.entry())
        spec_mt += sh.write()
    for (x, y), ch in zip(GANGWAY, GANGWAY_PIECES):
        g[y][x] = ch
    sh = kit.Sheet("gangway", pals[CITY_BANK], CITY_BANK, HERE, HERE, cols=3)
    for ch, ground in GANGWAY_PIECES.items():
        sh.add(f"gangway_{ch}", np.zeros((16, 16), np.uint8), tileset="secondary", ground=ground,
               behavior="MB_DEEP_SOUTH_WARP")
    spec_mt += sh.write()
    for e in spec_mt:  # sheets put "w"/"h" on everything; drop the 1x1 ones for readability
        if e["w"] == 1 and e["h"] == 1:
            del e["w"], e["h"]
    for bank, pal in pals.items():
        kit.write_palette(HERE / f"palette_{bank}.pal", pal)
    spec = {"version": "hns", "primary": kit.PRIMARY, "secondary": SECONDARY,
            "palettes": {"primary": base["palettes"],
                         "secondary": [f"palette_{CITY_BANK}.pal", base["secondary_palettes"][8],
                                       f"palette_{HOUSE_BANK}.pal"]},
            "reserve": {"primary": base["reserve"]},
            "animations": base["animations"],
            "field_effects": base["field_effects"],
            "metatiles": spec_mt}
    (HERE / "spec.json").write_text(json.dumps(spec, indent=1) + "\n")
    (HERE / "grid.txt").write_text("".join("".join(r) + "\n" for r in g))
    (HERE / "border.txt").write_text("~~\n~~\n")
    legend = dict(kit.LEGEND, **SHARED, **{k: load(k).name for k in OWN},
                  **{ch: {"name": f"gangway_{ch}", "joins": "d"} for ch in GANGWAY_PIECES})
    (HERE / "legend.json").write_text(json.dumps(legend, indent=1) + "\n")
    (HERE / "doors.json").write_text(json.dumps(d, indent=1) + "\n")
    print(f"{len(spec_mt)} metatiles in the spec; grid {MAP_W}x{MAP_H}; doors {d}")


if __name__ == "__main__":
    main()
