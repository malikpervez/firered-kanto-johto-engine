@ Johto (data/scripts/battle_pike.inc), as built into the FireRed game.

J_BattleFrontier_BattlePikeRoom_MapScripts:
	map_script 3, J_BattleFrontier_BattlePikeRoom_OnTransition
	map_script 4, J_BattleFrontier_BattlePikeRoom_OnWarp

J_BattleFrontier_BattlePikeRoom_OnTransition:
	pike_setroomobjects
	pike_getroomtype
	switch 32781
	case 0, J_BattleFrontier_BattlePikeRoomNormal_EventScript_SetOneObjectRoomPos
	case 1, J_BattleFrontier_BattlePikeRoomNormal_EventScript_SetOneObjectRoomPos
	case 2, J_BattleFrontier_BattlePikeRoomNormal_EventScript_SetNPCRoomObjPos
	case 3, J_BattleFrontier_BattlePikeRoomNormal_EventScript_SetTwoObjectRoomPos
	case 4, J_BattleFrontier_BattlePikeRoomNormal_EventScript_SetOneObjectRoomPos
	case 7, J_BattleFrontier_BattlePikeRoomNormal_EventScript_SetDoubleBattleObjPos
	case 6, J_BattleFrontier_BattlePikeRoomNormal_EventScript_SetTwoObjectRoomPos
	case 8, J_BattleFrontier_BattlePikeRoomNormal_EventScript_SetBrainRoomObjPos
	end

J_BattleFrontier_BattlePikeRoomNormal_EventScript_SetDoubleBattleObjPos::
	setobjectxyperm 1, 2, 5
	setobjectxyperm 2, 6, 5
	end

J_BattleFrontier_BattlePikeRoomNormal_EventScript_SetTwoObjectRoomPos::
	setobjectxyperm 1, 4, 4
	setobjectxyperm 2, 3, 4
	end

J_BattleFrontier_BattlePikeRoomNormal_EventScript_SetOneObjectRoomPos::
	setobjectxyperm 1, 4, 4
	setobjectxyperm 2, 0, 0
	end

J_BattleFrontier_BattlePikeRoomNormal_EventScript_SetNPCRoomObjPos::
	setobjectxyperm 1, 5, 5
	setobjectxyperm 2, 0, 0
	end

J_BattleFrontier_BattlePikeRoomNormal_EventScript_SetBrainRoomObjPos::
	setobjectxyperm 1, 4, 3
	setobjectxyperm 2, 4, 4
	end

J_BattleFrontier_BattlePikeRoom_OnWarp:
	map_script_2 16388, 0, J_BattleFrontier_BattlePikeRoomNormal_EventScript_InitRoomObjects
	.2byte 0

J_BattleFrontier_BattlePikeRoomNormal_EventScript_InitRoomObjects::
	setvar 16401, 28
	setvar 16400, 28
	pike_getroomtype
	goto_if_eq 32781, 3, J_BattleFrontier_BattlePikeRoomNormal_EventScript_InitTwoObjectRoom
	goto_if_eq 32781, 6, J_BattleFrontier_BattlePikeRoomNormal_EventScript_InitTwoObjectRoom
	goto_if_eq 32781, 7, J_BattleFrontier_BattlePikeRoomNormal_EventScript_InitTwoObjectRoom
	goto_if_eq 32781, 8, J_BattleFrontier_BattlePikeRoomNormal_EventScript_InitBrainRoomObjects
	hideobjectat 2, MAP_BATTLE_FRONTIER_BATTLE_PIKE_ROOM_NORMAL
	setvar 16388, 1
	turnobject 255, DIR_NORTH
	end

J_BattleFrontier_BattlePikeRoomNormal_EventScript_InitTwoObjectRoom::
	setvar 16388, 1
	turnobject 255, DIR_NORTH
	end

J_BattleFrontier_BattlePikeRoomNormal_EventScript_InitBrainRoomObjects::
	setvar 16388, 1
	turnobject 255, DIR_NORTH
	hideobjectat 1, MAP_BATTLE_FRONTIER_BATTLE_PIKE_ROOM_NORMAL
	end

