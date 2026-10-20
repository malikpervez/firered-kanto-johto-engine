@ Johto (data/maps/RocketHideout_B2F_hns/scripts.inc), as built into the FireRed game.

RocketHideout_B2F_hns_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, RocketHideout_B2F_OnLoad
	.byte 0

RocketHideout_B2F_OnLoad::
	call_if_set JOHTO_FLAG_HIDE_ROCKETHIDEOUT2_GATE, RocketHideout_B2F_HideGate
	call_if_eq JOHTO_VAR_MAHOGANY_TOWN_STATE, 13, RocketHideout_B2F_MoveLanceDragonite
	call_if_ge JOHTO_VAR_ELECTRODES_FAINTED, 4, RockerHideout2_DeactivateGenerator
	end

RockerHideout2_DeactivateGenerator::
	setmetatile 13, 8, 0x303, TRUE
	setmetatile 13, 9, 0x303, TRUE
	setmetatile 13, 10, 0x303, TRUE
	setmetatile 13, 11, 0x303, TRUE
	setmetatile 13, 12, 0x303, TRUE
	setmetatile 13, 13, 0x303, TRUE
	setmetatile 13, 14, 0x303, TRUE
	setmetatile 13, 15, 0x303, TRUE

	setmetatile 14, 8, 0x303, TRUE
	setmetatile 14, 9, 0x303, TRUE
	setmetatile 14, 10, 0x303, TRUE
	setmetatile 14, 11, 0x303, TRUE
	setmetatile 14, 12, 0x303, TRUE
	setmetatile 14, 13, 0x303, TRUE
	setmetatile 14, 14, 0x303, TRUE
	setmetatile 14, 15, 0x303, TRUE

	setmetatile 15, 8, 0x303, TRUE
	setmetatile 15, 9, 0x303, TRUE
	setmetatile 15, 10, 0x303, TRUE
	setmetatile 15, 11, 0x303, TRUE
	setmetatile 15, 12, 0x303, TRUE
	setmetatile 15, 13, 0x303, TRUE
	setmetatile 15, 14, 0x303, TRUE
	setmetatile 15, 15, 0x303, TRUE

	setmetatile 16, 8, 0x303, TRUE
	setmetatile 16, 9, 0x303, TRUE
	setmetatile 16, 10, 0x303, TRUE
	setmetatile 16, 11, 0x303, TRUE
	setmetatile 16, 12, 0x303, TRUE
	setmetatile 16, 13, 0x303, TRUE
	setmetatile 16, 14, 0x303, TRUE
	setmetatile 16, 15, 0x303, TRUE

	setmetatile 17, 8, 0x303, TRUE
	setmetatile 17, 9, 0x303, TRUE
	setmetatile 17, 10, 0x303, TRUE
	setmetatile 17, 11, 0x303, TRUE
	setmetatile 17, 12, 0x303, TRUE
	setmetatile 17, 13, 0x303, TRUE
	setmetatile 17, 14, 0x303, TRUE
	setmetatile 17, 15, 0x303, TRUE

	setmetatile 18, 8, 0x303, TRUE
	setmetatile 18, 9, 0x303, TRUE
	setmetatile 18, 10, 0x303, TRUE
	setmetatile 18, 11, 0x303, TRUE
	setmetatile 18, 12, 0x303, TRUE
	setmetatile 18, 13, 0x303, TRUE
	setmetatile 18, 14, 0x303, TRUE
	setmetatile 18, 15, 0x303, TRUE
	return

RocketHideout_B2F_HideGate::
	setmetatile 14, 19, 0x378, FALSE
	setmetatile 14, 20, 0x380, FALSE
	setmetatile 15, 19, 0x379, FALSE
	setmetatile 15, 20, 0x379, FALSE
	setmetatile 16, 19, 0x379, FALSE
	setmetatile 16, 20, 0x379, FALSE
	return

RocketHideout_B2F_MoveLanceDragonite::
	setobjectxyperm LOCALID_ROCKETHIDEOUT2_DRAGONITE, 20, 16
	setobjectxyperm LOCALID_ROCKETHIDEOUT2_LANCE, 19, 16
	setobjectmovementtype LOCALID_ROCKETHIDEOUT2_DRAGONITE, MOVEMENT_TYPE_WALK_IN_PLACE_UP
	setobjectmovementtype LOCALID_ROCKETHIDEOUT2_LANCE, MOVEMENT_TYPE_FACE_UP
	return

RocketHideout_B2F_Trigger_MurkrowStairs::
	lock
	applymovement LOCALID_ROCKETHIDEOUT2_MURKROWSTAIRS, RocketHideout_B2F_Movement_MurkrowStairs1
	waitmovement 0
	playmoncry SPECIES_MURKROW, CRY_MODE_NORMAL
	msgbox RocketHideout_B3F_Text_MurkrowSpeak1, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_ROCKETHIDEOUT2_MURKROWSTAIRS, RocketHideout_B2F_Movement_MurkrowStairs2
	waitmovement 0
	setflag JOHTO_FLAG_HIDE_ROCKETHIDEOUT2_MURKROWSTAIRS
	removeobject LOCALID_ROCKETHIDEOUT2_MURKROWSTAIRS
	clearflag JOHTO_FLAG_HIDE_ROCKETHIDEOUT3_MURKROWSTAIRS
	setvar JOHTO_VAR_MAHOGANY_TOWN_STATE, 10
	release
	end

RocketHideout_B2F_Movement_MurkrowStairs1:
	jump_in_place_left
	jump_in_place_left
	step_end

RocketHideout_B2F_Movement_MurkrowStairs2:
	jump_in_place_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	step_end

