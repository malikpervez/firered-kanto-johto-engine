"""Terraces: cliffs in levels, so a mountain steps up in tiers set back one behind the other, as FireRed's do (the
owner, 4 November 2026: "some cliffs should be stacked but offset so it looks like a progressive hill").

A plan marks a cliff's blocks with its level, ``1`` to ``3`` (``C``, the plain cliff, is level 1); everything else is
the ground, level 0. Each level is laid out as a cliff of its own: the bottom blocks of each column of it are its face,
the rest its top, the top's edges where the level below shows round it. Level 1 has the rock and cliff pack's
two-block wall, as every cliff had before; the levels above it a one-block step, as FireRed's tiers have (a lit rim,
then the face, standing on the level below). Each block is the piece of its own level drawn over the piece of the
level below (the metatile's two layers: its ``ground``), so a step stands on the top in front of it and a top's edge
shows the level beyond it.

Until the terraces pack (its brief: Drive, "Kanto Terraces v0.1 brief") brings them, two of the pieces are
stand-ins made from the rock and cliff pack's own: the step (its wall's lit edge and darker rock in one block, under
the top's rim) and the side walls (half a block of its face's rock along a tier's east end, in shadow, and its west
end, in the light). ``STAND_INS`` names them.

What the levels must keep to (``problems`` says where a plan breaks them; ``tidy`` lowers what does):
  * a level stands inside the one below it, never on that level's face: its foot at least the lower face's height
    above that level's foot in every column (then as many blocks of the lower level's top as you like, its shelf);
  * a face is as tall as its level's (two blocks for level 1, one above) and two columns wide at least, and faces side
    by side line up (or are a face's height or more apart, where a top steps round them).

``auto`` turns a plan's ``C`` into levels by how far each block is from the cliff's edge; ``from_rects`` from
rectangles, for a map drawn by hand. ``compose`` lays the levels out and returns the sheet's pieces and the grid's
characters.
"""
import random
import re
from math import ceil

import numpy as np

import cliffs

FIRST = 0x3400  # the grid's characters for the composed pieces (CJK Extension A: no other legend uses them)
WALL, STEP = 2, 1  # the faces' heights: level 1's wall, the step of each level above it
STAND_INS = ("step_*", "*+sideE", "*+sideW")  # pieces made here from the rock and cliff pack until its terraces pack


def levels(g) -> list[list[int]]:
    """The plan's levels: ``1``-``9`` as they are, ``C`` 1, everything else 0."""
    return [[int(c) if c.isdigit() else 1 if c == "C" else 0 for c in row] for row in g]


def height(L: int) -> int:
    return WALL if L == 1 else STEP


def auto(g, south: int = 2, side: int = 2, north: int = 2, top: int = 3, shift=None) -> None:
    """``C`` in the plan as levels by how far each block is from the cliff's foot (a tier every ``south`` blocks in
    from level 1's wall), its east and west ends (``side``) and its back (``north``), up to ``top``; ``shift(x)``
    moves the tiers' feet north (+) or south (-) in column ``x``. Then ``tidy``."""
    h, w = len(g), len(g[0])
    mass = [[c == "C" for c in row] for row in g]

    def run(x, y, dx, dy):  # blocks of cliff from (x, y) to its edge that way, the map's edges counting as cliff
        n = 0
        while 0 <= x < w and 0 <= y < h and mass[y][x]:
            n, x, y = n + 1, x + dx, y + dy
        return n if (0 <= x < w and 0 <= y < h) else 10 ** 6
    for y in range(h):
        for x in range(w):
            if not mass[y][x]:
                continue
            ds = run(x, y, 0, 1)
            if ds < 10 ** 6:
                ds = max(1, ds - WALL + (shift(x) if shift else 0))  # level 1's wall, then a tier every ``south``
            lv = min(1 + (ds - 1) // south if ds < 10 ** 6 else top, ceil(run(x, y, 1, 0) / side),
                     ceil(run(x, y, -1, 0) / side), ceil(run(x, y, 0, -1) / north), top)
            g[y][x] = str(max(1, lv))
    tidy(g)


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


def _layer(lv, L):
    """Level ``L`` as a cliff of its own: the blocks at ``L`` or higher."""
    return [["C" if v >= L else "." for v in row] for row in lv]


