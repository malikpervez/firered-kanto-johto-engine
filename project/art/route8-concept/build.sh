#!/bin/sh
# Rebuild Route 8 from its concept with pae: lay out the plan, build the tileset (the kit's primary, the Underground
# Path's hut and Saffron's east gate), paint the map, keep its joins to Saffron and Lavender, make the seams and the
# doors, put the events where the new route has them. Run from the repository root (project/art/build_all.sh
# rebuilds every map).
set -e
A=project/art/route8-concept
V=project/art/viridian-concept/buildings
R2=project/art/route2-concept/buildings
python3 $A/make_art.py
python3 project/art/kit/settle.py $A  # the kit's small pieces into the ground they stand in
cd engine
P="-p ."
M=Route8_Frlg

# the tileset and the block files (the first time)
grep -q "gTileset_Route8Concept =" src/data/tilesets/headers.h || pae tileset new gTileset_Route8Concept --secondary $P
pae map geometry $M --primary gTileset_PalletConcept_General --secondary gTileset_Route8Concept \
    --blockdata data/layouts/Route8_Concept/map.bin --border data/layouts/Route8_Concept/border.bin \
    --width 60 --height 30 $P

pae tileset build ../$A/spec.json $P
pae map paint $M ../$A/grid.txt ../$A/legend.json --names ../$A/names.json --border ../$A/border.txt $P

# the joins: Lavender's street (its rows 9-11) meets the right edge at rows 13-15; Saffron lies beyond the left edge,
# its own gate door (its row 27) level with the gate's here (row 12), as with the old route
pae map connect $M right LavenderTown_Frlg --offset 4 $P
pae map connect $M left SaffronCity_Connection_Frlg --offset -15 $P
# no seam with Saffron's twin (as Route 5's, KR-34): no block of this route is in view of it, and old Saffron itself
# draws no neighbour (its joins aren't compiled: connections_no_include), only its own border trees
[ -n "$KIT_BUILD_ALL" ] || pae seam build $M --skip SaffronCity_Connection_Frlg $P

# doors, drawn in their packs (the gate's two open together: give its left one)
pae door add $M 10 12 --frames ../$R2/forest_gate_south/forest_gate_south_door.png $P
pae door add $M 18 12 --frames ../$V/house_pond_keeper/house_pond_keeper_door.png $P

# events: every warp keeps its number (the buildings behind them point at it); the gate's right door block is a
# second warp to the same gatehouse door, added the first time
python3 - <<'EOF'
import json
p = "data/maps/Route8_Frlg/map.json"
m = json.load(open(p))
w = m["warp_events"]
if len(w) == 2:
    w.append(dict(w[1]))
open(p, "w").write(json.dumps(m, indent=2) + "\n")
EOF
pae map place $M warp 0 18 12 $P   # the Underground Path's hut
pae map place $M warp 1 10 12 $P   # Saffron's east gate
pae map place $M warp 2 11 12 $P
pae map place $M object 0 55 19 $P   # Julia, looking west across the picnic lawn's east end
pae map place $M object 1 23 6 $P    # Rich and Stan, the gamblers, watching the race over the stands' rail
pae map place $M object 7 23 8 $P
pae map place $M object 2 44 20 $P   # Glenn, looking about the lawn
pae map place $M object 3 29 19 $P   # Paige, Leslie, Andrea and Megan in their row by the picnic cloth
pae map place $M object 4 29 20 $P
pae map place $M object 5 29 21 $P
pae map place $M object 6 29 22 $P
pae map place $M object 8 8 21 $P    # Aidan, at the grass field's edge
pae map place $M object 9 36 9 $P    # the trees to cut: the berry garden's gap...
pae map place $M object 10 46 23 $P  # ...and the meadow's
pae map place $M object 11 51 9 $P   # the twins Eli and Anne, in the pine grove
pae map place $M object 12 52 9 $P
pae map place $M object 13 28 3 $P   # Ricardo and Jaren, riding round the track at its opposite corners
pae map place $M object 14 43 11 $P
pae map place $M object 15 40 26 $P  # Kadabra, in the meadow
pae map place $M object 16 32 7 $P   # Growlithe and Vulpix, playing in the berry garden
pae map place $M object 17 33 7 $P
pae map place $M object 18 56 10 $P  # Duskull, in the pine grove (at night)
pae map place $M bg 0 21 12 $P       # the Underground Path's sign, by the hut
pae map place $M bg 1 33 6 $P        # the hidden Rawst, Lum and Leppa Berries, in the berry garden
pae map place $M bg 2 38 8 $P
pae map place $M bg 3 39 6 $P
# Rich looks at the track; the bikers ride round its loop clockwise from opposite corners (their range 15x8, the most
# a range can be across); the Pokémon stand at the ground's elevation (some were on old ledges)
python3 - <<'EOF'
import json
p = "data/maps/Route8_Frlg/map.json"
m = json.load(open(p))
o = m["object_events"]
o[1]["movement_type"] = "MOVEMENT_TYPE_FACE_RIGHT"
for i, mv in ((13, "RIGHT_DOWN_LEFT_UP"), (14, "LEFT_UP_RIGHT_DOWN")):
    o[i]["movement_type"] = f"MOVEMENT_TYPE_WALK_SEQUENCE_{mv}"
    o[i]["movement_range_x"], o[i]["movement_range_y"] = 15, 8
for i in range(15, 19):
    o[i]["elevation"] = 3
open(p, "w").write(json.dumps(m, indent=2) + "\n")
EOF
