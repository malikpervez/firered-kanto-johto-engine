@ Johto (data/maps/BlackthornCity_Mart_hns/scripts.inc), as built into the FireRed game.

BlackthornCity_Mart_hns_MapScripts::
	.byte 0

BlackthornMart_EventScript_CoolTrainerM::
	msgbox BlackthornMart_Text_CooltrainerM, MSGBOX_NPC
	end

BlackthornMart_EventScript_BlackBelt::
	msgbox BlackthornMart_Text_BlackBelt, MSGBOX_NPC
	end

BlackthornMart_Text_CooltrainerM:
	.string "Yo{SE_M_DIVE}can'{SE_M_SPIT_UP}bu{SE_M_YAWN}MA{SE_M_LOCK_ON}REVIVE{SE_M_SUPERSONIC}bu{SE_M_SPIT_UP}it\n"
	.string "full{SE_M_YAWN}restore{SE_M_GRASSWHISTLE}{SE_M_CHARGE}fainte{SE_M_WATERFALL}POKéMON.\p"
	.string "Beware--i{SE_M_SPIT_UP}won'{SE_M_SPIT_UP}restor{SE_M_REVERSAL}PP{SE_M_SUPERSONIC}the\n"
	.string "POWE{SE_M_MINIMIZE}POINT{SE_M_SKETCH}neede{SE_M_WATERFALL}fo{SE_M_SAND_TOMB}moves.$"

BlackthornMart_Text_BlackBelt:
	.string "MA{SE_M_LOCK_ON}REPE{SE_M_BRICK_BREAK}keep{SE_M_GRASSWHISTLE}wea{SE_M_ENCORE2}POKéMO{SE_M_PSYBEAM2}away\n"
	.string "fro{SE_M_MILK_DRINK}you.\p"
	.string "It'{SE_M_GRASSWHISTLE}th{SE_M_REVERSAL}longes{SE_M_SPIT_UP}lastin{SE_M_SANDSTORM}o{SE_M_ACID_ARMOR}the\n"
	.string "REPE{SE_M_BRICK_BREAK}sprays.$"

