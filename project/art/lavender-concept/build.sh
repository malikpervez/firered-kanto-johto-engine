#!/bin/sh
# Rebuild Lavender Town from its concept with pae: lay out the plan, build the tileset (the kit's primary and the
# town's own, with the Pokémon Tower), paint the map, keep its joins to Routes 10, 8 and 12, make the seams and the
# doors, put the events where the new town has them. Run from the repository root (project/art/build_all.sh rebuilds
# every map).
set -e
A=project/art/lavender-concept
K=project/art/kit/buildings
V=project/art/viridian-concept/buildings
T=project/art/lavender-concept/buildings/pokemon_tower
python3 $A/make_art.py
cd engine
P="-p ."
M=LavenderTown_Frlg

# the tileset and the block files (the first time)
grep -q "gTileset_LavenderConcept =" src/data/tilesets/headers.h || pae tileset new gTileset_LavenderConcept --secondary $P
pae map geometry $M --primary gTileset_PalletConcept_General --secondary gTileset_LavenderConcept \
    --blockdata data/layouts/LavenderTown_Concept/map.bin --border data/layouts/LavenderTown_Concept/border.bin \
    --width 38 --height 32 $P

pae tileset build ../$A/spec.json $P
pae map paint $M ../$A/grid.txt ../$A/legend.json --names ../$A/names.json --border ../$A/border.txt $P

# the joins: Route 10's road south (its columns 16-20) meets the top at columns 12-16, as before; the new Route 8's road
# (its rows 13-15) the left edge at rows 9-11 (offset -4, was -10); Route 12's (its columns 11-13) the bottom at columns
# 13-15, so Route 12 sits 4 blocks further east under the new town than under the old (offset 2, was -2)
pae map connect $M up Route10_Frlg --offset -4 $P
pae map connect $M left Route8_Frlg --offset -4 $P
pae map connect $M down Route12_Frlg --offset 2 $P
[ -n "$KIT_BUILD_ALL" ] || pae seam build $M $P

# doors, drawn in their packs
pae door add $M 7 6 --frames ../$K/pokemon_center/pokemon_center_door.png --sound sliding $P
pae door add $M 19 6 --frames ../$K/poke_mart/poke_mart_door.png --sound sliding $P
pae door add $M 29 8 --frames ../$T/pokemon_tower_door.png $P
pae door add $M 5 16 --frames ../$V/house_family/house_family_door.png $P
pae door add $M 4 24 --frames ../$V/house_pond_keeper/house_pond_keeper_door.png $P
pae door add $M 9 24 --frames ../$V/house_gardener/house_gardener_door.png $P

# events: every warp keeps its number (the buildings behind them point at it)
pae map place $M warp 0 29 8 $P    # the Pokémon Tower
pae map place $M warp 1 7 6 $P     # the Pokémon Center
pae map place $M warp 2 5 16 $P    # the Volunteer House (Mr. Fuji's), west of the square
pae map place $M warp 3 4 24 $P    # the two houses in the south-west yard
pae map place $M warp 4 9 24 $P
pae map place $M warp 5 19 6 $P    # the Poké Mart
# the people keep their order (the Friends are called by local id)
pae map place $M object 0 27 19 $P    # the girl who asks if you believe in ghosts, about the east lawn
pae map place $M object 1 20 16 $P    # the worker, by the stone garden
pae map place $M object 2 25 12 $P    # the boy, on the way to the tower
pae map place $M object 3 32 4 $P     # at night: ghosts in the tower's garden...
pae map place $M object 4 33 5 $P
pae map place $M object 5 34 4 $P
pae map place $M object 6 21 15 $P    # ...Haunters going round the stone garden...
pae map place $M object 7 23 17 $P
pae map place $M object 8 35 26 $P    # ...and Gengar and Gastly about the town
pae map place $M object 9 3 8 $P
pae map place $M object 10 7 17 $P
pae map place $M object 11 22 16 $P
pae map place $M object 12 10 16 $P   # the gentleman, by the Volunteer House
pae map place $M bg 0 23 8 $P         # the Silph Scope notice, on the way to the tower
pae map place $M bg 1 11 8 $P         # the town sign, at the north road's foot
pae map place $M bg 2 26 8 $P         # the tower's sign
pae map place $M bg 3 8 16 $P         # the Volunteer House's sign
# (the Friends, objects 13-19, camp round 13,13 as before: src/data/friends_scene_locations.h)
# everyone stands at the ground's elevation (Gengar and a Gastly were on old ledges)
python3 - <<'PY'
import json
p = "data/maps/LavenderTown_Frlg/map.json"
m = json.load(open(p))
for o in m["object_events"][:13]:
    o["elevation"] = 3
open(p, "w").write(json.dumps(m, indent=2) + "\n")
PY
