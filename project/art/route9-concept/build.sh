#!/bin/sh
# Rebuild Route 9 from its concept with pae: lay out the plan, build the tileset (the kit's primary and the route's
# own cliffs), paint the map, join it to Cerulean and Route 10, make the seams, put the events where the new route has
# them. Run from the repository root (project/art/build_all.sh rebuilds every map).
set -e
A=project/art/route9-concept
python3 $A/make_art.py
python3 project/art/kit/settle.py $A  # the kit's small pieces into the ground they stand in
cd engine
P="-p ."
M=Route9_Frlg

# the tileset and the block files (the first time)
grep -q "gTileset_Route9Concept =" src/data/tilesets/headers.h || pae tileset new gTileset_Route9Concept --secondary $P
pae map geometry $M --primary gTileset_PalletConcept_General --secondary gTileset_Route9Concept \
    --blockdata data/layouts/Route9_Concept/map.bin --border data/layouts/Route9_Concept/border.bin \
    --width 60 --height 28 $P

pae tileset build ../$A/spec.json $P
pae map paint $M ../$A/grid.txt ../$A/legend.json --names ../$A/names.json --border ../$A/border.txt $P

# the joins: Cerulean's road east (its rows 28-30, where its edge opens) meets the left edge at rows 8-10; the road out
# (rows 17-19) meets old Route 10's lawn by its west edge, its rows 17-19
pae map connect $M left CeruleanCity_Frlg --offset -20 $P
pae map connect $M right Route10_Frlg --offset 0 $P
[ -n "$KIT_BUILD_ALL" ] || pae seam build $M $P

# events: the trainers keep their scripts (and their battles)
pae map place $M object 0 13 6 $P    # Alicia and Chris, under the gorge's northern cliff: they look across the road
pae map place $M object 3 19 6 $P
pae map place $M object 1 19 15 $P   # Jeremy and Brent, in the west field
pae map place $M object 4 13 17 $P
pae map place $M object 5 28 20 $P   # Conner and Drew, in the middle field's grass
pae map place $M object 8 30 23 $P
pae map place $M object 7 43 9 $P    # Caitlin and Alan, on the terrace
pae map place $M object 2 50 10 $P
pae map place $M object 6 48 22 $P   # Brice, wandering the lawn south of the road out
pae map place $M object 9 9 9 $P     # the tree to cut, in the neck
pae map place $M object 10 55 7 $P   # TM40, at the terrace's far end
pae map place $M object 11 10 24 $P   # the Burn Heal, in the west field's corner
pae map place $M object 12 30 13 $P  # the Marowak by the outcrop's foot (by day)
pae map place $M object 13 33 13 $P
pae map place $M object 14 15 21 $P  # Venonat and Venomoth in the fields' grass (at night)
pae map place $M object 15 36 21 $P
pae map place $M object 16 52 11 $P  # the Aron, on the terrace
pae map place $M bg 0 11 6 $P         # the route sign, by the way in
pae map place $M bg 1 19 24 $P       # the hidden Ether, in the west field
pae map place $M bg 2 55 24 $P       # the hidden Rare Candy, in the south-east corner
pae map place $M bg 3 39 13 $P       # the hidden Chesto Berry, at the outcrop's foot
# the gorge's two look down across the road (Chris looked about); the Pokémon stand at the ground's elevation (they
# were on old ledges)
python3 - <<'EOF'
import json
p = "data/maps/Route9_Frlg/map.json"
m = json.load(open(p))
o = m["object_events"]
for i in (0, 3):
    o[i]["movement_type"] = "MOVEMENT_TYPE_FACE_DOWN"
    o[i]["trainer_sight_or_berry_tree_id"] = "3"
for i in range(12, 17):
    o[i]["elevation"] = 3
open(p, "w").write(json.dumps(m, indent=2) + "\n")
# Cerulean shows the tree across the join (its clone of it): the tree's block on Cerulean's grid (58 + 9, 20 + 9)
p = "data/maps/CeruleanCity_Frlg/map.json"
m = json.load(open(p))
clone = [o for o in m["object_events"] if o.get("type") == "clone" and o.get("target_map") == "MAP_ROUTE9"]
assert len(clone) == 1
clone[0]["x"], clone[0]["y"] = 67, 29
open(p, "w").write(json.dumps(m, indent=2) + "\n")
EOF
