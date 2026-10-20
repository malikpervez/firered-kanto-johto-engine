@ Johto (data/maps/RocketHideout_B1F_hns/scripts.inc), as built into the FireRed game.

RocketHideout_B1F_hns_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, J_RocketHideout_B1F_OnLoad
	.byte 0

J_RocketHideout_B1F_OnLoad::
	setflag JOHTO_FLAG_HIDE_ROCKETHIDEOUT_ROCKETS
	call_if_eq JOHTO_VAR_ROCKET_HIDEOUT_STATUE_1, 2, RocketHideout_B1F_EventScript_SetStatue1
	call_if_eq JOHTO_VAR_ROCKET_HIDEOUT_STATUE_2, 2, RocketHideout_B1F_EventScript_SetStatue2
	call_if_eq JOHTO_VAR_ROCKET_HIDEOUT_STATUE_3, 2, RocketHideout_B1F_EventScript_SetStatue3
	call_if_eq JOHTO_VAR_ROCKET_HIDEOUT_STATUE_4, 2, RocketHideout_B1F_EventScript_SetStatue4
	call_if_eq JOHTO_VAR_ROCKET_HIDEOUT_STATUE_5, 2, RocketHideout_B1F_EventScript_SetStatue5
	end

RocketHideout_B1F_EventScript_SetStatue1::
	setmetatile 45, 1, 0x2A9, TRUE
	return

RocketHideout_B1F_EventScript_SetStatue2::
	setmetatile 24, 1, 0x2A9, TRUE
	return

RocketHideout_B1F_EventScript_SetStatue3::
	setmetatile 45, 6, 0x2A9, TRUE
	return

RocketHideout_B1F_EventScript_SetStatue4::
	setmetatile 45, 19, 0x2A9, TRUE
	return

RocketHideout_B1F_EventScript_SetStatue5::
	setmetatile 27, 19, 0x2A9, TRUE
	return

RocketHideout_B1F_TriggerTest::
	setflag JOHTO_FLAG_HIDE_ROCKETHIDEOUT_ROCKETS
	clearflag JOHTO_FLAG_ROCKETHIDEOUT_SWITCH
	clearflag JOHTO_FLAG_HIDE_ROCKETHIDEOUT2_LANCE_DRAGONITE
	clearflag JOHTO_FLAG_HIDE_ROCKETHIDEOUT2_GATE
	setflag JOHTO_FLAG_HIDE_ROCKETHIDEOUT3_SILVER
	clearflag JOHTO_FLAG_HIDE_ROCKETHIDEOUT3_GATE
	clearflag JOHTO_FLAG_GOT_PASSWORD_FROM_ETO
	clearflag JOHTO_FLAG_GOT_PASSWORD_FROM_GRUNTF
	setvar JOHTO_VAR_ROCKET_PASSWORD, 0
	clearflag JOHTO_FLAG_HIDE_ROCKETHIDEOUT3_MURKROW
	clearflag JOHTO_FLAG_HIDE_ROCKETHIDEOUT3_GIOVANNI
	setflag JOHTO_FLAG_HIDE_ROCKETHIDEOUT3_PETREL
	setflag JOHTO_FLAG_HIDE_ROCKETHIDEOUT2_MURKROWSTAIRS
	setflag JOHTO_FLAG_HIDE_ROCKETHIDEOUT2_MURKROWGATE
	setflag JOHTO_FLAG_HIDE_ROCKETHIDEOUT3_MURKROWSTAIRS
	setflag JOHTO_FLAG_HIDE_ROCKETHIDEOUT2_ARIANA_AND_GRUNT
	setvar VAR_TEMP_3, 1
	end

RocketHideout_B1F_EventScript_SpawnGruntLeft::
	clearflag JOHTO_FLAG_HIDE_ROCKETHIDEOUT_ROCKETS
	addobject VAR_TEMP_0
	return

