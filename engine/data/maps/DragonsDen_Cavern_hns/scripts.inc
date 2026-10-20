@ Johto (data/maps/DragonsDen_Cavern_hns/scripts.inc), as built into the FireRed game.

DragonsDen_Cavern_hns_MapScripts::
	map_script 3, CharacterStory_DenTransition

	.byte 0

DragonsDen_Cavern_OnFrame::
	map_script_2 20550, 3, DragonsDen_Cavern_EventScript_Clair
	.2byte 0

DragonsDen_EventScript_ClairRematch::
	lock
	faceplayer
	msgbox DragonsDen_Text_Clair, MSGBOX_DEFAULT
	closemessage
	fadescreenswapbuffers 1
	setflag 8350
	removeobject 35
	fadescreenswapbuffers 0
	clearflag 8391
	release
	end

DragonsDen_Text_Clair:
	.string "{PLAYER}{SE_M_DIZZY_PUNCH}S{SE_M_ATTRACT2}you'r{SE_M_REVERSAL}here.\p"
	.string "I{SE_M_ACID_ARMOR}yo{SE_M_DIVE}thin{SE_M_ENCORE2}yo{SE_M_DIVE}ca{SE_M_ATTRACT}kee{SE_M_MORNING_SUN}up,\n"
	.string "wit{SE_M_TRI_ATTACK}me{SE_M_SUPERSONIC}com{SE_M_REVERSAL}t{SE_M_ATTRACT2}th{SE_M_REVERSAL}FIGHTING\l"
	.string "DOJ{SE_M_SOLAR_BEAM}i{SE_M_ATTRACT}SAFFRON.$"

DragonsDen_Cavern_Trigger_ClairLeft::
	lock
	setflag 14
	playse 21
	playbgm ((558 + 1) + 0x4C), FALSE
	applymovement2 5, J_Common_Movement_ExclamationMark
	delay 55
	waitmovement 5
	call DragonsDen_Cavern_EventScript_Clair
	applymovement 255, DragonsDen_Cavern_Movement_ClairLeaveLeftPLAYER
	waitmovement 0
	applymovement2 5, DragonsDen_Cavern_Movement_ClairLeaveLeft
	waitmovement 0
	setflag 8351
	removeobject 5
	playse 9
	fadedefaultbgm
	setvar 20550, 4
	setrespawn 137
	releaseall
	end

DragonsDen_Cavern_Trigger_ClairMid::
	lock
	playse 21
	playbgm ((558 + 1) + 0x4C), FALSE
	applymovement2 5, J_Common_Movement_ExclamationMark
	delay 55
	waitmovement 5
	applymovement2 5, J_Common_Movement_WalkRight1
	call DragonsDen_Cavern_EventScript_Clair
	applymovement2 5, DragonsDen_Cavern_Movement_ClairLeaveMid
	waitmovement 0
	setflag 8351
	removeobject 5
	playse 9
	fadedefaultbgm
	setvar 20550, 4
	release
	end

DragonsDen_Cavern_Trigger_ClairRight::
	lock
	playse 21
	playbgm ((558 + 1) + 0x4C), FALSE
	applymovement2 5, J_Common_Movement_ExclamationMark
	delay 55
	waitmovement 5
	applymovement2 5, J_Common_Movement_WalkRight1
	waitmovement 0
	applymovement2 5, J_Common_Movement_WalkRight1
	call DragonsDen_Cavern_EventScript_Clair
	applymovement2 5, DragonsDen_Cavern_Movement_ClairLeaveRight
	waitmovement 0
	setflag 8351
	removeobject 5
	playse 9
	fadedefaultbgm
	setvar 20550, 4
	release
	end

DragonsDen_Cavern_EventScript_Clair::
	turnobject 255, DIR_WEST
	msgbox DragonsDen_Cavern_Text_Clair_GiveTM, MSGBOX_DEFAULT
	giveitem 640
	msgbox DragonsDen_Cavern_Text_Clair_ExplainTM, MSGBOX_DEFAULT
	closemessage
	delay 30
	msgbox DragonsDen_Cavern_Text_ClairWhatsTheMatter, MSGBOX_DEFAULT
	closemessage
	delay 10
	clearflag 8707
	return

DragonsDen_Cavern_Movement_ClairLeaveLeftPLAYER:
	walk_fast_down
	face_up
	step_end

DragonsDen_Cavern_Movement_ClairLeaveLeft:
	walk_right
	walk_right
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

