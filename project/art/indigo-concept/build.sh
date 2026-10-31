#!/bin/sh
# Rebuild Indigo Plateau from its concept with pae: draw the League's tower, lay out the plan, build the tileset (the
# kit's primary and the tower), paint the map, keep its joins to Route 23 and League West Pass, make the seams and the
# door, put the events where the new mountaintop has them. Run from the repository root
# (project/art/build_all.sh rebuilds every map).
set -e
A=project/art/indigo-concept
B=project/art/packs/buildings_v0.3/buildings  # the remakes pack: the League
python3 $A/make_art.py
python3 project/art/kit/settle.py $A  # the kit's small pieces into the ground they stand in
cd engine
P="-p ."
M=IndigoPlateau_Exterior_Frlg

# the tileset and the block files (the first time); the old mountaintop's layout wasn't in the kit's (HnS's) format
grep -q "gTileset_IndigoConcept =" src/data/tilesets/headers.h || pae tileset new gTileset_IndigoConcept --secondary $P
pae map geometry $M --primary gTileset_PalletConcept_General --secondary gTileset_IndigoConcept \
    --blockdata data/layouts/IndigoPlateau_Concept/map.bin --border data/layouts/IndigoPlateau_Concept/border.bin \
    --version hns --width 24 --height 20 $P

pae tileset build ../$A/spec.json $P
pae map paint $M ../$A/grid.txt ../$A/legend.json --names ../$A/names.json --border ../$A/border.txt $P

# the joins stay where they were: Route 23's road below (its columns 10-13), League West Pass's road to the left (its
# rows 9-11)
pae map connect $M down Route23_Frlg --offset 0 $P
pae map connect $M left LeagueWestPass_Frlg --offset 0 $P
[ -n "$KIT_BUILD_ALL" ] || pae seam build $M $P

# the League's door, drawn in its pack (Silph Co.'s, recoloured)
pae door add $M 11 11 --frames ../$B/pokemon_league/pokemon_league_door.png --sound sliding $P

# events: the warp keeps its number (the Pokémon Center points at it); the people keep their order
pae map place $M warp 0 11 11 $P
pae map place $M object 0 11 11 $P   # the rival and Oak, for the credits (hidden till then), at the door as before
pae map place $M object 1 11 11 $P
pae map place $M object 2 2 9 $P     # the workers across the west road, until the game is won
pae map place $M object 3 2 10 $P
pae map place $M object 4 2 11 $P
python3 - <<'PY'
import json
p = "data/maps/IndigoPlateau_Exterior_Frlg/map.json"
m = json.load(open(p))
for e in m["object_events"]:
    e["elevation"] = 3
open(p, "w").write(json.dumps(m, indent=2) + "\n")
PY
