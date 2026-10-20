@ Johto (data/maps/Route36_hns/scripts.inc), as built into the FireRed game.

Route36_hns_MapScripts::
	map_script 3, Route36_OnTransition
	map_script 5, J_SetTimeEncounters
	.byte 0

Route36_OnTransition:
	callnative SetTimeBasedEncounters
	end

Route36_EventScript_RockSmashGuy::
	lock
	faceplayer
	goto_if_set 8246, Route36_EventScript_RockSmashGuy2
	msgbox Route36_Text_RockSmashGuy1, MSGBOX_DEFAULT
	closemessage
	release
	end

Route36_EventScript_RockSmashGuy2::
	goto_if_set 8695, Route36_EventScript_RockSmashGuy3
	msgbox Route36_Text_RockSmashGuy2, MSGBOX_DEFAULT
	giveitem 687
	setflag 8695

Route36_EventScript_RockSmashGuy3::
	msgbox Route36_Text_RockSmashGuy3
	closemessage
	release
	end

Route36_EventScript_Lass::
	lock
	faceplayer
	goto_if_set 8246, Route36_EventScript_Lass2
	msgbox Route36_Text_Lass1, MSGBOX_DEFAULT
	closemessage
	release
	end

Route36_EventScript_Lass2::
	msgbox Route36_Text_Lass2_ClearedSudowoodo, MSGBOX_DEFAULT
	closemessage
	release
	end

Route36_EventScript_Arthur::
	lock
	faceplayer
	goto_if_set 8727, Route36_EventScript_ArthurCompleted
	msgbox Route36_Text_MeetArthur, MSGBOX_DEFAULT
	closemessage
	multichoice 20, 0, 159, FALSE
	switch 32781
	case 0, Route36_EventScript_ArthurNope
	case 1, Route36_EventScript_ArthurNope
	case 2, Route36_EventScript_ArthurNope
	case 3, Route36_EventScript_ArthurNope
	case 4, Route36_EventScript_ArthurYes
	case 5, Route36_EventScript_ArthurNope
	case 6, Route36_EventScript_ArthurNope
	case 7, Route36_EventScript_ArthurCancel
	case 127, Route36_EventScript_ArthurCancel
	closemessage
	release
	end

Route36_EventScript_ArthurYes::
	msgbox Route36_Text_ArthurGivesGift, MSGBOX_DEFAULT
	giveitem ITEM_HARD_STONE
	goto_if_eq 32781, FALSE, J_Common_EventScript_ShowBagIsFull
	setflag 8727
	msgbox Route36_Text_ArthurGaveGift, MSGBOX_DEFAULT
	closemessage
	release
	end

Route36_EventScript_ArthurNope::
	msgbox Route36_Text_ArthurNope, MSGBOX_DEFAULT
	closemessage
	release
	end

Route36_EventScript_ArthurCancel::
	closemessage
	release
	end

Route36_EventScript_ArthurCompleted::
	msgbox Route36_Text_ArthurThursday, MSGBOX_DEFAULT
	closemessage
	release
	end

Route36_EventScript_SudoWoodo::
	lock
	msgbox Route36_Text_OddTree, MSGBOX_DEFAULT
	checkitem ITEM_SQUIRT_BOTTLE
	goto_if_eq 32781, TRUE, Route36_EventScript_SudoWoodoChoice
	closemessage
	release
	end

Route36_EventScript_SudoWoodoChoice::
	msgbox Route36_Text_UseSquirtbottle, MSGBOX_YESNO
	goto_if_eq 32781, TRUE, Route36_EventScript_SudoWoodoWater
	closemessage
	release
	end

Route36_EventScript_SudoWoodoWater::
	msgbox Route36_Text_UsedSquirtbottle, MSGBOX_DEFAULT
	playse 83
	waitse
	closemessage
	playse 269
	applymovement 6, Route36_Movement_SudoWoodo
	waitmovement 0
	faceplayer
	msgbox Route36_Text_SudowoodoAttacked
	closemessage
	waitse
	playmoncry 185, 2
	delay 40
	waitmoncry
	setvar 32783, 6
	setwildbattle 185, 20

	dowildbattle

	specialvar 32781, GetBattleOutcome
	goto_if_eq 32781, 1, Route36_EventScript_Defeated_Sudowoodo
	goto_if_eq 32781, 4, Route36_EventScript_RanSudowoodo
	goto_if_eq 32781, 5, Route36_EventScript_RanSudowoodo

