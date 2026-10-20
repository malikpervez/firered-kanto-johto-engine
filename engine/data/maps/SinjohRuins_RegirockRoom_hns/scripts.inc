@ Johto (data/maps/SinjohRuins_RegirockRoom_hns/scripts.inc), as built into the FireRed game.

SinjohRuins_RegirockRoom_hns_MapScripts::
	.byte 0

SinjohRuins_RegirockRoom_EventScript_Regirock::
	lock
	faceplayer
	playmoncry 377, 2
	waitmoncry
	seteventmon 377, 80
	special BattleSetup_StartLegendaryBattle
	waitstate
	specialvar 32781, GetBattleOutcome
	goto_if_eq 32781, 4, SinjohRuins_RegirockRoom_EventScript_RegirockRan
	fadescreenswapbuffers 1
	removeobject 1
	setflag 9133
	fadescreenswapbuffers 0
	release
	end

SinjohRuins_RegirockRoom_EventScript_RegirockRan::
	release
	end

