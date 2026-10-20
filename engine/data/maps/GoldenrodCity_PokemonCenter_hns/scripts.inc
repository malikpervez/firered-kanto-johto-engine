@ Johto (data/maps/GoldenrodCity_PokemonCenter_hns/scripts.inc), as built into the FireRed game.

GoldenrodCity_PokemonCenter_hns_MapScripts::
	map_script 2, GoldenrodCity_PokemonCenter_hns_OnFrame
	map_script 4, GoldenrodCity_PokemonCenter_hns_OnWarp
	map_script 3, GoldenrodCity_PokemonCenter_OnTransition
	.byte 0

GoldenrodCity_PokemonCenter_OnTransition::
	setrespawn 132
	call CG_SilverGoldenrodVisibility
	end

GoldenrodCity_PokemonCenter_hns_OnWarp:
	map_script_2 20599, 3, GoldenrodCity_PokemonCenter_hns_OnWarp_Nop
	map_script_2 20599, 1, GoldenrodCity_PokemonCenter_hns_OnWarp_Nop
	map_script_2 20599, 2, GoldenrodCity_PokemonCenter_hns_OnWarp_Nop
	.2byte 0

GoldenrodCity_PokemonCenter_hns_OnWarp_Nop::
	end

GoldenrodCity_PokemonCenter_hns_OnFrame:
	map_script_2 20599, 3, GoldenrodCity_PokemonCenter_hns_ExitLinkRoom
	map_script_2 20599, 1, GoldenrodCity_PokemonCenter_hns_ExitLinkRoom
	map_script_2 20599, 2, GoldenrodCity_PokemonCenter_hns_ExitLinkRoom
	.2byte 0

GoldenrodCity_PokemonCenter_hns_ExitLinkRoom::
	lockall
	special CloseLink
	setvar 20599, 0
	erasebox 0, 0, 29, 19
	releaseall
	end

GoldenrodCity_PokemonCenter_EventScript_LinkNpc::
	lock
	faceplayer
	copyvar 32775, 32783
	msgbox GoldenrodCity_PokemonCenter_LinkNpc_Text_Intro, MSGBOX_DEFAULT
	multichoice 0, 0, 174, FALSE
	switch 32781
	case 0, GoldenrodCity_PokemonCenter_EventScript_ChooseTrade
	case 1, GoldenrodCity_PokemonCenter_EventScript_ChooseBattle
	case 2, GoldenrodCity_PokemonCenter_EventScript_LinkNpc_Decline
	case 127, GoldenrodCity_PokemonCenter_EventScript_LinkNpc_Decline
	end

GoldenrodCity_PokemonCenter_EventScript_ChooseTrade::
	helpwindow HELP_TRADE_WINDOW
	delay 30
	call J_CableClub_EventScript_CheckPartyTradeRequirements
	goto_if_eq 32781, 0, GoldenrodCity_PokemonCenter_EventScript_LinkNpc_End
	call J_Common_EventScript_SaveGame
	goto_if_eq 32781, 0, GoldenrodCity_PokemonCenter_EventScript_LinkNpc_End
	message J_gText_PleaseWaitForLink
	waitmessage
	special TryTradeLinkup
	waitstate
	goto_if_eq 32781, 1, GoldenrodCity_PokemonCenter_EventScript_EnterTradeRoom
	goto_if_eq 32781, 2, J_CableClub_EventScript_AbortLinkSomeoneNotReady
	goto_if_eq 32781, 3, J_CableClub_EventScript_AbortLinkDifferentSelections
	goto_if_eq 32781, 4, J_CableClub_EventScript_AbortLinkIncorrectNumberOfParticipants
	goto_if_eq 32781, 5, J_CableClub_EventScript_AbortLink
	goto_if_eq 32781, 6, J_CableClub_EventScript_AbortLinkConnectionError
	goto_if_eq 32781, 7, J_CableClub_EventScript_AbortLinkPlayerNotReady
	goto_if_eq 32781, 9, J_CableClub_EventScript_AbortLinkOtherTrainerNotReady
	end

GoldenrodCity_PokemonCenter_EventScript_EnterTradeRoom::
	setvar 20599, 3
	closemessage
	release
	setdynamicwarp MAP_GOLDENROD_CITY_POKEMON_CENTER_HNS, 255, 14, 6
	setwarp MAP_TRADE_CENTER_HNS, 5, 8
	special DoCableClubWarp
	waitstate
	end

