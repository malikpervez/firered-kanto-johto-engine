@ Johto (data/maps/EcruteakCity_hns/scripts.inc), as built into the FireRed game.

EcruteakCity_hns_MapScripts::
	map_script 3, EcruteakCity_OnTransition
	map_script 5, J_SetTimeEncounters
	.byte 0

EcruteakCity_OnTransition::
	call RB_EcruteakVisibility
	callnative SetTimeBasedEncounters
	call CG_SilverEcruteakVisibility
	end

EcruteakCity_Test_Lugia::
	setvar 20577, 1
	end

EcruteakCity_Test_League::
	setvar 20558, 4
	setvar 20559, 4
	end

EcruteakCity_EventScript_Trigger::

	clearflag 8664
	clearflag 8661
	clearflag 8308
	clearflag 8759
	clearflag 8764
	clearflag 8760
	clearflag 8765
	clearflag 8313
	clearflag 8316
	clearflag 8238
	clearflag 8315
	clearflag 8309
	clearflag 8766
	clearflag 8767
	clearflag 8718
	clearflag 8244
	clearflag 8709
	clearflag 8665
	clearflag 8775
	clearflag 8311
	clearflag 8312
	clearflag 8317
	clearflag 8245
	clearflag 8254
	clearflag 8253

	setflag 10485
	setflag 8366

	setflag 8318
	setflag 8356
	setflag 8310
	setflag 8365
	setflag 8314
	setvar 20558, 0
	setvar 20559, 0
	setvar 20562, 0
	setvar 20561, 1
	end

EcruteakCity_Trigger_Silver::
	lockall
	opendoor 39, 40
	waitdooranim
	delay 10
	clearflag 8314
	addobject 33
	playbgm ((558 + 1) + 0x3B), FALSE
	playse 20
	applymovement 33, EcruteakCity_Movement_Silver1
	applymovement 255, EcruteakCity_Movement_Silver1
	message EcruteakCity_Text_Silver1

	waitmovement 255
	waitmovement 33
	turnobject 255, DIR_NORTH
	closedoor 39, 40
	waitdooranim
	msgbox EcruteakCity_Text_Silver2, MSGBOX_DEFAULT
	closemessage
	playse 21
	applymovement 33, J_Common_Movement_ExclamationMark
	delay 55
	waitmovement 33
	turnobject 33, DIR_SOUTH
	msgbox EcruteakCity_Text_Silver3, MSGBOX_DEFAULT
	closemessage

	applymovement 33, EcruteakCity_Movement_Silver2
	waitmovement 33


	setflag 8314
	removeobject 33
	fadedefaultbgm

	setvar 20562, 5
	releaseall
	end

EcruteakCity_Movement_Silver1:
	delay_16
	lock_facing_direction
	walk_down
	unlock_facing_direction
	step_end

EcruteakCity_Movement_Silver2:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

EcruteakCity_Text_Silver1:
	.string "THUD!!$"

EcruteakCity_Text_Silver2:
	.string "{RIVAL}{SE_M_HEAT_WAVE}How...{SE_M_SING}Ho{SE_M_TWISTER}i{SE_M_GRASSWHISTLE}this\n"
	.string "possible{SE_M_SING}Ho{SE_M_TWISTER}ca{SE_M_ATTRACT}{SE_M_HEAL_BELL}los{SE_M_REVERSAL}t{SE_M_ATTRACT2}mere\l"
	.string "KIMON{SE_M_SOLAR_BEAM}GIRLS...?$"

