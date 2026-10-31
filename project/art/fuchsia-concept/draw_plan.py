#!/usr/bin/env python3
"""Draws Fuchsia City's block plan (plan_stage1.txt): the concept, as shapes. Edit the shapes here and run it again;
make_art.py builds the map from the plan. Run from the repository root:
python3 project/art/fuchsia-concept/draw_plan.py

Fuchsia is Kanto's town of the Safari Zone, by the southern sea. It is 48x40 blocks, as before, and its joins stay
where they were: Route 18's road (its rows 8-10) at the left edge, rows 18-20; Route 15's (its rows 4-7) at the right
edge, rows 20-23; Route 19's beach path (its columns 7-16) below the bottom edge, columns 19-28. It has:
- **the Safari plaza** at the top, under the woods: the Safari Zone's gate lodge, its game's notices;
- **the zoo** either side of the plaza, the pens of the Pokémon from the Safari Zone along two walks: the fossil
  Pokémon's pond and Lapras's lake to the west; Voltorb's, Kangaskhan's and Chansey's yards to the east;
- **the main street** across the town from Route 18 to Route 15, the avenue from the plaza meeting it: the Mart and
  the Safari Zone's office along it, Slowpoke dozing in the office's garden;
- **the park** south of it, the Friends' camp on its lawn;
- **the shore street** along the south, Koga's Gym, the houses, the Pokémon Center and the Warden's house along it;
  behind the house at its east end, a pond garden reached only by the house's back door;
- **the beach path** down from the shore street to Route 19's beach, through the woods.

Trees to cut close four short ways: the zoo's west walk to the main street, the east walk to the office's garden,
the park's flower garden, and the lane round the Warden's house.

Letters: the kit's legend (T forest, . lawn, = cobble, : dirt, p paving, g grass, * flowers, ~ pond, # fences,
b bushes, R trees, l lamps, S signs), and the buildings: A the Safari Zone's gate lodge, G Koga's Gym, Z the Pokémon
Center, L the Mart, O the Safari Zone's office, W the Warden's house, H and J houses, K the house with a back door.
"""
from pathlib import Path

W, H = 48, 40
g = [["T" for _ in range(W)] for _ in range(H)]


def rect(x0, y0, x1, y1, c):
    for y in range(y0, y1 + 1):
        for x in range(x0, x1 + 1):
            g[y][x] = c


def at(x, y, c):
    g[y][x] = c


def tree(x, y):
    rect(x, y, x + 1, y + 1, "R")


def lamp(x, y):  # the kit's lamp: a post two blocks tall
    rect(x, y, x, y + 1, "l")


# the town's ground, inside the woods (the woods keep to the even grid: whole forest cells)
rect(2, 2, 41, 33, ".")

# the main street from Route 18 (rows 18-20) to Route 15 (rows 20-23); the avenue up to the plaza
rect(0, 18, 40, 21, "=")
at(0, 21, "b")
rect(0, 16, 1, 17, "b")                         # bushes above the road at the edge, as Route 18 has them there
rect(40, 20, 47, 23, "=")
rect(21, 10, 26, 17, "p")

# the Safari plaza and the lodge (door 23,6), lamps either side
rect(18, 7, 26, 9, "p")
rect(18, 10, 20, 10, "p")                       # where the zoo's west walk meets it, beside the guardian statue
rect(20, 2, 26, 6, "A")
at(19, 6, "S")                                  # the Safari Zone's sign
at(27, 6, "S")                                  # the Safari Game's notice
lamp(18, 5)
lamp(28, 5)

# the zoo's west walk (rows 9-10) and its pens: the fossil Pokémon's pond, Lapras's lake
rect(2, 3, 8, 8, "#")
rect(3, 4, 7, 7, ".")
rect(4, 5, 6, 6, "~")
rect(10, 3, 17, 8, "#")
rect(11, 4, 16, 7, "~")
at(5, 8, "S")                                   # the fossil Pokémon's sign
at(13, 8, "S")                                  # Lapras's sign
rect(2, 9, 17, 10, ":")
rect(2, 11, 17, 11, "b")                        # the walk's hedge, the tree to cut in it at 9,11
at(9, 11, ".")

# the zoo's east walk (rows 9-10) and its yards: Voltorb's, Kangaskhan's, Chansey's
rect(30, 3, 34, 8, "#")
rect(31, 4, 33, 7, ":")
rect(36, 3, 40, 8, "#")
rect(37, 4, 39, 7, ":")
rect(29, 9, 40, 10, ":")
at(32, 8, "S")                                  # Voltorb's sign (on its yard's fence, read from the walk)
at(38, 8, "S")                                  # Kangaskhan's sign
rect(34, 11, 40, 16, "#")
rect(35, 12, 39, 15, ":")
rect(36, 12, 37, 12, "*")
at(37, 16, "S")                                 # Chansey's sign

# along the main street: the Mart (door 5,16), the Safari Zone's office (door 29,16), Slowpoke's garden beside it
# behind a hedge from the east walk (the tree to cut at 30,11)
rect(4, 13, 7, 16, "L")
rect(28, 13, 31, 16, "O")
rect(27, 11, 33, 11, "b")
at(30, 11, ".")                                 # (the tree to cut)
rect(10, 13, 12, 14, "*")
tree(14, 13)
at(32, 17, "S")                                 # Slowpoke's sign
at(3, 17, "S")                                  # the town sign, by Route 18's road

# the park south of the main street (the Friends' camp round 8,24), its flower garden behind a hedge (the tree to
# cut at 17,26)
rect(14, 22, 20, 26, "b")
rect(15, 23, 19, 25, "*")
at(17, 26, ".")
tree(24, 23)

# the shore street's buildings (doors on row 31), the lanes between them (the tree to cut at 22,27 in the hedge
# across the lane by the Center)
rect(2, 27, 8, 31, "G")                         # Koga's Gym, door 5,31
rect(11, 28, 14, 31, "H")                       # a house, door 12,31
rect(17, 28, 21, 31, "Z")                       # the Pokémon Center, door 19,31
rect(24, 28, 27, 31, "J")                       # a house, door 25,31
rect(29, 28, 33, 31, "W")                       # the Warden's house, door 31,31
rect(36, 28, 39, 31, "K")                       # the house with the pond garden, doors 37,31 and (back) 37,28
rect(15, 27, 16, 27, "b")
rect(22, 27, 23, 27, "b")
at(22, 27, ".")
rect(28, 27, 28, 27, "b")
at(9, 30, "S")                                  # the Gym's sign
at(34, 30, "S")                                 # the Warden's sign
rect(2, 32, 41, 33, "=")

# the pond garden behind the house at the east end: fenced, reached only by its back door
rect(34, 22, 40, 27, "#")
rect(35, 23, 39, 26, ".")
rect(36, 27, 39, 27, ".")
rect(36, 23, 38, 24, "~")

# the beach path down to Route 19 (columns 18-29, as wide as Route 19's), through the woods
rect(18, 34, 29, 39, ":")

Path(__file__).with_name("plan_stage1.txt").write_text("".join("".join(r) + "\n" for r in g))
