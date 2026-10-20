@ Johto (data/scripts/players_house.inc), as built into the FireRed game.

J_PlayersHouse_2F_EventScript_BlockStairsUntilClockIsSet::
	setvar 20610, 5
	return

J_PlayersHouse_1F_EventScript_EnterHouseMovingIn::
	msgbox J_PlayersHouse_1F_Text_IsntItNiceInHere, MSGBOX_DEFAULT
	applymovement 32772, J_Common_Movement_FacePlayer
	waitmovement 0
	call_if_eq 32773, MALE, J_PlayersHouse_1F_EventScript_MomFacePlayerMovingInMale
	call_if_eq 32773, FEMALE, J_PlayersHouse_1F_EventScript_MomFacePlayerMovingInFemale
	msgbox J_PlayersHouse_1F_Text_MoversPokemonGoSetClock, MSGBOX_DEFAULT
	closemessage
	setvar 20610, 4
	applymovement 255, J_PlayersHouse_1F_Movement_PlayerWalkIn
	applymovement 32772, J_Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	releaseall
	end

J_PlayersHouse_1F_EventScript_MomFacePlayerMovingInMale::
	applymovement 255, J_Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	return

J_PlayersHouse_1F_EventScript_MomFacePlayerMovingInFemale::
	applymovement 255, J_Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	return

J_PlayersHouse_1F_Movement_PlayerWalkIn:
	walk_up
	step_end

J_PlayersHouse_1F_EventScript_MomGoSeeRoom::
	msgbox J_PlayersHouse_1F_Text_ArentYouInterestedInRoom, MSGBOX_DEFAULT
	closemessage
	applymovement 32772, J_Common_Movement_WalkInPlaceFasterUp
	applymovement 255, J_PlayersHouse_1F_Movement_MovePlayerAwayFromDoor
	waitmovement 0
	releaseall
	end

J_LittlerootTown_BrendansHouse_2F_EventScript_WallClock::
	lockall
	setvar 32772, MALE
	goto_if_unset 8807, J_PlayersHouse_2F_EventScript_WallClock
	msgbox J_PlayersHouse_2F_Text_ClockChange, MSGBOX_DEFAULT
	goto J_PlayersHouse_2F_EventScript_WallClock
	end

J_LittlerootTown_MaysHouse_2F_EventScript_WallClock::
	lockall
	setvar 32772, FEMALE
	goto_if_unset 8807, J_PlayersHouse_2F_EventScript_WallClock
	msgbox J_PlayersHouse_2F_Text_ClockChange, MSGBOX_DEFAULT
	goto J_PlayersHouse_2F_EventScript_WallClock
	end

J_PlayersHouse_2F_Text_ClockChange:
	.string "Pres{SE_M_GRASSWHISTLE}th{SE_M_REVERSAL}{SE_M_MINIMIZE}Butto{SE_M_ATTRACT}t{SE_M_ATTRACT2}se{SE_M_SPIT_UP}the\n"
	.string "cloc{SE_M_ENCORE2}whe{SE_M_ATTRACT}lookin{SE_M_SANDSTORM}a{SE_M_SPIT_UP}th{SE_M_REVERSAL}time.$"

J_PlayersHouse_2F_EventScript_WallClock::
	goto_if_set 8807, J_PlayersHouse_2F_EventScript_CheckWallClock
	msgbox J_PlayersHouse_2F_Text_ClockIsStopped, MSGBOX_DEFAULT
	call J_PlayersHouse_2F_EventScript_SetWallClock
	delay 30
	setvar 20610, 6
	setflag 8807
	setflag 0
	setflag 0
	checkplayergender
	call_if_eq 32781, MALE, J_PlayersHouse_2F_EventScript_MomComesUpstairsMale
	call_if_eq 32781, FEMALE, J_PlayersHouse_2F_EventScript_MomComesUpstairsFemale
	playse 9
	removeobject 32776
	releaseall
	end

