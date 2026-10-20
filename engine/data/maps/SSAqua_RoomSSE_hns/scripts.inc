@ Johto (data/maps/SSAqua_RoomSSE_hns/scripts.inc), as built into the FireRed game.

SSAqua_RoomSSE_hns_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, SSAqua_RoomSSE_OnFrame
	map_script MAP_SCRIPT_ON_TRANSITION, SSAqua_RoomSSE_OnTransition
	.byte 0

SSAqua_RoomSSE_OnTransition::
	goto_if_ge JOHTO_VAR_SSAQUA_STATE, 5, SSAqua_RoomSSE_SetGirlPos
	end

SSAqua_RoomSSE_OnFrame::
	map_script_2 JOHTO_VAR_SSAQUA_STATE, 4, SSAqua_RoomSSE_EventScript_ReuinionScene
	.2byte 0

SSAqua_RoomSSE_SetGirlPos::
	setobjectxyperm LOCALID_SSAQUA_ROOM_SSE_GRANDDAUGTHER, 2, 4
	setobjectmovementtype LOCALID_SSAQUA_ROOM_SSE_GRANDDAUGTHER, MOVEMENT_TYPE_FACE_LEFT
	end

SSAqua_RoomSSE_EventScript_ReuinionScene::
	lock
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	turnobject LOCALID_SSAQUA_ROOM_SSE_GRANDFATHER, DIR_SOUTH
	playse SE_PIN
	applymovement LOCALID_SSAQUA_ROOM_SSE_GRANDFATHER, J_Common_Movement_ExclamationMark
	delay 55
	waitmovement LOCALID_SSAQUA_ROOM_SSE_GRANDFATHER
	applymovement LOCALID_SSAQUA_ROOM_SSE_GRANDDAUGTHER, SSAqua_RoomSSE_Movement_GirlEnter
	waitmovement 0
	turnobject LOCALID_SSAQUA_ROOM_SSE_GRANDFATHER, DIR_EAST
	msgbox SSAqua_RoomSSE_Text_GranddaughterWasPlaying, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, SSAqua_RoomSSE_Movement_PlayerEnter
	waitmovement 0
	turnobject LOCALID_SSAQUA_ROOM_SSE_GRANDFATHER, DIR_SOUTH
	msgbox SSAqua_RoomSSE_Text_EntertainedGranddaughter, MSGBOX_DEFAULT
	msgbox SSAqua_RoomSSE_Text_GrandpaHaveThis, MSGBOX_DEFAULT
	giveitem ITEM_METAL_COAT
	closemessage
	setvar JOHTO_VAR_SSAQUA_STATE, 5
	release
	end

SSAqua_RoomSSE_EventScript_Grandpa::
	lock
	faceplayer
	goto_if_ge JOHTO_VAR_SSAQUA_STATE, 4, SSAqua_RoomSSE_EventScript_GrandpaAfter
	msgbox SSAqua_RoomSSE_Text_CantFindGranddaughter, MSGBOX_DEFAULT
	closemessage
	release
	end

SSAqua_RoomSSE_EventScript_GrandpaAfter::
	msgbox SSAqua_RoomSSE_Text_GrandpaTravelling, MSGBOX_DEFAULT
	closemessage
	release
	end

SSAqua_RoomSSE_EventScript_GrandDaughter::
	msgbox SSAqua_RoomSSE_Text_GranddaughterHadFun, MSGBOX_NPC
	end

SSAqua_RoomSSE_Movement_GirlEnter:
	walk_up
	walk_up
	walk_left
	step_end

SSAqua_RoomSSE_Movement_PlayerEnter:
	walk_up
	walk_left
	walk_left
	walk_up
	step_end

SSAqua_RoomSSE_Text_CantFindGranddaughter:
	.string "Oh{SE_M_SUPERSONIC}hello…\p"
	.string "{SE_M_HEAL_BELL}stil{SE_M_BATON_PASS}can'{SE_M_SPIT_UP}fin{SE_M_WATERFALL}my\n"
	.string "granddaughter.\p"
	.string "I{SE_M_ACID_ARMOR}she'{SE_M_GRASSWHISTLE}o{SE_M_ATTRACT}th{SE_M_REVERSAL}ship,\n"
	.string "that'{SE_M_GRASSWHISTLE}OK.\p"
	.string "She'{SE_M_GRASSWHISTLE}a{SE_M_ATTRACT}energeti{SE_M_HYPER_BEAM}child,\n"
	.string "s{SE_M_ATTRACT2}sh{SE_M_REVERSAL}ma{SE_M_YAWN}b{SE_M_REVERSAL}buggin{SE_M_SANDSTORM}someone\l"
	.string "I'{SE_M_MILK_DRINK}worried…$"

SSAqua_RoomSSE_Text_EntertainedGranddaughter:
	.string "{PLAYER}{SE_M_SUPERSONIC}wa{SE_M_GRASSWHISTLE}it?\n"
	.string "{SE_M_HEAL_BELL}hear{SE_M_WATERFALL}yo{SE_M_DIVE}entertaine{SE_M_WATERFALL}my\l"
	.string "granddaughter.\p"
	.string "{SE_M_HEAL_BELL}wan{SE_M_SPIT_UP}t{SE_M_ATTRACT2}than{SE_M_ENCORE2}yo{SE_M_DIVE}fo{SE_M_SAND_TOMB}that.$"

SSAqua_RoomSSE_Text_GrandpaHaveThis:
	.string "{SE_M_HEAL_BELL}know{SE_M_DRAGON_RAGE}I'{SE_M_WATERFALL}lik{SE_M_REVERSAL}you\n"
	.string "t{SE_M_ATTRACT2}hav{SE_M_REVERSAL}this!$"

SSAqua_RoomSSE_Text_GrandpaTravelling:
	.string "We'r{SE_M_REVERSAL}travelin{SE_M_SANDSTORM}around\n"
	.string "th{SE_M_REVERSAL}world.$"

SSAqua_RoomSSE_Text_GranddaughterWasPlaying:
	.string "Grandpa{SE_M_SUPERSONIC}her{SE_M_REVERSAL}{SE_M_HEAL_BELL}am!\n"
	.string "{SE_M_HEAL_BELL}wa{SE_M_GRASSWHISTLE}playin{SE_M_SANDSTORM}with\l"
	.string "th{SE_M_REVERSAL}CAPTAI{SE_M_PSYBEAM2}an{SE_M_WATERFALL}thi{SE_M_GRASSWHISTLE}person!$"

SSAqua_RoomSSE_Text_GranddaughterHadFun:
	.string "{SE_M_HEAL_BELL}ha{SE_M_WATERFALL}lot{SE_M_GRASSWHISTLE}o{SE_M_ACID_ARMOR}fu{SE_M_ATTRACT}playing!$"

