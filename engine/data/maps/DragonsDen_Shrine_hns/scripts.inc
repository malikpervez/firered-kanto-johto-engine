@ Johto (data/maps/DragonsDen_Shrine_hns/scripts.inc), as built into the FireRed game.

DragonsDen_Shrine_hns_MapScripts::

	.byte 0

DragonsDen_Shrine_OnFrame::
	map_script_2 20550, 2, DragonsDen_Shrine_Trigger_ElderQuizTop
	.2byte 0

DragonsDen_Shrine_EventScript_Elder::
	lock
	faceplayer
	goto_if_ge 20550, 4, DragonsDen_Shrine_EventScript_ElderChooseDratini
	msgbox DragonsDen_Shrine_Text_ComeAgain, MSGBOX_DEFAULT
	release
	end

DragonsDen_Shrine_Trigger_ElderQuizLeft::
	lock
	applymovement2 255, DragonsDen_Shrine_Movement_PlayerWalkToElderLeft
	applymovement2 0xFE, DragonsDen_Shrine_Movement_MonWalkToElderLeft
	waitmovement 0xFE
	waitmovement 255
	delay 10
	lockall
	goto DragonsDen_Shrine_EventScript_ElderOfferQuiz

DragonsDen_Shrine_Trigger_ElderQuizTop::
	lock
	applymovement2 255, DragonsDen_Shrine_Movement_PlayerWalkToElderTop
	applymovement2 0xFE, DragonsDen_Shrine_Movement_PlayerWalkToElderTop
	waitmovement 0xFE
	waitmovement 255
	delay 10
	lockall
	goto DragonsDen_Shrine_EventScript_ElderOfferQuiz

DragonsDen_Shrine_Trigger_ElderQuizRight::
	lock
	applymovement2 255, DragonsDen_Shrine_Movement_PlayerWalkToElderRight
	applymovement2 0xFE, DragonsDen_Shrine_Movement_MonWalkToElderRight
	waitmovement 0xFE
	waitmovement 255
	delay 10
	lockall
	goto DragonsDen_Shrine_EventScript_ElderOfferQuiz

DragonsDen_Shrine_Movement_PlayerWalkToElderLeft:
	walk_up
	walk_right
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

DragonsDen_Shrine_Movement_MonWalkToElderLeft:
	walk_left
	walk_up
	walk_right
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

DragonsDen_Shrine_Movement_PlayerWalkToElderTop:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

DragonsDen_Shrine_Movement_PlayerWalkToElderRight:
	walk_up
	walk_left
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

DragonsDen_Shrine_Movement_MonWalkToElderRight:
	walk_right
	walk_up
	walk_left
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

DragonsDen_Shrine_EventScript_ElderOfferQuiz::
	msgbox DragonsDen_Shrine_Text_ElderGreeting, MSGBOX_DEFAULT
	setvar 20560, 0
	goto DragonsDen_Shrine_EventScript_ElderQuiz1

DragonsDen_Shrine_EventScript_ElderQuiz1::
	message DragonsDen_Shrine_Text_Question1
	multichoice 20, 6, 164, FALSE
	switch 32781
	case 0, DragonsDen_Shrine_EventScript_ElderQuiz1Correct
	case 2, DragonsDen_Shrine_EventScript_ElderQuiz1Correct
	case 127, DragonsDen_Shrine_EventScript_ElderQuiz1
	call DragonsDen_Shrine_EventScript_ElderWrong
	goto DragonsDen_Shrine_EventScript_ElderQuiz1

DragonsDen_Shrine_EventScript_ElderQuiz1Correct::
	msgbox DragonsDen_Shrine_Text_RightAnswer, MSGBOX_DEFAULT
	goto DragonsDen_Shrine_EventScript_ElderQuiz2

