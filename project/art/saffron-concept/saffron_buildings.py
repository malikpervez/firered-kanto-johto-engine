"""Saffron's own buildings, drawn here in one palette (bank 9 of the city's tileset): Silph Co.'s tower, Sabrina's Gym,
the Fighting Dojo, the gatehouses at the ends of its two avenues (the front one, its double door on its south face;
the back one, a doorway in its roof's back edge) and the Magnet Train station. The Gym's and the Dojo's doors are
Pewter Gym's door frames, each colour the palette's at the Gym's index, as Celadon's are (celadon-concept); the
gatehouse's double door is drawn here.

Each function writes buildings/<name>/<name>.png, its door frames and <name>.json and returns the pack's folder.
Drawn on the 16-pixel grid, so the tiles of a storey repeat along it.
"""
import json
import sys
from pathlib import Path

import numpy as np
from PIL import Image

HERE = Path(__file__).resolve().parent
sys.path.insert(0, str(HERE.parent / "celadon-concept"))
from celadon_buildings import _door_frames, _outline, _window, _windows  # noqa: E402

OUT = HERE / "buildings"

# the palette: Pewter Gym's at the indices its door frames use (1, 2, 4, 9-13), the city's own at the others
PAL = [(0, 0, 0),
       (24, 24, 40),     # 1 outline
       (56, 56, 72),     # 2 deep shadow, the doorways
       (72, 48, 104),    # 3 deep violet
       (88, 104, 128),   # 4 slate
       (136, 96, 176),   # 5 violet
       (200, 168, 224),  # 6 lilac
       (48, 96, 112),    # 7 glass, dark
       (120, 192, 192),  # 8 glass, light
       (184, 176, 160),  # 9 stone, shaded
       (216, 208, 184),  # 10 stone
       (240, 232, 208),  # 11 stone, lit
       (136, 104, 56),   # 12 bronze
       (200, 160, 72),   # 13 gold
       (240, 212, 128),  # 14 gold, lit
       (96, 56, 40)]     # 15 dark wood


