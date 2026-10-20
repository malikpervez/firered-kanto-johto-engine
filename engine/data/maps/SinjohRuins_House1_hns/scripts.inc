@ Johto (data/maps/SinjohRuins_House1_hns/scripts.inc), as built into the FireRed game.

SinjohRuins_House1_hns_MapScripts::
	map_script 2, SinjohRuins_Lab_OnFrame
	map_script 3, SinjohRuins_Lab_OnTransition
	.byte 0

SinjohRuins_Lab_OnTransition::
	call_if_eq 20639, 7, SinjohRuins_Lab_SetupFinalPlateScene
	end

SinjohRuins_Lab_OnFrame::
	map_script_2 20639, 7, SinjohRuins_Lab_FinalPlateScene
	.2byte 0

SinjohRuins_Lab_EventScript_TriggerIntroTop::
	lock
	playse 21
	applymovement2 8, J_Common_Movement_ExclamationMark
	delay 55
	waitmovement 8
	msgbox SinjohRuins_Lab_Text_StevenIntroCutscene1, MSGBOX_DEFAULT
	closemessage
	applymovement2 255, J_Common_Movement_WalkDown1
	applymovement2 8, SinjohRuins_Lab_Movement_StevenMeetPlayer
	waitmovement 0
	waitmovement 8
	goto SinjohRuins_Lab_EventScript_TriggerIntro

SinjohRuins_Lab_EventScript_TriggerIntroMid::
	lock
	playse 21
	applymovement2 8, J_Common_Movement_ExclamationMark
	delay 55
	waitmovement 8
	msgbox SinjohRuins_Lab_Text_StevenIntroCutscene1, MSGBOX_DEFAULT
	closemessage
	applymovement2 8, SinjohRuins_Lab_Movement_StevenMeetPlayer
	waitmovement 8
	goto SinjohRuins_Lab_EventScript_TriggerIntro

SinjohRuins_Lab_EventScript_TriggerIntroBot::
	lock
	playse 21
	applymovement2 8, J_Common_Movement_ExclamationMark
	delay 55
	waitmovement 8
	msgbox SinjohRuins_Lab_Text_StevenIntroCutscene1, MSGBOX_DEFAULT
	closemessage
	applymovement2 255, J_Common_Movement_WalkUp1
	applymovement2 8, SinjohRuins_Lab_Movement_StevenMeetPlayer
	waitmovement 0
	waitmovement 8
	goto SinjohRuins_Lab_EventScript_TriggerIntro

SinjohRuins_Lab_EventScript_TriggerIntro::
	turnobject 255, DIR_EAST
	msgbox SinjohRuins_Lab_Text_StevenIntroCutscene2, MSGBOX_DEFAULT
	closemessage
	applymovement2 8, SinjohRuins_Lab_Movement_StevenSitsDown
	delay 10
	applymovement 255, SinjohRuins_Lab_Movement_PlayerGoesToTable
	delay 40
	applymovement2 1, SinjohRuins_Lab_Movement_LinguistWalkDown
	waitmovement 0
	waitmovement 8
	waitmovement 1
	applymovement2 8, J_Common_Movement_WalkInPlaceRight
	waitmovement 0
	msgbox SinjohRuins_Lab_Text_StevenIntroCutscene3, MSGBOX_DEFAULT
	closemessage
	delay 10
	applymovement2 1, J_Common_Movement_WalkInPlaceDown
	waitmovement 0
	msgbox SinjohRuins_Lab_Text_StevenIntroCutscene4, MSGBOX_DEFAULT
	closemessage
	delay 10
	applymovement 1, SinjohRuins_Lab_Movement_LinguistWalkUp
	applymovement2 8, J_Common_Movement_WalkInPlaceRight
	waitmovement 0
	msgbox SinjohRuins_Lab_Text_StevenIntroCutscene5, MSGBOX_YESNO
	goto_if_eq 32781, TRUE, SinjohRuins_Lab_EventScript_IntroChoseYes

SinjohRuins_Lab_EventScript_IntroChoice::
	msgbox SinjohRuins_Lab_Text_StevenIntroCutsceneRefused, MSGBOX_YESNO
	goto_if_eq 32781, TRUE, SinjohRuins_Lab_EventScript_IntroChoseYes
	goto SinjohRuins_Lab_EventScript_IntroChoice

SinjohRuins_Lab_EventScript_IntroChoseYes::
	msgbox SinjohRuins_Lab_Text_StevenIntroCutscene6, MSGBOX_DEFAULT
	closemessage
	setvar 20639, 6
	setvar 20642, 1
	setvar 20645, 1
	setvar 20646, 1
	setvar 20647, 1
	setvar 20648, 1
	setvar 20649, 1
	setvar 20650, 1
	setvar 20651, 1
	release
	end

SinjohRuins_Lab_Movement_StevenMeetPlayer:
	walk_up
	walk_up
	walk_up
	face_left
	step_end

SinjohRuins_Lab_Movement_StevenSitsDown:
	walk_down
	walk_down
	walk_down
	face_right
	step_end

SinjohRuins_Lab_Movement_PlayerGoesToTable:
	walk_right
	walk_right
	walk_right
	walk_down
	walk_right
	walk_right
	walk_down
	walk_down
	walk_right
	face_left
	step_end

SinjohRuins_Lab_Movement_LinguistWalkDown:
	walk_down
	walk_left
	walk_left
	walk_down
	walk_down
	walk_down
	walk_down
	face_down
	step_end

SinjohRuins_Lab_Movement_LinguistWalkUp:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_right
	walk_right
	walk_up
	step_end

SinjohRuins_Lab_Text_StevenIntroCutscene1:
	.string "STEVEN{SE_M_HEAT_WAVE}Hm?$"

SinjohRuins_Lab_Text_StevenIntroCutscene2:
	.string "STEVEN{SE_M_HEAT_WAVE}{PLAYER}!\p"
	.string "I'{SE_M_WATERFALL}recogniz{SE_M_REVERSAL}thos{SE_M_REVERSAL}eye{SE_M_GRASSWHISTLE}anywhere.\p"
	.string "Wha{SE_M_SPIT_UP}bring{SE_M_GRASSWHISTLE}yo{SE_M_DIVE}thi{SE_M_GRASSWHISTLE}fa{SE_M_SAND_TOMB}north?\p"
	.string ".............\p"
	.string "{SE_M_HEAL_BELL}see{SE_M_SUPERSONIC}th{SE_M_REVERSAL}KIMON{SE_M_SOLAR_BEAM}GIRL{SE_M_SKETCH}o{SE_M_ACID_ARMOR}NE{SE_M_DETECT}SINJOH\n"
	.string "hav{SE_M_REVERSAL}sen{SE_M_SPIT_UP}yo{SE_M_DIVE}t{SE_M_ATTRACT2}ai{SE_M_WATERFALL}our\l"
	.string "investigation.\p"
	.string "I{SE_M_ATTRACT}tha{SE_M_SPIT_UP}case{SE_M_SUPERSONIC}allo{SE_M_TWISTER}m{SE_M_REVERSAL}t{SE_M_ATTRACT2}brin{SE_M_SANDSTORM}you\n"
	.string "u{SE_M_MORNING_SUN}t{SE_M_ATTRACT2}speed.$"

SinjohRuins_Lab_Text_StevenIntroCutscene3:
	.string "STEVEN{SE_M_HEAT_WAVE}Whe{SE_M_ATTRACT}{SE_M_HEAL_BELL}firs{SE_M_SPIT_UP}hear{SE_M_WATERFALL}about\n"
	.string "thes{SE_M_REVERSAL}ruins{SE_M_SUPERSONIC}{SE_M_HEAL_BELL}ha{SE_M_WATERFALL}t{SE_M_ATTRACT2}com{SE_M_REVERSAL}see\l"
	.string "the{SE_M_MILK_DRINK}fo{SE_M_SAND_TOMB}myself.\p"
	.string "{SE_M_HEAL_BELL}assemble{SE_M_WATERFALL}{SE_M_CHARGE}tea{SE_M_MILK_DRINK}fro{SE_M_MILK_DRINK}DEVO{SE_M_PSYBEAM2}CORP.\n"
	.string "an{SE_M_WATERFALL}w{SE_M_REVERSAL}se{SE_M_SPIT_UP}of{SE_M_ACID_ARMOR}o{SE_M_ATTRACT}{SE_M_CHARGE}research\l"
	.string "expedition.\p"
	.string "Wh{SE_M_ATTRACT2}know{SE_M_GRASSWHISTLE}wha{SE_M_SPIT_UP}we'l{SE_M_BATON_PASS}fin{SE_M_WATERFALL}buried\n"
	.string "here.\p"
	.string "We'v{SE_M_REVERSAL}learne{SE_M_WATERFALL}quit{SE_M_REVERSAL}{SE_M_CHARGE}lot\n"
	.string "already.$"

SinjohRuins_Lab_Text_StevenIntroCutscene4:
	.string "LINGUIST{SE_M_HEAT_WAVE}Whil{SE_M_REVERSAL}th{SE_M_REVERSAL}ful{SE_M_BATON_PASS}translation\n"
	.string "o{SE_M_ACID_ARMOR}th{SE_M_REVERSAL}glyph{SE_M_GRASSWHISTLE}foun{SE_M_WATERFALL}aroun{SE_M_WATERFALL}th{SE_M_REVERSAL}ruins\l"
	.string "stil{SE_M_BATON_PASS}elude{SE_M_GRASSWHISTLE}me{SE_M_SUPERSONIC}I'v{SE_M_REVERSAL}bee{SE_M_ATTRACT}able\l"
	.string "t{SE_M_ATTRACT2}mak{SE_M_REVERSAL}ou{SE_M_SPIT_UP}som{SE_M_REVERSAL}aspects.\p"
	.string "Ther{SE_M_REVERSAL}ar{SE_M_REVERSAL}1{SE_M_MIST}peculia{SE_M_SAND_TOMB}PLATES.\p"
	.string "The{SE_M_YAWN}hav{SE_M_REVERSAL}som{SE_M_REVERSAL}significance\n"
	.string "t{SE_M_ATTRACT2}th{SE_M_REVERSAL}ruins{SE_M_SUPERSONIC}bu{SE_M_SPIT_UP}we'v{SE_M_REVERSAL}only\l"
	.string "foun{SE_M_WATERFALL}{SE_M_HEADBUTT}s{SE_M_ATTRACT2}far.\p"
	.string "Th{SE_M_REVERSAL}res{SE_M_SPIT_UP}ar{SE_M_REVERSAL}sai{SE_M_WATERFALL}t{SE_M_ATTRACT2}b{SE_M_REVERSAL}guarded\n"
	.string "b{SE_M_YAWN}POKéMO{SE_M_PSYBEAM2}an{SE_M_WATERFALL}trainer{SE_M_GRASSWHISTLE}of\l"
	.string "awesom{SE_M_REVERSAL}power.$"

