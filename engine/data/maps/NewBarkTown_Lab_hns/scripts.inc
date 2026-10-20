@ Johto (data/maps/NewBarkTown_Lab_hns/scripts.inc), as built into the FireRed game.

NewBarkTown_Lab_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, NewBarkTown_Lab_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, NewBarkTown_Lab_OnFrame
	.byte 0

NewBarkTown_Lab_OnTransition::
	goto_if_eq JOHTO_VAR_NEWBARKTOWN_LABSTATE, 6, NewBarkTown_Lab_EventScript_ElmAtComputer
	goto_if_eq JOHTO_VAR_NEWBARKTOWN_LABSTATE, 2, NewBarkTown_Lab_EventScript_ElmAtComputer
	goto_if_eq JOHTO_VAR_NEWBARKTOWN_LABSTATE, 3, NewBarkTown_Lab_EventScript_ElmAtComputer
	end

NewBarkTown_Lab_OnFrame::
	map_script_2 JOHTO_VAR_NEWBARKTOWN_LABSTATE, 4, NewBarkTown_Lab_EventScript_PoliceEpisode
	.2byte 0

NewBarkTown_Lab_EventScript_ElmAtComputer::
	setobjectxyperm LOCALID_ELM, 3, 2
	setobjectmovementtype LOCALID_ELM, MOVEMENT_TYPE_FACE_UP
	end

NewBarkTown_Lab_EventScript_TriggerStartLabLeft::
	lock
	applymovement OBJ_EVENT_ID_PLAYER, NewBarkTown_Lab_Movement_WalkRight
	waitmovement 0
	goto NewBarkTown_Lab_EventScript_TriggerStartLab
	end

NewBarkTown_Lab_EventScript_TriggerStartLabRight::
	lock
	applymovement OBJ_EVENT_ID_PLAYER, NewBarkTown_Lab_Movement_WalkLeft
	waitmovement 0
	goto NewBarkTown_Lab_EventScript_TriggerStartLab
	end

NewBarkTown_Lab_EventScript_TriggerStartLab::
	lock
	applymovement OBJ_EVENT_ID_PLAYER, NewBarkTown_LabMovement_WalkToElm
	waitmovement 0
	goto NewBarkTown_Lab_EventScript_ElmIntro
	end

NewBarkTown_EventScript_Aide1::
	lock
	faceplayer
	msgbox NewBarkTown_Lab_Text_AideAlwaysBusy, MSGBOX_DEFAULT
	closemessage
	release
	end

NewBarkTown_EventScript_Aide2::
	lock
	faceplayer
	goto_if_eq JOHTO_VAR_NEWBARKTOWN_LABSTATE, 5, NewBarkTown_EventScript_Aide2Testimony
	msgbox NewBarkTown_Lab_Text_AideSave, MSGBOX_DEFAULT
	closemessage
	release
	end

NewBarkTown_EventScript_Aide2Testimony::
	msgbox NewBarkTown_Lab_Text_AideTheftTestimony, MSGBOX_DEFAULT
	closemessage
	release
	end

NewBarkTown_Lab_EventScript_Elm::
	lock
	faceplayer
	goto_if_set JOHTO_FLAG_HIDE_NEWBARKTOWN_LAB_AIDE, NewBarkTown_Lab_EventScript_ElmAideIsWaiting
	goto_if_eq JOHTO_VAR_NEWBARKTOWN_LABSTATE, 7, NewBarkTown_Lab_EventScript_ElmMasterBall
	goto_if_eq JOHTO_VAR_NEWBARKTOWN_LABSTATE, 8, NewBarkTown_Lab_EventScript_ElmKimono
	goto_if_eq JOHTO_VAR_NEWBARKTOWN_LABSTATE, 9, NewBarkTown_Lab_EventScript_ElmLeague
	goto_if_eq JOHTO_VAR_NEWBARKTOWN_LABSTATE, 10, NewBarkTown_Lab_EventScript_ElmSSTicket

	goto_if_unset JOHTO_FLAG_RECEIVED_TOGEPI_EGG, NewBarkTown_Lab_EventScript_Elm_AfterEggCheck
	goto_if_set JOHTO_FLAG_SHOWN_ELM_TOGEPI, NewBarkTown_Lab_EventScript_Elm_CallMe
	call_if_unset JOHTO_FLAG_SHOWN_ELM_TOGEPI, NewBarkTown_Lab_EventScript_Elm_Check_Togepi

