@ Johto (data/maps/Route28_hns/scripts.inc), as built into the FireRed game.

Route28_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route28_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, J_SetTimeEncounters
	.byte 0

Route28_OnTransition:
	callnative SetTimeBasedEncounters
	end

Route28_EventScript_Sign::
	msgbox Route28_Text_Sign, MSGBOX_SIGN
	end

Route28_EventScript_Item_Flamethrower::
	finditem ITEM_TM_FLAMETHROWER
	end

Route28_Text_Sign:
	.string "ROUT{SE_M_SWORDS_DANCE}28$"

Route28_EventScript_Trigger_Scientist::
	lock
	clearflag JOHTO_FLAG_HIDE_ROUTE28_SCIENTIST
	addobject LOCALID_ROUTE28_SCIENTIST
	special SpawnCameraObject
	applymovement2 OBJ_EVENT_ID_CAMERA, Route28_Movement_CameraPanDown
	waitmovement OBJ_EVENT_ID_CAMERA
	playse SE_POKENAV_CALL
	waitse
	msgbox Route28_Text_Scientist, MSGBOX_DEFAULT
	playse SE_POKENAV_HANG_UP
	msgbox Route28_Text_Scientist2, MSGBOX_DEFAULT
	closemessage
	applymovement2 LOCALID_ROUTE28_SCIENTIST, Route28_Movement_ScientistLeave
	waitmovement LOCALID_ROUTE28_SCIENTIST
	applymovement2 OBJ_EVENT_ID_CAMERA, Route28_Movement_CameraPanUp
	waitmovement OBJ_EVENT_ID_CAMERA
	special RemoveCameraObject
	setvar JOHTO_VAR_ROUTE28_SCIENTIST, 2
	setflag JOHTO_FLAG_HIDE_ROUTE28_SCIENTIST
	removeobject LOCALID_ROUTE28_SCIENTIST
	release
	end

Route28_Movement_CameraPanDown:
	walk_down
	walk_down
	walk_down
	walk_diag_southwest
	walk_diag_southwest
	step_end

Route28_Movement_CameraPanUp:
	walk_diag_northeast
	walk_diag_northeast
	walk_up
	walk_up
	walk_up
	step_end

Route28_Movement_ScientistLeave:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

Route28_Text_Scientist:
	.string "Hiya{SE_M_SUPERSONIC}Boss.\p"
	.string "Yes{SE_M_SUPERSONIC}I'v{SE_M_REVERSAL}foun{SE_M_WATERFALL}severa{SE_M_BATON_PASS}artifacts,\n"
	.string "bu{SE_M_SPIT_UP}n{SE_M_ATTRACT2}sig{SE_M_ATTRACT}o{SE_M_ACID_ARMOR}th{SE_M_REVERSAL}AZUR{SE_M_SWORDS_DANCE}FLUTE.\p"
	.string "I{SE_M_SPIT_UP}ma{SE_M_YAWN}b{SE_M_REVERSAL}insid{SE_M_REVERSAL}th{SE_M_REVERSAL}MOUNTAIN{SE_M_SUPERSONIC}but\n"
	.string "th{SE_M_REVERSAL}wil{SE_M_WATERFALL}POKéMO{SE_M_PSYBEAM2}her{SE_M_REVERSAL}ar{SE_M_REVERSAL}strong,\l"
	.string "an{SE_M_WATERFALL}m{SE_M_YAWN}tea{SE_M_MILK_DRINK}need{SE_M_GRASSWHISTLE}som{SE_M_REVERSAL}rest...\p"
	.string "..................\p"
	.string "You'r{SE_M_REVERSAL}breakin{SE_M_SANDSTORM}up...\l"
	.string "Boss....?\p"
	.string "I'{SE_M_MILK_DRINK}goin{SE_M_SANDSTORM}t{SE_M_ATTRACT2}th{SE_M_REVERSAL}POKéMO{SE_M_PSYBEAM2}CENTER.\p"
	.string "I'l{SE_M_BATON_PASS}cal{SE_M_BATON_PASS}bac{SE_M_ENCORE2}i{SE_M_ACID_ARMOR}{SE_M_HEAL_BELL}fin{SE_M_WATERFALL}th{SE_M_REVERSAL}FLUTE.$"

Route28_Text_Scientist2:
	.string ".......CLICK\p"
	.string "Th{SE_M_REVERSAL}signa{SE_M_BATON_PASS}i{SE_M_ATTRACT}SINJO{SE_M_SWAGGER2}sucks...$"

