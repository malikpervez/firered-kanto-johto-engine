@ Johto (data/maps/NewBarkTown_hns/scripts.inc), as built into the FireRed game.

NewBarkTown_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, NewBarkTown_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, NewBarkTown_OnFrame
	map_script MAP_SCRIPT_ON_RESUME, J_SetTimeEncounters
	.byte 0

NewBarkTown_OnFrame::
	map_script_2 JOHTO_VAR_NEWBARK_TOWN_STATE, 6, NewBarkTown_EventScript_ElmCallAfterLeague
	.2byte 0

NewBarkTown_EventScript_ElmCallAfterLeague::
	lock
	setspeaker NewBarkTown_Text_ElmName
	pokenavcall BlackthornCity_Text_ElmCall
	waitmessage
	delay 30
	setvar JOHTO_VAR_NEWBARK_TOWN_STATE, 7
	setvar JOHTO_VAR_NEWBARKTOWN_LABSTATE, 10
	release
	end

NewBarkTown_Text_ElmName:
	.string "PROF.ELM$"

NewBarkTown_OnTransition::
	goto_if_eq JOHTO_VAR_NEWBARK_TOWN_STATE, 2, NewBarkTown_Set_TalkToElm
	goto_if_eq JOHTO_VAR_NEWBARK_TOWN_STATE, 4, NewBarkTown_Set_TalkToMom
	end

NewBarkTown_Set_TalkToElm::
	clearflag JOHTO_FLAG_HIDE_SILVER_NEWBARKTOWN
	setobjectxyperm LOCALID_LASS, 0, 11
	callnative SetTimeBasedEncounters
	end

NewBarkTown_Set_TalkToMom::
	setobjectxyperm LOCALID_LASS, 0, 11
	callnative SetTimeBasedEncounters
	end

NewBarkTown_EventScript_LabSign::
	msgbox NewBarkTown_Text_LabSign, MSGBOX_SIGN
	end

NewBarkTown_EventScript_TownSign::
	msgbox NewBarkTown_Text_Sign, MSGBOX_SIGN
	closemessage
	end

NewBarkTown_EventScript_Lass::
	lock
	faceplayer
	goto_if_eq JOHTO_VAR_NEWBARK_TOWN_STATE, 2, NewBarkTown_EventScript_LassState2
	goto_if_eq JOHTO_VAR_NEWBARK_TOWN_STATE, 3, NewBarkTown_EventScript_LassState3
	goto_if_eq JOHTO_VAR_NEWBARK_TOWN_STATE, 4, NewBarkTown_EventScript_LassState4
	msgbox NewBarkTown_Text_LassState5, MSGBOX_DEFAULT
	closemessage
	release
	end

NewBarkTown_EventScript_LassState2::
	playse SE_PIN
	applymovement LOCALID_LASS, J_Common_Movement_ExclamationMark
	delay 55
	waitmovement LOCALID_LASS
	faceplayer
	waitmovement 0
	msgbox NewBarkTown_Text_LassState2, MSGBOX_DEFAULT
	closemessage
	release
	end

NewBarkTown_EventScript_LassState3::
	msgbox NewBarkTown_Text_LassState3, MSGBOX_DEFAULT
	closemessage
	release
	end

NewBarkTown_EventScript_LassState4::
	playse SE_PIN
	applymovement LOCALID_LASS, J_Common_Movement_ExclamationMark
	delay 55
	waitmovement LOCALID_LASS
	faceplayer
	waitmovement 0
	msgbox NewBarkTown_Text_LassState4, MSGBOX_DEFAULT
	closemessage
	release
	end

NewBarkTown_EventScript_Wooper::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_WOOPER, CRY_MODE_NORMAL
	msgbox NewBarkTown_Text_Wooper, MSGBOX_DEFAULT
	waitmoncry
	release
	end

NewBarkTown_EventScript_LeaveTrigger::
	lock
	call_if_eq JOHTO_VAR_NEWBARK_TOWN_STATE, 2, NewBarkTown_EventScript_LeaveTriggersState2
	call_if_eq JOHTO_VAR_NEWBARK_TOWN_STATE, 4, NewBarkTown_EventScript_LeaveTriggersState4
	applymovement OBJ_EVENT_ID_PLAYER, J_OldaleTown_Movement_PlayerStepBack
	waitmovement 0
	release
	end

NewBarkTown_EventScript_LeaveTriggersState2::
	playse SE_PIN
	applymovement LOCALID_LASS, J_Common_Movement_ExclamationMark
	delay 55
	waitmovement LOCALID_LASS
	applymovement LOCALID_LASS, NewBarkTown_Movement_FaceDown
	waitmovement 0
	msgbox NewBarkTown_Text_LassState2, MSGBOX_DEFAULT
	closemessage
	return

NewBarkTown_EventScript_LeaveTriggersState4::
	playse SE_PIN
	applymovement LOCALID_LASS, J_Common_Movement_ExclamationMark
	delay 55
	waitmovement LOCALID_LASS
	applymovement LOCALID_LASS, NewBarkTown_Movement_FaceDown
	waitmovement 0
	msgbox NewBarkTown_Text_LassState4, MSGBOX_DEFAULT
	closemessage
	return

NewBarkTown_EventScript_FatMan::
	lock
	faceplayer
	goto_if_eq JOHTO_VAR_NEWBARK_TOWN_STATE, 2, NewBarkTown_EventScript_FatManState2
	msgbox NewBarkTown_Text_FatManState3, MSGBOX_DEFAULT
	closemessage
	release
	end

