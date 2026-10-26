#!/usr/bin/env python3
"""Draws Route 8's block plan (plan_stage1.txt): the concept, as shapes. Edit the shapes here and run it again;
make_art.py builds the map from the plan. Run from the repository root:
python3 project/art/route8-concept/draw_plan.py

Route 8 is the road west from Lavender to Saffron's east gate, where Lavender's townsfolk come out to race and to
gamble. It is 60x30 blocks (old Route 8 was 68x40, half of it mountain). Lavender's street meets the right edge at rows
13-15; Saffron lies beyond the left edge, reached only through the gate (its door 10-11,12). It has:
- **the road** of cobbles from Lavender to the gate, in no trainer's sight, the Underground Path's hut north of it
  with its sign: the way under Saffron to Route 7 and Celadon, as Saffron's gates are shut;
- **the stands** west of the track, where the gamblers Rich and Stan watch the race;
- **the old race track**, a loop of dirt the bikers Ricardo and Jaren ride round and round, one chasing the other,
  round a hedged berry garden (three berries hidden in it) behind a tree to cut, where Growlithe and Vulpix play;
- **the pine grove** in the north-east, where the twins Eli and Anne stand together (and Duskull at night);
- **the grass field** south-west of the road, Aidan at its edge;
- **the picnic lawn** south of the road, where Paige, Leslie, Andrea and Megan stand in their row looking out both
  ways, Glenn and Julia further east;
- **the meadow** of grass in the south-east behind a hedge and the second tree to cut, Kadabra in it.

Every block is at least 7 in from the left edge, so the camera never shows old Saffron across it (no seam: KR-34).
The trees to cut stand more than 8 blocks from the right edge (the game hides one nearer the edge you come in by).

Letters: the kit's legend (T forest, . lawn, = cobble, : dirt, g grass, * flowers, o rocks, b bushes, R trees,
S signs), F Saffron's east gate (Route 2's south forest gate), U the Underground Path's hut (Viridian's pond keeper's
house).
"""
from pathlib import Path

W, H = 60, 30
g = [["." for _ in range(W)] for _ in range(H)]


def rect(x0, y0, x1, y1, c):
    for y in range(y0, y1 + 1):
        for x in range(x0, x1 + 1):
            g[y][x] = c


def at(x, y, c):
    g[y][x] = c


# the frame: the hills' forest, open at Lavender's street; the west deep, so old Saffron is never in view
rect(0, 0, 59, 1, "T")
rect(0, 28, 59, 29, "T")
rect(0, 0, 6, 29, "T")
rect(58, 0, 59, 29, "T")
rect(7, 2, 14, 6, "T")                         # the forest over the gate

# the road, Lavender's street (rows 13-15) to the gate
rect(7, 13, 59, 15, "=")
rect(7, 7, 14, 12, "F")                        # Saffron's east gate, doors 10-11,12

# the stands, and the Underground Path's hut with its sign
rect(17, 9, 20, 12, "U")                       # the hut, door 18,12
at(21, 12, "S")                                # its sign, read from 21,13
rect(16, 3, 17, 4, "R"); rect(20, 2, 21, 3, "R")
rect(24, 5, 24, 9, "b")                        # the rail before the stands (Rich and Stan behind it)
at(24, 7, ".")

# the race track: a loop of dirt round the hedged berry garden (its outer edge 16x9, the most a walker's range can
# go round), the garden's gap closed by a tree to cut (36,9)
rect(28, 3, 43, 11, ":")
rect(30, 5, 41, 9, "b")
rect(31, 6, 40, 8, "*")
at(36, 9, ".")                                 # the tree to cut stands here

# the pine grove in the north-east
for x, y in ((49, 3), (53, 2), (56, 5), (49, 7), (54, 8), (50, 11)):
    rect(x, y, x + 1, y + 1, "R")

# the grass field south-west of the road
rect(9, 18, 20, 26, "g")
rect(8, 17, 8, 17, "o"); at(21, 26, "o")

# the picnic lawn: a cloth of flowers between the row of four and the trees
rect(24, 18, 27, 23, "*")
rect(33, 18, 34, 19, "R"); rect(33, 24, 34, 25, "R")

# the meadow in the south-east, behind its hedge and the second tree to cut (46,23)
rect(36, 23, 57, 23, "b")
at(46, 23, ".")                                # the tree to cut stands here
rect(37, 24, 57, 27, "g")
rect(36, 24, 36, 27, "b")
rect(40, 18, 41, 19, "R"); at(50, 17, "o")

Path(__file__).with_name("plan_stage1.txt").write_text("".join("".join(r) + "\n" for r in g))
print("    " + "".join(str(x % 10) for x in range(W)))
for y, r in enumerate(g):
    print(f"{y:2d}  " + "".join(r))
