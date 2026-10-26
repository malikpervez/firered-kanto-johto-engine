#!/usr/bin/env python3
"""Draws Celadon City's block plan (plan_stage1.txt): the concept, as shapes. Edit the shapes here and run it again;
make_art.py builds the map from the plan. Run from the repository root:
python3 project/art/celadon-concept/draw_plan.py

Celadon is Kanto's garden city, the city of rainbow dreams: a broad boulevard through it from Route 16 in the west to
Route 7 in the east, its grand buildings along it, and gardens behind them. It is 60x40 blocks, as old Celadon was.
Route 16's road (its rows 22-25) and Route 7's (its rows 10-13) meet the boulevard at rows 20-23. It has:
- **the boulevard**, four blocks of road between broad pavements (rows 19-24), the town sign by the east entrance;
- **the Department Store** on its north side, tall, with its two doors onto the pavement and its sign;
- **the Celadon Mansion** beside it, its back door onto the garden behind it (reached up the path beside it), the
  softboiled tutor on its east side;
- **the hotel** and the **Pokémon Center** further east, the fat man and his Poliwrath between them; behind the
  Center, **a walled garden** behind a tree to cut, with the Ether and a hidden PP Up;
- **Lucky Lane** south of the boulevard, with the **Game Corner**, its **Prize Room**, the restaurant and a house
  along it, their signs by their doors;
- **Erika's Gym** in the south-west, a glasshouse in a walled flower garden, behind the second tree to cut;
- **the pond garden** south of Lucky Lane, where the Friends camp and the researchers come with their Meowth.

The west seven columns are forest and road only, as old Route 16 needed (it had little room for more of this strip;
Route 16 is from the kit now).

Letters: the kit's legend (T forest, . lawn, = cobble, * flowers, ~ pond, b bushes, R trees, S signs), D the
Department Store, M the Mansion, O the hotel, C the Pokémon Center, G the Game Corner, P its Prize Room, E the
restaurant, H the house, Y Erika's Gym.
"""
from pathlib import Path

W, H = 60, 40
g = [["." for _ in range(W)] for _ in range(H)]


def rect(x0, y0, x1, y1, c):
    for y in range(y0, y1 + 1):
        for x in range(x0, x1 + 1):
            g[y][x] = c


def at(x, y, c):
    g[y][x] = c


# the frame: forest, open at the boulevard's two ends; the west band forest and road only
rect(0, 0, 59, 1, "T")
rect(0, 38, 59, 39, "T")
rect(0, 0, 6, 39, "T")
rect(58, 0, 59, 39, "T")
rect(7, 2, 17, 10, "T")                        # the wood behind the store

# the boulevard: pavements (rows 19 and 24) either side of the road (rows 20-23), open at both edges
rect(0, 20, 59, 23, "=")
rect(7, 19, 57, 19, "=")
rect(7, 24, 57, 24, "=")

# the north side: the store, the Mansion, the hotel and the Center, doors onto the pavement
rect(8, 12, 17, 18, "D")                       # the Department Store, doors 10,18 and 15,18
at(18, 18, "S")                                # its sign
rect(22, 11, 29, 18, "M")                      # the Mansion, front door 25,18, back door 25,11
at(30, 18, "S")                                # its sign
rect(33, 14, 38, 18, "O")                      # the hotel, door 35,18
rect(47, 15, 51, 18, "C")                      # the Pokémon Center, door 49,18
at(45, 18, "S")                                # trainer tips
at(55, 18, "S")                                # the town sign, by the east entrance
rect(40, 13, 41, 14, "R"); rect(43, 13, 44, 14, "R"); rect(53, 15, 54, 16, "R")
rect(31, 3, 32, 4, "R"); rect(36, 6, 37, 7, "R"); rect(40, 4, 41, 5, "R")
rect(19, 3, 20, 4, "R")
rect(22, 4, 28, 6, "*"); rect(34, 9, 39, 10, "*"); rect(27, 8, 28, 9, "R")   # the back garden's beds

# behind the Center: the walled garden, its hedge's gap closed by a tree to cut (50,13)
rect(45, 2, 57, 2, "T")
rect(45, 3, 45, 13, "b")
rect(45, 13, 57, 13, "b")
at(50, 13, ".")                                # the tree to cut stands here
rect(47, 4, 55, 11, "*")
rect(49, 6, 53, 9, ".")

# Lucky Lane, south of the boulevard, joined to it at both its ends
rect(20, 30, 55, 31, "=")
rect(20, 25, 21, 29, "=")
rect(54, 25, 55, 29, "=")
rect(24, 25, 32, 29, "G")                      # the Game Corner, door 28,29
at(33, 29, "S")                                # its sign
rect(34, 26, 37, 29, "P")                      # the Prize Room, door 35,29
at(38, 29, "S")                                # the prize exchange sign
rect(39, 26, 43, 29, "E")                      # the restaurant, door 41,29
rect(45, 26, 48, 29, "H")                      # a house, door 46,29
at(52, 29, "S")                                # trainer tips
rect(22, 25, 23, 26, "R"); rect(50, 26, 51, 27, "R")

# Erika's Gym: a glasshouse in its walled flower garden, the hedge's gap closed by the second tree to cut (12,25)
rect(7, 25, 18, 25, "b")
rect(7, 25, 7, 37, "b")
rect(18, 25, 18, 37, "b")
rect(7, 37, 18, 37, "b")
at(12, 25, ".")                                # the tree to cut stands here
rect(9, 30, 15, 34, "Y")                       # the Gym, door 12,34
at(14, 35, "S")                                # its sign
rect(8, 26, 10, 28, "*"); rect(14, 26, 17, 28, "*"); rect(8, 35, 10, 36, "*"); rect(16, 33, 17, 36, "*")

# the pond garden south of Lucky Lane: the Friends' camp round 25,34, the pond, flowers
rect(29, 33, 34, 35, "~")
rect(19, 36, 21, 37, "*"); rect(36, 33, 39, 34, "*"); rect(44, 35, 47, 36, "*")
rect(52, 33, 53, 34, "R"); rect(41, 32, 42, 33, "R")

Path(__file__).with_name("plan_stage1.txt").write_text("".join("".join(r) + "\n" for r in g))
print("    " + "".join(str(x % 10) for x in range(W)))
for y, r in enumerate(g):
    print(f"{y:2d}  " + "".join(r))
