@ Johto (data/maps/AzaleaTown_KurtsHouse_hns/scripts.inc), as built into the FireRed game.

AzaleaTown_KurtsHouse_hns_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, AzaleaTown_KurtsHouse_OnFrame
	map_script MAP_SCRIPT_ON_TRANSITION, AzaleaTown_KurtsHouse_OnTransition
	.byte 0

AzaleaTown_KurtsHouse_OnTransition::
	goto_if_eq JOHTO_VAR_AZALEA_TOWN_STATE, 3, AzaleaTown_KurtsHouse_EventScript_ReturnFromWellSetup
	end

AzaleaTown_KurtsHouse_OnFrame::
	map_script_2 JOHTO_VAR_AZALEA_TOWN_STATE, 3, AzaleaTown_KurtsHouse_EventScript_ReturnFromWell
	.2byte 0

AzaleaTown_KurtsHouse_EventScript_KurtBefore::
	lock
	faceplayer
	msgbox KurtsHouse_Text_KurtMakingBallsMustWait, MSGBOX_DEFAULT
	closemessage
	goto_if_eq VAR_FACING, DIR_NORTH, AzaleaTown_KurtsHouse_EventScript_PlayerMove
	applymovement LOCALID_AZALEA_TOWN_KURT_BEFORE, AzaleaTown_KurtsHouse_Movement_KurtWalkDown
	waitmovement 0
	playse SE_EXIT
	removeobject LOCALID_AZALEA_TOWN_KURT_BEFORE
	setflag JOHTO_FLAG_HIDE_KURT_1
	setflag JOHTO_FLAG_HIDE_AZALEA_TOWN_WELL_ROCKET
	setvar JOHTO_VAR_AZALEA_TOWN_STATE, 2
	release
	end

AzaleaTown_KurtsHouse_EventScript_PlayerMove::
	applymovement OBJ_EVENT_ID_PLAYER, AzaleaTown_KurtsHouse_Movement_Player
	waitmovement 0
	applymovement LOCALID_AZALEA_TOWN_KURT_BEFORE, AzaleaTown_KurtsHouse_Movement_KurtWalkDown
	waitmovement 0
	playse SE_EXIT
	removeobject LOCALID_AZALEA_TOWN_KURT_BEFORE
	setflag JOHTO_FLAG_HIDE_KURT_1
	setflag JOHTO_FLAG_HIDE_AZALEA_TOWN_WELL_ROCKET
	release
	end

AzaleaTown_KurtsHouse_EventScript_Girl::
	lock
	faceplayer
	goto_if_unset JOHTO_FLAG_HIDE_KURT_2, AzaleaTown_KurtsHouse_EventScript_Girl2
	goto_if_set JOHTO_FLAG_HIDE_KURT_1, AzaleaTown_KurtsHouse_EventScript_Girl3
	msgbox KurtsHouse_Text_GranddaughterSlowpokeGone, MSGBOX_DEFAULT
	release
	end

AzaleaTown_KurtsHouse_EventScript_Girl2::
	goto_if_eq JOHTO_VAR_AZALEA_TOWN_STATE, 3, AzaleaTown_KurtsHouse_EventScript_Girl4
	goto_if_eq JOHTO_VAR_AZALEA_TOWN_STATE, 4, AzaleaTown_KurtsHouse_EventScript_Girl4
	goto_if_eq JOHTO_VAR_AZALEA_TOWN_STATE, 5, AzaleaTown_KurtsHouse_EventScript_Girl4
	goto_if_eq JOHTO_VAR_AZALEA_TOWN_STATE, 6, AzaleaTown_KurtsHouse_EventScript_Girl4
	goto_if_eq JOHTO_VAR_AZALEA_TOWN_STATE, 8, AzaleaTown_KurtsHouse_EventScript_Girl5
	goto_if_eq JOHTO_VAR_AZALEA_TOWN_STATE, 9, AzaleaTown_KurtsHouse_EventScript_Girl5

	msgbox KurtsHouse_Text_GranddaughterDad, MSGBOX_DEFAULT
	closemessage
	release
	end

