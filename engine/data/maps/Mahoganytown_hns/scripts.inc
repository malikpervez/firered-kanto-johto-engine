@ Johto (data/maps/Mahoganytown_hns/scripts.inc), as built into the FireRed game.

Mahoganytown_hns_MapScripts::
	map_script 1, Mahoganytown_OnLoad
	map_script 2, Mahoganytown_OnFrame
	.byte 0

Mahoganytown_OnLoad::
	call_if_ge 20578, 13, MahoganyTown_EventScript_FixTree
	end

MahoganyTown_EventScript_FixTree::
	setmetatile 18, 8, 0x378, FALSE
	setmetatile 19, 8, 0x379, FALSE
	end

Mahoganytown_OnFrame::
	map_script_2 20643, 1, Mahoganytown_EventScript_RocketTrigger
	.2byte 0

Mahoganytown_EventScript_RocketTrigger::
	lock
	setspeaker Route30_Text_ElmName
	pokenavcall ElmPhoneRadioTowerRocketTakeoverText
	waitmessage
	setvar 20569, 6
	clearflag 8300
	setflag 8301
	setflag 8296
	clearflag 8306
	setvar 20578, 16
	setvar 20643, 2
	delay 10
	release
	end

MahoganyTown_EventScript_TownTrigger::
	clearflag 8243
	clearflag 8333
	clearflag 8332
	clearflag 8714
	clearflag 8723
	clearflag 8671
	clearflag 8338
	clearflag 8337
	clearflag 8341
	clearflag 8741
	clearflag 8742
	clearflag 8344
	clearflag 8342
	clearflag 8240
	clearflag 8241
	clearflag 8242
	clearflag 8711
	clearflag 8355

	setflag 10488
	setflag 8348
	setflag 8334
	setflag 8331
	setflag 8335
	setflag 8347
	setflag 8346
	setflag 8340
	setflag 8339
	setflag 8345
	setflag 8336

	setvar 20586, 0
	setvar 20587, 0
	setvar 20588, 0
	setvar 20589, 0
	setvar 20590, 0
	setvar 20591, 0
	setvar 20563, 0
	setvar 20575, 0
	setvar 20570, 0
	setvar 20593, 0

	setvar 20578, 1


	setvar 20550, 1
	setflag 8353
	setflag 8351
	setflag 8352
	setflag 8354
	clearflag 8736
	clearflag 8707
	setvar 20551, 0
	setvar 20560, 0
	end

MahoganyTown_EventScript_MerchantTrigger::
	lock
	turnobject 3, DIR_SOUTH
	playse 21
	applymovement 3, J_Common_Movement_ExclamationMark
	delay 60
	turnobject 255, DIR_NORTH
	getplayerxy 16384, 16385
	call_if_eq 16385, 14, MahoganyTown_EventScript_WalkUp2
	call_if_eq 16385, 13, MahoganyTown_EventScript_WalkUp1
	showmoneybox 0, 0
	msgbox MahoganyTown_Text_RageCandyBarMerchantTryOne, MSGBOX_YESNO
	goto_if_eq 32781, FALSE, MahoganyTown_EventScript_MerchantRefused
	checkmoney 300, 0
	goto_if_eq 32781, FALSE, MahoganyTown_EventScript_MerchantBroke
	removemoney 300
	updatemoneybox 0
	playse 95
	msgbox MahoganyTown_Text_RageCandyBarMerchantSavorIt, MSGBOX_DEFAULT
	giveitem ITEM_RAGE_CANDY_BAR
	goto_if_eq 32781, FALSE, J_Common_EventScript_BagIsFull
	hidemoneybox
	closemessage
	getplayerxy 16384, 16385
	call_if_eq 16384, 30, MahoganyTown_EventScript_PushPlayer
	release
	end

MahoganyTown_EventScript_WalkUp1::
	applymovement 255, MahoganyTown_Movement_PlayerMerchant1
	waitmovement 0
	return

