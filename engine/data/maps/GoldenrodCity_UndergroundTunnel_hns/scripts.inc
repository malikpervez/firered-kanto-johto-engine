@ Johto (data/maps/GoldenrodCity_UndergroundTunnel_hns/scripts.inc), as built into the FireRed game.

GoldenrodCity_UndergroundTunnel_hns_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, GoldenrodCity_UndergroundTunnel_OnLoad
	.byte 0

GoldenrodCity_UndergroundTunnel_OnLoad::
	goto GoldenrodCity_UndergroundTunnel_MapScript_TryOpenDoor
	end

GoldenrodCity_UndergroundTunnel_EventScript_KimonoTriggerBot::
	lock
	playbgm ((558 + 1) + 0x85), FALSE
	applymovement LOCALID_GOLDENROD_UNDERGROUND_KIMONO, GoldenrodCity_UndergroundTunnel_Movement_Kimono_WalkToPlayerBot
	waitmovement 0
	msgbox GoldenrodCity_UndergroundTunnel_Text_Kimono1, MSGBOX_DEFAULT
	closemessage
	playse SE_PIN
	applymovement LOCALID_GOLDENROD_UNDERGROUND_KIMONO, J_Common_Movement_ExclamationMark
	delay 55
	waitmovement LOCALID_GOLDENROD_UNDERGROUND_KIMONO
	msgbox GoldenrodCity_UndergroundTunnel_Text_Kimono2, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_GOLDENROD_UNDERGROUND_KIMONO, J_Common_Movement_WalkUp1
	waitmovement 0
	applymovement LOCALID_GOLDENROD_UNDERGROUND_KIMONO, GoldenrodCity_UndergroundTunnel_Movement_Kimono_Leave1
	waitmovement 0
	playse SE_M_PETAL_DANCE
	applymovement LOCALID_GOLDENROD_UNDERGROUND_KIMONO, GoldenrodCity_UndergroundTunnel_Movement_Kimono_Spin
	waitmovement 0
	applymovement LOCALID_GOLDENROD_UNDERGROUND_KIMONO, GoldenrodCity_UndergroundTunnel_Movement_Kimono_Leave2
	waitmovement 0
	setflag JOHTO_FLAG_HIDE_GOLDENROD_UNDERGROUND_KIMONO
	removeobject LOCALID_GOLDENROD_UNDERGROUND_KIMONO
	fadedefaultbgm
	setvar JOHTO_VAR_GOLDENROD_CITY_STATE, 8
	releaseall
	end

GoldenrodCity_UndergroundTunnel_EventScript_KimonoTriggerTop::
	lock
	playbgm ((558 + 1) + 0x85), FALSE
	applymovement LOCALID_GOLDENROD_UNDERGROUND_KIMONO, GoldenrodCity_UndergroundTunnel_Movement_Kimono_WalkToPlayerTop
	waitmovement 0
	msgbox GoldenrodCity_UndergroundTunnel_Text_Kimono1, MSGBOX_DEFAULT
	closemessage
	playse SE_PIN
	applymovement LOCALID_GOLDENROD_UNDERGROUND_KIMONO, J_Common_Movement_ExclamationMark
	delay 55
	waitmovement LOCALID_GOLDENROD_UNDERGROUND_KIMONO
	msgbox GoldenrodCity_UndergroundTunnel_Text_Kimono2, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_GOLDENROD_UNDERGROUND_KIMONO, J_Common_Movement_WalkDown1
	waitmovement 0
	applymovement LOCALID_GOLDENROD_UNDERGROUND_KIMONO, GoldenrodCity_UndergroundTunnel_Movement_Kimono_Leave1
	waitmovement 0
	playse SE_M_PETAL_DANCE
	applymovement LOCALID_GOLDENROD_UNDERGROUND_KIMONO, GoldenrodCity_UndergroundTunnel_Movement_Kimono_Spin
	waitmovement 0
	applymovement LOCALID_GOLDENROD_UNDERGROUND_KIMONO, GoldenrodCity_UndergroundTunnel_Movement_Kimono_Leave2
	waitmovement 0
	setflag JOHTO_FLAG_HIDE_GOLDENROD_UNDERGROUND_KIMONO
	removeobject LOCALID_GOLDENROD_UNDERGROUND_KIMONO
	fadedefaultbgm
	setvar JOHTO_VAR_GOLDENROD_CITY_STATE, 8
	releaseall
	end

