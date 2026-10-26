#!/bin/sh
# Rebuild Route 10 from its concept with pae: lay out the plan, build the tileset (the kit's primary, the route's own
# cliffs, Route 2's cave mouth for Rock Tunnel's two mouths and Pewter's Gym made the Power Plant), paint the map, keep
# its joins to Route 9 and Lavender, make the seams and the doors, put the events where the new route has them. Run from
# the repository root (project/art/build_all.sh rebuilds every map).
set -e
A=project/art/route10-concept
K=project/art/kit/buildings
PG=project/art/route10-concept/buildings/power_plant
python3 $A/make_art.py
cd engine
P="-p ."
M=Route10_Frlg

# the tileset and the block files (the first time)
grep -q "gTileset_Route10Concept =" src/data/tilesets/headers.h || pae tileset new gTileset_Route10Concept --secondary $P
pae map geometry $M --primary gTileset_PalletConcept_General --secondary gTileset_Route10Concept \
    --blockdata data/layouts/Route10_Concept/map.bin --border data/layouts/Route10_Concept/border.bin \
    --width 38 --height 60 $P

pae tileset build ../$A/spec.json $P
pae map paint $M ../$A/grid.txt ../$A/legend.json --names ../$A/names.json --border ../$A/border.txt $P

# the joins: Route 9's road out (its rows 17-19) meets the left edge at rows 17-19; Lavender's road north (its columns
# 12-16) the bottom at columns 16-20, as before
pae map connect $M left Route9_Frlg --offset 0 $P
pae map connect $M down LavenderTown_Frlg --offset 4 $P
[ -n "$KIT_BUILD_ALL" ] || pae seam build $M $P

# doors, drawn in their packs (the caves' mouths are open)
pae door add $M 14 15 --frames ../$K/pokemon_center/pokemon_center_door.png --sound sliding $P
pae door add $M 29 39 --frames ../$PG/power_plant_door.png $P

# events: every warp keeps its number (the tunnel, the Center and the plant point at it)
pae map place $M warp 0 8 8 $P     # Rock Tunnel's north mouth, in the clearing's ridge
pae map place $M warp 1 10 45 $P   # its south mouth, at the mountains' foot
pae map place $M warp 2 29 39 $P   # the Power Plant's door, on its island
pae map place $M warp 3 14 15 $P   # the Pokémon Center
pae map place $M warp 4 25 37 $P   # where the plant's back door lets you out, on the island's west shore
# the trainers, where the plan is made for them (make_art.py: none of them sees the road)
pae map place $M object 0 28 50 $P   # Carol, Clark, Herman and Trent in the south valley
pae map place $M object 1 5 50 $P
pae map place $M object 2 26 57 $P
pae map place $M object 3 6 57 $P
pae map place $M object 4 27 22 $P   # Mark, on the river bank, and Heidi, by the meadow's hedge
pae map place $M object 5 22 13 $P
pae map place $M object 6 20 11 $P   # the young trees to cut, in the meadow's hedge
pae map place $M object 7 21 11 $P
pae map place $M object 8 22 11 $P
pae map place $M object 9 23 11 $P
pae map place $M object 10 27 41 $P  # the Electabuzz, by the Power Plant
pae map place $M object 11 21 4 $P   # the Voltorb, rolling about the meadow
pae map place $M object 15 25 8 $P
pae map place $M object 12 12 55 $P  # Fearow, in the south valley
pae map place $M object 13 7 48 $P   # Gengar, by Rock Tunnel's south mouth (at night)
pae map place $M object 14 6 23 $P   # Electrike, among the clearing's flowers
pae map place $M bg 0 14 46 $P       # the south mouth's sign
pae map place $M bg 1 26 15 $P       # the Power Plant sign, by the river
pae map place $M bg 2 12 9 $P        # the north mouth's sign
pae map place $M bg 3 3 10 $P        # the hidden Super Potion, in the clearing's corner
pae map place $M bg 4 33 41 $P       # the hidden Max Ether, on the island
pae map place $M bg 5 26 3 $P        # the hidden Cheri Berry, in the meadow
pae map place $M bg 6 25 24 $P       # the hidden Persim Berry, in the clearing
pae map place $M bg 7 34 56 $P       # the hidden Nanab Berry, in the valley's corner
# the Pokémon keep to their places and stand at the ground's elevation (some were on old ledges or water)
python3 - <<'PY'
import json
p = "data/maps/Route10_Frlg/map.json"
m = json.load(open(p))
o = m["object_events"]
for i in (11, 15):
    o[i]["movement_range_x"], o[i]["movement_range_y"] = 2, 2
o[14]["movement_range_y"] = 1
for i in range(10, 16):
    o[i]["elevation"] = 3
open(p, "w").write(json.dumps(m, indent=2) + "\n")
PY