J_BattleFrontier_BattlePikeThreePathRoom_EventScript_LeftRoomWarp::
	setvar 32775, 0
	goto J_BattleFrontier_BattlePikeThreePathRoom_EventScript_RoomWarp
	end

J_BattleFrontier_BattlePikeThreePathRoom_EventScript_CenterRoomWarp::
	setvar 32775, 1
	goto J_BattleFrontier_BattlePikeThreePathRoom_EventScript_RoomWarp
	end

J_BattleFrontier_BattlePikeThreePathRoom_EventScript_RightRoomWarp::
	setvar 32775, 2
	goto J_BattleFrontier_BattlePikeThreePathRoom_EventScript_RoomWarp
	end

J_BattleFrontier_BattlePikeThreePathRoom_EventScript_RoomWarp::
	clearflag 16389
	pike_get 1
	addvar 32781, 1
	pike_set 1, 32781
	frontier_get 2
	addvar 32781, 1
	frontier_set 2, 32781
	pike_setnextroom
	pike_getroomtype
	switch 32781
	case 0, J_BattleFrontier_BattlePikeThreePathRoom_EventScript_WarpNPCRoom
	case 1, J_BattleFrontier_BattlePikeThreePathRoom_EventScript_WarpNPCRoom
	case 2, J_BattleFrontier_BattlePikeThreePathRoom_EventScript_WarpNPCRoom
	case 3, J_BattleFrontier_BattlePikeThreePathRoom_EventScript_WarpNPCRoom
	case 4, J_BattleFrontier_BattlePikeThreePathRoom_EventScript_WarpNPCRoom
	case 5, J_BattleFrontier_BattlePikeThreePathRoom_EventScript_WarpWildMonRoom
	case 6, J_BattleFrontier_BattlePikeThreePathRoom_EventScript_WarpNPCRoom
	case 7, J_BattleFrontier_BattlePikeThreePathRoom_EventScript_WarpNPCRoom
	case 8, J_BattleFrontier_BattlePikeThreePathRoom_EventScript_WarpNPCRoom
	end

J_BattleFrontier_BattlePikeThreePathRoom_EventScript_WarpNPCRoom::
	applymovement 255, J_BattleFrontier_BattlePikeRoom_Movement_HidePlayer
	waitmovement 0
	call BattleFrontier_BattlePike_EventScript_CloseCurtain
	warpsilent MAP_BATTLE_FRONTIER_BATTLE_PIKE_ROOM_NORMAL, 4, 7
	waitstate
	end

J_BattleFrontier_BattlePikeThreePathRoom_EventScript_WarpWildMonRoom::
	applymovement 255, J_BattleFrontier_BattlePikeRoom_Movement_HidePlayer
	waitmovement 0
	call BattleFrontier_BattlePike_EventScript_CloseCurtain
	warpsilent MAP_BATTLE_FRONTIER_BATTLE_PIKE_ROOM_WILD_MONS, 4, 19
	waitstate
	end

J_BattleFrontier_BattlePikeThreePathRoom_EventScript_SetEnteredRoom::
	setvar 16387, 1
	setvar 16386, 1
	end

J_BattleFrontier_BattlePikeThreePathRoom_EventScript_NoTurningBack::
	setvar 16387, 0
	setvar 16386, 0
	lockall
	msgbox J_BattleFrontier_BattlePike_Text_PathBlockedNoTurningBack, MSGBOX_DEFAULT
	closemessage
	releaseall
	end

J_BattleFrontier_BattlePikeRoomNormal_EventScript_SetEnteredRoom::
	setvar 16387, 1
	setvar 16386, 1
	end

J_BattleFrontier_BattlePikeRoomNormal_EventScript_NoTurningBack::
	setvar 16387, 0
	setvar 16386, 0
	lockall
	msgbox J_BattleFrontier_BattlePike_Text_PathBlockedNoTurningBack, MSGBOX_DEFAULT
	closemessage
	releaseall
	end

