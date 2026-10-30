#!/bin/sh
# Rebuild Route 21's two maps from their concept with pae: lay out the plans, build the tileset they share (the kit's
# primary; nothing of their own), paint the maps, keep their joins to Pallet, to each other and to Cinnabar, make the
# seams, put the events where the new route has them. Run from the repository root (project/art/build_all.sh
# rebuilds every map).
set -e
A=project/art/route21-concept
python3 $A/make_art.py
python3 project/art/kit/settle.py $A grid_north.txt grid_south.txt  # the kit's small pieces into the ground they stand in
cd engine
P="-p ."
N=Route21_North_Frlg
S=Route21_South_Frlg

# the tileset and the block files (the first time)
grep -q "gTileset_Route21Concept =" src/data/tilesets/headers.h || pae tileset new gTileset_Route21Concept --secondary $P
pae map geometry $N --primary gTileset_PalletConcept_General --secondary gTileset_Route21Concept \
    --blockdata data/layouts/Route21_North_Concept/map.bin --border data/layouts/Route21_North_Concept/border.bin \
    --width 24 --height 50 $P
pae map geometry $S --primary gTileset_PalletConcept_General --secondary gTileset_Route21Concept \
    --blockdata data/layouts/Route21_South_Concept/map.bin --border data/layouts/Route21_South_Concept/border.bin \
    --width 24 --height 50 $P

pae tileset build ../$A/spec.json $P
pae map paint $N ../$A/grid_north.txt ../$A/legend.json --names ../$A/names.json --border ../$A/border.txt $P
pae map paint $S ../$A/grid_south.txt ../$A/legend.json --names ../$A/names.json --border ../$A/border.txt $P

# the joins stay where they were: Pallet's river (its columns 18-21) at the north map's top, columns 7-10; the two
# maps across their whole width; Cinnabar below the south map
pae map connect $N up PalletTown_Frlg --offset -11 $P
pae map connect $N down $S --offset 0 $P
pae map connect $S down CinnabarIsland_Frlg --offset 0 $P
[ -n "$KIT_BUILD_ALL" ] || { pae seam build $N $P; pae seam build $S $P; }

# events: the people and the Pokémon keep their order (the north map's object 5 stays off the map, as before)
pae map place $N object 0 6 25 $P    # Ronald, fishing off the islet's north shore
pae map place $N object 1 16 29 $P   # Wade, off its south shore
pae map place $N object 2 12 44 $P   # Spencer, swimming his round west of the pearl sandbar
pae map place $N object 3 14 35 $P   # Lil and Ian, swimming together
pae map place $N object 4 15 35 $P
pae map place $N object 6 19 3 $P    # Mr. Mime, in its meadow by the river
pae map place $N object 7 4 11 $P    # the Tangela, in the tall grass of both meadows
pae map place $N object 8 19 7 $P
pae map place $N object 9 20 38 $P   # Corphish, by the pearl sandbar
pae map place $N bg 0 18 41 $P       # the Pearl, hidden on the sandbar
pae map place $S object 0 15 8 $P    # Claude, fishing off the long islet's east shore
pae map place $S object 1 8 15 $P    # Nolan, off its west shore
pae map place $S object 2 15 24 $P   # Jack, Jerome and Roland, swimming
pae map place $S object 3 15 38 $P
pae map place $S object 4 10 29 $P
# everyone at the elevation of what they stand on: the water's or the ground's
python3 - <<'PY'
import json
for name, grid in (("Route21_North_Frlg", "grid_north.txt"), ("Route21_South_Frlg", "grid_south.txt")):
    p = f"data/maps/{name}/map.json"
    g = open(f"../project/art/route21-concept/{grid}").read().split()
    m = json.load(open(p))
    for e in m["object_events"]:
        if e.get("type") != "clone" and 0 <= e["y"] < len(g):
            e["elevation"] = 1 if g[e["y"]][e["x"]] == "s" else 3
    open(p, "w").write(json.dumps(m, indent=2) + "\n")
PY