SinjohRuins_Lab_Text_StevenIntroCutscene5:
	.string "STEVEN{SE_M_HEAT_WAVE}That'{SE_M_GRASSWHISTLE}th{SE_M_REVERSAL}story{SE_M_SUPERSONIC}{PLAYER}.\p"
	.string "Th{SE_M_REVERSAL}NOBL{SE_M_SWORDS_DANCE}POKéMO{SE_M_PSYBEAM2}tha{SE_M_SPIT_UP}guar{SE_M_WATERFALL}the\n"
	.string "remainin{SE_M_SANDSTORM}PLATE{SE_M_SKETCH}ar{SE_M_REVERSAL}to{SE_M_ATTRACT2}strong\l"
	.string "fo{SE_M_SAND_TOMB}m{SE_M_YAWN}team{SE_M_SUPERSONIC}I'{SE_M_MILK_DRINK}afraid.\p"
	.string "An{SE_M_WATERFALL}{SE_M_HEAL_BELL}nee{SE_M_WATERFALL}t{SE_M_ATTRACT2}sta{SE_M_YAWN}her{SE_M_REVERSAL}t{SE_M_ATTRACT2}oversee\n"
	.string "th{SE_M_REVERSAL}research.\p"
	.string "Bu{SE_M_SPIT_UP}{SE_M_HEAL_BELL}thin{SE_M_ENCORE2}yo{SE_M_DIVE}coul{SE_M_WATERFALL}d{SE_M_ATTRACT2}it.\n"
	.string "Wil{SE_M_BATON_PASS}yo{SE_M_DIVE}hel{SE_M_MORNING_SUN}us?$"

SinjohRuins_Lab_Text_StevenIntroCutscene6:
	.string "Excellent.\p"
	.string "Th{SE_M_REVERSAL}glyph{SE_M_GRASSWHISTLE}sa{SE_M_YAWN}th{SE_M_REVERSAL}PLATE{SE_M_SKETCH}are\n"
	.string "hel{SE_M_WATERFALL}b{SE_M_YAWN}NOBL{SE_M_SWORDS_DANCE}POKéMO{SE_M_PSYBEAM2}and\l"
	.string "stron{SE_M_SANDSTORM}trainer{SE_M_GRASSWHISTLE}acros{SE_M_GRASSWHISTLE}SINJOH.\p"
	.string "I'l{SE_M_BATON_PASS}cal{SE_M_BATON_PASS}you{SE_M_SAND_TOMB}POKéGEA{SE_M_MINIMIZE}i{SE_M_ACID_ARMOR}we\n"
	.string "lear{SE_M_ATTRACT}anythin{SE_M_SANDSTORM}new.\p"
	.string "Than{SE_M_ENCORE2}you{SE_M_SUPERSONIC}{PLAYER}.$"

SinjohRuins_Lab_Text_StevenIntroCutsceneRefused:
	.string "Ar{SE_M_REVERSAL}yo{SE_M_DIVE}sure?\p"
	.string "Wh{SE_M_ATTRACT2}know{SE_M_GRASSWHISTLE}wha{SE_M_SPIT_UP}we'l{SE_M_BATON_PASS}fin{SE_M_WATERFALL}buried\n"
	.string "here.\p"
	.string "Won'{SE_M_SPIT_UP}yo{SE_M_DIVE}reconsider?$"

SinjohRuins_Lab_SetupFinalPlateScene::
	setobjectxyperm 8, 4, 7
	setobjectmovementtype 8, 0xA
	setobjectxyperm 1, 5, 7
	setobjectmovementtype 1, 0x9
	return

SinjohRuins_Lab_FinalPlateScene::
	lock
	applymovement 255, J_Common_Movement_WalkUp1
	waitmovement 0
	applymovement 255, J_Common_Movement_WalkUp1
	waitmovement 0
	playse 21
	applymovement 8, J_Common_Movement_ExclamationMark
	delay 55
	waitmovement 8
	turnobject 8, DIR_SOUTH
	delay 30
	applymovement 8, J_Common_Movement_WalkDown1
	turnobject 1, DIR_SOUTH
	delay 30
	msgbox SinjohRuins_Lab_Text_FinalPlateScene1, MSGBOX_DEFAULT
	closemessage
	dofieldeffectsparkle 3, 8, 0
	waitfieldeffect 54
	setvar 32781, 3
	playfanfare 388
	playse 107
	special DoOrbEffect
	delay 200
	special FadeOutOrbEffect
	waitstate
	setvar 32772, 2
	setvar 32773, 2
	setvar 32774, 40
	setvar 32775, 3
	special ShakeCamera
	waitstate
	msgbox SinjohRuins_Lab_Text_FinalPlateScene2, MSGBOX_DEFAULT
	closemessage
	applymovement 255, SinjohRuins_Lab_Movement_PlayerLeaveLab
	applymovement 8, SinjohRuins_Lab_Movement_StevenLeaveLab
	waitmovement 0
	waitmovement 0
	setvar 20639, 8
	warp MAP_SINJOH_RUINS_HNS, 0
	waitstate
	end

SinjohRuins_Lab_Text_FinalPlateScene1:
	.string "STEVEN{SE_M_HEAT_WAVE}{PLAYER}!\p"
	.string "{SE_M_HEAL_BELL}thin{SE_M_ENCORE2}{SE_M_HEAL_BELL}kno{SE_M_TWISTER}what'{SE_M_GRASSWHISTLE}goin{SE_M_SANDSTORM}to\n"
	.string "happe{SE_M_ATTRACT}w{SE_M_REVERSAL}brin{SE_M_SANDSTORM}togethe{SE_M_SAND_TOMB}al{SE_M_BATON_PASS}1{SE_M_MIST}of\l"
	.string "th{SE_M_REVERSAL}PLATES.\p"
	.string "{SE_M_HEAL_BELL}feel...\l"
	.string ".....................$"

SinjohRuins_Lab_Text_FinalPlateScene2:
	.string "STEVEN{SE_M_HEAT_WAVE}{SE_M_HEAL_BELL}nee{SE_M_WATERFALL}t{SE_M_ATTRACT2}se{SE_M_REVERSAL}thi{SE_M_GRASSWHISTLE}for\n"
	.string "myself!\p"
	.string "Outside{SE_M_SUPERSONIC}{PLAYER}!$"

SinjohRuins_Lab_Movement_PlayerLeaveLab:
	walk_fast_down
	walk_fast_down
	walk_in_place_fast_down
	step_end

SinjohRuins_Lab_Movement_StevenLeaveLab:
	walk_fast_down
	walk_fast_down
	walk_in_place_fast_down
	step_end

SinjohRuins_Lab_EventScript_Steven::
	lock
	faceplayer
	buffernumberstring STR_VAR_1, 20640
	goto_if_ge 20640, 17, SinjohRuins_Lab_EventScript_StevenAfterAllPlates
	goto_if_ge 20640, 15, SinjohRuins_Lab_EventScript_StevenAfter15Plates
	goto_if_ge 20640, 12, SinjohRuins_Lab_EventScript_StevenAfter12Plates
	goto_if_ge 20640, 9, SinjohRuins_Lab_EventScript_StevenAfter9Plates
	goto_if_ge 20640, 6, SinjohRuins_Lab_EventScript_StevenAfter6Plates
	goto_if_ge 20640, 3, SinjohRuins_Lab_EventScript_StevenAfter3Plates
	msgbox SinjohRuins_Lab_Text_StevenFindPlates, MSGBOX_AUTOCLOSE
	release
	end

SinjohRuins_Lab_EventScript_StevenAfter3Plates::
	msgbox SinjohRuins_Lab_Text_StevenFindPlates3, MSGBOX_AUTOCLOSE
	release
	end

SinjohRuins_Lab_EventScript_StevenAfter6Plates::
	msgbox SinjohRuins_Lab_Text_StevenFindPlates3, MSGBOX_AUTOCLOSE
	release
	end

SinjohRuins_Lab_EventScript_StevenAfter9Plates::
	msgbox SinjohRuins_Lab_Text_StevenFindPlates9, MSGBOX_AUTOCLOSE
	release
	end

SinjohRuins_Lab_EventScript_StevenAfter12Plates::
	msgbox SinjohRuins_Lab_Text_StevenFindPlates9, MSGBOX_AUTOCLOSE
	release
	end

SinjohRuins_Lab_EventScript_StevenAfter15Plates::
	msgbox SinjohRuins_Lab_Text_StevenFindPlates9, MSGBOX_AUTOCLOSE
	release
	end

SinjohRuins_Lab_EventScript_StevenAfterAllPlates::
	msgbox SinjohRuins_Lab_Text_StevenAfterAll, MSGBOX_AUTOCLOSE
	release
	end

SinjohRuins_Lab_Text_StevenFindPlates:
	.string "STEVEN{SE_M_HEAT_WAVE}Ah{SE_M_SUPERSONIC}{PLAYER}.\p"
	.string "{STR_VAR_1} PLATE{SE_M_SKETCH}s{SE_M_ATTRACT2}far.\n"
	.string "No{SE_M_SPIT_UP}ba{SE_M_WATERFALL}a{SE_M_SPIT_UP}all.\p"
	.string "{SE_M_HEAL_BELL}hav{SE_M_REVERSAL}t{SE_M_ATTRACT2}admit{SE_M_SUPERSONIC}I'{SE_M_MILK_DRINK}curious\n"
	.string "wha{SE_M_SPIT_UP}wil{SE_M_BATON_PASS}happe{SE_M_ATTRACT}onc{SE_M_REVERSAL}they're\l"
	.string "al{SE_M_BATON_PASS}gathered.\p"
	.string "Well{SE_M_SUPERSONIC}let'{SE_M_GRASSWHISTLE}se{SE_M_REVERSAL}wha{SE_M_SPIT_UP}yo{SE_M_DIVE}find.$"

