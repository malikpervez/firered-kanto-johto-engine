@ Johto (data/maps/WhirlIslands_LugiaChamber_hns/scripts.inc), as built into the FireRed game.

WhirlIslands_LugiaChamber_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, WhirlIslands_LugiaChamber_OnTransition
	map_script 2, BlackTide_OnFrame
	map_script 7, BlackTide_OnReturnToField
	.byte 0

WhirlIslands_LugiaChamber_OnTransition:
	callnative RainbowVisuals_EndEncounter
	call BlackTide_UpdateVisibility
	setvar JOHTO_VAR_TEMP_2, 1
	goto_if_set FLAG_LG_LEGACY_EXEMPT, BlackTide_NativeTransition
	goto_if_set FLAG_LG_FINAL_RESOLVED, BlackTide_NativeTransition
	callnative Special_RainbowStoryAllReplicasResolved
	goto_if_eq JOHTO_VAR_RESULT, FALSE, BlackTide_HideNativeLugia

BlackTide_NativeTransition:
	goto_if_eq JOHTO_VAR_COMPLETED_LUGIA, 2, WhirlIslands_LugiaChamber_MapScript_LugiaStory
	goto_if_eq JOHTO_VAR_COMPLETED_LUGIA, 3, WhirlIslands_LugiaChamber_MapScript_LugiaPostStoryGone
	goto_if_eq JOHTO_VAR_COMPLETED_LUGIA, 4, WhirlIslands_LugiaChamber_MapScript_LugiaPostStoryEncounter
	end

WhirlIslands_LugiaChamber_MapScript_LugiaStory::
	clearflag JOHTO_FLAG_HIDE_LUGIA
	end

WhirlIslands_LugiaChamber_MapScript_LugiaPostStoryGone::
	setflag JOHTO_FLAG_HIDE_WHIRL_ISLANDS_KIMONO_GIRLS
	setflag JOHTO_FLAG_HIDE_LUGIA
	end

WhirlIslands_LugiaChamber_MapScript_LugiaPostStoryEncounter::
	setflag JOHTO_FLAG_HIDE_WHIRL_ISLANDS_KIMONO_GIRLS
	clearflag JOHTO_FLAG_HIDE_LUGIA
	setobjectxyperm LOCALID_LUGIA, 29, 12
	end

WhirlIslands_LugiaChamber_EventScript_TalkToKimono::
	callnative Special_RainbowStoryAdoptWhirl
	goto_if_eq JOHTO_VAR_RESULT, FALSE, BlackTide_End
	goto_if_set FLAG_LG_LEGACY_EXEMPT, BlackTide_NativeRitual
	goto_if_set FLAG_LG_FINAL_RESOLVED, BlackTide_NativeRitual
	callnative Special_RainbowStoryAllReplicasResolved
	goto_if_eq JOHTO_VAR_RESULT, FALSE, BlackTide_KimonoWait

