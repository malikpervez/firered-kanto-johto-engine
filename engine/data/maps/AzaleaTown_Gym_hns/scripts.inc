@ Johto (data/maps/AzaleaTown_Gym_hns/scripts.inc), as built into the FireRed game.

AzaleaTown_Gym_hns_MapScripts::
	map_script 3, AzaleaTown_Gym_OnTransition
	.byte 0

AzaleaTown_Gym_OnTransition::
	setflag 8231
	setflag 8232
	setflag 8233
	end

AzaleaTown_Gym_EventScript_Trigger_1::
	lock
	turnobject 255, DIR_NORTH
	clearflag 8231
	addobject 8
	SetObjectSubpriority 255, MAP_AZALEA_TOWN_GYM_HNS, 0
	applymovement 8, AzaleaTown_Gym_Movement_Ariados_Down
	waitmovement 0
	turnobject 8, DIR_NORTH
	delay 30
	applymovement 255, J_Common_Movement_JumpUp1
	playse 10
	waitmovement 0
	waitmovement 0
	applymovement 8, AzaleaTown_Gym_Movement_Ariados_Up
	applymovement 255, AzaleaTown_Gym_Movement_Player_Up
	waitmovement 0
	waitmovement 0

	applymovement 8, AzaleaTown_Gym_Movement_Ariados_Right
	applymovement 255, AzaleaTown_Gym_Movement_Player_Right
	waitmovement 0
	waitmovement 0
	turnobject 255, DIR_NORTH
	applymovement 8, AzaleaTown_Gym_Movement_Ariados_Up
	applymovement 255, AzaleaTown_Gym_Movement_Player_Up
	waitmovement 0
	applymovement 255, J_Common_Movement_JumpUp1
	waitmovement 0
	applymovement 8, AzaleaTown_Gym_Movement_Ariados_Down
	waitmovement 0
	setflag 8231
	removeobject 8
	resetobjectsubpriority 255, MAP_AZALEA_TOWN_GYM_HNS
	release
	end

AzaleaTown_Gym_EventScript_Trigger_5::
	lock
	turnobject 255, DIR_SOUTH
	clearflag 8232
	addobject 9
	SetObjectSubpriority 255, MAP_AZALEA_TOWN_GYM_HNS, 0
	applymovement 9, AzaleaTown_Gym_Movement_Ariados_Up
	waitmovement 0
	turnobject 9, DIR_SOUTH
	delay 30
	applymovement 255, J_Common_Movement_JumpDown1
	playse 10
	waitmovement 0
	waitmovement 0
	applymovement 9, AzaleaTown_Gym_Movement_Ariados_Down
	delay 3
	applymovement 255, AzaleaTown_Gym_Movement_Player_Down
	waitmovement 0
	waitmovement 0

	applymovement 9, AzaleaTown_Gym_Movement_Ariados_Left
	applymovement 255, AzaleaTown_Gym_Movement_Player_Left
	waitmovement 0
	waitmovement 0
	turnobject 255, DIR_SOUTH
	applymovement 9, AzaleaTown_Gym_Movement_Ariados_Down
	delay 3
	applymovement 255, AzaleaTown_Gym_Movement_Player_Down
	waitmovement 0
	applymovement 255, J_Common_Movement_JumpDown1
	playse 10
	waitmovement 0
	applymovement 9, AzaleaTown_Gym_Movement_Ariados_Up
	waitmovement 0
	setflag 8232
	removeobject 9
	resetobjectsubpriority 255, MAP_AZALEA_TOWN_GYM_HNS
	release
	end

AzaleaTown_Gym_EventScript_Trigger_2::
	lock
	turnobject 255, DIR_NORTH
	clearflag 8232
	addobject 9
	SetObjectSubpriority 255, MAP_AZALEA_TOWN_GYM_HNS, 0
	applymovement 9, AzaleaTown_Gym_Movement_Ariados_Down
	waitmovement 0
	turnobject 9, DIR_NORTH
	delay 30
	applymovement 255, J_Common_Movement_JumpUp1
	playse 10
	waitmovement 0
	waitmovement 0
	applymovement 9, AzaleaTown_Gym_Movement_Ariados_Up
	applymovement 255, AzaleaTown_Gym_Movement_Player_Up
	waitmovement 0
	waitmovement 0

	applymovement 9, AzaleaTown_Gym_Movement_Ariados_Right
	applymovement 255, AzaleaTown_Gym_Movement_Player_Right
	waitmovement 0
	waitmovement 0
	turnobject 255, DIR_NORTH
	applymovement 9, AzaleaTown_Gym_Movement_Ariados_Up
	applymovement 255, AzaleaTown_Gym_Movement_Player_Up
	waitmovement 0
	applymovement 255, J_Common_Movement_JumpUp1
	playse 10
	waitmovement 0
	applymovement 9, AzaleaTown_Gym_Movement_Ariados_Down
	waitmovement 0
	setflag 8232
	removeobject 9
	resetobjectsubpriority 255, MAP_AZALEA_TOWN_GYM_HNS
	release
	end

