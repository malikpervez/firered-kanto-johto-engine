#!/usr/bin/env python3
"""Draws Route 16's block plan (plan_stage1.txt): the concept, as shapes. Edit the shapes here and run it again;
make_art.py builds the map from the plan. Run from the repository root:
python3 project/art/route16-concept/draw_plan.py

Route 16 is where Celadon's boulevard runs out west into a wooded valley and Cycling Road begins. It is 56x44 blocks
(old Route 16 was 64x52). Celadon's boulevard (its rows 20-23) meets the right edge at rows 22-25; Cycling Road
(Route 17) starts below the bottom edge, its road at columns 12-17. It has:
- **the road west from Celadon**, where Snorlax sleeps in the one-block gap between two outcrops of rock: nothing
  passes until the Poké Flute wakes him (the Leftovers he leaves are hidden where he lay);
- **the Cycling Road gatehouse** beyond him, across the way, its lower hall open to bikes only (its guard's rule):
  through it, the plaza at the top of Cycling Road, where the bikers hang out by the road down;
- **the woodland path**, behind a tree to cut north of the road before Snorlax, through the woods (Lea and Jed out
  walking, tall grass either side) to the gatehouse's upper hall, open on foot;
- **the glade** beyond the upper hall, closed off from the plaza by the forest, with the house in the woods where
  the girl who gives HM02 Fly lives;
- **the meadow** south of the road before Snorlax, tall grass round a pond.

Letters: the kit's legend (T forest, . lawn, = cobble, : dirt, p paving, g grass, * flowers, ~ pond, b bushes,
o rocks, R trees, S signs), C the Cycling Road gatehouse (its lower hall and its upper hall: one pack, twice), Y the
house in the woods (Viridian's pond keeper's house).
"""
from pathlib import Path

W, H = 56, 44
g = [["T" for _ in range(W)] for _ in range(H)]


def rect(x0, y0, x1, y1, c):
    for y in range(y0, y1 + 1):
        for x in range(x0, x1 + 1):
            g[y][x] = c


def at(x, y, c):
    g[y][x] = c


def tree(x, y):
    rect(x, y, x + 1, y + 1, "R")


# the road from Celadon (rows 22-25), the outcrops where Snorlax sleeps (44,24), on to the gatehouse's lower hall
rect(46, 21, 53, 26, ".")
rect(46, 22, 55, 25, "=")
rect(43, 20, 45, 28, "o")
at(43, 24, "=")
at(44, 24, "=")
at(45, 24, "=")
rect(36, 21, 42, 26, ".")
rect(36, 22, 42, 25, "=")
rect(28, 21, 35, 24, "C")                      # the gatehouse's lower hall: doorways 28,24 and 35,24

# the plaza at the top of Cycling Road and the road down to it (columns 12-17)
rect(2, 20, 27, 32, ".")
rect(8, 21, 27, 27, "p")
rect(12, 28, 17, 43, "=")
rect(2, 21, 6, 24, "*")
tree(3, 27); tree(22, 29); tree(25, 30)
at(4, 31, "o")                                 # a field rock in the plaza's west lawn
at(19, 28, "S")                                # the route sign

# the woodland path: the tree to cut (46,21) in the hedge north of the road, north and west to the upper hall
rect(36, 2, 53, 20, ".")
rect(36, 21, 53, 21, "b")
at(46, 21, ".")                                # (the tree to cut stands here)
at(38, 21, "S")                                # the Cycling Road sign, by the road west of Snorlax
rect(46, 14, 47, 20, ":")
rect(36, 12, 47, 13, ":")
rect(38, 3, 52, 8, "g")
rect(48, 14, 52, 19, "g")
rect(36, 15, 43, 19, "g")
tree(36, 9); tree(44, 9); tree(50, 10)
rect(28, 9, 35, 12, "C")                       # the gatehouse's upper hall: doorways 28,12 and 35,12

# the glade beyond the upper hall, the house in the woods
rect(2, 2, 27, 15, ".")
rect(14, 12, 27, 13, ":")
rect(16, 8, 19, 11, "Y")                       # the house, door 17,11
rect(3, 3, 9, 6, "g")
rect(21, 4, 25, 6, "*")
rect(5, 10, 9, 12, "~")
at(7, 11, "v")                                 # a lily pad in the middle of the pond
at(12, 8, ","); at(13, 8, ","); at(12, 9, ",")  # a few flowers in the glade's open lawn
tree(11, 3); tree(23, 8); tree(3, 13)

# the meadow south of the road before Snorlax: tall grass round a pond
rect(46, 27, 53, 36, ".")
rect(47, 28, 53, 35, "g")
rect(49, 31, 51, 33, "~")

# the forest is drawn in 2x2 cells on the even grid: its edges on even rows, so no half trees show. A lawn row before
# the woods south of the bikers' lawns (row 33); south of the road west of the rocks the woods start at row 28, the
# rock column's foot (43-45,28) woods too. (Below the meadow, row 37 is old Route 17's strip: it stays forest.)
rect(2, 33, 11, 33, "."); rect(18, 33, 27, 33, ".")
rect(36, 27, 42, 27, "."); rect(43, 28, 45, 28, "T")
# under each hall's base a hedge (solid, 1x1), so the woods below start on an even row (14, 26) and no cut-off crowns
# sit against the wall; the halls stay sealed
rect(28, 13, 35, 13, "b"); rect(28, 25, 35, 25, "b")

Path(__file__).with_name("plan_stage1.txt").write_text("".join("".join(r) + "\n" for r in g))