DragonsDen_Shrine_EventScript_ElderQuiz2::
	message DragonsDen_Shrine_Text_Question2
	multichoice 20, 6, 165, FALSE
	switch 32781
	case 0, DragonsDen_Shrine_EventScript_ElderQuiz2Correct
	case 1, DragonsDen_Shrine_EventScript_ElderQuiz2Correct
	case 127, DragonsDen_Shrine_EventScript_ElderQuiz2
	call DragonsDen_Shrine_EventScript_ElderWrong
	goto DragonsDen_Shrine_EventScript_ElderQuiz2

DragonsDen_Shrine_EventScript_ElderQuiz2Correct::
	msgbox DragonsDen_Shrine_Text_RightAnswer, MSGBOX_DEFAULT
	goto DragonsDen_Shrine_EventScript_ElderQuiz3

DragonsDen_Shrine_EventScript_ElderQuiz3::
	message DragonsDen_Shrine_Text_Question3
	multichoice 20, 6, 166, FALSE
	switch 32781
	case 1, DragonsDen_Shrine_EventScript_ElderQuiz3Correct
	case 2, DragonsDen_Shrine_EventScript_ElderQuiz3Correct
	case 127, DragonsDen_Shrine_EventScript_ElderQuiz3
	call DragonsDen_Shrine_EventScript_ElderWrong
	goto DragonsDen_Shrine_EventScript_ElderQuiz3

DragonsDen_Shrine_EventScript_ElderQuiz3Correct::
	msgbox DragonsDen_Shrine_Text_RightAnswer, MSGBOX_DEFAULT
	goto DragonsDen_Shrine_EventScript_ElderQuiz4

DragonsDen_Shrine_EventScript_ElderQuiz4::
	message DragonsDen_Shrine_Text_Question4
	multichoice 20, 6, 167, FALSE
	switch 32781
	case 0, DragonsDen_Shrine_EventScript_ElderQuiz4Correct
	case 2, DragonsDen_Shrine_EventScript_ElderQuiz4Correct
	case 127, DragonsDen_Shrine_EventScript_ElderQuiz4
	call DragonsDen_Shrine_EventScript_ElderWrong
	goto DragonsDen_Shrine_EventScript_ElderQuiz4

DragonsDen_Shrine_EventScript_ElderQuiz4Correct::
	msgbox DragonsDen_Shrine_Text_RightAnswer, MSGBOX_DEFAULT
	goto DragonsDen_Shrine_EventScript_ElderQuiz5

DragonsDen_Shrine_EventScript_ElderQuiz5::
	message DragonsDen_Shrine_Text_Question5
	multichoice 20, 6, 168, FALSE
	switch 32781
	case 2, DragonsDen_Shrine_EventScript_ElderQuizFinish
	case 127, DragonsDen_Shrine_EventScript_ElderQuiz5
	call DragonsDen_Shrine_EventScript_ElderWrong
	goto DragonsDen_Shrine_EventScript_ElderQuiz5

DragonsDen_Shrine_EventScript_ElderWrong::
	msgbox DragonsDen_Shrine_Text_WrongAnswer1, MSGBOX_DEFAULT
	addvar 20560, 1
	return

DragonsDen_Shrine_EventScript_ElderQuizFinish::
	msgbox DragonsDen_Shrine_Text_RightAnswer, MSGBOX_DEFAULT
	delay 20
	msgbox DragonsDen_Shrine_Text_PassedTest, MSGBOX_DEFAULT
	closemessage
	goto DragonsDen_Shrine_EventScript_ClairEnter

