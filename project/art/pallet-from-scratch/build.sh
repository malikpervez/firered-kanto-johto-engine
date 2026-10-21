#!/bin/sh
# Rebuild Pallet Town from the art: draw, build the tilesets, paint the map, then the parts derived from the art
# (connection seams, door animations). Run from the repository root.
set -e
A=project/art/pallet-from-scratch
python3 $A/make_art.py
cd engine
pae tileset build ../$A/spec.json -p .
pae map paint PalletTown_Frlg ../$A/grid.txt ../$A/legend.json --names ../$A/names.json --border ../$A/border.txt -p .
pae seam build PalletTown_Frlg -p .
pae door add PalletTown_Frlg 6 7 --panel 3,0,13,14 -p .    # the houses' door (both houses share it)
pae door add PalletTown_Frlg 16 13 --panel 2,1,14,15 -p .  # Oak's lab
