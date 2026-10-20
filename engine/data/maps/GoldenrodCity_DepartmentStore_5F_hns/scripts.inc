@ Johto (data/maps/GoldenrodCity_DepartmentStore_5F_hns/scripts.inc), as built into the FireRed game.

GoldenrodCity_DepartmentStore_5F_hns_MapScripts::
	map_script 2, GoldenrodDeptElevator_OnFrame
	.byte 0

GoldenrodDeptStore5_EventScript_Lass::
	lock
	faceplayer
	msgbox GoldenrodDeptStore_Text_5FLass, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodDeptStore5_EventScript_PokefanM::
	lock
	faceplayer
	msgbox GoldenrodDeptStore_Text_5FPokefanM, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodDeptStore5_EventScript_Girl::
	lock
	faceplayer
	msgbox GoldenrodDeptStore_Text_Girl, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodDeptStore5_EventScript_Sign::
	lock
	faceplayer
	msgbox GoldenrodDeptStore_Text_5FDirectory, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodDeptStore5_EventScript_Receptionist::
	lock
	faceplayer
	goto_if_set 8712, GoldenrodDeptStore5_EventScript_Receptionist_Already
	msgbox GoldenrodDeptStore_Text_5FReceptionistOhYourMon, MSGBOX_DEFAULT
	closemessage
	specialvar 32781, GetLeadMonFriendshipScore
	goto_if_ge 32781, 4, GoldenrodDeptStore5_EventScript_Receptionist_GiveReturn
	msgbox GoldenrodDeptStore_Text_5FReceptionistPutInSomeMoreEffort, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodDeptStore5_EventScript_Receptionist_GiveReturn::
	giveitem 608
	setflag 8712
	msgbox GoldenrodDeptStore_Text_5FReceptionistThisMoveShouldBePerfect, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodDeptStore5_EventScript_Receptionist_Already::
	msgbox GoldenrodDeptStore_Text_5FReceptionistWait, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodDeptStore_Text_5FReceptionistOhYourMon:
	.string "Hello{SE_M_PERISH_SONG}Oh{SE_M_SUPERSONIC}you{SE_M_SAND_TOMB}POKéMON…$"

GoldenrodDeptStore_Text_5FReceptionistWait:
	.string "Wait{SE_M_SUPERSONIC}{SE_M_HEAL_BELL}alread{SE_M_YAWN}gav{SE_M_REVERSAL}yo{SE_M_DIVE}tha{SE_M_SPIT_UP}TM!$"

GoldenrodDeptStore_Text_5FReceptionistPutInSomeMoreEffort:
	.string "Hmm…\n"
	.string "It'{SE_M_GRASSWHISTLE}no{SE_M_SPIT_UP}bad{SE_M_SUPERSONIC}bu{SE_M_SPIT_UP}it'{SE_M_GRASSWHISTLE}als{SE_M_ATTRACT2}no{SE_M_SPIT_UP}good.\p"
	.string "You{SE_M_SUPERSONIC}a{SE_M_GRASSWHISTLE}th{SE_M_REVERSAL}TRAINER{SE_M_SUPERSONIC}nee{SE_M_WATERFALL}t{SE_M_ATTRACT2}pu{SE_M_SPIT_UP}in\n"
	.string "som{SE_M_REVERSAL}mor{SE_M_REVERSAL}effort.$"

GoldenrodDeptStore_Text_5FReceptionistThisMoveShouldBePerfect:
	.string "It'{SE_M_GRASSWHISTLE}ver{SE_M_YAWN}attache{SE_M_WATERFALL}t{SE_M_ATTRACT2}you.\p"
	.string "Thi{SE_M_GRASSWHISTLE}mov{SE_M_REVERSAL}shoul{SE_M_WATERFALL}b{SE_M_REVERSAL}perfec{SE_M_SPIT_UP}fo{SE_M_SAND_TOMB}a\n"
	.string "pai{SE_M_SAND_TOMB}lik{SE_M_REVERSAL}you.$"

GoldenrodDeptStore_Text_5FLass:
	.string "Durin{SE_M_SANDSTORM}th{SE_M_REVERSAL}day{SE_M_SUPERSONIC}{SE_M_CHARGE}lad{SE_M_YAWN}come{SE_M_GRASSWHISTLE}t{SE_M_ATTRACT2}check\n"
	.string "ou{SE_M_SPIT_UP}POKéMON.\p"
	.string "Sh{SE_M_REVERSAL}eve{SE_M_ATTRACT}give{SE_M_GRASSWHISTLE}awa{SE_M_YAWN}TMs!$"

GoldenrodDeptStore_Text_5FPokefanM:
	.string "Yo{SE_M_DIVE}can'{SE_M_SPIT_UP}renam{SE_M_REVERSAL}{SE_M_CHARGE}POKéMO{SE_M_PSYBEAM2}yo{SE_M_DIVE}get\n"
	.string "i{SE_M_ATTRACT}{SE_M_CHARGE}trade.\p"
	.string "Th{SE_M_REVERSAL}nam{SE_M_REVERSAL}i{SE_M_GRASSWHISTLE}{SE_M_CHARGE}reflectio{SE_M_ATTRACT}o{SE_M_ACID_ARMOR}the\n"
	.string "origina{SE_M_BATON_PASS}trainer'{SE_M_GRASSWHISTLE}feeling{SE_M_GRASSWHISTLE}fo{SE_M_SAND_TOMB}it.$"

GoldenrodDeptStore_Text_Girl:
	.string "Th{SE_M_REVERSAL}lad{SE_M_YAWN}gav{SE_M_REVERSAL}m{SE_M_REVERSAL}RETURN!\n"
	.string "M{SE_M_YAWN}POKéMO{SE_M_PSYBEAM2}mus{SE_M_SPIT_UP}reall{SE_M_YAWN}lik{SE_M_REVERSAL}me!$"

GoldenrodDeptStore5_EventScript_Clerk::
	lock
	faceplayer
	message J_gText_HowMayIServeYou
	waitmessage
	pokemart GoldenrodDeptStore5_Pokemart
	msgbox J_gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2

GoldenrodDeptStore5_Pokemart:
	.2byte 597
	.2byte 598
	.2byte 614
	.2byte 664
	.2byte 595
	.2byte 596
	.2byte 603
	.2byte 606
	.2byte 619
	.2byte 633
	pokemartlistend

GoldenrodDeptStore_Text_5FDirectory:
	.string "Customiz{SE_M_REVERSAL}You{SE_M_SAND_TOMB}POKéMON\p"
	.string "5{SE_M_LEER}T{SE_M_GIGA_DRAIN}CORNER$"

