@ Johto (data/scripts/rival_graphics.inc), as built into the FireRed game.

J_Common_EventScript_SetupRivalGfxId::
	checkplayergender
	goto_if_eq 32781, MALE, J_EventScript_SetupRivalGfxIdFemale
	goto_if_eq 32781, FEMALE, J_EventScript_SetupRivalGfxIdMale
	end

J_EventScript_SetupRivalGfxIdFemale::
	setvar 16400, 105
	return

J_EventScript_SetupRivalGfxIdMale::
	setvar 16400, 100
	return

J_Common_EventScript_SetupRivalOnBikeGfxId::
	checkplayergender
	goto_if_eq 32781, MALE, J_EventScript_SetupRivalOnBikeGfxIdFemale
	goto_if_eq 32781, FEMALE, J_EventScript_SetupRivalOnBikeGfxIdMale
	end

J_EventScript_SetupRivalOnBikeGfxIdFemale::
	setvar 16403, 106
	return

J_EventScript_SetupRivalOnBikeGfxIdMale::
	setvar 16403, 101
	return

J_Common_EventScript_SetupRivalGfxIdSameGender::
	checkplayergender
	goto_if_eq 32781, MALE, J_EventScript_SetupRivalGfxIdMale2
	goto_if_eq 32781, FEMALE, J_EventScript_SetupRivalGfxIdFemale2
	end

J_EventScript_SetupRivalGfxIdMale2::
	setvar 16400, 100
	return

J_EventScript_SetupRivalGfxIdFemale2::
	setvar 16400, 105
	return