NewBarkTown_Lab_EventScript_Elm_AfterEggCheck:
	goto_if_ge JOHTO_VAR_GOLDENROD_CITY_STATE, 1, NewBarkTown_Lab_EventScript_Elm_Check_WhereIsEgg
	goto_if_eq JOHTO_VAR_NEWBARKTOWN_LABSTATE, 5, NewBarkTown_Lab_EventScript_ElmState5

	goto_if_ge JOHTO_VAR_NEWBARKTOWN_LABSTATE, 6, NewBarkTown_Lab_EventScript_ElmState5
	goto_if_eq JOHTO_VAR_NEWBARKTOWN_LABSTATE, 2, CopNewBarkTown_Lab_EventScript_ElmState2
	goto_if_eq JOHTO_VAR_NEWBARKTOWN_LABSTATE, 3, CopNewBarkTown_Lab_EventScript_ElmState2
	goto_if_eq JOHTO_VAR_NEWBARKTOWN_LABSTATE, 0, NewBarkTown_Lab_EventScript_ElmIntro
	goto_if_eq JOHTO_VAR_NEWBARKTOWN_LABSTATE, 1, NewBarkTown_Lab_EventScript_ElmChoosePokemon
	end

NewBarkTown_Lab_EventScript_ElmAideIsWaiting::
	msgbox NewBarkTown_Lab_Text_ElmAideIsWaiting, MSGBOX_DEFAULT
	closemessage
	release
	end

NewBarkTown_Lab_Text_ElmAideIsWaiting:
	.string "{PLAYER}!\p"
	.string "What are you doing here?\p"
	.string "My aide is still waiting for you\n"
	.string "In VIOLET CITY!$"

NewBarkTown_Lab_EventScript_ElmIntro::
	call RB_ElmBird
	msgbox NewBarkTown_Lab_Text_ElmIntro, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, NewBarkTown_Lab_EventScript_ElmAccepted
	goto_if_eq VAR_RESULT, NO, NewBarkTown_Lab_EventScript_ElmRefused
	end

NewBarkTown_Lab_EventScript_ElmRefused::
	msgbox NewBarkTown_Lab_Text_ElmRefused, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, NewBarkTown_Lab_EventScript_ElmAccepted
	goto_if_eq VAR_RESULT, NO, NewBarkTown_Lab_EventScript_ElmRefused
	end

NewBarkTown_Lab_EventScript_ElmAccepted::
	msgbox NewBarkTown_Lab_Text_ElmAccepted, MSGBOX_DEFAULT
	msgbox NewBarkTown_Lab_Text_ElmResearchAmbitions, MSGBOX_DEFAULT
	delay 30
	playse SE_PC_LOGIN
	waitse
	playse SE_PIN
	applymovement LOCALID_ELM, J_Common_Movement_QuestionMark
	delay 55
	waitmovement LOCALID_ELM
	applymovement LOCALID_ELM, NewBarkTown_Lab_Movement_CheckEmail
	applymovement OBJ_EVENT_ID_PLAYER, NewBarkTown_Lab_Movement_Look_Left
	waitmovement 0
	waitmovement 0
	msgbox NewBarkTown_Lab_Text_ElmGotAnEmail, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_ELM, NewBarkTown_Lab_Movement_ReturnFromEmail
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, NewBarkTown_Lab_Movement_Look_Up
	waitmovement 0
	delay 30
	msgbox NewBarkTown_Lab_Text_ElmMissionFromMrPokemon, MSGBOX_DEFAULT
	goto NewBarkTown_Lab_EventScript_ElmChoosePokemon
	end

NewBarkTown_Lab_EventScript_ElmChoosePokemon::
	msgbox NewBarkTown_Lab_Text_ElmChooseAPokemon, MSGBOX_DEFAULT
	closemessage
	call_if_unset JOHTO_FLAG_RECEIVED_POKENAV, NewBarkTown_PlayersHouse_1F_EventScript_GivePokeGear
	goto NewBarkTown_Lab_EventScript_MrPokemon
	end

NewBarkTown_Lab_EventScript_TriggerReturnPlayer::
	lock
	msgbox NewBarkTown_Lab_Text_ElmWhereGoing, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, NewBarkTown_Lab_Movement_ReturnPlayer
	waitmovement 0
	release
	end

NewBarkTown_Lab_EventScript_ShouldntTouch::
	msgbox NewBarkTown_Lab_Text_ShouldntTouch, MSGBOX_DEFAULT
	closemessage
	release
	end

NewBarkTown_Lab_EventScript_ChikoritaBall::
	msgbox NewBarkTown_Lab_Text_ElmPokeBall, MSGBOX_DEFAULT
	closemessage
	release
	end

NewBarkTown_Lab_EventScript_CyndaquilBall::
	msgbox NewBarkTown_Lab_Text_ElmPokeBall, MSGBOX_DEFAULT
	closemessage
	release
	end

