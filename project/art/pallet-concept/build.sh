#!/bin/sh
# Rebuild Pallet Town from the concept art with pae: draw the tiles, build the tilesets, paint the map, join it to
# Route 1 and Route 21, make the connection seams and door animations, put the events where the new town has them
# and walk Oak's cutscenes along its roads. Run from the repository root.
set -e
A=project/art/pallet-concept
python3 $A/make_art.py
cd engine
P="-p ."
M=PalletTown_Frlg

# the tilesets and the block files (the first time)
grep -q "gTileset_PalletConcept_General =" src/data/tilesets/headers.h || pae tileset new gTileset_PalletConcept_General --primary $P
grep -q "gTileset_PalletConcept =" src/data/tilesets/headers.h || pae tileset new gTileset_PalletConcept --secondary $P
pae map geometry $M --primary gTileset_PalletConcept_General --secondary gTileset_PalletConcept \
    --blockdata data/layouts/PalletTown_Concept/map.bin --border data/layouts/PalletTown_Concept/border.bin $P

pae tileset build ../$A/spec.json $P
pae map paint $M ../$A/grid.txt ../$A/legend.json --names ../$A/names.json --border ../$A/border.txt $P

# the road north meets Route 1's (its columns 24-25), the channel south Route 21's water (its columns 7-10)
pae map connect $M up Route1_Frlg --align 14,24 $P
pae map connect $M down Route21_North_Frlg --align 18,7 $P
[ -n "$KIT_BUILD_ALL" ] || pae seam build $M $P  # build_all.sh makes them last, when every map is painted
pae door add $M 7 7 --frames ../$A/buildings/red_house/red_house_door.png $P    # your house's door (drawn frames)
pae door add $M 18 7 --frames ../$A/buildings/blue_house/blue_house_door.png $P  # your rival's
pae door add $M 21 15 --panel 1,0,15,14 $P  # Oak's lab

# events
pae map place $M warp 0 7 7 $P               # your house
pae map place $M warp 1 18 7 $P              # your rival's
pae map place $M warp 2 21 15 $P             # Oak's lab
pae map place $M coord 0 14 1 $P             # Oak stops you (left of the road)
pae map place $M coord 1 15 1 $P             # (right)
pae map place $M coord 2 15 2 $P             # the sign lady by the road north
pae map place $M bg 0 19 16 $P               # Oak's lab sign
pae map place $M bg 1 6 8 $P                 # your house's sign (in the fence by the gate)
pae map place $M bg 2 17 8 $P                # your rival's
pae map place $M bg 3 13 11 $P               # town sign
pae map place $M bg 4 10 20 $P               # trainer tips
pae map place $M object LOCALID_PALLET_SIGN_LADY 13 14 $P
pae map place $M object LOCALID_PALLET_FAT_MAN 18 17 $P
pae map place $M object LOCALID_PALLET_PROF_OAK 14 9 $P
pae map place $M object LOCALID_B2_PALLET_GUIDE 12 10 $P
pae map place $M object 5 25 3 $P            # Pineco in the pines
pae map place $M object 8 30 1 $P
pae map place $M object 9 24 18 $P           # Mr. Mime by the pond

# Oak's walks. Stopped at the road north, he comes up from the town, then leads you to the lab: he walks to the
# block below its door and you follow one step behind.
pae map path $M 14,9 14,2 --write PalletTown_Movement_OakEnterLeft $P
pae map path $M 14,9 15,2 --write PalletTown_Movement_OakEnterRight $P
pae map path $M 14,2 21,16 --then walk_in_place_faster_up --write PalletTown_Movement_OakWalkToLabLeft $P
pae map path $M 15,2 21,16 --then walk_in_place_faster_up --write PalletTown_Movement_OakWalkToLabRight $P
pae map path $M 14,1 14,2 21,16 --stop-short 1 --write PalletTown_Movement_PlayerWalkToLabLeft $P
pae map path $M 15,1 15,2 21,16 --stop-short 1 --write PalletTown_Movement_PlayerWalkToLabRight $P
pae map path $M 21,17 21,15 --then set_invisible --write PalletTown_Movement_PlayerEnterLab $P
# After the League he meets you at your door (from out of sight) and takes you to the lab, or leaves.
pae map path $M 15,15 7,9 --then walk_in_place_faster_up --write PalletTown_Movement_OakWalkToPlayersDoor $P
pae map path $M 7,9 21,16 --then walk_in_place_faster_up --write PalletTown_Movement_OakWalkToLabFromHouse $P
pae map path $M 7,8 7,9 21,16 --stop-short 1 --write PalletTown_Movement_PlayerWalkToLabFromHouse $P
pae map path $M 7,9 15,15 --write PalletTown_Movement_OakExit $P

# the Friends story's group (the same shape, on the lawn south of the garden; its anchor is in
# src/data/friends_scene_locations.h)
for who in BRIAN:12,22 HAM:14,22 JON:10,22 NICK:11,23 X:13,23 LB:11,20 TIM:8,22; do
    n=${who%%:*}; xy=${who#*:}
    pae map place $M object LOCALID_FRIENDS_PALLETTOWN_FRLG_$n ${xy%,*} ${xy#*,} $P
done
