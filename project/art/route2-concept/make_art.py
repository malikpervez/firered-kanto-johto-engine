#!/usr/bin/env python3
"""Route 2 after the concept (concept.png, plan_stage1.txt and plan_metadata.json, made with another AI from a
brief): the road north from Viridian City to Pewter City. Viridian Forest (a map of its own) is the way through:
the south meadow's only way on is the forest's south gate, and the forest's north gate opens onto the north meadow
and the road to Pewter. With Cut, an eastern detour runs alongside: two items, the small east gatehouse (in at its
south door, out at its north one), a ledge with stairs, and the north enclave with the trade house and the north
entrance of Diglett's Cave, then back to the north meadow. The Friends' camp is a lawn west of the south road.

The route is 30x80 blocks, as before, and joins its neighbours where it did: Pewter's road meets the top at
columns 8-11, Viridian's the bottom at columns 6-11.

The buildings are native pixel packs (Route 2 Stage 2 Assets v0.3, made with another AI from a brief: buildings/):
the two forest gates (bank 7), the east gatehouse and the cave (the Route 22 rock and cliff pack's top and face
with a mouth cut in it; bank 10). The trade house is Viridian's family house, loaded from Viridian's folder as it
is. The east gatehouse's colours are the house's but two, so they share bank 9: the house keeps its palette and
the gatehouse's two other colours go in two entries the house doesn't use. Bank 8 is the kit's plants palette;
11-12 stay free for the seams (Pewter, not rebuilt yet).

Doors (the packs' own): the south forest gate's double door animates as one (two door blocks wide, build.sh); the
north forest gate and the east gatehouse are drawn open, and their north doors are entered walking south (you step
on the doorway and keep going, as on the old Route 2); the gatehouse's south door and the cave mouth are open
doorways entered walking north; the trade house's door animates as in Viridian.

Run from the repository root:  python3 project/art/route2-concept/make_art.py
It writes sheets/, the palettes, spec.json, grid.txt, border.txt and legend.json next to itself; build.sh turns them
into the game's tileset and map with pae.
"""
import json
import sys
from collections import deque
from dataclasses import dataclass, replace
from pathlib import Path

import numpy as np
from PIL import Image

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "kit"))
import kit

HERE = Path(__file__).resolve().parent
VIRIDIAN = HERE.parent / "viridian-concept"
SECONDARY = "gTileset_Route2Concept"
MAP_W, MAP_H = 30, 80
GATE_BANK, HOUSE_BANK, CAVE_BANK = 7, 9, 10
CUT_TREES = [(16, 68), (21, 30), (16, 14)]  # south, middle, north: FireRed's tree, events on the dirt path
ITEMS = [(19, 52), (25, 64)]
FRIENDS_CAMP = (2, 60, 6, 4)  # x, y, width, height: a lawn
EAST_GATE = ((21, 47), (21, 44))  # the east gatehouse's south and north doors: one way through, inside
SOLID = set("T#bRoklSBcw_~vrFNEUD")  # what you can't walk onto (ledges you hop only going south; doors are open)


@dataclass
class Building:
    name: str
    idx: np.ndarray  # palette indices, 16 px a block
    palette: list[tuple[int, int, int]]  # 16 colours, index 0 transparent
    doors: list[tuple[int, int]]  # door blocks, from the building's top-left


def load(folder: Path) -> Building:
    """A building from its pack: <name>.png (indexed, its palette in the PNG) and <name>.json (its footprint and its
    door blocks: ``door_blocks``, or the older packs' one ``door_block``)."""
    name = folder.name
    meta = json.loads((folder / f"{name}.json").read_text())
    with Image.open(folder / f"{name}.png") as im:
        if im.mode != "P":
            raise SystemExit(f"{folder}/{name}.png is not indexed")
        idx = np.array(im, np.uint8)
        flat = im.getpalette()[:48]
    fp = meta["footprint_blocks"]
    if idx.shape != (fp["height"] * 16, fp["width"] * 16):
        raise SystemExit(f"{name}: the picture is not its footprint ({fp['width']}x{fp['height']} blocks)")
    doors = [tuple(d) for d in meta["door_blocks"]] if "door_blocks" in meta else [tuple(meta["door_block"])]
    if name.startswith("forest_gate_"):
        idx = tidy_forest_gate(idx)
    return Building(name, idx, [tuple(flat[i:i + 3]) for i in range(0, 48, 3)], doors)


