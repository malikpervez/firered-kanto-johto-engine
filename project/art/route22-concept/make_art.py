#!/usr/bin/env python3
"""Route 22 after the concept (plan_stage1.txt and the packs, made with another AI from a brief): the hilly route
west of Viridian City to the Pokémon League Front Gate, between rocky cliffs and pine forest, with tall grass, a
pond, ledges and a dressed-stone approach up the stairs to the gate.

The route is 52x28 blocks, as before. Its road from Viridian leaves the right edge at rows 6-9 (Viridian's rows
28-31: Route 22's top row is Viridian's row 22). plan.txt is the stage 1 plan with the cliffs' faces two blocks tall
(the rock and cliff pack's): the forecourt's edge is a face now, with the pack's stairs, and a big boulder stands
east of it.

The pieces: the kit's (and its dressed-stone paving, a pack in the ground palette), the League Front Gate (a native
pixel pack, bank 7) and the rock and cliff pack (rock_cliff/, bank 9: meant for every route, but the kit has no
palette slot left, so it's Route 22's own for now). Bank 8 is the kit's plants palette.

The cliffs: ``C`` in the plan is a cliff's whole footprint. The bottom two blocks of each column of it are the face
(the pack's columns: an outer end beside the lawn, an inner one where it meets a cliff top or the stairs coming
further south, the three middles mixed between), the rest is the top. The top's texture repeats every three blocks
from the map's corner (its nine phases), each with its edges where the lawn is around it (the pack's recipes by its
neighbours).

Run from the repository root:  python3 project/art/route22-concept/make_art.py
It writes sheets/, the palettes, spec.json, grid.txt, border.txt and legend.json next to itself; build.sh turns them
into the game's tileset and map with pae.
"""
import json
import random
import sys
from collections import deque
from pathlib import Path

import numpy as np
from PIL import Image

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "kit"))
import buildings
import kit

HERE = Path(__file__).resolve().parent
SECONDARY = "gTileset_Route22Concept"
MAP_W, MAP_H = 52, 28
GATE_BANK, CLIFF_BANK = 7, 9
GATE_TOP = 4  # the gate's top rows (its roof) stand against the cliff: the cliff's top under them, not lawn
ROCK = HERE / "rock_cliff"
TOP = "ADEFGIJKV"  # the cliff's top, by its phase (1-9); the gate's top joins it (no edge between them)
FACE = {"[": "outer_W", "{": "inner_W", "M": "middle_1", "N": "middle_2", "P": "middle_3", "}": "inner_E",
        "]": "outer_E"}  # the face's columns (two blocks tall)
MIDDLES = "MNP"
SOLID = set("T#bRoklSBcw_~vrULX" + TOP + "".join(FACE))  # what you can't walk onto (ledges: going south only)
RIVAL_ROWS = range(6, 10)  # the road from Viridian, where Blue meets you
JOINS = "0123456789!$%&()"  # the cobble blocks over the stone approach's joins, by their cobble piece's mask


def plan() -> list[list[str]]:
    rows = (HERE / "plan.txt").read_text().split("\n")[:MAP_H]
    g = [list(r) for r in rows]
    assert len(g) == MAP_H and all(len(r) == MAP_W for r in g), "the plan is 52x28"
    return g


def phase(x: int, y: int) -> int:
    """The cliff top's phase at block (x, y): its texture repeats every three blocks from the map's corner."""
    return 1 + 3 * (y % 3) + x % 3


