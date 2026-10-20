@ Johto (data/maps/SouthernIsland_Exterior_hns/scripts.inc), as built into the FireRed game.

SouthernIsland_Exterior_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, SouthernIsland_Exterior_hns_OnTransition
	.byte 0

SouthernIsland_Exterior_hns_OnTransition:
	setflag JOHTO_FLAG_VISITED_CERULEAN_CITY
	end

SouthernIsland_Exterior_hns_EventScript_Sailor::
	lock
	faceplayer
	msgbox J_EventTicket_Text_SouthernIslandSailBack, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, SouthernIsland_Exterior_hns_EventScript_AsYouLike
	msgbox J_EventTicket_Text_SailHome, MSGBOX_DEFAULT
	closemessage
	applymovement VAR_LAST_TALKED, J_Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	delay 30
	hideobjectat LOCALID_SOUTHERN_ISLAND_EXTERIOR_HNS_SAILOR, MAP_SOUTHERN_ISLAND_EXTERIOR_HNS
	setvar VAR_0x8004, LOCALID_SOUTHERN_ISLAND_EXTERIOR_HNS_SS_TIDAL
	call J_Common_EventScript_FerryDepartIsland
	warpsilent MAP_OLIVINE_CITY_PORT_INSIDE_HNS, 8, 16
	waitstate
	release
	end

SouthernIsland_Exterior_hns_EventScript_AsYouLike::
	msgbox J_EventTicket_Text_AsYouLike, MSGBOX_DEFAULT
	release
	end

SouthernIsland_Exterior_hns_EventScript_Sign::
	msgbox J_SouthernIsland_Exterior_Text_Sign, MSGBOX_SIGN
	end

