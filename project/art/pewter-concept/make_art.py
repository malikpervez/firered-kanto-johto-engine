#!/usr/bin/env python3
"""Pewter City after its concept (draw_plan.py and plan_stage1.txt): the grey-stone town at the foot of the mountains
(see draw_plan.py). It is 52x44 blocks, as before, and its exits stay where they met its neighbours: Route 2's road
leaves the bottom at columns 22-25, Route 3's the right edge at rows 24-27.

The pieces: the kit's, its cliffs (cliffs.py, bank 9), the Pokémon Center and the Mart (the kit's), and buildings
from the towns before, in Pewter's colours:
- bank 7, Pewter's stone: the League Front Gate's pavilion (Route 22's pack) is the Museum of Science, and Brock's
  Gym (Kanto Buildings Remakes v0.3, ../packs/buildings_v0.3) is drawn in the pavilion's palette;
- bank 10: Viridian's houses' palette, for the Museum's annex and the two houses: all three are Viridian's family
  house, because the secondary tileset's 384 tiles don't fit another kind of house beside the Museum and the Gym
  (and leave room for the seam to Route 3).
Bank 8 is the kit's plants palette; 11 and 12 are the family house recoloured, slate and clay, for the cottages
without doors (the house's own tiles, a window where its door was: no new tiles).

Run from the repository root:  python3 project/art/pewter-concept/make_art.py
It writes sheets/, the palettes, spec.json, grid.txt, border.txt, legend.json and doors.json next to itself; build.sh
turns them into the game's tileset and map with pae.
"""
import json
import shutil
import sys
from collections import deque
from dataclasses import replace
from pathlib import Path


sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "kit"))
import buildings
import cliffs
import kit

HERE = Path(__file__).resolve().parent
ART = HERE.parent
SECONDARY = "gTileset_PewterConcept"
MAP_W, MAP_H = 52, 44
STONE_BANK, CLIFF_BANK, HOUSE_BANK = 7, 9, 10
# the buildings: their letters in the plan, where each comes from and its palette's bank
OWN = {"U": (ART / "route22-concept/buildings/league_front_gate", STONE_BANK),
       "W": (buildings.REMAKES / "pewter_gym", STONE_BANK),
       "Y": (ART / "viridian-concept/buildings/house_family", HOUSE_BANK),
       "H": (ART / "viridian-concept/buildings/house_family", HOUSE_BANK),
       "X": (ART / "viridian-concept/buildings/house_family", HOUSE_BANK)}  # the same house twice: no more tiles
SHARED = {"Z": "pokemon_center", "L": "poke_mart"}
CUT_TREE = (32, 12)  # the tree to cut, in the gap into the annex's yard (an event, on the lawn)
SOUTH, EAST = [(x, MAP_H - 1) for x in range(22, 26)], [(MAP_W - 1, y) for y in range(24, 28)]
GUIDE_GATE = [(43, y) for y in range(25, 28)]  # the Gym guide's triggers across the road east (he stands at 43,24)
SOLID = set("T#bRoklSBcw_~vrUWYHXZL12") | cliffs.SOLID
# the cottages: the family house with a third window where its door was, recoloured (the same indices, so the same
# tiles in other banks): their letters, names, banks and colour changes (2 the roof's outline, 4-5 its tiles, 13 its
# trim, shutters and woodwork; 10-12 the walls)
COTTAGES = {"1": ("cottage_slate", 11, {2: (48, 56, 72), 4: (88, 104, 128), 5: (128, 148, 168), 13: (80, 88, 104)}),
            "2": ("cottage_clay", 12, {2: (72, 48, 40), 4: (152, 104, 72), 5: (192, 144, 104), 13: (112, 80, 56),
                                       10: (184, 168, 136), 11: (224, 208, 176), 12: (240, 232, 208)})}


