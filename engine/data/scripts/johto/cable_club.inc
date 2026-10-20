@ Johto (data/scripts/cable_club.inc), as built into the FireRed game.

J_CableClub_OnTransition:
	call J_CableClub_EventScript_HideOrShowMysteryGiftMan
	end

J_CableClub_EventScript_HideOrShowMysteryGiftMan::
	specialvar 32781, ShouldDistributeEonTicket
	goto_if_eq 32781, TRUE, J_CableClub_EventScript_ShowMysteryGiftMan
	specialvar 32781, ValidateSavedWonderCard
	goto_if_eq 32781, FALSE, J_CableClub_EventScript_HideMysteryGiftMan
	goto J_CableClub_EventScript_ShowMysteryGiftMan
	end

J_CableClub_EventScript_ShowMysteryGiftMan::
	clearflag 8424
	return

J_CableClub_EventScript_HideMysteryGiftMan::
	setflag 8424
	return

J_CableClub_EventScript_MysteryGiftMan::
	specialvar 32781, ShouldDistributeEonTicket
	goto_if_eq 32781, TRUE, J_CableClub_EventScript_DistributeEonTicket
	goto J_CableClub_EventScript_TryWonderCardScript
	end

J_CableClub_EventScript_TryWonderCardScript::
	trywondercardscript

J_CableClub_EventScript_MysteryGiftThankYou::
	msgbox J_gText_ThankYouForAccessingMysteryGift, MSGBOX_NPC
	end

J_CableClub_EventScript_DistributeEonTicket::
	checkitem ITEM_EON_TICKET
	goto_if_eq 32781, TRUE, J_CableClub_EventScript_TryWonderCardScript
	goto_if_set 0, J_CableClub_EventScript_TryWonderCardScript
	msgbox J_MysteryGift_Text_TheresATicketForYou, MSGBOX_DEFAULT
	giveitem ITEM_EON_TICKET
	setflag 0
	setvar 20527, 0
	msgbox J_MysteryGift_Text_TryUsingItAtLilycovePort, MSGBOX_DEFAULT
	release
	end

J_CableClub_EventScript_MysteryGiftThankYou2::
	msgbox J_gText_ThankYouForAccessingMysteryGift, MSGBOX_DEFAULT
	release
	end

J_CableClub_OnWarp:
	map_script_2 20599, 1, J_CableClub_EventScript_CheckTurnAttendant
	map_script_2 20599, 2, J_CableClub_EventScript_CheckTurnAttendant
	map_script_2 20599, 5, J_CableClub_EventScript_CheckTurnAttendant
	map_script_2 20599, 3, J_CableClub_EventScript_CheckTurnAttendant
	map_script_2 20599, 4, J_CableClub_EventScript_CheckTurnAttendant
	map_script_2 20599, 6, J_CableClub_EventScript_CheckTurnAttendant
	map_script_2 20599, 7, J_CableClub_EventScript_CheckTurnAttendant
	map_script_2 20599, 8, J_CableClub_EventScript_CheckTurnAttendant
	.2byte 0

J_CableClub_EventScript_CheckTurnAttendant::
	goto_if_eq 32775, 0, J_CableClub_EventScript_DontTurnAttendant
	turnobject 32775, DIR_WEST

J_CableClub_EventScript_DontTurnAttendant::
	end

J_CableClub_OnLoad:
	goto_if_eq 20599, 1, J_CableClub_EventScript_OnLoadFromColosseum
	goto_if_eq 20599, 2, J_CableClub_EventScript_OnLoadFromColosseum
	goto_if_eq 20599, 5, J_CableClub_EventScript_OnLoadFromColosseum
	goto_if_eq 20599, 3, J_CableClub_EventScript_OnLoadFromTradeCenter
	goto_if_eq 20599, 4, J_CableClub_EventScript_OnLoadFromRecordCorner
	goto_if_eq 20599, 6, J_CableClub_EventScript_OnLoadFromUnionRoom
	goto_if_eq 20599, 7, J_CableClub_EventScript_OnLoadFromBerryCrush
	goto_if_eq 20599, 8, J_CableClub_EventScript_OnLoadFromGameCorner
	end

J_CableClub_EventScript_OnLoadFromColosseum::
	call J_CableClub_EventScript_OpenDirectCornerBarrier
	end

J_CableClub_EventScript_OnLoadFromTradeCenter::
	call J_CableClub_EventScript_OpenDirectCornerBarrier
	end

J_CableClub_EventScript_OnLoadFromRecordCorner::
	call J_CableClub_EventScript_OpenDirectCornerBarrier
	end

J_CableClub_EventScript_OnLoadFromUnionRoom::
	call J_CableClub_EventScript_OpenUnionRoomBarrier
	end

J_CableClub_EventScript_OnLoadFromBerryCrush::
	call J_CableClub_EventScript_OpenDirectCornerBarrier
	end

J_CableClub_EventScript_OnLoadFromGameCorner::
	call J_EventScript_OpenMossdeepGameCornerBarrier
	end

J_CableClub_OnFrame:
	map_script_2 20669, 1, J_CableClub_EventScript_Tutorial
	map_script_2 20599, 1, J_CableClub_EventScript_ExitLinkRoom
	map_script_2 20599, 2, J_CableClub_EventScript_ExitLinkRoom
	map_script_2 20599, 5, J_CableClub_EventScript_ExitLinkRoom
	map_script_2 20599, 3, J_CableClub_EventScript_ExitTradeCenter
	map_script_2 20599, 4, J_CableClub_EventScript_ExitRecordCorner
	map_script_2 20599, 6, J_CableClub_EventScript_ExitUnionRoom
	map_script_2 20599, 7, J_CableClub_EventScript_ExitLinkRoom
	map_script_2 20599, 8, J_CableClub_EventScript_ExitMinigameRoom
	.2byte 0

J_CableClub_EventScript_ExitLinkRoom::
	lockall
	call J_CableClub_EventScript_CloseLinkAndExitLinkRoom
	call J_CableClub_EventScript_CloseDirectCornerBarrier
	special DrawWholeMapView
	playse 36
	erasebox 0, 0, 29, 19
	releaseall
	end

J_CableClub_EventScript_ExitMinigameRoom::
	lockall
	call J_CableClub_EventScript_CloseLinkAndExitLinkRoom
	call J_EventScript_CloseMossdeepGameCornerBarrier
	special DrawWholeMapView
	playse 36
	erasebox 0, 0, 29, 19
	releaseall
	end

J_CableClub_EventScript_CloseLinkAndExitLinkRoom::
	special CloseLink
	setvar 20599, 0
	goto_if_eq 32775, 0, J_CableClub_EventScript_PlayerExitLinkRoom
	applymovement 32775, J_Movement_AttendantFaceLeft
	waitmovement 0
	applymovement 255, J_Movement_PlayerExitLinkRoom
	waitmovement 0
	applymovement 32775, J_Movement_AttendantFaceDown
	waitmovement 0
	return

J_CableClub_EventScript_ExitTradeCenter::
	lockall
	call J_CableClub_EventScript_PlayerExitTradeCenter
	call J_CableClub_EventScript_CloseDirectCornerBarrier
	special DrawWholeMapView
	playse 36
	erasebox 0, 0, 29, 19
	releaseall
	end

