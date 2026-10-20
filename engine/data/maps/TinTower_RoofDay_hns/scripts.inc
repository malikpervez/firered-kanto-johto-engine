@ Johto (data/maps/TinTower_RoofDay_hns/scripts.inc), as built into the FireRed game.

TinTower_RoofDay_hns_MapScripts::
	map_script 3, TinTower_RoofDay_OnTransition
	.byte 0

TinTower_RoofDay_OnTransition:
	call_if_set 8796, TinTower_RoofDay_EventScript_SetNight
	call_if_unset 8796, TinTower_RoofDay_EventScript_SetDay
	goto_if_eq 20558, 2, TinTower_RoofDay_MapScript_HoohStory
	goto_if_eq 20558, 3, TinTower_RoofDay_MapScript_HoohPostStoryGone
	goto_if_eq 20558, 4, TinTower_RoofDay_MapScript_HoohPostStoryEncounter
	end

TinTower_RoofDay_EventScript_SetNight::
	setmaplayoutindex 1106
	return

TinTower_RoofDay_EventScript_SetDay::
	setmaplayoutindex 1105
	return

TinTower_RoofDay_MapScript_HoohStory::
	clearflag 8253
	end

TinTower_RoofDay_MapScript_HoohPostStoryGone::
	setflag 8318
	setflag 8253
	end

TinTower_RoofDay_MapScript_HoohPostStoryEncounter::
	setflag 8318
	clearflag 8253
	setobjectxyperm 8, 10, 6
	end

