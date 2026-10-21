"""The concept Pallet's two houses, after the original games' Pallet houses, in their own palette (bank 9): white
plaster walls on a stone base, a roof of scalloped clay tiles with a ridge cap, a dormer window and a brick
chimney, a panelled door under a little awning, and two big windows with wooden frames, shutters and flower
boxes. The player's house has a red roof and shutters, the rival's blue ones.

5x5 blocks (80x80 pixels); the door is block (1, 4). Index 0 is transparent: the grass shows there.
"""
import numpy as np

PH = [(0, 0, 0), (40, 32, 40), (176, 168, 160), (224, 216, 200), (248, 244, 232), (136, 40, 40), (192, 64, 56),
      (232, 112, 88), (40, 64, 128), (64, 104, 176), (112, 152, 216), (96, 56, 40), (152, 96, 56), (64, 96, 128),
      (168, 208, 232), (128, 128, 136)]
H_OUT, WSH, WAL, WLT, RD0, RD1, RD2, BL0, BL1, BL2, WD0, WD1, GL0, GL1, STN = range(1, 16)
ROOFS = {"red": (RD0, RD1, RD2), "blue": (BL0, BL1, BL2)}
BAYER = [[0, 8, 2, 10], [12, 4, 14, 6], [3, 11, 1, 9], [15, 7, 13, 5]]


def _roof(t, dark, mid, light):
    """A front-facing roof of scalloped tiles over the eaves (rows 3-37), lit from the left."""
    for y in range(3, 38):
        inset = max(0, 10 - (y - 3))  # the hips: the roof narrows to the ridge
        x0, x1 = 1 + inset, 79 - inset
        for x in range(x0, x1):
            row = (y - 5) // 5
            ty = (y - 5) % 5
            tx = (x + (3 if row % 2 else 0)) % 6
            c = mid
            if ty == 4 or (ty == 3 and tx in (0, 5)):
                c = dark  # the scalloped lower edge of each tile row
            elif ty == 0 and 1 <= tx <= 4:
                c = light  # each tile's lit top
            elif tx == 0 and ty < 3:
                c = dark if x > 40 else mid
            if x > 56 and c == light and (x + y) % 2:
                c = mid  # the right of the roof is in shade
            t[y, x] = c
        t[y, x0] = H_OUT
        t[y, x1 - 1] = H_OUT
    t[3, 11:69] = H_OUT
    t[4:6, 12:68] = light  # the ridge cap
    t[5, 12:68:4] = mid
    t[6, 11:69] = dark
    t[37, 1:79] = dark  # eaves
    t[38, 0:80] = H_OUT
    t[39, 3:77] = WSH  # the eaves' shadow on the wall


def _dormer(t, dark, mid, light):
    """A small window in the roof with its own little gable."""
    x0, x1, y0, y1 = 33, 47, 10, 30
    for y in range(y0, y0 + 7):  # its gable
        half = (y - y0) + 1
        t[y, 40 - half:40 + half] = mid
        t[y, 40 - half] = H_OUT
        t[y, 40 + half - 1] = H_OUT
        if y > y0 + 1:
            t[y, 40 - half + 1] = light
    t[y0 + 7, x0 - 1:x1 + 1] = H_OUT
    t[y0 + 8:y1, x0:x1] = WAL
    t[y0 + 8:y1, x0] = H_OUT
    t[y0 + 8:y1, x1 - 1] = H_OUT
    t[y0 + 8:y1, x1 - 2] = WSH
    t[y0 + 10:y1 - 2, x0 + 3:x1 - 3] = GL0
    t[y0 + 10:y0 + 13, x0 + 3:x1 - 3] = GL1
    t[y0 + 10:y1 - 2, 39:41] = WD1
    t[y1 - 2, x0 + 2:x1 - 2] = WD0
    t[y1, x0 - 1:x1 + 1] = dark


