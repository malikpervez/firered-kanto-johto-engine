@ Johto (data/maps/VictoryRoadKanto_1F_hns/scripts.inc), as built into the FireRed game.

VictoryRoadKanto_1F_hns_MapScripts::
	.byte 0

VictoryRoadKanto_1F_EventScript_Item_RareCandy::
	finditem ITEM_RARE_CANDY
	end

VictoryRoadKanto_1F_EventScript_Item_MaxEther::
	finditem ITEM_MAX_ETHER
	end

VictoryRoadKanto_EventScript_Item_Dark_Pulse::
	finditem 660
	end

VictoryRoadKanto_1F_Trigger::
	lock
	playbgm ((558 + 1) + 0x3B), FALSE
	delay 5
	playse 21
	applymovement2 255, J_Common_Movement_ExclamationMark
	waitmovement 255
	addobject 13
	getplayerxy 16384, 16385
	call_if_eq 16384, 27, VictoryRoadKanto_1F_EventScript_SilverEnterLeft
	call_if_eq 16384, 28, VictoryRoadKanto_1F_EventScript_SilverEnterMid
	call_if_eq 16384, 29, VictoryRoadKanto_1F_EventScript_SilverEnterRight
	msgbox VictoryRoad_Text_RivalBefore, MSGBOX_DEFAULT
	call_if_eq 20499, 0, VictoryRoadKanto_1F_Silver_Battle_Cyndaquil
	call_if_eq 20499, 1, VictoryRoadKanto_1F_Silver_Battle_Totodile
	call_if_eq 20499, 2, VictoryRoadKanto_1F_Silver_Battle_Chikorita
	playbgm ((558 + 1) + 0x3C), FALSE
	msgbox VictoryRoad_Text_RivalAfter, MSGBOX_DEFAULT
	closemessage
	applymovement2 13, VictoryRoadKanto_1F_Movement_SilverLeave
	waitmovement 0
	removeobject 13
	fadedefaultbgm
	release
	setvar 20594, 3
	end

VictoryRoadKanto_1F_EventScript_SilverEnterLeft::
	applymovement2 13, VictoryRoadKanto_1F_Movement_SilverEnterLeft
	applymovement2 255, J_Common_Movement_WalkDown1
	applymovement2 0xFE, J_Common_Movement_WalkUp1
	waitmovement 13
	return

VictoryRoadKanto_1F_EventScript_SilverEnterMid::
	applymovement2 13, VictoryRoadKanto_1F_Movement_SilverEnterMid
	applymovement2 255, J_Common_Movement_WalkDown1
	applymovement2 0xFE, J_Common_Movement_WalkUp1
	waitmovement 13
	return

VictoryRoadKanto_1F_EventScript_SilverEnterRight::
	applymovement2 13, VictoryRoadKanto_1F_Movement_SilverEnterRight
	applymovement2 255, J_Common_Movement_WalkDown1
	applymovement2 0xFE, J_Common_Movement_WalkUp1
	waitmovement 13
	return

VictoryRoadKanto_1F_Silver_Battle_Cyndaquil::
	trainerbattle_no_intro 1478, VictoryRoad_Text_RivalDefeat
	return

VictoryRoadKanto_1F_Silver_Battle_Totodile::
	trainerbattle_no_intro 1485, VictoryRoad_Text_RivalDefeat
	return

VictoryRoadKanto_1F_Silver_Battle_Chikorita::
	trainerbattle_no_intro 1471, VictoryRoad_Text_RivalDefeat
	return

VictoryRoadKanto_1F_Movement_SilverEnterLeft:
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_up
	walk_up
	step_end

VictoryRoadKanto_1F_Movement_SilverEnterMid:
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_up
	walk_up
	step_end

VictoryRoadKanto_1F_Movement_SilverEnterRight:
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_up
	walk_up
	step_end

VictoryRoadKanto_1F_Movement_SilverLeave:
	walk_down
	walk_down
	walk_left
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

