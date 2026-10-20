@ Johto (data/scripts/lilycove_lady.inc), as built into the FireRed game.

J_LilycoveCity_PokemonCenter_1F_EventScript_LilycoveLady::
	special Script_GetLilycoveLadyId
	switch 32781
	case 0, J_LilycoveCity_PokemonCenter_1F_EventScript_QuizLady
	case 1, J_LilycoveCity_PokemonCenter_1F_EventScript_FavorLady
	case 2, J_LilycoveCity_PokemonCenter_1F_EventScript_ContestLady
	end

J_LilycoveCity_PokemonCenter_1F_EventScript_FavorLady::
	lock
	faceplayer
	msgbox J_LilycoveCity_PokemonCenter_1F_Text_ImTheFavorLady, MSGBOX_DEFAULT
	specialvar 32781, GetFavorLadyState
	goto_if_eq 32781, 0, J_LilycoveCity_PokemonCenter_1F_EventScript_FavorLadyReady
	goto_if_eq 32781, 1, J_LilycoveCity_PokemonCenter_1F_EventScript_FavorLadyCompleted
	goto_if_eq 32781, 2, J_LilycoveCity_PokemonCenter_1F_EventScript_FavorLadyPrize
	end

J_LilycoveCity_PokemonCenter_1F_EventScript_FavorLadyCompleted::
	msgbox J_LilycoveCity_PokemonCenter_1F_Text_ThankYouForLastTime, MSGBOX_DEFAULT
	release
	end

J_LilycoveCity_PokemonCenter_1F_EventScript_FavorLadyReady::
	special BufferFavorLadyRequest
	msgbox J_LilycoveCity_PokemonCenter_1F_Text_ObsessedWithThing, MSGBOX_DEFAULT
	specialvar 32781, HasAnotherPlayerGivenFavorLadyItem
	goto_if_eq 32781, FALSE, J_LilycoveCity_PokemonCenter_1F_EventScript_RequestItem
	goto_if_eq 32781, TRUE, J_LilycoveCity_PokemonCenter_1F_EventScript_TellAboutPlayersItem
	end

J_LilycoveCity_PokemonCenter_1F_EventScript_TellAboutPlayersItem::
	special BufferFavorLadyItemName
	special BufferFavorLadyPlayerName
	specialvar 32781, DidFavorLadyLikeItem
	goto_if_eq 32781, FALSE, J_LilycoveCity_PokemonCenter_1F_EventScript_PlayerGaveBadThing
	goto_if_eq 32781, TRUE, J_LilycoveCity_PokemonCenter_1F_EventScript_PlayerGaveGreatThing
	end

J_LilycoveCity_PokemonCenter_1F_EventScript_PlayerGaveBadThing::
	msgbox J_LilycoveCity_PokemonCenter_1F_Text_PlayerGaveMeBadThing, MSGBOX_DEFAULT
	goto J_LilycoveCity_PokemonCenter_1F_EventScript_RequestItem
	end

J_LilycoveCity_PokemonCenter_1F_EventScript_PlayerGaveGreatThing::
	msgbox J_LilycoveCity_PokemonCenter_1F_Text_PlayerGaveMeGreatThing, MSGBOX_DEFAULT
	goto J_LilycoveCity_PokemonCenter_1F_EventScript_RequestItem
	end

J_LilycoveCity_PokemonCenter_1F_EventScript_RequestItem::
	msgbox J_LilycoveCity_PokemonCenter_1F_Text_WillYouShareThing, MSGBOX_YESNO
	goto_if_eq 32781, NO, J_LilycoveCity_PokemonCenter_1F_EventScript_DeclineFavor
	goto_if_eq 32781, YES, J_LilycoveCity_PokemonCenter_1F_EventScript_AcceptFavor
	end

J_LilycoveCity_PokemonCenter_1F_EventScript_DeclineFavor::
	msgbox J_LilycoveCity_PokemonCenter_1F_Text_IsThatSoGoodbye, MSGBOX_DEFAULT
	release
	end

J_LilycoveCity_PokemonCenter_1F_EventScript_AcceptFavor::
	msgbox J_LilycoveCity_PokemonCenter_1F_Text_WhatWillYouGiveMe, MSGBOX_DEFAULT
	goto J_LilycoveCity_PokemonCenter_1F_EventScript_ChooseFavorItem
	end

J_LilycoveCity_PokemonCenter_1F_EventScript_ChooseFavorItem::
	fadescreen 1
	setvar 32781, 0
	special Script_FavorLadyOpenBagMenu
	waitstate
	goto_if_eq 32781, 0, J_LilycoveCity_PokemonCenter_1F_EventScript_AskQuitChooseFavorItem
	goto_if_eq 32781, 1, J_LilycoveCity_PokemonCenter_1F_EventScript_GiveFavorItem
	end

J_LilycoveCity_PokemonCenter_1F_EventScript_AskQuitChooseFavorItem::
	msgbox J_LilycoveCity_PokemonCenter_1F_Text_NotWillingToShare, MSGBOX_YESNO
	goto_if_eq 32781, YES, J_LilycoveCity_PokemonCenter_1F_EventScript_DeclineFavor
	goto_if_eq 32781, NO, J_LilycoveCity_PokemonCenter_1F_EventScript_ChooseFavorItem
	end

J_LilycoveCity_PokemonCenter_1F_EventScript_GiveFavorItem::
	specialvar 32781, Script_DoesFavorLadyLikeItem
	goto_if_eq 32781, FALSE, J_LilycoveCity_PokemonCenter_1F_EventScript_DidntLikeFavorItem
	goto_if_eq 32781, TRUE, J_LilycoveCity_PokemonCenter_1F_EventScript_CheckLovedItem
	end

J_LilycoveCity_PokemonCenter_1F_EventScript_DidntLikeFavorItem::
	special BufferFavorLadyRequest
	msgbox J_LilycoveCity_PokemonCenter_1F_Text_IllTryToCherishIt, MSGBOX_DEFAULT
	release
	end

J_LilycoveCity_PokemonCenter_1F_EventScript_CheckLovedItem::
	specialvar 32781, IsFavorLadyThresholdMet
	goto_if_eq 32781, FALSE, J_LilycoveCity_PokemonCenter_1F_EventScript_LikedFavorItem
	goto_if_eq 32781, TRUE, J_LilycoveCity_PokemonCenter_1F_EventScript_LovedFavorItem
	end

J_LilycoveCity_PokemonCenter_1F_EventScript_LikedFavorItem::
	special BufferFavorLadyRequest
	msgbox J_LilycoveCity_PokemonCenter_1F_Text_IWillCherishThis, MSGBOX_DEFAULT
	release
	end

J_LilycoveCity_PokemonCenter_1F_EventScript_LovedFavorItem::
	special BufferFavorLadyRequest
	msgbox J_LilycoveCity_PokemonCenter_1F_Text_IWillTreasureThis, MSGBOX_DEFAULT
	goto J_LilycoveCity_PokemonCenter_1F_EventScript_FavorLadyPrize
	end

J_LilycoveCity_PokemonCenter_1F_EventScript_FavorLadyPrize::
	setvar 32772, 0
	specialvar 32772, FavorLadyGetPrize
	msgbox J_LilycoveCity_PokemonCenter_1F_Text_IllGiveYouThisInReturn, MSGBOX_DEFAULT
	giveitem 32772
	goto_if_eq 32781, 0, J_LilycoveCity_PokemonCenter_1F_EventScript_NoRoomForFavorPrize
	goto_if_eq 32781, 1, J_LilycoveCity_PokemonCenter_1F_EventScript_ReceivedFavorPrize
	end

