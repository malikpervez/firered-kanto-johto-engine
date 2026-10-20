@ Johto (data/maps/SSAqua_B1F_hns/scripts.inc), as built into the FireRed game.

SSAqua_B1F_hns_MapScripts::
	.byte 0

SSAqua_B1F_EventScript_Trigger::
	lock
	turnobject 10, DIR_EAST
	turnobject 255, DIR_WEST
	msgbox SSAqua_B1F_Text_FastShipOnDutySailor, MSGBOX_DEFAULT
	closemessage
	applymovement 255, J_Common_Movement_WalkDown1
	waitmovement 0
	turnobject 10, DIR_SOUTH
	release
	end

SSAqua_B1F_EventScript_SailorLookingForBuddy::
	lock
	faceplayer
	goto_if_set 8328, SSAqua_B1F_EventScript_SailorLookingFoundBuddy
	msgbox SSAqua_B1F_Text_FastShipOnDutySailor, MSGBOX_DEFAULT
	closemessage
	release
	end

SSAqua_B1F_EventScript_SailorLookingFoundBuddy::
	msgbox SSAqua_B1F_Text_FastShipOnDutySailorThanks, MSGBOX_DEFAULT
	goto_if_lt 20603, 5, SSAqua_B1F_EventScript_SailorGirl
	closemessage
	release
	end

SSAqua_B1F_EventScript_SailorGirl::
	msgbox SSAqua_B1F_Text_FastShipOnDutySailorSawGirl, MSGBOX_DEFAULT
	closemessage
	release
	end

SSAqua_B1F_EventScript_SleepySailor::
	msgbox SSAqua_B1F_Text_FastShipOnDutySailorDirections, MSGBOX_NPC
	end

SSAqua_B1F_EventScript_Barfcan::
	msgbox SSAqua_B1F_Text_BarfCan, MSGBOX_SIGN
	end

SSAqua_B1F_Text_BarfCan:
	.string "Yuck!\n"
	.string "Shouldn'{SE_M_SPIT_UP}hav{SE_M_REVERSAL}looked!$"

SSAqua_B1F_Text_FastShipOnDutySailor:
	.string "Hey{SE_M_SUPERSONIC}kid{SE_M_PERISH_SONG}Coul{SE_M_WATERFALL}{SE_M_HEAL_BELL}ge{SE_M_SPIT_UP}yo{SE_M_DIVE}to\n"
	.string "loo{SE_M_ENCORE2}fo{SE_M_SAND_TOMB}m{SE_M_YAWN}buddy?\p"
	.string "He'{SE_M_GRASSWHISTLE}goofin{SE_M_SANDSTORM}of{SE_M_ACID_ARMOR}somewhere,\n"
	.string "tha{SE_M_SPIT_UP}laz{SE_M_YAWN}bum!\p"
	.string "{SE_M_HEAL_BELL}wan{SE_M_SPIT_UP}t{SE_M_ATTRACT2}g{SE_M_ATTRACT2}fin{SE_M_WATERFALL}him{SE_M_SUPERSONIC}bu{SE_M_SPIT_UP}I'm\n"
	.string "o{SE_M_ATTRACT}dut{SE_M_YAWN}righ{SE_M_SPIT_UP}now.$"

SSAqua_B1F_Text_FastShipOnDutySailorRefused:
	.string "Oh{SE_M_SUPERSONIC}gee…\p"
	.string "Th{SE_M_REVERSAL}CAPTAI{SE_M_PSYBEAM2}wil{SE_M_BATON_PASS}b{SE_M_REVERSAL}furious…$"

SSAqua_B1F_Text_FastShipOnDutySailorThanks:
	.string "Thanks{SE_M_SUPERSONIC}kid{SE_M_DRAGON_RAGE}{SE_M_HEAL_BELL}chewe{SE_M_WATERFALL}hi{SE_M_MILK_DRINK}out\n"
	.string "goo{SE_M_WATERFALL}s{SE_M_ATTRACT2}he'l{SE_M_BATON_PASS}qui{SE_M_SPIT_UP}slackin{SE_M_SANDSTORM}off!$"

