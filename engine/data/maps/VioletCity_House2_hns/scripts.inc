@ Johto (data/maps/VioletCity_House2_hns/scripts.inc), as built into the FireRed game.

VioletCity_House2_hns_MapScripts::
	.byte 0

VioletCity_House2_EventScript_Lass::
	lock
	faceplayer
	msgbox VioletCity_NicknameHouse_Text_Lass, MSGBOX_DEFAULT
	closemessage
	release
	end

VioletCity_House2_EventScript_Teacher::
	lock
	faceplayer
	msgbox VioletCity_NicknameHouse_Text_Teacher, MSGBOX_DEFAULT
	closemessage
	release
	end

VioletCity_House2_EventScript_Pidgey::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_PIDGEY, CRY_MODE_NORMAL
	msgbox VioletCity_NicknameHouse_Text_Bird, MSGBOX_DEFAULT
	waitmoncry
	release
	end

VioletCity_NicknameHouse_Text_Teacher:
	.string "Sh{SE_M_REVERSAL}use{SE_M_GRASSWHISTLE}th{SE_M_REVERSAL}name{SE_M_GRASSWHISTLE}o{SE_M_ACID_ARMOR}her\n"
	.string "favorit{SE_M_REVERSAL}thing{SE_M_GRASSWHISTLE}t{SE_M_ATTRACT2}eat.\p"
	.string "Fo{SE_M_SAND_TOMB}th{SE_M_REVERSAL}nickname{SE_M_GRASSWHISTLE}sh{SE_M_REVERSAL}give{SE_M_GRASSWHISTLE}to\n"
	.string "he{SE_M_SAND_TOMB}POKéMON{SE_M_SUPERSONIC}{SE_M_HEAL_BELL}mean.$"

VioletCity_NicknameHouse_Text_Lass:
	.string "{SE_M_HEAL_BELL}cal{SE_M_BATON_PASS}m{SE_M_YAWN}PIDGE{SE_M_MOONLIGHT}STRAWBERRY!$"

VioletCity_NicknameHouse_Text_Bird:
	.string "STRAWBERRY{SE_M_HEAT_WAVE}Pijji!$"

