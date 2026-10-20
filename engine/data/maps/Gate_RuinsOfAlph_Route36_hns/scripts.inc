@ Johto (data/maps/Gate_RuinsOfAlph_Route36_hns/scripts.inc), as built into the FireRed game.

Gate_RuinsOfAlph_Route36_hns_MapScripts::
	.byte 0

Gate_RuinsOfAlph_Route36_EventScript_Officer::
	lock
	faceplayer
	msgbox Gate_RuinsOfAlph_Route36_Text_Officer, MSGBOX_DEFAULT
	closemessage
	release
	end

Gate_RuinsOfAlph_Route36_EventScript_PokefanM::
	lock
	faceplayer
	msgbox Gate_RuinsOfAlph_Route36_Text_PokefanM, MSGBOX_DEFAULT
	closemessage
	release
	end

Gate_RuinsOfAlph_Route36_EventScript_Youngster::
	lock
	faceplayer
	msgbox Gate_RuinsOfAlph_Route36_Text_Youngster, MSGBOX_DEFAULT
	closemessage
	release
	end

Gate_RuinsOfAlph_Route36_Text_Officer:
	.string "RUIN{SE_M_SKETCH}O{SE_M_LEER}ALPH\p"
	.string "{SE_M_BONEMERANG}Look-and-Touc{SE_M_TRI_ATTACK}Touris{SE_M_SPIT_UP}Site\p"
	.string "Tr{SE_M_YAWN}th{SE_M_REVERSAL}slidin{SE_M_SANDSTORM}ston{SE_M_REVERSAL}panels!$"

Gate_RuinsOfAlph_Route36_Text_PokefanM:
	.string "You'r{SE_M_REVERSAL}studyin{SE_M_SANDSTORM}th{SE_M_REVERSAL}RUINS?\p"
	.string "{SE_M_HEAL_BELL}se{SE_M_REVERSAL}{SE_M_CHARGE}scientis{SE_M_SPIT_UP}i{SE_M_ATTRACT}th{SE_M_REVERSAL}making.$"

Gate_RuinsOfAlph_Route36_Text_Youngster:
	.string "Ther{SE_M_REVERSAL}ar{SE_M_REVERSAL}drawing{SE_M_GRASSWHISTLE}o{SE_M_ATTRACT}stone\n"
	.string "panels.\p"
	.string "{SE_M_HEAL_BELL}trie{SE_M_WATERFALL}movin{SE_M_SANDSTORM}them.\n"
	.string "{SE_M_HEAL_BELL}wonde{SE_M_SAND_TOMB}wha{SE_M_SPIT_UP}the{SE_M_YAWN}are.$"