J_CableClub_EventScript_PlayerExitTradeCenter::
	special CloseLink
	setvar 20599, 0
	goto_if_eq 32775, 0, J_CableClub_EventScript_PlayerExitLinkRoom
	applymovement 255, J_Movement_PlayerFaceAttendantRight
	waitmovement 0
	applymovement 32775, J_Movement_AttendantFaceLeft
	waitmovement 0
	call J_CableClub_EventScript_TrainerCardDataOverwritten
	return

J_CableClub_EventScript_ExitRecordCorner::
	lockall
	call J_CableClub_EventScript_PlayerExitRecordCorner
	call J_CableClub_EventScript_CloseDirectCornerBarrier
	special DrawWholeMapView
	playse 36
	erasebox 0, 0, 29, 19
	releaseall
	end

J_CableClub_EventScript_PlayerExitRecordCorner::
	special CloseLink
	setvar 20599, 0
	applymovement 255, J_Movement_PlayerExitLinkRoom
	waitmovement 0
	goto_if_eq 32775, 0, J_CableClub_EventScript_ExitRecordCornerRet
	applymovement 32775, J_Movement_AttendantFaceDown
	waitmovement 0

J_CableClub_EventScript_ExitRecordCornerRet::
	return

J_CableClub_EventScript_ExitUnionRoom::
	lockall
	call J_CableClub_EventScript_PlayerExitUnionRoom
	call J_CableClub_EventScript_CloseUnionRoomBarrier
	special DrawWholeMapView
	playse 36
	erasebox 0, 0, 29, 19
	releaseall
	end

J_CableClub_EventScript_PlayerExitUnionRoom::
	setvar 20599, 0
	goto_if_eq 32775, 0, J_CableClub_EventScript_PlayerExitLinkRoom
	applymovement 255, J_Movement_PlayerFaceAttendantRight
	waitmovement 0
	applymovement 32775, J_Movement_AttendantFaceLeft
	waitmovement 0
	call J_CableClub_EventScript_TrainerCardDataOverwritten
	return

J_CableClub_EventScript_TrainerCardDataOverwritten::
	message J_CableClub_Text_TrainerCardDataOverwritten
	waitmessage
	playse 21
	delay 60
	message J_CableClub_Text_HopeToSeeYouAgain
	waitmessage
	applymovement 255, J_Movement_PlayerExitLinkRoom
	waitmovement 0
	applymovement 32775, J_Movement_AttendantFaceDown
	waitmovement 0
	return

J_CableClub_EventScript_PlayerExitLinkRoom::
	applymovement 255, J_Movement_PlayerExitLinkRoom
	waitmovement 0
	return

J_CableClub_EventScript_Tutorial::
	lockall
	applymovement 255, J_Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	msgbox J_CableClub_Text_FirstTimeRightThisWay, MSGBOX_DEFAULT
	closemessage
	applymovement 255, J_CableClub_Movement_PlayerApproachCounter
	waitmovement 0
	delay 30
	msgbox J_CableClub_Text_ExplainWirelessClubFirstTime, MSGBOX_DEFAULT
	setvar 20669, 2
	releaseall
	end

J_CableClub_Movement_PlayerApproachCounter:
	walk_up
	walk_up
	step_end

J_CableClub_EventScript_WelcomeToCableClub::
	message J_CableClub_Text_WelcomeWhichCableClubService
	waitmessage
	delay 28
	goto J_CableClub_EventScript_SelectCableClubRoom
	end

J_CableClub_EventScript_UnusedWelcomeToCableClub::
	msgbox J_CableClub_Text_WhichService, MSGBOX_DEFAULT
	goto J_CableClub_EventScript_SelectCableClubRoom
	end

J_CableClub_EventScript_SelectCableClubRoom::
	setvar 32772, 0
	goto_if_set 0, J_CableClub_EventScript_CableClubUnlockedRecordCorner
	multichoice 0, 0, 74, FALSE
	switch 32781
	case 0, J_CableClub_EventScript_TradeCenter
	case 1, J_CableClub_EventScript_Colosseum
	case 2, J_CableClub_EventScript_AbortLink
	case 127, J_CableClub_EventScript_AbortLink
	end

J_CableClub_EventScript_CableClubUnlockedRecordCorner::
	multichoice 0, 0, 76, FALSE
	switch 32781
	case 0, J_CableClub_EventScript_TradeCenter
	case 1, J_CableClub_EventScript_Colosseum
	case 2, J_CableClub_EventScript_RecordCorner
	case 3, J_CableClub_EventScript_AbortLink
	case 127, J_CableClub_EventScript_AbortLink
	end

J_CableClub_EventScript_Colosseum::
	copyvar 32775, 32783
	goto J_CableClub_EventScript_SelectBattleMode
	end

J_CableClub_EventScript_SelectBattleMode::
	message J_CableClub_Text_PlayWhichBattleMode
	waitmessage
	multichoice 0, 0, 18, FALSE
	switch 32781
	case 0, J_CableClub_EventScript_SingleBattleMode
	case 1, J_CableClub_EventScript_DoubleBattleMode
	case 2, J_CableClub_EventScript_MultiBattleMode
	case 3, J_CableClub_EventScript_BattleModeInfo
	case 4, J_CableClub_EventScript_AbortLink
	case 127, J_CableClub_EventScript_AbortLink
	end

J_CableClub_EventScript_BattleModeInfo::
	msgbox J_CableClub_Text_ExplainBattleModes, MSGBOX_DEFAULT
	goto J_CableClub_EventScript_SelectBattleMode
	end

J_CableClub_EventScript_SingleBattleMode::
	setvar 32772, 1
	goto J_CableClub_EventScript_TryEnterColosseum
	end

J_CableClub_EventScript_DoubleBattleMode::
	special HasEnoughMonsForDoubleBattle
	goto_if_ne 32781, 0, J_CableClub_EventScript_NeedTwoMonsForDoubleBattle
	setvar 32772, 2
	goto J_CableClub_EventScript_TryEnterColosseum
	end

J_CableClub_EventScript_NeedTwoMonsForDoubleBattle::
	msgbox J_CableClub_Text_NeedTwoMonsForDoubleBattle, MSGBOX_DEFAULT
	goto J_CableClub_EventScript_SelectBattleMode
	end

J_CableClub_EventScript_MultiBattleMode::
	setvar 32772, 5
	goto J_CableClub_EventScript_TryEnterColosseum
	end

J_CableClub_EventScript_TryEnterColosseum::
	call J_Common_EventScript_SaveGame
	goto_if_eq 32781, 0, J_CableClub_EventScript_AbortLink
	message J_gText_PleaseWaitForLink
	waitmessage
	special TryBattleLinkup
	waitstate
	goto_if_eq 32781, 1, J_CableClub_EventScript_EnterColosseum
	goto_if_eq 32781, 2, J_CableClub_EventScript_AbortLinkSomeoneNotReady
	goto_if_eq 32781, 3, J_CableClub_EventScript_AbortLinkDifferentSelections
	goto_if_eq 32781, 4, J_CableClub_EventScript_AbortLinkIncorrectNumberOfBattlers
	goto_if_eq 32781, 5, J_CableClub_EventScript_AbortLink
	goto_if_eq 32781, 6, J_CableClub_EventScript_AbortLinkConnectionError
	end

