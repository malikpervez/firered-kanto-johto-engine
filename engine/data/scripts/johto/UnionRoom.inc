@ Johto (data/maps/UnionRoom/scripts.inc), as built into the FireRed game.

J_UnionRoom_MapScripts::
	map_script 5, UnionRoom_OnResume
	map_script 3, UnionRoom_OnTransition
	.byte 0

UnionRoom_OnResume:
	setflag 0
	setflag 0
	setflag 0
	setflag 0
	setflag 0
	setflag 0
	setflag 0
	setflag 0
	removeobject 9
	removeobject 8
	removeobject 7
	removeobject 2
	removeobject 6
	removeobject 5
	removeobject 4
	removeobject 3
	special RunUnionRoom
	end

UnionRoom_OnTransition:
	setflag 14
	end

J_UnionRoom_EventScript_Player1::
	lock
	faceplayer
	setvar 32781, 1
	waitstate
	release
	end

J_UnionRoom_EventScript_Player2::
	lock
	faceplayer
	setvar 32781, 2
	waitstate
	release
	end

J_UnionRoom_EventScript_Player3::
	lock
	faceplayer
	setvar 32781, 3
	waitstate
	release
	end

J_UnionRoom_EventScript_Player4::
	lock
	faceplayer
	setvar 32781, 4
	waitstate
	release
	end

J_UnionRoom_EventScript_Player5::
	lock
	faceplayer
	setvar 32781, 5
	waitstate
	release
	end

J_UnionRoom_EventScript_Player6::
	lock
	faceplayer
	setvar 32781, 6
	waitstate
	release
	end

J_UnionRoom_EventScript_Player7::
	lock
	faceplayer
	setvar 32781, 7
	waitstate
	release
	end

J_UnionRoom_EventScript_Player8::
	lock
	faceplayer
	setvar 32781, 8
	waitstate
	release
	end

J_UnionRoom_EventScript_Attendant::
	lock
	faceplayer
	setvar 32781, 9
	waitstate
	release
	end

J_UnionRoom_EventScript_Unused::
	lockall
	setvar 32781, 10
	waitstate
	releaseall
	end