TinTower_RoofDay_EventScript_TalkToKimono::
	lockall
	playbgm ((558 + 1) + 0x84), FALSE
	msgbox TinTower_RoofDay_Text_Kimono_Opening, MSGBOX_DEFAULT
	closemessage

	applymovement 4, TinTower_RoofDay_Movement_Kimono_Step_Aside
	waitmovement 0
	applymovement 255, TinTower_RoofDay_Walk_To_Center
	waitmovement 0
	applymovement 4, TinTower_RoofDay_Movement_Kimono_Step_In
	applymovement 3, TinTower_RoofDay_Movement_Kimono_Step_Start_Left
	applymovement 5, TinTower_RoofDay_Movement_Kimono_Step_Start_Right
	waitmovement 5
	playse 202
	applymovement 4, TinTower_RoofDay_Movement_Kimono_Dance_Mid
	waitmovement 0
	playse 202
	applymovement 3, TinTower_RoofDay_Movement_Kimono_Dance_Mid
	applymovement 6, TinTower_RoofDay_Movement_Kimono_Dance_Mid
	applymovement 7, TinTower_RoofDay_Movement_Kimono_Dance_Mid
	applymovement 5, TinTower_RoofDay_Movement_Kimono_Dance_Mid
	applymovement 4, TinTower_RoofDay_Movement_Kimono_Dance_Mid
	waitmovement 0
	playse 202
	setweather 12
	doweather

	applymovement 3, TinTower_RoofDay_Movement_Kimono_Dance_Shift_Down
	applymovement 6, TinTower_RoofDay_Movement_Kimono_Dance_Shift_Right
	applymovement 7, TinTower_RoofDay_Movement_Kimono_Dance_Shift_Up
	applymovement 5, TinTower_RoofDay_Movement_Kimono_Dance_Shift_Left
	waitmovement 5
	delay 30
	applymovement 3, TinTower_RoofDay_Movement_Kimono_Dance_Mid
	applymovement 6, TinTower_RoofDay_Movement_Kimono_Dance_Mid
	applymovement 7, TinTower_RoofDay_Movement_Kimono_Dance_Mid
	applymovement 5, TinTower_RoofDay_Movement_Kimono_Dance_Mid
	applymovement 4, TinTower_RoofDay_Movement_Kimono_Dance_Mid
	waitmovement 0
	playse 202

	applymovement 3, TinTower_RoofDay_Movement_Kimono_Dance_Shift_Down
	applymovement 6, TinTower_RoofDay_Movement_Kimono_Dance_Shift_Far_Right
	applymovement 7, TinTower_RoofDay_Movement_Kimono_Dance_Shift_Up
	applymovement 5, TinTower_RoofDay_Movement_Kimono_Dance_Shift_Far_Left
	waitmovement 5
	delay 30
	applymovement 3, TinTower_RoofDay_Movement_Kimono_Dance_Mid
	applymovement 6, TinTower_RoofDay_Movement_Kimono_Dance_Mid
	applymovement 7, TinTower_RoofDay_Movement_Kimono_Dance_Mid
	applymovement 5, TinTower_RoofDay_Movement_Kimono_Dance_Mid
	applymovement 4, TinTower_RoofDay_Movement_Kimono_Dance_Mid
	waitmovement 0
	playse 202

	applymovement 3, TinTower_RoofDay_Movement_Kimono_Dance_Shift_Right
	applymovement 6, TinTower_RoofDay_Movement_Kimono_Dance_Shift_Up
	applymovement 7, TinTower_RoofDay_Movement_Kimono_Dance_Shift_Left
	applymovement 5, TinTower_RoofDay_Movement_Kimono_Dance_Shift_Down
	waitmovement 7
	delay 30
	applymovement 3, TinTower_RoofDay_Movement_Kimono_Dance_Mid
	applymovement 6, TinTower_RoofDay_Movement_Kimono_Dance_Mid
	applymovement 7, TinTower_RoofDay_Movement_Kimono_Dance_Mid
	applymovement 5, TinTower_RoofDay_Movement_Kimono_Dance_Mid
	applymovement 4, TinTower_RoofDay_Movement_Kimono_Dance_Mid
	waitmovement 0
	playse 202

	applymovement 3, TinTower_RoofDay_Movement_Kimono_Dance_Shift_Far_Right
	applymovement 6, TinTower_RoofDay_Movement_Kimono_Dance_Shift_Up
	applymovement 7, TinTower_RoofDay_Movement_Kimono_Dance_Shift_Far_Left
	applymovement 5, TinTower_RoofDay_Movement_Kimono_Dance_Shift_Down
	waitmovement 7
	delay 30
	applymovement 3, TinTower_RoofDay_Movement_Kimono_Dance_Mid
	applymovement 6, TinTower_RoofDay_Movement_Kimono_Dance_Mid
	applymovement 7, TinTower_RoofDay_Movement_Kimono_Dance_Mid
	applymovement 5, TinTower_RoofDay_Movement_Kimono_Dance_Mid
	applymovement 4, TinTower_RoofDay_Movement_Kimono_Dance_Mid
	waitmovement 0
	playse 202

	applymovement 3, TinTower_RoofDay_Movement_Kimono_Dance_Shift_Left_Up
	applymovement 5, TinTower_RoofDay_Movement_Kimono_Dance_Shift_Right_Up
	applymovement 4, TinTower_RoofDay_Movement_Kimono_Dance_Step_Up
	waitmovement 3
	delay 30
	applymovement 3, TinTower_RoofDay_Movement_Kimono_Dance_Mid
	applymovement 6, TinTower_RoofDay_Movement_Kimono_Dance_Mid
	applymovement 7, TinTower_RoofDay_Movement_Kimono_Dance_Mid
	applymovement 5, TinTower_RoofDay_Movement_Kimono_Dance_Mid
	applymovement 4, TinTower_RoofDay_Movement_Kimono_Dance_Mid
	waitmovement 0
	playse 202
	waitse
	setvar 16385, 1
	special SpawnCameraObject
	setvar 32772, 3
	setvar 32773, 35
	special LoopWingFlapSE
	applymovement 8, TinTower_RoofDay_Movement_HoOhAppear
	applymovement 127, TinTower_RoofDay_Movement_CameraPanUp
	waitmovement 0
	delay 50


	waitse
	playmoncry 250, 2
	delay 30
	waitmoncry
	delay 60
	setvar 32772, 3
	setvar 32773, 35
	special LoopWingFlapSE
	applymovement 8, TinTower_RoofDay_Movement_HoOhApproach
	waitmovement 0
	applymovement 127, TinTower_RoofDay_Movement_CameraPanDown
	waitmovement 0
	special RemoveCameraObject
	applymovement 4, TinTower_RoofDay_Movement_Kimono_Dance_Look_Up
	applymovement 3, TinTower_RoofDay_Movement_Kimono_Dance_Look_Up
	applymovement 6, TinTower_RoofDay_Movement_Kimono_Dance_Look_Up
	applymovement 7, TinTower_RoofDay_Movement_Kimono_Dance_Look_Up
	applymovement 5, TinTower_RoofDay_Movement_Kimono_Dance_Look_Up
	waitmovement 0
	msgbox TinTower_RoofDay_Text_Kimono_Closing1, MSGBOX_DEFAULT
	waitmessage
	closemessage
	releaseall
	end