Route36_EventScript_Defeated_Sudowoodo::
	setflag 8246
	removeobject 6
	checkitem 687
	call_if_eq 32781, FALSE, Route36_EventScript_RockSmashGuySudoWoodo
	release
	end

Route36_EventScript_RanSudowoodo::
	turnobject 6, DIR_NORTH
	release
	end

Route36_EventScript_RockSmashGuySudoWoodo:
	playse 21
	applymovement 3, J_Common_Movement_ExclamationMark
	turnobject 3, DIR_WEST
	waitmovement 0
	applymovement 3, Route36_Movement_RockSmashGuy
	playse 10
	waitse
	playse 10
	waitse
	playse 10
	waitse
	playse 10
	waitmovement 0
	return

Route36_Movement_RockSmashGuy:
	jump_in_place_left
	delay_2
	jump_in_place_left
	delay_2
	jump_in_place_left
	delay_2
	jump_in_place_left
	step_end

Route36_EventScript_Mark::
	trainerbattle_single 1336, Route36_Text_PsychicMarkSeen, Route36_Text_PsychicMarkBeaten
	msgbox Route36_Text_PsychicMarkAfter, MSGBOX_AUTOCLOSE
	end

Route36_EventScript_Schoolboy::
	trainerbattle_single 1043, Route36_Text_SchoolboyAlan1Seen, Route36_Text_SchoolboyAlan1Beaten, Route36_EventScript_RegisterAlan
	goto_if_set 8939, Route36_EventScript_AlanGiveItem
	specialvar 32781, ShouldTryRematchBattle
	goto_if_eq 32781, TRUE, Route36_EventScript_RematchAlan
	msgbox Route36_Text_SchoolboyAlanAfter, MSGBOX_AUTOCLOSE
	end

Route36_EventScript_RegisterAlan::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox Route36_Text_AlanRegister, MSGBOX_DEFAULT
	register_matchcall 1043
	release
	end

Route36_EventScript_RematchAlan::
	trainerbattle_rematch 1043, Route36_Text_AlanRematchIntro, Route36_Text_AlanRematchDefeat
	msgbox Route36_Text_AlanPostRematch, MSGBOX_AUTOCLOSE
	end

Route36_EventScript_AlanGiveItem::
	msgbox Route36_Text_AlanHasItem, MSGBOX_DEFAULT
	giveitem 20616
	goto_if_eq 32781, FALSE, Route36_EventScript_AlanNoRoom
	clearflag 8939
	msgbox Route36_Text_AlanGaveItem, MSGBOX_AUTOCLOSE
	end

Route36_EventScript_AlanNoRoom::
	msgbox Route36_Text_AlanNoRoom, MSGBOX_AUTOCLOSE
	end

Route36_EventScript_Sign::
	lock
	msgbox Route36_Text_Sign_RuinsNorth, MSGBOX_SIGN
	closemessage
	release
	end

Route36_EventScript_Sign2::
	lock
	msgbox Route36_Text_Tips1, MSGBOX_SIGN
	closemessage
	release
	end

Route36_Movement_SudoWoodo:
	face_right
	delay_8
	face_down
	delay_8
	face_left
	delay_8
	face_down
	delay_8
	face_right
	delay_8
	face_down
	delay_8
	face_left
	delay_8
	face_down
	step_end

Route36_Text_UseSquirtbottle:
	.string "Us{SE_M_REVERSAL}SQUIRTBOTTLE?$"

Route36_Text_UsedSquirtbottle:
	.string "{PLAYER} use{SE_M_WATERFALL}th{SE_M_REVERSAL}SQUIRTBOTTLE.$"

Route36_Text_SudowoodoAttacked:
	.string "Th{SE_M_REVERSAL}weir{SE_M_WATERFALL}tre{SE_M_REVERSAL}doesn'{SE_M_SPIT_UP}lik{SE_M_REVERSAL}the\n"
	.string "SQUIRTBOTTLE!\p"
	.string "Th{SE_M_REVERSAL}weir{SE_M_WATERFALL}tre{SE_M_REVERSAL}attacked!$"

Route36_Text_RockSmashGuy1:
	.string "Wa-hey!\p"
	.string "{SE_M_HEAL_BELL}wa{SE_M_GRASSWHISTLE}goin{SE_M_SANDSTORM}t{SE_M_ATTRACT2}sna{SE_M_MORNING_SUN}tha{SE_M_SPIT_UP}tree\n"
	.string "wit{SE_M_TRI_ATTACK}m{SE_M_YAWN}straight-ar{SE_M_MILK_DRINK}punch.\p"
	.string "Bu{SE_M_SPIT_UP}{SE_M_HEAL_BELL}couldn't{SE_M_DRAGON_RAGE}I'{SE_M_MILK_DRINK}{SE_M_CHARGE}failure!$"

