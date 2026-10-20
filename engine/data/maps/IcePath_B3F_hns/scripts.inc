@ Johto (data/maps/IcePath_B3F_hns/scripts.inc), as built into the FireRed game.

IcePath_B3F_hns_MapScripts::
	map_script 3, IcePath_B3F_OnTransition
	map_script 5, J_SetTimeEncounters
	.byte 0

IcePath_B3F_OnTransition:
	callnative SetTimeBasedEncounters
	end

IcePath_B3F_Trigger_Swinub_Jump::
	goto_if_set 8796, IcePath_B3F_Trigger_Night
	playse 21
	applymovement 255, J_Common_Movement_ExclamationMark
	waitmovement 255
	waitse
	turnobject 255, DIR_WEST
	playmoncry 220, 0
	applymovement 4, IcePath_B3F_Movement_StuckSwinubJump0
	waitmovement 4
	delay 20
	playse 10
	applymovement 4, IcePath_B3F_Movement_StuckSwinubJump
	waitmovement 0
	setobjectxyperm 4, 3, 19
	setobjectmovementtype 4, 0x8
	setvar 16384, 1
	end

IcePath_B3F_Trigger_Night::
	setvar 16384, 1
	end

IcePath_B3F_EventScript_Swinub::
	lockall
	faceplayer
	playmoncry 220, 0
	msgbox IcePath_B3F_Text_Swinub, MSGBOX_DEFAULT
	waitmoncry
	goto_if_set 8500, IcePath_B3F_EventScript_SwinubBlowPlayer
	msgbox IcePath_B3F_Text_SwinubBerry, MSGBOX_YESNO
	goto_if_eq 32781, FALSE, IcePath_B3F_EventScript_SwinubBlowPlayer
	fadescreen 1
	special Bag_ChooseBerry
	waitstate
	removeitem 32782, 1
	goto_if_ne 32782, ITEM_ASPEAR_BERRY, IcePath_B3F_EventScript_SwinubDislikedBerry
	msgbox IcePath_B3F_Text_SwinubAteBerry, MSGBOX_DEFAULT
	giveitem 653
	setflag 8500

IcePath_B3F_EventScript_SwinubBlowPlayer::
	closemessage
	playse 153
	setweather 4
	doweather
	call_if_eq 32780, DIR_SOUTH, IcePath_B3F_EventScript_SwinubBlowPlayerUp
	call_if_eq 32780, DIR_EAST, IcePath_B3F_EventScript_SwinubBlowPlayerLeft
	releaseall
	end

IcePath_B3F_EventScript_SwinubDislikedBerry::
	msgbox IcePath_B3F_Text_SwinubTurnedAway, MSGBOX_DEFAULT
	goto IcePath_B3F_EventScript_SwinubBlowPlayer

IcePath_B3F_EventScript_SwinubBlowPlayerUp::
	applymovement 2, IcePath_B3F_Movement_JumpUp
	applymovement 255, IcePath_B3F_Movement_Player_BlownUp
	waitmovement 0
	return

IcePath_B3F_EventScript_SwinubBlowPlayerLeft::
	applymovement 2, IcePath_B3F_Movement_JumpLeft
	applymovement 255, IcePath_B3F_Movement_Player_BlownLeft
	waitmovement 0
	return

IcePath_B3F_EventScript_Delibird::
	lockall
	faceplayer
	playmoncry 225, 0
	msgbox IcePath_B3F_Text_Delibird, MSGBOX_DEFAULT
	waitmoncry
	goto_if_set 8500, IcePath_B3F_EventScript_DelibirdBlowPlayer
	msgbox IcePath_B3F_Text_DelibirdBerry, MSGBOX_YESNO
	goto_if_eq 32781, FALSE, IcePath_B3F_EventScript_DelibirdBlowPlayer
	fadescreen 1
	special Bag_ChooseBerry
	waitstate
	removeitem 32782, 1
	goto_if_ne 32782, ITEM_ASPEAR_BERRY, IcePath_B3F_EventScript_DelibirdDislikedBerry
	msgbox IcePath_B3F_Text_DelibirdAteBerry, MSGBOX_DEFAULT
	giveitem 653
	setflag 8500