RocketHideout_B1F_EventScript_SpawnGruntRight::
	clearflag JOHTO_FLAG_HIDE_ROCKETHIDEOUT_ROCKETS
	addobject VAR_TEMP_0
	return

RocketHideout_B1F_EventScript_HeightAdjust::
	applymovement VAR_TEMP_0, J_Common_Movement_WalkDown1
	waitmovement 0
	return

RocketHideout_B1F_Trigger_SpawnGruntStatue1::
	setvar 16384, 1
	call RocketHideout_B1F_EventScript_SpawnGruntLeft
	setvar JOHTO_VAR_ROCKET_HIDEOUT_STATUE_1, LOCALID_ROCKETHIDEOUT_GRUNTM1
	end

RocketHideout_B1F_Trigger_Statue1::
	lock
	setvar VAR_TEMP_0, LOCALID_ROCKETHIDEOUT_GRUNTM1
	call RocketHideout_B1F_EventScript_SpawnGruntLeft
	call RocketHideout_B1F_EventScript_SpawnGruntRight
	call RocketHideout_B1F_Trigger_StatueGruntLeft
	setvar JOHTO_VAR_ROCKET_HIDEOUT_STATUE_1, 2
	fadescreenswapbuffers FADE_TO_BLACK
	removeobject VAR_TEMP_0
	fadescreenswapbuffers FADE_FROM_BLACK
	setmetatile 45, 1, 0x2A9, TRUE
	special DrawWholeMapView
	release
	end

RocketHideout_B1F_Trigger_SpawnGruntStatue2::
	setvar VAR_TEMP_0, LOCALID_ROCKETHIDEOUT_GRUNTM2
	call RocketHideout_B1F_EventScript_SpawnGruntRight
	setvar JOHTO_VAR_ROCKET_HIDEOUT_STATUE_2, 1
	end

RocketHideout_B1F_Trigger_Statue2::
	lock
	setvar 16384, 2
	call RocketHideout_B1F_EventScript_SpawnGruntLeft
	call RocketHideout_B1F_EventScript_SpawnGruntRight
	call RocketHideout_B1F_Trigger_StatueGruntRight
	setvar JOHTO_VAR_ROCKET_HIDEOUT_STATUE_2, LOCALID_ROCKETHIDEOUT_GRUNTM2
	fadescreenswapbuffers FADE_TO_BLACK
	removeobject VAR_TEMP_0
	fadescreenswapbuffers FADE_FROM_BLACK
	setmetatile 24, 1, 0x2A9, TRUE
	special DrawWholeMapView
	release
	end

RocketHideout_B1F_Trigger_SpawnGruntStatue3::
	setvar VAR_TEMP_0, LOCALID_ROCKETHIDEOUT_GRUNTM3
	call RocketHideout_B1F_EventScript_SpawnGruntLeft
	setvar JOHTO_VAR_ROCKET_HIDEOUT_STATUE_3, 1
	end

RocketHideout_B1F_Trigger_Statue3::
	lock
	setvar VAR_TEMP_0, LOCALID_ROCKETHIDEOUT_GRUNTM3
	call RocketHideout_B1F_EventScript_SpawnGruntLeft
	call RocketHideout_B1F_EventScript_SpawnGruntRight
	call RocketHideout_B1F_Trigger_StatueGruntLeft
	setvar JOHTO_VAR_ROCKET_HIDEOUT_STATUE_3, 2
	fadescreenswapbuffers FADE_TO_BLACK
	removeobject VAR_TEMP_0
	fadescreenswapbuffers FADE_FROM_BLACK
	setmetatile 45, 6, 0x2A9, TRUE
	special DrawWholeMapView
	release
	end

RocketHideout_B1F_Trigger_SpawnGruntStatue4::
	setvar VAR_TEMP_0, LOCALID_ROCKETHIDEOUT_GRUNTM4
	call RocketHideout_B1F_EventScript_SpawnGruntLeft
	setvar JOHTO_VAR_ROCKET_HIDEOUT_STATUE_4, 1
	end

