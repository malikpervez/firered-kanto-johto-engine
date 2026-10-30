#!/bin/sh
# Rebuild Route 24 (Nugget Bridge) from its concept with pae: lay out the plan, build the tileset (the kit's primary;
# nothing of the route's own), paint the map, keep its joins to Cerulean City and Route 25, make the seams, put the
# events where the new route has them. Run from the repository root (project/art/build_all.sh rebuilds every map).
set -e
A=project/art/route24-concept
python3 $A/make_art.py
python3 project/art/kit/settle.py $A  # the kit's small pieces into the ground they stand in
cd engine
P="-p ."
M=Route24_Frlg

# the tileset and the block files (the first time)
grep -q "gTileset_Route24Concept =" src/data/tilesets/headers.h || pae tileset new gTileset_Route24Concept --secondary $P
pae map geometry $M --primary gTileset_PalletConcept_General --secondary gTileset_Route24Concept \
    --blockdata data/layouts/Route24_Concept/map.bin --border data/layouts/Route24_Concept/border.bin \
    --width 30 --height 22 $P

pae tileset build ../$A/spec.json $P
pae map paint $M ../$A/grid.txt ../$A/legend.json --names ../$A/names.json --border ../$A/border.txt $P

# the joins stay where they were: Cerulean's bridge road (its columns 41-44) meets the bottom at columns 16-19, Route
# 25's bridge the top at the same columns (with its west and east paths at 7-10 and 24-25)
pae map connect $M down CeruleanCity_Frlg --offset -25 $P
pae map connect $M up Route25_Frlg --offset 0 $P
[ -n "$KIT_BUILD_ALL" ] || pae seam build $M $P

# events: the people keep their order and their scripts; the Rocket and his triggers stay where they were (his scene
# walks him one block along row 8)
pae map place $M object 0 18 8 $P    # the Rocket, at the bridge's north end
pae map place $M object 5 19 19 $P   # the bridge's five trainers, each at a side looking across it: Cale first,
pae map place $M object 4 16 17 $P   #  then Ali,
pae map place $M object 3 19 15 $P   #  Timmy,
pae map place $M object 2 16 13 $P   #  Reli,
pae map place $M object 1 19 11 $P   #  and Ethan
pae map place $M object 6 8 12 $P    # Shane, at the west shore's foot: he looks up across it
pae map place $M object 7 5 3 $P     # the TM, at the top of the west shore
pae map place $M object 8 5 7 $P     # Abra, in the shore's tall grass
pae map place $M object 9 21 3 $P    # Surskit (by day), on the water east of the bridge
pae map place $M object 10 9 5 $P    # Spoink (by night), on the shore
pae map place $M object 11 24 10 $P  # the shelter's traveler, on the east meadow...
pae map place $M object 12 25 10 $P  # ...the Charmander he looks after...
pae map place $M object 13 24 9 $P   # ...and his box
pae map place $M bg 0 10 4 $P        # the hidden Pecha Berry, on the west shore
# the bridge is four blocks wide: its trainers see all of it (three blocks), so none can be passed unseen
python3 - <<'EOF'
import json
p = "data/maps/Route24_Frlg/map.json"
m = json.load(open(p))
for i in (1, 2, 3, 4, 5):
    m["object_events"][i]["trainer_sight_or_berry_tree_id"] = "3"
open(p, "w").write(json.dumps(m, indent=2) + "\n")
EOF