GoldenrodCity_PokemonCenter_EventScript_ChooseBattle::
	helpwindow HELP_TRADE_WINDOW
	msgbox GoldenrodCity_PokemonCenter_LinkNpc_Text_BattleMode, MSGBOX_DEFAULT
	multichoice 0, 0, 175, FALSE
	switch 32781
	case 0, GoldenrodCity_PokemonCenter_EventScript_SingleBattle
	case 1, GoldenrodCity_PokemonCenter_EventScript_DoubleBattle
	case 2, GoldenrodCity_PokemonCenter_EventScript_LinkNpc_Decline
	case 127, GoldenrodCity_PokemonCenter_EventScript_LinkNpc_Decline
	end

GoldenrodCity_PokemonCenter_EventScript_SingleBattle::
	setvar 32772, 1
	goto GoldenrodCity_PokemonCenter_EventScript_TryEnterColosseum
	end

GoldenrodCity_PokemonCenter_EventScript_DoubleBattle::
	special HasEnoughMonsForDoubleBattle
	goto_if_ne 32781, 0, GoldenrodCity_PokemonCenter_EventScript_NeedTwoMons
	setvar 32772, 2
	goto GoldenrodCity_PokemonCenter_EventScript_TryEnterColosseum
	end

GoldenrodCity_PokemonCenter_EventScript_NeedTwoMons::
	msgbox J_CableClub_Text_NeedTwoMonsForDoubleBattle, MSGBOX_DEFAULT
	goto GoldenrodCity_PokemonCenter_EventScript_ChooseBattle
	end

GoldenrodCity_PokemonCenter_EventScript_TryEnterColosseum::
	call J_Common_EventScript_SaveGame
	goto_if_eq 32781, 0, GoldenrodCity_PokemonCenter_EventScript_LinkNpc_End
	message J_gText_PleaseWaitForLink
	waitmessage
	special TryBattleLinkup
	waitstate
	goto_if_eq 32781, 1, GoldenrodCity_PokemonCenter_EventScript_EnterColosseum
	goto_if_eq 32781, 2, J_CableClub_EventScript_AbortLinkSomeoneNotReady
	goto_if_eq 32781, 3, J_CableClub_EventScript_AbortLinkDifferentSelections
	goto_if_eq 32781, 4, J_CableClub_EventScript_AbortLinkIncorrectNumberOfBattlers
	goto_if_eq 32781, 5, J_CableClub_EventScript_AbortLink
	goto_if_eq 32781, 6, J_CableClub_EventScript_AbortLinkConnectionError
	end

GoldenrodCity_PokemonCenter_EventScript_EnterColosseum::
	special HealPlayerParty
	special SavePlayerParty
	special LoadPlayerBag
	copyvar 20599, 32772
	closemessage
	release
	setdynamicwarp MAP_GOLDENROD_CITY_POKEMON_CENTER_HNS, 255, 14, 6
	setwarp MAP_BATTLE_COLOSSEUM_2P_HNS, 6, 8
	special DoCableClubWarp
	waitstate
	end

GoldenrodCity_PokemonCenter_EventScript_LinkNpc_Decline::
	msgbox GoldenrodCity_PokemonCenter_LinkNpc_Text_Goodbye, MSGBOX_NPC
	end

GoldenrodCity_PokemonCenter_EventScript_LinkNpc_End::
	release
	end

GoldenrodCity_PokemonCenter_LinkNpc_Text_Intro:
	.string "LIN{SE_M_SNORE}CORNER\p"
	.string "SELEC{SE_M_SWIFT}LIN{SE_M_SNORE}TYPE.$"

GoldenrodCity_PokemonCenter_LinkNpc_Text_BattleMode:
	.string "SELEC{SE_M_SWIFT}BATTL{SE_M_SWORDS_DANCE}TYPE.$"

GoldenrodCity_PokemonCenter_LinkNpc_Text_Goodbye:
	.string "GOODBYE.$"

GoldenrodCity_PokemonCenter_EventScript_LinkExplainerNpc::
	msgbox GoldenrodCity_PokemonCenter_Text_LinkExplainer, MSGBOX_NPC
	end

