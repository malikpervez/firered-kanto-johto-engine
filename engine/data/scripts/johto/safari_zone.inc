@ Johto (data/scripts/safari_zone.inc), as built into the FireRed game.

J_SafariZone_EventScript_OutOfBallsMidBattle::



	setvar JOHTO_VAR_SAFARI_ZONE_STATE, 1



	special ExitSafariMode



	goto_if_set JOHTO_FLAG_IN_KANTO_SAFARI_ZONE, J_SafariZone_EventScript_ExitKantoMidBattle
	setwarp MAP_SAFARI_ZONE_GATE_SAFARI_ZONE_ENTRANCE_HNS, 9, 3



	end

J_SafariZone_EventScript_ExitKantoMidBattle::
	clearflag JOHTO_FLAG_IN_KANTO_SAFARI_ZONE
	setwarp MAP_FUCHSIA_CITY_SAFARI_ZONE_ENTRANCE_HNS, 5, 6
	end

J_SafariZone_EventScript_Exit::



	setvar JOHTO_VAR_SAFARI_ZONE_STATE, 1



	special ExitSafariMode



	goto_if_set JOHTO_FLAG_IN_KANTO_SAFARI_ZONE, J_SafariZone_EventScript_ExitKanto
	warp MAP_SAFARI_ZONE_GATE_SAFARI_ZONE_ENTRANCE_HNS, 9, 3



	waitstate
	end

J_SafariZone_EventScript_ExitKanto::
	clearflag JOHTO_FLAG_IN_KANTO_SAFARI_ZONE
	warp MAP_FUCHSIA_CITY_SAFARI_ZONE_ENTRANCE_HNS, 5, 6
	waitstate
	end

J_SafariZone_EventScript_RetirePrompt::
	lockall
	msgbox J_SafariZone_Text_WouldYouLikeToExit, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, J_SafariZone_EventScript_Retire
	releaseall
	end

J_SafariZone_EventScript_Retire::
	goto J_SafariZone_EventScript_Exit

J_SafariZone_EventScript_TimesUp::
	lockall
	playse SE_DING_DONG
	message J_SafariZone_Text_TimesUp
	waitmessage
	waitbuttonpress
	releaseall
	goto J_SafariZone_EventScript_Exit

J_SafariZone_EventScript_OutOfBalls::
	lockall
	playse SE_DING_DONG
	message J_SafariZone_Text_OutOfBalls
	waitmessage
	waitbuttonpress
	releaseall
	goto J_SafariZone_EventScript_Exit

J_EventScript_PokeBlockFeeder::
	lockall
	special GetPokeblockFeederInFront
	goto_if_ne VAR_RESULT, 0xFFFF, J_SafariZone_EventScript_PokeblockPresent
	msgbox J_SafariZone_Text_PlacePokeblockOnFeeder, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, J_SafariZone_EventScript_ChoosePokeblock
	releaseall
	end

J_SafariZone_EventScript_ChoosePokeblock::
	fadescreen FADE_TO_BLACK
	special OpenPokeblockCaseOnFeeder
	waitstate
	goto_if_ne VAR_RESULT, 0xFFFF, J_SafariZone_EventScript_PokeblockPlaced

	releaseall

	end

J_SafariZone_EventScript_PokeblockPlaced::
	message J_SafariZone_Text_PokeblockWasPlaced
	waitmessage
	waitbuttonpress
	releaseall
	end

J_SafariZone_EventScript_PokeblockPresent::
	message J_SafariZone_Text_PokeblockStillHere
	waitmessage
	waitbuttonpress
	releaseall
	end

J_SafariZone_EventScript_PokeblockGone::
	lockall
	message J_SafariZone_Text_PokeblockGone
	waitmessage
	waitbuttonpress
	releaseall
	end

J_SafariZone_Text_PokeblockGone:
	.string "Th{SE_M_REVERSAL}{STR_VAR_1} wa{SE_M_GRASSWHISTLE}all\n"
	.string "eate{SE_M_ATTRACT}up!$"

