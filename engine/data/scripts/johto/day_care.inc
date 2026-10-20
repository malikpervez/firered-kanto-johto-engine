@ Johto (data/scripts/day_care.inc), as built into the FireRed game.

J_Route117_EventScript_DaycareMan::
	lock
	faceplayer
	special GetDaycareMonNicknames
	specialvar 32781, GetDaycareState
	goto_if_eq 32781, 1, J_Route117_EventScript_DaycareEggWaiting
	goto_if_eq 32781, 2, J_Route117_EventScript_CheckOnOneMon
	goto_if_eq 32781, 3, J_Route117_EventScript_CheckOnTwoMons
	msgbox J_Route117_Text_SeeWifeIfYoudLikeMeToRaiseMon, MSGBOX_DEFAULT
	release
	end

J_Route117_EventScript_DaycareEggWaiting::
	msgbox J_Route117_Text_DoYouWantEgg, MSGBOX_YESNO
	goto_if_eq 32781, YES, J_Route117_EventScript_DaycareAcceptEgg
	msgbox J_Route117_Text_IWillKeepDoYouWantIt, MSGBOX_YESNO
	goto_if_eq 32781, YES, J_Route117_EventScript_DaycareAcceptEgg
	msgbox J_Route117_Text_IllKeepIt, MSGBOX_DEFAULT
	clearflag 8806
	special RejectEggFromDayCare
	release
	end

J_Route117_EventScript_DaycareAcceptEgg::
	specialvar 32781, CalculatePlayerPartyCount
	goto_if_ne 32781, 6, J_Route117_EventScript_DaycareReceiveEgg
	msgbox J_Route117_Text_YouHaveNoRoomForIt, MSGBOX_DEFAULT
	release
	end

J_Route117_EventScript_DaycareReceiveEgg::
	message J_Route117_Text_ReceivedEgg
	playfanfare 367
	waitfanfare
	waitbuttonpress
	msgbox J_Route117_Text_TakeGoodCareOfIt, MSGBOX_DEFAULT
	special GiveEggFromDaycare
	clearflag 8806
	release
	end

J_Route117_EventScript_CheckMonReceivedMail::
	specialvar 32781, CheckDaycareMonReceivedMail
	call_if_eq 32781, 1, J_Route117_EventScript_MonReceivedMail
	return

J_Route117_EventScript_MonReceivedMail::
	msgbox J_Route117_Text_FriendlyWithOtherTrainersMon, MSGBOX_DEFAULT
	return

J_Route117_EventScript_CheckOnOneMon::
	special GetDaycareMonNicknames
	msgbox J_Route117_Text_YourMonIsDoingFine, MSGBOX_DEFAULT
	setvar 32772, 0
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
	setvar 32772, 0
	call J_Route117_EventScript_CheckMonReceivedMail
	setvar 32772, 1
	call J_Route117_EventScript_CheckMonReceivedMail
	release
	end

J_Route117_PokemonDayCare_EventScript_DaycareWoman::
	lock
	faceplayer
	specialvar 32781, GetDaycareState
	goto_if_eq 32781, 1, J_Route117_PokemonDayCare_EventScript_EggWaiting
	goto_if_eq 32781, 2, J_Route117_PokemonDayCare_EventScript_OneMonInDaycare
	goto_if_eq 32781, 3, J_Route117_PokemonDayCare_EventScript_TwoMonsInDaycare
	msgbox J_Route117_PokemonDayCare_Text_WouldYouLikeUsToRaiseAMon, MSGBOX_YESNO
	goto_if_eq 32781, YES, J_Route117_PokemonDayCare_EventScript_GiveMonToRaise
	msgbox J_Route117_PokemonDayCare_Text_FineThenComeAgain, MSGBOX_DEFAULT
	release
	end