DragonsDen_Shrine_Text_ElderGreeting:
	.string "Hm{SE_M_DIZZY_PUNCH}Goo{SE_M_WATERFALL}t{SE_M_ATTRACT2}se{SE_M_REVERSAL}yo{SE_M_DIVE}here.\p"
	.string "N{SE_M_ATTRACT2}nee{SE_M_WATERFALL}t{SE_M_ATTRACT2}explai{SE_M_ATTRACT}wh{SE_M_YAWN}yo{SE_M_DIVE}came.\n"
	.string "CLAI{SE_M_MINIMIZE}sen{SE_M_SPIT_UP}yo{SE_M_DIVE}here{SE_M_SUPERSONIC}didn'{SE_M_SPIT_UP}she?\p"
	.string "Tha{SE_M_SPIT_UP}gir{SE_M_BATON_PASS}i{SE_M_GRASSWHISTLE}{SE_M_CHARGE}handful…\n"
	.string "{SE_M_HEAL_BELL}a{SE_M_MILK_DRINK}sorry{SE_M_SUPERSONIC}bu{SE_M_SPIT_UP}{SE_M_HEAL_BELL}mus{SE_M_SPIT_UP}tes{SE_M_SPIT_UP}you.\p"
	.string "No{SE_M_SPIT_UP}t{SE_M_ATTRACT2}worry{SE_M_SUPERSONIC}yo{SE_M_DIVE}ar{SE_M_REVERSAL}t{SE_M_ATTRACT2}answer\n"
	.string "onl{SE_M_YAWN}{SE_M_CHARGE}fe{SE_M_TWISTER}questions.\l"
	.string "Ready?$"

DragonsDen_Shrine_Text_Question1:
	.string "Wha{SE_M_SPIT_UP}ar{SE_M_REVERSAL}POKéMO{SE_M_PSYBEAM2}t{SE_M_ATTRACT2}you?$"

DragonsDen_Shrine_Text_Question2:
	.string "Wha{SE_M_SPIT_UP}help{SE_M_GRASSWHISTLE}yo{SE_M_DIVE}t{SE_M_ATTRACT2}wi{SE_M_ATTRACT}battles?$"

DragonsDen_Shrine_Text_Question3:
	.string "Wha{SE_M_SPIT_UP}kin{SE_M_WATERFALL}o{SE_M_ACID_ARMOR}traine{SE_M_SAND_TOMB}d{SE_M_ATTRACT2}yo{SE_M_DIVE}wish\n"
	.string "t{SE_M_ATTRACT2}battle?$"

DragonsDen_Shrine_Text_Question4:
	.string "Wha{SE_M_SPIT_UP}i{SE_M_GRASSWHISTLE}mos{SE_M_SPIT_UP}importan{SE_M_SPIT_UP}for\n"
	.string "raisin{SE_M_SANDSTORM}POKéMON?$"

DragonsDen_Shrine_Text_Question5:
	.string "Stron{SE_M_SANDSTORM}POKéMON{SE_M_PERISH_SONG}Wea{SE_M_ENCORE2}POKéMON.\n"
	.string "Whic{SE_M_TRI_ATTACK}i{SE_M_GRASSWHISTLE}mor{SE_M_REVERSAL}important?$"

DragonsDen_Shrine_Text_WrongAnswer1:
	.string "Hah{SE_M_SING}{SE_M_HEAL_BELL}didn'{SE_M_SPIT_UP}quit{SE_M_REVERSAL}catc{SE_M_TRI_ATTACK}that…$"

DragonsDen_Shrine_Text_WrongAnswer2:
	.string "Wha{SE_M_SPIT_UP}wa{SE_M_GRASSWHISTLE}i{SE_M_SPIT_UP}yo{SE_M_DIVE}said?$"

DragonsDen_Shrine_Text_RightAnswer:
	.string "Oh{SE_M_SUPERSONIC}{SE_M_HEAL_BELL}understand…$"

DragonsDen_Shrine_Text_PassedTest:
	.string "Hm{SE_M_DIZZY_PUNCH}{SE_M_HEAL_BELL}see…\p"
	.string "Yo{SE_M_DIVE}car{SE_M_REVERSAL}deepl{SE_M_YAWN}fo{SE_M_SAND_TOMB}POKéMON.\p"
	.string "Ver{SE_M_YAWN}commendable.\p"
	.string "Tha{SE_M_SPIT_UP}convictio{SE_M_ATTRACT}i{SE_M_GRASSWHISTLE}wha{SE_M_SPIT_UP}is\n"
	.string "important!\p"
	.string "{PLAYER}{SE_M_SUPERSONIC}don'{SE_M_SPIT_UP}los{SE_M_REVERSAL}tha{SE_M_SPIT_UP}belief.\p"
	.string "I{SE_M_SPIT_UP}wil{SE_M_BATON_PASS}se{SE_M_REVERSAL}yo{SE_M_DIVE}throug{SE_M_TRI_ATTACK}a{SE_M_SPIT_UP}the\n"
	.string "POKéMO{SE_M_PSYBEAM2}LEAGUE.$"

