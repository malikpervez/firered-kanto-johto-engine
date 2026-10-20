@ Johto (data/maps/Route29_hns/scripts.inc), as built into the FireRed game.

Route29_hns_MapScripts::
	map_script 3, Route29_OnTransition
	map_script 5, J_SetTimeEncounters
	.byte 0

Route29_OnTransition:
	callnative SetTimeBasedEncounters
	end

Route29_Trigger_Monview::
	special SpawnCameraObject
	applymovement2 127, J_Common_Movement_WalkUp1
	waitmovement 0
	applymovement2 127, J_Common_Movement_WalkUp1
	waitmovement 0
	applymovement2 127, J_Common_Movement_WalkUp1
	waitmovement 0
	applymovement2 127, J_Common_Movement_WalkUp1
	waitmovement 0
	message Route29_Text_PressAorB
	waitbuttonpress
	closemessage
	applymovement2 127, J_Common_Movement_WalkDown1
	waitmovement 0
	applymovement2 127, J_Common_Movement_WalkDown1
	waitmovement 0
	applymovement2 127, J_Common_Movement_WalkDown1
	waitmovement 0
	applymovement2 127, J_Common_Movement_WalkDown1
	waitmovement 0
	special RemoveCameraObject
	applymovement2 255, J_Common_Movement_WalkDown1
	waitmovement 0
	end

Route29_Text_PressAorB:
	.string "Pres{SE_M_GRASSWHISTLE}{SE_M_BONEMERANG}o{SE_M_SAND_TOMB}{SE_M_LICK}t{SE_M_ATTRACT2}sto{SE_M_MORNING_SUN}viewing.$"

Route29_EventScript_OldMan::
	lock
	faceplayer
	goto_if_set 8660, Route29_EventScript_OldMan2
	msgbox Route29_Text_OldMan1, MSGBOX_DEFAULT
	closemessage
	release
	end

Route29_EventScript_OldMan2::
	msgbox Route29_Text_OldMan2, MSGBOX_YESNO
	goto_if_eq 32781, YES, Route29_EventScript_OldMan_Tutorial
	waitmessage
	msgbox Route29_Text_OldManDeclined, MSGBOX_DEFAULT
	closemessage
	release
	end

Route29_EventScript_OldMan_Tutorial::
	msgbox Route29_Text_OldManExplanation, MSGBOX_DEFAULT
	closemessage
	release
	end

Route29_EventScript_Lass::
	lock
	faceplayer
	msgbox Route29_Text_Lass, MSGBOX_DEFAULT
	closemessage
	release
	end

Route29_EventScript_Youngster::
	lock
	faceplayer
	msgbox Route29_Text_Youngster, MSGBOX_DEFAULT
	closemessage
	release
	end

Route29_EventScript_Tuscany::
	lock
	faceplayer
	goto_if_set 8735, Route29_EventScript_TuscanyCompleted
	msgbox Route29_Text_MeetTuscany, MSGBOX_DEFAULT
	closemessage
	multichoice 20, 0, 159, FALSE
	switch 32781
	case 0, Route29_EventScript_TuscanyNope
	case 1, Route29_EventScript_TuscanyNope
	case 2, Route29_EventScript_TuscanyYes
	case 3, Route29_EventScript_TuscanyNope
	case 4, Route29_EventScript_TuscanyNope
	case 5, Route29_EventScript_TuscanyNope
	case 6, Route29_EventScript_TuscanyNope
	case 7 Route29_EventScript_TuscanyCancel
	case 127, Route29_EventScript_TuscanyCancel
	closemessage
	release
	end

Route29_EventScript_TuscanyYes::
	msgbox Route29_Text_TuscanyGivesGift, MSGBOX_DEFAULT
	giveitem ITEM_SILK_SCARF
	goto_if_eq 32781, FALSE, J_Common_EventScript_ShowBagIsFull
	setflag 8735
	msgbox Route29_Text_TuscanyGaveGift, MSGBOX_DEFAULT
	closemessage
	release
	end

