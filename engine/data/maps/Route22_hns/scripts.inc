@ Johto (data/maps/Route22_hns/scripts.inc), as built into the FireRed game.

Route22_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route22_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, J_SetTimeEncounters
	.byte 0

Route22_OnTransition:
	callnative SetTimeBasedEncounters
	end

Route22_EventScript_Sign::
	msgbox Route22_Text_VictoryRoadEntranceSign, MSGBOX_NPC
	end

Route22_Text_VictoryRoadEntranceSign:
	.string "POKéMO{SE_M_PSYBEAM2}LEAGUE\p"
	.string "VICTOR{SE_M_MOONLIGHT}ROA{SE_M_FAINT_ATTACK}ENTRANCE$"

Route22_EventScript_ResetActivation::
	setvar VAR_TEMP_0, 0
	end

Route22_EventScript_DoNothing::
	setvar VAR_TEMP_0, 1
	end

Route22_EventScript_TriggerBottom::
	goto_if_ne JOHTO_VAR_ROUTE22_GIOVANNI_STATE, 0, Route22_EventScript_DoNothing
	specialvar VAR_RESULT, CheckCelebi
	goto_if_eq VAR_RESULT, FALSE, Route22_EventScript_DoNothing
	goto Route22_EventScript_Scene

Route22_EventScript_TriggerTop::
	goto_if_ne JOHTO_VAR_ROUTE22_GIOVANNI_STATE, 0, Route22_EventScript_DoNothing
	specialvar VAR_RESULT, CheckCelebi
	goto_if_eq VAR_RESULT, FALSE, Route22_EventScript_DoNothing
	goto Route22_EventScript_Scene

Route22_EventScript_TriggerMid::
	goto_if_ne JOHTO_VAR_ROUTE22_GIOVANNI_STATE, 0, Route22_EventScript_DoNothing
	specialvar VAR_RESULT, CheckCelebi
	goto_if_eq VAR_RESULT, FALSE, Route22_EventScript_DoNothing
	goto Route22_EventScript_Scene

