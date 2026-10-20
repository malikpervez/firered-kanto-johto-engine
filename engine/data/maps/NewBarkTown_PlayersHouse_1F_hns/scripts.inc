@ Johto (data/maps/NewBarkTown_PlayersHouse_1F_hns/scripts.inc), as built into the FireRed game.

NewBarkTown_PlayersHouse_1F_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, NewBarkTown_PlayersHouse_1F_OnTransition
	.byte 0

NewBarkTown_PlayersHouse_1F_OnTransition::
	call_if_eq JOHTO_VAR_NEWBARK_TOWN_STATE, 1, NewBarkTown_PlayersHouse_1F_SetMomStandingAtTable
	call_if_eq JOHTO_VAR_NEWBARK_TOWN_STATE, 2, NewBarkTown_PlayersHouse_1F_SetMomStandingAtTable
	call_if_eq JOHTO_VAR_NEWBARK_TOWN_STATE, 3, NewBarkTown_PlayersHouse_1F_SetMomStandingAtTable
	end

NewBarkTown_PlayersHouse_1F_SetMomStandingAtTable::
	setobjectxyperm LOCALID_MOM, 8, 4
	setobjectmovementtype LOCALID_MOM, MOVEMENT_TYPE_FACE_LEFT


	clearflag JOHTO_FLAG_HIDE_MOMS_FRIEND
	clearflag JOHTO_FLAG_MOM_VISITED
	return

NewBarkTown_PlayersHouse_1F_EventScript_Mom::
	lock
	faceplayer
	call_if_unset JOHTO_FLAG_RECEIVED_POKENAV, NewBarkTown_PlayersHouse_1F_EventScript_GivePokeGear
	goto_if_set JOHTO_FLAG_MOM_VISITED, NewBarkTown_PlayersHouse_1F_EventScript_Mom_Regular
	goto_if_set JOHTO_FLAG_ADVENTURE_STARTED, NewBarkTown_PlayersHouse_1F_MomEventScript_GoodLuck
	msgbox NewBarkTown_PlayersHouse_1F_Text_MomHurryUpElmIsWaiting, MSGBOX_DEFAULT
	applymovement LOCALID_MOM, NewBarkTown_PlayersHouse_1F_MovementFaceLeft
	waitmovement 0
	release
	end

NewBarkTown_PlayersHouse_1F_EventScript_MomsFriend::
	lock
	faceplayer
	msgbox NewBarkTown_PlayersHouse_1F_Text_MomsFriend, MSGBOX_DEFAULT
	applymovement LOCALID_MOMS_FRIEND, NewBarkTown_PlayersHouse_1F_MovementFaceRight
	waitmovement 0
	release
	end

NewBarkTown_PlayersHouse_1F_MomEventScript_GoodLuck::
	playbgm ((558 + 1) + 0x39), FALSE
	msgbox NewBarkTown_PlayersHouse_1F_Text_MomLeaving, MSGBOX_DEFAULT
	setflag JOHTO_FLAG_MOM_VISITED
	clearflag JOHTO_FLAG_HIDE_ROUTE_30_NPCS
	setvar JOHTO_VAR_NEWBARK_TOWN_STATE, 5
	fadedefaultbgm
	release
	end

NewBarkTown_PlayersHouse_1F_EventScript_Mom_Regular::
	playbgm ((558 + 1) + 0x39), FALSE
	specialvar VAR_RESULT, IsPokecenterChallengeActivated
	goto_if_eq VAR_RESULT, TRUE, NewBarkTown_PlayersHouse_1F_EventScript_Mom_PokecenterChallenge
	msgbox NewBarkTown_PlayersHouse_1F_Text_GuestRest, MSGBOX_DEFAULT
	closemessage
	call J_Common_EventScript_OutOfCenterPartyHeal
	incrementgamestat GAME_STAT_RESTED_AT_HOME
	call NewBarkTown_PlayersHouse_1F_EventScript_MomSavingsMenu
	fadedefaultbgm
	release
	end

