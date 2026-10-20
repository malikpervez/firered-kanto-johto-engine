@ Johto (data/scripts/pkmn_center_nurse.inc), as built into the FireRed game.

J_Common_EventScript_PkmnCenterNurse::
	lock
	faceplayer
	setvar 32772, 0
	specialvar 32781, IsPokecenterChallengeActivated
	goto_if_eq 32781, TRUE, J_EventScript_PkmnCenterNurse_PkmnCenterChallenge_NoVisits
	specialvar 32781, CountPlayerTrainerStars
	goto_if_eq 32781, 4, J_EventScript_PkmnCenterNurse_GoldCard
	goto_if_set 10592, J_EventScript_PkmnCenterNurse_HealPkmnFast
	msgbox J_gText_WouldYouLikeToRestYourPkmn, MSGBOX_YESNO
	goto_if_eq 32781, YES, J_EventScript_PkmnCenterNurse_HealPkmn
	goto_if_eq 32781, NO, J_EventScript_PkmnCenterNurse_Goodbye
	end

J_EventScript_PkmnCenterNurse_Goodbye::
	waitmessage
	applymovement 32779, J_Movement_PkmnCenterNurse_Bow
	waitmovement 0
	message J_gText_WeHopeToSeeYouAgain
	goto J_EventScript_PkmnCenterNurse_PlayerTurn
	return

J_EventScript_PkmnCenterNurse_PkmnCenterChallenge_NoVisits::
	message J_gText_PkmnCenterChallenge_NoVisitsLeft
	waitmessage
	applymovement 255, J_Common_Movement_FaceDown
	waitmovement 0
	release
	end

J_EventScript_PkmnCenterNurse_HealPkmn::
	incrementgamestat 15
	call_if_eq 32772, 0, J_EventScript_PkmnCenterNurse_IllTakeYourPkmn
	call_if_eq 32772, 1, J_EventScript_PkmnCenterNurse_IllTakeYourPkmn2
	waitmessage
	call J_EventScript_PkmnCenterNurse_TakeAndHealPkmn

	goto_if_unset 8937, J_EventScript_PkmnCenterNurse_CheckPokerus_Hns
	goto J_EventScript_PkmnCenterNurse_ReturnPkmn




	end

J_EventScript_PkmnCenterNurse_HealPkmnFast::
	incrementgamestat 15
	special HealPlayerParty


	playse (((((((558 + 1) + 0xAF) + 1) + 0x0A) + 1) + 50) + 1)
	goto J_EventScript_PkmnCenterNurse_ReturnPkmn
	end

J_EventScript_PkmnCenterNurse_IllTakeYourPkmn::
	message J_gText_IllTakeYourPkmn
	return

J_EventScript_PkmnCenterNurse_IllTakeYourPkmn2::
	message J_gText_IllTakeYourPkmn2
	return

J_EventScript_PkmnCenterNurse_TakeAndHealPkmn::
	hidefollower 0
	applymovement 32779, J_Movement_PkmnCenterNurse_Turn
	waitmovement 0
	dofieldeffect 25
	.if FALSE == FALSE && 0 != 0
	setflag 0
	call J_CableClub_OnResume
	clearflag 0
	.endif
	waitfieldeffect 25
	applymovement 32779, J_Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	special HealPlayerParty
	return

J_EventScript_PkmnCenterNurse_CheckTrainerHillAndUnionRoom::
	specialvar 32781, PlayerNotAtTrainerHillEntrance
	goto_if_eq 32781, 0, J_EventScript_PkmnCenterNurse_ReturnPkmn
	specialvar 32781, BufferUnionRoomPlayerName
	copyvar 32776, 32781
	goto_if_eq 32776, 0, J_EventScript_PkmnCenterNurse_ReturnPkmn
	goto_if_eq 32776, 1, J_EventScript_PkmnCenterNurse_PlayerWaitingInUnionRoom
	end

J_EventScript_PkmnCenterNurse_ReturnPkmn::
	goto_if_eq 32772, 1, J_EventScript_PkmnCenterNurse_ReturnPkmn2
	message J_gText_RestoredPkmnToFullHealth
	waitmessage
	applymovement 32779, J_Movement_PkmnCenterNurse_Bow
	waitmovement 0
	message J_gText_WeHopeToSeeYouAgain
	goto J_EventScript_PkmnCenterNurse_PlayerTurn
	return