J_SafariZone_Text_WouldYouLikeToExit:
	.string "Woul{SE_M_WATERFALL}yo{SE_M_DIVE}lik{SE_M_REVERSAL}t{SE_M_ATTRACT2}exi{SE_M_SPIT_UP}th{SE_M_REVERSAL}SAFARI\n"
	.string "ZON{SE_M_SWORDS_DANCE}righ{SE_M_SPIT_UP}now?$"

J_SafariZone_Text_TimesUp:
	.string "Ding-dong{SE_M_DRAGON_RAGE}Time'{SE_M_GRASSWHISTLE}up!\n"
	.string "You{SE_M_SAND_TOMB}SAFAR{SE_M_HEAL_BELL}Gam{SE_M_REVERSAL}i{SE_M_GRASSWHISTLE}over.$"

J_SafariZone_Text_OutOfBalls:
	.string "You'v{SE_M_REVERSAL}ru{SE_M_ATTRACT}ou{SE_M_SPIT_UP}o{SE_M_ACID_ARMOR}SAFAR{SE_M_HEAL_BELL}BALLS.\n"
	.string "You{SE_M_SAND_TOMB}SAFAR{SE_M_HEAL_BELL}Gam{SE_M_REVERSAL}i{SE_M_GRASSWHISTLE}over.$"

J_SafariZone_Text_PlacePokeblockOnFeeder:
	.string "Woul{SE_M_WATERFALL}yo{SE_M_DIVE}lik{SE_M_REVERSAL}t{SE_M_ATTRACT2}plac{SE_M_REVERSAL}{SE_M_CHARGE}{POKEBLOCK}\n"
	.string "o{SE_M_ATTRACT}th{SE_M_REVERSAL}{POKEBLOCK} FEEDER?$"

J_SafariZone_Text_PokeblockStillHere:
	.string "Th{SE_M_REVERSAL}{STR_VAR_1} yo{SE_M_DIVE}left\n"
	.string "befor{SE_M_REVERSAL}i{SE_M_GRASSWHISTLE}stil{SE_M_BATON_PASS}here.$"

J_SafariZone_Text_PokeblockWasPlaced:
	.string "Th{SE_M_REVERSAL}{STR_VAR_1} wa{SE_M_GRASSWHISTLE}placed\n"
	.string "o{SE_M_ATTRACT}th{SE_M_REVERSAL}{POKEBLOCK} FEEDER.$"

J_Route121_SafariZoneEntrance_Text_WelcomeToSafariZone:
	.string "Welcom{SE_M_REVERSAL}t{SE_M_ATTRACT2}th{SE_M_REVERSAL}SAFAR{SE_M_HEAL_BELL}ZONE!\p"
	.string "Here{SE_M_SUPERSONIC}yo{SE_M_DIVE}ma{SE_M_YAWN}witnes{SE_M_GRASSWHISTLE}man{SE_M_YAWN}kind{SE_M_GRASSWHISTLE}of\n"
	.string "POKéMO{SE_M_PSYBEAM2}rarel{SE_M_YAWN}see{SE_M_ATTRACT}i{SE_M_ATTRACT}thi{SE_M_GRASSWHISTLE}region.\p"
	.string "And{SE_M_SUPERSONIC}you'l{SE_M_BATON_PASS}se{SE_M_REVERSAL}the{SE_M_MILK_DRINK}i{SE_M_ATTRACT}thei{SE_M_SAND_TOMB}wild,\n"
	.string "untame{SE_M_WATERFALL}stat{SE_M_REVERSAL}i{SE_M_ATTRACT}natura{SE_M_BATON_PASS}habitats.\p"
	.string "What'{SE_M_GRASSWHISTLE}more{SE_M_SUPERSONIC}we'v{SE_M_REVERSAL}throw{SE_M_ATTRACT}ope{SE_M_ATTRACT}the\n"
	.string "gate{SE_M_GRASSWHISTLE}t{SE_M_ATTRACT2}POKéMO{SE_M_PSYBEAM2}TRAINERS.\p"
	.string "You'r{SE_M_REVERSAL}encourage{SE_M_WATERFALL}t{SE_M_ATTRACT2}catc{SE_M_TRI_ATTACK}POKéMON\n"
	.string "fo{SE_M_SAND_TOMB}keeps!\p"
	.string "Com{SE_M_REVERSAL}i{SE_M_ATTRACT}an{SE_M_WATERFALL}enjo{SE_M_YAWN}th{SE_M_REVERSAL}SAFAR{SE_M_HEAL_BELL}ZONE!$"

