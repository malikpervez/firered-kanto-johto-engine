#!/usr/bin/env python3
"""Draws Route 11's block plan (plan_stage1.txt): the concept, as shapes. Edit the shapes here and run it again;
make_art.py builds the map from the plan. Run from the repository root:
python3 project/art/route11-concept/draw_plan.py

Route 11 is the road east out of Vermilion to the gatehouse before Route 12:
- **the road**, Vermilion's cobbles carried on (rows 14-17 at the left edge, where its main street meets it), a dirt
  road east to Route 12 (rows 17-19 at the right edge). No trainer's sight is on it: Route 11's are for those who
  go looking;
- **Diglett's Cave** in the north-west, its mouth (Route 2's: the same cave) set into a rock ridge, its sign by it;
- **the Friends' clearing** east of the cave (their camp at 25,7, as before);
- **the north grass** and **the south grass**, where the gamblers and youngsters stand, and a pond in the south-east
  for the water Pokémon;
- **the gatehouse** (Route 2's south forest gate, like Saffron's) north of the road's east end: the way up to the
  Itemfinder, its two doors either half of its double door.

Letters: the kit's legend (T forest, . lawn, = cobble, : dirt, ~ pond, * flowers, b bushes, g tall grass, o rocks,
S signs), C cliffs, Y the cave mouth, X the gatehouse.
"""
from pathlib import Path

W, H = 60, 32
g = [["." for _ in range(W)] for _ in range(H)]


def rect(x0, y0, x1, y1, c):
    for y in range(y0, y1 + 1):
        for x in range(x0, x1 + 1):
            g[y][x] = c


def at(x, y, c):
    g[y][x] = c


# the frame: forest round the route, the rock ridge along the top-left with the cave's mouth set into it
rect(0, 0, 59, 2, "T")
rect(0, 0, 3, 31, "T")
rect(56, 0, 59, 31, "T")
rect(0, 28, 59, 31, "T")
rect(4, 0, 30, 4, "C")
rect(14, 2, 19, 6, "Y")                       # Diglett's Cave, door (16,6)
at(13, 6, "S")                                # its sign, read from (13,7)

# the road: cobbles in from Vermilion (rows 14-17), dirt east to Route 12 (rows 17-19)
rect(0, 14, 3, 17, "=")
rect(4, 14, 47, 17, ":")
rect(44, 17, 59, 19, ":")
rect(56, 16, 59, 16, "b")                      # a hedge along the road below the gatehouse (no half trees over it)

# the Friends' clearing (their camp at 25,7), the north grass, flowers and rocks
rect(21, 5, 28, 9, ".")
rect(20, 10, 22, 11, "*"); rect(28, 5, 29, 6, "*")
rect(32, 4, 46, 11, "g")
rect(5, 9, 9, 12, "*"); at(11, 11, "o"); at(30, 12, "o")

# the gatehouse north of the road's east end, its doors (53,15) and (54,15)
rect(50, 10, 57, 15, "X")
rect(48, 9, 49, 9, "b"); rect(52, 7, 55, 8, "*")

# the south grass, the pond, bushes along the road's south side
rect(6, 20, 32, 27, "g")
rect(42, 22, 53, 27, "~")
rect(4, 18, 40, 18, "b"); at(12, 18, "."); at(26, 18, "."); at(36, 18, ".")
rect(36, 21, 38, 22, "*"); at(54, 22, "o"); rect(34, 26, 36, 27, "*")

Path(__file__).with_name("plan_stage1.txt").write_text("".join("".join(r) + "\n" for r in g))
print("    " + "".join(str(x // 10 % 10) if x % 10 == 0 else " " for x in range(W)))
print("    " + "".join(str(x % 10) for x in range(W)))
for y, r in enumerate(g):
    print(f"{y:2d}  " + "".join(r))
