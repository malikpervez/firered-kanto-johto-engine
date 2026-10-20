@ Johto (data/maps/RocketHideout_B3F_hns/scripts.inc), as built into the FireRed game.

RocketHideout_B3F_hns_MapScripts::
	map_script 2, RocketHideout_B3F_OnFrame
	map_script 1, RocketHideout_B3F_OnLoad
	.byte 0

RocketHideout_B3F_OnLoad::
	call_if_set 8341, RocketHideout_B3F_HideGate
	call_if_eq 20591, 2, RocketHideout_B3F_HidePetrel
	end

RocketHideout_B3F_HideGate::
	setmetatile 11, 11, 0x378, FALSE
	setmetatile 11, 12, 0x380, FALSE
	setmetatile 12, 11, 0x379, FALSE
	setmetatile 12, 12, 0x379, FALSE
	setmetatile 13, 11, 0x379, FALSE
	setmetatile 13, 12, 0x379, FALSE
	return

RocketHideout_B3F_HidePetrel::
	setflag 8346
	clearflag 8342
	return

RocketHideout_B3F_OnFrame::
	map_script_2 20578, 6, RocketHideout_B3F_EventScript_LancePassword
	.2byte 0

RocketHideout_B3F_EventScript_LancePassword::
	lock
	delay 55
	playse 21
	applymovement 3, J_Common_Movement_ExclamationMark
	delay 55
	waitmovement 3
	applymovement 3, J_Common_Movement_WalkRight1
	msgbox RocketHideout_B3F_Text_LanceGetPassword, MSGBOX_DEFAULT
	closemessage
	applymovement 3, RocketHideout_B3F_Movement_LanceLeave
	applymovement 2, RocketHideout_B3F_Movement_DragoniteLeave
	waitmovement 3
	waitmovement 2
	setflag 8343
	removeobject 2
	removeobject 3
	setvar 20578, 7
	release
	end

RocketHideout_B3F_Movement_LanceLeave:
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	delay_2
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

RocketHideout_B3F_Movement_DragoniteLeave:
	delay_16
	delay_16
	delay_16
	delay_16
	delay_8
	delay_8
	delay_8
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

RocketHideout_B3F_Text_LanceGetPassword:
	.string "LANCE{SE_M_HEAT_WAVE}I{SE_M_SPIT_UP}take{SE_M_GRASSWHISTLE}tw{SE_M_ATTRACT2}passwords\n"
	.string "t{SE_M_ATTRACT2}ge{SE_M_SPIT_UP}int{SE_M_ATTRACT2}th{SE_M_REVERSAL}boss{SE_M_ABSORB}quarters.\p"
	.string "Thos{SE_M_REVERSAL}password{SE_M_GRASSWHISTLE}ar{SE_M_REVERSAL}know{SE_M_ATTRACT}only\n"
	.string "t{SE_M_ATTRACT2}{SE_M_CHARGE}fe{SE_M_TWISTER}ROCKETS.\p"
	.string "Tha{SE_M_SPIT_UP}ROCKE{SE_M_SWIFT}ther{SE_M_REVERSAL}ver{SE_M_YAWN}graciously\n"
	.string "tol{SE_M_WATERFALL}m{SE_M_REVERSAL}so.\p"
	.string "{PLAYER}{SE_M_SUPERSONIC}let'{SE_M_GRASSWHISTLE}g{SE_M_ATTRACT2}ge{SE_M_SPIT_UP}the\n"
	.string "passwords.$"

RocketHideout_B3F_EventScript_RocketKO::
	lock
	faceplayer
	msgbox RocketHideout_B3F_Text_B3FRocket, MSGBOX_DEFAULT
	release
	end

RocketHideout_B3F_Text_B3FRocket:
	.string "Urrggh{SE_M_DIZZY_PUNCH}Th{SE_M_REVERSAL}gu{SE_M_YAWN}i{SE_M_ATTRACT}th{SE_M_REVERSAL}cap{SE_M_REVERSAL}is\n"
	.string "incredibl{SE_M_YAWN}tough…$"

RocketHideout_B3F_Trigger_MurkrowStairs::
	lock
	applymovement 17, RocketHideout_B3F_Movement_MurkrowStairs1
	waitmovement 0
	playmoncry 198, 0
	msgbox RocketHideout_B3F_Text_MurkrowSpeak1, MSGBOX_DEFAULT
	closemessage
	applymovement 17, RocketHideout_B3F_Movement_MurkrowStairs2
	waitmovement 0
	setflag 8345
	removeobject 17
	clearflag 8339
	setvar 20578, 11
	release
	end

