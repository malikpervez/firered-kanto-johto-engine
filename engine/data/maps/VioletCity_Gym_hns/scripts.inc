@ Johto (data/maps/VioletCity_Gym_hns/scripts.inc), as built into the FireRed game.

VioletCity_Gym_hns_MapScripts::
	.byte 0

VioletCity_Gym_EventScript_GymGuy::
	lock
	faceplayer
	goto_if_set JOHTO_FLAG_DEFEATED_VIOLET_GYM, VioletCity_Gym_EventScript_GymGuy2
	msgbox VioletGym_Text_GymGuide_Intro, MSGBOX_DEFAULT
	closemessage
	release
	end

VioletCity_Gym_EventScript_GymGuy2::
	msgbox VioletGym_Text_GymGuide_Win, MSGBOX_DEFAULT
	release
	end

VioletCity_Gym_EventScript_Rod::
	trainerbattle_single TRAINER_JOHTO_ROD_HNS, VioletGym_Text_BirdKeeperRod_Seen, VioletGym_Text_BirdKeeperRod_Beaten
	msgbox VioletGym_Text_BirdKeeperRod_After, MSGBOX_AUTOCLOSE
	end

VioletCity_Gym_EventScript_Abe::
	trainerbattle_single TRAINER_JOHTO_ABE_HNS, VioletGym_Text_BirdKeeperAbe_Seen, VioletGym_Text_BirdKeeperAbe_Beaten
	msgbox VioletGym_Text_BirdKeeperAbe_After, MSGBOX_AUTOCLOSE
	end

VioletCity_Gym_EventScript_Falkner::
	lock
	faceplayer
	goto_if_set JOHTO_FLAG_DEFEATED_VIOLET_GYM, VioletCity_Gym_EventScript_Falkner_Defeated
	msgbox VioletGym_Text_Falkner_Intro, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_JOHTO_FALKNER_1_HNS, VioletGym_Text_Falkner_WinLoss
	message VioletGym_Text_ReceivedZephyrBadge
	waitmessage
	call J_Common_EventScript_PlayGymBadgeFanfare
	msgbox VioletGym_Text_Falkner_BadgeExplain, MSGBOX_DEFAULT
	setflag JOHTO_FLAG_BADGE01_GET
	setflag JOHTO_FLAG_DEFEATED_VIOLET_GYM
	addvar JOHTO_VAR_NUM_BADGES, 1
	setvar VAR_0x8008, 1
	call J_Common_EventScript_SetGymTrainers_hns
	giveitem ITEM_TM_ROOST
	msgbox VioletGym_Text_Falkner_TMExplain, MSGBOX_DEFAULT
	setvar JOHTO_VAR_VIOLET_CITY_STATE, 3
	setrespawn JOHTO_HEAL_LOCATION_VIOLET_CITY_HNS
	closemessage
	release
	end

VioletCity_Gym_EventScript_Falkner_Defeated::
	msgbox VioletGym_Text_Falkner_AfterFight, MSGBOX_DEFAULT
	closemessage
	release
	end

VioletGym_Text_Falkner_Intro:
	.string "I'{SE_M_MILK_DRINK}FALKNER{SE_M_SUPERSONIC}th{SE_M_REVERSAL}VIOLE{SE_M_SWIFT}POKéMON\n"
	.string "GY{SE_M_GIGA_DRAIN}leader!\p"
	.string "Peopl{SE_M_REVERSAL}sa{SE_M_YAWN}yo{SE_M_DIVE}ca{SE_M_ATTRACT}clip\n"
	.string "FLYING-typ{SE_M_REVERSAL}POKéMON'{SE_M_GRASSWHISTLE}wings\p"
	.string "wit{SE_M_TRI_ATTACK}{SE_M_CHARGE}jol{SE_M_SPIT_UP}o{SE_M_ACID_ARMOR}electricity…\n"
	.string "{SE_M_HEAL_BELL}won'{SE_M_SPIT_UP}allo{SE_M_TWISTER}suc{SE_M_TRI_ATTACK}insult{SE_M_GRASSWHISTLE}t{SE_M_ATTRACT2}bird\l"
	.string "POKéMON!\p"
	.string "I'l{SE_M_BATON_PASS}sho{SE_M_TWISTER}yo{SE_M_DIVE}th{SE_M_REVERSAL}rea{SE_M_BATON_PASS}power\n"
	.string "o{SE_M_ACID_ARMOR}th{SE_M_REVERSAL}magnificen{SE_M_SPIT_UP}bir{SE_M_WATERFALL}POKéMON!$"

