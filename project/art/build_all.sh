#!/bin/sh
# Rebuild every map made from the kit (project/art/kit), after a change to the kit or to any of them. The maps
# share the kit's primary tileset, so each map's build makes it again (the same each time) and the seams between
# them are made last, when every map is painted. Run from the repository root.
set -e
export KIT_BUILD_ALL=1  # the maps' own builds leave the seams to the end
sh project/art/route1-concept/build.sh
sh project/art/pallet-concept/build.sh
sh project/art/viridian-concept/build.sh
cd engine
for m in Route1_Frlg PalletTown_Frlg; do
    pae seam build $m -p .
done
# Route 22 (not rebuilt yet) has no room for Viridian's strip: it gets its seams when it's rebuilt from the kit
pae seam build ViridianCity_Frlg -p . --skip Route22_Frlg
