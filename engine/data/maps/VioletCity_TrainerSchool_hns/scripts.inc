@ Johto (data/maps/VioletCity_TrainerSchool_hns/scripts.inc), as built into the FireRed game.

VioletCity_TrainerSchool_hns_MapScripts::
	.byte 0

VioletCity_TrainerSchool_EventScript_Earl::
	lock
	faceplayer
	msgbox VioletCity_TrainerSchool_Text_EarlIntro, MSGBOX_DEFAULT
	closemessage
	release
	end

VioletCity_TrainerSchool_EventScript_Teacher::
	lock
	faceplayer
	msgbox VioletCity_TrainerSchool_Text_Teacher, MSGBOX_DEFAULT
	closemessage
	release
	end

VioletCity_TrainerSchool_EventScript_Boy1::
	lock
	faceplayer
	msgbox VioletCity_TrainerSchool_Text_GameboyKid1, MSGBOX_DEFAULT
	closemessage
	release
	end

VioletCity_TrainerSchool_EventScript_Boy2::
	lock
	faceplayer
	msgbox VioletCity_TrainerSchool_Text_GameboyKid2, MSGBOX_DEFAULT
	closemessage
	release
	end

VioletCity_TrainerSchool_EventScript_Kid::
	lock
	faceplayer
	msgbox VioletCity_TrainerSchool_Text_Youngster1, MSGBOX_DEFAULT
	closemessage
	release
	end

VioletCity_TrainerSchool_EventScript_Girl::
	lock
	faceplayer
	msgbox VioletCity_TrainerSchool_Text_Youngster2, MSGBOX_DEFAULT
	closemessage
	release
	end

VioletCity_TrainerSchool_EventScript_Twin::
	msgbox VioletCity_TrainerSchool_Text_Twin, MSGBOX_NPC
	end

VioletCity_TrainerSchool_EventScript_BlackBoard::
	lock
	msgbox VioletCity_TrainerSchool_Text_Blackboard, MSGBOX_DEFAULT
	closemessage
	release
	end

VioletCity_TrainerSchool_Text_Twin:
	.string "I'{SE_M_MILK_DRINK}no{SE_M_SPIT_UP}{SE_M_CHARGE}GB{SE_M_BONEMERANG}kid{SE_M_SUPERSONIC}bu{SE_M_SPIT_UP}{SE_M_HEAL_BELL}love\n"
	.string "playin{SE_M_SANDSTORM}POKéMO{SE_M_PSYBEAM2}games!\p"
	.string "I{SE_M_ATTRACT}th{SE_M_REVERSAL}ol{SE_M_WATERFALL}games{SE_M_SUPERSONIC}yo{SE_M_DIVE}ha{SE_M_WATERFALL}t{SE_M_ATTRACT2}battle\n"
	.string "{SE_M_CHARGE}lo{SE_M_SPIT_UP}o{SE_M_ACID_ARMOR}wil{SE_M_WATERFALL}POKéMO{SE_M_PSYBEAM2}t{SE_M_ATTRACT2}ge{SE_M_SPIT_UP}enough\l"
	.string "EXP.\p"
	.string "Bu{SE_M_SPIT_UP}i{SE_M_ATTRACT}newe{SE_M_SAND_TOMB}games{SE_M_SUPERSONIC}th{SE_M_REVERSAL}EXP{SE_M_PERISH_SONG}SHARE\n"
	.string "make{SE_M_GRASSWHISTLE}you{SE_M_SAND_TOMB}POKéMO{SE_M_PSYBEAM2}leve{SE_M_BATON_PASS}u{SE_M_MORNING_SUN}to{SE_M_ATTRACT2}fast.\p"
	.string "I{SE_M_ATTRACT}thi{SE_M_GRASSWHISTLE}game{SE_M_SUPERSONIC}th{SE_M_REVERSAL}EXP{SE_M_PERISH_SONG}SHAR{SE_M_SWORDS_DANCE}is\n"
	.string "balance{SE_M_WATERFALL}t{SE_M_ATTRACT2}pu{SE_M_SPIT_UP}you{SE_M_SAND_TOMB}POKéMO{SE_M_PSYBEAM2}a{SE_M_SPIT_UP}just\l"
	.string "th{SE_M_REVERSAL}righ{SE_M_SPIT_UP}level{SE_M_PERISH_SONG}O{SE_M_SAND_TOMB}slightl{SE_M_YAWN}higher,\l"
	.string "dependin{SE_M_SANDSTORM}o{SE_M_ATTRACT}ho{SE_M_TWISTER}man{SE_M_YAWN}battle{SE_M_GRASSWHISTLE}yo{SE_M_DIVE}do.\p"
	.string "I{SE_M_ACID_ARMOR}yo{SE_M_DIVE}wan{SE_M_SPIT_UP}{SE_M_CHARGE}traditiona{SE_M_BATON_PASS}GE{SE_M_PSYBEAM2}1-4\n"
	.string "experience{SE_M_SUPERSONIC}tur{SE_M_ATTRACT}EXP{SE_M_PERISH_SONG}SHAR{SE_M_SWORDS_DANCE}off.\l"
	.string "I{SE_M_ACID_ARMOR}yo{SE_M_DIVE}wan{SE_M_SPIT_UP}{SE_M_CHARGE}moder{SE_M_ATTRACT}experience,\l"
	.string "tur{SE_M_ATTRACT}EXP{SE_M_PERISH_SONG}SHAR{SE_M_SWORDS_DANCE}ON.\p"
	.string "Yo{SE_M_DIVE}choos{SE_M_REVERSAL}ho{SE_M_TWISTER}yo{SE_M_DIVE}wan{SE_M_SPIT_UP}t{SE_M_ATTRACT2}play!$"