GoldenrodCity_PokemonCenter_Text_LinkExplainer:
	.string "Yo{SE_M_DIVE}ca{SE_M_ATTRACT}us{SE_M_REVERSAL}thi{SE_M_GRASSWHISTLE}machin{SE_M_REVERSAL}t{SE_M_ATTRACT2}trade\n"
	.string "o{SE_M_SAND_TOMB}battl{SE_M_REVERSAL}wit{SE_M_TRI_ATTACK}othe{SE_M_SAND_TOMB}loca{SE_M_BATON_PASS}players.\p"
	.string "Isn'{SE_M_SPIT_UP}technolog{SE_M_YAWN}wonderful?$"

GoldenrodCity_PokemonCenter_EventScript_GbaKid1::
	lock
	faceplayer
	msgbox GoldenrodCity_PokemonCenter_GameboyKidText1, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_PokemonCenter_EventScript_GbaKid2::
	lock
	faceplayer
	msgbox GoldenrodCity_PokemonCenter_GameboyKidText2, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_PokemonCenter_EventScript_Granny::
	lock
	faceplayer
	msgbox GoldenrodCity_PokemonCenter_GrannyText, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_PokemonCenter_EventScript_Lass::
	lock
	faceplayer
	msgbox GoldenrodCity_PokemonCenter_LassText, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_PokemonCenter_GrannyText:
	.string "{SE_M_HEAL_BELL}jus{SE_M_SPIT_UP}lov{SE_M_REVERSAL}livin{SE_M_SANDSTORM}i{SE_M_ATTRACT}th{SE_M_REVERSAL}bi{SE_M_SANDSTORM}city!\n"
	.string "{SE_M_HEAL_BELL}move{SE_M_WATERFALL}her{SE_M_REVERSAL}whe{SE_M_ATTRACT}{SE_M_HEAL_BELL}wa{SE_M_GRASSWHISTLE}{SE_M_CHARGE}young\l"
	.string "trainer{SE_M_SUPERSONIC}lik{SE_M_REVERSAL}you!$"

GoldenrodCity_PokemonCenter_GameboyKidText1:
	.string "Thi{SE_M_GRASSWHISTLE}i{SE_M_GRASSWHISTLE}{SE_M_CHARGE}specia{SE_M_BATON_PASS}POKéMO{SE_M_PSYBEAM2}CENTER.\n"
	.string "Th{SE_M_REVERSAL}roo{SE_M_ACID_ARMOR}i{SE_M_GRASSWHISTLE}mad{SE_M_REVERSAL}o{SE_M_ACID_ARMOR}gold!$"

GoldenrodCity_PokemonCenter_GameboyKidText2:
	.string "{SE_M_HEAL_BELL}tol{SE_M_WATERFALL}m{SE_M_YAWN}brothe{SE_M_SAND_TOMB}tha{SE_M_SPIT_UP}th{SE_M_REVERSAL}roo{SE_M_ACID_ARMOR}is\n"
	.string "mad{SE_M_REVERSAL}o{SE_M_ACID_ARMOR}rea{SE_M_BATON_PASS}gold{SE_M_PERISH_SONG}He'l{SE_M_BATON_PASS}believe\l"
	.string "anything!$"

GoldenrodCity_PokemonCenter_LassText:
	.string "{SE_M_BONEMERANG}highe{SE_M_SAND_TOMB}leve{SE_M_BATON_PASS}POKéMO{SE_M_PSYBEAM2}doesn't\n"
	.string "alway{SE_M_GRASSWHISTLE}win.\p"
	.string "Afte{SE_M_SAND_TOMB}all{SE_M_SUPERSONIC}i{SE_M_SPIT_UP}ma{SE_M_YAWN}hav{SE_M_REVERSAL}{SE_M_CHARGE}type\n"
	.string "disadvantage.\p"
	.string "{SE_M_HEAL_BELL}don'{SE_M_SPIT_UP}thin{SE_M_ENCORE2}ther{SE_M_REVERSAL}i{SE_M_GRASSWHISTLE}{SE_M_CHARGE}single\n"
	.string "POKéMO{SE_M_PSYBEAM2}tha{SE_M_SPIT_UP}i{SE_M_GRASSWHISTLE}th{SE_M_REVERSAL}toughest.$"

