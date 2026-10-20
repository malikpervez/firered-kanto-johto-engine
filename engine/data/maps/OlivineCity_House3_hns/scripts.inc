@ Johto (data/maps/OlivineCity_House3_hns/scripts.inc), as built into the FireRed game.

OlivineCity_House3_hns_MapScripts::
	.byte 0

OlivineCityHouse3_EventScriptFishingGuru::
	lock
	faceplayer
	checkitem ITEM_GOOD_ROD
	goto_if_eq VAR_RESULT, TRUE, OlivineCityHouse3_EventScriptFishingGuru2
	msgbox OlivineCity_Text_OfferGoodRod, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, FALSE, OlivineCityHouse3_EventScriptFishingGuruRefused
	msgbox OlivineCity_Text_GiveGoodRod, MSGBOX_DEFAULT
	giveitem ITEM_GOOD_ROD
	msgbox OlivineCity_Text_GaveGoodRod, MSGBOX_DEFAULT
	closemessage
	release
	end

OlivineCityHouse3_EventScriptFishingGuru2::
	msgbox OlivineCity_Text_HaveGoodRod, MSGBOX_DEFAULT
	closemessage
	release
	end

OlivineCityHouse3_EventScriptFishingGuruRefused::
	msgbox OlivineCity_Text_DontWantGoodRod, MSGBOX_DEFAULT
	closemessage
	release
	end

OlivineCity_Text_OfferGoodRod:
	.string "OLIVIN{SE_M_SWORDS_DANCE}i{SE_M_GRASSWHISTLE}o{SE_M_ATTRACT}th{SE_M_REVERSAL}sea!\p"
	.string "An{SE_M_WATERFALL}i{SE_M_ACID_ARMOR}it'{SE_M_GRASSWHISTLE}o{SE_M_ATTRACT}th{SE_M_REVERSAL}sea{SE_M_SUPERSONIC}there\n"
	.string "ar{SE_M_REVERSAL}boun{SE_M_WATERFALL}t{SE_M_ATTRACT2}b{SE_M_REVERSAL}fish!\p"
	.string "I'v{SE_M_REVERSAL}fishe{SE_M_WATERFALL}her{SE_M_REVERSAL}fo{SE_M_SAND_TOMB}3{SE_M_BITE}years.\p"
	.string "Woul{SE_M_WATERFALL}yo{SE_M_DIVE}lik{SE_M_REVERSAL}t{SE_M_ATTRACT2}fac{SE_M_REVERSAL}th{SE_M_REVERSAL}sea\n"
	.string "an{SE_M_WATERFALL}tr{SE_M_YAWN}you{SE_M_SAND_TOMB}han{SE_M_WATERFALL}a{SE_M_SPIT_UP}fishing?$"

OlivineCity_Text_GiveGoodRod:
	.string "Ah{SE_M_SUPERSONIC}hahah{SE_M_DRAGON_RAGE}W{SE_M_REVERSAL}hav{SE_M_REVERSAL}ourselves\n"
	.string "{SE_M_CHARGE}ne{SE_M_TWISTER}angle{SE_M_SAND_TOMB}i{SE_M_ATTRACT}th{SE_M_REVERSAL}making!$"

OlivineCity_Text_GaveGoodRod:
	.string "Fis{SE_M_TRI_ATTACK}aren'{SE_M_SPIT_UP}onl{SE_M_YAWN}foun{SE_M_WATERFALL}i{SE_M_ATTRACT}the\n"
	.string "sea--they'r{SE_M_REVERSAL}whereve{SE_M_SAND_TOMB}there's\l"
	.string "water.\p"
	.string "B{SE_M_YAWN}th{SE_M_REVERSAL}way{SE_M_SUPERSONIC}you{SE_M_SAND_TOMB}POKéDE{SE_M_LOCK_ON}shows\n"
	.string "fishin{SE_M_SANDSTORM}group{SE_M_GRASSWHISTLE}fo{SE_M_SAND_TOMB}POKéMON.\p"
	.string "Differen{SE_M_SPIT_UP}spot{SE_M_GRASSWHISTLE}ma{SE_M_YAWN}contain\n"
	.string "simila{SE_M_SAND_TOMB}fis{SE_M_TRI_ATTACK}types.$"

OlivineCity_Text_DontWantGoodRod:
	.string "Whaaat{SE_M_SING}Yo{SE_M_DIVE}don'{SE_M_SPIT_UP}lik{SE_M_REVERSAL}t{SE_M_ATTRACT2}fish!?\n"
	.string "That'{SE_M_GRASSWHISTLE}incomprehensible!$"

OlivineCity_Text_HaveGoodRod:
	.string "Ho{SE_M_TWISTER}ar{SE_M_REVERSAL}things?\n"
	.string "Di{SE_M_WATERFALL}yo{SE_M_DIVE}lan{SE_M_WATERFALL}th{SE_M_REVERSAL}bi{SE_M_SANDSTORM}one?$"