J_LilycoveCity_PokemonCenter_1F_EventScript_NoRoomForFavorPrize::
	msgbox J_LilycoveCity_PokemonCenter_1F_Text_YouDontHaveSpaceForIt, MSGBOX_DEFAULT
	release
	end

J_LilycoveCity_PokemonCenter_1F_EventScript_ReceivedFavorPrize::
	special SetFavorLadyState_Complete
	release
	end

J_LilycoveCity_PokemonCenter_1F_EventScript_QuizLady::
	lock
	faceplayer
	msgbox J_LilycoveCity_PokemonCenter_1F_Text_ImTheQuizLady, MSGBOX_DEFAULT
	specialvar 32781, GetQuizLadyState
	goto_if_eq 32781, 0, J_LilycoveCity_PokemonCenter_1F_EventScript_HasQuiz
	goto_if_eq 32781, 1, J_LilycoveCity_PokemonCenter_1F_EventScript_CheckMadeQuiz
	goto_if_eq 32781, 2, J_LilycoveCity_PokemonCenter_1F_EventScript_ReadyGivePrize
	end

J_LilycoveCity_PokemonCenter_1F_EventScript_HasQuiz::
	specialvar 32781, GetQuizAuthor
	goto_if_eq 32781, 0, J_LilycoveCity_PokemonCenter_1F_EventScript_WaitingToTakeYourQuiz
	goto_if_eq 32781, 1, J_LilycoveCity_PokemonCenter_1F_EventScript_PlayerQuizReady
	goto_if_eq 32781, 2, J_LilycoveCity_PokemonCenter_1F_EventScript_LadyQuizReady
	end

J_LilycoveCity_PokemonCenter_1F_EventScript_CheckMadeQuiz::
	specialvar 32781, IsQuizLadyWaitingForChallenger
	goto_if_eq 32781, FALSE, J_LilycoveCity_PokemonCenter_1F_EventScript_AskMakeQuiz
	goto_if_eq 32781, TRUE, J_LilycoveCity_PokemonCenter_1F_EventScript_WaitingToTakeYourQuiz
	end

J_LilycoveCity_PokemonCenter_1F_EventScript_WaitingToTakeYourQuiz::
	msgbox J_LilycoveCity_PokemonCenter_1F_Text_WaitingToTakeYourQuiz, MSGBOX_DEFAULT
	release
	end

J_LilycoveCity_PokemonCenter_1F_EventScript_PlayerQuizReady::
	msgbox J_LilycoveCity_PokemonCenter_1F_Text_WaitingForChallenger, MSGBOX_DEFAULT
	goto J_LilycoveCity_PokemonCenter_1F_EventScript_AskTakeQuiz
	end

J_LilycoveCity_PokemonCenter_1F_EventScript_LadyQuizReady::
	msgbox J_LilycoveCity_PokemonCenter_1F_Text_WaitingForChallenger, MSGBOX_DEFAULT
	goto J_LilycoveCity_PokemonCenter_1F_EventScript_AskTakeQuiz
	end

J_LilycoveCity_PokemonCenter_1F_EventScript_AskTakeQuiz::
	setvar 32772, 0
	msgbox J_LilycoveCity_PokemonCenter_1F_Text_TakeQuizChallenge, MSGBOX_YESNO
	goto_if_eq 32781, YES, J_LilycoveCity_PokemonCenter_1F_EventScript_TakeQuiz
	goto_if_eq 32781, NO, J_LilycoveCity_PokemonCenter_1F_EventScript_DeclineQuiz
	end

J_LilycoveCity_PokemonCenter_1F_EventScript_DeclineQuiz::
	msgbox J_LilycoveCity_PokemonCenter_1F_Text_HowBoringBye, MSGBOX_DEFAULT
	release
	end

J_LilycoveCity_PokemonCenter_1F_EventScript_TakeQuiz::
	special ClearQuizLadyPlayerAnswer
	goto_if_eq 32772, 0, J_LilycoveCity_PokemonCenter_1F_EventScript_ShowQuestion
	goto_if_eq 32772, 15, J_LilycoveCity_PokemonCenter_1F_EventScript_GetAnswer

J_LilycoveCity_PokemonCenter_1F_EventScript_CheckQuizTakingState::
	goto_if_eq 32781, 0, J_LilycoveCity_PokemonCenter_1F_EventScript_AskQuitQuiz
	goto_if_eq 32781, 1, J_LilycoveCity_PokemonCenter_1F_EventScript_SubmitQuizResponse
	end

J_LilycoveCity_PokemonCenter_1F_EventScript_ShowQuestion::
	special QuizLadyShowQuizQuestion
	waitstate
	goto J_LilycoveCity_PokemonCenter_1F_EventScript_CheckQuizTakingState
	end

J_LilycoveCity_PokemonCenter_1F_EventScript_GetAnswer::
	special QuizLadyGetPlayerAnswer
	waitstate
	goto J_LilycoveCity_PokemonCenter_1F_EventScript_CheckQuizTakingState
	end

J_LilycoveCity_PokemonCenter_1F_EventScript_AskQuitQuiz::
	msgbox J_LilycoveCity_PokemonCenter_1F_Text_YoureGoingToQuit, MSGBOX_YESNO
	goto_if_eq 32781, YES, J_LilycoveCity_PokemonCenter_1F_EventScript_QuitTakingQuiz
	goto_if_eq 32781, NO, J_LilycoveCity_PokemonCenter_1F_EventScript_TakeQuiz
	end

J_LilycoveCity_PokemonCenter_1F_EventScript_QuitTakingQuiz::
	msgbox J_LilycoveCity_PokemonCenter_1F_Text_TakeTheQuizAnotherTime, MSGBOX_DEFAULT
	release
	end

J_LilycoveCity_PokemonCenter_1F_EventScript_SubmitQuizResponse::
	special SetQuizLadyState_Complete
	msgbox J_LilycoveCity_PokemonCenter_1F_Text_WaitForAnswer, MSGBOX_DEFAULT
	specialvar 32781, IsQuizAnswerCorrect
	goto_if_eq 32781, FALSE, J_LilycoveCity_PokemonCenter_1F_EventScript_IncorrectResponse
	goto_if_eq 32781, TRUE, J_LilycoveCity_PokemonCenter_1F_EventScript_CorrectResponse
	end

J_LilycoveCity_PokemonCenter_1F_EventScript_CorrectResponse::
	playse 31
	delay 10
	playse 31
	msgbox J_LilycoveCity_PokemonCenter_1F_Text_YouGotItRight, MSGBOX_DEFAULT
	goto J_LilycoveCity_PokemonCenter_1F_EventScript_ReadyGivePrize
	end

J_LilycoveCity_PokemonCenter_1F_EventScript_IncorrectResponse::
	special BufferQuizCorrectAnswer
	special BufferQuizPrizeName
	playse 32
	delay 10
	playse 32
	msgbox J_LilycoveCity_PokemonCenter_1F_Text_WrongTheCorrectAnswerIs, MSGBOX_DEFAULT
	msgbox J_LilycoveCity_PokemonCenter_1F_Text_IGetToKeepPrize, MSGBOX_DEFAULT
	goto J_LilycoveCity_PokemonCenter_1F_EventScript_AskMakeQuiz
	end

