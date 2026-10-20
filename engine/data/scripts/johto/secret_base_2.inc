@ Johto (data/scripts/secret_base.inc), as built into the FireRed game.

J_SecretBase_EventScript_CheckEntrance::
	special GetSecretBaseTypeInFrontOfPlayer
	special CheckPlayerHasSecretBase
	goto_if_eq 32781, TRUE, J_SecretBase_EventScript_AlreadyHasSecretBase
	checkfieldmove FIELD_MOVE_SECRET_POWER
	setfieldeffectargument 0, 32781
	buffermovename STR_VAR_2, MOVE_SECRET_POWER
	goto_if_eq 32775, 1, J_SecretBase_EventScript_Cave
	goto_if_eq 32775, 2, J_SecretBase_EventScript_Cave
	goto_if_eq 32775, 3, J_SecretBase_EventScript_Cave
	goto_if_eq 32775, 4, J_SecretBase_EventScript_Cave
	goto_if_eq 32775, 5, J_SecretBase_EventScript_Tree
	goto_if_eq 32775, 6, J_SecretBase_EventScript_Shrub
	end

J_SecretBase_EventScript_Cave::
	lockall
	goto_if_eq 32781, 6, J_SecretBase_EventScript_CaveNoSecretPower
	bufferpartymonnick STR_VAR_1, 32781
	msgbox SecretBase_Text_IndentUseSecretPower, MSGBOX_YESNO
	goto_if_eq 32781, NO, J_SecretBase_EventScript_CancelOnEntrance
	msgbox J_Text_MonUsedFieldMove, MSGBOX_DEFAULT
	closemessage
	dofieldeffect 11
	waitstate
	goto J_SecretBase_EventScript_CaveEnter
	end

J_SecretBase_EventScript_CaveUseSecretPower::
	lockall
	dofieldeffect 11
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
	goto_if_eq 32781, 6, J_SecretBase_EventScript_TreeNoSecretPower
	bufferpartymonnick STR_VAR_1, 32781
	msgbox J_SecretBase_Text_TreeUseSecretPower, MSGBOX_YESNO
	goto_if_eq 32781, NO, J_SecretBase_EventScript_CancelOnEntrance
	msgbox J_Text_MonUsedFieldMove, MSGBOX_DEFAULT
	closemessage
	dofieldeffect 26
	waitstate
	goto J_SecretBase_EventScript_TreeEnter
	end

J_SecretBase_EventScript_TreeUseSecretPower::
	lockall
	dofieldeffect 26
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
	goto_if_eq 32781, 6, J_SecretBase_EventScript_ShrubNoSecretPower
	bufferpartymonnick STR_VAR_1, 32781
	msgbox J_SecretBase_Text_ClumpUseSecretPower, MSGBOX_YESNO
	goto_if_eq 32781, NO, J_SecretBase_EventScript_CancelOnEntrance
	msgbox J_Text_MonUsedFieldMove, MSGBOX_DEFAULT
	closemessage
	dofieldeffect 27
	waitstate
	goto J_SecretBase_EventScript_ShrubEnter
	end

J_SecretBase_EventScript_ShrubUseSecretPower::
	lockall
	dofieldeffect 27
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
	playse 9
	setvar 20615, 0
	setflag 0
	special SetPlayerSecretBase
	special EnterSecretBase
	setvar 32772, 0
	setvar 32773, 0
	special InitSecretBaseDecorationSprites
	setvar 20601, 1
	waitstate
	end

J_SecretBase_EventScript_FirstEntrance::
	applymovement 255, J_SecretBase_Movement_EnterBase
	waitmovement 0
	setvar 20615, 1
	msgbox J_SecretBase_Text_WantToMakeYourSecretBaseHere, MSGBOX_YESNO
	goto_if_eq 32781, YES, J_SecretBase_EventScript_SetAsBase
	closemessage
	playse 9
	special ClearAndLeaveSecretBase
	end

J_SecretBase_EventScript_SetAsBase::
	closemessage
	setflag 0
	special EnterNewlyCreatedSecretBase
	waitstate
	end

J_SecretBase_Movement_EnterBase:
	walk_up
	walk_up
	step_end