VioletCity_TrainerSchool_Text_EarlIntro:
	.string "EARL{SE_M_SUPERSONIC}{SE_M_HEAL_BELL}am!\p"
	.string "Wonderfu{SE_M_BATON_PASS}ar{SE_M_REVERSAL}POKéMON{SE_M_SUPERSONIC}yes!\p"
	.string "Teac{SE_M_TRI_ATTACK}yo{SE_M_DIVE}{SE_M_HEAL_BELL}wil{SE_M_BATON_PASS}t{SE_M_ATTRACT2}b{SE_M_REVERSAL}{SE_M_CHARGE}better\n"
	.string "trainer!$"

VioletCity_TrainerSchool_Text_Teacher:
	.string "Certai{SE_M_ATTRACT}POKéMO{SE_M_PSYBEAM2}star{SE_M_SPIT_UP}of{SE_M_ACID_ARMOR}wea{SE_M_ENCORE2}and\n"
	.string "requir{SE_M_REVERSAL}muc{SE_M_TRI_ATTACK}mor{SE_M_REVERSAL}EX{SE_M_PETAL_DANCE}t{SE_M_ATTRACT2}become\l"
	.string "stron{SE_M_SANDSTORM}tha{SE_M_ATTRACT}other{SE_M_GRASSWHISTLE}do.\p"
	.string "Fo{SE_M_SAND_TOMB}example{SE_M_SUPERSONIC}LARVITA{SE_M_MINIMIZE}i{SE_M_GRASSWHISTLE}quit{SE_M_REVERSAL}weak\n"
	.string "bu{SE_M_SPIT_UP}wil{SE_M_BATON_PASS}eventuall{SE_M_YAWN}becom{SE_M_REVERSAL}a\l"
	.string "might{SE_M_YAWN}TYRANITAR{SE_M_SUPERSONIC}a{SE_M_SPIT_UP}th{SE_M_REVERSAL}cos{SE_M_SPIT_UP}of\l"
	.string "muc{SE_M_TRI_ATTACK}EXP.\p"
	.string "Onl{SE_M_YAWN}th{SE_M_REVERSAL}mos{SE_M_SPIT_UP}dedicate{SE_M_WATERFALL}trainers\n"
	.string "shoul{SE_M_WATERFALL}attemp{SE_M_SPIT_UP}t{SE_M_ATTRACT2}trai{SE_M_ATTRACT}suc{SE_M_TRI_ATTACK}a\l"
	.string "POKéMON.$"

