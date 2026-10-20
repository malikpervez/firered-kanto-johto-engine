@ Johto (data/maps/AzaleaTown_Mart_hns/scripts.inc), as built into the FireRed game.

AzaleaTown_Mart_hns_MapScripts::
	.byte 0

AzaleaTown_Mart_EventScriptCooltrainerM::
	lock
	faceplayer
	msgbox AzaleaMart_Text_CooltrainerM, MSGBOX_DEFAULT
	closemessage
	release
	end

AzaleaTown_Mart_EventScriptBugCatcher::
	lock
	faceplayer
	msgbox AzaleaMart_Text_BugCatcher, MSGBOX_DEFAULT
	closemessage
	release
	end

AzaleaMart_Text_CooltrainerM:
	.string "Ar{SE_M_REVERSAL}yo{SE_M_DIVE}abl{SE_M_REVERSAL}t{SE_M_ATTRACT2}bu{SE_M_YAWN}{SE_M_CHARGE}GREA{SE_M_SWIFT}BALL?\n"
	.string "Al{SE_M_BATON_PASS}{SE_M_HEAL_BELL}ca{SE_M_ATTRACT}bu{SE_M_YAWN}ar{SE_M_REVERSAL}POK{SE_U}BALLS.\p"
	.string "{SE_M_HEAL_BELL}hear{SE_M_WATERFALL}tha{SE_M_SPIT_UP}mor{SE_M_REVERSAL}item{SE_M_GRASSWHISTLE}become\n"
	.string "availabl{SE_M_REVERSAL}t{SE_M_ATTRACT2}bu{SE_M_YAWN}whe{SE_M_ATTRACT}yo{SE_M_DIVE}earn\l"
	.string "GY{SE_M_GIGA_DRAIN}BADGES!\p"
	.string "{SE_M_HEAL_BELL}wis{SE_M_TRI_ATTACK}KUR{SE_M_SWIFT}woul{SE_M_WATERFALL}mak{SE_M_REVERSAL}m{SE_M_REVERSAL}some\n"
	.string "o{SE_M_ACID_ARMOR}hi{SE_M_GRASSWHISTLE}custo{SE_M_MILK_DRINK}BALLS.$"

AzaleaMart_Text_BugCatcher:
	.string "{SE_M_BONEMERANG}GREA{SE_M_SWIFT}BAL{SE_M_BRICK_BREAK}i{SE_M_GRASSWHISTLE}bette{SE_M_SAND_TOMB}fo{SE_M_SAND_TOMB}catch-\n"
	.string "in{SE_M_SANDSTORM}POKéMO{SE_M_PSYBEAM2}tha{SE_M_ATTRACT}{SE_M_CHARGE}POK{SE_U}BALL.\p"
	.string "Bu{SE_M_SPIT_UP}KURT'{SE_M_GRASSWHISTLE}migh{SE_M_SPIT_UP}b{SE_M_REVERSAL}bette{SE_M_SAND_TOMB}some-\n"
	.string "times.$"