SinjohRuins_Lab_Text_StevenFindPlates3:
	.string "STEVEN{SE_M_HEAT_WAVE}Ah{SE_M_SUPERSONIC}{PLAYER}.\p"
	.string "{STR_VAR_1} PLATE{SE_M_SKETCH}s{SE_M_ATTRACT2}far.\n"
	.string "No{SE_M_SPIT_UP}ba{SE_M_WATERFALL}a{SE_M_SPIT_UP}all.\p"
	.string "Hav{SE_M_REVERSAL}yo{SE_M_DIVE}investigate{SE_M_WATERFALL}that\n"
	.string "chambe{SE_M_SAND_TOMB}yet?\l"
	.string "It'{SE_M_GRASSWHISTLE}al{SE_M_BATON_PASS}quit{SE_M_REVERSAL}mysterious.$"

SinjohRuins_Lab_Text_StevenFindPlates9:
	.string "STEVEN{SE_M_HEAT_WAVE}Ah{SE_M_SUPERSONIC}{PLAYER}.\p"
	.string "{STR_VAR_1} PLATE{SE_M_SKETCH}s{SE_M_ATTRACT2}far.\n"
	.string "Makin{SE_M_SANDSTORM}grea{SE_M_SPIT_UP}progress.\p"
	.string "Th{SE_M_REVERSAL}chamber{SE_M_GRASSWHISTLE}tha{SE_M_SPIT_UP}hav{SE_M_REVERSAL}opened\n"
	.string "u{SE_M_MORNING_SUN}bea{SE_M_SAND_TOMB}{SE_M_CHARGE}strikin{SE_M_SANDSTORM}similarity\l"
	.string "t{SE_M_ATTRACT2}{SE_M_CHARGE}serie{SE_M_GRASSWHISTLE}o{SE_M_ACID_ARMOR}chambers\l"
	.string "i{SE_M_ATTRACT}th{SE_M_REVERSAL}HOEN{SE_M_PSYBEAM2}region.\p"
	.string "Eac{SE_M_TRI_ATTACK}o{SE_M_ACID_ARMOR}thos{SE_M_REVERSAL}wa{SE_M_GRASSWHISTLE}als{SE_M_ATTRACT2}hom{SE_M_REVERSAL}t{SE_M_ATTRACT2}a\n"
	.string "legendar{SE_M_YAWN}POKéMON.\p"
	.string "Bu{SE_M_SPIT_UP}i{SE_M_ATTRACT}HOENN{SE_M_SUPERSONIC}onl{SE_M_YAWN}{SE_M_HYDRO_PUMP}wer{SE_M_REVERSAL}ever\n"
	.string "discovered.\p"
	.string "An{SE_M_WATERFALL}here{SE_M_SUPERSONIC}ther{SE_M_REVERSAL}ar{SE_M_REVERSAL}a{SE_M_SPIT_UP}leas{SE_M_SPIT_UP}6.\p"
	.string "Wh{SE_M_ATTRACT2}know{SE_M_GRASSWHISTLE}wha{SE_M_SPIT_UP}we'l{SE_M_BATON_PASS}fin{SE_M_WATERFALL}next.$"

SinjohRuins_Lab_Text_StevenAfterAll:
	.string "STEVEN{SE_M_HEAT_WAVE}{PLAYER}!\p"
	.string "Thi{SE_M_GRASSWHISTLE}expeditio{SE_M_ATTRACT}ha{SE_M_GRASSWHISTLE}bee{SE_M_ATTRACT}the\n"
	.string "experienc{SE_M_REVERSAL}o{SE_M_ACID_ARMOR}{SE_M_CHARGE}lifetime.\p"
	.string "Eve{SE_M_SAND_TOMB}sinc{SE_M_REVERSAL}{SE_M_HEAL_BELL}hear{SE_M_WATERFALL}abou{SE_M_SPIT_UP}thes{SE_M_REVERSAL}ruins,\n"
	.string "{SE_M_HEAL_BELL}ha{SE_M_WATERFALL}thi{SE_M_GRASSWHISTLE}feeling.\p"
	.string "{SE_M_HEAL_BELL}though{SE_M_SPIT_UP}w{SE_M_REVERSAL}woul{SE_M_WATERFALL}discove{SE_M_SAND_TOMB}something\n"
	.string "amazing.\p"
	.string "An{SE_M_WATERFALL}m{SE_M_YAWN}prediction{SE_M_GRASSWHISTLE}usuall{SE_M_YAWN}com{SE_M_REVERSAL}true.\p"
	.string "Than{SE_M_ENCORE2}yo{SE_M_DIVE}fo{SE_M_SAND_TOMB}al{SE_M_BATON_PASS}you{SE_M_SAND_TOMB}help,\n"
	.string "Champion.\p"
	.string "Wher{SE_M_REVERSAL}wil{SE_M_BATON_PASS}yo{SE_M_DIVE}g{SE_M_ATTRACT2}fro{SE_M_MILK_DRINK}here?\p"
	.string "{SE_M_HEAL_BELL}hop{SE_M_REVERSAL}w{SE_M_REVERSAL}ca{SE_M_ATTRACT}mee{SE_M_SPIT_UP}agai{SE_M_ATTRACT}somewhere.$"

SinjohRuins_Lab_EventScript_Geologist::
	goto_if_ge 20639, 13, SinjohRuins_Lab_EventScript_GeologistAfterEvent
	goto_if_ge 20639, 9, SinjohRuins_Lab_EventScript_GeologistDuringEvent
	msgbox SinjohRuins_Lab_Text_Geologist MSGBOX_NPC
	end

SinjohRuins_Lab_EventScript_GeologistDuringEvent::
	msgbox SinjohRuins_Lab_Text_GeologistDuring, MSGBOX_NPC
	end

SinjohRuins_Lab_EventScript_GeologistAfterEvent::
	msgbox SinjohRuins_Lab_Text_GeologistAfter, MSGBOX_NPC
	end

SinjohRuins_Lab_Text_Geologist:
	.string "Ground-penetratin{SE_M_SANDSTORM}rada{SE_M_SAND_TOMB}shows\n"
	.string "{SE_M_TAIL_WHIP}subterranea{SE_M_ATTRACT}chamber{SE_M_GRASSWHISTLE}i{SE_M_ATTRACT}this\l"
	.string "valley.\p"
	.string "{SE_M_HORN_ATTACK}o{SE_M_ACID_ARMOR}the{SE_M_MILK_DRINK}appea{SE_M_SAND_TOMB}t{SE_M_ATTRACT2}b{SE_M_REVERSAL}closer\n"
	.string "t{SE_M_ATTRACT2}th{SE_M_REVERSAL}surfac{SE_M_REVERSAL}level{SE_M_SUPERSONIC}wit{SE_M_TRI_ATTACK}1\l"
	.string "burie{SE_M_WATERFALL}eve{SE_M_ATTRACT}deeper.$"

SinjohRuins_Lab_Text_GeologistDuring:
	.string "Al{SE_M_BATON_PASS}thi{SE_M_GRASSWHISTLE}tim{SE_M_REVERSAL}I'v{SE_M_REVERSAL}directe{SE_M_WATERFALL}my\n"
	.string "equipmen{SE_M_SPIT_UP}downwar{SE_M_WATERFALL}t{SE_M_ATTRACT2}image\l"
	.string "th{SE_M_REVERSAL}underground.\p"
	.string "Whe{SE_M_ATTRACT}clearl{SE_M_YAWN}{SE_M_HEAL_BELL}should'v{SE_M_REVERSAL}pointed\n"
	.string "i{SE_M_SPIT_UP}up!$"

SinjohRuins_Lab_Text_GeologistAfter:
	.string "Thos{SE_M_REVERSAL}PLATE{SE_M_SKETCH}wer{SE_M_REVERSAL}relate{SE_M_WATERFALL}t{SE_M_ATTRACT2}the\n"
	.string "mos{SE_M_SPIT_UP}powerfu{SE_M_BATON_PASS}POKéMON??\p"
	.string "{SE_M_HEAL_BELL}wis{SE_M_TRI_ATTACK}{SE_M_HEAL_BELL}ha{SE_M_WATERFALL}mor{SE_M_REVERSAL}tim{SE_M_REVERSAL}t{SE_M_ATTRACT2}stud{SE_M_YAWN}them.$"

SinjohRuins_Lab_EventScript_Linguist::
	goto_if_ge 20639, 13, SinjohRuins_Lab_EventScript_LinguistAfterEvent
	goto_if_ge 20639, 9, SinjohRuins_Lab_EventScript_LinguistDuringEvent
	msgbox SinjohRuins_Lab_Text_Linguist MSGBOX_NPC
	end

SinjohRuins_Lab_EventScript_LinguistDuringEvent::
	msgbox SinjohRuins_Lab_Text_LinguistDuring, MSGBOX_NPC
	end

SinjohRuins_Lab_EventScript_LinguistAfterEvent::
	msgbox SinjohRuins_Lab_Text_LinguistAfter, MSGBOX_NPC
	end

SinjohRuins_Lab_Text_Linguist:
	.string "Ugh....\n"
	.string "There'{SE_M_GRASSWHISTLE}s{SE_M_ATTRACT2}man{SE_M_YAWN}glyph{SE_M_GRASSWHISTLE}to\l"
	.string "translate..\p"
	.string "W{SE_M_REVERSAL}don'{SE_M_SPIT_UP}hav{SE_M_REVERSAL}anythin{SE_M_SANDSTORM}lik{SE_M_REVERSAL}this\n"
	.string "i{SE_M_ATTRACT}th{SE_M_REVERSAL}HOEN{SE_M_PSYBEAM2}region.$"

