@ Johto (data/maps/SinjohRuins_ArceusRoom_hns/scripts.inc), as built into the FireRed game.

SinjohRuins_ArceusRoom_hns_MapScripts::
	map_script 3, SinjohRuins_ArceusRoom_OnTransition
	.byte 0

SinjohRuins_ArceusRoom_OnTransition::
	call_if_ge 20639, 11, SinjohRuins_ArceusRoom_MoveArceus
	end

SinjohRuins_ArceusRoom_MoveArceus::
	setobjectxyperm 1, 18, 18
	return

SinjohRuins_ArceusRoom_TriggerRight::
	lock
	playse 209
	dofieldeffectsparkle 19, 24, 0
	waitfieldeffect 54
	goto SinjohRuins_ArceusRoom_TriggerScene

SinjohRuins_ArceusRoom_TriggerLeft::
	lock
	playse 209
	dofieldeffectsparkle 17, 24, 0
	waitfieldeffect 54
	goto SinjohRuins_ArceusRoom_TriggerScene

SinjohRuins_ArceusRoom_TriggerMid::
	lock
	playse 209
	dofieldeffectsparkle 18, 24, 0
	waitfieldeffect 54
	goto SinjohRuins_ArceusRoom_TriggerScene

SinjohRuins_ArceusRoom_TriggerScene::

	playse 21
	applymovement2 255, J_Common_Movement_ExclamationMark
	delay 55
	waitmovement 255
	msgbox SinjohRuins_Lab_Text_PlayFlute, MSGBOX_YESNO
	closemessage
	goto_if_eq 32781, FALSE, SinjohRuins_Lab_EventScript_NoOp

	playbgm ((((558 + 1) + 0xAF) + 1) + 0x00), FALSE
	applymovement2 255, SinjohRuins_ArceusRoom_Movement_WalkSlowUp
	waitmovement 0
	setvar 32781, 3
	playse 107
	special DoOrbEffect

	delay 200
	applymovement2 255, SinjohRuins_ArceusRoom_Movement_Dance
	applymovement2 0xFE, SinjohRuins_ArceusRoom_Movement_Dance
	delay 400
	waitmovement 0
	waitmovement 0xFE
	special FadeOutOrbEffect

	setweather 2
	doweather
	playse 87
	delay 80
	setvar 32772, 1
	setvar 32773, 1
	setvar 32774, 15
	setvar 32775, 6
	special ShakeCamera
	waitstate
	delay 80
	playse 87
	fadescreen 3
	addobject 1
	clearflag 9124

	playse 87
	applymovement2 1, SinjohRuins_ArceusRoom_Movement_ArceusWalkDown
	playfanfare 388
	fadescreen 2
	playmoncry 493, 0
	delay 20
	waitmovement 1
	setvar 32772, 0
	setvar 32773, 1
	setvar 32774, 6
	setvar 32775, 2
	special ShakeCamera
	waitstate
	waitmoncry
	delay 8
	playse 21
	applymovement 255, J_Common_Movement_ExclamationMark
	delay 55
	waitmovement 255
	setweather 0
	doweather
	applymovement2 1, SinjohRuins_ArceusRoom_Movement_ArceusLooksAround
	playmoncry 493, 0
	waitmovement 0
	playmoncry 493, 0
	waitmoncry
	fadedefaultbgm
	setobjectxyperm 1, 18, 18
	setvar 20639, 11
	release
	end

SinjohRuins_ArceusRoom_Movement_ArceusLooksAround:
	walk_in_place_down
	delay_16
	delay_16
	delay_16
	delay_16
	walk_in_place_left
	delay_16
	delay_16
	delay_16
	delay_16
	walk_in_place_right
	delay_16
	delay_16
	delay_16
	delay_16
	walk_in_place_down
	walk_in_place_fast_down
	step_end

