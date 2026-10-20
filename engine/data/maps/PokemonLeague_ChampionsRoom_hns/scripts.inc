@ Johto (data/maps/PokemonLeague_ChampionsRoom_hns/scripts.inc), as built into the FireRed game.

PokemonLeague_ChampionsRoom_hns_MapScripts::
	map_script 2, ChampionRoom_OnFrame
	map_script 5, J_PokemonLeague_ChampionsRoom_OnResume
	.byte 0

J_PokemonLeague_ChampionsRoom_OnResume::
	setvar 32772, 4
	special DoPokemonLeagueLightingEffect
	end

ChampionRoom_OnFrame::
	map_script_2 16384, 0, ChampionRoom_CloseDoor
	.2byte 0

ChampionRoom_CloseDoor::
	lock
	setflag 2
	special DrawWholeMapView
	applymovement 255, ChamionRoom_Movement_Enter
	waitmovement 0
	setvar 16384, 1
	release
	end

ChamionRoom_Movement_Enter:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

ChampionRoom_Trigger::
	lock
	applymovement 255, J_Common_Movement_WalkUp1
	waitmovement 0
	release
	end

PokemonLeague_WillsRoom_EventScript_Lance::
	lockall
	call_if_eq 32780, DIR_EAST, PokemonLeague_ChampionsRoom_EventScript_AdjustPlayerFacingEast
	call_if_eq 32780, DIR_SOUTH, PokemonLeague_ChampionsRoom_EventScript_AdjustPlayerFacingSouth
	call_if_eq 32780, DIR_WEST, PokemonLeague_ChampionsRoom_EventScript_AdjustPlayerFacingWest
	faceplayer
	goto_if_set 10399, PokemonLeague_WillsRoom_EventScript_LanceRematch
	msgbox PokemonLeague_ChampionsRoom_Text_BattleIntro, MSGBOX_DEFAULT
	setflag 3
	setflag 5
	trainerbattle_no_intro 1465, PokemonLeague_ChampionsRoom_Text_BattleWin
	goto PokemonLeague_WillsRoom_EventScript_LanceOnDefeatJohto

PokemonLeague_WillsRoom_EventScript_LanceRematch::
	goto_if_unset 10400, PokemonLeague_WillsRoom_EventScript_LanceRematchStandard
	goto_if_ge 20639, 13, PokemonLeague_WillsRoom_EventScript_LanceRematchPostOBC

PokemonLeague_WillsRoom_EventScript_LanceRematchStandard::
	msgbox PokemonLeague_ChampionsRoom_Text_RematchBattleIntro, MSGBOX_DEFAULT
	setflag 3
	setflag 5
	trainerbattle_no_intro 1466, PokemonLeague_ChampionsRoom_Text_BattleWin
	goto PokemonLeague_WillsRoom_EventScript_LanceOnDefeatKanto

PokemonLeague_WillsRoom_EventScript_LanceRematchPostOBC::
	msgbox PokemonLeague_ChampionsRoom_Text_RematchBattleIntro, MSGBOX_DEFAULT
	setflag 3
	setflag 5
	trainerbattle_no_intro 1673, PokemonLeague_ChampionsRoom_Text_BattleWin
	goto PokemonLeague_WillsRoom_EventScript_LanceOnDefeatKanto