AzaleaTown_KurtsHouse_EventScript_Girl3::
	msgbox KurtsHouse_Text_GranddaughterLonely, MSGBOX_DEFAULT
	closemessage
	release
	end

AzaleaTown_KurtsHouse_EventScript_Girl4::
	msgbox KurtsHouse_Text_GranddaughterSlowpokeBack, MSGBOX_DEFAULT
	closemessage
	release
	end

AzaleaTown_KurtsHouse_EventScript_Girl5::
	msgbox KurtsHouse_Text_GranddaughterSound, MSGBOX_DEFAULT
	closemessage
	release
	end

AzaleaTown_KurtsHouse_EventScript_ReturnFromWellSetup::
	setobjectmovementtype LOCALID_AZALEA_TOWN_KURT, MOVEMENT_TYPE_FACE_DOWN
	end

AzaleaTown_KurtsHouse_EventScript_ReturnFromWell::
	lock
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	msgbox KurtsHouse_Text_KurtHonoredToMakeBalls, MSGBOX_DEFAULT
	giveitem ITEM_FAST_BALL
	goto_if_eq VAR_RESULT, FALSE, J_Common_EventScript_BagIsFull
	msgbox KurtsHouse_Text_KurtBallsFromApricorns, MSGBOX_DEFAULT
	closemessage
	turnobject LOCALID_AZALEA_TOWN_KURT, DIR_NORTH
	setvar JOHTO_VAR_AZALEA_TOWN_STATE, 4
	release
	end

AzaleaTown_KurtsHouse_EventScript_KurtCheckGSBall::
	checkitem ITEM_GS_BALL
	goto_if_eq VAR_RESULT, TRUE, AzaleaTown_KurtsHouse_EventScript_KurtGsBall
	return

AzaleaTown_KurtsHouse_EventScript_Kurt::
	lock
	faceplayer
	goto_if_eq JOHTO_VAR_AZALEA_TOWN_STATE, 8, AzaleaTown_KurtsHouse_EventScript_KurtGsBall2
	goto_if_eq JOHTO_VAR_AZALEA_TOWN_STATE, 9, AzaleaTown_KurtsHouse_EventScript_KurtGsBall3
	msgbox KurtsHouse_Text_KurtAskYouHaveAnApricorn, MSGBOX_DEFAULT
	closemessage
	call_if_unset JOHTO_FLAG_CAUGHT_CELEBI, AzaleaTown_KurtsHouse_EventScript_KurtCheckGSBall

AzaleaTown_KurtsHouse_EventScript_Kurt2::
	special CreateKurtBallShop
	waitstate
	goto_if_eq VAR_RESULT, FALSE, AzaleaTown_KurtsHouse_EventScript_KurtCancel
	playse SE_BANG
	applymovement LOCALID_AZALEA_TOWN_KURT, AzaleaTownKurt_Movement_Making_Ball
	waitmovement 0
	playse SE_BANG
	applymovement LOCALID_AZALEA_TOWN_KURT, AzaleaTownKurt_Movement_Making_Ball
	waitmovement 0
	call_if_eq VAR_FACING, DIR_EAST, AzaleaTown_KurtsHouse_EventScript_TurnWest
	call_if_eq VAR_FACING, DIR_WEST, AzaleaTown_KurtsHouse_EventScript_TurnEast
	call_if_eq VAR_FACING, DIR_NORTH, AzaleaTown_KurtsHouse_EventScript_TurnSouth
	goto_if_eq VAR_0x8005, 1, AzaleaTown_KurtsHouse_EventScript_SingularBall
	bufferitemname STR_VAR_1, VAR_0x8004
	buffernumberstring STR_VAR_2, VAR_0x8005
	msgbox KurtsHouse_Text_KurtFinishedPlural, MSGBOX_DEFAULT
	message KurtsHouse_Text_KurtObtainedPlural
	waitmessage
	playfanfare MUS_OBTAIN_ITEM
	waitfanfare
	additem VAR_0x8004, VAR_0x8005
	msgbox KurtsHouse_Text_KurtTurnedOutGreat, MSGBOX_DEFAULT
	closemessage
	turnobject LOCALID_AZALEA_TOWN_KURT, DIR_NORTH
	release
	end

