@ Johto (data/maps/OlivineCity_Gym_hns/scripts.inc), as built into the FireRed game.

OlivineCity_Gym_hns_MapScripts::
	.byte 0

OlivineCity_Gym_EventScript_Gent::
	lock
	faceplayer
	goto_if_set JOHTO_FLAG_DEFEATED_OLIVINE_CITY_GYM, OlivineCity_Gym_EventScript_Gent2
	msgbox OlivineCity_Gym_Text_Gent, MSGBOX_DEFAULT
	closemessage
	release
	end

OlivineCity_Gym_EventScript_Gent2::
	msgbox OlivineCity_Gym_Text_Gent2, MSGBOX_DEFAULT
	closemessage
	release
	end

OlivineCity_Gym_TriggerRow1::
	lock
	setvar VAR_TEMP_0, LOCALID_OLIVINE_CITY_GYM_NPC1
	playse SE_PIN
	applymovement VAR_TEMP_0, J_Common_Movement_ExclamationMark
	waitmovement VAR_TEMP_0
	getplayerxy VAR_TEMP_1, VAR_TEMP_2
	call_if_eq VAR_TEMP_1, 6, OlivineCity_Gym_EventScript_MoveLeft4
	call_if_eq VAR_TEMP_1, 7, OlivineCity_Gym_EventScript_MoveLeft3
	call_if_eq VAR_TEMP_1, 8, OlivineCity_Gym_EventScript_MoveLeft2
	call_if_eq VAR_TEMP_1, 9, OlivineCity_Gym_EventScript_MoveLeft1
	call_if_eq VAR_TEMP_1, 10, OlivineCity_Gym_EventScript_MoveLeft0
	turnobject OBJ_EVENT_ID_PLAYER, DIR_EAST
	msgbox OlivineCity_Gym_Text_Gent, MSGBOX_DEFAULT
	closemessage
	setvar JOHTO_VAR_OLIVINE_CITY_STATE, 6
	release
	end

OlivineCity_Gym_EventScript_MoveLeft0::
	turnobject VAR_TEMP_0, DIR_WEST
	return

OlivineCity_Gym_EventScript_MoveLeft1::
	applymovement VAR_TEMP_0, J_Common_Movement_WalkLeft1
	waitmovement 0
	return

OlivineCity_Gym_EventScript_MoveLeft2::
	applymovement VAR_TEMP_0, J_Common_Movement_WalkLeft1
	waitmovement 0
	applymovement VAR_TEMP_0, J_Common_Movement_WalkLeft1
	waitmovement 0
	return

OlivineCity_Gym_EventScript_MoveLeft3::
	applymovement VAR_TEMP_0, J_Common_Movement_WalkLeft1
	waitmovement 0
	applymovement VAR_TEMP_0, J_Common_Movement_WalkLeft1
	waitmovement 0
	applymovement VAR_TEMP_0, J_Common_Movement_WalkLeft1
	waitmovement 0
	return

OlivineCity_Gym_EventScript_MoveLeft4::
	applymovement VAR_TEMP_0, J_Common_Movement_WalkLeft1
	waitmovement 0
	applymovement VAR_TEMP_0, J_Common_Movement_WalkLeft1
	waitmovement 0
	applymovement VAR_TEMP_0, J_Common_Movement_WalkLeft1
	waitmovement 0
	applymovement VAR_TEMP_0, J_Common_Movement_WalkLeft1
	waitmovement 0
	return

OlivineCity_Gym_Text_Gent:
	.string "{SE_M_HEAL_BELL}kne{SE_M_TWISTER}you'{SE_M_WATERFALL}com{SE_M_REVERSAL}here.\p"
	.string "Than{SE_M_ENCORE2}yo{SE_M_DIVE}fo{SE_M_SAND_TOMB}helpin{SE_M_SANDSTORM}th{SE_M_REVERSAL}GY{SE_M_GIGA_DRAIN}LEADER,\n"
	.string "bu{SE_M_SPIT_UP}battl{SE_M_REVERSAL}i{SE_M_GRASSWHISTLE}{SE_M_CHARGE}separat{SE_M_REVERSAL}matter.\p"
	.string "G{SE_M_ATTRACT2}fo{SE_M_SAND_TOMB}it!$"

