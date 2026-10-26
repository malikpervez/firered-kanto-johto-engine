#!/bin/sh
# Rebuild Route 14 from its concept with pae: lay out the plan, build the tileset (the kit's primary; nothing of the
# route's own), paint the map, keep its joins to Route 13 and Route 15, make the seams, put the events where the new
# route has them. Run from the repository root (project/art/build_all.sh rebuilds every map).
set -e
A=project/art/route14-concept
python3 $A/make_art.py
cd engine
P="-p ."
M=Route14_Frlg

# the tileset and the block files (the first time)
grep -q "gTileset_Route14Concept =" src/data/tilesets/headers.h || pae tileset new gTileset_Route14Concept --secondary $P
pae map geometry $M --primary gTileset_PalletConcept_General --secondary gTileset_Route14Concept \
    --blockdata data/layouts/Route14_Concept/map.bin --border data/layouts/Route14_Concept/border.bin \
    --width 26 --height 62 $P

pae tileset build ../$A/spec.json $P
pae map paint $M ../$A/grid.txt ../$A/legend.json --names ../$A/names.json --border ../$A/border.txt $P

# the joins: Route 13's path (its columns 20-22) at the top edge, columns 16-19; Route 15's low road (its rows 14-17)
# at the left edge, rows 50-53
pae map connect $M up Route13_Frlg --offset -4 $P
pae map connect $M left Route15_Frlg --offset 36 $P
[ -n "$KIT_BUILD_ALL" ] || pae seam build $M $P

# events: the trainers, the trees to cut, the twins and the Shroomish keep their order
pae map place $M object 0 4 28 $P    # Gerald, on the bikers' road, looking across the meadow
pae map place $M object 1 15 31 $P   # Donald, wandering below the pond
pae map place $M object 2 2 17 $P    # Beck, at the third lane's west end, looking along it
pae map place $M object 3 19 23 $P   # Marlon, below the maze, looking up the last lane's east end
pae map place $M object 4 4 38 $P    # Isaac, on the bikers' road
pae map place $M object 5 14 52 $P   # Malik, at the crossroads, looking east to the pier
pae map place $M object 6 16 15 $P   # Mitch, pacing the second lane's east end
pae map place $M object 7 2 12 $P    # Carter, at the first lane's west end
pae map place $M object 8 5 44 $P    # Lukas, riding up and down the bikers' road
pae map place $M object 9 13 45 $P   # Benny, wandering in the lower meadow
pae map place $M object 10 19 16 $P  # the tree to cut in the maze's third fence: the short cut
pae map place $M object 11 15 42 $P  # the tree to cut in the dell's hedge
pae map place $M object 12 12 54 $P  # the tree to cut at the berry garden's gap
pae map place $M object 13 12 49 $P  # Jan and Kiri, who battle together, above the crossroads
pae map place $M object 14 13 49 $P
pae map place $M object 15 18 42 $P  # the Shroomish, in the dell
pae map place $M bg 0 15 8 $P        # the route sign, at the foot of the way in from Route 13
pae map place $M bg 1 21 9 $P        # the Zinc, hidden by the shore at the maze's start
pae map place $M bg 2 15 56 $P       # the Pinap Berry, hidden in the berry garden
# everyone stands at the ground's elevation
python3 - <<'PY'
import json
p = "data/maps/Route14_Frlg/map.json"
m = json.load(open(p))
for e in m["object_events"]:
    if e.get("type") != "clone" and "elevation" in e:
        e["elevation"] = 3
open(p, "w").write(json.dumps(m, indent=2) + "\n")
PY
