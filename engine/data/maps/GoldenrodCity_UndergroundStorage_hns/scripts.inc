@ Johto (data/maps/GoldenrodCity_UndergroundStorage_hns/scripts.inc), as built into the FireRed game.

GoldenrodCity_UndergroundStorage_hns_MapScripts::
	.byte 0

GoldenrodCity_UndergroundStorage_EventScript_Director::
	lock
	faceplayer
	checkitem ITEM_CARD_KEY
	goto_if_eq 32781, TRUE, GoldenrodCity_UndergroundStorage_EventScript_Director2
	msgbox RadioTowerBasement_Text_DirectorIntro, MSGBOX_DEFAULT
	closemessage
	giveitem ITEM_CARD_KEY
	msgbox RadioTowerBasement_Text_DirectorCardKey, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_UndergroundStorage_EventScript_Director2::
	msgbox RadioTowerBasement_Text_DirectorAfter, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_UndergroundStorage_EventScript_Grunt19::
	trainerbattle_single 1161, RadioTowerBasement_Text_GruntM24Seen, RadioTowerBasement_Text_GruntM24Beaten
	msgbox RadioTowerBasement_Text_GruntM24After, MSGBOX_AUTOCLOSE
	end

GoldenrodCity_UndergroundStorage_EventScript_Grunt12::
	trainerbattle_single 1154, RadioTowerBasement_Text_GruntM14Seen, RadioTowerBasement_Text_GruntM14Beaten
	msgbox RadioTowerBasement_Text_GruntM14After, MSGBOX_AUTOCLOSE
	end

GoldenrodCity_UndergroundStorage_EventScript_Eto::
	trainerbattle_single 1178, RadioTowerBasement_Text_GruntM15Seen, RadioTowerBasement_Text_GruntM15Beaten
	msgbox RadioTowerBasement_Text_GruntM15After, MSGBOX_AUTOCLOSE
	end

GoldenrodCity_UndergroundStorage_EventScript_Item_TM_CALM_MIND::
	finditem 585
	end

GoldenrodCity_UndergroundStorage_EventScript_Item_UltraBall::
	finditem ITEM_ULTRA_BALL
	end

GoldenrodCity_UndergroundStorage_EventScript_Item_MaxEther::
	finditem ITEM_MAX_ETHER
	end

RadioTowerBasement_Text_GruntM24Seen:
	.string "Ho{SE_M_TWISTER}di{SE_M_WATERFALL}yo{SE_M_DIVE}ge{SE_M_SPIT_UP}thi{SE_M_GRASSWHISTLE}far?\p"
	.string "{SE_M_HEAL_BELL}gues{SE_M_GRASSWHISTLE}i{SE_M_SPIT_UP}can'{SE_M_SPIT_UP}b{SE_M_REVERSAL}helped{SE_M_PERISH_SONG}I'll\n"
	.string "dispos{SE_M_REVERSAL}o{SE_M_ACID_ARMOR}you.$"

RadioTowerBasement_Text_GruntM24Beaten:
	.string "{SE_M_HEAL_BELL}go{SE_M_SPIT_UP}dispose{SE_M_WATERFALL}of…$"

RadioTowerBasement_Text_GruntM24After:
	.string "TEA{SE_M_GIGA_DRAIN}ROCKE{SE_M_SWIFT}wil{SE_M_BATON_PASS}kee{SE_M_MORNING_SUN}going{SE_M_SUPERSONIC}waiting\n"
	.string "fo{SE_M_SAND_TOMB}th{SE_M_REVERSAL}retur{SE_M_ATTRACT}o{SE_M_ACID_ARMOR}GIOVANNI.\p"
	.string "We'l{SE_M_BATON_PASS}d{SE_M_ATTRACT2}whateve{SE_M_SAND_TOMB}i{SE_M_SPIT_UP}takes.$"

RadioTowerBasement_Text_GruntM14Seen:
	.string "You'r{SE_M_REVERSAL}no{SE_M_SPIT_UP}goin{SE_M_SANDSTORM}an{SE_M_YAWN}farther!\p"
	.string "{SE_M_HEAL_BELL}don'{SE_M_SPIT_UP}sho{SE_M_TWISTER}merc{SE_M_YAWN}t{SE_M_ATTRACT2}m{SE_M_YAWN}enemies,\n"
	.string "no{SE_M_SPIT_UP}eve{SE_M_ATTRACT}brats!$"

RadioTowerBasement_Text_GruntM14Beaten:
	.string "Blas{SE_M_SPIT_UP}it!$"

RadioTowerBasement_Text_GruntM14After:
	.string "{SE_M_HEAL_BELL}lost…\p"
	.string "Pleas{SE_M_REVERSAL}forgiv{SE_M_REVERSAL}me{SE_M_SUPERSONIC}GIOVANNI!$"

