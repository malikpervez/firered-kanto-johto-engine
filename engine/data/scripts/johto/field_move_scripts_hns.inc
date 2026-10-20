@ Johto (data/scripts/field_move_scripts_hns.inc), as built into the FireRed game.

J_EventScript_CutTree::
	lockall
	goto_if_set JOHTO_FLAG_BADGE10_GET, J_B4_CarriedFieldPermission_0
	goto_if_unset JOHTO_FLAG_RECEIVED_HM_CUT, J_EventScript_CheckTreeCantCut
	goto_if_unset JOHTO_FLAG_BADGE02_GET, J_EventScript_CheckTreeCantCut

J_B4_CarriedFieldPermission_0::
	checkpartymove MOVE_CUT
	goto_if_eq JOHTO_VAR_RESULT, 6, J_EventScript_CheckTreeCantCut
	bufferpartymonnick STR_VAR_1, 32781
	setfieldeffectargument 0, 32781
	buffermovename STR_VAR_2, MOVE_CUT


	msgbox J_Text_MonUsedFieldMove, MSGBOX_DEFAULT
	closemessage

J_EventScript_CutTreeCommon:
	isfollowerfieldmoveuser VAR_0x8004

J_EventScript_CutTreeDown::
	setflag JOHTO_FLAG_SAFE_FOLLOWER_MOVEMENT
	call_if_eq 32772, TRUE, J_EventScript_FollowerFieldMove
	applymovement JOHTO_VAR_LAST_TALKED, J_Movement_CutTreeDown
	playse SE_M_CUT
	waitmovement 0
	removeobject JOHTO_VAR_LAST_TALKED
	releaseall
	end

J_EventScript_UseCut::
	lockall
	goto J_EventScript_CutTreeCommon

J_Movement_CutTreeDown:
	cut_tree
	step_end

J_EventScript_CheckTreeCantCut::
	msgbox J_Text_CantCut, MSGBOX_DEFAULT
	releaseall
	end

J_EventScript_CancelCut::
	closemessage
	releaseall
	end

J_Text_WantToCut:
	.string "This tree looks like it can be\n"
	.string "CUT down!\p"
	.string "Would you like to CUT it?$"

J_Text_MonUsedFieldMove:
	.string "{STR_VAR_1} used {STR_VAR_2}!$"

J_Text_CantCut:
	.string "This tree looks like it can be\n"
	.string "CUT down!$"

J_EventScript_UseRockSmash::
	lockall
	goto J_EventScript_RockSmashCommon

J_EventScript_RockSmash::
	lockall
	checkpartymove MOVE_ROCK_SMASH
	goto_if_set JOHTO_FLAG_BADGE14_GET, J_B4_CarriedFieldPermission_1
	goto_if_unset JOHTO_FLAG_BADGE01_GET, J_EventScript_CantSmashRock
	goto_if_unset JOHTO_FLAG_RECEIVED_HM_ROCK_SMASH, J_EventScript_CantSmashRock

J_B4_CarriedFieldPermission_1::
	goto_if_eq JOHTO_VAR_RESULT, 6, J_EventScript_CantSmashRock
	bufferpartymonnick STR_VAR_1, 32781
	setfieldeffectargument 0, 32781
	bufferpartymonnick STR_VAR_1, 32781
	buffermovename STR_VAR_2, MOVE_ROCK_SMASH


	msgbox J_Text_MonUsedFieldMove, MSGBOX_DEFAULT
	closemessage

J_EventScript_RockSmashCommon:

	isfollowerfieldmoveuser VAR_0x8004

J_EventScript_SmashRock::
	setflag JOHTO_FLAG_SAFE_FOLLOWER_MOVEMENT
	call_if_eq 32772, TRUE, J_EventScript_FollowerFieldMove
	applymovement JOHTO_VAR_LAST_TALKED, J_Movement_SmashRock
	playse SE_M_ROCK_THROW
	waitmovement 0
	removeobject JOHTO_VAR_LAST_TALKED
	specialvar JOHTO_VAR_RESULT, TryUpdateRusturfTunnelState
	goto_if_eq JOHTO_VAR_RESULT, TRUE, J_EventScript_EndSmash
	special RockSmashWildEncounter
	goto_if_eq JOHTO_VAR_RESULT, FALSE, J_EventScript_EndSmash
	waitstate
	random 20
	call_if_eq JOHTO_VAR_RESULT, 1, J_EventScript_RockSmashHeartscale
	call_if_eq JOHTO_VAR_RESULT, 2, J_EventScript_RockSmashBlueShard
	call_if_eq JOHTO_VAR_RESULT, 3, J_EventScript_RockSmashRedShard
	call_if_eq JOHTO_VAR_RESULT, 4, J_EventScript_RockSmashGreenShard
	call_if_eq JOHTO_VAR_RESULT, 5, J_EventScript_RockSmashYellowShard
	releaseall
	end

