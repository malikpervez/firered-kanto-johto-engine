@ Johto (data/maps/BlackthornCity_House1_hns/scripts.inc), as built into the FireRed game.

BlackthornCity_House1_hns_MapScripts::
	.byte 0

BlackthornCity_House1EventScript_Granny::
	msgbox BlackthornCity_House1_Text_Granny, MSGBOX_NPC
	end

BlackthornCity_House1EventScript_Dratini::
	lock
	faceplayer
	waitse
	playmoncry 147, 0
	msgbox BlackthornCity_House1_Text_Dratini, MSGBOX_DEFAULT
	waitmoncry
	release
	end

BlackthornCity_House1_Text_Granny:
	.string "{SE_M_BONEMERANG}cla{SE_M_ATTRACT}o{SE_M_ACID_ARMOR}trainer{SE_M_GRASSWHISTLE}wh{SE_M_ATTRACT2}ca{SE_M_ATTRACT}freely\n"
	.string "comman{SE_M_WATERFALL}dragon{SE_M_GRASSWHISTLE}liv{SE_M_REVERSAL}righ{SE_M_SPIT_UP}her{SE_M_REVERSAL}in\l"
	.string "BLACKTHORN.\p"
	.string "A{SE_M_GRASSWHISTLE}{SE_M_CHARGE}result{SE_M_SUPERSONIC}ther{SE_M_REVERSAL}ar{SE_M_REVERSAL}man{SE_M_YAWN}legends\n"
	.string "abou{SE_M_SPIT_UP}dragon{SE_M_GRASSWHISTLE}i{SE_M_ATTRACT}thi{SE_M_GRASSWHISTLE}town.$"

BlackthornCity_House1_Text_Dratini:
	.string "DRATINI{SE_M_HEAT_WAVE}Draa!$"

