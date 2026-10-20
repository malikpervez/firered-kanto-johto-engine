@ Johto (data/maps/GoldenrodCity_DepartmentStore_2F_hns/scripts.inc), as built into the FireRed game.

GoldenrodCity_DepartmentStore_2F_hns_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, GoldenrodDeptElevator_OnFrame
	.byte 0

GoldenrodDeptStore2_EventScript_Youngster::
	lock
	faceplayer
	msgbox GoldenrodDeptStore_Text_2FYoungster, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodDeptStore2_EventScript_CooltrainerF::
	lock
	faceplayer
	msgbox GoldenrodDeptStore_Text_2FCooltrainerF, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodDeptStore2_EventScript_Gent::
	lock
	faceplayer
	msgbox GoldenrodDeptStore_Text_2FGentleman, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodDeptStore2_EventScript_Sign::
	lock
	faceplayer
	msgbox GoldenrodDeptStore_Text_2FDirectory, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodDeptStore_Text_2FYoungster:
	.string "POKéGEA{SE_M_MINIMIZE}ca{SE_M_ATTRACT}stor{SE_M_REVERSAL}u{SE_M_MORNING_SUN}t{SE_M_ATTRACT2}10{SE_M_BITE}phone\n"
	.string "numbers.\p"
	.string "It'{SE_M_GRASSWHISTLE}har{SE_M_WATERFALL}t{SE_M_ATTRACT2}decid{SE_M_REVERSAL}whic{SE_M_TRI_ATTACK}numbers\n"
	.string "t{SE_M_ATTRACT2}keep.$"

GoldenrodDeptStore_Text_2FCooltrainerF:
	.string "{SE_M_HEAL_BELL}go{SE_M_SPIT_UP}m{SE_M_YAWN}ABR{SE_M_BONEMERANG}a{SE_M_SPIT_UP}th{SE_M_REVERSAL}GAM{SE_M_SWORDS_DANCE}CORNER.\p"
	.string "No{SE_M_TWISTER}it'{SE_M_GRASSWHISTLE}m{SE_M_YAWN}bes{SE_M_SPIT_UP}partner.$"

GoldenrodDeptStore_Text_2FGentleman:
	.string "Thi{SE_M_GRASSWHISTLE}DEPT.STOR{SE_M_SWORDS_DANCE}make{SE_M_GRASSWHISTLE}m{SE_M_REVERSAL}realize\n"
	.string "tha{SE_M_SPIT_UP}GOLDENRO{SE_M_FAINT_ATTACK}i{SE_M_GRASSWHISTLE}{SE_M_CHARGE}bi{SE_M_SANDSTORM}city.\p"
	.string "Th{SE_M_REVERSAL}selectio{SE_M_ATTRACT}her{SE_M_REVERSAL}i{SE_M_GRASSWHISTLE}unmatched\n"
	.string "anywher{SE_M_REVERSAL}else.$"

GoldenrodDeptStore2_EventScript_Clerk::
	lock
	faceplayer
	message J_gText_HowMayIServeYou
	waitmessage
	pokemart GoldenrodDeptStore2_Pokemart
	msgbox J_gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2

GoldenrodDeptStore2_Pokemart:
	.2byte ITEM_POKE_BALL
	.2byte ITEM_GREAT_BALL
	.2byte ITEM_ULTRA_BALL
	.2byte ITEM_FIRE_STONE
	.2byte ITEM_WATER_STONE
	.2byte ITEM_THUNDER_STONE
	.2byte ITEM_POTION
	.2byte ITEM_SUPER_POTION
	.2byte ITEM_HYPER_POTION
	.2byte ITEM_MAX_POTION
	.2byte ITEM_REVIVE
	.2byte ITEM_ANTIDOTE
	.2byte ITEM_PARALYZE_HEAL
	.2byte ITEM_BURN_HEAL
	.2byte ITEM_ICE_HEAL
	.2byte ITEM_AWAKENING
	.2byte ITEM_FULL_HEAL
	.2byte ITEM_ESCAPE_ROPE
	.2byte ITEM_REPEL
	.2byte ITEM_SUPER_REPEL
	.2byte ITEM_MAX_REPEL
	pokemartlistend

