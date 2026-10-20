@ Johto (data/maps/SafariZoneGate_SafariZoneEntrance_hns/scripts.inc), as built into the FireRed game.

SafariZoneGate_SafariZoneEntrance_hns_MapScripts::
	map_script 2, SafariZoneGate_SafariZoneEntrance_OnFrame
	.byte 0

SafariZoneGate_SafariZoneEntrance_OnFrame::
	map_script_2 20597, 3, SafariZoneGate_SafariZoneEntrance_MeetBaoba
	map_script_2 20628, 2, SafariZoneGate_SafariZoneEntrance_EventScript_ExitSafari
	.2byte 0

SafariZoneGate_SafariZoneEntrance_EventScript_ExitSafari::
	lock
	turnobject 255, DIR_EAST
	msgbox J_SafariZone_Text_WouldYouLikeToExit, MSGBOX_YESNO
	goto_if_eq 32781, FALSE, SafariZoneGate_SafariZoneEntrance_EventScript_ReenterSafari
	special ExitSafariMode
	setvar 20628, 1
	setflag 8792
	msgbox J_SafariZone_South_Text_ExitEarlyThankYouForPlaying
	closemessage
	applymovement 255, J_Common_Movement_WalkDown1
	waitmovement 0
	release
	end

SafariZoneGate_SafariZoneEntrance_EventScript_ReenterSafari::
	closemessage
	applymovement 255, SafariZoneGate_SafariZoneEntrance_Movement_EnterSafariZone
	waitmovement 0
	warp MAP_SAFARI_ZONE_ENTERANCE_HNS, 0
	delay 120
	end

SafariZoneGate_SafariZoneEntrance_MeetBaoba::
	lock
	playse 21
	applymovement 1, J_Common_Movement_ExclamationMark
	delay 55
	waitmovement 1
	applymovement 1, SafariZoneGate_SafariZoneEntrance_Movement_WalkToPlayer
	applymovement 255, J_Common_Movement_WalkUp1
	waitmovement 1
	msgbox SafariZoneGate_SafariZoneEntrance_Text_BaobaWelcome, MSGBOX_DEFAULT
	closemessage
	msgbox SafariZoneGate_SafariZoneEntrance_Text_BaobaPokeblocks, MSGBOX_DEFAULT
	closemessage
	giveitem ITEM_POKEBLOCK_CASE
	closemessage
	applymovement 1, SafariZoneGate_SafariZoneEntrance_Movement_ReturnToTable
	waitmovement 0
	setvar 20597, 4
	release
	end

SafariZoneGate_SafariZoneEntrance_EventScript_Baoba::
	lock
	faceplayer
	goto_if_eq 20548, 1, SafariZoneGate_SafariZoneEntrance_EventScript_BaobaBeach
	goto_if_eq 20548, 2, SafariZoneGate_SafariZoneEntrance_EventScript_BaobaBrush
	goto_if_eq 20548, 3, SafariZoneGate_SafariZoneEntrance_EventScript_BaobaMountain
	goto_if_eq 20548, 4, SafariZoneGate_SafariZoneEntrance_EventScript_BaobaCave
	goto_if_ge 20548, 5, SafariZoneGate_SafariZoneEntrance_EventScript_BaobaDone
	msgbox SafariZoneGate_SafariZoneEntrance_Text_Baoba, MSGBOX_DEFAULT
	closemessage
	release
	end

SafariZoneGate_SafariZoneEntrance_EventScript_BaobaBeach::
	msgbox SafariZoneGate_SafariZoneEntrance_Text_BaobaBeach, MSGBOX_YESNO
	goto_if_eq 32781, FALSE, SafariZoneGate_SafariZoneEntrance_EventScript_BaobaDeclined
	special ChoosePartyMon
	waitstate
	lockall
	copyvar 32778, 32772
	goto_if_eq 32772, 0xFF, SafariZoneGate_SafariZoneEntrance_EventScript_BaobaDeclined
	baobacheckmon 1
	goto_if_eq 32781, FALSE, SafarioneEntrance_EventScript_BaobaWrong
	msgbox SafariZoneGate_SafariZoneEntrance_Text_BaobaBeachDone, MSGBOX_DEFAULT
	showmoneybox 0, 0
	addmoney 200000
	delay 60
	playse 95
	updatemoneybox
	delay 60
	closemessage
	hidemoneybox
	setvar 20548, 2
	release
	end

