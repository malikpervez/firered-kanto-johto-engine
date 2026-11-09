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
import props
import streets
import trees

HERE = Path(__file__).resolve().parent
ART = HERE.parent
VB = ART / "viridian-concept/buildings"
SB = buildings.REMAKES
SECONDARY = "gTileset_SaffronConcept"
MAP_W, MAP_H = 60, 48
HOUSE_BANK, CITY_BANK = 7, 9
GROUND = "kerb#15"  # what shows round the city's own buildings' edges: the pavement
SOLID = set("T#bRoklSBcw_~vrXMDGNWEUZLYHPKAFIJVCa|^uy")
# the town props (Kanto Town Props v0.1, kit/props.py): (piece, x, y of its top-left block, the ground under it)
PROPS = [("bench_stone", 9, 19, "granite#15"), ("litter_bin", 12, 19, "granite#15"), ("bench_stone", 14, 19, "granite#15"),
         ("bench_stone", 39, 19, "granite#15"), ("flower_tub", 42, 19, "granite#15"), ("flower_tub", 45, 19, "granite#15"),
         ("bench_stone", 47, 19, "granite#15"), ("litter_bin", 50, 19, "granite#15")]  # on the plazas, the tubs either side of the compass
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
# what shows round a building's edges, block by block (row by row): the pavement ("k", GROUND) but where it backs
# onto the lawn, the garden's trees, a hedge or the forest: grass ("g"), or the pavement's own north verge ("p",
# pavement#14: grass over its top half, paving under) where the paving runs on beside it, or its east verge ("r",
# pavement#13: paving, grass on its east half) down a building's side along the forest. (pae bakes one layer of a
# ground under a piece: for the pavement's verge quarters its grass, for the kerb's rim quarters its asphalt, so a
# building's corner on the kerb's rim or on the verge's foot would show a square of road or grass: those keep "k")
EDGE_GROUNDS = {"k": GROUND, "g": "grass", "p": "pavement#14", "r": "pavement#13"}
EDGES = {"N": ["gggg", "gggg", "kkkk"],                 # the gatehouses in the forest: the north one,
         "W": ["gggp", "gkkk", "gkkk"],                 # the west one (bushes above it),
         "E": ["pggg", "kkkg", "kkkg"],                 # the east one,
         "U": ["gkkg", "gkkg", "gggg"],                 # and the south one's back
         "X": ["kkkkkkkkg"] * 8 + ["kkkkkkkkk"] * 4,    # Silph Co.: the garden's trees down its east side
         "M": ["pggggggg"] + ["kkkkkkkk"] * 3,          # the station: the garden's trees behind it
         "u": ["gggg", "kkkg", "kkkg", "kggg"],         # the arcade east of it: bushes behind, the forest beside
         "y": ["pppp"] + ["kkkk"] * 5,                  # the narrow office under the Gym square's hedge
         "C": ["kkkr"] * 6}                             # and the narrow brick one by the east forest (CITY's own)
# their letters in the plan: (design, colour); a letter may stand for several of them, apart
CITY = {"A": ("office_tall", "sand"), "F": ("office_tall", "brick"), "I": ("office_mid", "sand"),
        "J": ("office_mid", "brick"), "V": ("office_narrow", "beige"), "C": ("office_narrow", "brick"),
        "a": ("arcade", "beige")}
EDGED = {"u": ("arcade", "beige"), "y": ("office_narrow", "beige")}  # those with their own edges (EDGES)
# the kit's Center, Mart and lamp stand on grass; Saffron is paved, so it has its own copies of them on its paving
# (the kit's tiles in the kit's banks: no new tiles)
PAVED = {"Z": ("pokemon_center", "center", 5), "L": ("poke_mart", "mart", 6)}
# what the pavement runs up to without a kerb: the buildings, signs, street trees, lamps and the dropped kerbs
JOINS = "".join(k for k in BUILDINGS if k not in "NWEU") + "".join(SHARED) + "".join(CITY) + "".join(EDGED) + "S|l68"  # (not the gates)
# the street pieces (the kit's, streets.py) by their letters; the granite and the compass are Saffron's own, from the
# pack's city palette (bank 12)
STREET_PIECES = {"0": "crossing_road_NS", "2": "crossing_end_W", "3": "crossing_end_E", "6": "crossing_dropped_kerb_E",
                 "8": "crossing_dropped_kerb_W", "%": "manhole", "-": "asphalt_dashed_H_boundary",
                 ";": "asphalt_dashed_V_boundary"}
STREETS_BANK = 12
ROAD = set("+-;%023")  # the road's letters: the asphalt and what's painted on it
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


