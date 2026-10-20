@ Johto (data/maps/Route30_hns/scripts.inc), as built into the FireRed game.

Route30_hns_MapScripts::
	map_script 3, Route30_OnTransition
	map_script 5, J_SetTimeEncounters
	map_script 2, Route30_OnFrame
	.byte 0

Route30_OnTransition:
	callnative SetTimeBasedEncounters
	end

Route30_OnFrame::
	map_script_2 20554, 2, Route30_EventScript_ElmCall_Trigger
	.2byte 0

Route30_EventScript_Boy::
	lock
	faceplayer
	goto_if_set 8660, Route30_EventScript_Boy2
	msgbox Route30_Text_YoungsterDirectionsToMrPokemon, MSGBOX_DEFAULT
	closemessage
	release
	end

Route30_EventScript_Boy2::
	lock
	faceplayer
	msgbox Route30_Text_YoungsterEveryoneIsBattling, MSGBOX_DEFAULT
	closemessage
	release
	end

Route30_EventScript_Girl::
	lock
	faceplayer
	msgbox Route30_Text_CooltrainerF, MSGBOX_DEFAULT
	closemessage
	release
	end

Route30_EventScript_Youngster_Joey_Fighting::
	lock
	msgbox Route30_Text_UseTackle, MSGBOX_AUTOCLOSE
	waitmessage
	playse 21
	applymovement 6, J_Common_Movement_QuestionMark
	delay 55
	waitmovement 6
	faceplayer
	msgbox Route30_Text_ThisIsABigBattle, MSGBOX_AUTOCLOSE
	waitmessage
	turnobject 6 DIR_NORTH
	release
	end

Route30_EventScript_Youngster_Joey::
	trainerbattle_single 1031, Route30_Text_YoungsterJoey1Seen, Route30_Text_YoungsterJoey1Beaten, Route30_EventScript_RegisterJoey
	specialvar 32781, ShouldTryRematchBattle
	goto_if_eq 32781, TRUE, Route30_EventScript_RematchJoey
	msgbox Route30_Text_YoungsterJoey1After, MSGBOX_AUTOCLOSE
	end

Route30_EventScript_RegisterJoey::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox Route30_Text_JoeyRegister, MSGBOX_DEFAULT
	register_matchcall 1031
	release
	end

Route30_EventScript_RematchJoey::
	trainerbattle_rematch 1031, Route30_Text_JoeyRematchIntro, Route30_Text_JoeyRematchDefeat
	msgbox Route30_Text_JoeyPostRematch, MSGBOX_AUTOCLOSE
	end

Route30_EventScript_Youngster_Mikey::
	trainerbattle_single 1032, Route30_Text_YoungsterMikeySeen, Route30_Text_YoungsterMikeyBeaten
	msgbox Route30_Text_YoungsterMikeyAfter, MSGBOX_AUTOCLOSE
	end

Route30_EventScript_Bugcatcher_Don::
	trainerbattle_single 1189, Route30_Text_BugCatcherDonSeen, Route30_Text_BugCatcherDonBeaten
	msgbox Route30_Text_BugCatcherDonAfter, MSGBOX_AUTOCLOSE
	end

Route30_EventScript_ElmCall_Trigger::
	lock
	setspeaker Route30_Text_ElmName
	pokenavcall Route30_Text_Elm_Disaster
	waitmessage
	delay 30
	setvar 20554, 3
	release
	end

Route30_EventScript_Sign::
	lock
	msgbox Route30_Text_Sign, MSGBOX_SIGN
	closemessage
	release
	end

Route30_EventScript_TrainerTips::
	lock
	msgbox Route30_Text_TrainerTips, MSGBOX_SIGN
	closemessage
	release
	end

Route30_EventScript_Poliwag::
	lock
	faceplayer
	waitse
	playmoncry 60, 0
	msgbox Route30_Text_Poliwag, MSGBOX_DEFAULT
	waitmoncry
	release
	end

Route30_EventScript_Mailbox::
	msgbox Route30_Text_Mailbox, MSGBOX_SIGN
	end

Route30_Text_Mailbox:
	.string "MR.POKéMON'{SE_M_GRASSWHISTLE}House$"

