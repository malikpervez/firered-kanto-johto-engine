@ Johto (data/maps/SlowpokeWell_B1F_hns/scripts.inc), as built into the FireRed game.

SlowpokeWell_B1F_hns_MapScripts::
	.byte 0

SlowpokeWell_B1F_EventScript_Item_Super_Potion_1::
	finditem ITEM_SUPER_POTION
	end

SlowpokeWell_B1F_EventScript_Item_Super_Potion_2::
	finditem ITEM_SUPER_POTION
	end

SlowpokeWell_B1F_EventScript_Item_Great_Ball::
	finditem ITEM_GREAT_BALL
	end

SlowpokeWell_B1F_EventScript_Item_Full_Heal::
	finditem ITEM_FULL_HEAL
	end

SlowpokeWell_B1F_EventScript_Kurt::
	lock
	msgbox SlowpokeWell_B1F_Text_KurtIntro, MSGBOX_DEFAULT
	closemessage
	end

SlowpokeWell_B1F_EventScript_Grunt21::
	trainerbattle_single 1163, SlowpokeWell_B1F_Text_GruntM29Seen, SlowpokeWell_B1F_Text_GruntM29Beaten
	msgbox SlowpokeWell_B1F_Text_GruntM29After, MSGBOX_AUTOCLOSE
	end

SlowpokeWell_B1F_EventScript_Grunt22F::
	trainerbattle_single 1164, SlowpokeWell_B1F_Text_GruntF1Seen, SlowpokeWell_B1F_Text_GruntF1Beaten
	msgbox SlowpokeWell_B1F_Text_GruntF1After, MSGBOX_AUTOCLOSE
	end

SlowpokeWell_B1F_EventScript_Eto::
	trainerbattle_single 1176, SlowpokeWell_B1F_Text_GruntM2Seen, SlowpokeWell_B1F_Text_GruntM2Beaten
	msgbox SlowpokeWell_B1F_Text_GruntM2After, MSGBOX_AUTOCLOSE
	end

SlowpokeWell_B1F_EventScript_Proton::
	lock
	faceplayer
	msgbox SlowpokeWell_B1F_Text_ProtonSeen, MSGBOX_DEFAULT
	closemessage
	trainerbattle_no_intro 1491, SlowpokeWell_B1F_Text_ProtonBeaten
	msgbox SlowpokeWell_B1F_Text_ProtonAfter, MSGBOX_AUTOCLOSE
	closemessage
	fadescreen 1
	setflag 8283
	clearflag 8292
	addobject 19
	removeobject 11
	removeobject 12
	removeobject 13
	delay 120
	fadescreen 0
	special DrawWholeMapView
	turnobject 255, DIR_SOUTH
	applymovement 19, SlowpokeWell_B1F_Movement_Kurt
	waitmovement 0
	msgbox SlowpokeWell_B1F_Text_KurtAfter, MSGBOX_DEFAULT
	closemessage
	fadescreen 1
	setflag 8286
	setflag 8292
	clearflag 8293
	clearflag 8230
	setvar 20547, 3
	warp MAP_AZALEA_TOWN_KURTS_HOUSE_HNS, 15, 4
	waitstate
	end

SlowpokeWell_B1F_Movement_Kurt:
	walk_left
	walk_left
	walk_left
	walk_up
	walk_up
	walk_up
	step_end

