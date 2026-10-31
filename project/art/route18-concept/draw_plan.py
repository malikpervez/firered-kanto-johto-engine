#!/usr/bin/env python3
"""Draws Route 18's block plan (plan_stage1.txt): the concept, as shapes. Edit the shapes here and run it again;
make_art.py builds the map from the plan. Run from the repository root:
python3 project/art/route18-concept/draw_plan.py

Route 18 is the end of Cycling Road: the road down from Route 17's finish turns east along the shore to the
gatehouse, and on to Fuchsia. It is 60x20 blocks, as before. Route 17's road (its columns 14-22) comes in at the top
edge at columns 8-16; Fuchsia's west road (its rows 18-20) meets the right edge at rows 8-10. It has:
- **the road down**, between Route 17's two fences, to the shore;
- **the shore road** east along the coast, the sea west and south of it, to the gatehouse: by bike only, as Cycling
  Road (its guard's rule, inside);
- **the meadow** north of it, under the woods: two Dodrio running up and down, and two Kecleon at the woods' edge;
- **the rockers' grass** south of it, on the bluff over the sea: three rockers waiting in the tall grass, none of
  them looking at the road;
- **the gatehouse**, across the road, the only way between Cycling Road and Fuchsia: woods north and south of it;
- **the road on to Fuchsia** beyond it, out of the woods.

Letters: the kit's legend (T forest, . lawn, = cobble, g grass, * flowers, s the sea, q and Q sea rocks, # fences,
b bushes, S signs), and C the gatehouse (Route 16's Cycling Road gatehouse: packs/buildings_v0.3, cycling_gate).
"""
from pathlib import Path

W, H = 60, 20
g = [["T" for _ in range(W)] for _ in range(H)]


def rect(x0, y0, x1, y1, c):
    for y in range(y0, y1 + 1):
        for x in range(x0, x1 + 1):
            g[y][x] = c


def at(x, y, c):
    g[y][x] = c


# the sea: west of the road down, along the west shore and the south
rect(0, 0, 6, 6, "s")
rect(0, 7, 1, 15, "s")
rect(18, 0, 29, 5, "s")
rect(0, 16, 39, 19, "s")

# the land: the meadow under the woods, the bluff, the road down between Route 17's fences and east along the shore
rect(2, 7, 39, 15, ".")
rect(7, 0, 7, 6, "#")
rect(17, 0, 17, 5, "#")
rect(17, 6, 40, 7, ".")
rect(8, 0, 16, 10, "=")
rect(17, 8, 39, 10, "=")
rect(40, 8, 40, 9, "=")                        # (the woods under the gatehouse start at row 10)
rect(3, 12, 6, 14, "*")
rect(20, 6, 23, 6, "*")

# the rockers' tall grass on the bluff; the gatehouse (doorways 41,9 and 48,9), the woods round it
rect(22, 12, 38, 15, "g")
rect(41, 6, 48, 9, "C")
at(38, 7, "S")                                  # the Cycling Road sign, by the gatehouse's west doorway

# beyond the gatehouse: the road on to Fuchsia, out of the woods
rect(49, 6, 59, 7, ".")
rect(49, 8, 59, 9, "=")
rect(50, 10, 59, 10, "=")
rect(50, 11, 59, 11, ".")
at(52, 7, "S")                                  # the route sign
for y in (6, 7, 11):
    at(W - 1, y, "b")                           # hedges at the edge: only the road leads on

# sea rocks off the shore
for x, y, c in ((3, 3, "q"), (24, 2, "Q"), (8, 18, "Q"), (27, 18, "q"), (35, 17, "Q")):
    at(x, y, c)

# the south woods end on a shore (their trunks at row 17, whole 2x2 cells) instead of running into the map's bottom
# edge, as far as old Fuchsia's strip (its columns 53-59 stay forest; the woods' cell 52-53 whole)
rect(40, 18, 51, 19, "s")

Path(__file__).with_name("plan_stage1.txt").write_text("".join("".join(r) + "\n" for r in g))
