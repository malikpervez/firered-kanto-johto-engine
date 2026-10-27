#!/usr/bin/env python3
"""Draws Route 20's block plan (plan_stage1.txt): the concept, as shapes. Edit the shapes here and run it again;
make_art.py builds the map from the plan. Run from the repository root:
python3 project/art/route20-concept/draw_plan.py

Route 20 is the sea route west from Route 19 to Cinnabar Island, past the Seafoam Islands, by Surf. It is 120x20
blocks, as before. Cinnabar's sea meets the left edge (offset 0, as before); Route 19's sea (its rows 41-59) the right
edge at rows 0-18 (offset -41, as before). It has:
- **the sandbars** along the way, where the picnickers and a camper rest and the Seel and Dewgong haul out (the
  Stardust is hidden on one);
- **the Seafoam Islands**, two rocky islands in the middle, each with a cave's mouth facing south onto its shore, the
  islands' sign by each: the caves join under the sea;
- **the open sea** between, the swimmers in it, sea rocks along the route's edges.

Letters: the kit's legend (. lawn, * flowers, s the sea, q and Q sea rocks, S signs), C the islands' cliffs and Y the
caves' mouths (Route 2's).
"""
from pathlib import Path

W, H = 120, 20
g = [["s" for _ in range(W)] for _ in range(H)]


def rect(x0, y0, x1, y1, c):
    for y in range(y0, y1 + 1):
        for x in range(x0, x1 + 1):
            g[y][x] = c


def at(x, y, c):
    g[y][x] = c


# the sandbars
rect(8, 3, 15, 6, ".")
rect(9, 3, 10, 4, "*")
rect(20, 4, 25, 7, ".")
rect(38, 8, 45, 11, ".")
rect(39, 8, 40, 9, "*")
rect(90, 13, 97, 16, ".")
rect(94, 13, 96, 14, "*")

# the Seafoam Islands: the west island (its mouth's door 58,10) and the east one (78,12), their signs
rect(50, 2, 67, 16, ".")
rect(52, 3, 65, 10, "C")
rect(56, 6, 61, 10, "Y")
at(55, 11, "S")
rect(70, 3, 85, 17, ".")
rect(72, 4, 83, 12, "C")
rect(76, 8, 81, 12, "Y")
at(75, 13, "S")
rect(63, 13, 65, 15, "*")
rect(82, 15, 84, 16, "*")

# sea rocks along the edges, where open sea is all round them
def open_sea(x, y):
    return all(0 <= x + i < W and 0 <= y + j < H and g[y + j][x + i] == "s" for i in (-1, 0, 1) for j in (-1, 0, 1))


for x in range(3, 117, 7):
    for xx, yy, c in ((x, 1, "q" if x % 2 else "Q"), (x + 3, 18, "Q" if x % 2 else "q")):
        if open_sea(xx, yy):
            at(xx, yy, c)

Path(__file__).with_name("plan_stage1.txt").write_text("".join("".join(r) + "\n" for r in g))
