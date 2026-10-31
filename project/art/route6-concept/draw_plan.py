#!/usr/bin/env python3
"""Draws Route 6's block plan (plan_stage1.txt): the concept, as shapes. Edit the shapes here and run it again;
make_art.py builds the map from the plan. Run from the repository root:
python3 project/art/route6-concept/draw_plan.py

Route 6 is the park south of Saffron, between its south gate and Vermilion:
- **Saffron's south gate** at the top (Route 2's south forest gate): its door at columns 40-41, where the old
  gatehouse's was, above Saffron's own gate door;
- **the road** down from the gate to Vermilion's stairs (columns 40-42 at the bottom), lamps by the gate where
  Magnemite gather;
- **the Underground Path's hut** east of the road, its sign by the door: the way back under Saffron to Cerulean;
- **the pond** west of the road, the park's middle: the couple (Ricky and Nancy) talk on its east shore, and won't
  be overheard; a lawn with no bugs on it for Keigo north of it, tall grass round it to the south and west, Plusle
  and Minun playing in the north meadow, Granbull and Snubbull by the south one;
- **the east lawn** beside the road, where Elijah, Isabelle and Jeff stand looking across at it (they see part of
  the lawn, not the road).

Letters: the kit's legend (T forest, . lawn, = cobble, ~ pond, * flowers, b bushes, g tall grass, o rocks, l lamps,
S signs) and the buildings: F the gate (Route 2's south forest gate), U the Underground Path's hut (Viridian's pond
keeper's house).
"""
from pathlib import Path

W, H = 56, 32
g = [["." for _ in range(W)] for _ in range(H)]


def rect(x0, y0, x1, y1, c):
    for y in range(y0, y1 + 1):
        for x in range(x0, x1 + 1):
            g[y][x] = c


def at(x, y, c):
    g[y][x] = c


# the frame: forest round the park, the gate in the top edge, Vermilion's stairs in the bottom one
rect(0, 0, 13, 31, "T")
rect(52, 0, 55, 31, "T")
rect(14, 0, 51, 3, "T")
rect(14, 29, 51, 31, "T")
rect(16, 29, 36, 29, "g"); rect(37, 29, 39, 29, "."); rect(43, 29, 51, 29, ".")   # the south forest from row 30: whole trees
rect(37, 0, 44, 5, "F")                       # Saffron's south gate, its door (40-41,5)
rect(14, 4, 15, 28, "T")

# the road: from the gate's door down to Vermilion (40-42 at the bottom)
rect(40, 6, 41, 12, "=")
rect(40, 13, 42, 31, "=")
rect(38, 6, 38, 7, "l"); rect(43, 6, 43, 7, "l")  # lamps by the gate (Magnemite)

# the Underground Path's hut and its sign
rect(45, 8, 48, 11, "U")                      # door (46,11)
rect(42, 12, 46, 12, "=")
at(44, 11, "S")                               # its sign, read from (44,12)
rect(49, 8, 51, 9, "*")

# the pond, the couple's shore, the meadows round it
rect(20, 14, 34, 21, "~")
rect(16, 6, 33, 9, "g")                       # the north meadow (Plusle and Minun)
rect(24, 10, 33, 12, ".")                     # Keigo's lawn, no bugs on it
rect(16, 12, 18, 21, "g")                     # the west shore's grass
rect(16, 23, 36, 28, "g")                     # the south meadow
rect(35, 14, 37, 15, "*"); rect(35, 20, 37, 21, "*")
at(20, 11, "o"); at(36, 9, "o"); rect(34, 4, 36, 5, "b"); rect(45, 4, 47, 5, "b")

# the east lawn: bushes along its edge, flowers
rect(48, 16, 51, 17, "*"); at(50, 25, "o"); rect(44, 30, 51, 30, "T")
rect(44, 14, 44, 15, "b"); rect(44, 26, 44, 27, "b")
rect(43, 30, 43, 31, "b")                     # bushes beside the road out, so the forest east of it starts on whole trees
rect(36, 0, 36, 3, "b"); rect(45, 0, 45, 3, "b")   # and either side of Saffron's gate (the forest ends on whole trees)
# a little detail on the open lawns (off the road, the people's places and the trainers' sights): flowers in the east
# lawn's south corner and on the strip between the south meadow and the road, a stump under the north treeline
rect(45, 28, 46, 29, "*"); rect(37, 25, 38, 26, "*"); at(18, 4, "k")

Path(__file__).with_name("plan_stage1.txt").write_text("".join("".join(r) + "\n" for r in g))
print("    " + "".join(str(x // 10 % 10) if x % 10 == 0 else " " for x in range(W)))
print("    " + "".join(str(x % 10) for x in range(W)))
for y, r in enumerate(g):
    print(f"{y:2d}  " + "".join(r))