NewBarkTown_PlayersHouse_1F_EventScript_Mom_PokecenterChallenge::
	msgbox NewBarkTown_PlayersHouse_1F_Text_GuestRestChallenge, MSGBOX_DEFAULT
	call NewBarkTown_PlayersHouse_1F_EventScript_MomSavingsMenu
	fadedefaultbgm
	release
	end

NewBarkTown_PlayersHouse_1F_EventScript_MomSavingsMenu::
	special Special_MomEnsureInitialized
	msgbox NewBarkTown_PlayersHouse_1F_Text_MomAnythingElse, MSGBOX_DEFAULT
	multichoice 0, 0, MULTI_MOM_MENU, FALSE
	switch VAR_RESULT
	case 0, NewBarkTown_PlayersHouse_1F_EventScript_CheckSavings
	case 1, NewBarkTown_PlayersHouse_1F_EventScript_Deposit
	case 2, NewBarkTown_PlayersHouse_1F_EventScript_Withdraw
	case 3, NewBarkTown_PlayersHouse_1F_EventScript_ToggleSaving
	case 4, NewBarkTown_PlayersHouse_1F_EventScript_ExitSavings
	case MULTI_B_PRESSED, NewBarkTown_PlayersHouse_1F_EventScript_ExitSavings
	end

NewBarkTown_PlayersHouse_1F_EventScript_CheckSavings::
	special Special_MomGetBalance
	msgbox NewBarkTown_PlayersHouse_1F_Text_CurrentSavings, MSGBOX_DEFAULT
	goto NewBarkTown_PlayersHouse_1F_EventScript_MomSavingsMenu
	end

NewBarkTown_PlayersHouse_1F_EventScript_Deposit::
	checkmoney 1
	compare VAR_RESULT, FALSE
	goto_if_eq NewBarkTown_PlayersHouse_1F_EventScript_DepositFailed
	closemessage
	special Special_MomOpenDepositInput
	waitstate
	compare VAR_0x8000, 0
	goto_if_eq NewBarkTown_PlayersHouse_1F_EventScript_MomSavingsMenu
	msgbox NewBarkTown_PlayersHouse_1F_Text_DepositSuccess, MSGBOX_DEFAULT
	goto NewBarkTown_PlayersHouse_1F_EventScript_MomSavingsMenu
	end

NewBarkTown_PlayersHouse_1F_EventScript_DepositFailed::
	msgbox NewBarkTown_PlayersHouse_1F_Text_NoMoneyToDeposit, MSGBOX_DEFAULT
	goto NewBarkTown_PlayersHouse_1F_EventScript_MomSavingsMenu
	end

NewBarkTown_PlayersHouse_1F_EventScript_Withdraw::
	special Special_MomGetBalance
	compare VAR_RESULT, 0
	goto_if_eq NewBarkTown_PlayersHouse_1F_EventScript_WithdrawFailed
	closemessage
	special Special_MomOpenWithdrawInput
	waitstate
	compare VAR_0x8000, 0
	goto_if_eq NewBarkTown_PlayersHouse_1F_EventScript_MomSavingsMenu
	msgbox NewBarkTown_PlayersHouse_1F_Text_WithdrawSuccess, MSGBOX_DEFAULT
	goto NewBarkTown_PlayersHouse_1F_EventScript_MomSavingsMenu
	end

NewBarkTown_PlayersHouse_1F_EventScript_WithdrawFailed::
	msgbox NewBarkTown_PlayersHouse_1F_Text_NoMoneyToWithdraw, MSGBOX_DEFAULT
	goto NewBarkTown_PlayersHouse_1F_EventScript_MomSavingsMenu
	end

NewBarkTown_PlayersHouse_1F_EventScript_ToggleSaving::
	special Special_MomIsSavingEnabled
	compare VAR_RESULT, TRUE
	goto_if_eq NewBarkTown_PlayersHouse_1F_EventScript_DisableSaving
	msgbox NewBarkTown_PlayersHouse_1F_Text_EnableSaving, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq NewBarkTown_PlayersHouse_1F_EventScript_ConfirmEnable
	goto NewBarkTown_PlayersHouse_1F_EventScript_MomSavingsMenu
	end

