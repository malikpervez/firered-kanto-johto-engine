@ Johto (data/maps/CherrygroveCity_PokemonCenter_hns/scripts.inc), as built into the FireRed game.

CherrygroveCity_PokemonCenter_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, CherryGrove_Pokecenter_OnTransition
	.byte 0

CherryGrove_Pokecenter_OnTransition::
	setrespawn JOHTO_HEAL_LOCATION_CHERRYGROVE_CITY_HNS
	end

CherryGrove_Pokecenter_EventScript_Fisher::
	lock
	faceplayer
	msgbox CherryGrove_Pokecenter_Text_Fisher, MSGBOX_DEFAULT
	closemessage
	release
	end

CherryGrove_Pokecenter_EventScript_Gentleman::
	lock
	faceplayer
	msgbox CherryGrove_Pokecenter_Text_Gentleman, MSGBOX_DEFAULT
	closemessage
	release
	end

CherryGrove_Pokecenter_EventScript_Lass::
	lock
	faceplayer
	msgbox CherryGrove_Pokecenter_Text_Lass, MSGBOX_DEFAULT
	closemessage
	release
	end

CherryGrove_Pokecenter_Chansey::
	lock
	faceplayer
	playmoncry SPECIES_CHANSEY, CRY_MODE_NORMAL
	msgbox CherryGrove_Pokecenter_Text_Chansey, MSGBOX_DEFAULT
	delay 40
	waitmoncry
	closemessage
	end

CherryGrove_Pokecenter_Text_Fisher:
	.string "It'{SE_M_GRASSWHISTLE}great{SE_M_PERISH_SONG}{SE_M_HEAL_BELL}ca{SE_M_ATTRACT}stor{SE_M_REVERSAL}an{SE_M_YAWN}number\n"
	.string "o{SE_M_ACID_ARMOR}POKéMON{SE_M_SUPERSONIC}an{SE_M_WATERFALL}it'{SE_M_GRASSWHISTLE}al{SE_M_BATON_PASS}free.$"

CherryGrove_Pokecenter_Text_Gentleman:
	.string "Tha{SE_M_SPIT_UP}P{SE_M_PSYBEAM}i{SE_M_GRASSWHISTLE}fre{SE_M_REVERSAL}fo{SE_M_SAND_TOMB}any\n"
	.string "traine{SE_M_SAND_TOMB}t{SE_M_ATTRACT2}use.$"

CherryGrove_Pokecenter_Text_Lass:
	.string "The{SE_M_YAWN}sa{SE_M_YAWN}{SE_M_CHARGE}watche{SE_M_WATERFALL}po{SE_M_SPIT_UP}never\n"
	.string "boils{SE_M_PERISH_SONG}Bu{SE_M_SPIT_UP}watchin{SE_M_SANDSTORM}th{SE_M_REVERSAL}clock\l"
	.string "i{SE_M_ATTRACT}th{SE_M_REVERSAL}POKéCENTE{SE_M_MINIMIZE}make{SE_M_GRASSWHISTLE}tim{SE_M_REVERSAL}fly!$"

CherryGrove_Pokecenter_Text_Chansey:
	.string "CHANSEY{SE_M_HEAT_WAVE}Chaan{SE_M_DRAGON_RAGE}Sii!$"

