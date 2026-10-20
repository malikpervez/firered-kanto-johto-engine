@ Johto (data/maps/GoldenrodCity_DepartmentStore_3F_hns/scripts.inc), as built into the FireRed game.

GoldenrodCity_DepartmentStore_3F_hns_MapScripts::
	map_script 2, GoldenrodDeptElevator_OnFrame
	.byte 0

GoldenrodDeptStore3_EventScript_Nerd::
	lock
	faceplayer
	msgbox GoldenrodDeptStore_Text_3FSuperNerd, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodDeptStore3_EventScript_Sign::
	lock
	faceplayer
	msgbox GoldenrodDeptStore_Text_3FDirectory, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodDeptStore3_EventScript_Rocker::
	lock
	faceplayer
	msgbox GoldenrodDeptStore_Text_3FRocker, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodDeptStore_Text_3FSuperNerd:
	.string "I{SE_M_SUPERSONIC}I{SE_M_SUPERSONIC}I'{SE_M_MILK_DRINK}reall{SE_M_YAWN}impatient!\p"
	.string "{SE_M_HEAL_BELL}us{SE_M_REVERSAL}{SE_M_LOCK_ON}SPEE{SE_M_FAINT_ATTACK}i{SE_M_ATTRACT}battl{SE_M_REVERSAL}t{SE_M_ATTRACT2}spee{SE_M_WATERFALL}up\n"
	.string "m{SE_M_YAWN}POKéMON.$"

GoldenrodDeptStore_Text_3FRocker:
	.string "Hey{SE_M_DRAGON_RAGE}Whe{SE_M_ATTRACT}yo{SE_M_DIVE}battle{SE_M_SUPERSONIC}d{SE_M_ATTRACT2}yo{SE_M_DIVE}us{SE_M_REVERSAL}X\n"
	.string "SPECIAL?\p"
	.string "It'{SE_M_GRASSWHISTLE}awesome{SE_M_PERISH_SONG}I{SE_M_SPIT_UP}reall{SE_M_YAWN}jack{SE_M_GRASSWHISTLE}up\n"
	.string "SPECIA{SE_M_BRICK_BREAK}ATTACK!$"

GoldenrodDeptStore3_EventScript_Clerk::
	lock
	faceplayer
	message J_gText_HowMayIServeYou
	waitmessage
	pokemart GoldenrodDeptStore3_Pokemart
	msgbox J_gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2

GoldenrodDeptStore3_Pokemart:
	.2byte ITEM_X_SPEED
	.2byte ITEM_X_SP_ATK
	.2byte ITEM_X_ATTACK
	.2byte ITEM_X_DEFENSE
	.2byte ITEM_DIRE_HIT
	.2byte ITEM_GUARD_SPEC
	.2byte ITEM_X_ACCURACY
	pokemartlistend

GoldenrodDeptStore_Text_3FDirectory:
	.string "Fo{SE_M_SAND_TOMB}Victor{SE_M_YAWN}Seekers\p"
	.string "3{SE_M_LEER}BATTL{SE_M_SWORDS_DANCE}COLLECTION$"

