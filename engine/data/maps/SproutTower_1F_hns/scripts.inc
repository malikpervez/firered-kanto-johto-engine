@ Johto (data/maps/SproutTower_1F_hns/scripts.inc), as built into the FireRed game.

SproutTower_1F_hns_MapScripts::
	.byte 0

SproutTower_1F_EventScript_SageChow::
	trainerbattle_single TRAINER_JOHTO_CHOW_HNS, SproutTower_Text_SageChow_Seen, SproutTower_Text_SageChow_Beaten
	msgbox SproutTower_Text_SageChow_AfterBattle, MSGBOX_AUTOCLOSE
	end

SproutTower_1F_EventScript_Sage1::
	lock
	faceplayer
	msgbox SproutTower_Text_1F_Sage1, MSGBOX_DEFAULT
	closemessage
	release
	end

SproutTower_1F_EventScript_Sage2::
	lock
	faceplayer
	msgbox SproutTower_Text_1F_Sage2, MSGBOX_DEFAULT
	closemessage
	release
	end

SproutTower_1F_EventScript_Granny::
	lock
	faceplayer
	msgbox SproutTower_Text_1F_Granny, MSGBOX_DEFAULT
	closemessage
	release
	end

SproutTower_1F_EventScript_Teacher::
	lock
	faceplayer
	msgbox SproutTower_Text_1F_Teacher, MSGBOX_DEFAULT
	closemessage
	release
	end

SproutTower_1F_EventScript_ItemParalyzeHeal::
	finditem ITEM_PARALYZE_HEAL
	end

SproutTower_Text_SageChow_Seen:
	.string "W{SE_M_REVERSAL}stan{SE_M_WATERFALL}guar{SE_M_WATERFALL}i{SE_M_ATTRACT}thi{SE_M_GRASSWHISTLE}tower.\p"
	.string "Here{SE_M_SUPERSONIC}w{SE_M_REVERSAL}expres{SE_M_GRASSWHISTLE}ou{SE_M_SAND_TOMB}gratitude\n"
	.string "t{SE_M_ATTRACT2}hono{SE_M_SAND_TOMB}al{SE_M_BATON_PASS}POKéMON.$"

SproutTower_Text_SageChow_Beaten:
	.string "Th-Than{SE_M_ENCORE2}you!$"

SproutTower_Text_SageChow_AfterBattle:
	.string "Al{SE_M_BATON_PASS}livin{SE_M_SANDSTORM}being{SE_M_GRASSWHISTLE}coexist\n"
	.string "throug{SE_M_TRI_ATTACK}cooperation.\p"
	.string "W{SE_M_REVERSAL}mus{SE_M_SPIT_UP}alway{SE_M_GRASSWHISTLE}b{SE_M_REVERSAL}thankful\n"
	.string "fo{SE_M_SAND_TOMB}this.$"

SproutTower_Text_1F_Sage1:
	.string "Onl{SE_M_YAWN}i{SE_M_ACID_ARMOR}yo{SE_M_DIVE}reac{SE_M_TRI_ATTACK}th{SE_M_REVERSAL}to{SE_M_MORNING_SUN}will\n"
	.string "yo{SE_M_DIVE}obtai{SE_M_ATTRACT}a{SE_M_ATTRACT}HM.$"

SproutTower_Text_1F_Sage2:
	.string "SPROU{SE_M_SWIFT}TOWE{SE_M_MINIMIZE}wa{SE_M_GRASSWHISTLE}buil{SE_M_SPIT_UP}lon{SE_M_SANDSTORM}ago\n"
	.string "a{SE_M_GRASSWHISTLE}{SE_M_CHARGE}plac{SE_M_REVERSAL}fo{SE_M_SAND_TOMB}POKéMO{SE_M_PSYBEAM2}training.$"

SproutTower_Text_1F_Granny:
	.string "{SE_M_BONEMERANG}BELLSPROU{SE_M_SWIFT}ove{SE_M_SAND_TOMB}10{SE_M_BITE}feet\n"
	.string "tall…\p"
	.string "Peopl{SE_M_REVERSAL}sa{SE_M_YAWN}tha{SE_M_SPIT_UP}i{SE_M_SPIT_UP}becam{SE_M_REVERSAL}the\n"
	.string "cente{SE_M_SAND_TOMB}pilla{SE_M_SAND_TOMB}here.$"

SproutTower_Text_1F_Teacher:
	.string "Se{SE_M_REVERSAL}th{SE_M_REVERSAL}pilla{SE_M_SAND_TOMB}shaking?\p"
	.string "Peopl{SE_M_REVERSAL}ar{SE_M_REVERSAL}trainin{SE_M_SANDSTORM}upstairs.$"

SproutTower_Text_1F_Statue:
	.string "{SE_M_BONEMERANG}POKéMO{SE_M_PSYBEAM2}statue…\p"
	.string "I{SE_M_SPIT_UP}look{SE_M_GRASSWHISTLE}ver{SE_M_YAWN}distinguished.$"

