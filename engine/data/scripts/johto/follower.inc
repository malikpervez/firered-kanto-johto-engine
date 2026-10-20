@ Johto (data/scripts/follower.inc), as built into the FireRed game.

J_gText_FollowerLovesYou::
	.string "{STR_VAR_1} i{SE_M_GRASSWHISTLE}regardin{SE_M_SANDSTORM}yo{SE_M_DIVE}with\nadoration!$"

J_gText_FollowerLostInThought::
	.string "{STR_VAR_1} seem{SE_M_GRASSWHISTLE}los{SE_M_SPIT_UP}i{SE_M_ATTRACT}thought.$"

J_gText_FollowerDefault::
	.string "ERRO{SE_M_MINIMIZE}404{SE_M_HEAT_WAVE}Scrip{SE_M_SPIT_UP}no{SE_M_SPIT_UP}found.$"

J_gText_WantsToFly::
	.string "{STR_VAR_1} look{SE_M_GRASSWHISTLE}u{SE_M_MORNING_SUN}a{SE_M_SPIT_UP}the\nsk{SE_M_YAWN}restlessly.\pWoul{SE_M_WATERFALL}yo{SE_M_DIVE}lik{SE_M_REVERSAL}t{SE_M_ATTRACT2}us{SE_M_REVERSAL}FLY?$"

J_EventScript_Follower::
	lock
	bufferlivemonnickname STR_VAR_1
	playfirstmoncry
	getfolloweraction

J_EventScript_FollowerEnd::
	waitfieldeffect 33
	release
	end

J_EventScript_FollowerLovesYou::
	applymovement 0xFE, J_ContestHall_Movement_Heart
	waitmovement 0xFE
	waitmoncry
	msgbox J_gText_FollowerLovesYou, MSGBOX_DEFAULT
	return

J_EventScript_FollowerGeneric::
	faceplayer

J_EventScript_FollowerGenericSkipFace:
	waitfieldeffect 33
	message 0x0
	waitmessage
	waitbuttonpress
	return

J_EventScript_FollowerJump::
	faceplayer
	applymovement 0xFE, J_FollowerSplashMovement
	waitmovement 0xFE
	waitfieldeffect 33
	message 0x0
	waitmessage
	waitbuttonpress
	return

J_EnterPokeballMovement::
	enter_pokeball
	step_end

J_FollowerSplashMovement::
	jump_in_place_down
	delay_4
	jump_in_place_down
	face_player
	step_end

J_FollowerShiverVerticalMovement:
	lock_facing_direction
	slide_left
	slide_right
	slide_right
	slide_left
	unlock_facing_direction
	step_end

J_FollowerShiverHorizontalMovement:
	lock_facing_direction
	slide_up
	slide_down
	slide_down
	slide_up
	unlock_facing_direction
	step_end

J_FollowerNostalgiaMovement:
	face_away_player
	lock_facing_direction
	jump_in_place_down
	jump_in_place_down
	jump_in_place_down
	unlock_facing_direction
	face_player
	lock_facing_direction
	jump_in_place_down
	unlock_facing_direction
	step_end

J_FollowerSkippingMovement:
	lock_facing_direction
	jump_in_place_down
	delay_4
	jump_in_place_down
	unlock_facing_direction
	step_end

J_FollowerJumpOnPlayerNorth:
	jump_up
	delay_4
	lock_facing_direction
	walk_fast_down
	unlock_facing_direction
	step_end

J_FollowerJumpOnPlayerSouth:
	jump_down
	delay_4
	lock_facing_direction
	walk_fast_up
	unlock_facing_direction
	step_end

J_FollowerJumpOnPlayerEast:
	jump_right
	delay_4
	lock_facing_direction
	walk_fast_left
	unlock_facing_direction
	step_end

J_FollowerJumpOnPlayerWest:
	jump_left
	delay_4
	lock_facing_direction
	walk_fast_right
	unlock_facing_direction
	step_end

J_FollowerCuddlingNorth:
	face_left
	lock_facing_direction
	walk_up
	walk_in_place_left
	walk_in_place_left
	unlock_facing_direction
	walk_down
	face_player
	step_end

J_FollowerCuddlingSouth:
	face_right
	lock_facing_direction
	walk_down
	walk_in_place_right
	walk_in_place_right
	unlock_facing_direction
	walk_up
	face_player
	step_end

