@ Johto (data/maps/CianwoodHouse1_hns/scripts.inc), as built into the FireRed game.

CianwoodHouse1_hns_MapScripts::
	.byte 0

CianwoodHouse1_EventScript_Hermit::
	lock
	faceplayer
	msgbox CianwoodCity_Text_OldManIntro, MSGBOX_DEFAULT
	goto_if_eq 20577, 2, CianwoodHouse1_EventScript_HermitHooh
	checkitem ITEM_TIDAL_BELL
	goto_if_eq 32781, TRUE, CianwoodHouse1_EventScript_HermitTidalBell
	msgbox CianwoodCity_Text_WhirlIslandsStory, MSGBOX_DEFAULT
	closemessage
	release
	end

CianwoodHouse1_EventScript_HermitTidalBell::
	msgbox CianwoodCity_Text_TidalBellReaction, MSGBOX_DEFAULT
	closemessage
	release
	end

CianwoodHouse1_EventScript_HermitHooh::
	checkitem ITEM_CLEAR_BELL
	goto_if_eq 32781, TRUE, CianwoodHouse1_EventScript_HermitClearBell
	msgbox CianwoodCity_Text_BellTowerStory, MSGBOX_DEFAULT
	closemessage
	release
	end

CianwoodHouse1_EventScript_HermitClearBell::
	msgbox CianwoodCity_Text_ClearBellReaction, MSGBOX_DEFAULT
	closemessage
	release
	end

CianwoodCity_Text_OldManIntro:
	.string "{SE_M_HEAL_BELL}don'{SE_M_SPIT_UP}remembe{SE_M_SAND_TOMB}th{SE_M_REVERSAL}las{SE_M_SPIT_UP}time\n"
	.string "someon{SE_M_REVERSAL}cam{SE_M_REVERSAL}t{SE_M_ATTRACT2}visi{SE_M_SPIT_UP}me.\p"
	.string "Whe{SE_M_ATTRACT}{SE_M_HEAL_BELL}wa{SE_M_GRASSWHISTLE}young{SE_M_SUPERSONIC}{SE_M_HEAL_BELL}wa{SE_M_GRASSWHISTLE}a\n"
	.string "POKéMO{SE_M_PSYBEAM2}Trainer{SE_M_SUPERSONIC}too.\l"
	.string "{SE_M_HEAL_BELL}trie{SE_M_WATERFALL}t{SE_M_ATTRACT2}reac{SE_M_TRI_ATTACK}th{SE_M_REVERSAL}towe{SE_M_SAND_TOMB}and\l"
	.string "div{SE_M_REVERSAL}int{SE_M_ATTRACT2}th{SE_M_REVERSAL}ocean.\p"
	.string "{SE_M_HEAL_BELL}pu{SE_M_SPIT_UP}{SE_M_CHARGE}lo{SE_M_SPIT_UP}o{SE_M_ACID_ARMOR}effor{SE_M_SPIT_UP}int{SE_M_ATTRACT2}many\n"
	.string "things.\p"
	.string "Well{SE_M_SUPERSONIC}{SE_M_HEAL_BELL}tak{SE_M_REVERSAL}thing{SE_M_GRASSWHISTLE}eas{SE_M_YAWN}now,\n"
	.string "listenin{SE_M_SANDSTORM}t{SE_M_ATTRACT2}th{SE_M_REVERSAL}wave{SE_M_GRASSWHISTLE}an{SE_M_WATERFALL}winds\l"
	.string "o{SE_M_ATTRACT}thi{SE_M_GRASSWHISTLE}beach.$"

CianwoodCity_Text_BellTowerStory:
	.string "Hav{SE_M_REVERSAL}yo{SE_M_DIVE}hear{SE_M_WATERFALL}o{SE_M_ACID_ARMOR}th{SE_M_REVERSAL}TI{SE_M_PSYBEAM2}TOWER\n"
	.string "i{SE_M_ATTRACT}ECRUTEAK?\p"
	.string "Ther{SE_M_REVERSAL}ar{SE_M_REVERSAL}wha{SE_M_SPIT_UP}the{SE_M_YAWN}cal{SE_M_BATON_PASS}Clea{SE_M_SAND_TOMB}Bells\n"
	.string "o{SE_M_ATTRACT}to{SE_M_MORNING_SUN}o{SE_M_ACID_ARMOR}th{SE_M_REVERSAL}tower.\p"
	.string "The{SE_M_YAWN}don'{SE_M_SPIT_UP}mak{SE_M_REVERSAL}{SE_M_CHARGE}singl{SE_M_REVERSAL}noise\n"
	.string "i{SE_M_ATTRACT}stron{SE_M_SANDSTORM}winds.\p"
	.string "Ther{SE_M_REVERSAL}i{SE_M_GRASSWHISTLE}onl{SE_M_YAWN}on{SE_M_REVERSAL}wa{SE_M_YAWN}t{SE_M_ATTRACT2}mak{SE_M_REVERSAL}them\n"
	.string "ring.\p"
	.string "I{SE_M_SPIT_UP}i{SE_M_GRASSWHISTLE}t{SE_M_ATTRACT2}obtai{SE_M_ATTRACT}anothe{SE_M_SAND_TOMB}CLEA{SE_M_MINIMIZE}BELL\n"
	.string "jus{SE_M_SPIT_UP}lik{SE_M_REVERSAL}th{SE_M_REVERSAL}one{SE_M_GRASSWHISTLE}a{SE_M_SPIT_UP}th{SE_M_REVERSAL}to{SE_M_MORNING_SUN}o{SE_M_ACID_ARMOR}the\l"
	.string "tower.\p"
	.string "{SE_M_HEAL_BELL}wen{SE_M_SPIT_UP}afte{SE_M_SAND_TOMB}i{SE_M_SPIT_UP}whe{SE_M_ATTRACT}{SE_M_HEAL_BELL}wa{SE_M_GRASSWHISTLE}young.\n"
	.string "Bu{SE_M_SPIT_UP}{SE_M_HEAL_BELL}neve{SE_M_SAND_TOMB}go{SE_M_SPIT_UP}one...$"