def fit(g):
    """The plan as the kit builds it: the gate's door is part of it, its top rows (against the cliff) are ``U``;
    where the stone approach meets the cobblestone road (the four blocks under it, as the pack says), the stone
    blocks are its joins to cobble ``n`` and the cobble blocks over them are drawn open to the south (digits: their
    cobble piece by its mask); the cliffs are their tops (by phase) and faces (cliffs())."""
    h, w = len(g), len(g[0])
    cells = [(x, y) for y in range(h) for x in range(w) if g[y][x] in "L@"]
    x0, y0 = min(x for x, _ in cells), min(y for _, y in cells)
    for x, y in cells:
        g[y][x] = "U" if y < y0 + GATE_TOP else "L"
    cliffs(g)
    joins = {}
    for y in range(1, h):
        for x in range(w):
            if g[y][x] == "p" and g[y - 1][x] == "=":
                g[y][x] = "n"
    for y in range(h - 1):
        for x in range(w):
            if g[y][x] == "=" and g[y + 1][x] == "n":
                mask = 4 | sum(bit for bit, (dx, dy) in ((1, (0, -1)), (2, (1, 0)), (8, (-1, 0)))
                               if 0 <= x + dx < w and 0 <= y + dy < h and g[y + dy][x + dx] in "=" + JOINS)
                joins[mask] = JOINS[mask]  # one character per piece used
                g[y][x] = joins[mask]
    return g, (x0, y0), joins


def cliffs(g) -> None:
    """``C`` (a cliff's footprint) as its top and its face: the bottom two blocks of each column of it are the face,
    the rest the top (none over the gate's roof: it stands against the top). A face's ends are outer beside the lawn,
    inner beside a top or the stairs."""
    h, w = len(g), len(g[0])
    face = {}  # (x, y of its upper block) -> column
    for x in range(w):
        y = 0
        while y < h:
            if g[y][x] != "C":
                y += 1
                continue
            y1 = y
            while y1 + 1 < h and g[y1 + 1][x] == "C":
                y1 += 1
            if y1 + 1 < h and g[y1 + 1][x] != "U":
                assert y1 > y, f"({x},{y}): a cliff needs two blocks for its face"
                face[x, y1 - 1] = None
            y = y1 + 1

    def end(x: int, y: int) -> str | None:  # what's beside a face: None (more face), "inner" or "outer"
        if (x, y) in face:
            return None
        assert (x, y + 1) not in face and (x, y - 1) not in face, f"({x},{y}): faces beside each other must line up"
        return "inner" if 0 <= x < w and g[y][x] in "CUH" and (x, y) not in face else "outer"
    for x, y in sorted(face, key=lambda c: (c[1], c[0])):  # west to east, the middles mixed (never one twice)
        west, east = end(x - 1, y), end(x + 1, y)
        assert not (west and east), f"({x},{y}): a face needs two columns at least"
        if west or east:
            face[x, y] = next(c for c, n in FACE.items() if n == (f"{west}_W" if west else f"{east}_E"))
        else:
            options = [c for c in MIDDLES if c != face.get((x - 1, y))]
            face[x, y] = options[random.Random(x * 1000 + y).randrange(len(options))]
    for y in range(h):
        for x in range(w):
            if g[y][x] == "C":
                g[y][x] = TOP[phase(x, y) - 1]
    for (x, y), c in face.items():
        g[y][x] = g[y + 1][x] = c


def reachable(g, start) -> set[tuple[int, int]]:
    """The blocks you can walk to from ``start`` (ledges hopped going south only)."""
    h, w = len(g), len(g[0])
    seen, todo = {start}, deque([start])
    while todo:
        x, y = todo.popleft()
        for dx, dy in ((1, 0), (-1, 0), (0, 1), (0, -1)):
            nx, ny = x + dx, y + dy
            if not (0 <= nx < w and 0 <= ny < h) or (nx, ny) in seen:
                continue
            c = g[ny][nx]
            if c == "_":
                if dy == 1 and ny + 1 < h and g[ny + 1][nx] not in SOLID:
                    seen.add((nx, ny + 1))
                    todo.append((nx, ny + 1))
                continue
            if c in SOLID:
                continue
            seen.add((nx, ny))
            todo.append((nx, ny))
    return seen


