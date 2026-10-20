@ Johto (data/maps/UnionCave_B2F_hns/scripts.inc), as built into the FireRed game.

UnionCave_B2F_hns_MapScripts::
	.byte 0

UnionCave_B2F_EventScript_CooltrainerNick::
	trainerbattle_single 1079, UnionCave_B2F_Text_CooltrainermNickSeen, UnionCave_B2F_Text_CooltrainermNickBeaten
	msgbox UnionCave_B2F_Text_CooltrainermNickAfter, MSGBOX_AUTOCLOSE
	end

UnionCave_B2F_EventScript_CooltrainerfGwen::
	trainerbattle_single 1097, UnionCave_B2F_Text_CooltrainerfGwenSeen, UnionCave_B2F_Text_CooltrainerfGwenBeaten
	msgbox UnionCave_B2F_Text_CooltrainerfGwenAfter, MSGBOX_AUTOCLOSE
	end

UnionCave_B2F_EventScript_CooltrainerfEmma::
	trainerbattle_single 1110, UnionCave_B2F_Text_CooltrainerfEmmaSeen, UnionCave_B2F_Text_CooltrainerfEmmaBeaten
	msgbox UnionCave_B2F_Text_CooltrainerfEmmaAfter, MSGBOX_AUTOCLOSE
	end

UnionCave_B2F_EventScript_Lapras::
	lock
	faceplayer
	playmoncry 131, 2
	waitmoncry
	setwildbattle 131, 20
	dowildbattle
	specialvar 32781, GetBattleOutcome
	goto_if_eq 32781, 4, UnionCave_B2F_EventScript_LaprasRan
	fadescreenswapbuffers 1
	removeobject 6
	setflag 8247
	fadescreenswapbuffers 0
	release
	end

UnionCave_B2F_EventScript_LaprasRan::
	release
	end

UnionCave_B2F_EventScript_Item_Ether::
	finditem ITEM_ETHER
	end

UnionCave_B2F_EventScript_Item_HyperPotion::
	finditem ITEM_HYPER_POTION
	end

UnionCave_B2F_EventScript_Item_MaxRevive::
	finditem ITEM_MAX_REVIVE
	end

UnionCave_B2F_Text_CooltrainermNickSeen:
	.string "Ther{SE_M_REVERSAL}ar{SE_M_REVERSAL}tw{SE_M_ATTRACT2}kind{SE_M_GRASSWHISTLE}o{SE_M_ACID_ARMOR}people.\p"
	.string "Thos{SE_M_REVERSAL}wh{SE_M_ATTRACT2}hav{SE_M_REVERSAL}style{SE_M_SUPERSONIC}an{SE_M_WATERFALL}those\n"
	.string "wh{SE_M_ATTRACT2}don't.\p"
	.string "Wha{SE_M_SPIT_UP}kin{SE_M_WATERFALL}o{SE_M_ACID_ARMOR}perso{SE_M_ATTRACT}ar{SE_M_REVERSAL}you?$"

UnionCave_B2F_Text_CooltrainermNickBeaten:
	.string "You'v{SE_M_REVERSAL}go{SE_M_SPIT_UP}dazzlin{SE_M_SANDSTORM}style!$"

UnionCave_B2F_Text_CooltrainermNickAfter:
	.string "You{SE_M_SAND_TOMB}POKéMO{SE_M_PSYBEAM2}styl{SE_M_REVERSAL}i{SE_M_GRASSWHISTLE}stunnin{SE_M_SANDSTORM}and\n"
	.string "colorful{SE_M_SUPERSONIC}{SE_M_HEAL_BELL}admit.\p"
	.string "You'l{SE_M_BATON_PASS}jus{SE_M_SPIT_UP}kee{SE_M_MORNING_SUN}gettin{SE_M_SANDSTORM}better!$"

UnionCave_B2F_Text_CooltrainerfGwenSeen:
	.string "I'{SE_M_MILK_DRINK}i{SE_M_ATTRACT}training{SE_M_PERISH_SONG}Car{SE_M_REVERSAL}fo{SE_M_SAND_TOMB}{SE_M_CHARGE}round?$"

UnionCave_B2F_Text_CooltrainerfGwenBeaten:
	.string "Aww{SE_M_SUPERSONIC}no{SE_M_DRAGON_RAGE}You'r{SE_M_REVERSAL}to{SE_M_ATTRACT2}goo{SE_M_WATERFALL}fo{SE_M_SAND_TOMB}me.$"

UnionCave_B2F_Text_CooltrainerfGwenAfter:
	.string "I'{SE_M_MILK_DRINK}goin{SE_M_SANDSTORM}t{SE_M_ATTRACT2}trai{SE_M_ATTRACT}b{SE_M_YAWN}mysel{SE_M_ACID_ARMOR}unti{SE_M_BATON_PASS}I\n"
	.string "improve.$"

UnionCave_B2F_Text_CooltrainerfEmmaSeen:
	.string "I{SE_M_ACID_ARMOR}th{SE_M_REVERSAL}POKéMO{SE_M_PSYBEAM2}{SE_M_HEAL_BELL}like{SE_M_WATERFALL}wer{SE_M_REVERSAL}there,\n"
	.string "I'{SE_M_WATERFALL}g{SE_M_ATTRACT2}anywhere.\p"
	.string "That'{SE_M_GRASSWHISTLE}wha{SE_M_SPIT_UP}{SE_M_CHARGE}rea{SE_M_BATON_PASS}traine{SE_M_SAND_TOMB}does.$"

UnionCave_B2F_Text_CooltrainerfEmmaBeaten:
	.string "I'{SE_M_WATERFALL}rathe{SE_M_SAND_TOMB}pe{SE_M_SPIT_UP}m{SE_M_YAWN}babie{SE_M_GRASSWHISTLE}tha{SE_M_ATTRACT}this!$"

UnionCave_B2F_Text_CooltrainerfEmmaAfter:
	.string "Jus{SE_M_SPIT_UP}onc{SE_M_REVERSAL}{SE_M_CHARGE}week{SE_M_SUPERSONIC}{SE_M_CHARGE}POKéMO{SE_M_PSYBEAM2}come{SE_M_GRASSWHISTLE}to\n"
	.string "th{SE_M_REVERSAL}water'{SE_M_GRASSWHISTLE}edge.\p"
	.string "{SE_M_HEAL_BELL}wante{SE_M_WATERFALL}t{SE_M_ATTRACT2}se{SE_M_REVERSAL}tha{SE_M_SPIT_UP}POKéMON…$"

