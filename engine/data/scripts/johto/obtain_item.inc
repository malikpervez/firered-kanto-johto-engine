@ Johto (data/scripts/obtain_item.inc), as built into the FireRed game.

J_Std_ObtainItem::

	callnative ObtainItemRandomize_NativeCall

	copyvar VAR_0x8006, ITEMID
	additem ITEMID, AMOUNT
	copyvar VAR_0x8007, VAR_RESULT
	call J_EventScript_ObtainItemMessage
	return

J_EventScript_ObtainItemMessage::
	bufferitemnameplural STR_VAR_2, ITEMID, AMOUNT
	checkitemtype ITEMID
	call J_EventScript_BufferPocketNameAndTryFanfare
	call_if_eq VAR_0x8007, TRUE, J_EventScript_ObtainedItem
	call_if_eq VAR_0x8007, FALSE, J_EventScript_NoRoomForItem
	return

J_EventScript_BufferPocketNameAndTryFanfare::
	switch VAR_RESULT
	case POCKET_MEDICINE J_EventScript_BufferMedicinePocket,
	case POCKET_POKE_BALLS J_EventScript_BufferPokeballsPocket,
	case POCKET_BERRIES J_EventScript_BufferBerriesPocket,
	case POCKET_ITEMS J_EventScript_BufferItemsPocket,
	case POCKET_TM_HM J_EventScript_BufferTMHMsPocket,
	case POCKET_KEY_ITEMS J_EventScript_BufferKeyItemsPocket,

	case POCKET_ITEMS J_EventScript_BufferTreasuresPocket,
	case POCKET_MEDICINE J_EventScript_BufferBattleItemsPocket,

	end

J_EventScript_BufferItemsPocket::
	bufferstdstring STR_VAR_3, STDSTRING_ITEMS
	call_if_eq VAR_0x8007, TRUE, J_EventScript_PlayFanfareObtainedItem
	return

J_EventScript_BufferKeyItemsPocket::
	bufferstdstring STR_VAR_3, STDSTRING_KEYITEMS
	call_if_eq VAR_0x8007, TRUE, J_EventScript_PlayFanfareObtainedKeyItem
	return

J_EventScript_BufferPokeballsPocket::
	bufferstdstring STR_VAR_3, STDSTRING_POKEBALLS
	call_if_eq VAR_0x8007, TRUE, J_EventScript_PlayFanfareObtainedItem
	return

J_EventScript_BufferTMHMsPocket::
	bufferstdstring STR_VAR_3, STDSTRING_TMHMS
	call_if_eq VAR_0x8007, TRUE, J_EventScript_PlayFanfareObtainedTMHM
	return

J_EventScript_BufferBerriesPocket::
	bufferstdstring STR_VAR_3, STDSTRING_BERRIES
	call_if_eq VAR_0x8007, TRUE, J_EventScript_PlayFanfareObtainedBerry
	return

J_EventScript_BufferMedicinePocket::
	bufferstdstring STR_VAR_3, STDSTRING_MEDICINE
	call_if_eq VAR_0x8007, TRUE, J_EventScript_PlayFanfareObtainedItem
	return

J_EventScript_BufferBattleItemsPocket::
	bufferstdstring STR_VAR_3, STDSTRING_BATTLE_ITEMS
	call_if_eq VAR_0x8007, TRUE, J_EventScript_PlayFanfareObtainedItem
	return

J_EventScript_BufferTreasuresPocket::
	bufferstdstring STR_VAR_3, STDSTRING_TREASURES
	call_if_eq VAR_0x8007, TRUE, J_EventScript_PlayFanfareObtainedItem
	return

J_EventScript_ObtainedItem::
	compare VAR_0x8001, TRUE
	goto_if_eq J_EventScript_ObtainedItemMessage
	buffernumberstring 0, VAR_0x8001
	message J_gText_ObtainedTheItems
	goto J_EventScript_ContinueObtainedItem

J_EventScript_ObtainedItemMessage:
	message J_gText_ObtainedTheItem

