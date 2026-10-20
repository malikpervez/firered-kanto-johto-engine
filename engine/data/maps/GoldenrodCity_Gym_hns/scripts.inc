@ Johto (data/maps/GoldenrodCity_Gym_hns/scripts.inc), as built into the FireRed game.

GoldenrodCity_Gym_hns_MapScripts::
	.byte 0

GoldenrodCity_Gym_EventScript_Carrie::
	trainerbattle_single 1068, GoldenrodCity_Gym_Text_LassCarrieSeen, GoldenrodCity_Gym_Text_LassCarrieBeaten
	msgbox GoldenrodCity_Gym_Text_LassCarrieAfter, MSGBOX_AUTOCLOSE
	end

GoldenrodCity_Gym_EventScript_Bridget::
	trainerbattle_single 1069, GoldenrodCity_Gym_Text_LassBridgetSeen, GoldenrodCity_Gym_Text_LassBridgetBeaten
	msgbox GoldenrodCity_Gym_Text_LassBridgetAfter, MSGBOX_AUTOCLOSE
	end

GoldenrodCity_Gym_EventScript_Victoria::
	trainerbattle_single 1114, GoldenrodCity_Gym_Text_BeautyVictoriaSeen, GoldenrodCity_Gym_Text_BeautyVictoriaBeaten
	msgbox GoldenrodCity_Gym_Text_BeautyVictoriaAfter, MSGBOX_AUTOCLOSE
	end

GoldenrodCity_Gym_EventScript_Samantha::
	trainerbattle_single 1115, GoldenrodCity_Gym_Text_BeautySamanthaSeen, GoldenrodCity_Gym_Text_BeautySamanthaBeaten
	msgbox GoldenrodCity_Gym_Text_BeautySamanthaAfter, MSGBOX_AUTOCLOSE
	end

GoldenrodCity_Gym_EventScript_Gym_Guy::
	lock
	faceplayer
	goto_if_set 10370, GoldenrodCity_Gym_EventScript_Gym_Guy_After
	msgbox GoldenrodCity_Gym_Text_GymGuide, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_Gym_EventScript_Gym_Guy_After::
	msgbox GoldenrodCity_Gym_Text_GymGuideWin, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_Gym_EventScript_Whitney::
	lock
	faceplayer
	goto_if_eq 20569, 3, GoldenrodCity_Gym_EventScript_WhitneyCrying
	goto_if_eq 20569, 4, GoldenrodCity_Gym_EventScript_WhitneyBadge
	goto_if_set 8745, GoldenrodCity_Gym_EventScript_WhitneyDefeated
	msgbox GoldenrodCity_Gym_Text_WhitneyBefore, MSGBOX_DEFAULT
	trainerbattle_no_intro 1430, GoldenrodCity_Gym_Text_WhitneyShouldntBeSoSerious
	msgbox GoldenrodCity_Gym_Text_WhitneyYouMeanie, MSGBOX_DEFAULT
	setvar 20569, 3
	closemessage
	release
	end

GoldenrodCity_Gym_EventScript_WhitneyCrying::
	lock
	faceplayer
	msgbox GoldenrodCity_Gym_Text_WhitneyYouMeanie, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_Gym_EventScript_WhitneyBadge::
	lock
	faceplayer
	msgbox GoldenrodCity_Gym_Text_WhitneyWhatDoYouWant, MSGBOX_DEFAULT
	closemessage
	message GoldenrodCity_Gym_Text_PlayerReceivedPlainBadge
	waitmessage
	call J_Common_EventScript_PlayGymBadgeFanfare
	msgbox GoldenrodCity_Gym_Text_WhitneyPlainBadge, MSGBOX_DEFAULT
	setflag 10370
	setflag 8745
	addvar 20582, 1
	setvar 32776, 3
	call J_Common_EventScript_SetGymTrainers_hns
	giveitem 626
	msgbox GoldenrodCity_Gym_Text_WhitneyAttract, MSGBOX_DEFAULT
	setvar 20569, 5
	closemessage
	release
	end