J_LilycoveCity_PokemonCenter_1F_EventScript_ReadyGivePrize::
	specialvar 32781, BufferQuizAuthorNameAndCheckIfLady
	goto_if_eq 32781, 1, J_LilycoveCity_PokemonCenter_1F_EventScript_GivePrize1
	goto_if_eq 32781, 0, J_LilycoveCity_PokemonCenter_1F_EventScript_GivePrize0
	end

J_LilycoveCity_PokemonCenter_1F_EventScript_GivePrize1::
	msgbox J_LilycoveCity_PokemonCenter_1F_Text_YouGotItRightYouveWonPersonsPrize, MSGBOX_DEFAULT
	goto J_LilycoveCity_PokemonCenter_1F_EventScript_GivePrize
	end

J_LilycoveCity_PokemonCenter_1F_EventScript_GivePrize0::
	msgbox J_LilycoveCity_PokemonCenter_1F_Text_YouGotItRightYouveWonPersonsPrize, MSGBOX_DEFAULT
	goto J_LilycoveCity_PokemonCenter_1F_EventScript_GivePrize
	end

J_LilycoveCity_PokemonCenter_1F_EventScript_GivePrize::
	setvar 32773, 0
	special BufferQuizPrizeItem
	special SetQuizLadyState_Complete
	giveitem 32773
	goto_if_eq 32781, FALSE, J_LilycoveCity_PokemonCenter_1F_EventScript_NoSpaceForQuizPrize
	goto J_LilycoveCity_PokemonCenter_1F_EventScript_AskMakeQuiz
	end

J_LilycoveCity_PokemonCenter_1F_EventScript_NoSpaceForQuizPrize::
	msgbox J_LilycoveCity_PokemonCenter_1F_Text_YourBagIsFilledUp, MSGBOX_DEFAULT
	special SetQuizLadyState_GivePrize
	release
	end

J_LilycoveCity_PokemonCenter_1F_EventScript_AskMakeQuiz::
	msgbox J_LilycoveCity_PokemonCenter_1F_Text_MakeYourOwnQuiz, MSGBOX_YESNO
	goto_if_eq 32781, YES, J_LilycoveCity_PokemonCenter_1F_EventScript_MakeQuiz
	goto_if_eq 32781, NO, J_LilycoveCity_PokemonCenter_1F_EventScript_DeclineMakeQuiz
	end

J_LilycoveCity_PokemonCenter_1F_EventScript_DeclineMakeQuiz::
	special QuizLadyPickNewQuestion
	msgbox J_LilycoveCity_PokemonCenter_1F_Text_MaybeNextTime, MSGBOX_DEFAULT
	release
	end

J_LilycoveCity_PokemonCenter_1F_EventScript_MakeQuiz::
	msgbox J_LilycoveCity_PokemonCenter_1F_Text_PickYourPrize, MSGBOX_DEFAULT

J_LilycoveCity_PokemonCenter_1F_EventScript_PickPrize::
	fadescreen 1
	setvar 32781, 0
	special Script_QuizLadyOpenBagMenu
	waitstate
	goto_if_eq 32781, 0, J_LilycoveCity_PokemonCenter_1F_EventScript_AskQuitChoosingPrize
	goto_if_eq 32781, 1, J_LilycoveCity_PokemonCenter_1F_EventScript_WriteQuiz
	end

J_LilycoveCity_PokemonCenter_1F_EventScript_AskQuitChoosingPrize::
	msgbox J_LilycoveCity_PokemonCenter_1F_Text_QuitChoosingPrize, MSGBOX_YESNO
	goto_if_eq 32781, YES, J_LilycoveCity_PokemonCenter_1F_EventScript_DeclineMakeQuiz
	goto_if_eq 32781, NO, J_LilycoveCity_PokemonCenter_1F_EventScript_PickPrize
	end

J_LilycoveCity_PokemonCenter_1F_EventScript_WriteQuiz::
	msgbox J_LilycoveCity_PokemonCenter_1F_Text_WriteYourQuiz, MSGBOX_DEFAULT
	special ClearQuizLadyQuestionAndAnswer
	special ClearQuizLadyPlayerAnswer
	setvar 32772, 16

J_LilycoveCity_PokemonCenter_1F_EventScript_WriteQuizQuestion::
	fadescreen 1
	special QuizLadySetCustomQuestion
	waitstate
	goto_if_eq 32781, 0, J_LilycoveCity_PokemonCenter_1F_EventScript_AskQuitWritingQuizQuestion
	goto J_LilycoveCity_PokemonCenter_1F_EventScript_FinishMakingQuiz
	end

J_LilycoveCity_PokemonCenter_1F_EventScript_AskQuitWritingQuizQuestion::
	msgbox J_LilycoveCity_PokemonCenter_1F_Text_QuitWritingQuizQuestion, MSGBOX_YESNO
	goto_if_eq 32781, YES, J_LilycoveCity_PokemonCenter_1F_EventScript_DeclineMakeQuiz
	goto_if_eq 32781, NO, J_LilycoveCity_PokemonCenter_1F_EventScript_WriteQuizQuestion
	end

J_LilycoveCity_PokemonCenter_1F_EventScript_FinishMakingQuiz::
	special QuizLadyTakePrizeForCustomQuiz
	special QuizLadyRecordCustomQuizData
	special QuizLadySetWaitingForChallenger
	msgbox J_LilycoveCity_PokemonCenter_1F_Text_IllLookForAChallenger, MSGBOX_DEFAULT
	release
	end

J_LilycoveCity_PokemonCenter_1F_EventScript_ContestLady::
	lock
	faceplayer
	msgbox J_LilycoveCity_PokemonCenter_1F_Text_ImTheContestLady, MSGBOX_DEFAULT
	specialvar 32781, HasPlayerGivenContestLadyPokeblock
	goto_if_eq 32781, FALSE, J_LilycoveCity_PokemonCenter_1F_EventScript_NotGivenPokeblock
	goto_if_eq 32781, TRUE, J_LilycoveCity_PokemonCenter_1F_EventScript_GivenPokeblock
	end

J_LilycoveCity_PokemonCenter_1F_EventScript_NotGivenPokeblock::
	specialvar 32781, ShouldContestLadyShowGoOnAir
	goto_if_eq 32781, FALSE, J_LilycoveCity_PokemonCenter_1F_EventScript_AskForPokeblock
	goto_if_eq 32781, TRUE, J_LilycoveCity_PokemonCenter_1F_EventScript_GivenPokeblock
	end

J_LilycoveCity_PokemonCenter_1F_EventScript_GivenPokeblock::
	msgbox J_LilycoveCity_PokemonCenter_1F_Text_ThankForPokeblock, MSGBOX_DEFAULT
	release
	end

J_LilycoveCity_PokemonCenter_1F_EventScript_AskForPokeblock::
	special Script_BufferContestLadyCategoryAndMonName
	msgbox J_LilycoveCity_PokemonCenter_1F_Text_MyFriendDisplaysQuality, MSGBOX_DEFAULT
	checkitem ITEM_POKEBLOCK_CASE
	goto_if_eq 32781, FALSE, J_LilycoveCity_PokemonCenter_1F_EventScript_NoPokeblockCase
	msgbox J_LilycoveCity_PokemonCenter_1F_Text_AskingForOnePokeblock, MSGBOX_YESNO
	goto_if_eq 32781, NO, J_LilycoveCity_PokemonCenter_1F_EventScript_DeclineGivePokeblock
	goto_if_eq 32781, YES, J_LilycoveCity_PokemonCenter_1F_EventScript_ChoosePokeblock
	end

