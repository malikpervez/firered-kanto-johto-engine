@ Johto (data/maps/IndigoPlateau_PokemonCenter_hns/scripts.inc), as built into the FireRed game.

IndigoPlateau_PokemonCenter_hns_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, IndigoPlateau_PokemonCenter_OnFrame
	map_script MAP_SCRIPT_ON_TRANSITION, IndigoPlateau_Pokecenter_OnTransition
	.byte 0

IndigoPlateau_PokemonCenter_OnFrame::
	map_script_2 JOHTO_VAR_LEAGUE_STATE, 0, IndigoPlateau_PokemonCenter_Enter
	map_script_2 JOHTO_VAR_LEAGUE_STATE, 2, IndigoPlateau_PokemonCenter_Enter
	map_script_2 JOHTO_VAR_LEAGUE_STATE, 3, IndigoPlateau_PokemonCenter_Enter
	map_script_2 JOHTO_VAR_LEAGUE_STATE, 4, IndigoPlateau_PokemonCenter_Enter
	map_script_2 JOHTO_VAR_LEAGUE_STATE, 5, IndigoPlateau_PokemonCenter_Enter
	map_script_2 JOHTO_VAR_LEAGUE_STATE, 6, IndigoPlateau_PokemonCenter_Enter
	.2byte 0

IndigoPlateau_PokemonCenter_Enter::
	setflag JOHTO_FLAG_VISITED_INDIGO_PLATEAU
	setvar JOHTO_VAR_LEAGUE_STATE, 1
	end

IndigoPlateau_Pokecenter_OnTransition::
	setrespawn JOHTO_HEAL_LOCATION_INDIGO_PLATEAU_HNS
	end

IndigoPlateau_EventScript_Cooltrainer::
	msgbox IndigoPlateau_Text_CooltrainerM, MSGBOX_NPC
	end

IndigoPlateau_EventScript_BlackBelt::
	msgbox IndigoPlateau_Text_Blackbelt, MSGBOX_NPC
	end

IndigoPlateau_EventScript_ShigyNinja::
	msgbox IndigoPlateau_Text_ShigyNinja, MSGBOX_NPC
	end

IndigoPlateau_Text_ShigyNinja:
	.string "Congrat{SE_M_GRASSWHISTLE}o{SE_M_ATTRACT}makin{SE_M_SANDSTORM}i{SE_M_SPIT_UP}here!\p"
	.string "I'v{SE_M_REVERSAL}see{SE_M_ATTRACT}ton{SE_M_GRASSWHISTLE}o{SE_M_ACID_ARMOR}trainer{SE_M_GRASSWHISTLE}come\n"
	.string "throug{SE_M_TRI_ATTACK}her{SE_M_REVERSAL}ove{SE_M_SAND_TOMB}th{SE_M_REVERSAL}years{SE_M_SUPERSONIC}and\l"
	.string "al{SE_M_BATON_PASS}o{SE_M_ACID_ARMOR}the{SE_M_MILK_DRINK}ar{SE_M_REVERSAL}wonderfull{SE_M_YAWN}unique.\p"
	.string "Yo{SE_M_DIVE}shoul{SE_M_WATERFALL}b{SE_M_REVERSAL}prou{SE_M_WATERFALL}o{SE_M_ACID_ARMOR}yourself\n"
	.string "fo{SE_M_SAND_TOMB}gettin{SE_M_SANDSTORM}thi{SE_M_GRASSWHISTLE}far!\p"
	.string "Now{SE_M_SUPERSONIC}g{SE_M_ATTRACT2}ge{SE_M_SPIT_UP}'em!$"

IndigoPlateau_Text_Blackbelt:
	.string "Th{SE_M_REVERSAL}POKéMO{SE_M_PSYBEAM2}LEAGU{SE_M_SWORDS_DANCE}i{SE_M_GRASSWHISTLE}no{SE_M_SPIT_UP}taking\n"
	.string "ne{SE_M_TWISTER}challenger{SE_M_GRASSWHISTLE}a{SE_M_SPIT_UP}th{SE_M_REVERSAL}moment.\p"
	.string "Pleas{SE_M_REVERSAL}chec{SE_M_ENCORE2}bac{SE_M_ENCORE2}later.$"

