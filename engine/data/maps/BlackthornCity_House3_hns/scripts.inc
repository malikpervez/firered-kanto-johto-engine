@ Johto (data/maps/BlackthornCity_House3_hns/scripts.inc), as built into the FireRed game.

BlackthornCity_House3_hns_MapScripts::
	.byte 0

BlackthornCity_MoveDeletersHouse_EventScript_MoveDeleter::
	lockall
	applymovement LOCALID_MOVE_DELETER, J_Common_Movement_FacePlayer
	waitmovement 0
	msgbox BlackthornCity_MoveDeletersHouse_Text_ICanMakeMonForgetMove, MSGBOX_YESNO
	switch VAR_RESULT
	case YES, BlackthornCity_MoveDeletersHouse_EventScript_ChooseMonAndMoveToForget
	case NO, BlackthornCity_MoveDeletersHouse_EventScript_ComeAgain
	releaseall
	end

BlackthornCity_MoveDeletersHouse_EventScript_ChooseMonAndMoveToForget::
	msgbox BlackthornCity_MoveDeletersHouse_Text_WhichMonShouldForget, MSGBOX_DEFAULT
	special ChoosePartyMon
	waitstate
	goto_if_eq VAR_0x8004, PARTY_NOTHING_CHOSEN, BlackthornCity_MoveDeletersHouse_EventScript_ComeAgain
	special IsSelectedMonEgg
	goto_if_eq VAR_RESULT, TRUE, BlackthornCity_MoveDeletersHouse_EventScript_EggCantForgetMoves
	special GetNumMovesSelectedMonHas
	goto_if_eq VAR_RESULT, 1, BlackthornCity_MoveDeletersHouse_EventScript_MonOnlyKnowsOneMove
	msgbox BlackthornCity_MoveDeletersHouse_Text_WhichMoveShouldBeForgotten, MSGBOX_DEFAULT
	fadescreen FADE_TO_BLACK
	special MoveDeleterChooseMoveToForget
	fadescreen FADE_FROM_BLACK
	goto_if_eq VAR_0x8005, MAX_MON_MOVES, BlackthornCity_MoveDeletersHouse_EventScript_ChooseMonAndMoveToForget
	special BufferMoveDeleterNicknameAndMove
	msgbox BlackthornCity_MoveDeletersHouse_Text_MonsMoveShouldBeForgotten, MSGBOX_YESNO
	switch VAR_RESULT
	case YES, BlackthornCity_MoveDeletersHouse_EventScript_TryForgetMove
	case NO, BlackthornCity_MoveDeletersHouse_EventScript_ComeAgain
	releaseall
	end

BlackthornCity_MoveDeletersHouse_EventScript_TryForgetMove::
	special IsLastMonThatKnowsSurf
	goto_if_eq VAR_RESULT, TRUE, BlackthornCity_MoveDeletersHouse_EventScript_LastMonWithSurf
	special MoveDeleterForgetMove
	playfanfare MUS_MOVE_DELETED
	waitfanfare
	msgbox BlackthornCity_MoveDeletersHouse_Text_MonHasForgottenMove, MSGBOX_DEFAULT
	releaseall
	end

BlackthornCity_MoveDeletersHouse_EventScript_MonOnlyKnowsOneMove::
	special BufferMoveDeleterNicknameAndMove
	msgbox BlackthornCity_MoveDeletersHouse_Text_MonOnlyKnowsOneMove, MSGBOX_DEFAULT
	releaseall
	end

BlackthornCity_MoveDeletersHouse_EventScript_EggCantForgetMoves::
	msgbox BlackthornCity_MoveDeletersHouse_Text_EggCantForgetMoves, MSGBOX_DEFAULT
	releaseall
	end

BlackthornCity_MoveDeletersHouse_EventScript_ComeAgain::
	msgbox BlackthornCity_MoveDeletersHouse_Text_ComeAgain, MSGBOX_DEFAULT
	releaseall
	end

BlackthornCity_MoveDeletersHouse_EventScript_LastMonWithSurf::
	special BufferMoveDeleterNicknameAndMove
	msgbox BlackthornCity_MoveDeletersHouse_Text_CantForgetSurf, MSGBOX_DEFAULT
	releaseall
	end

