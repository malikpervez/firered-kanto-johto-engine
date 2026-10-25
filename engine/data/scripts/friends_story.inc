@ Generated from the complete owner-authorized Friends script. See private
@ narrative-dialogue.json for draft anchors, exact pages, branches and widths.
@ No event/battle receipt stands in for an unexecuted visual or gameplay check.
@ Camera calls overwrite VAR_RESULT. Keep story/menu results in their existing
@ saved operands before calling either helper. A failed Begin skips safely.

@ Presentation-only helpers. Preserve native RESULT and event operands.
@ 8000..8003 are audited scratch; 8008/Fuji8009..B remain untouched.
@ Never write FACING/RESULT/ITEM_ID/LAST_TALKED aliases as scratch.
.macro fg_focus speaker:req
	copyvar VAR_0x8000, VAR_0x8004
	copyvar VAR_0x8001, VAR_RESULT
	setvar VAR_0x8004, \speaker
	callnative Special_FriendsStoryFocusSpeaker, requests_effects=1
	copyvar VAR_0x8004, VAR_0x8000
	copyvar VAR_RESULT, VAR_0x8001
.endm
.macro fg_react actor:req, movement:req
	closemessage
	copyvar VAR_0x8000, VAR_0x8004
	copyvar VAR_0x8001, VAR_RESULT
	setvar VAR_0x8004, \actor
	callnative Special_FriendsStoryGetActorLocalId, requests_effects=1
	goto_if_eq VAR_RESULT, 0, .Lfg_no_reaction\@
	copyvar VAR_0x8002, VAR_RESULT
	applymovement2 VAR_0x8002, \movement
	waitmovement VAR_0x8002
.Lfg_no_reaction\@:
	copyvar VAR_0x8004, VAR_0x8000
	copyvar VAR_RESULT, VAR_0x8001
.endm
.macro fg_walk_out actor:req, direction:req
	closemessage
	copyvar VAR_0x8000, VAR_0x8004
	copyvar VAR_0x8001, VAR_RESULT
	copyvar VAR_0x8002, VAR_0x8005
	setvar VAR_0x8004, \actor
	setvar VAR_0x8005, \direction
	callnative Special_FriendsStoryStep, requests_effects=1
	copyvar VAR_0x8006, VAR_RESULT
	call FG_WaitSceneMovement
	copyvar VAR_0x8004, VAR_0x8000
	copyvar VAR_0x8005, VAR_0x8002
	copyvar VAR_RESULT, VAR_0x8001
.endm
.macro fg_walk_back actor:req, direction:req
	closemessage
	copyvar VAR_0x8000, VAR_0x8004
	copyvar VAR_0x8001, VAR_RESULT
	copyvar VAR_0x8002, VAR_0x8005
	goto_if_eq VAR_0x8006, FALSE, .Lfg_skip_return\@
	setvar VAR_0x8004, \actor
	setvar VAR_0x8005, \direction
	callnative Special_FriendsStoryStep, requests_effects=1
	call FG_WaitSceneMovement
.Lfg_skip_return\@:
	setvar VAR_0x8006, FALSE
	copyvar VAR_0x8004, VAR_0x8000
	copyvar VAR_0x8005, VAR_0x8002
	copyvar VAR_RESULT, VAR_0x8001
.endm
FG_WaitSceneMovement::
	copyvar VAR_0x8003, VAR_RESULT
	callnative Special_FriendsStoryWaitMovement, requests_effects=1
	goto_if_eq VAR_RESULT, FALSE, FG_SceneMovementSettled
	waitstate
FG_SceneMovementSettled::
	copyvar VAR_RESULT, VAR_0x8003
	return
FG_FrameCamera::
	call FG_WaitSceneMovement
	closemessage
	callnative Special_FriendsCameraBegin, requests_effects=1
	goto_if_eq VAR_RESULT, FALSE, FG_Release
	goto_if_eq VAR_RESULT, 2, FG_CameraFramed
	waitstate
FG_CameraFramed::
	return
FG_ReturnCamera::
	call FG_WaitSceneMovement
	closemessage
	callnative Special_FriendsCameraReturn, requests_effects=1
	goto_if_eq VAR_RESULT, FALSE, FG_CameraReturned
	waitstate
FG_CameraReturned::
	return
FG_Release::
	call FG_ReturnCamera
	callnative Special_FriendsStoryEndScene, requests_effects=1
	closemessage
	releaseall
	end
@ Viridian's arrival (FG01) plays by itself the first time the player enters the town after the Pokédex:
@ Giratina tears the sky over the south road, drops the seven onto it and leaves them there.
FG01_ArrivalCheck::
	setvar VAR_TEMP_D, 0
	callnative Special_FriendsStoryArrivalPending, requests_effects=1
	goto_if_eq VAR_RESULT, FALSE, FG01_ArrivalCheckDone
	setvar VAR_TEMP_D, 1
FG01_ArrivalCheckDone::
	return
FG01_Interact::
FG01_Arrival::
	lockall
	setvar VAR_TEMP_D, 0
	setvar VAR_0x8004, 1
	callnative Special_FriendsStoryBegin, requests_effects=1
	goto_if_ne VAR_RESULT, 1, FG_Release
	copyvar VAR_0x8008, VAR_RESULT
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceUp
	waitmovement 0
	playmoncry SPECIES_GIRATINA_ALTERED, CRY_MODE_ENCOUNTER
	setvar VAR_0x8004, 0
	setvar VAR_0x8005, 3
	setvar VAR_0x8006, 10
	setvar VAR_0x8007, 3
	special ShakeCamera
	waitstate
	setvar VAR_0x8004, 24
	callnative Special_FriendsDistortionFlash, requests_effects=1
	call_if_eq VAR_RESULT, TRUE, FG01_WaitEffect
	waitmoncry
	msgbox FG01_Text_Tear
	call FG_FrameCamera
	setvar VAR_0x8004, 1
	setvar VAR_0x8005, 0
	callnative Special_FriendsStoryStage, requests_effects=1
	call FG_WaitSceneMovement
	playmoncry SPECIES_GIRATINA_ALTERED, CRY_MODE_ENCOUNTER
	setvar VAR_0x8004, 40
	callnative Special_FriendsDistortionFlash, requests_effects=1
	call_if_eq VAR_RESULT, TRUE, FG01_WaitEffect
	waitmoncry
	callnative Special_FriendsStoryLand, requests_effects=1
	setobjectxyperm LOCALID_FRIENDS_VIRIDIANCITY_FRLG_JON, 25, 43
	addobject LOCALID_FRIENDS_VIRIDIANCITY_FRLG_JON
	applymovement LOCALID_FRIENDS_VIRIDIANCITY_FRLG_JON, FG01_Movement_Drop
	delay 6
	setobjectxyperm LOCALID_FRIENDS_VIRIDIANCITY_FRLG_BRIAN, 26, 44
	addobject LOCALID_FRIENDS_VIRIDIANCITY_FRLG_BRIAN
	applymovement LOCALID_FRIENDS_VIRIDIANCITY_FRLG_BRIAN, FG01_Movement_Drop
	delay 4
	setobjectxyperm LOCALID_FRIENDS_VIRIDIANCITY_FRLG_NICK, 27, 45
	addobject LOCALID_FRIENDS_VIRIDIANCITY_FRLG_NICK
	applymovement LOCALID_FRIENDS_VIRIDIANCITY_FRLG_NICK, FG01_Movement_Drop
	delay 6
	setobjectxyperm LOCALID_FRIENDS_VIRIDIANCITY_FRLG_TIM, 27, 43
	addobject LOCALID_FRIENDS_VIRIDIANCITY_FRLG_TIM
	applymovement LOCALID_FRIENDS_VIRIDIANCITY_FRLG_TIM, FG01_Movement_Drop
	delay 3
	setobjectxyperm LOCALID_FRIENDS_VIRIDIANCITY_FRLG_X, 25, 45
	addobject LOCALID_FRIENDS_VIRIDIANCITY_FRLG_X
	applymovement LOCALID_FRIENDS_VIRIDIANCITY_FRLG_X, FG01_Movement_Drop
	delay 5
	setobjectxyperm LOCALID_FRIENDS_VIRIDIANCITY_FRLG_LB, 23, 45
	addobject LOCALID_FRIENDS_VIRIDIANCITY_FRLG_LB
	applymovement LOCALID_FRIENDS_VIRIDIANCITY_FRLG_LB, FG01_Movement_Drop
	delay 12
	setobjectxyperm LOCALID_FRIENDS_VIRIDIANCITY_FRLG_HAM, 24, 44
	addobject LOCALID_FRIENDS_VIRIDIANCITY_FRLG_HAM
	applymovement LOCALID_FRIENDS_VIRIDIANCITY_FRLG_HAM, FG01_Movement_DropFlat
	waitmovement LOCALID_FRIENDS_VIRIDIANCITY_FRLG_HAM
	playse SE_M_STRENGTH
	delay 40
	fg_react 2, FG_Move_Startled
	fg_focus 2
	msgbox FG01_Text_Main01
	fg_focus 0
	msgbox FG01_Text_Main02
	fg_focus 3
	msgbox FG01_Text_Main03
	fg_focus 0
	msgbox FG01_Text_Main04
	fg_focus 3
	msgbox FG01_Text_Main05
	fg_focus 0
	msgbox FG01_Text_Main06
	fg_focus 2
	msgbox FG01_Text_Main07
	fg_focus 6
	msgbox FG01_Text_Main08
	fg_focus 2
	msgbox FG01_Text_Main09
	fg_focus 6
	msgbox FG01_Text_Main10
	fg_focus 4
	msgbox FG01_Text_Main11
	fg_focus 2
	msgbox FG01_Text_Main12
	fg_focus 4
	msgbox FG01_Text_Main13
	fg_focus 5
	msgbox FG01_Text_Main14
	fg_focus 3
	msgbox FG01_Text_Main15
	closemessage
	playmoncry SPECIES_GIRATINA_ALTERED, CRY_MODE_FAINT
	setvar VAR_0x8004, 32
	callnative Special_FriendsDistortionFlash, requests_effects=1
	call_if_eq VAR_RESULT, TRUE, FG01_WaitEffect
	removeobject 230
	waitmoncry
	fg_focus 0
	msgbox FG01_Text_Main16
	fg_focus 2
	msgbox FG01_Text_Main17
	fg_focus 3
	msgbox FG01_Text_Main18
	fg_focus 4
	msgbox FG01_Text_Main19
	fg_react 1, FG_Move_Startled
	fg_focus 1
	msgbox FG01_Text_Main20
	fg_focus 3
	msgbox FG01_Text_Main21
	fg_focus 5
	msgbox FG01_Text_Main22
	fg_focus 0
	msgbox FG01_Text_Main23
	fg_focus 6
	msgbox FG01_Text_Main24
	fg_focus 3
	msgbox FG01_Text_Main25
	fg_focus 2
	msgbox FG01_Text_Main26
	fg_focus 0
	msgbox FG01_Text_Main27
	fg_focus 4
	msgbox FG01_Text_Main28
	fg_focus 3
	msgbox FG01_Text_Main29
	fg_focus 5
	msgbox FG01_Text_Main30
	fg_focus 0
	msgbox FG01_Text_Main31
	fg_focus 5
	msgbox FG01_Text_Main32
	fg_focus 6
	msgbox FG01_Text_Main33
	fg_focus 0
	msgbox FG01_Text_Main34
	fg_focus 2
	msgbox FG01_Text_Main35
	fg_focus 1
	msgbox FG01_Text_Main36
	fg_focus 3
	msgbox FG01_Text_Main37
	fg_focus 1
	msgbox FG01_Text_Main38
	fg_focus 4
	msgbox FG01_Text_Main39
	fg_focus 0
	msgbox FG01_Text_Main40
	fg_focus 3
	msgbox FG01_Text_Main41
	fg_focus 2
	msgbox FG01_Text_Main42
	call FG_ReturnCamera
FG01_Approach::
	getplayerxy VAR_0x8000, VAR_0x8001
	goto_if_le VAR_0x8001, 48, FG01_Approached
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkUp
	waitmovement 0
	goto FG01_Approach
FG01_Approached::
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceUp
	waitmovement 0
	fg_focus 4
	msgbox FG01_Text_Main43
	fg_focus 0
	msgbox FG01_Text_Main44
	setvar VAR_0x8004, 1
	callnative Special_FriendsStoryMarkSeen, requests_effects=1
FG01_Repeat::
FG01_Menu::
	call FG_WaitSceneMovement
	closemessage
	callnative Special_FriendsStoryPrepareMenu, requests_effects=1
	multichoice 0, 0, MULTI_FG01, TRUE
	goto_if_eq VAR_RESULT, 1, FG01_Choice1
FG01_Choice0::
	fg_focus 3
	msgbox FG01_Text_Choice0_01
	fg_focus 4
	msgbox FG01_Text_Choice0_02
	fg_focus 6
	msgbox FG01_Text_Choice0_03
	fg_focus 3
	msgbox FG01_Text_Choice0_04
	fg_focus 0
	msgbox FG01_Text_Choice0_05
	goto FG01_Leave
FG01_Choice1::
	fg_focus 0
	msgbox FG01_Text_Choice1_01
	fg_focus 3
	msgbox FG01_Text_Choice1_02
	fg_focus 0
	msgbox FG01_Text_Choice1_03
	fg_focus 4
	msgbox FG01_Text_Choice1_04
FG01_Leave::
	fg_focus 2
	msgbox FG01_Text_Leave01
	fg_focus 4
	msgbox FG01_Text_Leave02
	closemessage
	applymovement LOCALID_FRIENDS_VIRIDIANCITY_FRLG_X, FG01_Movement_HeadNorth
	applymovement LOCALID_FRIENDS_VIRIDIANCITY_FRLG_NICK, FG01_Movement_HeadNorth
	applymovement LOCALID_FRIENDS_VIRIDIANCITY_FRLG_LB, FG01_Movement_HeadNorth
	applymovement LOCALID_FRIENDS_VIRIDIANCITY_FRLG_BRIAN, FG01_Movement_HeadNorthSlowly
	applymovement LOCALID_FRIENDS_VIRIDIANCITY_FRLG_TIM, FG01_Movement_HeadNorth
	applymovement LOCALID_FRIENDS_VIRIDIANCITY_FRLG_HAM, FG01_Movement_HeadNorth
	applymovement LOCALID_FRIENDS_VIRIDIANCITY_FRLG_JON, FG01_Movement_HeadNorthAngrily
	waitmovement LOCALID_FRIENDS_VIRIDIANCITY_FRLG_BRIAN
	setvar VAR_0x8004, 1
	setvar VAR_0x8005, 90
	callnative Special_FriendsStoryStage, requests_effects=1
	call FG_WaitSceneMovement
	goto FG_Release
FG01_WaitEffect::
	waitstate
	return
FG01_Movement_Drop::
	jump_2_down
	step_end
FG01_Movement_DropFlat::
	jump_2_down
	face_up
	delay_16
	face_down
	step_end
FG01_Movement_HeadNorth::
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end
FG01_Movement_HeadNorthSlowly::
	delay_16
	walk_slow_up
	walk_slow_up
	walk_slow_up
	walk_slow_up
	walk_slow_up
	walk_slow_up
	walk_slow_up
	step_end
FG01_Movement_HeadNorthAngrily::
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	step_end
FG02_Interact::
	lockall
	faceplayer
	setvar VAR_0x8004, 2
	callnative Special_FriendsStoryBegin, requests_effects=1
	goto_if_eq VAR_RESULT, 0, FG_Release
	copyvar VAR_0x8008, VAR_RESULT
	call FG_FrameCamera
	callnative Special_FriendsStoryGetPendingLoss, requests_effects=1
	goto_if_eq VAR_RESULT, 1, FG_Loss01
	goto_if_eq VAR_RESULT, 2, FG_Loss02
	goto_if_eq VAR_RESULT, 3, FG_Loss03
	goto_if_eq VAR_RESULT, 4, FG_Loss04
	goto_if_eq VAR_RESULT, 5, FG_Loss05
	goto_if_eq VAR_RESULT, 6, FG_Loss06
	goto_if_eq VAR_RESULT, 7, FG_Loss07
	goto_if_eq VAR_RESULT, 8, FG_Loss08
	goto_if_eq VAR_RESULT, 9, FG_Loss09
	goto_if_eq VAR_RESULT, 10, FG_Loss10
	goto_if_eq VAR_RESULT, 11, FG_Loss11
	goto_if_eq VAR_RESULT, 12, FG_Loss12
	goto_if_eq VAR_RESULT, 13, FG_Loss13
	goto_if_eq VAR_RESULT, 14, FG_Loss14
	goto_if_eq VAR_0x8008, 2, FG02_Repeat
	callnative Special_FriendsStoryNeedsIntroduction, requests_effects=1
	goto_if_eq VAR_RESULT, FALSE, FG02_Introduced
	fg_focus 3
	msgbox FG_Text_Introduction_1
	fg_focus 3
	msgbox FG_Text_Introduction_2
FG02_Introduced::
	setvar VAR_0x8004, 2
	setvar VAR_0x8005, 0
	closemessage
	callnative Special_FriendsStoryStage, requests_effects=1
	call FG_WaitSceneMovement
	delay 30
	fg_focus 0
	msgbox FG02_Text_Main01
	fg_focus 3
	msgbox FG02_Text_Main02
	fg_focus 0
	msgbox FG02_Text_Main03
	fg_focus 3
	msgbox FG02_Text_Main04
	fg_focus 0
	msgbox FG02_Text_Main05
	fg_focus 3
	msgbox FG02_Text_Main06
	fg_focus 0
	msgbox FG02_Text_Main07
	fg_focus 3
	msgbox FG02_Text_Main08
	fg_focus 0
	msgbox FG02_Text_Main09
	setvar VAR_0x8004, 2
	setvar VAR_0x8005, 9
	closemessage
	callnative Special_FriendsStoryStage, requests_effects=1
	call FG_WaitSceneMovement
	delay 30
	fg_focus 2
	msgbox FG02_Text_Main10
	fg_focus 3
	msgbox FG02_Text_Main11
	fg_focus 2
	msgbox FG02_Text_Main12
	fg_focus 3
	msgbox FG02_Text_Main13
	fg_focus 2
	msgbox FG02_Text_Main14
	fg_focus 3
	msgbox FG02_Text_Main15
	fg_focus 2
	msgbox FG02_Text_Main16
	setvar VAR_0x8004, 2
	setvar VAR_0x8005, 16
	closemessage
	callnative Special_FriendsStoryStage, requests_effects=1
	call FG_WaitSceneMovement
	delay 30
	fg_walk_out 2, DIR_SOUTH
	fg_focus 0
	msgbox FG02_Text_Main17
	fg_focus 3
	msgbox FG02_Text_Main18
	fg_focus 0
	msgbox FG02_Text_Main19
	fg_focus 3
	msgbox FG02_Text_Main20
	fg_focus 2
	msgbox FG02_Text_Main21
	fg_walk_back 2, DIR_NORTH
	fg_focus 3
	msgbox FG02_Text_Main22
	setvar VAR_0x8004, 2
	setvar VAR_0x8005, 22
	closemessage
	callnative Special_FriendsStoryStage, requests_effects=1
	call FG_WaitSceneMovement
	delay 30
	fg_focus 0
	msgbox FG02_Text_Main23
	fg_focus 2
	msgbox FG02_Text_Main24
	fg_focus 0
	msgbox FG02_Text_Main25
	fg_focus 3
	msgbox FG02_Text_Main26
	setvar VAR_0x8004, 2
	callnative Special_FriendsStoryMarkSeen, requests_effects=1
FG02_Repeat::
	goto FG02_Menu
FG02_Menu::
	call FG_WaitSceneMovement
	closemessage
	callnative Special_FriendsStoryPrepareMenu, requests_effects=1
	multichoice 0, 0, MULTI_FG02, FALSE
	goto_if_eq VAR_RESULT, 0, FG02_Choice0
	goto_if_eq VAR_RESULT, 1, FG02_Choice1
	goto FG_Release
FG02_Choice0::
	call FG_FrameCamera
	fg_focus 0
	msgbox FG02_Text_Choice0_01
	fg_focus 3
	msgbox FG02_Text_Choice0_02
	fg_focus 0
	msgbox FG02_Text_Choice0_03
	goto FG_Battle01
FG02_Choice1::
	call FG_FrameCamera
	fg_focus 0
	msgbox FG02_Text_Choice1_01
	fg_focus 3
	msgbox FG02_Text_Choice1_02
	fg_focus 0
	msgbox FG02_Text_Choice1_03
	goto FG_Release
FG03_Interact::
	lockall
	faceplayer
	setvar VAR_0x8004, 3
	callnative Special_FriendsStoryBegin, requests_effects=1
	goto_if_eq VAR_RESULT, 0, FG_Release
	copyvar VAR_0x8008, VAR_RESULT
	call FG_FrameCamera
	callnative Special_FriendsStoryGetPendingLoss, requests_effects=1
	goto_if_eq VAR_RESULT, 1, FG_Loss01
	goto_if_eq VAR_RESULT, 2, FG_Loss02
	goto_if_eq VAR_RESULT, 3, FG_Loss03
	goto_if_eq VAR_RESULT, 4, FG_Loss04
	goto_if_eq VAR_RESULT, 5, FG_Loss05
	goto_if_eq VAR_RESULT, 6, FG_Loss06
	goto_if_eq VAR_RESULT, 7, FG_Loss07
	goto_if_eq VAR_RESULT, 8, FG_Loss08
	goto_if_eq VAR_RESULT, 9, FG_Loss09
	goto_if_eq VAR_RESULT, 10, FG_Loss10
	goto_if_eq VAR_RESULT, 11, FG_Loss11
	goto_if_eq VAR_RESULT, 12, FG_Loss12
	goto_if_eq VAR_RESULT, 13, FG_Loss13
	goto_if_eq VAR_RESULT, 14, FG_Loss14
	goto_if_eq VAR_0x8008, 2, FG03_Repeat
	callnative Special_FriendsStoryNeedsIntroduction, requests_effects=1
	goto_if_eq VAR_RESULT, FALSE, FG03_Introduced
	fg_focus 3
	msgbox FG_Text_Introduction_1
	fg_focus 3
	msgbox FG_Text_Introduction_2
	fg_focus 3
	msgbox FG03_Text_LatePartners1
	fg_focus 3
	msgbox FG03_Text_LatePartners2
FG03_Introduced::
	setvar VAR_0x8004, 3
	setvar VAR_0x8005, 0
	closemessage
	callnative Special_FriendsStoryStage, requests_effects=1
	call FG_WaitSceneMovement
	delay 30
	fg_react 2, FG_Move_Startled
	fg_focus 2
	msgbox FG03_Text_Main01
	fg_focus 5
	msgbox FG03_Text_Main02
	fg_focus 2
	msgbox FG03_Text_Main03
	fg_focus 5
	msgbox FG03_Text_Main04
	fg_focus 3
	msgbox FG03_Text_Main05
	fg_focus 5
	msgbox FG03_Text_Main06
	fg_focus 3
	msgbox FG03_Text_Main07
	fg_focus 5
	msgbox FG03_Text_Main08
	fg_focus 0
	msgbox FG03_Text_Main09
	fg_focus 2
	msgbox FG03_Text_Main10
	fg_walk_out 5, DIR_WEST
	fg_focus 3
	msgbox FG03_Text_Main11
	setvar VAR_0x8004, 3
	setvar VAR_0x8005, 11
	closemessage
	callnative Special_FriendsStoryStage, requests_effects=1
	call FG_WaitSceneMovement
	delay 30
	fg_focus 5
	msgbox FG03_Text_Main12
	fg_focus 2
	msgbox FG03_Text_Main13
	fg_focus 5
	msgbox FG03_Text_Main14
	fg_focus 3
	msgbox FG03_Text_Main15
	fg_focus 2
	msgbox FG03_Text_Main16
	fg_focus 3
	msgbox FG03_Text_Main17
	fg_focus 5
	msgbox FG03_Text_Main18
	fg_walk_back 5, DIR_EAST
	fg_focus 3
	msgbox FG03_Text_Main19
	setvar VAR_0x8004, 3
	setvar VAR_0x8005, 19
	closemessage
	callnative Special_FriendsStoryStage, requests_effects=1
	call FG_WaitSceneMovement
	delay 30
	fg_focus 5
	msgbox FG03_Text_Main20
	fg_focus 3
	msgbox FG03_Text_Main21
	fg_focus 2
	msgbox FG03_Text_Main22
	fg_focus 5
	msgbox FG03_Text_Main23
	fg_focus 3
	msgbox FG03_Text_Main24
	fg_focus 2
	msgbox FG03_Text_Main25
	fg_focus 0
	msgbox FG03_Text_Main26
	setvar VAR_0x8004, 3
	callnative Special_FriendsStoryMarkSeen, requests_effects=1
FG03_Repeat::
	goto FG03_Menu
FG03_Menu::
	call FG_WaitSceneMovement
	closemessage
	callnative Special_FriendsStoryPrepareMenu, requests_effects=1
	multichoice 0, 0, MULTI_FG03, FALSE
	goto_if_eq VAR_RESULT, 0, FG03_Choice0
	goto_if_eq VAR_RESULT, 1, FG03_Choice1
	goto FG_Release
FG03_Choice0::
	call FG_FrameCamera
	fg_focus 2
	msgbox FG03_Text_Choice0_01
	fg_focus 3
	msgbox FG03_Text_Choice0_02
	fg_focus 2
	msgbox FG03_Text_Choice0_03
	goto FG_Battle02
FG03_Choice1::
	call FG_FrameCamera
	fg_focus 3
	msgbox FG03_Text_Choice1_01
	fg_focus 2
	msgbox FG03_Text_Choice1_02
	fg_focus 3
	msgbox FG03_Text_Choice1_03
	fg_focus 2
	msgbox FG03_Text_Choice1_04
	goto FG_Release
FG04_Interact::
	lockall
	faceplayer
	setvar VAR_0x8004, 4
	callnative Special_FriendsStoryBegin, requests_effects=1
	goto_if_eq VAR_RESULT, 0, FG_Release
	copyvar VAR_0x8008, VAR_RESULT
	call FG_FrameCamera
	callnative Special_FriendsStoryGetPendingLoss, requests_effects=1
	goto_if_eq VAR_RESULT, 1, FG_Loss01
	goto_if_eq VAR_RESULT, 2, FG_Loss02
	goto_if_eq VAR_RESULT, 3, FG_Loss03
	goto_if_eq VAR_RESULT, 4, FG_Loss04
	goto_if_eq VAR_RESULT, 5, FG_Loss05
	goto_if_eq VAR_RESULT, 6, FG_Loss06
	goto_if_eq VAR_RESULT, 7, FG_Loss07
	goto_if_eq VAR_RESULT, 8, FG_Loss08
	goto_if_eq VAR_RESULT, 9, FG_Loss09
	goto_if_eq VAR_RESULT, 10, FG_Loss10
	goto_if_eq VAR_RESULT, 11, FG_Loss11
	goto_if_eq VAR_RESULT, 12, FG_Loss12
	goto_if_eq VAR_RESULT, 13, FG_Loss13
	goto_if_eq VAR_RESULT, 14, FG_Loss14
	goto_if_eq VAR_0x8008, 2, FG04_Repeat
	callnative Special_FriendsStoryNeedsIntroduction, requests_effects=1
	goto_if_eq VAR_RESULT, FALSE, FG04_Introduced
	fg_focus 3
	msgbox FG_Text_Introduction_1
	fg_focus 3
	msgbox FG_Text_Introduction_2
	fg_focus 3
	msgbox FG04_Text_LatePartners1
	fg_focus 3
	msgbox FG04_Text_LatePartners2
FG04_Introduced::
	setvar VAR_0x8004, 4
	setvar VAR_0x8005, 0
	closemessage
	callnative Special_FriendsStoryStage, requests_effects=1
	call FG_WaitSceneMovement
	delay 30
	fg_focus 4
	msgbox FG04_Text_Main01
	fg_focus 3
	msgbox FG04_Text_Main02
	fg_focus 4
	msgbox FG04_Text_Main03
	fg_focus 3
	msgbox FG04_Text_Main04
	fg_focus 4
	msgbox FG04_Text_Main05
	fg_focus 0
	msgbox FG04_Text_Main06
	fg_focus 3
	msgbox FG04_Text_Main07
	fg_focus 0
	msgbox FG04_Text_Main08
	fg_focus 4
	msgbox FG04_Text_Main09
	fg_focus 5
	msgbox FG04_Text_Main10
	fg_focus 4
	msgbox FG04_Text_Main11
	fg_focus 5
	msgbox FG04_Text_Main12
	fg_focus 4
	msgbox FG04_Text_Main13
	fg_focus 5
	msgbox FG04_Text_Main14
	setvar VAR_0x8004, 4
	setvar VAR_0x8005, 14
	closemessage
	callnative Special_FriendsStoryStage, requests_effects=1
	call FG_WaitSceneMovement
	delay 30
	fg_focus 6
	msgbox FG04_Text_Main15
	fg_focus 3
	msgbox FG04_Text_Main16
	fg_focus 6
	msgbox FG04_Text_Main17
	fg_focus 3
	msgbox FG04_Text_Main18
	fg_focus 6
	msgbox FG04_Text_Main19
	fg_focus 3
	msgbox FG04_Text_Main20
	fg_focus 0
	msgbox FG04_Text_Main21
	fg_react 1, FG_Move_LookAround
	fg_focus 1
	msgbox FG04_Text_Main22
	fg_focus 0
	msgbox FG04_Text_Main23
	fg_focus 3
	msgbox FG04_Text_Main24
	fg_focus 1
	msgbox FG04_Text_Main25
	setvar VAR_0x8004, 4
	setvar VAR_0x8005, 25
	closemessage
	callnative Special_FriendsStoryStage, requests_effects=1
	call FG_WaitSceneMovement
	delay 30
	fg_focus 3
	msgbox FG04_Text_Main26
	setvar VAR_0x8004, 4
	callnative Special_FriendsStoryMarkSeen, requests_effects=1
FG04_Repeat::
	goto FG04_Menu
FG04_Menu::
	call FG_WaitSceneMovement
	closemessage
	callnative Special_FriendsStoryPrepareMenu, requests_effects=1
	multichoice 0, 0, MULTI_FG04, FALSE
	goto_if_eq VAR_RESULT, 0, FG04_Choice0
	goto_if_eq VAR_RESULT, 1, FG04_Choice1
	goto FG_Release
