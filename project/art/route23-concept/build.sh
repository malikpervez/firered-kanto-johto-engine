#!/bin/sh
# Rebuild Route 23 from its concept with pae: lay out the plan, build the tileset (the kit's primary, its cliffs,
# Route 2's cave mouth and Route 12's north gatehouse), paint the map, keep its join to Indigo Plateau and join Route 22
# again, make the seams, put the events where the new route has them. Run from the repository root
# (project/art/build_all.sh rebuilds every map).
set -e
A=project/art/route23-concept
python3 $A/make_art.py
cd engine
P="-p ."
M=Route23_Frlg

# the tileset and the block files (the first time); the old route's layout wasn't in the kit's (HnS's) format
grep -q "gTileset_Route23Concept =" src/data/tilesets/headers.h || pae tileset new gTileset_Route23Concept --secondary $P
pae map geometry $M --primary gTileset_PalletConcept_General --secondary gTileset_Route23Concept \
    --blockdata data/layouts/Route23_Concept/map.bin --border data/layouts/Route23_Concept/border.bin \
    --version hns --width 24 --height 160 $P

pae tileset build ../$A/spec.json $P
pae map paint $M ../$A/grid.txt ../$A/legend.json --names ../$A/names.json --border ../$A/border.txt $P

# the joins: Indigo Plateau's road at the top (offset 0, as before); Route 22's woods below (joined again: both are
# the kit's now, and its woods meet Route 23's)
pae map connect $M up IndigoPlateau_Exterior_Frlg --offset 0 $P
pae map connect Route22_Frlg up $M --offset 0 $P
[ -n "$KIT_BUILD_ALL" ] || pae seam build $M $P

# events: every warp keeps its number (Victory Road's way in 0 and way out 1; the League gate's doorway 2 and 3)
pae map place $M warp 0 6 29 $P
pae map place $M warp 1 14 29 $P
pae map place $M warp 2 9 156 $P
pae map place $M warp 3 10 156 $P
# the badge guards keep their order (the scripts find them by local id), each in his gate's east column
pae map place $M object 0 11 140 $P  # Cascade
pae map place $M object 1 11 122 $P  # Thunder
pae map place $M object 2 11 104 $P  # Rainbow
pae map place $M object 3 11 86 $P   # Soul
pae map place $M object 4 11 58 $P   # Marsh
pae map place $M object 5 11 48 $P   # Volcano
pae map place $M object 6 7 38 $P    # Earth
# the gates' triggers: the old route's 42, six to each gate now (they were 5 to 10), each with its gate's script and
# the step of the road it checks (VAR_MAP_SCENE_ROUTE23, 1 for Cascade's to 7 for Earth's, as before): the three
# blocks beside the guard, on his row and the next. (pae map place moves an event; its script and step are set here)
python3 - <<'PY'
import json
gates = [(8, 138), (8, 120), (8, 102), (8, 84), (8, 56), (8, 46), (4, 36)]
badges = ["Cascade", "Thunder", "Rainbow", "Soul", "Marsh", "Volcano", "Earth"]
p = "data/maps/Route23_Frlg/map.json"
m = json.load(open(p))
old = m["coord_events"]
assert len(old) == 42
new = []
for i, ((x0, y0), badge) in enumerate(zip(gates, badges)):
    for r in (0, 1):
        for k in range(3):
            e = dict(old[len(new)])
            e.update({"x": x0 + k, "y": y0 + 2 + r, "elevation": 3, "var": "VAR_MAP_SCENE_ROUTE23",
                      "var_value": str(i + 1), "script": f"Route23_EventScript_{badge}BadgeGuardTrigger"})
            new.append(e)
m["coord_events"] = new
open(p, "w").write(json.dumps(m, indent=2) + "\n")
PY
pae map place $M bg 0 20 128 $P      # the hidden items: the Full Restore...
pae map place $M bg 1 2 110 $P       # ...the Ultra Ball...
pae map place $M bg 2 21 92 $P       # ...the Max Ether...
pae map place $M bg 3 2 63 $P        # ...the berries, on the lake's north shore...
pae map place $M bg 4 21 64 $P
pae map place $M bg 5 2 53 $P        # ...and in the meadows above it...
pae map place $M bg 6 21 43 $P
pae map place $M bg 7 3 5 $P         # ...the Max Elixir, on the cliff top
pae map place $M bg 8 3 30 $P        # Victory Road's sign
python3 - <<'PY'
import json
p = "data/maps/Route23_Frlg/map.json"
m = json.load(open(p))
for e in m["object_events"]:
    e["elevation"] = 3
open(p, "w").write(json.dumps(m, indent=2) + "\n")
PY
