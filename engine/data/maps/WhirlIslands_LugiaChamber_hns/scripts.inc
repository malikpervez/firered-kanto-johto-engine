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
	.string "Yo{SE_M_DIVE}hav{SE_M_REVERSAL}no{SE_M_SPIT_UP}onl{SE_M_YAWN}mad{SE_M_REVERSAL}LUGIA\n"
	.string "appear{SE_M_SUPERSONIC}bu{SE_M_SPIT_UP}yo{SE_M_DIVE}hav{SE_M_REVERSAL}als{SE_M_ATTRACT2}defeated\l"
	.string "it...\p"
	.string "Ther{SE_M_REVERSAL}i{SE_M_GRASSWHISTLE}nothin{SE_M_SANDSTORM}mor{SE_M_REVERSAL}fo{SE_M_SAND_TOMB}u{SE_M_GRASSWHISTLE}to\n"
	.string "say{SE_M_PERISH_SONG}Tak{SE_M_REVERSAL}car{SE_M_REVERSAL}o{SE_M_ACID_ARMOR}yoursel{SE_M_ACID_ARMOR}i{SE_M_ATTRACT}your\l"
	.string "journey...$"

WhirlIslands_LugiaChamber_Text_Kimono_AfterCaught:
	.string "Yo{SE_M_DIVE}hav{SE_M_REVERSAL}no{SE_M_SPIT_UP}onl{SE_M_YAWN}mad{SE_M_REVERSAL}LUGIA\n"
	.string "appear{SE_M_SUPERSONIC}bu{SE_M_SPIT_UP}yo{SE_M_DIVE}hav{SE_M_REVERSAL}als{SE_M_ATTRACT2}caught\l"
	.string "it...\p"
	.string "Ther{SE_M_REVERSAL}i{SE_M_GRASSWHISTLE}nothin{SE_M_SANDSTORM}mor{SE_M_REVERSAL}fo{SE_M_SAND_TOMB}u{SE_M_GRASSWHISTLE}to\n"
	.string "say{SE_M_PERISH_SONG}Tak{SE_M_REVERSAL}car{SE_M_REVERSAL}o{SE_M_ACID_ARMOR}yoursel{SE_M_ACID_ARMOR}i{SE_M_ATTRACT}your\l"
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
	.string "ZUKI{SE_M_HEAT_WAVE}Go{SE_M_SUPERSONIC}fac{SE_M_REVERSAL}LUGIA{SE_M_PERISH_SONG}$"

WhirlIslands_LugiaChamber_Text_Naoko_Before::
	.string "NAOKO{SE_M_HEAT_WAVE}Go{SE_M_SUPERSONIC}fac{SE_M_REVERSAL}LUGIA{SE_M_PERISH_SONG}$"

WhirlIslands_LugiaChamber_Text_Miki_Before::
	.string "MIKI{SE_M_HEAT_WAVE}Go{SE_M_SUPERSONIC}fac{SE_M_REVERSAL}LUGIA{SE_M_PERISH_SONG}$"

WhirlIslands_LugiaChamber_Text_Sayo_Before::
	.string "SAYO{SE_M_HEAT_WAVE}Go{SE_M_SUPERSONIC}fac{SE_M_REVERSAL}LUGIA{SE_M_PERISH_SONG}$"

WhirlIslands_LugiaChamber_Text_Kuni_Before::
	.string "KUNI{SE_M_HEAT_WAVE}Go{SE_M_SUPERSONIC}fac{SE_M_REVERSAL}LUGIA{SE_M_PERISH_SONG}$"

WhirlIslands_LugiaChamber_Text_Kimono_Opening::
	.string "KIMON{SE_M_SOLAR_BEAM}GIRL{SE_M_HEAT_WAVE}That'{SE_M_GRASSWHISTLE}right.\n"
	.string "Thi{SE_M_GRASSWHISTLE}i{SE_M_GRASSWHISTLE}wher{SE_M_REVERSAL}w{SE_M_REVERSAL}welcom{SE_M_REVERSAL}LUGIA.\p"
	.string "Whe{SE_M_ATTRACT}th{SE_M_REVERSAL}danc{SE_M_REVERSAL}w{SE_M_REVERSAL}practice{SE_M_WATERFALL}many\n"
	.string "day{SE_M_GRASSWHISTLE}become{SE_M_GRASSWHISTLE}on{SE_M_REVERSAL}wit{SE_M_TRI_ATTACK}th{SE_M_REVERSAL}soun{SE_M_WATERFALL}o{SE_M_ACID_ARMOR}the\l"
	.string "Tida{SE_M_BATON_PASS}Bel{SE_M_BATON_PASS}w{SE_M_REVERSAL}entruste{SE_M_WATERFALL}t{SE_M_ATTRACT2}you{SE_M_SUPERSONIC}then\l"
	.string "LUGI{SE_M_BONEMERANG}shal{SE_M_BATON_PASS}com{SE_M_REVERSAL}ou{SE_M_SPIT_UP}fro{SE_M_MILK_DRINK}dee{SE_M_MORNING_SUN}within\l"
	.string "th{SE_M_REVERSAL}waterfal{SE_M_BATON_PASS}basi{SE_M_ATTRACT}onc{SE_M_REVERSAL}again{SE_M_PERISH_SONG}$"

