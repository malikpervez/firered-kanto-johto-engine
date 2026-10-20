@ Johto (data/scripts/secret_base.inc), as built into the FireRed game.

J_SecretBase_EventScript_CheckEntrance::
	special GetSecretBaseTypeInFrontOfPlayer
	special CheckPlayerHasSecretBase
	goto_if_eq VAR_RESULT, TRUE, J_SecretBase_EventScript_AlreadyHasSecretBase
	checkfieldmove FIELD_MOVE_SECRET_POWER
	setfieldeffectargument 0, VAR_RESULT
	buffermovename STR_VAR_2, MOVE_SECRET_POWER
	goto_if_eq VAR_0x8007, SECRET_BASE_RED_CAVE, J_SecretBase_EventScript_Cave
	goto_if_eq VAR_0x8007, SECRET_BASE_BROWN_CAVE, J_SecretBase_EventScript_Cave
	goto_if_eq VAR_0x8007, SECRET_BASE_BLUE_CAVE, J_SecretBase_EventScript_Cave
	goto_if_eq VAR_0x8007, SECRET_BASE_YELLOW_CAVE, J_SecretBase_EventScript_Cave
	goto_if_eq VAR_0x8007, SECRET_BASE_TREE, J_SecretBase_EventScript_Tree
	goto_if_eq VAR_0x8007, SECRET_BASE_SHRUB, J_SecretBase_EventScript_Shrub
	end

J_SecretBase_EventScript_Cave::
	lockall
	goto_if_eq VAR_RESULT, PARTY_SIZE, J_SecretBase_EventScript_CaveNoSecretPower
	bufferpartymonnick STR_VAR_1, VAR_RESULT
	msgbox SecretBase_Text_IndentUseSecretPower, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, J_SecretBase_EventScript_CancelOnEntrance
	msgbox J_Text_MonUsedFieldMove, MSGBOX_DEFAULT
	closemessage
	dofieldeffect FLDEFF_USE_SECRET_POWER_CAVE
	waitstate
	goto J_SecretBase_EventScript_CaveEnter
	end

J_SecretBase_EventScript_CaveUseSecretPower::
	lockall
	dofieldeffect FLDEFF_USE_SECRET_POWER_CAVE
	waitstate
	goto J_SecretBase_EventScript_CaveEnter
	end

J_SecretBase_EventScript_CaveNoSecretPower::
	msgbox SecretBase_Text_SmallIndentInWall, MSGBOX_DEFAULT
	releaseall
	end

J_SecretBase_EventScript_CaveEnter::
	msgbox SecretBase_Text_DiscoveredSmallCavern, MSGBOX_DEFAULT
	goto J_SecretBase_EventScript_InitSecretBase
	end

J_SecretBase_EventScript_Tree::
	lockall
	goto_if_eq VAR_RESULT, PARTY_SIZE, J_SecretBase_EventScript_TreeNoSecretPower
	bufferpartymonnick STR_VAR_1, VAR_RESULT
	msgbox J_SecretBase_Text_TreeUseSecretPower, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, J_SecretBase_EventScript_CancelOnEntrance
	msgbox J_Text_MonUsedFieldMove, MSGBOX_DEFAULT
	closemessage
	dofieldeffect FLDEFF_USE_SECRET_POWER_TREE
	waitstate
	goto J_SecretBase_EventScript_TreeEnter
	end

J_SecretBase_EventScript_TreeUseSecretPower::
	lockall
	dofieldeffect FLDEFF_USE_SECRET_POWER_TREE
	waitstate
	goto J_SecretBase_EventScript_TreeEnter
	end

J_SecretBase_EventScript_TreeNoSecretPower::
	msgbox J_SecretBase_Text_TreeCanBeClimbed, MSGBOX_DEFAULT
	releaseall
	end

J_SecretBase_EventScript_TreeEnter::
	msgbox J_SecretBase_Text_VineDroppedDown, MSGBOX_DEFAULT
	goto J_SecretBase_EventScript_InitSecretBase
	end

J_SecretBase_EventScript_Shrub::
	lockall
	goto_if_eq VAR_RESULT, PARTY_SIZE, J_SecretBase_EventScript_ShrubNoSecretPower
	bufferpartymonnick STR_VAR_1, VAR_RESULT
	msgbox J_SecretBase_Text_ClumpUseSecretPower, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, J_SecretBase_EventScript_CancelOnEntrance
	msgbox J_Text_MonUsedFieldMove, MSGBOX_DEFAULT
	closemessage
	dofieldeffect FLDEFF_USE_SECRET_POWER_SHRUB
	waitstate
	goto J_SecretBase_EventScript_ShrubEnter
	end

