@ Johto (data/maps/GoldenrodCity_GameCorner_hns/scripts.inc), as built into the FireRed game.

GoldenrodCity_GameCorner_hns_MapScripts::
	.byte 0

GoldenrodCity_GameCorner_PrizeRoom_EventScript_PrizeClerkMons::
	lock
	faceplayer
	checkitem ITEM_COIN_CASE
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NeedCoinCase
	msgbox J_MauvilleCity_GameCorner_Text_ExchangeCoinsForPrizes, MSGBOX_DEFAULT
	goto GoldenrodCity_GameCorner_PrizeRoom_EventScript_ChoosePrizeMon
	end

GoldenrodCity_GameCorner_PrizeRoom_EventScript_ChoosePrizeMon::

	showcoinsbox 1, 1
	message J_MauvilleCity_GameCorner_Text_WhichPrize
	waitmessage
	multichoice 20, 0, MULTI_PRIZE_MONS, FALSE
	switch VAR_RESULT
	case 0, GoldenrodCity_GameCorner_PrizeRoom_EventScript_Abra
	case 1, GoldenrodCity_GameCorner_PrizeRoom_EventScript_Clefairy
	case 2, GoldenrodCity_GameCorner_PrizeRoom_EventScript_Munchlax
	case 3, GoldenrodCity_GameCorner_PrizeRoom_EventScript_Dratini
	case 4, GoldenrodCity_GameCorner_PrizeRoom_EventScript_Porygon
	case 5, GoldenrodCity_GameCorner_PrizeRoom_EventScript_EndPrizeExchange
	case 127, GoldenrodCity_GameCorner_PrizeRoom_EventScript_EndPrizeExchange
	end

GoldenrodCity_GameCorner_PrizeRoom_EventScript_EndPrizeExchange::
	hidecoinsbox 0, 0

	closemessage
	release
	end

GoldenrodCity_GameCorner_PrizeRoom_EventScript_Abra::
	setvar VAR_TEMP_1, SPECIES_ABRA
	setvar VAR_TEMP_2, 120
	goto GoldenrodCity_GameCorner_PrizeRoom_EventScript_ConfirmPrizeMon
	end

GoldenrodCity_GameCorner_PrizeRoom_EventScript_Clefairy::
	setvar VAR_TEMP_1, SPECIES_CLEFAIRY
	setvar VAR_TEMP_2, 500
	goto GoldenrodCity_GameCorner_PrizeRoom_EventScript_ConfirmPrizeMon
	end

GoldenrodCity_GameCorner_PrizeRoom_EventScript_Munchlax::
	setvar VAR_TEMP_1, SPECIES_MUNCHLAX
	setvar VAR_TEMP_2, 2800
	goto GoldenrodCity_GameCorner_PrizeRoom_EventScript_ConfirmPrizeMon
	end

GoldenrodCity_GameCorner_PrizeRoom_EventScript_Dratini::
	setvar VAR_TEMP_1, SPECIES_DRATINI
	setvar VAR_TEMP_2, 5500
	goto GoldenrodCity_GameCorner_PrizeRoom_EventScript_ConfirmPrizeMon
	end

GoldenrodCity_GameCorner_PrizeRoom_EventScript_Porygon::
	setvar VAR_TEMP_1, SPECIES_PORYGON
	setvar VAR_TEMP_2, 6500
	goto GoldenrodCity_GameCorner_PrizeRoom_EventScript_ConfirmPrizeMon
	end

GoldenrodCity_GameCorner_PrizeRoom_EventScript_ConfirmPrizeMon::
	bufferspeciesname STR_VAR_1, VAR_TEMP_1
	msgbox GoldenrodCity_GameCorner_PrizeRoom_Text_YouWantPrize, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, GoldenrodCity_GameCorner_PrizeRoom_EventScript_EndPrizeExchange
	checkcoins VAR_RESULT
	goto_if_lt VAR_RESULT, VAR_TEMP_2, GoldenrodCity_GameCorner_PrizeRoom_EventScript_NotEnoughCoins
	switch VAR_TEMP_1
	updatecoinsbox 1, 1
	playse SE_SHOP
	case SPECIES_ABRA, GoldenrodCity_GameCorner_PrizeRoom_EventScript_GiveAbra
	case SPECIES_CLEFAIRY, GoldenrodCity_GameCorner_PrizeRoom_EventScript_GiveClefairy
	case SPECIES_DRATINI, GoldenrodCity_GameCorner_PrizeRoom_EventScript_GiveDratini
	case SPECIES_MUNCHLAX, GoldenrodCity_GameCorner_PrizeRoom_EventScript_GiveMunchlax
	case SPECIES_PORYGON, GoldenrodCity_GameCorner_PrizeRoom_EventScript_GivePorygon
	case SPECIES_PINSIR, GoldenrodCity_GameCorner_PrizeRoom_EventScript_GivePinsir
	end

GoldenrodCity_GameCorner_PrizeRoom_EventScript_GiveAbra::
	givemon VAR_TEMP_1, 15
	goto GoldenrodCity_GameCorner_PrizeRoom_EventScript_CheckReceivedMon
	end

GoldenrodCity_GameCorner_PrizeRoom_EventScript_GiveClefairy::
	givemon VAR_TEMP_1, 15
	goto GoldenrodCity_GameCorner_PrizeRoom_EventScript_CheckReceivedMon
	end

GoldenrodCity_GameCorner_PrizeRoom_EventScript_GiveDratini::
	givemon VAR_TEMP_1, 15
	goto GoldenrodCity_GameCorner_PrizeRoom_EventScript_CheckReceivedMon
	end

GoldenrodCity_GameCorner_PrizeRoom_EventScript_GiveMunchlax::
	givemon VAR_TEMP_1, 15
	goto GoldenrodCity_GameCorner_PrizeRoom_EventScript_CheckReceivedMon
	end

GoldenrodCity_GameCorner_PrizeRoom_EventScript_GivePorygon::
	givemon VAR_TEMP_1, 15
	goto GoldenrodCity_GameCorner_PrizeRoom_EventScript_CheckReceivedMon
	end

GoldenrodCity_GameCorner_PrizeRoom_EventScript_GivePinsir::
	givemon VAR_TEMP_1, 15
	goto GoldenrodCity_GameCorner_PrizeRoom_EventScript_CheckReceivedMon
	end

GoldenrodCity_GameCorner_PrizeRoom_EventScript_CheckReceivedMon::
	bufferspeciesname STR_VAR_1, VAR_TEMP_1
	goto_if_eq VAR_RESULT, 0, GoldenrodCity_GameCorner_PrizeRoom_EventScript_ReceivedMonParty
	goto_if_eq VAR_RESULT, 1, GoldenrodCity_GameCorner_PrizeRoom_EventScript_ReceivedMonPC
	goto_if_eq VAR_RESULT, 2, GoldenrodCity_GameCorner_PrizeRoom_EventScript_PartyFull
	end

GoldenrodCity_GameCorner_PrizeRoom_EventScript_PartyFull::
	msgbox J_Route119_WeatherInstitute_2F_Text_NoRoomForPokemon
	hidecoinsbox 0, 0

	closemessage
	release
	end

GoldenrodCity_GameCorner_PrizeRoom_EventScript_NicknamePartyMon::
	getpartysize
	subvar VAR_RESULT, 1
	copyvar VAR_0x8004, VAR_RESULT
	call J_Common_EventScript_GetGiftMonPartySlot
	call J_Common_EventScript_NameReceivedPartyMon
	goto GoldenrodCity_GameCorner_PrizeRoom_EventScript_EndPrizeExchange
	end

GoldenrodCity_GameCorner_PrizeRoom_EventScript_ReceivedMonParty_Nickname_Nuzlocke::
	message GoldenrodGamecorner_Text_GiveNicknameToThisMon
	getpartysize
	subvar VAR_RESULT, 1
	copyvar VAR_0x8004, VAR_RESULT
	call J_Common_EventScript_GetGiftMonPartySlot
	call J_Common_EventScript_NameReceivedPartyMon
	goto GoldenrodCity_GameCorner_PrizeRoom_EventScript_EndPrizeExchange
	end

