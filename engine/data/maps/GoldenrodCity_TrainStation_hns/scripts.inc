@ Johto (data/maps/GoldenrodCity_TrainStation_hns/scripts.inc), as built into the FireRed game.

GoldenrodCity_TrainStation_hns_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, GoldenrodCity_TrainStation_OnFrame
	.byte 0

GoldenrodCity_TrainStation_OnFrame::
	map_script_2 JOHTO_VAR_TRAIN, 1, GoldenrodCity_TrainStation_EventScript_ExitTrain
	.2byte 0

GoldenrodCity_TrainStation_EventScript_Attendant::
	lock
	faceplayer
	checkitem ITEM_PASS
	goto_if_eq VAR_RESULT, TRUE, GoldenrodCity_TrainStation_EventScript_BoardTrain
	goto_if_set JOHTO_FLAG_RETURNED_MACHINE_PART, GoldenrodCity_TrainStation_EventScript_Attendant2
	msgbox GoldenrodMagnetTrainStation_Text_OfficerTrainHasntComeIn, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_TrainStation_EventScript_Attendant2::
	msgbox GoldenrodMagnetTrainStation_Text_OfficerNoRailPass, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_TrainStation_EventScript_BoardTrain::
	msgbox GoldenrodMagnetTrainStation_Text_OfficerRightThisWay, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_GOLDENROD_CITY_TRAIN_STATION_ATTENDANT, GoldenrodCity_TrainStation_Movement_Attendant_Move_Up
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, GoldenrodCity_TrainStation_Movement_WalktoTrain
	waitmovement 0
	special SpawnCameraObject
	applymovement OBJ_EVENT_ID_PLAYER, J_Common_Movement_WalkUp1
	waitmovement 0
	playse SE_EXIT
	waitse
	fadescreen FADE_TO_BLACK

	applymovement OBJ_EVENT_ID_CAMERA, GoldenrodCity_TrainStation_Movement_CameraPanUp
	waitmovement 0
	applymovement OBJ_EVENT_ID_CAMERA, GoldenrodCity_TrainStation_Movement_CameraPanLeft
	waitmovement 0
	delay 60

	applymovement 7 GoldenrodCity_TrainStation_Movement_SlideRight
	applymovement OBJ_EVENT_ID_CAMERA, GoldenrodCity_TrainStation_Movement_SlideRight
	playbgm ((558 + 1) + 0x41), FALSE
	fadescreen FADE_FROM_BLACK
	playse SE_TRUCK_MOVE
	delay 220
	playse SE_TRUCK_STOP
	applymovement 7 GoldenrodCity_TrainStation_Movement_SlideRight
	applymovement OBJ_EVENT_ID_CAMERA, GoldenrodCity_TrainStation_Movement_SlideRight
	fadescreen FADE_TO_BLACK
	waitse
	special RemoveCameraObject
	setvar JOHTO_VAR_TRAIN, 0
	delay 60
	warp MAP_SAFFRON_CITY, 22, 15
	waitstate
	releaseall
	end

GoldenrodCity_TrainStation_EventScript_ExitTrain::
	lock
	applymovement LOCALID_GOLDENROD_CITY_TRAIN_STATION_ATTENDANT, GoldenrodCity_TrainStation_Movement_Attendant_Move_Up
	applymovement OBJ_EVENT_ID_PLAYER, GoldenrodCity_TrainStation_Movement_ExitTrain
	waitmovement 0
	waitmovement 0
	setvar JOHTO_VAR_TRAIN, 0
	applymovement LOCALID_GOLDENROD_CITY_TRAIN_STATION_ATTENDANT, GoldenrodCity_TrainStation_Movement_Attendant_Move_Down
	waitmovement 0
	release
	end

GoldenrodCity_TrainStation_EventScript_Gent::
	lock
	faceplayer
	msgbox GoldenrodMagnetTrainStation_Text_GentlemanPresident, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_TrainStation_EventScript_Boy::
	lock
	msgbox GoldenrodCity_TrainStation_Text_Boy, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_TrainStation_EventScript_Psychic::
	lock
	msgbox GoldenrodCity_TrainStation_Text_Psychic, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_TrainStation_Movement_ExitTrain:
	walk_down
	walk_left
	walk_left
	walk_left
	walk_down
	walk_down
	walk_down
	step_end

GoldenrodCity_TrainStation_Movement_Attendant_Move_Up:
	face_up
	walk_up
	walk_left
	face_right
	step_end

GoldenrodCity_TrainStation_Movement_Attendant_Move_Down:
	walk_right
	walk_down
	step_end

GoldenrodCity_TrainStation_Movement_WalktoTrain:
	walk_up
	walk_up
	walk_up
	walk_right
	walk_right
	walk_right
	walk_up
	walk_up
	step_end

GoldenrodCity_TrainStation_Movement_CameraPanUp:
	slide_up
	slide_up
	slide_up
	slide_up
	slide_up
	slide_up
	slide_up
	slide_up
	slide_up
	slide_up
	slide_up
	step_end

GoldenrodCity_TrainStation_Movement_CameraPanLeft:
	slide_left
	slide_left
	slide_left
	slide_left
	slide_left
	slide_left
	slide_left
	slide_left
	slide_left
	slide_left
	slide_left
	step_end

