@ Johto (data/maps/CliffEdgeCave_hns/scripts.inc), as built into the FireRed game.

CliffEdgeCave_hns_MapScripts::
	.byte 0

CliffEdgeCave_EventScript_BaldMan::
	lock
	faceplayer
	msgbox CliffEdgeCave_Text_Baldman, MSGBOX_DEFAULT
	closemessage
	release
	end

CliffEdgeCave_Text_Baldman:
	.string "I{SE_M_ACID_ARMOR}yo{SE_M_DIVE}se{SE_M_REVERSAL}{SE_M_CHARGE}for{SE_M_ENCORE2}i{SE_M_ATTRACT}th{SE_M_REVERSAL}road\n"
	.string "insid{SE_M_REVERSAL}{SE_M_CHARGE}cave{SE_M_SUPERSONIC}mos{SE_M_SPIT_UP}likel{SE_M_YAWN}one\l"
	.string "wa{SE_M_YAWN}i{SE_M_GRASSWHISTLE}righ{SE_M_SPIT_UP}an{SE_M_WATERFALL}th{SE_M_REVERSAL}othe{SE_M_SAND_TOMB}leads\l"
	.string "t{SE_M_ATTRACT2}{SE_M_CHARGE}dea{SE_M_WATERFALL}end.\p"
	.string "Bu{SE_M_SPIT_UP}peopl{SE_M_REVERSAL}can'{SE_M_SPIT_UP}hel{SE_M_MORNING_SUN}tryin{SE_M_SANDSTORM}both.$"

