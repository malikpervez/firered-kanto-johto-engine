#!/bin/sh
# Rebuild Route 20 from its concept with pae: lay out the plan, build the tileset (the kit's primary, its cliffs and
# Route 2's cave mouth), paint the map, keep its joins to Cinnabar and Route 19, make the seams, put the events where
# the new route has them. Run from the repository root (project/art/build_all.sh rebuilds every map).
set -e
A=project/art/route20-concept
python3 $A/make_art.py
python3 project/art/kit/settle.py $A  # the kit's small pieces into the ground they stand in
cd engine
P="-p ."
M=Route20_Frlg

# the tileset and the block files (the first time)
grep -q "gTileset_Route20Concept =" src/data/tilesets/headers.h || pae tileset new gTileset_Route20Concept --secondary $P
pae map geometry $M --primary gTileset_PalletConcept_General --secondary gTileset_Route20Concept \
    --blockdata data/layouts/Route20_Concept/map.bin --border data/layouts/Route20_Concept/border.bin \
    --version hns --width 120 --height 20 $P

pae tileset build ../$A/spec.json $P
pae map paint $M ../$A/grid.txt ../$A/legend.json --names ../$A/names.json --border ../$A/border.txt $P

# the joins stay where they were: Cinnabar's sea at the left edge; Route 19's sea (its rows 41-59) at the right edge,
# rows 0-18
pae map connect $M left CinnabarIsland_Frlg --offset 0 $P
pae map connect $M right Route19_Frlg --offset -41 $P
[ -n "$KIT_BUILD_ALL" ] || pae seam build $M $P

# events: the warps keep their numbers (Seafoam's west mouth 0, its east mouth 1); the people and the Pokémon keep
# their order
pae map place $M warp 0 58 10 $P
pae map place $M warp 1 78 12 $P
pae map place $M object 0 8 11 $P    # Melissa, swimming by the first sandbar
pae map place $M object 1 12 5 $P    # Missy, on the first sandbar
pae map place $M object 2 34 7 $P    # Nora
pae map place $M object 3 43 9 $P    # Roger, on the third sandbar
pae map place $M object 4 23 10 $P   # Dean, swimming round the second sandbar
pae map place $M object 5 84 15 $P   # Irene, on the east island's shore, looking west along it
pae map place $M object 6 111 9 $P   # Barry and Darrin, swimming near Route 19's sea
pae map place $M object 7 106 11 $P
pae map place $M object 8 93 10 $P   # Shirley, looking about by the last sandbar
pae map place $M object 9 48 12 $P   # Tiffany, off the west island
pae map place $M object 10 64 14 $P  # the camper, on the west island's shore
pae map place $M object 11 51 14 $P  # the Seel and Dewgong, hauled out on the shores and swimming
pae map place $M object 12 48 17 $P
pae map place $M object 13 71 16 $P
pae map place $M object 14 69 9 $P
pae map place $M object 15 88 3 $P
pae map place $M object 16 42 9 $P
pae map place $M object 17 44 10 $P
pae map place $M object 18 34 5 $P
pae map place $M object 19 12 14 $P
pae map place $M object 20 116 5 $P
pae map place $M object 21 107 16 $P # the Clamperl
pae map place $M bg 0 55 11 $P       # the Seafoam Islands' sign by the west mouth
pae map place $M bg 1 75 13 $P       # and by the east mouth
pae map place $M bg 2 23 6 $P        # the Stardust, hidden on the second sandbar
# everyone at the elevation of what they stand on: the water's or the ground's
python3 - <<'PY'
import json
p = "data/maps/Route20_Frlg/map.json"
grid = open("../project/art/route20-concept/grid.txt").read().split()
m = json.load(open(p))
for e in m["object_events"]:
    if e.get("type") != "clone":
        e["elevation"] = 1 if grid[e["y"]][e["x"]] == "s" else 3
open(p, "w").write(json.dumps(m, indent=2) + "\n")
PY