GoldenrodPokeCenter_LinkReceptionistPleaseAcceptGSBallText:
	.string "{PLAYER}{SE_M_SUPERSONIC}isn'{SE_M_SPIT_UP}it?\p"
	.string "Congratulations!\p"
	.string "A{SE_M_GRASSWHISTLE}{SE_M_CHARGE}specia{SE_M_BATON_PASS}deal{SE_M_SUPERSONIC}{SE_M_CHARGE}G{SE_M_SKETCH}BAL{SE_M_BRICK_BREAK}has\n"
	.string "bee{SE_M_ATTRACT}sen{SE_M_SPIT_UP}jus{SE_M_SPIT_UP}fo{SE_M_SAND_TOMB}you!\p"
	.string "Pleas{SE_M_REVERSAL}accep{SE_M_SPIT_UP}it!$"

GoldenrodPokeCenter_LinkReceptionistPleaseDoComeAgainText:
	.string "Pleas{SE_M_REVERSAL}d{SE_M_ATTRACT2}com{SE_M_REVERSAL}again!$"

GoldenrodCity_PokemonCenter_PokefanFDoYouHaveEonMailText:
	.string "O{SE_M_TRI_ATTACK}my{SE_M_SUPERSONIC}you{SE_M_SAND_TOMB}pac{SE_M_ENCORE2}look{SE_M_GRASSWHISTLE}s{SE_M_ATTRACT2}heavy!\p"
	.string "Oh{SE_M_DRAGON_RAGE}D{SE_M_ATTRACT2}yo{SE_M_DIVE}happe{SE_M_ATTRACT}t{SE_M_ATTRACT2}have\n"
	.string "somethin{SE_M_SANDSTORM}name{SE_M_WATERFALL}EO{SE_M_PSYBEAM2}MAIL?\p"
	.string "M{SE_M_YAWN}daughte{SE_M_SAND_TOMB}i{SE_M_GRASSWHISTLE}afte{SE_M_SAND_TOMB}one.\p"
	.string "Yo{SE_M_DIVE}ca{SE_M_ATTRACT}par{SE_M_SPIT_UP}wit{SE_M_TRI_ATTACK}one{SE_M_SUPERSONIC}can'{SE_M_SPIT_UP}you?$"

GoldenrodCity_PokemonCenter_AskGiveAwayAnEonMailText:
	.string "Giv{SE_M_REVERSAL}awa{SE_M_YAWN}a{SE_M_ATTRACT}EO{SE_M_PSYBEAM2}MAIL?$"

GoldenrodCity_PokemonCenter_PokefanFThisIsForYouText:
	.string "Oh{SE_M_SUPERSONIC}that'{SE_M_GRASSWHISTLE}great{SE_M_DRAGON_RAGE}Than{SE_M_ENCORE2}you,\n"
	.string "honey!\p"
	.string "Here{SE_M_SUPERSONIC}thi{SE_M_GRASSWHISTLE}i{SE_M_GRASSWHISTLE}fo{SE_M_SAND_TOMB}yo{SE_M_DIVE}i{SE_M_ATTRACT}return!$"

GoldenrodCity_PokemonCenter_PokefanFDaughterWillBeDelightedText:
	.string "M{SE_M_YAWN}daughte{SE_M_SAND_TOMB}wil{SE_M_BATON_PASS}b{SE_M_REVERSAL}delighted!$"

GoldenrodCity_PokemonCenter_PokefanFTooBadText:
	.string "Oh{SE_M_SING}Yo{SE_M_DIVE}don'{SE_M_SPIT_UP}hav{SE_M_REVERSAL}one{SE_M_SING}To{SE_M_ATTRACT2}bad.$"

GoldenrodCity_PokemonCenter_PokefanFAnotherTimeThenText:
	.string "Oh{SE_M_DIZZY_PUNCH}Well{SE_M_SUPERSONIC}anothe{SE_M_SAND_TOMB}time{SE_M_SUPERSONIC}then.$"

GoldenrodCity_PokemonCenter_PlayerGaveAwayTheEonMailText:
	.string "{PLAYER} gav{SE_M_REVERSAL}awa{SE_M_YAWN}th{SE_M_REVERSAL}EO{SE_M_PSYBEAM2}MAIL.$"

