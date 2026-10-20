@ Johto (data/maps/Route30_MrPokemonsHouse_hns/scripts.inc), as built into the FireRed game.

Route30_MrPokemonsHouse_hns_MapScripts::
	map_script 2, MrPokemonHouse_OnFrame
	.byte 0

MrPokemonHouse_OnFrame::
	map_script_2 20554, 1, MrPokemonHouse_EventScript_GiveEgg
	.2byte 0

MrPokemonHouse_EventScript_GiveEgg::
	lock
	playse 21
	applymovement 2, J_Common_Movement_ExclamationMark
	delay 55
	waitmovement 2
	turnobject 2, DIR_SOUTH
	msgbox MrPokemonHouse_Text_Intro1, MSGBOX_DEFAULT
	closemessage
	applymovement 255, MrPokemonHouse_Movement_MeetMrPokemon
	waitmovement 0
	msgbox MrPokemonHouse_Text_Intro2, MSGBOX_DEFAULT

	giveitem ITEM_MYSTERY_EGG
	goto_if_eq 32781, FALSE, J_Common_EventScript_ShowBagIsFull

	msgbox MrPokemonHouse_Text_Intro3, MSGBOX_DEFAULT
	msgbox MrPokemonHouse_Text_Intro4, MSGBOX_DEFAULT
	turnobject 3, DIR_WEST
	msgbox MrPokemonHouse_Text_Intro5, MSGBOX_DEFAULT
	closemessage
	playbgm ((558 + 1) + 0x26), FALSE
	applymovement 3, MrPokemonHouse_Movement_OakToPlayer
	waitmovement 0
	turnobject 255, DIR_EAST
	msgbox MrPokemonHouse_Text_OakIntro, MSGBOX_DEFAULT




	msgbox MrPokemonHouse_Text_OakParting, MSGBOX_DEFAULT
	closemessage
	applymovement 3, MrPokemonHouse_Movement_OakLeave
	waitmovement 0
	playse 9
	removeobject 3
	setflag 8662
	turnobject 255 DIR_NORTH
	fadedefaultbgm
	msgbox MrPokemonHouse_Text_Heal, MSGBOX_DEFAULT
	call J_Common_EventScript_OutOfCenterPartyHeal
	msgbox MrPokemonHouse_Text_DependingOnYou, MSGBOX_DEFAULT
	closemessage
	applymovement 2, MrPokemonHouse_Movement_MrPokemon_Leave
	waitmovement 0
	removeobject 2
	clearflag 8272
	addobject 1

	setvar 20580, 4
	setflag 8266
	clearflag 8268
	setvar 20554, 2
	setrespawn 129
	clearflag 8273
	setflag 8275
	clearflag 8274
	release
	end

MrPokemonHouse_EventScript_MrPokemon::
	lock
	faceplayer
	checkitem ITEM_RED_SCALE
	goto_if_eq 32781, TRUE, MrPokemonHouse_EventScript_MrPokemon_RedScale
	msgbox MrPokemonHouse_Text_AlwaysNewDiscoveries, MSGBOX_DEFAULT
	closemessage
	release
	end

MrPokemonHouse_EventScript_MrPokemon_RedScale::
	msgbox MrPokemonHouse_Text_GimmeTheScale, MSGBOX_YESNO
	goto_if_eq 32781, TRUE, MrPokemonHouse_EventScript_MrPokemon_RedScale_Accepted
	msgbox MrPokemonHouse_Text_Disappointed, MSGBOX_DEFAULT
	closemessage
	release
	end

MrPokemonHouse_EventScript_MrPokemon_RedScale_Accepted::
	removeitem ITEM_RED_SCALE
	giveitem ITEM_EXP_SHARE_SMALL
	goto_if_eq 32781, FALSE, J_Common_EventScript_ShowBagIsFull
	release
	end

