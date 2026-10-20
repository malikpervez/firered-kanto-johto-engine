WhirlIslands_Descent_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, BlackTide_DescentOnTransition
	.byte 0

BlackTide_DescentOnTransition:
	call_if_eq VAR_COMPLETED_LUGIA, 4, BlackTide_OpenNativePostgameApproach
	call JT04_Visibility
	end
BlackTide_OpenNativePostgameApproach:
	setflag FLAG_HIDE_WHIRL_ISLANDS_TENTACRUEL
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
	setweather WEATHER_FOG_HORIZONTAL
	doweather
	end
