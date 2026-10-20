@ Johto (data/maps/Route41_hns/scripts.inc), as built into the FireRed game.

Route41_hns_MapScripts::
	map_script 3, Route41_MapScript_OnTransition
	.byte 0

Route41_MapScript_OnTransition::
	goto_if_eq 20559, 4, Route41_MapScript_DoNothing
	goto_if_ge 20583, 5, OlivineCity_MapScript_ClearWeather
	end

Route41_MapScript_DoNothing::
	end

Route41_EventScript_Charlie::
	trainerbattle_single 1219, Route41_Text_SwimmermCharlieSeen, Route41_Text_SwimmermCharlieBeaten
	msgbox Route41_Text_SwimmermCharlieAfter, MSGBOX_AUTOCLOSE
	end

Route41_Text_SwimmermCharlieSeen:
	.string "Th{SE_M_REVERSAL}water'{SE_M_GRASSWHISTLE}war{SE_M_MILK_DRINK}here.\n"
	.string "I'{SE_M_MILK_DRINK}loos{SE_M_REVERSAL}an{SE_M_WATERFALL}limber.\p"
	.string "Sure{SE_M_SUPERSONIC}I'l{SE_M_BATON_PASS}tak{SE_M_REVERSAL}yo{SE_M_DIVE}on!$"

Route41_Text_SwimmermCharlieBeaten:
	.string "Yikes{SE_M_DRAGON_RAGE}I'v{SE_M_REVERSAL}go{SE_M_SPIT_UP}prun{SE_M_REVERSAL}skin!$"

Route41_Text_SwimmermCharlieAfter:
	.string "Isn'{SE_M_SPIT_UP}i{SE_M_SPIT_UP}relaxin{SE_M_SANDSTORM}jus{SE_M_SPIT_UP}floating\n"
	.string "lik{SE_M_REVERSAL}this?$"

Route41_EventScript_George::
	trainerbattle_single 1220, Route41_Text_SwimmermGeorgeSeen, Route41_Text_SwimmermGeorgeBeaten
	msgbox Route41_Text_SwimmermGeorgeAfter, MSGBOX_AUTOCLOSE
	end

Route41_Text_SwimmermGeorgeSeen:
	.string "I'{SE_M_MILK_DRINK}{SE_M_CHARGE}bi{SE_M_SPIT_UP}tired.\n"
	.string "I{SE_M_ACID_ARMOR}{SE_M_HEAL_BELL}win{SE_M_SUPERSONIC}len{SE_M_WATERFALL}m{SE_M_REVERSAL}you{SE_M_SAND_TOMB}POKéMON.$"

Route41_Text_SwimmermGeorgeBeaten:
	.string "Pant{SE_M_SUPERSONIC}pant…$"

Route41_Text_SwimmermGeorgeAfter:
	.string "It'{SE_M_GRASSWHISTLE}s{SE_M_ATTRACT2}fa{SE_M_SAND_TOMB}t{SE_M_ATTRACT2}CIANWOOD.\p"
	.string "Bu{SE_M_SPIT_UP}it'{SE_M_GRASSWHISTLE}n{SE_M_ATTRACT2}eas{SE_M_YAWN}retur{SE_M_ATTRACT}trip\n"
	.string "t{SE_M_ATTRACT2}OLIVIN{SE_M_SWORDS_DANCE}either.\p"
	.string "Wha{SE_M_SPIT_UP}shoul{SE_M_WATERFALL}{SE_M_HEAL_BELL}do?$"

Route41_EventScript_Berke::
	trainerbattle_single 1221, Route41_Text_SwimmermBerkeSeen, Route41_Text_SwimmermBerkeBeaten
	msgbox Route41_Text_SwimmermBerkeAfter, MSGBOX_AUTOCLOSE
	end

