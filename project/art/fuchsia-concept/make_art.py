#!/usr/bin/env python3
"""Fuchsia City after its concept (draw_plan.py and plan_stage1.txt): Kanto's town of the Safari Zone, by the southern
sea (see draw_plan.py). It is 48x40 blocks, as before, and its joins stay where they were: Route 18 at the left edge
(rows 18-20, offset 10), Route 15 at the right (rows 20-23, offset 16), Route 19 below the bottom edge (columns
19-28, offset 12).

The pieces: the kit's and its Pokémon Center and Mart; the Safari Zone's gate lodge and Koga's Gym (Kanto Buildings
Remakes v0.3, ../packs/buildings_v0.3) in Saffron's buildings' palette (bank 9); Viridian's houses in theirs (bank 7:
the gardener's for the Safari Zone's office and two houses, the family's for the Warden's, and the remakes' pond
keeper's house with a back door for the house with the pond garden). Bank 8 is the kit's plants palette.

Fuchsia's own ground and details are Kanto Fuchsia City v0.1 (../packs/fuchsia_v0.1, ../kit/fuchsia.py): one
sandstone through every street, the Safari plaza, its avenue and the zoo's walks (in a palette of its own, bank 10),
meeting the routes' cobble at the west and east edges and the beach path's dirt in half-block joins; the pens and
the pond garden fenced in bamboo palisade, an exhibit board in each pen's fence line, and fuchsia bushes in the
gardens and beside the houses (in the lodge's palette and the kit's plants). The sandstone has the same edge
wherever it meets the lawn; it runs straight up to the lodge's front. The house by the Center is the gardener's (it
was the pond keeper's): the town's tileset was nearly full, and this makes room for the pack (the owner's call,
November 3).

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
import fuchsia
import props

HERE = Path(__file__).resolve().parent
VB = HERE.parent / "viridian-concept/buildings"
FB = buildings.REMAKES
SECONDARY = "gTileset_FuchsiaConcept"
MAP_W, MAP_H = 48, 40
HOUSE_BANK, TOWN_BANK = 7, 9
WEST = [(0, y) for y in range(18, 21)]
EAST = [(MAP_W - 1, y) for y in range(20, 24)]
SOUTH = [(x, MAP_H - 1) for x in range(18, 30)]
SOLID = set("T#bRoklSBcw_~vrAGZLOWHJK")
# the town props (Kanto Town Props v0.1, kit/props.py): (piece, x, y of its top-left block, the ground under it:
# "sandstone" is the sandstone's block there, found when it's laid)
PROPS = [("statue_guardian", 18, 8, "sandstone"), ("flower_tub", 21, 7, "sandstone"), ("flower_tub", 25, 7, "sandstone"),
         ("bench_stone", 21, 13, "sandstone"), ("bench_stone", 25, 13, "sandstone"), ("litter_bin", 21, 17, "sandstone"),
         ("picnic_table", 30, 23, "grass")]  # (a picnic table in the park, clear of Cubone's walk)
# Fuchsia's ground (kit/fuchsia.py): the sandstone takes every street, the plaza, the avenue and the zoo's walks (the
# plan's cobble and paving, and its dirt on rows 9-10); its joins: the routes' cobble at the west and east edges,
# the beach path's dirt below the shore street
WALKS = (9, 10)
JOINS = {"to_cobble_W": {(0, y) for y in range(18, 21)}, "to_cobble_E": {(MAP_W - 1, y) for y in range(20, 24)},
         "to_dirt_S": {(x, 33) for x in range(18, 30)}}
# the beach path's top row runs on from the sandstone's dirt half without a lawn lip (and counts as dirt for the rest
# of the path below it)
BEACH_MOUTH = {(x, 34): "\u0255" for x in range(19, 29)}
BEACH_MOUTH[(18, 34)], BEACH_MOUTH[(29, 34)] = "\u0254", "\u0256"
JOIN_LEGEND = {"\u0254": {"name": "dirt#7", "joins": ":"}, "\u0255": {"name": "dirt#15", "joins": ":"},
               "\u0256": {"name": "dirt#13", "joins": ":"}}
# the pens' signs, in their fence lines: an exhibit board each (the signs' events stay where they are)
BOARDS = [(5, 8), (13, 8), (32, 8), (38, 8), (37, 16)]
# fuchsia bushes: along the back of the two flower beds west of the avenue and of the park's flower garden, beside
# the Mart and the office, and beside the house at the shore street's east end (none in the lanes up between the houses:
# a bush there would make someone's walk longer, which the checks stop)
BUSHES = ([(x, 13) for x in range(10, 13)] + [(x, 15) for x in range(17, 20)] + [(15, 23), (17, 23), (19, 23)]
          + [(8, 16), (27, 16), (32, 16), (40, 31)])
DOOR, BACK = "MB_ANIMATED_DOOR", "MB_SOUTH_ARROW_WARP"
# the buildings: their letters in the plan, their packs, their banks, and what each of their doors does (the house
# with the pond garden has a back door, entered walking south from the garden)
BUILDINGS = {"A": (FB / "safari_gate", TOWN_BANK, [DOOR]),
             "G": (FB / "fuchsia_gym", TOWN_BANK, [DOOR]),
             "O": (VB / "house_gardener", HOUSE_BANK, [DOOR]),
             "H": (VB / "house_gardener", HOUSE_BANK, [DOOR]),
             "W": (VB / "house_family", HOUSE_BANK, [DOOR]),
             "J": (VB / "house_gardener", HOUSE_BANK, [DOOR]),
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


def steps(g, start) -> dict[tuple[int, int], int]:
    """How many steps it is from ``start`` to every block you can walk to (the trees cut)."""
    dist, todo = {start: 0}, deque([start])
    while todo:
        x, y = todo.popleft()
        for n in ((x + 1, y), (x - 1, y), (x, y + 1), (x, y - 1)):
            if 0 <= n[0] < MAP_W and 0 <= n[1] < MAP_H and n not in dist and g[n[1]][n[0]] not in SOLID:
                dist[n] = dist[x, y] + 1
                todo.append(n)
    return dist


def check(g, d, signs) -> None:
    """The town's rules: only the three roads open onto the edges; the zoo's pens are closed; with the trees cut and the house walked through,
    everything walkable is reached from the main street; without the trees, all but the flower garden, and the pond
    garden only through the house; the trees stand more than 8 blocks from the edges you come in by (KR-45); every
    door can be walked into (the back door from the garden), every sign (``signs``: the pens' boards among them)
    read, the hidden item found; the Friends' camp is open ground."""
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
    for x, y in signs:
        assert g[y][x] in SOLID and (x, y + 1) in every, f"the sign at ({x},{y}) can't be read"
    x, y = HIDDEN
    assert HIDDEN in every and any(n in every for n in ((x + 1, y), (x - 1, y), (x, y + 1), (x, y - 1)))
    assert set(CAMP) <= outside, "the Friends' camp must be open ground"


def lay_fuchsia(g, prop_legend: dict, prop_grounds: dict) -> dict:
    """Fuchsia's own ground and details (../kit/fuchsia.py) into the plan: the sandstone over the plan's cobble, paving
    and zoo walks (and under the props standing on them), the palisade over its fences, a board in each pen's fence
    line and the fuchsia bushes. What stands on the sandstone takes its block there as its ground (another of a piece
    where the ground differs: "piece~2")."""
    letter_of = {(v if isinstance(v, str) else v["name"]): k for k, v in prop_legend.items()}
    on_sand = {}
    for piece, x, y, ground, *_ in PROPS:
        if ground == "sandstone":
            fp = props.PIECES[piece][1]["footprint_blocks"]
            on_sand[piece, x, y] = [(xx, yy) for yy in range(y, y + fp["height"]) for xx in range(x, x + fp["width"])]
    sand = {(x, y) for y in range(MAP_H) for x in range(MAP_W)
            if g[y][x] in "=p" or (g[y][x] == ":" and y in WALKS)} | {c for cells in on_sand.values() for c in cells}
    fences = {(x, y) for y in range(MAP_H) for x in range(MAP_W) if g[y][x] == "#"}
    assert all(g[y][x] == "S" for x, y in BOARDS), "the boards go where the pens' signs are"
    assert all(g[y][x] in ".*" for x, y in BUSHES), "the bushes stand on the lawn or in the flowers"
    lodge = {(x, y) for y in range(MAP_H) for x in range(MAP_W) if g[y][x] == "A"}
    walks_before = steps(g, STREET)
    fu = fuchsia.lay(g, sandstone=sand, joins=JOINS, level=lodge, palisade=fences,
                     details=[("exhibit_board", x, y) for x, y in BOARDS] + [("fuchsia_bush", x, y) for x, y in BUSHES],
                     town_palette=load("A")[0].palette, out=HERE, spec_dir=HERE)
    grounds_of: dict[str, list] = {}
    for (piece, x, y), cells in on_sand.items():
        under = [fu["ground"][c] for c in cells]
        seen = grounds_of.setdefault(piece, [])
        if under not in seen:
            seen.append(under)
        name = piece if seen.index(under) == 0 else f"{piece}~{seen.index(under) + 1}"
        prop_grounds[name] = under if len(under) > 1 else under[0]
        if name not in letter_of:  # a character of its own for it
            letter_of[name] = next(c for c in props.POOL if c not in prop_legend)
            prop_legend[letter_of[name]] = name
            if letter_of[piece] in SOLID:
                SOLID.add(letter_of[name])
        for xx, yy in cells:  # lay wrote the ground's character over it: the piece's again
            g[yy][xx] = letter_of[name]
    SOLID.update(fu["solid"])
    walks = steps(g, STREET)
    longer = sorted(xy for xy, n in walks.items() if walks_before.get(xy) != n)
    assert not longer and set(walks_before) - set(walks) == set(BUSHES), \
        f"the bushes stand in someone's way: the walk to {longer[:6]} is longer"
    return fu


def main() -> None:
    g = plan()
    signs = [(x, y) for y in range(MAP_H) for x in range(MAP_W) if g[y][x] == "S"]
    prop_legend, prop_grounds = props.place(g, PROPS, SOLID)
    d = doors(g)
    kit.check_forest(g)
    kit.check_water(g)
    for (x, y), ch in BEACH_MOUTH.items():
        assert g[y][x] == ":", f"({x},{y}) is '{g[y][x]}', not the beach path: the joins moved"
        g[y][x] = ch
    fu = lay_fuchsia(g, prop_legend, prop_grounds)
    check(g, d, signs)
    base = kit.primary(HERE)  # the kit: the primary tileset every map shares
    spec_mt = list(base["metatiles"]) + fu["entries"]
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
    prop_entries, prop_anims = props.pieces(HERE, HERE, prop_grounds)
    spec_mt += prop_entries
    for e in spec_mt:  # sheets put "w"/"h" on everything; drop the 1x1 ones for readability
        if e["w"] == 1 and e["h"] == 1:
            del e["w"], e["h"]
    for bank, pal in pals.items():
        kit.write_palette(HERE / f"palette_{bank}.pal", pal)
    assert fu["palette"], "the pack's sandstone is in a palette of its own"
    kit.write_palette(HERE / f"palette_{fuchsia.NEW_BANK}.pal", fu["palette"])
    spec = {"version": "hns", "primary": kit.PRIMARY, "secondary": SECONDARY,
            "palettes": {"primary": base["palettes"],
                         "secondary": [f"palette_{HOUSE_BANK}.pal", base["secondary_palettes"][8],
                                       f"palette_{TOWN_BANK}.pal", f"palette_{fuchsia.NEW_BANK}.pal"]},
            "reserve": {"primary": base["reserve"]},
            "animations": base["animations"] + prop_anims,
            "field_effects": base["field_effects"],
            "metatiles": spec_mt}
    (HERE / "spec.json").write_text(json.dumps(spec, indent=1) + "\n")
    (HERE / "grid.txt").write_text("".join("".join(r) + "\n" for r in g))
    (HERE / "border.txt").write_text("TT\nTT\n")
    legend = dict(kit.LEGEND, **SHARED, **{k: load(k)[0].name for k in BUILDINGS})
    legend.update(prop_legend)
    legend.update(fu["legend"])
    legend.update(JOIN_LEGEND)
    (HERE / "legend.json").write_text(json.dumps(legend, indent=1) + "\n")
    (HERE / "doors.json").write_text(json.dumps(d, indent=1) + "\n")
    print(f"{len(spec_mt)} metatiles in the spec; grid {MAP_W}x{MAP_H}; doors {d}")


if __name__ == "__main__":
    main()
