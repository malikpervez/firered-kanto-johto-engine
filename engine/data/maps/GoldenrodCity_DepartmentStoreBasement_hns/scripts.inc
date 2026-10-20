@ Johto (data/maps/GoldenrodCity_DepartmentStoreBasement_hns/scripts.inc), as built into the FireRed game.

GoldenrodCity_DepartmentStoreBasement_hns_MapScripts::
	map_script 2, GoldenrodDeptElevator_OnFrame
	map_script 1, GoldenrodCity_DepartmentStoreBasement_OnLoad
	.byte 0

GoldenrodCity_DepartmentStoreBasement_OnLoad::
	call_if_set 8682, GoldenrodCity_DepartmentStoreBasement_TryMachoke1
	call_if_set 8683, GoldenrodCity_DepartmentStoreBasement_TryMachoke2
	call_if_set 8684, GoldenrodCity_DepartmentStoreBasement_TryMachoke3

	end

GoldenrodCity_DepartmentStoreBasement_TryMachoke1::
	setobjectxyperm 11, 1, 12
	setobjectxyperm 1, 1, 11
	setobjectmovementtype 11, 0xA
	return

GoldenrodCity_DepartmentStoreBasement_TryMachoke2::
	setobjectxyperm 12, 10, 11
	setobjectxyperm 2, 9, 11
	setobjectmovementtype 12, 0x8
	return

GoldenrodCity_DepartmentStoreBasement_TryMachoke3::
	setobjectxyperm 13, 17, 16
	setobjectxyperm 3, 18, 16
	setobjectmovementtype 13, 0x9
	return

GoldenrodCity_DepartmentStoreBasement_EventScript_BlackBelt1::
	lock
	goto_if_unset 8682, GoldenrodCity_DepartmentStoreBasement_EventScript_MachokeMoveBoulder1
	faceplayer
	msgbox GoldenrodDeptStore_Text_B1FBlackBelt1, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_DepartmentStoreBasement_EventScript_BlackBelt2::
	lock
	goto_if_unset 8683, GoldenrodCity_DepartmentStoreBasement_EventScript_BlackBelt2_Mid
	faceplayer
	msgbox GoldenrodDeptStore_Text_B1FBlackBelt2, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_DepartmentStoreBasement_EventScript_BlackBelt2_Mid::
	checkitem ITEM_CARD_KEY
	goto_if_eq 32781, TRUE, GoldenrodCity_DepartmentStoreBasement_EventScript_MachokeMoveBoulder2
	msgbox GoldenrodDeptStore_Text_B1FBlackBelt2, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_DepartmentStoreBasement_EventScript_BlackBelt3::
	lock
	goto_if_unset 8684, GoldenrodCity_DepartmentStoreBasement_EventScript_MachokeMoveBoulder3
	faceplayer
	msgbox GoldenrodDeptStore_Text_B1FBlackBelt3After, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_DepartmentStoreBasement_EventScript_Machoke::
	lock
	faceplayer
	waitse
	playmoncry 67, 0
	msgbox GoldenrodDeptStore_Text_B1FMachoke, MSGBOX_DEFAULT
	waitmoncry
	release
	end

GoldenrodCity_DepartmentStoreBasement_EventScript_MachokeMoveBoulder1::
	msgbox GoldenrodDeptStore_Text_BlackBeltMove, MSGBOX_DEFAULT
	closemessage
	playse 214
	applymovement 1, GoldenrodCity_DepartmentStoreBasement_Movement_Boulder1
	applymovement 11, GoldenrodCity_DepartmentStoreBasement_Movement_Machoke1
	waitmovement 0
	waitmovement 0
	setobjectxyperm 11, 1, 12
	setobjectxyperm 1, 1, 11
	setflag 8682
	release
	end

GoldenrodCity_DepartmentStoreBasement_EventScript_MachokeMoveBoulder2::
	msgbox GoldenrodDeptStore_Text_BlackBeltMove, MSGBOX_DEFAULT
	closemessage
	playse 214
	applymovement 2, GoldenrodCity_DepartmentStoreBasement_Movement_Boulder2
	applymovement 12, GoldenrodCity_DepartmentStoreBasement_Movement_Machoke2
	waitmovement 0
	waitmovement 0
	setobjectxyperm 12, 10, 11
	setobjectxyperm 2, 9, 11
	setflag 8683
	release
	end