J_SecretBase_EventScript_Enter::
	lockall
	setvar 20615, 1
	playse 9
	special IsCurSecretBaseOwnedByAnotherPlayer
	goto_if_eq 32781, FALSE, J_SecretBase_EventScript_EnterPlayersBase
	clearflag 0
	special EnterSecretBase
	setvar 20601, 0
	waitstate
	end

J_SecretBase_EventScript_EnterPlayersBase::
	setflag 0
	special EnterSecretBase
	setvar 20601, 0
	waitstate
	end

J_SecretBase_EventScript_AlreadyHasSecretBase::
	checkfieldmove FIELD_MOVE_SECRET_POWER
	goto_if_eq 32781, 6, J_SecretBase_EventScript_NoSecretPower
	setfieldeffectargument 0, 32781
	setorcopyvar 32772, 32781
	lockall
	special GetSecretBaseNearbyMapName
	msgbox J_SecretBase_Text_WouldYouLikeToMoveBases, MSGBOX_YESNO
	goto_if_eq 32781, NO, J_SecretBase_EventScript_CancelOnEntrance
	msgbox J_SecretBase_Text_AllDecorationsWillBeReturned, MSGBOX_YESNO
	goto_if_eq 32781, NO, J_SecretBase_EventScript_CancelOnEntrance
	fadescreenswapbuffers 1
	special MoveOutOfSecretBaseFromOutside
	closemessage
	fadescreenswapbuffers 0
	msgbox J_SecretBase_Text_MovingCompletedUseSecretPower, MSGBOX_YESNO
	goto_if_eq 32781, NO, J_SecretBase_EventScript_CancelOnEntrance
	bufferpartymonnick STR_VAR_1, 32772
	buffermovename STR_VAR_2, MOVE_SECRET_POWER
	msgbox J_Text_MonUsedFieldMove, MSGBOX_DEFAULT
	closemessage
	closemessage
	goto_if_eq 32775, 1, J_SecretBase_EventScript_CaveUseSecretPower
	goto_if_eq 32775, 2, J_SecretBase_EventScript_CaveUseSecretPower
	goto_if_eq 32775, 3, J_SecretBase_EventScript_CaveUseSecretPower
	goto_if_eq 32775, 4, J_SecretBase_EventScript_CaveUseSecretPower
	goto_if_eq 32775, 5, J_SecretBase_EventScript_TreeUseSecretPower
	goto_if_eq 32775, 6, J_SecretBase_EventScript_ShrubUseSecretPower
	releaseall
	end

J_SecretBase_EventScript_NoSecretPower::
	lockall
	goto_if_eq 32775, 1, J_SecretBase_EventScript_CaveNoSecretPower
	goto_if_eq 32775, 2, J_SecretBase_EventScript_CaveNoSecretPower
	goto_if_eq 32775, 3, J_SecretBase_EventScript_CaveNoSecretPower
	goto_if_eq 32775, 4, J_SecretBase_EventScript_CaveNoSecretPower
	goto_if_eq 32775, 5, J_SecretBase_EventScript_TreeNoSecretPower
	goto_if_eq 32775, 6, J_SecretBase_EventScript_ShrubNoSecretPower
	end

J_SecretBase_EventScript_CancelOnEntrance::
	closemessage
	releaseall
	end

J_SecretBase_EventScript_SetDecorationFlags::
	setflag 9066
	setflag 9067
	setflag 9068
	setflag 9069
	setflag 9070
	setflag 9071
	setflag 9072
	setflag 9073
	setflag 9074
	setflag 9075
	setflag 9076
	setflag 9077
	setflag 9078
	setflag 9079
	return

J_SecretBase_EventScript_InitDecorations::
	setvar 32772, 0
	setvar 32773, 0
	special InitSecretBaseDecorationSprites
	setvar 20601, 1
	end

J_SecretBase_EventScript_SetDecoration::
	setvar 32773, 0
	goto J_SecretBase_EventScript_SetDecoration2
	end

J_SecretBase_EventScript_SetDecoration2::
	special SetDecoration
	end

J_SecretBase_EventScript_PutAwayDecoration::
	setvar 32772, 0
	goto J_SecretBase_EventScript_PutAwayDecorationLoop
	end