SlowpokeWell_B1F_Text_KurtIntro:
	.string "KURT{SE_M_HEAT_WAVE}He{SE_M_YAWN}there{SE_M_SUPERSONIC}{PLAYER}!\p"
	.string "Th{SE_M_REVERSAL}guar{SE_M_WATERFALL}u{SE_M_MORNING_SUN}to{SE_M_MORNING_SUN}too{SE_M_ENCORE2}of{SE_M_ACID_ARMOR}when\n"
	.string "{SE_M_HEAL_BELL}shoute{SE_M_WATERFALL}a{SE_M_SPIT_UP}him.\p"
	.string "Bu{SE_M_SPIT_UP}the{SE_M_ATTRACT}{SE_M_HEAL_BELL}too{SE_M_ENCORE2}{SE_M_CHARGE}tumbl{SE_M_REVERSAL}down\n"
	.string "th{SE_M_REVERSAL}WELL.\p"
	.string "{SE_M_HEAL_BELL}slamme{SE_M_WATERFALL}dow{SE_M_ATTRACT}har{SE_M_WATERFALL}o{SE_M_ATTRACT}m{SE_M_YAWN}back,\n"
	.string "s{SE_M_ATTRACT2}{SE_M_HEAL_BELL}can'{SE_M_SPIT_UP}move.\p"
	.string "Rats{SE_M_DRAGON_RAGE}I{SE_M_ACID_ARMOR}{SE_M_HEAL_BELL}wer{SE_M_REVERSAL}fit{SE_M_SUPERSONIC}m{SE_M_YAWN}POKéMON\n"
	.string "would'v{SE_M_REVERSAL}punishe{SE_M_WATERFALL}them…\p"
	.string "Ah{SE_M_SUPERSONIC}i{SE_M_SPIT_UP}can'{SE_M_SPIT_UP}b{SE_M_REVERSAL}helped.\p"
	.string "{PLAYER}{SE_M_SUPERSONIC}sho{SE_M_TWISTER}the{SE_M_MILK_DRINK}ho{SE_M_TWISTER}gutsy\n"
	.string "yo{SE_M_DIVE}ar{SE_M_REVERSAL}i{SE_M_ATTRACT}m{SE_M_YAWN}place!$"

SlowpokeWell_B1F_Text_KurtAfter:
	.string "KURT{SE_M_HEAT_WAVE}Wa{SE_M_YAWN}t{SE_M_ATTRACT2}go{SE_M_SUPERSONIC}{PLAYER}!\p"
	.string "TEA{SE_M_GIGA_DRAIN}ROCKE{SE_M_SWIFT}ha{SE_M_GRASSWHISTLE}take{SE_M_ATTRACT}off.\p"
	.string "M{SE_M_YAWN}back'{SE_M_GRASSWHISTLE}bette{SE_M_SAND_TOMB}too.\n"
	.string "Let'{SE_M_GRASSWHISTLE}ge{SE_M_SPIT_UP}ou{SE_M_SPIT_UP}o{SE_M_ACID_ARMOR}here.$"

SlowpokeWell_B1F_Text_GruntM29Seen:
	.string "Darn{SE_M_DRAGON_RAGE}{SE_M_HEAL_BELL}wa{SE_M_GRASSWHISTLE}standin{SE_M_SANDSTORM}guar{SE_M_WATERFALL}up\n"
	.string "to{SE_M_MORNING_SUN}whe{SE_M_ATTRACT}som{SE_M_REVERSAL}ol{SE_M_WATERFALL}coo{SE_M_SPIT_UP}yelled\l"
	.string "a{SE_M_SPIT_UP}me.\p"
	.string "H{SE_M_REVERSAL}startle{SE_M_WATERFALL}m{SE_M_REVERSAL}s{SE_M_ATTRACT2}muc{SE_M_TRI_ATTACK}that\n"
	.string "{SE_M_HEAL_BELL}fel{SE_M_BATON_PASS}dow{SE_M_ATTRACT}here.\p"
	.string "{SE_M_HEAL_BELL}thin{SE_M_ENCORE2}I'l{SE_M_BATON_PASS}ven{SE_M_SPIT_UP}m{SE_M_YAWN}ange{SE_M_SAND_TOMB}by\n"
	.string "takin{SE_M_SANDSTORM}i{SE_M_SPIT_UP}ou{SE_M_SPIT_UP}o{SE_M_ATTRACT}you!$"

SlowpokeWell_B1F_Text_GruntM29Beaten:
	.string "Arrgh{SE_M_DRAGON_RAGE}Thi{SE_M_GRASSWHISTLE}i{SE_M_GRASSWHISTLE}NO{SE_M_SWIFT}m{SE_M_YAWN}day!$"

