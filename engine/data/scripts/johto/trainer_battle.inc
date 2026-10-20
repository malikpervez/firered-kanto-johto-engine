@ Johto (data/scripts/trainer_battle.inc), as built into the FireRed game.

J_EventScript_StartTrainerApproach::
	selectapproachingtrainer
	lockfortrainer

J_EventScript_TrainerApproach::
	special PlayTrainerEncounterMusic
	special DoTrainerApproach
	waitstate
	goto J_EventScript_ShowTrainerIntroMsg

J_EventScript_TryDoNormalTrainerBattle::
	lock
	faceplayer
	setflag 16389
	applymovement 32783, J_Movement_RevealTrainer
	waitmovement 0
	clearflag 16389
	specialvar 32781, GetTrainerFlag
	goto_if_ne 32781, FALSE, J_EventScript_NoNormalTrainerBattle
	special PlayTrainerEncounterMusic
	special SetTrainerFacingDirection
	goto J_EventScript_ShowTrainerIntroMsg

J_EventScript_NoNormalTrainerBattle::
	gotopostbattlescript

J_EventScript_TryDoDoubleTrainerBattle::
	lock
	faceplayer
	call J_EventScript_RevealTrainer
	specialvar 32781, GetTrainerFlag
	goto_if_ne 32781, FALSE, J_EventScript_NoDoubleTrainerBattle
	special HasEnoughMonsForDoubleBattle
	goto_if_ne 32781, 0, J_EventScript_NotEnoughMonsForDoubleBattle
	special PlayTrainerEncounterMusic
	special SetTrainerFacingDirection
	goto J_EventScript_ShowTrainerIntroMsg

J_EventScript_NotEnoughMonsForDoubleBattle::
	special ShowTrainerCantBattleSpeech
	waitmessage
	waitbuttonpress
	release
	end

J_EventScript_NoDoubleTrainerBattle::
	gotopostbattlescript

J_EventScript_DoNoIntroTrainerBattle::
	setflag 16389
	applymovement 32783, J_Movement_RevealTrainer
	waitmovement 0
	clearflag 16389
	special PlayTrainerEncounterMusic
	dotrainerbattle
	gotopostbattlescript

J_EventScript_TryDoRematchBattle::
	call J_EventScript_RevealTrainer
	specialvar 32781, IsTrainerReadyForRematch
	goto_if_eq 32781, FALSE, J_EventScript_NoRematchTrainerBattle
	special PlayTrainerEncounterMusic
	special SetTrainerFacingDirection
	special ShowTrainerIntroSpeech
	waitmessage
	waitbuttonpress
	special BattleSetup_StartRematchBattle
	waitstate
	releaseall
	end

J_EventScript_NoRematchTrainerBattle::
	gotopostbattlescript

J_EventScript_TryDoDoubleRematchBattle::
	specialvar 32781, IsTrainerReadyForRematch
	goto_if_eq 32781, FALSE, J_EventScript_NoDoubleRematchTrainerBattle
	special HasEnoughMonsForDoubleBattle
	goto_if_ne 32781, 0, J_EventScript_NotEnoughMonsForDoubleRematchBattle
	special PlayTrainerEncounterMusic
	special SetTrainerFacingDirection
	special ShowTrainerIntroSpeech
	waitmessage
	waitbuttonpress
	special BattleSetup_StartRematchBattle
	waitstate
	releaseall
	end

J_EventScript_NoDoubleRematchTrainerBattle::
	gotopostbattlescript

J_EventScript_NotEnoughMonsForDoubleRematchBattle::
	special ShowTrainerCantBattleSpeech
	waitmessage
	waitbuttonpress
	release
	end

J_EventScript_RevealTrainer::
	setflag 16389
	applymovement 32783, J_Movement_RevealTrainer
	waitmovement 0
	clearflag 16389
	return

J_Movement_RevealTrainer:
	reveal_trainer
	step_end

J_EventScript_ShowTrainerIntroMsg::
	special ShowTrainerIntroSpeech
	waitmessage
	waitbuttonpress
	special TryPrepareSecondApproachingTrainer
	goto_if_eq 32781, TRUE, J_EventScript_TrainerApproach
	goto J_EventScript_DoTrainerBattle

J_EventScript_DoTrainerBattle::
	dotrainerbattle

	specialvar 32781, GetTrainerBattleMode
	goto_if_eq 32781, 0, J_EventScript_EndTrainerBattle
	goto_if_eq 32781, 2, J_EventScript_EndTrainerBattle
	goto_if_eq 32781, 1, J_EventScript_EndTrainerBattle
	goto_if_eq 32781, 6, J_EventScript_EndTrainerBattle
	goto_if_eq 32781, 8, J_EventScript_EndTrainerBattle

J_EventScript_EndTrainerBattle::
	gotobeatenscript
	releaseall
	end

J_Std_MsgboxAutoclose::
	message NULL
	waitmessage
	waitbuttonpress
	release
	return

