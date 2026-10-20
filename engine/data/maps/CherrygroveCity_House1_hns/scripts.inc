@ Johto (data/maps/CherrygroveCity_House1_hns/scripts.inc), as built into the FireRed game.

CherrygroveCity_House1_hns_MapScripts::
	.byte 0

CherrygroveCity_House1_EventScript_Baldingman::
	lock
	faceplayer
	msgbox CherrygroveCity_GymSpeechHouse_Text_PokefanM, MSGBOX_DEFAULT
	closemessage
	release
	end

CherrygroveCity_House1_EventScript_Kid::
	lock
	faceplayer
	msgbox CherrygroveCity_GymSpeechHouse_Text_BugCatcher, MSGBOX_DEFAULT
	closemessage
	release
	end

CherrygroveCity_GymSpeechHouse_Text_PokefanM:
	.string "You'r{SE_M_REVERSAL}tryin{SE_M_SANDSTORM}t{SE_M_ATTRACT2}se{SE_M_REVERSAL}ho{SE_M_TWISTER}good\n"
	.string "yo{SE_M_DIVE}ar{SE_M_REVERSAL}a{SE_M_GRASSWHISTLE}{SE_M_CHARGE}POKéMO{SE_M_PSYBEAM2}trainer?\p"
	.string "Yo{SE_M_DIVE}bette{SE_M_SAND_TOMB}visi{SE_M_SPIT_UP}th{SE_M_REVERSAL}POKéMON\n"
	.string "GYM{SE_M_SKETCH}al{SE_M_BATON_PASS}ove{SE_M_SAND_TOMB}JOHT{SE_M_SOLAR_BEAM}an{SE_M_WATERFALL}collect\l"
	.string "BADGES.$"

CherrygroveCity_GymSpeechHouse_Text_BugCatcher:
	.string "Whe{SE_M_ATTRACT}{SE_M_HEAL_BELL}ge{SE_M_SPIT_UP}older{SE_M_SUPERSONIC}I'{SE_M_MILK_DRINK}goin{SE_M_SANDSTORM}to\n"
	.string "b{SE_M_REVERSAL}{SE_M_CHARGE}GY{SE_M_GIGA_DRAIN}LEADER!\p"
	.string "{SE_M_HEAL_BELL}mak{SE_M_REVERSAL}m{SE_M_YAWN}POKéMO{SE_M_PSYBEAM2}battl{SE_M_REVERSAL}with\n"
	.string "m{SE_M_YAWN}friend'{SE_M_GRASSWHISTLE}t{SE_M_ATTRACT2}mak{SE_M_REVERSAL}them\l"
	.string "tougher!$"

