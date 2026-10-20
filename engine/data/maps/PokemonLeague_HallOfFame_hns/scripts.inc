@ Johto (data/maps/PokemonLeague_HallOfFame_hns/scripts.inc), as built into the FireRed game.

PokemonLeague_HallOfFame_hns_MapScripts::
	map_script 2, J_PokemonLeague_HallOfFame_OnFrame
	.byte 0

J_PokemonLeague_HallOfFame_OnFrame::
	map_script_2 20576, 6, PokemonLeague_HallOfFame_EventScript_Cutscene
	.2byte 0

PokemonLeague_HallOfFame_EventScript_Cutscene::
	lock
	goto_if_set 10399, PokemonLeague_HallOfFame_EventScript_CutsceneKantoChamp
	applymovement 1, PokemonLeague_HallOfFame_Movement_LanceEnter
	applymovement 255, PokemonLeague_HallOfFame_Movement_PlayerEnter
	waitmovement 255
	waitmovement 1
	msgbox PokemonLeague_HallOfFame_LanceText, MSGBOX_DEFAULT
	closemessage
	special GivePartyMonChampionRibbon
	applymovement 255, J_Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	delay 20
	dofieldeffect 79
	waitfieldeffect 79
	delay 40
	setvar 16385, 1
	call PokemonLeague_HallOfFame_EventScript_SetFirstGameClearFlags
	setrespawn 128
	fadescreenspeed 1, 24
	special GameClear
	waitstate
	releaseall
	end

PokemonLeague_HallOfFame_EventScript_CutsceneKantoChamp::
	applymovement 1, PokemonLeague_HallOfFame_Movement_LanceEnter
	applymovement 255, PokemonLeague_HallOfFame_Movement_PlayerEnter
	waitmovement 255
	waitmovement 1
	msgbox PokemonLeague_HallOfFame_Rematch_LanceText, MSGBOX_DEFAULT
	closemessage
	special GivePartyMonChampionRibbon
	applymovement 255, J_Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	delay 20
	dofieldeffect 79
	waitfieldeffect 79
	delay 40
	setvar 16385, 1
	call PokemonLeague_HallOfFame_EventScript_SetGameClearFlags
	setrespawn 128
	fadescreenspeed 1, 24
	special GameClear
	waitstate
	releaseall
	end

PokemonLeague_HallOfFame_EventScript_SetFirstGameClearFlags::
	setflag 8230
	setflag 9142
	clearflag 9166
	clearflag 8359
	setflag 10399
	setflag 8411
	setvar 20576, 1
	setvar 20581, 6
	setvar 20603, 0
	return

PokemonLeague_HallOfFame_EventScript_SetGameClearFlags::
	setflag 8372
	setflag 8230
	setflag 9142
	clearflag 9166
	clearflag 8264
	clearflag 8263
	clearflag 8262
	clearflag 8260
	clearflag 8261
	clearflag 8259
	clearflag 8250
	clearflag 8247
	clearflag 8246
	clearflag 8257
	clearflag 8256
	clearflag 8258
	clearflag 8657
	setflag 8411
	setflag 10400
	setvar 20559, 4
	clearflag 8254
	setvar 20558, 4
	clearflag 8253
	call PokemonLeague_HallOfFame_EventScript_SpawnRoamers
	call_if_ge 20604, 8, PokemonLeague_HallOfFame_EventScript_SpawnSuicune
	call_if_set 8768, PokemonLeague_HallOfFame_EventScript_SpawnSecondCelebi
	call_if_ge 20632, 4, PokemonLeague_HallOfFame_EventScript_SpawnPichu
	call_if_ge 20638, 4, PokemonLeague_HallOfFame_EventScript_SpawnAlolaMons
	call PokemonLeague_HallOfFame_EventScript_SpawnSinjohMons
	call_if_ge 20639, 13 PokemonLeague_HallOfFame_EventScript_SpawnArceus
	clearflag 8761
	clearflag 8769
	clearflag 8666
	clearflag 8762
	clearflag 8673
	setvar 20576, 1
	return

PokemonLeague_HallOfFame_EventScript_SpawnAlolaMons::
	clearflag 9302
	clearflag 9304
	clearflag 9305
	clearflag 9303
	clearflag 9340
	clearflag 9341
	clearflag 9344
	clearflag 9337
	clearflag 9338
	clearflag 9339
	clearflag 9342
	clearflag 9343
	return

