#!/usr/bin/env python3
"""Draws Route 13's block plan (plan_stage1.txt): the concept, as shapes. Edit the shapes here and run it again;
make_art.py builds the map from the plan. Run from the repository root:
python3 project/art/route13-concept/draw_plan.py

Route 13 is the coast road west from Silence Bridge, Route 12's boardwalk, to Route 14. It is 104x32 blocks, as
before. Silence Bridge (Route 12's columns 21-24) comes down onto the top edge at columns 86-89 (offset 65, as
before); Route 14's way in (its columns 16-19) leaves the bottom edge at columns 20-23 (offset 4, as before). It has:
- **the boardwalk** down from Silence Bridge over the bay, ashore at the landing, the route sign there;
- **the coast road** west from the landing to Route 14, past the headland where two beauties sit looking down on it;
- **the cove** south of the road's east half: its shore where the picnickers are, the sea beyond;
- **the fields** south of the road's west half, tall grass either side of an old lamp post, the trainer tips sign
  by it (something is hidden just left of the post);
- **the upland meadow** north of the road, under the woods: tall grass, ledges along its south side down to the
  road (one way; the path at its east end goes up), and behind a tree to cut, a nook in the woods where a Seedot
  lives;
- **the lovers' meadow** at the road's west end: a ring of flowers where Nidorino and Nidorina face each other.

Letters: the kit's legend (T forest, . lawn, : dirt, g grass, * flowers, s the sea, d the boardwalk, _ ledges,
b bushes, R trees, l lamps, S signs).
"""
from pathlib import Path

W, H = 104, 32
g = [["T" for _ in range(W)] for _ in range(H)]


def rect(x0, y0, x1, y1, c):
    for y in range(y0, y1 + 1):
        for x in range(x0, x1 + 1):
            g[y][x] = c


def at(x, y, c):
    g[y][x] = c


def tree(x, y):
    rect(x, y, x + 1, y + 1, "R")


# the sea: the bay under Silence Bridge, east of the landing, the cove
rect(74, 0, 103, 13, "s")
rect(92, 14, 103, 31, "s")
rect(56, 26, 91, 31, "s")

# the land between the woods and the sea, the upland meadow under the woods
rect(2, 14, 91, 25, ".")
rect(8, 8, 47, 13, ".")

# the boardwalk from Silence Bridge (Route 12's columns 21-24) down over the bay to the landing; the route sign
rect(86, 0, 89, 13, "d")
at(84, 15, "S")

# the coast road from the landing west to Route 14 (columns 20-23 at the bottom edge)
rect(86, 14, 89, 19, ":")
rect(20, 18, 89, 19, ":")
rect(20, 20, 23, 31, ":")
at(24, 17, "S")                                 # the trainer tips sign (SELECT)

# the headland above the road: bushes and a tree behind the beauties' seat
rect(58, 14, 65, 14, "b")
tree(66, 14)
tree(50, 14)

# the upland meadow: tall grass, ledges along its south side (the way up at its east end, columns 42-47)
rect(10, 9, 17, 11, "g")
rect(26, 9, 35, 11, "g")
rect(8, 13, 41, 13, "_")
tree(38, 9)

# the nook in the woods behind the tree to cut at 44,7, the Seedot's (its east side in line with the meadow's)
rect(40, 2, 47, 5, ".")
rect(44, 6, 45, 7, ".")
at(45, 7, "b")
rect(41, 2, 43, 3, "*")

# the fields south of the road: tall grass either side of the old lamp post (40,22), the tips sign by it
rect(26, 21, 35, 24, "g")
rect(44, 21, 53, 24, "g")
rect(40, 22, 40, 23, "l")
at(42, 21, "S")

# the lovers' meadow at the west end: a ring of flowers
rect(4, 17, 9, 21, "*")
rect(5, 18, 8, 20, ".")
tree(12, 15)
tree(14, 22)

# the cove's shore: flowers, trees
rect(68, 21, 71, 22, "*")
tree(80, 22)
tree(58, 22)

Path(__file__).with_name("plan_stage1.txt").write_text("".join("".join(r) + "\n" for r in g))
