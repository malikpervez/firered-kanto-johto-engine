#!/bin/sh
# Rebuild Route 7 from its concept with pae: lay out the plan, build the tileset (the kit's primary, the Underground
# Path's hut and Saffron's west gate), paint the map, keep its joins to Celadon and Saffron, make the seams and the
# doors, put the events where the new route has them. Run from the repository root (project/art/build_all.sh
# rebuilds every map).
set -e
A=project/art/route7-concept
V=project/art/viridian-concept/buildings
R2=project/art/route2-concept/buildings
python3 $A/make_art.py
python3 project/art/kit/settle.py $A  # the kit's small pieces into the ground they stand in
cd engine
P="-p ."
M=Route7_Frlg

# the tileset and the block files (the first time)
grep -q "gTileset_Route7Concept =" src/data/tilesets/headers.h || pae tileset new gTileset_Route7Concept --secondary $P
pae map geometry $M --primary gTileset_PalletConcept_General --secondary gTileset_Route7Concept \
    --blockdata data/layouts/Route7_Concept/map.bin --border data/layouts/Route7_Concept/border.bin \
    --width 30 --height 24 $P

pae tileset build ../$A/spec.json $P
pae map paint $M ../$A/grid.txt ../$A/legend.json --names ../$A/names.json --border ../$A/border.txt $P

# the joins: Celadon's boulevard (its rows 20-23) meets the left edge at rows 10-13; Saffron lies beyond the right
# edge, its own west gate door (its row 27) level with the gate's here (row 9), as with the old route
pae map connect $M left CeladonCity_Frlg --offset -10 $P
pae map connect $M right SaffronCity_Connection_Frlg --offset -18 $P
# no seam with Saffron's twin (as Routes 5, 6 and 8's, KR-34): no block of this route is in view of it, and old
# Saffron itself draws no neighbour (KR-53)
[ -n "$KIT_BUILD_ALL" ] || pae seam build $M --skip SaffronCity_Connection_Frlg $P

# doors, drawn in their packs (the gate's two open together: give its left one)
pae door add $M 18 9 --frames ../$R2/forest_gate_south/forest_gate_south_door.png $P
pae door add $M 9 9 --frames ../$V/house_pond_keeper/house_pond_keeper_door.png $P

# events: every warp keeps its number (the buildings behind them point at it); the gate's right door block is a
# second warp to the same gatehouse door, added the first time
python3 - <<'PY'
import json
p = "data/maps/Route7_Frlg/map.json"
m = json.load(open(p))
w = m["warp_events"]
if len(w) == 2:
    w.append(dict(w[1]))
open(p, "w").write(json.dumps(m, indent=2) + "\n")
PY
pae map place $M warp 0 9 9 $P     # the Underground Path's hut
pae map place $M warp 1 18 9 $P    # Saffron's west gate
pae map place $M warp 2 19 9 $P
pae map place $M object 1 9 17 $P  # the Jigglypuff, singing to the Ralts in the garden
pae map place $M object 2 12 17 $P
pae map place $M bg 0 12 9 $P       # the Underground Path's sign, by the hut
pae map place $M bg 1 22 21 $P     # the hidden Wepear Berry, in the garden's corner
# the Pokémon stand at the ground's elevation; Celadon's border tree is shown across the join where it stands on
# Celadon's grid (its 50,13: x 50 - 60, y 13 - 10)
python3 - <<'PY'
import json
p = "data/maps/Route7_Frlg/map.json"
m = json.load(open(p))
o = m["object_events"]
for i in (1, 2):
    o[i]["elevation"] = 3
clone = [e for e in o if e.get("type") == "clone" and e.get("target_map") == "MAP_CELADON_CITY"]
assert len(clone) == 1
clone[0]["x"], clone[0]["y"] = -10, 3
open(p, "w").write(json.dumps(m, indent=2) + "\n")
PY