J_SecretBase_EventScript_PutAwayDecorationLoop::
	special PutAwayDecorationIteration
	goto_if_eq 32781, 1, J_SecretBase_EventScript_PutAwayDecorationEnd
	addvar 32772, 1
	goto_if_eq 32773, 0, J_SecretBase_EventScript_PutAwayDecorationLoop
	removeobject 32774
	setflag 32773
	goto J_SecretBase_EventScript_PutAwayDecorationLoop
	end

J_SecretBase_EventScript_PutAwayDecorationEnd::
	end

J_SecretBase_EventScript_RecordMixTrainer::
	special GetSecretBaseOwnerAndState
	goto_if_eq 32772, 0, J_SecretBase_EventScript_Trainer0
	goto_if_eq 32772, 1, J_SecretBase_EventScript_Trainer1
	goto_if_eq 32772, 2, J_SecretBase_EventScript_Trainer2
	goto_if_eq 32772, 3, J_SecretBase_EventScript_Trainer3
	goto_if_eq 32772, 4, J_SecretBase_EventScript_Trainer4
	goto_if_eq 32772, 5, J_SecretBase_EventScript_Trainer5
	goto_if_eq 32772, 6, J_SecretBase_EventScript_Trainer6
	goto_if_eq 32772, 7, J_SecretBase_EventScript_Trainer7
	goto_if_eq 32772, 8, J_SecretBase_EventScript_Trainer8
	goto_if_eq 32772, 9, J_SecretBase_EventScript_Trainer9
	end

J_SecretBase_EventScript_Trainer0::
	lock
	faceplayer
	goto_if_unset 10387, J_SecretBase_EventScript_Trainer0PreChampion
	goto_if_eq 32781, 1, J_SecretBase_EventScript_Trainer0PostBattle
	msgbox J_SecretBase_Text_Trainer0Intro, MSGBOX_YESNO
	goto_if_eq 32781, NO, J_SecretBase_EventScript_Trainer0DeclineBattle
	setvar 32781, 1
	special SetBattledOwnerFromResult
	call J_Common_EventScript_SaveGame
	goto_if_eq 32781, 0, J_SecretBase_EventScript_Trainer0DeclineBattle
	msgbox J_SecretBase_Text_Trainer0AcceptBattle, MSGBOX_DEFAULT
	goto J_SecretBase_EventScript_BattleTrainer
	end

J_SecretBase_EventScript_Trainer0PreChampion::
	msgbox J_SecretBase_Text_Trainer0PreChampion, MSGBOX_DEFAULT
	release
	end

J_SecretBase_EventScript_Trainer0DeclineBattle::
	special DeclinedSecretBaseBattle
	setvar 32781, 0
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
	goto_if_unset 10387, J_SecretBase_EventScript_Trainer1PreChampion
	goto_if_eq 32781, 1, J_SecretBase_EventScript_Trainer1PostBattle
	msgbox J_SecretBase_Text_Trainer1Intro, MSGBOX_YESNO
	goto_if_eq 32781, NO, J_SecretBase_EventScript_Trainer1DeclineBattle
	setvar 32781, 1
	special SetBattledOwnerFromResult
	call J_Common_EventScript_SaveGame
	goto_if_eq 32781, 0, J_SecretBase_EventScript_Trainer1DeclineBattle
	msgbox J_SecretBase_Text_Trainer1AcceptBattle, MSGBOX_DEFAULT
	goto J_SecretBase_EventScript_BattleTrainer
	end

J_SecretBase_EventScript_Trainer1PreChampion::
	msgbox J_SecretBase_Text_Trainer1PreChampion, MSGBOX_DEFAULT
	release
	end

J_SecretBase_EventScript_Trainer1DeclineBattle::
	special DeclinedSecretBaseBattle
	setvar 32781, 0
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
	goto_if_unset 10387, J_SecretBase_EventScript_Trainer2PreChampion
	goto_if_eq 32781, 1, J_SecretBase_EventScript_Trainer2PostBattle
	msgbox J_SecretBase_Text_Trainer2Intro, MSGBOX_YESNO
	goto_if_eq 32781, NO, J_SecretBase_EventScript_Trainer2DeclineBattle
	setvar 32781, 1
	special SetBattledOwnerFromResult
	call J_Common_EventScript_SaveGame
	goto_if_eq 32781, 0, J_SecretBase_EventScript_Trainer2DeclineBattle
	msgbox J_SecretBase_Text_Trainer2AcceptBattle, MSGBOX_DEFAULT
	goto J_SecretBase_EventScript_BattleTrainer
	end

