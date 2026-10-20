@ Johto (data/maps/MahoganyTown_Shop_hns/scripts.inc), as built into the FireRed game.

MahoganyTown_Shop_hns_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, MahoganyTown_Shop_OnLoad
	map_script MAP_SCRIPT_ON_FRAME_TABLE, MahoganyTown_Shop_OnFrame
	.byte 0

MahoganyTown_Shop_OnLoad:
	goto_if_ge JOHTO_VAR_MAHOGANY_TOWN_STATE, 5, MahoganyTown_Shop_SetStairs
	end

MahoganyTown_Shop_SetStairs::
	setmetatile 8, 4, 0x28D, FALSE
	end

MahoganyTown_Shop_OnFrame::
	map_script_2 JOHTO_VAR_MAHOGANY_TOWN_STATE, 4, MahoganyTown_Shop_EventScript_Raid
	.2byte 0

MahoganyTown_Shop_EventScript_Raid::
	playbgm ((558 + 1) + 0x32), FALSE
	lock
	playse SE_PIN
	applymovement OBJ_EVENT_ID_PLAYER, J_Common_Movement_ExclamationMark
	waitmovement OBJ_EVENT_ID_PLAYER
	msgbox MahoganyMart1F_Text_Lance_HyperBeam, MSGBOX_DEFAULT
	closemessage
	playse SE_M_HYPER_BEAM
	applymovement LOCALID_MAHOGANYSHOP_DRAGONITE, MahoganyTown_Shop_Movement_Dragonite1
	delay 10
	applymovement LOCALID_MAHOGANYSHOP_ROCKET, MahoganyTown_Shop_Movement_Rocket1
	waitmovement LOCALID_MAHOGANYSHOP_ROCKET
	waitse
	setvar VAR_0x8004, 1
	setvar VAR_0x8005, 1
	setvar VAR_0x8006, 5
	setvar VAR_0x8007, 6
	special ShakeCamera
	waitmovement LOCALID_MAHOGANYSHOP_DRAGONITE
	waitse
	delay 10
	turnobject LOCALID_MAHOGANYSHOP_LANCE, DIR_SOUTH
	delay 50
	applymovement LOCALID_MAHOGANYSHOP_LANCE, MahoganyTown_Shop_Movement_LanceGreetPlayer
	waitmovement 0
	msgbox MahoganyMart1F_Text_Lance_Radio, MSGBOX_DEFAULT
	closemessage
	playse SE_PIN
	applymovement LOCALID_MAHOGANYSHOP_DRAGONITE, J_Common_Movement_QuestionMark
	delay 55
	waitmovement LOCALID_MAHOGANYSHOP_DRAGONITE
	applymovement LOCALID_MAHOGANYSHOP_DRAGONITE, MahoganyTown_Shop_Movement_DragoniteGotoBox
	waitmovement 0
	playmoncry SPECIES_DRAGONITE, CRY_MODE_NORMAL
	waitmovement 0
	applymovement LOCALID_MAHOGANYSHOP_LANCE, MahoganyTown_Shop_Movement_LanceGotoBox
	applymovement OBJ_EVENT_ID_PLAYER, MahoganyTown_Shop_Movement_PlayerGotoBox
	waitmovement LOCALID_MAHOGANYSHOP_LANCE
	waitmovement OBJ_EVENT_ID_PLAYER

	playse SE_M_HYPER_BEAM
	applymovement LOCALID_MAHOGANYSHOP_DRAGONITE, MahoganyTown_Shop_Movement_Dragonite2
	delay 20
	waitse
	setvar VAR_0x8004, 1
	setvar VAR_0x8005, 1
	setvar VAR_0x8006, 5
	setvar VAR_0x8007, 6
	special ShakeCamera

	waitmovement 0

	setmetatile 8, 4, 0x28D, FALSE
	special DrawWholeMapView
	delay 40
	msgbox MahoganyMart1F_Text_Lance_Stairs, MSGBOX_DEFAULT
	turnobject LOCALID_MAHOGANYSHOP_DRAGONITE, DIR_WEST
	playmoncry SPECIES_DRAGONITE, CRY_MODE_NORMAL
	waitmoncry
	turnobject LOCALID_MAHOGANYSHOP_DRAGONITE, DIR_EAST

	turnobject LOCALID_MAHOGANYSHOP_LANCE, DIR_SOUTH
	msgbox MahoganyMart1F_Text_Lance_SplitUp, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_MAHOGANYSHOP_DRAGONITE, J_Common_Movement_WalkRight1
	waitmovement 0
	removeobject LOCALID_MAHOGANYSHOP_DRAGONITE
	playse SE_EXIT
	applymovement LOCALID_MAHOGANYSHOP_LANCE, J_Common_Movement_WalkRight1
	waitmovement 0
	applymovement LOCALID_MAHOGANYSHOP_LANCE, J_Common_Movement_WalkRight1
	waitmovement 0
	removeobject LOCALID_MAHOGANYSHOP_LANCE
	playse SE_EXIT
	delay 50

	playse SE_PIN
	applymovement 2 J_Common_Movement_ExclamationMark
	delay 55
	waitmovement LOCALID_MAHOGANYSHOP_ROCKET
	applymovement 2 MahoganyTown_Shop_Movement_RocketLeave
	waitmovement 0
	removeobject LOCALID_MAHOGANYSHOP_ROCKET
	playse SE_EXIT
	setflag JOHTO_FLAG_HIDE_MAHOGANY_TOWN_SHOP_NPCS


	setvar JOHTO_VAR_MAHOGANY_TOWN_STATE, 5
	release
	end