GoldenrodCity_UndergroundTunnel_Movement_Kimono_WalkToPlayerBot:
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

GoldenrodCity_UndergroundTunnel_Movement_Kimono_WalkToPlayerTop:
	walk_up
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

GoldenrodCity_UndergroundTunnel_Movement_Kimono_Leave1:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

GoldenrodCity_UndergroundTunnel_Movement_Kimono_Spin:
	face_down
	face_right
	face_up
	face_left
	face_down
	face_right
	face_up
	step_end

GoldenrodCity_UndergroundTunnel_Movement_Kimono_Leave2:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

GoldenrodCity_UndergroundTunnel_Text_Kimono1:
	.string "Tea{SE_M_MILK_DRINK}Rocke{SE_M_SPIT_UP}member{SE_M_GRASSWHISTLE}i{SE_M_ATTRACT}blac{SE_M_ENCORE2}suits\n"
	.string "hav{SE_M_REVERSAL}bee{SE_M_ATTRACT}runnin{SE_M_SANDSTORM}around...\p"
	.string "{SE_M_HEAL_BELL}wa{SE_M_GRASSWHISTLE}wonderin{SE_M_SANDSTORM}wha{SE_M_SPIT_UP}wa{SE_M_GRASSWHISTLE}goin{SE_M_SANDSTORM}on.\n"
	.string "So{SE_M_SUPERSONIC}yo{SE_M_DIVE}too{SE_M_ENCORE2}o{SE_M_ATTRACT}Tea{SE_M_MILK_DRINK}Rocket?\l"
	.string "Yo{SE_M_DIVE}ar{SE_M_REVERSAL}impressive!\p"
	.string "Yo{SE_M_DIVE}ma{SE_M_YAWN}b{SE_M_REVERSAL}abl{SE_M_REVERSAL}t{SE_M_ATTRACT2}fac{SE_M_REVERSAL}the\n"
	.string "legendar{SE_M_YAWN}POKé...$"

GoldenrodCity_UndergroundTunnel_Text_Kimono2:
	.string "Hahaha{SE_M_DRAGON_RAGE}Neve{SE_M_SAND_TOMB}mind.\n"
	.string "{SE_M_HEAL_BELL}mus{SE_M_SPIT_UP}g{SE_M_ATTRACT2}now.$"

GoldenrodUnderground_EventScript_Eric::
	trainerbattle_single TRAINER_JOHTO_ERIC_HNS, GoldenrodUnderground_Text_SupernerdEricSeen, GoldenrodUnderground_Text_SupernerdEricBeaten
	msgbox GoldenrodUnderground_Text_SupernerdEricAfterBattle, MSGBOX_AUTOCLOSE
	end

GoldenrodUnderground_EventScript_Teru::
	trainerbattle_single TRAINER_JOHTO_TERU_HNS, GoldenrodUnderground_Text_SupernerdTeruSeen, GoldenrodUnderground_Text_SupernerdTeruBeaten
	msgbox GoldenrodUnderground_Text_SupernerdTeruAfterBattle, MSGBOX_AUTOCLOSE
	end

GoldenrodUnderground_EventScript_Issac::
	trainerbattle_single TRAINER_JOHTO_ISSAC_HNS, GoldenrodUnderground_Text_PokemaniacIssacSeen, GoldenrodUnderground_Text_PokemaniacIssacBeaten
	msgbox GoldenrodUnderground_Text_PokemaniacIssacAfterBattle, MSGBOX_AUTOCLOSE
	end

GoldenrodUnderground_EventScript_Donald::
	trainerbattle_single TRAINER_JOHTO_DONALD_HNS, GoldenrodUnderground_Text_PokemaniacDonaldSeen, GoldenrodUnderground_Text_PokemaniacDonaldBeaten
	msgbox GoldenrodUnderground_Text_PokemaniacDonaldAfterBattle, MSGBOX_AUTOCLOSE
	end

