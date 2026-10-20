@ Johto (data/maps/Route40_hns/scripts.inc), as built into the FireRed game.

Route40_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route40_MapScript_OnTransition
	.byte 0

Route40_MapScript_OnTransition::
	callnative SetTimeBasedEncounters
	goto_if_ge JOHTO_VAR_OLIVINE_CITY_STATE, 5, Route40_MapScript_ClearWeather
	end

Route40_MapScript_ClearWeather::
	setweather WEATHER_NONE
	end

Route40_EventScript_Simon::
	trainerbattle_single TRAINER_JOHTO_SIMON_HNS, Route40_Text_SwimmermSimonSeen, Route40_Text_SwimmermSimonBeaten
	msgbox Route40_Text_SwimmermSimonAfter, MSGBOX_AUTOCLOSE
	end

Route40_Text_SwimmermSimonSeen:
	.string "Yo{SE_M_DIVE}hav{SE_M_REVERSAL}t{SE_M_ATTRACT2}war{SE_M_MILK_DRINK}u{SE_M_MORNING_SUN}before\n"
	.string "goin{SE_M_SANDSTORM}int{SE_M_ATTRACT2}th{SE_M_REVERSAL}water.\p"
	.string "That'{SE_M_GRASSWHISTLE}basic.$"

Route40_Text_SwimmermSimonBeaten:
	.string "OK{SE_M_DRAGON_RAGE}Uncle{SE_M_DRAGON_RAGE}{SE_M_HEAL_BELL}give!$"

Route40_Text_SwimmermSimonAfter:
	.string "CIANWOO{SE_M_FAINT_ATTACK}CIT{SE_M_MOONLIGHT}i{SE_M_GRASSWHISTLE}{SE_M_CHARGE}good\n"
	.string "distanc{SE_M_REVERSAL}awa{SE_M_YAWN}fro{SE_M_MILK_DRINK}here.$"

Route40_EventScript_Randall::
	trainerbattle_single TRAINER_JOHTO_RANDALL_HNS, Route40_Text_SwimmermRandallSeen, Route40_Text_SwimmermRandallBeaten
	msgbox Route40_Text_SwimmermRandallAfter, MSGBOX_AUTOCLOSE
	end

Route40_Text_SwimmermRandallSeen:
	.string "Hey{SE_M_SUPERSONIC}you'r{SE_M_REVERSAL}youn{SE_M_SANDSTORM}an{SE_M_WATERFALL}fit!\p"
	.string "Don'{SE_M_SPIT_UP}rid{SE_M_REVERSAL}you{SE_M_SAND_TOMB}POKéMON!\n"
	.string "Swim!$"

Route40_Text_SwimmermRandallBeaten:
	.string "Uh-oh{SE_M_PERISH_SONG}{SE_M_HEAL_BELL}lost…$"

Route40_Text_SwimmermRandallAfter:
	.string "Swimmin{SE_M_SANDSTORM}exercise{SE_M_GRASSWHISTLE}your\n"
	.string "entir{SE_M_REVERSAL}body{SE_M_PERISH_SONG}It'{SE_M_GRASSWHISTLE}healthy.$"

Route40_EventScript_Elaine::
	trainerbattle_single TRAINER_JOHTO_ELAINE_HNS, Route40_Text_SwimmerfElaineSeen, Route40_Text_SwimmerfElaineBeaten
	msgbox Route40_Text_SwimmerfElaineAfter, MSGBOX_AUTOCLOSE
	end

Route40_Text_SwimmerfElaineSeen:
	.string "Ar{SE_M_REVERSAL}yo{SE_M_DIVE}goin{SE_M_SANDSTORM}t{SE_M_ATTRACT2}CIANWOOD?\p"
	.string "Ho{SE_M_TWISTER}abou{SE_M_SPIT_UP}{SE_M_CHARGE}quic{SE_M_ENCORE2}battle\n"
	.string "first?$"

Route40_Text_SwimmerfElaineBeaten:
	.string "{SE_M_HEAL_BELL}los{SE_M_SPIT_UP}tha{SE_M_SPIT_UP}one!$"

Route40_Text_SwimmerfElaineAfter:
	.string "I'{SE_M_WATERFALL}sa{SE_M_YAWN}I'{SE_M_MILK_DRINK}{SE_M_CHARGE}bette{SE_M_SAND_TOMB}swimmer\n"
	.string "tha{SE_M_ATTRACT}you{SE_M_PERISH_SONG}Yeah!$"

Route40_EventScript_Paula::
	trainerbattle_single TRAINER_JOHTO_PAULA_HNS, Route40_Text_SwimmerfPaulaSeen, Route40_Text_SwimmerfPaulaBeaten
	msgbox Route40_Text_SwimmerfPaulaAfter, MSGBOX_AUTOCLOSE
	end

