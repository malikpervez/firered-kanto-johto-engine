@ Johto (data/maps/Route32_hns/scripts.inc), as built into the FireRed game.

Route32_hns_MapScripts::
	map_script 3, Route32_OnTransition
	map_script 5, J_SetTimeEncounters
	.byte 0

Route32_OnTransition:
	callnative SetTimeBasedEncounters
	end

Route32_EventScript_FisherJustin::
	trainerbattle_single 1200, Route32_Text_FisherJustin_Seen, Route32_Text_FisherJustin_Beaten
	msgbox Route32_Text_FisherJustin_After, MSGBOX_AUTOCLOSE
	end

Route32_EventScript_FisherRalph::
	trainerbattle_single 1201, Route32_Text_FisherRalph1_Seen, Route32_Text_FisherRalph1_Beaten, Route32_EventScript_RegisterRalph
	specialvar 32781, ShouldTryRematchBattle
	goto_if_eq 32781, TRUE, Route32_EventScript_RematchRalph
	msgbox Route32_Text_FisherRalph1_After, MSGBOX_AUTOCLOSE
	end

Route32_EventScript_RegisterRalph::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox Route32_Text_RalphRegister, MSGBOX_DEFAULT
	register_matchcall 1201
	release
	end

Route32_EventScript_RematchRalph::
	trainerbattle_rematch 1201, Route32_Text_RalphRematchIntro, Route32_Text_RalphRematchDefeat
	msgbox Route32_Text_RalphPostRematch, MSGBOX_AUTOCLOSE
	end

Route32_EventScript_FisherHenry::
	trainerbattle_single 1204, Route32_Text_FisherHenry_Seen, Route32_Text_FisherHenry_Beaten
	msgbox Route32_Text_FisherHenry_After, MSGBOX_AUTOCLOSE
	end

Route32_EventScript_YoungsterAlbert::
	trainerbattle_single 1033, Route32_Text_YoungsterAlbert_Seen, Route32_Text_YoungsterAlbert_Beaten
	msgbox Route32_Text_YoungsterAlbert_After, MSGBOX_AUTOCLOSE
	end

Route32_EventScript_YoungsterGordon::
	trainerbattle_single 1034, Route32_Text_YoungsterGordon_Seen, Route32_Text_YoungsterGordon_Beaten
	msgbox Route32_Text_YoungsterGordon_After, MSGBOX_AUTOCLOSE
	end

Route32_EventScript_CamperRoland::
	trainerbattle_single 1355, Route32_Text_CamperRoland_Seen, Route32_Text_CamperRoland_Beaten
	msgbox Route32_Text_CamperRoland_After, MSGBOX_AUTOCLOSE
	end

Route32_EventScript_PicnickerLiz::
	trainerbattle_single 1342, Route32_Text_PicnickerLiz1_Seen, Route32_Text_PicnickerLiz1_Beaten, Route32_EventScript_RegisterLiz
	specialvar 32781, ShouldTryRematchBattle
	goto_if_eq 32781, TRUE, Route32_EventScript_RematchLiz
	msgbox Route32_Text_PicnickerLiz1_After, MSGBOX_AUTOCLOSE
	end

Route32_EventScript_RegisterLiz::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox Route32_Text_LizRegister, MSGBOX_DEFAULT
	register_matchcall 1342
	release
	end

Route32_EventScript_RematchLiz::
	trainerbattle_rematch 1342, Route32_Text_LizRematchIntro, Route32_Text_LizRematchDefeat
	msgbox Route32_Text_LizPostRematch, MSGBOX_AUTOCLOSE
	end

Route32_EventScript_BirdkeeperPeter::
	trainerbattle_single 1065, Route32_Text_BirdKeeperPeter_Seen, Route32_Text_BirdKeeperPeter_Beaten
	msgbox Route32_Text_BirdKeeperPeter_After, MSGBOX_AUTOCLOSE
	end

Route32_EventScript_Roar::
	lock
	faceplayer
	checkitem 586
	goto_if_eq 32781, TRUE, Route32_EventScript_Roar2
	msgbox Route32_Text_RoarIntro, MSGBOX_DEFAULT
	giveitem 586
	msgbox Route32_Text_RoarOutro, MSGBOX_DEFAULT
	closemessage
	release
	end

Route32_EventScript_Roar2::
	msgbox Route32_Text_RoarOutro, MSGBOX_DEFAULT
	closemessage
	release
	end

