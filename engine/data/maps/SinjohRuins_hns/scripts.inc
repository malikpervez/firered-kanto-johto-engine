@ Johto (data/maps/SinjohRuins_hns/scripts.inc), as built into the FireRed game.

SinjohRuins_hns_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, SinjohRuins_OnFrame
	map_script MAP_SCRIPT_ON_TRANSITION, SinjohRuins_hns_OnTransition
	map_script MAP_SCRIPT_ON_LOAD, SinjohRuins_hns_OnLoad
	.byte 0

SinjohRuins_OnFrame::
	map_script_2 JOHTO_VAR_SINJOH_STORYLINE, 8, SinjohRuins_StairsScene
	.2byte 0

SinjohRuins_hns_OnTransition::
	call_if_eq JOHTO_VAR_SINJOH_STORYLINE, 9, SinjohRuins_StevenLanding
	call_if_eq JOHTO_VAR_SINJOH_STORYLINE, 10, SinjohRuins_StevenLanding
	call_if_eq JOHTO_VAR_SINJOH_STORYLINE, 11, SinjohRuins_StevenLanding
	call_if_eq JOHTO_VAR_SINJOH_STORYLINE, 12, SinjohRuins_StevenLanding
	callnative SetTimeBasedEncounters
	end

SinjohRuins_StevenLanding::
	setobjectxyperm LOCALID_SINJOHRUINS_STEVEN, 24, 31
	setobjectmovementtype LOCALID_SINJOHRUINS_STEVEN, MOVEMENT_TYPE_FACE_UP
	return

SinjohRuins_hns_OnLoad::
	call_if_ge JOHTO_VAR_PLATECOUNTER, 3, SinjohRuins_OpenRegirock
	call_if_ge JOHTO_VAR_PLATECOUNTER, 6, SinjohRuins_OpenRegice
	call_if_ge JOHTO_VAR_PLATECOUNTER, 9, SinjohRuins_OpenRegisteel
	call_if_ge JOHTO_VAR_PLATECOUNTER, 12, SinjohRuins_OpenRegieleki
	call_if_ge JOHTO_VAR_PLATECOUNTER, 15, SinjohRuins_OpenRegidrago
	call_if_ge JOHTO_VAR_PLATECOUNTER, 17, SinjohRuins_OpenArceus
	end

SinjohRuins_OpenRegirock::
	setmetatile 9, 44, 0x378, FALSE
	setmetatile 8, 44, 0x0BE, TRUE
	return

SinjohRuins_OpenRegice::
	setmetatile 7, 48, 0x370, FALSE
	setmetatile 6, 48, 0x0BE, TRUE
	return

SinjohRuins_OpenRegisteel::
	setmetatile 8, 54, 0x370, FALSE
	setmetatile 7, 54, 0x0BE, TRUE
	return

SinjohRuins_OpenRegieleki::
	setmetatile 38, 44, 0x371, FALSE
	setmetatile 39, 44, 0x0BD, TRUE
	return

SinjohRuins_OpenRegidrago::
	setmetatile 37, 49, 0x371, FALSE
	setmetatile 38, 49, 0x0BD, TRUE
	return

SinjohRuins_OpenArceus::

	setmetatile 17, 32, 0x089, FALSE
	setmetatile 17, 33, 0x089, FALSE
	setmetatile 17, 34, 0x089, FALSE
	setmetatile 17, 35, 0x089, FALSE
	setmetatile 17, 36, 0x089, FALSE
	setmetatile 18, 32, 0x091, FALSE
	setmetatile 18, 33, 0x091, FALSE
	setmetatile 18, 34, 0x091, FALSE
	setmetatile 18, 35, 0x091, FALSE
	setmetatile 18, 36, 0x091, FALSE
	setmetatile 19, 32, 0x091, FALSE
	setmetatile 19, 33, 0x091, FALSE
	setmetatile 19, 34, 0x091, FALSE
	setmetatile 19, 35, 0x091, FALSE
	setmetatile 19, 36, 0x091, FALSE

	setmetatile 29, 32, 0x089, FALSE
	setmetatile 29, 33, 0x089, FALSE
	setmetatile 29, 34, 0x089, FALSE
	setmetatile 29, 35, 0x089, FALSE
	setmetatile 29, 36, 0x089, FALSE
	setmetatile 30, 32, 0x091, FALSE
	setmetatile 30, 33, 0x091, FALSE
	setmetatile 30, 34, 0x091, FALSE
	setmetatile 30, 35, 0x091, FALSE
	setmetatile 30, 36, 0x091, FALSE
	setmetatile 31, 32, 0x091, FALSE
	setmetatile 31, 33, 0x091, FALSE
	setmetatile 31, 34, 0x091, FALSE
	setmetatile 31, 35, 0x091, FALSE
	setmetatile 31, 36, 0x091, FALSE
	return