GoldenrodCity_DepartmentStoreBasement_EventScript_MachokeMoveBoulder3::
	msgbox GoldenrodDeptStore_Text_BlackBeltMove, MSGBOX_DEFAULT
	closemessage
	playse 214
	applymovement 3, GoldenrodCity_DepartmentStoreBasement_Movement_Boulder3
	applymovement 13, GoldenrodCity_DepartmentStoreBasement_Movement_Machoke3
	waitmovement 0
	waitmovement 0
	setobjectxyperm 13, 17, 16
	setobjectxyperm 3, 18, 16
	setflag 8684
	release
	end

GoldenrodCity_DepartmentStoreBasement_EventScript_Item_AmuletCoin::
	finditem ITEM_AMULET_COIN
	end

GoldenrodCity_DepartmentStoreBasement_EventScript_Item_Ether::
	finditem ITEM_ETHER
	end

GoldenrodCity_DepartmentStoreBasement_EventScript_Item_UltraBall::
	finditem ITEM_ULTRA_BALL
	end

GoldenrodCity_DepartmentStoreBasement_EventScript_Item_ExpShare::
	finditem ITEM_EXP_SHARE_SMALL
	end

GoldenrodCity_DepartmentStoreBasement_Movement_Machoke1:
	walk_left
	walk_left
	walk_left
	walk_down
	walk_left
	face_up
	step_end

GoldenrodCity_DepartmentStoreBasement_Movement_Boulder1:
	slide_left
	delay_8
	slide_left
	delay_8
	slide_left
	step_end

GoldenrodCity_DepartmentStoreBasement_Movement_Machoke2:
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

GoldenrodCity_DepartmentStoreBasement_Movement_Boulder2:
	slide_left
	slide_left
	slide_left
	slide_left
	step_end

GoldenrodCity_DepartmentStoreBasement_Movement_Machoke3:
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

GoldenrodCity_DepartmentStoreBasement_Movement_Boulder3:
	slide_right
	slide_right
	slide_right
	slide_right
	slide_right
	step_end

GoldenrodDeptStore_Text_BlackBeltMove:
	.string "MACHOKE{SE_M_SUPERSONIC}hel{SE_M_MORNING_SUN}u{SE_M_GRASSWHISTLE}mov{SE_M_REVERSAL}tha{SE_M_SPIT_UP}boulder!$"

GoldenrodDeptStore_Text_B1FBlackBelt1:
	.string "Hey{SE_M_SUPERSONIC}kid{SE_M_DRAGON_RAGE}You'r{SE_M_REVERSAL}holdin{SE_M_SANDSTORM}u{SE_M_GRASSWHISTLE}up!\p"
	.string "Ou{SE_M_SAND_TOMB}polic{SE_M_YAWN}i{SE_M_GRASSWHISTLE}t{SE_M_ATTRACT2}wor{SE_M_ENCORE2}behin{SE_M_WATERFALL}the\n"
	.string "scene{SE_M_GRASSWHISTLE}wher{SE_M_REVERSAL}n{SE_M_ATTRACT2}on{SE_M_REVERSAL}ca{SE_M_ATTRACT}se{SE_M_REVERSAL}us!$"

GoldenrodDeptStore_Text_B1FBlackBelt2:
	.string "{SE_M_HEAL_BELL}los{SE_M_REVERSAL}m{SE_M_YAWN}passio{SE_M_ATTRACT}fo{SE_M_SAND_TOMB}wor{SE_M_ENCORE2}if\n"
	.string "someone'{SE_M_GRASSWHISTLE}watching.\p"
	.string "Com{SE_M_REVERSAL}on{SE_M_SUPERSONIC}kid{SE_M_SUPERSONIC}scoot!$"

GoldenrodDeptStore_Text_B1FBlackBelt3:
	.string "Oohah{SE_M_DRAGON_RAGE}Oohah!\p"
	.string "Wha{SE_M_SPIT_UP}d{SE_M_ATTRACT2}yo{SE_M_DIVE}nee{SE_M_WATERFALL}kid?\l"
	.string "I'{SE_M_MILK_DRINK}workin{SE_M_SANDSTORM}here!$"

GoldenrodDeptStore_Text_B1FBlackBelt3After:
	.string "Oohah{SE_M_DRAGON_RAGE}Oohah!\p"
	.string "Th{SE_M_REVERSAL}stuf{SE_M_ACID_ARMOR}o{SE_M_ATTRACT}th{SE_M_REVERSAL}ground'{SE_M_GRASSWHISTLE}junk.\p"
	.string "Tak{SE_M_REVERSAL}i{SE_M_SPIT_UP}i{SE_M_ACID_ARMOR}yo{SE_M_DIVE}wan{SE_M_SPIT_UP}it!$"

GoldenrodDeptStore_Text_B1FMachoke:
	.string "MACHOKE{SE_M_HEAT_WAVE}Maaacho!$"

