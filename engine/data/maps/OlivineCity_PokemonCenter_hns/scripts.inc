@ Johto (data/maps/OlivineCity_PokemonCenter_hns/scripts.inc), as built into the FireRed game.

OlivineCity_PokemonCenter_hns_MapScripts::
	map_script 3, OlivineCity_PokemonCenter_OnTransition
	.byte 0

OlivineCity_PokemonCenter_OnTransition::
	setrespawn 134
	end

OlivineCity_EventScript_Fisher::
	lock
	faceplayer
	msgbox OlivineCity_Text_PokecenterFisher, MSGBOX_DEFAULT
	closemessage
	release
	end

OlivineCity_EventScript_Teacher::
	lock
	faceplayer
	msgbox OlivineCity_Text_PokecenterTeacher, MSGBOX_DEFAULT
	closemessage
	release
	end

OlivineCity_Text_PokecenterFisher:
	.string "Th{SE_M_REVERSAL}SAILO{SE_M_MINIMIZE}i{SE_M_ATTRACT}th{SE_M_REVERSAL}OLIVIN{SE_M_SWORDS_DANCE}CAFE\n"
	.string "nex{SE_M_SPIT_UP}doo{SE_M_SAND_TOMB}i{SE_M_GRASSWHISTLE}reall{SE_M_YAWN}generous.\p"
	.string "H{SE_M_REVERSAL}taugh{SE_M_SPIT_UP}m{SE_M_YAWN}POKéMO{SE_M_PSYBEAM2}STRENGTH.\p"
	.string "No{SE_M_TWISTER}i{SE_M_SPIT_UP}ca{SE_M_ATTRACT}mov{SE_M_REVERSAL}bi{SE_M_SANDSTORM}boulders\n"
	.string "withou{SE_M_SPIT_UP}breakin{SE_M_SANDSTORM}{SE_M_CHARGE}sweat.$"

OlivineCity_Text_PokecenterTeacher:
	.string "There'{SE_M_GRASSWHISTLE}{SE_M_CHARGE}perso{SE_M_ATTRACT}i{SE_M_ATTRACT}CIANWOOD\n"
	.string "CIT{SE_M_MOONLIGHT}acros{SE_M_GRASSWHISTLE}th{SE_M_REVERSAL}sea.\p"
	.string "{SE_M_HEAL_BELL}hear{SE_M_WATERFALL}hi{SE_M_MILK_DRINK}braggin{SE_M_SANDSTORM}abou{SE_M_SPIT_UP}his\n"
	.string "rar{SE_M_REVERSAL}POKéMO{SE_M_PSYBEAM2}al{SE_M_BATON_PASS}th{SE_M_REVERSAL}time.$"

