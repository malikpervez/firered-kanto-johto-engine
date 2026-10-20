@ Johto (data/scripts/apprentice.inc), as built into the FireRed game.

J_BattleFrontier_BattleTowerLobby_EventScript_Apprentice::
	lock
	faceplayer
	apprentice_gavelvlmode
	goto_if_eq 32781, FALSE, J_Apprentice_EventScript_FirstMeeting
	apprentice_shouldcheckgone
	goto_if_eq 32772, FALSE, J_Apprentice_EventScript_AskQuestion
	goto_if_set 10518, J_Apprentice_EventScript_Gone

J_Apprentice_EventScript_AskQuestion:
	apprentice_getquestion
	goto_if_eq 32781, 2, J_Apprentice_EventScript_UseWhichMon
	goto_if_eq 32781, 4, J_Apprentice_EventScript_UseWhatHeldItem
	goto_if_eq 32781, 3, J_Apprentice_EventScript_UseWhichMove
	goto_if_eq 32781, 1, J_Apprentice_EventScript_PutWhichMonFirst
	goto_if_eq 32781, 5, J_Apprentice_EventScript_PickWinSpeech
	release
	releaseall
	end

J_Apprentice_EventScript_FirstMeeting:
	apprentice_buff STR_VAR_1, 6
	apprentice_msg FALSE, 0

J_Apprentice_EventScript_WhichLvlMode:
	apprentice_menu 6
	goto_if_eq 32781, 1, J_Apprentice_EventScript_RejectTeach
	apprentice_msg FALSE, 2
	apprentice_menu 0
	apprentice_setlvlmode 32781
	apprentice_shufflespecies
	apprentice_buff STR_VAR_1, 8
	apprentice_msg TRUE, 3
	call J_Apprentice_EventScript_SetHideFlags
	release
	releaseall
	switch 32780
	case DIR_NORTH, J_Apprentice_EventScript_LeaveNorth
	goto J_Apprentice_EventScript_Leave
	end

J_Apprentice_EventScript_RejectTeach:
	apprentice_msg FALSE, 1
	goto J_Apprentice_EventScript_WhichLvlMode

J_Apprentice_EventScript_UseWhichMon:
	apprentice_initquestion 2
	apprentice_buff STR_VAR_1, 0
	apprentice_buff STR_VAR_2, 1
	apprentice_msg FALSE, 6
	apprentice_menu 2
	copyvar 32773, 32781
	call_if_eq 32773, 0, J_Apprentice_EventScript_ChoseFirstMon
	call_if_eq 32773, 1, J_Apprentice_EventScript_ChoseSecondMon
	apprentice_getnumpartymons
	apprentice_setpartymon 32781
	apprentice_answeredquestion
	apprentice_getnumpartymons
	call_if_eq 32781, (6 / 2), J_Apprentice_EventScript_LastMonSelected
	apprentice_buff STR_VAR_1, 32775
	apprentice_freequestion
	apprentice_msg TRUE, 7
	call J_Apprentice_EventScript_SetHideFlags
	release
	releaseall
	switch 32780
	case DIR_NORTH, J_Apprentice_EventScript_LeaveNorth
	goto J_Apprentice_EventScript_Leave
	end

J_Apprentice_EventScript_ChoseFirstMon:
	setvar 32775, 0
	return

J_Apprentice_EventScript_ChoseSecondMon:
	setvar 32775, 1
	return

J_Apprentice_EventScript_LastMonSelected:
	apprentice_randomizequestions
	return

J_Apprentice_EventScript_UseWhatHeldItem:
	apprentice_initquestion 4
	apprentice_buff STR_VAR_1, 2
	apprentice_msg TRUE, 10
	apprentice_freequestion

J_Apprentice_EventScript_ChooseHoldItem:
	fadescreen 1
	setvar 32781, 0
	apprentice_openbag
	goto_if_eq 32781, FALSE, J_Apprentice_EventScript_ConfirmHoldNothing
	apprentice_trysetitem
	goto_if_eq 32781, FALSE, J_Apprentice_EventScript_AlreadySuggestedItem
	apprentice_buff STR_VAR_1, 5
	apprentice_msg TRUE, 12
	apprentice_answeredquestion
	call J_Apprentice_EventScript_SetHideFlags
	release
	releaseall
	switch 32780
	case DIR_NORTH, J_Apprentice_EventScript_LeaveNorth
	goto J_Apprentice_EventScript_Leave
	end

