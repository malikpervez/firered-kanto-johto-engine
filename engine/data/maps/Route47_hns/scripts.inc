@ Johto (data/maps/Route47_hns/scripts.inc), as built into the FireRed game.

Route47_hns_MapScripts::
	.byte 0

Route47_EventScript_Hiker::
	trainerbattle_single 1297, Route47_Text_HikerSeen, Route47_Text_HikerBeaten
	msgbox Route47_Text_HikerAfter, MSGBOX_AUTOCLOSE
	end

Route47_Text_HikerSeen::
	.string "Longin{SE_M_SANDSTORM}fo{SE_M_SAND_TOMB}other{SE_M_GRASSWHISTLE}is...\n"
	.string "wha{SE_M_SPIT_UP}i{SE_M_SPIT_UP}is{SE_M_PERISH_SONG}\p"
	.string "Bu{SE_M_SPIT_UP}battle{SE_M_GRASSWHISTLE}ar{SE_M_REVERSAL}battles,\n"
	.string "s{SE_M_ATTRACT2}let'{SE_M_GRASSWHISTLE}go!$"

Route47_Text_HikerBeaten::
	.string "Wahaha!$"

Route47_Text_HikerAfter::
	.string "Afte{SE_M_SAND_TOMB}{SE_M_CHARGE}battl{SE_M_REVERSAL}yo{SE_M_DIVE}shoul{SE_M_WATERFALL}alway{SE_M_GRASSWHISTLE}leave\n"
	.string "wit{SE_M_TRI_ATTACK}{SE_M_CHARGE}partin{SE_M_SANDSTORM}laugh!$"

Route47_EventScript_Camper::
	trainerbattle_single 1371, Route47_Text_CamperSeen, Route47_Text_CamperBeaten
	msgbox Route47_Text_CamperAfter, MSGBOX_AUTOCLOSE
	end

Route47_Text_CamperSeen::
	.string "I'{SE_M_MILK_DRINK}no{SE_M_SPIT_UP}goo{SE_M_WATERFALL}wit{SE_M_TRI_ATTACK}larg{SE_M_REVERSAL}crowds{SE_M_SUPERSONIC}so\n"
	.string "I'{SE_M_MILK_DRINK}campin{SE_M_SANDSTORM}ou{SE_M_SPIT_UP}her{SE_M_REVERSAL}wit{SE_M_TRI_ATTACK}my\l"
	.string "POKéMON!$"

Route47_Text_CamperBeaten::
	.string "{SE_M_HEAL_BELL}shoul{SE_M_WATERFALL}b{SE_M_REVERSAL}heade{SE_M_WATERFALL}deepe{SE_M_SAND_TOMB}int{SE_M_ATTRACT2}the\n"
	.string "mountai{SE_M_ATTRACT}{SE_M_HEAL_BELL}guess...$"

Route47_Text_CamperAfter::
	.string "Se{SE_M_REVERSAL}ya!$"

Route47_EventScript_Thom::
	trainerbattle_double 1424, Route47_Text_Couple1Seen, Route47_Text_Couple1Beaten, J_Route104_Text_GinaNotEnoughMons
	special GetPlayerBigGuyGirlString
	msgbox Route47_Text_Couple1After1, MSGBOX_AUTOCLOSE
	end

Route47_EventScript_Kae::
	trainerbattle_double 1424, Route47_Text_Couple1Seen, Route47_Text_Couple1Beaten, J_Route104_Text_GinaNotEnoughMons
	special GetPlayerBigGuyGirlString
	msgbox Route47_Text_Couple1After2, MSGBOX_AUTOCLOSE
	end

Route47_Text_Couple1Seen::
	.string "THOM{SE_M_HEAT_WAVE}On{SE_M_REVERSAL}plu{SE_M_GRASSWHISTLE}on{SE_M_REVERSAL}i{SE_M_GRASSWHISTLE}two{SE_M_PERISH_SONG}Bu{SE_M_SPIT_UP}the\n"
	.string "tw{SE_M_ATTRACT2}o{SE_M_ACID_ARMOR}u{SE_M_GRASSWHISTLE}togethe{SE_M_SAND_TOMB}i{SE_M_GRASSWHISTLE}much\l"
	.string "stronger!\p"
	.string "KAE{SE_M_HEAT_WAVE}Th{SE_M_REVERSAL}tw{SE_M_ATTRACT2}o{SE_M_ACID_ARMOR}u{SE_M_GRASSWHISTLE}aren'{SE_M_SPIT_UP}jus{SE_M_SPIT_UP}some\n"
	.string "borin{SE_M_SANDSTORM}pair!$"

