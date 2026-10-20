@ Johto (data/maps/NewSinjoh_House3_hns/scripts.inc), as built into the FireRed game.

NewSinjoh_House3_hns_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, NewSinjoh_House3_OnFrame
	map_script MAP_SCRIPT_ON_LOAD, NewSinjoh_House3_OnTransition
	.byte 0

NewSinjoh_House3_OnTransition::
	call_if_ge JOHTO_VAR_NOBLE_TYPHLOSION, 2, NewSinjoh_House3_AddStairs
	end

NewSinjoh_House3_AddStairs::
	setmetatile 38, 13, 0x015, TRUE
	setmetatile 38, 14, 0x005, TRUE
	setmetatile 38, 15, 0x00D, TRUE
	setmetatile 39, 14, 0x006, TRUE
	setmetatile 39, 15, 0x00E, TRUE
	setmetatile 40, 14, 0x007, FALSE
	setmetatile 40, 15, 0x00F, FALSE
	return

NewSinjoh_House3_OnFrame:
	map_script_2 VAR_TEMP_0, 0, NewSinjoh_HauntedHouse_EventScript_Enter
	.2byte 0

NewSinjoh_HauntedHouse_EventScript_Enter::
	setvar VAR_TEMP_0, 1
	goto_if_eq JOHTO_VAR_NOBLE_TYPHLOSION, 1, NewSinjoh_HauntedHouse_EventScript_StartScary
	goto_if_eq JOHTO_VAR_NOBLE_TYPHLOSION, 0, NewSinjoh_HauntedHouse_EventScript_TooEarly
	end

NewSinjoh_HauntedHouse_EventScript_TooEarly::
	msgbox NewSinjoh_HauntedHouse_Text_TooEarlyNoReaction, MSGBOX_AUTOCLOSE
	release
	end

NewSinjoh_HauntedHouse_Text_TooEarlyNoReaction:
	.string "Yo{SE_M_DIVE}sens{SE_M_REVERSAL}a{SE_M_ATTRACT}od{SE_M_WATERFALL}presence...\p"
	.string "Bu{SE_M_SPIT_UP}ther{SE_M_REVERSAL}i{SE_M_GRASSWHISTLE}n{SE_M_ATTRACT2}reaction.$"

NewSinjoh_HauntedHouse_EventScript_StartScary::
	msgbox NewSinjoh_HauntedHouse_Text_StartScary, MSGBOX_AUTOCLOSE
	playse SE_M_DETECT
	getplayerxy VAR_TEMP_1, VAR_TEMP_2
	dofieldeffectsparkle VAR_TEMP_1, VAR_TEMP_2, 0
	waitfieldeffect FLDEFF_SPARKLE
	playse SE_PIN
	applymovement2 LOCALID_PLAYER, J_Common_Movement_ExclamationMark
	delay 55
	waitmovement LOCALID_PLAYER
	msgbox SinjohRuins_Lab_Text_PlayFlute, MSGBOX_YESNO
	closemessage
	goto_if_eq VAR_RESULT, FALSE, SinjohRuins_Lab_EventScript_NoOp
	playbgm ((((558 + 1) + 0xAF) + 1) + 0x00), FALSE
	delay 200
	fadedefaultbgm
	special SpawnCameraObject
	applymovement OBJ_EVENT_ID_CAMERA, NewSinjoh_House3_Movement_CameraPanLeft
	waitmovement 0
	setvar VAR_0x8004, 2
	setvar VAR_0x8005, 2
	setvar VAR_0x8006, 20
	setvar VAR_0x8007, 4
	special ShakeCamera
	waitstate
	call NewSinjoh_House3_AddStairs
	special DrawWholeMapView
	playse SE_CLICK
	applymovement2 OBJ_EVENT_ID_CAMERA, NewSinjoh_House3_Movement_CameraPanRight
	waitmovement 0
	special RemoveCameraObject
	addobject LOCALID_NEWSINJOH_HOUSE3_NOBLE_TYPHLOSION
	clearflag JOHTO_FLAG_HIDE_NEWSINJOH_HOUSE3_NOBLE_TYPHLOSION
	setvar JOHTO_VAR_NOBLE_TYPHLOSION, 2
	release
	end

