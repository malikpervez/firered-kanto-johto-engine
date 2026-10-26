#!/bin/sh
# Rebuild every map made from the kit (project/art/kit), after a change to the kit or to any of them. The maps
# share the kit's primary tileset, so each map's build makes it again (the same each time) and the seams between
# them are made last, when every map is painted. Run from the repository root.
set -e
export KIT_BUILD_ALL=1  # the maps' own builds leave the seams to the end
sh project/art/route1-concept/build.sh
sh project/art/pallet-concept/build.sh
sh project/art/viridian-concept/build.sh
sh project/art/route22-concept/build.sh
sh project/art/route2-concept/build.sh
sh project/art/viridianforest-concept/build.sh  # no joins, so no seams
sh project/art/pewter-concept/build.sh
python3 project/art/pewter-concept/escort.py  # the guides' walks, on the map as built
sh project/art/route3-concept/build.sh
sh project/art/route4-concept/build.sh
sh project/art/cerulean-concept/build.sh
sh project/art/route24-concept/build.sh
cd engine
for m in Route1_Frlg PalletTown_Frlg ViridianCity_Frlg Route22_Frlg Route2_Frlg PewterCity_Frlg Route3_Frlg Route4_Frlg \
        CeruleanCity_Frlg Route24_Frlg; do
    pae seam build $m -p .
done
