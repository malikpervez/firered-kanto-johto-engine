@ Johto (data/maps/FarawayIsland_Entrance_hns/scripts.inc), as built into the FireRed game.

FarawayIsland_Entrance_hns_MapScripts::
	map_script 3, FarawayIsland_Entrance_hns_OnTransition
	.byte 0

FarawayIsland_Entrance_hns_OnTransition:
	setflag 0
	end

FarawayIsland_Entrance_hns_EventScript_SetCloudsWeather::
	setweather 1
	doweather
	end

FarawayIsland_Entrance_hns_EventScript_ClearWeather::
	setweather 0
	doweather
	end

FarawayIsland_Entrance_hns_EventScript_Sailor::
	lock
	faceplayer
	msgbox J_FarawayIsland_Entrance_Text_SailorReturn, MSGBOX_YESNO
	goto_if_eq 32781, NO, FarawayIsland_Entrance_hns_EventScript_AsYouLike
	msgbox J_EventTicket_Text_SailHome, MSGBOX_DEFAULT
	closemessage
	applymovement 32783, J_Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	delay 30
	hideobjectat 1, MAP_FARAWAY_ISLAND_ENTRANCE_HNS
	setvar 32772, 2
	call J_Common_EventScript_FerryDepartIsland
	warpsilent MAP_OLIVINE_CITY_PORT_INSIDE_HNS, 8, 16
	waitstate
	release
	end

FarawayIsland_Entrance_hns_EventScript_AsYouLike::
	msgbox J_EventTicket_Text_AsYouLike, MSGBOX_DEFAULT
	release
	end

FarawayIsland_Entrance_hns_EventScript_Sign::
	msgbox FarawayIsland_Entrance_hns_Text_Sign, MSGBOX_SIGN
	closemessage
	end

FarawayIsland_Entrance_hns_Text_Sign:
	.string "Th{SE_M_REVERSAL}writin{SE_M_SANDSTORM}i{SE_M_GRASSWHISTLE}fadin{SE_M_SANDSTORM}a{SE_M_GRASSWHISTLE}i{SE_M_ACID_ARMOR}it\n"
	.string "wa{SE_M_GRASSWHISTLE}writte{SE_M_ATTRACT}{SE_M_CHARGE}lon{SE_M_SANDSTORM}tim{SE_M_REVERSAL}ago..\p"
	.string "..ber{SE_M_SUPERSONIC}6t{SE_M_TRI_ATTACK}da{SE_M_YAWN}I{SE_M_ACID_ARMOR}an{SE_M_YAWN}human..\n"
	.string "set{SE_M_GRASSWHISTLE}foo{SE_M_SPIT_UP}here.{SE_M_PERISH_SONG}again..e{SE_M_SPIT_UP}it\l"
	.string "b{SE_M_REVERSAL}{SE_M_CHARGE}kindhearte{SE_M_WATERFALL}pers.{SE_M_PERISH_SONG}..ith\l"
	.string "tha{SE_M_SPIT_UP}hope{SE_M_SUPERSONIC}{SE_M_HEAL_BELL}depar..$"