DragonsDen_Shrine_EventScript_ClairEnter::
	clearflag 8354
	addobject 4
	playbgm ((558 + 1) + 0x4C), FALSE
	playse 8
	delay 40
	playse 21
	applymovement2 255, J_Common_Movement_ExclamationMark
	turnobject 255, DIR_SOUTH
	delay 20
	turnobject 0xFE, DIR_SOUTH
	applymovement2 4, DragonsDen_Shrine_Movement_ClairEnter
	waitmovement 0
	turnobject 1, DIR_WEST
	turnobject 255, DIR_WEST
	turnobject 0xFE, DIR_NORTH
	msgbox DragonsDen_Shrine_Text_ClairYouPassed, MSGBOX_DEFAULT
	applymovement2 4, DragonsDen_Shrine_Movement_ClairBackup1
	waitmovement 0
	msgbox DragonsDen_Shrine_Text_ClairThatCantBe, MSGBOX_DEFAULT
	applymovement2 4, DragonsDen_Shrine_Movement_ClairBackup2
	waitmovement 0
	msgbox DragonsDen_Shrine_Text_ClairYoureLying, MSGBOX_DEFAULT
	applymovement2 1, DragonsDen_Shrine_Movement_ElderWalkToClair
	waitmovement 0
	turnobject 4, DIR_NORTH
	msgbox DragonsDen_Shrine_Text_MustIInformLance, MSGBOX_DEFAULT
	playse 21
	applymovement2 4, J_Common_Movement_ExclamationMark
	msgbox DragonsDen_Shrine_Text_IUnderstand, MSGBOX_DEFAULT
	applymovement2 4, DragonsDen_Shrine_Movement_ClairReturnToPlayer
	waitmovement 0
	msgbox DragonsDen_Shrine_Text_HereRisingBadge, MSGBOX_DEFAULT

	message DragonsDen_Shrine_Text_PlayerReceivedRisingBadge
	waitmessage
	call J_Common_EventScript_PlayGymBadgeFanfare
	msgbox DragonsDen_Shrine_Text_RisingBadgeExplanation, MSGBOX_DEFAULT
	setflag 10375
	addvar 20582, 1

	applymovement2 1, DragonsDen_Shrine_Movement_ElderReturnToPlayer
	waitmovement 0
	turnobject 255, DIR_NORTH
	turnobject 4, DIR_NORTH
	msgbox DragonsDen_Shrine_Text_ElderScoldsClair, MSGBOX_DEFAULT
	closemessage
	delay 20
	msgbox DragonsDen_Shrine_Text_Speechless, MSGBOX_DEFAULT
	closemessage
	applymovement2 4, DragonsDen_Shrine_Movement_ClairLeave
	waitmovement 0
	playse 9
	fadedefaultbgm
	setflag 8354
	removeobject 4
	clearflag 8351
	setvar 20550, 3
	release
	end

DragonsDen_Shrine_Movement_ClairEnter:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	face_right
	step_end

DragonsDen_Shrine_Movement_ClairBackup1:
	lock_facing_direction
	walk_fast_left
	unlock_facing_direction
	step_end

DragonsDen_Shrine_Movement_ClairBackup2:
	lock_facing_direction
	walk_slow_left
	unlock_facing_direction
	step_end

DragonsDen_Shrine_Movement_ElderWalkToClair:
	walk_left
	walk_left
	walk_left
	face_down
	step_end

DragonsDen_Shrine_Movement_ClairReturnToPlayer:
	walk_right
	walk_right
	step_end

DragonsDen_Shrine_Movement_ElderReturnToPlayer:
	walk_slow_right
	walk_slow_right
	walk_slow_right
	face_down
	step_end