VioletGym_Text_Falkner_WinLoss:
	.string "…Darn{SE_M_DRAGON_RAGE}M{SE_M_YAWN}dad'{SE_M_GRASSWHISTLE}cherishe{SE_M_WATERFALL}bird\n"
	.string "POKéMON…\p"
	.string "Al{SE_M_BATON_PASS}right{SE_M_PERISH_SONG}Tak{SE_M_REVERSAL}this.\p"
	.string "It'{SE_M_GRASSWHISTLE}th{SE_M_REVERSAL}officia{SE_M_BATON_PASS}POKéMO{SE_M_PSYBEAM2}LEAGUE\n"
	.string "ZEPHYRBADGE.$"

VioletGym_Text_ReceivedZephyrBadge:
	.string "{PLAYER} receive{SE_M_WATERFALL}ZEPHYRBADGE.$"

VioletGym_Text_Falkner_BadgeExplain:
	.string "ZEPHYRBADG{SE_M_SWORDS_DANCE}raise{SE_M_GRASSWHISTLE}th{SE_M_REVERSAL}ATTACK\n"
	.string "powe{SE_M_SAND_TOMB}o{SE_M_ACID_ARMOR}POKéMON.\p"
	.string "I{SE_M_SPIT_UP}als{SE_M_ATTRACT2}enable{SE_M_GRASSWHISTLE}POKéMO{SE_M_PSYBEAM2}t{SE_M_ATTRACT2}use\n"
	.string "FLASH{SE_M_SUPERSONIC}i{SE_M_ACID_ARMOR}the{SE_M_YAWN}ca{SE_M_ATTRACT}lear{SE_M_ATTRACT}it,\l"
	.string "anytime.\p"
	.string "Here--tak{SE_M_REVERSAL}thi{SE_M_GRASSWHISTLE}too.$"

VioletGym_Text_Falkner_TMExplain:
	.string "B{SE_M_YAWN}usin{SE_M_SANDSTORM}{SE_M_CHARGE}TM{SE_M_SUPERSONIC}{SE_M_CHARGE}POKéMO{SE_M_PSYBEAM2}will\n"
	.string "instantl{SE_M_YAWN}lear{SE_M_ATTRACT}{SE_M_CHARGE}ne{SE_M_TWISTER}move.\p"
	.string "Tha{SE_M_SPIT_UP}T{SE_M_GIGA_DRAIN}contain{SE_M_GRASSWHISTLE}ROOST.\p"
	.string "I{SE_M_SPIT_UP}restore{SE_M_GRASSWHISTLE}H{SE_M_PETAL_DANCE}u{SE_M_MORNING_SUN}t{SE_M_ATTRACT2}hal{SE_M_ACID_ARMOR}o{SE_M_ACID_ARMOR}your\n"
	.string "POKéMON'{SE_M_GRASSWHISTLE}maximum.\p"
	.string "I{SE_M_ATTRACT}othe{SE_M_SAND_TOMB}words{SE_M_SUPERSONIC}i{SE_M_SPIT_UP}heal{SE_M_GRASSWHISTLE}your\n"
	.string "POKéMON.$"

VioletGym_Text_Falkner_AfterFight:
	.string "Ther{SE_M_REVERSAL}ar{SE_M_REVERSAL}POKéMO{SE_M_PSYBEAM2}GYM{SE_M_SKETCH}i{SE_M_ATTRACT}cities\n"
	.string "an{SE_M_WATERFALL}town{SE_M_GRASSWHISTLE}ahead.\p"
	.string "Yo{SE_M_DIVE}shoul{SE_M_WATERFALL}tes{SE_M_SPIT_UP}you{SE_M_SAND_TOMB}skill{SE_M_GRASSWHISTLE}at\n"
	.string "thes{SE_M_REVERSAL}GYMS.\p"
	.string "I'{SE_M_MILK_DRINK}goin{SE_M_SANDSTORM}t{SE_M_ATTRACT2}trai{SE_M_ATTRACT}harde{SE_M_SAND_TOMB}to\n"
	.string "becom{SE_M_REVERSAL}th{SE_M_REVERSAL}greates{SE_M_SPIT_UP}bir{SE_M_WATERFALL}master!$"

