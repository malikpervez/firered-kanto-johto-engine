@ Johto (data/maps/Route27_hns/scripts.inc), as built into the FireRed game.

Route27_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route27_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, J_SetTimeEncounters
	.byte 0

Route27_OnTransition:
	callnative SetTimeBasedEncounters
	end

Route27_EventScript_BaobaCall::
	goto_if_unset JOHTO_FLAG_BADGE08_GET, Route27_EventScript_DeferLateArrival
	setspeaker Route27_Text_BaobaName
	pokenavcall BlackthornCity_Text_BaobaCall
	waitmessage
	delay 30
	setflag JOHTO_FLAG_SAFARI_ZONE_WEST_EXPANSION
	setvar JOHTO_VAR_ROUTE27_BAOBA_CALL, 1
	end

Route27_Text_BaobaName:
	.string "BAOBA$"

Route27_EventScript_FirstSteps::
	goto_if_unset JOHTO_FLAG_BADGE08_GET, Route27_EventScript_DeferLateArrival
	lock
	playse SE_PIN
	setflag JOHTO_FLAG_VISITED_KANTO
	applymovement2 LOCALID_ROUTE27_FATMAN, J_Common_Movement_ExclamationMark
	turnobject LOCALID_ROUTE27_FATMAN, DIR_WEST
	delay 30
	getplayerxy VAR_TEMP_0, VAR_TEMP_1
	call_if_eq VAR_TEMP_1, 24, Route27_EventScript_FirstStepsWalkTop
	call_if_eq VAR_TEMP_1, 25, Route27_EventScript_FirstStepsWalkBot

	msgbox Route27_Text_FisherHey, MSGBOX_DEFAULT
	msgbox Route27_Text_FisherMessage, MSGBOX_DEFAULT
	closemessage
	turnobject LOCALID_ROUTE27_FATMAN, DIR_SOUTH


	setflag JOHTO_FLAG_HIDE_VICTORY_ROAD_SILVER
	setflag JOHTO_FLAG_HIDE_INDIGO_PLATEAU_SILVER
	setflag JOHTO_FLAG_HIDE_INDIGO_PLATEAU_MARY_OAK

	clearflag JOHTO_FLAG_GOT_TM_SANDSTORM
	clearflag JOHTO_FLAG_INDIGOJUNCTION_HIDE_SILVER_GUARD
	clearflag JOHTO_FLAG_INDIGOJUNCTION_HIDE_KANTO_GUARD

	setvar JOHTO_VAR_ROUTE27_STATE, 1
	release
	end

Route27_EventScript_FirstStepsWalkTop::
	applymovement2 LOCALID_ROUTE27_FATMAN, Route27_Movement_WalkTop
	waitmovement 0
	return

Route27_EventScript_FirstStepsWalkBot::
	applymovement2 LOCALID_ROUTE27_FATMAN, Route27_Movement_WalkBot
	waitmovement 0
	return

Route27_Movement_WalkTop:
	face_left
	walk_left
	step_end

Route27_Movement_WalkBot:
	walk_down
	walk_left
	step_end

Route27_EventScript_Item_Moonstone::
	finditem ITEM_MOON_STONE
	end

Route27_EventScript_Item_RareCandy::
	finditem ITEM_RARE_CANDY
	end

Route27_EventScript_Item_DragonClaw::
	finditem ITEM_TM_DRAGON_CLAW
	end

Route27_EventScript_Item_Destiny_Knot::
	finditem ITEM_DESTINY_KNOT
	end

Route27_EventScript_Fatman::
	msgbox Route27_Text_FisherMessage, MSGBOX_NPC
	end

Route27_EventScript_Blake::
	trainerbattle_single TRAINER_JOHTO_BLAKE_HNS, Route27_Text_CooltrainermBlakeSeen, Route27_Text_CooltrainermBlakeBeaten
	msgbox Route27_Text_CooltrainermBlakeAfter, MSGBOX_AUTOCLOSE
	end

Route27_EventScript_Brian::
	trainerbattle_single TRAINER_JOHTO_BRIAN_HNS, Route27_Text_CooltrainermBrianSeen, Route27_Text_CooltrainermBrianBeaten
	msgbox Route27_Text_CooltrainermBrianAfter, MSGBOX_AUTOCLOSE
	end

