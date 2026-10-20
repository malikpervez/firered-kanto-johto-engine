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
	.string "Wha{SE_M_SPIT_UP}ar{SE_M_REVERSAL}yo{SE_M_DIVE}doin{SE_M_SANDSTORM}here?\p"
	.string "M{SE_M_YAWN}aid{SE_M_REVERSAL}i{SE_M_GRASSWHISTLE}stil{SE_M_BATON_PASS}waitin{SE_M_SANDSTORM}fo{SE_M_SAND_TOMB}you\n"
	.string "I{SE_M_ATTRACT}VIOLE{SE_M_SWIFT}CITY!$"

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
	.string "Probabl{SE_M_YAWN}shouldn'{SE_M_SPIT_UP}touch!$"

NewBarkTown_Lab_Text_ElmIntro::
	.string "ELM{SE_M_HEAT_WAVE}Yo{SE_M_DIVE}mus{SE_M_SPIT_UP}b{SE_M_REVERSAL}{PLAYER}!\p"
	.string "PROF.OA{SE_M_SNORE}tol{SE_M_WATERFALL}m{SE_M_REVERSAL}abou{SE_M_SPIT_UP}your\n"
	.string "victor{SE_M_YAWN}a{SE_M_SPIT_UP}th{SE_M_REVERSAL}KANT{SE_M_SOLAR_BEAM}LEAGUE.\p"
	.string "Welcom{SE_M_REVERSAL}t{SE_M_ATTRACT2}JOHTO{SE_M_DRAGON_RAGE}You{SE_M_SAND_TOMB}experience\n"
	.string "coul{SE_M_WATERFALL}hel{SE_M_MORNING_SUN}wit{SE_M_TRI_ATTACK}m{SE_M_YAWN}research.\p"
	.string "Ther{SE_M_REVERSAL}i{SE_M_GRASSWHISTLE}somethin{SE_M_SANDSTORM}I'{SE_M_WATERFALL}lik{SE_M_REVERSAL}your\n"
	.string "hel{SE_M_MORNING_SUN}investigating{SE_M_PERISH_SONG}Wil{SE_M_BATON_PASS}yo{SE_M_DIVE}help?$"

NewBarkTown_Lab_Text_ElmAccepted:
	.string "Thanks{SE_M_SUPERSONIC}{PLAYER}!\n"
	.string "You'r{SE_M_REVERSAL}{SE_M_CHARGE}grea{SE_M_SPIT_UP}help!$"

NewBarkTown_Lab_Text_ElmRefused:
	.string "But{SE_M_DIZZY_PUNCH}Please{SE_M_SUPERSONIC}{SE_M_HEAL_BELL}nee{SE_M_WATERFALL}your\n"
	.string "help!$"

NewBarkTown_Lab_Text_ElmResearchAmbitions:
	.string "Whe{SE_M_ATTRACT}{SE_M_HEAL_BELL}announc{SE_M_REVERSAL}m{SE_M_YAWN}findings,\n"
	.string "I'{SE_M_MILK_DRINK}sur{SE_M_REVERSAL}we'l{SE_M_BATON_PASS}delv{SE_M_REVERSAL}deeper\p"
	.string "int{SE_M_ATTRACT2}th{SE_M_REVERSAL}man{SE_M_YAWN}mysterie{SE_M_GRASSWHISTLE}of\n"
	.string "POKéMON.\p"
	.string "Yo{SE_M_DIVE}ca{SE_M_ATTRACT}coun{SE_M_SPIT_UP}o{SE_M_ATTRACT}it!$"

NewBarkTown_Lab_Text_ElmGotAnEmail:
	.string "Oh{SE_M_SUPERSONIC}hey{SE_M_DRAGON_RAGE}{SE_M_HEAL_BELL}go{SE_M_SPIT_UP}a{SE_M_ATTRACT}e-mail!\p"
	.string "{SE_M_DIZZY_PUNCH}{SE_M_DIZZY_PUNCH}{SE_M_DIZZY_PUNCH}{SE_M_DIZZY_PUNCH}{SE_M_DIZZY_PUNCH}{SE_M_DIZZY_PUNCH}{SE_M_DIZZY_PUNCH}…\n"
	.string "Hm{SE_M_DIZZY_PUNCH}Uh-huh…\p"
	.string "Okay…$"

