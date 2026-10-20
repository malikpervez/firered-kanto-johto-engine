@ Johto (data/maps/PokemonLeague_KarensRoom_hns/scripts.inc), as built into the FireRed game.

PokemonLeague_KarensRoom_hns_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, EliteFourRoom_OnFrame
	map_script MAP_SCRIPT_ON_RESUME, PokemonLeague_KarensRoom_OnResume
	map_script MAP_SCRIPT_ON_LOAD, EliteFourRoom_OnLoad
	.byte 0

PokemonLeague_KarensRoom_OnResume::
	setvar VAR_0x8004, 3
	special DoPokemonLeagueLightingEffect
	end

PokemonLeague_KarensRoom_EventScript_Karen::
	lock
	faceplayer
	goto_if_ge JOHTO_VAR_LEAGUE_STATE, 5, PokemonLeague_KarensRoom_EventScript_KarenDefeated
	goto_if_set JOHTO_FLAG_IS_CHAMPION, PokemonLeague_KarensRoom_EventScript_KarenRematch
	msgbox PokemonLeague_KarensRoom_Text_Before, MSGBOX_DEFAULT
	setflag FLAG_TEMP_3
	setflag FLAG_TEMP_5
	trainerbattle_no_intro TRAINER_JOHTO_KAREN_1_HNS, PokemonLeague_KarensRoom_Text_Beaten
	goto PokemonLeague_KarensRoom_EventScript_KarenOnDefeat

PokemonLeague_KarensRoom_EventScript_KarenRematch::
	goto_if_unset JOHTO_FLAG_IS_KANTO_CHAMPION, PokemonLeague_KarensRoom_EventScript_KarenRematchStandard
	goto_if_ge JOHTO_VAR_SINJOH_STORYLINE, 13, PokemonLeague_KarensRoom_EventScript_KarenRematchPostOBC

PokemonLeague_KarensRoom_EventScript_KarenRematchStandard::
	msgbox PokemonLeague_KarensRoom_Text_RematchBefore, MSGBOX_DEFAULT
	setflag FLAG_TEMP_3
	setflag FLAG_TEMP_5
	trainerbattle_no_intro TRAINER_JOHTO_KAREN_2_HNS, PokemonLeague_KarensRoom_Text_Beaten
	goto PokemonLeague_KarensRoom_EventScript_KarenOnDefeat

PokemonLeague_KarensRoom_EventScript_KarenRematchPostOBC::
	msgbox PokemonLeague_KarensRoom_Text_RematchBefore, MSGBOX_DEFAULT
	setflag FLAG_TEMP_3
	setflag FLAG_TEMP_5
	trainerbattle_no_intro TRAINER_JOHTO_KAREN_POSTOBC_HNS, PokemonLeague_KarensRoom_Text_Beaten
	goto PokemonLeague_KarensRoom_EventScript_KarenOnDefeat

PokemonLeague_KarensRoom_EventScript_KarenOnDefeat::
	clearflag FLAG_TEMP_5
	msgbox PokemonLeague_KarensRoom_Text_Defeat, MSGBOX_DEFAULT
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
	setvar JOHTO_VAR_LEAGUE_STATE, 5
	release
	end

PokemonLeague_KarensRoom_EventScript_KarenDefeated::
	msgbox PokemonLeague_KarensRoom_Text_Defeat, MSGBOX_DEFAULT
	closemessage
	release
	end