NewBarkTown_PlayersHouse_1F_EventScript_ConfirmEnable::
	special Special_MomEnableSaving
	msgbox NewBarkTown_PlayersHouse_1F_Text_SavingEnabled, MSGBOX_DEFAULT
	goto NewBarkTown_PlayersHouse_1F_EventScript_MomSavingsMenu
	end

NewBarkTown_PlayersHouse_1F_EventScript_DisableSaving::
	msgbox NewBarkTown_PlayersHouse_1F_Text_DisableSaving, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq NewBarkTown_PlayersHouse_1F_EventScript_ConfirmDisable
	goto NewBarkTown_PlayersHouse_1F_EventScript_MomSavingsMenu
	end

NewBarkTown_PlayersHouse_1F_EventScript_ConfirmDisable::
	special Special_MomDisableSaving
	msgbox NewBarkTown_PlayersHouse_1F_Text_SavingDisabled, MSGBOX_DEFAULT
	goto NewBarkTown_PlayersHouse_1F_EventScript_MomSavingsMenu
	end

NewBarkTown_PlayersHouse_1F_EventScript_ExitSavings::
	msgbox NewBarkTown_PlayersHouse_1F_Text_Goodbye, MSGBOX_DEFAULT
	return

NewBarkTown_PlayersHouse_1F_Text_MomAnythingElse:
	.string "I{SE_M_GRASSWHISTLE}ther{SE_M_REVERSAL}anythin{SE_M_SANDSTORM}els{SE_M_REVERSAL}{SE_M_HEAL_BELL}can\n"
	.string "hel{SE_M_MORNING_SUN}yo{SE_M_DIVE}with{SE_M_SUPERSONIC}sweetie?$"

NewBarkTown_PlayersHouse_1F_Text_CurrentSavings:
	.string "I'{SE_M_MILK_DRINK}holdin{SE_M_SANDSTORM}{STR_VAR_2}\n"
	.string "fo{SE_M_SAND_TOMB}yo{SE_M_DIVE}righ{SE_M_SPIT_UP}now.$"

NewBarkTown_PlayersHouse_1F_Text_EnableSaving:
	.string "D{SE_M_ATTRACT2}yo{SE_M_DIVE}wan{SE_M_SPIT_UP}m{SE_M_REVERSAL}t{SE_M_ATTRACT2}sav{SE_M_REVERSAL}som{SE_M_REVERSAL}o{SE_M_ACID_ARMOR}the\n"
	.string "mone{SE_M_YAWN}yo{SE_M_DIVE}earn?$"

NewBarkTown_PlayersHouse_1F_Text_SavingEnabled:
	.string "Okay{SE_M_DRAGON_RAGE}I'l{SE_M_BATON_PASS}sav{SE_M_REVERSAL}25{SE_EXP_MAX}of\n"
	.string "th{SE_M_REVERSAL}mone{SE_M_YAWN}yo{SE_M_DIVE}ear{SE_M_ATTRACT}fro{SE_M_MILK_DRINK}battles.$"

NewBarkTown_PlayersHouse_1F_Text_DisableSaving:
	.string "Woul{SE_M_WATERFALL}yo{SE_M_DIVE}lik{SE_M_REVERSAL}m{SE_M_REVERSAL}t{SE_M_ATTRACT2}stop\n"
	.string "savin{SE_M_SANDSTORM}fo{SE_M_SAND_TOMB}you?$"

NewBarkTown_PlayersHouse_1F_Text_SavingDisabled:
	.string "Okay{SE_M_SUPERSONIC}I'l{SE_M_BATON_PASS}sto{SE_M_MORNING_SUN}savin{SE_M_SANDSTORM}fo{SE_M_SAND_TOMB}now.$"

NewBarkTown_PlayersHouse_1F_Text_Goodbye:
	.string "Tak{SE_M_REVERSAL}care{SE_M_SUPERSONIC}sweetie!$"