Route36_Text_RockSmashGuy2:
	.string "Di{SE_M_WATERFALL}yo{SE_M_DIVE}clea{SE_M_SAND_TOMB}tha{SE_M_SPIT_UP}wretche{SE_M_WATERFALL}tree?\p"
	.string "I'{SE_M_MILK_DRINK}impressed!\n"
	.string "{SE_M_HEAL_BELL}wan{SE_M_SPIT_UP}yo{SE_M_DIVE}t{SE_M_ATTRACT2}hav{SE_M_REVERSAL}this.$"

Route36_Text_RockSmashGuy3:
	.string "Tha{SE_M_SPIT_UP}happen{SE_M_GRASSWHISTLE}t{SE_M_ATTRACT2}b{SE_M_REVERSAL}ROC{SE_M_SNORE}SMASH.\p"
	.string "Yo{SE_M_DIVE}ca{SE_M_ATTRACT}shatte{SE_M_SAND_TOMB}rock{SE_M_GRASSWHISTLE}wit{SE_M_TRI_ATTACK}jus{SE_M_SPIT_UP}a\n"
	.string "singl{SE_M_REVERSAL}well-aime{SE_M_WATERFALL}smack.\p"
	.string "I{SE_M_ACID_ARMOR}an{SE_M_YAWN}rock{SE_M_GRASSWHISTLE}ar{SE_M_REVERSAL}i{SE_M_ATTRACT}you{SE_M_SAND_TOMB}way,\n"
	.string "jus{SE_M_SPIT_UP}smas{SE_M_TRI_ATTACK}'e{SE_M_MILK_DRINK}up!$"

Route36_Text_OddTree:
	.string "{SE_M_BONEMERANG}weir{SE_M_WATERFALL}tre{SE_M_REVERSAL}i{SE_M_GRASSWHISTLE}blockin{SE_M_SANDSTORM}th{SE_M_REVERSAL}way.$"

Route36_Text_Lass1:
	.string "B{SE_M_REVERSAL}carefu{SE_M_BATON_PASS}a{SE_M_SPIT_UP}nigh{SE_M_SPIT_UP}o{SE_M_ATTRACT}thi{SE_M_GRASSWHISTLE}route!\p"
	.string "{SE_M_HEAL_BELL}sa{SE_M_TWISTER}{SE_M_CHARGE}POKéMO{SE_M_PSYBEAM2}tha{SE_M_SPIT_UP}looke{SE_M_WATERFALL}like\n"
	.string "GROWLITHE{SE_M_SUPERSONIC}bu{SE_M_SPIT_UP}i{SE_M_SPIT_UP}ha{SE_M_WATERFALL}{SE_M_CHARGE}scar{SE_M_YAWN}aura\l"
	.string "t{SE_M_ATTRACT2}it.$"

Route36_Text_Lass2_ClearedSudowoodo:
	.string "Tha{SE_M_SPIT_UP}od{SE_M_WATERFALL}tre{SE_M_REVERSAL}disappeare{SE_M_WATERFALL}without\n"
	.string "{SE_M_CHARGE}trace.\p"
	.string "Oh{SE_M_DRAGON_RAGE}Tha{SE_M_SPIT_UP}tre{SE_M_REVERSAL}wa{SE_M_GRASSWHISTLE}reall{SE_M_YAWN}a\n"
	.string "POKéMON?$"

Route36_Text_PsychicMarkSeen:
	.string "I'{SE_M_MILK_DRINK}goin{SE_M_SANDSTORM}t{SE_M_ATTRACT2}rea{SE_M_WATERFALL}you{SE_M_SAND_TOMB}thoughts!$"

Route36_Text_PsychicMarkBeaten:
	.string "{SE_M_HEAL_BELL}misrea{SE_M_WATERFALL}you!$"

Route36_Text_PsychicMarkAfter:
	.string "I'{SE_M_WATERFALL}b{SE_M_REVERSAL}stron{SE_M_SANDSTORM}i{SE_M_ACID_ARMOR}onl{SE_M_YAWN}{SE_M_HEAL_BELL}coul{SE_M_WATERFALL}tell\n"
	.string "wha{SE_M_SPIT_UP}m{SE_M_YAWN}opponen{SE_M_SPIT_UP}wa{SE_M_GRASSWHISTLE}thinking.$"