SinjohRuins_StairsScene::
	lock
	setvar VAR_0x8004, 2
	setvar VAR_0x8005, 2
	setvar VAR_0x8006, 40
	setvar VAR_0x8007, 3
	special ShakeCamera
	applymovement LOCALID_PLAYER, SinjohRuins_Movement_PlayerWalkRight
	opendoor 14, 52
	waitdooranim
	addobject LOCALID_SINJOHRUINS_STEVEN
	clearflag JOHTO_FLAG_HIDE_SINJOHRUINS_STEVEN
	applymovement LOCALID_SINJOHRUINS_STEVEN, J_Common_Movement_WalkDown1
	waitmovement LOCALID_SINJOHRUINS_STEVEN
	applymovement LOCALID_SINJOHRUINS_STEVEN, SinjohRuins_Movement_StevenWalkRight
	waitmovement 0
	closedoor 14, 52
	waitdooranim
	setvar VAR_0x8004, 2
	setvar VAR_0x8005, 2
	setvar VAR_0x8006, 40
	setvar VAR_0x8007, 3
	special ShakeCamera
	waitstate
	waitmovement LOCALID_SINJOHRUINS_STEVEN
	waitmovement 0
	setvar VAR_0x8004, 2
	setvar VAR_0x8005, 2
	setvar VAR_0x8006, 40
	setvar VAR_0x8007, 3
	special ShakeCamera
	waitstate
	special SpawnCameraObject
	applymovement OBJ_EVENT_ID_CAMERA, SinjohRuins_Movement_CameraPanUp
	waitmovement 0
	setvar VAR_0x8004, 2
	setvar VAR_0x8005, 2
	setvar VAR_0x8006, 40
	setvar VAR_0x8007, 3
	special ShakeCamera
	setobjectxyperm LOCALID_SINJOHRUINS_STEVEN, 19, 52
	setobjectmovementtype LOCALID_SINJOHRUINS_STEVEN, MOVEMENT_TYPE_FACE_UP
	call SinjohRuins_OpenArceus
	special DrawWholeMapView
	delay 60
	applymovement OBJ_EVENT_ID_CAMERA, SinjohRuins_Movement_CameraPanDown
	waitmovement 0
	special RemoveCameraObject
	msgbox SinjohRuins_Text_StevenGotoStairs1, MSGBOX_AUTOCLOSE
	turnobject LOCALID_SINJOHRUINS_STEVEN, DIR_EAST
	delay 10
	turnobject LOCALID_PLAYER, DIR_WEST
	msgbox SinjohRuins_Text_StevenGotoStairs2, MSGBOX_AUTOCLOSE
	setvar JOHTO_VAR_SINJOH_STORYLINE, 9
	setvar JOHTO_VAR_PLATECOUNTER, 17
	applymovement LOCALID_SINJOHRUINS_STEVEN, SinjohRuins_Movement_StevenGoesToStairs
	waitmovement 0
	removeobject LOCALID_SINJOHRUINS_STEVEN
	setobjectxyperm LOCALID_SINJOHRUINS_STEVEN, 24, 31
	setobjectmovementtype LOCALID_SINJOHRUINS_STEVEN, MOVEMENT_TYPE_FACE_UP
	addobject LOCALID_SINJOHRUINS_STEVEN
	clearflag JOHTO_FLAG_HIDE_SINJOHRUINS_STEVEN
	setflag JOHTO_FLAG_HIDE_SINJOHRUINS_LAB_STEVEN
	setvar JOHTO_VAR_SINJOH_STORYLINE, 9
	release
	end

SinjohRuins_Text_StevenGotoStairs1:
	.string "STEVEN{SE_M_HEAT_WAVE}Thi{SE_M_GRASSWHISTLE}coul{SE_M_WATERFALL}onl{SE_M_YAWN}mea{SE_M_ATTRACT}on{SE_M_REVERSAL}thing.$"

