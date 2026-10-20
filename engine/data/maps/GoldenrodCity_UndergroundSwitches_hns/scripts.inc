@ Johto (data/maps/GoldenrodCity_UndergroundSwitches_hns/scripts.inc), as built into the FireRed game.

GoldenrodCity_UndergroundSwitches_hns_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, GoldenrodUnderground1_OnLoad
	.byte 0

GoldenrodUnderground1_OnLoad::
	setvar VAR_TEMP_0, 0
	call_if_set JOHTO_FLAG_COMPLETED_SWITCHES, GoldenrodUnderground1_ClearTheWay
	clearflag JOHTO_FLAG_GOLDENROD_SWITCH_1
	clearflag JOHTO_FLAG_GOLDENROD_SWITCH_2
	clearflag JOHTO_FLAG_GOLDENROD_SWITCH_3
	clearflag JOHTO_FLAG_GOLDENROD_SWITCH_ORDER
	end

GoldenrodUnderground1_ClearTheWay::
	call GoldenrodCity_UndergroundSwitches_EventScript_CreateWall1
	call GoldenrodCity_UndergroundSwitches_EventScript_RemoveWall2
	call GoldenrodCity_UndergroundSwitches_EventScript_RemoveWall3
	call GoldenrodCity_UndergroundSwitches_EventScript_CreateWall4
	call GoldenrodCity_UndergroundSwitches_EventScript_RemoveWall5
	call GoldenrodCity_UndergroundSwitches_EventScript_CreateWall6
	return

GoldenrodCity_UndergroundSwitches_InDoorAntiLock::
	lock
	msgbox GoldenrodCity_UndergroundSwitches_EventScript_AntiSoftLock_Text, MSGBOX_YESNO
	closemessage
	goto_if_eq VAR_RESULT, FALSE, J_Common_EventScript_NoOp
	warp MAP_GOLDENROD_CITY_UNDERGROUND_SWITCHES_HNS, 2, 25, 5
	waitstate
	release
	end

GoldenrodCity_UndergroundSwitches_InDoorAntiLock2::
	lock
	setvar VAR_TEMP_0, 1
	release
	end

GoldenrodCity_UndergroundSwitches_EventScript_AntiSoftLock::
	lock
	msgbox GoldenrodCity_UndergroundSwitches_EventScript_AntiSoftLock_Text, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, TRUE, GoldenrodCity_UndergroundSwitches_EventScript_AntiSoftLock_TP
	closemessage
	release
	end

GoldenrodCity_UndergroundSwitches_EventScript_AntiSoftLock_TP::
	warp MAP_GOLDENROD_CITY_UNDERGROUND_SWITCHES_HNS, 2, 25, 5
	waitstate
	release
	end

GoldenrodCity_UndergroundSwitches_EventScript_AntiSoftLock_Text::
	.string "Yo{SE_M_DIVE}ma{SE_M_YAWN}b{SE_M_REVERSAL}stuck.\p"
	.string "G{SE_M_ATTRACT2}bac{SE_M_ENCORE2}t{SE_M_ATTRACT2}th{SE_M_REVERSAL}entrance\n"
	.string "an{SE_M_WATERFALL}rese{SE_M_SPIT_UP}switches?$"

GoldenrodCity_UndergroundSwitches_EventScript_Panel1::
	lock
	goto_if_unset JOHTO_FLAG_GOLDENROD_SWITCH_1, GoldenrodCity_UndergroundSwitches_EventScript_Panel1Activate
	clearflag JOHTO_FLAG_GOLDENROD_SWITCH_1
	playse SE_BANG
	msgbox GoldenrodUnderground_Text_Switch1Off, MSGBOX_DEFAULT
	closemessage
	call GoldenrodCity_UndergroundSwitches_EventScript_CreateWall1
	call GoldenrodCity_UndergroundSwitches_EventScript_CreateWall2
	call GoldenrodCity_UndergroundSwitches_EventScript_CreateWall3
	call GoldenrodCity_UndergroundSwitches_EventScript_CreateWall4
	call GoldenrodCity_UndergroundSwitches_EventScript_CreateWall5
	call GoldenrodCity_UndergroundSwitches_EventScript_CreateWall6
	special DrawWholeMapView
	waitse
	release
	end

GoldenrodCity_UndergroundSwitches_EventScript_Panel1Activate::
	setflag JOHTO_FLAG_GOLDENROD_SWITCH_1
	goto_if_set JOHTO_FLAG_GOLDENROD_SWITCH_ORDER, GoldenrodCity_UndergroundSwitches_EventScript_Panel1ActivateCorrect
	clearflag JOHTO_FLAG_GOLDENROD_SWITCH_ORDER
	playse SE_BANG
	msgbox GoldenrodUnderground_Text_Switch1, MSGBOX_DEFAULT
	closemessage
	call GoldenrodCity_UndergroundSwitches_EventScript_RemoveWall1
	call GoldenrodCity_UndergroundSwitches_EventScript_RemoveWall2
	call GoldenrodCity_UndergroundSwitches_EventScript_RemoveWall3
	call GoldenrodCity_UndergroundSwitches_EventScript_CreateWall4
	call GoldenrodCity_UndergroundSwitches_EventScript_CreateWall5
	call GoldenrodCity_UndergroundSwitches_EventScript_CreateWall6
	special DrawWholeMapView
	waitse
	release
	end

