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
	.string "Thi{SE_M_GRASSWHISTLE}i{SE_M_GRASSWHISTLE}th{SE_M_REVERSAL}receptio{SE_M_ATTRACT}counte{SE_M_SAND_TOMB}for\n"
	.string "POKéMO{SE_M_PSYBEAM2}CONTESTS.\p"
	.string "Oh{SE_M_SING}I{SE_M_SPIT_UP}appear{SE_M_GRASSWHISTLE}tha{SE_M_SPIT_UP}yo{SE_M_DIVE}don'{SE_M_SPIT_UP}have\n"
	.string "{SE_M_CHARGE}{POKEBLOCK} CAS{SE_M_SWORDS_DANCE}yet.\p"
	.string "I{SE_M_ATTRACT}tha{SE_M_SPIT_UP}case{SE_M_SUPERSONIC}w{SE_M_REVERSAL}nee{SE_M_WATERFALL}t{SE_M_ATTRACT2}provid{SE_M_REVERSAL}you\n"
	.string "wit{SE_M_TRI_ATTACK}this!$"

J_LilycoveCity_ContestLobby_Text_NowThatWeveClearedThatUp:
	.string "Okay{SE_M_SUPERSONIC}no{SE_M_TWISTER}tha{SE_M_SPIT_UP}we'v{SE_M_REVERSAL}cleare{SE_M_WATERFALL}that\n"
	.string "up…\p"
	.string "Hello!\p"
	.string "Thi{SE_M_GRASSWHISTLE}i{SE_M_GRASSWHISTLE}th{SE_M_REVERSAL}receptio{SE_M_ATTRACT}counte{SE_M_SAND_TOMB}for\n"
	.string "POKéMO{SE_M_PSYBEAM2}CONTESTS.$"

J_LilycoveCity_ContestLobby_Text_ContestReception:
	.string "Hello!\p"
	.string "Thi{SE_M_GRASSWHISTLE}i{SE_M_GRASSWHISTLE}th{SE_M_REVERSAL}receptio{SE_M_ATTRACT}counte{SE_M_SAND_TOMB}for\n"
	.string "POKéMO{SE_M_PSYBEAM2}CONTESTS.$"

J_LilycoveCity_ContestLobby_Text_CounterOnlyFor4PlayerContests:
	.string "Hello!\p"
	.string "Thi{SE_M_GRASSWHISTLE}receptio{SE_M_ATTRACT}counte{SE_M_SAND_TOMB}i{SE_M_GRASSWHISTLE}only\n"
	.string "fo{SE_M_SAND_TOMB}4-playe{SE_M_SAND_TOMB}POKéMO{SE_M_PSYBEAM2}CONTESTS.$"

J_LilycoveCity_ContestLobby_Text_EnterContest1:
	.string "Woul{SE_M_WATERFALL}yo{SE_M_DIVE}lik{SE_M_REVERSAL}t{SE_M_ATTRACT2}ente{SE_M_SAND_TOMB}you{SE_M_SAND_TOMB}POKéMON\n"
	.string "i{SE_M_ATTRACT}ou{SE_M_SAND_TOMB}CONTESTS?$"

J_LilycoveCity_ContestLobby_Text_WhichTopic1:
	.string "Whic{SE_M_TRI_ATTACK}topi{SE_M_HYPER_BEAM}woul{SE_M_WATERFALL}yo{SE_M_DIVE}like?$"

J_LilycoveCity_ContestLobby_Text_ExplainContests:
	.string "{SE_M_BONEMERANG}POKéMO{SE_M_PSYBEAM2}CONTES{SE_M_SWIFT}involve{SE_M_GRASSWHISTLE}four\n"
	.string "TRAINER{SE_M_SKETCH}enterin{SE_M_SANDSTORM}on{SE_M_REVERSAL}POKéMO{SE_M_PSYBEAM2}each\l"
	.string "i{SE_M_ATTRACT}competitiv{SE_M_REVERSAL}judging.\p"
	.string "{SE_M_BONEMERANG}CONTES{SE_M_SWIFT}ha{SE_M_GRASSWHISTLE}tw{SE_M_ATTRACT2}stage{SE_M_GRASSWHISTLE}o{SE_M_ACID_ARMOR}judging,\n"
	.string "primar{SE_M_YAWN}an{SE_M_WATERFALL}secondary.\p"
	.string "Primar{SE_M_YAWN}judgin{SE_M_SANDSTORM}i{SE_M_GRASSWHISTLE}{SE_M_CHARGE}popularit{SE_M_YAWN}poll\n"
	.string "involvin{SE_M_SANDSTORM}th{SE_M_REVERSAL}audience.\p"
	.string "Secondar{SE_M_YAWN}judgin{SE_M_SANDSTORM}feature{SE_M_GRASSWHISTLE}appeals\n"
	.string "b{SE_M_YAWN}th{SE_M_REVERSAL}POKéMO{SE_M_PSYBEAM2}usin{SE_M_SANDSTORM}thei{SE_M_SAND_TOMB}moves.\p"
	.string "Pla{SE_M_ATTRACT}appeal{SE_M_GRASSWHISTLE}carefull{SE_M_YAWN}t{SE_M_ATTRACT2}ear{SE_M_ATTRACT}the\n"
	.string "mos{SE_M_SPIT_UP}attentio{SE_M_ATTRACT}o{SE_M_ACID_ARMOR}th{SE_M_REVERSAL}JUDG{SE_M_SWORDS_DANCE}and\l"
	.string "excit{SE_M_REVERSAL}th{SE_M_REVERSAL}audience.\l"
	.string "D{SE_M_ATTRACT2}you{SE_M_SAND_TOMB}bes{SE_M_SPIT_UP}t{SE_M_ATTRACT2}stan{SE_M_WATERFALL}out.\p"
	.string "Th{SE_M_REVERSAL}primar{SE_M_YAWN}an{SE_M_WATERFALL}secondar{SE_M_YAWN}score{SE_M_GRASSWHISTLE}are\n"
	.string "adde{SE_M_WATERFALL}a{SE_M_SPIT_UP}th{SE_M_REVERSAL}end.\p"
	.string "Th{SE_M_REVERSAL}POKéMO{SE_M_PSYBEAM2}garnerin{SE_M_SANDSTORM}th{SE_M_REVERSAL}highest\n"
	.string "scor{SE_M_REVERSAL}i{SE_M_GRASSWHISTLE}declare{SE_M_WATERFALL}th{SE_M_REVERSAL}winner.$"

