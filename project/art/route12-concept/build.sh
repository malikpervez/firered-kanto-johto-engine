#!/bin/sh
# Rebuild Route 12 from its concept with pae: lay out the plan, build the tileset (the kit's primary, the north
# gatehouse and the fishing house), paint the map, keep its joins to Lavender, Route 11 and Route 13, make the seams,
# add the doors, put the events where the new route has them. Run from the repository root
# (project/art/build_all.sh rebuilds every map).
set -e
A=project/art/route12-concept
B=project/art/packs/buildings_v0.3/buildings  # the remakes pack: the gatehouse
V=project/art/viridian-concept/buildings
python3 $A/make_art.py
python3 project/art/kit/settle.py $A  # the kit's small pieces into the ground they stand in
cd engine
P="-p ."
M=Route12_Frlg

# the tileset and the block files (the first time)
grep -q "gTileset_Route12Concept =" src/data/tilesets/headers.h || pae tileset new gTileset_Route12Concept --secondary $P
pae map geometry $M --primary gTileset_PalletConcept_General --secondary gTileset_Route12Concept \
    --blockdata data/layouts/Route12_Concept/map.bin --border data/layouts/Route12_Concept/border.bin \
    --width 38 --height 80 $P

pae tileset build ../$A/spec.json $P
pae map paint $M ../$A/grid.txt ../$A/legend.json --names ../$A/names.json --border ../$A/border.txt $P

# the joins stay where they were: Lavender's road (its columns 13-15) at the top edge, columns 10-13; Route 11's road
# (its rows 17-19) at the left edge, rows 44-47; Route 13's boardwalk (its columns 86-89) at the bottom, columns 21-24
pae map connect $M up LavenderTown_Frlg --offset -2 $P
pae map connect $M left Route11_Frlg --offset 27 $P
pae map connect $M down Route13_Frlg --offset -65 $P
[ -n "$KIT_BUILD_ALL" ] || pae seam build $M $P

# the doors that open: the gatehouse's front double door, the fishing house's
pae door add $M 11 13 --frames ../$B/route12_gate/route12_gate_door.png $P
pae door add $M 21 63 --frames ../$V/house_gardener/house_gardener_door.png $P

# events: the warps keep their numbers: the fishing house (0), the gatehouse's back doorway (1, 2) and its front door
# (3); the front door's right half is warp 4 (added: the door is two blocks wide)
pae map place $M warp 0 21 63 $P
pae map place $M warp 1 11 10 $P
pae map place $M warp 2 12 10 $P
pae map place $M warp 3 11 13 $P
pae map place $M object 0 12 24 $P   # Ned, fishing off Silence Bridge
pae map place $M object 1 15 30 $P   # Chip
pae map place $M object 2 12 35 $P   # Hank, looking down the bridge
pae map place $M object 3 15 37 $P   # Elliot
pae map place $M object 4 17 48 $P   # Snorlax, asleep in the neck south of the deck
pae map place $M object 5 22 45 $P   # Luca, pacing the deck
pae map place $M object 6 16 64 $P   # Justin, on the islet
pae map place $M object 7 22 74 $P   # Andrew, fishing off the bridge south
pae map place $M object 8 26 63 $P   # the two trees to cut, the pocket's way in
pae map place $M object 13 26 64 $P
pae map place $M object 9 24 41 $P   # TM48, on the deck
pae map place $M object 10 30 62 $P  # the Iron, in the pocket
pae map place $M object 11 20 42 $P  # Gia and Jes, the couple on the deck
pae map place $M object 12 20 41 $P
pae map place $M object 14 27 30 $P  # the Carvanha, swimming by the bridge
pae map place $M bg 0 14 14 $P       # the route sign, on the cliff top
pae map place $M bg 1 19 63 $P       # the fishing house's sign
pae map place $M bg 2 7 17 $P        # the Hyper Potion, hidden on the cliff top (by the hedge at the woods' edge)
pae map place $M bg 3 17 48 $P       # the Leftovers, under Snorlax
pae map place $M bg 4 31 65 $P       # the Rare Candy, hidden in the pocket
# the front door's right half (warp 4, to the gatehouse's other south door); everyone at the ground's elevation
python3 - <<'PY'
import json
p = "data/maps/Route12_Frlg/map.json"
m = json.load(open(p))
w = m["warp_events"]
if len(w) == 4:
    w.append(dict(w[3], x=12, y=13, dest_warp_id="3"))
assert (w[4]["x"], w[4]["y"], w[4]["dest_warp_id"]) == (12, 13, "3")
for e in m["object_events"]:
    if e.get("type") != "clone" and "elevation" in e:
        e["elevation"] = 3
open(p, "w").write(json.dumps(m, indent=2) + "\n")
PY