GoldenrodCity_UndergroundSwitches_EventScript_Panel1ActivateCorrect::
	playse SE_CLICK
	setflag JOHTO_FLAG_COMPLETED_SWITCHES
	msgbox GoldenrodUnderground_Text_Switch1, MSGBOX_DEFAULT
	closemessage
	call GoldenrodCity_UndergroundSwitches_EventScript_CreateWall1
	call GoldenrodCity_UndergroundSwitches_EventScript_RemoveWall2
	call GoldenrodCity_UndergroundSwitches_EventScript_RemoveWall3
	call GoldenrodCity_UndergroundSwitches_EventScript_CreateWall4
	call GoldenrodCity_UndergroundSwitches_EventScript_RemoveWall5
	call GoldenrodCity_UndergroundSwitches_EventScript_CreateWall6
	special DrawWholeMapView
	waitse
	release
	end

GoldenrodCity_UndergroundSwitches_EventScript_Panel2::
	lock
	goto_if_unset JOHTO_FLAG_GOLDENROD_SWITCH_2, GoldenrodCity_UndergroundSwitches_EventScript_Panel2Activate
	clearflag JOHTO_FLAG_GOLDENROD_SWITCH_2
	clearflag JOHTO_FLAG_GOLDENROD_SWITCH_ORDER
	playse SE_BANG
	msgbox GoldenrodUnderground_Text_Switch2Off, MSGBOX_DEFAULT
	closemessage
	call GoldenrodCity_UndergroundSwitches_EventScript_CreateWall1
	call GoldenrodCity_UndergroundSwitches_EventScript_CreateWall2
	call GoldenrodCity_UndergroundSwitches_EventScript_CreateWall3
	call GoldenrodCity_UndergroundSwitches_EventScript_CreateWall4
	call GoldenrodCity_UndergroundSwitches_EventScript_CreateWall5
	call GoldenrodCity_UndergroundSwitches_EventScript_CreateWall6
	special DrawWholeMapView
	waitse
	release
	end

GoldenrodCity_UndergroundSwitches_EventScript_Panel2Activate::
	setflag JOHTO_FLAG_GOLDENROD_SWITCH_2
	goto_if_set JOHTO_FLAG_GOLDENROD_SWITCH_1, GoldenrodCity_UndergroundSwitches_EventScript_Panel2ActivateWrong
	goto_if_set JOHTO_FLAG_GOLDENROD_SWITCH_3, GoldenrodCity_UndergroundSwitches_EventScript_Panel2ActivateCorrect
	playse SE_BANG
	msgbox GoldenrodUnderground_Text_Switch2, MSGBOX_DEFAULT
	closemessage
	call GoldenrodCity_UndergroundSwitches_EventScript_RemoveWall1
	call GoldenrodCity_UndergroundSwitches_EventScript_RemoveWall2
	call GoldenrodCity_UndergroundSwitches_EventScript_RemoveWall3
	call GoldenrodCity_UndergroundSwitches_EventScript_CreateWall4
	call GoldenrodCity_UndergroundSwitches_EventScript_CreateWall5
	call GoldenrodCity_UndergroundSwitches_EventScript_CreateWall6
	special DrawWholeMapView
	waitse
	release
	end

GoldenrodCity_UndergroundSwitches_EventScript_Panel2ActivateWrong::
	clearflag JOHTO_FLAG_GOLDENROD_SWITCH_ORDER
	playse SE_BANG
	msgbox GoldenrodUnderground_Text_Switch2, MSGBOX_DEFAULT
	closemessage
	call GoldenrodCity_UndergroundSwitches_EventScript_RemoveWall1
	call GoldenrodCity_UndergroundSwitches_EventScript_RemoveWall2
	call GoldenrodCity_UndergroundSwitches_EventScript_RemoveWall3
	call GoldenrodCity_UndergroundSwitches_EventScript_CreateWall4
	call GoldenrodCity_UndergroundSwitches_EventScript_CreateWall5
	call GoldenrodCity_UndergroundSwitches_EventScript_CreateWall6
	special DrawWholeMapView
	waitse
	release
	end

GoldenrodCity_UndergroundSwitches_EventScript_Panel2ActivateCorrect::
	setflag JOHTO_FLAG_GOLDENROD_SWITCH_ORDER
	playse SE_CLICK
	msgbox GoldenrodUnderground_Text_Switch2, MSGBOX_DEFAULT
	closemessage
	call GoldenrodCity_UndergroundSwitches_EventScript_CreateWall1
	call GoldenrodCity_UndergroundSwitches_EventScript_RemoveWall2
	call GoldenrodCity_UndergroundSwitches_EventScript_RemoveWall3
	call GoldenrodCity_UndergroundSwitches_EventScript_CreateWall4
	call GoldenrodCity_UndergroundSwitches_EventScript_CreateWall5
	call GoldenrodCity_UndergroundSwitches_EventScript_CreateWall6
	special DrawWholeMapView
	waitse
	release
	end

