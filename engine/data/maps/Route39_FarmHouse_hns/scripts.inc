@ Johto (data/maps/Route39_FarmHouse_hns/scripts.inc), as built into the FireRed game.

Route39_FarmHouse_hns_MapScripts::
	.byte 0

Route39House_EventScript_FarmerF::
	lock
	faceplayer
	goto_if_eq JOHTO_VAR_ROUTE39_BARN, 5, Route39House_EventScript_FarmerFAfter
	msgbox Route39_Text_FarmerFInTrouble, MSGBOX_DEFAULT
	closemessage
	release
	end

Route39House_EventScript_FarmerFAfter::
	goto_if_set JOHTO_FLAG_GOT_TM_SNATCH, Route39House_EventScript_FarmerFAfterTM
	msgbox Route39_Text_FarmerFHealedMiltank, MSGBOX_DEFAULT
	giveitem ITEM_TM_SNATCH
	msgbox Route39_Text_FarmerFSnatchSpeech, MSGBOX_DEFAULT
	closemessage
	setflag JOHTO_FLAG_GOT_TM_SNATCH
	release
	end

Route39House_EventScript_FarmerFAfterTM::
	msgbox Route39_Text_FarmerFSnatchSpeech, MSGBOX_DEFAULT
	closemessage
	release
	end

Route39_FarmHouse_EventScript_FarmerM::
	lock
	faceplayer
	goto_if_lt JOHTO_VAR_ROUTE39_BARN, 5, Route39_FarmHouse_EventScript_FarmerM_Sick
	showmoneybox 0, 0
	msgbox Route39_Text_FarmerMBuyMilk, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, TRUE, Route39_FarmHouse_EventScript_FarmerMBuyMilk
	msgbox Route39_Text_FarmerMNoSale, MSGBOX_DEFAULT
	hidemoneybox
	closemessage
	end

Route39_FarmHouse_EventScript_FarmerMBuyMilk::
	checkmoney 500, 0
	goto_if_eq VAR_RESULT, FALSE, Route39_FarmHouse_EventScript_FarmerM_NotEnough
	additem ITEM_MOOMOO_MILK
	goto_if_eq VAR_RESULT, FALSE, Route39_FarmHouse_EventScript_FarmerM_BagFull
	removemoney 500
	updatemoneybox 0
	msgbox Route39FarmHouse_Text_WouldYouLikeAnother, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, TRUE, Route39_FarmHouse_EventScript_FarmerMBuyMilk


	msgbox Route39_Text_FarmerMGotMilk, MSGBOX_DEFAULT
	closemessage
	playse MUS_OBTAIN_ITEM
	msgbox Route39_Text_GotMilk, MSGBOX_DEFAULT
	closemessage
	hidemoneybox
	release
	end

Route39_FarmHouse_EventScript_FarmerM_Sick::
	msgbox Route39_Text_FarmerMSickCow, MSGBOX_DEFAULT
	closemessage
	release
	end

Route39_FarmHouse_EventScript_FarmerM_BagFull::
	msgbox Route39_Text_FarmerMNoRoom, MSGBOX_DEFAULT
	hidemoneybox
	closemessage
	release
	end

Route39_FarmHouse_EventScript_FarmerM_NotEnough::
	msgbox Route39_Text_FarmerMNoMoney, MSGBOX_DEFAULT
	closemessage
	hidemoneybox
	release
	end

Route39_Text_FarmerMSickCow:
	.string "M{SE_M_YAWN}MILTAN{SE_M_SNORE}ain'{SE_M_SPIT_UP}givin{SE_M_ABSORB}me\n"
	.string "mil{SE_M_ENCORE2}n{SE_M_ATTRACT2}more.\p"
	.string "Thi{SE_M_GRASSWHISTLE}her{SE_M_REVERSAL}FARM'{SE_M_GRASSWHISTLE}go{SE_M_SPIT_UP}famou{SE_M_GRASSWHISTLE}milk.\p"
	.string "Mos{SE_M_SPIT_UP}everyon{SE_M_REVERSAL}want{SE_M_GRASSWHISTLE}{SE_M_CHARGE}drink.\p"
	.string "It'l{SE_M_BATON_PASS}giv{SE_M_REVERSAL}m{SE_M_REVERSAL}lot{SE_M_GRASSWHISTLE}o{SE_M_ABSORB}mil{SE_M_ENCORE2}if'n\n"
	.string "{SE_M_HEAL_BELL}fee{SE_M_WATERFALL}i{SE_M_SPIT_UP}lot{SE_M_GRASSWHISTLE}o{SE_M_ABSORB}BERRIES,\l"
	.string "{SE_M_HEAL_BELL}reckon.$"

Route39_Text_FarmerMBuyMilk:
	.string "How'{SE_M_WATERFALL}yo{SE_M_DIVE}lik{SE_M_REVERSAL}m{SE_M_YAWN}MOOMO{SE_M_SOLAR_BEAM}MILK?\p"
	.string "It'{SE_M_GRASSWHISTLE}m{SE_M_YAWN}prid{SE_M_REVERSAL}an{SE_M_WATERFALL}joy{SE_M_SUPERSONIC}there.\p"
	.string "Giv{SE_M_REVERSAL}i{SE_M_SPIT_UP}t{SE_M_ATTRACT2}POKéMO{SE_M_PSYBEAM2}t{SE_M_ATTRACT2}restor{SE_M_REVERSAL}HP!\p"
	.string "I'l{SE_M_BATON_PASS}giv{SE_M_REVERSAL}i{SE_M_SPIT_UP}t{SE_M_ATTRACT2}y{SE_M_CHARGE}fe{SE_M_SAND_TOMB}just\n"
	.string "¥500.$"

