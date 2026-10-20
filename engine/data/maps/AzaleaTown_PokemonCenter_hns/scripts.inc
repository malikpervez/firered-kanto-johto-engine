@ Johto (data/maps/AzaleaTown_PokemonCenter_hns/scripts.inc), as built into the FireRed game.

AzaleaTown_PokemonCenter_hns_MapScripts::
	map_script 3, AzaleaTown_Pokecenter_OnTransition
	.byte 0

AzaleaTown_Pokecenter_OnTransition::
	setrespawn 131
	end

AzaleaPokeCenter_EventScript_Gentleman::
	lock
	faceplayer
	msgbox AzaleaPokecenter_Text_Gentleman, MSGBOX_DEFAULT
	closemessage
	release
	end

AzaleaPokeCenter_EventScript_Fisher::
	lock
	faceplayer
	msgbox AzaleaPokecenter_Text_FishingGuru, MSGBOX_DEFAULT
	closemessage
	release
	end

AzaleaPokeCenter_EventScript_PokefanF::
	lock
	faceplayer
	msgbox AzaleaPokecenter_Text_PokefanF, MSGBOX_DEFAULT
	closemessage
	release
	end

AzaleaPokecenter_Text_Gentleman:
	.string "D{SE_M_ATTRACT2}you{SE_M_SAND_TOMB}POKéMO{SE_M_PSYBEAM2}kno{SE_M_TWISTER}H{SE_M_GIGA_DRAIN}moves?\p"
	.string "Thos{SE_M_REVERSAL}move{SE_M_GRASSWHISTLE}ca{SE_M_ATTRACT}b{SE_M_REVERSAL}use{SE_M_WATERFALL}eve{SE_M_ATTRACT}if\n"
	.string "you{SE_M_SAND_TOMB}POKéMO{SE_M_PSYBEAM2}ha{SE_M_GRASSWHISTLE}fainted.$"

AzaleaPokecenter_Text_UnusedPCExplanation:
	.string "Thi{SE_M_GRASSWHISTLE}BIL{SE_M_BRICK_BREAK}gu{SE_M_YAWN}create{SE_M_WATERFALL}th{SE_M_REVERSAL}system\n"
	.string "fo{SE_M_SAND_TOMB}storin{SE_M_SANDSTORM}POKéMO{SE_M_PSYBEAM2}i{SE_M_ATTRACT}{SE_M_CHARGE}PC.\p"
	.string "BILL'{SE_M_GRASSWHISTLE}P{SE_M_PSYBEAM}ca{SE_M_ATTRACT}stor{SE_M_REVERSAL}u{SE_M_MORNING_SUN}t{SE_M_ATTRACT2}30\n"
	.string "POKéMO{SE_M_PSYBEAM2}pe{SE_M_SAND_TOMB}BOX.$"

AzaleaPokecenter_Text_FishingGuru:
	.string "BILL'{SE_M_GRASSWHISTLE}P{SE_M_PSYBEAM}ca{SE_M_ATTRACT}stor{SE_M_REVERSAL}u{SE_M_MORNING_SUN}t{SE_M_ATTRACT2}30\n"
	.string "POKéMO{SE_M_PSYBEAM2}pe{SE_M_SAND_TOMB}BOX.$"

AzaleaPokecenter_Text_PokefanF:
	.string "D{SE_M_ATTRACT2}yo{SE_M_DIVE}kno{SE_M_TWISTER}abou{SE_M_SPIT_UP}BERRIES?\p"
	.string "Crac{SE_M_ENCORE2}on{SE_M_REVERSAL}open{SE_M_SUPERSONIC}hollo{SE_M_TWISTER}i{SE_M_SPIT_UP}ou{SE_M_SPIT_UP}and\n"
	.string "fi{SE_M_SPIT_UP}i{SE_M_SPIT_UP}wit{SE_M_TRI_ATTACK}{SE_M_CHARGE}specia{SE_M_BATON_PASS}device.\p"
	.string "The{SE_M_ATTRACT}yo{SE_M_DIVE}ca{SE_M_ATTRACT}catc{SE_M_TRI_ATTACK}POKéMO{SE_M_PSYBEAM2}wit{SE_M_TRI_ATTACK}it.\p"
	.string "Befor{SE_M_REVERSAL}POK{SE_U}BALL{SE_M_SKETCH}wer{SE_M_REVERSAL}invented,\n"
	.string "everyon{SE_M_REVERSAL}use{SE_M_WATERFALL}BERRIES.$"