PokemonLeague_WillsRoom_EventScript_LanceOnDefeatJohto::
	clearflag 5
	msgbox PokemonLeague_ChampionsRoom_Text_BattleAfter, MSGBOX_DEFAULT
	closemessage
	setmetatile 6, 1, 0x3F2, FALSE
	setmetatile 6, 2, 0x296, FALSE
	playse 20
	setvar 32772, 1
	setvar 32773, 1
	setvar 32774, 4
	setvar 32775, 4
	special ShakeCamera
	waitstate
	special DrawWholeMapView
	playse 21
	applymovement 1, J_Common_Movement_ExclamationMark
	delay 55
	waitmovement 1
	turnobject 255, DIR_SOUTH
	applymovement 255, PokemonLeague_ChampionsRoom_Movement_PlayerMoveToCenter
	applymovement 1, PokemonLeague_ChampionsRoom_Movement_LanceMoveOver
	waitmovement 255
	waitmovement 1
	addobject 2
	addobject 3
	applymovement 2, PokemonLeague_ChampionsRoom_Movement_MaryEnter
	waitmovement 0
	msgbox PokemonLeague_ChampionsRoom_Text_MaryOhNoOak, MSGBOX_DEFAULT
	closemessage
	applymovement 3, PokemonLeague_ChampionsRoom_Movement_OakEnter
	delay 60
	applymovement 2, PokemonLeague_ChampionsRoom_Movement_MaryMoveOver
	waitmovement 2
	waitmovement 3
	msgbox PokemonLeague_ChampionsRoom_Text_OakCongratulations, MSGBOX_DEFAULT
	applymovement 2, PokemonLeague_ChampionsRoom_Movement_MaryInterview
	waitmovement 0
	msgbox PokemonLeague_ChampionsRoom_Text_MaryInterview, MSGBOX_DEFAULT
	closemessage
	applymovement 1, PokemonLeague_ChampionsRoom_Movement_LanceAnxious
	waitmovement 0
	msgbox PokemonLeague_ChampionsRoom_Text_Noisy, MSGBOX_DEFAULT
	closemessage
	applymovement 1, PokemonLeague_ChampionsRoom_Movement_LanceLeave
	delay 30
	applymovement 255, PokemonLeague_ChampionsRoom_Movement_PlayerLeave
	waitmovement 1

	removeobject 1
	playse 9
	waitmovement 255
	special SpawnCameraObject
	removeobject 255
	playse 9
	waitse
	delay 50
	applymovement 2, PokemonLeague_ChampionsRoom_Movement_MaryLeft
	waitmovement 0
	playse 21
	applymovement 2, J_Common_Movement_ExclamationMark
	delay 55
	waitmovement 2
	msgbox PokemonLeague_ChampionsRoom_Text_MaryNoInterview, MSGBOX_DEFAULT
	closemessage
	setvar 20576, 6
	warpsilent MAP_POKEMON_LEAGUE_HALL_OF_FAME_HNS, 0
	waitstate
	releaseall
	end

PokemonLeague_WillsRoom_EventScript_LanceOnDefeatKanto::
	clearflag 5
	msgbox PokemonLeague_ChampionsRoom_Text_BattleAfter, MSGBOX_DEFAULT
	closemessage
	setmetatile 6, 1, 0x3F2, FALSE
	setmetatile 6, 2, 0x296, FALSE
	playse 20
	setvar 32772, 1
	setvar 32773, 1
	setvar 32774, 4
	setvar 32775, 4
	special ShakeCamera
	waitstate
	special DrawWholeMapView
	playse 21
	applymovement 1, J_Common_Movement_ExclamationMark
	delay 55
	waitmovement 1
	turnobject 255, DIR_SOUTH
	applymovement 255, PokemonLeague_ChampionsRoom_Movement_PlayerMoveToCenter
	applymovement 1, PokemonLeague_ChampionsRoom_Movement_LanceMoveOver
	waitmovement 255
	waitmovement 1
	addobject 2
	addobject 3
	applymovement 2, PokemonLeague_ChampionsRoom_Movement_MaryEnter
	waitmovement 0
	msgbox PokemonLeague_ChampionsRoom_Text_MaryOhNoOak, MSGBOX_DEFAULT
	closemessage
	applymovement 3, PokemonLeague_ChampionsRoom_Movement_OakEnter
	delay 60
	applymovement 2, PokemonLeague_ChampionsRoom_Movement_MaryMoveOver
	waitmovement 2
	waitmovement 3
	msgbox PokemonLeague_ChampionsRoom_Text_RematchOakCongratulations, MSGBOX_DEFAULT
	applymovement 2, PokemonLeague_ChampionsRoom_Movement_MaryInterview
	waitmovement 0
	msgbox PokemonLeague_ChampionsRoom_Text_RematchMaryInterview, MSGBOX_DEFAULT
	closemessage
	applymovement 1, PokemonLeague_ChampionsRoom_Movement_LanceAnxious
	waitmovement 0
	msgbox PokemonLeague_ChampionsRoom_Text_Noisy, MSGBOX_DEFAULT
	closemessage
	applymovement 1, PokemonLeague_ChampionsRoom_Movement_LanceLeave
	delay 30
	applymovement 255, PokemonLeague_ChampionsRoom_Movement_PlayerLeave
	waitmovement 1

	removeobject 1
	playse 9
	waitmovement 255
	special SpawnCameraObject
	removeobject 255
	playse 9
	waitse
	delay 50
	applymovement 2, PokemonLeague_ChampionsRoom_Movement_MaryLeft
	waitmovement 0
	playse 21
	applymovement 2, J_Common_Movement_ExclamationMark
	delay 55
	waitmovement 2
	msgbox PokemonLeague_ChampionsRoom_Text_RematchMaryNoInterview, MSGBOX_DEFAULT
	closemessage
	setvar 20576, 6
	warpsilent MAP_POKEMON_LEAGUE_HALL_OF_FAME_HNS, 0
	waitstate
	releaseall
	end

