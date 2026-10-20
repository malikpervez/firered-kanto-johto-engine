@ Johto (data/maps/SlowpokeWell_B2F_hns/scripts.inc), as built into the FireRed game.

SlowpokeWell_B2F_hns_MapScripts::
	.byte 0

SlowpokeWell_EventScript_Item_Kings_Rock::
	finditem ITEM_KINGS_ROCK
	end

SlowpokeWell_EventScript_Slowking::
	lock
	faceplayer
	playmoncry 199, 0
	msgbox SlowpokeWell_Text_Slowking, MSGBOX_DEFAULT
	waitmoncry
	closemessage
	goto_if_set 8439, SlowpokeWell_EventScript_Slowking2
	playmoncry 199, 0
	applymovement 1, SlowpokeWell_Movement_RainDance1
	waitmovement 0
	delay 55
	playmoncry 199, 0
	applymovement 1, SlowpokeWell_Movement_RainDance2
	waitmovement 0
	delay 55
	playmoncry 199, 0
	applymovement 1, SlowpokeWell_Movement_RainDance3
	waitmovement 0
	delay 55
	playmoncry 199, 0
	applymovement 1, SlowpokeWell_Movement_RainDance4
	waitmovement 0
	delay 55
	playmoncry 199, 0
	setweather 3
	doweather
	waitmoncry
	giveitem 599
	goto_if_eq 32781, FALSE, J_Common_EventScript_BagIsFull
	setflag 8439
	release
	end

SlowpokeWell_EventScript_Slowking2::
	setweather 3
	doweather
	release
	end

SlowpokeWell_Movement_RainDance1:
	face_right
	delay_8
	walk_in_place_fast_right
	walk_in_place_fast_right
	walk_in_place_fast_right
	delay_8
	step_end

SlowpokeWell_Movement_RainDance2:
	face_left
	walk_in_place_fast_left
	walk_in_place_fast_left
	walk_in_place_fast_left
	delay_8
	step_end

SlowpokeWell_Movement_RainDance3:
	face_down
	lock_facing_direction
	walk_fast_right
	walk_fast_left
	unlock_facing_direction
	delay_8
	step_end

SlowpokeWell_Movement_RainDance4:
	lock_facing_direction
	walk_fast_left
	walk_fast_right
	unlock_facing_direction
	step_end

SlowpokeWell_Text_Slowking:
	.string "SLOWKING{SE_M_HEAT_WAVE}........................$"

