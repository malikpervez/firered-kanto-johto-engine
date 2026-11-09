"""Kanto Fuchsia City v0.1 (../packs/fuchsia_v0.1, a native pixel pack made with another AI from
Fuchsia_City_v0.1_prompt.md): Fuchsia's own ground and details.

- sandstone: warm sandstone flags in courses, a 32x32 repeat (the four phase pieces "large_NW" ... "large_SE", the
  phase anchored to the map as the pack lays it: an even row is north, an even column west), for every street, the
  Safari plaza, its avenue and the zoo's walks; with half-block joins to the routes' cobble (west and east) and to the
  kit's dirt (south: the beach path). Its edge to the lawn is the same on every side: two pixels of the kit's lawn, a
  joint and a pale lip.
- palisade: golden bamboo canes lashed to two rails (picked by the palisade beside it: 1 N, 2 E, 4 S, 8 W; a board or
  a wall beside it isn't palisade, so it ends in a post there).
- details: an exhibit board for each pen (1x1) and a fuchsia bush (1x1), both solid.

Every 8x8 quarter is in one palette, named by the pack: the kit's plants (bank 8, the bush), the Safari lodge's and
Koga's Gym's (bank 9, the town's own: the palisade and the boards) and the pack's one new palette, fuchsia_town (bank
10, the sandstone: the kit's ground palette with its darkest colour swapped for the stone's, so the joins and the lawn
edges keep the kit's exact greens, browns and greys). A quarter's indices are the pack's, in the order of that
palette's .gpl; they're matched to the map's palette by colour. The sandstone is put together the pack's way: each
quarter copied from a named piece, by the recipe for the block's phase and its neighbours that aren't sandstone (1 N,
2 E, 4 S, 8 W, 16 NE, 32 SE, 64 SW, 128 NW), or a join's recipe where it meets the cobble or the dirt.

A map lays them with ``lay``: its sandstone blocks (and where they join), the palisade, and the details on them; it
gets back the legend, the spec entries, the solid characters, the new palette and each block's name (for what stands
on the sandstone).
"""
import json
from pathlib import Path

import numpy as np
from PIL import Image

import kit

PACK = Path(__file__).resolve().parents[1] / "packs/fuchsia_v0.1"
QUARTERS = {"NW": np.s_[0:8, 0:8], "NE": np.s_[0:8, 8:16], "SW": np.s_[8:16, 0:8], "SE": np.s_[8:16, 8:16]}
BITS = {(0, -1): 1, (1, 0): 2, (0, 1): 4, (-1, 0): 8, (1, -1): 16, (1, 1): 32, (-1, 1): 64, (-1, -1): 128}
RAIL_BITS = {(0, -1): 1, (1, 0): 2, (0, 1): 4, (-1, 0): 8}
JOINS = ("to_cobble_W", "to_cobble_E", "to_dirt_S")  # the pack's joins: the kit's cobble or dirt on that side
LETTERS = [chr(c) for c in range(0x1E00, 0x1F00)]  # the characters lay hands out (no map uses them)
NEW_BANK = 10


def gpl(name: str) -> list[tuple[int, int, int]]:
    rows = [r.split() for r in (PACK / "palettes" / f"{name}.gpl").read_text().splitlines() if r.strip()[:1].isdigit()]
    return [tuple(int(v) for v in r[:3]) for r in rows[:16]]


NEW_PALETTE = gpl("fuchsia_town")  # bank 10: the sandstone


def banks(town_palette) -> dict[str, tuple[int, list]]:
    """The pack's palettes: the bank each goes in and its colours there (the map's own order)."""
    return {"kit_ground": (kit.BANK["ground"], kit.PALS["ground"]), "kit_water": (kit.BANK["water"], kit.PALS["water"]),
            "kit_wood": (kit.BANK["wood"], kit.PALS["wood"]), "kit_plants": (kit.BANK["plants"], kit.PALS["plants"]),
            "fuchsia_safari": (9, list(town_palette)), "fuchsia_town": (NEW_BANK, NEW_PALETTE)}


def _catalogue() -> dict[tuple[str, str], dict]:
    out = {}
    for surface in ("sandstone", "palisade"):
        meta = json.loads((PACK / surface / f"{surface}.json").read_text())
        for p in meta["tiles"] + meta.get("transitions", []):
            out[surface, p["name"]] = dict(p, folder=PACK / surface)
    for f in sorted((PACK / "details").glob("*.json")):
        meta = json.loads(f.read_text())
        if "footprint_blocks" in meta:
            out["details", meta["id"]] = dict(meta, folder=PACK / "details")
    return out