Route41_Text_SwimmermBerkeSeen:
	.string "Se{SE_M_REVERSAL}thos{SE_M_REVERSAL}island{SE_M_GRASSWHISTLE}tha{SE_M_SPIT_UP}are\n"
	.string "blocke{SE_M_WATERFALL}b{SE_M_YAWN}whirlpools?\p"
	.string "Ther{SE_M_REVERSAL}jus{SE_M_SPIT_UP}ha{SE_M_GRASSWHISTLE}t{SE_M_ATTRACT2}b{SE_M_REVERSAL}{SE_M_CHARGE}secret!$"

Route41_Text_SwimmermBerkeBeaten:
	.string "What'{SE_M_GRASSWHISTLE}th{SE_M_REVERSAL}secre{SE_M_SPIT_UP}t{SE_M_ATTRACT2}your\n"
	.string "strength?$"

Route41_Text_SwimmermBerkeAfter:
	.string "I{SE_M_SPIT_UP}wa{SE_M_GRASSWHISTLE}{SE_M_CHARGE}dar{SE_M_ENCORE2}an{SE_M_WATERFALL}storm{SE_M_YAWN}night…\p"
	.string "{SE_M_HEAL_BELL}sa{SE_M_TWISTER}thi{SE_M_GRASSWHISTLE}gian{SE_M_SPIT_UP}POKéMO{SE_M_PSYBEAM2}flying\n"
	.string "fro{SE_M_MILK_DRINK}th{SE_M_REVERSAL}islands.\p"
	.string "I{SE_M_SPIT_UP}wa{SE_M_GRASSWHISTLE}scatterin{SE_M_SANDSTORM}feathers\n"
	.string "fro{SE_M_MILK_DRINK}it{SE_M_GRASSWHISTLE}silve{SE_M_SAND_TOMB}wings.$"

Route41_EventScript_Kirk::
	trainerbattle_single 1222, Route41_Text_SwimmermKirkSeen, Route41_Text_SwimmermKirkBeaten
	msgbox Route41_Text_SwimmermKirkAfter, MSGBOX_AUTOCLOSE
	end

Route41_Text_SwimmermKirkSeen:
	.string "Th{SE_M_REVERSAL}wave{SE_M_GRASSWHISTLE}ar{SE_M_REVERSAL}wil{SE_M_WATERFALL}here.\p"
	.string "The{SE_M_YAWN}tir{SE_M_REVERSAL}yo{SE_M_DIVE}ou{SE_M_SPIT_UP}while\n"
	.string "yo{SE_M_DIVE}swim.$"

Route41_Text_SwimmermKirkBeaten:
	.string "I'{SE_M_MILK_DRINK}beat!$"

Route41_Text_SwimmermKirkAfter:
	.string "Th{SE_M_REVERSAL}current{SE_M_GRASSWHISTLE}kee{SE_M_MORNING_SUN}m{SE_M_REVERSAL}from\n"
	.string "reachin{SE_M_SANDSTORM}tha{SE_M_SPIT_UP}island.$"

Route41_EventScript_Mathew::
	trainerbattle_single 1223, Route41_Text_SwimmermMathewSeen, Route41_Text_SwimmermMathewBeaten
	msgbox Route41_Text_SwimmermMathewAfter, MSGBOX_AUTOCLOSE
	end

Route41_Text_SwimmermMathewSeen:
	.string "Ar{SE_M_REVERSAL}yo{SE_M_DIVE}seekin{SE_M_SANDSTORM}th{SE_M_REVERSAL}secrets\n"
	.string "o{SE_M_ACID_ARMOR}WHIR{SE_M_BRICK_BREAK}ISLANDS?$"

Route41_Text_SwimmermMathewBeaten:
	.string "Ooh{SE_M_SUPERSONIC}you'v{SE_M_REVERSAL}go{SE_M_SPIT_UP}grea{SE_M_SPIT_UP}endurance!$"

