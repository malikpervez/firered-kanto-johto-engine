@ Johto (data/scripts/mauville_man.inc), as built into the FireRed game.

J_MauvilleCity_PokemonCenter_1F_EventScript_MauvilleOldMan::
	special Script_GetCurrentMauvilleMan
	switch 32781
	case 0, J_MauvilleCity_PokemonCenter_1F_EventScript_Bard
	case 1, J_MauvilleCity_PokemonCenter_1F_EventScript_Hipster
	case 2, J_MauvilleCity_PokemonCenter_1F_EventScript_Trader
	case 3, J_MauvilleCity_PokemonCenter_1F_EventScript_Storyteller
	case 4, J_MauvilleCity_PokemonCenter_1F_EventScript_Giddy
	end

J_MauvilleCity_PokemonCenter_1F_EventScript_Bard::
	lock
	faceplayer
	msgbox J_MauvilleCity_PokemonCenter_1F_Text_WouldYouLikeToHearMySong, MSGBOX_YESNO
	goto_if_eq 32781, YES, J_MauvilleCity_PokemonCenter_1F_EventScript_PlaySong
	goto_if_eq 32781, NO, J_MauvilleCity_PokemonCenter_1F_EventScript_DeclineSong
	end

J_MauvilleCity_PokemonCenter_1F_EventScript_PlaySong::
	setvar 32772, FALSE
	special PlayBardSong
	delay 60
	special HasBardSongBeenChanged
	goto_if_eq 32781, FALSE, J_MauvilleCity_PokemonCenter_1F_EventScript_AskToWriteLyrics
	msgbox J_MauvilleCity_PokemonCenter_1F_Text_WishICouldPlaySongForOthers, MSGBOX_DEFAULT
	release
	end

J_MauvilleCity_PokemonCenter_1F_EventScript_DeclineSong::
	msgbox J_MauvilleCity_PokemonCenter_1F_Text_BardFeelingTheBlues1, MSGBOX_DEFAULT
	release
	end

J_MauvilleCity_PokemonCenter_1F_EventScript_AskToWriteLyrics::
	msgbox J_MauvilleCity_PokemonCenter_1F_Text_WouldYouLikeToWriteSomeLyrics, MSGBOX_YESNO
	goto_if_eq 32781, YES, J_MauvilleCity_PokemonCenter_1F_EventScript_WriteLyrics
	goto_if_eq 32781, NO, J_MauvilleCity_PokemonCenter_1F_EventScript_DeclineWritingLyrics
	end

J_MauvilleCity_PokemonCenter_1F_EventScript_WriteLyrics::
	setvar 32772, 6
	call J_Common_ShowEasyChatScreen
	lock
	faceplayer
	goto_if_eq 32781, 0, J_MauvilleCity_PokemonCenter_1F_EventScript_DeclineWritingLyrics
	msgbox J_MauvilleCity_PokemonCenter_1F_Text_LetMeSingItForYou, MSGBOX_DEFAULT
	setvar 32772, TRUE
	special PlayBardSong
	delay 60
	msgbox J_MauvilleCity_PokemonCenter_1F_Text_ThatHowYouWantedSongToGo, MSGBOX_YESNO
	goto_if_eq 32781, NO, J_MauvilleCity_PokemonCenter_1F_EventScript_WriteLyrics
	special SaveBardSongLyrics
	msgbox J_MauvilleCity_PokemonCenter_1F_Text_IllSingThisSongForAWhile, MSGBOX_DEFAULT
	release
	end

J_MauvilleCity_PokemonCenter_1F_EventScript_DeclineWritingLyrics::
	msgbox J_MauvilleCity_PokemonCenter_1F_Text_BardFeelingTheBlues2, MSGBOX_DEFAULT
	release
	end

J_MauvilleCity_PokemonCenter_1F_EventScript_Hipster::
	lock
	faceplayer
	setflag 0
	msgbox J_MauvilleCity_PokemonCenter_1F_Text_TeachWhatsHipAndHappening, MSGBOX_DEFAULT
	special HasHipsterTaughtWord
	goto_if_eq 32781, FALSE, J_MauvilleCity_PokemonCenter_1F_EventScript_TryTeachWord
	msgbox J_MauvilleCity_PokemonCenter_1F_Text_IAlreadyTaughtYou, MSGBOX_DEFAULT
	release
	end

J_MauvilleCity_PokemonCenter_1F_EventScript_TryTeachWord::
	special HipsterTryTeachWord
	goto_if_eq 32781, TRUE, J_MauvilleCity_PokemonCenter_1F_EventScript_TeachWord
	msgbox J_MauvilleCity_PokemonCenter_1F_Text_IveGotNothingNewToTeach, MSGBOX_DEFAULT
	release
	end

J_MauvilleCity_PokemonCenter_1F_EventScript_TeachWord::
	msgbox J_MauvilleCity_PokemonCenter_1F_Text_HaveYouHeardOfWord, MSGBOX_DEFAULT
	special SetHipsterTaughtWord
	release
	end

J_MauvilleCity_PokemonCenter_1F_Text_WantToTradeDecor:
	.string "Hi{SE_M_SUPERSONIC}I'{SE_M_MILK_DRINK}th{SE_M_REVERSAL}TRADER.\n"
	.string "Wan{SE_M_SPIT_UP}t{SE_M_ATTRACT2}trad{SE_M_REVERSAL}decoration{SE_M_GRASSWHISTLE}wit{SE_M_TRI_ATTACK}me?$"

J_MauvilleCity_PokemonCenter_1F_Text_TraderFeelingTheBlues:
	.string "Oh…\n"
	.string "You'v{SE_M_REVERSAL}lef{SE_M_SPIT_UP}m{SE_M_REVERSAL}feelin{SE_M_SANDSTORM}th{SE_M_REVERSAL}blues…$"

J_MauvilleCity_PokemonCenter_1F_Text_WeveAlreadyTraded:
	.string "Bu{SE_M_SPIT_UP}we'v{SE_M_REVERSAL}trade{SE_M_WATERFALL}decoration{SE_M_GRASSWHISTLE}already,\n"
	.string "yo{SE_M_DIVE}an{SE_M_WATERFALL}I.$"

J_MauvilleCity_PokemonCenter_1F_Text_PickADecorItem:
	.string "I{SE_M_ACID_ARMOR}yo{SE_M_DIVE}se{SE_M_REVERSAL}an{SE_M_YAWN}decorativ{SE_M_REVERSAL}ite{SE_M_MILK_DRINK}that\n"
	.string "yo{SE_M_DIVE}wan{SE_M_SPIT_UP}o{SE_M_ACID_ARMOR}mine{SE_M_SUPERSONIC}spea{SE_M_ENCORE2}up.$"

J_MauvilleCity_PokemonCenter_1F_Text_YouDontWantAnything:
	.string "Yo{SE_M_DIVE}don'{SE_M_SPIT_UP}wan{SE_M_SPIT_UP}anything?\n"
	.string "{SE_M_HEAL_BELL}fee{SE_M_BATON_PASS}unwanted…$"

J_MauvilleCity_PokemonCenter_1F_Text_OnceBelongedToPlayerDoYouWantIt:
	.string "Tha{SE_M_SPIT_UP}decorativ{SE_M_REVERSAL}ite{SE_M_MILK_DRINK}onc{SE_M_REVERSAL}belonged\n"
	.string "t{SE_M_ATTRACT2}{STR_VAR_1}.\p"
	.string "D{SE_M_ATTRACT2}yo{SE_M_DIVE}wan{SE_M_SPIT_UP}it?$"

J_MauvilleCity_PokemonCenter_1F_Text_YouDontHaveAnyDecor:
	.string "Uh{SE_M_DIZZY_PUNCH}Wai{SE_M_SPIT_UP}{SE_M_CHARGE}second{SE_M_PERISH_SONG}Yo{SE_M_DIVE}don'{SE_M_SPIT_UP}hav{SE_M_REVERSAL}a\n"
	.string "singl{SE_M_REVERSAL}piec{SE_M_REVERSAL}o{SE_M_ACID_ARMOR}decoration!$"

J_MauvilleCity_PokemonCenter_1F_Text_PickTheDecorToTrade:
	.string "Okay{SE_M_SUPERSONIC}pic{SE_M_ENCORE2}th{SE_M_REVERSAL}decoratio{SE_M_ATTRACT}tha{SE_M_SPIT_UP}you'll\n"
	.string "trad{SE_M_REVERSAL}t{SE_M_ATTRACT2}me.$"

J_MauvilleCity_PokemonCenter_1F_Text_YouDontWantToTrade:
	.string "Yo{SE_M_DIVE}won'{SE_M_SPIT_UP}trad{SE_M_REVERSAL}wit{SE_M_TRI_ATTACK}me?\n"
	.string "{SE_M_HEAL_BELL}fee{SE_M_BATON_PASS}unwanted…$"

J_MauvilleCity_PokemonCenter_1F_Text_YouveNoRoomForThis:
	.string "You'v{SE_M_REVERSAL}go{SE_M_SPIT_UP}al{SE_M_BATON_PASS}th{SE_M_REVERSAL}{STR_VAR_2}{SE_M_SKETCH}tha{SE_M_SPIT_UP}can\n"
	.string "b{SE_M_REVERSAL}stored{SE_M_PERISH_SONG}You'v{SE_M_REVERSAL}n{SE_M_ATTRACT2}roo{SE_M_MILK_DRINK}fo{SE_M_SAND_TOMB}this.$"

J_MauvilleCity_PokemonCenter_1F_Text_SoWellTradeTheseDecor:
	.string "Okay{SE_M_SUPERSONIC}s{SE_M_ATTRACT2}we'l{SE_M_BATON_PASS}trad{SE_M_REVERSAL}m{SE_M_YAWN}{STR_VAR_3}\n"
	.string "fo{SE_M_SAND_TOMB}you{SE_M_SAND_TOMB}{STR_VAR_2}?$"

J_MauvilleCity_PokemonCenter_1F_Text_ThatDecorIsInUse:
	.string "Tha{SE_M_SPIT_UP}piec{SE_M_REVERSAL}o{SE_M_ACID_ARMOR}decoratio{SE_M_ATTRACT}i{SE_M_GRASSWHISTLE}i{SE_M_ATTRACT}use.\n"
	.string "Yo{SE_M_DIVE}can'{SE_M_SPIT_UP}trad{SE_M_REVERSAL}it.$"

J_MauvilleCity_PokemonCenter_1F_Text_SendDecorToYourPC:
	.string "The{SE_M_ATTRACT}we'l{SE_M_BATON_PASS}trade!\n"
	.string "I'l{SE_M_BATON_PASS}sen{SE_M_WATERFALL}m{SE_M_YAWN}decoratio{SE_M_ATTRACT}t{SE_M_ATTRACT2}you{SE_M_SAND_TOMB}PC.$"

