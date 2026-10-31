#!/usr/bin/env python3
"""Cerulean City after its concept (draw_plan.py and plan_stage1.txt): the town by the lake where Nugget Bridge comes
down (see draw_plan.py). It is 58x51 blocks, as before, and its exits stay where its neighbours meet it: Route 24's
bridge the top at columns 41-44, Route 4's road the left edge at rows 17-20, Route 9's the right edge at rows 28-30,
Route 5's the bottom at columns 21-24.

The pieces: the kit's, the Pokémon Center and the Mart (the kit's), Viridian's buildings and Route 2's cave mouth:
- bank 7: Viridian's Gym (the Gym) and its Trainer School (the Bike Shop);
- bank 9: Viridian's houses' palette, for the two family houses and the three small ones (the gardener's house),
  and Route 2's cave mouth (Cerulean Cave) drawn in it: the two colours the houses don't use are the cave's two
  that the palette has least like them, its others each the palette's nearest (``cave_mouth``). The seams to the
  three old routes need every bank from 10, so the cave can't have its own;
- the two holes into houses (the robbed house's and the badge house's back door) are lawn you step down from into
  the house (an arrow warp south: stand on it and walk into the wall).
Bank 8 is the kit's plants palette. The town is paved (KR-93): the kit's dressed stone round the buildings, which stand
on it (the paving under their see-through blocks; the Center and the Mart are the town's own copies of the kit's),
and the street pack's brick, in Cerulean's blues without its kerbs (bank 10), for the lakeside promenade, the sidewalk
down the road south, the ring round the pool and the paths; four cottages without doors are the family house in
blue (bank 11) and teal (bank 12), no new tiles. The paving, the brick, the cobbles and what stands in them are one
material for each other's edges.

Run from the repository root:  python3 project/art/cerulean-concept/make_art.py
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
import props
import streets

HERE = Path(__file__).resolve().parent
ART = HERE.parent
SECONDARY = "gTileset_CeruleanConcept"
MAP_W, MAP_H = 58, 51
SCHOOL_BANK, HOUSE_BANK = 7, 9
VB = ART / "viridian-concept/buildings"
# the buildings: their letters in the plan, where each comes from and its palette's bank
OWN = {"W": (VB / "viridian_gym", SCHOOL_BANK), "K": (VB / "trainer_school", SCHOOL_BANK),
       "H": (VB / "house_family", HOUSE_BANK), "X": (VB / "house_gardener", HOUSE_BANK)}
SHARED = {"Z": "pokemon_center", "L": "poke_mart"}
SIGN_BRICK = (19, 41)                  # trainer tips, the sign in the brick at the west canal's foot ("!")
HOLES = [(35, 18), (36, 18), (48, 7)]  # the robbed house's hole (from its backyard) and the badge house's back door
CUT_TREE = (49, 39)                    # the tree to cut, in the gap into the garden (an event, on the lawn)
NECK = [(22, 45), (23, 45)]            # where the lass and her Slowbro stand until the S.S. Ticket
GRUNT = (38, 17)                       # the Rocket in the backyard's way out...
GRUNT_GATE = [(38, 16), (38, 18)]      # ...and his triggers either side of him (stepping on one starts his battle)
NORTH = [(x, 0) for x in range(41, 45)]
WEST = [(0, y) for y in range(17, 21)]
EAST = [(MAP_W - 1, y) for y in range(28, 31)]
SOUTH = [(x, MAP_H - 1) for x in range(21, 25)]
WATER = set("~vr")
SOLID = set("T#bRoklSBcw_~vrWKHXZLY12@/fFunatie")
# the paving and the brick: what stands on them (the buildings but the two family houses and the cave, the lamps and
# the signs) and the cobbles are one material with them, so no edge between
WALK = "%"
PAVED = "WKXZL12@/"  # what stands on the paving
FENCE = "f"          # a fence on the paving (the kit's fence, its own blocks: on the paving, one with it)
FENCE_CHARS = "3456789"
# the town props (Kanto Town Props v0.1) by their letters in the plan; the footbridges with what is under them
PROPS = {"F": "fountain_3x3", "u": "bench_wood_south", "n": "bench_wood_north", "a": "bench_wood_west",
         "t": "flower_tub", "i": "litter_bin", "e": "bike_rack",
         "x": "bridge_ew_1_west", "y": "bridge_ew_1_middle", "z": "bridge_ew_1_east",
         "0": "bridge_ns_1_north", "m": "bridge_ns_1_middle", "j": "bridge_ns_1_south"}
BRIDGES = {"x": ("bridge_ew_1_west", "cerulean_brick#15"), "y": ("bridge_ew_1_middle", "pond#5"),
           "z": ("bridge_ew_1_east", "cerulean_brick#15"), "0": ("bridge_ns_1_north", "paving#15"),
           "m": ("bridge_ns_1_middle", "pond#10"), "j": ("bridge_ns_1_south", "cobble#15")}
SHARED_PAVED = {"Z": ("pokemon_center", "center"), "L": ("poke_mart", "mart")}
BRICK_BANK = 10
BRICK = {3: (104, 128, 168), 4: (136, 160, 200), 5: (176, 196, 224), 8: (72, 88, 120)}  # the pack's bricks, in blues
COTTAGES = {"1": ("cottage_blue", 11, {2: (40, 56, 96), 4: (64, 96, 160), 5: (104, 144, 200), 13: (72, 80, 112)}),
            "2": ("cottage_teal", 12, {2: (32, 72, 80), 4: (48, 120, 128), 5: (88, 168, 168), 13: (64, 96, 96)})}


def paved(idx) -> list[str]:
    """A picture's grounds on the paving, block by block (row by row): the paving under those with see-through
    pixels, the lawn (as before, so the same blocks) under the rest."""
    return ["paving#15" if (idx[y:y + 16, x:x + 16] == 0).any() else "grass"
            for y in range(0, idx.shape[0], 16) for x in range(0, idx.shape[1], 16)]


def cottage(idx):
    """The family house (5x4 blocks, door at 2,3) without its door, as Pewter's cottages: its porch's awning gone (the
    wall's 8x8 cell beside it), and the right-hand window copied into the door's place."""
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


def _mouth() -> buildings.Building:
    """Route 2's cave mouth (its pack names its door ``door_blocks``, which the kit's loader doesn't read)."""
    folder = ART / "route2-concept/buildings/diglett_cave"
    meta = json.loads((folder / "diglett_cave.json").read_text())
    with Image.open(folder / "diglett_cave.png") as im:
        idx, flat = np.array(im, np.uint8), im.getpalette()[:48]
    return buildings.Building("diglett_cave", idx, [tuple(flat[i:i + 3]) for i in range(0, 48, 3)],
                              tuple(meta["door_blocks"][0]), folder / "diglett_cave_door.png")


def cave_mouth(houses) -> tuple[list, buildings.Building]:
    """The houses' palette with the cave mouth's colours in the indices they don't use, and the mouth drawn in it:
    the two of its colours that leave the least error go in the spare indices, and its others each take the nearest
    of the palette's browns and greys (never its greens or oranges, which speckled the rock)."""
    m = _mouth()
    count = {int(i): int((m.idx == i).sum()) for i in np.unique(m.idx) if i}
    dist = lambda c, d: sum((a - b) ** 2 for a, b in zip(c, d))
    best = None
    for a in count:
        for b in count:
            if a >= b:
                continue
            pal = list(houses)
            pal[HOUSE_SPARE[0]], pal[HOUSE_SPARE[1]] = m.palette[a], m.palette[b]
            lut = list(range(16))
            lut[a], lut[b] = HOUSE_SPARE
            err = 0
            for i in count:
                if i not in (a, b):
                    lut[i] = min(CAVE_OK + HOUSE_SPARE, key=lambda j: dist(m.palette[i], pal[j]))
                    err += count[i] * dist(m.palette[i], pal[lut[i]])
            if best is None or err < best[0]:
                best = (err, pal, lut)
    _, pal, lut = best
    return pal, buildings.Building(m.name, np.array(lut, np.uint8)[m.idx], pal, m.door, m.door_frames)


CAVE_OK = (1, 2, 13, 11, 12)  # the houses' browns and greys the rock may use besides its own two (not 4-7, 9, 10)
HOUSE_SPARE = (3, 8)  # the indices of the houses' palette neither house uses


def plan() -> list[list[str]]:
    rows = (HERE / "plan_stage1.txt").read_text().split("\n")[:MAP_H]
    g = [list(r) for r in rows]
    assert len(g) == MAP_H and all(len(r) == MAP_W for r in g), "the plan is 58x51"
    return g


def load(letter: str) -> buildings.Building:
    if letter in SHARED:
        return kit.SHARED_BUILDINGS[SHARED[letter]][0]
    if letter == "Y":
        return _mouth()
    return buildings.load(OWN[letter][0])


def doors(g) -> dict[str, list[tuple[int, int]]]:
    """Each building's doors (a letter may stand for more than one building of its kind), west to east."""
    out = {}
    for letter in list(SHARED) + list(OWN) + ["Y"]:
        b = load(letter)
        bw, bh = b.idx.shape[1] // 16, b.idx.shape[0] // 16
        cells = {(x, y) for y, r in enumerate(g) for x, c in enumerate(r) if c == letter}
        tops = sorted((x, y) for x, y in cells if (x - 1, y) not in cells and (x, y - 1) not in cells)
        for x0, y0 in tops:
            assert {(x0 + i, y0 + j) for i in range(bw) for j in range(bh)} <= cells, f"{letter} at ({x0},{y0})"
            out.setdefault(letter, []).append((x0 + b.door[0], y0 + b.door[1]))
        assert len(tops) * bw * bh == len(cells), f"{letter}: the plan's footprints aren't {bw}x{bh}"
    return out


def reachable(g, starts, blocked=(), surf=False) -> set[tuple[int, int]]:
    """The blocks you can walk to from ``starts`` (and surf to, with ``surf``), not through ``blocked``."""
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
    """The town's rules:
    - only its four exits open onto the edges;
    - with the tree standing, the grunt in his way and the lass and her Slowbro in the neck, the town is everything
      walkable but the garden, the backyard, the yard, the cave's island and the road south past the neck;
    - the neck is the only way south; the grunt's way (past him or his triggers) the only way into the backyard (but
      its hole); the tree the
      only way into the garden; the badge house the only way into its yard; the island is reached only by surfing;
    - every door can be walked into from the block below it, every sign read from it."""
    edge = {(x, y) for y in range(MAP_H) for x in range(MAP_W) if x in (0, MAP_W - 1) or y in (0, MAP_H - 1)}
    assert {xy for xy in edge if g[xy[1]][xy[0]] not in SOLID} == set(NORTH + WEST + EAST + SOUTH), "only the exits"
    people = {CUT_TREE, GRUNT, *GRUNT_GATE, *NECK}
    town = reachable(g, [WEST[0]], people)
    assert set(NORTH + WEST + EAST) <= town, "the bridge and the roads east and west must meet in town"
    assert not set(SOUTH) & town, "the road south must go through the neck"
    assert set(SOUTH) <= reachable(g, [WEST[0]], people - set(NECK)), "the neck must open the road south"
    walk = {(x, y) for y in range(MAP_H) for x in range(MAP_W) if g[y][x] not in SOLID} - people
    backyard = reachable(g, [HOLES[0]], people)
    yard = reachable(g, [HOLES[2]], people)
    garden = reachable(g, [(49, 40)], people)
    south = reachable(g, [SOUTH[0]], people)
    island = reachable(g, [(6, 7)], people)
    for name, part in (("backyard", backyard), ("yard", yard), ("garden", garden), ("island", island)):
        assert not part & town, f"the {name} must not be reached from town"
    assert walk <= town | backyard | yard | garden | south | island, \
        f"blocks you can't reach: {sorted(walk - town - backyard - yard - garden - south - island)[:8]}"
    assert backyard <= reachable(g, [WEST[0]], {CUT_TREE, *NECK}), "the grunt's way out must lead into the backyard"
    assert garden <= reachable(g, [WEST[0]], people - {CUT_TREE}), "the garden must open when the tree is cut"
    sea = reachable(g, [WEST[0]], people | {HOLES[2]}, surf=True)
    assert island <= sea and not yard & sea, "the island must be reached by surfing, the yard not at all"
    for letter, ds in d.items():
        for x, y in ds:
            assert (x, y + 1) in walk, f"the door of {letter} at ({x},{y}) can't be walked into"
    for y in range(MAP_H):
        for x in range(MAP_W):
            if g[y][x] in "S/":
                assert (x, y + 1) in walk, f"the sign at ({x},{y}) can't be read"
    for x, y in HOLES:
        assert g[y + 1][x] in SOLID - WATER, f"the hole at ({x},{y}) must be against a wall"


def main() -> None:
    g = plan()
    d = doors(g)
    kit.check_forest(g)
    kit.check_water(g)
    check(g, d)
    for x, y in HOLES:
        g[y][x] = "^"
    g[SIGN_BRICK[1]][SIGN_BRICK[0]] = "!"
    base = kit.primary(HERE)  # the kit: the primary tileset every map shares
    spec_mt = list(base["metatiles"])
    pals = {}
    for letter, (folder, bank) in OWN.items():
        b = load(letter)
        pals.setdefault(bank, b.palette)
        if pals[bank] != b.palette:
            raise SystemExit(f"{folder.name}: its palette isn't the one bank {bank} has")
        sh = kit.Sheet(b.name, b.palette, bank, HERE, HERE, cols=b.idx.shape[1] // 16)
        sh.add(b.name, b.idx, tileset="secondary", **dict(b.entry(), **({"ground": paved(b.idx)}
                                                                         if letter in PAVED else {})))
        spec_mt += sh.write()
    for letter, (name, pal) in SHARED_PAVED.items():  # the kit's Center and Mart, the town's own copies on the paving
        b = kit.SHARED_BUILDINGS[name][0]
        sh = kit.Sheet(f"{name}_paved", kit.PALS[pal], kit.BANK[pal], HERE, HERE, cols=b.idx.shape[1] // 16)
        sh.add(f"{name}_paved", b.idx, tileset="secondary", **dict(b.entry(), ground=paved(b.idx)))
        spec_mt += sh.write()
    house = load("H")
    for letter, (name, bank, changes) in COTTAGES.items():
        pals[bank] = buildings.recolour(house.palette, changes)
        sh = kit.Sheet(name, pals[bank], bank, HERE, HERE, cols=house.idx.shape[1] // 16)
        sh.add(name, cottage(house.idx), tileset="secondary", solid=True, ground=paved(cottage(house.idx)),
               dedupe=True)
        spec_mt += sh.write()
    city = streets.city_palette()
    pals[BRICK_BANK] = [BRICK.get(i, c) for i, c in enumerate(city)]
    sh = kit.Sheet("cerulean_brick", pals[BRICK_BANK], BRICK_BANK, HERE, HERE, cols=8)
    sh.add("cerulean_brick#15", streets.block("brick", 15, 0, city), tileset="secondary", ground="grass")
    for k, v in enumerate(("center_b", "center_c"), 1):  # the plain brick's variants, spread by position
        sh.add(f"cerulean_brick#15~{k}", streets.piece("brick", v, city), tileset="secondary", ground="grass")
    spec_mt += sh.write()
    sh = kit.Sheet("lamp_paving", kit.PALS["plants"], kit.BANK["plants"], HERE, HERE, cols=1)
    sh.add("lamp_paving", kit.lamp(), tileset="secondary", ground="paving#15", solid=True, dedupe=True)
    spec_mt += sh.write()
    sh = kit.Sheet("sign_paving", kit.PALS["wood"], kit.BANK["wood"], HERE, HERE, cols=1)
    sh.add("sign_paving", kit.sign(), tileset="secondary", ground="paving#15", solid=True, dedupe=True)
    spec_mt += sh.write()
    sh = kit.Sheet("sign_brick", kit.PALS["wood"], kit.BANK["wood"], HERE, HERE, cols=1)  # the same sign on the brick
    sh.add("sign_brick", kit.sign(), tileset="secondary", ground="cerulean_brick#15", solid=True, dedupe=True)
    spec_mt += sh.write()
    fences = {}  # the fences on the paving, by the sides they join on (1 N, 2 E, 4 S, 8 W)
    for y in range(MAP_H):
        for x in range(MAP_W):
            if g[y][x] == FENCE:
                m = sum(b for b, (dx, dy) in ((1, (0, -1)), (2, (1, 0)), (4, (0, 1)), (8, (-1, 0)))
                        if 0 <= x + dx < MAP_W and 0 <= y + dy < MAP_H and g[y + dy][x + dx] == FENCE)
                fences.setdefault(m, []).append((x, y))
    assert len(fences) <= len(FENCE_CHARS), "more kinds of fence than characters for them"
    sh = kit.Sheet("fence_paving", kit.PALS["wood"], kit.BANK["wood"], HERE, HERE, cols=8)
    for (m, cells), ch in zip(sorted(fences.items()), FENCE_CHARS):
        sh.add(f"fence_paving#{m}", kit.fence(m), tileset="secondary", ground="paving#15", solid=True, dedupe=True)
        for x, y in cells:
            g[y][x] = ch
    spec_mt += sh.write()
    fence_names = {ch: f"fence_paving#{m}" for m, ch in zip(sorted(fences), FENCE_CHARS)}
    # the town props (kit/props.py): each on the paving, or the footbridges over the canals (their middles on the
    # water under them, their ends on the banks)
    placed = {name: paved(props.frames(name)[0]) for ch, name in PROPS.items() if ch not in BRIDGES}
    for ch, (name, under) in BRIDGES.items():
        placed[name] = under
    prop_entries, prop_anims = props.pieces(HERE, HERE, placed)
    spec_mt += prop_entries
    for letter in "HX":
        b = load(letter)
        assert not set(HOUSE_SPARE) & set(np.unique(b.idx)), f"{b.name} uses an index kept for the cave"
    pals[HOUSE_BANK], mouth = cave_mouth(pals[HOUSE_BANK])
    sh = kit.Sheet(mouth.name, mouth.palette, HOUSE_BANK, HERE, HERE, cols=mouth.idx.shape[1] // 16)
    dx, dy = mouth.door
    sh.add(mouth.name, mouth.idx, tileset="secondary", ground="grass", solid=True, open=[f"{dx},{dy}"],
           behaviors={f"{dx},{dy}": "MB_NON_ANIMATED_DOOR"})  # an open mouth: you walk in, as in Route 2
    sh.add("hole", np.zeros((16, 16), np.uint8), tileset="secondary", ground="lawn_a",
           behavior="MB_SOUTH_ARROW_WARP")  # lawn: walk south from it into the house
    spec_mt += sh.write()
    for e in spec_mt:  # sheets put "w"/"h" on everything; drop the 1x1 ones for readability
        if e["w"] == 1 and e["h"] == 1:
            del e["w"], e["h"]
    for bank, pal in pals.items():
        kit.write_palette(HERE / f"palette_{bank}.pal", pal)
    spec = {"version": "hns", "primary": kit.PRIMARY, "secondary": SECONDARY,
            "palettes": {"primary": base["palettes"],
                         "secondary": [f"palette_{SCHOOL_BANK}.pal", base["secondary_palettes"][8],
                                       f"palette_{HOUSE_BANK}.pal", f"palette_{BRICK_BANK}.pal"]
                         + [f"palette_{b}.pal" for _, b, _ in COTTAGES.values()]},
            "reserve": {"primary": base["reserve"]},
            "animations": base["animations"] + prop_anims,
            "field_effects": base["field_effects"],
            "metatiles": spec_mt}
    (HERE / "spec.json").write_text(json.dumps(spec, indent=1) + "\n")
    (HERE / "grid.txt").write_text("".join("".join(r) + "\n" for r in g))
    (HERE / "border.txt").write_text("TT\nTT\n")
    legend = dict(kit.LEGEND, **SHARED, **{k: load(k).name for k in OWN}, Y="diglett_cave")
    legend["^"] = "hole"
    legend.update({k: name for k, (name, _, _) in COTTAGES.items()}, **{"@": "lamp_paving", "/": "sign_paving", "!": "sign_brick"},
                  **{k: f"{n}_paved" for k, (n, _) in SHARED_PAVED.items()})
    legend.update({k: {"name": legend[k], "joins": WALK} for k in PAVED + "!"})
    legend.update({WALK: {"pick": ["cerulean_brick#15", "cerulean_brick#15~1", "cerulean_brick#15~2"]},
                   "=": {"auto": "cobble", "joins": WALK}, "p": {"auto": "paving", "joins": WALK},
                   # the bridge's planks and the dirt path meet the street without a lawn rim between
                   "d": {"auto": "dock", "joins": WALK}, ":": {"auto": "dirt", "joins": WALK},
                   "P": {"pick": ["paving#15", "paving#15~1", "paving#15~2"], "joins": WALK}})  # plain, no edges
    legend.update({ch: {"name": n, "joins": WALK} for ch, n in fence_names.items()})
    assert not set(PROPS) & set(legend), "a prop's character the legend has"
    legend.update({ch: {"name": n, "joins": "~" if n.endswith("_middle") else WALK} for ch, n in PROPS.items()})
    (HERE / "legend.json").write_text(json.dumps(legend, indent=1) + "\n")
    (HERE / "doors.json").write_text(json.dumps(d, indent=1) + "\n")
    print(f"{len(spec_mt)} metatiles in the spec; grid {MAP_W}x{MAP_H}; doors {d}")


if __name__ == "__main__":
    main()
