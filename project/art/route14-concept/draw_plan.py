#!/usr/bin/env python3
"""Draws Route 14's block plan (plan_stage1.txt): the concept, as shapes. Edit the shapes here and run it again;
make_art.py builds the map from the plan. Run from the repository root:
python3 project/art/route14-concept/draw_plan.py

Route 14 runs south down the coast from Route 13 to where Route 15 turns west for Fuchsia. It is 26x62 blocks, as
before. Route 13's path (its columns 20-22) comes in at the top edge, columns 16-19; Route 15's low road (its rows
14-17) meets the left edge at rows 50-53 (offset 36, was 37: the road moved a row up to sit on the forest's grid).
It has:
- **the way in** from Route 13, down through the woods, the route sign at its foot;
- **the grass maze**: four lanes of tall grass between fences, each open at the other end from the last, so the way
  south zigzags through all four; a tree to cut in the third fence makes a short cut past two of them;
- **the clifftop meadow** below the maze: its pond, its grass and its trees, ledges along its south side down into
  the lower meadow (one way);
- **the bikers' road** down the meadows' west side, from the maze to the crossroads;
- **the Shroomish's dell** by the shore, behind a hedge, a tree to cut its way in;
- **the crossroads** at the bottom, the road west to Route 15, a short pier out over the sea;
- **the berry garden** under the woods south of the road, behind a tree to cut (more than 8 blocks in from the edge
  Route 15 joins, or the game would hide it: KR-45).
The sea runs down the whole east side, beyond a strip of shore.

Letters: the kit's legend (T forest, . lawn, : dirt, g grass, * flowers, ~ pond, v lily pads, s the sea, d the
pier, # fences, _ ledges, b bushes, R trees, S signs).
"""
from pathlib import Path

W, H = 26, 62
g = [["T" for _ in range(W)] for _ in range(H)]


def rect(x0, y0, x1, y1, c):
    for y in range(y0, y1 + 1):
        for x in range(x0, x1 + 1):
            g[y][x] = c


def at(x, y, c):
    g[y][x] = c


def tree(x, y):
    rect(x, y, x + 1, y + 1, "R")


# the way in from Route 13 (its columns 20-22: here 16-19), the route sign at its foot
rect(16, 0, 19, 7, ":")
rect(2, 8, 21, 49, ".")
at(15, 8, "S")

# the sea down the east side, beyond the shore (columns 20-21)
rect(22, 12, 25, 61, "s")

# the grass maze: fences across, each open at the other end from the last; the lanes' tall grass
rect(6, 10, 21, 10, "#")                        # open at the west end (2-5)
rect(2, 13, 17, 13, "#")                        # open at the east end (18-21)
rect(6, 16, 21, 16, "#")                        # open at the west end; the tree to cut at 19,16
at(19, 16, ".")
rect(2, 19, 17, 19, "#")                        # open at the east end
# where a fence meets the forest its rails run on into the trees (no free end post with a slit of lawn beside it)
at(2, 13, "\u01c8"); at(2, 19, "\u01c8"); at(21, 10, "\u01c8")
rect(8, 11, 15, 12, "g")
rect(6, 14, 13, 15, "g")
rect(10, 17, 17, 18, "g")
rect(4, 20, 11, 21, "g")

# the clifftop meadow: its pond, grass, trees and flowers; the ledges along its south side
rect(12, 24, 17, 29, "~")
at(13, 25, "v")
at(16, 28, "v")
rect(9, 23, 10, 24, "*")
tree(8, 26)
tree(19, 24)
rect(8, 30, 11, 32, "g")
rect(18, 30, 21, 32, "g")
rect(8, 33, 21, 33, "_")

# the bikers' road down the west side, to the crossroads; its verge's tree and flowers
rect(4, 23, 5, 49, ":")
rect(2, 22, 3, 22, "*"); rect(6, 22, 7, 22, "*")  # its head, a row clear of the tall grass, between two beds of flowers
tree(2, 30)
rect(2, 40, 3, 42, "*")

# the shore's flowers and rocks
rect(20, 35, 21, 37, "*")
at(21, 27, "o")
at(20, 48, "o")

# the lower meadow: grass, a tree
rect(8, 35, 13, 38, "g")
rect(7, 44, 11, 47, "g")
tree(11, 40)

# the Shroomish's dell by the shore, behind a hedge, the tree to cut its way in at 15,42
rect(15, 39, 21, 39, "b")
rect(15, 40, 15, 45, "b")
rect(15, 46, 21, 46, "b")
at(15, 42, ".")
rect(19, 44, 20, 45, "*")

# the crossroads: the road west to Route 15 (rows 50-53 at the left edge), the pier
rect(0, 50, 21, 53, ":")
rect(21, 52, 21, 53, ".")                       # the road's corner by the sea is lawn: only the pier meets the water (the dirt joins the pier's planks)
rect(22, 50, 24, 51, "d")

# the berry garden south of the road, behind the tree to cut at 12,54
rect(12, 54, 13, 55, ".")
at(13, 54, "b")
rect(10, 56, 15, 59, ".")
rect(10, 58, 12, 59, "*")

Path(__file__).with_name("plan_stage1.txt").write_text("".join("".join(r) + "\n" for r in g))