J_MauvilleCity_PokemonCenter_1F_Text_CantTradeThatOne:
	.string "Oops{SE_M_DRAGON_RAGE}Sorry{SE_M_DRAGON_RAGE}That'{SE_M_GRASSWHISTLE}{SE_M_CHARGE}reall{SE_M_YAWN}rare\n"
	.string "piec{SE_M_REVERSAL}o{SE_M_ACID_ARMOR}decoration.\l"
	.string "{SE_M_HEAL_BELL}can'{SE_M_SPIT_UP}trad{SE_M_REVERSAL}tha{SE_M_SPIT_UP}on{SE_M_REVERSAL}away!\p"
	.string "Ca{SE_M_ATTRACT}{SE_M_HEAL_BELL}interes{SE_M_SPIT_UP}yo{SE_M_DIVE}i{SE_M_ATTRACT}somethin{SE_M_SANDSTORM}else?$"

J_MauvilleCity_PokemonCenter_1F_EventScript_Trader::
	lock
	faceplayer
	msgbox J_MauvilleCity_PokemonCenter_1F_Text_WantToTradeDecor, MSGBOX_YESNO
	goto_if_eq 32781, NO, J_MauvilleCity_PokemonCenter_1F_EventScript_DeclineTrade
	special GetTraderTradedFlag
	goto_if_eq 32781, TRUE, J_MauvilleCity_PokemonCenter_1F_EventScript_AlreadyTraded
	message J_MauvilleCity_PokemonCenter_1F_Text_PickADecorItem
	waitmessage
	goto J_MauvilleCity_PokemonCenter_1F_EventScript_PickDecorToReceive
	end

J_MauvilleCity_PokemonCenter_1F_EventScript_DeclineTrade::
	msgbox J_MauvilleCity_PokemonCenter_1F_Text_TraderFeelingTheBlues, MSGBOX_DEFAULT
	release
	end

J_MauvilleCity_PokemonCenter_1F_EventScript_AlreadyTraded::
	msgbox J_MauvilleCity_PokemonCenter_1F_Text_WeveAlreadyTraded, MSGBOX_DEFAULT
	release
	end

J_MauvilleCity_PokemonCenter_1F_EventScript_PickDecorToReceive::
	special TraderMenuGetDecoration
	waitstate
	goto_if_eq 32772, 0, J_MauvilleCity_PokemonCenter_1F_EventScript_CancelPickDecor
	goto_if_eq 32772, 0xFFFF, J_MauvilleCity_PokemonCenter_1F_EventScript_InvalidDecor
	msgbox J_MauvilleCity_PokemonCenter_1F_Text_OnceBelongedToPlayerDoYouWantIt, MSGBOX_YESNO
	goto_if_eq 32781, NO, J_MauvilleCity_PokemonCenter_1F_EventScript_PickDifferentDecor
	special DoesPlayerHaveNoDecorations
	goto_if_eq 32781, TRUE, J_MauvilleCity_PokemonCenter_1F_EventScript_DontHaveAnyDecor
	goto J_MauvilleCity_PokemonCenter_1F_EventScript_PickDecorToGive
	end

J_MauvilleCity_PokemonCenter_1F_EventScript_CancelPickDecor::
	msgbox J_MauvilleCity_PokemonCenter_1F_Text_YouDontWantAnything, MSGBOX_DEFAULT
	release
	end

J_MauvilleCity_PokemonCenter_1F_EventScript_InvalidDecor::
	message J_MauvilleCity_PokemonCenter_1F_Text_CantTradeThatOne
	waitmessage
	goto J_MauvilleCity_PokemonCenter_1F_EventScript_PickDecorToReceive
	end

J_MauvilleCity_PokemonCenter_1F_EventScript_PickDifferentDecor::
	message J_MauvilleCity_PokemonCenter_1F_Text_PickADecorItem
	waitmessage
	goto J_MauvilleCity_PokemonCenter_1F_EventScript_PickDecorToReceive
	end

J_MauvilleCity_PokemonCenter_1F_EventScript_DontHaveAnyDecor::
	msgbox J_MauvilleCity_PokemonCenter_1F_Text_YouDontHaveAnyDecor, MSGBOX_DEFAULT
	release
	end

J_MauvilleCity_PokemonCenter_1F_EventScript_PickDecorToGive::
	msgbox J_MauvilleCity_PokemonCenter_1F_Text_PickTheDecorToTrade, MSGBOX_DEFAULT
	special TraderShowDecorationMenu
	waitstate
	goto_if_eq 32774, 0, J_MauvilleCity_PokemonCenter_1F_EventScript_CancelGiveDecor
	goto_if_eq 32774, 0xFFFF, J_MauvilleCity_PokemonCenter_1F_EventScript_DecorInUse
	special IsDecorationCategoryFull
	goto_if_eq 32781, TRUE, J_MauvilleCity_PokemonCenter_1F_EventScript_NoRoomForDecor
	msgbox J_MauvilleCity_PokemonCenter_1F_Text_SoWellTradeTheseDecor, MSGBOX_YESNO
	goto_if_eq 32781, NO, J_MauvilleCity_PokemonCenter_1F_EventScript_PickDecorToGive
	special TraderDoDecorationTrade
	msgbox J_MauvilleCity_PokemonCenter_1F_Text_SendDecorToYourPC, MSGBOX_DEFAULT
	release
	end

J_MauvilleCity_PokemonCenter_1F_EventScript_CancelGiveDecor::
	msgbox J_MauvilleCity_PokemonCenter_1F_Text_YouDontWantToTrade, MSGBOX_DEFAULT
	release
	end

J_MauvilleCity_PokemonCenter_1F_EventScript_DecorInUse::
	msgbox J_MauvilleCity_PokemonCenter_1F_Text_ThatDecorIsInUse, MSGBOX_DEFAULT
	goto J_MauvilleCity_PokemonCenter_1F_EventScript_PickDecorToGive
	end

J_MauvilleCity_PokemonCenter_1F_EventScript_NoRoomForDecor::
	msgbox J_MauvilleCity_PokemonCenter_1F_Text_YouveNoRoomForThis, MSGBOX_DEFAULT
	release
	end

J_MauvilleCity_PokemonCenter_1F_Text_WillYouHearMyTale:
	.string "I'{SE_M_MILK_DRINK}th{SE_M_REVERSAL}STORYTELLER.\n"
	.string "I'l{SE_M_BATON_PASS}tel{SE_M_BATON_PASS}yo{SE_M_DIVE}tale{SE_M_GRASSWHISTLE}o{SE_M_ACID_ARMOR}legendary\l"
	.string "TRAINERS.\p"
	.string "Wil{SE_M_BATON_PASS}yo{SE_M_DIVE}hea{SE_M_SAND_TOMB}m{SE_M_YAWN}tale?$"

J_MauvilleCity_PokemonCenter_1F_Text_StorytellerFeelingTheBlues:
	.string "Oh…\n"
	.string "You'v{SE_M_REVERSAL}lef{SE_M_SPIT_UP}m{SE_M_REVERSAL}feelin{SE_M_SANDSTORM}th{SE_M_REVERSAL}blues…$"

J_MauvilleCity_PokemonCenter_1F_Text_WhichTaleToTell:
	.string "{SE_M_HEAL_BELL}kno{SE_M_TWISTER}o{SE_M_ACID_ARMOR}thes{SE_M_REVERSAL}legends.\n"
	.string "Whic{SE_M_TRI_ATTACK}tal{SE_M_REVERSAL}wil{SE_M_BATON_PASS}yo{SE_M_DIVE}hav{SE_M_REVERSAL}m{SE_M_REVERSAL}tell?$"

J_MauvilleCity_PokemonCenter_1F_Text_IKnowNoTales:
	.string "But{SE_M_SUPERSONIC}{SE_M_HEAL_BELL}kno{SE_M_TWISTER}o{SE_M_ACID_ARMOR}n{SE_M_ATTRACT2}legendar{SE_M_YAWN}TRAINERS.\n"
	.string "Hence{SE_M_SUPERSONIC}{SE_M_HEAL_BELL}kno{SE_M_TWISTER}n{SE_M_ATTRACT2}tales.\p"
	.string "Wher{SE_M_REVERSAL}doe{SE_M_GRASSWHISTLE}on{SE_M_REVERSAL}fin{SE_M_WATERFALL}{SE_M_CHARGE}TRAINE{SE_M_MINIMIZE}worthy\n"
	.string "o{SE_M_ACID_ARMOR}{SE_M_CHARGE}legendar{SE_M_YAWN}tale?$"

J_MauvilleCity_PokemonCenter_1F_Text_YouDidStatXTimes:
	.string "What'{SE_M_GRASSWHISTLE}that?!\n"
	.string "You{SE_M_DIZZY_PUNCH}You…\p"
	.string "{STR_VAR_2}\n"
	.string "{STR_VAR_1} time(s)?!\p"
	.string "Tha{SE_M_SPIT_UP}i{SE_M_GRASSWHISTLE}indee{SE_M_WATERFALL}magnificent!\n"
	.string "It'{SE_M_GRASSWHISTLE}th{SE_M_REVERSAL}birt{SE_M_TRI_ATTACK}o{SE_M_ACID_ARMOR}{SE_M_CHARGE}ne{SE_M_TWISTER}legend!$"

J_MauvilleCity_PokemonCenter_1F_Text_CouldThereBeOtherLegends:
	.string "I{SE_M_SPIT_UP}get{SE_M_GRASSWHISTLE}m{SE_M_REVERSAL}thinking{SE_M_SUPERSONIC}coul{SE_M_WATERFALL}ther{SE_M_REVERSAL}be\n"
	.string "othe{SE_M_SAND_TOMB}TRAINER{SE_M_SKETCH}wit{SE_M_TRI_ATTACK}mor{SE_M_REVERSAL}impressive\l"
	.string "legend{SE_M_GRASSWHISTLE}awaitin{SE_M_SANDSTORM}discovery?$"

J_MauvilleCity_PokemonCenter_1F_Text_HaveYouAnyLegendaryTales:
	.string "Ar{SE_M_REVERSAL}yo{SE_M_DIVE}{SE_M_CHARGE}TRAINER?\p"
	.string "The{SE_M_ATTRACT}tel{SE_M_BATON_PASS}me{SE_M_SUPERSONIC}hav{SE_M_REVERSAL}yo{SE_M_DIVE}an{SE_M_YAWN}tale{SE_M_GRASSWHISTLE}that\n"
	.string "ar{SE_M_REVERSAL}eve{SE_M_ATTRACT}remotel{SE_M_YAWN}legendary?$"

J_MauvilleCity_PokemonCenter_1F_Text_HearAnotherLegendaryTale:
	.string "Incidentally{SE_M_DIZZY_PUNCH}Woul{SE_M_WATERFALL}yo{SE_M_DIVE}car{SE_M_REVERSAL}t{SE_M_ATTRACT2}hear\n"
	.string "anothe{SE_M_SAND_TOMB}legendar{SE_M_YAWN}tale?$"

J_MauvilleCity_PokemonCenter_1F_Text_NotWorthyOfLegend:
	.string "Hmm…\n"
	.string "I'{SE_M_MILK_DRINK}no{SE_M_SPIT_UP}satisfied…\p"
	.string "{SE_M_HEAL_BELL}wis{SE_M_TRI_ATTACK}yo{SE_M_DIVE}woul{SE_M_WATERFALL}brin{SE_M_SANDSTORM}m{SE_M_REVERSAL}new{SE_M_GRASSWHISTLE}worthy\n"
	.string "o{SE_M_ACID_ARMOR}bein{SE_M_SANDSTORM}calle{SE_M_WATERFALL}{SE_M_CHARGE}legend.$"