SinjohRuins_ArceusRoom_Movement_Dance:
	face_right
	delay_8
	face_up
	delay_8
	face_left
	delay_8
	face_down
	delay_8
	face_right
	delay_8
	face_up
	delay_8
	face_left
	delay_8
	face_down
	delay_8
	face_right
	delay_8
	face_up
	face_left
	delay_8
	face_down
	delay_8
	face_right
	delay_8
	face_up
	delay_8
	face_left
	delay_8
	face_down
	delay_8
	face_right
	delay_8
	face_up
	face_left
	delay_8
	face_down
	delay_8
	face_right
	delay_8
	face_up
	delay_8
	face_left
	delay_8
	face_down
	delay_8
	face_right
	delay_8
	face_up
	face_left
	delay_8
	face_down
	delay_8
	face_right
	delay_8
	face_up
	delay_8
	face_left
	delay_8
	face_down
	delay_8
	face_right
	delay_8
	face_up
	delay_8
	face_left
	delay_8
	face_down
	delay_8
	face_right
	delay_8
	face_up
	delay_8
	face_left
	delay_8
	face_down
	delay_8
	face_right
	delay_8
	face_up
	face_left
	delay_8
	face_down
	delay_8
	face_right
	delay_8
	face_up
	delay_8
	face_left
	delay_8
	face_down
	delay_8
	face_right
	delay_8
	face_up
	face_left
	delay_8
	face_down
	delay_8
	face_right
	delay_8
	face_up
	delay_8
	face_left
	delay_8
	face_down
	delay_8
	face_right
	delay_8
	face_up
	face_left
	delay_8
	face_down
	delay_8
	face_right
	delay_8
	face_up
	delay_8
	face_left
	delay_8
	face_down
	delay_8
	face_right
	delay_8
	face_up
	step_end

SinjohRuins_ArceusRoom_Movement_ArceusWalkDown:
	slide_down
	slide_down
	slide_down
	slide_down
	slide_down
	slide_down
	slide_down
	step_end

SinjohRuins_ArceusRoom_Movement_WalkSlowUp:
	walk_slow_up
	walk_slow_up
	walk_slow_up
	walk_slow_up
	step_end

SinjohRuins_ArceusRoom_EventScript_Arceus::
	lock
	faceplayer
	goto_if_ge 20639, 12, SinjohRuins_ArceusRoom_EventScript_ArceusPhase2
	playmoncry 493, 2
	msgbox SinjohRuins_ArceusRoom_Text_CryArceus, MSGBOX_AUTOCLOSE
	delay 40
	waitmoncry
	setflag 2411
	setflag 2410
	setflag 2409
	setflag 8804
	setwildbossbattle species=1080, level=100, item=ITEM_IRON_PLATE, move1_1=MOVE_JUDGMENT, move1_2=MOVE_HYDRO_PUMP, move1_3=MOVE_RECOVER move1_4=MOVE_DAZZLING_GLEAM
	settotemboost B_POSITION_OPPONENT_LEFT, 2, 2, 0, 2, 2, 2
	special BattleSetup_StartLegendaryBattle
	playbgm ((558 + 1) + 0x90), 0
	waitstate
	specialvar 32781, GetBattleOutcome
	goto_if_eq 32781, 4, SinjohRuins_ArceusRoom_EventScript_ArceusRan
	setvar 20639, 12
	clearflag 2411
	clearflag 2410
	clearflag 2409
	clearflag 8804

SinjohRuins_ArceusRoom_EventScript_ArceusPhase2::
	playmoncry 493, 2
	msgbox SinjohRuins_ArceusRoom_Text_CryArceus2, MSGBOX_AUTOCLOSE
	delay 40
	waitmoncry
	setwildbossbattle species=493, level=80, item=ITEM_NONE, move1_1=MOVE_EXTREME_SPEED, move1_2=MOVE_EARTH_POWER, move1_3=MOVE_RECOVER move1_4=MOVE_HYPER_BEAM

	special BattleSetup_StartLegendaryBattle
	playbgm ((558 + 1) + 0x90), 0
	waitstate
	specialvar 32781, GetBattleOutcome
	goto_if_eq 32781, 4, SinjohRuins_ArceusRoom_EventScript_ArceusRan
	fadescreenswapbuffers 1
	removeobject 1
	setflag 9124
	special GivePartyMonSkyRibbon
	fadescreenswapbuffers 0
	release
	end

SinjohRuins_ArceusRoom_EventScript_ArceusRan::
	release
	end

SinjohRuins_ArceusRoom_Text_CryArceus:
	.string "ARCEUS{SE_M_HEAT_WAVE}Dodogyuuun!$"

SinjohRuins_ArceusRoom_Text_CryArceus2:
	.string "ARCEUS{SE_M_HEAT_WAVE}Dodogyuuun!\p"
	.string "Th{SE_M_REVERSAL}ARCEU{SE_M_SKETCH}i{SE_M_GRASSWHISTLE}weakened...\n"
	.string "Ca{SE_M_ATTRACT}b{SE_M_REVERSAL}caught?$"