EcruteakCity_Text_Silver3:
	.string "{RIVAL}{SE_M_HEAT_WAVE}Yo{SE_M_DIVE}wer{SE_M_REVERSAL}watchin{SE_M_SANDSTORM}me,\n"
	.string "{PLAYER}...\p"
	.string "Yeah{SE_M_SUPERSONIC}that'{SE_M_GRASSWHISTLE}right!\p"
	.string "{SE_M_HEAL_BELL}neve{SE_M_SAND_TOMB}though{SE_M_SPIT_UP}defeatin{SE_M_SANDSTORM}five\n"
	.string "KIMON{SE_M_SOLAR_BEAM}GIRL{SE_M_SKETCH}woul{SE_M_WATERFALL}b{SE_M_REVERSAL}s{SE_M_ATTRACT2}hard...\p"
	.string "{SE_M_HEAL_BELL}go{SE_M_SPIT_UP}beate{SE_M_ATTRACT}t{SE_M_ATTRACT2}{SE_M_CHARGE}pulp...\p"
	.string "...\p"
	.string "Yo{SE_M_DIVE}mus{SE_M_SPIT_UP}hav{SE_M_REVERSAL}com{SE_M_REVERSAL}her{SE_M_REVERSAL}fo{SE_M_SAND_TOMB}the\n"
	.string "sam{SE_M_REVERSAL}reason{SE_M_SUPERSONIC}right?\p"
	.string "Don'{SE_M_SPIT_UP}ge{SE_M_SPIT_UP}cock{SE_M_YAWN}jus{SE_M_SPIT_UP}becaus{SE_M_REVERSAL}you\n"
	.string "defeate{SE_M_WATERFALL}TEA{SE_M_GIGA_DRAIN}ROCKET!\p"
	.string "Thes{SE_M_REVERSAL}KIMON{SE_M_SOLAR_BEAM}GIRL{SE_M_SKETCH}ar{SE_M_REVERSAL}insanely\n"
	.string "strong.\p"
	.string "Se{SE_M_REVERSAL}i{SE_M_ACID_ARMOR}yo{SE_M_DIVE}ca{SE_M_ATTRACT}defea{SE_M_SPIT_UP}them.\p"
	.string "Bu{SE_M_SPIT_UP}I'{SE_M_MILK_DRINK}no{SE_M_SPIT_UP}goin{SE_M_SANDSTORM}back{SE_M_SUPERSONIC}{SE_M_HEAL_BELL}don't\n"
	.string "wan{SE_M_SPIT_UP}t{SE_M_ATTRACT2}se{SE_M_REVERSAL}yo{SE_M_DIVE}win.$"

EcruteakCity_EventScript_Gramps::
	lock
	faceplayer
	msgbox EcruteakCity_Text_Gramps1, MSGBOX_DEFAULT
	closemessage
	release
	end

EcruteakCity_EventScript_Lass::
	lock
	faceplayer
	msgbox EcruteakCity_Text_Lass1, MSGBOX_DEFAULT
	closemessage
	release
	end

EcruteakCity_EventScript_Girl::
	lock
	faceplayer
	goto_if_set 8664, EcruteakCity_EventScript_Girl2
	msgbox EcruteakCity_Text_Lass2, MSGBOX_DEFAULT
	closemessage
	release
	end

EcruteakCity_EventScript_Girl2::
	msgbox EcruteakCity_Text_Lass2_ReleasedBeasts, MSGBOX_DEFAULT
	closemessage
	release
	end

EcruteakCity_EventScrip_Man::
	lock
	faceplayer
	goto_if_set 8661, EcruteakCity_EventScrip_Man2
	msgbox EcruteakCity_Text_Fisher, MSGBOX_DEFAULT
	closemessage
	release
	end

EcruteakCity_EventScrip_Man2::
	msgbox EcruteakCity_Text_Fisher_JasmineReturned, MSGBOX_DEFAULT
	closemessage
	release
	end

EcruteakCity_EventScript_Youngster::
	lock
	faceplayer
	msgbox EcruteakCity_Text_Youngster, MSGBOX_DEFAULT
	closemessage
	release
	end

EcruteakCity_EventScript_SageRight::
	lock
	faceplayer
	msgbox EcruteakCity_Text_Gramps2, MSGBOX_DEFAULT
	closemessage
	release
	end

EcruteakCity_EventScript_SageTower::
	lock
	faceplayer
	msgbox EcruteakCity_Text_Gramps3, MSGBOX_DEFAULT
	closemessage
	release
	end

EcruteakCity_EventScript_SageGym::
	lock
	faceplayer
	msgbox EcruteakCity_Text_SageGym, MSGBOX_DEFAULT
	closemessage
	release
	end

EcruteakCity_EventScript_TheaterSign::
	lock
	msgbox EcruteakCity_Text_DanceTheaterSign, MSGBOX_SIGN
	closemessage
	release
	end

EcruteakCity_EventScript_OfficeSign::
	lock
	msgbox EcruteakCity_Text_OfficeSign, MSGBOX_SIGN
	closemessage
	release
	end

EcruteakCity_EventScript_BurnedSign::
	lock
	msgbox EcruteakCity_Text_BurnedTowerSign, MSGBOX_SIGN
	closemessage
	release
	end

EcruteakCity_EventScript_CitySign::
	lock
	msgbox EcruteakCity_Text_Sign, MSGBOX_SIGN
	closemessage
	release
	end