GoldenrodCity_TrainStation_Movement_SlideRight:
	slide_right
	slide_right
	slide_right
	slide_right
	slide_right
	slide_right
	slide_right
	slide_right
	slide_right
	slide_right
	slide_right
	slide_right
	slide_right
	slide_right
	slide_right
	slide_right
	slide_right
	slide_right
	slide_right
	slide_right
	slide_right
	slide_right
	slide_right
	slide_right
	slide_right
	slide_right
	slide_right
	slide_right
	slide_right
	slide_right
	slide_right
	slide_right
	slide_right
	slide_right
	slide_right
	slide_right
	slide_right
	slide_right
	slide_right
	slide_right
	slide_right
	slide_right
	slide_right
	slide_right
	slide_right
	slide_right
	slide_right
	slide_right
	slide_right
	slide_right
	slide_right
	slide_right
	slide_right
	slide_right
	slide_right
	slide_right
	slide_right
	slide_right
	slide_right
	slide_right
	slide_right
	slide_right
	slide_right
	slide_right
	slide_right
	slide_right
	slide_right
	slide_right
	slide_right
	slide_right
	slide_right
	slide_right
	slide_right
	slide_right
	slide_right
	slide_right
	slide_right
	slide_right
	slide_right
	slide_right
	slide_right
	slide_right
	slide_right
	slide_right
	slide_right
	slide_right
	slide_right
	slide_right
	slide_right
	slide_right
	slide_right
	slide_right
	slide_right
	slide_right
	slide_right
	slide_right
	slide_right
	slide_right
	slide_right
	slide_right
	slide_right
	slide_right
	slide_right
	slide_right
	slide_right
	slide_right
	slide_right
	slide_right
	slide_right
	slide_right
	slide_right
	slide_right
	slide_right
	slide_right
	slide_right
	slide_right
	slide_right
	slide_right
	slide_right
	slide_right
	slide_right
	slide_right
	slide_right
	slide_right
	slide_right
	slide_right
	slide_right
	slide_right
	slide_right
	slide_right
	slide_right
	slide_right
	slide_right
	slide_right
	step_end

GoldenrodMagnetTrainStation_Text_OfficerTrainHasntComeIn:
	.string "Th{SE_M_REVERSAL}trai{SE_M_ATTRACT}hasn'{SE_M_SPIT_UP}com{SE_M_REVERSAL}in…\p"
	.string "{SE_M_HEAL_BELL}know{SE_M_DRAGON_RAGE}I'l{SE_M_BATON_PASS}carr{SE_M_YAWN}th{SE_M_REVERSAL}passengers\n"
	.string "o{SE_M_ATTRACT}m{SE_M_YAWN}back!\p"
	.string "Tha{SE_M_SPIT_UP}won'{SE_M_SPIT_UP}work.$"

GoldenrodMagnetTrainStation_Text_OfficerRightThisWay:
	.string "Ma{SE_M_YAWN}{SE_M_HEAL_BELL}se{SE_M_REVERSAL}you{SE_M_SAND_TOMB}rai{SE_M_BATON_PASS}PASS{SE_M_SUPERSONIC}please?\p"
	.string "OK{SE_M_PERISH_SONG}Righ{SE_M_SPIT_UP}thi{SE_M_GRASSWHISTLE}way{SE_M_SUPERSONIC}please.$"

GoldenrodMagnetTrainStation_Text_OfficerNoRailPass:
	.string "Sorry{SE_M_PERISH_SONG}Yo{SE_M_DIVE}don'{SE_M_SPIT_UP}hav{SE_M_REVERSAL}{SE_M_CHARGE}rai{SE_M_BATON_PASS}PASS.$"

GoldenrodMagnetTrainStation_Text_GentlemanPresident:
	.string "I'{SE_M_MILK_DRINK}th{SE_M_REVERSAL}PRESIDENT.\p"
	.string "M{SE_M_YAWN}drea{SE_M_MILK_DRINK}wa{SE_M_GRASSWHISTLE}t{SE_M_ATTRACT2}buil{SE_M_WATERFALL}{SE_M_CHARGE}trai{SE_M_ATTRACT}that\n"
	.string "i{SE_M_GRASSWHISTLE}faste{SE_M_SAND_TOMB}tha{SE_M_ATTRACT}an{SE_M_YAWN}POKéMON.\p"
	.string "I{SE_M_SPIT_UP}reall{SE_M_YAWN}bring{SE_M_GRASSWHISTLE}JOHT{SE_M_SOLAR_BEAM}muc{SE_M_TRI_ATTACK}closer\n"
	.string "t{SE_M_ATTRACT2}KANTO.$"

GoldenrodCity_TrainStation_Text_Boy:
	.string "Yo{SE_M_DIVE}brough{SE_M_SPIT_UP}th{SE_M_REVERSAL}MAGNE{SE_M_SWIFT}TRAI{SE_M_PSYBEAM2}PASS,\n"
	.string "right?$"

GoldenrodCity_TrainStation_Text_Psychic:
	.string "{SE_M_HEAL_BELL}though{SE_M_SPIT_UP}yo{SE_M_DIVE}ha{SE_M_WATERFALL}it!$"