Route27_EventScript_Reena::
	trainerbattle_single TRAINER_JOHTO_REENA_HNS, Route27_Text_CooltrainerfReenaSeen, Route27_Text_CooltrainerfReenaBeaten, Route27_EventScript_RegisterReena
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, Route27_EventScript_RematchReena
	msgbox Route27_Text_CooltrainerfReenaAfter, MSGBOX_AUTOCLOSE
	end

Route27_EventScript_RegisterReena::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox Route27_Text_ReenaRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_JOHTO_REENA_HNS
	release
	end

Route27_EventScript_RematchReena::
	trainerbattle_rematch TRAINER_JOHTO_REENA_HNS, Route27_Text_ReenaRematchIntro, Route27_Text_ReenaRematchDefeat
	msgbox Route27_Text_ReenaPostRematch, MSGBOX_AUTOCLOSE
	end

Route27_EventScript_Megan::
	trainerbattle_single TRAINER_JOHTO_MEGAN_HNS, Route27_Text_CooltrainerfMeganSeen, Route27_Text_CooltrainerfMeganBeaten
	msgbox Route27_Text_CooltrainerfMeganAfter, MSGBOX_AUTOCLOSE
	end

Route27_EventScript_Gilbert::
	trainerbattle_single TRAINER_JOHTO_GILBERT_HNS, Route27_Text_PsychicGilbertSeen, Route27_Text_PsychicGilbertBeaten
	msgbox Route27_Text_PsychicGilbertAfter, MSGBOX_AUTOCLOSE
	end

Route27_EventScript_Jose::
	trainerbattle_single TRAINER_JOHTO_JOSE_HNS, Route27_Text_BirdKeeperJoseSeen, Route27_Text_BirdKeeperJoseBeaten, Route27_EventScript_RegisterJose
	goto_if_set JOHTO_FLAG_JOSE_HAS_ITEM_HNS, Route27_EventScript_JoseGiveItem
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, Route27_EventScript_RematchJose
	msgbox Route27_Text_BirdKeeperJoseAfter, MSGBOX_AUTOCLOSE
	end

Route27_EventScript_RegisterJose::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox Route27_Text_JoseRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_JOHTO_JOSE_HNS
	release
	end

Route27_EventScript_RematchJose::
	trainerbattle_rematch TRAINER_JOHTO_JOSE_HNS, Route27_Text_JoseRematchIntro, Route27_Text_JoseRematchDefeat
	msgbox Route27_Text_JosePostRematch, MSGBOX_AUTOCLOSE
	end

Route27_EventScript_JoseGiveItem::
	msgbox Route27_Text_JoseHasItem, MSGBOX_DEFAULT
	giveitem JOHTO_VAR_JOSE_ITEM_HNS
	goto_if_eq VAR_RESULT, FALSE, Route27_EventScript_JoseNoRoom
	clearflag JOHTO_FLAG_JOSE_HAS_ITEM_HNS
	msgbox Route27_Text_JoseGaveItem, MSGBOX_AUTOCLOSE
	end

Route27_EventScript_JoseNoRoom::
	msgbox Route27_Text_JoseNoRoom, MSGBOX_AUTOCLOSE
	end

Route27_EventScript_Scott::
	trainerbattle_single TRAINER_JOHTO_SCOTT_HNS, Route27_Text_FisherScottSeen, Route27_Text_FisherScottBeaten
	msgbox Route27_Text_FisherScottAfter, MSGBOX_AUTOCLOSE
	end

Route27_EventScript_TohjoFallsSign::
	msgbox TohjoFalls_Text_Sign, MSGBOX_SIGN
	end

Route27_Text_FisherHey:
	.string "Hey!$"

Route27_Text_FisherMessage:
	.string "Headin{SE_M_SANDSTORM}t{SE_M_ATTRACT2}JOHT{SE_M_SOLAR_BEAM}fro{SE_M_MILK_DRINK}KANTO?\pSUR{SE_M_LEER}wes{SE_M_SPIT_UP}acros{SE_M_GRASSWHISTLE}thi{SE_M_GRASSWHISTLE}wate{SE_M_SAND_TOMB}to\nreac{SE_M_TRI_ATTACK}NE{SE_M_DETECT}BAR{SE_M_SNORE}TOWN.\pTh{SE_M_REVERSAL}easter{SE_M_ATTRACT}rout{SE_M_REVERSAL}lead{SE_M_GRASSWHISTLE}through\nTOHJ{SE_M_SOLAR_BEAM}FALL{SE_M_SKETCH}towar{SE_M_WATERFALL}th{SE_M_REVERSAL}LEAGUE.$"

