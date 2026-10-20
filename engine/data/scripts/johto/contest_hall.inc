@ Johto (data/scripts/contest_hall.inc), as built into the FireRed game.

J_LilycoveCity_ContestLobby_EventScript_SpeakToContestReceptionist::
	lock
	faceplayer

	goto_if_ne JOHTO_VAR_CONTEST_PRIZE_PICKUP_HNS, 0, J_LilycoveCity_ContestLobby_EventScript_PickUpPrize
	checkitem ITEM_POKEBLOCK_CASE
	call_if_eq VAR_RESULT, TRUE, J_LilycoveCity_ContestLobby_EventScript_ReceptionWelcome
	call_if_eq VAR_RESULT, FALSE, J_LilycoveCity_ContestLobby_EventScript_GivePokeblockCase





	goto J_LilycoveCity_ContestLobby_EventScript_AskEnterContest
	end

J_LilycoveCity_ContestLobby_EventScript_ReceptionWelcome::
	msgbox J_LilycoveCity_ContestLobby_Text_ContestReception, MSGBOX_DEFAULT
	return

J_LilycoveCity_ContestLobby_EventScript_GivePokeblockCase::
	msgbox J_LilycoveCity_ContestLobby_Text_ReceptionDontHavePokeblockCase, MSGBOX_DEFAULT
	giveitem ITEM_POKEBLOCK_CASE
	goto_if_eq VAR_RESULT, FALSE, J_Common_EventScript_ShowBagIsFull



	msgbox J_LilycoveCity_ContestLobby_Text_NowThatWeveClearedThatUp, MSGBOX_DEFAULT
	return

J_LilycoveCity_ContestLobby_EventScript_PickUpPrize::
	msgbox J_LilycoveCity_ContestLobby_Text_PokemonWonWeHavePrize, MSGBOX_DEFAULT

	switch JOHTO_VAR_CONTEST_PRIZE_PICKUP_HNS



	case 4, J_LilycoveCity_ContestLobby_EventScript_GiveLuxuryBallAtCounter
	end

J_LilycoveCity_ContestLobby_EventScript_GiveLuxuryBallAtCounter::
	giveitem ITEM_LUXURY_BALL
	goto_if_eq VAR_RESULT, FALSE, J_LilycoveCity_ContestLobby_EventScript_NoRoomForLuxuryBallAtCounter

	setvar JOHTO_VAR_CONTEST_PRIZE_PICKUP_HNS, 0



	closemessage
	release
	end

J_LilycoveCity_ContestLobby_EventScript_NoRoomForLuxuryBallAtCounter::
	call J_Common_EventScript_BagIsFull
	msgbox J_LilycoveCity_ContestLobby_Text_ComeBackForPrizeLater, MSGBOX_DEFAULT
	release
	end

J_LilycoveCity_ContestLobby_EventScript_AskEnterContest::
	message J_LilycoveCity_ContestLobby_Text_EnterContest1
	waitmessage
	multichoice 0, 0, MULTI_ENTERINFO, FALSE
	switch VAR_RESULT
	case 0, J_LilycoveCity_ContestLobby_EventScript_ChooseContestRank
	case 1, J_LilycoveCity_ContestLobby_EventScript_ContestInfo
	case 2, J_LilycoveCity_ContestLobby_EventScript_CancelEnterContest
	case MULTI_B_PRESSED, J_LilycoveCity_ContestLobby_EventScript_CancelEnterContest
	end

J_LilycoveCity_ContestLobby_EventScript_ContestInfo::
	message J_LilycoveCity_ContestLobby_Text_WhichTopic1
	waitmessage
	multichoice 0, 0, MULTI_CONTEST_INFO, FALSE
	switch VAR_RESULT
	case 0, J_LilycoveCity_ContestLobby_EventScript_ExplainContests
	case 1, J_LilycoveCity_ContestLobby_EventScript_ExplainContestTypes
	case 2, J_LilycoveCity_ContestLobby_EventScript_ExplainContestRanks
	case 3, J_LilycoveCity_ContestLobby_EventScript_AskEnterContest
	case MULTI_B_PRESSED, J_LilycoveCity_ContestLobby_EventScript_AskEnterContest
	end

J_LilycoveCity_ContestLobby_EventScript_ExplainContests::
	msgbox J_LilycoveCity_ContestLobby_Text_ExplainContests, MSGBOX_DEFAULT
	goto J_LilycoveCity_ContestLobby_EventScript_ContestInfo
	end

J_LilycoveCity_ContestLobby_EventScript_ExplainContestTypes::
	msgbox J_LilycoveCity_ContestLobby_Text_ExplainContestTypes, MSGBOX_DEFAULT
	goto J_LilycoveCity_ContestLobby_EventScript_ContestInfo
	end

J_LilycoveCity_ContestLobby_EventScript_ExplainContestRanks::
	msgbox J_LilycoveCity_ContestLobby_Text_ExplainContestRanks, MSGBOX_DEFAULT
	goto J_LilycoveCity_ContestLobby_EventScript_ContestInfo
	end

J_LilycoveCity_ContestLobby_EventScript_CancelEnterContest::
	msgbox J_LilycoveCity_ContestLobby_Text_ParticipateAnotherTime, MSGBOX_DEFAULT
	release
	end

J_LilycoveCity_ContestLobby_EventScript_ChooseContestMon::
	msgbox J_LilycoveCity_ContestLobby_Text_EnterWhichPokemon1, MSGBOX_DEFAULT
	choosecontestmon
	goto_if_eq VAR_0x8004, PARTY_NOTHING_CHOSEN, J_LilycoveCity_ContestLobby_EventScript_CancelEnterContest
	special TryEnterContestMon
	goto_if_eq VAR_RESULT, CANT_ENTER_CONTEST, J_LilycoveCity_ContestLobby_EventScript_CantEnterLowRank
	goto_if_eq VAR_RESULT, CAN_ENTER_CONTEST_EQUAL_RANK, J_LilycoveCity_ContestLobby_EventScript_EnterMon
	goto_if_eq VAR_RESULT, CAN_ENTER_CONTEST_HIGH_RANK, J_LilycoveCity_ContestLobby_EventScript_ConfirmEntryAlreadyWon
	goto_if_eq VAR_RESULT, CANT_ENTER_CONTEST_EGG, J_LilycoveCity_ContestLobby_EventScript_CantEnterEgg
	goto_if_eq VAR_RESULT, CANT_ENTER_CONTEST_FAINTED, J_LilycoveCity_ContestLobby_EventScript_CantEnterFainted
	end

J_LilycoveCity_ContestLobby_EventScript_ChooseContestRank::
	message J_LilycoveCity_ContestLobby_Text_EnterWhichRank
	waitmessage
	multichoice 0, 0, MULTI_CONTEST_RANK, FALSE
	switch VAR_RESULT
	case 0, J_LilycoveCity_ContestLobby_EventScript_EnterNormalRank
	case 1, J_LilycoveCity_ContestLobby_EventScript_EnterSuperRank
	case 2, J_LilycoveCity_ContestLobby_EventScript_EnterHyperRank
	case 3, J_LilycoveCity_ContestLobby_EventScript_EnterMasterRank
	case 4, J_LilycoveCity_ContestLobby_EventScript_CancelEnterContest
	case MULTI_B_PRESSED, J_LilycoveCity_ContestLobby_EventScript_CancelEnterContest
	end

J_LilycoveCity_ContestLobby_EventScript_EnterNormalRank::
	setvar VAR_CONTEST_RANK, CONTEST_RANK_NORMAL
	goto J_LilycoveCity_ContestLobby_EventScript_ChooseContestType
	end

J_LilycoveCity_ContestLobby_EventScript_EnterSuperRank::
	setvar VAR_CONTEST_RANK, CONTEST_RANK_SUPER
	goto J_LilycoveCity_ContestLobby_EventScript_ChooseContestType
	end

J_LilycoveCity_ContestLobby_EventScript_EnterHyperRank::
	setvar VAR_CONTEST_RANK, CONTEST_RANK_HYPER
	goto J_LilycoveCity_ContestLobby_EventScript_ChooseContestType
	end

J_LilycoveCity_ContestLobby_EventScript_EnterMasterRank::
	setvar VAR_CONTEST_RANK, CONTEST_RANK_MASTER
	goto J_LilycoveCity_ContestLobby_EventScript_ChooseContestType
	end

J_LilycoveCity_ContestLobby_EventScript_ChooseContestType::
	message J_LilycoveCity_ContestLobby_Text_EnterWhichContest1
	waitmessage
	multichoice 0, 0, MULTI_CONTEST_TYPE, FALSE
	switch VAR_RESULT
	case 5, J_LilycoveCity_ContestLobby_EventScript_CancelEnterContest
	case MULTI_B_PRESSED, J_LilycoveCity_ContestLobby_EventScript_CancelEnterContest
	copyvar VAR_CONTEST_CATEGORY, VAR_RESULT
	goto J_LilycoveCity_ContestLobby_EventScript_ChooseContestMon
	end

J_LilycoveCity_ContestLobby_EventScript_CantEnterLowRank::
	msgbox J_LilycoveCity_ContestLobby_Text_MonNotQualifiedForRank, MSGBOX_DEFAULT
	goto J_LilycoveCity_ContestLobby_EventScript_ChooseContestMon
	release
	end

J_LilycoveCity_ContestLobby_EventScript_ConfirmEntry::
	msgbox J_LilycoveCity_ContestLobby_Text_ConfirmContestMon, MSGBOX_YESNO
	switch VAR_RESULT
	case NO, J_LilycoveCity_ContestLobby_EventScript_ChooseContestMon
	case YES, J_LilycoveCity_ContestLobby_EventScript_EnterMon
	end

J_LilycoveCity_ContestLobby_EventScript_ConfirmEntryAlreadyWon::
	msgbox J_LilycoveCity_ContestLobby_Text_AlreadyWonEnterAnyway, MSGBOX_YESNO
	switch VAR_RESULT
	case NO, J_LilycoveCity_ContestLobby_EventScript_ChooseContestMon
	case YES, J_LilycoveCity_ContestLobby_EventScript_EnterMon
	end

