@ Johto (data/maps/SSAqua_1F_hns/scripts.inc), as built into the FireRed game.

SSAqua_1F_hns_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, SSAqua_1F_OnFrame
	.byte 0

SSAqua_1F_OnFrame::
	map_script_2 JOHTO_VAR_SSAQUA_STATE, 5, SSAqua_1F_EventScript_Arrived
	.2byte 0

SSAqua_1F_EventScript_Arrived::
	lock
	setvar VAR_0x8004, 1
	setvar VAR_0x8005, 1
	setvar VAR_0x8006, 10
	setvar VAR_0x8007, 6
	special ShakeCamera
	waitstate
	playse SE_DING_DONG
	msgbox SSAqua_1F_Text_Sailor1_InVermilion, MSGBOX_DEFAULT
	closemessage
	setvar JOHTO_VAR_SSAQUA_STATE, 6
	release
	end

SSAqua_1F_EventScript_DoorSailor::
	lock
	faceplayer
	goto_if_ge JOHTO_VAR_SSAQUA_STATE, 5, SSAqua_1F_EventScript_DoorSailorArrived
	msgbox SSAqua_1F_Text_Sailor1_ToVermilion, MSGBOX_NPC
	end

SSAqua_1F_EventScript_DoorSailorArrived::
	msgbox SSAqua_1F_Text_SailorDoorArrived, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, TRUE, SSAqua_1F_EventScript_LeaveBoat
	closemessage
	release
	end

SSAqua_1F_EventScript_LeaveBoat::
	fadescreenswapbuffers FADE_TO_BLACK
	clearflag JOHTO_FLAG_HIDE_CELADON_FALKNER
	clearflag JOHTO_FLAG_HIDE_VIRIDIAN_BUGSY
	clearflag JOHTO_FLAG_HIDE_DEPTSTORE_WHITNEY
	clearflag JOHTO_FLAG_HIDE_BELLCHIME_MORTY
	clearflag JOHTO_FLAG_HIDE_CAFE_JASMINE
	clearflag JOHTO_FLAG_HIDE_LAKE_PRYCE
	clearflag JOHTO_FLAG_HIDE_DEN_CLAIR
	setvar JOHTO_VAR_SSAQUA_STATE, 7
	warp MAP_VERMILION_CITY, 13, 26
	waitstate
	release
	end

SSAqua_1F_EventScript_RoomSailor::
	msgbox SSAqua_1F_Text_Sailor2_FirstTime, MSGBOX_NPC
	end

SSAqua_1F_EventScript_Sailor3::
	msgbox SSAqua_1F_Text_Sailor3, MSGBOX_NPC
	end

SSAqua_1F_Trigger_Grandpa::
	lock
	clearflag JOHTO_FLAG_HIDE_SSAQUA_1F_GRANDPA
	getplayerxy VAR_TEMP_0, VAR_TEMP_1
	call_if_eq VAR_TEMP_0, 28, SSAqua_1F_EventScript_GrandpaEnterLeft
	call_if_eq VAR_TEMP_0, 29, SSAqua_1F_EventScript_GrandpaEnterRight
	applymovement OBJ_EVENT_ID_PLAYER, SSAqua_1F_Movement_PlayerSlideRight
	waitmovement 0
	applymovement LOCALID_SSAQUA_1F_GRANDPA, J_Common_Movement_WalkRight1
	waitmovement 0
	msgbox SSAqua_1F_Text_Grandpa, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SSAQUA_1F_GRANDPA, SSAqua_1F_Movement_GrandpaLeave
	waitmovement 0
	playse SE_DOOR
	removeobject LOCALID_SSAQUA_1F_GRANDPA

	setflag JOHTO_FLAG_HIDE_SSAQUA_1F_GRANDPA
	setflag JOHTO_FLAG_HIDE_SSAQUA_ROOM_SSE_GRANDDAUGHTER

	clearflag JOHTO_FLAG_HIDE_SSAQUA_SAILOR
	clearflag JOHTO_FLAG_HIDE_SSAQUA_CAPTAINS_ROOM_GRANDDAUGHTER

	setvar JOHTO_VAR_SSAQUA_STATE, 2
	release
	end

SSAqua_1F_EventScript_GrandpaEnterLeft::
	applymovement LOCALID_SSAQUA_1F_GRANDPA, SSAqua_1F_Movement_GrandpaEnterLeft
	waitmovement 0
	return

SSAqua_1F_EventScript_GrandpaEnterRight::
	applymovement LOCALID_SSAQUA_1F_GRANDPA, SSAqua_1F_Movement_GrandpaEnterRight
	waitmovement 0
	return

SSAqua_1F_Movement_GrandpaEnterLeft:
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	step_end

SSAqua_1F_Movement_GrandpaEnterRight:
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	step_end

SSAqua_1F_Movement_PlayerSlideRight:
	face_left
	lock_facing_direction
	walk_fast_right
	unlock_facing_direction
	step_end

