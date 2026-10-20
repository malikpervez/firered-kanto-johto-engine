@ Johto (data/maps/SinjohRuins_ArceusRoom_hns/scripts.inc), as built into the FireRed game.

SinjohRuins_ArceusRoom_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, SinjohRuins_ArceusRoom_OnTransition
	.byte 0

SinjohRuins_ArceusRoom_OnTransition::
	call_if_ge JOHTO_VAR_SINJOH_STORYLINE, 11, SinjohRuins_ArceusRoom_MoveArceus
	end

SinjohRuins_ArceusRoom_MoveArceus::
	setobjectxyperm LOCALID_SINJOHRUINS_ARCEUSROOM_ARCEUS, 18, 18
	return

SinjohRuins_ArceusRoom_TriggerRight::
	lock
	playse SE_M_DETECT
	dofieldeffectsparkle 19, 24, 0
	waitfieldeffect FLDEFF_SPARKLE
	goto SinjohRuins_ArceusRoom_TriggerScene

SinjohRuins_ArceusRoom_TriggerLeft::
	lock
	playse SE_M_DETECT
	dofieldeffectsparkle 17, 24, 0
	waitfieldeffect FLDEFF_SPARKLE
	goto SinjohRuins_ArceusRoom_TriggerScene

SinjohRuins_ArceusRoom_TriggerMid::
	lock
	playse SE_M_DETECT
	dofieldeffectsparkle 18, 24, 0
	waitfieldeffect FLDEFF_SPARKLE
	goto SinjohRuins_ArceusRoom_TriggerScene

SinjohRuins_ArceusRoom_TriggerScene::

	playse SE_PIN
	applymovement2 LOCALID_PLAYER, J_Common_Movement_ExclamationMark
	delay 55
	waitmovement LOCALID_PLAYER
	msgbox SinjohRuins_Lab_Text_PlayFlute, MSGBOX_YESNO
	closemessage
	goto_if_eq VAR_RESULT, FALSE, SinjohRuins_Lab_EventScript_NoOp

	playbgm ((((558 + 1) + 0xAF) + 1) + 0x00), FALSE
	applymovement2 LOCALID_PLAYER, SinjohRuins_ArceusRoom_Movement_WalkSlowUp
	waitmovement 0
	setvar VAR_RESULT, 3
	playse SE_ORB
	special DoOrbEffect

	delay 200
	applymovement2 LOCALID_PLAYER, SinjohRuins_ArceusRoom_Movement_Dance
	applymovement2 OBJ_EVENT_ID_FOLLOWER, SinjohRuins_ArceusRoom_Movement_Dance
	delay 400
	waitmovement 0
	waitmovement OBJ_EVENT_ID_FOLLOWER
	special FadeOutOrbEffect

	setweather WEATHER_SUNNY
	doweather
	playse SE_THUNDER
	delay 80
	setvar VAR_0x8004, 1
	setvar VAR_0x8005, 1
	setvar VAR_0x8006, 15
	setvar VAR_0x8007, 6
	special ShakeCamera
	waitstate
	delay 80
	playse SE_THUNDER
	fadescreen FADE_TO_WHITE
	addobject LOCALID_SINJOHRUINS_ARCEUSROOM_ARCEUS
	clearflag JOHTO_FLAG_HIDE_SINJOHRUINS_ARCEUSROOM_ARCEUS

	playse SE_THUNDER
	applymovement2 LOCALID_SINJOHRUINS_ARCEUSROOM_ARCEUS, SinjohRuins_ArceusRoom_Movement_ArceusWalkDown
	playfanfare MUS_AWAKEN_LEGEND
	fadescreen FADE_FROM_WHITE
	playmoncry SPECIES_ARCEUS, 0
	delay 20
	waitmovement LOCALID_SINJOHRUINS_ARCEUSROOM_ARCEUS
	setvar VAR_0x8004, 0
	setvar VAR_0x8005, 1
	setvar VAR_0x8006, 6
	setvar VAR_0x8007, 2
	special ShakeCamera
	waitstate
	waitmoncry
	delay 8
	playse SE_PIN
	applymovement LOCALID_PLAYER, J_Common_Movement_ExclamationMark
	delay 55
	waitmovement LOCALID_PLAYER
	setweather WEATHER_NONE
	doweather
	applymovement2 LOCALID_SINJOHRUINS_ARCEUSROOM_ARCEUS, SinjohRuins_ArceusRoom_Movement_ArceusLooksAround
	playmoncry SPECIES_ARCEUS, 0
	waitmovement 0
	playmoncry SPECIES_ARCEUS, 0
	waitmoncry
	fadedefaultbgm
	setobjectxyperm LOCALID_SINJOHRUINS_ARCEUSROOM_ARCEUS, 18, 18
	setvar JOHTO_VAR_SINJOH_STORYLINE, 11
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
	goto_if_ge JOHTO_VAR_SINJOH_STORYLINE, 12, SinjohRuins_ArceusRoom_EventScript_ArceusPhase2
	playmoncry SPECIES_ARCEUS, CRY_MODE_ENCOUNTER
	msgbox SinjohRuins_ArceusRoom_Text_CryArceus, MSGBOX_AUTOCLOSE
	delay 40
	waitmoncry
	setflag FLAG_NO_WILD_CATCHING
	setflag FLAG_NO_WILD_RUNNING
	setflag FLAG_SMART_WILD_AI
	setflag JOHTO_FLAG_NO_SHINY
	setwildbossbattle species=1080, level=100, item=ITEM_IRON_PLATE, move1_1=MOVE_JUDGMENT, move1_2=MOVE_HYDRO_PUMP, move1_3=MOVE_RECOVER move1_4=MOVE_DAZZLING_GLEAM
	settotemboost B_POSITION_OPPONENT_LEFT, 2, 2, 0, 2, 2, 2
	special BattleSetup_StartLegendaryBattle
	playbgm ((558 + 1) + 0x90), MUS_DUMMY
	waitstate
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, SinjohRuins_ArceusRoom_EventScript_ArceusRan
	setvar JOHTO_VAR_SINJOH_STORYLINE, 12
	clearflag FLAG_NO_WILD_CATCHING
	clearflag FLAG_NO_WILD_RUNNING
	clearflag FLAG_SMART_WILD_AI
	clearflag JOHTO_FLAG_NO_SHINY

