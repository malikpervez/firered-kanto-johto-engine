@ Johto (data/maps/NewBarkTown_PlayersHouse_1F_hns/scripts.inc), as built into the FireRed game.

NewBarkTown_PlayersHouse_1F_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, NewBarkTown_PlayersHouse_1F_OnTransition
	.byte 0

NewBarkTown_PlayersHouse_1F_OnTransition::
	call_if_eq JOHTO_VAR_NEWBARK_TOWN_STATE, 1, NewBarkTown_PlayersHouse_1F_SetMomStandingAtTable
	call_if_eq JOHTO_VAR_NEWBARK_TOWN_STATE, 2, NewBarkTown_PlayersHouse_1F_SetMomStandingAtTable
	call_if_eq JOHTO_VAR_NEWBARK_TOWN_STATE, 3, NewBarkTown_PlayersHouse_1F_SetMomStandingAtTable
	end

NewBarkTown_PlayersHouse_1F_SetMomStandingAtTable::
	setobjectxyperm LOCALID_MOM, 8, 4
	setobjectmovementtype LOCALID_MOM, MOVEMENT_TYPE_FACE_LEFT


	clearflag JOHTO_FLAG_HIDE_MOMS_FRIEND
	clearflag JOHTO_FLAG_MOM_VISITED
	return

NewBarkTown_PlayersHouse_1F_EventScript_Mom::
	lock
	faceplayer
	call_if_unset JOHTO_FLAG_RECEIVED_POKENAV, NewBarkTown_PlayersHouse_1F_EventScript_GivePokeGear
	goto_if_set JOHTO_FLAG_MOM_VISITED, NewBarkTown_PlayersHouse_1F_EventScript_Mom_Regular
	goto_if_set JOHTO_FLAG_ADVENTURE_STARTED, NewBarkTown_PlayersHouse_1F_MomEventScript_GoodLuck
	msgbox NewBarkTown_PlayersHouse_1F_Text_MomHurryUpElmIsWaiting, MSGBOX_DEFAULT
	applymovement LOCALID_MOM, NewBarkTown_PlayersHouse_1F_MovementFaceLeft
	waitmovement 0
	release
	end

NewBarkTown_PlayersHouse_1F_EventScript_MomsFriend::
	lock
	faceplayer
	msgbox NewBarkTown_PlayersHouse_1F_Text_MomsFriend, MSGBOX_DEFAULT
	applymovement LOCALID_MOMS_FRIEND, NewBarkTown_PlayersHouse_1F_MovementFaceRight
	waitmovement 0
	release
	end

NewBarkTown_PlayersHouse_1F_MomEventScript_GoodLuck::
	playbgm ((558 + 1) + 0x39), FALSE
	msgbox NewBarkTown_PlayersHouse_1F_Text_MomLeaving, MSGBOX_DEFAULT
	setflag JOHTO_FLAG_MOM_VISITED
	clearflag JOHTO_FLAG_HIDE_ROUTE_30_NPCS
	setvar JOHTO_VAR_NEWBARK_TOWN_STATE, 5
	fadedefaultbgm
	release
	end

NewBarkTown_PlayersHouse_1F_EventScript_Mom_Regular::
	playbgm ((558 + 1) + 0x39), FALSE
	specialvar VAR_RESULT, IsPokecenterChallengeActivated
	goto_if_eq VAR_RESULT, TRUE, NewBarkTown_PlayersHouse_1F_EventScript_Mom_PokecenterChallenge
	msgbox NewBarkTown_PlayersHouse_1F_Text_GuestRest, MSGBOX_DEFAULT
	closemessage
	call J_Common_EventScript_OutOfCenterPartyHeal
	incrementgamestat GAME_STAT_RESTED_AT_HOME
	call NewBarkTown_PlayersHouse_1F_EventScript_MomSavingsMenu
	fadedefaultbgm
	release
	end

NewBarkTown_PlayersHouse_1F_EventScript_Mom_PokecenterChallenge::
	msgbox NewBarkTown_PlayersHouse_1F_Text_GuestRestChallenge, MSGBOX_DEFAULT
	call NewBarkTown_PlayersHouse_1F_EventScript_MomSavingsMenu
	fadedefaultbgm
	release
	end