BlackthornCity_MoveDeletersHouse_Text_ICanMakeMonForgetMove:
	.string "Uh…\n"
	.string "Oh{SE_M_SUPERSONIC}yes{SE_M_SUPERSONIC}I'{SE_M_MILK_DRINK}th{SE_M_REVERSAL}MOV{SE_M_SWORDS_DANCE}DELETER.\p"
	.string "{SE_M_HEAL_BELL}ca{SE_M_ATTRACT}mak{SE_M_REVERSAL}POKéMO{SE_M_PSYBEAM2}forge{SE_M_SPIT_UP}thei{SE_M_SAND_TOMB}moves.\p"
	.string "Woul{SE_M_WATERFALL}yo{SE_M_DIVE}lik{SE_M_REVERSAL}m{SE_M_REVERSAL}t{SE_M_ATTRACT2}d{SE_M_ATTRACT2}that?$"

BlackthornCity_MoveDeletersHouse_Text_WhichMonShouldForget:
	.string "Whic{SE_M_TRI_ATTACK}POKéMO{SE_M_PSYBEAM2}shoul{SE_M_WATERFALL}forge{SE_M_SPIT_UP}{SE_M_CHARGE}move?$"

BlackthornCity_MoveDeletersHouse_Text_WhichMoveShouldBeForgotten:
	.string "Whic{SE_M_TRI_ATTACK}mov{SE_M_REVERSAL}shoul{SE_M_WATERFALL}b{SE_M_REVERSAL}forgotten?$"

BlackthornCity_MoveDeletersHouse_Text_MonOnlyKnowsOneMove:
	.string "{STR_VAR_1} know{SE_M_GRASSWHISTLE}onl{SE_M_YAWN}on{SE_M_REVERSAL}move\n"
	.string "s{SE_M_ATTRACT2}i{SE_M_SPIT_UP}can'{SE_M_SPIT_UP}b{SE_M_REVERSAL}forgotten…$"

BlackthornCity_MoveDeletersHouse_Text_MonsMoveShouldBeForgotten:
	.string "Hm{SE_M_DRAGON_RAGE}{STR_VAR_1}'{SE_M_GRASSWHISTLE}{STR_VAR_2}?\n"
	.string "Tha{SE_M_SPIT_UP}mov{SE_M_REVERSAL}shoul{SE_M_WATERFALL}b{SE_M_REVERSAL}forgotten?$"

BlackthornCity_MoveDeletersHouse_Text_MonHasForgottenMove:
	.string "I{SE_M_SPIT_UP}worke{SE_M_WATERFALL}t{SE_M_ATTRACT2}perfection!\p"
	.string "{STR_VAR_1} ha{SE_M_GRASSWHISTLE}forgotten\n"
	.string "{STR_VAR_2} completely.$"

BlackthornCity_MoveDeletersHouse_Text_ComeAgain:
	.string "Com{SE_M_REVERSAL}agai{SE_M_ATTRACT}i{SE_M_ACID_ARMOR}ther{SE_M_REVERSAL}ar{SE_M_REVERSAL}move{SE_M_GRASSWHISTLE}that\n"
	.string "nee{SE_M_WATERFALL}t{SE_M_ATTRACT2}b{SE_M_REVERSAL}forgotten.$"

BlackthornCity_MoveDeletersHouse_Text_EggCantForgetMoves:
	.string "What?\n"
	.string "N{SE_M_ATTRACT2}EG{SE_M_SWAGGER}shoul{SE_M_WATERFALL}kno{SE_M_TWISTER}an{SE_M_YAWN}moves.$"

BlackthornCity_MoveDeletersHouse_Text_CantForgetSurf:
	.string "Hm!\p"
	.string "You{SE_M_SAND_TOMB}{STR_VAR_1} doesn'{SE_M_SPIT_UP}see{SE_M_MILK_DRINK}willing\n"
	.string "t{SE_M_ATTRACT2}forge{SE_M_SPIT_UP}SURF.$"

BlackthornCity_MoveRelearnersHouse_EventScript_MoveRelearner::
	lockall
	faceplayer
	specialvar VAR_RESULT, IsRandomMovesActivated
	goto_if_eq VAR_RESULT, TRUE, BlackthornCity_MoveRelearnersHouse_EventScript_Randomizer
	goto_if_set FLAG_TEMP_1, BlackthornCity_MoveRelearnersHouse_EventScript_AskTeachMove
	msgbox BlackthornCity_MoveRelearnersHouse_Text_ImTheMoveTutor, MSGBOX_DEFAULT
	setflag FLAG_TEMP_1
	goto BlackthornCity_MoveRelearnersHouse_EventScript_AskTeachMove
	end