VioletCity_TrainerSchool_Text_TeachHowToWin:
	.string "Good{SE_M_DRAGON_RAGE}Teac{SE_M_TRI_ATTACK}you{SE_M_SUPERSONIC}{SE_M_HEAL_BELL}will!\p"
	.string "I{SE_M_ATTRACT}battle{SE_M_SUPERSONIC}POKéMO{SE_M_PSYBEAM2}to{SE_M_MORNING_SUN}o{SE_M_ATTRACT}list\n"
	.string "jum{SE_M_MORNING_SUN}ou{SE_M_SPIT_UP}first!\p"
	.string "Chang{SE_M_REVERSAL}orde{SE_M_SAND_TOMB}i{SE_M_ATTRACT}list{SE_M_SUPERSONIC}make\n"
	.string "battl{SE_M_REVERSAL}easy{SE_M_SUPERSONIC}maybe!\p"
	.string "Mor{SE_M_REVERSAL}fro{SE_M_MILK_DRINK}m{SE_M_REVERSAL}yo{SE_M_DIVE}wan{SE_M_SPIT_UP}t{SE_M_ATTRACT2}hear?$"

VioletCity_TrainerSchool_Text_TeachMore:
	.string "So{SE_M_SUPERSONIC}wan{SE_M_SPIT_UP}t{SE_M_ATTRACT2}kno{SE_M_TWISTER}ho{SE_M_TWISTER}t{SE_M_ATTRACT2}raise\n"
	.string "POKéMO{SE_M_PSYBEAM2}well?$"

VioletCity_TrainerSchool_Text_TeachRaiseWell:
	.string "Fine{SE_M_DRAGON_RAGE}Teac{SE_M_TRI_ATTACK}you{SE_M_SUPERSONIC}{SE_M_HEAL_BELL}will!\p"
	.string "I{SE_M_ACID_ARMOR}POKéMO{SE_M_PSYBEAM2}com{SE_M_REVERSAL}ou{SE_M_SPIT_UP}i{SE_M_ATTRACT}battle\n"
	.string "eve{SE_M_ATTRACT}briefly{SE_M_SUPERSONIC}som{SE_M_REVERSAL}EXP{SE_M_PERISH_SONG}Points\p"
	.string "i{SE_M_SPIT_UP}gets.\n"
	.string "A{SE_M_SPIT_UP}to{SE_M_MORNING_SUN}o{SE_M_ACID_ARMOR}lis{SE_M_SPIT_UP}pu{SE_M_SPIT_UP}wea{SE_M_ENCORE2}POKéMON\p"
	.string "Switc{SE_M_TRI_ATTACK}i{SE_M_ATTRACT}battl{SE_M_REVERSAL}quick!\n"
	.string "Thi{SE_M_GRASSWHISTLE}way{SE_M_SUPERSONIC}wea{SE_M_ENCORE2}POKéMO{SE_M_PSYBEAM2}strong\p"
	.string "become!$"

VioletCity_TrainerSchool_Text_NoMoreToTeach:
	.string "Oh{SE_M_DRAGON_RAGE}Smar{SE_M_SPIT_UP}studen{SE_M_SPIT_UP}yo{SE_M_DIVE}are!\n"
	.string "Nothin{SE_M_SANDSTORM}mor{SE_M_REVERSAL}d{SE_M_ATTRACT2}{SE_M_HEAL_BELL}teach!\p"
	.string "I{SE_M_ACID_ARMOR}yo{SE_M_DIVE}wan{SE_M_SPIT_UP}more{SE_M_SUPERSONIC}tal{SE_M_ENCORE2}to\n"
	.string "pupils!$"

VioletCity_TrainerSchool_Text_Youngster1:
	.string "POKéMO{SE_M_PSYBEAM2}previousl{SE_M_YAWN}though{SE_M_SPIT_UP}to\n"
	.string "onl{SE_M_YAWN}evolv{SE_M_REVERSAL}throug{SE_M_TRI_ATTACK}trad{SE_M_REVERSAL}can\p"
	.string "evolv{SE_M_REVERSAL}throug{SE_M_TRI_ATTACK}leveling.\n"
	.string "MACHOK{SE_M_SWORDS_DANCE}an{SE_M_WATERFALL}GRAVELE{SE_M_MINIMIZE}evolve\p"
	.string "a{SE_M_SPIT_UP}LV{SE_M_BRICK_BREAK}38{SE_M_SUPERSONIC}whil{SE_M_REVERSAL}KADABR{SE_M_BONEMERANG}and\n"
	.string "HAUNTE{SE_M_MINIMIZE}evolv{SE_M_REVERSAL}a{SE_M_SPIT_UP}LV{SE_M_BRICK_BREAK}42.\p"
	.string "Som{SE_M_REVERSAL}items{SE_M_SUPERSONIC}lik{SE_M_REVERSAL}th{SE_M_REVERSAL}METAL\n"
	.string "COAT{SE_M_SUPERSONIC}hav{SE_M_REVERSAL}als{SE_M_ATTRACT2}bee{SE_M_ATTRACT}foun{SE_M_WATERFALL}to\p"
	.string "evolv{SE_M_REVERSAL}certai{SE_M_ATTRACT}POKéMON\n"
	.string "whil{SE_M_REVERSAL}holdin{SE_M_SANDSTORM}an{SE_M_WATERFALL}levelin{SE_M_SANDSTORM}up.$"