GoldenrodCity_GameCorner_PrizeRoom_EventScript_NeedCoinCase::
	msgbox GoldenrodCity_GameCorner_Text_PrizeVendorNoCoinCase
	release
	end

GoldenrodCity_GameCorner_PrizeRoom_EventScript_NotEnoughCoins::
	msgbox GoldenrodCity_GameCorner_Text_PrizeVendorNeedMoreCoins
	goto GoldenrodCity_GameCorner_PrizeRoom_EventScript_EndPrizeExchange
	end

GoldenrodCity_GameCorner_PrizeRoom_EventScript_ReceivedMonParty::
	removecoins VAR_TEMP_2
	playse SE_SHOP
	updatecoinsbox 1, 1
	bufferspeciesname STR_VAR_1, VAR_TEMP_1
	playfanfare MUS_LEVEL_UP
	message GoldenrodCity_GameCorner_Text_PlayerObtainedTheMon
	waitmessage
	waitfanfare
	specialvar VAR_RESULT, IsNuzlockeNicknamingActive
	goto_if_eq VAR_RESULT, TRUE, GoldenrodCity_GameCorner_PrizeRoom_EventScript_ReceivedMonParty_Nickname_Nuzlocke
	msgbox GoldenrodGamecorner_Text_GiveNicknameToThisMon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, GoldenrodCity_GameCorner_PrizeRoom_EventScript_NicknamePartyMon
	goto GoldenrodCity_GameCorner_PrizeRoom_EventScript_EndPrizeExchange
	end

GoldenrodCity_GameCorner_PrizeRoom_EventScript_ReceivedMonPC::
	removecoins VAR_TEMP_2
	playse SE_SHOP
	updatecoinsbox 1, 1
	bufferspeciesname STR_VAR_1, VAR_TEMP_1
	playfanfare MUS_LEVEL_UP
	message GoldenrodCity_GameCorner_Text_PlayerObtainedTheMon
	waitmessage
	waitfanfare
	goto GoldenrodCity_GameCorner_PrizeRoom_EventScript_TransferredToPC
	end

GoldenrodCity_GameCorner_PrizeRoom_EventScript_TransferredToPC::
	call J_Common_EventScript_TransferredToPC
	goto GoldenrodCity_GameCorner_PrizeRoom_EventScript_EndPrizeExchange
	end

GoldenrodCity_GameCorner_PrizeRoom_EventScript_PartyMon::
	call J_Common_EventScript_GetGiftMonPartySlot
	call J_Common_EventScript_NameReceivedPartyMon
	end

GoldenrodCity_GameCorner_PrizeRoom_EventScript_PcMon::
	msgbox J_gText_NicknameThisPokemon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, GoldenrodCity_GameCorner_EventScript_SendMon
	call J_Common_EventScript_NameReceivedBoxMon
	goto GoldenrodCity_GameCorner_EventScript_SendMon
	closemessage
	hidecoinsbox 0, 0

	release
	end

GoldenrodCity_GameCorner_EventScript_SendMon::
	call J_Common_EventScript_TransferredToPC
	closemessage
	hidecoinsbox 0, 0

	release
	end

	.set TM_ICE_BEAM_COINS, 4000
	.set TM_FLAMETHROWER_COINS, 4000
	.set TM_THUNDERBOLT_COINS, 4000
	.set TM_REST_COINS, 2000
	.set TM_SWORDS_DANCE_COINS, 3000
	.set TM_SUBSTITUTE_COINS, 2000

GoldenrodCity_GameCorner_PrizeRoom_EventScript_PrizeClerkTMs::
	lock
	faceplayer
	checkitem ITEM_COIN_CASE
	goto_if_eq VAR_RESULT, FALSE, GoldenrodCity_GameCorner_PrizeRoom_EventScript_NeedCoinCase
	msgbox GoldenrodCity_GameCorner_Text_PrizeVendorIntro, MSGBOX_DEFAULT
	goto GoldenrodCity_GameCorner_PrizeRoom_EventScript_ChooseTMPrizeMessage
	end

GoldenrodCity_GameCorner_PrizeRoom_EventScript_ChooseTMPrizeMessage::
	message GoldenrodCity_GameCorner_Text_PrizeVendorWhichPrize
	waitmessage
	setvar VAR_TEMP_1, 0
	showcoinsbox 1, 1
	goto GoldenrodCity_GameCorner_PrizeRoom_EventScript_ChooseTMPrize

GoldenrodCity_GameCorner_PrizeRoom_EventScript_ReturnToChooseTMPrize::
	message GoldenrodCity_GameCorner_Text_PrizeVendorWhichPrize
	waitmessage
	goto GoldenrodCity_GameCorner_PrizeRoom_EventScript_ChooseTMPrize

GoldenrodCity_GameCorner_PrizeRoom_EventScript_ChooseTMPrize::
	dynmultichoice 12, 0, FALSE, 6, 0, DYN_MULTICHOICE_CB_NONE, GoldenrodCity_GameCorner_PrizeRoom_Text_TM44, GoldenrodCity_GameCorner_PrizeRoom_Text_TM90, GoldenrodCity_GameCorner_PrizeRoom_Text_TM75, GoldenrodCity_GameCorner_PrizeRoom_Text_TM13, GoldenrodCity_GameCorner_PrizeRoom_Text_TM24, GoldenrodCity_GameCorner_PrizeRoom_Text_TM35, GoldenrodCity_GameCorner_PrizeRoom_Text_Cancel
	switch VAR_RESULT
	case 0, GoldenrodCity_GameCorner_PrizeRoom_EventScript_TMRest
	case 1, GoldenrodCity_GameCorner_PrizeRoom_EventScript_TMSubstitute
	case 2, GoldenrodCity_GameCorner_PrizeRoom_EventScript_TMSwordsDance
	case 3, GoldenrodCity_GameCorner_PrizeRoom_EventScript_TMIceBeam
	case 4, GoldenrodCity_GameCorner_PrizeRoom_EventScript_TMThunderbolt
	case 5, GoldenrodCity_GameCorner_PrizeRoom_EventScript_TMFlamethrower
	case 6, GoldenrodCity_GameCorner_PrizeRoom_EventScript_CancelTMSelect
	goto GoldenrodCity_GameCorner_PrizeRoom_EventScript_CancelTMSelect
	end

GoldenrodCity_GameCorner_PrizeRoom_EventScript_TMIceBeam::
	setvar VAR_TEMP_1, 1
	bufferitemname STR_VAR_1, ITEM_TM_ICE_BEAM
	setvar VAR_0x8004, ITEM_TM_ICE_BEAM
	goto GoldenrodCity_GameCorner_PrizeRoom_EventScript_ConfirmTMPrize

GoldenrodCity_GameCorner_PrizeRoom_EventScript_TMFlamethrower::
	setvar VAR_TEMP_1, 2
	bufferitemname STR_VAR_1, ITEM_TM_FLAMETHROWER
	setvar VAR_0x8004, ITEM_TM_FLAMETHROWER
	goto GoldenrodCity_GameCorner_PrizeRoom_EventScript_ConfirmTMPrize

GoldenrodCity_GameCorner_PrizeRoom_EventScript_TMThunderbolt::
	setvar VAR_TEMP_1, 6
	bufferitemname STR_VAR_1, ITEM_TM_THUNDERBOLT
	setvar VAR_0x8004, ITEM_TM_THUNDERBOLT
	goto GoldenrodCity_GameCorner_PrizeRoom_EventScript_ConfirmTMPrize