J_Route117_PokemonDayCare_EventScript_GiveMonToRaise::
	specialvar 32781, CountPartyNonEggMons
	goto_if_eq 32781, 1, J_Route117_PokemonDayCare_EventScript_OnlyOneMon
	specialvar 32781, CountPartyAliveNonEggMons
	goto_if_eq 32781, 2, J_Route117_PokemonDayCare_EventScript_OnlyTwoAliveMons
	msgbox J_Route117_PokemonDayCare_Text_WhichMonShouldWeRaise, MSGBOX_DEFAULT
	chooseboxmon SELECT_PC_MON_DAYCARE
	waitstate
	goto_if_eq 32772, 0xFF, J_Route117_PokemonDayCare_EventScript_ComeAgain
	specialvar 32781, CountPartyAliveNonEggMons_IgnoreVar0x8004Slot
	goto_if_eq 32781, 0, J_Route117_PokemonDayCare_EventScript_OnlyOneAliveMon
	specialvar 32773, GetSelectedMonNicknameAndSpecies
	waitse
	playmoncry 32773, 0
	msgbox J_Route117_PokemonDayCare_Text_WellRaiseYourMon, MSGBOX_DEFAULT
	waitmoncry
	special StoreSelectedPokemonInDaycare
	callnative UpdateFollowingPokemon
	incrementgamestat 47
	specialvar 32781, GetDaycareState
	goto_if_eq 32781, 2, J_Route117_PokemonDayCare_EventScript_CanRaiseOneMore
	release
	end

J_Route117_PokemonDayCare_EventScript_ComeAgain::
	msgbox J_Route117_PokemonDayCare_Text_ComeAgain, MSGBOX_DEFAULT
	release
	end

J_Route117_PokemonDayCare_EventScript_CanRaiseOneMore::
	msgbox J_Route117_PokemonDayCare_Text_WeCanRaiseOneMore, MSGBOX_YESNO
	goto_if_eq 32781, YES, J_Route117_PokemonDayCare_EventScript_GiveMonToRaise
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
	specialvar 32781, GetNumLevelsGainedFromDaycare
	call_if_ne 32781, 0, J_Route117_PokemonDayCare_EventScript_YourMonHasGrownXLevels
	return

J_Route117_PokemonDayCare_EventScript_OneMonInDaycare::
	msgbox J_Route117_PokemonDayCare_Text_GoodToSeeYou, MSGBOX_DEFAULT
	setvar 32772, 0
	call J_Route117_PokemonDayCare_EventScript_DisplayLevelsGained
	msgbox J_Route117_PokemonDayCare_Text_WeCanRaiseOneMore, MSGBOX_YESNO
	goto_if_eq 32781, YES, J_Route117_PokemonDayCare_EventScript_GiveMonToRaise
	msgbox J_Route117_PokemonDayCare_Text_TakeYourMonBack, MSGBOX_YESNO
	goto_if_eq 32781, YES, J_Route117_PokemonDayCare_EventScript_TryRetrieveMon
	goto J_Route117_PokemonDayCare_EventScript_ComeAgain
	end

J_Route117_PokemonDayCare_EventScript_TryRetrieveMon::
	specialvar 32781, CalculatePlayerPartyCount
	goto_if_eq 32781, 6, J_Route117_PokemonDayCare_EventScript_NoRoom
	specialvar 32781, GetDaycareState
	setvar 32772, 0
	goto_if_eq 32781, 2, J_Route117_PokemonDayCare_EventScript_CostPrompt
	special ShowDaycareLevelMenu
	waitstate
	copyvar 32772, 32781
	goto_if_eq 32781, 2, J_Route117_PokemonDayCare_EventScript_ComeAgain
	goto J_Route117_PokemonDayCare_EventScript_CostPrompt
	end

J_Route117_PokemonDayCare_EventScript_CostPrompt::
	special GetDaycareCost
	msgbox J_Route117_PokemonDayCare_Text_ItWillCostX, MSGBOX_YESNO
	goto_if_eq 32781, YES, J_Route117_PokemonDayCare_EventScript_CheckEnoughMoney
	goto J_Route117_PokemonDayCare_EventScript_ComeAgain
	end

J_Route117_PokemonDayCare_EventScript_CheckEnoughMoney::
	specialvar 32781, IsEnoughForCostInVar0x8005
	goto_if_eq 32781, 1, J_Route117_PokemonDayCare_EventScript_RetrieveMon
	msgbox J_Route117_PokemonDayCare_Text_NotEnoughMoney, MSGBOX_DEFAULT
	release
	end