Route47_Text_Couple1Beaten::
	.string "THOM{SE_M_HEAT_WAVE}Tha{SE_M_SPIT_UP}wasn'{SE_M_SPIT_UP}wha{SE_M_SPIT_UP}{SE_M_HEAL_BELL}expected.\l"
	.string "KAE{SE_M_HEAT_WAVE}You'r{SE_M_REVERSAL}unusua{SE_M_BATON_PASS}too!$"

Route47_Text_Couple1After1::
	.string "THOM{SE_M_HEAT_WAVE}I{SE_M_SPIT_UP}seem{SE_M_GRASSWHISTLE}you{SE_M_SAND_TOMB}powe{SE_M_SAND_TOMB}is\n"
	.string "impossibl{SE_M_REVERSAL}t{SE_M_ATTRACT2}predict!$"

Route47_Text_Couple1After2::
	.string "KAE{SE_M_HEAT_WAVE}{SE_M_HEAL_BELL}figure{SE_M_WATERFALL}yo{SE_M_DIVE}wer{SE_M_REVERSAL}a{SE_M_ATTRACT}ordinary\n"
	.string "lon{SE_M_REVERSAL}trainer{SE_M_PERISH_SONG}Bo{SE_M_YAWN}wa{SE_M_GRASSWHISTLE}{SE_M_HEAL_BELL}wrong!$"

Route47_EventScript_Duff::
	trainerbattle_double 1425, Route47_Text_Couple2Seen, Route47_Text_Couple2Beaten, J_Route104_Text_GinaNotEnoughMons
	special GetPlayerBigGuyGirlString
	msgbox Route47_Text_Couple2After1, MSGBOX_AUTOCLOSE
	end

Route47_EventScript_Eda::
	trainerbattle_double 1425, Route47_Text_Couple2Seen, Route47_Text_Couple2Beaten, J_Route104_Text_GinaNotEnoughMons
	msgbox Route47_Text_Couple2After2, MSGBOX_AUTOCLOSE
	end

Route47_Text_Couple2Seen::
	.string "DUFF{SE_M_HEAT_WAVE}Watchin{SE_M_SANDSTORM}ove{SE_M_SAND_TOMB}m{SE_M_YAWN}girlfriend\n"
	.string "make{SE_M_GRASSWHISTLE}m{SE_M_YAWN}hear{SE_M_SPIT_UP}soar!\p"
	.string "EDA{SE_M_HEAT_WAVE}M{SE_M_YAWN}heart'{SE_M_GRASSWHISTLE}feeling{SE_M_GRASSWHISTLE}fo{SE_M_SAND_TOMB}my\n"
	.string "boyfrien{SE_M_WATERFALL}ar{SE_M_REVERSAL}a{SE_M_GRASSWHISTLE}wid{SE_M_REVERSAL}an{SE_M_WATERFALL}deep\l"
	.string "th{SE_M_REVERSAL}ocean!$"

Route47_Text_Couple2Beaten::
	.string "DUFF{SE_M_HEAT_WAVE}{SE_M_HEAL_BELL}wa{SE_M_GRASSWHISTLE}n{SE_M_ATTRACT2}matc{SE_M_TRI_ATTACK}fo{SE_M_SAND_TOMB}you...\l"
	.string "EDA{SE_M_HEAT_WAVE}Yo{SE_M_DIVE}ar{SE_M_REVERSAL}reall{SE_M_YAWN}something...$"

Route47_Text_Couple2After1::
	.string "DUFF{SE_M_HEAT_WAVE}Than{SE_M_ENCORE2}yo{SE_M_DIVE}fo{SE_M_SAND_TOMB}th{SE_M_REVERSAL}awe-\n"
	.string "inspirin{SE_M_SANDSTORM}battle{SE_M_DRAGON_RAGE}Bye!$"

Route47_Text_Couple2After2::
	.string "EDA{SE_M_HEAT_WAVE}Yo{SE_M_DIVE}shoul{SE_M_WATERFALL}reall{SE_M_YAWN}fin{SE_M_WATERFALL}a\n"
	.string "wonderfu{SE_M_BATON_PASS}partner{SE_M_SUPERSONIC}too!$"

Route47_EventScript_Sage::
	lock
	faceplayer
	msgbox EmbeddedTower_Text_OldManIntro, MSGBOX_DEFAULT
	closemessage
	release
	end

