@ Johto (data/maps/TinTower_RoofDay_hns/scripts.inc), as built into the FireRed game.

TinTower_RoofDay_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, TinTower_RoofDay_OnTransition
	.byte 0

TinTower_RoofDay_OnTransition:
	call_if_set JOHTO_FLAG_DAY_POKEMON, TinTower_RoofDay_EventScript_SetNight
	call_if_unset JOHTO_FLAG_DAY_POKEMON, TinTower_RoofDay_EventScript_SetDay
	goto_if_eq JOHTO_VAR_COMPLETED_HO_OH, 2, TinTower_RoofDay_MapScript_HoohStory
	goto_if_eq JOHTO_VAR_COMPLETED_HO_OH, 3, TinTower_RoofDay_MapScript_HoohPostStoryGone
	goto_if_eq JOHTO_VAR_COMPLETED_HO_OH, 4, TinTower_RoofDay_MapScript_HoohPostStoryEncounter
	end

TinTower_RoofDay_EventScript_SetNight::
	setmaplayoutindex LAYOUT_TIN_TOWER_ROOF_NIGHT_HNS
	return

TinTower_RoofDay_EventScript_SetDay::
	setmaplayoutindex LAYOUT_TIN_TOWER_ROOF_DAY_HNS
	return

TinTower_RoofDay_MapScript_HoohStory::
	clearflag JOHTO_FLAG_HIDE_HO_OH
	end

TinTower_RoofDay_MapScript_HoohPostStoryGone::
	setflag JOHTO_FLAG_HIDE_TIN_TOWER_KIMONO_GIRLS
	setflag JOHTO_FLAG_HIDE_HO_OH
	end

TinTower_RoofDay_MapScript_HoohPostStoryEncounter::
	setflag JOHTO_FLAG_HIDE_TIN_TOWER_KIMONO_GIRLS
	clearflag JOHTO_FLAG_HIDE_HO_OH
	setobjectxyperm LOCALID_HO_OH, 10, 6
	end

