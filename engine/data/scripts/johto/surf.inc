@ Johto (data/scripts/surf.inc), as built into the FireRed game.

J_EventScript_UseSurf::
	checkfieldmove FIELD_MOVE_SURF, TRUE
	goto_if_eq 32781, 6, J_EventScript_EndUseSurf
	bufferpartymonnick STR_VAR_1, 32781
	setfieldeffectargument 0, 32781
	lockall
	msgbox J_gText_WantToUseSurf, MSGBOX_YESNO
	goto_if_eq 32781, NO, J_EventScript_ReleaseUseSurf
	msgbox J_gText_PlayerUsedSurf, MSGBOX_DEFAULT
	dofieldeffect 9

J_EventScript_ReleaseUseSurf::
	releaseall

J_EventScript_EndUseSurf::
	end

J_EventScript_CurrentTooFast::
	lockall
	checkfieldmove FIELD_MOVE_SURF
	goto_if_eq 32781, FALSE, J_EventScript_CurrentTooFastEndMsg
	playse 5
	msgbox J_Text_CurrentTooFast

J_EventScript_CurrentTooFastEndMsg::
	releaseall
	end