AzaleaTown_Gym_EventScript_Trigger_6::
	lock
	turnobject 255, DIR_SOUTH
	clearflag 8233
	addobject 10
	SetObjectSubpriority 255, MAP_AZALEA_TOWN_GYM_HNS, 0
	applymovement 10, AzaleaTown_Gym_Movement_Ariados_Up
	waitmovement 0
	turnobject 10, DIR_SOUTH
	delay 30
	applymovement 255, J_Common_Movement_JumpDown1
	playse 10
	waitmovement 0
	waitmovement 0
	applymovement 10, AzaleaTown_Gym_Movement_Ariados_Down
	delay 3
	applymovement 255, AzaleaTown_Gym_Movement_Player_Down
	waitmovement 0
	waitmovement 0

	applymovement 10, AzaleaTown_Gym_Movement_Ariados_Left
	applymovement 255, AzaleaTown_Gym_Movement_Player_Left
	waitmovement 0
	waitmovement 0
	turnobject 255, DIR_SOUTH
	applymovement 10, AzaleaTown_Gym_Movement_Ariados_Down
	delay 3
	applymovement 255, AzaleaTown_Gym_Movement_Player_Down
	waitmovement 0
	applymovement 255, J_Common_Movement_JumpDown1
	playse 10
	waitmovement 0
	applymovement 10, AzaleaTown_Gym_Movement_Ariados_Up
	waitmovement 0
	setflag 8233
	removeobject 10
	resetobjectsubpriority 255, MAP_AZALEA_TOWN_GYM_HNS
	release
	end

AzaleaTown_Gym_EventScript_Trigger_3::
	lock
	turnobject 255, DIR_NORTH
	clearflag 8233
	addobject 10
	SetObjectSubpriority 255, MAP_AZALEA_TOWN_GYM_HNS, 0
	applymovement 10, AzaleaTown_Gym_Movement_Ariados_Down
	waitmovement 0
	turnobject 10, DIR_NORTH
	delay 30
	applymovement 255, J_Common_Movement_JumpUp1
	playse 10
	waitmovement 0
	waitmovement 0
	applymovement 10, AzaleaTown_Gym_Movement_Ariados_Up
	applymovement 255, AzaleaTown_Gym_Movement_Player_Up
	waitmovement 0
	waitmovement 0

	applymovement 10, AzaleaTown_Gym_Movement_Ariados_Left
	applymovement 255, AzaleaTown_Gym_Movement_Player_Left
	waitmovement 0
	waitmovement 0
	applymovement 10, AzaleaTown_Gym_Movement_Ariados_Left
	applymovement 255, AzaleaTown_Gym_Movement_Player_Left
	waitmovement 0
	waitmovement 0
	turnobject 255, DIR_NORTH
	applymovement 10, AzaleaTown_Gym_Movement_Ariados_Up
	applymovement 255, AzaleaTown_Gym_Movement_Player_Up
	waitmovement 0
	applymovement 255, J_Common_Movement_JumpUp1
	playse 10
	waitmovement 0
	applymovement 10, AzaleaTown_Gym_Movement_Ariados_Down
	waitmovement 0
	setflag 8233
	removeobject 10
	resetobjectsubpriority 255, MAP_AZALEA_TOWN_GYM_HNS
	release
	end

AzaleaTown_Gym_EventScript_Trigger_4::
	lock
	turnobject 255, DIR_SOUTH
	clearflag 8231
	addobject 8
	SetObjectSubpriority 255, MAP_AZALEA_TOWN_GYM_HNS, 0
	applymovement 8, AzaleaTown_Gym_Movement_Ariados_Up
	waitmovement 0
	turnobject 8, DIR_SOUTH
	delay 30
	applymovement 255, J_Common_Movement_JumpDown1
	playse 10
	waitmovement 0
	waitmovement 0
	applymovement 8, AzaleaTown_Gym_Movement_Ariados_Down
	delay 3
	applymovement 255, AzaleaTown_Gym_Movement_Player_Down
	waitmovement 0
	waitmovement 0

	applymovement 8, AzaleaTown_Gym_Movement_Ariados_Right
	applymovement 255, AzaleaTown_Gym_Movement_Player_Right
	waitmovement 0
	waitmovement 0
	applymovement 8, AzaleaTown_Gym_Movement_Ariados_Right
	applymovement 255, AzaleaTown_Gym_Movement_Player_Right
	waitmovement 0
	waitmovement 0
	turnobject 255, DIR_SOUTH
	applymovement 8, AzaleaTown_Gym_Movement_Ariados_Down
	delay 3
	applymovement 255, AzaleaTown_Gym_Movement_Player_Down
	waitmovement 0
	applymovement 255, J_Common_Movement_JumpDown1
	playse 10
	waitmovement 0
	applymovement 8, AzaleaTown_Gym_Movement_Ariados_Up
	waitmovement 0
	setflag 8231
	removeobject 8
	resetobjectsubpriority 255, MAP_AZALEA_TOWN_GYM_HNS
	release
	end