TinTower_RoofDay_EventScript_TalkToKimono::
	lockall
	playbgm ((558 + 1) + 0x84), FALSE
	msgbox TinTower_RoofDay_Text_Kimono_Opening, MSGBOX_DEFAULT
	closemessage

	applymovement LOCALID_KIMONO_MID, TinTower_RoofDay_Movement_Kimono_Step_Aside
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, TinTower_RoofDay_Walk_To_Center
	waitmovement 0
	applymovement LOCALID_KIMONO_MID, TinTower_RoofDay_Movement_Kimono_Step_In
	applymovement LOCALID_KIMONO_1, TinTower_RoofDay_Movement_Kimono_Step_Start_Left
	applymovement LOCALID_KIMONO_4, TinTower_RoofDay_Movement_Kimono_Step_Start_Right
	waitmovement 5
	playse SE_M_PETAL_DANCE
	applymovement LOCALID_KIMONO_MID, TinTower_RoofDay_Movement_Kimono_Dance_Mid
	waitmovement 0
	playse SE_M_PETAL_DANCE
	applymovement LOCALID_KIMONO_1, TinTower_RoofDay_Movement_Kimono_Dance_Mid
	applymovement LOCALID_TINTOWER_KIMONO_2, TinTower_RoofDay_Movement_Kimono_Dance_Mid
	applymovement LOCALID_TINTOWER_KIMONO_3, TinTower_RoofDay_Movement_Kimono_Dance_Mid
	applymovement LOCALID_KIMONO_4, TinTower_RoofDay_Movement_Kimono_Dance_Mid
	applymovement LOCALID_KIMONO_MID, TinTower_RoofDay_Movement_Kimono_Dance_Mid
	waitmovement 0
	playse SE_M_PETAL_DANCE
	setweather WEATHER_DROUGHT
	doweather

	applymovement LOCALID_KIMONO_1, TinTower_RoofDay_Movement_Kimono_Dance_Shift_Down
	applymovement LOCALID_TINTOWER_KIMONO_2, TinTower_RoofDay_Movement_Kimono_Dance_Shift_Right
	applymovement LOCALID_TINTOWER_KIMONO_3, TinTower_RoofDay_Movement_Kimono_Dance_Shift_Up
	applymovement LOCALID_KIMONO_4, TinTower_RoofDay_Movement_Kimono_Dance_Shift_Left
	waitmovement LOCALID_KIMONO_4
	delay 30
	applymovement LOCALID_KIMONO_1, TinTower_RoofDay_Movement_Kimono_Dance_Mid
	applymovement LOCALID_TINTOWER_KIMONO_2, TinTower_RoofDay_Movement_Kimono_Dance_Mid
	applymovement LOCALID_TINTOWER_KIMONO_3, TinTower_RoofDay_Movement_Kimono_Dance_Mid
	applymovement LOCALID_KIMONO_4, TinTower_RoofDay_Movement_Kimono_Dance_Mid
	applymovement LOCALID_KIMONO_MID, TinTower_RoofDay_Movement_Kimono_Dance_Mid
	waitmovement 0
	playse SE_M_PETAL_DANCE

	applymovement LOCALID_KIMONO_1, TinTower_RoofDay_Movement_Kimono_Dance_Shift_Down
	applymovement LOCALID_TINTOWER_KIMONO_2, TinTower_RoofDay_Movement_Kimono_Dance_Shift_Far_Right
	applymovement LOCALID_TINTOWER_KIMONO_3, TinTower_RoofDay_Movement_Kimono_Dance_Shift_Up
	applymovement LOCALID_KIMONO_4, TinTower_RoofDay_Movement_Kimono_Dance_Shift_Far_Left
	waitmovement LOCALID_KIMONO_4
	delay 30
	applymovement LOCALID_KIMONO_1, TinTower_RoofDay_Movement_Kimono_Dance_Mid
	applymovement LOCALID_TINTOWER_KIMONO_2, TinTower_RoofDay_Movement_Kimono_Dance_Mid
	applymovement LOCALID_TINTOWER_KIMONO_3, TinTower_RoofDay_Movement_Kimono_Dance_Mid
	applymovement LOCALID_KIMONO_4, TinTower_RoofDay_Movement_Kimono_Dance_Mid
	applymovement LOCALID_KIMONO_MID, TinTower_RoofDay_Movement_Kimono_Dance_Mid
	waitmovement 0
	playse SE_M_PETAL_DANCE

	applymovement LOCALID_KIMONO_1, TinTower_RoofDay_Movement_Kimono_Dance_Shift_Right
	applymovement LOCALID_TINTOWER_KIMONO_2, TinTower_RoofDay_Movement_Kimono_Dance_Shift_Up
	applymovement LOCALID_TINTOWER_KIMONO_3, TinTower_RoofDay_Movement_Kimono_Dance_Shift_Left
	applymovement LOCALID_KIMONO_4, TinTower_RoofDay_Movement_Kimono_Dance_Shift_Down
	waitmovement LOCALID_TINTOWER_KIMONO_3
	delay 30
	applymovement LOCALID_KIMONO_1, TinTower_RoofDay_Movement_Kimono_Dance_Mid
	applymovement LOCALID_TINTOWER_KIMONO_2, TinTower_RoofDay_Movement_Kimono_Dance_Mid
	applymovement LOCALID_TINTOWER_KIMONO_3, TinTower_RoofDay_Movement_Kimono_Dance_Mid
	applymovement LOCALID_KIMONO_4, TinTower_RoofDay_Movement_Kimono_Dance_Mid
	applymovement LOCALID_KIMONO_MID, TinTower_RoofDay_Movement_Kimono_Dance_Mid
	waitmovement 0
	playse SE_M_PETAL_DANCE

	applymovement LOCALID_KIMONO_1, TinTower_RoofDay_Movement_Kimono_Dance_Shift_Far_Right
	applymovement LOCALID_TINTOWER_KIMONO_2, TinTower_RoofDay_Movement_Kimono_Dance_Shift_Up
	applymovement LOCALID_TINTOWER_KIMONO_3, TinTower_RoofDay_Movement_Kimono_Dance_Shift_Far_Left
	applymovement LOCALID_KIMONO_4, TinTower_RoofDay_Movement_Kimono_Dance_Shift_Down
	waitmovement LOCALID_TINTOWER_KIMONO_3
	delay 30
	applymovement LOCALID_KIMONO_1, TinTower_RoofDay_Movement_Kimono_Dance_Mid
	applymovement LOCALID_TINTOWER_KIMONO_2, TinTower_RoofDay_Movement_Kimono_Dance_Mid
	applymovement LOCALID_TINTOWER_KIMONO_3, TinTower_RoofDay_Movement_Kimono_Dance_Mid
	applymovement LOCALID_KIMONO_4, TinTower_RoofDay_Movement_Kimono_Dance_Mid
	applymovement LOCALID_KIMONO_MID, TinTower_RoofDay_Movement_Kimono_Dance_Mid
	waitmovement 0
	playse SE_M_PETAL_DANCE

	applymovement LOCALID_KIMONO_1, TinTower_RoofDay_Movement_Kimono_Dance_Shift_Left_Up
	applymovement LOCALID_KIMONO_4, TinTower_RoofDay_Movement_Kimono_Dance_Shift_Right_Up
	applymovement LOCALID_KIMONO_MID, TinTower_RoofDay_Movement_Kimono_Dance_Step_Up
	waitmovement LOCALID_KIMONO_1
	delay 30
	applymovement LOCALID_KIMONO_1, TinTower_RoofDay_Movement_Kimono_Dance_Mid
	applymovement LOCALID_TINTOWER_KIMONO_2, TinTower_RoofDay_Movement_Kimono_Dance_Mid
	applymovement LOCALID_TINTOWER_KIMONO_3, TinTower_RoofDay_Movement_Kimono_Dance_Mid
	applymovement LOCALID_KIMONO_4, TinTower_RoofDay_Movement_Kimono_Dance_Mid
	applymovement LOCALID_KIMONO_MID, TinTower_RoofDay_Movement_Kimono_Dance_Mid
	waitmovement 0
	playse SE_M_PETAL_DANCE
	waitse
	setvar VAR_TEMP_1, 1
	special SpawnCameraObject
	setvar VAR_0x8004, 3
	setvar VAR_0x8005, 35
	special LoopWingFlapSE
	applymovement LOCALID_HO_OH, TinTower_RoofDay_Movement_HoOhAppear
	applymovement OBJ_EVENT_ID_CAMERA, TinTower_RoofDay_Movement_CameraPanUp
	waitmovement 0
	delay 50


	waitse
	playmoncry SPECIES_HO_OH, CRY_MODE_ENCOUNTER
	delay 30
	waitmoncry
	delay 60
	setvar VAR_0x8004, 3
	setvar VAR_0x8005, 35
	special LoopWingFlapSE
	applymovement LOCALID_HO_OH, TinTower_RoofDay_Movement_HoOhApproach
	waitmovement 0
	applymovement OBJ_EVENT_ID_CAMERA, TinTower_RoofDay_Movement_CameraPanDown
	waitmovement 0
	special RemoveCameraObject
	applymovement LOCALID_KIMONO_MID, TinTower_RoofDay_Movement_Kimono_Dance_Look_Up
	applymovement LOCALID_KIMONO_1, TinTower_RoofDay_Movement_Kimono_Dance_Look_Up
	applymovement LOCALID_TINTOWER_KIMONO_2, TinTower_RoofDay_Movement_Kimono_Dance_Look_Up
	applymovement LOCALID_TINTOWER_KIMONO_3, TinTower_RoofDay_Movement_Kimono_Dance_Look_Up
	applymovement LOCALID_KIMONO_4, TinTower_RoofDay_Movement_Kimono_Dance_Look_Up
	waitmovement 0
	msgbox TinTower_RoofDay_Text_Kimono_Closing1, MSGBOX_DEFAULT
	waitmessage
	closemessage
	releaseall
	end