FG04_Choice0::
	call FG_FrameCamera
	fg_focus 3
	msgbox FG04_Text_Choice0_01
	fg_focus 0
	msgbox FG04_Text_Choice0_02
	fg_focus 3
	msgbox FG04_Text_Choice0_03
	fg_focus 4
	msgbox FG04_Text_Choice0_04
	goto FG_Release
FG04_Choice1::
	call FG_FrameCamera
	fg_focus 4
	msgbox FG04_Text_Choice1_01
	fg_focus 0
	msgbox FG04_Text_Choice1_02
	fg_focus 3
	msgbox FG04_Text_Choice1_03
	fg_focus 0
	msgbox FG04_Text_Choice1_04
	goto FG_Release
FG05_Interact::
	lockall
	faceplayer
	setvar VAR_0x8004, 5
	callnative Special_FriendsStoryBegin, requests_effects=1
	goto_if_eq VAR_RESULT, 0, FG_Release
	copyvar VAR_0x8008, VAR_RESULT
	call FG_FrameCamera
	callnative Special_FriendsStoryGetPendingLoss, requests_effects=1
	goto_if_eq VAR_RESULT, 1, FG_Loss01
	goto_if_eq VAR_RESULT, 2, FG_Loss02
	goto_if_eq VAR_RESULT, 3, FG_Loss03
	goto_if_eq VAR_RESULT, 4, FG_Loss04
	goto_if_eq VAR_RESULT, 5, FG_Loss05
	goto_if_eq VAR_RESULT, 6, FG_Loss06
	goto_if_eq VAR_RESULT, 7, FG_Loss07
	goto_if_eq VAR_RESULT, 8, FG_Loss08
	goto_if_eq VAR_RESULT, 9, FG_Loss09
	goto_if_eq VAR_RESULT, 10, FG_Loss10
	goto_if_eq VAR_RESULT, 11, FG_Loss11
	goto_if_eq VAR_RESULT, 12, FG_Loss12
	goto_if_eq VAR_RESULT, 13, FG_Loss13
	goto_if_eq VAR_RESULT, 14, FG_Loss14
	goto_if_eq VAR_0x8008, 2, FG05_Repeat
	callnative Special_FriendsStoryNeedsIntroduction, requests_effects=1
	goto_if_eq VAR_RESULT, FALSE, FG05_Introduced
	fg_focus 3
	msgbox FG_Text_Introduction_1
	fg_focus 3
	msgbox FG_Text_Introduction_2
	fg_focus 3
	msgbox FG_Text_PartnersKanto
FG05_Introduced::
	setvar VAR_0x8004, 5
	setvar VAR_0x8005, 0
	closemessage
	callnative Special_FriendsStoryStage, requests_effects=1
	call FG_WaitSceneMovement
	delay 30
	fg_focus 6
	msgbox FG05_Text_Main01
	fg_focus 7
	msgbox FG05_Text_Main02
	fg_focus 6
	msgbox FG05_Text_Main03
	fg_focus 7
	msgbox FG05_Text_Main04
	fg_focus 6
	msgbox FG05_Text_Main05
	fg_focus 7
	msgbox FG05_Text_Main06
	fg_focus 6
	msgbox FG05_Text_Main07
	fg_focus 7
	msgbox FG05_Text_Main08
	fg_focus 6
	msgbox FG05_Text_Main09
	fg_walk_out 6, DIR_WEST
	fg_focus 7
	msgbox FG05_Text_Main10
	setvar VAR_0x8004, 5
	setvar VAR_0x8005, 10
	closemessage
	callnative Special_FriendsStoryStage, requests_effects=1
	call FG_WaitSceneMovement
	delay 30
	fg_focus 3
	msgbox FG05_Text_Main11
	fg_focus 6
	msgbox FG05_Text_Main12
	fg_focus 3
	msgbox FG05_Text_Main13
	fg_focus 6
	msgbox FG05_Text_Main14
	fg_focus 3
	msgbox FG05_Text_Main15
	fg_focus 6
	msgbox FG05_Text_Main16
	fg_walk_back 6, DIR_EAST
	fg_focus 3
	msgbox FG05_Text_Main17
	setvar VAR_0x8004, 5
	setvar VAR_0x8005, 17
	closemessage
	callnative Special_FriendsStoryStage, requests_effects=1
	call FG_WaitSceneMovement
	delay 30
	fg_focus 2
	msgbox FG05_Text_Main18
	fg_focus 7
	msgbox FG05_Text_Main19
	fg_focus 6
	msgbox FG05_Text_Main20
	fg_focus 7
	msgbox FG05_Text_Main21
	fg_focus 6
	msgbox FG05_Text_Main22
	fg_focus 7
	msgbox FG05_Text_Main23
	fg_focus 3
	msgbox FG05_Text_Main24
	fg_focus 6
	msgbox FG05_Text_Main25
	fg_focus 7
	msgbox FG05_Text_Main26
	setvar VAR_0x8004, 5
	setvar VAR_0x8005, 26
	closemessage
	callnative Special_FriendsStoryStage, requests_effects=1
	call FG_WaitSceneMovement
	delay 30
	setvar VAR_0x8004, 5
	callnative Special_FriendsStoryMarkSeen, requests_effects=1
FG05_Repeat::
	fg_focus 6
	msgbox FG05_Text_Repeat
	goto FG_Release
FG06_Interact::
	lockall
	faceplayer
	setvar VAR_0x8004, 6
	callnative Special_FriendsStoryBegin, requests_effects=1
	goto_if_eq VAR_RESULT, 0, FG_Release
	copyvar VAR_0x8008, VAR_RESULT
	call FG_FrameCamera
	callnative Special_FriendsStoryGetPendingLoss, requests_effects=1
	goto_if_eq VAR_RESULT, 1, FG_Loss01
	goto_if_eq VAR_RESULT, 2, FG_Loss02
	goto_if_eq VAR_RESULT, 3, FG_Loss03
	goto_if_eq VAR_RESULT, 4, FG_Loss04
	goto_if_eq VAR_RESULT, 5, FG_Loss05
	goto_if_eq VAR_RESULT, 6, FG_Loss06
	goto_if_eq VAR_RESULT, 7, FG_Loss07
	goto_if_eq VAR_RESULT, 8, FG_Loss08
	goto_if_eq VAR_RESULT, 9, FG_Loss09
	goto_if_eq VAR_RESULT, 10, FG_Loss10
	goto_if_eq VAR_RESULT, 11, FG_Loss11
	goto_if_eq VAR_RESULT, 12, FG_Loss12
	goto_if_eq VAR_RESULT, 13, FG_Loss13
	goto_if_eq VAR_RESULT, 14, FG_Loss14
	goto_if_eq VAR_0x8008, 2, FG06_Repeat
	callnative Special_FriendsStoryNeedsIntroduction, requests_effects=1
	goto_if_eq VAR_RESULT, FALSE, FG06_Introduced
	fg_focus 3
	msgbox FG_Text_Introduction_1
	fg_focus 3
	msgbox FG_Text_Introduction_2
	fg_focus 3
	msgbox FG_Text_PartnersKanto
FG06_Introduced::
	setvar VAR_0x8004, 6
	setvar VAR_0x8005, 0
	closemessage
	callnative Special_FriendsStoryStage, requests_effects=1
	call FG_WaitSceneMovement
	delay 30
	fg_focus 0
	msgbox FG06_Text_Main01
	fg_focus 3
	msgbox FG06_Text_Main02
	fg_focus 0
	msgbox FG06_Text_Main03
	fg_focus 3
	msgbox FG06_Text_Main04
	fg_focus 0
	msgbox FG06_Text_Main05
	fg_focus 3
	msgbox FG06_Text_Main06
	fg_focus 0
	msgbox FG06_Text_Main07
	fg_focus 3
	msgbox FG06_Text_Main08
	fg_focus 0
	msgbox FG06_Text_Main09
	fg_focus 3
	msgbox FG06_Text_Main10
	setvar VAR_0x8004, 6
	setvar VAR_0x8005, 10
	closemessage
	callnative Special_FriendsStoryStage, requests_effects=1
	call FG_WaitSceneMovement
	delay 30
	fg_focus 5
	msgbox FG06_Text_Main11
	fg_react 5, FG_Move_LookAround
	fg_focus 4
	msgbox FG06_Text_Main12
	fg_focus 5
	msgbox FG06_Text_Main13
	fg_focus 4
	msgbox FG06_Text_Main14
	fg_focus 5
	msgbox FG06_Text_Main15
	fg_focus 4
	msgbox FG06_Text_Main16
	fg_focus 5
	msgbox FG06_Text_Main17
	fg_focus 4
	msgbox FG06_Text_Main18
	fg_focus 5
	msgbox FG06_Text_Main19
	fg_focus 4
	msgbox FG06_Text_Main20
	setvar VAR_0x8004, 6
	setvar VAR_0x8005, 20
	closemessage
	callnative Special_FriendsStoryStage, requests_effects=1
	call FG_WaitSceneMovement
	delay 30
	fg_walk_out 5, DIR_NORTH
	fg_focus 5
	msgbox FG06_Text_Main21
	fg_focus 3
	msgbox FG06_Text_Main22
	fg_focus 2
	msgbox FG06_Text_Main23
	fg_walk_back 5, DIR_SOUTH
	fg_focus 5
	msgbox FG06_Text_Main24
	fg_focus 2
	msgbox FG06_Text_Main25
	fg_focus 3
	msgbox FG06_Text_Main26
	setvar VAR_0x8004, 6
	callnative Special_FriendsStoryMarkSeen, requests_effects=1
FG06_Repeat::
	goto FG06_Menu
FG06_Menu::
	call FG_WaitSceneMovement
	closemessage
	callnative Special_FriendsStoryPrepareMenu, requests_effects=1
	multichoice 0, 0, MULTI_FG06, FALSE
	goto_if_eq VAR_RESULT, 0, FG06_Choice0
	goto_if_eq VAR_RESULT, 1, FG06_Choice1
	goto_if_eq VAR_RESULT, 2, FG06_Choice2
	goto FG_Release
FG06_Choice0::
	call FG_FrameCamera
	fg_focus 3
	msgbox FG06_Text_Choice0_01
	fg_focus 0
	msgbox FG06_Text_Choice0_02
	fg_focus 3
	msgbox FG06_Text_Choice0_03
	goto FG_Battle03
FG06_Choice1::
	call FG_FrameCamera
	fg_focus 5
	msgbox FG06_Text_Choice1_01
	fg_focus 4
	msgbox FG06_Text_Choice1_02
	fg_focus 5
	msgbox FG06_Text_Choice1_03
	goto FG_Battle04
FG06_Choice2::
	call FG_FrameCamera
	fg_focus 3
	msgbox FG06_Text_Choice2_01
	fg_focus 0
	msgbox FG06_Text_Choice2_02
	fg_focus 3
	msgbox FG06_Text_Choice2_03
	goto FG_Release
FG07_Interact::
	lockall
	faceplayer
	setvar VAR_0x8004, 7
	callnative Special_FriendsStoryBegin, requests_effects=1
	goto_if_eq VAR_RESULT, 0, FG_Release
	copyvar VAR_0x8008, VAR_RESULT
	call FG_FrameCamera
	callnative Special_FriendsStoryGetPendingLoss, requests_effects=1
	goto_if_eq VAR_RESULT, 1, FG_Loss01
	goto_if_eq VAR_RESULT, 2, FG_Loss02
	goto_if_eq VAR_RESULT, 3, FG_Loss03
	goto_if_eq VAR_RESULT, 4, FG_Loss04
	goto_if_eq VAR_RESULT, 5, FG_Loss05
	goto_if_eq VAR_RESULT, 6, FG_Loss06
	goto_if_eq VAR_RESULT, 7, FG_Loss07
	goto_if_eq VAR_RESULT, 8, FG_Loss08
	goto_if_eq VAR_RESULT, 9, FG_Loss09
	goto_if_eq VAR_RESULT, 10, FG_Loss10
	goto_if_eq VAR_RESULT, 11, FG_Loss11
	goto_if_eq VAR_RESULT, 12, FG_Loss12
	goto_if_eq VAR_RESULT, 13, FG_Loss13
	goto_if_eq VAR_RESULT, 14, FG_Loss14
	goto_if_eq VAR_0x8008, 2, FG07_Repeat
	callnative Special_FriendsStoryNeedsIntroduction, requests_effects=1
	goto_if_eq VAR_RESULT, FALSE, FG07_Introduced
	fg_focus 3
	msgbox FG_Text_Introduction_1
	fg_focus 3
	msgbox FG_Text_Introduction_2
	fg_focus 3
	msgbox FG_Text_PartnersKanto
FG07_Introduced::
	setvar VAR_0x8004, 7
	setvar VAR_0x8005, 0
	closemessage
	callnative Special_FriendsStoryStage, requests_effects=1
	call FG_WaitSceneMovement
	delay 30
	fg_focus 4
	msgbox FG07_Text_Main01
	fg_focus 0
	msgbox FG07_Text_Main02
	fg_focus 4
	msgbox FG07_Text_Main03
	fg_focus 0
	msgbox FG07_Text_Main04
	fg_focus 4
	msgbox FG07_Text_Main05
	fg_focus 0
	msgbox FG07_Text_Main06
	fg_focus 5
	msgbox FG07_Text_Main07
	fg_focus 4
	msgbox FG07_Text_Main08
	fg_focus 5
	msgbox FG07_Text_Main09
	fg_focus 4
	msgbox FG07_Text_Main10
	fg_focus 2
	msgbox FG07_Text_Main11
	fg_focus 4
	msgbox FG07_Text_Main12
	fg_focus 3
	msgbox FG07_Text_Main13
	fg_focus 4
	msgbox FG07_Text_Main14
	fg_focus 0
	msgbox FG07_Text_Main15
	fg_focus 4
	msgbox FG07_Text_Main16
	setvar VAR_0x8004, 7
	setvar VAR_0x8005, 16
	closemessage
	callnative Special_FriendsStoryStage, requests_effects=1
	call FG_WaitSceneMovement
	delay 30
	fg_focus 3
	msgbox FG07_Text_Main17
	fg_focus 4
	msgbox FG07_Text_Main18
	fg_focus 0
	msgbox FG07_Text_Main19
	fg_walk_out 4, DIR_WEST
	fg_focus 4
	msgbox FG07_Text_Main20
	fg_focus 5
	msgbox FG07_Text_Main21
	fg_focus 4
	msgbox FG07_Text_Main22
	setvar VAR_0x8004, 7
	setvar VAR_0x8005, 22
	closemessage
	callnative Special_FriendsStoryStage, requests_effects=1
	call FG_WaitSceneMovement
	delay 30
	fg_focus 7
	msgbox FG07_Text_Main23
	fg_focus 2
	msgbox FG07_Text_Main24
	fg_focus 7
	msgbox FG07_Text_Main25
	fg_walk_back 4, DIR_EAST
	fg_focus 0
	msgbox FG07_Text_Main26
	setvar VAR_0x8004, 7
	setvar VAR_0x8005, 26
	closemessage
	callnative Special_FriendsStoryStage, requests_effects=1
	call FG_WaitSceneMovement
	delay 30
	setvar VAR_0x8004, 7
	callnative Special_FriendsStoryMarkSeen, requests_effects=1
FG07_Repeat::
	goto FG07_Menu
FG07_Menu::
	call FG_WaitSceneMovement
	closemessage
	callnative Special_FriendsStoryPrepareMenu, requests_effects=1
	multichoice 0, 0, MULTI_FG07, FALSE
	goto_if_eq VAR_RESULT, 0, FG07_Choice0
	goto_if_eq VAR_RESULT, 1, FG07_Choice1
	goto_if_eq VAR_RESULT, 2, FG07_Choice2
	goto FG_Release
FG07_Choice0::
	call FG_FrameCamera
	fg_focus 4
	msgbox FG07_Text_Choice0_01
	fg_focus 0
	msgbox FG07_Text_Choice0_02
	fg_focus 4
	msgbox FG07_Text_Choice0_03
	goto FG_Battle05
FG07_Choice1::
	call FG_FrameCamera
	fg_focus 4
	msgbox FG07_Text_Choice1_01
	fg_focus 5
	msgbox FG07_Text_Choice1_02
	fg_focus 0
	msgbox FG07_Text_Choice1_03
	fg_focus 4
	msgbox FG07_Text_Choice1_04
	goto FG_Release
FG07_Choice2::
	call FG_FrameCamera
	fg_focus 4
	msgbox FG07_Text_Choice2_01
	fg_focus 0
	msgbox FG07_Text_Choice2_02
	fg_focus 3
	msgbox FG07_Text_Choice2_03
	fg_focus 0
	msgbox FG07_Text_Choice2_04
	goto FG_Release
@ Native warps replace the global script context. Resume only through the
@ destination map's one-shot frame table; these gates live in temporary RAM.
FG08_InsideOnFrame::
	map_script_2 VAR_0x8007, 1, FG08_ResumeInside
	.2byte 0
FG08_OutsideOnFrame::
	map_script_2 VAR_0x8007, 2, FG08_ResumeOutside
	.2byte 0
FG08_ResumeInside::
	lockall
	setvar VAR_0x8004, 8
	setvar VAR_0x8005, 1
	callnative Special_FriendsStoryConsumeFujiWarp, requests_effects=1
	goto_if_eq VAR_RESULT, FALSE, FG_Release
	goto FG08_InsidePhase
FG08_ResumeOutside::
	lockall
	setvar VAR_0x8004, 8
	setvar VAR_0x8005, 2
	callnative Special_FriendsStoryConsumeFujiWarp, requests_effects=1
	goto_if_eq VAR_RESULT, FALSE, FG_Release
	goto FG08_ReframeRepeat
FG08_Interact::
	lockall
	faceplayer
	call FG_ReturnCamera
	getplayerxy VAR_0x800A, VAR_0x800B
	callnative Special_FriendsStoryAtFujiHouse, requests_effects=1
	copyvar VAR_0x8009, VAR_RESULT
	setvar VAR_0x8004, 8
	callnative Special_FriendsStoryBegin, requests_effects=1
	goto_if_eq VAR_RESULT, 0, FG_Release
	copyvar VAR_0x8008, VAR_RESULT
	call FG_FrameCamera
	callnative Special_FriendsStoryGetPendingLoss, requests_effects=1
	goto_if_eq VAR_RESULT, 1, FG_Loss01
	goto_if_eq VAR_RESULT, 2, FG_Loss02
	goto_if_eq VAR_RESULT, 3, FG_Loss03
	goto_if_eq VAR_RESULT, 4, FG_Loss04
	goto_if_eq VAR_RESULT, 5, FG_Loss05
	goto_if_eq VAR_RESULT, 6, FG_Loss06
	goto_if_eq VAR_RESULT, 7, FG_Loss07
	goto_if_eq VAR_RESULT, 8, FG_Loss08
	goto_if_eq VAR_RESULT, 9, FG_Loss09
	goto_if_eq VAR_RESULT, 10, FG_Loss10
	goto_if_eq VAR_RESULT, 11, FG_Loss11
	goto_if_eq VAR_RESULT, 12, FG_Loss12
	goto_if_eq VAR_RESULT, 13, FG_Loss13
	goto_if_eq VAR_RESULT, 14, FG_Loss14
	goto_if_eq VAR_0x8008, 2, FG08_Repeat
	callnative Special_FriendsStoryNeedsIntroduction, requests_effects=1
	goto_if_eq VAR_RESULT, FALSE, FG08_Introduced
	fg_focus 3
	msgbox FG_Text_Introduction_1
	fg_focus 3
	msgbox FG_Text_Introduction_2
	fg_focus 3
	msgbox FG_Text_PartnersKanto
FG08_Introduced::
	setvar VAR_0x8004, 8
	setvar VAR_0x8005, 0
	closemessage
	callnative Special_FriendsStoryStage, requests_effects=1
	call FG_WaitSceneMovement
	delay 30
	fg_focus 1
	msgbox FG08_Text_Main01
	fg_focus 7
	msgbox FG08_Text_Main02
	fg_focus 2
	msgbox FG08_Text_Main03
	setvar VAR_0x8004, 8
	setvar VAR_0x8005, 3
	closemessage
	callnative Special_FriendsStoryStage, requests_effects=1
	call FG_WaitSceneMovement
	delay 30
	fg_focus 3
	msgbox FG08_Text_Main04
	fg_focus 2
	msgbox FG08_Text_Main05
	fg_focus 7
	msgbox FG08_Text_Main06
	fg_focus 1
	msgbox FG08_Text_Main07
	fg_focus 7
	msgbox FG08_Text_Main08
	closemessage
	call FG_ReturnCamera
	callnative Special_FriendsStoryEndScene, requests_effects=1
	goto_if_eq VAR_0x8009, TRUE, FG08_InsidePhase
	call FG_ReturnCamera
	setvar VAR_0x8005, 1
	callnative Special_FriendsStoryPrepareFujiWarp, requests_effects=1
	goto_if_eq VAR_RESULT, FALSE, FG_Release
	warp MAP_LAVENDER_TOWN_VOLUNTEER_POKEMON_HOUSE, 4, 6
	waitstate
	end
FG08_InsidePhase::
	callnative Special_FriendsStoryReadFujiReturn, requests_effects=1
	call FG_FrameCamera
	setvar VAR_0x8004, 8
	setvar VAR_0x8005, 8
	callnative Special_FriendsStoryStage, requests_effects=1
	call FG_WaitSceneMovement
	delay 30
	fg_focus 3
	msgbox FG08_Text_Main09
	fg_focus 2
	msgbox FG08_Text_Main10
	fg_focus 7
	msgbox FG08_Text_Main11
	setvar VAR_0x8004, 8
	setvar VAR_0x8005, 11
	closemessage
	callnative Special_FriendsStoryStage, requests_effects=1
	call FG_WaitSceneMovement
	delay 30
	fg_focus 5
	msgbox FG08_Text_Main12
	fg_focus 7
	msgbox FG08_Text_Main13
	fg_focus 1
	msgbox FG08_Text_Main14
	fg_focus 2
	msgbox FG08_Text_Main15
	fg_focus 7
	msgbox FG08_Text_Main16
	setvar VAR_0x8004, 8
	setvar VAR_0x8005, 16
	closemessage
	callnative Special_FriendsStoryStage, requests_effects=1
	call FG_WaitSceneMovement
	delay 30
	setvar VAR_0x8004, 8
	callnative Special_FriendsStoryMarkSeen, requests_effects=1
	call FG_ReturnCamera
	callnative Special_FriendsStoryEndScene, requests_effects=1
	callnative Special_FriendsStoryReadFujiReturn, requests_effects=1
	goto_if_eq VAR_0x8009, TRUE, FG08_ReframeRepeat
	call FG_ReturnCamera
	setvar VAR_0x8005, 2
	callnative Special_FriendsStoryPrepareFujiWarp, requests_effects=1
	goto_if_eq VAR_RESULT, FALSE, FG_Release
	warp MAP_LAVENDER_TOWN, VAR_0x800A, VAR_0x800B
	waitstate
	end
FG08_ReframeRepeat::
	call FG_FrameCamera
FG08_Repeat::
	fg_focus 7
	msgbox FG08_Text_Repeat
	goto FG_Release
FG09_Interact::
	lockall
	faceplayer
	setvar VAR_0x8004, 9
	callnative Special_FriendsStoryBegin, requests_effects=1
	goto_if_eq VAR_RESULT, 0, FG_Release
	copyvar VAR_0x8008, VAR_RESULT
	call FG_FrameCamera
	callnative Special_FriendsStoryGetPendingLoss, requests_effects=1
	goto_if_eq VAR_RESULT, 1, FG_Loss01
	goto_if_eq VAR_RESULT, 2, FG_Loss02
	goto_if_eq VAR_RESULT, 3, FG_Loss03
	goto_if_eq VAR_RESULT, 4, FG_Loss04
	goto_if_eq VAR_RESULT, 5, FG_Loss05
	goto_if_eq VAR_RESULT, 6, FG_Loss06
	goto_if_eq VAR_RESULT, 7, FG_Loss07
	goto_if_eq VAR_RESULT, 8, FG_Loss08
	goto_if_eq VAR_RESULT, 9, FG_Loss09
	goto_if_eq VAR_RESULT, 10, FG_Loss10
	goto_if_eq VAR_RESULT, 11, FG_Loss11
	goto_if_eq VAR_RESULT, 12, FG_Loss12
	goto_if_eq VAR_RESULT, 13, FG_Loss13
	goto_if_eq VAR_RESULT, 14, FG_Loss14
	goto_if_eq VAR_0x8008, 2, FG09_Repeat
	callnative Special_FriendsStoryNeedsIntroduction, requests_effects=1
	goto_if_eq VAR_RESULT, FALSE, FG09_Introduced
	fg_focus 3
	msgbox FG_Text_Introduction_1
	fg_focus 3
	msgbox FG_Text_Introduction_2
	fg_focus 3
	msgbox FG09_Text_LatePartners1
	fg_focus 3
	msgbox FG09_Text_LatePartners2
FG09_Introduced::
	setvar VAR_0x8004, 9
	setvar VAR_0x8005, 0
	closemessage
	callnative Special_FriendsStoryStage, requests_effects=1
	call FG_WaitSceneMovement
	delay 30
	fg_focus 0
	msgbox FG09_Text_Main01
	fg_focus 3
	msgbox FG09_Text_Main02
	fg_focus 0
	msgbox FG09_Text_Main03
	fg_focus 3
	msgbox FG09_Text_Main04
	setvar VAR_0x8004, 9
	setvar VAR_0x8005, 4
	closemessage
	callnative Special_FriendsStoryStage, requests_effects=1
	call FG_WaitSceneMovement
	delay 30
	fg_focus 0
	msgbox FG09_Text_Main05
	fg_focus 6
	msgbox FG09_Text_Main06
	fg_focus 2
	msgbox FG09_Text_Main07
	fg_focus 1
	msgbox FG09_Text_Main08
	fg_focus 3
	msgbox FG09_Text_Main09
	fg_focus 6
	msgbox FG09_Text_Main10
	fg_focus 4
	msgbox FG09_Text_Main11
	fg_walk_out 6, DIR_EAST
	fg_focus 6
	msgbox FG09_Text_Main12
	setvar VAR_0x8004, 9
	setvar VAR_0x8005, 12
	closemessage
	callnative Special_FriendsStoryStage, requests_effects=1
	call FG_WaitSceneMovement
	delay 30
	fg_focus 5
	msgbox FG09_Text_Main13
	fg_focus 0
	msgbox FG09_Text_Main14
	fg_focus 5
	msgbox FG09_Text_Main15
	fg_focus 0
	msgbox FG09_Text_Main16
	fg_walk_back 6, DIR_WEST
	fg_focus 3
	msgbox FG09_Text_Main17
	setvar VAR_0x8004, 9
	setvar VAR_0x8005, 17
	closemessage
	callnative Special_FriendsStoryStage, requests_effects=1
	call FG_WaitSceneMovement
	delay 30
	fg_focus 0
	msgbox FG09_Text_Main18
	fg_focus 6
	msgbox FG09_Text_Main19
	fg_focus 3
	msgbox FG09_Text_Main20
	fg_focus 4
	msgbox FG09_Text_Main21
	fg_focus 6
	msgbox FG09_Text_Main22
	setvar VAR_0x8004, 9
	callnative Special_FriendsStoryMarkSeen, requests_effects=1
FG09_Repeat::
	goto FG09_Menu
FG09_Menu::
	call FG_WaitSceneMovement
	closemessage
	callnative Special_FriendsStoryPrepareMenu, requests_effects=1
	multichoice 0, 0, MULTI_FG09, FALSE
	goto_if_eq VAR_RESULT, 0, FG09_Choice0
	goto_if_eq VAR_RESULT, 1, FG09_Choice1
	goto_if_eq VAR_RESULT, 2, FG09_Choice2
	goto FG_Release
FG09_Choice0::
	call FG_FrameCamera
	fg_focus 6
	msgbox FG09_Text_Choice0_01
	fg_focus 3
	msgbox FG09_Text_Choice0_02
	goto FG_Battle06
FG09_Choice1::
	call FG_FrameCamera
	fg_focus 6
	msgbox FG09_Text_Choice1_01
	fg_focus 0
	msgbox FG09_Text_Choice1_02
	fg_focus 3
	msgbox FG09_Text_Choice1_03
	goto FG_Release
FG09_Choice2::
	call FG_FrameCamera
	fg_focus 6
	msgbox FG09_Text_Choice2_01
	fg_focus 0
	msgbox FG09_Text_Choice2_02
	fg_focus 3
	msgbox FG09_Text_Choice2_03
	goto FG_Release
FG10_Interact::
	lockall
	faceplayer
	setvar VAR_0x8004, 10
	callnative Special_FriendsStoryBegin, requests_effects=1
	goto_if_eq VAR_RESULT, 0, FG_Release
	copyvar VAR_0x8008, VAR_RESULT
	call FG_FrameCamera
	callnative Special_FriendsStoryGetPendingLoss, requests_effects=1
	goto_if_eq VAR_RESULT, 1, FG_Loss01
	goto_if_eq VAR_RESULT, 2, FG_Loss02
	goto_if_eq VAR_RESULT, 3, FG_Loss03
	goto_if_eq VAR_RESULT, 4, FG_Loss04
	goto_if_eq VAR_RESULT, 5, FG_Loss05
	goto_if_eq VAR_RESULT, 6, FG_Loss06
	goto_if_eq VAR_RESULT, 7, FG_Loss07
	goto_if_eq VAR_RESULT, 8, FG_Loss08
	goto_if_eq VAR_RESULT, 9, FG_Loss09
	goto_if_eq VAR_RESULT, 10, FG_Loss10
	goto_if_eq VAR_RESULT, 11, FG_Loss11
	goto_if_eq VAR_RESULT, 12, FG_Loss12
	goto_if_eq VAR_RESULT, 13, FG_Loss13
	goto_if_eq VAR_RESULT, 14, FG_Loss14
	goto_if_eq VAR_0x8008, 2, FG10_Repeat
	callnative Special_FriendsStoryNeedsIntroduction, requests_effects=1
	goto_if_eq VAR_RESULT, FALSE, FG10_Introduced
	fg_focus 3
	msgbox FG_Text_Introduction_1
	fg_focus 3
	msgbox FG_Text_Introduction_2
	fg_focus 3
	msgbox FG_Text_PartnersKanto
