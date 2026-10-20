@ Johto (data/maps/MtSilver_3F_hns/scripts.inc), as built into the FireRed game.

MtSilver_3F_hns_MapScripts::
	map_script 3, MtSilver_3F_OnTransition
	map_script 5, MtSilver_3F_OnResume
	.byte 0

MtSilver_3F_OnResume::
	callnative SetTimeBasedEncounters
	setescapewarp MAP_MT_SILVER_OUTSIDE_HNS, 17, 8
	end

MtSilver_3F_OnTransition:
	callnative SetTimeBasedEncounters
	setescapewarp MAP_MT_SILVER_OUTSIDE_HNS, 17, 8
	end

