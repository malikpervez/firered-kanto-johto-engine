@ Johto (data/scripts/day_care.inc), as built into the FireRed game.

J_Route117_EventScript_DaycareMan::
	lock
	faceplayer
	special GetDaycareMonNicknames
	specialvar VAR_RESULT, GetDaycareState
	goto_if_eq VAR_RESULT, DAYCARE_EGG_WAITING, J_Route117_EventScript_DaycareEggWaiting
	goto_if_eq VAR_RESULT, DAYCARE_ONE_MON, J_Route117_EventScript_CheckOnOneMon
	goto_if_eq VAR_RESULT, DAYCARE_TWO_MONS, J_Route117_EventScript_CheckOnTwoMons
	msgbox J_Route117_Text_SeeWifeIfYoudLikeMeToRaiseMon, MSGBOX_DEFAULT
	release
	end

J_Route117_EventScript_DaycareEggWaiting::
	msgbox J_Route117_Text_DoYouWantEgg, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, J_Route117_EventScript_DaycareAcceptEgg
	msgbox J_Route117_Text_IWillKeepDoYouWantIt, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, J_Route117_EventScript_DaycareAcceptEgg
	msgbox J_Route117_Text_IllKeepIt, MSGBOX_DEFAULT
	clearflag JOHTO_FLAG_PENDING_DAYCARE_EGG
	special RejectEggFromDayCare
	release
	end

J_Route117_EventScript_DaycareAcceptEgg::
	specialvar VAR_RESULT, CalculatePlayerPartyCount
	goto_if_ne VAR_RESULT, PARTY_SIZE, J_Route117_EventScript_DaycareReceiveEgg
	msgbox J_Route117_Text_YouHaveNoRoomForIt, MSGBOX_DEFAULT
	release
	end

J_Route117_EventScript_DaycareReceiveEgg::
	message J_Route117_Text_ReceivedEgg
	playfanfare MUS_LEVEL_UP
	waitfanfare
	waitbuttonpress
	msgbox J_Route117_Text_TakeGoodCareOfIt, MSGBOX_DEFAULT
	special GiveEggFromDaycare
	clearflag JOHTO_FLAG_PENDING_DAYCARE_EGG
	release
	end

J_Route117_EventScript_CheckMonReceivedMail::
	specialvar VAR_RESULT, CheckDaycareMonReceivedMail
	call_if_eq VAR_RESULT, 1, J_Route117_EventScript_MonReceivedMail
	return

J_Route117_EventScript_MonReceivedMail::
	msgbox J_Route117_Text_FriendlyWithOtherTrainersMon, MSGBOX_DEFAULT
	return

J_Route117_EventScript_CheckOnOneMon::
	special GetDaycareMonNicknames
	msgbox J_Route117_Text_YourMonIsDoingFine, MSGBOX_DEFAULT
	setvar VAR_0x8004, 0
	call J_Route117_EventScript_CheckMonReceivedMail
	release
	end

J_Route117_EventScript_CheckOnTwoMons::
	special GetDaycareMonNicknames
	msgbox J_Route117_Text_YourMonsAreDoingFine, MSGBOX_DEFAULT
	special SetDaycareCompatibilityString
	special ShowFieldMessageStringVar4
	waitmessage
	waitbuttonpress
	setvar VAR_0x8004, 0
	call J_Route117_EventScript_CheckMonReceivedMail
	setvar VAR_0x8004, 1
	call J_Route117_EventScript_CheckMonReceivedMail
	release
	end