J_LilycoveCity_ContestLobby_EventScript_CantEnterEgg::
	msgbox J_LilycoveCity_ContestLobby_Text_EggCannotTakePart, MSGBOX_DEFAULT
	goto J_LilycoveCity_ContestLobby_EventScript_ChooseContestMon
	release
	end

J_LilycoveCity_ContestLobby_EventScript_CantEnterFainted::
	msgbox J_LilycoveCity_ContestLobby_Text_MonInNoConditionForContest, MSGBOX_DEFAULT
	goto J_LilycoveCity_ContestLobby_EventScript_ChooseContestMon
	release
	end

J_LilycoveCity_ContestLobby_EventScript_EnterMon::
	msgbox J_LilycoveCity_ContestLobby_Text_YourMonIsEntryNum4, MSGBOX_DEFAULT
	closemessage
	releaseall
	setvar JOHTO_VAR_CONTEST_HALL_STATE, 1
	return

J_ContestHall_EventScript_DoContest::
	special LinkContestTryShowWirelessIndicator
	setvar VAR_0x8006, 0
	lockall
	applymovement LOCALID_CONTESTANT_4, J_ContestHall_Movement_Player4FaceUp
	waitmovement 0
	applymovement LOCALID_CONTEST_MC, J_ContestHall_Movement_MCWalkDown
	waitmovement 0
	releaseall
	call J_ContestHall_EventScript_TryWaitForLink
	call J_ContestHall_EventScript_GetContestRankStringId
	call J_ContestHall_EventScript_GetContestCategory
	call J_ContestHall_EventScript_ContestGettingStarted
	call J_ContestHall_EventScript_ShowContestMons
	call J_ContestHall_EventScript_DoContestAppeals
	call J_ContestHall_EventScript_ContestResults
	call J_ContestHall_EventScript_GetWinnerObjEventId
	call J_ContestHall_EventScript_CongratulateWinner
	call J_ContestHall_EventScript_AudienceLookAround
	call J_ContestHall_EventScript_GiveWinnerPrize
	setvar JOHTO_VAR_CONTEST_HALL_STATE, 2
	return

J_ContestHall_EventScript_GetContestRankStringId::
	switch VAR_CONTEST_RANK
	case CONTEST_RANK_NORMAL, J_ContestHall_EventScript_GetNormalStringId
	case CONTEST_RANK_SUPER, J_ContestHall_EventScript_GetSuperStringId
	case CONTEST_RANK_HYPER, J_ContestHall_EventScript_GetHyperStringId
	case CONTEST_RANK_MASTER, J_ContestHall_EventScript_GetMasterStringId
	return

J_ContestHall_EventScript_GetNormalStringId::
	setvar VAR_0x8009, STDSTRING_NORMAL
	return

J_ContestHall_EventScript_GetSuperStringId::
	setvar VAR_0x8009, STDSTRING_SUPER
	return

J_ContestHall_EventScript_GetHyperStringId::
	setvar VAR_0x8009, STDSTRING_HYPER
	return

J_ContestHall_EventScript_GetMasterStringId::
	setvar VAR_0x8009, STDSTRING_MASTER
	return

J_ContestHall_EventScript_GetContestCategory::
	switch VAR_CONTEST_CATEGORY
	case CONTEST_CATEGORY_COOL, J_ContestHall_EventScript_GetCategoryCool
	case CONTEST_CATEGORY_BEAUTY, J_ContestHall_EventScript_GetCategoryBeauty
	case CONTEST_CATEGORY_CUTE, J_ContestHall_EventScript_GetCategoryCute
	case CONTEST_CATEGORY_SMART, J_ContestHall_EventScript_GetCategorySmart
	case CONTEST_CATEGORY_TOUGH, J_ContestHall_EventScript_GetCategoryTough
	return

J_ContestHall_EventScript_GetCategoryCool::
	setvar VAR_0x8008, CONTEST_CATEGORY_COOL
	return

J_ContestHall_EventScript_GetCategoryBeauty::
	setvar VAR_0x8008, CONTEST_CATEGORY_BEAUTY
	return

J_ContestHall_EventScript_GetCategoryCute::
	setvar VAR_0x8008, CONTEST_CATEGORY_CUTE
	return

J_ContestHall_EventScript_GetCategorySmart::
	setvar VAR_0x8008, CONTEST_CATEGORY_SMART
	return

J_ContestHall_EventScript_GetCategoryTough::
	setvar VAR_0x8008, CONTEST_CATEGORY_TOUGH
	return

J_ContestHall_EventScript_ContestGettingStarted::
	buffercontestname STR_VAR_2, VAR_0x8008
	bufferstdstring STR_VAR_3, VAR_0x8009
	call J_ContestHall_EventScript_GettingStarted
	lockall
	applymovement LOCALID_CONTEST_MC, J_ContestHall_Movement_MCBackUp
	waitmovement 0
	releaseall
	return

J_ContestHall_EventScript_GettingStarted::
	goto_if_eq JOHTO_VAR_CONTEST_TYPE, (4 + 1), J_ContestHall_EventScript_GettingStartedLink
	lockall
	msgbox J_ContestHall_Text_GettingStartedParticipantsAsFollows, MSGBOX_DEFAULT
	releaseall
	return

J_ContestHall_EventScript_GettingStartedLink::
	specialvar VAR_RESULT, IsWirelessContest
	goto_if_eq VAR_RESULT, TRUE, J_ContestHall_EventScript_GettingStartedWireless
	messageautoscroll J_ContestHall_Text_GettingStartedParticipantsAsFollowsLink
	waitmessage
	return

J_ContestHall_EventScript_GettingStartedWireless::
	messageautoscroll J_ContestHall_Text_GettingStartedWireless
	waitmessage
	call J_ContestHall_EventScript_TryWaitForLink
	messageautoscroll J_ContestHall_Text_ParticipantsAsFollows
	waitmessage
	call J_ContestHall_EventScript_TryWaitForLink
	return

J_ContestHall_EventScript_ShowContestMons::
	call J_ContestHall_EventScript_ContestantWalkToCenter
	call J_ContestHall_EventScript_ShowContestMonPic
	call J_ContestHall_EventScript_AudienceHeartEmotes
	call J_ContestHall_EventScript_AudienceReactToContestant
	call J_ContestHall_EventScript_ContestantReturn
	call J_ContestHall_EventScript_TryWaitForLink
	call J_ContestHall_EventScript_TryWaitForLink
	addvar VAR_0x8006, 1
	goto_if_ne VAR_0x8006, CONTESTANT_COUNT, J_ContestHall_EventScript_ShowContestMons
	call J_ContestHall_EventScript_AudienceVote
	setvar VAR_TEMP_1, 6
	return

J_ContestHall_EventScript_TryWaitForLink::
	specialvar VAR_RESULT, IsWirelessContest
	goto_if_eq VAR_RESULT, TRUE, J_ContestHall_EventScript_WaitForLink
	return

J_ContestHall_EventScript_WaitForLink::
	special LinkContestWaitForConnection
	waitstate
	return

J_ContestHall_EventScript_ContestantWalkToCenter::
	goto_if_eq VAR_0x8006, 0, J_ContestHall_EventScript_Player1WalkToCenter
	goto_if_eq VAR_0x8006, 1, J_ContestHall_EventScript_Player2WalkToCenter
	goto_if_eq VAR_0x8006, 2, J_ContestHall_EventScript_Player3WalkToCenter
	goto_if_eq VAR_0x8006, 3, J_ContestHall_EventScript_Player4WalkToCenter
	return

J_ContestHall_EventScript_Player1WalkToCenter::
	call J_ContestHall_EventScript_TryWaitForLink
	lockall
	applymovement LOCALID_CONTESTANT_1, J_ContestHall_Movement_Player1WalkToCenter
	waitmovement 0
	releaseall
	setvar VAR_0x800B, LOCALID_CONTESTANT_1
	return

J_ContestHall_EventScript_Player2WalkToCenter::
	call J_ContestHall_EventScript_TryWaitForLink
	lockall
	applymovement LOCALID_CONTESTANT_2, J_ContestHall_Movement_Player2WalkToCenter
	waitmovement 0
	releaseall
	setvar VAR_0x800B, LOCALID_CONTESTANT_2
	return

J_ContestHall_EventScript_Player3WalkToCenter::
	call J_ContestHall_EventScript_TryWaitForLink
	lockall
	applymovement LOCALID_CONTESTANT_3, J_ContestHall_Movement_Player3WalkToCenter
	waitmovement 0
	releaseall
	setvar VAR_0x800B, LOCALID_CONTESTANT_3
	return

J_ContestHall_EventScript_Player4WalkToCenter::
	call J_ContestHall_EventScript_TryWaitForLink
	lockall
	applymovement LOCALID_CONTESTANT_4, J_ContestHall_Movement_Player4WalkToCenter
	waitmovement 0
	releaseall
	setvar VAR_0x800B, LOCALID_CONTESTANT_4
	return

J_ContestHall_EventScript_ShowContestMonPic::
	special BufferContestTrainerAndMonNames
	addvar VAR_0x8006, 1
	buffernumberstring STR_VAR_2, VAR_0x8006
	lockall
	applymovement VAR_0x800B, J_ContestHall_Movement_ContestantDelay32
	waitmovement 0
	releaseall
	call J_ContestHall_EventScript_TryWaitForLink
	call J_ContestHall_EventScript_CheckIfContestWithRSPlayer
	addobject LOCALID_CONTEST_POKEBALL
	playse SE_LEDGE
	lockall
	applymovement VAR_0x800B, J_ContestHall_Movement_ContestantDelay32
	waitmovement 0
	releaseall
	addvar VAR_0x8006, -1
	playse SE_BALL_OPEN
	special ShowContestEntryMonPic
	call J_ContestHall_EventScript_EntryXTrainersMon
	return