Route36_Text_SchoolboyAlan1Seen:
	.string "Thank{SE_M_GRASSWHISTLE}t{SE_M_ATTRACT2}m{SE_M_YAWN}studies{SE_M_SUPERSONIC}I'{SE_M_MILK_DRINK}ready\n"
	.string "fo{SE_M_SAND_TOMB}an{SE_M_YAWN}POKéMON!$"

Route36_Text_SchoolboyAlan1Beaten:
	.string "Oops{SE_M_DRAGON_RAGE}Computatio{SE_M_ATTRACT}error?$"

Route36_Text_SchoolboyAlanAfter:
	.string "Darn{SE_M_PERISH_SONG}{SE_M_HEAL_BELL}stud{SE_M_YAWN}fiv{SE_M_REVERSAL}hour{SE_M_GRASSWHISTLE}{SE_M_CHARGE}da{SE_M_YAWN}too.\p"
	.string "There'{SE_M_GRASSWHISTLE}mor{SE_M_REVERSAL}t{SE_M_ATTRACT2}learnin{SE_M_SANDSTORM}tha{SE_M_ATTRACT}just\n"
	.string "readin{SE_M_SANDSTORM}books.$"

Route36_Text_MeetArthur:
	.string "ARTHUR{SE_M_HEAT_WAVE}Wh{SE_M_ATTRACT2}ar{SE_M_REVERSAL}you?\n"
	.string "I'{SE_M_MILK_DRINK}ARTHU{SE_M_MINIMIZE}o{SE_M_ACID_ARMOR}th{SE_M_REVERSAL}WEEKDA{SE_M_MOONLIGHT}FAMILY.\p"
	.string "I{SE_M_ACID_ARMOR}yo{SE_M_DIVE}ca{SE_M_ATTRACT}gues{SE_M_GRASSWHISTLE}m{SE_M_YAWN}favorit{SE_M_REVERSAL}day,\n"
	.string "I'l{SE_M_BATON_PASS}giv{SE_M_REVERSAL}yo{SE_M_DIVE}{SE_M_CHARGE}reward.$"

Route36_Text_ArthurNope:
	.string "No{SE_M_SPIT_UP}quite!$"

Route36_Text_ArthurGivesGift:
	.string "Here{SE_M_PERISH_SONG}Yo{SE_M_DIVE}ca{SE_M_ATTRACT}hav{SE_M_REVERSAL}this.$"

Route36_Text_ArthurGaveGift:
	.string "ARTHUR{SE_M_HEAT_WAVE}{SE_M_BONEMERANG}POKéMO{SE_M_PSYBEAM2}tha{SE_M_SPIT_UP}use{SE_M_GRASSWHISTLE}ROCK-\n"
	.string "typ{SE_M_REVERSAL}move{SE_M_GRASSWHISTLE}shoul{SE_M_WATERFALL}hol{SE_M_WATERFALL}o{SE_M_ATTRACT}t{SE_M_ATTRACT2}that.\p"
	.string "I{SE_M_SPIT_UP}pump{SE_M_GRASSWHISTLE}u{SE_M_MORNING_SUN}ROCK-typ{SE_M_REVERSAL}attacks.$"

Route36_Text_ArthurThursday:
	.string "ARTHUR{SE_M_HEAT_WAVE}I'{SE_M_MILK_DRINK}ARTHU{SE_M_MINIMIZE}o{SE_M_ACID_ARMOR}Thursday.\n"
	.string "I'{SE_M_MILK_DRINK}th{SE_M_REVERSAL}fift{SE_M_TRI_ATTACK}so{SE_M_ATTRACT}ou{SE_M_SPIT_UP}o{SE_M_ACID_ARMOR}seven.$"

Route36_Text_Sign:
	.string "ROUT{SE_M_SWORDS_DANCE}36$"

Route36_Text_Sign_RuinsNorth:
	.string "RUIN{SE_M_SKETCH}O{SE_M_LEER}ALPH\n"
	.string "NORT{SE_M_SWAGGER2}ENTRANCE$"

