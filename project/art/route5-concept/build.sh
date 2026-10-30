#!/bin/sh
# Rebuild Route 5 from its concept with pae: lay out the plan, build the tileset (the kit's primary, the Day Care,
# the Underground Path's hut and Saffron's gate), paint the map, keep its joins to Cerulean City and Saffron, make the
# seams and the doors, put the events where the new route has them. Run from the repository root
# (project/art/build_all.sh rebuilds every map).
set -e
A=project/art/route5-concept
V=project/art/viridian-concept/buildings
python3 $A/make_art.py
python3 project/art/kit/settle.py $A  # the kit's small pieces into the ground they stand in
cd engine
P="-p ."
M=Route5_Frlg

# the tileset and the block files (the first time)
grep -q "gTileset_Route5Concept =" src/data/tilesets/headers.h || pae tileset new gTileset_Route5Concept --secondary $P
pae map geometry $M --primary gTileset_PalletConcept_General --secondary gTileset_Route5Concept \
    --blockdata data/layouts/Route5_Concept/map.bin --border data/layouts/Route5_Concept/border.bin \
    --width 50 --height 36 $P

pae tileset build ../$A/spec.json $P
pae map paint $M ../$A/grid.txt ../$A/legend.json --names ../$A/names.json --border ../$A/border.txt $P

# the joins stay where they were: Cerulean's neck (its columns 21-24) meets the top at columns 29-32, Saffron is
# below with its gate door (its 28-29) under the gate's top door here (24-25)
pae map connect $M up CeruleanCity_Frlg --offset 8 $P
pae map connect $M down SaffronCity_Connection_Frlg --offset -4 $P
# (old Saffron has no tile slot left for this route's strip, and neither can see the other: the gate and the forest
# fill this route's bottom rows, the gatehouse and forest Saffron's top ones. Their seam waits for Saffron's rebuild)
[ -n "$KIT_BUILD_ALL" ] || pae seam build $M --skip SaffronCity_Connection_Frlg $P

# the houses' doors, drawn in their packs (the gate's are open blocks at its top: no door to animate)
pae door add $M 16 10 --frames ../$V/house_family/house_family_door.png $P
pae door add $M 35 24 --frames ../$V/house_gardener/house_gardener_door.png $P

# events: every warp keeps its number (the buildings behind them point at it)
pae map place $M warp 0 35 24 $P   # the Underground Path's hut
pae map place $M warp 1 16 10 $P   # the Day Care
pae map place $M warp 2 24 30 $P   # Saffron's north gate: its two door blocks (the gatehouse's north door points at
pae map place $M warp 3 25 30 $P   #  2 and 3; 4 and 5, the old map's wider door, go on the same blocks)
pae map place $M warp 4 24 30 $P
pae map place $M warp 5 25 30 $P
pae map place $M object 0 38 17 $P   # Hoothoot (by night) and Pidgey (by day), on the lawn by the forest
pae map place $M object 2 40 18 $P
pae map place $M object 1 12 16 $P   # the Day Care's Pokémon in its paddock: two Meowth and Spinda
pae map place $M object 3 17 19 $P
pae map place $M object 4 15 18 $P
pae map place $M object 5 36 27 $P   # a Meowth by the Underground Path's hut
pae map place $M bg 0 37 25 $P       # the Underground Path's sign, by the hut's door
# Spinda plays on the ground (it stood on the old map's raised lawn)
python3 - <<'EOF'
import json
p = "data/maps/Route5_Frlg/map.json"
m = json.load(open(p))
m["object_events"][4]["elevation"] = 3
open(p, "w").write(json.dumps(m, indent=2) + "\n")
EOF
