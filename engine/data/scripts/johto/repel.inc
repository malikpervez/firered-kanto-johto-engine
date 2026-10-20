@ Johto (data/scripts/repel.inc), as built into the FireRed game.

J_EventScript_BufferSprayName::
	.if 0 != 0
	bufferitemname STR_VAR_1, 0
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
	checkitem 0, 1
	compare 32781, TRUE
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
	setvar 32781, 0
	call J_EventScript_UseSpray
	return

J_EventScript_UseDifferentSpray::
	specialvar LOCAL_VAR_NEW_SPRAY, GetSprayId
	bufferitemname STR_VAR_2, LOCAL_VAR_NEW_SPRAY
	msgbox J_Text_SprayWoreOffAskUseX, MSGBOX_YESNO
	compare 32781, YES
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
	compare 32781, YES
	goto_if_eq J_EventScript_UseLastUsedSpray_2

J_EventScript_UseLastUsedSpray_1:
	return

J_EventScript_UseLastUsedSpray_2:
	copyvar LOCAL_VAR_SPRAY, 0
	call J_EventScript_SetSingleSprayAndUse
	goto J_EventScript_UseLastUsedSpray_1
	.endif


	.if TRUE == TRUE

J_EventScript_ChooseWhichSpray::
	message J_Text_SprayWoreOffAskUseAnother
	waitmessage
	callnative DrawSprayMenu
	waitstate
	compare 32781, 127
	goto_if_ne J_EventScript_ChooseWhichSpray_3

J_EventScript_ChooseWhichSpray_1:
	closemessage
	releaseall
	end

J_EventScript_ChooseWhichSpray_2:
	call J_EventScript_UseSpray
	goto J_EventScript_ChooseWhichSpray_1

J_EventScript_ChooseWhichSpray_3:
	compare 32781, 32771
	goto_if_ne J_EventScript_ChooseWhichSpray_2
	goto J_EventScript_ChooseWhichSpray_1
	.endif

J_EventScript_UseSpray::
	playse 47
	waitse
	callnative HandleSprayMenuChoice
	removeitem LOCAL_VAR_SPRAY, 1
	bufferitemname STR_VAR_2, LOCAL_VAR_SPRAY
	msgbox J_Text_SprayWoreOffUseX, MSGBOX_SIGN
	return

J_Text_SprayWoreOff::
	.string "{STR_VAR_1}'{SE_M_GRASSWHISTLE}effec{SE_M_SPIT_UP}wor{SE_M_REVERSAL}off…$"

J_Text_SprayWoreOffAskUseAnother::
	.string "{STR_VAR_1}'{SE_M_GRASSWHISTLE}effec{SE_M_SPIT_UP}wor{SE_M_REVERSAL}off!\n"
	.string "Us{SE_M_REVERSAL}another?$"

J_Text_SprayWoreOffAskUseX::
	.string "{STR_VAR_1}'{SE_M_GRASSWHISTLE}effec{SE_M_SPIT_UP}wor{SE_M_REVERSAL}off…\n"
	.string "Us{SE_M_REVERSAL}{SE_M_CHARGE}{STR_VAR_2}?$"

J_Text_SprayWoreOffUseX::
	.string "{PLAYER} use{SE_M_WATERFALL}the\n"
	.string "{STR_VAR_2}.$"