SafariZoneGate_SafariZoneEntrance_EventScript_BaobaBrush::
	msgbox SafariZoneGate_SafariZoneEntrance_Text_BaobaBrush, MSGBOX_YESNO
	goto_if_eq 32781, FALSE, SafariZoneGate_SafariZoneEntrance_EventScript_BaobaDeclined
	special ChoosePartyMon
	waitstate
	lockall
	copyvar 32778, 32772
	goto_if_eq 32772, 0xFF, SafariZoneGate_SafariZoneEntrance_EventScript_BaobaDeclined
	baobacheckmon 2
	goto_if_eq 32781, FALSE, SafarioneEntrance_EventScript_BaobaWrong
	msgbox SafariZoneGate_SafariZoneEntrance_Text_BaobaBrushDone, MSGBOX_DEFAULT
	showmoneybox 0, 0
	addmoney 300000
	delay 60
	playse 95
	updatemoneybox
	delay 60
	closemessage
	hidemoneybox
	setvar 20548, 3
	release
	end

SafariZoneGate_SafariZoneEntrance_EventScript_BaobaMountain::
	msgbox SafariZoneGate_SafariZoneEntrance_Text_BaobaMountain, MSGBOX_YESNO
	goto_if_eq 32781, FALSE, SafariZoneGate_SafariZoneEntrance_EventScript_BaobaDeclined
	special ChoosePartyMon
	waitstate
	lockall
	copyvar 32778, 32772
	goto_if_eq 32772, 0xFF, SafariZoneGate_SafariZoneEntrance_EventScript_BaobaDeclined
	baobacheckmon 3
	goto_if_eq 32781, FALSE, SafarioneEntrance_EventScript_BaobaWrong
	msgbox SafariZoneGate_SafariZoneEntrance_Text_BaobaMountainDone, MSGBOX_DEFAULT
	showmoneybox 0, 0
	addmoney 400000
	delay 60
	playse 95
	updatemoneybox
	delay 60
	closemessage
	hidemoneybox
	setvar 20548, 4
	release
	end

SafariZoneGate_SafariZoneEntrance_EventScript_BaobaCave::
	msgbox SafariZoneGate_SafariZoneEntrance_Text_BaobaCave, MSGBOX_YESNO
	goto_if_eq 32781, FALSE, SafariZoneGate_SafariZoneEntrance_EventScript_BaobaDeclined
	special ChoosePartyMon
	waitstate
	lockall
	copyvar 32778, 32772
	goto_if_eq 32772, 0xFF, SafariZoneGate_SafariZoneEntrance_EventScript_BaobaDeclined
	baobacheckmon 4
	goto_if_eq 32781, FALSE, SafarioneEntrance_EventScript_BaobaWrong
	msgbox SafariZoneGate_SafariZoneEntrance_Text_BaobaCaveDone, MSGBOX_DEFAULT
	showmoneybox 0, 0
	addmoney 400000
	delay 20
	playse 95
	updatemoneybox
	delay 20
	closemessage
	hidemoneybox
	setvar 20548, 5
	release
	end

SafarioneEntrance_EventScript_BaobaWrong::
	msgbox SafariZoneGate_SafariZoneEntrance_Text_BaobaWrong, MSGBOX_DEFAULT
	release
	end

SafariZoneGate_SafariZoneEntrance_EventScript_BaobaDeclined:
	msgbox SafariZoneGate_SafariZoneEntrance_Text_BaobaDeclined, MSGBOX_DEFAULT
	closemessage
	release
	end

SafariZoneGate_SafariZoneEntrance_EventScript_BaobaDone::
	msgbox SafariZoneGate_SafariZoneEntrance_Text_BaobaDone, MSGBOX_DEFAULT
	closemessage
	release
	end

SafariZoneGate_SafariZoneEntrance_EventScript_Test::
	givemon 374, 5
	givemon 351, 5
	givemon 308, 5
	givemon 371, 5
	end