J_EventScript_Headbutt::
	lockall
	goto_if_unset JOHTO_FLAG_GET_HEADBUTT, J_EventScript_CantHeadbuttTree
	checkpartymove MOVE_HEADBUTT
	goto_if_eq VAR_RESULT, PARTY_SIZE, J_EventScript_CantHeadbuttTree
	bufferpartymonnick STR_VAR_1, VAR_RESULT
	setfieldeffectargument 0, VAR_RESULT
	msgbox J_Text_MonUsedHeadbutt, MSGBOX_DEFAULT
	closemessage

J_EventScript_HeadbuttCommon:

	isfollowerfieldmoveuser VAR_0x8004

J_EventScript_HeadbuttTree::
	setflag JOHTO_FLAG_SAFE_FOLLOWER_MOVEMENT
	call_if_eq 32772, TRUE, J_EventScript_FollowerFieldMove
	applymovement JOHTO_VAR_LAST_TALKED, J_Movement_HeadbuttTree
	playse SE_M_HEADBUTT
	waitmovement 0
	special RockSmashWildEncounter
	goto J_EventScript_EndHeadbutt
	waitstate
	releaseall
	end

J_Movement_HeadbuttTree:
	rock_smash_break
	step_end

J_EventScript_CantHeadbuttTree::
	msgbox J_Text_CantHeadbutt, MSGBOX_DEFAULT
	releaseall
	end

J_EventScript_CancelHeadbutt::
	closemessage
	releaseall
	end

J_EventScript_EndHeadbutt::
	releaseall
	end

J_Text_MonUsedHeadbutt::
	.string "{STR_VAR_1} used HEADBUTT!$"

J_EventScript_FollowerFieldMove:
	getdirectiontoface VAR_0x8005, OBJ_EVENT_ID_FOLLOWER, OBJ_EVENT_ID_PLAYER
	specialvar VAR_0x8006, GetPlayerFacingDirection
	goto_if_eq VAR_0x8005, DIR_NONE, J_EventScript_FollowerFieldMoveEnd

	call J_EventScript_FollowerSwap

	switch VAR_0x8006
	case DIR_NORTH, J_EventScript_FollowerJumpNorth
	case DIR_EAST, J_EventScript_FollowerJumpEast
	case DIR_SOUTH, J_EventScript_FollowerJumpSouth
	case DIR_WEST, J_EventScript_FollowerJumpWest

J_EventScript_FollowerFieldMoveEnd:
	return

J_EventScript_FollowerSwap:
	switch VAR_0x8005
	case DIR_NORTH, J_EventScript_FollowerMoveNorth
	case DIR_EAST, J_EventScript_FollowerMoveEast
	case DIR_SOUTH, J_EventScript_FollowerMoveSouth
	case DIR_WEST, J_EventScript_FollowerMoveWest
	return

J_EventScript_FollowerMoveNorth:
	applymovement OBJ_EVENT_ID_FOLLOWER, J_Movement_WalkUp
	applymovement OBJ_EVENT_ID_PLAYER, J_Movement_WalkDown
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, J_Common_Movement_FaceUp
	waitmovement 0
	return

J_EventScript_FollowerMoveEast:
	applymovement OBJ_EVENT_ID_FOLLOWER, J_Movement_WalkRight
	applymovement OBJ_EVENT_ID_PLAYER, J_Movement_WalkLeft
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, J_Common_Movement_FaceRight
	waitmovement 0
	return

J_EventScript_FollowerMoveSouth:
	applymovement OBJ_EVENT_ID_FOLLOWER, J_Movement_WalkDown
	applymovement OBJ_EVENT_ID_PLAYER, J_Movement_WalkUp
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, J_Common_Movement_FaceDown
	waitmovement 0
	return

J_EventScript_FollowerMoveWest:
	applymovement OBJ_EVENT_ID_FOLLOWER, J_Movement_WalkLeft
	applymovement OBJ_EVENT_ID_PLAYER, J_Movement_WalkRight
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, J_Common_Movement_FaceLeft
	waitmovement 0
	return

J_EventScript_FollowerJumpNorth:
	applymovement OBJ_EVENT_ID_FOLLOWER, J_Movement_JumpUp
	waitmovement 0
	return

J_EventScript_FollowerJumpEast:
	applymovement OBJ_EVENT_ID_FOLLOWER, J_Movement_JumpRight
	waitmovement 0
	return

