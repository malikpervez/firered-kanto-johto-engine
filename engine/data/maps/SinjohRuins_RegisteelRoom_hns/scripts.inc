@ Johto (data/maps/SinjohRuins_RegisteelRoom_hns/scripts.inc), as built into the FireRed game.

SinjohRuins_RegisteelRoom_hns_MapScripts::
	.byte 0

SinjohRuins_RegisteelRoom_EventScript_Registeel::
	lock
	faceplayer
	playmoncry 379, 2
	waitmoncry
	seteventmon 379, 80
	special BattleSetup_StartLegendaryBattle
	waitstate
	specialvar 32781, GetBattleOutcome
	goto_if_eq 32781, 4, SinjohRuins_RegisteelRoom_EventScript_RegisteelRan
	fadescreenswapbuffers 1
	removeobject 1
	setflag 9134
	fadescreenswapbuffers 0
	release
	end

SinjohRuins_RegisteelRoom_EventScript_RegisteelRan::
	release
	end