Route27_Text_CooltrainermBlakeSeen:
	.string "Yo{SE_M_DIVE}loo{SE_M_ENCORE2}prett{SE_M_YAWN}strong.\n"
	.string "Le{SE_M_SPIT_UP}m{SE_M_REVERSAL}battl{SE_M_REVERSAL}you!$"

Route27_Text_CooltrainermBlakeBeaten:
	.string "Yow!$"

Route27_Text_CooltrainermBlakeAfter:
	.string "I{SE_M_ACID_ARMOR}yo{SE_M_DIVE}prevai{SE_M_BATON_PASS}o{SE_M_ATTRACT}thi{SE_M_GRASSWHISTLE}hars{SE_M_TRI_ATTACK}trek,\n"
	.string "th{SE_M_REVERSAL}trut{SE_M_TRI_ATTACK}wil{SE_M_BATON_PASS}b{SE_M_REVERSAL}revealed!\p"
	.string "Heh{SE_M_SUPERSONIC}sorry{SE_M_SUPERSONIC}{SE_M_HEAL_BELL}jus{SE_M_SPIT_UP}wante{SE_M_WATERFALL}t{SE_M_ATTRACT2}say\n"
	.string "somethin{SE_M_SANDSTORM}cool.$"

Route27_Text_CooltrainermBrianSeen:
	.string "Hm{SE_M_SING}You'r{SE_M_REVERSAL}good{SE_M_SUPERSONIC}aren'{SE_M_SPIT_UP}you?$"

Route27_Text_CooltrainermBrianBeaten:
	.string "Jus{SE_M_SPIT_UP}a{SE_M_GRASSWHISTLE}{SE_M_HEAL_BELL}thought!$"

Route27_Text_CooltrainermBrianAfter:
	.string "{SE_M_BONEMERANG}goo{SE_M_WATERFALL}traine{SE_M_SAND_TOMB}ca{SE_M_ATTRACT}recogniz{SE_M_REVERSAL}other\n"
	.string "goo{SE_M_WATERFALL}trainers.$"

Route27_Text_CooltrainerfReenaSeen:
	.string "Yo{SE_M_DIVE}shouldn'{SE_M_SPIT_UP}underestimat{SE_M_REVERSAL}the\n"
	.string "wil{SE_M_WATERFALL}POKéMO{SE_M_PSYBEAM2}i{SE_M_ATTRACT}thes{SE_M_REVERSAL}parts.$"

Route27_Text_CooltrainerfReenaBeaten:
	.string "Oh{SE_M_DRAGON_RAGE}You'r{SE_M_REVERSAL}muc{SE_M_TRI_ATTACK}to{SE_M_ATTRACT2}strong!$"

Route27_Text_CooltrainerfReenaAfter:
	.string "You'r{SE_M_REVERSAL}jus{SE_M_SPIT_UP}{SE_M_CHARGE}kid{SE_M_SUPERSONIC}bu{SE_M_SPIT_UP}you'r{SE_M_REVERSAL}not\n"
	.string "t{SE_M_ATTRACT2}b{SE_M_REVERSAL}underestimate{SE_M_WATERFALL}either.$"

Route27_Text_ReenaRegister:
	.string "You'r{SE_M_REVERSAL}jus{SE_M_SPIT_UP}{SE_M_CHARGE}kid{SE_M_SUPERSONIC}bu{SE_M_SPIT_UP}you'r{SE_M_REVERSAL}not\n"
	.string "t{SE_M_ATTRACT2}b{SE_M_REVERSAL}underestimate{SE_M_WATERFALL}either.$"

Route27_Text_ReenaRematchIntro:
	.string "Yo{SE_M_DIVE}shouldn'{SE_M_SPIT_UP}underestimat{SE_M_REVERSAL}the\n"
	.string "wil{SE_M_WATERFALL}POKéMO{SE_M_PSYBEAM2}i{SE_M_ATTRACT}thes{SE_M_REVERSAL}parts.$"

Route27_Text_ReenaRematchDefeat:
	.string "Oh{SE_M_DRAGON_RAGE}You'r{SE_M_REVERSAL}muc{SE_M_TRI_ATTACK}to{SE_M_ATTRACT2}strong!$"

