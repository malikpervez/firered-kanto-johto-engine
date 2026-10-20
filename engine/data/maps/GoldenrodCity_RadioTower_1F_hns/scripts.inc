@ Johto (data/maps/GoldenrodCity_RadioTower_1F_hns/scripts.inc), as built into the FireRed game.

GoldenrodCity_RadioTower_1F_hns_MapScripts::
	.byte 0

RadioTower1F_EventScript_Grunt::
	lock
	faceplayer
	msgbox RadioTower1F_Text_GruntM3Seen, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_JOHTO_GRUNT_2_HNS, RadioTower1F_Text_GruntM3Beaten
	msgbox RadioTower1F_Text_GruntM3After, MSGBOX_AUTOCLOSE
	turnobject LOCALID_GOLDENROD_RADIOTOWER_GRUNT, DIR_EAST
	applymovement2 LOCALID_GOLDENROD_RADIOTOWER_GRUNT, RadioTower1F_Movement_Rocket
	waitmovement 0
	playse SE_EXIT
	removeobject LOCALID_GOLDENROD_RADIOTOWER_GRUNT
	setflag JOHTO_FLAG_HIDE_ROCKET_GOLDENROD_RADIOTOWER_1
	release
	end

RadioTower1F_Movement_Rocket::
	walk_in_place_right
	step_end

RadioTower1F_EventScript_Lass::
	lock
	faceplayer
	msgbox RadioTower1F_Text_Lass, MSGBOX_DEFAULT
	call RB_RadioAftermath
	closemessage
	release
	end

RadioTower1F_EventScript_Youngster::
	lock
	faceplayer
	msgbox RadioTower1F_Text_Youngster, MSGBOX_DEFAULT
	closemessage
	release
	end

RadioTower1F_EventScript_Whitney::
	lock
	faceplayer
	msgbox RadioTower1F_Text_Whitney1, MSGBOX_DEFAULT
	closemessage
	turnobject LOCALID_GOLDENROD_RADIOTOWER_WHITNEY, DIR_SOUTH
	release
	end

RadioTower1F_Text_Whitney1::
	.string "WHITNEY{SE_M_HEAT_WAVE}Hi!\p"
	.string "M{SE_M_YAWN}nam{SE_M_REVERSAL}i{SE_M_GRASSWHISTLE}WHITNEY!\p"
	.string "{SE_M_HEAL_BELL}hear{SE_M_WATERFALL}abou{SE_M_SPIT_UP}th{SE_M_REVERSAL}QUI{SE_M_CHARM}t{SE_M_ATTRACT2}wi{SE_M_ATTRACT}a\n"
	.string "RADI{SE_M_SOLAR_BEAM}CARD{SE_M_SUPERSONIC}s{SE_M_ATTRACT2}{SE_M_HEAL_BELL}cam{SE_M_REVERSAL}her{SE_M_REVERSAL}t{SE_M_ATTRACT2}get\l"
	.string "one...\p"
	.string "Bu{SE_M_SPIT_UP}thi{SE_M_GRASSWHISTLE}QUI{SE_M_CHARM}i{SE_M_GRASSWHISTLE}s{SE_M_ATTRACT2}hard!$"

RadioTower1F_Text_Whitney2::
	.string "WHITNEY{SE_M_HEAT_WAVE}Wow{SE_M_SUPERSONIC}yo{SE_M_DIVE}di{SE_M_WATERFALL}it!\p"
	.string "{SE_M_HEAL_BELL}though{SE_M_SPIT_UP}th{SE_M_REVERSAL}answe{SE_M_SAND_TOMB}t{SE_M_ATTRACT2}th{SE_M_REVERSAL}third\n"
	.string "questio{SE_M_ATTRACT}wa{SE_M_GRASSWHISTLE}surel{SE_M_YAWN}apricorns!\l"
	.string "Oops!\p"
	.string "It'{SE_M_GRASSWHISTLE}tim{SE_M_REVERSAL}t{SE_M_ATTRACT2}g{SE_M_ATTRACT2}bac{SE_M_ENCORE2}t{SE_M_ATTRACT2}th{SE_M_REVERSAL}GYM!$"

RadioTower1F_EventScript_Reception::
	lock
	faceplayer
	msgbox RadioTower1F_Text_ReceptionistWelcome, MSGBOX_DEFAULT
	goto_if_unset JOHTO_FLAG_ENABLE_RADIO, RadioTower1F_EventScript_ReceptionOfferQuiz
	msgbox RadioTower1F_Text_ReceptionistNoTours, MSGBOX_DEFAULT
	closemessage
	release
	end