DragonsDen_Shrine_Movement_ClairLeave:
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_right
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	step_end

DragonsDen_Shrine_Text_ClairYouPassed:
	.string "S{SE_M_ATTRACT2}ho{SE_M_TWISTER}di{SE_M_WATERFALL}i{SE_M_SPIT_UP}go?\p"
	.string "{SE_M_HEAL_BELL}gues{SE_M_GRASSWHISTLE}there'{SE_M_GRASSWHISTLE}n{SE_M_ATTRACT2}point\n"
	.string "i{SE_M_ATTRACT}asking{SE_M_PERISH_SONG}Yo{SE_M_DIVE}di{SE_M_WATERFALL}fail?\p"
	.string "..................................\p"
	.string "…What{SE_M_SING}Yo{SE_M_DIVE}passed?$"

DragonsDen_Shrine_Text_ClairThatCantBe:
	.string "Tha{SE_M_SPIT_UP}can'{SE_M_SPIT_UP}be!$"

DragonsDen_Shrine_Text_ClairYoureLying:
	.string "You'r{SE_M_REVERSAL}lying!\p"
	.string "Eve{SE_M_ATTRACT}{SE_M_HEAL_BELL}haven'{SE_M_SPIT_UP}bee{SE_M_ATTRACT}approved!$"

DragonsDen_Shrine_Text_MustIInformLance:
	.string "CLAIR!\p"
	.string "Thi{SE_M_GRASSWHISTLE}chil{SE_M_WATERFALL}i{SE_M_GRASSWHISTLE}impeccable,\n"
	.string "i{SE_M_ATTRACT}skil{SE_M_BATON_PASS}an{SE_M_WATERFALL}spirit!\p"
	.string "Admi{SE_M_SPIT_UP}defea{SE_M_SPIT_UP}an{SE_M_WATERFALL}confe{SE_M_SAND_TOMB}the\n"
	.string "RISINGBADGE!\p"
	.string "…O{SE_M_SAND_TOMB}mus{SE_M_SPIT_UP}{SE_M_HEAL_BELL}infor{SE_M_MILK_DRINK}LANC{SE_M_SWORDS_DANCE}o{SE_M_ACID_ARMOR}this?$"

DragonsDen_Shrine_Text_IUnderstand:
	.string "I-{SE_M_HEAL_BELL}understand…$"

DragonsDen_Shrine_Text_HereRisingBadge:
	.string "Here{SE_M_SUPERSONIC}thi{SE_M_GRASSWHISTLE}i{SE_M_GRASSWHISTLE}th{SE_M_REVERSAL}RISINGBADGE…\p"
	.string "Hurr{SE_M_YAWN}up{SE_M_DRAGON_RAGE}Tak{SE_M_REVERSAL}it!$"

DragonsDen_Shrine_Text_PlayerReceivedRisingBadge:
	.string "{PLAYER} receive{SE_M_WATERFALL}RISINGBADGE.$"

DragonsDen_Shrine_Text_RisingBadgeExplanation:
	.string "RISINGBADG{SE_M_SWORDS_DANCE}wil{SE_M_BATON_PASS}enabl{SE_M_REVERSAL}your\n"
	.string "POKéMO{SE_M_PSYBEAM2}t{SE_M_ATTRACT2}us{SE_M_REVERSAL}th{SE_M_REVERSAL}mov{SE_M_REVERSAL}for\l"
	.string "climbin{SE_M_SANDSTORM}waterfalls.\p"
	.string "Also{SE_M_SUPERSONIC}al{SE_M_BATON_PASS}POKéMO{SE_M_PSYBEAM2}wil{SE_M_BATON_PASS}recognize\n"
	.string "yo{SE_M_DIVE}a{SE_M_GRASSWHISTLE}{SE_M_CHARGE}traine{SE_M_SAND_TOMB}an{SE_M_WATERFALL}obe{SE_M_YAWN}your\l"
	.string "ever{SE_M_YAWN}comman{SE_M_WATERFALL}withou{SE_M_SPIT_UP}question.$"