EcruteakCity_EventScript_GymSign::
	lock
	msgbox EcruteakCity_Text_GymSign, MSGBOX_SIGN
	closemessage
	release
	end

EcruteakCity_EventScript_Eevee::
	lock
	faceplayer
	waitse
	playmoncry 133, 0
	msgbox EcruteakCity_Text_Eevee, MSGBOX_DEFAULT
	waitmoncry
	release
	end

EcruteakCity_EventScript_Vulpix::
	lock
	faceplayer
	waitse
	playmoncry 37, 0
	msgbox EcruteakCity_Text_Vulpix, MSGBOX_DEFAULT
	waitmoncry
	release
	end

EcruteakCity_EventScript_Item_RareCandy::
	finditem ITEM_RARE_CANDY
	end

EcruteakCity_Text_Eevee:
	.string "EEVEE{SE_M_HEAT_WAVE}Veee!$"

EcruteakCity_Text_Vulpix:
	.string "VULPIX{SE_M_HEAT_WAVE}Vulll{SE_M_BATON_PASS}Pix!$"

EcruteakCity_Text_UnusedMissingDaughter:
	.string "Oh{SE_M_SUPERSONIC}no{SE_M_PERISH_SONG}Oh{SE_M_SUPERSONIC}no…\p"
	.string "M{SE_M_YAWN}daughte{SE_M_SAND_TOMB}i{SE_M_GRASSWHISTLE}missing.\p"
	.string "No{SE_M_DIZZY_PUNCH}Sh{SE_M_REVERSAL}couldn'{SE_M_SPIT_UP}hav{SE_M_REVERSAL}gon{SE_M_REVERSAL}t{SE_M_ATTRACT2}the\n"
	.string "BURNE{SE_M_FAINT_ATTACK}TOWER.\p"
	.string "{SE_M_HEAL_BELL}tol{SE_M_WATERFALL}he{SE_M_SAND_TOMB}no{SE_M_SPIT_UP}t{SE_M_ATTRACT2}g{SE_M_ATTRACT2}nea{SE_M_SAND_TOMB}it…\p"
	.string "Peopl{SE_M_REVERSAL}see{SE_M_MILK_DRINK}t{SE_M_ATTRACT2}disappea{SE_M_SAND_TOMB}there…\p"
	.string "Oh{SE_M_SUPERSONIC}wha{SE_M_SPIT_UP}shoul{SE_M_WATERFALL}{SE_M_HEAL_BELL}do…?$"

EcruteakCity_Text_Gramps1:
	.string "ECRUTEA{SE_M_SNORE}use{SE_M_WATERFALL}t{SE_M_ATTRACT2}hav{SE_M_REVERSAL}tw{SE_M_ATTRACT2}towers:\n"
	.string "on{SE_M_REVERSAL}eac{SE_M_TRI_ATTACK}i{SE_M_ATTRACT}th{SE_M_REVERSAL}eas{SE_M_SPIT_UP}an{SE_M_WATERFALL}west.$"

EcruteakCity_Text_Gramps2:
	.string "Ah{SE_M_SUPERSONIC}child{SE_M_PERISH_SONG}Hav{SE_M_REVERSAL}yo{SE_M_DIVE}learne{SE_M_WATERFALL}to\n"
	.string "danc{SE_M_REVERSAL}lik{SE_M_REVERSAL}th{SE_M_REVERSAL}KIMON{SE_M_SOLAR_BEAM}GIRLS?\p"
	.string "I{SE_M_ACID_ARMOR}yo{SE_M_DIVE}g{SE_M_ATTRACT2}t{SE_M_ATTRACT2}thei{SE_M_SAND_TOMB}DANC{SE_M_SWORDS_DANCE}THEATER,\n"
	.string "a{SE_M_ATTRACT}od{SE_M_WATERFALL}ol{SE_M_WATERFALL}ma{SE_M_ATTRACT}wil{SE_M_BATON_PASS}giv{SE_M_REVERSAL}you\l"
	.string "somethin{SE_M_SANDSTORM}nice{SE_M_SUPERSONIC}{SE_M_HEAL_BELL}hear.$"

EcruteakCity_Text_Lass1:
	.string "I'{SE_M_MILK_DRINK}goin{SE_M_SANDSTORM}t{SE_M_ATTRACT2}practic{SE_M_REVERSAL}a{SE_M_SPIT_UP}th{SE_M_REVERSAL}DANCE\n"
	.string "THEATER{SE_M_PERISH_SONG}Car{SE_M_REVERSAL}t{SE_M_ATTRACT2}joi{SE_M_ATTRACT}me?$"