WhirlIslands_LugiaChamber_Text_Kimono_Closing1::
	.string "Tha{SE_M_SPIT_UP}i{SE_M_GRASSWHISTLE}indee{SE_M_WATERFALL}LUGIA...\n"
	.string "Th{SE_M_REVERSAL}guardia{SE_M_ATTRACT}o{SE_M_ACID_ARMOR}thes{SE_M_REVERSAL}island{SE_M_GRASSWHISTLE}from\l"
	.string "ancien{SE_M_SPIT_UP}times..{SE_M_PERISH_SONG}\p"
	.string "S{SE_M_ATTRACT2}man{SE_M_YAWN}hav{SE_M_REVERSAL}trie{SE_M_WATERFALL}agai{SE_M_ATTRACT}an{SE_M_WATERFALL}again,\n"
	.string "onl{SE_M_YAWN}t{SE_M_ATTRACT2}fail...\p"
	.string "{PLAYER}{SE_M_SUPERSONIC}you{SE_M_SAND_TOMB}hear{SE_M_SPIT_UP}i{SE_M_ATTRACT}complete\n"
	.string "harmon{SE_M_YAWN}wit{SE_M_TRI_ATTACK}th{SE_M_REVERSAL}Tida{SE_M_BATON_PASS}Bel{SE_M_BATON_PASS}ha{SE_M_GRASSWHISTLE}finally\l"
	.string "allowe{SE_M_WATERFALL}i{SE_M_SPIT_UP}t{SE_M_ATTRACT2}appear...\n"
	.string "{PLAYER}{SE_M_SUPERSONIC}don'{SE_M_SPIT_UP}yo{SE_M_DIVE}see?\p"
	.string "LUGIA..{SE_M_PERISH_SONG}I{SE_M_SPIT_UP}mus{SE_M_SPIT_UP}hav{SE_M_REVERSAL}bee{SE_M_ATTRACT}waitin{SE_M_SANDSTORM}for\n"
	.string "someon{SE_M_REVERSAL}lik{SE_M_REVERSAL}yo{SE_M_DIVE}al{SE_M_BATON_PASS}thi{SE_M_GRASSWHISTLE}time.\p"
	.string "Wouldn'{SE_M_SPIT_UP}yo{SE_M_DIVE}agree{SE_M_SING}$"

WhirlIslands_LugiaChamber_Text_Kimono_After::
	.string "KIMON{SE_M_SOLAR_BEAM}GIRL{SE_M_HEAT_WAVE}You'v{SE_M_REVERSAL}prove{SE_M_ATTRACT}yourself\n"
	.string "today{SE_M_SUPERSONIC}{PLAYER}.$"

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
	.string "Thre{SE_M_REVERSAL}crie{SE_M_GRASSWHISTLE}cu{SE_M_SPIT_UP}throug{SE_M_TRI_ATTACK}th{SE_M_REVERSAL}cave.\pTh{SE_M_REVERSAL}bird{SE_M_GRASSWHISTLE}strik{SE_M_REVERSAL}i{SE_M_ATTRACT}{SE_M_CHARGE}cruel\npattern{SE_M_PERISH_SONG}LUGI{SE_M_BONEMERANG}turn{SE_M_GRASSWHISTLE}awa{SE_M_YAWN}from\lth{SE_M_REVERSAL}inhabite{SE_M_WATERFALL}coast.\pI{SE_M_SPIT_UP}shield{SE_M_GRASSWHISTLE}th{SE_M_REVERSAL}frightene{SE_M_WATERFALL}POKéMON\nfro{SE_M_MILK_DRINK}fallin{SE_M_SANDSTORM}stone.$"