TinTower_RoofDay_EventScript_HoOh::
	lockall
	goto_if_eq JOHTO_VAR_COMPLETED_HO_OH, 4, TinTower_RoofDay_EventScript_HoOhPostgame
	waitse
	playmoncry SPECIES_HO_OH, CRY_MODE_ENCOUNTER
	delay 30
	waitmoncry
	playbgm ((558 + 1) + 0x66), MUS_DUMMY
	seteventmon SPECIES_HO_OH, 50
	setflag JOHTO_FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	waitstate
	clearflag JOHTO_FLAG_SYS_CTRL_OBJ_DELETE
	setvar JOHTO_VAR_LAST_TALKED, 8
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, TinTower_RoofDay_EventScript_RanFromHoOh
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, TinTower_RoofDay_EventScript_RanFromHoOh
	call_if_eq VAR_RESULT, B_OUTCOME_WON, TinTower_RoofDay_EventScript_HoohFlewAway
	call_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, TinTower_RoofDay_EventScript_CaughtHooh
	setflag JOHTO_FLAG_HIDE_TIN_TOWER_KIMONO_GIRLS
	applymovement LOCALID_KIMONO_MID, TinTower_RoofDay_Movement_Kimono_Dance_Shift_Right2
	waitmovement 0
	clearflag JOHTO_FLAG_HIDE_ECRUTEAK_CITY_THEATER_KIMONOS
	clearflag JOHTO_FLAG_HIDE_ECRUTEAK_CITY_THEATER_ZUKI
	clearflag JOHTO_FLAG_HIDE_ECRUTEAK_CITY_THEATER_NPCS
	setvar JOHTO_VAR_ECRUTEAK_CITY_THEATER, LOCALID_HO_OH
	setvar JOHTO_VAR_COMPLETED_HO_OH, 3
	releaseall
	end