J_SecretBase_EventScript_ShrubUseSecretPower::
	lockall
	dofieldeffect FLDEFF_USE_SECRET_POWER_SHRUB
	waitstate
	goto J_SecretBase_EventScript_ShrubEnter
	end

J_SecretBase_EventScript_ShrubNoSecretPower::
	msgbox J_SecretBase_Text_ClumpOfGrass, MSGBOX_DEFAULT
	releaseall
	end

J_SecretBase_EventScript_ShrubEnter::
	msgbox J_SecretBase_Text_DiscoveredSmallEntrance, MSGBOX_DEFAULT
	goto J_SecretBase_EventScript_InitSecretBase
	end

J_SecretBase_EventScript_InitSecretBase::
	closemessage
	playse SE_EXIT
	setvar JOHTO_VAR_INIT_SECRET_BASE, 0
	setflag FLAG_HIDE_SECRET_BASE_TRAINER
	special SetPlayerSecretBase
	special EnterSecretBase
	setvar VAR_0x8004, 0
	setvar VAR_0x8005, 0
	special InitSecretBaseDecorationSprites
	setvar JOHTO_VAR_SECRET_BASE_INITIALIZED, 1
	waitstate
	end

J_SecretBase_EventScript_FirstEntrance::
	applymovement LOCALID_PLAYER, J_SecretBase_Movement_EnterBase
	waitmovement 0
	setvar JOHTO_VAR_INIT_SECRET_BASE, 1
	msgbox J_SecretBase_Text_WantToMakeYourSecretBaseHere, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, J_SecretBase_EventScript_SetAsBase
	closemessage
	playse SE_EXIT
	special ClearAndLeaveSecretBase
	end

J_SecretBase_EventScript_SetAsBase::
	closemessage
	setflag FLAG_RECEIVED_SECRET_POWER
	special EnterNewlyCreatedSecretBase
	waitstate
	end

J_SecretBase_Movement_EnterBase:
	walk_up
	walk_up
	step_end

J_SecretBase_EventScript_Enter::
	lockall
	setvar JOHTO_VAR_INIT_SECRET_BASE, 1
	playse SE_EXIT
	special IsCurSecretBaseOwnedByAnotherPlayer
	goto_if_eq VAR_RESULT, FALSE, J_SecretBase_EventScript_EnterPlayersBase
	clearflag FLAG_HIDE_SECRET_BASE_TRAINER
	special EnterSecretBase
	setvar JOHTO_VAR_SECRET_BASE_INITIALIZED, 0
	waitstate
	end

J_SecretBase_EventScript_EnterPlayersBase::
	setflag FLAG_HIDE_SECRET_BASE_TRAINER
	special EnterSecretBase
	setvar JOHTO_VAR_SECRET_BASE_INITIALIZED, 0
	waitstate
	end

J_SecretBase_EventScript_AlreadyHasSecretBase::
	checkfieldmove FIELD_MOVE_SECRET_POWER
	goto_if_eq VAR_RESULT, PARTY_SIZE, J_SecretBase_EventScript_NoSecretPower
	setfieldeffectargument 0, VAR_RESULT
	setorcopyvar VAR_0x8004, VAR_RESULT
	lockall
	special GetSecretBaseNearbyMapName
	msgbox J_SecretBase_Text_WouldYouLikeToMoveBases, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, J_SecretBase_EventScript_CancelOnEntrance
	msgbox J_SecretBase_Text_AllDecorationsWillBeReturned, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, J_SecretBase_EventScript_CancelOnEntrance
	fadescreenswapbuffers FADE_TO_BLACK
	special MoveOutOfSecretBaseFromOutside
	closemessage
	fadescreenswapbuffers FADE_FROM_BLACK
	msgbox J_SecretBase_Text_MovingCompletedUseSecretPower, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, J_SecretBase_EventScript_CancelOnEntrance
	bufferpartymonnick STR_VAR_1, VAR_0x8004
	buffermovename STR_VAR_2, MOVE_SECRET_POWER
	msgbox J_Text_MonUsedFieldMove, MSGBOX_DEFAULT
	closemessage
	closemessage
	goto_if_eq VAR_0x8007, SECRET_BASE_RED_CAVE, J_SecretBase_EventScript_CaveUseSecretPower
	goto_if_eq VAR_0x8007, SECRET_BASE_BROWN_CAVE, J_SecretBase_EventScript_CaveUseSecretPower
	goto_if_eq VAR_0x8007, SECRET_BASE_BLUE_CAVE, J_SecretBase_EventScript_CaveUseSecretPower
	goto_if_eq VAR_0x8007, SECRET_BASE_YELLOW_CAVE, J_SecretBase_EventScript_CaveUseSecretPower
	goto_if_eq VAR_0x8007, SECRET_BASE_TREE, J_SecretBase_EventScript_TreeUseSecretPower
	goto_if_eq VAR_0x8007, SECRET_BASE_SHRUB, J_SecretBase_EventScript_ShrubUseSecretPower
	releaseall
	end