J_ContestHall_EventScript_EntryXTrainersMon::
	goto_if_eq JOHTO_VAR_CONTEST_TYPE, (4 + 1), J_ContestHall_EventScript_EntryXTrainersMonLink
	message J_ContestHall_Text_EntryXTrainersMon
	waitmessage
	return

J_ContestHall_EventScript_EntryXTrainersMonLink::
	messageautoscroll J_ContestHall_Text_EntryXTrainersMon
	waitmessage
	return

J_ContestHall_EventScript_AudienceVote::
	call J_ContestHall_EventScript_AudienceWillVote
	call J_ContestHall_EventScript_VotingUnderWay
	playse SE_M_ENCORE2
	waitmessage
	call J_ContestHall_EventScript_AudienceLookAround
	applymovement LOCALID_CONTEST_MC, J_ContestHall_Movement_MCFaceJudge2
	waitmovement 0
	applymovement LOCALID_CONTEST_JUDGE, J_ContestHall_Movement_JudgeFaceMC
	waitmovement 0
	delay 20
	applymovement LOCALID_CONTEST_MC, J_ContestHall_Movement_FaceContestants
	applymovement LOCALID_CONTEST_JUDGE, J_ContestHall_Movement_FaceContestants
	waitmovement 0
	return

J_ContestHall_EventScript_AudienceWillVote::
	goto_if_eq JOHTO_VAR_CONTEST_TYPE, (4 + 1), J_ContestHall_EventScript_AudienceWillVoteLink
	msgbox J_ContestHall_Text_SeenContestantsAudienceWillVote, MSGBOX_DEFAULT
	return

J_ContestHall_EventScript_AudienceWillVoteLink::
	specialvar VAR_RESULT, IsWirelessContest
	goto_if_eq VAR_RESULT, TRUE, J_ContestHall_EventScript_AudienceWillVoteWireless
	messageautoscroll J_ContestHall_Text_SeenContestantsAudienceWillVote
	waitmessage
	return

J_ContestHall_EventScript_AudienceWillVoteWireless::
	messageautoscroll J_ContestHall_Text_WeveSeenContestants
	waitmessage
	call J_ContestHall_EventScript_TryWaitForLink
	messageautoscroll J_ContestHall_Text_AudienceWillVote
	waitmessage
	call J_ContestHall_EventScript_TryWaitForLink
	messageautoscroll J_ContestHall_Text_LetVotingBegin
	waitmessage
	call J_ContestHall_EventScript_TryWaitForLink
	return

J_ContestHall_EventScript_VotingUnderWay::
	goto_if_eq JOHTO_VAR_CONTEST_TYPE, (4 + 1), J_ContestHall_EventScript_VotingUnderWayLink
	message J_ContestHall_Text_VotingUnderWay
	return

J_ContestHall_EventScript_VotingUnderWayLink::
	messageautoscroll J_ContestHall_Text_VotingUnderWay
	call J_ContestHall_EventScript_TryWaitForLink
	return

J_ContestHall_EventScript_AudienceReactToContestant::
	call J_ContestHall_EventScript_TryWaitForLink
	applymovement LOCALID_CONTEST_MC, J_ContestHall_Movement_AudienceMemberLookLeft
	waitmovement 0
	playse SE_M_ENCORE2
	call J_ContestHall_EventScript_VObjectAudienceLookAround
	applymovement LOCALID_CONTEST_AUDIENCE_5, J_ContestHall_Movement_AudienceMemberLookRight
	applymovement LOCALID_CONTEST_AUDIENCE_2, J_ContestHall_Movement_AudienceMemberLookDown
	applymovement LOCALID_CONTEST_AUDIENCE_3, J_ContestHall_Movement_AudienceMemberLookRight
	waitmovement 0
	applymovement LOCALID_CONTEST_MC, J_ContestHall_Movement_AudienceMemberLookRight
	waitmovement 0
	applymovement LOCALID_CONTEST_AUDIENCE_6, J_ContestHall_Movement_AudienceMemberLookLeft
	applymovement LOCALID_CONTEST_AUDIENCE_7, J_ContestHall_Movement_AudienceMemberLookDown
	applymovement LOCALID_CONTEST_AUDIENCE_1, J_ContestHall_Movement_AudienceMemberLookUp
	applymovement LOCALID_CONTEST_AUDIENCE_4, J_ContestHall_Movement_AudienceMemberLookLeft
	waitmovement 0
	applymovement LOCALID_CONTEST_MC, J_ContestHall_Movement_MCLookAtJudge
	waitmovement 0
	applymovement LOCALID_CONTEST_MC, J_ContestHall_Movement_MCWalkInPlaceDown
	applymovement LOCALID_CONTEST_JUDGE, J_ContestHall_Movement_JudgeLookAtMC
	waitmovement 0
	releaseall
	call J_ContestHall_EventScript_TryWaitForLink
	return

J_ContestHall_EventScript_AudienceHeartEmotes::
	special GetContestMonCondition
	call_if_eq JOHTO_VAR_CONTEST_TYPE, (0 + 1), J_ContestHall_EventScript_GetNumberOfHeartsNormal
	call_if_eq JOHTO_VAR_CONTEST_TYPE, (1 + 1), J_ContestHall_EventScript_GetNumberOfHeartsSuper
	call_if_eq JOHTO_VAR_CONTEST_TYPE, (2 + 1), J_ContestHall_EventScript_GetNumberOfHeartsHyper
	call_if_eq JOHTO_VAR_CONTEST_TYPE, (3 + 1), J_ContestHall_EventScript_GetNumberOfHeartsMaster
	call_if_eq JOHTO_VAR_CONTEST_TYPE, (4 + 1), J_ContestHall_EventScript_GetNumberOfHeartsLink
	setvar VAR_TEMP_1, 9
	setvar VAR_TEMP_2, 9
	setvar VAR_TEMP_3, 9
	setvar VAR_TEMP_4, 9
	setvar VAR_TEMP_5, 9
	setvar VAR_TEMP_6, 9
	setvar VAR_TEMP_7, 9
	setvar VAR_TEMP_8, 9
	call_if_gt VAR_TEMP_0, 0, J_ContestHall_EventScript_DisplayHearts
	setvar VAR_TEMP_1, 0
	setvar VAR_TEMP_2, 0
	setvar VAR_TEMP_3, 0
	setvar VAR_TEMP_4, 0
	setvar VAR_TEMP_5, 0
	setvar VAR_TEMP_6, 0
	setvar VAR_TEMP_7, 0
	setvar VAR_TEMP_8, 0
	return

J_ContestHall_EventScript_DisplayHearts::
	setvar VAR_RESULT, 8
	special GenerateContestRand
	call_if_eq VAR_RESULT, 0, J_ContestHall_EventScript_TryDisplayHeartAudienceMember1
	call_if_eq VAR_RESULT, 1, J_ContestHall_EventScript_TryDisplayHeartAudienceMember2
	call_if_eq VAR_RESULT, 2, J_ContestHall_EventScript_TryDisplayHeartAudienceMember3
	call_if_eq VAR_RESULT, 3, J_ContestHall_EventScript_TryDisplayHeartAudienceMember4
	call_if_eq VAR_RESULT, 4, J_ContestHall_EventScript_TryDisplayHeartAudienceMember5
	call_if_eq VAR_RESULT, 5, J_ContestHall_EventScript_TryDisplayHeartAudienceMember6
	call_if_eq VAR_RESULT, 6, J_ContestHall_EventScript_TryDisplayHeartAudienceMember7
	call_if_eq VAR_RESULT, 7, J_ContestHall_EventScript_TryDisplayHeartAudienceMember8
	goto_if_gt VAR_TEMP_0, 0, J_ContestHall_EventScript_DisplayHearts
	waitmovement 0
	return

J_ContestHall_EventScript_GetNumberOfHeartsNormal::
	goto_if_gt VAR_0x8004, 80, J_ContestHall_EventScript_Set8Hearts
	goto_if_gt VAR_0x8004, 70, J_ContestHall_EventScript_Set7Hearts
	goto_if_gt VAR_0x8004, 60, J_ContestHall_EventScript_Set6Hearts
	goto_if_gt VAR_0x8004, 50, J_ContestHall_EventScript_Set5Hearts
	goto_if_gt VAR_0x8004, 40, J_ContestHall_EventScript_Set4Hearts
	goto_if_gt VAR_0x8004, 30, J_ContestHall_EventScript_Set3Hearts
	goto_if_gt VAR_0x8004, 20, J_ContestHall_EventScript_Set2Hearts
	goto_if_gt VAR_0x8004, 10, J_ContestHall_EventScript_Set1Heart
	setvar VAR_TEMP_0, 0
	return

J_ContestHall_EventScript_GetNumberOfHeartsSuper::
	goto_if_gt VAR_0x8004, 230, J_ContestHall_EventScript_Set8Hearts
	goto_if_gt VAR_0x8004, 210, J_ContestHall_EventScript_Set7Hearts
	goto_if_gt VAR_0x8004, 190, J_ContestHall_EventScript_Set6Hearts
	goto_if_gt VAR_0x8004, 170, J_ContestHall_EventScript_Set5Hearts
	goto_if_gt VAR_0x8004, 150, J_ContestHall_EventScript_Set4Hearts
	goto_if_gt VAR_0x8004, 130, J_ContestHall_EventScript_Set3Hearts
	goto_if_gt VAR_0x8004, 110, J_ContestHall_EventScript_Set2Hearts
	goto_if_gt VAR_0x8004, 90, J_ContestHall_EventScript_Set1Heart
	setvar VAR_TEMP_0, 0
	return