NewBarkTown_Lab_Text_ElmMissionFromMrPokemon:
	.string "Hey{SE_M_SUPERSONIC}listen.\p"
	.string "{SE_M_HEAL_BELL}hav{SE_M_REVERSAL}a{SE_M_ATTRACT}acquaintanc{SE_M_REVERSAL}called\n"
	.string "MR{SE_M_PERISH_SONG}POKéMON.\p"
	.string "H{SE_M_REVERSAL}keep{SE_M_GRASSWHISTLE}findin{SE_M_SANDSTORM}weir{SE_M_WATERFALL}thing{SE_M_GRASSWHISTLE}and\n"
	.string "ravin{SE_M_SANDSTORM}abou{SE_M_SPIT_UP}hi{SE_M_GRASSWHISTLE}discoveries.\p"
	.string "Anyway{SE_M_SUPERSONIC}{SE_M_HEAL_BELL}jus{SE_M_SPIT_UP}go{SE_M_SPIT_UP}a{SE_M_ATTRACT}e-mail\n"
	.string "fro{SE_M_MILK_DRINK}hi{SE_M_MILK_DRINK}sayin{SE_M_SANDSTORM}tha{SE_M_SPIT_UP}this\l"
	.string "tim{SE_M_REVERSAL}it'{SE_M_GRASSWHISTLE}real.\p"
	.string "I{SE_M_SPIT_UP}i{SE_M_GRASSWHISTLE}intriguing{SE_M_SUPERSONIC}bu{SE_M_SPIT_UP}we're\n"
	.string "bus{SE_M_YAWN}wit{SE_M_TRI_ATTACK}ou{SE_M_SAND_TOMB}POKéMO{SE_M_PSYBEAM2}research...\p"
	.string "Wait!\n"
	.string "{SE_M_HEAL_BELL}know!\p"
	.string "{PLAYER}{SE_M_SUPERSONIC}ca{SE_M_ATTRACT}yo{SE_M_DIVE}g{SE_M_ATTRACT2}i{SE_M_ATTRACT}our\n"
	.string "place?$"

NewBarkTown_Lab_Text_ElmChooseAPokemon::
	.string "You{SE_M_SAND_TOMB}ow{SE_M_ATTRACT}POKéMO{SE_M_PSYBEAM2}hav{SE_M_REVERSAL}brough{SE_M_SPIT_UP}you\n"
	.string "al{SE_M_BATON_PASS}th{SE_M_REVERSAL}wa{SE_M_YAWN}fro{SE_M_MILK_DRINK}KANTO.\p"
	.string "Pleas{SE_M_REVERSAL}tak{SE_M_REVERSAL}the{SE_M_MILK_DRINK}wit{SE_M_TRI_ATTACK}yo{SE_M_DIVE}o{SE_M_ATTRACT}this\n"
	.string "errand{SE_M_PERISH_SONG}{SE_M_HEAL_BELL}kno{SE_M_TWISTER}{SE_M_HEAL_BELL}ca{SE_M_ATTRACT}trus{SE_M_SPIT_UP}you!\p"
	.string "{SE_M_HEAL_BELL}hav{SE_M_REVERSAL}arrange{SE_M_WATERFALL}{SE_M_CHARGE}POKéGEA{SE_M_MINIMIZE}s{SE_M_ATTRACT2}we\n"
	.string "ca{SE_M_ATTRACT}kee{SE_M_MORNING_SUN}i{SE_M_ATTRACT}touc{SE_M_TRI_ATTACK}alon{SE_M_SANDSTORM}th{SE_M_REVERSAL}way.$"

NewBarkTown_Lab_Text_ElmWhereGoing:
	.string "ELM{SE_M_HEAT_WAVE}Wait{SE_M_DRAGON_RAGE}Wher{SE_M_REVERSAL}ar{SE_M_REVERSAL}you\n"
	.string "going?$"

NewBarkTown_Lab_Text_ElmDirections1:
	.string "MR{SE_M_PERISH_SONG}POKéMO{SE_M_PSYBEAM2}live{SE_M_GRASSWHISTLE}{SE_M_CHARGE}littl{SE_M_REVERSAL}bit\n"
	.string "beyon{SE_M_WATERFALL}CHERRYGROVE{SE_M_SUPERSONIC}th{SE_M_REVERSAL}next\l"
	.string "cit{SE_M_YAWN}over.\p"
	.string "It'{SE_M_GRASSWHISTLE}almos{SE_M_SPIT_UP}{SE_M_CHARGE}direc{SE_M_SPIT_UP}route\n"
	.string "there{SE_M_SUPERSONIC}s{SE_M_ATTRACT2}yo{SE_M_DIVE}can'{SE_M_SPIT_UP}mis{SE_M_GRASSWHISTLE}it.\p"
	.string "Bu{SE_M_SPIT_UP}jus{SE_M_SPIT_UP}i{SE_M_ATTRACT}case{SE_M_SUPERSONIC}yo{SE_M_DIVE}hav{SE_M_REVERSAL}my\n"
	.string "phon{SE_M_REVERSAL}number{SE_M_PERISH_SONG}Cal{SE_M_BATON_PASS}m{SE_M_REVERSAL}if\l"
	.string "anythin{SE_M_SANDSTORM}come{SE_M_GRASSWHISTLE}up!$"

