"""The rock and cliff pack (rock_cliff/, made with another AI from a brief, its README.md): cliffs for every map
that has them. The kit has no palette slot left, so each map gives the pack a bank of its own secondary tileset
(``PAL``).

In a plan, ``C`` is a cliff's whole footprint. ``layout`` turns it into tops and faces: the bottom two blocks of
each column of it are the face (the pack's columns: an outer end beside the lawn, an inner one where it meets a cliff
top or the stairs coming further south, the three middles mixed between), the rest is the top. The top's texture
repeats every three blocks from the map's corner (its nine phases), each with its edges where the lawn is around it
(the pack's recipes by its neighbours). ``add`` puts the pieces the map uses on a sheet and ``legend`` names them for
pae map paint.

A map can have blocks that count as cliff top without being drawn as one (``roof``: Route 22's League gate's roof,
which stands against the cliff) and stairs up a face (``stairs``: the pack's, a face's inner end).
"""
import json
import random
from pathlib import Path

import numpy as np
from PIL import Image

ROCK = Path(__file__).resolve().parent / "rock_cliff"
TOP = "ADEFGIJKV"  # the cliff's top, by its phase (1-9)
FACE = {"[": "outer_W", "{": "inner_W", "M": "middle_1", "N": "middle_2", "P": "middle_3", "}": "inner_E",
        "]": "outer_E"}  # the face's columns (two blocks tall)
MIDDLES = "MNP"
JUNCTION_CHARS = "aefijmtuxyz<>?;^|"  # tops beside a face, one character for each piece
SOLID = set(TOP + "".join(FACE) + JUNCTION_CHARS)  # every cliff block is solid


def phase(x: int, y: int) -> int:
    """The cliff top's phase at block (x, y): its texture repeats every three blocks from the map's corner."""
    return 1 + 3 * (y % 3) + x % 3


def layout(g, roof: str = "", stairs: str = "") -> None:
    """``C`` (a cliff's footprint) as its top and its face: the bottom two blocks of each column of it are the face,
    the rest the top (none over a ``roof`` block: it stands against the top). A face's ends are outer beside the
    lawn, inner beside a top, a roof or the ``stairs``."""
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
            if y1 + 1 < h and g[y1 + 1][x] not in roof:
                assert y1 > y, f"({x},{y}): a cliff needs two blocks for its face"
                face[x, y1 - 1] = None
            y = y1 + 1

    def end(x: int, y: int) -> str | None:  # what's beside a face: None (more face), "inner" or "outer"
        if (x, y) in face:
            return None
        assert (x, y + 1) not in face and (x, y - 1) not in face, f"({x},{y}): faces beside each other must line up"
        return "inner" if 0 <= x < w and g[y][x] in "C" + roof + stairs and (x, y) not in face else "outer"
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


def pack(rel: str) -> np.ndarray:
    """A picture of the rock and cliff pack as its palette's indices (0 transparent)."""
    with Image.open(ROCK / rel) as im:
        assert im.mode == "P" and im.getpalette()[:48] == _flat, f"{rel}: not in the pack's palette"
        return np.array(im)


with Image.open(ROCK / "tileset_8x8.png") as _im:  # the pack's palette, in its PNGs
    _flat = _im.getpalette()[:48]
PAL = [tuple(_flat[i:i + 3]) for i in range(0, 48, 3)]
_atlas = pack("tileset_8x8.png")
_recipes = {(r["phase"], r["mask"]): r["tiles_8x8"]
            for r in json.loads((ROCK / "autotile_recipes.json").read_text())["recipes"]}
_junctions = json.loads((ROCK / "face_junctions.json").read_text())["phases"]


