@ Johto (data/maps/PokemonLeague_BrunosRoom_hns/scripts.inc), as built into the FireRed game.

PokemonLeague_BrunosRoom_hns_MapScripts::
	map_script 2, EliteFourRoom_OnFrame
	map_script 5, J_PokemonLeague_BrunosRoom_OnResume
	map_script 1, EliteFourRoom_OnLoad
	.byte 0

J_PokemonLeague_BrunosRoom_OnResume::
	setvar 32772, 2
	special DoPokemonLeagueLightingEffect
	end

J_PokemonLeague_BrunosRoom_EventScript_Bruno::
	lock
	faceplayer
	goto_if_ge 20576, 4, PokemonLeague_BrunosRoom_EventScript_BrunoDefeated
	goto_if_set 10399, PokemonLeague_BrunosRoom_EventScript_BrunoRematch
	msgbox PokemonLeague_BrunosRoom_Text_Before, MSGBOX_DEFAULT
	setflag 3
	setflag 5
	trainerbattle_no_intro 1459, PokemonLeague_BrunosRoom_Text_Beaten
	goto PokemonLeague_BrunosRoom_EventScript_BrunoOnDefeat

PokemonLeague_BrunosRoom_EventScript_BrunoRematch::
	goto_if_unset 10400, PokemonLeague_BrunosRoom_EventScript_BrunoRematchStandard
	goto_if_ge 20639, 13, PokemonLeague_BrunosRoom_EventScript_BrunoRematchPostOBC

PokemonLeague_BrunosRoom_EventScript_BrunoRematchStandard::
	msgbox PokemonLeague_BrunosRoom_Text_RematchBefore, MSGBOX_DEFAULT
	setflag 3
	setflag 5
	trainerbattle_no_intro 1460, PokemonLeague_BrunosRoom_Text_Beaten
	goto PokemonLeague_BrunosRoom_EventScript_BrunoOnDefeat

PokemonLeague_BrunosRoom_EventScript_BrunoRematchPostOBC::
	msgbox PokemonLeague_BrunosRoom_Text_RematchBefore, MSGBOX_DEFAULT
	setflag 3
	setflag 5
	trainerbattle_no_intro 1671, PokemonLeague_BrunosRoom_Text_Beaten
	goto PokemonLeague_BrunosRoom_EventScript_BrunoOnDefeat

PokemonLeague_BrunosRoom_EventScript_BrunoOnDefeat::
	clearflag 5
	msgbox PokemonLeague_BrunosRoom_Text_Defeat, MSGBOX_DEFAULT
	closemessage
	setmetatile 6, 1, 0x28E, FALSE
	setmetatile 6, 2, 0x296, FALSE
	playse 20
	setvar 32772, 1
	setvar 32773, 1
	setvar 32774, 4
	setvar 32775, 4
	special ShakeCamera
	waitstate
	special DrawWholeMapView
	setvar 20576, 4
	release
	end

PokemonLeague_BrunosRoom_EventScript_BrunoDefeated::
	msgbox PokemonLeague_BrunosRoom_Text_Defeat, MSGBOX_DEFAULT
	closemessage
	release
	end

PokemonLeague_BrunosRoom_Text_RematchBefore:
	.string "BRUNO{SE_M_HEAT_WAVE}Welcom{SE_M_REVERSAL}back{SE_M_SUPERSONIC}young\n"
	.string "warrior.\p"
	.string "Throug{SE_M_TRI_ATTACK}rigorou{SE_M_GRASSWHISTLE}training{SE_M_SUPERSONIC}w{SE_M_REVERSAL}have\n"
	.string "grow{SE_M_ATTRACT}stronger.\p"
	.string "M{SE_M_YAWN}rock-har{SE_M_WATERFALL}wil{SE_M_BATON_PASS}i{SE_M_GRASSWHISTLE}eve{SE_M_ATTRACT}mor{SE_M_REVERSAL}firm\n"
	.string "an{SE_M_WATERFALL}unyielding.\p"
	.string "Ar{SE_M_REVERSAL}yo{SE_M_DIVE}prepare{SE_M_WATERFALL}t{SE_M_ATTRACT2}fac{SE_M_REVERSAL}a{SE_M_ATTRACT}even\n"
	.string "greate{SE_M_SAND_TOMB}challenge?\p"
	.string "Sho{SE_M_TWISTER}m{SE_M_REVERSAL}th{SE_M_REVERSAL}result{SE_M_GRASSWHISTLE}o{SE_M_ACID_ARMOR}your\n"
	.string "training.\p"
	.string "Ho{SE_M_ATTRACT2}hah!$"

PokemonLeague_BrunosRoom_Text_Before:
	.string "{SE_M_HEAL_BELL}a{SE_M_MILK_DRINK}BRUN{SE_M_SOLAR_BEAM}o{SE_M_ACID_ARMOR}th{SE_M_REVERSAL}ELIT{SE_M_SWORDS_DANCE}FOUR.\p"
	.string "{SE_M_HEAL_BELL}alway{SE_M_GRASSWHISTLE}trai{SE_M_ATTRACT}t{SE_M_ATTRACT2}th{SE_M_REVERSAL}extrem{SE_M_REVERSAL}be-\n"
	.string "caus{SE_M_REVERSAL}{SE_M_HEAL_BELL}believ{SE_M_REVERSAL}i{SE_M_ATTRACT}ou{SE_M_SAND_TOMB}potential.\p"
	.string "Tha{SE_M_SPIT_UP}i{SE_M_GRASSWHISTLE}ho{SE_M_TWISTER}w{SE_M_REVERSAL}becam{SE_M_REVERSAL}strong.\p"
	.string "Ca{SE_M_ATTRACT}yo{SE_M_DIVE}withstan{SE_M_WATERFALL}ou{SE_M_SAND_TOMB}power?\p"
	.string "Hm{SE_M_SING}{SE_M_HEAL_BELL}se{SE_M_REVERSAL}n{SE_M_ATTRACT2}fea{SE_M_SAND_TOMB}i{SE_M_ATTRACT}you{SE_M_PERISH_SONG}Yo{SE_M_DIVE}look\n"
	.string "determined{SE_M_PERISH_SONG}Perfec{SE_M_SPIT_UP}fo{SE_M_SAND_TOMB}battle!\p"
	.string "Ready{SE_M_SUPERSONIC}{PLAYER}{SE_M_SING}Yo{SE_M_DIVE}wil{SE_M_BATON_PASS}bo{SE_M_TWISTER}down\n"
	.string "t{SE_M_ATTRACT2}ou{SE_M_SAND_TOMB}overwhelmin{SE_M_SANDSTORM}power!\p"
	.string "Ho{SE_M_ATTRACT2}hah!$"

PokemonLeague_BrunosRoom_Text_Beaten:
	.string "Why{SE_M_SING}Ho{SE_M_TWISTER}coul{SE_M_WATERFALL}w{SE_M_REVERSAL}lose?$"

PokemonLeague_BrunosRoom_Text_Defeat:
	.string "Havin{SE_M_SANDSTORM}lost{SE_M_SUPERSONIC}{SE_M_HEAL_BELL}hav{SE_M_REVERSAL}n{SE_M_ATTRACT2}righ{SE_M_SPIT_UP}to\n"
	.string "sa{SE_M_YAWN}anything…\p"
	.string "G{SE_M_ATTRACT2}fac{SE_M_REVERSAL}you{SE_M_SAND_TOMB}nex{SE_M_SPIT_UP}challenge!$"