PokemonLeague_HallOfFame_EventScript_SpawnSinjohMons::
	clearflag 9133
	clearflag 9132
	clearflag 9134
	clearflag 9135
	clearflag 9136
	clearflag 9137
	return

PokemonLeague_HallOfFame_EventScript_SpawnArceus::
	clearflag 9124
	return

PokemonLeague_HallOfFame_EventScript_SpawnPichu::
	clearflag 9286
	return

PokemonLeague_HallOfFame_EventScript_SpawnRoamers::
	clearflag 8766
	clearflag 8767
	special InitRoamer
	copyvar 32772, 20626
	special InitKantoRoamers
	setflag 8955
	return

PokemonLeague_HallOfFame_EventScript_SpawnSuicune::
	clearflag 8249
	return

PokemonLeague_HallOfFame_EventScript_SpawnSecondCelebi::
	clearflag 8291
	return

PokemonLeague_HallOfFame_Movement_LanceEnter:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_right
	face_left
	step_end

PokemonLeague_HallOfFame_Movement_PlayerEnter:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	face_right
	step_end

PokemonLeague_HallOfFame_LanceText:
	.string "LANCE{SE_M_HEAT_WAVE}It'{SE_M_GRASSWHISTLE}bee{SE_M_ATTRACT}{SE_M_CHARGE}lon{SE_M_SANDSTORM}tim{SE_M_REVERSAL}sinc{SE_M_REVERSAL}I\n"
	.string "las{SE_M_SPIT_UP}cam{SE_M_REVERSAL}here.\p"
	.string "Thi{SE_M_GRASSWHISTLE}i{SE_M_GRASSWHISTLE}wher{SE_M_REVERSAL}w{SE_M_REVERSAL}hono{SE_M_SAND_TOMB}th{SE_M_REVERSAL}LEAGUE\n"
	.string "CHAMPION{SE_M_SKETCH}fo{SE_M_SAND_TOMB}al{SE_M_BATON_PASS}eternity.\p"
	.string "Thei{SE_M_SAND_TOMB}courageou{SE_M_GRASSWHISTLE}POKéMO{SE_M_PSYBEAM2}ar{SE_M_REVERSAL}also\n"
	.string "inducted.\p"
	.string "Her{SE_M_REVERSAL}today{SE_M_SUPERSONIC}w{SE_M_REVERSAL}witnesse{SE_M_WATERFALL}th{SE_M_REVERSAL}rise\n"
	.string "o{SE_M_ACID_ARMOR}{SE_M_CHARGE}ne{SE_M_TWISTER}LEAGU{SE_M_SWORDS_DANCE}CHAMPION--a\p"
	.string "traine{SE_M_SAND_TOMB}wh{SE_M_ATTRACT2}feel{SE_M_GRASSWHISTLE}compassio{SE_M_ATTRACT}for,\n"
	.string "an{SE_M_WATERFALL}trus{SE_M_SPIT_UP}toward{SE_M_SUPERSONIC}al{SE_M_BATON_PASS}POKéMON.\p"
	.string "{SE_M_BONEMERANG}traine{SE_M_SAND_TOMB}wh{SE_M_ATTRACT2}succeede{SE_M_WATERFALL}through\n"
	.string "perseveranc{SE_M_REVERSAL}an{SE_M_WATERFALL}determination.\p"
	.string "Th{SE_M_REVERSAL}ne{SE_M_TWISTER}LEAGU{SE_M_SWORDS_DANCE}CHAMPIO{SE_M_PSYBEAM2}wh{SE_M_ATTRACT2}has\n"
	.string "al{SE_M_BATON_PASS}th{SE_M_REVERSAL}making{SE_M_GRASSWHISTLE}o{SE_M_ACID_ARMOR}greatness!\p"
	.string "{PLAYER}{SE_M_SUPERSONIC}allo{SE_M_TWISTER}m{SE_M_REVERSAL}t{SE_M_ATTRACT2}registe{SE_M_SAND_TOMB}you\n"
	.string "an{SE_M_WATERFALL}you{SE_M_SAND_TOMB}partner{SE_M_GRASSWHISTLE}a{SE_M_GRASSWHISTLE}CHAMPIONS!$"

