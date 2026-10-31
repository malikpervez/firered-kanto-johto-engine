#!/usr/bin/env python3
"""Draws Route 7's block plan (plan_stage1.txt): the concept, as shapes. Edit the shapes here and run it again;
make_art.py builds the map from the plan. Run from the repository root:
python3 project/art/route7-concept/draw_plan.py

Route 7 is the short park road from Celadon's boulevard to Saffron's west gate. It is 30x24 blocks (old Route 7
was 20x28). Celadon's boulevard (its rows 20-23) meets the left edge at rows 10-13; Saffron lies beyond the right edge,
reached only through the gate (its door 18-19,9). It has:
- **the road** of cobbles, four blocks wide as Celadon's boulevard is, out of the trees at Celadon's edge to the gate;
- **Saffron's west gate** (Route 2's south forest gate, as on Routes 6 and 8) at the road's east end, its doors
  onto the road;
- **the Underground Path's hut** north of the road with its sign: the way under Saffron to Route 8 and Lavender;
- **the singing garden** south of the road, a bed of flowers where the Jigglypuff sings to the Ralts, by a little
  pond, with tall grass along its south side (Route 7's wild Pokémon) and the Wepear Berry hidden in its corner.

The west seven columns are forest and road only, as old Celadon needed (it had no room for more of this strip:
KR-54, gone with Celadon's rebuild). Every block is at least 7 in from the right edge, so the camera never shows old Saffron
across it (no seam: KR-34).

Letters: the kit's legend (T forest, . lawn, = cobble, g grass, * flowers, ~ pond, o rocks, b bushes, R trees, S signs),
F Saffron's west gate (Route 2's south forest gate), U the Underground Path's hut (Viridian's pond keeper's house).
"""
from pathlib import Path

W, H = 30, 24
g = [["." for _ in range(W)] for _ in range(H)]


def rect(x0, y0, x1, y1, c):
    for y in range(y0, y1 + 1):
        for x in range(x0, x1 + 1):
            g[y][x] = c


def at(x, y, c):
    g[y][x] = c


# the frame: forest, open at Celadon's boulevard, the west band forest and road only; the east deep, so old Saffron is
# never in view
rect(0, 0, 29, 1, "T")
rect(0, 22, 29, 23, "T")
rect(0, 0, 6, 9, "T")
rect(0, 14, 6, 23, "T")
rect(23, 0, 29, 23, "T")
rect(14, 2, 22, 3, "T")                        # the forest over the gate

# the road, Celadon's boulevard (rows 10-13) to the gate
rect(0, 10, 22, 13, "=")
rect(15, 4, 22, 9, "F")                        # Saffron's west gate, doors 18-19,9

# the Underground Path's hut and its sign, north of the road
rect(8, 6, 11, 9, "U")                         # the hut, door 9,9
at(12, 9, "S")                                 # its sign, read from 12,10
rect(7, 2, 8, 3, "R"); rect(12, 3, 13, 4, "R")

# the singing garden south of the road: flowers, the little pond, a tree and a rock by it; tall grass along its
# south side (Route 7's wild Pokémon live there)
rect(8, 15, 14, 19, "*")
rect(16, 15, 19, 17, "~")
rect(21, 15, 22, 16, "R"); at(20, 18, "o")
rect(8, 20, 22, 21, "g")
at(17, 16, "v")                                # a lily pad on the little pond
# the clearing north of the hut: a field rock and a few flowers in its lawn
at(10, 3, "o"); at(9, 5, ","); at(10, 5, ",")

Path(__file__).with_name("plan_stage1.txt").write_text("".join("".join(r) + "\n" for r in g))
print("    " + "".join(str(x % 10) for x in range(W)))
for y, r in enumerate(g):
    print(f"{y:2d}  " + "".join(r))