Route36_Text_Tips1:
	.string "TRAINE{SE_M_MINIMIZE}TIPS\n"
	.string "POKéMO{SE_M_PSYBEAM2}stat{SE_M_GRASSWHISTLE}vary--eve{SE_M_ATTRACT}within\l"
	.string "th{SE_M_REVERSAL}sam{SE_M_REVERSAL}species.\p"
	.string "Thei{SE_M_SAND_TOMB}stat{SE_M_GRASSWHISTLE}ma{SE_M_YAWN}b{SE_M_REVERSAL}simila{SE_M_SAND_TOMB}a{SE_M_SPIT_UP}first.\p"
	.string "However{SE_M_SUPERSONIC}difference{SE_M_GRASSWHISTLE}wil{SE_M_BATON_PASS}become\n"
	.string "pronounce{SE_M_WATERFALL}a{SE_M_GRASSWHISTLE}th{SE_M_REVERSAL}POKéMO{SE_M_PSYBEAM2}grow.$"

Route36_Text_Tips2:
	.string "TRAINE{SE_M_MINIMIZE}TIPS\n"
	.string "Us{SE_M_REVERSAL}DI{SE_M_SWAGGER}t{SE_M_ATTRACT2}retur{SE_M_ATTRACT}t{SE_M_ATTRACT2}th{SE_M_REVERSAL}entranc{SE_M_REVERSAL}of\n"
	.string "an{SE_M_YAWN}place.\p"
	.string "I{SE_M_SPIT_UP}i{SE_M_GRASSWHISTLE}convenien{SE_M_SPIT_UP}fo{SE_M_SAND_TOMB}exploring\n"
	.string "cave{SE_M_GRASSWHISTLE}an{SE_M_WATERFALL}othe{SE_M_SAND_TOMB}landmarks.$"

Route36_Text_AlanRegister:
	.string "Darn{SE_M_PERISH_SONG}{SE_M_HEAL_BELL}stud{SE_M_YAWN}fiv{SE_M_REVERSAL}hour{SE_M_GRASSWHISTLE}{SE_M_CHARGE}da{SE_M_YAWN}too.\p"
	.string "There'{SE_M_GRASSWHISTLE}mor{SE_M_REVERSAL}t{SE_M_ATTRACT2}learnin{SE_M_SANDSTORM}tha{SE_M_ATTRACT}just\n"
	.string "readin{SE_M_SANDSTORM}books.$"

Route36_Text_AlanRematchIntro:
	.string "Thank{SE_M_GRASSWHISTLE}t{SE_M_ATTRACT2}m{SE_M_YAWN}studies{SE_M_SUPERSONIC}I'{SE_M_MILK_DRINK}ready\n"
	.string "fo{SE_M_SAND_TOMB}an{SE_M_YAWN}POKéMON!$"

Route36_Text_AlanRematchDefeat:
	.string "Oops{SE_M_DRAGON_RAGE}Computatio{SE_M_ATTRACT}error?$"

Route36_Text_AlanPostRematch:
	.string "Darn{SE_M_PERISH_SONG}{SE_M_HEAL_BELL}stud{SE_M_YAWN}fiv{SE_M_REVERSAL}hour{SE_M_GRASSWHISTLE}{SE_M_CHARGE}da{SE_M_YAWN}too.\p"
	.string "There'{SE_M_GRASSWHISTLE}mor{SE_M_REVERSAL}t{SE_M_ATTRACT2}learnin{SE_M_SANDSTORM}tha{SE_M_ATTRACT}just\n"
	.string "readin{SE_M_SANDSTORM}books.$"

Route36_Text_AlanHasItem:
	.string "Hey{SE_M_DRAGON_RAGE}{SE_M_HEAL_BELL}foun{SE_M_WATERFALL}something\n"
	.string "whil{SE_M_REVERSAL}studying!\p"
	.string "Here{SE_M_SUPERSONIC}yo{SE_M_DIVE}ca{SE_M_ATTRACT}hav{SE_M_REVERSAL}it!$"

Route36_Text_AlanGaveItem:
	.string "I'l{SE_M_BATON_PASS}le{SE_M_SPIT_UP}yo{SE_M_DIVE}kno{SE_M_TWISTER}i{SE_M_ACID_ARMOR}{SE_M_HEAL_BELL}find\n"
	.string "anythin{SE_M_SANDSTORM}else!$"

Route36_Text_AlanNoRoom:
	.string "Hmm{SE_M_SUPERSONIC}you{SE_M_SAND_TOMB}BA{SE_M_SWAGGER}i{SE_M_GRASSWHISTLE}full.\p"
	.string "Com{SE_M_REVERSAL}bac{SE_M_ENCORE2}whe{SE_M_ATTRACT}yo{SE_M_DIVE}hav{SE_M_REVERSAL}room.$"

