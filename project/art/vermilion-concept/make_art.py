#!/usr/bin/env python3
"""Vermilion City after its concept (draw_plan.py and plan_stage1.txt): the harbour city (see draw_plan.py). It is
60x42 blocks (old Vermilion was 71x78), and its joins stay where its neighbours meet it: Route 6's road the top at
columns 32-34 (offset -8), Route 11's the right edge at rows 11-14 (its 14-17, offset -3); the S.S. Anne's gangway
is the pier's end (37-39 on the bottom row).

The pieces: the kit's, the Pokémon Center and the Mart (the kit's), Viridian's Gym (every Gym looks the same outside, as
in FireRed) and its Trainer School (the Fan Club) in Viridian's buildings' palette (bank 7), and Viridian's three houses in its houses' palette (bank 9).
Bank 8 is the kit's plants palette; 10-12 stay free for the seam to Route 11 (not rebuilt yet).

Run from the repository root:  python3 project/art/vermilion-concept/make_art.py
It writes sheets/, the palettes, spec.json, grid.txt, border.txt, legend.json and doors.json next to itself;
build.sh turns them into the game's tileset and map with pae.
"""
import json
import sys
from collections import deque
from pathlib import Path

import numpy as np

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "kit"))
import buildings
import harbour
import kit
import trees
import props

HERE = Path(__file__).resolve().parent
ART = HERE.parent
SECONDARY = "gTileset_VermilionConcept"
MAP_W, MAP_H = 60, 42
CITY_BANK, HOUSE_BANK = 7, 9
VB = ART / "viridian-concept/buildings"
# the buildings: their letters in the plan, where each comes from and its palette's bank
OWN = {"K": (VB / "trainer_school", CITY_BANK), "W": (VB / "viridian_gym", CITY_BANK),
       "X": (VB / "house_gardener", HOUSE_BANK), "H": (VB / "house_family", HOUSE_BANK),
       "U": (VB / "house_pond_keeper", HOUSE_BANK)}
SHARED = {"Z": "pokemon_center", "L": "poke_mart"}
CUT_TREE = (15, 15)                            # the tree to cut, in the Gym yard's gate
NORTH = [(x, 0) for x in range(32, 35)]
EAST = [(MAP_W - 1, y) for y in range(11, 15)]
GANGWAY = [(x, MAP_H - 1) for x in range(37, 40)]  # the S.S. Anne's warps, at the pier's end
# the gangway's blocks: the pier's planks (their pieces: open to the pier and off the map's edge) that warp you onto
# the ship as you step on them; the pier joins them
GANGWAY_PIECES = {"J": "dock#7", "G": "dock#15", "Y": "dock#13"}
FERRY = (39, MAP_H - 2)                        # the ferry sailor, his ticket check on 37-38 before him
WATER = set("~vr")
SOLID = set("T#bRoklSBcwO_~vrZLKWXHU")
# the town props (Kanto Town Props v0.1, kit/props.py): (piece, x, y of its top-left block, the ground under it)
# ("setts", "quay": on the harbour's ground, kit/harbour.py, their ground its block there)
PROPS = [("fountain_3x3", 33, 17, "setts"), ("bench_wood_west", 37, 17, "setts"), ("flower_tub", 32, 16, "setts"),
         ("flower_tub", 36, 16, "setts"),
         # along the harbour, looking out to sea
         ("bench_wood_south", 21, 22, "quay"), ("bench_wood_south", 27, 22, "quay"),
         ("bench_wood_south", 45, 22, "quay"), ("bench_wood_south", 51, 22, "quay"),
         ("litter_bin", 33, 22, "quay"), ("litter_bin", 48, 22, "quay")]
# the harbour's ground (Kanto Harbour Textures v0.1, kit/harbour.py): two squares in fan setts, each with the block its
# pattern starts from: the one before the Center and the Mart, with a band of the setts over the pavement running on
# from its foot along the north of the street both ways (where lawn was); and the fountain's between the houses south
# of the street (in place of its lawn, flowers and bushes; its pattern runs on into the promenade's flags), with the
# same band along the south of the street (the Gym yard's fence standing on it); the main
# street the kit's asphalt with a strip of pavement each side, running on under the forest's edge at its west end, and
# meeting the cobble Route 11's road is on one line at its east end, where the forest starts (column 56), as its bands
# end there; the promenade in quay flags, the quay wall round the water and the docks; the details, the mooring ring in
# the coping and a ladder
BAND = [(x, 10) for x in list(range(4, 24)) + list(range(43, 56))]  # (4-5: under the forest's edge)
SOUTH_BAND = [(x, 15) for x in list(range(4, 25)) + list(range(44, 56))]
WOODS_EDGE = [(4, 10), (4, 12), (4, 14)]  # the forest's cells (2x2) the street runs on under, its blocks over the street
SQUARES = [([(x, y) for y in range(7, 11) for x in range(24, 43)] + BAND, (24, 7)),
           ([(x, y) for y in range(15, 22) for x in range(25, 44)] + SOUTH_BAND, (25, 16))]
