@ Johto (data/scripts/pkmn_center_nurse.inc), as built into the FireRed game.

J_Common_EventScript_PkmnCenterNurse::
	lock
	faceplayer
	setvar VAR_0x8004, 0
	specialvar VAR_RESULT, IsPokecenterChallengeActivated
	goto_if_eq VAR_RESULT, TRUE, J_EventScript_PkmnCenterNurse_PkmnCenterChallenge_NoVisits
	specialvar VAR_RESULT, CountPlayerTrainerStars
	goto_if_eq VAR_RESULT, 4, J_EventScript_PkmnCenterNurse_GoldCard
	goto_if_set JOHTO_FLAG_EVEN_FASTER_JOY, J_EventScript_PkmnCenterNurse_HealPkmnFast
	msgbox J_gText_WouldYouLikeToRestYourPkmn, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, J_EventScript_PkmnCenterNurse_HealPkmn
	goto_if_eq VAR_RESULT, NO, J_EventScript_PkmnCenterNurse_Goodbye
	end

J_EventScript_PkmnCenterNurse_Goodbye::
	waitmessage
	applymovement VAR_0x800B, J_Movement_PkmnCenterNurse_Bow
	waitmovement 0
	message J_gText_WeHopeToSeeYouAgain
	goto J_EventScript_PkmnCenterNurse_PlayerTurn
	return

J_EventScript_PkmnCenterNurse_PkmnCenterChallenge_NoVisits::
	message J_gText_PkmnCenterChallenge_NoVisitsLeft
	waitmessage
	applymovement LOCALID_PLAYER, J_Common_Movement_FaceDown
	waitmovement 0
	release
	end

J_EventScript_PkmnCenterNurse_HealPkmn::
	incrementgamestat GAME_STAT_USED_POKECENTER
	call_if_eq VAR_0x8004, 0, J_EventScript_PkmnCenterNurse_IllTakeYourPkmn
	call_if_eq VAR_0x8004, 1, J_EventScript_PkmnCenterNurse_IllTakeYourPkmn2
	waitmessage
	call J_EventScript_PkmnCenterNurse_TakeAndHealPkmn

	goto_if_unset JOHTO_FLAG_POKERUS_EXPLAINED, J_EventScript_PkmnCenterNurse_CheckPokerus_Hns
	goto J_EventScript_PkmnCenterNurse_ReturnPkmn




	end

J_EventScript_PkmnCenterNurse_HealPkmnFast::
	incrementgamestat GAME_STAT_USED_POKECENTER
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
	applymovement VAR_0x800B, J_Movement_PkmnCenterNurse_Turn
	waitmovement 0
	dofieldeffect FLDEFF_POKECENTER_HEAL
	.if FALSE == FALSE && 0 != 0
	setflag OW_FLAG_MOVE_UNION_ROOM_CHECK
	call J_CableClub_OnResume
	clearflag OW_FLAG_MOVE_UNION_ROOM_CHECK
	.endif
	waitfieldeffect FLDEFF_POKECENTER_HEAL
	applymovement VAR_0x800B, J_Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	special HealPlayerParty
	return

J_EventScript_PkmnCenterNurse_CheckTrainerHillAndUnionRoom::
	specialvar VAR_RESULT, PlayerNotAtTrainerHillEntrance
	goto_if_eq VAR_RESULT, 0, J_EventScript_PkmnCenterNurse_ReturnPkmn
	specialvar VAR_RESULT, BufferUnionRoomPlayerName
	copyvar VAR_0x8008, VAR_RESULT
	goto_if_eq VAR_0x8008, 0, J_EventScript_PkmnCenterNurse_ReturnPkmn
	goto_if_eq VAR_0x8008, 1, J_EventScript_PkmnCenterNurse_PlayerWaitingInUnionRoom
	end

J_EventScript_PkmnCenterNurse_ReturnPkmn::
	goto_if_eq VAR_0x8004, 1, J_EventScript_PkmnCenterNurse_ReturnPkmn2
	message J_gText_RestoredPkmnToFullHealth
	waitmessage
	applymovement VAR_0x800B, J_Movement_PkmnCenterNurse_Bow
	waitmovement 0
	message J_gText_WeHopeToSeeYouAgain
	goto J_EventScript_PkmnCenterNurse_PlayerTurn
	return

