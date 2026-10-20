@ Johto (data/maps/CherrygroveCity_Mart_hns/scripts.inc), as built into the FireRed game.

CherrygroveCity_Mart_hns_MapScripts::
	.byte 0

Cherrygrove_Pokemart_EventScript_Clerk::
	lock
	faceplayer
	message J_gText_HowMayIServeYou
	waitmessage
	goto_if_ge JOHTO_VAR_NEWBARK_TOWN_STATE, 5, Cherrygrove_Pokemart_EventScript_Clerk2
	pokemart Cherrygrove_Pokemart_Pokemart
	msgbox J_gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

Cherrygrove_Pokemart_EventScript_Youngster::
	lock
	faceplayer
	msgbox Cherrygrove_Pokemart_Text_Youngster, MSGBOX_DEFAULT
	closemessage
	release
	end

Cherrygrove_Pokemart_EventScript_Bugcatcher::
	lock
	faceplayer
	goto_if_eq JOHTO_VAR_NEWBARK_TOWN_STATE, 5, Cherrygrove_Pokemart_EventScript_Bugcatcher2
	msgbox Cherrygrove_Pokemart_Text_CooltrainerM, MSGBOX_DEFAULT
	closemessage
	release
	end

Cherrygrove_Pokemart_EventScript_Bugcatcher2::
	msgbox Cherrygrove_Pokemart_Text_CooltrainerM_PokeBallsInStock, MSGBOX_DEFAULT
	closemessage
	release
	end

Cherrygrove_Pokemart_EventScript_Clerk2::
	pokemart 0
	msgbox J_gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 3

Cherrygrove_Pokemart_Pokemart:
	.2byte ITEM_POTION
	.2byte ITEM_ANTIDOTE
	.2byte ITEM_NONE
	release
	end

Cherrygrove_Pokemart_Text_CooltrainerM:
	.string "They'r{SE_M_REVERSAL}fres{SE_M_TRI_ATTACK}ou{SE_M_SPIT_UP}o{SE_M_ACID_ARMOR}POK{SE_U}BALLS!\p"
	.string "Whe{SE_M_ATTRACT}wil{SE_M_BATON_PASS}the{SE_M_YAWN}ge{SE_M_SPIT_UP}mor{SE_M_REVERSAL}o{SE_M_ACID_ARMOR}them?$"

Cherrygrove_Pokemart_Text_CooltrainerM_PokeBallsInStock:
	.string "POK{SE_U}BALL{SE_M_SKETCH}ar{SE_M_REVERSAL}i{SE_M_ATTRACT}stock!\n"
	.string "No{SE_M_TWISTER}{SE_M_HEAL_BELL}ca{SE_M_ATTRACT}catc{SE_M_TRI_ATTACK}POKéMON!$"

Cherrygrove_Pokemart_Text_Youngster:
	.string "Whe{SE_M_ATTRACT}{SE_M_HEAL_BELL}wa{SE_M_GRASSWHISTLE}walkin{SE_M_SANDSTORM}i{SE_M_ATTRACT}th{SE_M_REVERSAL}grass{SE_M_SUPERSONIC}a\n"
	.string "bu{SE_M_SANDSTORM}POKéMO{SE_M_PSYBEAM2}poisone{SE_M_WATERFALL}m{SE_M_YAWN}POKéMON!\p"
	.string "{SE_M_HEAL_BELL}jus{SE_M_SPIT_UP}kep{SE_M_SPIT_UP}going{SE_M_SUPERSONIC}bu{SE_M_SPIT_UP}the{SE_M_ATTRACT}my\n"
	.string "POKéMO{SE_M_PSYBEAM2}fainted.\p"
	.string "Yo{SE_M_DIVE}shoul{SE_M_WATERFALL}kee{SE_M_MORNING_SUN}a{SE_M_ATTRACT}ANTIDOTE\n"
	.string "wit{SE_M_TRI_ATTACK}you.$"