J_LilycoveCity_ContestLobby_Text_ExplainContestTypes:
	.string "Ther{SE_M_REVERSAL}ar{SE_M_REVERSAL}fiv{SE_M_REVERSAL}kind{SE_M_GRASSWHISTLE}o{SE_M_ACID_ARMOR}CONTESTS.\p"
	.string "COOL{SE_M_SUPERSONIC}BEAUTY{SE_M_SUPERSONIC}CUTE{SE_M_SUPERSONIC}SMART{SE_M_SUPERSONIC}and\n"
	.string "TOUG{SE_M_SWAGGER2}ar{SE_M_REVERSAL}th{SE_M_REVERSAL}fiv{SE_M_REVERSAL}categories.\p"
	.string "Choos{SE_M_REVERSAL}th{SE_M_REVERSAL}CONTES{SE_M_SWIFT}tha{SE_M_SPIT_UP}i{SE_M_GRASSWHISTLE}righ{SE_M_SPIT_UP}for\n"
	.string "th{SE_M_REVERSAL}POKéMO{SE_M_PSYBEAM2}yo{SE_M_DIVE}pla{SE_M_ATTRACT}t{SE_M_ATTRACT2}enter.$"

J_LilycoveCity_ContestLobby_Text_ExplainContestRanks:
	.string "Ther{SE_M_REVERSAL}ar{SE_M_REVERSAL}fou{SE_M_SAND_TOMB}rank{SE_M_GRASSWHISTLE}o{SE_M_ACID_ARMOR}POKéMON\n"
	.string "CONTESTS.\p"
	.string "NORMAL{SE_M_SUPERSONIC}SUPER{SE_M_SUPERSONIC}HYPER{SE_M_SUPERSONIC}an{SE_M_WATERFALL}MASTER\n"
	.string "ar{SE_M_REVERSAL}th{SE_M_REVERSAL}fou{SE_M_SAND_TOMB}ranks.\p"
	.string "I{SE_M_ATTRACT}th{SE_M_REVERSAL}NORMA{SE_M_BRICK_BREAK}Rank{SE_M_SUPERSONIC}an{SE_M_YAWN}POKéMO{SE_M_PSYBEAM2}may\n"
	.string "enter.\p"
	.string "An{SE_M_YAWN}POKéMO{SE_M_PSYBEAM2}tha{SE_M_SPIT_UP}wo{SE_M_ATTRACT}{SE_M_CHARGE}NORMA{SE_M_BRICK_BREAK}Rank\n"
	.string "CONTES{SE_M_SWIFT}ma{SE_M_YAWN}mov{SE_M_REVERSAL}u{SE_M_MORNING_SUN}t{SE_M_ATTRACT2}th{SE_M_REVERSAL}SUPE{SE_M_MINIMIZE}Rank\l"
	.string "i{SE_M_ATTRACT}th{SE_M_REVERSAL}sam{SE_M_REVERSAL}category.\p"
	.string "I{SE_M_ATTRACT}th{SE_M_REVERSAL}sam{SE_M_REVERSAL}way{SE_M_SUPERSONIC}{SE_M_CHARGE}SUPE{SE_M_MINIMIZE}Ran{SE_M_ENCORE2}winner\n"
	.string "ca{SE_M_ATTRACT}mov{SE_M_REVERSAL}u{SE_M_MORNING_SUN}t{SE_M_ATTRACT2}th{SE_M_REVERSAL}HYPE{SE_M_MINIMIZE}Rank{SE_M_SUPERSONIC}and\l"
	.string "{SE_M_CHARGE}HYPE{SE_M_MINIMIZE}Ran{SE_M_ENCORE2}winne{SE_M_SAND_TOMB}ca{SE_M_ATTRACT}advanc{SE_M_REVERSAL}to\l"
	.string "th{SE_M_REVERSAL}MASTE{SE_M_MINIMIZE}Ran{SE_M_ENCORE2}i{SE_M_ATTRACT}th{SE_M_REVERSAL}sam{SE_M_REVERSAL}category.\p"
	.string "{SE_M_BONEMERANG}POKéMO{SE_M_PSYBEAM2}tha{SE_M_SPIT_UP}wo{SE_M_ATTRACT}i{SE_M_ATTRACT}th{SE_M_REVERSAL}MASTE{SE_M_MINIMIZE}Rank\n"
	.string "ma{SE_M_YAWN}compet{SE_M_REVERSAL}i{SE_M_ATTRACT}th{SE_M_REVERSAL}MASTE{SE_M_MINIMIZE}Ran{SE_M_ENCORE2}as\l"
	.string "ofte{SE_M_ATTRACT}a{SE_M_GRASSWHISTLE}it{SE_M_GRASSWHISTLE}TRAINE{SE_M_MINIMIZE}wants.$"

J_LilycoveCity_ContestLobby_Text_EnterWhichRank:
	.string "Whic{SE_M_TRI_ATTACK}Ran{SE_M_ENCORE2}woul{SE_M_WATERFALL}yo{SE_M_DIVE}lik{SE_M_REVERSAL}t{SE_M_ATTRACT2}enter?$"

J_LilycoveCity_ContestLobby_Text_EnterWhichContest1:
	.string "Whic{SE_M_TRI_ATTACK}CONTES{SE_M_SWIFT}woul{SE_M_WATERFALL}yo{SE_M_DIVE}lik{SE_M_REVERSAL}t{SE_M_ATTRACT2}enter?$"

J_LilycoveCity_ContestLobby_Text_EnterWhichPokemon1:
	.string "Whic{SE_M_TRI_ATTACK}POKéMO{SE_M_PSYBEAM2}woul{SE_M_WATERFALL}yo{SE_M_DIVE}lik{SE_M_REVERSAL}t{SE_M_ATTRACT2}enter?$"

J_LilycoveCity_ContestLobby_Text_MonNotQualifiedForRank:
	.string "I'{SE_M_MILK_DRINK}terribl{SE_M_YAWN}sorry{SE_M_SUPERSONIC}bu{SE_M_SPIT_UP}you{SE_M_SAND_TOMB}POKéMON\n"
	.string "i{SE_M_GRASSWHISTLE}no{SE_M_SPIT_UP}qualifie{SE_M_WATERFALL}t{SE_M_ATTRACT2}compet{SE_M_REVERSAL}a{SE_M_SPIT_UP}this\l"
	.string "Ran{SE_M_ENCORE2}yet…$"

J_LilycoveCity_ContestLobby_Text_EggCannotTakePart:
	.string "I'{SE_M_MILK_DRINK}sorry{SE_M_SUPERSONIC}bu{SE_M_SPIT_UP}a{SE_M_ATTRACT}EG{SE_M_SWAGGER}canno{SE_M_SPIT_UP}tak{SE_M_REVERSAL}part\n"
	.string "i{SE_M_ATTRACT}{SE_M_CHARGE}POKéMO{SE_M_PSYBEAM2}CONTEST.$"