VictoryRoad_Text_RivalBefore:
	.string "Hol{SE_M_WATERFALL}it.\p"
	.string "…Ar{SE_M_REVERSAL}yo{SE_M_DIVE}goin{SE_M_SANDSTORM}t{SE_M_ATTRACT2}tak{SE_M_REVERSAL}th{SE_M_REVERSAL}POKéMON\n"
	.string "LEAGU{SE_M_SWORDS_DANCE}challenge?\p"
	.string "…Don'{SE_M_SPIT_UP}mak{SE_M_REVERSAL}m{SE_M_REVERSAL}laugh.\p"
	.string "You'r{SE_M_REVERSAL}s{SE_M_ATTRACT2}muc{SE_M_TRI_ATTACK}weake{SE_M_SAND_TOMB}tha{SE_M_ATTRACT}{SE_M_HEAL_BELL}am.\p"
	.string "I'{SE_M_MILK_DRINK}no{SE_M_SPIT_UP}lik{SE_M_REVERSAL}{SE_M_HEAL_BELL}wa{SE_M_GRASSWHISTLE}before.\p"
	.string "{SE_M_HEAL_BELL}no{SE_M_TWISTER}hav{SE_M_REVERSAL}th{SE_M_REVERSAL}bes{SE_M_SPIT_UP}an{SE_M_WATERFALL}strongest\n"
	.string "POKéMO{SE_M_PSYBEAM2}wit{SE_M_TRI_ATTACK}me.\p"
	.string "I'{SE_M_MILK_DRINK}invincible!\p"
	.string "{PLAYER}!\n"
	.string "{SE_M_HEAL_BELL}challeng{SE_M_REVERSAL}you!$"

VictoryRoad_Text_RivalDefeat:
	.string "…{SE_M_HEAL_BELL}couldn'{SE_M_SPIT_UP}win…\p"
	.string "{SE_M_HEAL_BELL}gav{SE_M_REVERSAL}i{SE_M_SPIT_UP}every-thin{SE_M_SANDSTORM}{SE_M_HEAL_BELL}had…\p"
	.string "Wha{SE_M_SPIT_UP}yo{SE_M_DIVE}possess{SE_M_SUPERSONIC}an{SE_M_WATERFALL}wha{SE_M_SPIT_UP}{SE_M_HEAL_BELL}lack…\p"
	.string "I'{SE_M_MILK_DRINK}beginnin{SE_M_SANDSTORM}t{SE_M_ATTRACT2}understan{SE_M_WATERFALL}what\n"
	.string "tha{SE_M_SPIT_UP}drago{SE_M_ATTRACT}maste{SE_M_SAND_TOMB}sai{SE_M_WATERFALL}t{SE_M_ATTRACT2}me…$"

VictoryRoad_Text_RivalAfter:
	.string "…{SE_M_HEAL_BELL}haven'{SE_M_SPIT_UP}give{SE_M_ATTRACT}u{SE_M_MORNING_SUN}o{SE_M_ATTRACT}becomin{SE_M_SANDSTORM}the\n"
	.string "greates{SE_M_SPIT_UP}trainer…\p"
	.string "I'{SE_M_MILK_DRINK}goin{SE_M_SANDSTORM}t{SE_M_ATTRACT2}fin{SE_M_WATERFALL}ou{SE_M_SPIT_UP}wh{SE_M_YAWN}{SE_M_HEAL_BELL}can't\n"
	.string "wi{SE_M_ATTRACT}an{SE_M_WATERFALL}becom{SE_M_REVERSAL}stronger…\p"
	.string "Whe{SE_M_ATTRACT}{SE_M_HEAL_BELL}do{SE_M_SUPERSONIC}{SE_M_HEAL_BELL}wil{SE_M_BATON_PASS}challeng{SE_M_REVERSAL}you.\p"
	.string "An{SE_M_WATERFALL}I'l{SE_M_BATON_PASS}bea{SE_M_SPIT_UP}yo{SE_M_DIVE}dow{SE_M_ATTRACT}wit{SE_M_TRI_ATTACK}al{SE_M_BATON_PASS}my\n"
	.string "power.\p"
	.string "…Humph{SE_M_DRAGON_RAGE}Yo{SE_M_DIVE}kee{SE_M_MORNING_SUN}a{SE_M_SPIT_UP}i{SE_M_SPIT_UP}unti{SE_M_BATON_PASS}then.$"

