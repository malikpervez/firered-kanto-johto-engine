#!/usr/bin/env python3
"""Draws Lavender Town's block plan (plan_stage1.txt): the concept, as shapes. Edit the shapes here and run it again;
make_art.py builds the map from the plan. Run from the repository root:
python3 project/art/lavender-concept/draw_plan.py

Lavender is the quiet town in a hollow of the hills, where people come to remember their Pokémon. It is 38x32 blocks
(old Lavender was 38x31), as wide as before. Route 10's road meets the top at columns 12-16, where it met the old
town, and Route 8's the left edge at rows 9-11; Route 12's road meets the bottom at columns 13-15, under the square
(Route 12 moves 4 blocks east under the town to meet it). It has:
- **the square**, where the three roads meet: the Pokémon Center and the Poké Mart on its north side either side of
  the road from Route 10, the town sign, the Friends' camp (round 13,13, as before);
- **Pokémon Tower** in the east on its rise, the tallest building in Kanto's east, its sign and the Silph Scope notice
  on the path up to it, and the garden of remembrance before it (flowers and stones);
- **Mr. Fuji's Volunteer Pokémon House** west of the square with its sign, and two houses in the south-west (the Name
  Rater's among them);
- **the road south** to Route 12, between lawns and the town's few trees.

Letters: the kit's legend (T forest, . lawn, = cobble, * flowers, o stones, b bushes, R trees, S signs), Z the
Pokémon Center, L the Poké Mart, X Pokémon Tower (drawn in make_art.py), H the Volunteer House, U and W the two houses.
"""
from pathlib import Path

W, H = 38, 32
g = [["." for _ in range(W)] for _ in range(H)]


def rect(x0, y0, x1, y1, c):
    for y in range(y0, y1 + 1):
        for x in range(x0, x1 + 1):
            g[y][x] = c


def at(x, y, c):
    g[y][x] = c


# the frame: the hills' forest round the hollow, open at the three roads
rect(0, 0, 37, 1, "T")
rect(0, 0, 1, 31, "T")
rect(36, 0, 37, 31, "T")
rect(0, 30, 37, 31, "T")

# the roads and the square
rect(12, 0, 16, 8, "=")                        # Route 10's road (columns 12-16)
rect(0, 9, 9, 11, "=")                         # Route 8's (rows 9-11)
rect(10, 9, 20, 14, "=")                       # the square
rect(13, 15, 15, 31, "=")                      # Route 12's road (columns 13-15)
rect(21, 9, 30, 11, "=")                       # the path east to the tower
at(11, 8, "S")                                 # the town sign, read from the square (11,9)

# the north side: the Center and the Mart either side of the road from Route 10
rect(5, 3, 9, 6, "Z")                          # the Pokémon Center, door 7,6
rect(7, 7, 7, 8, "=")
rect(18, 3, 21, 6, "L")                        # the Poké Mart, door 19,6
rect(19, 7, 19, 8, "=")
rect(2, 2, 3, 3, "R"); rect(23, 2, 24, 3, "R"); at(10, 3, "b"); at(11, 3, "b")

# Pokémon Tower on its rise in the east, its sign and the Silph Scope notice on the path up, the garden before it
rect(27, 2, 31, 8, "X")                        # the tower, door 29,8
at(26, 8, "S")                                 # its sign, read from 26,9
at(23, 8, "S")                                 # the Silph Scope notice, read from 23,9
rect(22, 13, 34, 16, "*")                      # the garden of remembrance
for x in (23, 26, 29, 32):
    at(x, 14, "o")                             # its stones
rect(32, 3, 34, 7, "*"); rect(33, 9, 34, 11, "b")

# west of the square: the Volunteer House, its sign; the two houses in the south-west
rect(3, 13, 7, 16, "H")                        # Mr. Fuji's Volunteer Pokémon House, door 5,16
at(8, 16, "S")                                 # its sign, read from 8,17
rect(3, 21, 6, 24, "U")                        # a house, door 4,24
rect(8, 21, 11, 24, "W")                       # the Name Rater's, door 9,24
rect(2, 27, 3, 28, "R"); rect(9, 27, 10, 28, "R"); rect(2, 18, 9, 18, "b")

# east of the road south: lawns, trees, a bed of flowers
rect(18, 20, 22, 22, "*"); rect(26, 22, 27, 23, "R"); rect(31, 19, 32, 20, "R"); rect(30, 26, 31, 27, "R")
at(19, 26, "o"); at(24, 28, "o")

Path(__file__).with_name("plan_stage1.txt").write_text("".join("".join(r) + "\n" for r in g))
print("    " + "".join(str(x % 10) for x in range(W)))
for y, r in enumerate(g):
    print(f"{y:2d}  " + "".join(r))
