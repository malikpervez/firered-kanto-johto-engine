@ Johto (data/maps/Gate_IlexForest_Route34_hns/scripts.inc), as built into the FireRed game.

Gate_IlexForest_Route34_hns_MapScripts::
	.byte 0

Route34IlexForestGate_EventScript_Lass::
	lock
	faceplayer
	msgbox Route34IlexForestGate_Text_Lass, MSGBOX_DEFAULT
	closemessage
	release
	end

Route34IlexForestGate_EventScript_Butterfree::
	lock
	faceplayer
	waitse
	playmoncry 12, 0
	msgbox Route34IlexForestGate_Text_Butterfree, MSGBOX_DEFAULT
	waitmoncry
	release
	end

Route34IlexForestGate_Text_Lass:
	.string "Di{SE_M_WATERFALL}yo{SE_M_DIVE}se{SE_M_REVERSAL}th{SE_M_REVERSAL}shrin{SE_M_REVERSAL}honoring\n"
	.string "th{SE_M_REVERSAL}protector?\p"
	.string "I{SE_M_SPIT_UP}watche{SE_M_GRASSWHISTLE}ove{SE_M_SAND_TOMB}th{SE_M_REVERSAL}FORES{SE_M_SWIFT}from\n"
	.string "acros{SE_M_GRASSWHISTLE}time.\p"
	.string "{SE_M_HEAL_BELL}thin{SE_M_ENCORE2}tha{SE_M_SPIT_UP}i{SE_M_SPIT_UP}mus{SE_M_SPIT_UP}b{SE_M_REVERSAL}a\n"
	.string "GRASS-typ{SE_M_REVERSAL}POKéMON.$"

Route34IlexForestGate_Text_Butterfree:
	.string "BUTTERFREE{SE_M_HEAT_WAVE}Freeh!$"