Route27_Text_ReenaPostRematch:
	.string "You'r{SE_M_REVERSAL}jus{SE_M_SPIT_UP}{SE_M_CHARGE}kid{SE_M_SUPERSONIC}bu{SE_M_SPIT_UP}you'r{SE_M_REVERSAL}not\n"
	.string "t{SE_M_ATTRACT2}b{SE_M_REVERSAL}underestimate{SE_M_WATERFALL}either.$"

Route27_Text_CooltrainerfMeganSeen:
	.string "It'{SE_M_GRASSWHISTLE}rar{SE_M_REVERSAL}t{SE_M_ATTRACT2}se{SE_M_REVERSAL}anyon{SE_M_REVERSAL}com{SE_M_REVERSAL}here.\p"
	.string "Ar{SE_M_REVERSAL}yo{SE_M_DIVE}trainin{SE_M_SANDSTORM}o{SE_M_ATTRACT}you{SE_M_SAND_TOMB}own?$"

Route27_Text_CooltrainerfMeganBeaten:
	.string "Oh{SE_M_DRAGON_RAGE}You'r{SE_M_REVERSAL}reall{SE_M_YAWN}strong!$"

Route27_Text_CooltrainerfMeganAfter:
	.string "I'{SE_M_MILK_DRINK}checkin{SE_M_SANDSTORM}ou{SE_M_SPIT_UP}pre{SE_M_PAY_DAY}an{SE_M_WATERFALL}post-\n"
	.string "evolutio{SE_M_ATTRACT}POKéMON.\p"
	.string "Evolutio{SE_M_ATTRACT}reall{SE_M_YAWN}doe{SE_M_GRASSWHISTLE}make\n"
	.string "POKéMO{SE_M_PSYBEAM2}stronger.\p"
	.string "Bu{SE_M_SPIT_UP}evolve{SE_M_WATERFALL}form{SE_M_GRASSWHISTLE}als{SE_M_ATTRACT2}learn\n"
	.string "move{SE_M_GRASSWHISTLE}late{SE_M_SAND_TOMB}on.$"

Route27_Text_PsychicGilbertSeen:
	.string "Don'{SE_M_SPIT_UP}sa{SE_M_YAWN}{SE_M_CHARGE}thing!\p"
	.string "Le{SE_M_SPIT_UP}m{SE_M_REVERSAL}gues{SE_M_GRASSWHISTLE}wha{SE_M_SPIT_UP}you'r{SE_M_REVERSAL}thinking.\p"
	.string "Mmmmmmm…\p"
	.string "{SE_M_HEAL_BELL}go{SE_M_SPIT_UP}it{SE_M_DRAGON_RAGE}You'r{SE_M_REVERSAL}o{SE_M_ATTRACT}th{SE_M_REVERSAL}POKéMON\n"
	.string "LEAGU{SE_M_SWORDS_DANCE}challenge!$"

Route27_Text_PsychicGilbertBeaten:
	.string "You'r{SE_M_REVERSAL}to{SE_M_ATTRACT2}much!$"

Route27_Text_PsychicGilbertAfter:
	.string "Wit{SE_M_TRI_ATTACK}you{SE_M_SAND_TOMB}skills{SE_M_SUPERSONIC}you'l{SE_M_BATON_PASS}d{SE_M_ATTRACT2}wel{SE_M_BATON_PASS}at\n"
	.string "th{SE_M_REVERSAL}LEAGUE.\p"
	.string "That'{SE_M_GRASSWHISTLE}wha{SE_M_SPIT_UP}m{SE_M_YAWN}premonitio{SE_M_ATTRACT}says.$"

Route27_Text_BirdKeeperJoseSeen:
	.string "Tweet{SE_M_DRAGON_RAGE}Tweet{SE_M_DRAGON_RAGE}Tetweet!$"

Route27_Text_BirdKeeperJoseBeaten:
	.string "Tweet!$"

Route27_Text_BirdKeeperJoseAfter:
	.string "BIR{SE_M_FAINT_ATTACK}KEEPER{SE_M_SKETCH}lik{SE_M_REVERSAL}m{SE_M_REVERSAL}mimi{SE_M_HYPER_BEAM}bird\n"
	.string "whistle{SE_M_GRASSWHISTLE}t{SE_M_ATTRACT2}comman{SE_M_WATERFALL}POKéMON.$"