GoldenrodUnderground_EventScript_Brother_Haircut1::
	lock
	faceplayer
	goto_if_set JOHTO_FLAG_DAILY_HAIRCUT1_RECEIVED, GoldenrodUnderground_EventScript_Already_Got_Haircut1
	showmoneybox 0, 0
	msgbox GoldenrodUnderground_Text_OlderBrotherOffer, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, TRUE, GoldenrodUnderground_EventScript_Haircut1
	msgbox GoldenrodUnderground_Text_OlderBrotherThatsAShame, MSGBOX_DEFAULT
	hidemoneybox
	closemessage
	end

GoldenrodUnderground_EventScript_Haircut1::
	msgbox GoldenrodUnderground_Text_OlderBrotherAskWhich
	special ChoosePartyMon
	waitstate
	showmoneybox 0, 0
	lock
	faceplayer
	goto_if_ge VAR_0x8004, PARTY_SIZE, GoldenrodUnderground_EventScript_Declined_Haircut1
	specialvar VAR_RESULT, ScriptGetPartyMonSpecies
	goto_if_eq VAR_RESULT, (1572 + 1), GoldenrodUnderground_EventScript_Declined_Haircut1
	checkmoney 500, 0
	goto_if_eq VAR_RESULT, FALSE, GoldenrodUnderground_EventScript_NotEnough_Haircut1
	removemoney 500
	updatemoneybox 0
	playse SE_SHOP
	msgbox GoldenrodUnderground_Text_OlderBrotherWatchItBeautiful
	closemessage
	fadescreen FADE_TO_BLACK
	playfanfare MUS_HEAL
	waitfanfare
	special HaircutBrother2
	fadescreen FADE_FROM_BLACK
	special BufferMonNickname
	msgbox GoldenrodUnderground_Text_OlderBrotherAllDone
	hidemoneybox
	setflag JOHTO_FLAG_DAILY_HAIRCUT1_RECEIVED
	release
	end

GoldenrodUnderground_EventScript_Declined_Haircut1::
	msgbox GoldenrodUnderground_Text_OlderBrotherThatsAShame, MSGBOX_DEFAULT
	hidemoneybox
	closemessage
	release
	end

GoldenrodUnderground_EventScript_Already_Got_Haircut1::
	msgbox GoldenrodUnderground_Text_OlderBrotherOnePerDay, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodUnderground_EventScript_NotEnough_Haircut1::
	msgbox GoldenrodUnderground_Text_OlderBrotherNeedMoreMoney, MSGBOX_DEFAULT
	closemessage
	hidemoneybox
	release
	end

GoldenrodUnderground_EventScript_Brother_Haircut2::
	lock
	faceplayer
	goto_if_set JOHTO_FLAG_DAILY_HAIRCUT2_RECEIVED, GoldenrodUnderground_EventScript_Already_Got_Haircut2
	showmoneybox 0, 0
	msgbox GoldenrodUnderground_Text_YoungerBrotherOffer, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, TRUE, GoldenrodUnderground_EventScript_Haircut2
	msgbox GoldenrodUnderground_Text_YoungerBrotherDisappointed, MSGBOX_DEFAULT
	hidemoneybox
	closemessage
	end

GoldenrodUnderground_EventScript_Haircut2::
	msgbox GoldenrodUnderground_Text_YoungerBrotherAskWhich
	special ChoosePartyMon
	waitstate
	showmoneybox 0, 0
	lock
	faceplayer
	goto_if_ge VAR_0x8004, PARTY_SIZE, GoldenrodUnderground_EventScript_Declined_Haircut2
	specialvar VAR_RESULT, ScriptGetPartyMonSpecies
	goto_if_eq VAR_RESULT, (1572 + 1), GoldenrodUnderground_EventScript_Declined_Haircut2
	checkmoney 300, 0
	goto_if_eq VAR_RESULT, FALSE, GoldenrodUnderground_EventScript_NotEnough_Haircut2
	removemoney 300
	updatemoneybox 0
	playse SE_SHOP
	msgbox GoldenrodUnderground_Text_YoungerBrotherLookCool
	closemessage
	fadescreen FADE_TO_BLACK
	playfanfare MUS_HEAL
	waitfanfare
	special HaircutBrother1
	fadescreen FADE_FROM_BLACK
	special BufferMonNickname
	msgbox GoldenrodUnderground_Text_YoungerBrotherAllDone
	hidemoneybox
	setflag JOHTO_FLAG_DAILY_HAIRCUT2_RECEIVED
	release
	end

