@ Johto (data/maps/WhirlIslands_Descent_hns/scripts.inc), as built into the FireRed game.

WhirlIslands_Descent_hns_MapScripts::
	map_script 3, BlackTide_DescentOnTransition
	.byte 0

BlackTide_DescentOnTransition:
	call_if_eq 20559, 4, BlackTide_OpenNativePostgameApproach
	call JT04_Visibility
	end

BlackTide_OpenNativePostgameApproach:
	setflag 8245
	return

WhirlIslands_Descent_EventScript_Item_Max_Revive::
	finditem ITEM_MAX_REVIVE
	end

WhirlIslands_Descent_EventScript_Item_Full_Restore::
	finditem ITEM_FULL_RESTORE
	end

WhirlIslands_Descent_EventScript_Item_PP_Max::
	finditem ITEM_PP_MAX
	end

WhirlIslands_B2F_Trigger_Fog::
	setweather 6
	doweather
	end

