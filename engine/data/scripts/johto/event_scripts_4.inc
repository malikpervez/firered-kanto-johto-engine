@ Johto (data/event_scripts.s), as built into the FireRed game.

J_Common_EventScript_FerryDepart::
	delay 60
	applymovement 32772, J_Movement_FerryDepart
	waitmovement 0
	return

J_Movement_FerryDepart:
	walk_slow_right
	walk_slow_right
	walk_slow_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

J_EventScript_HideMrBriney::
	setflag 0
	setflag 0
	setflag 0
	setflag 0
	setflag 0
	setflag 0
	setflag 0
	setflag 0
	setvar 20614, 0
	return

J_RusturfTunnel_EventScript_SetRusturfTunnelOpen::
	removeobject 1
	removeobject 10
	clearflag 0
	clearflag 0
	setvar 20618, 6
	setflag 0
	return

J_EventScript_UnusedBoardFerry::
	delay 30
	applymovement 255, J_Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	showplayer
	delay 30
	applymovement 255, J_Movement_UnusedBoardFerry
	waitmovement 0
	delay 30
	return

J_Movement_UnusedBoardFerry:
	walk_up
	step_end

J_Common_EventScript_FerryDepartIsland::
	call_if_eq 32780, DIR_SOUTH, Ferry_EventScript_DepartIslandSouth
	call_if_eq 32780, DIR_WEST, Ferry_EventScript_DepartIslandWest
	call_if_eq 32780, DIR_EAST, Ferry_EventScript_DepartIslandEast
	delay 30
	hideplayer
	call J_Common_EventScript_FerryDepart
	return