GoldenrodCity_UndergroundSwitches_EventScript_Panel3::
	lock
	goto_if_unset JOHTO_FLAG_GOLDENROD_SWITCH_3, GoldenrodCity_UndergroundSwitches_EventScript_Panel3Activate
	clearflag JOHTO_FLAG_GOLDENROD_SWITCH_3
	clearflag JOHTO_FLAG_GOLDENROD_SWITCH_ORDER
	playse SE_BANG
	msgbox GoldenrodUnderground_Text_Switch3Off, MSGBOX_DEFAULT
	closemessage
	call GoldenrodCity_UndergroundSwitches_EventScript_CreateWall1
	call GoldenrodCity_UndergroundSwitches_EventScript_CreateWall2
	call GoldenrodCity_UndergroundSwitches_EventScript_CreateWall3
	call GoldenrodCity_UndergroundSwitches_EventScript_CreateWall4
	call GoldenrodCity_UndergroundSwitches_EventScript_CreateWall5
	call GoldenrodCity_UndergroundSwitches_EventScript_CreateWall6
	special DrawWholeMapView
	waitse
	release
	end

GoldenrodCity_UndergroundSwitches_EventScript_Panel3Activate::
	setflag JOHTO_FLAG_GOLDENROD_SWITCH_3
	clearflag JOHTO_FLAG_GOLDENROD_SWITCH_ORDER
	playse SE_CLICK
	msgbox GoldenrodUnderground_Text_Switch3, MSGBOX_DEFAULT
	closemessage
	call GoldenrodCity_UndergroundSwitches_EventScript_RemoveWall1
	call GoldenrodCity_UndergroundSwitches_EventScript_RemoveWall4
	call GoldenrodCity_UndergroundSwitches_EventScript_CreateWall2
	call GoldenrodCity_UndergroundSwitches_EventScript_CreateWall3
	call GoldenrodCity_UndergroundSwitches_EventScript_CreateWall5
	call GoldenrodCity_UndergroundSwitches_EventScript_CreateWall6
	special DrawWholeMapView
	waitse
	release
	end

GoldenrodCity_UndergroundSwitches_EventScript_CreateWall1::
	setmetatile 5, 7, 0x399, FALSE
	setmetatile 6, 7, 0x39A, FALSE
	setmetatile 7, 7, 0x39B, FALSE

	setmetatile 5, 8, 0x3A1, FALSE
	setmetatile 6, 8, 0x3A2, FALSE
	setmetatile 7, 8, 0x3A3, FALSE
	return

GoldenrodCity_UndergroundSwitches_EventScript_CreateWall2::
	setmetatile 14, 7, 0x399, FALSE
	setmetatile 15, 7, 0x39A, FALSE
	setmetatile 16, 7, 0x39B, FALSE

	setmetatile 14, 8, 0x3A1, FALSE
	setmetatile 15, 8, 0x3A2, FALSE
	setmetatile 16, 8, 0x3A3, FALSE
	return

GoldenrodCity_UndergroundSwitches_EventScript_CreateWall3::
	setmetatile 23, 7, 0x399, FALSE
	setmetatile 24, 7, 0x39A, FALSE
	setmetatile 25, 7, 0x39B, FALSE

	setmetatile 23, 8, 0x3A1, FALSE
	setmetatile 24, 8, 0x3A2, FALSE
	setmetatile 25, 8, 0x3A3, FALSE
	return

GoldenrodCity_UndergroundSwitches_EventScript_CreateWall4::
	setmetatile 5, 11, 0x399, FALSE
	setmetatile 6, 11, 0x39A, FALSE
	setmetatile 7, 11, 0x39B, FALSE

	setmetatile 5, 12, 0x3A1, FALSE
	setmetatile 6, 12, 0x3A2, FALSE
	setmetatile 7, 12, 0x3A3, FALSE
	return

GoldenrodCity_UndergroundSwitches_EventScript_CreateWall5::
	setmetatile 14, 11, 0x399, FALSE
	setmetatile 15, 11, 0x39A, FALSE
	setmetatile 16, 11, 0x39B, FALSE

	setmetatile 14, 12, 0x3A1, FALSE
	setmetatile 15, 12, 0x3A2, FALSE
	setmetatile 16, 12, 0x3A3, FALSE
	return

GoldenrodCity_UndergroundSwitches_EventScript_CreateWall6::
	setmetatile 23, 11, 0x399, FALSE
	setmetatile 24, 11, 0x39A, FALSE
	setmetatile 25, 11, 0x39B, FALSE

	setmetatile 23, 12, 0x3A1, FALSE
	setmetatile 24, 12, 0x3A2, FALSE
	setmetatile 25, 12, 0x3A3, FALSE
	return

