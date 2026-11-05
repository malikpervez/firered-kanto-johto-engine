"""Terraces: cliffs in levels, so a mountain climbs in tiers set back one behind the other, as FireRed's do (the
owner, 4 November 2026: "some cliffs should be stacked but offset so it looks like a progressive hill").

A plan marks a cliff's blocks with its level, ``1`` to ``5`` (``C``, the plain cliff, is level 1); everything else is
the ground, level 0. The pieces are the Kanto Terraces pack v0.2 (``rock_terraces/``, made with another AI from the
briefs "Kanto Terraces v0.1" and "v0.2"; its README), an addition to the rock and cliff pack (``rock_cliff/``,
cliffs.py): the same palette, nine-phase top and two-block wall, with
  * a face for each level above the first: level 2 a one-block step, levels 3-5 a two-block face (the pack's "taller
    mountains" profile); each brings its own lit rim, so the top above it has no south edge;
  * side walls: where a level ends east or west, the 8 px half of its top on that side is a wall of rock, lit on the
    west and shaded on the east (the other half the top's own phase); its back and front ends turn the rim; along a
    wall its two variants take turns by the map's row (``W_wall`` on even rows, ``W_wall_2`` on odd ones, as the pack
    lays them), so a long wall doesn't stripe;
  * ends: a face's ends are outer (beside what's lower) or inner (beside more of its level's top). A tier's outer end
    is square and turns into its side wall (v0.2, after the owner found the tiers' rounded ends made them "look
    separate"); level 1's outer ends meet the side wall above them and stay rounded at their foot, on the lawn;
  * junctions: a top beside a face of its own level, or with a face's first row below its inside corner.

Each level is laid out as a cliff of its own (``layer``: the blocks at that level or higher; the bottom one or two
blocks of each column are its face, the rest its top) and drawn over the level below, as the pack's previews are: so a
block is the piece of its own level over the piece of the level below, the metatile's two layers (its ``ground``). The
map's edges count as more of the same level.

The rules are the pack's (its source/previews.py ``render``), kept here block for block: ``check_against`` compares a
layout with the pack's own record of its previews. ``compose`` returns the sheet's pieces and the grid's characters.
"""
import json
import zlib
from pathlib import Path

import numpy as np
from PIL import Image

import cliffs

PACK = Path(__file__).resolve().parent / "rock_terraces"
FIRST = 0x3400  # the grid's characters for the composed pieces (CJK Extension A: no other legend uses them)
HEIGHTS = {1: 2, 2: 1, 3: 2, 4: 2, 5: 2}  # each level's face, in blocks (the pack's height_profiles.json default)
TALL = {3, 4, 5}  # the levels whose two-block face is the pack's tall_step (level 1's is the rock pack's wall)
WALL_VARIANTS = True  # the side walls' two variants take turns by row (False: the first only, a few tiles fewer)
_DIRS = {"N": (0, -1), "E": (1, 0), "S": (0, 1), "W": (-1, 0), "NE": (1, -1), "SE": (1, 1), "SW": (-1, 1),
         "NW": (-1, -1)}
_BITS = {"N": 1, "E": 2, "S": 4, "W": 8, "NE": 16, "SE": 32, "SW": 64, "NW": 128}


def _piece(rel: str) -> np.ndarray:
    with Image.open(PACK / rel) as im:
        assert im.mode == "P" and im.getpalette()[:48] == cliffs._flat, f"{rel}: not in the rock pack's palette"
        return np.array(im)


_RECIPES = json.loads((PACK / "terraces_recipes.json").read_text())["pieces"]
ALL = {n: _piece(p["image"].removeprefix("terraces/")) for n, p in _RECIPES.items()}  # (the pack's own
# folder is this one)


def _base_column(name: str) -> np.ndarray:
    return cliffs.pack(f"face/{name}.png")


def _base_junction(phase: int, name: str) -> np.ndarray:
    return cliffs.join(cliffs.quads(cliffs._junctions[str(phase)][name]["tiles_8x8"]))


def levels(g) -> list[list[int]]:
    """The plan's levels: ``1``-``9`` as they are, ``C`` 1, everything else 0."""
    return [[int(c) if c.isdigit() else 1 if c == "C" else 0 for c in row] for row in g]


def from_rects(g, rects: dict) -> None:
    """``C`` in the plan as levels from rectangles: {level: [(x0, y0, x1, y1), ...]} (inclusive); a block of the
    cliff takes the highest level whose rectangle holds it, the rest of the cliff level 1. Blocks that aren't cliff
    stay as they are."""
    for y, row in enumerate(g):
        for x, c in enumerate(row):
            if c == "C":
                lv = max([L for L, rs in rects.items() for x0, y0, x1, y1 in rs
                          if x0 <= x <= x1 and y0 <= y <= y1] + [1])
                g[y][x] = str(lv)