J_ContestHall_EventScript_GetNumberOfHeartsHyper::
	goto_if_gt VAR_0x8004, 380, J_ContestHall_EventScript_Set8Hearts
	goto_if_gt VAR_0x8004, 350, J_ContestHall_EventScript_Set7Hearts
	goto_if_gt VAR_0x8004, 320, J_ContestHall_EventScript_Set6Hearts
	goto_if_gt VAR_0x8004, 290, J_ContestHall_EventScript_Set5Hearts
	goto_if_gt VAR_0x8004, 260, J_ContestHall_EventScript_Set4Hearts
	goto_if_gt VAR_0x8004, 230, J_ContestHall_EventScript_Set3Hearts
	goto_if_gt VAR_0x8004, 200, J_ContestHall_EventScript_Set2Hearts
	goto_if_gt VAR_0x8004, 170, J_ContestHall_EventScript_Set1Heart
	setvar VAR_TEMP_0, 0
	return

J_ContestHall_EventScript_GetNumberOfHeartsMaster::
	goto_if_gt VAR_0x8004, 600, J_ContestHall_EventScript_Set8Hearts
	goto_if_gt VAR_0x8004, 560, J_ContestHall_EventScript_Set7Hearts
	goto_if_gt VAR_0x8004, 520, J_ContestHall_EventScript_Set6Hearts
	goto_if_gt VAR_0x8004, 480, J_ContestHall_EventScript_Set5Hearts
	goto_if_gt VAR_0x8004, 440, J_ContestHall_EventScript_Set4Hearts
	goto_if_gt VAR_0x8004, 400, J_ContestHall_EventScript_Set3Hearts
	goto_if_gt VAR_0x8004, 360, J_ContestHall_EventScript_Set2Hearts
	goto_if_gt VAR_0x8004, 320, J_ContestHall_EventScript_Set1Heart
	setvar VAR_TEMP_0, 0
	return

J_ContestHall_EventScript_GetNumberOfHeartsLink::
	goto_if_gt VAR_0x8004, 600, J_ContestHall_EventScript_Set8Hearts
	goto_if_gt VAR_0x8004, 550, J_ContestHall_EventScript_Set7Hearts
	goto_if_gt VAR_0x8004, 500, J_ContestHall_EventScript_Set6Hearts
	goto_if_gt VAR_0x8004, 450, J_ContestHall_EventScript_Set5Hearts
	goto_if_gt VAR_0x8004, 400, J_ContestHall_EventScript_Set4Hearts
	goto_if_gt VAR_0x8004, 300, J_ContestHall_EventScript_Set3Hearts
	goto_if_gt VAR_0x8004, 200, J_ContestHall_EventScript_Set2Hearts
	goto_if_gt VAR_0x8004, 100, J_ContestHall_EventScript_Set1Heart
	setvar VAR_TEMP_0, 0
	return

J_ContestHall_EventScript_Set1Heart::
	setvar VAR_TEMP_0, 1
	return

J_ContestHall_EventScript_Set2Hearts::
	setvar VAR_TEMP_0, 2
	return

J_ContestHall_EventScript_Set3Hearts::
	setvar VAR_TEMP_0, 3
	return

J_ContestHall_EventScript_Set4Hearts::
	setvar VAR_TEMP_0, 4
	return

J_ContestHall_EventScript_Set5Hearts::
	setvar VAR_TEMP_0, 5
	return

J_ContestHall_EventScript_Set6Hearts::
	setvar VAR_TEMP_0, 6
	return

J_ContestHall_EventScript_Set7Hearts::
	setvar VAR_TEMP_0, 7
	return

J_ContestHall_EventScript_Set8Hearts::
	setvar VAR_TEMP_0, 8
	return

J_ContestHall_EventScript_TryDisplayHeartAudienceMember1::
	goto_if_eq VAR_TEMP_1, 1, J_ContestHall_EventScript_AudienceMember1AlreadyEmoted
	applymovement LOCALID_CONTEST_AUDIENCE_1, J_ContestHall_Movement_Heart
	playse SE_PIN
	delay 14
	setvar VAR_TEMP_1, 1
	addvar VAR_TEMP_0, -1
	return

J_ContestHall_EventScript_AudienceMember1AlreadyEmoted::
	return

J_ContestHall_EventScript_TryDisplayHeartAudienceMember2::
	goto_if_eq VAR_TEMP_2, 1, J_ContestHall_EventScript_AudienceMember2AlreadyEmoted
	applymovement LOCALID_CONTEST_AUDIENCE_2, J_ContestHall_Movement_Heart
	playse SE_PIN
	delay 14
	setvar VAR_TEMP_2, 1
	addvar VAR_TEMP_0, -1
	return

J_ContestHall_EventScript_AudienceMember2AlreadyEmoted::
	return

J_ContestHall_EventScript_TryDisplayHeartAudienceMember3::
	goto_if_eq VAR_TEMP_3, 1, J_ContestHall_EventScript_AudienceMember3AlreadyEmoted
	applymovement LOCALID_CONTEST_AUDIENCE_3, J_ContestHall_Movement_Heart
	playse SE_PIN
	delay 14
	setvar VAR_TEMP_3, 1
	addvar VAR_TEMP_0, -1
	return

J_ContestHall_EventScript_AudienceMember3AlreadyEmoted::
	return

J_ContestHall_EventScript_TryDisplayHeartAudienceMember4::
	goto_if_eq VAR_TEMP_4, 1, J_ContestHall_EventScript_Audience4MemberAlreadyEmoted
	applymovement LOCALID_CONTEST_AUDIENCE_4, J_ContestHall_Movement_Heart
	playse SE_PIN
	delay 14
	setvar VAR_TEMP_4, 1
	addvar VAR_TEMP_0, -1
	return

J_ContestHall_EventScript_Audience4MemberAlreadyEmoted::
	return

J_ContestHall_EventScript_TryDisplayHeartAudienceMember5::
	goto_if_eq VAR_TEMP_5, 1, J_ContestHall_EventScript_AudienceMember5AlreadyEmoted
	applymovement LOCALID_CONTEST_AUDIENCE_5, J_ContestHall_Movement_Heart
	playse SE_PIN
	delay 14
	setvar VAR_TEMP_5, 1
	addvar VAR_TEMP_0, -1
	return

J_ContestHall_EventScript_AudienceMember5AlreadyEmoted::
	return

J_ContestHall_EventScript_TryDisplayHeartAudienceMember6::
	goto_if_eq VAR_TEMP_6, 1, J_ContestHall_EventScript_AudienceMember6AlreadyEmoted
	applymovement LOCALID_CONTEST_AUDIENCE_6, J_ContestHall_Movement_Heart
	playse SE_PIN
	delay 14
	setvar VAR_TEMP_6, 1
	addvar VAR_TEMP_0, -1
	return

J_ContestHall_EventScript_AudienceMember6AlreadyEmoted::
	return

J_ContestHall_EventScript_TryDisplayHeartAudienceMember7::
	goto_if_eq VAR_TEMP_7, 1, J_ContestHall_EventScript_AudienceMember7AlreadyEmoted
	applymovement LOCALID_CONTEST_AUDIENCE_7, J_ContestHall_Movement_Heart
	playse SE_PIN
	delay 14
	setvar VAR_TEMP_7, 1
	addvar VAR_TEMP_0, -1
	return

J_ContestHall_EventScript_AudienceMember7AlreadyEmoted::
	return

J_ContestHall_EventScript_TryDisplayHeartAudienceMember8::
	goto_if_eq VAR_TEMP_8, 1, J_ContestHall_EventScript_AudienceMember8AlreadyEmoted
	applymovement LOCALID_CONTEST_ARTIST, J_ContestHall_Movement_Heart
	playse SE_PIN
	delay 14
	setvar VAR_TEMP_8, 1
	addvar VAR_TEMP_0, -1
	return

J_ContestHall_EventScript_AudienceMember8AlreadyEmoted::
	return

J_ContestHall_EventScript_ContestantReturn::
	closemessage
	release
	removeobject LOCALID_CONTEST_POKEBALL
	special HideContestEntryMonPic
	call J_ContestHall_EventScript_TryWaitForLink
	switch VAR_0x8006
	case 0, J_ContestHall_EventScript_Player1WalkBack
	case 1, J_ContestHall_EventScript_Player2WalkBack
	case 2, J_ContestHall_EventScript_Player3WalkBack
	case 3, J_ContestHall_EventScript_Player4WalkBack
	return

J_ContestHall_EventScript_Player1WalkBack::
	call J_ContestHall_EventScript_TryWaitForLink
	lockall
	applymovement VAR_0x800B, J_ContestHall_Movement_Player1WalkBack
	waitmovement 0
	releaseall
	return

J_ContestHall_EventScript_Player2WalkBack::
	call J_ContestHall_EventScript_TryWaitForLink
	lockall
	applymovement VAR_0x800B, J_ContestHall_Movement_Player2WalkBack
	waitmovement 0
	releaseall
	return

J_ContestHall_EventScript_Player3WalkBack::
	call J_ContestHall_EventScript_TryWaitForLink
	lockall
	applymovement VAR_0x800B, J_ContestHall_Movement_Player3WalkBack
	waitmovement 0
	releaseall
	return

J_ContestHall_EventScript_Player4WalkBack::
	call J_ContestHall_EventScript_TryWaitForLink
	lockall
	applymovement VAR_0x800B, J_ContestHall_Movement_Player4WalkBack
	waitmovement 0
	releaseall
	return

J_ContestHall_EventScript_DoContestAppeals::
	lockall
	applymovement LOCALID_CONTEST_MC, J_ContestHall_Movement_FaceContestants2
	waitmovement 0
	call J_ContestHall_EventScript_TryWaitForLink
	call J_ContestHall_EventScript_LetsAppeal
	waitmessage
	applymovement LOCALID_CONTEST_MC, J_ContestHall_Movement_WalkStageLeft
	applymovement LOCALID_CONTEST_JUDGE, J_ContestHall_Movement_WalkStageRight
	waitmovement 0
	releaseall
	call J_ContestHall_EventScript_TryWaitForLink
	setvar VAR_TEMP_9, 1
	special LinkContestTryHideWirelessIndicator
	startcontest
	special LinkContestTryShowWirelessIndicator
	setvar VAR_TEMP_9, 0
	lockall
	applymovement LOCALID_CONTEST_MC, J_ContestHall_Movement_WalkStageRight
	applymovement LOCALID_CONTEST_JUDGE, J_ContestHall_Movement_WalkStageLeft
	waitmovement 0
	releaseall
	return