PokemonLeague_ChampionsRoom_EventScript_AdjustPlayerFacingEast::
	applymovement 255, PokemonLeague_ChampionsRoom_Movement_AdjustPlayerFacingEast
	waitmovement 0
	return

PokemonLeague_ChampionsRoom_EventScript_AdjustPlayerFacingSouth::
	applymovement 255, PokemonLeague_ChampionsRoom_Movement_AdjustPlayerFacingSouth
	waitmovement 0
	return

PokemonLeague_ChampionsRoom_EventScript_AdjustPlayerFacingWest::
	applymovement 255, PokemonLeague_ChampionsRoom_Movement_AdjustPlayerFacingWest
	waitmovement 0
	return

PokemonLeague_ChampionsRoom_Movement_AdjustPlayerFacingEast:
	walk_down
	walk_right
	face_up
	step_end

PokemonLeague_ChampionsRoom_Movement_AdjustPlayerFacingSouth:
	walk_left
	walk_down
	walk_down
	walk_right
	face_up
	step_end

PokemonLeague_ChampionsRoom_Movement_AdjustPlayerFacingWest:
	walk_down
	walk_left
	face_up
	step_end

PokemonLeague_ChampionsRoom_Movement_PlayerMoveToCenter:
	lock_facing_direction
	walk_up
	unlock_facing_direction
	step_end

PokemonLeague_ChampionsRoom_Movement_LanceMoveOver:
	lock_facing_direction
	walk_right
	unlock_facing_direction
	step_end

PokemonLeague_ChampionsRoom_Movement_MaryEnter:
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	delay_2
	walk_in_place_fast_down
	step_end

PokemonLeague_ChampionsRoom_Movement_MaryMoveOver:
	walk_left
	face_right
	step_end

PokemonLeague_ChampionsRoom_Movement_OakEnter:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

PokemonLeague_ChampionsRoom_Movement_MaryInterview:
	walk_fast_up
	walk_in_place_fast_right
	step_end

PokemonLeague_ChampionsRoom_Movement_LanceAnxious:
	face_up
	delay_16
	delay_16
	face_down
	delay_16
	delay_16
	face_left
	step_end

PokemonLeague_ChampionsRoom_Movement_LanceLeave:
	walk_up
	walk_left
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

PokemonLeague_ChampionsRoom_Movement_PlayerLeave:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

PokemonLeague_ChampionsRoom_Movement_MaryLeft:
	walk_fast_right
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	step_end