def cottage(idx):
    """The family house (5x4 blocks, door at 2,3) without its door: its porch's awning gone (the wall's 8x8 cell
    beside it), and the right-hand window copied into the door's place, so every cell is one the house has."""
    out = idx.copy()

    def cell(r, c):
        return idx[r * 8:r * 8 + 8, c * 8:c * 8 + 8]

    def put(r, c, t):
        out[r * 8:r * 8 + 8, c * 8:c * 8 + 8] = t
    for c in (3, 4, 5, 6):
        put(4, c, cell(5, 3))
    for r in (5, 6):
        for k, c in enumerate((7, 8)):
            put(r, 4 + k, cell(r, c))
    for c in (4, 5):
        put(7, c, cell(7, 3))
    put(4, 4, cell(4, 7)); put(4, 5, cell(4, 8))
    return out


def plan() -> list[list[str]]:
    rows = (HERE / "plan_stage1.txt").read_text().split("\n")[:MAP_H]
    g = [list(r) for r in rows]
    assert len(g) == MAP_H and all(len(r) == MAP_W for r in g), "the plan is 52x44"
    return g


def load(letter: str) -> buildings.Building:
    if letter in SHARED:
        return kit.SHARED_BUILDINGS[SHARED[letter]][0]
    folder = OWN[letter][0]
    b = buildings.load(folder)
    return b


def fit(g):
    """The plan as the kit builds it: the cliffs are their tops and faces (cliffs.layout); a lamp is two blocks (its
    head above its foot, both ``l`` in the plan)."""
    cliffs.layout(g)
    return g


def doors(g) -> dict[str, tuple[int, int]]:
    out = {}
    for letter in list(SHARED) + list(OWN):
        cells = [(x, y) for y, r in enumerate(g) for x, c in enumerate(r) if c == letter]
        x0, y0 = min(x for x, _ in cells), min(y for _, y in cells)
        b = load(letter)
        bh, bw = b.idx.shape[0] // 16, b.idx.shape[1] // 16
        assert sorted(cells) == sorted((x0 + i, y0 + j) for i in range(bw) for j in range(bh)), \
            f"{letter}: the plan's footprint isn't {bw}x{bh}"
        out[letter] = (x0 + b.door[0], y0 + b.door[1])
    return out


def doors_of() -> dict[str, tuple[int, int]]:
    """Each building's door on the map (for escort.py)."""
    return doors(fit(plan()))


def reachable(g, start, blocked=()) -> set[tuple[int, int]]:
    seen, todo = {start}, deque([start])
    while todo:
        x, y = todo.popleft()
        for n in ((x + 1, y), (x - 1, y), (x, y + 1), (x, y - 1)):
            if 0 <= n[0] < MAP_W and 0 <= n[1] < MAP_H and n not in seen and n not in blocked and \
                    g[n[1]][n[0]] not in SOLID:
                seen.add(n)
                todo.append(n)
    return seen


def check(g, d) -> None:
    """The town's rules: only its two exits open onto the edges; everything walkable is reached from Route 2's road
    (the tree to cut standing); every door can be walked into from the block below it and every sign read from it;
    the annex's yard opens only by cutting the tree; the road east can't be left without crossing the Gym guide's
    triggers (or him)."""
    edge = {(x, y) for y in range(MAP_H) for x in range(MAP_W) if x in (0, MAP_W - 1) or y in (0, MAP_H - 1)}
    assert {xy for xy in edge if g[xy[1]][xy[0]] not in SOLID} == set(SOUTH + EAST), "only the exits open"
    town = reachable(g, SOUTH[0], {CUT_TREE})
    walk = {(x, y) for y in range(MAP_H) for x in range(MAP_W) if g[y][x] not in SOLID} - {CUT_TREE}
    yard = walk - town
    annex = d["Y"]
    assert (annex[0], annex[1] + 1) in yard, "the annex's door must be behind the tree"
    assert yard <= reachable(g, SOUTH[0]), "the yard must open when the tree is cut"
    for letter, (x, y) in d.items():
        if letter != "Y":
            assert (x, y + 1) in town, f"the door of {letter} at ({x},{y}) can't be reached"
    for y in range(MAP_H):
        for x in range(MAP_W):
            if g[y][x] == "S":
                assert (x, y + 1) in town | yard, f"the sign at ({x},{y}) can't be read"
    assert not set(EAST) & reachable(g, SOUTH[0], set(GUIDE_GATE) | {(43, 24)}), "the road east goes round the guide"