SafariZoneGate_SafariZoneEntrance_Text_BaobaBeachDone:
	.string "Than{SE_M_ENCORE2}you{SE_M_SUPERSONIC}{PLAYER}!\n"
	.string "Here{SE_M_SUPERSONIC}tak{SE_M_REVERSAL}thi{SE_M_GRASSWHISTLE}mone{SE_M_YAWN}t{SE_M_ATTRACT2}upgrade\l"
	.string "you{SE_M_SAND_TOMB}SAFAR{SE_M_HEAL_BELL}LEVE{SE_M_BRICK_BREAK}an{SE_M_WATERFALL}sho{SE_M_TWISTER}m{SE_M_REVERSAL}an\l"
	.string "exoti{SE_M_HYPER_BEAM}POKéMO{SE_M_PSYBEAM2}fro{SE_M_MILK_DRINK}th{SE_M_REVERSAL}BRUS{SE_M_SWAGGER2}area\l"
	.string "next!$"

SafariZoneGate_SafariZoneEntrance_Text_BaobaBrushDone:
	.string "Than{SE_M_ENCORE2}you{SE_M_SUPERSONIC}{PLAYER}!\n"
	.string "Here{SE_M_SUPERSONIC}tak{SE_M_REVERSAL}thi{SE_M_GRASSWHISTLE}mone{SE_M_YAWN}t{SE_M_ATTRACT2}upgrade\l"
	.string "you{SE_M_SAND_TOMB}SAFAR{SE_M_HEAL_BELL}LEVE{SE_M_BRICK_BREAK}an{SE_M_WATERFALL}sho{SE_M_TWISTER}m{SE_M_REVERSAL}an\l"
	.string "exoti{SE_M_HYPER_BEAM}POKéMO{SE_M_PSYBEAM2}fro{SE_M_MILK_DRINK}th{SE_M_REVERSAL}MOUNTAIN\l"
	.string "are{SE_M_CHARGE}next!$"

SafariZoneGate_SafariZoneEntrance_Text_BaobaMountainDone:
	.string "Than{SE_M_ENCORE2}you{SE_M_SUPERSONIC}{PLAYER}!\n"
	.string "Here{SE_M_SUPERSONIC}tak{SE_M_REVERSAL}thi{SE_M_GRASSWHISTLE}mone{SE_M_YAWN}t{SE_M_ATTRACT2}upgrade\l"
	.string "you{SE_M_SAND_TOMB}SAFAR{SE_M_HEAL_BELL}LEVE{SE_M_BRICK_BREAK}an{SE_M_WATERFALL}sho{SE_M_TWISTER}m{SE_M_REVERSAL}an\l"
	.string "exoti{SE_M_HYPER_BEAM}POKéMO{SE_M_PSYBEAM2}fro{SE_M_MILK_DRINK}th{SE_M_REVERSAL}CAV{SE_M_SWORDS_DANCE}area\l"
	.string "next!$"

SafariZoneGate_SafariZoneEntrance_Text_BaobaCaveDone:
	.string "Than{SE_M_ENCORE2}you{SE_M_SUPERSONIC}{PLAYER}!\n"
	.string "That'{SE_M_GRASSWHISTLE}al{SE_M_BATON_PASS}{SE_M_HEAL_BELL}nee{SE_M_WATERFALL}t{SE_M_ATTRACT2}see.\p"
	.string "No{SE_M_TWISTER}tha{SE_M_SPIT_UP}{SE_M_HEAL_BELL}kno{SE_M_TWISTER}wha{SE_M_SPIT_UP}DEVO{SE_M_PSYBEAM2}i{SE_M_GRASSWHISTLE}up\n"
	.string "to{SE_M_SUPERSONIC}I'l{SE_M_BATON_PASS}b{SE_M_REVERSAL}abl{SE_M_REVERSAL}t{SE_M_ATTRACT2}kee{SE_M_MORNING_SUN}m{SE_M_YAWN}SAFARI\l"
	.string "competitive{SE_M_PERISH_SONG}Here{SE_M_SUPERSONIC}tak{SE_M_REVERSAL}thi{SE_M_GRASSWHISTLE}a{SE_M_GRASSWHISTLE}a\l"
	.string "rewar{SE_M_WATERFALL}fo{SE_M_SAND_TOMB}you{SE_M_SAND_TOMB}troubles.$"

SafariZoneGate_SafariZoneEntrance_Text_BaobaWrong:
	.string "Tha{SE_M_SPIT_UP}can'{SE_M_SPIT_UP}b{SE_M_REVERSAL}right!$"