PokemonLeague_ChampionsRoom_Text_RematchBattleIntro:
	.string "LANCE{SE_M_HEAT_WAVE}Welcom{SE_M_REVERSAL}back{SE_M_SUPERSONIC}{PLAYER}!\p"
	.string "Yo{SE_M_DIVE}conquere{SE_M_WATERFALL}th{SE_M_REVERSAL}JOHT{SE_M_SOLAR_BEAM}LEAGUE,\n"
	.string "an{SE_M_WATERFALL}prove{SE_M_WATERFALL}yoursel{SE_M_ACID_ARMOR}i{SE_M_ATTRACT}KANTO.\p"
	.string "M{SE_M_YAWN}tea{SE_M_MILK_DRINK}i{SE_M_GRASSWHISTLE}stronge{SE_M_SAND_TOMB}tha{SE_M_ATTRACT}before.\p"
	.string "Sho{SE_M_TWISTER}m{SE_M_REVERSAL}ho{SE_M_TWISTER}fa{SE_M_SAND_TOMB}yo{SE_M_DIVE}an{SE_M_WATERFALL}your\n"
	.string "POKéMO{SE_M_PSYBEAM2}hav{SE_M_REVERSAL}come{SE_M_SUPERSONIC}CHAMPION!$"

PokemonLeague_ChampionsRoom_Text_BattleIntro:
	.string "LANCE{SE_M_HEAT_WAVE}I'v{SE_M_REVERSAL}bee{SE_M_ATTRACT}waitin{SE_M_SANDSTORM}fo{SE_M_SAND_TOMB}you.\p"
	.string "{PLAYER}!\p"
	.string "{SE_M_HEAL_BELL}kne{SE_M_TWISTER}tha{SE_M_SPIT_UP}you{SE_M_SUPERSONIC}wit{SE_M_TRI_ATTACK}you{SE_M_SAND_TOMB}skills,\n"
	.string "woul{SE_M_WATERFALL}eventuall{SE_M_YAWN}reac{SE_M_TRI_ATTACK}m{SE_M_REVERSAL}here.\p"
	.string "There'{SE_M_GRASSWHISTLE}n{SE_M_ATTRACT2}nee{SE_M_WATERFALL}fo{SE_M_SAND_TOMB}word{SE_M_GRASSWHISTLE}now.\p"
	.string "W{SE_M_REVERSAL}wil{SE_M_BATON_PASS}battl{SE_M_REVERSAL}t{SE_M_ATTRACT2}determin{SE_M_REVERSAL}wh{SE_M_ATTRACT2}is\n"
	.string "th{SE_M_REVERSAL}stronge{SE_M_SAND_TOMB}o{SE_M_ACID_ARMOR}th{SE_M_REVERSAL}tw{SE_M_ATTRACT2}o{SE_M_ACID_ARMOR}us.\p"
	.string "A{SE_M_GRASSWHISTLE}th{SE_M_REVERSAL}mos{SE_M_SPIT_UP}powerfu{SE_M_BATON_PASS}traine{SE_M_SAND_TOMB}an{SE_M_WATERFALL}as\n"
	.string "th{SE_M_REVERSAL}POKéMO{SE_M_PSYBEAM2}LEAGU{SE_M_SWORDS_DANCE}CHAMPION…\p"
	.string "I{SE_M_SUPERSONIC}LANC{SE_M_SWORDS_DANCE}th{SE_M_REVERSAL}drago{SE_M_ATTRACT}master{SE_M_SUPERSONIC}accept\n"
	.string "you{SE_M_SAND_TOMB}challenge!$"

