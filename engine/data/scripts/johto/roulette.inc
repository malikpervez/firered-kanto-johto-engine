@ Johto (data/scripts/roulette.inc), as built into the FireRed game.

J_Roulette_EventScript_Table1::
	checkitem ITEM_COIN_CASE
	goto_if_eq 32781, FALSE, MauvilleCity_GameCorner_EventScript_NoCoinCase
	setvar 32772, 0
	getpokenewsactive 2
	goto_if_eq 32781, FALSE, J_Roulette_EventScript_Play
	addvar 32772, (1 << 7)
	goto J_Roulette_EventScript_Play
	end

J_Roulette_EventScript_Table2::
	checkitem ITEM_COIN_CASE
	goto_if_eq 32781, FALSE, MauvilleCity_GameCorner_EventScript_NoCoinCase
	setvar 32772, 1
	getpokenewsactive 2
	goto_if_eq 32781, FALSE, J_Roulette_EventScript_Play
	addvar 32772, (1 << 7)
	goto J_Roulette_EventScript_Play
	end

J_Roulette_EventScript_Play::
	special PlayRoulette
	waitstate
	end

