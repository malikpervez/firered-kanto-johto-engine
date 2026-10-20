@ Johto (data/maps/SnowsweptCavern_hns/scripts.inc), as built into the FireRed game.

SnowsweptCavern_hns_MapScripts::
	map_script 3, SnowsweptCavern_hns_OnTransition
	.byte 0

SnowsweptCavern_hns_OnTransition::
	goto_if_ge 20639, 3, SnowsweptCavern_hns_SetBoulderLocation
	end

SnowsweptCavern_hns_SetBoulderLocation::
	setobjectxyperm 6, 38, 56
	end

Snowswept_Cavern_EventScript_ActivateSneasler::
	lock
	setobjectmovementtype 38, 0x40
	setobjectxyperm 38, 6, 24
	playse 209
	dofieldeffectsparkle 10, 28, 0
	waitfieldeffect 54
	playse 21
	applymovement2 255, J_Common_Movement_ExclamationMark
	delay 55
	waitmovement 255
	msgbox SinjohRuins_Lab_Text_PlayFlute, MSGBOX_YESNO
	closemessage
	goto_if_eq 32781, FALSE, SinjohRuins_Lab_EventScript_NoOp
	playbgm ((((558 + 1) + 0xAF) + 1) + 0x00), FALSE
	delay 200
	fadedefaultbgm
	addobject 38
	clearflag 9115

	applymovement2 38, Snowswept_Cavern_Movement_SpawnSneasler1
	delay 10
	playmoncry 461, 0
	waitmoncry
	playmoncry 461, 0
	waitmoncry
	waitmovement 0


	applymovement2 38, Snowswept_Cavern_Movement_SpawnSneasler2
	delay 10
	playse 10
	delay 20
	setvar 32772, 1
	setvar 32773, 1
	setvar 32774, 5
	setvar 32775, 2
	special ShakeCamera
	waitmovement 0

	setobjectxyperm 38, 5, 26

	setvar 20642, 2
	release
	end

Snowswept_Cavern_Movement_SpawnSneasler1:
	walk_in_place_fast_down
	jump_in_place_down
	jump_in_place_down
	jump_in_place_down
	jump_in_place_down
	step_end

Snowswept_Cavern_Movement_SpawnSneasler2:
	jump_2_down
	walk_in_place_down
	face_down
	step_end

Snowswept_Cavern_EventScript_Sneasler::
	lock
	faceplayer
	playmoncry 461, 2
	waitmoncry
	setwildbossbattle species=903, level=80, item=ITEM_RAZOR_CLAW, move1_1=MOVE_DIRE_CLAW, move1_2=MOVE_ROCK_SLIDE, move1_3=MOVE_BRICK_BREAK move1_4=MOVE_LASH_OUT
	settotemboost B_POSITION_OPPONENT_LEFT, 1, 0, 2, 0, 0, 0
	setflag 2411
	setflag 2410
	setflag 2409
	setflag 8804
	dowildbattle
	specialvar 32781, GetBattleOutcome
	goto_if_eq 32781, 4, Snowswept_Cavern_EventScript_SneaslerRan
	bufferspeciesname STR_VAR_1, 903
	msgbox SinjohRuins_Lab_Text_DropedItem, MSGBOX_DEFAULT
	giveitem ITEM_TOXIC_PLATE
	addvar 20640, 1
	fadescreenswapbuffers 1
	removeobject 38
	setflag 9115
	fadescreenswapbuffers 0
	call_if_eq 20640, 3, SinjohRuins_Lab_EventScript_3Plates
	call_if_eq 20640, 6, SinjohRuins_Lab_EventScript_6Plates
	call_if_eq 20640, 9, SinjohRuins_Lab_EventScript_9Plates
	call_if_eq 20640, 12, SinjohRuins_Lab_EventScript_12Plates
	call_if_eq 20640, 15, SinjohRuins_Lab_EventScript_15Plates
	call_if_eq 20640, 16, SinjohRuins_Lab_EventScript_16Plates
	clearflag 2411
	clearflag 2410
	clearflag 2409
	clearflag 8804
	release
	end

