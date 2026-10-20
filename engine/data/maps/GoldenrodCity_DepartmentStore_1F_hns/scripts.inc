@ Johto (data/maps/GoldenrodCity_DepartmentStore_1F_hns/scripts.inc), as built into the FireRed game.

GoldenrodCity_DepartmentStore_1F_hns_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, GoldenrodDeptElevator_OnFrame
	.byte 0

GoldenrodDeptStore1_EventScript_Receptionist::
	lock
	faceplayer
	msgbox GoldenrodDeptStor1_Text_Receptionist, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodDeptStore1_EventScript_Gentleman::
	lock
	faceplayer
	msgbox GoldenrodDeptStore1_Text_Gentleman, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodDeptStore1_EventScript_PokefanF::
	lock
	faceplayer
	msgbox GoldenrodDeptStore1_Text_PokefanF, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodDeptStore1_EventScript_BugCatcher::
	lock
	faceplayer
	msgbox GoldenrodDeptStore1_Text_BugCatcher, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodDeptStore1_EventScript_Directory::
	lock
	msgbox GoldenrodDeptStore1_Text_Directory, MSGBOX_SIGN
	closemessage
	release
	end

GoldenrodDeptStor1_Text_Receptionist:
	.string "Welcom{SE_M_REVERSAL}t{SE_M_ATTRACT2}GOLDENRO{SE_M_FAINT_ATTACK}DEPT.STORE.$"

GoldenrodDeptStore1_Text_Gentleman:
	.string "Th{SE_M_REVERSAL}DEPT.STOR{SE_M_SWORDS_DANCE}ha{SE_M_GRASSWHISTLE}{SE_M_CHARGE}decent\n"
	.string "selection.\p"
	.string "Bu{SE_M_SPIT_UP}som{SE_M_REVERSAL}item{SE_M_GRASSWHISTLE}ar{SE_M_REVERSAL}onl{SE_M_YAWN}available\n"
	.string "a{SE_M_GRASSWHISTLE}GAM{SE_M_SWORDS_DANCE}CORNE{SE_M_MINIMIZE}prizes.$"

GoldenrodDeptStore1_Text_PokefanF:
	.string "I'{SE_M_MILK_DRINK}rarin{SE_M_SANDSTORM}t{SE_M_ATTRACT2}sho{SE_M_MORNING_SUN}agai{SE_M_ATTRACT}today!$"

GoldenrodDeptStore1_Text_BugCatcher:
	.string "Mom'{SE_M_GRASSWHISTLE}goo{SE_M_WATERFALL}a{SE_M_SPIT_UP}bargai{SE_M_ATTRACT}hunting.\p"
	.string "Sh{SE_M_REVERSAL}alway{SE_M_GRASSWHISTLE}buy{SE_M_GRASSWHISTLE}stuf{SE_M_ACID_ARMOR}a{SE_M_SPIT_UP}lower\n"
	.string "prices.$"

GoldenrodDeptStore1_Text_Directory:
	.string "1{SE_M_LEER}SERVIC{SE_M_SWORDS_DANCE}COUNTER\n"
	.string "YO{SE_M_REFLECT}AR{SE_M_SWORDS_DANCE}HERE.\p"
	.string "2{SE_M_LEER}TRAINER'{SE_M_SKETCH}MARKET\p"
	.string "3{SE_M_LEER}BATTL{SE_M_SWORDS_DANCE}COLLECTION\p"
	.string "4{SE_M_LEER}MEDICIN{SE_M_SWORDS_DANCE}BOX\p"
	.string "5{SE_M_LEER}T{SE_M_GIGA_DRAIN}CORNER\p"
	.string "6{SE_M_LEER}TRANQUI{SE_M_BRICK_BREAK}SQUARE\p"
	.string "ROOFTO{SE_M_PETAL_DANCE}LOOKOUT$"

