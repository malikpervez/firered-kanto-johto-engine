#!/usr/bin/env python3
"""Lavender Town after its concept (draw_plan.py and plan_stage1.txt): the quiet town in a hollow of the hills (see
draw_plan.py). It is 38x32 blocks (old Lavender was 38x31), as wide as before; its joins stay where its neighbours meet
it: Route 10's road the top at columns 12-16 (Route 10's 16-20, offset -4), Route 8's the left edge at rows 9-11 (Route
8's 13-15, offset -4), Route 12's the bottom at columns 13-15 (Route 12's 11-13, offset 2; it was -2, the old town
sitting 4 blocks further east over Route 12).

The pieces: the kit's, the Pokémon Center and the Mart (the kit's), Viridian's three houses in their palette (bank 7),
and Pokémon Tower (Kanto Buildings Remakes v0.3, ../packs/buildings_v0.3) in a palette of its own (bank 9).
Bank 8 is the kit's plants palette; 10-12 stay free for the seams to old Routes 8 and 12.

Run from the repository root:  python3 project/art/lavender-concept/make_art.py
It writes sheets/, the palettes, spec.json, grid.txt, border.txt, legend.json and doors.json next to itself; build.sh
turns them into the game's tileset and map with pae.
"""
import json
import sys
from collections import deque
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "kit"))
import buildings
import kit
import props

HERE = Path(__file__).resolve().parent
ART = HERE.parent
SECONDARY = "gTileset_LavenderConcept"
MAP_W, MAP_H = 38, 32
HOUSE_BANK, TOWER_BANK = 7, 9
VB = ART / "viridian-concept/buildings"
TOWER = buildings.REMAKES / "pokemon_tower"
NORTH = [(x, 0) for x in range(12, 17)]
WEST = [(0, y) for y in range(9, 12)]
SOUTH = [(x, MAP_H - 1) for x in range(12, 16)]
CAMP = [(13, 13), (12, 12), (11, 13), (14, 12), (12, 14), (10, 14), (15, 13)]  # the Friends', as before
SOLID = set("T#bRoklSBcw_~vrZLXHUW")
# the town props (Kanto Town Props v0.1, kit/props.py): (piece, x, y of its top-left block, the ground under it)
PROPS = [("statue_guardian", 24, 6, "grass"),  # between the Mart and the Tower
         ("bench_wood_north", 27, 17, "grass"), ("bench_wood_north", 31, 17, "grass"),  # looking at the memorial garden
         ("litter_bin", 21, 12, "grass")]

# the buildings: their letters in the plan, where each comes from and its palette's bank
OWN = {"H": (VB / "house_family", HOUSE_BANK), "U": (VB / "house_pond_keeper", HOUSE_BANK),
       "W": (VB / "house_gardener", HOUSE_BANK)}
SHARED = {"Z": "pokemon_center", "L": "poke_mart"}


def load(letter: str) -> buildings.Building:
    if letter in SHARED:
        return kit.SHARED_BUILDINGS[SHARED[letter]][0]
    if letter == "X":
        return buildings.load(TOWER)
    return buildings.load(OWN[letter][0])


def plan() -> list[list[str]]:
    rows = (HERE / "plan_stage1.txt").read_text().split("\n")[:MAP_H]
    g = [list(r) for r in rows]
    assert len(g) == MAP_H and all(len(r) == MAP_W for r in g), "the plan is 38x32"
    return g


def doors(g) -> dict[str, list[tuple[int, int]]]:
    out = {}
    for letter in list(SHARED) + ["X"] + list(OWN):
        b = load(letter)
        bw, bh = b.idx.shape[1] // 16, b.idx.shape[0] // 16
        cells = {(x, y) for y, r in enumerate(g) for x, c in enumerate(r) if c == letter}
        x0, y0 = min(cells)
        assert cells == {(x0 + i, y0 + j) for i in range(bw) for j in range(bh)}, f"{letter} isn't its footprint"
        out[letter] = [(x0 + b.door[0], y0 + b.door[1])]
    return out


def reachable(g, starts) -> set[tuple[int, int]]:
    seen, todo = set(starts), deque(starts)
    while todo:
        x, y = todo.popleft()
        for n in ((x + 1, y), (x - 1, y), (x, y + 1), (x, y - 1)):
            if 0 <= n[0] < MAP_W and 0 <= n[1] < MAP_H and n not in seen and g[n[1]][n[0]] not in SOLID:
                seen.add(n)
                todo.append(n)
    return seen