J_PlayersHouse_2F_EventScript_MomComesUpstairsMale::
	setvar 32776, 14
	addobject 32776
	applymovement 32776, J_PlayersHouse_2F_Movement_MomEntersMale
	waitmovement 0
	applymovement 255, J_Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	msgbox J_PlayersHouse_2F_Text_HowDoYouLikeYourRoom, MSGBOX_DEFAULT
	closemessage
	applymovement 32776, J_PlayersHouse_2F_Movement_MomExitsMale
	waitmovement 0
	return

J_PlayersHouse_2F_EventScript_MomComesUpstairsFemale::
	setvar 32776, 14
	addobject 32776
	applymovement 32776, J_PlayersHouse_2F_Movement_MomEntersFemale
	waitmovement 0
	applymovement 255, J_Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	msgbox J_PlayersHouse_2F_Text_HowDoYouLikeYourRoom, MSGBOX_DEFAULT
	closemessage
	applymovement 32776, J_PlayersHouse_2F_Movement_MomExitsFemale
	waitmovement 0
	return

J_PlayersHouse_2F_EventScript_CheckWallClock::
	incrementgamestat 45
	fadescreen 1
	special Special_ViewWallClock
	waitstate
	releaseall
	end

J_PlayersHouse_2F_EventScript_SetWallClock::
	fadescreen 1
	special StartWallClock
	waitstate
	return

J_PlayersHouse_2F_Movement_MomEntersMale:
	delay_8
	walk_down
	walk_in_place_faster_left
	delay_16
	delay_8
	walk_left
	step_end

J_PlayersHouse_2F_Movement_MomExitsMale:
	walk_right
	walk_up
	delay_8
	step_end

J_PlayersHouse_2F_Movement_MomEntersFemale:
	delay_8
	walk_down
	walk_in_place_faster_right
	delay_16
	delay_8
	walk_right
	step_end

J_PlayersHouse_2F_Movement_MomExitsFemale:
	walk_left
	walk_up
	delay_8
	step_end

J_PlayersHouse_1F_EventScript_SetWatchedBroadcast::
	setvar 20610, 7
	releaseall
	end

J_PlayersHouse_1F_EventScript_PetalburgGymReportMale::
	applymovement 32773, J_Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	call J_PlayersHouse_1F_EventScript_MomNoticeGymBroadcast
	applymovement 255, J_PlayersHouse_1F_Movement_PlayerApproachTVForGymMale
	waitmovement 0
	playbgm 453, FALSE
	msgbox J_PlayersHouse_1F_Text_MaybeDadWillBeOn, MSGBOX_DEFAULT
	closemessage
	applymovement 32773, J_PlayersHouse_1F_Movement_MomMakeRoomToSeeTVMale
	waitmovement 0
	applymovement 255, J_PlayersHouse_1F_Movement_PlayerMoveToTVMale
	waitmovement 0
	call J_PlayersHouse_1F_EventScript_WatchGymBroadcast
	applymovement 255, J_Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	msgbox J_PlayersHouse_1F_Text_ItsOverWeMissedHim, MSGBOX_DEFAULT
	msgbox J_PlayersHouse_1F_Text_GoIntroduceYourselfNextDoor, MSGBOX_DEFAULT
	closemessage
	setvar 16385, 1
	applymovement 32773, J_PlayersHouse_1F_Movement_MomReturnToSeatMale
	waitmovement 0
	goto J_PlayersHouse_1F_EventScript_SetWatchedBroadcast
	end