J_SecretBase_EventScript_NoSecretPower::
	lockall
	goto_if_eq VAR_0x8007, SECRET_BASE_RED_CAVE, J_SecretBase_EventScript_CaveNoSecretPower
	goto_if_eq VAR_0x8007, SECRET_BASE_BROWN_CAVE, J_SecretBase_EventScript_CaveNoSecretPower
	goto_if_eq VAR_0x8007, SECRET_BASE_BLUE_CAVE, J_SecretBase_EventScript_CaveNoSecretPower
	goto_if_eq VAR_0x8007, SECRET_BASE_YELLOW_CAVE, J_SecretBase_EventScript_CaveNoSecretPower
	goto_if_eq VAR_0x8007, SECRET_BASE_TREE, J_SecretBase_EventScript_TreeNoSecretPower
	goto_if_eq VAR_0x8007, SECRET_BASE_SHRUB, J_SecretBase_EventScript_ShrubNoSecretPower
	end

J_SecretBase_EventScript_CancelOnEntrance::
	closemessage
	releaseall
	end

J_SecretBase_EventScript_SetDecorationFlags::
	setflag JOHTO_FLAG_DECORATION_1
	setflag JOHTO_FLAG_DECORATION_2
	setflag JOHTO_FLAG_DECORATION_3
	setflag JOHTO_FLAG_DECORATION_4
	setflag JOHTO_FLAG_DECORATION_5
	setflag JOHTO_FLAG_DECORATION_6
	setflag JOHTO_FLAG_DECORATION_7
	setflag JOHTO_FLAG_DECORATION_8
	setflag JOHTO_FLAG_DECORATION_9
	setflag JOHTO_FLAG_DECORATION_10
	setflag JOHTO_FLAG_DECORATION_11
	setflag JOHTO_FLAG_DECORATION_12
	setflag JOHTO_FLAG_DECORATION_13
	setflag JOHTO_FLAG_DECORATION_14
	return

J_SecretBase_EventScript_InitDecorations::
	setvar VAR_0x8004, 0
	setvar VAR_0x8005, 0
	special InitSecretBaseDecorationSprites
	setvar JOHTO_VAR_SECRET_BASE_INITIALIZED, 1
	end

J_SecretBase_EventScript_SetDecoration::
	setvar VAR_0x8005, 0
	goto J_SecretBase_EventScript_SetDecoration2
	end

J_SecretBase_EventScript_SetDecoration2::
	special SetDecoration
	end

J_SecretBase_EventScript_PutAwayDecoration::
	setvar VAR_0x8004, 0
	goto J_SecretBase_EventScript_PutAwayDecorationLoop
	end

J_SecretBase_EventScript_PutAwayDecorationLoop::
	special PutAwayDecorationIteration
	goto_if_eq VAR_RESULT, 1, J_SecretBase_EventScript_PutAwayDecorationEnd
	addvar VAR_0x8004, 1
	goto_if_eq VAR_0x8005, 0, J_SecretBase_EventScript_PutAwayDecorationLoop
	removeobject VAR_0x8006
	setflag VAR_0x8005
	goto J_SecretBase_EventScript_PutAwayDecorationLoop
	end

J_SecretBase_EventScript_PutAwayDecorationEnd::
	end

