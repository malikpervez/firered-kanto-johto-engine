#!/usr/bin/env python3
"""Celadon City after its concept (draw_plan.py and plan_stage1.txt): Kanto's garden city (see draw_plan.py). It is
60x40 blocks, as old Celadon was; its joins: the boulevard's two ends, rows 20-23, meet Route 16's road (its rows
22-25, offset -2) at the left edge and Route 7's (its rows 10-13, offset 10) at the right.

The pieces: the kit's and its Pokémon Center; the Department Store, the Mansion, the hotel, the Game Corner and
Erika's Gym, from Kanto Buildings Remakes v0.3 (../packs/buildings_v0.3), in one palette (bank 9); Viridian's pond
keeper's house in its palette (bank 7) for the Prize Room, the restaurant and a house. The town's own tileset holds
384 tiles: the remakes take 290 of them, and one kind of house (55) fits beside them, two (102) don't. Bank 8 is the
kit's plants palette; 10 the street pack's city palette (Lucky Lane's brick, the compass); 11-12 stay free.

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
import buildings
import kit
import props
import streets

HERE = Path(__file__).resolve().parent
ART = HERE.parent
VB = ART / "viridian-concept/buildings"
SECONDARY = "gTileset_CeladonConcept"
MAP_W, MAP_H = 60, 40
HOUSE_BANK, CITY_BANK = 7, 9
WEST = [(0, y) for y in range(20, 24)]
EAST = [(MAP_W - 1, y) for y in range(20, 24)]
SOLID = set("T#bRoklSBcw_~vrDMOCGPEHY")
# the town props (Kanto Town Props v0.1, kit/props.py): (piece, x, y of its top-left block, the ground under it)
PROPS = [("bench_wood_south", 24, 3, "grass"), ("litter_bin", 27, 3, "grass"),  # in the park, looking at its flower bed
         ("bench_wood_south", 30, 32, "grass")]  # in the pond garden, looking out over the pond (the same bench: no new tiles)
STREETS_BANK = 10  # the pack's city palette (Part B: Lucky Lane's brick, the compass); 11-12 stay free
# the street pieces by their letters in the plan (the kit's, streets.py) and Celadon's own: its pavements, on the lawn
# on one side and the road on the other ("walk_s": the road south of it, "walk_n": north), the brick and the compass;
# the pavement, the brick, the compass and the dropped kerbs are one material ("n") for each other's edges
KIT_PIECES = {"1": "asphalt_to_cobble_W", "2": "asphalt_to_cobble_E", "-": "asphalt_dashed_H_boundary",
              "3": "crossing_road_EW", "4": "crossing_end_N", "5": "crossing_end_S", "7": "crossing_dropped_kerb_S",
              "9": "crossing_dropped_kerb_N", "%": "manhole"}
STREET_LEGEND = {"1": {"name": KIT_PIECES["1"], "joins": "="}, "2": {"name": KIT_PIECES["2"], "joins": "="},
                 "n": {"auto": "walk_s"}, "u": {"auto": "walk_n", "joins": "n"},
                 "^": {"auto": "brick", "joins": "n"}, "j": {"name": "brick_to_pavement_N", "joins": "n"},
                 "/": {"name": "compass", "joins": "n"}, "7": {"name": KIT_PIECES["7"], "joins": "n"},
                 "9": {"name": KIT_PIECES["9"], "joins": "n"}}
DOOR, BACK = "MB_ANIMATED_DOOR", "MB_SOUTH_ARROW_WARP"
# the buildings: their letters in the plan, their packs, their banks, and what each of their doors does (the
# Mansion's second is its back door, entered walking south from above)
R = buildings.REMAKES
BUILDINGS = {"D": (R / "department_store", CITY_BANK, [DOOR, DOOR]),
             "M": (R / "celadon_mansion", CITY_BANK, [DOOR, BACK]),
             "O": (R / "celadon_hotel", CITY_BANK, [DOOR]),
             "G": (R / "game_corner", CITY_BANK, [DOOR]),
             "Y": (R / "celadon_gym", CITY_BANK, [DOOR]),
             "P": (VB / "house_pond_keeper", HOUSE_BANK, [DOOR]),
             "E": (VB / "house_pond_keeper", HOUSE_BANK, [DOOR]),
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


def autotiled(g, legend) -> dict[str, set[tuple[int, int]]]:
    """The pieces pae map paint will ask for, as it works them out (a neighbour counts when it's in the same group,
    the map's edge counts; inside corners where both sides count and the diagonal doesn't): {auto: {(mask, corners)}}.
    Only these are drawn, so the city's tileset holds no piece the map doesn't show."""
    def group(c):
        it = legend.get(c)
        return it.get("joins", c) if isinstance(it, dict) else c

    def same(x, y, c):
        return not (0 <= x < MAP_W and 0 <= y < MAP_H) or group(g[y][x]) == group(c)
    out: dict[str, set[tuple[int, int]]] = {}
    for y in range(MAP_H):
        for x in range(MAP_W):
            it = legend.get(g[y][x])
            if not (isinstance(it, dict) and "auto" in it):
                continue
            c = g[y][x]
            mask = sum(bit for bit, (dx, dy) in ((1, (0, -1)), (2, (1, 0)), (4, (0, 1)), (8, (-1, 0)))
                       if same(x + dx, y + dy, c))
            corners = sum(bit for bit, (dx, dy), sides in ((1, (1, -1), 3), (2, (1, 1), 6), (4, (-1, 1), 12),
                                                          (8, (-1, -1), 9))
                          if mask & sides == sides and not same(x + dx, y + dy, c))
            out.setdefault(it["auto"], set()).add((mask, corners))
    return out


def walk(mask: int, corners: int, road: int) -> np.ndarray:
    """Celadon's pavement block: the kit's pavement (by its neighbours and inside corners), the lawn under its edges
    but the road (asphalt) under those on the ``road`` side (1 N, 4 S), so one row of pavement can have its kerb on
    the road and its edge on the lawn. Past a pavement's end (the columns its end cap leaves bare) the lawn runs on
    down to the road, as beside it: no tongue of asphalt beside the kerb's end, over the cobble at the city's
    entrances."""
    under = kit.lawn.tiles(kit.LAWN, kit.P0)["lawn_a"].copy()
    asphalt = streets.piece("asphalt", "center", kit.P0)
    top = streets.block("pavement", mask, corners, kit.P0)
    for r, rows in ((1, slice(0, 8)), (4, slice(8, 16))):
        if road & r:
            kerb = np.any(top[rows] != 0, axis=0)  # the columns the pavement covers on the road's side
            under[rows, :][:, kerb] = asphalt[rows, :][:, kerb]
    return np.where(top != 0, top, under).astype(np.uint8)


def edged_compass(pal) -> np.ndarray:
    """The compass set in Lucky Lane (2x2, rows 30-31), inlaid in the brick: the street's edges run across it (the lawn
    strip and its line along the top, as brick with no brick north of it draws them; the kerb lines along the bottom),
    its four corners are the brick's own, and the pale ground round the diamond is the brick's dark red. It takes no
    more tiles than the plain compass did (the town's tileset is full): the corners are the brick's tiles, and the
    rest stays mirror-symmetric, so its tiles repeat flipped."""
    c = streets.piece("mosaic", "compass_2x2", pal).copy()
    c[c == 13] = 3                                   # the pale ground round the diamond: the brick's dark red
    top, bottom = np.tile(streets.block("brick", 14, 0, pal), 2), np.tile(streets.block("brick", 11, 0, pal), 2)
    plain = streets.block("brick", 15, 0, pal)
    for x0 in (0, 24):                               # the corners: the brick's own (the diamond doesn't reach them)
        c[:8, x0:x0 + 8] = top[:8, x0:x0 + 8]
        c[24:, x0:x0 + 8] = bottom[8:, x0:x0 + 8]
    for r in np.flatnonzero(np.any(top[:, :16] != plain, axis=1)):     # the top edge's rows, across the middle
        c[r, 8:24] = top[r, 8:24]
    for r in np.flatnonzero(np.any(bottom[:, :16] != plain, axis=1)):  # the kerb lines', across the middle
        c[16 + r, 8:24] = bottom[r, 8:24]
    return c


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
    g = plan()
    prop_legend, prop_grounds = props.place(g, PROPS, SOLID)
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
    # the streets (KR-91): Celadon's pavements and Lucky Lane's brick, only the pieces the map shows
    legend = {**kit.LEGEND, **SHARED, **{k: load(k)[0].name for k in BUILDINGS}, **KIT_PIECES, **STREET_LEGEND}
    used = autotiled(g, legend)
    sh = kit.Sheet("walks", kit.P0, 0, HERE, HERE, cols=8)
    for name, road in (("walk_s", 4), ("walk_n", 1)):
        for m, c in sorted(used.get(name, ())):
            sh.add(f"{name}#{m}.{c}" if c else f"{name}#{m}", walk(m, c, road), tileset="secondary", dedupe=True)
    spec_mt += sh.write()
    pals[STREETS_BANK] = streets.city_palette()
    sh = kit.Sheet("brick", pals[STREETS_BANK], STREETS_BANK, HERE, HERE, cols=8)
    for m, c in sorted(used.get("brick", ())):  # on the lawn, as the pack draws it (its edges show the ground)
        sh.add(f"brick#{m}.{c}" if c else f"brick#{m}", streets.block("brick", m, c, pals[STREETS_BANK]),
               tileset="secondary", ground="grass", dedupe=True)
    sh.add("brick_to_pavement_N", streets.piece("brick", "to_pavement_N", pals[STREETS_BANK]), tileset="secondary",
           ground="grass")
    sh.add("compass", edged_compass(pals[STREETS_BANK]), tileset="secondary", ground="grass")
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
                         "secondary": [f"palette_{HOUSE_BANK}.pal", base["secondary_palettes"][8],
                                       f"palette_{CITY_BANK}.pal", f"palette_{STREETS_BANK}.pal"]},
            "reserve": {"primary": base["reserve"]},
            "animations": base["animations"] + prop_anims,
            "field_effects": base["field_effects"],
            "metatiles": spec_mt}
    (HERE / "spec.json").write_text(json.dumps(spec, indent=1) + "\n")
    (HERE / "grid.txt").write_text("".join("".join(r) + "\n" for r in g))
    (HERE / "border.txt").write_text("TT\nTT\n")
    legend.update(prop_legend)
    (HERE / "legend.json").write_text(json.dumps(legend, indent=1) + "\n")
    (HERE / "doors.json").write_text(json.dumps(d, indent=1) + "\n")
    print(f"{len(spec_mt)} metatiles in the spec; grid {MAP_W}x{MAP_H}; doors {d}")


if __name__ == "__main__":
    main()