AzaleaTown_KurtsHouse_EventScript_TurnSouth::
	turnobject LOCALID_AZALEA_TOWN_KURT, DIR_SOUTH
	return

AzaleaTown_KurtsHouse_EventScript_TurnWest::
	turnobject LOCALID_AZALEA_TOWN_KURT, DIR_WEST
	return

AzaleaTown_KurtsHouse_EventScript_TurnEast::
	turnobject LOCALID_AZALEA_TOWN_KURT, DIR_EAST
	return

AzaleaTown_KurtsHouse_EventScript_SingularBall::
	bufferitemname STR_VAR_1, VAR_0x8004
	msgbox KurtsHouse_Text_KurtFinishedSingular, MSGBOX_DEFAULT
	message KurtsHouse_Text_KurtObtainedSingular
	waitmessage
	playfanfare MUS_OBTAIN_ITEM
	waitfanfare
	additem VAR_0x8004, VAR_0x8005
	msgbox KurtsHouse_Text_KurtTurnedOutGreat, MSGBOX_DEFAULT
	closemessage
	turnobject LOCALID_AZALEA_TOWN_KURT, DIR_NORTH
	release
	end

AzaleaTown_KurtsHouse_EventScript_KurtCancel::
	closemessage
	turnobject LOCALID_AZALEA_TOWN_KURT, DIR_NORTH
	release
	end

AzaleaTown_KurtsHouse_EventScript_KurtGsBall::
	msgbox KurtsHouse_Text_KurtWhatIsThat, MSGBOX_DEFAULT
	closemessage
	removeitem ITEM_GS_BALL
	playse SE_BANG
	applymovement LOCALID_AZALEA_TOWN_KURT, AzaleaTownKurt_Movement_Making_Ball
	waitmovement 0
	playse SE_BANG
	applymovement LOCALID_AZALEA_TOWN_KURT, AzaleaTownKurt_Movement_Making_Ball
	waitmovement 0
	faceplayer
	msgbox KurtsHouse_Text_KurtThisBallStartedToShake, MSGBOX_DEFAULT
	closemessage
	playse SE_M_PETAL_DANCE
	waitse
	playse SE_PIN
	applymovement LOCALID_AZALEA_TOWN_KURT, J_Common_Movement_ExclamationMark
	applymovement OBJ_EVENT_ID_PLAYER, J_Common_Movement_ExclamationMark
	waitmovement OBJ_EVENT_ID_PLAYER
	waitse
	playse SE_M_PETAL_DANCE
	waitse
	applymovement LOCALID_AZALEA_TOWN_KURT, AzaleaTownKurt_Movement_Look_Around
	applymovement OBJ_EVENT_ID_PLAYER, AzaleaTownKurt_Movement_Look_Around
	waitmovement 0
	waitmovement 0

AzaleaTown_KurtsHouse_EventScript_KurtGsBall2::
	msgbox KurtsHouse_Text_Kurt_Whatwasthat, MSGBOX_DEFAULT
	setvar JOHTO_VAR_AZALEA_TOWN_STATE, 8
	closemessage
	release
	end

AzaleaTown_KurtsHouse_EventScript_KurtGsBall3::
	msgbox KurtsHouse_Text_Forest, MSGBOX_DEFAULT
	closemessage
	delay 30
	msgbox KurtsHouse_Text_BallAnyway, MSGBOX_DEFAULT
	closemessage
	goto AzaleaTown_KurtsHouse_EventScript_Kurt2
	release
	end

KurtsHouse_Text_BallAnyway:
	.string "Anyway{SE_M_SUPERSONIC}ca{SE_M_ATTRACT}{SE_M_HEAL_BELL}mak{SE_M_REVERSAL}yo{SE_M_DIVE}som{SE_M_REVERSAL}BALLS?$"