BlackTide_NativeRitual:
	lockall
	call BlackTide_LinksIfReady
	playbgm ((558 + 1) + 0x84), FALSE
	call BlackTide_KimonoOpening
	closemessage

	applymovement LOCALID_KIMONO_MID, WhirlIslands_LugiaChamber_Movement_Kimono_Step_Aside
	waitmovement 0
	applymovement LOCALID_PLAYER, WhirlIslands_LugiaChamber_Walk_To_Center
	waitmovement 0
	applymovement LOCALID_KIMONO_MID, WhirlIslands_LugiaChamber_Movement_Kimono_Step_In
	applymovement LOCALID_KIMONO_1, WhirlIslands_LugiaChamber_Movement_Kimono_Step_Start_Left
	applymovement LOCALID_KIMONO_4, WhirlIslands_LugiaChamber_Movement_Kimono_Step_Start_Right
	waitmovement 5
	playse SE_M_PETAL_DANCE
	applymovement LOCALID_KIMONO_MID, WhirlIslands_LugiaChamber_Movement_Kimono_Dance_Mid
	waitmovement 0
	playse SE_M_PETAL_DANCE
	applymovement LOCALID_KIMONO_1, WhirlIslands_LugiaChamber_Movement_Kimono_Dance_Mid
	applymovement LOCALID_KIMONO_2, WhirlIslands_LugiaChamber_Movement_Kimono_Dance_Mid
	applymovement LOCALID_KIMONO_3, WhirlIslands_LugiaChamber_Movement_Kimono_Dance_Mid
	applymovement LOCALID_KIMONO_4, WhirlIslands_LugiaChamber_Movement_Kimono_Dance_Mid
	applymovement LOCALID_KIMONO_MID, WhirlIslands_LugiaChamber_Movement_Kimono_Dance_Mid
	waitmovement 0
	playse SE_M_PETAL_DANCE
	setweather 6
	doweather

	applymovement LOCALID_KIMONO_1, WhirlIslands_LugiaChamber_Movement_Kimono_Dance_Shift_Down
	applymovement LOCALID_KIMONO_2, WhirlIslands_LugiaChamber_Movement_Kimono_Dance_Shift_Right
	applymovement LOCALID_KIMONO_3, WhirlIslands_LugiaChamber_Movement_Kimono_Dance_Shift_Up
	applymovement LOCALID_KIMONO_4, WhirlIslands_LugiaChamber_Movement_Kimono_Dance_Shift_Left
	waitmovement 5
	delay 30
	applymovement LOCALID_KIMONO_1, WhirlIslands_LugiaChamber_Movement_Kimono_Dance_Mid
	applymovement LOCALID_KIMONO_2, WhirlIslands_LugiaChamber_Movement_Kimono_Dance_Mid
	applymovement LOCALID_KIMONO_3, WhirlIslands_LugiaChamber_Movement_Kimono_Dance_Mid
	applymovement LOCALID_KIMONO_4, WhirlIslands_LugiaChamber_Movement_Kimono_Dance_Mid
	applymovement LOCALID_KIMONO_MID, WhirlIslands_LugiaChamber_Movement_Kimono_Dance_Mid
	waitmovement 0
	playse SE_M_PETAL_DANCE

	applymovement LOCALID_KIMONO_1, WhirlIslands_LugiaChamber_Movement_Kimono_Dance_Shift_Down
	applymovement LOCALID_KIMONO_2, WhirlIslands_LugiaChamber_Movement_Kimono_Dance_Shift_Far_Right
	applymovement LOCALID_KIMONO_3, WhirlIslands_LugiaChamber_Movement_Kimono_Dance_Shift_Up
	applymovement LOCALID_KIMONO_4, WhirlIslands_LugiaChamber_Movement_Kimono_Dance_Shift_Far_Left
	waitmovement 5
	delay 30
	applymovement LOCALID_KIMONO_1, WhirlIslands_LugiaChamber_Movement_Kimono_Dance_Mid
	applymovement LOCALID_KIMONO_2, WhirlIslands_LugiaChamber_Movement_Kimono_Dance_Mid
	applymovement LOCALID_KIMONO_3, WhirlIslands_LugiaChamber_Movement_Kimono_Dance_Mid
	applymovement LOCALID_KIMONO_4, WhirlIslands_LugiaChamber_Movement_Kimono_Dance_Mid
	applymovement LOCALID_KIMONO_MID, WhirlIslands_LugiaChamber_Movement_Kimono_Dance_Mid
	waitmovement 0
	playse SE_M_PETAL_DANCE

	applymovement LOCALID_KIMONO_1, WhirlIslands_LugiaChamber_Movement_Kimono_Dance_Shift_Right
	applymovement LOCALID_KIMONO_2, WhirlIslands_LugiaChamber_Movement_Kimono_Dance_Shift_Up
	applymovement LOCALID_KIMONO_3, WhirlIslands_LugiaChamber_Movement_Kimono_Dance_Shift_Left
	applymovement LOCALID_KIMONO_4, WhirlIslands_LugiaChamber_Movement_Kimono_Dance_Shift_Down
	waitmovement 6
	delay 30
	applymovement LOCALID_KIMONO_1, WhirlIslands_LugiaChamber_Movement_Kimono_Dance_Mid
	applymovement LOCALID_KIMONO_2, WhirlIslands_LugiaChamber_Movement_Kimono_Dance_Mid
	applymovement LOCALID_KIMONO_3, WhirlIslands_LugiaChamber_Movement_Kimono_Dance_Mid
	applymovement LOCALID_KIMONO_4, WhirlIslands_LugiaChamber_Movement_Kimono_Dance_Mid
	applymovement LOCALID_KIMONO_MID, WhirlIslands_LugiaChamber_Movement_Kimono_Dance_Mid
	waitmovement 0
	playse SE_M_PETAL_DANCE

	applymovement LOCALID_KIMONO_1, WhirlIslands_LugiaChamber_Movement_Kimono_Dance_Shift_Far_Right
	applymovement LOCALID_KIMONO_2, WhirlIslands_LugiaChamber_Movement_Kimono_Dance_Shift_Up
	applymovement LOCALID_KIMONO_3, WhirlIslands_LugiaChamber_Movement_Kimono_Dance_Shift_Far_Left
	applymovement LOCALID_KIMONO_4, WhirlIslands_LugiaChamber_Movement_Kimono_Dance_Shift_Down
	waitmovement 6
	delay 30
	applymovement LOCALID_KIMONO_1, WhirlIslands_LugiaChamber_Movement_Kimono_Dance_Mid
	applymovement LOCALID_KIMONO_2, WhirlIslands_LugiaChamber_Movement_Kimono_Dance_Mid
	applymovement LOCALID_KIMONO_3, WhirlIslands_LugiaChamber_Movement_Kimono_Dance_Mid
	applymovement LOCALID_KIMONO_4, WhirlIslands_LugiaChamber_Movement_Kimono_Dance_Mid
	applymovement LOCALID_KIMONO_MID, WhirlIslands_LugiaChamber_Movement_Kimono_Dance_Mid
	waitmovement 0
	playse SE_M_PETAL_DANCE

	applymovement LOCALID_KIMONO_1, WhirlIslands_LugiaChamber_Movement_Kimono_Dance_Shift_Left_Up
	applymovement LOCALID_KIMONO_4, WhirlIslands_LugiaChamber_Movement_Kimono_Dance_Shift_Right_Up
	applymovement LOCALID_KIMONO_MID, WhirlIslands_LugiaChamber_Movement_Kimono_Dance_Step_Up
	waitmovement 3
	delay 30
	applymovement LOCALID_KIMONO_1, WhirlIslands_LugiaChamber_Movement_Kimono_Dance_Mid
	applymovement LOCALID_KIMONO_2, WhirlIslands_LugiaChamber_Movement_Kimono_Dance_Mid
	applymovement LOCALID_KIMONO_3, WhirlIslands_LugiaChamber_Movement_Kimono_Dance_Mid
	applymovement LOCALID_KIMONO_4, WhirlIslands_LugiaChamber_Movement_Kimono_Dance_Mid
	applymovement LOCALID_KIMONO_MID, WhirlIslands_LugiaChamber_Movement_Kimono_Dance_Mid
	waitmovement 0
	playse SE_M_PETAL_DANCE
	waitse
	setobjectxyperm LOCALID_KIMONO_1, 27, 18
	setobjectxyperm LOCALID_KIMONO_2, 28, 19
	setobjectxyperm LOCALID_KIMONO_MID, 29, 20
	setobjectxyperm LOCALID_KIMONO_4, 30, 19
	setobjectxyperm LOCALID_KIMONO_3, 31, 18
	setobjectmovementtype LOCALID_KIMONO_1, 0x7
	setobjectmovementtype LOCALID_KIMONO_2, 0x7
	setobjectmovementtype LOCALID_KIMONO_3, 0x7
	setobjectmovementtype LOCALID_KIMONO_4, 0x7
	setobjectmovementtype LOCALID_KIMONO_MID, 0x7
	setvar 16385, 1
	special SpawnCameraObject
	setvar 32772, 3
	setvar 32773, 35
	special LoopWingFlapSE
	applymovement LOCALID_LUGIA, WhirlIslands_LugiaChamber_Movement_LugiaAppear
	applymovement LOCALID_CAMERA, WhirlIslands_LugiaChamber_Movement_CameraPanUp
	waitmovement 0
	delay 50


	waitse
	playmoncry SPECIES_LUGIA, 2
	delay 30
	waitmoncry
	delay 60
	setvar 32772, 3
	setvar 32773, 35
	special LoopWingFlapSE
	applymovement LOCALID_LUGIA, WhirlIslands_LugiaChamber_Movement_LugiaApproach
	waitmovement 0
	applymovement LOCALID_CAMERA, WhirlIslands_LugiaChamber_Movement_CameraPanDown
	waitmovement 0
	special RemoveCameraObject
	applymovement LOCALID_KIMONO_MID, WhirlIslands_LugiaChamber_Movement_Kimono_Dance_Look_Up
	applymovement LOCALID_KIMONO_1, WhirlIslands_LugiaChamber_Movement_Kimono_Dance_Look_Up
	applymovement LOCALID_KIMONO_2, WhirlIslands_LugiaChamber_Movement_Kimono_Dance_Look_Up
	applymovement LOCALID_KIMONO_3, WhirlIslands_LugiaChamber_Movement_Kimono_Dance_Look_Up
	applymovement LOCALID_KIMONO_4, WhirlIslands_LugiaChamber_Movement_Kimono_Dance_Look_Up
	waitmovement 0
	call BlackTide_ApplyLugiaColor
	call BlackTide_KimonoClosing
	waitmessage
	setobjectxyperm LOCALID_LUGIA, 29, 12


	closemessage
	releaseall
	end