OlivineCity_Gym_Text_Gent2:
	.string "Impressive!\n"
	.string "Yo{SE_M_DIVE}shoul{SE_M_WATERFALL}continu{SE_M_REVERSAL}you{SE_M_SAND_TOMB}journe{SE_M_YAWN}to\l"
	.string "differen{SE_M_SPIT_UP}places.\p"
	.string "Sinc{SE_M_REVERSAL}yo{SE_M_DIVE}ca{SE_M_ATTRACT}us{SE_M_REVERSAL}SURF{SE_M_SUPERSONIC}wh{SE_M_YAWN}don'{SE_M_SPIT_UP}you\n"
	.string "tr{SE_M_YAWN}i{SE_M_SPIT_UP}o{SE_M_ATTRACT}th{SE_M_REVERSAL}LAK{SE_M_SWORDS_DANCE}O{SE_M_LEER}RAGE?$"

OlivineCity_Gym_EventScript_Lass::
	lock
	faceplayer
	goto_if_set JOHTO_FLAG_DEFEATED_OLIVINE_CITY_GYM, OlivineCity_Gym_EventScript_Lass2
	msgbox OlivineCity_Gym_Text_Lass, MSGBOX_DEFAULT
	closemessage
	release
	end

OlivineCity_Gym_EventScript_Lass2::
	msgbox OlivineCity_Gym_Text_Lass2, MSGBOX_DEFAULT
	closemessage
	release
	end

OlivineCity_Gym_TriggerRow2::
	lock
	setvar VAR_TEMP_0, LOCALID_OLIVINE_CITY_GYM_NPC2
	playse SE_PIN
	applymovement VAR_TEMP_0, J_Common_Movement_ExclamationMark
	waitmovement VAR_TEMP_0
	getplayerxy VAR_TEMP_1, VAR_TEMP_2
	call_if_eq VAR_TEMP_1, 6, OlivineCity_Gym_EventScript_MoveRight0
	call_if_eq VAR_TEMP_1, 7, OlivineCity_Gym_EventScript_MoveRight1
	call_if_eq VAR_TEMP_1, 8, OlivineCity_Gym_EventScript_MoveRight2
	call_if_eq VAR_TEMP_1, 9, OlivineCity_Gym_EventScript_MoveRight3
	call_if_eq VAR_TEMP_1, 10, OlivineCity_Gym_EventScript_MoveRight4
	turnobject OBJ_EVENT_ID_PLAYER, DIR_WEST
	msgbox OlivineCity_Gym_Text_Lass, MSGBOX_DEFAULT
	closemessage
	setvar JOHTO_VAR_OLIVINE_CITY_STATE, 7
	release
	end

OlivineCity_Gym_EventScript_MoveRight0::
	turnobject VAR_TEMP_0, DIR_EAST
	return

OlivineCity_Gym_EventScript_MoveRight1::
	applymovement VAR_TEMP_0, J_Common_Movement_WalkRight1
	waitmovement 0
	return

OlivineCity_Gym_EventScript_MoveRight2::
	applymovement VAR_TEMP_0, J_Common_Movement_WalkRight1
	waitmovement 0
	applymovement VAR_TEMP_0, J_Common_Movement_WalkRight1
	waitmovement 0
	return

OlivineCity_Gym_EventScript_MoveRight3::
	applymovement VAR_TEMP_0, J_Common_Movement_WalkRight1
	waitmovement 0
	applymovement VAR_TEMP_0, J_Common_Movement_WalkRight1
	waitmovement 0
	applymovement VAR_TEMP_0, J_Common_Movement_WalkRight1
	waitmovement 0
	return

OlivineCity_Gym_EventScript_MoveRight4::
	applymovement VAR_TEMP_0, J_Common_Movement_WalkRight1
	waitmovement 0
	applymovement VAR_TEMP_0, J_Common_Movement_WalkRight1
	waitmovement 0
	applymovement VAR_TEMP_0, J_Common_Movement_WalkRight1
	waitmovement 0
	applymovement VAR_TEMP_0, J_Common_Movement_WalkRight1
	waitmovement 0
	return

