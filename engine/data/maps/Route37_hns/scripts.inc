@ Johto (data/maps/Route37_hns/scripts.inc), as built into the FireRed game.

Route37_hns_MapScripts::
	map_script 3, Route37_OnTransition
	map_script 5, J_SetTimeEncounters
	.byte 0

Route37_OnTransition:
	callnative SetTimeBasedEncounters
	end

Route37_EventScript_TwinAnn::
	trainerbattle_double 1414, Route37_Text_TwinsAnnAndAnne1_Seen, Route37_Text_TwinsAnnAndAnne1_Beaten, J_Route104_Text_GinaNotEnoughMons
	special GetPlayerBigGuyGirlString
	msgbox Route37_Text_TwinsAnnAndAnne1_After, MSGBOX_DEFAULT
	release
	end

Route37_EventScript_TwinAnne::
	trainerbattle_double 1414, Route37_Text_TwinsAnnAndAnne2_Seen, Route37_Text_TwinsAnnAndAnne2_Beaten, J_Route104_Text_GinaNotEnoughMons
	special GetPlayerBigGuyGirlString
	msgbox Route37_Text_TwinsAnnAndAnne2_After, MSGBOX_DEFAULT
	release
	end

Route37_EventScript_Greg::
	trainerbattle_single 1334, Route37_Text_PsychicGreg_Seen, Route37_Text_PsychicGreg_Beaten
	msgbox Route37_Text_PsychicGreg_After, MSGBOX_AUTOCLOSE
	end

Route37_EventScript_Sunny::
	lock
	faceplayer
	goto_if_set 8728, Route37_EventScript_SunnyCompleted
	msgbox Route37_Text_Sunny_Meet, MSGBOX_DEFAULT
	closemessage
	multichoice 20, 0, 159, FALSE
	switch 32781
	case 0, Route37_EventScript_SunnyYes
	case 1, Route37_EventScript_SunnyNope
	case 2, Route37_EventScript_SunnyNope
	case 3, Route37_EventScript_SunnyNope
	case 4, Route37_EventScript_SunnyNope
	case 5, Route37_EventScript_SunnyNope
	case 6, Route37_EventScript_SunnyNope
	case 7 Route37_EventScript_SunnyCancel
	case 127, Route37_EventScript_SunnyCancel
	closemessage
	release
	end

Route37_EventScript_SunnyYes::
	msgbox Route37_Text_Sunny_GiveGift2, MSGBOX_DEFAULT
	giveitem ITEM_MAGNET
	goto_if_eq 32781, FALSE, J_Common_EventScript_ShowBagIsFull
	setflag 8728
	msgbox Route37_Text_Sunny_GaveGift, MSGBOX_DEFAULT
	closemessage
	release
	end

Route37_EventScript_SunnyNope::
	msgbox Route29_Text_TuscanyNope, MSGBOX_DEFAULT
	closemessage
	release
	end

Route37_EventScript_SunnyCancel::
	closemessage
	release
	end

Route37_EventScript_SunnyCompleted::
	msgbox Route37_Text_Sunny_Sunday, MSGBOX_DEFAULT
	closemessage
	release
	end

Route37_EventScript_Sign::
	lock
	msgbox Route37_Text_Sign, MSGBOX_SIGN
	closemessage
	release
	end

Route37_Text_TwinsAnnAndAnne1_Seen:
	.string "ANN{SE_M_HEAT_WAVE}ANN{SE_M_SWORDS_DANCE}an{SE_M_WATERFALL}{SE_M_HEAL_BELL}ar{SE_M_REVERSAL}i{SE_M_ATTRACT}this\n"
	.string "together!$"

Route37_Text_TwinsAnnAndAnne1_Beaten:
	.string "AN{SE_M_PSYBEAM2}{SE_WARP_IN}ANNE{SE_M_HEAT_WAVE}Nnn{SE_M_DIZZY_PUNCH}{SE_M_BONEMERANG}littl{SE_M_REVERSAL}too\n"
	.string "strong.$"

Route37_Text_TwinsAnnAndAnne1_After:
	.string "ANN{SE_M_HEAT_WAVE}{SE_M_HEAL_BELL}ca{SE_M_ATTRACT}tel{SE_M_BATON_PASS}wha{SE_M_SPIT_UP}m{SE_M_YAWN}siste{SE_M_SAND_TOMB}and\n"
	.string "m{SE_M_YAWN}POKéMO{SE_M_PSYBEAM2}ar{SE_M_REVERSAL}thinking.$"

Route37_Text_TwinsAnnAndAnne2_Seen:
	.string "ANNE{SE_M_HEAT_WAVE}AN{SE_M_PSYBEAM2}an{SE_M_WATERFALL}{SE_M_HEAL_BELL}ar{SE_M_REVERSAL}i{SE_M_ATTRACT}this\n"
	.string "together!$"

Route37_Text_TwinsAnnAndAnne2_Beaten:
	.string "AN{SE_M_PSYBEAM2}{SE_WARP_IN}ANNE{SE_M_HEAT_WAVE}Nnn{SE_M_DIZZY_PUNCH}{SE_M_BONEMERANG}littl{SE_M_REVERSAL}too\n"
	.string "strong.$"

Route37_Text_TwinsAnnAndAnne2_After:
	.string "ANNE{SE_M_HEAT_WAVE}W{SE_M_REVERSAL}shar{SE_M_REVERSAL}th{SE_M_REVERSAL}sam{SE_M_REVERSAL}feeling{SE_M_GRASSWHISTLE}as\n"
	.string "ou{SE_M_SAND_TOMB}POKéMON.$"