MahoganyTown_EventScript_WalkUp2::
	applymovement 255, MahoganyTown_Movement_PlayerMerchant2
	waitmovement 0
	return

MahoganyTown_EventScript_Merchant::
	lock
	faceplayer
	goto_if_eq 20578, 17, MahoganyTown_EventScript_MerchantAfter
	showmoneybox 0, 0
	msgbox MahoganyTown_Text_RageCandyBarMerchantTryOne, MSGBOX_YESNO
	goto_if_eq 32781, FALSE, MahoganyTown_EventScript_MerchantRefused
	checkmoney 300, 0
	goto_if_eq 32781, FALSE, MahoganyTown_EventScript_MerchantBroke
	removemoney 300
	updatemoneybox 0
	msgbox MahoganyTown_Text_RageCandyBarMerchantSavorIt, MSGBOX_DEFAULT
	giveitem ITEM_RAGE_CANDY_BAR
	hidemoneybox
	closemessage
	release
	end

MahoganyTown_EventScript_MerchantRefused::
	msgbox MahoganyTown_Text_RageCandyBarMerchantRefused, MSGBOX_DEFAULT
	closemessage
	hidemoneybox
	closemessage
	getplayerxy 16384, 16385
	call_if_eq 16384, 30, MahoganyTown_EventScript_PushPlayer
	release
	end

MahoganyTown_EventScript_MerchantBroke::
	msgbox MahoganyTown_Text_RageCandyBarMerchantNotEnoughMoney, MSGBOX_DEFAULT
	closemessage
	hidemoneybox
	closemessage
	getplayerxy 16384, 16385
	call_if_eq 16384, 30, MahoganyTown_EventScript_PushPlayer
	release
	end

MahoganyTown_EventScript_NotEnoughSpace:
	msgbox MahoganyTown_Text_RageCandyBarMerchantRefused, MSGBOX_DEFAULT
	closemessage
	hidemoneybox
	closemessage
	getplayerxy 16384, 16385
	call_if_eq 16384, 30, MahoganyTown_EventScript_PushPlayer
	release
	return

MahoganyTown_EventScript_MerchantAfter::
	msgbox MahoganyTown_Text_RageCandyBarMerchantSoldOut, MSGBOX_DEFAULT
	closemessage
	release
	end

MahoganyTown_EventScript_PushPlayer::
	applymovement 255, J_Common_Movement_WalkLeft1
	waitmovement 0
	return

MahoganyTown_EventScript_Gramps::
	lock
	faceplayer
	goto_if_eq 20578, 6, MahoganyTown_EventScript_GrampsAfter
	msgbox MahoganyTown_Text_Gramps, MSGBOX_DEFAULT
	closemessage
	release
	end

MahoganyTown_EventScript_GrampsAfter::
	msgbox MahoganyTown_Text_GrampsClearedRocketHideout, MSGBOX_DEFAULT
	closemessage
	release
	end

MahoganyTown_EventScript_Fisher::
	lock
	faceplayer
	msgbox MahoganyTown_Text_Fisher, MSGBOX_DEFAULT
	closemessage
	release
	end

MahoganyTown_EventScript_Lass::
	lock
	faceplayer
	msgbox MahoganyTown_Text_Lass, MSGBOX_DEFAULT
	closemessage
	release
	end

MahoganyTown_EventScript_Sign::
	lock
	msgbox MahoganyTown_Text_Sign, MSGBOX_SIGN
	closemessage
	release
	end

MahoganyTown_EventScript_CandybarSign::
	lock
	msgbox MahoganyTown_Text_RagecandybarSign, MSGBOX_SIGN
	closemessage
	release
	end

MahoganyTown_EventScript_GymSign::
	lock
	msgbox MahoganyTown_Text_GymSign, MSGBOX_SIGN
	closemessage
	release
	end

MahoganyTown_Movement_PlayerMerchant1:
	walk_up
	step_end