SSAqua_B1F_Text_FastShipOnDutySailorSawGirl:
	.string "{SE_M_BONEMERANG}littl{SE_M_REVERSAL}girl?\p"
	.string "{SE_M_HEAL_BELL}ma{SE_M_YAWN}hav{SE_M_REVERSAL}see{SE_M_ATTRACT}he{SE_M_SAND_TOMB}g{SE_M_ATTRACT2}b{SE_M_YAWN}here.$"

SSAqua_B1F_Text_FastShipOnDutySailorDirections:
	.string "Th{SE_M_REVERSAL}dinin{SE_M_SANDSTORM}roo{SE_M_MILK_DRINK}i{SE_M_GRASSWHISTLE}u{SE_M_MORNING_SUN}ahead.\p"
	.string "Th{SE_M_REVERSAL}stair{SE_M_GRASSWHISTLE}a{SE_M_SPIT_UP}th{SE_M_REVERSAL}en{SE_M_WATERFALL}lea{SE_M_WATERFALL}to\n"
	.string "th{SE_M_REVERSAL}CAPTAIN'{SE_M_GRASSWHISTLE}cabin.$"

SSAqua_B1F_EventScript_Jeff::
	trainerbattle_single 1261, SSAqua_B1F_Text_SailorJeffSeen, SSAqua_B1F_Text_SailorJeffBeaten
	msgbox SSAqua_B1F_Text_SailorJeffAfter, MSGBOX_AUTOCLOSE
	end

SSAqua_B1F_Text_SailorJeffSeen:
	.string "Nothin{SE_M_SANDSTORM}beat{SE_M_GRASSWHISTLE}{SE_M_CHARGE}battl{SE_M_REVERSAL}when\n"
	.string "I'{SE_M_MILK_DRINK}o{SE_M_ATTRACT}m{SE_M_YAWN}break.$"

SSAqua_B1F_Text_SailorJeffBeaten:
	.string "Wi{SE_M_ATTRACT}o{SE_M_SAND_TOMB}lose{SE_M_SUPERSONIC}m{SE_M_YAWN}break'{SE_M_GRASSWHISTLE}over!$"

SSAqua_B1F_Text_SailorJeffAfter:
	.string "{SE_M_HEAL_BELL}gues{SE_M_GRASSWHISTLE}{SE_M_HEAL_BELL}can'{SE_M_SPIT_UP}wi{SE_M_ATTRACT}i{SE_M_ACID_ARMOR}{SE_M_HEAL_BELL}don't\n"
	.string "ge{SE_M_SPIT_UP}serious.$"

SSAqua_B1F_EventScript_Debra::
	trainerbattle_single 1349, SSAqua_B1F_Text_PicnickerDebraSeen, SSAqua_B1F_Text_PicnickerDebraBeaten
	msgbox SSAqua_B1F_Text_PicnickerDebraAfter, MSGBOX_AUTOCLOSE
	end

SSAqua_B1F_Text_PicnickerDebraSeen:
	.string "I'{SE_M_MILK_DRINK}s{SE_M_ATTRACT2}bored{SE_M_PERISH_SONG}Wan{SE_M_SPIT_UP}t{SE_M_ATTRACT2}battle?$"

SSAqua_B1F_Text_PicnickerDebraBeaten:
	.string "Yow{SE_M_DRAGON_RAGE}You'r{SE_M_REVERSAL}to{SE_M_ATTRACT2}strong!$"

SSAqua_B1F_Text_PicnickerDebraAfter:
	.string "SAFFRON{SE_M_SUPERSONIC}CELADON{SE_M_DIZZY_PUNCH}{SE_M_HEAL_BELL}hea{SE_M_SAND_TOMB}there\n"
	.string "ar{SE_M_REVERSAL}man{SE_M_YAWN}bi{SE_M_SANDSTORM}citie{SE_M_GRASSWHISTLE}i{SE_M_ATTRACT}KANTO.$"

