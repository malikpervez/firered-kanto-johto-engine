"""Kanto Harbour Textures v0.1 (../packs/harbour_v0.1, a native pixel pack made with another AI from
Harbour_Textures_v0.1_prompt.md): a port's ground.

- setts: granite setts laid in fans, a 32x32 repeat (the four phase pieces "large_NW" ... "large_SE"), for a harbour
  square; with joins to the cobble and the pavement.
- quay: big flagstones for a promenade along the water.
- quay_wall: the harbour wall, over two blocks: the coping on the edge of the land block, and the wall's face on the
  water block beside it, see-through below the face so the map's own animated water shows.
- details: bollards, rope, a drain cover and a lifebuoy.

Every block is put together the pack's way, each 8x8 quarter copied from a named piece by the recipe for its
neighbours: 1 N, 2 E, 4 S, 8 W, 16 NE, 32 SE, 64 SW, 128 NW (for the setts and the flags the neighbours that aren't
them; for the coping the water; for the wall the land and the docks). The setts and the flags are in the kit's ground
palette (bank 0), the wall and the bollards in its water palette (bank 1), the rope and the lifebuoy in its wood
palette (bank 2), so a map needs no bank of its own for any of it.

A map lays them with ``lay``: its square's and its promenade's blocks, the wall round its water, the details; it gets
back the legend, the spec entries and what each block of them shows (for what stands on them).
"""
import json
from pathlib import Path

import numpy as np
from PIL import Image

import kit

PACK = Path(__file__).resolve().parents[1] / "packs/harbour_v0.1"
PALETTE = {"kit_ground": "ground", "kit_water": "water", "kit_wood": "wood"}  # the pack's palettes: the kit's
FILES = {"kit_ground": "road_existing.gpl", "kit_water": "kit_water.gpl", "kit_wood": "kit_wood.gpl"}
QUARTERS = {"NW": np.s_[0:8, 0:8], "NE": np.s_[0:8, 8:16], "SW": np.s_[8:16, 0:8], "SE": np.s_[8:16, 8:16]}
BITS = {(0, -1): 1, (1, 0): 2, (0, 1): 4, (-1, 0): 8, (1, -1): 16, (1, 1): 32, (-1, 1): 64, (-1, -1): 128}
PHASES = {(0, 0): "NW", (1, 0): "NE", (0, 1): "SW", (1, 1): "SE"}  # the setts' 2x2 repeat, from its origin
LETTERS = [chr(c) for c in range(0x100, 0x180)]  # the map characters lay hands out (no map uses them)


def _gpl(name: str) -> list[tuple[int, int, int]]:
    rows = [r.split() for r in (PACK / "palettes" / name).read_text().splitlines() if r.strip()[:1].isdigit()]
    return [tuple(int(v) for v in r[:3]) for r in rows[:16]]


def _catalogue() -> dict[tuple[str, str], tuple[Path, list]]:
    out = {}
    for surface in ("setts", "quay", "quay_wall", "details"):
        meta = json.loads((PACK / surface / f"{surface}.json").read_text())
        for p in meta.get("tiles", []) + meta.get("transitions", []):
            if isinstance(p, dict):
                out[surface, p["name"]] = (PACK / surface / p["image"], p["palettes_8x8"])
    return out


PIECES = _catalogue()
_pictures: dict[tuple[str, str], tuple[np.ndarray, list]] = {}
_recipes: dict[str, dict] = {}


def picture(surface: str, name: str) -> tuple[np.ndarray, list[list[str]]]:
    """A piece's 16x16 indices, each quarter in its own palette (the kit's, its order), and those palettes' names."""
    if (surface, name) not in _pictures:
        path, pals = PIECES[surface, name]
        with Image.open(path) as im:
            raw = np.array(im, np.uint8)
        out = np.zeros_like(raw)
        for (qy, qx), q in zip(((0, 0), (0, 1), (1, 0), (1, 1)), QUARTERS.values()):
            src, dst = _gpl(FILES[pals[qy][qx]]), kit.PALS[PALETTE[pals[qy][qx]]]
            lut = {i: dst.index(c) for i, c in enumerate(src) if i}  # by colour: the ground's order differs
            out[q] = np.vectorize(lambda v: lut[v] if v else 0)(raw[q])
        _pictures[surface, name] = (out, pals)
    return _pictures[surface, name]


