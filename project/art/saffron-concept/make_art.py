#!/usr/bin/env python3
"""Saffron City after its concept (draw_plan.py and plan_stage1.txt): Kanto's golden city of commerce, two avenues
crossing in its middle, a gatehouse at each of their four ends (see draw_plan.py). It is 60x48 blocks (old Saffron
was 66x55). Its joins aren't compiled: the routes around it see its twin, SaffronCity_Connection, and from inside it
nothing shows beyond its edges but its border's forest. So it has no seams, and banks 10-12 are free for its own
palettes.

The pieces: the kit's and its Pokémon Center and Mart; Silph Co., Sabrina's Gym, the Fighting Dojo, the gatehouses and
the Magnet Train station, from Kanto Buildings Remakes v0.3 (../packs/buildings_v0.3), in one palette (bank 9); and
Viridian's pond keeper's house in its palette (bank 7) for Copycat's house, a house, Mr. Psychic's and the Trainer Fan
Club: the remakes take 300 of the town's 384 tiles, and one kind of house (55) is all that fits beside them. Between
them stand offices and arcades without doors, made from Silph Co.'s and the station's own tiles (CITY; banks 9-11),
and the city is paved, so its Center, Mart and lamps are its own copies of the kit's, on paving (PAVED).

Run from the repository root:  python3 project/art/saffron-concept/make_art.py
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
ART = HERE.parent
VB = ART / "viridian-concept/buildings"
SB = buildings.REMAKES
SECONDARY = "gTileset_SaffronConcept"
MAP_W, MAP_H = 60, 48
HOUSE_BANK, CITY_BANK = 7, 9
GROUND = "paving#15"  # what shows round the city's own buildings' edges
SOLID = set("T#bRoklSBcw_~vrXMDGNWEUZLYHPKAFIJVCa")
DOOR, BACK = "MB_ANIMATED_DOOR", "MB_SOUTH_ARROW_WARP"
# the buildings: their letters in the plan, their packs, their banks, and what each of their doors does (the south
# gatehouse's doorway is entered walking south from above; the station has no door)
BUILDINGS = {"X": (SB / "silph_co", CITY_BANK, [DOOR]),
             "G": (SB / "saffron_gym", CITY_BANK, [DOOR]),
             "D": (SB / "fighting_dojo", CITY_BANK, [DOOR]),
             "N": (SB / "saffron_gate", CITY_BANK, [DOOR, DOOR]),
             "W": (SB / "saffron_gate", CITY_BANK, [DOOR, DOOR]),
             "E": (SB / "saffron_gate", CITY_BANK, [DOOR, DOOR]),
             "U": (SB / "saffron_gate_back", CITY_BANK, [BACK, BACK]),
             "M": (SB / "magnet_train_station", CITY_BANK, []),
             "Y": (VB / "house_pond_keeper", HOUSE_BANK, [DOOR]),
             "H": (VB / "house_pond_keeper", HOUSE_BANK, [DOOR]),
             "P": (VB / "house_pond_keeper", HOUSE_BANK, [DOOR]),
             "K": (VB / "house_pond_keeper", HOUSE_BANK, [DOOR])}
SHARED = {"Z": "pokemon_center", "L": "poke_mart"}
# the city's blocks: offices and arcades without doors, made from Silph Co.'s and the station's own 8x8 cells
# (buildings.recompose), so they cost no tiles: Silph's tower without its emblem, sign and door, cut to fewer floors
# and narrower (its window columns 3-6 repeat: column 12 is 6, 13-15 are 3-5), and the station's hall without its sign
# and shutter (its columns 11-12 are 3-4). Each colour is a palette of its own (the free banks 10 and 11), its
# pictures the same indices, so the same tiles; blocks the designs share are one metatile ("dedupe").
SILPH_ROWS = {"tall": list(range(7)) + [7, 8, 9] * 2 + [19, 20, 21, 22, 23],  # roof, three floors, the ground floor
              "mid": list(range(7)) + [19, 20, 21, 22, 23]}                   # roof, one floor, the ground floor
SILPH_COLS = {6: [0, 1, 2, 3, 4, 5, 6, 3, 4, 5, 16, 17], 4: [0, 1, 2, 3, 4, 5, 16, 17]}  # blocks wide
STATION_COLS = [0, 1, 2, 3, 4, 13, 14, 15]
COLOURS = {"beige": (CITY_BANK, {}),  # Silph's own
           "sand": (10, {4: (136, 112, 72), 9: (216, 184, 112), 10: (232, 208, 144), 11: (248, 232, 184)}),
           "brick": (11, {4: (104, 72, 72), 9: (176, 104, 80), 10: (208, 144, 112), 11: (232, 192, 160)})}
# their letters in the plan: (design, colour); a letter may stand for several of them, apart
CITY = {"A": ("office_tall", "sand"), "F": ("office_tall", "brick"), "I": ("office_mid", "sand"),
        "J": ("office_mid", "brick"), "V": ("office_narrow", "beige"), "C": ("office_narrow", "brick"),
        "a": ("arcade", "beige")}
# the kit's Center, Mart and lamp stand on grass; Saffron is paved, so it has its own copies of them on its paving
# (the kit's tiles in the kit's banks: no new tiles)
PAVED = {"Z": ("pokemon_center", "center", 5), "L": ("poke_mart", "mart", 6)}
# what the paving runs up to without an edge: the buildings, signs, trees and lamps standing on it
JOINS = "".join(k for k in BUILDINGS if k not in "NWEU") + "".join(SHARED) + "".join(CITY) + "SRl"  # (not the gates)
CROSSING = (29, 23)  # the avenues' crossing: everything walkable is reached from it
CAMP = [(50, 8), (50, 10), (49, 9), (48, 8), (52, 8), (48, 10), (47, 6)]  # the Friends', round 50,8
TRAIN = (49, 18)     # where the Magnet Train from Goldenrod lets you off, in front of the station
WALKS = [(24, 20, 4), (7, 34, 4), (44, 33, 5), (45, 23, 4), (19, 33, 5), (55, 43, 1)]  # walkers: x, y, range


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


def city_designs() -> dict[str, np.ndarray]:
    """The doorless designs, as palette indices of the city's palette (bank 9)."""
    silph = load("X")[0].idx
    station = load("M")[0].idx
    return {"office_tall": buildings.recompose(silph, SILPH_ROWS["tall"], SILPH_COLS[6]),
            "office_mid": buildings.recompose(silph, SILPH_ROWS["mid"], SILPH_COLS[6]),
            "office_narrow": buildings.recompose(silph, SILPH_ROWS["mid"], SILPH_COLS[4]),
            "arcade": buildings.recompose(station, range(8), STATION_COLS)}