J_Route121_SafariZoneEntrance_Text_WelcomeFirstTime:
	.string "Welcom{SE_M_REVERSAL}t{SE_M_ATTRACT2}th{SE_M_REVERSAL}SAFAR{SE_M_HEAL_BELL}ZONE!\n"
	.string "I{SE_M_GRASSWHISTLE}i{SE_M_SPIT_UP}you{SE_M_SAND_TOMB}firs{SE_M_SPIT_UP}tim{SE_M_REVERSAL}here?$"

J_Route121_SafariZoneEntrance_Text_ComeInAndEnjoy:
	.string "Com{SE_M_REVERSAL}i{SE_M_ATTRACT}an{SE_M_WATERFALL}enjo{SE_M_YAWN}th{SE_M_REVERSAL}SAFAR{SE_M_HEAL_BELL}ZONE!$"

J_Route121_SafariZoneEntrance_Text_FirstTimeInfo:
	.string "Whe{SE_M_ATTRACT}yo{SE_M_DIVE}ente{SE_M_SAND_TOMB}th{SE_M_REVERSAL}SAFAR{SE_M_HEAL_BELL}ZONE{SE_M_SUPERSONIC}you\n"
	.string "star{SE_M_SPIT_UP}wit{SE_M_TRI_ATTACK}3{SE_M_BITE}SAFAR{SE_M_HEAL_BELL}BALL{SE_M_SKETCH}for\l"
	.string "catchin{SE_M_SANDSTORM}POKéMON.\p"
	.string "Th{SE_M_REVERSAL}SAFAR{SE_M_HEAL_BELL}Gam{SE_M_REVERSAL}i{SE_M_GRASSWHISTLE}ove{SE_M_SAND_TOMB}whe{SE_M_ATTRACT}yo{SE_M_DIVE}run\n"
	.string "ou{SE_M_SPIT_UP}o{SE_M_ACID_ARMOR}SAFAR{SE_M_HEAL_BELL}BALLS{SE_M_SUPERSONIC}o{SE_M_SAND_TOMB}whe{SE_M_ATTRACT}you've\l"
	.string "walke{SE_M_WATERFALL}50{SE_M_BITE}steps.\p"
	.string "Com{SE_M_REVERSAL}i{SE_M_ATTRACT}an{SE_M_WATERFALL}enjo{SE_M_YAWN}th{SE_M_REVERSAL}SAFAR{SE_M_HEAL_BELL}ZONE!$"

J_Route121_SafariZoneEntrance_Text_WouldYouLikeToPlay:
	.string "Welcom{SE_M_REVERSAL}t{SE_M_ATTRACT2}th{SE_M_REVERSAL}SAFAR{SE_M_HEAL_BELL}ZONE!\p"
	.string "Al{SE_M_BATON_PASS}yo{SE_M_DIVE}ca{SE_M_ATTRACT}catc{SE_M_TRI_ATTACK}fo{SE_M_SAND_TOMB}jus{SE_M_SPIT_UP}¥500!\n"
	.string "Woul{SE_M_WATERFALL}yo{SE_M_DIVE}lik{SE_M_REVERSAL}t{SE_M_ATTRACT2}pla{SE_M_YAWN}{SE_M_CHARGE}SAFAR{SE_M_HEAL_BELL}Game?$"

J_Route121_SafariZoneEntrance_Text_PlayAnotherTime:
	.string "Okay.\n"
	.string "Pleas{SE_M_REVERSAL}pla{SE_M_YAWN}anothe{SE_M_SAND_TOMB}time!$"

J_Route121_SafariZoneEntrance_Text_NotEnoughMoney:
	.string "Yo{SE_M_DIVE}don'{SE_M_SPIT_UP}hav{SE_M_REVERSAL}enoug{SE_M_TRI_ATTACK}money.\n"
	.string "Sorry.$"