WhirlIslands_LugiaChamber_EventScript_Lugia::
	lockall
	callnative Special_RainbowStoryAdoptWhirl
	goto_if_eq JOHTO_VAR_RESULT, FALSE, BlackTide_Release
	goto_if_set FLAG_LG_LEGACY_EXEMPT, BlackTide_LugiaNative
	goto_if_set FLAG_LG_FINAL_RESOLVED, BlackTide_LugiaNative
	goto_if_unset FLAG_LG_ATTACK_SEEN, BlackTide_LugiaLocked
	callnative Special_RainbowStoryAllReplicasResolved
	goto_if_eq VAR_RESULT, FALSE, BlackTide_LugiaLocked
	call BlackTide_LinksIfReady
	msgbox BlackTide_Text_FaceLugia, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, BlackTide_Release
	closemessage
	setvar 32772, 4
	callnative RainbowVisuals_BeginEncounter

BlackTide_LugiaNative:
	waitse
	playmoncry SPECIES_LUGIA, 2
	delay 30
	waitmoncry
	playbgm ((558 + 1) + 0x67), MUS_DUMMY
	goto_if_eq JOHTO_VAR_COMPLETED_LUGIA, 4, BlackTide_LugiaPostgame
	seteventmon SPECIES_LUGIA, 50
	goto BlackTide_LugiaBattle

BlackTide_LugiaPostgame:
	seteventmon SPECIES_LUGIA, 70

BlackTide_LugiaBattle:
	call BlackTide_StartBattle
	setvar JOHTO_VAR_LAST_TALKED, 1
	specialvar JOHTO_VAR_RESULT, GetBattleOutcome
	goto_if_eq JOHTO_VAR_RESULT, 1, BlackTide_LugiaWon
	goto_if_eq JOHTO_VAR_RESULT, 7, BlackTide_LugiaCaught
	goto BlackTide_Release

BlackTide_LugiaWon:
	call BlackTide_RestoreLugiaVisual
	call WhirlIslands_LugiaChamber_EventScript_LugiaFlewAway
	goto_if_set FLAG_LG_LEGACY_EXEMPT, BlackTide_LugiaNativeCompletion
	goto_if_set FLAG_LG_FINAL_RESOLVED, BlackTide_LugiaNativeCompletion
	setflag FLAG_LG_FINAL_RESOLVED
	msgbox BlackTide_Text_RestoredWon, MSGBOX_DEFAULT
	goto BlackTide_LugiaNativeCompletion

BlackTide_LugiaCaught:
	call BlackTide_RestoreLugiaVisual
	call WhirlIslands_LugiaChamber_EventScript_CaughtLugia
	goto_if_set FLAG_LG_LEGACY_EXEMPT, BlackTide_LugiaNativeCompletion
	goto_if_set FLAG_LG_FINAL_RESOLVED, BlackTide_LugiaNativeCompletion
	setflag FLAG_LG_FINAL_RESOLVED
	msgbox BlackTide_Text_RestoredCaught, MSGBOX_DEFAULT

BlackTide_LugiaNativeCompletion:
	goto_if_eq JOHTO_VAR_COMPLETED_LUGIA, 4, BlackTide_LugiaPostgameCompletion
	setflag JOHTO_FLAG_HIDE_WHIRL_ISLANDS_KIMONO_GIRLS
	applymovement LOCALID_KIMONO_MID, WhirlIslands_LugiaChamber_Movement_Kimono_Dance_Shift_Right2
	waitmovement 0
	clearflag JOHTO_FLAG_HIDE_ECRUTEAK_CITY_THEATER_KIMONOS
	clearflag JOHTO_FLAG_HIDE_ECRUTEAK_CITY_THEATER_ZUKI
	clearflag JOHTO_FLAG_HIDE_ECRUTEAK_CITY_THEATER_NPCS
	setvar JOHTO_VAR_ECRUTEAK_CITY_THEATER, 8

BlackTide_LugiaPostgameCompletion:
	setvar JOHTO_VAR_COMPLETED_LUGIA, 3
	goto BlackTide_Release

WhirlIslands_LugiaChamber_EventScript_LugiaFlewAway::
	fadescreenswapbuffers FADE_TO_BLACK
	removeobject LOCALID_LUGIA
	setweather WEATHER_NONE
	doweather
	setflag JOHTO_FLAG_HIDE_LUGIA
	fadescreenswapbuffers FADE_FROM_BLACK
	bufferspeciesname STR_VAR_1, SPECIES_LUGIA
	msgbox J_gText_LegendaryFlewAway, MSGBOX_DEFAULT
	return

WhirlIslands_LugiaChamber_EventScript_CaughtLugia::
	setflag JOHTO_FLAG_CAUGHT_LUGIA
	fadescreenswapbuffers FADE_TO_BLACK
	removeobject LOCALID_LUGIA
	setweather WEATHER_NONE
	doweather
	setflag JOHTO_FLAG_HIDE_LUGIA
	fadescreenswapbuffers FADE_FROM_BLACK
	return

WhirlIslands_LugiaChamber_EventScript_RanFromLugia::
	releaseall
	end

WhirlIslands_LugiaChamber_EventScript_Zuki::
	goto_if_set FLAG_LG_FINAL_RESOLVED, BlackTide_CoastRestored
	goto_if_eq JOHTO_VAR_COMPLETED_LUGIA, 3, WhirlIslands_LugiaChamber_EventScript_ZukiAfter
	msgbox WhirlIslands_LugiaChamber_Text_Zuki_Before, MSGBOX_NPC
	end

WhirlIslands_LugiaChamber_EventScript_ZukiAfter::
	goto_if_unset JOHTO_FLAG_CAUGHT_LUGIA, WhirlIslands_LugiaChamber_EventScript_ZukiAfterNotCaught
	msgbox WhirlIslands_LugiaChamber_Text_Kimono_AfterCaught, MSGBOX_NPC
	end

WhirlIslands_LugiaChamber_EventScript_ZukiAfterNotCaught::
	msgbox WhirlIslands_LugiaChamber_Text_Kimono_AfterNotCaught, MSGBOX_NPC
	end

