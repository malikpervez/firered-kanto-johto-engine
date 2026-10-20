@ Johto (data/maps/CianwoodShop_hns/scripts.inc), as built into the FireRed game.

CianwoodShop_hns_MapScripts::
	.byte 0

CianwoodShop_EventScriptMan::
	setvar JOHTO_VAR_OLIVINE_CITY_STATE, 4
	giveitem ITEM_SECRET_POTION
	end

CianwoodCity_EventScript_Pharmacist::
	lock
	faceplayer
	checkitem ITEM_SECRET_POTION
	goto_if_eq VAR_RESULT, TRUE, CianwoodCity_EventScript_PharmacistAfter
	goto_if_ge JOHTO_VAR_OLIVINE_CITY_STATE, 5, CianwoodCity_EventScript_PharmacistAfter
	msgbox CianwoodCity_Text_PharmacistGivePotion, MSGBOX_DEFAULT
	giveitem ITEM_SECRET_POTION
	closemessage
	setvar JOHTO_VAR_OLIVINE_CITY_STATE, 4
	release
	end

CianwoodCity_EventScript_PharmacistAfter::
	msgbox CianwoodCity_Text_PharmacistDescribePotion, MSGBOX_DEFAULT
	closemessage
	release
	end

CianwoodCity_Text_PharmacistGivePotion:
	.string "You{SE_M_SAND_TOMB}POKéMO{SE_M_PSYBEAM2}appea{SE_M_SAND_TOMB}t{SE_M_ATTRACT2}b{SE_M_REVERSAL}fine.\p"
	.string "I{SE_M_GRASSWHISTLE}somethin{SE_M_SANDSTORM}worryin{SE_M_SANDSTORM}you?\p"
	.string "…\p"
	.string "Th{SE_M_REVERSAL}LIGHTHOUS{SE_M_SWORDS_DANCE}POKéMO{SE_M_PSYBEAM2}i{SE_M_GRASSWHISTLE}in\n"
	.string "trouble?\p"
	.string "{SE_M_HEAL_BELL}go{SE_M_SPIT_UP}it!\p"
	.string "Thi{SE_M_GRASSWHISTLE}ough{SE_M_SPIT_UP}t{SE_M_ATTRACT2}d{SE_M_ATTRACT2}th{SE_M_REVERSAL}trick.$"

CianwoodCity_Text_ReceivedSecretpotion:
	.string "{PLAYER} receive{SE_M_WATERFALL}SECRE{SE_M_SWIFT}POTION.$"

CianwoodCity_Text_PharmacistDescribePotion:
	.string "M{SE_M_YAWN}SECRE{SE_M_SWIFT}POTIO{SE_M_PSYBEAM2}i{SE_M_GRASSWHISTLE}{SE_M_CHARGE}ta{SE_M_WATERFALL}too\n"
	.string "strong{SE_M_SUPERSONIC}s{SE_M_ATTRACT2}{SE_M_HEAL_BELL}onl{SE_M_YAWN}offe{SE_M_SAND_TOMB}i{SE_M_SPIT_UP}i{SE_M_ATTRACT}an\l"
	.string "emergency.$"