Route40_Text_SwimmerfPaulaSeen:
	.string "N{SE_M_ATTRACT2}inne{SE_M_SAND_TOMB}tub{SE_M_REVERSAL}fo{SE_M_SAND_TOMB}me.\p"
	.string "I'{SE_M_MILK_DRINK}hangin{SE_M_SANDSTORM}o{SE_M_ATTRACT}t{SE_M_ATTRACT2}{SE_M_CHARGE}sea\n"
	.string "POKéMON!$"

Route40_Text_SwimmerfPaulaBeaten:
	.string "Ooh{SE_M_SUPERSONIC}I'{SE_M_MILK_DRINK}feelin{SE_M_SANDSTORM}dizzy!$"

Route40_Text_SwimmerfPaulaAfter:
	.string "Whil{SE_M_REVERSAL}{SE_M_HEAL_BELL}floa{SE_M_SPIT_UP}lik{SE_M_REVERSAL}this,\n"
	.string "th{SE_M_REVERSAL}wave{SE_M_GRASSWHISTLE}carr{SE_M_YAWN}m{SE_M_REVERSAL}along.$"

Route40_EventScript_Woman1::
	lock
	faceplayer
	msgbox Route40_Text_Lass1, MSGBOX_DEFAULT
	closemessage
	release
	end

Route40_Text_Lass1:
	.string "Althoug{SE_M_TRI_ATTACK}yo{SE_M_DIVE}can'{SE_M_SPIT_UP}se{SE_M_REVERSAL}i{SE_M_SPIT_UP}fro{SE_M_MILK_DRINK}here,\n"
	.string "CIANWOO{SE_M_FAINT_ATTACK}i{SE_M_GRASSWHISTLE}acros{SE_M_GRASSWHISTLE}th{SE_M_REVERSAL}sea.$"

Route40_EventScript_Woman2::
	lock
	faceplayer
	msgbox Route40_Text_Lass2, MSGBOX_DEFAULT
	closemessage
	release
	end

Route40_Text_Lass2:
	.string "{SE_M_HEAL_BELL}cam{SE_M_REVERSAL}t{SE_M_ATTRACT2}OLIVIN{SE_M_SWORDS_DANCE}b{SE_M_YAWN}shi{SE_M_MORNING_SUN}t{SE_M_ATTRACT2}see\n"
	.string "th{SE_M_REVERSAL}sight{SE_M_GRASSWHISTLE}an{SE_M_WATERFALL}soa{SE_M_ENCORE2}u{SE_M_MORNING_SUN}the\l"
	.string "atmosphere.\p"
	.string "Bein{SE_M_SANDSTORM}{SE_M_CHARGE}port{SE_M_SUPERSONIC}i{SE_M_SPIT_UP}feel{SE_M_GRASSWHISTLE}so\n"
	.string "differen{SE_M_SPIT_UP}fro{SE_M_MILK_DRINK}{SE_M_CHARGE}bi{SE_M_SANDSTORM}city.$"

Route40_EventScript_Youngster::
	lock
	faceplayer
	msgbox Route40_Text_StandingYoungster, MSGBOX_DEFAULT
	closemessage
	release
	end

Route40_Text_StandingYoungster:
	.string "Hav{SE_M_REVERSAL}yo{SE_M_DIVE}gon{SE_M_REVERSAL}t{SE_M_ATTRACT2}th{SE_M_REVERSAL}TRAINER\n"
	.string "HILL?\p"
	.string "{SE_M_HEAL_BELL}thin{SE_M_ENCORE2}{SE_M_CHARGE}lo{SE_M_SPIT_UP}o{SE_M_ACID_ARMOR}toug{SE_M_TRI_ATTACK}trainers\n"
	.string "hav{SE_M_REVERSAL}gathere{SE_M_WATERFALL}ther{SE_M_REVERSAL}already.\p"
	.string "Bu{SE_M_SPIT_UP}sinc{SE_M_REVERSAL}yo{SE_M_DIVE}hav{SE_M_REVERSAL}s{SE_M_ATTRACT2}man{SE_M_YAWN}BADGES\n"
	.string "yo{SE_M_DIVE}shouldn'{SE_M_SPIT_UP}d{SE_M_ATTRACT2}badl{SE_M_YAWN}a{SE_M_SPIT_UP}all.$"

Route40_Text_Monica:
	.string "MONICA{SE_M_HEAT_WAVE}Gla{SE_M_WATERFALL}t{SE_M_ATTRACT2}mee{SE_M_SPIT_UP}you.\n"
	.string "I'{SE_M_MILK_DRINK}MONIC{SE_M_BONEMERANG}o{SE_M_ACID_ARMOR}th{SE_M_REVERSAL}WEEKDA{SE_M_MOONLIGHT}FAMILY.\p"
	.string "{SE_M_HEAL_BELL}be{SE_M_SPIT_UP}yo{SE_M_DIVE}can'{SE_M_SPIT_UP}gues{SE_M_GRASSWHISTLE}m{SE_M_YAWN}favorite\n"
	.string "da{SE_M_YAWN}o{SE_M_ACID_ARMOR}th{SE_M_REVERSAL}week!$"