MahoganyTown_Movement_PlayerMerchant2:
	walk_up
	walk_up
	step_end

MahoganyTown_Text_RageCandyBarMerchantTryOne:
	.string "Hiya{SE_M_SUPERSONIC}kid!\p"
	.string "{SE_M_HEAL_BELL}se{SE_M_REVERSAL}you'r{SE_M_REVERSAL}ne{SE_M_TWISTER}i{SE_M_ATTRACT}MAHOGAN{SE_M_MOONLIGHT}TOWN.\p"
	.string "Sinc{SE_M_REVERSAL}you'r{SE_M_REVERSAL}new{SE_M_SUPERSONIC}yo{SE_M_DIVE}shoul{SE_M_WATERFALL}tr{SE_M_YAWN}a\n"
	.string "yumm{SE_M_YAWN}RAGECANDYBAR!\p"
	.string "Righ{SE_M_SPIT_UP}now{SE_M_SUPERSONIC}i{SE_M_SPIT_UP}ca{SE_M_ATTRACT}b{SE_M_REVERSAL}your{SE_M_GRASSWHISTLE}fo{SE_M_SAND_TOMB}just\n"
	.string "¥300{SE_M_DRAGON_RAGE}Wan{SE_M_SPIT_UP}one?$"

MahoganyTown_Text_RageCandyBarMerchantSavorIt:
	.string "Good{SE_M_DRAGON_RAGE}Savo{SE_M_SAND_TOMB}it!$"

MahoganyTown_Text_RageCandyBarMerchantNotEnoughMoney:
	.string "Yo{SE_M_DIVE}don'{SE_M_SPIT_UP}hav{SE_M_REVERSAL}enoug{SE_M_TRI_ATTACK}money.$"

MahoganyTown_Text_RageCandyBarMerchantRefused:
	.string "Oh{SE_M_SUPERSONIC}fin{SE_M_REVERSAL}then…$"

MahoganyTown_Text_RageCandyBarMerchantSoldOut:
	.string "RAGECANDYBAR'{SE_M_GRASSWHISTLE}sol{SE_M_WATERFALL}out.\p"
	.string "I'{SE_M_MILK_DRINK}packin{SE_M_SANDSTORM}up{SE_M_PERISH_SONG}Don'{SE_M_SPIT_UP}bothe{SE_M_SAND_TOMB}me,\n"
	.string "kiddo.$"

MahoganyTown_Text_Gramps:
	.string "Ar{SE_M_REVERSAL}yo{SE_M_DIVE}of{SE_M_ACID_ARMOR}t{SE_M_ATTRACT2}se{SE_M_REVERSAL}th{SE_M_REVERSAL}GYARADOS\n"
	.string "rampag{SE_M_REVERSAL}a{SE_M_SPIT_UP}th{SE_M_REVERSAL}LAKE?$"

MahoganyTown_Text_GrampsClearedRocketHideout:
	.string "MAGIKAR{SE_M_PETAL_DANCE}hav{SE_M_REVERSAL}returne{SE_M_WATERFALL}t{SE_M_ATTRACT2}LAKE\n"
	.string "O{SE_M_LEER}RAGE.\p"
	.string "Tha{SE_M_SPIT_UP}shoul{SE_M_WATERFALL}b{SE_M_REVERSAL}goo{SE_M_WATERFALL}new{SE_M_GRASSWHISTLE}fo{SE_M_SAND_TOMB}the\n"
	.string "angler{SE_M_GRASSWHISTLE}there.$"

MahoganyTown_Text_Fisher:
	.string "Sinc{SE_M_REVERSAL}yo{SE_M_DIVE}cam{SE_M_REVERSAL}thi{SE_M_GRASSWHISTLE}far{SE_M_SUPERSONIC}tak{SE_M_REVERSAL}the\n"
	.string "tim{SE_M_REVERSAL}t{SE_M_ATTRACT2}d{SE_M_ATTRACT2}som{SE_M_REVERSAL}sightseeing.\p"
	.string "Yo{SE_M_DIVE}shoul{SE_M_WATERFALL}hea{SE_M_WATERFALL}nort{SE_M_TRI_ATTACK}an{SE_M_WATERFALL}check\n"
	.string "ou{SE_M_SPIT_UP}LAK{SE_M_SWORDS_DANCE}O{SE_M_LEER}RAG{SE_M_SWORDS_DANCE}righ{SE_M_SPIT_UP}now.$"