J_Route117_PokemonDayCare_EventScript_RetrieveMon::
	applymovement 1, J_Route117_PokemonDayCare_Movement_RetrieveDaycareMon
	waitmovement 0
	specialvar 32781, TakePokemonFromDaycare
	special SubtractMoneyFromVar0x8005
	playse 95
	msgbox J_Route117_PokemonDayCare_Text_HeresYourMon, MSGBOX_DEFAULT
	waitse
	playmoncry 32781, 0
	msgbox J_Route117_PokemonDayCare_Text_TookBackMon, MSGBOX_DEFAULT
	waitmoncry
	specialvar 32781, GetDaycareState
	goto_if_eq 32781, 2, J_Route117_PokemonDayCare_EventScript_AskRetrieveOtherMon
	goto J_Route117_PokemonDayCare_EventScript_ComeAgain
	end

J_Route117_PokemonDayCare_EventScript_AskRetrieveOtherMon::
	msgbox J_Route117_PokemonDayCare_Text_TakeOtherOneBackToo, MSGBOX_YESNO
	goto_if_eq 32781, YES, J_Route117_PokemonDayCare_EventScript_TryRetrieveMon
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
	setvar 32772, 0
	call J_Route117_PokemonDayCare_EventScript_DisplayLevelsGained
	setvar 32772, 1
	call J_Route117_PokemonDayCare_EventScript_DisplayLevelsGained
	msgbox J_Route117_PokemonDayCare_Text_TakeYourMonBack, MSGBOX_YESNO
	goto_if_eq 32781, YES, J_Route117_PokemonDayCare_EventScript_TryRetrieveMon
	msgbox J_Route117_PokemonDayCare_Text_ComeAgain, MSGBOX_DEFAULT
	release
	end

J_Route117_PokemonDayCare_EventScript_UnusedRetrieveMon::
	special ShowDaycareLevelMenu
	waitstate
	goto_if_eq 32781, 2, J_Route117_PokemonDayCare_EventScript_ComeAgain
	copyvar 32772, 32781
	specialvar 32781, TakePokemonFromDaycare
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
	.string "I'{SE_M_MILK_DRINK}th{SE_M_REVERSAL}DAY-CAR{SE_M_SWORDS_DANCE}MAN.\p"
	.string "{SE_M_HEAL_BELL}hel{SE_M_MORNING_SUN}tak{SE_M_REVERSAL}car{SE_M_REVERSAL}o{SE_M_ACID_ARMOR}th{SE_M_REVERSAL}precious\n"
	.string "POKéMO{SE_M_PSYBEAM2}o{SE_M_ACID_ARMOR}TRAINERS.\p"
	.string "I{SE_M_ACID_ARMOR}you'{SE_M_WATERFALL}lik{SE_M_REVERSAL}m{SE_M_REVERSAL}t{SE_M_ATTRACT2}rais{SE_M_REVERSAL}you{SE_M_SAND_TOMB}POKéMON,\n"
	.string "hav{SE_M_REVERSAL}{SE_M_CHARGE}wor{SE_M_WATERFALL}wit{SE_M_TRI_ATTACK}m{SE_M_YAWN}wife.$"

J_Route117_Text_DoYouWantEgg:
	.string "Ah{SE_M_SUPERSONIC}it'{SE_M_GRASSWHISTLE}you!\p"
	.string "W{SE_M_REVERSAL}wer{SE_M_REVERSAL}raisin{SE_M_SANDSTORM}you{SE_M_SAND_TOMB}POKéMON,\n"
	.string "an{SE_M_WATERFALL}m{SE_M_YAWN}goodness{SE_M_SUPERSONIC}wer{SE_M_REVERSAL}w{SE_M_REVERSAL}surprised!\p"
	.string "You{SE_M_SAND_TOMB}POKéMO{SE_M_PSYBEAM2}ha{SE_M_WATERFALL}a{SE_M_ATTRACT}EGG!\p"
	.string "W{SE_M_REVERSAL}don'{SE_M_SPIT_UP}kno{SE_M_TWISTER}ho{SE_M_TWISTER}i{SE_M_SPIT_UP}go{SE_M_SPIT_UP}there,\n"
	.string "bu{SE_M_SPIT_UP}you{SE_M_SAND_TOMB}POKéMO{SE_M_PSYBEAM2}ha{SE_M_WATERFALL}it.\p"
	.string "Yo{SE_M_DIVE}d{SE_M_ATTRACT2}wan{SE_M_SPIT_UP}it{SE_M_SUPERSONIC}yes?$"

