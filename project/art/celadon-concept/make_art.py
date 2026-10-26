#!/usr/bin/env python3
"""Celadon City after its concept (draw_plan.py and plan_stage1.txt): Kanto's garden city (see draw_plan.py). It is
60x40 blocks, as old Celadon was; its joins: the boulevard's two ends, rows 20-23, meet Route 16's road (its rows
22-25, offset -2) at the left edge and Route 7's (its rows 10-13, offset 10) at the right.

The pieces: the kit's and its Pokémon Center; the Department Store, the Mansion, the hotel, the Game Corner and
Erika's Gym, drawn here (celadon_buildings.py) in one palette (bank 9); Viridian's houses (the pond keeper's for the
Prize Room and a house, the family's for the restaurant) in theirs (bank 7). The town's own tileset holds 384 tiles:
the buildings are drawn on the 16-pixel grid so their tiles repeat. Bank 8 is the kit's plants palette; 10-12 stay free for seams to old maps (Route 16 is
from the kit now: their seam needs none).

Run from the repository root:  python3 project/art/celadon-concept/make_art.py
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
sys.path.insert(0, str(Path(__file__).resolve().parent))
import buildings
import celadon_buildings
import kit

HERE = Path(__file__).resolve().parent
ART = HERE.parent
VB = ART / "viridian-concept/buildings"
SECONDARY = "gTileset_CeladonConcept"
MAP_W, MAP_H = 60, 40
HOUSE_BANK, CITY_BANK = 7, 9
WEST = [(0, y) for y in range(20, 24)]
EAST = [(MAP_W - 1, y) for y in range(20, 24)]
SOLID = set("T#bRoklSBcw_~vrDMOCGPEHY")
DOOR, BACK = "MB_ANIMATED_DOOR", "MB_SOUTH_ARROW_WARP"
# the buildings: their letters in the plan, their packs, their banks, and what each of their doors does (the
# Mansion's second is its back door, entered walking south from above)
BUILDINGS = {"D": (celadon_buildings.OUT / "department_store", CITY_BANK, [DOOR, DOOR]),
             "M": (celadon_buildings.OUT / "mansion", CITY_BANK, [DOOR, BACK]),
             "O": (celadon_buildings.OUT / "hotel", CITY_BANK, [DOOR]),
             "G": (celadon_buildings.OUT / "game_corner", CITY_BANK, [DOOR]),
             "Y": (celadon_buildings.OUT / "celadon_gym", CITY_BANK, [DOOR]),
             "P": (VB / "house_pond_keeper", HOUSE_BANK, [DOOR]),
             "E": (VB / "house_family", HOUSE_BANK, [DOOR]),
             "H": (VB / "house_pond_keeper", HOUSE_BANK, [DOOR])}  # (the Prize Room's: one pack, fewer tiles)
SHARED = {"C": "pokemon_center"}
TREES = [(50, 13), (12, 25)]  # the trees to cut: the walled garden's behind the Center, the Gym garden's
GARDEN = {(x, y) for y in range(3, 13) for x in range(46, 58)}
GYM_GARDEN = {(x, y) for y in range(26, 37) for x in range(8, 18)}
CAMP = [(25, 34), (23, 34), (26, 33), (24, 33), (24, 35), (25, 36), (22, 35)]  # the Friends', round 25,34
GIRL = (35, 32, 4, 4)  # the little girl's walk: from 35,32 round a 4x4 square


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
    return buildings.Building(folder.name, idx, [tuple(flat[i:i + 3]) for i in range(0, 48, 3)], ds[0],
                              folder / f"{folder.name}_door.png"), ds


def plan() -> list[list[str]]:
    rows = (HERE / "plan_stage1.txt").read_text().split("\n")[:MAP_H]
    g = [list(r) for r in rows]
    assert len(g) == MAP_H and all(len(r) == MAP_W for r in g), "the plan is 60x40"
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


def check(g, d) -> None:
    """The city's rules: only the boulevard's two ends open onto the edges; the trees close the walled garden and the Gym garden, stand more than 8 blocks from
    either edge, and with them cut everything walkable is reached; every door can be walked into (the Mansion's back
    door from above), every sign read; the Friends' camp is open ground and the little girl's walk is clear."""
    edge = {(x, y) for y in range(MAP_H) for x in range(MAP_W) if x in (0, MAP_W - 1) or y in (0, MAP_H - 1)}
    assert {xy for xy in edge if g[xy[1]][xy[0]] not in SOLID} == set(WEST + EAST), "only the boulevard opens"
    walk = {(x, y) for y in range(MAP_H) for x in range(MAP_W) if g[y][x] not in SOLID}
    closed = reachable(g, EAST, set(TREES))
    assert not closed & (GARDEN | GYM_GARDEN), "the trees must close the two gardens"
    assert all(8 < x < MAP_W - 9 for x, _ in TREES), "the game would hide a tree near an edge you come in by"
    every = reachable(g, EAST)
    assert walk <= every, f"blocks you can't reach: {sorted(walk - every)[:8]}"
    assert set(WEST) <= every, "the boulevard must go through"
    for letter, ds in d.items():
        behaviors = BUILDINGS[letter][2] if letter in BUILDINGS else [DOOR]
        for (x, y), mb in zip(ds, behaviors):
            front = (x, y - 1) if mb == BACK else (x, y + 1)
            assert front in every, f"the door of {letter} at ({x},{y}) can't be walked into"
    for y in range(MAP_H):
        for x in range(MAP_W):
            if g[y][x] == "S":
                assert (x, y + 1) in every, f"the sign at ({x},{y}) can't be read"
    assert set(CAMP) <= every, "the Friends' camp must be open ground"
    x0, y0, rx, ry = GIRL
    loop = {(x, y) for x in range(x0, x0 + rx + 1) for y in (y0, y0 + ry)} | \
           {(x, y) for y in range(y0, y0 + ry + 1) for x in (x0, x0 + rx)}
    assert loop <= every, f"the little girl's walk is blocked at {sorted(loop - every)[:4]}"


def main() -> None:
    for draw in celadon_buildings.ALL:
        draw()
    g = plan()
    d = doors(g)
    kit.check_forest(g)
    kit.check_water(g)
    check(g, d)
    base = kit.primary(HERE)  # the kit: the primary tileset every map shares
    spec_mt = list(base["metatiles"])
    pals, added = {}, set()
    for letter, (folder, bank, behaviors) in BUILDINGS.items():
        if folder in added:  # one pack for two letters: its metatiles once
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
                                       f"palette_{CITY_BANK}.pal"]},
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