Route22_EventScript_Scene::
	lock
	applymovement2 OBJ_EVENT_ID_FOLLOWER, Route22_Movement_CelebiBegin
	playse SE_LEDGE
	waitse
	playse SE_LEDGE
	waitse
	waitmovement 0
	playse SE_PIN
	applymovement2 OBJ_EVENT_ID_PLAYER, J_Common_Movement_ExclamationMark
	waitmovement OBJ_EVENT_ID_PLAYER
	turnobject OBJ_EVENT_ID_PLAYER, DIR_EAST
	playse SE_PIN
	applymovement2 OBJ_EVENT_ID_PLAYER, J_Common_Movement_QuestionMark
	waitmovement OBJ_EVENT_ID_PLAYER
	applymovement2 OBJ_EVENT_ID_FOLLOWER, Route22_Movement_CelebiSpin1
	playse SE_LEDGE
	waitse
	playse SE_LEDGE
	waitse
	playse SE_LEDGE
	waitse
	playse SE_LEDGE
	waitmovement 0
	fadescreenswapbuffers FADE_TO_WHITE
	playse SE_M_TELEPORT
	waitse
	delay 60
	playse SE_M_TELEPORT
	waitse
	clearflag JOHTO_FLAG_HIDE_ROUTE22_GIOVANNI_SILVER
	addobject LOCALID_ROUTE22_GIOVANNI
	addobject LOCALID_ROUTE22_SILVER
	waitse
	playbgm ((558 + 1) + 0x1E), FALSE
	fadescreenswapbuffers FADE_FROM_WHITE
	delay 50
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	special SpawnCameraObject
	applymovement2 OBJ_EVENT_ID_CAMERA, Route22_Movement_CameraPanLeft
	waitmovement 0
	delay 30
	applymovement2 LOCALID_ROUTE22_SILVER, J_Common_Movement_WalkLeft1
	waitmovement 0
	msgbox Route22_Text_Silver1, MSGBOX_DEFAULT
	closemessage
	delay 30
	applymovement2 LOCALID_ROUTE22_GIOVANNI, Route22_Movement_WalkInPlaceRight
	waitmovement 0
	msgbox Route22_Text_Giovanni1, MSGBOX_DEFAULT
	closemessage
	delay 30
	applymovement2 LOCALID_ROUTE22_SILVER, Route22_Movement_WalkInPlaceLeft
	waitmovement 0
	msgbox Route22_Text_Silver2, MSGBOX_DEFAULT
	closemessage
	delay 30
	applymovement2 LOCALID_ROUTE22_GIOVANNI, Route22_Movement_WalkInPlaceRight
	waitmovement 0
	msgbox Route22_Text_Giovanni2, MSGBOX_DEFAULT
	closemessage
	delay 10
	applymovement2 LOCALID_ROUTE22_SILVER, J_Common_Movement_WalkLeft1
	waitmovement 0
	msgbox Route22_Text_Silver3, MSGBOX_DEFAULT
	closemessage
	delay 30
	applymovement2 LOCALID_ROUTE22_GIOVANNI, Route22_Movement_WalkInPlaceLeft
	waitmovement 0
	msgbox Route22_Text_Giovanni3, MSGBOX_DEFAULT
	closemessage
	delay 30
	applymovement2 LOCALID_ROUTE22_GIOVANNI, Route22_Movement_GiovanniLeave
	waitmovement 0
	msgbox Route22_Text_Silver4, MSGBOX_DEFAULT
	closemessage
	delay 30
	applymovement2 LOCALID_ROUTE22_SILVER, J_Common_Movement_WalkLeft1
	waitmovement 0
	msgbox Route22_Text_Silver5, MSGBOX_DEFAULT
	closemessage
	delay 20
	playbgm ((558 + 1) + 0x3B), FALSE
	applymovement2 LOCALID_ROUTE22_SILVER, Route22_Movement_SilverStartLeave
	applymovement2 OBJ_EVENT_ID_CAMERA, Route22_Movement_CameraPanRight
	waitmovement LOCALID_ROUTE22_SILVER
	waitmovement OBJ_EVENT_ID_CAMERA
	special RemoveCameraObject
	turnobject OBJ_EVENT_ID_PLAYER, DIR_WEST
	playse SE_PIN
	applymovement2 LOCALID_ROUTE22_SILVER, J_Common_Movement_ExclamationMark
	delay 55
	waitmovement LOCALID_ROUTE22_SILVER
	msgbox Route22_Text_Silver6, MSGBOX_DEFAULT
	closemessage
	applymovement2 LOCALID_ROUTE22_SILVER, J_Common_Movement_WalkRight1
	applymovement2 OBJ_EVENT_ID_PLAYER, Route22_Movement_PlayerPushed
	applymovement2 OBJ_EVENT_ID_FOLLOWER, Route22_Movement_CelebiPush
	playse SE_LEDGE
	waitmovement LOCALID_ROUTE22_SILVER
	waitmovement OBJ_EVENT_ID_PLAYER
	waitmovement OBJ_EVENT_ID_FOLLOWER
	waitse
	applymovement2 LOCALID_ROUTE22_SILVER, Route22_Movement_SilverFinishLeave
	waitmovement 0
	setflag JOHTO_FLAG_HIDE_ROUTE22_GIOVANNI_SILVER
	removeobject LOCALID_ROUTE22_SILVER
	removeobject LOCALID_ROUTE22_GIOVANNI

	applymovement2 OBJ_EVENT_ID_FOLLOWER, Route22_Movement_CelebiBegin
	playse SE_LEDGE
	waitse
	playse SE_LEDGE
	waitse
	waitmovement 0
	playse SE_PIN
	applymovement2 OBJ_EVENT_ID_PLAYER, J_Common_Movement_ExclamationMark
	waitmovement OBJ_EVENT_ID_PLAYER
	turnobject OBJ_EVENT_ID_PLAYER, DIR_EAST
	delay 20
	playse SE_PIN
	applymovement2 OBJ_EVENT_ID_PLAYER, J_Common_Movement_QuestionMark
	waitmovement OBJ_EVENT_ID_PLAYER
	applymovement2 OBJ_EVENT_ID_FOLLOWER, Route22_Movement_CelebiSpin1
	playse SE_LEDGE
	waitse
	playse SE_LEDGE
	waitse


	playse SE_LEDGE
	waitse
	playse SE_LEDGE
	waitmovement 0
	fadescreenswapbuffers FADE_TO_WHITE
	playse SE_M_TELEPORT
	waitse
	delay 60
	playse SE_M_TELEPORT
	waitse
	fadedefaultbgm
	fadescreenswapbuffers FADE_FROM_WHITE
	setvar JOHTO_VAR_ROUTE22_GIOVANNI_STATE, 2
	setvar VAR_TEMP_0, 2
	release
	end

