@ Johto (data/maps/Route39_Barn_hns/scripts.inc), as built into the FireRed game.

Route39_Barn_hns_MapScripts::
	.byte 0

Route39_Barn_EventScript_Miltank::
	lock
	faceplayer
	waitse
	playmoncry 241, 0
	goto_if_eq 20595, 0, Route39_Barn_EventScript_Miltank_NeedBerries5
	goto_if_eq 20595, 1, Route39_Barn_EventScript_Miltank_NeedBerries4
	goto_if_eq 20595, 2, Route39_Barn_EventScript_Miltank_NeedBerries3
	goto_if_eq 20595, 3, Route39_Barn_EventScript_Miltank_NeedBerries2
	goto_if_eq 20595, 4, Route39_Barn_EventScript_Miltank_NeedBerries1
	msgbox Route39_Text_MoomooHappyMoo, MSGBOX_DEFAULT
	waitmoncry
	release
	end

Route39_Barn_EventScript_Miltank_NeedBerries5::
	msgbox Route39_Text_MoomooWeakMoo, MSGBOX_DEFAULT
	waitmoncry
	closemessage
	delay 10
	msgbox Route39_Text_BarnCryIsWeak, MSGBOX_YESNO
	call_if_eq 32781, FALSE, Route39_Barn_EventScript_Miltank_Refused

	checkitem ITEM_ORAN_BERRY
	goto_if_eq 32781, FALSE, Route39_Barn_EventScript_Miltank_NoBerries
	removeitem ITEM_ORAN_BERRY, 1
	playse 1
	msgbox Route39_Text_BarnGaveBerry, MSGBOX_AUTOCLOSE
	waitse
	msgbox Route39_Text_BarnLittleHealthier, MSGBOX_DEFAULT
	closemessage

	setvar 20595, 1
	release
	end

Route39_Barn_EventScript_Miltank_NeedBerries4::
	msgbox Route39_Text_MoomooWeakMoo, MSGBOX_DEFAULT
	waitmoncry
	closemessage
	delay 10
	msgbox Route39_Text_BarnCryIsWeak, MSGBOX_YESNO
	call_if_eq 32781, FALSE, Route39_Barn_EventScript_Miltank_Refused

	checkitem ITEM_ORAN_BERRY
	goto_if_eq 32781, FALSE, Route39_Barn_EventScript_Miltank_NoBerries
	removeitem ITEM_ORAN_BERRY, 1
	playse 1
	msgbox Route39_Text_BarnGaveBerry, MSGBOX_AUTOCLOSE
	waitse
	msgbox Route39_Text_BarnLittleHealthier, MSGBOX_DEFAULT
	closemessage

	setvar 20595, 2
	release
	end

Route39_Barn_EventScript_Miltank_NeedBerries3::
	msgbox Route39_Text_MoomooWeakMoo, MSGBOX_DEFAULT
	waitmoncry
	closemessage
	delay 10
	msgbox Route39_Text_BarnCryIsWeak, MSGBOX_YESNO
	call_if_eq 32781, FALSE, Route39_Barn_EventScript_Miltank_Refused
	checkitem ITEM_ORAN_BERRY
	goto_if_eq 32781, FALSE, Route39_Barn_EventScript_Miltank_NoBerries
	removeitem ITEM_ORAN_BERRY, 1
	playse 1
	msgbox Route39_Text_BarnGaveBerry, MSGBOX_AUTOCLOSE
	waitse
	msgbox Route39_Text_BarnQuiteHealthy, MSGBOX_DEFAULT
	closemessage
	setvar 20595, 3
	release
	end

Route39_Barn_EventScript_Miltank_NeedBerries2::
	msgbox Route39_Text_MoomooWeakMoo, MSGBOX_DEFAULT
	waitmoncry
	closemessage
	delay 10
	msgbox Route39_Text_BarnCryIsWeak, MSGBOX_YESNO
	call_if_eq 32781, FALSE, Route39_Barn_EventScript_Miltank_Refused
	checkitem ITEM_ORAN_BERRY
	goto_if_eq 32781, FALSE, Route39_Barn_EventScript_Miltank_NoBerries
	removeitem ITEM_ORAN_BERRY, 1
	playse 1
	msgbox Route39_Text_BarnGaveBerry, MSGBOX_AUTOCLOSE
	waitse
	msgbox Route39_Text_BarnQuiteHealthy, MSGBOX_DEFAULT
	closemessage
	setvar 20595, 4
	release
	end

