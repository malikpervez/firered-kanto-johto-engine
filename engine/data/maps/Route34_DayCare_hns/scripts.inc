@ Johto (data/maps/Route34_DayCare_hns/scripts.inc), as built into the FireRed game.

Route34_DayCare_hns_MapScripts::
	.byte 0

Route34_DayCare_Bookshelf1::
	lock
	msgbox Route34_DayCare_Text_Bookshelf1, MSGBOX_AUTOCLOSE
	helpwindow HELP_DAYCARE1_WINDOW
	release
	end

Route34_DayCare_Bookshelf2::
	lock
	msgbox Route34_DayCare_Text_Bookshelf2, MSGBOX_AUTOCLOSE
	helpwindow HELP_DAYCARE2_WINDOW
	release
	end

Route34_DayCare_Bookshelf3::
	lock
	msgbox Route34_DayCare_Text_Bookshelf3, MSGBOX_AUTOCLOSE
	helpwindow HELP_DAYCARE3_WINDOW
	release
	end

Route34_DayCare_Bookshelf4::
	lock
	msgbox Route34_DayCare_Text_Bookshelf4, MSGBOX_AUTOCLOSE
	helpwindow HELP_DAYCARE4_WINDOW
	release
	end

Route34_DayCare_Text_Bookshelf1:
	.string "{SE_M_BONEMERANG}BAB{SE_M_MOONLIGHT}POKéMO{SE_M_PSYBEAM2}encyclopedia!\p"
	.string "VOLUM{SE_M_SWORDS_DANCE}1{SE_M_HEAT_WAVE}AL{SE_M_BRICK_BREAK}ABOU{SE_M_SWIFT}ABILITIES$"

Route34_DayCare_Text_Bookshelf2:
	.string "{SE_M_BONEMERANG}BAB{SE_M_MOONLIGHT}POKéMO{SE_M_PSYBEAM2}encyclopedia!\p"
	.string "VOLUM{SE_M_SWORDS_DANCE}2{SE_M_HEAT_WAVE}TYPICA{SE_M_BRICK_BREAK}TYPES$"

Route34_DayCare_Text_Bookshelf3:
	.string "{SE_M_BONEMERANG}BAB{SE_M_MOONLIGHT}POKéMO{SE_M_PSYBEAM2}encyclopedia!\p"
	.string "VOLUM{SE_M_SWORDS_DANCE}3{SE_M_HEAT_WAVE}BABIES{SE_M_ABSORB}CRIES$"

Route34_DayCare_Text_Bookshelf4:
	.string "{SE_M_BONEMERANG}BAB{SE_M_MOONLIGHT}POKéMO{SE_M_PSYBEAM2}encyclopedia!\p"
	.string "VOLUM{SE_M_SWORDS_DANCE}4{SE_M_HEAT_WAVE}ADORABL{SE_M_SWORDS_DANCE}ACTIONS$"

Route34_DayCare_EventScript_Clerk::
	lock
	faceplayer
	goto_if_set JOHTO_FLAG_RECEIVED_ODD_EGG, Route34_DayCare_EventScript_ClerkAfter
	msgbox Route34_DayCare_Text_ClerkBefore, MSGBOX_DEFAULT
	specialvar VAR_0x8004, GetMaxPartySize
	getpartysize
	goto_if_eq VAR_RESULT, VAR_0x8004, Route34_DayCare_EventScript_ClerkPartyFull
	msgbox Route34_DayCare_Text_ClerkQuestion, MSGBOX_DEFAULT
	closemessage
	setvar VAR_0x8004, EASY_CHAT_TYPE_INTERVIEW
	setvar VAR_0x8005, 0
	call J_Common_ShowEasyChatScreen
	lock
	faceplayer
	switch VAR_RESULT
	case 0, Route34_DayCare_EventScript_ClerkRejection
	case 1, Route34_DayCare_EventScript_GivePichu
	case 2, Route34_DayCare_EventScript_GiveCleffa
	case 3, Route34_DayCare_EventScript_GiveIgglybuff
	case 4, Route34_DayCare_EventScript_GiveTyrogue
	case 5, Route34_DayCare_EventScript_GiveSmoochum
	case 6, Route34_DayCare_EventScript_GiveElekid
	case 7, Route34_DayCare_EventScript_GiveMagby
	case 8, Route34_DayCare_EventScript_GiveMantyke
	case 9, Route34_DayCare_EventScript_GiveBonsly
	case 10, Route34_DayCare_EventScript_GiveHappiny
	case 11, Route34_DayCare_EventScript_GiveMimeJr
	closemessage
	release
	end

Route34_DayCare_EventScript_GivePichu::
	giveoddegg 1
	goto Route34_DayCare_EventScript_Clerk_GaveEgg

Route34_DayCare_EventScript_GiveCleffa::
	giveoddegg 2
	goto Route34_DayCare_EventScript_Clerk_GaveEgg

Route34_DayCare_EventScript_GiveIgglybuff::
	giveoddegg 3
	goto Route34_DayCare_EventScript_Clerk_GaveEgg