TinTower_RoofDay_EventScript_HoOh::
	lockall
	goto_if_eq 20558, 4, TinTower_RoofDay_EventScript_HoOhPostgame
	waitse
	playmoncry 250, 2
	delay 30
	waitmoncry
	playbgm ((558 + 1) + 0x66), 0
	seteventmon 250, 50
	setflag 10342
	special BattleSetup_StartLegendaryBattle
	waitstate
	clearflag 10342
	setvar 32783, 8
	specialvar 32781, GetBattleOutcome
	goto_if_eq 32781, 4, TinTower_RoofDay_EventScript_RanFromHoOh
	goto_if_eq 32781, 5, TinTower_RoofDay_EventScript_RanFromHoOh
	call_if_eq 32781, 1, TinTower_RoofDay_EventScript_HoohFlewAway
	call_if_eq 32781, 7, TinTower_RoofDay_EventScript_CaughtHooh
	setflag 8318
	applymovement 4, TinTower_RoofDay_Movement_Kimono_Dance_Shift_Right2
	waitmovement 0
	clearflag 8310
	clearflag 8312
	clearflag 8311
	setvar 20562, 8
	setvar 20558, 3
	releaseall
	end

TinTower_RoofDay_EventScript_HoOhPostgame::
	playmoncry 250, 2
	delay 30
	waitmoncry
	playbgm ((558 + 1) + 0x66), 0
	seteventmon 250, 70
	setflag 10342
	special BattleSetup_StartLegendaryBattle
	waitstate
	clearflag 10342
	setvar 32783, 8
	specialvar 32781, GetBattleOutcome
	goto_if_eq 32781, 4, TinTower_RoofDay_EventScript_RanFromHoOh
	goto_if_eq 32781, 5, TinTower_RoofDay_EventScript_RanFromHoOh
	call_if_eq 32781, 1, TinTower_RoofDay_EventScript_HoohFlewAway
	call_if_eq 32781, 7, TinTower_RoofDay_EventScript_CaughtHooh
	setvar 20558, 3
	releaseall
	end

TinTower_RoofDay_EventScript_HoohFlewAway::
	fadescreenswapbuffers 1
	removeobject 8
	setweather 0
	doweather
	setflag 8253
	fadescreenswapbuffers 0
	bufferspeciesname STR_VAR_1, 250
	msgbox J_gText_LegendaryFlewAway, MSGBOX_DEFAULT
	return

TinTower_RoofDay_EventScript_CaughtHooh::
	setflag 8764
	fadescreenswapbuffers 1
	removeobject 8
	setweather 0
	doweather
	setflag 8253
	fadescreenswapbuffers 0
	return

TinTower_RoofDay_EventScript_RanFromHoOh::
	releaseall
	end

TinTower_RoofDay_EventScript_Zuki::
	goto_if_eq 20558, 3, TinTower_RoofDay_EventScript_ZukiAfter
	msgbox TinTower_RoofDay_Text_Zuki_Before, MSGBOX_NPC
	end

TinTower_RoofDay_EventScript_ZukiAfter::
	goto_if_unset 8764, TinTower_RoofDay_EventScript_ZukiAfterNotCaught
	msgbox TinTower_RoofDay_Text_Kimono_AfterCaught, MSGBOX_NPC
	end

TinTower_RoofDay_EventScript_ZukiAfterNotCaught::
	msgbox TinTower_RoofDay_Text_Kimono_AfterNotCaught, MSGBOX_NPC
	end

TinTower_RoofDay_EventScript_Naoko::
	goto_if_eq 20558, 3, TinTower_RoofDay_EventScript_NaokoAfter
	msgbox TinTower_RoofDay_Text_Naoko_Before, MSGBOX_NPC
	end

TinTower_RoofDay_EventScript_NaokoAfter::
	msgbox TinTower_RoofDay_Text_Kimono_After, MSGBOX_NPC
	end

TinTower_RoofDay_EventScript_Miki::
	goto_if_eq 20558, 3, TinTower_RoofDay_EventScript_MikiAfter
	msgbox TinTower_RoofDay_Text_Miki_Before, MSGBOX_NPC
	end

TinTower_RoofDay_EventScript_MikiAfter::
	msgbox TinTower_RoofDay_Text_Kimono_After, MSGBOX_NPC
	end

TinTower_RoofDay_EventScript_Sayo::
	goto_if_eq 20558, 3, TinTower_RoofDay_EventScript_SayoAfter
	msgbox TinTower_RoofDay_Text_Sayo_Before, MSGBOX_NPC
	end

TinTower_RoofDay_EventScript_SayoAfter::
	msgbox TinTower_RoofDay_Text_Kimono_After, MSGBOX_NPC
	end

TinTower_RoofDay_EventScript_Kuni::
	goto_if_eq 20558, 3, TinTower_RoofDay_EventScript_KuniAfter
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