NewBarkTown_Lab_Text_ElmDirections1_Register:
	.string "MR{SE_M_PERISH_SONG}POKéMO{SE_M_PSYBEAM2}live{SE_M_GRASSWHISTLE}{SE_M_CHARGE}littl{SE_M_REVERSAL}bit\n"
	.string "beyon{SE_M_WATERFALL}CHERRYGROVE{SE_M_SUPERSONIC}th{SE_M_REVERSAL}next\l"
	.string "cit{SE_M_YAWN}over.\p"
	.string "It'{SE_M_GRASSWHISTLE}almos{SE_M_SPIT_UP}{SE_M_CHARGE}direc{SE_M_SPIT_UP}route\n"
	.string "there{SE_M_SUPERSONIC}s{SE_M_ATTRACT2}yo{SE_M_DIVE}can'{SE_M_SPIT_UP}mis{SE_M_GRASSWHISTLE}it.\p"
	.string "Bu{SE_M_SPIT_UP}jus{SE_M_SPIT_UP}i{SE_M_ATTRACT}case{SE_M_SUPERSONIC}here'{SE_M_GRASSWHISTLE}my\n"
	.string "phon{SE_M_REVERSAL}number{SE_M_PERISH_SONG}Cal{SE_M_BATON_PASS}m{SE_M_REVERSAL}if\l"
	.string "anythin{SE_M_SANDSTORM}come{SE_M_GRASSWHISTLE}up!$"

NewBarkTown_Lab_Text_RegisteredElm:
	.string "Registere{SE_M_WATERFALL}PROF.ELM\n"
	.string "i{SE_M_ATTRACT}th{SE_M_REVERSAL}POKéGEAR.$"

NewBarkTown_Lab_Text_ElmLetYourMonBattle:
	.string "JOHTO'{SE_M_GRASSWHISTLE}wil{SE_M_WATERFALL}POKéMO{SE_M_PSYBEAM2}ma{SE_M_YAWN}be\n"
	.string "differen{SE_M_SPIT_UP}fro{SE_M_MILK_DRINK}thos{SE_M_REVERSAL}i{SE_M_ATTRACT}KANTO.$"

NewBarkTown_Lab_Text_ElmDirections2::
	.string "You{SE_M_SAND_TOMB}tea{SE_M_MILK_DRINK}i{SE_M_GRASSWHISTLE}welcom{SE_M_REVERSAL}t{SE_M_ATTRACT2}us{SE_M_REVERSAL}the\n"
	.string "healin{SE_M_SANDSTORM}machin{SE_M_REVERSAL}t{SE_M_ATTRACT2}m{SE_M_YAWN}right.\p"
	.string "Ther{SE_M_REVERSAL}ar{SE_M_REVERSAL}POKéMO{SE_M_PSYBEAM2}CENTER{SE_M_SKETCH}i{SE_M_ATTRACT}the\n"
	.string "town{SE_M_GRASSWHISTLE}alon{SE_M_SANDSTORM}th{SE_M_REVERSAL}way{SE_M_SUPERSONIC}too.\p"
	.string "I'{SE_M_MILK_DRINK}countin{SE_M_SANDSTORM}o{SE_M_ATTRACT}you!$"

NewBarkTown_Lab_Text_GotElmsNumber:
	.string "{PLAYER} go{SE_M_SPIT_UP}ELM'{SE_M_GRASSWHISTLE}phone\n"
	.string "number.$"

NewBarkTown_Lab_Text_ElmDescribesMrPokemon:
	.string "MR{SE_M_PERISH_SONG}POKéMO{SE_M_PSYBEAM2}goe{SE_M_GRASSWHISTLE}everywher{SE_M_REVERSAL}and\n"
	.string "find{SE_M_GRASSWHISTLE}rarities.\p"
	.string "To{SE_M_ATTRACT2}ba{SE_M_WATERFALL}they'r{SE_M_REVERSAL}jus{SE_M_SPIT_UP}rar{SE_M_REVERSAL}and\n"
	.string "no{SE_M_SPIT_UP}ver{SE_M_YAWN}useful…$"

NewBarkTown_Lab_Text_ElmPokeBall:
	.string "I{SE_M_SPIT_UP}contain{SE_M_GRASSWHISTLE}{SE_M_CHARGE}POKéMO{SE_M_PSYBEAM2}caught\n"
	.string "b{SE_M_YAWN}PROF.ELM.$"

NewBarkTown_Lab_Text_ElmAfterTheft1:
	.string "ELM{SE_M_HEAT_WAVE}{PLAYER}{SE_M_SUPERSONIC}thi{SE_M_GRASSWHISTLE}i{SE_M_GRASSWHISTLE}terrible…\p"
	.string "Oh{SE_M_SUPERSONIC}yes{SE_M_SUPERSONIC}wha{SE_M_SPIT_UP}wa{SE_M_GRASSWHISTLE}MR{SE_M_PERISH_SONG}POKéMON's\n"
	.string "bi{SE_M_SANDSTORM}discovery?$"

NewBarkTown_Lab_Text_ElmAfterTheft2:
	.string "{PLAYER} hande{SE_M_WATERFALL}th{SE_M_REVERSAL}MYSTER{SE_M_MOONLIGHT}EGG\n"
	.string "t{SE_M_ATTRACT2}PROF.ELM.$"

NewBarkTown_Lab_Text_ElmAfterTheft3:
	.string "ELM{SE_M_HEAT_WAVE}This?$"