def tidy_forest_gate(idx: np.ndarray) -> np.ndarray:
    """Two slips in both forest gates' pack art (the same pixels in each): the window band under the eaves ends in a
    7th window cut off by the right-hand pillar, and a corner of the stone base slab sticks out past that pillar onto
    the grass. The sliver becomes the band's plain end, as at its left end (frame, pale strip, dark wall), and the
    stray slab goes (the baked grass shows, as at the left corner)."""
    idx = idx.copy()
    band = idx[51:60, 112:116]
    assert (band[2, :2] == 14).all(), "the gates' window band moved"
    band[:8] = [3, 11, 2, 2]  # rows 51-58: frame, pale strip, dark wall (the left end's 2,2,11,3 mirrored)
    band[8] = [2, 11, 2, 2]  # row 59, under the band
    assert (idx[89:95, 124:127] != 0).all(), "the gates' base slab moved"
    idx[88:96, 124:128] = 0
    return idx


# the buildings: their letters in the plan, where each comes from, its palette's bank, and what each door does
BUILDINGS = {
    "F": ("forest_gate_south", HERE / "buildings", GATE_BANK, ["MB_ANIMATED_DOOR", "MB_ANIMATED_DOOR"]),
    "N": ("forest_gate_north", HERE / "buildings", GATE_BANK, ["MB_SOUTH_ARROW_WARP", "MB_SOUTH_ARROW_WARP"]),
    "E": ("east_gatehouse", HERE / "buildings", HOUSE_BANK, ["MB_NON_ANIMATED_DOOR", "MB_SOUTH_ARROW_WARP"]),
    "U": ("house_family", VIRIDIAN / "buildings", HOUSE_BANK, ["MB_ANIMATED_DOOR"]),
    "D": ("diglett_cave", HERE / "buildings", CAVE_BANK, ["MB_NON_ANIMATED_DOOR"]),
}
UNDER_DOORS = {"N": "dirt"}  # the north gate's doorway shows the dirt path coming up to it (its pack's underlay)


def buildings() -> dict[str, Building]:
    out = {letter: load(folder / name) for letter, (name, folder, _, _) in BUILDINGS.items()}
    assert out["F"].palette == out["N"].palette, "the two forest gates share their pack's palette"
    out["E"] = share_palette(out["E"], out["U"])
    out["U"] = replace(out["U"], palette=out["E"].palette)  # its own, and the gatehouse's two in entries it doesn't use
    return out


def share_palette(b: Building, house: Building) -> Building:
    """``b`` in the house's palette: its colours where the house has them, the others in entries the house doesn't
    use (nor its drawn door frames)."""
    with Image.open(VIRIDIAN / "buildings" / "house_family" / "house_family_door.png") as im:
        frames = np.array(im.convert("RGBA")).reshape(-1, 4)
    used = set(np.unique(house.idx).tolist()) | {house.palette.index(tuple(c[:3])) for c in frames if c[3]}
    pal = list(house.palette)  # (index 0 is transparent: the house's own colour there stays)
    free = [i for i in range(1, 16) if i not in used]
    lut = np.zeros(16, np.uint8)
    for i in sorted(set(np.unique(b.idx).tolist()) - {0}):
        c = b.palette[i]
        have = [j for j in range(1, 16) if pal[j] == c]
        if have:
            j = have[0]
        else:
            assert free, f"{b.name}: its colours and the house's don't fit in one palette"
            j = free[0]
            pal[j] = c
        if j in free:
            free.remove(j)
        lut[i] = j
    return Building(b.name, lut[b.idx], pal, b.doors)


def plan() -> list[list[str]]:
    rows = (HERE / "plan_stage1.txt").read_text().split("\n")[:MAP_H]
    g = [list(r) for r in rows]
    assert len(g) == MAP_H and all(len(r) == MAP_W for r in g), "the plan is 30x80"
    return g


