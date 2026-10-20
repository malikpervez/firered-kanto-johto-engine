@ Johto (data/maps/CherrygroveCity_House2_hns/scripts.inc), as built into the FireRed game.

CherrygroveCity_House2_hns_MapScripts::
	.byte 0

CherrygroveCity_House2_EventScript_GuideGent::
	lock
	faceplayer
	msgbox CherrygroveCity_GuideHouse_Text_GuideGent, MSGBOX_DEFAULT
	closemessage
	release
	end

CherrygroveCity_GuideHouse_Text_GuideGent:
	.string "Whe{SE_M_ATTRACT}{SE_M_HEAL_BELL}wa{SE_M_GRASSWHISTLE}{SE_M_CHARGE}we{SE_M_REVERSAL}lad{SE_M_SUPERSONIC}{SE_M_HEAL_BELL}wa{SE_M_GRASSWHISTLE}a\n"
	.string "hotsho{SE_M_SPIT_UP}trainer!\p"
	.string "Here'{SE_M_GRASSWHISTLE}{SE_M_CHARGE}wor{SE_M_WATERFALL}o{SE_M_ACID_ARMOR}advice:\n"
	.string "Catc{SE_M_TRI_ATTACK}lot{SE_M_GRASSWHISTLE}o{SE_M_ACID_ARMOR}POKéMON!\p"
	.string "Trea{SE_M_SPIT_UP}the{SE_M_MILK_DRINK}al{SE_M_BATON_PASS}wit{SE_M_TRI_ATTACK}kindness!$"