Route32_EventScript_SlowpokeTail_TriggerLeft::
	lock
	turnobject 14, DIR_EAST
	turnobject 255, DIR_WEST
	playse 21
	applymovement 14, J_Common_Movement_ExclamationMark
	delay 55
	waitmovement 14
	applymovement 14, Route32_Movement_SlowpokeLeft
	waitmovement 0
	goto Route32_EventScript_SlowpokeTail_Trigger

Route32_EventScript_SlowpokeTail_TriggerMid::
	lock
	turnobject 14, DIR_EAST
	turnobject 255, DIR_WEST
	playse 21
	applymovement 14, J_Common_Movement_ExclamationMark
	delay 55
	waitmovement 14
	applymovement 14, Route32_Movement_SlowpokeMid
	waitmovement 0
	goto Route32_EventScript_SlowpokeTail_Trigger

Route32_EventScript_SlowpokeTail_TriggerRight::
	lock
	turnobject 14, DIR_EAST
	turnobject 255, DIR_WEST
	playse 21
	applymovement 14, J_Common_Movement_ExclamationMark
	delay 55
	waitmovement 14
	applymovement 14, Route32_Movement_SlowpokeRight
	waitmovement 0
	goto Route32_EventScript_SlowpokeTail_Trigger

Route32_EventScript_SlowpokeTail_Trigger::
	msgbox Route32_Text_SlowpokeTailOffer, MSGBOX_YESNO
	goto_if_eq 32781, TRUE, Route32_EventScript_SlowpokeTail_Trigger2
	msgbox Route32_Text_RefusedSlowpokeTail, MSGBOX_DEFAULT
	closemessage
	setvar 20655, 1
	release
	end

Route32_EventScript_SlowpokeTail_Trigger2::
	msgbox Route32_Text_ThoughtKidsLoaded, MSGBOX_DEFAULT
	closemessage
	getplayerxy 16384, 16385
	call_if_eq 16384, 16, Route32_EventScript_Movement_Left
	call_if_eq 16384, 17, Route32_EventScript_Movement_Right
	setvar 20655, 1
	release
	end

Route32_EventScript_Movement_Left::
	applymovement 14, J_Common_Movement_WalkLeft1
	waitmovement 0
	turnobject 14, DIR_EAST
	return

Route32_EventScript_Movement_Right::
	applymovement 14, J_Common_Movement_WalkLeft1
	waitmovement 0
	applymovement 14, J_Common_Movement_WalkLeft1
	waitmovement 0
	turnobject 14, DIR_EAST
	return

Route32_EventScript_SlowpokeTail::
	lock
	faceplayer
	msgbox Route32_Text_SlowpokeTailOffer, MSGBOX_YESNO
	goto_if_eq 32781, TRUE, Route32_EventScript_SlowpokeTail2
	msgbox Route32_Text_RefusedSlowpokeTail, MSGBOX_DEFAULT
	closemessage
	release
	end

Route32_EventScript_SlowpokeTail2::
	msgbox Route32_Text_ThoughtKidsLoaded, MSGBOX_DEFAULT
	closemessage
	release
	end

Route32_EventScript_Frieda::
	lock
	faceplayer
	goto_if_set 8731, Route32_EventScript_FriedaCompleted
	msgbox Route32_Text_MeetFrieda, MSGBOX_DEFAULT
	closemessage
	multichoice 20, 0, 159, FALSE
	switch 32781
	case 0, Route32_EventScript_FriedaNope
	case 1, Route32_EventScript_FriedaNope
	case 2, Route32_EventScript_FriedaNope
	case 3, Route32_EventScript_FriedaNope
	case 4, Route32_EventScript_FriedaNope
	case 5, Route32_EventScript_FriedaYes
	case 6, Route32_EventScript_FriedaNope
	case 7, Route32_EventScript_FriedaCancel
	case 127, Route32_EventScript_FriedaCancel
	closemessage
	release
	end

Route32_EventScript_FriedaYes::
	msgbox Route32_Text_FriedaGivesGift, MSGBOX_DEFAULT
	giveitem ITEM_POISON_BARB
	goto_if_eq 32781, FALSE, J_Common_EventScript_ShowBagIsFull
	setflag 8731
	msgbox Route32_Text_FriedaGaveGift, MSGBOX_DEFAULT
	closemessage
	release
	end

Route32_EventScript_FriedaNope::
	msgbox Route32_Text_FriedaNope, MSGBOX_DEFAULT
	closemessage
	release
	end

Route32_EventScript_FriedaCancel::
	closemessage
	release
	end

Route32_EventScript_FriedaCompleted::
	msgbox Route32_Text_FriedaFriday, MSGBOX_DEFAULT
	closemessage
	release
	end

