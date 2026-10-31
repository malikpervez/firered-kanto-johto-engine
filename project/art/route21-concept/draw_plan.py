#!/usr/bin/env python3
"""Draws Route 21's two block plans (plan_north.txt, plan_south.txt): the concept, as shapes. Edit the shapes here
and run it again; make_art.py builds the maps from the plans. Run from the repository root:
python3 project/art/route21-concept/draw_plan.py

Route 21 is the sea route south from Pallet Town to Cinnabar Island, by Surf, in two maps of 24x50 blocks, as before.
Its joins stay where they were: Pallet's river (its columns 18-21) at the top of the north map, columns 7-10 (offset
-11); the two maps meet across their whole width; Cinnabar's top (its columns 0-23) below the south map (offset 0),
where the island's north woods stand behind its Mansion and Gym, the sea lane down its west side (columns 0-3).

The north map has:
- **Pallet's river**, running down between two meadows (Mr. Mime's and the Tangela's tall grass) to the beach, and
  out over its bar into the sea;
- **the fishers' islet** in the open sea, its tall grass between them;
- **the pearl sandbar** further south (the Pearl hidden on it), the swimmers and Corphish round it.

The south map has:
- **the long islet**, its tall grass between the two fishers;
- **the open sea**, the swimmers in it;
- **Cinnabar's north shore** at the foot: the beach, its tall grass, and the woods behind the island's town.

Letters: the kit's legend (T forest, . lawn, g tall grass, * flowers, ~ the river, s the sea, q and Q sea rocks).
"""
from pathlib import Path

W, H = 24, 50


def blank(c):
    return [[c for _ in range(W)] for _ in range(H)]


def rect(g, x0, y0, x1, y1, c):
    for y in range(y0, y1 + 1):
        for x in range(x0, x1 + 1):
            g[y][x] = c


def open_sea(g, x, y):
    return all(0 <= x + i < W and 0 <= y + j < H and g[y + j][x + i] in "sqQ" for i in (-1, 0, 1) for j in (-1, 0, 1))


def rocks(g, spots):
    """Sea rocks out towards the two edges, scattered (some alone, some in pairs, never in a line), each where open sea
    is all round it, off the swimmers' and the fishers' lines of sight."""
    for x, y, c in spots:
        assert open_sea(g, x, y), f"the rock at ({x},{y}) isn't in open sea"
        g[y][x] = c


# ---------------------------------------------------------------- the north map
n = blank("s")
rect(n, 0, 0, 23, 13, "T")
rect(n, 6, 0, 11, 13, ".")             # the river's banks
rect(n, 12, 2, 21, 13, ".")            # Mr. Mime's meadow
rect(n, 14, 4, 20, 10, "g")
rect(n, 2, 4, 5, 13, ".")              # the Tangela's meadow
rect(n, 2, 8, 4, 12, "g")
rect(n, 16, 12, 18, 12, "*")
rect(n, 0, 14, 23, 15, ".")            # the beach
rect(n, 0, 2, 1, 15, "s")              # the sea round the land's west and east sides (the border is open sea: the
rect(n, 22, 0, 23, 15, "s")            # coast turns the corner inside the map, the woods end on whole trees)
rect(n, 7, 0, 10, 15, "~")             # Pallet's river, out over its bar into the sea
rect(n, 5, 25, 17, 29, ".")            # the fishers' islet
rect(n, 9, 26, 14, 28, "g")
for x, y in ((5, 25), (16, 25), (17, 25), (17, 26), (5, 28), (5, 29), (6, 29), (7, 29), (17, 29)):
    n[y][x] = "s"                      # its shore stepped in at the corners, not a box (the fishers' blocks stay land)
rect(n, 17, 40, 20, 42, ".")           # the pearl sandbar
rect(n, 19, 40, 20, 40, "*")
n[40][17] = n[42][20] = "s"            # (two corners off it; the Pearl's block stays)
rocks(n, [(2, 19, "Q"), (3, 20, "q"), (1, 26, "q"), (2, 34, "Q"), (1, 41, "q"), (3, 47, "Q"),
          (21, 22, "q"), (22, 28, "Q"), (20, 32, "q"), (21, 33, "Q"), (22, 46, "q")])

# ---------------------------------------------------------------- the south map
s = blank("s")
rect(s, 8, 5, 15, 17, ".")             # the long islet
rect(s, 9, 6, 14, 16, "g")
rect(s, 4, 40, 21, 43, ".")            # Cinnabar's north shore: the beach...
rect(s, 7, 41, 18, 42, "g")
rect(s, 4, 44, 23, 49, "T")            # ...and the woods behind the town
rocks(s, [(1, 3, "q"), (2, 9, "Q"), (3, 10, "q"), (1, 18, "Q"), (2, 26, "q"), (1, 33, "Q"),
          (21, 5, "q"), (22, 13, "Q"), (20, 20, "q"), (22, 29, "Q"), (21, 30, "q"), (22, 36, "q")])

here = Path(__file__).resolve().parent
(here / "plan_north.txt").write_text("".join("".join(r) + "\n" for r in n))
(here / "plan_south.txt").write_text("".join("".join(r) + "\n" for r in s))