RocketHideout_B3F_Movement_MurkrowStairs1:
	jump_in_place_right
	jump_in_place_right
	step_end

RocketHideout_B3F_Movement_MurkrowStairs2:
	jump_in_place_right
	walk_fast_down
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	step_end

RocketHideout_B3F_Trigger_Silver::
	lock
	clearflag 8347
	addobject 5
	playbgm ((558 + 1) + 0x3B), FALSE
	applymovement 5, RocketHideout_B3F_Movement_SilverEnter
	waitmovement 0
	turnobject 255, DIR_WEST
	msgbox RocketHideout_B3F_Text_Rival, MSGBOX_DEFAULT
	closemessage
	applymovement 5, RocketHideout_B3F_Movement_SilverLeave
	waitmovement 0
	setflag 8347
	removeobject 5
	setvar 20578, 8
	fadedefaultbgm
	release
	end

RocketHideout_B3F_Movement_SilverEnter:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

RocketHideout_B3F_Movement_SilverLeave:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

RocketHideout_B3F_EventScript_Door::
	lock
	goto_if_set 8341, RocketHideout_B3F_EventScript_DoorIsOpen
	goto_if_eq 20591, 2, RocketHideout_B3F_EventScript_OpenDoor
	msgbox RocketHideout_B3F_Text_B3FLockedDoorNeedsPassword, MSGBOX_DEFAULT
	closemessage
	release
	end

RocketHideout_B3F_EventScript_OpenDoor::
	msgbox RocketHideout_B3F_Text_B3FLockedDoorOpenSesame, MSGBOX_DEFAULT
	closemessage
	playse 36
	setmetatile 11, 11, 0x378, FALSE
	setmetatile 11, 12, 0x380, FALSE
	setmetatile 12, 11, 0x379, FALSE
	setmetatile 12, 12, 0x379, FALSE
	setmetatile 13, 11, 0x379, FALSE
	setmetatile 13, 12, 0x379, FALSE
	special DrawWholeMapView
	setflag 8341
	release
	end

RocketHideout_B3F_EventScript_DoorIsOpen::
	end

RocketHideout_B3F_EventScript_GruntF5::
	trainerbattle_single 1171, RocketHideout_B3F_Text_GruntF5Seen, RocketHideout_B3F_Text_GruntF5Beaten
	msgbox RocketHideout_B3F_Text_GruntF5After, MSGBOX_NPC
	goto_if_unset 8742, RocketHideout_B3F_EventScript_IncrementPasswordGruntF
	end

RocketHideout_B3F_EventScript_IncrementPasswordGruntF::
	addvar 20591, 1
	setflag 8742
	end

RocketHideout_B3F_EventScript_Eto::
	trainerbattle_single 1177, RocketHideout_B3F_Text_GruntM28Seen, RocketHideout_B3F_Text_GruntM28Beaten
	msgbox RocketHideout_B3F_Text_GruntM28After, MSGBOX_NPC
	goto_if_unset 8741, RocketHideout_B3F_EventScript_IncrementPasswordEto
	end

RocketHideout_B3F_EventScript_IncrementPasswordEto::
	addvar 20591, 1
	setflag 8741
	end

RocketHideout_B3F_EventScript_Ross::
	trainerbattle_single 1026, RocketHideout_B3F_Text_ScientistRossSeen, RocketHideout_B3F_Text_ScientistRossBeaten
	msgbox RocketHideout_B3F_Text_ScientistRossAfter, MSGBOX_AUTOCLOSE
	end

RocketHideout_B3F_EventScript_Mitch::
	trainerbattle_single 1027, RocketHideout_B3F_Text_ScientistMitchSeen, RocketHideout_B3F_Text_ScientistMitchBeaten
	msgbox RocketHideout_B3F_Text_ScientistMitchAfter, MSGBOX_AUTOCLOSE
	end

RocketHideout_B3F_EventScript_Item_IceHeal::
	finditem ITEM_ICE_HEAL
	end

RocketHideout_B3F_EventScript_Item_Protein::
	finditem ITEM_PROTEIN
	end

RocketHideout_B3F_EventScript_Item_FullHeal::
	finditem ITEM_FULL_HEAL
	end

