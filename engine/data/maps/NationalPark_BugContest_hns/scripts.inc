@ Johto (data/maps/NationalPark_BugContest_hns/scripts.inc), as built into the FireRed game.

NationalPark_BugContest_hns_MapScripts::
	map_script 3, NationalPark_BugContest_OnTransition
	map_script 2, NationalPark_BugContest_OnFrame
	.byte 0

NationalPark_BugContest_OnTransition::
	goto_if_eq 20552, 3, NationalPark_BugContest_EventScript_JudgeScene
	end

NationalPark_BugContest_OnFrame::
	map_script_2 20552, 1, NationalPark_BugContest_EventScript_Enter
	map_script_2 20552, 5, NationalPark_BugContest_EventScript_EnterSide
	map_script_2 20552, 3, NationalPark_BugContest_EventScript_JudgeSceneActivate
	.2byte 0

NationalPark_BugContest_EventScript_BC1::
	lock
	faceplayer
	msgbox NationalParkBugContest_Text_ContestantShaun, MSGBOX_DEFAULT
	closemessage
	release
	end

NationalPark_BugContest_EventScript_BC2::
	lock
	faceplayer
	msgbox NationalParkBugContest_Text_Contestant2A, MSGBOX_DEFAULT
	closemessage
	release
	end

NationalPark_BugContest_EventScript_Belinda::
	lock
	faceplayer
	msgbox NationalParkBugContest_Text_ContestantBelinda, MSGBOX_DEFAULT
	closemessage
	release
	end

NationalPark_BugContest_EventScript_Boy::
	lock
	faceplayer
	msgbox NationalParkBugContest_Text_Contestant6A, MSGBOX_DEFAULT
	closemessage
	release
	end

NationalPark_BugContest_EventScript_RelaxationSquare::
	lock
	msgbox NationalParkBugContest_Text_Sign_RelaxationSquare, MSGBOX_SIGN
	closemessage
	release
	end

NationalPark_BugContest_EventScript_BattleSign::
	lock
	msgbox NationalParkBugContest_Text_Sign_BattleNotice, MSGBOX_SIGN
	closemessage
	release
	end

NationalPark_BugContest_EventScript_TrainerTips::
	lock
	msgbox NationalParkBugContest_Text_TrainerTips, MSGBOX_SIGN
	closemessage
	release
	end

NationalPark_BugContest_EventScript_Trash::
	lock
	msgbox NationalPark_BugContest_Text_Trash, MSGBOX_SIGN
	closemessage
	release
	end

NationalPark_BugContest_EventScript_JudgeScene::
	special ShowBugContestChosenMon
	setobjectxyperm 32781, 20, 29
	setobjectxyperm 18, 24, 29
	setobjectxyperm 19, 22, 29
	setobjectxyperm 20, 18, 29
	setobjectxyperm 21, 16, 29

	setobjectxyperm 13, 18, 28
	setobjectxyperm 1, 22, 28
	setobjectxyperm 2, 24, 28
	setobjectxyperm 12, 16, 28
	setobjectxyperm 11, 20, 26

	setobjectmovementtype 13, 0x7
	setobjectmovementtype 1, 0x7
	setobjectmovementtype 2, 0x7
	setobjectmovementtype 12, 0x7
	setobjectmovementtype 11, 0x8
	end

NationalPark_BugContest_EventScript_JudgeSceneActivate::
	lockall
	turnobject 255, DIR_NORTH
	goto J_BugContestEventScript_Judging
	end

NationalPark_BugContest_EventScript_Enter::
	lockall
	applymovement 255, J_Common_Movement_WalkUp1
	waitmovement 0
	setvar 20552, 2
	msgbox NationlParkBugContest_Text_EnjoyTheContest, MSGBOX_DEFAULT
	closemessage
	releaseall
	end

NationalPark_BugContest_EventScript_EnterSide::
	lockall
	turnobject 255, DIR_WEST
	applymovement 255, J_Common_Movement_WalkLeft1
	waitmovement 0
	applymovement 255, J_Common_Movement_WalkLeft1
	waitmovement 0
	delay 20
	clearflag 8307
	addobject 17
	setvar 16385, 1
	setvar 20552, 2
	msgbox NationlParkBugContest_Text_EnjoyTheContest, MSGBOX_DEFAULT
	closemessage
	releaseall
	end

NationalPark_BugContest_EventScript_Trigger::
	lock
	turnobject 11, DIR_EAST
	goto NationalPark_BugContest_EventScript_RetireChoice

NationalPark_BugContest_EventScript_Attendant::
	lock
	faceplayer
	msgbox NationalParkBugContest_Text_Attendant, MSGBOX_YESNO
	goto_if_eq 32781, TRUE, J_BugContest_EventScript_TimesUp
	msgbox NationlParkBugContest_Text_EnjoyTheContest, MSGBOX_DEFAULT
	closemessage
	release
	end

NationalPark_BugContest_EventScript_RetireChoice::
	msgbox NationalParkBugContest_Text_Attendant, MSGBOX_YESNO
	goto_if_eq 32781, TRUE, J_BugContest_EventScript_TimesUp
	msgbox NationlParkBugContest_Text_EnjoyTheContest, MSGBOX_DEFAULT
	closemessage
	applymovement 255, J_Common_Movement_WalkUp1
	waitmovement 0
	release
	end

NationalPark_BugContest_Movement_AttendantSide:
	walk_in_place_left
	step_end

NationalPark_BugContest_Text_Trash:
	.string "Nothin{SE_M_SANDSTORM}here.$"

NationlParkBugContest_Text_EnjoyTheContest:
	.string "ATTENDANT{SE_M_HEAT_WAVE}Enjo{SE_M_YAWN}th{SE_M_REVERSAL}Contest!$"