def check(g, door) -> None:
    """The road from Viridian is open; from it you reach the gate's door and the tall grass; Blue's road is
    straight and clear; the top seven rows (Route 23 shows them) have only forest, cliff and lawn."""
    h, w = len(g), len(g[0])
    walk = reachable(g, (w - 1, 7))
    assert all((w - 1, y) in walk for y in RIVAL_ROWS), "the road to Viridian must be open at rows 6-9"
    assert (door[0], door[1] + 1) in walk, "the gate's door can't be reached from Viridian"
    assert any(g[y][x] == "g" for x, y in walk), "the tall grass can't be reached"
    for y in RIVAL_ROWS:
        assert all(g[y][x] == "=" or g[y][x] in JOINS for x in range(36, 51)), \
            f"Blue's road (row {y}) must be cobblestone, clear"
    assert "C" not in "".join("".join(r) for r in g), "every cliff block is its top or its face"


def pack(rel: str) -> np.ndarray:
    """A picture of the rock and cliff pack as its palette's indices (0 transparent)."""
    with Image.open(ROCK / rel) as im:
        assert im.mode == "P" and im.getpalette()[:48] == _flat, f"{rel}: not in the pack's palette"
        return np.array(im)


with Image.open(ROCK / "tileset_8x8.png") as _im:  # the pack's palette, in its PNGs
    _flat = _im.getpalette()[:48]
CLIFF_PAL = [tuple(_flat[i:i + 3]) for i in range(0, 48, 3)]
_atlas = pack("tileset_8x8.png")
_recipes = {(r["phase"], r["mask"]): r["tiles_8x8"]
            for r in json.loads((ROCK / "autotile_recipes.json").read_text())["recipes"]}


