@ Johto (data/scripts/field_move_scripts_hns.inc), as built into the FireRed game.

J_EventScript_CutTree::
	lockall
	goto_if_set 2081, J_B4_CarriedFieldPermission_0
	goto_if_unset 8693, J_EventScript_CheckTreeCantCut
	goto_if_unset 10369, J_EventScript_CheckTreeCantCut

J_B4_CarriedFieldPermission_0::
	checkpartymove MOVE_CUT
	goto_if_eq 32781, 6, J_EventScript_CheckTreeCantCut
	bufferpartymonnick STR_VAR_1, 32781
	setfieldeffectargument 0, 32781
	buffermovename STR_VAR_2, MOVE_CUT


	msgbox J_Text_MonUsedFieldMove, MSGBOX_DEFAULT
	closemessage

J_EventScript_CutTreeCommon:
	isfollowerfieldmoveuser 32772

J_EventScript_CutTreeDown::
	setflag 16389
	call_if_eq 32772, TRUE, J_EventScript_FollowerFieldMove
	applymovement 32783, J_Movement_CutTreeDown
	playse 128
	waitmovement 0
	removeobject 32783
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
	.string "Thi{SE_M_GRASSWHISTLE}tre{SE_M_REVERSAL}look{SE_M_GRASSWHISTLE}lik{SE_M_REVERSAL}i{SE_M_SPIT_UP}ca{SE_M_ATTRACT}be\n"
	.string "CU{SE_M_SWIFT}down!\p"
	.string "Woul{SE_M_WATERFALL}yo{SE_M_DIVE}lik{SE_M_REVERSAL}t{SE_M_ATTRACT2}CU{SE_M_SWIFT}it?$"

J_Text_MonUsedFieldMove:
	.string "{STR_VAR_1} use{SE_M_WATERFALL}{STR_VAR_2}!$"

J_Text_CantCut:
	.string "Thi{SE_M_GRASSWHISTLE}tre{SE_M_REVERSAL}look{SE_M_GRASSWHISTLE}lik{SE_M_REVERSAL}i{SE_M_SPIT_UP}ca{SE_M_ATTRACT}be\n"
	.string "CU{SE_M_SWIFT}down!$"

J_EventScript_UseRockSmash::
	lockall
	goto J_EventScript_RockSmashCommon

J_EventScript_RockSmash::
	lockall
	checkpartymove MOVE_ROCK_SMASH
	goto_if_set 2085, J_B4_CarriedFieldPermission_1
	goto_if_unset 10368, J_EventScript_CantSmashRock
	goto_if_unset 8695, J_EventScript_CantSmashRock

J_B4_CarriedFieldPermission_1::
	goto_if_eq 32781, 6, J_EventScript_CantSmashRock
	bufferpartymonnick STR_VAR_1, 32781
	setfieldeffectargument 0, 32781
	bufferpartymonnick STR_VAR_1, 32781
	buffermovename STR_VAR_2, MOVE_ROCK_SMASH


	msgbox J_Text_MonUsedFieldMove, MSGBOX_DEFAULT
	closemessage

J_EventScript_RockSmashCommon:

	isfollowerfieldmoveuser 32772

J_EventScript_SmashRock::
	setflag 16389
	call_if_eq 32772, TRUE, J_EventScript_FollowerFieldMove
	applymovement 32783, J_Movement_SmashRock
	playse 131
	waitmovement 0
	removeobject 32783
	specialvar 32781, TryUpdateRusturfTunnelState
	goto_if_eq 32781, TRUE, J_EventScript_EndSmash
	special RockSmashWildEncounter
	goto_if_eq 32781, FALSE, J_EventScript_EndSmash
	waitstate
	random 20
	call_if_eq 32781, 1, J_EventScript_RockSmashHeartscale
	call_if_eq 32781, 2, J_EventScript_RockSmashBlueShard
	call_if_eq 32781, 3, J_EventScript_RockSmashRedShard
	call_if_eq 32781, 4, J_EventScript_RockSmashGreenShard
	call_if_eq 32781, 5, J_EventScript_RockSmashYellowShard
	releaseall
	end

J_EventScript_Headbutt::
	lockall
	goto_if_unset 8704, J_EventScript_CantHeadbuttTree
	checkpartymove MOVE_HEADBUTT
	goto_if_eq 32781, 6, J_EventScript_CantHeadbuttTree
	bufferpartymonnick STR_VAR_1, 32781
	setfieldeffectargument 0, 32781
	msgbox J_Text_MonUsedHeadbutt, MSGBOX_DEFAULT
	closemessage

