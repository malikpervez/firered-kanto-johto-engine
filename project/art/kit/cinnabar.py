"""Kanto Cinnabar Island v0.1 (../packs/cinnabar_v0.1, a native pixel pack made with another AI from
Cinnabar_Island_v0.1_prompt.md): Cinnabar's own ground, rock and details.

- paving: dark basalt setts, repeating every block, for the town's streets and the lane to the harbour (in the pack's
  cinnabar_town palette, bank 12).
- ash: volcanic ash, the volcano island's ground (and under its rock); its second fill where nothing but ash is round it
  and (x + y) % 3 == 0, as the pack lays it.
- cliff: the volcano's basalt (a top in four phases, a two-block columnar face, the face's ends and the tops' junctions
  with it, the embered cap over the crater), laid block by block as the pack's placement plan records it for this
  island: it follows the pack's Rock & Cliff rules, and ``lay`` checks it covers the map's rock exactly.
- crater: cooling lava, its two fills by (x + y) % 2.
- details: a steam vent (animated), a lava rock and hot-spring steam (animated), each 1x1 and solid.

Everything but the paving is in the pack's cinnabar_volcano palette (bank 11, the kit rock's bank on this map). Both
new palettes carry the kit's lawn greens their edges need. A block's tiles are the pack's canonical 8x8s, each with its
flips (``tiles_8x8`` and ``flips_8x8`` in its recipe or piece); ``lay`` puts them on sheets for pae.
"""
import json
from pathlib import Path

import numpy as np
from PIL import Image

import kit

PACK = Path(__file__).resolve().parents[1] / "packs/cinnabar_v0.1"
BITS = {(0, -1): 1, (1, 0): 2, (0, 1): 4, (-1, 0): 8, (1, -1): 16, (1, 1): 32, (-1, 1): 64, (-1, -1): 128}
LETTERS = [chr(c) for c in range(0x1E00, 0x1F00)]  # the characters lay hands out (no map uses them)
VOLCANO_BANK, TOWN_BANK = 11, 12


def gpl(name: str) -> list[tuple[int, int, int]]:
    rows = [r.split() for r in (PACK / "palettes" / f"{name}.gpl").read_text().splitlines() if r.strip()[:1].isdigit()]
    return [tuple(int(v) for v in r[:3]) for r in rows[:16]]


PALETTES = {"cinnabar_volcano": (VOLCANO_BANK, gpl("cinnabar_volcano")), "cinnabar_town": (TOWN_BANK, gpl("cinnabar_town"))}
POOL = [np.array(t, np.uint8).reshape(8, 8) for t in json.loads((PACK / "tile_pool.json").read_text())["tiles"]]


def compose(tiles_8x8, flips_8x8) -> np.ndarray:
    """A picture (a block, or a piece of several) from the pack's canonical tiles and their flips."""
    out = np.zeros((8 * len(tiles_8x8), 8 * len(tiles_8x8[0])), np.uint8)
    for qy in range(len(tiles_8x8)):
        for qx in range(len(tiles_8x8[0])):
            t, f = POOL[tiles_8x8[qy][qx]], flips_8x8[qy][qx]
            if f["h"]:
                t = t[:, ::-1]
            if f["v"]:
                t = t[::-1]
            out[qy * 8:qy * 8 + 8, qx * 8:qx * 8 + 8] = t
    return out


def _pieces(surface: str) -> dict[str, dict]:
    return json.loads((PACK / surface / f"{surface}.json").read_text())["pieces"]


PIECES = {s: _pieces(s) for s in ("paving", "ash", "cliff", "crater", "details")}
RECIPES = {s: json.loads((PACK / s / "autotile_recipes.json").read_text())["recipes"] for s in ("paving", "ash")}
PLAN = json.loads((PACK / "previews/placement_plan.json").read_text())


def _check_pack() -> None:
    """Every piece's tiles and flips draw its picture exactly, in one palette."""
    for surface, pieces in PIECES.items():
        for name, p in pieces.items():
            with Image.open(PACK / surface / p["image"]) as im:
                assert im.mode == "P", f"{surface}/{name}: not indexed"
                want = np.array(im, np.uint8)
            assert np.array_equal(compose(p["tiles_8x8"], p["flips_8x8"]), want), f"{surface}/{name}: its tiles"
            assert {c for row in p["palettes_8x8"] for c in row} <= set(PALETTES), f"{surface}/{name}: its palette"


_check_pack()