J_LilycoveCity_ContestLobby_Text_MonInNoConditionForContest:
	.string "You{SE_M_SAND_TOMB}POKéMO{SE_M_PSYBEAM2}appear{SE_M_GRASSWHISTLE}t{SE_M_ATTRACT2}b{SE_M_REVERSAL}i{SE_M_ATTRACT}no\n"
	.string "conditio{SE_M_ATTRACT}t{SE_M_ATTRACT2}tak{SE_M_REVERSAL}par{SE_M_SPIT_UP}i{SE_M_ATTRACT}{SE_M_CHARGE}CONTEST…$"

J_LilycoveCity_ContestLobby_Text_AlreadyWonEnterAnyway:
	.string "Oh{SE_M_SUPERSONIC}bu{SE_M_SPIT_UP}tha{SE_M_SPIT_UP}RIBBON…\p"
	.string "You{SE_M_SAND_TOMB}POKéMO{SE_M_PSYBEAM2}ha{SE_M_GRASSWHISTLE}wo{SE_M_ATTRACT}thi{SE_M_GRASSWHISTLE}CONTEST\n"
	.string "before{SE_M_SUPERSONIC}hasn'{SE_M_SPIT_UP}it?\p"
	.string "Woul{SE_M_WATERFALL}yo{SE_M_DIVE}lik{SE_M_REVERSAL}t{SE_M_ATTRACT2}ente{SE_M_SAND_TOMB}i{SE_M_SPIT_UP}i{SE_M_ATTRACT}this\n"
	.string "CONTES{SE_M_SWIFT}anyway?$"

J_LilycoveCity_ContestLobby_Text_ConfirmContestMon:
	.string "I{SE_M_GRASSWHISTLE}tha{SE_M_SPIT_UP}you{SE_M_SAND_TOMB}CONTES{SE_M_SWIFT}POKéMON?$"

J_LilycoveCity_ContestLobby_Text_YourMonIsEntryNum4:
	.string "Okay{SE_M_SUPERSONIC}you{SE_M_SAND_TOMB}POKéMO{SE_M_PSYBEAM2}wil{SE_M_BATON_PASS}b{SE_M_REVERSAL}entered\n"
	.string "i{SE_M_ATTRACT}thi{SE_M_GRASSWHISTLE}CONTEST.\p"
	.string "You{SE_M_SAND_TOMB}POKéMO{SE_M_PSYBEAM2}i{SE_M_GRASSWHISTLE}Entr{SE_M_YAWN}No{SE_M_PERISH_SONG}4.\n"
	.string "Th{SE_M_REVERSAL}CONTES{SE_M_SWIFT}wil{SE_M_BATON_PASS}begi{SE_M_ATTRACT}shortly.$"

J_LilycoveCity_ContestLobby_Text_ComeThroughHere:
	.string "Pleas{SE_M_REVERSAL}com{SE_M_REVERSAL}i{SE_M_ATTRACT}throug{SE_M_TRI_ATTACK}here.\n"
	.string "Goo{SE_M_WATERFALL}luck!$"

J_LilycoveCity_ContestLobby_Text_PokemonWonWeHavePrize:
	.string "Congratulations{SE_M_DRAGON_RAGE}You{SE_M_SAND_TOMB}POKéMO{SE_M_PSYBEAM2}i{SE_M_GRASSWHISTLE}the\n"
	.string "CONTES{SE_M_SWIFT}winner!\p"
	.string "W{SE_M_REVERSAL}hav{SE_M_REVERSAL}you{SE_M_SAND_TOMB}priz{SE_M_REVERSAL}righ{SE_M_SPIT_UP}here.\n"
	.string "Please{SE_M_SUPERSONIC}righ{SE_M_SPIT_UP}thi{SE_M_GRASSWHISTLE}way!$"

J_LilycoveCity_ContestLobby_Text_ComeBackForPrizeLater:
	.string "Pleas{SE_M_REVERSAL}com{SE_M_REVERSAL}bac{SE_M_ENCORE2}fo{SE_M_SAND_TOMB}you{SE_M_SAND_TOMB}prize\n"
	.string "late{SE_M_SAND_TOMB}on.$"

J_ContestHall_Text_GettingStartedParticipantsAsFollows:
	.string "MC{SE_M_HEAT_WAVE}Hello{SE_M_DRAGON_RAGE}We'r{SE_M_REVERSAL}jus{SE_M_SPIT_UP}gettin{SE_M_SANDSTORM}started\n"
	.string "wit{SE_M_TRI_ATTACK}{SE_M_CHARGE}{STR_VAR_3} Ran{SE_M_ENCORE2}POKéMON\l"
	.string "{STR_VAR_2}!\p"
	.string "Th{SE_M_REVERSAL}participatin{SE_M_SANDSTORM}TRAINER{SE_M_SKETCH}an{SE_M_WATERFALL}their\n"
	.string "POKéMO{SE_M_PSYBEAM2}ar{SE_M_REVERSAL}a{SE_M_GRASSWHISTLE}follows:$"

J_ContestHall_Text_GettingStartedParticipantsAsFollowsLink:
	.string "MC{SE_M_HEAT_WAVE}Hello{SE_M_DRAGON_RAGE}We'r{SE_M_REVERSAL}jus{SE_M_SPIT_UP}gettin{SE_M_SANDSTORM}started\n"
	.string "wit{SE_M_TRI_ATTACK}{SE_M_CHARGE}4-playe{SE_M_SAND_TOMB}linke{SE_M_WATERFALL}POKéMON\l"
	.string "{STR_VAR_2}!\p"
	.string "Th{SE_M_REVERSAL}participatin{SE_M_SANDSTORM}TRAINER{SE_M_SKETCH}an{SE_M_WATERFALL}their\n"
	.string "POKéMO{SE_M_PSYBEAM2}ar{SE_M_REVERSAL}a{SE_M_GRASSWHISTLE}follows:$"

J_ContestHall_Text_EntryXTrainersMon:
	.string "MC{SE_M_HEAT_WAVE}Entr{SE_M_YAWN}No{SE_M_PERISH_SONG}{STR_VAR_2}!\n"
	.string "{STR_VAR_1}'{SE_M_GRASSWHISTLE}{STR_VAR_3}!$"

J_ContestHall_Text_SeenContestantsAudienceWillVote:
	.string "MC{SE_M_HEAT_WAVE}We'v{SE_M_REVERSAL}jus{SE_M_SPIT_UP}see{SE_M_ATTRACT}th{SE_M_REVERSAL}fou{SE_M_SAND_TOMB}POKéMON\n"
	.string "contestants.\p"
	.string "No{SE_M_TWISTER}it'{SE_M_GRASSWHISTLE}tim{SE_M_REVERSAL}fo{SE_M_SAND_TOMB}primar{SE_M_YAWN}judging!\p"
	.string "Th{SE_M_REVERSAL}audienc{SE_M_REVERSAL}wil{SE_M_BATON_PASS}vot{SE_M_REVERSAL}o{SE_M_ATTRACT}their\n"
	.string "favorit{SE_M_REVERSAL}POKéMO{SE_M_PSYBEAM2}contestants.\p"
	.string "Withou{SE_M_SPIT_UP}an{SE_M_YAWN}furthe{SE_M_SAND_TOMB}ado{SE_M_SUPERSONIC}le{SE_M_SPIT_UP}the\n"
	.string "votin{SE_M_SANDSTORM}begin!$"