GoldenrodUnderground_EventScript_Declined_Haircut2::
	msgbox GoldenrodUnderground_Text_YoungerBrotherDisappointed, MSGBOX_DEFAULT
	hidemoneybox
	closemessage
	release
	end

GoldenrodUnderground_EventScript_Already_Got_Haircut2::
	msgbox GoldenrodUnderground_Text_YoungerBrotherOnePerDay, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodUnderground_EventScript_NotEnough_Haircut2::
	msgbox GoldenrodUnderground_Text_YoungerBrotherShortOnFunds, MSGBOX_DEFAULT
	closemessage
	hidemoneybox
	release
	end

GoldenrodCity_UndergroundTunnel_MapScript_TryOpenDoor::
	goto_if_set JOHTO_FLAG_UNLOCKED_GOLDENROD_UNDERGROUND_DOOR, GoldenrodCity_UndergroundTunnel_MapScript_OpenDoor
	end

GoldenrodCity_UndergroundTunnel_MapScript_OpenDoor::
	setmetatile 12, 10, 0x2DD, FALSE
	end

GoldenrodCity_UndergroundTunnel_EventScript_Door::
	lock
	goto_if_set JOHTO_FLAG_UNLOCKED_GOLDENROD_UNDERGROUND_DOOR, GoldenrodCity_UndergroundTunnel_EventScript_DoorAlreadyOpened
	checkitem ITEM_BASEMENT_KEY
	goto_if_eq VAR_RESULT, TRUE, GoldenrodCity_UndergroundTunnel_EventScript_OpenDoor
	msgbox GoldenrodUnderground_Text_DoorsLocked, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_UndergroundTunnel_EventScript_OpenDoor::
	msgbox GoldenrodUnderground_Text_KeyOpenedDoor, MSGBOX_DEFAULT
	closemessage
	setflag JOHTO_FLAG_UNLOCKED_GOLDENROD_UNDERGROUND_DOOR
	setmetatile 12, 10, 0x2DD, FALSE
	playse SE_BANG
	special DrawWholeMapView
	waitse
	release
	end

GoldenrodCity_UndergroundTunnel_EventScript_DoorAlreadyOpened::
	msgbox GoldenrodUnderground_Text_DoorIsOpen, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_UndergroundTunnel_EventScript_Item_CoinCase::
	finditem ITEM_COIN_CASE
	end

GoldenrodCity_UndergroundTunnel_EventScript_Item_SuperPotion::
	finditem ITEM_SUPER_POTION
	end

GoldenrodCity_UndergroundTunnel_EventScript_Item_ParalyzeHeal::
	finditem ITEM_PARALYZE_HEAL
	end

GoldenrodCity_UndergroundTunnel_EventScript_Item_Antidote::
	finditem ITEM_ANTIDOTE
	end

GoldenrodUnderground_Text_YoungerBrotherOffer:
	.string "Welcom{SE_M_REVERSAL}t{SE_M_ATTRACT2}th{SE_M_REVERSAL}POKéMO{SE_M_PSYBEAM2}SALON!\p"
	.string "I'{SE_M_MILK_DRINK}th{SE_M_REVERSAL}younge{SE_M_SAND_TOMB}an{SE_M_WATERFALL}les{SE_M_GRASSWHISTLE}expensive\n"
	.string "o{SE_M_ACID_ARMOR}th{SE_M_REVERSAL}tw{SE_M_ATTRACT2}HAIRCU{SE_M_SWIFT}BROTHERS.\p"
	.string "I'l{SE_M_BATON_PASS}spif{SE_M_ACID_ARMOR}u{SE_M_MORNING_SUN}you{SE_M_SAND_TOMB}POKéMO{SE_M_PSYBEAM2}fo{SE_M_SAND_TOMB}just\n"
	.string "¥300.\p"
	.string "So{SE_M_SING}Ho{SE_M_TWISTER}abou{SE_M_SPIT_UP}it?$"

