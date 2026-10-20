@ Johto (data/maps/SSAqua_RoomSSW_hns/scripts.inc), as built into the FireRed game.

SSAqua_RoomSSW_hns_MapScripts::
	.byte 0

SSAqua_RoomSSW_EventScript_Lyle::
	trainerbattle_single 1319, SSAqua_RoomSSW_Text_FirebreatherLyleSeen, SSAqua_RoomSSW_Text_FirebreatherLyleBeaten
	msgbox SSAqua_RoomSSW_Text_FirebreatherLyleAfterBattle, MSGBOX_AUTOCLOSE
	end

SSAqua_RoomSSW_EventScript_Ken::
	trainerbattle_single 1197, SSAqua_RoomSSW_Text_BugCatcherKenSeen, SSAqua_RoomSSW_Text_BugCatcherKenBeaten
	msgbox SSAqua_RoomSSW_Text_BugCatcherKenAfterBattle, MSGBOX_AUTOCLOSE
	end

SSAqua_RoomSSW_Text_FirebreatherLyleSeen:
	.string "I'{SE_M_MILK_DRINK}goin{SE_M_SANDSTORM}t{SE_M_ATTRACT2}KANT{SE_M_SOLAR_BEAM}t{SE_M_ATTRACT2}put\n"
	.string "o{SE_M_ATTRACT}fire-breathin{SE_M_SANDSTORM}shows!$"

SSAqua_RoomSSW_Text_FirebreatherLyleBeaten:
	.string "Fizzle{SE_M_DIZZY_PUNCH}Th{SE_M_REVERSAL}flame'{SE_M_GRASSWHISTLE}tiny…$"

SSAqua_RoomSSW_Text_FirebreatherLyleAfterBattle:
	.string "{SE_M_HEAL_BELL}gues{SE_M_GRASSWHISTLE}fir{SE_M_REVERSAL}i{SE_M_GRASSWHISTLE}wea{SE_M_ENCORE2}o{SE_M_ATTRACT}th{SE_M_REVERSAL}sea.\n"
	.string "I{SE_M_SPIT_UP}doesn'{SE_M_SPIT_UP}matter{SE_M_SING}Really?$"

SSAqua_RoomSSW_Text_BugCatcherKenSeen:
	.string "I'{SE_M_MILK_DRINK}visitin{SE_M_SANDSTORM}m{SE_M_YAWN}grandm{SE_M_CHARGE}to\n"
	.string "catc{SE_M_TRI_ATTACK}m{SE_M_REVERSAL}som{SE_M_REVERSAL}bugs!$"

SSAqua_RoomSSW_Text_BugCatcherKenBeaten:
	.string "Ooh{SE_M_SUPERSONIC}wow{SE_M_PERISH_SONG}You'r{SE_M_REVERSAL}tough!$"

SSAqua_RoomSSW_Text_BugCatcherKenAfterBattle:
	.string "Yo{SE_M_DIVE}ca{SE_M_ATTRACT}fin{SE_M_WATERFALL}lot{SE_M_GRASSWHISTLE}o{SE_M_ACID_ARMOR}POKéMON\n"
	.string "i{SE_M_ATTRACT}th{SE_M_REVERSAL}tree{SE_M_GRASSWHISTLE}o{SE_M_ACID_ARMOR}JOHTO!$"

