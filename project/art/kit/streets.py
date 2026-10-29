"""Kanto Street Textures v0.3 (../packs/streets_v0.3, a native pixel pack made with another AI from
Street_Textures_v0.1_prompt.md): the city streets every map can use, in the kit's ground palette (bank 0).

- asphalt: the road. Its edges (N, E, ...: lawn outside on that side) are see-through outside the road, so a block
  shows its ground there.
- pavement: concrete slabs one step above the road, its kerb in its edges. The kit has it twice: on grass (``pavement``,
  for a park's edge) and on asphalt (``kerb``, for a street's: the road shows outside the kerb).
- crossing: zebra stripes (``road_EW`` for a road running east-west) with their ends, and the dropped kerbs.
- details: a manhole, storm drains, tactile paving and a tree grate.

Every block is put together the pack's way (its ``autotile_recipes.json``): each 8x8 quarter copied from a named
piece, for every neighbour mask and inside corner, so no block draws pixels the pack doesn't have. The pack's palette
(``road_existing.gpl``) is the kit's ground palette in another order; pieces are read by colour.
"""
import json
from pathlib import Path

import numpy as np

import autotile

PACK = Path(__file__).resolve().parents[1] / "packs/streets_v0.3"
QUARTERS = {"NW": np.s_[0:8, 0:8], "NE": np.s_[0:8, 8:16], "SW": np.s_[8:16, 0:8], "SE": np.s_[8:16, 8:16]}
# inside corners pae map paint asks for: a corner (1 NE, 2 SE, 4 SW, 8 NW) where both its sides are the material
SIDES_OF = {1: 1 | 2, 2: 2 | 4, 4: 4 | 8, 8: 8 | 1}
CORNERS = [(m, c) for m in range(16) for c in range(1, 16)
           if all(m & SIDES_OF[b] == SIDES_OF[b] for b in (1, 2, 4, 8) if c & b)]
LINES = ("dashed_H", "dashed_V", "dashed_H_boundary", "dashed_V_boundary",
         "lane_edge_N", "lane_edge_E", "lane_edge_S", "lane_edge_W")
JOINS = {"asphalt": [f"to_{m}_{d}" for m in ("cobble", "pavement") for d in "NESW"],
         "pavement": [f"to_{m}_{d}" for m in ("asphalt", "cobble", "dressed_stone") for d in "NESW"]}
CROSSING = ("road_EW", "road_NS", "end_N", "end_E", "end_S", "end_W",
            "dropped_kerb_N", "dropped_kerb_E", "dropped_kerb_S", "dropped_kerb_W")
DETAILS = ("manhole", "storm_drain_N", "storm_drain_E", "storm_drain_S", "storm_drain_W", "tactile_paving",
           "tree_grate")
_pieces: dict[tuple[str, str], np.ndarray] = {}
_recipes: dict[str, dict] = {}


def piece(surface: str, name: str, palette) -> np.ndarray:
    """A piece's 16x16 indices in ``palette``: from tiles/, or transitions/ for a ``to_*`` join."""
    if (surface, name) not in _pieces:
        sub = "transitions" if name.startswith("to_") else "tiles"
        _pieces[surface, name] = autotile.load(PACK / surface / sub / f"{name}.png", palette)
    return _pieces[surface, name]


def block(surface: str, mask: int, corners: int, palette) -> np.ndarray:
    """The block whose neighbours of the same material are ``mask`` (1 N, 2 E, 4 S, 8 W), with inside corners
    ``corners`` (1 NE, 2 SE, 4 SW, 8 NW), from the pack's recipe (its mask counts the outside: 1 N ... 8 W, and
    16 NE, 32 SE, 64 SW, 128 NW for the diagonals)."""
    if surface not in _recipes:
        _recipes[surface] = json.loads((PACK / surface / "autotile_recipes.json").read_text())["recipes"]
    recipe = _recipes[surface][str((~mask & 15) | corners << 4)]
    out = np.zeros((16, 16), np.uint8)
    for q, region in QUARTERS.items():
        out[region] = piece(surface, recipe[q]["piece"], palette)[QUARTERS[recipe[q]["quadrant"]]]
    return out