J_MauvilleCity_PokemonCenter_1F_Text_IWishMorePeopleWereInterested:
	.string "{SE_M_HEAL_BELL}wis{SE_M_TRI_ATTACK}mor{SE_M_REVERSAL}peopl{SE_M_REVERSAL}woul{SE_M_WATERFALL}b{SE_M_REVERSAL}interested\n"
	.string "i{SE_M_ATTRACT}hearin{SE_M_SANDSTORM}m{SE_M_YAWN}epi{SE_M_HYPER_BEAM}tale{SE_M_GRASSWHISTLE}o{SE_M_ACID_ARMOR}legendary\l"
	.string "TRAINERS.$"

J_MauvilleCity_PokemonCenter_1F_Text_SavedGameTitle::
	.string "Th{SE_M_REVERSAL}Save-Happ{SE_M_YAWN}TRAINER$"

J_MauvilleCity_PokemonCenter_1F_Text_SavedGameAction::
	.string "Save{SE_M_WATERFALL}th{SE_M_REVERSAL}game$"

J_MauvilleCity_PokemonCenter_1F_Text_SavedGameStory::
	.string "Thi{SE_M_GRASSWHISTLE}i{SE_M_GRASSWHISTLE}{SE_M_CHARGE}tal{SE_M_REVERSAL}o{SE_M_ACID_ARMOR}{SE_M_CHARGE}TRAINER\n"
	.string "name{SE_M_WATERFALL}{STR_VAR_3}.\p"
	.string "Thi{SE_M_GRASSWHISTLE}TRAINE{SE_M_MINIMIZE}save{SE_M_WATERFALL}th{SE_M_REVERSAL}game\n"
	.string "{STR_VAR_1} times!\p"
	.string "{SE_M_BONEMERANG}mor{SE_M_REVERSAL}cautiou{SE_M_GRASSWHISTLE}TRAINE{SE_M_MINIMIZE}than\n"
	.string "{STR_VAR_3} on{SE_M_REVERSAL}wil{SE_M_BATON_PASS}neve{SE_M_SAND_TOMB}find!$"

J_MauvilleCity_PokemonCenter_1F_Text_TrendsStartedTitle::
	.string "Th{SE_M_REVERSAL}Trendsette{SE_M_SAND_TOMB}TRAINER$"

J_MauvilleCity_PokemonCenter_1F_Text_TrendsStartedAction::
	.string "Starte{SE_M_WATERFALL}trends$"

J_MauvilleCity_PokemonCenter_1F_Text_TrendsStartedStory::
	.string "Thi{SE_M_GRASSWHISTLE}i{SE_M_GRASSWHISTLE}{SE_M_CHARGE}tal{SE_M_REVERSAL}o{SE_M_ACID_ARMOR}{SE_M_CHARGE}TRAINER\n"
	.string "name{SE_M_WATERFALL}{STR_VAR_3}.\p"
	.string "Thi{SE_M_GRASSWHISTLE}TRAINE{SE_M_MINIMIZE}starte{SE_M_WATERFALL}ne{SE_M_TWISTER}trends\n"
	.string "{STR_VAR_1} times!\p"
	.string "{STR_VAR_3} i{SE_M_GRASSWHISTLE}settin{SE_M_SANDSTORM}trend{SE_M_GRASSWHISTLE}fo{SE_M_SAND_TOMB}all\n"
	.string "th{SE_M_REVERSAL}HOEN{SE_M_PSYBEAM2}region!$"

J_MauvilleCity_PokemonCenter_1F_Text_BerriesPlantedTitle::
	.string "Th{SE_M_REVERSAL}BERRY-Plantin{SE_M_SANDSTORM}TRAINER$"

J_MauvilleCity_PokemonCenter_1F_Text_BerriesPlantedAction::
	.string "Plante{SE_M_WATERFALL}BERRIES$"

J_MauvilleCity_PokemonCenter_1F_Text_BerriesPlantedStory::
	.string "Thi{SE_M_GRASSWHISTLE}i{SE_M_GRASSWHISTLE}{SE_M_CHARGE}tal{SE_M_REVERSAL}o{SE_M_ACID_ARMOR}{SE_M_CHARGE}TRAINER\n"
	.string "name{SE_M_WATERFALL}{STR_VAR_3}.\p"
	.string "Thi{SE_M_GRASSWHISTLE}TRAINE{SE_M_MINIMIZE}plante{SE_M_WATERFALL}BERRIES\n"
	.string "{STR_VAR_1} times!\p"
	.string "{STR_VAR_3} i{SE_M_GRASSWHISTLE}{SE_M_CHARGE}legendar{SE_M_YAWN}love{SE_M_SAND_TOMB}of\n"
	.string "BERRIES!$"

J_MauvilleCity_PokemonCenter_1F_Text_BikeTradesTitle::
	.string "Th{SE_M_REVERSAL}BIKE-Lovin{SE_M_SANDSTORM}TRAINER$"

J_MauvilleCity_PokemonCenter_1F_Text_BikeTradesAction::
	.string "Trade{SE_M_WATERFALL}BIKES$"

J_MauvilleCity_PokemonCenter_1F_Text_BikeTradesStory::
	.string "Thi{SE_M_GRASSWHISTLE}i{SE_M_GRASSWHISTLE}{SE_M_CHARGE}tal{SE_M_REVERSAL}o{SE_M_ACID_ARMOR}{SE_M_CHARGE}TRAINER\n"
	.string "name{SE_M_WATERFALL}{STR_VAR_3}.\p"
	.string "Thi{SE_M_GRASSWHISTLE}TRAINE{SE_M_MINIMIZE}swappe{SE_M_WATERFALL}BIKES\n"
	.string "{STR_VAR_1} times!\p"
	.string "{STR_VAR_3} mus{SE_M_SPIT_UP}lov{SE_M_REVERSAL}BIKE{SE_M_SKETCH}deeply\n"
	.string "an{SE_M_WATERFALL}passionately!$"

J_MauvilleCity_PokemonCenter_1F_Text_InterviewsTitle::
	.string "Th{SE_M_REVERSAL}Interviewe{SE_M_WATERFALL}TRAINER$"

J_MauvilleCity_PokemonCenter_1F_Text_InterviewsAction::
	.string "Go{SE_M_SPIT_UP}interviewed$"

J_MauvilleCity_PokemonCenter_1F_Text_InterviewsStory::
	.string "Thi{SE_M_GRASSWHISTLE}i{SE_M_GRASSWHISTLE}{SE_M_CHARGE}tal{SE_M_REVERSAL}o{SE_M_ACID_ARMOR}{SE_M_CHARGE}TRAINER\n"
	.string "name{SE_M_WATERFALL}{STR_VAR_3}.\p"
	.string "Thi{SE_M_GRASSWHISTLE}TRAINE{SE_M_MINIMIZE}go{SE_M_SPIT_UP}interviewed\n"
	.string "{STR_VAR_1} times!\p"
	.string "{STR_VAR_3} mus{SE_M_SPIT_UP}b{SE_M_REVERSAL}{SE_M_CHARGE}TRAINE{SE_M_MINIMIZE}who's\n"
	.string "attractin{SE_M_SANDSTORM}muc{SE_M_TRI_ATTACK}attention!$"

J_MauvilleCity_PokemonCenter_1F_Text_TrainerBattlesTitle::
	.string "Th{SE_M_REVERSAL}Battle-Happ{SE_M_YAWN}TRAINER$"

J_MauvilleCity_PokemonCenter_1F_Text_TrainerBattlesAction::
	.string "Battled$"

J_MauvilleCity_PokemonCenter_1F_Text_TrainerBattlesStory::
	.string "Thi{SE_M_GRASSWHISTLE}i{SE_M_GRASSWHISTLE}{SE_M_CHARGE}tal{SE_M_REVERSAL}o{SE_M_ACID_ARMOR}{SE_M_CHARGE}TRAINER\n"
	.string "name{SE_M_WATERFALL}{STR_VAR_3}.\p"
	.string "Thi{SE_M_GRASSWHISTLE}TRAINE{SE_M_MINIMIZE}battle{SE_M_WATERFALL}{STR_VAR_1} times!\p"
	.string "{STR_VAR_3} mus{SE_M_SPIT_UP}b{SE_M_REVERSAL}{SE_M_CHARGE}TRAINE{SE_M_MINIMIZE}wh{SE_M_ATTRACT2}can\n"
	.string "neve{SE_M_SAND_TOMB}refus{SE_M_REVERSAL}{SE_M_CHARGE}chanc{SE_M_REVERSAL}t{SE_M_ATTRACT2}battle!$"

J_MauvilleCity_PokemonCenter_1F_Text_PokemonCaughtTitle::
	.string "Th{SE_M_REVERSAL}POKéMON-Catchin{SE_M_SANDSTORM}TRAINER$"

J_MauvilleCity_PokemonCenter_1F_Text_PokemonCaughtAction::
	.string "Caugh{SE_M_SPIT_UP}POKéMON$"

J_MauvilleCity_PokemonCenter_1F_Text_PokemonCaughtStory::
	.string "Thi{SE_M_GRASSWHISTLE}i{SE_M_GRASSWHISTLE}{SE_M_CHARGE}tal{SE_M_REVERSAL}o{SE_M_ACID_ARMOR}{SE_M_CHARGE}TRAINER\n"
	.string "name{SE_M_WATERFALL}{STR_VAR_3}.\p"
	.string "Thi{SE_M_GRASSWHISTLE}TRAINE{SE_M_MINIMIZE}caught\n"
	.string "{STR_VAR_1} POKéMON!\p"
	.string "{STR_VAR_3} i{SE_M_GRASSWHISTLE}{SE_M_CHARGE}legendar{SE_M_YAWN}catche{SE_M_SAND_TOMB}of\n"
	.string "wil{SE_M_WATERFALL}POKéMON!$"

J_MauvilleCity_PokemonCenter_1F_Text_FishingPokemonCaughtTitle::
	.string "Th{SE_M_REVERSAL}Fishin{SE_M_SANDSTORM}TRAINER$"

J_MauvilleCity_PokemonCenter_1F_Text_FishingPokemonCaughtAction::
	.string "Caugh{SE_M_SPIT_UP}POKéMO{SE_M_PSYBEAM2}wit{SE_M_TRI_ATTACK}{SE_M_CHARGE}ROD$"

J_MauvilleCity_PokemonCenter_1F_Text_FishingPokemonCaughtStory::
	.string "Thi{SE_M_GRASSWHISTLE}i{SE_M_GRASSWHISTLE}{SE_M_CHARGE}tal{SE_M_REVERSAL}o{SE_M_ACID_ARMOR}{SE_M_CHARGE}TRAINER\n"
	.string "name{SE_M_WATERFALL}{STR_VAR_3}.\p"
	.string "Thi{SE_M_GRASSWHISTLE}TRAINE{SE_M_MINIMIZE}caught\n"
	.string "{STR_VAR_1} POKéMO{SE_M_PSYBEAM2}whil{SE_M_REVERSAL}fishing!\p"
	.string "{STR_VAR_3} i{SE_M_GRASSWHISTLE}{SE_M_CHARGE}legendar{SE_M_YAWN}fishing\n"
	.string "expert!$"