J_ContestHall_Text_VotingUnderWay:
	.string "Votin{SE_M_SANDSTORM}unde{SE_M_SAND_TOMB}way…$"

J_ContestHall_Text_VotingCompleteLetsAppeal:
	.string "Votin{SE_M_SANDSTORM}i{SE_M_GRASSWHISTLE}no{SE_M_TWISTER}complete!\p"
	.string "Whil{SE_M_REVERSAL}th{SE_M_REVERSAL}vote{SE_M_GRASSWHISTLE}ar{SE_M_REVERSAL}bein{SE_M_SANDSTORM}tallied,\n"
	.string "let'{SE_M_GRASSWHISTLE}mov{SE_M_REVERSAL}o{SE_M_ATTRACT}t{SE_M_ATTRACT2}secondar{SE_M_YAWN}judging!\p"
	.string "Th{SE_M_REVERSAL}secon{SE_M_WATERFALL}stag{SE_M_REVERSAL}o{SE_M_ACID_ARMOR}judgin{SE_M_SANDSTORM}i{SE_M_GRASSWHISTLE}the\n"
	.string "muc{SE_M_TRI_ATTACK}anticipate{SE_M_WATERFALL}appea{SE_M_BATON_PASS}time!\p"
	.string "Ma{SE_M_YAWN}th{SE_M_REVERSAL}contestant{SE_M_GRASSWHISTLE}amaz{SE_M_REVERSAL}u{SE_M_GRASSWHISTLE}with\n"
	.string "super{SE_M_STRENGTH}appeal{SE_M_GRASSWHISTLE}o{SE_M_ACID_ARMOR}dazzlin{SE_M_SANDSTORM}moves!\p"
	.string "Let'{SE_M_GRASSWHISTLE}se{SE_M_REVERSAL}{SE_M_CHARGE}littl{SE_M_REVERSAL}enthusiasm!\n"
	.string "Let'{SE_M_GRASSWHISTLE}appeal!$"

J_ContestHall_Text_ThatsItForJudging:
	.string "MC{SE_M_HEAT_WAVE}That'{SE_M_GRASSWHISTLE}i{SE_M_SPIT_UP}fo{SE_M_SAND_TOMB}judging!$"

J_ContestHall_Text_ThankYouForAppeals:
	.string "Than{SE_M_ENCORE2}yo{SE_M_DIVE}al{SE_M_BATON_PASS}fo{SE_M_SAND_TOMB}{SE_M_CHARGE}mos{SE_M_SPIT_UP}wonderful\n"
	.string "displa{SE_M_YAWN}o{SE_M_ACID_ARMOR}qualit{SE_M_YAWN}appeals!\p"
	.string "Thi{SE_M_GRASSWHISTLE}conclude{SE_M_GRASSWHISTLE}al{SE_M_BATON_PASS}judging!\n"
	.string "Than{SE_M_ENCORE2}yo{SE_M_DIVE}fo{SE_M_SAND_TOMB}you{SE_M_SAND_TOMB}fin{SE_M_REVERSAL}efforts!$"

J_ContestHall_Text_JudgeLooksReady:
	.string "Now{SE_M_SUPERSONIC}al{SE_M_BATON_PASS}tha{SE_M_SPIT_UP}remain{SE_M_GRASSWHISTLE}i{SE_M_GRASSWHISTLE}th{SE_M_REVERSAL}pulse-\n"
	.string "poundin{SE_M_SANDSTORM}proclamatio{SE_M_ATTRACT}o{SE_M_ACID_ARMOR}th{SE_M_REVERSAL}winner.\p"
	.string "Th{SE_M_REVERSAL}JUDG{SE_M_SWORDS_DANCE}look{SE_M_GRASSWHISTLE}read{SE_M_YAWN}t{SE_M_ATTRACT2}make\n"
	.string "th{SE_M_REVERSAL}announcement!$"

J_ContestHall_Text_WeWillNowDeclareWinner:
	.string "JUDGE{SE_M_HEAT_WAVE}W{SE_M_REVERSAL}wil{SE_M_BATON_PASS}no{SE_M_TWISTER}declar{SE_M_REVERSAL}th{SE_M_REVERSAL}winner!$"

J_ContestHall_Text_CongratsTrainerXandMon:
	.string "MC{SE_M_HEAT_WAVE}Entr{SE_M_YAWN}No{SE_M_PERISH_SONG}{STR_VAR_2}!\p"
	.string "{STR_VAR_3} an{SE_M_WATERFALL}{STR_VAR_1},\n"
	.string "congratulations!$"

J_ContestHall_Text_CongratsPleaseCompeteAgain:
	.string "MC{SE_M_HEAT_WAVE}Congratulations!\n"
	.string "Pleas{SE_M_REVERSAL}d{SE_M_ATTRACT2}compet{SE_M_REVERSAL}again!$"

J_ContestHall_Text_AcceptYourPrize:
	.string "MC{SE_M_HEAT_WAVE}Her{SE_M_REVERSAL}yo{SE_M_DIVE}are!\n"
	.string "Pleas{SE_M_REVERSAL}accep{SE_M_SPIT_UP}you{SE_M_SAND_TOMB}prize!$"

J_ContestHall_Text_ConferRibbonAsPrize:
	.string "W{SE_M_REVERSAL}confe{SE_M_SAND_TOMB}o{SE_M_ATTRACT}yo{SE_M_DIVE}thi{SE_M_GRASSWHISTLE}RIBBON\n"
	.string "a{SE_M_GRASSWHISTLE}you{SE_M_SAND_TOMB}prize!$"

J_ContestHall_Text_ReceivedRibbon:
	.string "{PLAYER} receive{SE_M_WATERFALL}{SE_M_CHARGE}RIBBON.$"

J_ContestHall_Text_PutRibbonOnMon:
	.string "{PLAYER} pu{SE_M_SPIT_UP}th{SE_M_REVERSAL}RIBBO{SE_M_PSYBEAM2}on\n"
	.string "{STR_VAR_1}.$"

J_ContestHall_Text_PickUpPrizeAtCounterLater:
	.string "Pleas{SE_M_REVERSAL}pic{SE_M_ENCORE2}u{SE_M_MORNING_SUN}you{SE_M_SAND_TOMB}priz{SE_M_REVERSAL}at\n"
	.string "th{SE_M_REVERSAL}receptio{SE_M_ATTRACT}counte{SE_M_SAND_TOMB}later.\l"
	.string "Pleas{SE_M_REVERSAL}d{SE_M_ATTRACT2}compet{SE_M_REVERSAL}again!$"

