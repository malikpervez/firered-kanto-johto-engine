@ Johto (data/maps/SouthernIsland_Interior_hns/scripts.inc), as built into the FireRed game.

SouthernIsland_Interior_hns_MapScripts::
	map_script 3, SouthernIsland_Interior_hns_OnTransition
	.byte 0

SouthernIsland_Interior_hns_OnTransition::
	goto_if_eq 20626, 0, SouthernIsland_Interior_hns_HideLatias
	removeobject 1
	setflag 8264
	end

SouthernIsland_Interior_hns_HideLatias::
	removeobject 2
	setflag 8263
	end

SouthernIsland_Interior_hns_EventScript_Latios::
	lock
	faceplayer
	playmoncry 381, 2
	waitmoncry
	seteventmon 381, 50
	special BattleSetup_StartLegendaryBattle
	waitstate
	specialvar 32781, GetBattleOutcome
	goto_if_eq 32781, 4, SouthernIsland_Interior_hns_EventScript_LatiosRan
	fadescreenswapbuffers 1
	removeobject 1
	setflag 8264
	fadescreenswapbuffers 0
	release
	end

SouthernIsland_Interior_hns_EventScript_LatiosRan::
	release
	end

SouthernIsland_Interior_hns_EventScript_Latias::
	lock
	faceplayer
	playmoncry 380, 2
	waitmoncry
	seteventmon 380, 50
	special BattleSetup_StartLegendaryBattle
	waitstate
	specialvar 32781, GetBattleOutcome
	goto_if_eq 32781, 4, SouthernIsland_Interior_hns_EventScript_LatiasRan
	fadescreenswapbuffers 1
	removeobject 2
	setflag 8263
	fadescreenswapbuffers 0
	release
	end

SouthernIsland_Interior_hns_EventScript_LatiasRan::
	release
	end