WhirlIslands_LugiaChamber_EventScript_Naoko::
	goto_if_set FLAG_LG_FINAL_RESOLVED, BlackTide_CoastRestored
	goto_if_eq JOHTO_VAR_COMPLETED_LUGIA, 3, WhirlIslands_LugiaChamber_EventScript_NaokoAfter
	msgbox WhirlIslands_LugiaChamber_Text_Naoko_Before, MSGBOX_NPC
	end

WhirlIslands_LugiaChamber_EventScript_NaokoAfter::
	msgbox WhirlIslands_LugiaChamber_Text_Kimono_After, MSGBOX_NPC
	end

WhirlIslands_LugiaChamber_EventScript_Miki::
	goto_if_set FLAG_LG_FINAL_RESOLVED, BlackTide_CoastRestored
	goto_if_eq JOHTO_VAR_COMPLETED_LUGIA, 3, WhirlIslands_LugiaChamber_EventScript_MikiAfter
	msgbox WhirlIslands_LugiaChamber_Text_Miki_Before, MSGBOX_NPC
	end

WhirlIslands_LugiaChamber_EventScript_MikiAfter::
	msgbox WhirlIslands_LugiaChamber_Text_Kimono_After, MSGBOX_NPC
	end

WhirlIslands_LugiaChamber_EventScript_Sayo::
	goto_if_set FLAG_LG_FINAL_RESOLVED, BlackTide_CoastRestored
	goto_if_eq JOHTO_VAR_COMPLETED_LUGIA, 3, WhirlIslands_LugiaChamber_EventScript_SayoAfter
	msgbox WhirlIslands_LugiaChamber_Text_Sayo_Before, MSGBOX_NPC
	end

WhirlIslands_LugiaChamber_EventScript_SayoAfter::
	msgbox WhirlIslands_LugiaChamber_Text_Kimono_After, MSGBOX_NPC
	end

WhirlIslands_LugiaChamber_EventScript_Kuni::
	goto_if_set FLAG_LG_FINAL_RESOLVED, BlackTide_CoastRestored
	goto_if_eq JOHTO_VAR_COMPLETED_LUGIA, 3, WhirlIslands_LugiaChamber_EventScript_KuniAfter
	msgbox WhirlIslands_LugiaChamber_Text_Kuni_Before, MSGBOX_NPC
	end

WhirlIslands_LugiaChamber_EventScript_KuniAfter::
	msgbox WhirlIslands_LugiaChamber_Text_Kimono_After, MSGBOX_NPC
	end

WhirlIslands_LugiaChamber_Text_Kimono_AfterNotCaught:
	.string "You have not only made LUGIA\n"
	.string "appear, but you have also defeated\l"
	.string "it...\p"
	.string "There is nothing more for us to\n"
	.string "say. Take care of yourself in your\l"
	.string "journey...$"

WhirlIslands_LugiaChamber_Text_Kimono_AfterCaught:
	.string "You have not only made LUGIA\n"
	.string "appear, but you have also caught\l"
	.string "it...\p"
	.string "There is nothing more for us to\n"
	.string "say. Take care of yourself in your\l"
	.string "journey...$"

WhirlIslands_LugiaChamber_Movement_CameraPanUp:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

WhirlIslands_LugiaChamber_Movement_CameraPanDown:
	delay_16
	delay_16
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

WhirlIslands_LugiaChamber_Movement_LugiaApproach:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_in_place_down
	delay_16
	delay_16
	step_end

WhirlIslands_LugiaChamber_Movement_LugiaAppear:
	delay_16
	delay_16
	walk_in_place_down
	walk_in_place_down
	walk_in_place_down
	walk_in_place_down
	step_end

WhirlIslands_LugiaChamber_Movement_Kimono_Step_Aside:
	face_right
	delay_16
	walk_right
	delay_16
	face_left
	step_end

WhirlIslands_LugiaChamber_Walk_To_Center:
	walk_up
	walk_up
	walk_up
	delay_16
	face_down
	step_end

WhirlIslands_LugiaChamber_Movement_Kimono_Step_In:
	walk_left
	delay_16
	face_down
	step_end

WhirlIslands_LugiaChamber_Movement_Kimono_Step_Start_Left:
	face_right
	delay_16
	face_up
	delay_16
	walk_up
	walk_up
	delay_16
	face_left
	delay_16
	walk_left
	delay_16
	face_down
	step_end

WhirlIslands_LugiaChamber_Movement_Kimono_Step_Start_Right:
	face_right
	delay_16
	face_up
	delay_16
	walk_up
	walk_up
	delay_16
	face_right
	delay_16
	walk_right
	delay_16
	face_down
	step_end

WhirlIslands_LugiaChamber_Movement_Kimono_Dance_Mid:
	face_down
	delay_8
	face_right
	delay_8
	face_up
	delay_8
	face_left
	delay_8
	face_down
	delay_8
	delay_8
	delay_8
	delay_8
	delay_8
	delay_16
	face_down
	delay_8
	face_right
	delay_8
	face_up
	delay_8
	face_left
	delay_8
	face_down
	delay_16
	step_end

WhirlIslands_LugiaChamber_Movement_Kimono_Dance_Shift_Down:
	face_down
	delay_8
	walk_down
	delay_8
	face_down
	delay_16
	step_end

WhirlIslands_LugiaChamber_Movement_Kimono_Dance_Shift_Right:
	face_right
	delay_8
	walk_right
	delay_8
	face_down
	delay_16
	step_end

WhirlIslands_LugiaChamber_Movement_Kimono_Dance_Shift_Up:
	face_right
	delay_8
	face_up
	delay_8
	walk_up
	delay_8
	face_down
	delay_16
	step_end

WhirlIslands_LugiaChamber_Movement_Kimono_Dance_Shift_Left:
	face_right
	delay_8
	face_up
	delay_8
	face_left
	delay_8
	walk_left
	delay_8
	face_down
	delay_16
	step_end

WhirlIslands_LugiaChamber_Movement_Kimono_Dance_Shift_Far_Right:
	face_right
	delay_8
	walk_right
	walk_right
	walk_right
	face_down
	delay_16
	step_end

WhirlIslands_LugiaChamber_Movement_Kimono_Dance_Shift_Far_Left:
	face_right
	delay_8
	face_up
	delay_8
	face_left
	delay_8
	walk_left
	walk_left
	walk_left
	face_down
	delay_16
	step_end

WhirlIslands_LugiaChamber_Movement_Kimono_Dance_Shift_Left_Up:
	face_right
	delay_8
	face_up
	delay_8
	face_left
	delay_8
	walk_left
	delay_8
	face_up
	delay_8
	walk_up
	delay_8
	face_left
	delay_8
	face_down
	delay_16
	step_end