RocketHideout_B1F_Trigger_Statue4::
	lock
	setvar VAR_TEMP_0, LOCALID_ROCKETHIDEOUT_GRUNTM4
	call RocketHideout_B1F_EventScript_SpawnGruntLeft
	call RocketHideout_B1F_EventScript_SpawnGruntRight
	call RocketHideout_B1F_Trigger_StatueGruntLeft
	setvar JOHTO_VAR_ROCKET_HIDEOUT_STATUE_4, 2
	fadescreenswapbuffers FADE_TO_BLACK
	removeobject VAR_TEMP_0
	fadescreenswapbuffers FADE_FROM_BLACK
	setmetatile 45, 19, 0x2A9, TRUE
	special DrawWholeMapView
	release
	end

RocketHideout_B1F_Trigger_SpawnGruntStatue5::
	setvar VAR_TEMP_0, LOCALID_ROCKETHIDEOUT_GRUNTM4
	call RocketHideout_B1F_EventScript_SpawnGruntRight
	setvar JOHTO_VAR_ROCKET_HIDEOUT_STATUE_5, 1
	end

RocketHideout_B1F_Trigger_Statue5::
	lock
	setvar VAR_TEMP_0, LOCALID_ROCKETHIDEOUT_GRUNTM4
	call RocketHideout_B1F_EventScript_SpawnGruntLeft
	call RocketHideout_B1F_EventScript_SpawnGruntRight
	call RocketHideout_B1F_Trigger_StatueGruntRight
	setvar JOHTO_VAR_ROCKET_HIDEOUT_STATUE_5, 2
	fadescreenswapbuffers FADE_TO_BLACK
	removeobject VAR_TEMP_0
	fadescreenswapbuffers FADE_FROM_BLACK
	setmetatile 27, 19, 0x2A9, TRUE
	special DrawWholeMapView
	release
	end

RocketHideout_B1F_Trigger_StatueGruntLeft::
	playse SE_WARP_IN
	applymovement OBJ_EVENT_ID_PLAYER, J_Common_Movement_ExclamationMark
	getplayerxy VAR_TEMP_1, VAR_TEMP_2
	call_if_eq VAR_TEMP_2, 4, RocketHideout_B1F_EventScript_HeightAdjust
	call_if_eq VAR_TEMP_2, 9, RocketHideout_B1F_EventScript_HeightAdjust
	call_if_eq VAR_TEMP_2, 22, RocketHideout_B1F_EventScript_HeightAdjust
	applymovement VAR_TEMP_0, RocketHideout_B1F_Movement_GruntWalkRight
	waitmovement 0
	turnobject OBJ_EVENT_ID_PLAYER, DIR_WEST
	msgbox RocketHideout_B1F_Text_CameraGrunt1Seen, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_JOHTO_GRUNT_17_HNS, RocketHideout_B1F_Text_CameraGrunt1Beaten
	applymovement VAR_TEMP_0, RocketHideout_B1F_Movement_GruntWalkLeft
	waitmovement 0
	delay 55
	applymovement VAR_TEMP_0, RocketHideout_B1F_Movement_GruntWalkRight
	waitmovement 0
	msgbox RocketHideout_B1F_Text_CameraGrunt2Seen, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_JOHTO_GRUNT_18_HNS, RocketHideout_B1F_Text_CameraGrunt2Beaten
	applymovement VAR_TEMP_0, RocketHideout_B1F_Movement_GruntWalkLeft
	waitmovement 0
	setflag JOHTO_FLAG_HIDE_ROCKETHIDEOUT_ROCKETS
	removeobject VAR_TEMP_0
	removeobject LOCALID_ROCKETHIDEOUT_GRUNTM3
	removeobject LOCALID_ROCKETHIDEOUT_GRUNTM1
	return

