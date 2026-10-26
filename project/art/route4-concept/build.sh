#!/bin/sh
# Rebuild Route 4 from its concept with pae: lay out the plan, build the tileset (the kit's primary and the route's
# own cliffs and cave mouths), paint the map, keep its joins to Route 3 and Cerulean City, make the seams and the
# Center's door, put the events where the new route has them. Run from the repository root
# (project/art/build_all.sh rebuilds every map).
set -e
A=project/art/route4-concept
K=project/art/kit/buildings
python3 $A/make_art.py
cd engine
P="-p ."
M=Route4_Frlg

# the tileset and the block files (the first time)
grep -q "gTileset_Route4Concept =" src/data/tilesets/headers.h || pae tileset new gTileset_Route4Concept --secondary $P
pae map geometry $M --primary gTileset_PalletConcept_General --secondary gTileset_Route4Concept \
    --blockdata data/layouts/Route4_Concept/map.bin --border data/layouts/Route4_Concept/border.bin \
    --width 108 --height 20 $P

pae tileset build ../$A/spec.json $P
pae map paint $M ../$A/grid.txt ../$A/legend.json --names ../$A/names.json --border ../$A/border.txt $P

# the joins stay where they were: Route 3's pass (its columns 68-75) meets the bottom at columns 8-15, Cerulean's
# road (its rows 17-20) the right edge at rows 10-13
pae map connect $M down Route3_Frlg --offset -60 $P
pae map connect $M right CeruleanCity_Frlg --offset -7 $P
[ -n "$KIT_BUILD_ALL" ] || { pae seam build $M $P; pae seam build Route3_Frlg $P; }

pae door add $M 6 8 --frames ../$K/pokemon_center/pokemon_center_door.png --sound sliding $P

# events: every warp keeps its number; the people keep their order (the story's scenes call some by number: the
# stranger and his rock 12-13, Jessie and Meowth 14-15, the Friends from 16)
pae map place $M warp 0 19 14 $P   # Mt. Moon's near mouth (into its first floor)
pae map place $M warp 1 36 6 $P    # its far mouth (out of its basement), on the high shelf
pae map place $M warp 2 6 8 $P     # the Pokémon Center
pae map place $M object 0 10 6 $P    # the woman by the Center
pae map place $M object 1 75 3 $P    # Crissy, on the shelf: she looks east along it
pae map place $M object 2 68 3 $P    # the TM, on the shelf
pae map place $M object 3 12 14 $P   # the boy on Route 3's road
pae map place $M object 4 50 3 $P    # the martial artists who teach Mega Punch...
pae map place $M object 5 53 3 $P    # ...and Mega Kick, facing each other
pae map place $M object 7 62 3 $P    # Pidgey, on the shelf
pae map place $M object 8 70 15 $P   # Ekans, in the grass
pae map place $M object 9 85 3 $P    # Seviper, on the shelf
pae map place $M object 10 4 14 $P   # Zangoose, by the Center's flowers
pae map place $M object 11 56 8 $P   # the stranger, on the shelf by its edge...
pae map place $M object 12 57 8 $P   # ...and his rock
pae map place $M object 13 41 7 $P   # Jessie, by the far mouth...
pae map place $M object 14 43 7 $P   # ...and Meowth, in the net
pae map place $M object 6 114 0 $P   # (Cerulean Cave's guard as Route 4 shows him: 6,7 in Cerulean)
pae map place $M bg 0 16 12 $P       # Mt. Moon's sign, by the near mouth
pae map place $M bg 1 44 3 $P        # the route sign, on the shelf
pae map place $M bg 2 43 2 $P        # the hidden items: on the shelf,
pae map place $M bg 3 5 14 $P        # by the Center's flowers,
pae map place $M bg 4 67 17 $P       # and in the grass
# (the Friends' camp, 16-22, stays where it was: its anchor is 83,14 in src/data/friends_scene_locations.h)
