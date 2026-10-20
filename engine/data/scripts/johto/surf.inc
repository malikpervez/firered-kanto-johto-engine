@ Johto (data/scripts/surf.inc), as built into the FireRed game.

J_EventScript_UseSurf::
	checkfieldmove FIELD_MOVE_SURF, TRUE
	goto_if_eq VAR_RESULT, PARTY_SIZE, J_EventScript_EndUseSurf
	bufferpartymonnick STR_VAR_1, VAR_RESULT
	setfieldeffectargument 0, VAR_RESULT
	lockall
	msgbox J_gText_WantToUseSurf, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, J_EventScript_ReleaseUseSurf
	msgbox J_gText_PlayerUsedSurf, MSGBOX_DEFAULT
	dofieldeffect FLDEFF_USE_SURF

J_EventScript_ReleaseUseSurf::
	releaseall

J_EventScript_EndUseSurf::
	end

J_EventScript_CurrentTooFast::
	lockall
	checkfieldmove FIELD_MOVE_SURF
	goto_if_eq VAR_RESULT, FALSE, J_EventScript_CurrentTooFastEndMsg
	playse SE_SELECT
	msgbox J_Text_CurrentTooFast

J_EventScript_CurrentTooFastEndMsg::
	releaseall
	end