GoldenrodUnderground_Text_YoungerBrotherAskWhich:
	.string "OK{SE_M_SUPERSONIC}whic{SE_M_TRI_ATTACK}POKéMO{SE_M_PSYBEAM2}shoul{SE_M_WATERFALL}{SE_M_HEAL_BELL}do?$"

GoldenrodUnderground_Text_YoungerBrotherLookCool:
	.string "OK{SE_M_DRAGON_RAGE}I'l{SE_M_BATON_PASS}mak{SE_M_REVERSAL}i{SE_M_SPIT_UP}loo{SE_M_ENCORE2}cool!$"

GoldenrodUnderground_Text_YoungerBrotherAllDone:
	.string "Ther{SE_M_REVERSAL}w{SE_M_REVERSAL}go{SE_M_DRAGON_RAGE}Al{SE_M_BATON_PASS}done!$"

GoldenrodUnderground_Text_YoungerBrotherDisappointed:
	.string "No{SE_M_SING}Ho{SE_M_TWISTER}disappointing!$"

GoldenrodUnderground_Text_YoungerBrotherShortOnFunds:
	.string "You'r{SE_M_REVERSAL}{SE_M_CHARGE}littl{SE_M_REVERSAL}shor{SE_M_SPIT_UP}o{SE_M_ATTRACT}funds.$"

GoldenrodUnderground_Text_YoungerBrotherOnePerDay:
	.string "{SE_M_HEAL_BELL}ca{SE_M_ATTRACT}d{SE_M_ATTRACT2}onl{SE_M_YAWN}on{SE_M_REVERSAL}haircu{SE_M_SPIT_UP}{SE_M_CHARGE}day.\p"
	.string "Sorry{SE_M_SUPERSONIC}bu{SE_M_SPIT_UP}I'{SE_M_MILK_DRINK}al{SE_M_BATON_PASS}don{SE_M_REVERSAL}fo{SE_M_SAND_TOMB}today.$"

GoldenrodUnderground_Text_OlderBrotherOffer:
	.string "Welcome!\p"
	.string "{SE_M_HEAL_BELL}ru{SE_M_ATTRACT}th{SE_M_REVERSAL}POKéMO{SE_M_PSYBEAM2}SALON!\p"
	.string "I'{SE_M_MILK_DRINK}th{SE_M_REVERSAL}olde{SE_M_SAND_TOMB}an{SE_M_WATERFALL}bette{SE_M_SAND_TOMB}o{SE_M_ACID_ARMOR}th{SE_M_REVERSAL}two\n"
	.string "HAIRCU{SE_M_SWIFT}BROTHERS.\p"
	.string "{SE_M_HEAL_BELL}ca{SE_M_ATTRACT}mak{SE_M_REVERSAL}you{SE_M_SAND_TOMB}POKéMO{SE_M_PSYBEAM2}beautiful\n"
	.string "fo{SE_M_SAND_TOMB}jus{SE_M_SPIT_UP}¥500.\p"
	.string "Woul{SE_M_WATERFALL}yo{SE_M_DIVE}lik{SE_M_REVERSAL}m{SE_M_REVERSAL}t{SE_M_ATTRACT2}d{SE_M_ATTRACT2}that?$"

GoldenrodUnderground_Text_OlderBrotherAskWhich:
	.string "Whic{SE_M_TRI_ATTACK}POKéMO{SE_M_PSYBEAM2}shoul{SE_M_WATERFALL}{SE_M_HEAL_BELL}wor{SE_M_ENCORE2}on?$"

GoldenrodUnderground_Text_OlderBrotherWatchItBeautiful:
	.string "OK{SE_M_DRAGON_RAGE}Watc{SE_M_TRI_ATTACK}i{SE_M_SPIT_UP}becom{SE_M_REVERSAL}beautiful!$"

GoldenrodUnderground_Text_OlderBrotherAllDone:
	.string "There{SE_M_DRAGON_RAGE}Al{SE_M_BATON_PASS}done!$"

GoldenrodUnderground_Text_OlderBrotherThatsAShame:
	.string "I{SE_M_GRASSWHISTLE}tha{SE_M_SPIT_UP}right{SE_M_SING}That'{SE_M_GRASSWHISTLE}{SE_M_CHARGE}shame!$"