FG10_Introduced::
	setvar VAR_0x8004, 10
	setvar VAR_0x8005, 0
	closemessage
	callnative Special_FriendsStoryStage, requests_effects=1
	call FG_WaitSceneMovement
	delay 30
	fg_focus 4
	msgbox FG10_Text_Main01
	fg_focus 0
	msgbox FG10_Text_Main02
	fg_focus 3
	msgbox FG10_Text_Main03
	fg_focus 6
	msgbox FG10_Text_Main04
	fg_focus 4
	msgbox FG10_Text_Main05
	fg_focus 5
	msgbox FG10_Text_Main06
	fg_focus 2
	msgbox FG10_Text_Main07
	fg_focus 6
	msgbox FG10_Text_Main08
	fg_focus 3
	msgbox FG10_Text_Main09
	fg_focus 0
	msgbox FG10_Text_Main10
	fg_focus 4
	msgbox FG10_Text_Main11
	fg_focus 5
	msgbox FG10_Text_Main12
	setvar VAR_0x8004, 10
	setvar VAR_0x8005, 12
	closemessage
	callnative Special_FriendsStoryStage, requests_effects=1
	call FG_WaitSceneMovement
	delay 30
	fg_focus 6
	msgbox FG10_Text_Main13
	fg_focus 2
	msgbox FG10_Text_Main14
	fg_focus 3
	msgbox FG10_Text_Main15
	fg_focus 2
	msgbox FG10_Text_Main16
	fg_focus 3
	msgbox FG10_Text_Main17
	fg_focus 0
	msgbox FG10_Text_Main18
	fg_focus 6
	msgbox FG10_Text_Main19
	fg_focus 0
	msgbox FG10_Text_Main20
	fg_focus 4
	msgbox FG10_Text_Main21
	fg_focus 5
	msgbox FG10_Text_Main22
	fg_focus 3
	msgbox FG10_Text_Main23
	fg_focus 6
	msgbox FG10_Text_Main24
	setvar VAR_0x8004, 10
	callnative Special_FriendsStoryMarkSeen, requests_effects=1
FG10_Repeat::
	fg_focus 4
	msgbox FG10_Text_Repeat
	goto FG_Release
FG11_Interact::
	lockall
	faceplayer
	setvar VAR_0x8004, 11
	callnative Special_FriendsStoryBegin, requests_effects=1
	goto_if_eq VAR_RESULT, 0, FG_Release
	copyvar VAR_0x8008, VAR_RESULT
	call FG_FrameCamera
	callnative Special_FriendsStoryGetPendingLoss, requests_effects=1
	goto_if_eq VAR_RESULT, 1, FG_Loss01
	goto_if_eq VAR_RESULT, 2, FG_Loss02
	goto_if_eq VAR_RESULT, 3, FG_Loss03
	goto_if_eq VAR_RESULT, 4, FG_Loss04
	goto_if_eq VAR_RESULT, 5, FG_Loss05
	goto_if_eq VAR_RESULT, 6, FG_Loss06
	goto_if_eq VAR_RESULT, 7, FG_Loss07
	goto_if_eq VAR_RESULT, 8, FG_Loss08
	goto_if_eq VAR_RESULT, 9, FG_Loss09
	goto_if_eq VAR_RESULT, 10, FG_Loss10
	goto_if_eq VAR_RESULT, 11, FG_Loss11
	goto_if_eq VAR_RESULT, 12, FG_Loss12
	goto_if_eq VAR_RESULT, 13, FG_Loss13
	goto_if_eq VAR_RESULT, 14, FG_Loss14
	goto_if_eq VAR_0x8008, 2, FG11_Repeat
	callnative Special_FriendsStoryNeedsIntroduction, requests_effects=1
	goto_if_eq VAR_RESULT, FALSE, FG11_Introduced
	fg_focus 3
	msgbox FG_Text_Introduction_1
	fg_focus 3
	msgbox FG_Text_Introduction_2
	fg_focus 3
	msgbox FG_Text_PartnersKanto
FG11_Introduced::
	setvar VAR_0x8004, 11
	setvar VAR_0x8005, 0
	closemessage
	callnative Special_FriendsStoryStage, requests_effects=1
	call FG_WaitSceneMovement
	delay 30
	fg_focus 0
	msgbox FG11_Text_Main01
	fg_focus 6
	msgbox FG11_Text_Main02
	fg_focus 0
	msgbox FG11_Text_Main03
	fg_focus 3
	msgbox FG11_Text_Main04
	fg_focus 4
	msgbox FG11_Text_Main05
	fg_focus 6
	msgbox FG11_Text_Main06
	fg_focus 0
	msgbox FG11_Text_Main07
	fg_walk_out 3, DIR_EAST
	fg_focus 3
	msgbox FG11_Text_Main08
	setvar VAR_0x8004, 11
	setvar VAR_0x8005, 8
	closemessage
	callnative Special_FriendsStoryStage, requests_effects=1
	call FG_WaitSceneMovement
	delay 30
	fg_focus 1
	msgbox FG11_Text_Main09
	fg_focus 2
	msgbox FG11_Text_Main10
	fg_focus 4
	msgbox FG11_Text_Main11
	fg_focus 0
	msgbox FG11_Text_Main12
	setvar VAR_0x8004, 11
	setvar VAR_0x8005, 12
	closemessage
	callnative Special_FriendsStoryStage, requests_effects=1
	call FG_WaitSceneMovement
	delay 30
	fg_focus 6
	msgbox FG11_Text_Main13
	fg_walk_back 3, DIR_WEST
	fg_focus 3
	msgbox FG11_Text_Main14
	fg_focus 0
	msgbox FG11_Text_Main15
	fg_focus 4
	msgbox FG11_Text_Main16
	fg_focus 2
	msgbox FG11_Text_Main17
	fg_focus 3
	msgbox FG11_Text_Main18
	fg_focus 1
	msgbox FG11_Text_Main19
	fg_focus 6
	msgbox FG11_Text_Main20
	fg_focus 2
	msgbox FG11_Text_Main21
	setvar VAR_0x8004, 11
	callnative Special_FriendsStoryMarkSeen, requests_effects=1
FG11_Repeat::
	goto FG11_Menu
FG11_Menu::
	call FG_WaitSceneMovement
	closemessage
	callnative Special_FriendsStoryPrepareMenu, requests_effects=1
	multichoice 0, 0, MULTI_FG11, FALSE
	goto_if_eq VAR_RESULT, 0, FG11_Choice0
	goto_if_eq VAR_RESULT, 1, FG11_Choice1
	goto FG_Release
FG11_Choice0::
	call FG_FrameCamera
	fg_focus 3
	msgbox FG11_Text_Choice0_01
	fg_focus 0
	msgbox FG11_Text_Choice0_02
	fg_focus 6
	msgbox FG11_Text_Choice0_03
	goto FG_Release
FG11_Choice1::
	call FG_FrameCamera
	fg_focus 4
	msgbox FG11_Text_Choice1_01
	fg_focus 3
	msgbox FG11_Text_Choice1_02
	fg_focus 4
	msgbox FG11_Text_Choice1_03
	goto FG_Release
FG12_Interact::
	lockall
	faceplayer
	setvar VAR_0x8004, 12
	callnative Special_FriendsStoryBegin, requests_effects=1
	goto_if_eq VAR_RESULT, 0, FG_Release
	copyvar VAR_0x8008, VAR_RESULT
	call FG_FrameCamera
	callnative Special_FriendsStoryGetPendingLoss, requests_effects=1
	goto_if_eq VAR_RESULT, 1, FG_Loss01
	goto_if_eq VAR_RESULT, 2, FG_Loss02
	goto_if_eq VAR_RESULT, 3, FG_Loss03
	goto_if_eq VAR_RESULT, 4, FG_Loss04
	goto_if_eq VAR_RESULT, 5, FG_Loss05
	goto_if_eq VAR_RESULT, 6, FG_Loss06
	goto_if_eq VAR_RESULT, 7, FG_Loss07
	goto_if_eq VAR_RESULT, 8, FG_Loss08
	goto_if_eq VAR_RESULT, 9, FG_Loss09
	goto_if_eq VAR_RESULT, 10, FG_Loss10
	goto_if_eq VAR_RESULT, 11, FG_Loss11
	goto_if_eq VAR_RESULT, 12, FG_Loss12
	goto_if_eq VAR_RESULT, 13, FG_Loss13
	goto_if_eq VAR_RESULT, 14, FG_Loss14
	goto_if_eq VAR_0x8008, 2, FG12_Repeat
	callnative Special_FriendsStoryNeedsIntroduction, requests_effects=1
	goto_if_eq VAR_RESULT, FALSE, FG12_Introduced
	fg_focus 3
	msgbox FG12_Text_LateIntroduction
	fg_focus 3
	msgbox FG_Text_Introduction_2
	fg_focus 3
	msgbox FG_Text_PartnersKanto
FG12_Introduced::
	setvar VAR_0x8004, 12
	setvar VAR_0x8005, 0
	closemessage
	callnative Special_FriendsStoryStage, requests_effects=1
	call FG_WaitSceneMovement
	delay 30
	fg_focus 2
	msgbox FG12_Text_Main01
	fg_focus 3
	msgbox FG12_Text_Main02
	fg_focus 0
	msgbox FG12_Text_Main03
	fg_focus 3
	msgbox FG12_Text_Main04
	fg_focus 2
	msgbox FG12_Text_Main05
	fg_focus 6
	msgbox FG12_Text_Main06
	fg_focus 5
	msgbox FG12_Text_Main07
	fg_focus 2
	msgbox FG12_Text_Main08
	fg_focus 0
	msgbox FG12_Text_Main09
	fg_focus 1
	msgbox FG12_Text_Main10
	setvar VAR_0x8004, 12
	setvar VAR_0x8005, 10
	closemessage
	callnative Special_FriendsStoryStage, requests_effects=1
	call FG_WaitSceneMovement
	delay 30
	fg_focus 3
	msgbox FG12_Text_Main11
	fg_focus 5
	msgbox FG12_Text_Main12
	fg_focus 0
	msgbox FG12_Text_Main13
	fg_focus 4
	msgbox FG12_Text_Main14
	fg_focus 6
	msgbox FG12_Text_Main15
	fg_focus 0
	msgbox FG12_Text_Main16
	fg_focus 3
	msgbox FG12_Text_Main17
	fg_focus 4
	msgbox FG12_Text_Main18
	fg_focus 0
	msgbox FG12_Text_Main19
	fg_focus 6
	msgbox FG12_Text_Main20
	setvar VAR_0x8004, 12
	callnative Special_FriendsStoryMarkSeen, requests_effects=1
FG12_Repeat::
	goto FG12_Menu
FG12_Menu::
	call FG_WaitSceneMovement
	closemessage
	callnative Special_FriendsStoryPrepareMenu, requests_effects=1
	multichoice 0, 0, MULTI_FG12, FALSE
	goto_if_eq VAR_RESULT, 0, FG12_Choice0
	goto_if_eq VAR_RESULT, 1, FG12_Choice1
	goto FG_Release
FG12_Choice0::
	call FG_FrameCamera
	fg_focus 4
	msgbox FG12_Text_Choice0_01
	fg_focus 3
	msgbox FG12_Text_Choice0_02
	fg_focus 0
	msgbox FG12_Text_Choice0_03
	fg_focus 6
	msgbox FG12_Text_Choice0_04
	goto FG_Release
FG12_Choice1::
	call FG_FrameCamera
	fg_focus 6
	msgbox FG12_Text_Choice1_01
	fg_focus 0
	msgbox FG12_Text_Choice1_02
	fg_focus 3
	msgbox FG12_Text_Choice1_03
	fg_focus 0
	msgbox FG12_Text_Choice1_04
	goto FG_Release
FG13_Interact::
	lockall
	faceplayer
	setvar VAR_0x8004, 13
	callnative Special_FriendsStoryBegin, requests_effects=1
	goto_if_eq VAR_RESULT, 0, FG_Release
	copyvar VAR_0x8008, VAR_RESULT
	call FG_FrameCamera
	callnative Special_FriendsStoryGetPendingLoss, requests_effects=1
	goto_if_eq VAR_RESULT, 1, FG_Loss01
	goto_if_eq VAR_RESULT, 2, FG_Loss02
	goto_if_eq VAR_RESULT, 3, FG_Loss03
	goto_if_eq VAR_RESULT, 4, FG_Loss04
	goto_if_eq VAR_RESULT, 5, FG_Loss05
	goto_if_eq VAR_RESULT, 6, FG_Loss06
	goto_if_eq VAR_RESULT, 7, FG_Loss07
	goto_if_eq VAR_RESULT, 8, FG_Loss08
	goto_if_eq VAR_RESULT, 9, FG_Loss09
	goto_if_eq VAR_RESULT, 10, FG_Loss10
	goto_if_eq VAR_RESULT, 11, FG_Loss11
	goto_if_eq VAR_RESULT, 12, FG_Loss12
	goto_if_eq VAR_RESULT, 13, FG_Loss13
	goto_if_eq VAR_RESULT, 14, FG_Loss14
	goto_if_eq VAR_0x8008, 2, FG13_Repeat
	callnative Special_FriendsStoryNeedsIntroduction, requests_effects=1
	goto_if_eq VAR_RESULT, FALSE, FG13_Introduced
	fg_focus 3
	msgbox FG_Text_Introduction_1
	fg_focus 3
	msgbox FG_Text_Introduction_2
	fg_focus 3
	msgbox FG13_Text_LatePartners1
	fg_focus 3
	msgbox FG13_Text_LatePartners2
FG13_Introduced::
	setvar VAR_0x8004, 13
	setvar VAR_0x8005, 0
	closemessage
	callnative Special_FriendsStoryStage, requests_effects=1
	call FG_WaitSceneMovement
	delay 30
	fg_focus 0
	msgbox FG13_Text_Main01
	fg_focus 3
	msgbox FG13_Text_Main02
	fg_focus 0
	msgbox FG13_Text_Main03
	fg_focus 4
	msgbox FG13_Text_Main04
	fg_focus 0
	msgbox FG13_Text_Main05
	fg_focus 2
	msgbox FG13_Text_Main06
	fg_focus 3
	msgbox FG13_Text_Main07
	fg_focus 4
	msgbox FG13_Text_Main08
	setvar VAR_0x8004, 13
	setvar VAR_0x8005, 8
	closemessage
	callnative Special_FriendsStoryStage, requests_effects=1
	call FG_WaitSceneMovement
	delay 30
	fg_react 1, FG_Move_LookAround
	fg_focus 2
	msgbox FG13_Text_Main09
	fg_focus 1
	msgbox FG13_Text_Main10
	fg_focus 3
	msgbox FG13_Text_Main11
	fg_focus 1
	msgbox FG13_Text_Main12
	fg_focus 4
	msgbox FG13_Text_Main13
	fg_focus 1
	msgbox FG13_Text_Main14
	fg_focus 0
	msgbox FG13_Text_Main15
	setvar VAR_0x8004, 13
	setvar VAR_0x8005, 15
	closemessage
	callnative Special_FriendsStoryStage, requests_effects=1
	call FG_WaitSceneMovement
	delay 30
	fg_focus 3
	msgbox FG13_Text_Main16
	fg_focus 1
	msgbox FG13_Text_Main17
	fg_focus 4
	msgbox FG13_Text_Main18
	fg_focus 1
	msgbox FG13_Text_Main19
	fg_focus 3
	msgbox FG13_Text_Main20
	fg_focus 1
	msgbox FG13_Text_Main21
	setvar VAR_0x8004, 13
	setvar VAR_0x8005, 21
	closemessage
	callnative Special_FriendsStoryStage, requests_effects=1
	call FG_WaitSceneMovement
	delay 30
	fg_focus 0
	msgbox FG13_Text_Main22
	fg_focus 4
	msgbox FG13_Text_Main23
	fg_focus 3
	msgbox FG13_Text_Main24
	setvar VAR_0x8004, 13
	callnative Special_FriendsStoryMarkSeen, requests_effects=1
FG13_Repeat::
	fg_focus 3
	msgbox FG13_Text_Repeat
	goto FG_Release
FG14_Interact::
	lockall
	faceplayer
	setvar VAR_0x8004, 14
	callnative Special_FriendsStoryBegin, requests_effects=1
	goto_if_eq VAR_RESULT, 0, FG_Release
	copyvar VAR_0x8008, VAR_RESULT
	call FG_FrameCamera
	callnative Special_FriendsStoryGetPendingLoss, requests_effects=1
	goto_if_eq VAR_RESULT, 1, FG_Loss01
	goto_if_eq VAR_RESULT, 2, FG_Loss02
	goto_if_eq VAR_RESULT, 3, FG_Loss03
	goto_if_eq VAR_RESULT, 4, FG_Loss04
	goto_if_eq VAR_RESULT, 5, FG_Loss05
	goto_if_eq VAR_RESULT, 6, FG_Loss06
	goto_if_eq VAR_RESULT, 7, FG_Loss07
	goto_if_eq VAR_RESULT, 8, FG_Loss08
	goto_if_eq VAR_RESULT, 9, FG_Loss09
	goto_if_eq VAR_RESULT, 10, FG_Loss10
	goto_if_eq VAR_RESULT, 11, FG_Loss11
	goto_if_eq VAR_RESULT, 12, FG_Loss12
	goto_if_eq VAR_RESULT, 13, FG_Loss13
	goto_if_eq VAR_RESULT, 14, FG_Loss14
	goto_if_eq VAR_0x8008, 2, FG14_Repeat
	callnative Special_FriendsStoryNeedsIntroduction, requests_effects=1
	goto_if_eq VAR_RESULT, FALSE, FG14_Introduced
	fg_focus 3
	msgbox FG_Text_Introduction_1
	fg_focus 3
	msgbox FG_Text_Introduction_2
	fg_focus 3
	msgbox FG_Text_PartnersKanto
FG14_Introduced::
	setvar VAR_0x8004, 14
	setvar VAR_0x8005, 0
	closemessage
	callnative Special_FriendsStoryStage, requests_effects=1
	call FG_WaitSceneMovement
	delay 30
	fg_focus 4
	msgbox FG14_Text_Main01
	fg_focus 7
	msgbox FG14_Text_Main02
	fg_focus 4
	msgbox FG14_Text_Main03
	fg_focus 7
	msgbox FG14_Text_Main04
	fg_focus 3
	msgbox FG14_Text_Main05
	fg_focus 4
	msgbox FG14_Text_Main06
	fg_focus 7
	msgbox FG14_Text_Main07
	fg_focus 3
	msgbox FG14_Text_Main08
	fg_focus 5
	msgbox FG14_Text_Main09
	fg_focus 4
	msgbox FG14_Text_Main10
	fg_focus 5
	msgbox FG14_Text_Main11
	fg_focus 4
	msgbox FG14_Text_Main12
	setvar VAR_0x8004, 14
	setvar VAR_0x8005, 12
	closemessage
	callnative Special_FriendsStoryStage, requests_effects=1
	call FG_WaitSceneMovement
	delay 30
	fg_focus 7
	msgbox FG14_Text_Main13
	fg_focus 4
	msgbox FG14_Text_Main14
	fg_focus 7
	msgbox FG14_Text_Main15
	fg_focus 3
	msgbox FG14_Text_Main16
	fg_focus 5
	msgbox FG14_Text_Main17
	fg_focus 4
	msgbox FG14_Text_Main18
	fg_focus 7
	msgbox FG14_Text_Main19
	fg_focus 4
	msgbox FG14_Text_Main20
	setvar VAR_0x8004, 14
	callnative Special_FriendsStoryMarkSeen, requests_effects=1
FG14_Repeat::
	goto FG14_Menu
FG14_Menu::
	call FG_WaitSceneMovement
	closemessage
	callnative Special_FriendsStoryPrepareMenu, requests_effects=1
	multichoice 0, 0, MULTI_FG14, FALSE
	goto_if_eq VAR_RESULT, 0, FG14_Choice0
	goto_if_eq VAR_RESULT, 1, FG14_Choice1
	goto FG_Release
FG14_Choice0::
	call FG_FrameCamera
	fg_focus 4
	msgbox FG14_Text_Choice0_01
	fg_focus 3
	msgbox FG14_Text_Choice0_02
	fg_focus 5
	msgbox FG14_Text_Choice0_03
	goto FG_Release
FG14_Choice1::
	call FG_FrameCamera
	fg_focus 4
	msgbox FG14_Text_Choice1_01
	fg_focus 3
	msgbox FG14_Text_Choice1_02
	fg_focus 5
	msgbox FG14_Text_Choice1_03
	goto FG_Release
FG15_Interact::
	lockall
	faceplayer
	setvar VAR_0x8004, 15
	callnative Special_FriendsStoryBegin, requests_effects=1
	goto_if_eq VAR_RESULT, 0, FG_Release
	copyvar VAR_0x8008, VAR_RESULT
	call FG_FrameCamera
	callnative Special_FriendsStoryGetPendingLoss, requests_effects=1
	goto_if_eq VAR_RESULT, 1, FG_Loss01
	goto_if_eq VAR_RESULT, 2, FG_Loss02
	goto_if_eq VAR_RESULT, 3, FG_Loss03
	goto_if_eq VAR_RESULT, 4, FG_Loss04
	goto_if_eq VAR_RESULT, 5, FG_Loss05
	goto_if_eq VAR_RESULT, 6, FG_Loss06
	goto_if_eq VAR_RESULT, 7, FG_Loss07
	goto_if_eq VAR_RESULT, 8, FG_Loss08
	goto_if_eq VAR_RESULT, 9, FG_Loss09
	goto_if_eq VAR_RESULT, 10, FG_Loss10
	goto_if_eq VAR_RESULT, 11, FG_Loss11
	goto_if_eq VAR_RESULT, 12, FG_Loss12
	goto_if_eq VAR_RESULT, 13, FG_Loss13
	goto_if_eq VAR_RESULT, 14, FG_Loss14
	goto_if_eq VAR_0x8008, 2, FG15_Repeat
	callnative Special_FriendsStoryNeedsIntroduction, requests_effects=1
	goto_if_eq VAR_RESULT, FALSE, FG15_Introduced
	fg_focus 3
	msgbox FG_Text_Introduction_1
	fg_focus 3
	msgbox FG_Text_Introduction_2
	fg_focus 3
	msgbox FG15_Text_LatePartners1
	fg_focus 3
	msgbox FG15_Text_LatePartners2
FG15_Introduced::
	setvar VAR_0x8004, 15
	setvar VAR_0x8005, 0
	closemessage
	callnative Special_FriendsStoryStage, requests_effects=1
	call FG_WaitSceneMovement
	delay 30
	fg_focus 2
	msgbox FG15_Text_Main01
	fg_focus 3
	msgbox FG15_Text_Main02
	fg_focus 2
	msgbox FG15_Text_Main03
	fg_focus 3
	msgbox FG15_Text_Main04
	fg_focus 2
	msgbox FG15_Text_Main05
	fg_focus 3
	msgbox FG15_Text_Main06
	setvar VAR_0x8004, 15
	setvar VAR_0x8005, 6
	closemessage
	callnative Special_FriendsStoryStage, requests_effects=1
	call FG_WaitSceneMovement
	delay 30
	fg_focus 2
	msgbox FG15_Text_Main07
	fg_focus 3
	msgbox FG15_Text_Main08
	fg_focus 0
	msgbox FG15_Text_Main09
	fg_focus 2
	msgbox FG15_Text_Main10
	fg_focus 0
	msgbox FG15_Text_Main11
	fg_focus 3
	msgbox FG15_Text_Main12
	fg_react 2, FG_Move_QuietPause
	fg_focus 2
	msgbox FG15_Text_Main13
	fg_focus 3
	msgbox FG15_Text_Main14
	setvar VAR_0x8004, 15
	setvar VAR_0x8005, 14
	closemessage
	callnative Special_FriendsStoryStage, requests_effects=1
	call FG_WaitSceneMovement
	delay 30
	fg_focus 2
	msgbox FG15_Text_Main15
	fg_focus 3
	msgbox FG15_Text_Main16
	fg_focus 2
	msgbox FG15_Text_Main17
	fg_focus 0
	msgbox FG15_Text_Main18
	setvar VAR_0x8004, 15
	setvar VAR_0x8005, 18
	closemessage
	callnative Special_FriendsStoryStage, requests_effects=1
	call FG_WaitSceneMovement
	delay 30
	fg_focus 2
	msgbox FG15_Text_Main19
	fg_focus 3
	msgbox FG15_Text_Main20
	fg_focus 2
	msgbox FG15_Text_Main21
	fg_focus 0
	msgbox FG15_Text_Main22
	fg_focus 2
	msgbox FG15_Text_Main23
	setvar VAR_0x8004, 15
	setvar VAR_0x8005, 23
	closemessage
	callnative Special_FriendsStoryStage, requests_effects=1
	call FG_WaitSceneMovement
	delay 30
	setvar VAR_0x8004, 15
	callnative Special_FriendsStoryMarkSeen, requests_effects=1
FG15_Repeat::
	fg_focus 2
	msgbox FG15_Text_Repeat
	goto FG_Release
FG16_Interact::
	lockall
	faceplayer
	setvar VAR_0x8004, 16
	callnative Special_FriendsStoryBegin, requests_effects=1
	goto_if_eq VAR_RESULT, 0, FG_Release
	copyvar VAR_0x8008, VAR_RESULT
	call FG_FrameCamera
	callnative Special_FriendsStoryGetPendingLoss, requests_effects=1
	goto_if_eq VAR_RESULT, 1, FG_Loss01
	goto_if_eq VAR_RESULT, 2, FG_Loss02
	goto_if_eq VAR_RESULT, 3, FG_Loss03
	goto_if_eq VAR_RESULT, 4, FG_Loss04
	goto_if_eq VAR_RESULT, 5, FG_Loss05
	goto_if_eq VAR_RESULT, 6, FG_Loss06
	goto_if_eq VAR_RESULT, 7, FG_Loss07
	goto_if_eq VAR_RESULT, 8, FG_Loss08
	goto_if_eq VAR_RESULT, 9, FG_Loss09
	goto_if_eq VAR_RESULT, 10, FG_Loss10
	goto_if_eq VAR_RESULT, 11, FG_Loss11
	goto_if_eq VAR_RESULT, 12, FG_Loss12
	goto_if_eq VAR_RESULT, 13, FG_Loss13
	goto_if_eq VAR_RESULT, 14, FG_Loss14
	goto_if_eq VAR_0x8008, 2, FG16_Repeat
	callnative Special_FriendsStoryNeedsIntroduction, requests_effects=1
	goto_if_eq VAR_RESULT, FALSE, FG16_Introduced
	fg_focus 3
	msgbox FG_Text_Introduction_1
	fg_focus 3
	msgbox FG_Text_Introduction_2
	fg_focus 3
	msgbox FG16_Text_LatePartners1
	fg_focus 3
	msgbox FG16_Text_LatePartners2
FG16_Introduced::
	setvar VAR_0x8004, 16
	setvar VAR_0x8005, 0
	closemessage
	callnative Special_FriendsStoryStage, requests_effects=1
	call FG_WaitSceneMovement
	delay 30
	fg_focus 5
	msgbox FG16_Text_Main01
	fg_focus 3
	msgbox FG16_Text_Main02
	fg_focus 5
	msgbox FG16_Text_Main03
	fg_focus 3
	msgbox FG16_Text_Main04
	fg_focus 5
	msgbox FG16_Text_Main05
	setvar VAR_0x8004, 16
	setvar VAR_0x8005, 5
	closemessage
	callnative Special_FriendsStoryStage, requests_effects=1
	call FG_WaitSceneMovement
	delay 30
	fg_focus 2
	msgbox FG16_Text_Main06
	fg_focus 3
	msgbox FG16_Text_Main07
	fg_focus 2
	msgbox FG16_Text_Main08
	fg_focus 3
	msgbox FG16_Text_Main09
	fg_focus 1
	msgbox FG16_Text_Main10
	fg_focus 3
	msgbox FG16_Text_Main11
	fg_focus 1
	msgbox FG16_Text_Main12
	fg_focus 3
	msgbox FG16_Text_Main13
	fg_focus 1
	msgbox FG16_Text_Main14
	fg_focus 2
	msgbox FG16_Text_Main15
	fg_focus 3
	msgbox FG16_Text_Main16
	fg_focus 2
	msgbox FG16_Text_Main17
	fg_focus 1
	msgbox FG16_Text_Main18
	fg_focus 3
	msgbox FG16_Text_Main19
	fg_focus 1
	msgbox FG16_Text_LegalPsyduck
	fg_focus 2
	msgbox FG16_Text_LegalPrimeape
	setvar VAR_0x8004, 16
	setvar VAR_0x8005, 19
	closemessage
	callnative Special_FriendsStoryStage, requests_effects=1
	call FG_WaitSceneMovement
	delay 30
	fg_focus 1
	msgbox FG16_Text_Main20
	fg_focus 2
	msgbox FG16_Text_Main21
	fg_focus 3
	msgbox FG16_Text_Main22
	fg_focus 5
	msgbox FG16_Text_Main23
	fg_focus 1
	msgbox FG16_Text_Main24
	setvar VAR_0x8004, 16
	callnative Special_FriendsStoryMarkSeen, requests_effects=1
FG16_Repeat::
	goto FG16_Menu
FG16_Menu::
	call FG_WaitSceneMovement
	closemessage
	callnative Special_FriendsStoryPrepareMenu, requests_effects=1
	multichoice 0, 0, MULTI_FG16, FALSE
	goto_if_eq VAR_RESULT, 0, FG_Battle07
	goto_if_eq VAR_RESULT, 1, FG16_KeepPracticing
	goto FG_Release
FG16_KeepPracticing::
	call FG_FrameCamera
	fg_focus 1
	msgbox FG16_Text_Keep1
	fg_focus 3
	msgbox FG16_Text_Keep2
	fg_focus 1
	msgbox FG16_Text_Keep3
	goto FG_Release