CianwoodCity_Text_WhirlIslandsStory:
	.string "Hav{SE_M_REVERSAL}yo{SE_M_DIVE}hear{SE_M_WATERFALL}o{SE_M_ACID_ARMOR}WHIR{SE_M_BRICK_BREAK}ISLANDS?\p"
	.string "Ther{SE_M_REVERSAL}ar{SE_M_REVERSAL}wha{SE_M_SPIT_UP}the{SE_M_YAWN}cal{SE_M_BATON_PASS}Tida{SE_M_BATON_PASS}Bells\n"
	.string "a{SE_M_SPIT_UP}it{SE_M_GRASSWHISTLE}waterfal{SE_M_BATON_PASS}basin.\p"
	.string "The{SE_M_YAWN}don'{SE_M_SPIT_UP}mak{SE_M_REVERSAL}{SE_M_CHARGE}singl{SE_M_REVERSAL}noise\n"
	.string "i{SE_M_ATTRACT}crashin{SE_M_SANDSTORM}waves.\p"
	.string "Ther{SE_M_REVERSAL}i{SE_M_GRASSWHISTLE}onl{SE_M_YAWN}on{SE_M_REVERSAL}wa{SE_M_YAWN}t{SE_M_ATTRACT2}mak{SE_M_REVERSAL}them\n"
	.string "ring.\p"
	.string "I{SE_M_SPIT_UP}i{SE_M_GRASSWHISTLE}t{SE_M_ATTRACT2}obtai{SE_M_ATTRACT}anothe{SE_M_SAND_TOMB}Tida{SE_M_BATON_PASS}Bell\n"
	.string "jus{SE_M_SPIT_UP}lik{SE_M_REVERSAL}th{SE_M_REVERSAL}one{SE_M_GRASSWHISTLE}a{SE_M_SPIT_UP}th{SE_M_REVERSAL}waterfall\l"
	.string "basin.\p"
	.string "{SE_M_HEAL_BELL}wen{SE_M_SPIT_UP}afte{SE_M_SAND_TOMB}i{SE_M_SPIT_UP}whe{SE_M_ATTRACT}{SE_M_HEAL_BELL}wa{SE_M_GRASSWHISTLE}young.\n"
	.string "Bu{SE_M_SPIT_UP}{SE_M_HEAL_BELL}neve{SE_M_SAND_TOMB}go{SE_M_SPIT_UP}one...$"

CianwoodCity_Text_ClearBellReaction:
	.string "Oh{SE_M_DRAGON_RAGE}You'v{SE_M_REVERSAL}manage{SE_M_WATERFALL}t{SE_M_ATTRACT2}ge{SE_M_SPIT_UP}a\n"
	.string "CLEA{SE_M_MINIMIZE}BELL?\p"
	.string "Th{SE_M_REVERSAL}old-tim{SE_M_REVERSAL}drea{SE_M_MILK_DRINK}o{SE_M_ACID_ARMOR}mine...\n"
	.string "{SE_M_HEAL_BELL}see...\p"
	.string "You'v{SE_M_REVERSAL}don{SE_M_REVERSAL}it...\n"
	.string "...\l"
	.string "...{SE_M_HEAL_BELL}ca{SE_M_ATTRACT}hea{SE_M_SAND_TOMB}it!\p"
	.string "Th{SE_M_REVERSAL}chim{SE_M_REVERSAL}o{SE_M_ACID_ARMOR}th{SE_M_REVERSAL}bell{SE_M_GRASSWHISTLE}o{SE_M_ATTRACT}th{SE_M_REVERSAL}wind\n"
	.string "comin{SE_M_SANDSTORM}fro{SE_M_MILK_DRINK}th{SE_M_REVERSAL}directio{SE_M_ATTRACT}o{SE_M_ACID_ARMOR}the\l"
	.string "TI{SE_M_PSYBEAM2}TOWER...$"

CianwoodCity_Text_TidalBellReaction:
	.string "Oh{SE_M_DRAGON_RAGE}You'v{SE_M_REVERSAL}manage{SE_M_WATERFALL}t{SE_M_ATTRACT2}ge{SE_M_SPIT_UP}a\n"
	.string "Tida{SE_M_BATON_PASS}Bell?\p"
	.string "Th{SE_M_REVERSAL}old-tim{SE_M_REVERSAL}drea{SE_M_MILK_DRINK}o{SE_M_ACID_ARMOR}mine...\n"
	.string "{SE_M_HEAL_BELL}see...\p"
	.string "You'v{SE_M_REVERSAL}don{SE_M_REVERSAL}it...\n"
	.string "...\l"
	.string "...{SE_M_HEAL_BELL}ca{SE_M_ATTRACT}hea{SE_M_SAND_TOMB}it!\p"
	.string "Th{SE_M_REVERSAL}chim{SE_M_REVERSAL}o{SE_M_ACID_ARMOR}th{SE_M_REVERSAL}bell{SE_M_GRASSWHISTLE}o{SE_M_ATTRACT}th{SE_M_REVERSAL}sea\n"
	.string "breez{SE_M_REVERSAL}comin{SE_M_SANDSTORM}fro{SE_M_MILK_DRINK}th{SE_M_REVERSAL}directio{SE_M_ATTRACT}of\l"
	.string "th{SE_M_REVERSAL}WHIR{SE_M_BRICK_BREAK}ISLANDS...$"