SinjohRuins_Lab_Text_LinguistDuring:
	.string "Imagin{SE_M_REVERSAL}m{SE_M_YAWN}surpris{SE_M_REVERSAL}a{SE_M_GRASSWHISTLE}I\n"
	.string "translate{SE_M_WATERFALL}th{SE_M_REVERSAL}glyph!\p"
	.string "{SE_M_HEAL_BELL}tripl{SE_M_REVERSAL}an{SE_M_WATERFALL}quadrupl{SE_M_REVERSAL}checked\n"
	.string "i{SE_M_SPIT_UP}befor{SE_M_REVERSAL}tellin{SE_M_SANDSTORM}STEVEN!\p"
	.string "{SE_M_HEAL_BELL}mean{SE_M_SUPERSONIC}really{SE_M_SUPERSONIC}th{SE_M_REVERSAL}Go{SE_M_WATERFALL}of\n"
	.string "POKéMON?\p"
	.string "It'{SE_M_GRASSWHISTLE}incredible.$"

SinjohRuins_Lab_Text_LinguistAfter:
	.string "Thi{SE_M_GRASSWHISTLE}expeditio{SE_M_ATTRACT}ha{SE_M_GRASSWHISTLE}bee{SE_M_ATTRACT}a\n"
	.string "joy{SE_M_SUPERSONIC}{PLAYER}.\p"
	.string "Thank{SE_M_GRASSWHISTLE}fo{SE_M_SAND_TOMB}takin{SE_M_SANDSTORM}car{SE_M_REVERSAL}o{SE_M_ACID_ARMOR}all\n"
	.string "th{SE_M_REVERSAL}field-work.$"

SinjohRuins_Lab_EventScript_Archaeologist::
	goto_if_ge 20639, 13, SinjohRuins_Lab_EventScript_ArchaeologistAfterEvent
	goto_if_ge 20639, 9, SinjohRuins_Lab_EventScript_ArchaeologistDuringEvent
	msgbox SinjohRuins_Lab_Text_Archaeologist MSGBOX_NPC
	end

SinjohRuins_Lab_EventScript_ArchaeologistDuringEvent::
	msgbox SinjohRuins_Lab_Text_ArchaeologistDuring, MSGBOX_NPC
	end

SinjohRuins_Lab_EventScript_ArchaeologistAfterEvent::
	msgbox SinjohRuins_Lab_Text_ArchaeologistAfter, MSGBOX_NPC
	end

SinjohRuins_Lab_Text_Archaeologist:
	.string "Th{SE_M_REVERSAL}existenc{SE_M_REVERSAL}o{SE_M_ACID_ARMOR}{SE_M_CHARGE}civilization\n"
	.string "i{SE_M_ATTRACT}thi{SE_M_GRASSWHISTLE}are{SE_M_CHARGE}change{SE_M_GRASSWHISTLE}ou{SE_M_SAND_TOMB}whole\l"
	.string "understandin{SE_M_SANDSTORM}o{SE_M_ACID_ARMOR}history.\p"
	.string "Man{SE_M_YAWN}o{SE_M_ACID_ARMOR}th{SE_M_REVERSAL}artifact{SE_M_GRASSWHISTLE}we'v{SE_M_REVERSAL}found\n"
	.string "ar{SE_M_REVERSAL}ove{SE_M_SAND_TOMB}{SE_M_CHARGE}thousan{SE_M_WATERFALL}year{SE_M_GRASSWHISTLE}old.\p"
	.string "Th{SE_M_REVERSAL}carbo{SE_M_ATTRACT}datin{SE_M_SANDSTORM}line{SE_M_GRASSWHISTLE}u{SE_M_MORNING_SUN}with\n"
	.string "artifact{SE_M_GRASSWHISTLE}foun{SE_M_WATERFALL}i{SE_M_ATTRACT}th{SE_M_REVERSAL}SINNO{SE_M_SWAGGER2}region.\p"
	.string "Although{SE_M_SUPERSONIC}tha{SE_M_SPIT_UP}flut{SE_M_REVERSAL}yo{SE_M_DIVE}found...\n"
	.string "I{SE_M_SPIT_UP}seem{SE_M_GRASSWHISTLE}fa{SE_M_SAND_TOMB}older.$"

SinjohRuins_Lab_Text_ArchaeologistDuring:
	.string "Thos{SE_M_REVERSAL}plates...\n"
	.string "Th{SE_M_REVERSAL}connectio{SE_M_ATTRACT}t{SE_M_ATTRACT2}th{SE_M_REVERSAL}SINNOH\l"
	.string "region...\l"
	.string "Tha{SE_M_SPIT_UP}flute....\l"
	.string "It'{SE_M_GRASSWHISTLE}al{SE_M_BATON_PASS}startin{SE_M_SANDSTORM}t{SE_M_ATTRACT2}mak{SE_M_REVERSAL}sense.$"

SinjohRuins_Lab_Text_ArchaeologistAfter:
	.string "Th{SE_M_REVERSAL}historica{SE_M_BATON_PASS}valu{SE_M_REVERSAL}o{SE_M_ACID_ARMOR}what\n"
	.string "you'v{SE_M_REVERSAL}helpe{SE_M_WATERFALL}u{SE_M_GRASSWHISTLE}uneart{SE_M_TRI_ATTACK}here\l"
	.string "canno{SE_M_SPIT_UP}b{SE_M_REVERSAL}overstated{SE_M_SUPERSONIC}\l"
	.string "{PLAYER}.\p"
	.string "Truly{SE_M_SUPERSONIC}than{SE_M_ENCORE2}you.$"

SinjohRuins_Lab_EventScript_Growlithe_Hisui::
	lock
	faceplayer
	playmoncry 58, 0
	msgbox SinjohRuins_Lab_Text_Growlithe_Cry, MSGBOX_DEFAULT
	waitmoncry
	closemessage
	release
	end

SinjohRuins_Lab_Text_Growlithe_Cry:
	.string "Grow{SE_M_TRI_ATTACK}owh!!$"

SinjohRuins_Lab_EventScript_GrowlithePokeball::
	msgbox SinjohRuins_Lab_Text_GrowlitheBall MSGBOX_SIGN
	end

SinjohRuins_Lab_Text_GrowlitheBall:
	.string "Thi{SE_M_GRASSWHISTLE}appear{SE_M_GRASSWHISTLE}t{SE_M_ATTRACT2}b{SE_M_REVERSAL}Growlithe'{SE_M_GRASSWHISTLE}ball..\n"
	.string "Bette{SE_M_SAND_TOMB}leav{SE_M_REVERSAL}i{SE_M_SPIT_UP}alone.$"

SinjohRuins_Lab_EventScript_Biologist::
	goto_if_ge 20639, 13, SinjohRuins_Lab_EventScript_BiologistAfterEvent
	goto_if_ge 20639, 9, SinjohRuins_Lab_EventScript_BiologistDuringEvent
	msgbox SinjohRuins_Lab_Text_Biologist MSGBOX_NPC
	end

SinjohRuins_Lab_EventScript_BiologistDuringEvent::
	msgbox SinjohRuins_Lab_Text_BiologistDuring, MSGBOX_NPC
	end

SinjohRuins_Lab_EventScript_BiologistAfterEvent::
	msgbox SinjohRuins_Lab_Text_BiologistAfter, MSGBOX_NPC
	end

SinjohRuins_Lab_Text_Biologist:
	.string "Loo{SE_M_ENCORE2}a{SE_M_SPIT_UP}thi{SE_M_GRASSWHISTLE}wonderfu{SE_M_BATON_PASS}specimen!\p"
	.string "Thi{SE_M_GRASSWHISTLE}specie{SE_M_GRASSWHISTLE}o{SE_M_ACID_ARMOR}GROWLITH{SE_M_SWORDS_DANCE}i{SE_M_GRASSWHISTLE}unlike\n"
	.string "thos{SE_M_REVERSAL}foun{SE_M_WATERFALL}anywher{SE_M_REVERSAL}els{SE_M_REVERSAL}i{SE_M_ATTRACT}the\l"
	.string "world.\p"
	.string "DN{SE_M_BONEMERANG}analysi{SE_M_GRASSWHISTLE}reveal{SE_M_GRASSWHISTLE}tha{SE_M_SPIT_UP}i{SE_M_SPIT_UP}shares\n"
	.string "{SE_M_CHARGE}commo{SE_M_ATTRACT}ancesto{SE_M_SAND_TOMB}wit{SE_M_TRI_ATTACK}GROWLITHE\l"
	.string "foun{SE_M_WATERFALL}i{SE_M_ATTRACT}othe{SE_M_SAND_TOMB}regions.\p"
	.string "Yet{SE_M_SUPERSONIC}it{SE_M_GRASSWHISTLE}temperamen{SE_M_SPIT_UP}an{SE_M_WATERFALL}typing\n"
	.string "diffe{SE_M_SAND_TOMB}significantly.\p"
	.string "Description{SE_M_GRASSWHISTLE}o{SE_M_ACID_ARMOR}GROWLITH{SE_M_SWORDS_DANCE}foun{SE_M_WATERFALL}in\n"
	.string "ancien{SE_M_SPIT_UP}SINNO{SE_M_SWAGGER2}record{SE_M_GRASSWHISTLE}see{SE_M_MILK_DRINK}t{SE_M_ATTRACT2}match.\p"
	.string "Perhap{SE_M_GRASSWHISTLE}thi{SE_M_GRASSWHISTLE}specie{SE_M_GRASSWHISTLE}onc{SE_M_REVERSAL}occupied\n"
	.string "{SE_M_CHARGE}muc{SE_M_TRI_ATTACK}large{SE_M_SAND_TOMB}territory{SE_M_SUPERSONIC}stretching\l"
	.string "nort{SE_M_TRI_ATTACK}throug{SE_M_TRI_ATTACK}ancien{SE_M_SPIT_UP}SINNOH.$"

