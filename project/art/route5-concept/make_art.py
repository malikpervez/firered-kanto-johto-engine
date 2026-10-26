#!/usr/bin/env python3
"""Route 5 after its concept (draw_plan.py and plan_stage1.txt): the garden road south from Cerulean to Saffron's
north gate (see draw_plan.py). It is 50x36 blocks (old Route 5 was 68x46); its joins stay where its neighbours meet
it: Cerulean's neck the top at columns 29-32 (offset 8), Saffron below (offset -4), whose gate door (Saffron 28-29)
is under the gate's top door here (24-25).

The pieces: the kit's, Viridian's family and gardener's houses (the Day Care and the Underground Path's hut) in
Viridian's houses' palette (bank 9), and Route 2's north forest gate (Saffron's gate) in its own palette (bank 7).
Bank 8 is the kit's plants palette; 10-12 stay free for the seam to old Saffron.

Run from the repository root:  python3 project/art/route5-concept/make_art.py
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
SECONDARY = "gTileset_Route5Concept"
MAP_W, MAP_H = 50, 36
GATE_BANK, HOUSE_BANK = 7, 9
NORTH = [(x, 0) for x in range(29, 33)]
SOLID = set("T#bRoklSBcw_~vrDUN")
# the buildings: their letters in the plan, their packs, their banks, and what their doors do (the gate's two are
# open blocks at its top you step on and walk south from, the cobbles drawn under them)
BUILDINGS = {"D": (ART / "viridian-concept/buildings/house_family", HOUSE_BANK, ["MB_ANIMATED_DOOR"]),
             "U": (ART / "viridian-concept/buildings/house_gardener", HOUSE_BANK, ["MB_ANIMATED_DOOR"]),
             "N": (ART / "route2-concept/buildings/forest_gate_north", GATE_BANK,
                   ["MB_SOUTH_ARROW_WARP", "MB_SOUTH_ARROW_WARP"])}
UNDER_DOORS = {"N": "cobble"}
PADDOCK = (15, 18)  # inside the Day Care's fence: its Pokémon play there, no one walks in


def load(letter: str) -> tuple[buildings.Building, list[tuple[int, int]]]:
    """A building and its doors (``door_blocks``, or the older packs' one ``door_block``)."""
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
    assert len(g) == MAP_H and all(len(r) == MAP_W for r in g), "the plan is 50x36"
    return g


def doors(g) -> dict[str, list[tuple[int, int]]]:
    out = {}
    for letter in BUILDINGS:
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
    """The route's rules: only Cerulean's neck opens onto the edges (the gate below is a building, Saffron reached
    through it); everything walkable but the paddock is reached from it, and the paddock from nowhere; every door
    can be walked into (the houses' from below, the gate's from the road above it), the sign read."""
    edge = {(x, y) for y in range(MAP_H) for x in range(MAP_W) if x in (0, MAP_W - 1) or y in (0, MAP_H - 1)}
    assert {xy for xy in edge if g[xy[1]][xy[0]] not in SOLID} == set(NORTH), "only Cerulean's neck opens"
    walk = {(x, y) for y in range(MAP_H) for x in range(MAP_W) if g[y][x] not in SOLID}
    road = reachable(g, NORTH)
    paddock = reachable(g, [PADDOCK])
    assert not paddock & road, "the paddock must be fenced in"
    assert walk <= road | paddock, f"blocks you can't reach: {sorted(walk - road - paddock)[:8]}"
    for letter in "DU":
        (x, y), = d[letter]
        assert (x, y + 1) in road, f"the door of {letter} at ({x},{y}) can't be walked into"
    for x, y in d["N"]:
        assert (x, y - 1) in road, f"the gate's door at ({x},{y}) can't be reached from the road"
    for y in range(MAP_H):
        for x in range(MAP_W):
            if g[y][x] == "S":
                assert (x, y + 1) in road, f"the sign at ({x},{y}) can't be read"


def main() -> None:
    g = plan()
    d = doors(g)
    kit.check_forest(g)
    kit.check_water(g)
    check(g, d)
    base = kit.primary(HERE)  # the kit: the primary tileset every map shares
    spec_mt = list(base["metatiles"])
    pals = {}
    for letter, (folder, bank, behaviors) in BUILDINGS.items():
        b, ds = load(letter)
        pals.setdefault(bank, b.palette)
        assert pals[bank] == b.palette, f"{b.name}: its palette isn't the one bank {bank} has"
        bw, bh = b.idx.shape[1] // 16, b.idx.shape[0] // 16
        ground = ["grass"] * (bw * bh)
        open_, behavior = [], {}
        for (dx, dy), mb in zip(ds, behaviors):
            open_.append(f"{dx},{dy}")
            behavior[f"{dx},{dy}"] = mb
            if letter in UNDER_DOORS:  # the road's piece under the doorway: open to the north and to the other door
                sides = 1 | sum(bit for bit, ox in ((2, 1), (8, -1)) if (dx + ox, dy) in ds)
                ground[dy * bw + dx] = f"{UNDER_DOORS[letter]}#{sides}"
        sh = kit.Sheet(b.name, b.palette, bank, HERE, HERE, cols=bw)
        sh.add(b.name, b.idx, tileset="secondary", ground=ground if len(set(ground)) > 1 else "grass", solid=True,
               open=open_, behaviors=behavior)
        spec_mt += sh.write()
    for e in spec_mt:  # sheets put "w"/"h" on everything; drop the 1x1 ones for readability
        if e["w"] == 1 and e["h"] == 1:
            del e["w"], e["h"]
    for bank, pal in pals.items():
        kit.write_palette(HERE / f"palette_{bank}.pal", pal)
    spec = {"version": "hns", "primary": kit.PRIMARY, "secondary": SECONDARY,
            "palettes": {"primary": base["palettes"],
                         "secondary": [f"palette_{GATE_BANK}.pal", base["secondary_palettes"][8],
                                       f"palette_{HOUSE_BANK}.pal"]},
            "reserve": {"primary": base["reserve"]},
            "animations": base["animations"],
            "field_effects": base["field_effects"],
            "metatiles": spec_mt}
    (HERE / "spec.json").write_text(json.dumps(spec, indent=1) + "\n")
    (HERE / "grid.txt").write_text("".join("".join(r) + "\n" for r in g))
    (HERE / "border.txt").write_text("TT\nTT\n")
    legend = dict(kit.LEGEND, **{k: load(k)[0].name for k in BUILDINGS})
    (HERE / "legend.json").write_text(json.dumps(legend, indent=1) + "\n")
    (HERE / "doors.json").write_text(json.dumps(d, indent=1) + "\n")
    print(f"{len(spec_mt)} metatiles in the spec; grid {MAP_W}x{MAP_H}; doors {d}")


if __name__ == "__main__":
    main()