J_BattleFrontier_BattlePikeRoomNormal_EventScript_Exit::
	pike_ispartyfullhealth
	call_if_eq 32781, TRUE, J_BattleFrontier_BattlePikeRoom_EventScript_DisableHealing
	call_if_ne 32781, TRUE, J_BattleFrontier_BattlePikeRoom_EventScript_EnableHealing
	pike_get 1
	addvar 32781, 1
	pike_set 1, 32781
	frontier_get 2
	addvar 32781, 1
	frontier_set 2, 32781
	pike_isfinalroom
	call_if_eq 32781, TRUE, J_BattleFrontier_BattlePikeRoom_EventScript_WarpToFinalRoom
	call_if_eq 32781, FALSE, J_BattleFrontier_BattlePikeRoom_EventScript_WarpToThreePathRoom
	waitstate
	end

J_BattleFrontier_BattlePikeRoom_EventScript_DisableHealing::
	pike_nohealing TRUE
	return

J_BattleFrontier_BattlePikeRoom_EventScript_EnableHealing::
	pike_nohealing FALSE
	return

J_BattleFrontier_BattlePikeRoom_EventScript_WarpToFinalRoom::
	applymovement 255, J_BattleFrontier_BattlePikeRoom_Movement_HidePlayer
	waitmovement 0
	call BattleFrontier_BattlePike_EventScript_CloseCurtain
	warpsilent MAP_BATTLE_FRONTIER_BATTLE_PIKE_ROOM_FINAL, 2, 7
	return

J_BattleFrontier_BattlePikeRoom_EventScript_WarpToThreePathRoom::
	applymovement 255, J_BattleFrontier_BattlePikeRoom_Movement_HidePlayer
	waitmovement 0
	call BattleFrontier_BattlePike_EventScript_CloseCurtain
	warpsilent MAP_BATTLE_FRONTIER_BATTLE_PIKE_THREE_PATH_ROOM, 6, 10
	return

J_BattleFrontier_BattlePikeRoomWildMons_EventScript_Exit::
	pike_exitwildmonroom
	pike_ispartyfullhealth
	call_if_eq 32781, TRUE, J_BattleFrontier_BattlePikeRoom_EventScript_DisableHealing
	call_if_ne 32781, TRUE, J_BattleFrontier_BattlePikeRoom_EventScript_EnableHealing
	pike_get 1
	addvar 32781, 1
	pike_set 1, 32781
	frontier_get 2
	addvar 32781, 1
	frontier_set 2, 32781
	pike_isfinalroom
	call_if_eq 32781, TRUE, J_BattleFrontier_BattlePikeRoom_EventScript_WarpToFinalRoom
	call_if_eq 32781, FALSE, J_BattleFrontier_BattlePikeRoom_EventScript_WarpToThreePathRoom
	waitstate
	end

J_BattleFrontier_BattlePikeRoomWildMons_EventScript_SetEnteredRoom::
	setvar 16387, 1
	setvar 16386, 1
	end

J_BattleFrontier_BattlePikeRoomWildMons_EventScript_NoTurningBack::
	setvar 16387, 0
	setvar 16386, 0
	lockall
	msgbox J_BattleFrontier_BattlePike_Text_PathBlockedNoTurningBack, MSGBOX_DEFAULT
	closemessage
	releaseall
	end

J_BattleFrontier_BattlePike_EventScript_Retire::
	frontier_set 0 4
	warp MAP_BATTLE_FRONTIER_BATTLE_PIKE_LOBBY, 5, 6
	waitstate
	end

J_BattleFrontier_BattlePikeRoom_OnResume:
	setorcopyvar 32774, 32781
	frontier_get 0
	goto_if_eq 32781, 2, J_BattleFrontier_BattlePikeThreePathRoom_EventScript_EndOnResume
	goto_if_eq 32781, 1, J_BattleFrontier_BattlePikeThreePathRoom_EventScript_EndOnResume
	call J_BattleFrontier_BattlePikeRoom_EventScript_ResetSketchedMoves

J_BattleFrontier_BattlePikeThreePathRoom_EventScript_EndOnResume::
	setorcopyvar 32781, 32774
	end

J_BattleFrontier_BattlePikeRoom_EventScript_ResetSketchedMoves::
	frontier_resetsketch
	return

J_BattleFrontier_BattlePikeRoom_Movement_HidePlayer:
	set_invisible
	step_end

