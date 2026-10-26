#!/usr/bin/env python3
"""Draws Route 24's block plan (plan_stage1.txt): the concept, as shapes. Edit the shapes here and run it again;
make_art.py builds the map from the plan. Run from the repository root:
python3 project/art/route24-concept/draw_plan.py

Route 24 is Nugget Bridge, north out of Cerulean over the lake:
- **the bridge** (columns 16-19, the whole way up: Cerulean's bridge road meets its bottom, Route 25's span its top),
  with a rail of bushes along its east side. Five trainers stand across it in turn, each at a side facing the
  other, so their lines of sight close the bridge: you can't get past one without being seen. At its north end the
  Rocket waits, his triggers across the bridge at row 8 (his scene walks him one block along it);
- **the west shore**, a meadow off Route 25's west path above the lake: the TM, a berry hidden in the grass, tall
  grass, and Shane the camper watching it from its foot;
- **the east meadow**, off Route 25's east path: the shelter's traveler and the Charmander he looks after;
- **the lake** west of the bridge (it runs on into Cerulean's), and east of the bridge's foot a pond that carries on
  Cerulean's water east of its bridge, closed off by bushes: Cerulean's yard is still reached only through its house.

Letters: the kit's legend (T forest, . lawn, d the bridge's planks, ~ water, * flowers, b bushes, g tall grass,
o rocks).
"""
from pathlib import Path

W, H = 30, 22
g = [["." for _ in range(W)] for _ in range(H)]


def rect(x0, y0, x1, y1, c):
    for y in range(y0, y1 + 1):
        for x in range(x0, x1 + 1):
            g[y][x] = c


def at(x, y, c):
    g[y][x] = c


# the frame: forest either side
rect(0, 0, 3, 21, "T")
rect(28, 0, 29, 21, "T")

# the lake west of the bridge, and the channel up its west side to Route 25 (its water: columns 11-14)
rect(11, 0, 15, 12, "~")
rect(4, 13, 15, 21, "~")

# the bridge and its east rail
rect(16, 0, 19, 21, "d")
rect(20, 0, 20, 21, "b")

# the west shore: Route 25's west path comes down at columns 7-10
rect(4, 0, 6, 1, "b")
rect(4, 2, 10, 12, ".")
rect(4, 5, 7, 9, "g")             # tall grass (Abra)
rect(8, 2, 10, 3, "*"); at(4, 11, "o"); at(10, 7, "o"); rect(9, 9, 10, 10, "*")

# the east meadow, off Route 25's east path (columns 24-25), its water from Route 25 (columns 21-22)
rect(21, 0, 22, 7, "~")
at(23, 0, "b")
rect(23, 1, 25, 3, ".")
rect(26, 0, 27, 3, "T")
rect(23, 4, 27, 7, ".")
rect(21, 8, 27, 13, ".")
rect(25, 11, 27, 12, "*"); at(27, 6, "o")

# the pond east of the bridge's foot (Cerulean's water east of its bridge), closed off from the meadow
rect(21, 14, 27, 14, "b")
rect(21, 15, 27, 21, "~")

Path(__file__).with_name("plan_stage1.txt").write_text("".join("".join(r) + "\n" for r in g))
print("    " + "".join(str(x // 10 % 10) if x % 10 == 0 else " " for x in range(W)))
print("    " + "".join(str(x % 10) for x in range(W)))
for y, r in enumerate(g):
    print(f"{y:2d}  " + "".join(r))