Route30_Text_UseTackle:
	.string "Go{SE_M_SUPERSONIC}RATTATA!\p"
	.string "TACKLE!$"

Route30_Text_ThisIsABigBattle:
	.string "What{SE_M_SING}Thi{SE_M_GRASSWHISTLE}i{SE_M_GRASSWHISTLE}{SE_M_CHARGE}bi{SE_M_SANDSTORM}battle!\n"
	.string "Leav{SE_M_REVERSAL}m{SE_M_REVERSAL}alone!$"

Route30_Text_YoungsterJoey1Seen:
	.string "{SE_M_HEAL_BELL}jus{SE_M_SPIT_UP}lost{SE_M_SUPERSONIC}s{SE_M_ATTRACT2}I'{SE_M_MILK_DRINK}tryin{SE_M_SANDSTORM}to\n"
	.string "fin{SE_M_WATERFALL}mor{SE_M_REVERSAL}POKéMON.\p"
	.string "Wait{SE_M_DRAGON_RAGE}Yo{SE_M_DIVE}loo{SE_M_ENCORE2}weak{SE_M_DRAGON_RAGE}Com{SE_M_REVERSAL}on,\n"
	.string "let'{SE_M_GRASSWHISTLE}battle!$"

Route30_Text_YoungsterJoey1Beaten:
	.string "Ack{SE_M_DRAGON_RAGE}{SE_M_HEAL_BELL}los{SE_M_SPIT_UP}again!\n"
	.string "Doggon{SE_M_REVERSAL}it!$"

Route30_Text_YoungsterJoey1After:
	.string "D{SE_M_ATTRACT2}{SE_M_HEAL_BELL}hav{SE_M_REVERSAL}t{SE_M_ATTRACT2}hav{SE_M_REVERSAL}mor{SE_M_REVERSAL}POKéMON\n"
	.string "i{SE_M_ATTRACT}orde{SE_M_SAND_TOMB}t{SE_M_ATTRACT2}battl{SE_M_REVERSAL}better?\p"
	.string "No{SE_M_DRAGON_RAGE}I'{SE_M_MILK_DRINK}stickin{SE_M_SANDSTORM}wit{SE_M_TRI_ATTACK}thi{SE_M_GRASSWHISTLE}one\n"
	.string "n{SE_M_ATTRACT2}matte{SE_M_SAND_TOMB}what!$"

Route30_Text_YoungsterMikeySeen:
	.string "You'r{SE_M_REVERSAL}{SE_M_CHARGE}POKéMO{SE_M_PSYBEAM2}trainer,\n"
	.string "right?\p"
	.string "The{SE_M_ATTRACT}yo{SE_M_DIVE}hav{SE_M_REVERSAL}t{SE_M_ATTRACT2}battle!$"

Route30_Text_YoungsterMikeyBeaten:
	.string "That'{SE_M_GRASSWHISTLE}strange.\n"
	.string "{SE_M_HEAL_BELL}wo{SE_M_ATTRACT}before.$"

Route30_Text_YoungsterMikeyAfter:
	.string "Becomin{SE_M_SANDSTORM}{SE_M_CHARGE}goo{SE_M_WATERFALL}traine{SE_M_SAND_TOMB}is\n"
	.string "reall{SE_M_YAWN}tough.\p"
	.string "I'{SE_M_MILK_DRINK}goin{SE_M_SANDSTORM}t{SE_M_ATTRACT2}battl{SE_M_REVERSAL}other\n"
	.string "peopl{SE_M_REVERSAL}t{SE_M_ATTRACT2}ge{SE_M_SPIT_UP}better.$"

Route30_Text_BugCatcherDonSeen:
	.string "Instea{SE_M_WATERFALL}o{SE_M_ACID_ARMOR}{SE_M_CHARGE}bu{SE_M_SANDSTORM}POKéMON,\n"
	.string "{SE_M_HEAL_BELL}foun{SE_M_WATERFALL}{SE_M_CHARGE}trainer!$"

