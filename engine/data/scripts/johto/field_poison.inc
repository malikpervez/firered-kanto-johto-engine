@ Johto (data/scripts/field_poison.inc), as built into the FireRed game.

J_EventScript_FieldPoison::
	lockall
	special TryFieldPoisonWhiteOut
	waitstate
	goto_if_eq VAR_RESULT, FLDPSN_WHITEOUT, J_EventScript_FieldWhiteOut
	goto_if_eq VAR_RESULT, FLDPSN_FRONTIER_WHITEOUT, J_EventScript_FrontierFieldWhiteOut
	releaseall
	end

J_EventScript_FieldWhiteOut::
	goto_if_set JOHTO_FLAG_SYS_BUG_CONTEST_MODE, J_BugContest_EventScript_WhiteOut
	message J_gText_PlayerWhitedOut
	waitmessage
	waitbuttonpress
	special Script_FadeOutMapMusic
	waitstate
	fadescreen FADE_TO_BLACK
	call_if_set FLAG_WHITEOUT_TO_LAVARIDGE, J_EventScript_SetRespawnLavaridgePkmnCenter
	special SetCB2WhiteOut
	waitstate
	end

J_EventScript_SetRespawnLavaridgePkmnCenter::
	setrespawn HEAL_LOCATION_LAVARIDGE_TOWN
	return

J_EventScript_FrontierFieldWhiteOut::
	message J_gText_PlayerWhitedOut
	waitmessage
	waitbuttonpress
	pike_inchallenge
	goto_if_eq VAR_RESULT, TRUE, J_BattleFrontier_BattlePike_EventScript_Retire
	pyramid_getlocation
	goto_if_eq VAR_RESULT, PYRAMID_LOCATION_FLOOR, BattleFrontier_BattlePyramid_EventScript_WarpToLobby_hnsLost_hns
	goto_if_eq VAR_RESULT, PYRAMID_LOCATION_TOP, BattleFrontier_BattlePyramid_EventScript_WarpToLobby_hnsLost_hns
	trainerhill_inchallenge
	goto_if_eq VAR_RESULT, TRUE, J_TrainerHill_1F_EventScript_Lost
	special Script_FadeOutMapMusic
	waitstate
	fadescreen FADE_TO_BLACK
	special SetCB2WhiteOut
	waitstate
	end