SinjohRuins_ArceusRoom_EventScript_ArceusPhase2::
	playmoncry SPECIES_ARCEUS, CRY_MODE_ENCOUNTER
	msgbox SinjohRuins_ArceusRoom_Text_CryArceus2, MSGBOX_AUTOCLOSE
	delay 40
	waitmoncry
	setwildbossbattle species=493, level=80, item=ITEM_NONE, move1_1=MOVE_EXTREME_SPEED, move1_2=MOVE_EARTH_POWER, move1_3=MOVE_RECOVER move1_4=MOVE_HYPER_BEAM

	special BattleSetup_StartLegendaryBattle
	playbgm ((558 + 1) + 0x90), MUS_DUMMY
	waitstate
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, SinjohRuins_ArceusRoom_EventScript_ArceusRan
	fadescreenswapbuffers FADE_TO_BLACK
	removeobject LOCALID_SINJOHRUINS_ARCEUSROOM_ARCEUS
	setflag JOHTO_FLAG_HIDE_SINJOHRUINS_ARCEUSROOM_ARCEUS
	special GivePartyMonSkyRibbon
	fadescreenswapbuffers FADE_FROM_BLACK
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
	addobject LOCALID_SINJOHRUINS_ARCEUSROOM_STEVEN
	applymovement2 LOCALID_SINJOHRUINS_ARCEUSROOM_STEVEN, SinjohRuins_ArceusRoom_Movement_StevenWalkUp
	waitmovement 0
	msgbox SinjohRuins_ArceusRoom_Text_StevenCongrats, MSGBOX_AUTOCLOSE
	applymovement2 LOCALID_SINJOHRUINS_ARCEUSROOM_STEVEN, SinjohRuins_ArceusRoom_Movement_StevenWalkDown
	waitmovement 0
	removeobject LOCALID_SINJOHRUINS_ARCEUSROOM_STEVEN
	playse SE_EXIT
	setflag JOHTO_FLAG_HIDE_SINJOHRUINS_STEVEN
	clearflag JOHTO_FLAG_HIDE_NEWSINJOH_STEVEN
	setvar JOHTO_VAR_SINJOH_STORYLINE, 13
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

