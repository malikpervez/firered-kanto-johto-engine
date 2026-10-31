#!/bin/sh
# Rebuild Fuchsia City from its concept with pae: draw its buildings, lay out the plan, build the tileset (the kit's
# primary, the town's lodge and Gym, Viridian's houses), paint the map, keep its joins to Routes 18, 15 and 19, make
# the seams and the doors, put the events where the new town has them. Run from the repository root
# (project/art/build_all.sh rebuilds every map).
set -e
A=project/art/fuchsia-concept
B=project/art/packs/buildings_v0.3/buildings  # the remakes pack: the town's own buildings
K=project/art/kit/buildings
V=project/art/viridian-concept/buildings
python3 $A/make_art.py
python3 project/art/kit/settle.py $A  # the kit's small pieces into the ground they stand in
cd engine
P="-p ."
M=FuchsiaCity_Frlg

# the tileset and the block files (the first time)
grep -q "gTileset_FuchsiaConcept =" src/data/tilesets/headers.h || pae tileset new gTileset_FuchsiaConcept --secondary $P
pae map geometry $M --primary gTileset_PalletConcept_General --secondary gTileset_FuchsiaConcept \
    --blockdata data/layouts/FuchsiaCity_Concept/map.bin --border data/layouts/FuchsiaCity_Concept/border.bin \
    --width 48 --height 40 $P

pae tileset build ../$A/spec.json $P
pae map paint $M ../$A/grid.txt ../$A/legend.json --names ../$A/names.json --border ../$A/border.txt $P

# the joins: Route 18's road (its rows 8-10) at the left edge, rows 18-20; Route 15's (its rows 4-7) at the right,
# rows 20-23; Route 19's beach path (its columns 7-16) below, columns 19-28
pae map connect $M left Route18_Frlg --offset 10 $P
pae map connect $M right Route15_Frlg --offset 16 $P
pae map connect $M down Route19_Frlg --offset 12 $P
[ -n "$KIT_BUILD_ALL" ] || pae seam build $M $P

# doors, drawn in their packs (the house's back door is a doorway: it doesn't animate)
pae door add $M 19 31 --frames ../$K/pokemon_center/pokemon_center_door.png --sound sliding $P
pae door add $M 5 16 --frames ../$K/poke_mart/poke_mart_door.png --sound sliding $P
pae door add $M 23 6 --frames ../$B/safari_gate/safari_gate_door.png $P
pae door add $M 5 31 --frames ../$B/fuchsia_gym/fuchsia_gym_door.png $P
pae door add $M 29 16 --frames ../$V/house_gardener/house_gardener_door.png $P
pae door add $M 12 31 --frames ../$V/house_gardener/house_gardener_door.png $P
pae door add $M 31 31 --frames ../$V/house_family/house_family_door.png $P
pae door add $M 25 31 --frames ../$V/house_pond_keeper/house_pond_keeper_door.png $P
pae door add $M 37 31 --frames ../$B/house_pond_garden/house_pond_garden_door.png $P