J_EventScript_ContinueObtainedItem:
	delay 10
	showitemdescription
	waitfanfare
	msgbox J_gText_PutItemInPocket, MSGBOX_DEFAULT
	hideitemdescription
	setvar VAR_RESULT, TRUE
	return

J_EventScript_NoRoomForItem::
	setvar VAR_RESULT, FALSE
	return

J_EventScript_PlayFanfareObtainedItem::
	playfanfare MUS_OBTAIN_ITEM
	return

J_EventScript_PlayFanfareObtainedKeyItem::



	playfanfare MUS_RG_OBTAIN_KEY_ITEM



	return

J_EventScript_PlayFanfareObtainedTMHM::
	playfanfare MUS_OBTAIN_TMHM
	return

J_EventScript_PlayFanfareObtainedBerry::


	playfanfare MUS_OBTAIN_BERRY



	return

J_Std_ObtainDecoration::
	adddecoration ITEMID
	copyvar VAR_0x8007, VAR_RESULT
	call J_EventScript_ObtainDecorationMessage
	return

J_EventScript_ObtainDecorationMessage::
	bufferdecorationname STR_VAR_2, ITEMID
	call_if_eq VAR_0x8007, TRUE, J_EventScript_ObtainedDecor
	call_if_eq VAR_0x8007, FALSE, J_EventScript_NoRoomForDecor
	return

J_EventScript_ObtainedDecor::
	playfanfare MUS_OBTAIN_ITEM
	message J_gText_ObtainedTheDecor
	waitfanfare
	msgbox J_gText_TheDecorWasTransferredToThePC, MSGBOX_DEFAULT
	setvar VAR_RESULT, TRUE
	return

J_EventScript_NoRoomForDecor::
	setvar VAR_RESULT, FALSE
	return

J_Std_FindItem::
	lock
	faceplayer
	waitse
	copyvar VAR_0x8006, ITEMID
	copyvar VAR_0x8004, ITEMID
	copyvar VAR_0x8005, AMOUNT

	callnative FindItemRandomize_NativeCall
	copyvar VAR_0x8006, ITEMID
	copyvar VAR_0x8004, ITEMID

	checkitemspace ITEMID, AMOUNT
	copyvar VAR_0x8007, VAR_RESULT
	bufferitemnameplural STR_VAR_2, ITEMID, AMOUNT
	checkitemtype ITEMID
	call J_EventScript_BufferPocketNameAndTryFanfare
	call_if_eq VAR_0x8007, TRUE, J_EventScript_PickUpItem
	call_if_eq VAR_0x8007, FALSE, J_EventScript_NoRoomToPickUpItem
	release
	return

J_EventScript_PickUpItem::
	removeobject VAR_LAST_TALKED
	additem VAR_0x8004, VAR_0x8005
	copyvar 32774 32772
	specialvar VAR_RESULT, BufferTMHMMoveName
	copyvar VAR_0x8008, VAR_RESULT
	call_if_eq VAR_0x8008, TRUE, J_EventScript_FoundTMHM
	call_if_eq VAR_0x8008, FALSE, J_EventScript_FoundItem
	delay 10
	showitemdescription
	waitfanfare
	waitmessage
	bufferitemnameplural STR_VAR_2, VAR_0x8004, VAR_0x8005
	pyramid_getlocation
	goto_if_eq VAR_RESULT, PYRAMID_LOCATION_FLOOR, J_EventScript_PutBattlePyramidItemInBag
	msgbox J_gText_PutItemInPocket, MSGBOX_DEFAULT
	hideitemdescription
	return

J_EventScript_PutBattlePyramidItemInBag::
	msgbox J_gText_PlayerPutItemInBag, MSGBOX_DEFAULT
	hideitemdescription
	return

J_EventScript_FoundTMHM::
	bufferitemnameplural STR_VAR_1, VAR_0x8004, VAR_0x8005
	compare VAR_0x8005, 2
	goto_if_lt J_EventScript_FoundTMHMMessage
	buffernumberstring STR_VAR_3, VAR_0x8005
	message J_gText_PlayerFoundTMHMs
	goto J_EventScript_BufferTMHMsPocket
	return