J_SecretBase_EventScript_RecordMixTrainer::
	special GetSecretBaseOwnerAndState
	goto_if_eq VAR_0x8004, 0, J_SecretBase_EventScript_Trainer0
	goto_if_eq VAR_0x8004, 1, J_SecretBase_EventScript_Trainer1
	goto_if_eq VAR_0x8004, 2, J_SecretBase_EventScript_Trainer2
	goto_if_eq VAR_0x8004, 3, J_SecretBase_EventScript_Trainer3
	goto_if_eq VAR_0x8004, 4, J_SecretBase_EventScript_Trainer4
	goto_if_eq VAR_0x8004, 5, J_SecretBase_EventScript_Trainer5
	goto_if_eq VAR_0x8004, 6, J_SecretBase_EventScript_Trainer6
	goto_if_eq VAR_0x8004, 7, J_SecretBase_EventScript_Trainer7
	goto_if_eq VAR_0x8004, 8, J_SecretBase_EventScript_Trainer8
	goto_if_eq VAR_0x8004, 9, J_SecretBase_EventScript_Trainer9
	end

J_SecretBase_EventScript_Trainer0::
	lock
	faceplayer
	goto_if_unset JOHTO_FLAG_SYS_GAME_CLEAR, J_SecretBase_EventScript_Trainer0PreChampion
	goto_if_eq VAR_RESULT, 1, J_SecretBase_EventScript_Trainer0PostBattle
	msgbox J_SecretBase_Text_Trainer0Intro, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, J_SecretBase_EventScript_Trainer0DeclineBattle
	setvar VAR_RESULT, 1
	special SetBattledOwnerFromResult
	call J_Common_EventScript_SaveGame
	goto_if_eq VAR_RESULT, 0, J_SecretBase_EventScript_Trainer0DeclineBattle
	msgbox J_SecretBase_Text_Trainer0AcceptBattle, MSGBOX_DEFAULT
	goto J_SecretBase_EventScript_BattleTrainer
	end

J_SecretBase_EventScript_Trainer0PreChampion::
	msgbox J_SecretBase_Text_Trainer0PreChampion, MSGBOX_DEFAULT
	release
	end

J_SecretBase_EventScript_Trainer0DeclineBattle::
	special DeclinedSecretBaseBattle
	setvar VAR_RESULT, 0
	special SetBattledOwnerFromResult
	msgbox J_SecretBase_Text_Trainer0DeclineBattle, MSGBOX_DEFAULT
	release
	end

J_SecretBase_EventScript_Trainer0PostBattle::
	msgbox J_SecretBase_Text_Trainer0PostBattle, MSGBOX_DEFAULT
	release
	end

J_SecretBase_EventScript_Trainer1::
	lock
	faceplayer
	goto_if_unset JOHTO_FLAG_SYS_GAME_CLEAR, J_SecretBase_EventScript_Trainer1PreChampion
	goto_if_eq VAR_RESULT, 1, J_SecretBase_EventScript_Trainer1PostBattle
	msgbox J_SecretBase_Text_Trainer1Intro, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, J_SecretBase_EventScript_Trainer1DeclineBattle
	setvar VAR_RESULT, 1
	special SetBattledOwnerFromResult
	call J_Common_EventScript_SaveGame
	goto_if_eq VAR_RESULT, 0, J_SecretBase_EventScript_Trainer1DeclineBattle
	msgbox J_SecretBase_Text_Trainer1AcceptBattle, MSGBOX_DEFAULT
	goto J_SecretBase_EventScript_BattleTrainer
	end

J_SecretBase_EventScript_Trainer1PreChampion::
	msgbox J_SecretBase_Text_Trainer1PreChampion, MSGBOX_DEFAULT
	release
	end

J_SecretBase_EventScript_Trainer1DeclineBattle::
	special DeclinedSecretBaseBattle
	setvar VAR_RESULT, 0
	special SetBattledOwnerFromResult
	msgbox J_SecretBase_Text_Trainer1DeclineBattle, MSGBOX_DEFAULT
	release
	end

J_SecretBase_EventScript_Trainer1PostBattle::
	msgbox J_SecretBase_Text_Trainer1PostBattle, MSGBOX_DEFAULT
	release
	end

