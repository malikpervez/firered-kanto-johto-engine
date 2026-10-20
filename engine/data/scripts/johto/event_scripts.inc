@ Johto (data/event_scripts.s), as built into the FireRed game.

J_EventScript_WhiteOut::
	call J_EverGrandeCity_HallOfFame_EventScript_ResetEliteFour
	.if 1
	clearflag 2411
	clearflag 2410
	clearflag 2409
	clearflag 8804
	.endif
	goto J_EventScript_ResetMrBriney
	end

J_EventScript_AfterWhiteOutHeal::
	lockall
	msgbox J_gText_FirstShouldRestoreMonsHealth
	call J_EventScript_PkmnCenterNurse_TakeAndHealPkmn
	call_if_unset 0, J_EventScript_AfterWhiteOutHealMsgPreFirstBoss
	call_if_set 0, J_EventScript_AfterWhiteOutHealMsg
	applymovement 32783, J_Movement_PkmnCenterNurse_Bow
	waitmovement 0
	fadedefaultbgm
	releaseall
	end

J_EventScript_AfterWhiteOutHealMsgPreFirstBoss::
	msgbox J_gText_MonsHealedShouldBuyPotions
	return

J_EventScript_AfterWhiteOutHealMsg::
	msgbox J_gText_MonsHealed
	return

J_EventScript_AfterWhiteOutMomHeal::
	lockall
	textcolor 1
	applymovement 1, J_Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	msgbox J_gText_HadQuiteAnExperienceTakeRest
	call J_Common_EventScript_OutOfCenterPartyHeal
	msgbox J_gText_MomExplainHPGetPotions
	fadedefaultbgm
	releaseall
	end

J_EventScript_ResetMrBriney::
	goto_if_eq 20614, 1, J_EventScript_MoveMrBrineyToHouse
	goto_if_eq 20614, 2, J_EventScript_MoveMrBrineyToDewford
	goto_if_eq 20614, 3, J_EventScript_MoveMrBrineyToRoute109
	end

J_EventScript_MoveMrBrineyToHouse::
	setflag 0
	setflag 0
	setflag 0
	setflag 0
	clearflag 0
	clearflag 0
	clearflag 0
	end

J_EventScript_MoveMrBrineyToDewford::
	setflag 0
	setflag 0
	setflag 0
	setflag 0
	setflag 0
	setflag 0
	clearflag 0
	clearflag 0
	end

J_EventScript_MoveMrBrineyToRoute109::
	setflag 0
	setflag 0
	setflag 0
	setflag 0
	setflag 0
	setflag 0
	clearflag 0
	clearflag 0
	end

J_EverGrandeCity_HallOfFame_EventScript_ResetEliteFour::
	clearflag 0
	clearflag 0
	clearflag 0
	clearflag 0
	setvar 20620, 0
	return

J_Common_EventScript_UpdateBrineyLocation::
	goto_if_unset 8699, J_Common_EventScript_NopReturn
	goto_if_set 0, J_Common_EventScript_NopReturn
	goto_if_unset 0, J_EventScript_SetBrineyLocation_House
	goto_if_unset 0, J_EventScript_SetBrineyLocation_Dewford
	goto_if_unset 0, J_EventScript_SetBrineyLocation_Route109
	return

J_EventScript_SetBrineyLocation_House::
	setvar 20614, 1
	return

J_EventScript_SetBrineyLocation_Dewford::
	setvar 20614, 2
	return

J_EventScript_SetBrineyLocation_Route109::
	setvar 20614, 3
	return