RadioTower1F_EventScript_ReceptionOfferQuiz::
	msgbox RadioTower1F_Text_RadioCardWomanOfferQuiz, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, TRUE, RadioTower1F_EventScript_ReceptionQuiz1
	msgbox RadioTower1F_Text_DeclineQuiz, MSGBOX_DEFAULT
	closemessage
	release
	end

RadioTower1F_EventScript_ReceptionQuiz1::
	msgbox RadioTower1F_Text_QuizQuestion1, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, TRUE, RadioTower1F_EventScript_ReceptionQuiz2
	msgbox RadioTower1F_Text_WrongAnswer, MSGBOX_DEFAULT
	closemessage
	release
	end

RadioTower1F_EventScript_ReceptionQuiz2::
	msgbox RadioTower1F_Text_QuizQuestion2, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, TRUE, RadioTower1F_EventScript_ReceptionQuiz3
	msgbox RadioTower1F_Text_WrongAnswer, MSGBOX_DEFAULT
	closemessage
	release
	end

RadioTower1F_EventScript_ReceptionQuiz3::
	msgbox RadioTower1F_Text_QuizQuestion3, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, FALSE, RadioTower1F_EventScript_ReceptionQuiz4
	msgbox RadioTower1F_Text_WrongAnswer, MSGBOX_DEFAULT
	closemessage
	release
	end

RadioTower1F_EventScript_ReceptionQuiz4::
	msgbox RadioTower1F_Text_QuizQuestion4, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, TRUE, RadioTower1F_EventScript_ReceptionQuiz5
	msgbox RadioTower1F_Text_WrongAnswer, MSGBOX_DEFAULT
	closemessage
	release
	end

RadioTower1F_EventScript_ReceptionQuiz5::
	msgbox RadioTower1F_Text_QuizQuestion5, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, FALSE, RadioTower1F_EventScript_ReceptionGiveRadio
	msgbox RadioTower1F_Text_WrongAnswer, MSGBOX_DEFAULT
	closemessage
	release
	end

RadioTower1F_EventScript_ReceptionGiveRadio::
	msgbox RadioTower1F_Text_QuizWin, MSGBOX_DEFAULT
	closemessage
	playfanfare MUS_RG_OBTAIN_KEY_ITEM
	msgbox RadioTower1F_Text_PokegearRadio, MSGBOX_AUTOCLOSE
	waitfanfare
	msgbox RadioTower1F_Text_TuneIn, MSGBOX_DEFAULT
	closemessage
	playse SE_PIN
	applymovement LOCALID_GOLDENROD_RADIOTOWER_WHITNEY, J_Common_Movement_ExclamationMark
	delay 55
	waitmovement LOCALID_GOLDENROD_RADIOTOWER_WHITNEY
	turnobject LOCALID_GOLDENROD_RADIOTOWER_WHITNEY, DIR_EAST
	delay 20
	turnobject OBJ_EVENT_ID_PLAYER, DIR_WEST
	msgbox RadioTower1F_Text_Whitney2, MSGBOX_DEFAULT
	closemessage
	applymovement2 LOCALID_GOLDENROD_RADIOTOWER_WHITNEY, GoldenrodCity_RadioTower_4F_Movement_WhitneyLeave
	waitmovement 0
	playse SE_EXIT
	removeobject LOCALID_GOLDENROD_RADIOTOWER_WHITNEY
	setflag JOHTO_FLAG_ENABLE_RADIO
	setflag JOHTO_FLAG_HIDE_GOLDENROD_BEAUTY
	setvar JOHTO_VAR_GOLDENROD_CITY_STATE, 2
	release
	end

GoldenrodCity_RadioTower_4F_Movement_WhitneyLeave:
	face_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_down
	walk_down
	walk_in_place_down
	step_end

GoldenrodCity_RadioTower_1F_EventScript_Sign::
	lock
	msgbox RadioTower1F_Text_Directory, MSGBOX_SIGN
	closemessage
	release
	end

RadioTower1F_Text_ReceptionistWelcome:
	.string "Welcome!$"