NewBarkTown_EventScript_FatManState2::
	msgbox NewBarkTown_Text_FatManState2, MSGBOX_DEFAULT
	closemessage
	release
	end

NewBarkTown_EventScript_Silver::
	lock
	msgbox NewBarkTown_Text_Silver1, MSGBOX_DEFAULT
	delay 60
	playse SE_PIN
	applymovement LOCALID_SILVER, J_Common_Movement_ExclamationMark
	faceplayer
	waitmovement 0
	msgbox NewBarkTown_Text_Silver2, MSGBOX_DEFAULT
	playse SE_BANG
	applymovement LOCALID_SILVER, NewBarkTown_Movement_SilverPushesPlayer
	applymovement OBJ_EVENT_ID_PLAYER, NewBarkTown_Movement_PlayerPushedBySilver
	waitmovement 0
	applymovement LOCALID_SILVER, J_Common_Movement_FaceOriginalDirection
	waitmovement 0
	waitmovement 0
	release
	end

NewBarkTown_EventScript_Door::
	msgbox NewBarkTown_Text_Door, MSGBOX_SIGN
	end

NewBarkTown_EventScript_TestMan1::
	givebp 4
	msgbox J_BattleFrontier_Text_ObtainedXBattlePoints, MSGBOX_GETPOINTS
	end

NewBarkTown_EventScript_TestMan2::
	setvar JOHTO_VAR_NEWBARK_TOWN_STATE, 4
	setflag JOHTO_FLAG_HIDE_MOMS_FRIEND
	setflag JOHTO_FLAG_ADVENTURE_STARTED
	setflag JOHTO_FLAG_HIDE_SILVER_NEWBARKTOWN
	end

NewBarkTown_EventScript_TestMan3::
	setvar JOHTO_VAR_NEWBARK_TOWN_STATE, 5

	clearflag JOHTO_FLAG_COMPLETED_AERODACTYL_PUZZLE
	clearflag JOHTO_FLAG_COMPLETED_HOOH_PUZZLE
	clearflag JOHTO_FLAG_COMPLETED_KABUTO_PUZZLE
	clearflag JOHTO_FLAG_COMPLETED_OMANYTE_PUZZLE
	end

NewBarkTown_Movement_SilverPushesPlayer:
	walk_fast_left
	walk_fast_left
	walk_fast_down
	face_down
	lock_facing_direction
	unlock_facing_direction
	walk_fast_up
	walk_fast_right
	walk_fast_right
	step_end

NewBarkTown_Movement_PlayerPushedBySilver:
	walk_fast_left
	face_up
	walk_fast_down
	face_up
	lock_facing_direction
	jump_2_down
	unlock_facing_direction
	face_down
	step_end

NewBarkTown_Movement_FaceDown:
	face_down
	step_end

NewBarkTown_Text_LabSign:
	.string "PROF.ELM'S LAB$"

NewBarkTown_Text_Door:
	.string "The door is locked.$"

NewBarkTown_Text_Wooper:
	.string "WOOPER: Woooooop.$"

NewBarkTown_Text_FatManState2::
	.string "Welcome to JOHTO! PROF.ELM's\n"
	.string "neighbor can help you get a\l"
	.string "POKéGEAR for your travels.$"

NewBarkTown_Text_FatManState3:
	.string "Yo, {PLAYER}!\p"
	.string "I hear PROF.ELM discovered\n"
	.string "some new POKéMON.$"

NewBarkTown_Text_LassState2::
	.string "You're PROF.OAK's visitor, right?\p"
	.string "PROF.ELM is waiting in his lab.\n"
	.string "Please see him before setting out.$"

NewBarkTown_Text_LassState3:
	.string "Oh! Your POKéMON is adorable!\n"
	.string "I wish I had one!$"

NewBarkTown_Text_LassState4::
	.string "Leaving already, {PLAYER}?\p"
	.string "The woman in the guest house\n"
	.string "would like a word before you go.$"

NewBarkTown_Text_LassState5::
	.string "You can call the guest house on\n"
	.string "your POKéGEAR while traveling.$"

NewBarkTown_Text_Silver1:
	.string ". . .\p"
	.string "So this is the famous ELM\n"
	.string "POKéMON LAB…$"

NewBarkTown_Text_Silver2:
	.string "…What are you staring at?$"

NewBarkTown_Text_Sign:
	.string "NEW BARK TOWN\p"
	.string "The Town Where the Winds of\n"
	.string "a New Beginning Blow$"

NewBarkTown_EventScript_PlayersHouseMailbox::
	msgbox NewBarkTown_Text_PlayersHouse, MSGBOX_SIGN
	end

NewBarkTown_EventScript_ElmsHouseMailbox::
	msgbox NewBarkTown_Text_ElmsHouse, MSGBOX_SIGN
	end

NewBarkTown_Text_PlayersHouse::
	.string "PROF.ELM'S GUEST HOUSE$"

NewBarkTown_Text_ElmsHouse:
	.string "PROF.ELM'S HOUSE$"

B2_NewBark_EventScript_ReturnToKanto::
	lock
	faceplayer
	msgbox B2_NewBark_Text_ReturnToKanto, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, B2_NewBark_EventScript_DeclineTravel
	closemessage
	warp MAP_PALLET_TOWN, 12, 11
	waitstate
	releaseall
	end

B2_NewBark_EventScript_DeclineTravel::
	closemessage
	release
	end

B2_NewBark_Text_ReturnToKanto::
	.string "Return to PALLET TOWN?$"