def fit(g: list[list[str]]) -> list[list[str]]:
    """The plan as the kit builds it: the trees to cut (``x``) are the dirt path under them and the item balls
    (``i``) the lawn under them (both are events); the Friends' camp (``f``) is lawn; each door ``@`` is its
    building's letter."""
    h, w = len(g), len(g[0])
    for y in range(h):
        for x in range(w):
            g[y][x] = {"x": ":", "i": ".", "f": "."}.get(g[y][x], g[y][x])
    for y in range(h):
        for x in range(w):
            if g[y][x] == "@":
                near = [g[y + dy][x + dx] for dx, dy in ((-1, 0), (1, 0), (0, -1), (0, 1))
                        if 0 <= x + dx < w and 0 <= y + dy < h and g[y + dy][x + dx] in BUILDINGS]
                g[y][x] = near[0]
    assert [(x, y) for x, y in CUT_TREES if g[y][x] != ":"] == [], "the trees to cut stand on the path"
    return g


def placed(g, b: dict[str, Building]) -> dict[str, tuple[int, int]]:
    """Each building's top-left block on the map (where its letters start)."""
    out = {}
    for letter, bb in b.items():
        cells = [(x, y) for y, r in enumerate(g) for x, c in enumerate(r) if c == letter]
        x0, y0 = min(x for x, _ in cells), min(y for _, y in cells)
        bh, bw = bb.idx.shape[0] // 16, bb.idx.shape[1] // 16
        assert sorted(cells) == sorted((x0 + i, y0 + j) for i in range(bw) for j in range(bh)), \
            f"{bb.name}: the plan's {letter} isn't its {bw}x{bh} footprint"
        out[letter] = (x0, y0)
    return out


def door_blocks(g, b) -> dict[str, list[tuple[int, int]]]:
    at = placed(g, b)
    return {k: [(at[k][0] + dx, at[k][1] + dy) for dx, dy in b[k].doors] for k in b}


def reachable(g, start, doors, cut=(), inside=True) -> set[tuple[int, int]]:
    """The blocks you can walk to from ``start``: doors are open, the trees in ``cut`` are cut, ledges are hopped
    going south only; ``inside``: the east gatehouse takes you between its two doors."""
    h, w = len(g), len(g[0])
    blocked = {t for t in CUT_TREES if t not in cut} | set(ITEMS)
    seen, todo = {start}, deque([start])
    while todo:
        x, y = todo.popleft()
        steps = [(x + dx, y + dy, dy) for dx, dy in ((1, 0), (-1, 0), (0, 1), (0, -1))]
        if inside and (x, y) in EAST_GATE:
            other = EAST_GATE[1 - EAST_GATE.index((x, y))]
            steps.append((other[0], other[1], 0))
        for nx, ny, dy in steps:
            if not (0 <= nx < w and 0 <= ny < h) or (nx, ny) in seen or (nx, ny) in blocked:
                continue
            c = g[ny][nx]
            if c == "_":
                if dy == 1 and ny + 1 < h and g[ny + 1][nx] not in SOLID:
                    seen.add((nx, ny + 1))
                    todo.append((nx, ny + 1))
                continue
            if c in SOLID and (nx, ny) not in doors:
                continue
            seen.add((nx, ny))
            todo.append((nx, ny))
    return seen


