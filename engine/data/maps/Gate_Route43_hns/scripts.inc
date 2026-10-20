@ Johto (data/maps/Gate_Route43_hns/scripts.inc), as built into the FireRed game.

Gate_Route43_hns_MapScripts::
	map_script 2, Gate_Route43_Rocket_OnFrame
	.byte 0

Gate_Route43_Rocket_OnFrame::
	map_script_2 16384, 0, Gate_Route43_RocketChecker
	.2byte 0

Gate_Route43_RocketChecker::
	setvar 16384, 1
	goto_if_eq 20578, 1, Gate_Route43_Rocket_EventScript_Shakedown
	goto_if_eq 20578, 2, Gate_Route43_Rocket_EventScript_Shakedown
	goto_if_eq 20578, 3, Gate_Route43_Rocket_EventScript_Shakedown
	goto_if_eq 20578, 4, Gate_Route43_Rocket_EventScript_Shakedown
	goto_if_eq 20578, 5, Gate_Route43_Rocket_EventScript_Shakedown
	end

Gate_Route43_Rocket_EventScript_Shakedown::
	lock
	showmoneybox 0, 0
	msgbox Gate_Route43_Rocket_Text_TollFee, MSGBOX_DEFAULT
	checkmoney 500
	goto_if_eq 32781, FALSE, Gate_Route43_Rocket_EventScript_ShakedownBroke
	removemoney 500
	playse 95
	updatemoneybox
	msgbox Gate_Route43_Rocket_Text_ThankYou, MSGBOX_DEFAULT
	hidemoneybox
	release
	end

Gate_Route43_Rocket_EventScript_ShakedownBroke::
	checkmoney 1
	goto_if_eq 32781, FALSE, Gate_Route43_Rocket_EventScript_KickOut
	msgbox Gate_Route43_Rocket_Text_AllYouGot, MSGBOX_DEFAULT
	removemoney 500
	playse 95
	updatemoneybox
	msgbox Gate_Route43_Rocket_Text_ThankYou, MSGBOX_DEFAULT
	hidemoneybox
	release
	end

Gate_Route43_Rocket_EventScript_KickOut::
	msgbox Gate_Route43_Rocket_Text_KickOut, MSGBOX_DEFAULT
	closemessage
	hidemoneybox
	release
	end

Gate_Route43_Rocket_EventScript_Policeman::
	lock
	faceplayer
	goto_if_set 8714, Gate_Route43_Rocket_EventScript_PolicemanAfter
	msgbox Route43Gate_Text_OfficerFoundTM, MSGBOX_DEFAULT
	giveitem 617
	setflag 8714
	closemessage
	release
	end

Gate_Route43_Rocket_EventScript_PolicemanAfter::
	msgbox Gate_Route43_Text_OfficerAvoidGrass, MSGBOX_DEFAULT
	closemessage
	release
	end

Gate_Route43_Rocket_EventScript_Rockets::
	msgbox Gate_Route43_Rocket_Text_MakingABundle, MSGBOX_NPC
	end

Gate_Route43_Rocket_Text_TollFee:
	.string "Hol{SE_M_WATERFALL}i{SE_M_SPIT_UP}there{SE_M_SUPERSONIC}kiddo!\p"
	.string "Th{SE_M_REVERSAL}tol{SE_M_BATON_PASS}i{SE_M_GRASSWHISTLE}¥50{SE_M_BITE}t{SE_M_ATTRACT2}go\n"
	.string "through.$"

Gate_Route43_Rocket_Text_ThankYou:
	.string "Than{SE_M_ENCORE2}yo{SE_M_DIVE}ver{SE_M_YAWN}much!$"

Gate_Route43_Rocket_Text_AllYouGot:
	.string "The{SE_M_ATTRACT}pa{SE_M_YAWN}wha{SE_M_SPIT_UP}yo{SE_M_DIVE}have{SE_M_SUPERSONIC}please.$"

Gate_Route43_Rocket_Text_KickOut:
	.string "Wow!\p"
	.string "You'r{SE_M_REVERSAL}totall{SE_M_YAWN}broke!\p"
	.string "{SE_M_HEAL_BELL}almos{SE_M_SPIT_UP}fee{SE_M_BATON_PASS}sorr{SE_M_YAWN}fo{SE_M_SAND_TOMB}you.\p"
	.string "Okay{SE_M_SUPERSONIC}yo{SE_M_DIVE}ca{SE_M_ATTRACT}pass...\p"
	.string "Jus{SE_M_SPIT_UP}don'{SE_M_SPIT_UP}tel{SE_M_BATON_PASS}th{SE_M_REVERSAL}othe{SE_M_SAND_TOMB}guard,\n"
	.string "okay?$"

Gate_Route43_Rocket_Text_MakingABundle:
	.string "He-he-he{SE_M_PERISH_SONG}We'r{SE_M_REVERSAL}makin{SE_M_SANDSTORM}{SE_M_CHARGE}bundle.\p"
	.string "Everyon{SE_M_REVERSAL}want{SE_M_GRASSWHISTLE}t{SE_M_ATTRACT2}se{SE_M_REVERSAL}what'{SE_M_GRASSWHISTLE}going\n"
	.string "o{SE_M_ATTRACT}u{SE_M_MORNING_SUN}a{SE_M_SPIT_UP}LAK{SE_M_SWORDS_DANCE}O{SE_M_LEER}RAGE.$"

Route43Gate_Text_OfficerFoundTM:
	.string "{SE_M_HEAL_BELL}go{SE_M_SPIT_UP}chase{SE_M_WATERFALL}fro{SE_M_MILK_DRINK}m{SE_M_YAWN}pos{SE_M_SPIT_UP}b{SE_M_YAWN}these\n"
	.string "thug{SE_M_GRASSWHISTLE}i{SE_M_ATTRACT}black.\p"
	.string "The{SE_M_YAWN}lef{SE_M_SPIT_UP}thi{SE_M_GRASSWHISTLE}behind.\p"
	.string "I{SE_M_SPIT_UP}make{SE_M_GRASSWHISTLE}m{SE_M_REVERSAL}uncomfortable{SE_M_PERISH_SONG}Could\n"
	.string "yo{SE_M_DIVE}tak{SE_M_REVERSAL}i{SE_M_SPIT_UP}away?$"

Gate_Route43_Text_ReceivedTM30:
	.string "{PLAYER} receive{SE_M_WATERFALL}TM36.$"

Gate_Route43_Text_OfficerAvoidGrass:
	.string "Us{SE_M_REVERSAL}thi{SE_M_GRASSWHISTLE}gat{SE_M_REVERSAL}t{SE_M_ATTRACT2}avoi{SE_M_WATERFALL}walkin{SE_M_SANDSTORM}in\n"
	.string "th{SE_M_REVERSAL}grass.$"

