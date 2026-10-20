@ Johto (data/scripts/roulette.inc), as built into the FireRed game.

J_Roulette_EventScript_Table1::
	checkitem ITEM_COIN_CASE
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoCoinCase
	setvar VAR_0x8004, 0
	getpokenewsactive POKENEWS_GAME_CORNER
	goto_if_eq VAR_RESULT, FALSE, J_Roulette_EventScript_Play
	addvar VAR_0x8004, (1 << 7)
	goto J_Roulette_EventScript_Play
	end

J_Roulette_EventScript_Table2::
	checkitem ITEM_COIN_CASE
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoCoinCase
	setvar VAR_0x8004, 1
	getpokenewsactive POKENEWS_GAME_CORNER
	goto_if_eq VAR_RESULT, FALSE, J_Roulette_EventScript_Play
	addvar VAR_0x8004, (1 << 7)
	goto J_Roulette_EventScript_Play
	end

J_Roulette_EventScript_Play::
	special PlayRoulette
	waitstate
	end