NewBarkTown_Lab_Text_ElmAfterTheft4::
	.string "{SE_M_BONEMERANG}POKéMO{SE_M_PSYBEAM2}EGG{SE_M_DRAGON_RAGE}Thi{SE_M_GRASSWHISTLE}wil{SE_M_BATON_PASS}help\n"
	.string "wit{SE_M_TRI_ATTACK}m{SE_M_YAWN}research.\p"
	.string "Yo{SE_M_DIVE}me{SE_M_SPIT_UP}PROF.OA{SE_M_SNORE}a{SE_M_SPIT_UP}MR.POKéMON's?\n"
	.string "I'{SE_M_MILK_DRINK}gla{SE_M_WATERFALL}h{SE_M_REVERSAL}coul{SE_M_WATERFALL}se{SE_M_REVERSAL}yo{SE_M_DIVE}again.\p"
	.string "H{SE_M_REVERSAL}wa{SE_M_GRASSWHISTLE}righ{SE_M_SPIT_UP}t{SE_M_ATTRACT2}recommen{SE_M_WATERFALL}you.\n"
	.string "Than{SE_M_ENCORE2}yo{SE_M_DIVE}fo{SE_M_SAND_TOMB}bringin{SE_M_SANDSTORM}thi{SE_M_GRASSWHISTLE}back.\p"
	.string "I{SE_M_ACID_ARMOR}you'{SE_M_WATERFALL}lik{SE_M_REVERSAL}anothe{SE_M_SAND_TOMB}challenge,\n"
	.string "JOHT{SE_M_SOLAR_BEAM}ha{SE_M_GRASSWHISTLE}it{SE_M_GRASSWHISTLE}ow{SE_M_ATTRACT}POKéMO{SE_M_PSYBEAM2}GYMS.\p"
	.string "Th{SE_M_REVERSAL}closes{SE_M_SPIT_UP}i{SE_M_GRASSWHISTLE}i{SE_M_ATTRACT}VIOLE{SE_M_SWIFT}CITY.\p"
	.string "Befor{SE_M_REVERSAL}yo{SE_M_DIVE}leave{SE_M_SUPERSONIC}visi{SE_M_SPIT_UP}th{SE_M_REVERSAL}woman\n"
	.string "i{SE_M_ATTRACT}th{SE_M_REVERSAL}gues{SE_M_SPIT_UP}house{SE_M_PERISH_SONG}Sh{SE_M_REVERSAL}ca{SE_M_ATTRACT}help\l"
	.string "yo{SE_M_DIVE}kee{SE_M_MORNING_SUN}i{SE_M_ATTRACT}touc{SE_M_TRI_ATTACK}whil{SE_M_REVERSAL}traveling.$"

NewBarkTown_Lab_Text_ElmStudyingEgg:
	.string "ELM{SE_M_HEAT_WAVE}Don'{SE_M_SPIT_UP}giv{SE_M_REVERSAL}up!\n"
	.string "I'l{SE_M_BATON_PASS}cal{SE_M_BATON_PASS}i{SE_M_ACID_ARMOR}{SE_M_HEAL_BELL}lear{SE_M_ATTRACT}anything\l"
	.string "abou{SE_M_SPIT_UP}tha{SE_M_SPIT_UP}EGG!$"

NewBarkTown_Lab_Text_ElmAideHasEgg:
	.string "ELM{SE_M_HEAT_WAVE}{PLAYER}{SE_M_SING}Didn'{SE_M_SPIT_UP}yo{SE_M_DIVE}meet\n"
	.string "m{SE_M_YAWN}assistant?\p"
	.string "H{SE_M_REVERSAL}shoul{SE_M_WATERFALL}hav{SE_M_REVERSAL}me{SE_M_SPIT_UP}yo{SE_M_DIVE}with\n"
	.string "th{SE_M_REVERSAL}EG{SE_M_SWAGGER}a{SE_M_SPIT_UP}VIOLE{SE_M_SWIFT}CITY's\p"
	.string "POKéMO{SE_M_PSYBEAM2}CENTER.\p"
	.string "Yo{SE_M_DIVE}mus{SE_M_SPIT_UP}hav{SE_M_REVERSAL}jus{SE_M_SPIT_UP}misse{SE_M_WATERFALL}him.\n"
	.string "Tr{SE_M_YAWN}t{SE_M_ATTRACT2}catc{SE_M_TRI_ATTACK}hi{SE_M_MILK_DRINK}there.$"

NewBarkTown_Lab_Text_ElmWaitingEggHatch:
	.string "ELM{SE_M_HEAT_WAVE}Hey{SE_M_SUPERSONIC}ha{SE_M_GRASSWHISTLE}tha{SE_M_SPIT_UP}EG{SE_M_SWAGGER}changed\n"
	.string "any?$"

NewBarkTown_Lab_Text_ElmThoughtEggHatched:
	.string "{PLAYER}{SE_M_SING}{SE_M_HEAL_BELL}though{SE_M_SPIT_UP}th{SE_M_REVERSAL}EGG\n"
	.string "hatched.\p"
	.string "Wher{SE_M_REVERSAL}i{SE_M_GRASSWHISTLE}th{SE_M_REVERSAL}POKéMON?$"