J_Route117_Text_YourMonIsDoingFine:
	.string "Ah{SE_M_SUPERSONIC}it'{SE_M_GRASSWHISTLE}you{SE_M_DRAGON_RAGE}Goo{SE_M_WATERFALL}t{SE_M_ATTRACT2}se{SE_M_REVERSAL}you.\n"
	.string "You{SE_M_SAND_TOMB}{STR_VAR_1}'{SE_M_GRASSWHISTLE}doin{SE_M_SANDSTORM}fine.$"

J_Route117_Text_IllKeepIt:
	.string "Wel{SE_M_BATON_PASS}then{SE_M_SUPERSONIC}I'l{SE_M_BATON_PASS}kee{SE_M_MORNING_SUN}it.\n"
	.string "Thanks!$"

J_Route117_Text_YouHaveNoRoomForIt:
	.string "Yo{SE_M_DIVE}hav{SE_M_REVERSAL}n{SE_M_ATTRACT2}roo{SE_M_MILK_DRINK}fo{SE_M_SAND_TOMB}it…\n"
	.string "Com{SE_M_REVERSAL}bac{SE_M_ENCORE2}whe{SE_M_ATTRACT}you'v{SE_M_REVERSAL}mad{SE_M_REVERSAL}room.$"

J_Route117_Text_ReceivedEgg:
	.string "{PLAYER} receive{SE_M_WATERFALL}th{SE_M_REVERSAL}EG{SE_M_SWAGGER}from\n"
	.string "th{SE_M_REVERSAL}DAY-CAR{SE_M_SWORDS_DANCE}MAN.$"

J_Route117_Text_TakeGoodCareOfIt:
	.string "Tak{SE_M_REVERSAL}goo{SE_M_WATERFALL}car{SE_M_REVERSAL}o{SE_M_ACID_ARMOR}it.$"

J_Route117_Text_FriendlyWithOtherTrainersMon:
	.string "B{SE_M_YAWN}th{SE_M_REVERSAL}way{SE_M_SUPERSONIC}abou{SE_M_SPIT_UP}you{SE_M_SAND_TOMB}{STR_VAR_1},\n"
	.string "i{SE_M_SPIT_UP}seeme{SE_M_WATERFALL}t{SE_M_ATTRACT2}b{SE_M_REVERSAL}friendl{SE_M_YAWN}with\l"
	.string "{STR_VAR_2}'{SE_M_GRASSWHISTLE}{STR_VAR_3}.\p"
	.string "{SE_M_HEAL_BELL}ma{SE_M_YAWN}eve{SE_M_ATTRACT}hav{SE_M_REVERSAL}see{SE_M_ATTRACT}i{SE_M_SPIT_UP}receiving\n"
	.string "{SE_M_CHARGE}piec{SE_M_REVERSAL}o{SE_M_ACID_ARMOR}MAIL.$"

J_Route117_Text_SeeWifeIfYouWantToPickUpMon:
	.string "I{SE_M_ACID_ARMOR}yo{SE_M_DIVE}wan{SE_M_SPIT_UP}t{SE_M_ATTRACT2}pic{SE_M_ENCORE2}u{SE_M_MORNING_SUN}you{SE_M_SAND_TOMB}POKéMON,\n"
	.string "hav{SE_M_REVERSAL}{SE_M_CHARGE}wor{SE_M_WATERFALL}wit{SE_M_TRI_ATTACK}m{SE_M_YAWN}wife.$"

J_Route117_Text_YourMonsAreDoingFine:
	.string "Ah{SE_M_SUPERSONIC}it'{SE_M_GRASSWHISTLE}you{SE_M_DRAGON_RAGE}You{SE_M_SAND_TOMB}{STR_VAR_1} and\n"
	.string "{STR_VAR_2} ar{SE_M_REVERSAL}doin{SE_M_SANDSTORM}fine.$"

J_Route117_Text_IWillKeepDoYouWantIt:
	.string "{SE_M_HEAL_BELL}reall{SE_M_YAWN}wil{SE_M_BATON_PASS}kee{SE_M_MORNING_SUN}it.\n"
	.string "Yo{SE_M_DIVE}d{SE_M_ATTRACT2}wan{SE_M_SPIT_UP}this{SE_M_SUPERSONIC}yes?$"

