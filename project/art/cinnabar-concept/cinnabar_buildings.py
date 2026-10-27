"""Cinnabar's own buildings, made from packs drawn for other towns:
- the Pokémon Lab: Oak's lab as Pallet draws it (pallet-concept/make_art.py `lab()`), in its own palette; its door is
  pae's panel door, as Pallet's is;
- Blaine's Gym: Pewter's Gym recoloured in the volcano's reds and ochres (every colour's hue turned to fire, the
  stone warmed), its door frames recoloured the same;
- the burned Pokémon Mansion: Celadon's hotel charred (its colours greyed and darkened, soot over the walls), its
  door frames charred the same.

Each function writes buildings/<name>/ (the image, its door frames when it has them, the json) and returns the
folder.
"""
import colorsys
import json
import sys
from pathlib import Path

import numpy as np
from PIL import Image

HERE = Path(__file__).resolve().parent
ART = HERE.parent
OUT = HERE / "buildings"


def _write(name, idx, pal, door=None, meta=None):
    folder = OUT / name
    folder.mkdir(parents=True, exist_ok=True)
    im = Image.fromarray(idx, "P")
    im.putpalette([v for c in pal for v in c] + [0] * (768 - 3 * len(pal)))
    im.save(folder / f"{name}.png", transparency=0)
    if door is not None:
        door.save(folder / f"{name}_door.png")
    (folder / f"{name}.json").write_text(json.dumps(meta, indent=2) + "\n")
    return folder


def _recolour(src: Path, name: str, f, note: str) -> Path:
    """The pack at ``src`` with every palette colour c turned to f(c), its door frames the same."""
    with Image.open(src / f"{src.name}.png") as im:
        idx, flat = np.array(im, np.uint8), im.getpalette()[:48]
    pal = [tuple(flat[i:i + 3]) for i in range(0, 48, 3)]
    new = [pal[0]] + [f(c) for c in pal[1:]]
    swap = dict(zip(pal, new))
    door = Image.open(src / f"{src.name}_door.png").convert("RGBA")
    d = np.array(door)
    out = d.copy()
    for old, nc in swap.items():
        hit = (d[..., :3] == old).all(axis=2) & (d[..., 3] > 0)
        out[hit, :3] = nc
    meta = json.loads((src / f"{src.name}.json").read_text())
    meta.update({"id": name, "name": name, "image": f"{name}.png",
                 "source": f"cinnabar-concept/cinnabar_buildings.py: {note}"})
    if isinstance(meta.get("door"), dict):
        meta["door"]["image"] = f"{name}_door.png"
    return _write(name, idx, new, Image.fromarray(out, "RGBA"), meta)


def _fire(c):
    r, g, b = (v / 255 for v in c)
    h, s, v = colorsys.rgb_to_hsv(r, g, b)
    if s < 0.12:            # the greys: warmed stone
        h, s = 0.05, max(s, 0.18)
    else:                   # the colours: the volcano's reds and ochres, by how light they are
        h = 0.0 if v < 0.55 else 0.07
        s = min(1.0, s * 1.15 + 0.1)
    return tuple(round(x * 255) for x in colorsys.hsv_to_rgb(h, s, v))


def _charred(c):
    r, g, b = (v / 255 for v in c)
    h, s, v = colorsys.rgb_to_hsv(r, g, b)
    return tuple(round(x * 255) for x in colorsys.hsv_to_rgb(h, s * 0.3, v * 0.72))


def gym() -> Path:
    return _recolour(ART / "pewter-concept/buildings/pewter_gym", "cinnabar_gym", _fire,
                     "Pewter's Gym recoloured for Blaine (its hues turned to fire)")


def mansion() -> Path:
    folder = _recolour(ART / "celadon-concept/buildings/hotel", "pokemon_mansion", _charred,
                       "Celadon's hotel, charred: the burned Pokémon Mansion")
    with Image.open(folder / "pokemon_mansion.png") as im:      # soot streaks up the walls from the windows
        idx, flat = np.array(im, np.uint8), im.getpalette()
    pal = [tuple(flat[i:i + 3]) for i in range(0, 48, 3)]
    darkest = min(range(1, 16), key=lambda i: sum(pal[i]))
    h, w = idx.shape
    for x in range(5, w - 5, 11):
        for y in range(h // 2, 6, -2):
            if idx[y, x] and idx[y, x] != darkest and (x * 7 + y) % 5 < 2:
                idx[y, x] = darkest
    im = Image.fromarray(idx, "P")
    im.putpalette(flat)
    im.save(folder / "pokemon_mansion.png", transparency=0)
    return folder


def lab() -> Path:
    sys.path.insert(0, str(ART / "kit"))
    sys.path.insert(0, str(ART / "pallet-concept"))
    import importlib.util
    spec = importlib.util.spec_from_file_location("pallet_make_art", ART / "pallet-concept/make_art.py")
    pallet = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(pallet)
    idx = pallet.lab()
    pal = list(pallet.P3) + [(0, 0, 0)] * (16 - len(pallet.P3))
    meta = {"schema_version": 2, "id": "cinnabar_lab", "type": "building", "image": "cinnabar_lab.png",
            "image_size_px": [idx.shape[1], idx.shape[0]], "block_size_px": 16,
            "footprint_blocks": {"width": idx.shape[1] // 16, "height": idx.shape[0] // 16}, "transparent_index": 0,
            "door_blocks": [[3, 4]], "name": "cinnabar_lab",
            "source": "cinnabar-concept/cinnabar_buildings.py: Oak's lab as pallet-concept/make_art.py draws it; "
                      "its door is pae's panel door"}
    return _write("cinnabar_lab", idx, pal, None, meta)


ALL = (gym, mansion, lab)

if __name__ == "__main__":
    for f in ALL:
        print(f())
