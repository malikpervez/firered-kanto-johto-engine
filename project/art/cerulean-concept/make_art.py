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
Bank 8 is the kit's plants palette; 10-12 stay free for the seams to Routes 5, 9 and 24 (not rebuilt yet).

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
SOLID = set("T#bRoklSBcw_~vrWKHXZLY")


def _mouth() -> buildings.Building:
    """Route 2's cave mouth (its pack names its door ``door_blocks``, which the kit's loader doesn't read)."""
    folder = ART / "route2-concept/buildings/diglett_cave"
    meta = json.loads((folder / "diglett_cave.json").read_text())
    with Image.open(folder / "diglett_cave.png") as im:
        idx, flat = np.array(im, np.uint8), im.getpalette()[:48]
    return buildings.Building("diglett_cave", idx, [tuple(flat[i:i + 3]) for i in range(0, 48, 3)],
                              tuple(meta["door_blocks"][0]), folder / "diglett_cave_door.png")


def cave_mouth(houses) -> tuple[list, buildings.Building]:
    """The houses' palette with the cave mouth's colours in the indices they don't use, and the mouth drawn in it."""
    m = _mouth()
    used = set(range(16)) - set(HOUSE_SPARE)
    pal = list(houses)
    near = lambda c, idxs: min(idxs, key=lambda j: sum((a - b) ** 2 for a, b in zip(c, pal[j])))
    dist = lambda c, j: sum((a - b) ** 2 for a, b in zip(c, pal[j]))
    count = {int(i): int((m.idx == i).sum()) for i in np.unique(m.idx) if i}
    worst = sorted(count, key=lambda i: -count[i] * dist(m.palette[i], near(m.palette[i], used - {0})))
    lut = list(range(16))
    for i, spare in zip(worst, HOUSE_SPARE):
        pal[spare] = m.palette[i]
        lut[i] = spare
    for i in count:
        if lut[i] == i:
            lut[i] = near(m.palette[i], range(1, 16))
    return pal, buildings.Building(m.name, np.array(lut, np.uint8)[m.idx], pal, m.door, m.door_frames)


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
            if g[y][x] == "S":
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
                                       f"palette_{HOUSE_BANK}.pal"]},
            "reserve": {"primary": base["reserve"]},
            "animations": base["animations"],
            "field_effects": base["field_effects"],
            "metatiles": spec_mt}
    (HERE / "spec.json").write_text(json.dumps(spec, indent=1) + "\n")
    (HERE / "grid.txt").write_text("".join("".join(r) + "\n" for r in g))
    (HERE / "border.txt").write_text("TT\nTT\n")
    legend = dict(kit.LEGEND, **SHARED, **{k: load(k).name for k in OWN}, Y="diglett_cave")
    legend["^"] = "hole"
    (HERE / "legend.json").write_text(json.dumps(legend, indent=1) + "\n")
    (HERE / "doors.json").write_text(json.dumps(d, indent=1) + "\n")
    print(f"{len(spec_mt)} metatiles in the spec; grid {MAP_W}x{MAP_H}; doors {d}")


if __name__ == "__main__":
    main()