NewBarkTown_Lab_EventScript_TotodileBall::
	msgbox NewBarkTown_Lab_Text_ElmPokeBall, MSGBOX_DEFAULT
	closemessage
	release
	end

NewBarkTown_Lab_EventScript_MrPokemon::
	setvar JOHTO_VAR_NEWBARKTOWN_LABSTATE, 2
	setvar JOHTO_VAR_NEWBARK_TOWN_STATE, 3
	msgbox NewBarkTown_Lab_Text_ElmDirections1_Register, MSGBOX_DEFAULT
	playfanfare MUS_REGISTER_MATCH_CALL
	msgbox NewBarkTown_Lab_Text_RegisteredElm, MSGBOX_DEFAULT
	waitfanfare
	setflag JOHTO_FLAG_ENABLE_PROF_BIRCH_MATCH_CALL
	msgbox NewBarkTown_Lab_Text_ElmDirections2, MSGBOX_DEFAULT
	closemessage
	goto_if_eq VAR_FACING, DIR_EAST, NewBarkTown_Lab_EventScript_MrPokemonMovementSafe
	applymovement LOCALID_ELM, NewBarkTown_Lab_Movement_CheckEmailSlow
	waitmovement 0
	clearflag JOHTO_FLAG_RECEIVED_FIRST_BALLS
	clearflag JOHTO_FLAG_RECEIVED_FIRST_POTION
	setvar JOHTO_VAR_NEWBARK_TOWN_STATE, 3
	setflag JOHTO_FLAG_ENABLE_CONDITION
	release
	end

NewBarkTown_Lab_EventScript_MrPokemonMovementSafe::
	applymovement LOCALID_ELM, NewBarkTown_Lab_Movement_GotoComputerSafe
	waitmovement 0
	clearflag JOHTO_FLAG_RECEIVED_FIRST_BALLS
	clearflag JOHTO_FLAG_RECEIVED_FIRST_POTION
	setvar JOHTO_VAR_NEWBARK_TOWN_STATE, 3
	release
	end

CopNewBarkTown_Lab_EventScript_ElmState2::
	msgbox NewBarkTown_Lab_Text_ElmDirections1, MSGBOX_DEFAULT
	msgbox NewBarkTown_Lab_Text_ElmDirections2, MSGBOX_DEFAULT
	applymovement LOCALID_ELM, J_Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	closemessage
	release
	end

NewBarkTown_Lab_EventScript_HealingMachine1::
	lock
	goto_if_set FLAG_SYS_POKEMON_GET, NewBarkTown_Lab_EventScript_HealingMachine2
	msgbox J_LittlerootTown_ProfessorBirchsLab_Text_SeriousLookingMachine, MSGBOX_SIGN
	closemessage
	release
	end

NewBarkTown_Lab_EventScript_HealingMachine2::
	call J_Common_EventScript_OutOfCenterPartyHeal
	release
	end

NewBarkTown_Lab_EventScript_TriggerAideGivePotion::
	lock
	applymovement LOCALID_AIDE1, NewBarkTown_Lab_Movement_Aide1WalkToPlayer
	waitmovement 0
	turnobject OBJ_EVENT_ID_PLAYER, DIR_WEST
	msgbox NewBarkTown_Lab_Text_AideGivePotion, MSGBOX_DEFAULT
	closemessage
	giveitem ITEM_POTION
	goto_if_eq VAR_RESULT, FALSE, J_Common_EventScript_ShowBagIsFull
	setflag JOHTO_FLAG_RECEIVED_FIRST_POTION
	setvar JOHTO_VAR_NEWBARKTOWN_LABSTATE, 3
	applymovement LOCALID_AIDE1, NewBarkTown_Lab_Movement_Aide1LeavePlayer
	waitmovement 0
	turnobject OBJ_EVENT_ID_PLAYER, DIR_SOUTH
	release
	end

NewBarkTown_Lab_EventScript_HideCyndaquil::
	setflag JOHTO_FLAG_HIDE_CYNDAQUILBALL
	return

NewBarkTown_Lab_EventScript_HideTotodile::
	setflag JOHTO_FLAG_HIDE_TOTODILEBALL
	return

NewBarkTown_Lab_EventScript_HideChikorita::
	setflag JOHTO_FLAG_HIDE_CHIKORITABALL
	return