MahoganyTown_Shop_Movement_RocketLeave:
	walk_faster_left
	walk_faster_left
	walk_faster_up
	walk_faster_up
	walk_faster_up
	walk_faster_up
	walk_faster_right
	walk_faster_right
	step_end

MahoganyTown_Shop_Movement_Dragonite1:
	lock_facing_direction
	walk_fast_right
	walk_fast_right
	walk_fast_left
	walk_fast_left
	unlock_facing_direction
	step_end

MahoganyTown_Shop_Movement_Dragonite2:
	lock_facing_direction
	walk_fast_right
	walk_fast_left
	unlock_facing_direction
	step_end

MahoganyTown_Shop_Movement_Rocket1:
	lock_facing_direction
	slide_right
	slide_right
	unlock_facing_direction
	step_end

MahoganyTown_Shop_Movement_LanceGreetPlayer:
	walk_down
	walk_right
	walk_right
	face_down
	step_end

MahoganyTown_Shop_Movement_DragoniteGotoBox:
	face_up
	delay_2
	face_right
	walk_right
	walk_up
	walk_up
	walk_up
	walk_up
	walk_right
	step_end

MahoganyTown_Shop_Movement_LanceGotoBox:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	face_right
	step_end

MahoganyTown_Shop_Movement_PlayerGotoBox:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

MahoganyTown_Shop_EventScript_Granny::
	lock
	faceplayer
	goto_if_eq JOHTO_VAR_MAHOGANY_TOWN_STATE, 5, MahoganyTown_Shop_EventScript_GrannyDuring
	goto_if_ge JOHTO_VAR_MAHOGANY_TOWN_STATE, 14, MahoganyTown_Shop_EventScript_GrannyShop
	msgbox MahoganyTown_Shop_Text_Granny, MSGBOX_NPC
	release
	end

MahoganyTown_Shop_EventScript_GrannyDuring::
	msgbox MahoganyMart1F_Text_Pharmacist_Lance, MSGBOX_DEFAULT
	closemessage
	release
	end

MahoganyTown_Shop_EventScript_GrannyShop::
	message J_gText_HowMayIServeYou
	waitmessage
	pokemart MahoganyTown_Pokemart
	msgbox J_gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2

