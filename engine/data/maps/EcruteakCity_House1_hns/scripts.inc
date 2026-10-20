@ Johto (data/maps/EcruteakCity_House1_hns/scripts.inc), as built into the FireRed game.

EcruteakCity_House1_hns_MapScripts::
	.byte 0

EcruteakCity_House1_EventScript_Gramps::
	lock
	faceplayer
	msgbox EcruteakLugiaSpeechHouse_Text_Gramps, MSGBOX_DEFAULT
	closemessage
	release
	end

EcruteakCity_House1_EventScript_Youngster::
	lock
	faceplayer
	msgbox EcruteakLugiaSpeechHouse_Text_Youngster, MSGBOX_DEFAULT
	closemessage
	release
	end

EcruteakLugiaSpeechHouse_Text_Gramps:
	.string "Thi{SE_M_GRASSWHISTLE}happene{SE_M_WATERFALL}whe{SE_M_ATTRACT}{SE_M_HEAL_BELL}wa{SE_M_GRASSWHISTLE}young.\p"
	.string "Th{SE_M_REVERSAL}sk{SE_M_YAWN}suddenl{SE_M_YAWN}turne{SE_M_WATERFALL}black{SE_M_PERISH_SONG}A\n"
	.string "gian{SE_M_SPIT_UP}flyin{SE_M_SANDSTORM}POKéMO{SE_M_PSYBEAM2}wa{SE_M_GRASSWHISTLE}blocking\l"
	.string "ou{SE_M_SPIT_UP}th{SE_M_REVERSAL}sun.\p"
	.string "{SE_M_HEAL_BELL}wonde{SE_M_SAND_TOMB}wha{SE_M_SPIT_UP}tha{SE_M_SPIT_UP}POKéMO{SE_M_PSYBEAM2}was?\p"
	.string "I{SE_M_SPIT_UP}wa{SE_M_GRASSWHISTLE}lik{SE_M_REVERSAL}{SE_M_CHARGE}bir{SE_M_WATERFALL}an{SE_M_WATERFALL}{SE_M_CHARGE}dragon.$"

EcruteakLugiaSpeechHouse_Text_Youngster:
	.string "I{SE_M_GRASSWHISTLE}ther{SE_M_REVERSAL}reall{SE_M_YAWN}{SE_M_CHARGE}POKéMO{SE_M_PSYBEAM2}tha{SE_M_SPIT_UP}big?\p"
	.string "I{SE_M_ACID_ARMOR}i{SE_M_SPIT_UP}exists{SE_M_SUPERSONIC}i{SE_M_SPIT_UP}mus{SE_M_SPIT_UP}b{SE_M_REVERSAL}powerful.$"