def check(g, b) -> dict[str, list[tuple[int, int]]]:
    """The plan's rules, with every way of cutting the trees: Viridian Forest is the only way north without Cut;
    the east detour opens one tree at a time; the east gatehouse can't be walked round outside; every door and
    item can be reached."""
    d = door_blocks(g, b)
    doors = {xy for v in d.values() for xy in v}
    south, north = (8, MAP_H - 1), (9, 0)
    for y, xs in ((0, range(8, 12)), (MAP_H - 1, range(6, 12))):
        assert [x for x in range(MAP_W) if g[y][x] not in SOLID] == list(xs), f"row {y}: the join's road moved"
    near = {k: [(x, y + 1) if k in "FUD" or (x, y) == EAST_GATE[0] else (x, y - 1) for x, y in v]
            for k, v in d.items()}
    from_south = reachable(g, south, doors)
    assert all(xy in from_south for xy in near["F"]), "the forest's south gate can't be reached from Viridian"
    assert not set(near["N"]) & from_south and not set(near["E"]) & from_south, "the forest must be the way north"
    cx, cy, cw, chh = FRIENDS_CAMP
    assert all((cx + i, cy + j) in from_south for i in range(cw) for j in range(chh)), "the camp is off the road"
    assert reachable(g, (9, 0), doors) & set(near["N"]), "the forest's north gate can't be reached from Pewter"
    s, m, n = CUT_TREES
    one = reachable(g, south, doors, cut=[s])
    assert all(any(nb in one for nb in ((x + 1, y), (x - 1, y), (x, y + 1), (x, y - 1))) for x, y in ITEMS), \
        "the items are past the south tree"
    assert near["E"][0] in one and near["E"][1] in one and near["U"][0] not in one, "the middle tree must close it"
    two = reachable(g, south, doors, cut=[s, m])
    assert near["U"][0] in two and near["D"][0] in two and north not in two, "the north tree must close it"
    assert north in reachable(g, south, doors, cut=[s, m, n]), "with every tree cut, the detour reaches Pewter"
    assert near["E"][1] not in reachable(g, near["E"][0], doors - set(d["E"]), cut=CUT_TREES, inside=False), \
        "the east gatehouse can be walked round outside"
    return d


# ---------------------------------------------------------------- sheets and spec
def main() -> None:
    g = fit(plan())
    b = buildings()
    kit.check_forest(g)
    kit.check_water(g)
    doors = check(g, b)
    base = kit.primary(HERE)  # the kit: the primary tileset every map shares
    spec_mt = list(base["metatiles"])
    pals = {}
    for letter, (name, _, bank, behaviors) in BUILDINGS.items():
        bb = b[letter]
        pals.setdefault(bank, bb.palette)
        assert pals[bank] == bb.palette, f"{name}: its palette isn't the one bank {bank} has"
        bw, bh = bb.idx.shape[1] // 16, bb.idx.shape[0] // 16
        ground = ["grass"] * (bw * bh)
        open_, behavior = [], {}
        for (dx, dy), mb in zip(bb.doors, behaviors):
            open_.append(f"{dx},{dy}")
            behavior[f"{dx},{dy}"] = mb
            if letter in UNDER_DOORS:  # the path's piece under the doorway: open to the north and to the other door
                sides = 1 | sum(bit for bit, ox in ((2, 1), (8, -1)) if (dx + ox, dy) in bb.doors)
                ground[dy * bw + dx] = f"{UNDER_DOORS[letter]}#{sides}"
        sh = kit.Sheet(name, bb.palette, bank, HERE, HERE, cols=bw)
        sh.add(name, bb.idx, tileset="secondary", ground=ground if len(set(ground)) > 1 else "grass", solid=True,
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
                                       f"palette_{HOUSE_BANK}.pal", f"palette_{CAVE_BANK}.pal"]},
            "reserve": {"primary": base["reserve"]},
            "animations": base["animations"],
            "field_effects": base["field_effects"],
            "metatiles": spec_mt}
    (HERE / "spec.json").write_text(json.dumps(spec, indent=1) + "\n")
    (HERE / "grid.txt").write_text("".join("".join(r) + "\n" for r in g))
    (HERE / "border.txt").write_text("TT\nTT\n")
    legend = dict(kit.LEGEND, **{k: v[0] for k, v in BUILDINGS.items()})
    (HERE / "legend.json").write_text(json.dumps(legend, indent=1) + "\n")
    (HERE / "doors.json").write_text(json.dumps({BUILDINGS[k][0]: v for k, v in doors.items()}, indent=1) + "\n")
    print(f"{len(spec_mt)} metatiles in the spec; grid {MAP_W}x{MAP_H}; doors {doors}")


if __name__ == "__main__":
    main()