Route34_DayCare_EventScript_GiveTyrogue::
	giveoddegg 4
	goto Route34_DayCare_EventScript_Clerk_GaveEgg

Route34_DayCare_EventScript_GiveSmoochum::
	giveoddegg 5
	goto Route34_DayCare_EventScript_Clerk_GaveEgg

Route34_DayCare_EventScript_GiveElekid::
	giveoddegg 6
	goto Route34_DayCare_EventScript_Clerk_GaveEgg

Route34_DayCare_EventScript_GiveMagby::
	giveoddegg 7
	goto Route34_DayCare_EventScript_Clerk_GaveEgg

Route34_DayCare_EventScript_GiveMantyke::
	giveoddegg 8
	goto Route34_DayCare_EventScript_Clerk_GaveEgg

Route34_DayCare_EventScript_GiveBonsly::
	giveoddegg 9
	goto Route34_DayCare_EventScript_Clerk_GaveEgg

Route34_DayCare_EventScript_GiveHappiny::
	giveoddegg 10
	goto Route34_DayCare_EventScript_Clerk_GaveEgg

Route34_DayCare_EventScript_GiveMimeJr::
	giveoddegg 11
	goto Route34_DayCare_EventScript_Clerk_GaveEgg

Route34_DayCare_EventScript_Clerk_GaveEgg::
	msgbox Route34_DayCare_Text_TakeCare, MSGBOX_DEFAULT
	closemessage
	delay 30
	setflag JOHTO_FLAG_RECEIVED_ODD_EGG
	playfanfare MUS_RG_OBTAIN_KEY_ITEM
	message Route34_DayCare_Text_ReceivedOddEgg
	waitfanfare
	closemessage
	release
	end

Route34_DayCare_EventScript_ClerkPartyFull::
	msgbox Route34_DayCare_Text_ClerkNoRoom, MSGBOX_DEFAULT
	closemessage
	release
	end

Route34_DayCare_EventScript_ClerkRejection::
	msgbox Route34_DayCare_Text_Rejection, MSGBOX_DEFAULT
	closemessage
	release
	end

Route34_DayCare_EventScript_ClerkAfter::
	msgbox Route34_DayCare_Text_ClerkAfter, MSGBOX_DEFAULT
	closemessage
	release
	end

Route34_DayCare_Text_ClerkBefore:
	.string "I'{SE_M_MILK_DRINK}th{SE_M_REVERSAL}DAY-CAR{SE_M_SWORDS_DANCE}couple'{SE_M_GRASSWHISTLE}son.\p"
	.string "A{SE_M_ATTRACT}OD{SE_M_FAINT_ATTACK}EG{SE_M_SWAGGER}wa{SE_M_GRASSWHISTLE}foun{SE_M_WATERFALL}wit{SE_M_TRI_ATTACK}{SE_M_CHARGE}TRAINER's\n"
	.string "POKéMON{SE_M_SUPERSONIC}bu{SE_M_SPIT_UP}the{SE_M_YAWN}didn'{SE_M_SPIT_UP}wan{SE_M_SPIT_UP}it...\p"
	.string "I'{SE_M_WATERFALL}offe{SE_M_SAND_TOMB}i{SE_M_SPIT_UP}t{SE_M_ATTRACT2}you...\n"
	.string "Bu{SE_M_SPIT_UP}ho{SE_M_TWISTER}ca{SE_M_ATTRACT}{SE_M_HEAL_BELL}kno{SE_M_TWISTER}you'l{SE_M_BATON_PASS}tak{SE_M_REVERSAL}good\l"
	.string "car{SE_M_REVERSAL}o{SE_M_ACID_ARMOR}it?$"

Route34_DayCare_Text_ClerkNoRoom:
	.string "I{SE_M_SPIT_UP}look{SE_M_GRASSWHISTLE}lik{SE_M_REVERSAL}yo{SE_M_DIVE}can'{SE_M_SPIT_UP}carr{SE_M_YAWN}another\n"
	.string "POKéMO{SE_M_PSYBEAM2}anyway.$"

Route34_DayCare_Text_ClerkQuestion:
	.string "Answe{SE_M_SAND_TOMB}thi{SE_M_GRASSWHISTLE}questio{SE_M_ATTRACT}fo{SE_M_SAND_TOMB}me.\n"
	.string "Ho{SE_M_TWISTER}d{SE_M_ATTRACT2}yo{SE_M_DIVE}fee{SE_M_BATON_PASS}abou{SE_M_SPIT_UP}thi{SE_M_GRASSWHISTLE}OD{SE_M_FAINT_ATTACK}EGG?$"

