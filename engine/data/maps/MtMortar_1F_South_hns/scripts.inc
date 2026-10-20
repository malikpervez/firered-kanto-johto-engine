@ Johto (data/maps/MtMortar_1F_South_hns/scripts.inc), as built into the FireRed game.

MtMortar_1F_South_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, MtMortar_1F_South_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, J_SetTimeEncounters
	.byte 0

MtMortar_1F_South_OnTransition:
	callnative SetTimeBasedEncounters
	end

MtMortar_1F_South_EventScript_Item_Aerial_Ace::
	finditem ITEM_TM_AERIAL_ACE
	end

MtMortar_1F_South_EventScript_Item_Elixir::
	finditem ITEM_ELIXIR
	end

