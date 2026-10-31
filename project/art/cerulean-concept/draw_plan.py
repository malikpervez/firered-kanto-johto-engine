#!/usr/bin/env python3
"""Draws Cerulean City's block plan (plan_stage1.txt): the concept, as shapes. Edit the shapes here and run it
again; make_art.py builds the map from the plan. Run from the repository root:
python3 project/art/cerulean-concept/draw_plan.py

Cerulean is the town by the lake, where Nugget Bridge comes down from the north:
- **the bridge road** comes in from Route 24 (the top, columns 41-44) over the water and down into town: Blue waits
  on it (his scene walks rows 1-15 of those columns, so they stay open);
- **the lake** west of the bridge, with **Cerulean Cave** on an island in its north-west corner, reached by surfing
  from the lakeside walk; its guard stands at the mouth;
- **the badge guy's house** east of the bridge road, its back door onto a yard you only reach through the house;
- **the robbed house** in the middle of town: its back wall has the thieves' hole into a little backyard, and the
  Rocket grunt stands in the one-block way out of it (his triggers above and below him);
- the streets: Route 4's road in from the west (rows 17-20), the street past the Pokémon Center, the road east to
  Route 9 (rows 28-30), and the road south to Route 5 (columns 21-24), which narrows to two blocks where the lass and
  her Slowbro stand until you have the S.S. Ticket;
- the Gym south of the road east, the Mart and the Bike Shop in the south-west, three more houses, the plaza with
  its pool, the Friends' camp, the Pokémon shelter's corner and a garden behind a tree to cut.

Letters: the kit's legend (T forest, . lawn, = cobblestones, : dirt, d the bridge's planks, ~ water, * flowers,
b bushes, # fences, o rocks, l lamps (two blocks), S signs, p the dressed-stone paving), % brick (the street
pack's, in Cerulean's blues, without kerbs) and the buildings: 1 and 2 cottages without doors (the family house in
blue and in teal), W the Gym, Z the Pokémon Center, L the
Poké Mart, K the Bike Shop, H the two family houses, X the three small houses, Y Cerulean Cave's mouth.
"""
from pathlib import Path

W, H = 58, 51
g = [["." for _ in range(W)] for _ in range(H)]


def rect(x0, y0, x1, y1, c):
    for y in range(y0, y1 + 1):
        for x in range(x0, x1 + 1):
            g[y][x] = c


def at(x, y, c):
    g[y][x] = c


# the frame: forest round the edges, the lake and the bridge's water in the north
rect(0, 0, 57, 1, "T"); rect(0, 0, 1, 50, "T"); rect(54, 0, 57, 27, "T"); rect(0, 49, 57, 50, "T")
rect(54, 32, 57, 48, "T"); rect(54, 31, 57, 31, "b")   # (a hedge along the road east: the forest from row 32, whole trees)
rect(13, 2, 40, 13, "~")            # the lake
rect(29, 0, 40, 1, "~")             # under the bridge, west (from column 29, where Route 24's lake shore is)...
rect(45, 0, 52, 5, "~")             # ...and east
rect(2, 12, 12, 13, "~")            # south of the cave's island
rect(41, 0, 44, 5, "d")             # Nugget Bridge's last span (Route 24: the top, columns 41-44)
rect(45, 0, 45, 5, "b")             # (bushes along its east side: the yard is reached only through the house)
rect(53, 0, 53, 5, "b")             # (and a hedge on the east pond's far side: the forest's column there is half a tree)

# Cerulean Cave on its island
rect(2, 2, 12, 11, ".")
rect(4, 2, 9, 6, "Y")               # the cave's mouth, door (6,6); its guard at (6,7)
rect(2, 2, 3, 3, "T"); rect(10, 2, 11, 3, "T")
at(3, 8, "o"); at(10, 9, "o"); rect(8, 9, 9, 10, "*")

# the bridge road down into town (Blue's scene: columns 41-44, rows 1-15)
rect(41, 6, 44, 22, "=")
rect(39, 6, 40, 14, "b"); rect(45, 6, 45, 12, "b")

# the badge guy's house and its yard (only through the house: its back door at 48,7)
rect(46, 8, 50, 11, "H")            # door (48,11)
rect(46, 6, 53, 7, "."); rect(51, 8, 53, 13, "b"); at(52, 6, "*"); at(53, 6, "*")
rect(45, 12, 50, 12, ".")            # its front, onto the bridge road
rect(45, 13, 53, 13, "b")
rect(48, 12, 48, 12, ":")