NewBarkTown_Lab_EventScript_PoliceEpisode::
	lock
	setmetatile 7, 1, METATILE_R26_21_Broken_Window, TRUE
	call_if_eq JOHTO_VAR_STARTER_MON, 0 NewBarkTown_Lab_EventScript_HideCyndaquil
	call_if_eq JOHTO_VAR_STARTER_MON, 1 NewBarkTown_Lab_EventScript_HideTotodile
	call_if_eq JOHTO_VAR_STARTER_MON, 2 NewBarkTown_Lab_EventScript_HideChikorita
	applymovement OBJ_EVENT_ID_PLAYER, NeBarkTownLab_Movement_PlayerWalkToCop
	waitmovement 0
	setflag JOHTO_FLAG_HIDE_LAB_POLICEMAN
	turnobject 7 DIR_WEST
	msgbox NewBarkTown_Lab_Text_Officer1, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, NewBarkTown_Lab_EventScript_PoliceYes
	goto_if_eq VAR_RESULT, NO, NewBarkTown_Lab_EventScript_PoliceNo
	end

NewBarkTown_Lab_EventScript_PoliceNo::
	msgbox NewBarkTown_Lab_Text_OfficerNo, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, NewBarkTown_Lab_EventScript_PoliceYes
	goto_if_eq VAR_RESULT, NO, NewBarkTown_Lab_EventScript_PoliceNo
	end

NewBarkTown_Lab_EventScript_PoliceYes::
	closemessage
	special NameRival
	waitstate
	msgbox NewBarkTown_Lab_Text_Officer2_1, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, FALSE, NewBarkTown_Lab_EventScript_PoliceYes
	msgbox NewBarkTown_Lab_Text_Officer2, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_COP, NewBarkTown_Lab_Movement_CopLeaves
	waitmovement 0
	removeobject LOCALID_COP


	applymovement OBJ_EVENT_ID_PLAYER, NewBarkTown_Lab_Movement_PlayerStepsToElm
	waitmovement 0
	msgbox NewBarkTown_Lab_Text_ElmAfterTheft1, MSGBOX_DEFAULT
	playfanfare MUS_LEVEL_UP
	msgbox NewBarkTown_Lab_Text_ElmAfterTheft2, MSGBOX_DEFAULT
	waitfanfare
	closemessage
	applymovement LOCALID_ELM, NewBarkTown_Lab_Movement_ElmStepBack
	waitmovement 0
	msgbox NewBarkTown_Lab_Text_ElmAfterTheft3, MSGBOX_DEFAULT
	delay 20
	closemessage
	applymovement LOCALID_ELM, NewBarkTown_Lab_Movement_ElmStepForward
	waitmovement 0
	msgbox NewBarkTown_Lab_Text_ElmAfterTheft4, MSGBOX_DEFAULT
	closemessage
	setvar JOHTO_VAR_NEWBARKTOWN_LABSTATE, 5
	setvar JOHTO_VAR_NEWBARK_TOWN_STATE, 4
	setflag JOHTO_FLAG_HIDE_MOMS_FRIEND
	clearflag JOHTO_FLAG_HIDE_MOMS_FRIEND2
	setflag JOHTO_FLAG_ADVENTURE_STARTED
	removeitem ITEM_MYSTERY_EGG
	release
	end

NewBarkTown_Lab_EventScript_ElmState5::
	lock
	faceplayer
	msgbox NewBarkTown_Lab_Text_ElmStudyingEgg, MSGBOX_DEFAULT
	closemessage
	applymovement 2 J_Common_Movement_FaceOriginalDirection
	release
	end

NewBarkTown_Lab_EventScript_ElmMasterBall::
	lock
	faceplayer
	msgbox NewBarkTown_Lab_Text_ElmGiveMasterBall1, MSGBOX_DEFAULT
	giveitem ITEM_MASTER_BALL
	msgbox NewBarkTown_Lab_Text_ElmGiveMasterBall2, MSGBOX_DEFAULT
	closemessage
	delay 20
	playse SE_PIN
	applymovement LOCALID_ELM, J_Common_Movement_ExclamationMark
	delay 55
	waitmovement LOCALID_ELM
	msgbox NewBarkTown_Lab_Text_KimonoGirls, MSGBOX_DEFAULT
	closemessage
	setvar JOHTO_VAR_NEWBARKTOWN_LABSTATE, 8
	setvar JOHTO_VAR_ECRUTEAK_CITY_THEATER, 4
	setflag JOHTO_FLAG_HIDE_ECRUTEAK_SILVER
	setflag JOHTO_FLAG_HIDE_ECRUTEAK_CITY_THEATER_NPCS
	clearflag JOHTO_FLAG_HIDE_ECRUTEAK_CITY_THEATER_KIMONOS
	release
	end

NewBarkTown_Lab_EventScript_ElmKimono::
	lock
	faceplayer
	msgbox NewBarkTown_Lab_Text_KimonoWaiting, MSGBOX_DEFAULT
	closemessage
	release
	end

