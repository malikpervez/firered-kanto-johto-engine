@ Johto (data/scripts/hall_of_fame_frlg.inc), as built into the FireRed game.

J_EventScript_SetDefeatedEliteFourFlagsVars::
	clearflag 0
	call J_EventScript_ResetEliteFour
	special Script_UpdateTrainerFanClubGameClear
	specialvar 32781, IsNationalPokedexEnabled
	call_if_eq 32781, FALSE, J_EventScript_SetReadyTryGiveNationalDexScene
	call J_EventScript_ResetLegendaries
	return

J_EventScript_SetReadyTryGiveNationalDexScene::
	setvar 20544, 2
	return

J_EventScript_ResetLegendaries::
	clearflag 0
	clearflag 0
	clearflag 8935
	return

J_EventScript_ResetEliteFourEnd::
	call J_EventScript_ResetEliteFour
	end

J_EventScript_ResetEliteFour::
	clearflag 0
	clearflag 0
	clearflag 0
	clearflag 0
	clearflag 0
	cleartrainerflag 338
	cleartrainerflag 339
	cleartrainerflag 340
	cleartrainerflag 620
	cleartrainerflag 621
	cleartrainerflag 622
	setvar 20568, 0
	return

