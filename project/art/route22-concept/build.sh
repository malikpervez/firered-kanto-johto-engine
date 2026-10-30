#!/bin/sh
# Rebuild Route 22 from the concept with pae: lay out the plan, build the tileset (the kit's primary and the route's
# own), paint the map, join it to Route 23 and Viridian City, make the connection seams and the gate's door, put the
# events where the new route has them. Run from the repository root (project/art/build_all.sh rebuilds every map).
set -e
A=project/art/route22-concept
python3 $A/make_art.py
python3 project/art/kit/settle.py $A  # the kit's small pieces into the ground they stand in
cd engine
P="-p ."
M=Route22_Frlg

# the tileset and the block files (the first time)
grep -q "gTileset_Route22Concept =" src/data/tilesets/headers.h || pae tileset new gTileset_Route22Concept --secondary $P
pae map geometry $M --primary gTileset_PalletConcept_General --secondary gTileset_Route22Concept \
    --blockdata data/layouts/Route22_Concept/map.bin --border data/layouts/Route22_Concept/border.bin \
    --width 52 --height 28 $P

pae tileset build ../$A/spec.json $P
pae map paint $M ../$A/grid.txt ../$A/legend.json --names ../$A/names.json --border ../$A/border.txt $P

# Viridian to the east, where it was (its rows 28-31, the road west, meet Route 22's rows 6-9). Route 23 isn't
# joined: it was only seen across the top (both edges are solid; you go through the gate), and its strip needs more
# palettes than Route 22 has free, so each map shows its own border there until Route 23 is rebuilt (WORLD.md)
pae map connect $M right ViridianCity_Frlg --offset -22 $P
[ -n "$KIT_BUILD_ALL" ] || pae seam build $M $P  # build_all.sh makes them last, when every map is painted

# the gate's door, drawn in its pack: two blocks tall (the door and the block above it)
pae door add $M 12 13 --frames ../$A/buildings/league_front_gate/league_front_gate_door.png $P

# events
pae map place $M warp 0 12 13 $P              # the League Front Gate (both of its old door blocks are one now)
pae map place $M warp 1 12 13 $P
for i in 0 1 2 3 4 5 6 7; do                  # Blue meets you on the road from Viridian: one trigger a row (6-9),
    pae map place $M coord $i 44 $((6 + i % 4)) $P  # early (0-3) and late (4-7); he comes from the west
done
pae map place $M bg 0 18 14 $P                # the gate's sign, at the top of the stairs
pae map place $M bg 1 38 12 $P                # and where the stone approach leaves the road
pae map place $M object LOCALID_ROUTE22_RIVAL 36 7 $P  # (his script puts him in your row)
pae map place $M object 1 24 8 $P             # Fearow, Spearow, Ponyta, Doduo and Taillow about the route
pae map place $M object 2 28 9 $P
pae map place $M object 3 36 22 $P
pae map place $M object 4 38 17 $P
pae map place $M object 5 5 22 $P
pae map place $M object 6 24 15 $P            # the gentleman