RadioTower1F_Text_ReceptionistNoTours:
	.string "Hello{SE_M_PERISH_SONG}I'{SE_M_MILK_DRINK}sorry{SE_M_SUPERSONIC}bu{SE_M_SPIT_UP}we'r{SE_M_REVERSAL}not\n"
	.string "offerin{SE_M_SANDSTORM}an{SE_M_YAWN}tour{SE_M_GRASSWHISTLE}today.$"

RadioTower1F_Text_RadioCardWomanOfferQuiz:
	.string "W{SE_M_REVERSAL}hav{SE_M_REVERSAL}{SE_M_CHARGE}specia{SE_M_BATON_PASS}QUI{SE_M_CHARM}campaig{SE_M_ATTRACT}on\n"
	.string "righ{SE_M_SPIT_UP}now.\p"
	.string "Answe{SE_M_SAND_TOMB}fiv{SE_M_REVERSAL}question{SE_M_GRASSWHISTLE}correctl{SE_M_YAWN}to\n"
	.string "wi{SE_M_ATTRACT}{SE_M_CHARGE}POKéGEA{SE_M_MINIMIZE}RADI{SE_M_SOLAR_BEAM}CARD.\p"
	.string "Yo{SE_M_DIVE}an{SE_M_WATERFALL}you{SE_M_SAND_TOMB}POKéMO{SE_M_PSYBEAM2}ca{SE_M_ATTRACT}us{SE_M_REVERSAL}i{SE_M_SPIT_UP}to\n"
	.string "pla{SE_M_YAWN}musi{SE_M_HYPER_BEAM}anytime{SE_M_SUPERSONIC}anywhere.\p"
	.string "Woul{SE_M_WATERFALL}yo{SE_M_DIVE}lik{SE_M_REVERSAL}t{SE_M_ATTRACT2}tak{SE_M_REVERSAL}th{SE_M_REVERSAL}QUIZ?$"

RadioTower1F_Text_QuizQuestion1:
	.string "Questio{SE_M_ATTRACT}1:\p"
	.string "I{SE_M_GRASSWHISTLE}ther{SE_M_REVERSAL}{SE_M_CHARGE}POKéMO{SE_M_PSYBEAM2}tha{SE_M_SPIT_UP}appear{SE_M_GRASSWHISTLE}only\n"
	.string "i{SE_M_ATTRACT}th{SE_M_REVERSAL}daytime?$"

RadioTower1F_Text_QuizQuestion2:
	.string "Correct!\n"
	.string "Questio{SE_M_ATTRACT}2:\p"
	.string "I{SE_M_GRASSWHISTLE}thi{SE_M_GRASSWHISTLE}statemen{SE_M_SPIT_UP}correct?\p"
	.string "Yo{SE_M_DIVE}can'{SE_M_SPIT_UP}bu{SE_M_YAWN}{SE_M_CHARGE}BERR{SE_M_MOONLIGHT}a{SE_M_SPIT_UP}{SE_M_CHARGE}MART.$"

RadioTower1F_Text_QuizQuestion3:
	.string "Bull's-eye!\n"
	.string "Questio{SE_M_ATTRACT}3:\p"
	.string "KURT{SE_M_SUPERSONIC}th{SE_M_REVERSAL}POKéBAL{SE_M_BRICK_BREAK}creator{SE_M_SUPERSONIC}uses\n"
	.string "apricorn{SE_M_GRASSWHISTLE}a{SE_M_GRASSWHISTLE}ingredients?$"

RadioTower1F_Text_QuizQuestion4:
	.string "S{SE_M_ATTRACT2}fa{SE_M_SAND_TOMB}s{SE_M_ATTRACT2}good!\n"
	.string "Questio{SE_M_ATTRACT}4:\p"
	.string "I{SE_M_GRASSWHISTLE}FALKNE{SE_M_MINIMIZE}th{SE_M_REVERSAL}VIOLE{SE_M_SWIFT}GY{SE_M_GIGA_DRAIN}LEADER\n"
	.string "wh{SE_M_ATTRACT2}use{SE_M_GRASSWHISTLE}bir{SE_M_WATERFALL}POKéMON?$"

