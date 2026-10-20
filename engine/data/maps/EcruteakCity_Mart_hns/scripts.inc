@ Johto (data/maps/EcruteakCity_Mart_hns/scripts.inc), as built into the FireRed game.

EcruteakCity_Mart_hns_MapScripts::
	.byte 0

EcruteakCity_Mart_EventScript_Nerd::
	lock
	faceplayer
	msgbox EcruteakMart_Text_SuperNerd, MSGBOX_DEFAULT
	closemessage
	release
	end

EcruteakCity_Mart_EventScript_Granny::
	lock
	faceplayer
	msgbox EcruteakMart_Text_Granny, MSGBOX_DEFAULT
	closemessage
	release
	end

EcruteakMart_Text_SuperNerd:
	.string "M{SE_M_YAWN}EEVE{SE_M_SWORDS_DANCE}evolve{SE_M_WATERFALL}int{SE_M_ATTRACT2}a{SE_M_ATTRACT}ESPEON.\p"
	.string "Bu{SE_M_SPIT_UP}m{SE_M_YAWN}friend'{SE_M_GRASSWHISTLE}EEVE{SE_M_SWORDS_DANCE}turne{SE_M_WATERFALL}into\n"
	.string "a{SE_M_ATTRACT}UMBREON.\p"
	.string "{SE_M_HEAL_BELL}wonde{SE_M_SAND_TOMB}why{SE_M_SING}W{SE_M_REVERSAL}bot{SE_M_TRI_ATTACK}wer{SE_M_REVERSAL}raising\n"
	.string "ou{SE_M_SAND_TOMB}EEVE{SE_M_SWORDS_DANCE}i{SE_M_ATTRACT}th{SE_M_REVERSAL}sam{SE_M_REVERSAL}way…$"

EcruteakMart_Text_Granny:
	.string "I{SE_M_ACID_ARMOR}yo{SE_M_DIVE}us{SE_M_REVERSAL}REVIVE{SE_M_SUPERSONIC}{SE_M_CHARGE}POKéMO{SE_M_PSYBEAM2}that's\n"
	.string "fainte{SE_M_WATERFALL}wil{SE_M_BATON_PASS}wak{SE_M_REVERSAL}righ{SE_M_SPIT_UP}up.$"