RocketHideout_B1F_Trigger_StatueGruntRight::
	playse SE_WARP_IN
	applymovement OBJ_EVENT_ID_PLAYER, J_Common_Movement_ExclamationMark
	getplayerxy VAR_TEMP_1, VAR_TEMP_2
	call_if_eq VAR_TEMP_2, 4, RocketHideout_B1F_EventScript_HeightAdjust
	call_if_eq VAR_TEMP_2, 9, RocketHideout_B1F_EventScript_HeightAdjust
	call_if_eq VAR_TEMP_2, 22, RocketHideout_B1F_EventScript_HeightAdjust
	applymovement VAR_TEMP_0, RocketHideout_B1F_Movement_GruntWalkLeft
	waitmovement 0
	turnobject OBJ_EVENT_ID_PLAYER, DIR_EAST
	msgbox RocketHideout_B1F_Text_CameraGrunt1Seen, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_JOHTO_GRUNT_17_HNS, RocketHideout_B1F_Text_CameraGrunt1Beaten
	applymovement VAR_TEMP_0, RocketHideout_B1F_Movement_GruntWalkRight
	waitmovement 0
	delay 55
	applymovement VAR_TEMP_0, RocketHideout_B1F_Movement_GruntWalkLeft
	waitmovement 0
	msgbox RocketHideout_B1F_Text_CameraGrunt2Seen, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_JOHTO_GRUNT_18_HNS, RocketHideout_B1F_Text_CameraGrunt2Beaten
	applymovement VAR_TEMP_0, RocketHideout_B1F_Movement_GruntWalkRight
	waitmovement 0
	setflag JOHTO_FLAG_HIDE_ROCKETHIDEOUT_ROCKETS
	removeobject VAR_TEMP_0
	removeobject LOCALID_ROCKETHIDEOUT_GRUNTM3
	removeobject LOCALID_ROCKETHIDEOUT_GRUNTM1
	return

RocketHideout_B1F_Movement_GruntWalkRight:
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	step_end

RocketHideout_B1F_Movement_GruntWalkLeft:
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	step_end

RocketHideout_B1F_Text_CameraGrunt1Seen:
	.string "Hey!\n"
	.string "Intruder alert!$"

RocketHideout_B1F_Text_CameraGrunt1Beaten:
	.string "Dang… I failed…$"

RocketHideout_B1F_Text_CameraGrunt2Seen:
	.string "It's my turn! There's no escape!$"

RocketHideout_B1F_Text_CameraGrunt2Beaten:
	.string "Surveillance cams are in the\n"
	.string "POKéMON statues.\p"
	.string "We'll keep appearing until you\n"
	.string "trip a secret switch.$"

RocketHideout_B1F_EventScript_TrainerJed::
	trainerbattle_single TRAINER_JOHTO_JED_HNS, RocketHideout_B1F_Text_ScientistJedSeen, RocketHideout_B1F_Text_ScientistJedBeaten
	msgbox RocketHideout_B1F_Text_ScientistJedAfter, MSGBOX_AUTOCLOSE
	end

RocketHideout_B1F_Text_ScientistJedSeen:
	.string "This was once a ninja hideout.\p"
	.string "There are traps to confound\n"
	.string "intruders like you.$"

RocketHideout_B1F_Text_ScientistJedBeaten:
	.string "I get it…$"

RocketHideout_B1F_Text_ScientistJedAfter:
	.string "All right. I'll divulge a secret\n"
	.string "about our hideout.\p"
	.string "That thing on the floor up ahead\n"
	.string "is a warp panel.\p"
	.string "If you step on it, you'll be\n"
	.string "warped back to the entrance.$"

RocketHideout_B1F_Text_GruntM16Seen:
	.string "Heheh. Feeling lucky, punk?$"

RocketHideout_B1F_Text_GruntM16Beaten:
	.string "Kaboom!$"