def _save(name: str, a: np.ndarray, doors: list[tuple[int, int]], frames: np.ndarray | None, extra_doors=(),
          note: str = "") -> Path:
    """Paste the closed door frame at the first door block of ``doors`` (a frame 32 wide covers two blocks), write
    the pack. ``extra_doors``: doorways that don't animate (drawn in ``a`` already)."""
    folder = OUT / name
    folder.mkdir(parents=True, exist_ok=True)
    meta_door = None
    if frames is not None:
        fw = frames.shape[1] // 3
        closed = frames[:, 0:fw]
        bx, by = doors[0]
        x0, y0 = bx * 16, (by - 1) * 16
        mask = closed > 0
        a[y0:y0 + 32, x0:x0 + fw][mask] = closed[mask]
        rgba = np.zeros((*frames.shape, 4), np.uint8)
        for i, c in enumerate(PAL):
            if i:
                rgba[frames == i] = [*c, 255]
        Image.fromarray(rgba, "RGBA").save(folder / f"{name}_door.png")
        meta_door = {"image": f"{name}_door.png", "sheet_size_px": [3 * fw, 32], "frame_size_px": [fw, 32],
                     "frame_count": 3, "frame_order": ["closed", "half_open", "open"],
                     "closed_frame_matches_building_crop": True}
    im = Image.fromarray(a, "P")
    im.putpalette([v for c in PAL for v in c] + [0] * (768 - 48))
    im.save(folder / f"{name}.png", transparency=0)
    h, w = a.shape
    meta = {"schema_version": 2, "id": name, "type": "building", "image": f"{name}.png", "image_size_px": [w, h],
            "block_size_px": 16, "footprint_blocks": {"width": w // 16, "height": h // 16}, "transparent_index": 0,
            "door_blocks": [list(d) for d in list(doors) + list(extra_doors)],
            **({"door": meta_door} if meta_door else {}),
            "name": name, "source": "drawn by saffron-concept/saffron_buildings.py" + (f"; {note}" if note else "")}
    (folder / f"{name}.json").write_text(json.dumps(meta, indent=2) + "\n")
    return folder


def _slates(a, y0, y1, x0, x1, base=4, line=2, step=4):
    """A slate roof: ``base`` with a line of ``line`` every ``step`` rows (so its tiles repeat along it)."""
    a[y0:y1, x0:x1] = base
    for y in range(y0 + step - 1, y1, step):
        a[y, x0:x1] = line


def silph_co() -> Path:
    """9x12: Silph Co.'s tower, the tallest building in Kanto: a gold crown band with the company's emblem under a
    slate parapet, seven storeys of glass between stone piers, a bronze canopy over the glass lobby, its door in the
    middle (block 4 of the bottom row)."""
    w, h = 144, 192
    a = np.zeros((h, w), np.uint8)
    a[0:6, 0:w] = 4                                            # the parapet,
    a[1, 0:w] = 9
    a[6:8, 0:w] = 2                                            # its shadow
    a[8:32, 2:w - 2] = 13                                      # the crown band, gold
    a[8, 2:w - 2] = 14
    a[30:32, 2:w - 2] = 12
    for y in range(8, 32):                                     # the emblem: a slate diamond, a lit "S" in it
        for x in range(56, 88):
            d = abs(x - 71.5) + abs(y - 19.5)
            if d < 11:
                a[y, x] = 4 if d > 8 else 7
    for y, x0, x1 in ((14, 68, 76), (15, 66, 68), (16, 66, 68), (17, 66, 68), (18, 68, 74), (19, 68, 74),
                      (20, 74, 76), (21, 74, 76), (22, 74, 76), (23, 66, 74), (24, 66, 74)):
        a[y, x0:x1] = 14
    a[14, 66:68] = 7
    a[32:144, 2:w - 2] = 10                                    # seven storeys of glass between stone piers
    for r in range(2, 9):
        y0 = r * 16
        for bx in range(w // 16):
            x0 = bx * 16
            a[y0 + 2:y0 + 13, x0 + 3:x0 + 13] = 7
            a[y0 + 2:y0 + 7, x0 + 3:x0 + 13] = 8
            a[y0 + 7, x0 + 3:x0 + 13] = 9
        a[y0 + 14:y0 + 16, 2:w - 2] = 9                        # each storey's sill
    a[32:144, 2:4] = 11
    a[32:144, w - 4:w - 2] = 9
    a[144:150, 0:w] = 12                                       # the canopy over the lobby
    a[148:150, 0:w] = 13
    a[150:188, 2:w - 2] = 10                                   # the lobby: tall glass, the door in the middle
    for bx in range(w // 16):
        if bx != 4:
            x0 = bx * 16
            a[154:184, x0 + 2:x0 + 14] = 7
            a[154:166, x0 + 2:x0 + 14] = 8
            a[184, x0 + 2:x0 + 14] = 9
    a[188:h, 0:w] = 9                                          # the step along its front
    _outline(a)
    return _save("silph_co", a, [(4, 11)], _door_frames(False))


def gym() -> Path:
    """7x5: Sabrina's Gym, lilac walls under a violet roof with a crystal orb on a gold stand over the door, the
    Gym's board over its door (block 3 of the bottom row)."""
    w, h = 112, 80
    a = np.zeros((h, w), np.uint8)
    _slates(a, 0, 22, 0, w, base=5, line=3)
    a[0:2, 0:w] = 3
    for y in range(2, 20):                                     # the orb, its highlight, its stand
        for x in range(48, 64):
            d = (x - 55.5) ** 2 + (y - 10.5) ** 2
            if d < 50:
                a[y, x] = 6 if d > 9 or x > 55 or y > 10 else 11
    a[17:20, 50:62] = 13
    a[19, 52:60] = 12
    a[22:24, 0:w] = 2                                          # the eaves
    a[24:76, 2:w - 2] = 6                                      # the walls, violet piers on the block grid
    for x in range(0, w, 16):
        a[24:76, max(2, x):x + 2] = 5
    a[24:76, w - 4:w - 2] = 5
    _windows(a, 0, w, 30, skip=(0, 6))
    _windows(a, 0, w, 52, skip=(0, 3, 6), h=20)
    a[76:h, 0:w] = 9
    _outline(a)
    return _save("saffron_gym", a, [(3, 4)], _door_frames(True))


def dojo() -> Path:
    """7x5: the Fighting Dojo, a broad slate roof with a dark wooden ridge and gold ends, white plaster walls framed
    in dark wood, lattice windows and sliding panels, its board over the door (block 3 of the bottom row)."""
    w, h = 112, 80
    a = np.zeros((h, w), np.uint8)
    _slates(a, 3, 28, 0, w)
    a[0:4, 6:w - 6] = 15                                       # the ridge beam, gold at its ends
    a[0:5, 2:10] = 13
    a[0:5, w - 10:w - 2] = 13
    a[24:28, 0:4] = 9                                          # the eaves' tips, turned up
    a[24:28, w - 4:w] = 9
    a[28:32, 0:w] = 15                                         # the eaves
    a[32:76, 2:w - 2] = 11                                     # white plaster in a dark wooden frame
    for x in range(0, w, 16):
        a[32:76, max(2, x):x + 2] = 15
    a[32:76, w - 4:w - 2] = 15
    a[47:49, 2:w - 2] = 15
    for bx in range(w // 16):                                  # lattice windows above, sliding panels below
        if bx in (0, 6):
            continue
        x0 = bx * 16
        a[35:45, x0 + 4:x0 + 12] = 12
        a[35:45, x0 + 4:x0 + 12][:, ::3] = 15
        a[35:45, x0 + 4:x0 + 12][::3] = 15
        if bx != 3:
            a[52:74, x0 + 3:x0 + 13] = 12
            a[52:74, x0 + 7:x0 + 9] = 15
    a[76:h, 0:w] = 9
    _outline(a)
    return _save("fighting_dojo", a, [(3, 4)], _door_frames(False))


def _double_door() -> np.ndarray:
    """The gatehouse's double door, 96x32: three frames of 32x32 (closed, half open, open), the door in a stone
    arch, a threshold along its foot."""
    frames = np.zeros((32, 96), np.uint8)
    for k, gap in enumerate((0, 8, 13)):
        f = frames[:, k * 32:(k + 1) * 32]
        f[0:32, 0:32] = 10
        f[0:2, 0:32] = 9
        f[2:28, 2:30] = 1                                      # the arch
        f[3:28, 3:29] = 2
        f[3:6, 3:6] = 10
        f[3:6, 26:29] = 10
        for x0, x1 in ((3, 16 - gap), (16 + gap, 29)):         # the two leaves: dark wood, bronze planks, gold studs
            if x1 - x0 < 2:
                continue
            f[6:28, x0:x1] = 15
            f[6:28, x0:x1][:, 1::4] = 12
            for y in (10, 18, 25):
                f[y, x0 + 1:x1 - 1:3] = 13
        if gap == 0:
            f[16:19, 14:18] = 14                               # the handles
        f[28:32, 0:32] = 9                                     # the threshold
    return frames


def gate() -> Path:
    """4x3: the gatehouse at the end of an avenue, a slate roof with a gold ridge over stone walls, a window either
    side, its double door in the middle of its south face (blocks 1 and 2 of the bottom row)."""
    w, h = 64, 48
    a = np.zeros((h, w), np.uint8)
    _slates(a, 0, 14, 0, w)
    a[0:2, 4:w - 4] = 13
    a[14:16, 0:w] = 2
    a[16:44, 2:w - 2] = 10                                     # stone, laid in courses
    a[16:44, 2:w - 2][7::8] = 9
    a[16:44, 2:4] = 11
    a[16:44, w - 4:w - 2] = 9
    _window(a, 3, 22, 10, 14)
    _window(a, w - 13, 22, 10, 14)
    a[44:h, 0:w] = 9
    _outline(a)
    return _save("saffron_gate", a, [(1, 2), (2, 2)], _double_door(),
                 note="its double door (blocks 1 and 2 of the bottom row) is one wide door, 32 px")


def gate_back() -> Path:
    """4x3: the gatehouse at the south end of the north-south avenue, seen from the city: its roof's back slope with
    an open doorway in its middle (blocks 1 and 2 of the top row), entered walking south, that doesn't animate; its
    stone south face below."""
    w, h = 64, 48
    a = np.zeros((h, w), np.uint8)
    _slates(a, 0, 28, 0, w)
    a[0:16, 16:48] = 10                                        # the doorway: a stone porch, a dark arch in it
    a[0:2, 16:48] = 9
    a[2:16, 18:46] = 1
    a[3:16, 19:45] = 2
    a[3:5, 19:21] = 10
    a[3:5, 43:45] = 10
    a[28:30, 0:w] = 2
    a[30:44, 2:w - 2] = 10
    a[30:44, 2:w - 2][7::8] = 9
    a[30:44, 2:4] = 11
    a[30:44, w - 4:w - 2] = 9
    for bx in range(4):
        _window(a, bx * 16 + 3, 31, 10, 11)
    a[44:h, 0:w] = 9
    _outline(a)
    return _save("saffron_gate_back", a, [], None, extra_doors=[(1, 0), (2, 0)],
                 note="its doorway (blocks 1 and 2 of the top row) is entered walking south")


def station() -> Path:
    """8x4: the Magnet Train station, a glass vault on white ribs over a gold band with a magnet in it, stone walls
    with tall windows, and its entrance shuttered (the train is boarded with the attendant outside)."""
    w, h = 128, 64
    a = np.zeros((h, w), np.uint8)
    for r in range(0, 18):                                     # the vault: glass between white ribs
        inset = max(0, 6 - r)
        a[r, inset:w - inset] = 8 if r > 1 else 11
    for x in range(0, w, 16):
        a[2:18, x + 7:x + 9] = 11
    a[18:20, 0:w] = 2
    a[20:32, 2:w - 2] = 13                                     # the gold band, a magnet in its middle
    a[20, 2:w - 2] = 14
    a[31, 2:w - 2] = 12
    a[22:30, 56:72] = 5
    a[22:27, 60:68] = 13
    a[22:25, 56:60] = 14
    a[22:25, 68:72] = 14
    a[32:60, 2:w - 2] = 10                                     # the walls, tall windows, the shuttered entrance
    a[32:60, 2:4] = 11
    a[32:60, w - 4:w - 2] = 9
    _windows(a, 0, w, 36, skip=(0, 3, 4, 7), h=20)
    a[34:60, 50:78] = 12
    a[36:60, 52:76] = 4
    a[36:60, 52:76][::3] = 9
    a[60:h, 0:w] = 9
    _outline(a)
    return _save("magnet_train_station", a, [], None,
                 note="no door: its entrance is shuttered (the attendant outside arranges the journey)")


ALL = (silph_co, gym, dojo, gate, gate_back, station)
