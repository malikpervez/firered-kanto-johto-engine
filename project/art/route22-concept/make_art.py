#!/usr/bin/env python3
"""Route 22 after the concept (plan_stage1.txt and the packs, made with another AI from a brief): the hilly route
west of Viridian City to the Pokémon League Front Gate, between rocky cliffs and pine forest, with tall grass, a
pond, ledges and a dressed-stone approach up the stairs to the gate.

The route is 52x28 blocks, as before. Its road from Viridian leaves the right edge at rows 6-9 (Viridian's rows
28-31: Route 22's top row is Viridian's row 22). Its top seven rows, which Route 23 (an old map) shows across the
join, are forest and cliff only.

The pieces: the kit's (and its dressed-stone paving, a pack in the ground palette), the League Front Gate (a native
pixel pack, bank 7) and the rocky cliffs (a 16-piece pack like the water's, bank 9: meant for every route, but the
kit has no palette slot left, so they're Route 22's own for now). Bank 8 is the kit's plants palette; 10-12 stay
free for Route 23's seam.

Run from the repository root:  python3 project/art/route22-concept/make_art.py
It writes sheets/, the palettes, spec.json, grid.txt, border.txt and legend.json next to itself; build.sh turns them
into the game's tileset and map with pae.
"""
import json
import sys
from collections import deque
from pathlib import Path

from PIL import Image

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "kit"))
import autotile
import buildings
import kit

HERE = Path(__file__).resolve().parent
SECONDARY = "gTileset_Route22Concept"
MAP_W, MAP_H = 52, 28
GATE_BANK, CLIFF_BANK = 7, 9
GATE_TOP = 4  # the gate's top rows (its roof) stand against the cliff: cliff under them, not lawn
CLIFF = ("C", "U")  # the cliff, and the gate's top (it joins the cliff: no edge between them)
SOLID = set("T#bRoklSBcw_~vrCUL")  # what you can't walk onto (ledges you hop only going south)
RIVAL_ROWS = range(6, 10)  # the road from Viridian, where Blue meets you
JOINS = "0123456789!$%&()"  # the cobble blocks over the stone approach's joins, by their cobble piece's mask


def plan() -> list[list[str]]:
    rows = (HERE / "plan_stage1.txt").read_text().split("\n")[:MAP_H]
    g = [list(r) for r in rows]
    assert len(g) == MAP_H and all(len(r) == MAP_W for r in g), "the plan is 52x28"
    return g


def fit(g):
    """The plan as the kit builds it: the gate's door is part of it, its top rows (against the cliff) are ``U``;
    where the stone approach meets the cobblestone road (the four blocks under it, as the pack says), the stone
    blocks are its joins to cobble ``n`` and the cobble blocks over them are drawn open to the south (digits: their
    cobble piece by its mask)."""
    h, w = len(g), len(g[0])
    cells = [(x, y) for y in range(h) for x in range(w) if g[y][x] in "L@"]
    x0, y0 = min(x for x, _ in cells), min(y for _, y in cells)
    for x, y in cells:
        g[y][x] = "U" if y < y0 + GATE_TOP else "L"
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
    for y in range(7):
        assert all(c in "TC.=:" for c in g[y]), f"row {y}: Route 23 shows it; only forest, cliff, lawn and road"


def cliff_piece(name: str):
    if name not in _cliff:
        _cliff[name] = autotile.load(HERE / "cliff" / f"{name}.png", CLIFF_PAL)
    return _cliff[name]


_cliff: dict = {}
with Image.open(HERE / "cliff" / "center.png") as _im:  # the pack's palette, in its PNGs
    _flat = _im.getpalette()[:48]
CLIFF_PAL = [tuple(_flat[i:i + 3]) for i in range(0, 48, 3)]


# ---------------------------------------------------------------- sheets and spec
def main() -> None:
    g, gate_at, joins = fit(plan())
    gate = buildings.load(HERE / "buildings" / "league_front_gate")
    door = (gate_at[0] + gate.door[0], gate_at[1] + gate.door[1])
    kit.check_forest(g)
    kit.check_water(g)
    kit.check_paving(g)
    check(g, door)
    base = kit.primary(HERE)  # the kit: the primary tileset every map shares
    spec_mt = list(base["metatiles"])
    # the cliffs (bank 9): every way a block meets the rest, the inside corners this route has, and two more centres
    cliff = kit.Sheet("cliff", CLIFF_PAL, CLIFF_BANK, HERE, HERE)
    for m in range(16):
        cliff.add(f"cliff#{m}", autotile.compose(cliff_piece, m), tileset="secondary", ground="grass", solid=True)
    for v in (1, 2):
        cliff.add(f"cliff#15~{v}", autotile.compose(cliff_piece, 15, v), tileset="secondary", ground="grass",
                  solid=True)
    for m, c in sorted(autotile.corners_in(g, CLIFF, "C")):
        cliff.add(f"cliff#{m}.{c}", autotile.compose(cliff_piece, m, 0, c), tileset="secondary", ground="grass",
                  solid=True)
    spec_mt += cliff.write()
    # the gate (bank 7): its roof over the cliff, its front over the lawn; its door animates (build.sh)
    sh = kit.Sheet("league_front_gate", gate.palette, GATE_BANK, HERE, HERE, cols=gate.idx.shape[1] // 16)
    sh.add("league_gate_top", gate.idx[:GATE_TOP * 16], tileset="secondary", ground="cliff#15", solid=True)
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
    legend = dict(kit.LEGEND, C={"auto": "cliff"}, U={"name": "league_gate_top", "joins": "C"},
                  L="league_gate_front", n={"name": "paving_to_cobble_N", "joins": "p"})
    for mask, ch in joins.items():  # the cobble over the joins: open to the south
        legend[ch] = {"name": f"cobble#{mask}", "joins": "="}
    (HERE / "legend.json").write_text(json.dumps(legend, indent=1) + "\n")
    print(f"{len(spec_mt)} metatiles in the spec; grid {MAP_W}x{MAP_H}; the gate at {gate_at}, its door {door}")


if __name__ == "__main__":
    main()
