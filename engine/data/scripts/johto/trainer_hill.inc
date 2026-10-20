@ Johto (data/scripts/trainer_hill.inc), as built into the FireRed game.

J_TrainerHill_OnResume:
	setvar 16386, 0
	trainerhill_resumetimer
	frontier_get 5
	goto_if_eq 32781, 2, J_TrainerHill_1F_EventScript_Lost
	goto_if_eq 32781, 3, J_TrainerHill_1F_EventScript_Lost
	goto_if_eq 32781, 9, J_TrainerHill_1F_EventScript_Lost
	end

J_TrainerHill_OnWarp:
	map_script_2 16387, 0, J_TrainerHill_1F_EventScript_DummyOnWarp
	.2byte 0

J_TrainerHill_1F_EventScript_DummyOnWarp::
	setvar 16387, 1

	end

J_TrainerHill_OnFrame:
	map_script_2 16386, 0, J_TrainerHill_1F_EventScript_DummyWarpToEntranceCounter
	map_script_2 16385, 1, J_TrainerHill_EventScript_WarpToEntranceCounter
	.2byte 0

J_EventScript_TrainerHillTimer::
	lockall
	trainerhill_gettime
	msgbox J_TrainerHill_Entrance_Text_ChallengeTime, MSGBOX_DEFAULT
	releaseall
	end

J_TrainerHill_1F_EventScript_DummyWarpToEntranceCounter::
	setvar 16386, 1
	trainerhill_getusingereader
	goto_if_eq 32781, TRUE, J_TrainerHill_1F_EventScript_WarpSilentToEntranceCounter
	end

J_TrainerHill_1F_EventScript_WarpSilentToEntranceCounter::

	warpsilent MAP_TRAINER_HILL_ENTRANCE_HNS, 9, 6



	waitstate
	end

J_TrainerHill_1F_EventScript_Lost::
	trainerhill_settrainerflags
	trainerhill_lost
	setvar 16385, 1
	end

J_TrainerHill_EventScript_WarpToEntranceCounter::
	setvar 16385, 0

	warp MAP_TRAINER_HILL_ENTRANCE_HNS, 9, 6



	waitstate
	end

J_TrainerHill_1F_Movement_SetInvisible::
	set_invisible
	step_end

J_TrainerHill_EventScript_TrainerBattle::
	facilitytrainerbattle 8
	trainerhill_postbattletext
	waitmessage
	waitbuttonpress
	closemessage
	end