MrPokemonHouse_EventScript_Computer::
	lock
	msgbox MrPokemonHouse_Text_BrokenComputer, MSGBOX_SIGN
	release
	end

MrPokemonHouse_EventScript_Magazine::
	lock
	msgbox MrPokemonHouse_Text_ForeignMagazines, MSGBOX_SIGN
	release
	end

MrPokemonHouse_EventScript_Coins::
	lock
	msgbox MrPokemonHouse_Text_StrangeCoins, MSGBOX_SIGN
	release
	end

MrPokemonHouse_Movement_MeetMrPokemon:
	walk_up
	walk_up
	walk_right
	walk_right
	face_up
	step_end

MrPokemonHouse_Movement_OakToPlayer:
	walk_down
	face_left
	step_end

MrPokemonHouse_Movement_OakLeave:
	walk_down
	walk_left
	walk_left
	walk_left
	walk_down
	walk_in_place_down
	step_end

MrPokemonHouse_Movement_MrPokemon_Leave:
	walk_up
	walk_left
	walk_left
	step_end

MrPokemonHouse_Text_Intro1:
	.string "Welcome{SE_M_SUPERSONIC}{PLAYER}!\p"
	.string "PROF.EL{SE_M_GIGA_DRAIN}tol{SE_M_WATERFALL}m{SE_M_REVERSAL}KANTO's\n"
	.string "CHAMPIO{SE_M_PSYBEAM2}wa{SE_M_GRASSWHISTLE}coming.\p"
	.string "H{SE_M_REVERSAL}als{SE_M_ATTRACT2}sai{SE_M_WATERFALL}yo{SE_M_DIVE}wer{SE_M_REVERSAL}helping\n"
	.string "wit{SE_M_TRI_ATTACK}hi{SE_M_GRASSWHISTLE}POKéMO{SE_M_PSYBEAM2}research.$"

MrPokemonHouse_Text_Intro2:
	.string "Thi{SE_M_GRASSWHISTLE}i{SE_M_GRASSWHISTLE}wha{SE_M_SPIT_UP}{SE_M_HEAL_BELL}wan{SE_M_SPIT_UP}PROF.ELM\n"
	.string "t{SE_M_ATTRACT2}examine.$"

MrPokemonHouse_Text_GotEgg:
	.string "{PLAYER} receive{SE_M_WATERFALL}MYSTER{SE_M_MOONLIGHT}EGG.$"

MrPokemonHouse_Text_Intro3:
	.string "{SE_M_HEAL_BELL}kno{SE_M_TWISTER}{SE_M_CHARGE}coupl{SE_M_REVERSAL}wh{SE_M_ATTRACT2}ru{SE_M_ATTRACT}a\n"
	.string "POKéMO{SE_M_PSYBEAM2}DAY-CAR{SE_M_SWORDS_DANCE}service.\p"
	.string "The{SE_M_YAWN}gav{SE_M_REVERSAL}m{SE_M_REVERSAL}tha{SE_M_SPIT_UP}EGG.\p"
	.string "{SE_M_HEAL_BELL}wa{SE_M_GRASSWHISTLE}intrigued{SE_M_SUPERSONIC}s{SE_M_ATTRACT2}{SE_M_HEAL_BELL}sent\n"
	.string "mai{SE_M_BATON_PASS}t{SE_M_ATTRACT2}PROF.ELM.\p"
	.string "Fo{SE_M_SAND_TOMB}POKéMO{SE_M_PSYBEAM2}evolution,\n"
	.string "PROF.EL{SE_M_GIGA_DRAIN}i{SE_M_GRASSWHISTLE}th{SE_M_REVERSAL}authority.$"

MrPokemonHouse_Text_Intro4:
	.string "Eve{SE_M_ATTRACT}PROF.OA{SE_M_SNORE}her{SE_M_REVERSAL}recognizes\n"
	.string "that.$"