AzaleaTown_Gym_EventScript_Trigger_7::
	lock
	turnobject 255, DIR_NORTH
	clearflag 8231
	addobject 11
	SetObjectSubpriority 255, MAP_AZALEA_TOWN_GYM_HNS, 0
	applymovement 11, AzaleaTown_Gym_Movement_Ariados_Down
	waitmovement 0
	turnobject 11, DIR_NORTH
	delay 30
	applymovement 255, J_Common_Movement_JumpUp1
	playse 10
	waitmovement 0
	waitmovement 0
	applymovement 11, AzaleaTown_Gym_Movement_Ariados_Up
	applymovement 255, AzaleaTown_Gym_Movement_Player_Up
	waitmovement 0
	waitmovement 0
	applymovement 11, AzaleaTown_Gym_Movement_Ariados_Up
	applymovement 255, AzaleaTown_Gym_Movement_Player_Up
	waitmovement 0
	applymovement 255, J_Common_Movement_JumpUp1
	playse 10
	waitmovement 0
	applymovement 11, AzaleaTown_Gym_Movement_Ariados_Down
	waitmovement 0
	setflag 8231
	removeobject 11
	resetobjectsubpriority 255, MAP_AZALEA_TOWN_GYM_HNS
	release
	end

AzaleaTown_Gym_EventScript_Trigger_10::
	lock
	turnobject 255, DIR_SOUTH
	clearflag 8231
	addobject 11
	SetObjectSubpriority 255, MAP_AZALEA_TOWN_GYM_HNS, 0
	applymovement 11, AzaleaTown_Gym_Movement_Ariados_Up
	waitmovement 0
	turnobject 11, DIR_SOUTH
	delay 30
	applymovement 255, J_Common_Movement_JumpDown1
	playse 10
	waitmovement 0
	waitmovement 0
	applymovement 11, AzaleaTown_Gym_Movement_Ariados_Down
	delay 3
	applymovement 255, AzaleaTown_Gym_Movement_Player_Down
	waitmovement 0
	waitmovement 0
	applymovement 11, AzaleaTown_Gym_Movement_Ariados_Down
	delay 3
	applymovement 255, AzaleaTown_Gym_Movement_Player_Down
	waitmovement 0
	applymovement 255, J_Common_Movement_JumpDown1
	playse 10
	waitmovement 0
	applymovement 11, AzaleaTown_Gym_Movement_Ariados_Up
	waitmovement 0
	setflag 8231
	removeobject 11
	resetobjectsubpriority 255, MAP_AZALEA_TOWN_GYM_HNS
	release
	end

AzaleaTown_Gym_EventScript_Trigger_8::
	lock
	turnobject 255, DIR_NORTH
	clearflag 8232
	addobject 12
	SetObjectSubpriority 255, MAP_AZALEA_TOWN_GYM_HNS, 0
	applymovement 12, AzaleaTown_Gym_Movement_Ariados_Down
	waitmovement 0
	turnobject 12, DIR_NORTH
	delay 30
	applymovement 255, J_Common_Movement_JumpUp1
	playse 10
	waitmovement 0
	waitmovement 0
	applymovement 12, AzaleaTown_Gym_Movement_Ariados_Up
	applymovement 255, AzaleaTown_Gym_Movement_Player_Up
	waitmovement 0
	waitmovement 0

	applymovement 12, AzaleaTown_Gym_Movement_Ariados_Right
	applymovement 255, AzaleaTown_Gym_Movement_Player_Right
	waitmovement 0
	waitmovement 0
	turnobject 255, DIR_NORTH
	applymovement 12, AzaleaTown_Gym_Movement_Ariados_Up
	applymovement 255, AzaleaTown_Gym_Movement_Player_Up
	waitmovement 0
	applymovement 255, J_Common_Movement_JumpUp1
	playse 10
	waitmovement 0
	applymovement 12, AzaleaTown_Gym_Movement_Ariados_Down
	waitmovement 0
	setflag 8232
	removeobject 12
	resetobjectsubpriority 255, MAP_AZALEA_TOWN_GYM_HNS
	release
	end

AzaleaTown_Gym_EventScript_Trigger_12::
	lock
	turnobject 255, DIR_SOUTH
	clearflag 8233
	addobject 13
	SetObjectSubpriority 255, MAP_AZALEA_TOWN_GYM_HNS, 0
	applymovement 13, AzaleaTown_Gym_Movement_Ariados_Up
	waitmovement 0
	turnobject 13, DIR_SOUTH
	delay 30
	applymovement 255, J_Common_Movement_JumpDown1
	playse 10
	waitmovement 0
	waitmovement 0
	applymovement 13, AzaleaTown_Gym_Movement_Ariados_Down
	delay 3
	applymovement 255, AzaleaTown_Gym_Movement_Player_Down
	waitmovement 0
	waitmovement 0

	applymovement 13, AzaleaTown_Gym_Movement_Ariados_Left
	applymovement 255, AzaleaTown_Gym_Movement_Player_Left
	waitmovement 0
	waitmovement 0
	turnobject 255, DIR_SOUTH
	applymovement 13, AzaleaTown_Gym_Movement_Ariados_Down
	delay 3
	applymovement 255, AzaleaTown_Gym_Movement_Player_Down
	waitmovement 0
	applymovement 255, J_Common_Movement_JumpDown1
	playse 10
	waitmovement 0
	applymovement 13, AzaleaTown_Gym_Movement_Ariados_Up
	waitmovement 0
	setflag 8233
	removeobject 13
	resetobjectsubpriority 255, MAP_AZALEA_TOWN_GYM_HNS
	release
	end