DragonsDen_Shrine_Text_ElderScoldsClair:
	.string "CLAIR…\p"
	.string "Reflec{SE_M_SPIT_UP}upo{SE_M_ATTRACT}wha{SE_M_SPIT_UP}i{SE_M_SPIT_UP}i{SE_M_GRASSWHISTLE}tha{SE_M_SPIT_UP}you\n"
	.string "lac{SE_M_ENCORE2}an{SE_M_WATERFALL}thi{SE_M_GRASSWHISTLE}chil{SE_M_WATERFALL}has.$"

DragonsDen_Shrine_Text_Speechless:
	.string "..................................$"

DragonsDen_Shrine_Text_ComeAgain:
	.string "Com{SE_M_REVERSAL}again{SE_M_SUPERSONIC}i{SE_M_ACID_ARMOR}yo{SE_M_DIVE}s{SE_M_ATTRACT2}desire.$"

DragonsDen_Shrine_Text_SilverIsInTraining:
	.string "{SE_M_BONEMERANG}bo{SE_M_YAWN}clos{SE_M_REVERSAL}t{SE_M_ATTRACT2}you{SE_M_SAND_TOMB}ag{SE_M_REVERSAL}i{SE_M_GRASSWHISTLE}in\n"
	.string "trainin{SE_M_SANDSTORM}here.\p"
	.string "H{SE_M_REVERSAL}i{SE_M_GRASSWHISTLE}muc{SE_M_TRI_ATTACK}lik{SE_M_REVERSAL}CLAI{SE_M_MINIMIZE}whe{SE_M_ATTRACT}sh{SE_M_REVERSAL}was\n"
	.string "younger{SE_M_PERISH_SONG}I{SE_M_SPIT_UP}i{SE_M_GRASSWHISTLE}{SE_M_CHARGE}littl{SE_M_REVERSAL}worrisome…$"

DragonsDen_Shrine_EventScript_Elder2::
	msgbox DragonsDen_Shrine_Text_Elder2, MSGBOX_NPC
	end

DragonsDen_Shrine_EventScript_Elder3::
	msgbox DragonsDen_Shrine_Text_Elder3, MSGBOX_NPC
	end

DragonsDen_Shrine_Text_Elder2:
	.string "It'{SE_M_GRASSWHISTLE}bee{SE_M_ATTRACT}quit{SE_M_REVERSAL}som{SE_M_REVERSAL}tim{SE_M_REVERSAL}sinc{SE_M_REVERSAL}a\n"
	.string "traine{SE_M_SAND_TOMB}ha{SE_M_GRASSWHISTLE}gaine{SE_M_WATERFALL}ou{SE_M_SAND_TOMB}MASTER's\l"
	.string "rar{SE_M_REVERSAL}approval.\p"
	.string "I{SE_M_ATTRACT}fact{SE_M_SUPERSONIC}no{SE_M_SPIT_UP}sinc{SE_M_REVERSAL}Maste{SE_M_SAND_TOMB}LANCE.$"

DragonsDen_Shrine_Text_Elder3:
	.string "Yo{SE_M_DIVE}kno{SE_M_TWISTER}youn{SE_M_SANDSTORM}Maste{SE_M_SAND_TOMB}LANCE?\p"
	.string "H{SE_M_REVERSAL}look{SE_M_GRASSWHISTLE}s{SE_M_ATTRACT2}muc{SE_M_TRI_ATTACK}lik{SE_M_REVERSAL}ou{SE_M_SAND_TOMB}MASTER\n"
	.string "di{SE_M_WATERFALL}i{SE_M_ATTRACT}hi{SE_M_GRASSWHISTLE}youth.\p"
	.string "It'{SE_M_GRASSWHISTLE}i{SE_M_ATTRACT}thei{SE_M_SAND_TOMB}blood.$"