NewBarkTown_Lab_EventScript_ElmLeague::
	lock
	faceplayer
	msgbox NewBarkTown_Lab_Text_League, MSGBOX_DEFAULT
	closemessage
	release
	end

NewBarkTown_Lab_EventScript_ElmSSTicket::
	msgbox NewBarkTown_Lab_Text_ElmGiveTicket1, MSGBOX_DEFAULT
	giveitem ITEM_SS_TICKET
	msgbox NewBarkTown_Lab_Text_ElmGiveTicket2, MSGBOX_DEFAULT
	closemessage
	clearflag JOHTO_FLAG_HIDE_SSAQUA_1F_GRANDPA
	setvar JOHTO_VAR_NEWBARKTOWN_LABSTATE, 11
	clearflag JOHTO_FLAG_HIDE_OLIVINE_PORT_OAK
	release
	end

NewBarkTown_Lab_EventScript_TriggerAideGiveBalls::
	lock
	applymovement LOCALID_AIDE1, NewBarkTown_Lab_Movement_Aide1WalkToPlayer
	waitmovement 0
	turnobject OBJ_EVENT_ID_PLAYER, DIR_WEST
	msgbox NewBarkTown_Lab_Text_AideGiveBalls, MSGBOX_DEFAULT
	closemessage
	giveitem ITEM_POKE_BALL, 5
	goto_if_eq VAR_RESULT, FALSE, J_Common_EventScript_ShowBagIsFull
	setflag JOHTO_FLAG_RECEIVED_FIRST_BALLS
	setvar JOHTO_VAR_NEWBARKTOWN_LABSTATE, 6
	applymovement LOCALID_AIDE1, NewBarkTown_Lab_Movement_Aide1LeavePlayer
	waitmovement 0
	turnobject OBJ_EVENT_ID_PLAYER, DIR_SOUTH
	release
	end

NewBarkTown_Lab_EventScript_Elm_Check_WhereIsEgg::
	msgbox NewBarkTown_Lab_Text_ElmWaitingEggHatch, MSGBOX_DEFAULT
	closemessage
	release
	end

NewBarkTown_Lab_EventScript_Elm_Check_Togepi::
	checkspecies SPECIES_TOGEPI
	goto_if_eq VAR_RESULT, TRUE, NewBarkTown_Lab_EventScript_Elm_Togepi_Seen
	checkspecies SPECIES_TOGETIC
	goto_if_eq VAR_RESULT, TRUE, NewBarkTown_Lab_EventScript_Elm_Togepi_Seen
	checkspecies SPECIES_TOGEKISS
	goto_if_eq VAR_RESULT, TRUE, NewBarkTown_Lab_EventScript_Elm_Togepi_Seen
	return

NewBarkTown_Lab_EventScript_Elm_Togepi_Seen::
	msgbox NewBarkTown_Lab_Text_ShowTogepi1, MSGBOX_DEFAULT
	waitmessage
	msgbox NewBarkTown_Lab_Text_ShowTogepi2, MSGBOX_DEFAULT
	waitmessage
	msgbox NewBarkTown_Lab_Text_ShowTogepi3, MSGBOX_DEFAULT
	waitmessage
	msgbox NewBarkTown_Lab_Text_ElmGiveEverstone1, MSGBOX_DEFAULT
	waitmessage
	giveitem ITEM_EVERSTONE
	goto_if_eq VAR_RESULT, FALSE, J_Common_EventScript_ShowBagIsFull
	msgbox NewBarkTown_Lab_Text_ElmGiveEverstone2, MSGBOX_DEFAULT
	closemessage
	setflag JOHTO_FLAG_SHOWN_ELM_TOGEPI
	release
	end

NewBarkTown_Lab_EventScript_Elm_CallMe::
	msgbox NewBarkTown_Lab_Text_Elm_CallMe, MSGBOX_DEFAULT
	closemessage
	release
	end

NewBarkTown_Lab_Movement_WalkRight:
	walk_right
	step_end

NewBarkTown_Lab_Movement_WalkLeft:
	walk_left
	step_end

NewBarkTown_LabMovement_WalkToElm:
	walk_up
	walk_up
	walk_up
	step_end

NewBarkTown_Lab_Movement_ReturnPlayer:
	walk_up
	step_end

NewBarkTown_Lab_Movement_CheckEmail:
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_up
	step_end

NewBarkTown_Lab_Movement_CheckEmailSlow:
	walk_left
	walk_left
	walk_left
	walk_up
	step_end

NewBarkTown_Lab_Movement_GotoComputerSafe:
	walk_up
	walk_left
	walk_left
	walk_left
	face_up
	step_end

NewBarkTown_Lab_Movement_ReturnFromEmail:
	walk_fast_down
	walk_fast_right
	walk_fast_right
	walk_fast_right
	face_down
	step_end