NewBarkTown_PlayersHouse_1F_Text_DepositSuccess:
	.string "HOST{SE_M_HEAT_WAVE}Sound{SE_M_GRASSWHISTLE}good{SE_M_DRAGON_RAGE}I'l{SE_M_BATON_PASS}pu{SE_M_SPIT_UP}tha{SE_M_SPIT_UP}in\n"
	.string "saving{SE_M_GRASSWHISTLE}fo{SE_M_SAND_TOMB}you.$"

NewBarkTown_PlayersHouse_1F_Text_WithdrawSuccess:
	.string "HOST{SE_M_HEAT_WAVE}Her{SE_M_REVERSAL}yo{SE_M_DIVE}go!$"

NewBarkTown_PlayersHouse_1F_Text_NoMoneyToDeposit:
	.string "HOST{SE_M_HEAT_WAVE}Yo{SE_M_DIVE}don'{SE_M_SPIT_UP}hav{SE_M_REVERSAL}an{SE_M_YAWN}mone{SE_M_YAWN}to\n"
	.string "deposi{SE_M_SPIT_UP}righ{SE_M_SPIT_UP}now{SE_M_SUPERSONIC}sweetie.$"

NewBarkTown_PlayersHouse_1F_Text_NoMoneyToWithdraw:
	.string "HOST{SE_M_HEAT_WAVE}{SE_M_HEAL_BELL}haven'{SE_M_SPIT_UP}save{SE_M_WATERFALL}an{SE_M_YAWN}money\n"
	.string "fo{SE_M_SAND_TOMB}yo{SE_M_DIVE}yet{SE_M_SUPERSONIC}honey.$"

NewBarkTown_PlayersHouse_1F_EventScript_MomsIntroTrigger1::
	lock
	applymovement OBJ_EVENT_ID_PLAYER, NewBarkTown_PlayersHouse_1F_PlayerIntroMovement1
	waitmovement 0
	goto NewBarkTown_PlayersHouse_1F_EventScript_MomsIntro
	end

NewBarkTown_PlayersHouse_1F_EventScript_MomsIntroTrigger2::
	lock
	applymovement OBJ_EVENT_ID_PLAYER, NewBarkTown_PlayersHouse_1F_PlayerIntroMovement2
	waitmovement 0
	goto NewBarkTown_PlayersHouse_1F_EventScript_MomsIntro
	end

NewBarkTown_PlayersHouse_1F_EventScript_MomsIntro::
	playbgm ((558 + 1) + 0x39), FALSE
	playse SE_PIN
	applymovement LOCALID_MOM, J_Common_Movement_ExclamationMark
	delay 55
	waitmovement LOCALID_MOM
	applymovement LOCALID_MOM, NewBarkTown_PlayersHouse_1F_MomMovement_1
	waitmovement 0
	msgbox NewBarkTown_PlayersHouse_1F_Text_ElmsLookingForYou, MSGBOX_DEFAULT
	call NewBarkTown_PlayersHouse_1F_EventScript_GivePokeGear
	applymovement LOCALID_MOM, NewBarkTown_PlayersHouse_1F_MomMovement_2
	waitmovement 0
	setflag JOHTO_FLAG_HIDE_LAB_POLICEMAN
	setflag JOHTO_FLAG_VISITED_NEWBARK_TOWN



	fadedefaultbgm
	releaseall
	end

NewBarkTown_PlayersHouse_1F_EventScript_GivePokeGear::
	playfanfare MUS_REGISTER_MATCH_CALL
	message NewBarkTown_PlayersHouse_1F_Text_ObtainedPokeGear
	waitfanfare
	setflag JOHTO_FLAG_SYS_POKENAV_GET
	setflag JOHTO_FLAG_HAS_MATCH_CALL
	setflag JOHTO_FLAG_RECEIVED_POKENAV
	setflag JOHTO_FLAG_ADDED_MATCH_CALL_TO_POKENAV
	setflag JOHTO_FLAG_REGISTER_RIVAL_POKENAV
	msgbox NewBarkTown_PlayersHouse_1F_Text_ExplainPokeGear, MSGBOX_DEFAULT
	closemessage
	delay 30
	return

