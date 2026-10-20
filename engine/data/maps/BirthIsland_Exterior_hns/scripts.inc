@ Johto (data/maps/BirthIsland_Exterior_hns/scripts.inc), as built into the FireRed game.

BirthIsland_Exterior_hns_MapScripts::
	map_script 3, BirthIsland_Exterior_hns_OnTransition
	map_script 5, BirthIsland_Exterior_hns_OnResume
	map_script 7, BirthIsland_Exterior_hns_OnReturnToField
	.byte 0

BirthIsland_Exterior_hns_OnReturnToField:
	special SetDeoxysRockPalette
	end

BirthIsland_Exterior_hns_OnTransition:

	setflag 8931
	setvar 16400, 527
	setvar 20516, 0
	setvar 20517, 0
	call_if_set 8666, BirthIsland_Exterior_hns_EventScript_HideDeoxysAndPuzzle
	call_if_unset 8666, BirthIsland_Exterior_hns_EventScript_TryShowDeoxysPuzzle
	end

BirthIsland_Exterior_hns_EventScript_HideDeoxysAndPuzzle::
	setflag 8934
	setflag 8932
	return

BirthIsland_Exterior_hns_EventScript_TryShowDeoxysPuzzle::
	goto_if_set 8762, J_Common_EventScript_NopReturn
	clearflag 8932
	clearflag 8933
	return

BirthIsland_Exterior_hns_OnResume:
	call_if_set 10342, BirthIsland_Exterior_hns_EventScript_TryRemoveDeoxys
	end

BirthIsland_Exterior_hns_EventScript_TryRemoveDeoxys::
	specialvar 32781, GetBattleOutcome
	goto_if_ne 32781, 7, J_Common_EventScript_NopReturn
	removeobject 2
	return

BirthIsland_Exterior_hns_EventScript_Triangle::
	lock
	faceplayer
	special DoDeoxysRockInteraction
	waitstate
	switch 32781
	case DEOXYS_ROCK_FAILED, BirthIsland_Exterior_hns_EventScript_Failed
	case DEOXYS_ROCK_PROGRESSED, BirthIsland_Exterior_hns_EventScript_Progressed
	case DEOXYS_ROCK_SOLVED, BirthIsland_Exterior_hns_EventScript_Deoxys
	case DEOXYS_ROCK_COMPLETE, BirthIsland_Exterior_hns_EventScript_Complete
	end

BirthIsland_Exterior_hns_EventScript_Failed::
	release
	end

BirthIsland_Exterior_hns_EventScript_Progressed::
	release
	end

BirthIsland_Exterior_hns_EventScript_Complete::
	release
	end

BirthIsland_Exterior_hns_EventScript_Deoxys::
	waitse
	setfieldeffectargument 0, 1
	setfieldeffectargument 1, (MAP_BIRTH_ISLAND_EXTERIOR_HNS & 0xFF)
	setfieldeffectargument 2, (MAP_BIRTH_ISLAND_EXTERIOR_HNS >> 8)
	dofieldeffect 65
	playbgm 555, FALSE
	waitfieldeffect 65
	addobject 2
	applymovement 2, BirthIsland_Exterior_hns_Movement_DeoxysApproach
	waitmovement 0
	waitse
	playmoncry 386, 2
	delay 40
	waitmoncry
	setvar 32783, 2
	seteventmon 386, 70
	setflag 10342
	special BattleSetup_StartLegendaryBattle
	waitstate
	clearflag 10342
	specialvar 32781, GetBattleOutcome
	goto_if_eq 32781, 1, BirthIsland_Exterior_hns_EventScript_DefeatedDeoxys
	goto_if_eq 32781, 4, BirthIsland_Exterior_hns_EventScript_RanFromDeoxys
	goto_if_eq 32781, 5, BirthIsland_Exterior_hns_EventScript_RanFromDeoxys
	setflag 8666
	release
	end

BirthIsland_Exterior_hns_EventScript_DefeatedDeoxys::
	setflag 8762
	setvar 32772, 386
	goto J_Common_EventScript_LegendaryFlewAway
	end

BirthIsland_Exterior_hns_EventScript_RanFromDeoxys::
	setvar 32772, 386
	goto J_Common_EventScript_LegendaryFlewAway
	end

BirthIsland_Exterior_hns_Movement_DeoxysApproach:
	walk_slow_down
	walk_slow_down
	walk_slow_down
	walk_slow_down
	walk_slow_down
	walk_slow_down
	walk_slow_down
	step_end

BirthIsland_Exterior_hns_MeteorInteract::
	lock
	checkitem ITEM_METEORITE
	goto_if_eq 32781, TRUE, BirthIsland_Exterior_hns_GotMeteor
	setmetatile 21, 11, 0x001, FALSE
	special DrawWholeMapView
	giveitem ITEM_METEORITE
	release
	end

BirthIsland_Exterior_hns_GotMeteor::
	release
	end