def recipe(surface: str, mask: int, kind: str = "autotile", phase: str | None = None) -> np.ndarray:
    """The block for ``mask`` from the pack's recipes: ``kind`` "autotile" (the setts and the flags: the neighbours
    that aren't them; the coping: the water), "water" (the wall: the land and docks round a water block); the setts by
    their ``phase``. Its quarters all in one palette."""
    key = f"{surface}/{kind}"
    if key not in _recipes:
        fn = {"autotile": "autotile_recipes.json", "water": "water_recipes.json", "phase": "phase_recipes.json"}[kind]
        _recipes[key] = json.loads((PACK / surface / fn).read_text())
    r = _recipes[key]["recipes_by_phase"][phase] if kind == "phase" else _recipes[key]["recipes"]
    out, pals = np.zeros((16, 16), np.uint8), set()
    for q, region in QUARTERS.items():
        idx, pal = picture(surface, r[str(mask)][q]["piece"])
        src = r[str(mask)][q]["quadrant"]
        out[region] = idx[QUARTERS[src]]
        qy, qx = divmod(list(QUARTERS).index(src), 2)
        pals.add(pal[qy][qx])
    assert len(pals) == 1, f"{surface} {mask}: quarters in more than one palette"
    return out


def lay(g, squares: list[tuple[set, tuple[int, int]]], quay: set, *, out: Path, spec_dir: Path, water: str = "~vrO",
        dock: str = "dJGYBc", cobble: str = "=", street: set = frozenset(), details=(), ring=None,
        ladder=None) -> dict:
    """Lay the harbour into the plan ``g``: the ``squares`` in setts (each its cells, and the block its pattern starts
    from), ``quay`` (the promenade's cells, and what stands on them), the wall on every water block (``water``'s
    characters) beside land or a dock (``dock``'s), the coping on every flagstone beside water; ``details`` ((name, x,
    y)) on the flags, the coping (drawn into it, as a block holds two layers) or a dock; the mooring ring in the coping
    at ``ring``, the ladder down the wall at ``ladder``. A setts block takes the join to the cobble (``cobble``) north
    of it, or to the pavement of ``street`` north or south of it; the setts run on into the top half of a flagstone
    south of them (its pattern carried on: a square starts its pattern so that the flags' row is a top one).

    Returns the "legend" for the characters it wrote, the spec "entries" (to go after the kit's), the "solid" and the
    "water" characters, and the "ground" each setts and flags block shows (by cell), for what stands on them."""
    h, w = len(g), len(g[0])
    phase_of = {(x, y): PHASES[(x - ox) % 2, (y - oy) % 2] for cells, (ox, oy) in squares for x, y in cells}
    setts = set(phase_of)
    under = {(x, y + 1): PHASES[(x - ox) % 2, (y + 1 - oy) % 2] for cells, (ox, oy) in squares for x, y in cells
             if (x, y + 1) in quay}  # flagstones the setts run into
    detail_at = {(x, y): name for name, x, y in details}
    on_dock = {xy for xy in detail_at if g[xy[1]][xy[0]] in dock}

    def at(x, y):
        return g[y][x] if 0 <= x < w and 0 <= y < h else None

    def wet(x, y):  # water (off the map counts as water: the sea goes on)
        return at(x, y) is None or at(x, y) in water and (x, y) not in setts | quay

    def mask(x, y, outside) -> int:
        return sum(b for (dx, dy), b in BITS.items() if outside(x + dx, y + dy))

    names: dict[tuple[int, int], str] = {}
    sheets = {pal: kit.Sheet(f"harbour_{pal}", kit.PALS[pal], kit.BANK[pal], out, spec_dir)
              for pal in ("ground", "water", "wood")}
    made = set()

    def add(pal, name, idx, **entry):
        if name not in made:
            made.add(name)
            sheets[pal].add(name, idx, tileset="secondary", dedupe=True, **entry)

    ground = {}
    for x, y in sorted(setts):
        phase = phase_of[x, y]
        if at(x, y - 1) == cobble and (x, y - 1) not in setts:
            name = f"setts_{phase}_to_cobble_N"
            add("ground", name, picture("setts", f"to_cobble_N_{phase}")[0], ground="grass")
        elif (x, y + 1) in street:
            name = f"setts_{phase}_to_pavement_S"
            add("ground", name, picture("setts", f"to_pavement_S_{phase}")[0], ground="grass")
        elif (x, y - 1) in street:
            name = f"setts_{phase}_to_pavement_N"
            add("ground", name, picture("setts", f"to_pavement_N_{phase}")[0], ground="grass")
        else:
            m = mask(x, y, lambda a, b: at(a, b) is not None and (a, b) not in setts and (a, b) not in under)
            name = f"setts_{phase}#{m}"
            add("ground", name, recipe("setts", m, "phase", phase), ground="grass")
        names[x, y] = ground[x, y] = name
    for (x, y), phase in sorted(under.items()):  # the pack's join is the NW phase's: the NE one's from its pieces
        assert phase in ("NW", "NE"), f"({x},{y}): the setts' pattern must start a row above the flags"
        idx = picture("quay", "to_setts_N")[0].copy()
        idx[:8] = picture("setts", f"large_{phase}")[0][:8]
        names[x, y] = ground[x, y] = f"quay_to_setts_{phase}"
        add("ground", names[x, y], idx, ground="grass")
    for x, y in sorted(quay - set(under)):  # the flags: their edges where lawn (or anything but water, a dock or
        # flags) is beside
        m = mask(x, y, lambda a, b: at(a, b) is not None and (a, b) not in quay and not wet(a, b)
                 and at(a, b) not in dock)
        flags = f"quay#{m}"
        add("ground", flags, recipe("quay", m), ground="grass")
        names[x, y] = ground[x, y] = flags
        c = mask(x, y, wet)  # the coping, where water is beside
        if c:
            cope = picture("quay_wall", "edge_S_ring")[0] if (x, y) == ring else recipe("quay_wall", c)
            assert (x, y) != ring or c & 15 == 4, "the ring goes in a coping with water to the south only"
            names[x, y] = f"{flags}+coping#{c}" + ("_ring" if (x, y) == ring else "")
            add("water", names[x, y], cope, ground=flags)
    for y in range(h):  # the wall: every water block beside land or a dock
        for x in range(w):
            if not wet(x, y) or at(x, y) == "O":
                continue
            m = mask(x, y, lambda a, b: at(a, b) is not None and not wet(a, b))
            if not m:
                continue
            if (x, y) == ladder:
                assert m & 15 == 1, "the ladder goes down a wall with land to the north only"
                names[x, y] = "quay_wall_ladder"
                add("water", names[x, y], picture("quay_wall", "wall_S_ladder")[0], ground="pond#15",
                    behavior="MB_POND_WATER", elevation=1)
            else:
                names[x, y] = f"quay_wall#{m}"
                add("water", names[x, y], recipe("quay_wall", m, "water"), ground="pond#15",
                    behavior="MB_POND_WATER", elevation=1)
    solid = set()
    mixed = []
    for (x, y), name in sorted(detail_at.items()):
        idx, pals = picture("details", name)
        flat = {p for row in pals for p in row}
        is_solid = name != "harbour_drain"
        if (x, y) in on_dock:  # on the planks: the dock's block for its neighbours, as pae map paint picks it
            dm = sum(b for (dx, dy), b in BITS.items() if b < 16 and (at(x + dx, y + dy) is None
                                                                      or at(x + dx, y + dy) in "dJGY"
                                                                      or (x + dx, y + dy) in on_dock))
            base = f"dock#{dm}"
        else:
            assert (x, y) in quay, f"{name} at ({x},{y}) stands on neither the flags nor a dock"
            base = ground[x, y]
            if names[x, y] != base:  # on the coping: drawn into it, in its palette
                assert flat == {"kit_water"}, f"{name} at ({x},{y}): only a water-palette detail goes on the coping"
                cope = names[x, y]
                c = int(cope.split("coping#")[1].split("_")[0])
                idx = np.where(idx > 0, idx, recipe("quay_wall", c))
        cell = f"{name}@{x},{y}"
        names[x, y] = cell
        entry = dict(ground=base, solid=is_solid)
        if len(flat) == 1:
            add(PALETTE[flat.pop()], cell, idx, **entry)
        else:  # quarters in two palettes (the bollard's head water, its rope wood): an image of its own
            mixed.append((cell, idx, pals, entry))
        if is_solid:
            solid.add(cell)
    entries = []
    for pal in ("ground", "water", "wood"):
        if sheets[pal].cells:
            entries += sheets[pal].write()
    if mixed:
        canvas = np.zeros((16, 16 * len(mixed), 4), np.uint8)
        for i, (cell, idx, pals, entry) in enumerate(mixed):
            for (qy, qx), q in zip(((0, 0), (0, 1), (1, 0), (1, 1)), QUARTERS.values()):
                canvas[:, i * 16:(i + 1) * 16][q] = kit.rgba(idx[q], kit.PALS[PALETTE[pals[qy][qx]]])
            entries.append({"name": cell, "image": (Path(kit.os_relpath(out, spec_dir)) / "sheets/harbour_mixed.png")
                            .as_posix(), "x": i * 16, "y": 0, "w": 1, "h": 1,
                            "banks": sorted({kit.BANK[PALETTE[p]] for row in pals for p in row}),
                            "tileset": "secondary", **entry})
        Image.fromarray(canvas, "RGBA").save(out / "sheets/harbour_mixed.png")
    # a character for each block
    legend, letter = {}, {}
    for (x, y), name in sorted(names.items(), key=lambda kv: (kv[0][1], kv[0][0])):
        if name not in letter:
            letter[name] = LETTERS[len(letter)]
            joins = ("~" if name.startswith("quay_wall") else "d" if (x, y) in on_dock
                     else cobble if name.endswith("_to_cobble_N") else None)
            legend[letter[name]] = {"name": name, "joins": joins} if joins else name
        g[y][x] = letter[name]
    return {"legend": legend, "entries": entries, "ground": ground,
            "solid": {letter[n] for n in solid}, "water": {letter[n] for n in names.values() if n.startswith("quay_wall")}}
