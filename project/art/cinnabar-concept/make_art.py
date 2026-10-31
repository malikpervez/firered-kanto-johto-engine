#!/usr/bin/env python3
"""Cinnabar Island after its concept (draw_plan.py and plan_stage1.txt): Kanto's volcanic island town (see
draw_plan.py). It is 96x44 blocks, as before; its joins stay where they were: Route 21's sea above (offset 0), Route
20's to the right (offset 0).

The pieces: the kit's and its Pokémon Center and Mart; the island's own buildings, each in its own palette: Blaine's
Gym (Kanto Buildings Remakes v0.3, ../packs/buildings_v0.3: volcanic stone, bank 7), the burned Mansion (Celadon's old
hotel, charred: buildings/pokemon_mansion, until the remakes' larger Mansion moves in; bank 9), the Pokémon Lab (the
remakes' Oak's lab, as Pallet has it, bank 10); the kit's cliffs for the volcano's rock (bank 11).
Bank 8 is the kit's plants palette; 12 stays free. Route 20 and Route 21 are kit maps too, so there are no seams.

Run from the repository root:  python3 project/art/cinnabar-concept/make_art.py
It writes sheets/, the palettes, spec.json, grid.txt, border.txt, legend.json and doors.json next to
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
import cliffs
import kit
import props

HERE = Path(__file__).resolve().parent
R = buildings.REMAKES
SECONDARY = "gTileset_CinnabarConcept"
MAP_W, MAP_H = 96, 44
GYM_BANK, MANSION_BANK, LAB_BANK, CLIFF_BANK = 7, 9, 10, 11
DOOR = "MB_ANIMATED_DOOR"
BUILDINGS = {"H": (R / "cinnabar_gym", GYM_BANK), "U": (HERE / "buildings/pokemon_mansion", MANSION_BANK),
             "X": (R / "pokemon_lab", LAB_BANK)}
SHARED = {"Z": "pokemon_center", "L": "poke_mart"}
SEA = "s"
WATER = set("s~")
SOLID = set("T#bRoklSBcw_~vrsqQHUXZL") | cliffs.SOLID | {"C"}
# the town props (Kanto Town Props v0.1, kit/props.py): (piece, x, y of its top-left block, the ground under it)
PROPS = [("bench_wood_south", 9, 14, "grass"), ("litter_bin", 13, 14, "grass"), ("bench_wood_south", 16, 14, "grass")]  # looking out to sea
LANE = [(x, 0) for x in range(0, 4)]         # Route 21's sea lane down the town's west side
EAST = [(MAP_W - 1, y) for y in range(0, 20)]  # Route 20's sea
STREET = (12, 5)
# where the island's scenes walk: the player out of the Gym (20,5) or the Center (14,12); Bill from his place by the
# Mart (20,7) up to the player, round by the east lane (21,6-12) or along the harbour street (15-22,12) to the shore;
# the player off the Seagallop (21,7); the boat in from the east on rows 8 and 12, to x 25 (23,7: where it waits)
SCENE_GROUND = [(20, 5), (20, 6), (20, 7), (21, 6), (21, 7), (21, 8), (22, 8), (14, 12)] + \
               [(x, 12) for x in range(14, 23)] + [(21, y) for y in range(6, 13)]
SCENE_WATER = [(23, 7)] + [(x, y) for x in range(23, 31) for y in (8, 12)]
CAMP = [(46, 20), (48, 20), (45, 19), (44, 20), (47, 22), (45, 21), (44, 22), (42, 20)]  # the Friends', Giratina's
# the people on the town island (the woman, the old man, Bill, the gentleman) and the volcano's Pokémon
TOWN_PEOPLE = [(14, 6), (11, 13), (20, 7), (22, 10)]
VOLCANO_MONS = [(60, 26), (62, 26), (61, 27), (78, 9), (79, 11), (52, 9), (51, 13), (48, 15), (66, 27)]
WAILMER = (88, 40)
CRATER = {(x, y) for x in range(62, 69) for y in range(15, 18)}  # the pit in the volcano's top: no way in


def load(letter: str) -> tuple[buildings.Building, list[tuple[int, int]]]:
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


def plan() -> list[list[str]]:
    rows = (HERE / "plan_stage1.txt").read_text().split("\n")[:MAP_H]
    g = [list(r) for r in rows]
    assert len(g) == MAP_H and all(len(r) == MAP_W for r in g), "the plan is 96x44"
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


def reachable(g, starts, surf=False) -> set[tuple[int, int]]:
    seen, todo = set(starts), deque(starts)
    while todo:
        x, y = todo.popleft()
        for n in ((x + 1, y), (x - 1, y), (x, y + 1), (x, y - 1)):
            if not (0 <= n[0] < MAP_W and 0 <= n[1] < MAP_H) or n in seen:
                continue
            c = g[n[1]][n[0]]
            if c in SOLID and not (surf and c in WATER):
                continue
            seen.add(n)
            todo.append(n)
    return seen


def check(g, d) -> None:
    """The island's rules: on foot, the town is one place, reached from its street, and nothing walkable is on an edge
    but the lawn between the woods and the Gym (Route 21's woods stand above it); by Surf from Route 21's lane, both
    islands, the hot spring and Route 20's sea are reached; the two islands aren't joined on foot; every door can be
    walked into, every sign read; the scenes' ground is open and their water is open sea; the Friends' camp and
    Giratina's spot are open ground on the volcano island; the people and the Pokémon stand on open ground (Wailmer
    swims); the volcano's crater is a closed pit."""
    walk = {(x, y) for y in range(MAP_H) for x in range(MAP_W) if g[y][x] not in SOLID}
    assert CRATER <= walk and not CRATER & reachable(g, LANE, surf=True), "the crater is closed"
    walk -= CRATER
    edge = {(x, y) for x, y in walk if x in (0, MAP_W - 1) or y in (0, MAP_H - 1)}
    assert edge <= {(16, 0)}, f"land on an edge: {sorted(edge)}"
    town = reachable(g, [STREET])
    surfing = reachable(g, LANE, surf=True)
    assert walk <= surfing and set(EAST) <= surfing, f"blocks you can't reach: {sorted(walk - surfing)[:8]}"
    volcano = reachable(g, [CAMP[0]])
    assert not town & volcano, "the islands are apart"
    assert walk <= town | volcano, f"a third island: {sorted(walk - town - volcano)[:8]}"
    for letter, ds in d.items():
        for x, y in ds:
            assert (x, y + 1) in town, f"the door of {letter} at ({x},{y}) can't be walked into"
    assert d["Z"] == [(14, 11)] and d["H"] == [(20, 4)], "the scenes' doors stay where they were"
    for y in range(MAP_H):
        for x in range(MAP_W):
            if g[y][x] == "S":
                assert (x, y + 1) in town, f"the sign at ({x},{y}) can't be read"
    assert set(SCENE_GROUND) <= town, f"the scenes' ground: {sorted(set(SCENE_GROUND) - town)}"
    assert all(g[y][x] == SEA for x, y in SCENE_WATER), "the boat's way"
    assert set(CAMP) <= volcano, "the Friends' camp"
    assert set(TOWN_PEOPLE) <= town and set(VOLCANO_MONS) <= volcano, "the people and the Pokémon on open ground"
    assert g[WAILMER[1]][WAILMER[0]] == SEA, "Wailmer in the sea"


