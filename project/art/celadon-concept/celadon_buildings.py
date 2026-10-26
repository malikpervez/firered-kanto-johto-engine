"""Celadon's own buildings, drawn here in one palette (bank 9 of the town's tileset): the Department Store, the
Mansion, the hotel, the Game Corner and Erika's Gym, a glasshouse. Their doors are Pewter Gym's door frames, each
colour the palette's at the Gym's index (the palette keeps the Gym's at the indices the frames use); every door but
the Gym's has the board over it painted plain.

Each function writes buildings/<name>/<name>.png, <name>_door.png and <name>.json and returns the pack's folder.
"""
import json
from pathlib import Path

import numpy as np
from PIL import Image

HERE = Path(__file__).resolve().parent
GYM = HERE.parent / "pewter-concept/buildings/pewter_gym"
OUT = HERE / "buildings"

# the palette: Pewter Gym's at the indices its door frames use (1, 2, 4, 9-13), the town's own colours at the others
PAL = [(0, 0, 0),
       (24, 24, 40),     # 1 outline
       (56, 56, 72),     # 2 deep shadow, the doorway
       (120, 40, 56),    # 3 deep red
       (88, 104, 128),   # 4 slate
       (184, 64, 72),    # 5 red
       (232, 128, 136),  # 6 rose
       (48, 96, 112),    # 7 glass, dark
       (120, 192, 192),  # 8 glass, light
       (184, 176, 160),  # 9 stone, shaded
       (216, 208, 184),  # 10 stone
       (240, 232, 208),  # 11 stone, lit
       (136, 104, 56),   # 12 bronze
       (200, 160, 72),   # 13 gold
       (240, 212, 128),  # 14 gold, lit
       (80, 144, 88)]    # 15 leaf green


def _outline(a: np.ndarray) -> None:
    shape = a > 0
    p = np.pad(shape, 1)
    edge = shape & ~(p[2:, 1:-1] & p[:-2, 1:-1] & p[1:-1, 2:] & p[1:-1, :-2])
    a[edge] = 1


