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
Pokémon Center, L the Poké Mart, X Pokémon Tower (drawn in make_art.py), H the Volunteer House, U and W the two houses;
and Lavender's own ground (Kanto Lavender Town v0.1, ../kit/lavender.py): σ slate, γ gravel, λ lavender beds. The
railings, the gate, the lanterns, the memorial stones, the lamps and Mr. Fuji's yard stand on them (make_art.py).
The roads are slate too, to the edge: there the slate's join to the cobble meets the routes' cobble roads.
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
rect(12, 0, 16, 8, "σ")                        # Route 10's road (columns 12-16), slate like the town
rect(0, 9, 9, 11, "σ")                         # Route 8's (rows 9-11)
rect(10, 9, 20, 14, "σ")                       # the square, in slate
rect(12, 15, 15, 31, "σ")                      # Route 12's road (columns 12-15, as wide as its road below)
rect(21, 9, 31, 11, "σ")                       # the walk east to the tower (to its east wall), in slate
at(11, 8, "S")                                 # the town sign, read from the square (11,9)

# the north side: the Center and the Mart either side of the road from Route 10
rect(5, 3, 9, 6, "Z")                          # the Pokémon Center, door 7,6
rect(7, 7, 7, 8, "σ")
rect(18, 3, 21, 6, "L")                        # the Poké Mart, door 19,6
rect(19, 7, 19, 8, "σ")  # the Mart's path, slate as the square it leads to
rect(2, 2, 3, 3, "R"); rect(23, 2, 24, 3, "R"); at(10, 3, "b"); at(11, 3, "b")

# Pokémon Tower on its rise in the east, its sign and the Silph Scope notice on the path up, the garden before it
rect(27, 2, 31, 8, "X")                        # the tower, door 29,8
at(26, 8, "S")                                 # its sign, read from 26,9
at(23, 8, "S")                                 # the Silph Scope notice, read from 23,9
# the garden of remembrance, from the walk down to the town's south edge: lavender in rows, a gravel path down the
# middle from the gate to the edge (it crosses the lawn between the benches at row 17), three across it, and gravel
# round its stones (make_art.py puts them there); its two trees stay, for shade
rect(22, 13, 35, 16, "λ"); rect(22, 18, 35, 29, "λ")
rect(22, 15, 35, 15, "γ"); rect(22, 21, 35, 21, "γ"); rect(22, 26, 35, 26, "γ"); rect(28, 12, 30, 29, "γ")
for x, y in ((23, 14), (26, 14), (32, 14), (33, 14), (23, 19), (34, 19), (23, 23), (25, 23), (32, 23), (34, 23),
             (25, 24), (34, 24), (23, 28), (25, 28), (32, 28), (34, 28)):
    at(x, y, "γ")
rect(32, 3, 34, 7, "λ"); rect(33, 9, 34, 10, "b")  # lavender beside the tower; the railing runs on east of the bushes

# west of the square: the Volunteer House, its sign; the two houses in the south-west
rect(3, 13, 7, 16, "H")                        # Mr. Fuji's Volunteer Pokémon House, door 5,16
at(8, 16, "S")                                 # its sign, read from 8,17
rect(3, 21, 6, 24, "U")                        # a house, door 4,24
rect(8, 21, 11, 24, "W")                       # the Name Rater's, door 9,24
rect(2, 27, 3, 28, "R"); rect(9, 27, 10, 28, "R"); rect(2, 18, 9, 18, "b")

# east of the road south: lawns, trees, a bed of flowers
rect(17, 20, 20, 22, "λ"); rect(26, 22, 27, 23, "R"); rect(31, 19, 32, 20, "R")  # (the garden's two trees)
at(19, 26, "o")
# a little colour on the plain lawns (polish): a bed of flowers in the south-west yard between its trees and one on
# the east lawn, daisies in the grass south of the flower bed, a lamp by the road south
rect(6, 28, 7, 28, "*")
rect(17, 27, 18, 27, ","); at(18, 28, ",")  # (the lamps by the road south: make_art.py)

# the forest is drawn in 2x2 cells on the even grid: where a road's edge cuts a cell in half, a hedge or a lawn verge
# instead of half a tree (beside Route 10's road at 17,0-1; above Route 8's at 0-1,8)
at(17, 0, "b"); at(17, 1, "b")
at(0, 8, "b"); at(1, 8, ".")

Path(__file__).with_name("plan_stage1.txt").write_text("".join("".join(r) + "\n" for r in g))
print("    " + "".join(str(x % 10) for x in range(W)))
for y, r in enumerate(g):
    print(f"{y:2d}  " + "".join(r))