RocketHideout_B1F_Text_GruntM16After:
	.string "I don't even know where the traps\n"
	.string "are planted.\p"
	.string "You'll just have to collect your\n"
	.string "courage and walk.$"

RocketHideout_B1F_EventScript_Rocket16::
	trainerbattle_single TRAINER_JOHTO_GRUNT_13_HNS, RocketHideout_B1F_Text_GruntM16Seen, RocketHideout_B1F_Text_GruntM16Beaten
	msgbox RocketHideout_B1F_Text_GruntM16After, MSGBOX_AUTOCLOSE
	end

RocketHideout_B1F_EventScript_Item_BigNugget::
	finditem ITEM_BIG_NUGGET
	end

RocketHideout_B1F_EventScript_Item_HyperPotion::
	finditem ITEM_HYPER_POTION
	end

RocketHideout_B1F_EventScript_Item_Revive::
	finditem ITEM_REVIVE
	end

RocketHideout_B1F_EventScript_Persian::
	msgbox RocketHideout_B1F_Text_SecurityCameraStatue, MSGBOX_NPC
	end

RocketHideout_B1F_Text_SecurityCameraStatue:
	.string "It's a PERSIAN statue…$"

RocketHideout_B1F_EventScript_DummyPanel::
	msgbox RocketHideout_B1F_Text_NothingThere, MSGBOX_SIGN
	end

RocketHideout_B1F_EventScript_Switch::
	lock
	goto_if_set JOHTO_FLAG_ROCKETHIDEOUT_SWITCH, RocketHideout_B1F_EventScript_TurnOffSwitch
	msgbox RocketHideout_B1F_Text_SecretSwitch, MSGBOX_DEFAULT
	setvar JOHTO_VAR_ROCKET_HIDEOUT_STATUE_1, 2
	setvar JOHTO_VAR_ROCKET_HIDEOUT_STATUE_2, 2
	setvar JOHTO_VAR_ROCKET_HIDEOUT_STATUE_3, 2
	setvar JOHTO_VAR_ROCKET_HIDEOUT_STATUE_4, 2
	setvar JOHTO_VAR_ROCKET_HIDEOUT_STATUE_5, 2
	setmetatile 45, 1, 0x2A9, TRUE
	setmetatile 24, 1, 0x2A9, TRUE
	setmetatile 45, 6, 0x2A9, TRUE
	setmetatile 45, 19, 0x2A9, TRUE
	setmetatile 27, 19, 0x2A9, TRUE
	special DrawWholeMapView
	setflag JOHTO_FLAG_ROCKETHIDEOUT_SWITCH
	release
	end

RocketHideout_B1F_EventScript_TurnOffSwitch::
	msgbox RocketHideout_B1F_Text_SwitchOff, MSGBOX_DEFAULT
	setvar JOHTO_VAR_ROCKET_HIDEOUT_STATUE_1, 0
	setvar JOHTO_VAR_ROCKET_HIDEOUT_STATUE_2, 0
	setvar JOHTO_VAR_ROCKET_HIDEOUT_STATUE_3, 0
	setvar JOHTO_VAR_ROCKET_HIDEOUT_STATUE_4, 0
	setvar JOHTO_VAR_ROCKET_HIDEOUT_STATUE_5, 0
	setmetatile 45, 1, 0x2A8, TRUE
	setmetatile 24, 1, 0x2A8, TRUE
	setmetatile 45, 6, 0x2A8, TRUE
	setmetatile 45, 19, 0x2A8, TRUE
	setmetatile 27, 19, 0x2A8, TRUE
	special DrawWholeMapView
	clearflag JOHTO_FLAG_ROCKETHIDEOUT_SWITCH
	release
	end

RocketHideout_B1F_Text_NothingThere:
	.string "A strange panel... Nothing here.$"

RocketHideout_B1F_Text_SecretSwitch:
	.string "A secret switch! Better press it.$"

RocketHideout_B1F_Text_SwitchOff:
	.string "The switch is turned off.$"