BlackTide_Text_Technician:
	.string "ROCKE{SE_M_SWIFT}TECHNICIAN{SE_M_HEAT_WAVE}First{SE_M_SUPERSONIC}make\ni{SE_M_SPIT_UP}angry{SE_M_PERISH_SONG}The{SE_M_ATTRACT}kee{SE_M_MORNING_SUN}i{SE_M_SPIT_UP}tha{SE_M_SPIT_UP}way.\pThre{SE_M_REVERSAL}manufacture{SE_M_WATERFALL}specimens.\nThre{SE_M_REVERSAL}links{SE_M_PERISH_SONG}N{SE_M_ATTRACT2}orde{SE_M_SAND_TOMB}t{SE_M_ATTRACT2}retreat!$"

BlackTide_Text_Transformation:
	.string "Th{SE_M_REVERSAL}attack{SE_M_GRASSWHISTLE}follo{SE_M_TWISTER}on{SE_M_REVERSAL}las{SE_M_SPIT_UP}pulse.\nLUGIA'{SE_M_GRASSWHISTLE}colo{SE_M_SAND_TOMB}darkens!\pIt{SE_M_GRASSWHISTLE}cr{SE_M_YAWN}shake{SE_M_GRASSWHISTLE}th{SE_M_REVERSAL}water.\nTh{SE_M_REVERSAL}technicia{SE_M_ATTRACT}slip{SE_M_GRASSWHISTLE}away.$"

BlackTide_Text_ThreeLinks:
	.string "Th{SE_M_REVERSAL}replica{SE_M_GRASSWHISTLE}guar{SE_M_WATERFALL}thre{SE_M_REVERSAL}relays.\nSto{SE_M_MORNING_SUN}the{SE_M_MILK_DRINK}i{SE_M_ATTRACT}an{SE_M_YAWN}order.\pDefea{SE_M_SPIT_UP}o{SE_M_SAND_TOMB}catc{SE_M_TRI_ATTACK}eac{SE_M_TRI_ATTACK}replica\nt{SE_M_ATTRACT2}brea{SE_M_ENCORE2}ROCKET'{SE_M_GRASSWHISTLE}contro{SE_M_BATON_PASS}links.\pYo{SE_M_DIVE}ca{SE_M_ATTRACT}leav{SE_M_REVERSAL}t{SE_M_ATTRACT2}hea{SE_M_BATON_PASS}o{SE_M_SAND_TOMB}save.\nTher{SE_M_REVERSAL}i{SE_M_GRASSWHISTLE}n{SE_M_ATTRACT2}countdown.$"

BlackTide_Text_Articuno:
	.string "Yo{SE_M_DIVE}guid{SE_M_REVERSAL}{SE_M_CHARGE}frightene{SE_M_WATERFALL}POKéMON\nbehin{SE_M_WATERFALL}cover.\pTh{SE_M_REVERSAL}ic{SE_M_REVERSAL}replic{SE_M_CHARGE}follow{SE_M_GRASSWHISTLE}{SE_M_CHARGE}light.\nI{SE_M_SPIT_UP}attack{SE_M_GRASSWHISTLE}befor{SE_M_REVERSAL}th{SE_M_REVERSAL}nex{SE_M_SPIT_UP}pulse!$"

BlackTide_Text_Zapdos:
	.string "Eac{SE_M_TRI_ATTACK}flas{SE_M_TRI_ATTACK}make{SE_M_GRASSWHISTLE}th{SE_M_REVERSAL}rela{SE_M_YAWN}answer.\nTh{SE_M_REVERSAL}answe{SE_M_SAND_TOMB}trigger{SE_M_GRASSWHISTLE}anothe{SE_M_SAND_TOMB}flash.\pTh{SE_M_REVERSAL}electri{SE_M_HYPER_BEAM}replic{SE_M_CHARGE}turn{SE_M_GRASSWHISTLE}toward\nyou{SE_M_PERISH_SONG}Yo{SE_M_DIVE}stan{SE_M_WATERFALL}you{SE_M_SAND_TOMB}ground.$"

BlackTide_Text_Moltres:
	.string "Th{SE_M_REVERSAL}fir{SE_M_REVERSAL}replic{SE_M_CHARGE}trie{SE_M_GRASSWHISTLE}t{SE_M_ATTRACT2}leave.\nIt{SE_M_GRASSWHISTLE}flame{SE_M_GRASSWHISTLE}flare{SE_M_PERISH_SONG}Th{SE_M_REVERSAL}rela{SE_M_YAWN}answers.\pI{SE_M_SPIT_UP}turn{SE_M_GRASSWHISTLE}bac{SE_M_ENCORE2}towar{SE_M_WATERFALL}you!$"