J_ContestHall_Text_OnlyRegister4Players:
	.string "{SE_M_HEAL_BELL}onl{SE_M_YAWN}registe{SE_M_SAND_TOMB}fou{SE_M_SAND_TOMB}player{SE_M_GRASSWHISTLE}for\n"
	.string "POKéMO{SE_M_PSYBEAM2}CONTESTS.\p"
	.string "I{SE_M_ACID_ARMOR}thre{SE_M_REVERSAL}othe{SE_M_SAND_TOMB}player{SE_M_GRASSWHISTLE}lin{SE_M_ENCORE2}up{SE_M_SUPERSONIC}all\n"
	.string "fou{SE_M_SAND_TOMB}ma{SE_M_YAWN}ente{SE_M_SAND_TOMB}th{SE_M_REVERSAL}sam{SE_M_REVERSAL}CONTEST.\p"
	.string "Woul{SE_M_WATERFALL}yo{SE_M_DIVE}lik{SE_M_REVERSAL}t{SE_M_ATTRACT2}tak{SE_M_REVERSAL}part?$"

J_LilycoveCity_ContestLobby_Text_ProgressWillBeSaved:
	.string "Befor{SE_M_REVERSAL}enterin{SE_M_SANDSTORM}{SE_M_CHARGE}CONTEST{SE_M_SUPERSONIC}your\n"
	.string "progres{SE_M_GRASSWHISTLE}wil{SE_M_BATON_PASS}b{SE_M_REVERSAL}saved.$"

J_LilycoveCity_ContestLobby_Text_ParticipateAnotherTime:
	.string "W{SE_M_REVERSAL}hop{SE_M_REVERSAL}yo{SE_M_DIVE}wil{SE_M_BATON_PASS}participat{SE_M_REVERSAL}another\n"
	.string "time.$"

J_LilycoveCity_ContestLobby_Text_EnterContest2:
	.string "Woul{SE_M_WATERFALL}yo{SE_M_DIVE}lik{SE_M_REVERSAL}t{SE_M_ATTRACT2}ente{SE_M_SAND_TOMB}{SE_M_CHARGE}CONTEST?$"

J_LilycoveCity_ContestLobby_Text_Explain4PlayerContest:
	.string "Whe{SE_M_ATTRACT}fou{SE_M_SAND_TOMB}player{SE_M_GRASSWHISTLE}ar{SE_M_REVERSAL}ready{SE_M_SUPERSONIC}connect\n"
	.string "ove{SE_M_SAND_TOMB}{SE_M_CHARGE}Gam{SE_M_REVERSAL}Lin{SE_M_ENCORE2}cable{SE_M_SUPERSONIC}an{SE_M_WATERFALL}register\l"
	.string "wit{SE_M_TRI_ATTACK}me{SE_M_SUPERSONIC}please.\p"
	.string "Pleas{SE_M_REVERSAL}choos{SE_M_REVERSAL}th{SE_M_REVERSAL}sam{SE_M_REVERSAL}CONTEST\n"
	.string "a{SE_M_GRASSWHISTLE}you{SE_M_SAND_TOMB}fello{SE_M_TWISTER}contestants.\p"
	.string "Th{SE_M_REVERSAL}CONTES{SE_M_SWIFT}begin{SE_M_GRASSWHISTLE}a{SE_M_GRASSWHISTLE}soo{SE_M_ATTRACT}a{SE_M_GRASSWHISTLE}all\n"
	.string "player{SE_M_GRASSWHISTLE}registe{SE_M_SAND_TOMB}thei{SE_M_SAND_TOMB}entry.\p"
	.string "Afte{SE_M_SAND_TOMB}that{SE_M_SUPERSONIC}th{SE_M_REVERSAL}usua{SE_M_BATON_PASS}CONTES{SE_M_SWIFT}rules\n"
	.string "apply.$"

J_LilycoveCity_ContestLobby_Text_EnterWhichContest2:
	.string "Whic{SE_M_TRI_ATTACK}CONTES{SE_M_SWIFT}woul{SE_M_WATERFALL}yo{SE_M_DIVE}lik{SE_M_REVERSAL}t{SE_M_ATTRACT2}enter?$"

J_LilycoveCity_ContestLobby_Text_EnterWhichPokemon2:
	.string "Whic{SE_M_TRI_ATTACK}POKéMO{SE_M_PSYBEAM2}woul{SE_M_WATERFALL}yo{SE_M_DIVE}lik{SE_M_REVERSAL}t{SE_M_ATTRACT2}enter?$"

J_LilycoveCity_ContestLobby_Text_Transmitting:
	.string "Transmitting…$"

J_LilycoveCity_ContestLobby_Text_TransmissionError:
	.string "Transmissio{SE_M_ATTRACT}error…$"

J_LilycoveCity_ContestLobby_Text_PlayersChoseDifferentContest:
	.string "Yo{SE_M_DIVE}ma{SE_M_YAWN}hav{SE_M_REVERSAL}chose{SE_M_ATTRACT}{SE_M_CHARGE}different\n"
	.string "CONTES{SE_M_SWIFT}tha{SE_M_ATTRACT}anothe{SE_M_SAND_TOMB}player.$"

J_LilycoveCity_ContestLobby_Text_PlayersMadeDifferentChoice:
	.string "Yo{SE_M_DIVE}ma{SE_M_YAWN}hav{SE_M_REVERSAL}mad{SE_M_REVERSAL}{SE_M_CHARGE}different\n"
	.string "choic{SE_M_REVERSAL}tha{SE_M_ATTRACT}anothe{SE_M_SAND_TOMB}player.$"

J_LilycoveCity_ContestLobby_Text_PleaseWaitBButtonCancel:
	.string "Pleas{SE_M_REVERSAL}wait.\n"
	.string "{SE_M_DIZZY_PUNCH}{SE_M_DIZZY_PUNCH}{SE_M_LICK}Button{SE_M_HEAT_WAVE}Cancel$"

J_LilycoveCity_ContestLobby_Text_ParticipateAnotherTime2:
	.string "W{SE_M_REVERSAL}hop{SE_M_REVERSAL}yo{SE_M_DIVE}wil{SE_M_BATON_PASS}participat{SE_M_REVERSAL}another\n"
	.string "time.$"

J_LilycoveCity_ContestLobby_Text_TransmissionErrorTryAgain:
	.string "Transmissio{SE_M_ATTRACT}error.\n"
	.string "Pleas{SE_M_REVERSAL}tr{SE_M_YAWN}again.$"

J_LilycoveCity_ContestLobby_Text_YourMonIsEntryNumX:
	.string "You{SE_M_SAND_TOMB}POKéMO{SE_M_PSYBEAM2}wil{SE_M_BATON_PASS}b{SE_M_REVERSAL}entere{SE_M_WATERFALL}in\n"
	.string "th{SE_M_REVERSAL}CONTEST.\p"
	.string "You{SE_M_SAND_TOMB}POKéMO{SE_M_PSYBEAM2}i{SE_M_GRASSWHISTLE}Entr{SE_M_YAWN}No{SE_M_PERISH_SONG}{STR_VAR_2}.$"

