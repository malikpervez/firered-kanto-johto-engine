@ Johto (data/maps/GoldenrodCity_DepartmentStoreElevator_hns/scripts.inc), as built into the FireRed game.

GoldenrodCity_DepartmentStoreElevator_hns_MapScripts::
	map_script 2, GoldenrodDeptElevator_OnFrame
	.byte 0

GoldenrodDeptElevator_OnFrame::
	map_script_2 20564, 1, GoldenrodDeptElevator_EventScript_Exit
	.2byte 0

GoldenrodDeptElevator_EventScript_Exit::
	opendoor 9, 4
	opendoor 10, 6
	waitdooranim
	waitdooranim
	applymovement 255, J_Common_Movement_WalkDown1
	waitmovement 0
	applymovement 255, J_Common_Movement_WalkDown1
	waitmovement 0
	applymovement 255, J_Common_Movement_WalkDown1
	waitmovement 0
	closedoor 9, 4
	closedoor 10, 6
	waitdooranim
	waitdooranim
	setvar 20564, 0
	release
	end

GoldenrodDeptElevator_EventScript_Elevator::
	lock
	turnobject 255, DIR_NORTH
	delay 8
	opendoor 9, 4
	opendoor 10, 6
	waitdooranim
	waitdooranim
	applymovement 255, J_Common_Movement_WalkUp1
	waitmovement 0
	applymovement 255, J_Common_Movement_WalkUp1
	waitmovement 0
	closedoor 9, 4
	closedoor 10, 6
	waitdooranim
	waitdooranim
	multichoice 20, 0, 162, FALSE
	switch 32781
	case 0, GoldenrodDeptElevator_EventScript_F6
	case 1, GoldenrodDeptElevator_EventScript_F5
	case 2, GoldenrodDeptElevator_EventScript_F4
	case 3, GoldenrodDeptElevator_EventScript_F3
	case 4, GoldenrodDeptElevator_EventScript_F2
	case 5, GoldenrodDeptElevator_EventScript_F1
	case 6, GoldenrodDeptElevator_EventScript_F0
	case 7, GoldenrodDeptElevator_EventScript_Cancel
	case 127, GoldenrodDeptElevator_EventScript_Cancel
	closemessage
	end

GoldenrodDeptElevator_EventScript_F0::
	fadescreen 1
	playse 31
	setvar 20564, 1
	waitse
	warp MAP_GOLDENROD_CITY_DEPARTMENT_STORE_BASEMENT_HNS, 10, 5
	delay 60
	end

GoldenrodDeptElevator_EventScript_F1::
	fadescreen 1
	playse 31
	setvar 20564, 1
	waitse
	warp MAP_GOLDENROD_CITY_DEPARTMENT_STORE_1F_HNS, 9, 3
	delay 60
	end

GoldenrodDeptElevator_EventScript_F2::
	fadescreen 1
	playse 31
	setvar 20564, 1
	waitse
	warp MAP_GOLDENROD_CITY_DEPARTMENT_STORE_2F_HNS, 9, 3
	delay 60
	end

GoldenrodDeptElevator_EventScript_F3::
	fadescreen 1
	playse 31
	setvar 20564, 1
	waitse
	warp MAP_GOLDENROD_CITY_DEPARTMENT_STORE_3F_HNS, 9, 3
	delay 60
	end

GoldenrodDeptElevator_EventScript_F4::
	fadescreen 1
	playse 31
	setvar 20564, 1
	waitse
	warp MAP_GOLDENROD_CITY_DEPARTMENT_STORE_4F_HNS, 9, 3
	delay 60
	end

GoldenrodDeptElevator_EventScript_F5::
	fadescreen 1
	playse 31
	setvar 20564, 1
	waitse
	warp MAP_GOLDENROD_CITY_DEPARTMENT_STORE_5F_HNS, 9, 3
	delay 60
	end

GoldenrodDeptElevator_EventScript_F6::
	fadescreen 1
	playse 31
	setvar 20564, 1
	waitse
	warp MAP_GOLDENROD_CITY_DEPARTMENT_STORE_6F_HNS, 9, 3
	delay 60
	end

