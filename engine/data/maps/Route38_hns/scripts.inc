@ Johto (data/maps/Route38_hns/scripts.inc), as built into the FireRed game.

Route38_hns_MapScripts::
	map_script 3, Route38_OnTransition
	map_script 5, J_SetTimeEncounters
	.byte 0

Route38_OnTransition:
	callnative SetTimeBasedEncounters
	end

Route38_EventScript_Toby::
	trainerbattle_single 1057, Route38_Text_BirdKeeperTobySeen, Route38_Text_BirdKeeperTobyBeaten
	msgbox Route38_Text_BirdKeeperTobyAfter, MSGBOX_AUTOCLOSE
	end

Route38_EventScript_Chad::
	trainerbattle_single 1050, Route38_Text_SchoolboyChad1Seen, Route38_Text_SchoolboyChad1Beaten, Route38_EventScript_RegisterChad
	specialvar 32781, ShouldTryRematchBattle
	goto_if_eq 32781, TRUE, Route38_EventScript_RematchChad
	msgbox Route38_Text_SchoolboyChadAfter, MSGBOX_AUTOCLOSE
	end

Route38_EventScript_RegisterChad::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox Route38_Text_ChadRegister, MSGBOX_DEFAULT
	register_matchcall 1050
	release
	end

Route38_EventScript_RematchChad::
	trainerbattle_rematch 1050, Route38_Text_ChadRematchIntro, Route38_Text_ChadRematchDefeat
	msgbox Route38_Text_ChadPostRematch, MSGBOX_AUTOCLOSE
	end

Route38_EventScript_Dana::
	trainerbattle_single 1077, Route38_Text_LassDana1Seen, Route38_Text_LassDana1Beaten, Route38_EventScript_RegisterDana
	goto_if_set 8940, Route38_EventScript_DanaGiveItem
	specialvar 32781, ShouldTryRematchBattle
	goto_if_eq 32781, TRUE, Route38_EventScript_RematchDana
	msgbox Route38_Text_LassDanaAfter, MSGBOX_AUTOCLOSE
	end

Route38_EventScript_RegisterDana::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox Route38_Text_DanaRegister, MSGBOX_DEFAULT
	register_matchcall 1077
	release
	end

Route38_EventScript_RematchDana::
	trainerbattle_rematch 1077, Route38_Text_DanaRematchIntro, Route38_Text_DanaRematchDefeat
	msgbox Route38_Text_DanaPostRematch, MSGBOX_AUTOCLOSE
	end

Route38_EventScript_DanaGiveItem::
	msgbox Route38_Text_DanaHasItem, MSGBOX_DEFAULT
	giveitem 20618
	goto_if_eq 32781, FALSE, Route38_EventScript_DanaNoRoom
	clearflag 8940
	msgbox Route38_Text_DanaGaveItem, MSGBOX_AUTOCLOSE
	end

Route38_EventScript_DanaNoRoom::
	msgbox Route38_Text_DanaNoRoom, MSGBOX_AUTOCLOSE
	end

Route38_EventScript_Valerie::
	trainerbattle_single 1129, Route38_Text_BeautyValerieSeen, Route38_Text_BeautyValerieBeaten
	msgbox Route38_Text_BeautyValerieAfter, MSGBOX_AUTOCLOSE
	end

Route38_EventScript_Harry::
	trainerbattle_single 1265, Route38_Text_SailorHarrySeen, Route38_Text_SailorHarryBeaten
	msgbox Route38_Text_SailorHarryAfter, MSGBOX_AUTOCLOSE
	end

Route38_EventScript_Olivia::
	trainerbattle_single 1130, Route38_Text_BeautyOliviaSeen, Route38_Text_BeautyOliviaBeaten
	msgbox Route38_Text_BeautyOliviaAfter, MSGBOX_AUTOCLOSE
	end

