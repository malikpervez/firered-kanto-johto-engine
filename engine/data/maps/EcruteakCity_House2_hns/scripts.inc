@ Johto (data/maps/EcruteakCity_House2_hns/scripts.inc), as built into the FireRed game.

EcruteakCity_House2_hns_MapScripts::
	.byte 0

Ecruteak_Text_ItemfinderAdventure:
	.string "Ah{SE_M_PERISH_SONG}You'r{SE_M_REVERSAL}o{SE_M_ATTRACT}a{SE_M_ATTRACT}adventur{SE_M_REVERSAL}with\n"
	.string "you{SE_M_SAND_TOMB}POKéMON?\p"
	.string "Well{SE_M_SUPERSONIC}what'{SE_M_GRASSWHISTLE}a{SE_M_ATTRACT}adventur{SE_M_REVERSAL}without\n"
	.string "treasur{SE_M_REVERSAL}hunting?\p"
	.string "A{SE_M_MILK_DRINK}{SE_M_HEAL_BELL}right{SE_M_SUPERSONIC}o{SE_M_SAND_TOMB}a{SE_M_MILK_DRINK}{SE_M_HEAL_BELL}right?$"

Ecruteak_Text_ItemfinderTrueSpirit:
	.string "Good{SE_M_DRAGON_RAGE}Yo{SE_M_DIVE}understan{SE_M_WATERFALL}th{SE_M_REVERSAL}true\n"
	.string "spiri{SE_M_SPIT_UP}o{SE_M_ACID_ARMOR}adventure.\p"
	.string "{SE_M_HEAL_BELL}lik{SE_M_REVERSAL}that{SE_M_DRAGON_RAGE}Tak{SE_M_REVERSAL}thi{SE_M_GRASSWHISTLE}wit{SE_M_TRI_ATTACK}you.$"

Ecruteak_Text_ItemfinderExplanation:
	.string "Ther{SE_M_REVERSAL}ar{SE_M_REVERSAL}man{SE_M_YAWN}item{SE_M_GRASSWHISTLE}lyin{SE_M_SANDSTORM}about\n"
	.string "tha{SE_M_SPIT_UP}aren'{SE_M_SPIT_UP}obvious.\p"
	.string "Us{SE_M_REVERSAL}DOWSIN{SE_M_SWAGGER}MACHIN{SE_M_SWORDS_DANCE}t{SE_M_ATTRACT2}chec{SE_M_ENCORE2}i{SE_M_ACID_ARMOR}there\n"
	.string "i{SE_M_GRASSWHISTLE}a{SE_M_ATTRACT}ite{SE_M_MILK_DRINK}o{SE_M_ATTRACT}th{SE_M_REVERSAL}groun{SE_M_WATERFALL}nea{SE_M_SAND_TOMB}you.\p"
	.string "I{SE_M_SPIT_UP}doesn'{SE_M_SPIT_UP}sho{SE_M_TWISTER}th{SE_M_REVERSAL}exac{SE_M_SPIT_UP}spot,\n"
	.string "s{SE_M_ATTRACT2}you'l{SE_M_BATON_PASS}hav{SE_M_REVERSAL}t{SE_M_ATTRACT2}loo{SE_M_ENCORE2}yourself.\p"
	.string "O{SE_M_TRI_ATTACK}yeah--{SE_M_HEAL_BELL}hear{SE_M_WATERFALL}ther{SE_M_REVERSAL}ar{SE_M_REVERSAL}items\n"
	.string "i{SE_M_ATTRACT}ECRUTEAK'{SE_M_GRASSWHISTLE}BURNE{SE_M_FAINT_ATTACK}TOWER.$"

Ecruteak_Text_ItemfinderToEachHisOwn:
	.string "Oh{SE_M_DIZZY_PUNCH}T{SE_M_ATTRACT2}eac{SE_M_TRI_ATTACK}hi{SE_M_GRASSWHISTLE}own{SE_M_SUPERSONIC}{SE_M_HEAL_BELL}suppose…$"

EcruteakCity_House2_EventScript_ItemFinderMan::
	lock
	faceplayer
	checkitem ITEM_DOWSING_MACHINE
	goto_if_eq 32781, TRUE, EcruteakCity_House2_EventScript_AlreadyGotItemfinder
	msgbox Ecruteak_Text_ItemfinderAdventure, MSGBOX_YESNO
	goto_if_eq 32781, TRUE, EcruteakCity_House2_EventScript_GiveItemFinder
	msgbox Ecruteak_Text_ItemfinderToEachHisOwn, MSGBOX_DEFAULT
	closemessage
	release
	end

EcruteakCity_House2_EventScript_GiveItemFinder::
	msgbox Ecruteak_Text_ItemfinderTrueSpirit, MSGBOX_DEFAULT
	giveitem ITEM_DOWSING_MACHINE