PIECES = _catalogue()
_recipes: dict[str, dict] = {}


def _load(rel: str) -> dict:
    if rel not in _recipes:
        _recipes[rel] = json.loads((PACK / rel).read_text())
    return _recipes[rel]


class Pack:
    """The pack's pictures as the map's palette indices, for a map whose lodge and Gym have ``town_palette``."""

    def __init__(self, town_palette):
        self.banks = banks(town_palette)
        self._pictures: dict = {}

    def picture(self, surface: str, name: str) -> tuple[np.ndarray, list[list[str]]]:
        """A piece's indices (each 8x8 tile in its own palette, the map's order) and the palette of each tile."""
        if (surface, name) not in self._pictures:
            meta = PIECES[surface, name]
            with Image.open(meta["folder"] / meta["image"]) as im:
                assert im.mode == "P", f"{surface}/{name}: not an indexed PNG"
                raw = np.array(im, np.uint8)
            pals = meta["palettes_8x8"]
            assert raw.shape == (8 * len(pals), 8 * len(pals[0])), f"{surface}/{name}: its palette grid isn't its size"
            out = np.zeros_like(raw)
            for ty, row in enumerate(pals):
                for tx, pal in enumerate(row):
                    src, dst = gpl(pal), self.banks[pal][1]
                    t = raw[ty * 8:ty * 8 + 8, tx * 8:tx * 8 + 8]
                    lut = np.zeros(16, np.uint8)
                    for i in {int(v) for v in np.unique(t)} - {0}:
                        assert src[i] in dst, f"{surface}/{name}: colour {src[i]} isn't in the map's {pal} palette"
                        lut[i] = dst.index(src[i])
                    out[ty * 8:ty * 8 + 8, tx * 8:tx * 8 + 8] = lut[t]
            self._pictures[surface, name] = (out, pals)
        return self._pictures[surface, name]

    def quarter(self, surface: str, name: str, q: str) -> tuple[np.ndarray, str]:
        idx, pals = self.picture(surface, name)
        qy, qx = divmod(list(QUARTERS).index(q), 2)
        return idx[QUARTERS[q]], pals[qy][qx]


def sandstone_recipe(mask: int, phase: str, join: str | None = None) -> dict[str, tuple[str, str]]:
    """The (piece, quadrant) each quarter of a sandstone block copies: by its phase and ``mask`` (its neighbours that
    aren't sandstone), from the join's recipe where it meets the cobble or the dirt (its lawn edges kept on the
    sandstone's half)."""
    if join:
        r = _load("sandstone/join_recipes.json")["recipes"][join][phase]
    else:
        r = _load("sandstone/phase_recipes.json")["recipes_by_phase"][phase]
    return {q: (v["piece"], v["quadrant"]) for q, v in r[str(mask)].items()}


def palisade_piece(mask: int) -> str:
    return _load("palisade/autotile_recipes.json")["recipes"][str(mask)]["piece"]


def phase(x: int, y: int) -> str:
    """The sandstone's phase at (x, y), anchored to the map as the pack's previews lay it."""
    return ("N" if y % 2 == 0 else "S") + ("W" if x % 2 == 0 else "E")