def plan() -> list[list[str]]:
    rows = (HERE / "plan_stage1.txt").read_text().split("\n")[:MAP_H]
    g = [list(r) for r in rows]
    assert len(g) == MAP_H and all(len(r) == MAP_W for r in g), "the plan is 60x48"
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


def reachable(g, starts) -> set[tuple[int, int]]:
    seen, todo = set(starts), deque(starts)
    while todo:
        x, y = todo.popleft()
        for n in ((x + 1, y), (x - 1, y), (x, y + 1), (x, y - 1)):
            if not (0 <= n[0] < MAP_W and 0 <= n[1] < MAP_H) or n in seen or g[n[1]][n[0]] in SOLID:
                continue
            seen.add(n)
            todo.append(n)
    return seen


def check(g, d) -> None:
    """The city's rules: nothing walkable on its edges (it has no joins: its gatehouses are the ways out); everything
    walkable is reached from the avenues' crossing; every door can be walked into (the south gatehouse's from
    above), every sign read; the Friends' camp, the train's stop and the walkers' paths are open ground."""
    edge = {(x, y) for y in range(MAP_H) for x in range(MAP_W) if x in (0, MAP_W - 1) or y in (0, MAP_H - 1)}
    assert all(g[y][x] in SOLID for x, y in edge), "an edge is open"
    walk = {(x, y) for y in range(MAP_H) for x in range(MAP_W) if g[y][x] not in SOLID}
    every = reachable(g, [CROSSING])
    assert walk <= every, f"blocks you can't reach: {sorted(walk - every)[:8]}"
    for letter, ds in d.items():
        behaviors = BUILDINGS[letter][2] if letter in BUILDINGS else [DOOR]
        assert len(ds) == len(behaviors), f"{letter}'s doors"
        for (x, y), mb in zip(ds, behaviors):
            front = (x, y - 1) if mb == BACK else (x, y + 1)
            assert front in every, f"the door of {letter} at ({x},{y}) can't be walked into"
    for y in range(MAP_H):
        for x in range(MAP_W):
            if g[y][x] == "S":
                assert (x, y + 1) in every, f"the sign at ({x},{y}) can't be read"
    assert set(CAMP) <= every, "the Friends' camp must be open ground"
    assert TRAIN in every and g[TRAIN[1] - 1][TRAIN[0]] == "M", "the train's stop is in front of the station"
    for x, y, r in WALKS:
        path = {(xx, y) for xx in range(x - r, x + r + 1)}
        assert path <= every, f"the walk from ({x},{y}) is blocked at {sorted(path - every)[:4]}"