ASH = "ǝ"  # plain ash (dirt#15, no edge) where the ash meets the volcano's rock, so no grass rim runs round the rock
SIGN_CHARS = {"cobble#14": "ǣ", "cobble#12": "ǥ"}  # the signs standing in the street: a sign over its cobble
SIGNS_IN_STREET = [(9, 12), (22, 5)]  # the Lab's (the Lab above), the Gym's (the Gym above, sea east)


def ash_by_rock(g, junction_chars) -> None:
    """The ash next to the rock (and the crater's floor): plain ash, counted as ash by the ash round it, so the ash
    draws no grass edge against the rock. Only where all its sides are ash or rock (the edge to the lawn stays)."""
    rock = cliffs.SOLID | set(junction_chars)
    ash = {":", ASH, "o"}
    for y in range(MAP_H):
        for x in range(MAP_W):
            if g[y][x] != ":":
                continue
            near = [g[y + dy][x + dx] for dy in (-1, 0, 1) for dx in (-1, 0, 1)
                    if (dx or dy) and 0 <= x + dx < MAP_W and 0 <= y + dy < MAP_H]
            sides = [g[y + dy][x + dx] for dx, dy in ((0, -1), (1, 0), (0, 1), (-1, 0))]
            if any(c in rock for c in near) and all(c in rock or c in ash for c in sides):
                g[y][x] = ASH


