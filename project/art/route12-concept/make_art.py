#!/usr/bin/env python3
"""Route 12 after its concept (draw_plan.py and plan_stage1.txt): Silence Bridge, south from Lavender over the sea to
Route 13 (see draw_plan.py). It is 38x80 blocks (old Route 12 was 38x90); its joins stay where they were: Lavender's
road south (its columns 13-15) at the top edge, columns 10-13 (offset -2); Route 11's road (its rows 17-19) at the left
edge, rows 44-47 (offset 27); Route 13's boardwalk (its columns 86-89) at the bottom edge, columns 21-24 (offset -65).

The pieces: the kit's; the north gatehouse (Kanto Buildings Remakes v0.3, ../packs/buildings_v0.3) in Saffron's
buildings' palette (bank 7); the fishing house, Viridian's gardener's house, in Viridian's houses' palette (bank 9).
Every neighbour is from the kit, so no strip has to keep to few palettes.

Run from the repository root:  python3 project/art/route12-concept/make_art.py
It writes sheets/, the palettes, spec.json, grid.txt, border.txt, legend.json and doors.json next to itself; build.sh
turns them into the game's tileset and map with pae.
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
VB = HERE.parent / "viridian-concept/buildings"
SECONDARY = "gTileset_Route12Concept"
MAP_W, MAP_H = 38, 80
GATE_BANK, HOUSE_BANK = 7, 9
NORTH = [(x, 0) for x in range(10, 14)]
WEST = [(0, y) for y in range(44, 48)]
SOUTH = [(x, MAP_H - 1) for x in range(21, 25)]
SOLID = set("T#bRoklSBcw_~vrsqQNF")
DOOR, BACK = "MB_ANIMATED_DOOR", "MB_SOUTH_ARROW_WARP"
# the buildings: their letters in the plan, their packs, their banks, what each of their doors does (the gatehouse:
# its front double door, then the doorway in its back, entered walking south)
BUILDINGS = {"N": (buildings.REMAKES / "route12_gate", GATE_BANK, [DOOR, DOOR, BACK, BACK]),
             "F": (VB / "house_gardener", HOUSE_BANK, [DOOR])}
SNORLAX = (17, 48)       # asleep in the neck south of the fishers' deck, the Leftovers under him
CUT = [(26, 63), (26, 64)]  # the trees to cut: the pocket's way in
POCKET = (29, 63)
# the people (local ids 1-4, 6-8, 12-13: the fishers, Luca, Justin, Andrew, the couple), where they stand, which
# ways they look and how far (the couple only battle when spoken to)
TRAINERS = [(12, 24, ("NS", 1)), (15, 30, ("EW", 1)), (12, 35, ("SW", 4)), (15, 37, ("NS", 1)), (22, 45, ("NESW", 1)),
            (16, 64, ("S", 1)), (22, 74, ("EW", 1))]
COUPLE = [(20, 42), (20, 41)]
ITEMS = [(24, 41), (30, 62)]  # TM48 on the deck, the Iron in the pocket
LANDING = "\u01c6"  # the bridge's last row, where it lands on the islet
HIDDEN = [(7, 17), SNORLAX, (31, 65)]  # the Hyper Potion on the cliff top, the Leftovers, the Rare Candy
CARVANHA = (27, 30)      # swimming in the sea


def load(letter: str) -> tuple[buildings.Building, list[tuple[int, int]]]:
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
    assert len(g) == MAP_H and all(len(r) == MAP_W for r in g), "the plan is 38x80"
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


def reachable(g, starts, blocked=frozenset(), links=()) -> set[tuple[int, int]]:
    """Blocks you can walk to; ``links`` join a door's outside to another's (through the gatehouse)."""
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
            if g[n[1]][n[0]] in SOLID:
                continue
            seen.add(n)
            todo.append(n)
    return seen


def sight(g, x, y, dirs, n) -> set[tuple[int, int]]:
    out = set()
    for d in dirs:
        dx, dy = {"N": (0, -1), "E": (1, 0), "S": (0, 1), "W": (-1, 0)}[d]
        for k in range(1, n + 1):
            c = (x + dx * k, y + dy * k)
            if g[c[1]][c[0]] in SOLID or c in CUT:
                break
            out.add(c)
    return out


def check(g, d) -> None:
    """The route's rules: only the three ways open onto the edges; through the gatehouse, everything walkable is
    reached from Lavender's road, and the gatehouse is the only way from it down to the cliff top; with Snorlax
    asleep, Route 13 isn't reached from Lavender or Route 11, and Route 11's road and the deck are reached from
    Lavender; without the trees cut, the pocket isn't reached; the trees stand more than 8 blocks from the edges
    you come in by (KR-45); every door can be walked into (the gatehouse's back from above), every sign read; the
    people, items and hidden items are on open ground and each trainer sees some of the way."""
    edge = {(x, y) for y in range(MAP_H) for x in range(MAP_W) if x in (0, MAP_W - 1) or y in (0, MAP_H - 1)}
    assert {xy for xy in edge if g[xy[1]][xy[0]] not in SOLID} == set(NORTH + WEST + SOUTH), "only the three ways"
    walk = {(x, y) for y in range(MAP_H) for x in range(MAP_W) if g[y][x] not in SOLID}
    front = d["N"][0:2]
    back = d["N"][2:4]
    through = [((bx, by - 1), (fx, fy + 1)) for (bx, by), (fx, fy) in zip(back, front)]
    every = reachable(g, NORTH, links=through)
    assert walk <= every and set(WEST + SOUTH) <= every, f"blocks you can't reach: {sorted(walk - every)[:8]}"
    assert not reachable(g, NORTH) & {(fx, fy + 1) for fx, fy in front}, "the gatehouse must be the only way down"
    asleep = reachable(g, NORTH + WEST, {SNORLAX}, through)
    assert not set(SOUTH) & asleep and set(WEST) <= asleep, "Snorlax must close the way south, and only it"
    uncut = reachable(g, NORTH, set(CUT), through)
    assert POCKET not in uncut and POCKET in every, "the pocket is behind its trees"
    for x, y in CUT:
        assert x > 8 and 6 < y < MAP_H - 7, f"the game would hide the tree at ({x},{y}) (KR-45)"
    for letter, ds in d.items():
        behaviors = BUILDINGS[letter][2]
        assert len(ds) == len(behaviors), f"{letter}'s doors"
        for (x, y), mb in zip(ds, behaviors):
            way_in = (x, y - 1) if mb == BACK else (x, y + 1)
            assert way_in in every, f"the door of {letter} at ({x},{y}) can't be walked into"
    for y in range(MAP_H):
        for x in range(MAP_W):
            if g[y][x] == "S":
                assert (x, y + 1) in every, f"the sign at ({x},{y}) can't be read"
    people = [(x, y) for x, y, _ in TRAINERS] + COUPLE + ITEMS + [SNORLAX]
    assert len(set(people + CUT)) == len(people + CUT), "two events on one block"
    for x, y, look in TRAINERS:
        assert (x, y) in walk, f"the trainer at ({x},{y}) stands on open ground"
        assert sight(g, x, y, *look) - set(people), f"the trainer at ({x},{y}) sees nothing"
    assert all(xy in walk for xy in COUPLE + ITEMS + HIDDEN + CUT), "the people and items on open ground"
    assert g[CARVANHA[1]][CARVANHA[0]] == "s", "the Carvanha swims in the sea"


def main() -> None:
    g = plan()
    d = doors(g)
    kit.check_forest(g)
    kit.check_water(g)
    kit.check_paving(g)
    check(g, d)
    base = kit.primary(HERE)  # the kit: the primary tileset every map shares
    spec_mt = list(base["metatiles"])
    pals = {}
    for letter, (folder, bank, behaviors) in BUILDINGS.items():
        b, ds = load(letter)
        pals.setdefault(bank, b.palette)
        assert pals[bank] == b.palette, f"{b.name}: its palette isn't the one bank {bank} has"
        open_, behavior = [], {}
        for (dx, dy), mb in zip(ds, behaviors):
            open_.append(f"{dx},{dy}")
            behavior[f"{dx},{dy}"] = mb
        sh = kit.Sheet(b.name, b.palette, bank, HERE, HERE, cols=b.idx.shape[1] // 16)
        sh.add(b.name, b.idx, tileset="secondary", ground="grass", solid=True, open=open_, behaviors=behavior)
        spec_mt += sh.write()
    # the bridge's last row lands on the islet's lawn (row 60): its boards end on a plain dark edge there, not on the
    # beam and posts the dock has over water (dock#mask+landing, drawn where the plan has LANDING)
    sh = kit.Sheet("dock_landing", kit.PALS["wood"], kit.BANK["wood"], HERE, HERE, cols=8)
    for m in range(16):
        if m & 4:
            continue
        t = kit.planks(m | 4)
        t[15, :] = kit.D_OUT
        sh.add(f"dock#{m}+landing", t, tileset="secondary", ground="grass", dedupe=True)
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
    (HERE / "border.txt").write_text("ss\nss\n")
    legend = dict(kit.LEGEND, **{k: load(k)[0].name for k in BUILDINGS})
    # the road from Lavender runs up to the gatehouse's back door with no lawn rim; Route 11's dirt road runs straight
    # onto the fishers' deck (its only touch with the dock), with no lawn rim or plank edge between them
    legend["N"] = {"name": legend["N"], "joins": "="}
    legend[":"] = {"auto": "dirt", "joins": "d"}
    legend[LANDING] = {"auto": "dock", "joins": "d", "with": "landing"}
    (HERE / "legend.json").write_text(json.dumps(legend, indent=1) + "\n")
    (HERE / "doors.json").write_text(json.dumps(d, indent=1) + "\n")
    print(f"{len(spec_mt)} metatiles in the spec; grid {MAP_W}x{MAP_H}; doors {d}")


if __name__ == "__main__":
    main()