J_LilycoveCity_ContestLobby_Text_ContestBeginShortly:
	.string "Th{SE_M_REVERSAL}CONTES{SE_M_SWIFT}wil{SE_M_BATON_PASS}begi{SE_M_ATTRACT}shortly.$"

J_LilycoveCity_ContestLobby_Text_LinkContestReception:
	.string "Welcome{SE_M_DRAGON_RAGE}Thi{SE_M_GRASSWHISTLE}i{SE_M_GRASSWHISTLE}th{SE_M_REVERSAL}POKéMO{SE_M_PSYBEAM2}CONTEST\n"
	.string "lin{SE_M_ENCORE2}receptio{SE_M_ATTRACT}counter.\p"
	.string "Yo{SE_M_DIVE}ma{SE_M_YAWN}ente{SE_M_SAND_TOMB}CONTEST{SE_M_SKETCH}togethe{SE_M_SAND_TOMB}with\n"
	.string "on{SE_M_REVERSAL}o{SE_M_SAND_TOMB}mor{SE_M_REVERSAL}friends.$"

J_LilycoveCity_ContestLobby_Text_WhichTopic2:
	.string "Whic{SE_M_TRI_ATTACK}topi{SE_M_HYPER_BEAM}woul{SE_M_WATERFALL}yo{SE_M_DIVE}like?$"

J_LilycoveCity_ContestLobby_Text_EnterContest3:
	.string "Woul{SE_M_WATERFALL}yo{SE_M_DIVE}lik{SE_M_REVERSAL}t{SE_M_ATTRACT2}ente{SE_M_SAND_TOMB}{SE_M_CHARGE}CONTEST?$"

J_LilycoveCity_ContestLobby_Text_EnterWhichContest3:
	.string "Whic{SE_M_TRI_ATTACK}CONTES{SE_M_SWIFT}woul{SE_M_WATERFALL}yo{SE_M_DIVE}lik{SE_M_REVERSAL}t{SE_M_ATTRACT2}enter?$"

J_LilycoveCity_ContestLobby_Text_MonInNoCondition2:
	.string "You{SE_M_SAND_TOMB}POKéMO{SE_M_PSYBEAM2}appear{SE_M_GRASSWHISTLE}t{SE_M_ATTRACT2}b{SE_M_REVERSAL}i{SE_M_ATTRACT}no\n"
	.string "conditio{SE_M_ATTRACT}t{SE_M_ATTRACT2}tak{SE_M_REVERSAL}par{SE_M_SPIT_UP}i{SE_M_ATTRACT}{SE_M_CHARGE}CONTEST…$"

J_LilycoveCity_ContestLobby_Text_EggCannotTakePart2:
	.string "I'{SE_M_MILK_DRINK}sorry{SE_M_SUPERSONIC}bu{SE_M_SPIT_UP}a{SE_M_ATTRACT}EG{SE_M_SWAGGER}canno{SE_M_SPIT_UP}tak{SE_M_REVERSAL}part\n"
	.string "i{SE_M_ATTRACT}{SE_M_CHARGE}POKéMO{SE_M_PSYBEAM2}CONTEST.$"

J_LilycoveCity_ContestLobby_Text_EnterWhichPokemon3:
	.string "Whic{SE_M_TRI_ATTACK}POKéMO{SE_M_PSYBEAM2}woul{SE_M_WATERFALL}yo{SE_M_DIVE}lik{SE_M_REVERSAL}t{SE_M_ATTRACT2}enter?$"

J_LilycoveCity_ContestLobby_Text_PleaseDecideLinkLeader:
	.string "Pleas{SE_M_REVERSAL}decid{SE_M_REVERSAL}whic{SE_M_TRI_ATTACK}o{SE_M_ACID_ARMOR}yo{SE_M_DIVE}will\n"
	.string "becom{SE_M_REVERSAL}th{SE_M_REVERSAL}GROU{SE_M_PETAL_DANCE}LEADER.\p"
	.string "Th{SE_M_REVERSAL}othe{SE_M_SAND_TOMB}player{SE_M_GRASSWHISTLE}mus{SE_M_SPIT_UP}the{SE_M_ATTRACT}choose\n"
	.string "“JOI{SE_M_PSYBEAM2}GROUP.”$"

J_LilycoveCity_ContestLobby_Text_PlayerAt4PCounterUseGMode:
	.string "A{SE_M_SPIT_UP}leas{SE_M_SPIT_UP}on{SE_M_REVERSAL}playe{SE_M_SAND_TOMB}ha{SE_M_GRASSWHISTLE}entere{SE_M_WATERFALL}using\n"
	.string "th{SE_M_REVERSAL}4-playe{SE_M_SAND_TOMB}receptio{SE_M_ATTRACT}counter.\p"
	.string "Ther{SE_M_REVERSAL}mus{SE_M_SPIT_UP}b{SE_M_REVERSAL}fou{SE_M_SAND_TOMB}player{SE_M_GRASSWHISTLE}connected\n"
	.string "usin{SE_M_SANDSTORM}{SE_M_CHARGE}GB{SE_M_BONEMERANG}Gam{SE_M_REVERSAL}Lin{SE_M_ENCORE2}cable.\p"
	.string "Whe{SE_M_ATTRACT}th{SE_M_REVERSAL}fou{SE_M_SAND_TOMB}player{SE_M_GRASSWHISTLE}ar{SE_M_REVERSAL}ready,\n"
	.string "selec{SE_M_SPIT_UP}G-MOD{SE_M_SWORDS_DANCE}(GLOBA{SE_M_BRICK_BREAK}MODE),\l"
	.string "the{SE_M_ATTRACT}registe{SE_M_SAND_TOMB}t{SE_M_ATTRACT2}ente{SE_M_SAND_TOMB}again{SE_M_SUPERSONIC}please.$"