Route38_EventScript_Sign1::
	lock
	msgbox Route38_Text_Sign, MSGBOX_SIGN
	closemessage
	release
	end

Route38_EventScript_Sign2::
	lock
	msgbox Route38_Text_WaterSign, MSGBOX_SIGN
	closemessage
	release
	end

Route38_EventScript_Item_LaxIncense::
	finditem ITEM_LAX_INCENSE
	end

Route38_Text_BirdKeeperTobySeen:
	.string "Fl{SE_M_YAWN}hig{SE_M_TRI_ATTACK}int{SE_M_ATTRACT2}th{SE_M_REVERSAL}sky,\n"
	.string "m{SE_M_YAWN}belove{SE_M_WATERFALL}bir{SE_M_WATERFALL}POKéMON!$"

Route38_Text_BirdKeeperTobyBeaten:
	.string "{SE_M_HEAL_BELL}fee{SE_M_BATON_PASS}lik{SE_M_REVERSAL}jus{SE_M_SPIT_UP}flying\n"
	.string "awa{SE_M_YAWN}now.$"

Route38_Text_BirdKeeperTobyAfter:
	.string "{SE_M_HEAL_BELL}pla{SE_M_ATTRACT}t{SE_M_ATTRACT2}trai{SE_M_ATTRACT}i{SE_M_ATTRACT}CIANWOO{SE_M_FAINT_ATTACK}CITY\n"
	.string "t{SE_M_ATTRACT2}teac{SE_M_TRI_ATTACK}m{SE_M_YAWN}POKéMO{SE_M_PSYBEAM2}ho{SE_M_TWISTER}t{SE_M_ATTRACT2}FLY.$"

Route38_Text_SchoolboyChad1Seen:
	.string "Le{SE_M_SPIT_UP}m{SE_M_REVERSAL}tr{SE_M_YAWN}something\n"
	.string "{SE_M_HEAL_BELL}learne{SE_M_WATERFALL}today.$"

Route38_Text_SchoolboyChad1Beaten:
	.string "{SE_M_HEAL_BELL}didn'{SE_M_SPIT_UP}stud{SE_M_YAWN}enough,\n"
	.string "{SE_M_HEAL_BELL}guess.$"

Route38_Text_SchoolboyChadAfter:
	.string "{SE_M_HEAL_BELL}hav{SE_M_REVERSAL}t{SE_M_ATTRACT2}tak{SE_M_REVERSAL}s{SE_M_ATTRACT2}many\n"
	.string "tests{SE_M_SUPERSONIC}{SE_M_HEAL_BELL}don'{SE_M_SPIT_UP}hav{SE_M_REVERSAL}much\l"
	.string "tim{SE_M_REVERSAL}fo{SE_M_SAND_TOMB}POKéMON.\p"
	.string "S{SE_M_ATTRACT2}whe{SE_M_ATTRACT}{SE_M_HEAL_BELL}d{SE_M_ATTRACT2}ge{SE_M_SPIT_UP}t{SE_M_ATTRACT2}play,\n"
	.string "{SE_M_HEAL_BELL}reall{SE_M_YAWN}concentrate.$"

Route38_Text_ChadRegister:
	.string "{SE_M_HEAL_BELL}hav{SE_M_REVERSAL}t{SE_M_ATTRACT2}tak{SE_M_REVERSAL}s{SE_M_ATTRACT2}many\n"
	.string "tests{SE_M_SUPERSONIC}{SE_M_HEAL_BELL}don'{SE_M_SPIT_UP}hav{SE_M_REVERSAL}much\l"
	.string "tim{SE_M_REVERSAL}fo{SE_M_SAND_TOMB}POKéMON.\p"
	.string "S{SE_M_ATTRACT2}whe{SE_M_ATTRACT}{SE_M_HEAL_BELL}d{SE_M_ATTRACT2}ge{SE_M_SPIT_UP}t{SE_M_ATTRACT2}play,\n"
	.string "{SE_M_HEAL_BELL}reall{SE_M_YAWN}concentrate.$"