RocketHideout_B2F_Trigger_MurkrowGate::
	lock
	applymovement LOCALID_ROCKETHIDEOUT2_MURKROWGATE, RocketHideout_B2F_Movement_MurkrowGate1
	waitmovement 0
	playmoncry SPECIES_MURKROW, CRY_MODE_NORMAL
	msgbox RocketHideout_B3F_Text_Murkrow, MSGBOX_DEFAULT
	msgbox RocketHideout_B2F_Text_MurkrowUnlock, MSGBOX_DEFAULT
	playse SE_CLICK
	setmetatile 14, 19, 0x378, FALSE
	setmetatile 14, 20, 0x380, FALSE
	setmetatile 15, 19, 0x379, FALSE
	setmetatile 15, 20, 0x379, FALSE
	setmetatile 16, 19, 0x379, FALSE
	setmetatile 16, 20, 0x379, FALSE
	special DrawWholeMapView
	setflag JOHTO_FLAG_HIDE_ROCKETHIDEOUT2_GATE
	closemessage
	applymovement LOCALID_ROCKETHIDEOUT2_MURKROWGATE, RocketHideout_B2F_Movement_MurkrowGate2
	waitmovement 0
	setflag JOHTO_FLAG_HIDE_ROCKETHIDEOUT2_MURKROWGATE
	removeobject LOCALID_ROCKETHIDEOUT2_MURKROWGATE
	setvar JOHTO_VAR_MAHOGANY_TOWN_STATE, 12
	release
	end

RocketHideout_B2F_Movement_MurkrowGate1:
	jump_in_place_up
	jump_in_place_up
	step_end

RocketHideout_B2F_Movement_MurkrowGate2:
	jump_in_place_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	step_end

RocketHideout_B2F_Text_MurkrowUnlock:
	.string "MURKRO{SE_M_DETECT}screame{SE_M_WATERFALL}th{SE_M_REVERSAL}password,\n"
	.string "mimickin{SE_M_SANDSTORM}th{SE_M_REVERSAL}voic{SE_M_REVERSAL}o{SE_M_ACID_ARMOR}PETREL.\p"
	.string "..................\n"
	.string "Th{SE_M_REVERSAL}voice-recognitio{SE_M_ATTRACT}system\l"
	.string "unlocke{SE_M_WATERFALL}th{SE_M_REVERSAL}door!$"

RocketHideout_B2F_Trigger_PlayerMoveLeft::
	applymovement OBJ_EVENT_ID_PLAYER, J_Common_Movement_WalkRight1
	waitmovement 0
	return

RocketHideout_B2F_Trigger_PlayerMoveRight::
	applymovement OBJ_EVENT_ID_PLAYER, J_Common_Movement_WalkLeft1
	waitmovement 0
	return

RocketHideout_B2F_Trigger_Ariana::
	lock
	setobjectxyperm LOCALID_ROCKETHIDEOUT2_LANCE, 6, 26
	setobjectxyperm LOCALID_ROCKETHIDEOUT2_DRAGONITE, 5, 26
	clearflag JOHTO_FLAG_HIDE_ROCKETHIDEOUT2_ARIANA_AND_GRUNT
	addobject LOCALID_ROCKETHIDEOUT2_ARIANA
	addobject LOCALID_ROCKETHIDEOUT2_GRUNT
	delay 20
	msgbox RocketHideout_B2F_Text_ArianaHoldIt, MSGBOX_AUTOCLOSE
	playse SE_PIN
	applymovement OBJ_EVENT_ID_PLAYER, J_Common_Movement_ExclamationMark
	waitmovement OBJ_EVENT_ID_PLAYER
	getplayerxy VAR_TEMP_0, VAR_TEMP_1
	call_if_eq VAR_TEMP_0, 14, RocketHideout_B2F_Trigger_PlayerMoveLeft
	call_if_eq VAR_TEMP_0, 16, RocketHideout_B2F_Trigger_PlayerMoveRight
	applymovement OBJ_EVENT_ID_PLAYER, RocketHideout_B2F_Movement_PlayerMeetAriana
	applymovement LOCALID_ROCKETHIDEOUT2_ARIANA, RocketHideout_B2F_Movement_Ariana
	delay 20
	applymovement LOCALID_ROCKETHIDEOUT2_GRUNT, RocketHideout_B2F_Movement_Ariana
	waitmovement LOCALID_ROCKETHIDEOUT2_GRUNT
	msgbox RocketHideout_B2F_Text_ArianaChallenge, MSGBOX_DEFAULT
	closemessage
	clearflag JOHTO_FLAG_HIDE_ROCKETHIDEOUT2_LANCE_DRAGONITE
	addobject LOCALID_ROCKETHIDEOUT2_LANCE
	addobject LOCALID_ROCKETHIDEOUT2_DRAGONITE
	applymovement LOCALID_ROCKETHIDEOUT2_LANCE, RocketHideout_B2F_Movement_Lance
	delay 20
	applymovement LOCALID_ROCKETHIDEOUT2_DRAGONITE, RocketHideout_B2F_Movement_Lance
	waitmovement 0
	msgbox RocketHideout_B2F_Text_LanceInterrupt, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_ROCKETHIDEOUT2_ARIANA, J_Common_Movement_WalkInPlaceFasterUp
	msgbox RocketHideout_B2F_Text_ArianaOutraged
	closemessage
	goto RocketHideout_B2F_EventScript_ReadyForBattlePrompt
	end

RocketHideout_B2F_Movement_PlayerMeetAriana:
	walk_down
	walk_down
	walk_down
	step_end

RocketHideout_B2F_Movement_Ariana:
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

RocketHideout_B2F_Movement_Lance:
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	step_end

RocketHideout_B2F_Text_ArianaHoldIt:
	.string "ARIANA{SE_M_HEAT_WAVE}Hol{SE_M_WATERFALL}i{SE_M_SPIT_UP}righ{SE_M_SPIT_UP}there!$"

