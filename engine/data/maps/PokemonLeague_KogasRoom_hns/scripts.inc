@ Johto (data/maps/PokemonLeague_KogasRoom_hns/scripts.inc), as built into the FireRed game.

PokemonLeague_KogasRoom_hns_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, EliteFourRoom_OnFrame
	map_script MAP_SCRIPT_ON_RESUME, PokemonLeague_KogasRoom_OnResume
	map_script MAP_SCRIPT_ON_LOAD, EliteFourRoom_OnLoad
	.byte 0

PokemonLeague_KogasRoom_OnResume::
	setvar VAR_0x8004, 1
	special DoPokemonLeagueLightingEffect
	end

PokemonLeague_KogasRoom_EventScript_Koga::
	lock
	faceplayer
	goto_if_ge JOHTO_VAR_LEAGUE_STATE, 3, PokemonLeague_KogasRoom_EventScript_KogaDefeated
	goto_if_set JOHTO_FLAG_IS_CHAMPION, PokemonLeague_KogasRoom_EventScript_KogaRematch
	msgbox PokemonLeague_KogasRoom_Text_Before, MSGBOX_DEFAULT
	setflag FLAG_TEMP_3
	setflag FLAG_TEMP_5
	trainerbattle_no_intro TRAINER_JOHTO_KOGA_1_HNS, PokemonLeague_KogasRoom_Text_Beaten
	goto PokemonLeague_KogasRoom_EventScript_KogaOnDefeat

PokemonLeague_KogasRoom_EventScript_KogaRematch::
	goto_if_unset JOHTO_FLAG_IS_KANTO_CHAMPION, PokemonLeague_KogasRoom_EventScript_KogaRematchStandard
	goto_if_ge JOHTO_VAR_SINJOH_STORYLINE, 13, PokemonLeague_KogasRoom_EventScript_KogaRematchPostOBC

PokemonLeague_KogasRoom_EventScript_KogaRematchStandard::
	msgbox PokemonLeague_KogasRoom_Text_RematchBefore, MSGBOX_DEFAULT
	setflag FLAG_TEMP_3
	setflag FLAG_TEMP_5
	trainerbattle_no_intro TRAINER_JOHTO_KOGA_2_HNS, PokemonLeague_KogasRoom_Text_Beaten
	goto PokemonLeague_KogasRoom_EventScript_KogaOnDefeat

PokemonLeague_KogasRoom_EventScript_KogaRematchPostOBC::
	msgbox PokemonLeague_KogasRoom_Text_RematchBefore, MSGBOX_DEFAULT
	setflag FLAG_TEMP_3
	setflag FLAG_TEMP_5
	trainerbattle_no_intro TRAINER_JOHTO_KOGA_POSTOBC_HNS, PokemonLeague_KogasRoom_Text_Beaten
	goto PokemonLeague_KogasRoom_EventScript_KogaOnDefeat

PokemonLeague_KogasRoom_EventScript_KogaOnDefeat::
	clearflag FLAG_TEMP_5
	msgbox PokemonLeague_KogasRoom_Text_Defeat, MSGBOX_DEFAULT
	closemessage
	setmetatile 6, 1, 0x28E, FALSE
	setmetatile 6, 2, 0x296, FALSE
	playse SE_BANG
	setvar VAR_0x8004, 1
	setvar VAR_0x8005, 1
	setvar VAR_0x8006, 4
	setvar VAR_0x8007, 4
	special ShakeCamera
	waitstate
	special DrawWholeMapView
	setvar JOHTO_VAR_LEAGUE_STATE, 3
	release
	end

PokemonLeague_KogasRoom_EventScript_KogaDefeated::
	msgbox PokemonLeague_KogasRoom_Text_Defeat, MSGBOX_DEFAULT
	closemessage
	release
	end