NewSinjoh_House3_EventScript_NobleTyphlosion::
	lock
	faceplayer
	playmoncry SPECIES_TYPHLOSION_HISUI, CRY_MODE_ENCOUNTER
	waitmoncry
	setwildbossbattle species=997, level=80, item=ITEM_SPOOKY_PLATE, move1_1=MOVE_INFERNAL_PARADE, move1_2=MOVE_LAVA_PLUME, move1_3=MOVE_CONFUSE_RAY move1_4=MOVE_SOLAR_BEAM
	settotemboost B_POSITION_OPPONENT_LEFT, 0, 2, 0, 1, 2, 0
	setflag FLAG_NO_WILD_CATCHING
	setflag FLAG_NO_WILD_RUNNING
	setflag FLAG_SMART_WILD_AI
	setflag JOHTO_FLAG_NO_SHINY
	dowildbattle
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, NewSinjoh_House3_EventScript_NobleTyphlosionRan
	bufferspeciesname STR_VAR_1, SPECIES_TYPHLOSION_HISUI
	msgbox SinjohRuins_Lab_Text_DropedItem, MSGBOX_DEFAULT
	giveitem ITEM_SPOOKY_PLATE
	addvar JOHTO_VAR_PLATECOUNTER, 1
	fadescreenswapbuffers FADE_TO_BLACK
	removeobject LOCALID_NEWSINJOH_HOUSE3_NOBLE_TYPHLOSION
	setflag JOHTO_FLAG_HIDE_NEWSINJOH_HOUSE3_NOBLE_TYPHLOSION
	fadescreenswapbuffers FADE_FROM_BLACK
	call_if_eq JOHTO_VAR_PLATECOUNTER, 3, SinjohRuins_Lab_EventScript_3Plates
	call_if_eq JOHTO_VAR_PLATECOUNTER, 6, SinjohRuins_Lab_EventScript_6Plates
	call_if_eq JOHTO_VAR_PLATECOUNTER, 9, SinjohRuins_Lab_EventScript_9Plates
	call_if_eq JOHTO_VAR_PLATECOUNTER, 12, SinjohRuins_Lab_EventScript_12Plates
	call_if_eq JOHTO_VAR_PLATECOUNTER, 15, SinjohRuins_Lab_EventScript_15Plates
	call_if_eq JOHTO_VAR_PLATECOUNTER, 16, SinjohRuins_Lab_EventScript_16Plates
	clearflag FLAG_NO_WILD_CATCHING
	clearflag FLAG_NO_WILD_RUNNING
	clearflag FLAG_SMART_WILD_AI
	clearflag JOHTO_FLAG_NO_SHINY
	release
	end

NewSinjoh_House3_EventScript_NobleTyphlosionRan::
	clearflag FLAG_NO_WILD_CATCHING
	clearflag FLAG_NO_WILD_RUNNING
	clearflag FLAG_SMART_WILD_AI
	clearflag JOHTO_FLAG_NO_SHINY
	release
	end

NewSinjoh_House3_Movement_CameraPanLeft:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

NewSinjoh_House3_Movement_CameraPanRight:
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

NewSinjoh_HauntedHouse_Text_StartScary:
	.string "Yo{SE_M_DIVE}sens{SE_M_REVERSAL}a{SE_M_ATTRACT}od{SE_M_WATERFALL}presence...\p"
	.string "Ar{SE_M_REVERSAL}yo{SE_M_DIVE}bein{SE_M_SANDSTORM}watched?$"

NewSinjoh_HauntedHouse_EventScript_Log1::
	msgbox NewSinjoh_HauntedHouse_Text_Log1, MSGBOX_SIGN
	end

NewSinjoh_HauntedHouse_EventScript_Log2::
	msgbox NewSinjoh_HauntedHouse_Text_Log2, MSGBOX_SIGN
	end

NewSinjoh_HauntedHouse_EventScript_Log3::
	msgbox NewSinjoh_HauntedHouse_Text_Log3, MSGBOX_SIGN
	end