RocketHideout_B3F_EventScript_Item_GuardSpec::
	finditem ITEM_GUARD_SPEC
	end

RocketHideout_B3F_EventScript_Item_HyperPotion::
	finditem ITEM_HYPER_POTION
	end

RocketHideout_B3F_Text_B3FLockedDoorNeedsPassword:
	.string "Th{SE_M_REVERSAL}door'{SE_M_GRASSWHISTLE}closed…\p"
	.string "I{SE_M_SPIT_UP}need{SE_M_GRASSWHISTLE}tw{SE_M_ATTRACT2}password{SE_M_GRASSWHISTLE}t{SE_M_ATTRACT2}open.$"

RocketHideout_B3F_Text_B3FLockedDoorOpenSesame:
	.string "Th{SE_M_REVERSAL}door'{SE_M_GRASSWHISTLE}closed…\p"
	.string "{PLAYER} entere{SE_M_WATERFALL}th{SE_M_REVERSAL}tw{SE_M_ATTRACT2}passwords.\p"
	.string "Th{SE_M_REVERSAL}doo{SE_M_SAND_TOMB}opened!$"

RocketHideout_B3F_Text_Rival:
	.string "…\p"
	.string "Didn'{SE_M_SPIT_UP}{SE_M_HEAL_BELL}tel{SE_M_BATON_PASS}yo{SE_M_DIVE}tha{SE_M_SPIT_UP}{SE_M_HEAL_BELL}was\n"
	.string "goin{SE_M_SANDSTORM}t{SE_M_ATTRACT2}destro{SE_M_YAWN}TEA{SE_M_GIGA_DRAIN}ROCKET?\p"
	.string "…Tel{SE_M_BATON_PASS}me{SE_M_SUPERSONIC}wh{SE_M_ATTRACT2}wa{SE_M_GRASSWHISTLE}th{SE_M_REVERSAL}gu{SE_M_YAWN}i{SE_M_ATTRACT}the\n"
	.string "cap{SE_M_REVERSAL}wh{SE_M_ATTRACT2}use{SE_M_WATERFALL}drago{SE_M_ATTRACT}POKéMON?\p"
	.string "M{SE_M_YAWN}POKéMO{SE_M_PSYBEAM2}wer{SE_M_REVERSAL}n{SE_M_ATTRACT2}matc{SE_M_TRI_ATTACK}a{SE_M_SPIT_UP}all.\p"
	.string "It'{SE_M_GRASSWHISTLE}wha{SE_M_SPIT_UP}h{SE_M_REVERSAL}sai{SE_M_WATERFALL}tha{SE_M_SPIT_UP}bothers\n"
	.string "me…\p"
	.string "H{SE_M_REVERSAL}tol{SE_M_WATERFALL}m{SE_M_REVERSAL}tha{SE_M_SPIT_UP}{SE_M_HEAL_BELL}don'{SE_M_SPIT_UP}lov{SE_M_REVERSAL}and\n"
	.string "trus{SE_M_SPIT_UP}m{SE_M_YAWN}POKéMO{SE_M_PSYBEAM2}enough.\p"
	.string "It'{SE_M_GRASSWHISTLE}no{SE_M_SPIT_UP}m{SE_M_YAWN}faul{SE_M_SPIT_UP}m{SE_M_YAWN}tea{SE_M_MILK_DRINK}i{SE_M_GRASSWHISTLE}so\n"
	.string "useless.\p"
	.string "I'{SE_M_MILK_DRINK}furiou{SE_M_GRASSWHISTLE}tha{SE_M_SPIT_UP}{SE_M_HEAL_BELL}los{SE_M_SPIT_UP}t{SE_M_ATTRACT2}a\n"
	.string "bleedin{SE_M_SANDSTORM}hear{SE_M_SPIT_UP}lik{SE_M_REVERSAL}him.\p"
	.string "Bu{SE_M_SPIT_UP}i{SE_M_SPIT_UP}make{SE_M_GRASSWHISTLE}m{SE_M_REVERSAL}questio{SE_M_ATTRACT}myself.\p"
	.string "I{SE_M_GRASSWHISTLE}ther{SE_M_REVERSAL}somethin{SE_M_SANDSTORM}I'{SE_M_MILK_DRINK}doing\n"
	.string "wrong?\p"
	.string "Coul{SE_M_WATERFALL}i{SE_M_SPIT_UP}b{SE_M_REVERSAL}tha{SE_M_SPIT_UP}lov{SE_M_REVERSAL}mad{SE_M_REVERSAL}his\n"
	.string "tea{SE_M_MILK_DRINK}s{SE_M_ATTRACT2}powerful?$"

