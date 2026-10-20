@ Johto (data/maps/BlackthornCity_PokemonCenter_hns/scripts.inc), as built into the FireRed game.

BlackthornCity_PokemonCenter_hns_MapScripts::
	map_script MAP_SCRIPT_ON_RESUME, J_CableClub_OnResume
	map_script MAP_SCRIPT_ON_TRANSITION, BlackthornCity_PokemonCenter_OnTransition
	.byte 0

BlackthornCity_PokemonCenter_OnTransition::
	setrespawn JOHTO_HEAL_LOCATION_BLACKTHORN_CITY_HNS
	end

BlackthornCity_PokemonCenter_EventScript_Gent::
	msgbox BlackthornCity_PokemonCenter1FGentlemanText, MSGBOX_NPC
	end

BlackthornCity_PokemonCenter_EventScript_Twin::
	msgbox BlackthornCity_PokemonCenter1FTwinText, MSGBOX_NPC
	end

BlackthornCity_PokemonCenter1FGentlemanText:
	.string "Dee{SE_M_MORNING_SUN}insid{SE_M_REVERSAL}far-of{SE_M_ACID_ARMOR}INDIGO\n"
	.string "PLATEA{SE_M_REFLECT}i{SE_M_GRASSWHISTLE}th{SE_M_REVERSAL}POKéMO{SE_M_PSYBEAM2}LEAGUE.\p"
	.string "{SE_M_HEAL_BELL}hea{SE_M_SAND_TOMB}th{SE_M_REVERSAL}bes{SE_M_SPIT_UP}trainer{SE_M_GRASSWHISTLE}gather\n"
	.string "ther{SE_M_REVERSAL}fro{SE_M_MILK_DRINK}aroun{SE_M_WATERFALL}th{SE_M_REVERSAL}country.$"

BlackthornCity_PokemonCenter1FTwinText:
	.string "Ther{SE_M_REVERSAL}wa{SE_M_GRASSWHISTLE}thi{SE_M_GRASSWHISTLE}mov{SE_M_REVERSAL}{SE_M_HEAL_BELL}jus{SE_M_SPIT_UP}had\n"
	.string "t{SE_M_ATTRACT2}teac{SE_M_TRI_ATTACK}m{SE_M_YAWN}POKéMON.\p"
	.string "S{SE_M_ATTRACT2}{SE_M_HEAL_BELL}go{SE_M_SPIT_UP}th{SE_M_REVERSAL}MOV{SE_M_SWORDS_DANCE}DELETE{SE_M_MINIMIZE}t{SE_M_ATTRACT2}make\n"
	.string "i{SE_M_SPIT_UP}forge{SE_M_SPIT_UP}a{SE_M_ATTRACT}H{SE_M_GIGA_DRAIN}move.$"