AzaleaTown_Gym_EventScript_Trigger_9::
	lock
	turnobject 255, DIR_NORTH
	clearflag 8233
	addobject 13
	SetObjectSubpriority 255, MAP_AZALEA_TOWN_GYM_HNS, 0
	applymovement 13, AzaleaTown_Gym_Movement_Ariados_Down
	waitmovement 0
	turnobject 13, DIR_NORTH
	delay 30
	applymovement 255, J_Common_Movement_JumpUp1
	playse 10
	waitmovement 0
	waitmovement 0
	applymovement 13, AzaleaTown_Gym_Movement_Ariados_Up
	applymovement 255, AzaleaTown_Gym_Movement_Player_Up
	waitmovement 0
	waitmovement 0

	applymovement 13, AzaleaTown_Gym_Movement_Ariados_Left
	applymovement 255, AzaleaTown_Gym_Movement_Player_Left
	waitmovement 0
	waitmovement 0
	turnobject 255, DIR_NORTH
	applymovement 13, AzaleaTown_Gym_Movement_Ariados_Up
	applymovement 255, AzaleaTown_Gym_Movement_Player_Up
	waitmovement 0
	applymovement 255, J_Common_Movement_JumpUp1
	playse 10
	waitmovement 0
	applymovement 13, AzaleaTown_Gym_Movement_Ariados_Down
	waitmovement 0
	setflag 8233
	removeobject 13
	resetobjectsubpriority 255, MAP_AZALEA_TOWN_GYM_HNS
	release
	end

AzaleaTown_Gym_EventScript_Trigger_11::
	lock
	turnobject 255, DIR_SOUTH
	clearflag 8232
	addobject 12
	SetObjectSubpriority 255, MAP_AZALEA_TOWN_GYM_HNS, 0
	applymovement 12, AzaleaTown_Gym_Movement_Ariados_Up
	waitmovement 0
	turnobject 12, DIR_SOUTH
	delay 30
	applymovement 255, J_Common_Movement_JumpDown1
	playse 10
	waitmovement 0
	waitmovement 0
	applymovement 12, AzaleaTown_Gym_Movement_Ariados_Down
	delay 3
	applymovement 255, AzaleaTown_Gym_Movement_Player_Down
	waitmovement 0
	waitmovement 0

	applymovement 12, AzaleaTown_Gym_Movement_Ariados_Right
	applymovement 255, AzaleaTown_Gym_Movement_Player_Right
	waitmovement 0
	waitmovement 0
	turnobject 255, DIR_SOUTH
	applymovement 12, AzaleaTown_Gym_Movement_Ariados_Down
	delay 3
	applymovement 255, AzaleaTown_Gym_Movement_Player_Down
	waitmovement 0
	applymovement 255, J_Common_Movement_JumpDown1
	playse 10
	waitmovement 0
	applymovement 12, AzaleaTown_Gym_Movement_Ariados_Up
	waitmovement 0
	setflag 8232
	removeobject 12
	resetobjectsubpriority 255, MAP_AZALEA_TOWN_GYM_HNS
	release
	end

AzaleaTown_Gym_EventScript_GymGuy::
	lock
	faceplayer
	goto_if_set 10369, AzaleaTown_Gym_EventScript_GymGuy2
	msgbox AzaleaTown_Gym_Text_GymGuide, MSGBOX_DEFAULT
	closemessage
	release
	end

AzaleaTown_Gym_EventScript_GymGuy2::
	msgbox AzaleaTown_Gym_Text_GymGuideWin, MSGBOX_DEFAULT
	closemessage
	release
	end

AzaleaTown_Gym_EventScript_Al::
	trainerbattle_single 1194, AzaleaTown_Gym_Text_BugCatcherAlSeen, AzaleaTown_Gym_Text_BugCatcherAlBeaten
	msgbox AzaleaTown_Gym_Text_BugCatcherAlAfter, MSGBOX_AUTOCLOSE
	end

AzaleaTown_Gym_EventScript_Josh::
	trainerbattle_single 1195, AzaleaTown_Gym_Text_BugCatcherJoshSeen, AzaleaTown_Gym_Text_BugCatcherJoshBeaten
	msgbox AzaleaTown_Gym_Text_BugCatcherJoshAfter, MSGBOX_AUTOCLOSE
	end

AzaleaTown_Gym_EventScript_Benny::
	trainerbattle_single 1193, AzaleaTown_Gym_Text_BugCatcherBennySeen, AzaleaTown_Gym_Text_BugCatcherBennyBeaten
	msgbox AzaleaTown_Gym_Text_BugCatcherBennyAfter, MSGBOX_AUTOCLOSE
	end

AzaleaTown_Gym_EventScript_Amy::
	trainerbattle_double 1413, AzaleaTown_Gym_Text_TwinsAmyMay1Seen, AzaleaTown_Gym_Text_TwinsAmyMay1Beaten, J_Route104_Text_GinaNotEnoughMons
	special GetPlayerBigGuyGirlString
	msgbox AzaleaTown_Gym_Text_TwinsAmyMay1After, MSGBOX_DEFAULT
	release
	end