RocketHideout_B3F_EventScript_Giovanni::
	lock
	faceplayer
	msgbox RocketHideout_B3F_Text_PetrelIntro, MSGBOX_DEFAULT
	playse 21
	applymovement 16, J_Common_Movement_QuestionMark
	delay 55
	waitmovement 16
	msgbox RocketHideout_B3F_Text_PetrelDisbelief, MSGBOX_DEFAULT
	closemessage
	applymovement 16, RocketHideout_B3F_Movement_Spin
	waitmovement 0
	setflag 8342
	removeobject 16
	clearflag 8346
	addobject 15
	applymovement 15, RocketHideout_B3F_Movement_Spin2
	waitmovement 0
	call_if_eq 32780, DIR_EAST, RocketHideout_B3F_EventScript_FacingEast
	call_if_eq 32780, DIR_WEST, RocketHideout_B3F_EventScript_FacingWest
	msgbox RocketHideout_B3F_Text_PetrelReveal, MSGBOX_DEFAULT
	trainerbattle_no_intro 1497, RocketHideout_B3F_Text_PetrelBeaten
	msgbox RocketHideout_B3F_Text_PetrelAfterBattle, MSGBOX_DEFAULT
	closemessage
	call_if_eq 32780, DIR_EAST, RocketHideout_B3F_EventScript_LeaveEast
	call_if_eq 32780, DIR_WEST, RocketHideout_B3F_EventScript_LeaveWest
	call_if_eq 32780, DIR_NORTH, RocketHideout_B3F_EventScript_LeaveEast
	setflag 8346
	playse 9
	removeobject 15

	applymovement 14, RocketHideout_B3F_Movement_Murkrow1

	delay 120

	call_if_eq 32780, DIR_EAST, RocketHideout_B3F_EventScript_FacingEastMurkrow
	call_if_eq 32780, DIR_WEST, RocketHideout_B3F_EventScript_FacingWestMurkrow

	turnobject 255, DIR_SOUTH
	waitmovement 14
	playmoncry 198, 0
	msgbox RocketHideout_B3F_Text_MurkrowSpeak1, MSGBOX_DEFAULT
	msgbox RocketHideout_B3F_Text_MurkrowMimic, MSGBOX_DEFAULT
	closemessage
	applymovement 14, RocketHideout_B3F_Movement_Murkrow2
	waitmovement 14

	setflag 8344
	playse 9
	removeobject 14
	clearflag 8340
	setflag 8339
	setflag 8345
	setflag 8336
	setvar 20591, 3
	setvar 20578, 9
	release
	end

RocketHideout_B3F_EventScript_FacingEastMurkrow::
	applymovement 255, J_Common_Movement_WalkRight1
	waitmovement 255
	applymovement 255, J_Common_Movement_WalkDown1
	waitmovement 255
	return

RocketHideout_B3F_EventScript_FacingWestMurkrow::
	applymovement 255, J_Common_Movement_WalkLeft1
	waitmovement 255
	applymovement 255, J_Common_Movement_WalkDown1
	waitmovement 255
	return

RocketHideout_B3F_EventScript_FacingEast::
	turnobject 15, DIR_WEST
	return

RocketHideout_B3F_EventScript_FacingWest::
	turnobject 15, DIR_EAST
	return

RocketHideout_B3F_EventScript_FacingNorth::
	turnobject 15, DIR_SOUTH
	return

RocketHideout_B3F_EventScript_LeaveEast::
	applymovement 15, RocketHideout_B3F_Movement_LeaveEast
	waitmovement 0
	return

RocketHideout_B3F_EventScript_LeaveWest::
	applymovement 15, RocketHideout_B3F_Movement_LeaveWest
	waitmovement 0
	return

RocketHideout_B3F_Movement_Murkrow1:
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	jump_in_place_right
	jump_in_place_left
	jump_in_place_down
	jump_in_place_up
	jump_in_place_up
	jump_in_place_up
	jump_in_place_up
	step_end