MahoganyTown_Text_Lass:
	.string "Visi{SE_M_SPIT_UP}Grandma'{SE_M_GRASSWHISTLE}shop{SE_M_PERISH_SONG}Sh{SE_M_REVERSAL}sells\n"
	.string "stuf{SE_M_ACID_ARMOR}tha{SE_M_SPIT_UP}nobod{SE_M_YAWN}els{SE_M_REVERSAL}has.$"

MahoganyTown_Text_Sign:
	.string "MAHOGAN{SE_M_MOONLIGHT}TOWN\p"
	.string "Welcom{SE_M_REVERSAL}t{SE_M_ATTRACT2}th{SE_M_REVERSAL}Hom{SE_M_REVERSAL}o{SE_M_ACID_ARMOR}th{SE_M_REVERSAL}Ninja$"

MahoganyTown_Text_RagecandybarSign:
	.string "Whil{SE_M_REVERSAL}visitin{SE_M_SANDSTORM}MAHOGAN{SE_M_MOONLIGHT}TOWN{SE_M_SUPERSONIC}try\n"
	.string "{SE_M_CHARGE}RAGECANDYBAR!$"

MahoganyTown_Text_GymSign:
	.string "MAHOGAN{SE_M_MOONLIGHT}TOW{SE_M_PSYBEAM2}POKéMO{SE_M_PSYBEAM2}GYM\p"
	.string "LEADER{SE_M_HEAT_WAVE}PRYCE\p"
	.string "Th{SE_M_REVERSAL}Teache{SE_M_SAND_TOMB}o{SE_M_ACID_ARMOR}Winter'{SE_M_GRASSWHISTLE}Harshness$"

ElmPhoneRadioTowerRocketTakeoverText:
	.string "PROF.ELM{SE_M_HEAT_WAVE}{PLAYER}{SE_M_SUPERSONIC}ho{SE_M_TWISTER}are\n"
	.string "thing{SE_M_GRASSWHISTLE}going?\p"
	.string "{SE_M_HEAL_BELL}calle{SE_M_WATERFALL}becaus{SE_M_REVERSAL}somethin{SE_M_SANDSTORM}weird\n"
	.string "i{SE_M_GRASSWHISTLE}happenin{SE_M_SANDSTORM}wit{SE_M_TRI_ATTACK}th{SE_M_REVERSAL}radio\l"
	.string "broadcasts.\p"
	.string "The{SE_M_YAWN}wer{SE_M_REVERSAL}talkin{SE_M_SANDSTORM}abou{SE_M_SPIT_UP}TEAM\n"
	.string "ROCKET.\p"
	.string "{PLAYER}{SE_M_SUPERSONIC}d{SE_M_ATTRACT2}yo{SE_M_DIVE}kno{SE_M_TWISTER}anything\n"
	.string "abou{SE_M_SPIT_UP}it?\p"
	.string "Mayb{SE_M_REVERSAL}TEA{SE_M_GIGA_DRAIN}ROCKE{SE_M_SWIFT}ha{SE_M_GRASSWHISTLE}returned.\n"
	.string "No{SE_M_SUPERSONIC}tha{SE_M_SPIT_UP}jus{SE_M_SPIT_UP}can'{SE_M_SPIT_UP}b{SE_M_REVERSAL}true.\p"
	.string "Sorr{SE_M_YAWN}t{SE_M_ATTRACT2}bu{SE_M_SANDSTORM}you.\n"
	.string "Tak{SE_M_REVERSAL}care!$"

