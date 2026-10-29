#!/usr/bin/env python3
"""Draws Pewter City's block plan (plan_stage1.txt): the concept, as shapes. Edit the shapes here and run it again;
make_art.py builds the map from the plan. Run from the repository root:
python3 project/art/pewter-concept/draw_plan.py

Pewter is the grey-stone town at the foot of the mountains: cliffs close it in to the north and the north-east, the
forest to the west and south. The Museum of Science stands against the northern cliff over a paved plaza, its annex
in a yard behind a tree to cut; the Gym stands in the west with a paved forecourt; the Pokémon Center and the Mart
face each other across a square on the main street, which runs from Route 2's road (the bottom, columns 22-25) up to
the plaza. The road east to Route 3 (rows 24-27) runs between the north-eastern cliff and the forest, past the Gym
guide and Oak's aide, where they've always stood.

Letters: the kit's legend (T forest, . lawn, = cobblestones, p paving, % brick (the street pack's, in the Museum's
stone: paths through the paving and sidewalks by the main street; u a lamp and t a sign standing in it; y a sign on
the paving), # fence, b bushes, * flowers, o rocks,
l lamps (two blocks: the head above the foot), S signs), C cliffs, and the buildings: U the Museum, Y its annex,
W the Gym, Z the Pokémon Center, L the Poké Mart, H and X the two houses (Y, H and X are the same house); 1 and 2
the cottages without doors (the same house again, a window where its door was, in a slate and a clay recolour).
"""
from pathlib import Path

W, H = 52, 44
g = [["." for _ in range(W)] for _ in range(H)]


def rect(x0, y0, x1, y1, c):
    for y in range(y0, y1 + 1):
        for x in range(x0, x1 + 1):
            g[y][x] = c


def at(x, y, c):
    g[y][x] = c


# the frame: cliffs to the north and north-east, the forest west and south
rect(0, 0, 51, 5, "C")             # the northern cliff, its face on rows 4-5
rect(0, 6, 15, 13, "C")            # stepping down to the west, its face on rows 12-13
rect(42, 6, 51, 23, "C")           # the north-eastern cliff, down to the road east (its face on rows 22-23)
rect(0, 14, 3, 43, "T")            # the forest west
rect(0, 38, 21, 43, "T")           # and south, either side of Route 2's road
rect(26, 38, 39, 43, "T")
rect(40, 28, 51, 43, "T")          # the forest south of the road east
rect(36, 34, 39, 37, "T")

# the Museum of Science against the cliff, its plaza, the annex's yard behind a tree to cut
rect(17, 6, 31, 12, "U")           # door (24,12)
rect(16, 13, 32, 15, "p")          # the plaza
rect(4, 14, 15, 15, ".")
rect(35, 7, 39, 10, "Y")           # the annex, door (37,10)
rect(33, 13, 41, 13, "#")          # the yard's fence; the tree to cut stands in its gap at (32,13)
rect(32, 6, 32, 12, ".")
rect(16, 6, 16, 11, "b")           # behind the lamp west of the Museum
rect(40, 6, 41, 12, "b")
at(33, 6, "*"); at(34, 6, "*"); at(33, 8, "o"); at(33, 11, "*"); at(34, 11, "*")
rect(37, 11, 37, 12, ":")          # the path to the annex's door
at(16, 13, "l"); at(16, 12, "l")   # lamps either side of the plaza
at(32, 15, "S")                    # the museum's sign, east of the plaza (read from 32,16)

# the Gym in the west, its forecourt, the road to it
rect(6, 16, 12, 20, "W")           # door (9,20)
rect(5, 21, 13, 22, "p")
at(13, 20, "S")                    # the Gym's sign
rect(14, 22, 21, 23, "%")          # the sidewalk west to the Gym
rect(4, 16, 5, 20, "b")
rect(13, 16, 15, 19, "*")

# the main street from Route 2's road up to the plaza, the square, the road east
rect(22, 16, 25, 43, "=")
rect(26, 24, 51, 27, "=")          # the road east to Route 3
rect(26, 33, 35, 34, "%")          # the square's walk, a sidewalk past the Center and the Mart
rect(27, 29, 31, 32, "Z")          # the Pokémon Center, door (29,32)
rect(33, 29, 36, 32, "L")          # the Poké Mart, door (34,32)
at(32, 29, "l"); at(32, 28, "l")
rect(26, 35, 35, 37, ".")
rect(27, 36, 30, 36, "*")
at(37, 32, "S")                    # trainer tips, by the Mart

# the houses
rect(28, 17, 32, 20, "H")          # by the plaza, door (30,20)
rect(30, 21, 30, 23, "%")          # its path down to the road east
rect(8, 30, 12, 33, "X")           # in the south-west, door (10,33)
rect(10, 34, 10, 34, "%")
rect(5, 35, 21, 36, "%")           # the lane to it, a sidewalk
rect(4, 28, 7, 29, "*")
at(14, 30, "o"); at(16, 27, "o"); at(5, 25, "o")

# the guide's corner by the road east: lawn round the Museum guide (39,17), the road's edges closed
rect(33, 14, 41, 21, ".")
rect(33, 22, 41, 23, "b")          # the road east can only be left by its own rows
at(36, 17, "o"); at(34, 19, "*"); at(35, 19, "*")
at(39, 23, "S")                    # the police notice, by the road east (read from 39,24)

# the city sign by Route 2's road
at(26, 35, "S")                    # read from (26,36)
rect(14, 24, 21, 34, ".")
rect(26, 28, 26, 32, ".")

# more homes: cottages without doors (no new tiles: the family house's own, recoloured), off the guides' walks and
# the people's places, and lamps along the main street
rect(15, 16, 19, 19, "1")          # slate, beside the Gym
rect(8, 25, 12, 28, "2")           # clay, above the south-west house
rect(15, 29, 19, 32, "1")          # slate, by the lane
for x, y in ((21, 19), (26, 19), (21, 32), (26, 31)):
    rect(x, y - 1, x, y, "l")      # a lamp: its post's foot at x, y
at(5, 14, "o"); at(4, 24, "o")

# the west side is paved, no lawn: the plaza's dressed stone from the forest to the main street, round the Gym, the
# cottages and the house (their rocks, flowers and bushes gone), with brick paths through it (the Gym's walk, the
# lane, the house's doorstep) and the sidewalk by the street
for y in range(14, 38):
    for x in range(4, 22):
        if g[y][x] in ".,*ob:":
            g[y][x] = "p"
at(13, 20, "y")                    # the Gym's sign, on the paving
# the sidewalks: brick either side of the main street, from the plaza down to the forest, the walk past the Center
# and the Mart and the house's forecourt by the road east; the lamps and the city sign stand in them
for r in ((20, 16, 21, 37),                                                             # west of the street
          (26, 16, 28, 16), (26, 17, 27, 20), (26, 21, 32, 23), (26, 28, 31, 28),       # east of it
          (26, 29, 26, 32), (26, 35, 28, 37)):
    rect(*r, "%")
for x, y in ((21, 19), (26, 19), (21, 32), (26, 31)):
    rect(x, y - 1, x, y, "u")
at(26, 35, "t")

Path(__file__).with_name("plan_stage1.txt").write_text("".join("".join(r) + "\n" for r in g))
print("\n".join("".join(r) for r in g))