RadioTower1F_Text_QuizQuestion5:
	.string "Wow{SE_M_DRAGON_RAGE}Righ{SE_M_SPIT_UP}again!\n"
	.string "Here'{SE_M_GRASSWHISTLE}th{SE_M_REVERSAL}fina{SE_M_BATON_PASS}question:\p"
	.string "D{SE_M_ATTRACT2}GOLDENRO{SE_M_FAINT_ATTACK}GAM{SE_M_SWORDS_DANCE}CORNER'{SE_M_GRASSWHISTLE}slots\n"
	.string "hav{SE_M_REVERSAL}CHARMANDE{SE_M_MINIMIZE}o{SE_M_ATTRACT}thei{SE_M_SAND_TOMB}reels?$"

RadioTower1F_Text_QuizWin:
	.string "Bingo{SE_M_DRAGON_RAGE}Yo{SE_M_DIVE}go{SE_M_SPIT_UP}it!\n"
	.string "Congratulations!\p"
	.string "Here'{SE_M_GRASSWHISTLE}you{SE_M_SAND_TOMB}prize{SE_M_SUPERSONIC}{SE_M_CHARGE}RADI{SE_M_SOLAR_BEAM}CARD!$"

RadioTower1F_Text_PokegearRadio:
	.string "{PLAYER}'{SE_M_GRASSWHISTLE}POKéGEA{SE_M_MINIMIZE}ca{SE_M_ATTRACT}no{SE_M_TWISTER}doubl{SE_M_REVERSAL}as\n"
	.string "{SE_M_CHARGE}RADIO!$"

RadioTower1F_Text_TuneIn:
	.string "Pleas{SE_M_REVERSAL}tun{SE_M_REVERSAL}i{SE_M_ATTRACT}t{SE_M_ATTRACT2}ou{SE_M_SAND_TOMB}RADI{SE_M_SOLAR_BEAM}shows.$"

RadioTower1F_Text_WrongAnswer:
	.string "Oh{SE_M_SUPERSONIC}dear.\n"
	.string "Sorry{SE_M_SUPERSONIC}bu{SE_M_SPIT_UP}yo{SE_M_DIVE}go{SE_M_SPIT_UP}i{SE_M_SPIT_UP}wrong.\p"
	.string "Pleas{SE_M_REVERSAL}tr{SE_M_YAWN}again!$"

RadioTower1F_Text_DeclineQuiz:
	.string "Oh{SE_M_PERISH_SONG}{SE_M_HEAL_BELL}see{SE_M_PERISH_SONG}Pleas{SE_M_REVERSAL}se{SE_M_REVERSAL}m{SE_M_REVERSAL}i{SE_M_ACID_ARMOR}you\n"
	.string "chang{SE_M_REVERSAL}you{SE_M_SAND_TOMB}mind.$"

RadioTower1F_Text_Lass:
	.string "BE{SE_M_PSYBEAM2}i{SE_M_GRASSWHISTLE}{SE_M_CHARGE}fabulou{SE_M_GRASSWHISTLE}DJ.\p"
	.string "Hi{SE_M_GRASSWHISTLE}swee{SE_M_SPIT_UP}voic{SE_M_REVERSAL}make{SE_M_GRASSWHISTLE}m{SE_M_REVERSAL}melt!$"

RadioTower1F_Text_Youngster:
	.string "{SE_M_HEAL_BELL}lov{SE_M_REVERSAL}MARY{SE_M_SUPERSONIC}fro{SE_M_MILK_DRINK}POKéMO{SE_M_PSYBEAM2}TALK.\p"
	.string "{SE_M_HEAL_BELL}onl{SE_M_YAWN}kno{SE_M_TWISTER}wha{SE_M_SPIT_UP}sh{SE_M_REVERSAL}sound{SE_M_GRASSWHISTLE}like,\n"
	.string "though.$"

RadioTower1F_Text_GruntM3Seen:
	.string "We'v{SE_M_REVERSAL}finall{SE_M_YAWN}take{SE_M_ATTRACT}ove{SE_M_SAND_TOMB}the\n"
	.string "RADI{SE_M_SOLAR_BEAM}TOWER!\p"
	.string "No{SE_M_TWISTER}everyon{SE_M_REVERSAL}wil{SE_M_BATON_PASS}ge{SE_M_SPIT_UP}t{SE_M_ATTRACT2}experience\n"
	.string "th{SE_M_REVERSAL}tru{SE_M_REVERSAL}terro{SE_M_SAND_TOMB}o{SE_M_ACID_ARMOR}TEA{SE_M_GIGA_DRAIN}ROCKET!\p"
	.string "We'l{SE_M_BATON_PASS}sho{SE_M_TWISTER}yo{SE_M_DIVE}ho{SE_M_TWISTER}scar{SE_M_YAWN}w{SE_M_REVERSAL}are!$"

