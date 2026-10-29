#!/bin/sh
# Rebuild Saffron City from its concept with pae: draw its buildings, lay out the plan, build the tileset (the kit's
# primary, the city's own buildings, Viridian's houses and school), paint the map, make the doors, put the events
# where the new city has them. Saffron's joins aren't compiled (the routes see its twin, SaffronCity_Connection), so it
# has no joins to keep and no seams. Run from the repository root (project/art/build_all.sh rebuilds every map).
set -e
A=project/art/saffron-concept
B=project/art/packs/buildings_v0.3/buildings  # the remakes pack: the city's own buildings
K=project/art/kit/buildings
V=project/art/viridian-concept/buildings
python3 $A/make_art.py
cd engine
P="-p ."
M=SaffronCity_Frlg

# the tileset and the block files (the first time)
grep -q "gTileset_SaffronConcept =" src/data/tilesets/headers.h || pae tileset new gTileset_SaffronConcept --secondary $P
pae map geometry $M --primary gTileset_PalletConcept_General --secondary gTileset_SaffronConcept \
    --blockdata data/layouts/SaffronCity_Concept/map.bin --border data/layouts/SaffronCity_Concept/border.bin \
    --width 60 --height 48 $P

pae tileset build ../$A/spec.json $P
pae map paint $M ../$A/grid.txt ../$A/legend.json --names ../$A/names.json --border ../$A/border.txt $P

# doors, drawn in their packs (the gatehouses' double door is one wide door, the same on all three; the south
# gatehouse's doorway doesn't animate)
pae door add $M 6 30 --frames ../$K/pokemon_center/pokemon_center_door.png --sound sliding $P
pae door add $M 12 30 --frames ../$K/poke_mart/poke_mart_door.png --sound sliding $P
pae door add $M 38 17 --frames ../$B/silph_co/silph_co_door.png --sound sliding $P
pae door add $M 17 17 --frames ../$B/saffron_gym/saffron_gym_door.png $P
pae door add $M 7 17 --frames ../$B/fighting_dojo/fighting_dojo_door.png $P
pae door add $M 29 2 --frames ../$B/saffron_gate/saffron_gate_door.png $P
pae door add $M 6 8 --frames ../$V/house_pond_keeper/house_pond_keeper_door.png $P
pae door add $M 13 8 --frames ../$V/house_pond_keeper/house_pond_keeper_door.png $P
pae door add $M 36 30 --frames ../$V/house_pond_keeper/house_pond_keeper_door.png $P

# events: every warp keeps its number (the buildings behind them point at it); the west and east gatehouses' right
# door blocks are second warps to the same gatehouse doors, added the first time (15 and 16)
python3 - <<'EOF'
import json
p = "data/maps/SaffronCity_Frlg/map.json"
m = json.load(open(p))
w = m["warp_events"]
if len(w) == 15:
    w.append(dict(w[8]))
    w.append(dict(w[10]))
open(p, "w").write(json.dumps(m, indent=2) + "\n")
EOF
pae map place $M warp 0 38 17 $P    # Silph Co.
pae map place $M warp 1 6 8 $P      # Copycat's house
pae map place $M warp 2 7 17 $P     # the Fighting Dojo
pae map place $M warp 3 17 17 $P    # Sabrina's Gym
pae map place $M warp 4 13 8 $P     # the house
pae map place $M warp 5 12 30 $P    # the Mart
pae map place $M warp 6 6 30 $P     # the Pokémon Center
pae map place $M warp 7 19 30 $P    # Mr. Psychic's house
pae map place $M warp 8 2 21 $P     # the west gatehouse (to Route 7)...
pae map place $M warp 15 3 21 $P
pae map place $M warp 9 29 2 $P     # ...the north one (to Route 5)...
pae map place $M warp 13 30 2 $P
pae map place $M warp 10 56 21 $P   # ...the east one (to Route 8)...
pae map place $M warp 16 57 21 $P
pae map place $M warp 11 29 45 $P   # ...and the south one (to Route 6), entered walking south
pae map place $M warp 12 30 45 $P
pae map place $M warp 14 36 30 $P   # the Trainer Fan Club
# the people keep their order (the Rockets and the townspeople come and go by flag; the Friends by local id)
pae map place $M object 0 6 9 $P     # Rockets, until Silph Co. is freed: one at Copycat's door,
pae map place $M object 1 24 20 $P   # one walking the Gym square,
pae map place $M object 2 17 18 $P   # one barring the Gym's door,
pae map place $M object 3 13 9 $P    # one at the house's door,
pae map place $M object 4 7 34 $P    # one walking the park,
pae map place $M object 5 39 18 $P   # Silph's door guard (in front of the door until Mr. Fuji is rescued: the map
                                     # script puts him at 38,18), asleep beside it after
pae map place $M object 6 44 33 $P   # one walking the flower gardens,
pae map place $M object 7 45 23 $P   # one walking the avenue
pae map place $M object 8 50 34 $P   # the townspeople, back once Silph is freed: the youngster in the gardens,
pae map place $M object 9 51 18 $P   # the Magnet Train's attendant, by the station,
pae map place $M object 10 35 20 $P  # the man looking up at Silph Co.,
pae map place $M object 11 51 27 $P  # the boy who flew here on his Pidgeot, past the shops,
pae map place $M object 12 52 27 $P
pae map place $M object 13 19 33 $P  # the lass, walking the park
pae map place $M object 14 55 43 $P  # the battle girl (after the League), behind the towers
pae map place $M object 15 51 29 $P  # Pidgey, Pidgey, Pidgey and Abra about the city
pae map place $M object 16 26 40 $P
pae map place $M object 17 24 3 $P
pae map place $M object 18 55 11 $P
pae map place $M object 19 50 8 $P   # the Friends, round 50,8 in the garden behind Silph Co.
pae map place $M object 20 50 10 $P
pae map place $M object 21 49 9 $P
pae map place $M object 22 48 8 $P
pae map place $M object 23 52 8 $P
pae map place $M object 24 48 10 $P
pae map place $M object 25 47 6 $P
pae map place $M bg 0 27 3 $P        # the city sign, by the north gate
pae map place $M bg 1 11 17 $P       # the Dojo's sign
pae map place $M bg 2 33 17 $P       # Silph's latest product
pae map place $M bg 3 9 30 $P        # trainer tips, by the Center
pae map place $M bg 4 43 17 $P       # Silph Co.'s sign
pae map place $M bg 5 53 26 $P       # trainer tips, by the east gate
pae map place $M bg 6 21 17 $P       # the Gym's sign
pae map place $M bg 7 22 30 $P       # Mr. Psychic's house's sign
pae map place $M bg 8 39 30 $P       # the Trainer Fan Club's sign
# the attendant stays by the station; everyone stands at the ground's elevation
python3 - <<'EOF'
import json
p = "data/maps/SaffronCity_Frlg/map.json"
m = json.load(open(p))
o = m["object_events"]
o[9]["movement_type"] = "MOVEMENT_TYPE_FACE_DOWN"
o[4]["movement_range_x"] = 4  # the park's Rocket: the lawn north of the pond
for e in o:
    if e.get("type") != "clone" and "elevation" in e:
        e["elevation"] = 3
open(p, "w").write(json.dumps(m, indent=2) + "\n")
EOF
