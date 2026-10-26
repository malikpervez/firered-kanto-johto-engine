#!/usr/bin/env python3
"""Route 7 after its concept (draw_plan.py and plan_stage1.txt): the short park road from Celadon's boulevard to
Saffron's west gate (see draw_plan.py). It is 30x24 blocks (old Route 7 was 20x28); its joins: Celadon's boulevard
the left edge at rows 10-13 (Celadon's 20-23, offset -10), Saffron beyond the right edge (offset -18), whose gate door
(Saffron row 27) is level with the gate's door here (row 9), as it was with the old route's (row 12, offset -15).

The pieces: the kit's, Viridian's pond keeper's house (the Underground Path's hut) in Viridian's houses' palette
(bank 9), and Route 2's south forest gate (Saffron's gate) in its own palette (bank 7). Bank 8 is the kit's plants
palette; 10-12 stay free for seams to old maps (Celadon is from the kit now: their seam needs none).

Run from the repository root:  python3 project/art/route7-concept/make_art.py
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
SECONDARY = "gTileset_Route7Concept"
MAP_W, MAP_H = 30, 24
GATE_BANK, HOUSE_BANK = 7, 9
WEST = [(0, y) for y in range(10, 14)]
SOLID = set("T#bRoklSBcw_~vrUF")
# the buildings: their letters in the plan, their packs, their banks, and what their doors do (the gate's two open
# together)
BUILDINGS = {"U": (ART / "viridian-concept/buildings/house_pond_keeper", HOUSE_BANK, ["MB_ANIMATED_DOOR"]),
             "F": (ART / "route2-concept/buildings/forest_gate_south", GATE_BANK,
                   ["MB_ANIMATED_DOOR", "MB_ANIMATED_DOOR"])}
ROAD = {(x, y) for y in range(10, 14) for x in range(0, 23)}


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
    assert len(g) == MAP_H and all(len(r) == MAP_W for r in g), "the plan is 30x24"
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
    """The route's rules: only Celadon's boulevard opens onto the edges (the gate is a building, Saffron reached through
    it); no block you can walk to is within 7 of the right edge (the camera would show old Saffron, which has no seam);
    everything walkable is reached from Celadon; the road to the gate is all cobbles; every door can be walked into
    from below, the sign read."""
    edge = {(x, y) for y in range(MAP_H) for x in range(MAP_W) if x in (0, MAP_W - 1) or y in (0, MAP_H - 1)}
    assert {xy for xy in edge if g[xy[1]][xy[0]] not in SOLID} == set(WEST), "only Celadon's boulevard opens"
    walk = {(x, y) for y in range(MAP_H) for x in range(MAP_W) if g[y][x] not in SOLID}
    assert max(x for x, _ in walk) <= MAP_W - 8, "a block within 7 of the right edge: old Saffron would show"
    every = reachable(g, WEST)
    assert walk <= every, f"blocks you can't reach: {sorted(walk - every)[:8]}"
    assert all(g[y][x] == "=" for x, y in ROAD), "the road isn't all cobbles"
    for letter in BUILDINGS:
        for x, y in d[letter]:
            assert (x, y + 1) in every, f"the door of {letter} at ({x},{y}) can't be walked into"
    for y in range(MAP_H):
        for x in range(MAP_W):
            if g[y][x] == "S":
                assert (x, y + 1) in every, f"the sign at ({x},{y}) can't be read"


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
        open_, behavior = [], {}
        for (dx, dy), mb in zip(ds, behaviors):
            open_.append(f"{dx},{dy}")
            behavior[f"{dx},{dy}"] = mb
        sh = kit.Sheet(b.name, b.palette, bank, HERE, HERE, cols=bw)
        sh.add(b.name, b.idx, tileset="secondary", ground="grass", solid=True, open=open_, behaviors=behavior)
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