J_CableClub_EventScript_EnterColosseum::
	special HealPlayerParty
	special SavePlayerParty
	special LoadPlayerBag
	copyvar 20599, 32772
	messageautoscroll J_CableClub_Text_PleaseEnter
	waitmessage
	call J_CableClub_EventScript_OpenDirectCornerBarrier
	special DrawWholeMapView
	playse 36
	delay 60
	applymovement 32783, J_Movement_AttendantFaceLeft
	waitmovement 0
	closemessage
	applymovement 255, J_Movement_PlayerApproachLinkRoomLeft
	waitmovement 0
	opendoor 9, 1
	waitdooranim
	applymovement 255, J_Movement_PlayerEnterLinkRoom
	waitmovement 0
	hideplayer
	closedoor 9, 1
	waitdooranim
	release
	goto_if_eq 32772, 5, J_CableClub_EventScript_WarpTo4PColosseum
	special SetCableClubWarp
	warp MAP_BATTLE_COLOSSEUM_2P, 6, 8
	special DoCableClubWarp
	waitstate
	end

J_CableClub_EventScript_PlayerApproachLinkRoomRight::
	applymovement 255, J_Movement_PlayerApproachLinkRoomRight
	waitmovement 0
	return

J_CableClub_EventScript_WarpTo4PColosseum::
	special SetCableClubWarp
	warp MAP_BATTLE_COLOSSEUM_4P, 5, 8
	special DoCableClubWarp
	waitstate
	end

J_CableClub_EventScript_AbortLinkIncorrectNumberOfBattlers::
	switch 32772
	case 1, J_CableClub_EventScript_AbortLinkWrongNumberForSingleBattle
	case 2, J_CableClub_EventScript_AbortLinkWrongNumberForDoubleBattle
	case 5, J_CableClub_EventScript_AbortLinkNeedFourPlayers
	goto J_CableClub_EventScript_AbortLinkIncorrectNumberOfParticipants
	end

J_CableClub_EventScript_AbortLinkNeedFourPlayers::
	special CloseLink
	msgbox J_CableClub_Text_NeedFourPlayers, MSGBOX_DEFAULT
	goto J_CableClub_EventScript_ConfirmNumberAndRestart
	end

J_CableClub_EventScript_AbortLinkWrongNumberForDoubleBattle::
	special CloseLink
	msgbox J_CableClub_Text_CantDoubleBattleWithXPlayers, MSGBOX_DEFAULT
	goto J_CableClub_EventScript_ConfirmNumberAndRestart
	end

J_CableClub_EventScript_AbortLinkWrongNumberForSingleBattle::
	special CloseLink
	msgbox J_CableClub_Text_CantSingleBattleWithXPlayers, MSGBOX_DEFAULT
	goto J_CableClub_EventScript_ConfirmNumberAndRestart
	end

J_CableClub_EventScript_ConfirmNumberAndRestart::
	special CloseLink
	msgbox J_CableClub_Text_PleaseConfirmNumberAndRestart, MSGBOX_DEFAULT
	release
	end

J_CableClub_EventScript_TradeCenter::
	copyvar 32775, 32783
	call J_CableClub_EventScript_CheckPartyTradeRequirements
	goto_if_eq 32781, 0, J_CableClub_EventScript_AbortLink
	call J_Common_EventScript_SaveGame
	goto_if_eq 32781, 0, J_CableClub_EventScript_AbortLink
	message J_gText_PleaseWaitForLink
	waitmessage
	special TryTradeLinkup
	waitstate
	goto_if_eq 32781, 1, J_CableClub_EventScript_EnterTradeCenter
	goto_if_eq 32781, 2, J_CableClub_EventScript_AbortLinkSomeoneNotReady
	goto_if_eq 32781, 3, J_CableClub_EventScript_AbortLinkDifferentSelections
	goto_if_eq 32781, 4, J_CableClub_EventScript_AbortLinkIncorrectNumberOfParticipants
	goto_if_eq 32781, 5, J_CableClub_EventScript_AbortLink
	goto_if_eq 32781, 6, J_CableClub_EventScript_AbortLinkConnectionError
	goto_if_eq 32781, 7, J_CableClub_EventScript_AbortLinkPlayerNotReady
	goto_if_eq 32781, 9, J_CableClub_EventScript_AbortLinkOtherTrainerNotReady
	end

J_CableClub_EventScript_EnterTradeCenter::
	setvar 32772, 3
	copyvar 20599, 32772
	messageautoscroll J_CableClub_Text_PleaseEnter
	waitmessage
	call J_CableClub_EventScript_OpenDirectCornerBarrier
	special DrawWholeMapView
	playse 36
	delay 60
	applymovement 32783, J_Movement_AttendantFaceLeft
	waitmovement 0
	closemessage
	applymovement 255, J_Movement_PlayerApproachLinkRoomLeft
	waitmovement 0
	opendoor 9, 1
	waitdooranim
	applymovement 255, J_Movement_PlayerEnterLinkRoom
	waitmovement 0
	hideplayer
	closedoor 9, 1
	waitdooranim
	release
	special SetCableClubWarp
	setwarp MAP_TRADE_CENTER, 5, 8
	special DoCableClubWarp
	waitstate
	end

J_CableClub_EventScript_CheckPartyTradeRequirements::
	specialvar 32781, CalculatePlayerPartyCount
	goto_if_lt 32781, 2, J_CableClub_EventScript_NeedTwoMonsToTrade
	specialvar 32781, DoesPartyHaveEnigmaBerry
	goto_if_eq 32781, TRUE, J_CableClub_EventScript_CantTradeEnigmaBerry
	setvar 32781, 1
	return

J_CableClub_EventScript_NeedTwoMonsToTrade::
	msgbox J_CableClub_Text_NeedTwoMonsToTrade, MSGBOX_DEFAULT
	setvar 32781, 0
	return

J_CableClub_EventScript_CantTradeEnigmaBerry::
	msgbox J_CableClub_Text_CantTradeEnigmaBerry, MSGBOX_DEFAULT
	setvar 32781, 0
	return

J_CableClub_EventScript_RecordCorner::
	copyvar 32775, 32783
	call J_Common_EventScript_SaveGame
	goto_if_eq 32781, 0, J_CableClub_EventScript_AbortLink
	message J_gText_PleaseWaitForLink
	waitmessage
	special TryRecordMixLinkup
	waitstate
	special ValidateMixingGameLanguage
	waitstate
	goto_if_eq 32781, 12, J_CableClub_EventScript_AbortLinkForeignGame
	goto_if_eq 32781, 1, J_CableClub_EventScript_EnterRecordCorner
	goto_if_eq 32781, 2, J_CableClub_EventScript_AbortLinkSomeoneNotReady
	goto_if_eq 32781, 3, J_CableClub_EventScript_AbortLinkDifferentSelections
	goto_if_eq 32781, 4, J_CableClub_EventScript_AbortLinkIncorrectNumberOfParticipants
	goto_if_eq 32781, 5, J_CableClub_EventScript_AbortLink
	goto_if_eq 32781, 6, J_CableClub_EventScript_AbortLinkConnectionError
	end

J_CableClub_EventScript_EnterRecordCorner::
	setvar 32772, 4
	copyvar 20599, 32772
	messageautoscroll J_CableClub_Text_PleaseEnter
	waitmessage
	call J_CableClub_EventScript_OpenDirectCornerBarrier
	special DrawWholeMapView
	playse 36
	delay 60
	applymovement 32783, J_Movement_AttendantFaceLeft
	waitmovement 0
	closemessage
	applymovement 255, J_Movement_PlayerApproachLinkRoomLeft
	waitmovement 0
	opendoor 9, 1
	waitdooranim
	applymovement 255, J_Movement_PlayerEnterLinkRoom
	waitmovement 0
	hideplayer
	closedoor 9, 1
	waitdooranim
	release
	special SetCableClubWarp
	setwarp MAP_RECORD_CORNER, 8, 9
	special DoCableClubWarp
	waitstate
	end