J_EventScript_FollowerJumpSouth:
	applymovement OBJ_EVENT_ID_FOLLOWER, J_Movement_JumpDown
	waitmovement 0
	return

J_EventScript_FollowerJumpWest:
	applymovement OBJ_EVENT_ID_FOLLOWER, J_Movement_JumpLeft
	waitmovement 0
	return

J_EventScript_EndSmash::
	random 20
	call_if_eq VAR_RESULT, 1, J_EventScript_RockSmashHeartscale
	call_if_eq VAR_RESULT, 2, J_EventScript_RockSmashBlueShard
	call_if_eq VAR_RESULT, 3, J_EventScript_RockSmashRedShard
	call_if_eq VAR_RESULT, 4, J_EventScript_RockSmashGreenShard
	call_if_eq VAR_RESULT, 5, J_EventScript_RockSmashYellowShard
	releaseall
	end

J_EventScript_RockSmashHeartscale::
	giveitem ITEM_HEART_SCALE
	return

J_EventScript_RockSmashBlueShard::
	giveitem ITEM_BLUE_SHARD
	return

J_EventScript_RockSmashRedShard::
	giveitem ITEM_RED_SHARD
	return

J_EventScript_RockSmashGreenShard::
	giveitem ITEM_GREEN_SHARD
	return

J_EventScript_RockSmashYellowShard::
	giveitem ITEM_YELLOW_SHARD
	return

J_Movement_WalkUp:
	walk_up
	step_end

J_Movement_JumpUp:
	jump_in_place_up
	step_end

J_Movement_WalkRight:
	walk_right
	step_end

J_Movement_JumpRight:
	jump_in_place_right
	step_end

J_Movement_WalkDown:
	walk_down
	step_end

J_Movement_JumpDown:
	jump_in_place_down
	step_end

J_Movement_WalkLeft:
	walk_left
	step_end

J_Movement_JumpLeft:
	jump_in_place_left
	step_end

J_Movement_SmashRock:
	rock_smash_break
	step_end

J_EventScript_CantSmashRock::
	msgbox J_Text_CantSmash, MSGBOX_DEFAULT
	releaseall
	end

J_EventScript_CancelSmash::
	closemessage
	releaseall
	end

J_Text_WantToSmash:
	.string "This rock appears to be breakable.\n"
	.string "Would you like to use ROCK SMASH?$"

J_Text_CantSmash:
	.string "It's a rugged rock, but a POKéMON\n"
	.string "may be able to smash it.$"

J_Text_WantToHeadbutt:
	.string "This tree may house POKéMON.\n"
	.string "Would you like to use HEADBUTT?$"

J_Text_CantHeadbutt:
	.string "It's a small tree, but a wild\n"
	.string "POKéMON may be living within.$"

J_EventScript_StrengthBoulder::
	lockall
	goto_if_set JOHTO_FLAG_BADGE12_GET, J_B4_CarriedFieldPermission_2
	goto_if_unset JOHTO_FLAG_BADGE03_GET, J_EventScript_CantStrength

J_B4_CarriedFieldPermission_2::
	checkitem 685
	goto_if_eq JOHTO_VAR_RESULT, FALSE, J_EventScript_CantStrength
	goto_if_set JOHTO_FLAG_SYS_USE_STRENGTH, J_EventScript_CheckActivatedBoulder
	checkpartymove MOVE_STRENGTH
	goto_if_eq JOHTO_VAR_RESULT, 6, J_EventScript_CantStrength
	bufferpartymonnick STR_VAR_1, 32781
	setfieldeffectargument 0, 32781





	goto J_EventScript_ActivateStrength
	end

J_EventScript_UseStrength::
	lockall


	goto J_EventScript_ActivateStrength
	end

J_EventScript_ActivateStrength::
	setflag FLAG_SYS_USE_STRENGTH
	msgbox J_Text_MonUsedStrength, MSGBOX_DEFAULT
	releaseall
	end

J_EventScript_CantStrength::
	msgbox J_Text_CantStrength, MSGBOX_DEFAULT
	releaseall
	end

J_EventScript_CheckActivatedBoulder::
	msgbox J_Text_StrengthActivated, MSGBOX_DEFAULT
	releaseall
	end

J_EventScript_CancelStrength::
	closemessage
	releaseall
	end

J_Text_WantToStrength:
	.string "It's a big boulder, but a POKéMON\n"
	.string "may be able to push it aside.\p"
	.string "Would you like to use STRENGTH?$"

J_Text_MonUsedStrength:
	.string "{STR_VAR_1} used STRENGTH!$"