J_PlayersHouse_1F_EventScript_PetalburgGymReportFemale::
	applymovement 32773, J_Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	call J_PlayersHouse_1F_EventScript_MomNoticeGymBroadcast
	applymovement 255, J_PlayersHouse_1F_Movement_PlayerApproachTVForGymFemale
	waitmovement 0
	playbgm 453, FALSE
	msgbox J_PlayersHouse_1F_Text_MaybeDadWillBeOn, MSGBOX_DEFAULT
	closemessage
	applymovement 32773, J_PlayersHouse_1F_Movement_MomMakeRoomToSeeTVFemale
	waitmovement 0
	applymovement 255, J_PlayersHouse_1F_Movement_PlayerMoveToTVFemale
	waitmovement 0
	call J_PlayersHouse_1F_EventScript_WatchGymBroadcast
	applymovement 255, J_Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	msgbox J_PlayersHouse_1F_Text_ItsOverWeMissedHim, MSGBOX_DEFAULT
	msgbox J_PlayersHouse_1F_Text_GoIntroduceYourselfNextDoor, MSGBOX_DEFAULT
	closemessage
	setvar 16385, 1
	applymovement 32773, J_PlayersHouse_1F_Movement_MomReturnToSeatFemale
	waitmovement 0
	goto J_PlayersHouse_1F_EventScript_SetWatchedBroadcast
	end

J_PlayersHouse_1F_EventScript_MomNoticeGymBroadcast::
	playse 21
	applymovement 32773, J_Common_Movement_ExclamationMark
	waitmovement 0
	applymovement 32773, J_Common_Movement_Delay48
	waitmovement 0
	msgbox J_PlayersHouse_1F_Text_OhComeQuickly, MSGBOX_DEFAULT
	closemessage
	return

J_PlayersHouse_1F_EventScript_WatchGymBroadcast::
	applymovement 255, J_Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	msgbox J_PlayersHouse_1F_Text_ReportFromPetalburgGym, MSGBOX_DEFAULT
	fadedefaultbgm
	special TurnOffTVScreen
	setflag 0
	delay 35
	return

J_PlayersHouse_1F_Movement_MomApproachDadMale:
	walk_up
	walk_right
	walk_right
	walk_right
	walk_right
	walk_down
	walk_in_place_faster_right
	step_end

J_PlayersHouse_1F_Movement_MomApproachDadFemale:
	walk_up
	walk_left
	walk_left
	walk_left
	walk_left
	walk_down
	walk_in_place_faster_left
	step_end

J_PlayersHouse_1F_Movement_MomApproachPlayerMale:
	walk_right
	step_end

J_PlayersHouse_1F_Movement_MomApproachPlayerFemale:
	walk_left
	step_end

J_PlayersHouse_1F_Movement_MomNoticesLatiBroadcastMale:
	walk_in_place_faster_left
	delay_16
	delay_16
	delay_16
	delay_16
	walk_in_place_faster_right
	delay_16
	delay_16
	step_end

J_PlayersHouse_1F_Movement_MomNoticesLatiBroadcastFemale:
	walk_in_place_faster_right
	delay_16
	delay_16
	delay_16
	delay_16
	walk_in_place_faster_left
	delay_16
	delay_16
	step_end

J_PlayersHouse_1F_Movement_MomApproachPlayerAfterTVMale:
	walk_up
	walk_left
	walk_left
	step_end

J_PlayersHouse_1F_Movement_MomApproachPlayerAfterTVFemale:
	walk_up
	walk_right
	walk_right
	step_end

J_PlayersHouse_1F_Movement_MomMakeRoomToSeeTVMale:
	walk_left
	walk_in_place_faster_right
	step_end

J_PlayersHouse_1F_Movement_MomMakeRoomToSeeTVFemale:
	walk_right
	walk_in_place_faster_left
	step_end

J_PlayersHouse_1F_Movement_MomReturnToSeatMale:
	walk_left
	walk_down
	walk_in_place_faster_right
	step_end

J_PlayersHouse_1F_Movement_MomReturnToSeatFemale:
	walk_right
	walk_down
	walk_in_place_faster_left
	step_end