GoldenrodCity_UndergroundSwitches_EventScript_RemoveWall1::
	setmetatile 5, 7, 0x378, FALSE
	setmetatile 6, 7, 0x379, FALSE
	setmetatile 7, 7, 0x37A, FALSE

	setmetatile 5, 8, 0x380, FALSE
	setmetatile 6, 8, 0x381, FALSE
	setmetatile 7, 8, 0x382, FALSE
	return

GoldenrodCity_UndergroundSwitches_EventScript_RemoveWall2::
	setmetatile 14, 7, 0x378, FALSE
	setmetatile 15, 7, 0x379, FALSE
	setmetatile 16, 7, 0x37A, FALSE

	setmetatile 14, 8, 0x380, FALSE
	setmetatile 15, 8, 0x381, FALSE
	setmetatile 16, 8, 0x382, FALSE
	return

GoldenrodCity_UndergroundSwitches_EventScript_RemoveWall3::
	setmetatile 23, 7, 0x378, FALSE
	setmetatile 24, 7, 0x379, FALSE
	setmetatile 25, 7, 0x37A, FALSE

	setmetatile 23, 8, 0x380, FALSE
	setmetatile 24, 8, 0x381, FALSE
	setmetatile 25, 8, 0x382, FALSE
	return

GoldenrodCity_UndergroundSwitches_EventScript_RemoveWall4::
	setmetatile 5, 11, 0x378, FALSE
	setmetatile 6, 11, 0x379, FALSE
	setmetatile 7, 11, 0x37A, FALSE

	setmetatile 5, 12, 0x380, FALSE
	setmetatile 6, 12, 0x381, FALSE
	setmetatile 7, 12, 0x382, FALSE
	return

GoldenrodCity_UndergroundSwitches_EventScript_RemoveWall5::
	setmetatile 14, 11, 0x378, FALSE
	setmetatile 15, 11, 0x379, FALSE
	setmetatile 16, 11, 0x37A, FALSE

	setmetatile 14, 12, 0x380, FALSE
	setmetatile 15, 12, 0x381, FALSE
	setmetatile 16, 12, 0x382, FALSE
	return

GoldenrodCity_UndergroundSwitches_EventScript_RemoveWall6::
	setmetatile 23, 11, 0x378, FALSE
	setmetatile 24, 11, 0x379, FALSE
	setmetatile 25, 11, 0x37A, FALSE

	setmetatile 23, 12, 0x380, FALSE
	setmetatile 24, 12, 0x381, FALSE
	setmetatile 25, 12, 0x382, FALSE
	return

GoldenrodCity_UndergroundSwitches_EventScript_SilverTriggerTop::
	lock
	playse SE_EXIT
	waitse
	playse SE_PIN
	playbgm ((558 + 1) + 0x3B), FALSE

	addobject LOCALID_GOLDENROD_UNDERGROUND_SILVER
	applymovement OBJ_EVENT_ID_PLAYER, J_Common_Movement_ExclamationMark
	applymovement LOCALID_GOLDENROD_UNDERGROUND_SILVER, GoldenrodCity_UndergroundSwitches_Movement_SilverEnterTop
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, J_Common_Movement_WalkRight1
	waitmovement 0
	waitmovement 0
	msgbox GoldenrodUnderground_Text_SilverBefore, MSGBOX_DEFAULT
	closemessage
	call_if_eq JOHTO_VAR_STARTER_MON, 0, GoldenrodCity_UndergroundSwitches_EventScript_Cyndaquil
	call_if_eq JOHTO_VAR_STARTER_MON, 1, GoldenrodCity_UndergroundSwitches_EventScript_Totodile
	call_if_eq JOHTO_VAR_STARTER_MON, 2, GoldenrodCity_UndergroundSwitches_EventScript_Chikorita
	playbgm ((558 + 1) + 0x3C), FALSE
	msgbox GoldenrodUnderground_Text_SilverAfter, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_GOLDENROD_UNDERGROUND_SILVER, GoldenrodCity_UndergroundSwitches_Movement_SilverLeaveTop
	waitmovement 0
	playse SE_EXIT
	setflag JOHTO_FLAG_HIDE_GOLDENROD_UNDERGROUND_SILVER
	removeobject LOCALID_GOLDENROD_UNDERGROUND_SILVER
	fadedefaultbgm
	setvar JOHTO_VAR_GOLDENROD_CITY_STATE, 9
	release
	end