Route38_Text_ChadRematchIntro:
	.string "Le{SE_M_SPIT_UP}m{SE_M_REVERSAL}tr{SE_M_YAWN}something\n"
	.string "{SE_M_HEAL_BELL}learne{SE_M_WATERFALL}today.$"

Route38_Text_ChadRematchDefeat:
	.string "{SE_M_HEAL_BELL}didn'{SE_M_SPIT_UP}stud{SE_M_YAWN}enough,\n"
	.string "{SE_M_HEAL_BELL}guess.$"

Route38_Text_ChadPostRematch:
	.string "{SE_M_HEAL_BELL}hav{SE_M_REVERSAL}t{SE_M_ATTRACT2}tak{SE_M_REVERSAL}s{SE_M_ATTRACT2}many\n"
	.string "tests{SE_M_SUPERSONIC}{SE_M_HEAL_BELL}don'{SE_M_SPIT_UP}hav{SE_M_REVERSAL}much\l"
	.string "tim{SE_M_REVERSAL}fo{SE_M_SAND_TOMB}POKéMON.\p"
	.string "S{SE_M_ATTRACT2}whe{SE_M_ATTRACT}{SE_M_HEAL_BELL}d{SE_M_ATTRACT2}ge{SE_M_SPIT_UP}t{SE_M_ATTRACT2}play,\n"
	.string "{SE_M_HEAL_BELL}reall{SE_M_YAWN}concentrate.$"

Route38_Text_LassDana1Seen:
	.string "Yo{SE_M_DIVE}see{SE_M_MILK_DRINK}t{SE_M_ATTRACT2}b{SE_M_REVERSAL}goo{SE_M_WATERFALL}at\n"
	.string "POKéMON.\p"
	.string "I{SE_M_ACID_ARMOR}yo{SE_M_DIVE}are{SE_M_SUPERSONIC}ho{SE_M_TWISTER}about\n"
	.string "givin{SE_M_SANDSTORM}m{SE_M_REVERSAL}som{SE_M_REVERSAL}advice?$"

Route38_Text_LassDana1Beaten:
	.string "{SE_M_HEAL_BELL}see{SE_M_PERISH_SONG}S{SE_M_ATTRACT2}yo{SE_M_DIVE}ca{SE_M_ATTRACT}battle\n"
	.string "tha{SE_M_SPIT_UP}way.$"

Route38_Text_LassDanaAfter:
	.string "{SE_M_HEAL_BELL}kno{SE_M_TWISTER}somethin{SE_M_SANDSTORM}good!\p"
	.string "MOOMO{SE_M_SOLAR_BEAM}FARM'{SE_M_GRASSWHISTLE}mil{SE_M_ENCORE2}is\n"
	.string "famou{SE_M_GRASSWHISTLE}fo{SE_M_SAND_TOMB}it{SE_M_GRASSWHISTLE}flavor.$"

Route38_Text_BeautyValerieSeen:
	.string "Hi{SE_M_DRAGON_RAGE}Aren'{SE_M_SPIT_UP}yo{SE_M_DIVE}{SE_M_CHARGE}cute\n"
	.string "trainer!\p"
	.string "Ma{SE_M_YAWN}{SE_M_HEAL_BELL}se{SE_M_REVERSAL}you{SE_M_SAND_TOMB}POKéMON?$"

Route38_Text_BeautyValerieBeaten:
	.string "I'{SE_M_MILK_DRINK}gla{SE_M_WATERFALL}{SE_M_HEAL_BELL}go{SE_M_SPIT_UP}t{SE_M_ATTRACT2}see\n"
	.string "you{SE_M_SAND_TOMB}POKéMON!$"