def from_text(g, text: str) -> None:
    """Levels from a plan of the same size where the cliff's blocks are digits (the pack's
    route3_levels_proposed.txt, say): every block that is cliff in ``g`` takes its level from ``text``."""
    rows = text.split("\n")
    for y, row in enumerate(g):
        for x, c in enumerate(row):
            if c == "C" or c.isdigit():
                v = rows[y][x]
                assert v.isdigit() and v != "0", f"({x},{y}): the plan's cliff isn't cliff in the levels"
                g[y][x] = v
            else:
                assert not rows[y][x].isdigit(), f"({x},{y}): the levels put cliff where the plan has ground"


def layer(lv, L: int, edge_continues: bool = True) -> dict:
    """Level ``L`` laid out: (x, y) -> (kind, picture 16x16, names, part) for every block at ``L`` or higher, where
    kind is "top" or "face" and part a face block's row from its top (0 or 1). As the pack's render does."""
    h, w = len(lv), len(lv[0])
    cells = {(x, y) for y in range(h) for x in range(w) if lv[y][x] >= L}
    tall = L in TALL

    def has(x, y):
        if (x, y) in cells:
            return True
        if edge_continues and not (0 <= x < w and 0 <= y < h):
            return (max(0, min(w - 1, x)), max(0, min(h - 1, y))) in cells
        return False
    faces, tops = {}, set(cells)
    for x, y in sorted(cells):
        if not has(x, y + 1):
            height = HEIGHTS[L]
            for j in range(height):
                yy = y - height + 1 + j
                if (x, yy) in cells:
                    faces[x, yy] = j
                    tops.discard((x, yy))
    out = {}
    for x, y in sorted(tops):
        ph = cliffs.phase(x, y)
        mask = 0
        for d, (dx, dy) in _DIRS.items():
            outside = not has(x + dx, y + dy)
            if d == "S" and L == 1 and (x, y + 1) in faces:  # only level 1's wall leaves the top its south edge
                outside = True
            if outside:
                mask |= _BITS[d]
        a = cliffs.join(cliffs.quads(cliffs._recipes[ph, mask]))
        names = [f"top{ph}#{mask}"]
        for side, dx in (("W", -1), ("E", 1)):
            xx = 0 if side == "W" else 8
            if (x + dx, y) in faces:  # a face of this level beside it
                if L == 1:
                    n = f"side_{side}_face" + ("_start" if faces[x + dx, y] == 0 else "")
                    a[:, xx:xx + 8] = _base_junction(ph, n)[:, xx:xx + 8]
                else:
                    n = f"side_{side}_step"
                    a[:, xx:xx + 8] = ALL[n][:, xx:xx + 8]
                names.append(n)
            elif not has(x + dx, y):  # the level ends here: its side wall
                prefix = "N" if not has(x, y - 1) else "S" if (x, y + 1) in faces else ""
                n = prefix + side + "_wall" + ("_2" if WALL_VARIANTS and not prefix and y % 2 else "")  # turns by row
                a[:, xx:xx + 8] = ALL[n][:, xx:xx + 8]
                names.append(n)
            elif (x, y + 1) not in faces and (x + dx, y + 1) in faces and faces[x + dx, y + 1] == 0:
                n = f"in_S{side}_step" if L > 1 else f"in_S{side}_face"  # a face's first row below its corner
                src = ALL[n] if L > 1 else _base_junction(ph, n)
                a[8:, xx:xx + 8] = src[8:, xx:xx + 8]
                names.append(n)
        out[x, y] = ("top", a, names, None)
    for (x, y), part in sorted(faces.items()):
        topy = y - part
        variant = (0, 1, 2, 0, 1, 2, 1, 0, 2)[(x + 2 * L + topy) % 9] if tall else (x // 3 + topy + L) % 2
        mid = "middle_" + str(1 + (x % 2 if L == 1 else variant))
        full = _base_column(mid) if L == 1 else ALL[("tall_" if tall else "") + mid]
        a = full[part * 16:part * 16 + 16].copy()
        names = [("wall_" if L == 1 else "tall_" if tall else "step_") + mid + f".{part}"]
        for side, dx in (("W", -1), ("E", 1)):
            xx = 0 if side == "W" else 8
            if (x + dx, topy) in faces or (not (0 <= x + dx < w) and edge_continues):
                continue
            kind = "inner" if has(x + dx, topy) else "outer"
            if L == 1:
                if kind == "outer":
                    n, donor = f"outer_{side}_wall_side", ALL[f"outer_{side}_wall_side"]
                else:
                    n, donor = f"inner_{side}", _base_column(f"inner_{side}")
            else:
                if tall:
                    n = f"tall_{kind}_{side}"
                else:
                    n = f"outer_{side}_step_wall" if kind == "outer" else f"inner_{side}"
                donor = ALL[n]
            a[:, xx:xx + 8] = donor[part * 16:part * 16 + 16, xx:xx + 8]
            names.append(n)
        out[x, y] = ("face", a, names, part)
    return out


def compose(g, ground: str = "grass", extra=("top1#0",), edge_continues: bool = True, base: dict | None = None):
    """The plan's levels as pieces: every block of a cliff gets the piece of its own level over the piece of the level
    below (its ground; level 1's is ``ground``). Returns (cells, chars, names): ``cells`` the sheet's entries in order,
    (name, picture, entry), each one's ground before it; ``chars`` the grid's character for each block of a cliff;
    ``names`` piece name -> character. ``extra``: pieces the map uses elsewhere (its border: the plain top, phase 1).
    ``base``: for a map whose level 1 is laid by the rock pack's own cliffs.layout
    (``tiers_over``), the piece it has at each block of a higher level, (x, y) -> (name, picture): those are the
    tiers' grounds, and only the blocks above level 1 get pieces and characters here."""
    lv = levels(g)
    top = max(max(r) for r in lv)
    per = [layer(lv, L, edge_continues) for L in range(1, top + 1)]
    cells, made = [], {}
    for name in (() if base is not None else extra):
        ph, mask = int(name[3:name.index("#")]), int(name.split("#")[1])
        made[name] = True
        cells.append((name, cliffs.join(cliffs.quads(cliffs._recipes[ph, mask])), {"ground": ground}))

    def mark(pic):
        return f"~{zlib.crc32(pic.tobytes()) & 0xffff:04x}"

    def flat(L, x, y):
        """Levels 1-L at (x, y) drawn into one picture (0 where none shows: the ground)."""
        out = np.zeros((16, 16), np.uint8)
        for k in range(L):
            pic = per[k][x, y][1]
            out[pic > 0] = pic[pic > 0]
        return out

    def shows(name, qy, qx):
        """What a piece shows as a ground in one quarter, as pae builds it: its own art where that covers the whole
        quarter, else its own ground's (0: the kit's grass). A tile has one palette, so rock can't share a quarter
        with the grass in one layer."""
        if name not in pictures:
            return np.zeros((8, 8), np.uint8)
        pic, gr = pictures[name]
        q = pic[qy * 8:qy * 8 + 8, qx * 8:qx * 8 + 8]
        return q if (q > 0).all() else shows(gr, qy, qx)
    pictures = {n: (pic, e["ground"]) for n, pic, e in cells}

    def entry_of(L, x, y):
        if L == 1 and base is not None:  # the map's own level 1, already on its sheet
            name, pic = base[x, y]
            assert np.array_equal(pic, per[0][x, y][1]), f"({x},{y}): the map's cliff top isn't the layout's"
            pictures.setdefault(name, (pic, ground))
            return name
        kind, pic, names, part = per[L - 1][x, y]
        name, gr = "+".join(names) + mark(pic), ground  # the names, and the picture's mark
        if L > 1:
            gr = entry_of(L - 1, x, y)
            below = flat(L - 1, x, y)
            def quarter(a, qy, qx):
                return a[qy * 8:qy * 8 + 8, qx * 8:qx * 8 + 8]
            if all(np.array_equal(np.where(quarter(pic, qy, qx) > 0, 0, shows(gr, qy, qx)),
                                  np.where(quarter(pic, qy, qx) > 0, 0, quarter(below, qy, qx)))
                   for qy in (0, 1) for qx in (0, 1)):
                name = f"{name}@{gr}"
            else:
                # more levels show through one quarter than the metatile's two layers can hold (the grass under
                # one, the rock of two levels over it): the block's levels drawn into one piece over the grass
                pic = flat(L, x, y)
                name, gr = "flat" + mark(pic), ground
        if name not in made:
            made[name] = True
            cells.append((name, pic, {"ground": gr}))
            pictures[name] = (pic, gr)
        return name
    chars, names = {}, {}
    for y, row in enumerate(lv):
        for x, v in enumerate(row):
            if v > (1 if base is not None else 0):
                n = entry_of(v, x, y)
                if n not in names:
                    names[n] = chr(FIRST + len(names))
                chars[x, y] = names[n]
    return cells, chars, names


def check_against(lv, records, edge_continues: bool = True) -> list:
    """Where this layout differs from the pack's own (its layout.json placements of one scene, rebuilt from its
    atlas): [(level, (x, y), what)]."""
    with Image.open(PACK / "tileset_8x8.png") as im:
        atlas = np.array(im)
    tiles = [atlas[8 * (i // 16):8 * (i // 16) + 8, 8 * (i % 16):8 * (i % 16) + 8] for i in range(
        atlas.shape[0] // 8 * 16)]
    bad = []
    top = max(max(r) for r in lv)
    per = {L: layer(lv, L, edge_continues) for L in range(1, top + 1)}
    for r in records:
        x, y = r["block"]
        want = np.zeros((16, 16), np.uint8)
        for qy in (0, 1):
            for qx in (0, 1):
                t = tiles[r["tiles_8x8"][qy][qx]]
                f = r["flips_8x8"][qy][qx]
                t = t[:, ::-1] if f["h"] else t
                t = t[::-1] if f["v"] else t
                want[qy * 8:qy * 8 + 8, qx * 8:qx * 8 + 8] = t
        got = per[r["level"]].get((x, y))
        if got is None:
            bad.append((r["level"], (x, y), "missing"))
        elif not np.array_equal(got[1], want):
            bad.append((r["level"], (x, y), f"{got[2]} vs {r['pieces']}"))
    return bad


def plan_tiers(foot, h: int, w: int, top: int = 5, beyond=lambda x, y: False) -> list[list[int]]:
    """Tiers for a cliff's footprint (the blocks of level 1: a set of (x, y)), by Route 3's rules (the owner's
    feedback on it): each level above stands on the one below, set back two blocks from its sides and its back and,
    in front, far enough that one row of the lower level's top shows above that level's face; no tier is narrower
    than three blocks, or shorter than its face and a row of top. Where a cliff is too shallow for that (a band a few
    blocks deep), its step stands straight on its wall instead, the step's ends still set back two blocks: a taller
    wall that steps down at its ends. ``beyond(x, y)``: whether a block past the map's edge counts as cliff (where
    the cliff's top runs on to the edge and no map joins there); the tiers stay inside the map. Returns the levels,
    block by block (0 where no cliff)."""
    lv = [[1 if (x, y) in foot else 0 for x in range(w)] for y in range(h)]

    def tier(cur, L, front):
        def has(x, y):
            return (x, y) in cur if 0 <= x < w and 0 <= y < h else beyond(x, y)
        below = HEIGHTS[L - 1] + front  # the lower level's face, and the rows of its top that show
        er = {(x, y) for x, y in cur
              if all(has(x + dx, y + dy) for dx in range(-2, 3) for dy in range(-2, below + 1))}
        tall = HEIGHTS[L] + 1  # this level's face and a row of its top
        new = set()
        for x, y in er:  # an opening: every 3 x tall box that fits
            if all((x + dx, y + dy) in er for dx in range(3) for dy in range(tall)):
                new |= {(x + dx, y + dy) for dx in range(3) for dy in range(tall)}
        return new
    # each cliff on its own (its blocks joined side by side): set back where it's deep enough, else straight up
    left, parts = set(foot), []
    while left:
        part, todo = set(), [left.pop()]
        while todo:
            x, y = todo.pop()
            part.add((x, y))
            for n in ((x + 1, y), (x - 1, y), (x, y + 1), (x, y - 1)):
                if n in left:
                    left.discard(n)
                    todo.append(n)
        parts.append(part)
    for part in parts:
        cur = part
        for L in range(2, top + 1):
            new = tier(cur, L, 1) or (tier(cur, L, 0) if L == 2 else set())
            if not new:
                break
            for x, y in new:
                lv[y][x] = L
            cur = new
    return lv


def beyond_edges(w: int, h: int, up=(), down=()):
    """For ``plan_tiers``: past the map's top and bottom edges counts as cliff (the map's own top runs on to them)
    except where a map joins there (``up``, ``down``: the columns it covers); past its sides never."""
    up, down = set(up), set(down)

    def beyond(x, y):
        if not 0 <= x < w:
            return False
        return x not in up if y < 0 else x not in down if y >= h else False
    return beyond


def footprint(g, roof: str = "") -> set:
    """The cliff's footprint in a plan: its ``C`` blocks (before cliffs.layout), and its ``roof`` blocks (a cave's
    mouth the top runs down to, in place of a wall: cliffs.layout's)."""
    return {(x, y) for y, row in enumerate(g) for x, c in enumerate(row) if c == "C" or c in roof}


def tiers_over(g, foot, roof: str = "", top: int = 5, beyond=lambda x, y: False):
    """Tiers over a map whose cliffs are laid by the rock pack's cliffs.layout and cliffs.add (its level 1: the wall,
    the tops, the caves' mouths and stairs, all as they were): the levels above it, by ``plan_tiers`` from the
    cliff's footprint ``foot`` (the plan's ``C`` blocks before the layout). Puts each tier block's character into
    ``g`` and returns (cells, names, levels): ``beyond`` as ``plan_tiers``; the sheet's pieces for the tiers (each
    over the map's own top there, its ground), piece name -> character, and the levels. Every tier stands on a plain
    top of the map's (its sides all cliff top), so the map's level 1 is the layout's own there, which ``compose``
    checks pixel for pixel."""
    h, w = len(g), len(g[0])
    lv = plan_tiers(foot, h, w, top, beyond)
    # the tops' edges as pae paints them: the tops beside a face (cliffs.add's characters) count as top too
    tops = cliffs.tops_in(g, roof + cliffs.JUNCTION_CHARS)
    base = {}
    for y in range(h):
        for x in range(w):
            if lv[y][x] > 1:
                assert (x, y) in tops, f"({x},{y}): a tier over something that isn't the cliff's top"
                k, mask, corners = tops[x, y]
                base[x, y] = (cliffs.top_name(k, mask, corners), cliffs.top(k, cliffs.outside_of(mask, corners)))
    grid = [[str(v) if v else "." for v in row] for row in lv]
    # (a tier at the map's top or bottom edge runs on past it, as the map's own top does: no rim along the edge)
    cells, chars, names = compose(grid, edge_continues=True, base=base)
    apply(g, chars)
    return cells, names, lv


def apply(g, chars) -> None:
    """The composed pieces' characters into the grid."""
    for (x, y), c in chars.items():
        g[y][x] = c


def legend(names: dict, joins: str | None = None) -> dict:
    """The legend for the composed pieces: one character each. ``joins``: what the pieces count as for their
    neighbours' edges (``C`` for tiers over the rock pack's cliff, so the tops round them stay plain)."""
    return {c: {"name": n, **({"joins": joins} if joins else {})} for n, c in names.items()}


def solid(names: dict) -> set:
    return set(names.values())


def flatten(g, edge_continues: bool = True) -> np.ndarray:
    """Every level of the plan's cliffs drawn over the one below in full (as the pack's previews are), as palette
    indices (0 where no cliff shows): what the two-layer metatiles should show."""
    lv = levels(g)
    h, w = len(lv), len(lv[0])
    out = np.zeros((h * 16, w * 16), np.uint8)
    for L in range(1, max(max(r) for r in lv) + 1):
        for (x, y), (_k, pic, _n, _p) in layer(lv, L, edge_continues).items():
            m = pic > 0
            out[y * 16:y * 16 + 16, x * 16:x * 16 + 16][m] = pic[m]
    return out


def two_layers(cells, names, g) -> np.ndarray:
    """The grid's cliffs as the game draws them: each block's piece over its ground (per 8x8 quarter, the ground's
    own piece where that covers the quarter, else its ground's, as pae does), as palette indices (0: the kit's
    grass)."""
    by = {n: (pic, e.get("ground")) for n, pic, e in cells}
    rev = {c: n for n, c in names.items()}
    h, w = len(g), len(g[0])
    out = np.zeros((h * 16, w * 16), np.uint8)

    def under(n, qy, qx):  # what a piece gives as a ground in one quarter (as compose's shows)
        if n not in by:
            return np.zeros((8, 8), np.uint8)
        pic, gr = by[n]
        q = pic[qy * 8:qy * 8 + 8, qx * 8:qx * 8 + 8]
        return q if (q > 0).all() else under(gr, qy, qx)
    for y in range(h):
        for x in range(w):
            n = rev.get(g[y][x])
            if n is None:
                continue
            pic, gr = by[n]
            for qy in (0, 1):
                for qx in (0, 1):
                    q = pic[qy * 8:qy * 8 + 8, qx * 8:qx * 8 + 8]
                    base = under(gr, qy, qx)
                    out[y * 16 + qy * 8:y * 16 + qy * 8 + 8, x * 16 + qx * 8:x * 16 + qx * 8 + 8] = \
                        np.where(q > 0, q, base)
    return out
