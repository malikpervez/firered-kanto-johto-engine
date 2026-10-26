#!/usr/bin/env python3
"""Draws Route 9's block plan (plan_stage1.txt): the concept, as shapes. Edit the shapes here and run it again;
make_art.py builds the map from the plan. Run from the repository root:
python3 project/art/route9-concept/draw_plan.py

Route 9 is the hill road east from Cerulean to Rock Tunnel, for those who have Cut. It is 60x28 blocks (old Route 9
was 65x60, its top half solid mountain):
- **the way in**: Cerulean's cobbles carried on (rows 8-10 at the left edge, where its road east meets it), then a
  neck in the forest that the tree to cut closes;
- **the gorge**: the road between two cliffs, where a picnicker and a camper stand under the northern cliff and look
  straight across it: they can't be passed without a battle, as on the old route's upper path;
- **the west field** below the gorge's southern cliff, its grass and its two trainers off the road, reached from where
  the road turns south;
- **the outcrop**: a rocky hill the road turns south round, the Marowak by its foot, the middle field's grass below
  the road;
- **the terrace** in the east, up a flight of steps in its ledge (hop down it anywhere): two trainers, the Aron, and
  TM40 at its far end;
- **the road out**, east at rows 17-19 to Route 10 and Rock Tunnel's Pokémon Center.

Letters: the kit's legend (T forest, . lawn, = cobble, : dirt, g tall grass, _ ledges, h steps, * flowers, o rocks,
b bushes, S signs) and C cliffs.
"""
from pathlib import Path

W, H = 60, 28
g = [["." for _ in range(W)] for _ in range(H)]


def rect(x0, y0, x1, y1, c):
    for y in range(y0, y1 + 1):
        for x in range(x0, x1 + 1):
            g[y][x] = c


def at(x, y, c):
    g[y][x] = c


# the frame: forest round the route; the neck the tree to cut closes (the tree at 9,9: the game hides a tree to cut
# that is within 8 blocks of the edge you come in by, so it stands further in)
rect(0, 0, 59, 1, "T")
rect(0, 0, 3, 27, "T")
rect(56, 0, 59, 27, "T")
rect(0, 25, 59, 27, "T")
rect(4, 0, 9, 24, "T")
rect(0, 8, 3, 10, "=")                        # Cerulean's cobbles (rows 8-10)
rect(4, 8, 9, 10, "b")                        # the neck: bushes either side of it,
rect(4, 9, 9, 9, ":")                         # and the tree in it, at 9,9

# the gorge: the northern cliff (its face on rows 4-5), the road, the southern cliff (its top against the road)
rect(10, 0, 55, 5, "C")
rect(10, 6, 24, 6, ".")                       # where the gorge's two trainers stand, under the cliff
rect(10, 7, 24, 9, ":")                       # the road
rect(10, 10, 20, 13, "C")                     # the southern cliff, its face on rows 12-13 over the west field
at(11, 6, "S")                                # the route sign, read from the road (11,7)

# the road turns south round the outcrop, then east under it
rect(25, 0, 40, 12, "C")                      # the outcrop, its face on rows 11-12
rect(21, 10, 24, 16, ":")
rect(21, 15, 44, 17, ":")
rect(25, 13, 40, 14, ".")                     # the outcrop's foot
at(27, 13, "o"); at(38, 14, "o")
rect(40, 17, 59, 19, ":")                     # the road out (rows 17-19 at the right edge)

# the west field, below the southern cliff
rect(11, 16, 19, 22, "g")
rect(10, 23, 12, 24, "*"); at(15, 23, "o"); at(20, 14, "o")

# the middle field, below the road
rect(26, 19, 39, 23, "g")
rect(22, 21, 24, 23, "*"); at(41, 23, "o")

# the terrace in the east: its ledge (row 14), the steps up it (43,14), flowers and rocks on it
rect(41, 6, 55, 13, ".")
rect(41, 14, 55, 14, "_")
at(43, 14, "h")
rect(53, 6, 55, 8, "*"); at(45, 7, "o"); at(46, 7, "o"); at(51, 12, "b"); at(55, 12, "b")

# south of the road out: a lawn with rocks and a bush row by the forest
rect(40, 20, 55, 24, ".")
rect(44, 24, 50, 24, "b"); at(53, 21, "o")

Path(__file__).with_name("plan_stage1.txt").write_text("".join("".join(r) + "\n" for r in g))
print("    " + "".join(str(x % 10) for x in range(W)))
for y, r in enumerate(g):
    print(f"{y:2d}  " + "".join(r))
