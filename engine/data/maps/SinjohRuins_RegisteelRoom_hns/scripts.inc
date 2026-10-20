@ Johto (data/maps/SinjohRuins_RegisteelRoom_hns/scripts.inc), as built into the FireRed game.

SinjohRuins_RegisteelRoom_hns_MapScripts::
	.byte 0

SinjohRuins_RegisteelRoom_EventScript_Registeel::
	lock
	faceplayer
	playmoncry SPECIES_REGISTEEL, CRY_MODE_ENCOUNTER
	waitmoncry
	seteventmon SPECIES_REGISTEEL, 80
	special BattleSetup_StartLegendaryBattle
	waitstate
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, SinjohRuins_RegisteelRoom_EventScript_RegisteelRan
	fadescreenswapbuffers FADE_TO_BLACK
	removeobject LOCALID_SINJOHRUINS_REGISTEEL
	setflag JOHTO_FLAG_HIDE_SINJOHRUINS_REGISTEEL
	fadescreenswapbuffers FADE_FROM_BLACK
	release
	end

SinjohRuins_RegisteelRoom_EventScript_RegisteelRan::
	release
	end