J_EventScript_PkmnCenterNurse_ReturnPkmn2::
	message J_gText_ThankYouForWaiting
	waitmessage
	applymovement VAR_0x800B, J_Movement_PkmnCenterNurse_Bow
	waitmovement 0
	message J_gText_WeHopeToSeeYouAgain2
	goto J_EventScript_PkmnCenterNurse_PlayerTurn
	return

J_EventScript_PkmnCenterNurse_PlayerWaitingInUnionRoom::
	goto_if_set JOHTO_FLAG_NURSE_UNION_ROOM_REMINDER, J_EventScript_PkmnCenterNurse_ReturnPkmn
	msgbox J_gText_RestoredPkmnToFullHealth, MSGBOX_DEFAULT
	setflag JOHTO_FLAG_NURSE_UNION_ROOM_REMINDER
	message J_CableClub_Text_PlayerIsWaiting
	waitmessage
	applymovement VAR_0x800B, J_Movement_PkmnCenterNurse_Bow
	waitmovement 0
	message J_gText_WeHopeToSeeYouAgain
	goto J_EventScript_PkmnCenterNurse_PlayerTurn
	return

J_EventScript_PkmnCenterNurse_CheckPokerus_Hns::
	specialvar VAR_RESULT, IsPokerusInParty
	goto_if_eq VAR_RESULT, TRUE, J_EventScript_PkmnCenterNurse_ExplainPokerus
	goto J_EventScript_PkmnCenterNurse_ReturnPkmn
	end

J_EventScript_PkmnCenterNurse_CheckPokerus::
	specialvar VAR_RESULT, IsPokerusInParty
	goto_if_eq VAR_RESULT, TRUE, J_EventScript_PkmnCenterNurse_ExplainPokerus
	goto_if_eq VAR_RESULT, FALSE, J_EventScript_PkmnCenterNurse_CheckTrainerHillAndUnionRoom
	end

J_EventScript_PkmnCenterNurse_ExplainPokerus::
	message J_gText_PokerusExplanation
	setflag JOHTO_FLAG_POKERUS_EXPLAINED
	return

J_EventScript_PkmnCenterNurse_GoldCard::
	goto_if_set FLAG_NURSE_MENTIONS_GOLD_CARD, J_EventScript_PkmnCenterNurse_AskForUsual
	setflag FLAG_NURSE_MENTIONS_GOLD_CARD
	msgbox J_gText_WelcomeCutShort, MSGBOX_DEFAULT
	playse SE_PIN
	applymovement VAR_0x800B, J_Common_Movement_ExclamationMark
	waitmovement 0
	applymovement VAR_0x800B, J_Common_Movement_Delay48
	waitmovement 0
	msgbox J_gText_NoticesGoldCard, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, J_EventScript_PkmnCenterNurse_GoldCardHealPkmn
	waitmessage
	applymovement VAR_0x800B, J_Movement_PkmnCenterNurse_Bow
	waitmovement 0
	message J_gText_WeHopeToSeeYouAgain2
	goto J_EventScript_PkmnCenterNurse_PlayerTurn
	return

J_EventScript_PkmnCenterNurse_AskForUsual::
	msgbox J_gText_YouWantTheUsual, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, J_EventScript_PkmnCenterNurse_GoldCardHealPkmn
	waitmessage
	applymovement VAR_0x800B, J_Movement_PkmnCenterNurse_Bow
	waitmovement 0
	message J_gText_WeHopeToSeeYouAgain2
	goto J_EventScript_PkmnCenterNurse_PlayerTurn
	return

J_EventScript_PkmnCenterNurse_GoldCardHealPkmn::
	setvar VAR_0x8004, 1
	goto J_EventScript_PkmnCenterNurse_HealPkmn
	end

J_EventScript_PkmnCenterNurse_PlayerTurn::
	closemessage
	callnative UpdateFollowingPokemon
	applymovement OBJ_EVENT_ID_PLAYER, J_Common_Movement_FaceDown
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

