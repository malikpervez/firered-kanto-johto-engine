#!/bin/sh
# Rebuild Route 16 from its concept with pae: draw the gatehouse, lay out the plan, build the tileset (the kit's
# primary, the gatehouse and Viridian's pond keeper's house), paint the map, keep its joins to Celadon and Cycling
# Road, make the seams and the door, put the events where the new route has them. Run from the repository root
# (project/art/build_all.sh rebuilds every map).
set -e
A=project/art/route16-concept
V=project/art/viridian-concept/buildings
python3 $A/make_art.py
cd engine
P="-p ."
M=Route16_Frlg

# the tileset and the block files (the first time)
grep -q "gTileset_Route16Concept =" src/data/tilesets/headers.h || pae tileset new gTileset_Route16Concept --secondary $P
pae map geometry $M --primary gTileset_PalletConcept_General --secondary gTileset_Route16Concept \
    --blockdata data/layouts/Route16_Concept/map.bin --border data/layouts/Route16_Concept/border.bin \
    --width 56 --height 44 $P

pae tileset build ../$A/spec.json $P
pae map paint $M ../$A/grid.txt ../$A/legend.json --names ../$A/names.json --border ../$A/border.txt $P

# the joins: Celadon's boulevard (its rows 20-23) at the right edge, rows 22-25; Cycling Road's road (its columns
# 12-17) below the bottom edge, at the same columns
pae map connect $M right CeladonCity_Frlg --offset 2 $P
pae map connect $M down Route17_Frlg --offset 0 $P
[ -n "$KIT_BUILD_ALL" ] || pae seam build $M $P

# the house's door, drawn in its pack (the gatehouse's doorways are arrow warps: they don't animate)
pae door add $M 17 11 --frames ../$V/house_pond_keeper/house_pond_keeper_door.png $P

# events: every warp keeps its number (the house and the gatehouse's halls point at them)
pae map place $M warp 0 17 11 $P    # the house in the woods
pae map place $M warp 1 28 12 $P    # the upper hall: its west doorway (entered walking east)...
pae map place $M warp 2 35 12 $P    # ...and its east one (walking west)
pae map place $M warp 3 28 24 $P    # the lower hall, the same
pae map place $M warp 4 35 24 $P
pae map place $M object 0 11 29 $P   # the bikers, hanging out by the top of Cycling Road
pae map place $M object 1 18 29 $P
pae map place $M object 2 11 32 $P
pae map place $M object 3 18 32 $P
pae map place $M object 4 9 30 $P
pae map place $M object 5 20 31 $P
pae map place $M object 6 46 21 $P   # the tree to cut, in the hedge north of the road
pae map place $M object 7 40 11 $P   # Lea and Jed, out walking on the woodland path
pae map place $M object 8 41 11 $P
pae map place $M object 9 44 24 $P   # Snorlax, asleep in the gap between the outcrops
pae map place $M object 10 50 29 $P  # Grimer, in the meadow
pae map place $M object 11 44 5 $P   # Murkrow, in the woods' grass
pae map place $M object 12 39 17 $P  # Shuppet, at night, by the woodland path
pae map place $M object 13 23 5 $P   # Roselia, by day, in the glade's flowers
pae map place $M bg 0 19 28 $P       # the route sign, at the top of Cycling Road
pae map place $M bg 1 38 21 $P       # the Cycling Road sign, by the road west of Snorlax
pae map place $M bg 2 44 24 $P       # the Leftovers, hidden where Snorlax lay
# everyone stands at the ground's elevation; Celadon shows the tree across the join where it stands on this route's
# grid (46,21: x 46 - 56, y 21 - 2)
python3 - <<'EOF'
import json
p = "data/maps/Route16_Frlg/map.json"
m = json.load(open(p))
for e in m["object_events"]:
    if e.get("type") != "clone" and "elevation" in e:
        e["elevation"] = 3
open(p, "w").write(json.dumps(m, indent=2) + "\n")
p = "data/maps/CeladonCity_Frlg/map.json"
m = json.load(open(p))
clone = [e for e in m["object_events"] if e.get("type") == "clone" and e.get("target_map") == "MAP_ROUTE16"]
assert len(clone) == 1
clone[0]["x"], clone[0]["y"] = -10, 19
open(p, "w").write(json.dumps(m, indent=2) + "\n")
EOF