OlivineCity_Gym_Text_Lass:
	.string "Giggle...\n"
	.string "{SE_M_HEAL_BELL}kno{SE_M_TWISTER}ho{SE_M_TWISTER}capabl{SE_M_REVERSAL}yo{SE_M_DIVE}are\l"
	.string "fro{SE_M_MILK_DRINK}th{SE_M_REVERSAL}LIGHTHOUSE.\p"
	.string "It'{SE_M_GRASSWHISTLE}tim{SE_M_REVERSAL}yo{SE_M_DIVE}showe{SE_M_WATERFALL}tha{SE_M_SPIT_UP}sid{SE_M_REVERSAL}of\n"
	.string "yoursel{SE_M_ACID_ARMOR}t{SE_M_ATTRACT2}JASMINE{SE_M_DRAGON_RAGE}Goo{SE_M_WATERFALL}luck!$"

OlivineCity_Gym_Text_Lass2:
	.string "Yo{SE_M_DIVE}ar{SE_M_REVERSAL}amazing...\n"
	.string "Yo{SE_M_DIVE}shoul{SE_M_WATERFALL}ai{SE_M_MILK_DRINK}eve{SE_M_ATTRACT}higher{SE_M_SUPERSONIC}since\l"
	.string "yo{SE_M_DIVE}hav{SE_M_REVERSAL}suc{SE_M_TRI_ATTACK}potential.\p"
	.string "Hav{SE_M_REVERSAL}yo{SE_M_DIVE}bee{SE_M_ATTRACT}t{SE_M_ATTRACT2}MAHOGAN{SE_M_MOONLIGHT}TOWN?$"

OlivineCity_Gym_EventScript_GymGuide::
	lock
	faceplayer
	goto_if_lt JOHTO_VAR_OLIVINE_CITY_STATE, 5, OlivineCity_Gym_EventScript_GymGuideSick
	goto_if_set JOHTO_FLAG_DEFEATED_OLIVINE_CITY_GYM, OlivineCity_Gym_EventScript_GymGuideAfter
	msgbox OlivineCity_Gym_Text_GymGuideText, MSGBOX_DEFAULT
	closemessage
	release
	end

OlivineCity_Gym_EventScript_GymGuideSick::
	msgbox OlivineCity_Gym_Text_GymGuidePreText, MSGBOX_DEFAULT
	closemessage
	release
	end

OlivineCity_Gym_EventScript_GymGuideAfter::
	msgbox OlivineCity_Gym_Text_GymGuideWinText, MSGBOX_DEFAULT
	closemessage
	release
	end

OlivineCity_Gym_Text_GymGuideText:
	.string "JASMIN{SE_M_SWORDS_DANCE}use{SE_M_GRASSWHISTLE}th{SE_M_REVERSAL}newl{SE_M_YAWN}discovered\n"
	.string "STEEL-type.\p"
	.string "She'{SE_M_GRASSWHISTLE}know{SE_M_ATTRACT}fo{SE_M_SAND_TOMB}havin{SE_M_SANDSTORM}no{SE_M_SPIT_UP}one,\n"
	.string "bu{SE_M_SPIT_UP}tw{SE_M_ATTRACT2}aces.\p"
	.string "Th{SE_M_REVERSAL}firs{SE_M_SPIT_UP}i{SE_M_GRASSWHISTLE}{SE_M_CHARGE}meta{SE_M_BATON_PASS}bu{SE_M_SANDSTORM}tha{SE_M_SPIT_UP}can\n"
	.string "us{SE_M_REVERSAL}{SE_M_CHARGE}techniqu{SE_M_REVERSAL}t{SE_M_ATTRACT2}boos{SE_M_SPIT_UP}it{SE_M_GRASSWHISTLE}ATTACK.\p"
	.string "Whil{SE_M_REVERSAL}fir{SE_M_REVERSAL}wil{SE_M_BATON_PASS}hur{SE_M_SPIT_UP}it{SE_M_SUPERSONIC}i{SE_M_SPIT_UP}can\n"
	.string "sometime{SE_M_GRASSWHISTLE}endur{SE_M_REVERSAL}powerfu{SE_M_BATON_PASS}blows.\p"
	.string "Th{SE_M_REVERSAL}secon{SE_M_WATERFALL}i{SE_M_GRASSWHISTLE}{SE_M_CHARGE}gian{SE_M_SPIT_UP}iro{SE_M_ATTRACT}snake\n"
	.string "wit{SE_M_TRI_ATTACK}lot{SE_M_GRASSWHISTLE}o{SE_M_ACID_ARMOR}powerfu{SE_M_BATON_PASS}moves.\p"
	.string "Approac{SE_M_TRI_ATTACK}i{SE_M_SPIT_UP}wit{SE_M_TRI_ATTACK}caution.\p"
	.string "I{SE_M_SPIT_UP}ma{SE_M_YAWN}loo{SE_M_ENCORE2}slow{SE_M_SUPERSONIC}bu{SE_M_SPIT_UP}I'v{SE_M_REVERSAL}see{SE_M_ATTRACT}it\n"
	.string "strik{SE_M_REVERSAL}firs{SE_M_SPIT_UP}wit{SE_M_TRI_ATTACK}shockin{SE_M_SANDSTORM}displays\l"
	.string "o{SE_M_ACID_ARMOR}SPEED.$"