J_PlayersHouse_1F_EventScript_Mom::
	lock
	faceplayer
	goto_if_eq 20594, 4, J_PlayersHouse_1F_EventScript_DontPushYourselfTooHard
	goto_if_eq 20604, 4, J_PlayersHouse_1F_EventScript_DontPushYourselfTooHard
	goto_if_set 8691, J_PlayersHouse_1F_EventScript_TryRegisterMom
	goto_if_set 0, J_PlayersHouse_1F_EventScript_MomHealsParty
	goto_if_eq 16385, 1, J_PlayersHouse_1F_EventScript_SeeYouHoney
	goto_if_eq 20610, 7, J_PlayersHouse_1F_EventScript_DidYouMeetProfBirch
	msgbox J_PlayersHouse_1F_Text_IsntItNiceInHere, MSGBOX_DEFAULT
	release
	end

J_PlayersHouse_1F_EventScript_DontPushYourselfTooHard::
	msgbox J_PlayersHouse_1F_Text_DontPushYourselfTooHard, MSGBOX_DEFAULT
	release
	end

J_PlayersHouse_1F_EventScript_TryRegisterMom::
	goto_if_set 0, J_PlayersHouse_1F_EventScript_CheckGiveAmuletCoin
	msgbox J_PlayersHouse_1F_Text_IsThatAPokenav, MSGBOX_DEFAULT
	closemessage
	delay 30
	playfanfare 460
	msgbox J_PlayersHouse_1F_Text_RegisteredMom, MSGBOX_DEFAULT
	waitfanfare
	closemessage
	delay 30
	setflag 0
	release
	end

J_PlayersHouse_1F_EventScript_CheckGiveAmuletCoin::
	goto_if_set 10372, J_PlayersHouse_1F_EventScript_TryGiveAmuletCoin
	goto J_PlayersHouse_1F_EventScript_MomHealsParty

J_PlayersHouse_1F_EventScript_TryGiveAmuletCoin::
	goto_if_set 0, J_PlayersHouse_1F_EventScript_MomHealsParty
	msgbox J_PlayersHouse_1F_Text_GotDadsBadgeHeresSomethingFromMom, MSGBOX_DEFAULT
	giveitem ITEM_AMULET_COIN
	goto_if_eq 32781, FALSE, J_Common_EventScript_ShowBagIsFull
	msgbox J_PlayersHouse_1F_Text_DontPushYourselfTooHard, MSGBOX_DEFAULT
	setflag 0
	release
	end

J_PlayersHouse_1F_EventScript_MomHealsParty::
	specialvar 32781, IsPokecenterChallengeActivated
	goto_if_eq 32781, TRUE, J_PlayersHouse_1F_EventScript_MomHealsParty_PokecenterChallenge
	msgbox J_PlayersHouse_1F_Text_YouShouldRestABit, MSGBOX_DEFAULT
	goto J_PlayersHouse_1F_EventScript_HealParty
	end

J_PlayersHouse_1F_EventScript_MomHealsParty_PokecenterChallenge::
	msgbox J_PlayersHouse_1F_Text_YouShouldRestABit_PokecenterChallenge, MSGBOX_DEFAULT
	closemessage
	end

J_PlayersHouse_1F_Text_YouShouldRestABit_PokecenterChallenge:
	.string "MOM{SE_M_HEAT_WAVE}Sorr{SE_M_YAWN}honey{SE_M_SUPERSONIC}yo{SE_M_DIVE}ar{SE_M_REVERSAL}playing\n"
	.string "wit{SE_M_TRI_ATTACK}th{SE_M_REVERSAL}POKéCENTE{SE_M_MINIMIZE}challenge!$"

J_PlayersHouse_1F_EventScript_SeeYouHoney::
	msgbox J_PlayersHouse_1F_Text_SeeYouHoney, MSGBOX_DEFAULT
	release
	end

J_PlayersHouse_1F_EventScript_HealParty::
	closemessage
	call J_Common_EventScript_OutOfCenterPartyHeal
	incrementgamestat 16
	msgbox J_PlayersHouse_1F_Text_TakeCareHoney, MSGBOX_DEFAULT
	release
	end

J_PlayersHouse_1F_EventScript_DidYouMeetProfBirch::
	msgbox J_PlayersHouse_1F_Text_DidYouMeetProfBirch, MSGBOX_DEFAULT
	release
	end