PokemonLeague_KogasRoom_Text_RematchBefore:
	.string "KOGA{SE_M_HEAT_WAVE}Fwahahahaha!\p"
	.string "Yo{SE_M_DIVE}return{SE_M_SUPERSONIC}brav{SE_M_REVERSAL}challenger.\p"
	.string "M{SE_M_YAWN}ninj{SE_M_CHARGE}skill{SE_M_GRASSWHISTLE}hav{SE_M_REVERSAL}sharpened.\p"
	.string "Ne{SE_M_TWISTER}siniste{SE_M_SAND_TOMB}trap{SE_M_GRASSWHISTLE}awai{SE_M_SPIT_UP}you.\p"
	.string "Poison{SE_M_SUPERSONIC}sleep{SE_M_SUPERSONIC}an{SE_M_WATERFALL}more...\n"
	.string "B{SE_M_REVERSAL}ready!\p"
	.string "Fwahahahaha!\p"
	.string "Sho{SE_M_TWISTER}m{SE_M_REVERSAL}ho{SE_M_TWISTER}you'v{SE_M_REVERSAL}grown!$"

PokemonLeague_KogasRoom_Text_Before:
	.string "Fwahahahaha!\p"
	.string "{SE_M_HEAL_BELL}a{SE_M_MILK_DRINK}KOG{SE_M_BONEMERANG}o{SE_M_ACID_ARMOR}th{SE_M_REVERSAL}ELIT{SE_M_SWORDS_DANCE}FOUR.\p"
	.string "{SE_M_HEAL_BELL}liv{SE_M_REVERSAL}i{SE_M_ATTRACT}shadows{SE_M_SUPERSONIC}{SE_M_CHARGE}ninja!\p"
	.string "M{SE_M_YAWN}intricat{SE_M_REVERSAL}styl{SE_M_REVERSAL}wil{SE_M_BATON_PASS}confound\n"
	.string "an{SE_M_WATERFALL}destro{SE_M_YAWN}you!\p"
	.string "Confusion{SE_M_SUPERSONIC}sleep{SE_M_SUPERSONIC}poison…\p"
	.string "Prepar{SE_M_REVERSAL}t{SE_M_ATTRACT2}b{SE_M_REVERSAL}th{SE_M_REVERSAL}victi{SE_M_MILK_DRINK}o{SE_M_ACID_ARMOR}my\n"
	.string "siniste{SE_M_SAND_TOMB}technique!\p"
	.string "Fwahahahaha!\p"
	.string "POKéMO{SE_M_PSYBEAM2}i{SE_M_GRASSWHISTLE}no{SE_M_SPIT_UP}merel{SE_M_YAWN}abou{SE_M_SPIT_UP}brute\n"
	.string "force--yo{SE_M_DIVE}shal{SE_M_BATON_PASS}se{SE_M_REVERSAL}soo{SE_M_ATTRACT}enough!$"

PokemonLeague_KogasRoom_Text_Beaten:
	.string "Ah!\n"
	.string "Yo{SE_M_DIVE}hav{SE_M_REVERSAL}prove{SE_M_ATTRACT}you{SE_M_SAND_TOMB}worth!$"

PokemonLeague_KogasRoom_Text_Defeat:
	.string "{SE_M_HEAL_BELL}subjecte{SE_M_WATERFALL}yo{SE_M_DIVE}t{SE_M_ATTRACT2}everythin{SE_M_SANDSTORM}I\n"
	.string "coul{SE_M_WATERFALL}muster.\p"
	.string "Bu{SE_M_SPIT_UP}m{SE_M_YAWN}effort{SE_M_GRASSWHISTLE}failed{SE_M_PERISH_SONG}{SE_M_HEAL_BELL}mus{SE_M_SPIT_UP}hone\n"
	.string "m{SE_M_YAWN}skills.\p"
	.string "G{SE_M_ATTRACT2}o{SE_M_ATTRACT}t{SE_M_ATTRACT2}th{SE_M_REVERSAL}nex{SE_M_SPIT_UP}room{SE_M_SUPERSONIC}an{SE_M_WATERFALL}put\n"
	.string "you{SE_M_SAND_TOMB}abilitie{SE_M_GRASSWHISTLE}t{SE_M_ATTRACT2}test!$"

