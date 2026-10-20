@ Johto (data/maps/BurnedTower_B1F_hns/scripts.inc), as built into the FireRed game.

BurnedTower_B1F_hns_MapScripts::
	map_script 2,BurnedTower_B1F_OnFrame
	map_script 3, BurnedTower_B1F_OnTransition
	map_script 5, J_SetTimeEncounters
	.byte 0

BurnedTower_B1F_OnTransition:
	callnative SetTimeBasedEncounters
	end

BurnedTower_B1F_OnFrame::
	map_script_2 20561, 3, BurnedTower_B1F_EventScript_ReleaseBeasts
	.2byte 0

BurnedTower_B1F_EventScript_ReleaseBeasts::
	lock
	turnobject 255, DIR_WEST
	delay 60
	turnobject 255, DIR_EAST
	delay 60
	playse 21
	applymovement 255, J_Common_Movement_ExclamationMark
	turnobject 255, DIR_NORTH
	delay 60

	playmoncry 244, 0
	applymovement 1, BurnedTower_B1F_Movement_AwakenBeasts
	playse 10
	waitse
	playse 10
	waitse
	playse 10
	waitse
	waitmovement 0

	playmoncry 243, 0
	applymovement 2, BurnedTower_B1F_Movement_AwakenBeasts
	playse 10
	waitse
	playse 10
	waitse
	playse 10
	waitse
	waitmovement 0

	playmoncry 245, 0
	applymovement 3, BurnedTower_B1F_Movement_AwakenBeasts
	playse 10
	waitse
	playse 10
	waitse
	playse 10
	waitse
	waitmovement 0


	applymovement 1, BurnedTower_B1F_Movement_EnteiLeave
	playse 10
	delay 30
	playse 10
	delay 30
	playse 10
	delay 30
	playse 10
	delay 30
	playse 10
	delay 30
	waitmovement 0

	applymovement 2, BurnedTower_B1F_Movement_RaikouLeave
	playse 10
	delay 30
	playse 10
	delay 30
	playse 10
	delay 30
	playse 10
	delay 30
	playse 10
	delay 30
	waitmovement 0

	applymovement 3, BurnedTower_B1F_Movement_SuicuneLeave
	delay 30
	playse 10
	delay 30
	playmoncry 245, 0
	waitse
	playse 10
	delay 30
	playse 10
	delay 30
	playse 10
	delay 30
	playse 10
	delay 30
	playse 10
	waitmovement 0

	setflag 8238
	removeobject 1
	removeobject 2
	removeobject 3
	delay 55

	playse 9
	turnobject 255, DIR_EAST
	applymovement 11, BurnedTower_B1F_Movement_EusineEnter
	waitmovement 0
	msgbox BurnedTowerB1FEusineText, MSGBOX_DEFAULT
	closemessage
	applymovement 11, BurnedTower_B1F_Movement_EusineLeave
	waitmovement 0
	playse 9
	setflag 8315
	removeobject 11
	setflag 8316
	setflag 8309
	special InitRoamer
	setflag 8664
	setvar 20561, 4
	release
	end

BurnedTower_B1F_Movement_AwakenBeasts:
	jump_in_place_down
	jump_in_place_down
	jump_in_place_down
	step_end

BurnedTower_B1F_Movement_EnteiLeave:
	jump_down
	jump_2_right
	jump_2_right
	jump_2_right
	jump_2_right
	step_end

BurnedTower_B1F_Movement_RaikouLeave:
	jump_down
	jump_2_left
	jump_2_left
	jump_2_left
	jump_2_left
	step_end

BurnedTower_B1F_Movement_SuicuneLeave:
	jump_2_down
	delay_8
	jump_in_place_right_left
	jump_in_place_right_left
	jump_left
	jump_2_down
	jump_2_down
	jump_2_down
	step_end

BurnedTower_B1F_Movement_EusineEnter:
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	step_end

BurnedTower_B1F_Movement_EusineLeave:
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_right
	walk_fast_right
	walk_fast_right
	step_end

BurnedTowerB1FEusineText:
	.string "EUSINE{SE_M_HEAT_WAVE}I'{SE_M_MILK_DRINK}shocked!\p"
	.string "SUICUN{SE_M_SWORDS_DANCE}race{SE_M_WATERFALL}b{SE_M_YAWN}lik{SE_M_REVERSAL}{SE_M_CHARGE}blur,\n"
	.string "righ{SE_M_SPIT_UP}i{SE_M_ATTRACT}fron{SE_M_SPIT_UP}o{SE_M_ACID_ARMOR}m{SE_M_YAWN}eyes!\p"
	.string "Fo{SE_M_SAND_TOMB}te{SE_M_ATTRACT}year{SE_M_GRASSWHISTLE}{SE_M_HEAL_BELL}chased\n"
	.string "SUICUNE{SE_M_SUPERSONIC}an{SE_M_WATERFALL}{SE_M_HEAL_BELL}finall{SE_M_YAWN}go{SE_M_SPIT_UP}to\l"
	.string "se{SE_M_REVERSAL}it.\p"
	.string "I'{SE_M_MILK_DRINK}al{SE_M_BATON_PASS}choke{SE_M_WATERFALL}up!\p"
	.string "{PLAYER}{SE_M_SUPERSONIC}{SE_M_HEAL_BELL}ow{SE_M_REVERSAL}thi{SE_M_GRASSWHISTLE}al{SE_M_BATON_PASS}t{SE_M_ATTRACT2}you!\p"
	.string "Than{SE_M_ENCORE2}you!\p"
	.string "{SE_M_HEAL_BELL}hear{SE_M_WATERFALL}tha{SE_M_SPIT_UP}th{SE_M_REVERSAL}legendary\n"
	.string "POKéMO{SE_M_PSYBEAM2}o{SE_M_ACID_ARMOR}ECRUTEA{SE_M_SNORE}test\l"
	.string "chose{SE_M_ATTRACT}human{SE_M_GRASSWHISTLE}b{SE_M_YAWN}allowin{SE_M_SANDSTORM}them\l"
	.string "t{SE_M_ATTRACT2}ge{SE_M_SPIT_UP}close.\p"
	.string "I'{SE_M_MILK_DRINK}goin{SE_M_SANDSTORM}t{SE_M_ATTRACT2}trac{SE_M_ENCORE2}SUICUNE.\p"
	.string "{PLAYER}{SE_M_SUPERSONIC}let'{SE_M_GRASSWHISTLE}mee{SE_M_SPIT_UP}again!\p"
	.string "Farewell!$"

BurnedTower_B1F_EventScript_Item_Taunt::
	finditem 593
	end

BurnedTower_B1F_EventScript_Item_UltraBall::
	finditem ITEM_ULTRA_BALL
	end

