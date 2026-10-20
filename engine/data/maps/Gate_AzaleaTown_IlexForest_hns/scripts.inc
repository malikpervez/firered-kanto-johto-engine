@ Johto (data/maps/Gate_AzaleaTown_IlexForest_hns/scripts.inc), as built into the FireRed game.

Gate_AzaleaTown_IlexForest_hns_MapScripts::
	.byte 0

Gate_AzaleaTown_IlexForest_EventScript_Officer::
	lock
	faceplayer
	msgbox Gate_AzaleaTown_IlexForest_Text_Officer, MSGBOX_DEFAULT
	closemessage
	release
	end

Gate_AzaleaTown_IlexForest_EventScript_Granny::
	lock
	faceplayer
	msgbox Gate_AzaleaTown_IlexForest_Text_Granny, MSGBOX_DEFAULT
	closemessage
	release
	end

Gate_AzaleaTown_IlexForest_Text_Officer:
	.string "ILE{SE_M_LOCK_ON}FORES{SE_M_SWIFT}i{SE_M_GRASSWHISTLE}big.\n"
	.string "B{SE_M_REVERSAL}careful!\l"
	.string "Don'{SE_M_SPIT_UP}ge{SE_M_SPIT_UP}lost.$"

Gate_AzaleaTown_IlexForest_Text_Granny:
	.string "Th{SE_M_REVERSAL}ILE{SE_M_LOCK_ON}FORES{SE_M_SWIFT}i{SE_M_GRASSWHISTLE}watched\n"
	.string "ove{SE_M_SAND_TOMB}b{SE_M_YAWN}it{SE_M_GRASSWHISTLE}protector.\p"
	.string "Sta{SE_M_YAWN}ou{SE_M_SPIT_UP}o{SE_M_ACID_ARMOR}mischief!$"