def tile(t: int) -> np.ndarray:
    return _atlas[8 * (t // 16):8 * (t // 16) + 8, 8 * (t % 16):8 * (t % 16) + 8]


def quads(tiles) -> list[list[np.ndarray]]:
    return [[tile(t) for t in row] for row in tiles]


def join(q) -> np.ndarray:
    return np.vstack([np.hstack(row) for row in q])


def outside_of(mask: int, corners: int) -> int:
    """pae's mask (the sides that are top) and inside corners as the pack's bits of what isn't top (1 N, 2 E, 4 S,
    8 W, 16 NE, 32 SE, 64 SW, 128 NW)."""
    return (15 & ~mask) | sum(16 << i for i in range(4) if corners & 1 << i)


def top(k: int, outside: int) -> np.ndarray:
    """The cliff top of phase ``k`` whose neighbours ``outside`` aren't cliff top, from its recipe: four tiles of
    the pack's atlas."""
    return join(quads(_recipes[k, outside]))


def top_name(k: int, mask: int, corners: int) -> str:
    return f"top{k}#{mask}" + (f".{corners}" if corners else "")


def tops_in(g, roof: str = "") -> dict[tuple[int, int], tuple[int, int, int]]:
    """The cliff tops of the grid, as pae paints them: block -> (phase, mask of the sides that are top, inside
    corners)."""
    h, w = len(g), len(g[0])

    def same(x, y):  # the map's edges count as the same, as in pae
        return not (0 <= x < w and 0 <= y < h) or g[y][x] in TOP + roof
    out = {}
    for y in range(h):
        for x in range(w):
            if g[y][x] in TOP:
                mask = sum(b for b, (dx, dy) in ((1, (0, -1)), (2, (1, 0)), (4, (0, 1)), (8, (-1, 0)))
                           if same(x + dx, y + dy))
                corners = sum(b for b, (dx, dy), sides in ((1, (1, -1), 3), (2, (1, 1), 6), (4, (-1, 1), 12),
                                                           (8, (-1, -1), 9))
                              if mask & sides == sides and not same(x + dx, y + dy))
                out[x, y] = (TOP.index(g[y][x]) + 1, mask, corners)
    return out


def junctions(g, tops) -> dict[tuple[int, int], tuple[str, np.ndarray]]:
    """The tops that meet a face (the pack's 3.2 pieces, not its lawn edges): beside a face's upper block its side
    starts (``side_W_face_start``), beside its lower block it runs on (``side_W_face``); a top whose inside corner
    is a face's upper block has the face's corner (``in_SW_face``). Where the top's own edge (lawn north or south of
    it) meets that side, the quarter keeps its lawn edge."""
    h, w = len(g), len(g[0])

    def face_at(x, y):  # None, "start" (a face's upper block) or "on" (its lower block)
        if not (0 <= x < w and 0 <= y < h) or g[y][x] not in FACE:
            return None
        return "on" if 0 < y and g[y - 1][x] == g[y][x] and (y < 2 or g[y - 2][x] != g[y][x]) else "start"
    out = {}
    for (x, y), (k, mask, corners) in tops.items():
        j = _junctions[str(k)]
        sides = {"W": face_at(x - 1, y), "E": face_at(x + 1, y)}
        assert not (sides["W"] and sides["E"]), f"({x},{y}): a cliff top between two faces"
        lawn = quads(_recipes[k, outside_of(mask, corners)])
        inner = dict(mask=mask | (8 if sides["W"] else 0) | (2 if sides["E"] else 0))
        q = quads(_recipes[k, outside_of(inner["mask"], 0)])
        tags = []
        for side, col, bit in (("W", 0, 8), ("E", 1, 2)):
            if sides[side]:
                piece = quads(j[f"side_{side}_face" + ("_start" if sides[side] == "start" else "")]["tiles_8x8"])
                for row, edge in ((0, 1), (1, 4)):  # the top's own north/south edge keeps its lawn quarter
                    q[row][col] = lawn[row][col] if not mask & edge else piece[row][col]
                tags.append(f"{side}{sides[side]}")
        for bit, (dx, dy), name, col in ((4, (-1, 1), "in_SW_face", 0), (2, (1, 1), "in_SE_face", 1)):
            if corners & bit and face_at(x + dx, y + dy) == "start":
                q[1][col] = quads(j[name]["tiles_8x8"])[1][col]
                tags.append(name)
        for bit, (dx, dy) in ((1, (1, -1)), (8, (-1, -1))):
            assert not (corners & bit and face_at(x + dx, y + dy)), f"({x},{y}): a face north of a top's corner"
        if tags:
            # the rest as pae would draw it (the inside corners that aren't the face's)
            for row in (0, 1):
                for col in (0, 1):
                    if not ((col == 0 and sides["W"]) or (col == 1 and sides["E"])) and \
                            not (row == 1 and f"in_S{'W' if col == 0 else 'E'}_face" in tags):
                        q[row][col] = lawn[row][col]
            out[x, y] = (f"{top_name(k, mask, corners)}+{'+'.join(tags)}", join(q))
    return out


EXTRAS = ("rock_stairs", "small_rock", "big_boulder")  # the pack's other pieces


def add(sheet, g, roof: str = "", extra_tops=(), extras=EXTRAS) -> dict[str, str]:
    """Put the pieces the grid's cliffs use on ``sheet`` (in the pack's palette): its tops (by phase, the sides that
    are top and the inside corners), the tops beside a face, the face's columns, then the pack's stairs and its two
    rocks. ``extra_tops`` are tops the map draws under something else ((phase, mask, corners)). The tops beside a
    face get a character each in the grid; returns them (piece name -> character) for ``legend``. ``extras``: which
    of the pack's other pieces the map uses (each costs tiles)."""
    tops = tops_in(g, roof)
    beside = junctions(g, tops)
    for k, mask, corners in sorted({v for b, v in tops.items() if b not in beside} | set(extra_tops)):
        sheet.add(top_name(k, mask, corners), top(k, outside_of(mask, corners)), tileset="secondary",
                  ground="grass", solid=True)
    pieces = sorted({name: idx for name, idx in beside.values()}.items())
    assert len(pieces) <= len(JUNCTION_CHARS), "more tops beside faces than characters for them"
    char_of = {}
    for (name, idx), ch in zip(pieces, JUNCTION_CHARS):
        sheet.add(name, idx, tileset="secondary", ground="grass", solid=True)
        char_of[name] = ch
    for (x, y), (name, _) in beside.items():
        g[y][x] = char_of[name]
    for c in sorted(set(FACE[ch] for r in g for ch in r if ch in FACE)):
        sheet.add(f"face_{c}", pack(f"face/{c}.png"), tileset="secondary", ground="grass", solid=True)
    if "rock_stairs" in extras:
        sheet.add("rock_stairs", pack("face/stairs.png"), tileset="secondary")
    if "small_rock" in extras:
        sheet.add("small_rock", pack("rocks/small_rock.png"), tileset="secondary", ground="grass", solid=True)
    if "big_boulder" in extras:
        sheet.add("big_boulder", pack("rocks/big_boulder.png"), tileset="secondary", ground="grass", solid=True)
    return char_of


def legend(char_of: dict[str, str]) -> dict:
    """The legend for the cliffs: the tops by phase (all one cliff, ``C``, for their edges), the face's columns and
    the tops beside a face (part of the cliff for their neighbours' edges)."""
    out = {ch: {"auto": f"top{k}", "joins": "C"} for k, ch in enumerate(TOP, 1)}
    out.update({ch: f"face_{col}" for ch, col in FACE.items()})
    out.update({ch: {"name": name, "joins": "C"} for name, ch in char_of.items()})
    return out