J_MauvilleCity_PokemonCenter_1F_Text_EggsHatchedTitle::
	.string "Th{SE_M_REVERSAL}EGG-Warmin{SE_M_SANDSTORM}TRAINER$"

J_MauvilleCity_PokemonCenter_1F_Text_EggsHatchedAction::
	.string "Hatche{SE_M_WATERFALL}EGGS$"

J_MauvilleCity_PokemonCenter_1F_Text_EggsHatchedStory::
	.string "Thi{SE_M_GRASSWHISTLE}i{SE_M_GRASSWHISTLE}{SE_M_CHARGE}tal{SE_M_REVERSAL}o{SE_M_ACID_ARMOR}{SE_M_CHARGE}TRAINER\n"
	.string "name{SE_M_WATERFALL}{STR_VAR_3}.\p"
	.string "Thi{SE_M_GRASSWHISTLE}TRAINE{SE_M_MINIMIZE}hatche{SE_M_WATERFALL}{STR_VAR_1} POKéMON\n"
	.string "fro{SE_M_MILK_DRINK}EGGS!\p"
	.string "{STR_VAR_3} i{SE_M_GRASSWHISTLE}{SE_M_CHARGE}legendar{SE_M_YAWN}warmer\n"
	.string "o{SE_M_ACID_ARMOR}EGGS!$"

J_MauvilleCity_PokemonCenter_1F_Text_PokemonEvolvedTitle::
	.string "Th{SE_M_REVERSAL}Evolve{SE_M_SAND_TOMB}TRAINER$"

J_MauvilleCity_PokemonCenter_1F_Text_PokemonEvolvedAction::
	.string "Evolve{SE_M_WATERFALL}POKéMON$"

J_MauvilleCity_PokemonCenter_1F_Text_PokemonEvolvedStory::
	.string "Thi{SE_M_GRASSWHISTLE}i{SE_M_GRASSWHISTLE}{SE_M_CHARGE}tal{SE_M_REVERSAL}o{SE_M_ACID_ARMOR}{SE_M_CHARGE}TRAINER\n"
	.string "name{SE_M_WATERFALL}{STR_VAR_3}.\p"
	.string "Thi{SE_M_GRASSWHISTLE}TRAINE{SE_M_MINIMIZE}mad{SE_M_REVERSAL}{STR_VAR_1} POKéMON\n"
	.string "evolve!\p"
	.string "{STR_VAR_3} i{SE_M_GRASSWHISTLE}th{SE_M_REVERSAL}ultimat{SE_M_REVERSAL}evolver\n"
	.string "o{SE_M_ACID_ARMOR}POKéMON!$"

J_MauvilleCity_PokemonCenter_1F_Text_UsedPokemonCenterTitle::
	.string "Th{SE_M_REVERSAL}POKéMO{SE_M_PSYBEAM2}CENTER-Lovin{SE_M_SANDSTORM}TRAINER$"

J_MauvilleCity_PokemonCenter_1F_Text_UsedPokemonCenterAction::
	.string "Use{SE_M_WATERFALL}POKéMO{SE_M_PSYBEAM2}CENTERS$"

J_MauvilleCity_PokemonCenter_1F_Text_UsedPokemonCenterStory::
	.string "Thi{SE_M_GRASSWHISTLE}i{SE_M_GRASSWHISTLE}{SE_M_CHARGE}tal{SE_M_REVERSAL}o{SE_M_ACID_ARMOR}{SE_M_CHARGE}TRAINER\n"
	.string "name{SE_M_WATERFALL}{STR_VAR_3}.\p"
	.string "Thi{SE_M_GRASSWHISTLE}TRAINE{SE_M_MINIMIZE}heale{SE_M_WATERFALL}POKéMON\n"
	.string "{STR_VAR_1} time{SE_M_GRASSWHISTLE}a{SE_M_SPIT_UP}POKéMO{SE_M_PSYBEAM2}CENTERS!\p"
	.string "Ther{SE_M_REVERSAL}coul{SE_M_WATERFALL}b{SE_M_REVERSAL}n{SE_M_ATTRACT2}greate{SE_M_SAND_TOMB}love{SE_M_SAND_TOMB}of\n"
	.string "POKéMO{SE_M_PSYBEAM2}CENTER{SE_M_SKETCH}tha{SE_M_ATTRACT}{STR_VAR_3}!$"

J_MauvilleCity_PokemonCenter_1F_Text_RestedAtHomeTitle::
	.string "Th{SE_M_REVERSAL}Homebod{SE_M_YAWN}TRAINER$"

J_MauvilleCity_PokemonCenter_1F_Text_RestedAtHomeAction::
	.string "Reste{SE_M_WATERFALL}POKéMO{SE_M_PSYBEAM2}a{SE_M_SPIT_UP}home$"

J_MauvilleCity_PokemonCenter_1F_Text_RestedAtHomeStory::
	.string "Thi{SE_M_GRASSWHISTLE}i{SE_M_GRASSWHISTLE}{SE_M_CHARGE}tal{SE_M_REVERSAL}o{SE_M_ACID_ARMOR}{SE_M_CHARGE}TRAINER\n"
	.string "name{SE_M_WATERFALL}{STR_VAR_3}.\p"
	.string "Thi{SE_M_GRASSWHISTLE}TRAINE{SE_M_MINIMIZE}heale{SE_M_WATERFALL}POKéMON\n"
	.string "{STR_VAR_1} time{SE_M_GRASSWHISTLE}a{SE_M_SPIT_UP}home!\p"
	.string "Ther{SE_M_REVERSAL}coul{SE_M_WATERFALL}b{SE_M_REVERSAL}n{SE_M_ATTRACT2}mor{SE_M_REVERSAL}o{SE_M_ACID_ARMOR}{SE_M_CHARGE}homebody\n"
	.string "tha{SE_M_ATTRACT}{STR_VAR_3}!$"

J_MauvilleCity_PokemonCenter_1F_Text_SafariGamesTitle::
	.string "Th{SE_M_REVERSAL}SAFARI-Lovin{SE_M_SANDSTORM}TRAINER$"

J_MauvilleCity_PokemonCenter_1F_Text_SafariGamesAction::
	.string "Entere{SE_M_WATERFALL}th{SE_M_REVERSAL}SAFAR{SE_M_HEAL_BELL}ZONE$"

J_MauvilleCity_PokemonCenter_1F_Text_SafariGamesStory::
	.string "Thi{SE_M_GRASSWHISTLE}i{SE_M_GRASSWHISTLE}{SE_M_CHARGE}tal{SE_M_REVERSAL}o{SE_M_ACID_ARMOR}{SE_M_CHARGE}TRAINER\n"
	.string "name{SE_M_WATERFALL}{STR_VAR_3}.\p"
	.string "Thi{SE_M_GRASSWHISTLE}TRAINE{SE_M_MINIMIZE}wen{SE_M_SPIT_UP}int{SE_M_ATTRACT2}th{SE_M_REVERSAL}SAFAR{SE_M_HEAL_BELL}ZONE\n"
	.string "{STR_VAR_1} times!\p"
	.string "{STR_VAR_3} i{SE_M_GRASSWHISTLE}{SE_M_CHARGE}TRAINE{SE_M_MINIMIZE}whos{SE_M_REVERSAL}wil{SE_M_WATERFALL}side\n"
	.string "mus{SE_M_SPIT_UP}com{SE_M_REVERSAL}ou{SE_M_SPIT_UP}i{SE_M_ATTRACT}th{SE_M_REVERSAL}SAFAR{SE_M_HEAL_BELL}ZONE!$"

J_MauvilleCity_PokemonCenter_1F_Text_UsedCutTitle::
	.string "Th{SE_M_REVERSAL}CUT-Frenz{SE_M_YAWN}TRAINER$"

J_MauvilleCity_PokemonCenter_1F_Text_UsedCutAction::
	.string "Use{SE_M_WATERFALL}CUT$"

J_MauvilleCity_PokemonCenter_1F_Text_UsedCutStory::
	.string "Thi{SE_M_GRASSWHISTLE}i{SE_M_GRASSWHISTLE}{SE_M_CHARGE}tal{SE_M_REVERSAL}o{SE_M_ACID_ARMOR}{SE_M_CHARGE}TRAINER\n"
	.string "name{SE_M_WATERFALL}{STR_VAR_3}.\p"
	.string "Thi{SE_M_GRASSWHISTLE}TRAINE{SE_M_MINIMIZE}use{SE_M_WATERFALL}CUT\n"
	.string "{STR_VAR_1} times!\p"
	.string "{STR_VAR_3} i{SE_M_GRASSWHISTLE}{SE_M_CHARGE}TRAINE{SE_M_MINIMIZE}wh{SE_M_ATTRACT2}jus{SE_M_SPIT_UP}must\n"
	.string "lov{SE_M_REVERSAL}t{SE_M_ATTRACT2}CUT!$"

J_MauvilleCity_PokemonCenter_1F_Text_UsedRockSmashTitle::
	.string "Th{SE_M_REVERSAL}ROCK-SMASHIN{SE_M_SWAGGER}TRAINER$"

J_MauvilleCity_PokemonCenter_1F_Text_UsedRockSmashAction::
	.string "Smashe{SE_M_WATERFALL}rocks$"

J_MauvilleCity_PokemonCenter_1F_Text_UsedRockSmashStory::
	.string "Thi{SE_M_GRASSWHISTLE}i{SE_M_GRASSWHISTLE}{SE_M_CHARGE}tal{SE_M_REVERSAL}o{SE_M_ACID_ARMOR}{SE_M_CHARGE}TRAINER\n"
	.string "name{SE_M_WATERFALL}{STR_VAR_3}.\p"
	.string "Thi{SE_M_GRASSWHISTLE}TRAINE{SE_M_MINIMIZE}use{SE_M_WATERFALL}ROC{SE_M_SNORE}SMASH\n"
	.string "{STR_VAR_1} times!\p"
	.string "{STR_VAR_3} mus{SE_M_SPIT_UP}b{SE_M_REVERSAL}{SE_M_CHARGE}TRAINE{SE_M_MINIMIZE}who\n"
	.string "can'{SE_M_SPIT_UP}leav{SE_M_REVERSAL}{SE_M_CHARGE}ston{SE_M_REVERSAL}unsmashed!$"

J_MauvilleCity_PokemonCenter_1F_Text_MovedBasesTitle::
	.string "Th{SE_M_REVERSAL}Move-Lovin{SE_M_SANDSTORM}TRAINER$"

J_MauvilleCity_PokemonCenter_1F_Text_MovedBasesAction::
	.string "Move{SE_M_WATERFALL}th{SE_M_REVERSAL}SECRE{SE_M_SWIFT}BASE$"