NewBarkTown_Lab_Movement_Look_Left:
	face_left
	step_end

NewBarkTown_Lab_Movement_Look_Up:
	face_up
	step_end

NewBarkTown_Lab_Movement_Aide1WalkToPlayer:
	walk_down
	walk_down
	walk_right
	walk_right
	step_end

NewBarkTown_Lab_Movement_Aide1LeavePlayer:
	walk_left
	walk_left
	walk_up
	walk_up
	face_down
	step_end

NeBarkTownLab_Movement_PlayerWalkToCop:
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_left
	walk_fast_up
	face_right
	step_end

NewBarkTown_Lab_Movement_CopLeaves:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

NewBarkTown_Lab_Movement_PlayerStepsToElm:
	walk_right
	face_up
	step_end

NewBarkTown_Lab_Movement_ElmStepBack:
	lock_facing_direction
	walk_fast_up
	unlock_facing_direction
	step_end

NewBarkTown_Lab_Movement_ElmStepForward:
	walk_fast_down
	step_end

NewBarkTown_Lab_Text_ShouldntTouch:
	.string "Probably shouldn't touch!$"

NewBarkTown_Lab_Text_ElmIntro::
	.string "ELM: You must be {PLAYER}!\p"
	.string "PROF.OAK told me about your\n"
	.string "victory at the KANTO LEAGUE.\p"
	.string "Welcome to JOHTO! Your experience\n"
	.string "could help with my research.\p"
	.string "There is something I'd like your\n"
	.string "help investigating. Will you help?$"

NewBarkTown_Lab_Text_ElmAccepted:
	.string "Thanks, {PLAYER}!\n"
	.string "You're a great help!$"

NewBarkTown_Lab_Text_ElmRefused:
	.string "But… Please, I need your\n"
	.string "help!$"

NewBarkTown_Lab_Text_ElmResearchAmbitions:
	.string "When I announce my findings,\n"
	.string "I'm sure we'll delve deeper\p"
	.string "into the many mysteries of\n"
	.string "POKéMON.\p"
	.string "You can count on it!$"

NewBarkTown_Lab_Text_ElmGotAnEmail:
	.string "Oh, hey! I got an e-mail!\p"
	.string "… … … … … … … …\n"
	.string "Hm… Uh-huh…\p"
	.string "Okay…$"

NewBarkTown_Lab_Text_ElmMissionFromMrPokemon:
	.string "Hey, listen.\p"
	.string "I have an acquaintance called\n"
	.string "MR. POKéMON.\p"
	.string "He keeps finding weird things and\n"
	.string "raving about his discoveries.\p"
	.string "Anyway, I just got an e-mail\n"
	.string "from him saying that this\l"
	.string "time it's real.\p"
	.string "It is intriguing, but we're\n"
	.string "busy with our POKéMON research...\p"
	.string "Wait!\n"
	.string "I know!\p"
	.string "{PLAYER}, can you go in our\n"
	.string "place?$"

NewBarkTown_Lab_Text_ElmChooseAPokemon::
	.string "Your own POKéMON have brought you\n"
	.string "all the way from KANTO.\p"
	.string "Please take them with you on this\n"
	.string "errand. I know I can trust you!\p"
	.string "I have arranged a POKéGEAR so we\n"
	.string "can keep in touch along the way.$"

NewBarkTown_Lab_Text_ElmWhereGoing:
	.string "ELM: Wait! Where are you\n"
	.string "going?$"

NewBarkTown_Lab_Text_ElmDirections1:
	.string "MR. POKéMON lives a little bit\n"
	.string "beyond CHERRYGROVE, the next\l"
	.string "city over.\p"
	.string "It's almost a direct route\n"
	.string "there, so you can't miss it.\p"
	.string "But just in case, you have my\n"
	.string "phone number. Call me if\l"
	.string "anything comes up!$"

NewBarkTown_Lab_Text_ElmDirections1_Register:
	.string "MR. POKéMON lives a little bit\n"
	.string "beyond CHERRYGROVE, the next\l"
	.string "city over.\p"
	.string "It's almost a direct route\n"
	.string "there, so you can't miss it.\p"
	.string "But just in case, here's my\n"
	.string "phone number. Call me if\l"
	.string "anything comes up!$"

NewBarkTown_Lab_Text_RegisteredElm:
	.string "Registered PROF.ELM\n"
	.string "in the POKéGEAR.$"

NewBarkTown_Lab_Text_ElmLetYourMonBattle:
	.string "JOHTO's wild POKéMON may be\n"
	.string "different from those in KANTO.$"