Route22_Movement_PlayerPushed:
	lock_facing_direction
	jump_up
	unlock_facing_direction
	step_end

Route22_EventScript_PlayerFaceSouth::
	turnobject OBJ_EVENT_ID_PLAYER, DIR_SOUTH
	return

Route22_EventScript_PlayerFaceWest::
	turnobject OBJ_EVENT_ID_PLAYER, DIR_WEST
	return

Route22_EventScript_PlayerFaceNorth::
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	return

Route22_EventScript_PlayerFaceEast::
	turnobject OBJ_EVENT_ID_PLAYER, DIR_EAST
	return

Route22_Movement_CameraPanLeft:
	walk_up
	walk_left
	walk_left
	step_end

Route22_Movement_CameraPanRight:
	walk_down
	walk_right
	walk_right
	step_end

Route22_Movement_WalkInPlaceLeft:
	walk_in_place_left
	step_end

Route22_Movement_WalkInPlaceRight:
	walk_in_place_right
	step_end

Route22_Movement_GiovanniLeave:
	walk_left
	walk_left
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

Route22_Movement_SilverStartLeave:
	walk_fast_down
	jump_2_down
	walk_fast_down
	walk_fast_right
	walk_fast_right
	walk_fast_right
	step_end

Route22_Movement_SilverFinishLeave:
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	step_end

Route22_Movement_CelebiBegin:
	jump_in_place_left
	jump_in_place_left
	step_end

Route22_Movement_CelebiSpin1:
	jump_in_place_left
	jump_in_place_left
	jump_in_place_left
	jump_in_place_left
	step_end

Route22_Movement_CelebiPush:
	walk_up
	face_down
	walk_in_place_down
	step_end

Route22_Text_Silver1:
	.string "{RIVAL}{SE_M_HEAT_WAVE}Yo{SE_M_DIVE}tol{SE_M_WATERFALL}me...\n"
	.string "yo{SE_M_DIVE}wer{SE_M_REVERSAL}th{SE_M_REVERSAL}numbe{SE_M_SAND_TOMB}on{SE_M_REVERSAL}i{SE_M_ATTRACT}th{SE_M_REVERSAL}whole\l"
	.string "world!\p"
	.string "Ar{SE_M_REVERSAL}yo{SE_M_DIVE}gonn{SE_M_CHARGE}quit?\p"
	.string "Wha{SE_M_SPIT_UP}ar{SE_M_REVERSAL}yo{SE_M_DIVE}goin{SE_M_SANDSTORM}t{SE_M_ATTRACT2}d{SE_M_ATTRACT2}now?$"

Route22_Text_Giovanni1:
	.string "....................\p"
	.string "GIOVANNI{SE_M_HEAT_WAVE}On{SE_M_REVERSAL}mus{SE_M_SPIT_UP}acknowledg{SE_M_REVERSAL}one's\n"
	.string "defea{SE_M_SPIT_UP}befor{SE_M_REVERSAL}h{SE_M_REVERSAL}ca{SE_M_ATTRACT}mov{SE_M_REVERSAL}on...\p"
	.string "{SE_M_HEAL_BELL}wil{SE_M_BATON_PASS}g{SE_M_ATTRACT2}solo..{SE_M_PERISH_SONG}fo{SE_M_SAND_TOMB}now...\p"
	.string "S{SE_M_ATTRACT2}tha{SE_M_SPIT_UP}on{SE_M_REVERSAL}da{SE_M_YAWN}{SE_M_HEAL_BELL}wil{SE_M_BATON_PASS}for{SE_M_MILK_DRINK}a\n"
	.string "stronge{SE_M_SAND_TOMB}organization!$"

Route22_Text_Silver2:
	.string "{RIVAL}{SE_M_HEAT_WAVE}Wha{SE_M_SPIT_UP}aspec{SE_M_SPIT_UP}o{SE_M_ACID_ARMOR}yo{SE_M_DIVE}was\n"
	.string "numbe{SE_M_SAND_TOMB}one?\p"
	.string "Gatherin{SE_M_SANDSTORM}s{SE_M_ATTRACT2}man{SE_M_YAWN}onl{SE_M_YAWN}t{SE_M_ATTRACT2}be\n"
	.string "defeate{SE_M_WATERFALL}b{SE_M_YAWN}{SE_M_CHARGE}mer{SE_M_REVERSAL}child!$"

