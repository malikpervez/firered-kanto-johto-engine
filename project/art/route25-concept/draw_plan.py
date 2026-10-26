#!/usr/bin/env python3
"""Draws Route 25's block plan (plan_stage1.txt): the concept, as shapes. Edit the shapes here and run it again;
make_art.py builds the map from the plan. Run from the repository root:
python3 project/art/route25-concept/draw_plan.py

Route 25 is Cerulean's cape, north of Nugget Bridge: a road east under a rock ridge to Bill's Sea Cottage on the
headland, the sea beyond it.
- **the landing** (the west end), where the bridge comes up (columns 16-19) and Route 24's two paths meet it, the
  west one (7-10) from its shore, the east one (24-25) from its meadow. Grass along the forest, a stream by the
  bridge's rail;
- **the cape road** east along the foot of the ridge, through two necks where the meadow narrows to the road
  between rows of bushes: a trainer stands in each row looking across the road (Joey at the first, Wayne at the
  second), so the cottage can't be reached without beating them. Between the necks the couple (Kelsey and Flint)
  and the other trainers stand off the road, in sight of parts of it only;
- **the garden** under the ridge, fenced, with the tree to cut in its gate: TM43 and a hidden Ether inside;
- **the trail below**, along the bottom of the meadow, under its ledges: hop down from the road, and it takes you
  back west to Route 24's east path and the landing (a shortcut back to the bridge);
- **the headland**: Bill's cottage under the ridge, its sign by the door, and a lookout over the sea where a couple
  stands.

Letters: the kit's legend (T forest, . lawn, : dirt, d the bridge's planks, ~ pond, s sea, q/Q sea rocks, * flowers,
b bushes, g tall grass, o rocks, # fence, _ ledges, S signs), C cliffs and H the cottage (4x4, its door at 1,3).
"""
from pathlib import Path

W, H = 70, 24
g = [["." for _ in range(W)] for _ in range(H)]


def rect(x0, y0, x1, y1, c):
    for y in range(y0, y1 + 1):
        for x in range(x0, x1 + 1):
            g[y][x] = c


def at(x, y, c):
    g[y][x] = c


# the frame: forest west, the ridge along the top, the sea east, forest along the bottom east of Route 24's paths
rect(0, 0, 3, 23, "T")
rect(4, 0, 57, 3, "C")
rect(58, 0, 69, 23, "s")
at(61, 6, "q"); at(60, 13, "Q"); at(64, 9, "Q"); at(62, 19, "q"); at(66, 16, "q")
rect(26, 18, 57, 23, "T")

# the landing: Route 24's west path (columns 7-10), the bridge's last span (16-19) and its east path (24-25) come up
# from the bottom; the lake's channel west of the bridge, its rail and a stream east of it
rect(4, 21, 6, 23, "b")
rect(11, 16, 15, 23, "~")
rect(16, 15, 19, 23, "d")
rect(20, 15, 20, 23, "b")
rect(21, 16, 23, 16, "b"); rect(21, 17, 22, 23, "~"); rect(23, 17, 23, 23, "b")
rect(4, 10, 8, 13, "g")                       # grass along the forest
rect(5, 5, 7, 6, "*"); at(10, 4, "o"); rect(13, 12, 14, 13, "*"); at(23, 5, "o")
rect(17, 11, 18, 14, ":")                     # the road up off the bridge...
rect(17, 9, 52, 10, ":")                      # ...and east along the cape
rect(24, 4, 27, 7, "g")

# the first neck: bushes across the meadow but the road; Joey stands in their row above the road, looking down
rect(28, 4, 28, 7, "b"); rect(28, 11, 28, 13, "b")

# the garden under the ridge, fenced, its gate (34,7) closed by the tree to cut
rect(30, 4, 30, 7, "#"); rect(38, 4, 38, 7, "#"); rect(30, 7, 38, 7, "#"); at(34, 7, ".")
rect(31, 4, 33, 4, "*"); rect(35, 6, 37, 6, "*")
rect(30, 11, 36, 13, "g")                     # grass south of the road
rect(40, 4, 45, 7, "g")                       # grass north of it

# the second neck: Wayne stands in its row above the road, looking down
rect(47, 4, 47, 7, "b"); rect(47, 11, 47, 13, "b")

# the bottom of the meadow: bushes, and ledges down to the trail below (one way), which runs back west to Route 24's
# east path
rect(26, 14, 29, 14, "b"); rect(30, 14, 37, 14, "_"); rect(38, 14, 41, 14, "b"); rect(42, 14, 51, 14, "_")
rect(52, 14, 57, 14, "b")
rect(26, 16, 55, 16, ":")
rect(44, 17, 46, 17, "*"); at(56, 15, "o")

# the headland: the cottage under the ridge, its sign, the path to its door; the lookout over the sea
rect(50, 4, 53, 7, "H")
at(49, 7, "S")
rect(51, 8, 51, 8, ":")
rect(54, 4, 56, 5, "*"); at(57, 4, "o"); rect(55, 12, 57, 13, "*")

Path(__file__).with_name("plan_stage1.txt").write_text("".join("".join(r) + "\n" for r in g))
print("    " + "".join(str(x // 10 % 10) if x % 10 == 0 else " " for x in range(W)))
print("    " + "".join(str(x % 10) for x in range(W)))
for y, r in enumerate(g):
    print(f"{y:2d}  " + "".join(r))
