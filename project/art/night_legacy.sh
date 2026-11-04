#!/bin/sh
# The lights at night of the maps not made from the kit (KR-102): Johto's towns and routes on the HeartGold/SoulSilver
# port's tilesets, and the Sevii Islands on FireRed's. Their tilesets aren't built from a spec, so their light colours
# (the palettes' .pla) and their copies of palettes are set here with pae, once; run it again after replacing one of
# these tilesets. Kit maps are in kit/night.py. Run from the repository root.
#
# The port already lights most of Johto's glass, lanterns and lamps (bank 3 colours 8 and 15 of every Johto primary:
# the windows and glass doors of every Center, Mart, Gym, gate and house). What it left dark, and what it got wrong:
set -e
cd engine
P="-p ."

# Johto: glass and screens still dark (each colour checked on every outdoor map of its tileset: nothing else uses it)
pae tileset lights gTileset_VioletCity_Hns 12:9,10,11 $P        # Sprout Tower's and the Trainer School's windows, screens
pae tileset lights gTileset_Ecruteak_City_Hns 10:11,12,13 $P    # the hall's and the Theater's (the same design)
pae tileset lights gTileset_AzaleaTown_Hns 8:6 $P               # the window of Kurt's annex
pae tileset lights gTileset_MtSilver_NewSinjoh_Hns 7:9,11,12 $P # New Sinjoh's big house: its window strip and screens
pae tileset lights gTileset_SafariZoneJohto_Hns 9:4,5,6 $P      # the Safari Zone gate's glass double door

# Goldenrod's bikes, on the rack outside the Bike Shop, were painted in the glass's lit blue (bank 3 colour 8): the same
# blue, unlit (colour 10), so their tyres and seats stop glowing
pae map recolour GoldenrodCity_hns --metatiles 0x3ee,0x3ef --bank 3 --colour 8 --to 10 $P

# the port's lantern and lamp lights were plain sprites, a yellow square over each lantern by day and night and one of
# the 16 objects the game shows at once: now the game's glows, after dark only (each keeps its local id and flag).
# Outdoors only: the Whirl Islands' are in a cave, which the game doesn't darken, so they stay as they are.
for m in VioletCity_hns EcruteakCity_hns GoldenrodCity_hns OlivineCity_hns BlackthornCity_hns SafariZoneGate_hns \
         NewSinjoh_hns SinjohRuins_hns NationalPark_Normal_hns NationalPark_BugContest_hns BellchimeTrail_hns \
         RuinsOfAlph_Outside_hns Route22_hns Route32_hns Route34_hns Route37_hns Route45_hns Route49_hns Route50_hns; do
    pae map lights $m --adopt OBJ_EVENT_GFX_SMALL_LIGHT_HNS $P
done

# The Sevii Islands: FireRed's houses and Pokémon Centers keep their window glass in the primary's bank 3, whose blues
# are also the Mart's roof and the ponds. Bank 7 is free in all three islands' tilesets: a copy of bank 3 there, the
# windows' tiles drawn with it, and only the copy lit; by day nothing changes.
for s in gTileset_SeviiIslands123 gTileset_SeviiIslands45 gTileset_SeviiIslands67; do
    pae tileset copy-bank gTileset_General_Frlg 3 $s 7 $P
done
# the lower half of each Pokémon Center window (tile 0x181; these blocks are only on Islands 2-7's Centers)
pae map rebank TwoIsland_Frlg --from 3 --to 7 --metatiles 0x58,0x59,0x5b,0x197 --tiles 0x181 $P
# the houses' windows (tiles 0x2a4 and 0x2a5 of each island's tileset; Four Island's 0x30e/0x30f: Selphy's house)
pae map rebank OneIsland_Frlg --from 3 --to 7 --metatiles 0x2ad,0x2ae --tiles 0x2a4,0x2a5 $P
pae map rebank FourIsland_Frlg --from 3 --to 7 --metatiles 0x29b,0x29c,0x30e,0x30f --tiles 0x2a4,0x2a5 $P
pae map rebank SixIsland_Frlg --from 3 --to 7 --metatiles 0x29b,0x29c --tiles 0x2a4,0x2a5 $P
pae tileset lights gTileset_General_Frlg 2:15 $P                # the upper half of each Center window
pae tileset lights gTileset_SeviiIslands123 7:11,12,13 11:8,9 10:15 $P  # windows; One Island's Network Center;
                                                                         # the Joyful Game Corner's bulbs
pae tileset lights gTileset_SeviiIslands45 7:11,12,13 9:14,15 $P # windows; Lorelei's house
pae tileset lights gTileset_SeviiIslands67 7:11,12,13 $P
