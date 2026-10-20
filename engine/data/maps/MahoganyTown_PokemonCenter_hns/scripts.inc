@ Johto (data/maps/MahoganyTown_PokemonCenter_hns/scripts.inc), as built into the FireRed game.

MahoganyTown_PokemonCenter_hns_MapScripts::
	map_script 3, MahoganyTown_PokemonCenter_OnTransition
	.byte 0

MahoganyTown_PokemonCenter_OnTransition::
	setrespawn 136
	end

MahoganyTown_PokemonCenter_EventScript_Hiker::
	msgbox MahoganyTown_PokemonCenter_Text_PokefanM, MSGBOX_NPC
	end

MahoganyTown_PokemonCenter_EventScript_Boy::
	msgbox MahoganyTown_PokemonCenter_Text_Youngster, MSGBOX_NPC
	end

MahoganyTown_PokemonCenter_EventScript_Girl::
	msgbox MahoganyTown_PokemonCenter_Text_CooltrainerF, MSGBOX_NPC
	end

MahoganyTown_PokemonCenter_Text_PokefanM:
	.string "What'{SE_M_GRASSWHISTLE}this{SE_M_SING}TEA{SE_M_GIGA_DRAIN}ROCKE{SE_M_SWIFT}ha{SE_M_GRASSWHISTLE}come\n"
	.string "back?\p"
	.string "{SE_M_HEAL_BELL}sa{SE_M_TWISTER}som{SE_M_REVERSAL}me{SE_M_ATTRACT}i{SE_M_ATTRACT}blac{SE_M_ENCORE2}a{SE_M_SPIT_UP}LAK{SE_M_SWORDS_DANCE}OF\n"
	.string "RAGE…$"

MahoganyTown_PokemonCenter_Text_Youngster:
	.string "{SE_M_HEAL_BELL}sto{SE_M_MORNING_SUN}m{SE_M_YAWN}POKéMO{SE_M_PSYBEAM2}fro{SE_M_MILK_DRINK}evolvin{SE_M_SANDSTORM}too\n"
	.string "early.\p"
	.string "{SE_M_HEAL_BELL}mak{SE_M_REVERSAL}the{SE_M_MILK_DRINK}lear{SE_M_ATTRACT}certai{SE_M_ATTRACT}moves\n"
	.string "befor{SE_M_REVERSAL}{SE_M_HEAL_BELL}le{SE_M_SPIT_UP}the{SE_M_MILK_DRINK}evolve.$"

MahoganyTown_PokemonCenter_Text_CooltrainerF:
	.string "POKéMO{SE_M_PSYBEAM2}d{SE_M_ATTRACT2}becom{SE_M_REVERSAL}stronge{SE_M_SAND_TOMB}whe{SE_M_ATTRACT}they\n"
	.string "evolve,\p"
	.string "bu{SE_M_SPIT_UP}the{SE_M_YAWN}als{SE_M_ATTRACT2}lear{SE_M_ATTRACT}move{SE_M_GRASSWHISTLE}more\n"
	.string "slowly.$"