J_LilycoveCity_ContestLobby_Text_ExplainLinkContest:
	.string "Thi{SE_M_GRASSWHISTLE}i{SE_M_GRASSWHISTLE}{SE_M_CHARGE}CONTES{SE_M_SWIFT}fo{SE_M_SAND_TOMB}tw{SE_M_ATTRACT2}t{SE_M_ATTRACT2}four\n"
	.string "player{SE_M_GRASSWHISTLE}linke{SE_M_WATERFALL}usin{SE_M_SANDSTORM}{SE_M_CHARGE}Wireless\l"
	.string "Adapte{SE_M_SAND_TOMB}o{SE_M_SAND_TOMB}{SE_M_CHARGE}GB{SE_M_BONEMERANG}Gam{SE_M_REVERSAL}Lin{SE_M_ENCORE2}cable.\p"
	.string "Participant{SE_M_GRASSWHISTLE}ar{SE_M_REVERSAL}firs{SE_M_SPIT_UP}aske{SE_M_WATERFALL}t{SE_M_ATTRACT2}choose\n"
	.string "th{SE_M_REVERSAL}mod{SE_M_REVERSAL}the{SE_M_YAWN}wis{SE_M_TRI_ATTACK}t{SE_M_ATTRACT2}enter.\p"
	.string "Ther{SE_M_REVERSAL}ar{SE_M_REVERSAL}tw{SE_M_ATTRACT2}differen{SE_M_SPIT_UP}modes.\p"
	.string "E-MOD{SE_M_SWORDS_DANCE}(EMERAL{SE_M_FAINT_ATTACK}MODE{SE_ROULETTE_BALL2}i{SE_M_GRASSWHISTLE}for\n"
	.string "tw{SE_M_ATTRACT2}t{SE_M_ATTRACT2}fou{SE_M_SAND_TOMB}players{SE_M_SUPERSONIC}eac{SE_M_TRI_ATTACK}wit{SE_M_TRI_ATTACK}a\l"
	.string "POKéMO{SE_M_PSYBEAM2}Emeral{SE_M_WATERFALL}Gam{SE_M_REVERSAL}Pak.\p"
	.string "G-MOD{SE_M_SWORDS_DANCE}(GLOBA{SE_M_BRICK_BREAK}MODE{SE_ROULETTE_BALL2}i{SE_M_GRASSWHISTLE}onl{SE_M_YAWN}for\n"
	.string "fou{SE_M_SAND_TOMB}players{SE_M_SUPERSONIC}eac{SE_M_TRI_ATTACK}wit{SE_M_TRI_ATTACK}{SE_M_CHARGE}POKéMON\l"
	.string "Emerald{SE_M_SUPERSONIC}Ruby{SE_M_SUPERSONIC}o{SE_M_SAND_TOMB}Sapphir{SE_M_REVERSAL}Gam{SE_M_REVERSAL}Pak.\p"
	.string "Th{SE_M_REVERSAL}player{SE_M_GRASSWHISTLE}shoul{SE_M_WATERFALL}discus{SE_M_GRASSWHISTLE}whic{SE_M_TRI_ATTACK}mode\n"
	.string "the{SE_M_YAWN}want{SE_M_SUPERSONIC}the{SE_M_ATTRACT}choos{SE_M_REVERSAL}th{SE_M_REVERSAL}sam{SE_M_REVERSAL}mode.\p"
	.string "Onc{SE_M_REVERSAL}al{SE_M_BATON_PASS}th{SE_M_REVERSAL}player{SE_M_GRASSWHISTLE}hav{SE_M_REVERSAL}chosen\n"
	.string "th{SE_M_REVERSAL}sam{SE_M_REVERSAL}CONTES{SE_M_SWIFT}i{SE_M_ATTRACT}th{SE_M_REVERSAL}sam{SE_M_REVERSAL}mode,\l"
	.string "th{SE_M_REVERSAL}entr{SE_M_YAWN}registratio{SE_M_ATTRACT}i{SE_M_GRASSWHISTLE}complete.\p"
	.string "Afte{SE_M_SAND_TOMB}that{SE_M_SUPERSONIC}{SE_M_CHARGE}CONTES{SE_M_SWIFT}wil{SE_M_BATON_PASS}star{SE_M_SPIT_UP}in\n"
	.string "th{SE_M_REVERSAL}usua{SE_M_BATON_PASS}manner.$"

J_LilycoveCity_ContestLobby_Text_ExplainEMode:
	.string "I{SE_M_ATTRACT}E-MOD{SE_M_SWORDS_DANCE}(EMERAL{SE_M_FAINT_ATTACK}MODE),\n"
	.string "{SE_M_CHARGE}LIN{SE_M_SNORE}CONTES{SE_M_SWIFT}ca{SE_M_ATTRACT}b{SE_M_REVERSAL}hel{SE_M_WATERFALL}with\l"
	.string "tw{SE_M_ATTRACT2}t{SE_M_ATTRACT2}fou{SE_M_SAND_TOMB}players{SE_M_PERISH_SONG}Eac{SE_M_TRI_ATTACK}playe{SE_M_SAND_TOMB}must\l"
	.string "hav{SE_M_REVERSAL}{SE_M_CHARGE}POKéMO{SE_M_PSYBEAM2}Emeral{SE_M_WATERFALL}Gam{SE_M_REVERSAL}Pak.\p"
	.string "Th{SE_M_REVERSAL}player{SE_M_GRASSWHISTLE}mus{SE_M_SPIT_UP}b{SE_M_REVERSAL}linke{SE_M_WATERFALL}wit{SE_M_TRI_ATTACK}each\n"
	.string "othe{SE_M_SAND_TOMB}usin{SE_M_SANDSTORM}Wireles{SE_M_GRASSWHISTLE}Adapter{SE_M_GRASSWHISTLE}or\l"
	.string "GB{SE_M_BONEMERANG}Gam{SE_M_REVERSAL}Lin{SE_M_ENCORE2}cables.\p"
	.string "I{SE_M_ACID_ARMOR}ther{SE_M_REVERSAL}ar{SE_M_REVERSAL}fewe{SE_M_SAND_TOMB}tha{SE_M_ATTRACT}fou{SE_M_SAND_TOMB}players,\n"
	.string "TRAINER{SE_M_SKETCH}i{SE_M_ATTRACT}th{SE_M_REVERSAL}hal{SE_M_BATON_PASS}wil{SE_M_BATON_PASS}joi{SE_M_ATTRACT}t{SE_M_ATTRACT2}fill\l"
	.string "th{SE_M_REVERSAL}4-playe{SE_M_SAND_TOMB}CONTES{SE_M_SWIFT}lineup.\p"
	.string "Pleas{SE_M_REVERSAL}b{SE_M_REVERSAL}awar{SE_M_REVERSAL}tha{SE_M_SPIT_UP}E-MOD{SE_M_SWORDS_DANCE}i{SE_M_GRASSWHISTLE}not\n"
	.string "availabl{SE_M_REVERSAL}i{SE_M_ATTRACT}POKéMO{SE_M_PSYBEAM2}Rub{SE_M_YAWN}o{SE_M_SAND_TOMB}Sapphire.$"