J_MauvilleCity_PokemonCenter_1F_Text_MovedBasesStory::
	.string "Thi{SE_M_GRASSWHISTLE}i{SE_M_GRASSWHISTLE}{SE_M_CHARGE}tal{SE_M_REVERSAL}o{SE_M_ACID_ARMOR}{SE_M_CHARGE}TRAINER\n"
	.string "name{SE_M_WATERFALL}{STR_VAR_3}.\p"
	.string "Thi{SE_M_GRASSWHISTLE}TRAINE{SE_M_MINIMIZE}move{SE_M_WATERFALL}th{SE_M_REVERSAL}SECRE{SE_M_SWIFT}BASE\n"
	.string "{STR_VAR_1} times!\p"
	.string "{STR_VAR_3} i{SE_M_GRASSWHISTLE}{SE_M_CHARGE}TRAINE{SE_M_MINIMIZE}wh{SE_M_ATTRACT2}loves\n"
	.string "t{SE_M_ATTRACT2}mov{SE_M_REVERSAL}house{SE_M_GRASSWHISTLE}often!$"

J_MauvilleCity_PokemonCenter_1F_Text_UsedSplashTitle::
	.string "Th{SE_M_REVERSAL}SPLASH-Happ{SE_M_YAWN}TRAINER$"

J_MauvilleCity_PokemonCenter_1F_Text_UsedSplashAction::
	.string "Use{SE_M_WATERFALL}SPLASH$"

J_MauvilleCity_PokemonCenter_1F_Text_UsedSplashStory::
	.string "Thi{SE_M_GRASSWHISTLE}i{SE_M_GRASSWHISTLE}{SE_M_CHARGE}tal{SE_M_REVERSAL}o{SE_M_ACID_ARMOR}{SE_M_CHARGE}TRAINER\n"
	.string "name{SE_M_WATERFALL}{STR_VAR_3}.\p"
	.string "Thi{SE_M_GRASSWHISTLE}TRAINE{SE_M_MINIMIZE}use{SE_M_WATERFALL}SPLASH\n"
	.string "{STR_VAR_1} times!\p"
	.string "{STR_VAR_3} i{SE_M_GRASSWHISTLE}{SE_M_CHARGE}TRAINE{SE_M_MINIMIZE}wh{SE_M_ATTRACT2}mus{SE_M_SPIT_UP}love\n"
	.string "SPLASHIN{SE_M_SWAGGER}around!$"

J_MauvilleCity_PokemonCenter_1F_Text_UsedStruggleTitle::
	.string "Th{SE_M_REVERSAL}Tenaciou{SE_M_GRASSWHISTLE}TRAINER$"

J_MauvilleCity_PokemonCenter_1F_Text_UsedStruggleAction::
	.string "Resorte{SE_M_WATERFALL}t{SE_M_ATTRACT2}usin{SE_M_SANDSTORM}STRUGGLE$"

J_MauvilleCity_PokemonCenter_1F_Text_UsedStruggleStory::
	.string "Thi{SE_M_GRASSWHISTLE}i{SE_M_GRASSWHISTLE}{SE_M_CHARGE}tal{SE_M_REVERSAL}o{SE_M_ACID_ARMOR}{SE_M_CHARGE}TRAINER\n"
	.string "name{SE_M_WATERFALL}{STR_VAR_3}.\p"
	.string "Thi{SE_M_GRASSWHISTLE}TRAINE{SE_M_MINIMIZE}ha{SE_M_WATERFALL}t{SE_M_ATTRACT2}rel{SE_M_YAWN}o{SE_M_ATTRACT}STRUGGLE\n"
	.string "{STR_VAR_1} times!\p"
	.string "{STR_VAR_3} i{SE_M_GRASSWHISTLE}{SE_M_CHARGE}tenaciou{SE_M_GRASSWHISTLE}TRAINER\n"
	.string "wh{SE_M_ATTRACT2}neve{SE_M_SAND_TOMB}give{SE_M_GRASSWHISTLE}i{SE_M_ATTRACT}t{SE_M_ATTRACT2}adversity!$"

J_MauvilleCity_PokemonCenter_1F_Text_SlotJackpotsTitle::
	.string "Th{SE_M_REVERSAL}SLO{SE_M_SWIFT}Champ$"

J_MauvilleCity_PokemonCenter_1F_Text_SlotJackpotsAction::
	.string "Wo{SE_M_ATTRACT}th{SE_M_REVERSAL}jackpo{SE_M_SPIT_UP}o{SE_M_ATTRACT}th{SE_M_REVERSAL}SLOTS$"

J_MauvilleCity_PokemonCenter_1F_Text_SlotJackpotsStory::
	.string "Thi{SE_M_GRASSWHISTLE}i{SE_M_GRASSWHISTLE}{SE_M_CHARGE}tal{SE_M_REVERSAL}o{SE_M_ACID_ARMOR}{SE_M_CHARGE}TRAINER\n"
	.string "name{SE_M_WATERFALL}{STR_VAR_3}.\p"
	.string "Thi{SE_M_GRASSWHISTLE}TRAINE{SE_M_MINIMIZE}wo{SE_M_ATTRACT}th{SE_M_REVERSAL}jackpo{SE_M_SPIT_UP}on\n"
	.string "th{SE_M_REVERSAL}SLOT{SE_M_SKETCH}{STR_VAR_1} times.\p"
	.string "{STR_VAR_3} i{SE_M_GRASSWHISTLE}{SE_M_CHARGE}TRAINE{SE_M_MINIMIZE}wh{SE_M_ATTRACT2}wa{SE_M_GRASSWHISTLE}lucky\n"
	.string "o{SE_M_ATTRACT}th{SE_M_REVERSAL}SLOTS!$"

J_MauvilleCity_PokemonCenter_1F_Text_RouletteWinsTitle::
	.string "Th{SE_M_REVERSAL}ROULETT{SE_M_SWORDS_DANCE}Champ$"

J_MauvilleCity_PokemonCenter_1F_Text_RouletteWinsAction::
	.string "Ha{SE_M_WATERFALL}consecutiv{SE_M_REVERSAL}ROULETT{SE_M_SWORDS_DANCE}win{SE_M_GRASSWHISTLE}of$"

J_MauvilleCity_PokemonCenter_1F_Text_RouletteWinsStory::
	.string "Thi{SE_M_GRASSWHISTLE}i{SE_M_GRASSWHISTLE}{SE_M_CHARGE}tal{SE_M_REVERSAL}o{SE_M_ACID_ARMOR}{SE_M_CHARGE}TRAINER\n"
	.string "name{SE_M_WATERFALL}{STR_VAR_3}.\p"
	.string "Thi{SE_M_GRASSWHISTLE}TRAINE{SE_M_MINIMIZE}wo{SE_M_ATTRACT}i{SE_M_ATTRACT}ROULETTE\n"
	.string "{STR_VAR_1} time{SE_M_GRASSWHISTLE}i{SE_M_ATTRACT}{SE_M_CHARGE}row.\p"
	.string "{STR_VAR_3} wa{SE_M_GRASSWHISTLE}luck{SE_M_YAWN}whe{SE_M_ATTRACT}th{SE_M_REVERSAL}ball\n"
	.string "bounce{SE_M_WATERFALL}i{SE_M_ATTRACT}ROULETTE!$"

J_MauvilleCity_PokemonCenter_1F_Text_BattleTowerChallengesTitle::
	.string "Th{SE_M_REVERSAL}BATTL{SE_M_SWORDS_DANCE}TOWE{SE_M_MINIMIZE}Challenger$"

J_MauvilleCity_PokemonCenter_1F_Text_BattleTowerChallengesAction::
	.string "Too{SE_M_ENCORE2}th{SE_M_REVERSAL}BATTL{SE_M_SWORDS_DANCE}TOWE{SE_M_MINIMIZE}challenge$"

J_MauvilleCity_PokemonCenter_1F_Text_BattleTowerChallengesStory::
	.string "Thi{SE_M_GRASSWHISTLE}i{SE_M_GRASSWHISTLE}{SE_M_CHARGE}tal{SE_M_REVERSAL}o{SE_M_ACID_ARMOR}{SE_M_CHARGE}TRAINER\n"
	.string "name{SE_M_WATERFALL}{STR_VAR_3}.\p"
	.string "Thi{SE_M_GRASSWHISTLE}TRAINE{SE_M_MINIMIZE}too{SE_M_ENCORE2}th{SE_M_REVERSAL}BATTL{SE_M_SWORDS_DANCE}TOWER\n"
	.string "challeng{SE_M_REVERSAL}{STR_VAR_1} times!\p"
	.string "{STR_VAR_3} i{SE_M_GRASSWHISTLE}{SE_M_CHARGE}TRAINE{SE_M_MINIMIZE}wh{SE_M_ATTRACT2}aspires\n"
	.string "fo{SE_M_SAND_TOMB}excellenc{SE_M_REVERSAL}i{SE_M_ATTRACT}th{SE_M_REVERSAL}BATTL{SE_M_SWORDS_DANCE}TOWER!$"

J_MauvilleCity_PokemonCenter_1F_Text_MadePokeblocksTitle::
	.string "Th{SE_M_REVERSAL}Blend-Lovin{SE_M_SANDSTORM}TRAINER$"

J_MauvilleCity_PokemonCenter_1F_Text_MadePokeblocksAction::
	.string "Mad{SE_M_REVERSAL}{POKEBLOCK}S$"

J_MauvilleCity_PokemonCenter_1F_Text_MadePokeblocksStory::
	.string "Thi{SE_M_GRASSWHISTLE}i{SE_M_GRASSWHISTLE}{SE_M_CHARGE}tal{SE_M_REVERSAL}o{SE_M_ACID_ARMOR}{SE_M_CHARGE}TRAINER\n"
	.string "name{SE_M_WATERFALL}{STR_VAR_3}.\p"
	.string "Thi{SE_M_GRASSWHISTLE}TRAINE{SE_M_MINIMIZE}mad{SE_M_REVERSAL}{POKEBLOCK}S\n"
	.string "{STR_VAR_1} times!\p"
	.string "Ther{SE_M_REVERSAL}i{SE_M_GRASSWHISTLE}non{SE_M_REVERSAL}bette{SE_M_SAND_TOMB}a{SE_M_SPIT_UP}usin{SE_M_SANDSTORM}{SE_M_CHARGE}BERRY\n"
	.string "BLENDE{SE_M_MINIMIZE}tha{SE_M_ATTRACT}{STR_VAR_3}!$"

J_MauvilleCity_PokemonCenter_1F_Text_EnteredContestsTitle::
	.string "Th{SE_M_REVERSAL}CONTEST-Lovin{SE_M_SANDSTORM}TRAINER$"

J_MauvilleCity_PokemonCenter_1F_Text_EnteredContestsAction::
	.string "Entere{SE_M_WATERFALL}CONTESTS$"

J_MauvilleCity_PokemonCenter_1F_Text_EnteredContestsStory::
	.string "Thi{SE_M_GRASSWHISTLE}i{SE_M_GRASSWHISTLE}{SE_M_CHARGE}tal{SE_M_REVERSAL}o{SE_M_ACID_ARMOR}{SE_M_CHARGE}TRAINER\n"
	.string "name{SE_M_WATERFALL}{STR_VAR_3}.\p"
	.string "Thi{SE_M_GRASSWHISTLE}TRAINE{SE_M_MINIMIZE}entere{SE_M_WATERFALL}CONTESTS\n"
	.string "{STR_VAR_1} times!\p"
	.string "{STR_VAR_3} mus{SE_M_SPIT_UP}lov{SE_M_REVERSAL}showin{SE_M_SANDSTORM}off\n"
	.string "POKéMO{SE_M_PSYBEAM2}t{SE_M_ATTRACT2}others!$"

