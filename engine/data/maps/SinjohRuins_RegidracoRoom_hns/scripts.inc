@ Johto (data/maps/SinjohRuins_RegidracoRoom_hns/scripts.inc), as built into the FireRed game.

SinjohRuins_RegidracoRoom_hns_MapScripts::
	.byte 0

SinjohRuins_RegidragoRoom_EventScript_Regidrago::
	lock
	faceplayer
	playmoncry 895, 2
	waitmoncry
	seteventmon 895, 80
	special BattleSetup_StartLegendaryBattle
	waitstate
	specialvar 32781, GetBattleOutcome
	goto_if_eq 32781, 4, SinjohRuins_RegidragoRoom_EventScript_RegidragoRan
	fadescreenswapbuffers 1
	removeobject 1
	setflag 9136
	fadescreenswapbuffers 0
	release
	end

SinjohRuins_RegidragoRoom_EventScript_RegidragoRan::
	release
	end

