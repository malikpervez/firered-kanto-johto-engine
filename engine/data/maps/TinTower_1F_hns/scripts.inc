@ Johto (data/maps/TinTower_1F_hns/scripts.inc), as built into the FireRed game.

TinTower_1F_hns_MapScripts::
	map_script 3, TinTower_OnTransition
	.byte 0

TinTower_OnTransition::
	setescapewarp MAP_BELLCHIME_TRAIL_HNS, 35, 42
	end

TinTower_1F_EventScript_SageA::
	lock
	faceplayer
	goto_if_eq 20561, 11, TinTower_1F_EventScript_SageA_Hooh
	msgbox TinTower_1F_Sage4_Text2, MSGBOX_DEFAULT
	closemessage
	release
	end

TinTower_1F_EventScript_SageA_Hooh::
	msgbox TinTower_1F_Sage4_Text1, MSGBOX_DEFAULT
	closemessage
	release
	end

TinTower_1F_EventScript_SageB::
	lock
	faceplayer
	goto_if_eq 20561, 11, TinTower_1F_EventScript_SageB_Hooh
	msgbox TinTower_1F_Sage2_Text, MSGBOX_DEFAULT
	closemessage
	release
	end

TinTower_1F_EventScript_SageB_Hooh::
	msgbox TinTower_1F_Sage1_Text, MSGBOX_DEFAULT
	closemessage
	release
	end

TinTower_1F_EventScript_SageC::
	lock
	faceplayer
	goto_if_eq 20561, 11, TinTower_1F_EventScript_SageC_Hooh
	msgbox TinTower_1F_Sage6_Text2, MSGBOX_DEFAULT
	closemessage
	release
	end

TinTower_1F_EventScript_SageC_Hooh::
	msgbox TinTower_1F_Sage3_Text, MSGBOX_DEFAULT
	closemessage
	release
	end

TinTower_1F_Sage1_Text:
	.string "Accordin{SE_M_SANDSTORM}t{SE_M_ATTRACT2}legend…\n"
	.string "Whe{SE_M_ATTRACT}th{SE_M_REVERSAL}soul{SE_M_GRASSWHISTLE}o{SE_M_ACID_ARMOR}POKéMO{SE_M_PSYBEAM2}an{SE_M_WATERFALL}humans\p"
	.string "commune{SE_M_SUPERSONIC}fro{SE_M_MILK_DRINK}th{SE_M_REVERSAL}heaven{SE_M_GRASSWHISTLE}descend{SE_M_GRASSWHISTLE}a\n"
	.string "POKéMO{SE_M_PSYBEAM2}o{SE_M_ACID_ARMOR}rainbo{SE_M_TWISTER}colors…\p"
	.string "Coul{SE_M_WATERFALL}i{SE_M_SPIT_UP}mea{SE_M_ATTRACT}th{SE_M_REVERSAL}legendar{SE_M_YAWN}POKéMON\n"
	.string "ar{SE_M_REVERSAL}testin{SE_M_SANDSTORM}u{SE_M_GRASSWHISTLE}humans?$"

TinTower_1F_Sage2_Text:
	.string "Whe{SE_M_ATTRACT}th{SE_M_REVERSAL}BRAS{SE_M_SKETCH}TOWE{SE_M_MINIMIZE}burne{SE_M_WATERFALL}down,\n"
	.string "thre{SE_M_REVERSAL}nameles{SE_M_GRASSWHISTLE}POKéMO{SE_M_PSYBEAM2}wer{SE_M_REVERSAL}said\l"
	.string "t{SE_M_ATTRACT2}hav{SE_M_REVERSAL}perished{SE_M_PERISH_SONG}I{SE_M_SPIT_UP}wa{SE_M_GRASSWHISTLE}tragic.\p"
	.string "However…\p"
	.string "{SE_M_BONEMERANG}rainbow-colore{SE_M_WATERFALL}POKéMON…\n"
	.string "I{SE_M_ATTRACT}othe{SE_M_SAND_TOMB}words…\p"
	.string "HO-O{SE_M_SWAGGER2}descende{SE_M_WATERFALL}fro{SE_M_MILK_DRINK}th{SE_M_REVERSAL}sk{SE_M_YAWN}and\n"
	.string "gav{SE_M_REVERSAL}ne{SE_M_TWISTER}lif{SE_M_REVERSAL}t{SE_M_ATTRACT2}th{SE_M_REVERSAL}thre{SE_M_REVERSAL}POKéMON.\p"
	.string "The{SE_M_YAWN}are…\n"
	.string "SUICUNE{SE_M_SUPERSONIC}ENTE{SE_M_HEAL_BELL}an{SE_M_WATERFALL}RAIKOU.\p"
	.string "Tha{SE_M_SPIT_UP}i{SE_M_GRASSWHISTLE}wha{SE_M_SPIT_UP}the{SE_M_YAWN}say.$"