GoldenrodCity_GameCorner_PrizeRoom_EventScript_TMRest::
	setvar VAR_TEMP_1, 3
	bufferitemname STR_VAR_1, ITEM_TM_REST
	setvar VAR_0x8004, ITEM_TM_REST
	goto GoldenrodCity_GameCorner_PrizeRoom_EventScript_ConfirmTMPrize

GoldenrodCity_GameCorner_PrizeRoom_EventScript_TMSwordsDance::
	setvar VAR_TEMP_1, 4
	bufferitemname STR_VAR_1, ITEM_TM75
	setvar VAR_0x8004, ITEM_TM75
	goto GoldenrodCity_GameCorner_PrizeRoom_EventScript_ConfirmTMPrize

GoldenrodCity_GameCorner_PrizeRoom_EventScript_TMSubstitute::
	setvar VAR_TEMP_1, 5
	bufferitemname STR_VAR_1, ITEM_TM90
	setvar VAR_0x8004, ITEM_TM90
	goto GoldenrodCity_GameCorner_PrizeRoom_EventScript_ConfirmTMPrize

GoldenrodCity_GameCorner_PrizeRoom_EventScript_ConfirmTMPrize::
	special BufferTMHMMoveName
	msgbox GoldenrodCity_GameCorner_PrizeRoom_Text_SoYourChoiceIsTM, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, GoldenrodCity_GameCorner_PrizeRoom_EventScript_CancelTMSelect
	goto_if_unset JOHTO_FLAG_FINITE_TMS, GoldenrodCity_GameCorner_PrizeRoom_EventScript_ConfirmTMPrizeInfinite
	switch VAR_TEMP_1
	case 1, GoldenrodCity_GameCorner_PrizeRoom_EventScript_BuyTMIceBeam
	case 2, GoldenrodCity_GameCorner_PrizeRoom_EventScript_BuyTMFlamethrower
	case 3, GoldenrodCity_GameCorner_PrizeRoom_EventScript_BuyTMRest
	case 4, GoldenrodCity_GameCorner_PrizeRoom_EventScript_BuyTMSwordsDance
	case 5, GoldenrodCity_GameCorner_PrizeRoom_EventScript_BuyTMSubstitute
	case 6, GoldenrodCity_GameCorner_PrizeRoom_EventScript_BuyTMThunderbolt
	end

GoldenrodCity_GameCorner_PrizeRoom_EventScript_ConfirmTMPrizeInfinite::
	switch VAR_TEMP_1
	case 1, GoldenrodCity_GameCorner_PrizeRoom_EventScript_BuyTMIceBeamInfinite
	case 2, GoldenrodCity_GameCorner_PrizeRoom_EventScript_BuyTMFlamethrowerInfinite
	case 3, GoldenrodCity_GameCorner_PrizeRoom_EventScript_BuyTMRestInfinite
	case 4, GoldenrodCity_GameCorner_PrizeRoom_EventScript_BuyTMSwordsDanceInfinite
	case 5, GoldenrodCity_GameCorner_PrizeRoom_EventScript_BuyTMSubstituteInfinite
	case 6, GoldenrodCity_GameCorner_PrizeRoom_EventScript_BuyTMThunderboltInfinite
	end

GoldenrodCity_GameCorner_PrizeRoom_EventScript_BuyTMIceBeamInfinite::
	checkcoins VAR_TEMP_2
	goto_if_lt VAR_TEMP_2, TM_ICE_BEAM_COINS, GoldenrodCity_GameCorner_PrizeRoom_EventScript_NotEnoughCoinsForTM
	checkitem ITEM_TM_ICE_BEAM, 1
	goto_if_eq VAR_RESULT, TRUE, GoldenrodCity_GameCorner_PrizeRoom_EventScript_YouAlreadyHaveThis
	removecoins TM_ICE_BEAM_COINS
	additem ITEM_TM_ICE_BEAM
	updatecoinsbox 1, 1
	playse SE_SHOP
	msgbox GoldenrodCity_GameCorner_Text_PrizeVendorHereYouGo, MSGBOX_DEFAULT
	goto GoldenrodCity_GameCorner_PrizeRoom_EventScript_ReturnToChooseTMPrize
	end

GoldenrodCity_GameCorner_PrizeRoom_EventScript_BuyTMFlamethrowerInfinite::
	checkcoins VAR_TEMP_2
	goto_if_lt VAR_TEMP_2, TM_FLAMETHROWER_COINS, GoldenrodCity_GameCorner_PrizeRoom_EventScript_NotEnoughCoinsForTM
	checkitem ITEM_TM_FLAMETHROWER, 1
	goto_if_eq VAR_RESULT, TRUE, GoldenrodCity_GameCorner_PrizeRoom_EventScript_YouAlreadyHaveThis
	removecoins TM_FLAMETHROWER_COINS
	additem ITEM_TM_FLAMETHROWER
	updatecoinsbox 1, 1
	playse SE_SHOP
	msgbox GoldenrodCity_GameCorner_Text_PrizeVendorHereYouGo, MSGBOX_DEFAULT
	goto GoldenrodCity_GameCorner_PrizeRoom_EventScript_ReturnToChooseTMPrize
	end

GoldenrodCity_GameCorner_PrizeRoom_EventScript_BuyTMThunderboltInfinite::
	checkcoins VAR_TEMP_2
	goto_if_lt VAR_TEMP_2, TM_THUNDERBOLT_COINS, GoldenrodCity_GameCorner_PrizeRoom_EventScript_NotEnoughCoinsForTM
	checkitem ITEM_TM_THUNDERBOLT, 1
	goto_if_eq VAR_RESULT, TRUE, GoldenrodCity_GameCorner_PrizeRoom_EventScript_YouAlreadyHaveThis
	removecoins TM_THUNDERBOLT_COINS
	additem ITEM_TM_THUNDERBOLT
	updatecoinsbox 1, 1
	playse SE_SHOP
	msgbox GoldenrodCity_GameCorner_Text_PrizeVendorHereYouGo, MSGBOX_DEFAULT
	goto GoldenrodCity_GameCorner_PrizeRoom_EventScript_ReturnToChooseTMPrize
	end

GoldenrodCity_GameCorner_PrizeRoom_EventScript_BuyTMRestInfinite::
	checkcoins VAR_TEMP_2
	goto_if_lt VAR_TEMP_2, TM_REST_COINS, GoldenrodCity_GameCorner_PrizeRoom_EventScript_NotEnoughCoinsForTM
	checkitem ITEM_TM_REST, 1
	goto_if_eq VAR_RESULT, TRUE, GoldenrodCity_GameCorner_PrizeRoom_EventScript_YouAlreadyHaveThis
	removecoins TM_REST_COINS
	additem ITEM_TM_REST
	updatecoinsbox 1, 1
	playse SE_SHOP
	msgbox GoldenrodCity_GameCorner_Text_PrizeVendorHereYouGo, MSGBOX_DEFAULT
	goto GoldenrodCity_GameCorner_PrizeRoom_EventScript_ReturnToChooseTMPrize
	end

GoldenrodCity_GameCorner_PrizeRoom_EventScript_BuyTMSwordsDanceInfinite::
	checkcoins VAR_TEMP_2
	goto_if_lt VAR_TEMP_2, TM_SWORDS_DANCE_COINS, GoldenrodCity_GameCorner_PrizeRoom_EventScript_NotEnoughCoinsForTM
	checkitem ITEM_TM75, 1
	goto_if_eq VAR_RESULT, TRUE, GoldenrodCity_GameCorner_PrizeRoom_EventScript_YouAlreadyHaveThis
	removecoins TM_SWORDS_DANCE_COINS
	additem ITEM_TM75
	updatecoinsbox 1, 1
	playse SE_SHOP
	msgbox GoldenrodCity_GameCorner_Text_PrizeVendorHereYouGo, MSGBOX_DEFAULT
	goto GoldenrodCity_GameCorner_PrizeRoom_EventScript_ReturnToChooseTMPrize
	end

