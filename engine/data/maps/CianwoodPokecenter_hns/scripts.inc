@ Johto (data/maps/CianwoodPokecenter_hns/scripts.inc), as built into the FireRed game.

CianwoodPokecenter_hns_MapScripts::
	map_script 3, CianwoodPokecenter_OnTransition
	.byte 0

CianwoodPokecenter_OnTransition::
	setrespawn 135
	end

CianwoodPokemoncenter_EventScript_Fisher::
	lock
	faceplayer
	goto_if_set 1, CianwoodPokemoncenter_EventScript_FisherNormal
	checkfieldmove FIELD_MOVE_SURF
	goto_if_eq 32781, 6, CianwoodPokemoncenter_EventScript_FisherGiveTentacool

CianwoodPokemoncenter_EventScript_FisherNormal::
	msgbox CianwoodPokemoncenter_Text_Fisher1, MSGBOX_DEFAULT
	closemessage
	release
	end

CianwoodPokemoncenter_EventScript_FisherGiveTentacool::
	msgbox CianwoodPokemoncenter_Text_Fisher2, MSGBOX_DEFAULT


	setvar 16385, 72
	bufferspeciesname STR_VAR_1, 72
	givemon 72, 25
	call J_Common_EventScript_GiftMon
	setflag 1

	closemessage
	release
	end

CianwoodPokemoncenter_Text_Fisher1:
	.string "A{SE_M_GRASSWHISTLE}fa{SE_M_SAND_TOMB}a{SE_M_GRASSWHISTLE}wate{SE_M_SAND_TOMB}POKéMO{SE_M_PSYBEAM2}go,\n"
	.string "TENTACOO{SE_M_BRICK_BREAK}i{SE_M_GRASSWHISTLE}th{SE_M_REVERSAL}bes{SE_M_SPIT_UP}b{SE_M_YAWN}a\l"
	.string "nautica{SE_M_BATON_PASS}mile!$"

CianwoodPokemoncenter_Text_Fisher2:
	.string "Yo{SE_M_DIVE}see{SE_M_MILK_DRINK}lik{SE_M_REVERSAL}yo{SE_M_DIVE}nee{SE_M_WATERFALL}{SE_M_CHARGE}water\n"
	.string "POKéMON.\p"
	.string "Here{SE_M_SUPERSONIC}tak{SE_M_REVERSAL}thi{SE_M_GRASSWHISTLE}one{SE_M_SUPERSONIC}{SE_M_HEAL_BELL}hav{SE_M_REVERSAL}plenty.$"

CianwoodPokecenter_EventScript_Lass::
	lock
	faceplayer
	msgbox CianwoodCity_Text_PokecenterLass, MSGBOX_DEFAULT
	closemessage
	release
	end

CianwoodCity_Text_PokecenterLass:
	.string "Di{SE_M_WATERFALL}yo{SE_M_DIVE}mee{SE_M_SPIT_UP}th{SE_M_REVERSAL}POKéMANIAC?\p"
	.string "He'{SE_M_GRASSWHISTLE}alway{SE_M_GRASSWHISTLE}braggin{SE_M_SANDSTORM}abou{SE_M_SPIT_UP}his\n"
	.string "rar{SE_M_REVERSAL}POKéMON.$"

CianwoodGym_EventScript_GymGuide::
	lock
	faceplayer
	goto_if_set 8747, CianwoodGym_EventScript_GymGuideAfter
	msgbox CianwoodCity_Text_GymGuide, MSGBOX_DEFAULT
	closemessage
	release
	end

CianwoodGym_EventScript_GymGuideAfter::
	msgbox CianwoodCity_Text_GymGuideWin, MSGBOX_DEFAULT
	closemessage
	release
	end