Snowswept_Cavern_EventScript_SneaslerRan::
	clearflag 2411
	clearflag 2410
	clearflag 2409
	clearflag 8804
	release
	end

Snowswept_Cavern_Eventscript_Machamp::
	lock
	faceplayer
	playmoncry 68, 2
	msgbox Snowswept_Text_Machamp_Cry, MSGBOX_AUTOCLOSE
	waitmoncry
	goto_if_ge 20639, 3, Snowswept_Cavern_Eventscript_Machamp_AfterBoulder
	msgbox Snowswept_Text_Machamp_Plate, MSGBOX_YESNO
	closemessage
	goto_if_eq 32781, FALSE, Snowswept_Cavern_Eventscript_Machamp_Ran
	setwildbossbattle species=68, level=75, item=ITEM_NONE, move1_1=MOVE_SEISMIC_TOSS, move1_2=MOVE_ROCK_SLIDE, move1_3=MOVE_BRICK_BREAK move1_4=MOVE_SUBMISSION
	setflag 2411
	setflag 8804
	dowildbattle
	clearflag 2411
	clearflag 8804
	specialvar 32781, GetBattleOutcome
	goto_if_eq 32781, 4, Snowswept_Cavern_Eventscript_Machamp_Ran
	playmoncry 68, 2
	msgbox Snowswept_Cavern_Text_DroppedItem, MSGBOX_AUTOCLOSE
	giveitem ITEM_FIST_PLATE
	closemessage
	addvar 20640, 1
	setflag 9091
	applymovement2 5, Snowswept_Machamp_Movement
	waitmovement 0

	setvar 32772, 2
	setvar 32773, 2
	setvar 32774, 20
	setvar 32775, 4
	special ShakeCamera
	waitstate
	applymovement 6, Snowswept_Cavern_Movement_Boulder
	playse 214
	delay 5
	playse 214
	delay 5
	playse 214
	delay 5
	waitmovement 0
	playse 20

	setobjectxyperm 6, 38, 56
	setvar 20639, 3
	release
	end

Snowswept_Cavern_Eventscript_Machamp_Ran::
	turnobject 5, DIR_SOUTH
	release
	end

Snowswept_Cavern_Eventscript_Machamp_AfterBoulder::
	turnobject 5, DIR_SOUTH
	release
	end

Snowswept_Cavern_Text_DroppedItem:
	.string "Th{SE_M_REVERSAL}MACHAM{SE_M_PETAL_DANCE}droppe{SE_M_WATERFALL}a{SE_M_ATTRACT}item...$"

Snowswept_Text_Machamp_Cry:
	.string "Mahh!!$"

Snowswept_Text_Machamp_Plate:
	.string "Th{SE_M_REVERSAL}MACHAM{SE_M_PETAL_DANCE}seem{SE_M_GRASSWHISTLE}t{SE_M_ATTRACT2}b{SE_M_REVERSAL}holding\n"
	.string "{SE_M_CHARGE}PLAT{SE_M_SWORDS_DANCE}i{SE_M_ATTRACT}on{SE_M_REVERSAL}o{SE_M_ACID_ARMOR}it{SE_M_GRASSWHISTLE}hands.\p"
	.string "Battl{SE_M_REVERSAL}it?$"

Snowswept_Machamp_Movement:
	jump_in_place_down
	walk_in_place_fast_down
	walk_in_place_fast_down
	step_end

Snowswept_Cavern_Movement_Boulder:
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	step_end

Snowswept_EventScript_Item_IcyRock::
	finditem ITEM_ICY_ROCK
	end

Snowswept_EventScript_Item_UltraBall::
	finditem ITEM_ULTRA_BALL
	end

