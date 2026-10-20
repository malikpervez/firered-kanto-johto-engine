@ Johto (data/maps/Route30_House_hns/scripts.inc), as built into the FireRed game.

Route30_House_hns_MapScripts::
	.byte 0

Route30_House_EventScript_BaldMan::
	lock
	faceplayer
	goto_if_set 8722, Route30_House_EventScript_BaldMan2
	msgbox Route30_BerryHouse_Text_MonEatBerries, MSGBOX_DEFAULT
	giveitem ITEM_CHERI_BERRY
	goto_if_eq 32781, FALSE, J_Common_EventScript_ShowBagIsFull
	closemessage
	setflag 8722

Route30_House_EventScript_BaldMan2::
	msgbox Route30_BerryHouse_Text_CheckTrees, MSGBOX_DEFAULT
	closemessage
	release
	end

Route30_BerryHouse_Text_MonEatBerries:
	.string "Whe{SE_M_ATTRACT}yo{SE_M_DIVE}follo{SE_M_TWISTER}tha{SE_M_SPIT_UP}pat{SE_M_TRI_ATTACK}u{SE_M_MORNING_SUN}north,\n"
	.string "yo{SE_M_DIVE}wil{SE_M_BATON_PASS}se{SE_M_REVERSAL}MR{SE_M_PERISH_SONG}POKéMON'{SE_M_GRASSWHISTLE}house.\p"
	.string "Bu{SE_M_SPIT_UP}befor{SE_M_REVERSAL}yo{SE_M_DIVE}go{SE_M_SUPERSONIC}allo{SE_M_TWISTER}m{SE_M_REVERSAL}to\n"
	.string "tel{SE_M_BATON_PASS}yo{SE_M_DIVE}abou{SE_M_SPIT_UP}BERRIES!\p"
	.string "POKéMO{SE_M_PSYBEAM2}ge{SE_M_SPIT_UP}healthie{SE_M_SAND_TOMB}b{SE_M_YAWN}eating\n"
	.string "BERRIES.\p"
	.string "The{SE_M_YAWN}ca{SE_M_ATTRACT}eve{SE_M_ATTRACT}ea{SE_M_SPIT_UP}BERRIES\n"
	.string "they'r{SE_M_REVERSAL}holdin{SE_M_SANDSTORM}i{SE_M_ATTRACT}battle.\p"
	.string "BERRIE{SE_M_SKETCH}ca{SE_M_ATTRACT}als{SE_M_ATTRACT2}b{SE_M_REVERSAL}turne{SE_M_WATERFALL}into\n"
	.string "BALL{SE_M_SKETCH}b{SE_M_YAWN}KUR{SE_M_SWIFT}i{SE_M_ATTRACT}AZALE{SE_M_BONEMERANG}TOWN.\p"
	.string "Here{SE_M_PERISH_SONG}I'l{SE_M_BATON_PASS}shar{SE_M_REVERSAL}on{SE_M_REVERSAL}wit{SE_M_TRI_ATTACK}you!$"

Route30_BerryHouse_Text_CheckTrees:
	.string "Chec{SE_M_ENCORE2}tree{SE_M_GRASSWHISTLE}fo{SE_M_SAND_TOMB}BERRIES.\n"
	.string "The{SE_M_YAWN}gro{SE_M_TWISTER}bac{SE_M_ENCORE2}afte{SE_M_SAND_TOMB}{SE_M_CHARGE}fe{SE_M_TWISTER}hours.$"