FG17_Interact::
	lockall
	faceplayer
	setvar VAR_0x8004, 17
	callnative Special_FriendsStoryBegin, requests_effects=1
	goto_if_eq VAR_RESULT, 0, FG_Release
	copyvar VAR_0x8008, VAR_RESULT
	call FG_FrameCamera
	callnative Special_FriendsStoryGetPendingLoss, requests_effects=1
	goto_if_eq VAR_RESULT, 1, FG_Loss01
	goto_if_eq VAR_RESULT, 2, FG_Loss02
	goto_if_eq VAR_RESULT, 3, FG_Loss03
	goto_if_eq VAR_RESULT, 4, FG_Loss04
	goto_if_eq VAR_RESULT, 5, FG_Loss05
	goto_if_eq VAR_RESULT, 6, FG_Loss06
	goto_if_eq VAR_RESULT, 7, FG_Loss07
	goto_if_eq VAR_RESULT, 8, FG_Loss08
	goto_if_eq VAR_RESULT, 9, FG_Loss09
	goto_if_eq VAR_RESULT, 10, FG_Loss10
	goto_if_eq VAR_RESULT, 11, FG_Loss11
	goto_if_eq VAR_RESULT, 12, FG_Loss12
	goto_if_eq VAR_RESULT, 13, FG_Loss13
	goto_if_eq VAR_RESULT, 14, FG_Loss14
	goto_if_eq VAR_0x8008, 2, FG17_Repeat
	callnative Special_FriendsStoryNeedsIntroduction, requests_effects=1
	goto_if_eq VAR_RESULT, FALSE, FG17_Introduced
	fg_focus 3
	msgbox FG_Text_Introduction_1
	fg_focus 3
	msgbox FG_Text_Introduction_2
	fg_focus 3
	msgbox FG17_Text_LatePartners1
	fg_focus 3
	msgbox FG17_Text_LatePartners2
FG17_Introduced::
	setvar VAR_0x8004, 11
	callnative Special_FriendsStoryGetSeen, requests_effects=1
	goto_if_eq VAR_RESULT, TRUE, FG17_ReflectionKnown
	fg_focus 4
	msgbox FG17_Text_MissedReflection
FG17_ReflectionKnown::
	setvar VAR_0x8004, 17
	setvar VAR_0x8005, 0
	closemessage
	callnative Special_FriendsStoryStage, requests_effects=1
	call FG_WaitSceneMovement
	delay 30
	fg_focus 0
	msgbox FG17_Text_Main01
	fg_focus 3
	msgbox FG17_Text_Main02
	fg_focus 0
	msgbox FG17_Text_Main03
	fg_focus 3
	msgbox FG17_Text_Main04
	fg_focus 0
	msgbox FG17_Text_Main05
	fg_focus 3
	msgbox FG17_Text_Main06
	fg_focus 0
	msgbox FG17_Text_Main07
	fg_focus 3
	msgbox FG17_Text_Main08
	fg_focus 0
	msgbox FG17_Text_Main09
	fg_focus 4
	msgbox FG17_Text_Main10
	fg_focus 0
	msgbox FG17_Text_Main11
	fg_focus 4
	msgbox FG17_Text_Main12
	fg_focus 3
	msgbox FG17_Text_Main13
	fg_focus 0
	msgbox FG17_Text_Main14
	fg_focus 5
	msgbox FG17_Text_Main15
	fg_focus 4
	msgbox FG17_Text_Main16
	fg_focus 5
	msgbox FG17_Text_Main17
	setvar VAR_0x8004, 17
	setvar VAR_0x8005, 17
	closemessage
	callnative Special_FriendsStoryStage, requests_effects=1
	call FG_WaitSceneMovement
	delay 30
	fg_focus 0
	msgbox FG17_Text_Main18
	fg_focus 1
	msgbox FG17_Text_Main19
	fg_focus 3
	msgbox FG17_Text_Main20
	fg_focus 4
	msgbox FG17_Text_Main21
	fg_focus 0
	msgbox FG17_Text_Main22
	setvar VAR_0x8004, 17
	callnative Special_FriendsStoryMarkSeen, requests_effects=1
FG17_Repeat::
	fg_focus 0
	msgbox FG17_Text_Repeat
	goto FG_Release
FG18_Interact::
	lockall
	faceplayer
	setvar VAR_0x8004, 18
	callnative Special_FriendsStoryBegin, requests_effects=1
	goto_if_eq VAR_RESULT, 0, FG_Release
	copyvar VAR_0x8008, VAR_RESULT
	call FG_FrameCamera
	callnative Special_FriendsStoryGetPendingLoss, requests_effects=1
	goto_if_eq VAR_RESULT, 1, FG_Loss01
	goto_if_eq VAR_RESULT, 2, FG_Loss02
	goto_if_eq VAR_RESULT, 3, FG_Loss03
	goto_if_eq VAR_RESULT, 4, FG_Loss04
	goto_if_eq VAR_RESULT, 5, FG_Loss05
	goto_if_eq VAR_RESULT, 6, FG_Loss06
	goto_if_eq VAR_RESULT, 7, FG_Loss07
	goto_if_eq VAR_RESULT, 8, FG_Loss08
	goto_if_eq VAR_RESULT, 9, FG_Loss09
	goto_if_eq VAR_RESULT, 10, FG_Loss10
	goto_if_eq VAR_RESULT, 11, FG_Loss11
	goto_if_eq VAR_RESULT, 12, FG_Loss12
	goto_if_eq VAR_RESULT, 13, FG_Loss13
	goto_if_eq VAR_RESULT, 14, FG_Loss14
	goto_if_eq VAR_0x8008, 2, FG18_Repeat
	callnative Special_FriendsStoryNeedsIntroduction, requests_effects=1
	goto_if_eq VAR_RESULT, FALSE, FG18_Introduced
	fg_focus 3
	msgbox FG_Text_Introduction_1
	fg_focus 3
	msgbox FG_Text_Introduction_2
	fg_focus 3
	msgbox FG_Text_PartnersKanto
FG18_Introduced::
	setvar VAR_0x8004, 18
	setvar VAR_0x8005, 0
	closemessage
	callnative Special_FriendsStoryStage, requests_effects=1
	call FG_WaitSceneMovement
	delay 30
	fg_focus 7
	msgbox FG18_Text_Main01
	fg_focus 6
	msgbox FG18_Text_Main02
	fg_focus 7
	msgbox FG18_Text_Main03
	fg_focus 6
	msgbox FG18_Text_Main04
	fg_focus 3
	msgbox FG18_Text_Main05
	fg_focus 6
	msgbox FG18_Text_Main06
	fg_focus 3
	msgbox FG18_Text_Main07
	fg_focus 6
	msgbox FG18_Text_Main08
	setvar VAR_0x8004, 18
	setvar VAR_0x8005, 8
	closemessage
	callnative Special_FriendsStoryStage, requests_effects=1
	call FG_WaitSceneMovement
	delay 30
	fg_focus 7
	msgbox FG18_Text_Main09
	fg_focus 6
	msgbox FG18_Text_Main10
	fg_focus 7
	msgbox FG18_Text_Main11
	fg_focus 6
	msgbox FG18_Text_Main12
	fg_focus 3
	msgbox FG18_Text_Main13
	fg_focus 6
	msgbox FG18_Text_Main14
	fg_focus 3
	msgbox FG18_Text_Main15
	fg_focus 6
	msgbox FG18_Text_Main16
	fg_focus 3
	msgbox FG18_Text_Main17
	fg_walk_out 6, DIR_EAST
	fg_focus 6
	msgbox FG18_Text_Main18
	setvar VAR_0x8004, 18
	setvar VAR_0x8005, 18
	closemessage
	callnative Special_FriendsStoryStage, requests_effects=1
	call FG_WaitSceneMovement
	delay 30
	fg_focus 3
	msgbox FG18_Text_Main19
	fg_walk_back 6, DIR_WEST
	fg_focus 6
	msgbox FG18_Text_Main20
	setvar VAR_0x8004, 18
	callnative Special_FriendsStoryMarkSeen, requests_effects=1
FG18_Repeat::
	goto FG18_Menu
FG18_Menu::
	call FG_WaitSceneMovement
	closemessage
	callnative Special_FriendsStoryPrepareMenu, requests_effects=1
	multichoice 0, 0, MULTI_FG18, FALSE
	goto_if_eq VAR_RESULT, 0, FG18_Choice0
	goto_if_eq VAR_RESULT, 1, FG18_Choice1
	goto FG_Release
FG18_Choice0::
	call FG_FrameCamera
	fg_focus 6
	msgbox FG18_Text_Choice0_1
	fg_focus 3
	msgbox FG18_Text_Choice0_2
	fg_focus 6
	msgbox FG18_Text_Choice0_3
	goto FG_Release
FG18_Choice1::
	call FG_FrameCamera
	fg_focus 6
	msgbox FG18_Text_Choice1_1
	fg_focus 3
	msgbox FG18_Text_Choice1_2
	fg_focus 6
	msgbox FG18_Text_Choice1_3
	goto FG_Release
FG19_Interact::
	lockall
	faceplayer
	setvar VAR_0x8004, 19
	callnative Special_FriendsStoryBegin, requests_effects=1
	goto_if_eq VAR_RESULT, 0, FG_Release
	copyvar VAR_0x8008, VAR_RESULT
	call FG_FrameCamera
	callnative Special_FriendsStoryGetPendingLoss, requests_effects=1
	goto_if_eq VAR_RESULT, 1, FG_Loss01
	goto_if_eq VAR_RESULT, 2, FG_Loss02
	goto_if_eq VAR_RESULT, 3, FG_Loss03
	goto_if_eq VAR_RESULT, 4, FG_Loss04
	goto_if_eq VAR_RESULT, 5, FG_Loss05
	goto_if_eq VAR_RESULT, 6, FG_Loss06
	goto_if_eq VAR_RESULT, 7, FG_Loss07
	goto_if_eq VAR_RESULT, 8, FG_Loss08
	goto_if_eq VAR_RESULT, 9, FG_Loss09
	goto_if_eq VAR_RESULT, 10, FG_Loss10
	goto_if_eq VAR_RESULT, 11, FG_Loss11
	goto_if_eq VAR_RESULT, 12, FG_Loss12
	goto_if_eq VAR_RESULT, 13, FG_Loss13
	goto_if_eq VAR_RESULT, 14, FG_Loss14
	goto_if_eq VAR_0x8008, 2, FG19_Repeat
	callnative Special_FriendsStoryNeedsIntroduction, requests_effects=1
	goto_if_eq VAR_RESULT, FALSE, FG19_Introduced
	fg_focus 3
	msgbox FG_Text_Introduction_1
	fg_focus 3
	msgbox FG_Text_Introduction_2
	fg_focus 3
	msgbox FG_Text_PartnersKanto
FG19_Introduced::
	setvar VAR_0x8004, 19
	setvar VAR_0x8005, 0
	closemessage
	callnative Special_FriendsStoryStage, requests_effects=1
	call FG_WaitSceneMovement
	delay 30
	fg_focus 0
	msgbox FG19_Text_Main01
	fg_focus 3
	msgbox FG19_Text_Main02
	fg_focus 0
	msgbox FG19_Text_Main03
	fg_focus 3
	msgbox FG19_Text_Main04
	setvar VAR_0x8004, 19
	setvar VAR_0x8005, 4
	closemessage
	callnative Special_FriendsStoryStage, requests_effects=1
	call FG_WaitSceneMovement
	delay 30
	fg_focus 2
	msgbox FG19_Text_Main05
	fg_focus 3
	msgbox FG19_Text_Main06
	fg_focus 2
	msgbox FG19_Text_Main07
	setvar VAR_0x8004, 19
	setvar VAR_0x8005, 7
	closemessage
	callnative Special_FriendsStoryStage, requests_effects=1
	call FG_WaitSceneMovement
	delay 30
	fg_focus 5
	msgbox FG19_Text_Main08
	fg_focus 4
	msgbox FG19_Text_Main09
	fg_focus 5
	msgbox FG19_Text_Main10
	fg_focus 4
	msgbox FG19_Text_Main11
	fg_focus 5
	msgbox FG19_Text_Main12
	setvar VAR_0x8004, 19
	setvar VAR_0x8005, 12
	closemessage
	callnative Special_FriendsStoryStage, requests_effects=1
	call FG_WaitSceneMovement
	delay 30
	fg_focus 6
	msgbox FG19_Text_Main13
	fg_focus 1
	msgbox FG19_Text_Main14
	fg_focus 6
	msgbox FG19_Text_Main15
	fg_focus 1
	msgbox FG19_Text_Main16
	setvar VAR_0x8004, 19
	setvar VAR_0x8005, 16
	closemessage
	callnative Special_FriendsStoryStage, requests_effects=1
	call FG_WaitSceneMovement
	delay 30
	setvar VAR_0x8004, 19
	callnative Special_FriendsStoryMarkSeen, requests_effects=1
FG19_Repeat::
	fg_focus 3
	msgbox FG19_Text_Repeat
	goto FG_Release
FG20_Interact::
	lockall
	faceplayer
	setvar VAR_0x8004, 20
	callnative Special_FriendsStoryBegin, requests_effects=1
	goto_if_eq VAR_RESULT, 0, FG_Release
	copyvar VAR_0x8008, VAR_RESULT
	call FG_FrameCamera
	callnative Special_FriendsStoryGetPendingLoss, requests_effects=1
	goto_if_eq VAR_RESULT, 1, FG_Loss01
	goto_if_eq VAR_RESULT, 2, FG_Loss02
	goto_if_eq VAR_RESULT, 3, FG_Loss03
	goto_if_eq VAR_RESULT, 4, FG_Loss04
	goto_if_eq VAR_RESULT, 5, FG_Loss05
	goto_if_eq VAR_RESULT, 6, FG_Loss06
	goto_if_eq VAR_RESULT, 7, FG_Loss07
	goto_if_eq VAR_RESULT, 8, FG_Loss08
	goto_if_eq VAR_RESULT, 9, FG_Loss09
	goto_if_eq VAR_RESULT, 10, FG_Loss10
	goto_if_eq VAR_RESULT, 11, FG_Loss11
	goto_if_eq VAR_RESULT, 12, FG_Loss12
	goto_if_eq VAR_RESULT, 13, FG_Loss13
	goto_if_eq VAR_RESULT, 14, FG_Loss14
	goto_if_eq VAR_0x8008, 2, FG20_Repeat
	callnative Special_FriendsStoryNeedsIntroduction, requests_effects=1
	goto_if_eq VAR_RESULT, FALSE, FG20_Introduced
	fg_focus 3
	msgbox FG_Text_Introduction_1
	fg_focus 3
	msgbox FG_Text_Introduction_2
	fg_focus 3
	msgbox FG20_Text_LatePartners1
	fg_focus 3
	msgbox FG20_Text_LatePartners2
FG20_Introduced::
	setvar VAR_0x8004, 20
	setvar VAR_0x8005, 0
	closemessage
	callnative Special_FriendsStoryStage, requests_effects=1
	call FG_WaitSceneMovement
	delay 30
	fg_focus 3
	msgbox FG20_Text_Main01
	fg_focus 0
	msgbox FG20_Text_Main02
	fg_focus 3
	msgbox FG20_Text_Main03
	fg_focus 0
	msgbox FG20_Text_Main04
	fg_focus 3
	msgbox FG20_Text_Main05
	fg_focus 0
	msgbox FG20_Text_Main06
	setvar VAR_0x8004, 20
	setvar VAR_0x8005, 6
	closemessage
	callnative Special_FriendsStoryStage, requests_effects=1
	call FG_WaitSceneMovement
	delay 30
	fg_focus 2
	msgbox FG20_Text_Main07
	fg_focus 3
	msgbox FG20_Text_Main08
	fg_focus 2
	msgbox FG20_Text_Main09
	fg_focus 3
	msgbox FG20_Text_Main10
	fg_focus 1
	msgbox FG20_Text_Main11
	fg_focus 2
	msgbox FG20_Text_Main12
	fg_focus 1
	msgbox FG20_Text_Main13
	fg_focus 0
	msgbox FG20_Text_Main14
	setvar VAR_0x8004, 20
	setvar VAR_0x8005, 14
	closemessage
	callnative Special_FriendsStoryStage, requests_effects=1
	call FG_WaitSceneMovement
	delay 30
	fg_focus 5
	msgbox FG20_Text_Main15
	fg_focus 3
	msgbox FG20_Text_Main16
	fg_focus 5
	msgbox FG20_Text_Main17
	fg_focus 4
	msgbox FG20_Text_Main18
	fg_focus 5
	msgbox FG20_Text_Main19
	fg_walk_out 3, DIR_SOUTH
	fg_focus 4
	msgbox FG20_Text_Main20
	setvar VAR_0x8004, 20
	setvar VAR_0x8005, 20
	closemessage
	callnative Special_FriendsStoryStage, requests_effects=1
	call FG_WaitSceneMovement
	delay 30
	fg_focus 3
	msgbox FG20_Text_Main21
	fg_walk_back 3, DIR_NORTH
	fg_focus 0
	msgbox FG20_Text_Main22
	setvar VAR_0x8004, 20
	callnative Special_FriendsStoryMarkSeen, requests_effects=1
FG20_Repeat::
	goto FG20_Menu
FG20_Menu::
	call FG_WaitSceneMovement
	closemessage
	callnative Special_FriendsStoryPrepareMenu, requests_effects=1
	multichoice 0, 0, MULTI_FG20, FALSE
	goto_if_eq VAR_RESULT, 0, FG_FinalMenu
	goto_if_eq VAR_RESULT, 1, FG20_HowDoing
	goto_if_eq VAR_RESULT, 2, FG20_Later
	goto FG_Release
FG20_HowDoing::
	call FG_FrameCamera
	fg_focus 3
	msgbox FG20_Text_How1
	fg_focus 0
	msgbox FG20_Text_How2
	fg_focus 4
	msgbox FG20_Text_How3
	goto FG_Release
FG20_Later::
	call FG_FrameCamera
	fg_focus 0
	msgbox FG20_Text_Later1
	fg_focus 2
	msgbox FG20_Text_Later2
	goto FG_Release
FG21_Interact::
	lockall
	faceplayer
	setvar VAR_0x8004, 21
	callnative Special_FriendsStoryBegin, requests_effects=1
	goto_if_eq VAR_RESULT, 0, FG_Release
	copyvar VAR_0x8008, VAR_RESULT
	call FG_FrameCamera
	callnative Special_FriendsStoryGetPendingLoss, requests_effects=1
	goto_if_eq VAR_RESULT, 1, FG_Loss01
	goto_if_eq VAR_RESULT, 2, FG_Loss02
	goto_if_eq VAR_RESULT, 3, FG_Loss03
	goto_if_eq VAR_RESULT, 4, FG_Loss04
	goto_if_eq VAR_RESULT, 5, FG_Loss05
	goto_if_eq VAR_RESULT, 6, FG_Loss06
	goto_if_eq VAR_RESULT, 7, FG_Loss07
	goto_if_eq VAR_RESULT, 8, FG_Loss08
	goto_if_eq VAR_RESULT, 9, FG_Loss09
	goto_if_eq VAR_RESULT, 10, FG_Loss10
	goto_if_eq VAR_RESULT, 11, FG_Loss11
	goto_if_eq VAR_RESULT, 12, FG_Loss12
	goto_if_eq VAR_RESULT, 13, FG_Loss13
	goto_if_eq VAR_RESULT, 14, FG_Loss14
	callnative Special_FriendsStoryInvitation, requests_effects=1
	goto_if_eq VAR_RESULT, FALSE, FG21_Menu
	callnative Special_FriendsStoryNeedsIntroduction, requests_effects=1
	goto_if_eq VAR_RESULT, FALSE, FG21_Introduced
	fg_focus 3
	msgbox FG21_Text_LateIntroduction1
	fg_focus 4
	msgbox FG21_Text_LateIntroduction2
	fg_focus 1
	msgbox FG21_Text_LateIntroduction3
	fg_focus 3
	msgbox FG_Text_PartnersKanto
FG21_Introduced::
	setvar VAR_0x8004, 21
	setvar VAR_0x8005, 0
	closemessage
	callnative Special_FriendsStoryStage, requests_effects=1
	call FG_WaitSceneMovement
	delay 30
	fg_focus 0
	msgbox FG21_Text_Main01
	fg_focus 3
	msgbox FG21_Text_Main02
	fg_walk_out 0, DIR_NORTH
	fg_focus 0
	msgbox FG21_Text_Main03
	fg_focus 3
	msgbox FG21_Text_Main04
	fg_focus 1
	msgbox FG21_Text_Main05
	fg_focus 4
	msgbox FG21_Text_Main06
	fg_focus 1
	msgbox FG21_Text_Main07
	setvar VAR_0x8004, 21
	setvar VAR_0x8005, 7
	closemessage
	callnative Special_FriendsStoryStage, requests_effects=1
	call FG_WaitSceneMovement
	delay 30
	fg_walk_back 0, DIR_SOUTH
	fg_focus 6
	msgbox FG21_Text_Main08
	fg_focus 3
	msgbox FG21_Text_Main09
	fg_focus 6
	msgbox FG21_Text_Main10
	fg_focus 3
	msgbox FG21_Text_Main11
	setvar VAR_0x8004, 21
	setvar VAR_0x8005, 11
	closemessage
	callnative Special_FriendsStoryStage, requests_effects=1
	call FG_WaitSceneMovement
	delay 30
	fg_focus 4
	msgbox FG21_Text_Main12
	fg_focus 0
	msgbox FG21_Text_Main13
	fg_focus 3
	msgbox FG21_Text_Main14
	fg_focus 0
	msgbox FG21_Text_Main15
	fg_focus 5
	msgbox FG21_Text_Main16
	fg_focus 4
	msgbox FG21_Text_Main17
	fg_focus 5
	msgbox FG21_Text_Main18
	fg_focus 0
	msgbox FG21_Text_Main19
	fg_focus 3
	msgbox FG21_Text_Main20
	setvar VAR_0x8004, 21
	setvar VAR_0x8005, 20
	closemessage
	callnative Special_FriendsStoryStage, requests_effects=1
	call FG_WaitSceneMovement
	delay 30
	fg_focus 2
	msgbox FG21_Text_Main21
	fg_focus 3
	msgbox FG21_Text_Main22
	fg_focus 2
	msgbox FG21_Text_Main23
	setvar VAR_0x8004, 21
	setvar VAR_0x8005, 23
	closemessage
	callnative Special_FriendsStoryStage, requests_effects=1
	call FG_WaitSceneMovement
	delay 30
	fg_focus 4
	msgbox FG21_Text_Main24
	fg_focus 1
	msgbox FG21_Text_Main25
	fg_focus 0
	msgbox FG21_Text_Main26
FG21_Repeat::
	goto FG21_Menu
FG21_Menu::
	call FG_WaitSceneMovement
	closemessage
	callnative Special_FriendsStoryPrepareMenu, requests_effects=1
	multichoice 0, 0, MULTI_FG21, FALSE
	goto_if_eq VAR_RESULT, 0, FG21_SafeTravels
	goto_if_eq VAR_RESULT, 1, FG21_LastBattle
	goto_if_eq VAR_RESULT, 2, FG21_Stay
	goto FG_Release
FG21_SafeTravels::
	call FG_FrameCamera
	callnative Special_FriendsStoryNeedsIntroduction, requests_effects=1
	goto_if_eq VAR_RESULT, TRUE, FG21_LateThanks
	fg_focus 3
	msgbox FG21_Text_PriorThanks
	goto FG21_Crossing
FG21_LateThanks::
	fg_focus 3
	msgbox FG21_Text_LateThanks
FG21_Crossing::
	fg_focus 2
	msgbox FG21_Text_Tim1
	fg_focus 6
	msgbox FG21_Text_Tim2
	setvar VAR_0x8004, 21
	setvar VAR_0x8005, 30
	closemessage
	callnative Special_FriendsStoryStage, requests_effects=1
	call FG_WaitSceneMovement
	delay 30
	setvar VAR_0x8004, 21
	setvar VAR_0x8005, 31
	closemessage
	callnative Special_FriendsStoryStage, requests_effects=1
	call FG_WaitSceneMovement
	delay 30
	setvar VAR_0x8004, 21
	setvar VAR_0x8005, 32
	closemessage
	callnative Special_FriendsStoryStage, requests_effects=1
	call FG_WaitSceneMovement
	delay 30
	setvar VAR_0x8004, 21
	setvar VAR_0x8005, 33
	closemessage
	callnative Special_FriendsStoryStage, requests_effects=1
	call FG_WaitSceneMovement
	delay 30
	setvar VAR_0x8004, 21
	setvar VAR_0x8005, 34
	closemessage
	callnative Special_FriendsStoryStage, requests_effects=1
	call FG_WaitSceneMovement
	delay 30
	setvar VAR_0x8004, 21
	setvar VAR_0x8005, 35
	closemessage
	callnative Special_FriendsStoryStage, requests_effects=1
	call FG_WaitSceneMovement
	delay 30
	setvar VAR_0x8004, 21
	setvar VAR_0x8005, 36
	closemessage
	callnative Special_FriendsStoryStage, requests_effects=1
	call FG_WaitSceneMovement
	delay 30
	setvar VAR_0x8004, 21
	setvar VAR_0x8005, 37
	closemessage
	callnative Special_FriendsStoryStage, requests_effects=1
	call FG_WaitSceneMovement
	delay 30
	setvar VAR_0x8004, 21
	callnative Special_FriendsStoryMarkSeen, requests_effects=1
	goto FG_Release
FG21_LastBattle::
	call FG_FrameCamera
	fg_focus 3
	msgbox FG21_Text_LastBattle
	goto FG_FinalMenu
FG21_Stay::
	call FG_FrameCamera
	fg_focus 0
	msgbox FG21_Text_Stay1
	fg_focus 3
	msgbox FG21_Text_Stay2
	goto FG_Release
FG22_Interact::
	lockall
	faceplayer
	setvar VAR_0x8004, 22
	callnative Special_FriendsStoryBegin, requests_effects=1
	goto_if_eq VAR_RESULT, 0, FG_Release
	copyvar VAR_0x8008, VAR_RESULT
	call FG_FrameCamera
	callnative Special_FriendsStoryGetPendingLoss, requests_effects=1
	goto_if_eq VAR_RESULT, 1, FG_Loss01
	goto_if_eq VAR_RESULT, 2, FG_Loss02
	goto_if_eq VAR_RESULT, 3, FG_Loss03
	goto_if_eq VAR_RESULT, 4, FG_Loss04
	goto_if_eq VAR_RESULT, 5, FG_Loss05
	goto_if_eq VAR_RESULT, 6, FG_Loss06
	goto_if_eq VAR_RESULT, 7, FG_Loss07
	goto_if_eq VAR_RESULT, 8, FG_Loss08
	goto_if_eq VAR_RESULT, 9, FG_Loss09
	goto_if_eq VAR_RESULT, 10, FG_Loss10
	goto_if_eq VAR_RESULT, 11, FG_Loss11
	goto_if_eq VAR_RESULT, 12, FG_Loss12
	goto_if_eq VAR_RESULT, 13, FG_Loss13
	goto_if_eq VAR_RESULT, 14, FG_Loss14
	goto_if_eq VAR_0x8008, 2, FG22_Repeat
	callnative Special_FriendsStoryNeedsIntroduction, requests_effects=1
	goto_if_eq VAR_RESULT, FALSE, FG22_Introduced
	fg_focus 3
	msgbox FG_Text_Introduction_1
	fg_focus 3
	msgbox FG_Text_Introduction_2
	fg_focus 3
	msgbox FG_Text_PartnersKanto
FG22_Introduced::
	setvar VAR_0x8004, 22
	setvar VAR_0x8005, 0
	closemessage
	callnative Special_FriendsStoryStage, requests_effects=1
	call FG_WaitSceneMovement
	delay 30
	fg_focus 0
	msgbox FG22_Text_Main01
	fg_focus 3
	msgbox FG22_Text_Main02
	fg_focus 0
	msgbox FG22_Text_Main03
	fg_focus 3
	msgbox FG22_Text_Main04
	fg_focus 0
	msgbox FG22_Text_Main05
	fg_focus 3
	msgbox FG22_Text_Main06
	fg_focus 0
	msgbox FG22_Text_Main07
	setvar VAR_0x8004, 22
	setvar VAR_0x8005, 7
	closemessage
	callnative Special_FriendsStoryStage, requests_effects=1
	call FG_WaitSceneMovement
	delay 30
	fg_focus 4
	msgbox FG22_Text_Main08
	fg_focus 5
	msgbox FG22_Text_Main09
	fg_focus 4
	msgbox FG22_Text_Main10
	fg_react 5, FG_Move_Emphatic
	fg_focus 5
	msgbox FG22_Text_Main11
	fg_focus 4
	msgbox FG22_Text_Main12
	fg_focus 5
	msgbox FG22_Text_Main13
	fg_focus 4
	msgbox FG22_Text_Main14
	fg_focus 5
	msgbox FG22_Text_Main15
	setvar VAR_0x8004, 22
	setvar VAR_0x8005, 15
	closemessage
	callnative Special_FriendsStoryStage, requests_effects=1
	call FG_WaitSceneMovement
	delay 30
	fg_walk_out 3, DIR_EAST
	fg_focus 3
	msgbox FG22_Text_Main16
	fg_focus 0
	msgbox FG22_Text_Main17
	fg_focus 3
	msgbox FG22_Text_Main18
	fg_focus 0
	msgbox FG22_Text_Main19
	fg_walk_back 3, DIR_WEST
	fg_focus 4
	msgbox FG22_Text_Main20
	fg_focus 3
	msgbox FG22_Text_Main21
	fg_focus 0
	msgbox FG22_Text_Main22
	setvar VAR_0x8004, 22
	callnative Special_FriendsStoryMarkSeen, requests_effects=1
FG22_Repeat::
	goto FG22_Menu
FG22_Menu::
	call FG_WaitSceneMovement
	closemessage
	callnative Special_FriendsStoryPrepareMenu, requests_effects=1
	multichoice 0, 0, MULTI_FG22, FALSE
	goto_if_eq VAR_RESULT, 0, FG_FinalMenu
	goto_if_eq VAR_RESULT, 1, FG22_CatchUp
	goto_if_eq VAR_RESULT, 2, FG22_Bye
	goto FG_Release
FG22_CatchUp::
	call FG_FrameCamera
	fg_focus 4
	msgbox FG22_Text_Catch1
	fg_focus 0
	msgbox FG22_Text_Catch2
	fg_focus 3
	msgbox FG22_Text_Catch3
	goto FG_Release