NewSinjoh_HauntedHouse_Text_Log1:
	.string "Researc{SE_M_TRI_ATTACK}Lo{SE_M_SANDSTORM}9{SE_M_HEAT_WAVE} Septembe{SE_M_SAND_TOMB}20{SE_M_SUPERSONIC}1975\p"
	.string "Th{SE_M_REVERSAL}day{SE_M_GRASSWHISTLE}ar{SE_M_REVERSAL}gettin{SE_M_SANDSTORM}shorte{SE_M_SAND_TOMB}now\n"
	.string "an{SE_M_WATERFALL}th{SE_M_REVERSAL}win{SE_M_WATERFALL}i{SE_M_GRASSWHISTLE}becomin{SE_M_SANDSTORM}harsh.\p"
	.string "Th{SE_M_REVERSAL}villager{SE_M_GRASSWHISTLE}wer{SE_M_REVERSAL}quit{SE_M_REVERSAL}welcoming.\p"
	.string "The{SE_M_YAWN}ar{SE_M_REVERSAL}allowin{SE_M_SANDSTORM}m{SE_M_REVERSAL}t{SE_M_ATTRACT2}sta{SE_M_YAWN}here\n"
	.string "i{SE_M_ATTRACT}thi{SE_M_GRASSWHISTLE}cabi{SE_M_ATTRACT}fo{SE_M_SAND_TOMB}th{SE_M_REVERSAL}winter.\p"
	.string "I{SE_M_SPIT_UP}seem{SE_M_GRASSWHISTLE}{SE_M_CHARGE}famil{SE_M_YAWN}use{SE_M_WATERFALL}t{SE_M_ATTRACT2}liv{SE_M_REVERSAL}here.\n"
	.string "{SE_M_HEAL_BELL}ofte{SE_M_ATTRACT}thin{SE_M_ENCORE2}abou{SE_M_SPIT_UP}m{SE_M_YAWN}family.\p"
	.string "Mayb{SE_M_REVERSAL}{SE_M_HEAL_BELL}wil{SE_M_BATON_PASS}hav{SE_M_REVERSAL}th{SE_M_REVERSAL}courag{SE_M_REVERSAL}to\n"
	.string "retur{SE_M_ATTRACT}t{SE_M_ATTRACT2}the{SE_M_MILK_DRINK}i{SE_M_ATTRACT}th{SE_M_REVERSAL}spring.$"

NewSinjoh_HauntedHouse_Text_Log2:
	.string "Researc{SE_M_TRI_ATTACK}Lo{SE_M_SANDSTORM}10{SE_M_HEAT_WAVE}Octobe{SE_M_SAND_TOMB}20{SE_M_SUPERSONIC}1975\p"
	.string "M{SE_M_YAWN}thought{SE_M_GRASSWHISTLE}hav{SE_M_REVERSAL}turne{SE_M_WATERFALL}dark.\p"
	.string "Perhap{SE_M_GRASSWHISTLE}i{SE_M_SPIT_UP}i{SE_M_GRASSWHISTLE}th{SE_M_REVERSAL}changin{SE_M_SANDSTORM}o{SE_M_ACID_ARMOR}the\n"
	.string "seasons.\p"
	.string "Th{SE_M_REVERSAL}villager{SE_M_GRASSWHISTLE}continu{SE_M_REVERSAL}t{SE_M_ATTRACT2}trea{SE_M_SPIT_UP}me\n"
	.string "a{SE_M_GRASSWHISTLE}on{SE_M_REVERSAL}o{SE_M_ACID_ARMOR}thei{SE_M_SAND_TOMB}own.\p"
	.string "Bu{SE_M_SPIT_UP}th{SE_M_REVERSAL}guil{SE_M_SPIT_UP}{SE_M_HEAL_BELL}carr{SE_M_YAWN}prevent{SE_M_GRASSWHISTLE}m{SE_M_REVERSAL}from\n"
	.string "returnin{SE_M_SANDSTORM}th{SE_M_REVERSAL}sentiment.\p"
	.string "{SE_M_HEAL_BELL}rarel{SE_M_YAWN}leav{SE_M_REVERSAL}th{SE_M_REVERSAL}cabi{SE_M_ATTRACT}now.\p"
	.string "An{SE_M_WATERFALL}whe{SE_M_ATTRACT}{SE_M_HEAL_BELL}thin{SE_M_ENCORE2}o{SE_M_ACID_ARMOR}m{SE_M_YAWN}family...\n"
	.string "Thei{SE_M_SAND_TOMB}face{SE_M_GRASSWHISTLE}hav{SE_M_REVERSAL}changed...\l"
	.string "{SE_M_HEAL_BELL}onl{SE_M_YAWN}se{SE_M_REVERSAL}th{SE_M_REVERSAL}face{SE_M_GRASSWHISTLE}o{SE_M_ACID_ARMOR}th{SE_M_REVERSAL}POKéMON\l"
	.string "tha{SE_M_SPIT_UP}wer{SE_M_REVERSAL}los{SE_M_SPIT_UP}a{SE_M_SPIT_UP}th{SE_M_REVERSAL}ruins...\p"
	.string "Sometime{SE_M_GRASSWHISTLE}{SE_M_HEAL_BELL}thin{SE_M_ENCORE2}th{SE_M_REVERSAL}POKéMO{SE_M_PSYBEAM2}are\n"
	.string "her{SE_M_REVERSAL}wit{SE_M_TRI_ATTACK}me{SE_M_PERISH_SONG}{SE_M_HEAL_BELL}se{SE_M_REVERSAL}the{SE_M_MILK_DRINK}in\l"
	.string "reflections{SE_M_SUPERSONIC}{SE_M_HEAL_BELL}fee{SE_M_BATON_PASS}thei{SE_M_SAND_TOMB}gaze.\p"
	.string "Thing{SE_M_GRASSWHISTLE}wil{SE_M_BATON_PASS}b{SE_M_REVERSAL}bette{SE_M_SAND_TOMB}i{SE_M_ATTRACT}th{SE_M_REVERSAL}spring.$"