NewBarkTown_Lab_Text_ElmDirections2::
	.string "Your team is welcome to use the\n"
	.string "healing machine to my right.\p"
	.string "There are POKéMON CENTERS in the\n"
	.string "towns along the way, too.\p"
	.string "I'm counting on you!$"

NewBarkTown_Lab_Text_GotElmsNumber:
	.string "{PLAYER} got ELM's phone\n"
	.string "number.$"

NewBarkTown_Lab_Text_ElmDescribesMrPokemon:
	.string "MR. POKéMON goes everywhere and\n"
	.string "finds rarities.\p"
	.string "Too bad they're just rare and\n"
	.string "not very useful…$"

NewBarkTown_Lab_Text_ElmPokeBall:
	.string "It contains a POKéMON caught\n"
	.string "by PROF.ELM.$"

NewBarkTown_Lab_Text_ElmAfterTheft1:
	.string "ELM: {PLAYER}, this is terrible…\p"
	.string "Oh, yes, what was MR. POKéMON's\n"
	.string "big discovery?$"

NewBarkTown_Lab_Text_ElmAfterTheft2:
	.string "{PLAYER} handed the MYSTERY EGG\n"
	.string "to PROF.ELM.$"

NewBarkTown_Lab_Text_ElmAfterTheft3:
	.string "ELM: This?$"

NewBarkTown_Lab_Text_ElmAfterTheft4::
	.string "A POKéMON EGG! This will help\n"
	.string "with my research.\p"
	.string "You met PROF.OAK at MR.POKéMON's?\n"
	.string "I'm glad he could see you again.\p"
	.string "He was right to recommend you.\n"
	.string "Thank you for bringing this back.\p"
	.string "If you'd like another challenge,\n"
	.string "JOHTO has its own POKéMON GYMS.\p"
	.string "The closest is in VIOLET CITY.\p"
	.string "Before you leave, visit the woman\n"
	.string "in the guest house. She can help\l"
	.string "you keep in touch while traveling.$"

NewBarkTown_Lab_Text_ElmStudyingEgg:
	.string "ELM: Don't give up!\n"
	.string "I'll call if I learn anything\l"
	.string "about that EGG!$"

NewBarkTown_Lab_Text_ElmAideHasEgg:
	.string "ELM: {PLAYER}? Didn't you meet\n"
	.string "my assistant?\p"
	.string "He should have met you with\n"
	.string "the EGG at VIOLET CITY's\p"
	.string "POKéMON CENTER.\p"
	.string "You must have just missed him.\n"
	.string "Try to catch him there.$"

NewBarkTown_Lab_Text_ElmWaitingEggHatch:
	.string "ELM: Hey, has that EGG changed\n"
	.string "any?$"

NewBarkTown_Lab_Text_ElmThoughtEggHatched:
	.string "{PLAYER}? I thought the EGG\n"
	.string "hatched.\p"
	.string "Where is the POKéMON?$"

NewBarkTown_Lab_Text_ShowTogepi1:
	.string "ELM: {PLAYER}, you look great!$"

NewBarkTown_Lab_Text_ShowTogepi2:
	.string "What? That POKéMON!?!$"

NewBarkTown_Lab_Text_ShowTogepi3:
	.string "The EGG hatched into TOGEPI!\p"
	.string "Watching it grow will help my\n"
	.string "research into POKéMON EGGS.\p"
	.string "There's still so much to learn\n"
	.string "about this species!$"

NewBarkTown_Lab_Text_ElmGiveEverstone1:
	.string "Thanks, {PLAYER}! You're helping\n"
	.string "unravel POKéMON mysteries for us!\p"
	.string "I want you to have this as a\n"
	.string "token of our appreciation.$"

NewBarkTown_Lab_Text_ElmGiveEverstone2:
	.string "You may know this from KANTO:\n"
	.string "a POKéMON holding an EVERSTONE\l"
	.string "won't evolve.\p"
	.string "It can help while we study how\n"
	.string "POKéMON grow.$"

NewBarkTown_Lab_Text_ElmCallYou:
	.string "ELM: {PLAYER}, I'll call you if\n"
	.string "anything comes up.$"

NewBarkTown_Lab_Text_AideAfterTheft:
	.string "…sigh… That stolen POKéMON.\p"
	.string "I wonder how it's doing.\p"
	.string "They say a POKéMON raised by a\n"
	.string "bad person turns bad itself.$"

NewBarkTown_Lab_Text_ElmGiveMasterBall1:
	.string "ELM: Hi, {PLAYER}!\p"
	.string "Thanks to you, my research is\n"
	.string "going great!\p"
	.string "Take this as a token of my\n"
	.string "appreciation.$"