RocketHideout_B2F_Text_ArianaChallenge:
	.string "ARIANA{SE_M_HEAT_WAVE}W{SE_M_REVERSAL}can'{SE_M_SPIT_UP}le{SE_M_SPIT_UP}{SE_M_CHARGE}bra{SE_M_SPIT_UP}lik{SE_M_REVERSAL}you\n"
	.string "d{SE_M_ATTRACT2}a{SE_M_GRASSWHISTLE}yo{SE_M_DIVE}pleas{SE_M_REVERSAL}forever.\p"
	.string "It'l{SE_M_BATON_PASS}hur{SE_M_SPIT_UP}Tea{SE_M_MILK_DRINK}Rocket'{SE_M_GRASSWHISTLE}prid{SE_M_REVERSAL}over\n"
	.string "an{SE_M_WATERFALL}ove{SE_M_SAND_TOMB}again{SE_M_PERISH_SONG}Makin{SE_M_SANDSTORM}i{SE_M_SPIT_UP}lessen,\l"
	.string "yo{SE_M_DIVE}see.\p"
	.string "...So{SE_M_SUPERSONIC}it'{SE_M_GRASSWHISTLE}tim{SE_M_REVERSAL}t{SE_M_ATTRACT2}finis{SE_M_TRI_ATTACK}you.\n"
	.string "Howeve{SE_M_SAND_TOMB}stron{SE_M_SANDSTORM}yo{SE_M_DIVE}ma{SE_M_YAWN}be,\p"
	.string "i{SE_M_ACID_ARMOR}th{SE_M_REVERSAL}tw{SE_M_ATTRACT2}o{SE_M_ACID_ARMOR}u{SE_M_GRASSWHISTLE}figh{SE_M_SPIT_UP}a{SE_M_SPIT_UP}th{SE_M_REVERSAL}same\n"
	.string "time{SE_M_SUPERSONIC}you'l{SE_M_BATON_PASS}hav{SE_M_REVERSAL}n{SE_M_ATTRACT2}chanc{SE_M_REVERSAL}of\l"
	.string "winning{SE_M_PERISH_SONG}Don'{SE_M_SPIT_UP}yo{SE_M_DIVE}agree?\p"
	.string "He{SE_M_REVERSAL}he{SE_M_REVERSAL}hee{SE_M_DRAGON_RAGE}Sorry{SE_M_SUPERSONIC}baby.\n"
	.string "Now{SE_M_SUPERSONIC}ge{SE_M_SPIT_UP}read{SE_M_YAWN}t{SE_M_ATTRACT2}b{SE_M_REVERSAL}thrashed.$"

RocketHideout_B2F_Text_LanceInterrupt:
	.string "LANCE{SE_M_HEAT_WAVE}Hol{SE_M_WATERFALL}it!\n"
	.string "{SE_M_BONEMERANG}two-on-on{SE_M_REVERSAL}battle?\p"
	.string "Tha{SE_M_SPIT_UP}i{SE_M_GRASSWHISTLE}s{SE_M_ATTRACT2}unfair!\n"
	.string "Typica{SE_M_BATON_PASS}o{SE_M_ACID_ARMOR}Tea{SE_M_MILK_DRINK}Rocke{SE_M_SPIT_UP}t{SE_M_ATTRACT2}b{SE_M_REVERSAL}so\l"
	.string "sneaky.\p"
	.string "Allo{SE_M_TWISTER}m{SE_M_REVERSAL}t{SE_M_ATTRACT2}joi{SE_M_ATTRACT}th{SE_M_REVERSAL}battle!$"

RocketHideout_B2F_Text_ArianaOutraged:
	.string "ARIANA{SE_M_HEAT_WAVE}What{SE_M_SING}Yo{SE_M_DIVE}ha{SE_M_WATERFALL}a{SE_M_ATTRACT}accomplice?\n"
	.string "Wher{SE_M_REVERSAL}i{SE_M_GRASSWHISTLE}you{SE_M_SAND_TOMB}sens{SE_M_REVERSAL}o{SE_M_ACID_ARMOR}dignity?\p"
	.string "A{SE_M_GRASSWHISTLE}interi{SE_M_MILK_DRINK}bos{SE_M_GRASSWHISTLE}i{SE_M_ATTRACT}plac{SE_M_REVERSAL}o{SE_M_ACID_ARMOR}GIOVANNI,\n"
	.string "I'l{SE_M_BATON_PASS}sho{SE_M_TWISTER}yo{SE_M_DIVE}ho{SE_M_TWISTER}wron{SE_M_SANDSTORM}i{SE_M_SPIT_UP}i{SE_M_GRASSWHISTLE}t{SE_M_ATTRACT2}meddle\l"
	.string "wit{SE_M_TRI_ATTACK}Tea{SE_M_MILK_DRINK}Rocket!$"

RocketHideout_B2F_Text_LanceChooseMons:
	.string "LANCE{SE_M_HEAT_WAVE}Quickl{SE_M_YAWN}{PLAYER}{SE_M_SUPERSONIC}choose\n"
	.string "you{SE_M_SAND_TOMB}POKéMON!$"

RocketHideout_B2F_EventScript_ReadyForBattlePrompt::
	msgbox RocketHideout_B2F_Text_LanceChooseMons, MSGBOX_DEFAULT
	goto RocketHideout_B2F_EventScript_ChoosePartyForMultiBattle
	end

RocketHideout_B2F_EventScript_ChoosePartyForMultiBattle::
	setflag JOHTO_FLAG_ROCKETHIDEOUT2_BATTLE
	special SavePlayerParty
	fadescreen FADE_TO_BLACK
	special ChooseHalfPartyForBattle
	waitstate
	goto_if_ne VAR_RESULT, 0, RocketHideout_B2F_EventScript_DoLanceMultiBattle
	special LoadPlayerParty
	goto RocketHideout_B2F_EventScript_ReadyForBattlePrompt

RocketHideout_B2F_EventScript_DoLanceMultiBattle::




	applymovement LOCALID_ROCKETHIDEOUT2_ARIANA, J_Common_Movement_WalkUp1
	applymovement LOCALID_ROCKETHIDEOUT2_GRUNT, J_Common_Movement_WalkUp1
	waitmovement 0
	turnobject LOCALID_ROCKETHIDEOUT2_GRUNT, DIR_WEST
	multi_2_vs_2 TRAINER_JOHTO_ARIANA_1_HNS, J_Debug_Text_ArianaDefeat, TRAINER_JOHTO_GRUNT_23_HNS, J_Debug_Text_Grunt23Defeat, PARTNER_LANCE_HNS




	switch VAR_RESULT
	case 1, RocketHideout_B2F_EventScript_DefeatedAriana
	fadescreen FADE_TO_BLACK
	setflag JOHTO_FLAG_HIDE_ROCKETHIDEOUT2_LANCE_DRAGONITE
	setflag JOHTO_FLAG_HIDE_ROCKETHIDEOUT2_ARIANA_AND_GRUNT
	special SetCB2WhiteOut
	waitstate