Route32_EventScript_BaldingMan::
	lock
	faceplayer
	msgbox Route32_Text_CooltrainerM_Experiences, MSGBOX_DEFAULT
	closemessage
	turnobject 1, DIR_EAST
	release
	end

Route32_EventScript_BaldingManTriggerLeft::
	lock
	playse 21
	applymovement 1, J_Common_Movement_ExclamationMark
	delay 55
	waitmovement 1
	turnobject 255, DIR_WEST
	goto Route32_EventScript_BaldingManCheck
	end

Route32_EventScript_BaldingManTriggerMid::
	lock
	playse 21
	applymovement 1, J_Common_Movement_ExclamationMark
	delay 55
	waitmovement 1
	applymovement 255, Route32_Movement_StartMid
	waitmovement 0
	goto Route32_EventScript_BaldingManCheck
	end

Route32_EventScript_BaldingManTriggerRight::
	lock
	playse 21
	applymovement 1, J_Common_Movement_ExclamationMark
	delay 55
	waitmovement 1
	applymovement 255, Route32_Movment_StartRight
	waitmovement 0
	goto Route32_EventScript_BaldingManCheck
	end

Route32_EventScript_BaldingManCheck::
	goto_if_unset 8280, Route32_EventScript_BaldingManTower
	goto_if_unset 8743, Route32_EventScript_BaldingManGym
	goto_if_unset 8703, Route32_EventScript_BaldingManEgg
	msgbox Route32_Text_CooltrainerM_HaveThisSeed, MSGBOX_DEFAULT
	giveitem ITEM_MIRACLE_SEED
	goto_if_eq 32781, FALSE, J_Common_EventScript_ShowBagIsFull
	closemessage
	setvar 20609, 5
	release
	end

Route32_EventScript_BaldingManTower::
	msgbox Route32_Text_CooltrainerM_WhatsTheHurry, MSGBOX_DEFAULT
	msgbox Route32_Text_CooltrainerM_SproutTower, MSGBOX_DEFAULT
	closemessage
	applymovement 255, Route32_Movement_Turnback
	waitmovement 0
	release
	end

Route32_EventScript_BaldingManGym::
	msgbox Route32_Text_CooltrainerM_WhatsTheHurry, MSGBOX_DEFAULT
	msgbox Route32_Text_CooltrainerM_VioletGym, MSGBOX_DEFAULT
	closemessage
	applymovement 255, Route32_Movement_Turnback
	waitmovement 0
	release
	end

Route32_EventScript_BaldingManEgg::
	msgbox Route32_Text_CooltrainerM_WhatsTheHurry, MSGBOX_DEFAULT
	msgbox Route32_Text_CooltrainerM_AideIsWaiting, MSGBOX_DEFAULT
	closemessage
	applymovement 255, Route32_Movement_Turnback
	waitmovement 0
	release
	end

Route32_EventScript_Item_Bullet_Seed::
	finditem 590
	end

Route32_EventScript_GreatBall::
	finditem ITEM_GREAT_BALL
	end

Route32_EventScript_GreatBallII::
	finditem ITEM_GREAT_BALL
	end

Route32_EventScript_SuperPotion::
	finditem ITEM_SUPER_POTION
	end

Route32_EventScript_Sign1::
	lock
	msgbox Route32_Text_Sign1, MSGBOX_SIGN
	closemessage
	release
	end

Route32_EventScript_Sign2::
	lock
	msgbox Route32_Text_Sign2, MSGBOX_SIGN
	closemessage
	release
	end

Route32_EventScript_Sign3::
	lock
	msgbox Route32_Text_Sign3, MSGBOX_SIGN
	closemessage
	release
	end

Route32_Movement_Turnback:
	walk_up
	step_end

Route32_Movement_StartMid:
	walk_left
	step_end

Route32_Movment_StartRight:
	walk_left
	walk_left
	step_end

Route32_Movement_SlowpokeLeft::
	step_end

Route32_Movement_SlowpokeMid::
	walk_right
	step_end

Route32_Movement_SlowpokeRight::
	walk_right
	walk_right
	step_end

Route32_Text_CooltrainerM_WhatsTheHurry:
	.string "Wai{SE_M_SPIT_UP}up!\n"
	.string "What'{SE_M_GRASSWHISTLE}th{SE_M_REVERSAL}hurry?$"

