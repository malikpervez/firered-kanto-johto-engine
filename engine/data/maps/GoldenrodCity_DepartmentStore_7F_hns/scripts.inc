@ Johto (data/maps/GoldenrodCity_DepartmentStore_7F_hns/scripts.inc), as built into the FireRed game.

GoldenrodCity_DepartmentStore_7F_hns_MapScripts::
	map_script 3, GoldenrodCity_DepartmentStore_7F_OnTransition
	.byte 0

GoldenrodCity_DepartmentStore_7F_OnTransition:
	call_if_set 8796, GoldenrodCity_DepartmentStore_7F_EventScript_SetNight
	call_if_unset 8796, GoldenrodCity_DepartmentStore_7F_EventScript_SetDay
	end

GoldenrodCity_DepartmentStore_7F_EventScript_SetNight::
	setmaplayoutindex 901
	return

GoldenrodCity_DepartmentStore_7F_EventScript_SetDay::
	setmaplayoutindex 900
	return

GoldenrodDeptStore7_EventScript_PokefanF::
	lock
	faceplayer
	msgbox GoldenrodDeptStore_Text_RoofPokefanF, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodDeptStore7_EventScript_PokefanM::
	lock
	faceplayer
	msgbox GoldenrodDeptStore_Text_RoofPokefanM, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodDeptStore7_EventScript_Twin::
	lock
	faceplayer
	msgbox GoldenrodDeptStore_Text_RoofTwin, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodDeptStore7_EventScript_Nerd::
	lock
	msgbox GoldenrodDeptStore_Text_RoofSuperNerdOhWow, MSGBOX_DEFAULT
	closemessage
	PLAYSE 21
	applymovement 1, J_Common_Movement_ExclamationMark
	delay 55
	waitmovement 1
	faceplayer
	msgbox GoldenrodDeptStore_Text_RoofSuperNerdQuitBotheringMe, MSGBOX_DEFAULT
	closemessage
	turnobject 1, DIR_SOUTH
	release
	end

GoldenrodDeptStore7_EventScript_Teacher::
	lock
	faceplayer
	msgbox GoldenrodDeptStore_Text_RoofTeacher, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodDeptStore7_EventScript_Bugcatcher::
	lock
	faceplayer
	msgbox GoldenrodDeptStore_Text_RoofBugCatcher, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodDeptStore_Text_RoofPokefanF:
	.string "Whew{SE_M_SUPERSONIC}I'{SE_M_MILK_DRINK}tired.\p"
	.string "{SE_M_HEAL_BELL}sometime{SE_M_GRASSWHISTLE}com{SE_M_REVERSAL}u{SE_M_MORNING_SUN}t{SE_M_ATTRACT2}th{SE_M_REVERSAL}rooftop\n"
	.string "t{SE_M_ATTRACT2}tak{SE_M_REVERSAL}{SE_M_CHARGE}brea{SE_M_ENCORE2}fro{SE_M_MILK_DRINK}shopping.$"

GoldenrodDeptStore_Text_RoofFisher:
	.string "Pardon{SE_M_SING}Wh{SE_M_ATTRACT2}say{SE_M_GRASSWHISTLE}a{SE_M_ATTRACT}adul{SE_M_SPIT_UP}can'{SE_M_SPIT_UP}get\n"
	.string "int{SE_M_ATTRACT2}this?\p"
	.string "I'{SE_M_MILK_DRINK}goin{SE_M_SANDSTORM}t{SE_M_ATTRACT2}b{SE_M_REVERSAL}bac{SE_M_ENCORE2}ever{SE_M_YAWN}da{SE_M_YAWN}to\n"
	.string "collec{SE_M_SPIT_UP}al{SE_M_BATON_PASS}th{SE_M_REVERSAL}dolls!$"

GoldenrodDeptStore_Text_RoofTwin:
	.string "The{SE_M_YAWN}hav{SE_M_REVERSAL}bargai{SE_M_ATTRACT}sale{SE_M_GRASSWHISTLE}her{SE_M_REVERSAL}every\n"
	.string "s{SE_M_ATTRACT2}often.$"

GoldenrodDeptStore_Text_RoofSuperNerdOhWow:
	.string "Oh{SE_M_SUPERSONIC}wow!$"

GoldenrodDeptStore_Text_RoofSuperNerdQuitBotheringMe:
	.string "Wil{SE_M_BATON_PASS}yo{SE_M_DIVE}qui{SE_M_SPIT_UP}botherin{SE_M_SANDSTORM}me?$"

GoldenrodDeptStore_Text_RoofPokefanM:
	.string "There'{SE_M_GRASSWHISTLE}somethin{SE_M_SANDSTORM}{SE_M_HEAL_BELL}reall{SE_M_YAWN}want,\n"
	.string "bu{SE_M_SPIT_UP}{SE_M_HEAL_BELL}don'{SE_M_SPIT_UP}hav{SE_M_REVERSAL}th{SE_M_REVERSAL}necessar{SE_M_YAWN}cash…\p"
	.string "Mayb{SE_M_REVERSAL}I'l{SE_M_BATON_PASS}sel{SE_M_BATON_PASS}of{SE_M_ACID_ARMOR}th{SE_M_REVERSAL}BERRIE{SE_M_SKETCH}I've\n"
	.string "collected…$"

GoldenrodDeptStore_Text_RoofTeacher:
	.string "Oh{SE_M_SUPERSONIC}everythin{SE_M_SANDSTORM}i{SE_M_GRASSWHISTLE}s{SE_M_ATTRACT2}cheap!\p"
	.string "{SE_M_HEAL_BELL}bough{SE_M_SPIT_UP}s{SE_M_ATTRACT2}much{SE_M_SUPERSONIC}m{SE_M_YAWN}PACK'{SE_M_GRASSWHISTLE}crammed!$"

GoldenrodDeptStore_Text_RoofBugCatcher:
	.string "M{SE_M_YAWN}POKéMO{SE_M_PSYBEAM2}alway{SE_M_GRASSWHISTLE}ge{SE_M_SPIT_UP}paralyze{SE_M_WATERFALL}or\n"
	.string "poisone{SE_M_WATERFALL}whe{SE_M_ATTRACT}th{SE_M_REVERSAL}chip{SE_M_GRASSWHISTLE}ar{SE_M_REVERSAL}down…\p"
	.string "S{SE_M_ATTRACT2}{SE_M_HEAL_BELL}cam{SE_M_REVERSAL}t{SE_M_ATTRACT2}bu{SE_M_YAWN}som{SE_M_REVERSAL}FUL{SE_M_BRICK_BREAK}HEAL.\p"
	.string "{SE_M_HEAL_BELL}wonde{SE_M_SAND_TOMB}i{SE_M_ACID_ARMOR}there'{SE_M_GRASSWHISTLE}an{SE_M_YAWN}left?$"