Route29_EventScript_TuscanyNope::
	msgbox Route29_Text_TuscanyNope, MSGBOX_DEFAULT
	closemessage
	release
	end

Route29_EventScript_TuscanyCancel::
	closemessage
	release
	end

Route29_EventScript_TuscanyCompleted::
	msgbox Route29_Text_TuscanyTuesday, MSGBOX_DEFAULT
	closemessage
	release
	end

Route29_EventScript_Girl::
	lock
	faceplayer
	msgbox Route29_Text_Girl, MSGBOX_DEFAULT
	closemessage
	release
	end

Route29_EventScript_Boy::
	lock
	faceplayer
	goto_if_set 8797, Route29_EventScript_Boy2
	msgbox Route29_Text_Boy_WaitingForDay, MSGBOX_DEFAULT
	closemessage
	release
	end

Route29_EventScript_Boy2::
	msgbox Route29_Text_Boy_WaitingForNight, MSGBOX_DEFAULT
	closemessage
	release
	end

Route29_EventScript_Sign::
	lock
	msgbox Route29_Text_Sign1, MSGBOX_SIGN
	closemessage
	release
	end

Route29_EventScript_ItemPotion::
	finditem ITEM_POTION
	end

Route29_Text_OldMan1:
	.string "POKéMO{SE_M_PSYBEAM2}hid{SE_M_REVERSAL}i{SE_M_ATTRACT}th{SE_M_REVERSAL}grass.\n"
	.string "Wh{SE_M_ATTRACT2}know{SE_M_GRASSWHISTLE}whe{SE_M_ATTRACT}they'l{SE_M_BATON_PASS}po{SE_M_MORNING_SUN}out…$"

Route29_Text_OldMan2:
	.string "Welcom{SE_M_REVERSAL}back{SE_M_SUPERSONIC}{PLAYER}{SE_M_DRAGON_RAGE}Looking\nfo{SE_M_SAND_TOMB}ne{SE_M_TWISTER}POKéMO{SE_M_PSYBEAM2}i{SE_M_ATTRACT}JOHTO?\pWoul{SE_M_WATERFALL}yo{SE_M_DIVE}lik{SE_M_REVERSAL}{SE_M_CHARGE}quic{SE_M_ENCORE2}reminder\nabou{SE_M_SPIT_UP}catchin{SE_M_SANDSTORM}them?$"

Route29_Text_OldManExplanation:
	.string "I{SE_M_ACID_ARMOR}yo{SE_M_DIVE}weake{SE_M_ATTRACT}the{SE_M_MILK_DRINK}first,\n"
	.string "POKéMO{SE_M_PSYBEAM2}ar{SE_M_REVERSAL}easie{SE_M_SAND_TOMB}t{SE_M_ATTRACT2}catch.\p"
	.string "Then{SE_M_SUPERSONIC}thro{SE_M_TWISTER}{SE_M_CHARGE}bal{SE_M_BATON_PASS}a{SE_M_SPIT_UP}the{SE_M_MILK_DRINK}from\n"
	.string "you{SE_M_SAND_TOMB}bag{SE_M_DRAGON_RAGE}An{SE_M_YAWN}bal{SE_M_BATON_PASS}wil{SE_M_BATON_PASS}do.\p"
	.string "I{SE_M_ACID_ARMOR}yo{SE_M_DIVE}wan{SE_M_SPIT_UP}t{SE_M_ATTRACT2}lear{SE_M_ATTRACT}more,\n"
	.string "g{SE_M_ATTRACT2}t{SE_M_ATTRACT2}th{SE_M_REVERSAL}ACADEM{SE_M_MOONLIGHT}i{SE_M_ATTRACT}VIOLE{SE_M_SWIFT}CITY!\p"
	.string "Th{SE_M_REVERSAL}student{SE_M_GRASSWHISTLE}ther{SE_M_REVERSAL}kno{SE_M_TWISTER}{SE_M_CHARGE}lot\n"
	.string "abou{SE_M_SPIT_UP}POKéMON.$"