Route32_Text_CooltrainerM_AideIsWaiting:
	.string "{PLAYER}{SE_M_SUPERSONIC}right?\n"
	.string "Som{SE_M_REVERSAL}gu{SE_M_YAWN}wearin{SE_M_SANDSTORM}glasses\p"
	.string "wa{SE_M_GRASSWHISTLE}lookin{SE_M_SANDSTORM}fo{SE_M_SAND_TOMB}you.\p"
	.string "Se{SE_M_REVERSAL}fo{SE_M_SAND_TOMB}yourself{SE_M_PERISH_SONG}He'{SE_M_GRASSWHISTLE}waitin{SE_M_SANDSTORM}for\n"
	.string "yo{SE_M_DIVE}a{SE_M_SPIT_UP}th{SE_M_REVERSAL}POKéMO{SE_M_PSYBEAM2}CENTER.$"

Route32_Text_CooltrainerM_SproutTower:
	.string "Hav{SE_M_REVERSAL}yo{SE_M_DIVE}gon{SE_M_REVERSAL}t{SE_M_ATTRACT2}SPROU{SE_M_SWIFT}TOWER?\n"
	.string "I{SE_M_ACID_ARMOR}yo{SE_M_DIVE}eve{SE_M_SAND_TOMB}visi{SE_M_SPIT_UP}VIOLE{SE_M_SWIFT}CITY,\p"
	.string "they'l{SE_M_BATON_PASS}expec{SE_M_SPIT_UP}yo{SE_M_DIVE}t{SE_M_ATTRACT2}trai{SE_M_ATTRACT}there.\n"
	.string "That'{SE_M_GRASSWHISTLE}basi{SE_M_HYPER_BEAM}fo{SE_M_SAND_TOMB}trainers.\p"
	.string "G{SE_M_ATTRACT2}t{SE_M_ATTRACT2}SPROU{SE_M_SWIFT}TOWER!$"

Route32_Text_CooltrainerM_VioletGym:
	.string "Hav{SE_M_REVERSAL}yo{SE_M_DIVE}gon{SE_M_REVERSAL}t{SE_M_ATTRACT2}th{SE_M_REVERSAL}POKéMO{SE_M_PSYBEAM2}GYM?\n"
	.string "Yo{SE_M_DIVE}ca{SE_M_ATTRACT}tes{SE_M_SPIT_UP}you{SE_M_SAND_TOMB}POKéMO{SE_M_PSYBEAM2}and\p"
	.string "yoursel{SE_M_ACID_ARMOR}there.\n"
	.string "It'{SE_M_GRASSWHISTLE}{SE_M_CHARGE}rit{SE_M_REVERSAL}o{SE_M_ACID_ARMOR}passag{SE_M_REVERSAL}fo{SE_M_SAND_TOMB}all\p"
	.string "trainers!$"

Route32_Text_CooltrainerM_HaveThisSeed:
	.string "Yo{SE_M_DIVE}hav{SE_M_REVERSAL}som{SE_M_REVERSAL}goo{SE_M_WATERFALL}POKéMO{SE_M_PSYBEAM2}there.\n"
	.string "I{SE_M_SPIT_UP}mus{SE_M_SPIT_UP}b{SE_M_REVERSAL}fro{SE_M_MILK_DRINK}th{SE_M_REVERSAL}trainin{SE_M_SANDSTORM}you\p"
	.string "gav{SE_M_REVERSAL}the{SE_M_MILK_DRINK}aroun{SE_M_WATERFALL}VIOLE{SE_M_SWIFT}CITY.\n"
	.string "Th{SE_M_REVERSAL}trainin{SE_M_SANDSTORM}a{SE_M_SPIT_UP}th{SE_M_REVERSAL}GY{SE_M_GIGA_DRAIN}mus{SE_M_SPIT_UP}have\p"
	.string "bee{SE_M_ATTRACT}especiall{SE_M_YAWN}helpful{SE_M_PERISH_SONG}A{SE_M_GRASSWHISTLE}a\n"
	.string "souveni{SE_M_SAND_TOMB}o{SE_M_ACID_ARMOR}VIOLE{SE_M_SWIFT}CITY{SE_M_SUPERSONIC}tak{SE_M_REVERSAL}this.\p"
	.string "I{SE_M_SPIT_UP}increase{SE_M_GRASSWHISTLE}th{SE_M_REVERSAL}powe{SE_M_SAND_TOMB}o{SE_M_ACID_ARMOR}GRASS-\n"
	.string "typ{SE_M_REVERSAL}moves.$"

Route32_Text_CooltrainerM_Experiences:
	.string "You{SE_M_SAND_TOMB}experience{SE_M_GRASSWHISTLE}i{SE_M_ATTRACT}VIOLE{SE_M_SWIFT}CITY\n"
	.string "shoul{SE_M_WATERFALL}b{SE_M_REVERSAL}usefu{SE_M_BATON_PASS}fo{SE_M_SAND_TOMB}you{SE_M_SAND_TOMB}journey.$"

