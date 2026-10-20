@ Johto (data/maps/VioletCity_Mart_hns/scripts.inc), as built into the FireRed game.

VioletCity_Mart_hns_MapScripts::
	.byte 0

VioletCity_Mart_EventScript_Clerk::
	lock
	faceplayer
	message J_gText_HowMayIServeYou
	waitmessage
	pokemart 0
	msgbox J_gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

VioletCity_Mart_EventScript_Granny::
	lock
	faceplayer
	msgbox VioletCity_Mart_Text_Granny, MSGBOX_DEFAULT
	closemessage
	release
	end

VioletCity_Mart_EventScript_Rocker::
	lock
	faceplayer
	msgbox VioletCity_Mart_Text_CooltrainerM, MSGBOX_DEFAULT
	closemessage
	release
	end

VioletCity_Mart_Text_Granny:
	.string "Whe{SE_M_ATTRACT}yo{SE_M_DIVE}firs{SE_M_SPIT_UP}catc{SE_M_TRI_ATTACK}{SE_M_CHARGE}POKéMON,\n"
	.string "i{SE_M_SPIT_UP}ma{SE_M_YAWN}b{SE_M_REVERSAL}weak.\p"
	.string "Bu{SE_M_SPIT_UP}i{SE_M_SPIT_UP}wil{SE_M_BATON_PASS}eventuall{SE_M_YAWN}gro{SE_M_TWISTER}to\n"
	.string "b{SE_M_REVERSAL}strong.\p"
	.string "It'{SE_M_GRASSWHISTLE}importan{SE_M_SPIT_UP}t{SE_M_ATTRACT2}trea{SE_M_SPIT_UP}POKéMON\n"
	.string "wit{SE_M_TRI_ATTACK}love.$"

VioletCity_Mart_Text_CooltrainerM:
	.string "POKéMO{SE_M_PSYBEAM2}ca{SE_M_ATTRACT}hol{SE_M_WATERFALL}item{SE_M_GRASSWHISTLE}like\n"
	.string "POTIO{SE_M_PSYBEAM2}an{SE_M_WATERFALL}ANTIDOTE.\p"
	.string "Bu{SE_M_SPIT_UP}the{SE_M_YAWN}don'{SE_M_SPIT_UP}appea{SE_M_SAND_TOMB}t{SE_M_ATTRACT2}know\n"
	.string "ho{SE_M_TWISTER}t{SE_M_ATTRACT2}us{SE_M_REVERSAL}man-mad{SE_M_REVERSAL}items.$"