Route41_Text_SwimmermMathewAfter:
	.string "{SE_M_BONEMERANG}secre{SE_M_SPIT_UP}abou{SE_M_SPIT_UP}WHIR{SE_M_BRICK_BREAK}ISLANDS…\p"
	.string "It'{SE_M_GRASSWHISTLE}pitch-blac{SE_M_ENCORE2}inside!$"

Route41_EventScript_Kaylee::
	trainerbattle_single 1239, Route41_Text_SwimmerfKayleeSeen, Route41_Text_SwimmerfKayleeBeaten
	msgbox Route41_Text_SwimmerfKayleeAfter, MSGBOX_AUTOCLOSE
	end

Route41_Text_SwimmerfKayleeSeen:
	.string "I'{SE_M_MILK_DRINK}o{SE_M_ATTRACT}m{SE_M_YAWN}wa{SE_M_YAWN}t{SE_M_ATTRACT2}WHIR{SE_M_BRICK_BREAK}ISLANDS.\p"
	.string "I'{SE_M_MILK_DRINK}goin{SE_M_SANDSTORM}explorin{SE_M_SANDSTORM}wit{SE_M_TRI_ATTACK}friends.$"

Route41_Text_SwimmerfKayleeBeaten:
	.string "I{SE_M_GRASSWHISTLE}tha{SE_M_SPIT_UP}ho{SE_M_TWISTER}yo{SE_M_DIVE}d{SE_M_ATTRACT2}it?$"

Route41_Text_SwimmerfKayleeAfter:
	.string "There'{SE_M_GRASSWHISTLE}suppose{SE_M_WATERFALL}t{SE_M_ATTRACT2}b{SE_M_REVERSAL}{SE_M_CHARGE}big\n"
	.string "POKéMO{SE_M_PSYBEAM2}dee{SE_M_MORNING_SUN}beneat{SE_M_TRI_ATTACK}WHIR{SE_M_BRICK_BREAK}ISLANDS.\p"
	.string "{SE_M_HEAL_BELL}wonde{SE_M_SAND_TOMB}wha{SE_M_SPIT_UP}i{SE_M_SPIT_UP}coul{SE_M_WATERFALL}be?$"

Route41_EventScript_Susie::
	trainerbattle_single 1240, Route41_Text_SwimmerfSusieSeen, Route41_Text_SwimmerfSusieBeaten
	msgbox Route41_Text_SwimmerfSusieAfter, MSGBOX_AUTOCLOSE
	end

Route41_Text_SwimmerfSusieSeen:
	.string "Yo{SE_M_DIVE}loo{SE_M_ENCORE2}s{SE_M_ATTRACT2}elegant,\n"
	.string "ridin{SE_M_SANDSTORM}you{SE_M_SAND_TOMB}POKéMON.$"

Route41_Text_SwimmerfSusieBeaten:
	.string "I'{SE_M_MILK_DRINK}crushed…$"

Route41_Text_SwimmerfSusieAfter:
	.string "Wasn'{SE_M_SPIT_UP}ther{SE_M_REVERSAL}{SE_M_CHARGE}hi{SE_M_SPIT_UP}son{SE_M_SANDSTORM}about\n"
	.string "{SE_M_CHARGE}bo{SE_M_YAWN}ridin{SE_M_SANDSTORM}{SE_M_CHARGE}LAPRAS?$"

Route41_EventScript_Denise::
	trainerbattle_single 1241, Route41_Text_SwimmerfDeniseSeen, Route41_Text_SwimmerfDeniseBeaten
	msgbox Route41_Text_SwimmerfDeniseAfter, MSGBOX_AUTOCLOSE
	end

Route41_Text_SwimmerfDeniseSeen:
	.string "Th{SE_M_REVERSAL}weathe{SE_M_SAND_TOMB}i{SE_M_GRASSWHISTLE}s{SE_M_ATTRACT2}beautiful,\n"
	.string "I'{SE_M_MILK_DRINK}i{SE_M_ATTRACT}{SE_M_CHARGE}daze!$"