Route32_Text_SlowpokeTailOffer:
	.string "Ho{SE_M_TWISTER}woul{SE_M_WATERFALL}yo{SE_M_DIVE}lik{SE_M_REVERSAL}t{SE_M_ATTRACT2}hav{SE_M_REVERSAL}this\n"
	.string "tasty{SE_M_SUPERSONIC}nutritiou{SE_M_GRASSWHISTLE}SLOWPOKETAIL?\p"
	.string "Fo{SE_M_SAND_TOMB}yo{SE_M_DIVE}righ{SE_M_SPIT_UP}now{SE_M_SUPERSONIC}just\n"
	.string "¥1,000,000!\p"
	.string "You'l{SE_M_BATON_PASS}wan{SE_M_SPIT_UP}this!$"

Route32_Text_ThoughtKidsLoaded:
	.string "Tch{SE_M_DRAGON_RAGE}{SE_M_HEAL_BELL}though{SE_M_SPIT_UP}kids\n"
	.string "thes{SE_M_REVERSAL}day{SE_M_GRASSWHISTLE}wer{SE_M_REVERSAL}loaded…$"

Route32_Text_RefusedSlowpokeTail:
	.string "Yo{SE_M_DIVE}don'{SE_M_SPIT_UP}wan{SE_M_SPIT_UP}it?\n"
	.string "The{SE_M_ATTRACT}scram{SE_M_PERISH_SONG}Shoo!$"

Route32_Text_FisherJustin_Seen:
	.string "Whoa!\p"
	.string "Yo{SE_M_DIVE}mad{SE_M_REVERSAL}m{SE_M_REVERSAL}los{SE_M_REVERSAL}tha{SE_M_SPIT_UP}fish!$"

Route32_Text_FisherJustin_Beaten:
	.string "Sploosh!$"

Route32_Text_FisherJustin_After:
	.string "Calm{SE_M_SUPERSONIC}collected{SE_M_DIZZY_PUNCH}Th{SE_M_REVERSAL}essenc{SE_M_REVERSAL}of\n"
	.string "fishin{SE_M_SANDSTORM}an{SE_M_WATERFALL}POKéMO{SE_M_PSYBEAM2}i{SE_M_GRASSWHISTLE}th{SE_M_REVERSAL}same.$"

Route32_Text_FisherRalph1_Seen:
	.string "I'{SE_M_MILK_DRINK}reall{SE_M_YAWN}goo{SE_M_WATERFALL}a{SE_M_SPIT_UP}both\n"
	.string "fishin{SE_M_SANDSTORM}an{SE_M_WATERFALL}POKéMON.\p"
	.string "I'{SE_M_MILK_DRINK}no{SE_M_SPIT_UP}abou{SE_M_SPIT_UP}t{SE_M_ATTRACT2}los{SE_M_REVERSAL}t{SE_M_ATTRACT2}an{SE_M_YAWN}kid!$"

Route32_Text_FisherRalph1_Beaten:
	.string "Tch{SE_M_DRAGON_RAGE}{SE_M_HEAL_BELL}trie{SE_M_WATERFALL}t{SE_M_ATTRACT2}rush\n"
	.string "things…$"

Route32_Text_FisherRalph1_After:
	.string "Fishin{SE_M_SANDSTORM}i{SE_M_GRASSWHISTLE}{SE_M_CHARGE}lifelong\n"
	.string "passion.\p"
	.string "POKéMO{SE_M_PSYBEAM2}ar{SE_M_REVERSAL}lifelon{SE_M_SANDSTORM}friends!$"

Route32_Text_RalphRegister:
	.string "Fishin{SE_M_SANDSTORM}i{SE_M_GRASSWHISTLE}{SE_M_CHARGE}lifelong\n"
	.string "passion.\p"
	.string "POKéMO{SE_M_PSYBEAM2}ar{SE_M_REVERSAL}lifelon{SE_M_SANDSTORM}friends!$"

Route32_Text_RalphRematchIntro:
	.string "I'{SE_M_MILK_DRINK}reall{SE_M_YAWN}goo{SE_M_WATERFALL}a{SE_M_SPIT_UP}both\n"
	.string "fishin{SE_M_SANDSTORM}an{SE_M_WATERFALL}POKéMON.\p"
	.string "I'{SE_M_MILK_DRINK}no{SE_M_SPIT_UP}abou{SE_M_SPIT_UP}t{SE_M_ATTRACT2}los{SE_M_REVERSAL}t{SE_M_ATTRACT2}an{SE_M_YAWN}kid!$"