RocketHideout_B2F_EventScript_DefeatedAriana::
	clearflag JOHTO_FLAG_ROCKETHIDEOUT2_BATTLE
	msgbox RocketHideout_Text_ArianaRetreat, MSGBOX_DEFAULT
	closemessage
	fadescreenswapbuffers FADE_TO_BLACK
	applymovement LOCALID_ROCKETHIDEOUT2_LANCE, J_Common_Movement_WalkUp1
	applymovement LOCALID_ROCKETHIDEOUT2_DRAGONITE, J_Common_Movement_WalkUp1
	waitmovement 0
	applymovement LOCALID_ROCKETHIDEOUT2_LANCE, J_Common_Movement_WalkRight1
	applymovement LOCALID_ROCKETHIDEOUT2_DRAGONITE, J_Common_Movement_WalkRight1
	waitmovement 0
	setflag JOHTO_FLAG_HIDE_MAHOGANY_ROCKETS
	setflag JOHTO_FLAG_HIDE_ROCKETHIDEOUT2_ARIANA_AND_GRUNT
	removeobject LOCALID_ROCKETHIDEOUT2_ARIANA
	removeobject LOCALID_ROCKETHIDEOUT2_GRUNT
	turnobject OBJ_EVENT_ID_PLAYER, DIR_WEST
	fadescreenswapbuffers FADE_FROM_BLACK
	msgbox RocketHideout_Text_LanceStepBack, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_ROCKETHIDEOUT2_LANCE, RocketHideout_B2F_Movement_LanceWalkToGenerator
	applymovement LOCALID_ROCKETHIDEOUT2_DRAGONITE, RocketHideout_B2F_Movement_DragoniteWalkToGenerator
	delay 55
	applymovement OBJ_EVENT_ID_PLAYER, RocketHideout_B2F_Movement_LanceWalkToGenerator
	waitmovement 0

	applymovement LOCALID_ROCKETHIDEOUT2_DRAGONITE, RocketHideout_B2F_Movement_DragoniteInvestigateGenerator
	applymovement LOCALID_ROCKETHIDEOUT2_LANCE, RocketHideout_B2F_Movement_LanceInvestigateGenerator
	delay 165
	playmoncry SPECIES_DRAGONITE, CRY_MODE_NORMAL
	waitmovement LOCALID_ROCKETHIDEOUT2_DRAGONITE
	waitmovement LOCALID_ROCKETHIDEOUT2_LANCE
	msgbox RocketHideout_B2F_Text_LanceElectrodeFaint, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_ROCKETHIDEOUT2_LANCE, RocketHideout_B2F_Movement_LanceWalkToElectrode
	applymovement LOCALID_ROCKETHIDEOUT2_DRAGONITE, RocketHideout_B2F_Movement_LanceWalkToElectrode
	waitmovement LOCALID_ROCKETHIDEOUT2_DRAGONITE
	waitmovement LOCALID_ROCKETHIDEOUT2_LANCE
	applymovement OBJ_EVENT_ID_PLAYER, RocketHideout_B2F_Movement_PlayerWalkToElectrode
	waitmovement 0
	setobjectxyperm LOCALID_ROCKETHIDEOUT2_DRAGONITE, 20, 16
	setobjectxyperm LOCALID_ROCKETHIDEOUT2_LANCE, 19, 16
	setobjectmovementtype LOCALID_ROCKETHIDEOUT2_DRAGONITE, MOVEMENT_TYPE_WALK_IN_PLACE_UP
	setobjectmovementtype LOCALID_ROCKETHIDEOUT2_LANCE, MOVEMENT_TYPE_FACE_UP
	setvar JOHTO_VAR_MAHOGANY_TOWN_STATE, 13
	release
	end

RocketHideout_B2F_Movement_LanceWalkToGenerator:
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

RocketHideout_B2F_Movement_DragoniteWalkToGenerator:
	delay_8
	delay_8
	walk_right
	walk_up
	walk_up
	walk_up
	step_end

RocketHideout_B2F_Movement_LanceInvestigateGenerator:
	walk_up
	walk_left
	face_up
	delay_8
	delay_8
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	face_up
	delay_8
	delay_8
	face_right
	delay_8
	delay_8
	delay_8
	delay_8
	walk_left
	walk_left
	walk_left
	face_down
	step_end

RocketHideout_B2F_Movement_DragoniteInvestigateGenerator:
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_up
	walk_up
	walk_left
	delay_16
	delay_16
	delay_8
	delay_8
	delay_8
	delay_8
	walk_left
	walk_left
	walk_left
	step_end

RocketHideout_B2F_Movement_LanceWalkToElectrode:
	walk_right
	walk_right
	walk_right
	walk_right
	face_up
	step_end

RocketHideout_B2F_Movement_PlayerWalkToElectrode:
	walk_left
	walk_left
	walk_left
	step_end

RocketHideout_B2F_Trigger_Electrode::
	lock
	goto_if_eq JOHTO_VAR_ELECTRODES_FAINTED, 3, RocketHideout_B2F_EventScript_ElectrodeDone
	turnobject LOCALID_ROCKETHIDEOUT2_LANCE, DIR_WEST
	msgbox RocketHideout_B2F_Text_LanceSide, MSGBOX_DEFAULT
	closemessage
	turnobject LOCALID_ROCKETHIDEOUT2_LANCE, DIR_NORTH
	applymovement OBJ_EVENT_ID_PLAYER, J_Common_Movement_WalkLeft1
	waitmovement 0
	release
	end

RocketHideout_B2F_EventScript_Electrode::
	lock
	playmoncry SPECIES_ELECTRODE, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setwildbattle SPECIES_ELECTRODE, 30
	dowildbattle
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, RocketHideout_B2F_EventScript_Ran_Electrode
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, RocketHideout_B2F_EventScript_Ran_Electrode
	removeobject VAR_LAST_TALKED
	addvar JOHTO_VAR_ELECTRODES_FAINTED, 1
	release
	end

RocketHideout_B2F_EventScript_Ran_Electrode::
	release
	end