AzaleaTown_KurtsHouse_EventScript_OakPhoto::
	msgbox KurtsHouse_Text_OakPhoto, MSGBOX_SIGN
	closemessage
	end

AzaleaTown_KurtsHouse_EventScript_CelebiStatue::
	msgbox KurtsHouse_Text_CelebiStatue, MSGBOX_SIGN
	closemessage
	end

AzaleaTownKurt_Movement_Look_Around:
	face_left
	delay_8
	face_right
	delay_8
	face_up
	delay_8
	face_down
	delay_8
	face_left
	step_end

AzaleaTownKurt_Movement_Making_Ball:
	face_up
	walk_in_place_fast_up
	delay_8
	walk_in_place_fast_up
	delay_8
	walk_in_place_fast_up
	step_end

AzaleaTown_KurtsHouse_Movement_Player:
	face_right
	lock_facing_direction
	walk_left
	unlock_facing_direction
	step_end

AzaleaTown_KurtsHouse_Movement_KurtWalkDown:
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	step_end

KurtsHouse_Text_KurtGetStarted:
	.string "KURT{SE_M_HEAT_WAVE}I'l{SE_M_BATON_PASS}ge{SE_M_SPIT_UP}starte{SE_M_WATERFALL}righ{SE_M_SPIT_UP}now!$"

KurtsHouse_Text_KurtMakingBallsMustWait:
	.string "Hm{SE_M_SING}Wh{SE_M_ATTRACT2}ar{SE_M_REVERSAL}you?\p"
	.string "{PLAYER}{SE_M_SUPERSONIC}eh{SE_M_SING}Yo{SE_M_DIVE}wan{SE_M_SPIT_UP}m{SE_M_REVERSAL}t{SE_M_ATTRACT2}make\n"
	.string "som{SE_M_REVERSAL}BALLS?\p"
	.string "Sorry{SE_M_SUPERSONIC}bu{SE_M_SPIT_UP}that'l{SE_M_BATON_PASS}hav{SE_M_REVERSAL}t{SE_M_ATTRACT2}wait.\p"
	.string "D{SE_M_ATTRACT2}yo{SE_M_DIVE}kno{SE_M_TWISTER}TEA{SE_M_GIGA_DRAIN}ROCKET?\n"
	.string "Ah{SE_M_SUPERSONIC}don'{SE_M_SPIT_UP}worry.\p"
	.string "I'l{SE_M_BATON_PASS}tel{SE_M_BATON_PASS}yo{SE_M_DIVE}anyhow.\p"
	.string "TEA{SE_M_GIGA_DRAIN}ROCKET'{SE_M_GRASSWHISTLE}a{SE_M_ATTRACT}evi{SE_M_BATON_PASS}gan{SE_M_SANDSTORM}that\n"
	.string "use{SE_M_GRASSWHISTLE}POKéMO{SE_M_PSYBEAM2}fo{SE_M_SAND_TOMB}thei{SE_M_SAND_TOMB}dirt{SE_M_YAWN}work.\p"
	.string "They'r{SE_M_REVERSAL}suppose{SE_M_WATERFALL}t{SE_M_ATTRACT2}hav{SE_M_REVERSAL}disbanded\n"
	.string "thre{SE_M_REVERSAL}year{SE_M_GRASSWHISTLE}ago.\p"
	.string "Anyway{SE_M_SUPERSONIC}they'r{SE_M_REVERSAL}a{SE_M_SPIT_UP}th{SE_M_REVERSAL}WELL,\n"
	.string "cuttin{SE_M_SANDSTORM}of{SE_M_ACID_ARMOR}SLOWPOKETAIL{SE_M_SKETCH}t{SE_M_ATTRACT2}sell!\p"
	.string "S{SE_M_ATTRACT2}I'{SE_M_MILK_DRINK}goin{SE_M_SANDSTORM}t{SE_M_ATTRACT2}g{SE_M_ATTRACT2}giv{SE_M_REVERSAL}the{SE_M_MILK_DRINK}a\n"
	.string "lesso{SE_M_ATTRACT}i{SE_M_ATTRACT}pain!\p"
	.string "Han{SE_M_SANDSTORM}on{SE_M_SUPERSONIC}SLOWPOKE{SE_M_DRAGON_RAGE}Ol{SE_M_WATERFALL}KURT\n"
	.string "i{SE_M_GRASSWHISTLE}o{SE_M_ATTRACT}hi{SE_M_GRASSWHISTLE}way!$"