Route30_Text_BugCatcherDonBeaten:
	.string "Argh{SE_M_DRAGON_RAGE}You'r{SE_M_REVERSAL}to{SE_M_ATTRACT2}strong!$"

Route30_Text_BugCatcherDonAfter:
	.string "{SE_M_HEAL_BELL}ra{SE_M_ATTRACT}ou{SE_M_SPIT_UP}o{SE_M_ACID_ARMOR}POK{SE_U}BALL{SE_M_SKETCH}while\n"
	.string "{SE_M_HEAL_BELL}wa{SE_M_GRASSWHISTLE}catchin{SE_M_SANDSTORM}POKéMON.\p"
	.string "{SE_M_HEAL_BELL}should'v{SE_M_REVERSAL}bough{SE_M_SPIT_UP}som{SE_M_REVERSAL}more…$"

Route30_Text_YoungsterDirectionsToMrPokemon:
	.string "MR{SE_M_PERISH_SONG}POKéMON'{SE_M_GRASSWHISTLE}house?\n"
	.string "It'{SE_M_GRASSWHISTLE}{SE_M_CHARGE}bi{SE_M_SPIT_UP}farthe{SE_M_SAND_TOMB}ahead.$"

Route30_Text_YoungsterEveryoneIsBattling:
	.string "Everyone'{SE_M_GRASSWHISTLE}havin{SE_M_SANDSTORM}fun\n"
	.string "battling!\p"
	.string "Yo{SE_M_DIVE}shoul{SE_M_WATERFALL}too!$"

Route30_Text_CooltrainerF:
	.string "I'{SE_M_MILK_DRINK}no{SE_M_SPIT_UP}{SE_M_CHARGE}trainer.\p"
	.string "Bu{SE_M_SPIT_UP}i{SE_M_ACID_ARMOR}yo{SE_M_DIVE}loo{SE_M_ENCORE2}on{SE_M_REVERSAL}i{SE_M_ATTRACT}the\n"
	.string "eyes{SE_M_SUPERSONIC}prepar{SE_M_REVERSAL}t{SE_M_ATTRACT2}battle.$"

Route30_Text_Sign:
	.string "ROUT{SE_M_SWORDS_DANCE}30\p"
	.string "VIOLE{SE_M_SWIFT}CIT{SE_M_MOONLIGHT}{SE_M_PAY_DAY}CHERRYGROV{SE_M_SWORDS_DANCE}CITY$"

Route30_Text_MrPokemonsHouseDirectionsSign:
	.string "MR{SE_M_PERISH_SONG}POKéMON'{SE_M_SKETCH}HOUSE\n"
	.string "STRAIGH{SE_M_SWIFT}AHEAD!$"

Route30_Text_MrPokemonsHouseSign:
	.string "MR{SE_M_PERISH_SONG}POKéMON'{SE_M_SKETCH}HOUSE$"

Route30_Text_TrainerTips:
	.string "TRAINE{SE_M_MINIMIZE}TIPS\p"
	.string "N{SE_M_ATTRACT2}stealin{SE_M_SANDSTORM}othe{SE_M_SAND_TOMB}people's\n"
	.string "POKéMON!\p"
	.string "POK{SE_U}BALL{SE_M_SKETCH}ar{SE_M_REVERSAL}t{SE_M_ATTRACT2}b{SE_M_REVERSAL}thrown\n"
	.string "onl{SE_M_YAWN}a{SE_M_SPIT_UP}wil{SE_M_WATERFALL}POKéMON!$"

Route30_Text_JoeyRegister:
	.string "You'r{SE_M_REVERSAL}prett{SE_M_YAWN}good!\p"
	.string "M{SE_M_YAWN}RATTATA'{SE_M_GRASSWHISTLE}rarin{SE_M_SANDSTORM}t{SE_M_ATTRACT2}go,\n"
	.string "jus{SE_M_SPIT_UP}lik{SE_M_REVERSAL}always.\p"
	.string "It'{SE_M_GRASSWHISTLE}th{SE_M_REVERSAL}onl{SE_M_YAWN}on{SE_M_REVERSAL}{SE_M_HEAL_BELL}have.\n"
	.string "I'{SE_M_MILK_DRINK}goin{SE_M_SANDSTORM}t{SE_M_ATTRACT2}becom{SE_M_REVERSAL}{SE_M_CHARGE}great\l"
	.string "TRAINE{SE_M_MINIMIZE}wit{SE_M_TRI_ATTACK}it!\p"
	.string "Let'{SE_M_GRASSWHISTLE}battl{SE_M_REVERSAL}agai{SE_M_ATTRACT}sometime!$"