RadioTower1F_Text_GruntM3Beaten:
	.string "To{SE_M_ATTRACT2}strong{SE_M_DRAGON_RAGE}I'{SE_M_MILK_DRINK}sorr{SE_M_YAWN}boss…$"

RadioTower1F_Text_GruntM3After:
	.string "You'r{SE_M_REVERSAL}to{SE_M_ATTRACT2}strong.\p"
	.string "Ou{SE_M_SAND_TOMB}pla{SE_M_ATTRACT}coul{SE_M_WATERFALL}b{SE_M_REVERSAL}ruined{SE_M_PERISH_SONG}{SE_M_HEAL_BELL}must\n"
	.string "war{SE_M_ATTRACT}th{SE_M_REVERSAL}others…$"

RadioTower1F_Text_Directory:
	.string "1{SE_M_LEER}RECEPTION\n"
	.string "2{SE_M_LEER}SALES\p"
	.string "3{SE_M_LEER}PERSONNEL\n"
	.string "4{SE_M_LEER}PRODUCTION\p"
	.string "5{SE_M_LEER}DIRECTOR'{SE_M_SKETCH}OFFICE$"

RadioTower1F_Text_GotRadio:
	.string "{PLAYER} go{SE_M_SPIT_UP}th{SE_M_REVERSAL}RADI{SE_M_SOLAR_BEAM}CARD\n"
	.string "fo{SE_M_SAND_TOMB}th{SE_M_REVERSAL}POKéGEAR!$"

GoldenrodCity_RadioTower_1F_EventScript_LotteryClerk::
	lock
	faceplayer
	dotimebasedevents
	goto_if_ne JOHTO_VAR_POKELOT_PRIZE_ITEM, ITEM_NONE, GoldenrodCity_RadioTower_1F_EventScript_GivePrizeFromEarlier
	goto_if_set JOHTO_FLAG_DAILY_PICKED_LOTO_TICKET, GoldenrodCity_RadioTower_1F_EventScript_ComeBackTomorrow
	msgbox GoldenrodCity_RadioTower_1F_Text_LotteryCornerDrawTicket, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, GoldenrodCity_RadioTower_1F_EventScript_PleaseVisitAgain
	setflag JOHTO_FLAG_DAILY_PICKED_LOTO_TICKET
	message GoldenrodCity_RadioTower_1F_Text_PleasePickTicket
	waitmessage
	special RetrieveLotteryNumber
	copyvar VAR_0x8008, VAR_RESULT
	special BufferLottoTicketNumber
	msgbox GoldenrodCity_RadioTower_1F_Text_TicketNumberIsXPleaseWait, MSGBOX_DEFAULT
	applymovement 4, J_Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	playse SE_PC_ON
	special PickLotteryCornerTicket
	applymovement 4, J_Common_Movement_FacePlayer
	waitmovement 0
	goto_if_eq VAR_0x8004, 0, GoldenrodCity_RadioTower_1F_EventScript_NoMatch
	incrementgamestat GAME_STAT_WON_POKEMON_LOTTERY
	call_if_eq VAR_0x8006, 0, GoldenrodCity_RadioTower_1F_EventScript_TicketMatchPartyMon
	call_if_eq VAR_0x8006, 1, GoldenrodCity_RadioTower_1F_EventScript_TicketMatchPCMon
	bufferitemname STR_VAR_1, VAR_0x8005
	call_if_eq VAR_0x8004, 1, GoldenrodCity_RadioTower_1F_EventScript_TwoDigitMatch
	call_if_eq VAR_0x8004, 2, GoldenrodCity_RadioTower_1F_EventScript_ThreeDigitMatch
	call_if_eq VAR_0x8004, 3, GoldenrodCity_RadioTower_1F_EventScript_FourDigitMatch
	call_if_eq VAR_0x8004, 4, GoldenrodCity_RadioTower_1F_EventScript_FullMatch
	giveitem VAR_0x8005
	goto_if_eq VAR_RESULT, FALSE, GoldenrodCity_RadioTower_1F_EventScript_RecordPrizeNoRoom
	special TryPutLotteryWinnerReportOnAir
	goto GoldenrodCity_RadioTower_1F_EventScript_PleaseVisitAgain2
	end