Route32_Text_RalphRematchDefeat:
	.string "Tch{SE_M_DRAGON_RAGE}{SE_M_HEAL_BELL}trie{SE_M_WATERFALL}t{SE_M_ATTRACT2}rush\n"
	.string "things…$"

Route32_Text_RalphPostRematch:
	.string "Fishin{SE_M_SANDSTORM}i{SE_M_GRASSWHISTLE}{SE_M_CHARGE}lifelong\n"
	.string "passion.\p"
	.string "POKéMO{SE_M_PSYBEAM2}ar{SE_M_REVERSAL}lifelon{SE_M_SANDSTORM}friends!$"

Route32_Text_FisherHenry_Seen:
	.string "M{SE_M_YAWN}POKéMON{SE_M_SING}Freshl{SE_M_YAWN}caught!$"

Route32_Text_FisherHenry_Beaten:
	.string "SPLASH?$"

Route32_Text_FisherHenry_After:
	.string "Freshl{SE_M_YAWN}caugh{SE_M_SPIT_UP}POKéMO{SE_M_PSYBEAM2}are\n"
	.string "n{SE_M_ATTRACT2}matc{SE_M_TRI_ATTACK}fo{SE_M_SAND_TOMB}properl{SE_M_YAWN}raise{SE_M_WATERFALL}ones.$"

Route32_Text_YoungsterAlbert_Seen:
	.string "{SE_M_HEAL_BELL}haven'{SE_M_SPIT_UP}see{SE_M_ATTRACT}yo{SE_M_DIVE}aroun{SE_M_WATERFALL}before.\n"
	.string "S{SE_M_ATTRACT2}yo{SE_M_DIVE}thin{SE_M_ENCORE2}yo{SE_M_DIVE}ar{SE_M_REVERSAL}prett{SE_M_YAWN}tough?$"

Route32_Text_YoungsterAlbert_Beaten:
	.string "You'r{SE_M_REVERSAL}strong!$"

Route32_Text_YoungsterAlbert_After:
	.string "I'{SE_M_MILK_DRINK}goin{SE_M_SANDSTORM}t{SE_M_ATTRACT2}tr{SE_M_YAWN}t{SE_M_ATTRACT2}b{SE_M_REVERSAL}the\n"
	.string "bes{SE_M_SPIT_UP}wit{SE_M_TRI_ATTACK}m{SE_M_YAWN}favorites.\p"
	.string "I'{SE_M_MILK_DRINK}no{SE_M_SPIT_UP}usin{SE_M_SANDSTORM}th{SE_M_REVERSAL}sam{SE_M_REVERSAL}tough\n"
	.string "POKéMO{SE_M_PSYBEAM2}a{SE_M_GRASSWHISTLE}everyon{SE_M_REVERSAL}else.$"

Route32_Text_YoungsterGordon_Seen:
	.string "{SE_M_HEAL_BELL}foun{SE_M_WATERFALL}som{SE_M_REVERSAL}goo{SE_M_WATERFALL}POKéMON\n"
	.string "i{SE_M_ATTRACT}th{SE_M_REVERSAL}grass!\p"
	.string "{SE_M_HEAL_BELL}thin{SE_M_ENCORE2}they'l{SE_M_BATON_PASS}d{SE_M_ATTRACT2}i{SE_M_SPIT_UP}fo{SE_M_SAND_TOMB}me!$"

Route32_Text_YoungsterGordon_Beaten:
	.string "Darn{SE_M_PERISH_SONG}{SE_M_HEAL_BELL}though{SE_M_SPIT_UP}{SE_M_HEAL_BELL}coul{SE_M_WATERFALL}win.$"

Route32_Text_YoungsterGordon_After:
	.string "Th{SE_M_REVERSAL}gras{SE_M_GRASSWHISTLE}i{SE_M_GRASSWHISTLE}ful{SE_M_BATON_PASS}of\n"
	.string "cling{SE_M_YAWN}things.$"

Route32_Text_CamperRoland_Seen:
	.string "Tha{SE_M_SPIT_UP}glance{SE_M_DIZZY_PUNCH}It'{SE_M_GRASSWHISTLE}intriguing.$"

Route32_Text_CamperRoland_Beaten:
	.string "Hmmm{SE_M_PERISH_SONG}Thi{SE_M_GRASSWHISTLE}i{SE_M_GRASSWHISTLE}disappointing.$"