NewBarkTown_Lab_Text_ShowTogepi1:
	.string "ELM{SE_M_HEAT_WAVE}{PLAYER}{SE_M_SUPERSONIC}yo{SE_M_DIVE}loo{SE_M_ENCORE2}great!$"

NewBarkTown_Lab_Text_ShowTogepi2:
	.string "What{SE_M_SING}Tha{SE_M_SPIT_UP}POKéMON!?!$"

NewBarkTown_Lab_Text_ShowTogepi3:
	.string "Th{SE_M_REVERSAL}EG{SE_M_SWAGGER}hatche{SE_M_WATERFALL}int{SE_M_ATTRACT2}TOGEPI!\p"
	.string "Watchin{SE_M_SANDSTORM}i{SE_M_SPIT_UP}gro{SE_M_TWISTER}wil{SE_M_BATON_PASS}hel{SE_M_MORNING_SUN}my\n"
	.string "researc{SE_M_TRI_ATTACK}int{SE_M_ATTRACT2}POKéMO{SE_M_PSYBEAM2}EGGS.\p"
	.string "There'{SE_M_GRASSWHISTLE}stil{SE_M_BATON_PASS}s{SE_M_ATTRACT2}muc{SE_M_TRI_ATTACK}t{SE_M_ATTRACT2}learn\n"
	.string "abou{SE_M_SPIT_UP}thi{SE_M_GRASSWHISTLE}species!$"

NewBarkTown_Lab_Text_ElmGiveEverstone1:
	.string "Thanks{SE_M_SUPERSONIC}{PLAYER}{SE_M_DRAGON_RAGE}You'r{SE_M_REVERSAL}helping\n"
	.string "unrave{SE_M_BATON_PASS}POKéMO{SE_M_PSYBEAM2}mysterie{SE_M_GRASSWHISTLE}fo{SE_M_SAND_TOMB}us!\p"
	.string "{SE_M_HEAL_BELL}wan{SE_M_SPIT_UP}yo{SE_M_DIVE}t{SE_M_ATTRACT2}hav{SE_M_REVERSAL}thi{SE_M_GRASSWHISTLE}a{SE_M_GRASSWHISTLE}a\n"
	.string "toke{SE_M_ATTRACT}o{SE_M_ACID_ARMOR}ou{SE_M_SAND_TOMB}appreciation.$"

NewBarkTown_Lab_Text_ElmGiveEverstone2:
	.string "Yo{SE_M_DIVE}ma{SE_M_YAWN}kno{SE_M_TWISTER}thi{SE_M_GRASSWHISTLE}fro{SE_M_MILK_DRINK}KANTO:\n"
	.string "{SE_M_CHARGE}POKéMO{SE_M_PSYBEAM2}holdin{SE_M_SANDSTORM}a{SE_M_ATTRACT}EVERSTONE\l"
	.string "won'{SE_M_SPIT_UP}evolve.\p"
	.string "I{SE_M_SPIT_UP}ca{SE_M_ATTRACT}hel{SE_M_MORNING_SUN}whil{SE_M_REVERSAL}w{SE_M_REVERSAL}stud{SE_M_YAWN}how\n"
	.string "POKéMO{SE_M_PSYBEAM2}grow.$"

NewBarkTown_Lab_Text_ElmCallYou:
	.string "ELM{SE_M_HEAT_WAVE}{PLAYER}{SE_M_SUPERSONIC}I'l{SE_M_BATON_PASS}cal{SE_M_BATON_PASS}yo{SE_M_DIVE}if\n"
	.string "anythin{SE_M_SANDSTORM}come{SE_M_GRASSWHISTLE}up.$"

NewBarkTown_Lab_Text_AideAfterTheft:
	.string "…sigh{SE_M_DIZZY_PUNCH}Tha{SE_M_SPIT_UP}stole{SE_M_ATTRACT}POKéMON.\p"
	.string "{SE_M_HEAL_BELL}wonde{SE_M_SAND_TOMB}ho{SE_M_TWISTER}it'{SE_M_GRASSWHISTLE}doing.\p"
	.string "The{SE_M_YAWN}sa{SE_M_YAWN}{SE_M_CHARGE}POKéMO{SE_M_PSYBEAM2}raise{SE_M_WATERFALL}b{SE_M_YAWN}a\n"
	.string "ba{SE_M_WATERFALL}perso{SE_M_ATTRACT}turn{SE_M_GRASSWHISTLE}ba{SE_M_WATERFALL}itself.$"

NewBarkTown_Lab_Text_ElmGiveMasterBall1:
	.string "ELM{SE_M_HEAT_WAVE}Hi{SE_M_SUPERSONIC}{PLAYER}!\p"
	.string "Thank{SE_M_GRASSWHISTLE}t{SE_M_ATTRACT2}you{SE_M_SUPERSONIC}m{SE_M_YAWN}researc{SE_M_TRI_ATTACK}is\n"
	.string "goin{SE_M_SANDSTORM}great!\p"
	.string "Tak{SE_M_REVERSAL}thi{SE_M_GRASSWHISTLE}a{SE_M_GRASSWHISTLE}{SE_M_CHARGE}toke{SE_M_ATTRACT}o{SE_M_ACID_ARMOR}my\n"
	.string "appreciation.$"

