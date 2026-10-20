@ Johto (data/maps/SinjohRuins_RegiceRoom_hns/scripts.inc), as built into the FireRed game.

SinjohRuins_RegiceRoom_hns_MapScripts::
	.byte 0

SinjohRuins_RegiceRoom_EventScript_Regice::
	lock
	faceplayer
	playmoncry 378, 2
	waitmoncry
	seteventmon 378, 80
	special BattleSetup_StartLegendaryBattle
	waitstate
	specialvar 32781, GetBattleOutcome
	goto_if_eq 32781, 4, SinjohRuins_RegiceRoom_EventScript_RegiceRan
	fadescreenswapbuffers 1
	removeobject 1
	setflag 9132
	fadescreenswapbuffers 0
	release
	end

SinjohRuins_RegiceRoom_EventScript_RegiceRan::
	release
	end

