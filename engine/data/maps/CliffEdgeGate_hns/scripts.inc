@ Johto (data/maps/CliffEdgeGate_hns/scripts.inc), as built into the FireRed game.

CliffEdgeGate_hns_MapScripts::
	.byte 0

CliffEdgeGate_EventScript_Woman::
	lock
	faceplayer
	msgbox CliffEdgeGate_Text_IntroOpen, MSGBOX_DEFAULT
	closemessage
	release
	end

CliffEdgeGate_EventScript_Picnicker::
	lock
	faceplayer
	msgbox CliffEdgeGate_Text_Expectations, MSGBOX_DEFAULT
	closemessage
	release
	end

CliffEdgeGate_Text_IntroOpen:
	.string "Di{SE_M_WATERFALL}yo{SE_M_DIVE}know{SE_M_SING}There'{SE_M_GRASSWHISTLE}{SE_M_CHARGE}SAFAR{SE_M_HEAL_BELL}ZONE\n"
	.string "jus{SE_M_SPIT_UP}aroun{SE_M_WATERFALL}th{SE_M_REVERSAL}corner.\p"
	.string "It'{SE_M_GRASSWHISTLE}reall{SE_M_YAWN}fun!\n"
	.string "Yo{SE_M_DIVE}wil{SE_M_BATON_PASS}se{SE_M_REVERSAL}man{SE_M_YAWN}differen{SE_M_SPIT_UP}kind{SE_M_GRASSWHISTLE}of\l"
	.string "POKéMON{SE_M_SUPERSONIC}an{SE_M_WATERFALL}it'{SE_M_GRASSWHISTLE}al{SE_M_BATON_PASS}yo{SE_M_DIVE}ca{SE_M_ATTRACT}catch!\p"
	.string "Ther{SE_M_REVERSAL}i{SE_M_GRASSWHISTLE}n{SE_M_ATTRACT2}reaso{SE_M_ATTRACT}no{SE_M_SPIT_UP}t{SE_M_ATTRACT2}go{SE_M_SUPERSONIC}right?\n"
	.string "Jus{SE_M_SPIT_UP}aroun{SE_M_WATERFALL}th{SE_M_REVERSAL}corner.$"

CliffEdgeGate_Text_Expectations:
	.string "{SE_M_HEAL_BELL}appreciat{SE_M_REVERSAL}tha{SE_M_SPIT_UP}everybod{SE_M_YAWN}i{SE_M_GRASSWHISTLE}looking\n"
	.string "forwar{SE_M_WATERFALL}t{SE_M_ATTRACT2}it.\p"
	.string "Bu{SE_M_SPIT_UP}th{SE_M_REVERSAL}lad{SE_M_YAWN}a{SE_M_SPIT_UP}th{SE_M_REVERSAL}receptio{SE_M_ATTRACT}seems\n"
	.string "{SE_M_CHARGE}bi{SE_M_SPIT_UP}to{SE_M_ATTRACT2}dramatic...\p"
	.string "Don'{SE_M_SPIT_UP}ge{SE_M_SPIT_UP}you{SE_M_SAND_TOMB}expectation{SE_M_GRASSWHISTLE}to{SE_M_ATTRACT2}high!$"

CliffEdgeGate_EventScript_CaveSign::
	lock
	msgbox CliffEdgeGate_Text_SignOpen, MSGBOX_SIGN
	closemessage
	release
	end

CliffEdgeGate_Text_SignOpen:
	.string "Everythin{SE_M_SANDSTORM}I{SE_M_GRASSWHISTLE}Thrilling!\n"
	.string "Explor{SE_M_REVERSAL}t{SE_M_ATTRACT2}Fin{SE_M_WATERFALL}Wil{SE_M_WATERFALL}POKéMON!\l"
	.string "Warde{SE_M_ATTRACT}BAOBA'{SE_M_GRASSWHISTLE}SAFAR{SE_M_HEAL_BELL}ZONE\l"
	.string "U{SE_M_MORNING_SUN}an{SE_M_WATERFALL}Running!$"