DragonsDen_Cavern_Movement_ClairLeaveMid:
	walk_up
	walk_right
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

DragonsDen_Cavern_Movement_ClairLeaveRight:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

DragonsDen_Cavern_Text_Clair_GiveTM:
	.string "CLAIR{SE_M_HEAT_WAVE}WAIT!\p"
	.string "I'{SE_M_MILK_DRINK}sorr{SE_M_YAWN}abou{SE_M_SPIT_UP}this.\n"
	.string "Here{SE_M_SUPERSONIC}tak{SE_M_REVERSAL}thi{SE_M_GRASSWHISTLE}a{SE_M_GRASSWHISTLE}m{SE_M_YAWN}apology.$"

DragonsDen_Cavern_Text_Clair_ExplainTM:
	.string "DRAGO{SE_M_PSYBEAM2}PULS{SE_M_SWORDS_DANCE}i{SE_M_GRASSWHISTLE}{SE_M_CHARGE}kin{SE_M_WATERFALL}o{SE_M_ACID_ARMOR}er...\n"
	.string "neve{SE_M_SAND_TOMB}mind!\p"
	.string "It'{SE_M_GRASSWHISTLE}{SE_M_CHARGE}hug{SE_M_REVERSAL}energ{SE_M_YAWN}o{SE_M_ACID_ARMOR}som{SE_M_REVERSAL}kind.\p"
	.string "I{SE_M_ACID_ARMOR}yo{SE_M_DIVE}don'{SE_M_SPIT_UP}wan{SE_M_SPIT_UP}it{SE_M_SUPERSONIC}yo{SE_M_DIVE}don'{SE_M_SPIT_UP}have\n"
	.string "t{SE_M_ATTRACT2}tak{SE_M_REVERSAL}it.$"

DragonsDen_Cavern_Text_ClairWhatsTheMatter:
	.string "What'{SE_M_GRASSWHISTLE}th{SE_M_REVERSAL}matter{SE_M_SING}Aren't\n"
	.string "yo{SE_M_DIVE}goin{SE_M_SANDSTORM}o{SE_M_ATTRACT}t{SE_M_ATTRACT2}th{SE_M_REVERSAL}POKéMON\l"
	.string "LEAGUE?\p"
	.string "Afte{SE_M_SAND_TOMB}yo{SE_M_DIVE}becom{SE_M_REVERSAL}CHAMPION{SE_M_SUPERSONIC}you\n"
	.string "ca{SE_M_ATTRACT}rematc{SE_M_TRI_ATTACK}an{SE_M_YAWN}GY{SE_M_GIGA_DRAIN}LEADE{SE_M_MINIMIZE}you\l"
	.string "want.\p"
	.string "G{SE_M_ATTRACT2}t{SE_M_ATTRACT2}th{SE_M_REVERSAL}POKéMO{SE_M_PSYBEAM2}LEAGUE.\p"
	.string "D{SE_M_ATTRACT2}yo{SE_M_DIVE}kno{SE_M_TWISTER}ho{SE_M_TWISTER}t{SE_M_ATTRACT2}ge{SE_M_SPIT_UP}there?\p"
	.string "Fro{SE_M_MILK_DRINK}here{SE_M_SUPERSONIC}g{SE_M_ATTRACT2}t{SE_M_ATTRACT2}NE{SE_M_DETECT}BAR{SE_M_SNORE}TOWN.\p"
	.string "The{SE_M_ATTRACT}SUR{SE_M_LEER}eas{SE_M_SPIT_UP}t{SE_M_ATTRACT2}POKéMO{SE_M_PSYBEAM2}LEAGUE.\p"
	.string "Th{SE_M_REVERSAL}rout{SE_M_REVERSAL}ther{SE_M_REVERSAL}i{SE_M_GRASSWHISTLE}ver{SE_M_YAWN}tough.\p"
	.string "Don'{SE_M_SPIT_UP}yo{SE_M_DIVE}dar{SE_M_REVERSAL}los{SE_M_REVERSAL}a{SE_M_SPIT_UP}th{SE_M_REVERSAL}POKéMON\n"
	.string "LEAGUE!\p"
	.string "I{SE_M_ACID_ARMOR}yo{SE_M_DIVE}do{SE_M_SUPERSONIC}I'l{SE_M_BATON_PASS}fee{SE_M_BATON_PASS}eve{SE_M_ATTRACT}worse\n"
	.string "abou{SE_M_SPIT_UP}havin{SE_M_SANDSTORM}los{SE_M_SPIT_UP}t{SE_M_ATTRACT2}you!\p"
	.string "Giv{SE_M_REVERSAL}i{SE_M_SPIT_UP}everythin{SE_M_SANDSTORM}you'v{SE_M_REVERSAL}got.$"