Route32_Text_CamperRoland_After:
	.string "I{SE_M_ACID_ARMOR}yo{SE_M_DIVE}don'{SE_M_SPIT_UP}wan{SE_M_SPIT_UP}t{SE_M_ATTRACT2}battle,\n"
	.string "jus{SE_M_SPIT_UP}avoi{SE_M_WATERFALL}ey{SE_M_REVERSAL}contact.$"

Route32_Text_PicnickerLiz1_Seen:
	.string "Uh-huh{SE_M_PERISH_SONG}Yeah{SE_M_SUPERSONIC}an{SE_M_WATERFALL}yo{SE_M_DIVE}know…\p"
	.string "Pardon{SE_M_SING}Battle{SE_M_SING}I'{SE_M_MILK_DRINK}o{SE_M_ATTRACT}th{SE_M_REVERSAL}phone.\n"
	.string "Oh{SE_M_SUPERSONIC}al{SE_M_BATON_PASS}right{SE_M_PERISH_SONG}Bu{SE_M_SPIT_UP}mak{SE_M_REVERSAL}i{SE_M_SPIT_UP}fast.$"

Route32_Text_PicnickerLiz1_Beaten:
	.string "Oh{SE_M_DRAGON_RAGE}I'v{SE_M_REVERSAL}go{SE_M_SPIT_UP}t{SE_M_ATTRACT2}relieve\n"
	.string "m{SE_M_YAWN}anger!$"

Route32_Text_PicnickerLiz1_After:
	.string "{SE_M_HEAL_BELL}wa{SE_M_GRASSWHISTLE}havin{SE_M_SANDSTORM}{SE_M_CHARGE}nic{SE_M_REVERSAL}cha{SE_M_SPIT_UP}too.$"

Route32_Text_LizRegister:
	.string "{SE_M_HEAL_BELL}wa{SE_M_GRASSWHISTLE}havin{SE_M_SANDSTORM}{SE_M_CHARGE}nic{SE_M_REVERSAL}cha{SE_M_SPIT_UP}too.$"

Route32_Text_LizRematchIntro:
	.string "Uh-huh{SE_M_PERISH_SONG}Yeah{SE_M_SUPERSONIC}an{SE_M_WATERFALL}yo{SE_M_DIVE}know…\p"
	.string "Pardon{SE_M_SING}Battle{SE_M_SING}I'{SE_M_MILK_DRINK}o{SE_M_ATTRACT}th{SE_M_REVERSAL}phone.\n"
	.string "Oh{SE_M_SUPERSONIC}al{SE_M_BATON_PASS}right{SE_M_PERISH_SONG}Bu{SE_M_SPIT_UP}mak{SE_M_REVERSAL}i{SE_M_SPIT_UP}fast.$"

Route32_Text_LizRematchDefeat:
	.string "Oh{SE_M_DRAGON_RAGE}I'v{SE_M_REVERSAL}go{SE_M_SPIT_UP}t{SE_M_ATTRACT2}relieve\n"
	.string "m{SE_M_YAWN}anger!$"

Route32_Text_LizPostRematch:
	.string "{SE_M_HEAL_BELL}wa{SE_M_GRASSWHISTLE}havin{SE_M_SANDSTORM}{SE_M_CHARGE}nic{SE_M_REVERSAL}cha{SE_M_SPIT_UP}too.$"

Route32_Text_BirdKeeperPeter_Seen:
	.string "Tha{SE_M_SPIT_UP}BADGE{SE_M_DRAGON_RAGE}It'{SE_M_GRASSWHISTLE}fro{SE_M_MILK_DRINK}VIOLE{SE_M_SWIFT}CITY!\n"
	.string "Yo{SE_M_DIVE}bea{SE_M_SPIT_UP}FALKNER?$"

Route32_Text_BirdKeeperPeter_Beaten:
	.string "{SE_M_HEAL_BELL}kno{SE_M_TWISTER}wha{SE_M_SPIT_UP}m{SE_M_YAWN}weaknesse{SE_M_GRASSWHISTLE}are.$"

Route32_Text_BirdKeeperPeter_After:
	.string "{SE_M_HEAL_BELL}shoul{SE_M_WATERFALL}trai{SE_M_ATTRACT}agai{SE_M_ATTRACT}a{SE_M_SPIT_UP}the\n"
	.string "GY{SE_M_GIGA_DRAIN}i{SE_M_ATTRACT}VIOLE{SE_M_SWIFT}CITY.$"