PokemonLeague_KarensRoom_Text_RematchBefore:
	.string "KAREN{SE_M_HEAT_WAVE}Ah{SE_M_SUPERSONIC}it'{SE_M_GRASSWHISTLE}yo{SE_M_DIVE}again.\p"
	.string "{SE_M_HEAL_BELL}trus{SE_M_SPIT_UP}yo{SE_M_DIVE}haven'{SE_M_SPIT_UP}forgotten\n"
	.string "m{SE_M_YAWN}belief:\p"
	.string "Tru{SE_M_REVERSAL}strengt{SE_M_TRI_ATTACK}arise{SE_M_GRASSWHISTLE}fro{SE_M_MILK_DRINK}trust\n"
	.string "i{SE_M_ATTRACT}one'{SE_M_GRASSWHISTLE}POKéMON.\p"
	.string "Sinc{SE_M_REVERSAL}ou{SE_M_SAND_TOMB}las{SE_M_SPIT_UP}encounter{SE_M_SUPERSONIC}my\n"
	.string "bon{SE_M_WATERFALL}wit{SE_M_TRI_ATTACK}m{SE_M_YAWN}POKéMO{SE_M_PSYBEAM2}has\l"
	.string "deepene{SE_M_WATERFALL}further.\p"
	.string "Ar{SE_M_REVERSAL}yo{SE_M_DIVE}read{SE_M_YAWN}t{SE_M_ATTRACT2}fac{SE_M_REVERSAL}{SE_M_CHARGE}team\n"
	.string "unite{SE_M_WATERFALL}b{SE_M_YAWN}a{SE_M_ATTRACT}unbreakabl{SE_M_REVERSAL}bond?\p"
	.string "Sho{SE_M_TWISTER}m{SE_M_REVERSAL}th{SE_M_REVERSAL}powe{SE_M_SAND_TOMB}o{SE_M_ACID_ARMOR}th{SE_M_REVERSAL}bond\n"
	.string "wit{SE_M_TRI_ATTACK}you{SE_M_SAND_TOMB}POKéMON.$"

PokemonLeague_KarensRoom_Text_Before:
	.string "{SE_M_HEAL_BELL}a{SE_M_MILK_DRINK}KARE{SE_M_PSYBEAM2}o{SE_M_ACID_ARMOR}th{SE_M_REVERSAL}ELIT{SE_M_SWORDS_DANCE}FOUR.\p"
	.string "You'r{SE_M_REVERSAL}{PLAYER}{SE_M_SING}Ho{SE_M_TWISTER}amusing.\p"
	.string "{SE_M_HEAL_BELL}lov{SE_M_REVERSAL}DARK-typ{SE_M_REVERSAL}POKéMON.\p"
	.string "{SE_M_HEAL_BELL}fin{SE_M_WATERFALL}thei{SE_M_SAND_TOMB}wild{SE_M_SUPERSONIC}toug{SE_M_TRI_ATTACK}image\n"
	.string "t{SE_M_ATTRACT2}b{SE_M_REVERSAL}s{SE_M_ATTRACT2}appealing{SE_M_PERISH_SONG}An{SE_M_WATERFALL}they're\l"
	.string "s{SE_M_ATTRACT2}strong.\p"
	.string "Thin{SE_M_ENCORE2}yo{SE_M_DIVE}ca{SE_M_ATTRACT}tak{SE_M_REVERSAL}them?\n"
	.string "Jus{SE_M_SPIT_UP}tr{SE_M_YAWN}t{SE_M_ATTRACT2}entertai{SE_M_ATTRACT}me.\p"
	.string "Let'{SE_M_GRASSWHISTLE}go.$"

PokemonLeague_KarensRoom_Text_Beaten:
	.string "Well{SE_M_SUPERSONIC}aren'{SE_M_SPIT_UP}yo{SE_M_DIVE}good{SE_M_PERISH_SONG}{SE_M_HEAL_BELL}lik{SE_M_REVERSAL}that\n"
	.string "i{SE_M_ATTRACT}{SE_M_CHARGE}trainer.$"

PokemonLeague_KarensRoom_Text_Defeat:
	.string "Stron{SE_M_SANDSTORM}POKéMON.\p"
	.string "Wea{SE_M_ENCORE2}POKéMON.\p"
	.string "Tha{SE_M_SPIT_UP}i{SE_M_GRASSWHISTLE}onl{SE_M_YAWN}th{SE_M_REVERSAL}selfish\n"
	.string "perceptio{SE_M_ATTRACT}o{SE_M_ACID_ARMOR}people.\p"
	.string "Trul{SE_M_YAWN}skille{SE_M_WATERFALL}trainer{SE_M_GRASSWHISTLE}should\n"
	.string "tr{SE_M_YAWN}t{SE_M_ATTRACT2}wi{SE_M_ATTRACT}wit{SE_M_TRI_ATTACK}thei{SE_M_SAND_TOMB}favorites.\p"
	.string "{SE_M_HEAL_BELL}lik{SE_M_REVERSAL}you{SE_M_SAND_TOMB}style{SE_M_PERISH_SONG}Yo{SE_M_DIVE}understand\n"
	.string "what'{SE_M_GRASSWHISTLE}important.\p"
	.string "G{SE_M_ATTRACT2}on--th{SE_M_REVERSAL}CHAMPIO{SE_M_PSYBEAM2}i{SE_M_GRASSWHISTLE}waiting.$"