J_EventScript_PkmnCenterNurse_ReturnPkmn2::
	message J_gText_ThankYouForWaiting
	waitmessage
	applymovement 32779, J_Movement_PkmnCenterNurse_Bow
	waitmovement 0
	message J_gText_WeHopeToSeeYouAgain2
	goto J_EventScript_PkmnCenterNurse_PlayerTurn
	return

J_EventScript_PkmnCenterNurse_PlayerWaitingInUnionRoom::
	goto_if_set 10398, J_EventScript_PkmnCenterNurse_ReturnPkmn
	msgbox J_gText_RestoredPkmnToFullHealth, MSGBOX_DEFAULT
	setflag 10398
	message J_CableClub_Text_PlayerIsWaiting
	waitmessage
	applymovement 32779, J_Movement_PkmnCenterNurse_Bow
	waitmovement 0
	message J_gText_WeHopeToSeeYouAgain
	goto J_EventScript_PkmnCenterNurse_PlayerTurn
	return

J_EventScript_PkmnCenterNurse_CheckPokerus_Hns::
	specialvar 32781, IsPokerusInParty
	goto_if_eq 32781, TRUE, J_EventScript_PkmnCenterNurse_ExplainPokerus
	goto J_EventScript_PkmnCenterNurse_ReturnPkmn
	end

J_EventScript_PkmnCenterNurse_CheckPokerus::
	specialvar 32781, IsPokerusInParty
	goto_if_eq 32781, TRUE, J_EventScript_PkmnCenterNurse_ExplainPokerus
	goto_if_eq 32781, FALSE, J_EventScript_PkmnCenterNurse_CheckTrainerHillAndUnionRoom
	end

J_EventScript_PkmnCenterNurse_ExplainPokerus::
	message J_gText_PokerusExplanation
	setflag 8937
	return

J_EventScript_PkmnCenterNurse_GoldCard::
	goto_if_set 0, J_EventScript_PkmnCenterNurse_AskForUsual
	setflag 0
	msgbox J_gText_WelcomeCutShort, MSGBOX_DEFAULT
	playse 21
	applymovement 32779, J_Common_Movement_ExclamationMark
	waitmovement 0
	applymovement 32779, J_Common_Movement_Delay48
	waitmovement 0
	msgbox J_gText_NoticesGoldCard, MSGBOX_YESNO
	goto_if_eq 32781, YES, J_EventScript_PkmnCenterNurse_GoldCardHealPkmn
	waitmessage
	applymovement 32779, J_Movement_PkmnCenterNurse_Bow
	waitmovement 0
	message J_gText_WeHopeToSeeYouAgain2
	goto J_EventScript_PkmnCenterNurse_PlayerTurn
	return

J_EventScript_PkmnCenterNurse_AskForUsual::
	msgbox J_gText_YouWantTheUsual, MSGBOX_YESNO
	goto_if_eq 32781, YES, J_EventScript_PkmnCenterNurse_GoldCardHealPkmn
	waitmessage
	applymovement 32779, J_Movement_PkmnCenterNurse_Bow
	waitmovement 0
	message J_gText_WeHopeToSeeYouAgain2
	goto J_EventScript_PkmnCenterNurse_PlayerTurn
	return

J_EventScript_PkmnCenterNurse_GoldCardHealPkmn::
	setvar 32772, 1
	goto J_EventScript_PkmnCenterNurse_HealPkmn
	end

J_EventScript_PkmnCenterNurse_PlayerTurn::
	closemessage
	callnative UpdateFollowingPokemon
	applymovement 255, J_Common_Movement_FaceDown
	waitmovement 0
	release
	end

J_Movement_PkmnCenterNurse_Bow:
	nurse_joy_bow
	delay_4
	step_end

J_Movement_PkmnCenterNurse_Turn:
	walk_in_place_faster_left
	step_end

	.set ITEMID, 32768
	.set AMOUNT, 32769

