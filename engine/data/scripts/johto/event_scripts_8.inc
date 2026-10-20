@ Johto (data/event_scripts.s), as built into the FireRed game.

J_EventScript_GetInGameTradeSpeciesInfo::
	copyvar 32773, 32776
	specialvar 32777, GetInGameTradeSpeciesInfo
	return

J_EventScript_ChooseMonForInGameTrade::
	special ChoosePartyMon
	waitstate
	lock
	faceplayer
	return

J_EventScript_GetInGameTradeSpecies::
	specialvar 32781, GetTradeSpecies
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