J_CableClub_EventScript_AbortLinkPlayerNotReady::
	special CloseLink
	msgbox J_CableClub_Text_NotSetUpForFarAwayRegion, MSGBOX_DEFAULT
	release
	end

J_CableClub_EventScript_AbortLinkOtherTrainerNotReady::
	special CloseLink
	msgbox J_CableClub_Text_OtherTrainerNotReady, MSGBOX_DEFAULT
	release
	end

J_CableClub_EventScript_AbortLinkConnectionError::
	special CloseLink
	msgbox J_Text_LinkErrorPleaseReset, MSGBOX_DEFAULT
	release
	end

J_CableClub_EventScript_AbortLinkSomeoneNotReady::
	special CloseLink
	msgbox J_Text_SomeoneIsNotReadyToLink, MSGBOX_DEFAULT
	release
	end

J_CableClub_EventScript_AbortLinkDifferentSelections::
	special CloseLink
	msgbox J_Text_PlayersMadeDifferentSelections, MSGBOX_DEFAULT
	release
	end

J_CableClub_EventScript_AbortLink::
	special CloseLink
	msgbox J_CableClub_Text_PleaseVisitAgain, MSGBOX_DEFAULT
	release
	end

J_MossdeepCity_GameCorner_1F_EventScript_AbortMinigame::
	special CloseLink
	msgbox J_MossdeepCity_GameCorner_1F_Text_ComeAgain, MSGBOX_DEFAULT
	release
	end

J_CableClub_EventScript_CableClubWarp::
	special SetCableClubWarp
	special DoCableClubWarp
	waitstate
	end

J_CableClub_EventScript_AbortLinkIncorrectNumberOfParticipants::
	special CloseLink
	msgbox J_CableClub_Text_IncorrectNumberOfParticipants, MSGBOX_DEFAULT
	release
	end

J_CableClub_EventScript_AbortLinkPlayerHasBadEgg::
	special CloseLink
	msgbox J_CableClub_Text_YouHaveAMonThatCantBeTaken, MSGBOX_DEFAULT
	release
	end

J_CableClub_EventScript_AbortLinkForeignGame::
	special CloseLink
	msgbox J_CableClub_Text_CantMixWithJapaneseGame, MSGBOX_DEFAULT
	release
	end

J_CableClub_EventScript_WirelessClubAdjustements::
	msgbox J_gText_SorryWirelessClubAdjustments, MSGBOX_DEFAULT
	release
	end

J_CableClub_EventScript_NotReadyYet::
	msgbox J_gText_UndergoingAdjustments, MSGBOX_DEFAULT
	releaseall
	end

J_Movement_AttendantFaceDown:
	face_down
	step_end

J_Movement_AttendantFaceRight:
	face_right
	step_end

J_Movement_AttendantFaceLeft:
	face_left
	step_end

J_Movement_PlayerExitLinkRoom:
	walk_down
	walk_down
	step_end

J_Movement_PlayerApproachLinkRoomRight:
	walk_right
	walk_up
	walk_up
	step_end

J_Movement_PlayerApproachLinkRoomLeft:
	walk_left
	walk_up
	walk_up
	step_end

J_Movement_PlayerEnterLinkRoom:
	walk_up
	step_end

J_Movement_PlayerFaceAttendantLeft:
	face_left
	step_end

J_Movement_PlayerFaceAttendantRight:
	face_right
	step_end

J_Movement_PlayerEnterMinigameRoom:
	walk_left
	walk_up
	walk_up
	walk_up
	step_end

J_EventScript_CableBoxResults::
	lockall
	setvar 32772, 0
	special ShowLinkBattleRecords
	waitbuttonpress
	special RemoveRecordsWindow
	releaseall
	end

J_EventScript_BattleColosseum_2P_PlayerSpot0::
	setvar 32773, 0
	special ColosseumPlayerSpotTriggered
	waitstate
	end

J_EventScript_BattleColosseum_2P_PlayerSpot1::
	setvar 32773, 1
	special ColosseumPlayerSpotTriggered
	waitstate
	end

J_EventScript_BattleColosseum_4P_PlayerSpot0::
	fadescreen 1
	special ChooseHalfPartyForBattle
	waitstate
	goto_if_eq 32781, 0, J_EventScript_BattleColosseum_4P_CancelSpotTrigger
	setvar 32773, 0
	special ColosseumPlayerSpotTriggered
	waitstate
	end

J_EventScript_BattleColosseum_4P_PlayerSpot1::
	fadescreen 1
	special ChooseHalfPartyForBattle
	waitstate
	goto_if_eq 32781, 0, J_EventScript_BattleColosseum_4P_CancelSpotTrigger
	setvar 32773, 1
	special ColosseumPlayerSpotTriggered
	waitstate
	end

J_EventScript_BattleColosseum_4P_PlayerSpot2::
	fadescreen 1
	special ChooseHalfPartyForBattle
	waitstate
	goto_if_eq 32781, 0, J_EventScript_BattleColosseum_4P_CancelSpotTrigger
	setvar 32773, 2
	special ColosseumPlayerSpotTriggered
	waitstate
	end

J_EventScript_BattleColosseum_4P_PlayerSpot3::
	fadescreen 1
	special ChooseHalfPartyForBattle
	waitstate
	goto_if_eq 32781, 0, J_EventScript_BattleColosseum_4P_CancelSpotTrigger
	setvar 32773, 3
	special ColosseumPlayerSpotTriggered
	waitstate
	end

J_EventScript_BattleColosseum_4P_CancelSpotTrigger::
	end

J_EventScript_TradeCenter_Chair0::
	setvar 32773, 0
	special PlayerEnteredTradeSeat
	waitstate
	end

J_EventScript_TradeCenter_Chair1::
	setvar 32773, 1
	special PlayerEnteredTradeSeat
	waitstate
	end

J_EventScript_TradeCenter_Chair2::
	setvar 32773, 2
	special PlayerEnteredTradeSeat
	waitstate
	end

J_EventScript_TradeCenter_Chair3::
	setvar 32773, 3
	special PlayerEnteredTradeSeat
	waitstate
	end

J_EventScript_RecordCenter_Spot0::
	setvar 32773, 0
	special RecordMixingPlayerSpotTriggered
	waitstate
	goto_if_ne 16385, ITEM_NONE, J_RecordCorner_EventScript_ReceivedGiftItem
	end

J_EventScript_RecordCenter_Spot1::
	setvar 32773, 1
	special RecordMixingPlayerSpotTriggered
	waitstate
	goto_if_ne 16385, ITEM_NONE, J_RecordCorner_EventScript_ReceivedGiftItem
	end

J_EventScript_RecordCenter_Spot2::
	setvar 32773, 2
	special RecordMixingPlayerSpotTriggered
	waitstate
	goto_if_ne 16385, ITEM_NONE, J_RecordCorner_EventScript_ReceivedGiftItem
	end

J_EventScript_RecordCenter_Spot3::
	setvar 32773, 3
	special RecordMixingPlayerSpotTriggered
	waitstate
	goto_if_ne 16385, ITEM_NONE, J_RecordCorner_EventScript_ReceivedGiftItem
	end