J_LilycoveCity_PokemonCenter_1F_EventScript_DeclineGivePokeblock::
	msgbox J_LilycoveCity_PokemonCenter_1F_Text_WhatACheapskate, MSGBOX_DEFAULT
	release
	end

J_LilycoveCity_PokemonCenter_1F_EventScript_ChoosePokeblock::
	fadescreen 1
	special OpenPokeblockCaseForContestLady
	waitstate
	goto_if_eq 32781, 0xFFFF, J_LilycoveCity_PokemonCenter_1F_EventScript_AskQuitGivingPokeblock
	goto_if_ne 32781, 0xFFFF, J_LilycoveCity_PokemonCenter_1F_EventScript_GivePokeblock
	end

J_LilycoveCity_PokemonCenter_1F_EventScript_AskQuitGivingPokeblock::
	msgbox J_LilycoveCity_PokemonCenter_1F_Text_ICantHaveOnePokeblock, MSGBOX_YESNO
	goto_if_eq 32781, YES, J_LilycoveCity_PokemonCenter_1F_EventScript_DeclineGivePokeblock
	goto_if_eq 32781, NO, J_LilycoveCity_PokemonCenter_1F_EventScript_ChoosePokeblock
	end

J_LilycoveCity_PokemonCenter_1F_EventScript_GivePokeblock::
	msgbox J_LilycoveCity_PokemonCenter_1F_Text_IllUseYourPokeblock, MSGBOX_DEFAULT
	special SetContestLadyGivenPokeblock
	special GetContestLadyMonSpecies
	goto J_LilycoveCity_PokemonCenter_1F_EventScript_FeedPokeblock
	end

J_LilycoveCity_PokemonCenter_1F_EventScript_FeedPokeblock::
	applymovement 4, J_LilycoveCity_PokemonCenter_1F_Movement_LadyFaceMon
	waitmovement 0
	delay 60
	applymovement 5, J_LilycoveCity_PokemonCenter_1F_Movement_MonFaceLady
	waitmovement 0
	delay 60
	waitse
	playmoncry 32773, 0
	delay 120
	waitmoncry
	goto_if_eq 32772, 1, J_LilycoveCity_PokemonCenter_1F_EventScript_MonEnjoyPokeblock
	goto J_LilycoveCity_PokemonCenter_1F_EventScript_FinishFeedPokeblock
	end

J_LilycoveCity_PokemonCenter_1F_EventScript_MonEnjoyPokeblock::
	applymovement 5, J_LilycoveCity_PokemonCenter_1F_Movement_MonJump
	waitmovement 0
	delay 60

J_LilycoveCity_PokemonCenter_1F_EventScript_FinishFeedPokeblock::
	applymovement 4, J_LilycoveCity_PokemonCenter_1F_Movement_LadyFacePlayer
	waitmovement 0
	delay 60
	goto_if_eq 32772, 0, J_LilycoveCity_PokemonCenter_1F_EventScript_MonDislikedPokeblock
	goto_if_eq 32772, 1, J_LilycoveCity_PokemonCenter_1F_EventScript_MonLikedPokeblock
	end

J_LilycoveCity_PokemonCenter_1F_EventScript_MonDislikedPokeblock::
	msgbox J_LilycoveCity_PokemonCenter_1F_Text_NoChangeThanks, MSGBOX_DEFAULT
	goto J_LilycoveCity_PokemonCenter_1F_EventScript_CheckAirContestLadyShow
	end

J_LilycoveCity_PokemonCenter_1F_EventScript_MonLikedPokeblock::
	special Script_BufferContestLadyCategoryAndMonName
	msgbox J_LilycoveCity_PokemonCenter_1F_Text_ReallyImprovedThanks, MSGBOX_DEFAULT
	goto J_LilycoveCity_PokemonCenter_1F_EventScript_CheckAirContestLadyShow
	end

J_LilycoveCity_PokemonCenter_1F_EventScript_CheckAirContestLadyShow::
	specialvar 32781, ShouldContestLadyShowGoOnAir
	goto_if_eq 32781, 1, J_LilycoveCity_PokemonCenter_1F_EventScript_AirContestLadyShow
	release
	end

J_LilycoveCity_PokemonCenter_1F_EventScript_AirContestLadyShow::
	msgbox J_LilycoveCity_PokemonCenter_1F_Text_ReadyToEnterContests, MSGBOX_DEFAULT
	special PutLilycoveContestLadyShowOnTheAir
	release
	end

J_LilycoveCity_PokemonCenter_1F_EventScript_NoPokeblockCase::
	msgbox J_LilycoveCity_PokemonCenter_1F_Text_DontHaveAPokeblockCase, MSGBOX_DEFAULT
	release
	end

J_LilycoveCity_PokemonCenter_1F_Movement_LadyFaceMon:
	face_right
	delay_8
	step_end

J_LilycoveCity_PokemonCenter_1F_Movement_MonFaceLady:
	face_left
	delay_8
	step_end

J_LilycoveCity_PokemonCenter_1F_Movement_MonFaceDown:
	face_down
	step_end

J_LilycoveCity_PokemonCenter_1F_Movement_LadyFacePlayer:
	face_player
	step_end

J_LilycoveCity_PokemonCenter_1F_Movement_MonJump:
	disable_jump_landing_ground_effect
	jump_in_place_left
	disable_jump_landing_ground_effect
	jump_in_place_left
	step_end

J_LilycoveCity_PokemonCenter_1F_EventScript_ContestLadyMon::
	specialvar 32781, GetContestLadyCategory
	special Script_BufferContestLadyCategoryAndMonName
	special GetContestLadyMonSpecies
	goto_if_eq 32781, CONTEST_CATEGORY_COOL, J_LilycoveCity_PokemonCenter_1F_EventScript_Zigzagoon
	goto_if_eq 32781, CONTEST_CATEGORY_BEAUTY, J_LilycoveCity_PokemonCenter_1F_EventScript_Skitty
	goto_if_eq 32781, CONTEST_CATEGORY_CUTE, J_LilycoveCity_PokemonCenter_1F_EventScript_Poochyena
	goto_if_eq 32781, CONTEST_CATEGORY_SMART, J_LilycoveCity_PokemonCenter_1F_EventScript_Kecleon
	goto_if_eq 32781, CONTEST_CATEGORY_TOUGH, J_LilycoveCity_PokemonCenter_1F_EventScript_Pikachu
	end

J_LilycoveCity_PokemonCenter_1F_EventScript_Zigzagoon::
	lock
	faceplayer
	waitse
	playmoncry 32773, 0
	msgbox J_LilycoveCity_PokemonCenter_1F_Text_Zigzagoon, MSGBOX_DEFAULT
	waitmoncry
	release
	end

J_LilycoveCity_PokemonCenter_1F_EventScript_Skitty::
	lock
	faceplayer
	waitse
	playmoncry 32773, 0
	msgbox J_LilycoveCity_PokemonCenter_1F_Text_Skitty, MSGBOX_DEFAULT
	waitmoncry
	release
	end