J_MauvilleCity_PokemonCenter_1F_Text_WonContestsTitle::
	.string "Th{SE_M_REVERSAL}CONTES{SE_M_SWIFT}Master$"

J_MauvilleCity_PokemonCenter_1F_Text_WonContestsAction::
	.string "Wo{SE_M_ATTRACT}CONTESTS$"

J_MauvilleCity_PokemonCenter_1F_Text_WonContestsStory::
	.string "Thi{SE_M_GRASSWHISTLE}i{SE_M_GRASSWHISTLE}{SE_M_CHARGE}tal{SE_M_REVERSAL}o{SE_M_ACID_ARMOR}{SE_M_CHARGE}TRAINER\n"
	.string "name{SE_M_WATERFALL}{STR_VAR_3}.\p"
	.string "Thi{SE_M_GRASSWHISTLE}TRAINE{SE_M_MINIMIZE}wo{SE_M_ATTRACT}CONTESTS\n"
	.string "{STR_VAR_1} times!\p"
	.string "{STR_VAR_3} mus{SE_M_SPIT_UP}b{SE_M_REVERSAL}a{SE_M_ATTRACT}incredible\n"
	.string "CONTES{SE_M_SWIFT}master!$"

J_MauvilleCity_PokemonCenter_1F_Text_TimesShoppedTitle::
	.string "Th{SE_M_REVERSAL}Happ{SE_M_YAWN}Shopper$"

J_MauvilleCity_PokemonCenter_1F_Text_TimesShoppedAction::
	.string "Shopped$"

J_MauvilleCity_PokemonCenter_1F_Text_TimesShoppedStory::
	.string "Thi{SE_M_GRASSWHISTLE}i{SE_M_GRASSWHISTLE}{SE_M_CHARGE}tal{SE_M_REVERSAL}o{SE_M_ACID_ARMOR}{SE_M_CHARGE}TRAINER\n"
	.string "name{SE_M_WATERFALL}{STR_VAR_3}.\p"
	.string "Thi{SE_M_GRASSWHISTLE}TRAINE{SE_M_MINIMIZE}bough{SE_M_SPIT_UP}item{SE_M_GRASSWHISTLE}i{SE_M_ATTRACT}shops\n"
	.string "{STR_VAR_1} times!\p"
	.string "{STR_VAR_3} mus{SE_M_SPIT_UP}b{SE_M_REVERSAL}on{SE_M_REVERSAL}o{SE_M_ACID_ARMOR}those\n"
	.string "peopl{SE_M_REVERSAL}wh{SE_M_ATTRACT2}ar{SE_M_REVERSAL}bor{SE_M_ATTRACT}t{SE_M_ATTRACT2}shop.$"

J_MauvilleCity_PokemonCenter_1F_Text_UsedItemFinderTitle::
	.string "Th{SE_M_REVERSAL}Item-Findin{SE_M_SANDSTORM}TRAINER$"

J_MauvilleCity_PokemonCenter_1F_Text_UsedItemFinderAction::
	.string "Use{SE_M_WATERFALL}a{SE_M_ATTRACT}ITEMFINDER$"

J_MauvilleCity_PokemonCenter_1F_Text_UsedItemFinderStory::
	.string "Thi{SE_M_GRASSWHISTLE}i{SE_M_GRASSWHISTLE}{SE_M_CHARGE}tal{SE_M_REVERSAL}o{SE_M_ACID_ARMOR}{SE_M_CHARGE}TRAINER\n"
	.string "name{SE_M_WATERFALL}{STR_VAR_3}.\p"
	.string "Thi{SE_M_GRASSWHISTLE}TRAINE{SE_M_MINIMIZE}use{SE_M_WATERFALL}a{SE_M_ATTRACT}ITEMFINDER\n"
	.string "{STR_VAR_1} times!\p"
	.string "{STR_VAR_3} mus{SE_M_SPIT_UP}enjo{SE_M_YAWN}scourin{SE_M_SANDSTORM}the\n"
	.string "groun{SE_M_WATERFALL}fo{SE_M_SAND_TOMB}hidde{SE_M_ATTRACT}items!$"

J_MauvilleCity_PokemonCenter_1F_Text_TimesRainedTitle::
	.string "Th{SE_M_REVERSAL}Rain-Soake{SE_M_WATERFALL}TRAINER$"

J_MauvilleCity_PokemonCenter_1F_Text_TimesRainedAction::
	.string "Go{SE_M_SPIT_UP}raine{SE_M_WATERFALL}on$"

J_MauvilleCity_PokemonCenter_1F_Text_TimesRainedStory::
	.string "Thi{SE_M_GRASSWHISTLE}i{SE_M_GRASSWHISTLE}{SE_M_CHARGE}tal{SE_M_REVERSAL}o{SE_M_ACID_ARMOR}{SE_M_CHARGE}TRAINER\n"
	.string "name{SE_M_WATERFALL}{STR_VAR_3}.\p"
	.string "Thi{SE_M_GRASSWHISTLE}TRAINE{SE_M_MINIMIZE}go{SE_M_SPIT_UP}soake{SE_M_WATERFALL}b{SE_M_YAWN}rain\n"
	.string "{STR_VAR_1} times!\p"
	.string "{STR_VAR_3}'{SE_M_GRASSWHISTLE}charism{SE_M_CHARGE}mus{SE_M_SPIT_UP}even\n"
	.string "attrac{SE_M_SPIT_UP}rain!$"

J_MauvilleCity_PokemonCenter_1F_Text_CheckedPokedexTitle::
	.string "Th{SE_M_REVERSAL}Avi{SE_M_WATERFALL}POKéDE{SE_M_LOCK_ON}Reader$"

J_MauvilleCity_PokemonCenter_1F_Text_CheckedPokedexAction::
	.string "Checke{SE_M_WATERFALL}{SE_M_CHARGE}POKéDEX$"

J_MauvilleCity_PokemonCenter_1F_Text_CheckedPokedexStory::
	.string "Thi{SE_M_GRASSWHISTLE}i{SE_M_GRASSWHISTLE}{SE_M_CHARGE}tal{SE_M_REVERSAL}o{SE_M_ACID_ARMOR}{SE_M_CHARGE}TRAINER\n"
	.string "name{SE_M_WATERFALL}{STR_VAR_3}.\p"
	.string "Thi{SE_M_GRASSWHISTLE}TRAINE{SE_M_MINIMIZE}checke{SE_M_WATERFALL}{SE_M_CHARGE}POKéDEX\n"
	.string "{STR_VAR_1} times!\p"
	.string "{STR_VAR_3} mus{SE_M_SPIT_UP}lov{SE_M_REVERSAL}inspecting\n"
	.string "POKéMO{SE_M_PSYBEAM2}i{SE_M_ATTRACT}{SE_M_CHARGE}POKéDEX!$"

J_MauvilleCity_PokemonCenter_1F_Text_ReceivedRibbonsTitle::
	.string "Th{SE_M_REVERSAL}RIBBO{SE_M_PSYBEAM2}Collector$"

J_MauvilleCity_PokemonCenter_1F_Text_ReceivedRibbonsAction::
	.string "Receive{SE_M_WATERFALL}RIBBONS$"

J_MauvilleCity_PokemonCenter_1F_Text_ReceivedRibbonsStory::
	.string "Thi{SE_M_GRASSWHISTLE}i{SE_M_GRASSWHISTLE}{SE_M_CHARGE}tal{SE_M_REVERSAL}o{SE_M_ACID_ARMOR}{SE_M_CHARGE}TRAINER\n"
	.string "name{SE_M_WATERFALL}{STR_VAR_3}.\p"
	.string "Thi{SE_M_GRASSWHISTLE}TRAINE{SE_M_MINIMIZE}receive{SE_M_WATERFALL}RIBBONS\n"
	.string "{STR_VAR_1} times!\p"
	.string "{STR_VAR_3} mus{SE_M_SPIT_UP}b{SE_M_REVERSAL}{SE_M_CHARGE}TRAINE{SE_M_MINIMIZE}who\n"
	.string "love{SE_M_GRASSWHISTLE}t{SE_M_ATTRACT2}collec{SE_M_SPIT_UP}RIBBONS!$"

J_MauvilleCity_PokemonCenter_1F_Text_LedgesJumpedTitle::
	.string "Th{SE_M_REVERSAL}Ledge-Jumpin{SE_M_SANDSTORM}TRAINER$"

J_MauvilleCity_PokemonCenter_1F_Text_LedgesJumpedAction::
	.string "Jumpe{SE_M_WATERFALL}dow{SE_M_ATTRACT}ledges$"

J_MauvilleCity_PokemonCenter_1F_Text_LedgesJumpedStory::
	.string "Thi{SE_M_GRASSWHISTLE}i{SE_M_GRASSWHISTLE}{SE_M_CHARGE}tal{SE_M_REVERSAL}o{SE_M_ACID_ARMOR}{SE_M_CHARGE}TRAINER\n"
	.string "name{SE_M_WATERFALL}{STR_VAR_3}.\p"
	.string "Thi{SE_M_GRASSWHISTLE}TRAINE{SE_M_MINIMIZE}jumpe{SE_M_WATERFALL}dow{SE_M_ATTRACT}ledges\n"
	.string "{STR_VAR_1} times!\p"
	.string "I{SE_M_ACID_ARMOR}there'{SE_M_GRASSWHISTLE}{SE_M_CHARGE}ledg{SE_M_REVERSAL}t{SE_M_ATTRACT2}b{SE_M_REVERSAL}jumped,\n"
	.string "{STR_VAR_3} can'{SE_M_SPIT_UP}ignor{SE_M_REVERSAL}it!$"

J_MauvilleCity_PokemonCenter_1F_Text_TVWatchedTitle::
	.string "Th{SE_M_REVERSAL}Legendar{SE_M_YAWN}T{SE_M_BARRIER}Viewer$"

J_MauvilleCity_PokemonCenter_1F_Text_TVWatchedAction::
	.string "Watche{SE_M_WATERFALL}TV$"

J_MauvilleCity_PokemonCenter_1F_Text_TVWatchedStory::
	.string "Thi{SE_M_GRASSWHISTLE}i{SE_M_GRASSWHISTLE}{SE_M_CHARGE}tal{SE_M_REVERSAL}o{SE_M_ACID_ARMOR}{SE_M_CHARGE}TRAINER\n"
	.string "name{SE_M_WATERFALL}{STR_VAR_3}.\p"
	.string "Thi{SE_M_GRASSWHISTLE}TRAINE{SE_M_MINIMIZE}watche{SE_M_WATERFALL}TV\n"
	.string "{STR_VAR_1} times!\p"
	.string "{STR_VAR_3} mus{SE_M_SPIT_UP}lov{SE_M_REVERSAL}watchin{SE_M_SANDSTORM}TV!$"

J_MauvilleCity_PokemonCenter_1F_Text_CheckedClockTitle::
	.string "Th{SE_M_REVERSAL}Time-Consciou{SE_M_GRASSWHISTLE}TRAINER$"

J_MauvilleCity_PokemonCenter_1F_Text_CheckedClockAction::
	.string "Checke{SE_M_WATERFALL}th{SE_M_REVERSAL}time$"