J_RecordCorner_EventScript_ReceivedGiftItem::
	bufferitemname STR_VAR_2, 16385
	message J_RecordCorner_Text_PlayerSentOverOneX
	waitmessage
	waitbuttonpress
	releaseall
	end

J_CableClub_EventScript_ReadTrainerCard::
	msgbox J_CableClub_Text_GotToLookAtTrainerCard, MSGBOX_DEFAULT
	fadescreen 1
	special Script_ShowLinkTrainerCard
	waitstate
	end

J_CableClub_EventScript_ReadTrainerCardColored::
	msgbox J_CableClub_Text_GotToLookAtColoredTrainerCard, MSGBOX_DEFAULT
	fadescreen 1
	special Script_ShowLinkTrainerCard
	waitstate
	end

J_CableClub_EventScript_TooBusyToNotice::
	msgbox J_CableClub_Text_TooBusyToNotice, MSGBOX_DEFAULT
	closemessage
	end

J_BattleColosseum_2P_EventScript_Attendant::
	special Script_FacePlayer
	msgbox J_BattleColosseum_2P_Text_TakePlaceStartBattle, MSGBOX_DEFAULT
	special Script_ClearHeldMovement
	closemessage
	end

J_TradeCenter_EventScript_Attendant::
	special Script_FacePlayer
	msgbox J_TradeCenter_Text_TakeSeatStartTrade, MSGBOX_DEFAULT
	special Script_ClearHeldMovement
	closemessage
	end

J_RecordCorner_EventScript_Attendant::
	goto_if_ne 16384, 0, J_RecordCorner_EventScript_AlreadyMixed
	special Script_FacePlayer
	message J_RecordCorner_Text_TakeSeatAndWait
	waitmessage
	waitbuttonpress
	special Script_ClearHeldMovement
	closemessage
	end

J_RecordCorner_EventScript_AlreadyMixed::
	special Script_FacePlayer
	message J_RecordCorner_Text_ThanksForComing
	waitmessage
	waitbuttonpress
	special Script_ClearHeldMovement
	closemessage
	end

J_EventScript_ConfirmLeaveCableClubRoom::
	msgbox J_Text_TerminateLinkConfirmation, MSGBOX_YESNO
	goto_if_eq 32781, YES, J_EventScript_TerminateLink
	erasebox 0, 0, 29, 19
	releaseall
	end

J_EventScript_TerminateLink::
	messageautoscroll J_Text_TerminateLinkPleaseWait
	waitmessage
	special ExitLinkRoom
	end

J_EventScript_DoLinkRoomExit::
	special CleanupLinkRoomState
	special ReturnFromLinkRoom
	waitstate
	end

J_CableClub_EventScript_UnionRoomAttendant::
	lock
	faceplayer
	setvar 20671, 8
	goto_if_unset 2089, J_CableClub_EventScript_WirelessClubAdjustements
	specialvar 32781, IsBadEggInParty
	goto_if_eq 32781, TRUE, J_CableClub_EventScript_AbortLinkPlayerHasBadEgg
	copyvar 32775, 32783
	specialvar 32781, IsWirelessAdapterConnected
	goto_if_eq 32781, FALSE, J_CableClub_EventScript_UnionRoomAdapterNotConnected
	message J_CableClub_Text_WelcomeUnionRoomEnter
	waitmessage
	goto J_CableClub_EventScript_UnionRoomSelect
	end

J_CableClub_EventScript_UnionRoomSelect::
	multichoice 17, 6, 17, FALSE
	switch 32781
	case 0, J_CableClub_EventScript_EnterUnionRoom
	case 1, J_CableClub_EventScript_AbortLink
	case 2, J_CableClub_EventScript_UnionRoomInfo
	case 127, J_CableClub_EventScript_AbortLink
	end

J_CableClub_EventScript_UnionRoomInfo::
	message J_CableClub_Text_UnionRoomInfo
	waitmessage
	goto J_CableClub_EventScript_UnionRoomSelect
	end

J_CableClub_EventScript_EnterUnionRoom::
	call J_CableClub_EventScript_CheckPartyUnionRoomRequirements
	goto_if_eq 32781, 0, J_CableClub_EventScript_AbortLink
	call J_Common_EventScript_SaveGame
	goto_if_eq 32781, 0, J_CableClub_EventScript_AbortLink
	msgbox J_CableClub_Text_EnjoyUnionRoom, MSGBOX_DEFAULT
	closemessage
	special HealPlayerParty
	setvar 32772, 6
	copyvar 20599, 32772
	call J_CableClub_EventScript_OpenUnionRoomBarrier
	special DrawWholeMapView
	playse 36
	delay 60
	applymovement 32783, J_Movement_AttendantFaceLeft
	waitmovement 0
	applymovement 255, J_Movement_PlayerApproachLinkRoomLeft
	waitmovement 0
	opendoor 5, 1
	waitdooranim
	applymovement 255, J_Movement_PlayerEnterLinkRoom
	waitmovement 0
	hideplayer
	closedoor 5, 1
	waitdooranim
	special Script_ResetUnionRoomTrade
	special SetCableClubWarp
	warpspinenter MAP_UNION_ROOM, 7, 11
	waitstate
	special RunUnionRoom
	waitstate
	end

J_CableClub_EventScript_CheckPartyUnionRoomRequirements::
	specialvar 32781, CountPartyNonEggMons
	goto_if_lt 32781, 2, J_CableClub_EventScript_NeedTwoMonsForUnionRoom
	specialvar 32781, DoesPartyHaveEnigmaBerry
	goto_if_eq 32781, TRUE, J_CableClub_EventScript_NoEnigmaBerryInUnionRoom
	setvar 32781, 1
	return

J_CableClub_EventScript_NeedTwoMonsForUnionRoom::
	msgbox J_CableClub_Text_NeedTwoMonsForUnionRoom, MSGBOX_DEFAULT
	goto J_EventScript_CableClub_SetVarResult0
	end

J_CableClub_EventScript_NoEnigmaBerryInUnionRoom::
	msgbox J_CableClub_Text_NoEnigmaBerryInUnionRoom, MSGBOX_DEFAULT
	goto J_EventScript_CableClub_SetVarResult0
	end

J_CableClub_EventScript_UnionRoomAdapterNotConnected::
	msgbox J_CableClub_Text_UnionRoomAdapterNotConnected, MSGBOX_DEFAULT
	release
	return

J_CableClub_EventScript_WirelessClubAttendant::
	lock
	faceplayer
	goto_if_unset 2089, J_CableClub_EventScript_WirelessClubAdjustements
	msgbox J_CableClub_Text_AskAboutLinking, MSGBOX_YESNO
	goto_if_eq 32781, NO, J_CableClub_EventScript_DontAskAboutLinking
	msgbox J_CableClub_Text_ExplainWirelessClub, MSGBOX_DEFAULT
	release
	return

J_CableClub_EventScript_DontAskAboutLinking::
	msgbox J_CableClub_Text_HopeYouEnjoyWirelessSystem, MSGBOX_DEFAULT
	release
	return