J_Route117_PokemonDayCare_EventScript_DaycareWoman::
	lock
	faceplayer
	specialvar VAR_RESULT, GetDaycareState
	goto_if_eq VAR_RESULT, DAYCARE_EGG_WAITING, J_Route117_PokemonDayCare_EventScript_EggWaiting
	goto_if_eq VAR_RESULT, DAYCARE_ONE_MON, J_Route117_PokemonDayCare_EventScript_OneMonInDaycare
	goto_if_eq VAR_RESULT, DAYCARE_TWO_MONS, J_Route117_PokemonDayCare_EventScript_TwoMonsInDaycare
	msgbox J_Route117_PokemonDayCare_Text_WouldYouLikeUsToRaiseAMon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, J_Route117_PokemonDayCare_EventScript_GiveMonToRaise
	msgbox J_Route117_PokemonDayCare_Text_FineThenComeAgain, MSGBOX_DEFAULT
	release
	end

J_Route117_PokemonDayCare_EventScript_GiveMonToRaise::
	specialvar VAR_RESULT, CountPartyNonEggMons
	goto_if_eq VAR_RESULT, 1, J_Route117_PokemonDayCare_EventScript_OnlyOneMon
	specialvar VAR_RESULT, CountPartyAliveNonEggMons
	goto_if_eq VAR_RESULT, 2, J_Route117_PokemonDayCare_EventScript_OnlyTwoAliveMons
	msgbox J_Route117_PokemonDayCare_Text_WhichMonShouldWeRaise, MSGBOX_DEFAULT
	chooseboxmon SELECT_PC_MON_DAYCARE
	waitstate
	goto_if_eq VAR_0x8004, PARTY_NOTHING_CHOSEN, J_Route117_PokemonDayCare_EventScript_ComeAgain
	specialvar VAR_RESULT, CountPartyAliveNonEggMons_IgnoreVar0x8004Slot
	goto_if_eq VAR_RESULT, 0, J_Route117_PokemonDayCare_EventScript_OnlyOneAliveMon
	specialvar VAR_0x8005, GetSelectedMonNicknameAndSpecies
	waitse
	playmoncry VAR_0x8005, CRY_MODE_NORMAL
	msgbox J_Route117_PokemonDayCare_Text_WellRaiseYourMon, MSGBOX_DEFAULT
	waitmoncry
	special StoreSelectedPokemonInDaycare
	callnative UpdateFollowingPokemon
	incrementgamestat GAME_STAT_USED_DAYCARE
	specialvar VAR_RESULT, GetDaycareState
	goto_if_eq VAR_RESULT, DAYCARE_ONE_MON, J_Route117_PokemonDayCare_EventScript_CanRaiseOneMore
	release
	end

J_Route117_PokemonDayCare_EventScript_ComeAgain::
	msgbox J_Route117_PokemonDayCare_Text_ComeAgain, MSGBOX_DEFAULT
	release
	end

J_Route117_PokemonDayCare_EventScript_CanRaiseOneMore::
	msgbox J_Route117_PokemonDayCare_Text_WeCanRaiseOneMore, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, J_Route117_PokemonDayCare_EventScript_GiveMonToRaise
	goto J_Route117_PokemonDayCare_EventScript_ComeAgain
	end

J_Route117_PokemonDayCare_EventScript_OnlyOneMon::
	msgbox J_Route117_PokemonDayCare_Text_YouHaveJustOneMon, MSGBOX_DEFAULT
	release
	end

J_Route117_PokemonDayCare_EventScript_OnlyOneAliveMon::
	msgbox J_Route117_PokemonDayCare_Text_WhatWillYouBattleWith, MSGBOX_DEFAULT
	release
	end

J_Route117_PokemonDayCare_EventScript_OnlyTwoAliveMons::
	msgbox J_Route117_PokemonDayCare_Text_YoullBeLeftWithJustOne, MSGBOX_DEFAULT
	release
	end

J_Route117_PokemonDayCare_EventScript_EggWaiting::
	msgbox J_Route117_PokemonDayCare_Text_HusbandWasLookingForYou, MSGBOX_DEFAULT
	release
	end

J_Route117_PokemonDayCare_EventScript_YourMonHasGrownXLevels::
	msgbox J_Route117_PokemonDayCare_Text_YourMonHasGrownXLevels, MSGBOX_DEFAULT
	return

