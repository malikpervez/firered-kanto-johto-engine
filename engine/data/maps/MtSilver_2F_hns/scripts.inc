@ Johto (data/maps/MtSilver_2F_hns/scripts.inc), as built into the FireRed game.

MtSilver_2F_hns_MapScripts::
	map_script 3, MtSilver_2F_OnTransition
	map_script 5, MtSilver_2F_OnResume
	.byte 0

MtSilver_2F_OnResume::
	callnative SetTimeBasedEncounters
	setescapewarp MAP_MT_SILVER_OUTSIDE_HNS, 17, 8
	end

MtSilver_2F_OnTransition:
	callnative SetTimeBasedEncounters
	setescapewarp MAP_MT_SILVER_OUTSIDE_HNS, 17, 8
	end

MtSilver_2F_Item_AzureFlue::
	finditem ITEM_AZURE_FLUTE
	end