Route22_Text_Giovanni2:
	.string "GIOVANNI{SE_M_HEAT_WAVE}Puttin{SE_M_SANDSTORM}togethe{SE_M_SAND_TOMB}the\n"
	.string "potentia{SE_M_BATON_PASS}o{SE_M_ACID_ARMOR}man{SE_M_YAWN}i{SE_M_GRASSWHISTLE}ho{SE_M_TWISTER}you\l"
	.string "produc{SE_M_REVERSAL}{SE_M_CHARGE}hug{SE_M_REVERSAL}power...\l"
	.string "That'{SE_M_GRASSWHISTLE}wha{SE_M_SPIT_UP}a{SE_M_ATTRACT}organizatio{SE_M_ATTRACT}is...\l"
	.string "That'{SE_M_GRASSWHISTLE}th{SE_M_REVERSAL}strengt{SE_M_TRI_ATTACK}o{SE_M_ACID_ARMOR}organization\p"
	.string "{SE_M_HEAL_BELL}failed..{SE_M_PERISH_SONG}t{SE_M_ATTRACT2}mak{SE_M_REVERSAL}th{SE_M_REVERSAL}bes{SE_M_SPIT_UP}us{SE_M_REVERSAL}of\n"
	.string "m{SE_M_YAWN}subordinates{SE_M_ABSORB}potential...!\p"
	.string "Bu{SE_M_SPIT_UP}yo{SE_M_DIVE}shal{SE_M_BATON_PASS}witnes{SE_M_GRASSWHISTLE}on{SE_M_REVERSAL}da{SE_M_YAWN}the\n"
	.string "reviva{SE_M_BATON_PASS}o{SE_M_ACID_ARMOR}m{SE_M_REVERSAL}an{SE_M_WATERFALL}m{SE_M_YAWN}TEA{SE_M_GIGA_DRAIN}ROCKET!$"

Route22_Text_Silver3:
	.string "{RIVAL}{SE_M_HEAT_WAVE}{SE_M_HEAL_BELL}don'{SE_M_SPIT_UP}understan{SE_M_WATERFALL}you!\p"
	.string "Yo{SE_M_DIVE}don'{SE_M_SPIT_UP}mak{SE_M_REVERSAL}an{SE_M_YAWN}sense!$"

Route22_Text_Giovanni3:
	.string ".......................\p"
	.string "GIOVANNI{SE_M_HEAT_WAVE}On{SE_M_REVERSAL}da{SE_M_YAWN}yo{SE_M_DIVE}will\n"
	.string "understand.$"

Route22_Text_Silver4:
	.string "{RIVAL}{SE_M_HEAT_WAVE}{SE_M_HEAL_BELL}don'{SE_M_SPIT_UP}wan{SE_M_SPIT_UP}to\n"
	.string "understan{SE_M_WATERFALL}you!\p"
	.string "{SE_M_HEAL_BELL}wil{SE_M_BATON_PASS}neve{SE_M_SAND_TOMB}becom{SE_M_REVERSAL}someon{SE_M_REVERSAL}like\n"
	.string "you.\p"
	.string "{SE_M_BONEMERANG}cowar{SE_M_WATERFALL}whe{SE_M_ATTRACT}you'r{SE_M_REVERSAL}alon{SE_M_REVERSAL}and\n"
	.string "actin{SE_M_SANDSTORM}lik{SE_M_REVERSAL}{SE_M_CHARGE}tyran{SE_M_SPIT_UP}whe{SE_M_ATTRACT}you're\l"
	.string "i{SE_M_ATTRACT}fron{SE_M_SPIT_UP}o{SE_M_ACID_ARMOR}othe{SE_M_SAND_TOMB}cowards!\p"
	.string "{SE_M_HEAL_BELL}wil{SE_M_BATON_PASS}becom{SE_M_REVERSAL}strong!\p"
	.string "{SE_M_HEAL_BELL}wil{SE_M_BATON_PASS}becom{SE_M_REVERSAL}{SE_M_CHARGE}stronge{SE_M_SAND_TOMB}ma{SE_M_ATTRACT}all\n"
	.string "b{SE_M_YAWN}myself!$"

Route22_Text_Silver5:
	.string "AL{SE_M_BRICK_BREAK}B{SE_M_MOONLIGHT}MYSELF!$"

Route22_Text_Silver6:
	.string "{RIVAL}{SE_M_HEAT_WAVE}..{SE_M_PERISH_SONG}Wha{SE_M_SPIT_UP}ar{SE_M_REVERSAL}yo{SE_M_DIVE}starin{SE_M_SANDSTORM}at?$"