J_PlayersHouse_1F_EventScript_Vigoroth1::
	lock
	faceplayer
	waitse
	playmoncry 288, 0
	msgbox J_PlayersHouse_1F_Text_Vigoroth1, MSGBOX_DEFAULT
	waitmoncry
	release
	end

J_PlayersHouse_1F_EventScript_Vigoroth2::
	lock
	faceplayer
	waitse
	playmoncry 288, 0
	msgbox J_PlayersHouse_1F_Text_Vigoroth2, MSGBOX_DEFAULT
	waitmoncry
	release
	end

J_PlayersHouse_1F_Movement_PlayerApproachTVForGymMale:
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	step_end

J_PlayersHouse_1F_Movement_PlayerMoveToTVMale:
	walk_left
	step_end

J_PlayersHouse_1F_Movement_PlayerApproachTVForGymFemale:
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	step_end

J_PlayersHouse_1F_Movement_PlayerMoveToTVFemale:
	walk_right
	step_end

J_PlayersHouse_1F_Movement_MovePlayerAwayFromDoor:
	walk_up
	step_end

J_PlayersHouse_1F_EventScript_GetSSTicketAndSeeLatiTV::
	lockall
	checkplayergender
	call_if_eq 32781, MALE, J_PlayersHouse_1F_EventScript_SetUpObjectEventVarsMale
	call_if_eq 32781, FEMALE, J_PlayersHouse_1F_EventScript_SetUpObjectEventVarsFemale
	call_if_eq 32776, MALE, J_PlayersHouse_1F_EventScript_PlayerEnterRoomMale
	call_if_eq 32776, FEMALE, J_PlayersHouse_1F_EventScript_PlayerEnterRoomFemale
	applymovement 32777, J_Common_Movement_FacePlayer
	waitmovement 0
	playse 21
	applymovement 32777, J_Common_Movement_ExclamationMark
	waitmovement 0
	applymovement 32777, J_Common_Movement_Delay48
	waitmovement 0
	delay 20
	call_if_eq 32776, MALE, J_PlayersHouse_1F_EventScript_DadApproachPlayerMale
	call_if_eq 32776, FEMALE, J_PlayersHouse_1F_EventScript_DadApproachPlayerFemale
	msgbox J_PlayersHouse_1F_Text_TicketFromBrineyCameForYou, MSGBOX_DEFAULT
	giveitem ITEM_SS_TICKET
	msgbox J_PlayersHouse_1F_Text_PortsInSlateportLilycove, MSGBOX_DEFAULT
	closemessage
	delay 20
	call_if_eq 32776, MALE, J_PlayersHouse_1F_EventScript_MomApproachDadMale
	call_if_eq 32776, FEMALE, J_PlayersHouse_1F_EventScript_MomApproachDadFemale
	msgbox J_PlayersHouse_1F_Text_BetterGetBackToGym, MSGBOX_DEFAULT
	closemessage
	call_if_eq 32776, MALE, J_PlayersHouse_1F_EventScript_DadExitsMale
	call_if_eq 32776, FEMALE, J_PlayersHouse_1F_EventScript_DadExitsFemale
	playse 8
	removeobject 32777
	setflag 0
	delay 30
	call_if_eq 32776, MALE, J_PlayersHouse_1F_EventScript_MomApproachPlayerMale
	call_if_eq 32776, FEMALE, J_PlayersHouse_1F_EventScript_MomApproachPlayerFemale
	delay 20
	msgbox J_PlayersHouse_1F_Text_DadShouldStayLonger, MSGBOX_DEFAULT
	closemessage
	setflag 0
	special TurnOnTVScreen
	delay 60
	call_if_eq 32776, MALE, J_PlayersHouse_1F_EventScript_MomNoticesLatiBroadcastMale
	call_if_eq 32776, FEMALE, J_PlayersHouse_1F_EventScript_MomNoticesLatiBroadcastFemale
	msgbox J_PlayersHouse_1F_Text_IsThatABreakingStory, MSGBOX_DEFAULT
	closemessage
	call_if_eq 32776, MALE, J_PlayersHouse_1F_EventScript_PlayerApproachTVForLatiMale
	call_if_eq 32776, FEMALE, J_PlayersHouse_1F_EventScript_PlayerApproachTVForLatiFemale
	msgbox J_PlayersHouse_1F_Text_LatiEmergencyNewsFlash, MSGBOX_DEFAULT
	closemessage
	clearflag 0
	setflag 8955
	special TurnOffTVScreen
	call_if_eq 32776, MALE, J_PlayersHouse_1F_EventScript_MomApproachPlayerAfterTVMale
	call_if_eq 32776, FEMALE, J_PlayersHouse_1F_EventScript_MomApproachPlayerAfterTVFemale
	msgbox J_PlayersHouse_1F_Text_WhatColorDidTheySay, MSGBOX_DEFAULT
	multichoice 22, 8, 108, TRUE
	copyvar 32772, 32781
	special InitRoamer
	copyvar 20677, 32781
	msgbox J_PlayersHouse_1F_Text_StillUnknownPokemon, MSGBOX_DEFAULT
	closemessage
	setvar 20594, 4
	setvar 20604, 4
	releaseall
	end