RocketHideout_B3F_Movement_Murkrow2:
	jump_in_place_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_left
	walk_faster_left
	walk_faster_left
	walk_faster_left
	walk_faster_left
	walk_faster_left
	walk_faster_left
	walk_faster_left
	walk_faster_up
	walk_faster_up
	walk_faster_up
	walk_faster_up
	walk_faster_up
	walk_faster_up
	walk_faster_up
	walk_faster_up
	walk_faster_up
	walk_faster_up
	walk_faster_up
	walk_faster_up
	walk_faster_right
	walk_faster_right
	step_end

RocketHideout_B3F_Movement_LeaveEast:
	lock_facing_direction
	walk_slow_right
	unlock_facing_direction
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_left
	walk_faster_left
	walk_faster_left
	walk_faster_left
	walk_faster_left
	walk_faster_left
	walk_faster_left
	walk_faster_left
	walk_faster_left
	walk_faster_up
	walk_faster_up
	walk_faster_up
	walk_faster_up
	walk_faster_up
	walk_faster_up
	walk_faster_up
	walk_faster_up
	walk_faster_up
	walk_faster_up
	walk_faster_up
	walk_fast_right
	walk_fast_right
	step_end

RocketHideout_B3F_Movement_LeaveWest:
	lock_facing_direction
	walk_slow_left
	walk_slow_left
	unlock_facing_direction
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_left
	walk_faster_left
	walk_faster_left
	walk_faster_left
	walk_faster_left
	walk_faster_left
	walk_faster_left
	walk_faster_left
	walk_faster_left
	walk_faster_up
	walk_faster_up
	walk_faster_up
	walk_faster_up
	walk_faster_up
	walk_faster_up
	walk_faster_up
	walk_faster_up
	walk_faster_up
	walk_faster_up
	walk_faster_up
	walk_fast_right
	walk_fast_right
	step_end

RocketHideout_B3F_Movement_Spin:
	face_right
	delay_8
	face_up
	delay_8
	face_left
	delay_8
	face_down
	delay_8
	face_right
	delay_4
	face_up
	delay_4
	face_left
	delay_4
	face_down
	delay_4
	face_right
	delay_2
	face_up
	delay_2
	face_left
	delay_2
	face_down
	step_end

RocketHideout_B3F_Movement_Spin2:
	face_right
	delay_2
	face_up
	delay_2
	face_left
	delay_2
	face_down
	step_end

RocketHideout_B3F_Text_PetrelIntro:
	.string "Muhahaha{SE_M_SUPERSONIC}we'v{SE_M_REVERSAL}bee{SE_M_ATTRACT}waiting\n"
	.string "fo{SE_M_SAND_TOMB}you{SE_M_PERISH_SONG}So{SE_M_SUPERSONIC}yo{SE_M_DIVE}ar{SE_M_REVERSAL}{PLAYER}...\p"
	.string "Me{SE_M_SING}Yo{SE_M_DIVE}don'{SE_M_SPIT_UP}kno{SE_M_TWISTER}wh{SE_M_ATTRACT2}{SE_M_HEAL_BELL}am?\n"
	.string "I{SE_M_SPIT_UP}i{SE_M_GRASSWHISTLE}me{SE_M_SUPERSONIC}GIOVANNI.\p"
	.string "Th{SE_M_REVERSAL}majesti{SE_M_HYPER_BEAM}GIOVANN{SE_M_HEAL_BELL}himself!\n"
	.string "Wahahaha!$"

RocketHideout_B3F_Text_PetrelDisbelief:
	.string "...Huh?\n"
	.string "{SE_M_HEAL_BELL}don'{SE_M_SPIT_UP}soun{SE_M_WATERFALL}anythin{SE_M_SANDSTORM}like\l"
	.string "GIOVANNI?\p"
	.string "{SE_M_HEAL_BELL}don'{SE_M_SPIT_UP}eve{SE_M_ATTRACT}loo{SE_M_ENCORE2}lik{SE_M_REVERSAL}GIOVANNI?\n"
	.string "Ho{SE_M_TWISTER}come{SE_M_SING}I'v{SE_M_REVERSAL}worke{SE_M_WATERFALL}s{SE_M_ATTRACT2}hard\l"
	.string "t{SE_M_ATTRACT2}mimi{SE_M_HYPER_BEAM}him!$"