KurtsHouse_Text_KurtHonoredToMakeBalls:
	.string "KURT{SE_M_HEAT_WAVE}Hi{SE_M_SUPERSONIC}{PLAYER}!\p"
	.string "Yo{SE_M_DIVE}handle{SE_M_WATERFALL}yoursel{SE_M_ACID_ARMOR}lik{SE_M_REVERSAL}a\n"
	.string "rea{SE_M_BATON_PASS}her{SE_M_ATTRACT2}a{SE_M_SPIT_UP}th{SE_M_REVERSAL}WELL.\p"
	.string "{SE_M_HEAL_BELL}lik{SE_M_REVERSAL}you{SE_M_SAND_TOMB}style!\p"
	.string "{SE_M_HEAL_BELL}woul{SE_M_WATERFALL}b{SE_M_REVERSAL}honore{SE_M_WATERFALL}t{SE_M_ATTRACT2}make\n"
	.string "BALL{SE_M_SKETCH}fo{SE_M_SAND_TOMB}{SE_M_CHARGE}traine{SE_M_SAND_TOMB}lik{SE_M_REVERSAL}you.\p"
	.string "Thi{SE_M_GRASSWHISTLE}i{SE_M_GRASSWHISTLE}al{SE_M_BATON_PASS}{SE_M_HEAL_BELL}hav{SE_M_REVERSAL}now{SE_M_SUPERSONIC}\n"
	.string "bu{SE_M_SPIT_UP}tak{SE_M_REVERSAL}it.$"

KurtsHouse_Text_KurtBallsFromApricorns:
	.string "KURT{SE_M_HEAT_WAVE}{SE_M_HEAL_BELL}mak{SE_M_REVERSAL}BALL{SE_M_SKETCH}fro{SE_M_MILK_DRINK}BERRIES.\p"
	.string "Collec{SE_M_SPIT_UP}the{SE_M_MILK_DRINK}fro{SE_M_MILK_DRINK}tree{SE_M_GRASSWHISTLE}an{SE_M_WATERFALL}bring\n"
	.string "'e{SE_M_MILK_DRINK}t{SE_M_ATTRACT2}me.\p"
	.string "I'l{SE_M_BATON_PASS}mak{SE_M_REVERSAL}POK{SE_U}BALL{SE_M_SKETCH}ou{SE_M_SPIT_UP}o{SE_M_ACID_ARMOR}them.$"

KurtsHouse_Text_KurtAskYouHaveAnApricorn:
	.string "KURT{SE_M_HEAT_WAVE}Yo{SE_M_DIVE}hav{SE_M_REVERSAL}BERRIE{SE_M_SKETCH}fo{SE_M_SAND_TOMB}me?\p"
	.string "Fine{SE_M_DRAGON_RAGE}I'l{SE_M_BATON_PASS}tur{SE_M_ATTRACT}the{SE_M_MILK_DRINK}int{SE_M_ATTRACT2}POK{SE_U}BALLS.$"

KurtsHouse_Text_KurtThatsALetdown:
	.string "KURT{SE_M_HEAT_WAVE}{SE_M_HEAL_BELL}don'{SE_M_SPIT_UP}se{SE_M_REVERSAL}an{SE_M_YAWN}{STR_VAR_1}s!$"

KurtsHouse_Text_KurtFinishedPlural:
	.string "KURT{SE_M_HEAT_WAVE}{PLAYER}!\n"
	.string "You{SE_M_SAND_TOMB}{STR_VAR_1}{SE_M_GRASSWHISTLE}ar{SE_M_REVERSAL}done{SE_M_PERISH_SONG}Here!$"

