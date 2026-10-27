"""Indigo Plateau's building, made from a pack drawn for another town: the Pokémon League, Silph Co.'s tower from
Saffron (saffron-concept/buildings/silph_co) with its golden bands turned crimson and a Poké Ball in place of the
company's badge; its door frames recoloured the same.

``league()`` writes buildings/pokemon_league/ (the image, its door frames, the json) and returns the folder.
"""
import colorsys
import json
from pathlib import Path

import numpy as np
from PIL import Image

HERE = Path(__file__).resolve().parent
ART = HERE.parent
OUT = HERE / "buildings"
SRC = ART / "saffron-concept/buildings/silph_co"


def _crimson(c):
    r, g, b = (v / 255 for v in c)
    h, s, v = colorsys.rgb_to_hsv(r, g, b)
    if s > 0.3 and 0.05 < h < 0.2:  # the golds and ochres: the League's crimson
        h, s = 0.98, min(1.0, s * 1.1)
    return tuple(round(x * 255) for x in colorsys.hsv_to_rgb(h, s, v))


def _nearest(pal, rgb):
    return min(range(1, len(pal)), key=lambda i: sum((a - b) ** 2 for a, b in zip(pal[i], rgb)))


def league() -> Path:
    with Image.open(SRC / "silph_co.png") as im:
        idx, flat = np.array(im, np.uint8), im.getpalette()[:48]
    pal = [tuple(flat[i:i + 3]) for i in range(0, 48, 3)]
    new = [pal[0]] + [_crimson(c) for c in pal[1:]]
    # the badge on the top band (its colours are the band's own and none of the walls'): a Poké Ball in its place
    band = idx[8:40, :]
    base = int(np.bincount(band[band > 0]).argmax())
    logo = np.argwhere((band > 0) & (band != base))
    (y0, x0), (y1, x1) = logo.min(0), logo.max(0)
    y0, y1 = y0 + 8, y1 + 8
    idx[y0:y1 + 1, x0:x1 + 1] = base
    red, white, dark = _nearest(new, (200, 40, 48)), _nearest(new, (248, 248, 240)), _nearest(new, (24, 24, 32))
    cy, cx, rad = (y0 + y1) / 2, (x0 + x1) / 2, 7.5  # a ball 15 pixels across, ringed in white on the band
    for y in range(y0, y1 + 1):
        for x in range(x0, x1 + 1):
            d = ((y - cy) ** 2 + (x - cx) ** 2) ** 0.5
            if d <= rad + 1:
                idx[y, x] = white if d > rad else dark if d > rad - 1 or abs(y - cy) < 1 else (red if y < cy else white)
            if d <= 2.2:
                idx[y, x] = white if d <= 1.2 else dark
    folder = OUT / "pokemon_league"
    folder.mkdir(parents=True, exist_ok=True)
    out = Image.fromarray(idx, "P")
    out.putpalette([v for c in new for v in c] + [0] * (768 - 48))
    out.save(folder / "pokemon_league.png", transparency=0)
    door = np.array(Image.open(SRC / "silph_co_door.png").convert("RGBA"))
    recoloured = door.copy()
    for old, nc in zip(pal, new):
        hit = (door[..., :3] == old).all(axis=2) & (door[..., 3] > 0)
        recoloured[hit, :3] = nc
    Image.fromarray(recoloured, "RGBA").save(folder / "pokemon_league_door.png")
    meta = json.loads((SRC / "silph_co.json").read_text())
    meta.update({"id": "pokemon_league", "name": "pokemon_league", "image": "pokemon_league.png",
                 "source": "indigo-concept/indigo_buildings.py: Silph Co.'s tower, its golds turned crimson, a Poké "
                           "Ball for its badge"})
    if isinstance(meta.get("door"), dict):
        meta["door"]["image"] = "pokemon_league_door.png"
    (folder / "pokemon_league.json").write_text(json.dumps(meta, indent=2) + "\n")
    return folder


ALL = (league,)

if __name__ == "__main__":
    for f in ALL:
        print(f())