J_LilycoveCity_PokemonCenter_1F_EventScript_Poochyena::
	lock
	faceplayer
	waitse
	playmoncry 32773, 0
	msgbox J_LilycoveCity_PokemonCenter_1F_Text_Poochyena, MSGBOX_DEFAULT
	waitmoncry
	release
	end

J_LilycoveCity_PokemonCenter_1F_EventScript_Kecleon::
	lock
	faceplayer
	waitse
	playmoncry 32773, 0
	msgbox J_LilycoveCity_PokemonCenter_1F_Text_Kecleon, MSGBOX_DEFAULT
	waitmoncry
	release
	end

J_LilycoveCity_PokemonCenter_1F_EventScript_Pikachu::
	lock
	faceplayer
	waitse
	playmoncry 32773, 0
	msgbox J_LilycoveCity_PokemonCenter_1F_Text_Pikachu, MSGBOX_DEFAULT
	waitmoncry
	release
	end

J_LilycoveCity_PokemonCenter_1F_Text_ImTheFavorLady:
	.string "I'{SE_M_MILK_DRINK}th{SE_M_REVERSAL}FAVO{SE_M_MINIMIZE}LADY…$"

J_LilycoveCity_PokemonCenter_1F_Text_ObsessedWithThing:
	.string "I'v{SE_M_REVERSAL}recentl{SE_M_YAWN}develope{SE_M_WATERFALL}a{SE_M_ATTRACT}obsession\n"
	.string "fo{SE_M_SAND_TOMB}{STR_VAR_1} things…$"

J_LilycoveCity_PokemonCenter_1F_Text_ThankYouForLastTime:
	.string "Oh…\n"
	.string "Than{SE_M_ENCORE2}yo{SE_M_DIVE}fo{SE_M_SAND_TOMB}las{SE_M_SPIT_UP}time…$"

J_LilycoveCity_PokemonCenter_1F_Text_PlayerGaveMeBadThing:
	.string "Before{SE_M_SUPERSONIC}{SE_M_HEAL_BELL}thin{SE_M_ENCORE2}i{SE_M_SPIT_UP}wa{SE_M_GRASSWHISTLE}{STR_VAR_3}…\p"
	.string "{STR_VAR_3} gav{SE_M_REVERSAL}m{SE_M_REVERSAL}on{SE_M_REVERSAL}{STR_VAR_2},\n"
	.string "sayin{SE_M_SANDSTORM}i{SE_M_SPIT_UP}wa{SE_M_GRASSWHISTLE}{STR_VAR_1}.\p"
	.string "Bu{SE_M_SPIT_UP}i{SE_M_SPIT_UP}wasn'{SE_M_SPIT_UP}{STR_VAR_1}.\n"
	.string "No{SE_M_SPIT_UP}i{SE_M_ATTRACT}th{SE_M_REVERSAL}leas{SE_M_SPIT_UP}bit.$"

J_LilycoveCity_PokemonCenter_1F_Text_PlayerGaveMeGreatThing:
	.string "Before{SE_M_SUPERSONIC}{STR_VAR_3} gav{SE_M_REVERSAL}m{SE_M_REVERSAL}{SE_M_CHARGE}very\n"
	.string "{STR_VAR_1} {STR_VAR_2}.\p"
	.string "{SE_M_HEAL_BELL}cheris{SE_M_TRI_ATTACK}i{SE_M_SPIT_UP}now.$"

J_LilycoveCity_PokemonCenter_1F_Text_WillYouShareThing:
	.string "Listen{SE_M_SUPERSONIC}i{SE_M_ACID_ARMOR}yo{SE_M_DIVE}hav{SE_M_REVERSAL}anythin{SE_M_SANDSTORM}that\n"
	.string "i{SE_M_GRASSWHISTLE}{STR_VAR_1}{SE_M_SUPERSONIC}wil{SE_M_BATON_PASS}yo{SE_M_DIVE}shar{SE_M_REVERSAL}it\l"
	.string "wit{SE_M_TRI_ATTACK}me?$"

J_LilycoveCity_PokemonCenter_1F_Text_WhatWillYouGiveMe:
	.string "…Really?\n"
	.string "Wha{SE_M_SPIT_UP}wil{SE_M_BATON_PASS}yo{SE_M_DIVE}giv{SE_M_REVERSAL}me?$"

J_LilycoveCity_PokemonCenter_1F_Text_IsThatSoGoodbye:
	.string "I{SE_M_GRASSWHISTLE}tha{SE_M_SPIT_UP}so?\n"
	.string "Then{SE_M_SUPERSONIC}it'{SE_M_GRASSWHISTLE}good-bye…$"

J_LilycoveCity_PokemonCenter_1F_Text_NotWillingToShare:
	.string "Oh…\n"
	.string "You'r{SE_M_REVERSAL}no{SE_M_SPIT_UP}willin{SE_M_SANDSTORM}t{SE_M_ATTRACT2}share?$"

J_LilycoveCity_PokemonCenter_1F_Text_IllTryToCherishIt:
	.string "Oh?\n"
	.string "Tha{SE_M_SPIT_UP}{STR_VAR_2} i{SE_M_GRASSWHISTLE}{STR_VAR_1}?\p"
	.string "…Oh{SE_M_SUPERSONIC}i{SE_M_GRASSWHISTLE}tha{SE_M_SPIT_UP}right?\p"
	.string "Well{SE_M_SUPERSONIC}{SE_M_HEAL_BELL}ow{SE_M_REVERSAL}yo{SE_M_DIVE}{SE_M_CHARGE}thank{SE_M_GRASSWHISTLE}anyway.\n"
	.string "I'l{SE_M_BATON_PASS}tr{SE_M_YAWN}t{SE_M_ATTRACT2}cheris{SE_M_TRI_ATTACK}it…$"

J_LilycoveCity_PokemonCenter_1F_Text_IWillCherishThis:
	.string "Oh…\p"
	.string "That'{SE_M_GRASSWHISTLE}{SE_M_CHARGE}quit{SE_M_REVERSAL}{STR_VAR_1}\n"
	.string "{STR_VAR_2}…\p"
	.string "Isn'{SE_M_SPIT_UP}i{SE_M_SPIT_UP}nice?\n"
	.string "It'{SE_M_GRASSWHISTLE}s{SE_M_ATTRACT2}dreamy…\p"
	.string "Than{SE_M_ENCORE2}you…\n"
	.string "{SE_M_HEAL_BELL}wil{SE_M_BATON_PASS}cheris{SE_M_TRI_ATTACK}this…$"

J_LilycoveCity_PokemonCenter_1F_Text_IWillTreasureThis:
	.string "…Oh{SE_M_SUPERSONIC}oh{SE_M_SUPERSONIC}oh…\p"
	.string "Thi{SE_M_GRASSWHISTLE}i{SE_M_GRASSWHISTLE}amazing!\n"
	.string "Thi{SE_M_GRASSWHISTLE}reall{SE_M_YAWN}i{SE_M_GRASSWHISTLE}{STR_VAR_1}!\p"
	.string "{SE_M_HEAL_BELL}neve{SE_M_SAND_TOMB}kne{SE_M_TWISTER}tha{SE_M_SPIT_UP}on{SE_M_REVERSAL}{STR_VAR_2}\n"
	.string "coul{SE_M_WATERFALL}b{SE_M_REVERSAL}thi{SE_M_GRASSWHISTLE}{STR_VAR_1}!\p"
	.string "Than{SE_M_ENCORE2}you!\p"
	.string "{SE_M_HEAL_BELL}wil{SE_M_BATON_PASS}treasur{SE_M_REVERSAL}thi{SE_M_GRASSWHISTLE}fo{SE_M_SAND_TOMB}th{SE_M_REVERSAL}rest\n"
	.string "o{SE_M_ACID_ARMOR}m{SE_M_YAWN}life!$"

