@ Johto (data/maps/MtSilver_PokemonCenter_hns/scripts.inc), as built into the FireRed game.

MtSilver_PokemonCenter_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, MtSilver_PokemonCenter_OnTransition
	.byte 0

MtSilver_PokemonCenter_OnTransition::
	setrespawn JOHTO_HEAL_LOCATION_MT_SILVER_HNS
	end

MtSilver_PokemonCenter_EventScript_Meara::
	lock
	faceplayer
	goto_if_ge JOHTO_VAR_SINJOH_STORYLINE, 1, MtSilver_PokemonCenter_EventScript_Meara_AfterUnlockSinjoh
	msgbox MtSilver_PokemonCenter_Text_Meara1, MSGBOX_AUTOCLOSE
	checkitem ITEM_AZURE_FLUTE
	goto_if_eq VAR_RESULT, TRUE, MtSilver_PokemonCenter_EventScript_Meara_BonusContentPrompt
	release
	end

MtSilver_PokemonCenter_EventScript_Meara_BonusContentPrompt::
	msgbox MtSilver_PokemonCenter_Text_Meara2, MSGBOX_AUTOCLOSE
	helpwindow HELP_SINJOH_WINDOW

	msgbox MtSilver_PokemonCenter_Text_Prompt, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, FALSE, MtSilver_PokemonCenter_EventScript_Meara_BonusContentNo
	closemessage


	clearflag JOHTO_FLAG_MT_SILVER_1F_HIDE_SCIENTIST
	setflag JOHTO_FLAG_HIDE_SNOWSWEPT_NOBLE_SNEASLER
	setflag JOHTO_FLAG_HIDE_ROUTE49_NOBLE_WYRDEER
	setflag JOHTO_FLAG_HIDE_ROUTE49_NOBLE_OVERQWIL
	setflag JOHTO_FLAG_HIDE_HOTSPRINGS_NOBLE_ARCANINE
	setflag JOHTO_FLAG_HIDE_HOTSPRINGS_NOBLE_URSALUNA
	setflag JOHTO_FLAG_HIDE_ROUTE50_NOBLE_ELECTRODE
	setflag JOHTO_FLAG_HIDE_ROUTE50_NOBLE_KLEAVOR
	setflag JOHTO_FLAG_HIDE_NEWSINJOH_HOUSE3_NOBLE_TYPHLOSION
	setflag JOHTO_FLAG_HIDE_SINJOHRUINS_STEVEN
	setflag JOHTO_FLAG_HIDE_SINJOHRUINS_ARCEUSROOM_ARCEUS
	setflag JOHTO_FLAG_HIDE_SINJOHRUINS_ARCEUSROOM_STEVEN
	setflag JOHTO_FLAG_HIDE_NEWSINJOH_STEVEN
	setvar JOHTO_VAR_SINJOH_STORYLINE, 1
	setvar JOHTO_VAR_PLATECOUNTER, 0
	setvar JOHTO_VAR_REGIS_SCANNED, 0
	warp MAP_MT_SILVER_1F_WATERFALL_ROOM_HNS, 43, 9
	waitstate
	end

MtSilver_PokemonCenter_EventScript_Meara_BonusContentNo::
	release
	end

MtSilver_PokemonCenter_EventScript_Meara_AfterUnlockSinjoh::
	msgbox MtSilver_PokemonCenter_Text_Meara3, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, TRUE, MtSilver_PokemonCenter_EventScript_Meara_WarpToSinjoh
	closemessage
	release
	end

MtSilver_PokemonCenter_EventScript_Meara_WarpToSinjoh::
	warp MAP_MT_SILVER_1F_WATERFALL_ROOM_HNS, 43, 9
	waitstate
	release
	end

MtSilver_PokemonCenter_Text_Meara1:
	.string "I'{SE_M_MILK_DRINK}{SE_M_CHARGE}researche{SE_M_SAND_TOMB}from..{SE_M_PERISH_SONG}Uhh...\n"
	.string "th{SE_M_REVERSAL}PEWTE{SE_M_MINIMIZE}CIT{SE_M_MOONLIGHT}museum!\p"
	.string "A{SE_M_ATTRACT}unusua{SE_M_BATON_PASS}amoun{SE_M_SPIT_UP}o{SE_M_ACID_ARMOR}artifact{SE_M_GRASSWHISTLE}have\n"
	.string "bee{SE_M_ATTRACT}discovere{SE_M_WATERFALL}i{SE_M_ATTRACT}thi{SE_M_GRASSWHISTLE}area{SE_M_SUPERSONIC}so\l"
	.string "I'v{SE_M_REVERSAL}com{SE_M_REVERSAL}her{SE_M_REVERSAL}t{SE_M_ATTRACT2}investigate.\p"
	.string "Hav{SE_M_REVERSAL}yo{SE_M_DIVE}foun{SE_M_WATERFALL}anythin{SE_M_SANDSTORM}strange\n"
	.string "i{SE_M_ATTRACT}th{SE_M_REVERSAL}mountain?\p"
	.string "Mayb{SE_M_REVERSAL}somethin{SE_M_SANDSTORM}lik{SE_M_REVERSAL}{SE_M_CHARGE}FLUTE?\p"
	.string "I{SE_M_ACID_ARMOR}yo{SE_M_DIVE}do{SE_M_SUPERSONIC}pleas{SE_M_REVERSAL}sho{SE_M_TWISTER}me.$"

MtSilver_PokemonCenter_Text_Meara2:
	.string "Tha{SE_M_SPIT_UP}flute!\p"
	.string "Yo{SE_M_DIVE}hav{SE_M_REVERSAL}th{SE_M_REVERSAL}spiri{SE_M_SPIT_UP}o{SE_M_ACID_ARMOR}{SE_M_CHARGE}true\n"
	.string "archaeologist!\p"
	.string "There'{SE_M_GRASSWHISTLE}{SE_M_CHARGE}branc{SE_M_TRI_ATTACK}o{SE_M_ACID_ARMOR}th{SE_M_REVERSAL}cave\n"
	.string "wher{SE_M_REVERSAL}th{SE_M_REVERSAL}POKéMO{SE_M_PSYBEAM2}ar{SE_M_REVERSAL}to{SE_M_ATTRACT2}strong\l"
	.string "fo{SE_M_SAND_TOMB}m{SE_M_REVERSAL}t{SE_M_ATTRACT2}safel{SE_M_YAWN}explore.\p"
	.string "I{SE_M_ACID_ARMOR}{SE_M_HEAL_BELL}tak{SE_M_REVERSAL}yo{SE_M_DIVE}there{SE_M_SUPERSONIC}woul{SE_M_WATERFALL}you\n"
	.string "explor{SE_M_REVERSAL}i{SE_M_SPIT_UP}fo{SE_M_SAND_TOMB}mor{SE_M_REVERSAL}artifacts?$"

MtSilver_PokemonCenter_Text_Prompt:
	.string "I{SE_M_ACID_ARMOR}{SE_M_HEAL_BELL}tak{SE_M_REVERSAL}yo{SE_M_DIVE}there{SE_M_SUPERSONIC}woul{SE_M_WATERFALL}you\n"
	.string "explor{SE_M_REVERSAL}i{SE_M_SPIT_UP}fo{SE_M_SAND_TOMB}mor{SE_M_REVERSAL}artifacts?$"

MtSilver_PokemonCenter_Text_Meara3:
	.string "Read{SE_M_YAWN}t{SE_M_ATTRACT2}searc{SE_M_TRI_ATTACK}fo{SE_M_SAND_TOMB}mor{SE_M_REVERSAL}artifacts?$"

