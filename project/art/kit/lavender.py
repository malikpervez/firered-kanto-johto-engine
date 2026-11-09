"""Kanto Lavender Town v0.1 (../packs/lavender_v0.1, a native pixel pack made with another AI from
Lavender_Town_v0.1_prompt.md): Lavender's own ground and details.

- slate: blue-grey slate flags, a 32x32 repeat (the four phase pieces "large_NW" ... "large_SE", the phase anchored
  to the map: an even column is west, an odd row north), for the square and the walk to the Pokémon Tower; with joins
  to the kit's cobble (the roads, which run on into the routes).
- gravel: fine pale gravel, for the paths between the beds.
- lavender_beds: rows of lavender over sage leaves, walkable as flowers are, see-through between the plants (the lawn
  shows).
- railing: low iron railings (picked by the rails beside them: 1 N, 2 E, 4 S, 8 W) and an open gate (3x1: two solid
  posts, the middle block walkable).
- details: three memorial stones, an offering stone, a stone lantern (1x2), Lavender's street lamp (1x2), Pokémon food
  and water bowls, a straw bed (walkable) and a rest shelter (2x2).

Every 8x8 quarter is in one palette, named by the pack: the kit's ground (bank 0), wood (2) and plants (8), the
Pokémon Tower's (bank 9, the town's own) and the pack's one new palette, lavender_town (bank 10, the slate, the gravel
and the beds). A quarter's indices are the pack's, in the order of that palette's .gpl; they're matched to the map's
palette by colour. The surfaces are put together the pack's way: each quarter copied from a named piece, by the recipe
for the block's neighbours (1 N, 2 E, 4 S, 8 W, 16 NE, 32 SE, 64 SW, 128 NW: the neighbours that aren't it).

A map lays them with ``lay``: its slate, gravel and bed blocks, its rails and gates, and the details on them; it gets
back the legend, the spec entries, the solid characters and the new palette.
"""
import json
from pathlib import Path

import numpy as np
from PIL import Image

import kit

PACK = Path(__file__).resolve().parents[1] / "packs/lavender_v0.1"
QUARTERS = {"NW": np.s_[0:8, 0:8], "NE": np.s_[0:8, 8:16], "SW": np.s_[8:16, 0:8], "SE": np.s_[8:16, 8:16]}
BITS = {(0, -1): 1, (1, 0): 2, (0, 1): 4, (-1, 0): 8, (1, -1): 16, (1, 1): 32, (-1, 1): 64, (-1, -1): 128}
SIDE = {"N": (0, -1), "E": (1, 0), "S": (0, 1), "W": (-1, 0)}
RAIL_BITS = {(0, -1): 1, (1, 0): 2, (0, 1): 4, (-1, 0): 8}
BEDS_FILL = ("center", "center_b", "center_c")  # the beds' three fills, by (x + 2y) % 3 where no edge shows
LETTERS = [chr(c) for c in range(0x200, 0x300)]  # the characters lay hands out (no map uses them)
NEW_BANK = 10


def gpl(name: str) -> list[tuple[int, int, int]]:
    rows = [r.split() for r in (PACK / "palettes" / f"{name}.gpl").read_text().splitlines() if r.strip()[:1].isdigit()]
    return [tuple(int(v) for v in r[:3]) for r in rows[:16]]


NEW_PALETTE = gpl("lavender_town")  # bank 10: the slate, the gravel and the beds


def banks(tower_palette) -> dict[str, tuple[int, list]]:
    """The pack's palettes: the bank each goes in and its colours there (the map's own order)."""
    return {"kit_ground": (kit.BANK["ground"], kit.PALS["ground"]), "kit_water": (kit.BANK["water"], kit.PALS["water"]),
            "kit_wood": (kit.BANK["wood"], kit.PALS["wood"]), "kit_plants": (kit.BANK["plants"], kit.PALS["plants"]),
            "lavender_tower": (9, list(tower_palette)), "lavender_town": (NEW_BANK, NEW_PALETTE)}