RocketHideout_B3F_Text_PetrelReveal:
	.string "PETREL{SE_M_HEAT_WAVE}{SE_M_HEAL_BELL}a{SE_M_MILK_DRINK}{SE_M_CHARGE}Tea{SE_M_MILK_DRINK}Rocket\n"
	.string "Executive!\p"
	.string "Yo{SE_M_DIVE}mus{SE_M_SPIT_UP}b{SE_M_REVERSAL}tryin{SE_M_SANDSTORM}t{SE_M_ATTRACT2}snea{SE_M_ENCORE2}into\n"
	.string "th{SE_M_REVERSAL}radio-transmitte{SE_M_SAND_TOMB}room.\p"
	.string "Well{SE_M_SUPERSONIC}that'{SE_M_GRASSWHISTLE}no{SE_M_SPIT_UP}goin{SE_M_SANDSTORM}t{SE_M_ATTRACT2}happen.\n"
	.string "Tha{SE_M_SPIT_UP}roo{SE_M_MILK_DRINK}i{SE_M_GRASSWHISTLE}protecte{SE_M_WATERFALL}wit{SE_M_TRI_ATTACK}a\l"
	.string "specia{SE_M_BATON_PASS}password.\p"
	.string "Th{SE_M_REVERSAL}passwor{SE_M_WATERFALL}i{SE_M_GRASSWHISTLE}“Hai{SE_M_BATON_PASS}GIOVANNI.”\n"
	.string "Surprise{SE_M_WATERFALL}t{SE_M_ATTRACT2}hea{SE_M_SAND_TOMB}i{SE_M_SPIT_UP}fro{SE_M_MILK_DRINK}me?\p"
	.string "Knowin{SE_M_SANDSTORM}th{SE_M_REVERSAL}passwor{SE_M_WATERFALL}won'{SE_M_SPIT_UP}help\n"
	.string "yo{SE_M_DIVE}though.\p"
	.string "Th{SE_M_REVERSAL}doo{SE_M_SAND_TOMB}won'{SE_M_SPIT_UP}ope{SE_M_ATTRACT}unles{SE_M_GRASSWHISTLE}{SE_M_HEAL_BELL}say\n"
	.string "th{SE_M_REVERSAL}password{SE_M_PERISH_SONG}I{SE_M_SPIT_UP}onl{SE_M_YAWN}react{SE_M_GRASSWHISTLE}to\l"
	.string "m{SE_M_YAWN}voice.$"

RocketHideout_B3F_Text_PetrelBeaten:
	.string "I{SE_M_DIZZY_PUNCH}{SE_M_HEAL_BELL}couldn'{SE_M_SPIT_UP}d{SE_M_ATTRACT2}{SE_M_CHARGE}thing…\p"
	.string "GIOVANNI{SE_M_SUPERSONIC}pleas{SE_M_REVERSAL}forgiv{SE_M_REVERSAL}me…$"

RocketHideout_B3F_Text_PetrelAfterBattle:
	.string "PETREL{SE_M_HEAT_WAVE}Sinc{SE_M_REVERSAL}disbandin{SE_M_SANDSTORM}Team\n"
	.string "Rocke{SE_M_SPIT_UP}thre{SE_M_REVERSAL}year{SE_M_GRASSWHISTLE}ago{SE_M_SUPERSONIC}our\l"
	.string "GIOVANN{SE_M_HEAL_BELL}ha{SE_M_GRASSWHISTLE}bee{SE_M_ATTRACT}missing.\p"
	.string "Bu{SE_M_SPIT_UP}we'r{SE_M_REVERSAL}certai{SE_M_ATTRACT}he'{SE_M_GRASSWHISTLE}been\n"
	.string "waitin{SE_M_SANDSTORM}fo{SE_M_SAND_TOMB}th{SE_M_REVERSAL}righ{SE_M_SPIT_UP}tim{SE_M_REVERSAL}for\l"
	.string "ou{SE_M_SAND_TOMB}revival..{SE_M_PERISH_SONG}Wahahaha!\p"
	.string "Losin{SE_M_SANDSTORM}t{SE_M_ATTRACT2}yo{SE_M_DIVE}won'{SE_M_SPIT_UP}chang{SE_M_REVERSAL}the\n"
	.string "fac{SE_M_SPIT_UP}tha{SE_M_SPIT_UP}yo{SE_M_DIVE}ar{SE_M_REVERSAL}unabl{SE_M_REVERSAL}t{SE_M_ATTRACT2}get\l"
	.string "i{SE_M_ATTRACT}th{SE_M_REVERSAL}radio-transmitte{SE_M_SAND_TOMB}room!\p"
	.string "Yo{SE_M_DIVE}nee{SE_M_WATERFALL}m{SE_M_YAWN}voic{SE_M_REVERSAL}t{SE_M_ATTRACT2}unloc{SE_M_ENCORE2}it!$"