GoldenrodCity_UndergroundSwitches_EventScript_SilverTriggerBot::
	lock
	playse SE_EXIT
	waitse
	playse SE_PIN
	playbgm ((558 + 1) + 0x3B), FALSE
	clearflag JOHTO_FLAG_HIDE_GOLDENROD_UNDERGROUND_SILVER
	addobject LOCALID_GOLDENROD_UNDERGROUND_SILVER
	applymovement OBJ_EVENT_ID_PLAYER, J_Common_Movement_ExclamationMark
	applymovement LOCALID_GOLDENROD_UNDERGROUND_SILVER, GoldenrodCity_UndergroundSwitches_Movement_SilverEnterBot
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, J_Common_Movement_WalkRight1
	waitmovement 0
	waitmovement 0
	msgbox GoldenrodUnderground_Text_SilverBefore, MSGBOX_DEFAULT
	closemessage
	call_if_eq JOHTO_VAR_STARTER_MON, 0, GoldenrodCity_UndergroundSwitches_EventScript_Cyndaquil
	call_if_eq JOHTO_VAR_STARTER_MON, 1, GoldenrodCity_UndergroundSwitches_EventScript_Totodile
	call_if_eq JOHTO_VAR_STARTER_MON, 2, GoldenrodCity_UndergroundSwitches_EventScript_Chikorita
	playbgm ((558 + 1) + 0x3C), FALSE
	msgbox GoldenrodUnderground_Text_SilverAfter, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_GOLDENROD_UNDERGROUND_SILVER, GoldenrodCity_UndergroundSwitches_Movement_SilverLeaveBot
	waitmovement 0
	playse SE_EXIT
	setflag JOHTO_FLAG_HIDE_GOLDENROD_UNDERGROUND_SILVER
	removeobject LOCALID_GOLDENROD_UNDERGROUND_SILVER
	fadedefaultbgm
	setvar JOHTO_VAR_GOLDENROD_CITY_STATE, 9
	release
	end

GoldenrodCity_UndergroundSwitches_EventScript_Cyndaquil::
	trainerbattle_no_intro TRAINER_JOHTO_RIVAL_CYNDAQUIL_4_HNS, GoldenrodUnderground_Text_SilverWin
	return

GoldenrodCity_UndergroundSwitches_EventScript_Totodile::
	trainerbattle_no_intro TRAINER_JOHTO_RIVAL_TOTODILE_4_HNS, GoldenrodUnderground_Text_SilverWin
	return

GoldenrodCity_UndergroundSwitches_EventScript_Chikorita::
	trainerbattle_no_intro TRAINER_JOHTO_RIVAL_CHIKORITA_4_HNS, GoldenrodUnderground_Text_SilverWin
	return

GoldenrodCity_UndergroundSwitches_Movement_SilverEnterTop:
	walk_left
	walk_left
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

GoldenrodCity_UndergroundSwitches_Movement_SilverLeaveTop:
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_up
	walk_up
	walk_up
	face_right
	step_end

GoldenrodCity_UndergroundSwitches_Movement_SilverEnterBot:
	walk_left
	walk_left
	walk_down
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

GoldenrodCity_UndergroundSwitches_Movement_SilverLeaveBot:
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_up
	walk_up
	walk_up
	walk_up
	face_right
	step_end

GoldenrodCity_UndergroundSwitches_EventScript_Grunt10::
	trainerbattle_single TRAINER_JOHTO_GRUNT_10_HNS, GoldenrodUnderground_Text_GruntM11Seen, GoldenrodUnderground_Text_GruntM11Beaten
	msgbox GoldenrodUnderground_Text_GruntM11After, MSGBOX_AUTOCLOSE
	end

GoldenrodCity_UndergroundSwitches_EventScript_Grunt20::
	trainerbattle_single TRAINER_JOHTO_GRUNT_20_HNS, GoldenrodUnderground_Text_GruntM25Seen, GoldenrodUnderground_Text_GruntM25Beaten
	msgbox GoldenrodUnderground_Text_GruntM25After, MSGBOX_AUTOCLOSE
	end

GoldenrodCity_UndergroundSwitches_EventScript_Duncan::
	trainerbattle_single TRAINER_JOHTO_DUNCAN_HNS, GoldenrodUnderground_Text_BurglarDuncanSeen, GoldenrodUnderground_Text_BurglarDuncanBeaten
	msgbox GoldenrodUnderground_Text_BurglarDuncanAfter, MSGBOX_AUTOCLOSE
	end

GoldenrodCity_UndergroundSwitches_EventScript_Eddie::
	trainerbattle_single TRAINER_JOHTO_EDDIE_HNS, GoldenrodUnderground_Text_BurglarEddieSeen, GoldenrodUnderground_Text_BurglarEddieBeaten
	msgbox GoldenrodUnderground_Text_BurglarEddieAfter, MSGBOX_AUTOCLOSE
	end

GoldenrodCity_UndergroundSwitches_EventScript_Grunt11::
	trainerbattle_single TRAINER_JOHTO_GRUNT_11_HNS, GoldenrodUnderground_Text_GruntM13Seen, GoldenrodUnderground_Text_GruntM13Beaten
	msgbox GoldenrodUnderground_Text_GruntM13After, MSGBOX_AUTOCLOSE
	end

GoldenrodCity_UndergroundSwitches_EventScript_Grunt27::
	trainerbattle_single TRAINER_JOHTO_GRUNT_27_HNS, GoldenrodUnderground_Text_GruntF3Seen, GoldenrodUnderground_Text_GruntF3Beaten
	msgbox GoldenrodUnderground_Text_GruntF3After, MSGBOX_AUTOCLOSE
	end