J_LilycoveCity_PokemonCenter_1F_Text_IllGiveYouThisInReturn:
	.string "I'l{SE_M_BATON_PASS}giv{SE_M_REVERSAL}yo{SE_M_DIVE}thi{SE_M_GRASSWHISTLE}wonderfu{SE_M_BATON_PASS}ite{SE_M_MILK_DRINK}in\n"
	.string "retur{SE_M_ATTRACT}fo{SE_M_SAND_TOMB}you{SE_M_SAND_TOMB}fabulou{SE_M_GRASSWHISTLE}gift.\p"
	.string "{SE_M_HEAL_BELL}hop{SE_M_REVERSAL}yo{SE_M_DIVE}wil{SE_M_BATON_PASS}cheris{SE_M_TRI_ATTACK}it…$"

J_LilycoveCity_PokemonCenter_1F_Text_YouDontHaveSpaceForIt:
	.string "Oh{SE_M_SUPERSONIC}yo{SE_M_DIVE}can'{SE_M_SPIT_UP}hav{SE_M_REVERSAL}i{SE_M_SPIT_UP}i{SE_M_ACID_ARMOR}yo{SE_M_DIVE}don'{SE_M_SPIT_UP}have\n"
	.string "th{SE_M_REVERSAL}spac{SE_M_REVERSAL}fo{SE_M_SAND_TOMB}it.\p"
	.string "Pleas{SE_M_REVERSAL}com{SE_M_REVERSAL}se{SE_M_REVERSAL}m{SE_M_REVERSAL}whe{SE_M_ATTRACT}yo{SE_M_DIVE}get\n"
	.string "you{SE_M_SAND_TOMB}BA{SE_M_SWAGGER}organized…$"

J_LilycoveCity_PokemonCenter_1F_Text_ImTheQuizLady:
	.string "I'{SE_M_MILK_DRINK}th{SE_M_REVERSAL}QUI{SE_M_CHARM}LADY!\n"
	.string "{SE_M_HEAL_BELL}lov{SE_M_REVERSAL}quizzes!$"

J_LilycoveCity_PokemonCenter_1F_Text_WaitingToTakeYourQuiz:
	.string "Oh?\p"
	.string "I'{SE_M_MILK_DRINK}waitin{SE_M_SANDSTORM}fo{SE_M_SAND_TOMB}{SE_M_CHARGE}challenge{SE_M_SAND_TOMB}t{SE_M_ATTRACT2}answer\n"
	.string "th{SE_M_REVERSAL}qui{SE_M_SKY_UPPERCUT}yo{SE_M_DIVE}made.\p"
	.string "W{SE_M_REVERSAL}ca{SE_M_ATTRACT}cha{SE_M_SPIT_UP}anothe{SE_M_SAND_TOMB}time{SE_M_SUPERSONIC}okay?$"

J_LilycoveCity_PokemonCenter_1F_Text_WaitingForChallenger:
	.string "I'{SE_M_MILK_DRINK}waitin{SE_M_SANDSTORM}fo{SE_M_SAND_TOMB}someon{SE_M_REVERSAL}t{SE_M_ATTRACT2}challenge\n"
	.string "{SE_M_CHARGE}qui{SE_M_SKY_UPPERCUT}thi{SE_M_GRASSWHISTLE}{STR_VAR_1} though{SE_M_SPIT_UP}up!$"

J_LilycoveCity_PokemonCenter_1F_Text_TakeQuizChallenge:
	.string "I{SE_M_ACID_ARMOR}yo{SE_M_DIVE}answe{SE_M_SAND_TOMB}correctly{SE_M_SUPERSONIC}yo{SE_M_DIVE}ca{SE_M_ATTRACT}win\n"
	.string "fabulou{SE_M_GRASSWHISTLE}prizes!\p"
	.string "Woul{SE_M_WATERFALL}yo{SE_M_DIVE}lik{SE_M_REVERSAL}t{SE_M_ATTRACT2}tak{SE_M_REVERSAL}th{SE_M_REVERSAL}quiz\n"
	.string "challenge?$"

J_LilycoveCity_PokemonCenter_1F_Text_WaitForAnswer:
	.string "{SE_M_DIZZY_PUNCH}{SE_M_DIZZY_PUNCH}{SE_M_DIZZY_PUNCH}{SE_M_DIZZY_PUNCH}{SE_M_DIZZY_PUNCH}…\n"
	.string "{SE_M_DIZZY_PUNCH}{SE_M_DIZZY_PUNCH}{SE_M_DIZZY_PUNCH}{SE_M_DIZZY_PUNCH}{SE_M_DIZZY_PUNCH}…$"

J_LilycoveCity_PokemonCenter_1F_Text_HowBoringBye:
	.string "Oh{SE_M_SUPERSONIC}ho{SE_M_TWISTER}boring!\n"
	.string "Bye-bye!$"

J_LilycoveCity_PokemonCenter_1F_Text_YoureGoingToQuit:
	.string "Awww!\n"
	.string "You'r{SE_M_REVERSAL}goin{SE_M_SANDSTORM}t{SE_M_ATTRACT2}quit?$"

J_LilycoveCity_PokemonCenter_1F_Text_TakeTheQuizAnotherTime:
	.string "Pleas{SE_M_REVERSAL}tak{SE_M_REVERSAL}th{SE_M_REVERSAL}qui{SE_M_SKY_UPPERCUT}challenge\n"
	.string "anothe{SE_M_SAND_TOMB}time!$"

J_LilycoveCity_PokemonCenter_1F_Text_YouGotItRight:
	.string "You'r{SE_M_REVERSAL}amazing{SE_M_DRAGON_RAGE}You'v{SE_M_REVERSAL}go{SE_M_SPIT_UP}i{SE_M_SPIT_UP}right!\n"
	.string "You'r{SE_M_REVERSAL}on{SE_M_REVERSAL}shar{SE_M_MORNING_SUN}customer!$"

J_LilycoveCity_PokemonCenter_1F_Text_YouGotItRightYouveWonPersonsPrize:
	.string "Congratulations!\n"
	.string "You'v{SE_M_REVERSAL}go{SE_M_SPIT_UP}th{SE_M_REVERSAL}qui{SE_M_SKY_UPPERCUT}right!\p"
	.string "You'v{SE_M_REVERSAL}wo{SE_M_ATTRACT}{SE_M_CHARGE}priz{SE_M_REVERSAL}provide{SE_M_WATERFALL}by\n"
	.string "{STR_VAR_1}!$"

J_LilycoveCity_PokemonCenter_1F_Text_XReceivedOneY:
	.string "{STR_VAR_1} received\n"
	.string "on{SE_M_REVERSAL}{STR_VAR_2}!$"