RocketHideout_B2F_EventScript_ElectrodeDone::
	playse SE_M_HYPER_BEAM
	removeobject LOCALID_LANCEELECTRODE1
	removeobject LOCALID_LANCEELECTRODE2
	removeobject LOCALID_LANCEELECTRODE3
	waitse
	getplayerxy VAR_TEMP_0, VAR_TEMP_1
	call_if_eq VAR_TEMP_1, 16, RocketHideout_B2F_Movement_PlayerMeetLanceTop
	call_if_eq VAR_TEMP_1, 18, RocketHideout_B2F_Movement_PlayerMeetLanceBot
	turnobject OBJ_EVENT_ID_PLAYER, DIR_EAST
	applymovement LOCALID_ROCKETHIDEOUT2_LANCE, RocketHideout_B2F_Movement_LanceMeetPlayerAfterElectrode
	applymovement LOCALID_ROCKETHIDEOUT2_DRAGONITE, RocketHideout_B2F_Movement_LanceMeetPlayerAfterElectrode
	waitmovement LOCALID_ROCKETHIDEOUT2_DRAGONITE

	playse SE_CLICK
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	turnobject LOCALID_ROCKETHIDEOUT2_LANCE, DIR_NORTH
	call RockerHideout2_DeactivateGenerator
	special DrawWholeMapView
	delay 55
	turnobject 7 DIR_WEST
	turnobject OBJ_EVENT_ID_PLAYER, DIR_EAST
	delay 30
	msgbox RocketHideout_B2F_Text_LanceElectrodeDone, MSGBOX_DEFAULT
	giveitem ITEM_HM_WHIRLPOOL
	msgbox RocketHideout_B2F_Text_LanceWhirlpool, MSGBOX_DEFAULT
	closemessage
	turnobject LOCALID_ROCKETHIDEOUT2_LANCE, DIR_SOUTH
	delay 20
	msgbox RocketHideout_B2F_Text_LanceMonMaster, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_ROCKETHIDEOUT2_LANCE, RocketHideout_B2F_Movement_LanceFinalExit
	delay 20

	applymovement LOCALID_ROCKETHIDEOUT2_DRAGONITE, RocketHideout_B2F_Movement_DragoniteFinalExit
	waitmovement LOCALID_ROCKETHIDEOUT2_DRAGONITE
	waitmovement LOCALID_ROCKETHIDEOUT2_LANCE

	setflag JOHTO_FLAG_HIDE_ROCKETHIDEOUT2_LANCE_DRAGONITE
	removeobject LOCALID_ROCKETHIDEOUT2_DRAGONITE
	removeobject LOCALID_ROCKETHIDEOUT2_LANCE
	setvar JOHTO_VAR_ELECTRODES_FAINTED, 4
	setvar JOHTO_VAR_MAHOGANY_TOWN_STATE, 14
	clearflag JOHTO_FLAG_HIDE_MAHOGANY_COP
	setflag JOHTO_FLAG_HIDE_MAHOGANY_TOWN_FATMAN
	setvar JOHTO_VAR_ROCKET_HIDEOUT_STATUE_1, 2
	setvar JOHTO_VAR_ROCKET_HIDEOUT_STATUE_2, 2
	setvar JOHTO_VAR_ROCKET_HIDEOUT_STATUE_3, 2
	setvar JOHTO_VAR_ROCKET_HIDEOUT_STATUE_4, 2
	setvar JOHTO_VAR_ROCKET_HIDEOUT_STATUE_5, 2
	release
	end

RocketHideout_B2F_Movement_PlayerMeetLanceTop:
	applymovement OBJ_EVENT_ID_PLAYER, J_Common_Movement_WalkDown1
	waitmovement 0
	return

RocketHideout_B2F_Movement_PlayerMeetLanceBot:
	applymovement OBJ_EVENT_ID_PLAYER, J_Common_Movement_WalkUp1
	waitmovement 0
	return

RocketHideout_B2F_Movement_LanceMeetPlayerAfterElectrode:
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

RocketHideout_B2F_Movement_LanceFinalExit:
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	step_end

RocketHideout_B2F_Movement_DragoniteFinalExit:
	walk_left
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	step_end

RocketHideout_B2F_Text_GruntLoss:
	.string "....................$"

RocketHideout_B2F_Text_ArianaLoss:
	.string "Tch{SE_M_SUPERSONIC}yo{SE_M_DIVE}reall{SE_M_YAWN}ar{SE_M_REVERSAL}strong.\n"
	.string "It'{SE_M_GRASSWHISTLE}to{SE_M_ATTRACT2}bad.\p"
	.string "I{SE_M_ACID_ARMOR}yo{SE_M_DIVE}wer{SE_M_REVERSAL}t{SE_M_ATTRACT2}joi{SE_M_ATTRACT}Tea{SE_M_MILK_DRINK}Rocket,\n"
	.string "yo{SE_M_DIVE}coul{SE_M_WATERFALL}becom{SE_M_REVERSAL}a{SE_M_ATTRACT}Executive.$"

RocketHideout_Text_ArianaRetreat:
	.string "ARIANA{SE_M_HEAT_WAVE}Bu{SE_M_SPIT_UP}that'{SE_M_GRASSWHISTLE}fine.\n"
	.string "Th{SE_M_REVERSAL}broadcas{SE_M_SPIT_UP}experimen{SE_M_SPIT_UP}wa{SE_M_GRASSWHISTLE}a\l"
	.string "tota{SE_M_BATON_PASS}success.\p"
	.string "I{SE_M_SPIT_UP}doesn'{SE_M_SPIT_UP}matte{SE_M_SAND_TOMB}wha{SE_M_SPIT_UP}happen{SE_M_GRASSWHISTLE}to\n"
	.string "thi{SE_M_GRASSWHISTLE}hideou{SE_M_SPIT_UP}now.\p"
	.string "W{SE_M_REVERSAL}hav{SE_M_REVERSAL}muc{SE_M_TRI_ATTACK}bigge{SE_M_SAND_TOMB}plans.\n"
	.string "You'l{SE_M_BATON_PASS}com{SE_M_REVERSAL}t{SE_M_ATTRACT2}appreciat{SE_M_REVERSAL}Team\l"
	.string "Rocket'{SE_M_GRASSWHISTLE}tru{SE_M_REVERSAL}powe{SE_M_SAND_TOMB}soo{SE_M_ATTRACT}enough.\p"
	.string "Enjo{SE_M_YAWN}yoursel{SE_M_ACID_ARMOR}whil{SE_M_REVERSAL}yo{SE_M_DIVE}can...\n"
	.string "He{SE_M_REVERSAL}he{SE_M_REVERSAL}hee...$"

