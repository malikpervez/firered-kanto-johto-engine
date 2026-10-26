#!/usr/bin/env python3
"""Draws Vermilion City's block plan (plan_stage1.txt): the concept, as shapes. Edit the shapes here and run it again;
make_art.py builds the map from the plan. Run from the repository root:
python3 project/art/vermilion-concept/draw_plan.py

Vermilion is the harbour city: the town on the shore, the harbour below it.
- **the north plaza**, where Route 6's road comes in (columns 32-34): the Pokémon Center and the Poké Mart either side
  of it, the city sign, Oak's aide; west of it the Pokémon Fan Club and a small house, east of it the empty lot where
  the old man's Machop is stamping the ground flat for a house;
- **the main street**, east along the town to Route 11 (rows 11-14, where its road meets it), the Snorlax notice by
  its end;
- **south of the street**: the Gym in its fenced yard, closed by the tree to cut in the yard's gate; a family house;
  the little park where the Friends camp (its middle 30,19, as before); a house by the quay;
- **the harbour**: the promenade along the water, the long pier south to the S.S. Anne's gangway (the ferry sailor
  at its end, his ticket check before him), the east quay with its crates and barrels where the old sailor, Officer
  Jenny and the Squirtles are, boats in the water. The water is the kit's pond: it can be surfed and fished, as
  Vermilion's could.

Letters: the kit's legend (T forest, . lawn, = cobble, : dirt, d docks and the pier, ~ water, O boats, B barrels,
c crates, * flowers, b bushes, o rocks, # fence, S signs) and the buildings: Z the Pokémon Center, L the Poké Mart,
K the Fan Club (Viridian's Trainer School), W the Gym (Viridian's), X, H and U the houses (Viridian's gardener's,
family and pond keeper's).
"""
from pathlib import Path

W, H = 60, 42
g = [["." for _ in range(W)] for _ in range(H)]


def rect(x0, y0, x1, y1, c):
    for y in range(y0, y1 + 1):
        for x in range(x0, x1 + 1):
            g[y][x] = c


def at(x, y, c):
    g[y][x] = c


# the frame: forest round the town; the harbour's water the whole width below it
rect(0, 0, 59, 2, "T")
rect(0, 0, 5, 23, "T")
rect(56, 0, 59, 10, "T"); rect(56, 15, 59, 23, "T")
rect(0, 24, 59, 41, "~")

# the north plaza: Route 6's road in (32-34), the Center and the Mart either side, the plaza, the city sign
rect(32, 0, 34, 10, "=")
rect(26, 3, 30, 6, "Z")                      # door (28,6)
rect(36, 3, 39, 6, "L")                      # door (37,6)
rect(24, 7, 42, 10, "=")
at(31, 7, "S")                               # the city sign, read from (31,8)
rect(20, 3, 23, 4, "*"); rect(41, 3, 42, 5, "*")

# west of it: the Fan Club and its sign, a small house
rect(14, 6, 18, 9, "K")                      # door (16,9)
at(19, 9, "S")                               # the Fan Club's sign, read from (19,10)
rect(8, 6, 11, 9, "X")                       # door (9,9)
rect(6, 3, 12, 4, "*"); at(13, 4, "o")

# east of it: the empty lot (fenced dirt, its gate at the bottom) where the Machop stamps the ground
rect(44, 3, 53, 9, "#"); rect(45, 4, 52, 8, ":"); at(48, 9, ":")
at(55, 10, "S")                              # the Snorlax notice, read from (55,11)

# the main street, east to Route 11 (rows 11-14)
rect(6, 11, 59, 14, "=")

# south of the street: the Gym's yard (the tree to cut in its gate, 15,15), its sign; a family house
rect(6, 15, 17, 15, "#"); rect(6, 22, 17, 22, "#"); rect(6, 15, 6, 22, "#"); rect(17, 15, 17, 22, "#")
at(15, 15, ".")                              # the gate: the tree to cut stands in it
rect(7, 16, 13, 20, "W")                     # door (10,20)
at(15, 18, "S")                              # the Gym's sign, read from (15,19)
rect(14, 21, 16, 21, "*")
rect(20, 16, 24, 19, "H")                    # door (22,19)
# the Friends' little park round 30,19, and a house by the quay
rect(26, 16, 27, 17, "*"); rect(33, 20, 34, 21, "*"); at(26, 21, "b"); at(34, 16, "b")
rect(44, 16, 47, 19, "U")                    # door (45,19)
rect(50, 17, 52, 18, "*"); rect(18, 20, 18, 21, "b")

# the harbour: the promenade along the water, the pier to the S.S. Anne's gangway (37-39 at the bottom), the east quay
rect(7, 23, 55, 23, "="); rect(18, 22, 55, 22, "=")
at(36, 21, "S")                              # the harbour's sign, read from (36,22)
rect(37, 24, 39, 41, "d")
rect(44, 24, 54, 30, "d")
at(45, 25, "B"); at(46, 25, "B"); at(53, 24, "c"); at(54, 24, "c"); at(54, 25, "c")
for bx, by in ((30, 28), (24, 33), (46, 35), (52, 37), (12, 30)):  # boats (two blocks wide)
    rect(bx, by, bx + 1, by, "O")

Path(__file__).with_name("plan_stage1.txt").write_text("".join("".join(r) + "\n" for r in g))
print("    " + "".join(str(x // 10 % 10) if x % 10 == 0 else " " for x in range(W)))
print("    " + "".join(str(x % 10) for x in range(W)))
for y, r in enumerate(g):
    print(f"{y:2d}  " + "".join(r))