J_CableClub_EventScript_DirectCornerAttendant::
	lock
	faceplayer
	setvar 20671, 9
	goto_if_unset 2089, J_CableClub_EventScript_WirelessClubAdjustements
	specialvar 32781, IsBadEggInParty
	goto_if_eq 32781, TRUE, J_CableClub_EventScript_AbortLinkPlayerHasBadEgg
	specialvar 32781, IsWirelessAdapterConnected
	goto_if_eq 32781, FALSE, J_CableClub_EventScript_WelcomeToCableClub
	message J_CableClub_Text_WelcomeWhichDirectCornerRoom
	waitmessage
	delay 28
	goto J_CableClub_EventScript_DirectCornerSelectService
	end

J_CableClub_EventScript_DirectCornerSelectService::
	checkitem ITEM_POWDER_JAR
	goto_if_eq 32781, FALSE, J_CableClub_EventScript_DirectCornerNoBerry
	goto_if_set 0, J_CableClub_EventScript_DirectCornerSelectAllServices
	multichoice 0, 0, 78, FALSE
	switch 32781
	case 0, J_CableClub_EventScript_WirelessTrade
	case 1, J_CableClub_EventScript_WirelessBattleSelect
	case 2, J_CableClub_EventScript_WirelessBerryCrush
	case 3, J_CableClub_EventScript_AbortLink
	case 127, J_CableClub_EventScript_AbortLink
	end

J_CableClub_EventScript_DirectCornerSelectAllServices::
	multichoice 0, 0, 79, FALSE
	switch 32781
	case 0, J_CableClub_EventScript_WirelessTrade
	case 1, J_CableClub_EventScript_WirelessBattleSelect
	case 2, J_CableClub_EventScript_WirelessRecordMix
	case 3, J_CableClub_EventScript_WirelessBerryCrush
	case 4, J_CableClub_EventScript_AbortLink
	case 127, J_CableClub_EventScript_AbortLink
	end

J_CableClub_EventScript_DirectCornerNoBerry::
	goto_if_set 0, J_CableClub_EventScript_DirectCornerHasRecordMix
	multichoice 0, 0, 75, FALSE
	switch 32781
	case 0, J_CableClub_EventScript_WirelessTrade
	case 1, J_CableClub_EventScript_WirelessBattleSelect
	case 2, J_CableClub_EventScript_AbortLink
	case 127, J_CableClub_EventScript_AbortLink
	end

J_CableClub_EventScript_DirectCornerHasRecordMix::
	multichoice 0, 0, 77, FALSE
	switch 32781
	case 0, J_CableClub_EventScript_WirelessTrade
	case 1, J_CableClub_EventScript_WirelessBattleSelect
	case 2, J_CableClub_EventScript_WirelessRecordMix
	case 3, J_CableClub_EventScript_AbortLink
	case 127, J_CableClub_EventScript_AbortLink
	end

J_CableClub_EventScript_WirelessTrade::
	msgbox J_CableClub_Text_TradePokemon, MSGBOX_YESNO
	goto_if_eq 32781, NO, J_CableClub_EventScript_AbortLink
	call J_CableClub_EventScript_CheckPartyTradeRequirements
	goto_if_eq 32781, 0, J_CableClub_EventScript_AbortLink
	setvar 32772, 3
	goto J_CableClub_EventScript_SaveAndChooseLinkLeader
	end

J_CableClub_EventScript_WirelessBattleSelect::
	message J_CableClub_Text_PlayWhichBattleMode
	waitmessage
	multichoice 0, 0, 18, FALSE
	switch 32781
	case 0, J_CableClub_EventScript_WirelessSingleBattle
	case 1, J_CableClub_EventScript_WirelessDoubleBattle
	case 2, J_CableClub_EventScript_WirelessMultiBattle
	case 3, J_CableClub_EventScript_WirelessBattleInfo
	case 4, J_CableClub_EventScript_AbortLink
	case 127, J_CableClub_EventScript_AbortLink
	end

J_CableClub_EventScript_WirelessSingleBattle::
	setvar 32772, 0
	goto J_CableClub_EventScript_SaveAndChooseLinkLeader
	end

J_CableClub_EventScript_WirelessDoubleBattle::
	special HasEnoughMonsForDoubleBattle
	goto_if_ne 32781, 0, J_CableClub_EventScript_TwoMonsNeededForWirelessDoubleBattle
	setvar 32772, 1
	goto J_CableClub_EventScript_SaveAndChooseLinkLeader
	end

J_CableClub_EventScript_TwoMonsNeededForWirelessDoubleBattle::
	msgbox J_CableClub_Text_NeedTwoMonsForDoubleBattle, MSGBOX_DEFAULT
	goto J_CableClub_EventScript_WirelessBattleSelect
	end

J_CableClub_EventScript_WirelessMultiBattle::
	setvar 32772, 2
	goto J_CableClub_EventScript_SaveAndChooseLinkLeader
	end

J_CableClub_EventScript_WirelessBattleInfo::
	msgbox J_CableClub_Text_ExplainBattleModes, MSGBOX_DEFAULT
	goto J_CableClub_EventScript_WirelessBattleSelect
	end

J_CableClub_EventScript_WirelessRecordMix::
	msgbox J_CableClub_Text_AccessRecordCorner, MSGBOX_YESNO
	goto_if_eq 32781, NO, J_CableClub_EventScript_AbortLink
	setvar 32772, 12
	goto J_CableClub_EventScript_SaveAndChooseLinkLeader
	end

J_CableClub_EventScript_WirelessBerryCrush::
	msgbox J_CableClub_Text_UseBerryCrush, MSGBOX_YESNO
	goto_if_eq 32781, NO, J_CableClub_EventScript_AbortLink
	special HasAtLeastOneBerry
	goto_if_eq 32781, FALSE, J_CableClub_EventScript_NeedBerryForBerryCrush
	setvar 32772, 5
	goto J_CableClub_EventScript_SaveAndChooseLinkLeader
	end

J_CableClub_EventScript_NeedBerryForBerryCrush::
	msgbox J_CableClub_Text_NeedBerryForBerryCrush, MSGBOX_DEFAULT
	goto J_CableClub_EventScript_DirectCornerSelectService
	end

J_CableClub_EventScript_SaveAndChooseLinkLeader::
	call J_Common_EventScript_SaveGame
	goto_if_eq 32781, 0, J_CableClub_EventScript_AbortLink
	switch 32772
	case 3, J_CableClub_EventScript_ChooseLinkLeaderFrom2
	case 0, J_CableClub_EventScript_ChooseLinkLeaderFrom2
	case 1, J_CableClub_EventScript_ChooseLinkLeaderFrom2
	case 2, J_CableClub_EventScript_ChooseLinkLeaderFrom4
	case 5, J_CableClub_EventScript_ChooseLinkLeader
	case 12, J_CableClub_EventScript_ChooseLinkLeader
	end

J_CableClub_EventScript_ChooseLinkLeaderFrom2::
	message J_CableClub_Text_ChooseGroupLeaderOfTwo
	waitmessage
	multichoice 16, 6, 81, FALSE
	switch 32781
	case 0, J_CableClub_EventScript_TryJoinGroup2Players
	case 1, J_CableClub_EventScript_TryLeadGroup2Players
	case 2, J_CableClub_EventScript_AbortLink
	case 127, J_CableClub_EventScript_AbortLink
	end

J_CableClub_EventScript_TryLeadGroup2Players::
	call J_CableClub_EventScript_TryBecomeLinkLeader
	goto_if_eq 32781, 1, J_CableClub_EventScript_EnterWirelessLinkRoom
	goto_if_eq 32781, 5, J_CableClub_EventScript_ChooseLinkLeaderFrom2
	goto_if_eq 32781, 8, J_CableClub_EventScript_TryLeadGroup2Players
	release
	return

