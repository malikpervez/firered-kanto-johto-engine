@ Johto (data/maps/EmbeddedTower_hns/scripts.inc), as built into the FireRed game.

EmbeddedTower_hns_MapScripts::
	.byte 0

EmbeddedTower_EventScript_Rayquaza::
	lock
	faceplayer
	playmoncry 384, 2
	waitmoncry
	seteventmon 384, 70
	special BattleSetup_StartLegendaryBattle
	waitstate
	specialvar 32781, GetBattleOutcome
	goto_if_eq 32781, 4, EmbeddedTower_EventScript_RayquazaRan
	fadescreenswapbuffers 1
	removeobject 1
	setflag 8262
	fadescreenswapbuffers 0
	release
	end

EmbeddedTower_EventScript_RayquazaRan::
	release
	end