GoldenrodCity_Gym_EventScript_WhitneyDefeated::
	lock
	faceplayer
	msgbox GoldenrodCity_Gym_Text_WhitneyGoodCry, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_Gym_EventScript_Trigger::
	turnobject 6 DIR_WEST
	msgbox GoldenrodCity_Gym_Text_BridgetWhitneyCries, MSGBOX_DEFAULT
	applymovement 255, J_Common_Movement_WalkUp1
	waitmovement 0
	setvar 20569, 4
	closemessage
	release
	end

GoldenrodCity_Gym_EventScript_Statue::
	lock
	goto_if_set 8745, GoldenrodCity_Gym_EventScript_Statue2
	msgbox GoldenrodCity_Gym_Text_GymStatue, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_Gym_EventScript_Statue2::
	msgbox GoldenrodCity_Gym_Text_GymStatueCertified, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_Gym_Text_GymStatue:
	.string "GOLDENRO{SE_M_FAINT_ATTACK}POKéMO{SE_M_PSYBEAM2}GYM$"

GoldenrodCity_Gym_Text_GymStatueCertified:
	.string "GOLDENRO{SE_M_FAINT_ATTACK}TOW{SE_M_PSYBEAM2}POKéMO{SE_M_PSYBEAM2}GYM\p"
	.string "WHITNEY'{SE_M_SKETCH}CERTIFIE{SE_M_FAINT_ATTACK}TRAINERS:\n"
	.string "{PLAYER}$"

GoldenrodCity_Gym_Text_WhitneyBefore:
	.string "Hi{SE_M_DRAGON_RAGE}I'{SE_M_MILK_DRINK}WHITNEY!\p"
	.string "Everyon{SE_M_REVERSAL}wa{SE_M_GRASSWHISTLE}int{SE_M_ATTRACT2}POKéMON{SE_M_SUPERSONIC}s{SE_M_ATTRACT2}{SE_M_HEAL_BELL}got\n"
	.string "int{SE_M_ATTRACT2}i{SE_M_SPIT_UP}too!\p"
	.string "POKéMO{SE_M_PSYBEAM2}ar{SE_M_REVERSAL}super-cute!\p"
	.string "Yo{SE_M_DIVE}wan{SE_M_SPIT_UP}t{SE_M_ATTRACT2}battle{SE_M_SING}I'{SE_M_MILK_DRINK}warning\n"
	.string "you{SE_M_PAY_DAY}I'{SE_M_MILK_DRINK}good!$"

GoldenrodCity_Gym_Text_WhitneyShouldntBeSoSerious:
	.string "Sob…\p"
	.string "…Waaaaaaah{SE_M_DRAGON_RAGE}You'r{SE_M_REVERSAL}mean!\p"
	.string "Yo{SE_M_DIVE}shouldn'{SE_M_SPIT_UP}b{SE_M_REVERSAL}s{SE_M_ATTRACT2}serious{SE_M_DRAGON_RAGE}You…\n"
	.string "yo{SE_M_DIVE}child{SE_M_SUPERSONIC}you!$"

GoldenrodCity_Gym_Text_WhitneyYouMeanie:
	.string "Waaaaah!\p"
	.string "Waaaaah!\p"
	.string "…Snivel{SE_M_SUPERSONIC}hic{SE_M_DIZZY_PUNCH}…Yo{SE_M_DIVE}meanie!$"

GoldenrodCity_Gym_Text_WhitneyWhatDoYouWant:
	.string "…Sniff…\p"
	.string "What{SE_M_SING}Wha{SE_M_SPIT_UP}d{SE_M_ATTRACT2}yo{SE_M_DIVE}want{SE_M_SING}{SE_M_BONEMERANG}BADGE?\p"
	.string "Oh{SE_M_SUPERSONIC}right{SE_M_PERISH_SONG}{SE_M_HEAL_BELL}forgot{SE_M_PERISH_SONG}Here's\n"
	.string "PLAINBADGE.$"