TinTower_RoofDay_EventScript_HoOhPostgame::
	playmoncry SPECIES_HO_OH, CRY_MODE_ENCOUNTER
	delay 30
	waitmoncry
	playbgm ((558 + 1) + 0x66), MUS_DUMMY
	seteventmon SPECIES_HO_OH, 70
	setflag JOHTO_FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	waitstate
	clearflag JOHTO_FLAG_SYS_CTRL_OBJ_DELETE
	setvar VAR_LAST_TALKED, LOCALID_HO_OH
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, TinTower_RoofDay_EventScript_RanFromHoOh
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, TinTower_RoofDay_EventScript_RanFromHoOh
	call_if_eq VAR_RESULT, B_OUTCOME_WON, TinTower_RoofDay_EventScript_HoohFlewAway
	call_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, TinTower_RoofDay_EventScript_CaughtHooh
	setvar JOHTO_VAR_COMPLETED_HO_OH, 3
	releaseall
	end

TinTower_RoofDay_EventScript_HoohFlewAway::
	fadescreenswapbuffers FADE_TO_BLACK
	removeobject LOCALID_HO_OH
	setweather WEATHER_NONE
	doweather
	setflag JOHTO_FLAG_HIDE_HO_OH
	fadescreenswapbuffers FADE_FROM_BLACK
	bufferspeciesname STR_VAR_1, SPECIES_HO_OH
	msgbox J_gText_LegendaryFlewAway, MSGBOX_DEFAULT
	return

TinTower_RoofDay_EventScript_CaughtHooh::
	setflag JOHTO_FLAG_CAUGHT_HO_OH
	fadescreenswapbuffers FADE_TO_BLACK
	removeobject LOCALID_HO_OH
	setweather WEATHER_NONE
	doweather
	setflag JOHTO_FLAG_HIDE_HO_OH
	fadescreenswapbuffers FADE_FROM_BLACK
	return

TinTower_RoofDay_EventScript_RanFromHoOh::
	releaseall
	end

TinTower_RoofDay_EventScript_Zuki::
	goto_if_eq JOHTO_VAR_COMPLETED_HO_OH, 3, TinTower_RoofDay_EventScript_ZukiAfter
	msgbox TinTower_RoofDay_Text_Zuki_Before, MSGBOX_NPC
	end

TinTower_RoofDay_EventScript_ZukiAfter::
	goto_if_unset JOHTO_FLAG_CAUGHT_HO_OH, TinTower_RoofDay_EventScript_ZukiAfterNotCaught
	msgbox TinTower_RoofDay_Text_Kimono_AfterCaught, MSGBOX_NPC
	end

TinTower_RoofDay_EventScript_ZukiAfterNotCaught::
	msgbox TinTower_RoofDay_Text_Kimono_AfterNotCaught, MSGBOX_NPC
	end

