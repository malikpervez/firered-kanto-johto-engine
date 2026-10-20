@ Johto (data/maps/MtSilver_SummitDay_hns/scripts.inc), as built into the FireRed game.

MtSilver_SummitDay_hns_MapScripts::
	map_script 3, MtSilver_SummitDay_OnTransition
	map_script 2, MtSilver_SummitDay_OnFrame
	.byte 0

MtSilver_SummitDay_OnFrame::
	map_script_2 16395, 0, MtSilver_SummitDay_Blizzard
	.2byte 0

MtSilver_SummitDay_Blizzard::
	playse 153
	setvar 16395, 1
	end

MtSilver_SummitDay_OnTransition:
	setescapewarp MAP_MT_SILVER_OUTSIDE_HNS, 17, 8
	call_if_set 8796, MtSilver_SummitDay_EventScript_SetNight
	call_if_unset 8796, MtSilver_SummitDay_EventScript_SetDay
	end

MtSilver_SummitDay_EventScript_SetNight::
	setmaplayoutindex 962
	return

MtSilver_SummitDay_EventScript_SetDay::
	setmaplayoutindex 961
	return

MtSilver_SummitDay_EventScript_Red::
	lock
	faceplayer
	msgbox MtSilver_SummitDay_Text_Red, MSGBOX_DEFAULT
	closemessage
	goto_if_unset 10400, MtSilver_SummitDay_EventScript_RedStandard
	goto_if_ge 20639, 13, MtSilver_SummitDay_EventScript_RedPostOBC

MtSilver_SummitDay_EventScript_RedStandard::
	trainerbattle_no_intro 1488, MtSilver_SummitDay_Text_RedBeaten
	goto MtSilver_SummitDay_EventScript_RedOnDefeat

MtSilver_SummitDay_EventScript_RedPostOBC::
	trainerbattle_no_intro 1674, MtSilver_SummitDay_Text_RedBeaten
	goto MtSilver_SummitDay_EventScript_RedOnDefeat

MtSilver_SummitDay_EventScript_RedOnDefeat::
	playse 153
	setrespawn 128
	msgbox MtSilver_SummitDay_Text_Red, MSGBOX_DEFAULT
	special GivePartyMonLandRibbon
	closemessage
	fadescreenswapbuffers 1
	setflag 8361
	removeobject 1
	fadescreenswapbuffers 0
	delay 180
	fadescreenspeed 1, 24
	setflag 8763
	setflag 2404
	clearflag 8361
	special GameClear
	waitstate
	releaseall
	end

MtSilver_SummitDay_Text_Red:
	.string ".........................\n"
	.string ".........................$"

MtSilver_SummitDay_Text_RedBeaten:
	.string "...!$"

