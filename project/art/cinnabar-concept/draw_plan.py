#!/usr/bin/env python3
"""Draws Cinnabar Island's block plan (plan_stage1.txt): the concept, as shapes. Edit the shapes here and run it
again; make_art.py builds the map from the plan. Run from the repository root:
python3 project/art/cinnabar-concept/draw_plan.py

Cinnabar is Kanto's volcanic island town, out in the southern sea. It is 96x44 blocks, as before, and its joins stay
where they were: Route 21's sea above (its columns 0-23, offset 0), Route 20's to the right (its rows 0-19, offset 0).
It has two islands:
- **the town island** at the top left: the burned Pokémon Mansion and Blaine's Gym backing onto the woods along
  the north shore (Route 21's foot), the street between them; the Pokémon Lab, the Pokémon Center and the Mart
  along the harbour street below; the east lane down to the harbour, where Bill's friend's Seagallop comes in; the
  beach along the south. The doors the island's scenes walk to stay where they were: the Center's at 14,11 (Bill
  goes back in through it), the Gym's at 20,4 (its lock at 20,5); Bill and the player still walk the harbour street
  (row 12) and the east lane (column 21) to the boat, which comes in from the east on rows 8 and 12.
- **the volcano island** to the east, across the harbour: the volcano's rock in the middle, its crater a pit of ash
  in its top (no way down into it), its slopes of ash and boulders round it, a hot spring below it, the woods and lawns where the Friends camp (round 46,20, Giratina's
  rift four blocks west of them); its Pokémon (Magmar, Magcargo, Slugma, Torkoal, Koffing) on the ash.

Letters: the kit's legend (T forest, . lawn, = cobble, : dirt (the ash), * flowers, ~ the hot spring, s the sea, q
and Q sea rocks, o boulders, S signs), C the volcano's rock (the cliffs), and the buildings: U the burned Mansion, H
Blaine's Gym, X the Pokémon Lab, Z the Pokémon Center, L the Mart.
"""
from pathlib import Path

W, H = 96, 44
g = [["s" for _ in range(W)] for _ in range(H)]


def rect(x0, y0, x1, y1, c):
    for y in range(y0, y1 + 1):
        for x in range(x0, x1 + 1):
            g[y][x] = c


def at(x, y, c):
    g[y][x] = c


# ---------------------------------------------------------------- the town island
rect(4, 0, 23, 4, ".")
rect(3, 5, 22, 15, ".")
rect(10, 0, 15, 3, "T")                        # the woods between the Mansion and the Gym
rect(4, 5, 22, 6, "=")                         # the street
rect(3, 12, 22, 13, "=")                       # the harbour street
rect(21, 7, 22, 11, "=")                       # the east lane down to the harbour
rect(4, 0, 9, 4, "U")                          # the burned Mansion, door 6,4
rect(17, 0, 23, 4, "H")                        # Blaine's Gym, door 20,4
rect(3, 7, 11, 11, "X")                        # the Pokémon Lab, door 6,11
rect(12, 8, 16, 11, "Z")                       # the Pokémon Center, door 14,11
rect(17, 8, 20, 11, "L")                       # the Mart, door 18,11
at(12, 6, "S")                                 # the island's sign
at(9, 12, "S")                                 # the Lab's sign (one board; the Lab's wall by its door reads too)
at(22, 5, "S")                                 # the Gym's sign
rect(5, 15, 8, 15, "*")
rect(16, 15, 19, 15, "*")

# ---------------------------------------------------------------- the volcano island
rect(40, 6, 80, 34, ".")
rect(36, 10, 84, 30, ".")
rect(50, 8, 80, 28, ":")                       # the ash round the volcano
rect(58, 10, 72, 11, "C")                      # the volcano's rock, narrower at its summit...
rect(54, 12, 76, 24, "C")
rect(62, 15, 68, 17, ":")                      # ...and the crater in its top: a pit of ash, its north wall a face
rect(36, 10, 39, 17, "T")                      # the woods on the west shore
rect(40, 30, 47, 33, "T")
rect(42, 8, 46, 9, "*")
rect(64, 30, 68, 32, "~")                      # the hot spring
rect(70, 31, 73, 32, "*")
for x, y in ((52, 12), (79, 14), (51, 23), (78, 25), (57, 27), (74, 9), (80, 20)):
    at(x, y, "o")                              # boulders on the ash
at(80, 8, "."); at(80, 9, ".")                 # the lawn wraps round the ash's north-east corner (no ash on the shore)
for x, y in ((52, 31), (53, 31), (54, 31), (53, 32), (54, 32), (82, 18), (83, 18), (83, 19)):
    at(x, y, "*")                              # flowers on the south lawn and the east strip
at(39, 26, "o")                                # a rock on the west lawn
for x, y in ((41, 13), (38, 22), (46, 27), (43, 29)):
    at(x, y, ",")                              # flowers in the west lawn's grass


# sea rocks round the islands, where open sea is all round them
def open_sea(x, y):
    return all(0 <= x + i < W and 0 <= y + j < H and g[y + j][x + i] == "s" for i in (-1, 0, 1) for j in (-1, 0, 1))


for k, (x, y) in enumerate([(27, 3), (30, 15), (27, 22), (8, 20), (16, 24), (4, 30), (24, 34), (14, 40),
                             (33, 39), (52, 39), (70, 40), (88, 36), (90, 24), (88, 8), (60, 2), (44, 2),
                             (34, 26)]):
    if open_sea(x, y):
        at(x, y, "q" if k % 2 else "Q")

Path(__file__).with_name("plan_stage1.txt").write_text("".join("".join(r) + "\n" for r in g))
