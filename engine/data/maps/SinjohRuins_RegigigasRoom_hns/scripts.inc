@ Johto (data/maps/SinjohRuins_RegigigasRoom_hns/scripts.inc), as built into the FireRed game.

SinjohRuins_RegigigasRoom_hns_MapScripts::
	.byte 0

SinjohRuins_RegigigasRoom_EventScript_Regigigas::
	lock
	faceplayer
	playmoncry 486, 2
	waitmoncry
	seteventmon 486, 80
	special BattleSetup_StartLegendaryBattle
	waitstate
	specialvar 32781, GetBattleOutcome
	goto_if_eq 32781, 4, SinjohRuins_RegigigasRoom_EventScript_RegigigasRan
	fadescreenswapbuffers 1
	removeobject 1
	setflag 9137
	fadescreenswapbuffers 0
	release
	end

SinjohRuins_RegigigasRoom_EventScript_RegigigasRan::
	release
	end