SinjohRuins_Text_StevenGotoStairs2:
	.string "{PLAYER}{SE_M_PERISH_SONG}W{SE_M_REVERSAL}wer{SE_M_REVERSAL}abl{SE_M_REVERSAL}t{SE_M_ATTRACT2}decipher\n"
	.string "th{SE_M_REVERSAL}res{SE_M_SPIT_UP}o{SE_M_ACID_ARMOR}th{SE_M_REVERSAL}glyphs...\p"
	.string "I{SE_M_ACID_ARMOR}th{SE_M_REVERSAL}translatio{SE_M_ATTRACT}i{SE_M_GRASSWHISTLE}right{SE_M_SUPERSONIC}\n"
	.string "th{SE_M_REVERSAL}POKéMO{SE_M_PSYBEAM2}a{SE_M_SPIT_UP}th{SE_M_REVERSAL}to{SE_M_MORNING_SUN}o{SE_M_ACID_ARMOR}that\l"
	.string "staircas{SE_M_REVERSAL}i{SE_M_GRASSWHISTLE}th{SE_M_REVERSAL}mos{SE_M_SPIT_UP}powerful\l"
	.string "bein{SE_M_SANDSTORM}i{SE_M_ATTRACT}th{SE_M_REVERSAL}universe.\p"
	.string "An{SE_M_WATERFALL}i{SE_M_SPIT_UP}i{SE_M_GRASSWHISTLE}m{SE_M_YAWN}dut{SE_M_YAWN}a{SE_M_GRASSWHISTLE}former\n"
	.string "CHAMPIO{SE_M_PSYBEAM2}o{SE_M_ACID_ARMOR}th{SE_M_REVERSAL}HOEN{SE_M_PSYBEAM2}LEAGUE\l"
	.string "t{SE_M_ATTRACT2}mak{SE_M_REVERSAL}sur{SE_M_REVERSAL}yo{SE_M_DIVE}ar{SE_M_REVERSAL}strong\l"
	.string "enoug{SE_M_TRI_ATTACK}t{SE_M_ATTRACT2}fac{SE_M_REVERSAL}it.\p"
	.string "Mee{SE_M_SPIT_UP}m{SE_M_REVERSAL}a{SE_M_SPIT_UP}tha{SE_M_SPIT_UP}landing\n"
	.string "whe{SE_M_ATTRACT}yo{SE_M_DIVE}ar{SE_M_REVERSAL}ready.$"

SinjohRuins_Movement_StevenGoesToStairs:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_right
	walk_diag_southeast
	walk_diag_southeast
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

SinjohRuins_Movement_CameraPanDown:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_diag_southwest
	walk_diag_southwest
	walk_diag_southwest
	walk_diag_southwest
	step_end

SinjohRuins_Movement_CameraPanUp:
	walk_diag_northeast
	walk_diag_northeast
	walk_diag_northeast
	walk_diag_northeast
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

SinjohRuins_Movement_StevenWalkRight:
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_up
	step_end

SinjohRuins_Movement_PlayerWalkRight:
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_up
	step_end

SinjohRuins_EventScript_TriggerStevenBattleRight::
	lock
	turnobject LOCALID_SINJOHRUINS_STEVEN, DIR_EAST
	msgbox SinjohRuins_Text_StevenReadytoBattle, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, FALSE, SinjohRuins_EventScript_TriggerPlayerLeaveRight
	call SinjohRuins_EventScript_StevenBattle
	setvar JOHTO_VAR_SINJOH_STORYLINE, 10
	release
	end

SinjohRuins_EventScript_TriggerPlayerLeaveRight::
	closemessage
	applymovement LOCALID_PLAYER, J_Common_Movement_WalkRight1
	waitmovement 0
	release
	end

SinjohRuins_EventScript_TriggerStevenBattleLeft::
	lock
	turnobject LOCALID_SINJOHRUINS_STEVEN, DIR_WEST
	msgbox SinjohRuins_Text_StevenReadytoBattle, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, FALSE, SinjohRuins_EventScript_TriggerPlayerLeaveLeft
	call SinjohRuins_EventScript_StevenBattle
	setvar JOHTO_VAR_SINJOH_STORYLINE, 10
	release
	end

SinjohRuins_EventScript_TriggerPlayerLeaveLeft::
	closemessage
	applymovement LOCALID_PLAYER, J_Common_Movement_WalkLeft1
	waitmovement 0
	release
	end

SinjohRuins_Movement_StevenLeaveRight:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

SinjohRuins_Movement_StevenLeaveLeft:
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