KurtsHouse_Text_KurtObtainedPlural:
	.string "{PLAYER} obtained\n"
	.string "{STR_VAR_2} {STR_VAR_1}s!$"

KurtsHouse_Text_KurtFinishedSingular:
	.string "KURT{SE_M_HEAT_WAVE}{PLAYER}!\n"
	.string "You{SE_M_SAND_TOMB}{STR_VAR_1} i{SE_M_GRASSWHISTLE}done{SE_M_PERISH_SONG}Here!$"

KurtsHouse_Text_KurtObtainedSingular:
	.string "{PLAYER} obtained\n"
	.string "th{SE_M_REVERSAL}{STR_VAR_1}!$"

KurtsHouse_Text_KurtTurnedOutGreat:
	.string "KURT{SE_M_HEAT_WAVE}Tha{SE_M_SPIT_UP}turne{SE_M_WATERFALL}ou{SE_M_SPIT_UP}great.\p"
	.string "Tr{SE_M_YAWN}catchin{SE_M_SANDSTORM}POKéMO{SE_M_PSYBEAM2}wit{SE_M_TRI_ATTACK}it.$"

KurtsHouse_Text_KurtWhatIsThat:
	.string "Wh-wha{SE_M_SPIT_UP}i{SE_M_GRASSWHISTLE}that?\p"
	.string "I'v{SE_M_REVERSAL}neve{SE_M_SAND_TOMB}see{SE_M_ATTRACT}on{SE_M_REVERSAL}before.\p"
	.string "I{SE_M_SPIT_UP}look{SE_M_GRASSWHISTLE}{SE_M_CHARGE}lik{SE_M_REVERSAL}{SE_M_CHARGE}POK{SE_U}BALL{SE_M_SUPERSONIC}but\n"
	.string "i{SE_M_SPIT_UP}appear{SE_M_GRASSWHISTLE}t{SE_M_ATTRACT2}b{SE_M_REVERSAL}somethin{SE_M_SANDSTORM}else.\p"
	.string "Le{SE_M_SPIT_UP}m{SE_M_REVERSAL}chec{SE_M_ENCORE2}i{SE_M_SPIT_UP}fo{SE_M_SAND_TOMB}you.$"

KurtsHouse_Text_KurtImCheckingItNow:
	.string "I'{SE_M_MILK_DRINK}checkin{SE_M_SANDSTORM}i{SE_M_SPIT_UP}now.$"

KurtsHouse_Text_KurtAhHaISee:
	.string "Ah-ha{SE_M_DRAGON_RAGE}{SE_M_HEAL_BELL}see{SE_M_DRAGON_RAGE}So…$"

KurtsHouse_Text_KurtThisBallStartedToShake:
	.string "{PLAYER}!\p"
	.string "Thi{SE_M_GRASSWHISTLE}BAL{SE_M_BRICK_BREAK}starte{SE_M_WATERFALL}t{SE_M_ATTRACT2}shake\n"
	.string "whil{SE_M_REVERSAL}{SE_M_HEAL_BELL}wa{SE_M_GRASSWHISTLE}checkin{SE_M_SANDSTORM}it.\p"
	.string "Ther{SE_M_REVERSAL}mus{SE_M_SPIT_UP}b{SE_M_REVERSAL}somethin{SE_M_SANDSTORM}t{SE_M_ATTRACT2}this!$"

KurtsHouse_Text_Kurt_Whatwasthat:
	.string "Wha{SE_M_SPIT_UP}wa{SE_M_GRASSWHISTLE}tha{SE_M_SPIT_UP}sound?!\p"
	.string "Let'{SE_M_GRASSWHISTLE}g{SE_M_ATTRACT2}outsid{SE_M_REVERSAL}t{SE_M_ATTRACT2}investigate!$"

KurtsHouse_Text_GranddaughterSlowpokeGone:
	.string "Th{SE_M_REVERSAL}SLOWPOK{SE_M_SWORDS_DANCE}ar{SE_M_REVERSAL}gone{SE_M_DIZZY_PUNCH}\n"
	.string "Wer{SE_M_REVERSAL}the{SE_M_YAWN}take{SE_M_ATTRACT}awa{SE_M_YAWN}b{SE_M_YAWN}ba{SE_M_WATERFALL}people?$"