RocketHideout_Text_LanceStepBack:
	.string "Sorry{SE_M_SUPERSONIC}{PLAYER}{SE_M_PERISH_SONG}{SE_M_HEAL_BELL}sa{SE_M_TWISTER}ho{SE_M_TWISTER}wel{SE_M_BATON_PASS}you\n"
	.string "wer{SE_M_REVERSAL}doing{SE_M_SUPERSONIC}s{SE_M_ATTRACT2}{SE_M_HEAL_BELL}jus{SE_M_SPIT_UP}hun{SE_M_SANDSTORM}back.\p"
	.string "No{SE_M_TWISTER}al{SE_M_BATON_PASS}ther{SE_M_REVERSAL}i{SE_M_GRASSWHISTLE}lef{SE_M_SPIT_UP}t{SE_M_ATTRACT2}d{SE_M_ATTRACT2}i{SE_M_GRASSWHISTLE}t{SE_M_ATTRACT2}turn\n"
	.string "of{SE_M_ACID_ARMOR}tha{SE_M_SPIT_UP}od{SE_M_WATERFALL}radi{SE_M_ATTRACT2}signal.$"

RocketHideout_B2F_Text_LanceElectrodeFaint:
	.string "It'{SE_M_GRASSWHISTLE}thi{SE_M_GRASSWHISTLE}machin{SE_M_REVERSAL}that'{SE_M_GRASSWHISTLE}causing\n"
	.string "al{SE_M_BATON_PASS}th{SE_M_REVERSAL}problems.\p"
	.string "{SE_M_HEAL_BELL}don'{SE_M_SPIT_UP}se{SE_M_REVERSAL}{SE_M_CHARGE}switc{SE_M_TRI_ATTACK}o{SE_M_ATTRACT}it…\p"
	.string "W{SE_M_REVERSAL}hav{SE_M_REVERSAL}n{SE_M_ATTRACT2}choice{SE_M_PERISH_SONG}W{SE_M_REVERSAL}hav{SE_M_REVERSAL}to\n"
	.string "mak{SE_M_REVERSAL}al{SE_M_BATON_PASS}th{SE_M_REVERSAL}ELECTROD{SE_M_SWORDS_DANCE}faint.\p"
	.string "Tha{SE_M_SPIT_UP}shoul{SE_M_WATERFALL}sto{SE_M_MORNING_SUN}thi{SE_M_GRASSWHISTLE}machine\n"
	.string "fro{SE_M_MILK_DRINK}transmittin{SE_M_SANDSTORM}tha{SE_M_SPIT_UP}strange\l"
	.string "signal.\p"
	.string "It'{SE_M_GRASSWHISTLE}n{SE_M_ATTRACT2}faul{SE_M_SPIT_UP}o{SE_M_ACID_ARMOR}th{SE_M_REVERSAL}POKéMON{SE_M_SUPERSONIC}so\n"
	.string "i{SE_M_SPIT_UP}make{SE_M_GRASSWHISTLE}m{SE_M_REVERSAL}fee{SE_M_BATON_PASS}guilty.\p"
	.string "{PLAYER}{SE_M_SUPERSONIC}let'{SE_M_GRASSWHISTLE}spli{SE_M_SPIT_UP}th{SE_M_REVERSAL}job.$"

RocketHideout_B2F_Text_LanceSide:
	.string "LANCE{SE_M_HEAT_WAVE}Leav{SE_M_REVERSAL}thi{SE_M_GRASSWHISTLE}sid{SE_M_REVERSAL}t{SE_M_ATTRACT2}me.$"

RocketHideout_B2F_Text_LanceElectrodeDone:
	.string "LANCE{SE_M_HEAT_WAVE}Tha{SE_M_SPIT_UP}od{SE_M_WATERFALL}signa{SE_M_BATON_PASS}has\n"
	.string "finall{SE_M_YAWN}stopped.\p"
	.string "Th{SE_M_REVERSAL}LAK{SE_M_SWORDS_DANCE}shoul{SE_M_WATERFALL}b{SE_M_REVERSAL}bac{SE_M_ENCORE2}to\n"
	.string "normal.\p"
	.string "You'r{SE_M_REVERSAL}th{SE_M_REVERSAL}hero{SE_M_DRAGON_RAGE}Le{SE_M_SPIT_UP}m{SE_M_REVERSAL}thank\n"
	.string "yo{SE_M_DIVE}o{SE_M_ATTRACT}behal{SE_M_ACID_ARMOR}o{SE_M_ACID_ARMOR}al{SE_M_BATON_PASS}the\l"
	.string "POKéMON.\p"
	.string "Oh{SE_M_SUPERSONIC}yes{SE_M_PERISH_SONG}Yo{SE_M_DIVE}shoul{SE_M_WATERFALL}tak{SE_M_REVERSAL}this.\n"
	.string "{SE_M_HEAL_BELL}foun{SE_M_WATERFALL}i{SE_M_SPIT_UP}here{SE_M_SUPERSONIC}bu{SE_M_SPIT_UP}{SE_M_HEAL_BELL}don't\l"
	.string "hav{SE_M_REVERSAL}an{SE_M_YAWN}nee{SE_M_WATERFALL}fo{SE_M_SAND_TOMB}it.$"