IcePath_B3F_EventScript_DelibirdBlowPlayer::
	closemessage
	playse 153
	setweather 4
	doweather
	call_if_eq 32780, DIR_SOUTH, IcePath_B3F_EventScript_DelibirdBlowPlayerUp
	call_if_eq 32780, DIR_EAST, IcePath_B3F_EventScript_DelibirdBlowPlayerLeft
	releaseall
	end

IcePath_B3F_EventScript_DelibirdDislikedBerry::
	msgbox IcePath_B3F_Text_DelibirdTurnedAway, MSGBOX_DEFAULT
	goto IcePath_B3F_EventScript_DelibirdBlowPlayer

IcePath_B3F_EventScript_DelibirdBlowPlayerUp::
	applymovement 1, IcePath_B3F_Movement_JumpUp
	applymovement 255, IcePath_B3F_Movement_Player_BlownUp
	waitmovement 0
	return

IcePath_B3F_EventScript_DelibirdBlowPlayerLeft::
	applymovement 1, IcePath_B3F_Movement_JumpLeft
	applymovement 255, IcePath_B3F_Movement_Player_BlownLeft
	waitmovement 0
	return

IcePath_B3F_Movement_Player_BlownUp:
	lock_facing_direction
	walk_up
	walk_up
	unlock_facing_direction
	step_end

IcePath_B3F_Movement_Player_BlownLeft:
	lock_facing_direction
	walk_left
	walk_left
	unlock_facing_direction
	step_end

IcePath_B3F_Movement_JumpUp:
	jump_in_place_up
	step_end

IcePath_B3F_Movement_JumpLeft:
	jump_in_place_left
	step_end

IcePath_B3F_Movement_StuckSwinubJump0:
	jump_in_place_up
	step_end

IcePath_B3F_Movement_StuckSwinubJump:
	jump_2_up
	jump_in_place_left_right
	jump_in_place_left_right
	face_left
	step_end

IcePath_B3F_Text_Swinub:
	.string "SWINUB{SE_M_HEAT_WAVE}Swiiiiii!$"

IcePath_B3F_Text_SwinubBerry:
	.string "Giv{SE_M_REVERSAL}th{SE_M_REVERSAL}SWINU{SE_M_LICK}{SE_M_CHARGE}BERRY?$"

IcePath_B3F_Text_SwinubAteBerry:
	.string "SWINU{SE_M_LICK}enjoye{SE_M_WATERFALL}th{SE_M_REVERSAL}ASPEA{SE_M_MINIMIZE}BERRY!$"

IcePath_B3F_Text_SwinubTurnedAway:
	.string "SWINU{SE_M_LICK}doesn'{SE_M_SPIT_UP}lik{SE_M_REVERSAL}it!$"

IcePath_B3F_Text_Delibird:
	.string "DELIBIRD{SE_M_HEAT_WAVE}SKWAAAAA!$"

IcePath_B3F_Text_DelibirdBerry:
	.string "Giv{SE_M_REVERSAL}th{SE_M_REVERSAL}DELIBIR{SE_M_FAINT_ATTACK}{SE_M_CHARGE}BERRY?$"

IcePath_B3F_Text_DelibirdAteBerry:
	.string "DELIBIR{SE_M_FAINT_ATTACK}enjoye{SE_M_WATERFALL}th{SE_M_REVERSAL}ASPEA{SE_M_MINIMIZE}BERRY!$"

IcePath_B3F_Text_DelibirdTurnedAway:
	.string "DELIBIR{SE_M_FAINT_ATTACK}doesn'{SE_M_SPIT_UP}lik{SE_M_REVERSAL}it!$"

