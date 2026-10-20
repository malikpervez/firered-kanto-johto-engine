@ Johto (data/maps/MtMortar_1F_South_hns/scripts.inc), as built into the FireRed game.

MtMortar_1F_South_hns_MapScripts::
	map_script 3, MtMortar_1F_South_OnTransition
	map_script 5, J_SetTimeEncounters
	.byte 0

MtMortar_1F_South_OnTransition:
	callnative SetTimeBasedEncounters
	end

MtMortar_1F_South_EventScript_Item_Aerial_Ace::
	finditem 621
	end

MtMortar_1F_South_EventScript_Item_Elixir::
	finditem ITEM_ELIXIR
	end