GoldenrodDeptStore_EventScript_VendingMachine::
	lockall
	message GoldenrodDeptStore_Text_WhichDrinkWouldYouLike
	waitmessage
	showmoneybox 0, 0
	goto GoldenrodDeptStore_EventScript_ChooseDrink
	end

GoldenrodDeptStore_EventScript_ChooseDrink::
	multichoice 16, 0, MULTI_VENDING_MACHINE, FALSE
	copyvar VAR_TEMP_1, VAR_RESULT
	switch VAR_TEMP_1
	case 0, GoldenrodDeptStore_EventScript_FreshWater
	case 1, GoldenrodDeptStore_EventScript_SodaPop
	case 2, GoldenrodDeptStore_EventScript_Lemonade
	msgbox GoldenrodDeptStore_Text_DecidedAgainstBuyingDrink, MSGBOX_DEFAULT
	goto GoldenrodDeptStore_EventScript_ExitVendingMachine
	end

GoldenrodDeptStore_EventScript_FreshWater::
	setvar VAR_TEMP_0, ITEM_FRESH_WATER
	goto GoldenrodDeptStore_EventScript_TryBuyDrink
	end

GoldenrodDeptStore_EventScript_SodaPop::
	setvar VAR_TEMP_0, ITEM_SODA_POP
	goto GoldenrodDeptStore_EventScript_TryBuyDrink
	end

GoldenrodDeptStore_EventScript_Lemonade::
	setvar VAR_TEMP_0, ITEM_LEMONADE
	goto GoldenrodDeptStore_EventScript_TryBuyDrink
	end

GoldenrodDeptStore_EventScript_CheckMoneyFreshWater::
	checkmoney 200
	return

GoldenrodDeptStore_EventScript_CheckMoneySodaPop::
	checkmoney 300
	return

GoldenrodDeptStore_EventScript_CheckMoneyLemonade::
	checkmoney 350
	return

GoldenrodDeptStore_EventScript_RemoveMoneyFreshWater::
	removemoney 200
	return

GoldenrodDeptStore_EventScript_RemoveMoneySodaPop::
	removemoney 300
	return

GoldenrodDeptStore_EventScript_RemoveMoneyLemonade::
	removemoney 350
	return

GoldenrodDeptStore_EventScript_TryBuyDrink::
	call_if_eq VAR_TEMP_1, 0, GoldenrodDeptStore_EventScript_CheckMoneyFreshWater
	call_if_eq VAR_TEMP_1, 1, GoldenrodDeptStore_EventScript_CheckMoneySodaPop
	call_if_eq VAR_TEMP_1, 2, GoldenrodDeptStore_EventScript_CheckMoneyLemonade
	goto_if_eq VAR_RESULT, FALSE, GoldenrodDeptStore_EventScript_NotEnoughMoney
	checkitemspace VAR_TEMP_0
	goto_if_eq VAR_RESULT, FALSE, GoldenrodDeptStore_EventScript_NoRoomForDrink
	call_if_eq VAR_TEMP_1, 0, GoldenrodDeptStore_EventScript_RemoveMoneyFreshWater
	call_if_eq VAR_TEMP_1, 1, GoldenrodDeptStore_EventScript_RemoveMoneySodaPop
	call_if_eq VAR_TEMP_1, 2, GoldenrodDeptStore_EventScript_RemoveMoneyLemonade
	updatemoneybox
	bufferitemname STR_VAR_1, VAR_TEMP_0
	playse SE_VEND
	msgbox GoldenrodDeptStore_Text_DrinkClankedDown, MSGBOX_DEFAULT
	additem VAR_TEMP_0
	bufferitemname STR_VAR_2, VAR_TEMP_0
	bufferstdstring STR_VAR_3, STDSTRING_MEDICINE
	msgbox J_gText_PutItemInPocket, MSGBOX_DEFAULT
	random 64
	goto_if_ne VAR_RESULT, 0, GoldenrodDeptStore_EventScript_ChooseNewDrink
	checkitemspace VAR_TEMP_0
	goto_if_eq VAR_RESULT, FALSE, GoldenrodDeptStore_EventScript_NoRoomForDrink
	playse SE_VEND
	msgbox GoldenrodDeptStore_Text_ExtraDrinkClankedDown, MSGBOX_DEFAULT
	additem VAR_TEMP_0
	bufferitemname STR_VAR_2, VAR_TEMP_0
	bufferstdstring STR_VAR_3, STDSTRING_MEDICINE
	msgbox J_gText_PutItemInPocket, MSGBOX_DEFAULT
	random 64
	goto_if_ne VAR_RESULT, 0, GoldenrodDeptStore_EventScript_ChooseNewDrink
	checkitemspace VAR_TEMP_0
	goto_if_eq VAR_RESULT, 0, GoldenrodDeptStore_EventScript_NoRoomForDrink
	playse SE_VEND
	msgbox GoldenrodDeptStore_Text_ExtraDrinkClankedDown, MSGBOX_DEFAULT
	additem VAR_TEMP_0
	bufferitemname STR_VAR_2, VAR_TEMP_0
	bufferstdstring STR_VAR_3, STDSTRING_MEDICINE
	msgbox J_gText_PutItemInPocket, MSGBOX_DEFAULT
	goto GoldenrodDeptStore_EventScript_ChooseNewDrink
	end