TinTower_RoofDay_EventScript_Naoko::
	goto_if_eq JOHTO_VAR_COMPLETED_HO_OH, 3, TinTower_RoofDay_EventScript_NaokoAfter
	msgbox TinTower_RoofDay_Text_Naoko_Before, MSGBOX_NPC
	end

TinTower_RoofDay_EventScript_NaokoAfter::
	msgbox TinTower_RoofDay_Text_Kimono_After, MSGBOX_NPC
	end

TinTower_RoofDay_EventScript_Miki::
	goto_if_eq JOHTO_VAR_COMPLETED_HO_OH, 3, TinTower_RoofDay_EventScript_MikiAfter
	msgbox TinTower_RoofDay_Text_Miki_Before, MSGBOX_NPC
	end

TinTower_RoofDay_EventScript_MikiAfter::
	msgbox TinTower_RoofDay_Text_Kimono_After, MSGBOX_NPC
	end

TinTower_RoofDay_EventScript_Sayo::
	goto_if_eq JOHTO_VAR_COMPLETED_HO_OH, 3, TinTower_RoofDay_EventScript_SayoAfter
	msgbox TinTower_RoofDay_Text_Sayo_Before, MSGBOX_NPC
	end

TinTower_RoofDay_EventScript_SayoAfter::
	msgbox TinTower_RoofDay_Text_Kimono_After, MSGBOX_NPC
	end

TinTower_RoofDay_EventScript_Kuni::
	goto_if_eq JOHTO_VAR_COMPLETED_HO_OH, 3, TinTower_RoofDay_EventScript_KuniAfter
	msgbox TinTower_RoofDay_Text_Kuni_Before, MSGBOX_NPC
	end

TinTower_RoofDay_EventScript_KuniAfter::
	msgbox TinTower_RoofDay_Text_Kimono_After, MSGBOX_NPC
	end

TinTower_RoofDay_Text_Kimono_AfterNotCaught:
	.string "Yo{SE_M_DIVE}hav{SE_M_REVERSAL}no{SE_M_SPIT_UP}onl{SE_M_YAWN}mad{SE_M_REVERSAL}HO-OH\n"
	.string "appear{SE_M_SUPERSONIC}bu{SE_M_SPIT_UP}yo{SE_M_DIVE}hav{SE_M_REVERSAL}als{SE_M_ATTRACT2}defeated\l"
	.string "it...\p"
	.string "Ther{SE_M_REVERSAL}i{SE_M_GRASSWHISTLE}nothin{SE_M_SANDSTORM}mor{SE_M_REVERSAL}fo{SE_M_SAND_TOMB}u{SE_M_GRASSWHISTLE}to\n"
	.string "say{SE_M_PERISH_SONG}Tak{SE_M_REVERSAL}car{SE_M_REVERSAL}o{SE_M_ACID_ARMOR}yoursel{SE_M_ACID_ARMOR}i{SE_M_ATTRACT}your\l"
	.string "journey...$"

TinTower_RoofDay_Text_Kimono_AfterCaught:
	.string "Yo{SE_M_DIVE}hav{SE_M_REVERSAL}no{SE_M_SPIT_UP}onl{SE_M_YAWN}mad{SE_M_REVERSAL}HO-OH\n"
	.string "appear{SE_M_SUPERSONIC}bu{SE_M_SPIT_UP}yo{SE_M_DIVE}hav{SE_M_REVERSAL}als{SE_M_ATTRACT2}caught\l"
	.string "it...\p"
	.string "Ther{SE_M_REVERSAL}i{SE_M_GRASSWHISTLE}nothin{SE_M_SANDSTORM}mor{SE_M_REVERSAL}fo{SE_M_SAND_TOMB}u{SE_M_GRASSWHISTLE}to\n"
	.string "say{SE_M_PERISH_SONG}Tak{SE_M_REVERSAL}car{SE_M_REVERSAL}o{SE_M_ACID_ARMOR}yoursel{SE_M_ACID_ARMOR}i{SE_M_ATTRACT}your\l"
	.string "journey...$"

TinTower_RoofDay_Movement_CameraPanUp:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

TinTower_RoofDay_Movement_CameraPanDown:
	delay_16
	delay_16
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