VioletCity_TrainerSchool_Text_GameboyKid1:
	.string "Notabl{SE_M_REVERSAL}POKéMO{SE_M_PSYBEAM2}availabl{SE_M_REVERSAL}i{SE_M_ATTRACT}an\n"
	.string "are{SE_M_CHARGE}ca{SE_M_ATTRACT}b{SE_M_REVERSAL}see{SE_M_ATTRACT}i{SE_M_ATTRACT}th{SE_M_REVERSAL}overworld!\p"
	.string "Bu{SE_M_SPIT_UP}mak{SE_M_REVERSAL}sur{SE_M_REVERSAL}t{SE_M_ATTRACT2}chec{SE_M_ENCORE2}routes\n"
	.string "a{SE_M_SPIT_UP}DA{SE_M_MOONLIGHT}an{SE_M_WATERFALL}NIGHT!$"

VioletCity_TrainerSchool_Text_GameboyKid2:
	.string "BERRIE{SE_M_SKETCH}i{SE_M_ATTRACT}th{SE_M_REVERSAL}JOHT{SE_M_SOLAR_BEAM}regio{SE_M_ATTRACT}are\n"
	.string "goo{SE_M_WATERFALL}fo{SE_M_SAND_TOMB}healin{SE_M_SANDSTORM}an{SE_M_WATERFALL}makin{SE_M_SANDSTORM}BALLS.\p"
	.string "BERRIE{SE_M_SKETCH}i{SE_M_ATTRACT}KANT{SE_M_SOLAR_BEAM}ar{SE_M_REVERSAL}goo{SE_M_WATERFALL}for\n"
	.string "reducin{SE_M_SANDSTORM}{SE_M_CHARGE}POKéMON'{SE_M_GRASSWHISTLE}stats.\p"
	.string "Th{SE_M_REVERSAL}DOJ{SE_M_SOLAR_BEAM}i{SE_M_ATTRACT}KANT{SE_M_SOLAR_BEAM}help{SE_M_GRASSWHISTLE}POKéMON\n"
	.string "perfec{SE_M_SPIT_UP}individua{SE_M_BATON_PASS}stats.$"

VioletCity_TrainerSchool_Text_Youngster2:
	.string "B{SE_M_REVERSAL}awar{SE_M_REVERSAL}tha{SE_M_SPIT_UP}you{SE_M_SAND_TOMB}opponents\n"
	.string "no{SE_M_TWISTER}us{SE_M_REVERSAL}team{SE_M_GRASSWHISTLE}wit{SE_M_TRI_ATTACK}bette{SE_M_SAND_TOMB}type\l"
	.string "coverage{SE_M_SUPERSONIC}s{SE_M_ATTRACT2}expec{SE_M_SPIT_UP}{SE_M_CHARGE}much\l"
	.string "mor{SE_M_REVERSAL}challengin{SE_M_SANDSTORM}journe{SE_M_YAWN}ahead.$"

VioletCity_TrainerSchool_Text_Blackboard:
	.string "Th{SE_M_REVERSAL}blackboar{SE_M_WATERFALL}describes\n"
	.string "POKéMO{SE_M_PSYBEAM2}H{SE_M_GIGA_DRAIN}moves.\p"
	.string "HMs{SE_M_SUPERSONIC}onc{SE_M_REVERSAL}unlocked{SE_M_SUPERSONIC}don'{SE_M_SPIT_UP}nee{SE_M_WATERFALL}to\n"
	.string "b{SE_M_REVERSAL}taugh{SE_M_SPIT_UP}t{SE_M_ATTRACT2}b{SE_M_REVERSAL}used.$"