EcruteakCity_Text_Lass2:
	.string "Th{SE_M_REVERSAL}towe{SE_M_SAND_TOMB}tha{SE_M_SPIT_UP}use{SE_M_WATERFALL}t{SE_M_ATTRACT2}b{SE_M_REVERSAL}here…\p"
	.string "M{SE_M_YAWN}grandm{SE_M_CHARGE}tol{SE_M_WATERFALL}m{SE_M_REVERSAL}i{SE_M_SPIT_UP}use{SE_M_WATERFALL}t{SE_M_ATTRACT2}be\n"
	.string "muc{SE_M_TRI_ATTACK}taller.\p"
	.string "{SE_M_HEAL_BELL}hea{SE_M_SAND_TOMB}ther{SE_M_REVERSAL}ar{SE_M_REVERSAL}ghost{SE_M_GRASSWHISTLE}i{SE_M_ATTRACT}i{SE_M_SPIT_UP}now.$"

EcruteakCity_Text_Lass2_ReleasedBeasts:
	.string "Thre{SE_M_REVERSAL}bi{SE_M_SANDSTORM}POKéMO{SE_M_PSYBEAM2}ra{SE_M_ATTRACT}of{SE_M_ACID_ARMOR}i{SE_M_ATTRACT}different\n"
	.string "directions{SE_M_PERISH_SONG}Wha{SE_M_SPIT_UP}wer{SE_M_REVERSAL}they?$"

EcruteakCity_Text_Fisher:
	.string "{SE_M_HEAL_BELL}hear{SE_M_WATERFALL}{SE_M_CHARGE}rumo{SE_M_SAND_TOMB}abou{SE_M_SPIT_UP}OLIVINE\n"
	.string "LIGHTHOUSE.\p"
	.string "Th{SE_M_REVERSAL}POKéMO{SE_M_PSYBEAM2}tha{SE_M_SPIT_UP}serve{SE_M_GRASSWHISTLE}a{SE_M_GRASSWHISTLE}the\n"
	.string "beaco{SE_M_ATTRACT}fel{SE_M_BATON_PASS}ill{SE_M_PERISH_SONG}Sound{SE_M_GRASSWHISTLE}lik{SE_M_REVERSAL}they\l"
	.string "ar{SE_M_REVERSAL}i{SE_M_ATTRACT}trouble.$"

EcruteakCity_Text_Fisher_JasmineReturned:
	.string "Th{SE_M_REVERSAL}POKéMO{SE_M_PSYBEAM2}a{SE_M_SPIT_UP}OLIVIN{SE_M_SWORDS_DANCE}LIGHTHOUSE\n"
	.string "ha{SE_M_GRASSWHISTLE}bee{SE_M_ATTRACT}cured.\p"
	.string "Boat{SE_M_GRASSWHISTLE}ca{SE_M_ATTRACT}safel{SE_M_YAWN}sai{SE_M_BATON_PASS}ou{SE_M_SPIT_UP}t{SE_M_ATTRACT2}se{SE_M_CHARGE}at\n"
	.string "nigh{SE_M_SPIT_UP}again.$"

EcruteakCity_Text_Youngster:
	.string "{SE_M_HEAL_BELL}hea{SE_M_SAND_TOMB}POKéMO{SE_M_PSYBEAM2}ar{SE_M_REVERSAL}rampagin{SE_M_SANDSTORM}a{SE_M_SPIT_UP}the\n"
	.string "LAK{SE_M_SWORDS_DANCE}O{SE_M_LEER}RAGE{SE_M_PERISH_SONG}I'{SE_M_WATERFALL}lik{SE_M_REVERSAL}t{SE_M_ATTRACT2}se{SE_M_REVERSAL}that.$"