AzaleaTown_Gym_EventScript_May::
	trainerbattle_double 1413, AzaleaTown_Gym_Text_TwinsAmyMay2Seen, AzaleaTown_Gym_Text_TwinsAmyMay2Beaten, J_Route104_Text_GinaNotEnoughMons
	special GetPlayerBigGuyGirlString
	msgbox AzaleaTown_Gym_Text_TwinsAmyMay2After, MSGBOX_DEFAULT
	release
	end

AzaleaTown_Gym_EventScript_Bugsy::
	lock
	faceplayer
	goto_if_set 8744, AzaleaTown_Gym_EventScript_Bugsy_Defeated
	msgbox AzaleaTown_Gym_Text_BugsyIntro, MSGBOX_DEFAULT
	trainerbattle_no_intro 1428, AzaleaTown_Gym_Text_BugsyBeaten
	message AzaleaTown_Gym_Text_ReceivedHiveBadge
	waitmessage
	call J_Common_EventScript_PlayGymBadgeFanfare
	msgbox AzaleaTown_Gym_Text_HiveBadgeSpeech, MSGBOX_DEFAULT
	setflag 10369
	setflag 8744
	addvar 20582, 1
	setvar 32776, 2
	call J_Common_EventScript_SetGymTrainers_hns
	giveitem 670
	msgbox AzaleaTown_Gym_Text_FuryCutterSpeech, MSGBOX_DEFAULT
	setvar 20547, 5
	closemessage
	setflag 8229
	setflag 8704
	clearflag 8287
	clearflag 8234
	release
	end

AzaleaTown_Gym_EventScript_Bugsy_Defeated::
	msgbox AzaleaTown_Gym_Text_BugsyAdvice, MSGBOX_DEFAULT
	closemessage
	release
	end

AzaleaTown_Gym_Movement_Ariados_Down:
	delay_8
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	step_end

AzaleaTown_Gym_Movement_Ariados_Up:
	delay_8
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	step_end

AzaleaTown_Gym_Movement_Ariados_Right:
	lock_facing_direction
	delay_8
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	unlock_facing_direction
	step_end

AzaleaTown_Gym_Movement_Ariados_Left:
	lock_facing_direction
	delay_8
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	unlock_facing_direction
	step_end

AzaleaTown_Gym_Movement_Player_Down:
	lock_anim
	delay_8
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	unlock_anim
	unlock_facing_direction
	step_end

AzaleaTown_Gym_Movement_Player_Up:
	lock_anim
	delay_8
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	unlock_anim
	unlock_facing_direction
	step_end

AzaleaTown_Gym_Movement_Player_Right:
	lock_facing_direction
	lock_anim
	delay_8
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	unlock_anim
	unlock_facing_direction
	step_end

AzaleaTown_Gym_Movement_Player_Left:
	lock_facing_direction
	lock_anim
	delay_8
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	unlock_anim
	unlock_facing_direction
	step_end

AzaleaTown_Gym_EventScript_Statue::
	lock
	goto_if_set 8744, AzaleaTown_Gym_EventScript_Statue2
	msgbox AzaleaTown_Gym_Text_GymStatue, MSGBOX_DEFAULT
	closemessage
	release
	end

AzaleaTown_Gym_EventScript_Statue2::
	msgbox AzaleaTown_Gym_Text_GymStatueCertified, MSGBOX_DEFAULT
	closemessage
	release
	end

AzaleaTown_Gym_Text_GymStatue:
	.string "AZALE{SE_M_BONEMERANG}POKéMO{SE_M_PSYBEAM2}GYM$"

AzaleaTown_Gym_Text_GymStatueCertified:
	.string "AZALE{SE_M_BONEMERANG}TOW{SE_M_PSYBEAM2}POKéMO{SE_M_PSYBEAM2}GYM\p"
	.string "BUGSY'{SE_M_SKETCH}CERTIFIE{SE_M_FAINT_ATTACK}TRAINERS:\n"
	.string "{PLAYER}$"

AzaleaTown_Gym_Text_BugsyIntro:
	.string "I'{SE_M_MILK_DRINK}BUGSY!\p"
	.string "{SE_M_HEAL_BELL}neve{SE_M_SAND_TOMB}los{SE_M_REVERSAL}whe{SE_M_ATTRACT}i{SE_M_SPIT_UP}comes\n"
	.string "t{SE_M_ATTRACT2}bu{SE_M_SANDSTORM}POKéMON.\p"
	.string "M{SE_M_YAWN}researc{SE_M_TRI_ATTACK}i{SE_M_GRASSWHISTLE}goin{SE_M_SANDSTORM}t{SE_M_ATTRACT2}mak{SE_M_REVERSAL}m{SE_M_REVERSAL}the\n"
	.string "authorit{SE_M_YAWN}o{SE_M_ATTRACT}bu{SE_M_SANDSTORM}POKéMON!\p"
	.string "Le{SE_M_SPIT_UP}m{SE_M_REVERSAL}demonstrat{SE_M_REVERSAL}al{SE_M_BATON_PASS}I've\n"
	.string "learne{SE_M_WATERFALL}fro{SE_M_MILK_DRINK}m{SE_M_YAWN}studies.$"