NewBarkTown_PlayersHouse_1F_PlayerIntroMovement1:
	delay_8
	walk_down
	walk_right
	walk_down
	face_left
	delay_8
	step_end

NewBarkTown_PlayersHouse_1F_PlayerIntroMovement2:
	delay_8
	walk_down
	face_left
	delay_8
	step_end

NewBarkTown_PlayersHouse_1F_MomMovement_1:
	face_right
	walk_right
	step_end

NewBarkTown_PlayersHouse_1F_MomMovement_2:
	face_left
	walk_left
	delay_8
	step_end

NewBarkTown_PlayersHouse_1F_MovementFaceRight:
	face_right
	step_end

NewBarkTown_PlayersHouse_1F_MovementFaceLeft:
	face_left
	step_end

NewBarkTown_PlayersHouse_1F_Text_ElmsLookingForYou::
	.string "Welcome{SE_M_SUPERSONIC}{PLAYER}{SE_M_DRAGON_RAGE}PROF.EL{SE_M_GIGA_DRAIN}told\n"
	.string "m{SE_M_REVERSAL}abou{SE_M_SPIT_UP}hi{SE_M_GRASSWHISTLE}gues{SE_M_SPIT_UP}fro{SE_M_MILK_DRINK}KANTO.\p"
	.string "H{SE_M_REVERSAL}i{SE_M_GRASSWHISTLE}lookin{SE_M_SANDSTORM}fo{SE_M_SAND_TOMB}hel{SE_M_MORNING_SUN}wit{SE_M_TRI_ATTACK}his\n"
	.string "POKéMO{SE_M_PSYBEAM2}research.\p"
	.string "Her{SE_M_REVERSAL}i{SE_M_GRASSWHISTLE}{SE_M_CHARGE}POKéGEA{SE_M_MINIMIZE}t{SE_M_ATTRACT2}hel{SE_M_MORNING_SUN}you\n"
	.string "kee{SE_M_MORNING_SUN}i{SE_M_ATTRACT}touc{SE_M_TRI_ATTACK}whil{SE_M_REVERSAL}you'r{SE_M_REVERSAL}here.$"

NewBarkTown_PlayersHouse_1F_Text_ObtainedPokeGear:
	.string "{PLAYER} obtaine{SE_M_WATERFALL}th{SE_M_REVERSAL}POKéGEAR.$"

NewBarkTown_PlayersHouse_1F_Text_ExplainPokeGear::
	.string "Phon{SE_M_REVERSAL}number{SE_M_GRASSWHISTLE}ar{SE_M_REVERSAL}store{SE_M_WATERFALL}i{SE_M_ATTRACT}the\n"
	.string "POKéGEAR'{SE_M_GRASSWHISTLE}memory.\p"
	.string "Choos{SE_M_REVERSAL}{SE_M_CHARGE}nam{SE_M_REVERSAL}whe{SE_M_ATTRACT}yo{SE_M_DIVE}wan{SE_M_SPIT_UP}to\n"
	.string "call{SE_M_PERISH_SONG}Th{SE_M_REVERSAL}gues{SE_M_SPIT_UP}hous{SE_M_REVERSAL}numbe{SE_M_SAND_TOMB}is\l"
	.string "registere{SE_M_WATERFALL}i{SE_M_ACID_ARMOR}yo{SE_M_DIVE}nee{SE_M_WATERFALL}help.$"

NewBarkTown_PlayersHouse_1F_Text_MomHurryUpElmIsWaiting::
	.string "PROF.EL{SE_M_GIGA_DRAIN}i{SE_M_GRASSWHISTLE}waitin{SE_M_SANDSTORM}i{SE_M_ATTRACT}hi{SE_M_GRASSWHISTLE}lab.\p"
	.string "I'{SE_M_MILK_DRINK}gla{SE_M_WATERFALL}{SE_M_CHARGE}traine{SE_M_SAND_TOMB}fro{SE_M_MILK_DRINK}KANTO\n"
	.string "ha{SE_M_GRASSWHISTLE}com{SE_M_REVERSAL}t{SE_M_ATTRACT2}hel{SE_M_MORNING_SUN}him.$"