GoldenrodDeptStore_EventScript_ChooseNewDrink::
	message GoldenrodDeptStore_Text_WhichDrinkWouldYouLike
	waitmessage
	goto GoldenrodDeptStore_EventScript_ChooseDrink
	end

GoldenrodDeptStore_EventScript_NotEnoughMoney::
	msgbox GoldenrodDeptStore_Text_NotEnoughMoney, MSGBOX_DEFAULT
	goto GoldenrodDeptStore_EventScript_ExitVendingMachine
	end

GoldenrodDeptStore_EventScript_NoRoomForDrink::
	msgbox J_gText_TheBagIsFull, MSGBOX_DEFAULT
	goto GoldenrodDeptStore_EventScript_ExitVendingMachine
	end

GoldenrodDeptStore_EventScript_ExitVendingMachine::
	hidemoneybox
	releaseall
	end

GoldenrodDeptStore_Text_WhichDrinkWouldYouLike:
	.string "It'{SE_M_GRASSWHISTLE}{SE_M_CHARGE}VENDIN{SE_M_SWAGGER}MACHINE.\n"
	.string "Whic{SE_M_TRI_ATTACK}drin{SE_M_ENCORE2}woul{SE_M_WATERFALL}yo{SE_M_DIVE}like?$"

GoldenrodDeptStore_Text_DrinkClankedDown:
	.string "Clang!\p"
	.string "{SE_M_BONEMERANG}ca{SE_M_ATTRACT}o{SE_M_ACID_ARMOR}{STR_VAR_1} droppe{SE_M_WATERFALL}down.$"

GoldenrodDeptStore_Text_ExtraDrinkClankedDown:
	.string "Clang!\p"
	.string "Score{SE_M_DRAGON_RAGE}A{SE_M_ATTRACT}extr{SE_M_CHARGE}ca{SE_M_ATTRACT}o{SE_M_ACID_ARMOR}{STR_VAR_1}\n"
	.string "droppe{SE_M_WATERFALL}down!$"

GoldenrodDeptStore_Text_NotEnoughMoney:
	.string "No{SE_M_SPIT_UP}enoug{SE_M_TRI_ATTACK}money…$"

GoldenrodDeptStore_Text_DecidedAgainstBuyingDrink:
	.string "Decide{SE_M_WATERFALL}agains{SE_M_SPIT_UP}buyin{SE_M_SANDSTORM}{SE_M_CHARGE}drink.$"

GoldenrodDeptStore_Text_2FDirectory:
	.string "You{SE_M_SAND_TOMB}Trave{SE_M_BATON_PASS}Companion\p"
	.string "2{SE_M_LEER}TRAINER'{SE_M_SKETCH}MARKET$"

