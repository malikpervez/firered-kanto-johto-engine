@ Johto (data/maps/EcruteakCity_SageOffice1_hns/scripts.inc), as built into the FireRed game.

EcruteakCity_SageOffice1_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, EcruteakCity_SageOffice1_OnTransition
	.byte 0

EcruteakCity_SageOffice1_OnTransition::
	goto_if_set JOHTO_FLAG_HIDE_TINTOWER_GUARD, EcruteakCity_SageOffice1_EventScript_SageAside
	end

EcruteakCity_SageOffice1_EventScript_SageAside::
	setobjectxyperm LOCALID_SAGEOFFICE_SAGE, 15, 2
	end

EcruteakCity_SageOffice1_EventScript_Sign::
	msgbox EcruteakCity_SageOffice1_Text_Sign, MSGBOX_SIGN
	end

EcruteakCity_SageOffice1_Text_Sign:
	.string "Th{SE_M_REVERSAL}bel{SE_M_BATON_PASS}o{SE_M_ACID_ARMOR}ti{SE_M_ATTRACT}ring{SE_M_GRASSWHISTLE}clearl{SE_M_YAWN}for\n"
	.string "thos{SE_M_REVERSAL}unde{SE_M_SAND_TOMB}th{SE_M_REVERSAL}tower'{SE_M_GRASSWHISTLE}wing.$"

EcruteakCity_SageOffice2_EventScript_SageA::
	lock
	faceplayer
	goto_if_set JOHTO_FLAG_HIDE_TINTOWER_GUARD, EcruteakCity_SageOffice2_EventScript_SageA4
	checkitem ITEM_CLEAR_BELL
	goto_if_eq VAR_RESULT, TRUE, EcruteakCity_SageOffice2_EventScript_SageA2
	msgbox EcruteakTinTowerEntrance_Text_SageNoBadge, MSGBOX_DEFAULT
	closemessage
	release
	end

EcruteakCity_SageOffice2_EventScript_SageA2::
	msgbox EcruteakTinTowerEntrance_Text_SageHearsClearBell1, MSGBOX_DEFAULT
	waitmessage
	playse SE_M_PETAL_DANCE
	waitse
	playse SE_PIN
	applymovement LOCALID_SAGEOFFICE_SAGE, J_Common_Movement_ExclamationMark
	delay 55
	waitmovement LOCALID_SAGEOFFICE_SAGE
	msgbox EcruteakTinTowerEntrance_Text_SageHearsClearBell2, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SAGEOFFICE_SAGE, EcruteakCity_SageOffice2_Movement_StandAside
	waitmovement 0
	setobjectxyperm LOCALID_SAGEOFFICE_SAGE, 15, 2
	setflag JOHTO_FLAG_HIDE_TINTOWER_GUARD
	release
	end

EcruteakCity_SageOffice2_EventScript_SageA3::
	msgbox EcruteakTinTowerEntrance_Text_SagePleaseDoGoOn, MSGBOX_DEFAULT
	closemessage
	release
	end

EcruteakCity_SageOffice2_EventScript_SageA4::
	msgbox EcruteakTinTowerEntrance_Text_SageDone, MSGBOX_DEFAULT
	closemessage
	release
	end

EcruteakCity_SageOffice2_EventScript_SageB::
	lock
	faceplayer
	goto_if_eq JOHTO_VAR_ECRUTEAK_CITY_STATE, 10, EcruteakCity_SageOffice2_EventScript_B2
	goto_if_eq JOHTO_VAR_ECRUTEAK_CITY_STATE, 11, EcruteakCity_SageOffice2_EventScript_B2
	msgbox EcruteakTinTowerEntrance_Text_WanderingSage, MSGBOX_DEFAULT
	closemessage
	release
	end

EcruteakCity_SageOffice2_EventScript_B2::
	msgbox EcruteakTinTowerEntrance_Text_WanderingSageClearBell, MSGBOX_DEFAULT
	closemessage
	release
	end

EcruteakCity_SageOffice2_EventScript_SageC::
	lock
	faceplayer
	msgbox EcruteakTinTowerEntrance_Text_Gramps, MSGBOX_DEFAULT
	closemessage
	release
	end