GoldenrodUnderground_Text_OlderBrotherNeedMoreMoney:
	.string "You'l{SE_M_BATON_PASS}nee{SE_M_WATERFALL}mor{SE_M_REVERSAL}mone{SE_M_YAWN}tha{SE_M_ATTRACT}that.$"

GoldenrodUnderground_Text_OlderBrotherOnePerDay:
	.string "{SE_M_HEAL_BELL}d{SE_M_ATTRACT2}onl{SE_M_YAWN}on{SE_M_REVERSAL}haircu{SE_M_SPIT_UP}{SE_M_CHARGE}day.\n"
	.string "I'{SE_M_MILK_DRINK}don{SE_M_REVERSAL}fo{SE_M_SAND_TOMB}today.$"

GoldenrodUnderground_Text_SupernerdEricSeen:
	.string "{SE_M_HEAL_BELL}go{SE_M_SPIT_UP}boote{SE_M_WATERFALL}ou{SE_M_SPIT_UP}o{SE_M_ACID_ARMOR}th{SE_M_REVERSAL}GAM{SE_M_SWORDS_DANCE}CORNER.\p"
	.string "{SE_M_HEAL_BELL}wa{SE_M_GRASSWHISTLE}tryin{SE_M_SANDSTORM}t{SE_M_ATTRACT2}chea{SE_M_SPIT_UP}usin{SE_M_SANDSTORM}my\n"
	.string "POKéMON…$"

GoldenrodUnderground_Text_SupernerdEricBeaten:
	.string "…Grumble…$"

GoldenrodUnderground_Text_SupernerdEricAfterBattle:
	.string "{SE_M_HEAL_BELL}gues{SE_M_GRASSWHISTLE}{SE_M_HEAL_BELL}hav{SE_M_REVERSAL}t{SE_M_ATTRACT2}d{SE_M_ATTRACT2}thing{SE_M_GRASSWHISTLE}fai{SE_M_SAND_TOMB}and\n"
	.string "square…$"

GoldenrodUnderground_Text_SupernerdTeruSeen:
	.string "D{SE_M_ATTRACT2}yo{SE_M_DIVE}conside{SE_M_SAND_TOMB}typ{SE_M_REVERSAL}alignment{SE_M_GRASSWHISTLE}in\n"
	.string "battle?\p"
	.string "I{SE_M_ACID_ARMOR}yo{SE_M_DIVE}kno{SE_M_TWISTER}you{SE_M_SAND_TOMB}typ{SE_M_REVERSAL}advantages,\n"
	.string "you'l{SE_M_BATON_PASS}d{SE_M_ATTRACT2}bette{SE_M_SAND_TOMB}i{SE_M_ATTRACT}battle.$"

GoldenrodUnderground_Text_SupernerdTeruBeaten:
	.string "Ow{SE_M_SUPERSONIC}ow{SE_M_SUPERSONIC}ow!$"

GoldenrodUnderground_Text_SupernerdTeruAfterBattle:
	.string "{SE_M_HEAL_BELL}kno{SE_M_TWISTER}m{SE_M_YAWN}POKéMO{SE_M_PSYBEAM2}typ{SE_M_REVERSAL}alignments.\p"
	.string "Bu{SE_M_SPIT_UP}{SE_M_HEAL_BELL}onl{SE_M_YAWN}us{SE_M_REVERSAL}on{SE_M_REVERSAL}typ{SE_M_REVERSAL}o{SE_M_ACID_ARMOR}POKéMON.$"

GoldenrodUnderground_Text_PokemaniacIssacSeen:
	.string "M{SE_M_YAWN}POKéMO{SE_M_PSYBEAM2}jus{SE_M_SPIT_UP}go{SE_M_SPIT_UP}{SE_M_CHARGE}haircut!\p"
	.string "I'l{SE_M_BATON_PASS}sho{SE_M_TWISTER}yo{SE_M_DIVE}ho{SE_M_TWISTER}stron{SE_M_SANDSTORM}i{SE_M_SPIT_UP}is!$"

GoldenrodUnderground_Text_PokemaniacIssacBeaten:
	.string "Aiyeeee!$"