J_LilycoveCity_PokemonCenter_1F_Text_YourBagIsFilledUp:
	.string "Oh{SE_M_SING}You{SE_M_SAND_TOMB}BA{SE_M_SWAGGER}i{SE_M_GRASSWHISTLE}fille{SE_M_WATERFALL}up!\n"
	.string "Com{SE_M_REVERSAL}se{SE_M_REVERSAL}m{SE_M_REVERSAL}whe{SE_M_ATTRACT}yo{SE_M_DIVE}hav{SE_M_REVERSAL}room.$"

J_LilycoveCity_PokemonCenter_1F_Text_WrongTheCorrectAnswerIs:
	.string "Hmm{SE_M_DIZZY_PUNCH}Wrong!\n"
	.string "Th{SE_M_REVERSAL}correc{SE_M_SPIT_UP}answe{SE_M_SAND_TOMB}i{SE_M_GRASSWHISTLE}“{STR_VAR_3}”!$"

J_LilycoveCity_PokemonCenter_1F_Text_IGetToKeepPrize:
	.string "To{SE_M_ATTRACT2}bad!\p"
	.string "{SE_M_HEAL_BELL}ge{SE_M_SPIT_UP}t{SE_M_ATTRACT2}kee{SE_M_MORNING_SUN}th{SE_M_REVERSAL}qui{SE_M_SKY_UPPERCUT}prize\n"
	.string "{STR_VAR_1} now!$"

J_LilycoveCity_PokemonCenter_1F_Text_MakeYourOwnQuiz:
	.string "Listen{SE_M_SUPERSONIC}listen!\n"
	.string "Woul{SE_M_WATERFALL}yo{SE_M_DIVE}lik{SE_M_REVERSAL}t{SE_M_ATTRACT2}mak{SE_M_REVERSAL}you{SE_M_SAND_TOMB}ow{SE_M_ATTRACT}quiz?$"

J_LilycoveCity_PokemonCenter_1F_Text_MaybeNextTime:
	.string "Oh{SE_M_SUPERSONIC}{SE_M_HEAL_BELL}see…\n"
	.string "Well{SE_M_SUPERSONIC}mayb{SE_M_REVERSAL}nex{SE_M_SPIT_UP}time!$"

J_LilycoveCity_PokemonCenter_1F_Text_PickYourPrize:
	.string "Okay{SE_M_SUPERSONIC}th{SE_M_REVERSAL}firs{SE_M_SPIT_UP}thin{SE_M_SANDSTORM}yo{SE_M_DIVE}hav{SE_M_REVERSAL}t{SE_M_ATTRACT2}do\n"
	.string "i{SE_M_GRASSWHISTLE}pic{SE_M_ENCORE2}th{SE_M_REVERSAL}priz{SE_M_REVERSAL}fo{SE_M_SAND_TOMB}th{SE_M_REVERSAL}perso{SE_M_ATTRACT}that\l"
	.string "answer{SE_M_GRASSWHISTLE}you{SE_M_SAND_TOMB}qui{SE_M_SKY_UPPERCUT}correctly.\p"
	.string "Bu{SE_M_SPIT_UP}beware{SE_M_SUPERSONIC}i{SE_M_ACID_ARMOR}th{SE_M_REVERSAL}perso{SE_M_ATTRACT}taking\n"
	.string "th{SE_M_REVERSAL}qui{SE_M_SKY_UPPERCUT}can'{SE_M_SPIT_UP}ge{SE_M_SPIT_UP}i{SE_M_SPIT_UP}right{SE_M_SUPERSONIC}{SE_M_HEAL_BELL}ge{SE_M_SPIT_UP}to\l"
	.string "kee{SE_M_MORNING_SUN}th{SE_M_REVERSAL}prize!$"

J_LilycoveCity_PokemonCenter_1F_Text_QuitChoosingPrize:
	.string "I{SE_M_ACID_ARMOR}yo{SE_M_DIVE}don'{SE_M_SPIT_UP}choos{SE_M_REVERSAL}{SE_M_CHARGE}prize,\n"
	.string "you{SE_M_SAND_TOMB}qui{SE_M_SKY_UPPERCUT}can'{SE_M_SPIT_UP}b{SE_M_REVERSAL}made.\p"
	.string "Ar{SE_M_REVERSAL}yo{SE_M_DIVE}goin{SE_M_SANDSTORM}t{SE_M_ATTRACT2}qui{SE_M_SPIT_UP}making\n"
	.string "you{SE_M_SAND_TOMB}quiz?$"

J_LilycoveCity_PokemonCenter_1F_Text_WriteYourQuiz:
	.string "Oh{SE_M_SUPERSONIC}ho{SE_M_TWISTER}nice!\n"
	.string "That'{SE_M_GRASSWHISTLE}{SE_M_CHARGE}wonderfu{SE_M_BATON_PASS}prize!\p"
	.string "Next{SE_M_SUPERSONIC}yo{SE_M_DIVE}nee{SE_M_WATERFALL}t{SE_M_ATTRACT2}writ{SE_M_REVERSAL}you{SE_M_SAND_TOMB}quiz\n"
	.string "questio{SE_M_ATTRACT}an{SE_M_WATERFALL}it{SE_M_GRASSWHISTLE}answer.$"

J_LilycoveCity_PokemonCenter_1F_Text_QuitWritingQuizQuestion:
	.string "Ar{SE_M_REVERSAL}yo{SE_M_DIVE}goin{SE_M_SANDSTORM}t{SE_M_ATTRACT2}qui{SE_M_SPIT_UP}writing\n"
	.string "you{SE_M_SAND_TOMB}qui{SE_M_SKY_UPPERCUT}question?$"

J_LilycoveCity_PokemonCenter_1F_Text_QuitWritingQuizAnswer:
	.string "Ar{SE_M_REVERSAL}yo{SE_M_DIVE}goin{SE_M_SANDSTORM}t{SE_M_ATTRACT2}qui{SE_M_SPIT_UP}choosing\n"
	.string "you{SE_M_SAND_TOMB}qui{SE_M_SKY_UPPERCUT}answer?$"

J_LilycoveCity_PokemonCenter_1F_Text_IllLookForAChallenger:
	.string "Than{SE_M_ENCORE2}you!\n"
	.string "You'v{SE_M_REVERSAL}pu{SE_M_SPIT_UP}togethe{SE_M_SAND_TOMB}{SE_M_CHARGE}nic{SE_M_REVERSAL}quiz.\p"
	.string "I'l{SE_M_BATON_PASS}g{SE_M_ATTRACT2}loo{SE_M_ENCORE2}fo{SE_M_SAND_TOMB}someon{SE_M_REVERSAL}who'l{SE_M_BATON_PASS}take\n"
	.string "you{SE_M_SAND_TOMB}qui{SE_M_SKY_UPPERCUT}challeng{SE_M_REVERSAL}righ{SE_M_SPIT_UP}away.$"

J_LilycoveCity_PokemonCenter_1F_Text_ImTheContestLady:
	.string "I'{SE_M_MILK_DRINK}th{SE_M_REVERSAL}CONTES{SE_M_SWIFT}LADY!\n"
	.string "{SE_M_HEAL_BELL}sur{SE_M_REVERSAL}d{SE_M_ATTRACT2}lov{SE_M_REVERSAL}CONTESTS!$"