def main() -> None:
    g = plan()
    d = doors(g)
    kit.check_forest(g)
    kit.check_water(g)
    kit.check_paving(g, joins=JOINS)
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
        sh.add(b.name, b.idx, tileset="secondary", ground=GROUND, solid=True, open=open_, behaviors=behavior)
        spec_mt += sh.write()
    for letter, (name, pal, bank) in PAVED.items():
        b = kit.SHARED_BUILDINGS[name][0]
        sh = kit.Sheet(f"{name}_paved", kit.PALS[pal], bank, HERE, HERE, cols=b.idx.shape[1] // 16)
        sh.add(f"{name}_paved", b.idx, tileset="secondary", **dict(b.entry(), ground=GROUND))
        spec_mt += sh.write()
    sh = kit.Sheet("lamp_paved", kit.PALS["plants"], 8, HERE, HERE, cols=1)
    sh.add("lamp_paved", kit.lamp(), tileset="secondary", ground=GROUND, solid=True)
    spec_mt += sh.write()
    designs = city_designs()
    for colour, (bank, changes) in COLOURS.items():
        used = sorted({dn for dn, c in CITY.values() if c == colour})
        if not used:
            continue
        pal = buildings.recolour(pals[CITY_BANK], changes)
        pals.setdefault(bank, pal)
        sh = kit.Sheet(f"city_{colour}", pal, bank, HERE, HERE, cols=6)
        for dn in used:
            sh.add(f"{dn}_{colour}", designs[dn], tileset="secondary", ground=GROUND, solid=True, dedupe=True)
        spec_mt += sh.write()
    for e in spec_mt:  # sheets put "w"/"h" on everything; drop the 1x1 ones for readability
        if e["w"] == 1 and e["h"] == 1:
            del e["w"], e["h"]
    for bank, pal in pals.items():
        kit.write_palette(HERE / f"palette_{bank}.pal", pal)
    spec = {"version": "hns", "primary": kit.PRIMARY, "secondary": SECONDARY,
            "palettes": {"primary": base["palettes"],
                         "secondary": [f"palette_{HOUSE_BANK}.pal", base["secondary_palettes"][8]]
                         + [f"palette_{b}.pal" for b in sorted(pals) if b > 8]},
            "reserve": {"primary": base["reserve"]},
            "animations": base["animations"],
            "field_effects": base["field_effects"],
            "metatiles": spec_mt}
    (HERE / "spec.json").write_text(json.dumps(spec, indent=1) + "\n")
    (HERE / "grid.txt").write_text("".join("".join(r) + "\n" for r in g))
    (HERE / "border.txt").write_text("TT\nTT\n")
    legend = dict(kit.LEGEND, **{k: load(k)[0].name for k in BUILDINGS},
                  **{k: f"{d}_{c}" for k, (d, c) in CITY.items()},
                  **{k: f"{n}_paved" for k, (n, _, _) in PAVED.items()})
    legend["l"] = "lamp_paved"
    for k in JOINS:
        item = legend[k]
        legend[k] = dict({"name": item} if isinstance(item, str) else item, joins="p")
    (HERE / "legend.json").write_text(json.dumps(legend, indent=1) + "\n")
    (HERE / "doors.json").write_text(json.dumps(d, indent=1) + "\n")
    print(f"{len(spec_mt)} metatiles in the spec; grid {MAP_W}x{MAP_H}; doors {d}")


if __name__ == "__main__":
    main()