Route39_Text_FarmerMGotMilk:
	.string "Her{SE_M_REVERSAL}y{SE_M_CHARGE}go!\n"
	.string "Drin{SE_M_ENCORE2}up'{SE_M_ATTRACT}enjoy!$"

Route39_Text_FarmerMNoMoney:
	.string "Sorry{SE_M_SUPERSONIC}there.\n"
	.string "N{SE_M_ATTRACT2}cash{SE_M_SUPERSONIC}n{SE_M_ATTRACT2}sale!$"

Route39_Text_FarmerMNoRoom:
	.string "{SE_M_HEAL_BELL}recko{SE_M_ATTRACT}ye{SE_M_SAND_TOMB}PACK'{SE_M_GRASSWHISTLE}full.$"

Route39_Text_FarmerMNoSale:
	.string "Yo{SE_M_DIVE}don'{SE_M_SPIT_UP}wan{SE_M_SPIT_UP}it?\n"
	.string "Com{SE_M_REVERSAL}again{SE_M_SUPERSONIC}hear?$"

Route39FarmHouse_Text_WouldYouLikeAnother:
	.string "Ho{SE_M_TWISTER}bou{SE_M_SPIT_UP}another?$"

Route39_Text_GotMilk:
	.string "{PLAYER} go{SE_M_SPIT_UP}MOOMO{SE_M_SOLAR_BEAM}MILK.$"

Route39_Text_FarmerMMilking:
	.string "{SE_M_HEAL_BELL}bes{SE_M_SPIT_UP}g{SE_M_ATTRACT2}d{SE_M_ATTRACT2}m{SE_M_YAWN}milkin'.$"

Route39_Text_FarmerFInTrouble:
	.string "Ou{SE_M_SAND_TOMB}mil{SE_M_ENCORE2}eve{SE_M_ATTRACT}goe{SE_M_GRASSWHISTLE}ou{SE_M_SPIT_UP}to\n"
	.string "KANTO.\p"
	.string "S{SE_M_ATTRACT2}i{SE_M_ACID_ARMOR}ou{SE_M_SAND_TOMB}ow{SE_M_ATTRACT}MILTAN{SE_M_SNORE}won't\n"
	.string "giv{SE_M_REVERSAL}u{SE_M_GRASSWHISTLE}an{SE_M_YAWN}milk{SE_M_SUPERSONIC}we'r{SE_M_REVERSAL}i{SE_M_ATTRACT}trouble.$"

Route39_Text_FarmerFHealedMiltank:
	.string "Yo{SE_M_DIVE}fixe{SE_M_WATERFALL}ou{SE_M_SAND_TOMB}MILTANK{SE_M_SUPERSONIC}hon.\n"
	.string "No{SE_M_TWISTER}i{SE_M_SPIT_UP}give{SE_M_GRASSWHISTLE}MOOMO{SE_M_SOLAR_BEAM}MIL{SE_M_SNORE}again.\p"
	.string "Here'{SE_M_GRASSWHISTLE}somethin{SE_M_ABSORB}fe{SE_M_SAND_TOMB}you{SE_M_SAND_TOMB}trouble.$"

Route39_Text_FarmerFSnatchSpeech:
	.string "Tha{SE_M_SPIT_UP}there'{SE_M_GRASSWHISTLE}SNATCH.\p"
	.string "It'{SE_M_GRASSWHISTLE}{SE_M_CHARGE}trick{SE_M_YAWN}mov{SE_M_REVERSAL}tha{SE_M_SPIT_UP}lets\n"
	.string "{SE_M_CHARGE}POKéMO{SE_M_PSYBEAM2}stea{SE_M_BATON_PASS}{SE_M_CHARGE}foe'{SE_M_GRASSWHISTLE}move\l"
	.string "righ{SE_M_SPIT_UP}befor{SE_M_REVERSAL}it'{SE_M_GRASSWHISTLE}used.\p"
	.string "I{SE_M_ACID_ARMOR}mor{SE_M_REVERSAL}tha{SE_M_ATTRACT}on{SE_M_REVERSAL}POKéMO{SE_M_PSYBEAM2}use\n"
	.string "SNATCH{SE_M_SUPERSONIC}onl{SE_M_YAWN}th{SE_M_REVERSAL}slowes{SE_M_SPIT_UP}one\l"
	.string "wil{SE_M_BATON_PASS}en{SE_M_WATERFALL}u{SE_M_MORNING_SUN}stealin{SE_M_SANDSTORM}th{SE_M_REVERSAL}move.\p"
	.string "Us{SE_M_REVERSAL}i{SE_M_SPIT_UP}smart{SE_M_SUPERSONIC}hon{SE_M_PERISH_SONG}Timin{SE_M_SANDSTORM}is\n"
	.string "everything.$"