AzaleaTown_Gym_Text_BugsyBeaten:
	.string "Whoa{SE_M_SUPERSONIC}amazing{SE_M_DRAGON_RAGE}You'r{SE_M_REVERSAL}an\n"
	.string "exper{SE_M_SPIT_UP}o{SE_M_ATTRACT}POKéMON!\p"
	.string "M{SE_M_YAWN}researc{SE_M_TRI_ATTACK}isn'{SE_M_SPIT_UP}complete\n"
	.string "yet.\p"
	.string "OK{SE_M_SUPERSONIC}yo{SE_M_DIVE}win{SE_M_PERISH_SONG}Tak{SE_M_REVERSAL}this\n"
	.string "BADGE.$"

AzaleaTown_Gym_Text_ReceivedHiveBadge:
	.string "{PLAYER} receive{SE_M_WATERFALL}HIVEBADGE.$"

AzaleaTown_Gym_Text_HiveBadgeSpeech:
	.string "D{SE_M_ATTRACT2}yo{SE_M_DIVE}kno{SE_M_TWISTER}th{SE_M_REVERSAL}benefits\n"
	.string "o{SE_M_ACID_ARMOR}HIVEBADGE?\p"
	.string "I{SE_M_ACID_ARMOR}yo{SE_M_DIVE}hav{SE_M_REVERSAL}it{SE_M_SUPERSONIC}POKéMO{SE_M_PSYBEAM2}up\n"
	.string "t{SE_M_ATTRACT2}L3{SE_M_BITE}wil{SE_M_BATON_PASS}obe{SE_M_YAWN}you,\l"
	.string "eve{SE_M_ATTRACT}trade{SE_M_WATERFALL}ones.\p"
	.string "POKéMO{SE_M_PSYBEAM2}tha{SE_M_SPIT_UP}kno{SE_M_TWISTER}CU{SE_M_SWIFT}wil{SE_M_BATON_PASS}b{SE_M_REVERSAL}able\n"
	.string "t{SE_M_ATTRACT2}us{SE_M_REVERSAL}i{SE_M_SPIT_UP}outsid{SE_M_REVERSAL}o{SE_M_ACID_ARMOR}battl{SE_M_REVERSAL}too.\p"
	.string "Here{SE_M_SUPERSONIC}{SE_M_HEAL_BELL}als{SE_M_ATTRACT2}wan{SE_M_SPIT_UP}yo{SE_M_DIVE}to\n"
	.string "hav{SE_M_REVERSAL}this.$"

AzaleaTown_Gym_Text_FuryCutterSpeech:
	.string "TM8{SE_M_BIND}contain{SE_M_GRASSWHISTLE}U-TURN.\p"
	.string "U-TUR{SE_M_PSYBEAM2}let{SE_M_GRASSWHISTLE}yo{SE_M_DIVE}d{SE_M_ATTRACT2}damag{SE_M_REVERSAL}and\n"
	.string "switc{SE_M_TRI_ATTACK}you{SE_M_SAND_TOMB}POKéMO{SE_M_PSYBEAM2}i{SE_M_ATTRACT}th{SE_M_REVERSAL}same\l"
	.string "turn!\p"
	.string "Isn'{SE_M_SPIT_UP}tha{SE_M_SPIT_UP}great?\n"
	.string "{SE_M_HEAL_BELL}discovere{SE_M_WATERFALL}it!$"

AzaleaTown_Gym_Text_BugsyAdvice:
	.string "Bu{SE_M_SANDSTORM}POKéMO{SE_M_PSYBEAM2}ar{SE_M_REVERSAL}deep{SE_M_PERISH_SONG}Ther{SE_M_REVERSAL}are\n"
	.string "man{SE_M_YAWN}mysterie{SE_M_GRASSWHISTLE}t{SE_M_ATTRACT2}b{SE_M_REVERSAL}explored.\p"
	.string "Stud{SE_M_YAWN}you{SE_M_SAND_TOMB}favorite{SE_M_GRASSWHISTLE}thoroughly.$"

AzaleaTown_Gym_Text_BugsyRematch:
	.string "Wow{SE_M_SUPERSONIC}you'r{SE_M_REVERSAL}th{SE_M_REVERSAL}JOHT{SE_M_SOLAR_BEAM}CHAMPIO{SE_M_PSYBEAM2}now!\p"
	.string "You{SE_M_SAND_TOMB}skill{SE_M_GRASSWHISTLE}ar{SE_M_REVERSAL}trul{SE_M_YAWN}impressive!\p"
	.string "I'v{SE_M_REVERSAL}bee{SE_M_ATTRACT}bus{SE_M_YAWN}wit{SE_M_TRI_ATTACK}m{SE_M_YAWN}research.\p"
	.string "I'{SE_M_MILK_DRINK}read{SE_M_YAWN}t{SE_M_ATTRACT2}sho{SE_M_TWISTER}yo{SE_M_DIVE}m{SE_M_YAWN}new\n"
	.string "findings.\p"
	.string "Wan{SE_M_SPIT_UP}t{SE_M_ATTRACT2}hav{SE_M_REVERSAL}{SE_M_CHARGE}rematc{SE_M_TRI_ATTACK}wit{SE_M_TRI_ATTACK}me?$"