J_EventScript_HeadbuttCommon:

	isfollowerfieldmoveuser 32772

J_EventScript_HeadbuttTree::
	setflag 16389
	call_if_eq 32772, TRUE, J_EventScript_FollowerFieldMove
	applymovement 32783, J_Movement_HeadbuttTree
	playse 162
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
	.string "{STR_VAR_1} use{SE_M_WATERFALL}HEADBUTT!$"

J_EventScript_FollowerFieldMove:
	getdirectiontoface 32773, 0xFE, 255
	specialvar 32774, GetPlayerFacingDirection
	goto_if_eq 32773, DIR_NONE, J_EventScript_FollowerFieldMoveEnd

	call J_EventScript_FollowerSwap

	switch 32774
	case DIR_NORTH, J_EventScript_FollowerJumpNorth
	case DIR_EAST, J_EventScript_FollowerJumpEast
	case DIR_SOUTH, J_EventScript_FollowerJumpSouth
	case DIR_WEST, J_EventScript_FollowerJumpWest

J_EventScript_FollowerFieldMoveEnd:
	return

J_EventScript_FollowerSwap:
	switch 32773
	case DIR_NORTH, J_EventScript_FollowerMoveNorth
	case DIR_EAST, J_EventScript_FollowerMoveEast
	case DIR_SOUTH, J_EventScript_FollowerMoveSouth
	case DIR_WEST, J_EventScript_FollowerMoveWest
	return

J_EventScript_FollowerMoveNorth:
	applymovement 0xFE, J_Movement_WalkUp
	applymovement 255, J_Movement_WalkDown
	waitmovement 0
	applymovement 255, J_Common_Movement_FaceUp
	waitmovement 0
	return

J_EventScript_FollowerMoveEast:
	applymovement 0xFE, J_Movement_WalkRight
	applymovement 255, J_Movement_WalkLeft
	waitmovement 0
	applymovement 255, J_Common_Movement_FaceRight
	waitmovement 0
	return

J_EventScript_FollowerMoveSouth:
	applymovement 0xFE, J_Movement_WalkDown
	applymovement 255, J_Movement_WalkUp
	waitmovement 0
	applymovement 255, J_Common_Movement_FaceDown
	waitmovement 0
	return

J_EventScript_FollowerMoveWest:
	applymovement 0xFE, J_Movement_WalkLeft
	applymovement 255, J_Movement_WalkRight
	waitmovement 0
	applymovement 255, J_Common_Movement_FaceLeft
	waitmovement 0
	return

J_EventScript_FollowerJumpNorth:
	applymovement 0xFE, J_Movement_JumpUp
	waitmovement 0
	return

J_EventScript_FollowerJumpEast:
	applymovement 0xFE, J_Movement_JumpRight
	waitmovement 0
	return

J_EventScript_FollowerJumpSouth:
	applymovement 0xFE, J_Movement_JumpDown
	waitmovement 0
	return

J_EventScript_FollowerJumpWest:
	applymovement 0xFE, J_Movement_JumpLeft
	waitmovement 0
	return

J_EventScript_EndSmash::
	random 20
	call_if_eq 32781, 1, J_EventScript_RockSmashHeartscale
	call_if_eq 32781, 2, J_EventScript_RockSmashBlueShard
	call_if_eq 32781, 3, J_EventScript_RockSmashRedShard
	call_if_eq 32781, 4, J_EventScript_RockSmashGreenShard
	call_if_eq 32781, 5, J_EventScript_RockSmashYellowShard
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
	.string "Thi{SE_M_GRASSWHISTLE}roc{SE_M_ENCORE2}appear{SE_M_GRASSWHISTLE}t{SE_M_ATTRACT2}b{SE_M_REVERSAL}breakable.\n"
	.string "Woul{SE_M_WATERFALL}yo{SE_M_DIVE}lik{SE_M_REVERSAL}t{SE_M_ATTRACT2}us{SE_M_REVERSAL}ROC{SE_M_SNORE}SMASH?$"

J_Text_CantSmash:
	.string "It'{SE_M_GRASSWHISTLE}{SE_M_CHARGE}rugge{SE_M_WATERFALL}rock{SE_M_SUPERSONIC}bu{SE_M_SPIT_UP}{SE_M_CHARGE}POKéMON\n"
	.string "ma{SE_M_YAWN}b{SE_M_REVERSAL}abl{SE_M_REVERSAL}t{SE_M_ATTRACT2}smas{SE_M_TRI_ATTACK}it.$"

