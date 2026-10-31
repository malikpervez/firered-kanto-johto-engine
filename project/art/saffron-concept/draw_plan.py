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
  Pokémon Trainer Fan Club, shops between them; below it Saffron Park's pond in the south-west and the city's towers.
The city is paved block by block (FireRed's Saffron is), and between the buildings you can enter stand offices and
arcades without doors (KR-88).

The gatehouses: the north, west and east ones have their double door on their south face, onto the avenue; the south
one is entered walking south, through a doorway in its roof's back edge. No tree is cut and nothing is surfed here.

Letters: the kit's legend (T forest, . lawn, = cobble, p paving, * flowers, ~ pond, b bushes, R trees, S signs),
X Silph Co., M the Magnet Train station, D the Fighting Dojo, G Sabrina's Gym, N/W/E the north, west and east
gatehouses, U the south one, Z the Pokémon Center, L the Mart, Y Copycat's house, H the house, P Mr. Psychic's house,
K the Trainer Fan Club; the doorless blocks (make_art.py's CITY): A and I sand offices (tall, mid), F and J brick ones,
V a narrow beige one, C a narrow brick one, a an arcade; l lamps.
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


def tree(x, y, c="R"):
    rect(x, y, x + 1, y + 1, c)                # "R" on lawn, "|" a street tree standing on the pavement


# the frame: forest, thicker along the south either side of the south gatehouse
rect(0, 0, 59, 1, "T")
rect(0, 45, 59, 47, "T")
rect(0, 0, 1, 47, "T")
rect(58, 0, 59, 47, "T")

# the avenues, asphalt ("+"): north-south from the north gatehouse to the south one, east-west between the west and
# east ones
rect(28, 2, 31, 44, "+")
rect(2, 22, 57, 25, "+")
rect(28, 0, 31, 2, "N")                        # the gatehouses: doors 29-30,2
rect(28, 45, 31, 47, "U")                      # doorway 29-30,45, entered walking south
rect(1, 19, 4, 21, "W")                        # doors 2-3,21
rect(55, 19, 58, 21, "E")                      # doors 56-57,21
rect(1, 18, 4, 18, "b")
rect(55, 18, 58, 18, "b")

# the north-west: a lane with Copycat's house and a house; the Dojo and the Gym on the Gym square
rect(2, 9, 27, 10, "+")                        # the lane, off the avenue
rect(4, 5, 4, 8, ".")                          # (a lawn beside Copycat's house)
rect(5, 5, 8, 8, "Y")                          # Copycat's house, door 6,8
rect(12, 5, 15, 8, "H")                        # the house, door 13,8
rect(18, 3, 23, 8, "J")                        # a brick office on the lane
tree(3, 3, "|"); tree(10, 3, "|")      # (a row in from the forest's verge)
at(27, 3, "S")                                 # the city sign, by the north gate
rect(2, 11, 27, 11, "b")
rect(4, 13, 10, 17, "D")                       # the Fighting Dojo, door 7,17
rect(14, 13, 20, 17, "G")                      # Sabrina's Gym, door 17,17
at(11, 17, "S")                                # the Dojo's sign
at(21, 17, "S")                                # the Gym's sign
rect(22, 12, 25, 17, "y")                      # a narrow office beside the Gym (V, with the hedge's lawn behind it)
rect(5, 18, 26, 20, "@")                       # the Gym square: granite ("@"), its pavement to the avenues

# the north-east: Silph Co. and the station on the Silph plaza, the garden behind
rect(34, 6, 42, 17, "X")                       # Silph Co., door 38,17
rect(46, 14, 53, 17, "M")                      # the Magnet Train station (no door)
at(33, 17, "S")                                # Silph's latest product
at(43, 17, "S")                                # Silph Co.'s sign
rect(33, 18, 53, 20, "@")                      # the Silph plaza: granite, the compass set in it
rect(43, 19, 44, 20, "/")
tree(32, 10, "|"); tree(35, 3, "|"); tree(40, 3, "|")
rect(45, 3, 48, 4, "*")                        # the garden: flowers, a pond, the Friends' lawn round 50,8
rect(53, 3, 56, 6, "~")
rect(54, 13, 57, 13, "b")
rect(54, 14, 57, 17, "u")                      # and east of the station (a, with lawn and forest behind it)
tree(55, 9)
for y in (6, 8, 10, 12):                       # the garden's trees along the pavement
    tree(43, y)
for x in (45, 47, 49, 51):
    tree(x, 12)

# the south street, its buildings facing it, the park below
rect(2, 31, 27, 32, "+")
rect(32, 31, 57, 32, "+")
rect(4, 27, 8, 30, "Z")                        # the Pokémon Center, door 6,30
at(9, 30, "S")                                 # trainer tips
rect(11, 27, 14, 30, "L")                      # the Mart, door 12,30
rect(18, 27, 21, 30, "P")                      # Mr. Psychic's house, door 19,30
at(22, 30, "S")                                # its sign
rect(34, 27, 34, 30, ".")                      # (a lawn beside the Fan Club)
rect(35, 27, 38, 30, "K")                      # the Trainer Fan Club, door 36,30
at(39, 30, "S")                                # its sign
at(53, 26, "S")                                # trainer tips, by the east gate
rect(23, 27, 26, 30, "a")                      # the shops along the south street
rect(41, 27, 44, 30, "a"); rect(46, 27, 49, 30, "a")
tree(54, 28, "|")

# Saffron Park: the pond in the south-west, flower gardens in the south-east
rect(5, 36, 11, 40, "~")
rect(2, 33, 11, 33, "b")                       # a hedge between the south street and the park's lawn
rect(4, 42, 10, 43, "*")
tree(3, 42); tree(22, 36, "|")
rect(13, 34, 16, 37, "a"); rect(18, 34, 21, 37, "a")  # shops by the park
rect(14, 39, 19, 44, "J")                      # offices along the park's south side
rect(21, 39, 24, 44, "V")
rect(33, 36, 38, 44, "A")                      # the towers of the south-east
rect(40, 36, 45, 44, "F")
tree(48, 36, "|"); tree(51, 36, "|")
rect(47, 39, 52, 44, "I")
rect(54, 35, 57, 40, "C")



# the city is paved (FireRed's Saffron is): every block between the streets but Saffron Park's west half and the
# garden behind Silph Co. is pavement ("&": its kerbs over the road); its lamps along the pavements
def pave(x0, y0, x1, y1):
    for y in range(y0, y1 + 1):
        for x in range(x0, x1 + 1):
            if g[y][x] in ".p":
                g[y][x] = "&"


pave(2, 2, 27, 8)
pave(2, 12, 27, 21)
pave(32, 2, 44, 21)
pave(45, 14, 54, 21)
pave(2, 26, 27, 30)
pave(32, 26, 57, 30)
pave(12, 33, 27, 44)
pave(32, 33, 57, 44)
# (each a block in from the kerb and the verge, on the plain paving its post is drawn on: on an edge its paving would
# break the kerb's rim)
for x, y in ((25, 7), (3, 7), (26, 14), (33, 29), (3, 29), (56, 28), (26, 35), (33, 35), (53, 35)):
    rect(x, y - 1, x, y, "l")                  # a lamp: its post's foot at x, y
rect(11, 41, 11, 42, "^")                      # a lamp on the park's lawn, by the pavement
# where the pavement meets lawn, forest, water or a hedge rather than the road, it's the pavement on grass ("$")
GRASSY = set("T.,*~bR")  # (the garden's trees stand on its lawn)
for y in range(H):
    for x in range(W):
        if g[y][x] == "&" and any(0 <= x + dx < W and 0 <= y + dy < H and g[y + dy][x + dx] in GRASSY
                                  for dx in (-1, 0, 1) for dy in (-1, 0, 1)):
            g[y][x] = "$"

# the paving that should keep its kerb: beside the east gatehouse (the column flows into the gate's paved base) and
# at the south gatehouse's corners onto the avenue
for x, y in ((54, 19), (27, 44), (32, 44)):
    at(x, y, "&")
# the two road corners by the east forest, where the corner lamps stood: plain paving to the trees with the kerb on
# the road side only ("e"), as under the lamps, so no grass sliver shows between the asphalt and the paving
for x, y in ((57, 26), (57, 33), (2, 26)):
    at(x, y, "e")
# and where such a corner has the road to its south ("n"): its kerb on the road side, not a verge against the asphalt
for x, y in ((2, 8), (2, 30), (57, 30)):
    at(x, y, "n")

# the road's markings: a dashed line down the middle of each avenue ("-", ";"), zebra crossings over the north-south
# avenue either side of the crossroads, their dropped kerbs ("6" "8") and ends ("2" "3"), and manholes ("%")
for y in range(3, 45):
    if y not in (9, 10, 22, 23, 24, 25, 26, 31, 32):  # (broken where the streets meet it)
        at(30, y, ";")
for x in list(range(2, 28)) + list(range(32, 58)):
    at(x, 24, "-")
for y in (17, 27):  # (the south one a row clear of the cross avenue, so its dropped kerbs meet a straight kerb)
    at(27, y, "6"); at(28, y, "2"); at(29, y, "0"); at(30, y, "0"); at(31, y, "3"); at(32, y, "8")
for x, y in ((15, 23), (44, 25), (29, 7), (29, 37)):
    at(x, y, "%")

Path(__file__).with_name("plan_stage1.txt").write_text("".join("".join(r) + "\n" for r in g))