FG22_Bye::
	call FG_FrameCamera
	fg_focus 0
	msgbox FG22_Text_Bye1
	fg_focus 3
	msgbox FG22_Text_Bye2
	goto FG_Release
FG_FinalMenu::
	callnative Special_FriendsStoryCanFinalBattle, requests_effects=1
	goto_if_eq VAR_RESULT, FALSE, FG_Release
	call FG_WaitSceneMovement
	closemessage
	callnative Special_FriendsStoryPrepareMenu, requests_effects=1
	multichoicegrid 0, 0, MULTI_FG_OPPONENTS, 2, FALSE
	goto_if_eq VAR_RESULT, 0, FG_FinalInvite0
	goto_if_eq VAR_RESULT, 1, FG_FinalInvite1
	goto_if_eq VAR_RESULT, 2, FG_FinalInvite2
	goto_if_eq VAR_RESULT, 3, FG_FinalInvite3
	goto_if_eq VAR_RESULT, 4, FG_FinalInvite4
	goto_if_eq VAR_RESULT, 5, FG_FinalInvite5
	goto_if_eq VAR_RESULT, 6, FG_FinalInvite6
	goto_if_eq VAR_RESULT, 7, FG_Release
	goto FG_Release
FG_FinalInvite0::
	call FG_FrameCamera
	fg_focus 0
	msgbox FG_Text_FinalInvitation0
	call FG_WaitSceneMovement
	msgbox FG_Text_BattleOrLater, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, FG_Release
	goto FG_Battle08
FG_FinalInvite1::
	call FG_FrameCamera
	fg_focus 4
	msgbox FG_Text_FinalInvitation1
	call FG_WaitSceneMovement
	msgbox FG_Text_BattleOrLater, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, FG_Release
	goto FG_Battle09
FG_FinalInvite2::
	call FG_FrameCamera
	fg_focus 6
	msgbox FG_Text_FinalInvitation2
	call FG_WaitSceneMovement
	msgbox FG_Text_BattleOrLater, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, FG_Release
	goto FG_Battle10
FG_FinalInvite3::
	call FG_FrameCamera
	fg_focus 5
	msgbox FG_Text_FinalInvitation3
	call FG_WaitSceneMovement
	msgbox FG_Text_BattleOrLater, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, FG_Release
	goto FG_Battle11
FG_FinalInvite4::
	call FG_FrameCamera
	fg_focus 3
	msgbox FG_Text_FinalInvitation4
	call FG_WaitSceneMovement
	msgbox FG_Text_BattleOrLater, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, FG_Release
	goto FG_Battle12
FG_FinalInvite5::
	call FG_FrameCamera
	fg_focus 2
	msgbox FG_Text_FinalInvitation5
	call FG_WaitSceneMovement
	msgbox FG_Text_BattleOrLater, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, FG_Release
	goto FG_Battle13
FG_FinalInvite6::
	call FG_FrameCamera
	fg_focus 1
	msgbox FG_Text_FinalInvitation6
	call FG_WaitSceneMovement
	msgbox FG_Text_BattleOrLater, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, FG_Release
	goto FG_Battle14
FG_Battle01::
	setvar VAR_0x8004, 626
	callnative Special_FriendsStoryCanBattle, requests_effects=1
	goto_if_eq VAR_RESULT, FALSE, FG_CannotBattle
	call FG_ReturnCamera
	closemessage
	trainerbattle_no_intro 626, FG_Battle01_Won01
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_ne VAR_RESULT, B_OUTCOME_WON, FG_Release
	call FG_FrameCamera
	fg_focus 3
	msgbox FG_Battle01_Won02
	fg_focus 0
	msgbox FG_Battle01_Won03
	fg_focus 3
	msgbox FG_Battle01_Won04
	fg_focus 0
	msgbox FG_Battle01_Won05
	fg_focus 3
	msgbox FG_Battle01_Won06
	fg_focus 0
	msgbox FG_Battle01_Won07
	goto FG_Release
FG_Loss01::
	fg_focus 0
	msgbox FG_Battle01_Lost01
	fg_focus 3
	msgbox FG_Battle01_Lost02
	fg_focus 0
	msgbox FG_Battle01_Lost03
	fg_focus 3
	msgbox FG_Battle01_Lost04
	fg_focus 0
	msgbox FG_Battle01_Lost05
	callnative Special_FriendsStoryClearPendingLoss, requests_effects=1
	goto FG_Release
FG_Battle02::
	setvar VAR_0x8004, 627
	callnative Special_FriendsStoryCanBattle, requests_effects=1
	goto_if_eq VAR_RESULT, FALSE, FG_CannotBattle
	call FG_ReturnCamera
	closemessage
	trainerbattle_no_intro 627, FG_Battle02_Won01
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_ne VAR_RESULT, B_OUTCOME_WON, FG_Release
	call FG_FrameCamera
	fg_focus 3
	msgbox FG_Battle02_Won02
	fg_focus 2
	msgbox FG_Battle02_Won03
	fg_focus 3
	msgbox FG_Battle02_Won04
	fg_focus 2
	msgbox FG_Battle02_Won05
	fg_focus 3
	msgbox FG_Battle02_Won06
	fg_focus 2
	msgbox FG_Battle02_Won07
	goto FG_Release
FG_Loss02::
	fg_focus 2
	msgbox FG_Battle02_Lost01
	fg_focus 3
	msgbox FG_Battle02_Lost02
	fg_focus 2
	msgbox FG_Battle02_Lost03
	fg_focus 3
	msgbox FG_Battle02_Lost04
	fg_focus 2
	msgbox FG_Battle02_Lost05
	callnative Special_FriendsStoryClearPendingLoss, requests_effects=1
	goto FG_Release
FG_Battle03::
	setvar VAR_0x8004, 628
	callnative Special_FriendsStoryCanBattle, requests_effects=1
	goto_if_eq VAR_RESULT, FALSE, FG_CannotBattle
	call FG_ReturnCamera
	closemessage
	trainerbattle_no_intro 628, FG_Battle03_Won01
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_ne VAR_RESULT, B_OUTCOME_WON, FG_Release
	call FG_FrameCamera
	fg_focus 0
	msgbox FG_Battle03_Won02
	fg_focus 3
	msgbox FG_Battle03_Won03
	fg_focus 0
	msgbox FG_Battle03_Won04
	fg_focus 3
	msgbox FG_Battle03_Won05
	fg_focus 0
	msgbox FG_Battle03_Won06
	goto FG_Release
FG_Loss03::
	fg_focus 3
	msgbox FG_Battle03_Lost01
	fg_focus 0
	msgbox FG_Battle03_Lost02
	fg_focus 3
	msgbox FG_Battle03_Lost03
	fg_focus 0
	msgbox FG_Battle03_Lost04
	fg_focus 3
	msgbox FG_Battle03_Lost05
	callnative Special_FriendsStoryClearPendingLoss, requests_effects=1
	goto FG_Release
FG_Battle04::
	setvar VAR_0x8004, 629
	callnative Special_FriendsStoryCanBattle, requests_effects=1
	goto_if_eq VAR_RESULT, FALSE, FG_CannotBattle
	call FG_ReturnCamera
	closemessage
	trainerbattle_no_intro 629, FG_Battle04_Won01
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_ne VAR_RESULT, B_OUTCOME_WON, FG_Release
	call FG_FrameCamera
	fg_focus 4
	msgbox FG_Battle04_Won02
	fg_focus 5
	msgbox FG_Battle04_Won03
	fg_focus 4
	msgbox FG_Battle04_Won04
	fg_focus 5
	msgbox FG_Battle04_Won05
	fg_focus 4
	msgbox FG_Battle04_Won06
	fg_focus 5
	msgbox FG_Battle04_Won07
	goto FG_Release
FG_Loss04::
	fg_focus 5
	msgbox FG_Battle04_Lost01
	fg_focus 4
	msgbox FG_Battle04_Lost02
	fg_focus 5
	msgbox FG_Battle04_Lost03
	fg_focus 4
	msgbox FG_Battle04_Lost04
	fg_focus 5
	msgbox FG_Battle04_Lost05
	fg_focus 5
	msgbox FG_Battle04_Lost06
	callnative Special_FriendsStoryClearPendingLoss, requests_effects=1
	goto FG_Release
FG_Battle05::
	setvar VAR_0x8004, 630
	callnative Special_FriendsStoryCanBattle, requests_effects=1
	goto_if_eq VAR_RESULT, FALSE, FG_CannotBattle
	call FG_ReturnCamera
	closemessage
	trainerbattle_no_intro 630, FG_Battle05_Won01
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_ne VAR_RESULT, B_OUTCOME_WON, FG_Release
	call FG_FrameCamera
	fg_focus 2
	msgbox FG_Battle05_Won02
	fg_focus 4
	msgbox FG_Battle05_Won03
	fg_focus 2
	msgbox FG_Battle05_Won04
	fg_focus 4
	msgbox FG_Battle05_Won05
	fg_focus 2
	msgbox FG_Battle05_Won06
	fg_focus 4
	msgbox FG_Battle05_Won07
	goto FG_Release
FG_Loss05::
	fg_focus 4
	msgbox FG_Battle05_Lost01
	fg_focus 0
	msgbox FG_Battle05_Lost02
	fg_focus 4
	msgbox FG_Battle05_Lost03
	fg_focus 0
	msgbox FG_Battle05_Lost04
	fg_focus 4
	msgbox FG_Battle05_Lost05
	fg_focus 0
	msgbox FG_Battle05_Lost06
	callnative Special_FriendsStoryClearPendingLoss, requests_effects=1
	goto FG_Release
FG_Battle06::
	setvar VAR_0x8004, 631
	callnative Special_FriendsStoryCanBattle, requests_effects=1
	goto_if_eq VAR_RESULT, FALSE, FG_CannotBattle
	call FG_ReturnCamera
	closemessage
	trainerbattle_no_intro 631, FG_Battle06_Won01
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_ne VAR_RESULT, B_OUTCOME_WON, FG_Release
	call FG_FrameCamera
	fg_focus 3
	msgbox FG_Battle06_Won02
	fg_focus 6
	msgbox FG_Battle06_Won03
	fg_focus 3
	msgbox FG_Battle06_Won04
	fg_focus 6
	msgbox FG_Battle06_Won05
	fg_focus 3
	msgbox FG_Battle06_Won06
	goto FG_Release
FG_Loss06::
	fg_focus 6
	msgbox FG_Battle06_Lost01
	fg_focus 3
	msgbox FG_Battle06_Lost02
	fg_focus 6
	msgbox FG_Battle06_Lost03
	fg_focus 3
	msgbox FG_Battle06_Lost04
	fg_focus 6
	msgbox FG_Battle06_Lost05
	callnative Special_FriendsStoryClearPendingLoss, requests_effects=1
	goto FG_Release
FG_Battle07::
	setvar VAR_0x8004, 632
	callnative Special_FriendsStoryCanBattle, requests_effects=1
	goto_if_eq VAR_RESULT, FALSE, FG_CannotBattle
	call FG_ReturnCamera
	closemessage
	trainerbattle_no_intro 632, FG_Battle07_Won01
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_ne VAR_RESULT, B_OUTCOME_WON, FG_Release
	call FG_FrameCamera
	fg_focus 3
	msgbox FG_Battle07_Won02
	fg_focus 1
	msgbox FG_Battle07_Won03
	fg_focus 3
	msgbox FG_Battle07_Won04
	fg_focus 1
	msgbox FG_Battle07_Won05
	fg_focus 3
	msgbox FG_Battle07_Won06
	fg_focus 1
	msgbox FG_Battle07_Won07
	fg_focus 1
	msgbox FG_Battle07_GrowthWin1
	fg_focus 3
	msgbox FG_Battle07_GrowthWin2
	fg_focus 1
	msgbox FG_Battle07_GrowthWin3
	goto FG_Release
FG_Loss07::
	fg_focus 1
	msgbox FG_Battle07_Lost01
	fg_focus 3
	msgbox FG_Battle07_Lost02
	fg_focus 1
	msgbox FG_Battle07_Lost03
	fg_focus 3
	msgbox FG_Battle07_Lost04
	fg_focus 1
	msgbox FG_Battle07_Lost05
	fg_focus 3
	msgbox FG_Battle07_Lost06
	fg_focus 1
	msgbox FG_Battle07_Lost07
	fg_focus 1
	msgbox FG_Battle07_GrowthLoss1
	fg_focus 3
	msgbox FG_Battle07_GrowthLoss2
	callnative Special_FriendsStoryClearPendingLoss, requests_effects=1
	goto FG_Release
FG_Battle08::
	setvar VAR_0x8004, 633
	callnative Special_FriendsStoryCanBattle, requests_effects=1
	goto_if_eq VAR_RESULT, FALSE, FG_CannotBattle
	call FG_ReturnCamera
	closemessage
	trainerbattle_no_intro 633, FG_Battle08_Won01
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_ne VAR_RESULT, B_OUTCOME_WON, FG_Release
	call FG_FrameCamera
	fg_focus 3
	msgbox FG_Battle08_Won02
	fg_focus 0
	msgbox FG_Battle08_Won03
	fg_focus 3
	msgbox FG_Battle08_Won04
	fg_focus 0
	msgbox FG_Battle08_Won05
	callnative Special_FriendsStoryGetStage, requests_effects=1
	goto_if_eq VAR_RESULT, 22, FG_Battle08_ReunionAfter
	fg_focus 3
	msgbox FG_Battle08_FinalAfter
	goto FG_Release
FG_Battle08_ReunionAfter::
	fg_focus 3
	msgbox FG_Battle08_ReunionText
	goto FG_Release
FG_Loss08::
	fg_focus 0
	msgbox FG_Battle08_Lost01
	fg_focus 3
	msgbox FG_Battle08_Lost02
	fg_focus 0
	msgbox FG_Battle08_Lost03
	fg_focus 3
	msgbox FG_Battle08_Lost04
	fg_focus 0
	msgbox FG_Battle08_Lost05
	callnative Special_FriendsStoryClearPendingLoss, requests_effects=1
	goto FG_Release
FG_Battle09::
	setvar VAR_0x8004, 634
	callnative Special_FriendsStoryCanBattle, requests_effects=1
	goto_if_eq VAR_RESULT, FALSE, FG_CannotBattle
	call FG_ReturnCamera
	closemessage
	trainerbattle_no_intro 634, FG_Battle09_Won01
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_ne VAR_RESULT, B_OUTCOME_WON, FG_Release
	call FG_FrameCamera
	fg_focus 5
	msgbox FG_Battle09_Won02
	fg_focus 4
	msgbox FG_Battle09_Won03
	fg_focus 5
	msgbox FG_Battle09_Won04
	fg_focus 4
	msgbox FG_Battle09_Won05
	callnative Special_FriendsStoryGetStage, requests_effects=1
	goto_if_eq VAR_RESULT, 22, FG_Battle09_ReunionAfter
	fg_focus 3
	msgbox FG_Battle09_FinalAfter
	goto FG_Release
FG_Battle09_ReunionAfter::
	fg_focus 3
	msgbox FG_Battle09_ReunionText
	goto FG_Release
FG_Loss09::
	fg_focus 4
	msgbox FG_Battle09_Lost01
	fg_focus 5
	msgbox FG_Battle09_Lost02
	fg_focus 4
	msgbox FG_Battle09_Lost03
	fg_focus 5
	msgbox FG_Battle09_Lost04
	fg_focus 4
	msgbox FG_Battle09_Lost05
	callnative Special_FriendsStoryClearPendingLoss, requests_effects=1
	goto FG_Release
FG_Battle10::
	setvar VAR_0x8004, 635
	callnative Special_FriendsStoryCanBattle, requests_effects=1
	goto_if_eq VAR_RESULT, FALSE, FG_CannotBattle
	call FG_ReturnCamera
	closemessage
	trainerbattle_no_intro 635, FG_Battle10_Won01
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_ne VAR_RESULT, B_OUTCOME_WON, FG_Release
	call FG_FrameCamera
	fg_focus 3
	msgbox FG_Battle10_Won02
	fg_focus 6
	msgbox FG_Battle10_Won03
	fg_focus 3
	msgbox FG_Battle10_Won04
	fg_focus 6
	msgbox FG_Battle10_Won05
	callnative Special_FriendsStoryGetStage, requests_effects=1
	goto_if_eq VAR_RESULT, 22, FG_Battle10_ReunionAfter
	fg_focus 3
	msgbox FG_Battle10_FinalAfter
	goto FG_Release
FG_Battle10_ReunionAfter::
	fg_focus 3
	msgbox FG_Battle10_ReunionText
	goto FG_Release
FG_Loss10::
	fg_focus 6
	msgbox FG_Battle10_Lost01
	fg_focus 3
	msgbox FG_Battle10_Lost02
	fg_focus 6
	msgbox FG_Battle10_Lost03
	fg_focus 3
	msgbox FG_Battle10_Lost04
	fg_focus 6
	msgbox FG_Battle10_Lost05
	callnative Special_FriendsStoryClearPendingLoss, requests_effects=1
	goto FG_Release
FG_Battle11::
	setvar VAR_0x8004, 636
	callnative Special_FriendsStoryCanBattle, requests_effects=1
	goto_if_eq VAR_RESULT, FALSE, FG_CannotBattle
	call FG_ReturnCamera
	closemessage
	trainerbattle_no_intro 636, FG_Battle11_Won01
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_ne VAR_RESULT, B_OUTCOME_WON, FG_Release
	call FG_FrameCamera
	fg_focus 4
	msgbox FG_Battle11_Won02
	fg_focus 5
	msgbox FG_Battle11_Won03
	fg_focus 4
	msgbox FG_Battle11_Won04
	fg_focus 5
	msgbox FG_Battle11_Won05
	fg_focus 4
	msgbox FG_Battle11_Won06
	callnative Special_FriendsStoryGetStage, requests_effects=1
	goto_if_eq VAR_RESULT, 22, FG_Battle11_ReunionAfter
	fg_focus 3
	msgbox FG_Battle11_FinalAfter
	goto FG_Release
FG_Battle11_ReunionAfter::
	fg_focus 3
	msgbox FG_Battle11_ReunionText
	goto FG_Release
FG_Loss11::
	fg_focus 5
	msgbox FG_Battle11_Lost01
	fg_focus 4
	msgbox FG_Battle11_Lost02
	fg_focus 5
	msgbox FG_Battle11_Lost03
	fg_focus 4
	msgbox FG_Battle11_Lost04
	fg_focus 5
	msgbox FG_Battle11_Lost05
	fg_focus 4
	msgbox FG_Battle11_Lost06
	callnative Special_FriendsStoryClearPendingLoss, requests_effects=1
	goto FG_Release
FG_Battle12::
	setvar VAR_0x8004, 637
	callnative Special_FriendsStoryCanBattle, requests_effects=1
	goto_if_eq VAR_RESULT, FALSE, FG_CannotBattle
	call FG_ReturnCamera
	closemessage
	trainerbattle_no_intro 637, FG_Battle12_Won01
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_ne VAR_RESULT, B_OUTCOME_WON, FG_Release
	call FG_FrameCamera
	fg_focus 0
	msgbox FG_Battle12_Won02
	fg_focus 3
	msgbox FG_Battle12_Won03
	fg_focus 0
	msgbox FG_Battle12_Won04
	fg_focus 3
	msgbox FG_Battle12_Won05
	callnative Special_FriendsStoryGetStage, requests_effects=1
	goto_if_eq VAR_RESULT, 22, FG_Battle12_ReunionAfter
	fg_focus 3
	msgbox FG_Battle12_FinalAfter
	goto FG_Release
FG_Battle12_ReunionAfter::
	fg_focus 3
	msgbox FG_Battle12_ReunionText
	goto FG_Release
FG_Loss12::
	fg_focus 3
	msgbox FG_Battle12_Lost01
	fg_focus 0
	msgbox FG_Battle12_Lost02
	fg_focus 3
	msgbox FG_Battle12_Lost03
	fg_focus 0
	msgbox FG_Battle12_Lost04
	fg_focus 3
	msgbox FG_Battle12_Lost05
	callnative Special_FriendsStoryClearPendingLoss, requests_effects=1
	goto FG_Release
FG_Battle13::
	setvar VAR_0x8004, 638
	callnative Special_FriendsStoryCanBattle, requests_effects=1
	goto_if_eq VAR_RESULT, FALSE, FG_CannotBattle
	call FG_ReturnCamera
	closemessage
	trainerbattle_no_intro 638, FG_Battle13_Won01
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_ne VAR_RESULT, B_OUTCOME_WON, FG_Release
	call FG_FrameCamera
	fg_focus 3
	msgbox FG_Battle13_Won02
	fg_focus 2
	msgbox FG_Battle13_Won03
	fg_focus 3
	msgbox FG_Battle13_Won04
	fg_focus 2
	msgbox FG_Battle13_Won05
	callnative Special_FriendsStoryGetStage, requests_effects=1
	goto_if_eq VAR_RESULT, 22, FG_Battle13_ReunionAfter
	fg_focus 3
	msgbox FG_Battle13_FinalAfter
	goto FG_Release
FG_Battle13_ReunionAfter::
	fg_focus 3
	msgbox FG_Battle13_ReunionText
	goto FG_Release
FG_Loss13::
	fg_focus 2
	msgbox FG_Battle13_Lost01
	fg_focus 2
	msgbox FG_Battle13_Lost02
	fg_focus 3
	msgbox FG_Battle13_Lost03
	fg_focus 2
	msgbox FG_Battle13_Lost04
	fg_focus 3
	msgbox FG_Battle13_Lost05
	callnative Special_FriendsStoryClearPendingLoss, requests_effects=1
	goto FG_Release
FG_Battle14::
	setvar VAR_0x8004, 639
	callnative Special_FriendsStoryCanBattle, requests_effects=1
	goto_if_eq VAR_RESULT, FALSE, FG_CannotBattle
	call FG_ReturnCamera
	closemessage
	trainerbattle_no_intro 639, FG_Battle14_Won01
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_ne VAR_RESULT, B_OUTCOME_WON, FG_Release
	call FG_FrameCamera
	fg_focus 3
	msgbox FG_Battle14_Won02
	fg_focus 1
	msgbox FG_Battle14_Won03
	fg_focus 3
	msgbox FG_Battle14_Won04
	fg_focus 1
	msgbox FG_Battle14_Won05
	fg_focus 3
	msgbox FG_Battle14_Won06
	callnative Special_FriendsStoryGetStage, requests_effects=1
	goto_if_eq VAR_RESULT, 22, FG_Battle14_ReunionAfter
	fg_focus 3
	msgbox FG_Battle14_FinalAfter
	goto FG_Release
FG_Battle14_ReunionAfter::
	fg_focus 3
	msgbox FG_Battle14_ReunionText
	goto FG_Release
FG_Loss14::
	fg_focus 1
	msgbox FG_Battle14_Lost01
	fg_focus 3
	msgbox FG_Battle14_Lost02
	fg_focus 1
	msgbox FG_Battle14_Lost03
	fg_focus 3
	msgbox FG_Battle14_Lost04
	fg_focus 1
	msgbox FG_Battle14_Lost05
	callnative Special_FriendsStoryClearPendingLoss, requests_effects=1
	goto FG_Release
FG_CannotBattle::
	fg_focus 3
	msgbox FG_Text_CannotBattle
	goto FG_Release

@ Every reaction terminates and is synchronously waited by fg_react.
FG_Move_Startled::
	emote_exclamation_mark
	step_end
FG_Move_LookAround::
	face_left
	delay_8
	face_right
	delay_8
	step_end
FG_Move_QuietPause::
	delay_16
	step_end
FG_Move_Emphatic::
	jump_in_place_down
	step_end

FG_Text_Introduction_1::
	.string "NICK: We landed near Viridian. Seven of\nus, no idea how. We have been trying to\pget home ever since.$"
FG_Text_Introduction_2::
	.string "NICK: I am Nick. That is Brian, Xavier -\nwe call him X - Tim, LB, Jon and Ham.$"
FG12_Text_LateIntroduction::
	.string "NICK: We're the seven people you've\nprobably heard arguing about\pdirections. I'm Nick. We watched the\nLeague, but we haven't actually met\pyou. Congratulations.$"
FG21_Text_LateIntroduction1::
	.string "NICK: We landed near Viridian. Seven of\nus, no idea how.$"
FG21_Text_LateIntroduction2::
	.string "XAVIER: Reflections kept showing\nBrian's living room. We think that thing\pis finally letting us go back.$"
FG21_Text_LateIntroduction3::
	.string "HAM: With everyone.$"
FG_Text_PartnersKanto::
	.string "NICK: Our partners chose to stay while\nwe traveled. You did not miss a job we\pneeded you to do; that was our own\njourney.$"
FG17_Text_MissedReflection::
	.string "XAVIER: The water has shown Brian's\nhome before. We have been keeping\ptrack of what we actually saw.$"
FG03_Text_LatePartners1::
	.string "NICK: Brian travels with Rattata, and\nJon with Mankey. They chose us after a\pdifficult first camp.$"
FG03_Text_LatePartners2::
	.string "NICK: Poliwag joined me at a roadside\npond. LB is still working out what to do\pwith this Jigglypuff.$"
FG04_Text_LatePartners1::
	.string "NICK: Brian has Rattata, Jon has\nMankey, LB has Jigglypuff, and I\ptravel with Poliwag.$"
FG04_Text_LatePartners2::
	.string "NICK: X and Tim met their own partners\non the road. Ham has had company all\pmorning.$"
FG09_Text_LatePartners1::
	.string "NICK: Our first partners are Rattata,\nOddish, Spearow, Jigglypuff, Poliwag,\pMankey and Psyduck.$"
FG09_Text_LatePartners2::
	.string "NICK: Paras joined X after following\nhis map's shade. We are learning to\plook after everybody.$"
FG13_Text_LatePartners1::
	.string "NICK: Brian has Rattata and Slowpoke.\nX travels with Oddish and Paras; Tim\pwith Spearow and Krabby.$"
FG13_Text_LatePartners2::
	.string "NICK: I have Poliwag and Geodude. LB\nhas Jigglypuff, Jon has Mankey, and\pHam has Psyduck. Same partners, new\nregion.$"
FG15_Text_LatePartners1::
	.string "NICK: We brought our Kanto partners\nwith us. Jon's Mankey evolved into\pPrimeape on the road.$"
FG15_Text_LatePartners2::
	.string "NICK: Ham has Psyduck and Sentret\nnow. Sentret chose to come with us at\pour last camp.$"
FG16_Text_LatePartners1::
	.string "NICK: We have kept traveling with the\npartners we met in Kanto. Ham has\pPsyduck and Sentret.$"
FG16_Text_LatePartners2::
	.string "NICK: Hoothoot joined Jon after he\nlearned to give it space. LB has just\pfound another visitor.$"
FG17_Text_LatePartners1::
	.string "NICK: All seven of us have two\npartners now. They chose to stay as we\ptraveled.$"
FG17_Text_LatePartners2::
	.string "NICK: Getting home matters, but we are\nnot leaving them behind to do it.$"
FG20_Text_LatePartners1::
	.string "NICK: We have been training on the way\nhere. Some partners evolved; all\pfourteen stayed with us.$"
FG20_Text_LatePartners2::
	.string "NICK: Those were our own practice\nmatches. You do not owe us the early\pones you missed.$"
FG01_Text_Tear::
	.string "The air over the road bends like a\nbad signal.\pSomething huge is pushing through.$"
FG01_Text_Main01::
	.string "JON: I WAS ON A COUCH. I WAS ON A\nCOUCH FIVE SECONDS AGO!$"
FG01_Text_Main02::
	.string "BRIAN: Nobody move. Nobody step on\nanything. I still have the cable.$"
FG01_Text_Main03::
	.string "NICK: Brian. There's a giant ghost\ndragon looking at us.$"
FG01_Text_Main04::
	.string "BRIAN: I can see it. I'm prioritizing.\nThis is the HDMI that actually works.\pDo you know what those cost?$"
FG01_Text_Main05::
	.string "NICK: What are you going to plug it\ninto? We're on a road.$"
FG01_Text_Main06::
	.string "BRIAN: My TV. When we get back. I'm\nnot buying a new one because a dragon\pdidn't respect the setup.$"
FG01_Text_Main07::
	.string "JON: WHERE ARE MY SHOES? IT TOOK MY\nFUCKING SHOES AND LEFT ME THE CUP?$"
FG01_Text_Main08::
	.string "TIM: Okay. Nobody panic. But was that\nthe Thailand tab? I had a video going\pon the other screen.$"
FG01_Text_Main09::
	.string "JON: YOU THINK A DRAGON CAME OUT OF\nA FUCKING POP-UP?$"
FG01_Text_Main10::
	.string "TIM: I'm saying we work out which tab\ndid it before anybody refreshes\panything.$"
FG01_Text_Main11::
	.string "XAVIER: Nobody is refreshing anything.\nEverybody breathe. Ground your energy.$"
FG01_Text_Main12::
	.string "JON: MY ENERGY IS GROUNDED, X. MY BARE\nFUCKING FEET ARE ON THE GROUND.$"
FG01_Text_Main13::
	.string "XAVIER: Then you're the most grounded\nperson here. Step one, headcount.\pStep two, nobody touches the dragon.\nStep three, a roof.$"
FG01_Text_Main14::
	.string "LB: It's still staring. Why is it\nstill staring at us?$"
FG01_Text_Main15::
	.string "NICK: Don't make eye contact. It's\nlike a dog. Or a landlord.$"
FG01_Text_Main16::
	.string "BRIAN: It's leaving. It's actually\nleaving! Hey! Our stuff is still in\pthe living room!$"
FG01_Text_Main17::
	.string "JON: GET BACK HERE, YOU FLOATING\nPIECE OF SHIT! TAKE US HOME!$"
FG01_Text_Main18::
	.string "NICK: …It didn't take us home.$"
FG01_Text_Main19::
	.string "XAVIER: Headcount. Brian, Nick, Tim,\nLB, Jon… Where's Ham?$"
FG01_Text_Main20::
	.string "HAM: …cock.$"
FG01_Text_Main21::
	.string "NICK: Seven. Everyone's here. That's\nthe part that matters right now.$"