def _window(a, x, y, w, h, lit=True):
    a[y:y + h, x:x + w] = 2
    a[y + 1:y + h - 1, x + 1:x + w - 1] = 7
    if lit:
        a[y + 1:y + 1 + (h - 2) // 2, x + 1:x + w - 1] = 8      # the sky in its upper panes
    a[y + h - 1, x:x + w] = 11                                  # the sill


def _door_frames(letters: bool) -> np.ndarray:
    """Pewter Gym's three door frames (48x32), in this palette by index; ``letters``: keep the "GYM" board."""
    gym_pal = [tuple(c) for c in np.array(Image.open(GYM / "pewter_gym.png").getpalette()[:48]).reshape(16, 3)]
    to_index = {c: i for i, c in enumerate(gym_pal)}
    frames = np.array(Image.open(GYM / "pewter_gym_door.png").convert("RGBA"))
    idx = np.zeros(frames.shape[:2], np.uint8)
    for y in range(frames.shape[0]):
        for x in range(frames.shape[1]):
            if frames[y, x, 3]:
                idx[y, x] = to_index[tuple(frames[y, x, :3])]
    if not letters:
        board = idx[2:9]
        board[board == 2] = 10                                  # the board's letters, painted out
    return idx


def _save(name: str, a: np.ndarray, doors: list[tuple[int, int]], frames: np.ndarray, extra_doors=(),
          note: str = "") -> Path:
    """Paste the closed door frame at each animated door (its board in the block above it), outline nothing more,
    write the pack. ``extra_doors``: doorways that don't animate (drawn in ``a`` already)."""
    folder = OUT / name
    folder.mkdir(parents=True, exist_ok=True)
    closed = frames[:, 0:16]
    for bx, by in doors:
        x0, y0 = bx * 16, (by - 1) * 16
        mask = closed > 0
        a[y0:y0 + 32, x0:x0 + 16][mask] = closed[mask]
    im = Image.fromarray(a, "P")
    im.putpalette([v for c in PAL for v in c] + [0] * (768 - 48))
    im.save(folder / f"{name}.png", transparency=0)
    rgba = np.zeros((*frames.shape, 4), np.uint8)
    for i, c in enumerate(PAL):
        if i:
            rgba[frames == i] = [*c, 255]
    Image.fromarray(rgba, "RGBA").save(folder / f"{name}_door.png")
    h, w = a.shape
    meta = {"schema_version": 2, "id": name, "type": "building", "image": f"{name}.png", "image_size_px": [w, h],
            "block_size_px": 16, "footprint_blocks": {"width": w // 16, "height": h // 16}, "transparent_index": 0,
            "door_blocks": [list(d) for d in list(doors) + list(extra_doors)],
            "door": {"image": f"{name}_door.png", "sheet_size_px": [48, 32], "frame_size_px": [16, 32],
                     "frame_count": 3, "frame_order": ["closed", "half_open", "open"],
                     "closed_frame_matches_building_crop": True},
            "name": name, "source": "drawn by celadon-concept/celadon_buildings.py; its doors are Pewter Gym's, "
                                    "recoloured" + (f"; {note}" if note else "")}
    (folder / f"{name}.json").write_text(json.dumps(meta, indent=2) + "\n")
    return folder


def _windows(a, x_from, x_to, y0, skip=(), h=12, lit=True):
    """A row of windows on the 16-pixel grid (so their tiles repeat): one in each block column from ``x_from`` to
    ``x_to`` (pixels), but the block columns in ``skip``."""
    for bx in range(x_from // 16, x_to // 16):
        if bx not in skip:
            _window(a, bx * 16 + 3, y0, 10, h, lit)


def department_store() -> Path:
    """10x7: a flat-roofed store of four floors, its name board in red and gold across the top floor, broad shop
    windows on the ground floor either side of its two doors (blocks 2 and 7 of the bottom row)."""
    w, h = 160, 112
    a = np.zeros((h, w), np.uint8)
    a[0:6, 0:w] = 4                                            # the roof's parapet,
    a[1, 0:w] = 9
    a[6:8, 0:w] = 2                                            # its shadow
    a[8:h, 4:w - 4] = 10                                       # the walls
    a[8:h, 4:6] = 11
    a[8:h, w - 6:w - 4] = 9
    a[12:26, 8:w - 8] = 5                                      # the name board: red, gold-edged, gold lettering
    a[12, 8:w - 8] = 13
    a[25, 8:w - 8] = 3
    for x in range(16, w - 16, 8):
        a[16:22, x + 1:x + 6] = 14
        a[16:22, x + 3:x + 4] = 13
    for y0 in (34, 50):                                        # two floors of windows
        _windows(a, 0, w, y0, skip=(0, 9))
    a[66:68, 4:w - 4] = 9
    a[68:72, 4:w - 4] = 12                                     # the awning over the ground floor
    a[70:72, 4:w - 4] = 13
    for x0 in range(4, w - 4, 8):
        a[72:76, x0:x0 + 4] = 5                                # its red and cream stripes
        a[72:76, x0 + 4:x0 + 8] = 11
    for x0, x1 in ((8, 24), (48, 112), (136, 152)):            # the shop windows, between the doors
        a[80:108, x0:x1] = 2
        a[81:107, x0 + 1:x1 - 1] = 7
        a[81:92, x0 + 1:x1 - 1] = 8
    a[108:h, 0:w] = 9                                          # the step along its front
    _outline(a)
    return _save("department_store", a, [(2, 6), (7, 6)], _door_frames(False))


def mansion() -> Path:
    """8x8: the Celadon Mansion, five floors of flats in cream stone under a slate mansard, a canopy over its front
    door (block 3 of the bottom row); its back door is a lit doorway in the roof's back edge (block 3 of the top
    row), entered walking south, that doesn't animate."""
    w, h = 128, 128
    a = np.zeros((h, w), np.uint8)
    a[0:20, 2:w - 2] = 4                                       # the mansard's back slope, the back door's porch in it
    a[0:20, 2:w - 2][::4] = 2
    a[2:16, 48:64] = 1                                         # the back doorway: a dark arch, gold lamp above it
    a[3:16, 49:63] = 2
    a[6:16, 52:60] = 13
    a[8:16, 53:59] = 14
    a[0:2, 50:62] = 13
    a[16:20, 46:66] = 9                                        # its step
    a[20:24, 0:w] = 2                                          # the eaves
    a[24:h, 4:w - 4] = 10                                      # the walls
    a[24:h, 4:6] = 11
    a[24:h, w - 6:w - 4] = 9
    for y0 in (26, 42, 58, 74):                                # four floors of windows above the ground floor
        _windows(a, 0, w, y0, skip=(0, 3, 7))
        a[y0 + 14, 4:w - 4] = 9                                # each floor's cornice
    a[24:92, 48:64] = 9                                        # the stair tower over the door
    for y0 in (26, 42, 58, 74):
        _window(a, 51, y0 + 2, 10, 8, lit=False)
    a[92:96, 36:76] = 12                                       # the canopy over the front door
    a[94:96, 36:76] = 13
    _windows(a, 0, w, 100, skip=(0, 3, 7), h=20)              # the ground floor's tall windows
    a[124:h, 0:w] = 9
    _outline(a)
    return _save("mansion", a, [(3, 7)], _door_frames(False), extra_doors=[(3, 0)],
                 note="its back door (3,0) is a doorway in the roof's back edge, entered walking south")


def hotel() -> Path:
    """6x5: a rose-walled hotel of three floors under a slate roof, its sign in gold over the door (block 2 of the
    bottom row), balconies with flowers."""
    w, h = 96, 80
    a = np.zeros((h, w), np.uint8)
    a[0:14, 0:w] = 4
    a[0:14, 0:w][:, ::8] = 2
    a[14:16, 0:w] = 2
    a[16:h, 4:w - 4] = 6
    a[16:h, 4:6] = 11
    a[16:h, w - 6:w - 4] = 5
    for y0 in (18, 34):
        _windows(a, 0, w, y0, skip=(0, 5), h=11)
        for bx in range(1, w // 16 - 1):                       # the balconies' flowers
            a[y0 + 11:y0 + 14, bx * 16 + 1:bx * 16 + 15] = 15
            a[y0 + 11, bx * 16 + 3:bx * 16 + 13:4] = 6
    _windows(a, 0, w, 52, skip=(0, 2, 5), h=22)
    a[76:h, 0:w] = 9
    _outline(a)
    return _save("hotel", a, [(2, 4)], _door_frames(False))


def game_corner() -> Path:
    """9x5: the Game Corner, a red facade under a marquee of gold lights, coin signs either side, glass doors in the
    middle (block 4 of the bottom row)."""
    w, h = 144, 80
    a = np.zeros((h, w), np.uint8)
    a[0:10, 0:w] = 3
    a[2:8, 4:w - 4] = 5
    a[10:12, 0:w] = 2
    a[12:h, 2:w - 2] = 5
    a[12:h, 2:4] = 6
    a[12:h, w - 4:w - 2] = 3
    a[14:28, 4:w - 4] = 13                                     # the marquee: gold, a row of lights
    a[15:27, 5:w - 5] = 12
    for x in range(8, w - 8, 8):
        a[17:21, x + 1:x + 4] = 14
        a[22:25, x + 5:x + 7] = 11
    for cx in (32, w - 32):                                    # the coin signs, centred on block corners
        for y in range(32, 64):
            for x in range(cx - 16, cx + 16):
                d = (x - cx + 0.5) ** 2 + (y - 48 + 0.5) ** 2
                if d < 196:
                    a[y, x] = 13 if d < 120 else 12
                    if d < 40:
                        a[y, x] = 14
        a[42:54, cx - 2:cx + 2] = 12
    for x0 in (52, 84):                                        # windows of light either side of the doors
        a[34:72, x0:x0 + 8] = 6
        a[36:70, x0 + 2:x0 + 6] = 14
    a[76:h, 0:w] = 9
    _outline(a)
    return _save("game_corner", a, [(4, 4)], _door_frames(False))


def gym() -> Path:
    """7x5: Erika's Gym, a glasshouse: panes of green glass in white frames under a glass roof, a plant in each pane,
    the Gym's board over its door (block 3 of the bottom row)."""
    w, h = 112, 80
    a = np.zeros((h, w), np.uint8)
    for r in range(0, 22):                                     # the glass roof, rising to its ridge, framed
        inset = max(0, 22 - r) // 2
        a[r, inset:w - inset] = 8 if r % 6 else 11
        a[r, inset:w - inset][(np.arange(inset, w - inset) % 16) == 0] = 11
    a[20:24, 0:w] = 11
    a[24:h, 2:w - 2] = 7
    for x in range(0, w, 16):                                  # the panes' white frames, on the block grid
        a[24:h, max(2, x):x + 2] = 11
    a[24:h, w - 4:w - 2] = 11
    for y in (40, 56):
        a[y:y + 2, 2:w - 2] = 11
    for bx in range(w // 16):                                  # a plant in each pane: leaves, a pink flower
        for y0 in (44, 60):
            x0 = bx * 16 + 4
            a[y0 + 4:y0 + 12, x0 + 3:x0 + 5] = 15
            a[y0 + 2:y0 + 6, x0:x0 + 8] = 15
            a[y0 + 6:y0 + 8, x0 + 1:x0 + 7] = 15
            a[y0 + 2:y0 + 4, x0 + 3:x0 + 5] = 6
    a[76:h, 0:w] = 9
    _outline(a)
    return _save("celadon_gym", a, [(3, 4)], _door_frames(True))


ALL = (department_store, mansion, hotel, game_corner, gym)
