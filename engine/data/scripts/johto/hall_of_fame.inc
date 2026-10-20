@ Johto (data/scripts/hall_of_fame.inc), as built into the FireRed game.

J_EverGrandeCity_HallOfFame_EventScript_SetGameClearFlags::
	special SetChampionSaveWarp
	setflag 10399
	call J_EverGrandeCity_HallOfFame_EventScript_ResetDefeatedEventLegendaries
	call_if_eq 20668, 0, J_EverGrandeCity_HallOfFame_EventScript_SetDesertUnderpassCommentReady
	clearflag 0
	call J_EverGrandeCity_HallOfFame_EventScript_ResetEliteFour
	setflag 0
	clearflag 0
	clearflag 0
	setvar 20662, 2
	setflag 0
	clearflag 0
	clearflag 0
	clearflag 0
	setflag 0
	clearflag 0
	setflag 0
	special UpdateTrainerFanClubGameClear
	call_if_unset 0, J_EverGrandeCity_HallOfFame_EventScript_ReadyReceiveSSTicketEvent
	call_if_unset 0, J_EverGrandeCity_HallOfFame_EventScript_ShowStevensHouseBeldum
	setflag 0
	setflag 0
	call_if_eq 20675, 0, J_EverGrandeCity_HallOfFame_EventScript_ReadyDexUpgradeEvent
	return

J_EverGrandeCity_HallOfFame_EventScript_ResetDefeatedEventLegendaries::
	clearflag 8761
	clearflag 0
	clearflag 8762
	clearflag 8760
	clearflag 8759
	return

J_EverGrandeCity_HallOfFame_EventScript_SetDesertUnderpassCommentReady::
	setvar 20668, 1
	return

J_EverGrandeCity_HallOfFame_EventScript_ShowStevensHouseBeldum::
	clearflag 0
	return

J_EverGrandeCity_HallOfFame_EventScript_ReadyReceiveSSTicketEvent::
	setvar 20594, 3
	setvar 20604, 3
	clearflag 0
	return

J_EverGrandeCity_HallOfFame_EventScript_ReadyDexUpgradeEvent::
	setvar 20675, 1
	return