J_Route117_PokemonDayCare_Text_WouldYouLikeUsToRaiseAMon:
	.string "I'{SE_M_MILK_DRINK}th{SE_M_REVERSAL}DAY-CAR{SE_M_SWORDS_DANCE}LADY.\p"
	.string "W{SE_M_REVERSAL}ca{SE_M_ATTRACT}rais{SE_M_REVERSAL}POKéMO{SE_M_PSYBEAM2}fo{SE_M_SAND_TOMB}you.\p"
	.string "Woul{SE_M_WATERFALL}yo{SE_M_DIVE}lik{SE_M_REVERSAL}u{SE_M_GRASSWHISTLE}t{SE_M_ATTRACT2}rais{SE_M_REVERSAL}one?$"

J_Route117_PokemonDayCare_Text_WhichMonShouldWeRaise:
	.string "Whic{SE_M_TRI_ATTACK}POKéMO{SE_M_PSYBEAM2}shoul{SE_M_WATERFALL}w{SE_M_REVERSAL}rais{SE_M_REVERSAL}for\n"
	.string "you?$"

J_Route117_PokemonDayCare_Text_WellRaiseYourMon:
	.string "Fine{SE_M_SUPERSONIC}we'l{SE_M_BATON_PASS}rais{SE_M_REVERSAL}you{SE_M_SAND_TOMB}{STR_VAR_1}\n"
	.string "fo{SE_M_SAND_TOMB}{SE_M_CHARGE}while.\p"
	.string "Com{SE_M_REVERSAL}bac{SE_M_ENCORE2}fo{SE_M_SAND_TOMB}i{SE_M_SPIT_UP}later.$"

J_Route117_PokemonDayCare_Text_WeCanRaiseOneMore:
	.string "W{SE_M_REVERSAL}ca{SE_M_ATTRACT}rais{SE_M_REVERSAL}tw{SE_M_ATTRACT2}o{SE_M_ACID_ARMOR}you{SE_M_SAND_TOMB}POKéMON.\n"
	.string "Woul{SE_M_WATERFALL}yo{SE_M_DIVE}lik{SE_M_REVERSAL}u{SE_M_GRASSWHISTLE}t{SE_M_ATTRACT2}rais{SE_M_REVERSAL}on{SE_M_REVERSAL}more?$"

J_Route117_PokemonDayCare_Text_HusbandWasLookingForYou:
	.string "M{SE_M_YAWN}husban{SE_M_WATERFALL}wa{SE_M_GRASSWHISTLE}lookin{SE_M_SANDSTORM}fo{SE_M_SAND_TOMB}you.$"

J_Route117_PokemonDayCare_Text_FineThenComeAgain:
	.string "Oh{SE_M_SUPERSONIC}fine{SE_M_SUPERSONIC}then.\n"
	.string "Com{SE_M_REVERSAL}again.$"

J_Route117_PokemonDayCare_Text_NotEnoughMoney:
	.string "Yo{SE_M_DIVE}don'{SE_M_SPIT_UP}hav{SE_M_REVERSAL}enoug{SE_M_TRI_ATTACK}money…$"

J_Route117_PokemonDayCare_Text_TakeOtherOneBackToo:
	.string "Wil{SE_M_BATON_PASS}yo{SE_M_DIVE}tak{SE_M_REVERSAL}bac{SE_M_ENCORE2}th{SE_M_REVERSAL}othe{SE_M_SAND_TOMB}one,\n"
	.string "too?$"

J_Route117_PokemonDayCare_Text_ComeAgain:
	.string "Fine.\n"
	.string "Com{SE_M_REVERSAL}again.$"

J_Route117_PokemonDayCare_Text_GoodToSeeYou:
	.string "Ah{SE_M_SUPERSONIC}it'{SE_M_GRASSWHISTLE}you{SE_M_DRAGON_RAGE}Goo{SE_M_WATERFALL}t{SE_M_ATTRACT2}se{SE_M_REVERSAL}you.\n"
	.string "You{SE_M_SAND_TOMB}POKéMO{SE_M_PSYBEAM2}ca{SE_M_ATTRACT}onl{SE_M_YAWN}b{SE_M_REVERSAL}doin{SE_M_SANDSTORM}good!$"

J_Route117_PokemonDayCare_Text_YourMonHasGrownXLevels:
	.string "B{SE_M_YAWN}level{SE_M_SUPERSONIC}you{SE_M_SAND_TOMB}{STR_VAR_1} has\n"
	.string "grow{SE_M_ATTRACT}b{SE_M_YAWN}{STR_VAR_2}.$"