MrPokemonHouse_Text_Intro5:
	.string "I{SE_M_ACID_ARMOR}m{SE_M_YAWN}assumptio{SE_M_ATTRACT}i{SE_M_GRASSWHISTLE}correct,\n"
	.string "PROF.EL{SE_M_GIGA_DRAIN}wil{SE_M_BATON_PASS}kno{SE_M_TWISTER}it.$"

MrPokemonHouse_Text_Heal:
	.string "Yo{SE_M_DIVE}ar{SE_M_REVERSAL}returnin{SE_M_SANDSTORM}t{SE_M_ATTRACT2}PROF.ELM?\p"
	.string "Here{SE_M_PERISH_SONG}You{SE_M_SAND_TOMB}POKéMO{SE_M_PSYBEAM2}shoul{SE_M_WATERFALL}have\n"
	.string "som{SE_M_REVERSAL}rest.$"

MrPokemonHouse_Text_DependingOnYou:
	.string "I'{SE_M_MILK_DRINK}dependin{SE_M_SANDSTORM}o{SE_M_ATTRACT}you!$"

MrPokemonHouse_Text_AlwaysNewDiscoveries:
	.string "Lif{SE_M_REVERSAL}i{SE_M_GRASSWHISTLE}delightful!\n"
	.string "Always{SE_M_SUPERSONIC}ne{SE_M_TWISTER}discoverie{SE_M_GRASSWHISTLE}t{SE_M_ATTRACT2}b{SE_M_REVERSAL}made.$"

MrPokemonHouse_Text_OakIntro::
	.string "OAK{SE_M_HEAT_WAVE}{PLAYER}{SE_M_DRAGON_RAGE}Goo{SE_M_WATERFALL}t{SE_M_ATTRACT2}se{SE_M_REVERSAL}you.\n"
	.string "Ho{SE_M_TWISTER}wa{SE_M_GRASSWHISTLE}th{SE_M_REVERSAL}tri{SE_M_MORNING_SUN}fro{SE_M_MILK_DRINK}KANTO?\p"
	.string "{SE_M_HEAL_BELL}wa{SE_M_GRASSWHISTLE}visitin{SE_M_SANDSTORM}m{SE_M_YAWN}ol{SE_M_WATERFALL}friend\n"
	.string "MR.POKéMO{SE_M_PSYBEAM2}whe{SE_M_ATTRACT}{SE_M_HEAL_BELL}hear{SE_M_WATERFALL}tha{SE_M_SPIT_UP}you\l"
	.string "wer{SE_M_REVERSAL}helpin{SE_M_SANDSTORM}PROF.ELM.\p"
	.string "You{SE_M_SAND_TOMB}experienc{SE_M_REVERSAL}an{SE_M_WATERFALL}car{SE_M_REVERSAL}for\n"
	.string "POKéMO{SE_M_PSYBEAM2}wil{SE_M_BATON_PASS}serv{SE_M_REVERSAL}hi{SE_M_MILK_DRINK}well.\p"
	.string "Kee{SE_M_MORNING_SUN}recordin{SE_M_SANDSTORM}th{SE_M_REVERSAL}discoveries\n"
	.string "yo{SE_M_DIVE}mak{SE_M_REVERSAL}i{SE_M_ATTRACT}you{SE_M_SAND_TOMB}POKéDEX!$"

MrPokemonHouse_Text_OakParting:
	.string "G{SE_M_ATTRACT2}mee{SE_M_SPIT_UP}man{SE_M_YAWN}kind{SE_M_GRASSWHISTLE}o{SE_M_ACID_ARMOR}POKéMO{SE_M_PSYBEAM2}and\n"
	.string "complet{SE_M_REVERSAL}tha{SE_M_SPIT_UP}POKéDEX!\p"
	.string "Bu{SE_M_SPIT_UP}I'v{SE_M_REVERSAL}staye{SE_M_WATERFALL}to{SE_M_ATTRACT2}long.\p"
	.string "{SE_M_HEAL_BELL}hav{SE_M_REVERSAL}t{SE_M_ATTRACT2}ge{SE_M_SPIT_UP}t{SE_M_ATTRACT2}GOLDENROD\n"
	.string "fo{SE_M_SAND_TOMB}m{SE_M_YAWN}usua{SE_M_BATON_PASS}radi{SE_M_ATTRACT2}show.\p"
	.string "{PLAYER}{SE_M_SUPERSONIC}I'{SE_M_MILK_DRINK}countin{SE_M_SANDSTORM}o{SE_M_ATTRACT}you!$"

