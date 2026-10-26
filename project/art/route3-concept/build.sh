#!/bin/sh
# Rebuild Route 3 from its concept with pae: lay out the plan, build the tileset (the kit's primary and the route's
# own cliffs), paint the map, keep its joins to Pewter City and Route 4, make the seams, put the events where the new
# route has them. Run from the repository root (project/art/build_all.sh rebuilds every map).
set -e
A=project/art/route3-concept
python3 $A/make_art.py
cd engine
P="-p ."
M=Route3_Frlg

# the tileset and the block files (the first time)
grep -q "gTileset_Route3Concept =" src/data/tilesets/headers.h || pae tileset new gTileset_Route3Concept --secondary $P
pae map geometry $M --primary gTileset_PalletConcept_General --secondary gTileset_Route3Concept \
    --blockdata data/layouts/Route3_Concept/map.bin --border data/layouts/Route3_Concept/border.bin \
    --width 84 --height 20 $P

pae tileset build ../$A/spec.json $P
pae map paint $M ../$A/grid.txt ../$A/legend.json --names ../$A/names.json --border ../$A/border.txt $P

# the joins stay where they were: Pewter's road east (its rows 24-27) meets the left edge at rows 9-12, Route 4's road
# (its columns 8-15) the top at columns 68-75
pae map connect $M left PewterCity_Frlg --offset -15 $P
pae map connect $M up Route4_Frlg --offset 60 $P
[ -n "$KIT_BUILD_ALL" ] || { pae seam build $M $P; pae seam build PewterCity_Frlg $P; }

# events: the trainers keep their scripts (and their battles)
pae map place $M object 7 17 10 $P   # Colton, at the field's west edge: he looks east across it
pae map place $M object 8 20 4 $P    # Ben, on the high path: he looks down across it
pae map place $M object 4 28 4 $P    # Greg, further along the high path
pae map place $M object 3 36 6 $P    # Sally, at the high path's east end: she looks back west along it
pae map place $M object 2 16 7 $P    # James, at the top of the lane: he looks east along the high path
pae map place $M object 5 41 11 $P   # Calvin, at the field's east edge: he looks west across it
pae map place $M object 6 41 14 $P   # Janice, beside him lower down
pae map place $M object 1 30 12 $P   # Robin, wandering in the field
pae map place $M object 0 63 11 $P   # the hiker from Cerulean, resting at the rest stop
pae map place $M object 9 14 13 $P   # Skitty (by day), by the way in
pae map place $M object 10 51 14 $P  # Arbok, by the rocks past the outcrop
pae map place $M object 11 34 4 $P   # Jigglypuff, on the high path
pae map place $M object 12 62 8 $P   # Sandshrew, at the rest stop
pae map place $M object 13 78 11 $P  # Nincada (by night), in the grass east of the pass
pae map place $M bg 0 67 10 $P       # the route sign, at the rest stop
pae map place $M bg 1 26 9 $P        # the hidden Oran Berry, in the field
