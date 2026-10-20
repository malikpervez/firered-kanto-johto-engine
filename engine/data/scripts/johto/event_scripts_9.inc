@ Johto (data/event_scripts.s), as built into the FireRed game.

J_Common_EventScript_NopReturn::
	return

J_EventScript_SetResultTrue::
	setvar 32781, TRUE
	return

J_EventScript_SetResultFalse::
	setvar 32781, FALSE
	return

J_EventScript_GetElevatorFloor::
	special GetElevatorFloor
	return

J_EventScript_CableClub_SetVarResult1::
	setvar 32781, 1
	return

J_EventScript_CableClub_SetVarResult0::
	setvar 32781, 0
	return

J_Common_EventScript_UnionRoomAttendant::



	call J_CableClub_EventScript_UnionRoomAttendant

	end

J_Common_EventScript_WirelessClubAttendant::



	call J_CableClub_EventScript_WirelessClubAttendant

	end

J_Common_EventScript_DirectCornerAttendant::



	call J_CableClub_EventScript_DirectCornerAttendant

	end

J_Common_EventScript_RemoveStaticPokemon::
	fadescreenswapbuffers 1
	removeobject 32783
	fadescreenswapbuffers 0
	release
	end

J_Common_EventScript_LegendaryFlewAway::
	fadescreenswapbuffers 1
	removeobject 32783
	fadescreenswapbuffers 0
	bufferspeciesname STR_VAR_1, 32772
	msgbox J_gText_LegendaryFlewAway, MSGBOX_DEFAULT
	release
	end

J_EventScript_VsSeekerChargingDone::
	special VsSeekerFreezeObjectsAfterChargeComplete
	waitstate
	special VsSeekerResetObjectMovementAfterChargeComplete
	releaseall
	end

J_EventScript_SetExitingCyclingRoad::
	lockall
	clearflag 2096
	setvar 20558, 0
	releaseall
	end

J_EventScript_SetEnteringCyclingRoad::
	lockall
	setvar 20558, 1
	releaseall
	end

J_EventScript_TryDarkenRuins::
	goto_if_set 0, J_Common_EventScript_NopReturn
	setweather 11
	doweather
	return

J_Text_MonFlewAway::
	.string "Th{SE_M_REVERSAL}{STR_VAR_1} fle{SE_M_TWISTER}away!$"

J_Text_Gyaoo::
	.string "Gyaoo!$"

J_EventScript_BrailleCursorWaitButton::
	special BrailleCursorToggle
	waitbuttonpress
	closebraillemessage
	playse 5
	setvar 32774, 1
	special BrailleCursorToggle
	return

J_EventScript_PalletTown_PlayersHouse_2F_ShutDownPC::
	setvar 32772, PC_LOCATION_PLAYER_HOUSE_FRLG
	playse 3
	special DoPCTurnOffEffect
	releaseall
	end

J_EventScript_PalletTown_PlayersHouse_2F_TurnOnPC::
	lockall
	setvar 32772, PC_LOCATION_PLAYER_HOUSE_FRLG
	special DoPCTurnOnEffect
	playse 4
	msgbox J_gText_PlayerHouseBootPC
	special BedroomPC
	waitstate
	releaseall
	end

