#!/usr/bin/env python3
"""Viridian City after the concept (concept.png and plan_stage1.txt, made with another AI from a brief): a leafy
forest-edge town around a square with the Pokémon Center and the Poké Mart, the Gym set apart in the northeastern
trees, a pond with ledges in the west, the Trainer School, three houses, the old man lying across the road north
and a hidden grove behind a tree to cut.

The town is 60x52 blocks (it was 56x50). Its exits stay where they met its neighbours: Route 2's road leaves the
top at columns 24-27, Route 22's the left edge at rows 28-31, Route 1's the bottom at columns 24-27.

The plan is the concept's own block grid; ``fit`` makes it something the kit can build (see there). The buildings
are native pixel packs too (buildings/): the Center and the Mart from the kit, the Gym, the school and the houses
of Viridian's own tileset, in two palettes (bank 7: the Gym and the school; bank 9: the houses). Bank 8 is the kit's
plants palette; 10-12 stay free for the seams to the routes that aren't rebuilt.

Run from the repository root:  python3 project/art/viridian-concept/make_art.py
It writes sheets/, the palettes, spec.json, grid.txt, border.txt and legend.json next to itself; build.sh turns them
into the game's tileset and map with pae.
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
SECONDARY = "gTileset_ViridianConcept"
MAP_W, MAP_H = 60, 52
# Viridian's own buildings (buildings/<name>/), their letters in the plan and their palettes' banks
OWN = {"G": ("viridian_gym", 7), "K": ("trainer_school", 7), "H": ("house_gardener", 9), "J": ("house_family", 9),
       "Y": ("house_pond_keeper", 9)}
SHARED = {"P": "pokemon_center", "M": "poke_mart"}
LOCKED = {"H", "Y"}  # houses with no inside (yet): their doors are shut (solid, a sign says they're locked)
# the events the plan places (the old man and the tree to cut are events, on dirt)
OLD_MAN = (25, 11)
CUT_TREE = (48, 42)
LAMPS = [(23, 26), (28, 26), (38, 21)]  # lamps' feet added beside the square and the Gym's court
SOLID = set("T#bRoklSBcw_~vrGKHJYPM")  # what you can't walk onto (ledges you hop only going south)
# the town props (Kanto Town Props v0.1, kit/props.py): (piece, x, y of its top-left block, the ground under it)
PROPS = [("bench_wood_south", 14, 17, "grass"), ("picnic_table", 4, 23, "grass"), ("fingerpost", 5, 26, "grass"),
         ("fingerpost", 22, 16, "grass"), ("bench_wood_west", 32, 32, "grass"), ("litter_bin", 29, 24, "grass"),
         ("bench_stone", 40, 24, "grass")]


def plan() -> list[list[str]]:
    rows = (HERE / "plan_stage1.txt").read_text().split("\n")[:MAP_H]
    g = [list(r) for r in rows]
    assert len(g) == MAP_H and all(len(r) == MAP_W for r in g), "the plan is 60x52"
    return g


def fit(g: list[list[str]]) -> list[list[str]]:
    """The plan as the kit builds it:

    - the events' cells (the old man ``n``, the tree to cut ``x``) are the dirt road under them;
    - the pond keeper's cottage is ``Y`` (``Q`` is the kit's sea rock), and each door ``@`` is its building's letter;
    - the forest is drawn in 2x2-block trees on an even grid: a 2x2 cell the plan has partly forest becomes all
      forest where the rest is plain lawn, else its forest blocks become bushes (still solid, so the old man's
      one-block road and the grove stay closed);
    - round trees and the well are 2x2, lamps 1x2 (the lamp above its foot): the plan's one-block ones grow where
      there's lawn for them, else they become a bush (trees) or are left out (lamps);
    - lily pads and reeds only grow in open water, with water all round: the plan's at the shore are plain water;
    - lamps and signs stand on the lawn beside the road and the Gym's court, not on its stones.
    """
    h, w = len(g), len(g[0])
    for y in range(h):
        for x in range(w):
            if g[y][x] in "nx":
                g[y][x] = ":"
            elif g[y][x] == "Q":
                g[y][x] = "Y"
    for y in range(h):  # doors: their building's letter (the one beside them)
        for x in range(w):
            if g[y][x] == "@":
                near = [g[y][x + dx] for dx in (-1, 1) if 0 <= x + dx < w and g[y][x + dx] in OWN.keys() | SHARED.keys()]
                g[y][x] = near[0]
    # the forest on the 2x2 grid
    for cy in range(0, h, 2):
        for cx in range(0, w, 2):
            cells = [(x, y) for y in (cy, cy + 1) for x in (cx, cx + 1)]
            n = sum(g[y][x] == "T" for x, y in cells)
            if 0 < n < 4:
                rest = [g[y][x] for x, y in cells if g[y][x] != "T"]
                fill = "T" if all(c in ".," for c in rest) else None
                for x, y in cells:
                    if fill and g[y][x] != "T":
                        g[y][x] = "T"
                    elif not fill and g[y][x] == "T":
                        g[y][x] = "b"

    def free(cells):
        return all(0 <= x < w and 0 <= y < h and g[y][x] in ".," for x, y in cells)
    singles = [(x, y, g[y][x]) for y in range(h) for x in range(w) if g[y][x] in "Rw"]
    for x, y, c in singles:  # each grows to 2x2 with the plan's block as one of its corners, where there's lawn
        for ox, oy in ((0, 0), (-1, 0), (0, -1), (-1, -1)):
            area = [(x + ox + i, y + oy + j) for j in (0, 1) for i in (0, 1)]
            if free([a for a in area if a != (x, y)]):
                for xx, yy in area:
                    g[yy][xx] = c
                break
        else:
            g[y][x] = "b" if c == "R" else "."
    # lamps and signs standing in the paved runs (two or more stone neighbours) move to the lawn beside them, the
    # stones closing over where they stood; then each lamp's head goes above its foot
    props = [(x, y, g[y][x]) for y in range(h) for x in range(w) if g[y][x] in "lS"]
    feet = []
    for x, y, c in props:
        around = [(xx, yy) for xx, yy in ((x - 1, y), (x + 1, y), (x, y - 1), (x, y + 1)) if 0 <= xx < w and 0 <= yy < h]
        if sum(g[yy][xx] == "=" for xx, yy in around) < 2:
            feet.append((x, y, c))
            continue
        g[y][x] = "="
        for xx, yy in ((x - 1, y), (x + 1, y), (x, y + 1), (x, y - 1), (x - 2, y), (x + 2, y)):
            if 0 <= xx < w and 0 <= yy < h and g[yy][xx] in ".," and (c == "S" or free([(xx, yy - 1)])):
                g[yy][xx] = c
                feet.append((xx, yy, c))
                break
    for x, y, c in feet:
        if c == "l":
            if free([(x, y - 1)]):
                g[y - 1][x] = "l"
            else:
                g[y][x] = "."
    # the lamps the plan stood in the road and on the Gym's court, on the lawn beside them: by the Center and the Mart
    # on the square, and on each side of the court
    for x, y in LAMPS:
        assert free([(x, y - 1), (x, y)]), f"no lawn for a lamp at ({x},{y})"
        g[y - 1][x] = g[y][x] = "l"
    # the road north meets Route 2's wider path (Viridian's columns 22-27): its first two rows widen to meet all of it
    for y in (0, 1):
        for x in (22, 23):
            g[y][x] = ":"
    # lily pads and reeds in open water only
    water = set("~vr")
    for y in range(h):
        for x in range(w):
            if g[y][x] in "vr" and not all(0 <= x + dx < w and 0 <= y + dy < h and g[y + dy][x + dx] in water
                                          for dx, dy in ((1, 0), (-1, 0), (0, 1), (0, -1))):
                g[y][x] = "~"
    return g


def reachable(g, blocked=()) -> set[tuple[int, int]]:
    """The blocks you can walk to from the road in from Route 1 (ledges hopped going south only)."""
    h, w = len(g), len(g[0])
    start = (25, h - 1)
    seen, todo = {start}, deque([start])
    while todo:
        x, y = todo.popleft()
        for dx, dy in ((1, 0), (-1, 0), (0, 1), (0, -1)):
            nx, ny = x + dx, y + dy
            if not (0 <= nx < w and 0 <= ny < h) or (nx, ny) in seen or (nx, ny) in blocked:
                continue
            c = g[ny][nx]
            if c == "_":  # a ledge: hop it going south onto the block below
                if dy == 1 and ny + 1 < h and g[ny + 1][nx] not in SOLID:
                    seen.add((nx, ny + 1))
                    todo.append((nx, ny + 1))
                continue
            if c in SOLID:
                continue
            seen.add((nx, ny))
            todo.append((nx, ny))
    return seen


def check(g) -> None:
    """The gates still gate: the old man alone closes the road north, the tree alone the grove; every door is
    reachable; the exits are open."""
    closed = reachable(g, {OLD_MAN, CUT_TREE})
    north = {(x, 0) for x in range(24, 28)}
    west = {(0, y) for y in range(28, 32)}
    grove = (52, 42)
    assert not north & closed, "the road north must be closed while the old man lies there"
    assert north & reachable(g, {CUT_TREE}), "the road north must open when he gets up"
    assert grove not in closed and grove in reachable(g, {OLD_MAN}), "the grove opens only by cutting the tree"
    assert west & closed, "the road west to Route 22 must be open"
    for letter, (x, y) in doors(g).items():
        assert (x, y + 1) in closed, f"the door of {letter} at ({x},{y}) can't be reached"


def doors(g) -> dict[str, tuple[int, int]]:
    """Each building's door block on the map, from where its letters start (its top-left) and its door block."""
    out = {}
    for letter, name in list(SHARED.items()) + [(k, v[0]) for k, v in OWN.items()]:
        cells = [(x, y) for y, r in enumerate(g) for x, c in enumerate(r) if c == letter]
        x0, y0 = min(x for x, _ in cells), min(y for _, y in cells)
        b = kit.SHARED_BUILDINGS[name][0] if letter in SHARED else load(name)
        out[letter] = (x0 + b.door[0], y0 + b.door[1])
    return out


