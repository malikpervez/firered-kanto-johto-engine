"""Route 16's own building, drawn here: the Cycling Road gatehouse, a gatehouse set across the road, its doorways at
its two ends (the left one entered walking east, the right one walking west), as its inside has its doors on its west
and east walls. It is in Saffron's buildings' palette (saffron-concept/saffron_buildings.py: stone and slate), and
drawn on the 16-pixel grid. The route has two of it: the upper hall's (on foot) and the lower hall's (by bike).

Each function writes buildings/<name>/<name>.png and <name>.json and returns the pack's folder.
"""
import json
import sys
from pathlib import Path

import numpy as np
from PIL import Image

HERE = Path(__file__).resolve().parent
sys.path.insert(0, str(HERE.parent / "celadon-concept"))
sys.path.insert(0, str(HERE.parent / "saffron-concept"))
from celadon_buildings import _outline, _window  # noqa: E402
from saffron_buildings import PAL, _slates  # noqa: E402

OUT = HERE / "buildings"


def _side_doorway(a: np.ndarray, x0: int, y0: int, opens_left: bool) -> None:
    """A doorway through the building's end, its block at (x0, y0): a stone lintel, the dark hall beyond, the
    threshold; its open side faces out of the building (left or right)."""
    a[y0:y0 + 16, x0:x0 + 16] = 10
    a[y0:y0 + 3, x0:x0 + 16] = 9                               # the lintel
    a[y0 + 3:y0 + 13, x0 + 2:x0 + 14] = 2                      # the hall beyond, lit at its far side
    if opens_left:
        a[y0 + 3:y0 + 13, x0 + 11:x0 + 14] = 4
    else:
        a[y0 + 3:y0 + 13, x0 + 2:x0 + 5] = 4
    a[y0 + 13:y0 + 16, x0:x0 + 16] = 9                         # the threshold
    a[y0 + 13, x0 + 2:x0 + 14] = 11


def gate() -> Path:
    """8x4: the Cycling Road gatehouse, across the road: a slate roof with a gold ridge over stone walls, a row of
    windows, and a doorway at each end of its bottom row (blocks 0 and 7), the hall through it."""
    w, h = 128, 64
    a = np.zeros((h, w), np.uint8)
    _slates(a, 0, 20, 0, w)
    a[0:2, 4:w - 4] = 13
    a[20:22, 0:w] = 2
    a[22:64, 0:w] = 10                                         # stone, laid in courses
    a[22:64, 0:w][7::8] = 9
    a[22:64, 0:2] = 11
    a[22:64, w - 2:w] = 9
    for bx in range(1, 7):
        _window(a, bx * 16 + 3, 26, 10, 12)
        if bx not in (3, 4):
            _window(a, bx * 16 + 3, 46, 10, 12)
    a[44:64, 48:80] = 12                                       # the guard's window on the hall, its sill
    a[46:60, 50:78] = 7
    a[46:52, 50:78] = 8
    a[60:64, 48:80] = 9
    _side_doorway(a, 0, 48, opens_left=True)
    _side_doorway(a, w - 16, 48, opens_left=False)
    _outline(a)
    folder = OUT / "cycling_gate"
    folder.mkdir(parents=True, exist_ok=True)
    im = Image.fromarray(a, "P")
    im.putpalette([v for c in PAL for v in c] + [0] * (768 - 48))
    im.save(folder / "cycling_gate.png", transparency=0)
    meta = {"schema_version": 2, "id": "cycling_gate", "type": "building", "image": "cycling_gate.png",
            "image_size_px": [w, h], "block_size_px": 16, "footprint_blocks": {"width": w // 16, "height": h // 16},
            "transparent_index": 0, "door_blocks": [[0, 3], [7, 3]], "name": "cycling_gate",
            "source": "drawn by route16-concept/route16_buildings.py; its doorways (0,3) and (7,3) are entered walking "
                      "east and west (arrow warps), and don't animate"}
    (folder / "cycling_gate.json").write_text(json.dumps(meta, indent=2) + "\n")
    return folder


ALL = (gate,)