GoldenrodCity_Gym_Text_PlayerReceivedPlainBadge:
	.string "{PLAYER} receive{SE_M_WATERFALL}PLAINBADGE.$"

GoldenrodCity_Gym_Text_WhitneyPlainBadge:
	.string "PLAINBADG{SE_M_SWORDS_DANCE}let{SE_M_GRASSWHISTLE}you{SE_M_SAND_TOMB}POKéMO{SE_M_PSYBEAM2}use\n"
	.string "STRENGT{SE_M_SWAGGER2}outsid{SE_M_REVERSAL}o{SE_M_ACID_ARMOR}battle.\p"
	.string "I{SE_M_SPIT_UP}als{SE_M_ATTRACT2}boost{SE_M_GRASSWHISTLE}you{SE_M_SAND_TOMB}POKéMON's\n"
	.string "DEFENSE.\p"
	.string "Oh{SE_M_SUPERSONIC}yo{SE_M_DIVE}ca{SE_M_ATTRACT}hav{SE_M_REVERSAL}thi{SE_M_GRASSWHISTLE}too!$"

GoldenrodCity_Gym_Text_WhitneyAttract:
	.string "It'{SE_M_GRASSWHISTLE}ATTRACT{SE_M_DRAGON_RAGE}I{SE_M_SPIT_UP}make{SE_M_GRASSWHISTLE}ful{SE_M_BATON_PASS}us{SE_M_REVERSAL}o{SE_M_ACID_ARMOR}a\n"
	.string "POKéMON'{SE_M_GRASSWHISTLE}charm.\p"
	.string "Isn'{SE_M_SPIT_UP}i{SE_M_SPIT_UP}jus{SE_M_SPIT_UP}perfec{SE_M_SPIT_UP}fo{SE_M_SAND_TOMB}{SE_M_CHARGE}cutie\n"
	.string "lik{SE_M_REVERSAL}me?$"

GoldenrodCity_Gym_Text_WhitneyGoodCry:
	.string "Ah{SE_M_SUPERSONIC}tha{SE_M_SPIT_UP}wa{SE_M_GRASSWHISTLE}{SE_M_CHARGE}goo{SE_M_WATERFALL}cry!$"

GoldenrodCity_Gym_Text_WhitneyRematch:
	.string "Hi{SE_M_DRAGON_RAGE}It'{SE_M_GRASSWHISTLE}you!\p"
	.string "Wow{SE_M_SUPERSONIC}JOHT{SE_M_SOLAR_BEAM}CHAMPIO{SE_M_PSYBEAM2}now?\p"
	.string "Yo{SE_M_DIVE}reall{SE_M_YAWN}ar{SE_M_REVERSAL}amazing!\p"
	.string "{SE_M_HEAL_BELL}wan{SE_M_SPIT_UP}t{SE_M_ATTRACT2}se{SE_M_REVERSAL}ho{SE_M_TWISTER}stron{SE_M_SANDSTORM}yo{SE_M_DIVE}are.\p"
	.string "Wan{SE_M_SPIT_UP}t{SE_M_ATTRACT2}hav{SE_M_REVERSAL}{SE_M_CHARGE}rematc{SE_M_TRI_ATTACK}wit{SE_M_TRI_ATTACK}me?$"

GoldenrodCity_Gym_Text_WhitneyRematchDefeat:
	.string "Waaaaah!\p"
	.string "Waaaaah!\p"
	.string "…Snivel{SE_M_SUPERSONIC}hic{SE_M_DIZZY_PUNCH}…Yo{SE_M_DIVE}meanie!$"

GoldenrodCity_Gym_Text_LassCarrieSeen:
	.string "Don'{SE_M_SPIT_UP}le{SE_M_SPIT_UP}m{SE_M_YAWN}POKéMON'{SE_M_GRASSWHISTLE}cut{SE_M_REVERSAL}looks\n"
	.string "foo{SE_M_BATON_PASS}you.\p"
	.string "The{SE_M_YAWN}ca{SE_M_ATTRACT}whi{SE_M_MORNING_SUN}you!$"