IndigoPlateau_Text_CooltrainerM:
	.string "A{SE_M_SPIT_UP}th{SE_M_REVERSAL}POKéMO{SE_M_PSYBEAM2}LEAGUE{SE_M_SUPERSONIC}you'l{SE_M_BATON_PASS}get\n"
	.string "teste{SE_M_WATERFALL}b{SE_M_YAWN}th{SE_M_REVERSAL}ELIT{SE_M_SWORDS_DANCE}FOUR.\p"
	.string "Yo{SE_M_DIVE}hav{SE_M_REVERSAL}t{SE_M_ATTRACT2}bea{SE_M_SPIT_UP}the{SE_M_MILK_DRINK}all{SE_M_PERISH_SONG}I{SE_M_ACID_ARMOR}you\n"
	.string "lose{SE_M_SUPERSONIC}yo{SE_M_DIVE}hav{SE_M_REVERSAL}t{SE_M_ATTRACT2}star{SE_M_SPIT_UP}al{SE_M_BATON_PASS}over!$"

IndigoPlateau_EventScript_Silver::
	lock
	faceplayer
	goto_if_set JOHTO_FLAG_DAILY_BEAT_SILVER, IndigoPlateau_EventScript_SilverBeat
	msgbox IndigoPlateau_Text_RivalEntrance1, MSGBOX_DEFAULT
	call_if_eq JOHTO_VAR_STARTER_MON, 0, IndigoPlateau_Silver_Battle_Cyndaquil
	call_if_eq JOHTO_VAR_STARTER_MON, 1, IndigoPlateau_Silver_Battle_Totodile
	call_if_eq JOHTO_VAR_STARTER_MON, 2, IndigoPlateau_Silver_Battle_Chikorita
	msgbox IndigoPlateau_Text_RivalAfter, MSGBOX_DEFAULT
	setflag JOHTO_FLAG_DAILY_BEAT_SILVER
	release
	end

IndigoPlateau_EventScript_SilverBeat::
	msgbox IndigoPlateau_Text_RivalAfter, MSGBOX_DEFAULT
	closemessage
	release
	end

IndigoPlateau_Silver_Battle_Cyndaquil::
	trainerbattle_no_intro TRAINER_JOHTO_RIVAL_CYNDAQUIL_7_HNS, IndigoPlateau_Text_RivalWin
	return

IndigoPlateau_Silver_Battle_Totodile::
	trainerbattle_no_intro TRAINER_JOHTO_RIVAL_TOTODILE_7_HNS, IndigoPlateau_Text_RivalWin
	return

IndigoPlateau_Silver_Battle_Chikorita::
	trainerbattle_no_intro TRAINER_JOHTO_RIVAL_CHIKORITA_7_HNS, IndigoPlateau_Text_RivalWin
	return

IndigoPlateau_Text_RivalEntrance1:
	.string "Hol{SE_M_WATERFALL}it.\p"
	.string "You'r{SE_M_REVERSAL}goin{SE_M_SANDSTORM}t{SE_M_ATTRACT2}tak{SE_M_REVERSAL}th{SE_M_REVERSAL}POKéMON\n"
	.string "LEAGU{SE_M_SWORDS_DANCE}challeng{SE_M_REVERSAL}now?\p"
	.string "That'{SE_M_GRASSWHISTLE}no{SE_M_SPIT_UP}goin{SE_M_SANDSTORM}t{SE_M_ATTRACT2}happen.\p"
	.string "M{SE_M_YAWN}super-well-traine{SE_M_WATERFALL}POKéMON\n"
	.string "ar{SE_M_REVERSAL}goin{SE_M_SANDSTORM}t{SE_M_ATTRACT2}poun{SE_M_WATERFALL}you.\p"
	.string "{PLAYER}!\n"
	.string "{SE_M_HEAL_BELL}challeng{SE_M_REVERSAL}you!$"

IndigoPlateau_Text_RivalWin:
	.string "…\p"
	.string "OK--{SE_M_HEAL_BELL}lost…$"