AzaleaTown_Gym_Text_BugsyRematchDefeat:
	.string "Wow{SE_M_SUPERSONIC}yo{SE_M_DIVE}mus{SE_M_SPIT_UP}b{SE_M_REVERSAL}a{SE_M_ATTRACT}exper{SE_M_SPIT_UP}trainer.\n"
	.string "M{SE_M_YAWN}researc{SE_M_TRI_ATTACK}mus{SE_M_SPIT_UP}no{SE_M_SPIT_UP}b{SE_M_REVERSAL}complete...$"

AzaleaTown_Gym_Text_BugCatcherBennySeen:
	.string "Bu{SE_M_SANDSTORM}POKéMO{SE_M_PSYBEAM2}evolv{SE_M_REVERSAL}young{SE_M_PERISH_SONG}S{SE_M_ATTRACT2}they\n"
	.string "ge{SE_M_SPIT_UP}stronge{SE_M_SAND_TOMB}tha{SE_M_SPIT_UP}muc{SE_M_TRI_ATTACK}faster.$"

AzaleaTown_Gym_Text_BugCatcherBennyBeaten:
	.string "Jus{SE_M_SPIT_UP}evolvin{SE_M_SANDSTORM}isn'{SE_M_SPIT_UP}enough!$"

AzaleaTown_Gym_Text_BugCatcherBennyAfter:
	.string "POKéMO{SE_M_PSYBEAM2}becom{SE_M_REVERSAL}stronger\n"
	.string "i{SE_M_ACID_ARMOR}the{SE_M_YAWN}evolve{SE_M_PERISH_SONG}Really!$"

AzaleaTown_Gym_Text_BugCatcherAlSeen:
	.string "Bu{SE_M_SANDSTORM}POKéMO{SE_M_PSYBEAM2}ar{SE_M_REVERSAL}coo{SE_M_BATON_PASS}an{SE_M_WATERFALL}tough!\n"
	.string "I'l{SE_M_BATON_PASS}prov{SE_M_REVERSAL}i{SE_M_SPIT_UP}t{SE_M_ATTRACT2}you!$"

AzaleaTown_Gym_Text_BugCatcherAlBeaten:
	.string "Yo{SE_M_DIVE}prove{SE_M_WATERFALL}ho{SE_M_TWISTER}toug{SE_M_TRI_ATTACK}yo{SE_M_DIVE}are…$"

AzaleaTown_Gym_Text_BugCatcherAlAfter:
	.string "They'r{SE_M_REVERSAL}s{SE_M_ATTRACT2}cool{SE_M_SUPERSONIC}bu{SE_M_SPIT_UP}mos{SE_M_SPIT_UP}girls\n"
	.string "don'{SE_M_SPIT_UP}lik{SE_M_REVERSAL}bu{SE_M_SANDSTORM}POKéMON.\p"
	.string "{SE_M_HEAL_BELL}don'{SE_M_SPIT_UP}kno{SE_M_TWISTER}why…$"

AzaleaTown_Gym_Text_BugCatcherJoshSeen:
	.string "Yo{SE_M_DIVE}save{SE_M_WATERFALL}al{SE_M_BATON_PASS}th{SE_M_REVERSAL}SLOWPOKE?\n"
	.string "Whew{SE_M_SUPERSONIC}you'r{SE_M_REVERSAL}mighty!\p"
	.string "Bu{SE_M_SPIT_UP}m{SE_M_YAWN}grown-u{SE_M_MORNING_SUN}POKéMO{SE_M_PSYBEAM2}are\n"
	.string "prett{SE_M_YAWN}toug{SE_M_TRI_ATTACK}too!$"

AzaleaTown_Gym_Text_BugCatcherJoshBeaten:
	.string "Urrgggh!$"

AzaleaTown_Gym_Text_BugCatcherJoshAfter:
	.string "{SE_M_HEAL_BELL}gues{SE_M_GRASSWHISTLE}{SE_M_HEAL_BELL}shoul{SE_M_WATERFALL}teac{SE_M_TRI_ATTACK}them\n"
	.string "bette{SE_M_SAND_TOMB}moves…$"

AzaleaTown_Gym_Text_TwinsAmyMay1Seen:
	.string "AMY{SE_M_HEAT_WAVE}Hi{SE_M_DRAGON_RAGE}Ar{SE_M_REVERSAL}yo{SE_M_DIVE}challenging\n"
	.string "th{SE_M_REVERSAL}LEADER{SE_M_SING}N{SE_M_ATTRACT2}way!$"

AzaleaTown_Gym_Text_TwinsAmyMay1Beaten:
	.string "AM{SE_M_MOONLIGHT}{SE_WARP_IN}MAY{SE_M_HEAT_WAVE}Oh{SE_M_SUPERSONIC}double\n"
	.string "goodness!$"