J_SecretBase_EventScript_Trainer2::
	lock
	faceplayer
	goto_if_unset JOHTO_FLAG_SYS_GAME_CLEAR, J_SecretBase_EventScript_Trainer2PreChampion
	goto_if_eq VAR_RESULT, 1, J_SecretBase_EventScript_Trainer2PostBattle
	msgbox J_SecretBase_Text_Trainer2Intro, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, J_SecretBase_EventScript_Trainer2DeclineBattle
	setvar VAR_RESULT, 1
	special SetBattledOwnerFromResult
	call J_Common_EventScript_SaveGame
	goto_if_eq VAR_RESULT, 0, J_SecretBase_EventScript_Trainer2DeclineBattle
	msgbox J_SecretBase_Text_Trainer2AcceptBattle, MSGBOX_DEFAULT
	goto J_SecretBase_EventScript_BattleTrainer
	end

J_SecretBase_EventScript_Trainer2PreChampion::
	msgbox J_SecretBase_Text_Trainer2PreChampion, MSGBOX_DEFAULT
	release
	end

J_SecretBase_EventScript_Trainer2DeclineBattle::
	special DeclinedSecretBaseBattle
	setvar VAR_RESULT, 0
	special SetBattledOwnerFromResult
	msgbox J_SecretBase_Text_Trainer2DeclineBattle, MSGBOX_DEFAULT
	release
	end

J_SecretBase_EventScript_Trainer2PostBattle::
	msgbox J_SecretBase_Text_Trainer2PostBattle, MSGBOX_DEFAULT
	release
	end

J_SecretBase_EventScript_Trainer3::
	lock
	faceplayer
	goto_if_unset JOHTO_FLAG_SYS_GAME_CLEAR, J_SecretBase_EventScript_Trainer3PreChampion
	goto_if_eq VAR_RESULT, 1, J_SecretBase_EventScript_Trainer3PostBattle
	msgbox J_SecretBase_Text_Trainer3Intro, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, J_SecretBase_EventScript_Trainer3DeclineBattle
	setvar VAR_RESULT, 1
	special SetBattledOwnerFromResult
	call J_Common_EventScript_SaveGame
	goto_if_eq VAR_RESULT, 0, J_SecretBase_EventScript_Trainer3DeclineBattle
	msgbox J_SecretBase_Text_Trainer3AcceptBattle, MSGBOX_DEFAULT
	goto J_SecretBase_EventScript_BattleTrainer
	end

J_SecretBase_EventScript_Trainer3PreChampion::
	msgbox J_SecretBase_Text_Trainer3PreChampion, MSGBOX_DEFAULT
	release
	end

J_SecretBase_EventScript_Trainer3DeclineBattle::
	special DeclinedSecretBaseBattle
	setvar VAR_RESULT, 0
	special SetBattledOwnerFromResult
	msgbox J_SecretBase_Text_Trainer3DeclineBattle, MSGBOX_DEFAULT
	release
	end

J_SecretBase_EventScript_Trainer3PostBattle::
	msgbox J_SecretBase_Text_Trainer3PostBattle, MSGBOX_DEFAULT
	release
	end

J_SecretBase_EventScript_Trainer4::
	lock
	faceplayer
	goto_if_unset JOHTO_FLAG_SYS_GAME_CLEAR, J_SecretBase_EventScript_Trainer4PreChampion
	goto_if_eq VAR_RESULT, 1, J_SecretBase_EventScript_Trainer4PostBattle
	msgbox J_SecretBase_Text_Trainer4Intro, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, J_SecretBase_EventScript_Trainer4DeclineBattle
	setvar VAR_RESULT, 1
	special SetBattledOwnerFromResult
	call J_Common_EventScript_SaveGame
	goto_if_eq VAR_RESULT, 0, J_SecretBase_EventScript_Trainer4DeclineBattle
	msgbox J_SecretBase_Text_Trainer4AcceptBattle, MSGBOX_DEFAULT
	goto J_SecretBase_EventScript_BattleTrainer
	end

J_SecretBase_EventScript_Trainer4PreChampion::
	msgbox J_SecretBase_Text_Trainer4PreChampion, MSGBOX_DEFAULT
	release
	end

J_SecretBase_EventScript_Trainer4DeclineBattle::
	special DeclinedSecretBaseBattle
	setvar VAR_RESULT, 0
	special SetBattledOwnerFromResult
	msgbox J_SecretBase_Text_Trainer4DeclineBattle, MSGBOX_DEFAULT
	release
	end

J_SecretBase_EventScript_Trainer4PostBattle::
	msgbox J_SecretBase_Text_Trainer4PostBattle, MSGBOX_DEFAULT
	release
	end

