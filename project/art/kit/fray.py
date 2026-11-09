"""The cobble-to-dirt join: where a town's grey cobbles meet a route's brown dirt road, the stones thin out into the
dirt over two blocks instead of stopping on a dead-straight line.

The join is two blocks along the road, drawn as one picture and cut in two: the cobble block next to the dirt (most
stones still there, the last ones loose with dirt between them) and the dirt block next to the cobbles (a few stray
stones, half sunk, the dirt's own texture round them). Its far ends are exactly the kit's ``cobble(15)`` and
``dirt(15)``, so it runs on into both without a seam; its stones are the cobbles' own (the same Voronoi stones, kept or
dropped whole, the loose ones smaller), shaded as the cobbles are, with the dirt's dark shade under them; its sides
take the cobble's and the dirt's own wobbly edges where the road meets grass.

Each half is an edge surface for ``pae map paint`` ("fray<side>[v]_cobble#mask", "fray<side>[v]_dirt#mask"; <side> is
the side the dirt is on, N E S W; v the variant, 1 or 2, none for the first): only the two sides across the road
matter (grass there or more road); the cobble half counts as cobble for its neighbours, the dirt half as dirt, so
neither draws an edge against the road it continues. The front where the stones give out wanders, in three variants
that are the same at a block's sides, so neighbours across the road run on into each other with different fronts.
It changes nothing in the kit: a map adds the pieces to its own (secondary) tileset, in the ground palette (bank 0).

In a map's make_art.py, after its checks (the plan's "=" and ":" are the kit's cobble and dirt):
    import fray
    fray.lay(g, "ǀǂǃ", "ǁǄǅ")                 # the cobble half's letters (one a variant), the dirt half's
    sh = kit.Sheet("fray", kit.PALS["ground"], kit.BANK["ground"], HERE, HERE, cols=8)
    fray.add(sh, "N")                          # the sides the dirt is on in this map
    spec_mt += sh.write()
    legend.update(fray.legend("N", "ǀǂǃ", "ǁǄǅ"))
(a map with joins on more than one side uses other letters for each side's.)
"""
import random

import numpy as np

import kit

SIDES = ("N", "E", "S", "W")
ACROSS = {"N": (2, 8), "S": (2, 8), "E": (1, 4), "W": (1, 4)}  # the mask bits across the road


VARIANTS = 3  # the front's shapes: the same at a block's two sides (so any two run on side by side), not inside


