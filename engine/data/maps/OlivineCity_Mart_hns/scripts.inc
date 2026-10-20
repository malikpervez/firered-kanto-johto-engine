@ Johto (data/maps/OlivineCity_Mart_hns/scripts.inc), as built into the FireRed game.

OlivineCity_Mart_hns_MapScripts::
	.byte 0

OlivineCity_EventScript_Trainer1::
	lock
	faceplayer
	msgbox OlivineCity_Text_MartCooltrainerF, MSGBOX_DEFAULT
	closemessage
	release
	end

OlivineCity_EventScript_Lass::
	lock
	faceplayer
	msgbox OlivineCity_Text_MartLass, MSGBOX_DEFAULT
	closemessage
	release
	end

OlivineCity_Text_MartCooltrainerF:
	.string "D{SE_M_ATTRACT2}you{SE_M_SAND_TOMB}POKéMO{SE_M_PSYBEAM2}alread{SE_M_YAWN}know\n"
	.string "th{SE_M_REVERSAL}mov{SE_M_REVERSAL}fo{SE_M_SAND_TOMB}carryin{SE_M_SANDSTORM}people\l"
	.string "acros{SE_M_GRASSWHISTLE}water?$"

OlivineCity_Text_MartLass:
	.string "M{SE_M_YAWN}BUTTERFRE{SE_M_SWORDS_DANCE}cam{SE_M_REVERSAL}fro{SE_M_MILK_DRINK}my\n"
	.string "boyfrien{SE_M_WATERFALL}overseas.\p"
	.string "I{SE_M_SPIT_UP}carrie{SE_M_WATERFALL}som{SE_M_REVERSAL}MAI{SE_M_BRICK_BREAK}fro{SE_M_MILK_DRINK}him.\p"
	.string "Wan{SE_M_SPIT_UP}t{SE_M_ATTRACT2}kno{SE_M_TWISTER}wha{SE_M_SPIT_UP}i{SE_M_SPIT_UP}says?\p"
	.string "Let'{SE_M_GRASSWHISTLE}see..{SE_M_PERISH_SONG}Nope{SE_M_DRAGON_RAGE}It'{SE_M_GRASSWHISTLE}a\n"
	.string "secret!$"

