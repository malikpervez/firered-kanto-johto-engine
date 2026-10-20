@ Johto (data/scripts/trainer_hill.inc), as built into the FireRed game.

J_TrainerHill_OnResume:
	setvar VAR_TEMP_2, 0
	trainerhill_resumetimer
	frontier_get FRONTIER_DATA_BATTLE_OUTCOME
	goto_if_eq VAR_RESULT, B_OUTCOME_LOST, J_TrainerHill_1F_EventScript_Lost
	goto_if_eq VAR_RESULT, B_OUTCOME_DREW, J_TrainerHill_1F_EventScript_Lost
	goto_if_eq VAR_RESULT, B_OUTCOME_FORFEITED, J_TrainerHill_1F_EventScript_Lost
	end

J_TrainerHill_OnWarp:
	map_script_2 VAR_TEMP_3, 0, J_TrainerHill_1F_EventScript_DummyOnWarp
	.2byte 0

J_TrainerHill_1F_EventScript_DummyOnWarp::
	setvar VAR_TEMP_3, 1

	end

J_TrainerHill_OnFrame:
	map_script_2 VAR_TEMP_2, 0, J_TrainerHill_1F_EventScript_DummyWarpToEntranceCounter
	map_script_2 VAR_TEMP_1, 1, J_TrainerHill_EventScript_WarpToEntranceCounter
	.2byte 0

J_EventScript_TrainerHillTimer::
	lockall
	trainerhill_gettime
	msgbox J_TrainerHill_Entrance_Text_ChallengeTime, MSGBOX_DEFAULT
	releaseall
	end

J_TrainerHill_1F_EventScript_DummyWarpToEntranceCounter::
	setvar VAR_TEMP_2, 1
	trainerhill_getusingereader
	goto_if_eq VAR_RESULT, TRUE, J_TrainerHill_1F_EventScript_WarpSilentToEntranceCounter
	end

J_TrainerHill_1F_EventScript_WarpSilentToEntranceCounter::

	warpsilent MAP_TRAINER_HILL_ENTRANCE_HNS, 9, 6



	waitstate
	end

J_TrainerHill_1F_EventScript_Lost::
	trainerhill_settrainerflags
	trainerhill_lost
	setvar VAR_TEMP_1, 1
	end

J_TrainerHill_EventScript_WarpToEntranceCounter::
	setvar VAR_TEMP_1, 0

	warp MAP_TRAINER_HILL_ENTRANCE_HNS, 9, 6



	waitstate
	end

J_TrainerHill_1F_Movement_SetInvisible::
	set_invisible
	step_end

J_TrainerHill_EventScript_TrainerBattle::
	facilitytrainerbattle FACILITY_BATTLE_TRAINER_HILL
	trainerhill_postbattletext
	waitmessage
	waitbuttonpress
	closemessage
	end