J_MauvilleCity_PokemonCenter_1F_Text_CheckedClockStory::
	.string "Thi{SE_M_GRASSWHISTLE}i{SE_M_GRASSWHISTLE}{SE_M_CHARGE}tal{SE_M_REVERSAL}o{SE_M_ACID_ARMOR}{SE_M_CHARGE}TRAINER\n"
	.string "name{SE_M_WATERFALL}{STR_VAR_3}.\p"
	.string "Thi{SE_M_GRASSWHISTLE}TRAINE{SE_M_MINIMIZE}checke{SE_M_WATERFALL}th{SE_M_REVERSAL}time\n"
	.string "{STR_VAR_1} times!\p"
	.string "{STR_VAR_3} mus{SE_M_SPIT_UP}b{SE_M_REVERSAL}{SE_M_CHARGE}punctua{SE_M_BATON_PASS}TRAINER\n"
	.string "who'{SE_M_GRASSWHISTLE}consciou{SE_M_GRASSWHISTLE}o{SE_M_ACID_ARMOR}th{SE_M_REVERSAL}time.$"

J_MauvilleCity_PokemonCenter_1F_Text_WonLotteryTitle::
	.string "Th{SE_M_REVERSAL}POKéMO{SE_M_PSYBEAM2}LOTTER{SE_M_MOONLIGHT}Wizard$"

J_MauvilleCity_PokemonCenter_1F_Text_WonLotteryAction::
	.string "Wo{SE_M_ATTRACT}POKéMO{SE_M_PSYBEAM2}LOTTERIES$"

J_MauvilleCity_PokemonCenter_1F_Text_WonLotteryStory::
	.string "Thi{SE_M_GRASSWHISTLE}i{SE_M_GRASSWHISTLE}{SE_M_CHARGE}tal{SE_M_REVERSAL}o{SE_M_ACID_ARMOR}{SE_M_CHARGE}TRAINER\n"
	.string "name{SE_M_WATERFALL}{STR_VAR_3}.\p"
	.string "Thi{SE_M_GRASSWHISTLE}TRAINE{SE_M_MINIMIZE}wo{SE_M_ATTRACT}POKéMO{SE_M_PSYBEAM2}LOTTERIES\n"
	.string "{STR_VAR_1} times!\p"
	.string "{STR_VAR_3} mus{SE_M_SPIT_UP}hav{SE_M_REVERSAL}man{SE_M_YAWN}friends\n"
	.string "t{SE_M_ATTRACT2}trad{SE_M_REVERSAL}POKéMO{SE_M_PSYBEAM2}with!$"

J_MauvilleCity_PokemonCenter_1F_Text_UsedDaycareTitle::
	.string "Th{SE_M_REVERSAL}DA{SE_M_MOONLIGHT}CARE-Usin{SE_M_SANDSTORM}Trainer$"

J_MauvilleCity_PokemonCenter_1F_Text_UsedDaycareAction::
	.string "Lef{SE_M_SPIT_UP}POKéMO{SE_M_PSYBEAM2}a{SE_M_SPIT_UP}th{SE_M_REVERSAL}DA{SE_M_MOONLIGHT}CARE$"

J_MauvilleCity_PokemonCenter_1F_Text_UsedDaycareStory::
	.string "Thi{SE_M_GRASSWHISTLE}i{SE_M_GRASSWHISTLE}{SE_M_CHARGE}tal{SE_M_REVERSAL}o{SE_M_ACID_ARMOR}{SE_M_CHARGE}TRAINER\n"
	.string "name{SE_M_WATERFALL}{STR_VAR_3}.\p"
	.string "Thi{SE_M_GRASSWHISTLE}TRAINE{SE_M_MINIMIZE}lef{SE_M_SPIT_UP}POKéMO{SE_M_PSYBEAM2}wit{SE_M_TRI_ATTACK}the\n"
	.string "DA{SE_M_MOONLIGHT}CAR{SE_M_SWORDS_DANCE}{STR_VAR_1} times!\p"
	.string "{STR_VAR_3} mus{SE_M_SPIT_UP}b{SE_M_REVERSAL}{SE_M_CHARGE}rea{SE_M_BATON_PASS}go-getter\n"
	.string "wh{SE_M_ATTRACT2}raise{SE_M_GRASSWHISTLE}POKéMO{SE_M_PSYBEAM2}aggressively!$"

J_MauvilleCity_PokemonCenter_1F_Text_RodeCableCarTitle::
	.string "Th{SE_M_REVERSAL}CABL{SE_M_SWORDS_DANCE}CAR-Lovin{SE_M_SANDSTORM}TRAINER$"

J_MauvilleCity_PokemonCenter_1F_Text_RodeCableCarAction::
	.string "Rod{SE_M_REVERSAL}th{SE_M_REVERSAL}CABL{SE_M_SWORDS_DANCE}CAR$"

J_MauvilleCity_PokemonCenter_1F_Text_RodeCableCarStory::
	.string "Thi{SE_M_GRASSWHISTLE}i{SE_M_GRASSWHISTLE}{SE_M_CHARGE}tal{SE_M_REVERSAL}o{SE_M_ACID_ARMOR}{SE_M_CHARGE}TRAINER\n"
	.string "name{SE_M_WATERFALL}{STR_VAR_3}.\p"
	.string "Thi{SE_M_GRASSWHISTLE}TRAINE{SE_M_MINIMIZE}rod{SE_M_REVERSAL}th{SE_M_REVERSAL}CABL{SE_M_SWORDS_DANCE}CAR\n"
	.string "{STR_VAR_1} times!\p"
	.string "{STR_VAR_3} mus{SE_M_SPIT_UP}b{SE_M_REVERSAL}{SE_M_CHARGE}bus{SE_M_YAWN}TRAINER\n"
	.string "who'{SE_M_GRASSWHISTLE}u{SE_M_MORNING_SUN}an{SE_M_WATERFALL}dow{SE_M_ATTRACT}al{SE_M_BATON_PASS}th{SE_M_REVERSAL}time!$"

J_MauvilleCity_PokemonCenter_1F_Text_HotSpringsTitle::
	.string "Th{SE_M_REVERSAL}Ho{SE_M_SPIT_UP}Spring-Lovin{SE_M_SANDSTORM}TRAINER$"

J_MauvilleCity_PokemonCenter_1F_Text_HotSpringsAction::
	.string "Bathe{SE_M_WATERFALL}i{SE_M_ATTRACT}ho{SE_M_SPIT_UP}springs$"

J_MauvilleCity_PokemonCenter_1F_Text_HotSpringsStory::
	.string "Thi{SE_M_GRASSWHISTLE}i{SE_M_GRASSWHISTLE}{SE_M_CHARGE}tal{SE_M_REVERSAL}o{SE_M_ACID_ARMOR}{SE_M_CHARGE}TRAINER\n"
	.string "name{SE_M_WATERFALL}{STR_VAR_3}.\p"
	.string "Thi{SE_M_GRASSWHISTLE}TRAINE{SE_M_MINIMIZE}bathe{SE_M_WATERFALL}i{SE_M_ATTRACT}ho{SE_M_SPIT_UP}springs\n"
	.string "{STR_VAR_1} times!\p"
	.string "{STR_VAR_3} mus{SE_M_SPIT_UP}b{SE_M_REVERSAL}{SE_M_CHARGE}TRAINE{SE_M_MINIMIZE}with\n"
	.string "baby-smoot{SE_M_TRI_ATTACK}skin!$"

J_MauvilleCity_PokemonCenter_1F_EventScript_Storyteller::
	lock
	faceplayer
	setvar 32776, 0
	setvar 32777, 0
	setvar 32778, 0
	setvar 32779, 0
	msgbox J_MauvilleCity_PokemonCenter_1F_Text_WillYouHearMyTale, MSGBOX_YESNO
	goto_if_eq 32781, NO, J_MauvilleCity_PokemonCenter_1F_EventScript_DeclineStoryteller
	specialvar 32781, StorytellerGetFreeStorySlot
	goto_if_eq 32781, 0, J_MauvilleCity_PokemonCenter_1F_EventScript_KnowNoTales
	message J_MauvilleCity_PokemonCenter_1F_Text_WhichTaleToTell
	waitmessage
	special StorytellerStoryListMenu
	waitstate
	goto_if_eq 32781, 0, J_MauvilleCity_PokemonCenter_1F_EventScript_CancelStorySelection
	setvar 32776, 1
	special Script_StorytellerDisplayStory
	waitmessage
	waitbuttonpress
	specialvar 32781, StorytellerUpdateStat
	goto_if_eq 32781, 0, J_MauvilleCity_PokemonCenter_1F_EventScript_AreThereOtherTales
	goto J_MauvilleCity_PokemonCenter_1F_EventScript_TellPlayersTale

J_MauvilleCity_PokemonCenter_1F_EventScript_CancelStorySelection::
	goto J_MauvilleCity_PokemonCenter_1F_EventScript_DeclineStoryteller
	end

J_MauvilleCity_PokemonCenter_1F_EventScript_AreThereOtherTales::
	msgbox J_MauvilleCity_PokemonCenter_1F_Text_CouldThereBeOtherLegends, MSGBOX_DEFAULT
	specialvar 32781, HasStorytellerAlreadyRecorded
	goto_if_eq 32781, TRUE, J_MauvilleCity_PokemonCenter_1F_EventScript_StorytellerEnd
	goto J_MauvilleCity_PokemonCenter_1F_EventScript_DoYouHaveAnyTales

J_MauvilleCity_PokemonCenter_1F_EventScript_KnowNoTales::
	msgbox J_MauvilleCity_PokemonCenter_1F_Text_IKnowNoTales, MSGBOX_DEFAULT

J_MauvilleCity_PokemonCenter_1F_EventScript_DoYouHaveAnyTales::
	msgbox J_MauvilleCity_PokemonCenter_1F_Text_HaveYouAnyLegendaryTales, MSGBOX_YESNO
	goto_if_eq 32781, NO, J_MauvilleCity_PokemonCenter_1F_EventScript_DeclineStoryteller
	specialvar 32781, Script_StorytellerInitializeRandomStat
	goto_if_eq 32781, 1, J_MauvilleCity_PokemonCenter_1F_EventScript_TellPlayersTale
	msgbox J_MauvilleCity_PokemonCenter_1F_Text_NotWorthyOfLegend, MSGBOX_DEFAULT
	release
	end

J_MauvilleCity_PokemonCenter_1F_EventScript_TellPlayersTale::
	msgbox J_MauvilleCity_PokemonCenter_1F_Text_YouDidStatXTimes, MSGBOX_DEFAULT
	release
	end

J_MauvilleCity_PokemonCenter_1F_EventScript_DeclineStoryteller::
	msgbox J_MauvilleCity_PokemonCenter_1F_Text_StorytellerFeelingTheBlues, MSGBOX_DEFAULT
	release
	end

J_MauvilleCity_PokemonCenter_1F_EventScript_WaitingForRecordMix::
	msgbox J_MauvilleCity_PokemonCenter_1F_Text_IWishMorePeopleWereInterested, MSGBOX_DEFAULT
	release
	end

J_MauvilleCity_PokemonCenter_1F_EventScript_StorytellerEnd::
	release
	end