EcruteakCity_House2_EventScript_AlreadyGotItemfinder::
	msgbox Ecruteak_Text_ItemfinderExplanation, MSGBOX_DEFAULT
	closemessage
	release
	end

EcruteakCity_House2_EventScript_Book::
	lock
	msgbox Ecruteak_Text_HistoryBook, MSGBOX_YESNO
	goto_if_eq 32781, TRUE, EcruteakCity_House2_EventScript_Book2
	closemessage
	release
	end

EcruteakCity_House2_EventScript_Book2::
	msgbox Ecruteak_Text_TwoTowers, MSGBOX_YESNO
	goto_if_eq 32781, TRUE, EcruteakCity_House2_EventScript_Book3
	release
	end

EcruteakCity_House2_EventScript_Book3::
	msgbox Ecruteak_Text_ThreeMon, MSGBOX_DEFAULT
	closemessage
	release
	end

Ecruteak_Text_ItemFinderMan::
	.string "ECRUTEA{SE_M_SNORE}i{SE_M_GRASSWHISTLE}{SE_M_CHARGE}ver{SE_M_YAWN}ol{SE_M_WATERFALL}city.\n"
	.string "Man{SE_M_YAWN}generation{SE_M_GRASSWHISTLE}passe{SE_M_WATERFALL}down\l"
	.string "thei{SE_M_SAND_TOMB}histor{SE_M_YAWN}i{SE_M_ATTRACT}book{SE_M_GRASSWHISTLE}lik{SE_M_REVERSAL}these.$"

Ecruteak_Text_HistoryBook:
	.string "HISTOR{SE_M_MOONLIGHT}O{SE_M_LEER}ECRUTEAK\p"
	.string "Wan{SE_M_SPIT_UP}t{SE_M_ATTRACT2}rea{SE_M_WATERFALL}it?$"

Ecruteak_Text_TwoTowers:
	.string "I{SE_M_ATTRACT}ECRUTEAK{SE_M_SUPERSONIC}ther{SE_M_REVERSAL}wer{SE_M_REVERSAL}tw{SE_M_ATTRACT2}towers.\p"
	.string "Eac{SE_M_TRI_ATTACK}towe{SE_M_SAND_TOMB}wa{SE_M_GRASSWHISTLE}th{SE_M_REVERSAL}roos{SE_M_SPIT_UP}of\n"
	.string "powerfu{SE_M_BATON_PASS}flyin{SE_M_SANDSTORM}POKéMON.\p"
	.string "Bu{SE_M_SPIT_UP}on{SE_M_REVERSAL}o{SE_M_ACID_ARMOR}th{SE_M_REVERSAL}tower{SE_M_GRASSWHISTLE}burne{SE_M_WATERFALL}to\n"
	.string "th{SE_M_REVERSAL}ground.\p"
	.string "Th{SE_M_REVERSAL}tw{SE_M_ATTRACT2}POKéMO{SE_M_PSYBEAM2}haven'{SE_M_SPIT_UP}bee{SE_M_ATTRACT}seen\n"
	.string "since…\p"
	.string "Kee{SE_M_MORNING_SUN}reading?$"

Ecruteak_Text_ThreeMon:
	.string "ECRUTEA{SE_M_SNORE}wa{SE_M_GRASSWHISTLE}als{SE_M_ATTRACT2}hom{SE_M_REVERSAL}t{SE_M_ATTRACT2}three\n"
	.string "POKéMO{SE_M_PSYBEAM2}tha{SE_M_SPIT_UP}race{SE_M_WATERFALL}aroun{SE_M_WATERFALL}th{SE_M_REVERSAL}town.\p"
	.string "The{SE_M_YAWN}wer{SE_M_REVERSAL}sai{SE_M_WATERFALL}t{SE_M_ATTRACT2}hav{SE_M_REVERSAL}bee{SE_M_ATTRACT}born\n"
	.string "o{SE_M_ACID_ARMOR}water{SE_M_SUPERSONIC}lightnin{SE_M_SANDSTORM}an{SE_M_WATERFALL}fire.\p"
	.string "Bu{SE_M_SPIT_UP}the{SE_M_YAWN}coul{SE_M_WATERFALL}no{SE_M_SPIT_UP}contai{SE_M_ATTRACT}their\n"
	.string "excessiv{SE_M_REVERSAL}power.\p"
	.string "S{SE_M_ATTRACT2}the{SE_M_YAWN}sa{SE_M_YAWN}th{SE_M_REVERSAL}thre{SE_M_REVERSAL}ra{SE_M_ATTRACT}lik{SE_M_REVERSAL}the\n"
	.string "win{SE_M_WATERFALL}of{SE_M_ACID_ARMOR}int{SE_M_ATTRACT2}th{SE_M_REVERSAL}grassland.$"