SafariZoneGate_SafariZoneEntrance_Text_BaobaBeach:
	.string "Ah{SE_M_SUPERSONIC}{PLAYER}!\p"
	.string "Di{SE_M_WATERFALL}yo{SE_M_DIVE}brin{SE_M_SANDSTORM}a{SE_M_ATTRACT}exoti{SE_M_HYPER_BEAM}POKéMON\n"
	.string "fro{SE_M_MILK_DRINK}th{SE_M_REVERSAL}BEAC{SE_M_SWAGGER2}are{SE_M_CHARGE}o{SE_M_ACID_ARMOR}th{SE_M_REVERSAL}FUCHSIA\l"
	.string "SAFAR{SE_M_HEAL_BELL}ZON{SE_M_SWORDS_DANCE}t{SE_M_ATTRACT2}sho{SE_M_TWISTER}me?$"

SafariZoneGate_SafariZoneEntrance_Text_BaobaBrush:
	.string "Ah{SE_M_SUPERSONIC}{PLAYER}!\p"
	.string "Di{SE_M_WATERFALL}yo{SE_M_DIVE}brin{SE_M_SANDSTORM}a{SE_M_ATTRACT}exoti{SE_M_HYPER_BEAM}POKéMON\n"
	.string "fro{SE_M_MILK_DRINK}th{SE_M_REVERSAL}BRUS{SE_M_SWAGGER2}are{SE_M_CHARGE}o{SE_M_ACID_ARMOR}th{SE_M_REVERSAL}FUCHSIA\l"
	.string "SAFAR{SE_M_HEAL_BELL}ZON{SE_M_SWORDS_DANCE}t{SE_M_ATTRACT2}sho{SE_M_TWISTER}me?$"

SafariZoneGate_SafariZoneEntrance_Text_BaobaMountain:
	.string "Ah{SE_M_SUPERSONIC}{PLAYER}!\p"
	.string "Di{SE_M_WATERFALL}yo{SE_M_DIVE}brin{SE_M_SANDSTORM}a{SE_M_ATTRACT}exoti{SE_M_HYPER_BEAM}POKéMON\n"
	.string "fro{SE_M_MILK_DRINK}th{SE_M_REVERSAL}MOUNTAI{SE_M_PSYBEAM2}are{SE_M_CHARGE}o{SE_M_ACID_ARMOR}the\l"
	.string "FUCHSI{SE_M_BONEMERANG}SAFAR{SE_M_HEAL_BELL}ZON{SE_M_SWORDS_DANCE}t{SE_M_ATTRACT2}sho{SE_M_TWISTER}me?$"

SafariZoneGate_SafariZoneEntrance_Text_BaobaCave:
	.string "Ah{SE_M_SUPERSONIC}{PLAYER}!\p"
	.string "Di{SE_M_WATERFALL}yo{SE_M_DIVE}brin{SE_M_SANDSTORM}a{SE_M_ATTRACT}exoti{SE_M_HYPER_BEAM}POKéMON\n"
	.string "fro{SE_M_MILK_DRINK}th{SE_M_REVERSAL}CAV{SE_M_SWORDS_DANCE}are{SE_M_CHARGE}o{SE_M_ACID_ARMOR}th{SE_M_REVERSAL}FUCHSIA\l"
	.string "SAFAR{SE_M_HEAL_BELL}ZON{SE_M_SWORDS_DANCE}t{SE_M_ATTRACT2}sho{SE_M_TWISTER}me?$"

SafariZoneGate_SafariZoneEntrance_Text_BaobaDeclined:
	.string "Wha{SE_M_SPIT_UP}wil{SE_M_BATON_PASS}{SE_M_HEAL_BELL}d{SE_M_ATTRACT2}now?\n"
	.string "We'l{SE_M_BATON_PASS}neve{SE_M_SAND_TOMB}kee{SE_M_MORNING_SUN}u{SE_M_MORNING_SUN}wit{SE_M_TRI_ATTACK}DEVON!$"

SafariZoneGate_SafariZoneEntrance_Text_BaobaLastMon:
	.string "{SE_M_HEAL_BELL}can'{SE_M_SPIT_UP}tak{SE_M_REVERSAL}you{SE_M_SAND_TOMB}las{SE_M_SPIT_UP}POKéMON!$"

