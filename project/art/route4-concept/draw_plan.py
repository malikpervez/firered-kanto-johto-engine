#!/usr/bin/env python3
"""Draws Route 4's block plan (plan_stage1.txt): the concept, as shapes. Edit the shapes here and run it again;
make_art.py builds the map from the plan. Run from the repository root:
python3 project/art/route4-concept/draw_plan.py

Route 4 runs round Mt. Moon, the mountain in its west third (cliffs), which only its cave goes through:
- **the foot of the mountain** (west of it): Route 3's road comes up from the bottom (columns 8-15), past the Pokémon
  Center (heal spot in front of it) to Mt. Moon's mouth at the foot of the mountain's face;
- **the high shelf** (east of it), where Mt. Moon's far mouth opens: Jessie and Meowth by the cave, the route sign, the
  two martial artists who teach their moves, the stranger by his rock, Crissy and the TM. Its only way on is down
  its ledge (you can't climb back, so the far mouth can't be reached from Cerulean);
- **the road down to Cerulean** (the right edge, rows 10-13) along the bottom, past tall grass, the Friends' camp (the
  third scene, at 83,14) and a pond with its lawn under the cliff.

Letters: the kit's legend (T forest, . lawn, : dirt, g tall grass, _ ledges, ~ pond, * flowers, o rocks, b bushes,
S signs), C cliffs and the buildings: Z the Pokémon Center, X and Y the two mouths of Mt. Moon (the near one at the
foot of the mountain's face, the far one set into the cliff with no face over it).
"""
from pathlib import Path

W, H = 108, 20
g = [["." for _ in range(W)] for _ in range(H)]


def rect(x0, y0, x1, y1, c):
    for y in range(y0, y1 + 1):
        for x in range(x0, x1 + 1):
            g[y][x] = c


def at(x, y, c):
    g[y][x] = c


# the frame
rect(0, 0, 1, 19, "T")             # the forest west
rect(2, 0, 15, 3, "C")             # the cliff over the Center, its face on rows 2-3
rect(16, 0, 23, 9, "C")            # Mt. Moon: its face over the near mouth on rows 8-9...
rect(24, 0, 33, 19, "C")           # ...and its bulk, down to the bottom: the mountain divides the route
rect(34, 0, 39, 1, "C")            # the mountain's top over the far mouth...
rect(40, 0, 99, 1, "T")            # ...and the forest along the top east of it (it runs on into the border's: no cliff
                                   #  face cut off by the map's edge)
rect(100, 0, 107, 1, "T")          # (forest by the join: old Cerulean has no palette slot for the cliffs or water)
rect(0, 16, 7, 19, "C"); rect(16, 16, 23, 19, "C")   # Route 3's mountains either side of its road, carried on up
rect(24, 18, 33, 19, "T")          # the forest at the foot of Mt. Moon's south face (rows 16-17; nothing joins below)
rect(34, 18, 107, 19, "T")         # the forest along the bottom east of the mountain
rect(106, 2, 107, 9, "T"); rect(106, 14, 107, 17, "T")

# the foot of the mountain: Route 3's road up past the Center to the near mouth
rect(8, 10, 15, 19, ":")           # Route 3's road (the bottom, columns 8-15)...
rect(8, 16, 9, 19, "."); rect(14, 16, 15, 19, ".")   # ...between the mountains 4 wide with lawn verges, as Route 3's
rect(4, 5, 8, 8, "Z")              # the Pokémon Center, door (6,8)
rect(5, 9, 15, 9, ":"); rect(6, 9, 6, 9, ":")
rect(16, 15, 20, 15, ":")          # the way along the mountain's foot to the near mouth's door (19,14), no further
rect(17, 10, 22, 14, "X")          # the near mouth of Mt. Moon, door (19,14)
at(16, 12, "S")                    # Mt. Moon's sign (read from 16,13)
rect(2, 11, 5, 13, "*"); at(3, 14, "o"); at(14, 5, "o"); at(10, 4, "*"); at(11, 4, "*")
rect(9, 5, 13, 7, ".")

# the high shelf east of the mountain, from the far mouth along to the TM; its ledge down to the road
rect(34, 2, 39, 4, "C"); rect(34, 5, 39, 6, "Y")   # the far mouth (Mt. Moon's way out), door (36,6), its face set
                                                  # into the cliff, the cliff's top over it
rect(34, 7, 90, 8, ".")
rect(40, 2, 90, 6, ".")
rect(40, 5, 90, 6, ":")            # the shelf's path
rect(35, 7, 40, 7, ":")            # from the far mouth's door to it
rect(34, 9, 90, 9, "_")            # its ledge
rect(91, 2, 91, 9, "b")            # its east end
at(44, 3, "S")                     # the route sign (read from 44,4)
rect(48, 2, 49, 3, "*"); rect(54, 2, 55, 3, "*"); at(65, 3, "o"); at(80, 7, "o"); rect(70, 2, 72, 3, "*")

# the road down to Cerulean, the grass, the Friends' camp and the pond
rect(34, 12, 105, 13, ":")         # the road east
rect(100, 10, 107, 13, ":")        # to Cerulean (the right edge, rows 10-13)
rect(104, 10, 107, 13, "=")        # its cobbles start here and run on into Cerulean's
rect(60, 14, 77, 17, "g"); rect(60, 10, 70, 11, "g")
rect(78, 11, 87, 16, ".")          # the Friends' camp: a clearing of trodden earth the road opens into
rect(79, 11, 86, 15, ":"); rect(78, 12, 87, 13, ":")
at(78, 11, "k"); at(87, 11, "k")   # (two stumps at its corners to sit on)
rect(93, 3, 99, 7, "~")            # the pond under the forest (west of the 7 columns Cerulean shows)
rect(92, 8, 105, 9, "."); rect(92, 2, 105, 2, "."); rect(100, 3, 105, 7, "."); rect(92, 3, 92, 7, ".")
rect(100, 8, 100, 9, "*")          # (flowers too stay out of those columns: the plants palette)
at(95, 4, "v"); at(97, 6, "r")
rect(36, 14, 40, 16, "*"); rect(46, 10, 48, 11, "*"); rect(82, 16, 85, 17, "*"); rect(66, 7, 68, 8, "*"); at(44, 15, "o"); at(52, 16, "o"); at(89, 15, "o"); rect(92, 15, 96, 16, "*")

Path(__file__).with_name("plan_stage1.txt").write_text("".join("".join(r) + "\n" for r in g))
print("     " + "".join(str(x // 10 % 10) if x % 10 == 0 else " " for x in range(W)))
print("     " + "".join(str(x % 10) for x in range(W)))
for y, r in enumerate(g):
    print(f"{y:2d}   " + "".join(r))
