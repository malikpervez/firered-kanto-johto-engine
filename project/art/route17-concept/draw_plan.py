#!/usr/bin/env python3
"""Draws Route 17's block plan (plan_stage1.txt): the concept, as shapes. Edit the shapes here and run it again;
make_art.py builds the map from the plan. Run from the repository root:
python3 project/art/route17-concept/draw_plan.py

Route 17 is Cycling Road: the downhill run from the wooded heights of Route 16 to the shore of Route 18, by bike
only. It is 36x120 blocks (old Route 17 was 33x158). Route 16's road down from the plaza (its columns 12-17) comes in
at the top edge, at the same columns; the road onto Route 18 (its columns 8-16) leaves by the bottom edge at columns
14-22. It has:
- **the start**, at the top of the hill: the road from Route 16 opens onto a clearing in the woods (tall grass either
  side) and a cobbled start area, where the track begins at a chequered line;
- **the track**, twelve blocks wide, three lanes painted on it, all one slope the bike runs down by itself: down a
  cutting through the woods to the cliff top, then out over the sea on a causeway, fenced on both sides, lamps along
  its verges;
- **the lagoon**, halfway down: the causeway splits round a stretch of open sea (its two sea rocks inside a fence),
  the track in two lanes either side;
- **two rest stops** off the causeway, a paved lay-by on each side (the west one above the lagoon, the east one
  below), flat ground where a rider can stop: the bikers gather there, and the notices are;
- **the finish**, where the causeway comes ashore: a chequered line, a cobbled plaza where the slope ends, the shore's
  grass and flowers, and the road on to Route 18 between two fences.

Letters: the kit's legend (T forest, . lawn, = cobble, p paving, g grass, * flowers, s the sea, q and Q sea rocks,
# fences, l lamps, o rocks, S signs), and the track's: t the track, i its lane lines, a its arrows, x its chequered
lines.
"""
from pathlib import Path

W, H = 36, 120
g = [["T" for _ in range(W)] for _ in range(H)]


def rect(x0, y0, x1, y1, c):
    for y in range(y0, y1 + 1):
        for x in range(x0, x1 + 1):
            g[y][x] = c


def at(x, y, c):
    g[y][x] = c


def lamp(x, y):  # the kit's lamp: a post two blocks tall
    rect(x, y, x, y + 1, "l")


TRACK = (12, 23)          # its columns
START, FINISH = 15, 106   # its first and last rows (the chequered lines)
LANES = (15, 20)          # the lane lines' columns
LAGOON = (62, 80)         # the rows where the causeway splits round the lagoon

# the sea below the cliff
rect(0, 32, W - 1, H - 1, "s")

# the start: the road from Route 16, the clearing, the start area
rect(12, 0, 17, 9, "=")
rect(3, 7, 32, 14, ".")
rect(12, 7, 17, 9, "=")
rect(10, 10, 25, 14, "=")
rect(4, 8, 7, 10, "g")
rect(28, 8, 31, 10, "g")
rect(3, 12, 6, 13, "*")
rect(29, 12, 32, 13, "*")
rect(2, 12, 2, 13, "b"); rect(33, 12, 33, 13, "b")   # bushes beside the flowers: the forest's 2x2 trees end whole
rect(26, 15, 33, 15, "b"); at(33, 14, "b")      # bushes along the forest's odd top row by the hidden Rare Candy:
                                                # its trees start whole a row down, the lawn before them stays lawn
at(9, 9, "S")                                   # the route sign
at(26, 13, "S")                                 # trainer tips: B to stay in place on the slope

# the cutting through the woods, the cliff top, the causeway over the sea (its fences and verges)
rect(10, START, 11, 31, ".")
rect(24, START, 25, 31, ".")
rect(2, 28, W - 3, 31, ".")
rect(2, 29, 4, 30, "o")
rect(31, 28, 33, 29, "o")
rect(9, 32, 26, FINISH - 3, "#")
rect(10, 32, 25, FINISH - 3, ".")

# the west rest stop, above the lagoon
rect(1, 43, 9, 55, "#")
rect(2, 44, 9, 54, ".")
rect(3, 46, 7, 52, "p")
rect(2, 44, 3, 45, "*")
at(5, 45, "S")                                  # the notice: watch out for discarded items
lamp(8, 44)
lamp(8, 52)

# the east rest stop, below it
rect(26, 85, 34, 97, "#")
rect(26, 86, 33, 96, ".")
rect(28, 88, 32, 94, "p")
rect(32, 95, 33, 96, "*")
at(29, 87, "S")                                 # the notice: throw Poké Balls
at(31, 87, "S")                                 # trainer tips: the same species grow at different rates
lamp(27, 86)
lamp(27, 95)

# the shore at the finish, the plaza where the slope ends, the road on to Route 18
rect(5, FINISH - 2, 30, 112, ".")
rect(5, FINISH - 2, 9, FINISH, "g")
rect(26, FINISH - 2, 30, FINISH, "g")
rect(6, 109, 8, 111, "*")
rect(27, 109, 29, 111, "*")
rect(10, FINISH + 1, 25, 110, "=")
rect(13, 111, 23, H - 1, "#")
rect(14, 111, 22, H - 1, "=")
at(9, FINISH + 1, "S")                          # Cycling Road: the slope ends here

# the track: its lanes, arrows and chequered lines; the lagoon
rect(TRACK[0], START, TRACK[1], FINISH, "t")
for y in list(range(START + 2, LAGOON[0] - 1)) + list(range(LAGOON[1] + 2, FINISH - 1)):
    for x in LANES:
        at(x, y, "i")
for y in (24, 40, 54, 90, 100):
    at(17, y, "a")
    at(18, y, "a")
rect(TRACK[0], START, TRACK[1], START, "x")
rect(TRACK[0], FINISH, TRACK[1], FINISH, "x")
rect(15, LAGOON[0], 20, LAGOON[1], "#")
rect(16, LAGOON[0] + 1, 19, LAGOON[1] - 1, "s")
at(17, 68, "q")
at(18, 74, "Q")

# lamps along the verges; sea rocks off the causeway
for y in (19, 27, 36, 60, 78, 100):
    lamp(10, y)
    lamp(25, y)
for x, y, c in ((4, 38, "q"), (31, 46, "Q"), (30, 70, "q"), (4, 76, "Q"), (5, 96, "q"), (31, 102, "Q")):
    at(x, y, c)

Path(__file__).with_name("plan_stage1.txt").write_text("".join("".join(r) + "\n" for r in g))