J_PlayersHouse_1F_EventScript_AirLatiBroadcast::
	setflag 0
	return

J_PlayersHouse_1F_EventScript_SetUpObjectEventVarsMale::
	setvar 32776, MALE
	setvar 32777, 5
	setvar 32778, 1
	return

J_PlayersHouse_1F_EventScript_SetUpObjectEventVarsFemale::
	setvar 32776, FEMALE
	setvar 32777, 5
	setvar 32778, 1
	return

J_PlayersHouse_1F_EventScript_DadApproachPlayerMale::
	applymovement 32777, J_PlayersHouse_1F_Movement_DadApproachPlayerMale
	waitmovement 0
	return

J_PlayersHouse_1F_EventScript_DadApproachPlayerFemale::
	applymovement 32777, J_PlayersHouse_1F_Movement_DadApproachPlayerFemale
	waitmovement 0
	return

J_PlayersHouse_1F_EventScript_MomApproachDadMale::
	applymovement 32778, J_PlayersHouse_1F_Movement_MomApproachDadMale
	waitmovement 0
	applymovement 32777, J_PlayersHouse_1F_Movement_DadFaceMomMale
	waitmovement 0
	return

J_PlayersHouse_1F_EventScript_MomApproachDadFemale::
	applymovement 32778, J_PlayersHouse_1F_Movement_MomApproachDadFemale
	waitmovement 0
	applymovement 32777, J_PlayersHouse_1F_Movement_DadFaceMomFemale
	waitmovement 0
	return

J_PlayersHouse_1F_EventScript_DadExitsMale::
	applymovement 255, J_PlayersHouse_1F_Movement_MomAndPlayerWatchDadExit
	applymovement 32778, J_PlayersHouse_1F_Movement_MomAndPlayerWatchDadExit
	applymovement 32777, J_PlayersHouse_1F_Movement_DadExitsMale
	waitmovement 0
	return

J_PlayersHouse_1F_EventScript_DadExitsFemale::
	applymovement 255, J_PlayersHouse_1F_Movement_MomAndPlayerWatchDadExit
	applymovement 32778, J_PlayersHouse_1F_Movement_MomAndPlayerWatchDadExit
	applymovement 32777, J_PlayersHouse_1F_Movement_DadExitsFemale
	waitmovement 0
	return

J_PlayersHouse_1F_EventScript_PlayerEnterRoomMale::
	applymovement 255, J_PlayersHouse_1F_Movement_PlayerEnterRoomMale
	waitmovement 0
	return