DragonsDen_Cavern_EventScript_Darin::
	trainerbattle_single 1096, DragonsDen_Cavern_Text_CooltrainermDarinSeen, DragonsDen_Cavern_Text_CooltrainermDarinBeaten
	msgbox DragonsDen_Cavern_Text_CooltrainermDarinAfter, MSGBOX_AUTOCLOSE
	end

DragonsDen_Cavern_EventScript_Cara::
	trainerbattle_single 1113, DragonsDen_Cavern_Text_CooltrainerfCaraSeen, DragonsDen_Cavern_Text_CooltrainerfCaraBeaten
	msgbox DragonsDen_Cavern_Text_CooltrainerfCaraAfter, MSGBOX_AUTOCLOSE
	end

DragonsDen_Cavern_EventScript_TwinLea::
	trainerbattle_double 1417, DragonsDen_Cavern_Text_TwinsLeaandPia1Seen, DragonsDen_Cavern_Text_TwinsLeaandPia1Beaten, J_Route104_Text_GinaNotEnoughMons
	special GetPlayerBigGuyGirlString
	msgbox DragonsDen_Cavern_Text_TwinsLeaandPia1After, MSGBOX_DEFAULT
	release
	end

DragonsDen_Cavern_EventScript_TwinPia::
	trainerbattle_double 1417, DragonsDen_Cavern_Text_TwinsLeaandPia2Seen, DragonsDen_Cavern_Text_TwinsLeaandPia2Beaten, J_Route104_Text_GinaNotEnoughMons
	special GetPlayerBigGuyGirlString
	msgbox DragonsDen_Cavern_Text_TwinsLeaandPia2After, MSGBOX_DEFAULT
	release
	end

DragonsDen_Cavern_EventScript_Item_Dragon_Fang::
	finditem ITEM_DRAGON_FANG
	end

DragonsDen_Cavern_EventScript_Item_Max_Potion::
	finditem ITEM_MAX_POTION
	end

DragonsDen_Cavern_EventScript_Item_PP_Max::
	finditem ITEM_PP_MAX
	end

DragonsDen_Cavern_Text_DragonShrineSign:
	.string "DRAGO{SE_M_PSYBEAM2}SHRINE\p"
	.string "{SE_M_BONEMERANG}shrin{SE_M_REVERSAL}honorin{SE_M_SANDSTORM}th{SE_M_REVERSAL}dragon\n"
	.string "POKéMON\p"
	.string "sai{SE_M_WATERFALL}t{SE_M_ATTRACT2}hav{SE_M_REVERSAL}live{SE_M_WATERFALL}i{SE_M_ATTRACT}DRAGON'S\n"
	.string "DEN.$"

DragonsDen_Cavern_Text_SilverTraining1:
	.string "…\n"
	.string "What{SE_M_SING}{PLAYER}?\p"
	.string "…No{SE_M_SUPERSONIC}{SE_M_HEAL_BELL}won'{SE_M_SPIT_UP}battl{SE_M_REVERSAL}yo{SE_M_DIVE}now…\p"
	.string "M{SE_M_YAWN}POKéMO{SE_M_PSYBEAM2}aren'{SE_M_SPIT_UP}read{SE_M_YAWN}t{SE_M_ATTRACT2}beat\n"
	.string "you.\p"
	.string "{SE_M_HEAL_BELL}can'{SE_M_SPIT_UP}pus{SE_M_TRI_ATTACK}the{SE_M_MILK_DRINK}to{SE_M_ATTRACT2}har{SE_M_WATERFALL}now.\p"
	.string "{SE_M_HEAL_BELL}hav{SE_M_REVERSAL}t{SE_M_ATTRACT2}b{SE_M_REVERSAL}discipline{SE_M_WATERFALL}t{SE_M_ATTRACT2}become\n"
	.string "th{SE_M_REVERSAL}greates{SE_M_SPIT_UP}POKéMO{SE_M_PSYBEAM2}trainer…$"

DragonsDen_Cavern_Text_SilverTraining2:
	.string "…\p"
	.string "Whew…\p"
	.string "Lear{SE_M_ATTRACT}t{SE_M_ATTRACT2}sta{SE_M_YAWN}ou{SE_M_SPIT_UP}o{SE_M_ACID_ARMOR}m{SE_M_YAWN}way…$"