SinjohRuins_Lab_Text_BiologistDuring:
	.string "I{SE_M_ACID_ARMOR}th{SE_M_REVERSAL}creatur{SE_M_REVERSAL}a{SE_M_SPIT_UP}th{SE_M_REVERSAL}to{SE_M_MORNING_SUN}of\n"
	.string "thos{SE_M_REVERSAL}stair{SE_M_GRASSWHISTLE}reall{SE_M_YAWN}i{SE_M_GRASSWHISTLE}th{SE_M_REVERSAL}God\l"
	.string "o{SE_M_ACID_ARMOR}al{SE_M_BATON_PASS}POKéMON{SE_M_SUPERSONIC}doe{SE_M_GRASSWHISTLE}tha{SE_M_SPIT_UP}mean\l"
	.string "i{SE_M_SPIT_UP}i{SE_M_GRASSWHISTLE}th{SE_M_REVERSAL}firs{SE_M_SPIT_UP}commo{SE_M_ATTRACT}ancestor?$"

SinjohRuins_Lab_Text_BiologistAfter:
	.string "I'v{SE_M_REVERSAL}bee{SE_M_ATTRACT}abl{SE_M_REVERSAL}t{SE_M_ATTRACT2}gathe{SE_M_SAND_TOMB}s{SE_M_ATTRACT2}much\n"
	.string "dat{SE_M_CHARGE}o{SE_M_ATTRACT}regiona{SE_M_BATON_PASS}form{SE_M_GRASSWHISTLE}and\l"
	.string "divergen{SE_M_SPIT_UP}evolutio{SE_M_ATTRACT}fro{SE_M_MILK_DRINK}this\l"
	.string "expedition{SE_M_PERISH_SONG}Than{SE_M_ENCORE2}you,\l"
	.string "{PLAYER}.$"

SinjohRuins_Lab_EventScript_Hiker::
	goto_if_ge 20639, 9, SinjohRuins_Lab_EventScript_HikerDuringAfter
	msgbox SinjohRuins_Lab_Text_Hiker MSGBOX_NPC
	end

SinjohRuins_Lab_EventScript_HikerDuringAfter::
	msgbox SinjohRuins_Lab_Text_HikerDuringAfter, MSGBOX_NPC
	end

SinjohRuins_Lab_Text_Hiker:
	.string "Fo{SE_M_SAND_TOMB}te{SE_M_ATTRACT}years{SE_M_SUPERSONIC}I'v{SE_M_REVERSAL}hike{SE_M_WATERFALL}these\n"
	.string "wilds.\p"
	.string "No{SE_M_SUPERSONIC}mak{SE_M_REVERSAL}tha{SE_M_SPIT_UP}twent{SE_M_YAWN}years.\p"
	.string "Unti{SE_M_BATON_PASS}on{SE_M_REVERSAL}da{SE_M_YAWN}{SE_M_HEAL_BELL}foun{SE_M_WATERFALL}thos{SE_M_REVERSAL}big\n"
	.string "ston{SE_M_REVERSAL}pillar{SE_M_GRASSWHISTLE}an{SE_M_WATERFALL}tha{SE_M_SPIT_UP}ominous\l"
	.string "temple.\p"
	.string "That'{SE_M_GRASSWHISTLE}th{SE_M_REVERSAL}SINJO{SE_M_SWAGGER2}RUINS.\n"
	.string "O{SE_M_SAND_TOMB}s{SE_M_ATTRACT2}I'v{SE_M_REVERSAL}heard.\p"
	.string "{SE_M_HEAL_BELL}didn'{SE_M_SPIT_UP}kno{SE_M_TWISTER}abou{SE_M_SPIT_UP}th{SE_M_REVERSAL}tow{SE_M_ATTRACT}then.\p"
	.string "Al{SE_M_BATON_PASS}{SE_M_HEAL_BELL}di{SE_M_WATERFALL}wa{SE_M_GRASSWHISTLE}tel{SE_M_BATON_PASS}{SE_M_CHARGE}fe{SE_M_TWISTER}o{SE_M_ACID_ARMOR}my\n"
	.string "pals{SE_M_PERISH_SONG}Bu{SE_M_SPIT_UP}wor{SE_M_WATERFALL}travel{SE_M_GRASSWHISTLE}fast.\p"
	.string "{SE_M_HEAL_BELL}neve{SE_M_SAND_TOMB}though{SE_M_SPIT_UP}i{SE_M_SPIT_UP}woul{SE_M_WATERFALL}bring\n"
	.string "s{SE_M_ATTRACT2}muc{SE_M_TRI_ATTACK}attentio{SE_M_ATTRACT}t{SE_M_ATTRACT2}th{SE_M_REVERSAL}area.\p"
	.string "Make{SE_M_GRASSWHISTLE}m{SE_M_REVERSAL}fee{SE_M_BATON_PASS}kind{SE_M_CHARGE}funny.\n"
	.string "Y'know?$"

SinjohRuins_Lab_Text_HikerDuringAfter:
	.string "Don'{SE_M_SPIT_UP}tel{SE_M_BATON_PASS}anyone{SE_M_SUPERSONIC}{PLAYER},\n"
	.string "Bu{SE_M_SPIT_UP}{SE_M_HEAL_BELL}sa{SE_M_TWISTER}tha{SE_M_SPIT_UP}templ{SE_M_REVERSAL}on\l"
	.string "th{SE_M_REVERSAL}mountainto{SE_M_MORNING_SUN}whe{SE_M_ATTRACT}{SE_M_HEAL_BELL}first\l"
	.string "discovere{SE_M_WATERFALL}thi{SE_M_GRASSWHISTLE}place.\p"
	.string "{SE_M_HEAL_BELL}kep{SE_M_SPIT_UP}i{SE_M_SPIT_UP}t{SE_M_ATTRACT2}myself.\p"
	.string "I'v{SE_M_REVERSAL}blabbe{SE_M_WATERFALL}enoug{SE_M_TRI_ATTACK}about\n"
	.string "thes{SE_M_REVERSAL}ruins.\p"
	.string "I{SE_M_SPIT_UP}seem{SE_M_GRASSWHISTLE}lik{SE_M_REVERSAL}everythin{SE_M_SANDSTORM}worked\n"
	.string "out{SE_M_SUPERSONIC}a{SE_M_SPIT_UP}least.$"

SinjohRuins_Lab_EventScript_Notes1::
	msgbox SinjohRuins_Lab_Text_Note1 MSGBOX_SIGN
	end

SinjohRuins_Lab_EventScript_Notes2::
	msgbox SinjohRuins_Lab_Text_Note2 MSGBOX_SIGN
	end

SinjohRuins_Lab_EventScript_Notes3::
	msgbox SinjohRuins_Lab_Text_Note3 MSGBOX_SIGN
	end

SinjohRuins_Lab_EventScript_Notes4::
	msgbox SinjohRuins_Lab_Text_Note4 MSGBOX_SIGN
	end

SinjohRuins_Lab_EventScript_Notes5::
	msgbox SinjohRuins_Lab_Text_Note5 MSGBOX_SIGN
	end

SinjohRuins_Lab_EventScript_Notes6::
	msgbox SinjohRuins_Lab_Text_Note6 MSGBOX_SIGN
	end

SinjohRuins_Lab_EventScript_Notes7::
	msgbox SinjohRuins_Lab_Text_Note7 MSGBOX_SIGN
	end

SinjohRuins_Lab_EventScript_Notes8::
	msgbox SinjohRuins_Lab_Text_Note8 MSGBOX_SIGN
	end

SinjohRuins_Lab_Text_Note1:
	.string "Researc{SE_M_TRI_ATTACK}Lo{SE_M_SANDSTORM}1{SE_M_HEAT_WAVE}Ma{SE_M_YAWN}3{SE_M_SUPERSONIC}1975\p"
	.string "We'v{SE_M_REVERSAL}arrive{SE_M_WATERFALL}a{SE_M_SPIT_UP}th{SE_M_REVERSAL}location\n"
	.string "o{SE_M_ACID_ARMOR}th{SE_M_REVERSAL}ruins.\p"
	.string "Th{SE_M_REVERSAL}hars{SE_M_TRI_ATTACK}col{SE_M_WATERFALL}o{SE_M_ACID_ARMOR}Mt.Silver\n"
	.string "ca{SE_M_ATTRACT}b{SE_M_REVERSAL}fel{SE_M_SPIT_UP}fro{SE_M_MILK_DRINK}al{SE_M_BATON_PASS}th{SE_M_REVERSAL}way\l"
	.string "dow{SE_M_ATTRACT}here...\p"
	.string "Soo{SE_M_ATTRACT}th{SE_M_REVERSAL}mai{SE_M_ATTRACT}excavatio{SE_M_ATTRACT}team\n"
	.string "wil{SE_M_BATON_PASS}mak{SE_M_REVERSAL}i{SE_M_SPIT_UP}throug{SE_M_TRI_ATTACK}th{SE_M_REVERSAL}mountain..\l"
	.string "{SE_M_HEAL_BELL}canno{SE_M_SPIT_UP}wai{SE_M_SPIT_UP}t{SE_M_ATTRACT2}se{SE_M_REVERSAL}wha{SE_M_SPIT_UP}wait{SE_M_GRASSWHISTLE}fo{SE_M_SAND_TOMB}us\l"
	.string "underneat{SE_M_TRI_ATTACK}ou{SE_M_SAND_TOMB}feet!$"

SinjohRuins_Lab_Text_Note2:
	.string "Researc{SE_M_TRI_ATTACK}Lo{SE_M_SANDSTORM}2{SE_M_HEAT_WAVE} Ma{SE_M_YAWN}10{SE_M_SUPERSONIC}1975\p"
	.string "{SE_M_BONEMERANG}wee{SE_M_ENCORE2}o{SE_M_ACID_ARMOR}diggin{SE_M_SANDSTORM}ha{SE_M_GRASSWHISTLE}yielded\n"
	.string "n{SE_M_ATTRACT2}resul{SE_M_SPIT_UP}whatsoever.\p"
	.string "Th{SE_M_REVERSAL}ic{SE_M_REVERSAL}her{SE_M_REVERSAL}i{SE_M_GRASSWHISTLE}impossibl{SE_M_YAWN}thick,\n"
	.string "an{SE_M_WATERFALL}th{SE_M_REVERSAL}roc{SE_M_ENCORE2}jus{SE_M_SPIT_UP}break{SE_M_GRASSWHISTLE}our\l"
	.string "equipmen{SE_M_SPIT_UP}entirely.\p"
	.string "No{SE_M_SPIT_UP}eve{SE_M_ATTRACT}MACHAM{SE_M_PETAL_DANCE}wa{SE_M_GRASSWHISTLE}abl{SE_M_REVERSAL}to\n"
	.string "mak{SE_M_REVERSAL}{SE_M_CHARGE}dent.\p"
	.string "Wha{SE_M_SPIT_UP}i{SE_M_GRASSWHISTLE}thi{SE_M_GRASSWHISTLE}place?\p"
	.string "W{SE_M_REVERSAL}mus{SE_M_SPIT_UP}fin{SE_M_WATERFALL}out.$"

