@ Johto (data/maps/PokemonLeague_HallOfFame_hns/scripts.inc), as built into the FireRed game.

PokemonLeague_HallOfFame_hns_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, J_PokemonLeague_HallOfFame_OnFrame
	.byte 0

J_PokemonLeague_HallOfFame_OnFrame::
	map_script_2 JOHTO_VAR_LEAGUE_STATE, 6, PokemonLeague_HallOfFame_EventScript_Cutscene
	.2byte 0

PokemonLeague_HallOfFame_EventScript_Cutscene::
	lock
	goto_if_set JOHTO_FLAG_IS_CHAMPION, PokemonLeague_HallOfFame_EventScript_CutsceneKantoChamp
	applymovement LOCALID_HALLOFFAME_LANCE, PokemonLeague_HallOfFame_Movement_LanceEnter
	applymovement OBJ_EVENT_ID_PLAYER, PokemonLeague_HallOfFame_Movement_PlayerEnter
	waitmovement OBJ_EVENT_ID_PLAYER
	waitmovement LOCALID_HALLOFFAME_LANCE
	msgbox PokemonLeague_HallOfFame_LanceText, MSGBOX_DEFAULT
	closemessage
	special GivePartyMonChampionRibbon
	applymovement OBJ_EVENT_ID_PLAYER, J_Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	delay 20
	dofieldeffect FLDEFF_HALL_OF_FAME_RECORD_FRLG
	waitfieldeffect FLDEFF_HALL_OF_FAME_RECORD_FRLG
	delay 40
	setvar VAR_TEMP_1, 1
	call PokemonLeague_HallOfFame_EventScript_SetFirstGameClearFlags
	setrespawn JOHTO_HEAL_LOCATION_NEW_BARK_TOWN_HNS
	fadescreenspeed FADE_TO_BLACK, 24
	special GameClear
	waitstate
	releaseall
	end

PokemonLeague_HallOfFame_EventScript_CutsceneKantoChamp::
	applymovement LOCALID_HALLOFFAME_LANCE, PokemonLeague_HallOfFame_Movement_LanceEnter
	applymovement OBJ_EVENT_ID_PLAYER, PokemonLeague_HallOfFame_Movement_PlayerEnter
	waitmovement OBJ_EVENT_ID_PLAYER
	waitmovement LOCALID_HALLOFFAME_LANCE
	msgbox PokemonLeague_HallOfFame_Rematch_LanceText, MSGBOX_DEFAULT
	closemessage
	special GivePartyMonChampionRibbon
	applymovement OBJ_EVENT_ID_PLAYER, J_Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	delay 20
	dofieldeffect FLDEFF_HALL_OF_FAME_RECORD_FRLG
	waitfieldeffect FLDEFF_HALL_OF_FAME_RECORD_FRLG
	delay 40
	setvar VAR_TEMP_1, 1
	call PokemonLeague_HallOfFame_EventScript_SetGameClearFlags
	setrespawn JOHTO_HEAL_LOCATION_NEW_BARK_TOWN_HNS
	fadescreenspeed FADE_TO_BLACK, 24
	special GameClear
	waitstate
	releaseall
	end

PokemonLeague_HallOfFame_EventScript_SetFirstGameClearFlags::
	setflag JOHTO_FLAG_HIDE_AZALEA_TOWN_SLOWPOKE
	setflag JOHTO_FLAG_HIDE_SLOWPOKE_WELL_TAILLESS_SLOWPOKES
	clearflag JOHTO_FLAG_HIDE_AZALEA_TOWN_TAILED_SLOWPOKES
	clearflag JOHTO_FLAG_HIDE_LEAGUE_BLACKBELT
	setflag JOHTO_FLAG_IS_CHAMPION
	setflag JOHTO_FLAG_HIDE_BATTLEFRONTIER_ENGINEER
	setvar JOHTO_VAR_LEAGUE_STATE, 1
	setvar JOHTO_VAR_NEWBARK_TOWN_STATE, 6
	setvar JOHTO_VAR_SSAQUA_STATE, 0
	return