J_Text_WantToHeadbutt:
	.string "Thi{SE_M_GRASSWHISTLE}tre{SE_M_REVERSAL}ma{SE_M_YAWN}hous{SE_M_REVERSAL}POKéMON.\n"
	.string "Woul{SE_M_WATERFALL}yo{SE_M_DIVE}lik{SE_M_REVERSAL}t{SE_M_ATTRACT2}us{SE_M_REVERSAL}HEADBUTT?$"

J_Text_CantHeadbutt:
	.string "It'{SE_M_GRASSWHISTLE}{SE_M_CHARGE}smal{SE_M_BATON_PASS}tree{SE_M_SUPERSONIC}bu{SE_M_SPIT_UP}{SE_M_CHARGE}wild\n"
	.string "POKéMO{SE_M_PSYBEAM2}ma{SE_M_YAWN}b{SE_M_REVERSAL}livin{SE_M_SANDSTORM}within.$"

J_EventScript_StrengthBoulder::
	lockall
	goto_if_set 2083, J_B4_CarriedFieldPermission_2
	goto_if_unset 10370, J_EventScript_CantStrength

J_B4_CarriedFieldPermission_2::
	checkitem 685
	goto_if_eq 32781, FALSE, J_EventScript_CantStrength
	goto_if_set 2053, J_EventScript_CheckActivatedBoulder
	checkpartymove MOVE_STRENGTH
	goto_if_eq 32781, 6, J_EventScript_CantStrength
	bufferpartymonnick STR_VAR_1, 32781
	setfieldeffectargument 0, 32781





	goto J_EventScript_ActivateStrength
	end

J_EventScript_UseStrength::
	lockall


	goto J_EventScript_ActivateStrength
	end

J_EventScript_ActivateStrength::
	setflag 2053
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
	.string "It'{SE_M_GRASSWHISTLE}{SE_M_CHARGE}bi{SE_M_SANDSTORM}boulder{SE_M_SUPERSONIC}bu{SE_M_SPIT_UP}{SE_M_CHARGE}POKéMON\n"
	.string "ma{SE_M_YAWN}b{SE_M_REVERSAL}abl{SE_M_REVERSAL}t{SE_M_ATTRACT2}pus{SE_M_TRI_ATTACK}i{SE_M_SPIT_UP}aside.\p"
	.string "Woul{SE_M_WATERFALL}yo{SE_M_DIVE}lik{SE_M_REVERSAL}t{SE_M_ATTRACT2}us{SE_M_REVERSAL}STRENGTH?$"

J_Text_MonUsedStrength:
	.string "{STR_VAR_1} use{SE_M_WATERFALL}STRENGTH!$"

J_Text_CantStrength:
	.string "It'{SE_M_GRASSWHISTLE}{SE_M_CHARGE}bi{SE_M_SANDSTORM}boulder{SE_M_SUPERSONIC}bu{SE_M_SPIT_UP}{SE_M_CHARGE}POKéMON\n"
	.string "ma{SE_M_YAWN}b{SE_M_REVERSAL}abl{SE_M_REVERSAL}t{SE_M_ATTRACT2}pus{SE_M_TRI_ATTACK}i{SE_M_SPIT_UP}aside.$"

J_Text_StrengthActivated:
	.string "STRENGT{SE_M_SWAGGER2}mad{SE_M_REVERSAL}i{SE_M_SPIT_UP}possibl{SE_M_REVERSAL}t{SE_M_ATTRACT2}move\n"
	.string "boulder{SE_M_GRASSWHISTLE}around.$"

J_EventScript_UseWaterfall::
	lockall
	goto_if_set 2086, J_B4_CarriedFieldPermission_3
	goto_if_unset 10375, J_EventScript_CantWaterfall

J_B4_CarriedFieldPermission_3::
	checkpartymove MOVE_WATERFALL
	goto_if_eq 32781, 6, J_EventScript_CantWaterfall
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
	.string "{SE_M_BONEMERANG}wal{SE_M_BATON_PASS}o{SE_M_ACID_ARMOR}wate{SE_M_SAND_TOMB}i{SE_M_GRASSWHISTLE}crashin{SE_M_SANDSTORM}dow{SE_M_ATTRACT}with\n"
	.string "{SE_M_CHARGE}might{SE_M_YAWN}roar.$"