EcruteakCity_SageOffice2_Movement_StandAside:
	walk_left
	face_down
	step_end

EcruteakTinTowerEntrance_Text_SageNoBadge:
	.string "TI{SE_M_PSYBEAM2}TOWE{SE_M_MINIMIZE}i{SE_M_GRASSWHISTLE}of{SE_M_ACID_ARMOR}limit{SE_M_GRASSWHISTLE}t{SE_M_ATTRACT2}the\n"
	.string "unworthy{SE_M_PERISH_SONG}Sorr{SE_M_YAWN}bu{SE_M_SPIT_UP}you'l{SE_M_BATON_PASS}have\l"
	.string "t{SE_M_ATTRACT2}leave.$"

EcruteakTinTowerEntrance_Text_SageWithBadge:
	.string "TI{SE_M_PSYBEAM2}TOWE{SE_M_MINIMIZE}i{SE_M_GRASSWHISTLE}of{SE_M_ACID_ARMOR}limit{SE_M_GRASSWHISTLE}t{SE_M_ATTRACT2}anyone\n"
	.string "withou{SE_M_SPIT_UP}ECRUTEA{SE_M_SNORE}GYM'{SE_M_GRASSWHISTLE}BADGE.\p"
	.string "Ah!\p"
	.string "ECRUTEAK'{SE_M_GRASSWHISTLE}GY{SE_M_GIGA_DRAIN}BADGE{SE_M_DRAGON_RAGE}Please{SE_M_SUPERSONIC}go\n"
	.string "righ{SE_M_SPIT_UP}through.$"

EcruteakTinTowerEntrance_Text_SageNoClearBell:
	.string "{SE_M_BONEMERANG}momentou{SE_M_GRASSWHISTLE}even{SE_M_SPIT_UP}ha{SE_M_GRASSWHISTLE}occurred.\p"
	.string "{SE_M_HEAL_BELL}be{SE_M_SANDSTORM}you{SE_M_SAND_TOMB}pardon{SE_M_SUPERSONIC}bu{SE_M_SPIT_UP}{SE_M_HEAL_BELL}mus{SE_M_SPIT_UP}ask\n"
	.string "yo{SE_M_DIVE}t{SE_M_ATTRACT2}leave.\p"
	.string "…Wha{SE_M_SPIT_UP}soothe{SE_M_GRASSWHISTLE}th{SE_M_REVERSAL}soul…\p"
	.string "Th{SE_M_REVERSAL}WIS{SE_M_SWORDS_DANCE}TRI{SE_M_SOLAR_BEAM}sa{SE_M_YAWN}thing{SE_M_GRASSWHISTLE}tha{SE_M_SPIT_UP}are\n"
	.string "s{SE_M_ATTRACT2}ver{SE_M_YAWN}difficul{SE_M_SPIT_UP}t{SE_M_ATTRACT2}understand…$"

EcruteakTinTowerEntrance_Text_SageHearsClearBell1:
	.string "{SE_M_BONEMERANG}momentou{SE_M_GRASSWHISTLE}even{SE_M_SPIT_UP}ha{SE_M_GRASSWHISTLE}occurred.\p"
	.string "{SE_M_HEAL_BELL}be{SE_M_SANDSTORM}you{SE_M_SAND_TOMB}pardon{SE_M_SUPERSONIC}bu{SE_M_SPIT_UP}{SE_M_HEAL_BELL}mus{SE_M_SPIT_UP}ask\n"
	.string "yo{SE_M_DIVE}t{SE_M_ATTRACT2}leave.\p"
	.string "..............................$"