GoldenrodCity_Gym_Text_LassCarrieBeaten:
	.string "Darn{SE_M_DIZZY_PUNCH}{SE_M_HEAL_BELL}though{SE_M_SPIT_UP}yo{SE_M_DIVE}wer{SE_M_REVERSAL}weak…$"

GoldenrodCity_Gym_Text_LassCarrieAfter:
	.string "D{SE_M_ATTRACT2}m{SE_M_YAWN}POKéMO{SE_M_PSYBEAM2}thin{SE_M_ENCORE2}I'{SE_M_MILK_DRINK}cute?$"

GoldenrodCity_Gym_Text_LassBridgetSeen:
	.string "{SE_M_HEAL_BELL}lik{SE_M_REVERSAL}cut{SE_M_REVERSAL}POKéMO{SE_M_PSYBEAM2}bette{SE_M_SAND_TOMB}than\n"
	.string "stron{SE_M_SANDSTORM}POKéMON.\p"
	.string "Bu{SE_M_SPIT_UP}{SE_M_HEAL_BELL}hav{SE_M_REVERSAL}stron{SE_M_SANDSTORM}an{SE_M_WATERFALL}cut{SE_M_REVERSAL}POKéMON!$"

GoldenrodCity_Gym_Text_LassBridgetBeaten:
	.string "Oh{SE_M_SUPERSONIC}no{SE_M_SUPERSONIC}no{SE_M_SUPERSONIC}no!$"

GoldenrodCity_Gym_Text_LassBridgetAfter:
	.string "I'{SE_M_MILK_DRINK}tryin{SE_M_SANDSTORM}t{SE_M_ATTRACT2}bea{SE_M_SPIT_UP}WHITNEY{SE_M_SUPERSONIC}but…\n"
	.string "It'{SE_M_GRASSWHISTLE}depressing.\p"
	.string "I'{SE_M_MILK_DRINK}okay{SE_M_DRAGON_RAGE}I{SE_M_ACID_ARMOR}{SE_M_HEAL_BELL}lose{SE_M_SUPERSONIC}I'l{SE_M_BATON_PASS}jus{SE_M_SPIT_UP}try\n"
	.string "harde{SE_M_SAND_TOMB}nex{SE_M_SPIT_UP}time!$"

GoldenrodCity_Gym_Text_BridgetWhitneyCries:
	.string "Oh{SE_M_SUPERSONIC}no{SE_M_PERISH_SONG}Yo{SE_M_DIVE}mad{SE_M_REVERSAL}WHITNE{SE_M_MOONLIGHT}cry.\p"
	.string "It'{SE_M_GRASSWHISTLE}OK{SE_M_PERISH_SONG}She'l{SE_M_BATON_PASS}sto{SE_M_MORNING_SUN}soon{SE_M_PERISH_SONG}She\n"
	.string "alway{SE_M_GRASSWHISTLE}crie{SE_M_GRASSWHISTLE}whe{SE_M_ATTRACT}sh{SE_M_REVERSAL}loses.$"

GoldenrodCity_Gym_Text_BeautyVictoriaSeen:
	.string "Oh{SE_M_SUPERSONIC}yo{SE_M_DIVE}ar{SE_M_REVERSAL}{SE_M_CHARGE}cut{SE_M_REVERSAL}littl{SE_M_REVERSAL}trainer!\p"
	.string "{SE_M_HEAL_BELL}lik{SE_M_REVERSAL}you{SE_M_SUPERSONIC}bu{SE_M_SPIT_UP}{SE_M_HEAL_BELL}won'{SE_M_SPIT_UP}hol{SE_M_WATERFALL}back!$"

GoldenrodCity_Gym_Text_BeautyVictoriaBeaten:
	.string "Let'{SE_M_GRASSWHISTLE}see{SE_M_DIZZY_PUNCH}Oops{SE_M_SUPERSONIC}it'{SE_M_GRASSWHISTLE}over?$"