Route41_Text_SwimmerfDeniseBeaten:
	.string "Ohhh!$"

Route41_Text_SwimmerfDeniseAfter:
	.string "{SE_M_BONEMERANG}sunbur{SE_M_ATTRACT}i{SE_M_GRASSWHISTLE}th{SE_M_REVERSAL}wors{SE_M_SPIT_UP}fo{SE_M_SAND_TOMB}skin.\p"
	.string "Bu{SE_M_SPIT_UP}{SE_M_HEAL_BELL}don'{SE_M_SPIT_UP}us{SE_M_REVERSAL}{SE_M_CHARGE}sunblock.\p"
	.string "{SE_M_HEAL_BELL}won'{SE_M_SPIT_UP}pollut{SE_M_REVERSAL}th{SE_M_REVERSAL}water.$"

Route41_EventScript_Kara::
	trainerbattle_single 1242, Route41_Text_SwimmerfKaraSeen, Route41_Text_SwimmerfKaraBeaten
	msgbox Route41_Text_SwimmerfKaraAfter, MSGBOX_AUTOCLOSE
	end

Route41_Text_SwimmerfKaraSeen:
	.string "I{SE_M_ACID_ARMOR}yo{SE_M_DIVE}nee{SE_M_WATERFALL}t{SE_M_ATTRACT2}rest,\n"
	.string "jus{SE_M_SPIT_UP}trea{SE_M_WATERFALL}water.\p"
	.string "You'l{SE_M_BATON_PASS}ge{SE_M_SPIT_UP}you{SE_M_SAND_TOMB}win{SE_M_WATERFALL}back,\n"
	.string "s{SE_M_ATTRACT2}yo{SE_M_DIVE}ca{SE_M_ATTRACT}kee{SE_M_MORNING_SUN}o{SE_M_ATTRACT}goin{SE_M_SANDSTORM}strong.$"

Route41_Text_SwimmerfKaraBeaten:
	.string "Oh{SE_M_DRAGON_RAGE}Yo{SE_M_DIVE}hav{SE_M_REVERSAL}mor{SE_M_REVERSAL}energ{SE_M_YAWN}tha{SE_M_ATTRACT}{SE_M_HEAL_BELL}do.$"

Route41_Text_SwimmerfKaraAfter:
	.string "{SE_M_HEAL_BELL}hear{SE_M_WATERFALL}roar{SE_M_GRASSWHISTLE}fro{SE_M_MILK_DRINK}dee{SE_M_MORNING_SUN}inside\n"
	.string "th{SE_M_REVERSAL}ISLANDS.$"

Route41_EventScript_Wendy::
	trainerbattle_single 1243, Route41_Text_SwimmerfWendySeen, Route41_Text_SwimmerfWendyBeaten
	msgbox Route41_Text_SwimmerfWendyAfter, MSGBOX_AUTOCLOSE
	end

Route41_Text_SwimmerfWendySeen:
	.string "A{SE_M_SPIT_UP}night{SE_M_SUPERSONIC}STARY{SE_M_REFLECT}gathe{SE_M_SAND_TOMB}near\n"
	.string "th{SE_M_REVERSAL}water'{SE_M_GRASSWHISTLE}surface.$"

Route41_Text_SwimmerfWendyBeaten:
	.string "Oh{SE_M_SUPERSONIC}dear…$"

Route41_Text_SwimmerfWendyAfter:
	.string "Th{SE_M_REVERSAL}cluster{SE_M_GRASSWHISTLE}o{SE_M_ACID_ARMOR}STARY{SE_M_REFLECT}ligh{SE_M_SPIT_UP}up\n"
	.string "a{SE_M_SPIT_UP}th{SE_M_REVERSAL}sam{SE_M_REVERSAL}time.\p"
	.string "It'{SE_M_GRASSWHISTLE}s{SE_M_ATTRACT2}beautiful{SE_M_SUPERSONIC}it'{SE_M_GRASSWHISTLE}scary.$"