# east of the bridge road: the berry man's house
rect(45, 14, 53, 27, ".")
rect(47, 15, 50, 18, "X")           # door (48,18)
rect(48, 19, 48, 21, ":")
rect(51, 15, 53, 16, "*"); at(46, 24, "o")

# the lakeside walk and Route 4's road in from the west
rect(2, 14, 31, 15, ".")
rect(2, 16, 31, 16, "b"); rect(12, 16, 13, 16, "."); rect(24, 16, 25, 16, ".")
rect(0, 17, 31, 20, "=")            # Route 4's road (the left edge, rows 17-20)
rect(3, 14, 5, 14, "*")

# the robbed house, its backyard and the grunt's way out of it
rect(32, 14, 32, 22, "b")
rect(33, 14, 40, 15, "b")
rect(33, 16, 37, 18, ".")           # the backyard (the hole: 35-36,18)
rect(38, 16, 38, 22, ":")           # the grunt's way out (he stands at 38,17)
rect(39, 15, 40, 22, "b")
at(33, 16, "o"); at(37, 16, "*")

# the town's middle: the street, the Center, the plaza and its pool, the Friends' camp
rect(26, 23, 44, 24, "=")           # the street past the Center (the policeman stands on it, 36,23)
rect(26, 21, 31, 22, "=")
rect(2, 21, 25, 36, ".")
rect(26, 25, 44, 36, ".")
rect(26, 25, 30, 28, "Z")           # the Pokémon Center, door (28,28)
rect(26, 29, 31, 29, "=")
rect(33, 25, 37, 27, "~")           # the plaza's pool
rect(32, 28, 38, 28, "*")
at(25, 25, "S")                     # the town sign (read from 25,26)
rect(30, 30, 38, 34, ".")           # the Friends' camp (their anchor: 34,32)
rect(14, 26, 17, 29, "X")           # a small house, door (15,29)
rect(15, 30, 15, 31, ":")
rect(3, 22, 7, 25, "*"); at(9, 23, "o"); rect(18, 24, 19, 25, "*")

rect(33, 19, 37, 22, "H")           # the robbed house, door (35,22)

# the road east to Route 9 and the Gym south of it
rect(39, 28, 57, 30, "=")           # the road east (the right edge, rows 28-30)
rect(39, 25, 40, 27, "=")
rect(45, 25, 53, 27, ".")
rect(44, 32, 50, 36, "W")           # the Gym, door (47,36)
rect(43, 37, 51, 38, "=")
at(51, 36, "S")                     # the Gym's sign (read from 51,37)
rect(41, 32, 43, 36, "."); rect(51, 32, 53, 35, ".")

# the road south to Route 5, its neck, the Mart, the Bike Shop and a small house
rect(21, 21, 24, 50, "=")           # the road south (the bottom, columns 21-24)
rect(25, 37, 42, 38, "=")
rect(20, 45, 21, 48, "b"); rect(24, 45, 25, 48, "b")   # the neck (22-23,45): the lass and her Slowbro stand in it until the S.S. Ticket
rect(26, 38, 29, 41, "L")           # the Poké Mart, door (27,41)
rect(31, 38, 34, 41, "X")           # a small house, door (32,41)
rect(25, 42, 42, 43, "=")
rect(8, 38, 12, 41, "K")            # the Bike Shop, door (10,41)
rect(2, 42, 20, 43, "=")
at(14, 38, "S")   # the Bike Shop's sign (read from 14,39)
at(19, 41, "S")                     # trainer tips (read from 19,42)
rect(2, 44, 20, 48, ".")            # the Pokémon shelter's corner (the caretaker at 5,46)
rect(14, 46, 18, 47, "*")
rect(25, 44, 42, 48, ".")
rect(36, 46, 40, 47, "*")
at(29, 47, "o")

# the garden behind a tree to cut (the tree at 49,39)
rect(43, 39, 53, 48, "#")
rect(44, 40, 52, 47, ".")
at(49, 39, ".")                     # its gap, where the tree to cut stands
rect(45, 41, 47, 42, "*"); rect(50, 45, 52, 46, "*")

# the town's detail (KR-93): the town paved (the kit's dressed stone), canals by the roads south and east (the one
# south banked with Cerulean's blue brick), cottages without doors, lamps; west of the road south the blue brick
# borders the paving where it meets anything else (the roads, the lawn, the forest, the hedges), the lakeside promenade plain paving (P) behind a fence along the
# lake's shore, and a fence along the Pokémon Center's north and west sides (f: fences on the paving)
for x0, y0, x1, y1 in ((2, 21, 20, 41), (25, 21, 44, 36), (45, 14, 53, 27), (41, 31, 53, 36), (25, 38, 42, 41),
                       (25, 44, 42, 48), (52, 37, 53, 38)):
    for y in range(y0, y1 + 1):
        for x in range(x0, x1 + 1):
            if g[y][x] in ".o:*":
                g[y][x] = "p"