SinjohRuins_ArceusRoom_TriggerSteven::
	lock
	addobject 2
	applymovement2 2, SinjohRuins_ArceusRoom_Movement_StevenWalkUp
	waitmovement 0
	msgbox SinjohRuins_ArceusRoom_Text_StevenCongrats, MSGBOX_AUTOCLOSE
	applymovement2 2, SinjohRuins_ArceusRoom_Movement_StevenWalkDown
	waitmovement 0
	removeobject 2
	playse 9
	setflag 9122
	clearflag 9126
	setvar 20639, 13
	release
	end

SinjohRuins_ArceusRoom_Movement_StevenWalkUp:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

SinjohRuins_ArceusRoom_Movement_StevenWalkDown:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_in_place_down
	step_end

SinjohRuins_ArceusRoom_Text_StevenCongrats:
	.string "STEVEN{SE_M_HEAT_WAVE}Yo{SE_M_DIVE}di{SE_M_WATERFALL}it{SE_M_SUPERSONIC}{PLAYER}!\p"
	.string "Tha{SE_M_SPIT_UP}battl{SE_M_REVERSAL}wa{SE_M_GRASSWHISTLE}breathtaking.\p"
	.string "Seein{SE_M_SANDSTORM}you{SE_M_SAND_TOMB}powe{SE_M_SAND_TOMB}mad{SE_M_REVERSAL}m{SE_M_REVERSAL}realize.\p"
	.string "Th{SE_M_REVERSAL}KIMON{SE_M_SOLAR_BEAM}GIRL{SE_M_SKETCH}didn'{SE_M_SPIT_UP}sen{SE_M_WATERFALL}you\n"
	.string "t{SE_M_ATTRACT2}hel{SE_M_MORNING_SUN}ou{SE_M_SAND_TOMB}research.\p"
	.string "{SE_M_HEAL_BELL}thin{SE_M_ENCORE2}the{SE_M_YAWN}sen{SE_M_SPIT_UP}yo{SE_M_DIVE}because\n"
	.string "yo{SE_M_DIVE}wer{SE_M_REVERSAL}th{SE_M_REVERSAL}onl{SE_M_YAWN}on{SE_M_REVERSAL}worth{SE_M_YAWN}of\l"
	.string "tamin{SE_M_SANDSTORM}th{SE_M_REVERSAL}legendar{SE_M_YAWN}POKéMON.\p"
	.string "The{SE_M_YAWN}didn'{SE_M_SPIT_UP}trus{SE_M_SPIT_UP}m{SE_M_YAWN}tea{SE_M_MILK_DRINK}an{SE_M_WATERFALL}I\n"
	.string "t{SE_M_ATTRACT2}handl{SE_M_REVERSAL}it.\p"
	.string "An{SE_M_WATERFALL}afte{SE_M_SAND_TOMB}wha{SE_M_SPIT_UP}I'v{SE_M_REVERSAL}jus{SE_M_SPIT_UP}seen...\p"
	.string "{SE_M_HEAL_BELL}thin{SE_M_ENCORE2}the{SE_M_YAWN}wer{SE_M_REVERSAL}right.\p"
	.string "I'v{SE_M_REVERSAL}brough{SE_M_SPIT_UP}{SE_M_CHARGE}lo{SE_M_SPIT_UP}o{SE_M_ACID_ARMOR}unwanted\n"
	.string "attentio{SE_M_ATTRACT}t{SE_M_ATTRACT2}thi{SE_M_GRASSWHISTLE}town.\p"
	.string "{SE_M_HEAL_BELL}thin{SE_M_ENCORE2}I'l{SE_M_BATON_PASS}spen{SE_M_WATERFALL}som{SE_M_REVERSAL}time\n"
	.string "wit{SE_M_TRI_ATTACK}th{SE_M_REVERSAL}locals.\p"
	.string "Afte{SE_M_SAND_TOMB}al{SE_M_BATON_PASS}o{SE_M_ACID_ARMOR}this{SE_M_SUPERSONIC}yo{SE_M_DIVE}an{SE_M_WATERFALL}your\n"
	.string "POKéMO{SE_M_PSYBEAM2}deserv{SE_M_REVERSAL}som{SE_M_REVERSAL}rest.\p"
	.string "I'l{SE_M_BATON_PASS}b{SE_M_REVERSAL}a{SE_M_SPIT_UP}th{SE_M_REVERSAL}villag{SE_M_REVERSAL}i{SE_M_ACID_ARMOR}yo{SE_M_DIVE}nee{SE_M_WATERFALL}me.\p"
	.string "Fufufu{SE_M_SUPERSONIC}wha{SE_M_SPIT_UP}coul{SE_M_WATERFALL}yo{SE_M_DIVE}nee{SE_M_WATERFALL}fro{SE_M_MILK_DRINK}me?$"