PokemonLeague_ChampionsRoom_Text_BattleWin:
	.string "…It'{SE_M_GRASSWHISTLE}over.\p"
	.string "Bu{SE_M_SPIT_UP}it'{SE_M_GRASSWHISTLE}a{SE_M_ATTRACT}od{SE_M_WATERFALL}feeling.\p"
	.string "I'{SE_M_MILK_DRINK}no{SE_M_SPIT_UP}angr{SE_M_YAWN}tha{SE_M_SPIT_UP}{SE_M_HEAL_BELL}lost{SE_M_PERISH_SONG}I{SE_M_ATTRACT}fact,\n"
	.string "{SE_M_HEAL_BELL}fee{SE_M_BATON_PASS}happy.\p"
	.string "Happ{SE_M_YAWN}tha{SE_M_SPIT_UP}{SE_M_HEAL_BELL}witnesse{SE_M_WATERFALL}th{SE_M_REVERSAL}rise\n"
	.string "o{SE_M_ACID_ARMOR}{SE_M_CHARGE}grea{SE_M_SPIT_UP}ne{SE_M_TWISTER}CHAMPION!$"

PokemonLeague_ChampionsRoom_Text_BattleAfter:
	.string "…Whew.\p"
	.string "Yo{SE_M_DIVE}hav{SE_M_REVERSAL}becom{SE_M_REVERSAL}trul{SE_M_YAWN}powerful,\n"
	.string "{PLAYER}.\p"
	.string "You{SE_M_SAND_TOMB}POKéMO{SE_M_PSYBEAM2}hav{SE_M_REVERSAL}responde{SE_M_WATERFALL}t{SE_M_ATTRACT2}your\n"
	.string "stron{SE_M_SANDSTORM}an{SE_M_WATERFALL}upstandin{SE_M_SANDSTORM}nature.\p"
	.string "A{SE_M_GRASSWHISTLE}{SE_M_CHARGE}trainer{SE_M_SUPERSONIC}yo{SE_M_DIVE}wil{SE_M_BATON_PASS}continu{SE_M_REVERSAL}to\n"
	.string "gro{SE_M_TWISTER}stron{SE_M_SANDSTORM}wit{SE_M_TRI_ATTACK}you{SE_M_SAND_TOMB}POKéMON.$"

PokemonLeague_ChampionsRoom_Text_MaryOhNoOak:
	.string "MARY{SE_M_HEAT_WAVE}Oh{SE_M_SUPERSONIC}no{SE_M_DRAGON_RAGE}It'{SE_M_GRASSWHISTLE}al{SE_M_BATON_PASS}over!\p"
	.string "PROF.OAK{SE_M_SUPERSONIC}i{SE_M_ACID_ARMOR}yo{SE_M_DIVE}weren'{SE_M_SPIT_UP}s{SE_M_ATTRACT2}slow…$"

PokemonLeague_ChampionsRoom_Text_OakCongratulations:
	.string "PROF.OAK{SE_M_HEAT_WAVE}Ah{SE_M_SUPERSONIC}{PLAYER}!\p"
	.string "It'{SE_M_GRASSWHISTLE}bee{SE_M_ATTRACT}{SE_M_CHARGE}lon{SE_M_SANDSTORM}while.\p"
	.string "Yo{SE_M_DIVE}certainl{SE_M_YAWN}loo{SE_M_ENCORE2}mor{SE_M_REVERSAL}impressive.\p"
	.string "You{SE_M_SAND_TOMB}conques{SE_M_SPIT_UP}o{SE_M_ACID_ARMOR}th{SE_M_REVERSAL}JOHT{SE_M_SOLAR_BEAM}LEAGUE\n"
	.string "i{SE_M_GRASSWHISTLE}jus{SE_M_SPIT_UP}fantastic!\p"
	.string "You{SE_M_SAND_TOMB}dedication{SE_M_SUPERSONIC}trus{SE_M_SPIT_UP}an{SE_M_WATERFALL}lov{SE_M_REVERSAL}for\n"
	.string "you{SE_M_SAND_TOMB}POKéMO{SE_M_PSYBEAM2}mad{SE_M_REVERSAL}thi{SE_M_GRASSWHISTLE}happen.\p"
	.string "You{SE_M_SAND_TOMB}POKéMO{SE_M_PSYBEAM2}wer{SE_M_REVERSAL}outstandin{SE_M_SANDSTORM}too.\p"
	.string "Becaus{SE_M_REVERSAL}the{SE_M_YAWN}believe{SE_M_WATERFALL}i{SE_M_ATTRACT}yo{SE_M_DIVE}a{SE_M_GRASSWHISTLE}a\n"
	.string "trainer{SE_M_SUPERSONIC}the{SE_M_YAWN}persevered.\p"
	.string "Congratulations{SE_M_SUPERSONIC}{PLAYER}!$"

