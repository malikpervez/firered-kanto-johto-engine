#!/bin/sh
# Rebuild Route 19 from its concept with pae: lay out the plan, build the tileset (the kit's primary; nothing of the
# route's own), paint the map, keep its joins to Fuchsia and Route 20, make the seams, put the events where the new
# route has them. Run from the repository root (project/art/build_all.sh rebuilds every map).
set -e
A=project/art/route19-concept
python3 $A/make_art.py
python3 project/art/kit/settle.py $A  # the kit's small pieces into the ground they stand in
cd engine
P="-p ."
M=Route19_Frlg

# the tileset and the block files (the first time)
grep -q "gTileset_Route19Concept =" src/data/tilesets/headers.h || pae tileset new gTileset_Route19Concept --secondary $P
pae map geometry $M --primary gTileset_PalletConcept_General --secondary gTileset_Route19Concept \
    --blockdata data/layouts/Route19_Concept/map.bin --border data/layouts/Route19_Concept/border.bin \
    --version hns --width 24 --height 60 $P

pae tileset build ../$A/spec.json $P
pae map paint $M ../$A/grid.txt ../$A/legend.json --names ../$A/names.json --border ../$A/border.txt $P

# the joins stay where they were: Fuchsia's beach path (its columns 18-29) at the top edge, columns 6-17; Route 20's
# sea (its rows 0-18) at the left edge, rows 41-59
pae map connect $M up FuchsiaCity_Frlg --offset -12 $P
pae map connect $M left Route20_Frlg --offset 41 $P
[ -n "$KIT_BUILD_ALL" ] || pae seam build $M $P

# events: the swimmers and the Wingull keep their order
pae map place $M object 0 17 8 $P    # Reece, resting on the beach, looking along it
pae map place $M object 1 6 8 $P     # Richard, the same from the other end
pae map place $M object 2 12 18 $P   # Tony, off the end of the jetty
pae map place $M object 3 18 33 $P   # Matthew, swimming round the sandbar
pae map place $M object 4 8 29 $P    # Douglas
pae map place $M object 5 16 22 $P   # David, looking across the channel
pae map place $M object 6 11 47 $P   # Axle, Alice, Connie and Anya, swimming together
pae map place $M object 7 14 48 $P
pae map place $M object 8 12 49 $P
pae map place $M object 9 9 48 $P
pae map place $M object 10 8 41 $P   # Lia and Luc, who battle together
pae map place $M object 11 9 41 $P
pae map place $M object 12 8 54 $P   # the Wingull, on the rock island
pae map place $M bg 0 12 4 $P        # the route sign, on the beach
# the swimmers in the water at the water's elevation, everyone else at the ground's
python3 - <<'PY'
import json
p = "data/maps/Route19_Frlg/map.json"
m = json.load(open(p))
for e in m["object_events"]:
    if e.get("type") != "clone":
        e["elevation"] = 1 if "WATER" in e["graphics_id"] else 3
open(p, "w").write(json.dumps(m, indent=2) + "\n")
PY