EcruteakTinTowerEntrance_Text_SageHearsClearBell2:
	.string "Ah!\p"
	.string "Th{SE_M_REVERSAL}soun{SE_M_WATERFALL}o{SE_M_ACID_ARMOR}tha{SE_M_SPIT_UP}CLEA{SE_M_MINIMIZE}BELL!\p"
	.string "It{SE_M_DIZZY_PUNCH}It'{SE_M_GRASSWHISTLE}sublime!\p"
	.string "I'v{SE_M_REVERSAL}neve{SE_M_SAND_TOMB}hear{SE_M_WATERFALL}s{SE_M_ATTRACT2}beautifu{SE_M_BATON_PASS}a\n"
	.string "soun{SE_M_WATERFALL}before!\p"
	.string "Tha{SE_M_SPIT_UP}bell'{SE_M_GRASSWHISTLE}chim{SE_M_REVERSAL}i{SE_M_GRASSWHISTLE}indicativ{SE_M_REVERSAL}of\n"
	.string "th{SE_M_REVERSAL}bearer'{SE_M_GRASSWHISTLE}soul.\p"
	.string "You…\p"
	.string "Yo{SE_M_DIVE}ma{SE_M_YAWN}b{SE_M_REVERSAL}abl{SE_M_REVERSAL}t{SE_M_ATTRACT2}mak{SE_M_REVERSAL}i{SE_M_SPIT_UP}through\n"
	.string "TI{SE_M_PSYBEAM2}TOWER.\p"
	.string "Please{SE_M_SUPERSONIC}d{SE_M_ATTRACT2}g{SE_M_ATTRACT2}on.$"

EcruteakTinTowerEntrance_Text_SagePleaseDoGoOn:
	.string "Please{SE_M_SUPERSONIC}d{SE_M_ATTRACT2}g{SE_M_ATTRACT2}on.$"

EcruteakTinTowerEntrance_Text_SageDone:
	.string "Tha{SE_M_SPIT_UP}bell'{SE_M_GRASSWHISTLE}chim{SE_M_REVERSAL}i{SE_M_GRASSWHISTLE}indicativ{SE_M_REVERSAL}of\n"
	.string "th{SE_M_REVERSAL}bearer'{SE_M_GRASSWHISTLE}soul.\p"
	.string "You…\n"
	.string "Trul{SE_M_YAWN}ar{SE_M_REVERSAL}worthy.$"

EcruteakTinTowerEntrance_Text_WanderingSage:
	.string "Th{SE_M_REVERSAL}TI{SE_M_PSYBEAM2}TOWE{SE_M_MINIMIZE}ahea{SE_M_WATERFALL}i{SE_M_GRASSWHISTLE}{SE_M_CHARGE}nine-\n"
	.string "tie{SE_M_SAND_TOMB}towe{SE_M_SAND_TOMB}o{SE_M_ACID_ARMOR}divin{SE_M_REVERSAL}beauty.\p"
	.string "I{SE_M_SPIT_UP}soothe{SE_M_GRASSWHISTLE}th{SE_M_REVERSAL}sou{SE_M_BATON_PASS}o{SE_M_ACID_ARMOR}al{SE_M_BATON_PASS}who\n"
	.string "se{SE_M_REVERSAL}it.$"

EcruteakTinTowerEntrance_Text_WanderingSageClearBell:
	.string "Th{SE_M_REVERSAL}TI{SE_M_PSYBEAM2}TOWE{SE_M_MINIMIZE}shook{SE_M_DRAGON_RAGE}{SE_M_BONEMERANG}POKéMO{SE_M_PSYBEAM2}must\n"
	.string "hav{SE_M_REVERSAL}returne{SE_M_WATERFALL}t{SE_M_ATTRACT2}th{SE_M_REVERSAL}top!$"

EcruteakTinTowerEntrance_Text_Gramps:
	.string "Tw{SE_M_ATTRACT2}towers{SE_M_DIZZY_PUNCH}Tw{SE_M_ATTRACT2}POKéMON…\p"
	.string "Bu{SE_M_SPIT_UP}whe{SE_M_ATTRACT}on{SE_M_REVERSAL}burne{SE_M_WATERFALL}down{SE_M_SUPERSONIC}both\n"
	.string "POKéMO{SE_M_PSYBEAM2}fle{SE_M_TWISTER}away{SE_M_SUPERSONIC}neve{SE_M_SAND_TOMB}t{SE_M_ATTRACT2}return.$"