J_MauvilleCity_PokemonCenter_1F_Text_HearMyStory:
	.string "I'{SE_M_MILK_DRINK}GIDDY!\n"
	.string "{SE_M_HEAL_BELL}hav{SE_M_REVERSAL}{SE_M_CHARGE}scintillatin{SE_M_SANDSTORM}stor{SE_M_YAWN}fo{SE_M_SAND_TOMB}you!\p"
	.string "Woul{SE_M_WATERFALL}yo{SE_M_DIVE}lik{SE_M_REVERSAL}t{SE_M_ATTRACT2}hea{SE_M_SAND_TOMB}m{SE_M_YAWN}story?$"

J_MauvilleCity_PokemonCenter_1F_Text_GiddyFeelingTheBlues:
	.string "Oh…\n"
	.string "You'v{SE_M_REVERSAL}lef{SE_M_SPIT_UP}m{SE_M_REVERSAL}feelin{SE_M_SANDSTORM}th{SE_M_REVERSAL}blues…$"

J_MauvilleCity_PokemonCenter_1F_Text_AlsoIWasThinking:
	.string "Also{SE_M_SUPERSONIC}{SE_M_HEAL_BELL}wa{SE_M_GRASSWHISTLE}thinking…$"

J_MauvilleCity_PokemonCenter_1F_Text_WeShouldChatAgain:
	.string "That'{SE_M_GRASSWHISTLE}abou{SE_M_SPIT_UP}it{SE_M_SUPERSONIC}{SE_M_HEAL_BELL}think…\p"
	.string "W{SE_M_REVERSAL}shoul{SE_M_WATERFALL}cha{SE_M_SPIT_UP}again!\n"
	.string "Bye-bye!$"

J_MauvilleCity_PokemonCenter_1F_EventScript_Giddy::
	lock
	faceplayer
	msgbox J_MauvilleCity_PokemonCenter_1F_Text_HearMyStory, MSGBOX_YESNO
	goto_if_eq 32781, YES, J_MauvilleCity_PokemonCenter_1F_EventScript_TryTellTale
	goto_if_eq 32781, NO, J_MauvilleCity_PokemonCenter_1F_EventScript_DeclineGiddy
	end

J_MauvilleCity_PokemonCenter_1F_EventScript_TryTellTale::
	special GiddyShouldTellAnotherTale
	goto_if_eq 32781, TRUE, J_MauvilleCity_PokemonCenter_1F_EventScript_GiddyTellTale
	goto_if_eq 32781, FALSE, J_MauvilleCity_PokemonCenter_1F_EventScript_ToldEnoughTales
	end

J_MauvilleCity_PokemonCenter_1F_EventScript_TryTellNewTale::
	special GiddyShouldTellAnotherTale
	goto_if_eq 32781, TRUE, J_MauvilleCity_PokemonCenter_1F_EventScript_GiddyStartNewTale
	goto_if_eq 32781, FALSE, J_MauvilleCity_PokemonCenter_1F_EventScript_ToldEnoughTales
	end

J_MauvilleCity_PokemonCenter_1F_EventScript_GiddyStartNewTale::
	msgbox J_MauvilleCity_PokemonCenter_1F_Text_AlsoIWasThinking, MSGBOX_DEFAULT
	goto J_MauvilleCity_PokemonCenter_1F_EventScript_GiddyTellTale
	end

J_MauvilleCity_PokemonCenter_1F_EventScript_GiddyTellTale::
	special GenerateGiddyLine
	special ShowFieldMessageStringVar4
	waitmessage
	yesnobox 20, 8
	goto_if_eq 32781, YES, J_MauvilleCity_PokemonCenter_1F_EventScript_TryTellNewTale
	goto_if_eq 32781, NO, J_MauvilleCity_PokemonCenter_1F_EventScript_TryTellNewTale
	end

J_MauvilleCity_PokemonCenter_1F_EventScript_DeclineGiddy::
	msgbox J_MauvilleCity_PokemonCenter_1F_Text_GiddyFeelingTheBlues, MSGBOX_DEFAULT
	release
	end

J_MauvilleCity_PokemonCenter_1F_EventScript_ToldEnoughTales::
	msgbox J_MauvilleCity_PokemonCenter_1F_Text_WeShouldChatAgain, MSGBOX_DEFAULT
	release
	end

J_MauvilleCity_PokemonCenter_1F_Text_WouldYouLikeToHearMySong:
	.string "Hi{SE_M_SUPERSONIC}I'{SE_M_MILK_DRINK}th{SE_M_REVERSAL}BARD.\n"
	.string "Woul{SE_M_WATERFALL}yo{SE_M_DIVE}lik{SE_M_REVERSAL}t{SE_M_ATTRACT2}hea{SE_M_SAND_TOMB}m{SE_M_YAWN}song?$"

J_MauvilleCity_PokemonCenter_1F_Text_BardFeelingTheBlues1:
	.string "Oh…\n"
	.string "You'v{SE_M_REVERSAL}lef{SE_M_SPIT_UP}m{SE_M_REVERSAL}feelin{SE_M_SANDSTORM}th{SE_M_REVERSAL}blues…$"

J_MauvilleCity_PokemonCenter_1F_Text_WishICouldPlaySongForOthers:
	.string "Oh{SE_M_SUPERSONIC}wha{SE_M_SPIT_UP}{SE_M_CHARGE}movin{SE_M_SANDSTORM}song…\n"
	.string "{SE_M_HEAL_BELL}wis{SE_M_TRI_ATTACK}{SE_M_HEAL_BELL}coul{SE_M_WATERFALL}pla{SE_M_YAWN}i{SE_M_SPIT_UP}fo{SE_M_SAND_TOMB}others…$"

J_MauvilleCity_PokemonCenter_1F_Text_WouldYouLikeToWriteSomeLyrics:
	.string "So?\n"
	.string "Ho{SE_M_TWISTER}d{SE_M_ATTRACT2}yo{SE_M_DIVE}lik{SE_M_REVERSAL}m{SE_M_YAWN}song?\p"
	.string "Bu{SE_M_SPIT_UP}I'{SE_M_MILK_DRINK}non{SE_M_REVERSAL}to{SE_M_ATTRACT2}happ{SE_M_YAWN}about\n"
	.string "th{SE_M_REVERSAL}lyrics.\p"
	.string "Ho{SE_M_TWISTER}woul{SE_M_WATERFALL}yo{SE_M_DIVE}lik{SE_M_REVERSAL}t{SE_M_ATTRACT2}writ{SE_M_REVERSAL}some\n"
	.string "ne{SE_M_TWISTER}lyric{SE_M_GRASSWHISTLE}fo{SE_M_SAND_TOMB}me?$"

J_MauvilleCity_PokemonCenter_1F_Text_BardFeelingTheBlues2:
	.string "Oh…\n"
	.string "You'v{SE_M_REVERSAL}lef{SE_M_SPIT_UP}m{SE_M_REVERSAL}feelin{SE_M_SANDSTORM}th{SE_M_REVERSAL}blues…$"

J_MauvilleCity_PokemonCenter_1F_Text_LetMeSingItForYou:
	.string "Than{SE_M_ENCORE2}yo{SE_M_DIVE}kindly!\n"
	.string "Le{SE_M_SPIT_UP}m{SE_M_REVERSAL}sin{SE_M_SANDSTORM}i{SE_M_SPIT_UP}fo{SE_M_SAND_TOMB}you.$"

J_MauvilleCity_PokemonCenter_1F_Text_ThatHowYouWantedSongToGo:
	.string "Wa{SE_M_GRASSWHISTLE}tha{SE_M_SPIT_UP}ho{SE_M_TWISTER}yo{SE_M_DIVE}wante{SE_M_WATERFALL}you{SE_M_SAND_TOMB}song\n"
	.string "t{SE_M_ATTRACT2}go?$"

J_MauvilleCity_PokemonCenter_1F_Text_IllSingThisSongForAWhile:
	.string "Okay{SE_M_DRAGON_RAGE}That'{SE_M_GRASSWHISTLE}it{SE_M_SUPERSONIC}then.\n"
	.string "I'l{SE_M_BATON_PASS}sin{SE_M_SANDSTORM}thi{SE_M_GRASSWHISTLE}son{SE_M_SANDSTORM}fo{SE_M_SAND_TOMB}{SE_M_CHARGE}while.$"

J_MauvilleCity_PokemonCenter_1F_Text_TeachWhatsHipAndHappening:
	.string "Hey{SE_M_SUPERSONIC}yo{SE_M_DRAGON_RAGE}The{SE_M_YAWN}cal{SE_M_BATON_PASS}m{SE_M_REVERSAL}th{SE_M_REVERSAL}HIPSTER.\n"
	.string "I'l{SE_M_BATON_PASS}teac{SE_M_TRI_ATTACK}yo{SE_M_DIVE}what'{SE_M_GRASSWHISTLE}hi{SE_M_MORNING_SUN}an{SE_M_WATERFALL}happening.$"

J_MauvilleCity_PokemonCenter_1F_Text_IAlreadyTaughtYou:
	.string "But{SE_M_SUPERSONIC}hey{SE_M_SUPERSONIC}{SE_M_HEAL_BELL}taugh{SE_M_SPIT_UP}yo{SE_M_DIVE}what'{SE_M_GRASSWHISTLE}hi{SE_M_MORNING_SUN}and\n"
	.string "happenin{SE_M_SANDSTORM}already.\p"
	.string "I'{SE_M_WATERFALL}lik{SE_M_REVERSAL}t{SE_M_ATTRACT2}sprea{SE_M_WATERFALL}th{SE_M_REVERSAL}goo{SE_M_WATERFALL}wor{SE_M_WATERFALL}to\n"
	.string "othe{SE_M_SAND_TOMB}folks.$"

J_MauvilleCity_PokemonCenter_1F_Text_IveGotNothingNewToTeach:
	.string "But{SE_M_SUPERSONIC}hey{SE_M_SUPERSONIC}yo{SE_M_DIVE}alread{SE_M_YAWN}kno{SE_M_TWISTER}{SE_M_CHARGE}lo{SE_M_SPIT_UP}about\n"
	.string "what'{SE_M_GRASSWHISTLE}hi{SE_M_MORNING_SUN}an{SE_M_WATERFALL}happening.\p"
	.string "I'v{SE_M_REVERSAL}go{SE_M_SPIT_UP}nothin{SE_M_SANDSTORM}ne{SE_M_TWISTER}t{SE_M_ATTRACT2}teac{SE_M_TRI_ATTACK}you!$"

J_MauvilleCity_PokemonCenter_1F_Text_HaveYouHeardOfWord:
	.string "Hey{SE_M_SUPERSONIC}hav{SE_M_REVERSAL}yo{SE_M_DIVE}hear{SE_M_WATERFALL}about\n"
	.string "“{STR_VAR_1}”?\p"
	.string "What'{SE_M_GRASSWHISTLE}i{SE_M_SPIT_UP}mean{SE_M_SING}Well…\n"
	.string "As{SE_M_ENCORE2}you{SE_M_SAND_TOMB}dadd{SE_M_YAWN}o{SE_M_SAND_TOMB}mommy{SE_M_SUPERSONIC}okay?$"

