#!/usr/bin/env python3
"""Draws Route 23's block plan (plan_stage1.txt): the concept, as shapes. Edit the shapes here and run it again;
make_art.py builds the map from the plan. Run from the repository root:
python3 project/art/route23-concept/draw_plan.py

Route 23 is the road to the Pokémon League: north from the League gate (Route 22's), through the badge gates, to
Victory Road and, out of it, up to Indigo Plateau. It is 24x160 blocks, as before. Indigo Plateau's road (its columns
10-13) meets the top edge at columns 10-13 (offset 0, as before); Route 22's woods are below the bottom edge (offset 0:
the two weren't joined while Route 23 was the old map). It has, from the south:
- **the League gate's back**, its doorway out onto the road (warps 2 and 3, from the gate, as before);
- **the badge gates**, six narrow passes through the woods, a guard beside each who stops you without the badge
  (Cascade, Thunder, Rainbow, Soul, Marsh, Volcano), meadows of tall grass between them;
- **the lake** past the Soul Badge's gate, crossed by Surf (the Soul Badge lets you use it), its shores;
- **the Earth Badge's gate**, the last, into the yard under Victory Road's cliff, the way in (warp 0) and its sign;
- **Victory Road's way out** (warp 1), in the same cliff, opening into a yard of its own, walled from the first: the
  lane up beside the cliff to the meadow on the cliff top, and the road north out of it to Indigo Plateau.

Each gate is a pass four blocks wide: the guard stands in its east column; across the three blocks beside him, two
rows of triggers (the game's coord events, 42 in all as before) stop anyone without the badge.

Letters: the kit's legend (T forest, . lawn, g tall grass, * flowers, ~ the lake, b bushes, S signs), C the cliff and Y Victory
Road's mouths (Route 2's cave mouth), H the League gate's back (Route 12's north gatehouse).
"""
from pathlib import Path

W, H = 24, 160
g = [["T" for _ in range(W)] for _ in range(H)]


def rect(x0, y0, x1, y1, c):
    for y in range(y0, y1 + 1):
        for x in range(x0, x1 + 1):
            g[y][x] = c


def at(x, y, c):
    g[y][x] = c


# the badge gates (pass columns and rows; the guard in the east column, on the gate's guard row)
GATES = [(8, 138), (8, 120), (8, 102), (8, 84), (8, 56), (8, 46), (4, 36)]  # (west column, top row), south first
for x0, y0 in GATES:
    rect(x0, y0, x0 + 3, y0 + 5, ".")

# the League gate's back, its doorway at 9-10,156; the plaza before it
rect(8, 156, 11, 159, "H")
rect(2, 144, 21, 155, ".")
rect(3, 145, 6, 147, "*")
rect(17, 145, 20, 147, "*")
# the meadows between the gates
for y0, y1 in ((126, 137), (108, 119), (90, 101), (52, 55), (42, 45)):
    rect(2, y0, 21, y1, ".")
    rect(3, y0 + 1, 7, y1 - 1, "g")
    rect(15, y0 + 1, 20, y1 - 1, "g")
# the lake past the Soul Badge's gate, its shores
rect(2, 62, 21, 83, ".")
rect(2, 66, 21, 79, "~")
rect(3, 81, 6, 82, "*")
# the yard under Victory Road's cliff (its way in), walled from the yard of its way out
rect(2, 30, 9, 35, ".")
at(3, 30, "S")                                   # Victory Road's sign
rect(12, 30, 21, 35, ".")
rect(10, 30, 11, 35, "b")                        # the hedge between the two yards
rect(2, 20, 19, 29, "C")                         # the cliff
rect(4, 25, 9, 29, "Y")                          # Victory Road's way in, door 6,29
rect(12, 25, 17, 29, "Y")                        # and its way out, door 14,29
rect(20, 20, 21, 29, ".")                        # the lane up beside the cliff
# the meadow on the cliff top, the road north to Indigo Plateau
rect(2, 4, 21, 19, ".")
rect(4, 6, 8, 10, "g")
rect(15, 12, 20, 17, "g")
rect(13, 5, 17, 7, "*")
rect(10, 0, 13, 3, ".")

Path(__file__).with_name("plan_stage1.txt").write_text("".join("".join(r) + "\n" for r in g))
