@ Johto (data/maps/OlivineCity_PortOutside_hns/scripts.inc), as built into the FireRed game.

OlivineCity_PortOutside_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, OlivineCity_MapScript_OnTransition
	.byte 0

OlivineCity_PortOutside_EventScript_Sabrina::
	lock
	faceplayer
	msgbox OlivineCity_PortOutside_Text_Sabrina, MSGBOX_DEFAULT
	closemessage
	fadescreenswapbuffers FADE_TO_BLACK
	setflag JOHTO_FLAG_HIDE_OLIVINE_SABRINA
	removeobject LOCALID_OLIVINE_SABRINA
	fadescreenswapbuffers FADE_FROM_BLACK
	clearflag JOHTO_FLAG_HIDE_DOJO_SABRINA
	release
	end

OlivineCity_PortOutside_Text_Sabrina:
	.string "SABRINA{SE_M_HEAT_WAVE}Ou{SE_M_SPIT_UP}o{SE_M_ACID_ARMOR}th{SE_M_REVERSAL}blue,\n"
	.string "{SE_M_HEAL_BELL}ge{SE_M_SPIT_UP}th{SE_M_REVERSAL}urg{SE_M_REVERSAL}t{SE_M_ATTRACT2}se{SE_M_REVERSAL}th{SE_M_REVERSAL}ocean.\p"
	.string "I'l{SE_M_BATON_PASS}se{SE_M_REVERSAL}yo{SE_M_DIVE}a{SE_M_SPIT_UP}th{SE_M_REVERSAL}FIGHTING\n"
	.string "DOJO.$"

OlivineCity_PortOutside_EventScript_Fisherman1::
	lock
	faceplayer
	msgbox OlivineCity_PortOutside_Text_PortFisherman1, MSGBOX_DEFAULT
	closemessage
	release
	end

OlivineCity_PortOutside_EventScript_Fisherman2::
	lock
	faceplayer
	msgbox OlivineCity_PortOutside_Text_Fisherman2, MSGBOX_DEFAULT
	closemessage
	release
	end

OlivineCity_PortOutside_Text_PortFisherman1:
	.string "FAS{SE_M_SWIFT}SHI{SE_M_PETAL_DANCE}S.S.AQU{SE_M_BONEMERANG}use{SE_M_WATERFALL}t{SE_M_ATTRACT2}sai{SE_M_BATON_PASS}to\n"
	.string "KANT{SE_M_SOLAR_BEAM}o{SE_M_ATTRACT}Monday{SE_M_GRASSWHISTLE}an{SE_M_WATERFALL}Fridays{SE_M_PERISH_SONG}But\l"
	.string "now{SE_M_SUPERSONIC}i{SE_M_SPIT_UP}sail{SE_M_GRASSWHISTLE}almos{SE_M_SPIT_UP}constantly!$"

OlivineCity_PortOutside_Text_Fisherman2:
	.string "A{SE_M_TWISTER}yeah{SE_M_SUPERSONIC}I'{SE_M_MILK_DRINK}fishin'.$"