NewBarkTown_PlayersHouse_1F_EventScript_MomSavingsMenu::
	special Special_MomEnsureInitialized
	msgbox NewBarkTown_PlayersHouse_1F_Text_MomAnythingElse, MSGBOX_DEFAULT
	multichoice 0, 0, MULTI_MOM_MENU, FALSE
	switch VAR_RESULT
	case 0, NewBarkTown_PlayersHouse_1F_EventScript_CheckSavings
	case 1, NewBarkTown_PlayersHouse_1F_EventScript_Deposit
	case 2, NewBarkTown_PlayersHouse_1F_EventScript_Withdraw
	case 3, NewBarkTown_PlayersHouse_1F_EventScript_ToggleSaving
	case 4, NewBarkTown_PlayersHouse_1F_EventScript_ExitSavings
	case MULTI_B_PRESSED, NewBarkTown_PlayersHouse_1F_EventScript_ExitSavings
	end

NewBarkTown_PlayersHouse_1F_EventScript_CheckSavings::
	special Special_MomGetBalance
	msgbox NewBarkTown_PlayersHouse_1F_Text_CurrentSavings, MSGBOX_DEFAULT
	goto NewBarkTown_PlayersHouse_1F_EventScript_MomSavingsMenu
	end

NewBarkTown_PlayersHouse_1F_EventScript_Deposit::
	checkmoney 1
	compare VAR_RESULT, FALSE
	goto_if_eq NewBarkTown_PlayersHouse_1F_EventScript_DepositFailed
	closemessage
	special Special_MomOpenDepositInput
	waitstate
	compare VAR_0x8000, 0
	goto_if_eq NewBarkTown_PlayersHouse_1F_EventScript_MomSavingsMenu
	msgbox NewBarkTown_PlayersHouse_1F_Text_DepositSuccess, MSGBOX_DEFAULT
	goto NewBarkTown_PlayersHouse_1F_EventScript_MomSavingsMenu
	end

NewBarkTown_PlayersHouse_1F_EventScript_DepositFailed::
	msgbox NewBarkTown_PlayersHouse_1F_Text_NoMoneyToDeposit, MSGBOX_DEFAULT
	goto NewBarkTown_PlayersHouse_1F_EventScript_MomSavingsMenu
	end

NewBarkTown_PlayersHouse_1F_EventScript_Withdraw::
	special Special_MomGetBalance
	compare VAR_RESULT, 0
	goto_if_eq NewBarkTown_PlayersHouse_1F_EventScript_WithdrawFailed
	closemessage
	special Special_MomOpenWithdrawInput
	waitstate
	compare VAR_0x8000, 0
	goto_if_eq NewBarkTown_PlayersHouse_1F_EventScript_MomSavingsMenu
	msgbox NewBarkTown_PlayersHouse_1F_Text_WithdrawSuccess, MSGBOX_DEFAULT
	goto NewBarkTown_PlayersHouse_1F_EventScript_MomSavingsMenu
	end

NewBarkTown_PlayersHouse_1F_EventScript_WithdrawFailed::
	msgbox NewBarkTown_PlayersHouse_1F_Text_NoMoneyToWithdraw, MSGBOX_DEFAULT
	goto NewBarkTown_PlayersHouse_1F_EventScript_MomSavingsMenu
	end

NewBarkTown_PlayersHouse_1F_EventScript_ToggleSaving::
	special Special_MomIsSavingEnabled
	compare VAR_RESULT, TRUE
	goto_if_eq NewBarkTown_PlayersHouse_1F_EventScript_DisableSaving
	msgbox NewBarkTown_PlayersHouse_1F_Text_EnableSaving, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq NewBarkTown_PlayersHouse_1F_EventScript_ConfirmEnable
	goto NewBarkTown_PlayersHouse_1F_EventScript_MomSavingsMenu
	end

NewBarkTown_PlayersHouse_1F_EventScript_ConfirmEnable::
	special Special_MomEnableSaving
	msgbox NewBarkTown_PlayersHouse_1F_Text_SavingEnabled, MSGBOX_DEFAULT
	goto NewBarkTown_PlayersHouse_1F_EventScript_MomSavingsMenu
	end

