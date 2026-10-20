@ Johto (data/maps/GoldenrodCity_House1_hns/scripts.inc), as built into the FireRed game.

GoldenrodCity_House1_hns_MapScripts::
	.byte 0

GoldenrodCity_NameRatersHouse_EventScript_ToggleShinies::
	lock
	msgbox GoldenrodCity_NameRatersHouse_Text_AskToggleShinies, MSGBOX_YESNO
	goto_if_eq 32781, FALSE, GoldenrodCity_NameRatersHouse_EventScript_ToggleShiniesRefused

	msgbox GoldenrodCity_NameRatersHouse_Text_ToggleShinies, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_NameRatersHouse_EventScript_ToggleShiniesRefused::
	release
	end

GoldenrodCity_NameRatersHouse_Text_AskToggleShinies:
	.string "Woul{SE_M_WATERFALL}yo{SE_M_DIVE}lik{SE_M_REVERSAL}t{SE_M_ATTRACT2}toggl{SE_M_REVERSAL}th{SE_M_REVERSAL}Unique\n"
	.string "Shin{SE_M_YAWN}Color{SE_M_GRASSWHISTLE}setting?$"

GoldenrodCity_NameRatersHouse_Text_ToggleShinies:
	.string "Shin{SE_M_YAWN}Color{SE_M_GRASSWHISTLE}Toggled!\p"
	.string "Vie{SE_M_TWISTER}you{SE_M_SAND_TOMB}settin{SE_M_SANDSTORM}a{SE_M_SPIT_UP}th{SE_M_REVERSAL}CHALLENGE\n"
	.string "VIEWE{SE_M_MINIMIZE}a{SE_M_SPIT_UP}an{SE_M_YAWN}PC.$"

GoldenrodCity_NameRatersHouse_EventScript_RenameRival::
	msgbox GoldenrodCity_NameRatersHouse_Text_RenameRival, MSGBOX_DEFAULT
	closemessage
	special NameRival
	waitstate
	end

GoldenrodCity_NameRatersHouse_Text_RenameRival:
	.string "It'{SE_M_GRASSWHISTLE}th{SE_M_REVERSAL}news...\p"
	.string "Th{SE_M_REVERSAL}POLIC{SE_M_SWORDS_DANCE}ar{SE_M_REVERSAL}lookin{SE_M_SANDSTORM}fo{SE_M_SAND_TOMB}this\n"
	.string "REDHEADE{SE_M_FAINT_ATTACK}BOY!\p"
	.string "D{SE_M_ATTRACT2}YO{SE_M_REFLECT}kno{SE_M_TWISTER}hi{SE_M_GRASSWHISTLE}name?$"

GoldenrodCity_NameRatersHouse_EventScript_NameRater::
	lock
	faceplayer
	msgbox GoldenrodCity_NameRatersHouse_Text_PleasedToRateMonNickname, MSGBOX_YESNO
	goto_if_eq 32781, YES, GoldenrodCity_NameRatersHouse_EventScript_ChooseMonToRate
	goto_if_eq 32781, NO, GoldenrodCity_NameRatersHouse_EventScript_DeclineNameRate
	end

GoldenrodCity_NameRatersHouse_EventScript_ChooseMonToRate::
	msgbox GoldenrodCity_NameRatersHouse_Text_CritiqueWhichMonNickname, MSGBOX_DEFAULT
	special ChoosePartyMon
	waitstate
	lock
	goto_if_ne 32772, 0xFF, GoldenrodCity_NameRatersHouse_EventScript_RateMonNickname
	goto_if_eq 32772, 0xFF, GoldenrodCity_NameRatersHouse_EventScript_DeclineNameRate
	end

GoldenrodCity_NameRatersHouse_EventScript_DeclineNameRate::
	msgbox GoldenrodCity_NameRatersHouse_Text_DoVisitAgain, MSGBOX_DEFAULT
	release
	end