GoldenrodCity_GameCorner_PrizeRoom_EventScript_BuyTMSubstituteInfinite::
	checkcoins VAR_TEMP_2
	goto_if_lt VAR_TEMP_2, TM_SUBSTITUTE_COINS, GoldenrodCity_GameCorner_PrizeRoom_EventScript_NotEnoughCoinsForTM
	checkitem ITEM_TM90, 1
	goto_if_eq VAR_RESULT, TRUE, GoldenrodCity_GameCorner_PrizeRoom_EventScript_YouAlreadyHaveThis
	removecoins TM_SUBSTITUTE_COINS
	additem ITEM_TM90
	updatecoinsbox 1, 1
	playse SE_SHOP
	msgbox GoldenrodCity_GameCorner_Text_PrizeVendorHereYouGo, MSGBOX_DEFAULT
	goto GoldenrodCity_GameCorner_PrizeRoom_EventScript_ReturnToChooseTMPrize
	end

GoldenrodCity_GameCorner_PrizeRoom_EventScript_BuyTMIceBeam::
	checkcoins VAR_TEMP_2
	goto_if_lt VAR_TEMP_2, TM_ICE_BEAM_COINS, GoldenrodCity_GameCorner_PrizeRoom_EventScript_NotEnoughCoinsForTM
	checkitemspace ITEM_TM_ICE_BEAM
	goto_if_eq VAR_RESULT, FALSE, GoldenrodCity_GameCorner_PrizeRoom_EventScript_NoRoomForTM
	removecoins TM_ICE_BEAM_COINS
	additem ITEM_TM_ICE_BEAM
	updatecoinsbox 1, 1
	playse SE_SHOP
	msgbox GoldenrodCity_GameCorner_Text_PrizeVendorHereYouGo, MSGBOX_DEFAULT
	goto GoldenrodCity_GameCorner_PrizeRoom_EventScript_ReturnToChooseTMPrize
	end

GoldenrodCity_GameCorner_PrizeRoom_EventScript_BuyTMFlamethrower::
	checkcoins VAR_TEMP_2
	goto_if_lt VAR_TEMP_2, TM_FLAMETHROWER_COINS, GoldenrodCity_GameCorner_PrizeRoom_EventScript_NotEnoughCoinsForTM
	checkitemspace ITEM_TM_FLAMETHROWER
	goto_if_eq VAR_RESULT, FALSE, GoldenrodCity_GameCorner_PrizeRoom_EventScript_NoRoomForTM
	removecoins TM_FLAMETHROWER_COINS
	additem ITEM_TM_FLAMETHROWER
	updatecoinsbox 1, 1
	playse SE_SHOP
	msgbox GoldenrodCity_GameCorner_Text_PrizeVendorHereYouGo, MSGBOX_DEFAULT
	goto GoldenrodCity_GameCorner_PrizeRoom_EventScript_ReturnToChooseTMPrize
	end

GoldenrodCity_GameCorner_PrizeRoom_EventScript_BuyTMThunderbolt::
	checkcoins VAR_TEMP_2
	goto_if_lt VAR_TEMP_2, TM_THUNDERBOLT_COINS, GoldenrodCity_GameCorner_PrizeRoom_EventScript_NotEnoughCoinsForTM
	checkitemspace ITEM_TM_THUNDERBOLT
	goto_if_eq VAR_RESULT, FALSE, GoldenrodCity_GameCorner_PrizeRoom_EventScript_NoRoomForTM
	removecoins TM_THUNDERBOLT_COINS
	additem ITEM_TM_THUNDERBOLT
	updatecoinsbox 1, 1
	playse SE_SHOP
	msgbox GoldenrodCity_GameCorner_Text_PrizeVendorHereYouGo, MSGBOX_DEFAULT
	goto GoldenrodCity_GameCorner_PrizeRoom_EventScript_ReturnToChooseTMPrize
	end

GoldenrodCity_GameCorner_PrizeRoom_EventScript_BuyTMRest::
	checkcoins VAR_TEMP_2
	goto_if_lt VAR_TEMP_2, TM_REST_COINS, GoldenrodCity_GameCorner_PrizeRoom_EventScript_NotEnoughCoinsForTM
	checkitemspace ITEM_TM_REST
	goto_if_eq VAR_RESULT, FALSE, GoldenrodCity_GameCorner_PrizeRoom_EventScript_NoRoomForTM
	removecoins TM_REST_COINS
	additem ITEM_TM_REST
	updatecoinsbox 1, 1
	playse SE_SHOP
	msgbox GoldenrodCity_GameCorner_Text_PrizeVendorHereYouGo, MSGBOX_DEFAULT
	goto GoldenrodCity_GameCorner_PrizeRoom_EventScript_ReturnToChooseTMPrize
	end

GoldenrodCity_GameCorner_PrizeRoom_EventScript_BuyTMSwordsDance::
	checkcoins VAR_TEMP_2
	goto_if_lt VAR_TEMP_2, TM_SWORDS_DANCE_COINS, GoldenrodCity_GameCorner_PrizeRoom_EventScript_NotEnoughCoinsForTM
	checkitemspace ITEM_TM75
	goto_if_eq VAR_RESULT, FALSE, GoldenrodCity_GameCorner_PrizeRoom_EventScript_NoRoomForTM
	removecoins TM_SWORDS_DANCE_COINS
	additem ITEM_TM75
	updatecoinsbox 1, 1
	playse SE_SHOP
	msgbox GoldenrodCity_GameCorner_Text_PrizeVendorHereYouGo, MSGBOX_DEFAULT
	goto GoldenrodCity_GameCorner_PrizeRoom_EventScript_ReturnToChooseTMPrize
	end

GoldenrodCity_GameCorner_PrizeRoom_EventScript_BuyTMSubstitute::
	checkcoins VAR_TEMP_2
	goto_if_lt VAR_TEMP_2, TM_SUBSTITUTE_COINS, GoldenrodCity_GameCorner_PrizeRoom_EventScript_NotEnoughCoinsForTM
	checkitemspace ITEM_TM90
	goto_if_eq VAR_RESULT, FALSE, GoldenrodCity_GameCorner_PrizeRoom_EventScript_NoRoomForTM
	removecoins TM_SUBSTITUTE_COINS
	additem ITEM_TM90
	updatecoinsbox 1, 1
	playse SE_SHOP
	msgbox GoldenrodCity_GameCorner_Text_PrizeVendorHereYouGo, MSGBOX_DEFAULT
	goto GoldenrodCity_GameCorner_PrizeRoom_EventScript_ReturnToChooseTMPrize
	end

GoldenrodCity_GameCorner_PrizeRoom_EventScript_NotEnoughCoinsForTM::
	msgbox GoldenrodCity_GameCorner_Text_PrizeVendorNeedMoreCoins, MSGBOX_DEFAULT
	goto GoldenrodCity_GameCorner_PrizeRoom_EventScript_ReturnToChooseTMPrize
	end

GoldenrodCity_GameCorner_PrizeRoom_EventScript_NoRoomForTM::
	call J_Common_EventScript_BagIsFull
	goto GoldenrodCity_GameCorner_PrizeRoom_EventScript_ReturnToChooseTMPrize
	end

GoldenrodCity_GameCorner_PrizeRoom_EventScript_YouAlreadyHaveThis::
	msgbox GoldenrodCity_GameCorner_PrizeRoom_Text_YouAlreadyHaveThis, MSGBOX_DEFAULT
	goto GoldenrodCity_GameCorner_PrizeRoom_EventScript_ReturnToChooseTMPrize
	end

GoldenrodCity_GameCorner_PrizeRoom_EventScript_CancelTMSelect::
	msgbox GoldenrodCity_GameCorner_Text_PrizeVendorQuit, MSGBOX_DEFAULT
	hidecoinsbox 0, 0
	release
	end

GoldenrodCity_GameCorner_PrizeRoom_Text_TM44:
	.string "REST{CLEAR_TO}ク2,00{SE_M_BITE}C.$"