SSAqua_B1F_EventScript_Fritz::
	trainerbattle_single 1321, SSAqua_B1F_Text_JugglerFritzSeen, SSAqua_B1F_Text_JugglerFritzBeaten
	msgbox SSAqua_B1F_Text_JugglerFritzAfter, MSGBOX_AUTOCLOSE
	end

SSAqua_B1F_Text_JugglerFritzSeen:
	.string "Urrf{SE_M_DIZZY_PUNCH}I'{SE_M_MILK_DRINK}seasick!$"

SSAqua_B1F_Text_JugglerFritzBeaten:
	.string "{SE_M_HEAL_BELL}can'{SE_M_SPIT_UP}mov{SE_M_REVERSAL}anymore…$"

SSAqua_B1F_Text_JugglerFritzAfter:
	.string "N{SE_M_ATTRACT2}mor{SE_M_REVERSAL}ship{SE_M_GRASSWHISTLE}fo{SE_M_SAND_TOMB}me.\n"
	.string "Nex{SE_M_SPIT_UP}time,\p"
	.string "I'{SE_M_MILK_DRINK}takin{SE_M_SANDSTORM}th{SE_M_REVERSAL}MAGNE{SE_M_SWIFT}TRAIN.$"

SSAqua_B1F_EventScript_Garrett::
	trainerbattle_single 1262, SSAqua_B1F_Text_SailorGarrettSeen, SSAqua_B1F_Text_SailorGarrettBeaten
	msgbox SSAqua_B1F_Text_SailorGarrettAfter, MSGBOX_AUTOCLOSE
	end

SSAqua_B1F_Text_SailorGarrettSeen:
	.string "Thi{SE_M_GRASSWHISTLE}i{SE_M_GRASSWHISTLE}wher{SE_M_REVERSAL}w{SE_M_REVERSAL}sailor{SE_M_GRASSWHISTLE}work!$"

SSAqua_B1F_Text_SailorGarrettBeaten:
	.string "{SE_M_HEAL_BELL}los{SE_M_SPIT_UP}o{SE_M_ATTRACT}m{SE_M_YAWN}hom{SE_M_REVERSAL}field…$"

SSAqua_B1F_Text_SailorGarrettAfter:
	.string "W{SE_M_REVERSAL}ge{SE_M_SPIT_UP}differen{SE_M_SPIT_UP}passengers\n"
	.string "fro{SE_M_MILK_DRINK}VERMILIO{SE_M_PSYBEAM2}CIT{SE_M_MOONLIGHT}to\p"
	.string "OLIVIN{SE_M_SWORDS_DANCE}CITY.$"

SSAqua_B1F_EventScript_Jonah::
	trainerbattle_single 1211, SSAqua_B1F_Text_FisherJonahSeen, SSAqua_B1F_Text_FisherJonahBeaten
	msgbox SSAqua_B1F_Text_FisherJonahAfter, MSGBOX_AUTOCLOSE
	end

SSAqua_B1F_Text_FisherJonahSeen:
	.string "Eve{SE_M_ATTRACT}thoug{SE_M_TRI_ATTACK}we'r{SE_M_REVERSAL}ou{SE_M_SPIT_UP}o{SE_M_ATTRACT}the\n"
	.string "sea{SE_M_SUPERSONIC}{SE_M_HEAL_BELL}can'{SE_M_SPIT_UP}fish!\p"
	.string "Thi{SE_M_GRASSWHISTLE}i{SE_M_GRASSWHISTLE}boring{SE_M_DRAGON_RAGE}Let'{SE_M_GRASSWHISTLE}battle!$"