OlivineCity_Gym_Text_GymGuideWinText:
	.string "Tha{SE_M_SPIT_UP}wa{SE_M_GRASSWHISTLE}awesome.\p"
	.string "Th{SE_M_REVERSAL}STEEL-type{SE_M_SUPERSONIC}huh?\p"
	.string "Tha{SE_M_SPIT_UP}wa{SE_M_GRASSWHISTLE}{SE_M_CHARGE}clos{SE_M_REVERSAL}encounte{SE_M_SAND_TOMB}o{SE_M_ACID_ARMOR}an\n"
	.string "unknow{SE_M_ATTRACT}kind!$"

OlivineCity_Gym_Text_GymGuidePreText:
	.string "JASMINE{SE_M_SUPERSONIC}th{SE_M_REVERSAL}GY{SE_M_GIGA_DRAIN}LEADER{SE_M_SUPERSONIC}i{SE_M_GRASSWHISTLE}a{SE_M_SPIT_UP}the\n"
	.string "LIGHTHOUSE.\p"
	.string "She'{SE_M_GRASSWHISTLE}bee{SE_M_ATTRACT}tendin{SE_M_SANDSTORM}t{SE_M_ATTRACT2}{SE_M_CHARGE}sic{SE_M_ENCORE2}POKéMON.\p"
	.string "{SE_M_BONEMERANG}stron{SE_M_SANDSTORM}traine{SE_M_SAND_TOMB}ha{SE_M_GRASSWHISTLE}t{SE_M_ATTRACT2}be\n"
	.string "compassionate.$"

OlivineCity_Gym_EventScript_Jasmine::
	lock
	faceplayer
	goto_if_set JOHTO_FLAG_DEFEATED_OLIVINE_CITY_GYM, OlivineCity_Gym_EventScript_Jasmine_Defeated
	msgbox OlivineCity_Gym_Text_JasmineSteelTypeIntro, MSGBOX_DEFAULT
	goto_if_set JOHTO_FLAG_DEFEATED_CIANWOOD_GYM, OlivineCity_Gym_EventScript_CianwoodCheckMahog
	goto_if_set JOHTO_FLAG_DEFEATED_MAHOGANY_TOWN_GYM, OlivineCity_Gym_EventScript_MahogCheckCianwood
	goto OlivineCity_Gym_EventScript_Jasmine_Battle1

OlivineCity_Gym_EventScript_JasmineVictory::
	message OlivineCity_Gym_Text_ReceivedMineralBadge
	waitmessage
	call J_Common_EventScript_PlayGymBadgeFanfare
	msgbox OlivineCity_Gym_Text_JasmineBadgeSpeech, MSGBOX_DEFAULT
	setflag JOHTO_FLAG_BADGE06_GET
	setflag JOHTO_FLAG_DEFEATED_OLIVINE_CITY_GYM
	addvar JOHTO_VAR_NUM_BADGES, 1
	setvar VAR_0x8008, 6
	call J_Common_EventScript_SetGymTrainers_hns
	giveitem ITEM_TM_IRON_TAIL
	msgbox OlivineCity_Gym_Text_JasmineIronTailSpeech, MSGBOX_DEFAULT
	setvar JOHTO_VAR_OLIVINE_CITY_STATE, 8
	setrespawn JOHTO_HEAL_LOCATION_OLIVINE_CITY_HNS
	call_if_eq JOHTO_VAR_NUM_BADGES, 7, MahoganyTown_Gym_EventScript_SetupElmRocketCall
	closemessage
	release
	end