RocketHideout_B2F_Text_LanceWhirlpool:
	.string "That'{SE_M_GRASSWHISTLE}WHIRLPOOL{SE_M_PERISH_SONG}Teac{SE_M_TRI_ATTACK}i{SE_M_SPIT_UP}t{SE_M_ATTRACT2}a\n"
	.string "POKéMO{SE_M_PSYBEAM2}t{SE_M_ATTRACT2}ge{SE_M_SPIT_UP}acros{SE_M_GRASSWHISTLE}wil{SE_M_WATERFALL}water.\p"
	.string "Bu{SE_M_SPIT_UP}kee{SE_M_MORNING_SUN}thi{SE_M_GRASSWHISTLE}i{SE_M_ATTRACT}mind.\p"
	.string "Yo{SE_M_DIVE}ca{SE_M_ATTRACT}us{SE_M_REVERSAL}tha{SE_M_SPIT_UP}ou{SE_M_SPIT_UP}o{SE_M_ACID_ARMOR}battle\n"
	.string "onl{SE_M_YAWN}wit{SE_M_TRI_ATTACK}th{SE_M_REVERSAL}BADG{SE_M_SWORDS_DANCE}from\l"
	.string "MAHOGAN{SE_M_MOONLIGHT}GYM.$"

RocketHideout_B2F_Text_LanceMonMaster:
	.string "{PLAYER}…\p"
	.string "Th{SE_M_REVERSAL}journe{SE_M_YAWN}t{SE_M_ATTRACT2}becomin{SE_M_SANDSTORM}the\n"
	.string "POKéMO{SE_M_PSYBEAM2}MASTE{SE_M_MINIMIZE}i{SE_M_GRASSWHISTLE}lon{SE_M_SANDSTORM}and\l"
	.string "difficult.\p"
	.string "Knowin{SE_M_SANDSTORM}that{SE_M_SUPERSONIC}wil{SE_M_BATON_PASS}yo{SE_M_DIVE}keep\n"
	.string "going?\p"
	.string "…\p"
	.string "{SE_M_HEAL_BELL}see{SE_M_PERISH_SONG}No{SE_M_SUPERSONIC}you'r{SE_M_REVERSAL}right.\p"
	.string "I{SE_M_ACID_ARMOR}yo{SE_M_DIVE}woul{SE_M_WATERFALL}giv{SE_M_REVERSAL}u{SE_M_MORNING_SUN}tha{SE_M_SPIT_UP}easily,\n"
	.string "yo{SE_M_DIVE}woul{SE_M_WATERFALL}hav{SE_M_REVERSAL}neve{SE_M_SAND_TOMB}chase{SE_M_WATERFALL}that\l"
	.string "drea{SE_M_MILK_DRINK}i{SE_M_ATTRACT}th{SE_M_REVERSAL}firs{SE_M_SPIT_UP}place.\p"
	.string "{SE_M_HEAL_BELL}loo{SE_M_ENCORE2}forwar{SE_M_WATERFALL}t{SE_M_ATTRACT2}seein{SE_M_SANDSTORM}you\n"
	.string "again!$"

RocketHideout_B2F_Text_B2FTransmitter:
	.string "It'{SE_M_GRASSWHISTLE}th{SE_M_REVERSAL}radi{SE_M_ATTRACT2}transmitte{SE_M_SAND_TOMB}that's\n"
	.string "sendin{SE_M_SANDSTORM}th{SE_M_REVERSAL}siniste{SE_M_SAND_TOMB}signal.\p"
	.string "It'{SE_M_GRASSWHISTLE}workin{SE_M_SANDSTORM}a{SE_M_SPIT_UP}ful{SE_M_BATON_PASS}capacity.$"

RocketHideout_B2F_Text_B2FDeactivateTransmitter:
	.string "Th{SE_M_REVERSAL}radi{SE_M_ATTRACT2}transmitte{SE_M_SAND_TOMB}ha{SE_M_GRASSWHISTLE}finally\n"
	.string "stoppe{SE_M_WATERFALL}it{SE_M_GRASSWHISTLE}evi{SE_M_BATON_PASS}broadcast.$"

RocketHideout_EventScript_Item_Thief::
	finditem ITEM_TM_THIEF
	end

RocketHideout_B2F_EventScript_LanceTriggerLeft::
	lock
	applymovement OBJ_EVENT_ID_PLAYER, J_Common_Movement_WalkRight1
	waitmovement 0
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	goto RocketHideout_B2F_EventScript_Lance

RocketHideout_B2F_EventScript_LanceTriggerRight::
	lock
	applymovement OBJ_EVENT_ID_PLAYER, J_Common_Movement_WalkLeft1
	waitmovement 0
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	goto RocketHideout_B2F_EventScript_Lance

RocketHideout_B2F_EventScript_Lance::
	lock
	applymovement OBJ_EVENT_ID_PLAYER, J_Common_Movement_WalkUp1
	waitmovement 0
	msgbox RocketHideout_B2F_Text_LanceHeals1, MSGBOX_DEFAULT
	closemessage
	call J_Common_EventScript_OutOfCenterPartyHeal
	msgbox RocketHideout_B2F_Text_LanceHeals2, MSGBOX_DEFAULT
	closemessage
	applymovement2 LOCALID_ROCKETHIDEOUT2_LANCE, RocketHideout_B2F_Movement_LanceGoDeeper
	applymovement2 LOCALID_ROCKETHIDEOUT2_DRAGONITE, RocketHideout_B2F_Movement_DragoniteGoDeeper
	waitmovement LOCALID_ROCKETHIDEOUT2_LANCE
	waitmovement LOCALID_ROCKETHIDEOUT2_DRAGONITE
	setflag JOHTO_FLAG_HIDE_ROCKETHIDEOUT2_LANCE_DRAGONITE
	removeobject LOCALID_ROCKETHIDEOUT2_LANCE
	setvar JOHTO_VAR_MAHOGANY_TOWN_STATE, 6
	removeobject LOCALID_ROCKETHIDEOUT2_DRAGONITE
	release
	end

RocketHideout_B2F_Movement_LanceGoDeeper:
	walk_right
	walk_right
	delay_2
	walk_right
	walk_right
	walk_right
	walk_right
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

RocketHideout_B2F_Movement_DragoniteGoDeeper:
	delay_8
	delay_8
	delay_8
	delay_8
	walk_down
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
	walk_right
	walk_right
	walk_right
	step_end