def signs_on_cobble(g) -> dict[tuple[int, int], str]:
    """The signs in the street with two sides on it (kit/settle.py takes the ones with three): each over the cobble
    pae would draw there if it were cobble, and cobble for the cobble round it."""
    out = {}
    for x, y in SIGNS_IN_STREET:
        assert g[y][x] == "S", f"no sign at ({x},{y})"
        same = lambda xx, yy: g[yy][xx] in "=S" or (xx, yy) in SIGNS_IN_STREET
        mask = sum(b for b, (dx, dy) in ((1, (0, -1)), (2, (1, 0)), (4, (0, 1)), (8, (-1, 0))) if same(x + dx, y + dy))
        out[x, y] = f"cobble#{mask}"
    for (x, y), ground in out.items():
        g[y][x] = SIGN_CHARS[ground]
    return out


def main() -> None:
    g = plan()
    prop_legend, prop_grounds = props.place(g, PROPS, SOLID)
    d = doors(g)
    cliffs.layout(g)
    kit.check_forest(g)
    kit.check_water(g)
    kit.check_paving(g)
    check(g, d)
    base = kit.primary(HERE)  # the kit: the primary tileset every map shares
    spec_mt = list(base["metatiles"])
    pals = {}
    for letter, (folder, bank) in BUILDINGS.items():
        b, ds = load(letter)
        pals[bank] = b.palette
        sh = kit.Sheet(b.name, b.palette, bank, HERE, HERE, cols=b.idx.shape[1] // 16)
        sh.add(b.name, b.idx, tileset="secondary", ground="grass", solid=True,
               open=[f"{dx},{dy}" for dx, dy in ds], behaviors={f"{dx},{dy}": DOOR for dx, dy in ds})
        spec_mt += sh.write()
    rock = kit.Sheet("rock_cliff", cliffs.PAL, CLIFF_BANK, HERE, HERE)
    char_of = cliffs.add(rock, g, extras=())
    rock_entries = rock.write()
    for e in rock_entries:  # the volcano's rock stands in its ash all round: its lip and corners on ash, not grass
        if e.get("ground") == "grass":
            e["ground"] = "dirt#15"
    spec_mt += rock_entries
    ash_by_rock(g, set(char_of.values()))
    signs = signs_on_cobble(g)
    sh = kit.Sheet("signs_cobble", kit.PALS["wood"], kit.BANK["wood"], HERE, HERE, cols=2)
    for ground in sorted(set(signs.values())):
        sh.add(f"sign_on_{ground}", kit.sign(), tileset="secondary", ground=ground, solid=True)
    spec_mt += sh.write()
    pals[CLIFF_BANK] = cliffs.PAL
    prop_entries, prop_anims = props.pieces(HERE, HERE, prop_grounds)
    spec_mt += prop_entries
    for e in spec_mt:  # sheets put "w"/"h" on everything; drop the 1x1 ones for readability
        if e["w"] == 1 and e["h"] == 1:
            del e["w"], e["h"]
    for bank, pal in pals.items():
        kit.write_palette(HERE / f"palette_{bank}.pal", pal)
    spec = {"version": "hns", "primary": kit.PRIMARY, "secondary": SECONDARY,
            "palettes": {"primary": base["palettes"],
                         "secondary": [f"palette_{GYM_BANK}.pal", base["secondary_palettes"][8],
                                       f"palette_{MANSION_BANK}.pal", f"palette_{LAB_BANK}.pal",
                                       f"palette_{CLIFF_BANK}.pal"]},
            "reserve": {"primary": base["reserve"]},
            "animations": base["animations"] + prop_anims,
            "field_effects": base["field_effects"],
            "metatiles": spec_mt}
    (HERE / "spec.json").write_text(json.dumps(spec, indent=1) + "\n")
    (HERE / "grid.txt").write_text("".join("".join(r) + "\n" for r in g))
    (HERE / "border.txt").write_text("ss\nss\n")
    legend = dict(kit.LEGEND, **SHARED, **{k: load(k)[0].name for k in BUILDINGS})
    assert not set(legend) & set(cliffs.legend(char_of)), "a building's letter is one of the cliffs'"
    legend.update(cliffs.legend(char_of))
    legend.update(prop_legend)
    legend[ASH] = {"pick": ["dirt#15"], "joins": ":"}
    legend.update({ch: {"name": f"sign_on_{ground}", "joins": "="} for ground, ch in SIGN_CHARS.items()})
    (HERE / "legend.json").write_text(json.dumps(legend, indent=1) + "\n")
    (HERE / "doors.json").write_text(json.dumps(d, indent=1) + "\n")
    print(f"{len(spec_mt)} metatiles in the spec; grid {MAP_W}x{MAP_H}; doors {d}")


if __name__ == "__main__":
    main()
