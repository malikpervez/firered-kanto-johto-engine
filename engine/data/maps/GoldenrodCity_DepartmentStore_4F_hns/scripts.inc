@ Johto (data/maps/GoldenrodCity_DepartmentStore_4F_hns/scripts.inc), as built into the FireRed game.

GoldenrodCity_DepartmentStore_4F_hns_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, GoldenrodDeptElevator_OnFrame
	.byte 0

GoldenrodDeptStore4_EventScript_Cooltrainer::
	lock
	faceplayer
	msgbox GoldenrodDeptStore_Text_4FCooltrainerM, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodDeptStore4_EventScript_BugCatcher::
	lock
	faceplayer
	msgbox GoldenrodDeptStore_Text_4FBugCatcher, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodDeptStore4_EventScript_GBAKid::
	lock
	faceplayer
	msgbox GoldenrodDeptStore_Text_4FGameboyKid, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodDeptStore4_EventScript_Sign::
	lock
	faceplayer
	msgbox GoldenrodDeptStore_Text_4FDirectory, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodDeptStore_Text_4FCooltrainerM:
	.string "Hey{SE_M_PERISH_SONG}{SE_M_HEAL_BELL}lov{SE_M_REVERSAL}stron{SE_M_SANDSTORM}POKéMON.\p"
	.string "{SE_M_HEAL_BELL}fee{SE_M_WATERFALL}the{SE_M_MILK_DRINK}PROTEI{SE_M_PSYBEAM2}t{SE_M_ATTRACT2}cran{SE_M_ENCORE2}up\n"
	.string "thei{SE_M_SAND_TOMB}ATTACK.$"

GoldenrodDeptStore_Text_4FBugCatcher:
	.string "IRO{SE_M_PSYBEAM2}add{SE_M_GRASSWHISTLE}t{SE_M_ATTRACT2}you{SE_M_SAND_TOMB}POKéMON's\n"
	.string "DEFENSE.$"

GoldenrodDeptStore_Text_4FGameboyKid:
	.string "Ther{SE_M_REVERSAL}wer{SE_M_REVERSAL}rumour{SE_M_GRASSWHISTLE}tha{SE_M_SPIT_UP}some\n"
	.string "POKéMO{SE_M_PSYBEAM2}evolv{SE_M_REVERSAL}onl{SE_M_YAWN}by\l"
	.string "bein{SE_M_SANDSTORM}trade{SE_M_WATERFALL}vi{SE_M_CHARGE}{SE_M_CHARGE}Gam{SE_M_REVERSAL}Link\l"
	.string "cable.\p"
	.string "Pfft...\p"
	.string "Suc{SE_M_TRI_ATTACK}misinformation.\p"
	.string "{SE_M_HEAL_BELL}kno{SE_M_TWISTER}som{SE_M_REVERSAL}o{SE_M_ACID_ARMOR}th{SE_M_REVERSAL}rumoured\n"
	.string "POKéMON:\l"
	.string "MACHOKE{SE_M_SUPERSONIC}KADABRA{SE_M_SUPERSONIC}HAUNTE{SE_M_MINIMIZE}and,\l"
	.string "um{SE_M_SUPERSONIC}GRAVELER,\l"
	.string "bu{SE_M_SPIT_UP}the{SE_M_YAWN}al{SE_M_BATON_PASS}evolv{SE_M_REVERSAL}through\l"
	.string "leve{SE_M_BATON_PASS}up.$"

GoldenrodDeptStore4_EventScript_Clerk::
	lock
	faceplayer
	message J_gText_HowMayIServeYou
	waitmessage
	pokemart GoldenrodDeptStore4_Pokemart
	msgbox J_gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2

GoldenrodDeptStore4_Pokemart:
	.2byte ITEM_PROTEIN
	.2byte ITEM_CALCIUM
	.2byte ITEM_IRON
	.2byte ITEM_ZINC
	.2byte ITEM_CARBOS
	.2byte ITEM_HP_UP
	pokemartlistend

GoldenrodDeptStore_Text_4FDirectory:
	.string "Le{SE_M_SPIT_UP}U{SE_M_GRASSWHISTLE}Pum{SE_M_MORNING_SUN}U{SE_M_MORNING_SUN}You{SE_M_SAND_TOMB}POKéMON!\p"
	.string "4{SE_M_LEER}MEDICIN{SE_M_SWORDS_DANCE}BOX$"