VioletGym_Text_Falkner_Rematch:
	.string "Congratulation{SE_M_GRASSWHISTLE}o{SE_M_ATTRACT}defeating\n"
	.string "th{SE_M_REVERSAL}ELIT{SE_M_SWORDS_DANCE}4!\p"
	.string "I'v{SE_M_REVERSAL}bee{SE_M_ATTRACT}trainin{SE_M_SANDSTORM}my\n"
	.string "FLYING-typ{SE_M_REVERSAL}POKéMO{SE_M_PSYBEAM2}eve{SE_M_ATTRACT}harder.\p"
	.string "Thin{SE_M_ENCORE2}yo{SE_M_DIVE}ca{SE_M_ATTRACT}tak{SE_M_REVERSAL}o{SE_M_ATTRACT}th{SE_M_REVERSAL}power\n"
	.string "o{SE_M_ACID_ARMOR}th{SE_M_REVERSAL}skie{SE_M_GRASSWHISTLE}again?$"

VioletGym_Text_Falkner_RematchLoss:
	.string "Wow{SE_M_DIZZY_PUNCH}Yo{SE_M_DIVE}bea{SE_M_SPIT_UP}m{SE_M_REVERSAL}again.\p"
	.string "I'{SE_M_MILK_DRINK}goin{SE_M_SANDSTORM}t{SE_M_ATTRACT2}trai{SE_M_ATTRACT}harde{SE_M_SAND_TOMB}to\n"
	.string "becom{SE_M_REVERSAL}th{SE_M_REVERSAL}greates{SE_M_SPIT_UP}bir{SE_M_WATERFALL}master!$"

VioletGym_Text_BirdKeeperRod_Seen:
	.string "Th{SE_M_REVERSAL}keywor{SE_M_WATERFALL}i{SE_M_GRASSWHISTLE}guts!\p"
	.string "Thos{SE_M_REVERSAL}her{SE_M_REVERSAL}ar{SE_M_REVERSAL}trainin{SE_M_SANDSTORM}nigh{SE_M_SPIT_UP}and\n"
	.string "da{SE_M_YAWN}t{SE_M_ATTRACT2}becom{SE_M_REVERSAL}bir{SE_M_WATERFALL}POKéMO{SE_M_PSYBEAM2}masters.\p"
	.string "Com{SE_M_REVERSAL}on!$"

VioletGym_Text_BirdKeeperRod_Beaten:
	.string "Gaaah!$"

VioletGym_Text_BirdKeeperRod_After:
	.string "FALKNER'{SE_M_GRASSWHISTLE}skill{SE_M_GRASSWHISTLE}ar{SE_M_REVERSAL}fo{SE_M_SAND_TOMB}real!\p"
	.string "Don'{SE_M_SPIT_UP}ge{SE_M_SPIT_UP}cock{SE_M_YAWN}jus{SE_M_SPIT_UP}because\n"
	.string "yo{SE_M_DIVE}bea{SE_M_SPIT_UP}me!$"

VioletGym_Text_BirdKeeperAbe_Seen:
	.string "Le{SE_M_SPIT_UP}m{SE_M_REVERSAL}se{SE_M_REVERSAL}i{SE_M_ACID_ARMOR}yo{SE_M_DIVE}ar{SE_M_REVERSAL}good\n"
	.string "enoug{SE_M_TRI_ATTACK}t{SE_M_ATTRACT2}fac{SE_M_REVERSAL}FALKNER!$"

VioletGym_Text_BirdKeeperAbe_Beaten:
	.string "Thi{SE_M_GRASSWHISTLE}can'{SE_M_SPIT_UP}b{SE_M_REVERSAL}true!$"

VioletGym_Text_BirdKeeperAbe_After:
	.string "Thi{SE_M_GRASSWHISTLE}i{SE_M_GRASSWHISTLE}pathetic{SE_M_SUPERSONIC}losin{SE_M_SANDSTORM}t{SE_M_ATTRACT2}some\n"
	.string "rooki{SE_M_REVERSAL}trainer…$"