def _chimney(t):
    t[0:16, 58:66] = STN
    for y in range(1, 16):
        for x in range(58, 66):
            if (y % 3 == 0) or ((x + (y // 3) * 2) % 4 == 0):
                t[y, x] = H_OUT if y % 3 == 0 else WSH  # bricks and mortar
    t[0, 57:67] = H_OUT
    t[1, 57:67] = WLT
    t[0:16, 57] = H_OUT
    t[0:16, 66] = H_OUT


def _walls(t):
    t[40:74, 4:76] = WAL
    t[40:74, 70:75] = WSH  # the right corner is in shade, stippled into the lit wall
    for y in range(40, 74):
        for x in range(66, 70):
            if (x - 65) * 4 > BAYER[y % 4][x % 4]:
                t[y, x] = WSH
    t[40:74, 7:9] = WLT  # the lit left corner
    t[40:74, 4] = H_OUT
    t[40:74, 75] = H_OUT
    t[40:74, 5:7] = WSH
    t[40:74, 73:75] = WSH
    # the stone base
    t[72:79, 3:77] = STN
    for x in range(3, 77):
        if (x - 3) % 7 == 0:
            t[72:79, x] = H_OUT
    t[72, 3:77] = WLT
    t[79, 3:77] = H_OUT


def _window(t, x0, y0, dark, mid, light):
    w, h = 16, 14
    t[y0 - 1:y0 + h + 1, x0 - 1:x0 + w + 1] = H_OUT
    t[y0:y0 + h, x0:x0 + w] = WD1
    t[y0 + 1:y0 + h - 1, x0 + 2:x0 + w - 2] = GL0
    t[y0 + 1:y0 + 5, x0 + 2:x0 + w - 2] = GL1
    for k in range(3):  # a glint
        t[y0 + 2 + k, x0 + 3 + k] = WLT
    t[y0 + 1:y0 + h - 1, x0 + 7:x0 + 9] = WD1
    t[y0 + 6:y0 + 8, x0 + 2:x0 + w - 2] = WD1
    t[y0 + h - 1, x0:x0 + w] = WD0
    for sx in (x0 - 6, x0 + w + 1):  # shutters
        t[y0:y0 + h, sx:sx + 5] = mid
        t[y0:y0 + h, sx] = H_OUT
        t[y0:y0 + h, sx + 4] = H_OUT
        for yy in range(y0 + 1, y0 + h - 1, 2):
            t[yy, sx + 1:sx + 4] = dark
        t[y0, sx:sx + 5] = H_OUT
        t[y0 + h - 1, sx:sx + 5] = H_OUT
    # flower box
    t[y0 + h + 1:y0 + h + 4, x0 - 1:x0 + w + 1] = WD1
    t[y0 + h + 3, x0 - 1:x0 + w + 1] = WD0
    t[y0 + h + 1, x0:x0 + w:2] = light
    t[y0 + h, x0 + 1:x0 + w - 1:3] = mid


def _small_window(t, x0, y0):
    """A narrow window right of the shutters, for the stairs."""
    w, h = 7, 12
    t[y0 - 1:y0 + h + 1, x0 - 1:x0 + w + 1] = H_OUT
    t[y0:y0 + h, x0:x0 + w] = WD1
    t[y0 + 1:y0 + h - 1, x0 + 1:x0 + w - 1] = GL0
    t[y0 + 1:y0 + 4, x0 + 1:x0 + w - 1] = GL1
    t[y0 + 2, x0 + 2] = WLT
    t[y0 + 5:y0 + 6, x0 + 1:x0 + w - 1] = WD1
    t[y0 + h - 1, x0:x0 + w] = WD0


def _door(t, dark, mid, light):
    """At block (1, 4): x 16-31, y 64-79, with an awning above it."""
    t[56:59, 14:34] = mid  # the awning
    t[56, 14:34] = light
    t[58, 14:34] = dark
    t[55, 14:34] = H_OUT
    t[59, 13:35] = H_OUT
    t[60:62, 15:33] = WSH  # its shadow
    t[62:78, 18:30] = H_OUT
    t[63:78, 19:29] = WD1
    t[63:78, 19] = WD0
    t[63:78, 28] = WD0
    for y0 in (64, 71):  # panels
        t[y0:y0 + 5, 21:27] = WD0
        t[y0 + 1:y0 + 4, 22:26] = WD1
    t[64:68, 22:26] = GL0  # a little window in the door
    t[64, 22:26] = GL1
    t[70:72, 26:28] = light  # the handle
    t[77, 16:32] = STN  # the step
    t[78, 15:33] = STN
    t[78, 15:33][::2] = WLT
    t[79, 15:33] = H_OUT


def house(roof: str = "red") -> np.ndarray:
    dark, mid, light = ROOFS[roof]
    t = np.zeros((80, 80), np.uint8)
    _walls(t)
    _roof(t, dark, mid, light)
    _chimney(t)
    _dormer(t, dark, mid, light)
    _window(t, 41, 53, dark, mid, light)
    _small_window(t, 65, 50)
    _door(t, dark, mid, light)
    return t
