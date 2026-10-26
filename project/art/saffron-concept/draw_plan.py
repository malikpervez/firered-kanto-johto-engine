#!/usr/bin/env python3
"""Draws Saffron City's block plan (plan_stage1.txt): the concept, as shapes. Edit the shapes here and run it again;
make_art.py builds the map from the plan. Run from the repository root:
python3 project/art/saffron-concept/draw_plan.py

Saffron is Kanto's golden city of commerce, at the crossroads of the region: two avenues cross in its middle, each
ending at a stone gatehouse, the way out to Routes 5, 6, 7 and 8 (the guards inside them let you through once they
have had a drink). It is 60x48 blocks (old Saffron was 66x55). Its joins aren't compiled (the routes see its twin,
SaffronCity_Connection), so nothing beyond its edges shows but its border's forest, and its size is its own. It has:
- **the north-west**: Copycat's house and a house on a lane off the avenue; the Fighting Dojo and Sabrina's Gym side by
  side on the Gym square, its paving running to the avenue;
- **the north-east**: Silph Co.'s tower, the tallest building in Kanto, and the Magnet Train station beside it on the
  Silph plaza (the attendant outside it arranges the journey to Goldenrod, and the train comes in there); behind them
  a garden where the Friends camp;
- **the south**, along a street parallel to the avenue: the Pokémon Center, the Mart, Mr. Psychic's house and the
  Pokémon Trainer Fan Club; below it Saffron Park with its pond in the south-west and flower gardens in the south-east.

The gatehouses: the north, west and east ones have their double door on their south face, onto the avenue; the south
one is entered walking south, through a doorway in its roof's back edge. No tree is cut and nothing is surfed here.

Letters: the kit's legend (T forest, . lawn, = cobble, p paving, * flowers, ~ pond, b bushes, R trees, S signs),
X Silph Co., M the Magnet Train station, D the Fighting Dojo, G Sabrina's Gym, N/W/E the north, west and east
gatehouses, U the south one, Z the Pokémon Center, L the Mart, Y Copycat's house, H the house, P Mr. Psychic's house,
K the Trainer Fan Club.
"""
from pathlib import Path

W, H = 60, 48
g = [["." for _ in range(W)] for _ in range(H)]


def rect(x0, y0, x1, y1, c):
    for y in range(y0, y1 + 1):
        for x in range(x0, x1 + 1):
            g[y][x] = c


def at(x, y, c):
    g[y][x] = c


def tree(x, y):
    rect(x, y, x + 1, y + 1, "R")


# the frame: forest, thicker along the south either side of the south gatehouse
rect(0, 0, 59, 1, "T")
rect(0, 45, 59, 47, "T")
rect(0, 0, 1, 47, "T")
rect(58, 0, 59, 47, "T")

# the avenues: north-south from the north gatehouse to the south one, east-west between the west and east ones
rect(28, 2, 31, 44, "=")
rect(2, 22, 57, 25, "=")
rect(28, 0, 31, 2, "N")                        # the gatehouses: doors 29-30,2
rect(28, 45, 31, 47, "U")                      # doorway 29-30,45, entered walking south
rect(1, 19, 4, 21, "W")                        # doors 2-3,21
rect(55, 19, 58, 21, "E")                      # doors 56-57,21
rect(1, 18, 4, 18, "b")
rect(55, 18, 58, 18, "b")

# the north-west: a lane with Copycat's house and a house; the Dojo and the Gym on the Gym square
rect(2, 9, 27, 10, "=")                        # the lane, off the avenue
rect(4, 5, 8, 8, "Y")                          # Copycat's house, door 6,8
rect(12, 5, 15, 8, "H")                        # the house, door 13,8
rect(18, 4, 24, 6, "*")
tree(3, 2); tree(10, 2); tree(25, 5); tree(19, 7)
at(27, 3, "S")                                 # the city sign, by the north gate
rect(2, 11, 27, 11, "b")
rect(4, 13, 10, 17, "D")                       # the Fighting Dojo, door 7,17
rect(14, 13, 20, 17, "G")                      # Sabrina's Gym, door 17,17
at(11, 17, "S")                                # the Dojo's sign
at(21, 17, "S")                                # the Gym's sign
tree(23, 13); tree(25, 15)
rect(2, 15, 3, 16, "*")
rect(5, 18, 27, 21, "p")                       # the Gym square

# the north-east: Silph Co. and the station on the Silph plaza, the garden behind
rect(34, 6, 42, 17, "X")                       # Silph Co., door 38,17
rect(46, 14, 53, 17, "M")                      # the Magnet Train station (no door)
at(33, 17, "S")                                # Silph's latest product
at(43, 17, "S")                                # Silph Co.'s sign
rect(32, 18, 54, 21, "p")                      # the Silph plaza
tree(32, 3); tree(32, 10); tree(43, 6); tree(43, 11)
rect(45, 3, 48, 4, "*")                        # the garden: flowers, a pond, the Friends' lawn round 50,8
rect(53, 3, 56, 6, "~")
rect(54, 13, 57, 13, "b")
tree(55, 9); tree(45, 11)

# the south street, its buildings facing it, the park below
rect(2, 31, 27, 32, "=")
rect(32, 31, 57, 32, "=")
rect(4, 27, 8, 30, "Z")                        # the Pokémon Center, door 6,30
at(9, 30, "S")                                 # trainer tips
rect(11, 27, 14, 30, "L")                      # the Mart, door 12,30
rect(18, 27, 21, 30, "P")                      # Mr. Psychic's house, door 19,30
at(22, 30, "S")                                # its sign
rect(34, 27, 38, 30, "K")                      # the Trainer Fan Club, door 36,30
at(39, 30, "S")                                # its sign
at(53, 26, "S")                                # trainer tips, by the east gate
rect(42, 27, 50, 28, "*")
tree(24, 27); tree(54, 28)

# Saffron Park: the pond in the south-west, flower gardens in the south-east
rect(5, 36, 11, 40, "~")
rect(15, 34, 20, 35, "*")
tree(3, 42); tree(13, 41); tree(22, 36); tree(25, 41); tree(16, 38)
rect(35, 35, 40, 37, "*")
rect(47, 35, 52, 37, "*")
rect(35, 41, 40, 42, "*")
rect(47, 41, 52, 42, "*")
tree(43, 38); tree(55, 35); tree(55, 41); tree(32, 41)

Path(__file__).with_name("plan_stage1.txt").write_text("".join("".join(r) + "\n" for r in g))