J_Route121_SafariZoneEntrance_Text_ThatWillBe500Please:
	.string "Tha{SE_M_SPIT_UP}wil{SE_M_BATON_PASS}b{SE_M_REVERSAL}¥500{SE_M_SUPERSONIC}please.$"

J_Route121_SafariZoneEntrance_Text_HereAreYourSafariBalls:
	.string "Her{SE_M_REVERSAL}ar{SE_M_REVERSAL}you{SE_M_SAND_TOMB}SAFAR{SE_M_HEAL_BELL}BALLS.$"

J_Route121_SafariZoneEntrance_Text_Received30SafariBalls:
	.string "{PLAYER} receive{SE_M_WATERFALL}3{SE_M_BITE}SAFAR{SE_M_HEAL_BELL}BALLS.$"

J_Route121_SafariZoneEntrance_Text_PleaseEnjoyYourself:
	.string "We'l{SE_M_BATON_PASS}le{SE_M_SPIT_UP}yo{SE_M_DIVE}kno{SE_M_TWISTER}whe{SE_M_ATTRACT}you{SE_M_SAND_TOMB}game\n"
	.string "i{SE_M_GRASSWHISTLE}over.\p"
	.string "So{SE_M_SUPERSONIC}unti{SE_M_BATON_PASS}then{SE_M_SUPERSONIC}enjo{SE_M_YAWN}yourself{SE_M_SUPERSONIC}please!\n"
	.string "Of{SE_M_ACID_ARMOR}yo{SE_M_DIVE}g{SE_M_ATTRACT2}o{SE_M_ATTRACT}you{SE_M_SAND_TOMB}wil{SE_M_WATERFALL}excursion!$"

J_Route121_SafariZoneEntrance_Text_PCIsFull:
	.string "Excus{SE_M_REVERSAL}me!\n"
	.string "You{SE_M_SAND_TOMB}P{SE_M_PSYBEAM}BO{SE_M_LOCK_ON}i{SE_M_GRASSWHISTLE}full.$"

J_Route121_SafariZoneEntrance_Text_YouNeedPokeblockCase:
	.string "Excus{SE_M_REVERSAL}me!\n"
	.string "Yo{SE_M_DIVE}see{SE_M_MILK_DRINK}t{SE_M_ATTRACT2}b{SE_M_REVERSAL}withou{SE_M_SPIT_UP}{SE_M_CHARGE}{POKEBLOCK} CASE.\p"
	.string "You{SE_M_SAND_TOMB}SAFAR{SE_M_HEAL_BELL}Gam{SE_M_REVERSAL}wil{SE_M_BATON_PASS}b{SE_M_REVERSAL}muc{SE_M_TRI_ATTACK}more\n"
	.string "fruitfu{SE_M_BATON_PASS}i{SE_M_ACID_ARMOR}yo{SE_M_DIVE}us{SE_M_REVERSAL}{POKEBLOCK}S.\p"
	.string "Pleas{SE_M_REVERSAL}com{SE_M_REVERSAL}bac{SE_M_ENCORE2}wit{SE_M_TRI_ATTACK}{SE_M_CHARGE}{POKEBLOCK} CASE.\p"
	.string "Yo{SE_M_DIVE}ma{SE_M_YAWN}obtai{SE_M_ATTRACT}{SE_M_CHARGE}{POKEBLOCK} CAS{SE_M_SWORDS_DANCE}from\n"
	.string "tha{SE_M_SPIT_UP}bo{SE_M_YAWN}ove{SE_M_SAND_TOMB}there.$"

J_SafariZone_South_Text_StillHaveTimeExit:
	.string "Yo{SE_M_DIVE}stil{SE_M_BATON_PASS}hav{SE_M_REVERSAL}tim{SE_M_REVERSAL}left{SE_M_PERISH_SONG}Woul{SE_M_WATERFALL}yo{SE_M_DIVE}like\n"
	.string "t{SE_M_ATTRACT2}exi{SE_M_SPIT_UP}th{SE_M_REVERSAL}SAFAR{SE_M_HEAL_BELL}ZON{SE_M_SWORDS_DANCE}now?$"