J_LilycoveCity_PokemonCenter_1F_Text_ThankForPokeblock:
	.string "Thank{SE_M_GRASSWHISTLE}fo{SE_M_SAND_TOMB}you{SE_M_SAND_TOMB}{POKEBLOCK} before!$"

J_LilycoveCity_PokemonCenter_1F_Text_MyFriendDisplaysQuality:
	.string "Thi{SE_M_GRASSWHISTLE}i{SE_M_GRASSWHISTLE}m{SE_M_YAWN}frien{SE_M_WATERFALL}{STR_VAR_1}!\n"
	.string "It'{SE_M_GRASSWHISTLE}th{SE_M_REVERSAL}epitom{SE_M_REVERSAL}o{SE_M_ACID_ARMOR}{STR_VAR_2}!\p"
	.string "Bu{SE_M_SPIT_UP}{SE_M_HEAL_BELL}thin{SE_M_ENCORE2}tha{SE_M_SPIT_UP}i{SE_M_SPIT_UP}wil{SE_M_BATON_PASS}display\n"
	.string "eve{SE_M_ATTRACT}mor{SE_M_REVERSAL}{STR_VAR_2}!$"

J_LilycoveCity_PokemonCenter_1F_Text_DontHaveAPokeblockCase:
	.string "So{SE_M_SUPERSONIC}{SE_M_HEAL_BELL}nee{SE_M_WATERFALL}you{SE_M_SAND_TOMB}help!\p"
	.string "Please{SE_M_SUPERSONIC}ma{SE_M_YAWN}{SE_M_HEAL_BELL}hav{SE_M_REVERSAL}on{SE_M_REVERSAL}{POKEBLOCK}?\n"
	.string "Al{SE_M_BATON_PASS}I'{SE_M_MILK_DRINK}askin{SE_M_SANDSTORM}fo{SE_M_SAND_TOMB}i{SE_M_GRASSWHISTLE}one!\p"
	.string "…Oh{SE_M_SUPERSONIC}but…\n"
	.string "Don'{SE_M_SPIT_UP}yo{SE_M_DIVE}hav{SE_M_REVERSAL}{SE_M_CHARGE}{POKEBLOCK} CASE?\l"
	.string "That'{SE_M_GRASSWHISTLE}n{SE_M_ATTRACT2}good{SE_M_PERISH_SONG}Nex{SE_M_SPIT_UP}time{SE_M_SUPERSONIC}then!$"

J_LilycoveCity_PokemonCenter_1F_Text_AskingForOnePokeblock:
	.string "So{SE_M_SUPERSONIC}{SE_M_HEAL_BELL}nee{SE_M_WATERFALL}you{SE_M_SAND_TOMB}help!\p"
	.string "Please{SE_M_SUPERSONIC}ma{SE_M_YAWN}{SE_M_HEAL_BELL}hav{SE_M_REVERSAL}on{SE_M_REVERSAL}{POKEBLOCK}?\n"
	.string "Al{SE_M_BATON_PASS}I'{SE_M_MILK_DRINK}askin{SE_M_SANDSTORM}fo{SE_M_SAND_TOMB}i{SE_M_GRASSWHISTLE}one!$"

J_LilycoveCity_PokemonCenter_1F_Text_ICantHaveOnePokeblock:
	.string "Awww!\n"
	.string "{SE_M_HEAL_BELL}can'{SE_M_SPIT_UP}hav{SE_M_REVERSAL}on{SE_M_REVERSAL}{POKEBLOCK}?!$"

J_LilycoveCity_PokemonCenter_1F_Text_WhatACheapskate:
	.string "Sheesh!\n"
	.string "Wha{SE_M_SPIT_UP}{SE_M_CHARGE}cheapskate!$"

J_LilycoveCity_PokemonCenter_1F_Text_IllUseYourPokeblock:
	.string "Yay!\n"
	.string "Than{SE_M_ENCORE2}you!\p"
	.string "I'l{SE_M_BATON_PASS}fee{SE_M_WATERFALL}m{SE_M_YAWN}POKéMO{SE_M_PSYBEAM2}you{SE_M_SAND_TOMB}{POKEBLOCK}\n"
	.string "righ{SE_M_SPIT_UP}away.$"

J_LilycoveCity_PokemonCenter_1F_Text_NoChangeThanks:
	.string "…I{SE_M_SPIT_UP}doesn'{SE_M_SPIT_UP}see{SE_M_MILK_DRINK}t{SE_M_ATTRACT2}hav{SE_M_REVERSAL}changed\n"
	.string "i{SE_M_ATTRACT}an{SE_M_YAWN}wa{SE_M_YAWN}a{SE_M_SPIT_UP}all…\p"
	.string "Hmm…\p"
	.string "Oh{SE_M_SUPERSONIC}well!\n"
	.string "Than{SE_M_ENCORE2}yo{SE_M_DIVE}ver{SE_M_YAWN}much!$"

J_LilycoveCity_PokemonCenter_1F_Text_ReallyImprovedThanks:
	.string "Oh{SE_M_SUPERSONIC}yay!\n"
	.string "It'{SE_M_GRASSWHISTLE}reall{SE_M_YAWN}delighted!\p"
	.string "{SE_M_HEAL_BELL}thin{SE_M_ENCORE2}i{SE_M_SPIT_UP}reall{SE_M_YAWN}improve{SE_M_WATERFALL}{STR_VAR_1}'s\n"
	.string "{STR_VAR_2} quality{SE_M_SUPERSONIC}too.\p"
	.string "Than{SE_M_ENCORE2}yo{SE_M_DIVE}s{SE_M_ATTRACT2}much!$"

J_LilycoveCity_PokemonCenter_1F_Text_ReadyToEnterContests:
	.string "Hmm…\p"
	.string "{SE_M_HEAL_BELL}thin{SE_M_ENCORE2}w{SE_M_REVERSAL}ma{SE_M_YAWN}b{SE_M_REVERSAL}read{SE_M_YAWN}t{SE_M_ATTRACT2}enter\n"
	.string "som{SE_M_REVERSAL}CONTESTS.\p"
	.string "I{SE_M_ACID_ARMOR}yo{SE_M_DIVE}se{SE_M_REVERSAL}u{SE_M_GRASSWHISTLE}i{SE_M_ATTRACT}on{SE_M_REVERSAL}somewhere,\n"
	.string "{SE_M_HEAL_BELL}hop{SE_M_REVERSAL}you'l{SE_M_BATON_PASS}chee{SE_M_SAND_TOMB}fo{SE_M_SAND_TOMB}us.$"

J_LilycoveCity_PokemonCenter_1F_Text_Zigzagoon:
	.string "{STR_VAR_1}{SE_M_HEAT_WAVE}Guguuh!$"

J_LilycoveCity_PokemonCenter_1F_Text_Kecleon:
	.string "{STR_VAR_1}{SE_M_HEAT_WAVE}Igigigiiih!$"

J_LilycoveCity_PokemonCenter_1F_Text_Poochyena:
	.string "{STR_VAR_1}{SE_M_HEAT_WAVE}Baaarun…$"

J_LilycoveCity_PokemonCenter_1F_Text_Pikachu:
	.string "{STR_VAR_1}{SE_M_HEAT_WAVE}Pikka!$"

J_LilycoveCity_PokemonCenter_1F_Text_Skitty:
	.string "{STR_VAR_1}{SE_M_HEAT_WAVE}Umyaaaan!$"

