#!/bin/sh
# Rebuild Viridian City from the concept with pae: lay out the plan, build the tileset (the kit's primary and the
# town's own), paint the map, join it to Route 2, Route 22 and Route 1, make the connection seams and the doors, put
# the events where the new town has them. Run from the repository root (project/art/build_all.sh rebuilds every map).
set -e
A=project/art/viridian-concept
K=project/art/kit/buildings
python3 $A/make_art.py
cd engine
P="-p ."
M=ViridianCity_Frlg

# the tileset and the block files (the first time); the town is 60x52 now
grep -q "gTileset_ViridianConcept =" src/data/tilesets/headers.h || pae tileset new gTileset_ViridianConcept --secondary $P
pae map geometry $M --primary gTileset_PalletConcept_General --secondary gTileset_ViridianConcept \
    --blockdata data/layouts/ViridianCity_Concept/map.bin --border data/layouts/ViridianCity_Concept/border.bin \
    --width 60 --height 52 $P

pae tileset build ../$A/spec.json $P
pae map paint $M ../$A/grid.txt ../$A/legend.json --names ../$A/names.json --border ../$A/border.txt $P

# the joins stay where they were: Route 2's road (its columns 6-11) meets the top at columns 22-27, Route 22's (its
# rows 6-9) the left edge at rows 28-31, Route 1's (its columns 22-25) the bottom at columns 24-27
pae map connect $M up Route2_Frlg --offset 16 $P
pae map connect $M left Route22_Frlg --offset 22 $P
pae map connect $M down Route1_Frlg --offset 2 $P
# (Route 22, not rebuilt yet, has no room for Viridian's strip: it gets its seams when it's rebuilt from the kit)
[ -n "$KIT_BUILD_ALL" ] || pae seam build $M --skip Route22_Frlg $P  # build_all.sh makes them last

# doors, drawn in their packs: two blocks tall (the door and the block above it)
pae door add $M 20 27 --frames ../$K/pokemon_center/pokemon_center_door.png --sound sliding $P
pae door add $M 31 27 --frames ../$K/poke_mart/poke_mart_door.png --sound sliding $P
pae door add $M 44 20 --frames ../$A/buildings/viridian_gym/viridian_gym_door.png $P
pae door add $M 12 38 --frames ../$A/buildings/trainer_school/trainer_school_door.png $P
pae door add $M 44 33 --frames ../$A/buildings/house_family/house_family_door.png $P

# events
pae map place $M warp 0 20 27 $P              # Pokémon Center
pae map place $M warp 1 44 33 $P              # the house (the family's, on the eastern lane)
pae map place $M warp 2 44 20 $P              # Gym
pae map place $M warp 3 12 38 $P              # Trainer School
pae map place $M warp 4 31 27 $P              # Poké Mart
pae map place $M coord 0 25 12 $P             # the old man lies across the road north: "private property"
pae map place $M coord 1 44 21 $P             # the Gym's doors are locked (you step back down the court)
pae map place $M coord 2 25 13 $P             # up again, he stands by the road and shows you how to catch
pae map place $M bg 0 5 32 $P                 # trainer tips, by the road west
pae map place $M bg 1 48 20 $P                # the Gym's sign, by its court
pae map place $M bg 2 15 39 $P                # trainer tips, by the school
pae map place $M bg 3 23 42 $P                # town sign, by the road from Route 1
pae map place $M bg 4 44 20 $P                # the Gym's door
pae map place $M bg 5 36 40 $P                # the gardener's house: locked
pae map place $M bg 6 9 17 $P                 # the pond keeper's cottage: locked
pae map place $M object 0 17 37 $P            # the Dream Eater tutor, by the school garden
pae map place $M object LOCALID_VIRIDIAN_OLD_MAN 46 23 $P     # watches the Gym
pae map place $M object LOCALID_TUTORIAL_MAN 26 14 $P         # (the old man; his script puts him on the road)
pae map place $M object LOCALID_VIRIDIAN_WOMAN 27 14 $P       # his granddaughter, below the road north
pae map place $M object 4 14 32 $P            # the youngster
pae map place $M object 5 21 22 $P            # the boy, by the pond
pae map place $M object LOCALID_VIRIDIAN_BORDER_TREE 48 42 $P # the tree to cut, at the way into the grove
pae map place $M object 7 53 44 $P            # a Potion in the grove
pae map place $M object 8 5 20 $P             # a Pidgey by the pond
pae map place $M object 9 37 29 $P            # the gentleman

# the Friends story's group (the same shape, on the lawn east of the square; its anchor is in
# src/data/friends_scene_locations.h)
for who in BRIAN:50,28 HAM:48,28 JON:49,27 NICK:51,29 X:49,29 LB:47,29 TIM:51,27; do
    n=${who%%:*}; xy=${who#*:}
    pae map place $M object LOCALID_FRIENDS_VIRIDIANCITY_FRLG_$n ${xy%,*} ${xy#*,} $P
done