GoldenrodCity_UndergroundSwitches_EventScript_Item_Revive::
	finditem ITEM_MAX_REVIVE
	end

GoldenrodCity_UndergroundSwitches_EventScript_Item_MaxPotion::
	finditem ITEM_MAX_POTION
	end

GoldenrodCity_UndergroundSwitches_EventScript_Item_SmokeBall::
	finditem ITEM_SMOKE_BALL
	end

GoldenrodUnderground_Text_SilverBefore:
	.string "Hol{SE_M_WATERFALL}it!\p"
	.string "{SE_M_HEAL_BELL}sa{SE_M_TWISTER}you{SE_M_SUPERSONIC}s{SE_M_ATTRACT2}{SE_M_HEAL_BELL}taile{SE_M_WATERFALL}you.\p"
	.string "{SE_M_HEAL_BELL}don'{SE_M_SPIT_UP}nee{SE_M_WATERFALL}yo{SE_M_DIVE}underfoo{SE_M_SPIT_UP}whil{SE_M_REVERSAL}I\n"
	.string "tak{SE_M_REVERSAL}car{SE_M_REVERSAL}o{SE_M_ACID_ARMOR}TEA{SE_M_GIGA_DRAIN}ROCKET.\p"
	.string "…Wai{SE_M_SPIT_UP}{SE_M_CHARGE}second{SE_M_PERISH_SONG}Yo{SE_M_DIVE}bea{SE_M_SPIT_UP}m{SE_M_REVERSAL}before,\n"
	.string "didn'{SE_M_SPIT_UP}you?\p"
	.string "Tha{SE_M_SPIT_UP}wa{SE_M_GRASSWHISTLE}jus{SE_M_SPIT_UP}{SE_M_CHARGE}fluke.\p"
	.string "I'v{SE_M_REVERSAL}bee{SE_M_ATTRACT}trainin{SE_M_SANDSTORM}m{SE_M_YAWN}tea{SE_M_MILK_DRINK}an{SE_M_WATERFALL}now\n"
	.string "{SE_M_HEAL_BELL}wil{SE_M_BATON_PASS}repa{SE_M_YAWN}m{SE_M_YAWN}debts!$"

GoldenrodUnderground_Text_SilverWin:
	.string "…Why{SE_M_DIZZY_PUNCH}Wh{SE_M_YAWN}d{SE_M_ATTRACT2}{SE_M_HEAL_BELL}lose?\p"
	.string "I'v{SE_M_REVERSAL}assemble{SE_M_WATERFALL}th{SE_M_REVERSAL}toughes{SE_M_SPIT_UP}POKéMON.\p"
	.string "{SE_M_HEAL_BELL}didn'{SE_M_SPIT_UP}eas{SE_M_REVERSAL}u{SE_M_MORNING_SUN}o{SE_M_ATTRACT}th{SE_M_REVERSAL}gas.\p"
	.string "S{SE_M_ATTRACT2}wh{SE_M_YAWN}d{SE_M_ATTRACT2}{SE_M_HEAL_BELL}lose?$"

GoldenrodUnderground_Text_SilverAfter:
	.string "…{SE_M_HEAL_BELL}don'{SE_M_SPIT_UP}understand…\p"
	.string "I{SE_M_GRASSWHISTLE}wha{SE_M_SPIT_UP}tha{SE_M_SPIT_UP}LANC{SE_M_SWORDS_DANCE}gu{SE_M_YAWN}sai{SE_M_WATERFALL}true?\p"
	.string "Tha{SE_M_SPIT_UP}{SE_M_HEAL_BELL}don'{SE_M_SPIT_UP}trea{SE_M_SPIT_UP}POKéMO{SE_M_PSYBEAM2}properly?\p"
	.string "Love…\p"
	.string "Trust…\p"
	.string "Ar{SE_M_REVERSAL}the{SE_M_YAWN}reall{SE_M_YAWN}wha{SE_M_SPIT_UP}{SE_M_HEAL_BELL}lack?\p"
	.string "Ar{SE_M_REVERSAL}the{SE_M_YAWN}keepin{SE_M_SANDSTORM}m{SE_M_REVERSAL}fro{SE_M_MILK_DRINK}winning?\p"
	.string "I{SE_M_DIZZY_PUNCH}{SE_M_HEAL_BELL}jus{SE_M_SPIT_UP}don'{SE_M_SPIT_UP}understand.\p"
	.string "Bu{SE_M_SPIT_UP}it'{SE_M_GRASSWHISTLE}no{SE_M_SPIT_UP}goin{SE_M_SANDSTORM}t{SE_M_ATTRACT2}en{SE_M_WATERFALL}here.\p"
	.string "No{SE_M_SPIT_UP}now{SE_M_PERISH_SONG}No{SE_M_SPIT_UP}becaus{SE_M_REVERSAL}o{SE_M_ACID_ARMOR}this.\p"
	.string "{SE_M_HEAL_BELL}won'{SE_M_SPIT_UP}giv{SE_M_REVERSAL}u{SE_M_MORNING_SUN}m{SE_M_YAWN}drea{SE_M_MILK_DRINK}o{SE_M_ACID_ARMOR}becoming\n"
	.string "th{SE_M_REVERSAL}world'{SE_M_GRASSWHISTLE}bes{SE_M_SPIT_UP}POKéMO{SE_M_PSYBEAM2}trainer!$"

