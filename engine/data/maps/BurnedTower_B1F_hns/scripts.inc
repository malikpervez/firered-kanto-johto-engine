@ Johto (data/maps/BurnedTower_B1F_hns/scripts.inc), as built into the FireRed game.

BurnedTower_B1F_hns_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, BurnedTower_B1F_OnFrame
	map_script MAP_SCRIPT_ON_TRANSITION, BurnedTower_B1F_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, J_SetTimeEncounters
	.byte 0

BurnedTower_B1F_OnTransition:
	callnative SetTimeBasedEncounters
	end

BurnedTower_B1F_OnFrame::
	map_script_2 JOHTO_VAR_ECRUTEAK_CITY_STATE, 3, BurnedTower_B1F_EventScript_ReleaseBeasts
	.2byte 0

BurnedTower_B1F_EventScript_ReleaseBeasts::
	lock
	turnobject OBJ_EVENT_ID_PLAYER, DIR_WEST
	delay 60
	turnobject OBJ_EVENT_ID_PLAYER, DIR_EAST
	delay 60
	playse SE_PIN
	applymovement OBJ_EVENT_ID_PLAYER, J_Common_Movement_ExclamationMark
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	delay 60

	playmoncry SPECIES_ENTEI, CRY_MODE_NORMAL
	applymovement LOCALID_BURNEDTOWER_ENTEI, BurnedTower_B1F_Movement_AwakenBeasts
	playse SE_LEDGE
	waitse
	playse SE_LEDGE
	waitse
	playse SE_LEDGE
	waitse
	waitmovement 0

	playmoncry SPECIES_RAIKOU, CRY_MODE_NORMAL
	applymovement LOCALID_BURNEDTOWER_RAIKOU, BurnedTower_B1F_Movement_AwakenBeasts
	playse SE_LEDGE
	waitse
	playse SE_LEDGE
	waitse
	playse SE_LEDGE
	waitse
	waitmovement 0

	playmoncry SPECIES_SUICUNE, CRY_MODE_NORMAL
	applymovement LOCALID_BURNEDTOWER_SUICUNE, BurnedTower_B1F_Movement_AwakenBeasts
	playse SE_LEDGE
	waitse
	playse SE_LEDGE
	waitse
	playse SE_LEDGE
	waitse
	waitmovement 0


	applymovement LOCALID_BURNEDTOWER_ENTEI, BurnedTower_B1F_Movement_EnteiLeave
	playse SE_LEDGE
	delay 30
	playse SE_LEDGE
	delay 30
	playse SE_LEDGE
	delay 30
	playse SE_LEDGE
	delay 30
	playse SE_LEDGE
	delay 30
	waitmovement 0

	applymovement LOCALID_BURNEDTOWER_RAIKOU, BurnedTower_B1F_Movement_RaikouLeave
	playse SE_LEDGE
	delay 30
	playse SE_LEDGE
	delay 30
	playse SE_LEDGE
	delay 30
	playse SE_LEDGE
	delay 30
	playse SE_LEDGE
	delay 30
	waitmovement 0

	applymovement LOCALID_BURNEDTOWER_SUICUNE, BurnedTower_B1F_Movement_SuicuneLeave
	delay 30
	playse SE_LEDGE
	delay 30
	playmoncry SPECIES_SUICUNE, CRY_MODE_NORMAL
	waitse
	playse SE_LEDGE
	delay 30
	playse SE_LEDGE
	delay 30
	playse SE_LEDGE
	delay 30
	playse SE_LEDGE
	delay 30
	playse SE_LEDGE
	waitmovement 0

	setflag JOHTO_FLAG_HIDE_BURNED_TOWER_BEASTS
	removeobject LOCALID_BURNEDTOWER_ENTEI
	removeobject LOCALID_BURNEDTOWER_RAIKOU
	removeobject LOCALID_BURNEDTOWER_SUICUNE
	delay 55

	playse SE_EXIT
	turnobject OBJ_EVENT_ID_PLAYER, DIR_EAST
	applymovement LOCALID_BURNEDTOWER2_EUSINE, BurnedTower_B1F_Movement_EusineEnter
	waitmovement 0
	msgbox BurnedTowerB1FEusineText, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_BURNEDTOWER2_EUSINE, BurnedTower_B1F_Movement_EusineLeave
	waitmovement 0
	playse SE_EXIT
	setflag JOHTO_FLAG_HIDE_BURNED_TOWER_B1F_EUSINE
	removeobject LOCALID_BURNEDTOWER2_EUSINE
	setflag JOHTO_FLAG_HIDE_BURNED_TOWER_NPCS
	setflag JOHTO_FLAG_HIDE_ECRUTEAK_CITY_SAGE
	special InitRoamer
	setflag JOHTO_FLAG_RELEASED_BEASTS
	setvar JOHTO_VAR_ECRUTEAK_CITY_STATE, 4
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
	finditem ITEM_TM_TAUNT
	end

BurnedTower_B1F_EventScript_Item_UltraBall::
	finditem ITEM_ULTRA_BALL
	end