SSAqua_B1F_Text_FisherJonahBeaten:
	.string "I{SE_M_DIZZY_PUNCH}I'{SE_M_MILK_DRINK}no{SE_M_SPIT_UP}bore{SE_M_WATERFALL}anymore…$"

SSAqua_B1F_Text_FisherJonahAfter:
	.string "{SE_M_HEAL_BELL}pla{SE_M_ATTRACT}t{SE_M_ATTRACT2}fis{SE_M_TRI_ATTACK}off\n"
	.string "VERMILION'{SE_M_GRASSWHISTLE}pier.$"

SSAqua_B1F_EventScript_Wai::
	trainerbattle_single 1329, SSAqua_B1F_Text_BlackbeltWaiSeen, SSAqua_B1F_Text_BlackbeltWaiBeaten
	msgbox SSAqua_B1F_Text_BlackbeltWaiAfter, MSGBOX_AUTOCLOSE
	end

SSAqua_B1F_Text_BlackbeltWaiSeen:
	.string "I'{SE_M_MILK_DRINK}buildin{SE_M_SANDSTORM}u{SE_M_MORNING_SUN}m{SE_M_YAWN}leg{SE_M_GRASSWHISTLE}by\n"
	.string "bracing\p"
	.string "agains{SE_M_SPIT_UP}th{SE_M_REVERSAL}ship'{SE_M_GRASSWHISTLE}rocking!$"

SSAqua_B1F_Text_BlackbeltWaiBeaten:
	.string "Rocke{SE_M_WATERFALL}an{SE_M_WATERFALL}rolle{SE_M_WATERFALL}over!$"

SSAqua_B1F_Text_BlackbeltWaiAfter:
	.string "{SE_M_HEAL_BELL}couldn'{SE_M_SPIT_UP}fin{SE_M_WATERFALL}th{SE_M_REVERSAL}KARAT{SE_M_SWORDS_DANCE}KING\n"
	.string "i{SE_M_ATTRACT}JOHTO.\p"
	.string "He'{SE_M_GRASSWHISTLE}suppose{SE_M_WATERFALL}t{SE_M_ATTRACT2}b{SE_M_REVERSAL}trainin{SE_M_SANDSTORM}in\n"
	.string "{SE_M_CHARGE}cav{SE_M_REVERSAL}somewhere.$"

SSAqua_B1F_EventScript_Kenneth::
	trainerbattle_single 1263, SSAqua_B1F_Text_SailorKennethSeen, SSAqua_B1F_Text_SailorKennethBeaten
	msgbox SSAqua_B1F_Text_SailorKennethAfter, MSGBOX_AUTOCLOSE
	end

SSAqua_B1F_Text_SailorKennethSeen:
	.string "I'{SE_M_MILK_DRINK}{SE_M_CHARGE}sailo{SE_M_SAND_TOMB}man!\p"
	.string "Bu{SE_M_SPIT_UP}I'{SE_M_MILK_DRINK}trainin{SE_M_SANDSTORM}POKéMON{SE_M_SUPERSONIC}s{SE_M_ATTRACT2}I\n"
	.string "ca{SE_M_ATTRACT}becom{SE_M_REVERSAL}th{SE_M_REVERSAL}CHAMP!$"

SSAqua_B1F_Text_SailorKennethBeaten:
	.string "M{SE_M_YAWN}lac{SE_M_ENCORE2}o{SE_M_ACID_ARMOR}trainin{SE_M_SANDSTORM}i{SE_M_GRASSWHISTLE}obvious…$"

SSAqua_B1F_Text_SailorKennethAfter:
	.string "Eigh{SE_M_SPIT_UP}BADGES{SE_M_DRAGON_RAGE}The{SE_M_YAWN}mus{SE_M_SPIT_UP}prove\n"
	.string "tha{SE_M_SPIT_UP}you'v{SE_M_REVERSAL}beaten\p"
	.string "GY{SE_M_GIGA_DRAIN}LEADERS.\p"
	.string "N{SE_M_ATTRACT2}wonde{SE_M_SAND_TOMB}you'r{SE_M_REVERSAL}s{SE_M_ATTRACT2}good!$"