Route38_Text_BeautyValerieAfter:
	.string "Whe{SE_M_ATTRACT}{SE_M_HEAL_BELL}se{SE_M_REVERSAL}POKéMON{SE_M_SUPERSONIC}it\n"
	.string "seem{SE_M_GRASSWHISTLE}t{SE_M_ATTRACT2}sooth{SE_M_REVERSAL}m{SE_M_YAWN}nerves.$"

Route38_Text_SailorHarrySeen:
	.string "I'v{SE_M_REVERSAL}bee{SE_M_ATTRACT}overseas{SE_M_SUPERSONIC}s{SE_M_ATTRACT2}I\n"
	.string "kno{SE_M_TWISTER}abou{SE_M_SPIT_UP}al{SE_M_BATON_PASS}sort{SE_M_GRASSWHISTLE}of\l"
	.string "POKéMON!$"

Route38_Text_SailorHarryBeaten:
	.string "You{SE_M_SAND_TOMB}skil{SE_M_BATON_PASS}i{SE_M_GRASSWHISTLE}worl{SE_M_WATERFALL}class!$"

Route38_Text_SailorHarryAfter:
	.string "Al{SE_M_BATON_PASS}kind{SE_M_GRASSWHISTLE}o{SE_M_ACID_ARMOR}peopl{SE_M_REVERSAL}around\n"
	.string "th{SE_M_REVERSAL}worl{SE_M_WATERFALL}liv{SE_M_REVERSAL}happil{SE_M_YAWN}with\l"
	.string "POKéMON.$"

Route38_Text_BeautyOliviaSeen:
	.string "Don'{SE_M_SPIT_UP}yo{SE_M_DIVE}thin{SE_M_ENCORE2}m{SE_M_YAWN}POKéMON\n"
	.string "an{SE_M_WATERFALL}{SE_M_HEAL_BELL}ar{SE_M_REVERSAL}beautiful?$"

Route38_Text_BeautyOliviaBeaten:
	.string "W{SE_M_REVERSAL}drin{SE_M_ENCORE2}MOOMO{SE_M_SOLAR_BEAM}MIL{SE_M_SNORE}every\n"
	.string "day.$"

Route38_Text_BeautyOliviaAfter:
	.string "MOOMO{SE_M_SOLAR_BEAM}MIL{SE_M_SNORE}i{SE_M_GRASSWHISTLE}goo{SE_M_WATERFALL}for\n"
	.string "beaut{SE_M_YAWN}an{SE_M_WATERFALL}health,\p"
	.string "bu{SE_M_SPIT_UP}inconveniently{SE_M_SUPERSONIC}they\n"
	.string "onl{SE_M_YAWN}sel{SE_M_BATON_PASS}on{SE_M_REVERSAL}bottl{SE_M_REVERSAL}a{SE_M_SPIT_UP}{SE_M_CHARGE}time.$"

Route38_Text_Sign:
	.string "ROUT{SE_M_SWORDS_DANCE}38\p"
	.string "OLIVIN{SE_M_SWORDS_DANCE}CIT{SE_M_MOONLIGHT}{SE_M_PAY_DAY}ECRUTEA{SE_M_SNORE}CITY$"

Route38_Text_TrainerTips:
	.string "TRAINE{SE_M_MINIMIZE}TIPS\p"
	.string "I{SE_M_ACID_ARMOR}{SE_M_CHARGE}POKéMO{SE_M_PSYBEAM2}i{SE_M_GRASSWHISTLE}tryin{SE_M_SANDSTORM}to\n"
	.string "evolve{SE_M_SUPERSONIC}yo{SE_M_DIVE}ca{SE_M_ATTRACT}sto{SE_M_MORNING_SUN}it.\p"
	.string "Pres{SE_M_GRASSWHISTLE}th{SE_M_REVERSAL}{SE_M_LICK}Butto{SE_M_ATTRACT}during\n"
	.string "evolutio{SE_M_ATTRACT}t{SE_M_ATTRACT2}cance{SE_M_BATON_PASS}it.\p"
	.string "Tha{SE_M_SPIT_UP}startle{SE_M_GRASSWHISTLE}th{SE_M_REVERSAL}POKéMON\n"
	.string "an{SE_M_WATERFALL}stop{SE_M_GRASSWHISTLE}it{SE_M_GRASSWHISTLE}evolution.$"

