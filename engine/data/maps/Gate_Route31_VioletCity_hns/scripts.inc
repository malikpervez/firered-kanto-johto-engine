@ Johto (data/maps/Gate_Route31_VioletCity_hns/scripts.inc), as built into the FireRed game.

Gate_Route31_VioletCity_hns_MapScripts::
	.byte 0

Gate_Route31_VioletCity_EventScript_Policeman::
	lock
	faceplayer
	msgbox Gate_Route31_VioletCity_Text_Policeman, MSGBOX_DEFAULT
	closemessage
	release
	end

Gate_Route31_VioletCity_EventScript_CooltrainerF::
	lock
	faceplayer
	msgbox Gate_Route31_VioletCity_Text_CooltrainerF, MSGBOX_DEFAULT
	closemessage
	release
	end

Gate_Route31_VioletCity_Text_Policeman:
	.string "H{SE_M_TRI_ATTACK2}there{SE_M_DRAGON_RAGE}Di{SE_M_WATERFALL}yo{SE_M_DIVE}visit\n"
	.string "SPROU{SE_M_SWIFT}TOWER?$"

Gate_Route31_VioletCity_Text_CooltrainerF:
	.string "{SE_M_HEAL_BELL}sa{SE_M_TWISTER}th{SE_M_REVERSAL}cutes{SE_M_SPIT_UP}POKéMO{SE_M_PSYBEAM2}out\n"
	.string "there.\p"
	.string "I{SE_M_SPIT_UP}looke{SE_M_WATERFALL}{SE_M_CHARGE}lo{SE_M_SPIT_UP}lik{SE_M_REVERSAL}PIKACHU!$"