NationalParkBugContest_Text_Attendant:
	.string "ATTENDANT{SE_M_HEAT_WAVE}Woul{SE_M_WATERFALL}yo{SE_M_DIVE}lik{SE_M_REVERSAL}t{SE_M_ATTRACT2}end\n"
	.string "th{SE_M_REVERSAL}contest?$"

NationalParkBugContest_Text_ContestantBelinda:
	.string "BELINDA{SE_M_HEAT_WAVE}I'{SE_M_MILK_DRINK}goin{SE_M_SANDSTORM}t{SE_M_ATTRACT2}win!\n"
	.string "Don'{SE_M_SPIT_UP}bothe{SE_M_SAND_TOMB}me.$"

NationalParkBugContest_Text_Contestant2A:
	.string "ED{SE_M_HEAT_WAVE}M{SE_M_YAWN}PARASEC{SE_M_SWIFT}put{SE_M_GRASSWHISTLE}POKéMO{SE_M_PSYBEAM2}to\n"
	.string "slee{SE_M_MORNING_SUN}wit{SE_M_TRI_ATTACK}SPORE.$"

NationalParkBugContest_Text_ContestantShaun:
	.string "SHAUN{SE_M_HEAT_WAVE}I'{SE_M_MILK_DRINK}no{SE_M_SPIT_UP}concerne{SE_M_WATERFALL}about\n"
	.string "winning.\p"
	.string "I'{SE_M_MILK_DRINK}jus{SE_M_SPIT_UP}lookin{SE_M_SANDSTORM}fo{SE_M_SAND_TOMB}rar{SE_M_REVERSAL}POKéMON.$"

NationalParkBugContest_Text_Contestant6A:
	.string "BARRY{SE_M_HEAT_WAVE}Yo{SE_M_DIVE}shoul{SE_M_WATERFALL}weake{SE_M_ATTRACT}bug\n"
	.string "POKéMO{SE_M_PSYBEAM2}first,\p"
	.string "the{SE_M_ATTRACT}thro{SE_M_TWISTER}{SE_M_CHARGE}BALL.$"

NationalParkBugContest_Text_Contestant7A:
	.string "CINDY{SE_M_HEAT_WAVE}{SE_M_HEAL_BELL}lov{SE_M_REVERSAL}bu{SE_M_SANDSTORM}POKéMON.\p"
	.string "{SE_M_HEAL_BELL}gues{SE_M_GRASSWHISTLE}yo{SE_M_DIVE}mus{SE_M_SPIT_UP}lik{SE_M_REVERSAL}the{SE_M_MILK_DRINK}too.$"

NationalParkBugContest_Text_Contestant8A:
	.string "JOSH{SE_M_HEAT_WAVE}I'v{SE_M_REVERSAL}bee{SE_M_ATTRACT}collectin{SE_M_SANDSTORM}bug\n"
	.string "POKéMO{SE_M_PSYBEAM2}sinc{SE_M_REVERSAL}{SE_M_HEAL_BELL}wa{SE_M_GRASSWHISTLE}jus{SE_M_SPIT_UP}{SE_M_CHARGE}baby.\p"
	.string "There'{SE_M_GRASSWHISTLE}n{SE_M_ATTRACT2}wa{SE_M_YAWN}I'{SE_M_MILK_DRINK}goin{SE_M_SANDSTORM}t{SE_M_ATTRACT2}lose!$"

NationalParkBugContest_Text_Contestant9A:
	.string "SAMUEL{SE_M_HEAT_WAVE}I{SE_M_ACID_ARMOR}you'v{SE_M_REVERSAL}go{SE_M_SPIT_UP}th{SE_M_REVERSAL}tim{SE_M_REVERSAL}to\n"
	.string "chat{SE_M_SUPERSONIC}g{SE_M_ATTRACT2}fin{SE_M_WATERFALL}som{SE_M_REVERSAL}bu{SE_M_SANDSTORM}POKéMON.$"

NationalParkBugContest_Text_Contestant10A:
	.string "KIPP{SE_M_HEAT_WAVE}I'v{SE_M_REVERSAL}studie{SE_M_WATERFALL}abou{SE_M_SPIT_UP}bug\n"
	.string "POKéMO{SE_M_PSYBEAM2}{SE_M_CHARGE}lot.\p"
	.string "I'{SE_M_MILK_DRINK}goin{SE_M_SANDSTORM}t{SE_M_ATTRACT2}wi{SE_M_ATTRACT}fo{SE_M_SAND_TOMB}sure.$"

NationalParkBugContest_Text_Sign_RelaxationSquare:
	.string "RELAXATIO{SE_M_PSYBEAM2}SQUARE\n"
	.string "NATIONA{SE_M_BRICK_BREAK}PARK$"

NationalParkBugContest_Text_Sign_BattleNotice:
	.string "Wha{SE_M_SPIT_UP}i{SE_M_GRASSWHISTLE}thi{SE_M_GRASSWHISTLE}notice?\p"
	.string "Pleas{SE_M_REVERSAL}battl{SE_M_REVERSAL}onl{SE_M_YAWN}i{SE_M_ATTRACT}th{SE_M_REVERSAL}grass.\p"
	.string "NATIONA{SE_M_BRICK_BREAK}PAR{SE_M_SNORE}WARDEN'{SE_M_SKETCH}OFFICE$"

NationalParkBugContest_Text_TrainerTips:
	.string "Th{SE_M_REVERSAL}NATIONA{SE_M_BRICK_BREAK}PAR{SE_M_SNORE}ha{SE_M_GRASSWHISTLE}different\n"
	.string "POKéMO{SE_M_PSYBEAM2}durin{SE_M_SANDSTORM}th{SE_M_REVERSAL}BUG-CATCHING\l"
	.string "CONTEST.$"

