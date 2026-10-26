#!/bin/sh
# Rebuild Route 6 from its concept with pae: lay out the plan, build the tileset (the kit's primary, the Underground
# Path's hut and Saffron's south gate), paint the map, keep its joins to Saffron and Vermilion, make the seams and the
# doors, put the events where the new route has them. Run from the repository root (project/art/build_all.sh
# rebuilds every map).
set -e
A=project/art/route6-concept
V=project/art/viridian-concept/buildings
R2=project/art/route2-concept/buildings
python3 $A/make_art.py
cd engine
P="-p ."
M=Route6_Frlg

# the tileset and the block files (the first time)
grep -q "gTileset_Route6Concept =" src/data/tilesets/headers.h || pae tileset new gTileset_Route6Concept --secondary $P
pae map geometry $M --primary gTileset_PalletConcept_General --secondary gTileset_Route6Concept \
    --blockdata data/layouts/Route6_Concept/map.bin --border data/layouts/Route6_Concept/border.bin \
    --width 56 --height 32 $P

pae tileset build ../$A/spec.json $P
pae map paint $M ../$A/grid.txt ../$A/legend.json --names ../$A/names.json --border ../$A/border.txt $P

# the joins stay where they were: Saffron above (its gate door, its 28-29, over the gate's here, 40-41), Vermilion's
# stairs (its 32-34) the bottom at columns 40-42
pae map connect $M up SaffronCity_Connection_Frlg --offset 12 $P
pae map connect $M down VermilionCity_Frlg --offset 8 $P
[ -n "$KIT_BUILD_ALL" ] || pae seam build $M --skip SaffronCity_Connection_Frlg $P  # (as Route 5's: KR-34)

# doors, drawn in their packs (the gate's two open together: give its left one)
pae door add $M 40 5 --frames ../$R2/forest_gate_south/forest_gate_south_door.png $P
pae door add $M 46 11 --frames ../$V/house_pond_keeper/house_pond_keeper_door.png $P

# events: every warp keeps its number (the buildings behind them point at it)
pae map place $M warp 0 46 11 $P   # the Underground Path's hut
pae map place $M warp 1 40 5 $P    # Saffron's south gate
pae map place $M warp 2 41 5 $P
pae map place $M object 0 25 11 $P   # Keigo, on the lawn north of the pond (no bugs on it)
pae map place $M object 1 36 18 $P   # Ricky and Nancy, talking on the pond's east shore
pae map place $M object 2 37 18 $P
pae map place $M object 3 48 20 $P   # Elijah, Isabelle and Jeff on the east lawn, looking across it
pae map place $M object 4 48 23 $P
pae map place $M object 5 48 26 $P
pae map place $M object 6 38 8 $P    # the Magnemite under the gate's lamps
pae map place $M object 7 43 8 $P
pae map place $M object 8 17 22 $P   # Granbull and Snubbull, by the south meadow
pae map place $M object 9 18 22 $P
pae map place $M object 10 24 7 $P   # Plusle and Minun, playing in the north meadow
pae map place $M object 11 26 8 $P
pae map place $M bg 0 44 11 $P       # the Underground Path's sign, by the hut's door
pae map place $M bg 1 30 6 $P        # the hidden Sitrus Berry, in the north meadow
pae map place $M bg 2 50 10 $P       # the hidden Rare Candy, in the east corner
# the trainers see what the plan is made for; the Pokémon stand at the ground's elevation (some were on old ledges)
python3 - <<'EOF'
import json
p = "data/maps/Route6_Frlg/map.json"
m = json.load(open(p))
for i, (mv, sight) in enumerate([("RIGHT", 5), ("RIGHT", 0), ("LEFT", 0), ("LEFT", 3), ("LEFT", 3), ("LEFT", 3)]):
    m["object_events"][i]["movement_type"] = f"MOVEMENT_TYPE_FACE_{mv}"
    m["object_events"][i]["trainer_sight_or_berry_tree_id"] = str(sight)
for i in range(6, 12):
    m["object_events"][i]["elevation"] = 3
open(p, "w").write(json.dumps(m, indent=2) + "\n")
EOF