BlackthornCity_MoveRelearnersHouse_EventScript_AskTeachMove::
	checkitem ITEM_HEART_SCALE
	goto_if_eq VAR_RESULT, FALSE, BlackthornCity_MoveRelearnersHouse_EventScript_ComeBackWithHeartScale
	msgbox BlackthornCity_MoveRelearnersHouse_Text_ThatsAHeartScaleWantMeToTeachMove, MSGBOX_YESNO
	switch VAR_RESULT
	case NO, BlackthornCity_MoveRelearnersHouse_EventScript_ComeBackWithHeartScale
	goto BlackthornCity_MoveRelearnersHouse_EventScript_ChooseMon
	end

BlackthornCity_MoveRelearnersHouse_EventScript_ChooseMon::
	msgbox BlackthornCity_MoveRelearnersHouse_Text_TutorWhichMon, MSGBOX_DEFAULT
	setmoverelearnerstate MOVE_RELEARNER_LEVEL_UP_MOVES
	chooseboxmon SELECT_PC_MON_MOVE_RELEARNER
	waitstate
	goto_if_eq VAR_0x8004, PARTY_NOTHING_CHOSEN, BlackthornCity_MoveRelearnersHouse_EventScript_ComeBackWithHeartScale
	special IsSelectedMonEgg
	goto_if_eq VAR_RESULT, TRUE, BlackthornCity_MoveRelearnersHouse_EventScript_CantTeachEgg
	special HasMovesToRelearn
	goto_if_eq VAR_RESULT, FALSE, BlackthornCity_MoveRelearnersHouse_EventScript_NoMoveToTeachMon
	goto BlackthornCity_MoveRelearnersHouse_EventScript_ChooseMove
	end

BlackthornCity_MoveRelearnersHouse_EventScript_ChooseMove::
	msgbox BlackthornCity_MoveRelearnersHouse_Text_TeachWhichMove, MSGBOX_DEFAULT
	special TeachMoveRelearnerMove
	waitstate
	goto_if_eq VAR_0x8004, 0, BlackthornCity_MoveRelearnersHouse_EventScript_ChooseMon
	msgbox BlackthornCity_MoveRelearnersHouse_Text_HandedOverHeartScale, MSGBOX_DEFAULT
	removeitem ITEM_HEART_SCALE
	goto BlackthornCity_MoveRelearnersHouse_EventScript_ComeBackWithHeartScale
	end

BlackthornCity_MoveRelearnersHouse_EventScript_NoMoveToTeachMon::
	msgbox BlackthornCity_MoveRelearnersHouse_Text_DontHaveMoveToTeachPokemon, MSGBOX_DEFAULT
	goto BlackthornCity_MoveRelearnersHouse_EventScript_ChooseMon
	end

BlackthornCity_MoveRelearnersHouse_EventScript_CantTeachEgg::
	msgbox BlackthornCity_MoveRelearnersHouse_Text_CantTeachEgg, MSGBOX_DEFAULT
	goto BlackthornCity_MoveRelearnersHouse_EventScript_ChooseMon
	end

BlackthornCity_MoveRelearnersHouse_EventScript_ComeBackWithHeartScale::
	msgbox BlackthornCity_MoveRelearnersHouse_Text_ComeBackWithHeartScale, MSGBOX_DEFAULT
	closemessage
	releaseall
	end

BlackthornCity_MoveRelearnersHouse_EventScript_Randomizer::
	msgbox BlackthornCity_MoveRelearnersHouse_Text_SorryCantHelp, MSGBOX_DEFAULT
	closemessage
	releaseall
	end

BlackthornCity_MoveRelearnersHouse_Text_SorryCantHelp:
	.string "Sorry{SE_M_SUPERSONIC}{SE_M_HEAL_BELL}can'{SE_M_SPIT_UP}hel{SE_M_MORNING_SUN}you.$"