Route27_Text_JoseRegister:
	.string "BIR{SE_M_FAINT_ATTACK}KEEPER{SE_M_SKETCH}lik{SE_M_REVERSAL}m{SE_M_REVERSAL}mimi{SE_M_HYPER_BEAM}bird\n"
	.string "whistle{SE_M_GRASSWHISTLE}t{SE_M_ATTRACT2}comman{SE_M_WATERFALL}POKéMON.$"

Route27_Text_JoseRematchIntro:
	.string "Tweet{SE_M_DRAGON_RAGE}Tweet{SE_M_DRAGON_RAGE}Tetweet!$"

Route27_Text_JoseRematchDefeat:
	.string "Tweet!$"

Route27_Text_JosePostRematch:
	.string "BIR{SE_M_FAINT_ATTACK}KEEPER{SE_M_SKETCH}lik{SE_M_REVERSAL}m{SE_M_REVERSAL}mimi{SE_M_HYPER_BEAM}bird\n"
	.string "whistle{SE_M_GRASSWHISTLE}t{SE_M_ATTRACT2}comman{SE_M_WATERFALL}POKéMON.$"

Route27_Text_JoseHasItem:
	.string "Hey{SE_M_DRAGON_RAGE}{SE_M_HEAL_BELL}foun{SE_M_WATERFALL}something\n"
	.string "shin{SE_M_YAWN}whil{SE_M_REVERSAL}bird-watching!\p"
	.string "Here{SE_M_SUPERSONIC}yo{SE_M_DIVE}ca{SE_M_ATTRACT}hav{SE_M_REVERSAL}it!$"

Route27_Text_JoseGaveItem:
	.string "{SE_M_HEAL_BELL}fin{SE_M_WATERFALL}al{SE_M_BATON_PASS}sort{SE_M_GRASSWHISTLE}o{SE_M_ACID_ARMOR}things\n"
	.string "ou{SE_M_SPIT_UP}her{SE_M_REVERSAL}o{SE_M_ATTRACT}ROUT{SE_M_SWORDS_DANCE}27.\p"
	.string "I'l{SE_M_BATON_PASS}le{SE_M_SPIT_UP}yo{SE_M_DIVE}kno{SE_M_TWISTER}i{SE_M_ACID_ARMOR}{SE_M_HEAL_BELL}find\n"
	.string "anythin{SE_M_SANDSTORM}else!$"

Route27_Text_JoseNoRoom:
	.string "Hmm{SE_M_SUPERSONIC}you{SE_M_SAND_TOMB}BA{SE_M_SWAGGER}i{SE_M_GRASSWHISTLE}full.\p"
	.string "Com{SE_M_REVERSAL}bac{SE_M_ENCORE2}whe{SE_M_ATTRACT}yo{SE_M_DIVE}hav{SE_M_REVERSAL}room.$"

TohjoFalls_Text_Sign:
	.string "TOHJ{SE_M_SOLAR_BEAM}FALLS\p"
	.string "TH{SE_M_SWORDS_DANCE}LIN{SE_M_SNORE}BETWEE{SE_M_PSYBEAM2}KANT{SE_M_SOLAR_BEAM}AN{SE_M_FAINT_ATTACK}JOHTO$"

Route27_Text_FisherScottSeen:
	.string "I'{SE_M_MILK_DRINK}feelin{SE_M_SANDSTORM}grea{SE_M_SPIT_UP}today!\p"
	.string "{SE_M_HEAL_BELL}fee{SE_M_BATON_PASS}lik{SE_M_REVERSAL}{SE_M_HEAL_BELL}coul{SE_M_WATERFALL}boo{SE_M_SPIT_UP}eve{SE_M_ATTRACT}the\n"
	.string "LEAGU{SE_M_SWORDS_DANCE}CHAMP!$"

Route27_Text_FisherScottBeaten:
	.string "No{SE_M_DRAGON_RAGE}No{SE_M_SPIT_UP}i{SE_M_ATTRACT}thi{SE_M_GRASSWHISTLE}battle!$"

Route27_Text_FisherScottAfter:
	.string "Jus{SE_M_SPIT_UP}lik{SE_M_REVERSAL}i{SE_M_ATTRACT}fishing{SE_M_SUPERSONIC}it'{SE_M_GRASSWHISTLE}al{SE_M_BATON_PASS}over\n"
	.string "i{SE_M_ATTRACT}POKéMO{SE_M_PSYBEAM2}i{SE_M_ACID_ARMOR}yo{SE_M_DIVE}giv{SE_M_REVERSAL}up.$"

Route27_EventScript_DeferLateArrival::
	end