GoldenrodCity_RadioTower_1F_EventScript_TicketMatchPartyMon::
	msgbox GoldenrodCity_RadioTower_1F_Text_TicketMatchesPartyMon, MSGBOX_DEFAULT
	return

GoldenrodCity_RadioTower_1F_EventScript_TicketMatchPCMon::
	msgbox GoldenrodCity_RadioTower_1F_Text_TicketMatchesPCMon, MSGBOX_DEFAULT
	return

GoldenrodCity_RadioTower_1F_EventScript_ComeBackTomorrow::
	msgbox GoldenrodCity_RadioTower_1F_Text_ComeBackTomorrow, MSGBOX_DEFAULT
	release
	end

GoldenrodCity_RadioTower_1F_EventScript_PleaseVisitAgain::
	msgbox GoldenrodCity_RadioTower_1F_Text_PleaseVisitAgain, MSGBOX_DEFAULT
	release
	end

GoldenrodCity_RadioTower_1F_EventScript_NoMatch::
	msgbox GoldenrodCity_RadioTower_1F_Text_NoNumbersMatched, MSGBOX_DEFAULT
	goto GoldenrodCity_RadioTower_1F_EventScript_PleaseVisitAgain2
	end

GoldenrodCity_RadioTower_1F_EventScript_PleaseVisitAgain2::
	msgbox GoldenrodCity_RadioTower_1F_Text_PleaseVisitAgain2, MSGBOX_DEFAULT
	release
	end

GoldenrodCity_RadioTower_1F_EventScript_TwoDigitMatch::
	msgbox GoldenrodCity_RadioTower_1F_Text_TwoDigitsMatched, MSGBOX_DEFAULT
	return

GoldenrodCity_RadioTower_1F_EventScript_ThreeDigitMatch::
	msgbox GoldenrodCity_RadioTower_1F_Text_ThreeDigitsMatched, MSGBOX_DEFAULT
	return

GoldenrodCity_RadioTower_1F_EventScript_FourDigitMatch::
	msgbox GoldenrodCity_RadioTower_1F_Text_FourDigitsMatched, MSGBOX_DEFAULT
	return

GoldenrodCity_RadioTower_1F_EventScript_FullMatch::
	msgbox GoldenrodCity_RadioTower_1F_Text_AllFiveDigitsMatched, MSGBOX_DEFAULT
	return

GoldenrodCity_RadioTower_1F_EventScript_RecordPrizeNoRoom::
	copyvar JOHTO_VAR_POKELOT_PRIZE_PLACE, VAR_0x8004
	copyvar JOHTO_VAR_POKELOT_PRIZE_ITEM, VAR_0x8005
	goto GoldenrodCity_RadioTower_1F_EventScript_NoRoomForPrize
	end

GoldenrodCity_RadioTower_1F_EventScript_NoRoomForPrize::
	msgbox GoldenrodCity_RadioTower_1F_Text_NoRoomForThis, MSGBOX_DEFAULT
	release
	end

GoldenrodCity_RadioTower_1F_EventScript_GivePrizeFromEarlier::
	msgbox GoldenrodCity_RadioTower_1F_Text_PrizeWeveBeenHolding, MSGBOX_DEFAULT
	giveitem JOHTO_VAR_POKELOT_PRIZE_ITEM
	goto_if_eq VAR_RESULT, FALSE, GoldenrodCity_RadioTower_1F_EventScript_NoRoomForPrize
	copyvar VAR_0x8004, JOHTO_VAR_POKELOT_PRIZE_PLACE
	copyvar VAR_0x8005, JOHTO_VAR_POKELOT_PRIZE_ITEM
	special TryPutLotteryWinnerReportOnAir
	setvar JOHTO_VAR_POKELOT_PRIZE_ITEM, ITEM_NONE
	setvar JOHTO_VAR_POKELOT_PRIZE_PLACE, 0
	release
	end