RadioTowerBasement_Text_GruntM15Seen:
	.string "Hyuck-hyuck-hyuck{SE_M_DRAGON_RAGE}Loo{SE_M_ENCORE2}wh{SE_M_ATTRACT2}i{SE_M_SPIT_UP}is!\p"
	.string "Ready{SE_M_SING}I'{SE_M_MILK_DRINK}reall{SE_M_YAWN}toug{SE_M_TRI_ATTACK}now!$"

RadioTowerBasement_Text_GruntM15Beaten:
	.string "Hyuck-hyuck-hyuck{SE_M_DRAGON_RAGE}You'r{SE_M_REVERSAL}s{SE_M_ATTRACT2}good!\p"
	.string "Thi{SE_M_GRASSWHISTLE}TEA{SE_M_GIGA_DRAIN}ROCKE{SE_M_SWIFT}thin{SE_M_SANDSTORM}i{SE_M_GRASSWHISTLE}just\n"
	.string "{SE_M_CHARGE}job{SE_M_SUPERSONIC}bu{SE_M_SPIT_UP}{SE_M_HEAL_BELL}ca{SE_M_ATTRACT}se{SE_M_REVERSAL}i{SE_M_SPIT_UP}hurt{SE_M_GRASSWHISTLE}others.\p"
	.string "That'{SE_M_GRASSWHISTLE}it{SE_M_SUPERSONIC}I'{SE_M_MILK_DRINK}leaving.\p"
	.string "Than{SE_M_ENCORE2}yo{SE_M_DIVE}s{SE_M_ATTRACT2}much{SE_M_PERISH_SONG}Sorr{SE_M_YAWN}GIOVANNI!$"

RadioTowerBasement_Text_GruntM15After:
	.string "Hyuck-hyuck-hyuck{SE_M_DRAGON_RAGE}Tha{SE_M_SPIT_UP}wa{SE_M_GRASSWHISTLE}{SE_M_CHARGE}blast!\n"
	.string "I'l{SE_M_BATON_PASS}remembe{SE_M_SAND_TOMB}you!$"

RadioTowerBasement_Text_DirectorIntro:
	.string "DIRECTOR{SE_M_HEAT_WAVE}Who{SE_M_SING}What{SE_M_SING}Yo{SE_M_DIVE}cam{SE_M_REVERSAL}to\n"
	.string "rescu{SE_M_REVERSAL}me?\p"
	.string "Than{SE_M_ENCORE2}you!\p"
	.string "Th{SE_M_REVERSAL}RADI{SE_M_SOLAR_BEAM}TOWER!\p"
	.string "What'{SE_M_GRASSWHISTLE}happenin{SE_M_SANDSTORM}there?\p"
	.string "Take{SE_M_ATTRACT}ove{SE_M_SAND_TOMB}b{SE_M_YAWN}TEA{SE_M_GIGA_DRAIN}ROCKET?\p"
	.string "Here{SE_M_PERISH_SONG}Tak{SE_M_REVERSAL}thi{SE_M_GRASSWHISTLE}CAR{SE_M_FAINT_ATTACK}KEY.$"

RadioTowerBasement_Text_DirectorCardKey:
	.string "DIRECTOR{SE_M_HEAT_WAVE}Us{SE_M_REVERSAL}tha{SE_M_SPIT_UP}t{SE_M_ATTRACT2}ope{SE_M_ATTRACT}the\n"
	.string "shutter{SE_M_GRASSWHISTLE}o{SE_M_ATTRACT}3F.$"

RadioTowerBasement_Text_DirectorAfter:
	.string "I'{SE_M_MILK_DRINK}beggin{SE_M_SANDSTORM}yo{SE_M_DIVE}t{SE_M_ATTRACT2}help.\p"
	.string "There'{SE_M_GRASSWHISTLE}n{SE_M_ATTRACT2}tellin{SE_M_SANDSTORM}wha{SE_M_SPIT_UP}they'l{SE_M_BATON_PASS}d{SE_M_ATTRACT2}if\n"
	.string "the{SE_M_YAWN}contro{SE_M_BATON_PASS}th{SE_M_REVERSAL}transmitter.\p"
	.string "The{SE_M_YAWN}ma{SE_M_YAWN}eve{SE_M_ATTRACT}b{SE_M_REVERSAL}abl{SE_M_REVERSAL}t{SE_M_ATTRACT2}control\n"
	.string "POKéMO{SE_M_PSYBEAM2}usin{SE_M_SANDSTORM}{SE_M_CHARGE}specia{SE_M_BATON_PASS}signal!\p"
	.string "You'r{SE_M_REVERSAL}th{SE_M_REVERSAL}onl{SE_M_YAWN}on{SE_M_REVERSAL}{SE_M_HEAL_BELL}ca{SE_M_ATTRACT}cal{SE_M_BATON_PASS}on.\p"
	.string "Pleas{SE_M_REVERSAL}sav{SE_M_REVERSAL}th{SE_M_REVERSAL}RADI{SE_M_SOLAR_BEAM}TOWER…\p"
	.string "An{SE_M_WATERFALL}al{SE_M_BATON_PASS}th{SE_M_REVERSAL}POKéMO{SE_M_PSYBEAM2}nationwide!$"