J_FollowerCuddlingEast:
	face_down
	lock_facing_direction
	walk_right
	walk_in_place_down
	walk_in_place_down
	unlock_facing_direction
	walk_left
	face_player
	step_end

J_FollowerCuddlingWest:
	face_down
	lock_facing_direction
	walk_left
	walk_in_place_down
	walk_in_place_down
	unlock_facing_direction
	walk_right
	face_player
	step_end

J_FollowerGetCloserNorth:
	walk_up
	delay_16
	lock_facing_direction
	walk_down
	unlock_facing_direction
	step_end

J_FollowerGetCloserSouth:
	walk_down
	delay_16
	lock_facing_direction
	walk_up
	unlock_facing_direction
	step_end

J_FollowerGetCloserEast:
	walk_right
	delay_16
	lock_facing_direction
	walk_left
	unlock_facing_direction
	step_end

J_FollowerGetCloserWest:
	walk_left
	delay_16
	lock_facing_direction
	walk_right
	unlock_facing_direction
	step_end

J_FollowerPokeNorth:
	walk_faster_up
	delay_8
	lock_facing_direction
	walk_faster_down
	delay_4
	walk_faster_up
	delay_4
	walk_faster_down
	unlock_facing_direction
	step_end

J_FollowerPokeSouth:
	walk_faster_down
	delay_8
	lock_facing_direction
	walk_faster_up
	delay_4
	walk_faster_down
	delay_4
	walk_faster_up
	unlock_facing_direction
	step_end

J_FollowerPokeEast:
	walk_faster_right
	delay_8
	lock_facing_direction
	walk_faster_left
	delay_4
	walk_faster_right
	delay_4
	walk_faster_left
	unlock_facing_direction
	step_end

J_FollowerPokeWest:
	walk_faster_left
	delay_8
	lock_facing_direction
	walk_faster_right
	delay_4
	walk_faster_left
	delay_4
	walk_faster_right
	unlock_facing_direction
	step_end

J_FollowerLookAround:
	face_away_player
	delay_16
	delay_16
	face_left
	delay_16
	delay_16
	face_up
	delay_16
	delay_16
	face_down
	delay_16
	delay_16
	step_end

J_FollowerLookAway:
	face_away_player
	delay_16
	delay_16
	step_end

J_FollowerLookAwayBark:
	face_away_player
	lock_facing_direction
	jump_in_place_down
	jump_in_place_down
	unlock_facing_direction
	step_end

J_FollowerLookAwayPokeG:
	face_away_player
	lock_facing_direction
	walk_in_place_down
	walk_in_place_down
	walk_in_place_down
	unlock_facing_direction
	step_end

J_FollowerPokeGround:
	lock_facing_direction
	walk_in_place_down
	walk_in_place_down
	walk_in_place_down
	unlock_facing_direction
	step_end

J_FollowerStartled:
	face_away_player
	lock_facing_direction
	jump_in_place_down
	unlock_facing_direction
	face_player
	step_end

J_FollowerHopFast:
	jump_in_place_up
	jump_in_place_down
	jump_in_place_left
	jump_in_place_right
	face_player
	step_end

J_FollowerDizzy:
	walk_in_place_left
	walk_in_place_fast_right
	walk_in_place_slow_up
	walk_in_place_fast_down
	delay_4
	face_away_player
	step_end

J_FollowerLookAroundScared:
	face_up
	delay_16
	face_down
	delay_16
	face_left
	delay_16
	face_right
	delay_16
	face_up
	delay_16
	face_down
	delay_16
	face_left
	delay_16
	face_right
	delay_16
	face_player
	step_end

J_FollowerDance:
	lock_facing_direction
	jump_in_place_up
	unlock_facing_direction
	walk_in_place_fast_up
	walk_in_place_fast_left
	walk_in_place_fast_down
	walk_in_place_fast_right
	walk_in_place_fast_up
	walk_in_place_fast_left
	walk_in_place_fast_down
	walk_in_place_fast_right
	jump_in_place_up
	jump_in_place_down
	jump_in_place_up
	face_player
	step_end

J_EventScript_FollowerIsShivering::
	faceplayer
	compare 32780, DIR_NORTH
	call_if_eq J_ShiverVertical
	compare 32780, DIR_SOUTH
	call_if_eq J_ShiverVertical
	compare 32780, DIR_WEST
	call_if_eq J_ShiverHorizontal
	compare 32780, DIR_EAST
	call_if_eq J_ShiverHorizontal
	goto J_EventScript_FollowerGeneric