J_PlayersHouse_1F_EventScript_PlayerEnterRoomFemale::
	applymovement 255, J_PlayersHouse_1F_Movement_PlayerEnterRoomFemale
	waitmovement 0
	return

J_PlayersHouse_1F_EventScript_PlayerApproachTVForLatiMale::
	applymovement 255, J_PlayersHouse_1F_Movement_PlayerApproachTVForLatiMale
	waitmovement 0
	applymovement 32778, J_Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	return

J_PlayersHouse_1F_EventScript_PlayerApproachTVForLatiFemale::
	applymovement 255, J_PlayersHouse_1F_Movement_PlayerApproachTVForLatiFemale
	waitmovement 0
	applymovement 32778, J_Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	return

J_PlayersHouse_1F_EventScript_MomApproachPlayerMale::
	applymovement 32778, J_PlayersHouse_1F_Movement_MomApproachPlayerMale
	waitmovement 0
	applymovement 255, J_Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	return

J_PlayersHouse_1F_EventScript_MomApproachPlayerFemale::
	applymovement 32778, J_PlayersHouse_1F_Movement_MomApproachPlayerFemale
	waitmovement 0
	applymovement 255, J_Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	return

J_PlayersHouse_1F_EventScript_MomNoticesLatiBroadcastMale::
	applymovement 32778, J_PlayersHouse_1F_Movement_MomNoticesLatiBroadcastMale
	waitmovement 0
	return

J_PlayersHouse_1F_EventScript_MomNoticesLatiBroadcastFemale::
	applymovement 32778, J_PlayersHouse_1F_Movement_MomNoticesLatiBroadcastFemale
	waitmovement 0
	return

J_PlayersHouse_1F_EventScript_MomApproachPlayerAfterTVMale::
	applymovement 32778, J_PlayersHouse_1F_Movement_MomApproachPlayerAfterTVMale
	waitmovement 0
	applymovement 255, J_Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	return

J_PlayersHouse_1F_EventScript_MomApproachPlayerAfterTVFemale::
	applymovement 32778, J_PlayersHouse_1F_Movement_MomApproachPlayerAfterTVFemale
	waitmovement 0
	applymovement 255, J_Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	return

J_PlayersHouse_1F_Movement_DadApproachPlayerMale:
	walk_right
	walk_right
	step_end

J_PlayersHouse_1F_Movement_DadApproachPlayerFemale:
	walk_left
	walk_left
	step_end

J_PlayersHouse_1F_Movement_DadFaceMomMale:
	face_left
	step_end

J_PlayersHouse_1F_Movement_DadFaceMomFemale:
	face_right
	step_end

J_PlayersHouse_1F_Movement_DadExitsMale:
	walk_down
	walk_right
	walk_down
	delay_8
	step_end

J_PlayersHouse_1F_Movement_DadExitsFemale:
	walk_down
	walk_left
	walk_down
	delay_8
	step_end

J_PlayersHouse_1F_Movement_PlayerEnterRoomMale:
	delay_16
	walk_down
	walk_down
	walk_down
	walk_in_place_faster_left
	step_end

J_PlayersHouse_1F_Movement_MomAndPlayerWatchDadExit:
	delay_8
	delay_16
	delay_16
	walk_in_place_faster_down
	step_end

J_PlayersHouse_1F_Movement_PlayerEnterRoomFemale:
	delay_16
	walk_down
	walk_down
	walk_down
	walk_in_place_faster_right
	step_end

J_PlayersHouse_1F_Movement_PlayerApproachTVForLatiMale:
	walk_up
	walk_left
	walk_left
	walk_left
	walk_left
	walk_in_place_faster_up
	step_end

J_PlayersHouse_1F_Movement_PlayerApproachTVForLatiFemale:
	walk_up
	walk_right
	walk_right
	walk_right
	walk_right
	walk_in_place_faster_up
	step_end

J_EventScript_RunningShoesManual::
	msgbox J_PlayersHouse_1F_Text_RunningShoesManual, MSGBOX_SIGN
	end

	.set NUM_OPPONENTS, 32777

