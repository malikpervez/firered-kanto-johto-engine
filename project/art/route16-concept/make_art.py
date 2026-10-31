#!/usr/bin/env python3
"""Route 16 after its concept (draw_plan.py and plan_stage1.txt): where Celadon's boulevard runs out west into a wooded
valley and Cycling Road begins (see draw_plan.py). It is 56x44 blocks (old Route 16 was 64x52); its joins: Celadon's
boulevard (its rows 20-23) at the right edge, rows 22-25 (offset 2), and Cycling Road (Route 17) below the bottom edge,
its road at columns 12-17 (offset 0).

The pieces: the kit's, the Cycling Road gatehouse (Kanto Buildings Remakes v0.3, ../packs/buildings_v0.3) in Saffron's buildings' palette
(bank 9), and Viridian's pond keeper's house (bank 7). Bank 8 is the kit's plants palette; 10-12 stay free for the
seam to old Route 17, whose strip in this route (the bottom seven rows) is forest and road only.

Run from the repository root:  python3 project/art/route16-concept/make_art.py
It writes buildings/, sheets/, the palettes, spec.json, grid.txt, border.txt, legend.json and doors.json next to
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
import kit

HERE = Path(__file__).resolve().parent
ART = HERE.parent
VB = ART / "viridian-concept/buildings"
SECONDARY = "gTileset_Route16Concept"
MAP_W, MAP_H = 56, 44
HOUSE_BANK, GATE_BANK = 7, 9
EAST = [(MAP_W - 1, y) for y in range(22, 26)]
SOUTH = [(x, MAP_H - 1) for x in range(12, 18)]
SOLID = set("T#bRoklSBcw_~vrCY")
DOOR, IN_EAST, IN_WEST = "MB_ANIMATED_DOOR", "MB_EAST_ARROW_WARP", "MB_WEST_ARROW_WARP"
# the buildings: their letters in the plan, their packs, their banks, and what each of their doors does (the
# gatehouse's doorways: the left one entered walking east, the right one walking west)
BUILDINGS = {"C": (buildings.REMAKES / "cycling_gate", GATE_BANK, [IN_EAST, IN_WEST]),
             "Y": (VB / "house_pond_keeper", HOUSE_BANK, [DOOR])}
SNORLAX = (44, 24)       # asleep in the gap between the outcrops
TREES = [(46, 21)]       # the tree to cut, in the hedge north of the road: the woodland path behind it
HALLS = [((28, 24), (35, 24)), ((28, 12), (35, 12))]  # the gatehouse's lower and upper halls: doorway to doorway
BIKERS = [(11, 29), (18, 29), (11, 32), (18, 32), (9, 30), (20, 31)]  # looking about, a block of sight
COUPLE = [(40, 11), (41, 11)]   # Lea and Jed, looking down onto the woodland path
ROAD_DOWN = [(x, y) for x in (14, 15) for y in range(28, MAP_H)]
STRIP = 7                # the rows of this route old Route 17 draws


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
    assert len(g) == MAP_H and all(len(r) == MAP_W for r in g), "the plan is 56x44"
    return g


def doors(g) -> dict[str, list[tuple[int, int]]]:
    out = {}
    for letter in BUILDINGS:
        b, ds = load(letter)
        bw, bh = b.idx.shape[1] // 16, b.idx.shape[0] // 16
        cells = {(x, y) for y, r in enumerate(g) for x, c in enumerate(r) if c == letter}
        tops = sorted({(x, y) for x, y in cells if (x - 1, y) not in cells and (x, y - 1) not in cells})
        out[letter] = []
        for x0, y0 in tops:  # one or more copies of the pack
            assert {(x0 + i, y0 + j) for i in range(bw) for j in range(bh)} <= cells, f"{letter} isn't its footprint"
            out[letter] += [(x0 + dx, y0 + dy) for dx, dy in ds]
        assert len(cells) == len(tops) * bw * bh, f"{letter} isn't whole copies of its footprint"
    return out


def reachable(g, starts, blocked=frozenset(), links=()) -> set[tuple[int, int]]:
    """Blocks you can walk to from ``starts``; a building's doorways are open ground, and ``links`` join pairs of
    them (a hall through a gatehouse)."""
    hop = {}
    for a, b in links:
        hop.setdefault(a, []).append(b)
        hop.setdefault(b, []).append(a)
    doorways = {d for pair in HALLS for d in pair}
    seen, todo = set(starts), deque(starts)
    while todo:
        x, y = todo.popleft()
        for n in [(x + 1, y), (x - 1, y), (x, y + 1), (x, y - 1)] + hop.get((x, y), []):
            if not (0 <= n[0] < MAP_W and 0 <= n[1] < MAP_H) or n in seen or n in blocked:
                continue
            if g[n[1]][n[0]] in SOLID and n not in doorways:
                continue
            seen.add(n)
            todo.append(n)
    return seen


def sight(g, x, y, n) -> set[tuple[int, int]]:
    out = set()
    for dx, dy in ((1, 0), (-1, 0), (0, 1), (0, -1)):
        for k in range(1, n + 1):
            c = (x + dx * k, y + dy * k)
            if g[c[1]][c[0]] in SOLID:
                break
            out.add(c)
    return out


def check(g, d) -> None:
    """The route's rules: only Celadon's road and Cycling Road's open onto the edges; until Snorlax wakes, Celadon's
    side reaches neither the gatehouse's lower hall nor Cycling Road, and until the tree is cut, not the woodland
    path; with both, and the halls walked through, everything walkable is reached, the glade only by the upper hall
    (never from the plaza: no way round the gatehouse's bike rule); the tree stands more than 8 blocks from the edges
    you come in by (KR-45); the road down to Cycling Road is in no biker's sight; every doorway can be walked into,
    every sign read; the strip old Route 17 draws is forest and road only."""
    edge = {(x, y) for y in range(MAP_H) for x in range(MAP_W) if x in (0, MAP_W - 1) or y in (0, MAP_H - 1)}
    assert {xy for xy in edge if g[xy[1]][xy[0]] not in SOLID} == set(EAST + SOUTH), "only the two roads open"
    walk = {(x, y) for y in range(MAP_H) for x in range(MAP_W) if g[y][x] not in SOLID}
    asleep = reachable(g, EAST, {SNORLAX, *TREES}, HALLS)
    assert not asleep & set(SOUTH) and HALLS[0][1] not in asleep, "Snorlax must close the way"
    assert (46, 20) not in asleep, "the tree must close the woodland path"
    every = reachable(g, EAST, links=HALLS)
    assert walk <= every, f"blocks you can't reach: {sorted(walk - every)[:8]}"
    plaza = reachable(g, SOUTH, {HALLS[0][0], HALLS[1][0]})
    assert (17, 12) not in plaza, "the glade must be closed off from the plaza"
    assert all(8 < x < MAP_W - 9 and y < MAP_H - 9 for x, y in TREES), "the game would hide the tree"
    seen = set().union(*(sight(g, x, y, 1) for x, y in BIKERS))
    assert not seen & set(ROAD_DOWN), f"the road down is in a biker's sight at {sorted(seen & set(ROAD_DOWN))}"
    assert all(g[y][x] not in SOLID for x, y in BIKERS + COUPLE), "the trainers stand on open ground"
    for letter, ds in d.items():
        for (x, y), mb in zip(ds, BUILDINGS[letter][2] * 2):
            front = {DOOR: (x, y + 1), IN_EAST: (x - 1, y), IN_WEST: (x + 1, y)}[mb]
            assert front in every and g[front[1]][front[0]] not in SOLID, f"the door at ({x},{y}) can't be walked into"
    for y in range(MAP_H):
        for x in range(MAP_W):
            if g[y][x] == "S":
                assert (x, y + 1) in every, f"the sign at ({x},{y}) can't be read"
    assert {g[y][x] for y in range(MAP_H - STRIP, MAP_H) for x in range(MAP_W)} == {"T", "="}, "Route 17's strip"


ROAD_ROCKS = [(x, y) for y in (22, 23, 25) for x in range(43, 46)]  # the outcrops either side of Snorlax's gap
ROCK_CHARS = iter("ǎǐǒǔǖǘǚǜǟǡ")
MOUTH = [(x, 27) for x in range(12, 18)]   # the plaza's paving opening into the road down to Cycling Road...
MOUTH_TO = [(x, 28) for x in range(12, 18)]  # ...and the paving's change to its cobble, a row below
# the plaza's paving and the road's cobble run up to the lower hall's doorways (28,24 and 35,24)
DOORSTEPS = {(27, 24): ("Ǣ", {"name": "paving#15", "joins": "p"}), (36, 24): ("Ǥ", {"name": "cobble#15", "joins": "="}),
             # the woodland path runs into the upper hall's doorways (28,12 and 35,12): its edge on the north only
             (27, 12): ("ǥ", {"name": "dirt#14", "joins": ":"}), (36, 12): ("ǥ", {"name": "dirt#14", "joins": ":"})}


def rock_name(x: int, y: int) -> str:
    """The rock "o" picks at (x, y) (as pae map paint picks)."""
    return kit.ROCKS[(x * 7919 + y * 104729 + (x * y) % 13) % len(kit.ROCKS)]


def settle_road(g) -> tuple[dict, list]:
    """The rocks in the road stand on its cobble (each over the cobble pae would draw there, the rocks counted as
    cobble, and cobble for the cobble round them, so it draws no lawn rim round them); the paving opens into the road
    to Cycling Road and turns to cobble a row down; the doorsteps of the lower hall."""
    legend, made = {}, {}
    sh = kit.Sheet("rocks_on_cobble", kit.PALS["ground"], kit.BANK["ground"], HERE, HERE, cols=4)
    same = lambda xx, yy: g[yy][xx] == "=" or (xx, yy) in ROAD_ROCKS
    for x, y in ROAD_ROCKS:
        assert g[y][x] == "o", f"no rock at ({x},{y})"
        mask = sum(b for b, (dx, dy) in ((1, (0, -1)), (2, (1, 0)), (4, (0, 1)), (8, (-1, 0))) if same(x + dx, y + dy))
        name = f"{rock_name(x, y)}@cobble#{mask}"
        if name not in made:
            made[name] = next(ROCK_CHARS)
            sh.add(name, kit.field_rock(rock_name(x, y)), tileset="secondary", ground=f"cobble#{mask}", solid=True)
            legend[made[name]] = {"name": name, "joins": "="}
    for x, y in ROAD_ROCKS:
        mask = sum(b for b, (dx, dy) in ((1, (0, -1)), (2, (1, 0)), (4, (0, 1)), (8, (-1, 0))) if same(x + dx, y + dy))
        g[y][x] = made[f"{rock_name(x, y)}@cobble#{mask}"]
    for (x, y), (ch, item) in DOORSTEPS.items():
        assert g[y][x] == item["joins"], f"no {item['joins']} at ({x},{y})"
        g[y][x] = ch
        legend[ch] = item
    for (x, y), (x2, y2) in zip(MOUTH, MOUTH_TO):
        assert g[y][x] == "p" and g[y2][x2] == "="
        g[y][x], g[y2][x2] = "ǽ", "ǿ"
    legend["ǽ"] = {"name": "paving#15", "joins": "p"}
    legend["ǿ"] = {"name": "paving_to_cobble_S", "joins": "="}
    return legend, sh.write()


def main() -> None:
    g = plan()
    d = doors(g)
    kit.check_forest(g)
    kit.check_water(g)
    kit.check_paving(g)
    check(g, d)
    road_legend, road_mt = settle_road(g)
    base = kit.primary(HERE)  # the kit: the primary tileset every map shares
    spec_mt = list(base["metatiles"]) + road_mt
    pals = {}
    for letter, (folder, bank, behaviors) in BUILDINGS.items():
        b, ds = load(letter)
        pals.setdefault(bank, b.palette)
        assert pals[bank] == b.palette, f"{b.name}: its palette isn't the one bank {bank} has"
        bw = b.idx.shape[1] // 16
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
                         "secondary": [f"palette_{HOUSE_BANK}.pal", base["secondary_palettes"][8],
                                       f"palette_{GATE_BANK}.pal"]},
            "reserve": {"primary": base["reserve"]},
            "animations": base["animations"],
            "field_effects": base["field_effects"],
            "metatiles": spec_mt}
    (HERE / "spec.json").write_text(json.dumps(spec, indent=1) + "\n")
    (HERE / "grid.txt").write_text("".join("".join(r) + "\n" for r in g))
    (HERE / "border.txt").write_text("TT\nTT\n")
    legend = dict(kit.LEGEND, **{k: load(k)[0].name for k in BUILDINGS}, **road_legend)
    (HERE / "legend.json").write_text(json.dumps(legend, indent=1) + "\n")
    (HERE / "doors.json").write_text(json.dumps(d, indent=1) + "\n")
    print(f"{len(spec_mt)} metatiles in the spec; grid {MAP_W}x{MAP_H}; doors {d}")


if __name__ == "__main__":
    main()
