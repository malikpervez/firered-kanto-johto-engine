#!/usr/bin/env python3
"""Lavender Town after its concept (draw_plan.py and plan_stage1.txt): the quiet town in a hollow of the hills (see
draw_plan.py). It is 38x32 blocks (old Lavender was 38x31), as wide as before; its joins stay where its neighbours meet
it: Route 10's road the top at columns 12-16 (Route 10's 16-20, offset -4), Route 8's the left edge at rows 9-11 (Route
8's 13-15, offset -4), Route 12's the bottom at columns 13-15 (Route 12's 11-13, offset 2; it was -2, the old town
sitting 4 blocks further east over Route 12).

The pieces: the kit's, the Pokémon Center and the Mart (the kit's), Viridian's three houses in their palette (bank 7),
and Pokémon Tower (Kanto Buildings Remakes v0.3, ../packs/buildings_v0.3) in a palette of its own (bank 9).
Bank 8 is the kit's plants palette. Lavender's own ground and details are Kanto Lavender Town v0.1
(../packs/lavender_v0.1, ../kit/lavender.py): the slate square and the walk to the tower, the garden of remembrance's
lavender, gravel, railings, gate, lanterns and memorial stones, the violet street lamps and Mr. Fuji's yard; its slate,
gravel and lavender are in a palette of their own (bank 10), its stones and lamps in the tower's, its iron and wood in
the kit's. Banks 11-12 stay free.

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
import lavender
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
NEW_BANK = lavender.NEW_BANK  # the pack's slate, gravel and lavender
# Lavender's ground, from the plan's letters (draw_plan.py): slate, gravel and lavender beds
SURFACES = {"σ": "slate", "γ": "gravel", "λ": "beds"}
# the railings: along the walk's south side (on its slate) either side of the gate and on east past the bushes, and down
# the garden's west side from row 18 to the town's south edge, open where its paths come out (rows 21 and 26); north of
# that its west side stays open (the Haunters go round there at night, and the worker stands by it), and the forest
# closes it east and south
RAILS = ({(x, 11) for x in range(21, 27)} | {(x, 11) for x in range(32, 36)}
         | {(21, y) for y in range(18, 30) if y not in (21, 26)})
# the routes' cobble roads, just past the edges: the town's slate roads take the join to the cobble on that side
EDGE_ROADS = ({(x, -1) for x, _ in NORTH} | {(-1, y) for _, y in WEST} | {(x, MAP_H) for x, _ in SOUTH})
GATES = [(28, 11)]  # the open gate (3x1, its middle block walkable), in line with the tower's door
# the details: (piece, x, y of its top-left block)
DETAILS = [("stone_lantern", 27, 11), ("stone_lantern", 31, 11),  # either side of the gate
           ("memorial_rounded", 23, 14), ("memorial_flat", 26, 14),  # the garden's stones, where its four stood
           ("memorial_flower", 32, 14), ("offering_stone", 33, 14),
           ("memorial_rounded", 23, 19), ("memorial_flat", 34, 19),  # and on south, row by row, to the town's edge
           ("memorial_flower", 23, 23), ("memorial_rounded", 25, 23), ("memorial_flat", 32, 23),
           ("memorial_rounded", 34, 23), ("offering_stone", 25, 24), ("offering_stone", 34, 24),
           ("memorial_rounded", 23, 28), ("memorial_flower", 25, 28), ("memorial_flat", 32, 28),
           ("memorial_rounded", 34, 28),
           ("stone_lantern", 28, 28), ("stone_lantern", 30, 28), ("memorial_flower", 29, 29),  # the path's end
           ("street_lamp", 16, 24), ("street_lamp", 11, 19),  # by the road south
           ("rest_shelter", 8, 13), ("food_water_bowls", 8, 15), ("straw_bed", 2, 16)]  # Mr. Fuji's yard
# at night (the game's light colours, see ../kit/kit.py's LIGHTS for the Center's and the Mart's): the houses' window
# glass (bank 7); in the tower's palette (bank 9) the lanterns' windows and the tower's door lamps, and the glint on
# the violet lamps' glass and the tower's windows, in a pale violet of the town's own
LIGHTS = {HOUSE_BANK: [14, 15], TOWER_BANK: {"colours": [6, 14], "light": [232, 200, 248]}}
# and a glow round each lantern's and street lamp's head (its top block) after dark (`pae map lights`, build.sh)
GLOWS = [(x, y) for piece, x, y in DETAILS if piece in ("stone_lantern", "street_lamp")]
# the town props (Kanto Town Props v0.1, kit/props.py): (piece, x, y of its top-left block, the ground under it)
PROPS = [("statue_guardian", 24, 6, "grass"),  # between the Mart and the Tower
         ("bench_wood_north", 24, 17, "grass"), ("bench_wood_north", 32, 17, "grass"),  # in the garden, the path between
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


def lay_lavender(g) -> dict:
    """Lavender's own ground and details (../kit/lavender.py) into the plan. The gravel has no edges at all (the
    owner: a border either all round or nowhere; it runs into the lavender, the lawn, the trees and the forest alike)."""
    cells = {kind: {(x, y) for y, r in enumerate(g) for x, c in enumerate(r) if c == ch} for ch, kind in SURFACES.items()}
    return lavender.lay(g, slate=cells["slate"], gravel=cells["gravel"], beds=cells["beds"], rails=RAILS, gates=GATES,
                        details=DETAILS, edge_roads=EDGE_ROADS, gravel_edges=False, tower_palette=buildings.load(TOWER).palette,
                        out=HERE, spec_dir=HERE)


def main() -> None:
    g = plan()
    prop_legend, prop_grounds = props.place(g, PROPS, SOLID)
    lav = lay_lavender(g)
    SOLID.update(lav["solid"])
    d = doors(g)
    kit.check_forest(g)
    kit.check_water(g)
    check(g, d)
    base = kit.primary(HERE)  # the kit: the primary tileset every map shares
    spec_mt = list(base["metatiles"]) + lav["entries"]
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
    assert lav["palette"], "the pack's slate, gravel and lavender are in a palette of their own"
    kit.write_palette(HERE / f"palette_{NEW_BANK}.pal", lav["palette"])
    spec = {"version": "hns", "primary": kit.PRIMARY, "secondary": SECONDARY,
            "palettes": {"primary": base["palettes"],
                         "secondary": [f"palette_{HOUSE_BANK}.pal", base["secondary_palettes"][8],
                                       f"palette_{TOWER_BANK}.pal", f"palette_{NEW_BANK}.pal"]},
            "reserve": {"primary": base["reserve"]},
            "lights": {**base["lights"], **{str(b): v for b, v in LIGHTS.items()}},
            "animations": base["animations"] + prop_anims,
            "field_effects": base["field_effects"],
            "metatiles": spec_mt}
    (HERE / "spec.json").write_text(json.dumps(spec, indent=1) + "\n")
    (HERE / "grid.txt").write_text("".join("".join(r) + "\n" for r in g))
    (HERE / "border.txt").write_text("TT\nTT\n")
    (HERE / "glows.txt").write_text(" ".join(f"{x},{y}" for x, y in GLOWS) + "\n")
    # the Center, the Mart and the Tower count as cobble for the paths up to their doors (no lawn lip at the step)
    legend = dict(kit.LEGEND, **{k: {"name": v, "joins": "="} for k, v in SHARED.items()},
                  X={"name": "pokemon_tower", "joins": "="}, **{k: load(k).name for k in OWN})
    legend.update(prop_legend)
    legend.update(lav["legend"])
    (HERE / "legend.json").write_text(json.dumps(legend, indent=1) + "\n")
    (HERE / "doors.json").write_text(json.dumps(d, indent=1) + "\n")
    print(f"{len(spec_mt)} metatiles in the spec; grid {MAP_W}x{MAP_H}; doors {d}")


if __name__ == "__main__":
    main()