def bname(letter: str) -> str:
    """A building's piece: the pack's, or its own copy where it has its own edges (EDGES)."""
    name = load(letter)[0].name
    return f"{name}_{letter.lower()}" if letter in EDGES else name


def edge_ground(letter: str):
    """What shows round a piece's edges: the pavement, or block by block (EDGES)."""
    return [EDGE_GROUNDS[c] for row in EDGES[letter] for c in row] if letter in EDGES else GROUND


def onto_plazas(g, legend, names) -> list[list[str]]:
    """The pavement round the granite plazas runs on under their brass-banded edge (the granite's ground is the
    pavement): beside the granite it keeps its kerb or verge only where it meets the road or a lawn, so the strip under
    each plaza is a kerb in front of it, not an island between two roads. Each such block gets the piece pae map paint
    would give it if the granite were pavement (its own letter, in the pavement's group)."""
    def grp(c):
        it = legend.get(c)
        return it.get("joins", c) if isinstance(it, dict) else c

    def same(x, y):
        return not (0 <= x < MAP_W and 0 <= y < MAP_H) or grp(g[y][x]) in ("&", "@")
    plaza = {c for c in legend if grp(c) == "@"}
    out, letters = [r[:] for r in g], {}
    for y in range(MAP_H):
        for x in range(MAP_W):
            if g[y][x] not in "&$" or not any(0 <= x + dx < MAP_W and 0 <= y + dy < MAP_H and g[y + dy][x + dx] in plaza
                                               for dx in (-1, 0, 1) for dy in (-1, 0, 1)):
                continue
            auto = legend[g[y][x]]["auto"]
            mask = sum(b for b, (dx, dy) in ((1, (0, -1)), (2, (1, 0)), (4, (0, 1)), (8, (-1, 0))) if same(x + dx, y + dy))
            corners = sum(b for b, (dx, dy), s in ((1, (1, -1), 3), (2, (1, 1), 6), (4, (-1, 1), 12), (8, (-1, -1), 9))
                          if mask & s == s and not same(x + dx, y + dy))
            name = next(n for n in (f"{auto}#{mask}.{corners}" if corners else None, f"{auto}#{mask}", f"{auto}#15")
                        if n and n in names)
            variants = [name] + [f"{name}~{k}" for k in range(1, 64) if f"{name}~{k}" in names]
            name = variants[(x * 7919 + y * 104729 + (x * y) % 13) % len(variants)]
            if name not in letters:
                letters[name] = chr(0x3B1 + len(letters))  # (Greek letters: no plan or kit piece uses them)
                legend[letters[name]] = {"name": name, "joins": "&"}
            out[y][x] = letters[name]
    return out


def plaza_corners(g, prop_legend) -> set[tuple[int, int]]:
    """The granite's inside corners the plazas have (its edge mask and corners, as pae map paint picks them): only
    those are drawn, so the others' tiles don't take the full tileset's room."""
    plaza = {"@", "/"} | {k for k, v in prop_legend.items() if isinstance(v, dict) and v.get("joins") == "@"}

    def same(x, y):
        return not (0 <= x < MAP_W and 0 <= y < MAP_H) or g[y][x] in plaza
    out = set()
    for y in range(MAP_H):
        for x in range(MAP_W):
            if g[y][x] == "@":
                mask = sum(b for b, (dx, dy) in ((1, (0, -1)), (2, (1, 0)), (4, (0, 1)), (8, (-1, 0))) if same(x + dx, y + dy))
                corners = sum(b for b, (dx, dy), sd in ((1, (1, -1), 3), (2, (1, 1), 6), (4, (-1, 1), 12), (8, (-1, -1), 9))
                              if mask & sd == sd and not same(x + dx, y + dy))
                if corners:
                    out.add((mask, corners))
    return out


def compass_band(pal, base) -> np.ndarray:
    """What runs along the bottom of the compass's lower blocks, over it: the plaza's brass band (the granite's
    bottom edge, granite#11) and under it the pavement's tips as they show beside it, so the band runs on across the
    compass, set in the plaza, instead of stopping either side of it. As indices of the city palette (one tile, and
    its mirror)."""
    out = np.zeros((16, 32), np.uint8)
    out[9:13] = np.tile(streets.block("granite", 11, 0, pal)[9:13], (1, 2))
    e = next(e for e in base["metatiles"] if e["name"] == GROUND)
    with Image.open(HERE / e["image"]) as im:
        px = np.array(im.convert("RGBA"))[e["y"] + 13:e["y"] + 16, e["x"]:e["x"] + 16]
    assert (px[..., 3] == 255).all(), "the pavement under the band is opaque"
    index = {tuple(c): i for i, c in enumerate(pal) if i}
    out[13:16] = np.tile(np.vectorize(lambda r, g_, b: index[(r, g_, b)])(px[..., 0], px[..., 1], px[..., 2]), (1, 2))
    return out


