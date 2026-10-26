#!/bin/sh
# Rebuild Vermilion City from its concept with pae: lay out the plan, build the tileset (the kit's primary and the
# town's own), paint the map, keep its joins to Route 6 and Route 11, make the seams and the doors, put the events
# where the new town has them. Run from the repository root (project/art/build_all.sh rebuilds every map).
set -e
A=project/art/vermilion-concept
K=project/art/kit/buildings
V=project/art/viridian-concept/buildings
python3 $A/make_art.py
cd engine
P="-p ."
M=VermilionCity_Frlg

# the tileset and the block files (the first time)
grep -q "gTileset_VermilionConcept =" src/data/tilesets/headers.h || pae tileset new gTileset_VermilionConcept --secondary $P
pae map geometry $M --primary gTileset_PalletConcept_General --secondary gTileset_VermilionConcept \
    --blockdata data/layouts/VermilionCity_Concept/map.bin --border data/layouts/VermilionCity_Concept/border.bin \
    --width 60 --height 42 $P

pae tileset build ../$A/spec.json $P
pae map paint $M ../$A/grid.txt ../$A/legend.json --names ../$A/names.json --border ../$A/border.txt $P

# the joins stay where they were: Route 6's road (its columns 40-42) meets the top at columns 32-34, Route 11's (its
# rows 14-17) the right edge at rows 11-14
pae map connect $M up Route6_Frlg --offset -8 $P
pae map connect $M right Route11_Frlg --offset -3 $P
[ -n "$KIT_BUILD_ALL" ] || pae seam build $M $P

# doors, drawn in their packs
pae door add $M 28 6 --frames ../$K/pokemon_center/pokemon_center_door.png --sound sliding $P
pae door add $M 37 6 --frames ../$K/poke_mart/poke_mart_door.png --sound sliding $P
pae door add $M 16 9 --frames ../$V/trainer_school/trainer_school_door.png $P
pae door add $M 10 20 --frames ../$V/viridian_gym/viridian_gym_door.png $P
pae door add $M 9 9 --frames ../$V/house_gardener/house_gardener_door.png $P
pae door add $M 22 19 --frames ../$V/house_family/house_family_door.png $P
pae door add $M 45 19 --frames ../$V/house_pond_keeper/house_pond_keeper_door.png $P

# events: every warp keeps its number (the buildings behind them point at it)
pae map place $M warp 0 37 41 $P   # the S.S. Anne's gangway, at the pier's end
pae map place $M warp 1 38 41 $P
pae map place $M warp 2 39 41 $P
pae map place $M warp 3 9 9 $P     # the small house west of the plaza
pae map place $M warp 4 28 6 $P    # the Pokémon Center
pae map place $M warp 5 16 9 $P    # the Fan Club
pae map place $M warp 6 22 19 $P   # the family house south of the street
pae map place $M warp 7 37 6 $P    # the Poké Mart
pae map place $M warp 8 45 19 $P   # the house by the quay
pae map place $M warp 9 10 20 $P   # the Gym
# the people keep their order (the Squirtle story and the Friends are called by local id)
pae map place $M object 0 36 12 $P    # a woman on the main street
pae map place $M object 1 45 27 $P    # the old sailor on the quay...
pae map place $M object 4 46 29 $P    # ...and his mate
pae map place $M object 2 49 10 $P    # the old man at the empty lot's gate...
pae map place $M object 3 48 6 $P     # ...and his Machop, stamping the ground flat in it
pae map place $M object 5 39 40 $P    # the ferry sailor, at the pier's end: his ticket check is on 37-38 before him
pae map place $M object 6 15 15 $P    # the tree to cut, in the Gym yard's gate
pae map place $M object 7 25 8 $P     # Oak's aide, on the plaza
pae map place $M object 8 40 9 $P     # Spearow on the plaza, Raichu by the family house
pae map place $M object 9 19 18 $P
pae map place $M object 10 50 26 $P   # Officer Jenny and the Squirtle on the quay, the crate the other two are under
pae map place $M object 11 51 26 $P
pae map place $M object 12 49 28 $P
pae map place $M object 13 48 28 $P
pae map place $M object 14 50 28 $P
pae map place $M coord 0 37 40 $P     # the ferry sailor's ticket check...
pae map place $M coord 1 38 40 $P
pae map place $M coord 2 37 39 $P     # ...and the blocks before it that end it
pae map place $M coord 3 38 39 $P
pae map place $M bg 0 31 7 $P         # the city sign, at the plaza
pae map place $M bg 1 19 9 $P         # the Fan Club's sign
pae map place $M bg 2 15 18 $P        # the Gym's sign, in its yard
pae map place $M bg 3 36 21 $P        # the harbour's sign, by the pier's head
pae map place $M bg 4 55 10 $P        # the Snorlax notice, by the road to Route 11
pae map place $M bg 5 54 30 $P        # the hidden Max Ether, at the quay's corner
# (the Friends, objects 15-21, camp round 30,19 as before: src/data/friends_scene_locations.h)