J_SecretBase_EventScript_Trainer5::
	lock
	faceplayer
	goto_if_unset JOHTO_FLAG_SYS_GAME_CLEAR, J_SecretBase_EventScript_Trainer5PreChampion
	goto_if_eq VAR_RESULT, 1, J_SecretBase_EventScript_Trainer5PostBattle
	msgbox J_SecretBase_Text_Trainer5Intro, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, J_SecretBase_EventScript_Trainer5DeclineBattle
	setvar VAR_RESULT, 1
	special SetBattledOwnerFromResult
	call J_Common_EventScript_SaveGame
	goto_if_eq VAR_RESULT, 0, J_SecretBase_EventScript_Trainer5DeclineBattle
	msgbox J_SecretBase_Text_Trainer5AcceptBattle, MSGBOX_DEFAULT
	goto J_SecretBase_EventScript_BattleTrainer
	end

J_SecretBase_EventScript_Trainer5PreChampion::
	msgbox J_SecretBase_Text_Trainer5PreChampion, MSGBOX_DEFAULT
	release
	end

J_SecretBase_EventScript_Trainer5DeclineBattle::
	special DeclinedSecretBaseBattle
	setvar VAR_RESULT, 0
	special SetBattledOwnerFromResult
	msgbox J_SecretBase_Text_Trainer5DeclineBattle, MSGBOX_DEFAULT
	release
	end

J_SecretBase_EventScript_Trainer5PostBattle::
	msgbox J_SecretBase_Text_Trainer5PostBattle, MSGBOX_DEFAULT
	release
	end

J_SecretBase_EventScript_Trainer6::
	lock
	faceplayer
	goto_if_unset JOHTO_FLAG_SYS_GAME_CLEAR, J_SecretBase_EventScript_Trainer6PreChampion
	goto_if_eq VAR_RESULT, 1, J_SecretBase_EventScript_Trainer6PostBattle
	msgbox J_SecretBase_Text_Trainer6Intro, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, J_SecretBase_EventScript_Trainer6DeclineBattle
	setvar VAR_RESULT, 1
	special SetBattledOwnerFromResult
	call J_Common_EventScript_SaveGame
	goto_if_eq VAR_RESULT, 0, J_SecretBase_EventScript_Trainer6DeclineBattle
	msgbox J_SecretBase_Text_Trainer6AcceptBattle, MSGBOX_DEFAULT
	goto J_SecretBase_EventScript_BattleTrainer
	end

J_SecretBase_EventScript_Trainer6PreChampion::
	msgbox J_SecretBase_Text_Trainer6PreChampion, MSGBOX_DEFAULT
	release
	end

J_SecretBase_EventScript_Trainer6DeclineBattle::
	special DeclinedSecretBaseBattle
	setvar VAR_RESULT, 0
	special SetBattledOwnerFromResult
	msgbox J_SecretBase_Text_Trainer6DeclineBattle, MSGBOX_DEFAULT
	release
	end

J_SecretBase_EventScript_Trainer6PostBattle::
	msgbox J_SecretBase_Text_Trainer6PostBattle, MSGBOX_DEFAULT
	release
	end

J_SecretBase_EventScript_Trainer7::
	lock
	faceplayer
	goto_if_unset JOHTO_FLAG_SYS_GAME_CLEAR, J_SecretBase_EventScript_Trainer7PreChampion
	goto_if_eq VAR_RESULT, 1, J_SecretBase_EventScript_Trainer7PostBattle
	msgbox J_SecretBase_Text_Trainer7Intro, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, J_SecretBase_EventScript_Trainer7DeclineBattle
	setvar VAR_RESULT, 1
	special SetBattledOwnerFromResult
	call J_Common_EventScript_SaveGame
	goto_if_eq VAR_RESULT, 0, J_SecretBase_EventScript_Trainer7DeclineBattle
	msgbox J_SecretBase_Text_Trainer7AcceptBattle, MSGBOX_DEFAULT
	goto J_SecretBase_EventScript_BattleTrainer
	end

J_SecretBase_EventScript_Trainer7PreChampion::
	msgbox J_SecretBase_Text_Trainer7PreChampion, MSGBOX_DEFAULT
	release
	end

J_SecretBase_EventScript_Trainer7DeclineBattle::
	special DeclinedSecretBaseBattle
	setvar VAR_RESULT, 0
	special SetBattledOwnerFromResult
	msgbox J_SecretBase_Text_Trainer7DeclineBattle, MSGBOX_DEFAULT
	release
	end