J_SafariZone_South_Text_EnjoyTheRestOfYourAdventure:
	.string "Pleas{SE_M_REVERSAL}enjo{SE_M_YAWN}th{SE_M_REVERSAL}res{SE_M_SPIT_UP}o{SE_M_ACID_ARMOR}you{SE_M_SAND_TOMB}wild\n"
	.string "adventure!$"

J_SafariZone_South_Text_ExitEarlyThankYouForPlaying:
	.string "Okay.\p"
	.string "I'l{SE_M_BATON_PASS}tak{SE_M_REVERSAL}bac{SE_M_ENCORE2}you{SE_M_SAND_TOMB}remainin{SE_M_SANDSTORM}SAFARI\n"
	.string "BALLS.\p"
	.string "Than{SE_M_ENCORE2}yo{SE_M_DIVE}fo{SE_M_SAND_TOMB}playing.\n"
	.string "W{SE_M_REVERSAL}hop{SE_M_REVERSAL}t{SE_M_ATTRACT2}se{SE_M_REVERSAL}yo{SE_M_DIVE}again.$"

J_SafariZone_South_Text_GoodLuck:
	.string "Goo{SE_M_WATERFALL}luck!\p"
	.string "I{SE_M_ACID_ARMOR}yo{SE_M_DIVE}nee{SE_M_WATERFALL}anything{SE_M_SUPERSONIC}don'{SE_M_SPIT_UP}hesitate\n"
	.string "t{SE_M_ATTRACT2}tel{SE_M_BATON_PASS}me{SE_M_SUPERSONIC}please!$"

J_SafariZone_South_Text_Boy:
	.string "Di{SE_M_WATERFALL}yo{SE_M_DIVE}know?\p"
	.string "I{SE_M_ACID_ARMOR}yo{SE_M_DIVE}pu{SE_M_SPIT_UP}{SE_M_CHARGE}{POKEBLOCK} i{SE_M_ATTRACT}tha{SE_M_SPIT_UP}squar{SE_M_REVERSAL}box,\n"
	.string "POKéMO{SE_M_PSYBEAM2}gathe{SE_M_SAND_TOMB}around.$"

J_SafariZone_South_Text_Man:
	.string "{SE_M_HEAL_BELL}wan{SE_M_SPIT_UP}t{SE_M_ATTRACT2}kee{SE_M_MORNING_SUN}goin{SE_M_SANDSTORM}deeper{SE_M_SUPERSONIC}bu{SE_M_SPIT_UP}I\n"
	.string "forgo{SE_M_SPIT_UP}t{SE_M_ATTRACT2}brin{SE_M_SANDSTORM}{SE_M_CHARGE}BIKE.\p"
	.string "Somethin{SE_M_SANDSTORM}tell{SE_M_GRASSWHISTLE}m{SE_M_REVERSAL}tha{SE_M_SPIT_UP}rar{SE_M_REVERSAL}POKéMON\n"
	.string "liv{SE_M_REVERSAL}i{SE_M_ATTRACT}th{SE_M_REVERSAL}outlyin{SE_M_SANDSTORM}areas.$"

J_SafariZone_Southwest_Text_Woman:
	.string "Sometimes{SE_M_SUPERSONIC}whe{SE_M_ATTRACT}{SE_M_HEAL_BELL}tos{SE_M_GRASSWHISTLE}{SE_M_CHARGE}{POKEBLOCK} a{SE_M_SPIT_UP}\n"
	.string "POKéMON{SE_M_SUPERSONIC}i{SE_M_SPIT_UP}get{SE_M_GRASSWHISTLE}ignored.\p"
	.string "D{SE_M_ATTRACT2}POKéMO{SE_M_PSYBEAM2}hav{SE_M_REVERSAL}like{SE_M_GRASSWHISTLE}an{SE_M_WATERFALL}dislikes\n"
	.string "abou{SE_M_SPIT_UP}wha{SE_M_SPIT_UP}the{SE_M_YAWN}eat?$"

J_SafariZone_Northwest_Text_Man:
	.string "Gasp{SE_M_DIZZY_PUNCH}Gasp…\n"
	.string "I…mad{SE_M_REVERSAL}i{SE_M_SPIT_UP}ou{SE_M_SPIT_UP}here…but…\p"
	.string "I'{SE_M_MILK_DRINK}exhausted{SE_M_DIZZY_PUNCH}{SE_M_HEAL_BELL}don'{SE_M_SPIT_UP}hav{SE_M_REVERSAL}the\n"
	.string "energ{SE_M_YAWN}t{SE_M_ATTRACT2}catc{SE_M_TRI_ATTACK}POKéMON…$"