Route29_Text_OldManDeclined:
	.string "Oh{SE_M_PERISH_SONG}Fine{SE_M_SUPERSONIC}then.\p"
	.string "Chec{SE_M_ENCORE2}ever{SE_M_YAWN}rout{SE_M_REVERSAL}t{SE_M_ATTRACT2}find\n"
	.string "differen{SE_M_SPIT_UP}type{SE_M_GRASSWHISTLE}o{SE_M_ACID_ARMOR}POKéMON.\p"
	.string "You{SE_M_SAND_TOMB}POKéDE{SE_M_LOCK_ON}show{SE_M_GRASSWHISTLE}wher{SE_M_REVERSAL}yo{SE_M_DIVE}can\n"
	.string "fin{SE_M_WATERFALL}the{SE_M_MILK_DRINK}too!\p"
	.string "I{SE_M_ACID_ARMOR}yo{SE_M_DIVE}wan{SE_M_SPIT_UP}t{SE_M_ATTRACT2}lear{SE_M_ATTRACT}more,\n"
	.string "g{SE_M_ATTRACT2}t{SE_M_ATTRACT2}th{SE_M_REVERSAL}ACADEM{SE_M_MOONLIGHT}i{SE_M_ATTRACT}VIOLE{SE_M_SWIFT}CITY!\p"
	.string "Th{SE_M_REVERSAL}student{SE_M_GRASSWHISTLE}kno{SE_M_TWISTER}{SE_M_CHARGE}lo{SE_M_SPIT_UP}about\n"
	.string "POKéMON.$"

Route29_Text_Youngster:
	.string "Yo{SE_M_PERISH_SONG}Ho{SE_M_TWISTER}ar{SE_M_REVERSAL}you{SE_M_SAND_TOMB}POKéMON?\p"
	.string "I{SE_M_ACID_ARMOR}they'r{SE_M_REVERSAL}wea{SE_M_ENCORE2}an{SE_M_WATERFALL}no{SE_M_SPIT_UP}ready\n"
	.string "fo{SE_M_SAND_TOMB}battle{SE_M_SUPERSONIC}kee{SE_M_MORNING_SUN}ou{SE_M_SPIT_UP}o{SE_M_ACID_ARMOR}th{SE_M_REVERSAL}grass.$"

Route29_Text_Lass:
	.string "Se{SE_M_REVERSAL}thos{SE_M_REVERSAL}ledges?\n"
	.string "It'{SE_M_GRASSWHISTLE}scar{SE_M_YAWN}t{SE_M_ATTRACT2}jum{SE_M_MORNING_SUN}of{SE_M_ACID_ARMOR}them.\p"
	.string "Bu{SE_M_SPIT_UP}yo{SE_M_DIVE}ca{SE_M_ATTRACT}g{SE_M_ATTRACT2}t{SE_M_ATTRACT2}NE{SE_M_DETECT}BARK\n"
	.string "withou{SE_M_SPIT_UP}walkin{SE_M_SANDSTORM}throug{SE_M_TRI_ATTACK}th{SE_M_REVERSAL}grass.$"

Route29_Text_Girl:
	.string "{SE_M_HEAL_BELL}wante{SE_M_WATERFALL}t{SE_M_ATTRACT2}tak{SE_M_REVERSAL}{SE_M_CHARGE}break,\n"
	.string "s{SE_M_ATTRACT2}{SE_M_HEAL_BELL}save{SE_M_WATERFALL}t{SE_M_ATTRACT2}recor{SE_M_WATERFALL}m{SE_M_YAWN}progress.$"

Route29_Text_Boy_WaitingForDay:
	.string "I'{SE_M_MILK_DRINK}waitin{SE_M_SANDSTORM}fo{SE_M_SAND_TOMB}POKéMO{SE_M_PSYBEAM2}that\n"
	.string "appea{SE_M_SAND_TOMB}onl{SE_M_YAWN}late{SE_M_SAND_TOMB}i{SE_M_ATTRACT}th{SE_M_REVERSAL}day.$"

