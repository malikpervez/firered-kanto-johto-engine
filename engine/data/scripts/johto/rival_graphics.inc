@ Johto (data/scripts/rival_graphics.inc), as built into the FireRed game.

J_Common_EventScript_SetupRivalGfxId::
	checkplayergender
	goto_if_eq VAR_RESULT, MALE, J_EventScript_SetupRivalGfxIdFemale
	goto_if_eq VAR_RESULT, FEMALE, J_EventScript_SetupRivalGfxIdMale
	end

J_EventScript_SetupRivalGfxIdFemale::
	setvar VAR_OBJ_GFX_ID_0, OBJ_EVENT_GFX_RIVAL_MAY_NORMAL
	return

J_EventScript_SetupRivalGfxIdMale::
	setvar VAR_OBJ_GFX_ID_0, OBJ_EVENT_GFX_RIVAL_BRENDAN_NORMAL
	return

J_Common_EventScript_SetupRivalOnBikeGfxId::
	checkplayergender
	goto_if_eq VAR_RESULT, MALE, J_EventScript_SetupRivalOnBikeGfxIdFemale
	goto_if_eq VAR_RESULT, FEMALE, J_EventScript_SetupRivalOnBikeGfxIdMale
	end

J_EventScript_SetupRivalOnBikeGfxIdFemale::
	setvar VAR_OBJ_GFX_ID_3, OBJ_EVENT_GFX_RIVAL_MAY_MACH_BIKE
	return

J_EventScript_SetupRivalOnBikeGfxIdMale::
	setvar VAR_OBJ_GFX_ID_3, OBJ_EVENT_GFX_RIVAL_BRENDAN_MACH_BIKE
	return

J_Common_EventScript_SetupRivalGfxIdSameGender::
	checkplayergender
	goto_if_eq VAR_RESULT, MALE, J_EventScript_SetupRivalGfxIdMale2
	goto_if_eq VAR_RESULT, FEMALE, J_EventScript_SetupRivalGfxIdFemale2
	end

J_EventScript_SetupRivalGfxIdMale2::
	setvar VAR_OBJ_GFX_ID_0, OBJ_EVENT_GFX_RIVAL_BRENDAN_NORMAL
	return

J_EventScript_SetupRivalGfxIdFemale2::
	setvar VAR_OBJ_GFX_ID_0, OBJ_EVENT_GFX_RIVAL_MAY_NORMAL
	return