NewBarkTown_PlayersHouse_1F_EventScript_DisableSaving::
	msgbox NewBarkTown_PlayersHouse_1F_Text_DisableSaving, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq NewBarkTown_PlayersHouse_1F_EventScript_ConfirmDisable
	goto NewBarkTown_PlayersHouse_1F_EventScript_MomSavingsMenu
	end

NewBarkTown_PlayersHouse_1F_EventScript_ConfirmDisable::
	special Special_MomDisableSaving
	msgbox NewBarkTown_PlayersHouse_1F_Text_SavingDisabled, MSGBOX_DEFAULT
	goto NewBarkTown_PlayersHouse_1F_EventScript_MomSavingsMenu
	end

NewBarkTown_PlayersHouse_1F_EventScript_ExitSavings::
	msgbox NewBarkTown_PlayersHouse_1F_Text_Goodbye, MSGBOX_DEFAULT
	return

NewBarkTown_PlayersHouse_1F_Text_MomAnythingElse:
	.string "Is there anything else I can\n"
	.string "help you with, sweetie?$"

NewBarkTown_PlayersHouse_1F_Text_CurrentSavings:
	.string "I'm holding {STR_VAR_2}\n"
	.string "for you right now.$"

NewBarkTown_PlayersHouse_1F_Text_EnableSaving:
	.string "Do you want me to save some of the\n"
	.string "money you earn?$"

NewBarkTown_PlayersHouse_1F_Text_SavingEnabled:
	.string "Okay! I'll save 25% of\n"
	.string "the money you earn from battles.$"

NewBarkTown_PlayersHouse_1F_Text_DisableSaving:
	.string "Would you like me to stop\n"
	.string "saving for you?$"

NewBarkTown_PlayersHouse_1F_Text_SavingDisabled:
	.string "Okay, I'll stop saving for now.$"

NewBarkTown_PlayersHouse_1F_Text_Goodbye:
	.string "Take care, sweetie!$"

NewBarkTown_PlayersHouse_1F_Text_DepositSuccess:
	.string "HOST: Sounds good! I'll put that in\n"
	.string "savings for you.$"

NewBarkTown_PlayersHouse_1F_Text_WithdrawSuccess:
	.string "HOST: Here you go!$"

NewBarkTown_PlayersHouse_1F_Text_NoMoneyToDeposit:
	.string "HOST: You don't have any money to\n"
	.string "deposit right now, sweetie.$"

NewBarkTown_PlayersHouse_1F_Text_NoMoneyToWithdraw:
	.string "HOST: I haven't saved any money\n"
	.string "for you yet, honey.$"

NewBarkTown_PlayersHouse_1F_EventScript_MomsIntroTrigger1::
	lock
	applymovement OBJ_EVENT_ID_PLAYER, NewBarkTown_PlayersHouse_1F_PlayerIntroMovement1
	waitmovement 0
	goto NewBarkTown_PlayersHouse_1F_EventScript_MomsIntro
	end

NewBarkTown_PlayersHouse_1F_EventScript_MomsIntroTrigger2::
	lock
	applymovement OBJ_EVENT_ID_PLAYER, NewBarkTown_PlayersHouse_1F_PlayerIntroMovement2
	waitmovement 0
	goto NewBarkTown_PlayersHouse_1F_EventScript_MomsIntro
	end

NewBarkTown_PlayersHouse_1F_EventScript_MomsIntro::
	playbgm ((558 + 1) + 0x39), FALSE
	playse SE_PIN
	applymovement LOCALID_MOM, J_Common_Movement_ExclamationMark
	delay 55
	waitmovement LOCALID_MOM
	applymovement LOCALID_MOM, NewBarkTown_PlayersHouse_1F_MomMovement_1
	waitmovement 0
	msgbox NewBarkTown_PlayersHouse_1F_Text_ElmsLookingForYou, MSGBOX_DEFAULT
	call NewBarkTown_PlayersHouse_1F_EventScript_GivePokeGear
	applymovement LOCALID_MOM, NewBarkTown_PlayersHouse_1F_MomMovement_2
	waitmovement 0
	setflag JOHTO_FLAG_HIDE_LAB_POLICEMAN
	setflag JOHTO_FLAG_VISITED_NEWBARK_TOWN



	fadedefaultbgm
	releaseall
	end