GoldenrodCity_GameCorner_PrizeRoom_Text_TM90:
	.string "SUBSTITUTE{CLEAR_TO}ク2,00{SE_M_BITE}C.$"

GoldenrodCity_GameCorner_PrizeRoom_Text_TM75:
	.string "SWORD{SE_M_SKETCH}DANCE{CLEAR_TO}ク3,00{SE_M_BITE}C.$"

GoldenrodCity_GameCorner_PrizeRoom_Text_TM13:
	.string "IC{SE_M_SWORDS_DANCE}BEAM{CLEAR_TO}ク4,00{SE_M_BITE}C.$"

GoldenrodCity_GameCorner_PrizeRoom_Text_TM24:
	.string "THUNDERBOLT{CLEAR_TO}ク4,00{SE_M_BITE}C.$"

GoldenrodCity_GameCorner_PrizeRoom_Text_TM35:
	.string "FLAMETHROWER{CLEAR_TO}ク4,00{SE_M_BITE}C.$"

GoldenrodCity_GameCorner_PrizeRoom_Text_Cancel:
	.string "EXIT$"

GoldenrodCity_GameCorner_PrizeRoom_Text_SoYourChoiceIsTM:
	.string "S{SE_M_ATTRACT2}you{SE_M_SAND_TOMB}choic{SE_M_REVERSAL}is\n"
	.string "th{SE_M_REVERSAL}{STR_VAR_1} {STR_VAR_2}?$"

GoldenrodCity_GameCorner_PrizeRoom_Text_YouAlreadyHaveThis:
	.string "Yo{SE_M_DIVE}alread{SE_M_YAWN}hav{SE_M_REVERSAL}tha{SE_M_SPIT_UP}item.$"

GoldenrodCity_GameCorner_EventScript_PokefanM::
	lock
	faceplayer
	msgbox GoldenrodCity_GameCorner_Text_PokefanM1, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_GameCorner_EventScript_Hiker::
	lock
	faceplayer
	msgbox GoldenrodCity_GameCorner_Text_MoveTutorInside, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_GameCorner_EventScript_Woman::
	lock
	faceplayer
	msgbox GoldenrodCity_GameCorner_Text_Woman, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_GameCorner_EventScript_Gentleman::
	lock
	faceplayer
	msgbox GoldenrodCity_GameCorner_Text_Gentleman, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_GameCorner_EventScript_PokefanF::
	lock
	faceplayer
	msgbox GoldenrodCity_GameCorner_Text_PokefanF, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_GameCorner_EventScript_PokefanM2::
	lock
	faceplayer
	msgbox GoldenrodCity_GameCorner_Text_PokefanM2, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_GameCorner_EventScript_CooltrainerM::
	lock
	faceplayer
	msgbox GoldenrodCity_GameCorner_Text_CooltrainerM, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_GameCorner_EventScript_Pharmacist::
	lock
	faceplayer
	msgbox GoldenrodCity_GameCorner_Text_Pharmacist, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_GameCorner_PrizeRoom_Text_YouWantPrize:
	.string "{STR_VAR_1} i{SE_M_GRASSWHISTLE}wha{SE_M_SPIT_UP}yo{SE_M_DIVE}want?$"

GoldenrodCity_GameCorner_Text_PlayerObtainedTheMon:
	.string "{PLAYER} go{SE_M_SPIT_UP}{STR_VAR_1}!$"

GoldenrodGamecorner_Text_GiveNicknameToThisMon:
	.string "Nicknam{SE_M_REVERSAL}{STR_VAR_1}?$"

GoldenrodCity_GameCorner_Text_PrizeVendorIntro:
	.string "Welcome!\p"
	.string "W{SE_M_REVERSAL}exchang{SE_M_REVERSAL}you{SE_M_SAND_TOMB}gam{SE_M_REVERSAL}coin{SE_M_GRASSWHISTLE}for\n"
	.string "fabulou{SE_M_GRASSWHISTLE}prizes!$"

GoldenrodCity_GameCorner_Text_PrizeVendorWhichPrize:
	.string "Whic{SE_M_TRI_ATTACK}priz{SE_M_REVERSAL}woul{SE_M_WATERFALL}yo{SE_M_DIVE}like?$"

GoldenrodCity_GameCorner_Text_PrizeVendorHereYouGo:
	.string "Her{SE_M_REVERSAL}yo{SE_M_DIVE}go!$"

GoldenrodCity_GameCorner_Text_PrizeVendorNeedMoreCoins:
	.string "Sorry{SE_M_DRAGON_RAGE}Yo{SE_M_DIVE}nee{SE_M_WATERFALL}mor{SE_M_REVERSAL}coins.$"

GoldenrodCity_GameCorner_Text_PrizeVendorNoMoreRoom:
	.string "Sorry{SE_M_PERISH_SONG}Yo{SE_M_DIVE}can'{SE_M_SPIT_UP}carr{SE_M_YAWN}an{SE_M_YAWN}more.$"

GoldenrodCity_GameCorner_Text_PrizeVendorQuit:
	.string "OK{SE_M_PERISH_SONG}Pleas{SE_M_REVERSAL}sav{SE_M_REVERSAL}you{SE_M_SAND_TOMB}coin{SE_M_GRASSWHISTLE}an{SE_M_WATERFALL}come\n"
	.string "again!$"

GoldenrodCity_GameCorner_Text_PrizeVendorNoCoinCase:
	.string "Oh{SE_M_SING}Yo{SE_M_DIVE}don'{SE_M_SPIT_UP}hav{SE_M_REVERSAL}{SE_M_CHARGE}COI{SE_M_PSYBEAM2}CASE.$"

GoldenrodCity_GameCorner_Text_Pharmacist:
	.string "{SE_M_HEAL_BELL}alway{SE_M_GRASSWHISTLE}pla{SE_M_YAWN}thi{SE_M_GRASSWHISTLE}slo{SE_M_SPIT_UP}machine.\n"
	.string "I{SE_M_SPIT_UP}pay{SE_M_GRASSWHISTLE}ou{SE_M_SPIT_UP}mor{SE_M_REVERSAL}tha{SE_M_ATTRACT}others,\l"
	.string "{SE_M_HEAL_BELL}think.$"

GoldenrodCity_GameCorner_Text_Woman:
	.string "{SE_M_HEAL_BELL}can'{SE_M_SPIT_UP}sto{SE_M_MORNING_SUN}winning!$"

GoldenrodCity_GameCorner_Text_PokefanM1:
	.string "{SE_M_HEAL_BELL}jus{SE_M_SPIT_UP}lov{SE_M_REVERSAL}thi{SE_M_GRASSWHISTLE}ne{SE_M_TWISTER}slo{SE_M_SPIT_UP}machine.\p"
	.string "It'{SE_M_GRASSWHISTLE}mor{SE_M_REVERSAL}o{SE_M_ACID_ARMOR}{SE_M_CHARGE}challeng{SE_M_REVERSAL}tha{SE_M_ATTRACT}the\n"
	.string "one{SE_M_GRASSWHISTLE}i{SE_M_ATTRACT}CELADON.$"

GoldenrodCity_GameCorner_Text_CooltrainerM:
	.string "Lif{SE_M_REVERSAL}i{SE_M_GRASSWHISTLE}{SE_M_CHARGE}gamble{SE_M_PERISH_SONG}I'{SE_M_MILK_DRINK}goin{SE_M_SANDSTORM}t{SE_M_ATTRACT2}pull\n"
	.string "til{SE_M_BATON_PASS}{SE_M_HEAL_BELL}drop!$"

