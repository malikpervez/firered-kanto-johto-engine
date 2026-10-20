@ Johto (data/maps/RuinsOfAlph_Outside_hns/scripts.inc), as built into the FireRed game.

RuinsOfAlph_Outside_hns_MapScripts::
	map_script 3, RuinsOfAlph_Outside_OnTransition
	map_script 5, J_SetTimeEncounters
	.byte 0

RuinsOfAlph_Outside_OnTransition:
	callnative SetTimeBasedEncounters
	end

RuinsOfAlph_Outside_EventScript_Quagsire::
	lock
	faceplayer
	waitse
	playmoncry 195, 0
	msgbox RuinsOfAlph_Outside_Text_Quagsire, MSGBOX_DEFAULT
	waitmoncry
	release
	end

RuinsOfAlph_Outside_Text_Quagsire:
	.string "QUAGSIRE{SE_M_HEAT_WAVE}Qua{SE_M_SANDSTORM}Quag$"

RuinsOfAlph_Outside_EventScript_Stan::
	trainerbattle_single 1266, RuinsOfAlph_Outside_Text_SuperNerdStan_Seen, RuinsOfAlph_Outside_Text_SuperNerdStan_Beaten
	msgbox RuinsOfAlph_Outside_Text_SuperNerdStan_After, MSGBOX_AUTOCLOSE
	end

RuinsOfAlph_Outside_EventScript_Nathan::
	trainerbattle_single 1330, RuinsOfAlph_Outside_Text_PsychicNathan_Seen, RuinsOfAlph_Outside_Text_PsychicNathan_Beaten
	msgbox RuinsOfAlph_Outside_Text_PsychicNathan_After, MSGBOX_AUTOCLOSE
	end

RuinsOfAlph_Outside_EventScript_Youngster1::
	lock
	faceplayer
	msgbox RuinsOfAlph_Outside_Text_Youngster1, MSGBOX_DEFAULT
	closemessage
	release
	end

RuinsOfAlph_Outside_EventScript_Youngster2::
	lock
	faceplayer
	msgbox RuinsOfAlph_Outside_Text_Youngster2, MSGBOX_DEFAULT
	closemessage
	release
	end

RuinsOfAlph_Outside_EventScript_Fisher1::
	lock
	faceplayer
	msgbox RuinsOfAlph_Outside_Text_Fisher1, MSGBOX_DEFAULT
	closemessage
	release
	end

RuinsOfAlph_Outside_EventScript_Fisher2::
	lock
	faceplayer
	msgbox RuinsOfAlph_Outside_Text_Fisher2, MSGBOX_DEFAULT
	closemessage
	release
	end

RuinsOfAlph_Outside_EventScript_Sign1::
	lock
	msgbox RuinsOfAlph_Outside_Text_MainSign, MSGBOX_SIGN
	closemessage
	release
	end

RuinsOfAlph_Outside_EventScript_Sign2::
	lock
	msgbox RuinsOfAlph_Outside_Text_ResearchSign, MSGBOX_SIGN
	closemessage
	release
	end

RuinsOfAlph_Outside_EventScript_Sign3::
	lock
	msgbox RuinsOfAlph_Outside_Text_MysteryChamberSign, MSGBOX_SIGN
	closemessage
	release
	end

RuinsOfAlph_Outside_Text_Scientist:
	.string "Hm{SE_M_SING}That'{SE_M_GRASSWHISTLE}{SE_M_CHARGE}POKéDEX{SE_M_SUPERSONIC}isn'{SE_M_SPIT_UP}it?\n"
	.string "Ma{SE_M_YAWN}{SE_M_HEAL_BELL}se{SE_M_REVERSAL}it?\p"
	.string "Ther{SE_M_REVERSAL}ar{SE_M_REVERSAL}s{SE_M_ATTRACT2}man{SE_M_YAWN}kind{SE_M_GRASSWHISTLE}of\n"
	.string "POKéMON.\p"
	.string "Hm{SE_M_SING}What'{SE_M_GRASSWHISTLE}this?\p"
	.string "Wha{SE_M_SPIT_UP}i{SE_M_GRASSWHISTLE}thi{SE_M_GRASSWHISTLE}POKéMON?\p"
	.string "I{SE_M_SPIT_UP}look{SE_M_GRASSWHISTLE}lik{SE_M_REVERSAL}th{SE_M_REVERSAL}strange\n"
	.string "writin{SE_M_SANDSTORM}o{SE_M_ATTRACT}th{SE_M_REVERSAL}wall{SE_M_GRASSWHISTLE}o{SE_M_ACID_ARMOR}the\p"
	.string "RUINS.\p"
	.string "I{SE_M_ACID_ARMOR}thos{SE_M_REVERSAL}drawing{SE_M_GRASSWHISTLE}ar{SE_M_REVERSAL}really\n"
	.string "POKéMON{SE_M_SUPERSONIC}ther{SE_M_REVERSAL}shoul{SE_M_WATERFALL}b{SE_M_REVERSAL}many\n"
	.string "more.\p"
	.string "{SE_M_HEAL_BELL}know{SE_M_DRAGON_RAGE}Le{SE_M_SPIT_UP}m{SE_M_REVERSAL}upgrad{SE_M_REVERSAL}your\n"
	.string "POKéDEX{SE_M_PERISH_SONG}Follo{SE_M_TWISTER}me.$"

RuinsOfAlph_Outside_Text_SuperNerdStan_Seen:
	.string "Wha{SE_M_SPIT_UP}d{SE_M_ATTRACT2}yo{SE_M_DIVE}want{SE_M_SING}I'{SE_M_MILK_DRINK}studying--\n"
	.string "don'{SE_M_SPIT_UP}distur{SE_M_STRENGTH}me!$"