GoldenrodCity_RadioTower_1F_Text_LotteryCornerDrawTicket:
	.string "Thi{SE_M_GRASSWHISTLE}i{SE_M_GRASSWHISTLE}th{SE_M_REVERSAL}POKéMO{SE_M_PSYBEAM2}LOTTER{SE_M_MOONLIGHT}CORNER.\p"
	.string "I{SE_M_ACID_ARMOR}th{SE_M_REVERSAL}LOT{SE_M_SOLAR_BEAM}TICKET'{SE_M_GRASSWHISTLE}numbe{SE_M_SAND_TOMB}matches\n"
	.string "th{SE_M_REVERSAL}I{SE_M_FAINT_ATTACK}numbe{SE_M_SAND_TOMB}o{SE_M_ACID_ARMOR}an{SE_M_YAWN}o{SE_M_ACID_ARMOR}you{SE_M_SAND_TOMB}POKéMON,\l"
	.string "yo{SE_M_DIVE}wil{SE_M_BATON_PASS}receiv{SE_M_REVERSAL}{SE_M_CHARGE}fabulou{SE_M_GRASSWHISTLE}gift.\p"
	.string "Woul{SE_M_WATERFALL}yo{SE_M_DIVE}lik{SE_M_REVERSAL}t{SE_M_ATTRACT2}dra{SE_M_TWISTER}{SE_M_CHARGE}POKéMON\n"
	.string "LOT{SE_M_SOLAR_BEAM}TICKET?$"

GoldenrodCity_RadioTower_1F_Text_ComeBackTomorrow:
	.string "Pleas{SE_M_REVERSAL}com{SE_M_REVERSAL}bac{SE_M_ENCORE2}tomorrow.$"

GoldenrodCity_RadioTower_1F_Text_PleaseVisitAgain:
	.string "Pleas{SE_M_REVERSAL}d{SE_M_ATTRACT2}visi{SE_M_SPIT_UP}again.$"

GoldenrodCity_RadioTower_1F_Text_PleasePickTicket:
	.string "Pleas{SE_M_REVERSAL}pic{SE_M_ENCORE2}{SE_M_CHARGE}LOT{SE_M_SOLAR_BEAM}TICKET.\n"
	.string "…{PAUSE}Ô{PAUSE}Ô{PAUSE}Ô{PAUSE}Ô…{PAUSE}Ô{PAUSE}Ô{PAUSE}Ô{PAUSE}Ô…{PAUSE}Ô{PAUSE}Ô{PAUSE}Ô{PAUSE}Ô$"

GoldenrodCity_RadioTower_1F_Text_TicketNumberIsXPleaseWait:
	.string "Th{SE_M_REVERSAL}LOT{SE_M_SOLAR_BEAM}TICKE{SE_M_SWIFT}numbe{SE_M_SAND_TOMB}i{SE_M_GRASSWHISTLE}{STR_VAR_1}.\p"
	.string "{SE_M_HEAL_BELL}nee{SE_M_WATERFALL}t{SE_M_ATTRACT2}ru{SE_M_ATTRACT}{SE_M_CHARGE}chec{SE_M_ENCORE2}o{SE_M_ATTRACT}thi{SE_M_GRASSWHISTLE}number\n"
	.string "t{SE_M_ATTRACT2}se{SE_M_REVERSAL}i{SE_M_ACID_ARMOR}i{SE_M_SPIT_UP}matche{SE_M_GRASSWHISTLE}an{SE_M_YAWN}o{SE_M_ACID_ARMOR}your\l"
	.string "POKéMON'{SE_M_GRASSWHISTLE}I{SE_M_FAINT_ATTACK}numbers{SE_M_PERISH_SONG}Pleas{SE_M_REVERSAL}wait.$"

GoldenrodCity_RadioTower_1F_Text_TicketMatchesPartyMon:
	.string "Congratulations!\p"
	.string "Th{SE_M_REVERSAL}I{SE_M_FAINT_ATTACK}numbe{SE_M_SAND_TOMB}o{SE_M_ACID_ARMOR}you{SE_M_SAND_TOMB}team's\n"
	.string "{STR_VAR_1} matche{SE_M_GRASSWHISTLE}your\l"
	.string "LOT{SE_M_SOLAR_BEAM}TICKET'{SE_M_GRASSWHISTLE}number!$"

GoldenrodCity_RadioTower_1F_Text_TicketMatchesPCMon:
	.string "Congratulations!\p"
	.string "Th{SE_M_REVERSAL}I{SE_M_FAINT_ATTACK}numbe{SE_M_SAND_TOMB}o{SE_M_ACID_ARMOR}you{SE_M_SAND_TOMB}PC-boxed\n"
	.string "{STR_VAR_1} matche{SE_M_GRASSWHISTLE}your\l"
	.string "LOT{SE_M_SOLAR_BEAM}TICKET'{SE_M_GRASSWHISTLE}number!$"

