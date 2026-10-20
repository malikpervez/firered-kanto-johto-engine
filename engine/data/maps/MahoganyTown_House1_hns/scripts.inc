@ Johto (data/maps/MahoganyTown_House1_hns/scripts.inc), as built into the FireRed game.

MahoganyTown_House1_hns_MapScripts::
	.byte 0

MahoganyTown_House1_EventScript_BlackBelt::
	msgbox MahoganyRedGyaradosHouse_Text_BlackBelt, MSGBOX_NPC
	end

MahoganyTown_House1_EventScript_Teacher::
	goto_if_lt JOHTO_VAR_GOLDENROD_CITY_STATE, 6, MahoganyTown_House1_EventScript_TeacherBeforeAfter
	goto_if_lt JOHTO_VAR_GOLDENROD_CITY_STATE, 10, MahoganyTown_House1_EventScript_TeacherDuring

MahoganyTown_House1_EventScript_TeacherBeforeAfter::
	msgbox MahoganyRedGyaradosHouse_Text_Teacher, MSGBOX_NPC
	end

MahoganyTown_House1_EventScript_TeacherDuring::
	msgbox MahoganyRedGyaradosHouse_Text_Teacher_Rockets, MSGBOX_NPC
	end

MahoganyRedGyaradosHouse_Text_BlackBelt:
	.string "{SE_M_HEAL_BELL}hear{SE_M_WATERFALL}tha{SE_M_SPIT_UP}{SE_M_CHARGE}re{SE_M_WATERFALL}GYARADO{SE_M_SKETCH}appeared\n"
	.string "a{SE_M_SPIT_UP}th{SE_M_REVERSAL}LAKE.\p"
	.string "That'{SE_M_GRASSWHISTLE}odd{SE_M_SUPERSONIC}sinc{SE_M_REVERSAL}eve{SE_M_ATTRACT}ordinary\n"
	.string "GYARADO{SE_M_SKETCH}ar{SE_M_REVERSAL}rar{SE_M_REVERSAL}i{SE_M_ATTRACT}tha{SE_M_SPIT_UP}lake…$"

MahoganyRedGyaradosHouse_Text_Teacher:
	.string "M{SE_M_YAWN}favorit{SE_M_REVERSAL}radi{SE_M_ATTRACT2}program{SE_M_SING}I'{SE_M_WATERFALL}say\n"
	.string "POKéMO{SE_M_PSYBEAM2}MUSIC.$"

MahoganyRedGyaradosHouse_Text_Teacher_Rockets:
	.string "I'v{SE_M_REVERSAL}bee{SE_M_ATTRACT}hearin{SE_M_SANDSTORM}laughte{SE_M_SAND_TOMB}o{SE_M_ATTRACT}the\n"
	.string "radio…\p"
	.string "It'{SE_M_GRASSWHISTLE}creepy.$"