RuinsOfAlph_Outside_Text_SuperNerdStan_Beaten:
	.string "Sorry…\n"
	.string "I'{SE_M_MILK_DRINK}frustrate{SE_M_WATERFALL}b{SE_M_YAWN}ou{SE_M_SAND_TOMB}lac{SE_M_ENCORE2}of\p"
	.string "rea{SE_M_BATON_PASS}understanding…$"

RuinsOfAlph_Outside_Text_SuperNerdStan_After:
	.string "Th{SE_M_REVERSAL}RUIN{SE_M_SKETCH}ar{SE_M_REVERSAL}fro{SE_M_MILK_DRINK}abou{SE_M_SPIT_UP}1500\n"
	.string "year{SE_M_GRASSWHISTLE}ago.\p"
	.string "Nobod{SE_M_YAWN}know{SE_M_GRASSWHISTLE}wh{SE_M_ATTRACT2}buil{SE_M_SPIT_UP}them.\p"
	.string "It'{SE_M_GRASSWHISTLE}als{SE_M_ATTRACT2}no{SE_M_SPIT_UP}know{SE_M_ATTRACT}i{SE_M_ACID_ARMOR}th{SE_M_REVERSAL}POKéMON\n"
	.string "statue{SE_M_GRASSWHISTLE}hav{SE_M_REVERSAL}an{SE_M_YAWN}meaning.\p"
	.string "It'{SE_M_GRASSWHISTLE}al{SE_M_BATON_PASS}on{SE_M_REVERSAL}bi{SE_M_SANDSTORM}mystery…$"

RuinsOfAlph_Outside_Text_PsychicNathan_Seen:
	.string "Hmmm{SE_M_DIZZY_PUNCH}Thi{SE_M_GRASSWHISTLE}i{SE_M_GRASSWHISTLE}{SE_M_CHARGE}strang{SE_M_REVERSAL}place.$"

RuinsOfAlph_Outside_Text_PsychicNathan_Beaten:
	.string "…$"

RuinsOfAlph_Outside_Text_PsychicNathan_After:
	.string "{SE_M_HEAL_BELL}lik{SE_M_REVERSAL}thinkin{SE_M_SANDSTORM}here.$"

RuinsOfAlph_Outside_Text_MysteryChamberSign:
	.string "MYSTER{SE_M_MOONLIGHT}STON{SE_M_SWORDS_DANCE}PANE{SE_M_BRICK_BREAK}CHAMBER$"

RuinsOfAlph_Outside_Text_MainSign:
	.string "RUIN{SE_M_SKETCH}O{SE_M_LEER}ALPH\n"
	.string "VISITOR{SE_M_SKETCH}WELCOME$"

RuinsOfAlph_Outside_Text_ResearchSign:
	.string "RUIN{SE_M_SKETCH}O{SE_M_LEER}ALP{SE_M_SWAGGER2}RESEARC{SE_M_SWAGGER2}CENTER\p"
	.string "TH{SE_M_SWORDS_DANCE}AUTHORIT{SE_M_MOONLIGHT}O{SE_M_PSYBEAM2}THE\n"
	.string "RUIN{SE_M_SKETCH}O{SE_M_LEER}ALPH$"

RuinsOfAlph_Outside_Text_Fisher1:
	.string "Whil{SE_M_REVERSAL}explorin{SE_M_SANDSTORM}th{SE_M_REVERSAL}RUINS{SE_M_SUPERSONIC}we\n"
	.string "suddenl{SE_M_YAWN}notice{SE_M_WATERFALL}a{SE_M_ATTRACT}od{SE_M_WATERFALL}presence.\p"
	.string "W{SE_M_REVERSAL}al{SE_M_BATON_PASS}go{SE_M_SPIT_UP}scare{SE_M_WATERFALL}an{SE_M_WATERFALL}ra{SE_M_ATTRACT}away.\n"
	.string "Yo{SE_M_DIVE}shoul{SE_M_WATERFALL}b{SE_M_REVERSAL}carefu{SE_M_BATON_PASS}too.$"

RuinsOfAlph_Outside_Text_Fisher2:
	.string "Th{SE_M_REVERSAL}RUIN{SE_M_SKETCH}hid{SE_M_REVERSAL}{SE_M_CHARGE}hug{SE_M_REVERSAL}secret!\p"
	.string "…{SE_M_HEAL_BELL}think…$"

RuinsOfAlph_Outside_Text_Youngster1:
	.string "Ther{SE_M_REVERSAL}ar{SE_M_REVERSAL}man{SE_M_YAWN}kind{SE_M_GRASSWHISTLE}o{SE_M_ACID_ARMOR}UNOWN{SE_M_SUPERSONIC}so\n"
	.string "w{SE_M_REVERSAL}us{SE_M_REVERSAL}the{SE_M_MILK_DRINK}fo{SE_M_SAND_TOMB}ou{SE_M_SAND_TOMB}secre{SE_M_SPIT_UP}codes.$"

RuinsOfAlph_Outside_Text_Youngster2:
	.string "A{SE_M_DIZZY_PUNCH}H{SE_M_DIZZY_PUNCH}E{SE_M_DIZZY_PUNCH}A{SE_M_DIZZY_PUNCH}D{SE_M_DIZZY_PUNCH}Hmm…\p"
	.string "What?\p"
	.string "I'{SE_M_MILK_DRINK}decodin{SE_M_SANDSTORM}thi{SE_M_GRASSWHISTLE}message!$"

