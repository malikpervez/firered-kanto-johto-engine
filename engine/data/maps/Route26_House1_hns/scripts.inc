@ Johto (data/maps/Route26_House1_hns/scripts.inc), as built into the FireRed game.

Route26_House1_hns_MapScripts::
	.byte 0

Route26_House1_EventScript_HealWoman::
	lock
	faceplayer
	msgbox Route26_Text_HealHouseRest, MSGBOX_DEFAULT
	closemessage
	call J_Common_EventScript_OutOfCenterPartyHeal
	msgbox Route26_Text_HealHouseKeepAtIt, MSGBOX_DEFAULT
	release
	end

Route26_Text_HealHouseRest:
	.string "You{SE_M_SAND_TOMB}POKéMO{SE_M_PSYBEAM2}loo{SE_M_ENCORE2}{SE_M_CHARGE}littl{SE_M_REVERSAL}tired.\p"
	.string "Yo{SE_M_DIVE}shoul{SE_M_WATERFALL}res{SE_M_SPIT_UP}the{SE_M_MILK_DRINK}{SE_M_CHARGE}while.$"

Route26_Text_HealHouseKeepAtIt:
	.string "There!\p"
	.string "You{SE_M_SAND_TOMB}POKéMO{SE_M_PSYBEAM2}ar{SE_M_REVERSAL}lookin{SE_M_SANDSTORM}good!\p"
	.string "Kee{SE_M_MORNING_SUN}a{SE_M_SPIT_UP}it!$"

