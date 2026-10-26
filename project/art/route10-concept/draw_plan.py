#!/usr/bin/env python3
"""Draws Route 10's block plan (plan_stage1.txt): the concept, as shapes. Edit the shapes here and run it again;
make_art.py builds the map from the plan. Run from the repository root:
python3 project/art/route10-concept/draw_plan.py

Route 10 runs down the east of the mountains from Route 9 to Lavender, and Rock Tunnel goes under them. It is 38x60
blocks (old Route 10 was 38x90), as wide as before, so Lavender's join stays where it was:
- **the north clearing**, where Route 9's road comes in (rows 17-19 at the left edge): the Pokémon Center, and Rock
  Tunnel's north mouth in a ridge, with its sign; a meadow of grass behind a row of young trees to cut, where the
  Voltorb roll about;
- **the river** down the east of the clearing, which can be surfed: it widens into **the lake** where the abandoned
  Power Plant stands on its island, with the Electabuzz that live there; the plant can only be reached by water;
- **the mountains** across the middle: no way over them but Rock Tunnel (its south mouth faces south at their foot);
- **the south valley**, from Rock Tunnel's south mouth down to Lavender (columns 16-20 on the bottom edge, where
  Lavender's road north meets it), its trainers off the road.

Letters: the kit's legend (T forest, . lawn, : dirt, g tall grass, ~ pond water, * flowers, o rocks, b bushes, S signs),
C cliffs, Y the caves' mouths (Route 2's), Z the Pokémon Center, X the Power Plant (Pewter's Gym: FireRed's plant is a
plain stone hall).
"""
from pathlib import Path

W, H = 38, 60
g = [["." for _ in range(W)] for _ in range(H)]


def rect(x0, y0, x1, y1, c):
    for y in range(y0, y1 + 1):
        for x in range(x0, x1 + 1):
            g[y][x] = c


def at(x, y, c):
    g[y][x] = c


# the frame: forest round the route, open at Route 9's road (left, rows 17-19) and Lavender's (bottom, 16-20)
rect(0, 0, 37, 1, "T")
rect(0, 0, 1, 59, "T")
rect(36, 0, 37, 59, "T")
rect(0, 58, 37, 59, "T")

# the north clearing
rect(2, 2, 17, 8, "C")                         # the ridge Rock Tunnel's north mouth is set in (its face on rows 7-8)
rect(6, 4, 11, 8, "Y")                         # the mouth, door 8,8
at(12, 9, "S")                                 # the Rock Tunnel sign, read from 12,10
rect(18, 2, 18, 10, "b")                       # the meadow's west hedge
rect(19, 2, 27, 10, "g")                       # the meadow
rect(18, 11, 27, 11, "b")                      # its south hedge, with the young trees to cut at 20-23
rect(20, 11, 23, 11, ".")
rect(12, 12, 16, 15, "Z")                      # the Pokémon Center, door 14,15
rect(0, 17, 13, 19, ":")                       # Route 9's road (rows 17-19)
rect(13, 16, 15, 19, ":")                      # and up to the Center's door
rect(3, 23, 7, 25, "*"); rect(20, 20, 24, 22, "*"); at(4, 13, "o"); at(24, 26, "o")
at(26, 15, "S")                                # the Power Plant sign, by the river, read from 26,16
rect(2, 27, 27, 27, "b")                       # bushes along the mountains' foot

# the river (it can be surfed) and the lake with the plant's island
rect(28, 2, 31, 30, "~")
rect(32, 2, 35, 30, "T")
rect(2, 28, 21, 45, "C")                       # the mountains across the middle (their face on rows 44-45)
rect(22, 28, 27, 30, "T")
rect(20, 31, 35, 44, "~")                      # the lake
rect(25, 34, 33, 42, ".")                      # the island
rect(26, 35, 32, 39, "X")                      # the Power Plant, door 29,39
at(25, 34, "*"); at(33, 34, "o"); at(25, 42, "o")
rect(20, 45, 35, 49, "T")                      # the lake's south shore: forest, so the valley can't be reached by water

# the south valley: Rock Tunnel's south mouth at the mountains' foot, the road down to Lavender
rect(8, 41, 13, 45, "Y")                       # the south mouth, door 10,45
rect(2, 46, 19, 57, ".")
rect(20, 50, 35, 57, ".")
at(14, 46, "S")                                # its sign, read from 14,47
rect(10, 46, 12, 50, ":")                      # the road from the mouth
rect(10, 50, 20, 52, ":")
rect(16, 52, 20, 59, ":")                      # down to Lavender (16-20)
rect(3, 53, 8, 56, "g"); rect(23, 51, 33, 56, "g")
rect(2, 46, 7, 47, "*"); at(5, 49, "o"); at(33, 50, "o"); at(14, 56, "o")

Path(__file__).with_name("plan_stage1.txt").write_text("".join("".join(r) + "\n" for r in g))
print("    " + "".join(str(x % 10) for x in range(W)))
for y, r in enumerate(g):
    print(f"{y:2d}  " + "".join(r))