J_ShiverVertical:
	applymovement 0xFE, J_FollowerShiverVerticalMovement
	waitmovement 0xFE
	return

J_ShiverHorizontal:
	applymovement 0xFE, J_FollowerShiverHorizontalMovement
	waitmovement 0xFE
	return

J_EventScript_FollowerNostalgia::
	applymovement 0xFE, J_FollowerNostalgiaMovement
	waitmovement 0xFE
	goto J_EventScript_FollowerGeneric

J_EventScript_FollowerHopping::
	faceplayer
	applymovement 0xFE, J_FollowerSkippingMovement
	waitmovement 0xFE
	goto J_EventScript_FollowerGeneric

J_JumpOnN:
	applymovement 0xFE, J_FollowerJumpOnPlayerNorth
	waitmovement 0xFE
	return

J_JumpOnS:
	applymovement 0xFE, J_FollowerJumpOnPlayerSouth
	waitmovement 0xFE
	return

J_JumpOnE:
	applymovement 0xFE, J_FollowerJumpOnPlayerEast
	waitmovement 0xFE
	return

J_JumpOnW:
	applymovement 0xFE, J_FollowerJumpOnPlayerWest
	waitmovement 0xFE
	return

J_EventScript_FollowerJumpOnPlayer::
	faceplayer
	compare 32780, DIR_NORTH
	call_if_eq J_JumpOnS
	compare 32780, DIR_SOUTH
	call_if_eq J_JumpOnN
	compare 32780, DIR_WEST
	call_if_eq J_JumpOnE
	compare 32780, DIR_EAST
	call_if_eq J_JumpOnW
	goto J_EventScript_FollowerGeneric

J_CuddleN:
	applymovement 0xFE, J_FollowerCuddlingNorth
	waitmovement 0xFE
	return

J_CuddleS:
	applymovement 0xFE, J_FollowerCuddlingSouth
	waitmovement 0xFE
	return

J_CuddleE:
	applymovement 0xFE, J_FollowerCuddlingEast
	waitmovement 0xFE
	return

J_CuddleW:
	applymovement 0xFE, J_FollowerCuddlingWest
	waitmovement 0xFE
	return

J_EventScript_FollowerCuddling::
	faceplayer
	compare 32780, DIR_NORTH
	call_if_eq J_CuddleS
	compare 32780, DIR_SOUTH
	call_if_eq J_CuddleN
	compare 32780, DIR_WEST
	call_if_eq J_CuddleE
	compare 32780, DIR_EAST
	call_if_eq J_CuddleW
	goto J_EventScript_FollowerGeneric

J_ShCuddleN:
	applymovement 0xFE J_FollowerShiverVerticalMovement
	waitmovement 0xFE
	applymovement 0xFE J_FollowerCuddlingNorth
	waitmovement 0xFE
	return

J_ShCuddleS:
	applymovement 0xFE J_FollowerShiverVerticalMovement
	waitmovement 0xFE
	applymovement 0xFE J_FollowerCuddlingSouth
	waitmovement 0xFE
	return

J_ShCuddleE:
	applymovement 0xFE J_FollowerShiverHorizontalMovement
	waitmovement 0xFE
	applymovement 0xFE J_FollowerCuddlingEast
	waitmovement 0xFE
	return

J_ShCuddleW:
	applymovement 0xFE J_FollowerShiverHorizontalMovement
	waitmovement 0xFE
	applymovement 0xFE J_FollowerCuddlingWest
	waitmovement 0xFE
	return

J_EventScript_FollowerShiverCuddling::
	faceplayer
	compare 32780, DIR_NORTH
	call_if_eq J_ShCuddleS
	compare 32780, DIR_SOUTH
	call_if_eq J_ShCuddleN
	compare 32780, DIR_WEST
	call_if_eq J_ShCuddleE
	compare 32780, DIR_EAST
	call_if_eq J_ShCuddleW
	goto J_EventScript_FollowerGeneric

J_CreepCloserN:
	applymovement 0xFE J_FollowerGetCloserNorth
	waitmovement 0xFE
	return

J_CreepCloserS:
	applymovement 0xFE J_FollowerGetCloserSouth
	waitmovement 0xFE
	return

J_CreepCloserE:
	applymovement 0xFE J_FollowerGetCloserEast
	waitmovement 0xFE
	return

J_CreepCloserW:
	applymovement 0xFE J_FollowerGetCloserWest
	waitmovement 0xFE
	return