# events: every warp keeps its number (the buildings behind them point at it)
pae map place $M warp 0 23 6 $P     # the Safari Zone's gate lodge
pae map place $M warp 1 31 31 $P    # the Warden's house
pae map place $M warp 2 5 16 $P     # the Mart
pae map place $M warp 3 29 16 $P    # the Safari Zone's office
pae map place $M warp 4 5 31 $P     # Koga's Gym
pae map place $M warp 5 12 31 $P    # a house on the shore street
pae map place $M warp 6 19 31 $P    # the Pokémon Center
pae map place $M warp 7 37 31 $P    # the house with the pond garden: its front door...
pae map place $M warp 8 37 28 $P    # ...and its back door (the house points at 8; 9 shares its block)
pae map place $M warp 9 37 28 $P
pae map place $M warp 10 25 31 $P   # a house on the shore street
# the people keep their order (the Friends' scene finds them by local id)
pae map place $M object 0 31 12 $P   # Erik, waiting by the Safari Zone's office
pae map place $M object 1 33 14 $P   # Slowpoke, dozing in the office's garden
pae map place $M object 2 32 5 $P    # Voltorb, in its yard
pae map place $M object 3 38 10 $P   # the youngster on the east walk, looking into Kangaskhan's yard
pae map place $M object 4 37 14 $P   # Chansey, in its yard
pae map place $M object 5 9 17 $P    # the little boy, by the Mart
pae map place $M object 6 13 5 $P    # Lapras, on its lake
pae map place $M object 7 24 12 $P   # the old man, on the avenue
pae map place $M object 8 3 4 $P     # the fossil Pokémon (Kabuto or Omanyte, by the fossil you chose), in its pen
pae map place $M object 9 38 5 $P    # Kangaskhan, in its yard
pae map place $M object 10 9 11 $P   # the trees to cut: the west walk's hedge...
pae map place $M object 11 30 11 $P  # ...the office garden's hedge...
pae map place $M object 12 17 26 $P  # ...the flower garden's...
pae map place $M object 13 22 27 $P  # ...and the lane's by the Center
pae map place $M object 14 12 12 $P  # the Substitute tutor, below the zoo's west walk
pae map place $M object 15 27 12 $P  # the lass who gossips about the Gym Leader (after the League)
pae map place $M object 16 21 36 $P  # Kabuto on the beach path
pae map place $M object 17 26 37 $P
pae map place $M object 18 15 6 $P   # Dratini, in Lapras's lake
pae map place $M object 19 12 7 $P
pae map place $M object 20 27 25 $P  # Cubone, in the park
pae map place $M object 21 7 4 $P    # Omanyte, in the fossil Pokémon's pen
pae map place $M object 22 3 7 $P
pae map place $M object 23 3 23 $P   # Kangaskhan, in the park
pae map place $M object 24 8 24 $P   # the Friends, round 8,24
pae map place $M object 25 6 24 $P
pae map place $M object 26 10 24 $P
pae map place $M object 27 7 26 $P
pae map place $M object 28 7 22 $P
pae map place $M object 29 9 23 $P
pae map place $M object 30 5 26 $P
pae map place $M bg 0 3 17 $P        # the town sign, by Route 18's road
pae map place $M bg 1 19 6 $P        # the Safari Zone's sign
pae map place $M bg 2 9 30 $P        # the Gym's sign
pae map place $M bg 3 34 30 $P       # the Warden's sign
pae map place $M bg 4 32 8 $P        # the pens' signs: Voltorb's...
pae map place $M bg 5 32 17 $P       # ...Slowpoke's...
pae map place $M bg 6 37 16 $P       # ...Chansey's...
pae map place $M bg 7 38 8 $P        # ...Kangaskhan's...
pae map place $M bg 8 5 8 $P         # ...the fossil Pokémon's...
pae map place $M bg 9 13 8 $P        # ...Lapras's
pae map place $M bg 10 27 6 $P       # the Safari Game's notice
pae map place $M bg 11 35 26 $P      # the hidden Max Revive, in the pond garden
# the Pokémon in the lake swim at the water's elevation, everyone else stands at the ground's; the walkers keep to
# their places
python3 - <<'PY'
import json
p = "data/maps/FuchsiaCity_Frlg/map.json"
m = json.load(open(p))
o = m["object_events"]
for e in o:
    if e.get("type") != "clone" and "elevation" in e:
        e["elevation"] = 3
for i in (6, 18, 19):
    o[i]["elevation"] = 1
for i, (rx, ry) in {5: (2, 0), 7: (1, 0), 1: (1, 1), 4: (2, 1), 9: (1, 1), 20: (2, 1), 23: (1, 1),
                     16: (2, 1), 17: (2, 1), 21: (1, 1), 22: (1, 1)}.items():
    o[i]["movement_range_x"], o[i]["movement_range_y"] = rx, ry
open(p, "w").write(json.dumps(m, indent=2) + "\n")
PY