STREET = {11: "n", 12: "+", 13: "-", 14: "u"}  # by row, columns 6-55: pavement over asphalt, the road, its line
STREET_GROUND = {11: "pavement_to_asphalt_S", 12: "asphalt#15", 13: "asphalt_dashed_H_boundary",
                 14: "pavement_to_asphalt_N"}
PROMENADE = [(x, 22) for x in range(18, 56)] + [(x, 23) for x in range(7, 56)]
HARBOUR_DETAILS = [("mooring_bollard", 20, 23), ("mooring_bollard", 54, 23), ("harbour_drain", 30, 22),
                   ("lifebuoy_post", 41, 22), ("bollard_rope", 54, 27), ("coiled_rope", 54, 26)]
RING, LADDER = (32, 23), (31, 24)


def plan() -> list[list[str]]:
    rows = (HERE / "plan_stage1.txt").read_text().split("\n")[:MAP_H]
    g = [list(r) for r in rows]
    assert len(g) == MAP_H and all(len(r) == MAP_W for r in g), "the plan is 60x42"
    return g


def load(letter: str) -> buildings.Building:
    if letter in SHARED:
        return kit.SHARED_BUILDINGS[SHARED[letter]][0]
    return buildings.load(OWN[letter][0])


def doors(g) -> dict[str, list[tuple[int, int]]]:
    """Each building's door."""
    out = {}
    for letter in list(SHARED) + list(OWN):
        b = load(letter)
        bw, bh = b.idx.shape[1] // 16, b.idx.shape[0] // 16
        cells = {(x, y) for y, r in enumerate(g) for x, c in enumerate(r) if c == letter}
        x0, y0 = min(cells)
        assert cells == {(x0 + i, y0 + j) for i in range(bw) for j in range(bh)}, f"{letter} isn't its footprint"
        out[letter] = [(x0 + b.door[0], y0 + b.door[1])]
    return out


def reachable(g, starts, blocked=(), surf=False) -> set[tuple[int, int]]:
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
    """The town's rules: only its three ways out open onto the edges (Route 6's road, Route 11's, the S.S. Anne's
    gangway); with the tree standing, the town is everything walkable but the Gym's yard, which the tree opens; the
    pier leads to the gangway, past the ferry sailor's ticket check; every door can be walked into from the block
    below it, every sign read from it; the harbour can be surfed from the promenade."""
    edge = {(x, y) for y in range(MAP_H) for x in range(MAP_W) if x in (0, MAP_W - 1) or y in (0, MAP_H - 1)}
    assert {xy for xy in edge if g[xy[1]][xy[0]] not in SOLID} == set(NORTH + EAST + GANGWAY), "only the ways out"
    people = {CUT_TREE, FERRY}
    town = reachable(g, NORTH, people)
    assert set(EAST + GANGWAY) <= town, "Route 11's road and the gangway must be reached from Route 6's"
    walk = {(x, y) for y in range(MAP_H) for x in range(MAP_W) if g[y][x] not in SOLID} - people
    yard = reachable(g, [(15, 16)], people)
    assert not yard & town and yard <= reachable(g, NORTH, {FERRY}), "the tree must close the Gym's yard"
    assert walk <= town | yard, f"blocks you can't reach: {sorted(walk - town - yard)[:8]}"
    assert all((x, MAP_H - 2) in town for x in (37, 38)), "the ticket check is before the gangway"
    for letter, ds in d.items():
        for x, y in ds:
            assert (x, y + 1) in walk, f"the door of {letter} at ({x},{y}) can't be walked into"
    for y in range(MAP_H):
        for x in range(MAP_W):
            if g[y][x] == "S":
                assert (x, y + 1) in walk, f"the sign at ({x},{y}) can't be read"
    assert (30, 30) in reachable(g, NORTH, people, surf=True), "the harbour must be surfed from the town"