FG01_Text_Main22::
	.string "LB: None of our phones have service.\nMine still thinks we're at Brian's.$"
FG01_Text_Main23::
	.string "BRIAN: Emotionally, it's correct.$"
FG01_Text_Main24::
	.string "TIM: Is anybody else seeing a box\nunder everything we say?$"
FG01_Text_Main25::
	.string "NICK: Don't look at the box, Tim.$"
FG01_Text_Main26::
	.string "JON: AND WHY IS MY NAME IN CAPITALS?\nWHO DID THAT?$"
FG01_Text_Main27::
	.string "BRIAN: That's just how you talk, Jon.$"
FG01_Text_Main28::
	.string "XAVIER: Look at the trees. They're all\nthe same tree. The grass is on a grid.\pWe're somewhere very… tidy.$"
FG01_Text_Main29::
	.string "NICK: Okay. New place, same us. It's\nlike any trip. Food, somewhere to\psleep, then a plan.$"
FG01_Text_Main30::
	.string "LB: Same? Nick. Look around.\pFirst of all, NOTHING WAS THE SAME.$"
FG01_Text_Main31::
	.string "BRIAN: He's been waiting his whole life\nto say that, and it had to be here.$"
FG01_Text_Main32::
	.string "LB: It's the album. It fits the\nsituation. I stand by it.$"
FG01_Text_Main33::
	.string "TIM: If it isn't Thailand, is it at\nleast near Thailand? It's giving\pThailand a little.$"
FG01_Text_Main34::
	.string "BRIAN: Nothing here has a corner that\nisn't ninety degrees, Tim.$"
FG01_Text_Main35::
	.string "JON: AND WHO SCREAMED ON THE WAY\nDOWN? SOMEBODY WENT OFF LIKE A KETTLE.$"
FG01_Text_Main36::
	.string "HAM: I'm not a bitch.$"
FG01_Text_Main37::
	.string "NICK: Nobody said you were, Ham.$"
FG01_Text_Main38::
	.string "HAM: Pre-emptively.$"
FG01_Text_Main39::
	.string "XAVIER: Okay. Shelter. Brian, you're\nthe expert. What do we need?$"
FG01_Text_Main40::
	.string "BRIAN: A roof over a room. With a\ncouch. People keep calling trees\pshelter and I need us to have\nstandards.$"
FG01_Text_Main41::
	.string "NICK: There's a kid on the road.\nEverybody act normal.$"
FG01_Text_Main42::
	.string "JON: I HAVE NO SHOES, NICK.$"
FG01_Text_Main43::
	.string "XAVIER: Hi. Sorry. Strange morning.\nWe're not from… here. Where is here,\pexactly?$"
FG01_Text_Main44::
	.string "BRIAN: And does here have somewhere\nto sit?$"
FG01_Text_Choice0_01::
	.string "NICK: Right. Follow-up question. What\nthe fuck is a Kanto?$"
FG01_Text_Choice0_02::
	.string "XAVIER: It's a place with a name.\nThat's more than we had a minute ago.$"
FG01_Text_Choice0_03::
	.string "TIM: Does Kanto have nightlife?\nAsking for the group.$"
FG01_Text_Choice0_04::
	.string "NICK: The group isn't asking, Tim.$"
FG01_Text_Choice0_05::
	.string "BRIAN: Ask about rooms before money.\nI want a reason to care what the\pmoney's called.$"
FG01_Text_Choice1_01::
	.string "BRIAN: A building. Finally, somebody\nwith a plan.$"
FG01_Text_Choice1_02::
	.string "NICK: They gave us a direction, Brian.\nWe still have to walk there.$"
FG01_Text_Choice1_03::
	.string "BRIAN: Walking is how this started. I\nwas sitting down.$"
FG01_Text_Choice1_04::
	.string "XAVIER: Thank you. We'll ask there\nbefore we decide anything else.$"
FG01_Text_Leave01::
	.string "JON: IF ANYBODY SEES SHOES, THEY'RE\nMINE. I DON'T CARE WHOSE THEY ARE.$"
FG01_Text_Leave02::
	.string "XAVIER: One group, one direction.\nLet's go.$"
FG02_Text_Main01::
	.string "BRIAN: Nick. There's a rat in my\nbedroom.$"
FG02_Text_Main02::
	.string "NICK: That's a patch of grass.$"
FG02_Text_Main03::
	.string "BRIAN: I put my bag down. There were\nboundaries. Now he's moving furniture.$"
FG02_Text_Main04::
	.string "NICK: He's moving your sock toward the\nsandwich in the bottom.$"
FG02_Text_Main05::
	.string "BRIAN: So he's found the kitchen.\nGreat. That rat has moved in without\ppaying rent.$"
FG02_Text_Main06::
	.string "NICK: Put the bag down slowly. Let him\ncome out before you start negotiating\pthe lease.$"
FG02_Text_Main07::
	.string "BRIAN: If he takes the sandwich, I'm\ngoing to have to walk back to town.$"
FG02_Text_Main08::
	.string "NICK: You have another one in your\npocket.$"
FG02_Text_Main09::
	.string "BRIAN: That's tomorrow's plan. You're\ndescribing a collapse of the whole\psystem.$"
FG02_Text_Main10::
	.string "JON: THIS LITTLE BASTARD TOOK MY LAST\nONE.$"
FG02_Text_Main11::
	.string "NICK: Yours was on the ground. Stop\nleaning over him.$"
FG02_Text_Main12::
	.string "JON: I'm trying to explain ownership.$"
FG02_Text_Main13::
	.string "NICK: He's trying to explain that he's\nscared of the shouting man above him.\pTake a step back.$"
FG02_Text_Main14::
	.string "JON: He shouted first.$"
FG02_Text_Main15::
	.string "NICK: And now you both need a minute.\nYou can be the first one to take it.$"
FG02_Text_Main16::
	.string "JON: Fine. One step. Look. I'm taking\nthe fucking step.$"
FG02_Text_Main17::
	.string "BRIAN: Mine stopped when I stopped.\nThat's uncomfortable information to\preceive from a rat.$"
FG02_Text_Main18::
	.string "NICK: Keep doing what works. Give him\nsome room.$"
FG02_Text_Main19::
	.string "BRIAN: He's coming back. With the sock.\nIs that a deposit?$"
FG02_Text_Main20::
	.string "NICK: I think he likes being near you.\nYou can offer him one of those balls\pwe picked up. Let him decide.$"
FG02_Text_Main21::
	.string "JON: Mine's following me now. I stopped\nshouting and he started following me.\pWhat the fuck am I supposed to learn\nfrom that?$"
FG02_Text_Main22::
	.string "NICK: You don't have to announce it.\nJust remember it.$"
FG02_Text_Main23::
	.string "BRIAN: I'm naming mine Roommate. He's\nalready more comfortable here than I\pam.$"
FG02_Text_Main24::
	.string "JON: I'm keeping the wrapper. One of us\nhas to clean up after this meeting.$"
FG02_Text_Main25::
	.string "BRIAN: So we've got partners. We could\ntry one of those trainer battles.\pSomething short. Close to where I live.$"
FG02_Text_Main26::
	.string "NICK: You still don't live on the grass,\nbut yes. You can ask.$"
FG02_Text_Choice0_01::
	.string "BRIAN: Roommate, we're going to try\nthis. Nick, don't coach both sides.$"
FG02_Text_Choice0_02::
	.string "NICK: I'll start by making sure both\nsides understand what's happening.$"
FG02_Text_Choice0_03::
	.string "BRIAN: That's already more coaching\nthan I got at home.$"
FG02_Text_Choice1_01::
	.string "BRIAN: Perfect. I've had enough\noutside for today.$"
FG02_Text_Choice1_02::
	.string "NICK: You're still outside.$"
FG02_Text_Choice1_03::
	.string "BRIAN: Recreationally outside is\ndifferent from competitively outside.\pRoommate understands.$"
FG03_Text_Main01::
	.string "JON: WHO THE FUCK DREW AN EYEBROW ON\nMY FOREHEAD?$"
FG03_Text_Main02::
	.string "LB: Hold on. Before you get mad, how\nmuch of the performance do you\premember?$"
FG03_Text_Main03::
	.string "JON: You said the acoustics were\nincredible. Then I woke up with a third\pfucking eyebrow.$"
FG03_Text_Main04::
	.string "LB: So you heard the echo. I was right\nabout that part.$"
FG03_Text_Main05::
	.string "NICK: We lost everyone when\nJigglypuff started singing. My shoe's\pbeen getting splashed for five\nminutes.$"
FG03_Text_Main06::
	.string "LB: I thought the silence meant people\nwere listening.$"
FG03_Text_Main07::
	.string "NICK: Brian was snoring.$"
FG03_Text_Main08::
	.string "LB: He does that while people are\ntalking. I didn't want to single him\pout.$"
FG03_Text_Main09::
	.string "BRIAN: I've slept in worse rooms.\nYesterday. That room was outside. This\pone has an echo and a working alarm\nsystem.$"
FG03_Text_Main10::
	.string "JON: Where's the little round fucker? I\nwant it to see the work it's done.$"
FG03_Text_Main11::
	.string "NICK: Right beside LB. Keep your voice\ndown. It's upset because everyone\pstopped watching.$"
FG03_Text_Main12::
	.string "LB: Okay. That's on me. You came in\nstrong, everybody went down, and\pnobody thanked you. The timing needs\nwork, but I respect the commitment.$"
FG03_Text_Main13::
	.string "JON: You are reviewing the concert\nthat put us on the fucking floor.$"
FG03_Text_Main14::
	.string "LB: I'm establishing a working\nrelationship. Can you go wash your\pface before you make it weird?$"
FG03_Text_Main15::
	.string "NICK: There's clean water in the bottle\nbeside your bag. Don't use the pond\pyet; Poliwag's been settling in there.$"
FG03_Text_Main16::
	.string "JON: Since when do you have a Poliwag?$"
FG03_Text_Main17::
	.string "NICK: Since the roadside pond\nyesterday. It kept coming back when I\psat down, so I waited. Eventually it\nwanted to come with us.$"
FG03_Text_Main18::
	.string "LB: You got a friend by sitting quietly.\nI hummed for two seconds and now I'm\presponsible for whatever happened to\nhis face.$"
FG03_Text_Main19::
	.string "NICK: Try sitting quietly with this\none. See whether it stays when there's\pno show.$"
FG03_Text_Main20::
	.string "LB: Alright. You can stay with us. But\nwe need to talk about the marker. Some\pof us wake up angry enough already.$"
FG03_Text_Main21::
	.string "NICK: Start by asking before the\nsinging.$"
FG03_Text_Main22::
	.string "JON: And give me enough warning to\nleave the fucking cave.$"
FG03_Text_Main23::
	.string "LB: Fine. You get advance notice. Nick\ngets a dry shoe. Everybody happy?$"
FG03_Text_Main24::
	.string "NICK: Close enough. Poliwag, come out\nof the puddle. We're taking a proper\pbreak now.$"
FG03_Text_Main25::
	.string "JON: I don't need another nap. I need\nsomething with actual rules. Mankey\pand I can do a battle.$"
FG03_Text_Main26::
	.string "BRIAN: Great. You work on that. I'm\ngoing to finish the rest I apparently\previewed so highly.$"
FG03_Text_Choice0_01::
	.string "JON: Good. Clear space, one opponent,\nnobody singing. I understand this.$"
FG03_Text_Choice0_02::
	.string "NICK: Ask Mankey if he's ready too.$"
FG03_Text_Choice0_03::
	.string "JON: You good? Yeah? All right. Let's\ndo it.$"
FG03_Text_Choice1_01::
	.string "NICK: Good call. His volume's still\nsuper effective.$"
FG03_Text_Choice1_02::
	.string "JON: I'm standing right here.$"
FG03_Text_Choice1_03::
	.string "NICK: Then stand right here with some\nwater. We can battle later.$"
FG03_Text_Choice1_04::
	.string "JON: Give me the bottle. And somebody\ntell me if the eyebrow comes off.$"
FG04_Text_Main01::
	.string "XAVIER: Don't move that bag yet.\nOddish picked the shady side. I've\pbeen shifting the supplies so it\ndoesn't have to keep getting up.$"
FG04_Text_Main02::
	.string "NICK: That's considerate. Did you ask\nwhether it wanted to come with us?$"
FG04_Text_Main03::
	.string "XAVIER: I offered a ball this morning.\nIt inspected it, waited a while, then\pjoined me. We took our time.$"
FG04_Text_Main04::
	.string "NICK: Good. So what was all that about\naligning with your natural companion?$"
FG04_Text_Main05::
	.string "XAVIER: Also true. Spiritually we\nconnected. Practically I stopped\pputting the water in the sun.$"
FG04_Text_Main06::
	.string "BRIAN: Is that why Rattata keeps\nlooking at me? I gave him my shaded\pspot and now he's staring at the\nsandwich.$"
FG04_Text_Main07::
	.string "NICK: He's allowed to want two things,\nBrian.$"
FG04_Text_Main08::
	.string "BRIAN: Fine. I just want one meal where\nnobody is reviewing my decisions.$"
FG04_Text_Main09::
	.string "XAVIER: Same seven people, same\narguments over lunch. Underneath all\pthis, it's all the same.$"
FG04_Text_Main10::
	.string "LB (to XAVIER): First of all, NOTHING\nWAS THE SAME.$"
FG04_Text_Main11::
	.string "XAVIER: I walked directly into that\none. Can the album debate wait until\pwe've fed everybody?$"
FG04_Text_Main12::
	.string "LB (to XAVIER): Nigga, you announced\nspiritual alignment while counting\pcrackers. Let me have my moment.$"
FG04_Text_Main13::
	.string "XAVIER: You can have the moment and\ncount these portions. Jigglypuff\pneeds lunch too.$"
FG04_Text_Main14::
	.string "LB: Alright. But I'm counting his\nportions too. Somehow the rat always\pgets seconds before the rest of us.$"
FG04_Text_Main15::
	.string "TIM: Mine already has a designated\nseat. Followed me after that meal stop\pyesterday. Apparently sharing lunch\nworks better than asking where the\pairport is.$"
FG04_Text_Main16::
	.string "NICK: You've been carrying that perch\nall morning?$"
FG04_Text_Main17::
	.string "TIM: It kept landing on my shoulder. I\nfigured a place with a grip would be\pmore comfortable. And less shit on my\nshirt.$"
FG04_Text_Main18::
	.string "NICK: That's a good reason. Both of\nthem.$"
FG04_Text_Main19::
	.string "TIM: It can fly, though. That's still\nrelevant to the getting-home\pdiscussion.$"
FG04_Text_Main20::
	.string "NICK: It can fly around this picnic\narea. Let's not assign it international\ptransport before we've finished lunch.$"
FG04_Text_Main21::
	.string "BRIAN: Ham, is that duck yours? It's\nbeen beside you for twenty minutes.$"
FG04_Text_Main22::
	.string "HAM: I thought it was with you.$"
FG04_Text_Main23::
	.string "BRIAN: Mine has been stealing my\nsocks. I'd have mentioned the second\ptenant.$"
FG04_Text_Main24::
	.string "NICK: It seems comfortable with you.\nYou can ask it to stay. Same as we did.$"
FG04_Text_Main25::
	.string "HAM: You want to come? We don't really\nknow where we're going yet. There'll be\pfood, though.$"
FG04_Text_Main26::
	.string "NICK: Seven people, seven partners. All\nright. Now let's learn what they\pactually need before we start\npromising anybody a world tour.$"
FG04_Text_Choice0_01::
	.string "NICK: We have learned that shouting a\nmove you made up doesn't count.$"
FG04_Text_Choice0_02::
	.string "BRIAN: Jon called it creative coaching.$"
FG04_Text_Choice0_03::
	.string "NICK: Mankey called it standing there.\nWe're starting with the moves they\pknow and taking breaks before\neverybody gets frustrated.$"
FG04_Text_Choice0_04::
	.string "XAVIER: And meals before practice.\nThat has improved morale more than\pany speech I've given.$"
FG04_Text_Choice1_01::
	.string "XAVIER: We have a route, a budget and\nalmost enough socks.$"
FG04_Text_Choice1_02::
	.string "BRIAN: There were enough socks before\nRattata started furnishing his area.$"
FG04_Text_Choice1_03::
	.string "NICK: You gave him permission to keep\none.$"
FG04_Text_Choice1_04::
	.string "BRIAN: One became a matching set.\nThat's how they get you.$"
FG05_Text_Main01::
	.string "TIM: What gets me closest to Thailand?$"
FG05_Text_Main02::
	.string "CLERK: This service goes to the\nislands listed on the board.$"
FG05_Text_Main03::
	.string "TIM: Right. And which of those\nconnects onward?$"
FG05_Text_Main04::
	.string "CLERK: Onward to which island?$"
FG05_Text_Main05::
	.string "TIM: Ideally not an island. I'm keeping\nmy options open, though.$"
FG05_Text_Main06::
	.string "CLERK: Then you should decide where\nyou want to go before buying a ticket.$"
FG05_Text_Main07::
	.string "TIM: That's what I'm trying to do. Any\nadult nightlife at these stops?$"
FG05_Text_Main08::
	.string "CLERK: The evening service departs at\nsix.$"
FG05_Text_Main09::
	.string "TIM: I meant something to do after the\nboat arrives.$"
FG05_Text_Main10::
	.string "CLERK: Most passengers collect their\nluggage.$"
FG05_Text_Main11::
	.string "NICK: You got pulled through reality\nand you're still planning a trip around\psex workers.$"
FG05_Text_Main12::
	.string "TIM: I had a hotel booked and a return\nflight. It was a perfectly reasonable\pplan before reality got involved.$"
FG05_Text_Main13::
	.string "NICK: We don't know how to get home.\nCould that be the first plan?$"
FG05_Text_Main14::
	.string "TIM: It is. I checked for Wi-Fi before\nasking about the nightlife.$"
FG05_Text_Main15::
	.string "NICK: That's the same plan with a\nloading screen. Look at the actual\pmap. Where can seven people and their\nPokémon go with the money we've got?$"
FG05_Text_Main16::
	.string "TIM: Depends whether partners need\nseparate fares. Also depends whether\pwe're buying seven tickets or there's\na group rate.$"
FG05_Text_Main17::
	.string "NICK: Good. Ask those questions. You\nactually know how to do this when you\pstop trying to improve the\ndestination.$"
FG05_Text_Main18::
	.string "JON: BOOK A FUCKING BOAT THAT EXISTS.\nI've got three bags and something in\pBrian's keeps touching my wrist.$"
FG05_Text_Main19::
	.string "CLERK: Excellent. Someone understands\nthe board.$"
FG05_Text_Main20::
	.string "TIM: Seven adults. Our Pokémon travel\nwith us. Which listed crossing gives us\penough room without paying for space\nwe don't need?$"
FG05_Text_Main21::
	.string "CLERK: This local service. Keep the\naisle clear and arrange the luggage\pbefore boarding. You can book it\ntogether.$"
FG05_Text_Main22::
	.string "TIM: Great. One booking, seven names.\nI'll check the details before I pay.\pDoes the posted fare include\neverything on that route?$"
FG05_Text_Main23::
	.string "CLERK: Yes. The crossing and the\nluggage allowance shown beneath it.$"
FG05_Text_Main24::
	.string "NICK: There he is. That's the guy who\nused to get us through airports.$"
FG05_Text_Main25::
	.string "TIM: Thank you. I can have interests\nand still read the fucking terms.$"
FG05_Text_Main26::
	.string "CLERK: Then please read the departure\npoint as well. This is the ticket\poffice. The boat is outside.$"
FG05_Text_Repeat::
	.string "TIM: We checked the route and the\nfare. Our booking is sorted.$"
FG06_Text_Main01::
	.string "BRIAN: Nick, force the mismatch. Make\nthem react to you.$"
FG06_Text_Main02::
	.string "NICK: They're Pokémon, Brian.$"
FG06_Text_Main03::
	.string "BRIAN: And yet you understood me\nimmediately. The coaching translates.$"
FG06_Text_Main04::
	.string "NICK: Some of it does. The part where\nyou told me to bring somebody off the\pbench doesn't. I have one partner.$"
FG06_Text_Main05::
	.string "BRIAN: Then protect your starter.\nThat's roster management.$"
FG06_Text_Main06::
	.string "NICK: I'm giving Poliwag water and a\nbreak. You can just call it that.$"
FG06_Text_Main07::
	.string "BRIAN: You never appreciated the work\nI did on those 2K rotations either.$"
FG06_Text_Main08::
	.string "NICK: You gave yourself the ball every\npossession.$"
FG06_Text_Main09::
	.string "BRIAN: Reliable offense. Look, I'm\nsaying watch what they're doing\pbefore you rush in. That's all.$"
FG06_Text_Main10::
	.string "NICK: That's good advice. Keep that\nbit. Poliwag, take your time; we're only\ppracticing.$"
FG06_Text_Main11::
	.string "LB: You're both overcomplicating this.\nShe sings, they sleep, we win.$"
FG06_Text_Main12::
	.string "XAVIER: She just yawned.$"
FG06_Text_Main13::
	.string "LB: That's not the same thing. The\nsleeping is supposed to happen over\pthere.$"
FG06_Text_Main14::
	.string "XAVIER: She's tired. Ask whether she\nwants to battle.$"
FG06_Text_Main15::
	.string "LB: We haven't even started.$"
FG06_Text_Main16::
	.string "XAVIER: She's been walking too. Take\ncare of her first.$"
FG06_Text_Main17::
	.string "LB: TAKE CARE. See? That's what I've\nbeen telling you.$"
FG06_Text_Main18::
	.string "XAVIER: You told me the album was\nperfect. I'm telling you to fill her\pwater cup.$"
FG06_Text_Main19::
	.string "LB: Both good advice. You could've just\nagreed with me.$"
FG06_Text_Main20::
	.string "XAVIER: Fill the cup and I'll consider\nit.$"
FG06_Text_Main21::
	.string "LB: She leaned on my leg. I think we're\ntaking a minute.$"
FG06_Text_Main22::
	.string "NICK: We can wait. Nobody's keeping\nscore yet.$"
FG06_Text_Main23::
	.string "JON: Keep the marker away from her. I\nscrubbed my forehead for twenty\pfucking minutes.$"
FG06_Text_Main24::
	.string "LB: You're going to bring that up in\nevery town, aren't you?$"
FG06_Text_Main25::
	.string "JON: Until I can look in a mirror\nwithout checking for a third eyebrow.\pYes.$"
FG06_Text_Main26::
	.string "NICK: We're both up for a practice\nmatch if you are. Pick one, or just\ptake a break with us. No pressure.$"
FG06_Text_Choice0_01::
	.string "NICK: All right. Poliwag and I are\nready. Let's give each other a decent\pmatch.$"
FG06_Text_Choice0_02::
	.string "BRIAN: Remember what I said about…$"
FG06_Text_Choice0_03::
	.string "NICK: I remember. You can watch the\nfirst turn before adding another\psystem.$"
FG06_Text_Choice1_01::
	.string "LB: Okay. You rested? You want to try?\nAlright. Just us, Jigglypuff.$"
FG06_Text_Choice1_02::
	.string "XAVIER: That was a remarkably\npractical sentence.$"
FG06_Text_Choice1_03::
	.string "LB: Enjoy it. If this goes well, I'm\ntaking credit for listening to you.$"
FG06_Text_Choice2_01::
	.string "NICK: There's room in the shade.\nBrian's been scouting it\pprofessionally.$"
FG06_Text_Choice2_02::
	.string "BRIAN: The breeze reaches this side.\nThat side looks good until the sun\pmoves. You're welcome.$"
FG06_Text_Choice2_03::
	.string "NICK: He actually has done the\nresearch. Sit wherever you like.$"
FG07_Text_Main01::
	.string "XAVIER: We need to manifest\nabundance. Right now the budget buys\pdinner or rooms. It doesn't buy both.$"
FG07_Text_Main02::
	.string "BRIAN: Rooms. We have snacks.$"
FG07_Text_Main03::
	.string "XAVIER: Seven people and seven\nPokémon cannot live on the emergency\pcrackers you've been protecting since\nRoute 2.$"
FG07_Text_Main04::
	.string "BRIAN: They're called emergency\ncrackers for a reason. A hotel with no\pfood is still better than food with no\nhotel.$"
FG07_Text_Main05::
	.string "XAVIER: You said that yesterday. Then\nyou were hungry, indoors, explaining\pwhy that was a different emergency.$"
FG07_Text_Main06::
	.string "BRIAN: I remember. The room had\nexcellent acoustics for the complaint.$"
FG07_Text_Main07::
	.string "LB: What if we get one big room? Spread\neverybody out. Make it a creative\pretreat.$"
FG07_Text_Main08::
	.string "XAVIER (to LB): Nigga, the universe is\nnot paying for a hotel. Calling it a\pretreat doesn't change the number at\nthe bottom.$"
FG07_Text_Main09::
	.string "LB: I said one room instead of seven.\nThat's an actual suggestion. We need\psomewhere to recover after all this\nwalking.$"
FG07_Text_Main10::
	.string "XAVIER: I agree. That's why I spoke to\nthe restaurant owner instead of\pnaming the trip. Seven people. Two\nhours washing dishes. Dinner and beds.$"
FG07_Text_Main11::
	.string "JON: THAT'S A FUCKING JOB.$"
FG07_Text_Main12::
	.string "XAVIER: Yes. But I said it beautifully.\nI also asked about the Pokémon. They\phave a sheltered space we can set up\nbeside the rooms.$"
FG07_Text_Main13::
	.string "NICK: He's the only one with a plan\nthat includes dinner. What needs doing\pfirst?$"
FG07_Text_Main14::
	.string "XAVIER: Clear tables, wash, dry, put\neverything away. We split it up. Nobody\pfinishes early and disappears while\nsomebody else is still working.$"
FG07_Text_Main15::
	.string "BRIAN: Why did you look at me for that\nlast part?$"
FG07_Text_Main16::
	.string "XAVIER: Because you asked whether\ndrying could be done lying down.$"
FG07_Text_Main17::
	.string "NICK: That Paras has followed your map\nall the way down the street.$"
FG07_Text_Main18::
	.string "XAVIER: I thought it wanted the food.\nIt stays when I move the food. It only\pleaves when the shade goes.$"
FG07_Text_Main19::
	.string "BRIAN: It's scouting seating. Finally,\nsomebody understands my\pcontribution.$"
FG07_Text_Main20::
	.string "XAVIER: We're going to be indoors for a\nwhile. I need to find it somewhere cool\pbefore we start.$"
FG07_Text_Main21::
	.string "LB: Use the spare cloth. I'll hold the\nmap while you set it up. We can't tell\ppeople we're learning to look after\nPokémon and then fold this one's roof\paway.$"
FG07_Text_Main22::
	.string "XAVIER: Good call. Thanks. Give it room\nto move out if it wants to.$"
FG07_Text_Main23::
	.string "RESTAURANT OWNER: Are all seven of you\nhelping? I need the tables clear\pbefore the dinner customers arrive.$"
FG07_Text_Main24::
	.string "JON: Yes. All seven. Apparently we're a\nfucking catering company now.$"
FG07_Text_Main25::
	.string "RESTAURANT OWNER: Good. The aprons\nare here. Please don't dry the plates\pwith the table cloths.$"
FG07_Text_Main26::
	.string "BRIAN: I'll dry. Standing up. But I want\nit on record that the chairs are right\pthere.$"
FG07_Text_Choice0_01::
	.string "XAVIER: Sure. They've eaten, they've\nrested, and we've got a little daylight.\pLet's see what our preparation\nactually does.$"
FG07_Text_Choice0_02::
	.string "BRIAN: If the preparation loses, do we\nget the two hours washing dishes\pback?$"
FG07_Text_Choice0_03::
	.string "XAVIER: You already spent those hours\non dinner. The battle is a separate\ptransaction.$"
FG07_Text_Choice1_01::
	.string "XAVIER: Healthy, if Tim stops\nconverting everything into airfare.$"
FG07_Text_Choice1_02::
	.string "LB: He's put the food money in a\nseparate envelope. Brian keeps\pchecking it like something's going to\nhatch.$"
FG07_Text_Choice1_03::
	.string "BRIAN: I'm making sure we have\nbreakfast. That's called thinking\pahead.$"
FG07_Text_Choice1_04::
	.string "XAVIER: It is. Which is why you can\nstop opening it. I wrote breakfast on\pthe front.$"
FG07_Text_Choice2_01::
	.string "XAVIER: We'll still be here. Brian is\nmeasuring the bench.$"
FG07_Text_Choice2_02::
	.string "BRIAN: Comparing it with the one\noutside our room. I'm trying to improve\pour quality of life.$"
FG07_Text_Choice2_03::
	.string "NICK: Leave both benches where they\nare. Come help me check the bedding.$"
FG07_Text_Choice2_04::
	.string "BRIAN: Finally. Somebody assigning\nwork in my actual field.$"
FG08_Text_Main01::
	.string "HAM: Where do you want this? The\nground's wet out here.$"
FG08_Text_Main02::
	.string "FUJI: By the window, please. Leave\nenough room for someone to get past\pit.$"
FG08_Text_Main03::
	.string "JON: WATCH THE…$"
FG08_Text_Main04::
	.string "NICK: We saw it. Ham's got the other\nend.$"
FG08_Text_Main05::
	.string "JON: I was trying to stop him hitting\nthe frame. I wasn't yelling at it.$"
FG08_Text_Main06::
	.string "FUJI: I understand. It doesn't know\nyou well enough to understand that\pyet.$"
FG08_Text_Main07::
	.string "HAM: Here? It can still get behind the\nchair if it wants.$"
FG08_Text_Main08::
	.string "FUJI: Yes. That's a good place.$"
FG08_Text_Main09::
	.string "NICK: Should we leave the blanket and\nstep back?$"
FG08_Text_Main10::
	.string "JON: I can go outside. If I'm making it\nworse.$"
FG08_Text_Main11::
	.string "FUJI: You can sit down. Let it decide\nhow close it wants to come.$"
FG08_Text_Main12::
	.string "LB: That bowl's empty. Is there\nsomewhere I can get water?$"
FG08_Text_Main13::
	.string "FUJI: I'll show you. Thank you for\nnoticing.$"
FG08_Text_Main14::
	.string "HAM: There's another mattress outside.\nI'll bring it when everyone's clear of\pthe door.$"
