#!/bin/sh
# Rebuild Route 1 from the concept art with pae: draw the tiles, build the tileset (the kit's primary and the
# route's own), paint the map, join it to Viridian City and Pallet Town, make the connection seams, put the events
# where the new route has them. Run from the repository root (project/art/build_all.sh rebuilds every map).
set -e
A=project/art/route1-concept
python3 $A/make_art.py
python3 project/art/kit/settle.py $A  # the kit's small pieces into the ground they stand in
cd engine
P="-p ."
M=Route1_Frlg

# the tileset and the block files (the first time)
grep -q "gTileset_Route1Concept =" src/data/tilesets/headers.h || pae tileset new gTileset_Route1Concept --secondary $P
pae map geometry $M --primary gTileset_PalletConcept_General --secondary gTileset_Route1Concept \
    --blockdata data/layouts/Route1_Concept/map.bin --border data/layouts/Route1_Concept/border.bin $P

pae tileset build ../$A/spec.json $P
pae map paint $M ../$A/grid.txt ../$A/legend.json --names ../$A/names.json --border ../$A/border.txt $P

# the joins stay where they were: Viridian's road (its columns 24-27) meets the top at columns 22-25, Pallet's
# road (its columns 14-15) the bottom at columns 24-25
pae map connect $M up ViridianCity_Frlg --align 22,24 $P
pae map connect $M down PalletTown_Frlg --align 24,14 $P
[ -n "$KIT_BUILD_ALL" ] || pae seam build $M $P  # build_all.sh makes them last, when every map is painted

# events
pae map place $M object 0 23 20 $P   # the Poké Mart clerk with a sample, by the road
pae map place $M object 1 31 16 $P   # the boy who tells you about ledges, under the second one
pae map place $M object 2 12 17 $P   # a Pidgey by the stream
pae map place $M object 3 23 25 $P   # a Pidgey by the steps
pae map place $M object 5 12 7 $P    # a Rattata in the grass at the top
pae map place $M object 6 33 22 $P   # a Poochyena in the grass
pae map place $M object 7 5 30 $P    # the shiny Rattata in the clearing across the bridge
pae map place $M object 8 21 33 $P   # the Pidgey you shelter (the opening scene), beside the road
pae map place $M object 9 24 25 $P   # Blue, at the top of the last steps
pae map place $M bg 0 23 33 $P       # the route sign, by the arch