J_SafariZone_North_Text_Fisherman:
	.string "I'{SE_M_MILK_DRINK}o{SE_M_ATTRACT}{SE_M_CHARGE}missio{SE_M_ATTRACT}t{SE_M_ATTRACT2}fin{SE_M_WATERFALL}WATE{SE_M_MINIMIZE}POKéMON\n"
	.string "yo{SE_M_DIVE}don'{SE_M_SPIT_UP}se{SE_M_REVERSAL}i{SE_M_ATTRACT}HOENN.\p"
	.string "D{SE_M_ATTRACT2}yo{SE_M_DIVE}hav{SE_M_REVERSAL}an{SE_M_YAWN}ide{SE_M_CHARGE}wher{SE_M_REVERSAL}th{SE_M_REVERSAL}lak{SE_M_REVERSAL}is?$"

J_SafariZone_North_Text_Man:
	.string "I'{SE_M_MILK_DRINK}goin{SE_M_SANDSTORM}t{SE_M_ATTRACT2}catc{SE_M_TRI_ATTACK}{SE_M_CHARGE}lo{SE_M_SPIT_UP}o{SE_M_ACID_ARMOR}rar{SE_M_REVERSAL}POKéMON\n"
	.string "her{SE_M_REVERSAL}an{SE_M_WATERFALL}trad{SE_M_REVERSAL}the{SE_M_MILK_DRINK}wit{SE_M_TRI_ATTACK}m{SE_M_YAWN}friends!$"

J_SafariZone_South_Text_Youngster:
	.string "{SE_M_HEAL_BELL}pu{SE_M_SPIT_UP}{SE_M_CHARGE}{POKEBLOCK} o{SE_M_ATTRACT}th{SE_M_REVERSAL}{POKEBLOCK} FEEDER.\n"
	.string "Bu{SE_M_SPIT_UP}i{SE_M_SPIT_UP}seem{SE_M_GRASSWHISTLE}t{SE_M_ATTRACT2}hav{SE_M_REVERSAL}disappeared.\p"
	.string "{SE_M_HEAL_BELL}gues{SE_M_GRASSWHISTLE}POKéMO{SE_M_PSYBEAM2}mus{SE_M_SPIT_UP}hav{SE_M_REVERSAL}eate{SE_M_ATTRACT}it\n"
	.string "withou{SE_M_SPIT_UP}m{SE_M_REVERSAL}noticing.$"

J_Route121_SafariZoneEntrance_Text_TrainerTip:
	.string "SAFAR{SE_M_HEAL_BELL}ZON{SE_M_SWORDS_DANCE}TRAINE{SE_M_MINIMIZE}TIP!\p"
	.string "Thro{SE_M_TWISTER}{POKEBLOCK}{SE_M_SKETCH}a{SE_M_SPIT_UP}wil{SE_M_WATERFALL}POKéMO{SE_M_PSYBEAM2}t{SE_M_ATTRACT2}make\n"
	.string "the{SE_M_MILK_DRINK}les{SE_M_GRASSWHISTLE}likel{SE_M_YAWN}t{SE_M_ATTRACT2}flee.$"

J_SafariZone_Southwest_Text_RestHouseSign:
	.string "“Reliev{SE_M_REVERSAL}you{SE_M_SAND_TOMB}tire{SE_M_WATERFALL}feet.”\n"
	.string "RES{SE_M_SWIFT}HOUSE$"