J_Text_CantStrength:
	.string "It's a big boulder, but a POKéMON\n"
	.string "may be able to push it aside.$"

J_Text_StrengthActivated:
	.string "STRENGTH made it possible to move\n"
	.string "boulders around.$"

J_EventScript_UseWaterfall::
	lockall
	goto_if_set JOHTO_FLAG_BADGE15_GET, J_B4_CarriedFieldPermission_3
	goto_if_unset JOHTO_FLAG_BADGE08_GET, J_EventScript_CantWaterfall

J_B4_CarriedFieldPermission_3::
	checkpartymove MOVE_WATERFALL
	goto_if_eq JOHTO_VAR_RESULT, 6, J_EventScript_CantWaterfall
	bufferpartymonnick STR_VAR_1, 32781
	setfieldeffectargument 0, 32781


	msgbox J_Text_MonUsedWaterfall, MSGBOX_DEFAULT
	dofieldeffect 43
	goto J_EventScript_EndWaterfall

J_EventScript_CannotUseWaterfall::
	lockall

J_EventScript_CantWaterfall::
	msgbox J_Text_CantWaterfall, MSGBOX_DEFAULT

J_EventScript_EndWaterfall::
	releaseall
	end

J_Text_CantWaterfall:
	.string "A wall of water is crashing down with\n"
	.string "a mighty roar.$"

J_Text_WantToWaterfall:
	.string "It's a large waterfall.\n"
	.string "Would you like to use WATERFALL?$"

J_Text_MonUsedWaterfall:
	.string "{STR_VAR_1} used WATERFALL.$"

J_EventScript_UseDive::
	lockall
	checkpartymove MOVE_DIVE
	goto_if_eq VAR_RESULT, PARTY_SIZE, J_EventScript_CantDive
	bufferpartymonnick STR_VAR_1, VAR_RESULT
	setfieldeffectargument 0, VAR_RESULT
	setfieldeffectargument 1, 1
	msgbox J_Text_WantToDive, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, J_EventScript_EndDive
	msgbox J_Text_MonUsedDive, MSGBOX_DEFAULT
	dofieldeffect FLDEFF_USE_DIVE
	goto J_EventScript_EndDive
	end

J_EventScript_CantDive::
	msgbox J_Text_CantDive, MSGBOX_DEFAULT
	releaseall
	end

J_EventScript_EndDive::
	releaseall
	end

J_EventScript_UseDiveUnderwater::
	lockall
	checkpartymove MOVE_DIVE
	goto_if_eq VAR_RESULT, PARTY_SIZE, J_EventScript_CantSurface
	bufferpartymonnick STR_VAR_1, VAR_RESULT
	setfieldeffectargument 0, VAR_RESULT
	setfieldeffectargument 1, 1
	msgbox J_Text_WantToSurface, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, J_EventScript_EndSurface
	msgbox J_Text_MonUsedDive, MSGBOX_DEFAULT
	dofieldeffect FLDEFF_USE_DIVE
	goto J_EventScript_EndSurface
	end

J_EventScript_CantSurface::
	lockall
	msgbox J_Text_CantSurface, MSGBOX_DEFAULT
	goto J_EventScript_EndSurface
	end

J_EventScript_EndSurface::
	releaseall
	end

J_EventScript_Whirlpool::
	lockall
	goto_if_unset JOHTO_FLAG_BADGE07_GET, J_EventScript_CantWhirlpool


	playse SE_M_WATERFALL
	goto_if_eq VAR_FACING, DIR_NORTH, J_EventScript_WhirlpoolGoNorth
	goto_if_eq VAR_FACING, DIR_SOUTH, J_EventScript_WhirlpoolGoSouth
	goto_if_eq VAR_FACING, DIR_EAST, J_EventScript_WhirlpoolGoEast
	goto_if_eq VAR_FACING, DIR_WEST, J_EventScript_WhirlpoolGoWest
	releaseall
	end

J_EventScript_WhirlpoolGoNorth::
	applymovement OBJ_EVENT_ID_PLAYER, J_Movement_WhirlpoolNorth
	waitmovement 0
	releaseall
	end

J_EventScript_WhirlpoolGoSouth::
	applymovement OBJ_EVENT_ID_PLAYER, J_Movement_WhirlpoolSouth
	waitmovement 0
	releaseall
	end

J_EventScript_WhirlpoolGoEast::
	applymovement OBJ_EVENT_ID_PLAYER, J_Movement_WhirlpoolEast
	waitmovement 0
	releaseall
	end

