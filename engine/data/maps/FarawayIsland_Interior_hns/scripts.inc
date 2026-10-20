@ Johto (data/maps/FarawayIsland_Interior_hns/scripts.inc), as built into the FireRed game.

FarawayIsland_Interior_hns_MapScripts::
	map_script 5, FarawayIsland_Interior_hns_OnResume
	map_script 3, FarawayIsland_Interior_hns_OnTransition
	map_script 2, FarawayIsland_Interior_hns_OnFrame
	map_script 7, FarawayIsland_Interior_hns_OnReturnToField
	.byte 0

FarawayIsland_Interior_hns_OnReturnToField:
	call_if_set 10342, FarawayIsland_Interior_hns_EventScript_TrySetMewAboveGrass
	end

FarawayIsland_Interior_hns_EventScript_TrySetMewAboveGrass::
	specialvar 32781, GetBattleOutcome
	goto_if_eq 32781, 1, FarawayIsland_Interior_hns_EventScript_SetMewAboveGrass
	goto_if_eq 32781, 4, FarawayIsland_Interior_hns_EventScript_SetMewAboveGrass
	goto_if_eq 32781, 5, FarawayIsland_Interior_hns_EventScript_SetMewAboveGrass
	goto_if_eq 32781, 10, FarawayIsland_Interior_hns_EventScript_SetMewAboveGrass
	return

FarawayIsland_Interior_hns_EventScript_SetMewAboveGrass::
	setvar 32772, 1
	special SetMewAboveGrass
	return

FarawayIsland_Interior_hns_OnResume:
	call_if_set 10342, FarawayIsland_Interior_hns_EventScript_TryRemoveMew
	end

FarawayIsland_Interior_hns_EventScript_TryRemoveMew::
	specialvar 32781, GetBattleOutcome
	goto_if_ne 32781, 7, J_Common_EventScript_NopReturn
	removeobject 32783
	return

FarawayIsland_Interior_hns_OnTransition:
	setflag 14
	setvar 20522, 0
	setvar 16385, 1
	call_if_unset 8769, FarawayIsland_Interior_hns_EventScript_TryShowMew
	end

FarawayIsland_Interior_hns_EventScript_TryShowMew::
	goto_if_set 8761, J_Common_EventScript_NopReturn
	clearflag 9104
	setvar 16385, 0
	return

FarawayIsland_Interior_hns_OnFrame:
	map_script_2 16385, 0, FarawayIsland_Interior_hns_EventScript_FindMew
	.2byte 0

FarawayIsland_Interior_hns_EventScript_FindMew::
	lockall
	playse 21
	applymovement 1, J_Common_Movement_ExclamationMark
	delay 55
	waitmovement 1
	applymovement 1, J_Common_Movement_Delay48
	waitmovement 0
	applymovement 1, FarawayIsland_Interior_hns_Movement_MewMoveAndHide
	waitmovement 0
	copyobjectxytoperm 1
	setvar 16385, 1
	releaseall
	end

FarawayIsland_Interior_hns_Movement_MewMoveAndHide:
	walk_up
	walk_up
	walk_up
	walk_in_place_faster_down
	set_invisible
	step_end

FarawayIsland_Interior_hns_Movement_MewAppear:
	set_visible
	step_end

FarawayIsland_Interior_hns_Movement_MewFloatUpNorth:
	lock_facing_direction
	walk_fast_up
	walk_fast_up
	unlock_facing_direction
	walk_in_place_down
	walk_in_place_down
	step_end

FarawayIsland_Interior_hns_Movement_MewFloatUpSouth:
	lock_facing_direction
	walk_fast_up
	walk_fast_up
	unlock_facing_direction
	walk_in_place_up
	walk_in_place_up
	step_end

FarawayIsland_Interior_hns_Movement_MewFloatUpWest:
	lock_facing_direction
	walk_fast_up
	walk_fast_up
	unlock_facing_direction
	walk_in_place_right
	walk_in_place_right
	step_end

FarawayIsland_Interior_hns_Movement_MewFloatUpEast:
	lock_facing_direction
	walk_fast_up
	walk_fast_up
	unlock_facing_direction
	walk_in_place_left
	walk_in_place_left
	step_end

FarawayIsland_Interior_hns_EventScript_Mew::
	lock
	faceplayer
	applymovement 1, FarawayIsland_Interior_hns_Movement_MewAppear
	waitmovement 0
	setvar 32772, 0
	special SetMewAboveGrass
	message J_FarawayIsland_Interior_Text_Mew
	waitse
	playmoncry 151, 2
	call_if_eq 32780, DIR_NORTH, FarawayIsland_Interior_hns_EventScript_FoundMewNorth
	call_if_eq 32780, DIR_SOUTH, FarawayIsland_Interior_hns_EventScript_FoundMewSouth
	call_if_eq 32780, DIR_WEST, FarawayIsland_Interior_hns_EventScript_FoundMewWest
	call_if_eq 32780, DIR_EAST, FarawayIsland_Interior_hns_EventScript_FoundMewEast
	special DestroyMewEmergingGrassSprite
	delay 40
	waitmoncry
	seteventmon 151, 50
	setflag 10342
	special BattleSetup_StartLegendaryBattle
	waitstate
	clearflag 10342
	specialvar 32781, GetBattleOutcome
	goto_if_eq 32781, 1, FarawayIsland_Interior_hns_EventScript_MewDefeated
	goto_if_eq 32781, 4, FarawayIsland_Interior_hns_EventScript_PlayerOrMewRan
	goto_if_eq 32781, 5, FarawayIsland_Interior_hns_EventScript_PlayerOrMewRan
	goto_if_eq 32781, 10, FarawayIsland_Interior_hns_EventScript_PlayerOrMewRan
	setflag 8769
	release
	end

FarawayIsland_Interior_hns_EventScript_MewDefeated::
	setflag 8761
	setvar 32772, 151
	goto J_Common_EventScript_LegendaryFlewAway
	end

FarawayIsland_Interior_hns_EventScript_PlayerOrMewRan::
	setvar 32772, 151
	goto J_Common_EventScript_LegendaryFlewAway
	end

FarawayIsland_Interior_hns_EventScript_FoundMewNorth::
	applymovement 1, FarawayIsland_Interior_hns_Movement_MewFloatUpNorth
	waitmovement 0
	return

FarawayIsland_Interior_hns_EventScript_FoundMewSouth::
	applymovement 1, FarawayIsland_Interior_hns_Movement_MewFloatUpSouth
	waitmovement 0
	return

FarawayIsland_Interior_hns_EventScript_FoundMewWest::
	applymovement 1, FarawayIsland_Interior_hns_Movement_MewFloatUpWest
	waitmovement 0
	return

FarawayIsland_Interior_hns_EventScript_FoundMewEast::
	applymovement 1, FarawayIsland_Interior_hns_Movement_MewFloatUpEast
	waitmovement 0
	return

FarawayIsland_Interior_hns_EventScript_HideMewWhenGrassCut::
	lockall
	fadescreenswapbuffers 1
	setflag 9104
	removeobject 1
	fadescreenswapbuffers 0
	msgbox FarawayIsland_Interior_hns_Text_TheFeelingOfBeingWatchedFaded, MSGBOX_DEFAULT
	closemessage
	releaseall
	end

FarawayIsland_Interior_hns_Text_TheFeelingOfBeingWatchedFaded:
	.string "Th{SE_M_REVERSAL}feelin{SE_M_SANDSTORM}o{SE_M_ACID_ARMOR}bein{SE_M_SANDSTORM}watche{SE_M_WATERFALL}faded…$"