PokemonLeague_HallOfFame_EventScript_SetGameClearFlags::
	setflag JOHTO_FLAG_HIDE_CERULEANCAVE_GUARD
	setflag JOHTO_FLAG_HIDE_AZALEA_TOWN_SLOWPOKE
	setflag JOHTO_FLAG_HIDE_SLOWPOKE_WELL_TAILLESS_SLOWPOKES
	clearflag JOHTO_FLAG_HIDE_AZALEA_TOWN_TAILED_SLOWPOKES
	clearflag JOHTO_FLAG_HIDE_LATIOS
	clearflag JOHTO_FLAG_HIDE_LATIAS
	clearflag JOHTO_FLAG_HIDE_RAYQUAZA
	clearflag JOHTO_FLAG_HIDE_GROUDON
	clearflag JOHTO_FLAG_HIDE_KYOGRE
	clearflag JOHTO_FLAG_HIDE_MEWTWO
	clearflag JOHTO_FLAG_HIDE_VERMILION_SNORLAX
	clearflag JOHTO_FLAG_HIDE_UNION_CAVE_LAPRAS
	clearflag JOHTO_FLAG_HIDE_SUDOWOODO
	clearflag JOHTO_FLAG_HIDE_ZAPDOS
	clearflag JOHTO_FLAG_HIDE_ARTICUNO
	clearflag JOHTO_FLAG_HIDE_MOLTRES
	clearflag JOHTO_FLAG_ITEM_GS_BALL
	setflag JOHTO_FLAG_HIDE_BATTLEFRONTIER_ENGINEER
	setflag JOHTO_FLAG_IS_KANTO_CHAMPION
	setvar JOHTO_VAR_COMPLETED_LUGIA, 4
	clearflag JOHTO_FLAG_HIDE_LUGIA
	setvar JOHTO_VAR_COMPLETED_HO_OH, 4
	clearflag JOHTO_FLAG_HIDE_HO_OH
	call PokemonLeague_HallOfFame_EventScript_SpawnRoamers
	call_if_ge JOHTO_VAR_SUICUNE_ENCOUNTERS, 8, PokemonLeague_HallOfFame_EventScript_SpawnSuicune
	call_if_set JOHTO_FLAG_CAUGHT_CELEBI, PokemonLeague_HallOfFame_EventScript_SpawnSecondCelebi
	call_if_ge JOHTO_VAR_VIRIDIAN_FOREST_PICHU, 4, PokemonLeague_HallOfFame_EventScript_SpawnPichu
	call_if_ge JOHTO_VAR_ALOLA_STATE, 4, PokemonLeague_HallOfFame_EventScript_SpawnAlolaMons
	call PokemonLeague_HallOfFame_EventScript_SpawnSinjohMons
	call_if_ge JOHTO_VAR_SINJOH_STORYLINE, 13 PokemonLeague_HallOfFame_EventScript_SpawnArceus
	clearflag JOHTO_FLAG_DEFEATED_MEW
	clearflag JOHTO_FLAG_CAUGHT_MEW
	clearflag JOHTO_FLAG_BATTLED_DEOXYS
	clearflag JOHTO_FLAG_DEFEATED_DEOXYS
	clearflag JOHTO_FLAG_SUMMONED_MTMOON_JIRACHI
	setvar JOHTO_VAR_LEAGUE_STATE, 1
	return

PokemonLeague_HallOfFame_EventScript_SpawnAlolaMons::
	clearflag JOHTO_FLAG_HIDE_TAPU_BULU
	clearflag JOHTO_FLAG_HIDE_TAPU_FINI
	clearflag JOHTO_FLAG_HIDE_TAPU_KOKO
	clearflag JOHTO_FLAG_HIDE_TAPU_LELE
	clearflag JOHTO_FLAG_HIDE_DUGTRIO_ALOLA
	clearflag JOHTO_FLAG_HIDE_MAROWAK_ALOLA
	clearflag JOHTO_FLAG_HIDE_EXEGGUTOR_ALOLA
	clearflag JOHTO_FLAG_HIDE_SANDSLASH_ALOLA
	clearflag JOHTO_FLAG_HIDE_NINETALES_ALOLA
	clearflag JOHTO_FLAG_HIDE_MUK_ALOLA
	clearflag JOHTO_FLAG_HIDE_RAICHU_ALOLA
	clearflag JOHTO_FLAG_HIDE_GOLEM_ALOLA
	return

PokemonLeague_HallOfFame_EventScript_SpawnSinjohMons::
	clearflag JOHTO_FLAG_HIDE_SINJOHRUINS_REGIROCK
	clearflag JOHTO_FLAG_HIDE_SINJOHRUINS_REGICE
	clearflag JOHTO_FLAG_HIDE_SINJOHRUINS_REGISTEEL
	clearflag JOHTO_FLAG_HIDE_SINJOHRUINS_REGIELEKI
	clearflag JOHTO_FLAG_HIDE_SINJOHRUINS_REGIDRAGO
	clearflag JOHTO_FLAG_HIDE_SINJOHRUINS_REGIGIGAS
	return

PokemonLeague_HallOfFame_EventScript_SpawnArceus::
	clearflag JOHTO_FLAG_HIDE_SINJOHRUINS_ARCEUSROOM_ARCEUS
	return

PokemonLeague_HallOfFame_EventScript_SpawnPichu::
	clearflag JOHTO_FLAG_HIDE_VIRIDIAN_FOREST_SPIKY_EARED_PICHU
	return

PokemonLeague_HallOfFame_EventScript_SpawnRoamers::
	clearflag JOHTO_FLAG_CAUGHT_ENTEI
	clearflag JOHTO_FLAG_CAUGHT_RAIKOU
	special InitRoamer
	copyvar VAR_0x8004, JOHTO_VAR_ROAMER_POKEMON_HNS
	special InitKantoRoamers
	setflag JOHTO_FLAG_LATIOS_OR_LATIAS_ROAMING
	return

PokemonLeague_HallOfFame_EventScript_SpawnSuicune::
	clearflag JOHTO_FLAG_HIDE_ROUTE25_SUICUNE
	return

PokemonLeague_HallOfFame_EventScript_SpawnSecondCelebi::
	clearflag JOHTO_FLAG_HIDE_ILEX_FOREST_SECOND_CELEBI
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