SlowpokeWell_B1F_Text_GruntM29After:
	.string "Sure{SE_M_SUPERSONIC}we'v{SE_M_REVERSAL}bee{SE_M_ATTRACT}hackin{SE_M_SANDSTORM}the\n"
	.string "tail{SE_M_GRASSWHISTLE}of{SE_M_ACID_ARMOR}SLOWPOK{SE_M_SWORDS_DANCE}an{SE_M_WATERFALL}selling\l"
	.string "them.\p"
	.string "Everythin{SE_M_SANDSTORM}w{SE_M_REVERSAL}d{SE_M_ATTRACT2}i{SE_M_GRASSWHISTLE}fo{SE_M_SAND_TOMB}profit.\p"
	.string "That'{SE_M_GRASSWHISTLE}right{SE_M_DRAGON_RAGE}We'r{SE_M_REVERSAL}TEA{SE_M_GIGA_DRAIN}ROCKET,\n"
	.string "an{SE_M_WATERFALL}we'l{SE_M_BATON_PASS}d{SE_M_ATTRACT2}anythin{SE_M_SANDSTORM}fo{SE_M_SAND_TOMB}money!$"

SlowpokeWell_B1F_Text_ProtonSeen:
	.string "Wha{SE_M_SPIT_UP}d{SE_M_ATTRACT2}yo{SE_M_DIVE}want?\p"
	.string "I{SE_M_ACID_ARMOR}yo{SE_M_DIVE}interrup{SE_M_SPIT_UP}ou{SE_M_SAND_TOMB}work,\n"
	.string "don'{SE_M_SPIT_UP}expec{SE_M_SPIT_UP}an{SE_M_YAWN}mercy!$"

SlowpokeWell_B1F_Text_ProtonBeaten:
	.string "Yo{SE_M_DIVE}di{SE_M_WATERFALL}O{SE_M_SNORE}today,\n"
	.string "bu{SE_M_SPIT_UP}wai{SE_M_SPIT_UP}til{SE_M_BATON_PASS}nex{SE_M_SPIT_UP}time!$"

SlowpokeWell_B1F_Text_ProtonAfter:
	.string "Yeah{SE_M_SUPERSONIC}TEA{SE_M_GIGA_DRAIN}ROCKE{SE_M_SWIFT}wa{SE_M_GRASSWHISTLE}broke{SE_M_ATTRACT}up\n"
	.string "thre{SE_M_REVERSAL}year{SE_M_GRASSWHISTLE}ago.\p"
	.string "Th{SE_M_REVERSAL}bos{SE_M_GRASSWHISTLE}wen{SE_M_SPIT_UP}int{SE_M_ATTRACT2}hiding.\p"
	.string "Bu{SE_M_SPIT_UP}w{SE_M_REVERSAL}continue{SE_M_WATERFALL}ou{SE_M_SAND_TOMB}activities\n"
	.string "underground!\p"
	.string "{SE_M_BONEMERANG}smal{SE_M_BATON_PASS}obstacl{SE_M_REVERSAL}lik{SE_M_REVERSAL}yo{SE_M_DIVE}won'{SE_M_SPIT_UP}be\n"
	.string "muc{SE_M_TRI_ATTACK}o{SE_M_ACID_ARMOR}{SE_M_CHARGE}proble{SE_M_MILK_DRINK}fo{SE_M_SAND_TOMB}ou{SE_M_SAND_TOMB}mission.\p"
	.string "{SE_M_HEAL_BELL}advis{SE_M_REVERSAL}yo{SE_M_DIVE}t{SE_M_ATTRACT2}b{SE_M_REVERSAL}ver{SE_M_YAWN}afrai{SE_M_WATERFALL}of\n"
	.string "wha{SE_M_SPIT_UP}i{SE_M_GRASSWHISTLE}t{SE_M_ATTRACT2}come!$"