RocketHideout_B3F_EventScript_Murkrow::
	lock
	faceplayer
	waitse
	playmoncry 198, 0
	msgbox RocketHideout_B3F_Text_MurkrowSpeak1, MSGBOX_DEFAULT
	waitmoncry
	release
	end

RocketHideout_B3F_Text_MurkrowSpeak1:
	.string "MURKROW{SE_M_HEAT_WAVE}Hai{SE_M_BATON_PASS}GIOVANNI.$"

RocketHideout_B3F_Text_MurkrowMimic:
	.string "MURKRO{SE_M_DETECT}i{SE_M_GRASSWHISTLE}mimicking\n"
	.string "th{SE_M_REVERSAL}voic{SE_M_REVERSAL}o{SE_M_ACID_ARMOR}PETREL!\p"
	.string "Yo{SE_M_DIVE}ma{SE_M_YAWN}b{SE_M_REVERSAL}abl{SE_M_REVERSAL}to...!?$"

RocketHideout_B3F_Text_Murkrow:
	.string "MURKROW{SE_M_HEAT_WAVE}Th{SE_M_REVERSAL}passwor{SE_M_WATERFALL}is…\p"
	.string "HAI{SE_M_BRICK_BREAK}GIOVANNI.$"

RocketHideout_B3F_Text_GruntF5Seen:
	.string "D{SE_M_ATTRACT2}{SE_M_HEAL_BELL}kno{SE_M_TWISTER}th{SE_M_REVERSAL}password?\p"
	.string "Maybe.\p"
	.string "Bu{SE_M_SPIT_UP}n{SE_M_ATTRACT2}weakling'{SE_M_GRASSWHISTLE}goin{SE_M_SANDSTORM}t{SE_M_ATTRACT2}get\n"
	.string "it!$"

RocketHideout_B3F_Text_GruntF5Beaten:
	.string "Al{SE_M_BATON_PASS}right{SE_M_PERISH_SONG}Stop{SE_M_PERISH_SONG}I'l{SE_M_BATON_PASS}tel{SE_M_BATON_PASS}you.$"

RocketHideout_B3F_Text_GruntF5After:
	.string "Th{SE_M_REVERSAL}passwor{SE_M_WATERFALL}t{SE_M_ATTRACT2}th{SE_M_REVERSAL}boss{SE_M_ABSORB}room\n"
	.string "i{SE_M_GRASSWHISTLE}SLOWPOKETAIL.\p"
	.string "Bu{SE_M_SPIT_UP}it'{SE_M_GRASSWHISTLE}useles{SE_M_GRASSWHISTLE}unles{SE_M_GRASSWHISTLE}yo{SE_M_DIVE}have\n"
	.string "tw{SE_M_ATTRACT2}passwords.$"

RocketHideout_B3F_Text_GruntM28Seen:
	.string "Hyuck-hyuck-hyuck!\p"
	.string "{SE_M_HEAL_BELL}remembe{SE_M_SAND_TOMB}yo{SE_M_DIVE}fro{SE_M_MILK_DRINK}th{SE_M_REVERSAL}well!\p"
	.string "You'r{SE_M_REVERSAL}challengin{SE_M_SANDSTORM}m{SE_M_REVERSAL}again?\p"
	.string "Hah{SE_M_DRAGON_RAGE}You'r{SE_M_REVERSAL}nuts{SE_M_SUPERSONIC}bu{SE_M_SPIT_UP}yo{SE_M_DIVE}have\n"
	.string "guts!\p"
	.string "I'l{SE_M_BATON_PASS}war{SE_M_ATTRACT}you{SE_M_SUPERSONIC}{SE_M_HEAL_BELL}go{SE_M_SPIT_UP}better!\p"
	.string "I{SE_M_ACID_ARMOR}yo{SE_M_DIVE}ca{SE_M_ATTRACT}bea{SE_M_SPIT_UP}me{SE_M_SUPERSONIC}I'l{SE_M_BATON_PASS}tell\l"
	.string "yo{SE_M_DIVE}{SE_M_CHARGE}passwor{SE_M_WATERFALL}t{SE_M_ATTRACT2}th{SE_M_REVERSAL}boss'\n"
	.string "room!$"

