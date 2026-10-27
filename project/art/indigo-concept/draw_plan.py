#!/usr/bin/env python3
"""Draws Indigo Plateau's block plan (plan_stage1.txt): the concept, as shapes. Edit the shapes here and run it again;
make_art.py builds the map from the plan. Run from the repository root:
python3 project/art/indigo-concept/draw_plan.py

Indigo Plateau is the Pokémon League's mountaintop: the League's tower, its forecourt, the road down to Route 23. It
is 24x20 blocks, as before. Route 23's road (its columns 10-13) leaves the bottom edge at columns 10-13 (offset 0, as
before); League West Pass's road (its rows 9-11) meets the left edge at rows 9-11 (offset 0, as before), closed by
the workers until the game is won. It has:
- **the League's tower** at the top, its door at 11,11 (warp 0, into the Pokémon Center, as before);
- **the forecourt** before it, paved, lamps and flower beds either side, a tree by the tower;
- **the road** down from the forecourt to Route 23, between the pines;
- **the west road** out to League West Pass (and Johto), under construction: the workers stand across it.

Letters: the kit's legend (T forest, . lawn, p paving, = cobble, : dirt, * flowers, b bushes, R trees, l lamps), L the League.
"""
from pathlib import Path

W, H = 24, 20
g = [["T" for _ in range(W)] for _ in range(H)]


def rect(x0, y0, x1, y1, c):
    for y in range(y0, y1 + 1):
        for x in range(x0, x1 + 1):
            g[y][x] = c


def at(x, y, c):
    g[y][x] = c


rect(6, 0, 17, 19, ".")                         # the mountaintop's lawn
rect(7, 0, 15, 11, "L")                         # the League's tower, door 11,11
rect(8, 12, 15, 15, "p")                        # the forecourt
rect(10, 16, 13, 19, "=")                       # the cobbled road down to Route 23
rect(0, 8, 6, 11, ":")                          # the west road to League West Pass (rows 9-11 meet it)
rect(0, 8, 5, 8, "b")                           # (its north verge)
for x in (7, 16):
    rect(x, 12, x, 13, "l")                     # lamps either side of the forecourt
rect(6, 14, 7, 15, "*")
rect(16, 14, 17, 15, "*")
rect(16, 6, 17, 7, "R")                         # a tree beside the tower
rect(6, 0, 6, 7, "b")                           # a hedge along the tower's west side
rect(16, 0, 17, 5, "T")                         # the pines close in at the top and the foot
rect(6, 18, 9, 19, "T")
rect(14, 18, 17, 19, "T")

Path(__file__).with_name("plan_stage1.txt").write_text("".join("".join(r) + "\n" for r in g))