WhirlIslands_LugiaChamber_Movement_Kimono_Dance_Shift_Right_Up:
	face_right
	delay_8
	walk_right
	delay_8
	face_up
	delay_8
	walk_up
	delay_8
	face_right
	delay_8
	face_down
	delay_16
	step_end

WhirlIslands_LugiaChamber_Movement_Kimono_Dance_Look_Up:
	face_right
	delay_8
	face_up
	delay_16
	step_end

WhirlIslands_LugiaChamber_Movement_Kimono_Dance_Step_Up:
	face_right
	delay_8
	face_up
	delay_8
	walk_up
	delay_8
	face_left
	delay_8
	face_down
	delay_16
	step_end

WhirlIslands_LugiaChamber_Movement_Kimono_Dance_Shift_Right2:
	face_right
	delay_8
	walk_right
	delay_8
	face_down
	delay_16
	face_left
	step_end

WhirlIslands_LugiaChamber_Text_Zuki_Before::
	.string "ZUKI: Go, face LUGIA. $"

WhirlIslands_LugiaChamber_Text_Naoko_Before::
	.string "NAOKO: Go, face LUGIA. $"

WhirlIslands_LugiaChamber_Text_Miki_Before::
	.string "MIKI: Go, face LUGIA. $"

WhirlIslands_LugiaChamber_Text_Sayo_Before::
	.string "SAYO: Go, face LUGIA. $"

WhirlIslands_LugiaChamber_Text_Kuni_Before::
	.string "KUNI: Go, face LUGIA. $"

WhirlIslands_LugiaChamber_Text_Kimono_Opening::
	.string "KIMONO GIRL: That's right.\n"
	.string "This is where we welcome LUGIA.\p"
	.string "When the dance we practiced many\n"
	.string "days becomes one with the sound of the\l"
	.string "Tidal Bell we entrusted to you, then\l"
	.string "LUGIA shall come out from deep within\l"
	.string "the waterfall basin once again. $"

WhirlIslands_LugiaChamber_Text_Kimono_Closing1::
	.string "That is indeed LUGIA...\n"
	.string "The guardian of these islands from\l"
	.string "ancient times... \p"
	.string "So many have tried again and again,\n"
	.string "only to fail...\p"
	.string "{PLAYER}, your heart in complete\n"
	.string "harmony with the Tidal Bell has finally\l"
	.string "allowed it to appear...\l"
	.string "{PLAYER}, don't you see?\p"
	.string "LUGIA... It must have been waiting for\n"
	.string "someone like you all this time.\p"
	.string "Wouldn't you agree? $"

WhirlIslands_LugiaChamber_Text_Kimono_After::
	.string "KIMONO GIRL: You've proven yourself\n"
	.string "today, {PLAYER}.$"

BlackTide_OnFrame:
	map_script_2 JOHTO_VAR_TEMP_2, 1, BlackTide_FirstSafeFrame
	.2byte 0

BlackTide_FirstSafeFrame:
	setvar JOHTO_VAR_TEMP_2, 0
	callnative Special_RainbowStoryAdoptWhirl
	goto_if_eq JOHTO_VAR_RESULT, FALSE, BlackTide_End
	goto_if_set FLAG_LG_LEGACY_EXEMPT, BlackTide_End
	goto_if_set FLAG_LG_FINAL_RESOLVED, BlackTide_End
	goto_if_eq JOHTO_VAR_COMPLETED_LUGIA, 2, BlackTide_FirstSafeEligible
	goto_if_ne JOHTO_VAR_COMPLETED_LUGIA, 4, BlackTide_End

BlackTide_FirstSafeEligible:
	goto_if_unset FLAG_LG_ATTACK_SEEN, BlackTide_Attack
	call BlackTide_ApplyBirdColors
	callnative Special_RainbowStoryAllReplicasResolved
	goto_if_eq JOHTO_VAR_RESULT, FALSE, BlackTide_End
	setvar 32772, 4
	setvar 32773, 1
	callnative RainbowVisuals_ApplyCorruption
	end

BlackTide_UpdateVisibility:
	setflag JOHTO_FLAG_TEMP_17
	setflag JOHTO_FLAG_TEMP_18
	setflag JOHTO_FLAG_TEMP_19
	setflag JOHTO_FLAG_TEMP_1A
	setflag JOHTO_FLAG_TEMP_1B
	setflag JOHTO_FLAG_TEMP_1C
	callnative Special_RainbowStoryAdoptWhirl
	goto_if_eq JOHTO_VAR_RESULT, FALSE, BlackTide_Return
	goto_if_set FLAG_LG_LEGACY_EXEMPT, BlackTide_Return
	goto_if_set FLAG_LG_FINAL_RESOLVED, BlackTide_ShowKeeper
	goto_if_unset FLAG_LG_ATTACK_SEEN, BlackTide_Return
	goto_if_eq JOHTO_VAR_COMPLETED_LUGIA, 2, BlackTide_ShowUnresolved
	goto_if_ne JOHTO_VAR_COMPLETED_LUGIA, 4, BlackTide_Return

BlackTide_ShowUnresolved:
	clearflag JOHTO_FLAG_TEMP_1C
	setvar 32772, 0
	callnative Special_RainbowStoryGetReplicaResult
	call_if_eq JOHTO_VAR_RESULT, 0, BlackTide_ShowArticuno
	setvar 32772, 1
	callnative Special_RainbowStoryGetReplicaResult
	call_if_eq JOHTO_VAR_RESULT, 0, BlackTide_ShowZapdos
	setvar 32772, 2
	callnative Special_RainbowStoryGetReplicaResult
	call_if_eq JOHTO_VAR_RESULT, 0, BlackTide_ShowMoltres
	return

BlackTide_ShowKeeper:
	clearflag JOHTO_FLAG_TEMP_1C
	return

BlackTide_ShowArticuno:
	clearflag JOHTO_FLAG_TEMP_17
	return

BlackTide_ShowZapdos:
	clearflag JOHTO_FLAG_TEMP_18
	return

BlackTide_ShowMoltres:
	clearflag JOHTO_FLAG_TEMP_19
	return

BlackTide_HideNativeLugia:
	setflag JOHTO_FLAG_HIDE_LUGIA
	end