Route37_Text_PsychicGreg_Seen:
	.string "POKéMO{SE_M_PSYBEAM2}can'{SE_M_SPIT_UP}d{SE_M_ATTRACT2}{SE_M_CHARGE}thin{SE_M_SANDSTORM}i{SE_M_ACID_ARMOR}the{SE_M_YAWN}are\n"
	.string "asleep.\p"
	.string "I'l{SE_M_BATON_PASS}sho{SE_M_TWISTER}yo{SE_M_DIVE}ho{SE_M_TWISTER}scar{SE_M_YAWN}tha{SE_M_SPIT_UP}is!$"

Route37_Text_PsychicGreg_Beaten:
	.string "{SE_M_HEAL_BELL}lost{SE_M_PERISH_SONG}That'{SE_M_GRASSWHISTLE}prett{SE_M_YAWN}sad…$"

Route37_Text_PsychicGreg_After:
	.string "Puttin{SE_M_SANDSTORM}POKéMO{SE_M_PSYBEAM2}t{SE_M_ATTRACT2}slee{SE_M_MORNING_SUN}o{SE_M_SAND_TOMB}paralyz-\n"
	.string "in{SE_M_SANDSTORM}the{SE_M_MILK_DRINK}ar{SE_M_REVERSAL}goo{SE_M_WATERFALL}battl{SE_M_REVERSAL}techniques.$"

Route37_Text_Sunny_Meet:
	.string "SUNNY{SE_M_HEAT_WAVE}Hi!\p"
	.string "I'{SE_M_MILK_DRINK}SUNN{SE_M_MOONLIGHT}o{SE_M_ACID_ARMOR}th{SE_M_REVERSAL}WEEKDA{SE_M_MOONLIGHT}family!\p"
	.string "I{SE_M_ACID_ARMOR}yo{SE_M_DIVE}ca{SE_M_ATTRACT}gues{SE_M_GRASSWHISTLE}m{SE_M_YAWN}favorit{SE_M_REVERSAL}day,\n"
	.string "I'l{SE_M_BATON_PASS}giv{SE_M_REVERSAL}yo{SE_M_DIVE}{SE_M_CHARGE}reward.$"

Route37_Text_Sunny_GiveGift1:
	.string "{SE_M_HEAL_BELL}wa{SE_M_GRASSWHISTLE}tol{SE_M_WATERFALL}t{SE_M_ATTRACT2}giv{SE_M_REVERSAL}yo{SE_M_DIVE}thi{SE_M_GRASSWHISTLE}i{SE_M_ACID_ARMOR}{SE_M_HEAL_BELL}saw\n"
	.string "you!$"

Route37_Text_Sunny_GiveGift2:
	.string "{SE_M_HEAL_BELL}wa{SE_M_GRASSWHISTLE}tol{SE_M_WATERFALL}t{SE_M_ATTRACT2}giv{SE_M_REVERSAL}yo{SE_M_DIVE}thi{SE_M_GRASSWHISTLE}i{SE_M_ACID_ARMOR}{SE_M_HEAL_BELL}saw\n"
	.string "you!$"

Route37_Text_Sunny_GaveGift:
	.string "SUNNY{SE_M_HEAT_WAVE}Tha{SE_M_SPIT_UP}thing…\p"
	.string "Um…\p"
	.string "{SE_M_DIZZY_PUNCH}Wha{SE_M_SPIT_UP}wa{SE_M_GRASSWHISTLE}i{SE_M_SPIT_UP}now…\p"
	.string "…\p"
	.string "Oh{SE_M_DRAGON_RAGE}{SE_M_HEAL_BELL}remembe{SE_M_SAND_TOMB}now!\p"
	.string "{SE_M_BONEMERANG}POKéMO{SE_M_PSYBEAM2}tha{SE_M_SPIT_UP}know{SE_M_GRASSWHISTLE}electric\n"
	.string "move{SE_M_GRASSWHISTLE}shoul{SE_M_WATERFALL}hol{SE_M_WATERFALL}it.\p"
	.string "M{SE_M_YAWN}si{SE_M_GRASSWHISTLE}MONIC{SE_M_BONEMERANG}sai{SE_M_WATERFALL}i{SE_M_SPIT_UP}power{SE_M_GRASSWHISTLE}up\n"
	.string "electri{SE_M_HYPER_BEAM}moves!$"

Route37_Text_Sunny_Sunday:
	.string "SUNNY{SE_M_HEAT_WAVE}M{SE_M_YAWN}sister{SE_M_GRASSWHISTLE}an{SE_M_WATERFALL}brother{SE_M_GRASSWHISTLE}are\n"
	.string "MONICA{SE_M_SUPERSONIC}TUSCANY{SE_M_SUPERSONIC}WESLEY{SE_M_SUPERSONIC}ARTHUR,\l"
	.string "FRIED{SE_M_BONEMERANG}an{SE_M_WATERFALL}SANTOS.\p"
	.string "They'r{SE_M_REVERSAL}al{SE_M_BATON_PASS}olde{SE_M_SAND_TOMB}tha{SE_M_ATTRACT}me!$"

Route37_Text_Sunny_NotSunday:
	.string "SUNNY{SE_M_HEAT_WAVE}Isn'{SE_M_SPIT_UP}toda{SE_M_YAWN}Sunday?\n"
	.string "Um{SE_M_DIZZY_PUNCH}{SE_M_HEAL_BELL}forgot!$"

Route37_Text_Sign:
	.string "ROUT{SE_M_SWORDS_DANCE}37\n"
	.string "ECRUTEA{SE_M_SNORE}CIT{SE_M_MOONLIGHT}AHEAD$"