TinTower_1F_Sage3_Text:
	.string "Th{SE_M_REVERSAL}tw{SE_M_ATTRACT2}TOWER{SE_M_SKETCH}ar{SE_M_REVERSAL}sai{SE_M_WATERFALL}t{SE_M_ATTRACT2}hav{SE_M_REVERSAL}been\n"
	.string "buil{SE_M_SPIT_UP}t{SE_M_ATTRACT2}foste{SE_M_SAND_TOMB}friendshi{SE_M_MORNING_SUN}and\p"
	.string "hop{SE_M_REVERSAL}betwee{SE_M_ATTRACT}POKéMO{SE_M_PSYBEAM2}an{SE_M_WATERFALL}people.\n"
	.string "Tha{SE_M_SPIT_UP}wa{SE_M_GRASSWHISTLE}70{SE_M_BITE}year{SE_M_GRASSWHISTLE}ago{SE_M_SUPERSONIC}bu{SE_M_SPIT_UP}th{SE_M_REVERSAL}ideal\p"
	.string "stil{SE_M_BATON_PASS}remain{SE_M_GRASSWHISTLE}importan{SE_M_SPIT_UP}today.$"

TinTower_1F_Sage4_Text1:
	.string "HO-O{SE_M_SWAGGER2}appear{SE_M_GRASSWHISTLE}t{SE_M_ATTRACT2}hav{SE_M_REVERSAL}descended\n"
	.string "upo{SE_M_ATTRACT}this{SE_M_SUPERSONIC}th{SE_M_REVERSAL}TI{SE_M_PSYBEAM2}TOWER!$"

TinTower_1F_Sage4_Text2:
	.string "Th{SE_M_REVERSAL}legendar{SE_M_YAWN}POKéMO{SE_M_PSYBEAM2}ar{SE_M_REVERSAL}said\n"
	.string "t{SE_M_ATTRACT2}embod{SE_M_YAWN}thre{SE_M_REVERSAL}powers…\p"
	.string "Th{SE_M_REVERSAL}lightnin{SE_M_SANDSTORM}tha{SE_M_SPIT_UP}struc{SE_M_ENCORE2}th{SE_M_REVERSAL}TOWER.\n"
	.string "Th{SE_M_REVERSAL}fir{SE_M_REVERSAL}tha{SE_M_SPIT_UP}burne{SE_M_WATERFALL}th{SE_M_REVERSAL}TOWER.\p"
	.string "An{SE_M_WATERFALL}th{SE_M_REVERSAL}rai{SE_M_ATTRACT}tha{SE_M_SPIT_UP}pu{SE_M_SPIT_UP}ou{SE_M_SPIT_UP}th{SE_M_REVERSAL}fire…$"

TinTower_1F_Sage6_Text2:
	.string "O{SE_M_ACID_ARMOR}th{SE_M_REVERSAL}legendar{SE_M_YAWN}POKéMON{SE_M_SUPERSONIC}SUICUNE\n"
	.string "i{SE_M_GRASSWHISTLE}sai{SE_M_WATERFALL}t{SE_M_ATTRACT2}b{SE_M_REVERSAL}th{SE_M_REVERSAL}closes{SE_M_SPIT_UP}t{SE_M_ATTRACT2}HO-OH.\p"
	.string "{SE_M_HEAL_BELL}hea{SE_M_SAND_TOMB}ther{SE_M_REVERSAL}ma{SE_M_YAWN}als{SE_M_ATTRACT2}b{SE_M_REVERSAL}{SE_M_CHARGE}lin{SE_M_ENCORE2}to\n"
	.string "POKéMO{SE_M_PSYBEAM2}know{SE_M_ATTRACT}a{SE_M_GRASSWHISTLE}UNOWN.\p"
	.string "Th{SE_M_REVERSAL}POKéMO{SE_M_PSYBEAM2}UNOW{SE_M_PSYBEAM2}mus{SE_M_SPIT_UP}b{SE_M_REVERSAL}sharin{SE_M_SANDSTORM}a\n"
	.string "cooperativ{SE_M_REVERSAL}bon{SE_M_WATERFALL}wit{SE_M_TRI_ATTACK}SUICUNE.$"