BlackTide_Attack:
	lockall
	fadescreenswapbuffers 1
	clearflag JOHTO_FLAG_TEMP_17
	clearflag JOHTO_FLAG_TEMP_18
	clearflag JOHTO_FLAG_TEMP_19
	clearflag JOHTO_FLAG_TEMP_1A
	clearflag JOHTO_FLAG_TEMP_1B
	addobject 9
	addobject 10
	addobject 11
	addobject 12
	addobject 13
	setobjectxy 9, 27, 33
	setobjectxy 10, 31, 33
	setobjectxy 11, 29, 32
	setobjectxy 13, 29, 33
	call BlackTide_ApplyBirdColors
	fadescreenswapbuffers 0
	msgbox BlackTide_Text_Attack, MSGBOX_DEFAULT
	applymovement 9, BlackTide_Movement_IceStrike
	waitmovement 9
	playse SE_THUNDERSTORM_STOP
	applymovement 13, BlackTide_Movement_Recoil
	waitmovement 13
	applymovement 10, BlackTide_Movement_LightningStrike
	waitmovement 10
	playse SE_THUNDERSTORM_STOP
	applymovement 13, BlackTide_Movement_Recoil
	waitmovement 13
	applymovement 11, BlackTide_Movement_FireStrike
	waitmovement 11
	msgbox BlackTide_Text_Technician, MSGBOX_DEFAULT
	setvar 32772, 4
	setvar 32773, 13
	callnative RainbowVisuals_ApplyCorruption
	playmoncry SPECIES_LUGIA, 2
	waitmoncry
	msgbox BlackTide_Text_Transformation, MSGBOX_DEFAULT
	fadescreenswapbuffers 1
	removeobject 12
	removeobject 13
	setflag JOHTO_FLAG_TEMP_1A
	setflag JOHTO_FLAG_TEMP_1B
	setobjectxy 9, 25, 34
	setobjectxy 10, 33, 34
	setobjectxy 11, 29, 27
	setflag FLAG_LG_ATTACK_SEEN
	clearflag JOHTO_FLAG_TEMP_1C
	addobject 14
	fadescreenswapbuffers 0
	msgbox BlackTide_Text_ThreeLinks, MSGBOX_DEFAULT
	goto BlackTide_Release

BlackTide_ApplyBirdColors:
	setvar 32772, 1
	setvar 32773, 9
	callnative RainbowVisuals_ApplyCorruption
	setvar 32772, 2
	setvar 32773, 10
	callnative RainbowVisuals_ApplyCorruption
	setvar 32772, 3
	setvar 32773, 11
	callnative RainbowVisuals_ApplyCorruption
	return

BlackTide_Articuno::
	lockall
	call BlackTide_CheckReplicaEligible
	goto_if_eq JOHTO_VAR_RESULT, FALSE, BlackTide_Release
	setvar 32772, 0
	callnative Special_RainbowStoryGetReplicaResult
	goto_if_ne JOHTO_VAR_RESULT, 0, BlackTide_Release
	msgbox BlackTide_Text_Articuno, MSGBOX_DEFAULT
	goto_if_eq JOHTO_VAR_COMPLETED_LUGIA, 4, BlackTide_Articuno70
	seteventmon SPECIES_ARTICUNO, 50
	goto BlackTide_ArticunoBattle

BlackTide_Articuno70:
	seteventmon SPECIES_ARTICUNO, 70

BlackTide_ArticunoBattle:
	setvar 32772, 1
	callnative RainbowVisuals_BeginEncounter
	call BlackTide_StartBattle
	setvar 32772, 0
	callnative Special_RainbowStoryRecordReplicaResult
	goto_if_eq JOHTO_VAR_RESULT, FALSE, BlackTide_Release
	setvar 32772, 0
	setvar 32773, 9
	callnative RainbowVisuals_ApplyCorruption
	delay 20
	setflag JOHTO_FLAG_TEMP_17
	removeobject 9
	goto BlackTide_ReplicaResolved

BlackTide_Zapdos::
	lockall
	call BlackTide_CheckReplicaEligible
	goto_if_eq JOHTO_VAR_RESULT, FALSE, BlackTide_Release
	setvar 32772, 1
	callnative Special_RainbowStoryGetReplicaResult
	goto_if_ne JOHTO_VAR_RESULT, 0, BlackTide_Release
	msgbox BlackTide_Text_Zapdos, MSGBOX_DEFAULT
	goto_if_eq JOHTO_VAR_COMPLETED_LUGIA, 4, BlackTide_Zapdos70
	seteventmon SPECIES_ZAPDOS, 50
	goto BlackTide_ZapdosBattle

BlackTide_Zapdos70:
	seteventmon SPECIES_ZAPDOS, 70

BlackTide_ZapdosBattle:
	setvar 32772, 2
	callnative RainbowVisuals_BeginEncounter
	call BlackTide_StartBattle
	setvar 32772, 1
	callnative Special_RainbowStoryRecordReplicaResult
	goto_if_eq JOHTO_VAR_RESULT, FALSE, BlackTide_Release
	setvar 32772, 0
	setvar 32773, 10
	callnative RainbowVisuals_ApplyCorruption
	delay 20
	setflag JOHTO_FLAG_TEMP_18
	removeobject 10
	goto BlackTide_ReplicaResolved

BlackTide_Moltres::
	lockall
	call BlackTide_CheckReplicaEligible
	goto_if_eq JOHTO_VAR_RESULT, FALSE, BlackTide_Release
	setvar 32772, 2
	callnative Special_RainbowStoryGetReplicaResult
	goto_if_ne JOHTO_VAR_RESULT, 0, BlackTide_Release
	msgbox BlackTide_Text_Moltres, MSGBOX_DEFAULT
	goto_if_eq JOHTO_VAR_COMPLETED_LUGIA, 4, BlackTide_Moltres70
	seteventmon SPECIES_MOLTRES, 50
	goto BlackTide_MoltresBattle

BlackTide_Moltres70:
	seteventmon SPECIES_MOLTRES, 70

BlackTide_MoltresBattle:
	setvar 32772, 3
	callnative RainbowVisuals_BeginEncounter
	call BlackTide_StartBattle
	setvar 32772, 2
	callnative Special_RainbowStoryRecordReplicaResult
	goto_if_eq JOHTO_VAR_RESULT, FALSE, BlackTide_Release
	setvar 32772, 0
	setvar 32773, 11
	callnative RainbowVisuals_ApplyCorruption
	delay 20
	setflag JOHTO_FLAG_TEMP_19
	removeobject 11

BlackTide_ReplicaResolved:
	specialvar JOHTO_VAR_RESULT, GetBattleOutcome
	goto_if_eq JOHTO_VAR_RESULT, 7, BlackTide_ReplicaCaught
	msgbox BlackTide_Text_ReplicaWon, MSGBOX_DEFAULT
	goto BlackTide_ReplicaAfter

BlackTide_ReplicaCaught:
	msgbox BlackTide_Text_ReplicaCaught, MSGBOX_DEFAULT