Route40_Text_MonicaGivesGift:
	.string "That'{SE_M_GRASSWHISTLE}right!\p"
	.string "A{SE_M_GRASSWHISTLE}{SE_M_CHARGE}toke{SE_M_ATTRACT}o{SE_M_ACID_ARMOR}ou{SE_M_SAND_TOMB}friendship,\n"
	.string "{SE_M_HEAL_BELL}hav{SE_M_REVERSAL}{SE_M_CHARGE}gif{SE_M_SPIT_UP}fo{SE_M_SAND_TOMB}you!$"

Route40_Text_MonicaGaveGift:
	.string "MONICA{SE_M_HEAT_WAVE}It'{SE_M_GRASSWHISTLE}a{SE_M_ATTRACT}ite{SE_M_MILK_DRINK}tha{SE_M_SPIT_UP}raises\n"
	.string "th{SE_M_REVERSAL}powe{SE_M_SAND_TOMB}o{SE_M_ACID_ARMOR}FLYING-typ{SE_M_REVERSAL}moves.\p"
	.string "Yo{SE_M_DIVE}shoul{SE_M_WATERFALL}equi{SE_M_MORNING_SUN}{SE_M_CHARGE}bird\n"
	.string "POKéMO{SE_M_PSYBEAM2}wit{SE_M_TRI_ATTACK}tha{SE_M_SPIT_UP}item.$"

Route40_Text_MonicaMonday:
	.string "MONICA{SE_M_HEAT_WAVE}M{SE_M_YAWN}brother{SE_M_GRASSWHISTLE}and\n"
	.string "sister{SE_M_GRASSWHISTLE}ar{SE_M_REVERSAL}al{SE_M_BATON_PASS}ove{SE_M_SAND_TOMB}th{SE_M_REVERSAL}place.\p"
	.string "Se{SE_M_REVERSAL}i{SE_M_ACID_ARMOR}yo{SE_M_DIVE}coul{SE_M_WATERFALL}find\n"
	.string "the{SE_M_MILK_DRINK}all!$"

Route40_Text_MonicaNotMonday:
	.string "MONICA{SE_M_HEAT_WAVE}{SE_M_HEAL_BELL}don'{SE_M_SPIT_UP}thin{SE_M_ENCORE2}today\n"
	.string "i{SE_M_GRASSWHISTLE}Monday{SE_M_PERISH_SONG}Ho{SE_M_TWISTER}sad…$"

Route40_Text_MonicaNope:
	.string "No{SE_M_SPIT_UP}tha{SE_M_SPIT_UP}one.$"

Rotue40_EventScript_Monica::
	lock
	faceplayer
	goto_if_set JOHTO_FLAG_GOT_SHARP_BEAK, Rotue40_EventScript_MonicaCompleted
	msgbox Route40_Text_Monica, MSGBOX_DEFAULT
	closemessage
	multichoice 20, 0, MULTI_DAYS_OF_WEEK, FALSE
	switch VAR_RESULT
	case 0, Rotue40_EventScript_MonicaNope
	case 1, Rotue40_EventScript_MonicaYes
	case 2, Rotue40_EventScript_MonicaNope
	case 3, Rotue40_EventScript_MonicaNope
	case 4, Rotue40_EventScript_MonicaNope
	case 5, Rotue40_EventScript_MonicaNope
	case 6, Rotue40_EventScript_MonicaNope
	case 7 Rotue40_EventScript_MonicaCancel
	case MULTI_B_PRESSED, Rotue40_EventScript_MonicaCancel
	closemessage
	release
	end

Rotue40_EventScript_MonicaYes::
	msgbox Route40_Text_MonicaGivesGift, MSGBOX_DEFAULT
	giveitem ITEM_SHARP_BEAK
	goto_if_eq VAR_RESULT, FALSE, J_Common_EventScript_ShowBagIsFull
	setflag JOHTO_FLAG_GOT_SHARP_BEAK
	msgbox Route40_Text_MonicaGaveGift, MSGBOX_DEFAULT
	closemessage
	release
	end

Rotue40_EventScript_MonicaNope::
	msgbox Route40_Text_MonicaNope, MSGBOX_DEFAULT
	closemessage
	release
	end

Rotue40_EventScript_MonicaCancel::
	closemessage
	release
	end

Rotue40_EventScript_MonicaCompleted::
	msgbox Route40_Text_MonicaMonday, MSGBOX_DEFAULT
	closemessage
	release
	end

