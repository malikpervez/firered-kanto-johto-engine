@ Johto (data/scripts/questionnaire.inc), as built into the FireRed game.

J_EventScript_Questionnaire::
	lockall
	msgbox J_Questionnaire_Text_FillOut, MSGBOX_YESNO
	goto_if_eq 32781, NO, J_Questionnaire_EventScript_Release
	setvar 32772, 20
	call J_Common_ShowEasyChatScreen
	lock
	faceplayer
	specialvar 32776, GetMartEmployeeObjectEventId
	goto_if_eq 32772, 1, J_Questionnaire_EventScript_PlayerInputMysteryEventPhrase
	goto_if_eq 32772, 2, J_Questionnaire_EventScript_PlayerInputMysteryGiftPhrase
	goto_if_eq 32781, 0, J_Questionnaire_EventScript_Release
	goto_if_eq 32781, 1, J_Questionnaire_EventScript_ThankYou
	end

J_Questionnaire_EventScript_PlayerInputMysteryEventPhrase::
	goto_if_unset 2089, J_Questionnaire_EventScript_ThankYou
	goto_if_set 10395, J_Questionnaire_EventScript_ThankYou
	applymovement 32776, J_Common_Movement_FaceDown
	waitmovement 0
	playse 21
	applymovement 32776, J_Common_Movement_ExclamationMark
	waitmovement 0
	applymovement 32776, J_Common_Movement_Delay48
	waitmovement 0
	msgbox J_Questionnaire_Text_YouKnowThoseWordsEvent, MSGBOX_DEFAULT
	setflag 10395
	msgbox J_Questionnaire_Text_YouCanAccessMysteryEvent, MSGBOX_DEFAULT
	releaseall
	end

J_Questionnaire_EventScript_PlayerInputMysteryGiftPhrase::
	goto_if_unset 2089, J_Questionnaire_EventScript_ThankYou
	goto_if_set 10395, J_Questionnaire_EventScript_ThankYou
	applymovement 32776, J_Common_Movement_FaceDown
	waitmovement 0
	playse 21
	applymovement 32776, J_Common_Movement_ExclamationMark
	waitmovement 0
	applymovement 32776, J_Common_Movement_Delay48
	waitmovement 0
	msgbox J_Questionnaire_Text_YouKnowThoseWordsGift, MSGBOX_DEFAULT
	setflag 10395
	msgbox J_Questionnaire_Text_YouCanAccessMysteryGift, MSGBOX_DEFAULT
	releaseall
	end

J_Questionnaire_EventScript_Release::
	releaseall
	end

J_Questionnaire_EventScript_ThankYou::
	applymovement 32776, J_Common_Movement_FaceDown
	waitmovement 0
	msgbox J_Questionnaire_Text_ThankYou, MSGBOX_DEFAULT
	releaseall
	end

