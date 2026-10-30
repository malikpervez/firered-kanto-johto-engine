#!/bin/sh
# Rebuild Route 13 from its concept with pae: lay out the plan, build the tileset (the kit's primary; nothing of the
# route's own), paint the map, keep its joins to Route 12 and Route 14, make the seams, put the events where the new
# route has them. Run from the repository root (project/art/build_all.sh rebuilds every map).
set -e
A=project/art/route13-concept
python3 $A/make_art.py
python3 project/art/kit/settle.py $A  # the kit's small pieces into the ground they stand in
cd engine
P="-p ."
M=Route13_Frlg

# the tileset and the block files (the first time)
grep -q "gTileset_Route13Concept =" src/data/tilesets/headers.h || pae tileset new gTileset_Route13Concept --secondary $P
pae map geometry $M --primary gTileset_PalletConcept_General --secondary gTileset_Route13Concept \
    --blockdata data/layouts/Route13_Concept/map.bin --border data/layouts/Route13_Concept/border.bin \
    --width 104 --height 32 $P

pae tileset build ../$A/spec.json $P
pae map paint $M ../$A/grid.txt ../$A/legend.json --names ../$A/names.json --border ../$A/border.txt $P

# the joins stay where they were: Route 12's boardwalk (its columns 21-23) at the top edge, columns 86-89; Route 14's
# way in (its columns 16-19) at the bottom edge, columns 20-23
pae map connect $M up Route12_Frlg --offset 65 $P
pae map connect $M down Route14_Frlg --offset 4 $P
[ -n "$KIT_BUILD_ALL" ] || pae seam build $M $P

# events: the trainers, the tree to cut and the Pokémon keep their order
pae map place $M object 0 66 23 $P   # Alma, wandering on the cove's shore
pae map place $M object 1 78 22 $P   # Sebastian, wandering on the shore by the landing
pae map place $M object 2 72 24 $P   # Susie, wandering on the cove's shore
pae map place $M object 3 61 15 $P   # Sheila and Lola, sitting on the headland, looking down on the road
pae map place $M object 4 62 15 $P
pae map place $M object 5 45 17 $P   # Valerie, by the road at the way up to the meadow
pae map place $M object 6 84 19 $P   # Gwen, at the road's east end, looking west along it
pae map place $M object 7 16 25 $P   # Robert, at the west fields' foot, looking up them
pae map place $M object 8 12 19 $P   # Perry, by the lovers' meadow, looking east
pae map place $M object 9 30 19 $P   # Jared, on the road, looking about
pae map place $M object 10 44 7 $P   # the tree to cut, the nook's way in
pae map place $M object 11 6 19 $P   # Nidorino and Nidorina, face to face in the ring of flowers
pae map place $M object 12 7 19 $P
pae map place $M object 13 46 3 $P   # the Seedot, in the nook
pae map place $M bg 0 84 15 $P       # the route sign, at the landing
pae map place $M bg 1 24 17 $P       # the trainer tips (SELECT), by the road's west end
pae map place $M bg 2 42 21 $P       # the trainer tips (look to the left of that post), by the lamp post
pae map place $M bg 3 39 23 $P       # the PP Up, hidden just left of the lamp post
# everyone stands at the ground's elevation
python3 - <<'PY'
import json
p = "data/maps/Route13_Frlg/map.json"
m = json.load(open(p))
for e in m["object_events"]:
    if e.get("type") != "clone" and "elevation" in e:
        e["elevation"] = 3
open(p, "w").write(json.dumps(m, indent=2) + "\n")
PY