BlackTide_ReplicaAfter:
	call BlackTide_LinksIfReady
	goto BlackTide_Release

BlackTide_CheckReplicaEligible:
	callnative Special_RainbowStoryAdoptWhirl
	goto_if_eq JOHTO_VAR_RESULT, FALSE, BlackTide_Return
	goto_if_set FLAG_LG_LEGACY_EXEMPT, BlackTide_Ineligible
	goto_if_set FLAG_LG_FINAL_RESOLVED, BlackTide_Ineligible
	goto_if_unset FLAG_LG_ATTACK_SEEN, BlackTide_Ineligible
	goto_if_eq JOHTO_VAR_COMPLETED_LUGIA, 2, BlackTide_Eligible
	goto_if_ne JOHTO_VAR_COMPLETED_LUGIA, 4, BlackTide_Ineligible

BlackTide_Eligible:
	setvar JOHTO_VAR_RESULT, TRUE
	return

BlackTide_Ineligible:
	setvar JOHTO_VAR_RESULT, FALSE
	return

BlackTide_StartBattle:
	closemessage
	setflag JOHTO_FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	waitstate
	clearflag JOHTO_FLAG_SYS_CTRL_OBJ_DELETE
	callnative RainbowVisuals_EndEncounter


	call BlackTide_ReapplyPresentation
	return

BlackTide_LinksIfReady:
	goto_if_set FLAG_LG_LEGACY_EXEMPT, BlackTide_Return
	goto_if_set FLAG_LG_FINAL_RESOLVED, BlackTide_Return
	goto_if_set FLAG_LG_LINKS_OFF_SEEN, BlackTide_Return
	callnative Special_RainbowStoryAllReplicasResolved
	goto_if_eq JOHTO_VAR_RESULT, FALSE, BlackTide_Return
	msgbox BlackTide_Text_LinksBroken, MSGBOX_DEFAULT
	closemessage
	setflag FLAG_LG_LINKS_OFF_SEEN
	clearflag JOHTO_FLAG_HIDE_LUGIA
	addobject LOCALID_LUGIA
	call_if_eq JOHTO_VAR_COMPLETED_LUGIA, 4, BlackTide_PositionPostgameLugia
	setvar 32772, 4
	setvar 32773, 1
	callnative RainbowVisuals_ApplyCorruption
	return

BlackTide_PositionPostgameLugia:
	setobjectxyperm LOCALID_LUGIA, 29, 12
	setobjectxy LOCALID_LUGIA, 29, 12
	return

BlackTide_KimonoWait:
	lockall
	msgbox BlackTide_Text_KimonoWait, MSGBOX_DEFAULT
	goto BlackTide_Release

BlackTide_LugiaLocked:
	msgbox BlackTide_Text_KimonoWait, MSGBOX_DEFAULT
	goto BlackTide_Release

BlackTide_KimonoOpening:
	goto_if_set FLAG_LG_LEGACY_EXEMPT, BlackTide_OriginalOpening
	goto_if_set FLAG_LG_FINAL_RESOLVED, BlackTide_OriginalOpening
	msgbox BlackTide_Text_KimonoOpening, MSGBOX_DEFAULT
	return

BlackTide_OriginalOpening:
	msgbox WhirlIslands_LugiaChamber_Text_Kimono_Opening, MSGBOX_DEFAULT
	return

BlackTide_RestoreLugiaVisual:
	goto_if_set FLAG_LG_LEGACY_EXEMPT, BlackTide_Return
	goto_if_set FLAG_LG_FINAL_RESOLVED, BlackTide_Return
	setvar 32772, 0
	setvar 32773, 1
	callnative RainbowVisuals_ApplyCorruption
	delay 30
	return

BlackTide_ApplyLugiaColor:
	goto_if_set FLAG_LG_LEGACY_EXEMPT, BlackTide_Return
	goto_if_set FLAG_LG_FINAL_RESOLVED, BlackTide_Return
	setvar 32772, 4
	setvar 32773, 1
	callnative RainbowVisuals_ApplyCorruption
	return

BlackTide_KimonoClosing:
	goto_if_set FLAG_LG_LEGACY_EXEMPT, BlackTide_OriginalClosing
	goto_if_set FLAG_LG_FINAL_RESOLVED, BlackTide_OriginalClosing
	msgbox BlackTide_Text_KimonoClosing, MSGBOX_DEFAULT
	return

BlackTide_OriginalClosing:
	msgbox WhirlIslands_LugiaChamber_Text_Kimono_Closing1, MSGBOX_DEFAULT
	return

BlackTide_CoastRestored:
	msgbox BlackTide_Text_CoastRestored, MSGBOX_NPC
	end

BlackTide_Release:
	closemessage
	releaseall

BlackTide_End::
	end

BlackTide_Return:
	return

BlackTide_Movement_Recoil:
	jump_in_place_down
	step_end

BlackTide_Movement_IceStrike:
	face_right
	delay_16
	face_down
	step_end

BlackTide_Movement_LightningStrike:
	face_left
	delay_16
	face_down
	step_end

BlackTide_Movement_FireStrike:
	face_down
	delay_16
	step_end

BlackTide_Text_Attack:
	.string "Three cries cut through the cave.\pThe birds strike in a cruel\npattern. LUGIA turns away from\lthe inhabited coast.\pIt shields the frightened POKéMON\nfrom falling stone.$"

BlackTide_Text_Technician:
	.string "ROCKET TECHNICIAN: First, make\nit angry. Then keep it that way.\pThree manufactured specimens.\nThree links. No order to retreat!$"

BlackTide_Text_Transformation:
	.string "The attacks follow one last pulse.\nLUGIA's color darkens!\pIts cry shakes the water.\nThe technician slips away.$"

BlackTide_Text_ThreeLinks:
	.string "The replicas guard three relays.\nStop them in any order.\pDefeat or catch each replica\nto break ROCKET's control links.\pYou can leave to heal or save.\nThere is no countdown.$"

BlackTide_Text_Articuno:
	.string "You guide a frightened POKéMON\nbehind cover.\pThe ice replica follows a light.\nIt attacks before the next pulse!$"

BlackTide_Text_Zapdos:
	.string "Each flash makes the relay answer.\nThe answer triggers another flash.\pThe electric replica turns toward\nyou. You stand your ground.$"

BlackTide_Text_Moltres:
	.string "The fire replica tries to leave.\nIts flames flare. The relay answers.\pIt turns back toward you!$"

BlackTide_Text_ReplicaWon:
	.string "The conditioning breaks.\nThe bird's color returns.\pIt withdraws safely.\nOne control link is silent.$"