def main() -> None:
    g = fit(plan())
    d = doors(g)
    kit.check_forest(g)
    kit.check_water(g)
    check(g, d)
    base = kit.primary(HERE)  # the kit: the primary tileset every map shares
    spec_mt = list(base["metatiles"])
    rock = kit.Sheet("rock_cliff", cliffs.PAL, CLIFF_BANK, HERE, HERE)
    char_of = cliffs.add(rock, g, extras=())
    spec_mt += rock.write()
    pals = {}
    for letter, (folder, bank) in OWN.items():
        b = load(letter)
        if any(load(k).name == b.name for k in list(OWN)[:list(OWN).index(letter)]):
            continue  # a building already on the sheet
        pals.setdefault(bank, b.palette)
        if pals[bank] != b.palette:
            raise SystemExit(f"{folder.name}: its palette isn't the one bank {bank} has")
        sh = kit.Sheet(b.name, b.palette, bank, HERE, HERE, cols=b.idx.shape[1] // 16)
        sh.add(b.name, b.idx, tileset="secondary", **b.entry())
        spec_mt += sh.write()
    house = load("X")
    for letter, (name, bank, changes) in COTTAGES.items():
        pals[bank] = buildings.recolour(house.palette, changes)
        sh = kit.Sheet(name, pals[bank], bank, HERE, HERE, cols=house.idx.shape[1] // 16)
        sh.add(name, cottage(house.idx), tileset="secondary", ground="grass", solid=True, dedupe=True)
        spec_mt += sh.write()
    for e in spec_mt:  # sheets put "w"/"h" on everything; drop the 1x1 ones for readability
        if e["w"] == 1 and e["h"] == 1:
            del e["w"], e["h"]
    for bank, pal in pals.items():
        kit.write_palette(HERE / f"palette_{bank}.pal", pal)
    kit.write_palette(HERE / f"palette_{CLIFF_BANK}.pal", cliffs.PAL)
    spec = {"version": "hns", "primary": kit.PRIMARY, "secondary": SECONDARY,
            "palettes": {"primary": base["palettes"],
                         "secondary": [f"palette_{STONE_BANK}.pal", base["secondary_palettes"][8],
                                       f"palette_{CLIFF_BANK}.pal", f"palette_{HOUSE_BANK}.pal"]
                         + [f"palette_{b}.pal" for _, b, _ in COTTAGES.values()]},
            "reserve": {"primary": base["reserve"]},
            "animations": base["animations"],
            "field_effects": base["field_effects"],
            "metatiles": spec_mt}
    (HERE / "spec.json").write_text(json.dumps(spec, indent=1) + "\n")
    (HERE / "grid.txt").write_text("".join("".join(r) + "\n" for r in g))
    (HERE / "border.txt").write_text("TT\nTT\n")
    legend = dict(kit.LEGEND, **SHARED, **{k: load(k).name for k in OWN})
    legend.update(cliffs.legend(char_of))
    legend.update({k: name for k, (name, _, _) in COTTAGES.items()})
    (HERE / "legend.json").write_text(json.dumps(legend, indent=1) + "\n")
    (HERE / "doors.json").write_text(json.dumps({load(k).name: v for k, v in d.items()}, indent=1) + "\n")
    print(f"{len(spec_mt)} metatiles in the spec; grid {MAP_W}x{MAP_H}; doors {d}")


if __name__ == "__main__":
    main()