J_ContestHall_EventScript_LetsAppeal::
	goto_if_eq JOHTO_VAR_CONTEST_TYPE, (4 + 1), J_ContestHall_EventScript_LetsAppealLink
	msgbox J_ContestHall_Text_VotingCompleteLetsAppeal, MSGBOX_DEFAULT
	return

J_ContestHall_EventScript_LetsAppealLink::
	specialvar VAR_RESULT, IsWirelessContest
	goto_if_eq VAR_RESULT, TRUE, J_ContestHall_EventScript_LetsAppealWireless
	messageautoscroll J_ContestHall_Text_VotingCompleteLetsAppeal
	waitmessage
	return

J_ContestHall_EventScript_LetsAppealWireless::
	call J_ContestHall_EventScript_TryWaitForLink
	messageautoscroll J_ContestHall_Text_VotingComplete
	waitmessage
	call J_ContestHall_EventScript_TryWaitForLink
	messageautoscroll J_ContestHall_Text_SecondStageOfJudging
	waitmessage
	call J_ContestHall_EventScript_TryWaitForLink
	messageautoscroll J_ContestHall_Text_LetsAppeal
	waitmessage
	call J_ContestHall_EventScript_TryWaitForLink
	return

J_ContestHall_EventScript_ContestResults::
	call J_ContestHall_EventScript_TryWaitForLink
	call J_ContestHall_EventScript_ThatsItForJudging
	call J_ContestHall_EventScript_TryWaitForLink
	call J_ContestHall_EventScript_ThankYouForAppeals
	call J_ContestHall_EventScript_TryWaitForLink
	applymovement LOCALID_CONTEST_MC, J_ContestHall_Movement_MCFaceJudge
	waitmovement 0
	call J_ContestHall_EventScript_JudgeLooksReady
	call J_ContestHall_EventScript_TryWaitForLink
	call J_ContestHall_EventScript_WeWillDeclareWinner
	call J_ContestHall_EventScript_TryWaitForLink
	applymovement LOCALID_CONTEST_MC, J_ContestHall_Movement_FaceContestants
	waitmovement 0
	closemessage
	releaseall
	special LinkContestTryHideWirelessIndicator
	setvar VAR_TEMP_9, 1
	showcontestresults
	setvar VAR_TEMP_9, 0
	playbgm MUS_CONTEST_WINNER, FALSE
	return

J_ContestHall_EventScript_ThatsItForJudging::
	goto_if_eq JOHTO_VAR_CONTEST_TYPE, (4 + 1), J_ContestHall_EventScript_ThatsItForJudgingLink
	msgbox J_ContestHall_Text_ThatsItForJudging, MSGBOX_DEFAULT
	return

J_ContestHall_EventScript_ThatsItForJudgingLink::
	call J_ContestHall_EventScript_TryWaitForLink
	messageautoscroll J_ContestHall_Text_ThatsItForJudging
	waitmessage
	delay 30
	return

J_ContestHall_EventScript_ThankYouForAppeals::
	goto_if_eq JOHTO_VAR_CONTEST_TYPE, (4 + 1), J_ContestHall_EventScript_ThankYouForAppealsLink
	msgbox J_ContestHall_Text_ThankYouForAppeals, MSGBOX_DEFAULT
	return

J_ContestHall_EventScript_ThankYouForAppealsLink::
	call J_ContestHall_EventScript_TryWaitForLink
	messageautoscroll J_ContestHall_Text_ThankYouForAppeals
	waitmessage
	delay 30
	return

J_ContestHall_EventScript_JudgeLooksReady::
	goto_if_eq JOHTO_VAR_CONTEST_TYPE, (4 + 1), J_ContestHall_EventScript_JudgeLooksReadyLink
	msgbox J_ContestHall_Text_JudgeLooksReady, MSGBOX_DEFAULT
	return

J_ContestHall_EventScript_JudgeLooksReadyLink::
	call J_ContestHall_EventScript_TryWaitForLink
	messageautoscroll J_ContestHall_Text_JudgeLooksReady
	waitmessage
	delay 30
	return

J_ContestHall_EventScript_WeWillDeclareWinner::
	goto_if_eq JOHTO_VAR_CONTEST_TYPE, (4 + 1), J_ContestHall_EventScript_WeWillDeclareWinnerLink
	msgbox J_ContestHall_Text_WeWillNowDeclareWinner, MSGBOX_DEFAULT
	return

J_ContestHall_EventScript_WeWillDeclareWinnerLink::
	call J_ContestHall_EventScript_TryWaitForLink
	messageautoscroll J_ContestHall_Text_WeWillNowDeclareWinner
	waitmessage
	delay 30
	return

J_ContestHall_EventScript_GetWinnerObjEventId::
	special GetContestWinnerId
	switch VAR_0x8005
	case 0, J_ContestHall_EventScript_GetPlayer1ObjEventId
	case 1, J_ContestHall_EventScript_GetPlayer2ObjEventId
	case 2, J_ContestHall_EventScript_GetPlayer3ObjEventId
	case 3, J_ContestHall_EventScript_GetPlayer4ObjEventId
	return

J_ContestHall_EventScript_GetPlayer1ObjEventId::
	setvar VAR_TEMP_3, LOCALID_CONTESTANT_1
	return

J_ContestHall_EventScript_GetPlayer2ObjEventId::
	setvar VAR_TEMP_3, LOCALID_CONTESTANT_2
	return

J_ContestHall_EventScript_GetPlayer3ObjEventId::
	setvar VAR_TEMP_3, LOCALID_CONTESTANT_3
	return

J_ContestHall_EventScript_GetPlayer4ObjEventId::
	setvar VAR_TEMP_3, LOCALID_CONTESTANT_4
	return

J_ContestHall_EventScript_CongratulateWinner::
	special BufferContestWinnerTrainerName
	special BufferContestWinnerMonName
	addvar VAR_0x8005, 1
	buffernumberstring STR_VAR_2, VAR_0x8005
	addvar VAR_0x8005, -1
	call J_ContestHall_EventScript_CongratsWinner
	applymovement VAR_TEMP_3, J_ContestHall_Movement_WinningPlayerWalkUp
	waitmovement 0
	playse SE_M_ENCORE2
	setvar VAR_TEMP_1, 0
	return

J_ContestHall_EventScript_CongratsWinner::
	goto_if_eq JOHTO_VAR_CONTEST_TYPE, (4 + 1), J_ContestHall_EventScript_CongratsWinnerLink
	msgbox J_ContestHall_Text_CongratsTrainerXandMon, MSGBOX_DEFAULT
	return

J_ContestHall_EventScript_CongratsWinnerLink::
	messageautoscroll J_ContestHall_Text_CongratsTrainerXandMon
	waitmessage
	return

J_ContestHall_EventScript_AudienceLookAround::
	addvar VAR_TEMP_1, 1
	lockall
	call_if_gt JOHTO_VAR_CONTEST_TYPE, (0 + 1), J_ContestHall_EventScript_VObjectAudienceLookAround
	applymovement LOCALID_CONTEST_AUDIENCE_5, J_ContestHall_Movement_AudienceMemberLookRight
	applymovement LOCALID_CONTEST_AUDIENCE_2, J_ContestHall_Movement_AudienceMemberLookDown
	applymovement LOCALID_CONTEST_AUDIENCE_3, J_ContestHall_Movement_AudienceMemberLookRight
	delay 30
	applymovement LOCALID_CONTEST_AUDIENCE_6, J_ContestHall_Movement_AudienceMemberLookLeft
	applymovement LOCALID_CONTEST_AUDIENCE_7, J_ContestHall_Movement_AudienceMemberLookDown
	applymovement LOCALID_CONTEST_AUDIENCE_1, J_ContestHall_Movement_AudienceMemberLookUp
	applymovement LOCALID_CONTEST_AUDIENCE_4, J_ContestHall_Movement_AudienceMemberLookLeft
	goto_if_ne VAR_TEMP_1, 4, J_ContestHall_EventScript_AudienceLookAround
	delay 30
	return

J_ContestHall_EventScript_VObjectAudienceLookAround::
	turnvobject LOCALID_NONE, DIR_SOUTH
	turnvobject 2, DIR_SOUTH
	turnvobject 4, DIR_EAST
	turnvobject 6, DIR_SOUTH
	turnvobject 8, DIR_SOUTH
	turnvobject 10, DIR_SOUTH
	turnvobject 12, DIR_SOUTH
	turnvobject 14, DIR_SOUTH
	turnvobject 16, DIR_SOUTH
	turnvobject 18, DIR_SOUTH
	turnvobject 20, DIR_EAST
	turnvobject 22, DIR_EAST
	turnvobject 25, DIR_EAST
	turnvobject 27, DIR_WEST
	turnvobject 28, DIR_EAST
	delay 10
	turnvobject LOCALID_NONE, DIR_EAST
	turnvobject 2, DIR_EAST
	turnvobject 4, DIR_EAST
	turnvobject 6, DIR_EAST
	turnvobject 8, DIR_EAST
	turnvobject 10, DIR_WEST
	turnvobject 12, DIR_WEST
	turnvobject 14, DIR_WEST
	turnvobject 16, DIR_WEST
	turnvobject 18, DIR_WEST
	turnvobject 20, DIR_SOUTH
	turnvobject 22, DIR_SOUTH
	turnvobject 25, DIR_NORTH
	turnvobject 27, DIR_NORTH
	turnvobject 28, DIR_NORTH
	delay 10
	turnvobject 1, DIR_NORTH
	turnvobject 3, DIR_NORTH
	turnvobject 5, DIR_NORTH
	turnvobject 7, DIR_NORTH
	turnvobject 9, DIR_EAST
	turnvobject 11, DIR_NORTH
	turnvobject 15, DIR_NORTH
	turnvobject 13, DIR_NORTH
	turnvobject 17, DIR_NORTH
	turnvobject 19, DIR_NORTH
	turnvobject 21, DIR_WEST
	turnvobject 23, DIR_WEST
	turnvobject 24, DIR_WEST
	turnvobject 26, DIR_EAST
	turnvobject 29, DIR_WEST
	turnvobject 30, DIR_WEST
	delay 10
	turnvobject 1, DIR_EAST
	turnvobject 3, DIR_EAST
	turnvobject 5, DIR_EAST
	turnvobject 7, DIR_EAST
	turnvobject 9, DIR_EAST
	turnvobject 11, DIR_WEST
	turnvobject 15, DIR_WEST
	turnvobject 13, DIR_WEST
	turnvobject 17, DIR_WEST
	turnvobject 19, DIR_WEST
	turnvobject 21, DIR_SOUTH
	turnvobject 23, DIR_SOUTH
	turnvobject 24, DIR_SOUTH
	turnvobject 26, DIR_NORTH
	turnvobject 29, DIR_NORTH
	turnvobject 30, DIR_NORTH
	delay 10
	return

