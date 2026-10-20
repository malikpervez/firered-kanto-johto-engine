@ Johto (data/scripts/repel.inc), as built into the FireRed game.

J_EventScript_BufferSprayName::
	.if 0 != 0
	bufferitemname STR_VAR_1, VAR_LAST_REPEL_LURE_USED
	return
	.endif
	specialvar LOCAL_VAR_SPRAY_TYPE, GetLastUsedSprayType
	compare LOCAL_VAR_SPRAY_TYPE, ITEM_REPEL
	goto_if_eq J_EventScript_BufferSprayName_2
	bufferitemname STR_VAR_1, ITEM_LURE

J_EventScript_BufferSprayName_1:
	return

J_EventScript_BufferSprayName_2:
	bufferitemname STR_VAR_1, ITEM_REPEL
	goto J_EventScript_BufferSprayName_1

J_EventScript_SprayWoreOff::
	lock
	call J_EventScript_BufferSprayName
	specialvar LOCAL_VAR_NUM_SPRAY_STRENGTH, GetNumberSprayStrength
	switch LOCAL_VAR_NUM_SPRAY_STRENGTH
	case 0, J_EventScript_SprayWoreOffMessage
	case 1, J_EventScript_UseSingleSpray
	goto J_EventScript_HandleMultipleSprays
	return

J_EventScript_HandleMultipleSprays::
	.if TRUE == TRUE
	goto J_EventScript_ChooseWhichSpray
	.else
	goto J_EventScript_UseSingleSpray
	.endif
	return

J_EventScript_SprayWoreOffMessage::
	msgbox J_Text_SprayWoreOff, MSGBOX_SIGN
	releaseall
	end

J_EventScript_UseSingleSpray::
	.if 0 == 0
	call J_EventScript_UseDifferentSpray
	.else
	checkitem VAR_LAST_REPEL_LURE_USED, 1
	compare VAR_RESULT, TRUE
	goto_if_eq J_EventScript_UseSingleSpray_2
	call J_EventScript_UseDifferentSpray
	.endif

J_EventScript_UseSingleSpray_1:
	closemessage
	releaseall
	end

	.if 0 != 0

J_EventScript_UseSingleSpray_2:
	call J_EventScript_UseLastUsedSpray
	goto J_EventScript_UseSingleSpray_1
	.endif

J_EventScript_SetSingleSprayAndUse::
	setvar VAR_RESULT, 0
	call J_EventScript_UseSpray
	return

J_EventScript_UseDifferentSpray::
	specialvar LOCAL_VAR_NEW_SPRAY, GetSprayId
	bufferitemname STR_VAR_2, LOCAL_VAR_NEW_SPRAY
	msgbox J_Text_SprayWoreOffAskUseX, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq J_EventScript_UseDifferentSpray_2

J_EventScript_UseDifferentSpray_1:
	return

J_EventScript_UseDifferentSpray_2:
	copyvar LOCAL_VAR_SPRAY, LOCAL_VAR_NEW_SPRAY
	call J_EventScript_SetSingleSprayAndUse
	goto J_EventScript_UseDifferentSpray_1


	.if 0 != 0

J_EventScript_UseLastUsedSpray::
	msgbox J_Text_SprayWoreOffAskUseAnother, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq J_EventScript_UseLastUsedSpray_2

J_EventScript_UseLastUsedSpray_1:
	return

J_EventScript_UseLastUsedSpray_2:
	copyvar LOCAL_VAR_SPRAY, VAR_LAST_REPEL_LURE_USED
	call J_EventScript_SetSingleSprayAndUse
	goto J_EventScript_UseLastUsedSpray_1
	.endif


	.if TRUE == TRUE

J_EventScript_ChooseWhichSpray::
	message J_Text_SprayWoreOffAskUseAnother
	waitmessage
	callnative DrawSprayMenu
	waitstate
	compare VAR_RESULT, MULTI_B_PRESSED
	goto_if_ne J_EventScript_ChooseWhichSpray_3

J_EventScript_ChooseWhichSpray_1:
	closemessage
	releaseall
	end

J_EventScript_ChooseWhichSpray_2:
	call J_EventScript_UseSpray
	goto J_EventScript_ChooseWhichSpray_1

J_EventScript_ChooseWhichSpray_3:
	compare VAR_RESULT, VAR_0x8003
	goto_if_ne J_EventScript_ChooseWhichSpray_2
	goto J_EventScript_ChooseWhichSpray_1
	.endif

J_EventScript_UseSpray::
	playse SE_REPEL
	waitse
	callnative HandleSprayMenuChoice
	removeitem LOCAL_VAR_SPRAY, 1
	bufferitemname STR_VAR_2, LOCAL_VAR_SPRAY
	msgbox J_Text_SprayWoreOffUseX, MSGBOX_SIGN
	return

J_Text_SprayWoreOff::
	.string "{STR_VAR_1}'s effect wore off…$"

J_Text_SprayWoreOffAskUseAnother::
	.string "{STR_VAR_1}'s effect wore off!\n"
	.string "Use another?$"

J_Text_SprayWoreOffAskUseX::
	.string "{STR_VAR_1}'s effect wore off…\n"
	.string "Use a {STR_VAR_2}?$"

J_Text_SprayWoreOffUseX::
	.string "{PLAYER} used the\n"
	.string "{STR_VAR_2}.$"