SinjohRuins_EventScript_StevenBattle::
	msgbox SinjohRuins_Text_ChallengeSteven, MSGBOX_AUTOCLOSE
	trainerbattle_no_intro TRAINER_JOHTO_STEVEN_HNS, SinjohRuins_Text_StevenDefeat
	msgbox SinjohRuins_Text_StevenAfterBattle, MSGBOX_AUTOCLOSE
	giveitem ITEM_STONE_PLATE
	msgbox SinjohRuins_Text_HealParty, MSGBOX_AUTOCLOSE
	fadescreenswapbuffers FADE_TO_BLACK
	special HealPlayerParty
	closemessage
	playfanfare MUS_HEAL
	waitfanfare
	fadescreenswapbuffers FADE_FROM_BLACK
	msgbox SinjohRuins_Text_StevenAfterPlate, MSGBOX_AUTOCLOSE
	return

SinjohRuins_Text_HealParty::
	.string "STEVEN{SE_M_HEAT_WAVE}Le{SE_M_SPIT_UP}m{SE_M_REVERSAL}hea{SE_M_BATON_PASS}you{SE_M_SAND_TOMB}POKéMON\n"
	.string "befor{SE_M_REVERSAL}yo{SE_M_DIVE}go.$"

SinjohRuins_Text_StevenAfterPlate:
	.string "STEVEN{SE_M_HEAT_WAVE}Goo{SE_M_WATERFALL}luck{SE_M_SUPERSONIC}{PLAYER}\p"
	.string "G{SE_M_ATTRACT2}on{SE_M_SUPERSONIC}I'{SE_M_MILK_DRINK}righ{SE_M_SPIT_UP}behin{SE_M_WATERFALL}you.$"

SinjohRuins_Text_StevenAfterBattle:
	.string "STEVEN{SE_M_HEAT_WAVE}T{SE_M_ATTRACT2}think{SE_M_SUPERSONIC}anothe{SE_M_SAND_TOMB}traine{SE_M_SAND_TOMB}\n"
	.string "woul{SE_M_WATERFALL}defea{SE_M_SPIT_UP}m{SE_M_REVERSAL}lik{SE_M_REVERSAL}this.\p"
	.string "Incredible.\p"
	.string "Tak{SE_M_REVERSAL}this{SE_M_SUPERSONIC}it'{SE_M_GRASSWHISTLE}th{SE_M_REVERSAL}fina{SE_M_BATON_PASS}plate.$"

SinjohRuins_Text_StevenReadytoBattle:
	.string "STEVEN{SE_M_HEAT_WAVE}{PLAYER}.\p"
	.string "Eve{SE_M_SAND_TOMB}sinc{SE_M_REVERSAL}{SE_M_HEAL_BELL}firs{SE_M_SPIT_UP}sa{SE_M_TWISTER}the\n"
	.string "determinatio{SE_M_ATTRACT}i{SE_M_ATTRACT}you{SE_M_SAND_TOMB}eyes,\l"
	.string "{SE_M_HEAL_BELL}fel{SE_M_SPIT_UP}i{SE_M_SPIT_UP}woul{SE_M_WATERFALL}lea{SE_M_WATERFALL}t{SE_M_ATTRACT2}this.\p"
	.string "{SE_M_HEAL_BELL}wil{SE_M_BATON_PASS}tes{SE_M_SPIT_UP}th{SE_M_REVERSAL}bon{SE_M_WATERFALL}betwee{SE_M_ATTRACT}you\n"
	.string "an{SE_M_WATERFALL}you{SE_M_SAND_TOMB}POKéMON.\p"
	.string "Ar{SE_M_REVERSAL}yo{SE_M_DIVE}ready?$"

SinjohRuins_Text_ChallengeSteven:
	.string "Okay{SE_M_SUPERSONIC}{PLAYER}{KUN}{SE_M_SUPERSONIC}i{SE_M_ACID_ARMOR}you'r{SE_M_REVERSAL}goin{SE_M_SANDSTORM}t{SE_M_ATTRACT2}mount\n"
	.string "{SE_M_CHARGE}seriou{SE_M_GRASSWHISTLE}challenge{SE_M_SUPERSONIC}expec{SE_M_SPIT_UP}th{SE_M_REVERSAL}worst!$"

SinjohRuins_Text_StevenDefeat:
	.string "You...\n"
	.string "Yo{SE_M_DIVE}ar{SE_M_REVERSAL}ready.$"

SinjohRuins_EventScript_Steven::
	msgbox SinjohRuins_Text_StevenAfterPlate, MSGBOX_NPC
	end

SinjohRuins_EventScript_Sign::
	msgbox SinjohRuins_Text_Sign, MSGBOX_SIGN
	end

SinjohRuins_Text_Sign:
	.string "SINJO{SE_M_SWAGGER2}RUINS$"

