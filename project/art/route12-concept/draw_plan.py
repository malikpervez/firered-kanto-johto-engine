#!/usr/bin/env python3
"""Draws Route 12's block plan (plan_stage1.txt): the concept, as shapes. Edit the shapes here and run it again;
make_art.py builds the map from the plan. Run from the repository root:
python3 project/art/route12-concept/draw_plan.py

Route 12 is Silence Bridge: south from Lavender over the sea to Route 13. It is 38x80 blocks (old Route 12 was 38x90).
Lavender's road south (its columns 13-15) comes in at the top edge, columns 10-13 (offset -2, as before); Route 11's
road (its rows 17-19) at the left edge, rows 44-47 (offset 27, as before); Route 13's boardwalk (its columns 86-89)
leaves the bottom edge at columns 21-24 (offset -65, as before). It has:
- **the north gatehouse**, across the way down from Lavender between the woods: you walk in at its back and out of
  its front door onto the cliff top;
- **the cliff top**, a lookout over the sea, its tall grass, the route sign;
- **Silence Bridge**, a boardwalk south over the sea, the fishers on it;
- **the fishers' deck** where Route 11's road comes onto the bridge: the couple and the TM on it; at its south side
  the bridge goes on through a neck one block wide, where **Snorlax** sleeps (the Leftovers hidden under him);
- **the fishing house** on its islet halfway down, tall grass by the bridge; behind a hedge at the islet's east end, two trees to cut close
  the way into a pocket of land (the Iron, and the Rare Candy hidden);
- **the bridge south** from the islet to Route 13.

Letters: the kit's legend (T forest, . lawn, : dirt, g tall grass, * flowers, s the sea, d the boardwalk, b bushes,
R trees, S signs), and the buildings: N the north gatehouse, F the fishing house.
"""
from pathlib import Path

W, H = 38, 80
g = [["T" for _ in range(W)] for _ in range(H)]


def rect(x0, y0, x1, y1, c):
    for y in range(y0, y1 + 1):
        for x in range(x0, x1 + 1):
            g[y][x] = c


def at(x, y, c):
    g[y][x] = c


def tree(x, y):
    rect(x, y, x + 1, y + 1, "R")


# the sea east of the woods, below the cliffs
rect(8, 18, 37, 79, "s")

# the way down from Lavender (columns 10-13) through the woods to the north gatehouse's back (doorway 11-12,10): Lavender's
# cobbled road carries on to the gatehouse (it was dirt, cut off straight against Lavender's cobbles at the top edge)
rect(10, 0, 13, 9, "=")
rect(10, 10, 13, 13, "N")

# the cliff top below the gatehouse's front door (11-12,13): a lookout, the route sign
rect(6, 14, 17, 17, ".")
rect(6, 16, 9, 17, "g")
# a hedge at the woods' edge: standing beside it, the screen stays off the map's west border (sea)
rect(6, 14, 6, 17, "b")
rect(16, 15, 17, 16, "*")
at(14, 14, "S")

# Silence Bridge south to the fishers' deck
rect(12, 18, 15, 39, "d")

# the fishers' deck, Route 11's road onto it (rows 44-47 at the left edge)
rect(8, 40, 25, 47, "d")
rect(0, 44, 7, 47, ":")

# the neck where Snorlax sleeps (17,48), the bridge on south to the fishing house's islet
rect(17, 48, 17, 49, "d")
rect(16, 50, 19, 59, "d")
rect(16, 59, 19, 59, "\u01c6")  # its last boards land on the islet's lawn: a plain board end, no beam and posts on land

# the islet: the fishing house (door 21,63), its sign; behind a hedge at its east end, a pocket of land closed by two
# trees to cut (26,63 and 26,64: more than 8 blocks from every edge you come in by, KR-45)
rect(14, 60, 25, 67, ".")
rect(20, 60, 23, 63, "F")
at(19, 63, "S")
rect(14, 60, 15, 63, "g")
rect(14, 65, 15, 67, "*")
rect(26, 60, 26, 67, "b")
rect(26, 63, 26, 64, ".")
rect(27, 61, 31, 66, ".")
rect(27, 64, 29, 66, "g")
rect(30, 65, 31, 66, "*")

# the bridge south from the islet to Route 13 (columns 21-24 at the bottom edge)
rect(21, 68, 24, 79, "d")

Path(__file__).with_name("plan_stage1.txt").write_text("".join("".join(r) + "\n" for r in g))
