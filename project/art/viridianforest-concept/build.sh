#!/bin/sh
# Rebuild Viridian Forest from the concept with pae: lay out the plan, build the tileset (the kit's primary and the
# forest's own exit blocks), paint the map, put the events where the new forest has them. The forest has no joins
# (its gates are warps), so no seams. Run from the repository root (project/art/build_all.sh rebuilds every map).
set -e
A=project/art/viridianforest-concept
python3 $A/make_art.py
python3 project/art/kit/settle.py $A  # the kit's small pieces into the ground they stand in
cd engine
P="-p ."
M=ViridianForest_Frlg

# the tileset and the block files (the first time)
grep -q "gTileset_ViridianForestConcept =" src/data/tilesets/headers.h || pae tileset new gTileset_ViridianForestConcept --secondary $P
pae map geometry $M --primary gTileset_PalletConcept_General --secondary gTileset_ViridianForestConcept \
    --blockdata data/layouts/ViridianForest_Concept/map.bin --border data/layouts/ViridianForest_Concept/border.bin \
    --width 48 --height 60 $P

pae tileset build ../$A/spec.json $P
pae map paint $M ../$A/grid.txt ../$A/legend.json --names ../$A/names.json --border ../$A/border.txt $P

# events: the exits keep their warp numbers (the gates warp to 0 and 2); the forest is all one level, so the
# Pokémon that stood on the old forest's raised ground come down to it
pae map place $M warp 0 23 59 $P   # the south exit, to the south gate (its middle block: where you arrive)
pae map place $M warp 1 22 59 $P
pae map place $M warp 4 24 59 $P
pae map place $M warp 2 23 0 $P    # the north exit, to the north gate (its middle block: where you arrive)
pae map place $M warp 5 22 0 $P
pae map place $M warp 3 24 0 $P
pae map place $M object 0 14 29 $P   # the youngster, on the east approach to the pond
pae map place $M object 1 21 56 $P   # the boy, by the south exit
pae map place $M object 2 20 48 $P   # Rick, on the trail: he looks south across it
pae map place $M object 3 33 29 $P   # Doug, on the trail: he looks west across it
pae map place $M object 4 7 43 $P    # Sammy, on the west item branch
pae map place $M object 8 42 20 $P   # Anthony, on the north-east item branch
pae map place $M object 9 11 18 $P   # Charlie, on the north-west item branch
pae map place $M object 7 3 43 $P    # the Potion, at the end of the west branch
pae map place $M object 5 41 43 $P   # the Poké Ball, at the end of the south-east branch
pae map place $M object 6 41 13 $P   # the Antidote, at the end of the north-east branch
pae map place $M object 10 5 11 $P   # the second Potion, at the end of the north-west branch
pae map place $M object 11 38 45 --elevation 3 $P  # the forest's Pokémon, each with walkable ground round it: Caterpie,
pae map place $M object 18 35 55 --elevation 3 $P  # Weedle,
pae map place $M object 14 4 45 $P   # Paras,
pae map place $M object 12 12 30 $P  # Pikachu,
pae map place $M object 16 7 32 --elevation 3 $P   # Butterfree,
pae map place $M object 17 38 15 --elevation 3 $P  # Beedrill,
pae map place $M object 13 41 25 $P  # Weedle,
pae map place $M object 19 6 14 $P   # Caterpie,
pae map place $M object 20 28 7 $P   # Butterfree
pae map place $M object 15 21 43 $P  # and Paras
pae map place $M bg 0 26 56 $P       # the trainer tips, each read from the block below it
pae map place $M bg 4 8 41 $P
pae map place $M bg 1 14 35 $P
pae map place $M bg 2 33 24 $P
pae map place $M bg 5 16 12 $P       # (on the lawn beside the trail)
pae map place $M bg 3 25 2 $P        # the exit sign, beside the north exit (on the lawn by the trail)
pae map place $M bg 7 41 55 $P       # the hidden Antidote, in the south-east glade
pae map place $M bg 6 18 44 $P       # the hidden Potion, in the tall grass west of the trail
