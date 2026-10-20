@ Johto (data/scripts/cave_hole.inc), as built into the FireRed game.

J_CaveHole_CheckFallDownHole:
	map_script_2 VAR_ICE_STEP_COUNT, 0, J_EventScript_FallDownHole
	.2byte 0

J_CaveHole_FixCrackedGround:

	setvar VAR_ICE_STEP_COUNT, 1



	end

J_EventScript_FallDownHole::
	lockall
	delay 20
	applymovement LOCALID_PLAYER, J_Movement_SetInvisible
	waitmovement 0
	playse SE_FALL
	delay 60
	warphole MAP_UNDEFINED
	waitstate
	end

J_EventScript_FallDownHoleMtPyre::
	lockall
	delay 20
	applymovement LOCALID_PLAYER, J_Movement_SetInvisible
	waitmovement 0
	playse SE_FALL
	delay 60
	special DoFallWarp
	waitstate
	end

J_Movement_SetInvisible:
	set_invisible
	step_end

