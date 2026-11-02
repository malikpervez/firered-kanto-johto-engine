#!/bin/sh
# Rebuild Pewter City from its concept with pae: lay out the plan, build the tileset (the kit's primary and the town's
# own), paint the map, keep its joins to Route 2 and Route 3, make the seams and the doors, put the events where the
# new town has them. Run from the repository root (project/art/build_all.sh rebuilds every map).
set -e
A=project/art/pewter-concept
R=project/art/packs/buildings_v0.3/buildings  # the remakes pack: the Gym
K=project/art/kit/buildings
python3 $A/make_art.py
python3 project/art/kit/settle.py $A  # the kit's small pieces into the ground they stand in
cd engine
P="-p ."
M=PewterCity_Frlg

# the tileset and the block files (the first time)
grep -q "gTileset_PewterConcept =" src/data/tilesets/headers.h || pae tileset new gTileset_PewterConcept --secondary $P
pae map geometry $M --primary gTileset_PalletConcept_General --secondary gTileset_PewterConcept \
    --blockdata data/layouts/PewterCity_Concept/map.bin --border data/layouts/PewterCity_Concept/border.bin \
    --width 52 --height 44 $P

pae tileset build ../$A/spec.json $P
pae map paint $M ../$A/grid.txt ../$A/legend.json --names ../$A/names.json --border ../$A/border.txt $P

# the joins stay where they were: Route 2's road (its columns 8-11) meets the bottom at columns 22-25, Route 3's road
# (its rows 9-12) the right edge at rows 24-27
pae map connect $M down Route2_Frlg --offset 14 $P
pae map connect $M right Route3_Frlg --offset 15 $P
[ -n "$KIT_BUILD_ALL" ] || pae seam build $M $P  # build_all.sh makes them last, when every map is painted

# doors, drawn in their packs
pae door add $M 29 32 --frames ../$K/pokemon_center/pokemon_center_door.png --sound sliding $P
pae door add $M 34 32 --frames ../$K/poke_mart/poke_mart_door.png --sound sliding $P
pae door add $M 24 12 --frames ../project/art/route22-concept/buildings/league_front_gate/league_front_gate_door.png $P
pae door add $M 9 20 --frames ../$R/pewter_gym/pewter_gym_door.png $P
pae door add $M 30 20 --frames ../project/art/viridian-concept/buildings/house_family/house_family_door.png $P

# events: every warp keeps its number (the buildings behind them point at it)
pae map place $M warp 0 24 12 $P   # the Museum of Science
pae map place $M warp 1 37 10 $P   # its annex, behind the tree to cut
pae map place $M warp 2 9 20 $P    # the Gym
pae map place $M warp 3 34 32 $P   # the Poké Mart
pae map place $M warp 4 30 20 $P   # the house by the plaza
pae map place $M warp 5 29 32 $P   # the Pokémon Center
pae map place $M warp 6 10 33 $P   # the house in the south-west (the same house: its door's frames are added above)
pae map place $M object 0 15 25 $P   # the lass, on the road to the Gym
pae map place $M object LOCALID_PEWTER_MUSEUM_GUIDE 39 17 $P   # by the road east (he walks you to the Museum)
pae map place $M object 2 18 21 $P   # the fat man who talks about Brock, by the road to the Gym
pae map place $M object 3 16 36 $P   # the bug catcher with his Repel, on the lane south-west
pae map place $M object LOCALID_PEWTER_GYM_GUIDE 43 24 $P      # across the road east, where he always stood
pae map place $M object 5 32 12 $P   # the tree to cut, in the gap into the annex's yard
pae map place $M object LOCALID_PEWTER_AIDE 47 24 $P           # Oak's aide with the Running Shoes, further east
pae map place $M object 7 7 26 $P    # a Geodude by the forest
pae map place $M object 8 13 15 $P   # a Geodude under the cliff
pae map place $M object 9 34 9 $P    # a Pidgey in the annex's yard (on its lawn, not the roof)
pae map place $M object 10 31 36 $P  # a Spearow by the flowers south of the square
pae map place $M object 11 20 14 $P  # Nao, on the plaza
pae map place $M bg 0 32 15 $P       # the Museum's sign
pae map place $M bg 1 39 23 $P       # the police notice, by the road east
pae map place $M bg 2 13 20 $P       # the Gym's sign
pae map place $M bg 3 37 32 $P       # trainer tips, by the Mart
pae map place $M bg 4 26 35 $P       # the town's sign, by Route 2's road
pae map place $M bg 5 4 37 $P        # the hidden Poké Ball, in the forest's corner