NewBarkTown_Lab_Text_ElmGiveMasterBall2:
	.string "Th{SE_M_REVERSAL}MASTE{SE_M_MINIMIZE}BAL{SE_M_BRICK_BREAK}i{SE_M_GRASSWHISTLE}th{SE_M_REVERSAL}best!\p"
	.string "It'{SE_M_GRASSWHISTLE}th{SE_M_REVERSAL}ultimat{SE_M_REVERSAL}BALL{SE_M_DRAGON_RAGE}It'll\n"
	.string "catc{SE_M_TRI_ATTACK}an{SE_M_YAWN}POKéMO{SE_M_PSYBEAM2}withou{SE_M_SPIT_UP}fail.\p"
	.string "It'{SE_M_GRASSWHISTLE}give{SE_M_ATTRACT}onl{SE_M_YAWN}t{SE_M_ATTRACT2}recognized\n"
	.string "POKéMO{SE_M_PSYBEAM2}researchers.\p"
	.string "{SE_M_HEAL_BELL}thin{SE_M_ENCORE2}yo{SE_M_DIVE}ca{SE_M_ATTRACT}mak{SE_M_REVERSAL}muc{SE_M_TRI_ATTACK}better\n"
	.string "us{SE_M_REVERSAL}o{SE_M_ACID_ARMOR}i{SE_M_SPIT_UP}tha{SE_M_ATTRACT}{SE_M_HEAL_BELL}can{SE_M_SUPERSONIC}{PLAYER}!$"

NewBarkTown_Lab_Text_KimonoGirls:
	.string "B{SE_M_YAWN}th{SE_M_REVERSAL}way...\n"
	.string "{SE_M_BONEMERANG}grou{SE_M_MORNING_SUN}o{SE_M_ACID_ARMOR}beautifu{SE_M_BATON_PASS}KIMONO\l"
	.string "GIRL{SE_M_SKETCH}wer{SE_M_REVERSAL}lookin{SE_M_SANDSTORM}fo{SE_M_SAND_TOMB}you.\p"
	.string "The{SE_M_YAWN}tol{SE_M_WATERFALL}m{SE_M_REVERSAL}the{SE_M_YAWN}are\n"
	.string "waitin{SE_M_SANDSTORM}fo{SE_M_SAND_TOMB}yo{SE_M_DIVE}a{SE_M_SPIT_UP}the\l"
	.string "ECRUTEA{SE_M_SNORE}DANC{SE_M_SWORDS_DANCE}THEATER.\p"
	.string "{SE_M_HEAL_BELL}kno{SE_M_TWISTER}you'v{SE_M_REVERSAL}gon{SE_M_REVERSAL}throug{SE_M_TRI_ATTACK}many\n"
	.string "thing{SE_M_GRASSWHISTLE}sinc{SE_M_REVERSAL}tha{SE_M_SPIT_UP}EG{SE_M_SWAGGER}go{SE_M_SPIT_UP}you\l"
	.string "involve{SE_M_WATERFALL}i{SE_M_ATTRACT}al{SE_M_BATON_PASS}this...\p"
	.string "{SE_M_HEAL_BELL}hop{SE_M_REVERSAL}you'l{SE_M_BATON_PASS}carr{SE_M_YAWN}throug{SE_M_TRI_ATTACK}it.$"

NewBarkTown_Lab_Text_KimonoWaiting:
	.string "PROF.ELM{SE_M_HEAT_WAVE}Th{SE_M_REVERSAL}KIMONO\n"
	.string "GIRL{SE_M_SKETCH}ar{SE_M_REVERSAL}waitin{SE_M_SANDSTORM}fo{SE_M_SAND_TOMB}yo{SE_M_DIVE}at\l"
	.string "th{SE_M_REVERSAL}ECRUTEA{SE_M_SNORE}DANC{SE_M_SWORDS_DANCE}THEATER.$"