GoldenrodCity_NameRatersHouse_EventScript_RateMonNickname::
	specialvar 32781, ScriptGetPartyMonSpecies
	goto_if_eq 32781, (1572 + 1), GoldenrodCity_NameRatersHouse_EventScript_CantRateEgg
	special BufferMonNickname



	special BufferMonNickname

	msgbox GoldenrodCity_NameRatersHouse_Text_FineNameSuggestBetterOne, MSGBOX_YESNO
	goto_if_eq 32781, YES, GoldenrodCity_NameRatersHouse_EventScript_ChangeNickname
	goto_if_eq 32781, NO, GoldenrodCity_NameRatersHouse_EventScript_DeclineNameRate
	end

GoldenrodCity_NameRatersHouse_EventScript_CantRateEgg::
	msgbox GoldenrodCity_NameRatersHouse_Text_ThatIsMerelyAnEgg, MSGBOX_DEFAULT
	release
	end

GoldenrodCity_NameRatersHouse_EventScript_PlayerNotMonsOT::
	msgbox GoldenrodCity_NameRatersHouse_Text_MagnificentName, MSGBOX_DEFAULT
	release
	end

GoldenrodCity_NameRatersHouse_EventScript_ChangeNickname::
	msgbox GoldenrodCity_NameRatersHouse_Text_WhatShallNewNameBe, MSGBOX_DEFAULT
	call J_Common_EventScript_NameReceivedPartyMon
	specialvar 32781, TryPutNameRaterShowOnTheAir
	special BufferMonNickname
	goto_if_eq 32781, TRUE, GoldenrodCity_NameRatersHouse_EventScript_NewNameDifferent
	msgbox GoldenrodCity_NameRatersHouse_Text_NameNoDifferentYetSuperior, MSGBOX_DEFAULT
	release
	end

GoldenrodCity_NameRatersHouse_EventScript_NewNameDifferent::
	msgbox GoldenrodCity_NameRatersHouse_Text_MonShallBeKnownAsName, MSGBOX_DEFAULT
	release
	end

GoldenrodCity_NameRatersHouse_Text_PleasedToRateMonNickname:
	.string "Hi{SE_M_SUPERSONIC}hi{SE_M_DRAGON_RAGE}I'{SE_M_MILK_DRINK}th{SE_M_REVERSAL}NAM{SE_M_SWORDS_DANCE}RATER!\n"
	.string "I'{SE_M_MILK_DRINK}th{SE_M_REVERSAL}fortune-telle{SE_M_SAND_TOMB}o{SE_M_ACID_ARMOR}names!\p"
	.string "{SE_M_HEAL_BELL}shal{SE_M_BATON_PASS}b{SE_M_REVERSAL}please{SE_M_WATERFALL}t{SE_M_ATTRACT2}rat{SE_M_REVERSAL}your\n"
	.string "POKéMON'{SE_M_GRASSWHISTLE}nickname.$"

GoldenrodCity_NameRatersHouse_Text_CritiqueWhichMonNickname:
	.string "Whic{SE_M_TRI_ATTACK}POKéMON'{SE_M_GRASSWHISTLE}nicknam{SE_M_REVERSAL}should\n"
	.string "{SE_M_HEAL_BELL}critique?$"

GoldenrodCity_NameRatersHouse_Text_FineNameSuggestBetterOne:
	.string "Hmmm{SE_M_DIZZY_PUNCH}{STR_VAR_1}{SE_M_SUPERSONIC}i{SE_M_GRASSWHISTLE}it{SE_M_SING}Tha{SE_M_SPIT_UP}is\n"
	.string "quit{SE_M_REVERSAL}{SE_M_CHARGE}fin{SE_M_REVERSAL}nam{SE_M_REVERSAL}yo{SE_M_DIVE}bestowed.\p"
	.string "But{SE_M_DRAGON_RAGE}Wha{SE_M_SPIT_UP}sa{SE_M_YAWN}you{SE_M_SUPERSONIC}i{SE_M_ACID_ARMOR}{SE_M_HEAL_BELL}wer{SE_M_REVERSAL}to\n"
	.string "sugges{SE_M_SPIT_UP}{SE_M_CHARGE}slightl{SE_M_YAWN}bette{SE_M_SAND_TOMB}name?$"