DragonsDen_Shrine_EventScript_ElderChooseDratini::
	goto_if_eq 20560, 0, DragonsDen_Shrine_EventScript_ElderGiveSpecialDratini
	goto DragonsDen_Shrine_EventScript_ElderGiveBasicDratini

DragonsDen_Shrine_EventScript_ElderGiveBasicDratini::
	goto_if_set 8707, DragonsDen_Shrine_EventScript_ElderAlreadyGotDratini
	msgbox DragonsDen_Shrine_Text_TakeThisDratini, MSGBOX_DEFAULT

	setvar 16385, 147
	bufferspeciesname STR_VAR_1, 147
	givemon 147, 15
	call J_Common_EventScript_GiftMon

	msgbox DragonsDen_Shrine_Text_SymbolicDragon, MSGBOX_DEFAULT
	setflag 8707
	release
	end

DragonsDen_Shrine_EventScript_ElderGiveSpecialDratini::
	goto_if_set 8707, DragonsDen_Shrine_EventScript_ElderAlreadyGotDratini
	msgbox DragonsDen_Shrine_Text_TakeThisDratini, MSGBOX_DEFAULT

	setvar 16385, 147
	bufferspeciesname STR_VAR_1, 147
	givenamedmon 4
	call J_Common_EventScript_GiftMonNamed

	msgbox DragonsDen_Shrine_Text_SymbolicDragon, MSGBOX_DEFAULT
	setflag 8707
	release
	end

DragonsDen_Shrine_EventScript_ElderAlreadyGotDratini::
	msgbox DragonsDen_Shrine_Text_ClairsGrandfather, MSGBOX_DEFAULT
	release
	end

DragonsDen_Shrine_Text_TakeThisDratini:
	.string "Hm{SE_M_DIZZY_PUNCH}Goo{SE_M_WATERFALL}t{SE_M_ATTRACT2}se{SE_M_REVERSAL}yo{SE_M_DIVE}here.\p"
	.string "You{SE_M_SAND_TOMB}arriva{SE_M_BATON_PASS}i{SE_M_GRASSWHISTLE}mos{SE_M_SPIT_UP}fortunate.\p"
	.string "{SE_M_HEAL_BELL}hav{SE_M_REVERSAL}somethin{SE_M_SANDSTORM}fo{SE_M_SAND_TOMB}you.\p"
	.string "Tak{SE_M_REVERSAL}thi{SE_M_GRASSWHISTLE}DRATIN{SE_M_HEAL_BELL}a{SE_M_GRASSWHISTLE}proo{SE_M_ACID_ARMOR}tha{SE_M_SPIT_UP}I\n"
	.string "hav{SE_M_REVERSAL}recognize{SE_M_WATERFALL}you{SE_M_SAND_TOMB}worth.$"

DragonsDen_Shrine_Text_SymbolicDragon:
	.string "Drago{SE_M_ATTRACT}POKéMO{SE_M_PSYBEAM2}ar{SE_M_REVERSAL}symboli{SE_M_HYPER_BEAM}o{SE_M_ACID_ARMOR}our\n"
	.string "clan.\p"
	.string "Yo{SE_M_DIVE}hav{SE_M_REVERSAL}show{SE_M_ATTRACT}tha{SE_M_SPIT_UP}yo{SE_M_DIVE}ca{SE_M_ATTRACT}be\n"
	.string "entruste{SE_M_WATERFALL}wit{SE_M_TRI_ATTACK}one.$"

DragonsDen_Shrine_Text_ClairsGrandfather:
	.string "CLAI{SE_M_MINIMIZE}appear{SE_M_GRASSWHISTLE}t{SE_M_ATTRACT2}hav{SE_M_REVERSAL}learne{SE_M_WATERFALL}an\n"
	.string "invaluabl{SE_M_REVERSAL}lesso{SE_M_ATTRACT}fro{SE_M_MILK_DRINK}you.\p"
	.string "{SE_M_HEAL_BELL}than{SE_M_ENCORE2}yo{SE_M_DIVE}a{SE_M_GRASSWHISTLE}he{SE_M_SAND_TOMB}grandfather.$"