def layout(G, h: int) -> set:
    """``cliffs.layout`` for faces ``h`` blocks tall: ``C`` (a level's footprint) as its tops and faces, in place.
    Returns the faces' blocks."""
    H, W = len(G), len(G[0])
    face = {}  # (x, y of its upper block) -> column
    for x in range(W):
        y = 0
        while y < H:
            if G[y][x] != "C":
                y += 1
                continue
            y1 = y
            while y1 + 1 < H and G[y1 + 1][x] == "C":
                y1 += 1
            if y1 + 1 < H:
                assert y1 - y + 1 >= h, f"({x},{y}): a cliff needs {h} blocks for its face"
                face[x, y1 - h + 1] = None
            y = y1 + 1

    def end(x, y):  # what's beside a face: None (more face), "inner" or "outer"
        if (x, y) in face:
            return None
        for d in range(1, h):
            assert (x, y + d) not in face and (x, y - d) not in face, f"({x},{y}): faces beside each other must line up"
        return "inner" if 0 <= x < W and G[y][x] == "C" and (x, y) not in face else "outer"
    for x, y in sorted(face, key=lambda c: (c[1], c[0])):  # west to east, the middles mixed (never one twice)
        west, east = end(x - 1, y), end(x + 1, y)
        assert not (west and east), f"({x},{y}): a face needs two columns at least"
        if west or east:
            face[x, y] = next(c for c, n in cliffs.FACE.items() if n == (f"{west}_W" if west else f"{east}_E"))
        else:
            options = [c for c in cliffs.MIDDLES if c != face.get((x - 1, y))]
            face[x, y] = options[random.Random(x * 1000 + y).randrange(len(options))]
    for y in range(H):
        for x in range(W):
            if G[y][x] == "C":
                G[y][x] = cliffs.TOP[cliffs.phase(x, y) - 1]
    blocks = set()
    for (x, y), c in face.items():
        for d in range(h):
            G[y + d][x] = c
            blocks.add((x, y + d))
    return blocks


_AT = re.compile(r"\((\d+),(\d+)\)")


def problems(g) -> list[tuple[int, int, int, str]]:
    """Where the plan's levels break the rules above: (x, y, level, why)."""
    lv = levels(g)
    out, below = [], None
    for L in range(1, max(max(r) for r in lv) + 1):
        G = _layer(lv, L)
        try:
            faces = layout(G, height(L))
            cliffs.junctions(G, cliffs.tops_in(G))
        except AssertionError as e:
            m = _AT.search(str(e))
            x, y = (int(m.group(1)), int(m.group(2))) if m else (0, 0)
            out.append((x, y, L, str(e)))
            break
        if below is not None:
            out += [(x, y, L, f"({x},{y}): level {L} stands on level {L - 1}'s face")
                    for y, row in enumerate(lv) for x, v in enumerate(row) if v >= L and (x, y) in below]
        below = faces
    return out


def tidy(g, rounds: int = 400) -> None:
    """Lower the blocks of a level that break the rules (``problems``) to the level below, with the rest of that
    level's run in the block's column, until none is left."""
    for _ in range(rounds):
        found = problems(g)
        if not found:
            return
        x, y, L, why = found[0]
        assert L > 1, f"the plan's cliff itself: {why}"
        lv = levels(g)
        ys = [y]
        for d in (-1, 1):
            yy = y + d
            while 0 <= yy < len(g) and lv[yy][x] >= L:
                ys.append(yy)
                yy += d
        for yy in ys:
            g[yy][x] = str(L - 1)
    raise AssertionError(f"levels still break the rules after {rounds} rounds: {problems(g)[:3]}")


def step(col: str, k: int) -> np.ndarray:
    """A one-block step (stand-in): the top's lit rim (phase ``k``; rounded at an outer end), the wall's lit edge,
    a band of its darker rock and its foot."""
    face = cliffs.pack(f"face/{col}.png")
    outside = 4 | (2 if col == "outer_E" else 0) | (8 if col == "outer_W" else 0)
    rim = cliffs.top(k, outside)[-3:]
    return np.vstack([rim, face[:2], face[17:31]])[:16]


_ROCK = cliffs.pack("face/middle_2.png")
SHADE = {1: 1, 2: 1, 3: 2, 4: 3, 5: 4, 6: 5, 7: 6, 8: 7, 9: 2, 10: 9, 11: 10, 12: 11, 13: 12, 14: 9, 15: 14}


def side(pic: np.ndarray, east: bool) -> np.ndarray:
    """A top with a side wall (stand-in) half a block wide: along its east end the wall's rock a shade darker (in
    shadow), along its west end the rock as it is (in the light); the top's lit rim along its inner edge, an outline
    at the outer."""
    out = pic.copy()
    for y in range(16):
        for i in range(7):
            x = 9 + i if east else 6 - i
            v = int(_ROCK[12 + (y % 16), 4 + i])
            if v:
                out[y, x] = SHADE[v] if east else v
        out[y, 8 if east else 7] = 8
        out[y, 15 if east else 0] = 1 if east else 2
    return out