BlackTide_Text_ReplicaWon:
	.string "Th{SE_M_REVERSAL}conditionin{SE_M_SANDSTORM}breaks.\nTh{SE_M_REVERSAL}bird'{SE_M_GRASSWHISTLE}colo{SE_M_SAND_TOMB}returns.\pI{SE_M_SPIT_UP}withdraw{SE_M_GRASSWHISTLE}safely.\nOn{SE_M_REVERSAL}contro{SE_M_BATON_PASS}lin{SE_M_ENCORE2}i{SE_M_GRASSWHISTLE}silent.$"

BlackTide_Text_ReplicaCaught:
	.string "Th{SE_M_REVERSAL}conditionin{SE_M_SANDSTORM}break{SE_M_GRASSWHISTLE}a{SE_M_GRASSWHISTLE}the\ncaugh{SE_M_SPIT_UP}bird'{SE_M_GRASSWHISTLE}colo{SE_M_SAND_TOMB}returns.\pTh{SE_M_REVERSAL}rescue{SE_M_WATERFALL}POKéMO{SE_M_PSYBEAM2}i{SE_M_GRASSWHISTLE}safe.\nOn{SE_M_REVERSAL}contro{SE_M_BATON_PASS}lin{SE_M_ENCORE2}i{SE_M_GRASSWHISTLE}silent.$"

BlackTide_Text_LinksBroken:
	.string "Th{SE_M_REVERSAL}las{SE_M_SPIT_UP}rela{SE_M_YAWN}goe{SE_M_GRASSWHISTLE}dark.\nFo{SE_M_SAND_TOMB}{SE_M_CHARGE}moment{SE_M_SUPERSONIC}th{SE_M_REVERSAL}wate{SE_M_SAND_TOMB}i{SE_M_GRASSWHISTLE}still.\p{SE_M_BONEMERANG}dee{SE_M_MORNING_SUN}cr{SE_M_YAWN}shake{SE_M_GRASSWHISTLE}th{SE_M_REVERSAL}cavern.\nLUGI{SE_M_BONEMERANG}remain{SE_M_GRASSWHISTLE}i{SE_M_ATTRACT}th{SE_M_REVERSAL}SHADO{SE_M_DETECT}state.\pTh{SE_M_REVERSAL}link{SE_M_GRASSWHISTLE}ar{SE_M_REVERSAL}gone{SE_M_PERISH_SONG}No{SE_M_TWISTER}{SE_M_CHARGE}rescue\ni{SE_M_GRASSWHISTLE}possible{SE_M_PERISH_SONG}Yo{SE_M_DIVE}ca{SE_M_ATTRACT}prepar{SE_M_REVERSAL}first.$"

BlackTide_Text_KimonoWait:
	.string "Thre{SE_M_REVERSAL}replica{SE_M_GRASSWHISTLE}kee{SE_M_MORNING_SUN}ROCKET's\ncontro{SE_M_BATON_PASS}link{SE_M_GRASSWHISTLE}alive.\pSto{SE_M_MORNING_SUN}eac{SE_M_TRI_ATTACK}one{SE_M_SUPERSONIC}i{SE_M_ATTRACT}an{SE_M_YAWN}order.\nThe{SE_M_ATTRACT}w{SE_M_REVERSAL}ca{SE_M_ATTRACT}approac{SE_M_TRI_ATTACK}LUGIA.$"

BlackTide_Text_KimonoOpening:
	.string "KIMON{SE_M_SOLAR_BEAM}GIRL{SE_M_HEAT_WAVE}Th{SE_M_REVERSAL}link{SE_M_GRASSWHISTLE}ar{SE_M_REVERSAL}gone.\nW{SE_M_REVERSAL}ca{SE_M_ATTRACT}cal{SE_M_BATON_PASS}t{SE_M_ATTRACT2}LUGI{SE_M_BONEMERANG}now.\pOu{SE_M_SAND_TOMB}danc{SE_M_REVERSAL}an{SE_M_WATERFALL}you{SE_M_SAND_TOMB}earne{SE_M_WATERFALL}TIDAL\nBEL{SE_M_BRICK_BREAK}wil{SE_M_BATON_PASS}giv{SE_M_REVERSAL}i{SE_M_SPIT_UP}{SE_M_CHARGE}familia{SE_M_SAND_TOMB}sound.$"

BlackTide_Text_KimonoClosing:
	.string "W{SE_M_REVERSAL}canno{SE_M_SPIT_UP}mak{SE_M_REVERSAL}LUGI{SE_M_BONEMERANG}trus{SE_M_SPIT_UP}us.\pStan{SE_M_WATERFALL}you{SE_M_SAND_TOMB}ground{SE_M_PERISH_SONG}Giv{SE_M_REVERSAL}it\nsomethin{SE_M_SANDSTORM}beside{SE_M_GRASSWHISTLE}th{SE_M_REVERSAL}attack\lt{SE_M_ATTRACT2}recognize.\pYo{SE_M_DIVE}ca{SE_M_ATTRACT}leav{SE_M_REVERSAL}t{SE_M_ATTRACT2}prepar{SE_M_REVERSAL}first.$"

