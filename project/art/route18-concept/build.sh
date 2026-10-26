#!/bin/sh
# Rebuild Route 18 from its concept with pae: lay out the plan, build the tileset (the kit's primary and Route 16's
# Cycling Road gatehouse), paint the map, keep its joins to Route 17 and Fuchsia, make the seams, put the events where
# the new route has them. Run from the repository root (project/art/build_all.sh rebuilds every map).
set -e
A=project/art/route18-concept
python3 $A/make_art.py
cd engine
P="-p ."
M=Route18_Frlg

# the tileset and the block files (the first time)
grep -q "gTileset_Route18Concept =" src/data/tilesets/headers.h || pae tileset new gTileset_Route18Concept --secondary $P
pae map geometry $M --primary gTileset_PalletConcept_General --secondary gTileset_Route18Concept \
    --blockdata data/layouts/Route18_Concept/map.bin --border data/layouts/Route18_Concept/border.bin \
    --width 60 --height 20 $P

pae tileset build ../$A/spec.json $P
pae map paint $M ../$A/grid.txt ../$A/legend.json --names ../$A/names.json --border ../$A/border.txt $P

# the joins: Route 17's road (its columns 14-22) at the top edge, columns 8-16; Fuchsia's west road (its rows 18-20)
# at the right edge, rows 8-10
pae map connect $M up Route17_Frlg --offset -6 $P
pae map connect $M right FuchsiaCity_Frlg --offset -10 $P
[ -n "$KIT_BUILD_ALL" ] || pae seam build $M $P

# events: the gatehouse's doorways keep their warps (0 west, 1 east: they're arrow warps, with no door to animate)
pae map place $M warp 0 41 9 $P
pae map place $M warp 1 48 9 $P
pae map place $M object 0 38 13 $P   # Jacob, in the rockers' grass, looking west along it
pae map place $M object 1 31 14 $P   # Ramiro, looking about in the middle of it
pae map place $M object 2 23 12 $P   # Wilton, at its west end, looking east along it
pae map place $M object 3 31 6 $P    # a Kecleon at the woods' edge
pae map place $M object 4 33 7 $P    # the Dodrio, running up and down the meadow
pae map place $M object 5 36 7 $P
pae map place $M object 6 39 6 $P    # the other Kecleon
pae map place $M bg 0 38 7 $P        # the Cycling Road sign, by the gatehouse's west doorway
pae map place $M bg 1 52 7 $P        # the route sign, beyond it
# the Dodrio run their stretch of meadow; everyone stands at the ground's elevation
python3 - <<'PY'
import json
p = "data/maps/Route18_Frlg/map.json"
m = json.load(open(p))
o = m["object_events"]
for i in (4, 5):
    o[i]["movement_range_x"], o[i]["movement_range_y"] = 2, 0
for e in o:
    if e.get("type") != "clone" and "elevation" in e:
        e["elevation"] = 3
open(p, "w").write(json.dumps(m, indent=2) + "\n")
PY