AzaleaTown_Gym_Text_TwinsAmyMay1After:
	.string "AMY{SE_M_HEAT_WAVE}You'r{SE_M_REVERSAL}reall{SE_M_YAWN}strong!\p"
	.string "Bu{SE_M_SPIT_UP}BUGSY'{SE_M_GRASSWHISTLE}eve{SE_M_ATTRACT}stronger!\n"
	.string "Hi{SE_M_GRASSWHISTLE}SCYTHER'{SE_M_GRASSWHISTLE}CU{SE_M_SWIFT}almost\l"
	.string "alway{SE_M_GRASSWHISTLE}make{SE_M_GRASSWHISTLE}critica{SE_M_BATON_PASS}hits!$"

AzaleaTown_Gym_Text_TwinsAmyMay2Seen:
	.string "MAY{SE_M_HEAT_WAVE}Yo{SE_M_DIVE}wan{SE_M_SPIT_UP}t{SE_M_ATTRACT2}se{SE_M_REVERSAL}the\n"
	.string "LEADER{SE_M_SING}Goo{SE_M_WATERFALL}luck!\p"
	.string "BUGS{SE_M_MOONLIGHT}i{SE_M_GRASSWHISTLE}s{SE_M_ATTRACT2}strong!\n"
	.string "Hi{SE_M_GRASSWHISTLE}SCYTHER'{SE_M_GRASSWHISTLE}CU{SE_M_SWIFT}always\l"
	.string "seem{SE_M_GRASSWHISTLE}t{SE_M_ATTRACT2}crit!$"

AzaleaTown_Gym_Text_TwinsAmyMay2Beaten:
	.string "AM{SE_M_MOONLIGHT}{SE_WARP_IN}MAY{SE_M_HEAT_WAVE}Oh{SE_M_SUPERSONIC}double\n"
	.string "goodness!$"

AzaleaTown_Gym_Text_TwinsAmyMay2After:
	.string "MAY{SE_M_HEAT_WAVE}Ou{SE_M_SAND_TOMB}bu{SE_M_SANDSTORM}POKéMO{SE_M_PSYBEAM2}lost!\n"
	.string "Oh{SE_M_SUPERSONIC}wha{SE_M_SPIT_UP}{SE_M_CHARGE}shame.\p"
	.string "BUGSY'{SE_M_GRASSWHISTLE}won'{SE_M_SPIT_UP}los{SE_M_REVERSAL}though!\p"
	.string "Hi{SE_M_GRASSWHISTLE}PINEC{SE_M_SOLAR_BEAM}make{SE_M_GRASSWHISTLE}shor{SE_M_SPIT_UP}work\n"
	.string "o{SE_M_ACID_ARMOR}ROCK-typ{SE_M_REVERSAL}POKéMON!$"

AzaleaTown_Gym_Text_GymGuide:
	.string "Yo{SE_M_SUPERSONIC}challenger!\p"
	.string "BUGSY'{SE_M_GRASSWHISTLE}young{SE_M_SUPERSONIC}bu{SE_M_SPIT_UP}hi{SE_M_GRASSWHISTLE}knowledge\n"
	.string "o{SE_M_ACID_ARMOR}bu{SE_M_SANDSTORM}POKéMO{SE_M_PSYBEAM2}i{SE_M_GRASSWHISTLE}fo{SE_M_SAND_TOMB}real.\p"
	.string "It'{SE_M_GRASSWHISTLE}goin{SE_M_SANDSTORM}t{SE_M_ATTRACT2}b{SE_M_REVERSAL}tough\n"
	.string "withou{SE_M_SPIT_UP}m{SE_M_YAWN}advice.\p"
	.string "Let'{SE_M_GRASSWHISTLE}see{SE_M_DIZZY_PUNCH}BUGSY'{SE_M_GRASSWHISTLE}bagwor{SE_M_MILK_DRINK}POKéMON\n"
	.string "know{SE_M_GRASSWHISTLE}{SE_M_CHARGE}mov{SE_M_REVERSAL}tha{SE_M_SPIT_UP}cover{SE_M_GRASSWHISTLE}its\l"
	.string "ROCK-typ{SE_M_REVERSAL}weakness.\p"
	.string "Oh{SE_M_SUPERSONIC}an{SE_M_WATERFALL}don'{SE_M_SPIT_UP}forge{SE_M_SPIT_UP}abou{SE_M_SPIT_UP}those\n"
	.string "nast{SE_M_YAWN}critica{SE_M_BATON_PASS}hits{SE_M_DRAGON_RAGE}Goo{SE_M_WATERFALL}luck!$"

AzaleaTown_Gym_Text_GymGuideWin:
	.string "Wel{SE_M_BATON_PASS}done{SE_M_DRAGON_RAGE}Tha{SE_M_SPIT_UP}wa{SE_M_GRASSWHISTLE}{SE_M_CHARGE}great\n"
	.string "clas{SE_M_TRI_ATTACK}o{SE_M_ACID_ARMOR}talente{SE_M_WATERFALL}youn{SE_M_SANDSTORM}trainers.\p"
	.string "Wit{SE_M_TRI_ATTACK}peopl{SE_M_REVERSAL}lik{SE_M_REVERSAL}you{SE_M_SUPERSONIC}the\n"
	.string "futur{SE_M_REVERSAL}o{SE_M_ACID_ARMOR}POKéMO{SE_M_PSYBEAM2}i{SE_M_GRASSWHISTLE}bright!$"