Route34_DayCare_Text_Rejection:
	.string "Hmm{SE_M_SUPERSONIC}{SE_M_HEAL_BELL}thin{SE_M_ENCORE2}thi{SE_M_GRASSWHISTLE}EG{SE_M_SWAGGER}isn'{SE_M_SPIT_UP}fo{SE_M_SAND_TOMB}you.\p"
	.string "I{SE_M_SPIT_UP}woul{SE_M_WATERFALL}b{SE_M_REVERSAL}irresponsibl{SE_M_REVERSAL}o{SE_M_ACID_ARMOR}m{SE_M_REVERSAL}to\n"
	.string "giv{SE_M_REVERSAL}ou{SE_M_SPIT_UP}{SE_M_CHARGE}preciou{SE_M_GRASSWHISTLE}EG{SE_M_SWAGGER}lik{SE_M_REVERSAL}this\l"
	.string "t{SE_M_ATTRACT2}someon{SE_M_REVERSAL}wh{SE_M_ATTRACT2}isn'{SE_M_SPIT_UP}a{SE_M_GRASSWHISTLE}well-read\l"
	.string "o{SE_M_ATTRACT}th{SE_M_REVERSAL}subjec{SE_M_SPIT_UP}o{SE_M_ACID_ARMOR}bab{SE_M_YAWN}POKéMON!$"

Route34_DayCare_Text_ReceivedOddEgg:
	.string "{PLAYER} Receive{SE_M_WATERFALL}th{SE_M_REVERSAL}OD{SE_M_FAINT_ATTACK}EGG.$"

Route34_DayCare_Text_TakeCare:
	.string "{SE_M_HEAL_BELL}kne{SE_M_TWISTER}yo{SE_M_DIVE}wer{SE_M_REVERSAL}th{SE_M_REVERSAL}righ{SE_M_SPIT_UP}trainer\n"
	.string "fo{SE_M_SAND_TOMB}th{SE_M_REVERSAL}job{SE_M_PERISH_SONG}Tak{SE_M_REVERSAL}goo{SE_M_WATERFALL}car{SE_M_REVERSAL}o{SE_M_ACID_ARMOR}it!$"

Route34_DayCare_Text_ClerkAfter:
	.string "W{SE_M_REVERSAL}se{SE_M_REVERSAL}{SE_M_CHARGE}lo{SE_M_SPIT_UP}o{SE_M_ACID_ARMOR}thos{SE_M_REVERSAL}egg{SE_M_GRASSWHISTLE}around\n"
	.string "here.\p"
	.string "Somethin{SE_M_SANDSTORM}wa{SE_M_GRASSWHISTLE}differen{SE_M_SPIT_UP}abou{SE_M_SPIT_UP}that\n"
	.string "one{SE_M_SUPERSONIC}though.$"

Route34_DayCare_EventScript_Ditto::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_DITTO, CRY_MODE_NORMAL
	msgbox Route34_DayCare_Text_Ditto, MSGBOX_DEFAULT
	waitmoncry
	release
	end

Route34_DayCare_Text_Ditto:
	.string "DITTO{SE_M_HEAT_WAVE}Tto!$"

Route34_EventScript_DaycareMan::
	lock
	faceplayer
	specialvar VAR_RESULT, IsPartyLimitChallengeActive
	goto_if_eq VAR_RESULT, TRUE, Route34_DayCare_EventScript_ClosedForChallenge
	special GetDaycareMonNicknames
	specialvar VAR_RESULT, GetDaycareState
	goto_if_eq VAR_RESULT, DAYCARE_EGG_WAITING, Route34_EventScript_DaycareEggWaiting
	goto_if_eq VAR_RESULT, DAYCARE_ONE_MON, Route34_EventScript_CheckOnOneMon
	goto_if_eq VAR_RESULT, DAYCARE_TWO_MONS, Route34_EventScript_CheckOnTwoMons
	msgbox Route34_Text_SeeWifeIfYoudLikeMeToRaiseMon, MSGBOX_DEFAULT
	release
	end

Route34_EventScript_DaycareEggWaiting::
	msgbox Route34_Text_DoYouWantEgg, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, Route34_EventScript_DaycareAcceptEgg
	msgbox Route34_Text_IWillKeepDoYouWantIt, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, Route34_EventScript_DaycareAcceptEgg
	msgbox Route34_Text_IllKeepIt, MSGBOX_DEFAULT
	clearflag JOHTO_FLAG_PENDING_DAYCARE_EGG
	special RejectEggFromDayCare
	release
	end

Route34_EventScript_DaycareAcceptEgg::
	specialvar VAR_0x8004, GetMaxPartySize
	specialvar VAR_RESULT, CalculatePlayerPartyCount
	goto_if_ne VAR_RESULT, VAR_0x8004, Route34_EventScript_DaycareReceiveEgg
	msgbox Route34_Text_YouHaveNoRoomForIt, MSGBOX_DEFAULT
	release
	end

Route34_EventScript_DaycareReceiveEgg::
	message Route34_Text_ReceivedEgg
	playfanfare ((558 + 1) + 0xA1)
	waitfanfare
	waitbuttonpress
	msgbox Route34_Text_TakeGoodCareOfIt, MSGBOX_DEFAULT
	special GiveEggFromDaycare
	clearflag JOHTO_FLAG_PENDING_DAYCARE_EGG
	release
	end

Route34_EventScript_CheckMonReceivedMail::
	specialvar VAR_RESULT, CheckDaycareMonReceivedMail
	call_if_eq VAR_RESULT, 1, Route34_EventScript_MonReceivedMail
	return

Route34_EventScript_MonReceivedMail::
	msgbox Route34_Text_FriendlyWithOtherTrainersMon, MSGBOX_DEFAULT
	return