VioletCity_TrainerSchool_Text_Notebook:
	.string "It'{SE_M_GRASSWHISTLE}thi{SE_M_GRASSWHISTLE}kid'{SE_M_GRASSWHISTLE}notebook…\p"
	.string "Catc{SE_M_TRI_ATTACK}POKéMO{SE_M_PSYBEAM2}usin{SE_M_SANDSTORM}POK{SE_U}BALLS.\p"
	.string "U{SE_M_MORNING_SUN}t{SE_M_ATTRACT2}si{SE_M_SWEET_SCENT}ca{SE_M_ATTRACT}b{SE_M_REVERSAL}i{SE_M_ATTRACT}you{SE_M_SAND_TOMB}party.\p"
	.string "Kee{SE_M_MORNING_SUN}reading?$"

VioletCity_TrainerSchool_Text_Notebook1:
	.string "Befor{SE_M_REVERSAL}throwin{SE_M_SANDSTORM}{SE_M_CHARGE}POK{SE_U}BALL,\n"
	.string "weake{SE_M_ATTRACT}th{SE_M_REVERSAL}targe{SE_M_SPIT_UP}first.\p"
	.string "{SE_M_BONEMERANG}poisone{SE_M_WATERFALL}o{SE_M_SAND_TOMB}burne{SE_M_WATERFALL}POKéMON\n"
	.string "i{SE_M_GRASSWHISTLE}easie{SE_M_SAND_TOMB}t{SE_M_ATTRACT2}catch.\p"
	.string "Kee{SE_M_MORNING_SUN}reading?$"

VioletCity_TrainerSchool_Text_Notebook2:
	.string "Som{SE_M_REVERSAL}move{SE_M_GRASSWHISTLE}ma{SE_M_YAWN}caus{SE_M_REVERSAL}confusion.\p"
	.string "Confusio{SE_M_ATTRACT}ma{SE_M_YAWN}mak{SE_M_REVERSAL}{SE_M_CHARGE}POKéMON\n"
	.string "attac{SE_M_ENCORE2}itself.\p"
	.string "Leavin{SE_M_SANDSTORM}battl{SE_M_REVERSAL}clear{SE_M_GRASSWHISTLE}u{SE_M_MORNING_SUN}any\n"
	.string "confusion.\p"
	.string "Kee{SE_M_MORNING_SUN}reading?$"

VioletCity_TrainerSchool_Text_Notebook3:
	.string "Peopl{SE_M_REVERSAL}wh{SE_M_ATTRACT2}catc{SE_M_TRI_ATTACK}an{SE_M_WATERFALL}use\n"
	.string "POKéMO{SE_M_PSYBEAM2}i{SE_M_ATTRACT}battl{SE_M_REVERSAL}ar{SE_M_REVERSAL}POKéMON\n"
	.string "trainers.\p"
	.string "The{SE_M_YAWN}ar{SE_M_REVERSAL}expecte{SE_M_WATERFALL}t{SE_M_ATTRACT2}visit\n"
	.string "POKéMO{SE_M_PSYBEAM2}GYM{SE_M_SKETCH}an{SE_M_WATERFALL}defea{SE_M_SPIT_UP}other\n"
	.string "trainers.\p"
	.string "Th{SE_M_REVERSAL}nex{SE_M_SPIT_UP}pag{SE_M_REVERSAL}is{SE_M_DIZZY_PUNCH}Blank!\p"
	.string "Boy{SE_M_HEAT_WAVE}E-he-he…\p"
	.string "{SE_M_HEAL_BELL}haven'{SE_M_SPIT_UP}writte{SE_M_ATTRACT}anymore…$"

VioletCity_TrainerSchool_Text_StickerMachine:
	.string "Thi{SE_M_GRASSWHISTLE}supe{SE_M_SAND_TOMB}machin{SE_M_REVERSAL}print{SE_M_GRASSWHISTLE}data\n"
	.string "ou{SE_M_SPIT_UP}a{SE_M_GRASSWHISTLE}stickers!$"

