"""Kanto Town Props v0.1 (../packs/town_props_v0.1, a native pixel pack made with another AI from
Town_Props_v0.1_prompt.md): street furniture for any town or route. The pack has:
- a fountain (3x3, its water animated);
- benches (wood, facing each way, and stone);
- a flower tub, a litter bin, a statue, a fingerpost, a picnic table and a bike rack;
- footbridges (north-south and east-west, one and two blocks wide).

Every piece is drawn in one of the kit's own palettes: the water's (bank 1) or the wood's (bank 2). So a map needs no
bank of its own for them, and takes only the pieces it places into its own tileset.

``pieces(out, spec_dir, placed)`` puts the pieces a map places on sheets, with their spec entries and the fountain's
animation. ``placed`` maps each piece to its ground: one block name, or a list of them (row by row).
- Every block of a solid piece is solid; a bridge's blocks are walkable, laid over the water like the kit's dock.
- The pack's over_rows (art drawn over the player) aren't used: its solid pieces have nothing to walk behind, and a
  one-row bench drawn over the player would cover the head of anyone standing in front of it.
"""
import json
from pathlib import Path

import numpy as np
from PIL import Image

import kit

PACK = Path(__file__).resolve().parents[1] / "packs/town_props_v0.1"
PALETTE = {"kit_water": "water", "kit_wood": "wood"}  # the pack's palettes: the kit's, by name


def _catalogue() -> dict[str, tuple[Path, dict]]:
    out = {}
    for f in sorted(PACK.glob("*/*.json")):
        meta = json.loads(f.read_text())
        if "footprint_blocks" in meta:
            out[meta["id"]] = (f.parent, meta)
    return out


PIECES = _catalogue()


def frames(name: str) -> list[np.ndarray]:
    """A piece's pictures as the kit palette's indices: one, or the fountain's four frames."""
    folder, meta = PIECES[name]
    pal = kit.PALS[PALETTE[meta["palette"]]]
    out = []
    for rel in meta["frames"]:
        with Image.open(folder / rel) as im:
            flat = im.getpalette()[:48]
            assert [tuple(flat[i:i + 3]) for i in range(3, 48, 3)] == [tuple(c) for c in pal[1:]], \
                f"{rel}: not in the kit's {meta['palette']} palette"
            out.append(np.array(im, np.uint8))
    return out


def pieces(out: Path, spec_dir: Path, placed: dict[str, str | list[str]]) -> tuple[list[dict], list[dict]]:
    """The spec entries for the pieces ``placed`` (name -> ground), and the animations they need."""
    entries, animations = [], []
    rel = Path(kit.os_relpath(out, spec_dir))
    still = {}
    for name, ground in placed.items():
        meta = PIECES[name][1]
        fw, fh = meta["footprint_blocks"]["width"], meta["footprint_blocks"]["height"]
        entry = {"tileset": "secondary", "ground": ground, "solid": bool(meta["solid_blocks"])}
        if meta["solid_blocks"] and meta["walkable_blocks"]:
            entry["open"] = [f"{x},{y}" for x, y in meta["walkable_blocks"]]
        pics = frames(name)
        pal = PALETTE[meta["palette"]]
        assert pics[0].shape == (fh * 16, fw * 16), f"{name}: its picture isn't its footprint"
        if len(pics) > 1:  # animated: its own sheet, every metatile drawn from it animating
            sh = kit.Sheet(f"prop_{name}", kit.PALS[pal], kit.BANK[pal], out, spec_dir, cols=fw)
            sh.add(name, pics[0], **entry)
            entries += sh.write([[p] for p in pics[1:]])
            animations.append({"name": "".join(w.title() for w in name.split("_")),
                               "image": (rel / f"sheets/prop_{name}.png").as_posix(),
                               "frames": [(rel / f"sheets/prop_{name}_f{k}.png").as_posix()
                                          for k in range(1, len(pics))],
                               "speed": meta["frame_speed"]})
        else:
            still.setdefault(pal, []).append((name, pics[0], entry))
    for pal, items in still.items():
        sh = kit.Sheet(f"props_{pal}", kit.PALS[pal], kit.BANK[pal], out, spec_dir, cols=8)
        for name, pic, entry in items:
            sh.add(name, pic, dedupe=True, **entry)
        entries += sh.write()
    return entries, animations
