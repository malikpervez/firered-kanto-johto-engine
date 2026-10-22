"""The kit's trees, in their own palette (bank 3): the Sunlit Broadleaf pack (broadleaf/, native pixel art made
with another AI from a brief, v0.4; the kit keeps its trees, forest cells, palette and notes, not its previews and
sources). Every tree is 32x32, a 2x2 block cell on the even grid: forest cells in 47 shapes, each in three crown
variants that can be mixed (their outer five pixels are the same), and three standalone trees. Transparent pixels
show the ground under them. The bushes are its companion pack's (broadleaf/bushes/, Sunlit Broadleaf Bush Pack
v0.2): three 16x16 shrubs in the same palette that can be mixed in any order. make_art.py puts them on the "trees"
sheet."""
from pathlib import Path

import numpy as np

import autotile

HERE = Path(__file__).resolve().parent / "broadleaf"
VARIANTS = ("a", "b", "c")
STANDALONE = {"round_tree": "round_crown", "offset_tree": "offset_crown", "broad_tree": "broad_crown"}


def _palette() -> list[tuple[int, int, int]]:
    out = []
    for line in (HERE / "palette.gpl").read_text().splitlines():
        parts = line.split()
        if len(parts) >= 3 and all(p.isdigit() for p in parts[:3]):
            out.append(tuple(int(p) for p in parts[:3]))
    return out[:16]


PT = _palette()  # index 0 is transparent


def forest(mask: int = 15, corners: int = 0, variant: str = "a") -> np.ndarray:
    """The forest cell whose neighbouring cells are forest at ``mask`` (1 north, 2 east, 4 south, 8 west, as pae map
    paint counts them), with inside corners ``corners`` (1 NE, 2 SE, 4 SW, 8 NW: both sides forest, the diagonal
    not). The pack numbers its shapes by the neighbours outside the forest instead, diagonals from 16."""
    shape = (~mask & 15) | (corners << 4)
    return autotile.load(HERE / "forest" / variant / f"mask_{shape:03d}.png", PT)


def tree(name: str) -> np.ndarray:
    """A standalone tree (a name in ``STANDALONE``)."""
    return autotile.load(HERE / "trees" / f"{STANDALONE[name]}.png", PT)


BUSHES = ("bush_a", "bush_b", "bush_c")


def bush(name: str) -> np.ndarray:
    """A bush (a name in ``BUSHES``), one solid block."""
    return autotile.load(HERE / "bushes" / f"{name}.png", PT)
