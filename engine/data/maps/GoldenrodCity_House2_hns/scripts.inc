@ Johto (data/maps/GoldenrodCity_House2_hns/scripts.inc), as built into the FireRed game.

GoldenrodCity_House2_hns_MapScripts::
	.byte 0

GoldenrodCity_House2_EventScript_Man::
	faceplayer
	lock
	msgbox GoldenrodPPSpeechHouse_Text_Man, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_House2_EventScript_Woman::
	faceplayer
	lock
	msgbox GoldenrodPPSpeechHouse_Text_Lass, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodPPSpeechHouse_Text_Man:
	.string "Onc{SE_M_REVERSAL}whil{SE_M_REVERSAL}{SE_M_HEAL_BELL}wa{SE_M_GRASSWHISTLE}battling{SE_M_SUPERSONIC}my\n"
	.string "POKéMO{SE_M_PSYBEAM2}couldn'{SE_M_SPIT_UP}mak{SE_M_REVERSAL}an{SE_M_YAWN}moves.\p"
	.string "Th{SE_M_REVERSAL}POWE{SE_M_MINIMIZE}POINTS{SE_M_SUPERSONIC}o{SE_M_SAND_TOMB}PP{SE_M_SUPERSONIC}o{SE_M_ACID_ARMOR}its\n"
	.string "move{SE_M_GRASSWHISTLE}wer{SE_M_REVERSAL}al{SE_M_BATON_PASS}gone.$"

GoldenrodPPSpeechHouse_Text_Lass:
	.string "Sometimes{SE_M_SUPERSONIC}{SE_M_CHARGE}health{SE_M_YAWN}POKéMO{SE_M_PSYBEAM2}ma{SE_M_YAWN}be\n"
	.string "unabl{SE_M_REVERSAL}t{SE_M_ATTRACT2}us{SE_M_REVERSAL}it{SE_M_GRASSWHISTLE}moves.\p"
	.string "I{SE_M_ACID_ARMOR}tha{SE_M_SPIT_UP}happens{SE_M_SUPERSONIC}hea{SE_M_BATON_PASS}i{SE_M_SPIT_UP}a{SE_M_SPIT_UP}a\n"
	.string "POKéMO{SE_M_PSYBEAM2}CENTE{SE_M_MINIMIZE}o{SE_M_SAND_TOMB}us{SE_M_REVERSAL}a{SE_M_ATTRACT}item.$"