J_CableClub_EventScript_TryJoinGroup2Players::
	call J_CableClub_EventScript_TryJoinLinkGroup
	goto_if_eq 32781, 1, J_CableClub_EventScript_EnterWirelessLinkRoom
	goto_if_eq 32781, 5, J_CableClub_EventScript_ChooseLinkLeaderFrom2
	goto_if_eq 32781, 8, J_CableClub_EventScript_TryJoinGroup2Players
	release
	return

J_CableClub_EventScript_ChooseLinkLeaderFrom4::
	message J_CableClub_Text_ChooseGroupLeaderOfFour
	waitmessage
	multichoice 16, 6, 81, FALSE
	switch 32781
	case 0, J_CableClub_EventScript_TryJoinGroup4Players
	case 1, J_CableClub_EventScript_TryLeadGroup4Players
	case 2, J_CableClub_EventScript_AbortLink
	case 127, J_CableClub_EventScript_AbortLink
	end

J_CableClub_EventScript_TryLeadGroup4Players::
	call J_CableClub_EventScript_TryBecomeLinkLeader
	goto_if_eq 32781, 1, J_CableClub_EventScript_EnterWirelessLinkRoom
	goto_if_eq 32781, 5, J_CableClub_EventScript_ChooseLinkLeaderFrom4
	goto_if_eq 32781, 8, J_CableClub_EventScript_TryLeadGroup4Players
	release
	return

J_CableClub_EventScript_TryJoinGroup4Players::
	call J_CableClub_EventScript_TryJoinLinkGroup
	goto_if_eq 32781, 1, J_CableClub_EventScript_EnterWirelessLinkRoom
	goto_if_eq 32781, 5, J_CableClub_EventScript_ChooseLinkLeaderFrom4
	goto_if_eq 32781, 8, J_CableClub_EventScript_TryJoinGroup4Players
	release
	return

J_CableClub_EventScript_ChooseLinkLeader::
	message J_CableClub_Text_ChooseGroupLeader
	waitmessage
	multichoice 16, 6, 81, FALSE
	switch 32781
	case 0, J_CableClub_EventScript_TryJoinGroupXPlayers
	case 1, J_CableClub_EventScript_TryLeadGroupXPlayers
	case 2, J_CableClub_EventScript_AbortLink
	case 127, J_CableClub_EventScript_AbortLink
	end

J_CableClub_EventScript_TryLeadGroupXPlayers::
	call J_CableClub_EventScript_TryBecomeLinkLeader
	goto_if_eq 32781, 1, J_CableClub_EventScript_EnterWirelessLinkRoom
	goto_if_eq 32781, 5, J_CableClub_EventScript_ChooseLinkLeader
	goto_if_eq 32781, 8, J_CableClub_EventScript_TryLeadGroupXPlayers
	release
	return

J_CableClub_EventScript_TryJoinGroupXPlayers::
	call J_CableClub_EventScript_TryJoinLinkGroup
	goto_if_eq 32781, 1, J_CableClub_EventScript_EnterWirelessLinkRoom
	goto_if_eq 32781, 5, J_CableClub_EventScript_ChooseLinkLeader
	goto_if_eq 32781, 8, J_CableClub_EventScript_TryJoinGroupXPlayers
	release
	return

J_CableClub_EventScript_TryBecomeLinkLeader::
	special TryBecomeLinkLeader
	waitstate
	return

J_CableClub_EventScript_TryJoinLinkGroup::
	special TryJoinLinkGroup
	waitstate
	return

J_CableClub_EventScript_EnterWirelessLinkRoom::
	messageautoscroll J_CableClub_Text_DirectYouToYourRoom
	waitmessage
	delay 60
	closemessage
	copyvar 32775, 32783
	call J_CableClub_EventScript_OpenDirectCornerBarrier
	special DrawWholeMapView
	playse 36
	delay 60
	applymovement 32783, J_Movement_AttendantFaceLeft
	waitmovement 0
	closemessage
	applymovement 255, J_Movement_PlayerApproachLinkRoomLeft
	waitmovement 0
	opendoor 9, 1
	waitdooranim
	applymovement 255, J_Movement_PlayerEnterLinkRoom
	waitmovement 0
	hideplayer
	closedoor 9, 1
	waitdooranim
	release
	waitstate
	end

J_EventScript_WirelessBoxResults::
	lockall
	goto_if_unset 2089, J_CableClub_EventScript_NotReadyYet
	specialvar 32781, IsWirelessAdapterConnected
	goto_if_eq 32781, FALSE, J_CableClub_EventScript_AdapterNotConnected
	fadescreen 1
	special ShowWirelessCommunicationScreen
	waitstate
	msgbox J_CableClub_Text_ParticipantsStepUpToCounter, MSGBOX_DEFAULT
	releaseall
	end

J_CableClub_EventScript_AdapterNotConnected::
	msgbox J_CableClub_Text_AdapterNotConnected, MSGBOX_DEFAULT
	releaseall
	end

J_CableClub_EventScript_OpenUnionRoomBarrier::
	setmetatile 5, 2, 0x2DC, FALSE
	setmetatile 5, 3, 0x2E4, FALSE
	return

J_CableClub_EventScript_CloseUnionRoomBarrier::
	setmetatile 5, 2, 0x21E, TRUE
	setmetatile 5, 3, 0x25D, TRUE
	return

J_CableClub_EventScript_OpenDirectCornerBarrier::
	setmetatile 9, 2, 0x2DC, FALSE
	setmetatile 9, 3, 0x2E4, FALSE
	return

J_CableClub_EventScript_CloseDirectCornerBarrier::
	setmetatile 9, 2, 0x21E, TRUE
	setmetatile 9, 3, 0x25D, TRUE
	return

J_EventScript_OpenMossdeepGameCornerBarrier::
	setmetatile 5, 2, 0x22C, FALSE
	setmetatile 5, 3, 0x234, FALSE
	return

J_EventScript_CloseMossdeepGameCornerBarrier::
	setmetatile 5, 2, 0x22A, TRUE
	setmetatile 5, 3, 0x232, TRUE
	return

J_CableClub_OnResume:
	special InitUnionRoom
	.if 0 != 0
	return
	.else
	end
	.endif

J_MossdeepCity_GameCorner_1F_EventScript_InfoMan2::
	lock
	faceplayer
	message J_MossdeepCity_GameCorner_1F_Text_DescribeWhichGame
	waitmessage
	multichoice 0, 0, 80, FALSE
	switch 32781
	case 0, J_MossdeepCity_GameCorner_1F_EventScript_PokemonJumpInfo
	case 1, J_MossdeepCity_GameCorner_1F_EventScript_DodrioBerryPickingInfo
	case 2, J_MossdeepCity_GameCorner_1F_EventScript_MinigameInfoExit
	case 127, J_MossdeepCity_GameCorner_1F_EventScript_MinigameInfoExit
	end

J_MossdeepCity_GameCorner_1F_EventScript_PokemonJumpInfo::
	msgbox J_MossdeepCity_GameCorner_1F_Text_PokemonJumpInfo, MSGBOX_DEFAULT
	release
	end

J_MossdeepCity_GameCorner_1F_EventScript_DodrioBerryPickingInfo::
	msgbox J_MossdeepCity_GameCorner_1F_Text_DodrioBerryPickingInfo, MSGBOX_DEFAULT
	release
	end