NewBarkTown_PlayersHouse_1F_EventScript_GivePokeGear::
	playfanfare MUS_REGISTER_MATCH_CALL
	message NewBarkTown_PlayersHouse_1F_Text_ObtainedPokeGear
	waitfanfare
	setflag JOHTO_FLAG_SYS_POKENAV_GET
	setflag JOHTO_FLAG_HAS_MATCH_CALL
	setflag JOHTO_FLAG_RECEIVED_POKENAV
	setflag JOHTO_FLAG_ADDED_MATCH_CALL_TO_POKENAV
	setflag JOHTO_FLAG_REGISTER_RIVAL_POKENAV
	msgbox NewBarkTown_PlayersHouse_1F_Text_ExplainPokeGear, MSGBOX_DEFAULT
	closemessage
	delay 30
	return

NewBarkTown_PlayersHouse_1F_PlayerIntroMovement1:
	delay_8
	walk_down
	walk_right
	walk_down
	face_left
	delay_8
	step_end

NewBarkTown_PlayersHouse_1F_PlayerIntroMovement2:
	delay_8
	walk_down
	face_left
	delay_8
	step_end

NewBarkTown_PlayersHouse_1F_MomMovement_1:
	face_right
	walk_right
	step_end

NewBarkTown_PlayersHouse_1F_MomMovement_2:
	face_left
	walk_left
	delay_8
	step_end

NewBarkTown_PlayersHouse_1F_MovementFaceRight:
	face_right
	step_end

NewBarkTown_PlayersHouse_1F_MovementFaceLeft:
	face_left
	step_end

NewBarkTown_PlayersHouse_1F_Text_ElmsLookingForYou::
	.string "Welcome, {PLAYER}! PROF.ELM told\n"
	.string "me about his guest from KANTO.\p"
	.string "He is looking for help with his\n"
	.string "POKéMON research.\p"
	.string "Here is a POKéGEAR to help you\n"
	.string "keep in touch while you're here.$"

NewBarkTown_PlayersHouse_1F_Text_ObtainedPokeGear:
	.string "{PLAYER} obtained the POKéGEAR.$"

NewBarkTown_PlayersHouse_1F_Text_ExplainPokeGear::
	.string "Phone numbers are stored in the\n"
	.string "POKéGEAR's memory.\p"
	.string "Choose a name when you want to\n"
	.string "call. The guest house number is\l"
	.string "registered if you need help.$"

NewBarkTown_PlayersHouse_1F_Text_MomHurryUpElmIsWaiting::
	.string "PROF.ELM is waiting in his lab.\p"
	.string "I'm glad a trainer from KANTO\n"
	.string "has come to help him.$"

NewBarkTown_PlayersHouse_1F_Text_MomsFriend::
	.string "Hi, {PLAYER}! You're PROF.ELM's\n"
	.string "guest from KANTO, aren't you?\p"
	.string "My daughter hopes to become his\n"
	.string "assistant. She loves POKéMON!$"

NewBarkTown_PlayersHouse_1F_Text_MomLeaving::
	.string "You're ready to explore JOHTO?\n"
	.string "Your POKéMON look eager, too!\p"
	.string "I can help look after some of your\n"
	.string "battle winnings if you'd like.\p"
	.string "It is your choice. Come back any\n"
	.string "time to manage your savings.\p"
	.string "Call on your POKéGEAR if you need\n"
	.string "anything. Take care, {PLAYER}!$"

NewBarkTown_PlayersHouse_1F_Text_GuestRest::
	.string "Your team must be tired.\n"
	.string "Please rest here for a while.$"

NewBarkTown_PlayersHouse_1F_Text_GuestRestChallenge::
	.string "Your challenge rules do not allow\n"
	.string "healing here, but I can still help\l"
	.string "with your savings.$"

