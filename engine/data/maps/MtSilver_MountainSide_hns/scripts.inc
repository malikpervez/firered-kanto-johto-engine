@ Johto (data/maps/MtSilver_MountainSide_hns/scripts.inc), as built into the FireRed game.

MtSilver_MountainSide_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, MtSilver_MountainSide_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, J_SetTimeEncounters
	.byte 0

MtSilver_MountainSide_OnTransition:
	callnative SetTimeBasedEncounters
	end

MtSilver_MountainSide_EventScript_Item_Stealth_Rock::
	finditem ITEM_TM_STEALTH_ROCK
	end

