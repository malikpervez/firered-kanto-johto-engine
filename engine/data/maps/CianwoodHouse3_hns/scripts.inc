@ Johto (data/maps/CianwoodHouse3_hns/scripts.inc), as built into the FireRed game.

CianwoodHouse3_hns_MapScripts::
	.byte 0

CianwoodCity_EventScript_Kirk::
	lock
	faceplayer
	goto_if_eq 20654, 1, CianwoodCity_EventScript_KirkGivenShuckie
	goto_if_eq 20654, 3, CianwoodCity_EventScript_KirkReturnedShuckie
	msgbox CianwoodCity_Text_ManiacAskShuckle, MSGBOX_YESNO
	goto_if_eq 32781, FALSE, CianwoodCity_EventScript_KirkDeclined


	setvar 16385, 213
	bufferspeciesname STR_VAR_1, 213
	givenamedmon 2
	call J_Common_EventScript_GiftMonNamed

	setvar 20654, 1
	release
	end

CianwoodCity_EventScript_KirkDeclined::
	msgbox CianwoodCity_Text_ManiacIfHeComesBack, MSGBOX_DEFAULT
	closemessage
	end

CianwoodCity_EventScript_KirkGivenShuckie::
	goto_if_set 10368, CianwoodCity_EventScript_KirkReturnShuckie
	msgbox CianwoodCity_Text_ManiacHowsdoing, MSGBOX_DEFAULT
	closemessage
	end

CianwoodCity_EventScript_KirkReturnShuckie::
	msgbox CianwoodCity_Text_ManiacAskReturn, MSGBOX_YESNO
	goto_if_eq 32781, FALSE, CianwoodCity_EventScript_KirkDeclineReturnShuckie
	removenamedmon 2
	goto_if_eq 32781, 2, CianwoodCity_EventScript_KirkNotRight
	goto_if_eq 32781, 3, CianwoodCity_EventScript_KirkKeepShuckie
	playse 370
	callnative UpdateFollowingPokemon
	msgbox CianwoodCity_Text_ManiacReturnedMon, MSGBOX_DEFAULT
	waitse
	msgbox CianwoodCity_Text_ManiacThankYou, MSGBOX_DEFAULT
	setvar 20654, 3
	release
	end

CianwoodCity_EventScript_KirkDeclineReturnShuckie::
	msgbox CianwoodCity_Text_ManiacRobbed2, MSGBOX_DEFAULT
	closemessage
	release
	end

CianwoodCity_EventScript_KirkNotRight::
	msgbox CianwoodCity_Text_ManiacRobbed, MSGBOX_DEFAULT
	closemessage
	release
	end

CianwoodCity_EventScript_KirkKeepShuckie::
	msgbox CianwoodCity_Text_ManiacShuckleLikesYou, MSGBOX_DEFAULT
	closemessage
	setvar 20654, 3
	release
	end

CianwoodCity_EventScript_KirkReturnedShuckie::
	msgbox CianwoodCity_Text_ManiacHappinessSpeech, MSGBOX_DEFAULT
	closemessage
	end

CianwoodCity_Text_ManiacAskShuckle:
	.string "I{SE_M_SUPERSONIC}I'{SE_M_MILK_DRINK}i{SE_M_ATTRACT}shock!\p"
	.string "{SE_M_BONEMERANG}gu{SE_M_YAWN}abou{SE_M_SPIT_UP}you{SE_M_SAND_TOMB}ag{SE_M_REVERSAL}wit{SE_M_TRI_ATTACK}piercing\n"
	.string "eye{SE_M_GRASSWHISTLE}an{SE_M_WATERFALL}lon{SE_M_SANDSTORM}hai{SE_M_SAND_TOMB}cam{SE_M_REVERSAL}in.\p"
	.string "H{SE_M_REVERSAL}scare{SE_M_WATERFALL}m{SE_M_REVERSAL}int{SE_M_ATTRACT2}givin{SE_M_SANDSTORM}hi{SE_M_MILK_DRINK}my\n"
	.string "prize{SE_M_WATERFALL}POKéMON!\p"
	.string "{SE_M_HEAL_BELL}stil{SE_M_BATON_PASS}hav{SE_M_REVERSAL}on{SE_M_REVERSAL}left{SE_M_SUPERSONIC}bu{SE_M_SPIT_UP}wha{SE_M_SPIT_UP}if\n"
	.string "h{SE_M_REVERSAL}come{SE_M_GRASSWHISTLE}back?\p"
	.string "Yo{SE_M_DIVE}loo{SE_M_ENCORE2}strong{SE_M_PERISH_SONG}Coul{SE_M_WATERFALL}yo{SE_M_DIVE}look\n"
	.string "afte{SE_M_SAND_TOMB}m{SE_M_YAWN}POKéMO{SE_M_PSYBEAM2}fo{SE_M_SAND_TOMB}{SE_M_CHARGE}while?$"