Route34_EventScript_CheckOnOneMon::
	special GetDaycareMonNicknames
	msgbox Route34_Text_YourMonIsDoingFine, MSGBOX_DEFAULT
	setvar VAR_0x8004, 0
	call Route34_EventScript_CheckMonReceivedMail
	release
	end

Route34_EventScript_CheckOnTwoMons::
	special GetDaycareMonNicknames
	msgbox Route34_Text_YourMonsAreDoingFine, MSGBOX_DEFAULT
	special SetDaycareCompatibilityString
	special ShowFieldMessageStringVar4
	waitmessage
	waitbuttonpress
	setvar VAR_0x8004, 0
	call Route34_EventScript_CheckMonReceivedMail
	setvar VAR_0x8004, 1
	call Route34_EventScript_CheckMonReceivedMail
	release
	end

Route34_DayCare_EventScript_DaycareWoman::
	lock
	faceplayer
	specialvar VAR_RESULT, IsPartyLimitChallengeActive
	goto_if_eq VAR_RESULT, TRUE, Route34_DayCare_EventScript_ClosedForChallenge
	specialvar VAR_RESULT, GetDaycareState
	goto_if_eq VAR_RESULT, DAYCARE_EGG_WAITING, Route34_DayCare_EventScript_EggWaiting
	goto_if_eq VAR_RESULT, DAYCARE_ONE_MON, Route34_DayCare_EventScript_OneMonInDaycare
	goto_if_eq VAR_RESULT, DAYCARE_TWO_MONS, Route34_DayCare_EventScript_TwoMonsInDaycare
	msgbox Route34_DayCare_Text_WouldYouLikeUsToRaiseAMon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, Route34_DayCare_EventScript_GiveMonToRaise
	msgbox Route34_DayCare_Text_FineThenComeAgain, MSGBOX_DEFAULT
	release
	end

Route34_DayCare_EventScript_GiveMonToRaise::
	specialvar VAR_RESULT, CountPartyNonEggMons
	goto_if_eq VAR_RESULT, 1, Route34_DayCare_EventScript_OnlyOneMon
	specialvar VAR_RESULT, CountPartyAliveNonEggMons
	goto_if_eq VAR_RESULT, 2, Route34_DayCare_EventScript_OnlyTwoAliveMons
	msgbox Route34_DayCare_Text_WhichMonShouldWeRaise, MSGBOX_DEFAULT
	fadescreen FADE_TO_BLACK
	special ChooseSendDaycareMon
	waitstate
	goto_if_eq VAR_0x8004, PARTY_NOTHING_CHOSEN, Route34_DayCare_EventScript_ComeAgain
	specialvar VAR_RESULT, CountPartyAliveNonEggMons_IgnoreVar0x8004Slot
	goto_if_eq VAR_RESULT, 0, Route34_DayCare_EventScript_OnlyOneAliveMon
	specialvar VAR_0x8005, GetSelectedMonNicknameAndSpecies
	waitse
	playmoncry VAR_0x8005, CRY_MODE_NORMAL
	msgbox Route34_DayCare_Text_WellRaiseYourMon, MSGBOX_DEFAULT
	waitmoncry
	special StoreSelectedPokemonInDaycare
	callnative UpdateFollowingPokemon
	incrementgamestat GAME_STAT_USED_DAYCARE
	specialvar VAR_RESULT, GetDaycareState
	goto_if_eq VAR_RESULT, DAYCARE_ONE_MON, Route34_DayCare_EventScript_CanRaiseOneMore
	release
	end

Route34_DayCare_EventScript_ComeAgain::
	msgbox Route34_DayCare_Text_ComeAgain, MSGBOX_DEFAULT
	release
	end

Route34_DayCare_EventScript_CanRaiseOneMore::
	msgbox Route34_DayCare_Text_WeCanRaiseOneMore, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, Route34_DayCare_EventScript_GiveMonToRaise
	goto Route34_DayCare_EventScript_ComeAgain
	end

Route34_DayCare_EventScript_ClosedForChallenge::
	msgbox Route34_DayCare_Text_ClosedForChallenge, MSGBOX_DEFAULT
	release
	end

Route34_DayCare_Text_ClosedForChallenge:
	.string "Sorry{SE_M_SUPERSONIC}w{SE_M_REVERSAL}can'{SE_M_SPIT_UP}loo{SE_M_ENCORE2}afte{SE_M_SAND_TOMB}your\n"
	.string "POKéMO{SE_M_PSYBEAM2}durin{SE_M_SANDSTORM}{SE_M_CHARGE}part{SE_M_YAWN}limit\l"
	.string "challenge!$"

Route34_DayCare_EventScript_OnlyOneMon::
	msgbox Route34_DayCare_Text_YouHaveJustOneMon, MSGBOX_DEFAULT
	release
	end

Route34_DayCare_EventScript_OnlyOneAliveMon::
	msgbox Route34_DayCare_Text_WhatWillYouBattleWith, MSGBOX_DEFAULT
	release
	end

