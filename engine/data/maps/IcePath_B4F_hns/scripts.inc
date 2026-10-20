@ Johto (data/maps/IcePath_B4F_hns/scripts.inc), as built into the FireRed game.

IcePath_B4F_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, IcePath_B4F_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, J_SetTimeEncounters
	.byte 0

IcePath_B4F_OnTransition:
	callnative SetTimeBasedEncounters
	end

IcePath_B4F_EventScript_Item_NeverMeltIce::
	finditem ITEM_NEVER_MELT_ICE
	end