Route32_Text_RoarIntro:
	.string "WROOOOAR{SE_M_DRAGON_RAGE}PEOPL{SE_M_SWORDS_DANCE}RU{SE_M_PSYBEAM2}WHE{SE_M_PSYBEAM2}I\n"
	.string "ROAR{SE_M_DRAGON_RAGE}BU{SE_M_SWIFT}YO{SE_M_REFLECT}CAM{SE_M_SWORDS_DANCE}LOOKING!\p"
	.string "THA{SE_M_SWIFT}PLEASE{SE_M_SKETCH}ME{SE_M_DRAGON_RAGE}NO{SE_M_DETECT}TAK{SE_M_SWORDS_DANCE}THIS!$"

Route32_Text_RoarOutro:
	.string "WROOOOAR{SE_M_DRAGON_RAGE}IT'{SE_M_SKETCH}ROAR!\p"
	.string "EVE{SE_M_PSYBEAM2}POKéMO{SE_M_PSYBEAM2}RU{SE_M_PSYBEAM2}FRO{SE_M_GIGA_DRAIN}{SE_M_BONEMERANG}GOOD\n"
	.string "ROAR!$"

Route32_Text_MeetFrieda:
	.string "FRIEDA{SE_M_HEAT_WAVE}Yahoo!\p"
	.string "I'{SE_M_MILK_DRINK}FRIED{SE_M_BONEMERANG}o{SE_M_ACID_ARMOR}th{SE_M_REVERSAL}WEEKDA{SE_M_MOONLIGHT}FAMILY!\n"
	.string "Nic{SE_M_REVERSAL}t{SE_M_ATTRACT2}mee{SE_M_SPIT_UP}you!\p"
	.string "I{SE_M_ACID_ARMOR}yo{SE_M_DIVE}ca{SE_M_ATTRACT}gues{SE_M_GRASSWHISTLE}m{SE_M_YAWN}favorit{SE_M_REVERSAL}day,\n"
	.string "I'l{SE_M_BATON_PASS}giv{SE_M_REVERSAL}yo{SE_M_DIVE}{SE_M_CHARGE}reward.$"

Route32_Text_FriedaGivesGift:
	.string "Here'{SE_M_GRASSWHISTLE}{SE_M_CHARGE}POISO{SE_M_PSYBEAM2}BAR{SE_M_LICK}fo{SE_M_SAND_TOMB}you!$"

Route32_Text_FriedaGaveGift:
	.string "FRIEDA{SE_M_HEAT_WAVE}Giv{SE_M_REVERSAL}i{SE_M_SPIT_UP}t{SE_M_ATTRACT2}{SE_M_CHARGE}POKéMON\n"
	.string "tha{SE_M_SPIT_UP}ha{SE_M_GRASSWHISTLE}POISON-typ{SE_M_REVERSAL}moves.\p"
	.string "Oh!\p"
	.string "It'{SE_M_GRASSWHISTLE}wicked!\p"
	.string "You'l{SE_M_BATON_PASS}b{SE_M_REVERSAL}shocke{SE_M_WATERFALL}ho{SE_M_TWISTER}goo{SE_M_WATERFALL}it\n"
	.string "make{SE_M_GRASSWHISTLE}poiso{SE_M_ATTRACT}moves!$"

Route32_Text_FriedaFriday:
	.string "FRIEDA{SE_M_HEAT_WAVE}Hiya{SE_M_DRAGON_RAGE}Wha{SE_M_SPIT_UP}da{SE_M_YAWN}do\n"
	.string "yo{SE_M_DIVE}like?\p"
	.string "{SE_M_HEAL_BELL}lov{SE_M_REVERSAL}Friday{SE_M_PERISH_SONG}N{SE_M_ATTRACT2}doub{SE_M_SPIT_UP}about\n"
	.string "it!\p"
	.string "Don'{SE_M_SPIT_UP}yo{SE_M_DIVE}thin{SE_M_ENCORE2}it'{SE_M_GRASSWHISTLE}grea{SE_M_SPIT_UP}too?$"

Route32_Text_FriedaNope:
	.string "FRIEDA{SE_M_HEAT_WAVE}No{SE_M_SPIT_UP}tha{SE_M_SPIT_UP}one!$"

Route32_Text_Sign1:
	.string "ROUT{SE_M_SWORDS_DANCE}32\p"
	.string "VIOLE{SE_M_SWIFT}CIT{SE_M_MOONLIGHT}{SE_M_PAY_DAY}AZALE{SE_M_BONEMERANG}TOWN$"

Route32_Text_Sign2:
	.string "RUIN{SE_M_SKETCH}O{SE_M_LEER}ALPH\n"
	.string "EAS{SE_M_SWIFT}ENTRANCE$"

Route32_Text_Sign3:
	.string "UNIO{SE_M_PSYBEAM2}CAVE\n"
	.string "AHEAD$"