J_Text_WantToWaterfall:
	.string "It'{SE_M_GRASSWHISTLE}{SE_M_CHARGE}larg{SE_M_REVERSAL}waterfall.\n"
	.string "Woul{SE_M_WATERFALL}yo{SE_M_DIVE}lik{SE_M_REVERSAL}t{SE_M_ATTRACT2}us{SE_M_REVERSAL}WATERFALL?$"

J_Text_MonUsedWaterfall:
	.string "{STR_VAR_1} use{SE_M_WATERFALL}WATERFALL.$"

J_EventScript_UseDive::
	lockall
	checkpartymove MOVE_DIVE
	goto_if_eq 32781, 6, J_EventScript_CantDive
	bufferpartymonnick STR_VAR_1, 32781
	setfieldeffectargument 0, 32781
	setfieldeffectargument 1, 1
	msgbox J_Text_WantToDive, MSGBOX_YESNO
	goto_if_eq 32781, NO, J_EventScript_EndDive
	msgbox J_Text_MonUsedDive, MSGBOX_DEFAULT
	dofieldeffect 44
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
	goto_if_eq 32781, 6, J_EventScript_CantSurface
	bufferpartymonnick STR_VAR_1, 32781
	setfieldeffectargument 0, 32781
	setfieldeffectargument 1, 1
	msgbox J_Text_WantToSurface, MSGBOX_YESNO
	goto_if_eq 32781, NO, J_EventScript_EndSurface
	msgbox J_Text_MonUsedDive, MSGBOX_DEFAULT
	dofieldeffect 44
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
	goto_if_unset 10374, J_EventScript_CantWhirlpool


	playse 216
	goto_if_eq 32780, DIR_NORTH, J_EventScript_WhirlpoolGoNorth
	goto_if_eq 32780, DIR_SOUTH, J_EventScript_WhirlpoolGoSouth
	goto_if_eq 32780, DIR_EAST, J_EventScript_WhirlpoolGoEast
	goto_if_eq 32780, DIR_WEST, J_EventScript_WhirlpoolGoWest
	releaseall
	end

J_EventScript_WhirlpoolGoNorth::
	applymovement 255, J_Movement_WhirlpoolNorth
	waitmovement 0
	releaseall
	end

J_EventScript_WhirlpoolGoSouth::
	applymovement 255, J_Movement_WhirlpoolSouth
	waitmovement 0
	releaseall
	end

J_EventScript_WhirlpoolGoEast::
	applymovement 255, J_Movement_WhirlpoolEast
	waitmovement 0
	releaseall
	end

J_EventScript_WhirlpoolGoWest::
	applymovement 255, J_Movement_WhirlpoolWest
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
	.string "Th{SE_M_REVERSAL}wate{SE_M_SAND_TOMB}i{SE_M_GRASSWHISTLE}swirlin{SE_M_SANDSTORM}an{SE_M_WATERFALL}spinning\n"
	.string "aroun{SE_M_WATERFALL}wit{SE_M_TRI_ATTACK}{SE_M_CHARGE}might{SE_M_YAWN}roar.$"

J_Text_CantDive:
	.string "Th{SE_M_REVERSAL}se{SE_M_CHARGE}i{SE_M_GRASSWHISTLE}dee{SE_M_MORNING_SUN}here{SE_M_PERISH_SONG}{SE_M_BONEMERANG}POKéMON\n"
	.string "ma{SE_M_YAWN}b{SE_M_REVERSAL}abl{SE_M_REVERSAL}t{SE_M_ATTRACT2}g{SE_M_ATTRACT2}underwater.$"

J_Text_WantToDive:
	.string "Th{SE_M_REVERSAL}se{SE_M_CHARGE}i{SE_M_GRASSWHISTLE}dee{SE_M_MORNING_SUN}here.\n"
	.string "Woul{SE_M_WATERFALL}yo{SE_M_DIVE}lik{SE_M_REVERSAL}t{SE_M_ATTRACT2}us{SE_M_REVERSAL}DIVE?$"

J_Text_MonUsedDive:
	.string "{STR_VAR_1} use{SE_M_WATERFALL}WHIRLPOOL.$"

J_Text_CantSurface:
	.string "Ligh{SE_M_SPIT_UP}i{SE_M_GRASSWHISTLE}filterin{SE_M_SANDSTORM}dow{SE_M_ATTRACT}fro{SE_M_MILK_DRINK}above.\n"
	.string "{SE_M_BONEMERANG}POKéMO{SE_M_PSYBEAM2}ma{SE_M_YAWN}b{SE_M_REVERSAL}abl{SE_M_REVERSAL}t{SE_M_ATTRACT2}surface.$"