BlackTide_Text_FaceLugia:
	.string "Fac{SE_M_REVERSAL}SHADO{SE_M_DETECT}LUGI{SE_M_BONEMERANG}now?\pYES{SE_M_HEAT_WAVE}Fac{SE_M_REVERSAL}LUGIA.\nNO{SE_M_HEAT_WAVE}Prepar{SE_M_REVERSAL}first.$"

BlackTide_Text_RestoredWon:
	.string "Th{SE_M_REVERSAL}SHADO{SE_M_DETECT}colorin{SE_M_SANDSTORM}fades.\nLUGI{SE_M_BONEMERANG}i{SE_M_GRASSWHISTLE}restored.\pFo{SE_M_SAND_TOMB}th{SE_M_REVERSAL}firs{SE_M_SPIT_UP}tim{SE_M_REVERSAL}sinc{SE_M_REVERSAL}this\nbegan{SE_M_SUPERSONIC}i{SE_M_SPIT_UP}chos{SE_M_REVERSAL}wher{SE_M_REVERSAL}t{SE_M_ATTRACT2}go.$"

BlackTide_Text_RestoredCaught:
	.string "Th{SE_M_REVERSAL}caugh{SE_M_SPIT_UP}LUGI{SE_M_BONEMERANG}i{SE_M_GRASSWHISTLE}restored.\nI{SE_M_SPIT_UP}ca{SE_M_ATTRACT}hea{SE_M_SAND_TOMB}mor{SE_M_REVERSAL}tha{SE_M_ATTRACT}command{SE_M_GRASSWHISTLE}now.\pTak{SE_M_REVERSAL}car{SE_M_REVERSAL}o{SE_M_ACID_ARMOR}it.$"

BlackTide_Text_CoastRestored:
	.string "Th{SE_M_REVERSAL}relay{SE_M_GRASSWHISTLE}ar{SE_M_REVERSAL}silent.\nTh{SE_M_REVERSAL}island{SE_M_GRASSWHISTLE}ar{SE_M_REVERSAL}recovering.\pTh{SE_M_REVERSAL}guardian'{SE_M_GRASSWHISTLE}choice{SE_M_GRASSWHISTLE}ar{SE_M_REVERSAL}it{SE_M_GRASSWHISTLE}own.$"

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
	.string "Sailor{SE_M_GRASSWHISTLE}sa{SE_M_TWISTER}thre{SE_M_REVERSAL}hug{SE_M_REVERSAL}birds\ncirclin{SE_M_SANDSTORM}th{SE_M_REVERSAL}WHIR{SE_M_BRICK_BREAK}ISLANDS.\pThe{SE_M_YAWN}too{SE_M_ENCORE2}turn{SE_M_GRASSWHISTLE}striking{SE_M_SUPERSONIC}a{SE_M_GRASSWHISTLE}if\nsomeon{SE_M_REVERSAL}tol{SE_M_WATERFALL}the{SE_M_MILK_DRINK}whe{SE_M_ATTRACT}t{SE_M_ATTRACT2}attack.\pFollo{SE_M_TWISTER}you{SE_M_SAND_TOMB}earne{SE_M_WATERFALL}legendary\njourney{SE_M_PERISH_SONG}W{SE_M_REVERSAL}canno{SE_M_SPIT_UP}rus{SE_M_TRI_ATTACK}th{SE_M_REVERSAL}sea.$"

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
	.string "KEEPER{SE_M_HEAT_WAVE}W{SE_M_REVERSAL}ca{SE_M_ATTRACT}approac{SE_M_TRI_ATTACK}now.\nW{SE_M_REVERSAL}canno{SE_M_SPIT_UP}mak{SE_M_REVERSAL}LUGI{SE_M_BONEMERANG}trus{SE_M_SPIT_UP}us.\pStan{SE_M_WATERFALL}you{SE_M_SAND_TOMB}ground{SE_M_PERISH_SONG}Giv{SE_M_REVERSAL}it\nsomethin{SE_M_SANDSTORM}beside{SE_M_GRASSWHISTLE}th{SE_M_REVERSAL}attack\lt{SE_M_ATTRACT2}recognize.\pPrepar{SE_M_REVERSAL}a{SE_M_GRASSWHISTLE}lon{SE_M_SANDSTORM}a{SE_M_GRASSWHISTLE}yo{SE_M_DIVE}need.$"

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