GoldenrodUnderground_Text_SilverLoss:
	.string "Humph{SE_M_PERISH_SONG}Thi{SE_M_GRASSWHISTLE}i{SE_M_GRASSWHISTLE}m{SE_M_YAWN}rea{SE_M_BATON_PASS}power{SE_M_SUPERSONIC}wimp.\p"
	.string "I'l{SE_M_BATON_PASS}mak{SE_M_REVERSAL}TEA{SE_M_GIGA_DRAIN}ROCKE{SE_M_SWIFT}history.\p"
	.string "An{SE_M_WATERFALL}I'{SE_M_MILK_DRINK}goin{SE_M_SANDSTORM}t{SE_M_ATTRACT2}grin{SE_M_WATERFALL}tha{SE_M_SPIT_UP}LANCE\n"
	.string "unde{SE_M_SAND_TOMB}m{SE_M_YAWN}heels.$"

GoldenrodUnderground_Text_GruntM11Seen:
	.string "Ope{SE_M_ATTRACT}on{SE_M_REVERSAL}shutter{SE_M_SUPERSONIC}anothe{SE_M_SAND_TOMB}closes.\p"
	.string "Be{SE_M_SPIT_UP}yo{SE_M_DIVE}can'{SE_M_SPIT_UP}ge{SE_M_SPIT_UP}wher{SE_M_REVERSAL}yo{SE_M_DIVE}want!$"

GoldenrodUnderground_Text_GruntM11Beaten:
	.string "Drat{SE_M_DRAGON_RAGE}{SE_M_HEAL_BELL}wa{SE_M_GRASSWHISTLE}sun{SE_M_ENCORE2}b{SE_M_YAWN}indecision!$"

GoldenrodUnderground_Text_GruntM11After:
	.string "I'{SE_M_MILK_DRINK}confuse{SE_M_WATERFALL}too{SE_M_DIZZY_PUNCH}Th{SE_M_REVERSAL}switc{SE_M_TRI_ATTACK}o{SE_M_ATTRACT}the\n"
	.string "en{SE_M_WATERFALL}i{SE_M_GRASSWHISTLE}th{SE_M_REVERSAL}on{SE_M_REVERSAL}t{SE_M_ATTRACT2}pres{SE_M_GRASSWHISTLE}first{SE_M_SUPERSONIC}but…$"

GoldenrodUnderground_Text_GruntM25Seen:
	.string "Kwahaha!\p"
	.string "Confounde{SE_M_WATERFALL}b{SE_M_YAWN}th{SE_M_REVERSAL}shutters{SE_M_SUPERSONIC}ar{SE_M_REVERSAL}we?\p"
	.string "I'l{SE_M_BATON_PASS}le{SE_M_SPIT_UP}yo{SE_M_DIVE}i{SE_M_ATTRACT}o{SE_M_ATTRACT}{SE_M_CHARGE}secre{SE_M_SPIT_UP}i{SE_M_ACID_ARMOR}you\n"
	.string "ca{SE_M_ATTRACT}bea{SE_M_SPIT_UP}me!$"

GoldenrodUnderground_Text_GruntM25Beaten:
	.string "Uwww{SE_M_DIZZY_PUNCH}{SE_M_HEAL_BELL}ble{SE_M_TWISTER}it.$"

GoldenrodUnderground_Text_GruntM25After:
	.string "Al{SE_M_BATON_PASS}right{SE_M_PERISH_SONG}{SE_M_BONEMERANG}hint!\p"
	.string "Chang{SE_M_REVERSAL}th{SE_M_REVERSAL}orde{SE_M_SAND_TOMB}o{SE_M_ACID_ARMOR}switching.\p"
	.string "That'l{SE_M_BATON_PASS}chang{SE_M_REVERSAL}th{SE_M_REVERSAL}way{SE_M_GRASSWHISTLE}th{SE_M_REVERSAL}shutters\n"
	.string "ope{SE_M_ATTRACT}an{SE_M_WATERFALL}close.$"

GoldenrodUnderground_Text_BurglarDuncanSeen:
	.string "For{SE_M_ENCORE2}ove{SE_M_SAND_TOMB}you{SE_M_SAND_TOMB}goodies!$"

GoldenrodUnderground_Text_BurglarDuncanBeaten:
	.string "Mercy!$"

GoldenrodUnderground_Text_BurglarDuncanAfter:
	.string "Stea{SE_M_BATON_PASS}an{SE_M_WATERFALL}sell{SE_M_DRAGON_RAGE}That'{SE_M_GRASSWHISTLE}basi{SE_M_HYPER_BEAM}in\n"
	.string "crime{SE_M_SUPERSONIC}kid!$"