J_MossdeepCity_GameCorner_1F_EventScript_MinigameInfoExit::
	msgbox J_MossdeepCity_GameCorner_1F_Text_TalkToOldManToPlay, MSGBOX_DEFAULT
	release
	end

J_MossdeepCity_GameCorner_1F_EventScript_OldMan2::
	lock
	faceplayer
	message J_MossdeepCity_GameCorner_1F_Text_WelcomeCanYouWait
	waitmessage
	specialvar 32781, IsWirelessAdapterConnected
	goto_if_eq 32781, FALSE, J_MossdeepCity_GameCorner_1F_EventScript_AdapterNotConnected
	delay 60
	message J_MossdeepCity_GameCorner_1F_Text_PlayWhichGame
	waitmessage
	multichoice 0, 0, 80, FALSE
	switch 32781
	case 0, J_MossdeepCity_GameCorner_1F_EventScript_PlayPokemonJump
	case 1, J_MossdeepCity_GameCorner_1F_EventScript_PlayDodrioBerryPicking
	case 2, J_MossdeepCity_GameCorner_1F_EventScript_AbortMinigame
	case 127, J_MossdeepCity_GameCorner_1F_EventScript_AbortMinigame
	end

J_MossdeepCity_GameCorner_1F_EventScript_PlayPokemonJump::
	setvar 32773, 0
	special IsPokemonJumpSpeciesInParty
	goto_if_eq 32781, FALSE, J_MossdeepCity_GameCorner_1F_EventScript_DontHaveRequiredMon
	msgbox J_MossdeepCity_GameCorner_1F_Text_EnterWhichPokemon, MSGBOX_DEFAULT
	fadescreen 1
	setvar 32773, 0
	special ChooseMonForWirelessMinigame
	waitstate
	goto_if_ge 32772, 6, J_MossdeepCity_GameCorner_1F_EventScript_AbortMinigame
	call J_Common_EventScript_SaveGame
	goto_if_eq 32781, 0, J_MossdeepCity_GameCorner_1F_EventScript_AbortMinigame
	setvar 32772, 4
	goto J_MossdeepCity_GameCorner_1F_EventScript_ChooseLinkLeader
	end

J_MossdeepCity_GameCorner_1F_EventScript_PlayDodrioBerryPicking::
	setvar 32773, 1
	special IsDodrioInParty
	goto_if_eq 32781, FALSE, J_MossdeepCity_GameCorner_1F_EventScript_DontHaveRequiredMon
	msgbox J_MossdeepCity_GameCorner_1F_Text_EnterWhichPokemon, MSGBOX_DEFAULT
	fadescreen 1
	setvar 32773, 1
	special ChooseMonForWirelessMinigame
	waitstate
	goto_if_ge 32772, 6, J_MossdeepCity_GameCorner_1F_EventScript_AbortMinigame
	call J_Common_EventScript_SaveGame
	goto_if_eq 32781, 0, J_MossdeepCity_GameCorner_1F_EventScript_AbortMinigame
	setvar 32772, 6
	goto J_MossdeepCity_GameCorner_1F_EventScript_ChooseLinkLeader
	end

J_MossdeepCity_GameCorner_1F_EventScript_ChooseLinkLeader::
	message J_CableClub_Text_ChooseGroupLeader
	waitmessage
	multichoice 16, 6, 81, FALSE
	switch 32781
	case 0, J_MossdeepCity_GameCorner_1F_EventScript_TryJoinLinkGroup
	case 1, J_MossdeepCity_GameCorner_1F_EventScript_TryBecomeLinkLeader
	case 2, J_MossdeepCity_GameCorner_1F_EventScript_AbortMinigame
	case 127, J_MossdeepCity_GameCorner_1F_EventScript_AbortMinigame
	end

J_MossdeepCity_GameCorner_1F_EventScript_TryBecomeLinkLeader::
	call J_CableClub_EventScript_TryBecomeLinkLeader
	goto_if_eq 32781, 1, J_MossdeepCity_GameCorner_1F_EventScript_EnterMinigameRoom
	goto_if_eq 32781, 5, J_MossdeepCity_GameCorner_1F_EventScript_ChooseLinkLeader
	goto_if_eq 32781, 8, J_MossdeepCity_GameCorner_1F_EventScript_TryBecomeLinkLeader
	release
	return

J_MossdeepCity_GameCorner_1F_EventScript_TryJoinLinkGroup::
	call J_CableClub_EventScript_TryJoinLinkGroup
	goto_if_eq 32781, 1, J_MossdeepCity_GameCorner_1F_EventScript_EnterMinigameRoom
	goto_if_eq 32781, 5, J_MossdeepCity_GameCorner_1F_EventScript_ChooseLinkLeader
	goto_if_eq 32781, 8, J_MossdeepCity_GameCorner_1F_EventScript_TryJoinLinkGroup
	release
	return

J_MossdeepCity_GameCorner_1F_EventScript_EnterMinigameRoom::
	messageautoscroll J_MossdeepCity_GameCorner_1F_Text_AllGoodToGo
	waitmessage
	delay 60
	closemessage
	copyvar 32775, 32783
	call J_EventScript_OpenMossdeepGameCornerBarrier
	special DrawWholeMapView
	playse 36
	delay 60
	applymovement 32783, J_Movement_AttendantFaceLeft
	waitmovement 0
	closemessage
	applymovement 255, J_Movement_PlayerEnterMinigameRoom
	waitmovement 0
	hideplayer
	release
	waitstate
	end

J_MossdeepCity_GameCorner_1F_EventScript_AdapterNotConnected::
	delay 60
	msgbox J_MossdeepCity_GameCorner_1F_Text_AdapterNotConnected, MSGBOX_DEFAULT
	release
	end

J_MossdeepCity_GameCorner_1F_EventScript_DontHaveRequiredMon::
	msgbox J_MossdeepCity_GameCorner_1F_Text_ExplainRequiredMon, MSGBOX_YESNO
	goto_if_eq 32781, NO, J_MossdeepCity_GameCorner_1F_EventScript_AbortMinigame
	call_if_eq 32773, 0, J_MossdeepCity_GameCorner_1F_EventScript_ExplainPokemonJumpRequirements
	call_if_eq 32773, 1, J_MossdeepCity_GameCorner_1F_EventScript_ExplainDodrioBerryPickingRequirements
	goto J_MossdeepCity_GameCorner_1F_EventScript_AbortMinigame
	end

J_MossdeepCity_GameCorner_1F_EventScript_ExplainPokemonJumpRequirements::
	msgbox J_MossdeepCity_GameCorner_1F_Text_ShortJumpingPokemonAllowed, MSGBOX_DEFAULT
	return

J_MossdeepCity_GameCorner_1F_EventScript_ExplainDodrioBerryPickingRequirements::
	msgbox J_MossdeepCity_GameCorner_1F_Text_OnlyDodrioAllowed, MSGBOX_DEFAULT
	return

J_MossdeepCity_GameCorner_1F_EventScript_PokemonJumpRecords::
	lockall
	special ShowPokemonJumpRecords
	waitstate
	releaseall
	end

J_MossdeepCity_GameCorner_1F_EventScript_DodrioBerryPickingRecords::
	lockall
	special ShowDodrioBerryPickingRecords
	waitstate
	releaseall
	end

