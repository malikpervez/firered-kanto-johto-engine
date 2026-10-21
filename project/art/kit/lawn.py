"""The kit's lawn, from a native pixel pack (lawn/<option>/, made with another AI from a brief): four plain lawn
tiles and one with daisies, 16x16, that sit seamlessly beside each other in any order, so a map scatters them.

Each option brings its own six greens (darkest first), which take the ground palette's six green slots (bank 0):
the ledges, steps, lily pads and reeds drawn in those slots take the option's greens with them.
"""
from pathlib import Path

import numpy as np
from PIL import Image

HERE = Path(__file__).resolve().parent / "lawn"
PLAIN = ("lawn_a", "lawn_b", "lawn_c", "lawn_d")
NAMES = PLAIN + ("lawn_flowers",)


def greens(option: str) -> list[tuple[int, int, int]]:
    """The option's six greens, darkest first (the first six colours of its palette.gpl)."""
    out = []
    for line in (HERE / option / "palette.gpl").read_text().splitlines():
        parts = line.split()
        if len(parts) >= 3 and all(p.isdigit() for p in parts[:3]):
            out.append(tuple(int(p) for p in parts[:3]))
    return out[:6]


def tiles(option: str, palette: list[tuple[int, int, int]]) -> dict[str, np.ndarray]:
    """The option's tiles as indices into ``palette`` (the ground palette, with the option's greens)."""
    lut = {c: i for i, c in enumerate(palette) if i}
    out = {}
    for name in NAMES:
        with Image.open(HERE / option / f"{name}.png") as im:
            a = np.array(im.convert("RGB"))
        t = np.zeros(a.shape[:2], np.uint8)
        for y in range(a.shape[0]):
            for x in range(a.shape[1]):
                c = tuple(int(v) for v in a[y, x])
                if c not in lut:
                    raise SystemExit(f"lawn/{option}/{name}.png: {c} is not in the ground palette")
                t[y, x] = lut[c]
        out[name] = t
    return out