def _composite(side: str, variant: int = 0) -> tuple[np.ndarray, np.ndarray]:
    """The two-block join as one picture (dirt end first along the road): returns it and, per pixel, which part it is
    (True: a stone)."""
    vertical = side in "NS"
    h, w = (32, 16) if vertical else (16, 32)
    reps = (h // 16, w // 16)
    cob = np.tile(kit.cobble(15), reps)
    drt = np.tile(kit.dirt(15), reps)
    cid, gap, rel = kit.COBBLE
    cid = np.tile(cid, reps)
    rel = np.tile(rel, reps + (1,))
    yy, xx = np.mgrid[0:h, 0:w]
    cx = xx + 0.5 - rel[..., 0]
    cy = yy + 0.5 - rel[..., 1]
    dist = np.hypot(rel[..., 0], rel[..., 1])
    # how far into the cobbles each stone's centre is, from the dirt end (0) to the cobble end (32)
    depth = {"N": cy, "S": 32 - cy, "W": cx, "E": 32 - cx}[side]
    across = (cx if vertical else cy) % 16
    # the front where the cobbles give out wanders across the road (the same in every block side by side)
    front = 17 + 5 * np.sin(2 * np.pi * across / 16 + 0.7) + 2.5 * np.sin(4 * np.pi * across / 16 + 2.1)
    # each variant bends it differently inside the block, away from its sides (a stone over a side is the same in all)
    inside = (across > 3.5) & (across < 12.5)
    bend = np.sin(np.pi * (across - 3.5) / 9)
    front = front + inside * {0: 0 * bend, 1: -6 * bend, 2: 5 * np.sin(2 * np.pi * (across - 3.5) / 9)}[variant]
    stone = np.zeros((h, w), bool)
    decided: dict[tuple[int, int], tuple[bool, float]] = {}
    for y in range(h):
        for x in range(w):
            d, f = float(depth[y, x]), float(front[y, x])
            key = (int(cid[y, x]), int(round(d * 4)))
            if key not in decided:
                r = random.Random(key[0] * 7331 + key[1] * 97 + 1 + (variant * 13 if inside[y, x] else 0))
                if d >= 28 or d >= f + 4:
                    p, rmax = 1.0, 99.0
                elif d >= f:
                    p, rmax = 0.85, 2.3 + 0.2 * (d - f)
                elif d >= f - 7 and d >= 5:
                    p, rmax = 0.3, 1.7
                elif d >= 5:
                    p, rmax = 0.04, 1.6
                else:
                    p, rmax = 0.0, 0.0
                decided[key] = (r.random() < p, rmax)
            keep, rmax = decided[key]
            stone[y, x] = keep and dist[y, x] <= rmax
    # drop the crumbs: a loose stone of fewer than 5 pixels reads as noise
    inst = {}
    for y in range(h):
        for x in range(w):
            if stone[y, x]:
                inst.setdefault((int(cid[y, x]), int(round(float(depth[y, x]) * 4))), []).append((y, x))
    for key, px in inst.items():
        if len(px) < 5 and key[1] < 28 * 4:
            for y, x in px:
                stone[y, x] = False
    out = np.where(stone, cob, drt).astype(np.uint8)
    # the stones sit in the dirt: a dark rim on their lower/right sides and the dirt's shade under them. The road
    # repeats across (the same block side by side), so across it the neighbours wrap; along it they don't.
    axis_across = 1 if vertical else 0
    def shifted(a, dy, dx):
        if (dx and axis_across == 1) or (dy and axis_across == 0):
            return np.roll(a, (dy, dx), (0, 1))
        p = np.pad(a, 1, constant_values=a.dtype.type(0))
        return p[1 - dy:1 - dy + h, 1 - dx:1 - dx + w]
    loose = stone & (depth < 28)
    below_dirt = shifted(~stone, -1, 0) & loose  # stone pixel with dirt under it
    right_dirt = shifted(~stone, 0, -1) & loose
    out[below_dirt | right_dirt] = kit.KD
    shade = (shifted(stone, 1, 0) & ~stone) & (depth < 30)  # dirt just under a stone
    out[shade] = kit.SD
    return out, stone


def _cut(t: np.ndarray, bits: int, seed: int) -> np.ndarray:
    """The side edges (as kit._cut draws them) where ``bits`` says grass; the lip in the dirt's shade or the
    mortar's, whichever the edge pixel is."""
    t = t.copy()
    dirt_colours = (kit.SD, kit.SM, kit.SL)
    for bit, seed_off in kit.EDGE_SEED.items():
        if not bits & bit:
            continue
        wob = kit.wobble(seed + seed_off, 16, 1, 3)
        for i in range(16):
            d = wob[i]
            if bit == 1:
                t[:d, i] = 0
                yx = (d, i)
            elif bit == 4:
                t[16 - d:, i] = 0
                yx = (15 - d, i)
            elif bit == 8:
                t[i, :d] = 0
                yx = (i, d)
            else:
                t[i, 16 - d:] = 0
                yx = (i, 15 - d)
            if t[yx]:
                t[yx] = kit.SD if t[yx] in dirt_colours else kit.KD
    return t


def surface(side: str, part: str, variant: int = 0) -> str:
    """The edge surface's name: part "cobble" or "dirt"."""
    return f"fray{side}{variant or ''}_{part}"


def pieces(side: str) -> dict[str, np.ndarray]:
    """{name: 16x16 block} for the join with the dirt on ``side`` of the cobbles: both halves, every variant and mask
    (the drawing depends only on the two sides across the road; the others are the same block)."""
    assert side in SIDES, side
    a, b = ACROSS[side]
    out = {}
    for v in range(VARIANTS):
        comp, _ = _composite(side, v)
        if side in "NS":
            dirt_half, cob_half = (comp[:16], comp[16:]) if side == "N" else (comp[16:], comp[:16])
        else:
            dirt_half, cob_half = (comp[:, :16], comp[:, 16:]) if side == "W" else (comp[:, 16:], comp[:, :16])
        for m in range(16):
            grass = (a | b) & ~m  # across-road sides with no road beyond: the edge
            out[f"{surface(side, 'cobble', v)}#{m}"] = _cut(cob_half, grass, 11)
            out[f"{surface(side, 'dirt', v)}#{m}"] = _cut(dirt_half, grass, 23)
    return out


def add(sheet, side: str, tileset: str = "secondary") -> None:
    """Add the join's pieces to a map's sheet (in the ground palette). Identical blocks share a metatile."""
    for name, idx in pieces(side).items():
        sheet.add(name, idx, tileset=tileset, ground="grass", dedupe=True)


def legend(side: str, cobble_chars: str, dirt_chars: str, cobble_group: str = "=", dirt_group: str = ":") -> dict:
    """The legend letters for the two halves, one letter a variant (``VARIANTS`` of each): the cobble half in the
    cobbles' group, the dirt half in the dirt's."""
    assert len(cobble_chars) == len(dirt_chars) == VARIANTS
    out = {}
    for v in range(VARIANTS):
        out[cobble_chars[v]] = {"auto": surface(side, "cobble", v), "joins": cobble_group}
        out[dirt_chars[v]] = {"auto": surface(side, "dirt", v), "joins": dirt_group}
    return out


def lay(g, cobble_chars: str, dirt_chars: str, cobble: str = "=", dirt: str = ":", sides: str = "NESW") -> dict:
    """Put the join in a plan ``g`` (rows of letters, changed in place) wherever a block of ``cobble`` has ``dirt`` on
    one of ``sides``: that block and the dirt block take the two halves, in the variant their place across the road
    gives (neighbours across the road differ). Returns {side: count} of the joins laid."""
    h, w = len(g), len(g[0])
    step = {"N": (0, -1), "S": (0, 1), "W": (-1, 0), "E": (1, 0)}
    done = {}
    for y in range(h):
        for x in range(w):
            if g[y][x] != cobble:
                continue
            for side in sides:
                dx, dy = step[side]
                if 0 <= x + dx < w and 0 <= y + dy < h and g[y + dy][x + dx] == dirt:
                    v = (x if side in "NS" else y) % VARIANTS
                    g[y][x], g[y + dy][x + dx] = cobble_chars[v], dirt_chars[v]
                    done[side] = done.get(side, 0) + 1
                    break
    return done


def preview(path, side: str = "N", width: int = 4) -> None:
    """A picture of the join (with plain cobble and dirt either side) to look at it outside a map."""
    from PIL import Image
    p = pieces(side)
    full = lambda n, v=0: p[f"{surface(side, n, v)}#15"]
    if side in "NS":
        col = [[kit.dirt(15)] * width, [full("dirt", i % VARIANTS) for i in range(width)],
               [full("cobble", i % VARIANTS) for i in range(width)], [kit.cobble(15)] * width]
        col = col if side == "N" else col[::-1]
        img = np.vstack([np.hstack(c) for c in col])
    else:
        row = [kit.dirt(15), full("dirt"), full("cobble"), kit.cobble(15)]
        row = row if side == "W" else row[::-1]
        img = np.vstack([np.hstack(row)] * width)
    Image.fromarray(kit.rgba(img, kit.P0), "RGBA").resize((img.shape[1] * 6, img.shape[0] * 6), 0).save(path)
