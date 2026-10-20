@ Johto (data/maps/Gate_Route29_Route46_hns/scripts.inc), as built into the FireRed game.

Gate_Route29_Route46_hns_MapScripts::
	.byte 0

Gate_Route29_Route46_EventScript_Officer::
	lock
	faceplayer
	msgbox Gate_Route29_Route46_Text_Officer, MSGBOX_DEFAULT
	closemessage
	release
	end

Gate_Route29_Route46_EventScript_Youngster::
	lock
	faceplayer
	msgbox Gate_Route29_Route46_Text_Youngster, MSGBOX_DEFAULT
	closemessage
	release
	end

Gate_Route29_Route46_Text_Officer:
	.string "Yo{SE_M_DIVE}can'{SE_M_SPIT_UP}clim{SE_M_STRENGTH}ledges.\p"
	.string "Bu{SE_M_SPIT_UP}yo{SE_M_DIVE}ca{SE_M_ATTRACT}jum{SE_M_MORNING_SUN}dow{SE_M_ATTRACT}from\n"
	.string "the{SE_M_MILK_DRINK}t{SE_M_ATTRACT2}tak{SE_M_REVERSAL}{SE_M_CHARGE}shortcut.$"

Gate_Route29_Route46_Text_Youngster:
	.string "Differen{SE_M_SPIT_UP}kind{SE_M_GRASSWHISTLE}o{SE_M_ACID_ARMOR}POKéMON\n"
	.string "appea{SE_M_SAND_TOMB}pas{SE_M_SPIT_UP}here.\p"
	.string "I{SE_M_ACID_ARMOR}yo{SE_M_DIVE}wan{SE_M_SPIT_UP}t{SE_M_ATTRACT2}catc{SE_M_TRI_ATTACK}the{SE_M_MILK_DRINK}all,\n"
	.string "yo{SE_M_DIVE}hav{SE_M_REVERSAL}t{SE_M_ATTRACT2}loo{SE_M_ENCORE2}everywhere.$"