OlivineCity_Gym_EventScript_CianwoodCheckMahog::
	goto_if_set JOHTO_FLAG_DEFEATED_MAHOGANY_TOWN_GYM, OlivineCity_Gym_EventScript_Jasmine_Battle3
	goto OlivineCity_Gym_EventScript_Jasmine_Battle2

OlivineCity_Gym_EventScript_MahogCheckCianwood::
	goto_if_set JOHTO_FLAG_DEFEATED_CIANWOOD_GYM, OlivineCity_Gym_EventScript_Jasmine_Battle3
	goto OlivineCity_Gym_EventScript_Jasmine_Battle2

OlivineCity_Gym_EventScript_Jasmine_Battle1::
	trainerbattle_no_intro TRAINER_JOHTO_JASMINE_1_HNS, OlivineCity_Gym_Text_JasmineBetterTrainer
	goto OlivineCity_Gym_EventScript_JasmineVictory

OlivineCity_Gym_EventScript_Jasmine_Battle2::
	trainerbattle_no_intro TRAINER_JOHTO_JASMINE_1_2_HNS, OlivineCity_Gym_Text_JasmineBetterTrainer
	goto OlivineCity_Gym_EventScript_JasmineVictory

OlivineCity_Gym_EventScript_Jasmine_Battle3::
	trainerbattle_no_intro TRAINER_JOHTO_JASMINE_1_3_HNS, OlivineCity_Gym_Text_JasmineBetterTrainer
	goto OlivineCity_Gym_EventScript_JasmineVictory

OlivineCity_Gym_EventScript_Jasmine_Defeated::
	goto_if_unset JOHTO_FLAG_HIDE_DOJO_JASMINE, OlivineCity_Gym_EventScript_Jasmine_Trade
	msgbox OlivineCity_Gym_Text_JasmineGoodLuck, MSGBOX_DEFAULT
	closemessage
	release
	end

OlivineCity_Gym_Text_JasmineSteelTypeIntro:
	.string "…Than{SE_M_ENCORE2}yo{SE_M_DIVE}fo{SE_M_SAND_TOMB}you{SE_M_SAND_TOMB}hel{SE_M_MORNING_SUN}a{SE_M_SPIT_UP}the\n"
	.string "LIGHTHOUSE…\p"
	.string "Bu{SE_M_SPIT_UP}thi{SE_M_GRASSWHISTLE}i{SE_M_GRASSWHISTLE}different.\n"
	.string "Pleas{SE_M_REVERSAL}allo{SE_M_TWISTER}m{SE_M_REVERSAL}t{SE_M_ATTRACT2}introduc{SE_M_REVERSAL}myself.\p"
	.string "{SE_M_HEAL_BELL}a{SE_M_MILK_DRINK}JASMINE{SE_M_SUPERSONIC}{SE_M_CHARGE}GY{SE_M_GIGA_DRAIN}LEADER.\n"
	.string "{SE_M_HEAL_BELL}us{SE_M_REVERSAL}th{SE_M_REVERSAL}STEEL-type.\p"
	.string "…D{SE_M_ATTRACT2}yo{SE_M_DIVE}kno{SE_M_TWISTER}abou{SE_M_SPIT_UP}th{SE_M_REVERSAL}STEEL-type?\p"
	.string "It'{SE_M_GRASSWHISTLE}{SE_M_CHARGE}typ{SE_M_REVERSAL}tha{SE_M_SPIT_UP}wa{SE_M_GRASSWHISTLE}onl{SE_M_YAWN}recently\n"
	.string "discovered.\p"
	.string "…Um{SE_M_DIZZY_PUNCH}Ma{SE_M_YAWN}{SE_M_HEAL_BELL}begin?$"

OlivineCity_Gym_Text_JasmineBetterTrainer:
	.string "…Yo{SE_M_DIVE}ar{SE_M_REVERSAL}{SE_M_CHARGE}bette{SE_M_SAND_TOMB}traine{SE_M_SAND_TOMB}tha{SE_M_ATTRACT}me,\n"
	.string "i{SE_M_ATTRACT}bot{SE_M_TRI_ATTACK}skil{SE_M_BATON_PASS}an{SE_M_WATERFALL}kindness.\p"
	.string "I{SE_M_ATTRACT}accordanc{SE_M_REVERSAL}wit{SE_M_TRI_ATTACK}LEAGU{SE_M_SWORDS_DANCE}rules,\n"
	.string "{SE_M_HEAL_BELL}confe{SE_M_SAND_TOMB}upo{SE_M_ATTRACT}yo{SE_M_DIVE}thi{SE_M_GRASSWHISTLE}BADGE.$"

