@ Johto (data/event_scripts.s), as built into the FireRed game.

J_EventScript_GetInGameTradeSpeciesInfo::
	copyvar VAR_0x8005, VAR_0x8008
	specialvar VAR_0x8009, GetInGameTradeSpeciesInfo
	return

J_EventScript_ChooseMonForInGameTrade::
	special ChoosePartyMon
	waitstate
	lock
	faceplayer
	return

J_EventScript_GetInGameTradeSpecies::
	specialvar VAR_RESULT, GetTradeSpecies
	return

J_EventScript_DoInGameTrade::
	special CreateInGameTradePokemon
	special DoInGameTradeScene
	waitstate
	lock
	faceplayer
	return

J_EventScript_SelectWithoutRegisteredItem::
	msgbox J_gText_SelectWithoutRegisteredItem, MSGBOX_SIGN
	end

J_EventScript_SelectWithoutRegisteredHoldItem::
	msgbox J_gText_SelectWithoutRegisteredHoldItem, MSGBOX_SIGN
	end