GoldenrodUnderground_Text_BurglarEddieSeen:
	.string "The{SE_M_YAWN}ditche{SE_M_WATERFALL}thi{SE_M_GRASSWHISTLE}projec{SE_M_SPIT_UP}befor{SE_M_REVERSAL}they\n"
	.string "finished.\p"
	.string "I'{SE_M_MILK_DRINK}searchin{SE_M_SANDSTORM}fo{SE_M_SAND_TOMB}leftove{SE_M_SAND_TOMB}loot.$"

GoldenrodUnderground_Text_BurglarEddieBeaten:
	.string "Ove{SE_M_SAND_TOMB}th{SE_M_REVERSAL}top!$"

GoldenrodUnderground_Text_BurglarEddieAfter:
	.string "UNDERGROUN{SE_M_FAINT_ATTACK}WAREHOUSE?\p"
	.string "Wha{SE_M_SPIT_UP}d{SE_M_ATTRACT2}yo{SE_M_DIVE}wan{SE_M_SPIT_UP}t{SE_M_ATTRACT2}g{SE_M_ATTRACT2}ther{SE_M_REVERSAL}for?\p"
	.string "There'{SE_M_GRASSWHISTLE}nothin{SE_M_SANDSTORM}dow{SE_M_ATTRACT}there.$"

GoldenrodUnderground_Text_GruntM13Seen:
	.string "{SE_M_HEAL_BELL}don'{SE_M_SPIT_UP}car{SE_M_REVERSAL}i{SE_M_ACID_ARMOR}you'r{SE_M_REVERSAL}lost.\p"
	.string "Yo{SE_M_DIVE}sho{SE_M_TWISTER}u{SE_M_MORNING_SUN}here{SE_M_SUPERSONIC}you'r{SE_M_REVERSAL}nothin{SE_M_SANDSTORM}but\n"
	.string "{SE_M_CHARGE}victim!$"

GoldenrodUnderground_Text_GruntM13Beaten:
	.string "Urk{SE_M_DRAGON_RAGE}Yeah{SE_M_SUPERSONIC}thin{SE_M_ENCORE2}you'r{SE_M_REVERSAL}cool{SE_M_SUPERSONIC}huh?$"

GoldenrodUnderground_Text_GruntM13After:
	.string "Yo{SE_M_DIVE}mus{SE_M_SPIT_UP}hav{SE_M_REVERSAL}ic{SE_M_REVERSAL}i{SE_M_ATTRACT}you{SE_M_SAND_TOMB}vein{SE_M_GRASSWHISTLE}to\n"
	.string "dis{SE_M_GRASSWHISTLE}TEA{SE_M_GIGA_DRAIN}ROCKET.$"

GoldenrodUnderground_Text_GruntF3Seen:
	.string "Ar{SE_M_REVERSAL}yo{SE_M_DIVE}lost{SE_M_SING}No{SE_M_SUPERSONIC}yo{SE_M_DIVE}can'{SE_M_SPIT_UP}be.\p"
	.string "Yo{SE_M_DIVE}don'{SE_M_SPIT_UP}hav{SE_M_REVERSAL}tha{SE_M_SPIT_UP}scare{SE_M_WATERFALL}look.\p"
	.string "I'l{SE_M_BATON_PASS}giv{SE_M_REVERSAL}yo{SE_M_DIVE}somethin{SE_M_SANDSTORM}t{SE_M_ATTRACT2}be\n"
	.string "scare{SE_M_WATERFALL}about!$"

GoldenrodUnderground_Text_GruntF3Beaten:
	.string "Ho{SE_M_TWISTER}coul{SE_M_WATERFALL}you?$"

GoldenrodUnderground_Text_GruntF3After:
	.string "G{SE_M_ATTRACT2}whereve{SE_M_SAND_TOMB}you'{SE_M_WATERFALL}like{SE_M_DRAGON_RAGE}Ge{SE_M_SPIT_UP}lost!\n"
	.string "Se{SE_M_REVERSAL}i{SE_M_ACID_ARMOR}{SE_M_HEAL_BELL}care!$"

GoldenrodUnderground_Text_Switch1:
	.string "SWITC{SE_M_SWAGGER2}{SE_M_HEADBUTT}activated.$"

GoldenrodUnderground_Text_Switch2:
	.string "SWITC{SE_M_SWAGGER2}{SE_M_SURF}activated.$"

GoldenrodUnderground_Text_Switch3:
	.string "SWITC{SE_M_SWAGGER2}{SE_M_HYDRO_PUMP}activated.$"

GoldenrodUnderground_Text_Switch1Off:
	.string "SWITC{SE_M_SWAGGER2}{SE_M_HEADBUTT}deactivated.$"

GoldenrodUnderground_Text_Switch2Off:
	.string "SWITC{SE_M_SWAGGER2}{SE_M_SURF}deactivated.$"

GoldenrodUnderground_Text_Switch3Off:
	.string "SWITC{SE_M_SWAGGER2}{SE_M_HYDRO_PUMP}deactivated.$"