IndigoPlateau_Text_RivalAfter:
	.string "…Darn{SE_M_DIZZY_PUNCH}{SE_M_HEAL_BELL}stil{SE_M_BATON_PASS}can'{SE_M_SPIT_UP}win…\p"
	.string "I{SE_M_DIZZY_PUNCH}{SE_M_HEAL_BELL}hav{SE_M_REVERSAL}t{SE_M_ATTRACT2}thin{SE_M_ENCORE2}mor{SE_M_REVERSAL}abou{SE_M_SPIT_UP}my\n"
	.string "POKéMON…\p"
	.string "Humph{SE_M_DRAGON_RAGE}Tr{SE_M_YAWN}no{SE_M_SPIT_UP}t{SE_M_ATTRACT2}lose!$"

IndigoPlateau_EventScript_Psychic::
	lock
	faceplayer
	msgbox IndigoPlateau_Text_TeleportGuy1, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, TRUE, IndigoPlateau_EventScript_PsychicTeleport
	msgbox IndigoPlateau_Text_TeleportGuyNo, MSGBOX_DEFAULT
	closemessage
	release
	end

IndigoPlateau_EventScript_PsychicTeleport::
	msgbox IndigoPlateau_Text_TeleportGuyYes, MSGBOX_DEFAULT
	closemessage
	turnobject OBJ_EVENT_ID_PLAYER, DIR_SOUTH
	playbgm ((558 + 1) + 0x0A), FALSE
	delay 60
	playmoncry SPECIES_ABRA, CRY_MODE_NORMAL
	applymovement2 LOCALID_INDIGOPLATEAU_ABRA, IndigoPLateau_Movement_Abra
	waitmovement 0
	fadescreen FADE_TO_WHITE
	warpteleport MAP_NEW_BARK_TOWN_HNS, 20, 12
	waitstate
	release
	end

IndigoPLateau_Movement_Abra:
	jump_in_place_right
	jump_in_place_right
	step_end

IndigoPlateau_EventScript_Abra::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_ABRA, CRY_MODE_NORMAL
	msgbox IndigoPlateau_Text_Abra, MSGBOX_DEFAULT
	waitmoncry
	release
	end

IndigoPlateau_Text_TeleportGuy1:
	.string "Ah{SE_M_DRAGON_RAGE}You'r{SE_M_REVERSAL}challengin{SE_M_SANDSTORM}th{SE_M_REVERSAL}ELITE\n"
	.string "FOUR{SE_M_SING}Ar{SE_M_REVERSAL}yo{SE_M_DIVE}sur{SE_M_REVERSAL}you'r{SE_M_REVERSAL}ready?\p"
	.string "I{SE_M_ACID_ARMOR}yo{SE_M_DIVE}nee{SE_M_WATERFALL}t{SE_M_ATTRACT2}trai{SE_M_ATTRACT}som{SE_M_REVERSAL}more,\n"
	.string "m{SE_M_YAWN}ABR{SE_M_BONEMERANG}ca{SE_M_ATTRACT}hel{SE_M_MORNING_SUN}you.\p"
	.string "I{SE_M_SPIT_UP}ca{SE_M_ATTRACT}TELEPOR{SE_M_SWIFT}yo{SE_M_DIVE}home.\p"
	.string "Woul{SE_M_WATERFALL}yo{SE_M_DIVE}lik{SE_M_REVERSAL}t{SE_M_ATTRACT2}g{SE_M_ATTRACT2}hom{SE_M_REVERSAL}now?$"

IndigoPlateau_Text_TeleportGuyYes:
	.string "OK{SE_M_SUPERSONIC}OK{SE_M_PERISH_SONG}Pictur{SE_M_REVERSAL}you{SE_M_SAND_TOMB}hous{SE_M_REVERSAL}i{SE_M_ATTRACT}your\n"
	.string "mind…$"

IndigoPlateau_Text_TeleportGuyNo:
	.string "OK{SE_M_SUPERSONIC}OK{SE_M_PERISH_SONG}Th{SE_M_REVERSAL}bes{SE_M_SPIT_UP}o{SE_M_ACID_ARMOR}luc{SE_M_ENCORE2}t{SE_M_ATTRACT2}you!$"

IndigoPlateau_Text_Abra:
	.string "ABRA{SE_M_HEAT_WAVE}Aabra…$"