def lay(g, *, sandstone: set, joins: dict[str, set] | None = None, level: set = frozenset(),
        palisade: set = frozenset(), details=(), town_palette, out: Path, spec_dir: Path) -> dict:
    """Lay the pack into the plan ``g``: ``sandstone`` (its cells), ``joins`` (a join's name -> the sandstone cells that
    take it: the cobble or the dirt is beside them on that side), ``palisade`` (cells) and ``details`` ((piece, x, y):
    its top-left block). ``level`` are cells the sandstone runs up to without an edge, as if they were sandstone (the
    lodge's front). A block of the map's edge counts as not sandstone beyond it (the joins' recipes take that side).
    The palisade and the details stand on the sandstone their cell has or, if none, the lawn, and draw over it.

    Returns the "legend" for the characters it wrote, the spec "entries", the "solid" characters, the "palette" of the
    new bank (``NEW_BANK``) and the "ground": the block name at each cell it laid (for the props standing on it)."""
    h, w = len(g), len(g[0])
    pk = Pack(town_palette)
    join_at = {}
    for name, cells in (joins or {}).items():
        assert name in JOINS, name
        for xy in cells:
            assert xy in sandstone and xy not in join_at, f"{xy}: a join on a block that isn't plain sandstone"
            join_at[xy] = name

    def outside(x, y) -> bool:
        return (x, y) not in sandstone and (x, y) not in level

    blocks: dict[str, tuple[np.ndarray, list[list[str]], dict]] = {}  # name -> indices, palette grid, entry
    by_picture: dict[tuple, str] = {}
    names: dict[tuple[int, int], str] = {}

    def add(name: str, idx: np.ndarray, pals: list[list[str]], **entry) -> str:
        key = (idx.tobytes(), str(pals), json.dumps(entry, sort_keys=True))
        if key in by_picture:  # the same block under another name (a diagonal that changes nothing): the first's
            return by_picture[key]
        if name not in blocks:
            blocks[name] = (idx, pals, entry)
            by_picture[key] = name
        return name

    # the sandstone, block by block
    for x, y in sorted(sandstone, key=lambda c: (c[1], c[0])):
        ph = phase(x, y)
        m = sum(b for (dx, dy), b in BITS.items() if outside(x + dx, y + dy))
        jn = join_at.get((x, y))
        idx, pals = np.zeros((16, 16), np.uint8), set()
        for q, (piece, src) in sandstone_recipe(m, ph, jn).items():
            t, pal = pk.quarter("sandstone", piece, src)
            idx[QUARTERS[q]] = t
            pals.add(pal)
        assert pals == {"fuchsia_town"}, f"({x},{y}): the sandstone's quarters in {pals}"
        names[x, y] = add(f"sandstone_{ph}#{m}" + (f"_{jn}" if jn else ""), idx, [["fuchsia_town"] * 2] * 2,
                          ground="grass")

    # the palisade and the details, each block over the ground its cell has
    solid = set()

    def stand(piece_name: str, x: int, y: int, idx: np.ndarray, pals, is_solid: bool) -> None:
        under = names.get((x, y), "grass")
        cell = add(f"{piece_name}@{under}", idx, pals, ground=under, **({"solid": True} if is_solid else {}))
        names[x, y] = cell
        if is_solid:
            solid.add(cell)

    for x, y in sorted(palisade):
        piece = palisade_piece(sum(b for (dx, dy), b in RAIL_BITS.items() if (x + dx, y + dy) in palisade))
        idx, pals = pk.picture("palisade", piece)
        stand(f"palisade_{piece}", x, y, idx, pals, True)
    for piece, x, y in details:
        meta = PIECES["details", piece]
        fw, fh = meta["footprint_blocks"]["width"], meta["footprint_blocks"]["height"]
        idx, pals = pk.picture("details", piece)
        walkable = {tuple(b) for b in meta["walkable_blocks"]}
        for j in range(fh):
            for i in range(fw):
                assert (x + i, y + j) not in palisade, f"{piece} at ({x},{y}) is on the palisade"
                stand(f"{piece}_{i}{j}", x + i, y + j, idx[j * 16:(j + 1) * 16, i * 16:(i + 1) * 16],
                      [r[2 * i:2 * i + 2] for r in pals[2 * j:2 * j + 2]], (i, j) not in walkable)

    # the sheets, one for each bank; the sandstone's first (what stands on it names it as its ground, and pae wants a
    # ground listed first)
    entries, by_bank = [], {}
    for name, (idx, pals, entry) in blocks.items():
        flat = {p for row in pals for p in row}
        assert len(flat) == 1, f"{name}: its quarters are in {flat}"
        by_bank.setdefault(flat.pop(), []).append((name, idx, entry))
    for pal, cells in sorted(by_bank.items(), key=lambda kv: (kv[0] != "fuchsia_town", kv[0])):
        bank, colours = pk.banks[pal]
        sh = kit.Sheet(f"fuchsia_{pal}", colours, bank, out, spec_dir, cols=8)
        for name, idx, entry in cells:
            sh.add(name, idx, tileset="secondary", dedupe=True, **entry)
        entries += sh.write()

    # a character for each block
    legend, letter = {}, {}
    for (x, y), name in sorted(names.items(), key=lambda kv: (kv[0][1], kv[0][0])):
        if name not in letter:
            letter[name] = LETTERS[len(letter)]
            legend[letter[name]] = name
        g[y][x] = letter[name]
    uses_new = any(p == "fuchsia_town" for idx, pals, e in blocks.values() for row in pals for p in row)
    return {"legend": legend, "entries": entries, "solid": {letter[n] for n in solid},
            "palette": NEW_PALETTE if uses_new else None, "ground": dict(names)}
