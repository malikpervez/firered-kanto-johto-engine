#!/usr/bin/env python3
"""Draws Route 15's block plan (plan_stage1.txt): the concept, as shapes. Edit the shapes here and run it again;
make_art.py builds the map from the plan. Run from the repository root:
python3 project/art/route15-concept/draw_plan.py

Route 15 is the way east out of Fuchsia: two roads through the woods to Route 14. It is 80x24 blocks (old Route 15
was 96x32, its south half forest). Fuchsia's main street (its rows 20-23) comes in at the left edge, rows 4-7; Route
14's road (its rows 50-53) meets the right edge at rows 14-17 (offset -36: Route 14, rebuilt, moved its road up a
row). It has:
- **the gatehouse** at Fuchsia's edge, across the road (Route 16's Cycling Road gatehouse: its doorways at its ends);
- **the high road** east from it along the woods' edge, flowers on its verge: the quick way, with trainers on it;
- **the ledges** along its south side, down into the meadow (one way: there's no climbing back);
- **the meadow** between the two roads: tall grass in patches, trees, the pair who battle together;
- **the low road** below it, from the gatehouse round to Route 14, and the south meadow's grass under the woods;
- **the lookout** at the high road's east end, where the TM lies, and the slope down from it to the low road.

Letters: the kit's legend (T forest, . lawn, : dirt, = cobble, g grass, * flowers, _ ledges, b bushes, R trees,
S signs), and C the gatehouse.
"""
from pathlib import Path

W, H = 80, 24
g = [["T" for _ in range(W)] for _ in range(H)]


def rect(x0, y0, x1, y1, c):
    for y in range(y0, y1 + 1):
        for x in range(x0, x1 + 1):
            g[y][x] = c


def at(x, y, c):
    g[y][x] = c


def tree(x, y):
    rect(x, y, x + 1, y + 1, "R")


# Fuchsia's main street (rows 4-7) to the gatehouse (doorways 9,5 and 16,5); hedges round it
rect(0, 4, 8, 7, "=")
rect(9, 2, 16, 5, "C")
rect(8, 2, 8, 3, "b")
rect(9, 6, 16, 7, "b")

# the route's open ground between the woods (rows 2-19, east of the gatehouse)
rect(17, 2, 77, 19, ".")
rect(8, 8, 17, 19, "T")

# the high road (rows 4-6), its verge's flowers, the ledges below it (row 7)
rect(17, 4, 72, 6, ":")
for x0 in (22, 34, 47, 60):
    rect(x0, 2, x0 + 3, 3, "*")
rect(20, 7, 66, 7, "_")
at(20, 2, "S")                                  # the route sign, by the gatehouse's east doorway

# the lookout at the high road's east end (the TM at 75,3), the slope down to the low road
rect(73, 2, 77, 6, ".")
tree(74, 2)
rect(70, 7, 72, 13, ":")

# the meadow between the roads: tall grass, trees, the pair's clearing
rect(20, 9, 28, 12, "g")
rect(38, 9, 45, 12, "g")
rect(56, 9, 64, 12, "g")
tree(31, 9); tree(34, 11); tree(51, 9); tree(66, 10)
rect(47, 11, 49, 12, "*")

# the low road (rows 14-16), down from the gatehouse's side, round to Route 14 (rows 14-17 at the right edge)
rect(18, 6, 19, 16, ":")
rect(18, 14, 79, 16, ":")
rect(76, 14, 79, 17, ":")

# the south meadow under the woods
rect(22, 17, 30, 19, "g")
rect(44, 17, 52, 19, "g")
rect(62, 17, 68, 18, "*")
tree(36, 18); tree(57, 18)
at(72, 18, "k")                                 # an old stump on the lawn by Route 14's road
at(40, 18, "o")                                 # a field rock in the south meadow, daisies on its lawn
for x, y in ((20, 18), (33, 17), (42, 19)):
    at(x, y, ",")

Path(__file__).with_name("plan_stage1.txt").write_text("".join("".join(r) + "\n" for r in g))