J_SecretBase_EventScript_Trainer2PreChampion::
	msgbox J_SecretBase_Text_Trainer2PreChampion, MSGBOX_DEFAULT
	release
	end

J_SecretBase_EventScript_Trainer2DeclineBattle::
	special DeclinedSecretBaseBattle
	setvar 32781, 0
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
	goto_if_unset 10387, J_SecretBase_EventScript_Trainer3PreChampion
	goto_if_eq 32781, 1, J_SecretBase_EventScript_Trainer3PostBattle
	msgbox J_SecretBase_Text_Trainer3Intro, MSGBOX_YESNO
	goto_if_eq 32781, NO, J_SecretBase_EventScript_Trainer3DeclineBattle
	setvar 32781, 1
	special SetBattledOwnerFromResult
	call J_Common_EventScript_SaveGame
	goto_if_eq 32781, 0, J_SecretBase_EventScript_Trainer3DeclineBattle
	msgbox J_SecretBase_Text_Trainer3AcceptBattle, MSGBOX_DEFAULT
	goto J_SecretBase_EventScript_BattleTrainer
	end

J_SecretBase_EventScript_Trainer3PreChampion::
	msgbox J_SecretBase_Text_Trainer3PreChampion, MSGBOX_DEFAULT
	release
	end

J_SecretBase_EventScript_Trainer3DeclineBattle::
	special DeclinedSecretBaseBattle
	setvar 32781, 0
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
	goto_if_unset 10387, J_SecretBase_EventScript_Trainer4PreChampion
	goto_if_eq 32781, 1, J_SecretBase_EventScript_Trainer4PostBattle
	msgbox J_SecretBase_Text_Trainer4Intro, MSGBOX_YESNO
	goto_if_eq 32781, NO, J_SecretBase_EventScript_Trainer4DeclineBattle
	setvar 32781, 1
	special SetBattledOwnerFromResult
	call J_Common_EventScript_SaveGame
	goto_if_eq 32781, 0, J_SecretBase_EventScript_Trainer4DeclineBattle
	msgbox J_SecretBase_Text_Trainer4AcceptBattle, MSGBOX_DEFAULT
	goto J_SecretBase_EventScript_BattleTrainer
	end

J_SecretBase_EventScript_Trainer4PreChampion::
	msgbox J_SecretBase_Text_Trainer4PreChampion, MSGBOX_DEFAULT
	release
	end

J_SecretBase_EventScript_Trainer4DeclineBattle::
	special DeclinedSecretBaseBattle
	setvar 32781, 0
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
	goto_if_unset 10387, J_SecretBase_EventScript_Trainer5PreChampion
	goto_if_eq 32781, 1, J_SecretBase_EventScript_Trainer5PostBattle
	msgbox J_SecretBase_Text_Trainer5Intro, MSGBOX_YESNO
	goto_if_eq 32781, NO, J_SecretBase_EventScript_Trainer5DeclineBattle
	setvar 32781, 1
	special SetBattledOwnerFromResult
	call J_Common_EventScript_SaveGame
	goto_if_eq 32781, 0, J_SecretBase_EventScript_Trainer5DeclineBattle
	msgbox J_SecretBase_Text_Trainer5AcceptBattle, MSGBOX_DEFAULT
	goto J_SecretBase_EventScript_BattleTrainer
	end

J_SecretBase_EventScript_Trainer5PreChampion::
	msgbox J_SecretBase_Text_Trainer5PreChampion, MSGBOX_DEFAULT
	release
	end

J_SecretBase_EventScript_Trainer5DeclineBattle::
	special DeclinedSecretBaseBattle
	setvar 32781, 0
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
	goto_if_unset 10387, J_SecretBase_EventScript_Trainer6PreChampion
	goto_if_eq 32781, 1, J_SecretBase_EventScript_Trainer6PostBattle
	msgbox J_SecretBase_Text_Trainer6Intro, MSGBOX_YESNO
	goto_if_eq 32781, NO, J_SecretBase_EventScript_Trainer6DeclineBattle
	setvar 32781, 1
	special SetBattledOwnerFromResult
	call J_Common_EventScript_SaveGame
	goto_if_eq 32781, 0, J_SecretBase_EventScript_Trainer6DeclineBattle
	msgbox J_SecretBase_Text_Trainer6AcceptBattle, MSGBOX_DEFAULT
	goto J_SecretBase_EventScript_BattleTrainer
	end