SafariZoneGate_SafariZoneEntrance_Text_BaobaDone:
	.string "Ah{SE_M_SUPERSONIC}{PLAYER}!\p"
	.string "Thank{SE_M_GRASSWHISTLE}t{SE_M_ATTRACT2}you{SE_M_SUPERSONIC}th{SE_M_REVERSAL}SAFAR{SE_M_HEAL_BELL}ZON{SE_M_SWORDS_DANCE}is\n"
	.string "thriving!\p"
	.string "Mayb{SE_M_REVERSAL}{SE_M_HEAL_BELL}shoul{SE_M_WATERFALL}nam{SE_M_REVERSAL}yo{SE_M_DIVE}OWNE{SE_M_MINIMIZE}of\n"
	.string "th{SE_M_REVERSAL}safar{SE_M_TRI_ATTACK2}zone...\p"
	.string "No{SE_M_SUPERSONIC}tha{SE_M_SPIT_UP}woul{SE_M_WATERFALL}b{SE_M_REVERSAL}ridiculous.\n"
	.string "Ahahahaha.$"

SafariZoneGate_SafariZoneEntrance_EventScript_EntranceCounterTrigger::
	lockall
	turnobject 255, DIR_EAST
	showmoneybox 0, 0
	msgbox J_Route121_SafariZoneEntrance_Text_WouldYouLikeToPlay, MSGBOX_YESNO
	goto_if_eq 32781, YES, SafariZoneGate_SafariZoneEntrance_EventScript_TryEnterSafariZone
	msgbox J_Route121_SafariZoneEntrance_Text_PlayAnotherTime, MSGBOX_DEFAULT
	goto SafariZoneGate_SafariZoneEntrance_EventScript_MovePlayerBackFromCounter
	end

SafariZoneGate_SafariZoneEntrance_EventScript_TryEnterSafariZone::
	checkitem ITEM_POKEBLOCK_CASE
	goto_if_eq 32781, 0, SafariZoneGate_SafariZoneEntrance_EventScript_NoPokeblockCase
	call SafariZoneGate_SafariZoneEntrance_EventScript_CheckHasRoomForPokemon
	checkmoney 500
	goto_if_eq 32781, 0, SafariZoneGate_SafariZoneEntrance_EventScript_NotEnoughMoney
	msgbox J_Route121_SafariZoneEntrance_Text_ThatWillBe500Please, MSGBOX_DEFAULT
	removemoney 500
	playse 95
	updatemoneybox
	msgbox J_Route121_SafariZoneEntrance_Text_HereAreYourSafariBalls, MSGBOX_DEFAULT
	playfanfare 370
	message J_Route121_SafariZoneEntrance_Text_Received30SafariBalls
	waitfanfare
	msgbox J_Route121_SafariZoneEntrance_Text_PleaseEnjoyYourself, MSGBOX_DEFAULT
	closemessage
	hidemoneybox
	applymovement 255, SafariZoneGate_SafariZoneEntrance_Movement_EnterSafariZone
	waitmovement 0
	special EnterSafariMode
	setvar 20628, 2
	clearflag 8792
	warp MAP_SAFARI_ZONE_ENTERANCE_HNS, 0
	waitstate
	end

SafariZoneGate_SafariZoneEntrance_EventScript_CheckHasRoomForPokemon::
	getpartysize
	goto_if_ne 32781, 6, SafariZoneGate_SafariZoneEntrance_EventScript_HasRoomForPokemon
	specialvar 32781, ScriptCheckFreePokemonStorageSpace
	goto_if_eq 32781, 1, SafariZoneGate_SafariZoneEntrance_EventScript_HasRoomForPokemon
	msgbox J_Route121_SafariZoneEntrance_Text_PCIsFull, MSGBOX_DEFAULT
	goto SafariZoneGate_SafariZoneEntrance_EventScript_MovePlayerBackFromCounter
	end

SafariZoneGate_SafariZoneEntrance_EventScript_HasRoomForPokemon::
	return

SafariZoneGate_SafariZoneEntrance_EventScript_NoPokeblockCase::
	msgbox J_Route121_SafariZoneEntrance_Text_YouNeedPokeblockCase, MSGBOX_DEFAULT
	goto SafariZoneGate_SafariZoneEntrance_EventScript_MovePlayerBackFromCounter
	end

