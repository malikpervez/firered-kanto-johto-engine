@ Johto (data/maps/GoldenrodCity_UndergroundEntrance_hns/scripts.inc), as built into the FireRed game.

GoldenrodCity_UndergroundEntrance_hns_MapScripts::
	.byte 0

GoldenrodUnderground_EventScript_SuperNerd::
	lock
	faceplayer
	msgbox GoldenrodUnderground1_Text_SuperNerd, MSGBOX_DEFAULT
	closemessage
	lock
	release
	end

GoldenrodUnderground_EventScript_Teacher::
	lock
	faceplayer
	msgbox GoldenrodUnderground1_Text_Teacher, MSGBOX_DEFAULT
	closemessage
	lock
	release
	end

GoldenrodUnderground1_Text_SuperNerd:
	.string "{SE_M_HEAL_BELL}wa{SE_M_GRASSWHISTLE}challenge{SE_M_WATERFALL}t{SE_M_ATTRACT2}{SE_M_CHARGE}battle\n"
	.string "downstairs.\p"
	.string "It'{SE_M_GRASSWHISTLE}roug{SE_M_TRI_ATTACK}dow{SE_M_ATTRACT}there{SE_M_PERISH_SONG}You'd\n"
	.string "bette{SE_M_SAND_TOMB}b{SE_M_REVERSAL}careful.$"

GoldenrodUnderground1_Text_Teacher:
	.string "Ther{SE_M_REVERSAL}ar{SE_M_REVERSAL}som{SE_M_REVERSAL}shop{SE_M_GRASSWHISTLE}downstairs…\n"
	.string "Bu{SE_M_SPIT_UP}ther{SE_M_REVERSAL}ar{SE_M_REVERSAL}als{SE_M_ATTRACT2}trainers.\p"
	.string "I'{SE_M_MILK_DRINK}scare{SE_M_WATERFALL}t{SE_M_ATTRACT2}g{SE_M_ATTRACT2}dow{SE_M_ATTRACT}there.$"