NewBarkTown_Lab_Text_League:
	.string "PROF.ELM{SE_M_HEAT_WAVE}Wel{SE_M_BATON_PASS}done{SE_M_SUPERSONIC}{PLAYER}!\p"
	.string "Yo{SE_M_DIVE}cam{SE_M_REVERSAL}her{SE_M_REVERSAL}a{SE_M_GRASSWHISTLE}KANTO's\n"
	.string "CHAMPIO{SE_M_PSYBEAM2}an{SE_M_WATERFALL}helpe{SE_M_WATERFALL}u{SE_M_GRASSWHISTLE}s{SE_M_ATTRACT2}much.\p"
	.string "No{SE_M_TWISTER}JOHTO'{SE_M_GRASSWHISTLE}LEAGU{SE_M_SWORDS_DANCE}i{SE_M_GRASSWHISTLE}waiting.\n"
	.string "Tak{SE_M_REVERSAL}you{SE_M_SAND_TOMB}tea{SE_M_MILK_DRINK}t{SE_M_ATTRACT2}INDIG{SE_M_SOLAR_BEAM}PLATEAU!\p"
	.string "D{SE_M_ATTRACT2}yo{SE_M_DIVE}kno{SE_M_TWISTER}ho{SE_M_TWISTER}t{SE_M_ATTRACT2}ge{SE_M_SPIT_UP}there?\n"
	.string "Follo{SE_M_TWISTER}ROUT{SE_M_SWORDS_DANCE}2{SE_M_MIST}t{SE_M_ATTRACT2}ROUT{SE_M_SWORDS_DANCE}26.\p"
	.string "Onc{SE_M_REVERSAL}there{SE_M_SUPERSONIC}g{SE_M_ATTRACT2}straigh{SE_M_SPIT_UP}north!$"

NewBarkTown_Lab_Text_ElmGiveTicket1::
	.string "ELM{SE_M_HEAT_WAVE}{PLAYER}{SE_M_DRAGON_RAGE}{SE_M_HEAL_BELL}hav{SE_M_REVERSAL}something\n"
	.string "fo{SE_M_SAND_TOMB}you{SE_M_SAND_TOMB}travels.\p"
	.string "It'{SE_M_GRASSWHISTLE}a{SE_M_ATTRACT}S.S.TICKE{SE_M_SWIFT}fo{SE_M_SAND_TOMB}th{SE_M_REVERSAL}ship\n"
	.string "a{SE_M_SPIT_UP}OLIVIN{SE_M_SWORDS_DANCE}CITY.$"

NewBarkTown_Lab_Text_ElmGiveTicket2:
	.string "Th{SE_M_REVERSAL}shi{SE_M_MORNING_SUN}depart{SE_M_GRASSWHISTLE}fro{SE_M_MILK_DRINK}OLIVINE\n"
	.string "CITY.\p"
	.string "Bu{SE_M_SPIT_UP}yo{SE_M_DIVE}kne{SE_M_TWISTER}tha{SE_M_SPIT_UP}already,\n"
	.string "{PLAYER}.\p"
	.string "Afte{SE_M_SAND_TOMB}all{SE_M_SUPERSONIC}you'v{SE_M_REVERSAL}travele{SE_M_WATERFALL}all\n"
	.string "ove{SE_M_SAND_TOMB}wit{SE_M_TRI_ATTACK}you{SE_M_SAND_TOMB}POKéMON.\p"
	.string "Giv{SE_M_REVERSAL}m{SE_M_YAWN}regard{SE_M_GRASSWHISTLE}t{SE_M_ATTRACT2}PROF.OA{SE_M_SNORE}in\n"
	.string "KANTO!$"

NewBarkTown_Lab_Text_LabMonEgg:
	.string "It'{SE_M_GRASSWHISTLE}th{SE_M_REVERSAL}POKéMO{SE_M_PSYBEAM2}EG{SE_M_SWAGGER}being\n"
	.string "studie{SE_M_WATERFALL}b{SE_M_YAWN}PROF.ELM.$"

NewBarkTown_Lab_Text_AideGivePotion:
	.string "{PLAYER}{SE_M_SUPERSONIC}{SE_M_HEAL_BELL}wan{SE_M_SPIT_UP}yo{SE_M_DIVE}t{SE_M_ATTRACT2}have\n"
	.string "thi{SE_M_GRASSWHISTLE}fo{SE_M_SAND_TOMB}you{SE_M_SAND_TOMB}errand.$"

NewBarkTown_Lab_Text_AideAlwaysBusy:
	.string "Ther{SE_M_REVERSAL}ar{SE_M_REVERSAL}onl{SE_M_YAWN}thre{SE_M_REVERSAL}o{SE_M_ACID_ARMOR}us{SE_M_SUPERSONIC}so\n"
	.string "we'r{SE_M_REVERSAL}alway{SE_M_GRASSWHISTLE}busy.$"

NewBarkTown_Lab_Text_AideSave:
	.string "Travelin{SE_M_SANDSTORM}fa{SE_M_SAND_TOMB}fro{SE_M_MILK_DRINK}KANTO?\n"
	.string "Remembe{SE_M_SAND_TOMB}t{SE_M_ATTRACT2}sav{SE_M_REVERSAL}you{SE_M_SAND_TOMB}progress.$"