def _catalogue() -> dict[tuple[str, str], dict]:
    out = {}
    for surface in ("slate", "gravel", "lavender_beds", "railing"):
        meta = json.loads((PACK / surface / f"{surface}.json").read_text())
        for p in meta["tiles"] + meta["transitions"]:
            out[surface, p["name"]] = dict(p, folder=PACK / surface)
    for f in sorted((PACK / "details").glob("*.json")):
        meta = json.loads(f.read_text())
        if "footprint_blocks" in meta:
            out["details", meta["id"]] = dict(meta, folder=PACK / "details")
    return out


PIECES = _catalogue()
_recipes: dict[str, dict] = {}


class Pack:
    """The pack's pictures as the map's palette indices, for a map whose Pokémon Tower has ``tower_palette``."""

    def __init__(self, tower_palette):
        self.banks = banks(tower_palette)
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

    def recipe(self, surface: str, mask: int, phase: str | None = None) -> dict[str, tuple[str, str]]:
        """The (piece, quadrant) each quarter of the block for ``mask`` copies: the surface's autotile recipe, or the
        slate's by its ``phase``."""
        key = f"{surface}/{'phase' if phase else 'autotile'}"
        if key not in _recipes:
            fn = "phase_recipes.json" if phase else "autotile_recipes.json"
            _recipes[key] = json.loads((PACK / surface / fn).read_text())
        r = _recipes[key]["recipes_by_phase"][phase] if phase else _recipes[key]["recipes"]
        return {q: (v["piece"], v["quadrant"]) for q, v in r[str(mask)].items()}


def phase(x: int, y: int) -> str:
    """The slate's phase at (x, y), anchored to the map (as the pack's previews lay it)."""
    return ("N" if y % 2 == 1 else "S") + ("W" if x % 2 == 0 else "E")