Route34_DayCare_EventScript_OnlyTwoAliveMons::
	msgbox Route34_DayCare_Text_YoullBeLeftWithJustOne, MSGBOX_DEFAULT
	release
	end

Route34_DayCare_EventScript_EggWaiting::
	msgbox Route34_DayCare_Text_HusbandWasLookingForYou, MSGBOX_DEFAULT
	release
	end

Route34_DayCare_EventScript_YourMonHasGrownXLevels::
	msgbox Route34_DayCare_Text_YourMonHasGrownXLevels, MSGBOX_DEFAULT
	return

Route34_DayCare_EventScript_DisplayLevelsGained::
	specialvar VAR_RESULT, GetNumLevelsGainedFromDaycare
	call_if_ne VAR_RESULT, 0, Route34_DayCare_EventScript_YourMonHasGrownXLevels
	return

Route34_DayCare_EventScript_OneMonInDaycare::
	msgbox Route34_DayCare_Text_GoodToSeeYou, MSGBOX_DEFAULT
	setvar VAR_0x8004, 0
	call Route34_DayCare_EventScript_DisplayLevelsGained
	msgbox Route34_DayCare_Text_WeCanRaiseOneMore, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, Route34_DayCare_EventScript_GiveMonToRaise
	msgbox Route34_DayCare_Text_TakeYourMonBack, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, Route34_DayCare_EventScript_TryRetrieveMon
	goto Route34_DayCare_EventScript_ComeAgain
	end

Route34_DayCare_EventScript_TryRetrieveMon::
	specialvar VAR_0x8004, GetMaxPartySize
	specialvar VAR_RESULT, CalculatePlayerPartyCount
	goto_if_eq VAR_RESULT, VAR_0x8004, Route34_DayCare_EventScript_NoRoom
	specialvar VAR_RESULT, GetDaycareState
	setvar VAR_0x8004, 0
	goto_if_eq VAR_RESULT, DAYCARE_ONE_MON, Route34_DayCare_EventScript_CostPrompt
	special ShowDaycareLevelMenu
	waitstate
	copyvar VAR_0x8004, VAR_RESULT
	goto_if_eq VAR_RESULT, DAYCARE_EXITED_LEVEL_MENU, Route34_DayCare_EventScript_ComeAgain
	goto Route34_DayCare_EventScript_CostPrompt
	end

Route34_DayCare_EventScript_CostPrompt::
	special GetDaycareCost
	msgbox Route34_DayCare_Text_ItWillCostX, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, Route34_DayCare_EventScript_CheckEnoughMoney
	goto Route34_DayCare_EventScript_ComeAgain
	end

Route34_DayCare_EventScript_CheckEnoughMoney::
	specialvar VAR_RESULT, IsEnoughForCostInVar0x8005
	goto_if_eq VAR_RESULT, 1, Route34_DayCare_EventScript_RetrieveMon
	msgbox Route34_DayCare_Text_NotEnoughMoney, MSGBOX_DEFAULT
	release
	end

Route34_DayCare_EventScript_RetrieveMon::


	specialvar VAR_RESULT, TakePokemonFromDaycare
	special SubtractMoneyFromVar0x8005
	playse SE_SHOP
	msgbox Route34_DayCare_Text_HeresYourMon, MSGBOX_DEFAULT
	waitse
	playmoncry VAR_RESULT, CRY_MODE_NORMAL
	msgbox Route34_DayCare_Text_TookBackMon, MSGBOX_DEFAULT
	waitmoncry
	specialvar VAR_RESULT, GetDaycareState
	goto_if_eq VAR_RESULT, DAYCARE_ONE_MON, Route34_DayCare_EventScript_AskRetrieveOtherMon
	goto Route34_DayCare_EventScript_ComeAgain
	end

Route34_DayCare_EventScript_AskRetrieveOtherMon::
	msgbox Route34_DayCare_Text_TakeOtherOneBackToo, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, Route34_DayCare_EventScript_TryRetrieveMon
	goto Route34_DayCare_EventScript_ComeAgain
	end

Route34_DayCare_EventScript_NoRoom::
	msgbox Route34_DayCare_Text_YourTeamIsFull, MSGBOX_DEFAULT
	release
	end

Route34_DayCare_Movement_RetrieveDaycareMon:
	delay_16
	delay_16
	face_left
	delay_16
	delay_16
	face_right
	delay_16
	delay_16
	face_up
	walk_slow_up
	set_invisible
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	face_down
	set_visible
	walk_slow_down
	step_end

Route34_DayCare_EventScript_UnusedEnd::
	end

Route34_DayCare_EventScript_TwoMonsInDaycare::
	msgbox Route34_DayCare_Text_GoodToSeeYou, MSGBOX_DEFAULT
	setvar VAR_0x8004, 0
	call Route34_DayCare_EventScript_DisplayLevelsGained
	setvar VAR_0x8004, 1
	call Route34_DayCare_EventScript_DisplayLevelsGained
	msgbox Route34_DayCare_Text_TakeYourMonBack, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, Route34_DayCare_EventScript_TryRetrieveMon
	msgbox Route34_DayCare_Text_ComeAgain, MSGBOX_DEFAULT
	release
	end

