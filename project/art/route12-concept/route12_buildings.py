"""Route 12's own building: its north gatehouse, a gatehouse you walk through from north to south, put together from
Saffron's two gatehouse packs (saffron-concept/saffron_buildings.py): the back of `saffron_gate_back` (its roof's
back slope with the open doorway in it, entered walking south) over the front of `saffron_gate` (its stone south face
with the double door). In Saffron's buildings' palette.

`gate()` writes buildings/route12_gate/ (the image, the double door's frames copied from `saffron_gate`, the json)
and returns the folder.
"""
import json
import shutil
from pathlib import Path

import numpy as np
from PIL import Image

HERE = Path(__file__).resolve().parent
SB = HERE.parent / "saffron-concept/buildings"
OUT = HERE / "buildings"


def gate() -> Path:
    """4x4: the back's top two rows (the doorway in the roof's back slope, blocks 1 and 2 of the top row) over the
    front's bottom two (the stone face with the double door, blocks 1 and 2 of the bottom row)."""
    with Image.open(SB / "saffron_gate_back/saffron_gate_back.png") as im:
        back, pal = np.array(im, np.uint8), im.getpalette()[:48]
    with Image.open(SB / "saffron_gate/saffron_gate.png") as im:
        front = np.array(im, np.uint8)
        assert im.getpalette()[:48] == pal, "the two packs share Saffron's buildings' palette"
    a = np.concatenate([back[0:32], front[16:48]])
    name = "route12_gate"
    folder = OUT / name
    folder.mkdir(parents=True, exist_ok=True)
    out = Image.fromarray(a, "P")
    out.putpalette(pal + [0] * (768 - 48))
    out.save(folder / f"{name}.png", transparency=0)
    shutil.copyfile(SB / "saffron_gate/saffron_gate_door.png", folder / f"{name}_door.png")
    meta = json.loads((SB / "saffron_gate/saffron_gate.json").read_text())
    meta.update({"id": name, "name": name, "image": f"{name}.png", "image_size_px": [64, 64],
                 "footprint_blocks": {"width": 4, "height": 4}, "door_blocks": [[1, 3], [2, 3], [1, 0], [2, 0]],
                 "source": "route12-concept/route12_buildings.py: saffron_gate_back's top two rows over "
                           "saffron_gate's bottom two; the double door (blocks 1 and 2 of the bottom row) is one wide "
                           "door, 32 px; the doorway (blocks 1 and 2 of the top row) is entered walking south"})
    meta["door"]["image"] = f"{name}_door.png"
    (folder / f"{name}.json").write_text(json.dumps(meta, indent=2) + "\n")
    return folder


ALL = (gate,)

if __name__ == "__main__":
    print(gate())