CianwoodCity_Text_ManiacTakeCareShuckle:
	.string "Oh{SE_M_SUPERSONIC}than{SE_M_ENCORE2}you!\p"
	.string "Tak{SE_M_REVERSAL}goo{SE_M_WATERFALL}car{SE_M_REVERSAL}o{SE_M_ACID_ARMOR}it{SE_M_SUPERSONIC}please!$"

CianwoodCity_Text_ManiacGotShuckle:
	.string "{PLAYER} receive{SE_M_WATERFALL}{SE_M_CHARGE}POKéMON.$"

CianwoodCity_Text_ManiacPartyFull:
	.string "You{SE_M_SAND_TOMB}POKéMO{SE_M_PSYBEAM2}part{SE_M_YAWN}i{SE_M_GRASSWHISTLE}full.$"

CianwoodCity_Text_ManiacIfHeComesBack:
	.string "Oh{SE_M_SUPERSONIC}no{SE_M_DIZZY_PUNCH}What'l{SE_M_BATON_PASS}{SE_M_HEAL_BELL}d{SE_M_ATTRACT2}i{SE_M_ACID_ARMOR}h{SE_M_REVERSAL}comes\n"
	.string "back?$"

CianwoodCity_Text_ManiacHowsdoing:
	.string "Hi{SE_M_DRAGON_RAGE}How'{SE_M_GRASSWHISTLE}m{SE_M_YAWN}POKéMON?$"

CianwoodCity_Text_ManiacAskReturn:
	.string "Hi{SE_M_DRAGON_RAGE}How'{SE_M_GRASSWHISTLE}m{SE_M_YAWN}POKéMON?\p"
	.string "{SE_M_HEAL_BELL}thin{SE_M_ENCORE2}I'{SE_M_MILK_DRINK}saf{SE_M_REVERSAL}now{SE_M_SUPERSONIC}s{SE_M_ATTRACT2}ma{SE_M_YAWN}I\n"
	.string "hav{SE_M_REVERSAL}i{SE_M_SPIT_UP}back?$"

CianwoodCity_Text_ManiacThankYou:
	.string "Than{SE_M_ENCORE2}you!$"

CianwoodCity_Text_ManiacShuckleNotThere:
	.string "Hey{SE_M_SUPERSONIC}yo{SE_M_DIVE}don'{SE_M_SPIT_UP}hav{SE_M_REVERSAL}m{SE_M_YAWN}POKéMON\n"
	.string "wit{SE_M_TRI_ATTACK}you.$"

CianwoodCity_Text_ManiacShuckleLikesYou:
	.string "M{SE_M_YAWN}POKéMO{SE_M_PSYBEAM2}ha{SE_M_GRASSWHISTLE}com{SE_M_REVERSAL}t{SE_M_ATTRACT2}lik{SE_M_REVERSAL}you.\p"
	.string "Al{SE_M_BATON_PASS}right{SE_M_SUPERSONIC}yo{SE_M_DIVE}shoul{SE_M_WATERFALL}kee{SE_M_MORNING_SUN}it.\p"
	.string "Bu{SE_M_SPIT_UP}promis{SE_M_REVERSAL}t{SE_M_ATTRACT2}b{SE_M_REVERSAL}goo{SE_M_WATERFALL}t{SE_M_ATTRACT2}it!$"

CianwoodCity_Text_ManiacRobbed:
	.string "Huh{SE_M_SUPERSONIC}something'{SE_M_GRASSWHISTLE}no{SE_M_SPIT_UP}right.$"

CianwoodCity_Text_ManiacRobbed2:
	.string "Oh{SE_M_SUPERSONIC}no{SE_M_SUPERSONIC}no{SE_M_DIZZY_PUNCH}That'{SE_M_GRASSWHISTLE}th{SE_M_REVERSAL}sam{SE_M_REVERSAL}as\n"
	.string "bein{SE_M_SANDSTORM}robbed.$"

CianwoodCity_Text_ManiacHappinessSpeech:
	.string "Fo{SE_M_SAND_TOMB}POKéMON{SE_M_SUPERSONIC}happines{SE_M_GRASSWHISTLE}i{SE_M_GRASSWHISTLE}being\n"
	.string "wit{SE_M_TRI_ATTACK}{SE_M_CHARGE}perso{SE_M_ATTRACT}wh{SE_M_ATTRACT2}treat{SE_M_GRASSWHISTLE}the{SE_M_MILK_DRINK}well.$"

CianwoodCity_Text_ManiacLastMon:
	.string "I{SE_M_ACID_ARMOR}{SE_M_HEAL_BELL}tak{SE_M_REVERSAL}m{SE_M_YAWN}POKéMO{SE_M_PSYBEAM2}back,\n"
	.string "wha{SE_M_SPIT_UP}ar{SE_M_REVERSAL}yo{SE_M_DIVE}goin{SE_M_SANDSTORM}t{SE_M_ATTRACT2}use\n"
	.string "i{SE_M_ATTRACT}battle?$"

CianwoodCity_Text_ManiacReturnedMon:
	.string "{PLAYER} returne{SE_M_WATERFALL}SHUCKIE.$"