J_SafariZone_RestHouse_Text_Youngster:
	.string "{SE_M_HEAL_BELL}don'{SE_M_SPIT_UP}hav{SE_M_REVERSAL}an{SE_M_YAWN}{POKEBLOCK}S{SE_M_SUPERSONIC}bu{SE_M_SPIT_UP}{SE_M_HEAL_BELL}caught\n"
	.string "{SE_M_CHARGE}goo{SE_M_WATERFALL}numbe{SE_M_SAND_TOMB}o{SE_M_ACID_ARMOR}POKéMON.\p"
	.string "Yo{SE_M_DIVE}ca{SE_M_ATTRACT}improv{SE_M_REVERSAL}you{SE_M_SAND_TOMB}chance{SE_M_GRASSWHISTLE}o{SE_M_ACID_ARMOR}making\n"
	.string "{SE_M_CHARGE}catc{SE_M_TRI_ATTACK}b{SE_M_YAWN}gettin{SE_M_SANDSTORM}close{SE_M_SAND_TOMB}t{SE_M_ATTRACT2}them\l"
	.string "befor{SE_M_REVERSAL}throwin{SE_M_SANDSTORM}{SE_M_CHARGE}SAFAR{SE_M_HEAL_BELL}BALL.$"

J_SafariZone_RestHouse_Text_PsychicM:
	.string "I{SE_M_ACID_ARMOR}yo{SE_M_DIVE}us{SE_M_REVERSAL}{POKEBLOCK}S{SE_M_SUPERSONIC}wil{SE_M_WATERFALL}POKéMO{SE_M_PSYBEAM2}won't\n"
	.string "b{SE_M_REVERSAL}s{SE_M_ATTRACT2}quic{SE_M_ENCORE2}t{SE_M_ATTRACT2}ru{SE_M_ATTRACT}away.\p"
	.string "It'{SE_M_GRASSWHISTLE}no{SE_M_SPIT_UP}muc{SE_M_TRI_ATTACK}us{SE_M_REVERSAL}t{SE_M_ATTRACT2}giv{SE_M_REVERSAL}{POKEBLOCK}{SE_M_SKETCH}to\n"
	.string "POKéMO{SE_M_PSYBEAM2}tha{SE_M_SPIT_UP}don'{SE_M_SPIT_UP}fle{SE_M_REVERSAL}easily.$"

J_SafariZone_RestHouse_Text_FatMan:
	.string "I{SE_M_ACID_ARMOR}yo{SE_M_DIVE}pu{SE_M_SPIT_UP}{SE_M_CHARGE}{POKEBLOCK} o{SE_M_ATTRACT}th{SE_M_REVERSAL}FEEDER,\n"
	.string "POKéMO{SE_M_PSYBEAM2}ar{SE_M_REVERSAL}attracte{SE_M_WATERFALL}t{SE_M_ATTRACT2}it.\p"
	.string "{SE_M_HEAL_BELL}thin{SE_M_ENCORE2}POKéMO{SE_M_PSYBEAM2}wit{SE_M_TRI_ATTACK}th{SE_M_REVERSAL}sam{SE_M_REVERSAL}sor{SE_M_SPIT_UP}of\n"
	.string "natur{SE_M_REVERSAL}ar{SE_M_REVERSAL}draw{SE_M_ATTRACT}b{SE_M_YAWN}{SE_M_CHARGE}certai{SE_M_ATTRACT}{POKEBLOCK}.$"

J_SafariZone_South_Text_AreaOffLimits1:
	.string "Thi{SE_M_GRASSWHISTLE}are{SE_M_CHARGE}i{SE_M_GRASSWHISTLE}stil{SE_M_BATON_PASS}unde{SE_M_SAND_TOMB}construction.\n"
	.string "It'{SE_M_GRASSWHISTLE}off-limits{SE_M_SUPERSONIC}sorry!$"

J_SafariZone_Southeast_Text_ExpansionIsFinished:
	.string "Th{SE_M_REVERSAL}SAFAR{SE_M_HEAL_BELL}ZONE'{SE_M_GRASSWHISTLE}expansio{SE_M_ATTRACT}project\n"
	.string "i{SE_M_GRASSWHISTLE}finishe{SE_M_WATERFALL}now.\p"
	.string "W{SE_M_REVERSAL}hop{SE_M_REVERSAL}yo{SE_M_DIVE}wil{SE_M_BATON_PASS}enjo{SE_M_YAWN}th{SE_M_REVERSAL}ne{SE_M_TWISTER}area.$"