SlowpokeWell_B1F_Text_GruntM2Seen:
	.string "Hyuck-hyuck-hyuck!\n"
	.string "Qui{SE_M_SPIT_UP}takin{SE_M_SANDSTORM}SLOWPOKETAILS?\p"
	.string "You'r{SE_M_REVERSAL}nuts!\n"
	.string "I{SE_M_ACID_ARMOR}w{SE_M_REVERSAL}obeye{SE_M_WATERFALL}you{SE_M_SUPERSONIC}TEA{SE_M_GIGA_DRAIN}ROCKET's\l"
	.string "re{SE_M_MORNING_SUN}woul{SE_M_WATERFALL}b{SE_M_REVERSAL}ruined!$"

SlowpokeWell_B1F_Text_GruntM2Beaten:
	.string "Hyuck…\n"
	.string "To{SE_M_ATTRACT2}strong…$"

SlowpokeWell_B1F_Text_GruntM2After:
	.string "W{SE_M_REVERSAL}nee{SE_M_WATERFALL}th{SE_M_REVERSAL}money,\n"
	.string "bu{SE_M_SPIT_UP}sellin{SE_M_SANDSTORM}SLOWPOKETAILS?\p"
	.string "It'{SE_M_GRASSWHISTLE}toug{SE_M_TRI_ATTACK}bein{SE_M_SANDSTORM}{SE_M_CHARGE}ROCKE{SE_M_SWIFT}GRUNT!$"

SlowpokeWell_B1F_Text_GruntF1Seen:
	.string "Sto{SE_M_MORNING_SUN}takin{SE_M_SANDSTORM}TAILS?\p"
	.string "Yeah{SE_M_SUPERSONIC}jus{SE_M_SPIT_UP}tr{SE_M_YAWN}t{SE_M_ATTRACT2}defea{SE_M_SPIT_UP}all\n"
	.string "o{SE_M_ACID_ARMOR}us!$"

SlowpokeWell_B1F_Text_GruntF1Beaten:
	.string "Yo{SE_M_DIVE}rotte{SE_M_ATTRACT}brat!$"

SlowpokeWell_B1F_Text_GruntF1After:
	.string "SLOWPOKETAIL{SE_M_SKETCH}gro{SE_M_TWISTER}bac{SE_M_ENCORE2}fast!\p"
	.string "What'{SE_M_GRASSWHISTLE}wron{SE_M_SANDSTORM}wit{SE_M_TRI_ATTACK}sellin{SE_M_SANDSTORM}them?$"

SlowpokeWell_B1F_Text_SlowpokeWithMail:
	.string "{SE_M_BONEMERANG}SLOWPOK{SE_M_SWORDS_DANCE}wit{SE_M_TRI_ATTACK}it{SE_M_GRASSWHISTLE}TAI{SE_M_BRICK_BREAK}cu{SE_M_SPIT_UP}off…\p"
	.string "Huh{SE_M_SING}I{SE_M_SPIT_UP}ha{SE_M_GRASSWHISTLE}MAIL.\n"
	.string "Rea{SE_M_WATERFALL}it?$"

SlowpokeWell_B1F_Text_SlowpokeMail:
	.string "{PLAYER} rea{SE_M_WATERFALL}th{SE_M_REVERSAL}MAIL.\p"
	.string "B{SE_M_REVERSAL}goo{SE_M_WATERFALL}an{SE_M_WATERFALL}loo{SE_M_ENCORE2}afte{SE_M_SAND_TOMB}the\n"
	.string "hous{SE_M_REVERSAL}wit{SE_M_TRI_ATTACK}Grandp{SE_M_CHARGE}an{SE_M_WATERFALL}SLOWPOKE.\p"
	.string "Love{SE_M_SUPERSONIC}Dad$"

SlowpokeWell_B1F_Text_TaillessSlowpoke:
	.string "{SE_M_BONEMERANG}SLOWPOK{SE_M_SWORDS_DANCE}wit{SE_M_TRI_ATTACK}it{SE_M_GRASSWHISTLE}TAI{SE_M_BRICK_BREAK}cu{SE_M_SPIT_UP}off…$"