FG08_Text_Main15::
	.string "JON: Yeah. We can stay a minute.$"
FG08_Text_Main16::
	.string "FUJI: There's no hurry.$"
FG08_Text_Repeat::
	.string "FUJI: There is no hurry. Leave them\nroom, and let them decide.$"
FG09_Text_Main01::
	.string "BRIAN: Finally. Something that\nunderstands my pace. I've been here\ptwenty minutes and neither of us has\nasked the other to move.$"
FG09_Text_Main02::
	.string "NICK: It followed you over because you\nwere carrying the food.$"
FG09_Text_Main03::
	.string "BRIAN: And then it stayed. That's\ncalled building a relationship.$"
FG09_Text_Main04::
	.string "NICK: Good. The next part is feeding it\nwhen you aren't also hungry.$"
FG09_Text_Main05::
	.string "BRIAN: Alright. What does it eat?\nBefore one of you says whatever I'm\peating.$"
FG09_Text_Main06::
	.string "TIM: Ask at the Center. That's what I\ndid for Krabby. Turns out helping with\pthe ropes doesn't mean it can live on\nrope.$"
FG09_Text_Main07::
	.string "JON: THE CRAB HAS A JOB BEFORE HAM.$"
FG09_Text_Main08::
	.string "HAM: I carried the mattresses.$"
FG09_Text_Main09::
	.string "NICK: He did. You yelled at a towel\nbecause you thought something was in\pit.$"
FG09_Text_Main10::
	.string "TIM: Anyway, the dockworker said it\nhangs around there. Nobody's partner.\pIt helped us clear the loose rubbish,\nthen followed me when I left.$"
FG09_Text_Main11::
	.string "XAVIER: Did you ask whether it\nactually wanted to leave the dock?$"
FG09_Text_Main12::
	.string "TIM: I walked back. It came with me. I\nwalked here again. Still with me. I'm\prunning out of ways to make this less\nof a decision.$"
FG09_Text_Main13::
	.string "LB: Brian, hold your bowl straight. I'm\nnot pouring the whole thing into your\pshoe again.$"
FG09_Text_Main14::
	.string "BRIAN: There. Thanks. You could've\nmentioned the bowl part before you\pstarted tipping it.$"
FG09_Text_Main15::
	.string "LB: THANK ME LATER. Especially if\nyou're going to complain first.$"
FG09_Text_Main16::
	.string "BRIAN: I can thank you and complain.\nWe've known each other long enough\pfor you to understand that.$"
FG09_Text_Main17::
	.string "NICK: While you two work that out, give\nSlowpoke some room. It doesn't need\pthe bowl held against its face.$"
FG09_Text_Main18::
	.string "BRIAN: So now I've got two mouths to\nfeed and one bag they both think\pbelongs to them.$"
FG09_Text_Main19::
	.string "TIM: You were asking for somewhere to\nlive. You've accidentally started a\phousehold.$"
FG09_Text_Main20::
	.string "NICK: Could be worse. Mine helps move\nthe furniture.$"
FG09_Text_Main21::
	.string "XAVIER: Nobody is making Geodude\ncarry Brian because he says his feet\phurt.$"
FG09_Text_Main22::
	.string "TIM: Before he asks, how about a\nbattle? Just me. Spearow and Krabby\pcould use a proper practice match.$"
FG09_Text_Choice0_01::
	.string "TIM: Give me a second to get them\nready. The rope trick wasn't a battle\pmove, no matter what Jon called it.$"
FG09_Text_Choice0_02::
	.string "NICK: That's already a better start\nthan making the move up after the\pmatch begins.$"
FG09_Text_Choice1_01::
	.string "TIM: Spearow checks the road ahead.\nKrabby checks whether anything on\pthe ground needs pinching. We're\nworking on making that a shorter list.$"
FG09_Text_Choice1_02::
	.string "BRIAN: Slowpoke and I handle the rest\nstops.$"
FG09_Text_Choice1_03::
	.string "NICK: And Geodude and I make sure the\nrest stop isn't in the middle of the\ppath. It's a whole operation now.$"
FG09_Text_Choice2_01::
	.string "TIM: No problem. We'll get them fed\nfirst. Practice can wait.$"
FG09_Text_Choice2_02::
	.string "BRIAN: See? A professional\nunderstands the schedule.$"
FG09_Text_Choice2_03::
	.string "NICK: Your schedule was a nap. This is\nstill about feeding the Pokémon.$"
FG10_Text_Main01::
	.string "XAVIER: We're checking who owns the\nbuilding before anybody fills out\panother application.$"
FG10_Text_Main02::
	.string "BRIAN: You say that like I signed\nanything. I asked whether they had\premote positions.$"
FG10_Text_Main03::
	.string "NICK: We are already as remote as\npeople can physically get.$"
FG10_Text_Main04::
	.string "TIM: I asked about transport work.\nCarrying supplies, arranging trips.\pThat part sounded normal.$"
FG10_Text_Main05::
	.string "XAVIER: The first warning was the\nuniform.$"
FG10_Text_Main06::
	.string "LB: Plenty of legitimate places have\nbad uniforms. You can't put a company\pon trial because the jacket's ugly.$"
FG10_Text_Main07::
	.string "JON: THE SECOND WARNING WAS “STEAL\nPOKÉMON.”$"
FG10_Text_Main08::
	.string "TIM: They called it acquisition. I\nthought they meant collecting\psomething that somebody had ordered.$"
FG10_Text_Main09::
	.string "NICK: Which is why I asked whether the\nperson handing it over had agreed.$"
FG10_Text_Main10::
	.string "BRIAN: And he said that depended on\nhow quickly we wanted to get paid.\pThat was a pretty bad answer.$"
FG10_Text_Main11::
	.string "XAVIER: That's where the interview\nended. We weren't negotiating our way\pinto a crime.$"
FG10_Text_Main12::
	.string "LB: For the record, I'd already put the\npen down. The jacket defense ended\pwith the stealing part.$"
FG10_Text_Main13::
	.string "TIM: There's a delivery place on this\nlist. Actual parcels. We can ask at the\pcounter instead of following a\nstranger upstairs.$"
FG10_Text_Main14::
	.string "JON: GOOD. I WOULD LIKE ONE FUCKING\nDAY WHERE THE JOB IS THE JOB.$"
FG10_Text_Main15::
	.string "NICK: Then ask what it is before you\ntell them you can do it.$"
FG10_Text_Main16::
	.string "JON: I CAN CARRY A BOX.$"
FG10_Text_Main17::
	.string "NICK: I know. I meant what is in the\nbox.$"
FG10_Text_Main18::
	.string "BRIAN: And whether the job requires\ngoing somewhere. People keep hiding\pthat part in the word delivery.$"
FG10_Text_Main19::
	.string "TIM: I'll handle the routes. You can\nsort things at the depot if they need\psomeone there.$"
FG10_Text_Main20::
	.string "BRIAN: Indoors? With a chair?$"
FG10_Text_Main21::
	.string "XAVIER: We don't know yet. We're going\nto ask normal questions and leave if\pthe answers are bad.$"
FG10_Text_Main22::
	.string "LB: That's what we did last time. Bad\nplace, good exit. Give us a little\pcredit.$"
FG10_Text_Main23::
	.string "NICK: You can have credit when\neveryone gets paid by a business that\pstill exists tomorrow.$"
FG10_Text_Main24::
	.string "TIM: Come on. We'll lead with the box\nquestion this time.$"
FG10_Text_Repeat::
	.string "XAVIER: We ask what the job is before\nagreeing. The next one is legitimate\pwork.$"
FG11_Text_Main01::
	.string "BRIAN: Stop. Don't step in that.$"
FG11_Text_Main02::
	.string "TIM: It's a puddle. We have passed\nseveral without a meeting.$"
FG11_Text_Main03::
	.string "BRIAN: That's my couch. Look at the\narm. The bit Nick keeps saying isn't\pbroken.$"
FG11_Text_Main04::
	.string "NICK: It isn't broken. You sit on the\narm instead of the part designed for\psitting.$"
FG11_Text_Main05::
	.string "XAVIER: Brian, keep your feet there.\nTim, move back. I want to see whether\pthe picture moves with us.$"
FG11_Text_Main06::
	.string "TIM: Can you see the laptop? It's\nsupposed to be on the table.$"
FG11_Text_Main07::
	.string "BRIAN: Could we get the seven missing\npeople home before checking your\ptravel tabs?$"
FG11_Text_Main08::
	.string "NICK: From you, that's incredible. Give\nme a second. This strap's caught.$"
FG11_Text_Main09::
	.string "HAM: Nick. Stay there.$"
FG11_Text_Main10::
	.string "JON: HOLY SHIT. THAT'S THE DOOR. WE CAN\nGO THROUGH THE…$"
FG11_Text_Main11::
	.string "XAVIER: Wait. We don't know that.\nNobody jump into it.$"
FG11_Text_Main12::
	.string "BRIAN: I can see the table. That's\nwhere we were sitting. I was right\pthere.$"
FG11_Text_Main13::
	.string "TIM: It shut it. We were right there\nand it just shut it.$"
FG11_Text_Main14::
	.string "NICK: Brian. Come back a step. You're\ngoing to fall in.$"
FG11_Text_Main15::
	.string "BRIAN: I'm fine. I just wanted to\ncheck. Maybe it was still under the\psurface or something.$"
FG11_Text_Main16::
	.string "XAVIER: It lined up when all seven of\nus were here. That's worth writing\pdown. It doesn't mean we can make it\nopen.$"
FG11_Text_Main17::
	.string "JON: SO WE FINALLY FIND THE EXIT AND\nTHE GIANT BASTARD LOCKS IT?$"
FG11_Text_Main18::
	.string "NICK: We found a way to see home.\nThat's more than we had this morning.$"
FG11_Text_Main19::
	.string "HAM: And it didn't look right until Nick\ngot here. So no leaving anybody.$"
FG11_Text_Main20::
	.string "TIM: Was leaving somebody an option we\nwere seriously considering?$"
FG11_Text_Main21::
	.string "JON: NO. EVEN YOU. NOW COME AWAY FROM\nTHE WATER.$"
FG11_Text_Choice0_01::
	.string "NICK: Together. That's the part we've\nfigured out. The rest can take a little\plonger.$"
FG11_Text_Choice0_02::
	.string "BRIAN: I hate that the sensible answer\nis more walking.$"
FG11_Text_Choice0_03::
	.string "TIM: We walk until we know where we're\ngoing. Then I'll find the ride.$"
FG11_Text_Choice1_01::
	.string "XAVIER: The thing that brought us\nhere. Same shape, same way the\preflection bent around it. I don't\nthink it's finished with us.$"
FG11_Text_Choice1_02::
	.string "NICK: That's what we think. We don't\nknow why it opened this much, or why it\pstopped.$"
FG11_Text_Choice1_03::
	.string "XAVIER: Right. I'll write down what\nhappened before we turn the rest into\pa story we can't prove.$"
FG12_Text_Main01::
	.string "JON: I COACHED THAT WHOLE FUCKING\nMATCH FROM THE SOFA.$"
FG12_Text_Main02::
	.string "NICK: They couldn't hear you. Nobody\nplaying could hear you.$"
FG12_Text_Main03::
	.string "BRIAN: That's good coaching. It\ntranscends latency.$"
FG12_Text_Main04::
	.string "NICK: It annoyed everyone else\nwatching, which is a different\pachievement.$"
FG12_Text_Main05::
	.string "JON: I WAS SUPPORTING THE TRAINER.$"
FG12_Text_Main06::
	.string "TIM: The woman beside us moved three\nseats away. She was supporting her\phearing.$"
FG12_Text_Main07::
	.string "LB: You were quiet for about thirty\nseconds at the end. I thought\psomething was wrong with the screen.$"
FG12_Text_Main08::
	.string "JON: I WAS TAKING IT IN. I'M ALLOWED TO\nTAKE IT IN.$"
FG12_Text_Main09::
	.string "BRIAN: He did. Sat right back and\neverything. First time the sofa got\pits money's worth.$"
FG12_Text_Main10::
	.string "HAM: Can the Champion eat before we\nreplay the whole room?$"
FG12_Text_Main11::
	.string "NICK: He's right. Congratulations.\nProperly. That was a lot of work to get\pthrough.$"
FG12_Text_Main12::
	.string "LB: Must be strange. Everyone's\nlooking at you, and you're still the\pperson who has to find somewhere to\nput the bag down.$"
FG12_Text_Main13::
	.string "BRIAN: That's why we've got a chair. I'm\ngood at the part after the\pachievement.$"
FG12_Text_Main14::
	.string "XAVIER: We also have our next route.\nTim checked the directions while the\prest of you argued about seating.$"
FG12_Text_Main15::
	.string "TIM: Johto. Ordinary roads, actual\nplace on the map. I'm trying something\pnew.$"
FG12_Text_Main16::
	.string "BRIAN: How far is ordinary?$"
FG12_Text_Main17::
	.string "NICK: Farther than your chair. Closer\nthan your living room.$"
FG12_Text_Main18::
	.string "XAVIER: We know the reflection can\nshow home. We still need to learn why it\pdoes. Sitting here won't answer that.$"
FG12_Text_Main19::
	.string "BRIAN: Fine. But we leave after\neveryone eats. That's a travel\pcondition now, not a complaint.$"
FG12_Text_Main20::
	.string "TIM: Agreed. Nobody gets loaded onto\nthe next leg hungry. Where are you\pheaded?$"
FG12_Text_Choice0_01::
	.string "XAVIER: We're spending less on\nbandages and more on food. We've got\pwork when we need it, and everyone\nchecks for the Pokémon before we move\pcamp now.$"
FG12_Text_Choice0_02::
	.string "NICK: We're still trying to get home. We\njust stopped treating everything\pbetween here and there like a mistake.$"
FG12_Text_Choice0_03::
	.string "BRIAN: I can like this table and still\nmiss my own kitchen. Both things are\pallowed.$"
FG12_Text_Choice0_04::
	.string "TIM: Next stop's Johto. We'll see what\nwe can learn there.$"
FG12_Text_Choice1_01::
	.string "TIM: Already checked the directions\nfor our trip. Give us a head start with\pBrian.$"
FG12_Text_Choice1_02::
	.string "BRIAN: You all keep saying that like\nI'm the only one who sits down. I just\ppick better places.$"
FG12_Text_Choice1_03::
	.string "NICK: We can compare notes when we\nget there. Travel notes, Brian. Not a\pranked list of benches.$"
FG12_Text_Choice1_04::
	.string "BRIAN: You're going to want that list\neventually.$"
FG13_Text_Main01::
	.string "BRIAN: So do we get another starter\nhere?$"
FG13_Text_Main02::
	.string "NICK: You have two Pokémon. One is\nsitting on your foot.$"
FG13_Text_Main03::
	.string "BRIAN: I meant a starter apartment.\nSomewhere with a tap, a door, an\paddress I can say without pointing at\na tree.$"
FG13_Text_Main04::
	.string "XAVIER: We've found somewhere to\nstay. We still have to walk to it.$"
FG13_Text_Main05::
	.string "BRIAN: See how you waited until the\nsecond sentence to ruin it?$"
FG13_Text_Main06::
	.string "JON: AND WE'RE CARRYING THE SAME\nFUCKING BAGS. I THOUGHT A NEW REGION\pMIGHT COME WITH A TROLLEY.$"
FG13_Text_Main07::
	.string "NICK: New place. Same belongings.\nNothing said we were starting over.$"
FG13_Text_Main08::
	.string "XAVIER: Good. We've put a lot of work\ninto getting this far without losing\peach other.$"
FG13_Text_Main09::
	.string "JON: HAM. YOUR ARM'S GOT A FACE.$"
FG13_Text_Main10::
	.string "HAM: I know.$"
FG13_Text_Main11::
	.string "NICK: How long have you known?$"
FG13_Text_Main12::
	.string "HAM: Since camp. It climbed in when I\npicked my coat up.$"
FG13_Text_Main13::
	.string "XAVIER: And you carried it all the way\nhere without saying anything?$"
FG13_Text_Main14::
	.string "HAM: It was asleep. I didn't need\nanything from that arm.$"
FG13_Text_Main15::
	.string "BRIAN: That's the most reasonable\nexplanation anybody's given us in two\pregions.$"
FG13_Text_Main16::
	.string "NICK: Give it a minute on the ground.\nIt should be able to leave if it wants.$"
FG13_Text_Main17::
	.string "HAM: That's what I'm doing.$"
FG13_Text_Main18::
	.string "XAVIER: If it stays, we'll need enough\nfood for another partner. We can ask\pwhat it needs before we leave town.$"
FG13_Text_Main19::
	.string "HAM: I'm not a bitch. I'm not letting it\ngo hungry.$"
FG13_Text_Main20::
	.string "NICK: Nobody said you would. You can\njust say you want it to stay.$"
FG13_Text_Main21::
	.string "HAM: Alright. I want it to stay.$"
FG13_Text_Main22::
	.string "BRIAN: Congratulations. You've got two\nnow. Does that qualify either of us for\pthe apartment?$"
FG13_Text_Main23::
	.string "XAVIER: It qualifies us to check\nwhether the place we're staying has\proom for the Pokémon.$"
FG13_Text_Main24::
	.string "NICK: Come on. Ham can use both arms\nagain. That's practically extra\pluggage capacity.$"
FG13_Text_Repeat::
	.string "NICK: Same team, same journey. Ham can\nuse both arms again.$"
FG14_Text_Main01::
	.string "XAVIER: We saw a room where the water\nshould have been. Seven energies,\preflected through the cosmic…$"
FG14_Text_Main02::
	.string "RESEARCHER: Is that a sofa?$"
FG14_Text_Main03::
	.string "XAVIER: Yes. Brian's. We recognized the\nroom.$"
FG14_Text_Main04::
	.string "RESEARCHER: Then start there. You\ndrew something you recognized. What\pdid you actually see it do?$"
FG14_Text_Main05::
	.string "NICK: There he is. Ask him a question\nwith an answer and he's much easier to\pfollow.$"
FG14_Text_Main06::
	.string "XAVIER: It widened when Nick joined\nus. Before that, only six of us lined up\pin the reflection. Then the shadow\ncrossed it and it closed.$"
FG14_Text_Main07::
	.string "RESEARCHER: Did you see the room from\nanother position, or did everyone stay\pin the same place?$"
FG14_Text_Main08::
	.string "NICK: We mostly stayed put. It was a\ngood view, but nobody was thinking\pabout taking notes yet.$"
FG14_Text_Main09::
	.string "LB: Call that page VIEWS. Better title\nthan whatever cosmic thing X was\pabout to name it.$"
FG14_Text_Main10::
	.string "XAVIER (to LB): Nigga, I'm trying to\nremember which side of the water we\pstood on. Help me with that before you\nreview the album.$"
FG14_Text_Main11::
	.string "LB: Brian was on the left. Tim kept\nleaning over him to look for the\plaptop. I was behind Tim, wishing he'd\nmove. That's your view.$"
FG14_Text_Main12::
	.string "XAVIER: That helps. I had you and Tim\nthe other way around.$"
FG14_Text_Main13::
	.string "RESEARCHER: Keep observations like\nthat separate from what you think\pcaused them. You might find a pattern\nlater. You might also find your first\pexplanation was wrong.$"
FG14_Text_Main14::
	.string "XAVIER: So the seven people could\nmatter, or Nick could have stepped\pforward at the same moment something\nelse happened.$"
FG14_Text_Main15::
	.string "RESEARCHER: From what you've told me,\nyou can't distinguish those\ppossibilities yet.$"
FG14_Text_Main16::
	.string "NICK: Which means we aren't making Ham\nstand in every pond we pass to test it.$"
FG14_Text_Main17::
	.string "LB: He would, too. You'd get halfway\nthrough explaining the experiment and\phear the splash.$"
FG14_Text_Main18::
	.string "XAVIER: Nobody's standing in a pond.\nI'll make two lists. What happened, and\pwhat we're guessing.$"
FG14_Text_Main19::
	.string "RESEARCHER: That sounds useful. The\nruins are worth observing carefully as\pwell, but I have no evidence that they\ncaused your crossing.$"
FG14_Text_Main20::
	.string "XAVIER: Understood. We'll leave your\nwork alone. We've already got enough\punanswered questions of our own.$"
FG14_Text_Choice0_01::
	.string "XAVIER: It shows home. The picture\nchanged when we were all together. The\psame shadow appeared before it shut.\nWhy any of that happened is still a\pguess.$"
FG14_Text_Choice0_02::
	.string "NICK: That's enough to remember\nwithout pretending it's a set of\pinstructions.$"
FG14_Text_Choice0_03::
	.string "LB: And we know which side Tim was\nstanding on. Put my name next to that\pdiscovery.$"
FG14_Text_Choice1_01::
	.string "XAVIER: Carefully. Next time I'll watch\nbefore I explain it. Guessing already\pmade the story more complicated than\nthe facts.$"
FG14_Text_Choice1_02::
	.string "NICK: I'll keep everyone back from the\nedge. You take the notes.$"
FG14_Text_Choice1_03::
	.string "LB: I'll remember the part you both\nmiss while you're telling everyone to\pstand still.$"
FG15_Text_Main01::
	.string "JON: COME HERE, YOU LITTLE…$"
FG15_Text_Main02::
	.string "NICK: Stay where you are.$"
FG15_Text_Main03::
	.string "JON: I'm trying to see if its wing's\nalright.$"
FG15_Text_Main04::
	.string "NICK: Then give it enough room to show\nyou.$"
FG15_Text_Main05::
	.string "JON: It keeps moving away.$"
FG15_Text_Main06::
	.string "NICK: You keep following it and\nshouting. Sit down for a second.$"
FG15_Text_Main07::
	.string "JON: This is the whole plan? Sit here?$"
FG15_Text_Main08::
	.string "NICK: For now. Let it work out what\nyou're doing.$"
FG15_Text_Main09::
	.string "BRIAN: Slowpoke and I have been using\nthis strategy for weeks.$"
FG15_Text_Main10::
	.string "JON: You're both asleep for most of it.$"
FG15_Text_Main11::
	.string "BRIAN: And yet nobody's running away\nfrom us.$"
FG15_Text_Main12::
	.string "NICK: Try talking like you aren't\narguing across a parking lot.$"
FG15_Text_Main13::
	.string "JON: Alright. I'm staying here. You can\ndo whatever the fuck you want.$"
FG15_Text_Main14::
	.string "NICK: Bit more swearing than I had in\nmind. Volume's good.$"
FG15_Text_Main15::
	.string "JON: It doesn't like that.$"
FG15_Text_Main16::
	.string "NICK: Then don't do that. You're\ngetting it.$"
FG15_Text_Main17::
	.string "JON: There's water over there. Brian's\nchecked it about six times.$"
FG15_Text_Main18::
	.string "BRIAN: It's clean. You can stop making\nthat sound suspicious.$"
FG15_Text_Main19::
	.string "JON: You want to sit here, that's fine.$"
FG15_Text_Main20::
	.string "NICK: See? It got to choose.$"
FG15_Text_Main21::
	.string "JON: Yeah. I saw.$"
FG15_Text_Main22::
	.string "BRIAN: You could try that voice with\npeople.$"
FG15_Text_Main23::
	.string "JON: Don't ruin this for me.$"
FG15_Text_Repeat::
	.string "JON: He can hear me. I am giving him\nroom.$"
FG16_Text_Main01::
	.string "LB: That's the same wrapper. I watched\nyou take it back out.$"
FG16_Text_Main02::
	.string "NICK: It keeps bringing it to you.$"
FG16_Text_Main03::
	.string "LB: I know. I appreciate the thought.\nWe just can't carry loose rubbish\pthrough every town.$"
FG16_Text_Main04::
	.string "NICK: Maybe it wants to carry\nsomething else. Or come with us.$"
FG16_Text_Main05::
	.string "LB: You can come without bringing a\npresent. Jigglypuff's already taking\pup most of my bag anyway.$"
FG16_Text_Main06::
	.string "JON: PRIMEAPE! FUCK HIM UP!$"
FG16_Text_Main07::
	.string "NICK: Pick a move.$"
FG16_Text_Main08::
	.string "JON: THAT WAS THE MOVE.$"
FG16_Text_Main09::
	.string "NICK: That's an objective. How's\nPrimeape supposed to do it?$"
FG16_Text_Main10::
	.string "HAM: I'm not a bitch. Psyduck, stare\nharder.$"
FG16_Text_Main11::
	.string "NICK: That's also an objective. Both of\nyou, stop. Let them wait.$"
FG16_Text_Main12::
	.string "HAM: He's very good at staring.$"
FG16_Text_Main13::
	.string "NICK: I believe you. What actual moves\nhave you practiced together?$"
FG16_Text_Main14::
	.string "HAM: I know them. I thought I could\nease him into it.$"
FG16_Text_Main15::
	.string "JON: I know Primeape's. He just moves\nfaster when I get into it.$"
FG16_Text_Main16::
	.string "NICK: You can be excited and still tell\nhim what you're asking for. One\pcommand. Then watch what happens.$"
FG16_Text_Main17::
	.string "JON: And I wait for Ham?$"
FG16_Text_Main18::
	.string "HAM: I'm standing right fucking here.$"
FG16_Text_Main19::
	.string "NICK: Good. You both know where the\nother person is. Already better than\pthe first attempt.$"
FG16_Text_LegalPsyduck::
	.string "HAM: Psyduck, WATER GUN. One command,\nthen I wait.$"
FG16_Text_LegalPrimeape::
	.string "JON: Primeape, KARATE CHOP. Alright. I\nam waiting.$"
FG16_Text_Main20::
	.string "HAM: He did exactly what I said.$"
FG16_Text_Main21::
	.string "JON: Yeah. Mine too.$"
FG16_Text_Main22::
	.string "NICK: Keep that feeling. That's the\npart you're trying to repeat.$"
FG16_Text_Main23::
	.string "LB: Murkrow watched the entire thing\nwithout stealing anything. We're all\phaving a good day.$"
FG16_Text_Main24::
	.string "HAM: Want to go? I know what I'm doing\nnow. Mostly.$"
FG16_Text_Keep1::
	.string "HAM: He knows what I mean.$"
FG16_Text_Keep2::
	.string "NICK: He does now. Keep giving him\nsomething he can actually do.$"
FG16_Text_Keep3::
	.string "HAM: Alright. One more slow one.$"
FG17_Text_Main01::
	.string "BRIAN: That corner gets sun in the\nafternoon.$"
FG17_Text_Main02::
	.string "NICK: You're looking at your actual\nhouse and that's the first thing you\psay?$"
FG17_Text_Main03::
	.string "BRIAN: Slowpoke could sleep there.\nThere's room if I move the little table.$"
FG17_Text_Main04::
	.string "NICK: The table you wouldn't move when\nwe had six people squeezed onto the\pcouch?$"
FG17_Text_Main05::
	.string "BRIAN: That table had a job. It can\nhave a different job.$"
FG17_Text_Main06::
	.string "NICK: Where does your other roommate\ngo?$"
FG17_Text_Main07::
	.string "BRIAN: Away from the cables. I'll put\nthem through something he can't chew.\pProbably should have done that before\nwe left.$"
FG17_Text_Main08::
	.string "NICK: You've thought about this a lot.$"
FG17_Text_Main09::
	.string "BRIAN: Every time I think about\ngetting home, I get to the door and\pthen realize I don't know where\neverybody sleeps.$"
FG17_Text_Main10::
	.string "XAVIER: We can solve beds. We don't\nknow if the crossing will let them\pthrough.$"
FG17_Text_Main11::
	.string "BRIAN: Then we need to find that out\nbefore we go anywhere.$"
FG17_Text_Main12::
	.string "XAVIER: Agreed. I just don't want us\ntreating a reflection like a ticket.$"
FG17_Text_Main13::
	.string "NICK: It hasn't even shown us a way to\nstep through yet.$"
FG17_Text_Main14::
	.string "BRIAN: I know. I'm making a floor plan,\nnot jumping in the fucking pond.$"
FG17_Text_Main15::
	.string "LB: Put something over that mirror by\nthe door. Murkrow is going to think\pyou've brought it an enormous present.$"
FG17_Text_Main16::
	.string "XAVIER: And somewhere Jigglypuff can\nsleep without the television keeping\pit up.$"
FG17_Text_Main17::
	.string "LB: I can manage that. It puts up with\nme. I can turn a television down.$"
FG17_Text_Main18::
	.string "BRIAN: There. It can see us. It can see\nwho's with us.$"
FG17_Text_Main19::
	.string "HAM: Then we ask with everyone there.$"
FG17_Text_Main20::
	.string "NICK: And if the doorway's only wide\nenough for us?$"
FG17_Text_Main21::
	.string "XAVIER: We wait. Nobody crosses while\nwe're still guessing.$"
FG17_Text_Main22::
	.string "BRIAN: Fine. I can wait. I've finally\ngot someone worth moving the table\pfor.$"
FG17_Text_Repeat::
	.string "BRIAN: Nobody leaves a partner behind.\nI can wait.$"
FG18_Text_Main01::
	.string "TRAVELER: So I don't need to change\nboats again?$"
FG18_Text_Main02::
	.string "TIM: No. This one gets you to the stop\nyou wanted. I've checked with the\pclerk.$"
FG18_Text_Main03::
	.string "TRAVELER: The first person I asked\nsent us to the other end of the\pharbor.$"
FG18_Text_Main04::
	.string "TIM: Yeah, that sign is for arrivals.\nEasy mistake. Stay here with your\pPokémon; I'll carry this over when they\ncall you.$"
FG18_Text_Main05::
	.string "NICK: You sorted all that out?$"
FG18_Text_Main06::
	.string "TIM: There were two services with\nnearly the same name. One takes the\plong way round.$"
FG18_Text_Main07::
	.string "NICK: And you picked the short one.$"
FG18_Text_Main08::
	.string "TIM: I picked the one that gets them\nsomewhere familiar before they're\pexhausted. Apparently those aren't\nalways the same thing.$"
FG18_Text_Main09::
	.string "TRAVELER: I can take that one. You've\nalready done enough.$"
FG18_Text_Main10::
	.string "TIM: I've got it. Sit down for a minute.$"
FG18_Text_Main11::
	.string "TRAVELER: Thank you. We both needed\nto hear that.$"
