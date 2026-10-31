#!/usr/bin/env python3
"""Draws Route 5's block plan (plan_stage1.txt): the concept, as shapes. Edit the shapes here and run it again;
make_art.py builds the map from the plan. Run from the repository root:
python3 project/art/route5-concept/draw_plan.py

Route 5 is the garden road south from Cerulean to Saffron's north gate:
- **the lane** out of Cerulean's neck (columns 29-32), its cobbles carried on through a belt of forest;
- **the Day Care**, a family house west of the road with a fenced paddock below it where the Pokémon left there
  play (Meowth and Spinda);
- **the Underground Path's hut** east of the road, its sign by its door, a lane of cobbles to it: the way under
  Saffron to Vermilion;
- **Saffron's north gate** at the bottom, a gatehouse you walk into from the north (its door at columns 24-25, over
  Saffron's own gate door below it);
- tall grass in the east meadow and the south-west corner, Pidgey and Hoothoot by the forest.

Letters: the kit's legend (T forest, . lawn, = cobble, * flowers, b bushes, g tall grass, o rocks, # fence, S signs)
and the buildings: D the Day Care (Viridian's family house), U the Underground Path's hut (Viridian's gardener's
house), N the gate (Route 2's north forest gate).
"""
from pathlib import Path

W, H = 50, 36
g = [["." for _ in range(W)] for _ in range(H)]


def rect(x0, y0, x1, y1, c):
    for y in range(y0, y1 + 1):
        for x in range(x0, x1 + 1):
            g[y][x] = c


def at(x, y, c):
    g[y][x] = c


# the frame: forest either side, a belt of it along the top (the lane through it), forest along the bottom
rect(0, 0, 7, 35, "T")
rect(42, 0, 49, 35, "T")
rect(8, 0, 41, 3, "T")             # (the forest is drawn in whole 2x2 trees on the even grid: it ends on odd rows
rect(8, 30, 41, 35, "T")           # and columns and starts on even ones, so no tree is cut in half)
rect(28, 0, 28, 3, "b"); rect(33, 0, 33, 3, "b")   # bushes either side of the lane through the belt

# the road: out of Cerulean's neck (29-32), bending west to the gate (its door at 24-25)
rect(29, 0, 32, 16, "=")
rect(23, 17, 32, 18, "=")
rect(23, 19, 26, 29, "=")

# the Day Care and its paddock
rect(14, 7, 18, 10, "D")                      # door (16,10)
rect(16, 11, 16, 12, "="); rect(16, 12, 28, 12, "=")
rect(10, 14, 22, 14, "#"); rect(10, 21, 22, 21, "#"); rect(10, 14, 10, 21, "#"); rect(22, 14, 22, 21, "#")
rect(12, 16, 14, 17, "*"); rect(18, 19, 20, 20, "*")
rect(9, 6, 12, 7, "*"); at(20, 7, "o"); at(9, 11, "b"); at(10, 11, "b")

# the Underground Path's hut, its sign and its lane
rect(34, 21, 37, 24, "U")                     # door (35,24)
rect(27, 25, 36, 25, "=")
at(37, 25, "S")                               # its sign, read from (37,26)
rect(39, 21, 40, 22, "*")

# the east meadow's grass, the south-west corner's, flowers and rocks
rect(34, 6, 40, 14, "g")
rect(9, 23, 15, 28, "g")
rect(17, 24, 19, 25, "*"); at(39, 27, "o"); at(33, 15, "o")
rect(27, 28, 29, 28, "b"); rect(20, 28, 22, 28, "b")
# a little detail on the open lawns (off the road and the people's places): flowers between the Day Care and the lane,
# a field rock in the lawn inside the road's bend, a stump under the north treeline
rect(23, 8, 25, 9, "*"); at(30, 21, "o"); at(35, 4, "k")

# Saffron's north gate: you walk into its top (24-25,30) from the road
rect(21, 30, 28, 35, "N")
# the gate's sides (columns 20 and 29) are odd halves of the forest's 2x2 cells: a hedge of bushes there instead, so
# the forest ends on whole trees either side of it
rect(20, 30, 20, 35, "b"); rect(29, 30, 29, 35, "b")

Path(__file__).with_name("plan_stage1.txt").write_text("".join("".join(r) + "\n" for r in g))
print("    " + "".join(str(x // 10 % 10) if x % 10 == 0 else " " for x in range(W)))
print("    " + "".join(str(x % 10) for x in range(W)))
for y, r in enumerate(g):
    print(f"{y:2d}  " + "".join(r))