GoldenrodCity_Gym_Text_BeautyVictoriaAfter:
	.string "Wow{SE_M_SUPERSONIC}yo{SE_M_DIVE}mus{SE_M_SPIT_UP}b{SE_M_REVERSAL}goo{SE_M_WATERFALL}t{SE_M_ATTRACT2}bea{SE_M_SPIT_UP}me!\n"
	.string "Kee{SE_M_MORNING_SUN}i{SE_M_SPIT_UP}up!$"

GoldenrodCity_Gym_Text_BeautySamanthaSeen:
	.string "Giv{SE_M_REVERSAL}i{SE_M_SPIT_UP}you{SE_M_SAND_TOMB}bes{SE_M_SPIT_UP}shot{SE_M_SUPERSONIC}o{SE_M_SAND_TOMB}I'l{SE_M_BATON_PASS}take\n"
	.string "yo{SE_M_DIVE}down!$"

GoldenrodCity_Gym_Text_BeautySamanthaBeaten:
	.string "No{SE_M_DRAGON_RAGE}Oh{SE_M_SUPERSONIC}MEOWTH{SE_M_SUPERSONIC}I'{SE_M_MILK_DRINK}s{SE_M_ATTRACT2}sorry!$"

GoldenrodCity_Gym_Text_BeautySamanthaAfter:
	.string "{SE_M_HEAL_BELL}taugh{SE_M_SPIT_UP}MEOWT{SE_M_SWAGGER2}move{SE_M_GRASSWHISTLE}fo{SE_M_SAND_TOMB}takin{SE_M_SANDSTORM}on\n"
	.string "an{SE_M_YAWN}type…$"

GoldenrodCity_Gym_Text_GymGuide:
	.string "Yo{SE_M_DRAGON_RAGE}CHAM{SE_M_PETAL_DANCE}i{SE_M_ATTRACT}making!\p"
	.string "Thi{SE_M_GRASSWHISTLE}GY{SE_M_GIGA_DRAIN}i{SE_M_GRASSWHISTLE}hom{SE_M_REVERSAL}t{SE_M_ATTRACT2}WHITNEY{SE_M_SUPERSONIC}the\n"
	.string "maste{SE_M_SAND_TOMB}o{SE_M_ACID_ARMOR}NORMAL-typ{SE_M_REVERSAL}POKéMON.\p"
	.string "B{SE_M_REVERSAL}cautiou{SE_M_GRASSWHISTLE}o{SE_M_ACID_ARMOR}he{SE_M_SAND_TOMB}cut{SE_M_REVERSAL}team.\p"
	.string "Som{SE_M_REVERSAL}o{SE_M_ACID_ARMOR}th{SE_M_REVERSAL}POKéMO{SE_M_PSYBEAM2}i{SE_M_ATTRACT}thi{SE_M_GRASSWHISTLE}gym\n"
	.string "hav{SE_M_REVERSAL}th{SE_M_REVERSAL}newl{SE_M_YAWN}discovere{SE_M_WATERFALL}FAIRY\l"
	.string "typ{SE_M_REVERSAL}a{SE_M_GRASSWHISTLE}well.\p"
	.string "Chec{SE_M_ENCORE2}ROUT{SE_M_SWORDS_DANCE}3{SE_M_WHIRLPOOL}i{SE_M_ACID_ARMOR}yo{SE_M_DIVE}nee{SE_M_WATERFALL}a\n"
	.string "FIGHTING-typ{SE_M_REVERSAL}o{SE_M_SAND_TOMB}POISON-type.$"

GoldenrodCity_Gym_Text_GymGuideWin:
	.string "Yo{SE_M_DIVE}won{SE_M_SING}Great{SE_M_DRAGON_RAGE}{SE_M_HEAL_BELL}wa{SE_M_GRASSWHISTLE}bus{SE_M_YAWN}admiring\n"
	.string "th{SE_M_REVERSAL}ladie{SE_M_GRASSWHISTLE}here.$"