RocketHideout_B2F_Text_LanceHeals1:
	.string "LANCE{SE_M_HEAT_WAVE}Ar{SE_M_REVERSAL}yo{SE_M_DIVE}al{SE_M_BATON_PASS}right?\p"
	.string "You{SE_M_SAND_TOMB}POKéMO{SE_M_PSYBEAM2}ar{SE_M_REVERSAL}hur{SE_M_SPIT_UP}an{SE_M_WATERFALL}tired.\p"
	.string "Here{SE_M_SUPERSONIC}giv{SE_M_REVERSAL}the{SE_M_MILK_DRINK}som{SE_M_REVERSAL}o{SE_M_ACID_ARMOR}my\n"
	.string "medicine.$"

RocketHideout_B2F_Text_LanceHeals2:
	.string "LANCE{SE_M_HEAT_WAVE}{PLAYER}{SE_M_SUPERSONIC}let'{SE_M_GRASSWHISTLE}giv{SE_M_REVERSAL}it\n"
	.string "ou{SE_M_SAND_TOMB}bes{SE_M_SPIT_UP}fo{SE_M_SAND_TOMB}POKéMON.$"

RocketHideout_B2F_Text_GruntM17Seen:
	.string "Th{SE_M_REVERSAL}doo{SE_M_SAND_TOMB}won'{SE_M_SPIT_UP}open?\p"
	.string "Well{SE_M_SUPERSONIC}duh{SE_M_PERISH_SONG}I{SE_M_SPIT_UP}ha{SE_M_GRASSWHISTLE}t{SE_M_ATTRACT2}hav{SE_M_REVERSAL}a\n"
	.string "passwor{SE_M_WATERFALL}tha{SE_M_SPIT_UP}onl{SE_M_YAWN}TEA{SE_M_GIGA_DRAIN}ROCKET\l"
	.string "knows.$"

RocketHideout_B2F_Text_GruntM17Beaten:
	.string "What{SE_M_SING}{SE_M_HEAL_BELL}lost?$"

RocketHideout_B2F_Text_GruntM17After:
	.string "Heh{SE_M_SUPERSONIC}I'{SE_M_MILK_DRINK}jus{SE_M_SPIT_UP}{SE_M_CHARGE}GRUNT.\p"
	.string "{SE_M_HEAL_BELL}don'{SE_M_SPIT_UP}kno{SE_M_TWISTER}th{SE_M_REVERSAL}password.\n"
	.string "To{SE_M_ATTRACT2}ba{SE_M_WATERFALL}fo{SE_M_SAND_TOMB}you.$"

RocketHideout_B2F_EventScript_Grunt14::
	trainerbattle_single TRAINER_JOHTO_GRUNT_14_HNS, RocketHideout_B2F_Text_GruntM17Seen, RocketHideout_B2F_Text_GruntM17Beaten
	msgbox RocketHideout_B2F_Text_GruntM17After, MSGBOX_AUTOCLOSE
	end

RocketHideout_B2F_Text_GruntM18Seen:
	.string "Oh{SE_M_SUPERSONIC}{SE_M_CHARGE}kid{SE_M_SING}{SE_M_HEAL_BELL}don'{SE_M_SPIT_UP}reall{SE_M_YAWN}like\n"
	.string "this{SE_M_SUPERSONIC}bu{SE_M_SPIT_UP}eliminat{SE_M_REVERSAL}yo{SE_M_DIVE}{SE_M_HEAL_BELL}must.$"

RocketHideout_B2F_Text_GruntM18Beaten:
	.string "{SE_M_HEAL_BELL}kne{SE_M_TWISTER}I'{SE_M_WATERFALL}lose…$"

RocketHideout_B2F_Text_GruntM18After:
	.string "{SE_M_HEAL_BELL}go{SE_M_SPIT_UP}wipe{SE_M_WATERFALL}ou{SE_M_SPIT_UP}o{SE_M_ATTRACT}th{SE_M_REVERSAL}last\n"
	.string "missio{SE_M_ATTRACT}b{SE_M_YAWN}{SE_M_CHARGE}ki{SE_M_WATERFALL}too.\p"
	.string "Whe{SE_M_ATTRACT}w{SE_M_REVERSAL}wer{SE_M_REVERSAL}abductin{SE_M_SANDSTORM}POKéMON,\n"
	.string "thi{SE_M_GRASSWHISTLE}ki{SE_M_WATERFALL}wit{SE_M_TRI_ATTACK}lon{SE_M_SANDSTORM}re{SE_M_WATERFALL}hai{SE_M_SAND_TOMB}and\l"
	.string "mean-lookin{SE_M_SANDSTORM}eye{SE_M_GRASSWHISTLE}just\l"
	.string "creame{SE_M_WATERFALL}me…$"

RocketHideout_B2F_EventScript_Grunt15::
	trainerbattle_single TRAINER_JOHTO_GRUNT_15_HNS, RocketHideout_B2F_Text_GruntM18Seen, RocketHideout_B2F_Text_GruntM18Beaten
	msgbox RocketHideout_B2F_Text_GruntM18After, MSGBOX_AUTOCLOSE
	end

RocketHideout_B2F_Text_GruntM19Seen:
	.string "Yo{SE_M_DIVE}rotte{SE_M_ATTRACT}littl{SE_M_REVERSAL}pest!$"

RocketHideout_B2F_Text_GruntM19Beaten:
	.string "Grrrr…$"

RocketHideout_B2F_Text_GruntM19After:
	.string "Heh{SE_M_SUPERSONIC}onl{SE_M_YAWN}th{SE_M_REVERSAL}bos{SE_M_GRASSWHISTLE}know{SE_M_GRASSWHISTLE}the\n"
	.string "passwor{SE_M_WATERFALL}fo{SE_M_SAND_TOMB}tha{SE_M_SPIT_UP}door.\p"
	.string "Where'{SE_M_GRASSWHISTLE}th{SE_M_REVERSAL}boss{SE_M_SING}Wh{SE_M_ATTRACT2}knows?\n"
	.string "G{SE_M_ATTRACT2}loo{SE_M_ENCORE2}fo{SE_M_SAND_TOMB}yourself.$"

RocketHideout_B2F_EventScript_Grunt16::
	trainerbattle_single TRAINER_JOHTO_GRUNT_16_HNS, RocketHideout_B2F_Text_GruntM19Seen, RocketHideout_B2F_Text_GruntM19Beaten
	msgbox RocketHideout_B2F_Text_GruntM19After, MSGBOX_AUTOCLOSE
	end

