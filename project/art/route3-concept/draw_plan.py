#!/usr/bin/env python3
"""Draws Route 3's block plan (plan_stage1.txt): the concept, as shapes. Edit the shapes here and run it again;
make_art.py builds the map from the plan. Run from the repository root:
python3 project/art/route3-concept/draw_plan.py

Route 3 is the mountain road east from Pewter, where every trainer who's just got through Viridian Forest waits to
test you. It runs along a valley between the mountains (cliffs to the north, cliffs and forest to the south):
- in from Pewter (the left edge, rows 9-12), a lane north climbs to the **high path**, a shelf under the northern
  cliff with four trainers on it; its way on is down its ledge into the grass (or back the way you came);
- the valley floor is **a wide field of tall grass** that can't be walked round, two trainers watching across it and
  a third wandering in it;
- past a rocky outcrop the road narrows, then opens onto **the rest stop** with the route sign, where a hiker from
  Cerulean sits down, and the road turns **north up a pass** to Route 4 and Mt. Moon (the top, columns 68-75, where
  Route 4's road meets it); more grass east of the pass.

Letters: the kit's legend (T forest, . lawn, : dirt, g tall grass, _ ledges, * flowers, o rocks, b bushes, S signs)
and C cliffs.
"""
from pathlib import Path

W, H = 84, 20
g = [["." for _ in range(W)] for _ in range(H)]


def rect(x0, y0, x1, y1, c):
    for y in range(y0, y1 + 1):
        for x in range(x0, x1 + 1):
            g[y][x] = c


def at(x, y, c):
    g[y][x] = c


# the mountains
rect(0, 0, 67, 3, "C")             # the northern cliff, its face on rows 2-3
rect(76, 0, 83, 7, "C")            # east of the pass, its face on rows 6-7
rect(59, 0, 67, 6, "C")            # west of the pass, its face on rows 5-6
rect(0, 0, 11, 8, "C")             # over the way in from Pewter, its face on rows 7-8
rect(41, 0, 58, 10, "C")           # the outcrop between the field and the rest stop, its face on rows 9-10
rect(0, 13, 7, 19, "C")            # south of the way in
rect(8, 16, 43, 19, "C")           # south of the field
rect(44, 16, 83, 19, "T")          # the forest south of the rest stop
rect(82, 8, 83, 19, "C")            # the east edge: the plateau east of the pass runs down it and on past the map
rect(0, 13, 1, 19, "T")            # Pewter's forest carries on over the join, south of the road in
rect(60, 0, 67, 1, "T")            # and Route 4's either side of the pass, ending on the plateaus
rect(76, 0, 83, 1, "T")

# the way in from Pewter and the lane up to the high path
rect(0, 9, 17, 12, ":")            # the road in (rows 9-12, as Pewter's road east)
rect(12, 4, 15, 8, ":")            # the lane north
rect(16, 4, 40, 7, ".")            # the high path, under the cliff
rect(16, 5, 40, 6, ":")
rect(16, 8, 40, 8, "_")            # its ledge down into the field
at(24, 4, "o"); at(31, 7, "*"); at(32, 7, "*"); at(38, 4, "b"); at(39, 4, "b"); at(40, 4, "b")
rect(8, 13, 11, 15, "*")
at(10, 13, "o")

# the field: tall grass across the whole valley floor
rect(18, 9, 40, 15, "g")
rect(16, 13, 17, 15, ".")
rect(41, 11, 43, 15, ".")

# past the outcrop: the road narrows, then the rest stop and the pass north
rect(44, 11, 58, 15, ".")
rect(42, 12, 69, 13, ":")          # the road east
rect(46, 14, 48, 15, "o")
rect(53, 11, 55, 11, "*")
rect(59, 7, 75, 15, ".")
rect(70, 0, 73, 13, ":")           # the pass north (Route 4's road: the top, columns 68-75)
rect(68, 2, 69, 6, "."); rect(74, 2, 75, 7, ".")
rect(68, 0, 75, 1, ":")            # (Route 4's road arrives 8 wide, then narrows to the pass)
rect(59, 12, 69, 13, ":")          # the road east runs on to the pass
rect(60, 14, 66, 15, "*")
at(61, 9, "o"); at(64, 8, "*"); at(65, 8, "*")
at(67, 10, "S")                    # the route sign (read from 67,11)
rect(76, 9, 81, 15, "g")           # grass east of the pass
rect(76, 8, 81, 8, ".")

Path(__file__).with_name("plan_stage1.txt").write_text("".join("".join(r) + "\n" for r in g))
print("    " + "".join(str(x % 10) for x in range(W)))
for y, r in enumerate(g):
    print(f"{y:2d}  " + "".join(r))