def lay(g, *, slate: set, gravel: set, beds: set, rails: set = frozenset(), gates=(), details=(), roads: str = "=",
        edge_roads: set = frozenset(), gravel_edges: bool = True, tower_palette, out: Path, spec_dir: Path) -> dict:
    """Lay the pack into the plan ``g``: ``slate``, ``gravel`` and ``beds`` (their cells), ``rails`` (cells), ``gates``
    (the left block of each, 3x1) and ``details`` ((piece, x, y): its top-left block). A rail, a gate or a detail stands
    on the surface its cell has (slate, gravel, a bed or, if none, the lawn) and draws over it.

    - The slate's quarters by a road (``roads``' characters, the kit's cobble, or a block just past the map's edge in
      ``edge_roads``, where a neighbour's cobble road comes in) are the pack's join to the cobble on that side; the others its own, by its neighbours that are neither slate nor road. Every slate block counts as
      cobble for the cobble beside it (no lawn lip at the join).
    - The gravel draws its edges only where lawn (anything but gravel, a bed or slate) is beside it, north, east, south
      or west: it runs quietly into the beds and up to the slate. With ``gravel_edges`` False it draws none at all, so
      it runs the same way into the lawn, trees and forest too.
    - The beds draw their edges where anything but a bed is beside them.

    Returns the "legend" for the characters it wrote, the spec "entries", the "solid" characters, and the "palette"
    of the new bank (``NEW_BANK``) if anything uses it."""
    h, w = len(g), len(g[0])
    pk = Pack(tower_palette)
    surface_of = {}
    for cells, kind in ((slate, "slate"), (gravel, "gravel"), (beds, "lavender_beds")):
        for xy in cells:
            assert xy not in surface_of, f"{xy}: two surfaces"
            surface_of[xy] = kind

    def at(x, y):
        return g[y][x] if 0 <= x < w and 0 <= y < h else None

    def road(x, y):
        if (x, y) in edge_roads:
            return True
        return (x, y) not in surface_of and at(x, y) is not None and at(x, y) in roads

    def mask(x, y, outside) -> int:
        return sum(b for (dx, dy), b in BITS.items() if outside(x + dx, y + dy))

    def compose(parts: dict[str, tuple[str, str, str]]) -> tuple[np.ndarray, set]:
        idx, pals = np.zeros((16, 16), np.uint8), set()
        for q, (surface, piece, src) in parts.items():
            t, pal = pk.quarter(surface, piece, src)
            idx[QUARTERS[q]] = t
            pals.add(pal)
        return idx, pals

    blocks: dict[str, tuple[np.ndarray, list[list[str]], dict]] = {}  # name -> indices, palette grid, entry
    names: dict[tuple[int, int], str] = {}

    def add(name: str, idx: np.ndarray, pals: list[list[str]], **entry) -> str:
        if name not in blocks:
            blocks[name] = (idx, pals, entry)
        return name

    def one(pals: set) -> list[list[str]]:
        assert len(pals) == 1, f"quarters in more than one palette: {pals}"
        p = next(iter(pals))
        return [[p, p], [p, p]]

    # the surfaces
    for (x, y), kind in sorted(surface_of.items(), key=lambda kv: (kv[0][1], kv[0][0])):
        if kind == "slate":
            ph = phase(x, y)
            m = mask(x, y, lambda a, b: at(a, b) is not None and surface_of.get((a, b)) != "slate" and not road(a, b))
            rec = pk.recipe("slate", m, ph)
            parts, joins = {}, []
            for q in QUARTERS:
                side = next((s for s in q if road(x + SIDE[s][0], y + SIDE[s][1])), None)
                if side:
                    parts[q] = ("slate", f"to_cobble_{side}_{ph}", q)
                    joins.append(f"{q}{side}")
                else:
                    parts[q] = ("slate",) + rec[q]
            idx, pals = compose(parts)
            name = f"slate_{ph}#{m}" + (f"_to_cobble_{'_'.join(joins)}" if joins else "")
        elif kind == "gravel":
            m = sum(BITS[d] for d in SIDE.values()
                    if at(x + d[0], y + d[1]) is not None and (x + d[0], y + d[1]) not in surface_of) if gravel_edges else 0
            idx, pals = compose({q: ("gravel",) + v for q, v in pk.recipe("gravel", m).items()})
            name = f"gravel#{m}"
        else:
            m = mask(x, y, lambda a, b: at(a, b) is not None and surface_of.get((a, b)) != "lavender_beds")
            if m == 0:
                fill = BEDS_FILL[(x + 2 * y) % 3]
                idx, pals = compose({q: ("lavender_beds", fill, q) for q in QUARTERS})
                name = f"lavender_{fill}"
            else:
                idx, pals = compose({q: ("lavender_beds",) + v for q, v in pk.recipe("lavender_beds", m).items()})
                name = f"lavender#{m}"
        names[x, y] = add(name, idx, one(pals), ground="grass")

    def ground(x, y) -> str:
        return names.get((x, y), "grass")

    # the rails, the gates and the details, each block over the ground its cell has
    solid = set()

    def stand(piece_name: str, x: int, y: int, idx: np.ndarray, pals, is_solid: bool) -> None:
        under = ground(x, y)
        if not idx.any() and not is_solid:  # nothing of its own here (the open gate's middle): just its ground
            names.setdefault((x, y), under)
            return
        cell = add(f"{piece_name}@{under}", idx, pals, ground=under, **({"solid": True} if is_solid else {}))
        names[x, y] = cell
        if is_solid:
            solid.add(cell)

    for x, y in sorted(rails):
        m = sum(b for (dx, dy), b in RAIL_BITS.items() if (x + dx, y + dy) in rails)
        piece = _recipe_rail(m)
        idx, pals = pk.picture("railing", piece)
        stand(f"rail_{piece}", x, y, idx, pals, True)
    for x, y in gates:
        idx, pals = pk.picture("railing", "gate_open")
        meta = PIECES["railing", "gate_open"]
        walkable = {tuple(b) for b in meta["walkable_blocks"]}
        for i in range(3):
            stand(f"gate_open_{i}", x + i, y, idx[:, i * 16:(i + 1) * 16], [r[2 * i:2 * i + 2] for r in pals],
                  (i, 0) not in walkable)
    for piece, x, y in details:
        meta = PIECES["details", piece]
        fw, fh = meta["footprint_blocks"]["width"], meta["footprint_blocks"]["height"]
        idx, pals = pk.picture("details", piece)
        walkable = {tuple(b) for b in meta["walkable_blocks"]}
        for j in range(fh):
            for i in range(fw):
                assert (x + i, y + j) not in rails, f"{piece} at ({x},{y}) is on a rail"
                stand(f"{piece}_{i}{j}", x + i, y + j, idx[j * 16:(j + 1) * 16, i * 16:(i + 1) * 16],
                      [r[2 * i:2 * i + 2] for r in pals[2 * j:2 * j + 2]], (i, j) not in walkable)

    # the sheets: one for each bank, and one picture for the blocks whose quarters are in two banks
    entries, by_bank, mixed = [], {}, []
    for name, (idx, pals, entry) in blocks.items():
        flat = {p for row in pals for p in row}
        if len(flat) == 1:
            by_bank.setdefault(flat.pop(), []).append((name, idx, entry))
        else:
            mixed.append((name, idx, pals, entry))
    # the surfaces' sheet first: what stands on them names them as its ground, and pae wants a ground listed first
    for pal, cells in sorted(by_bank.items(), key=lambda kv: (kv[0] != "lavender_town", kv[0])):
        bank, colours = pk.banks[pal]
        sh = kit.Sheet(f"lavender_{pal}", colours, bank, out, spec_dir, cols=8)
        for name, idx, entry in cells:
            sh.add(name, idx, tileset="secondary", dedupe=True, **entry)
        entries += sh.write()
    if mixed:
        canvas = np.zeros((16, 16 * len(mixed), 4), np.uint8)
        for i, (name, idx, pals, entry) in enumerate(mixed):
            for (qy, qx), q in zip(((0, 0), (0, 1), (1, 0), (1, 1)), QUARTERS.values()):
                canvas[:, i * 16:(i + 1) * 16][q] = kit.rgba(idx[q], pk.banks[pals[qy][qx]][1])
            entries.append({"name": name, "image": (Path(kit.os_relpath(out, spec_dir)) / "sheets/lavender_mixed.png")
                            .as_posix(), "x": i * 16, "y": 0, "w": 1, "h": 1,
                            "banks": sorted({pk.banks[p][0] for row in pals for p in row}),
                            "tileset": "secondary", **entry})
        Image.fromarray(canvas, "RGBA").save(out / "sheets/lavender_mixed.png")

    # a character for each block
    legend, letter = {}, {}
    for (x, y), name in sorted(names.items(), key=lambda kv: (kv[0][1], kv[0][0])):
        if name not in letter:
            letter[name] = LETTERS[len(letter)]
            slate_under = name.startswith("slate_") or (blocks[name][2].get("ground", "").startswith("slate_"))
            legend[letter[name]] = {"name": name, "joins": "="} if slate_under else name
        g[y][x] = letter[name]
    uses_new = any(p == "lavender_town" for idx, pals, e in blocks.values() for row in pals for p in row)
    return {"legend": legend, "entries": entries, "solid": {letter[n] for n in solid},
            "palette": NEW_PALETTE if uses_new else None}


def _recipe_rail(mask: int) -> str:
    if "railing/autotile" not in _recipes:
        _recipes["railing/autotile"] = json.loads((PACK / "railing/autotile_recipes.json").read_text())
    return _recipes["railing/autotile"]["recipes"][str(mask)]["piece"]