DragonsDen_Cavern_Text_CooltrainermDarinSeen:
	.string "You{SE_M_DRAGON_RAGE}Ho{SE_M_TWISTER}dar{SE_M_REVERSAL}yo{SE_M_DIVE}enter\n"
	.string "uninvited!$"

DragonsDen_Cavern_Text_CooltrainermDarinBeaten:
	.string "S-strong!$"

DragonsDen_Cavern_Text_CooltrainermDarinAfter:
	.string "Th{SE_M_REVERSAL}SHRIN{SE_M_SWORDS_DANCE}ahea{SE_M_WATERFALL}i{SE_M_GRASSWHISTLE}hom{SE_M_REVERSAL}t{SE_M_ATTRACT2}the\n"
	.string "MASTE{SE_M_MINIMIZE}o{SE_M_ACID_ARMOR}ou{SE_M_SAND_TOMB}dragon-use{SE_M_SAND_TOMB}clan.\p"
	.string "You'r{SE_M_REVERSAL}no{SE_M_SPIT_UP}allowe{SE_M_WATERFALL}t{SE_M_ATTRACT2}jus{SE_M_SPIT_UP}g{SE_M_ATTRACT2}in!$"

DragonsDen_Cavern_Text_CooltrainerfCaraSeen:
	.string "Yo{SE_M_DIVE}shouldn'{SE_M_SPIT_UP}b{SE_M_REVERSAL}i{SE_M_ATTRACT}here!$"

DragonsDen_Cavern_Text_CooltrainerfCaraBeaten:
	.string "O{SE_M_TRI_ATTACK}yikes{SE_M_SUPERSONIC}{SE_M_HEAL_BELL}lost!$"

DragonsDen_Cavern_Text_CooltrainerfCaraAfter:
	.string "Soo{SE_M_ATTRACT}I'{SE_M_MILK_DRINK}goin{SE_M_SANDSTORM}t{SE_M_ATTRACT2}ge{SE_M_SPIT_UP}permission\n"
	.string "fro{SE_M_MILK_DRINK}ou{SE_M_SAND_TOMB}MASTE{SE_M_MINIMIZE}t{SE_M_ATTRACT2}us{SE_M_REVERSAL}dragons.\p"
	.string "Whe{SE_M_ATTRACT}{SE_M_HEAL_BELL}do{SE_M_SUPERSONIC}I'{SE_M_MILK_DRINK}goin{SE_M_SANDSTORM}t{SE_M_ATTRACT2}becom{SE_M_REVERSAL}an\n"
	.string "admirabl{SE_M_REVERSAL}drago{SE_M_ATTRACT}traine{SE_M_SAND_TOMB}an{SE_M_WATERFALL}gain\l"
	.string "ou{SE_M_SAND_TOMB}MASTER'{SE_M_GRASSWHISTLE}approval.$"

DragonsDen_Cavern_Text_TwinsLeaandPia1Seen:
	.string "It'{SE_M_GRASSWHISTLE}{SE_M_CHARGE}strange{SE_M_SAND_TOMB}w{SE_M_REVERSAL}don'{SE_M_SPIT_UP}know.$"

DragonsDen_Cavern_Text_TwinsLeaandPia1Beaten:
	.string "Ouchies.$"

DragonsDen_Cavern_Text_TwinsLeaandPia1After:
	.string "I{SE_M_SPIT_UP}wa{SE_M_GRASSWHISTLE}lik{SE_M_REVERSAL}havin{SE_M_SANDSTORM}t{SE_M_ATTRACT2}battle\n"
	.string "LANCE.$"

DragonsDen_Cavern_Text_TwinsLeaandPia2Seen:
	.string "Wh{SE_M_ATTRACT2}ar{SE_M_REVERSAL}you?$"

DragonsDen_Cavern_Text_TwinsLeaandPia2Beaten:
	.string "Meanie.$"

DragonsDen_Cavern_Text_TwinsLeaandPia2After:
	.string "We'l{SE_M_BATON_PASS}tel{SE_M_BATON_PASS}o{SE_M_ATTRACT}you.\p"
	.string "MASTE{SE_M_MINIMIZE}wil{SE_M_BATON_PASS}b{SE_M_REVERSAL}angr{SE_M_YAWN}wit{SE_M_TRI_ATTACK}you.$"

CharacterStory_DenTransition::
	call CG_SilverDenVisibility
	end

