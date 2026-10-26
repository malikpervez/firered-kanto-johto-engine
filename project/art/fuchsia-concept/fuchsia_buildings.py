"""Fuchsia's own buildings, drawn here: the Safari Zone's gate lodge and Koga's Gym in Saffron's buildings' palette
(saffron-concept/saffron_buildings.py: here bank 9 of the town's tileset), and the house with a back door (house 2,
the one with the pond garden behind it): Viridian's pond keeper's house with a dormer door in its roof's back slope,
in Viridian's houses' palette (bank 7). The lodge's and the Gym's doors are Pewter Gym's door frames, as Saffron's are;
the house's front door keeps its pack's frames, and its back door is a doorway entered walking south, that doesn't
animate.

Each function writes buildings/<name>/<name>.png, its door frames and <name>.json and returns the pack's folder.
Drawn on the 16-pixel grid, so the tiles of a wall repeat along it.
"""
import json
import shutil
import sys
from pathlib import Path

import numpy as np
from PIL import Image

HERE = Path(__file__).resolve().parent
sys.path.insert(0, str(HERE.parent / "celadon-concept"))
sys.path.insert(0, str(HERE.parent / "saffron-concept"))
import saffron_buildings as sb  # noqa: E402
from celadon_buildings import _door_frames, _outline, _windows  # noqa: E402

OUT = HERE / "buildings"
VB = HERE.parent / "viridian-concept/buildings"


def _save(name, a, doors, frames, extra_doors=(), note=""):
    """Saffron's _save, writing into this folder's buildings/."""
    old, sb.OUT = sb.OUT, OUT
    try:
        folder = sb._save(name, a, doors, frames, extra_doors, note)
    finally:
        sb.OUT = old
    meta = json.loads((folder / f"{name}.json").read_text())
    meta["source"] = "drawn by fuchsia-concept/fuchsia_buildings.py" + (f"; {note}" if note else "")
    (folder / f"{name}.json").write_text(json.dumps(meta, indent=2) + "\n")
    return folder


def safari_gate() -> Path:
    """7x5: the Safari Zone's gate, a lodge under a deep thatched roof with a dark wooden ridge, a dark signboard with
    gold lettering under its eaves, walls of bronze logs, windows either side, its door in the middle (block 3 of the
    bottom row)."""
    w, h = 112, 80
    a = np.zeros((h, w), np.uint8)
    a[0:4, 6:w - 6] = 15                                       # the ridge
    a[4:32, 0:w] = 12                                          # the thatch: straw in bands
    for y in range(5, 32, 3):
        a[y, 0:w] = 13
    for x in range(2, w, 8):
        a[6:31, x] = 14 if x % 16 == 2 else 13
    a[32:35, 0:w] = 13                                         # its fringe at the eaves
    for x in range(0, w, 4):
        a[35, x:x + 2] = 13
    a[35, 2:w:4] = 2
    a[36:38, 0:w] = 2                                          # the shadow under it
    a[38:76, 2:w - 2] = 12                                     # the log walls
    for y in range(41, 76, 4):
        a[y, 2:w - 2] = 15
    a[38:76, 2:4] = 13
    a[40:48, 16:96] = 15                                       # the signboard, gold-rimmed, its lettering
    a[40, 16:96] = 13
    a[47, 16:96] = 13
    for x in range(22, 92, 4):
        a[43:45, x:x + 2] = 14
    _windows(a, 16, 48, 52, h=12)
    _windows(a, 64, 96, 52, h=12)
    a[76:h, 0:w] = 9                                           # the step along its front
    _outline(a)
    return _save("safari_gate", a, [(3, 4)], _door_frames(False))


def gym() -> Path:
    """7x5: Koga's Gym, a ninja house: a violet tiled roof in two tiers (the upper over its middle three blocks, gold
    finials at its ends), dark timber walls with paper screens, the Gym's board over its door (block 3 of the bottom
    row)."""
    w, h = 112, 80
    a = np.zeros((h, w), np.uint8)
    sb._slates(a, 2, 14, 32, 80, base=5, line=3)               # the upper roof
    a[0:3, 34:78] = 15
    a[0:4, 30:36] = 13
    a[0:4, 76:82] = 13
    a[14:16, 28:84] = 2
    sb._slates(a, 16, 30, 0, w, base=5, line=3)                # the lower roof, its tips turned up
    a[26:30, 0:4] = 6
    a[26:30, w - 4:w] = 6
    a[30:32, 0:w] = 15                                         # the eaves
    a[32:76, 2:w - 2] = 15                                     # dark timber, paper screens in it
    for bx in range(w // 16):
        x0 = bx * 16
        if bx != 3:
            a[35:73, x0 + 3:x0 + 13] = 11
            a[35:73, x0 + 3:x0 + 13][:, 3::4] = 10
            a[35:73, x0 + 3:x0 + 13][4::8] = 10
    a[76:h, 0:w] = 9
    _outline(a)
    return _save("fuchsia_gym", a, [(3, 4)], _door_frames(True))


def house_back_door() -> Path:
    """4x4: Viridian's pond keeper's house (its pack, approved) with a dormer door in its roof's back slope (block 1
    of the top row, beside the chimney), entered walking south from behind the house: the door to the pond garden. Its front door is the
    pack's (block 1 of the bottom row), with the pack's door frames."""
    src = VB / "house_pond_keeper"
    with Image.open(src / "house_pond_keeper.png") as im:
        a = np.array(im, np.uint8)
        pal = im.getpalette()[:48]
    x0 = 16                                                    # block 1 of the top row, beside the chimney
    for k in range(6):                                         # the dormer's gable: the roof's green, outlined
        a[1 + k, x0 + 7 - k:x0 + 9 + k] = 6
        a[1 + k, x0 + 7 - k] = 1
        a[1 + k, x0 + 8 + k] = 1
        if k:
            a[1 + k, x0 + 8 - k:x0 + 8] = 8
    a[0, x0 + 7:x0 + 9] = 1
    a[7:16, x0 + 2:x0 + 14] = 1                                # its front: plaster round a dark wooden door
    a[7:16, x0 + 3:x0 + 13] = 11
    a[9:16, x0 + 5:x0 + 11] = 2
    a[9:16, x0 + 5:x0 + 11][:, 2::3] = 13
    a[12, x0 + 9] = 7
    name = "house_back_door"
    folder = OUT / name
    folder.mkdir(parents=True, exist_ok=True)
    out = Image.fromarray(a, "P")
    out.putpalette(pal + [0] * (768 - 48))
    out.save(folder / f"{name}.png", transparency=0)
    shutil.copyfile(src / "house_pond_keeper_door.png", folder / f"{name}_door.png")
    meta = json.loads((src / "house_pond_keeper.json").read_text())
    meta.update({"id": name, "image": f"{name}.png", "name": name,
                 "door_blocks": [list(meta["door_block"]), [1, 0]],
                 "source": "Viridian's house_pond_keeper (approved pack), a dormer door added in its roof's back "
                           "slope by fuchsia-concept/fuchsia_buildings.py: the back door, block (1,0), entered "
                           "walking south"})
    if "door" in meta and isinstance(meta["door"], dict):
        meta["door"]["image"] = f"{name}_door.png"
    (folder / f"{name}.json").write_text(json.dumps(meta, indent=2) + "\n")
    return folder


ALL = (safari_gate, gym, house_back_door)