OlivineCity_Gym_Text_ReceivedMineralBadge:
	.string "{PLAYER} receive{SE_M_WATERFALL}MINERALBADGE.$"

OlivineCity_Gym_Text_JasmineBadgeSpeech:
	.string "MINERALBADG{SE_M_SWORDS_DANCE}raise{SE_M_GRASSWHISTLE}POKéMON'{SE_M_GRASSWHISTLE}\n"
	.string "SPECIA{SE_M_BRICK_BREAK}DEFENSE.\p"
	.string "…Um{SE_M_DIZZY_PUNCH}Pleas{SE_M_REVERSAL}tak{SE_M_REVERSAL}thi{SE_M_GRASSWHISTLE}too…$"

OlivineCity_Gym_Text_JasmineIronTailSpeech:
	.string "…Yo{SE_M_DIVE}coul{SE_M_WATERFALL}us{SE_M_REVERSAL}tha{SE_M_SPIT_UP}T{SE_M_GIGA_DRAIN}t{SE_M_ATTRACT2}teach\n"
	.string "IRO{SE_M_PSYBEAM2}TAIL.$"

OlivineCity_Gym_Text_JasmineGoodLuck:
	.string "Um{SE_M_DIZZY_PUNCH}{SE_M_HEAL_BELL}don'{SE_M_SPIT_UP}kno{SE_M_TWISTER}ho{SE_M_TWISTER}t{SE_M_ATTRACT2}sa{SE_M_YAWN}this,\n"
	.string "bu{SE_M_SPIT_UP}goo{SE_M_WATERFALL}luck…$"

OlivineCity_Gym_Text_JasmineRematchText:
	.string "…Congratulations{SE_M_SUPERSONIC}JOHT{SE_M_SOLAR_BEAM}CHAMPION.\p"
	.string "Yo{SE_M_DIVE}hav{SE_M_REVERSAL}becom{SE_M_REVERSAL}s{SE_M_ATTRACT2}strong…\p"
	.string "{SE_M_HEAL_BELL}wonde{SE_M_SAND_TOMB}i{SE_M_ACID_ARMOR}{SE_M_HEAL_BELL}hav{SE_M_REVERSAL}improved.\p"
	.string "Woul{SE_M_WATERFALL}yo{SE_M_DIVE}lik{SE_M_REVERSAL}t{SE_M_ATTRACT2}tes{SE_M_SPIT_UP}that?\p"
	.string "Wan{SE_M_SPIT_UP}t{SE_M_ATTRACT2}hav{SE_M_REVERSAL}{SE_M_CHARGE}rematc{SE_M_TRI_ATTACK}wit{SE_M_TRI_ATTACK}me?$"

OlivineCity_Gym_Text_JasmineRematchDefeatText:
	.string "…Yo{SE_M_DIVE}ar{SE_M_REVERSAL}{SE_M_CHARGE}bette{SE_M_SAND_TOMB}traine{SE_M_SAND_TOMB}tha{SE_M_ATTRACT}me,\n"
	.string "i{SE_M_ATTRACT}bot{SE_M_TRI_ATTACK}skil{SE_M_BATON_PASS}an{SE_M_WATERFALL}kindness.$"

OlivineCity_Gym_EventScript_Statue::
	lock
	goto_if_set JOHTO_FLAG_DEFEATED_OLIVINE_CITY_GYM, OlivineCity_Gym_EventScript_Statue2
	msgbox OlivineCity_Gym_Text_GymStatue, MSGBOX_DEFAULT
	closemessage
	release
	end

OlivineCity_Gym_EventScript_Statue2::
	msgbox OlivineCity_Gym_Text_GymStatueCertified, MSGBOX_DEFAULT
	closemessage
	release
	end

OlivineCity_Gym_Text_GymStatue:
	.string "OLIVIN{SE_M_SWORDS_DANCE}CIT{SE_M_MOONLIGHT}POKéMO{SE_M_PSYBEAM2}GYM$"