Route29_Text_Boy_WaitingForNight:
	.string "I'{SE_M_MILK_DRINK}waitin{SE_M_SANDSTORM}fo{SE_M_SAND_TOMB}POKéMO{SE_M_PSYBEAM2}that\n"
	.string "appea{SE_M_SAND_TOMB}onl{SE_M_YAWN}a{SE_M_SPIT_UP}night.$"

Route29_Text_MeetTuscany:
	.string "TUSCANY{SE_M_HEAT_WAVE}{SE_M_HEAL_BELL}d{SE_M_ATTRACT2}believ{SE_M_REVERSAL}tha{SE_M_SPIT_UP}this\n"
	.string "i{SE_M_GRASSWHISTLE}th{SE_M_REVERSAL}firs{SE_M_SPIT_UP}tim{SE_M_REVERSAL}we'v{SE_M_REVERSAL}met?\p"
	.string "I'{SE_M_MILK_DRINK}TUSCAN{SE_M_MOONLIGHT}o{SE_M_ACID_ARMOR}th{SE_M_REVERSAL}WEEKDA{SE_M_MOONLIGHT}FAMILY.\p"
	.string "I{SE_M_ACID_ARMOR}yo{SE_M_DIVE}ca{SE_M_ATTRACT}gues{SE_M_GRASSWHISTLE}m{SE_M_YAWN}favorit{SE_M_REVERSAL}day,\n"
	.string "I'l{SE_M_BATON_PASS}giv{SE_M_REVERSAL}yo{SE_M_DIVE}{SE_M_CHARGE}reward.$"

Route29_Text_TuscanyNope:
	.string "No{SE_M_SPIT_UP}quite!$"

Route29_Text_TuscanyGivesGift:
	.string "Yes{SE_M_DRAGON_RAGE}B{SE_M_YAWN}wa{SE_M_YAWN}o{SE_M_ACID_ARMOR}introduction,\n"
	.string "pleas{SE_M_REVERSAL}accep{SE_M_SPIT_UP}thi{SE_M_GRASSWHISTLE}gift{SE_M_SUPERSONIC}{SE_M_CHARGE}SILK\l"
	.string "SCARF.$"

Route29_Text_TuscanyGaveGift:
	.string "TUSCANY{SE_M_HEAT_WAVE}Wouldn'{SE_M_SPIT_UP}yo{SE_M_DIVE}agree\n"
	.string "tha{SE_M_SPIT_UP}i{SE_M_SPIT_UP}i{SE_M_GRASSWHISTLE}mos{SE_M_SPIT_UP}adorable?\p"
	.string "I{SE_M_SPIT_UP}strengthen{SE_M_GRASSWHISTLE}NORMAL-type\n"
	.string "moves.\p"
	.string "{SE_M_HEAL_BELL}a{SE_M_MILK_DRINK}certai{SE_M_ATTRACT}i{SE_M_SPIT_UP}wil{SE_M_BATON_PASS}b{SE_M_REVERSAL}o{SE_M_ACID_ARMOR}use.$"

Route29_Text_TuscanyTuesday:
	.string "TUSCANY{SE_M_HEAT_WAVE}Hav{SE_M_REVERSAL}yo{SE_M_DIVE}me{SE_M_SPIT_UP}MONICA,\n"
	.string "m{SE_M_YAWN}olde{SE_M_SAND_TOMB}sister?\p"
	.string "O{SE_M_SAND_TOMB}m{SE_M_YAWN}younge{SE_M_SAND_TOMB}brother{SE_M_SUPERSONIC}WESLEY?\p"
	.string "{SE_M_HEAL_BELL}a{SE_M_MILK_DRINK}th{SE_M_REVERSAL}thir{SE_M_WATERFALL}o{SE_M_ACID_ARMOR}seven\n"
	.string "children.$"

Route29_Text_Sign1:
	.string "ROUT{SE_M_SWORDS_DANCE}29\p"
	.string "CHERRYGROV{SE_M_SWORDS_DANCE}CIT{SE_M_MOONLIGHT}{SE_M_PAY_DAY}NE{SE_M_DETECT}BAR{SE_M_SNORE}TOWN$"