RocketHideout_B3F_Text_GruntM28Beaten:
	.string "Hyuck-hyuck-hyuck{SE_M_DRAGON_RAGE}You'r{SE_M_REVERSAL}good!$"

RocketHideout_B3F_Text_GruntM28After:
	.string "Hyuck-hyuck-hyuck!\p"
	.string "Th{SE_M_REVERSAL}passwor{SE_M_WATERFALL}t{SE_M_ATTRACT2}th{SE_M_REVERSAL}boss{SE_M_ABSORB}room…\p"
	.string "Uh…{SE_M_SUPERSONIC}{SE_M_HEAL_BELL}thin{SE_M_ENCORE2}i{SE_M_SPIT_UP}i{SE_M_GRASSWHISTLE}RATICAT{SE_M_SWORDS_DANCE}TAIL.$"

RocketHideout_B3F_Text_ScientistRossSeen:
	.string "{SE_M_HEAL_BELL}use{SE_M_WATERFALL}t{SE_M_ATTRACT2}wor{SE_M_ENCORE2}fo{SE_M_SAND_TOMB}SILPH{SE_M_SUPERSONIC}bu{SE_M_SPIT_UP}now\n"
	.string "{SE_M_HEAL_BELL}ru{SE_M_ATTRACT}researc{SE_M_TRI_ATTACK}fo{SE_M_SAND_TOMB}TEA{SE_M_GIGA_DRAIN}ROCKET.\p"
	.string "{SE_M_BONEMERANG}meddlesom{SE_M_REVERSAL}chil{SE_M_WATERFALL}lik{SE_M_REVERSAL}yo{SE_M_DIVE}needs\n"
	.string "t{SE_M_ATTRACT2}b{SE_M_REVERSAL}punished.$"

RocketHideout_B3F_Text_ScientistRossBeaten:
	.string "{SE_M_BONEMERANG}mer{SE_M_REVERSAL}tactica{SE_M_BATON_PASS}erro{SE_M_SAND_TOMB}cos{SE_M_SPIT_UP}me…$"

RocketHideout_B3F_Text_ScientistRossAfter:
	.string "{SE_M_BONEMERANG}radi{SE_M_ATTRACT2}signa{SE_M_BATON_PASS}tha{SE_M_SPIT_UP}drives\n"
	.string "POKéMO{SE_M_PSYBEAM2}mad…\p"
	.string "M{SE_M_YAWN}experimen{SE_M_SPIT_UP}i{SE_M_GRASSWHISTLE}{SE_M_CHARGE}complete\n"
	.string "success.\p"
	.string "M{SE_M_YAWN}promotio{SE_M_ATTRACT}i{SE_M_GRASSWHISTLE}assured{SE_M_PERISH_SONG}This\n"
	.string "los{SE_M_GRASSWHISTLE}mean{SE_M_GRASSWHISTLE}absolutel{SE_M_YAWN}nothing.$"

RocketHideout_B3F_Text_ScientistMitchSeen:
	.string "{SE_M_HEAL_BELL}don'{SE_M_SPIT_UP}car{SE_M_REVERSAL}tha{SE_M_SPIT_UP}POKéMO{SE_M_PSYBEAM2}ar{SE_M_REVERSAL}hurt\n"
	.string "b{SE_M_YAWN}ou{SE_M_SAND_TOMB}experiment.$"

RocketHideout_B3F_Text_ScientistMitchBeaten:
	.string "Thinkin{SE_M_SANDSTORM}i{SE_M_GRASSWHISTLE}m{SE_M_YAWN}stron{SE_M_SANDSTORM}suit{SE_M_SUPERSONIC}not\n"
	.string "battling.$"

RocketHideout_B3F_Text_ScientistMitchAfter:
	.string "I{SE_M_ACID_ARMOR}w{SE_M_REVERSAL}tur{SE_M_ATTRACT}u{SE_M_MORNING_SUN}th{SE_M_REVERSAL}powe{SE_M_SAND_TOMB}o{SE_M_ACID_ARMOR}our\n"
	.string "radi{SE_M_ATTRACT2}signa{SE_M_BATON_PASS}fo{SE_M_SAND_TOMB}broadcast\l"
	.string "nationwide…\p"
	.string "Th{SE_M_REVERSAL}ver{SE_M_YAWN}though{SE_M_SPIT_UP}excite{SE_M_GRASSWHISTLE}me!$"