TinTower_RoofDay_Movement_HoOhApproach:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_in_place_down
	delay_16
	delay_16
	step_end

TinTower_RoofDay_Movement_HoOhAppear:
	delay_16
	delay_16
	walk_in_place_down
	walk_in_place_down
	walk_in_place_down
	walk_in_place_down
	step_end

TinTower_RoofDay_Movement_Kimono_Step_Aside:
	face_right
	delay_16
	walk_right
	delay_16
	face_left
	step_end

TinTower_RoofDay_Walk_To_Center:
	walk_up
	walk_up
	walk_up
	delay_16
	face_down
	step_end

TinTower_RoofDay_Movement_Kimono_Step_In:
	walk_left
	delay_16
	face_down
	step_end

TinTower_RoofDay_Movement_Kimono_Step_Start_Left:
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

TinTower_RoofDay_Movement_Kimono_Step_Start_Right:
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

TinTower_RoofDay_Movement_Kimono_Dance_Mid:
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

TinTower_RoofDay_Movement_Kimono_Dance_Shift_Down:
	face_down
	delay_8
	walk_down
	delay_8
	face_down
	delay_16
	step_end

TinTower_RoofDay_Movement_Kimono_Dance_Shift_Right:
	face_right
	delay_8
	walk_right
	delay_8
	face_down
	delay_16
	step_end

TinTower_RoofDay_Movement_Kimono_Dance_Shift_Up:
	face_right
	delay_8
	face_up
	delay_8
	walk_up
	delay_8
	face_down
	delay_16
	step_end

TinTower_RoofDay_Movement_Kimono_Dance_Shift_Left:
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

TinTower_RoofDay_Movement_Kimono_Dance_Shift_Far_Right:
	face_right
	delay_8
	walk_right
	walk_right
	walk_right
	face_down
	delay_16
	step_end

TinTower_RoofDay_Movement_Kimono_Dance_Shift_Far_Left:
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

TinTower_RoofDay_Movement_Kimono_Dance_Shift_Left_Up:
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

TinTower_RoofDay_Movement_Kimono_Dance_Shift_Right_Up:
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

TinTower_RoofDay_Movement_Kimono_Dance_Look_Up:
	face_right
	delay_8
	face_up
	delay_16
	step_end

TinTower_RoofDay_Movement_Kimono_Dance_Step_Up:
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

TinTower_RoofDay_Movement_Kimono_Dance_Shift_Right2:
	face_right
	delay_8
	walk_right
	delay_8
	face_down
	delay_16
	face_left
	step_end

TinTower_RoofDay_Text_Zuki_Before::
	.string "ZUKI{SE_M_HEAT_WAVE}Go{SE_M_SUPERSONIC}fac{SE_M_REVERSAL}HO-OH{SE_M_PERISH_SONG}$"

TinTower_RoofDay_Text_Naoko_Before::
	.string "NAOKO{SE_M_HEAT_WAVE}Go{SE_M_SUPERSONIC}fac{SE_M_REVERSAL}HO-OH{SE_M_PERISH_SONG}$"

TinTower_RoofDay_Text_Miki_Before::
	.string "MIKI{SE_M_HEAT_WAVE}Go{SE_M_SUPERSONIC}fac{SE_M_REVERSAL}HO-OH{SE_M_PERISH_SONG}$"

TinTower_RoofDay_Text_Sayo_Before::
	.string "SAYO{SE_M_HEAT_WAVE}Go{SE_M_SUPERSONIC}fac{SE_M_REVERSAL}HO-OH{SE_M_PERISH_SONG}$"

TinTower_RoofDay_Text_Kuni_Before::
	.string "KUNI{SE_M_HEAT_WAVE}Go{SE_M_SUPERSONIC}fac{SE_M_REVERSAL}HO-OH{SE_M_PERISH_SONG}$"