def check(g, d) -> None:
    """The town's rules: only its three roads open onto the edges; everything walkable is reached from Route 10's
    road; every door can be walked into from the block below it, every sign read from it; the Friends' camp is open
    ground."""
    edge = {(x, y) for y in range(MAP_H) for x in range(MAP_W) if x in (0, MAP_W - 1) or y in (0, MAP_H - 1)}
    assert {xy for xy in edge if g[xy[1]][xy[0]] not in SOLID} == set(NORTH + WEST + SOUTH), "only the roads open"
    town = reachable(g, NORTH)
    walk = {(x, y) for y in range(MAP_H) for x in range(MAP_W) if g[y][x] not in SOLID}
    assert walk <= town, f"blocks you can't reach: {sorted(walk - town)[:8]}"
    for letter, ds in d.items():
        for x, y in ds:
            assert (x, y + 1) in town, f"the door of {letter} at ({x},{y}) can't be walked into"
    for y in range(MAP_H):
        for x in range(MAP_W):
            if g[y][x] == "S":
                assert (x, y + 1) in town, f"the sign at ({x},{y}) can't be read"
    assert set(CAMP) <= town, "the Friends' camp must be open ground"


GARDEN_STONES = [(23, 14), (26, 14), (29, 14), (32, 14)]  # the garden of remembrance's stones, in its flowers
STONE_CHARS = iter("ǎǐǒǔ")


def pick(names, x: int, y: int) -> str:
    """The piece a "pick" letter draws at (x, y) (as pae map paint picks)."""
    return names[(x * 7919 + y * 104729 + (x * y) % 13) % len(names)]


def garden_stones(g) -> tuple[dict, list]:
    """The garden's stones stand in its flowers: each the kit's rock over the flowers the bed has there."""
    legend, made = {}, {}
    sh = kit.Sheet("garden_stones", kit.PALS["ground"], kit.BANK["ground"], HERE, HERE, cols=4)
    flowers = kit.LEGEND["*"]["pick"]
    for x, y in GARDEN_STONES:
        assert g[y][x] == "o", f"no stone at ({x},{y})"
        rock, ground = pick(kit.ROCKS, x, y), pick(flowers, x, y)
        name = f"{rock}@{ground}"
        if name not in made:
            made[name] = next(STONE_CHARS)
            sh.add(name, kit.field_rock(rock), tileset="secondary", ground=ground, solid=True)
            legend[made[name]] = name
        g[y][x] = made[name]
    return legend, sh.write()


def main() -> None:
    g = plan()
    prop_legend, prop_grounds = props.place(g, PROPS, SOLID)
    d = doors(g)
    kit.check_forest(g)
    kit.check_water(g)
    check(g, d)
    stone_legend, stone_mt = garden_stones(g)
    base = kit.primary(HERE)  # the kit: the primary tileset every map shares
    spec_mt = list(base["metatiles"]) + stone_mt
    pals = {}
    for letter, (folder, bank) in list(OWN.items()) + [("X", (TOWER, TOWER_BANK))]:
        b = load(letter)
        pals.setdefault(bank, b.palette)
        if pals[bank] != b.palette:
            raise SystemExit(f"{folder.name}: its palette isn't the one bank {bank} has")
        sh = kit.Sheet(b.name, b.palette, bank, HERE, HERE, cols=b.idx.shape[1] // 16)
        sh.add(b.name, b.idx, tileset="secondary", **b.entry())
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
                                       f"palette_{TOWER_BANK}.pal"]},
            "reserve": {"primary": base["reserve"]},
            "animations": base["animations"] + prop_anims,
            "field_effects": base["field_effects"],
            "metatiles": spec_mt}
    (HERE / "spec.json").write_text(json.dumps(spec, indent=1) + "\n")
    (HERE / "grid.txt").write_text("".join("".join(r) + "\n" for r in g))
    (HERE / "border.txt").write_text("TT\nTT\n")
    # the Center, the Mart and the Tower count as cobble for the paths up to their doors (no lawn lip at the step)
    legend = dict(kit.LEGEND, **{k: {"name": v, "joins": "="} for k, v in SHARED.items()},
                  X={"name": "pokemon_tower", "joins": "="}, **{k: load(k).name for k in OWN})
    legend.update(prop_legend)
    legend.update(stone_legend)
    (HERE / "legend.json").write_text(json.dumps(legend, indent=1) + "\n")
    (HERE / "doors.json").write_text(json.dumps(d, indent=1) + "\n")
    print(f"{len(spec_mt)} metatiles in the spec; grid {MAP_W}x{MAP_H}; doors {d}")


if __name__ == "__main__":
    main()