NewBarkTown_PlayersHouse_1F_Text_MomsFriend::
	.string "Hi{SE_M_SUPERSONIC}{PLAYER}{SE_M_DRAGON_RAGE}You'r{SE_M_REVERSAL}PROF.ELM's\n"
	.string "gues{SE_M_SPIT_UP}fro{SE_M_MILK_DRINK}KANTO{SE_M_SUPERSONIC}aren'{SE_M_SPIT_UP}you?\p"
	.string "M{SE_M_YAWN}daughte{SE_M_SAND_TOMB}hope{SE_M_GRASSWHISTLE}t{SE_M_ATTRACT2}becom{SE_M_REVERSAL}his\n"
	.string "assistant{SE_M_PERISH_SONG}Sh{SE_M_REVERSAL}love{SE_M_GRASSWHISTLE}POKéMON!$"

NewBarkTown_PlayersHouse_1F_Text_MomLeaving::
	.string "You'r{SE_M_REVERSAL}read{SE_M_YAWN}t{SE_M_ATTRACT2}explor{SE_M_REVERSAL}JOHTO?\n"
	.string "You{SE_M_SAND_TOMB}POKéMO{SE_M_PSYBEAM2}loo{SE_M_ENCORE2}eager{SE_M_SUPERSONIC}too!\p"
	.string "{SE_M_HEAL_BELL}ca{SE_M_ATTRACT}hel{SE_M_MORNING_SUN}loo{SE_M_ENCORE2}afte{SE_M_SAND_TOMB}som{SE_M_REVERSAL}o{SE_M_ACID_ARMOR}your\n"
	.string "battl{SE_M_REVERSAL}winning{SE_M_GRASSWHISTLE}i{SE_M_ACID_ARMOR}you'{SE_M_WATERFALL}like.\p"
	.string "I{SE_M_SPIT_UP}i{SE_M_GRASSWHISTLE}you{SE_M_SAND_TOMB}choice{SE_M_PERISH_SONG}Com{SE_M_REVERSAL}bac{SE_M_ENCORE2}any\n"
	.string "tim{SE_M_REVERSAL}t{SE_M_ATTRACT2}manag{SE_M_REVERSAL}you{SE_M_SAND_TOMB}savings.\p"
	.string "Cal{SE_M_BATON_PASS}o{SE_M_ATTRACT}you{SE_M_SAND_TOMB}POKéGEA{SE_M_MINIMIZE}i{SE_M_ACID_ARMOR}yo{SE_M_DIVE}need\n"
	.string "anything{SE_M_PERISH_SONG}Tak{SE_M_REVERSAL}care{SE_M_SUPERSONIC}{PLAYER}!$"

NewBarkTown_PlayersHouse_1F_Text_GuestRest::
	.string "You{SE_M_SAND_TOMB}tea{SE_M_MILK_DRINK}mus{SE_M_SPIT_UP}b{SE_M_REVERSAL}tired.\n"
	.string "Pleas{SE_M_REVERSAL}res{SE_M_SPIT_UP}her{SE_M_REVERSAL}fo{SE_M_SAND_TOMB}{SE_M_CHARGE}while.$"

NewBarkTown_PlayersHouse_1F_Text_GuestRestChallenge::
	.string "You{SE_M_SAND_TOMB}challeng{SE_M_REVERSAL}rule{SE_M_GRASSWHISTLE}d{SE_M_ATTRACT2}no{SE_M_SPIT_UP}allow\n"
	.string "healin{SE_M_SANDSTORM}here{SE_M_SUPERSONIC}bu{SE_M_SPIT_UP}{SE_M_HEAL_BELL}ca{SE_M_ATTRACT}stil{SE_M_BATON_PASS}help\l"
	.string "wit{SE_M_TRI_ATTACK}you{SE_M_SAND_TOMB}savings.$"