TinTower_RoofDay_Text_Kimono_Opening::
	.string "KIMON{SE_M_SOLAR_BEAM}GIRL{SE_M_HEAT_WAVE}That'{SE_M_GRASSWHISTLE}right.\n"
	.string "Thi{SE_M_GRASSWHISTLE}i{SE_M_GRASSWHISTLE}wher{SE_M_REVERSAL}w{SE_M_REVERSAL}welcom{SE_M_REVERSAL}HO-OH.\p"
	.string "Whe{SE_M_ATTRACT}th{SE_M_REVERSAL}danc{SE_M_REVERSAL}w{SE_M_REVERSAL}practice{SE_M_WATERFALL}many\n"
	.string "day{SE_M_GRASSWHISTLE}become{SE_M_GRASSWHISTLE}on{SE_M_REVERSAL}wit{SE_M_TRI_ATTACK}th{SE_M_REVERSAL}soun{SE_M_WATERFALL}o{SE_M_ACID_ARMOR}the\p"
	.string "CLEA{SE_M_MINIMIZE}BEL{SE_M_BRICK_BREAK}w{SE_M_REVERSAL}entruste{SE_M_WATERFALL}t{SE_M_ATTRACT2}you{SE_M_SUPERSONIC}then\n"
	.string "HO-O{SE_M_SWAGGER2}shal{SE_M_BATON_PASS}com{SE_M_REVERSAL}dow{SE_M_ATTRACT}fro{SE_M_MILK_DRINK}th{SE_M_REVERSAL}great\l"
	.string "arc{SE_M_TRI_ATTACK}o{SE_M_ACID_ARMOR}th{SE_M_REVERSAL}sk{SE_M_YAWN}onc{SE_M_REVERSAL}again{SE_M_PERISH_SONG}$"

TinTower_RoofDay_Text_Kimono_Closing1::
	.string "Tha{SE_M_SPIT_UP}i{SE_M_GRASSWHISTLE}indee{SE_M_WATERFALL}HO-OH...\n"
	.string "Th{SE_M_REVERSAL}guardia{SE_M_ATTRACT}o{SE_M_ACID_ARMOR}th{SE_M_REVERSAL}sk{SE_M_YAWN}from\p"
	.string "ancien{SE_M_SPIT_UP}times..{SE_M_PERISH_SONG}\p"
	.string "S{SE_M_ATTRACT2}man{SE_M_YAWN}hav{SE_M_REVERSAL}trie{SE_M_WATERFALL}agai{SE_M_ATTRACT}an{SE_M_WATERFALL}again,\n"
	.string "onl{SE_M_YAWN}t{SE_M_ATTRACT2}fail...\p"
	.string "{PLAYER}{SE_M_SUPERSONIC}you{SE_M_SAND_TOMB}hear{SE_M_SPIT_UP}i{SE_M_ATTRACT}complete\n"
	.string "harmon{SE_M_YAWN}wit{SE_M_TRI_ATTACK}th{SE_M_REVERSAL}CLEA{SE_M_MINIMIZE}BEL{SE_M_BRICK_BREAK}ha{SE_M_GRASSWHISTLE}finally\p"
	.string "allowe{SE_M_WATERFALL}i{SE_M_SPIT_UP}t{SE_M_ATTRACT2}appear...\n"
	.string "{PLAYER}{SE_M_SUPERSONIC}don'{SE_M_SPIT_UP}yo{SE_M_DIVE}see?\p"
	.string "HO-OH..{SE_M_PERISH_SONG}I{SE_M_SPIT_UP}mus{SE_M_SPIT_UP}hav{SE_M_REVERSAL}bee{SE_M_ATTRACT}waitin{SE_M_SANDSTORM}for\n"
	.string "someon{SE_M_REVERSAL}lik{SE_M_REVERSAL}yo{SE_M_DIVE}al{SE_M_BATON_PASS}thi{SE_M_GRASSWHISTLE}time.\p"
	.string "Wouldn'{SE_M_SPIT_UP}yo{SE_M_DIVE}agree{SE_M_SING}$"

TinTower_RoofDay_Text_Kimono_After::
	.string "Yo{SE_M_DIVE}hav{SE_M_REVERSAL}don{SE_M_REVERSAL}{SE_M_CHARGE}grea{SE_M_SPIT_UP}job.\n"
	.string "Sa{SE_M_YAWN}hell{SE_M_ATTRACT2}t{SE_M_ATTRACT2}PROF.EL{SE_M_GIGA_DRAIN}fo{SE_M_SAND_TOMB}us.$"

