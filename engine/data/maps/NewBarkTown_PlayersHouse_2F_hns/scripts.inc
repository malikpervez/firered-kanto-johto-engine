@ Johto (data/maps/NewBarkTown_PlayersHouse_2F_hns/scripts.inc), as built into the FireRed game.

NewBarkTown_PlayersHouse_2F_hns_MapScripts::
	map_script 3, NewBarkTown_PlayersHouse_2F_OnTransition
	map_script 4, NewBarkTown_PlayersHouse_2F_OnWarp
	.byte 0

NewBarkTown_PlayersHouse_2F_OnTransition::
	call J_SecretBase_EventScript_SetDecorationFlags
	setvar 20601, 0
	end

NewBarkTown_PlayersHouse_2F_OnWarp::
	map_script_2 20601, 0, NewBarkTown_PlayersHouse_2F_OnWarp_SetDecoration
	.2byte 0

NewBarkTown_PlayersHouse_2F_OnWarp_SetDecoration::
	call J_SecretBase_EventScript_InitDecorations
	end

NewBarkTown_PlayersHouse_2F_Script_ClockSetupTrigger1::
	lock
	playse 21
	applymovement 255, J_Common_Movement_ExclamationMark
	waitmovement 255
	delay 60
	applymovement 255, NewBarkTown_PlayersHouse_2F_Movement_PlayerWalkToClock1
	waitmovement 0
	msgbox J_PlayersHouse_2F_Text_ClockIsStopped, MSGBOX_DEFAULT
	call J_PlayersHouse_2F_EventScript_SetWallClock
	delay 30
	setvar 20581, 1
	setflag 8807
	helpwindow HELP_GAMESTART_WINDOW
	releaseall
	end

NewBarkTown_PlayersHouse_2F_Script_ClockSetupTrigger2::
	lock
	playse 21
	applymovement 255, J_Common_Movement_ExclamationMark
	waitmovement 255
	delay 60
	applymovement 255, NewBarkTown_PlayersHouse_2F_Movement_PlayerWalkToClock2
	msgbox J_PlayersHouse_2F_Text_ClockIsStopped, MSGBOX_DEFAULT
	call J_PlayersHouse_2F_EventScript_SetWallClock
	delay 30
	setvar 20581, 1
	setflag 8807
	helpwindow HELP_GAMESTART_WINDOW
	releaseall
	end

NewBarkTown_PlayersHouse_2F_Movement_PlayerWalkToClock1:
	walk_right
	walk_up
	delay_8
	step_end

NewBarkTown_PlayersHouse_2F_Movement_PlayerWalkToClock2:
	walk_up
	delay_8
	step_end

NewBarkTown_PlayersHouse_2F_EventScript_NES::
	msgbox NewBarkTown_PlayersHouse_2F_Text_NES, MSGBOX_SIGN
	end

NewBarkTown_PlayersHouse_2F_EventScript_PC::
	lockall
	setvar 32772, PC_LOCATION_PLAYER_HOUSE_HNS
	special DoPCTurnOnEffect
	playse 4
	msgbox J_gText_PlayerHouseBootPC, MSGBOX_DEFAULT
	special BedroomPC
	waitstate
	releaseall
	end

NewBarkTown_PlayersHouse_2F_EventScript_TurnOffPlayerPC::
	setvar 32772, PC_LOCATION_PLAYER_HOUSE_HNS
	playse 3
	special DoPCTurnOffEffect
	releaseall
	end

NewBarkTown_PlayersHouse_2F_Text_NES:
	.string "{PLAYER} playe{SE_M_WATERFALL}wit{SE_M_TRI_ATTACK}th{SE_M_REVERSAL}NES.\p"
	.string "…Okay!\n"
	.string "It'{SE_M_GRASSWHISTLE}tim{SE_M_REVERSAL}t{SE_M_ATTRACT2}go!$"

