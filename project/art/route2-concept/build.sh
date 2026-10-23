#!/bin/sh
# Rebuild Route 2 from the concept with pae: lay out the plan, build the tileset (the kit's primary and the route's
# own), paint the map, join it to Pewter City and Viridian City, make the connection seams and the doors, put the
# events where the new route has them. Run from the repository root (project/art/build_all.sh rebuilds every map).
set -e
A=project/art/route2-concept
V=project/art/viridian-concept
python3 $A/make_art.py
cd engine
P="-p ."
M=Route2_Frlg

# the tileset and the block files (the first time)
grep -q "gTileset_Route2Concept =" src/data/tilesets/headers.h || pae tileset new gTileset_Route2Concept --secondary $P
pae map geometry $M --primary gTileset_PalletConcept_General --secondary gTileset_Route2Concept \
    --blockdata data/layouts/Route2_Concept/map.bin --border data/layouts/Route2_Concept/border.bin \
    --width 30 --height 80 $P

pae tileset build ../$A/spec.json $P
pae map paint $M ../$A/grid.txt ../$A/legend.json --names ../$A/names.json --border ../$A/border.txt $P

# the joins stay where they were: Pewter's road (its columns 22-25) meets the top at columns 8-11, Viridian's (its
# columns 22-27) the bottom at columns 6-11
pae map connect $M up PewterCity_Frlg --offset -14 $P
pae map connect $M down ViridianCity_Frlg --offset -16 $P
[ -n "$KIT_BUILD_ALL" ] || pae seam build $M $P  # build_all.sh makes them last, when every map is painted

# doors, drawn in their packs: the south forest gate's double door (two door blocks wide, both open as one) and the
# trade house's (Viridian's family house, two blocks tall)
pae door add $M 7 51 --frames ../$A/buildings/forest_gate_south/forest_gate_south_door.png $P
pae door add $M 22 24 --frames ../$V/buildings/house_family/house_family_door.png $P

# events
pae map place $M warp 0 7 20 $P               # the forest's north gate (both of its doorway's blocks)
pae map place $M warp 1 8 20 $P
pae map place $M warp 2 7 51 $P               # the forest's south gate (both of its double door's blocks)
pae map place $M warp 9 8 51 $P
pae map place $M warp 3 22 12 $P              # Diglett's Cave
pae map place $M warp 4 22 24 $P              # the trade house
pae map place $M warp 5 21 47 $P              # the east gatehouse: in at its south door...
pae map place $M warp 8 21 47 $P
pae map place $M warp 6 21 44 $P              # ...and out at its north one
pae map place $M warp 7 21 44 $P
pae map place $M bg 0 24 14 $P                # Diglett's Cave's sign, east of the cave's approach
pae map place $M bg 1 12 72 $P                # the route sign, by the road from Viridian
pae map place $M object 0 16 68 $P            # the trees to cut: the south one, into the eastern detour,
pae map place $M object 1 21 30 $P            # the middle one, past the east gatehouse,
pae map place $M object 2 16 14 $P            # and the north one, back to the north meadow
pae map place $M object 3 19 52 $P            # the Ether, on the spur west of the eastern path
pae map place $M object 4 25 64 $P            # the Paralyze Heal, on the spur east of it
pae map place $M object 5 11 55 $P            # Caterpie, by the tall grass in the south meadow
pae map place $M object 6 2 67 $P             # Weedle, by the tall grass further south
pae map place $M object 7 26 33 $P            # Zigzagoon, in the meadow past the east gatehouse

# the Friends story's group, in its camp west of the south road (the same shape as before; its anchor is in
# src/data/friends_scene_locations.h)
for who in BRIAN:5,62 HAM:4,61 JON:6,63 NICK:3,62 X:4,63 LB:5,60 TIM:2,63; do
    n=${who%%:*}; xy=${who#*:}
    pae map place $M object LOCALID_FRIENDS_ROUTE2_FRLG_$n ${xy%,*} ${xy#*,} $P
done