MahoganyTown_Pokemart:
	.2byte ITEM_RAGE_CANDY_BAR
	.2byte ITEM_ICE_STONE
	.2byte ITEM_METAL_COAT
	.2byte ITEM_DRAGON_SCALE
	.2byte ITEM_KINGS_ROCK
	.2byte ITEM_UP_GRADE
	.2byte ITEM_DUBIOUS_DISC
	.2byte ITEM_REAPER_CLOTH
	.2byte ITEM_NEVER_MELT_ICE
	.2byte ITEM_PROTECTOR
	.2byte ITEM_ELECTIRIZER
	.2byte ITEM_MAGMARIZER
	.2byte ITEM_OVAL_STONE
	.2byte ITEM_RAZOR_FANG
	.2byte ITEM_RAZOR_CLAW
	.2byte ITEM_DUSK_STONE
	.2byte ITEM_DAWN_STONE
	.2byte ITEM_SHINY_STONE
	.2byte ITEM_BLACK_AUGURITE
	.2byte ITEM_PEAT_BLOCK
	.2byte ITEM_NONE
	release
	end

MahoganyTown_Shop_Text_Granny:
	.string "Pleas{SE_M_REVERSAL}com{SE_M_REVERSAL}bac{SE_M_ENCORE2}anothe{SE_M_SAND_TOMB}time.\n"
	.string "Th{SE_M_REVERSAL}stor{SE_M_REVERSAL}is..{SE_M_PERISH_SONG}closed\l"
	.string "righ{SE_M_SPIT_UP}now.$"

MahoganyMart1F_Text_Pharmacist_Lance:
	.string "ROCKET{SE_M_SKETCH}hav{SE_M_REVERSAL}hijacke{SE_M_WATERFALL}m{SE_M_YAWN}basement!$"

MahoganyMart1F_Text_BlackBelt:
	.string "Heheh{SE_M_DRAGON_RAGE}Th{SE_M_REVERSAL}experi{SE_M_PAY_DAY}men{SE_M_SPIT_UP}worke{SE_M_WATERFALL}like\n"
	.string "{SE_M_CHARGE}charm.\p"
	.string "MAGIKAR{SE_M_PETAL_DANCE}ar{SE_M_REVERSAL}jus{SE_M_SPIT_UP}worthless{SE_M_SUPERSONIC}but\n"
	.string "GYARADO{SE_M_SKETCH}ar{SE_M_REVERSAL}bi{SE_M_SANDSTORM}moneymakers.$"

MahoganyMart1F_Text_BlackBelt_Lance:
	.string "Urrgh…\p"
	.string "Tha{SE_M_SPIT_UP}guy'{SE_M_GRASSWHISTLE}POKéMO{SE_M_PSYBEAM2}ar{SE_M_REVERSAL}tough…$"

MahoganyMart1F_Text_Lance_HyperBeam:
	.string "LANCE{SE_M_HEAT_WAVE}DRAGONITE{SE_M_SUPERSONIC}HYPE{SE_M_MINIMIZE}BEAM.$"

MahoganyMart1F_Text_Lance_Radio:
	.string "Wha{SE_M_SPIT_UP}too{SE_M_ENCORE2}you{SE_M_SUPERSONIC}{PLAYER}?\p"
	.string "Jus{SE_M_SPIT_UP}a{SE_M_GRASSWHISTLE}w{SE_M_REVERSAL}thought{SE_M_SUPERSONIC}tha{SE_M_SPIT_UP}strange\n"
	.string "radi{SE_M_ATTRACT2}signa{SE_M_BATON_PASS}i{SE_M_GRASSWHISTLE}comin{SE_M_SANDSTORM}fro{SE_M_MILK_DRINK}here.$"

MahoganyMart1F_Text_Lance_Stairs:
	.string "Excellen{SE_M_SPIT_UP}wor{SE_M_ENCORE2}findin{SE_M_SANDSTORM}th{SE_M_REVERSAL}stairs,\n"
	.string "DRAGONITE!$"

MahoganyMart1F_Text_Lance_SplitUp:
	.string "LANCE{SE_M_HEAT_WAVE}{PLAYER}{SE_M_SUPERSONIC}w{SE_M_REVERSAL}shoul{SE_M_WATERFALL}spli{SE_M_SPIT_UP}up\n"
	.string "t{SE_M_ATTRACT2}chec{SE_M_ENCORE2}thi{SE_M_GRASSWHISTLE}place.\p"
	.string "I'l{SE_M_BATON_PASS}g{SE_M_ATTRACT2}first.$"