Route41_EventScript_Tentacruel1::
	lock
	faceplayer
	waitse
	playmoncry 73, 0
	goto_if_ge 16384, 2, Route41_EventScript_TentacruelAttack1
	msgbox Route41_Text_Tentacruel, MSGBOX_DEFAULT
	waitmoncry
	addvar 16384, 1
	release
	end

Route41_EventScript_TentacruelAttack1::
	msgbox Route41_Text_TentacruelAttack, MSGBOX_DEFAULT
	waitmessage
	setflag 2411
	setflag 8804
	setwildbattle 73, 100, ITEM_NONE
	dowildbattle
	closemessage
	clearflag 2411
	clearflag 8804
	playse 1
	msgbox Route41_Text_TentacruelHeal, MSGBOX_DEFAULT
	setvar 16384, 0
	closemessage
	release
	end

Route41_EventScript_Tentacruel2::
	lock
	faceplayer
	waitse
	playmoncry 73, 0
	goto_if_ge 16385, 2, Route41_EventScript_TentacruelAttack2
	msgbox Route41_Text_Tentacruel, MSGBOX_DEFAULT
	waitmoncry
	addvar 16385, 1
	release
	end

Route41_EventScript_TentacruelAttack2::
	msgbox Route41_Text_TentacruelAttack, MSGBOX_DEFAULT
	waitmessage
	setwildbattle 73, 100, ITEM_NONE
	dowildbattle
	closemessage
	playse 1
	msgbox Route41_Text_TentacruelHeal, MSGBOX_DEFAULT
	setvar 16385, 0
	closemessage
	release
	end

Route41_EventScript_Tentacruel3::
	lock
	faceplayer
	waitse
	playmoncry 73, 0
	goto_if_ge 16386, 2, Route41_EventScript_TentacruelAttack3
	msgbox Route41_Text_Tentacruel, MSGBOX_DEFAULT
	waitmoncry
	addvar 16386, 1
	release
	end

Route41_EventScript_TentacruelAttack3::
	msgbox Route41_Text_TentacruelAttack, MSGBOX_DEFAULT
	waitmessage
	setwildbattle 73, 100, ITEM_NONE
	dowildbattle
	closemessage
	playse 1
	msgbox Route41_Text_TentacruelHeal, MSGBOX_DEFAULT
	setvar 16386, 0
	closemessage
	release
	end

Route41_EventScript_Tentacruel4::
	lock
	faceplayer
	waitse
	playmoncry 73, 0
	goto_if_ge 16387, 2, Route41_EventScript_TentacruelAttack4
	msgbox Route41_Text_Tentacruel, MSGBOX_DEFAULT
	waitmoncry
	addvar 16387, 1
	release
	end

Route41_EventScript_TentacruelAttack4::
	msgbox Route41_Text_TentacruelAttack, MSGBOX_DEFAULT
	waitmessage
	setwildbattle 73, 100, ITEM_NONE
	dowildbattle
	closemessage
	playse 1
	msgbox Route41_Text_TentacruelHeal, MSGBOX_DEFAULT
	setvar 16387, 0
	closemessage
	release
	end

Route41_Text_Tentacruel:
	.string "TENTACRUEL{SE_M_HEAT_WAVE}Cruooo...$"

Route41_Text_TentacruelAttack:
	.string "TENTACRUEL{SE_M_HEAT_WAVE}CRUOOOOOO!$"

Route41_Text_TentacruelHeal:
	.string "Th{SE_M_REVERSAL}TENTACRUE{SE_M_BRICK_BREAK}use{SE_M_WATERFALL}RECOVER!\n"
	.string "I{SE_M_SPIT_UP}i{SE_M_GRASSWHISTLE}full{SE_M_YAWN}healed!$"