rect(25, 21, 25, 23, "=")                           # the street past the robbed house meets the road south
rect(38, 21, 38, 22, ":")                           # the grunt's way out runs on down to the street
rect(32, 25, 32, 27, "%"); rect(38, 25, 38, 27, "%"); rect(32, 28, 38, 28, "%")   # the brick ring round the pool
rect(3, 22, 7, 25, "1"); rect(9, 22, 13, 25, "2"); rect(3, 27, 7, 30, "2"); rect(48, 22, 52, 25, "1")
rect(18, 22, 18, 40, "%"); rect(19, 22, 19, 40, "~"); rect(20, 22, 20, 40, "%")   # the canal by the road south
rect(45, 27, 53, 27, "~")                                                          # and by the road east
# east of the road south the town is one paved square: the walk in front of the Center and the road to the Gym are
# paving too, and no blue there
for x, y in [(x, 29) for x in range(26, 32)] + [(x, y) for y in (37, 38) for x in range(25, 52)]:
    if g[y][x] == "=":
        g[y][x] = "p"
for x, y in ((25, 34), (42, 34), (16, 36), (45, 25)):
    rect(x, y - 1, x, y, "@")                       # lamps on the paving: the post's foot at x, y
for x, y in ((25, 29), (51, 36), (14, 38), (19, 41)):
    at(x, y, "/")                                   # the signs, on the paving (the town sign moves off the fence)
rect(2, 13, 38, 13, "f")                            # the fence along the lake's shore (the cave's island by Surf
                                                    # from the bridge)
rect(2, 14, 31, 15, "P"); rect(12, 16, 13, 16, "P"); rect(24, 16, 25, 16, "P")   # the promenade
rect(25, 24, 38, 24, "f"); rect(25, 25, 25, 28, "f")   # round the Center's north and west sides
# the town props (Kanto Town Props v0.1, kit/props.py): the fountain in the square between the Center and the Gym
# (F), benches facing it (u its seat to the south, n to the north, a to the west), flower tubs (t) and a bin (i);
# benches along the promenade looking at the lake; footbridges over the canals (x y z west to east over the one by
# the road south, 0 m j north to south over the one by the road east)
rect(37, 31, 39, 33, "F")
rect(37, 29, 38, 29, "u"); rect(37, 35, 38, 35, "n"); rect(41, 31, 41, 32, "a")
at(36, 35, "t"); at(40, 35, "t"); at(39, 35, "i")
rect(24, 45, 24, 48, "t")                           # flower tubs on the paving narrow the road to the neck
rect(13, 40, 14, 40, "e")                           # the bike rack by the Bike Shop
for x in (6, 17, 28):
    rect(x, 14, x + 1, 14, "n")
at(18, 31, "x"); at(19, 31, "y"); at(20, 31, "z")
at(47, 26, "0"); at(47, 27, "m"); at(47, 28, "j")
rect(11, 34, 12, 34, "u"); at(10, 34, "t"); at(13, 34, "t")   # a bench between two tubs in the plaza west of the canal
BUILT = set("WKXZLHY12^")
border = [(x, y) for y in range(H) for x in range(21) if g[y][x] == "p" and any(  # the west side only
    g[y + dy][x + dx] not in "pP%~/@fFunatiexyz0mj" and g[y + dy][x + dx] not in BUILT
    for dy in (-1, 0, 1) for dx in (-1, 0, 1) if (dx or dy) and 0 <= x + dx < W and 0 <= y + dy < H)]
for x, y in border:
    g[y][x] = "%"

# where the paving meets the cobbles head on, the kit's join pieces (a row of setts between them): the promenade's two
# openings onto Route 4's road (U: paving to the north, cobbles to the south) and the Mart square's edge under the
# road east of the neck (N: cobbles to the north)
rect(12, 16, 13, 16, "U"); rect(24, 16, 25, 16, "U")
rect(25, 44, 41, 44, "N")

Path(__file__).with_name("plan_stage1.txt").write_text("".join("".join(r) + "\n" for r in g))
print("    " + "".join(str(x // 10 % 10) if x % 10 == 0 else " " for x in range(W)))
print("    " + "".join(str(x % 10) for x in range(W)))
for y, r in enumerate(g):
    print(f"{y:2d}  " + "".join(r))