SafariZoneGate_SafariZoneEntrance_EventScript_NotEnoughMoney::
	msgbox J_Route121_SafariZoneEntrance_Text_NotEnoughMoney, MSGBOX_DEFAULT
	goto SafariZoneGate_SafariZoneEntrance_EventScript_MovePlayerBackFromCounter
	end

SafariZoneGate_SafariZoneEntrance_EventScript_MovePlayerBackFromCounter::
	closemessage
	hidemoneybox
	applymovement 255, SafariZoneGate_SafariZoneEntrance_Movement_BackAwayFromCounter
	waitmovement 0
	releaseall
	end

SafariZoneGate_SafariZoneEntrance_EventScript_Chart1::
	lock
	helpwindow HELP_POKEBLOCK_WINDOW
	release
	end

SafariZoneGate_SafariZoneEntrance_EventScript_Chart2::
	lock
	helpwindow HELP_GOLD_POKEBLOCK_WINDOW
	release
	end

SafariZoneGate_SafariZoneEntrance_EventScript_Boy::
	lock
	faceplayer
	checkitem ITEM_POKEBLOCK_CASE
	goto_if_eq 32781, FALSE, SafariZoneGate_SafariZoneEntrance_EventScript_BoyGiveExtraPokeblockCase
	msgbox SafariZoneGate_SafariZoneEntrance_Text_Boy, MSGBOX_DEFAULT
	closemessage
	release
	end

SafariZoneGate_SafariZoneEntrance_EventScript_BoyGiveExtraPokeblockCase::
	msgbox SafariZoneGate_SafariZoneEntrance_Text_BoyGiveCase, MSGBOX_DEFAULT
	giveitem ITEM_POKEBLOCK_CASE
	closemessage
	release
	end

SafariZoneGate_SafariZoneEntrance_EventScript_Engineer::
	lock
	faceplayer
	msgbox SafariZoneGate_SafariZoneEntrance_Text_Engineer, MSGBOX_DEFAULT
	closemessage
	release
	end

SafariZoneGate_SafariZoneEntrance_Movement_BackAwayFromCounter:
	walk_down
	step_end

SafariZoneGate_SafariZoneEntrance_Movement_EnterSafariZone:
	walk_up
	step_end

SafariZoneGate_SafariZoneEntrance_Movement_WalkToPlayer:
	walk_right
	walk_right
	walk_right
	walk_right
	walk_down
	step_end

SafariZoneGate_SafariZoneEntrance_Movement_ReturnToTable:
	walk_up
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

SafariZoneGate_SafariZoneEntrance_Text_BaobaWelcome:
	.string "H{SE_M_TRI_ATTACK2}{PLAYER}!\n"
	.string "I'v{SE_M_REVERSAL}bee{SE_M_ATTRACT}waitin{SE_M_SANDSTORM}fo{SE_M_SAND_TOMB}you.\n"
	.string "Wha{SE_M_SPIT_UP}d{SE_M_ATTRACT2}yo{SE_M_DIVE}think?\p"
	.string "Thi{SE_M_GRASSWHISTLE}i{SE_M_GRASSWHISTLE}{SE_M_CHARGE}bran{SE_M_WATERFALL}ne{SE_M_TWISTER}SAFAR{SE_M_HEAL_BELL}ZONE\n"
	.string "b{SE_M_YAWN}th{SE_M_REVERSAL}way...\p"
	.string "An{SE_M_WATERFALL}it'{SE_M_GRASSWHISTLE}stil{SE_M_BATON_PASS}expanding!\p"
	.string "S{SE_M_ATTRACT2}far{SE_M_SUPERSONIC}w{SE_M_REVERSAL}hav{SE_M_REVERSAL}tw{SE_M_ATTRACT2}zone{SE_M_GRASSWHISTLE}open\n"
	.string "an{SE_M_WATERFALL}{SE_M_WHIRLPOOL}mor{SE_M_REVERSAL}o{SE_M_ATTRACT}th{SE_M_REVERSAL}way!\p"
	.string "Enjo{SE_M_YAWN}th{SE_M_REVERSAL}SAFAR{SE_M_HEAL_BELL}ZONE{SE_M_DRAGON_RAGE}I'll\n"
	.string "cal{SE_M_BATON_PASS}yo{SE_M_DIVE}whe{SE_M_ATTRACT}th{SE_M_REVERSAL}othe{SE_M_SAND_TOMB}zones\l"
	.string "ar{SE_M_REVERSAL}ready!$"