J_Apprentice_EventScript_ConfirmHoldNothing:
	apprentice_initquestion 4
	apprentice_buff STR_VAR_1, 2
	apprentice_msg FALSE, 13
	apprentice_menu 4
	apprentice_freequestion
	goto_if_eq 32781, 0, J_Apprentice_EventScript_ChooseHoldItem

J_Apprentice_EventScript_HoldNothing:
	apprentice_msg TRUE, 14
	apprentice_answeredquestion
	call J_Apprentice_EventScript_SetHideFlags
	release
	releaseall
	switch 32780
	case DIR_NORTH, J_Apprentice_EventScript_LeaveNorth
	goto J_Apprentice_EventScript_Leave
	end

J_Apprentice_EventScript_AlreadySuggestedItem:
	apprentice_initquestion 4
	apprentice_buff STR_VAR_1, 5
	apprentice_buff STR_VAR_2, 2
	apprentice_msg FALSE, 16
	apprentice_menu 4
	apprentice_freequestion
	goto_if_eq 32781, 0, J_Apprentice_EventScript_ChooseHoldItem
	goto J_Apprentice_EventScript_HoldNothing
	end

J_Apprentice_EventScript_UseWhichMove:
	apprentice_initquestion 3
	apprentice_buff STR_VAR_1, 2
	apprentice_buff STR_VAR_2, 3
	apprentice_buff STR_VAR_3, 4
	apprentice_msg FALSE, 8
	apprentice_menu 3
	copyvar 32773, 32781
	call_if_eq 32773, 0, J_Apprentice_EventScript_ChoseMove1
	call_if_eq 32773, 1, J_Apprentice_EventScript_ChoseMove2
	apprentice_setmove
	apprentice_answeredquestion
	apprentice_buff STR_VAR_1, 32775
	apprentice_freequestion
	apprentice_msg TRUE, 9
	call J_Apprentice_EventScript_SetHideFlags
	release
	releaseall
	switch 32780
	case DIR_NORTH, J_Apprentice_EventScript_LeaveNorth
	goto J_Apprentice_EventScript_Leave
	end

J_Apprentice_EventScript_ChoseMove1:
	setvar 32775, 3
	return

J_Apprentice_EventScript_ChoseMove2:
	setvar 32775, 4
	return

J_Apprentice_EventScript_PutWhichMonFirst:
	apprentice_msg FALSE, 4
	apprentice_menu 1
	apprentice_setleadmon 32781
	apprentice_answeredquestion
	apprentice_buff STR_VAR_1, 9
	apprentice_msg TRUE, 5
	call J_Apprentice_EventScript_SetHideFlags
	release
	releaseall
	switch 32780
	case DIR_NORTH, J_Apprentice_EventScript_LeaveNorth
	goto J_Apprentice_EventScript_Leave
	end

J_Apprentice_EventScript_PickWinSpeech:
	apprentice_msg TRUE, 11
	apprentice_shiftsaved
	setvar 32772, 19
	call J_Common_ShowEasyChatScreen
	lock
	faceplayer
	apprentice_save
	apprentice_buff STR_VAR_1, 7
	apprentice_msg TRUE, 15
	apprentice_reset
	call J_Apprentice_EventScript_SetHideFlags
	release
	releaseall
	switch 32780
	case DIR_NORTH, J_Apprentice_EventScript_LeaveNorth
	goto J_Apprentice_EventScript_Leave
	end

J_Apprentice_EventScript_SetHideFlags:
	setflag 8412
	setflag 10518
	return

J_Apprentice_EventScript_LeaveNorth:
	apprentice_shouldleave
	goto_if_eq 32772, FALSE, J_Apprentice_EventScript_DontMove
	applymovement 6, J_Apprentice_Movement_LeaveNorth
	waitmovement 0
	end

J_Apprentice_EventScript_Leave:
	apprentice_shouldleave
	goto_if_eq 32772, FALSE, J_Apprentice_EventScript_DontMove
	applymovement 6, J_Apprentice_Movement_Leave
	waitmovement 0
	end

J_Apprentice_EventScript_Gone:
	release
	releaseall
	end

J_Apprentice_EventScript_DontMove:
	end

J_Apprentice_Movement_LeaveNorth:
	walk_fast_right

J_Apprentice_Movement_Leave:
	walk_fast_down
	walk_fast_down
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	set_invisible
	slide_down
	slide_down
	slide_down
	step_end