MrPokemonHouse_Text_GimmeTheScale:
	.string "Hm{SE_M_SING}Tha{SE_M_SPIT_UP}SCALE{SE_M_DRAGON_RAGE}What'{SE_M_GRASSWHISTLE}that?\n"
	.string "{SE_M_BONEMERANG}re{SE_M_WATERFALL}GYARADOS?\p"
	.string "That'{SE_M_GRASSWHISTLE}rare{SE_M_DRAGON_RAGE}I{SE_M_SUPERSONIC}{SE_M_HEAL_BELL}wan{SE_M_SPIT_UP}it…\p"
	.string "{PLAYER}{SE_M_SUPERSONIC}woul{SE_M_WATERFALL}yo{SE_M_DIVE}car{SE_M_REVERSAL}to\n"
	.string "trad{SE_M_REVERSAL}it?\p"
	.string "{SE_M_HEAL_BELL}ca{SE_M_ATTRACT}offe{SE_M_SAND_TOMB}thi{SE_M_GRASSWHISTLE}EXP.SHARE\n"
	.string "tha{SE_M_SPIT_UP}{SE_M_HEAL_BELL}go{SE_M_SPIT_UP}fro{SE_M_MILK_DRINK}PROF.OAK.$"

MrPokemonHouse_Text_Disappointed:
	.string "That'{SE_M_GRASSWHISTLE}disappointing.\n"
	.string "Tha{SE_M_SPIT_UP}happen{SE_M_GRASSWHISTLE}t{SE_M_ATTRACT2}b{SE_M_REVERSAL}ver{SE_M_YAWN}rare.$"

MrPokemonHouse_Text_ExpShare:
	.string "{SE_M_HEAL_BELL}als{SE_M_ATTRACT2}hav{SE_M_REVERSAL}{SE_M_CHARGE}specia{SE_M_BATON_PASS}item\n"
	.string "fo{SE_M_SAND_TOMB}you.$"

MrPokemonHouse_Text_ForeignMagazines:
	.string "It'{SE_M_GRASSWHISTLE}packe{SE_M_WATERFALL}wit{SE_M_TRI_ATTACK}foreign\n"
	.string "magazines.\p"
	.string "Can'{SE_M_SPIT_UP}eve{SE_M_ATTRACT}rea{SE_M_WATERFALL}thei{SE_M_SAND_TOMB}titles…$"

MrPokemonHouse_Text_BrokenComputer:
	.string "It'{SE_M_GRASSWHISTLE}{SE_M_CHARGE}bi{SE_M_SANDSTORM}computer.\n"
	.string "Hmm{SE_M_PERISH_SONG}It'{SE_M_GRASSWHISTLE}broken.$"

MrPokemonHouse_Text_StrangeCoins:
	.string "{SE_M_BONEMERANG}whol{SE_M_REVERSAL}pil{SE_M_REVERSAL}o{SE_M_ACID_ARMOR}strang{SE_M_REVERSAL}coins!\p"
	.string "Mayb{SE_M_REVERSAL}they'r{SE_M_REVERSAL}fro{SE_M_MILK_DRINK}another\n"
	.string "country…$"

MrPokemonHouse_Text_GotExpShare:
	.string "{PLAYER} receive{SE_M_WATERFALL}EXP{SE_M_PERISH_SONG}SHARE!$"