def piece(surface: str, name: str) -> np.ndarray:
    p = PIECES[surface][name]
    return compose(p["tiles_8x8"], p["flips_8x8"])


def frames(name: str) -> list[np.ndarray]:
    """An animated detail's frames (its first is itself), and its speed."""
    p = PIECES["details"][name]
    out = []
    for fn in p["frames"]:
        with Image.open(PACK / "details/tiles" / fn) as im:
            out.append(np.array(im, np.uint8))
    assert np.array_equal(out[0], piece("details", name)), f"{name}: its first frame is itself"
    return out


def lay(g, *, paving: set, ash: set, rock: set, crater: set, level: set = frozenset(), kit_pieces: dict = None,
        lava_rocks=(), vents=(), spring_steam=(), out: Path, spec_dir: Path) -> dict:
    """Lay the pack into the plan ``g``: ``paving`` and ``ash`` (their cells), ``rock`` (the volcano's cells: the
    pack's placement plan must cover exactly these), ``crater`` (its cells, on the ash), the details on the ash or the
    lawn under them (``lava_rocks``, ``vents``, ``spring_steam``: cells), and ``kit_pieces`` (cell -> (name, picture,
    the kit palette it's in): a sign of the kit's, or another of its small pieces, standing on the paving or the ash,
    over the block there). ``level`` are cells the paving runs up to without an edge, as if they were paving (the
    buildings' fronts above it).

    Returns the "legend" for the characters it wrote, the spec "entries", the "solid" characters, the "palettes" (bank
    -> colours), the "animations" for the spec and the "ground": the block name at each cell it laid."""
    kit_pieces = kit_pieces or {}
    assert set(kit_pieces) <= paving | ash, "the kit's pieces stand on the paving or the ash"
    h, w = len(g), len(g[0])
    blocks: dict[str, tuple[np.ndarray, str, dict]] = {}  # name -> indices, palette, entry
    by_picture: dict[tuple, str] = {}
    names: dict[tuple[int, int], str] = {}

    def add(name: str, idx: np.ndarray, pal: str, **entry) -> str:
        key = (idx.tobytes(), pal, json.dumps(entry, sort_keys=True))
        if key in by_picture:  # the same block under another name: the first's
            return by_picture[key]
        blocks[name] = (idx, pal, entry)
        by_picture[key] = name
        return name

    def mask(x, y, inside) -> int:
        return sum(b for (dx, dy), b in BITS.items() if not inside(x + dx, y + dy))

    # the paving: its edge wherever the lawn is beside it
    for x, y in sorted(paving, key=lambda c: (c[1], c[0])):
        m = mask(x, y, lambda a, b: (a, b) in paving or (a, b) in level)
        r = RECIPES["paving"][str(m)]
        names[x, y] = add(f"basalt#{m}", compose(r["tiles_8x8"], r["flips_8x8"]), "cinnabar_town", ground="grass")
    # the ash: the same edge wherever the lawn is beside it; its second fill here and there where nothing else is
    for x, y in sorted(ash, key=lambda c: (c[1], c[0])):
        m = mask(x, y, lambda a, b: (a, b) in ash)
        if m == 0 and (x + y) % 3 == 0:
            idx, nm = piece("ash", "fill_2"), "ash_fill_2"
        else:
            r = RECIPES["ash"][str(m)]
            idx, nm = compose(r["tiles_8x8"], r["flips_8x8"]), f"ash#{m}"
        names[x, y] = add(nm, idx, "cinnabar_volcano", ground="grass")

    solid = set()
    anims = []

    def stand(name: str, x: int, y: int, idx: np.ndarray, pal: str) -> str:
        under = names.get((x, y), "grass")
        cell = add(f"{name}@{under}", idx, pal, ground=under, solid=True)
        names[x, y] = cell
        solid.add(cell)
        return cell

    # the volcano's rock, as the pack's plan lays it, over the ash under it
    plan = {tuple(c["block"]): c for c in PLAN["cliff"]}
    assert set(plan) == rock, f"the pack's cliff isn't the map's rock: {sorted(set(plan) ^ rock)[:6]}"
    assert tuple(PLAN["phase_origin"]) == (0, 0) and tuple(PLAN["map_blocks"]) == (w, h), "the pack's plan is another map"
    for (x, y), c in sorted(plan.items(), key=lambda kv: (kv[0][1], kv[0][0])):
        if "piece" in c:  # a half of the two-block face: the piece's own tiles and flips
            base, half = c["piece"].rsplit("_", 1)
            pic = piece("cliff", base)[:16] if half == "top" else piece("cliff", base)[16:]
            assert PIECES["cliff"][base]["tiles_8x8"][slice(0, 2) if half == "top" else slice(2, 4)] == c["tiles_8x8"]
            stand(f"basalt_{c['piece'].replace('/', '_')}", x, y, pic, "cinnabar_volcano")
        else:  # the rock's top: its recipe for this phase and mask, as the plan records it
            stand(f"basalt_rock_{c['phase']}#{c['mask']}", x, y, compose(c["tiles_8x8"], c["flips_8x8"]),
                  "cinnabar_volcano")
    for x, y in sorted(crater):
        stand(f"crater_{1 + (x + y) % 2}", x, y, piece("crater", f"fill_{1 + (x + y) % 2}"), "cinnabar_volcano")
    for x, y in sorted(lava_rocks):
        stand("lava_rock", x, y, piece("details", "lava_rock"), "cinnabar_volcano")
    for (x, y), (name, pic, kpal) in sorted(kit_pieces.items(), key=lambda kv: (kv[0][1], kv[0][0])):
        under = names[x, y]
        cell = f"{name}@{under}"
        blocks[cell] = (pic, f"kit_{kpal}", {"ground": under, "solid": True})
        names[x, y] = cell
        solid.add(cell)

    # the sheets, one for each bank; the ground first (what stands on it names it as its ground, and pae wants a
    # ground listed first)
    entries, by_pal = [], {}
    for name, (idx, pal, entry) in blocks.items():
        by_pal.setdefault(pal, []).append((name, idx, entry))
    banks = dict(PALETTES, **{f"kit_{p}": (kit.BANK[p], kit.PALS[p]) for p in kit.BANK})
    ground_first = sorted(by_pal.items(), key=lambda kv: (kv[0].startswith("kit_"), kv[0]))
    for pal, cells in ground_first:
        bank, colours = banks[pal]
        flat = [c for c in cells if c[2].get("ground") == "grass"]
        rest = [c for c in cells if c[2].get("ground") != "grass"]
        for part, items in (("ground", flat), ("on", rest)):
            if not items:
                continue
            sheet = pal if pal.startswith("cinnabar_") else f"cinnabar_{pal}"
            sh = kit.Sheet(f"{sheet}_{part}", colours, bank, out, spec_dir, cols=8)
            for name, idx, entry in items:
                sh.add(name, idx, tileset="secondary", dedupe=True, **entry)
            entries += sh.write()

    # the animated details: a sheet each (every metatile drawn from it animates), one block for each ground under one
    rel = Path(kit.os_relpath(out, spec_dir))
    for detail, cells, anim in (("steam_vent_f1", vents, "CinnabarSteamVent"),
                                ("hot_spring_steam_f1", spring_steam, "CinnabarSpringSteam")):
        if not cells:
            continue
        pics = frames(detail)
        grounds = {}
        for x, y in sorted(cells):
            grounds.setdefault(names.get((x, y), "grass"), []).append((x, y))
        bank, colours = PALETTES["cinnabar_volcano"]
        sheet = f"cinnabar_{detail.rsplit('_f', 1)[0]}"
        sh = kit.Sheet(sheet, colours, bank, out, spec_dir, cols=8)
        for under, at in grounds.items():
            nm = f"{detail.rsplit('_f', 1)[0]}@{under}"
            sh.add(nm, pics[0], tileset="secondary", ground=under, solid=True)
            for xy in at:
                names[xy] = nm
            solid.add(nm)
        entries += sh.write([[p] * len(grounds) for p in pics[1:]])
        anims.append({"name": anim, "image": (rel / f"sheets/{sheet}.png").as_posix(),
                      "frames": [(rel / f"sheets/{sheet}_f{k}.png").as_posix() for k in range(1, len(pics))],
                      "speed": PIECES["details"][detail]["frame_speed"]})

    # a character for each block
    legend, letter = {}, {}
    for (x, y), name in sorted(names.items(), key=lambda kv: (kv[0][1], kv[0][0])):
        if name not in letter:
            letter[name] = LETTERS[len(letter)]
            legend[letter[name]] = name
        g[y][x] = letter[name]
    return {"legend": legend, "entries": entries, "solid": {letter[n] for n in solid},
            "palettes": {bank: colours for bank, colours in PALETTES.values()}, "animations": anims,
            "ground": dict(names)}
