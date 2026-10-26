"""Route 17's own pieces, drawn here: the cycle track, Cycling Road's surface. Smooth tarmac edged with a stone kerb
wherever it meets something else, with paint on it: a dashed lane line, an arrow pointing downhill, and a chequered
start and finish line. Every piece is a slope the bike runs down by itself (MB_CYCLING_ROAD_PULL_DOWN); the kerb is
drawn in the piece, so the track meets the kit's cobblestones (its start and its end) without one.

The track is in its own palette (bank 7 of the route's tileset), drawn on the 16-pixel grid, one piece per way the
track goes on (1 north, 2 east, 4 south, 8 west), as the kit's ground is.
"""
import random

import numpy as np

# the track's palette: tarmac in four greys, the kerb's stone in three, the paint
PAL = [(0, 0, 0), (36, 40, 52), (62, 68, 82), (80, 86, 100), (98, 104, 118), (124, 130, 142), (104, 96, 88),
       (164, 156, 140), (212, 204, 188), (236, 236, 224), (216, 72, 56), (240, 200, 72), (36, 40, 52),
       (36, 40, 52), (36, 40, 52), (36, 40, 52)]
LINE, TD, TM, TL, TH, KD, KM, KL, WHITE, RED, YELLOW = range(1, 12)
MARKS = ("line", "arrow", "check")


def _tarmac() -> np.ndarray:
    """The tarmac: mid grey with grit in the other greys, the same in every piece (so pieces share their tiles)."""
    r = random.Random(17)
    t = np.full((16, 16), TM, np.uint8)
    for _ in range(40):
        t[r.randrange(16), r.randrange(16)] = TD
    for _ in range(26):
        t[r.randrange(16), r.randrange(16)] = TL
    for _ in range(5):
        t[r.randrange(16), r.randrange(16)] = TH
    return t


def _paint(t: np.ndarray, mark: str) -> None:
    if mark == "line":  # a dash of the lane line, down the middle of the block
        t[3:13, 7:9] = WHITE
    elif mark == "arrow":  # an arrow pointing downhill
        t[2:9, 7:9] = WHITE
        for k in range(5):
            t[8 + k, 3 + k:5 + k] = WHITE
            t[8 + k, 11 - k:13 - k] = WHITE
    elif mark == "check":  # a chequered line across the track, two rows of squares
        for y in range(4, 12):
            for x in range(16):
                t[y, x] = WHITE if (x // 4 + (y - 4) // 4) % 2 == 0 else LINE


def piece(mask: int, corners: int = 0, mark: str | None = None) -> np.ndarray:
    """The track's block whose neighbours of track (or the cobblestones it meets) are ``mask`` (1 N, 2 E, 4 S, 8 W),
    with inside corners ``corners`` (1 NE, 2 SE, 4 SW, 8 NW: both sides track, the diagonal not), and its paint."""
    t = _tarmac()
    if mark:
        _paint(t, mark)
    band = (KD, KL, KM)  # the kerb, from the block's edge in: its outer edge, its lit top, its face
    for bit, sl in ((1, lambda k: np.s_[k, :]), (2, lambda k: np.s_[:, 15 - k]), (4, lambda k: np.s_[15 - k, :]),
                    (8, lambda k: np.s_[:, k])):
        if not mask & bit:
            for k in (2, 1, 0):
                t[sl(k)] = band[k]
    for bit, (ys, xs) in ((1, ((0, 1, 2), (15, 14, 13))), (2, ((15, 14, 13), (15, 14, 13))),
                          (4, ((15, 14, 13), (0, 1, 2))), (8, ((0, 1, 2), (0, 1, 2)))):
        if corners & bit:  # a quarter of kerb round the corner where the track turns
            for k in (2, 1, 0):
                for j in range(k + 1):
                    t[ys[k], xs[j]] = band[k]
                    t[ys[j], xs[k]] = band[k]
    return t