J_Route117_PokemonDayCare_Text_YourTeamIsFull:
	.string "You{SE_M_SAND_TOMB}POKéMO{SE_M_PSYBEAM2}tea{SE_M_MILK_DRINK}i{SE_M_GRASSWHISTLE}full.\n"
	.string "Mak{SE_M_REVERSAL}room{SE_M_SUPERSONIC}the{SE_M_ATTRACT}com{SE_M_REVERSAL}se{SE_M_REVERSAL}me.$"

J_Route117_PokemonDayCare_Text_TakeBackWhichMon:
	.string "Whic{SE_M_TRI_ATTACK}POKéMO{SE_M_PSYBEAM2}wil{SE_M_BATON_PASS}yo{SE_M_DIVE}tak{SE_M_REVERSAL}back?$"

J_Route117_PokemonDayCare_Text_ItWillCostX:
	.string "I{SE_M_ACID_ARMOR}yo{SE_M_DIVE}wan{SE_M_SPIT_UP}you{SE_M_SAND_TOMB}{STR_VAR_1} back,\n"
	.string "i{SE_M_SPIT_UP}wil{SE_M_BATON_PASS}cos{SE_M_SPIT_UP}¥{STR_VAR_2}.$"

J_Route117_PokemonDayCare_Text_HeresYourMon:
	.string "Perfect!\n"
	.string "Here'{SE_M_GRASSWHISTLE}you{SE_M_SAND_TOMB}POKéMON.$"

J_Route117_PokemonDayCare_Text_TookBackMon:
	.string "{PLAYER} too{SE_M_ENCORE2}bac{SE_M_ENCORE2}{STR_VAR_1} from\n"
	.string "th{SE_M_REVERSAL}DAY-CAR{SE_M_SWORDS_DANCE}LADY.$"

J_Route117_PokemonDayCare_Text_YouHaveJustOneMon:
	.string "Oh{SE_M_SING}Bu{SE_M_SPIT_UP}yo{SE_M_DIVE}hav{SE_M_REVERSAL}jus{SE_M_SPIT_UP}one\n"
	.string "POKéMON.\p"
	.string "Com{SE_M_REVERSAL}bac{SE_M_ENCORE2}anothe{SE_M_SAND_TOMB}time.$"

J_Route117_PokemonDayCare_Text_TakeYourMonBack:
	.string "Wil{SE_M_BATON_PASS}yo{SE_M_DIVE}tak{SE_M_REVERSAL}you{SE_M_SAND_TOMB}POKéMO{SE_M_PSYBEAM2}back?$"

J_Route117_PokemonDayCare_Text_WhatWillYouBattleWith:
	.string "I{SE_M_ACID_ARMOR}yo{SE_M_DIVE}leav{SE_M_REVERSAL}m{SE_M_REVERSAL}tha{SE_M_SPIT_UP}POKéMON,\n"
	.string "wha{SE_M_SPIT_UP}wil{SE_M_BATON_PASS}yo{SE_M_DIVE}battl{SE_M_REVERSAL}with?\p"
	.string "Com{SE_M_REVERSAL}bac{SE_M_ENCORE2}anothe{SE_M_SAND_TOMB}time.$"

J_Text_EggHatchHuh:
	.string "Huh?$"

J_Route117_PokemonDayCare_Text_YoullBeLeftWithJustOne:
	.string "Huh?\n"
	.string "Now{SE_M_SUPERSONIC}now.\p"
	.string "I{SE_M_ACID_ARMOR}yo{SE_M_DIVE}leav{SE_M_REVERSAL}tha{SE_M_SPIT_UP}POKéMO{SE_M_PSYBEAM2}with\n"
	.string "me{SE_M_SUPERSONIC}you'l{SE_M_BATON_PASS}b{SE_M_REVERSAL}lef{SE_M_SPIT_UP}wit{SE_M_TRI_ATTACK}jus{SE_M_SPIT_UP}one.\p"
	.string "Yo{SE_M_DIVE}wil{SE_M_BATON_PASS}b{SE_M_REVERSAL}bette{SE_M_SAND_TOMB}of{SE_M_ACID_ARMOR}i{SE_M_ACID_ARMOR}yo{SE_M_DIVE}catch\n"
	.string "som{SE_M_REVERSAL}more{SE_M_SUPERSONIC}{SE_M_HEAL_BELL}dar{SE_M_REVERSAL}say.$"