GoldenrodCity_RadioTower_1F_Text_NoNumbersMatched:
	.string "I'{SE_M_MILK_DRINK}sorry.\n"
	.string "Non{SE_M_REVERSAL}o{SE_M_ACID_ARMOR}th{SE_M_REVERSAL}number{SE_M_GRASSWHISTLE}matched.$"

GoldenrodCity_RadioTower_1F_Text_TwoDigitsMatched:
	.string "Tw{SE_M_ATTRACT2}digit{SE_M_GRASSWHISTLE}matched{SE_M_SUPERSONIC}s{SE_M_ATTRACT2}yo{SE_M_DIVE}wi{SE_M_ATTRACT}the\n"
	.string "thir{SE_M_WATERFALL}prize!\l"
	.string "You'v{SE_M_REVERSAL}wo{SE_M_ATTRACT}th{SE_M_REVERSAL}{STR_VAR_1}!$"

GoldenrodCity_RadioTower_1F_Text_ThreeDigitsMatched:
	.string "Thre{SE_M_REVERSAL}digit{SE_M_GRASSWHISTLE}matched{SE_M_SUPERSONIC}s{SE_M_ATTRACT2}yo{SE_M_DIVE}wi{SE_M_ATTRACT}the\n"
	.string "secon{SE_M_WATERFALL}prize!\l"
	.string "You'v{SE_M_REVERSAL}wo{SE_M_ATTRACT}th{SE_M_REVERSAL}{STR_VAR_1}!$"

GoldenrodCity_RadioTower_1F_Text_FourDigitsMatched:
	.string "Fou{SE_M_SAND_TOMB}digit{SE_M_GRASSWHISTLE}matched{SE_M_SUPERSONIC}s{SE_M_ATTRACT2}yo{SE_M_DIVE}wi{SE_M_ATTRACT}the\n"
	.string "firs{SE_M_SPIT_UP}prize!\l"
	.string "You'v{SE_M_REVERSAL}wo{SE_M_ATTRACT}th{SE_M_REVERSAL}{STR_VAR_1}!$"

GoldenrodCity_RadioTower_1F_Text_AllFiveDigitsMatched:
	.string "Oh{SE_M_SUPERSONIC}m{SE_M_YAWN}goodness{SE_M_SUPERSONIC}al{SE_M_BATON_PASS}fiv{SE_M_REVERSAL}digits\n"
	.string "matched!\p"
	.string "You'v{SE_M_REVERSAL}wo{SE_M_ATTRACT}th{SE_M_REVERSAL}jackpo{SE_M_SPIT_UP}prize!\n"
	.string "You'v{SE_M_REVERSAL}wo{SE_M_ATTRACT}th{SE_M_REVERSAL}{STR_VAR_1}!$"

GoldenrodCity_RadioTower_1F_Text_NoRoomForThis:
	.string "Oh?\n"
	.string "Yo{SE_M_DIVE}see{SE_M_MILK_DRINK}t{SE_M_ATTRACT2}hav{SE_M_REVERSAL}n{SE_M_ATTRACT2}roo{SE_M_MILK_DRINK}fo{SE_M_SAND_TOMB}this.\p"
	.string "Pleas{SE_M_REVERSAL}mak{SE_M_REVERSAL}roo{SE_M_MILK_DRINK}i{SE_M_ATTRACT}you{SE_M_SAND_TOMB}BA{SE_M_SWAGGER}and\n"
	.string "le{SE_M_SPIT_UP}m{SE_M_REVERSAL}know.$"

GoldenrodCity_RadioTower_1F_Text_PrizeWeveBeenHolding:
	.string "{PLAYER}?\n"
	.string "Yes{SE_M_SUPERSONIC}I'v{SE_M_REVERSAL}bee{SE_M_ATTRACT}expectin{SE_M_SANDSTORM}you.\p"
	.string "Thi{SE_M_GRASSWHISTLE}i{SE_M_GRASSWHISTLE}th{SE_M_REVERSAL}priz{SE_M_REVERSAL}we'v{SE_M_REVERSAL}bee{SE_M_ATTRACT}holding\n"
	.string "fo{SE_M_SAND_TOMB}you.$"

GoldenrodCity_RadioTower_1F_Text_PleaseVisitAgain2:
	.string "Pleas{SE_M_REVERSAL}d{SE_M_ATTRACT2}visi{SE_M_SPIT_UP}again.$"