def _pieces(G, h: int):
    """Level grid ``G`` (laid out) as its blocks' pieces: (x, y) -> (name, picture, part) where part is None for a
    1x1 piece, 0 or 1 for a wall's upper or lower block."""
    tops = cliffs.tops_in(G)
    beside = cliffs.junctions(G, tops)
    out = {}
    H, W = len(G), len(G[0])

    def cliff(x, y):  # part of this level (the map's edges count as more of it)
        return not (0 <= x < W and 0 <= y < H) or G[y][x] in cliffs.TOP or (x, y) in beside
    for y in range(H):
        for x in range(W):
            c = G[y][x]
            if c in cliffs.FACE:
                col = cliffs.FACE[c]
                if h == 1:
                    k = cliffs.phase(x, y)
                    out[x, y] = (f"step_{col}~{k}", step(col, k), None)
                else:
                    upper = not (y > 0 and G[y - 1][x] == c and (y < 2 or G[y - 2][x] != c))
                    out[x, y] = (f"face_{col}", cliffs.pack(f"face/{col}.png"), 0 if upper else 1)
            elif (x, y) in beside:
                name, pic = beside[x, y]
                out[x, y] = (name, pic, None)
            elif (x, y) in tops:
                k, mask, corners = tops[x, y]
                name, pic = cliffs.top_name(k, mask, corners), cliffs.top(k, cliffs.outside_of(mask, corners))
                for east, dx in ((True, 1), (False, -1)):
                    if not cliff(x + dx, y) and G[y][x + dx] not in cliffs.FACE:
                        name, pic = name + ("+sideE" if east else "+sideW"), side(pic, east)
                out[x, y] = (name, pic, None)
    return out


def compose(g, faces: dict | None = None, ground: str = "grass", extra=("top1#15",)):
    """The plan's levels as pieces: every block of a cliff gets the piece of its own level over the piece of the
    level below. ``faces``: {(x, y): face character} set on level 1 after its layout (a wall that runs on over a
    join). Returns (cells, chars, names): ``cells`` the sheet's entries in order, (name, picture, entry), each one's
    ground before it; ``chars`` the grid's character for each block of a cliff; ``names`` piece name -> character.
    ``extra``: pieces the map uses elsewhere (its border)."""
    lv = levels(g)
    top = max(max(r) for r in lv)
    per = []
    for L in range(1, top + 1):
        G = _layer(lv, L)
        layout(G, height(L))
        if L == 1 and faces:
            for (x, y), c in faces.items():
                G[y][x] = c
        per.append(_pieces(G, height(L)))
    cells, made = [], {}
    for name in extra:  # the border's top, before anything else stands on it
        k = int(name[3:name.index("#")])
        made[name] = True
        cells.append((name, cliffs.top(k, cliffs.outside_of(int(name.split("#")[1]), 0)), {"ground": ground}))

    def entry_of(L, x, y):
        """The name of block (x, y)'s piece at level L, as a 1x1 metatile (made if it isn't yet)."""
        name, pic, part = per[L - 1][x, y]
        assert part is None, f"({x},{y}): level {L + 1} stands on level {L}'s face"
        base = name if L == 1 else f"{name}@{entry_of(L - 1, x, y)}"
        if base not in made:
            made[base] = True
            cells.append((base, pic, {"ground": ground if L == 1 else entry_of(L - 1, x, y)}))
        return base
    chars, names = {}, {}
    order = sorted(((x, y) for y, r in enumerate(lv) for x, v in enumerate(r) if v),
                   key=lambda c: (lv[c[1]][c[0]], c[1], c[0]))
    for x, y in order:
        if (x, y) in chars:
            continue
        L = lv[y][x]
        name, pic, part = per[L - 1][x, y]
        if part is None:
            n = entry_of(L, x, y)
            blocks = [(x, y)]
        else:
            assert part == 0 and L == 1, f"({x},{y}): a wall's lower block before its upper one"
            n = name
            if n not in made:
                made[n] = True
                cells.append((n, pic, {"ground": ground}))
            blocks = [(x, y), (x, y + 1)]
        if n not in names:
            names[n] = chr(FIRST + len(names))
        for b in blocks:
            chars[b] = names[n]
    return cells, chars, names


def apply(g, chars) -> None:
    """The composed pieces' characters into the grid."""
    for (x, y), c in chars.items():
        g[y][x] = c


def legend(names: dict) -> dict:
    """The legend for the composed pieces: one character each."""
    return {c: {"name": n} for n, c in names.items()}


def solid(names: dict) -> set:
    return set(names.values())


def preview(cells, names: dict, g, back=(112, 200, 120)) -> np.ndarray:
    """The grid's cliffs as an RGB picture (each block its ground under its piece, everything else ``back``), to
    look at a plan before building it."""
    pal = np.array(cliffs.PAL, np.uint8)
    by = {n: (pic, e.get("ground")) for n, pic, e in cells}
    rev = {c: n for n, c in names.items()}
    H, W = len(g), len(g[0])
    out = np.zeros((H * 16, W * 16, 3), np.uint8)
    out[:] = back

    def draw(n, x, y, part):
        pic, gr = by[n]
        if isinstance(gr, list):
            gr = gr[part]
        if gr in by:
            draw(gr, x, y, 0)
        cell = pic[part * 16:part * 16 + 16]
        m = cell > 0
        out[y * 16:y * 16 + 16, x * 16:x * 16 + 16][m] = pal[cell[m]]
    for y in range(H):
        for x in range(W):
            n = rev.get(g[y][x])
            if n is not None:
                part = int(by[n][0].shape[0] == 32 and y > 0 and g[y - 1][x] == g[y][x]
                           and (y < 2 or g[y - 2][x] != g[y][x]))
                draw(n, x, y, part)
    return out
