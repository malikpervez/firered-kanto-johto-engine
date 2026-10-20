@ Johto (data/maps/MtSilver_MountainSide_hns/scripts.inc), as built into the FireRed game.

MtSilver_MountainSide_hns_MapScripts::
	map_script 3, MtSilver_MountainSide_OnTransition
	map_script 5, J_SetTimeEncounters
	.byte 0

MtSilver_MountainSide_OnTransition:
	callnative SetTimeBasedEncounters
	end

MtSilver_MountainSide_EventScript_Item_Stealth_Rock::
	finditem 657
	end

