@ Johto (data/scripts/elite_four.inc), as built into the FireRed game.

J_PokemonLeague_EliteFour_SetAdvanceToNextRoomMetatiles::
	applymovement 255, J_Common_Movement_Delay32
	waitmovement 0
	playse 8
	setmetatile 6, 1, 0x344, FALSE
	setmetatile 6, 2, 0x345, FALSE
	setmetatile 0, 2, 0x2DE, TRUE
	setmetatile 1, 2, 0x2DD, TRUE
	setmetatile 2, 2, 0x2DE, TRUE
	setmetatile 3, 2, 0x2DD, TRUE
	setmetatile 4, 2, 0x2DE, TRUE
	setmetatile 8, 2, 0x2DD, TRUE
	setmetatile 9, 2, 0x2DE, TRUE
	setmetatile 10, 2, 0x2DD, TRUE
	setmetatile 11, 2, 0x2DE, TRUE
	setmetatile 12, 2, 0x2DD, TRUE
	special DrawWholeMapView
	return

J_PokemonLeague_EliteFour_EventScript_WalkInCloseDoor::
	applymovement 255, J_Common_Movement_WalkUp6
	waitmovement 0
	playse 52
	setmetatile 5, 12, 0x206, TRUE
	setmetatile 6, 12, 0x206, TRUE
	setmetatile 7, 12, 0x206, TRUE
	setmetatile 5, 13, 0x20E, TRUE
	setmetatile 6, 13, 0x20E, TRUE
	setmetatile 7, 13, 0x20E, TRUE
	special DrawWholeMapView
	return

J_PokemonLeague_EliteFour_EventScript_ResetAdvanceToNextRoom::
	setmetatile 6, 1, 0x344, FALSE
	setmetatile 6, 2, 0x345, FALSE
	setmetatile 5, 12, 0x206, TRUE
	setmetatile 6, 12, 0x206, TRUE
	setmetatile 7, 12, 0x206, TRUE
	setmetatile 5, 13, 0x20E, TRUE
	setmetatile 6, 13, 0x20E, TRUE
	setmetatile 7, 13, 0x20E, TRUE
	setmetatile 0, 2, 0x2DE, TRUE
	setmetatile 1, 2, 0x2DD, TRUE
	setmetatile 2, 2, 0x2DE, TRUE
	setmetatile 3, 2, 0x2DD, TRUE
	setmetatile 4, 2, 0x2DE, TRUE
	setmetatile 8, 2, 0x2DD, TRUE
	setmetatile 9, 2, 0x2DE, TRUE
	setmetatile 10, 2, 0x2DD, TRUE
	setmetatile 11, 2, 0x2DE, TRUE
	setmetatile 12, 2, 0x2DD, TRUE
	return

J_PokemonLeague_EliteFour_EventScript_CloseDoor::
	setmetatile 5, 12, 0x206, TRUE
	setmetatile 6, 12, 0x206, TRUE
	setmetatile 7, 12, 0x206, TRUE
	setmetatile 5, 13, 0x20E, TRUE
	setmetatile 6, 13, 0x20E, TRUE
	setmetatile 7, 13, 0x20E, TRUE
	return