Route34_Text_SeeWifeIfYoudLikeMeToRaiseMon:
	.string "I'{SE_M_MILK_DRINK}th{SE_M_REVERSAL}DAY-CAR{SE_M_SWORDS_DANCE}MAN.\p"
	.string "{SE_M_HEAL_BELL}hel{SE_M_MORNING_SUN}tak{SE_M_REVERSAL}car{SE_M_REVERSAL}o{SE_M_ACID_ARMOR}th{SE_M_REVERSAL}precious\n"
	.string "POKéMO{SE_M_PSYBEAM2}o{SE_M_ACID_ARMOR}TRAINERS.\p"
	.string "I{SE_M_ACID_ARMOR}you'{SE_M_WATERFALL}lik{SE_M_REVERSAL}m{SE_M_REVERSAL}t{SE_M_ATTRACT2}rais{SE_M_REVERSAL}you{SE_M_SAND_TOMB}POKéMON,\n"
	.string "hav{SE_M_REVERSAL}{SE_M_CHARGE}wor{SE_M_WATERFALL}wit{SE_M_TRI_ATTACK}m{SE_M_YAWN}wife.$"

Route34_Text_DoYouWantEgg:
	.string "Ah{SE_M_SUPERSONIC}it'{SE_M_GRASSWHISTLE}you!\p"
	.string "W{SE_M_REVERSAL}wer{SE_M_REVERSAL}raisin{SE_M_SANDSTORM}you{SE_M_SAND_TOMB}POKéMON,\n"
	.string "an{SE_M_WATERFALL}m{SE_M_YAWN}goodness{SE_M_SUPERSONIC}wer{SE_M_REVERSAL}w{SE_M_REVERSAL}surprised!\p"
	.string "You{SE_M_SAND_TOMB}POKéMO{SE_M_PSYBEAM2}ha{SE_M_WATERFALL}a{SE_M_ATTRACT}EGG!\p"
	.string "W{SE_M_REVERSAL}don'{SE_M_SPIT_UP}kno{SE_M_TWISTER}ho{SE_M_TWISTER}i{SE_M_SPIT_UP}go{SE_M_SPIT_UP}there,\n"
	.string "bu{SE_M_SPIT_UP}you{SE_M_SAND_TOMB}POKéMO{SE_M_PSYBEAM2}ha{SE_M_WATERFALL}it.\p"
	.string "Yo{SE_M_DIVE}d{SE_M_ATTRACT2}wan{SE_M_SPIT_UP}it{SE_M_SUPERSONIC}yes?$"

Route34_Text_YourMonIsDoingFine:
	.string "Ah{SE_M_SUPERSONIC}it'{SE_M_GRASSWHISTLE}you{SE_M_DRAGON_RAGE}Goo{SE_M_WATERFALL}t{SE_M_ATTRACT2}se{SE_M_REVERSAL}you.\n"
	.string "You{SE_M_SAND_TOMB}{STR_VAR_1}'{SE_M_GRASSWHISTLE}doin{SE_M_SANDSTORM}fine.$"

Route34_Text_IllKeepIt:
	.string "Wel{SE_M_BATON_PASS}then{SE_M_SUPERSONIC}I'l{SE_M_BATON_PASS}kee{SE_M_MORNING_SUN}it.\n"
	.string "Thanks!$"

Route34_Text_YouHaveNoRoomForIt:
	.string "Yo{SE_M_DIVE}hav{SE_M_REVERSAL}n{SE_M_ATTRACT2}roo{SE_M_MILK_DRINK}fo{SE_M_SAND_TOMB}it…\n"
	.string "Com{SE_M_REVERSAL}bac{SE_M_ENCORE2}whe{SE_M_ATTRACT}you'v{SE_M_REVERSAL}mad{SE_M_REVERSAL}room.$"

Route34_Text_ReceivedEgg:
	.string "{PLAYER} receive{SE_M_WATERFALL}th{SE_M_REVERSAL}EG{SE_M_SWAGGER}from\n"
	.string "th{SE_M_REVERSAL}DAY-CAR{SE_M_SWORDS_DANCE}MAN.$"

Route34_Text_TakeGoodCareOfIt:
	.string "Tak{SE_M_REVERSAL}goo{SE_M_WATERFALL}car{SE_M_REVERSAL}o{SE_M_ACID_ARMOR}it.$"

Route34_Text_FriendlyWithOtherTrainersMon:
	.string "B{SE_M_YAWN}th{SE_M_REVERSAL}way{SE_M_SUPERSONIC}abou{SE_M_SPIT_UP}you{SE_M_SAND_TOMB}{STR_VAR_1},\n"
	.string "i{SE_M_SPIT_UP}seeme{SE_M_WATERFALL}t{SE_M_ATTRACT2}b{SE_M_REVERSAL}friendl{SE_M_YAWN}with\l"
	.string "{STR_VAR_2}'{SE_M_GRASSWHISTLE}{STR_VAR_3}.\p"
	.string "{SE_M_HEAL_BELL}ma{SE_M_YAWN}eve{SE_M_ATTRACT}hav{SE_M_REVERSAL}see{SE_M_ATTRACT}i{SE_M_SPIT_UP}receiving\n"
	.string "{SE_M_CHARGE}piec{SE_M_REVERSAL}o{SE_M_ACID_ARMOR}MAIL.$"