SSAqua_B1F_EventScript_Shirley::
	trainerbattle_single 1188, SSAqua_B1F_Text_TeacherShirleySeen, SSAqua_B1F_Text_TeacherShirleyBeaten
	msgbox SSAqua_B1F_Text_TeacherShirleyAfter, MSGBOX_AUTOCLOSE
	end

SSAqua_B1F_Text_TeacherShirleySeen:
	.string "Don'{SE_M_SPIT_UP}la{SE_M_YAWN}{SE_M_CHARGE}finge{SE_M_SAND_TOMB}o{SE_M_ATTRACT}my\n"
	.string "students!$"

SSAqua_B1F_Text_TeacherShirleyBeaten:
	.string "Aaack!$"

SSAqua_B1F_Text_TeacherShirleyAfter:
	.string "We'r{SE_M_REVERSAL}o{SE_M_ATTRACT}{SE_M_CHARGE}fiel{SE_M_WATERFALL}tri{SE_M_MORNING_SUN}t{SE_M_ATTRACT2}the\n"
	.string "RUIN{SE_M_SKETCH}outsid{SE_M_REVERSAL}VIOLET.$"

SSAqua_B1F_EventScript_Nate::
	trainerbattle_single 1051, SSAqua_B1F_Text_SchoolboyNateSeen, SSAqua_B1F_Text_SchoolboyNateBeaten
	msgbox SSAqua_B1F_Text_SchoolboyNateAfter, MSGBOX_AUTOCLOSE
	end

SSAqua_B1F_Text_SchoolboyNateSeen:
	.string "D{SE_M_ATTRACT2}yo{SE_M_DIVE}kno{SE_M_TWISTER}th{SE_M_REVERSAL}RUIN{SE_M_SKETCH}O{SE_M_LEER}ALPH?$"

SSAqua_B1F_Text_SchoolboyNateBeaten:
	.string "Yaargh!$"

SSAqua_B1F_Text_SchoolboyNateAfter:
	.string "Radio{SE_M_GRASSWHISTLE}pic{SE_M_ENCORE2}u{SE_M_MORNING_SUN}strang{SE_M_REVERSAL}signals\n"
	.string "insid{SE_M_REVERSAL}th{SE_M_REVERSAL}RUINS.$"

SSAqua_B1F_EventScript_Ricky::
	trainerbattle_single 1052, SSAqua_B1F_Text_SchoolboyRickySeen, SSAqua_B1F_Text_SchoolboyRickyBeaten
	msgbox SSAqua_B1F_Text_SchoolboyRickyAfter, MSGBOX_AUTOCLOSE
	end

SSAqua_B1F_Text_SchoolboyRickySeen:
	.string "Ther{SE_M_REVERSAL}ar{SE_M_REVERSAL}som{SE_M_REVERSAL}od{SE_M_WATERFALL}ston{SE_M_REVERSAL}panels\n"
	.string "i{SE_M_ATTRACT}th{SE_M_REVERSAL}RUIN{SE_M_SKETCH}O{SE_M_LEER}ALPH.$"

SSAqua_B1F_Text_SchoolboyRickyBeaten:
	.string "{SE_M_HEAL_BELL}wa{SE_M_GRASSWHISTLE}don{SE_M_REVERSAL}in!$"

SSAqua_B1F_Text_SchoolboyRickyAfter:
	.string "{SE_M_HEAL_BELL}rea{SE_M_WATERFALL}tha{SE_M_SPIT_UP}ther{SE_M_REVERSAL}ar{SE_M_REVERSAL}fou{SE_M_SAND_TOMB}of\n"
	.string "thos{SE_M_REVERSAL}ston{SE_M_REVERSAL}panels.$"