J_ContestHall_EventScript_GiveWinnerPrize::
	goto_if_eq JOHTO_VAR_CONTEST_TYPE, (4 + 1), J_ContestHall_EventScript_EndLinkContest
	call J_ContestHall_EventScript_CheckShouldSkipPrize
	goto_if_set FLAG_TEMP_2, J_ContestHall_EventScript_SkipPrize
	lockall
	msgbox J_ContestHall_Text_AcceptYourPrize, MSGBOX_DEFAULT
	releaseall
	call J_ContestHall_EventScript_WinnerApproachForPrize
	call J_ContestHall_EventScript_GivePrizeIfWinner
	playse SE_M_ENCORE2
	setvar VAR_TEMP_1, 0
	call J_ContestHall_EventScript_AudienceLookAround
	delay 30
	special ShouldReadyContestArtist
	goto_if_eq VAR_0x8004, TRUE, J_ContestHall_EventScript_SetReadyForContestArtist
	return

J_ContestHall_EventScript_SkipPrize::
	lockall
	msgbox J_ContestHall_Text_CongratsPleaseCompeteAgain, MSGBOX_DEFAULT
	releaseall
	delay 90
	special ShouldReadyContestArtist
	goto_if_eq VAR_0x8004, TRUE, J_ContestHall_EventScript_SetReadyForContestArtist
	return

J_ContestHall_EventScript_CheckShouldSkipPrize::
	specialvar VAR_RESULT, HasMonWonThisContestBefore
	goto_if_eq VAR_RESULT, TRUE, J_ContestHall_EventScript_CheckPlayerWon
	return

J_ContestHall_EventScript_CheckPlayerWon::
	special GetContestWinnerId
	goto_if_eq VAR_0x8005, 3, J_ContestHall_EventScript_CheckRankIsMaster
	return

J_ContestHall_EventScript_CheckRankIsMaster::
	goto_if_eq VAR_CONTEST_RANK, CONTEST_RANK_MASTER, J_ContestHall_EventScript_DontSkipPrize
	setflag FLAG_TEMP_2
	return

J_ContestHall_EventScript_DontSkipPrize::
	return

J_ContestHall_EventScript_SetSketchFlag::
	setflag FLAG_CONTEST_SKETCH_CREATED
	return

J_ContestHall_EventScript_SetReadyForContestArtist::
	setvar JOHTO_VAR_LILYCOVE_CONTEST_LOBBY_STATE, 1
	return

J_ContestHall_EventScript_EndLinkContest::
	delay 60
	special GetContestPlayerId
	special GetContestWinnerId
	special ShouldReadyContestArtist
	goto_if_eq VAR_0x8004, TRUE, J_ContestHall_EventScript_SetReadyForLinkContestArtist
	closemessage
	return

J_ContestHall_EventScript_SetReadyForLinkContestArtist::
	setvar JOHTO_VAR_LILYCOVE_CONTEST_LOBBY_STATE, 2
	return

J_ContestHall_EventScript_Ret::
	return

J_ContestHall_EventScript_WinnerApproachForPrize::
	switch VAR_0x8005
	case 0, J_ContestHall_EventScript_Player1ApproachForPrize
	case 1, J_ContestHall_EventScript_Player2ApproachForPrize
	case 2, J_ContestHall_EventScript_Player3ApproachForPrize
	case 3, J_ContestHall_EventScript_Player4ApproachForPrize
	return

J_ContestHall_EventScript_Player1ApproachForPrize::
	lockall
	applymovement VAR_TEMP_3, J_ContestHall_Movement_Player1ApproachForPrize
	waitmovement 0
	releaseall
	return

J_ContestHall_EventScript_Player2ApproachForPrize::
	lockall
	applymovement VAR_TEMP_3, J_ContestHall_Movement_Player2ApproachForPrize
	waitmovement 0
	releaseall
	return

J_ContestHall_EventScript_Player3ApproachForPrize::
	lockall
	applymovement VAR_TEMP_3, J_ContestHall_Movement_Player3ApproachForPrize
	waitmovement 0
	releaseall
	return

J_ContestHall_EventScript_Player4ApproachForPrize::
	lockall
	applymovement VAR_TEMP_3, J_ContestHall_Movement_Player4ApproachForPrize
	waitmovement 0
	releaseall
	return

J_ContestHall_EventScript_GivePrizeIfWinner::
	special GetContestWinnerId
	goto_if_eq VAR_0x8005, 3, J_ContestHall_EventScript_GiveContestPrizes
	lockall
	msgbox J_ContestHall_Text_CongratsPleaseCompeteAgain, MSGBOX_DEFAULT
	releaseall
	return

J_ContestHall_EventScript_GiveContestPrizes::
	call_if_eq JOHTO_VAR_CONTEST_TYPE, (1 + 1), J_ContestHall_EventScript_SetSketchFlag
	specialvar VAR_RESULT, HasMonWonThisContestBefore
	goto_if_eq VAR_RESULT, FALSE, J_ContestHall_EventScript_ReceiveContestRibbon
	goto_if_eq VAR_CONTEST_RANK, CONTEST_RANK_MASTER, J_ContestHall_EventScript_GiveLuxuryBall
	lockall
	msgbox J_ContestHall_Text_CongratsPleaseCompeteAgain, MSGBOX_DEFAULT
	releaseall
	return

J_ContestHall_EventScript_NoRoomForLuxuryBall::
	lockall
	call J_Common_EventScript_BagIsFull
	msgbox J_ContestHall_Text_PickUpPrizeAtCounterLater, MSGBOX_DEFAULT
	releaseall

	setvar JOHTO_VAR_CONTEST_PRIZE_PICKUP_HNS, 4




	return

J_ContestHall_EventScript_GiveLuxuryBall::
	giveitem ITEM_LUXURY_BALL
	goto_if_eq VAR_RESULT, FALSE, J_ContestHall_EventScript_NoRoomForLuxuryBall
	lockall
	msgbox J_ContestHall_Text_CongratsPleaseCompeteAgain, MSGBOX_DEFAULT
	releaseall
	return

J_ContestHall_EventScript_ReceiveContestRibbon::
	special GiveMonContestRibbon
	incrementgamestat GAME_STAT_RECEIVED_RIBBONS
	setflag FLAG_SYS_RIBBON_GET
	lockall
	msgbox J_ContestHall_Text_ConferRibbonAsPrize, MSGBOX_DEFAULT
	playfanfare MUS_OBTAIN_ITEM
	msgbox J_ContestHall_Text_ReceivedRibbon, MSGBOX_DEFAULT
	waitfanfare
	special BufferContestWinnerMonName
	msgbox J_ContestHall_Text_PutRibbonOnMon, MSGBOX_DEFAULT
	releaseall
	return

J_ContestHall_Movement_MCWalkDown:
	walk_down
	step_end

J_ContestHall_Movement_MCBackUp:
	lock_facing_direction
	walk_up
	unlock_facing_direction
	step_end

J_ContestHall_Movement_MCFaceJudge:
	walk_in_place_faster_right
	step_end

J_ContestHall_Movement_Heart:
	emote_heart
	step_end

J_ContestHall_Movement_FaceContestants:
	walk_in_place_faster_down
	step_end

J_ContestHall_Movement_WalkStageLeft:
	walk_left
	walk_left
	walk_in_place_faster_down
	step_end

J_ContestHall_Movement_WalkStageRight:
	walk_right
	walk_right
	walk_in_place_faster_down
	step_end

J_ContestHall_Movement_WinningPlayerWalkUp:
	walk_up
	walk_in_place_faster_down
	step_end

J_ContestHall_Movement_ContestantDelay32:
	delay_16
	delay_16
	step_end

J_ContestHall_Movement_MCFaceJudge2:
	walk_in_place_faster_right
	step_end

J_ContestHall_Movement_JudgeFaceMC:
	walk_in_place_faster_left
	step_end

J_ContestHall_Movement_FaceContestants2:
	walk_in_place_faster_down
	step_end

J_ContestHall_Movement_Player3ApproachForPrize:
	walk_left
	walk_left
	walk_up
	step_end

J_ContestHall_Movement_Player4ApproachForPrize:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_up
	step_end

J_ContestHall_Movement_AudienceMemberLookLeft:
	face_left
	delay_16
	face_original_direction
	step_end

J_ContestHall_Movement_AudienceMemberLookUp:
	face_up
	delay_16
	face_original_direction
	step_end

J_ContestHall_Movement_AudienceMemberLookRight:
	face_right
	delay_16
	face_original_direction
	step_end

J_ContestHall_Movement_AudienceMemberLookDown:
	face_down
	delay_16
	face_original_direction
	step_end

J_ContestHall_Movement_Player4FaceUp:
	face_up
	step_end

J_ContestHall_Movement_MCLookAtJudge:
	face_up
	delay_16
	walk_in_place_faster_right
	step_end

J_ContestHall_Movement_JudgeLookAtMC:
	walk_in_place_faster_left
	delay_16
	delay_16
	walk_in_place_faster_down
	step_end