J_Route117_PokemonDayCare_EventScript_DisplayLevelsGained::
	specialvar VAR_RESULT, GetNumLevelsGainedFromDaycare
	call_if_ne VAR_RESULT, 0, J_Route117_PokemonDayCare_EventScript_YourMonHasGrownXLevels
	return

J_Route117_PokemonDayCare_EventScript_OneMonInDaycare::
	msgbox J_Route117_PokemonDayCare_Text_GoodToSeeYou, MSGBOX_DEFAULT
	setvar VAR_0x8004, 0
	call J_Route117_PokemonDayCare_EventScript_DisplayLevelsGained
	msgbox J_Route117_PokemonDayCare_Text_WeCanRaiseOneMore, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, J_Route117_PokemonDayCare_EventScript_GiveMonToRaise
	msgbox J_Route117_PokemonDayCare_Text_TakeYourMonBack, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, J_Route117_PokemonDayCare_EventScript_TryRetrieveMon
	goto J_Route117_PokemonDayCare_EventScript_ComeAgain
	end

J_Route117_PokemonDayCare_EventScript_TryRetrieveMon::
	specialvar VAR_RESULT, CalculatePlayerPartyCount
	goto_if_eq VAR_RESULT, PARTY_SIZE, J_Route117_PokemonDayCare_EventScript_NoRoom
	specialvar VAR_RESULT, GetDaycareState
	setvar VAR_0x8004, 0
	goto_if_eq VAR_RESULT, DAYCARE_ONE_MON, J_Route117_PokemonDayCare_EventScript_CostPrompt
	special ShowDaycareLevelMenu
	waitstate
	copyvar VAR_0x8004, VAR_RESULT
	goto_if_eq VAR_RESULT, DAYCARE_EXITED_LEVEL_MENU, J_Route117_PokemonDayCare_EventScript_ComeAgain
	goto J_Route117_PokemonDayCare_EventScript_CostPrompt
	end

J_Route117_PokemonDayCare_EventScript_CostPrompt::
	special GetDaycareCost
	msgbox J_Route117_PokemonDayCare_Text_ItWillCostX, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, J_Route117_PokemonDayCare_EventScript_CheckEnoughMoney
	goto J_Route117_PokemonDayCare_EventScript_ComeAgain
	end

J_Route117_PokemonDayCare_EventScript_CheckEnoughMoney::
	specialvar VAR_RESULT, IsEnoughForCostInVar0x8005
	goto_if_eq VAR_RESULT, 1, J_Route117_PokemonDayCare_EventScript_RetrieveMon
	msgbox J_Route117_PokemonDayCare_Text_NotEnoughMoney, MSGBOX_DEFAULT
	release
	end

J_Route117_PokemonDayCare_EventScript_RetrieveMon::
	applymovement LOCALID_DAYCARE_LADY, J_Route117_PokemonDayCare_Movement_RetrieveDaycareMon
	waitmovement 0
	specialvar VAR_RESULT, TakePokemonFromDaycare
	special SubtractMoneyFromVar0x8005
	playse SE_SHOP
	msgbox J_Route117_PokemonDayCare_Text_HeresYourMon, MSGBOX_DEFAULT
	waitse
	playmoncry VAR_RESULT, CRY_MODE_NORMAL
	msgbox J_Route117_PokemonDayCare_Text_TookBackMon, MSGBOX_DEFAULT
	waitmoncry
	specialvar VAR_RESULT, GetDaycareState
	goto_if_eq VAR_RESULT, DAYCARE_ONE_MON, J_Route117_PokemonDayCare_EventScript_AskRetrieveOtherMon
	goto J_Route117_PokemonDayCare_EventScript_ComeAgain
	end

J_Route117_PokemonDayCare_EventScript_AskRetrieveOtherMon::
	msgbox J_Route117_PokemonDayCare_Text_TakeOtherOneBackToo, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, J_Route117_PokemonDayCare_EventScript_TryRetrieveMon
	goto J_Route117_PokemonDayCare_EventScript_ComeAgain
	end