SSAqua_1F_Movement_GrandpaLeave:
	walk_fast_down
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	step_end

SSAqua_1F_Text_Sailor1_ToVermilion:
	.string "FAS{SE_M_SWIFT}SHI{SE_M_PETAL_DANCE}S.S.AQU{SE_M_BONEMERANG}i{SE_M_GRASSWHISTLE}e{SE_M_ATTRACT}rout{SE_M_REVERSAL}to\n"
	.string "VERMILIO{SE_M_PSYBEAM2}CITY.\p"
	.string "W{SE_M_REVERSAL}wil{SE_M_BATON_PASS}mak{SE_M_REVERSAL}a{SE_M_ATTRACT}announcemen{SE_M_SPIT_UP}when\n"
	.string "w{SE_M_REVERSAL}arrive.$"

SSAqua_1F_Text_Sailor1_ToOlivine:
	.string "FAS{SE_M_SWIFT}SHI{SE_M_PETAL_DANCE}S.S.AQU{SE_M_BONEMERANG}i{SE_M_GRASSWHISTLE}e{SE_M_ATTRACT}rout{SE_M_REVERSAL}to\n"
	.string "OLIVIN{SE_M_SWORDS_DANCE}CITY.\p"
	.string "W{SE_M_REVERSAL}wil{SE_M_BATON_PASS}mak{SE_M_REVERSAL}a{SE_M_ATTRACT}announcemen{SE_M_SPIT_UP}when\n"
	.string "w{SE_M_REVERSAL}arrive.$"

SSAqua_1F_Text_Sailor2_FirstTime:
	.string "Here'{SE_M_GRASSWHISTLE}you{SE_M_SAND_TOMB}cabin.\p"
	.string "I{SE_M_ACID_ARMOR}you{SE_M_SAND_TOMB}POKéMO{SE_M_PSYBEAM2}ar{SE_M_REVERSAL}hurt{SE_M_SUPERSONIC}tak{SE_M_REVERSAL}a\n"
	.string "na{SE_M_MORNING_SUN}i{SE_M_ATTRACT}th{SE_M_REVERSAL}bed.\p"
	.string "Tha{SE_M_SPIT_UP}wil{SE_M_BATON_PASS}hea{SE_M_BATON_PASS}them.$"

SSAqua_1F_Text_Sailor3:
	.string "Th{SE_M_REVERSAL}passenger{SE_M_GRASSWHISTLE}ar{SE_M_REVERSAL}al{SE_M_BATON_PASS}trainers.\p"
	.string "They'r{SE_M_REVERSAL}al{SE_M_BATON_PASS}itchin{SE_M_SANDSTORM}t{SE_M_ATTRACT2}battl{SE_M_REVERSAL}in\n"
	.string "thei{SE_M_SAND_TOMB}cabins.$"

SSAqua_1F_Text_Grandpa:
	.string "Whoa{SE_M_DRAGON_RAGE}Excus{SE_M_REVERSAL}me{SE_M_PERISH_SONG}{SE_M_HEAL_BELL}wa{SE_M_GRASSWHISTLE}i{SE_M_ATTRACT}{SE_M_CHARGE}hurry!\p"
	.string "M{SE_M_YAWN}granddaughte{SE_M_SAND_TOMB}i{SE_M_GRASSWHISTLE}missing!\p"
	.string "She'{SE_M_GRASSWHISTLE}jus{SE_M_SPIT_UP}{SE_M_CHARGE}we{SE_M_REVERSAL}girl{SE_M_PERISH_SONG}I{SE_M_ACID_ARMOR}yo{SE_M_DIVE}see\n"
	.string "her{SE_M_SUPERSONIC}pleas{SE_M_REVERSAL}le{SE_M_SPIT_UP}m{SE_M_REVERSAL}know!$"

SSAqua_1F_Text_Sailor1_InOlivine:
	.string "FAS{SE_M_SWIFT}SHI{SE_M_PETAL_DANCE}S.S.AQU{SE_M_BONEMERANG}ha{SE_M_GRASSWHISTLE}arrive{SE_M_WATERFALL}in\n"
	.string "OLIVIN{SE_M_SWORDS_DANCE}CITY.$"

SSAqua_1F_Text_Sailor1_InVermilion:
	.string "FAS{SE_M_SWIFT}SHI{SE_M_PETAL_DANCE}S.S.AQU{SE_M_BONEMERANG}ha{SE_M_GRASSWHISTLE}arrive{SE_M_WATERFALL}in\n"
	.string "VERMILIO{SE_M_PSYBEAM2}CITY.$"

SSAqua_1F_Text_SailorDoorArrived:
	.string "W{SE_M_REVERSAL}hav{SE_M_REVERSAL}arrive{SE_M_WATERFALL}i{SE_M_ATTRACT}VERMILIO{SE_M_PSYBEAM2}CITY.\n"
	.string "Woul{SE_M_WATERFALL}yo{SE_M_DIVE}lik{SE_M_REVERSAL}t{SE_M_ATTRACT2}disembark?$"