NewSinjoh_HauntedHouse_Text_Log3:
	.string "Researc{SE_M_TRI_ATTACK}Lo{SE_M_SANDSTORM}10{SE_M_HEAT_WAVE}Novembe{SE_M_SAND_TOMB}1{SE_M_SUPERSONIC}1975\p"
	.string "{SE_M_HEAL_BELL}a{SE_M_MILK_DRINK}no{SE_M_SPIT_UP}alon{SE_M_REVERSAL}here.\n"
	.string "Mayb{SE_M_REVERSAL}{SE_M_HEAL_BELL}neve{SE_M_SAND_TOMB}was.\p"
	.string "Th{SE_M_REVERSAL}POKéMO{SE_M_PSYBEAM2}ar{SE_M_REVERSAL}wit{SE_M_TRI_ATTACK}me...\p"
	.string "The{SE_M_YAWN}ar{SE_M_REVERSAL}angr{SE_M_YAWN}wit{SE_M_TRI_ATTACK}me{SE_M_SUPERSONIC}{SE_M_HEAL_BELL}think.\p"
	.string "Object{SE_M_GRASSWHISTLE}ar{SE_M_REVERSAL}thrown{SE_M_SUPERSONIC}door{SE_M_GRASSWHISTLE}slam.\p"
	.string "Heav{SE_M_YAWN}boxe{SE_M_GRASSWHISTLE}bloc{SE_M_ENCORE2}th{SE_M_REVERSAL}fron{SE_M_SPIT_UP}door.\p"
	.string "Bu{SE_M_SPIT_UP}truthfully{SE_M_SUPERSONIC}{SE_M_HEAL_BELL}coul{SE_M_WATERFALL}leave\n"
	.string "i{SE_M_ACID_ARMOR}{SE_M_HEAL_BELL}wante{SE_M_WATERFALL}to.\p"
	.string "Ther{SE_M_REVERSAL}i{SE_M_GRASSWHISTLE}nothin{SE_M_SANDSTORM}els{SE_M_REVERSAL}fo{SE_M_SAND_TOMB}m{SE_M_REVERSAL}now.\p"
	.string "I'v{SE_M_REVERSAL}writte{SE_M_ATTRACT}o{SE_M_ACID_ARMOR}{SE_M_CHARGE}famil{SE_M_YAWN}before,\n"
	.string "bu{SE_M_SPIT_UP}th{SE_M_REVERSAL}POKéMO{SE_M_PSYBEAM2}ar{SE_M_REVERSAL}th{SE_M_REVERSAL}onl{SE_M_YAWN}family\l"
	.string "{SE_M_HEAL_BELL}ca{SE_M_ATTRACT}remember...\p"
	.string "{SE_M_HEAL_BELL}a{SE_M_MILK_DRINK}runnin{SE_M_SANDSTORM}ou{SE_M_SPIT_UP}o{SE_M_ACID_ARMOR}food{SE_M_SUPERSONIC}bu{SE_M_SPIT_UP}my\n"
	.string "guil{SE_M_SPIT_UP}outpace{SE_M_GRASSWHISTLE}m{SE_M_YAWN}hunger.\p"
	.string "{SE_M_HEAL_BELL}thin{SE_M_ENCORE2}{SE_M_HEAL_BELL}wil{SE_M_BATON_PASS}sta{SE_M_YAWN}her{SE_M_REVERSAL}{SE_M_CHARGE}while...$"