SinjohRuins_Lab_Text_Note3:
	.string "Researc{SE_M_TRI_ATTACK}Lo{SE_M_SANDSTORM}3{SE_M_HEAT_WAVE} Ma{SE_M_YAWN}14{SE_M_SUPERSONIC}1975\p"
	.string "Yo{SE_M_DIVE}don'{SE_M_SPIT_UP}ge{SE_M_SPIT_UP}ahea{SE_M_WATERFALL}i{SE_M_ATTRACT}lif{SE_M_REVERSAL}by\n"
	.string "standin{SE_M_SANDSTORM}b{SE_M_YAWN}an{SE_M_WATERFALL}doin{SE_M_SANDSTORM}nothing.\p"
	.string "I'{SE_M_MILK_DRINK}jus{SE_M_SPIT_UP}{SE_M_CHARGE}worker.\p"
	.string "Bu{SE_M_SPIT_UP}{SE_M_HEAL_BELL}ha{SE_M_WATERFALL}a{SE_M_ATTRACT}ide{SE_M_CHARGE}o{SE_M_ACID_ARMOR}ho{SE_M_TWISTER}w{SE_M_REVERSAL}could\n"
	.string "brea{SE_M_ENCORE2}throug{SE_M_TRI_ATTACK}th{SE_M_REVERSAL}ice.\p"
	.string "O{SE_M_SAND_TOMB}rather{SE_M_SUPERSONIC}mel{SE_M_SPIT_UP}throug{SE_M_TRI_ATTACK}it.\p"
	.string "W{SE_M_REVERSAL}nee{SE_M_WATERFALL}FIRE-TYP{SE_M_SWORDS_DANCE}POKéMO{SE_M_PSYBEAM2}and\n"
	.string "lot{SE_M_GRASSWHISTLE}o{SE_M_ACID_ARMOR}them.\p"
	.string "Bu{SE_M_SPIT_UP}ho{SE_M_TWISTER}wil{SE_M_BATON_PASS}w{SE_M_REVERSAL}ge{SE_M_SPIT_UP}the{SE_M_MILK_DRINK}here\n"
	.string "al{SE_M_BATON_PASS}th{SE_M_REVERSAL}wa{SE_M_YAWN}fro{SE_M_MILK_DRINK}SINNOH?$"

SinjohRuins_Lab_Text_Note4:
	.string "Researc{SE_M_TRI_ATTACK}Lo{SE_M_SANDSTORM}4{SE_M_HEAT_WAVE} Ma{SE_M_YAWN}21{SE_M_SUPERSONIC}1975\p"
	.string "We'v{SE_M_REVERSAL}bee{SE_M_ATTRACT}busy.\p"
	.string "M{SE_M_YAWN}ide{SE_M_CHARGE}worke{SE_M_WATERFALL}t{SE_M_ATTRACT2}ge{SE_M_SPIT_UP}u{SE_M_GRASSWHISTLE}through\n"
	.string "th{SE_M_REVERSAL}ice{SE_M_PERISH_SONG}Onl{SE_M_YAWN}w{SE_M_REVERSAL}didn'{SE_M_SPIT_UP}ge{SE_M_SPIT_UP}the\l"
	.string "FIRE-TYPE{SE_M_GRASSWHISTLE}fro{SE_M_MILK_DRINK}bac{SE_M_ENCORE2}home.\p"
	.string "Th{SE_M_REVERSAL}bos{SE_M_GRASSWHISTLE}insiste{SE_M_WATERFALL}w{SE_M_REVERSAL}ge{SE_M_SPIT_UP}the{SE_M_MILK_DRINK}locally.\p"
	.string "W{SE_M_REVERSAL}foun{SE_M_WATERFALL}{SE_M_CHARGE}ho{SE_M_SPIT_UP}sprin{SE_M_SANDSTORM}b{SE_M_YAWN}{SE_M_CHARGE}nearby\n"
	.string "village....\p"
	.string "An{SE_M_WATERFALL}w{SE_M_REVERSAL}too{SE_M_ENCORE2}wha{SE_M_SPIT_UP}w{SE_M_REVERSAL}needed...\p"
	.string "I'{SE_M_MILK_DRINK}no{SE_M_SPIT_UP}prou{SE_M_WATERFALL}o{SE_M_ACID_ARMOR}it{SE_M_PERISH_SONG}Bu{SE_M_SPIT_UP}sacrifices\n"
	.string "ar{SE_M_REVERSAL}sometime{SE_M_GRASSWHISTLE}require{SE_M_WATERFALL}fo{SE_M_SAND_TOMB}progress.\p"
	.string "So{SE_M_SUPERSONIC}th{SE_M_REVERSAL}ic{SE_M_REVERSAL}i{SE_M_GRASSWHISTLE}gone.\p"
	.string "Ther{SE_M_REVERSAL}ar{SE_M_REVERSAL}{SE_M_TAIL_WHIP}chambers{SE_M_SUPERSONIC}an{SE_M_WATERFALL}{SE_M_CHARGE}sealed\n"
	.string "templ{SE_M_REVERSAL}i{SE_M_ATTRACT}th{SE_M_REVERSAL}center.\p"
	.string "Th{SE_M_REVERSAL}architectur{SE_M_REVERSAL}o{SE_M_ACID_ARMOR}th{SE_M_REVERSAL}mai{SE_M_ATTRACT}\n"
	.string "structur{SE_M_REVERSAL}indicate{SE_M_GRASSWHISTLE}i{SE_M_SPIT_UP}ma{SE_M_YAWN}b{SE_M_REVERSAL}o{SE_M_ACID_ARMOR}the\l"
	.string "th{SE_M_REVERSAL}ancien{SE_M_SPIT_UP}Celestic{SE_M_CHARGE}peoples...\p"
	.string "Ou{SE_M_SAND_TOMB}ancestors{SE_M_PERISH_SONG}Befor{SE_M_REVERSAL}the{SE_M_YAWN}move{SE_M_WATERFALL}north.\p"
	.string "Th{SE_M_REVERSAL}bos{SE_M_GRASSWHISTLE}want{SE_M_GRASSWHISTLE}tha{SE_M_SPIT_UP}templ{SE_M_REVERSAL}ope{SE_M_ATTRACT}as\n"
	.string "soo{SE_M_ATTRACT}a{SE_M_GRASSWHISTLE}possible...$"

SinjohRuins_Lab_Text_Note5:
	.string "Researc{SE_M_TRI_ATTACK}Lo{SE_M_SANDSTORM}5{SE_M_HEAT_WAVE} Jun{SE_M_REVERSAL}2{SE_M_SUPERSONIC}1975\p"
	.string "W{SE_M_REVERSAL}manage{SE_M_WATERFALL}t{SE_M_ATTRACT2}ge{SE_M_SPIT_UP}i{SE_M_SPIT_UP}open...\p"
	.string "{SE_M_HEAL_BELL}though{SE_M_SPIT_UP}I'{SE_M_WATERFALL}b{SE_M_REVERSAL}overjoyed...\p"
	.string "Bu{SE_M_SPIT_UP}w{SE_M_REVERSAL}los{SE_M_SPIT_UP}goo{SE_M_WATERFALL}me{SE_M_ATTRACT}i{SE_M_ATTRACT}th{SE_M_REVERSAL}blast\n"
	.string "o{SE_M_ACID_ARMOR}energ{SE_M_YAWN}tha{SE_M_SPIT_UP}sprun{SE_M_SANDSTORM}fro{SE_M_MILK_DRINK}the\l"
	.string "temple.\p"
	.string "No{SE_M_SPIT_UP}t{SE_M_ATTRACT2}mentio{SE_M_ATTRACT}th{SE_M_REVERSAL}POKéMO{SE_M_PSYBEAM2}that\n"
	.string "helpe{SE_M_WATERFALL}u{SE_M_GRASSWHISTLE}ge{SE_M_SPIT_UP}i{SE_M_SPIT_UP}open.\l"
	.string "Go{SE_M_WATERFALL}res{SE_M_SPIT_UP}thei{SE_M_SAND_TOMB}souls...\p"
	.string "........................\p"
	.string "Regardless.\p"
	.string "Th{SE_M_REVERSAL}templ{SE_M_REVERSAL}i{SE_M_GRASSWHISTLE}open{SE_M_SUPERSONIC}bu{SE_M_SPIT_UP}w{SE_M_REVERSAL}are\n"
	.string "onl{SE_M_YAWN}lef{SE_M_SPIT_UP}wit{SE_M_TRI_ATTACK}mor{SE_M_REVERSAL}questions.\p"
	.string "Ther{SE_M_REVERSAL}i{SE_M_GRASSWHISTLE}n{SE_M_ATTRACT2}legendar{SE_M_YAWN}POKéMON\n"
	.string "inside{SE_M_PERISH_SONG}N{SE_M_ATTRACT2}treasure.\p"
	.string "Ou{SE_M_SAND_TOMB}supplie{SE_M_GRASSWHISTLE}ar{SE_M_REVERSAL}startin{SE_M_SANDSTORM}t{SE_M_ATTRACT2}run\n"
	.string "ou{SE_M_SPIT_UP}an{SE_M_WATERFALL}w{SE_M_REVERSAL}hav{SE_M_REVERSAL}nothin{SE_M_SANDSTORM}t{SE_M_ATTRACT2}show\l"
	.string "fo{SE_M_SAND_TOMB}ou{SE_M_SAND_TOMB}efforts...$"