GoldenrodDeptElevator_EventScript_Cancel::
	closemessage
	opendoor 9, 4
	opendoor 10, 6
	waitdooranim
	waitdooranim
	applymovement 255, J_Common_Movement_WalkDown1
	waitmovement 0
	applymovement 255, J_Common_Movement_WalkDown1
	waitmovement 0
	applymovement 255, J_Common_Movement_WalkDown1
	waitmovement 0
	closedoor 9, 4
	closedoor 10, 6
	waitdooranim
	waitdooranim
	release
	end

CeladonDeptElevator_OnFrame::
	map_script_2 20564, 1, CeladonDeptElevator_EventScript_Exit
	.2byte 0

CeladonDeptElevator_EventScript_Exit::
	opendoor 6, 1
	opendoor 10, 6
	waitdooranim
	waitdooranim
	applymovement 255, J_Common_Movement_WalkDown1
	waitmovement 0
	applymovement 255, J_Common_Movement_WalkDown1
	waitmovement 0
	applymovement 255, J_Common_Movement_WalkDown1
	waitmovement 0
	closedoor 6, 1
	closedoor 10, 6
	waitdooranim
	waitdooranim
	setvar 20564, 0
	release
	end

CeladonDeptElevator_EventScript_Elevator::
	lock
	turnobject 255, DIR_NORTH
	delay 8
	opendoor 6, 1
	opendoor 10, 6
	waitdooranim
	waitdooranim
	applymovement 255, J_Common_Movement_WalkUp1
	waitmovement 0
	applymovement 255, J_Common_Movement_WalkUp1
	waitmovement 0
	closedoor 6, 1
	closedoor 10, 6
	waitdooranim
	waitdooranim
	multichoice 20, 0, 172, FALSE
	switch 32781
	case 0, CeladonDeptElevator_EventScript_F5
	case 1, CeladonDeptElevator_EventScript_F4
	case 2, CeladonDeptElevator_EventScript_F3
	case 3, CeladonDeptElevator_EventScript_F2
	case 4, CeladonDeptElevator_EventScript_F1
	case 5, CeladonDeptElevator_EventScript_Cancel
	case 127, CeladonDeptElevator_EventScript_Cancel
	closemessage
	end

CeladonDeptElevator_EventScript_F1::
	fadescreen 1
	playse 31
	setvar 20564, 1
	waitse
	warp MAP_CELADON_CITY_DEPARTMENT_STORE_1F_HNS, 6, 0
	delay 60
	end

CeladonDeptElevator_EventScript_F2::
	fadescreen 1
	playse 31
	setvar 20564, 1
	waitse
	warp MAP_CELADON_CITY_DEPARTMENT_STORE_2F_HNS, 6, 0
	delay 60
	end

CeladonDeptElevator_EventScript_F3::
	fadescreen 1
	playse 31
	setvar 20564, 1
	waitse
	warp MAP_CELADON_CITY_DEPARTMENT_STORE_3F_HNS, 6, 0
	delay 60
	end

CeladonDeptElevator_EventScript_F4::
	fadescreen 1
	playse 31
	setvar 20564, 1
	waitse
	warp MAP_CELADON_CITY_DEPARTMENT_STORE_4F_HNS, 6, 0
	delay 60
	end

CeladonDeptElevator_EventScript_F5::
	fadescreen 1
	playse 31
	setvar 20564, 1
	waitse
	warp MAP_CELADON_CITY_DEPARTMENT_STORE_5F_HNS, 6, 0
	delay 60
	end

CeladonDeptElevator_EventScript_Cancel::
	closemessage
	opendoor 6, 1
	opendoor 10, 6
	waitdooranim
	waitdooranim
	applymovement 255, J_Common_Movement_WalkDown1
	waitmovement 0
	applymovement 255, J_Common_Movement_WalkDown1
	waitmovement 0
	applymovement 255, J_Common_Movement_WalkDown1
	waitmovement 0
	closedoor 6, 1
	closedoor 10, 6
	waitdooranim
	waitdooranim
	release
	end