GoldenrodCity_GameCorner_Text_PokefanF:
	.string "Roulette…\p"
	.string "{SE_M_HEAL_BELL}prefe{SE_M_SAND_TOMB}i{SE_M_SPIT_UP}ove{SE_M_SAND_TOMB}th{SE_M_REVERSAL}slot{SE_M_GRASSWHISTLE}because\n"
	.string "it'{SE_M_GRASSWHISTLE}easie{SE_M_SAND_TOMB}t{SE_M_ATTRACT2}figur{SE_M_REVERSAL}th{SE_M_REVERSAL}odds.\p"
	.string "Bu{SE_M_SPIT_UP}th{SE_M_REVERSAL}payou{SE_M_SPIT_UP}i{SE_M_GRASSWHISTLE}muc{SE_M_TRI_ATTACK}lower.$"

GoldenrodCity_GameCorner_Text_CooltrainerF:
	.string "{SE_M_HEAL_BELL}won'{SE_M_SPIT_UP}qui{SE_M_SPIT_UP}unti{SE_M_BATON_PASS}{SE_M_HEAL_BELL}win!$"

GoldenrodCity_GameCorner_Text_Gentleman:
	.string "{SE_M_HEAL_BELL}taugh{SE_M_SPIT_UP}IC{SE_M_SWORDS_DANCE}BEA{SE_M_GIGA_DRAIN}t{SE_M_ATTRACT2}m{SE_M_YAWN}POKéMON.\p"
	.string "I{SE_M_SPIT_UP}wa{SE_M_GRASSWHISTLE}har{SE_M_WATERFALL}t{SE_M_ATTRACT2}ge{SE_M_SPIT_UP}enoug{SE_M_TRI_ATTACK}coin{SE_M_GRASSWHISTLE}for\n"
	.string "it{SE_M_SUPERSONIC}bu{SE_M_SPIT_UP}i{SE_M_SPIT_UP}wa{SE_M_GRASSWHISTLE}wort{SE_M_TRI_ATTACK}it.$"

GoldenrodCity_GameCorner_Text_PokefanM2:
	.string "{SE_M_HEAL_BELL}couldn'{SE_M_SPIT_UP}wi{SE_M_ATTRACT}a{SE_M_SPIT_UP}th{SE_M_REVERSAL}slots{SE_M_SUPERSONIC}an{SE_M_WATERFALL}I\n"
	.string "ble{SE_M_TWISTER}i{SE_M_SPIT_UP}o{SE_M_ATTRACT}roulette.\p"
	.string "{SE_M_HEAL_BELL}go{SE_M_SPIT_UP}s{SE_M_ATTRACT2}furious{SE_M_SUPERSONIC}{SE_M_HEAL_BELL}tosse{SE_M_WATERFALL}ou{SE_M_SPIT_UP}my\n"
	.string "COI{SE_M_PSYBEAM2}CAS{SE_M_SWORDS_DANCE}i{SE_M_ATTRACT}th{SE_M_REVERSAL}UNDERGROUND.$"

GoldenrodCity_GameCorner_Text_MoveTutorInside:
	.string "Wahahah{SE_M_DRAGON_RAGE}Th{SE_M_REVERSAL}coin{SE_M_GRASSWHISTLE}kee{SE_M_MORNING_SUN}rollin{SE_M_SANDSTORM}in!$"

GoldenrodCity_GameCorner_Text_LeftTheirDrink:
	.string "Someon{SE_M_REVERSAL}lef{SE_M_SPIT_UP}thei{SE_M_SAND_TOMB}drink.\p"
	.string "I{SE_M_SPIT_UP}smell{SE_M_GRASSWHISTLE}sweet.$"

GoldenrodCity_GameCorner_EventScript_VoltorbFlip::
	lockall
	checkitem ITEM_COIN_CASE
	goto_if_eq VAR_RESULT, FALSE, GoldenrodCity_GameCorner_EventScript_VF_NoCoinCase
	message GoldenrodCity_GameCorner_Text_VF_Welcome
	waitmessage
	setvar VAR_TEMP_4, 0

GoldenrodCity_GameCorner_EventScript_VF_CheckCoinCap::
	checkcoins VAR_RESULT
	goto_if_lt VAR_RESULT, MAX_COINS, GoldenrodCity_GameCorner_EventScript_VF_ShowMenu
	msgbox GoldenrodCity_GameCorner_Text_VF_CoinCap, MSGBOX_DEFAULT
	setvar VAR_TEMP_4, 0
	setvar VAR_TEMP_7, 0
	hidecoinsbox 0, 5
	releaseall
	end

GoldenrodCity_GameCorner_EventScript_VF_ShowMenu::
	showcoinsbox 1, 1
	copyvar VAR_TEMP_A, VAR_TEMP_4
	addvar VAR_TEMP_A, 1
	buffernumberstring STR_VAR_1, VAR_TEMP_A
	message GoldenrodCity_GameCorner_Text_VF_PlayLevel
	waitmessage
	dynmultichoice 19, 6, FALSE, 3, 0, DYN_MULTICHOICE_CB_NONE, GoldenrodCity_GameCorner_Text_VF_OptPlay, GoldenrodCity_GameCorner_Text_VF_OptGameInfo, GoldenrodCity_GameCorner_Text_VF_OptQuit
	goto_if_eq VAR_RESULT, 0, GoldenrodCity_GameCorner_EventScript_VF_Play
	goto_if_eq VAR_RESULT, 1, GoldenrodCity_GameCorner_EventScript_VF_GameInfo

	setvar VAR_TEMP_4, 0
	setvar VAR_TEMP_7, 0
	closemessage
	hidecoinsbox 0, 5
	releaseall
	end

GoldenrodCity_GameCorner_EventScript_VF_GameInfo::
	message GoldenrodCity_GameCorner_Text_VF_WhichInfo
	waitmessage
	dynmultichoice 19, 4, FALSE, 4, 0, DYN_MULTICHOICE_CB_NONE, GoldenrodCity_GameCorner_Text_VF_OptHowToPlay, GoldenrodCity_GameCorner_Text_VF_OptHint, GoldenrodCity_GameCorner_Text_VF_OptAboutNotes, GoldenrodCity_GameCorner_Text_VF_OptReturn
	goto_if_eq VAR_RESULT, 0, GoldenrodCity_GameCorner_EventScript_VF_HowToPlay
	goto_if_eq VAR_RESULT, 1, GoldenrodCity_GameCorner_EventScript_VF_Hint
	goto_if_eq VAR_RESULT, 2, GoldenrodCity_GameCorner_EventScript_VF_AboutNotes
	goto GoldenrodCity_GameCorner_EventScript_VF_ShowMenu

GoldenrodCity_GameCorner_EventScript_VF_HowToPlay::
	msgbox GoldenrodCity_GameCorner_Text_VF_HowToPlay, MSGBOX_DEFAULT
	goto GoldenrodCity_GameCorner_EventScript_VF_GameInfo

GoldenrodCity_GameCorner_EventScript_VF_Hint::
	msgbox GoldenrodCity_GameCorner_Text_VF_HintText, MSGBOX_DEFAULT
	goto GoldenrodCity_GameCorner_EventScript_VF_GameInfo

GoldenrodCity_GameCorner_EventScript_VF_AboutNotes::
	msgbox GoldenrodCity_GameCorner_Text_VF_AboutNotes, MSGBOX_DEFAULT
	goto GoldenrodCity_GameCorner_EventScript_VF_GameInfo

GoldenrodCity_GameCorner_EventScript_VF_Play::
	closemessage
	copyvar VAR_TEMP_6, VAR_TEMP_4
	setvar VAR_TEMP_5, 0
	hidecoinsbox 0, 5
	special Special_ViewVoltorbFlip
	waitstate
	goto_if_eq VAR_RESULT, 0, GoldenrodCity_GameCorner_EventScript_VF_HandleLoss
	goto_if_eq VAR_RESULT, 1, GoldenrodCity_GameCorner_EventScript_VF_HandleWin
	goto GoldenrodCity_GameCorner_EventScript_VF_HandleQuit
	end

