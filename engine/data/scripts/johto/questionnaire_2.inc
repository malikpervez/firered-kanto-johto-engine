@ Johto (data/scripts/questionnaire.inc), as built into the FireRed game.

J_EventScript_Questionnaire::
	lockall
	msgbox J_Questionnaire_Text_FillOut, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, J_Questionnaire_EventScript_Release
	setvar VAR_0x8004, EASY_CHAT_TYPE_QUESTIONNAIRE
	call J_Common_ShowEasyChatScreen
	lock
	faceplayer
	specialvar VAR_0x8008, GetMartEmployeeObjectEventId
	goto_if_eq VAR_0x8004, 1, J_Questionnaire_EventScript_PlayerInputMysteryEventPhrase
	goto_if_eq VAR_0x8004, 2, J_Questionnaire_EventScript_PlayerInputMysteryGiftPhrase
	goto_if_eq VAR_RESULT, 0, J_Questionnaire_EventScript_Release
	goto_if_eq VAR_RESULT, 1, J_Questionnaire_EventScript_ThankYou
	end

J_Questionnaire_EventScript_PlayerInputMysteryEventPhrase::
	goto_if_unset FLAG_SYS_POKEDEX_GET, J_Questionnaire_EventScript_ThankYou
	goto_if_set JOHTO_FLAG_SYS_MYSTERY_EVENT_ENABLE, J_Questionnaire_EventScript_ThankYou
	applymovement VAR_0x8008, J_Common_Movement_FaceDown
	waitmovement 0
	playse SE_PIN
	applymovement VAR_0x8008, J_Common_Movement_ExclamationMark
	waitmovement 0
	applymovement VAR_0x8008, J_Common_Movement_Delay48
	waitmovement 0
	msgbox J_Questionnaire_Text_YouKnowThoseWordsEvent, MSGBOX_DEFAULT
	setflag JOHTO_FLAG_SYS_MYSTERY_EVENT_ENABLE
	msgbox J_Questionnaire_Text_YouCanAccessMysteryEvent, MSGBOX_DEFAULT
	releaseall
	end

J_Questionnaire_EventScript_PlayerInputMysteryGiftPhrase::
	goto_if_unset FLAG_SYS_POKEDEX_GET, J_Questionnaire_EventScript_ThankYou
	goto_if_set JOHTO_FLAG_SYS_MYSTERY_GIFT_ENABLE, J_Questionnaire_EventScript_ThankYou
	applymovement VAR_0x8008, J_Common_Movement_FaceDown
	waitmovement 0
	playse SE_PIN
	applymovement VAR_0x8008, J_Common_Movement_ExclamationMark
	waitmovement 0
	applymovement VAR_0x8008, J_Common_Movement_Delay48
	waitmovement 0
	msgbox J_Questionnaire_Text_YouKnowThoseWordsGift, MSGBOX_DEFAULT
	setflag JOHTO_FLAG_SYS_MYSTERY_GIFT_ENABLE
	msgbox J_Questionnaire_Text_YouCanAccessMysteryGift, MSGBOX_DEFAULT
	releaseall
	end

J_Questionnaire_EventScript_Release::
	releaseall
	end

J_Questionnaire_EventScript_ThankYou::
	applymovement VAR_0x8008, J_Common_Movement_FaceDown
	waitmovement 0
	msgbox J_Questionnaire_Text_ThankYou, MSGBOX_DEFAULT
	releaseall
	end