J_Text_WantToSurface:
	.string "Ligh{SE_M_SPIT_UP}i{SE_M_GRASSWHISTLE}filterin{SE_M_SANDSTORM}dow{SE_M_ATTRACT}fro{SE_M_MILK_DRINK}above.\n"
	.string "Woul{SE_M_WATERFALL}yo{SE_M_DIVE}lik{SE_M_REVERSAL}t{SE_M_ATTRACT2}us{SE_M_REVERSAL}DIVE?$"

J_EventScript_FailSweetScent::
	msgbox J_Text_FailSweetScent, MSGBOX_SIGN
	end

J_Text_FailSweetScent:
	.string "Look{SE_M_GRASSWHISTLE}lik{SE_M_REVERSAL}there'{SE_M_GRASSWHISTLE}nothin{SE_M_SANDSTORM}here…$"

J_EventScript_DigCommon:
	isfollowerfieldmoveuser 32772
	setfieldeffectargument 3, 32772
	dofieldeffect 38
	waitstate

J_EventScript_DigSealedChamber::
	setflag 16389
	call_if_eq 32772, TRUE, J_EventScript_FollowerFieldMove
	callnative DoBrailleDigEffect
	releaseall
	end

J_EventScript_UseDig::
	lockall
	goto J_EventScript_DigCommon

J_EventScript_CutGrassCommon:
	isfollowerfieldmoveuser 32772
	setfieldeffectargument 3, 32772
	dofieldeffect 1
	waitstate

J_EventScript_UseCutGrass::
	lockall
	goto J_EventScript_CutGrassCommon

J_EventScript_UseDefog::
	lockall
	bufferpartymonnick STR_VAR_1, 32781
	buffermovename STR_VAR_2, MOVE_DEFOG
	msgbox J_Text_MonUsedFieldMove, MSGBOX_DEFAULT
	closemessage
	isfollowerfieldmoveuser 32772
	setfieldeffectargument 3, 32772
	setflag 16389
	call_if_eq 32772, TRUE, J_EventScript_FollowerFieldMove
	waitmovement 0
	setfieldeffectargument 0, 32781
	dofieldeffect 74
	waitstate
	releaseall
	end

J_EventScript_UseRockClimb::
	lockall
	checkfieldmove FIELD_MOVE_ROCK_CLIMB
	goto_if_eq 32781, 6, J_EventScript_CantRockClimb
	bufferpartymonnick STR_VAR_1, 32781
	setfieldeffectargument 0, 32781
	msgbox J_Text_WantToRockClimb, MSGBOX_YESNO
	goto_if_eq 32781, NO, J_EventScript_EndRockClimb
	msgbox J_Text_MonUsedRockClimb, MSGBOX_DEFAULT
	closemessage
	dofieldeffect 75
	waitstate
	goto J_EventScript_EndRockClimb
	end

J_EventScript_CantRockClimb::
	msgbox J_Text_CantRockClimb, MSGBOX_DEFAULT

J_EventScript_EndRockClimb::
	releaseall
	end

J_Text_WantToRockClimb:
	.string "Th{SE_M_REVERSAL}clif{SE_M_ACID_ARMOR}i{SE_M_GRASSWHISTLE}steep.\n"
	.string "Woul{SE_M_WATERFALL}yo{SE_M_DIVE}lik{SE_M_REVERSAL}t{SE_M_ATTRACT2}us{SE_M_REVERSAL}Roc{SE_M_ENCORE2}Climb?$"

J_Text_MonUsedRockClimb:
	.string "{STR_VAR_1} use{SE_M_WATERFALL}Roc{SE_M_ENCORE2}Climb!$"

J_Text_CantRockClimb:
	.string "Th{SE_M_REVERSAL}clif{SE_M_ACID_ARMOR}i{SE_M_GRASSWHISTLE}steep.\n"
	.string "{SE_M_BONEMERANG}Pokémo{SE_M_ATTRACT}ma{SE_M_YAWN}b{SE_M_REVERSAL}abl{SE_M_REVERSAL}t{SE_M_ATTRACT2}clim{SE_M_STRENGTH}it.$"

J_SetTimeEncounters::
	callnative SetTimeBasedEncounters
	return