GoldenrodCity_GameCorner_EventScript_VF_HandleWin::
	msgbox GoldenrodCity_GameCorner_Text_VF_GameClear, MSGBOX_DEFAULT
	copyvar VAR_TEMP_1, VAR_TEMP_5
	showcoinsbox 1, 1
	buffernumberstring STR_VAR_1, VAR_TEMP_1
	msgbox GoldenrodCity_GameCorner_Text_VF_ReceivedCoins, MSGBOX_DEFAULT
	addcoins VAR_TEMP_5
	setvar VAR_TEMP_5, 0
	updatecoinsbox 1, 1
	goto_if_le VAR_TEMP_4, VAR_TEMP_6, GoldenrodCity_GameCorner_EventScript_VF_CheckCoinCap
	copyvar VAR_TEMP_A, VAR_TEMP_4
	addvar VAR_TEMP_A, 1
	buffernumberstring STR_VAR_1, VAR_TEMP_A
	msgbox GoldenrodCity_GameCorner_Text_VF_Advanced, MSGBOX_DEFAULT
	goto GoldenrodCity_GameCorner_EventScript_VF_CheckCoinCap

GoldenrodCity_GameCorner_EventScript_VF_HandleLoss::
	msgbox GoldenrodCity_GameCorner_Text_VF_OhNo, MSGBOX_DEFAULT
	goto_if_ge VAR_TEMP_4, VAR_TEMP_6, GoldenrodCity_GameCorner_EventScript_VF_ShowMenu
	copyvar VAR_TEMP_A, VAR_TEMP_4
	addvar VAR_TEMP_A, 1
	buffernumberstring STR_VAR_1, VAR_TEMP_A
	msgbox GoldenrodCity_GameCorner_Text_VF_Dropped, MSGBOX_DEFAULT
	goto GoldenrodCity_GameCorner_EventScript_VF_ShowMenu

GoldenrodCity_GameCorner_EventScript_VF_HandleQuit::
	goto_if_eq VAR_TEMP_5, 0, GoldenrodCity_GameCorner_EventScript_VF_QuitNoCoins
	copyvar VAR_TEMP_1, VAR_TEMP_5
	showcoinsbox 1, 1
	buffernumberstring STR_VAR_1, VAR_TEMP_1
	msgbox GoldenrodCity_GameCorner_Text_VF_ReceivedCoins, MSGBOX_DEFAULT
	addcoins VAR_TEMP_5
	setvar VAR_TEMP_5, 0
	updatecoinsbox 1, 1

GoldenrodCity_GameCorner_EventScript_VF_QuitNoCoins::
	goto_if_ge VAR_TEMP_4, VAR_TEMP_6, GoldenrodCity_GameCorner_EventScript_VF_CheckCoinCap
	copyvar VAR_TEMP_A, VAR_TEMP_4
	addvar VAR_TEMP_A, 1
	buffernumberstring STR_VAR_1, VAR_TEMP_A
	msgbox GoldenrodCity_GameCorner_Text_VF_Dropped, MSGBOX_DEFAULT
	goto GoldenrodCity_GameCorner_EventScript_VF_CheckCoinCap

GoldenrodCity_GameCorner_EventScript_VF_NoCoinCase::
	msgbox GoldenrodCity_GameCorner_Text_VF_NeedCoinCase, MSGBOX_DEFAULT
	releaseall
	end

GoldenrodCity_GameCorner_EventScript_VFAttendant1::
	lock
	faceplayer
	msgbox GoldenrodCity_GameCorner_Text_VFAttendant1, MSGBOX_DEFAULT
	applymovement VAR_LAST_TALKED, J_Common_Movement_FaceDown
	waitmovement 0
	release
	end

GoldenrodCity_GameCorner_EventScript_VFAttendant2::
	lock
	faceplayer
	msgbox GoldenrodCity_GameCorner_Text_VFAttendant2, MSGBOX_DEFAULT
	applymovement VAR_LAST_TALKED, J_Common_Movement_FaceDown
	waitmovement 0
	release
	end

GoldenrodCity_GameCorner_Text_VF_OptPlay:
	.string "PLAY$"

GoldenrodCity_GameCorner_Text_VF_OptGameInfo:
	.string "GAM{SE_M_SWORDS_DANCE}INFO$"

GoldenrodCity_GameCorner_Text_VF_OptQuit:
	.string "QUIT$"

GoldenrodCity_GameCorner_Text_VF_OptHowToPlay:
	.string "HO{SE_M_DETECT}T{SE_M_SOLAR_BEAM}PLAY$"

GoldenrodCity_GameCorner_Text_VF_OptHint:
	.string "HINT$"

GoldenrodCity_GameCorner_Text_VF_OptAboutNotes:
	.string "ABOU{SE_M_SWIFT}NOTES$"

GoldenrodCity_GameCorner_Text_VF_OptReturn:
	.string "RETURN$"

GoldenrodCity_GameCorner_Text_VF_Welcome:
	.string "Welcom{SE_M_REVERSAL}t{SE_M_ATTRACT2}VOLTOR{SE_M_LICK}FLIP!\p$"

GoldenrodCity_GameCorner_Text_VF_PlayLevel:
	.string "Pla{SE_M_YAWN}VOLTOR{SE_M_LICK}Fli{SE_M_MORNING_SUN}Lv{SE_M_PERISH_SONG}{STR_VAR_1}?$"

GoldenrodCity_GameCorner_Text_VF_GameClear:
	.string "Gam{SE_M_REVERSAL}clear!\p"
	.string "You'v{SE_M_REVERSAL}foun{SE_M_WATERFALL}al{SE_M_BATON_PASS}th{SE_M_REVERSAL}hidden\n"
	.string "x{SE_M_SURF}an{SE_M_WATERFALL}x{SE_M_HYDRO_PUMP}cards!$"

GoldenrodCity_GameCorner_Text_VF_ReceivedCoins:
	.string "Yo{SE_M_DIVE}hav{SE_M_REVERSAL}received\n"
	.string "{STR_VAR_1} Coin(s)!$"

GoldenrodCity_GameCorner_Text_VF_Advanced:
	.string "Advance{SE_M_WATERFALL}t{SE_M_ATTRACT2}Gam{SE_M_REVERSAL}Lv{SE_M_PERISH_SONG}{STR_VAR_1}!$"

GoldenrodCity_GameCorner_Text_VF_OhNo:
	.string "O{SE_M_TRI_ATTACK}no{SE_M_DRAGON_RAGE}Yo{SE_M_DIVE}ge{SE_M_SPIT_UP}{SE_M_BITE}Coins!$"

GoldenrodCity_GameCorner_Text_VF_Dropped:
	.string "Droppe{SE_M_WATERFALL}t{SE_M_ATTRACT2}Gam{SE_M_REVERSAL}Lv{SE_M_PERISH_SONG}{STR_VAR_1}.$"

GoldenrodCity_GameCorner_Text_VF_CoinCap:
	.string "You'v{SE_M_REVERSAL}gathere{SE_M_WATERFALL}9,99{SE_M_BIND}COINS.\n"
	.string "Yo{SE_M_DIVE}canno{SE_M_SPIT_UP}gathe{SE_M_SAND_TOMB}an{SE_M_YAWN}more.$"

GoldenrodCity_GameCorner_Text_VF_WhichInfo:
	.string "Whic{SE_M_TRI_ATTACK}se{SE_M_SPIT_UP}o{SE_M_ACID_ARMOR}info?$"