Route39_Barn_EventScript_Miltank_NeedBerries1::
	msgbox Route39_Text_MoomooWeakMoo, MSGBOX_DEFAULT
	waitmoncry
	closemessage
	delay 10
	msgbox Route39_Text_BarnCryIsWeak, MSGBOX_YESNO
	call_if_eq 32781, FALSE, Route39_Barn_EventScript_Miltank_Refused
	checkitem ITEM_ORAN_BERRY
	goto_if_eq 32781, FALSE, Route39_Barn_EventScript_Miltank_NoBerries
	removeitem ITEM_ORAN_BERRY, 1
	playse 1
	msgbox Route39_Text_BarnGaveBerry, MSGBOX_AUTOCLOSE
	waitse
	msgbox Route39_Text_BarnTotallyHealthy, MSGBOX_DEFAULT
	playfanfare 368
	waitfanfare
	closemessage
	setvar 20595, 5
	release
	end

Route39_Barn_EventScript_Miltank_Refused::
	msgbox Route39_Text_BarnRefusedBerry, MSGBOX_DEFAULT
	closemessage
	release
	end

Route39_Barn_EventScript_Miltank_NoBerries::
	msgbox Route39_Text_BarnNoBerries, MSGBOX_DEFAULT
	release
	end

Route39_Barn_EventScript_Twins::
	lock
	faceplayer
	goto_if_eq 20595, 5, Route39_Barn_EventScript_TwinsAfter
	msgbox Route39_Text_BarnTwinMoomooIsSick, MSGBOX_DEFAULT
	closemessage
	release
	end

Route39_Barn_EventScript_TwinsAfter::
	msgbox Route39_Text_BarnTwinFeedingMoomoo
	closemessage
	release
	end

Route39_Text_BarnTwinMoomooIsSick:
	.string "MOOMO{SE_M_SOLAR_BEAM}i{SE_M_GRASSWHISTLE}sick…\p"
	.string "Sh{SE_M_REVERSAL}need{SE_M_GRASSWHISTLE}lot{SE_M_GRASSWHISTLE}o{SE_M_ACID_ARMOR}ORA{SE_M_PSYBEAM2}BERRIES.$"

Route39_Text_BarnTwinFeedingMoomoo:
	.string "MOOMO{SE_M_SOLAR_BEAM}i{SE_M_GRASSWHISTLE}al{SE_M_BATON_PASS}better!\n"
	.string "Than{SE_M_ENCORE2}you!$"

Route39_Text_MoomooWeakMoo:
	.string "MILTANK{SE_M_HEAT_WAVE}…Moo…$"

Route39_Text_BarnCryIsWeak:
	.string "It{SE_M_GRASSWHISTLE}cr{SE_M_YAWN}i{SE_M_GRASSWHISTLE}weak…\n"
	.string "Giv{SE_M_REVERSAL}a{SE_M_ATTRACT}ORA{SE_M_PSYBEAM2}BERR{SE_M_MOONLIGHT}t{SE_M_ATTRACT2}MILTANK?$"

Route39_Text_MoomooHappyMoo:
	.string "MILTANK{SE_M_HEAT_WAVE}Mooo!$"

Route39_Text_BarnGaveBerry:
	.string "{PLAYER} gav{SE_M_REVERSAL}a{SE_M_ATTRACT}ORA{SE_M_PSYBEAM2}BERR{SE_M_MOONLIGHT}to\n"
	.string "MILTANK.$"

Route39_Text_BarnLittleHealthier:
	.string "MILTAN{SE_M_SNORE}becam{SE_M_REVERSAL}{SE_M_CHARGE}little\n"
	.string "healthier!$"

Route39_Text_BarnQuiteHealthy:
	.string "MILTAN{SE_M_SNORE}becam{SE_M_REVERSAL}quite\n"
	.string "healthy!$"

Route39_Text_BarnTotallyHealthy:
	.string "MILTAN{SE_M_SNORE}becam{SE_M_REVERSAL}totally\n"
	.string "healthy!$"

Route39_Text_BarnNoBerries:
	.string "{PLAYER} ha{SE_M_GRASSWHISTLE}n{SE_M_ATTRACT2}ORA{SE_M_PSYBEAM2}BERRIES…$"

Route39_Text_BarnRefusedBerry:
	.string "{PLAYER} wouldn'{SE_M_SPIT_UP}giv{SE_M_REVERSAL}an\n"
	.string "ORA{SE_M_PSYBEAM2}BERRY.\p"
	.string "MILTAN{SE_M_SNORE}look{SE_M_GRASSWHISTLE}sad.$"