Route34_Text_SeeWifeIfYouWantToPickUpMon:
	.string "I{SE_M_ACID_ARMOR}yo{SE_M_DIVE}wan{SE_M_SPIT_UP}t{SE_M_ATTRACT2}pic{SE_M_ENCORE2}u{SE_M_MORNING_SUN}you{SE_M_SAND_TOMB}POKéMON,\n"
	.string "hav{SE_M_REVERSAL}{SE_M_CHARGE}wor{SE_M_WATERFALL}wit{SE_M_TRI_ATTACK}m{SE_M_YAWN}wife.$"

Route34_Text_YourMonsAreDoingFine:
	.string "Ah{SE_M_SUPERSONIC}it'{SE_M_GRASSWHISTLE}you{SE_M_DRAGON_RAGE}You{SE_M_SAND_TOMB}{STR_VAR_1} and\n"
	.string "{STR_VAR_2} ar{SE_M_REVERSAL}doin{SE_M_SANDSTORM}fine.$"

Route34_Text_IWillKeepDoYouWantIt:
	.string "{SE_M_HEAL_BELL}reall{SE_M_YAWN}wil{SE_M_BATON_PASS}kee{SE_M_MORNING_SUN}it.\n"
	.string "Yo{SE_M_DIVE}d{SE_M_ATTRACT2}wan{SE_M_SPIT_UP}this{SE_M_SUPERSONIC}yes?$"

Route34_DayCare_Text_WouldYouLikeUsToRaiseAMon:
	.string "I'{SE_M_MILK_DRINK}th{SE_M_REVERSAL}DAY-CAR{SE_M_SWORDS_DANCE}LADY.\p"
	.string "W{SE_M_REVERSAL}ca{SE_M_ATTRACT}rais{SE_M_REVERSAL}POKéMO{SE_M_PSYBEAM2}fo{SE_M_SAND_TOMB}you.\p"
	.string "Woul{SE_M_WATERFALL}yo{SE_M_DIVE}lik{SE_M_REVERSAL}u{SE_M_GRASSWHISTLE}t{SE_M_ATTRACT2}rais{SE_M_REVERSAL}one?$"

Route34_DayCare_Text_WhichMonShouldWeRaise:
	.string "Whic{SE_M_TRI_ATTACK}POKéMO{SE_M_PSYBEAM2}shoul{SE_M_WATERFALL}w{SE_M_REVERSAL}rais{SE_M_REVERSAL}for\n"
	.string "you?$"

Route34_DayCare_Text_WellRaiseYourMon:
	.string "Fine{SE_M_SUPERSONIC}we'l{SE_M_BATON_PASS}rais{SE_M_REVERSAL}you{SE_M_SAND_TOMB}{STR_VAR_1}\n"
	.string "fo{SE_M_SAND_TOMB}{SE_M_CHARGE}while.\p"
	.string "Com{SE_M_REVERSAL}bac{SE_M_ENCORE2}fo{SE_M_SAND_TOMB}i{SE_M_SPIT_UP}later.$"

Route34_DayCare_Text_WeCanRaiseOneMore:
	.string "W{SE_M_REVERSAL}ca{SE_M_ATTRACT}rais{SE_M_REVERSAL}tw{SE_M_ATTRACT2}o{SE_M_ACID_ARMOR}you{SE_M_SAND_TOMB}POKéMON.\n"
	.string "Woul{SE_M_WATERFALL}yo{SE_M_DIVE}lik{SE_M_REVERSAL}u{SE_M_GRASSWHISTLE}t{SE_M_ATTRACT2}rais{SE_M_REVERSAL}on{SE_M_REVERSAL}more?$"

Route34_DayCare_Text_HusbandWasLookingForYou:
	.string "M{SE_M_YAWN}husban{SE_M_WATERFALL}wa{SE_M_GRASSWHISTLE}lookin{SE_M_SANDSTORM}fo{SE_M_SAND_TOMB}you.$"

Route34_DayCare_Text_FineThenComeAgain:
	.string "Oh{SE_M_SUPERSONIC}fine{SE_M_SUPERSONIC}then.\n"
	.string "Com{SE_M_REVERSAL}again.$"

Route34_DayCare_Text_NotEnoughMoney:
	.string "Yo{SE_M_DIVE}don'{SE_M_SPIT_UP}hav{SE_M_REVERSAL}enoug{SE_M_TRI_ATTACK}money…$"

Route34_DayCare_Text_TakeOtherOneBackToo:
	.string "Wil{SE_M_BATON_PASS}yo{SE_M_DIVE}tak{SE_M_REVERSAL}bac{SE_M_ENCORE2}th{SE_M_REVERSAL}othe{SE_M_SAND_TOMB}one,\n"
	.string "too?$"

Route34_DayCare_Text_ComeAgain:
	.string "Fine.\n"
	.string "Com{SE_M_REVERSAL}again.$"