J_EventScript_FoundTMHMMessage::
	message J_gText_PlayerFoundOneTMHM
	return

J_EventScript_FoundItem::
	compare VAR_0x8001, TRUE
	goto_if_eq J_EventScript_FoundItemMessage
	buffernumberstring 0, VAR_0x8001
	message J_gText_PlayerFoundItems
	return

J_EventScript_FoundItemMessage::
	message J_gText_PlayerFoundOneItem
	return

J_EventScript_NoRoomToPickUpItem::
	msgbox J_gText_ObtainedTheItem, MSGBOX_DEFAULT
	msgbox J_gText_TooBadBagIsFull, MSGBOX_DEFAULT
	setvar VAR_RESULT, FALSE
	return

J_EventScript_HiddenItemScript::
	lockall
	waitse
	goto_if_eq VAR_0x8005, 0, J_EventScript_TryPickUpHiddenCoins

	callnative FindHiddenItemRandomize_NativeCall

	copyvar VAR_0x8006, VAR_0x8005
	additem VAR_0x8005, VAR_0x8009
	copyvar VAR_0x8007, VAR_RESULT
	bufferitemnameplural STR_VAR_2, VAR_0x8005, 1
	checkitemtype VAR_0x8005
	call J_EventScript_BufferPocketNameAndTryFanfare
	goto_if_eq VAR_0x8007, TRUE, J_EventScript_PickUpHiddenItem
	goto_if_eq VAR_0x8007, FALSE, J_EventScript_NoRoomForHiddenItem
	end

J_EventScript_PickUpHiddenItem::
	copyvar VAR_0x8008, VAR_0x8004
	copyvar VAR_0x8004, VAR_0x8005
	specialvar VAR_RESULT, BufferTMHMMoveName
	goto_if_eq VAR_RESULT, TRUE, J_EventScript_FoundHiddenTMHM
	goto_if_eq VAR_RESULT, FALSE, J_EventScript_FoundHiddenItem
	end

J_EventScript_FoundHiddenTMHM::
	bufferitemnameplural STR_VAR_1, VAR_0x8004, 1
	message J_gText_PlayerFoundOneTMHM
	goto J_EventScript_PutHiddenItemInPocket
	end

J_EventScript_FoundHiddenItem::
	call_if_eq VAR_0x8009, 1, J_EventScript_FoundSingleItem
	call_if_ne VAR_0x8009, 1, J_EventScript_FoundMultipleItems
	goto J_EventScript_PutHiddenItemInPocket
	end

J_EventScript_FoundSingleItem::
	message J_gText_PlayerFoundOneItem
	return

J_EventScript_FoundMultipleItems::
	buffernumberstring STR_VAR_1, VAR_0x8009
	message J_gText_FoundXItems
	return

J_EventScript_PutHiddenItemInPocket::
	callnative Script_ClearDowsingColor
	delay 10
	showitemdescription
	waitmessage
	waitfanfare
	bufferitemnameplural STR_VAR_2, VAR_0x8004, 1
	copyvar VAR_0x8004, VAR_0x8008
	msgbox J_gText_PutItemInPocket, MSGBOX_DEFAULT
	hideitemdescription
	special TryPutTreasureInvestigatorsOnAir
	special SetHiddenItemFlag
	callnative Script_UpdateDowseState
	releaseall
	end

J_EventScript_NoRoomForHiddenItem::
	msgbox J_gText_PlayerFoundOneItem, MSGBOX_DEFAULT
	msgbox J_gText_TooBadBagIsFull, MSGBOX_DEFAULT
	setvar VAR_RESULT, 0
	releaseall
	end

J_EventScript_RestorePrevTextColor::
	copyvar VAR_TEXT_COLOR, VAR_PREV_TEXT_COLOR
	return