def streets(g) -> None:
    """The main street: the kit's asphalt, a strip of pavement each side, the line down its middle; at its east end
    the cobble meets all of it on one line (its last column counts as cobble for the cobble, which draws no edge
    there)."""
    for y, ch in STREET.items():
        for x in range(6, 56):
            assert g[y][x] == "=", f"({x},{y}) isn't the old street"
            g[y][x] = ch
    g[12][55], g[13][55] = "j", "m"


def woods_edge(g, hb) -> list[dict]:
    """The forest's cells the street runs on under at its west end: the kit's forest (an edge to the east) over the
    street's blocks, forest for its neighbours."""
    sh = kit.Sheet("woods_edge", kit.PALS["trees"], kit.BANK["trees"], HERE, HERE, cols=2)
    hb["woods"] = {}
    for i, (x, y) in enumerate(WOODS_EDGE):
        under = [hb["ground"].get((xx, yy)) or STREET_GROUND[yy] for yy in (y, y + 1) for xx in (x, x + 1)]
        name = f"forest#13_over_street_{y}"
        sh.add(name, trees.forest(13), tileset="secondary", ground=under, solid=True)
        hb["woods"][chr(0x190 + i)] = name
        for yy in (y, y + 1):
            for xx in (x, x + 1):
                g[yy][xx] = chr(0x190 + i)
    return sh.write()


def lay_harbour(g, prop_legend: dict, prop_grounds: dict) -> dict:
    """The harbour (kit/harbour.py). What stands on its setts and flags takes their block there as its ground (another
    of a piece where the ground differs: "piece~2"); the signs on it are found again after it (check reads them)."""
    letter_of = {(v if isinstance(v, str) else v["name"]): k for k, v in prop_legend.items()}
    signs = {(x, y) for cells, _ in SQUARES for x, y in cells if g[y][x] == "S"}
    fenced = {(x, y) for cells, _ in SQUARES for x, y in cells if g[y][x] == "#"}  # the fence stands on the band
    fence_mask = {(x, y): sum(b for b, (dx, dy) in ((1, (0, -1)), (2, (1, 0)), (4, (0, 1)), (8, (-1, 0)))
                              if not (0 <= x + dx < MAP_W and 0 <= y + dy < MAP_H) or g[y + dy][x + dx] == "#")
                  for x, y in fenced}  # as pae map paint draws the fence: its neighbours that are fence too
    for x, y in fenced:
        g[y][x] = "."
    woods = {(x, y) for cells, _ in SQUARES for x, y in cells if g[y][x] == "T"}  # the band under the forest's edge
    for x, y in woods:
        g[y][x] = "."
    for cells, _ in SQUARES:
        assert all(g[y][x] in "=.*b" or g[y][x] in prop_legend or (x, y) in signs for x, y in cells), \
            "a square takes the cobble, lawn, flowers and bushes there, and keeps its props and signs"
    on_quay = {(x, y) for x, y in PROMENADE if g[y][x] != "="}
    assert all(g[y][x] in prop_legend for x, y in on_quay), "only the props stand on the promenade"
    hb = harbour.lay(g, [(set(cells), origin) for cells, origin in SQUARES], set(PROMENADE), out=HERE, spec_dir=HERE,
                     street={(x, 11) for x in range(6, 57)} | {(x, 14) for x in range(6, 57)},
                     details=HARBOUR_DETAILS, ring=RING, ladder=LADDER)
    grounds_of: dict[str, list] = {}
    for piece, x, y, ground, *_ in PROPS:
        if ground not in ("quay", "setts"):
            continue
        fp = props.PIECES[piece][1]["footprint_blocks"]
        cells = [(xx, yy) for yy in range(y, y + fp["height"]) for xx in range(x, x + fp["width"])]
        under = [hb["ground"][c] for c in cells]
        seen = grounds_of.setdefault(piece, [])
        if under not in seen:
            seen.append(under)
        name = piece if seen.index(under) == 0 else f"{piece}~{seen.index(under) + 1}"
        prop_grounds[name] = under
        if name not in letter_of:  # a character of its own for it
            letter_of[name] = next(c for c in props.POOL if c not in prop_legend)
            prop_legend[letter_of[name]] = name
            if letter_of[piece] in SOLID:
                SOLID.add(letter_of[name])
        for xx, yy in cells:  # lay wrote the ground's character over it: the piece's again
            g[yy][xx] = letter_of[name]
    for x, y in signs:
        g[y][x] = "S"
    for x, y in woods:
        g[y][x] = "T"
    hb["fences"] = {}
    for x, y in sorted(fenced):  # the fence again, each over the band's block there; fence for its neighbours
        name = f"fence#{fence_mask[x, y]}_on_{hb['ground'][x, y]}"
        ch = hb["fences"].setdefault(name, (chr(0x180 + len(hb["fences"])), fence_mask[x, y], hb["ground"][x, y]))[0]
        g[y][x] = ch
        SOLID.add(ch)
    SOLID.update(hb["solid"] | hb["water"])
    WATER.update(hb["water"])
    hb["signs"] = signs
    return hb