J_SecretBase_EventScript_Trainer6PreChampion::
	msgbox J_SecretBase_Text_Trainer6PreChampion, MSGBOX_DEFAULT
	release
	end

J_SecretBase_EventScript_Trainer6DeclineBattle::
	special DeclinedSecretBaseBattle
	setvar 32781, 0
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
	goto_if_unset 10387, J_SecretBase_EventScript_Trainer7PreChampion
	goto_if_eq 32781, 1, J_SecretBase_EventScript_Trainer7PostBattle
	msgbox J_SecretBase_Text_Trainer7Intro, MSGBOX_YESNO
	goto_if_eq 32781, NO, J_SecretBase_EventScript_Trainer7DeclineBattle
	setvar 32781, 1
	special SetBattledOwnerFromResult
	call J_Common_EventScript_SaveGame
	goto_if_eq 32781, 0, J_SecretBase_EventScript_Trainer7DeclineBattle
	msgbox J_SecretBase_Text_Trainer7AcceptBattle, MSGBOX_DEFAULT
	goto J_SecretBase_EventScript_BattleTrainer
	end

J_SecretBase_EventScript_Trainer7PreChampion::
	msgbox J_SecretBase_Text_Trainer7PreChampion, MSGBOX_DEFAULT
	release
	end

J_SecretBase_EventScript_Trainer7DeclineBattle::
	special DeclinedSecretBaseBattle
	setvar 32781, 0
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
	goto_if_unset 10387, J_SecretBase_EventScript_Trainer8PreChampion
	goto_if_eq 32781, 1, J_SecretBase_EventScript_Trainer8PostBattle
	msgbox J_SecretBase_Text_Trainer8Intro, MSGBOX_YESNO
	goto_if_eq 32781, NO, J_SecretBase_EventScript_Trainer8DeclineBattle
	setvar 32781, 1
	special SetBattledOwnerFromResult
	call J_Common_EventScript_SaveGame
	goto_if_eq 32781, 0, J_SecretBase_EventScript_Trainer8DeclineBattle
	msgbox J_SecretBase_Text_Trainer8AcceptBattle, MSGBOX_DEFAULT
	goto J_SecretBase_EventScript_BattleTrainer
	end

J_SecretBase_EventScript_Trainer8PreChampion::
	msgbox J_SecretBase_Text_Trainer8PreChampion, MSGBOX_DEFAULT
	release
	end

J_SecretBase_EventScript_Trainer8DeclineBattle::
	special DeclinedSecretBaseBattle
	setvar 32781, 0
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
	goto_if_unset 10387, J_SecretBase_EventScript_Trainer9PreChampion
	goto_if_eq 32781, 1, J_SecretBase_EventScript_Trainer9PostBattle
	msgbox J_SecretBase_Text_Trainer9Intro, MSGBOX_YESNO
	goto_if_eq 32781, NO, J_SecretBase_EventScript_Trainer9DeclineBattle
	setvar 32781, 1
	special SetBattledOwnerFromResult
	call J_Common_EventScript_SaveGame
	goto_if_eq 32781, 0, J_SecretBase_EventScript_Trainer9DeclineBattle
	msgbox J_SecretBase_Text_Trainer9AcceptBattle, MSGBOX_DEFAULT
	goto J_SecretBase_EventScript_BattleTrainer
	end

J_SecretBase_EventScript_Trainer9PreChampion::
	msgbox J_SecretBase_Text_Trainer9PreChampion, MSGBOX_DEFAULT
	release
	end

J_SecretBase_EventScript_Trainer9DeclineBattle::
	special DeclinedSecretBaseBattle
	setvar 32781, 0
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
	setvar 32772, 1
	setvar 32773, 0
	special DoSpecialTrainerBattle
	waitstate
	call_if_eq 32781, 3, J_SecretBase_EventScript_DrewSecretBaseBattle
	call_if_eq 32781, 1, J_SecretBase_EventScript_WonSecretBaseBattle
	call_if_eq 32781, 2, J_SecretBase_EventScript_LostSecretBaseBattle
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

