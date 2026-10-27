#!/bin/sh
# Rebuild Cinnabar Island from its concept with pae: draw its buildings, lay out the plan, build the tileset (the
# kit's primary, the island's Gym, Mansion and Lab, the kit's cliffs for the volcano), paint the map, keep its joins to
# Routes 21 and 20, make the doors, put the events where the new island has them. Run from the repository root
# (project/art/build_all.sh rebuilds every map).
set -e
A=project/art/cinnabar-concept
B=project/art/cinnabar-concept/buildings
K=project/art/kit/buildings
python3 $A/make_art.py
cd engine
P="-p ."
M=CinnabarIsland_Frlg

# the tileset and the block files (the first time); the old island was in FireRed's metatile format, the kit is in
# HnS's (its doors' behaviours are HnS's)
grep -q "gTileset_CinnabarConcept =" src/data/tilesets/headers.h || pae tileset new gTileset_CinnabarConcept --secondary $P
pae map geometry $M --primary gTileset_PalletConcept_General --secondary gTileset_CinnabarConcept \
    --blockdata data/layouts/CinnabarIsland_Concept/map.bin --border data/layouts/CinnabarIsland_Concept/border.bin \
    --version hns --width 96 --height 44 $P

pae tileset build ../$A/spec.json $P
pae map paint $M ../$A/grid.txt ../$A/legend.json --names ../$A/names.json --border ../$A/border.txt $P

# the joins stay where they were: Route 21's sea above (its columns 0-23), Route 20's to the right (its rows 0-19)
pae map connect $M up Route21_South_Frlg --offset 0 $P
pae map connect $M right Route20_Frlg --offset 0 $P
[ -n "$KIT_BUILD_ALL" ] || pae seam build $M $P

# doors, drawn in their packs (the Lab's is Pallet's lab's door, its panel moved by pae)
pae door add $M 14 11 --frames ../$K/pokemon_center/pokemon_center_door.png --sound sliding $P
pae door add $M 18 11 --frames ../$K/poke_mart/poke_mart_door.png --sound sliding $P
pae door add $M 20 4 --frames ../$B/cinnabar_gym/cinnabar_gym_door.png $P
pae door add $M 6 4 --frames ../$B/pokemon_mansion/pokemon_mansion_door.png $P
pae door add $M 6 11 --panel 1,0,15,14 $P

# events: every warp keeps its number (the buildings behind them point at it)
pae map place $M warp 0 6 4 $P      # the burned Mansion
pae map place $M warp 1 20 4 $P     # Blaine's Gym
pae map place $M warp 2 6 11 $P     # the Pokémon Lab
pae map place $M warp 3 14 11 $P    # the Pokémon Center
pae map place $M warp 4 18 11 $P    # the Mart
# the people and the Pokémon keep their order (the scenes and the Friends' find them by local id)
pae map place $M object 0 14 6 $P    # the woman on the street
pae map place $M object 1 11 13 $P   # the old man on the harbour street
pae map place $M object 2 20 7 $P    # Bill, by the Mart (the scenes move him)
pae map place $M object 3 23 7 $P    # the Seagallop, at the harbour
pae map place $M object 4 60 26 $P   # Magcargo and Slugma, on the ash below the volcano
pae map place $M object 5 62 26 $P
pae map place $M object 6 61 27 $P
pae map place $M object 7 78 9 $P    # Koffing and Weezing, on the ash to the east
pae map place $M object 8 79 11 $P
pae map place $M object 9 52 9 $P    # Magmar and Magby, on the ash to the west
pae map place $M object 10 51 13 $P
pae map place $M object 11 48 15 $P  # Misdreavus (at night), by the woods
pae map place $M object 12 66 27 $P  # Torkoal, by the hot spring
pae map place $M object 13 88 40 $P  # Wailmer, out at sea
pae map place $M object 14 22 10 $P  # the gentleman, in the east lane
pae map place $M object 15 46 20 $P  # the Friends, round 46,20
pae map place $M object 16 48 20 $P
pae map place $M object 17 45 19 $P
pae map place $M object 18 44 20 $P
pae map place $M object 19 47 22 $P
pae map place $M object 20 45 21 $P
pae map place $M object 21 44 22 $P
pae map place $M coord 0 20 5 $P     # the Gym's lock
pae map place $M bg 0 12 6 $P        # the island's sign
pae map place $M bg 1 9 12 $P        # the Lab's sign (two boards)
pae map place $M bg 2 22 5 $P        # the Gym's sign
pae map place $M bg 3 10 12 $P
# everyone at the elevation of what they stand on: the water's or the ground's
python3 - <<'PY'
import json
p = "data/maps/CinnabarIsland_Frlg/map.json"
grid = open("../project/art/cinnabar-concept/grid.txt").read().split()
m = json.load(open(p))
for e in m["object_events"]:
    if e.get("type") != "clone":
        e["elevation"] = 1 if grid[e["y"]][e["x"]] == "s" else 3
open(p, "w").write(json.dumps(m, indent=2) + "\n")
PY
