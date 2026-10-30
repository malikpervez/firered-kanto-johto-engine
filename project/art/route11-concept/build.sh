#!/bin/sh
# Rebuild Route 11 from its concept with pae: lay out the plan, build the tileset (the kit's primary, its cliffs,
# Route 2's cave mouth for Diglett's Cave and its south forest gate for the gatehouse), paint the map, keep its joins
# to Vermilion and Route 12, make the seams and the doors, put the events where the new route has them. Run from the
# repository root (project/art/build_all.sh rebuilds every map).
set -e
A=project/art/route11-concept
R2=project/art/route2-concept/buildings
python3 $A/make_art.py
python3 project/art/kit/settle.py $A  # the kit's small pieces into the ground they stand in
cd engine
P="-p ."
M=Route11_Frlg

# the tileset and the block files (the first time)
grep -q "gTileset_Route11Concept =" src/data/tilesets/headers.h || pae tileset new gTileset_Route11Concept --secondary $P
pae map geometry $M --primary gTileset_PalletConcept_General --secondary gTileset_Route11Concept \
    --blockdata data/layouts/Route11_Concept/map.bin --border data/layouts/Route11_Concept/border.bin \
    --width 60 --height 32 $P

pae tileset build ../$A/spec.json $P
pae map paint $M ../$A/grid.txt ../$A/legend.json --names ../$A/names.json --border ../$A/border.txt $P

# the joins stay where they were: Vermilion's main street (its rows 11-14) meets the left edge at rows 14-17,
# Route 12's road (its rows 44-46) the right edge at rows 17-19
pae map connect $M left VermilionCity_Frlg --offset 3 $P
pae map connect $M right Route12_Frlg --offset -27 $P
[ -n "$KIT_BUILD_ALL" ] || pae seam build $M $P

# doors, drawn in their packs (the gatehouse's two open together: give its left one; the cave's mouth is open)
pae door add $M 53 15 --frames ../$R2/forest_gate_south/forest_gate_south_door.png $P

# events: every warp keeps its number (the cave and the gatehouse point at it)
pae map place $M warp 0 16 6 $P    # Diglett's Cave, in the ridge
pae map place $M warp 1 53 15 $P   # the gatehouse to Route 12
pae map place $M warp 2 54 15 $P
# the trainers, where the plan is made for them (make_art.py: none of them sees the road)
pae map place $M object 0 34 6 $P    # Eddie, at the north grass's west edge
pae map place $M object 1 24 22 $P   # Hugo, Dave, Jasper and Bernie in the south grass
pae map place $M object 2 40 10 $P   # Dillon, in the north grass
pae map place $M object 3 14 22 $P
pae map place $M object 4 28 24 $P
pae map place $M object 5 44 6 $P    # Darian, in the north grass
pae map place $M object 6 47 12 $P   # Braxton, by the north grass's east corner
pae map place $M object 7 36 24 $P   # Yasu, walking among the south flowers
pae map place $M object 8 40 22 $P   # Dirk, by the pond's west shore
pae map place $M object 9 20 25 $P
pae map place $M object 10 34 22 $P  # the X Defend, by the south flowers
pae map place $M object 11 55 24 $P  # the Great Ball, past the pond
pae map place $M object 12 5 6 $P    # the Awakening, under the ridge west of the cave
pae map place $M object 13 5 26 $P   # Drowzee, in the south grass's west corner (at night)
pae map place $M object 14 33 3 $P   # the Hypnos swinging their pendulums at two Meowth, above the north grass (at night)
pae map place $M object 15 35 3 $P
pae map place $M object 16 36 3 $P
pae map place $M object 17 38 3 $P
pae map place $M object 18 50 5 $P   # the Magnemite, in the north-east corner
pae map place $M object 19 54 5 $P
pae map place $M object 20 10 10 $P  # Hoppip, by the west flowers (by day)
pae map place $M object 21 29 12 $P  # Slakoth, by the rock (at night)
pae map place $M bg 0 13 6 $P        # Diglett's Cave's sign, by its mouth
pae map place $M bg 1 55 9 $P        # the hidden Escape Rope, behind the gatehouse
# (the Friends, objects 22-28, camp round 25,7 as before: src/data/friends_scene_locations.h)
# the walkers stay near their places and the Pokémon stand at the ground's elevation (Hoppip and Slakoth were on old
# ledges)
python3 - <<'EOF'
import json
p = "data/maps/Route11_Frlg/map.json"
m = json.load(open(p))
o = m["object_events"]
o[3]["movement_range_x"], o[3]["movement_range_y"] = 1, 1   # Dave walks his square in the grass
o[7]["movement_range_y"] = 2                                # Yasu, up and down by his flowers
for i in (18, 19):                                          # the Magnemite keep to their corner
    o[i]["movement_range_x"], o[i]["movement_range_y"] = 2, 2
for i in (20, 21):
    o[i]["elevation"] = 3
open(p, "w").write(json.dumps(m, indent=2) + "\n")
EOF