FG18_Text_Main12::
	.string "TIM: There's water under the bench,\ntoo. The clerk said you could use it.$"
FG18_Text_Main13::
	.string "NICK: No detour? No twenty questions\nabout where to go after dark?$"
FG18_Text_Main14::
	.string "TIM: I'm capable of booking one\nfucking normal trip.$"
FG18_Text_Main15::
	.string "NICK: I can see that. I'm saying you\ndid a good thing.$"
FG18_Text_Main16::
	.string "TIM: Then stop looking like you caught\nme committing it.$"
FG18_Text_Main17::
	.string "NICK: Alright. Need a hand with that\nbag?$"
FG18_Text_Main18::
	.string "TIM: Yeah. Keep it level. Something in\nthere rattles, and I'd like one journey\pwhere we don't break somebody's stuff.$"
FG18_Text_Main19::
	.string "NICK: You checked the stop, the bags\nand the Pokémon. That's a complete\pplan.$"
FG18_Text_Main20::
	.string "TIM: I'm learning. Don't tell the others\nuntil I've had a chance to be annoying\pabout it myself.$"
FG18_Text_Choice0_1::
	.string "TIM: Don't make it weird. They needed a\nhand.$"
FG18_Text_Choice0_2::
	.string "NICK: Too late. I'm putting him in\ncharge of the bags.$"
FG18_Text_Choice0_3::
	.string "TIM: You can carry your own shit.$"
FG18_Text_Choice1_1::
	.string "TIM: With this lot. Unfortunately.$"
FG18_Text_Choice1_2::
	.string "NICK: He already checked our route\ntoo.$"
FG18_Text_Choice1_3::
	.string "TIM: Someone has to get you idiots to\nthe same place.$"
FG19_Text_Main01::
	.string "BRIAN: Food's over there. Water's here.\nThe attendant said to leave this\pcorner quiet.$"
FG19_Text_Main02::
	.string "NICK: Want me to move the spare\nblankets?$"
FG19_Text_Main03::
	.string "BRIAN: Leave two. Ham can't reach his\nwithout getting up.$"
FG19_Text_Main04::
	.string "NICK: Got it.$"
FG19_Text_Main05::
	.string "JON: Easy. Nobody's taking you\nanywhere. We're just sitting here.$"
FG19_Text_Main06::
	.string "NICK: Keep doing that. It's watching\nyour partner settle.$"
FG19_Text_Main07::
	.string "JON: Yeah. We can stay a bit.$"
FG19_Text_Main08::
	.string "LB: Not singing right now. I know you\nwant to help. Come sit with me.$"
FG19_Text_Main09::
	.string "XAVIER: You can help me spread this\none out instead.$"
FG19_Text_Main10::
	.string "LB: Hold it there. I'll get this side.$"
FG19_Text_Main11::
	.string "XAVIER: Then take that corner. We'll\nkeep it flat.$"
FG19_Text_Main12::
	.string "LB: Yeah. I've got it.$"
FG19_Text_Main13::
	.string "TIM: You've been there three hours.\nWant me to sit here while you stretch?$"
FG19_Text_Main14::
	.string "HAM: I'm awake.$"
FG19_Text_Main15::
	.string "TIM: Didn't ask that. I can take a turn.$"
FG19_Text_Main16::
	.string "HAM: In a minute. It's nearly asleep.$"
FG19_Text_Repeat::
	.string "NICK: We can stay a bit. Keep this\ncorner quiet.$"
FG20_Text_Main01::
	.string "NICK: You can put the diagram away. I\nwas there.$"
FG20_Text_Main02::
	.string "BRIAN: Then you saw the opening. I had\nthe right idea.$"
FG20_Text_Main03::
	.string "NICK: You did. You just changed your\nmind after giving the command.$"
FG20_Text_Main04::
	.string "BRIAN: In 2K I can adjust while the\nplay's moving.$"
FG20_Text_Main05::
	.string "NICK: Here you've got somebody\nlistening to you. Give them time to\pfinish what you asked.$"
FG20_Text_Main06::
	.string "BRIAN: Alright. One plan at a time. I\ncan do that.$"
FG20_Text_Main07::
	.string "JON: I HAVE BEEN USING MY INSIDE…$"
FG20_Text_Main08::
	.string "NICK: You were. Just then, before the\nannouncement.$"
FG20_Text_Main09::
	.string "JON: I'm telling you I've been\npracticing.$"
FG20_Text_Main10::
	.string "NICK: I can see it. Noctowl can hear\nyou from there.$"
FG20_Text_Main11::
	.string "HAM: So can everybody in town when you\ndo the other one.$"
FG20_Text_Main12::
	.string "JON: You want to battle or do fucking\ncommentary?$"
FG20_Text_Main13::
	.string "HAM: Battle. I brought both of mine.$"
FG20_Text_Main14::
	.string "BRIAN: We all brought both of ours.\nThat's the thing we're doing.$"
FG20_Text_Main15::
	.string "LB: Are we doing introductions? I\ncould make mine sound good.$"
FG20_Text_Main16::
	.string "NICK: Say their names. Say you're\nready. You'll sound like a trainer.$"
FG20_Text_Main17::
	.string "LB: I am a trainer. I have receipts in\nthe form of several extremely\pembarrassing losses.$"
FG20_Text_Main18::
	.string "XAVIER: Which you've learned from.\nSome of them more than once.$"
FG20_Text_Main19::
	.string "LB: You're really going to say that\nwhile standing here with your little\pbattle notes?$"
FG20_Text_Main20::
	.string "XAVIER: Yes. These are the things I\nlearned from losing.$"
FG20_Text_Main21::
	.string "NICK: Pick whoever you feel like.\nNobody has to fight seven people in a\prow.$"
FG20_Text_Main22::
	.string "BRIAN: And if you need a break, I've\nalready found the good rock to sit on.$"
FG20_Text_How1::
	.string "NICK: Still confused. Better company\nthan we were when we landed.$"
FG20_Text_How2::
	.string "BRIAN: I know what everybody eats\nnow. That's got to count for\psomething.$"
FG20_Text_How3::
	.string "XAVIER: It does. Getting home is the\nnext thing to figure out, not a prize\pfor winning today.$"
FG20_Text_Later1::
	.string "BRIAN: Excellent. Training break.$"
FG20_Text_Later2::
	.string "JON: Come on. We can wait.$"
FG21_Text_Main01::
	.string "BRIAN: That's home. Same couch. Same\nstupid cushion that keeps falling\pdown.$"
FG21_Text_Main02::
	.string "NICK: You want a minute?$"
FG21_Text_Main03::
	.string "BRIAN: I've wanted to go back since we\ngot here. Now I keep checking I've\ppacked enough food.$"
FG21_Text_Main04::
	.string "NICK: You've packed enough. I checked\nafter you checked.$"
FG21_Text_Main05::
	.string "HAM: They're coming with us.$"
FG21_Text_Main06::
	.string "XAVIER: We know. Nobody steps through\nuntil we know there's room for\peveryone.$"
FG21_Text_Main07::
	.string "HAM: Good. Just saying it where that\nthing can hear.$"
FG21_Text_Main08::
	.string "TIM: Could we do Thailand first?$"
FG21_Text_Main09::
	.string "NICK: Read the room. For once in your\nfucking life.$"
FG21_Text_Main10::
	.string "TIM: Alright. Home first. I was trying\nto make this feel normal.$"
FG21_Text_Main11::
	.string "NICK: It did, unfortunately.$"
FG21_Text_Main12::
	.string "XAVIER: Seven people. Fourteen\nPokémon. Everybody has their own\pthings?$"
FG21_Text_Main13::
	.string "BRIAN: And most of everybody else's.\nApparently the largest bag becomes\pcommunal property.$"
FG21_Text_Main14::
	.string "NICK: You insisted we take the spare\nblankets.$"
FG21_Text_Main15::
	.string "BRIAN: Yeah. We might need them.$"
FG21_Text_Main16::
	.string "LB: I thought I'd have something good\nto say when this happened.$"
FG21_Text_Main17::
	.string "XAVIER: You don't have to turn it into\na speech.$"
FG21_Text_Main18::
	.string "LB: I know. I'm just going to miss\nhaving all of us in the same place\pevery morning.$"
FG21_Text_Main19::
	.string "BRIAN: We're going to my living room.\nYou'll be there until I throw you out.$"
FG21_Text_Main20::
	.string "NICK: So we'll see everybody tomorrow.$"
FG21_Text_Main21::
	.string "JON: You ready? We go together.$"
FG21_Text_Main22::
	.string "NICK: They both look ready.$"
FG21_Text_Main23::
	.string "JON: Yeah. Give me a second.$"
FG21_Text_Main24::
	.string "XAVIER: We can wait. There's no\nschedule on this one.$"
FG21_Text_Main25::
	.string "HAM: Everybody or nobody. We're good\nnow.$"
FG21_Text_Main26::
	.string "BRIAN: Right. I need a bigger couch.$"
FG21_Text_PriorThanks::
	.string "NICK: Thanks for putting up with us\nwhile we figured this out. You made\pthis place feel a lot less strange.$"
FG21_Text_LateThanks::
	.string "NICK: Thanks for seeing us off. This is\nweird enough without doing it alone.$"
FG21_Text_Tim1::
	.string "JON: WE'RE TAKING TIM TOO?$"
FG21_Text_Tim2::
	.string "TIM: Fuck all of you. I packed the\nsnacks.$"
FG21_Text_LastBattle::
	.string "NICK: Alright. Your pick. We can say\ngoodbye properly afterward.$"
FG21_Text_Stay1::
	.string "BRIAN: I already sat down.$"
FG21_Text_Stay2::
	.string "NICK: Then we'll sit with you.$"
FG22_Text_Main01::
	.string "BRIAN: Don't put that on the wet bit.\nIt has the towels in it.$"
FG22_Text_Main02::
	.string "NICK: You brought towels to the place\nwith the pond. Good preparation.$"
FG22_Text_Main03::
	.string "BRIAN: Slowbro likes this pond. I like\nhaving somewhere dry to sit after he\plikes it.$"
FG22_Text_Main04::
	.string "NICK: How'd the corner by the window\nwork out?$"
FG22_Text_Main05::
	.string "BRIAN: Great. Moved the table, put a\nbed down. He still sits beside the\pcouch when we're there.$"
FG22_Text_Main06::
	.string "NICK: You could have predicted that.$"
FG22_Text_Main07::
	.string "BRIAN: Yeah. I'm keeping the bed\nanyway. He should have options.$"
FG22_Text_Main08::
	.string "XAVIER: You managed to pack less this\ntime.$"
FG22_Text_Main09::
	.string "LB: I had a door I could close behind\nme. Changes your relationship with\pluggage.$"
FG22_Text_Main10::
	.string "XAVIER: Still felt strange, though.\nBrian's place looked the same.$"
FG22_Text_Main11::
	.string "LB (to XAVIER): Nigga, NOTHING WAS THE\nSAME.$"
FG22_Text_Main12::
	.string "XAVIER: I knew you were saving that.$"
FG22_Text_Main13::
	.string "LB: I'm serious. I spent the first night\nlooking for a Pokémon Center. Then\pBrian asked if I wanted tea and I\nremembered I could just sit down.\pNobody needed a route or a place to\nsleep.$"
FG22_Text_Main14::
	.string "XAVIER: You stayed standing for a\nwhile.$"
FG22_Text_Main15::
	.string "LB: Yeah. Then Jigglypuff went to\nsleep on my bag and made the decision\pfor me.$"
FG22_Text_Main16::
	.string "NICK: We all missed this place. Even\nthe parts we complained about.$"
FG22_Text_Main17::
	.string "BRIAN: I did not miss sleeping on\nroots. I missed the people near the\proots.$"
FG22_Text_Main18::
	.string "NICK: That's almost a nice thing to\nsay.$"
FG22_Text_Main19::
	.string "BRIAN: It's a very nice thing. I've\nbrought my own chair so I can say it\pwithout lying.$"
FG22_Text_Main20::
	.string "XAVIER: We didn't know if we'd get to\ncome back. When the passage opened,\pwe were ready.$"
FG22_Text_Main21::
	.string "NICK: No idea when it'll happen again.\nWe're glad we got this visit.$"
FG22_Text_Main22::
	.string "BRIAN: Now somebody sit down before\nthis turns into another fucking\ppacking meeting.$"
FG22_Text_Catch1::
	.string "XAVIER: We got home. Then we realized\nwe had people to visit here.$"
FG22_Text_Catch2::
	.string "BRIAN: And somewhere Slowbro would\nlike to sit. I understand him better\pnow.$"
FG22_Text_Catch3::
	.string "NICK: He's inviting you to sit down.\nThis is how he does that.$"
FG22_Text_Bye1::
	.string "BRIAN: You know where we'll be.\nSomewhere with seating.$"
FG22_Text_Bye2::
	.string "NICK: Take care of yourself. We'll be\nhere for this visit.$"
FG_Text_FinalInvitation0::
	.string "BRIAN: Ready for a match? We can wait\nif you would rather rest.$"
FG_Text_FinalInvitation1::
	.string "XAVIER: Ready for a match? We can wait\nif you would rather rest.$"
FG_Text_FinalInvitation2::
	.string "TIM: Ready for a match? We can wait if\nyou would rather rest.$"
FG_Text_FinalInvitation3::
	.string "LB: Ready for a match? We can wait if\nyou would rather rest.$"
FG_Text_FinalInvitation4::
	.string "NICK: Ready for a match? We can wait if\nyou would rather rest.$"
FG_Text_FinalInvitation5::
	.string "JON: Ready for a match? We can wait if\nyou would rather rest.$"
FG_Text_FinalInvitation6::
	.string "HAM: Ready for a match? We can wait if\nyou would rather rest.$"
FG_Text_BattleOrLater::
	.string "Battle now? Choose NO to leave freely.$"
FG_Text_CannotBattle::
	.string "NICK: Finish what you are doing and\nmake sure a partner is ready. We can\ppractice another time.$"
FG_Battle01_Won01::
	.string "BRIAN: That was input delay.$"
FG_Battle01_Won02::
	.string "NICK: You said the command out loud.$"
FG_Battle01_Won03::
	.string "BRIAN: And there was a delay between\nthinking it and saying it.$"
FG_Battle01_Won04::
	.string "NICK: That's you.$"
FG_Battle01_Won05::
	.string "BRIAN: I know what it is. I'm saying we\nshould account for it.$"
FG_Battle01_Won06::
	.string "NICK: Get Roommate some rest. Then we\ncan practice.$"
FG_Battle01_Won07::
	.string "BRIAN: See? He's already improving my\nschedule.$"
FG_Battle01_Lost01::
	.string "BRIAN: Home court. I live on this patch\nof grass.$"
FG_Battle01_Lost02::
	.string "NICK: You said we were leaving this\nmorning.$"
FG_Battle01_Lost03::
	.string "BRIAN: That was before I established a\ncompetitive advantage.$"
FG_Battle01_Lost04::
	.string "NICK: Congratulations. Pack the tent.$"
FG_Battle01_Lost05::
	.string "BRIAN: Good game. Apparently we're an\naway team now.$"
FG_Battle02_Won01::
	.string "JON: THAT WAS BULLSHIT.$"
FG_Battle02_Won02::
	.string "NICK: Which part?$"
FG_Battle02_Won03::
	.string "JON: THE ENDING.$"
FG_Battle02_Won04::
	.string "NICK: The rules didn't change at the\nend.$"
FG_Battle02_Won05::
	.string "JON: I'M AWARE. I'M REVIEWING THEM.$"
FG_Battle02_Won06::
	.string "NICK: Review them while you check on\nMankey.$"
FG_Battle02_Won07::
	.string "JON: You did alright. We'll figure it\nout.$"
FG_Battle02_Lost01::
	.string "JON: SEE? COMPLETELY FAIR SYSTEM.$"
FG_Battle02_Lost02::
	.string "NICK: You were drafting a complaint\nbefore the battle.$"
FG_Battle02_Lost03::
	.string "JON: AND I'VE WITHDRAWN IT.$"
FG_Battle02_Lost04::
	.string "NICK: Tell them good game.$"
FG_Battle02_Lost05::
	.string "JON: Good game. I still have some\nquestions about the system.$"
FG_Battle03_Won01::
	.string "NICK: Good match. I need to be clearer\nabout what I want Poliwag to do.$"
FG_Battle03_Won02::
	.string "BRIAN: You need a playbook.$"
FG_Battle03_Won03::
	.string "NICK: I need two things I can remember\nunder pressure.$"
FG_Battle03_Won04::
	.string "BRIAN: That's a small playbook.$"
FG_Battle03_Won05::
	.string "NICK: Fine. Get something to write on.$"
FG_Battle03_Won06::
	.string "BRIAN: Finally. An assistant-coach\nrole that involves sitting.$"
FG_Battle03_Lost01::
	.string "NICK: Good match. You alright?$"
FG_Battle03_Lost02::
	.string "BRIAN: Don't apologize for winning.$"
FG_Battle03_Lost03::
	.string "NICK: I didn't. I asked if they were\nalright.$"
FG_Battle03_Lost04::
	.string "BRIAN: Right. Sportsmanship.$"
FG_Battle03_Lost05::
	.string "NICK: We can go again another time. I'm\nstill learning this too.$"
FG_Battle04_Won01::
	.string "LB: Alright. That one's on me.$"
FG_Battle04_Won02::
	.string "XAVIER: That's a good start.$"
FG_Battle04_Won03::
	.string "LB: Why do you sound surprised?$"
FG_Battle04_Won04::
	.string "XAVIER: I was prepared for a longer\nconversation.$"
FG_Battle04_Won05::
	.string "LB (to XAVIER): Nigga, I'm accepting\nfeedback. Don't make it weird.$"
FG_Battle04_Won06::
	.string "XAVIER: Then let's get her some water.$"
FG_Battle04_Won07::
	.string "LB: Come on. You don't have to listen\nto his whole speech.$"
FG_Battle04_Lost01::
	.string "LB: That felt good. I'm allowed to say\nthat.$"
FG_Battle04_Lost02::
	.string "XAVIER: You are.$"
FG_Battle04_Lost03::
	.string "LB: Without you adding a lesson?$"
FG_Battle04_Lost04::
	.string "XAVIER: Water first. Then celebrate.$"
FG_Battle04_Lost05::
	.string "LB: There it is.$"
FG_Battle04_Lost06::
	.string "LB: Good battle. Seriously.$"
FG_Battle05_Won01::
	.string "XAVIER: Useful feedback.$"
FG_Battle05_Won02::
	.string "JON: YOU LOST.$"
FG_Battle05_Won03::
	.string "XAVIER: That was the feedback.$"
FG_Battle05_Won04::
	.string "JON: YOU CAN JUST SAY YOU LOST.$"
FG_Battle05_Won05::
	.string "XAVIER: I lost. I want to understand\nwhy.$"
FG_Battle05_Won06::
	.string "JON: ...Fine. Start with the ending.$"
FG_Battle05_Won07::
	.string "XAVIER: We'll work backward.$"
FG_Battle05_Lost01::
	.string "XAVIER: Good match. We were prepared\ntoday.$"
FG_Battle05_Lost02::
	.string "BRIAN: Is this the universe thing\nagain?$"
FG_Battle05_Lost03::
	.string "XAVIER: No. We ate, rested and\npracticed.$"
FG_Battle05_Lost04::
	.string "BRIAN: I did two of those.$"
FG_Battle05_Lost05::
	.string "XAVIER: Then you've identified the\nnext step.$"
FG_Battle05_Lost06::
	.string "BRIAN: I preferred it when you blamed\nenergy.$"
FG_Battle06_Won01::
	.string "TIM: Alright. We need a break.$"
FG_Battle06_Won02::
	.string "NICK: You and the Pokémon?$"
FG_Battle06_Won03::
	.string "TIM: Mostly them. I'll carry the stuff.$"
FG_Battle06_Won04::
	.string "NICK: I'll get the bag.$"
FG_Battle06_Won05::
	.string "TIM: Thanks. We can argue about the\nroute afterward.$"
FG_Battle06_Won06::
	.string "NICK: We absolutely will.$"
FG_Battle06_Lost01::
	.string "TIM: Good match. Everybody made it in\none piece.$"
FG_Battle06_Lost02::
	.string "NICK: That your new standard?$"
FG_Battle06_Lost03::
	.string "TIM: Pretty solid starting point in a\nworld with lightning animals.$"
FG_Battle06_Lost04::
	.string "NICK: Can't argue with that.$"
FG_Battle06_Lost05::
	.string "TIM: We'll be around when you want\nanother go.$"
FG_Battle07_Won01::
	.string "HAM: I'm still not a bitch.$"
FG_Battle07_Won02::
	.string "NICK: Nobody put that on the results\nscreen.$"
FG_Battle07_Won03::
	.string "HAM: I'm clarifying.$"
FG_Battle07_Won04::
	.string "NICK: You can lose and still have done\nalright.$"
FG_Battle07_Won05::
	.string "HAM: Yeah. They did alright.$"
FG_Battle07_Won06::
	.string "NICK: I meant you as well.$"
FG_Battle07_Won07::
	.string "HAM: ...Oh. Thanks.$"
FG_Battle07_GrowthWin1::
	.string "HAM: He did what I asked, though.$"
FG_Battle07_GrowthWin2::
	.string "NICK: He did. Now you get to work out\nwhat to ask next time.$"
FG_Battle07_GrowthWin3::
	.string "HAM: Alright. We're doing another\npractice after a rest.$"
FG_Battle07_Lost01::
	.string "HAM: Told you.$"
FG_Battle07_Lost02::
	.string "NICK: You said three unrelated things\nbefore that battle.$"
FG_Battle07_Lost03::
	.string "HAM: One of them was right.$"
FG_Battle07_Lost04::
	.string "NICK: Fair.$"
FG_Battle07_Lost05::
	.string "HAM: Good game. Psyduck wants a snack.$"
FG_Battle07_Lost06::
	.string "NICK: So do you.$"
FG_Battle07_Lost07::
	.string "HAM: We're a team.$"
FG_Battle07_GrowthLoss1::
	.string "HAM: We should do it like that again.$"
FG_Battle07_GrowthLoss2::
	.string "NICK: Clear command, then give him\ntime. Keep it.$"
FG_Battle08_Won01::
	.string "BRIAN: Good game. I'm still blaming the\ncontroller.$"
FG_Battle08_Won02::
	.string "NICK: There isn't one.$"
FG_Battle08_Won03::
	.string "BRIAN: Then we agree the hardware\nsituation is unacceptable.$"
FG_Battle08_Won04::
	.string "NICK: Your Pokémon did well.$"
FG_Battle08_Won05::
	.string "BRIAN: Yeah. They did. Come on, we've\nearned a seat.$"
FG_Battle08_FinalAfter::
	.string "NICK: Another match whenever you are\nready. Or we can just sit for a minute.$"
FG_Battle08_ReunionText::
	.string "NICK: Good match. You can stay for a\nbit if you want.$"
FG_Battle08_Lost01::
	.string "BRIAN: Good game. Hydrate. Get a\nsnack. Complete coaching system.$"
FG_Battle08_Lost02::
	.string "NICK: You actually practiced this time.$"
FG_Battle08_Lost03::
	.string "BRIAN: I'm saving that for the premium\ntier.$"
FG_Battle08_Lost04::
	.string "NICK: It's free advice.$"
FG_Battle08_Lost05::
	.string "BRIAN: And yet everybody wants more\nof it.$"
FG_Battle09_Won01::
	.string "XAVIER: Good battle. I have a few\nthings to work on.$"
FG_Battle09_Won02::
	.string "LB: You want a minute?$"
FG_Battle09_Won03::
	.string "XAVIER: I want to write them down\nbefore I forget.$"
FG_Battle09_Won04::
	.string "LB: Alright. I'll keep Jon away.$"
FG_Battle09_Won05::
	.string "XAVIER: That's the most useful thing\nanyone's offered.$"
FG_Battle09_FinalAfter::
	.string "NICK: Another match whenever you are\nready. Or we can just sit for a minute.$"
FG_Battle09_ReunionText::
	.string "NICK: Good match. You can stay for a\nbit if you want.$"
FG_Battle09_Lost01::
	.string "XAVIER: Good match. That felt like the\npractice was paying off.$"
FG_Battle09_Lost02::
	.string "LB: I was ready for you to thank the\nuniverse.$"
FG_Battle09_Lost03::
	.string "XAVIER: It can have a little credit.\nYou helped too.$"
FG_Battle09_Lost04::
	.string "LB: Say that louder. Brian's pretending\nhe can't hear you.$"
FG_Battle09_Lost05::
	.string "XAVIER: I'll put it in the minutes.$"
FG_Battle10_Won01::
	.string "TIM: Good battle. I'm getting these\ntwo some rest.$"
FG_Battle10_Won02::
	.string "NICK: Need a hand?$"
FG_Battle10_Won03::
	.string "TIM: Grab the bag. I'll take this lot.$"
FG_Battle10_Won04::
	.string "NICK: Look at us. Sensible\narrangements.$"
FG_Battle10_Won05::
	.string "TIM: Don't get used to it.$"
FG_Battle10_FinalAfter::
	.string "NICK: Another match whenever you are\nready. Or we can just sit for a minute.$"
FG_Battle10_ReunionText::
	.string "NICK: Good match. You can stay for a\nbit if you want.$"
FG_Battle10_Lost01::
	.string "TIM: Good game. You've given us\nsomething to brag about on the way\pback.$"
FG_Battle10_Lost02::
	.string "NICK: How long is the way back?$"
FG_Battle10_Lost03::
	.string "TIM: Depends how long I can keep Brian\nwalking.$"
FG_Battle10_Lost04::
	.string "NICK: You have about eleven minutes.$"
FG_Battle10_Lost05::
	.string "TIM: I'll use them well.$"
FG_Battle11_Won01::
	.string "LB: Good battle. I need some water.$"
FG_Battle11_Won02::
	.string "XAVIER: I'll come with you.$"
FG_Battle11_Won03::
	.string "LB: You're not going to explain the\nwhole thing on the way?$"
FG_Battle11_Won04::
	.string "XAVIER: Only if you ask.$"
FG_Battle11_Won05::
	.string "LB: Alright. Start with one thing.$"
FG_Battle11_Won06::
	.string "XAVIER: You asked. Everybody heard\nthat.$"
FG_Battle11_FinalAfter::
	.string "NICK: Another match whenever you are\nready. Or we can just sit for a minute.$"
FG_Battle11_ReunionText::
	.string "NICK: Good match. You can stay for a\nbit if you want.$"
FG_Battle11_Lost01::
	.string "LB: Good game. I'm happy with that.$"
FG_Battle11_Lost02::
	.string "XAVIER: You should be. You put the\nwork in.$"
FG_Battle11_Lost03::
	.string "LB: Don't sound so surprised.$"
FG_Battle11_Lost04::
	.string "XAVIER: I didn't.$"
FG_Battle11_Lost05::
	.string "LB: I know. I'm still getting used to\nyou being sincere.$"
FG_Battle11_Lost06::
	.string "XAVIER: Take your time.$"
FG_Battle12_Won01::
	.string "NICK: That was good. I want another go\nwhen you're ready.$"
FG_Battle12_Won02::
	.string "BRIAN: I've got some notes.$"
FG_Battle12_Won03::
	.string "NICK: One note.$"
FG_Battle12_Won04::
	.string "BRIAN: Can it have subpoints?$"
FG_Battle12_Won05::
	.string "NICK: You get the walk back to camp.\nStart talking.$"
FG_Battle12_FinalAfter::
	.string "NICK: Another match whenever you are\nready. Or we can just sit for a minute.$"
FG_Battle12_ReunionText::
	.string "NICK: Good match. You can stay for a\nbit if you want.$"
FG_Battle12_Lost01::
	.string "NICK: Good match. Hope you had fun\nwith it.$"
FG_Battle12_Lost02::
	.string "BRIAN: We should review the footage.$"
FG_Battle12_Lost03::
	.string "NICK: There isn't any.$"
FG_Battle12_Lost04::
	.string "BRIAN: I remember enough.$"
FG_Battle12_Lost05::
	.string "NICK: This is your chance to leave.$"
FG_Battle13_Won01::
	.string "JON: Fuck. Good battle.$"
FG_Battle13_Won02::
	.string "NICK: That was almost graceful.$"
FG_Battle13_Won03::
	.string "JON: I'M ALLOWED TO BE ANNOYED.$"
FG_Battle13_Won04::
	.string "NICK: You are. You also said good\nbattle.$"
FG_Battle13_Won05::
	.string "JON: Because it was. Now let me be\nannoyed respectfully.$"
FG_Battle13_FinalAfter::
	.string "NICK: Another match whenever you are\nready. Or we can just sit for a minute.$"
FG_Battle13_ReunionText::
	.string "NICK: Good match. You can stay for a\nbit if you want.$"
FG_Battle13_Lost01::
	.string "JON: GOOD…$"
FG_Battle13_Lost02::
	.string "JON: Good battle.$"
FG_Battle13_Lost03::
	.string "NICK: You can celebrate.$"
FG_Battle13_Lost04::
	.string "JON: I know. The owl's right here.$"
FG_Battle13_Lost05::
	.string "NICK: Fair enough.$"
FG_Battle14_Won01::
	.string "HAM: Yeah. That was fair.$"
FG_Battle14_Won02::
	.string "NICK: You alright?$"
FG_Battle14_Won03::
	.string "HAM: They tried. I tried. Sometimes you\nlose.$"
FG_Battle14_Won04::
	.string "NICK: That's a pretty healthy way to\nlook at it.$"
FG_Battle14_Won05::
	.string "HAM: I'm going to ruin it if we keep\ntalking.$"
FG_Battle14_Won06::
	.string "NICK: Then we'll leave it there.$"
FG_Battle14_FinalAfter::
	.string "NICK: Another match whenever you are\nready. Or we can just sit for a minute.$"
FG_Battle14_ReunionText::
	.string "NICK: Good match. You can stay for a\nbit if you want.$"
FG_Battle14_Lost01::
	.string "HAM: I'm not a bitch.$"
FG_Battle14_Lost02::
	.string "NICK: There he is.$"
FG_Battle14_Lost03::
	.string "HAM: But that was close.$"
FG_Battle14_Lost04::
	.string "NICK: You can say that too.$"
FG_Battle14_Lost05::
	.string "HAM: Good game. We'll be here.$"
