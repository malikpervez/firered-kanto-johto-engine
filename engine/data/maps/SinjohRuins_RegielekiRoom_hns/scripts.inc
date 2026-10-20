@ Johto (data/maps/SinjohRuins_RegielekiRoom_hns/scripts.inc), as built into the FireRed game.

SinjohRuins_RegielekiRoom_hns_MapScripts::
	.byte 0

SinjohRuins_RegielekiRoom_EventScript_Regieleki::
	lock
	faceplayer
	playmoncry 894, 2
	waitmoncry
	seteventmon 894, 80
	special BattleSetup_StartLegendaryBattle
	waitstate
	specialvar 32781, GetBattleOutcome
	goto_if_eq 32781, 4, SinjohRuins_RegielekiRoom_EventScript_RegielekiRan
	fadescreenswapbuffers 1
	removeobject 1
	setflag 9135
	fadescreenswapbuffers 0
	release
	end

SinjohRuins_RegielekiRoom_EventScript_RegielekiRan::
	release
	end