def sign_rims(g) -> dict[tuple[int, int], int]:
    """The signs standing on the kerb's edge over a road to their north: each one's sides that aren't the road (bits
    1 N, 2 E, 4 S, 8 W, as pae map paint numbers the kerb's pieces), so its block stands on that kerb piece and the
    road meets its board as it meets the kerb's rim. (pae bakes the rim's quarters as their asphalt: above the board
    that is where the rim runs. Below it, a road to the south, the asphalt would come up round the post, higher than
    the road beside it and between the shopfronts; beside the post, a road to the east or west, it would notch the
    pavement. Those keep the plain paving.)"""
    out = {}
    for y in range(MAP_H):
        for x in range(MAP_W):
            if g[y][x] == "S":
                m = sum(b for b, (dx, dy) in ((1, (0, -1)), (2, (1, 0)), (4, (0, 1)), (8, (-1, 0)))
                        if not (0 <= x + dx < MAP_W and 0 <= y + dy < MAP_H) or g[y + dy][x + dx] not in ROAD)
                if m == 14:
                    out[(x, y)] = m
    return out


def main() -> None:
    g = plan()
    prop_legend, prop_grounds = props.place(g, PROPS, SOLID, joins='@')
    d = doors(g)
    kit.check_forest(g)
    kit.check_water(g)
    kit.check_paving(g, joins=JOINS)
    check(g, d)
    base = kit.primary(HERE)  # the kit: the primary tileset every map shares
    spec_mt = list(base["metatiles"])
    pals, added = {}, set()
    for letter, (folder, bank, behaviors) in BUILDINGS.items():
        if folder in added and letter not in EDGES:  # one pack for several letters: its metatiles once
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
        sh = kit.Sheet(bname(letter), b.palette, bank, HERE, HERE, cols=bw)
        sh.add(bname(letter), b.idx, tileset="secondary", ground=edge_ground(letter), solid=True, open=open_,
               behaviors=behavior, dedupe=True)
        spec_mt += sh.write()
    for letter, (name, pal, bank) in PAVED.items():
        b = kit.SHARED_BUILDINGS[name][0]
        sh = kit.Sheet(f"{name}_paved", kit.PALS[pal], bank, HERE, HERE, cols=b.idx.shape[1] // 16)
        sh.add(f"{name}_paved", b.idx, tileset="secondary", dedupe=True, **dict(b.entry(), ground=GROUND))
        spec_mt += sh.write()
    sh = kit.Sheet("lamp_paved", kit.PALS["plants"], 8, HERE, HERE, cols=1)
    sh.add("lamp_paved", kit.lamp(), tileset="secondary", ground=GROUND, solid=True, dedupe=True)
    spec_mt += sh.write()
    sh = kit.Sheet("sign_paved", kit.PALS["wood"], 2, HERE, HERE, cols=1)
    sh.add("sign_paved", kit.sign(), tileset="secondary", ground=GROUND, solid=True, dedupe=True)
    rims = sign_rims(g)
    for m in sorted(set(rims.values())):  # (the same sign on the kerb's edge pieces: no new tiles)
        sh.add(f"sign_paved_k{m}", kit.sign(), tileset="secondary", ground=f"kerb#{m}", solid=True, dedupe=True)
    spec_mt += sh.write()
    sh = kit.Sheet("trees_paved", kit.PALS["trees"], 3, HERE, HERE, cols=6)
    for name in trees.STANDALONE:  # as the kit's: the crown's row drawn over the player, who walks behind it
        sh.add(f"{name}_paved", trees.tree(name), tileset="secondary", ground=GROUND, solid=True,
               open=["0,0", "1,0"], over_rows=1, dedupe=True)
    spec_mt += sh.write()
    pals[STREETS_BANK] = streets.city_palette()
    sh = kit.Sheet("granite", pals[STREETS_BANK], STREETS_BANK, HERE, HERE)
    for m in range(16):  # the plazas' granite (the pack's Part B), on the pavement, as pae map paint autotiles it
        sh.add(f"granite#{m}", streets.block("granite", m, 0, pals[STREETS_BANK]), tileset="secondary",
               ground=GROUND, dedupe=True)
    for k, v in enumerate(("center_b", "center_c"), 1):
        sh.add(f"granite#15~{k}", streets.piece("granite", v, pals[STREETS_BANK]), tileset="secondary",
               ground=GROUND, dedupe=True)
    corners = plaza_corners(g, prop_legend)
    for m, c in streets.CORNERS:
        if (m, c) in corners:  # (the plazas' own inside corners only)
            sh.add(f"granite#{m}.{c}", streets.block("granite", m, c, pals[STREETS_BANK]), tileset="secondary",
                   ground=GROUND, dedupe=True)
    # the compass, its lower blocks with the plaza's band drawn over them (on the compass's own blocks, so it shows
    # through above the band)
    compass = streets.piece("mosaic", "compass_2x2", pals[STREETS_BANK])
    sh.add("compass_bl", compass[16:, :16], tileset="secondary", ground=GROUND, dedupe=True)
    sh.add("compass_br", compass[16:, 16:], tileset="secondary", ground=GROUND, dedupe=True)
    banded = compass.copy()
    banded[16:] = compass_band(pals[STREETS_BANK], base)
    sh.add("compass", banded, tileset="secondary", ground=[GROUND, GROUND, "compass_bl", "compass_br"], dedupe=True)
    spec_mt += sh.write()
    designs = city_designs()
    for colour, (bank, changes) in COLOURS.items():
        used = sorted({dn for dn, c in CITY.values() if c == colour})
        if not used:
            continue
        pal = buildings.recolour(pals[CITY_BANK], changes)
        pals.setdefault(bank, pal)
        sh = kit.Sheet(f"city_{colour}", pal, bank, HERE, HERE, cols=6)
        for dn in used:  # (each design and colour is one letter's)
            k = next(k for k, v in CITY.items() if v == (dn, colour))
            sh.add(f"{dn}_{colour}", designs[dn], tileset="secondary", ground=edge_ground(k), solid=True, dedupe=True)
        for k, (dn, c) in EDGED.items():
            if c == colour:
                sh.add(f"{dn}_{colour}_{k}", designs[dn], tileset="secondary", ground=edge_ground(k), solid=True,
                       dedupe=True)
        spec_mt += sh.write()
    prop_entries, prop_anims = props.pieces(HERE, HERE, prop_grounds)
    spec_mt += prop_entries
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
            "animations": base["animations"] + prop_anims,
            "field_effects": base["field_effects"],
            "metatiles": spec_mt}
    (HERE / "spec.json").write_text(json.dumps(spec, indent=1) + "\n")
    (HERE / "border.txt").write_text("TT\nTT\n")
    legend = dict(kit.LEGEND, **{k: bname(k) for k in BUILDINGS},
                  **{k: f"{d}_{c}" for k, (d, c) in CITY.items()},
                  **{k: f"{d}_{c}_{k}" for k, (d, c) in EDGED.items()},
                  **{k: f"{n}_paved" for k, (n, _, _) in PAVED.items()})
    legend["l"] = "lamp_paved"
    legend["^"] = "lamp"                       # the kit's lamp on the lawn (Saffron Park's corner)
    legend["E"], legend["W"] = ({"name": bname(k), "joins": "&"} for k in "EW")  # the pavement runs into their paved base
    legend["S"] = "sign_paved"
    legend["e"] = {"name": "kerb#14", "joins": "&"}  # the paving at the forest's road corners: kerb on the road side only
    legend["n"] = {"name": "kerb#11", "joins": "&"}  # (and those with the road to their south)
    legend["|"] = {"pick": [f"{n}_paved" for n in trees.STANDALONE]}
    legend["@"] = {"auto": "granite"}
    legend["/"] = {"name": "compass", "joins": "@"}
    legend.update(STREET_PIECES)
    for k in JOINS:
        item = legend[k]
        legend[k] = dict({"name": item} if isinstance(item, str) else item, joins="&")
    legend.update(prop_legend)
    g = onto_plazas(g, legend, {e["name"] for e in spec_mt})
    for k, m in enumerate(sorted(set(rims.values()))):  # the signs on the kerb's edge (Cyrillic letters: unused)
        legend[chr(0x410 + k)] = {"name": f"sign_paved_k{m}", "joins": "&"}
        for (x, y), mm in rims.items():
            if mm == m:
                g[y][x] = chr(0x410 + k)
    (HERE / "grid.txt").write_text("".join("".join(r) + "\n" for r in g))
    (HERE / "legend.json").write_text(json.dumps(legend, indent=1) + "\n")
    (HERE / "doors.json").write_text(json.dumps(d, indent=1) + "\n")
    print(f"{len(spec_mt)} metatiles in the spec; grid {MAP_W}x{MAP_H}; doors {d}")


if __name__ == "__main__":
    main()