EcruteakCity_Text_Gramps3:
	.string "I{SE_M_ATTRACT}th{SE_M_REVERSAL}distan{SE_M_SPIT_UP}past…\p"
	.string "Thi{SE_M_GRASSWHISTLE}towe{SE_M_SAND_TOMB}burne{SE_M_WATERFALL}i{SE_M_ATTRACT}{SE_M_CHARGE}fire{SE_M_PERISH_SONG}Three\n"
	.string "nameles{SE_M_GRASSWHISTLE}POKéMO{SE_M_PSYBEAM2}perishe{SE_M_WATERFALL}i{SE_M_ATTRACT}it.\p"
	.string "{SE_M_BONEMERANG}rainbow-colore{SE_M_WATERFALL}POKéMO{SE_M_PSYBEAM2}descended\n"
	.string "fro{SE_M_MILK_DRINK}th{SE_M_REVERSAL}sk{SE_M_YAWN}an{SE_M_WATERFALL}resurrecte{SE_M_WATERFALL}them…\p"
	.string "It'{SE_M_GRASSWHISTLE}{SE_M_CHARGE}legen{SE_M_WATERFALL}tha{SE_M_SPIT_UP}ha{SE_M_GRASSWHISTLE}bee{SE_M_ATTRACT}passed\n"
	.string "dow{SE_M_ATTRACT}b{SE_M_YAWN}ECRUTEA{SE_M_SNORE}GY{SE_M_GIGA_DRAIN}LEADERS.\p"
	.string "Me?\p"
	.string "{SE_M_HEAL_BELL}wa{SE_M_GRASSWHISTLE}{SE_M_CHARGE}traine{SE_M_SAND_TOMB}wa{SE_M_YAWN}bac{SE_M_ENCORE2}when.\n"
	.string "Hohoho!$"

EcruteakCity_Text_SageGym:
	.string "Gy{SE_M_MILK_DRINK}Leade{SE_M_SAND_TOMB}MORT{SE_M_MOONLIGHT}i{SE_M_GRASSWHISTLE}no{SE_M_SPIT_UP}her{SE_M_REVERSAL}right\n"
	.string "now{SE_M_PERISH_SONG}Yo{SE_M_DIVE}ma{SE_M_YAWN}fin{SE_M_WATERFALL}hi{SE_M_MILK_DRINK}a{SE_M_SPIT_UP}the\l"
	.string "BURNE{SE_M_FAINT_ATTACK}TOWER.$"

EcruteakCity_Text_Sign:
	.string "ECRUTEA{SE_M_SNORE}CITY\n"
	.string "{SE_M_BONEMERANG}Historica{SE_M_BATON_PASS}City\p"
	.string "Wher{SE_M_REVERSAL}th{SE_M_REVERSAL}Pas{SE_M_SPIT_UP}Meet{SE_M_GRASSWHISTLE}th{SE_M_REVERSAL}Present$"

EcruteakCity_Text_TinTowerSign:
	.string "TI{SE_M_PSYBEAM2}TOWER\p"
	.string "{SE_M_BONEMERANG}legendar{SE_M_YAWN}POKéMO{SE_M_PSYBEAM2}i{SE_M_GRASSWHISTLE}sai{SE_M_WATERFALL}to\n"
	.string "roos{SE_M_SPIT_UP}here.$"

EcruteakCity_Text_OfficeSign:
	.string "Barrie{SE_M_SAND_TOMB}Statio{SE_M_ATTRACT}t{SE_M_ATTRACT2}TI{SE_M_PSYBEAM2}TOWER\p"
	.string "N{SE_M_ATTRACT2}Trespassin{SE_M_SANDSTORM}b{SE_M_YAWN}th{SE_M_REVERSAL}Unworthy.$"

EcruteakCity_Text_GymSign:
	.string "ECRUTEA{SE_M_SNORE}CIT{SE_M_MOONLIGHT}POKéMO{SE_M_PSYBEAM2}GYM\n"
	.string "LEADER{SE_M_HEAT_WAVE}MORTY\p"
	.string "Th{SE_M_REVERSAL}Mysti{SE_M_HYPER_BEAM}See{SE_M_SAND_TOMB}o{SE_M_ACID_ARMOR}th{SE_M_REVERSAL}Future$"

EcruteakCity_Text_DanceTheaterSign:
	.string "ECRUTEA{SE_M_SNORE}DANC{SE_M_SWORDS_DANCE}THEATER$"

EcruteakCity_Text_BurnedTowerSign:
	.string "BURNE{SE_M_FAINT_ATTACK}TOWER\p"
	.string "I{SE_M_SPIT_UP}wa{SE_M_GRASSWHISTLE}destroye{SE_M_WATERFALL}b{SE_M_YAWN}{SE_M_CHARGE}mysterious\n"
	.string "fire.\p"
	.string "Pleas{SE_M_REVERSAL}sta{SE_M_YAWN}away{SE_M_SUPERSONIC}a{SE_M_GRASSWHISTLE}i{SE_M_SPIT_UP}i{SE_M_GRASSWHISTLE}unsafe.$"