GoldenrodCity_NameRatersHouse_Text_WhatShallNewNameBe:
	.string "Ah{SE_M_SUPERSONIC}good{SE_M_PERISH_SONG}Then{SE_M_SUPERSONIC}wha{SE_M_SPIT_UP}shal{SE_M_BATON_PASS}th{SE_M_REVERSAL}new\n"
	.string "nicknam{SE_M_REVERSAL}be?$"

GoldenrodCity_NameRatersHouse_Text_MonShallBeKnownAsName:
	.string "Done{SE_M_DRAGON_RAGE}Fro{SE_M_MILK_DRINK}no{SE_M_TWISTER}on{SE_M_SUPERSONIC}thi{SE_M_GRASSWHISTLE}POKéMON\n"
	.string "shal{SE_M_BATON_PASS}b{SE_M_REVERSAL}know{SE_M_ATTRACT}a{SE_M_GRASSWHISTLE}{STR_VAR_1}!\p"
	.string "I{SE_M_SPIT_UP}i{SE_M_GRASSWHISTLE}{SE_M_CHARGE}bette{SE_M_SAND_TOMB}nam{SE_M_REVERSAL}tha{SE_M_ATTRACT}before!\n"
	.string "Ho{SE_M_TWISTER}fortunat{SE_M_REVERSAL}fo{SE_M_SAND_TOMB}you!$"

GoldenrodCity_NameRatersHouse_Text_DoVisitAgain:
	.string "{SE_M_HEAL_BELL}see.\n"
	.string "D{SE_M_ATTRACT2}com{SE_M_REVERSAL}visi{SE_M_SPIT_UP}again.$"

GoldenrodCity_NameRatersHouse_Text_NameNoDifferentYetSuperior:
	.string "Done{SE_M_DRAGON_RAGE}Fro{SE_M_MILK_DRINK}no{SE_M_TWISTER}on{SE_M_SUPERSONIC}thi{SE_M_GRASSWHISTLE}POKéMON\n"
	.string "shal{SE_M_BATON_PASS}b{SE_M_REVERSAL}know{SE_M_ATTRACT}a{SE_M_GRASSWHISTLE}{STR_VAR_1}!\p"
	.string "I{SE_M_SPIT_UP}look{SE_M_GRASSWHISTLE}n{SE_M_ATTRACT2}differen{SE_M_SPIT_UP}fro{SE_M_MILK_DRINK}before,\n"
	.string "an{SE_M_WATERFALL}yet{SE_M_SUPERSONIC}thi{SE_M_GRASSWHISTLE}i{SE_M_GRASSWHISTLE}vastl{SE_M_YAWN}superior!\p"
	.string "Ho{SE_M_TWISTER}fortunat{SE_M_REVERSAL}fo{SE_M_SAND_TOMB}you!$"

GoldenrodCity_NameRatersHouse_Text_MagnificentName:
	.string "Hmmm{SE_M_DIZZY_PUNCH}{STR_VAR_1} i{SE_M_SPIT_UP}is!\p"
	.string "Thi{SE_M_GRASSWHISTLE}i{SE_M_GRASSWHISTLE}{SE_M_CHARGE}magnificen{SE_M_SPIT_UP}nickname!\n"
	.string "I{SE_M_SPIT_UP}i{SE_M_GRASSWHISTLE}impeccabl{SE_M_YAWN}beyon{SE_M_WATERFALL}reproach!\p"
	.string "You'l{SE_M_BATON_PASS}d{SE_M_ATTRACT2}wel{SE_M_BATON_PASS}t{SE_M_ATTRACT2}cheris{SE_M_TRI_ATTACK}your\n"
	.string "{STR_VAR_1} no{SE_M_TWISTER}an{SE_M_WATERFALL}beyond.$"

GoldenrodCity_NameRatersHouse_Text_ThatIsMerelyAnEgg:
	.string "Now{SE_M_SUPERSONIC}now.\n"
	.string "Tha{SE_M_SPIT_UP}i{SE_M_GRASSWHISTLE}merel{SE_M_YAWN}a{SE_M_ATTRACT}EGG!$"