Route34_DayCare_Text_GoodToSeeYou:
	.string "Ah{SE_M_SUPERSONIC}it'{SE_M_GRASSWHISTLE}you{SE_M_DRAGON_RAGE}Goo{SE_M_WATERFALL}t{SE_M_ATTRACT2}se{SE_M_REVERSAL}you.\n"
	.string "You{SE_M_SAND_TOMB}POKéMO{SE_M_PSYBEAM2}ca{SE_M_ATTRACT}onl{SE_M_YAWN}b{SE_M_REVERSAL}doin{SE_M_SANDSTORM}good!$"

Route34_DayCare_Text_YourMonHasGrownXLevels:
	.string "B{SE_M_YAWN}level{SE_M_SUPERSONIC}you{SE_M_SAND_TOMB}{STR_VAR_1} has\n"
	.string "grow{SE_M_ATTRACT}b{SE_M_YAWN}{STR_VAR_2}.$"

Route34_DayCare_Text_YourTeamIsFull:
	.string "You{SE_M_SAND_TOMB}POKéMO{SE_M_PSYBEAM2}tea{SE_M_MILK_DRINK}i{SE_M_GRASSWHISTLE}full.\n"
	.string "Mak{SE_M_REVERSAL}room{SE_M_SUPERSONIC}the{SE_M_ATTRACT}com{SE_M_REVERSAL}se{SE_M_REVERSAL}me.$"

Route34_DayCare_Text_TakeBackWhichMon:
	.string "Whic{SE_M_TRI_ATTACK}POKéMO{SE_M_PSYBEAM2}wil{SE_M_BATON_PASS}yo{SE_M_DIVE}tak{SE_M_REVERSAL}back?$"

Route34_DayCare_Text_ItWillCostX:
	.string "I{SE_M_ACID_ARMOR}yo{SE_M_DIVE}wan{SE_M_SPIT_UP}you{SE_M_SAND_TOMB}{STR_VAR_1} back,\n"
	.string "i{SE_M_SPIT_UP}wil{SE_M_BATON_PASS}cos{SE_M_SPIT_UP}¥{STR_VAR_2}.$"

Route34_DayCare_Text_HeresYourMon:
	.string "Perfect!\n"
	.string "Here'{SE_M_GRASSWHISTLE}you{SE_M_SAND_TOMB}POKéMON.$"

Route34_DayCare_Text_TookBackMon:
	.string "{PLAYER} too{SE_M_ENCORE2}bac{SE_M_ENCORE2}{STR_VAR_1} from\n"
	.string "th{SE_M_REVERSAL}DAY-CAR{SE_M_SWORDS_DANCE}LADY.$"

Route34_DayCare_Text_YouHaveJustOneMon:
	.string "Oh{SE_M_SING}Bu{SE_M_SPIT_UP}yo{SE_M_DIVE}hav{SE_M_REVERSAL}jus{SE_M_SPIT_UP}one\n"
	.string "POKéMON.\p"
	.string "Com{SE_M_REVERSAL}bac{SE_M_ENCORE2}anothe{SE_M_SAND_TOMB}time.$"

Route34_DayCare_Text_TakeYourMonBack:
	.string "Wil{SE_M_BATON_PASS}yo{SE_M_DIVE}tak{SE_M_REVERSAL}you{SE_M_SAND_TOMB}POKéMO{SE_M_PSYBEAM2}back?$"

Route34_DayCare_Text_WhatWillYouBattleWith:
	.string "I{SE_M_ACID_ARMOR}yo{SE_M_DIVE}leav{SE_M_REVERSAL}m{SE_M_REVERSAL}tha{SE_M_SPIT_UP}POKéMON,\n"
	.string "wha{SE_M_SPIT_UP}wil{SE_M_BATON_PASS}yo{SE_M_DIVE}battl{SE_M_REVERSAL}with?\p"
	.string "Com{SE_M_REVERSAL}bac{SE_M_ENCORE2}anothe{SE_M_SAND_TOMB}time.$"

Route34_DayCare_Text_YoullBeLeftWithJustOne:
	.string "Huh?\n"
	.string "Now{SE_M_SUPERSONIC}now.\p"
	.string "I{SE_M_ACID_ARMOR}yo{SE_M_DIVE}leav{SE_M_REVERSAL}tha{SE_M_SPIT_UP}POKéMO{SE_M_PSYBEAM2}with\n"
	.string "me{SE_M_SUPERSONIC}you'l{SE_M_BATON_PASS}b{SE_M_REVERSAL}lef{SE_M_SPIT_UP}wit{SE_M_TRI_ATTACK}jus{SE_M_SPIT_UP}one.\p"
	.string "Yo{SE_M_DIVE}wil{SE_M_BATON_PASS}b{SE_M_REVERSAL}bette{SE_M_SAND_TOMB}of{SE_M_ACID_ARMOR}i{SE_M_ACID_ARMOR}yo{SE_M_DIVE}catch\n"
	.string "som{SE_M_REVERSAL}more{SE_M_SUPERSONIC}{SE_M_HEAL_BELL}dar{SE_M_REVERSAL}say.$"