J_Std_PutItemAway::
	bufferitemnameplural STR_VAR_2, VAR_0x8000, VAR_0x8001
	checkitemtype VAR_0x8000
	call J_EventScript_BufferPutAwayPocketName
	msgbox J_gText_PutItemInPocket
	return

J_EventScript_BufferPutAwayPocketName::
	switch VAR_RESULT
	case POCKET_MEDICINE, J_EventScript_BufferPutAwayPocketMedicinePouch,
	case POCKET_ITEMS, J_EventScript_BufferPutAwayPocketItems
	case POCKET_KEY_ITEMS, J_EventScript_BufferPutAwayPocketKeyItems
	case POCKET_POKE_BALLS, J_EventScript_BufferPutAwayPocketPokeBalls
	case POCKET_TM_HM, J_EventScript_BufferPutAwayPocketTMCase
	case POCKET_BERRIES, J_EventScript_BufferPutAwayPocketBerryPouch

	case POCKET_ITEMS, J_EventScript_BufferPutAwayPocketTreasuresPouch
	case POCKET_MEDICINE, J_EventScript_BufferPutAwayPocketBattleItemsPouch

	end

J_EventScript_BufferPutAwayPocketItems::
	bufferstdstring STR_VAR_3, STDSTRING_ITEMS
	return

J_EventScript_BufferPutAwayPocketKeyItems::
	bufferstdstring STR_VAR_3, STDSTRING_KEYITEMS
	return

J_EventScript_BufferPutAwayPocketPokeBalls::
	bufferstdstring STR_VAR_3, STDSTRING_POKEBALLS
	return

J_EventScript_BufferPutAwayPocketTMCase::
	bufferstdstring STR_VAR_3, STDSTRING_TMHMS
	return

J_EventScript_BufferPutAwayPocketBerryPouch::
	bufferstdstring STR_VAR_3, STDSTRING_BERRIES
	return

J_EventScript_BufferPutAwayPocketMedicinePouch::
	bufferstdstring STR_VAR_3, STDSTRING_MEDICINE
	return

J_EventScript_BufferPutAwayPocketBattleItemsPouch::
	bufferstdstring STR_VAR_3, STDSTRING_BATTLE_ITEMS
	return

J_EventScript_BufferPutAwayPocketTreasuresPouch::
	bufferstdstring STR_VAR_3, STDSTRING_TREASURES
	return

J_EventScript_TryPickUpHiddenCoins::
	goto_if_unset JOHTO_FLAG_GOT_COIN_CASE, J_EventScript_NoCaseForHiddenCoins
	checkcoins VAR_RESULT
	specialvar VAR_RESULT, CheckAddCoins
	goto_if_eq VAR_RESULT, FALSE, J_EventScript_HiddenCoinsButCaseIsFull
	addcoins VAR_0x8009
	bufferstdstring STR_VAR_2, STDSTRING_COINS
	call J_EventScript_PlayFanfareObtainedItem
	call J_EventScript_FoundCoins
	waitfanfare
	waitmessage
	msgbox J_gText_PutCoinsAwayInCoinCase
	special SetHiddenItemFlag
	releaseall
	end

J_EventScript_FoundCoins::
	buffernumberstring STR_VAR_1, VAR_0x8009
	message J_gText_FoundXCoins
	return

J_EventScript_HiddenCoinsButCaseIsFull::
	buffernumberstring STR_VAR_1, VAR_0x8009
	bufferstdstring STR_VAR_2, STDSTRING_COINS
	msgbox J_gText_FoundXCoins
	msgbox J_gText_CoinCaseIsFull
	setvar VAR_RESULT, 0
	releaseall
	end

J_EventScript_NoCaseForHiddenCoins::
	buffernumberstring STR_VAR_1, VAR_0x8009
	bufferstdstring STR_VAR_2, STDSTRING_COINS
	msgbox J_gText_FoundXCoins
	msgbox J_gText_NothingToPutThemIn
	setvar VAR_RESULT, 0
	releaseall
	end