BlackthornCity_MoveRelearnersHouse_Text_ImTheMoveTutor:
	.string "I'{SE_M_MILK_DRINK}th{SE_M_REVERSAL}MOV{SE_M_SWORDS_DANCE}TUTOR.\p"
	.string "{SE_M_HEAL_BELL}kno{SE_M_TWISTER}al{SE_M_BATON_PASS}th{SE_M_REVERSAL}move{SE_M_GRASSWHISTLE}tha{SE_M_SPIT_UP}POKéMON\n"
	.string "learn--ever{SE_M_YAWN}on{SE_M_REVERSAL}o{SE_M_ACID_ARMOR}them--an{SE_M_WATERFALL}{SE_M_HEAL_BELL}can\l"
	.string "teac{SE_M_TRI_ATTACK}POKéMO{SE_M_PSYBEAM2}thos{SE_M_REVERSAL}moves.\p"
	.string "{SE_M_HEAL_BELL}ca{SE_M_ATTRACT}teac{SE_M_TRI_ATTACK}{SE_M_CHARGE}mov{SE_M_REVERSAL}t{SE_M_ATTRACT2}{SE_M_CHARGE}POKéMON\n"
	.string "o{SE_M_ACID_ARMOR}your{SE_M_GRASSWHISTLE}i{SE_M_ACID_ARMOR}you'{SE_M_WATERFALL}like.\p"
	.string "I'l{SE_M_BATON_PASS}d{SE_M_ATTRACT2}i{SE_M_SPIT_UP}fo{SE_M_SAND_TOMB}{SE_M_CHARGE}HEAR{SE_M_SWIFT}SCALE.\n"
	.string "I'{SE_M_MILK_DRINK}collectin{SE_M_SANDSTORM}thos{SE_M_REVERSAL}now.$"

BlackthornCity_MoveRelearnersHouse_Text_ThatsAHeartScaleWantMeToTeachMove:
	.string "Oh{SE_M_DRAGON_RAGE}That'{SE_M_GRASSWHISTLE}it{SE_M_DRAGON_RAGE}That'{SE_M_GRASSWHISTLE}a{SE_M_ATTRACT}hones{SE_M_SPIT_UP}to\n"
	.string "goodnes{SE_M_GRASSWHISTLE}HEAR{SE_M_SWIFT}SCALE!\p"
	.string "Le{SE_M_SPIT_UP}m{SE_M_REVERSAL}guess{SE_M_SUPERSONIC}yo{SE_M_DIVE}wan{SE_M_SPIT_UP}m{SE_M_REVERSAL}t{SE_M_ATTRACT2}teach\n"
	.string "{SE_M_CHARGE}move?$"

BlackthornCity_MoveRelearnersHouse_Text_TutorWhichMon:
	.string "Whic{SE_M_TRI_ATTACK}POKéMO{SE_M_PSYBEAM2}need{SE_M_GRASSWHISTLE}tutoring?$"

BlackthornCity_MoveRelearnersHouse_Text_TeachWhichMove:
	.string "Whic{SE_M_TRI_ATTACK}mov{SE_M_REVERSAL}shoul{SE_M_WATERFALL}{SE_M_HEAL_BELL}teach?$"

BlackthornCity_MoveRelearnersHouse_Text_DontHaveMoveToTeachPokemon:
	.string "Sorry…\p"
	.string "I{SE_M_SPIT_UP}doesn'{SE_M_SPIT_UP}appea{SE_M_SAND_TOMB}a{SE_M_GRASSWHISTLE}i{SE_M_ACID_ARMOR}{SE_M_HEAL_BELL}hav{SE_M_REVERSAL}an{SE_M_YAWN}move\n"
	.string "{SE_M_HEAL_BELL}ca{SE_M_ATTRACT}teac{SE_M_TRI_ATTACK}tha{SE_M_SPIT_UP}POKéMON.$"

BlackthornCity_MoveRelearnersHouse_Text_HandedOverHeartScale:
	.string "{PLAYER} hande{SE_M_WATERFALL}ove{SE_M_SAND_TOMB}on{SE_M_REVERSAL}HEAR{SE_M_SWIFT}SCALE\n"
	.string "i{SE_M_ATTRACT}exchange.$"

BlackthornCity_MoveRelearnersHouse_Text_ComeBackWithHeartScale:
	.string "I{SE_M_ACID_ARMOR}you{SE_M_SAND_TOMB}POKéMO{SE_M_PSYBEAM2}nee{SE_M_WATERFALL}t{SE_M_ATTRACT2}lear{SE_M_ATTRACT}{SE_M_CHARGE}move,\n"
	.string "com{SE_M_REVERSAL}bac{SE_M_ENCORE2}wit{SE_M_TRI_ATTACK}{SE_M_CHARGE}HEAR{SE_M_SWIFT}SCALE.$"

BlackthornCity_MoveRelearnersHouse_Text_CantTeachEgg:
	.string "Hunh{SE_M_SING}Ther{SE_M_REVERSAL}isn'{SE_M_SPIT_UP}{SE_M_CHARGE}singl{SE_M_REVERSAL}mov{SE_M_REVERSAL}that\n"
	.string "{SE_M_HEAL_BELL}ca{SE_M_ATTRACT}teac{SE_M_TRI_ATTACK}a{SE_M_ATTRACT}EGG.$"

