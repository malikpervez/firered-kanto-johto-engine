"""Buildings from native pixel packs (made with another AI from a brief): each in a folder of its own with
<name>.png (indexed, its palette in the PNG, index 0 transparent), <name>_door.png (three drawn door frames, 48x32:
the door block and the block above it) and <name>.json (footprint, door block, solid blocks).

The kit's own are in buildings/: the Pokémon Center and the Poké Mart, which every town shares. A town's own
buildings are in its folder and load the same way. The remakes of the buildings Claude first drew in code (the Gyms,
the League, Celadon's and Saffron's buildings, the gates...) are one pack, ../packs/buildings_v0.3 (REMAKES); scenery
without a door (the windmill, Route 1's shelter and arch, the Magnet Train station) has no door block.
"""
import json
from dataclasses import dataclass
from pathlib import Path

import numpy as np
from PIL import Image

HERE = Path(__file__).resolve().parent / "buildings"
REMAKES = HERE.parents[1] / "packs/buildings_v0.3/buildings"


@dataclass
class Building:
    name: str
    idx: np.ndarray  # palette indices, 16 px a block
    palette: list[tuple[int, int, int]]  # 16 colours, index 0 transparent
    door: tuple[int, int] | None  # the door block, in blocks from the building's top-left (None: no door)
    door_frames: Path

    def entry(self) -> dict:
        """The spec entry's keys for it: solid but its door, which animates."""
        d = f"{self.door[0]},{self.door[1]}"
        return {"ground": "grass", "solid": True, "open": [d], "behaviors": {d: "MB_ANIMATED_DOOR"}}


def load(folder: Path) -> Building:
    folder = Path(folder)
    name = folder.name
    meta = json.loads((folder / f"{name}.json").read_text())
    with Image.open(folder / f"{name}.png") as im:
        if im.mode != "P":
            raise SystemExit(f"{folder}/{name}.png is not indexed")
        idx = np.array(im, np.uint8)
        flat = im.getpalette()[:48]
    pal = [tuple(flat[i:i + 3]) for i in range(0, 48, 3)]
    fp = meta["footprint_blocks"]
    if idx.shape != (fp["height"] * 16, fp["width"] * 16):
        raise SystemExit(f"{name}: the picture is not its footprint ({fp['width']}x{fp['height']} blocks)")
    door = tuple(meta["door_block"]) if meta.get("door_block") else None
    return Building(name, idx, pal, door, folder / f"{name}_door.png")


CENTER = load(HERE / "pokemon_center")
MART = load(HERE / "poke_mart")


def recompose(idx: np.ndarray, rows, cols) -> np.ndarray:
    """A new picture from a building's own 8x8 cells: row ``i``, column ``j`` of it is the cell at (``rows[i]``,
    ``cols[j]``) of ``idx``. Every tile in it is one the building already has, so it costs its tileset no tiles
    (its blocks are new). Seamless where each step between neighbouring cells is one the building takes too."""
    if len(rows) % 2 or len(cols) % 2:
        raise SystemExit("a recomposed building is whole blocks: an even number of 8 px rows and columns")
    out = np.zeros((len(rows) * 8, len(cols) * 8), np.uint8)
    for i, r in enumerate(rows):
        for j, c in enumerate(cols):
            out[i * 8:i * 8 + 8, j * 8:j * 8 + 8] = idx[r * 8:r * 8 + 8, c * 8:c * 8 + 8]
    return out


def recolour(palette, changes: dict[int, tuple[int, int, int]]) -> list[tuple[int, int, int]]:
    """A palette with some of its colours changed. Its pictures keep their indices, so their tiles are the same tiles
    in another bank: the colours must stay distinct, or the tileset build would merge two indices."""
    out = list(palette)
    for i, c in changes.items():
        out[i] = tuple(c)
    if len(set(out[1:])) != len(out) - 1:
        raise SystemExit("a recolour gives two indices the same colour")
    return out