J_Route117_PokemonDayCare_EventScript_NoRoom::
	msgbox J_Route117_PokemonDayCare_Text_YourTeamIsFull, MSGBOX_DEFAULT
	release
	end

J_Route117_PokemonDayCare_Movement_RetrieveDaycareMon:
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

J_Route117_PokemonDayCare_EventScript_UnusedEnd::
	end

J_Route117_PokemonDayCare_EventScript_TwoMonsInDaycare::
	msgbox J_Route117_PokemonDayCare_Text_GoodToSeeYou, MSGBOX_DEFAULT
	setvar VAR_0x8004, 0
	call J_Route117_PokemonDayCare_EventScript_DisplayLevelsGained
	setvar VAR_0x8004, 1
	call J_Route117_PokemonDayCare_EventScript_DisplayLevelsGained
	msgbox J_Route117_PokemonDayCare_Text_TakeYourMonBack, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, J_Route117_PokemonDayCare_EventScript_TryRetrieveMon
	msgbox J_Route117_PokemonDayCare_Text_ComeAgain, MSGBOX_DEFAULT
	release
	end

J_Route117_PokemonDayCare_EventScript_UnusedRetrieveMon::
	special ShowDaycareLevelMenu
	waitstate
	goto_if_eq VAR_RESULT, 2, J_Route117_PokemonDayCare_EventScript_ComeAgain
	copyvar VAR_0x8004, VAR_RESULT
	specialvar VAR_RESULT, TakePokemonFromDaycare
	msgbox J_Route117_PokemonDayCare_Text_HeresYourMon, MSGBOX_DEFAULT
	msgbox J_Route117_PokemonDayCare_Text_ComeAgain, MSGBOX_DEFAULT
	release
	end

J_EventScript_EggHatch::
	lockall
	msgbox J_Text_EggHatchHuh, MSGBOX_DEFAULT
	special EggHatch
	waitstate
	releaseall
	end

J_Route117_Text_SeeWifeIfYoudLikeMeToRaiseMon:
	.string "I'm the DAY-CARE MAN.\p"
	.string "I help take care of the precious\n"
	.string "POKéMON of TRAINERS.\p"
	.string "If you'd like me to raise your POKéMON,\n"
	.string "have a word with my wife.$"

J_Route117_Text_DoYouWantEgg:
	.string "Ah, it's you!\p"
	.string "We were raising your POKéMON,\n"
	.string "and my goodness, were we surprised!\p"
	.string "Your POKéMON had an EGG!\p"
	.string "We don't know how it got there,\n"
	.string "but your POKéMON had it.\p"
	.string "You do want it, yes?$"

J_Route117_Text_YourMonIsDoingFine:
	.string "Ah, it's you! Good to see you.\n"
	.string "Your {STR_VAR_1}'s doing fine.$"

J_Route117_Text_IllKeepIt:
	.string "Well then, I'll keep it.\n"
	.string "Thanks!$"

J_Route117_Text_YouHaveNoRoomForIt:
	.string "You have no room for it…\n"
	.string "Come back when you've made room.$"

J_Route117_Text_ReceivedEgg:
	.string "{PLAYER} received the EGG from\n"
	.string "the DAY-CARE MAN.$"

J_Route117_Text_TakeGoodCareOfIt:
	.string "Take good care of it.$"

J_Route117_Text_FriendlyWithOtherTrainersMon:
	.string "By the way, about your {STR_VAR_1},\n"
	.string "it seemed to be friendly with\l"
	.string "{STR_VAR_2}'s {STR_VAR_3}.\p"
	.string "I may even have seen it receiving\n"
	.string "a piece of MAIL.$"

J_Route117_Text_SeeWifeIfYouWantToPickUpMon:
	.string "If you want to pick up your POKéMON,\n"
	.string "have a word with my wife.$"

