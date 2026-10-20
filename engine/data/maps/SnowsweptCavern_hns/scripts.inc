@ Johto (data/maps/SnowsweptCavern_hns/scripts.inc), as built into the FireRed game.

SnowsweptCavern_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, SnowsweptCavern_hns_OnTransition
	.byte 0

SnowsweptCavern_hns_OnTransition::
	goto_if_ge JOHTO_VAR_SINJOH_STORYLINE, 3, SnowsweptCavern_hns_SetBoulderLocation
	end

SnowsweptCavern_hns_SetBoulderLocation::
	setobjectxyperm LOCALID_SNOWSWEPT_CAVERN_BOULDER, 38, 56
	end

Snowswept_Cavern_EventScript_ActivateSneasler::
	lock
	setobjectmovementtype LOCALID_SNOWSWEPT_CAVERN_SNEASLER, MOVEMENT_TYPE_WALK_IN_PLACE_DOWN
	setobjectxyperm LOCALID_SNOWSWEPT_CAVERN_SNEASLER, 6, 24
	playse SE_M_DETECT
	dofieldeffectsparkle 10, 28, 0
	waitfieldeffect FLDEFF_SPARKLE
	playse SE_PIN
	applymovement2 LOCALID_PLAYER, J_Common_Movement_ExclamationMark
	delay 55
	waitmovement LOCALID_PLAYER
	msgbox SinjohRuins_Lab_Text_PlayFlute, MSGBOX_YESNO
	closemessage
	goto_if_eq VAR_RESULT, FALSE, SinjohRuins_Lab_EventScript_NoOp
	playbgm ((((558 + 1) + 0xAF) + 1) + 0x00), FALSE
	delay 200
	fadedefaultbgm
	addobject LOCALID_SNOWSWEPT_CAVERN_SNEASLER
	clearflag JOHTO_FLAG_HIDE_SNOWSWEPT_NOBLE_SNEASLER

	applymovement2 LOCALID_SNOWSWEPT_CAVERN_SNEASLER, Snowswept_Cavern_Movement_SpawnSneasler1
	delay 10
	playmoncry SPECIES_WEAVILE, CRY_MODE_NORMAL
	waitmoncry
	playmoncry SPECIES_WEAVILE, CRY_MODE_NORMAL
	waitmoncry
	waitmovement 0


	applymovement2 LOCALID_SNOWSWEPT_CAVERN_SNEASLER, Snowswept_Cavern_Movement_SpawnSneasler2
	delay 10
	playse SE_LEDGE
	delay 20
	setvar VAR_0x8004, 1
	setvar VAR_0x8005, 1
	setvar VAR_0x8006, 5
	setvar VAR_0x8007, 2
	special ShakeCamera
	waitmovement 0

	setobjectxyperm LOCALID_SNOWSWEPT_CAVERN_SNEASLER, 5, 26

	setvar JOHTO_VAR_NOBLE_SNEASLER, 2
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
	playmoncry SPECIES_WEAVILE, CRY_MODE_ENCOUNTER
	waitmoncry
	setwildbossbattle species=903, level=80, item=ITEM_RAZOR_CLAW, move1_1=MOVE_DIRE_CLAW, move1_2=MOVE_ROCK_SLIDE, move1_3=MOVE_BRICK_BREAK move1_4=MOVE_LASH_OUT
	settotemboost B_POSITION_OPPONENT_LEFT, 1, 0, 2, 0, 0, 0
	setflag FLAG_NO_WILD_CATCHING
	setflag FLAG_NO_WILD_RUNNING
	setflag FLAG_SMART_WILD_AI
	setflag JOHTO_FLAG_NO_SHINY
	dowildbattle
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, Snowswept_Cavern_EventScript_SneaslerRan
	bufferspeciesname STR_VAR_1, SPECIES_SNEASLER
	msgbox SinjohRuins_Lab_Text_DropedItem, MSGBOX_DEFAULT
	giveitem ITEM_TOXIC_PLATE
	addvar JOHTO_VAR_PLATECOUNTER, 1
	fadescreenswapbuffers FADE_TO_BLACK
	removeobject LOCALID_SNOWSWEPT_CAVERN_SNEASLER
	setflag JOHTO_FLAG_HIDE_SNOWSWEPT_NOBLE_SNEASLER
	fadescreenswapbuffers FADE_FROM_BLACK
	call_if_eq JOHTO_VAR_PLATECOUNTER, 3, SinjohRuins_Lab_EventScript_3Plates
	call_if_eq JOHTO_VAR_PLATECOUNTER, 6, SinjohRuins_Lab_EventScript_6Plates
	call_if_eq JOHTO_VAR_PLATECOUNTER, 9, SinjohRuins_Lab_EventScript_9Plates
	call_if_eq JOHTO_VAR_PLATECOUNTER, 12, SinjohRuins_Lab_EventScript_12Plates
	call_if_eq JOHTO_VAR_PLATECOUNTER, 15, SinjohRuins_Lab_EventScript_15Plates
	call_if_eq JOHTO_VAR_PLATECOUNTER, 16, SinjohRuins_Lab_EventScript_16Plates
	clearflag FLAG_NO_WILD_CATCHING
	clearflag FLAG_NO_WILD_RUNNING
	clearflag FLAG_SMART_WILD_AI
	clearflag JOHTO_FLAG_NO_SHINY
	release
	end