NewBarkTown_Lab_Text_AideTheftTestimony:
	.string "Ther{SE_M_REVERSAL}wa{SE_M_GRASSWHISTLE}{SE_M_CHARGE}lou{SE_M_WATERFALL}noise\n"
	.string "outside…\p"
	.string "Whe{SE_M_ATTRACT}w{SE_M_REVERSAL}wen{SE_M_SPIT_UP}t{SE_M_ATTRACT2}look,\n"
	.string "someon{SE_M_REVERSAL}stol{SE_M_REVERSAL}{SE_M_CHARGE}POKéMON.\p"
	.string "It'{SE_M_GRASSWHISTLE}unbelievabl{SE_M_REVERSAL}tha{SE_M_SPIT_UP}anyone\n"
	.string "woul{SE_M_WATERFALL}d{SE_M_ATTRACT2}that!\p"
	.string "…sigh{SE_M_DIZZY_PUNCH}Tha{SE_M_SPIT_UP}stole{SE_M_ATTRACT}POKéMON.\p"
	.string "{SE_M_HEAL_BELL}wonde{SE_M_SAND_TOMB}ho{SE_M_TWISTER}it'{SE_M_GRASSWHISTLE}doing.\p"
	.string "The{SE_M_YAWN}sa{SE_M_YAWN}{SE_M_CHARGE}POKéMO{SE_M_PSYBEAM2}raise{SE_M_WATERFALL}b{SE_M_YAWN}a\n"
	.string "ba{SE_M_WATERFALL}perso{SE_M_ATTRACT}turn{SE_M_GRASSWHISTLE}ba{SE_M_WATERFALL}itself.$"

NewBarkTown_Lab_Text_AideGiveBalls:
	.string "Fo{SE_M_SAND_TOMB}you{SE_M_SAND_TOMB}JOHT{SE_M_SOLAR_BEAM}fieldwork,\n"
	.string "{PLAYER}{SE_M_PERISH_SONG}Tak{SE_M_REVERSAL}thes{SE_M_REVERSAL}POK{SE_U}BALLS!$"

NewBarkTown_Lab_Text_AideExplainBalls:
	.string "Ther{SE_M_REVERSAL}ar{SE_M_REVERSAL}POKéMO{SE_M_PSYBEAM2}her{SE_M_REVERSAL}that\n"
	.string "yo{SE_M_DIVE}won'{SE_M_SPIT_UP}fin{SE_M_WATERFALL}bac{SE_M_ENCORE2}i{SE_M_ATTRACT}KANTO.\p"
	.string "{SE_M_HEAL_BELL}hop{SE_M_REVERSAL}thes{SE_M_REVERSAL}hel{SE_M_MORNING_SUN}yo{SE_M_DIVE}ad{SE_M_WATERFALL}more\n"
	.string "entrie{SE_M_GRASSWHISTLE}t{SE_M_ATTRACT2}you{SE_M_SAND_TOMB}POKéDEX!$"

NewBarkTown_Lab_Text_Officer1:
	.string "PROF.EL{SE_M_GIGA_DRAIN}tol{SE_M_WATERFALL}m{SE_M_REVERSAL}yo{SE_M_DIVE}came\n"
	.string "fro{SE_M_MILK_DRINK}KANTO.\p"
	.string "{SE_M_BONEMERANG}red-haire{SE_M_WATERFALL}bo{SE_M_YAWN}stol{SE_M_REVERSAL}one\n"
	.string "o{SE_M_ACID_ARMOR}hi{SE_M_GRASSWHISTLE}lab'{SE_M_GRASSWHISTLE}POKéMON.\p"
	.string "Yo{SE_M_DIVE}battle{SE_M_WATERFALL}tha{SE_M_SPIT_UP}bo{SE_M_YAWN}near\n"
	.string "CHERRYGROVE?\p"
	.string "Di{SE_M_WATERFALL}yo{SE_M_DIVE}fin{SE_M_WATERFALL}ou{SE_M_SPIT_UP}hi{SE_M_GRASSWHISTLE}name?$"

NewBarkTown_Lab_Text_Officer2_1:
	.string "OK{SE_M_DRAGON_RAGE}S{SE_M_ATTRACT2}{RIVAL} wa{SE_M_GRASSWHISTLE}hi{SE_M_GRASSWHISTLE}name?$"

NewBarkTown_Lab_Text_Officer2:
	.string "Thank{SE_M_GRASSWHISTLE}fo{SE_M_SAND_TOMB}helpin{SE_M_SANDSTORM}my\n"
	.string "investigation!$"

NewBarkTown_Lab_Text_OfficerNo:
	.string "Surel{SE_M_YAWN}yo{SE_M_DIVE}go{SE_M_SPIT_UP}hi{SE_M_GRASSWHISTLE}name?!$"

NewBarkTown_Lab_Text_Elm_CallMe:
	.string "Ah{SE_M_SUPERSONIC}{PLAYER}!\p"
	.string "How'{SE_M_GRASSWHISTLE}you{SE_M_SAND_TOMB}POKéDE{SE_M_LOCK_ON}comin{SE_M_SANDSTORM}along?\n"
	.string "I'{SE_M_MILK_DRINK}bus{SE_M_YAWN}now{SE_M_SUPERSONIC}bu{SE_M_SPIT_UP}cal{SE_M_BATON_PASS}m{SE_M_REVERSAL}sometime\l"
	.string "an{SE_M_WATERFALL}{SE_M_HEAL_BELL}ca{SE_M_ATTRACT}chec{SE_M_ENCORE2}you{SE_M_SAND_TOMB}progress!$"