J_EventScript_FollowerGetCloser::
	faceplayer
	compare 32780, DIR_NORTH
	call_if_eq J_CreepCloserS
	compare 32780, DIR_SOUTH
	call_if_eq J_CreepCloserN
	compare 32780, DIR_WEST
	call_if_eq J_CreepCloserE
	compare 32780, DIR_EAST
	call_if_eq J_CreepCloserW
	goto J_EventScript_FollowerGeneric

J_PokePlayerN:
	applymovement 0xFE J_FollowerGetCloserNorth
	waitmovement 0xFE
	return

J_PokePlayerS:
	applymovement 0xFE J_FollowerGetCloserSouth
	waitmovement 0xFE
	return

J_PokePlayerE:
	applymovement 0xFE J_FollowerGetCloserEast
	waitmovement 0xFE
	return

J_PokePlayerW:
	applymovement 0xFE J_FollowerGetCloserWest
	waitmovement 0xFE
	return

J_EventScript_FollowerPokingPlayer::
	faceplayer
	compare 32780, DIR_NORTH
	call_if_eq J_PokePlayerS
	compare 32780, DIR_SOUTH
	call_if_eq J_PokePlayerN
	compare 32780, DIR_WEST
	call_if_eq J_PokePlayerE
	compare 32780, DIR_EAST
	call_if_eq J_PokePlayerW
	goto J_EventScript_FollowerGeneric

J_EventScript_FollowerLookAround::
	applymovement 0xFE J_FollowerLookAround
	waitmovement 0xFE
	goto J_EventScript_FollowerGeneric

J_EventScript_FollowerLookAway::
	applymovement 0xFE J_FollowerLookAway
	waitmovement 0xFE
	goto J_EventScript_FollowerGenericSkipFace

J_EventScript_FollowerLookAwayBark::
	applymovement 0xFE J_FollowerLookAwayBark
	waitmovement 0xFE
	goto J_EventScript_FollowerGenericSkipFace

J_EventScript_FollowerLookAwayPoke::
	applymovement 0xFE J_FollowerLookAwayPokeG
	waitmovement 0xFE
	goto J_EventScript_FollowerGenericSkipFace

J_EventScript_FollowerPokeGround::
	faceplayer
	applymovement 0xFE J_FollowerPokeGround
	waitmovement 0xFE
	goto J_EventScript_FollowerGeneric

J_EventScript_FollowerStartled::
	applymovement 0xFE J_FollowerStartled
	waitmovement 0xFE
	goto J_EventScript_FollowerGenericSkipFace

J_EventScript_FollowerFastHopping::
	applymovement 0xFE J_FollowerHopFast
	waitmovement 0xFE
	goto J_EventScript_FollowerGenericSkipFace

J_EventScript_FollowerDizzy::
	applymovement 0xFE J_FollowerDizzy
	waitmovement 0
	goto J_EventScript_FollowerGenericSkipFace

J_EventScript_FollowerLookAroundScared::
	applymovement 0xFE J_FollowerLookAroundScared
	waitmovement 0xFE
	goto J_EventScript_FollowerGeneric

J_EventScript_FollowerDance::
	faceplayer
	applymovement 0xFE J_FollowerDance
	waitmovement 0
	goto J_EventScript_FollowerGenericSkipFace

J_EventScript_FollowerFaceUp::
	applymovement 0xFE J_Common_Movement_FaceUp
	waitmovement 0xFE
	goto J_EventScript_FollowerGenericSkipFace

J_EventScript_FollowerFaceResult::
	switch 32781
	case DIR_SOUTH, J_EventScript_FollowerFaceDown
	case DIR_NORTH, J_EventScript_FollowerFaceUp
	case DIR_WEST, J_EventScript_FollowerFaceLeft
	case DIR_EAST, J_EventScript_FollowerFaceRight
	goto J_EventScript_FollowerGeneric

J_EventScript_FollowerFaceDown:
	applymovement 0xFE J_Common_Movement_FaceDown
	waitmovement 0xFE
	goto J_EventScript_FollowerGenericSkipFace

J_EventScript_FollowerFaceLeft:
	applymovement 0xFE J_Common_Movement_FaceLeft
	waitmovement 0xFE
	goto J_EventScript_FollowerGenericSkipFace

J_EventScript_FollowerFaceRight:
	applymovement 0xFE J_Common_Movement_FaceRight
	waitmovement 0xFE
	goto J_EventScript_FollowerGenericSkipFace

	.align 2