CianwoodCity_Text_GymGuide:
	.string "Th{SE_M_REVERSAL}POKéMO{SE_M_PSYBEAM2}GY{SE_M_GIGA_DRAIN}trainer{SE_M_GRASSWHISTLE}her{SE_M_REVERSAL}are\n"
	.string "mach{SE_M_ATTRACT2}bullies.\p"
	.string "I{SE_M_ACID_ARMOR}{SE_M_HEAL_BELL}stic{SE_M_ENCORE2}around{SE_M_SUPERSONIC}the{SE_M_YAWN}might\n"
	.string "com{SE_M_REVERSAL}afte{SE_M_SAND_TOMB}me.\p"
	.string "Here'{SE_M_GRASSWHISTLE}som{SE_M_REVERSAL}advice{SE_M_HEAT_WAVE}th{SE_M_REVERSAL}GY{SE_M_GIGA_DRAIN}LEADER\n"
	.string "use{SE_M_GRASSWHISTLE}th{SE_M_REVERSAL}FIGHTING-type.\p"
	.string "S{SE_M_ATTRACT2}yo{SE_M_DIVE}shoul{SE_M_WATERFALL}confoun{SE_M_WATERFALL}hi{SE_M_MILK_DRINK}with\n"
	.string "psychi{SE_M_HYPER_BEAM}POKéMON.\p"
	.string "Wip{SE_M_REVERSAL}ou{SE_M_SPIT_UP}hi{SE_M_GRASSWHISTLE}POKéMO{SE_M_PSYBEAM2}befor{SE_M_REVERSAL}they\n"
	.string "ca{SE_M_ATTRACT}us{SE_M_REVERSAL}thei{SE_M_SAND_TOMB}physica{SE_M_BATON_PASS}strength.\p"
	.string "An{SE_M_WATERFALL}thos{SE_M_REVERSAL}boulder{SE_M_GRASSWHISTLE}i{SE_M_ATTRACT}th{SE_M_REVERSAL}middle\n"
	.string "o{SE_M_ACID_ARMOR}th{SE_M_REVERSAL}GYM?\p"
	.string "I{SE_M_ACID_ARMOR}yo{SE_M_DIVE}don'{SE_M_SPIT_UP}mov{SE_M_REVERSAL}the{SE_M_MILK_DRINK}correctly,\n"
	.string "yo{SE_M_DIVE}won'{SE_M_SPIT_UP}reac{SE_M_TRI_ATTACK}th{SE_M_REVERSAL}GY{SE_M_GIGA_DRAIN}LEADER.\p"
	.string "I{SE_M_ACID_ARMOR}yo{SE_M_DIVE}ge{SE_M_SPIT_UP}stuck{SE_M_SUPERSONIC}g{SE_M_ATTRACT2}outside.$"

CianwoodCity_Text_GymGuideWin:
	.string "{PLAYER}{SE_M_DRAGON_RAGE}Yo{SE_M_DIVE}won!\n"
	.string "{SE_M_HEAL_BELL}coul{SE_M_WATERFALL}tel{SE_M_BATON_PASS}b{SE_M_YAWN}lookin{SE_M_SANDSTORM}a{SE_M_SPIT_UP}you!$"

CianwoodPokecenter_EventScript_Nerd::
	lock
	faceplayer
	msgbox CianwoodCity_Text_PokecenterSuperNerd, MSGBOX_DEFAULT
	closemessage
	release
	end

CianwoodCity_Text_PokecenterSuperNerd:
	.string "{SE_M_HEAL_BELL}lov{SE_M_REVERSAL}showin{SE_M_SANDSTORM}of{SE_M_ACID_ARMOR}th{SE_M_REVERSAL}POKéMON\n"
	.string "tha{SE_M_SPIT_UP}I'v{SE_M_REVERSAL}raised.\p"
	.string "Don'{SE_M_SPIT_UP}you?\p"
	.string "I'{SE_M_MILK_DRINK}goin{SE_M_SANDSTORM}t{SE_M_ATTRACT2}ge{SE_M_SPIT_UP}int{SE_M_ATTRACT2}{SE_M_CHARGE}bunc{SE_M_TRI_ATTACK}of\n"
	.string "battles{SE_M_SUPERSONIC}an{SE_M_WATERFALL}sho{SE_M_TWISTER}of{SE_M_ACID_ARMOR}m{SE_M_YAWN}POKéMON!$"

