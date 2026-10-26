#!/bin/sh
# Rebuild Celadon City from its concept with pae: draw its buildings, lay out the plan, build the tileset (the kit's
# primary, the city's own buildings and Viridian's houses), paint the map, keep its joins to Route 16 and Route 7, make
# the seams and the doors, put the events where the new city has them. Run from the repository root
# (project/art/build_all.sh rebuilds every map).
set -e
A=project/art/celadon-concept
B=project/art/celadon-concept/buildings
K=project/art/kit/buildings
V=project/art/viridian-concept/buildings
python3 $A/make_art.py
cd engine
P="-p ."
M=CeladonCity_Frlg

# the tileset and the block files (the first time)
grep -q "gTileset_CeladonConcept =" src/data/tilesets/headers.h || pae tileset new gTileset_CeladonConcept --secondary $P
pae map geometry $M --primary gTileset_PalletConcept_General --secondary gTileset_CeladonConcept \
    --blockdata data/layouts/CeladonCity_Concept/map.bin --border data/layouts/CeladonCity_Concept/border.bin \
    --width 60 --height 40 $P

pae tileset build ../$A/spec.json $P
pae map paint $M ../$A/grid.txt ../$A/legend.json --names ../$A/names.json --border ../$A/border.txt $P

# the joins: the boulevard's two ends (rows 20-23) meet Route 16's road (its rows 22-25) at the left edge and Route 7's
# (its rows 10-13) at the right
pae map connect $M left Route16_Frlg --offset -2 $P
pae map connect $M right Route7_Frlg --offset 10 $P
[ -n "$KIT_BUILD_ALL" ] || pae seam build $M $P

# doors, drawn in their packs (the Mansion's back door is a doorway: it doesn't animate)
pae door add $M 49 18 --frames ../$K/pokemon_center/pokemon_center_door.png --sound sliding $P
pae door add $M 10 18 --frames ../$B/department_store/department_store_door.png --sound sliding $P
pae door add $M 15 18 --frames ../$B/department_store/department_store_door.png --sound sliding $P
pae door add $M 25 18 --frames ../$B/mansion/mansion_door.png $P
pae door add $M 35 18 --frames ../$B/hotel/hotel_door.png $P
pae door add $M 28 29 --frames ../$B/game_corner/game_corner_door.png --sound sliding $P
pae door add $M 12 34 --frames ../$B/celadon_gym/celadon_gym_door.png $P
pae door add $M 35 29 --frames ../$V/house_pond_keeper/house_pond_keeper_door.png $P
pae door add $M 41 29 --frames ../$V/house_family/house_family_door.png $P
pae door add $M 46 29 --frames ../$V/house_pond_keeper/house_pond_keeper_door.png $P  # (the Prize Room's pack)

# events: every warp keeps its number (the buildings behind them point at it)
pae map place $M warp 0 28 29 $P    # the Game Corner, on Lucky Lane
pae map place $M warp 1 10 18 $P    # the Department Store's two doors
pae map place $M warp 2 15 18 $P
pae map place $M warp 3 25 18 $P    # the Mansion's front door...
pae map place $M warp 10 25 11 $P   # ...and its back door (the Mansion points at 11; 10 and 12 share its block)
pae map place $M warp 11 25 11 $P
pae map place $M warp 12 25 11 $P
pae map place $M warp 4 49 18 $P    # the Pokémon Center
pae map place $M warp 5 35 29 $P    # the Prize Room
pae map place $M warp 6 12 34 $P    # Erika's Gym
pae map place $M warp 7 41 29 $P    # the restaurant
pae map place $M warp 8 46 29 $P    # the house on Lucky Lane
pae map place $M warp 9 35 18 $P    # the hotel
# the people keep their order (the stranger and the researchers' scenes remove them by local id)
pae map place $M object 0 44 19 $P    # a Rocket on the pavement by the Center (until the hideout)
pae map place $M object 1 42 17 $P    # the fat man and his Poliwrath, between the hotel and the Center
pae map place $M object 2 43 17 $P
pae map place $M object 3 35 32 $P    # the little girl, walking round the pond garden's flowers
pae map place $M object 4 40 21 $P    # the woman who doesn't like the Game Corner, on the boulevard
pae map place $M object 5 23 28 $P    # the old man who blew it all at the slots, by the Game Corner
pae map place $M object 6 31 17 $P    # the softboiled tutor, by the Mansion
pae map place $M object 7 38 31 $P    # a Rocket on Lucky Lane (until the hideout)
pae map place $M object 8 14 24 $P    # the old man by the Gym garden's tree
pae map place $M object 9 50 13 $P    # the trees to cut: the walled garden's, behind the Center...
pae map place $M object 10 12 25 $P   # ...and the Gym garden's
pae map place $M object 11 19 17 $P   # the boy by the Department Store
pae map place $M object 13 51 8 $P    # the Ether, in the walled garden
pae map place $M object 14 47 24 $P   # the Silph scientist, on the pavement
pae map place $M object 15 39 16 $P   # Pidgey, on the lawn by the hotel
pae map place $M object 16 16 30 $P   # Bellsprout, in the Gym garden
pae map place $M object 17 50 34 $P   # Jigglypuff, in the pond garden
pae map place $M object 18 33 27 $P   # the stranger, between the Game Corner and the Prize Room (after the hideout)
pae map place $M object 19 36 36 $P   # the researchers and their Meowth, in the pond garden (after the hideout)
pae map place $M object 20 37 36 $P
pae map place $M object 21 36 37 $P
pae map place $M object 22 25 34 $P   # the Friends, round 25,34
pae map place $M object 23 23 34 $P
pae map place $M object 24 26 33 $P
pae map place $M object 25 24 33 $P
pae map place $M object 26 24 35 $P
pae map place $M object 27 25 36 $P
pae map place $M object 28 22 35 $P
pae map place $M bg 0 52 29 $P        # trainer tips, at Lucky Lane's east end
pae map place $M bg 1 38 29 $P        # the prize exchange sign
pae map place $M bg 2 33 29 $P        # the Game Corner's sign
pae map place $M bg 3 55 18 $P        # the town sign, by the east entrance
pae map place $M bg 4 30 18 $P        # the Mansion's sign
pae map place $M bg 5 45 18 $P        # trainer tips, by the Center
pae map place $M bg 6 18 18 $P        # the Department Store's sign
pae map place $M bg 7 14 35 $P        # the Gym's sign, in its garden
pae map place $M bg 8 54 10 $P        # the hidden PP Up, in the walled garden
# the girl walks round her square, the woman keeps to the boulevard; Route 16's tree is shown across the join where it
# stands on Route 16's grid (its 46,21: x 46 - 56, y 21 - 2); everyone stands at the ground's elevation
python3 - <<'PY'
import json
p = "data/maps/CeladonCity_Frlg/map.json"
m = json.load(open(p))
o = m["object_events"]
o[3]["movement_range_x"], o[3]["movement_range_y"] = 4, 4
o[4]["movement_range_x"], o[4]["movement_range_y"] = 3, 1
clone = [e for e in o if e.get("type") == "clone" and e.get("target_map") == "MAP_ROUTE16"]
assert len(clone) == 1
clone[0]["x"], clone[0]["y"] = -10, 19
for e in o:
    if e.get("type") != "clone" and "elevation" in e:
        e["elevation"] = 3
open(p, "w").write(json.dumps(m, indent=2) + "\n")
PY