KurtsHouse_Text_GranddaughterLonely:
	.string "Grandpa'{SE_M_GRASSWHISTLE}gone{SE_M_DIZZY_PUNCH}I'{SE_M_MILK_DRINK}s{SE_M_ATTRACT2}lonely…$"

KurtsHouse_Text_GranddaughterSlowpokeBack:
	.string "Th{SE_M_REVERSAL}SLOWPOK{SE_M_SWORDS_DANCE}m{SE_M_YAWN}da{SE_M_WATERFALL}gav{SE_M_REVERSAL}m{SE_M_REVERSAL}cam{SE_M_REVERSAL}back!\p"
	.string "It{SE_M_GRASSWHISTLE}TAI{SE_M_BRICK_BREAK}i{SE_M_GRASSWHISTLE}growin{SE_M_SANDSTORM}bac{SE_M_ENCORE2}too!$"

KurtsHouse_Text_GranddaughterDad:
	.string "Da{SE_M_WATERFALL}work{SE_M_GRASSWHISTLE}a{SE_M_SPIT_UP}SILP{SE_M_SWAGGER2}where\n"
	.string "h{SE_M_REVERSAL}studie{SE_M_GRASSWHISTLE}POK{SE_U}BALLS.\p"
	.string "{SE_M_HEAL_BELL}hav{SE_M_REVERSAL}t{SE_M_ATTRACT2}sta{SE_M_YAWN}home\n"
	.string "wit{SE_M_TRI_ATTACK}Grandp{SE_M_CHARGE}an{SE_M_WATERFALL}SLOWPOKE.$"

KurtsHouse_Text_GranddaughterHelp:
	.string "{SE_M_HEAL_BELL}ge{SE_M_SPIT_UP}t{SE_M_ATTRACT2}hel{SE_M_MORNING_SUN}Grandp{SE_M_CHARGE}now!\p"
	.string "We'l{SE_M_BATON_PASS}mak{SE_M_REVERSAL}goo{SE_M_WATERFALL}BALLS\n"
	.string "fo{SE_M_SAND_TOMB}you{SE_M_SUPERSONIC}s{SE_M_ATTRACT2}pleas{SE_M_REVERSAL}wait!$"

KurtsHouse_Text_GranddaughterFun:
	.string "It'{SE_M_GRASSWHISTLE}fu{SE_M_ATTRACT}t{SE_M_ATTRACT2}mak{SE_M_REVERSAL}BALLS!$"

KurtsHouse_Text_GranddaughterSound:
	.string "Di{SE_M_WATERFALL}tha{SE_M_SPIT_UP}soun{SE_M_WATERFALL}com{SE_M_REVERSAL}from\n"
	.string "ILE{SE_M_LOCK_ON}FOREST????$"

KurtsHouse_Text_Forest:
	.string "Di{SE_M_WATERFALL}yo{SE_M_DIVE}chec{SE_M_ENCORE2}ILE{SE_M_LOCK_ON}FORES{SE_M_SWIFT}yet?\n"
	.string "I{SE_M_SPIT_UP}sound{SE_M_GRASSWHISTLE}ver{SE_M_YAWN}restless.$"

KurtsHouse_Text_Slowpoke:
	.string "SLOWPOKE{SE_M_HEAT_WAVE}{SE_M_DIZZY_PUNCH}Yawn?$"

KurtsHouse_Text_OakPhoto:
	.string "…{SE_M_BONEMERANG}youn{SE_M_SANDSTORM}PROF{SE_M_PERISH_SONG}OAK?$"

KurtsHouse_Text_CelebiStatue:
	.string "It'{SE_M_GRASSWHISTLE}{SE_M_CHARGE}statu{SE_M_REVERSAL}o{SE_M_ACID_ARMOR}th{SE_M_REVERSAL}forest's\n"
	.string "protector.$"