def sign_grounds(g, hb) -> dict[str, str]:
    """The signs standing on the new ground: each the kit's sign over the block there, a character for each ground."""
    out = {}
    for y, row in enumerate(g):
        for x, c in enumerate(row):
            if c == "S" and (x, y) in hb["signs"]:
                ground = hb["ground"][x, y]
                ch = out.setdefault(ground, "fFiI"[len(out)])
                g[y][x] = ch
    return out


def main() -> None:
    g = plan()
    prop_legend, prop_grounds = props.place(g, PROPS, SOLID)
    d = doors(g)
    kit.check_forest(g)
    kit.check_water(g)
    streets(g)
    hb = lay_harbour(g, prop_legend, prop_grounds)
    woods = woods_edge(g, hb)
    SOLID.update(hb["woods"])
    check(g, d)
    signs_on = sign_grounds(g, hb)
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
    for (x, y), ch in zip(GANGWAY, GANGWAY_PIECES):
        g[y][x] = ch
    sh = kit.Sheet("gangway", pals[CITY_BANK], CITY_BANK, HERE, HERE, cols=3)
    for ch, ground in GANGWAY_PIECES.items():
        sh.add(f"gangway_{ch}", np.zeros((16, 16), np.uint8), tileset="secondary", ground=ground,
               behavior="MB_DEEP_SOUTH_WARP")
    spec_mt += sh.write()
    spec_mt += hb["entries"] + woods
    sh = kit.Sheet("signs_harbour", kit.PALS["wood"], kit.BANK["wood"], HERE, HERE, cols=4)
    for ground, ch in signs_on.items():
        sh.add(f"sign_on_{ground}", kit.sign(), tileset="secondary", ground=ground, solid=True)
    for name, (ch, m, ground) in hb["fences"].items():
        sh.add(name, kit.fence(m), tileset="secondary", ground=ground, solid=True, dedupe=True)
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
                         "secondary": [f"palette_{CITY_BANK}.pal", base["secondary_palettes"][8],
                                       f"palette_{HOUSE_BANK}.pal"]},
            "reserve": {"primary": base["reserve"]},
            "animations": base["animations"] + prop_anims,
            "field_effects": base["field_effects"],
            "metatiles": spec_mt}
    (HERE / "spec.json").write_text(json.dumps(spec, indent=1) + "\n")
    (HERE / "grid.txt").write_text("".join("".join(r) + "\n" for r in g))
    (HERE / "border.txt").write_text("~~\n~~\n")
    legend = dict(kit.LEGEND, **SHARED, **{k: load(k).name for k in OWN},
                  **{ch: {"name": f"gangway_{ch}", "joins": "d"} for ch in GANGWAY_PIECES})
    legend.update(prop_legend)
    # the street's pieces next to the cobble at its east end count as cobble for it, so it draws no edge there
    legend.update(hb["legend"], n={"name": "pavement_to_asphalt_S", "joins": "="},
                  u={"name": "pavement_to_asphalt_N", "joins": "="},
                  **{ch: f"sign_on_{ground}" for ground, ch in signs_on.items()},
                  **{ch: {"name": name, "joins": "#"} for name, (ch, _, _) in hb["fences"].items()},
                  **{ch: {"name": name, "joins": "T"} for ch, name in hb["woods"].items()},
                  j={"name": "asphalt#15", "joins": "="}, m={"name": "asphalt_dashed_H_boundary", "joins": "="},
                  **{"-": "asphalt_dashed_H_boundary"})
    (HERE / "legend.json").write_text(json.dumps(legend, indent=1) + "\n")
    (HERE / "doors.json").write_text(json.dumps(d, indent=1) + "\n")
    print(f"{len(spec_mt)} metatiles in the spec; grid {MAP_W}x{MAP_H}; doors {d}")


if __name__ == "__main__":
    main()