J_SafariZone_South_Text_AreaOffLimits2:
	.string "Thi{SE_M_GRASSWHISTLE}are{SE_M_CHARGE}i{SE_M_GRASSWHISTLE}stil{SE_M_BATON_PASS}unde{SE_M_SAND_TOMB}construction.\n"
	.string "It'{SE_M_GRASSWHISTLE}off-limits{SE_M_SUPERSONIC}sorry!$"

J_SafariZone_Southeast_Text_LittleGirl:
	.string "Wow{SE_M_DRAGON_RAGE}Whee{SE_M_DRAGON_RAGE}{SE_M_HEAL_BELL}haven'{SE_M_SPIT_UP}see{SE_M_ATTRACT}an{SE_M_YAWN}of\n"
	.string "thes{SE_M_REVERSAL}POKéMO{SE_M_PSYBEAM2}before!$"

J_SafariZone_Southeast_Text_FatMan:
	.string "Th{SE_M_REVERSAL}POKéMO{SE_M_PSYBEAM2}i{SE_M_ATTRACT}thi{SE_M_GRASSWHISTLE}are{SE_M_CHARGE}ar{SE_M_REVERSAL}all\n"
	.string "ne{SE_M_TWISTER}t{SE_M_ATTRACT2}me.\p"
	.string "An{SE_M_WATERFALL}I'{SE_M_MILK_DRINK}allowe{SE_M_WATERFALL}t{SE_M_ATTRACT2}catc{SE_M_TRI_ATTACK}thes{SE_M_REVERSAL}rare\n"
	.string "POKéMON{SE_M_DRAGON_RAGE}To{SE_M_ATTRACT2}cool!$"

J_SafariZone_Southeast_Text_RichBoy:
	.string "Th{SE_M_REVERSAL}POKéMO{SE_M_PSYBEAM2}aroun{SE_M_WATERFALL}her{SE_M_REVERSAL}see{SE_M_MILK_DRINK}t{SE_M_ATTRACT2}be\n"
	.string "fro{SE_M_MILK_DRINK}somewher{SE_M_REVERSAL}othe{SE_M_SAND_TOMB}tha{SE_M_ATTRACT}HOENN.$"

J_SafariZone_Northeast_Text_Boy:
	.string "{SE_M_HEAL_BELL}onl{SE_M_YAWN}hav{SE_M_REVERSAL}{SE_M_CHARGE}coupl{SE_M_REVERSAL}SAFAR{SE_M_HEAL_BELL}BALL{SE_M_SKETCH}left.\p"
	.string "I'{SE_M_MILK_DRINK}havin{SE_M_SANDSTORM}{SE_M_CHARGE}har{SE_M_WATERFALL}tim{SE_M_REVERSAL}tryin{SE_M_SANDSTORM}to\n"
	.string "decid{SE_M_REVERSAL}wha{SE_M_SPIT_UP}{SE_M_HEAL_BELL}shoul{SE_M_WATERFALL}catch.$"

J_SafariZone_Northeast_Text_Woman:
	.string "{SE_M_HEAL_BELL}hear{SE_M_WATERFALL}tha{SE_M_SPIT_UP}yo{SE_M_DIVE}ca{SE_M_ATTRACT}se{SE_M_REVERSAL}PIKACH{SE_M_REFLECT}here.\n"
	.string "Wher{SE_M_REVERSAL}migh{SE_M_SPIT_UP}on{SE_M_REVERSAL}be?$"

J_SafariZone_Northeast_Text_Girl:
	.string "Oh{SE_M_SUPERSONIC}boo!\n"
	.string "{SE_M_HEAL_BELL}can'{SE_M_SPIT_UP}see{SE_M_MILK_DRINK}t{SE_M_ATTRACT2}catc{SE_M_TRI_ATTACK}anything!\p"
	.string "I'l{SE_M_BATON_PASS}en{SE_M_WATERFALL}u{SE_M_MORNING_SUN}wastin{SE_M_SANDSTORM}th{SE_M_REVERSAL}admission\n"
	.string "pric{SE_M_REVERSAL}i{SE_M_ACID_ARMOR}{SE_M_HEAL_BELL}don'{SE_M_SPIT_UP}catc{SE_M_TRI_ATTACK}something!$"

