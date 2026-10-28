#!/usr/bin/env python3
"""Fuchsia City after its concept (draw_plan.py and plan_stage1.txt): Kanto's town of the Safari Zone, by the southern
sea (see draw_plan.py). It is 48x40 blocks, as before, and its joins stay where they were: Route 18 at the left edge
(rows 18-20, offset 10), Route 15 at the right (rows 20-23, offset 16), Route 19 below the bottom edge (columns
19-28, offset 12).

The pieces: the kit's and its Pokémon Center and Mart; the Safari Zone's gate lodge and Koga's Gym (Kanto Buildings
Remakes v0.3, ../packs/buildings_v0.3) in Saffron's buildings' palette (bank 9); Viridian's houses in theirs (bank 7:
the gardener's for the Safari Zone's office and a house, the family's for the Warden's, the pond keeper's for a house,
and the same pack's pond keeper's house with a back door for the house with the pond garden). Bank 8 is the kit's plants palette; 10-12 stay free for the
seams to old Routes 15 and 19, whose strips in this town (the right seven columns, the bottom seven rows) are
forest, lawn, road, dirt and hedges only.

Run from the repository root:  python3 project/art/fuchsia-concept/make_art.py
It writes buildings/, sheets/, the palettes, spec.json, grid.txt, border.txt, legend.json and doors.json next to
itself; build.sh turns them into the game's tileset and map with pae.
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
VB = HERE.parent / "viridian-concept/buildings"
FB = buildings.REMAKES
SECONDARY = "gTileset_FuchsiaConcept"
MAP_W, MAP_H = 48, 40
HOUSE_BANK, TOWN_BANK = 7, 9
WEST = [(0, y) for y in range(18, 21)]
EAST = [(MAP_W - 1, y) for y in range(20, 24)]
SOUTH = [(x, MAP_H - 1) for x in range(19, 29)]
SOLID = set("T#bRoklSBcw_~vrAGZLOWHJK")
DOOR, BACK = "MB_ANIMATED_DOOR", "MB_SOUTH_ARROW_WARP"
# the buildings: their letters in the plan, their packs, their banks, and what each of their doors does (the house
# with the pond garden has a back door, entered walking south from the garden)
BUILDINGS = {"A": (FB / "safari_gate", TOWN_BANK, [DOOR]),
             "G": (FB / "fuchsia_gym", TOWN_BANK, [DOOR]),
             "O": (VB / "house_gardener", HOUSE_BANK, [DOOR]),
             "H": (VB / "house_gardener", HOUSE_BANK, [DOOR]),
             "W": (VB / "house_family", HOUSE_BANK, [DOOR]),
             "J": (VB / "house_pond_keeper", HOUSE_BANK, [DOOR]),
             "K": (FB / "house_pond_garden", HOUSE_BANK, [DOOR, BACK])}
SHARED = {"Z": "pokemon_center", "L": "poke_mart"}
STREET = (20, 19)        # the main street: everything walkable is reached from it
TREES = [(9, 11), (30, 11), (17, 26), (22, 27)]   # the trees to cut: shortcuts, and the flower garden's way in
FLOWER_GARDEN = (17, 24)  # behind the third tree
POND_GARDEN = (37, 26)    # behind the house at the east end, reached by its back door only
CAMP = [(8, 24), (6, 24), (10, 24), (7, 26), (7, 22), (9, 23), (5, 26)]  # the Friends', round 8,24
HIDDEN = (35, 26)         # the Max Revive, in the pond garden
# the zoo's pens (inside their fences): the fossil Pokémon's, Voltorb's, Kangaskhan's, Chansey's; closed, so their
# Pokémon stay in
PENS = [(3, 4, 7, 7), (31, 4, 33, 7), (37, 4, 39, 7), (35, 12, 39, 15)]
STRIP = 7                 # the columns (rows) of this town old Route 15 (Route 19) draws


def load(letter: str) -> tuple[buildings.Building, list[tuple[int, int]]]:
    """A building and its doors (``door_blocks``, or the older packs' one ``door_block``)."""
    if letter in SHARED:
        b = kit.SHARED_BUILDINGS[SHARED[letter]][0]
        return b, [b.door]
    folder = BUILDINGS[letter][0]
    meta = json.loads((folder / f"{folder.name}.json").read_text())
    with Image.open(folder / f"{folder.name}.png") as im:
        idx, flat = np.array(im, np.uint8), im.getpalette()[:48]
    ds = [tuple(d) for d in meta["door_blocks"]] if "door_blocks" in meta else [tuple(meta["door_block"])]
    return buildings.Building(folder.name, idx, [tuple(flat[i:i + 3]) for i in range(0, 48, 3)],
                              ds[0] if ds else None, folder / f"{folder.name}_door.png"), ds


def plan() -> list[list[str]]:
    rows = (HERE / "plan_stage1.txt").read_text().split("\n")[:MAP_H]
    g = [list(r) for r in rows]
    assert len(g) == MAP_H and all(len(r) == MAP_W for r in g), "the plan is 48x40"
    return g


def doors(g) -> dict[str, list[tuple[int, int]]]:
    out = {}
    for letter in list(SHARED) + list(BUILDINGS):
        b, ds = load(letter)
        bw, bh = b.idx.shape[1] // 16, b.idx.shape[0] // 16
        cells = {(x, y) for y, r in enumerate(g) for x, c in enumerate(r) if c == letter}
        x0, y0 = min(cells)
        assert cells == {(x0 + i, y0 + j) for i in range(bw) for j in range(bh)}, f"{letter} isn't its footprint"
        out[letter] = [(x0 + dx, y0 + dy) for dx, dy in ds]
    return out


def reachable(g, starts, blocked=frozenset(), links=()) -> set[tuple[int, int]]:
    """Blocks you can walk to; ``links`` join pairs of doors through a building (the house's front and back)."""
    hop = {}
    for a, b in links:
        hop.setdefault(a, []).append(b)
        hop.setdefault(b, []).append(a)
    seen, todo = set(starts), deque(starts)
    while todo:
        x, y = todo.popleft()
        for n in [(x + 1, y), (x - 1, y), (x, y + 1), (x, y - 1)] + hop.get((x, y), []):
            if not (0 <= n[0] < MAP_W and 0 <= n[1] < MAP_H) or n in seen or n in blocked:
                continue
            if g[n[1]][n[0]] in SOLID and n not in hop:
                continue
            seen.add(n)
            todo.append(n)
    return seen


def check(g, d) -> None:
    """The town's rules: only the three roads open onto the edges; the zoo's pens are closed; with the trees cut and the house walked through,
    everything walkable is reached from the main street; without the trees, all but the flower garden, and the pond
    garden only through the house; the trees stand more than 8 blocks from the edges you come in by (KR-45); every
    door can be walked into (the back door from the garden), every sign read, the hidden item found; the Friends'
    camp is open ground; the strips the old routes draw are forest, lawn, road, dirt and hedges only."""
    edge = {(x, y) for y in range(MAP_H) for x in range(MAP_W) if x in (0, MAP_W - 1) or y in (0, MAP_H - 1)}
    assert {xy for xy in edge if g[xy[1]][xy[0]] not in SOLID} == set(WEST + EAST + SOUTH), "only the roads open"
    walk = {(x, y) for y in range(MAP_H) for x in range(MAP_W) if g[y][x] not in SOLID}
    pens = {(x, y) for x0, y0, x1, y1 in PENS for x in range(x0, x1 + 1) for y in range(y0, y1 + 1)} & walk
    walk -= pens
    (front, back) = d["K"]
    house = [((front[0], front[1] + 1), (back[0], back[1] - 1))]
    every = reachable(g, [STREET], links=house)
    assert walk <= every, f"blocks you can't reach: {sorted(walk - every)[:8]}"
    assert not pens & every, "a pen is open: its Pokémon would walk out"
    uncut = reachable(g, [STREET], set(TREES), house)
    assert FLOWER_GARDEN not in uncut and walk - uncut - {FLOWER_GARDEN} <= reachable(
        g, [FLOWER_GARDEN], {TREES[2]}) | set(TREES), "only the flower garden is behind a tree"
    outside = reachable(g, [STREET])
    assert POND_GARDEN not in outside, "the pond garden is reached only through the house"
    assert all(8 < x < MAP_W - 9 and y < MAP_H - 9 for x, y in TREES), "the game would hide a tree"
    for letter, ds in d.items():
        behaviors = BUILDINGS[letter][2] if letter in BUILDINGS else [DOOR]
        assert len(ds) == len(behaviors), f"{letter}'s doors"
        for (x, y), mb in zip(ds, behaviors):
            way_in = (x, y - 1) if mb == BACK else (x, y + 1)
            assert way_in in every, f"the door of {letter} at ({x},{y}) can't be walked into"
    for y in range(MAP_H):
        for x in range(MAP_W):
            if g[y][x] == "S":
                assert (x, y + 1) in every, f"the sign at ({x},{y}) can't be read"
    x, y = HIDDEN
    assert HIDDEN in every and any(n in every for n in ((x + 1, y), (x - 1, y), (x, y + 1), (x, y - 1)))
    assert set(CAMP) <= outside, "the Friends' camp must be open ground"
    east = {g[y][x] for y in range(MAP_H) for x in range(MAP_W - STRIP, MAP_W)}
    south = {g[y][x] for y in range(MAP_H - STRIP, MAP_H) for x in range(MAP_W)}
    assert east <= set("T.=b") and south <= set("T.=:b"), f"the strips: {east}, {south}"


def main() -> None:
    g = plan()
    d = doors(g)
    kit.check_forest(g)
    kit.check_water(g)
    kit.check_paving(g)
    check(g, d)
    base = kit.primary(HERE)  # the kit: the primary tileset every map shares
    spec_mt = list(base["metatiles"])
    pals, added = {}, set()
    for letter, (folder, bank, behaviors) in BUILDINGS.items():
        if folder in added:  # one pack for several letters: its metatiles once
            continue
        added.add(folder)
        b, ds = load(letter)
        pals.setdefault(bank, b.palette)
        assert pals[bank] == b.palette, f"{b.name}: its palette isn't the one bank {bank} has"
        bw = b.idx.shape[1] // 16
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
                         "secondary": [f"palette_{HOUSE_BANK}.pal", base["secondary_palettes"][8],
                                       f"palette_{TOWN_BANK}.pal"]},
            "reserve": {"primary": base["reserve"]},
            "animations": base["animations"],
            "field_effects": base["field_effects"],
            "metatiles": spec_mt}
    (HERE / "spec.json").write_text(json.dumps(spec, indent=1) + "\n")
    (HERE / "grid.txt").write_text("".join("".join(r) + "\n" for r in g))
    (HERE / "border.txt").write_text("TT\nTT\n")
    legend = dict(kit.LEGEND, **SHARED, **{k: load(k)[0].name for k in BUILDINGS})
    (HERE / "legend.json").write_text(json.dumps(legend, indent=1) + "\n")
    (HERE / "doors.json").write_text(json.dumps(d, indent=1) + "\n")
    print(f"{len(spec_mt)} metatiles in the spec; grid {MAP_W}x{MAP_H}; doors {d}")


if __name__ == "__main__":
    main()
