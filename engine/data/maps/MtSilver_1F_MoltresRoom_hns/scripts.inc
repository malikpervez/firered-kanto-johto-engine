@ Johto (data/maps/MtSilver_1F_MoltresRoom_hns/scripts.inc), as built into the FireRed game.

MtSilver_1F_MoltresRoom_hns_MapScripts::
	map_script 3, MtSilver_1F_MoltresRoom_OnTransition
	map_script 5, MtSilver_1F_MoltresRoom_OnResume
	.byte 0

MtSilver_1F_MoltresRoom_OnResume::
	setescapewarp MAP_MT_SILVER_OUTSIDE_HNS, 17, 8
	end

MtSilver_1F_MoltresRoom_OnTransition:
	callnative SetTimeBasedEncounters
	end

MtSilver_1F_MoltresRoom_EventScript_Moltres::
	lock
	faceplayer
	playmoncry 146, 2
	msgbox J_SeafoamIslands_B1F_Text_ArticunoBattle
	delay 40
	waitmoncry
	seteventmon 146, 50
	special BattleSetup_StartLegendaryBattle
	waitstate
	specialvar 32781, GetBattleOutcome
	goto_if_eq 32781, 4, MtSilver_1F_MoltresRoom_EventScript_MoltresRan
	fadescreenswapbuffers 1
	removeobject 1
	setflag 8258
	fadescreenswapbuffers 0
	release
	end

MtSilver_1F_MoltresRoom_EventScript_MoltresRan::
	release
	end