Route38_Text_WaterSign:
	.string "N{SE_M_SOLAR_BEAM}SWIMMIN{SE_M_SWAGGER}O{SE_M_MINIMIZE}FISHING.\n"
	.string "WATE{SE_M_MINIMIZE}FO{SE_M_MINIMIZE}FARMIN{SE_M_SWAGGER}ONLY.\p"
	.string "-ECRUTEA{SE_M_SNORE}COUNCIL$"

Route38_Text_DanaRegister:
	.string "{SE_M_HEAL_BELL}kno{SE_M_TWISTER}somethin{SE_M_SANDSTORM}good!\p"
	.string "MOOMO{SE_M_SOLAR_BEAM}FARM'{SE_M_GRASSWHISTLE}mil{SE_M_ENCORE2}is\n"
	.string "famou{SE_M_GRASSWHISTLE}fo{SE_M_SAND_TOMB}it{SE_M_GRASSWHISTLE}flavor.$"

Route38_Text_DanaRematchIntro:
	.string "Yo{SE_M_DIVE}see{SE_M_MILK_DRINK}t{SE_M_ATTRACT2}b{SE_M_REVERSAL}goo{SE_M_WATERFALL}at\n"
	.string "POKéMON.\p"
	.string "I{SE_M_ACID_ARMOR}yo{SE_M_DIVE}are{SE_M_SUPERSONIC}ho{SE_M_TWISTER}about\n"
	.string "givin{SE_M_SANDSTORM}m{SE_M_REVERSAL}som{SE_M_REVERSAL}advice?$"

Route38_Text_DanaRematchDefeat:
	.string "{SE_M_HEAL_BELL}see{SE_M_PERISH_SONG}S{SE_M_ATTRACT2}yo{SE_M_DIVE}ca{SE_M_ATTRACT}battle\n"
	.string "tha{SE_M_SPIT_UP}way.$"

Route38_Text_DanaPostRematch:
	.string "{SE_M_HEAL_BELL}kno{SE_M_TWISTER}somethin{SE_M_SANDSTORM}good!\p"
	.string "MOOMO{SE_M_SOLAR_BEAM}FARM'{SE_M_GRASSWHISTLE}mil{SE_M_ENCORE2}is\n"
	.string "famou{SE_M_GRASSWHISTLE}fo{SE_M_SAND_TOMB}it{SE_M_GRASSWHISTLE}flavor.$"

Route38_Text_DanaHasItem:
	.string "Hey{SE_M_DRAGON_RAGE}{SE_M_HEAL_BELL}foun{SE_M_WATERFALL}something\n"
	.string "interesting!\p"
	.string "Here{SE_M_SUPERSONIC}yo{SE_M_DIVE}ca{SE_M_ATTRACT}hav{SE_M_REVERSAL}it!$"

Route38_Text_DanaGaveItem:
	.string "I'l{SE_M_BATON_PASS}le{SE_M_SPIT_UP}yo{SE_M_DIVE}kno{SE_M_TWISTER}i{SE_M_ACID_ARMOR}{SE_M_HEAL_BELL}find\n"
	.string "anythin{SE_M_SANDSTORM}else!$"

Route38_Text_DanaNoRoom:
	.string "Hmm{SE_M_SUPERSONIC}you{SE_M_SAND_TOMB}BA{SE_M_SWAGGER}i{SE_M_GRASSWHISTLE}full.\p"
	.string "Com{SE_M_REVERSAL}bac{SE_M_ENCORE2}whe{SE_M_ATTRACT}yo{SE_M_DIVE}hav{SE_M_REVERSAL}room.$"