J_SecretBase_EventScript_Trainer7PostBattle::
	msgbox J_SecretBase_Text_Trainer7PostBattle, MSGBOX_DEFAULT
	release
	end

J_SecretBase_EventScript_Trainer8::
	lock
	faceplayer
	goto_if_unset JOHTO_FLAG_SYS_GAME_CLEAR, J_SecretBase_EventScript_Trainer8PreChampion
	goto_if_eq VAR_RESULT, 1, J_SecretBase_EventScript_Trainer8PostBattle
	msgbox J_SecretBase_Text_Trainer8Intro, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, J_SecretBase_EventScript_Trainer8DeclineBattle
	setvar VAR_RESULT, 1
	special SetBattledOwnerFromResult
	call J_Common_EventScript_SaveGame
	goto_if_eq VAR_RESULT, 0, J_SecretBase_EventScript_Trainer8DeclineBattle
	msgbox J_SecretBase_Text_Trainer8AcceptBattle, MSGBOX_DEFAULT
	goto J_SecretBase_EventScript_BattleTrainer
	end

J_SecretBase_EventScript_Trainer8PreChampion::
	msgbox J_SecretBase_Text_Trainer8PreChampion, MSGBOX_DEFAULT
	release
	end

J_SecretBase_EventScript_Trainer8DeclineBattle::
	special DeclinedSecretBaseBattle
	setvar VAR_RESULT, 0
	special SetBattledOwnerFromResult
	msgbox J_SecretBase_Text_Trainer8DeclineBattle, MSGBOX_DEFAULT
	release
	end

J_SecretBase_EventScript_Trainer8PostBattle::
	msgbox J_SecretBase_Text_Trainer8PostBattle, MSGBOX_DEFAULT
	release
	end

J_SecretBase_EventScript_Trainer9::
	lock
	faceplayer
	goto_if_unset JOHTO_FLAG_SYS_GAME_CLEAR, J_SecretBase_EventScript_Trainer9PreChampion
	goto_if_eq VAR_RESULT, 1, J_SecretBase_EventScript_Trainer9PostBattle
	msgbox J_SecretBase_Text_Trainer9Intro, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, J_SecretBase_EventScript_Trainer9DeclineBattle
	setvar VAR_RESULT, 1
	special SetBattledOwnerFromResult
	call J_Common_EventScript_SaveGame
	goto_if_eq VAR_RESULT, 0, J_SecretBase_EventScript_Trainer9DeclineBattle
	msgbox J_SecretBase_Text_Trainer9AcceptBattle, MSGBOX_DEFAULT
	goto J_SecretBase_EventScript_BattleTrainer
	end

J_SecretBase_EventScript_Trainer9PreChampion::
	msgbox J_SecretBase_Text_Trainer9PreChampion, MSGBOX_DEFAULT
	release
	end

J_SecretBase_EventScript_Trainer9DeclineBattle::
	special DeclinedSecretBaseBattle
	setvar VAR_RESULT, 0
	special SetBattledOwnerFromResult
	msgbox J_SecretBase_Text_Trainer9DeclineBattle, MSGBOX_DEFAULT
	release
	end

J_SecretBase_EventScript_Trainer9PostBattle::
	msgbox J_SecretBase_Text_Trainer9PostBattle, MSGBOX_DEFAULT
	release
	end

J_SecretBase_EventScript_BattleTrainer::
	special PrepSecretBaseBattleFlags
	setvar VAR_0x8004, SPECIAL_BATTLE_SECRET_BASE
	setvar VAR_0x8005, 0
	special DoSpecialTrainerBattle
	waitstate
	call_if_eq VAR_RESULT, B_OUTCOME_DREW, J_SecretBase_EventScript_DrewSecretBaseBattle
	call_if_eq VAR_RESULT, B_OUTCOME_WON, J_SecretBase_EventScript_WonSecretBaseBattle
	call_if_eq VAR_RESULT, B_OUTCOME_LOST, J_SecretBase_EventScript_LostSecretBaseBattle
	special HealPlayerParty
	callnative UpdateFollowingPokemon
	release
	end

J_SecretBase_EventScript_DrewSecretBaseBattle::
	special DrewSecretBaseBattle
	return

J_SecretBase_EventScript_WonSecretBaseBattle::
	special WonSecretBaseBattle
	return

J_SecretBase_EventScript_LostSecretBaseBattle::
	special LostSecretBaseBattle
	return