NewBarkTown_Lab_Text_ElmGiveMasterBall2:
	.string "The MASTER BALL is the best!\p"
	.string "It's the ultimate BALL! It'll\n"
	.string "catch any POKéMON without fail.\p"
	.string "It's given only to recognized\n"
	.string "POKéMON researchers.\p"
	.string "I think you can make much better\n"
	.string "use of it than I can, {PLAYER}!$"

NewBarkTown_Lab_Text_KimonoGirls:
	.string "By the way...\n"
	.string "A group of beautiful KIMONO\l"
	.string "GIRLS were looking for you.\p"
	.string "They told me they are\n"
	.string "waiting for you at the\l"
	.string "ECRUTEAK DANCE THEATER.\p"
	.string "I know you've gone through many\n"
	.string "things since that EGG got you\l"
	.string "involved in all this...\p"
	.string "I hope you'll carry through it.$"

NewBarkTown_Lab_Text_KimonoWaiting:
	.string "PROF.ELM: The KIMONO\n"
	.string "GIRLS are waiting for you at\l"
	.string "the ECRUTEAK DANCE THEATER.$"

NewBarkTown_Lab_Text_League:
	.string "PROF.ELM: Well done, {PLAYER}!\p"
	.string "You came here as KANTO's\n"
	.string "CHAMPION and helped us so much.\p"
	.string "Now JOHTO's LEAGUE is waiting.\n"
	.string "Take your team to INDIGO PLATEAU!\p"
	.string "Do you know how to get there?\n"
	.string "Follow ROUTE 27 to ROUTE 26.\p"
	.string "Once there, go straight north!$"

NewBarkTown_Lab_Text_ElmGiveTicket1::
	.string "ELM: {PLAYER}! I have something\n"
	.string "for your travels.\p"
	.string "It's an S.S.TICKET for the ship\n"
	.string "at OLIVINE CITY.$"

NewBarkTown_Lab_Text_ElmGiveTicket2:
	.string "The ship departs from OLIVINE\n"
	.string "CITY.\p"
	.string "But you knew that already,\n"
	.string "{PLAYER}.\p"
	.string "After all, you've traveled all\n"
	.string "over with your POKéMON.\p"
	.string "Give my regards to PROF.OAK in\n"
	.string "KANTO!$"

NewBarkTown_Lab_Text_LabMonEgg:
	.string "It's the POKéMON EGG being\n"
	.string "studied by PROF.ELM.$"

NewBarkTown_Lab_Text_AideGivePotion:
	.string "{PLAYER}, I want you to have\n"
	.string "this for your errand.$"

NewBarkTown_Lab_Text_AideAlwaysBusy:
	.string "There are only three of us, so\n"
	.string "we're always busy.$"

NewBarkTown_Lab_Text_AideSave:
	.string "Traveling far from KANTO?\n"
	.string "Remember to save your progress.$"

NewBarkTown_Lab_Text_AideTheftTestimony:
	.string "There was a loud noise\n"
	.string "outside…\p"
	.string "When we went to look,\n"
	.string "someone stole a POKéMON.\p"
	.string "It's unbelievable that anyone\n"
	.string "would do that!\p"
	.string "…sigh… That stolen POKéMON.\p"
	.string "I wonder how it's doing.\p"
	.string "They say a POKéMON raised by a\n"
	.string "bad person turns bad itself.$"

NewBarkTown_Lab_Text_AideGiveBalls:
	.string "For your JOHTO fieldwork,\n"
	.string "{PLAYER}. Take these POKé BALLS!$"

NewBarkTown_Lab_Text_AideExplainBalls:
	.string "There are POKéMON here that\n"
	.string "you won't find back in KANTO.\p"
	.string "I hope these help you add more\n"
	.string "entries to your POKéDEX!$"

NewBarkTown_Lab_Text_Officer1:
	.string "PROF.ELM told me you came\n"
	.string "from KANTO.\p"
	.string "A red-haired boy stole one\n"
	.string "of his lab's POKéMON.\p"
	.string "You battled that boy near\n"
	.string "CHERRYGROVE?\p"
	.string "Did you find out his name?$"

NewBarkTown_Lab_Text_Officer2_1:
	.string "OK! So {RIVAL} was his name?$"

NewBarkTown_Lab_Text_Officer2:
	.string "Thanks for helping my\n"
	.string "investigation!$"

NewBarkTown_Lab_Text_OfficerNo:
	.string "Surely you got his name?!$"

NewBarkTown_Lab_Text_Elm_CallMe:
	.string "Ah, {PLAYER}!\p"
	.string "How's your POKéDEX coming along?\n"
	.string "I'm busy now, but call me sometime\l"
	.string "and I can check your progress!$"