SinjohRuins_Lab_Text_Note6:
	.string "Researc{SE_M_TRI_ATTACK}Lo{SE_M_SANDSTORM}6{SE_M_HEAT_WAVE} Jun{SE_M_REVERSAL}10{SE_M_SUPERSONIC}1975\p"
	.string "Th{SE_M_REVERSAL}expeditio{SE_M_ATTRACT}i{SE_M_GRASSWHISTLE}done.\n"
	.string "Th{SE_M_REVERSAL}res{SE_M_SPIT_UP}o{SE_M_ACID_ARMOR}th{SE_M_REVERSAL}me{SE_M_ATTRACT}ar{SE_M_REVERSAL}packin{SE_M_SANDSTORM}up.\p"
	.string "Bu{SE_M_SPIT_UP}{SE_M_HEAL_BELL}can't.\p"
	.string "{SE_M_HEAL_BELL}can'{SE_M_SPIT_UP}abando{SE_M_ATTRACT}thi{SE_M_GRASSWHISTLE}mission.\n"
	.string "No{SE_M_SPIT_UP}afte{SE_M_SAND_TOMB}wha{SE_M_SPIT_UP}we'v{SE_M_REVERSAL}lost.\p"
	.string "I'{SE_M_MILK_DRINK}goin{SE_M_SANDSTORM}t{SE_M_ATTRACT2}sta{SE_M_YAWN}behind.$"

SinjohRuins_Lab_Text_Note7:
	.string "Researc{SE_M_TRI_ATTACK}Lo{SE_M_SANDSTORM}7{SE_M_HEAT_WAVE} Septembe{SE_M_SAND_TOMB}10{SE_M_SUPERSONIC}1975\p"
	.string "It'{SE_M_GRASSWHISTLE}bee{SE_M_ATTRACT}month{SE_M_GRASSWHISTLE}sinc{SE_M_REVERSAL}w{SE_M_REVERSAL}got\n"
	.string "here{SE_M_PERISH_SONG}Sinc{SE_M_REVERSAL}{SE_M_HEAL_BELL}go{SE_M_SPIT_UP}here.\p"
	.string "Th{SE_M_REVERSAL}res{SE_M_SPIT_UP}o{SE_M_ACID_ARMOR}th{SE_M_REVERSAL}me{SE_M_ATTRACT}ar{SE_M_REVERSAL}gone.\p"
	.string "No{SE_M_TWISTER}it'{SE_M_GRASSWHISTLE}jus{SE_M_SPIT_UP}m{SE_M_REVERSAL}an{SE_M_WATERFALL}the\n"
	.string "POKéMO{SE_M_PSYBEAM2}w{SE_M_REVERSAL}capture{SE_M_WATERFALL}t{SE_M_ATTRACT2}hel{SE_M_MORNING_SUN}us\l"
	.string "wit{SE_M_TRI_ATTACK}th{SE_M_REVERSAL}work.\p"
	.string "I'v{SE_M_REVERSAL}bee{SE_M_ATTRACT}trainin{SE_M_SANDSTORM}the{SE_M_MILK_DRINK}t{SE_M_ATTRACT2}get\n"
	.string "stronger.\p"
	.string "M{SE_M_YAWN}TYPHLOSION{SE_M_SUPERSONIC}mos{SE_M_SPIT_UP}o{SE_M_ACID_ARMOR}all.\p"
	.string "W{SE_M_REVERSAL}mus{SE_M_SPIT_UP}fin{SE_M_WATERFALL}ou{SE_M_SPIT_UP}what'{SE_M_GRASSWHISTLE}beneath\n"
	.string "th{SE_M_REVERSAL}temple.$"

SinjohRuins_Lab_Text_Note8:
	.string "Researc{SE_M_TRI_ATTACK}Lo{SE_M_SANDSTORM}8{SE_M_HEAT_WAVE} Septembe{SE_M_SAND_TOMB}15{SE_M_SUPERSONIC}1975\p"
	.string "Failure.\p"
	.string "......................\p"
	.string "M{SE_M_YAWN}POKéMON....\p"
	.string "Together{SE_M_SUPERSONIC}al{SE_M_BATON_PASS}{SE_M_TAIL_WHIP}o{SE_M_ACID_ARMOR}m{SE_M_YAWN}POKéMON\n"
	.string "wer{SE_M_REVERSAL}abl{SE_M_REVERSAL}t{SE_M_ATTRACT2}smas{SE_M_TRI_ATTACK}through\n"
	.string "{SE_M_BONEMERANG}fals{SE_M_REVERSAL}wal{SE_M_BATON_PASS}i{SE_M_ATTRACT}th{SE_M_REVERSAL}temple.\p"
	.string "Bu{SE_M_SPIT_UP}i{SE_M_SPIT_UP}wa{SE_M_GRASSWHISTLE}waitin{SE_M_SANDSTORM}fo{SE_M_SAND_TOMB}us...\p"
	.string "Somethin{SE_M_SANDSTORM}lik{SE_M_REVERSAL}{SE_M_CHARGE}gian{SE_M_SPIT_UP}titan...\p"
	.string "Th{SE_M_REVERSAL}energ{SE_M_YAWN}i{SE_M_SPIT_UP}release{SE_M_WATERFALL}wa{SE_M_GRASSWHISTLE}just\n"
	.string "lik{SE_M_REVERSAL}wha{SE_M_SPIT_UP}happene{SE_M_WATERFALL}before.\p"
	.string "The{SE_M_YAWN}wer{SE_M_REVERSAL}al{SE_M_BATON_PASS}destroyed...\p"
	.string "An{SE_M_WATERFALL}wors{SE_M_SPIT_UP}o{SE_M_ACID_ARMOR}all{SE_M_SUPERSONIC}tha{SE_M_SPIT_UP}beast\n"
	.string "seale{SE_M_WATERFALL}th{SE_M_REVERSAL}wal{SE_M_BATON_PASS}bac{SE_M_ENCORE2}up.\p"
	.string "{SE_M_HEAL_BELL}can'{SE_M_SPIT_UP}g{SE_M_ATTRACT2}home.\n"
	.string "The{SE_M_YAWN}won'{SE_M_SPIT_UP}recogniz{SE_M_REVERSAL}m{SE_M_REVERSAL}anymore...\p"
	.string "Thi{SE_M_GRASSWHISTLE}plac{SE_M_REVERSAL}ha{SE_M_GRASSWHISTLE}change{SE_M_WATERFALL}me...\p"
	.string "I'{SE_M_MILK_DRINK}goin{SE_M_SANDSTORM}t{SE_M_ATTRACT2}tal{SE_M_ENCORE2}wit{SE_M_TRI_ATTACK}the\n"
	.string "villagers.\p"
	.string "The{SE_M_YAWN}don'{SE_M_SPIT_UP}kno{SE_M_TWISTER}wha{SE_M_SPIT_UP}I'v{SE_M_REVERSAL}done.\p"
	.string "Sinc{SE_M_REVERSAL}th{SE_M_REVERSAL}othe{SE_M_SAND_TOMB}me{SE_M_ATTRACT}ar{SE_M_REVERSAL}long\n"
	.string "gone{SE_M_SUPERSONIC}they'l{SE_M_BATON_PASS}thin{SE_M_ENCORE2}I'{SE_M_MILK_DRINK}jus{SE_M_SPIT_UP}a\l"
	.string "los{SE_M_SPIT_UP}hiker.\p"
	.string "Ther{SE_M_REVERSAL}i{SE_M_GRASSWHISTLE}n{SE_M_ATTRACT2}plac{SE_M_REVERSAL}lef{SE_M_SPIT_UP}fo{SE_M_SAND_TOMB}me\n"
	.string "bu{SE_M_SPIT_UP}here.$"

SinjohRuins_EventScript_DisplayCase::
	lock
	msgbox SinjohRuins_DisplayCase_Text MSGBOX_DEFAULT
	release
	end

SinjohRuins_DisplayCase_Text:
	.string "It'{SE_M_GRASSWHISTLE}{SE_M_CHARGE}displa{SE_M_YAWN}cas{SE_M_REVERSAL}neatly\n"
	.string "packe{SE_M_WATERFALL}an{SE_M_WATERFALL}line{SE_M_WATERFALL}wit{SE_M_TRI_ATTACK}samples\l"
	.string "an{SE_M_WATERFALL}artifacts!$"

SinjohRuins_EventScript_WallSign::
	lock
	msgbox SinjohRuins_WallSign_Text MSGBOX_DEFAULT
	release
	end

SinjohRuins_WallSign_Text:
	.string "Xra{SE_M_YAWN}an{SE_M_WATERFALL}printin{SE_M_SANDSTORM}lab.$"

SinjohRuins_EventScript_Artifact::
	lock
	msgbox SinjohRuins_Artifact_Text MSGBOX_DEFAULT
	release
	end

SinjohRuins_Artifact_Text:
	.string "It'{SE_M_GRASSWHISTLE}a{SE_M_ATTRACT}artifac{SE_M_SPIT_UP}foun{SE_M_WATERFALL}from\n"
	.string "insid{SE_M_REVERSAL}th{SE_M_REVERSAL}ruins!$"

SinjohRuins_Lab_EventScript_NoOp::
	release
	end

SinjohRuins_Lab_Text_PlayFlute:
	.string "Th{SE_M_REVERSAL}AZUR{SE_M_SWORDS_DANCE}FLUT{SE_M_SWORDS_DANCE}i{SE_M_GRASSWHISTLE}reacting.\n"
	.string "Pla{SE_M_YAWN}th{SE_M_REVERSAL}flute?$"

SinjohRuins_Lab_Text_DropedItem:
	.string "Th{SE_M_REVERSAL}NOBL{SE_M_SWORDS_DANCE}{STR_VAR_1} dropped\n"
	.string "a{SE_M_ATTRACT}item...$"

SinjohRuins_Lab_Text_StevenName:
	.string "STEVEN$"