GoldenrodCity_GameCorner_Text_VF_HowToPlay:
	.string "VOLTOR{SE_M_LICK}FLI{SE_M_PETAL_DANCE}i{SE_M_GRASSWHISTLE}{SE_M_CHARGE}gam{SE_M_REVERSAL}i{SE_M_ATTRACT}whic{SE_M_TRI_ATTACK}yo{SE_M_DIVE}flip\n"
	.string "card{SE_M_GRASSWHISTLE}t{SE_M_ATTRACT2}fin{SE_M_WATERFALL}number{SE_M_GRASSWHISTLE}hidde{SE_M_ATTRACT}beneath.\p"
	.string "Th{SE_M_REVERSAL}card{SE_M_GRASSWHISTLE}hid{SE_M_REVERSAL}th{SE_M_REVERSAL}number{SE_M_GRASSWHISTLE}{SE_M_HEADBUTT}throug{SE_M_TRI_ATTACK}3,\n"
	.string "an{SE_M_WATERFALL}VOLTOR{SE_M_LICK}a{SE_M_GRASSWHISTLE}well.\p"
	.string "Th{SE_M_REVERSAL}firs{SE_M_SPIT_UP}numbe{SE_M_SAND_TOMB}yo{SE_M_DIVE}fli{SE_M_MORNING_SUN}gives\n"
	.string "yo{SE_M_DIVE}tha{SE_M_SPIT_UP}man{SE_M_YAWN}Coins.\p"
	.string "Eac{SE_M_TRI_ATTACK}ne{SE_M_TWISTER}numbe{SE_M_SAND_TOMB}multiplie{SE_M_GRASSWHISTLE}you{SE_M_SAND_TOMB}total.\n"
	.string "{SE_M_BONEMERANG}{SE_M_SURF}b{SE_M_YAWN}x{SE_M_SURF}an{SE_M_WATERFALL}{SE_M_CHARGE}{SE_M_HYDRO_PUMP}b{SE_M_YAWN}x3.\p"
	.string "Bu{SE_M_SPIT_UP}i{SE_M_ACID_ARMOR}yo{SE_M_DIVE}fli{SE_M_MORNING_SUN}{SE_M_CHARGE}VOLTORB{SE_M_SUPERSONIC}it'{SE_M_GRASSWHISTLE}gam{SE_M_REVERSAL}over.\n"
	.string "Yo{SE_M_DIVE}los{SE_M_REVERSAL}al{SE_M_BATON_PASS}Coin{SE_M_GRASSWHISTLE}collecte{SE_M_WATERFALL}tha{SE_M_SPIT_UP}round!\p"
	.string "QUI{SE_M_SWIFT}th{SE_M_REVERSAL}gam{SE_M_REVERSAL}a{SE_M_SPIT_UP}an{SE_M_YAWN}tim{SE_M_REVERSAL}t{SE_M_ATTRACT2}keep\n"
	.string "th{SE_M_REVERSAL}Coin{SE_M_GRASSWHISTLE}you'v{SE_M_REVERSAL}foun{SE_M_WATERFALL}s{SE_M_ATTRACT2}far.\p"
	.string "Fin{SE_M_WATERFALL}al{SE_M_BATON_PASS}hidde{SE_M_ATTRACT}x{SE_M_SURF}an{SE_M_WATERFALL}x{SE_M_HYDRO_PUMP}card{SE_M_GRASSWHISTLE}t{SE_M_ATTRACT2}clear\n"
	.string "th{SE_M_REVERSAL}gam{SE_M_REVERSAL}an{SE_M_WATERFALL}advanc{SE_M_REVERSAL}t{SE_M_ATTRACT2}th{SE_M_REVERSAL}nex{SE_M_SPIT_UP}level!$"

GoldenrodCity_GameCorner_Text_VF_HintText:
	.string "Th{SE_M_REVERSAL}number{SE_M_GRASSWHISTLE}o{SE_M_ATTRACT}th{SE_M_REVERSAL}side{SE_M_GRASSWHISTLE}o{SE_M_ACID_ARMOR}th{SE_M_REVERSAL}board\n"
	.string "ar{SE_M_REVERSAL}hint{SE_M_GRASSWHISTLE}abou{SE_M_SPIT_UP}th{SE_M_REVERSAL}numbers…\p"
	.string "hidde{SE_M_ATTRACT}i{SE_M_ATTRACT}tha{SE_M_SPIT_UP}ro{SE_M_TWISTER}o{SE_M_SAND_TOMB}column.\p"
	.string "Th{SE_M_REVERSAL}large{SE_M_SAND_TOMB}th{SE_M_REVERSAL}number{SE_M_SUPERSONIC}th{SE_M_REVERSAL}mor{SE_M_REVERSAL}high-\n"
	.string "valu{SE_M_REVERSAL}card{SE_M_GRASSWHISTLE}ar{SE_M_REVERSAL}i{SE_M_ATTRACT}tha{SE_M_SPIT_UP}ro{SE_M_TWISTER}o{SE_M_SAND_TOMB}column.\p"
	.string "Th{SE_M_REVERSAL}VOLTOR{SE_M_LICK}coun{SE_M_SPIT_UP}tell{SE_M_GRASSWHISTLE}yo{SE_M_DIVE}how\n"
	.string "man{SE_M_YAWN}VOLTORB{SE_M_GRASSWHISTLE}lur{SE_M_ENCORE2}there.\p"
	.string "Us{SE_M_REVERSAL}bot{SE_M_TRI_ATTACK}total{SE_M_GRASSWHISTLE}t{SE_M_ATTRACT2}figur{SE_M_REVERSAL}out\n"
	.string "whic{SE_M_TRI_ATTACK}card{SE_M_GRASSWHISTLE}ar{SE_M_REVERSAL}saf{SE_M_REVERSAL}t{SE_M_ATTRACT2}flip!$"

GoldenrodCity_GameCorner_Text_VF_AboutNotes:
	.string "Us{SE_M_REVERSAL}th{SE_M_REVERSAL}note{SE_M_GRASSWHISTLE}mod{SE_M_REVERSAL}({L_BUTTON} {SE_WARP_IN}{R_BUTTON}{SE_ROULETTE_BALL2}t{SE_M_ATTRACT2}mark\n"
	.string "card{SE_M_GRASSWHISTLE}wit{SE_M_TRI_ATTACK}number{SE_M_GRASSWHISTLE}1-{SE_M_HYDRO_PUMP}o{SE_M_SAND_TOMB}{SE_M_CHARGE}VOLTORB.\p"
	.string "Mar{SE_M_ENCORE2}{SE_M_CHARGE}car{SE_M_WATERFALL}yo{SE_M_DIVE}thin{SE_M_ENCORE2}yo{SE_M_DIVE}know,\n"
	.string "the{SE_M_ATTRACT}fli{SE_M_MORNING_SUN}i{SE_M_SPIT_UP}whe{SE_M_ATTRACT}you'r{SE_M_REVERSAL}sure.\p"
	.string "Appl{SE_M_YAWN}{SE_M_CHARGE}not{SE_M_REVERSAL}agai{SE_M_ATTRACT}t{SE_M_ATTRACT2}remov{SE_M_REVERSAL}it.$"

GoldenrodCity_GameCorner_Text_VF_NeedCoinCase:
	.string "Oh{SE_M_SING}Yo{SE_M_DIVE}don'{SE_M_SPIT_UP}hav{SE_M_REVERSAL}{SE_M_CHARGE}COI{SE_M_PSYBEAM2}CASE.$"

GoldenrodCity_GameCorner_Text_VFAttendant1:
	.string "Yo{SE_M_DIVE}wan{SE_M_SPIT_UP}t{SE_M_ATTRACT2}pla{SE_M_YAWN}VOLTOR{SE_M_LICK}FLIP?\p"
	.string "Yo{SE_M_DIVE}nee{SE_M_WATERFALL}t{SE_M_ATTRACT2}b{SE_M_REVERSAL}o{SE_M_ATTRACT}th{SE_M_REVERSAL}other\n"
	.string "sid{SE_M_REVERSAL}o{SE_M_ACID_ARMOR}th{SE_M_REVERSAL}table.$"

GoldenrodCity_GameCorner_Text_VFAttendant2:
	.string "Tr{SE_M_YAWN}th{SE_M_REVERSAL}othe{SE_M_SAND_TOMB}sid{SE_M_REVERSAL}of\n"
	.string "th{SE_M_REVERSAL}table{SE_M_SUPERSONIC}pal.$"