J_ContestHall_Movement_MCWalkInPlaceDown:
	delay_16
	delay_16
	walk_in_place_faster_down
	step_end

J_ContestHall_Movement_Player1WalkToCenter:
	walk_up
	walk_right
	walk_right
	walk_right
	walk_in_place_faster_up
	step_end

J_ContestHall_Movement_Player1WalkBack:
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_down
	walk_in_place_faster_up
	step_end

J_ContestHall_Movement_Player2WalkToCenter:
	walk_up
	walk_right
	walk_in_place_faster_up
	step_end

J_ContestHall_Movement_Player2WalkBack:
	walk_fast_left
	walk_fast_down
	walk_in_place_faster_up
	step_end

J_ContestHall_Movement_Player3WalkToCenter:
	walk_up
	walk_left
	walk_in_place_faster_up
	step_end

J_ContestHall_Movement_Player3WalkBack:
	walk_fast_right
	walk_fast_down
	walk_in_place_faster_up
	step_end

J_ContestHall_Movement_Player4WalkToCenter:
	walk_up
	walk_left
	walk_left
	walk_left
	walk_in_place_faster_up
	step_end

J_ContestHall_Movement_Player4WalkBack:
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_down
	walk_in_place_faster_up
	step_end

J_ContestHall_Movement_Player1ApproachForPrize:
	walk_right
	walk_right
	walk_up
	step_end

J_ContestHall_Movement_Player2ApproachForPrize:
	walk_up
	step_end

J_ContestHall_EventScript_CheckIfContestWithRSPlayer::
	specialvar VAR_RESULT, IsContestWithRSPlayer
	goto_if_eq VAR_RESULT, TRUE, J_ContestHall_EventScript_RetRSPlayer
	return

J_ContestHall_EventScript_RetRSPlayer::
	return

J_LilycoveCity_ContestLobby_EventScript_DelayIfContestWithRSPlayer::
	specialvar VAR_RESULT, IsContestWithRSPlayer
	goto_if_eq VAR_RESULT, TRUE, J_LilycoveCity_ContestLobby_EventScript_DelayForRSPlayer
	return

J_LilycoveCity_ContestLobby_EventScript_DelayForRSPlayer::
	delay 9
	return

J_LilycoveCity_ContestLobby_Text_ReceptionDontHavePokeblockCase:
	.string "Hello!\p"
	.string "This is the reception counter for\n"
	.string "POKéMON CONTESTS.\p"
	.string "Oh? It appears that you don't have\n"
	.string "a オカキクケ CASE yet.\p"
	.string "In that case, we need to provide you\n"
	.string "with this!$"

J_LilycoveCity_ContestLobby_Text_NowThatWeveClearedThatUp:
	.string "Okay, now that we've cleared that\n"
	.string "up…\p"
	.string "Hello!\p"
	.string "This is the reception counter for\n"
	.string "POKéMON CONTESTS.$"

J_LilycoveCity_ContestLobby_Text_ContestReception:
	.string "Hello!\p"
	.string "This is the reception counter for\n"
	.string "POKéMON CONTESTS.$"

J_LilycoveCity_ContestLobby_Text_CounterOnlyFor4PlayerContests:
	.string "Hello!\p"
	.string "This reception counter is only\n"
	.string "for 4-player POKéMON CONTESTS.$"

J_LilycoveCity_ContestLobby_Text_EnterContest1:
	.string "Would you like to enter your POKéMON\n"
	.string "in our CONTESTS?$"

J_LilycoveCity_ContestLobby_Text_WhichTopic1:
	.string "Which topic would you like?$"

J_LilycoveCity_ContestLobby_Text_ExplainContests:
	.string "A POKéMON CONTEST involves four\n"
	.string "TRAINERS entering one POKéMON each\l"
	.string "in competitive judging.\p"
	.string "A CONTEST has two stages of judging,\n"
	.string "primary and secondary.\p"
	.string "Primary judging is a popularity poll\n"
	.string "involving the audience.\p"
	.string "Secondary judging features appeals\n"
	.string "by the POKéMON using their moves.\p"
	.string "Plan appeals carefully to earn the\n"
	.string "most attention of the JUDGE and\l"
	.string "excite the audience.\l"
	.string "Do your best to stand out.\p"
	.string "The primary and secondary scores are\n"
	.string "added at the end.\p"
	.string "The POKéMON garnering the highest\n"
	.string "score is declared the winner.$"

J_LilycoveCity_ContestLobby_Text_ExplainContestTypes:
	.string "There are five kinds of CONTESTS.\p"
	.string "COOL, BEAUTY, CUTE, SMART, and\n"
	.string "TOUGH are the five categories.\p"
	.string "Choose the CONTEST that is right for\n"
	.string "the POKéMON you plan to enter.$"

J_LilycoveCity_ContestLobby_Text_ExplainContestRanks:
	.string "There are four ranks of POKéMON\n"
	.string "CONTESTS.\p"
	.string "NORMAL, SUPER, HYPER, and MASTER\n"
	.string "are the four ranks.\p"
	.string "In the NORMAL Rank, any POKéMON may\n"
	.string "enter.\p"
	.string "Any POKéMON that won a NORMAL Rank\n"
	.string "CONTEST may move up to the SUPER Rank\l"
	.string "in the same category.\p"
	.string "In the same way, a SUPER Rank winner\n"
	.string "can move up to the HYPER Rank, and\l"
	.string "a HYPER Rank winner can advance to\l"
	.string "the MASTER Rank in the same category.\p"
	.string "A POKéMON that won in the MASTER Rank\n"
	.string "may compete in the MASTER Rank as\l"
	.string "often as its TRAINER wants.$"

J_LilycoveCity_ContestLobby_Text_EnterWhichRank:
	.string "Which Rank would you like to enter?$"

J_LilycoveCity_ContestLobby_Text_EnterWhichContest1:
	.string "Which CONTEST would you like to enter?$"

J_LilycoveCity_ContestLobby_Text_EnterWhichPokemon1:
	.string "Which POKéMON would you like to enter?$"

J_LilycoveCity_ContestLobby_Text_MonNotQualifiedForRank:
	.string "I'm terribly sorry, but your POKéMON\n"
	.string "is not qualified to compete at this\l"
	.string "Rank yet…$"

J_LilycoveCity_ContestLobby_Text_EggCannotTakePart:
	.string "I'm sorry, but an EGG cannot take part\n"
	.string "in a POKéMON CONTEST.$"

J_LilycoveCity_ContestLobby_Text_MonInNoConditionForContest:
	.string "Your POKéMON appears to be in no\n"
	.string "condition to take part in a CONTEST…$"

J_LilycoveCity_ContestLobby_Text_AlreadyWonEnterAnyway:
	.string "Oh, but that RIBBON…\p"
	.string "Your POKéMON has won this CONTEST\n"
	.string "before, hasn't it?\p"
	.string "Would you like to enter it in this\n"
	.string "CONTEST anyway?$"

J_LilycoveCity_ContestLobby_Text_ConfirmContestMon:
	.string "Is that your CONTEST POKéMON?$"

J_LilycoveCity_ContestLobby_Text_YourMonIsEntryNum4:
	.string "Okay, your POKéMON will be entered\n"
	.string "in this CONTEST.\p"
	.string "Your POKéMON is Entry No. 4.\n"
	.string "The CONTEST will begin shortly.$"

J_LilycoveCity_ContestLobby_Text_ComeThroughHere:
	.string "Please come in through here.\n"
	.string "Good luck!$"

J_LilycoveCity_ContestLobby_Text_PokemonWonWeHavePrize:
	.string "Congratulations! Your POKéMON is the\n"
	.string "CONTEST winner!\p"
	.string "We have your prize right here.\n"
	.string "Please, right this way!$"

J_LilycoveCity_ContestLobby_Text_ComeBackForPrizeLater:
	.string "Please come back for your prize\n"
	.string "later on.$"

J_ContestHall_Text_GettingStartedParticipantsAsFollows:
	.string "MC: Hello! We're just getting started\n"
	.string "with a {STR_VAR_3} Rank POKéMON\l"
	.string "{STR_VAR_2}!\p"
	.string "The participating TRAINERS and their\n"
	.string "POKéMON are as follows:$"

J_ContestHall_Text_GettingStartedParticipantsAsFollowsLink:
	.string "MC: Hello! We're just getting started\n"
	.string "with a 4-player linked POKéMON\l"
	.string "{STR_VAR_2}!\p"
	.string "The participating TRAINERS and their\n"
	.string "POKéMON are as follows:$"

J_ContestHall_Text_EntryXTrainersMon:
	.string "MC: Entry No. {STR_VAR_2}!\n"
	.string "{STR_VAR_1}'s {STR_VAR_3}!$"

J_ContestHall_Text_SeenContestantsAudienceWillVote:
	.string "MC: We've just seen the four POKéMON\n"
	.string "contestants.\p"
	.string "Now it's time for primary judging!\p"
	.string "The audience will vote on their\n"
	.string "favorite POKéMON contestants.\p"
	.string "Without any further ado, let the\n"
	.string "voting begin!$"

J_ContestHall_Text_VotingUnderWay:
	.string "Voting under way…$"

J_ContestHall_Text_VotingCompleteLetsAppeal:
	.string "Voting is now complete!\p"
	.string "While the votes are being tallied,\n"
	.string "let's move on to secondary judging!\p"
	.string "The second stage of judging is the\n"
	.string "much anticipated appeal time!\p"
	.string "May the contestants amaze us with\n"
	.string "superb appeals of dazzling moves!\p"
	.string "Let's see a little enthusiasm!\n"
	.string "Let's appeal!$"

J_ContestHall_Text_ThatsItForJudging:
	.string "MC: That's it for judging!$"

J_ContestHall_Text_ThankYouForAppeals:
	.string "Thank you all for a most wonderful\n"
	.string "display of quality appeals!\p"
	.string "This concludes all judging!\n"
	.string "Thank you for your fine efforts!$"