GoldenrodUnderground_Text_PokemaniacIssacAfterBattle:
	.string "You{SE_M_SAND_TOMB}POKéMO{SE_M_PSYBEAM2}wil{SE_M_BATON_PASS}lik{SE_M_REVERSAL}yo{SE_M_DIVE}mor{SE_M_REVERSAL}if\n"
	.string "yo{SE_M_DIVE}giv{SE_M_REVERSAL}the{SE_M_MILK_DRINK}haircuts.$"

GoldenrodUnderground_Text_PokemaniacDonaldSeen:
	.string "{SE_M_HEAL_BELL}thin{SE_M_ENCORE2}yo{SE_M_DIVE}hav{SE_M_REVERSAL}som{SE_M_REVERSAL}rar{SE_M_REVERSAL}POKéMON\n"
	.string "wit{SE_M_TRI_ATTACK}you.\p"
	.string "Le{SE_M_SPIT_UP}m{SE_M_REVERSAL}se{SE_M_REVERSAL}them!$"

GoldenrodUnderground_Text_PokemaniacDonaldBeaten:
	.string "Gaah{SE_M_DRAGON_RAGE}{SE_M_HEAL_BELL}lost{SE_M_DRAGON_RAGE}Tha{SE_M_SPIT_UP}make{SE_M_GRASSWHISTLE}m{SE_M_REVERSAL}mad!$"

GoldenrodUnderground_Text_PokemaniacDonaldAfterBattle:
	.string "Whe{SE_M_ATTRACT}{SE_M_HEAL_BELL}wa{SE_M_GRASSWHISTLE}walkin{SE_M_SANDSTORM}nea{SE_M_SAND_TOMB}th{SE_M_REVERSAL}BIKE\n"
	.string "SHO{SE_M_PETAL_DANCE}las{SE_M_SPIT_UP}night{SE_M_SUPERSONIC}{SE_M_HEAL_BELL}fel{SE_M_SPIT_UP}lik{SE_M_REVERSAL}{SE_M_HEAL_BELL}was\l"
	.string "bein{SE_M_SANDSTORM}watche{SE_M_WATERFALL}fro{SE_M_MILK_DRINK}th{SE_M_REVERSAL}rooftops...$"

GoldenrodUnderground_Text_PokemaniacDonaldAfterBattleOld:
	.string "Ar{SE_M_REVERSAL}yo{SE_M_DIVE}makin{SE_M_SANDSTORM}{SE_M_CHARGE}POKéDEX{SE_M_SING}Here'{SE_M_GRASSWHISTLE}a\n"
	.string "ho{SE_M_SPIT_UP}tip.\p"
	.string "Th{SE_M_REVERSAL}HIKE{SE_M_MINIMIZE}o{SE_M_ATTRACT}ROUT{SE_M_SWORDS_DANCE}33{SE_M_SUPERSONIC}ANTHONY{SE_M_SUPERSONIC}i{SE_M_GRASSWHISTLE}a\n"
	.string "goo{SE_M_WATERFALL}guy.\p"
	.string "He'l{SE_M_BATON_PASS}phon{SE_M_REVERSAL}yo{SE_M_DIVE}i{SE_M_ACID_ARMOR}h{SE_M_REVERSAL}see{SE_M_GRASSWHISTLE}an{SE_M_YAWN}rare\n"
	.string "POKéMON.$"

GoldenrodUnderground_Text_DoorsLocked:
	.string "Th{SE_M_REVERSAL}door'{SE_M_GRASSWHISTLE}locked…$"

GoldenrodUnderground_Text_DoorIsOpen:
	.string "Th{SE_M_REVERSAL}doo{SE_M_SAND_TOMB}i{SE_M_GRASSWHISTLE}open.$"

GoldenrodUnderground_Text_KeyOpenedDoor:
	.string "Th{SE_M_REVERSAL}BASEMEN{SE_M_SWIFT}KE{SE_M_MOONLIGHT}opene{SE_M_WATERFALL}th{SE_M_REVERSAL}door.$"

GoldenrodUnderground_Text_NoEntry:
	.string "N{SE_M_SOLAR_BEAM}ENTR{SE_M_MOONLIGHT}BEYON{SE_M_FAINT_ATTACK}THI{SE_M_SKETCH}POINT$"

