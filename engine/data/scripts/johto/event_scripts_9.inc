@ Johto (data/event_scripts.s), as built into the FireRed game.

J_Common_EventScript_NopReturn::
	return

J_EventScript_SetResultTrue::
	setvar VAR_RESULT, TRUE
	return

J_EventScript_SetResultFalse::
	setvar VAR_RESULT, FALSE
	return

J_EventScript_GetElevatorFloor::
	special GetElevatorFloor
	return

J_EventScript_CableClub_SetVarResult1::
	setvar VAR_RESULT, 1
	return

J_EventScript_CableClub_SetVarResult0::
	setvar VAR_RESULT, 0
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
	fadescreenswapbuffers FADE_TO_BLACK
	removeobject VAR_LAST_TALKED
	fadescreenswapbuffers FADE_FROM_BLACK
	release
	end

J_Common_EventScript_LegendaryFlewAway::
	fadescreenswapbuffers FADE_TO_BLACK
	removeobject VAR_LAST_TALKED
	fadescreenswapbuffers FADE_FROM_BLACK
	bufferspeciesname STR_VAR_1, VAR_0x8004
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
	clearflag FLAG_SYS_ON_CYCLING_ROAD
	setvar JOHTO_VAR_MAP_SCENE_ROUTE16, 0
	releaseall
	end

J_EventScript_SetEnteringCyclingRoad::
	lockall
	setvar JOHTO_VAR_MAP_SCENE_ROUTE16, 1
	releaseall
	end

J_EventScript_TryDarkenRuins::
	goto_if_set JOHTO_FLAG_SYS_UNLOCKED_TANOBY_RUINS, J_Common_EventScript_NopReturn
	setweather WEATHER_SHADE
	doweather
	return

J_Text_MonFlewAway::
	.string "The {STR_VAR_1} flew away!$"

J_Text_Gyaoo::
	.string "Gyaoo!$"

J_EventScript_BrailleCursorWaitButton::
	special BrailleCursorToggle
	waitbuttonpress
	closebraillemessage
	playse SE_SELECT
	setvar VAR_0x8006, 1
	special BrailleCursorToggle
	return

J_EventScript_PalletTown_PlayersHouse_2F_ShutDownPC::
	setvar VAR_0x8004, PC_LOCATION_PLAYER_HOUSE_FRLG
	playse SE_PC_OFF
	special DoPCTurnOffEffect
	releaseall
	end

J_EventScript_PalletTown_PlayersHouse_2F_TurnOnPC::
	lockall
	setvar VAR_0x8004, PC_LOCATION_PLAYER_HOUSE_FRLG
	special DoPCTurnOnEffect
	playse SE_PC_ON
	msgbox J_gText_PlayerHouseBootPC
	special BedroomPC
	waitstate
	releaseall
	end