OlivineCity_Gym_Text_GymStatueCertified:
	.string "OLIVIN{SE_M_SWORDS_DANCE}CIT{SE_M_MOONLIGHT}POKéMO{SE_M_PSYBEAM2}GYM\p"
	.string "JASMINE'{SE_M_SKETCH}CERTIFIE{SE_M_FAINT_ATTACK}TRAINERS:\n"
	.string "{PLAYER}$"

OlivineCity_Gym_EventScript_Jasmine_Trade::
	goto_if_set JOHTO_FLAG_OLIVINE_GYM_NPC_TRADE_COMPLETED, OlivineCity_Gym_EventScript_JasmineTradeCompleted
	setvar VAR_0x8005, INGAME_TRADE_STEELIX
	specialvar VAR_0x8009, GetInGameTradeSpeciesInfo
	msgbox OlivineCity_Gym_Text_JasmineWantToTrade, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, OlivineCity_Gym_EventScript_JasmineDeclineTrade
	chooseboxmon SELECT_PC_MON_TRADE
	waitstate
	goto_if_eq VAR_0x8004, PARTY_NOTHING_CHOSEN, OlivineCity_Gym_EventScript_JasmineDeclineTrade
	special CreateInGameTradePokemon
	special DoInGameTradeScene
	waitstate
	msgbox OlivineCity_Gym_Text_JasmineTakeCare, MSGBOX_DEFAULT
	setflag JOHTO_FLAG_OLIVINE_GYM_NPC_TRADE_COMPLETED
	release
	end

OlivineCity_Gym_EventScript_JasmineDeclineTrade::
	msgbox OlivineCity_Gym_Text_JasmineDeclineTrade, MSGBOX_DEFAULT
	release
	end

OlivineCity_Gym_EventScript_JasmineTradeCompleted::
	msgbox OlivineCity_Gym_Text_JasmineTradeCompleted, MSGBOX_DEFAULT
	release
	end

OlivineCity_Gym_Text_JasmineWantToTrade:
	.string "…Um{SE_M_SUPERSONIC}{PLAYER}…\n"
	.string "{SE_M_HEAL_BELL}hav{SE_M_REVERSAL}somethin{SE_M_SANDSTORM}t{SE_M_ATTRACT2}as{SE_M_ENCORE2}you.\p"
	.string "I'v{SE_M_REVERSAL}raise{SE_M_WATERFALL}thi{SE_M_GRASSWHISTLE}STEELI{SE_M_LOCK_ON}sinc{SE_M_REVERSAL}it\n"
	.string "wa{SE_M_GRASSWHISTLE}{SE_M_CHARGE}littl{SE_M_REVERSAL}ONIX.\p"
	.string "Bu{SE_M_SPIT_UP}{SE_M_HEAL_BELL}thin{SE_M_ENCORE2}RUST{SE_M_MOONLIGHT}woul{SE_M_WATERFALL}b{SE_M_REVERSAL}happier\n"
	.string "wit{SE_M_TRI_ATTACK}{SE_M_CHARGE}traine{SE_M_SAND_TOMB}lik{SE_M_REVERSAL}you.\p"
	.string "Woul{SE_M_WATERFALL}yo{SE_M_DIVE}trad{SE_M_REVERSAL}an{SE_M_YAWN}o{SE_M_ACID_ARMOR}your\n"
	.string "POKéMO{SE_M_PSYBEAM2}fo{SE_M_SAND_TOMB}m{SE_M_YAWN}RUSTY?$"

OlivineCity_Gym_Text_JasmineTakeCare:
	.string "…Than{SE_M_ENCORE2}you.\n"
	.string "Pleas{SE_M_REVERSAL}b{SE_M_REVERSAL}kin{SE_M_WATERFALL}t{SE_M_ATTRACT2}RUSTY…$"

OlivineCity_Gym_Text_JasmineDeclineTrade:
	.string "…Oh{SE_M_DIZZY_PUNCH}That'{SE_M_GRASSWHISTLE}okay.\n"
	.string "{SE_M_HEAL_BELL}understand…$"

OlivineCity_Gym_Text_JasmineTradeCompleted:
	.string "…Ho{SE_M_TWISTER}i{SE_M_GRASSWHISTLE}RUST{SE_M_MOONLIGHT}doing?\n"
	.string "{SE_M_HEAL_BELL}hop{SE_M_REVERSAL}you'r{SE_M_REVERSAL}takin{SE_M_SANDSTORM}goo{SE_M_WATERFALL}care…$"