J_EventScript_WhirlpoolGoWest::
	applymovement OBJ_EVENT_ID_PLAYER, J_Movement_WhirlpoolWest
	waitmovement 0
	releaseall
	end

J_EventScript_CantWhirlpool::
	msgbox J_Text_CantWhirlpool, MSGBOX_DEFAULT
	closemessage
	releaseall
	end

J_Movement_WhirlpoolNorth:
	slide_up
	slide_up
	slide_up
	step_end

J_Movement_WhirlpoolSouth:
	slide_down
	slide_down
	slide_down
	step_end

J_Movement_WhirlpoolEast:
	slide_right
	slide_right
	slide_right
	step_end

J_Movement_WhirlpoolWest:
	slide_left
	slide_left
	slide_left
	step_end

J_Text_CantWhirlpool:
	.string "The water is swirling and spinning\n"
	.string "around with a mighty roar.$"

J_Text_CantDive:
	.string "The sea is deep here. A POKéMON\n"
	.string "may be able to go underwater.$"

J_Text_WantToDive:
	.string "The sea is deep here.\n"
	.string "Would you like to use DIVE?$"

J_Text_MonUsedDive:
	.string "{STR_VAR_1} used WHIRLPOOL.$"

J_Text_CantSurface:
	.string "Light is filtering down from above.\n"
	.string "A POKéMON may be able to surface.$"

J_Text_WantToSurface:
	.string "Light is filtering down from above.\n"
	.string "Would you like to use DIVE?$"

J_EventScript_FailSweetScent::
	msgbox J_Text_FailSweetScent, MSGBOX_SIGN
	end

J_Text_FailSweetScent:
	.string "Looks like there's nothing here…$"

J_EventScript_DigCommon:
	isfollowerfieldmoveuser VAR_0x8004
	setfieldeffectargument 3, VAR_0x8004
	dofieldeffect FLDEFF_USE_DIG
	waitstate

J_EventScript_DigSealedChamber::
	setflag JOHTO_FLAG_SAFE_FOLLOWER_MOVEMENT
	call_if_eq 32772, TRUE, J_EventScript_FollowerFieldMove
	callnative DoBrailleDigEffect
	releaseall
	end

J_EventScript_UseDig::
	lockall
	goto J_EventScript_DigCommon

J_EventScript_CutGrassCommon:
	isfollowerfieldmoveuser VAR_0x8004
	setfieldeffectargument 3, VAR_0x8004
	dofieldeffect FLDEFF_USE_CUT_ON_GRASS
	waitstate

J_EventScript_UseCutGrass::
	lockall
	goto J_EventScript_CutGrassCommon

J_EventScript_UseDefog::
	lockall
	bufferpartymonnick STR_VAR_1, VAR_RESULT
	buffermovename STR_VAR_2, MOVE_DEFOG
	msgbox J_Text_MonUsedFieldMove, MSGBOX_DEFAULT
	closemessage
	isfollowerfieldmoveuser VAR_0x8004
	setfieldeffectargument 3, VAR_0x8004
	setflag FLAG_SAFE_FOLLOWER_MOVEMENT
	call_if_eq VAR_0x8004, TRUE, J_EventScript_FollowerFieldMove
	waitmovement 0
	setfieldeffectargument 0, VAR_RESULT
	dofieldeffect FLDEFF_DEFOG
	waitstate
	releaseall
	end

J_EventScript_UseRockClimb::
	lockall
	checkfieldmove FIELD_MOVE_ROCK_CLIMB
	goto_if_eq VAR_RESULT, PARTY_SIZE, J_EventScript_CantRockClimb
	bufferpartymonnick STR_VAR_1, VAR_RESULT
	setfieldeffectargument 0, VAR_RESULT
	msgbox J_Text_WantToRockClimb, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, J_EventScript_EndRockClimb
	msgbox J_Text_MonUsedRockClimb, MSGBOX_DEFAULT
	closemessage
	dofieldeffect FLDEFF_USE_ROCK_CLIMB
	waitstate
	goto J_EventScript_EndRockClimb
	end

J_EventScript_CantRockClimb::
	msgbox J_Text_CantRockClimb, MSGBOX_DEFAULT

J_EventScript_EndRockClimb::
	releaseall
	end

J_Text_WantToRockClimb:
	.string "The cliff is steep.\n"
	.string "Would you like to use Rock Climb?$"

J_Text_MonUsedRockClimb:
	.string "{STR_VAR_1} used Rock Climb!$"

J_Text_CantRockClimb:
	.string "The cliff is steep.\n"
	.string "A Pokémon may be able to climb it.$"

J_SetTimeEncounters::
	callnative SetTimeBasedEncounters
	return