EmbeddedTower_Text_OldManIntro:
	.string "Well{SE_M_SUPERSONIC}hello!\p"
	.string "It'{SE_M_GRASSWHISTLE}sai{SE_M_WATERFALL}tha{SE_M_SPIT_UP}pas{SE_M_SPIT_UP}thi{SE_M_GRASSWHISTLE}hol{SE_M_REVERSAL}use{SE_M_WATERFALL}to\n"
	.string "b{SE_M_REVERSAL}{SE_M_CHARGE}hug{SE_M_REVERSAL}towe{SE_M_SAND_TOMB}reachin{SE_M_SANDSTORM}fa{SE_M_SAND_TOMB}into\l"
	.string "th{SE_M_REVERSAL}sky.\p"
	.string "The{SE_M_YAWN}sa{SE_M_YAWN}tha{SE_M_SPIT_UP}i{SE_M_SPIT_UP}wa{SE_M_GRASSWHISTLE}{SE_M_CHARGE}rathe{SE_M_SAND_TOMB}strange\n"
	.string "towe{SE_M_SAND_TOMB}wit{SE_M_TRI_ATTACK}hal{SE_M_ACID_ARMOR}o{SE_M_ACID_ARMOR}i{SE_M_SPIT_UP}embedded\l"
	.string "i{SE_M_ATTRACT}th{SE_M_REVERSAL}cliff.\p"
	.string "I{SE_M_SPIT_UP}wa{SE_M_GRASSWHISTLE}no{SE_M_SPIT_UP}jus{SE_M_SPIT_UP}{SE_M_CHARGE}tal{SE_M_BATON_PASS}towe{SE_M_SAND_TOMB}reaching\n"
	.string "u{SE_M_MORNING_SUN}t{SE_M_ATTRACT2}th{SE_M_REVERSAL}sky{SE_M_SUPERSONIC}bu{SE_M_SPIT_UP}als{SE_M_ATTRACT2}reachin{SE_M_SANDSTORM}deep\l"
	.string "dow{SE_M_ATTRACT}underground!\p"
	.string "I{SE_M_SPIT_UP}i{SE_M_GRASSWHISTLE}rumore{SE_M_WATERFALL}tha{SE_M_SPIT_UP}i{SE_M_SPIT_UP}eve{SE_M_ATTRACT}reached\n"
	.string "th{SE_M_REVERSAL}botto{SE_M_MILK_DRINK}o{SE_M_ACID_ARMOR}th{SE_M_REVERSAL}ocean!\p"
	.string "I{SE_M_ATTRACT}short{SE_M_SUPERSONIC}th{SE_M_REVERSAL}ruin{SE_M_GRASSWHISTLE}use{SE_M_WATERFALL}t{SE_M_ATTRACT2}connect\n"
	.string "th{SE_M_REVERSAL}sky{SE_M_SUPERSONIC}th{SE_M_REVERSAL}land{SE_M_SUPERSONIC}an{SE_M_WATERFALL}th{SE_M_REVERSAL}se{SE_M_CHARGE}to\l"
	.string "eac{SE_M_TRI_ATTACK}other...\p"
	.string "Mos{SE_M_SPIT_UP}o{SE_M_ACID_ARMOR}th{SE_M_REVERSAL}towe{SE_M_SAND_TOMB}i{SE_M_GRASSWHISTLE}no{SE_M_TWISTER}crumbled,\n"
	.string "an{SE_M_WATERFALL}th{SE_M_REVERSAL}onl{SE_M_YAWN}thing{SE_M_GRASSWHISTLE}tha{SE_M_SPIT_UP}remai{SE_M_ATTRACT}are\l"
	.string "th{SE_M_REVERSAL}entranc{SE_M_REVERSAL}an{SE_M_WATERFALL}it{SE_M_GRASSWHISTLE}interior{SE_M_SUPERSONIC}where\l"
	.string "you'l{SE_M_BATON_PASS}se{SE_M_REVERSAL}strang{SE_M_REVERSAL}patterns.$"

Route47_EventScript_Item_Pearl::
	finditem ITEM_PEARL
	end

Route47_EventScript_Item_Revive::
	finditem ITEM_REVIVE
	end

Route47_EventScript_Item_WhiteFlute::
	finditem ITEM_WHITE_FLUTE
	end

Route47_EventScript_Item_Stardust::
	finditem ITEM_STARDUST
	end

Route47_EventScript_Item_LuckyPunch::
	finditem ITEM_LUCKY_PUNCH
	end

Route47_EventScript_Chinchou::
	lock
	faceplayer
	waitse
	playmoncry 170, 0
	msgbox Route47_Text_Chinchou, MSGBOX_DEFAULT
	waitmoncry
	release
	end

Route47_Text_Chinchou:
	.string "CHINCHOU{SE_M_HEAT_WAVE}Chou!$"