J_LilycoveCity_ContestLobby_Text_ExplainGMode:
	.string "G-MOD{SE_M_SWORDS_DANCE}(GLOBA{SE_M_BRICK_BREAK}MODE{SE_ROULETTE_BALL2}i{SE_M_GRASSWHISTLE}specifically\n"
	.string "fo{SE_M_SAND_TOMB}fou{SE_M_SAND_TOMB}player{SE_M_GRASSWHISTLE}wh{SE_M_ATTRACT2}ar{SE_M_REVERSAL}linke{SE_M_WATERFALL}using\l"
	.string "GB{SE_M_BONEMERANG}Gam{SE_M_REVERSAL}Lin{SE_M_ENCORE2}cables.\p"
	.string "Eac{SE_M_TRI_ATTACK}playe{SE_M_SAND_TOMB}mus{SE_M_SPIT_UP}hav{SE_M_REVERSAL}{SE_M_CHARGE}POKéMON\n"
	.string "Emerald{SE_M_SUPERSONIC}Ruby{SE_M_SUPERSONIC}o{SE_M_SAND_TOMB}Sapphir{SE_M_REVERSAL}Gam{SE_M_REVERSAL}Pak.\p"
	.string "Th{SE_M_REVERSAL}CONTES{SE_M_SWIFT}start{SE_M_GRASSWHISTLE}afte{SE_M_SAND_TOMB}al{SE_M_BATON_PASS}players\n"
	.string "choos{SE_M_REVERSAL}G-MOD{SE_M_SWORDS_DANCE}(POKéMO{SE_M_PSYBEAM2}Emerald{SE_ROULETTE_BALL2}or\l"
	.string "ente{SE_M_SAND_TOMB}throug{SE_M_TRI_ATTACK}th{SE_M_REVERSAL}4-playe{SE_M_SAND_TOMB}reception\l"
	.string "counte{SE_M_SAND_TOMB}(POKéMO{SE_M_PSYBEAM2}Rub{SE_M_YAWN}o{SE_M_SAND_TOMB}Sapphire).$"

J_LilycoveCity_ContestLobby_Text_NoWirelessAdapterInGMode:
	.string "I'{SE_M_MILK_DRINK}terribl{SE_M_YAWN}sorry.\p"
	.string "G-MOD{SE_M_SWORDS_DANCE}doe{SE_M_GRASSWHISTLE}no{SE_M_SPIT_UP}function\n"
	.string "wit{SE_M_TRI_ATTACK}Wireles{SE_M_GRASSWHISTLE}Adapters.\p"
	.string "Pleas{SE_M_REVERSAL}selec{SE_M_SPIT_UP}E-MOD{SE_M_SWORDS_DANCE}o{SE_M_SAND_TOMB}try\n"
	.string "agai{SE_M_ATTRACT}usin{SE_M_SANDSTORM}{SE_M_CHARGE}GB{SE_M_BONEMERANG}Gam{SE_M_REVERSAL}Lin{SE_M_ENCORE2}cable.$"

J_LilycoveCity_ContestLobby_Text_WhichContestMode:
	.string "Whic{SE_M_TRI_ATTACK}CONTES{SE_M_SWIFT}MOD{SE_M_SWORDS_DANCE}woul{SE_M_WATERFALL}yo{SE_M_DIVE}like\n"
	.string "t{SE_M_ATTRACT2}enter?$"

J_ContestHall_Text_GettingStartedWireless:
	.string "MC{SE_M_HEAT_WAVE}Hello{SE_M_DRAGON_RAGE}We'r{SE_M_REVERSAL}jus{SE_M_SPIT_UP}gettin{SE_M_SANDSTORM}started\n"
	.string "wit{SE_M_TRI_ATTACK}{SE_M_CHARGE}4-playe{SE_M_SAND_TOMB}linke{SE_M_WATERFALL}POKéMON\l"
	.string "{STR_VAR_2}!$"

J_ContestHall_Text_ParticipantsAsFollows:
	.string "Th{SE_M_REVERSAL}participatin{SE_M_SANDSTORM}TRAINER{SE_M_SKETCH}an{SE_M_WATERFALL}their\n"
	.string "POKéMO{SE_M_PSYBEAM2}ar{SE_M_REVERSAL}a{SE_M_GRASSWHISTLE}follows:$"

J_ContestHall_Text_WeveSeenContestants:
	.string "MC{SE_M_HEAT_WAVE}We'v{SE_M_REVERSAL}jus{SE_M_SPIT_UP}see{SE_M_ATTRACT}th{SE_M_REVERSAL}fou{SE_M_SAND_TOMB}POKéMON\n"
	.string "contestants.\p"
	.string "No{SE_M_TWISTER}it'{SE_M_GRASSWHISTLE}tim{SE_M_REVERSAL}fo{SE_M_SAND_TOMB}primar{SE_M_YAWN}judging!$"

J_ContestHall_Text_AudienceWillVote:
	.string "Th{SE_M_REVERSAL}audienc{SE_M_REVERSAL}wil{SE_M_BATON_PASS}vot{SE_M_REVERSAL}o{SE_M_ATTRACT}their\n"
	.string "favorit{SE_M_REVERSAL}POKéMO{SE_M_PSYBEAM2}contestants.$"

J_ContestHall_Text_LetVotingBegin:
	.string "Withou{SE_M_SPIT_UP}an{SE_M_YAWN}furthe{SE_M_SAND_TOMB}ado,\n"
	.string "le{SE_M_SPIT_UP}th{SE_M_REVERSAL}votin{SE_M_SANDSTORM}begin!$"

J_ContestHall_Text_VotingComplete:
	.string "Votin{SE_M_SANDSTORM}i{SE_M_GRASSWHISTLE}no{SE_M_TWISTER}complete!\p"
	.string "Whil{SE_M_REVERSAL}th{SE_M_REVERSAL}vote{SE_M_GRASSWHISTLE}ar{SE_M_REVERSAL}bein{SE_M_SANDSTORM}tallied,\n"
	.string "let'{SE_M_GRASSWHISTLE}mov{SE_M_REVERSAL}o{SE_M_ATTRACT}t{SE_M_ATTRACT2}secondar{SE_M_YAWN}judging!$"

J_ContestHall_Text_SecondStageOfJudging:
	.string "Th{SE_M_REVERSAL}secon{SE_M_WATERFALL}stag{SE_M_REVERSAL}o{SE_M_ACID_ARMOR}judgin{SE_M_SANDSTORM}is\n"
	.string "th{SE_M_REVERSAL}much-anticipate{SE_M_WATERFALL}appea{SE_M_BATON_PASS}time!\p"
	.string "Ma{SE_M_YAWN}th{SE_M_REVERSAL}contestant{SE_M_GRASSWHISTLE}amaz{SE_M_REVERSAL}u{SE_M_GRASSWHISTLE}with\n"
	.string "super{SE_M_STRENGTH}appeal{SE_M_GRASSWHISTLE}o{SE_M_ACID_ARMOR}dazzlin{SE_M_SANDSTORM}moves!$"

J_ContestHall_Text_LetsAppeal:
	.string "Let'{SE_M_GRASSWHISTLE}se{SE_M_REVERSAL}{SE_M_CHARGE}littl{SE_M_REVERSAL}enthusiasm!\n"
	.string "Let'{SE_M_GRASSWHISTLE}appeal!$"

