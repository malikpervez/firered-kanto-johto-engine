#!/usr/bin/env python3
"""Draws Route 19's block plan (plan_stage1.txt): the concept, as shapes. Edit the shapes here and run it again;
make_art.py builds the map from the plan. Run from the repository root:
python3 project/art/route19-concept/draw_plan.py

Route 19 is the sea route south from Fuchsia: a beach under the woods, then open sea, by Surf. It is 24x60 blocks, as
before. Fuchsia's beach path (its columns 18-29) comes in at the top edge, columns 6-17 (offset -12, as before);
Route 20's sea (its rows 0-18) meets the left edge at rows 41-59 (offset 41, as before). It has:
- **the beach** at the foot of Fuchsia's path, between the woods: a lawn shore with its flowers, the route sign, the
  two swimmers resting on it before they go in;
- **the jetty** out from the beach, where you start to surf;
- **the channel** south between the rocks, the swimmers in it; **the sandbar islet** halfway down, its flowers;
- **the rock island** at the bottom, where a Wingull nests, and the sea west to Route 20.

Letters: the kit's legend (T forest, . lawn, : dirt, * flowers, s the sea, q and Q sea rocks, d the jetty, b bushes,
R trees, S signs).
"""
from pathlib import Path

W, H = 24, 60
g = [["T" for _ in range(W)] for _ in range(H)]


def rect(x0, y0, x1, y1, c):
    for y in range(y0, y1 + 1):
        for x in range(x0, x1 + 1):
            g[y][x] = c


def at(x, y, c):
    g[y][x] = c


def tree(x, y):
    rect(x, y, x + 1, y + 1, "R")


# the sea: everything below the beach
rect(0, 10, 23, 59, "s")
rect(0, 10, 1, 19, "T")                         # the woods come down to the water either side at first
rect(22, 10, 23, 19, "T")

# Fuchsia's beach path (its columns 18-29: here 6-17), the beach under the woods
rect(6, 0, 17, 3, ":")
rect(2, 4, 21, 9, ".")
rect(2, 4, 4, 5, "*")
rect(19, 4, 21, 5, "*")
at(12, 4, "S")                                  # the route sign
tree(2, 8)
tree(20, 8)

# the jetty out from the beach
rect(10, 10, 13, 15, "d")

# the rocks along the channel
for x, y, c in ((3, 14, "q"), (19, 15, "Q"), (6, 21, "Q"), (20, 26, "q"), (2, 31, "q"), (21, 38, "Q"), (4, 37, "Q"),
                (18, 44, "q"), (15, 55, "Q"), (21, 51, "q")):
    at(x, y, c)

# the sandbar islet halfway down
rect(13, 29, 17, 32, ".")
rect(14, 30, 15, 31, "*")

# the rock island at the bottom, the Wingull's
rect(4, 52, 9, 56, ".")
rect(5, 53, 6, 54, "o")

Path(__file__).with_name("plan_stage1.txt").write_text("".join("".join(r) + "\n" for r in g))
