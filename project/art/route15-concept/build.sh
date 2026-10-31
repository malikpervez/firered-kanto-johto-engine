#!/bin/sh
# Rebuild Route 15 from its concept with pae: lay out the plan, build the tileset (the kit's primary and Route 16's
# Cycling Road gatehouse), paint the map, keep its joins to Fuchsia and Route 14, make the seams, put the events where
# the new route has them. Run from the repository root (project/art/build_all.sh rebuilds every map).
set -e
A=project/art/route15-concept
python3 $A/make_art.py
python3 project/art/kit/settle.py $A  # the kit's small pieces into the ground they stand in
cd engine
P="-p ."
M=Route15_Frlg

# the tileset and the block files (the first time)
grep -q "gTileset_Route15Concept =" src/data/tilesets/headers.h || pae tileset new gTileset_Route15Concept --secondary $P
pae map geometry $M --primary gTileset_PalletConcept_General --secondary gTileset_Route15Concept \
    --blockdata data/layouts/Route15_Concept/map.bin --border data/layouts/Route15_Concept/border.bin \
    --width 80 --height 24 $P

pae tileset build ../$A/spec.json $P
pae map paint $M ../$A/grid.txt ../$A/legend.json --names ../$A/names.json --border ../$A/border.txt $P

# the joins: Fuchsia's main street (its rows 20-23) at the left edge, rows 4-7; Route 14's road (its rows 50-53) at
# the right edge, rows 14-17
pae map connect $M left FuchsiaCity_Frlg --offset -16 $P
pae map connect $M right Route14_Frlg --offset -36 $P
[ -n "$KIT_BUILD_ALL" ] || pae seam build $M $P

# events: the gatehouse's doorways keep their warps (0 west, 1 east: arrow warps, no door to animate)
pae map place $M warp 0 9 5 $P
pae map place $M warp 1 16 5 $P
pae map place $M object 0 24 10 $P   # Yazmin, in the meadow's west grass
pae map place $M object 1 34 15 $P   # Edwin, on the low road, looking back west along it
pae map place $M object 2 42 16 $P   # Chester, on the low road, looking up into the meadow
pae map place $M object 3 41 10 $P   # Kindra, in the meadow's middle grass
pae map place $M object 4 30 4 $P    # Olivia, on the high road, looking down over the ledge
pae map place $M object 5 54 4 $P    # Alex, on the high road
pae map place $M object 6 60 15 $P   # Ernest, on the low road
pae map place $M object 7 40 2 $P    # Becky, among the high road's flowers
pae map place $M object 8 64 4 $P    # Grace, on the high road
pae map place $M object 9 55 2 $P    # Celia, among the flowers
pae map place $M object 10 76 5 $P   # the TM, at the lookout
pae map place $M object 11 47 10 $P  # Ron and Mya, who battle together, by the meadow's flowers
pae map place $M object 12 48 10 $P
pae map place $M object 14 58 13 $P  # Volbeat, by day
pae map place $M object 15 26 2 $P   # the Hoppip, drifting about
pae map place $M object 16 37 3 $P
pae map place $M object 17 50 2 $P
pae map place $M object 18 62 13 $P
pae map place $M object 19 28 18 $P
pae map place $M object 20 48 18 $P
pae map place $M object 21 65 19 $P  # Chansey, in the south meadow
pae map place $M object 22 17 3 $P   # Pidgeotto, by the gatehouse
pae map place $M object 23 44 13 $P  # Illumise, by night
pae map place $M bg 0 20 2 $P        # the route sign, by the gatehouse's east doorway
# Route 14's tree to cut is placed across the join where it stands on Route 14 (its 12,54: x 80 + 12, y 54 - 36);
# everyone stands at the ground's elevation
python3 - <<'PY'
import json
p = "data/maps/Route15_Frlg/map.json"
m = json.load(open(p))
o = m["object_events"]
clone = [e for e in o if e.get("type") == "clone"]
assert len(clone) == 1
clone[0]["x"], clone[0]["y"] = 92, 18
for e in o:
    if e.get("type") != "clone" and "elevation" in e:
        e["elevation"] = 3
open(p, "w").write(json.dumps(m, indent=2) + "\n")
PY
