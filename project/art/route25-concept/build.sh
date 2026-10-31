#!/bin/sh
# Rebuild Route 25 (Cerulean's cape) from its concept with pae: lay out the plan, build the tileset (the kit's
# primary, the cliffs and the cottage), paint the map, keep its join to Route 24, make the seams and the cottage's
# door, put the events where the new route has them. Run from the repository root (project/art/build_all.sh
# rebuilds every map).
set -e
A=project/art/route25-concept
V=project/art/viridian-concept/buildings
python3 $A/make_art.py
python3 project/art/kit/settle.py $A  # the kit's small pieces into the ground they stand in
cd engine
P="-p ."
M=Route25_Frlg

# the tileset and the block files (the first time)
grep -q "gTileset_Route25Concept =" src/data/tilesets/headers.h || pae tileset new gTileset_Route25Concept --secondary $P
pae map geometry $M --primary gTileset_PalletConcept_General --secondary gTileset_Route25Concept \
    --blockdata data/layouts/Route25_Concept/map.bin --border data/layouts/Route25_Concept/border.bin \
    --width 70 --height 24 $P

pae tileset build ../$A/spec.json $P
pae map paint $M ../$A/grid.txt ../$A/legend.json --names ../$A/names.json --border ../$A/border.txt $P

# the join stays where it was: Route 24 meets the bottom at the same columns (its west path 7-10, the bridge 16-19,
# its east path 24-25)
pae map connect $M down Route24_Frlg --offset 0 $P
[ -n "$KIT_BUILD_ALL" ] || pae seam build $M $P

# the cottage's door, drawn in its pack
pae door add $M 51 7 --frames ../$V/house_pond_keeper/house_pond_keeper_door.png $P

# events: the people keep their order and their scripts
pae map place $M warp 0 51 7 $P       # Bill's Sea Cottage
pae map place $M object 0 6 8 $P      # Franklin, on the landing's west lawn, looking along it
pae map place $M object 1 28 8 $P     # Joey, in the first neck's row of bushes, looking down across the road
pae map place $M object 2 47 8 $P     # Wayne, the same at the second neck ("You're going to see BILL?")
pae map place $M object 3 35 13 $P    # Dan, in the grass south of the road, looking round
pae map place $M object 4 39 12 $P    # Kelsey...
pae map place $M object 6 41 8 $P     # ...and Flint, the couple, either side of the road
pae map place $M object 5 44 12 $P    # Nob, below the road, on his way to the cape
pae map place $M object 7 40 16 $P    # Chad, walking to and fro along the trail below
pae map place $M object 8 55 8 $P     # Haley, on the headland
pae map place $M object 9 36 5 $P     # TM43, in the garden...
pae map place $M object 10 34 7 $P    # ...behind the tree to cut, in its gate
pae map place $M object 11 57 9 $P    # the couple at the lookout
pae map place $M object 12 57 10 $P
pae map place $M object 13 12 5 $P    # Swablu (by night), on the landing
pae map place $M object 14 56 6 $P    # Spearow, at the lookout
pae map place $M object 15 61 10 $P   # Luvdisc, in the sea
pae map place $M object 16 63 15 $P
pae map place $M object 17 47 16 $P   # Butterfree, over the trail below
pae map place $M bg 0 49 7 $P         # the cottage's sign, by its door
pae map place $M bg 1 5 13 $P         # the hidden Elixir, in the grass by the forest
pae map place $M bg 2 32 5 $P         # the hidden Ether, in the garden
pae map place $M bg 3 50 15 $P        # the hidden Oran Berry, on the trail below
pae map place $M bg 4 54 4 $P         # the hidden Bluk Berry, in the lookout's flowers
# Wayne looks down across his neck, Chad walks along the trail (he walked up and down); Spearow and Butterfree
# stand on the ground (they were on old Route 25's ledges)
python3 - <<'EOF'
import json
p = "data/maps/Route25_Frlg/map.json"
m = json.load(open(p))
m["object_events"][2]["movement_type"] = "MOVEMENT_TYPE_FACE_DOWN"
m["object_events"][7]["movement_type"] = "MOVEMENT_TYPE_WALK_LEFT_AND_RIGHT"
for i in (14, 17):
    m["object_events"][i]["elevation"] = 3
open(p, "w").write(json.dumps(m, indent=2) + "\n")
EOF