J_Route117_Text_YourMonsAreDoingFine:
	.string "Ah, it's you! Your {STR_VAR_1} and\n"
	.string "{STR_VAR_2} are doing fine.$"

J_Route117_Text_IWillKeepDoYouWantIt:
	.string "I really will keep it.\n"
	.string "You do want this, yes?$"

J_Route117_PokemonDayCare_Text_WouldYouLikeUsToRaiseAMon:
	.string "I'm the DAY-CARE LADY.\p"
	.string "We can raise POKéMON for you.\p"
	.string "Would you like us to raise one?$"

J_Route117_PokemonDayCare_Text_WhichMonShouldWeRaise:
	.string "Which POKéMON should we raise for\n"
	.string "you?$"

J_Route117_PokemonDayCare_Text_WellRaiseYourMon:
	.string "Fine, we'll raise your {STR_VAR_1}\n"
	.string "for a while.\p"
	.string "Come back for it later.$"

J_Route117_PokemonDayCare_Text_WeCanRaiseOneMore:
	.string "We can raise two of your POKéMON.\n"
	.string "Would you like us to raise one more?$"

J_Route117_PokemonDayCare_Text_HusbandWasLookingForYou:
	.string "My husband was looking for you.$"

J_Route117_PokemonDayCare_Text_FineThenComeAgain:
	.string "Oh, fine, then.\n"
	.string "Come again.$"

J_Route117_PokemonDayCare_Text_NotEnoughMoney:
	.string "You don't have enough money…$"

J_Route117_PokemonDayCare_Text_TakeOtherOneBackToo:
	.string "Will you take back the other one,\n"
	.string "too?$"

J_Route117_PokemonDayCare_Text_ComeAgain:
	.string "Fine.\n"
	.string "Come again.$"

J_Route117_PokemonDayCare_Text_GoodToSeeYou:
	.string "Ah, it's you! Good to see you.\n"
	.string "Your POKéMON can only be doing good!$"

J_Route117_PokemonDayCare_Text_YourMonHasGrownXLevels:
	.string "By level, your {STR_VAR_1} has\n"
	.string "grown by {STR_VAR_2}.$"

J_Route117_PokemonDayCare_Text_YourTeamIsFull:
	.string "Your POKéMON team is full.\n"
	.string "Make room, then come see me.$"

J_Route117_PokemonDayCare_Text_TakeBackWhichMon:
	.string "Which POKéMON will you take back?$"

J_Route117_PokemonDayCare_Text_ItWillCostX:
	.string "If you want your {STR_VAR_1} back,\n"
	.string "it will cost ¥{STR_VAR_2}.$"

J_Route117_PokemonDayCare_Text_HeresYourMon:
	.string "Perfect!\n"
	.string "Here's your POKéMON.$"

J_Route117_PokemonDayCare_Text_TookBackMon:
	.string "{PLAYER} took back {STR_VAR_1} from\n"
	.string "the DAY-CARE LADY.$"

J_Route117_PokemonDayCare_Text_YouHaveJustOneMon:
	.string "Oh? But you have just one\n"
	.string "POKéMON.\p"
	.string "Come back another time.$"

J_Route117_PokemonDayCare_Text_TakeYourMonBack:
	.string "Will you take your POKéMON back?$"

J_Route117_PokemonDayCare_Text_WhatWillYouBattleWith:
	.string "If you leave me that POKéMON,\n"
	.string "what will you battle with?\p"
	.string "Come back another time.$"

J_Text_EggHatchHuh:
	.string "Huh?$"

J_Route117_PokemonDayCare_Text_YoullBeLeftWithJustOne:
	.string "Huh?\n"
	.string "Now, now.\p"
	.string "If you leave that POKéMON with\n"
	.string "me, you'll be left with just one.\p"
	.string "You will be better off if you catch\n"
	.string "some more, I dare say.$"