PokemonLeague_HallOfFame_Rematch_LanceText:
	.string "LANCE{SE_M_HEAT_WAVE}{SE_M_HEAL_BELL}remember{SE_M_SUPERSONIC}i{SE_M_SPIT_UP}wasn'{SE_M_SPIT_UP}lon{SE_M_SANDSTORM}ago\n"
	.string "{SE_M_HEAL_BELL}stoo{SE_M_WATERFALL}here{SE_M_SUPERSONIC}welcomin{SE_M_SANDSTORM}yo{SE_M_DIVE}as\p"
	.string "th{SE_M_REVERSAL}CHAMPIO{SE_M_PSYBEAM2}o{SE_M_ACID_ARMOR}JOHTO.\p"
	.string "An{SE_M_WATERFALL}now{SE_M_SUPERSONIC}her{SE_M_REVERSAL}w{SE_M_REVERSAL}ar{SE_M_REVERSAL}again{SE_M_SUPERSONIC}i{SE_M_ATTRACT}this\n"
	.string "sacre{SE_M_WATERFALL}plac{SE_M_REVERSAL}wher{SE_M_REVERSAL}w{SE_M_REVERSAL}hono{SE_M_SAND_TOMB}th{SE_M_REVERSAL}very\p"
	.string "bes{SE_M_SPIT_UP}trainer{SE_M_GRASSWHISTLE}an{SE_M_WATERFALL}thei{SE_M_SAND_TOMB}POKéMON.\p"
	.string "Today{SE_M_SUPERSONIC}you'v{SE_M_REVERSAL}prove{SE_M_ATTRACT}yoursel{SE_M_ACID_ARMOR}not\n"
	.string "jus{SE_M_SPIT_UP}i{SE_M_ATTRACT}JOHTO{SE_M_SUPERSONIC}bu{SE_M_SPIT_UP}i{SE_M_ATTRACT}KANT{SE_M_SOLAR_BEAM}a{SE_M_GRASSWHISTLE}well,\l"
	.string "bestin{SE_M_SANDSTORM}eve{SE_M_ATTRACT}m{SE_M_YAWN}stronges{SE_M_SPIT_UP}team.\p"
	.string "You'v{SE_M_REVERSAL}show{SE_M_ATTRACT}remarkabl{SE_M_REVERSAL}compassion\n"
	.string "an{SE_M_WATERFALL}trus{SE_M_SPIT_UP}i{SE_M_ATTRACT}you{SE_M_SAND_TOMB}POKéMON,\l"
	.string "{SE_M_CHARGE}bon{SE_M_WATERFALL}tha{SE_M_SPIT_UP}ha{SE_M_GRASSWHISTLE}carrie{SE_M_WATERFALL}yo{SE_M_DIVE}to\l"
	.string "victor{SE_M_YAWN}tim{SE_M_REVERSAL}an{SE_M_WATERFALL}again.\p"
	.string "You{SE_M_SAND_TOMB}journey{SE_M_SUPERSONIC}marke{SE_M_WATERFALL}by\n"
	.string "perseveranc{SE_M_REVERSAL}an{SE_M_WATERFALL}unwavering\l"
	.string "determination,\l"
	.string "speak{SE_M_GRASSWHISTLE}t{SE_M_ATTRACT2}you{SE_M_SAND_TOMB}tru{SE_M_REVERSAL}spiri{SE_M_SPIT_UP}a{SE_M_GRASSWHISTLE}a\l"
	.string "trainer.\p"
	.string "Yo{SE_M_DIVE}hav{SE_M_REVERSAL}al{SE_M_BATON_PASS}th{SE_M_REVERSAL}making{SE_M_GRASSWHISTLE}o{SE_M_ACID_ARMOR}{SE_M_CHARGE}true\n"
	.string "great{SE_M_SUPERSONIC}perhap{SE_M_GRASSWHISTLE}eve{SE_M_ATTRACT}th{SE_M_REVERSAL}greatest.\p"
	.string "{PLAYER}{SE_M_SUPERSONIC}i{SE_M_SPIT_UP}i{SE_M_GRASSWHISTLE}m{SE_M_YAWN}hono{SE_M_SAND_TOMB}t{SE_M_ATTRACT2}register\n"
	.string "you{SE_M_SUPERSONIC}an{SE_M_WATERFALL}you{SE_M_SAND_TOMB}truste{SE_M_WATERFALL}partners,\l"
	.string "a{SE_M_GRASSWHISTLE}champion{SE_M_GRASSWHISTLE}onc{SE_M_REVERSAL}again.$"