def load(name: str) -> buildings.Building:
    return buildings.load(HERE / "buildings" / name)


# ---------------------------------------------------------------- sheets and spec
def main() -> None:
    g = fit(plan())
    prop_legend, prop_grounds = props.place(g, PROPS, SOLID)
    kit.check_forest(g)
    kit.check_water(g)
    check(g)
    base = kit.primary(HERE)  # the kit: the primary tileset every map shares
    spec_mt = list(base["metatiles"])
    pals = {}
    for letter, (name, bank) in OWN.items():
        b = load(name)
        pals.setdefault(bank, b.palette)
        if pals[bank] != b.palette:
            raise SystemExit(f"{name}: its palette isn't the one bank {bank} has")
        sh = kit.Sheet(name, b.palette, bank, HERE, HERE, cols=b.idx.shape[1] // 16)
        entry = b.entry() if letter not in LOCKED else {"ground": "grass", "solid": True}
        sh.add(name, b.idx, tileset="secondary", **entry)
        spec_mt += sh.write()
    prop_entries, prop_anims = props.pieces(HERE, HERE, prop_grounds)
    spec_mt += prop_entries
    # the kit's well stands on dirt and its barrel and crate on dock planks; here the well stands in the square's
    # paving and the barrels and crates on the lawn, so they get their own copies over that ground
    kit_mt = {e["name"]: e for e in base["metatiles"]}
    for name, new, ground in (("well", "well_cobble", "cobble#15"), ("barrel", "barrel_lawn", "grass"),
                              ("crate", "crate_lawn", "grass")):
        spec_mt.append(dict(kit_mt[name], name=new, tileset="secondary", ground=ground))
    for e in spec_mt:  # sheets put "w"/"h" on everything; drop the 1x1 ones for readability
        if e["w"] == 1 and e["h"] == 1:
            del e["w"], e["h"]
    for bank, pal in pals.items():
        kit.write_palette(HERE / f"palette_{bank}.pal", pal)
    spec = {"version": "hns", "primary": kit.PRIMARY, "secondary": SECONDARY,
            "palettes": {"primary": base["palettes"],
                         "secondary": ["palette_7.pal", base["secondary_palettes"][8], "palette_9.pal"]},
            "reserve": {"primary": base["reserve"]},
            "animations": base["animations"] + prop_anims,
            "field_effects": base["field_effects"],
            "metatiles": spec_mt}
    (HERE / "spec.json").write_text(json.dumps(spec, indent=1) + "\n")
    (HERE / "grid.txt").write_text("".join("".join(r) + "\n" for r in g))
    (HERE / "border.txt").write_text("TT\nTT\n")
    legend = dict(kit.LEGEND, **SHARED, **{k: v[0] for k, v in OWN.items()})
    legend.update(prop_legend)
    # the dirt paths run into the cobble roads with no grass rim between; the well sits in the paving
    legend[":"] = {"auto": "dirt", "joins": "="}
    legend["w"] = {"name": "well_cobble", "joins": "="}
    legend["B"], legend["c"] = "barrel_lawn", "crate_lawn"
    (HERE / "legend.json").write_text(json.dumps(legend, indent=1) + "\n")
    (HERE / "doors.json").write_text(json.dumps(doors(g), indent=1) + "\n")
    print(f"{len(spec_mt)} metatiles in the spec; grid {MAP_W}x{MAP_H}; doors {doors(g)}")


if __name__ == "__main__":
    main()