Snowswept_Cavern_EventScript_SneaslerRan::
	clearflag FLAG_NO_WILD_CATCHING
	clearflag FLAG_NO_WILD_RUNNING
	clearflag FLAG_SMART_WILD_AI
	clearflag JOHTO_FLAG_NO_SHINY
	release
	end

Snowswept_Cavern_Eventscript_Machamp::
	lock
	faceplayer
	playmoncry SPECIES_MACHAMP, CRY_MODE_ENCOUNTER
	msgbox Snowswept_Text_Machamp_Cry, MSGBOX_AUTOCLOSE
	waitmoncry
	goto_if_ge JOHTO_VAR_SINJOH_STORYLINE, 3, Snowswept_Cavern_Eventscript_Machamp_AfterBoulder
	msgbox Snowswept_Text_Machamp_Plate, MSGBOX_YESNO
	closemessage
	goto_if_eq VAR_RESULT, FALSE, Snowswept_Cavern_Eventscript_Machamp_Ran
	setwildbossbattle species=68, level=75, item=ITEM_NONE, move1_1=MOVE_SEISMIC_TOSS, move1_2=MOVE_ROCK_SLIDE, move1_3=MOVE_BRICK_BREAK move1_4=MOVE_SUBMISSION
	setflag FLAG_NO_WILD_CATCHING
	setflag JOHTO_FLAG_NO_SHINY
	dowildbattle
	clearflag FLAG_NO_WILD_CATCHING
	clearflag JOHTO_FLAG_NO_SHINY
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, Snowswept_Cavern_Eventscript_Machamp_Ran
	playmoncry SPECIES_MACHAMP, CRY_MODE_ENCOUNTER
	msgbox Snowswept_Cavern_Text_DroppedItem, MSGBOX_AUTOCLOSE
	giveitem ITEM_FIST_PLATE
	closemessage
	addvar JOHTO_VAR_PLATECOUNTER, 1
	setflag JOHTO_FLAG_GOT_FIST_PLATE
	applymovement2 LOCALID_SNOWSWEPT_CAVERN_MACHAMP, Snowswept_Machamp_Movement
	waitmovement 0

	setvar VAR_0x8004, 2
	setvar VAR_0x8005, 2
	setvar VAR_0x8006, 20
	setvar VAR_0x8007, 4
	special ShakeCamera
	waitstate
	applymovement LOCALID_SNOWSWEPT_CAVERN_BOULDER, Snowswept_Cavern_Movement_Boulder
	playse SE_M_STRENGTH
	delay 5
	playse SE_M_STRENGTH
	delay 5
	playse SE_M_STRENGTH
	delay 5
	waitmovement 0
	playse SE_BANG

	setobjectxyperm LOCALID_SNOWSWEPT_CAVERN_BOULDER, 38, 56
	setvar JOHTO_VAR_SINJOH_STORYLINE, 3
	release
	end

Snowswept_Cavern_Eventscript_Machamp_Ran::
	turnobject LOCALID_SNOWSWEPT_CAVERN_MACHAMP, DIR_SOUTH
	release
	end

Snowswept_Cavern_Eventscript_Machamp_AfterBoulder::
	turnobject LOCALID_SNOWSWEPT_CAVERN_MACHAMP, DIR_SOUTH
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