J_ContestHall_Text_JudgeLooksReady:
	.string "Now, all that remains is the pulse-\n"
	.string "pounding proclamation of the winner.\p"
	.string "The JUDGE looks ready to make\n"
	.string "the announcement!$"

J_ContestHall_Text_WeWillNowDeclareWinner:
	.string "JUDGE: We will now declare the winner!$"

J_ContestHall_Text_CongratsTrainerXandMon:
	.string "MC: Entry No. {STR_VAR_2}!\p"
	.string "{STR_VAR_3} and {STR_VAR_1},\n"
	.string "congratulations!$"

J_ContestHall_Text_CongratsPleaseCompeteAgain:
	.string "MC: Congratulations!\n"
	.string "Please do compete again!$"

J_ContestHall_Text_AcceptYourPrize:
	.string "MC: Here you are!\n"
	.string "Please accept your prize!$"

J_ContestHall_Text_ConferRibbonAsPrize:
	.string "We confer on you this RIBBON\n"
	.string "as your prize!$"

J_ContestHall_Text_ReceivedRibbon:
	.string "{PLAYER} received a RIBBON.$"

J_ContestHall_Text_PutRibbonOnMon:
	.string "{PLAYER} put the RIBBON on\n"
	.string "{STR_VAR_1}.$"

J_ContestHall_Text_PickUpPrizeAtCounterLater:
	.string "Please pick up your prize at\n"
	.string "the reception counter later.\l"
	.string "Please do compete again!$"

J_ContestHall_Text_OnlyRegister4Players:
	.string "I only register four players for\n"
	.string "POKéMON CONTESTS.\p"
	.string "If three other players link up, all\n"
	.string "four may enter the same CONTEST.\p"
	.string "Would you like to take part?$"

J_LilycoveCity_ContestLobby_Text_ProgressWillBeSaved:
	.string "Before entering a CONTEST, your\n"
	.string "progress will be saved.$"

J_LilycoveCity_ContestLobby_Text_ParticipateAnotherTime:
	.string "We hope you will participate another\n"
	.string "time.$"

J_LilycoveCity_ContestLobby_Text_EnterContest2:
	.string "Would you like to enter a CONTEST?$"

J_LilycoveCity_ContestLobby_Text_Explain4PlayerContest:
	.string "When four players are ready, connect\n"
	.string "over a Game Link cable, and register\l"
	.string "with me, please.\p"
	.string "Please choose the same CONTEST\n"
	.string "as your fellow contestants.\p"
	.string "The CONTEST begins as soon as all\n"
	.string "players register their entry.\p"
	.string "After that, the usual CONTEST rules\n"
	.string "apply.$"

J_LilycoveCity_ContestLobby_Text_EnterWhichContest2:
	.string "Which CONTEST would you like to enter?$"

J_LilycoveCity_ContestLobby_Text_EnterWhichPokemon2:
	.string "Which POKéMON would you like to enter?$"

J_LilycoveCity_ContestLobby_Text_Transmitting:
	.string "Transmitting…$"

J_LilycoveCity_ContestLobby_Text_TransmissionError:
	.string "Transmission error…$"

J_LilycoveCity_ContestLobby_Text_PlayersChoseDifferentContest:
	.string "You may have chosen a different\n"
	.string "CONTEST than another player.$"

J_LilycoveCity_ContestLobby_Text_PlayersMadeDifferentChoice:
	.string "You may have made a different\n"
	.string "choice than another player.$"

J_LilycoveCity_ContestLobby_Text_PleaseWaitBButtonCancel:
	.string "Please wait.\n"
	.string "… … B Button: Cancel$"

J_LilycoveCity_ContestLobby_Text_ParticipateAnotherTime2:
	.string "We hope you will participate another\n"
	.string "time.$"

J_LilycoveCity_ContestLobby_Text_TransmissionErrorTryAgain:
	.string "Transmission error.\n"
	.string "Please try again.$"

J_LilycoveCity_ContestLobby_Text_YourMonIsEntryNumX:
	.string "Your POKéMON will be entered in\n"
	.string "the CONTEST.\p"
	.string "Your POKéMON is Entry No. {STR_VAR_2}.$"

J_LilycoveCity_ContestLobby_Text_ContestBeginShortly:
	.string "The CONTEST will begin shortly.$"

J_LilycoveCity_ContestLobby_Text_LinkContestReception:
	.string "Welcome! This is the POKéMON CONTEST\n"
	.string "link reception counter.\p"
	.string "You may enter CONTESTS together with\n"
	.string "one or more friends.$"

J_LilycoveCity_ContestLobby_Text_WhichTopic2:
	.string "Which topic would you like?$"

J_LilycoveCity_ContestLobby_Text_EnterContest3:
	.string "Would you like to enter a CONTEST?$"

J_LilycoveCity_ContestLobby_Text_EnterWhichContest3:
	.string "Which CONTEST would you like to enter?$"

J_LilycoveCity_ContestLobby_Text_MonInNoCondition2:
	.string "Your POKéMON appears to be in no\n"
	.string "condition to take part in a CONTEST…$"

J_LilycoveCity_ContestLobby_Text_EggCannotTakePart2:
	.string "I'm sorry, but an EGG cannot take part\n"
	.string "in a POKéMON CONTEST.$"

J_LilycoveCity_ContestLobby_Text_EnterWhichPokemon3:
	.string "Which POKéMON would you like to enter?$"

J_LilycoveCity_ContestLobby_Text_PleaseDecideLinkLeader:
	.string "Please decide which of you will\n"
	.string "become the GROUP LEADER.\p"
	.string "The other players must then choose\n"
	.string "“JOIN GROUP.”$"

J_LilycoveCity_ContestLobby_Text_PlayerAt4PCounterUseGMode:
	.string "At least one player has entered using\n"
	.string "the 4-player reception counter.\p"
	.string "There must be four players connected\n"
	.string "using a GBA Game Link cable.\p"
	.string "When the four players are ready,\n"
	.string "select G-MODE (GLOBAL MODE),\l"
	.string "then register to enter again, please.$"

J_LilycoveCity_ContestLobby_Text_ExplainLinkContest:
	.string "This is a CONTEST for two to four\n"
	.string "players linked using a Wireless\l"
	.string "Adapter or a GBA Game Link cable.\p"
	.string "Participants are first asked to choose\n"
	.string "the mode they wish to enter.\p"
	.string "There are two different modes.\p"
	.string "E-MODE (EMERALD MODE) is for\n"
	.string "two to four players, each with a\l"
	.string "POKéMON Emerald Game Pak.\p"
	.string "G-MODE (GLOBAL MODE) is only for\n"
	.string "four players, each with a POKéMON\l"
	.string "Emerald, Ruby, or Sapphire Game Pak.\p"
	.string "The players should discuss which mode\n"
	.string "they want, then choose the same mode.\p"
	.string "Once all the players have chosen\n"
	.string "the same CONTEST in the same mode,\l"
	.string "the entry registration is complete.\p"
	.string "After that, a CONTEST will start in\n"
	.string "the usual manner.$"

J_LilycoveCity_ContestLobby_Text_ExplainEMode:
	.string "In E-MODE (EMERALD MODE),\n"
	.string "a LINK CONTEST can be held with\l"
	.string "two to four players. Each player must\l"
	.string "have a POKéMON Emerald Game Pak.\p"
	.string "The players must be linked with each\n"
	.string "other using Wireless Adapters or\l"
	.string "GBA Game Link cables.\p"
	.string "If there are fewer than four players,\n"
	.string "TRAINERS in the hall will join to fill\l"
	.string "the 4-player CONTEST lineup.\p"
	.string "Please be aware that E-MODE is not\n"
	.string "available in POKéMON Ruby or Sapphire.$"

J_LilycoveCity_ContestLobby_Text_ExplainGMode:
	.string "G-MODE (GLOBAL MODE) is specifically\n"
	.string "for four players who are linked using\l"
	.string "GBA Game Link cables.\p"
	.string "Each player must have a POKéMON\n"
	.string "Emerald, Ruby, or Sapphire Game Pak.\p"
	.string "The CONTEST starts after all players\n"
	.string "choose G-MODE (POKéMON Emerald) or\l"
	.string "enter through the 4-player reception\l"
	.string "counter (POKéMON Ruby or Sapphire).$"

J_LilycoveCity_ContestLobby_Text_NoWirelessAdapterInGMode:
	.string "I'm terribly sorry.\p"
	.string "G-MODE does not function\n"
	.string "with Wireless Adapters.\p"
	.string "Please select E-MODE or try\n"
	.string "again using a GBA Game Link cable.$"

J_LilycoveCity_ContestLobby_Text_WhichContestMode:
	.string "Which CONTEST MODE would you like\n"
	.string "to enter?$"

J_ContestHall_Text_GettingStartedWireless:
	.string "MC: Hello! We're just getting started\n"
	.string "with a 4-player linked POKéMON\l"
	.string "{STR_VAR_2}!$"

J_ContestHall_Text_ParticipantsAsFollows:
	.string "The participating TRAINERS and their\n"
	.string "POKéMON are as follows:$"

J_ContestHall_Text_WeveSeenContestants:
	.string "MC: We've just seen the four POKéMON\n"
	.string "contestants.\p"
	.string "Now it's time for primary judging!$"

J_ContestHall_Text_AudienceWillVote:
	.string "The audience will vote on their\n"
	.string "favorite POKéMON contestants.$"

J_ContestHall_Text_LetVotingBegin:
	.string "Without any further ado,\n"
	.string "let the voting begin!$"

J_ContestHall_Text_VotingComplete:
	.string "Voting is now complete!\p"
	.string "While the votes are being tallied,\n"
	.string "let's move on to secondary judging!$"

J_ContestHall_Text_SecondStageOfJudging:
	.string "The second stage of judging is\n"
	.string "the much-anticipated appeal time!\p"
	.string "May the contestants amaze us with\n"
	.string "superb appeals of dazzling moves!$"

J_ContestHall_Text_LetsAppeal:
	.string "Let's see a little enthusiasm!\n"
	.string "Let's appeal!$"