def top(k: int, outside: int) -> np.ndarray:
    """The cliff top of phase ``k`` whose neighbours ``outside`` aren't cliff top (the pack's bits: 1 N, 2 E, 4 S,
    8 W, 16 NE, 32 SE, 64 SW, 128 NW), from its recipe: four tiles of its atlas."""
    out = np.zeros((16, 16), np.uint8)
    for j, row in enumerate(_recipes[k, outside]):
        for i, t in enumerate(row):
            out[8 * j:8 * j + 8, 8 * i:8 * i + 8] = _atlas[8 * (t // 16):8 * (t // 16) + 8, 8 * (t % 16):8 * (t % 16) + 8]
    return out


def tops_in(g) -> set[tuple[int, int, int]]:
    """The cliff tops the grid has, as pae paints them: (phase, mask of the sides that are top, inside corners)."""
    h, w = len(g), len(g[0])

    def same(x, y):  # the map's edges count as the same, as in pae
        return not (0 <= x < w and 0 <= y < h) or g[y][x] in TOP + "U"
    used = set()
    for y in range(h):
        for x in range(w):
            if g[y][x] in TOP:
                mask = sum(b for b, (dx, dy) in ((1, (0, -1)), (2, (1, 0)), (4, (0, 1)), (8, (-1, 0)))
                           if same(x + dx, y + dy))
                corners = sum(b for b, (dx, dy), sides in ((1, (1, -1), 3), (2, (1, 1), 6), (4, (-1, 1), 12),
                                                           (8, (-1, -1), 9))
                              if mask & sides == sides and not same(x + dx, y + dy))
                used.add((TOP.index(g[y][x]) + 1, mask, corners))
    return used


def top_name(k: int, mask: int, corners: int) -> str:
    return f"top{k}#{mask}" + (f".{corners}" if corners else "")


# ---------------------------------------------------------------- sheets and spec
def main() -> None:
    g, gate_at, joins = fit(plan())
    gate = buildings.load(HERE / "buildings" / "league_front_gate")
    door = (gate_at[0] + gate.door[0], gate_at[1] + gate.door[1])
    kit.check_forest(g)
    kit.check_water(g)
    kit.check_paving(g, "H")  # the stairs: the forecourt and the road open onto them
    check(g, door)
    base = kit.primary(HERE)  # the kit: the primary tileset every map shares
    spec_mt = list(base["metatiles"])
    # the rock and cliff pack (bank 9): the tops this route has (by phase, the sides that are top and the inside
    # corners; the pack's recipes count the sides and corners that aren't), the face's columns, the stairs, the rocks
    rock = kit.Sheet("rock_cliff", CLIFF_PAL, CLIFF_BANK, HERE, HERE)
    gw = gate.idx.shape[1] // 16
    under_roof = [phase(gate_at[0] + i, gate_at[1] + j) for j in range(GATE_TOP) for i in range(gw)]
    for k, mask, corners in sorted(tops_in(g) | {(k, 15, 0) for k in under_roof}):
        outside = (15 & ~mask) | sum(16 << i for i in range(4) if corners & 1 << i)
        rock.add(top_name(k, mask, corners), top(k, outside), tileset="secondary", ground="grass", solid=True)
    for c in sorted(set(FACE[ch] for r in g for ch in r if ch in FACE)):
        rock.add(f"face_{c}", pack(f"face/{c}.png"), tileset="secondary", ground="grass", solid=True)
    rock.add("rock_stairs", pack("face/stairs.png"), tileset="secondary")
    rock.add("small_rock", pack("rocks/small_rock.png"), tileset="secondary", ground="grass", solid=True)
    rock.add("big_boulder", pack("rocks/big_boulder.png"), tileset="secondary", ground="grass", solid=True)
    spec_mt += rock.write()
    # the gate (bank 7): its roof against the cliff's top (drawn under it, by phase), its front over the lawn; its
    # door animates (build.sh)
    sh = kit.Sheet("league_front_gate", gate.palette, GATE_BANK, HERE, HERE, cols=gw)
    sh.add("league_gate_top", gate.idx[:GATE_TOP * 16], tileset="secondary",
           ground=[top_name(k, 15, 0) for k in under_roof], solid=True)
    front = gate.entry()
    d = f"{gate.door[0]},{gate.door[1] - GATE_TOP}"
    front.update(open=[d], behaviors={d: "MB_ANIMATED_DOOR"})
    sh.add("league_gate_front", gate.idx[GATE_TOP * 16:], tileset="secondary", **front)
    spec_mt += sh.write()
    for e in spec_mt:  # sheets put "w"/"h" on everything; drop the 1x1 ones for readability
        if e["w"] == 1 and e["h"] == 1:
            del e["w"], e["h"]
    kit.write_palette(HERE / f"palette_{GATE_BANK}.pal", gate.palette)
    kit.write_palette(HERE / f"palette_{CLIFF_BANK}.pal", CLIFF_PAL)
    spec = {"version": "hns", "primary": kit.PRIMARY, "secondary": SECONDARY,
            "palettes": {"primary": base["palettes"],
                         "secondary": [f"palette_{GATE_BANK}.pal", base["secondary_palettes"][8],
                                       f"palette_{CLIFF_BANK}.pal"]},
            "reserve": {"primary": base["reserve"]},
            "animations": base["animations"],
            "field_effects": base["field_effects"],
            "metatiles": spec_mt}
    (HERE / "spec.json").write_text(json.dumps(spec, indent=1) + "\n")
    (HERE / "grid.txt").write_text("".join("".join(r) + "\n" for r in g))
    (HERE / "border.txt").write_text("TT\nTT\n")
    legend = dict(kit.LEGEND, U={"name": "league_gate_top", "joins": "C"}, L="league_gate_front",
                  n={"name": "paving_to_cobble_N", "joins": "p"}, H={"name": "rock_stairs", "joins": "p"}, o="small_rock", X="big_boulder")
    for k, ch in enumerate(TOP, 1):  # the tops by phase, all one cliff (with the gate's top) for their edges
        legend[ch] = {"auto": f"top{k}", "joins": "C"}
    for ch, col in FACE.items():
        legend[ch] = f"face_{col}"
    for mask, ch in joins.items():  # the cobble over the joins: open to the south
        legend[ch] = {"name": f"cobble#{mask}", "joins": "="}
    (HERE / "legend.json").write_text(json.dumps(legend, indent=1) + "\n")
    print(f"{len(spec_mt)} metatiles in the spec; grid {MAP_W}x{MAP_H}; the gate at {gate_at}, its door {door}")


if __name__ == "__main__":
    main()