BlackTide_Text_ReplicaCaught:
	.string "The conditioning breaks as the\ncaught bird's color returns.\pThe rescued POKéMON is safe.\nOne control link is silent.$"

BlackTide_Text_LinksBroken:
	.string "The last relay goes dark.\nFor a moment, the water is still.\pA deep cry shakes the cavern.\nLUGIA remains in the SHADOW state.\pThe links are gone. Now a rescue\nis possible. You can prepare first.$"

BlackTide_Text_KimonoWait:
	.string "Three replicas keep ROCKET's\ncontrol links alive.\pStop each one, in any order.\nThen we can approach LUGIA.$"

BlackTide_Text_KimonoOpening:
	.string "KIMONO GIRL: The links are gone.\nWe can call to LUGIA now.\pOur dance and your earned TIDAL\nBELL will give it a familiar sound.$"

BlackTide_Text_KimonoClosing:
	.string "We cannot make LUGIA trust us.\pStand your ground. Give it\nsomething besides the attack\lto recognize.\pYou can leave to prepare first.$"

BlackTide_Text_FaceLugia:
	.string "Face SHADOW LUGIA now?\pYES: Face LUGIA.\nNO: Prepare first.$"

BlackTide_Text_RestoredWon:
	.string "The SHADOW coloring fades.\nLUGIA is restored.\pFor the first time since this\nbegan, it chose where to go.$"

BlackTide_Text_RestoredCaught:
	.string "The caught LUGIA is restored.\nIt can hear more than commands now.\pTake care of it.$"

BlackTide_Text_CoastRestored:
	.string "The relays are silent.\nThe islands are recovering.\pThe guardian's choices are its own.$"

WhirlIslands_LugiaChamber_EventScript_LugiaPostgame::
	goto BlackTide_LugiaPostgame

BlackTide_CoastalWarning:
	callnative Special_RainbowStoryAdoptWhirl
	goto_if_eq JOHTO_VAR_RESULT, FALSE, BlackTide_Return
	goto_if_set FLAG_LG_FINAL_RESOLVED, BlackTide_WarningRestored
	goto_if_set FLAG_LG_LEGACY_EXEMPT, BlackTide_WarningRestored
	msgbox BlackTide_Text_CoastalWarning, MSGBOX_DEFAULT
	return

BlackTide_WarningRestored:
	msgbox BlackTide_Text_CoastRestored, MSGBOX_DEFAULT
	return

BlackTide_Text_CoastalWarning:
	.string "Sailors saw three huge birds\ncircling the WHIRL ISLANDS.\pThey took turns striking, as if\nsomeone told them when to attack.\pFollow your earned legendary\njourney. We cannot rush the sea.$"

BlackTide_Keeper::
	lockall
	faceplayer
	goto_if_set FLAG_LG_FINAL_RESOLVED, BlackTide_KeeperRestored
	callnative Special_RainbowStoryAllReplicasResolved
	goto_if_eq JOHTO_VAR_RESULT, FALSE, BlackTide_KeeperWaiting
	call BlackTide_LinksIfReady
	msgbox BlackTide_Text_KeeperReady, MSGBOX_DEFAULT
	goto BlackTide_Release

BlackTide_KeeperWaiting:
	msgbox BlackTide_Text_ThreeLinks, MSGBOX_DEFAULT
	goto BlackTide_Release

BlackTide_KeeperRestored:
	msgbox BlackTide_Text_CoastRestored, MSGBOX_DEFAULT
	goto BlackTide_Release

BlackTide_Text_KeeperReady:
	.string "KEEPER: We can approach now.\nWe cannot make LUGIA trust us.\pStand your ground. Give it\nsomething besides the attack\lto recognize.\pPrepare as long as you need.$"

BlackTide_OnReturnToField:
	call BlackTide_ReapplyPresentation
	end

BlackTide_ReapplyPresentation:
	copyvar JOHTO_VAR_TEMP_3, JOHTO_VAR_RESULT
	copyvar JOHTO_VAR_TEMP_4, 32772
	copyvar JOHTO_VAR_TEMP_5, 32773
	callnative Special_RainbowStoryIsReady
	goto_if_eq JOHTO_VAR_RESULT, FALSE, BlackTide_RestorePresentationScratch
	goto_if_unset FLAG_LG_ATTACK_SEEN, BlackTide_RestorePresentationScratch
	goto_if_set FLAG_LG_FINAL_RESOLVED, BlackTide_RestorePresentationScratch
	goto_if_set FLAG_LG_LEGACY_EXEMPT, BlackTide_RestorePresentationScratch
	goto_if_eq JOHTO_VAR_COMPLETED_LUGIA, 2, BlackTide_RefreshPresentation
	goto_if_ne JOHTO_VAR_COMPLETED_LUGIA, 4, BlackTide_RestorePresentationScratch

BlackTide_RefreshPresentation:
	setvar 32772, 0
	callnative Special_RainbowStoryGetReplicaResult
	call_if_eq JOHTO_VAR_RESULT, 0, BlackTide_ColorUnresolvedArticuno
	setvar 32772, 1
	callnative Special_RainbowStoryGetReplicaResult
	call_if_eq JOHTO_VAR_RESULT, 0, BlackTide_ColorUnresolvedZapdos
	setvar 32772, 2
	callnative Special_RainbowStoryGetReplicaResult
	call_if_eq JOHTO_VAR_RESULT, 0, BlackTide_ColorUnresolvedMoltres
	callnative Special_RainbowStoryAllReplicasResolved
	call_if_eq JOHTO_VAR_RESULT, TRUE, BlackTide_ApplyLugiaColor

BlackTide_RestorePresentationScratch:
	copyvar JOHTO_VAR_RESULT, JOHTO_VAR_TEMP_3
	copyvar 32772, JOHTO_VAR_TEMP_4
	copyvar 32773, JOHTO_VAR_TEMP_5
	setvar JOHTO_VAR_TEMP_3, 0
	setvar JOHTO_VAR_TEMP_4, 0
	setvar JOHTO_VAR_TEMP_5, 0
	return

BlackTide_ColorUnresolvedArticuno:
	setvar 32772, 1
	setvar 32773, 9
	callnative RainbowVisuals_ApplyCorruption
	return

BlackTide_ColorUnresolvedZapdos:
	setvar 32772, 2
	setvar 32773, 10
	callnative RainbowVisuals_ApplyCorruption
	return

BlackTide_ColorUnresolvedMoltres:
	setvar 32772, 3
	setvar 32773, 11
	callnative RainbowVisuals_ApplyCorruption
	return

B4_Johto_EventScript_ReturnToRoute22::
	lockall
	warp MAP_ROUTE22, 0
	waitstate
	releaseall
	end

