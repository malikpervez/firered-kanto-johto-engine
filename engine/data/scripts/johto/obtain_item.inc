@ Johto (data/scripts/obtain_item.inc), as built into the FireRed game.

J_Std_ObtainItem::

	callnative ObtainItemRandomize_NativeCall

	copyvar 32774, ITEMID
	additem ITEMID, AMOUNT
	copyvar 32775, 32781
	call J_EventScript_ObtainItemMessage
	return

J_EventScript_ObtainItemMessage::
	bufferitemnameplural STR_VAR_2, ITEMID, AMOUNT
	checkitemtype ITEMID
	call J_EventScript_BufferPocketNameAndTryFanfare
	call_if_eq 32775, TRUE, J_EventScript_ObtainedItem
	call_if_eq 32775, FALSE, J_EventScript_NoRoomForItem
	return

J_EventScript_BufferPocketNameAndTryFanfare::
	switch 32781
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
	bufferstdstring STR_VAR_3, 14
	call_if_eq 32775, TRUE, J_EventScript_PlayFanfareObtainedItem
	return

J_EventScript_BufferKeyItemsPocket::
	bufferstdstring STR_VAR_3, 15
	call_if_eq 32775, TRUE, J_EventScript_PlayFanfareObtainedKeyItem
	return

J_EventScript_BufferPokeballsPocket::
	bufferstdstring STR_VAR_3, 16
	call_if_eq 32775, TRUE, J_EventScript_PlayFanfareObtainedItem
	return

J_EventScript_BufferTMHMsPocket::
	bufferstdstring STR_VAR_3, 17
	call_if_eq 32775, TRUE, J_EventScript_PlayFanfareObtainedTMHM
	return

J_EventScript_BufferBerriesPocket::
	bufferstdstring STR_VAR_3, 18
	call_if_eq 32775, TRUE, J_EventScript_PlayFanfareObtainedBerry
	return

J_EventScript_BufferMedicinePocket::
	bufferstdstring STR_VAR_3, 39
	call_if_eq 32775, TRUE, J_EventScript_PlayFanfareObtainedItem
	return

J_EventScript_BufferBattleItemsPocket::
	bufferstdstring STR_VAR_3, 40
	call_if_eq 32775, TRUE, J_EventScript_PlayFanfareObtainedItem
	return

J_EventScript_BufferTreasuresPocket::
	bufferstdstring STR_VAR_3, 41
	call_if_eq 32775, TRUE, J_EventScript_PlayFanfareObtainedItem
	return

J_EventScript_ObtainedItem::
	compare 32769, TRUE
	goto_if_eq J_EventScript_ObtainedItemMessage
	buffernumberstring 0, 32769
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
	setvar 32781, TRUE
	return

J_EventScript_NoRoomForItem::
	setvar 32781, FALSE
	return

J_EventScript_PlayFanfareObtainedItem::
	playfanfare 370
	return

J_EventScript_PlayFanfareObtainedKeyItem::



	playfanfare 530



	return

J_EventScript_PlayFanfareObtainedTMHM::
	playfanfare 372
	return

J_EventScript_PlayFanfareObtainedBerry::


	playfanfare 387



	return

J_Std_ObtainDecoration::
	adddecoration ITEMID
	copyvar 32775, 32781
	call J_EventScript_ObtainDecorationMessage
	return

J_EventScript_ObtainDecorationMessage::
	bufferdecorationname STR_VAR_2, ITEMID
	call_if_eq 32775, TRUE, J_EventScript_ObtainedDecor
	call_if_eq 32775, FALSE, J_EventScript_NoRoomForDecor
	return

J_EventScript_ObtainedDecor::
	playfanfare 370
	message J_gText_ObtainedTheDecor
	waitfanfare
	msgbox J_gText_TheDecorWasTransferredToThePC, MSGBOX_DEFAULT
	setvar 32781, TRUE
	return

J_EventScript_NoRoomForDecor::
	setvar 32781, FALSE
	return

J_Std_FindItem::
	lock
	faceplayer
	waitse
	copyvar 32774, ITEMID
	copyvar 32772, ITEMID
	copyvar 32773, AMOUNT

	callnative FindItemRandomize_NativeCall
	copyvar 32774, ITEMID
	copyvar 32772, ITEMID

	checkitemspace ITEMID, AMOUNT
	copyvar 32775, 32781
	bufferitemnameplural STR_VAR_2, ITEMID, AMOUNT
	checkitemtype ITEMID
	call J_EventScript_BufferPocketNameAndTryFanfare
	call_if_eq 32775, TRUE, J_EventScript_PickUpItem
	call_if_eq 32775, FALSE, J_EventScript_NoRoomToPickUpItem
	release
	return

J_EventScript_PickUpItem::
	removeobject 32783
	additem 32772, 32773
	copyvar 32774 32772
	specialvar 32781, BufferTMHMMoveName
	copyvar 32776, 32781
	call_if_eq 32776, TRUE, J_EventScript_FoundTMHM
	call_if_eq 32776, FALSE, J_EventScript_FoundItem
	delay 10
	showitemdescription
	waitfanfare
	waitmessage
	bufferitemnameplural STR_VAR_2, 32772, 32773
	pyramid_getlocation
	goto_if_eq 32781, 1, J_EventScript_PutBattlePyramidItemInBag
	msgbox J_gText_PutItemInPocket, MSGBOX_DEFAULT
	hideitemdescription
	return

J_EventScript_PutBattlePyramidItemInBag::
	msgbox J_gText_PlayerPutItemInBag, MSGBOX_DEFAULT
	hideitemdescription
	return