PokemonLeague_ChampionsRoom_Text_RematchOakCongratulations:
	.string "PROF.OAK{SE_M_HEAT_WAVE}Anothe{SE_M_SAND_TOMB}fin{SE_M_REVERSAL}victory,\n"
	.string "{PLAYER}!\p"
	.string "You{SE_M_SAND_TOMB}journey{SE_M_GRASSWHISTLE}throug{SE_M_TRI_ATTACK}KANT{SE_M_SOLAR_BEAM}and\n"
	.string "JOHT{SE_M_SOLAR_BEAM}hav{SE_M_REVERSAL}brough{SE_M_SPIT_UP}yo{SE_M_DIVE}far.\p"
	.string "Th{SE_M_REVERSAL}trus{SE_M_SPIT_UP}betwee{SE_M_ATTRACT}yo{SE_M_DIVE}an{SE_M_WATERFALL}your\n"
	.string "POKéMO{SE_M_PSYBEAM2}keep{SE_M_GRASSWHISTLE}growing.\p"
	.string "Congratulation{SE_M_GRASSWHISTLE}o{SE_M_ATTRACT}you{SE_M_SAND_TOMB}return\n"
	.string "t{SE_M_ATTRACT2}th{SE_M_REVERSAL}JOHT{SE_M_SOLAR_BEAM}LEAGUE!$"

PokemonLeague_ChampionsRoom_Text_MaryInterview:
	.string "MARY{SE_M_HEAT_WAVE}Let'{SE_M_GRASSWHISTLE}intervie{SE_M_TWISTER}th{SE_M_REVERSAL}bran{SE_M_WATERFALL}new\n"
	.string "JOHT{SE_M_SOLAR_BEAM}CHAMPION!$"

PokemonLeague_ChampionsRoom_Text_RematchMaryInterview:
	.string "MARY{SE_M_HEAT_WAVE}Let'{SE_M_GRASSWHISTLE}intervie{SE_M_TWISTER}JOHTO's\n"
	.string "returnin{SE_M_SANDSTORM}CHAMPION{SE_M_SUPERSONIC}{PLAYER}!$"

PokemonLeague_ChampionsRoom_Text_Noisy:
	.string "LANCE{SE_M_HEAT_WAVE}Thi{SE_M_GRASSWHISTLE}i{SE_M_GRASSWHISTLE}gettin{SE_M_SANDSTORM}t{SE_M_ATTRACT2}b{SE_M_REVERSAL}{SE_M_CHARGE}bit\n"
	.string "to{SE_M_ATTRACT2}noisy…\p"
	.string "{PLAYER}{SE_M_SUPERSONIC}coul{SE_M_WATERFALL}yo{SE_M_DIVE}com{SE_M_REVERSAL}wit{SE_M_TRI_ATTACK}me?$"

PokemonLeague_ChampionsRoom_Text_MaryNoInterview:
	.string "MARY{SE_M_HEAT_WAVE}Oh{SE_M_SUPERSONIC}wait{SE_M_DRAGON_RAGE}W{SE_M_REVERSAL}haven'{SE_M_SPIT_UP}done\n"
	.string "th{SE_M_REVERSAL}interview!$"

PokemonLeague_ChampionsRoom_Text_RematchMaryNoInterview:
	.string "MARY{SE_M_HEAT_WAVE}Com{SE_M_REVERSAL}on{SE_M_DRAGON_RAGE}Yo{SE_M_DIVE}can'{SE_M_SPIT_UP}blo{SE_M_TWISTER}off\n"
	.string "th{SE_M_REVERSAL}intervie{SE_M_TWISTER}AGAIN!$"

