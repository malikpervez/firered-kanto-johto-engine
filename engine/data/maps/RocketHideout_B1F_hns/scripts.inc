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
	.string "Intrude{SE_M_SAND_TOMB}alert!$"

RocketHideout_B1F_Text_CameraGrunt1Beaten:
	.string "Dang{SE_M_DIZZY_PUNCH}{SE_M_HEAL_BELL}failed…$"

RocketHideout_B1F_Text_CameraGrunt2Seen:
	.string "It'{SE_M_GRASSWHISTLE}m{SE_M_YAWN}turn{SE_M_DRAGON_RAGE}There'{SE_M_GRASSWHISTLE}n{SE_M_ATTRACT2}escape!$"

RocketHideout_B1F_Text_CameraGrunt2Beaten:
	.string "Surveillanc{SE_M_REVERSAL}cam{SE_M_GRASSWHISTLE}ar{SE_M_REVERSAL}i{SE_M_ATTRACT}the\n"
	.string "POKéMO{SE_M_PSYBEAM2}statues.\p"
	.string "We'l{SE_M_BATON_PASS}kee{SE_M_MORNING_SUN}appearin{SE_M_SANDSTORM}unti{SE_M_BATON_PASS}you\n"
	.string "tri{SE_M_MORNING_SUN}{SE_M_CHARGE}secre{SE_M_SPIT_UP}switch.$"

RocketHideout_B1F_EventScript_TrainerJed::
	trainerbattle_single TRAINER_JOHTO_JED_HNS, RocketHideout_B1F_Text_ScientistJedSeen, RocketHideout_B1F_Text_ScientistJedBeaten
	msgbox RocketHideout_B1F_Text_ScientistJedAfter, MSGBOX_AUTOCLOSE
	end

RocketHideout_B1F_Text_ScientistJedSeen:
	.string "Thi{SE_M_GRASSWHISTLE}wa{SE_M_GRASSWHISTLE}onc{SE_M_REVERSAL}{SE_M_CHARGE}ninj{SE_M_CHARGE}hideout.\p"
	.string "Ther{SE_M_REVERSAL}ar{SE_M_REVERSAL}trap{SE_M_GRASSWHISTLE}t{SE_M_ATTRACT2}confound\n"
	.string "intruder{SE_M_GRASSWHISTLE}lik{SE_M_REVERSAL}you.$"

RocketHideout_B1F_Text_ScientistJedBeaten:
	.string "{SE_M_HEAL_BELL}ge{SE_M_SPIT_UP}it…$"

RocketHideout_B1F_Text_ScientistJedAfter:
	.string "Al{SE_M_BATON_PASS}right{SE_M_PERISH_SONG}I'l{SE_M_BATON_PASS}divulg{SE_M_REVERSAL}{SE_M_CHARGE}secret\n"
	.string "abou{SE_M_SPIT_UP}ou{SE_M_SAND_TOMB}hideout.\p"
	.string "Tha{SE_M_SPIT_UP}thin{SE_M_SANDSTORM}o{SE_M_ATTRACT}th{SE_M_REVERSAL}floo{SE_M_SAND_TOMB}u{SE_M_MORNING_SUN}ahead\n"
	.string "i{SE_M_GRASSWHISTLE}{SE_M_CHARGE}war{SE_M_MORNING_SUN}panel.\p"
	.string "I{SE_M_ACID_ARMOR}yo{SE_M_DIVE}ste{SE_M_MORNING_SUN}o{SE_M_ATTRACT}it{SE_M_SUPERSONIC}you'l{SE_M_BATON_PASS}be\n"
	.string "warpe{SE_M_WATERFALL}bac{SE_M_ENCORE2}t{SE_M_ATTRACT2}th{SE_M_REVERSAL}entrance.$"

RocketHideout_B1F_Text_GruntM16Seen:
	.string "Heheh{SE_M_PERISH_SONG}Feelin{SE_M_SANDSTORM}lucky{SE_M_SUPERSONIC}punk?$"

RocketHideout_B1F_Text_GruntM16Beaten:
	.string "Kaboom!$"

RocketHideout_B1F_Text_GruntM16After:
	.string "{SE_M_HEAL_BELL}don'{SE_M_SPIT_UP}eve{SE_M_ATTRACT}kno{SE_M_TWISTER}wher{SE_M_REVERSAL}th{SE_M_REVERSAL}traps\n"
	.string "ar{SE_M_REVERSAL}planted.\p"
	.string "You'l{SE_M_BATON_PASS}jus{SE_M_SPIT_UP}hav{SE_M_REVERSAL}t{SE_M_ATTRACT2}collec{SE_M_SPIT_UP}your\n"
	.string "courag{SE_M_REVERSAL}an{SE_M_WATERFALL}walk.$"

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
	.string "It'{SE_M_GRASSWHISTLE}{SE_M_CHARGE}PERSIA{SE_M_PSYBEAM2}statue…$"

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
	.string "{SE_M_BONEMERANG}strang{SE_M_REVERSAL}panel..{SE_M_PERISH_SONG}Nothin{SE_M_SANDSTORM}here.$"

RocketHideout_B1F_Text_SecretSwitch:
	.string "{SE_M_BONEMERANG}secre{SE_M_SPIT_UP}switch{SE_M_DRAGON_RAGE}Bette{SE_M_SAND_TOMB}pres{SE_M_GRASSWHISTLE}it.$"

RocketHideout_B1F_Text_SwitchOff:
	.string "Th{SE_M_REVERSAL}switc{SE_M_TRI_ATTACK}i{SE_M_GRASSWHISTLE}turne{SE_M_WATERFALL}off.$"