SafariZoneGate_SafariZoneEntrance_Text_BaobaPokeblocks:
	.string "Oh{SE_M_DRAGON_RAGE}{SE_M_HEAL_BELL}almos{SE_M_SPIT_UP}forgot.\p"
	.string "POKéBLOCK{SE_M_SKETCH}ar{SE_M_REVERSAL}a{SE_M_ATTRACT}essential\n"
	.string "featur{SE_M_REVERSAL}o{SE_M_ACID_ARMOR}m{SE_M_YAWN}SAFAR{SE_M_HEAL_BELL}ZONE{SE_M_SUPERSONIC}so\l"
	.string "you'{SE_M_WATERFALL}bette{SE_M_SAND_TOMB}hav{SE_M_REVERSAL}on{SE_M_REVERSAL}o{SE_M_ACID_ARMOR}these!$"

SafariZoneGate_SafariZoneEntrance_Text_Baoba:
	.string "H{SE_M_TRI_ATTACK2}{PLAYER}!\p"
	.string "Ho{SE_M_TWISTER}ar{SE_M_REVERSAL}yo{SE_M_DIVE}enjoyin{SE_M_SANDSTORM}th{SE_M_REVERSAL}SAFARI\n"
	.string "ZONE?$"

SafariZoneGate_SafariZoneEntrance_Text_Boy:
	.string "D{SE_M_ATTRACT2}yo{SE_M_DIVE}kno{SE_M_TWISTER}abou{SE_M_SPIT_UP}POKéBLOCK\n"
	.string "feeders?\p"
	.string "Puttin{SE_M_SANDSTORM}{SE_M_CHARGE}POKéBLOC{SE_M_SNORE}i{SE_M_ATTRACT}th{SE_M_REVERSAL}feeder\n"
	.string "bring{SE_M_GRASSWHISTLE}ou{SE_M_SPIT_UP}POKéMO{SE_M_PSYBEAM2}wit{SE_M_TRI_ATTACK}HIDDEN\l"
	.string "ABILITIES!\p"
	.string "Th{SE_M_REVERSAL}typ{SE_M_REVERSAL}o{SE_M_ACID_ARMOR}POKéBLOC{SE_M_SNORE}als{SE_M_ATTRACT2}affects\n"
	.string "th{SE_M_REVERSAL}POKéMON'{SE_M_GRASSWHISTLE}nature.\p"
	.string "An{SE_M_WATERFALL}bes{SE_M_SPIT_UP}o{SE_M_ACID_ARMOR}all{SE_M_SUPERSONIC}th{SE_M_REVERSAL}typ{SE_M_REVERSAL}o{SE_M_ACID_ARMOR}POKéBLOCK\n"
	.string "yo{SE_M_DIVE}us{SE_M_REVERSAL}ca{SE_M_ATTRACT}attrac{SE_M_SPIT_UP}POKéMO{SE_M_PSYBEAM2}with\l"
	.string "perfec{SE_M_SPIT_UP}IVs!\p"
	.string "Thos{SE_M_REVERSAL}chart{SE_M_GRASSWHISTLE}o{SE_M_ATTRACT}th{SE_M_REVERSAL}wal{SE_M_BATON_PASS}hav{SE_M_REVERSAL}all\n"
	.string "th{SE_M_REVERSAL}details.$"

SafariZoneGate_SafariZoneEntrance_Text_BoyGiveCase:
	.string "Here{SE_M_SUPERSONIC}yo{SE_M_DIVE}see{SE_M_MILK_DRINK}lik{SE_M_REVERSAL}yo{SE_M_DIVE}nee{SE_M_WATERFALL}this.$"

SafariZoneGate_SafariZoneEntrance_Text_Engineer:
	.string "Sorr{SE_M_YAWN}Trainer{SE_M_SUPERSONIC}thi{SE_M_GRASSWHISTLE}are{SE_M_CHARGE}i{SE_M_GRASSWHISTLE}still\n"
	.string "unde{SE_M_SAND_TOMB}construction{SE_M_PERISH_SONG}Chec{SE_M_ENCORE2}back\l"
	.string "later!$"