VioletGym_Text_GymGuide_Intro:
	.string "Hey{SE_M_DRAGON_RAGE}What'{SE_M_GRASSWHISTLE}up{SE_M_SING}I'{SE_M_MILK_DRINK}n{SE_M_ATTRACT2}trainer,\n"
	.string "bu{SE_M_SPIT_UP}{SE_M_HEAL_BELL}ca{SE_M_ATTRACT}giv{SE_M_REVERSAL}som{SE_M_REVERSAL}advice!\p"
	.string "Believ{SE_M_REVERSAL}me{SE_M_DRAGON_RAGE}I{SE_M_ACID_ARMOR}yo{SE_M_DIVE}believe{SE_M_SUPERSONIC}a\n"
	.string "championshi{SE_M_MORNING_SUN}drea{SE_M_MILK_DRINK}ca{SE_M_ATTRACT}com{SE_M_REVERSAL}true.\p"
	.string "Yo{SE_M_DIVE}believe{SE_M_SING}The{SE_M_ATTRACT}listen.\p"
	.string "FALKNER'{SE_M_GRASSWHISTLE}ac{SE_M_REVERSAL}i{SE_M_GRASSWHISTLE}{SE_M_CHARGE}bulk{SE_M_YAWN}owl\n"
	.string "tha{SE_M_SPIT_UP}love{SE_M_GRASSWHISTLE}t{SE_M_ATTRACT2}ea{SE_M_SPIT_UP}BERRIES.\p"
	.string "Whil{SE_M_REVERSAL}it'{SE_M_GRASSWHISTLE}no{SE_M_SPIT_UP}th{SE_M_REVERSAL}strongest,\n"
	.string "i{SE_M_SPIT_UP}ca{SE_M_ATTRACT}tak{SE_M_REVERSAL}{SE_M_CHARGE}lo{SE_M_SPIT_UP}o{SE_M_ACID_ARMOR}hits.\p"
	.string "Yo{SE_M_DIVE}ca{SE_M_ATTRACT}hur{SE_M_SPIT_UP}i{SE_M_SPIT_UP}wit{SE_M_TRI_ATTACK}ELECTRI{SE_M_PSYBEAM}\n"
	.string "an{SE_M_WATERFALL}ROCK-typ{SE_M_REVERSAL}moves{SE_M_SUPERSONIC}bu{SE_M_SPIT_UP}watc{SE_M_TRI_ATTACK}out\l"
	.string "fo{SE_M_SAND_TOMB}MUD-SLAP!\p"
	.string "I{SE_M_ACID_ARMOR}yo{SE_M_DIVE}wan{SE_M_SPIT_UP}mor{SE_M_REVERSAL}help{SE_M_SUPERSONIC}g{SE_M_ATTRACT2}visi{SE_M_SPIT_UP}the\n"
	.string "POKéMO{SE_M_PSYBEAM2}ACADEMY.\p"
	.string "Th{SE_M_REVERSAL}student{SE_M_GRASSWHISTLE}ther{SE_M_REVERSAL}reall{SE_M_YAWN}know\n"
	.string "thei{SE_M_SAND_TOMB}stuff!$"

VioletGym_Text_GymGuide_Win:
	.string "Nic{SE_M_REVERSAL}battle{SE_M_DRAGON_RAGE}Kee{SE_M_MORNING_SUN}i{SE_M_SPIT_UP}up,\n"
	.string "an{SE_M_WATERFALL}you'l{SE_M_BATON_PASS}b{SE_M_REVERSAL}th{SE_M_REVERSAL}CHAM{SE_M_PETAL_DANCE}i{SE_M_ATTRACT}no\l"
	.string "tim{SE_M_REVERSAL}a{SE_M_SPIT_UP}all!$"

VioletCity_Gym_EventScript_Statue::
	lock
	goto_if_set JOHTO_FLAG_DEFEATED_VIOLET_GYM, VioletCity_Gym_EventScript_Statue2
	msgbox VioletCity_Gym_Text_GymStatue, MSGBOX_DEFAULT
	closemessage
	release
	end

VioletCity_Gym_EventScript_Statue2::
	msgbox VioletCity_Gym_Text_GymStatueCertified, MSGBOX_DEFAULT
	closemessage
	release
	end

VioletCity_Gym_Text_GymStatue:
	.string "VIOLE{SE_M_SWIFT}CIT{SE_M_MOONLIGHT}POKéMO{SE_M_PSYBEAM2}GYM$"

VioletCity_Gym_Text_GymStatueCertified:
	.string "VIOLE{SE_M_SWIFT}CIT{SE_M_MOONLIGHT}POKéMO{SE_M_PSYBEAM2}GYM\p"
	.string "FALKNER'{SE_M_SKETCH}CERTIFIE{SE_M_FAINT_ATTACK}TRAINERS:\n"
	.string "{PLAYER}$"