J_EventScript_FoundTMHM::
	bufferitemnameplural STR_VAR_1, 32772, 32773
	compare 32773, 2
	goto_if_lt J_EventScript_FoundTMHMMessage
	buffernumberstring STR_VAR_3, 32773
	message J_gText_PlayerFoundTMHMs
	goto J_EventScript_BufferTMHMsPocket
	return

J_EventScript_FoundTMHMMessage::
	message J_gText_PlayerFoundOneTMHM
	return

J_EventScript_FoundItem::
	compare 32769, TRUE
	goto_if_eq J_EventScript_FoundItemMessage
	buffernumberstring 0, 32769
	message J_gText_PlayerFoundItems
	return

J_EventScript_FoundItemMessage::
	message J_gText_PlayerFoundOneItem
	return

J_EventScript_NoRoomToPickUpItem::
	msgbox J_gText_ObtainedTheItem, MSGBOX_DEFAULT
	msgbox J_gText_TooBadBagIsFull, MSGBOX_DEFAULT
	setvar 32781, FALSE
	return

J_EventScript_HiddenItemScript::
	lockall
	waitse
	goto_if_eq 32773, 0, J_EventScript_TryPickUpHiddenCoins

	callnative FindHiddenItemRandomize_NativeCall

	copyvar 32774, 32773
	additem 32773, 32777
	copyvar 32775, 32781
	bufferitemnameplural STR_VAR_2, 32773, 1
	checkitemtype 32773
	call J_EventScript_BufferPocketNameAndTryFanfare
	goto_if_eq 32775, TRUE, J_EventScript_PickUpHiddenItem
	goto_if_eq 32775, FALSE, J_EventScript_NoRoomForHiddenItem
	end

J_EventScript_PickUpHiddenItem::
	copyvar 32776, 32772
	copyvar 32772, 32773
	specialvar 32781, BufferTMHMMoveName
	goto_if_eq 32781, TRUE, J_EventScript_FoundHiddenTMHM
	goto_if_eq 32781, FALSE, J_EventScript_FoundHiddenItem
	end

J_EventScript_FoundHiddenTMHM::
	bufferitemnameplural STR_VAR_1, 32772, 1
	message J_gText_PlayerFoundOneTMHM
	goto J_EventScript_PutHiddenItemInPocket
	end

J_EventScript_FoundHiddenItem::
	call_if_eq 32777, 1, J_EventScript_FoundSingleItem
	call_if_ne 32777, 1, J_EventScript_FoundMultipleItems
	goto J_EventScript_PutHiddenItemInPocket
	end

J_EventScript_FoundSingleItem::
	message J_gText_PlayerFoundOneItem
	return

J_EventScript_FoundMultipleItems::
	buffernumberstring STR_VAR_1, 32777
	message J_gText_FoundXItems
	return

J_EventScript_PutHiddenItemInPocket::
	callnative Script_ClearDowsingColor
	delay 10
	showitemdescription
	waitmessage
	waitfanfare
	bufferitemnameplural STR_VAR_2, 32772, 1
	copyvar 32772, 32776
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
	setvar 32781, 0
	releaseall
	end

J_EventScript_RestorePrevTextColor::
	copyvar 32786, 32787
	return

J_Std_PutItemAway::
	bufferitemnameplural STR_VAR_2, 32768, 32769
	checkitemtype 32768
	call J_EventScript_BufferPutAwayPocketName
	msgbox J_gText_PutItemInPocket
	return

J_EventScript_BufferPutAwayPocketName::
	switch 32781
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
	bufferstdstring STR_VAR_3, 14
	return

J_EventScript_BufferPutAwayPocketKeyItems::
	bufferstdstring STR_VAR_3, 15
	return

J_EventScript_BufferPutAwayPocketPokeBalls::
	bufferstdstring STR_VAR_3, 16
	return

J_EventScript_BufferPutAwayPocketTMCase::
	bufferstdstring STR_VAR_3, 17
	return

J_EventScript_BufferPutAwayPocketBerryPouch::
	bufferstdstring STR_VAR_3, 18
	return

J_EventScript_BufferPutAwayPocketMedicinePouch::
	bufferstdstring STR_VAR_3, 39
	return

J_EventScript_BufferPutAwayPocketBattleItemsPouch::
	bufferstdstring STR_VAR_3, 40
	return

J_EventScript_BufferPutAwayPocketTreasuresPouch::
	bufferstdstring STR_VAR_3, 41
	return

J_EventScript_TryPickUpHiddenCoins::
	goto_if_unset 0, J_EventScript_NoCaseForHiddenCoins
	checkcoins 32781
	specialvar 32781, CheckAddCoins
	goto_if_eq 32781, FALSE, J_EventScript_HiddenCoinsButCaseIsFull
	addcoins 32777
	bufferstdstring STR_VAR_2, 38
	call J_EventScript_PlayFanfareObtainedItem
	call J_EventScript_FoundCoins
	waitfanfare
	waitmessage
	msgbox J_gText_PutCoinsAwayInCoinCase
	special SetHiddenItemFlag
	releaseall
	end

J_EventScript_FoundCoins::
	buffernumberstring STR_VAR_1, 32777
	message J_gText_FoundXCoins
	return

J_EventScript_HiddenCoinsButCaseIsFull::
	buffernumberstring STR_VAR_1, 32777
	bufferstdstring STR_VAR_2, 38
	msgbox J_gText_FoundXCoins
	msgbox J_gText_CoinCaseIsFull
	setvar 32781, 0
	releaseall
	end

J_EventScript_NoCaseForHiddenCoins::
	buffernumberstring STR_VAR_1, 32777
	bufferstdstring STR_VAR_2, 38
	msgbox J_gText_FoundXCoins
	msgbox J_gText_NothingToPutThemIn
	setvar 32781, 0
	releaseall
	end

