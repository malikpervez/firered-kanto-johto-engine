#!/bin/sh
# Rebuild Route 17 (Cycling Road) from its concept with pae: lay out the plan, build the tileset (the kit's primary and
# the track), paint the map, keep its joins to Route 16 and Route 18, make the seams, put the events where the new
# route has them. Run from the repository root (project/art/build_all.sh rebuilds every map).
set -e
A=project/art/route17-concept
python3 $A/make_art.py
python3 project/art/kit/settle.py $A  # the kit's small pieces into the ground they stand in
cd engine
P="-p ."
M=Route17_Frlg

# the tileset and the block files (the first time)
grep -q "gTileset_Route17Concept =" src/data/tilesets/headers.h || pae tileset new gTileset_Route17Concept --secondary $P
pae map geometry $M --primary gTileset_PalletConcept_General --secondary gTileset_Route17Concept \
    --blockdata data/layouts/Route17_Concept/map.bin --border data/layouts/Route17_Concept/border.bin \
    --width 36 --height 120 $P

pae tileset build ../$A/spec.json $P
pae map paint $M ../$A/grid.txt ../$A/legend.json --names ../$A/names.json --border ../$A/border.txt $P

# the joins: Route 16's road down (its columns 12-17) at the top edge, the same columns; Route 18's road (its columns
# 8-16) below the bottom edge, at columns 14-22
pae map connect $M up Route16_Frlg --offset 0 $P
pae map connect $M down Route18_Frlg --offset 6 $P
[ -n "$KIT_BUILD_ALL" ] || pae seam build $M $P

# events: the bikers keep their order (0-9), then the Pokémon about
pae map place $M object 0 13 24 $P   # Virgil, riding up and down the cutting
pae map place $M object 1 22 30 $P   # Isaiah, at the cliff top
pae map place $M object 2 4 48 $P    # Raul, circling the west rest stop
pae map place $M object 3 21 42 $P   # Nikolas, on the causeway
pae map place $M object 4 8 50 $P    # Billy, at the west rest stop's mouth, looking out over the track
pae map place $M object 5 12 70 $P   # Jamal, watching the lagoon's west lane...
pae map place $M object 6 23 72 $P   # ...and Zeek its east one
pae map place $M object 7 13 88 $P   # Corey, below the lagoon
pae map place $M object 8 31 91 $P   # William, circling the east rest stop
pae map place $M object 9 21 98 $P   # Jaxon, on the last stretch
pae map place $M object 10 29 94 $P  # Gulpin, at the east rest stop
pae map place $M object 11 4 53 $P   # Grimer, about the west rest stop (watch out for discarded items)
pae map place $M object 12 5 12 $P   # Houndour, in the clearing at the top
pae map place $M bg 0 9 9 $P         # the route sign, at the start
pae map place $M bg 1 26 13 $P       # trainer tips: B to stay in place on the slope
pae map place $M bg 2 31 87 $P       # trainer tips: the same species grow differently (the east rest stop)
pae map place $M bg 3 5 45 $P        # the notice: watch out for discarded items (the west rest stop)
pae map place $M bg 4 29 87 $P       # the notice: throw Poké Balls (the east rest stop)
pae map place $M bg 5 9 107 $P       # Cycling Road: the slope ends here (the finish)
pae map place $M bg 6 31 13 $P       # the hidden Rare Candy, in the clearing's flowers
pae map place $M bg 7 2 54 $P        # the Full Restore, in the west rest stop's corner
pae map place $M bg 8 33 86 $P       # the PP Up, in the east rest stop's corner
pae map place $M bg 9 8 46 $P        # the Max Revive, by the west rest stop's lamp
pae map place $M bg 10 30 112 $P     # the Max Elixir, on the shore at the finish
# the bikers' rounds; everyone stands at the ground's elevation
python3 - <<'EOF'
import json
p = "data/maps/Route17_Frlg/map.json"
m = json.load(open(p))
o = m["object_events"]
for i, (rx, ry) in {0: (1, 6), 1: (1, 5), 3: (1, 5), 7: (1, 5), 9: (1, 5), 11: (2, 2)}.items():
    o[i]["movement_range_x"], o[i]["movement_range_y"] = rx, ry
for e in o:
    if e.get("type") != "clone" and "elevation" in e:
        e["elevation"] = 3
open(p, "w").write(json.dumps(m, indent=2) + "\n")
EOF