TinTower_1F_EusineHoOh_Text:
	.string "{SE_M_HEAL_BELL}kne{SE_M_TWISTER}it.\p"
	.string "{SE_M_HEAL_BELL}kne{SE_M_TWISTER}you'{SE_M_WATERFALL}ge{SE_M_SPIT_UP}t{SE_M_ATTRACT2}se{SE_M_REVERSAL}th{SE_M_REVERSAL}POKéMON\n"
	.string "o{SE_M_ACID_ARMOR}rainbo{SE_M_TWISTER}colors{SE_M_SUPERSONIC}<PLAYER>.\p"
	.string "I{SE_M_SPIT_UP}happene{SE_M_WATERFALL}jus{SE_M_SPIT_UP}a{SE_M_GRASSWHISTLE}{SE_M_HEAL_BELL}envisioned.\n"
	.string "M{SE_M_YAWN}researc{SE_M_TRI_ATTACK}isn'{SE_M_SPIT_UP}bad{SE_M_SUPERSONIC}{SE_M_HEAL_BELL}migh{SE_M_SPIT_UP}say.\p"
	.string "I'{SE_M_MILK_DRINK}goin{SE_M_SANDSTORM}t{SE_M_ATTRACT2}kee{SE_M_MORNING_SUN}studyin{SE_M_SANDSTORM}POKéMON\n"
	.string "t{SE_M_ATTRACT2}becom{SE_M_REVERSAL}{SE_M_CHARGE}famou{SE_M_GRASSWHISTLE}POKéMANIAC!$"

TinTower_1F_EusineSuicune_Text:
	.string "EUSINE{SE_M_HEAT_WAVE}Awesome{SE_M_DRAGON_RAGE}To{SE_M_ATTRACT2}awesome{SE_M_SUPERSONIC}even!\n"
	.string "I'v{SE_M_REVERSAL}neve{SE_M_SAND_TOMB}see{SE_M_ATTRACT}{SE_M_CHARGE}battl{SE_M_REVERSAL}tha{SE_M_SPIT_UP}great.\p"
	.string "Tha{SE_M_SPIT_UP}wa{SE_M_GRASSWHISTLE}trul{SE_M_YAWN}inspirin{SE_M_SANDSTORM}t{SE_M_ATTRACT2}see.\n"
	.string "SUICUN{SE_M_SWORDS_DANCE}wa{SE_M_GRASSWHISTLE}tough{SE_M_SUPERSONIC}bu{SE_M_SPIT_UP}yo{SE_M_DIVE}wer{SE_M_REVERSAL}even\p"
	.string "mor{SE_M_REVERSAL}incredible{SE_M_SUPERSONIC}<PLAYER>.\n"
	.string "{SE_M_HEAL_BELL}hear{SE_M_WATERFALL}SUICUNE'{SE_M_GRASSWHISTLE}mysti{SE_M_HYPER_BEAM}power\p"
	.string "summon{SE_M_GRASSWHISTLE}{SE_M_CHARGE}rainbow-colore{SE_M_WATERFALL}POKéMON.\n"
	.string "Maybe{SE_M_SUPERSONIC}jus{SE_M_SPIT_UP}maybe{SE_M_SUPERSONIC}wha{SE_M_SPIT_UP}wen{SE_M_SPIT_UP}o{SE_M_ATTRACT}today\p"
	.string "wil{SE_M_BATON_PASS}caus{SE_M_REVERSAL}tha{SE_M_SPIT_UP}POKéMO{SE_M_PSYBEAM2}t{SE_M_ATTRACT2}appear.\n"
	.string "I'{SE_M_MILK_DRINK}goin{SE_M_SANDSTORM}t{SE_M_ATTRACT2}stud{SE_M_YAWN}th{SE_M_REVERSAL}legend{SE_M_GRASSWHISTLE}more.\p"
	.string "Thank{SE_M_GRASSWHISTLE}fo{SE_M_SAND_TOMB}showin{SE_M_SANDSTORM}m{SE_M_REVERSAL}tha{SE_M_SPIT_UP}fantastic\n"
	.string "battle.\p"
	.string "Later{SE_M_SUPERSONIC}<PLAYER>!$"