Route30_Text_JoeyRematchIntro:
	.string "{SE_M_HEAL_BELL}promise{SE_M_WATERFALL}thing{SE_M_GRASSWHISTLE}woul{SE_M_WATERFALL}be\n"
	.string "different{SE_M_DRAGON_RAGE}Let'{SE_M_GRASSWHISTLE}battle!$"

Route30_Text_JoeyRematchDefeat:
	.string "Ack{SE_M_DRAGON_RAGE}{SE_M_HEAL_BELL}los{SE_M_SPIT_UP}again!\n"
	.string "Doggon{SE_M_REVERSAL}it!$"

Route30_Text_JoeyPostRematch:
	.string "I'{SE_M_MILK_DRINK}checkin{SE_M_SANDSTORM}ou{SE_M_SPIT_UP}my\n"
	.string "RATTATA'{SE_M_GRASSWHISTLE}move{SE_M_GRASSWHISTLE}an{SE_M_WATERFALL}devising\l"
	.string "som{SE_M_REVERSAL}strategies.\p"
	.string "Whe{SE_M_ATTRACT}{SE_M_HEAL_BELL}com{SE_M_REVERSAL}u{SE_M_MORNING_SUN}wit{SE_M_TRI_ATTACK}{SE_M_CHARGE}good\n"
	.string "one{SE_M_SUPERSONIC}let'{SE_M_GRASSWHISTLE}battle!$"

Route30_Text_YoungsterJoeyGiveHPUp:
	.string "{SE_M_HEAL_BELL}los{SE_M_SPIT_UP}again…\n"
	.string "Gee{SE_M_SUPERSONIC}you'r{SE_M_REVERSAL}tough!\p"
	.string "O{SE_M_TRI_ATTACK}yeah{SE_M_SUPERSONIC}{SE_M_HEAL_BELL}almos{SE_M_SPIT_UP}forgo{SE_M_SPIT_UP}that\n"
	.string "{SE_M_HEAL_BELL}ha{SE_M_WATERFALL}t{SE_M_ATTRACT2}giv{SE_M_REVERSAL}yo{SE_M_DIVE}this.\p"
	.string "Us{SE_M_REVERSAL}i{SE_M_SPIT_UP}t{SE_M_ATTRACT2}ge{SE_M_SPIT_UP}eve{SE_M_ATTRACT}tougher,\n"
	.string "OK?\p"
	.string "I'{SE_M_MILK_DRINK}goin{SE_M_SANDSTORM}t{SE_M_ATTRACT2}ge{SE_M_SPIT_UP}toughe{SE_M_SAND_TOMB}too.$"

Route30_Text_ElmName:
	.string "PROF.ELM$"

Route30_Text_Elm_Disaster:
	.string "PROF.ELM{SE_M_HEAT_WAVE}H-hello{SE_M_SING}{PLAYER}{SE_M_SING}It's\n"
	.string "{SE_M_CHARGE}disaster!\p"
	.string "Uh{SE_M_SUPERSONIC}um{SE_M_SUPERSONIC}it'{SE_M_GRASSWHISTLE}jus{SE_M_SPIT_UP}terrible!\p"
	.string "Wha{SE_M_SPIT_UP}shoul{SE_M_WATERFALL}{SE_M_HEAL_BELL}do{SE_M_SING}It…\n"
	.string "Oh{SE_M_SUPERSONIC}no…\p"
	.string "Pleas{SE_M_REVERSAL}ge{SE_M_SPIT_UP}bac{SE_M_ENCORE2}her{SE_M_REVERSAL}now!$"

Route30_Text_Poliwag:
	.string "POLIWAG{SE_M_HEAT_WAVE}Wa{SE_M_SANDSTORM}waag!$"