SinjohRuins_Lab_EventScript_3Plates::
	setspeaker SinjohRuins_Lab_Text_StevenName
	pokenavcall SinjohRuins_Lab_Text_StevenCall3Plates
	waitmessage
	delay 30
	return

SinjohRuins_Lab_EventScript_6Plates::
	setspeaker SinjohRuins_Lab_Text_StevenName
	pokenavcall SinjohRuins_Lab_Text_StevenCall6Plates
	waitmessage
	delay 30
	return

SinjohRuins_Lab_EventScript_9Plates::
	setspeaker SinjohRuins_Lab_Text_StevenName
	pokenavcall SinjohRuins_Lab_Text_StevenCall9Plates
	waitmessage
	delay 30
	return

SinjohRuins_Lab_EventScript_12Plates::
	setspeaker SinjohRuins_Lab_Text_StevenName
	pokenavcall SinjohRuins_Lab_Text_StevenCall12Plates
	waitmessage
	delay 30
	return

SinjohRuins_Lab_EventScript_15Plates::
	setspeaker SinjohRuins_Lab_Text_StevenName
	pokenavcall SinjohRuins_Lab_Text_StevenCall15Plates
	waitmessage
	delay 30
	return

SinjohRuins_Lab_EventScript_16Plates::
	setspeaker SinjohRuins_Lab_Text_StevenName
	pokenavcall SinjohRuins_Lab_Text_StevenCall16Plates
	waitmessage
	delay 30
	setvar 20639, 7
	return

SinjohRuins_Lab_Text_StevenCall3Plates:
	.string "STEVEN{SE_M_HEAT_WAVE}{PLAYER}.\p"
	.string "W{SE_M_REVERSAL}fel{SE_M_SPIT_UP}{SE_M_CHARGE}tremo{SE_M_SAND_TOMB}a{SE_M_SPIT_UP}th{SE_M_REVERSAL}ruins\n"
	.string "jus{SE_M_SPIT_UP}now.\p"
	.string "Everyone'{SE_M_GRASSWHISTLE}fine{SE_M_SUPERSONIC}don'{SE_M_SPIT_UP}worry.\p"
	.string "It'{SE_M_GRASSWHISTLE}quit{SE_M_REVERSAL}intriguing{SE_M_SUPERSONIC}on{SE_M_REVERSAL}o{SE_M_ACID_ARMOR}the\n"
	.string "subterranea{SE_M_ATTRACT}chamber{SE_M_GRASSWHISTLE}beneat{SE_M_TRI_ATTACK}the\l"
	.string "ruin{SE_M_GRASSWHISTLE}ha{SE_M_GRASSWHISTLE}sprun{SE_M_SANDSTORM}open.\p"
	.string "Th{SE_M_REVERSAL}marking{SE_M_GRASSWHISTLE}insid{SE_M_REVERSAL}remind\n"
	.string "m{SE_M_REVERSAL}o{SE_M_ACID_ARMOR}somethin{SE_M_SANDSTORM}fro{SE_M_MILK_DRINK}HOENN.\p"
	.string "Yo{SE_M_DIVE}shoul{SE_M_WATERFALL}com{SE_M_REVERSAL}tak{SE_M_REVERSAL}{SE_M_CHARGE}look\n"
	.string "whe{SE_M_ATTRACT}yo{SE_M_DIVE}can.$"

SinjohRuins_Lab_Text_StevenCall6Plates:
	.string "STEVEN{SE_M_HEAT_WAVE}{PLAYER}.\p"
	.string "How'{SE_M_GRASSWHISTLE}th{SE_M_REVERSAL}searc{SE_M_TRI_ATTACK}going?\p"
	.string "W{SE_M_REVERSAL}ha{SE_M_WATERFALL}anothe{SE_M_SAND_TOMB}tremo{SE_M_SAND_TOMB}here.\n"
	.string "{SE_M_BONEMERANG}secon{SE_M_WATERFALL}chambe{SE_M_SAND_TOMB}opene{SE_M_WATERFALL}up\l"
	.string "thi{SE_M_GRASSWHISTLE}time.\p"
	.string "I'v{SE_M_REVERSAL}aske{SE_M_WATERFALL}ou{SE_M_SAND_TOMB}geologis{SE_M_SPIT_UP}t{SE_M_ATTRACT2}keep\n"
	.string "hi{SE_M_GRASSWHISTLE}instrument{SE_M_GRASSWHISTLE}read{SE_M_YAWN}i{SE_M_ATTRACT}cas{SE_M_REVERSAL}it\l"
	.string "happen{SE_M_GRASSWHISTLE}again.\p"
	.string "Th{SE_M_REVERSAL}deepe{SE_M_SAND_TOMB}w{SE_M_REVERSAL}dig..{SE_M_PERISH_SONG}Th{SE_M_REVERSAL}more\n"
	.string "question{SE_M_GRASSWHISTLE}w{SE_M_REVERSAL}find.$"

SinjohRuins_Lab_Text_StevenCall9Plates:
	.string "STEVEN{SE_M_HEAT_WAVE}{PLAYER}.\p"
	.string "Anothe{SE_M_SAND_TOMB}tremo{SE_M_SAND_TOMB}her{SE_M_REVERSAL}a{SE_M_SPIT_UP}th{SE_M_REVERSAL}ruins.\p"
	.string "Th{SE_M_REVERSAL}dat{SE_M_CHARGE}paint{SE_M_GRASSWHISTLE}a{SE_M_ATTRACT}intriguing\n"
	.string "picture.\p"
	.string "I{SE_M_SPIT_UP}wasn'{SE_M_SPIT_UP}a{SE_M_ATTRACT}earthquak{SE_M_REVERSAL}a{SE_M_SPIT_UP}all.\p"
	.string "Som{SE_M_REVERSAL}kin{SE_M_WATERFALL}o{SE_M_ACID_ARMOR}energ{SE_M_YAWN}buil{SE_M_SPIT_UP}up\n"
	.string "undergroun{SE_M_WATERFALL}an{SE_M_WATERFALL}cracke{SE_M_WATERFALL}the\l"
	.string "roc{SE_M_ENCORE2}ope{SE_M_ATTRACT}fro{SE_M_MILK_DRINK}th{SE_M_REVERSAL}inside.\p"
	.string "Wha{SE_M_SPIT_UP}coul{SE_M_WATERFALL}caus{SE_M_REVERSAL}that...\n"
	.string "{SE_M_HEAL_BELL}honestl{SE_M_YAWN}don'{SE_M_SPIT_UP}know.$"

SinjohRuins_Lab_Text_StevenCall12Plates:
	.string "STEVEN{SE_M_HEAT_WAVE}{PLAYER}.\p"
	.string "Anothe{SE_M_SAND_TOMB}tremor{SE_M_PERISH_SONG}Anothe{SE_M_SAND_TOMB}chamber\n"
	.string "openin{SE_M_SANDSTORM}up.\p"
	.string "W{SE_M_REVERSAL}stil{SE_M_BATON_PASS}can'{SE_M_SPIT_UP}figur{SE_M_REVERSAL}ou{SE_M_SPIT_UP}the\n"
	.string "patter{SE_M_ATTRACT}behin{SE_M_WATERFALL}th{SE_M_REVERSAL}timing.\p"
	.string "Say{SE_M_SUPERSONIC}{PLAYER}..{SE_M_PERISH_SONG}you'r{SE_M_REVERSAL}not\n"
	.string "doin{SE_M_SANDSTORM}somethin{SE_M_SANDSTORM}t{SE_M_ATTRACT2}caus{SE_M_REVERSAL}all\l"
	.string "this{SE_M_SUPERSONIC}ar{SE_M_REVERSAL}you?\p"
	.string "No{SE_M_SUPERSONIC}tha{SE_M_SPIT_UP}can'{SE_M_SPIT_UP}b{SE_M_REVERSAL}right.$"

SinjohRuins_Lab_Text_StevenCall15Plates:
	.string "STEVEN{SE_M_HEAT_WAVE}{PLAYER}.\p"
	.string "Di{SE_M_WATERFALL}yo{SE_M_DIVE}jus{SE_M_SPIT_UP}fin{SE_M_WATERFALL}anothe{SE_M_SAND_TOMB}PLATE?\p"
	.string ".................\p"
	.string "O{SE_M_ACID_ARMOR}course.\p"
	.string "Th{SE_M_REVERSAL}legendar{SE_M_YAWN}POKéMO{SE_M_PSYBEAM2}lying\n"
	.string "i{SE_M_ATTRACT}thes{SE_M_REVERSAL}ruins..{SE_M_PERISH_SONG}they'r{SE_M_REVERSAL}responding\l"
	.string "t{SE_M_ATTRACT2}you{SE_M_SUPERSONIC}aren'{SE_M_SPIT_UP}they?\p"
	.string "A{SE_M_GRASSWHISTLE}i{SE_M_ACID_ARMOR}the{SE_M_YAWN}wan{SE_M_SPIT_UP}t{SE_M_ATTRACT2}b{SE_M_REVERSAL}found.\p"
	.string "M{SE_M_YAWN}prediction{SE_M_GRASSWHISTLE}usuall{SE_M_YAWN}com{SE_M_REVERSAL}true.\n"
	.string "{SE_M_HEAL_BELL}shoul{SE_M_WATERFALL}hav{SE_M_REVERSAL}know{SE_M_ATTRACT}bette{SE_M_SAND_TOMB}than\l"
	.string "t{SE_M_ATTRACT2}doub{SE_M_SPIT_UP}you.$"

SinjohRuins_Lab_Text_StevenCall16Plates:
	.string "STEVEN{SE_M_HEAT_WAVE}{PLAYER}.\p"
	.string "We'r{SE_M_REVERSAL}ver{SE_M_YAWN}clos{SE_M_REVERSAL}now{SE_M_PERISH_SONG}{SE_M_HEAL_BELL}ca{SE_M_ATTRACT}fee{SE_M_BATON_PASS}it.\p"
	.string "..................\p"
	.string "Yo{SE_M_DIVE}shoul{SE_M_WATERFALL}com{SE_M_REVERSAL}se{SE_M_REVERSAL}thi{SE_M_GRASSWHISTLE}for\n"
	.string "yourself.$"

