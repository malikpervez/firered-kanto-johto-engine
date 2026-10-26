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
sh project/art/route25-concept/build.sh
sh project/art/route5-concept/build.sh
sh project/art/route6-concept/build.sh
sh project/art/vermilion-concept/build.sh
sh project/art/route11-concept/build.sh
sh project/art/route9-concept/build.sh
sh project/art/route10-concept/build.sh
sh project/art/lavender-concept/build.sh
sh project/art/route8-concept/build.sh
sh project/art/route7-concept/build.sh
sh project/art/celadon-concept/build.sh
cd engine
for m in Route1_Frlg PalletTown_Frlg ViridianCity_Frlg Route22_Frlg Route2_Frlg PewterCity_Frlg Route3_Frlg Route4_Frlg \
        CeruleanCity_Frlg Route24_Frlg Route25_Frlg VermilionCity_Frlg Route11_Frlg \
        Route9_Frlg Route10_Frlg LavenderTown_Frlg CeladonCity_Frlg; do
    pae seam build $m -p .
done
for m in Route5_Frlg Route6_Frlg Route8_Frlg Route7_Frlg; do  # (no room in old Saffron: see their build.sh)
    pae seam build $m --skip SaffronCity_Connection_Frlg -p .
done
