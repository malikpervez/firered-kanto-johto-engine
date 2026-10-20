@ Johto (data/maps/BirthIsland_Harbor_hns/scripts.inc), as built into the FireRed game.

BirthIsland_Harbor_hns_MapScripts::
	.byte 0

BirthIsland_Harbor_hns_EventScript_Sailor::
	lock
	faceplayer
	msgbox J_BirthIsland_Harbor_Text_SailorReturn, MSGBOX_YESNO
	goto_if_eq 32781, NO, BirthIsland_Harbor_hns_EventScript_AsYouLike
	msgbox J_EventTicket_Text_SailHome, MSGBOX_DEFAULT
	closemessage
	applymovement 32783, J_Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	delay 30
	hideobjectat 1, MAP_BIRTH_ISLAND_HARBOR_HNS
	setvar 32772, 2
	call J_Common_EventScript_FerryDepartIsland
	warp MAP_OLIVINE_CITY_PORT_INSIDE_HNS, 8, 9
	waitstate
	release
	end

BirthIsland_Harbor_hns_EventScript_AsYouLike::
	msgbox J_EventTicket_Text_AsYouLike, MSGBOX_DEFAULT
	release
	end

