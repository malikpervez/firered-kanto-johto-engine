#!/bin/sh
# Rebuild Cerulean City from its concept with pae: lay out the plan, build the tileset (the kit's primary and the
# town's own), paint the map, keep its joins to Routes 4, 5, 9 and 24, make the seams and the doors, put the events
# where the new town has them. Run from the repository root (project/art/build_all.sh rebuilds every map).
set -e
A=project/art/cerulean-concept
K=project/art/kit/buildings
V=project/art/viridian-concept/buildings
python3 $A/make_art.py
python3 project/art/kit/settle.py $A  # the kit's small pieces into the ground they stand in
cd engine
P="-p ."
M=CeruleanCity_Frlg

# the tileset and the block files (the first time)
grep -q "gTileset_CeruleanConcept =" src/data/tilesets/headers.h || pae tileset new gTileset_CeruleanConcept --secondary $P
pae map geometry $M --primary gTileset_PalletConcept_General --secondary gTileset_CeruleanConcept \
    --blockdata data/layouts/CeruleanCity_Concept/map.bin --border data/layouts/CeruleanCity_Concept/border.bin \
    --width 58 --height 51 $P

pae tileset build ../$A/spec.json $P
pae map paint $M ../$A/grid.txt ../$A/legend.json --names ../$A/names.json --border ../$A/border.txt $P

# the joins stay where they were: Nugget Bridge (Route 24's columns 16-19) meets the top at columns 41-44, Route 4's
# road (its rows 10-13) the left edge at rows 17-20, Route 9's (its rows 8-10 since its rebuild) the right edge at
# rows 28-30, Route 5's (its columns 29-32) the bottom at columns 21-24
pae map connect $M up Route24_Frlg --offset 25 $P
pae map connect $M down Route5_Frlg --offset -8 $P
pae map connect $M left Route4_Frlg --offset 7 $P
pae map connect $M right Route9_Frlg --offset 20 $P
[ -n "$KIT_BUILD_ALL" ] || pae seam build $M $P  # build_all.sh makes them last, when every map is painted

# doors, drawn in their packs (one for each kind of building: the frames go with its door's metatile)
pae door add $M 28 28 --frames ../$K/pokemon_center/pokemon_center_door.png --sound sliding $P
pae door add $M 27 41 --frames ../$K/poke_mart/poke_mart_door.png --sound sliding $P
pae door add $M 47 36 --frames ../$V/viridian_gym/viridian_gym_door.png $P
pae door add $M 10 41 --frames ../$V/trainer_school/trainer_school_door.png $P
pae door add $M 35 22 --frames ../$V/house_family/house_family_door.png $P
pae door add $M 15 29 --frames ../$V/house_gardener/house_gardener_door.png $P

# events: every warp keeps its number (the buildings behind them point at it)
pae map place $M warp 0 48 11 $P   # the badge house, east of the bridge road...
pae map place $M warp 8 48 7 $P    # ...and its back door, from its yard
pae map place $M warp 1 35 22 $P   # the robbed house...
pae map place $M warp 9 35 18 $P   # ...and the hole in its back wall, from the backyard
pae map place $M warp 10 36 18 $P
pae map place $M warp 2 15 29 $P   # the small house in the west
pae map place $M warp 3 28 28 $P   # the Pokémon Center
pae map place $M warp 4 47 36 $P   # the Gym
pae map place $M warp 5 10 41 $P   # the Bike Shop (its three warps: one door)
pae map place $M warp 11 10 41 $P
pae map place $M warp 14 10 41 $P
pae map place $M warp 6 27 41 $P   # the Poké Mart
pae map place $M warp 7 6 6 $P     # Cerulean Cave, on its island
pae map place $M warp 12 32 41 $P  # the small house by the Mart
pae map place $M warp 13 48 18 $P  # the berry man's house
# the people keep their order (the story's scenes call some by number: the Friends from 19)
pae map place $M object 0 36 23 $P    # the policeman, by the robbed house (until the S.S. Ticket: in its door)
pae map place $M object 1 38 17 $P    # the Rocket, in the backyard's way out
pae map place $M object 2 26 44 $P    # the little boy who'd cut the tree, by the neck
pae map place $M object 3 7 32 $P     # the balding man, on the west lawn
pae map place $M object 4 28 46 $P    # Slowbro and the lass, south of the Mart (until the S.S. Ticket: in the neck,
pae map place $M object 5 27 46 $P    #  scripts.inc)
pae map place $M object 6 30 35 $P    # the youngster, by the Friends' camp
pae map place $M object 7 41 1 $P     # Blue, on the bridge (his scene)
pae map place $M object 8 49 39 $P    # the tree to cut, in the garden's gap
pae map place $M object 10 15 40 $P   # the woman who wants a bicycle, by the Bike Shop
pae map place $M object 11 6 7 $P     # Cerulean Cave's guard, at its mouth
pae map place $M object 12 32 26 $P   # Psyduck, by the plaza's pool
pae map place $M object 13 37 38 $P   # Spearow, on the road past the Mart
pae map place $M object 14 5 46 $P    # the shelter's caretaker...
pae map place $M object 15 7 46 $P    # ...Bulbasaur,
pae map place $M object 16 6 44 $P    # ...Pidgey,
pae map place $M object 17 4 44 $P    # ...and the box
pae map place $M object 18 34 32 $P   # the Friends' camp (their anchor: 34,32 in src/data/friends_scene_locations.h)
pae map place $M object 19 33 31 $P
pae map place $M object 20 33 33 $P
pae map place $M object 21 35 31 $P
pae map place $M object 22 32 32 $P
pae map place $M object 23 31 31 $P
pae map place $M object 24 35 33 $P
pae map place $M bg 0 25 25 $P       # the town's sign, by the Center
pae map place $M bg 1 51 36 $P       # the Gym's sign
pae map place $M bg 2 14 38 $P       # the Bike Shop's sign
pae map place $M bg 3 19 41 $P       # trainer tips
pae map place $M bg 4 11 10 $P       # the hidden Rare Candy, on the cave's island
pae map place $M bg 5 8 41 $P        # the bicycles in the Bike Shop's windows
pae map place $M bg 6 11 41 $P
pae map place $M bg 7 12 41 $P
# (the triggers stay: Blue's across the bridge road at row 7, the Rocket's either side of him)
