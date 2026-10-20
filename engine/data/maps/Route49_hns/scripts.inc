@ Johto (data/maps/Route49_hns/scripts.inc), as built into the FireRed game.

Route49_hns_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, Route49_hns_OnFrame
	.byte 0

Route49_hns_OnFrame::
	map_script_2 JOHTO_VAR_SINJOH_STORYLINE, 3, Route49_EventScripts_KimonoGirl
	.2byte 0

Route49_EventScript_Skylar::
	goto_if_defeated TRAINER_JOHTO_SKYLAR_HNS, Route49_EventScript_SkylarAfter
	msgbox Route49_Text_SkylarBefore, MSGBOX_NPC
	goto_if_not_defeated TRAINER_JOHTO_SKYLAR_HNS, Route49_EventScript_TrySkylarBattle
	end

Route49_EventScript_TrySkylarBattle::
	goto_if_eq JOHTO_VAR_SINJOH_STORYLINE, 6, Route49_EventScript_SkylarBattle
	end

Route49_EventScript_SkylarBattle::
	lock
	msgbox Route49_Text_SkylarBeforeBattle, MSGBOX_AUTOCLOSE
	trainerbattle_no_intro TRAINER_JOHTO_SKYLAR_HNS, Route49_Text_SkylarDefeat
	giveitem ITEM_SKY_PLATE
	addvar JOHTO_VAR_PLATECOUNTER, 1
	msgbox Route49_Text_SkylarAfter, MSGBOX_AUTOCLOSE
	call_if_eq JOHTO_VAR_PLATECOUNTER, 3, SinjohRuins_Lab_EventScript_3Plates
	call_if_eq JOHTO_VAR_PLATECOUNTER, 6, SinjohRuins_Lab_EventScript_6Plates
	call_if_eq JOHTO_VAR_PLATECOUNTER, 9, SinjohRuins_Lab_EventScript_9Plates
	call_if_eq JOHTO_VAR_PLATECOUNTER, 12, SinjohRuins_Lab_EventScript_12Plates
	call_if_eq JOHTO_VAR_PLATECOUNTER, 15, SinjohRuins_Lab_EventScript_15Plates
	call_if_eq JOHTO_VAR_PLATECOUNTER, 16, SinjohRuins_Lab_EventScript_16Plates
	release
	end

Route49_EventScript_SkylarAfter::
	msgbox Route49_Text_SkylarAfter, MSGBOX_NPC
	end

Route49_Text_SkylarDefeat:
	.string "OKAY{SE_M_SUPERSONIC}yo{SE_M_DIVE}ca{SE_M_ATTRACT}hav{SE_M_REVERSAL}th{SE_M_REVERSAL}PLATE.$"

Route49_Text_SkylarAfter:
	.string "A{SE_M_GRASSWHISTLE}coo{SE_M_BATON_PASS}a{SE_M_GRASSWHISTLE}tha{SE_M_SPIT_UP}PLAT{SE_M_SWORDS_DANCE}is,\n"
	.string "yo{SE_M_DIVE}earne{SE_M_WATERFALL}i{SE_M_SPIT_UP}fai{SE_M_SAND_TOMB}an{SE_M_WATERFALL}square.\p"
	.string "I'l{SE_M_BATON_PASS}jus{SE_M_SPIT_UP}bu{SE_M_YAWN}somethin{SE_M_SANDSTORM}a{SE_M_SPIT_UP}th{SE_M_REVERSAL}gift\n"
	.string "sho{SE_M_MORNING_SUN}instead.$"

Route49_Text_SkylarBeforeBattle:
	.string "What?\p"
	.string "Yo{SE_M_DIVE}wan{SE_M_SPIT_UP}th{SE_M_REVERSAL}PLATE?\n"
	.string "It'{SE_M_GRASSWHISTLE}a{SE_M_ATTRACT}artifac{SE_M_SPIT_UP}imbue{SE_M_WATERFALL}wit{SE_M_TRI_ATTACK}an\l"
	.string "ancien{SE_M_SPIT_UP}powe{SE_M_SAND_TOMB}wit{SE_M_TRI_ATTACK}{SE_M_CHARGE}connection\l"
	.string "t{SE_M_ATTRACT2}th{SE_M_REVERSAL}legendar{SE_M_YAWN}POKéMON?!\p"
	.string "Wel{SE_M_BATON_PASS}no{SE_M_TWISTER}I'{SE_M_MILK_DRINK}definitel{SE_M_YAWN}keepin{SE_M_SANDSTORM}it.\p"
	.string "Fine.\p"
	.string "You'l{SE_M_BATON_PASS}jus{SE_M_SPIT_UP}hav{SE_M_REVERSAL}t{SE_M_ATTRACT2}battl{SE_M_REVERSAL}m{SE_M_REVERSAL}fo{SE_M_SAND_TOMB}it.$"

Route49_Text_SkylarBefore:
	.string "Whe{SE_M_ATTRACT}{SE_M_HEAL_BELL}wa{SE_M_GRASSWHISTLE}hittin{SE_M_SANDSTORM}th{SE_M_REVERSAL}slopes{SE_M_SUPERSONIC}my\n"
	.string "ski{SE_M_GRASSWHISTLE}snagge{SE_M_WATERFALL}o{SE_M_ATTRACT}something.\p"
	.string "I{SE_M_SPIT_UP}wa{SE_M_GRASSWHISTLE}thi{SE_M_GRASSWHISTLE}strang{SE_M_REVERSAL}SKY-blu{SE_M_REVERSAL}PLATE.\p"
	.string "{SE_M_HEAL_BELL}thin{SE_M_ENCORE2}I'l{SE_M_BATON_PASS}hol{SE_M_WATERFALL}ont{SE_M_ATTRACT2}i{SE_M_SPIT_UP}a{SE_M_GRASSWHISTLE}a\n"
	.string "souvenir!$"

Route49_EventScript_SkierM::
	msgbox Route49_Text_SkierM, MSGBOX_NPC
	end

Route49_Text_SkierM::
	.string "Hey{SE_M_SUPERSONIC}watc{SE_M_TRI_ATTACK}ou{SE_M_SPIT_UP}fo{SE_M_SAND_TOMB}m{SE_M_YAWN}board!\p"
	.string "What{SE_M_SING}Yo{SE_M_DIVE}wan{SE_M_SPIT_UP}t{SE_M_ATTRACT2}battle?\n"
	.string "N{SE_M_ATTRACT2}way{SE_M_SUPERSONIC}thes{SE_M_REVERSAL}slope{SE_M_GRASSWHISTLE}ar{SE_M_REVERSAL}to{SE_M_ATTRACT2}wicked!$"

Route49_EventScripts_KimonoGirl::
	delay 10
	lock
	playbgm ((558 + 1) + 0x27), FALSE
	delay 10
	playse SE_PIN
	applymovement LOCALID_ROUTE49_KIMONOGIRL, J_Common_Movement_ExclamationMark
	waitmovement
	delay 20
	applymovement LOCALID_ROUTE49_KIMONOGIRL, Route49_KimonoGirl_Movement1
	waitmovement
	msgbox Route49_Text_KimonoGirl MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_ROUTE49_KIMONOGIRL, Route49_KimonoGitl_Movement2
	waitmovement
	setflag JOHTO_FLAG_ROUTE_49_KIMONOGIRL
	setvar JOHTO_VAR_SINJOH_STORYLINE, 4
	removeobject LOCALID_ROUTE49_KIMONOGIRL
	fadedefaultbgm
	release
	end

Route49_KimonoGirl_Movement1:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

Route49_KimonoGitl_Movement2:
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

Route49_Text_KimonoGirl:
	.string "You....\p"
	.string "Yo{SE_M_DIVE}mus{SE_M_SPIT_UP}b{SE_M_REVERSAL}{PLAYER}{SE_M_SUPERSONIC}correct?\n"
	.string "I'v{SE_M_REVERSAL}hear{SE_M_WATERFALL}al{SE_M_BATON_PASS}abou{SE_M_SPIT_UP}yo{SE_M_DIVE}and\l"
	.string "you{SE_M_SAND_TOMB}deed{SE_M_GRASSWHISTLE}fro{SE_M_MILK_DRINK}m{SE_M_YAWN}cousins\l"
	.string "i{SE_M_ATTRACT}ECRUTEA{SE_M_SNORE}CITY.\p"
	.string "M{SE_M_YAWN}sister{SE_M_GRASSWHISTLE}wis{SE_M_TRI_ATTACK}t{SE_M_ATTRACT2}mee{SE_M_SPIT_UP}wit{SE_M_TRI_ATTACK}you.\l"
	.string "I{SE_M_ACID_ARMOR}yo{SE_M_DIVE}fin{SE_M_WATERFALL}th{SE_M_REVERSAL}time{SE_M_SUPERSONIC}please\n"
	.string "see{SE_M_ENCORE2}u{SE_M_GRASSWHISTLE}ou{SE_M_SPIT_UP}i{SE_M_ATTRACT}th{SE_M_REVERSAL}tow{SE_M_ATTRACT}u{SE_M_MORNING_SUN}ahead.$"

Route49_EventScript_Item_StarDust::
	finditem ITEM_STARDUST
	end

Route49_EventScript_Item_Lure::
	finditem ITEM_LURE
	end

Route49_EventScript_Sign::
	msgbox Route49_Text_Sign, MSGBOX_SIGN
	end

Route49_Text_Sign:
	.string "Th{SE_M_REVERSAL}sig{SE_M_ATTRACT}i{SE_M_GRASSWHISTLE}faded.\n"
	.string "ROUT{SE_M_SWORDS_DANCE}49$"

Route49_EventScript_ActivateOverqwil::
	lock
	setobjectxyperm LOCALID_ROUTE49_NOBLE_OVERQWIL, 48, 42
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
	addobject LOCALID_ROUTE49_NOBLE_OVERQWIL
	clearflag JOHTO_FLAG_HIDE_ROUTE49_NOBLE_OVERQWIL
	applymovement2 LOCALID_ROUTE49_NOBLE_OVERQWIL, Route49_Movement_OverqwilEntrance1
	delay 10
	playmoncry SPECIES_OVERQWIL, CRY_MODE_NORMAL
	waitmoncry
	playmoncry SPECIES_OVERQWIL, CRY_MODE_NORMAL
	waitmoncry
	waitmovement 0
	applymovement2 LOCALID_ROUTE49_NOBLE_OVERQWIL, Route49_Movement_OverqwilEntrance2
	delay 10
	playse SE_LEDGE
	delay 20
	waitmovement LOCALID_ROUTE49_NOBLE_OVERQWIL
	setvar VAR_0x8004, 1
	setvar VAR_0x8005, 1
	setvar VAR_0x8006, 5
	setvar VAR_0x8007, 2
	special ShakeCamera
	setobjectxyperm LOCALID_ROUTE49_NOBLE_OVERQWIL, 48, 44
	setvar JOHTO_VAR_NOBLE_OVERQWIL, 2
	release
	end

Route49_Movement_OverqwilEntrance1:
	walk_in_place_fast_down
	jump_in_place_down
	jump_in_place_down
	jump_in_place_down
	jump_in_place_down
	step_end

Route49_Movement_OverqwilEntrance2:
	walk_slow_down
	walk_slow_down
	walk_in_place_slow_down
	walk_in_place_slow_down
	jump_in_place_down
	step_end

Route49_EventScript_Overqwil::
	lock
	faceplayer
	playmoncry SPECIES_OVERQWIL, CRY_MODE_ENCOUNTER
	waitmoncry
	setwildbossbattle species=904, level=80, item=ITEM_BLACK_SLUDGE, move1_1=MOVE_BARB_BARRAGE, move1_2=MOVE_LIQUIDATION, move1_3=MOVE_TOXIC_SPIKES move1_4=MOVE_CURSE
	settotemboost B_POSITION_OPPONENT_LEFT, 0, 2, 0, 0, 3, 0
	setflag FLAG_NO_WILD_CATCHING
	setflag FLAG_NO_WILD_RUNNING
	setflag FLAG_SMART_WILD_AI
	setflag JOHTO_FLAG_NO_SHINY
	dowildbattle
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, Route49_EventScript_OverqwilRan
	bufferspeciesname STR_VAR_1, SPECIES_OVERQWIL
	msgbox SinjohRuins_Lab_Text_DropedItem, MSGBOX_DEFAULT
	giveitem ITEM_DREAD_PLATE
	addvar JOHTO_VAR_PLATECOUNTER, 1
	fadescreenswapbuffers FADE_TO_BLACK
	removeobject LOCALID_ROUTE49_NOBLE_OVERQWIL
	setflag JOHTO_FLAG_HIDE_ROUTE49_NOBLE_OVERQWIL
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

Route49_EventScript_OverqwilRan::
	clearflag FLAG_NO_WILD_CATCHING
	clearflag FLAG_NO_WILD_RUNNING
	clearflag FLAG_SMART_WILD_AI
	clearflag JOHTO_FLAG_NO_SHINY
	release
	end

Route49_Movement_PlayerWyrdeerRight:
	walk_left
	walk_left
	walk_left
	walk_up
	walk_up
	step_end

Route49_Movement_PlayerWyrdeerLeft:
	walk_right
	walk_up
	walk_right
	walk_up
	step_end

Route49_EventScript_ActivateWyrdeerLeft::
	lock
	setobjectxyperm LOCALID_ROUTE49_NOBLE_WYRDEER, 59, 2
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
	applymovement2 LOCALID_PLAYER, Route49_Movement_PlayerWyrdeerLeft
	delay 200
	waitmovement 0
	fadedefaultbgm
	addobject LOCALID_ROUTE49_NOBLE_WYRDEER
	clearflag JOHTO_FLAG_HIDE_ROUTE49_NOBLE_WYRDEER
	applymovement2 LOCALID_ROUTE49_NOBLE_WYRDEER, Route49_Movement_WyrdeerEntrance1
	delay 10
	playmoncry SPECIES_WYRDEER, CRY_MODE_NORMAL
	waitmoncry
	playmoncry SPECIES_WYRDEER, CRY_MODE_NORMAL
	waitmoncry
	waitmovement 0
	applymovement2 LOCALID_ROUTE49_NOBLE_WYRDEER, Route49_Movement_WyrdeerEntrance2
	delay 90
	playse SE_LEDGE
	delay 20
	waitmovement LOCALID_ROUTE49_NOBLE_WYRDEER
	setvar VAR_0x8004, 1
	setvar VAR_0x8005, 1
	setvar VAR_0x8006, 5
	setvar VAR_0x8007, 2
	special ShakeCamera
	setobjectxyperm LOCALID_ROUTE49_NOBLE_WYRDEER, 59, 7
	setvar JOHTO_VAR_NOBLE_WYRDEER, 2
	release
	end

Route49_EventScript_ActivateWyrdeerRight::
	lock
	setobjectxyperm LOCALID_ROUTE49_NOBLE_WYRDEER, 59, 2
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
	applymovement2 LOCALID_PLAYER, Route49_Movement_PlayerWyrdeerRight
	delay 200
	waitmovement 0
	fadedefaultbgm
	addobject LOCALID_ROUTE49_NOBLE_WYRDEER
	clearflag JOHTO_FLAG_HIDE_ROUTE49_NOBLE_WYRDEER
	applymovement2 LOCALID_ROUTE49_NOBLE_WYRDEER, Route49_Movement_WyrdeerEntrance1
	delay 10
	playmoncry SPECIES_WYRDEER, CRY_MODE_NORMAL
	waitmoncry
	playmoncry SPECIES_WYRDEER, CRY_MODE_NORMAL
	waitmoncry
	waitmovement 0
	applymovement2 LOCALID_ROUTE49_NOBLE_WYRDEER, Route49_Movement_WyrdeerEntrance2
	delay 10
	playse SE_LEDGE
	delay 20
	waitmovement LOCALID_ROUTE49_NOBLE_WYRDEER
	setvar VAR_0x8004, 1
	setvar VAR_0x8005, 1
	setvar VAR_0x8006, 5
	setvar VAR_0x8007, 2
	special ShakeCamera
	setobjectxyperm LOCALID_ROUTE49_NOBLE_WYRDEER, 59, 7
	setvar JOHTO_VAR_NOBLE_WYRDEER, 2
	release
	end

Route49_Movement_WyrdeerEntrance1:
	walk_down
	walk_in_place_fast_down
	jump_in_place_down
	jump_in_place_down
	jump_in_place_down
	jump_in_place_down
	step_end

Route49_Movement_WyrdeerEntrance2:
	walk_slow_down
	walk_slow_down
	jump_2_down
	walk_in_place_slow_down
	walk_in_place_slow_down
	jump_in_place_down
	step_end

Route49_EventScript_Wyrdeer::
	lock
	faceplayer
	playmoncry SPECIES_WYRDEER, CRY_MODE_ENCOUNTER
	waitmoncry
	setwildbossbattle species=899, level=80, item=ITEM_CLEAR_AMULET, move1_1=MOVE_PSYSHIELD_BASH, move1_2=MOVE_LUNGE, move1_3=MOVE_CALM_MIND move1_4=MOVE_THUNDERBOLT
	settotemboost B_POSITION_OPPONENT_LEFT, 0, 1, 2, 0, 1, 0
	setflag FLAG_NO_WILD_CATCHING
	setflag FLAG_NO_WILD_RUNNING
	setflag FLAG_SMART_WILD_AI
	setflag JOHTO_FLAG_NO_SHINY
	dowildbattle
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, Route49_EventScript_WyrdeerRan
	bufferspeciesname STR_VAR_1, SPECIES_WYRDEER
	msgbox SinjohRuins_Lab_Text_DropedItem, MSGBOX_DEFAULT
	giveitem ITEM_MIND_PLATE
	addvar JOHTO_VAR_PLATECOUNTER, 1
	fadescreenswapbuffers FADE_TO_BLACK
	removeobject LOCALID_ROUTE49_NOBLE_WYRDEER
	setflag JOHTO_FLAG_HIDE_ROUTE49_NOBLE_WYRDEER
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

Route49_EventScript_WyrdeerRan::
	clearflag FLAG_NO_WILD_CATCHING
	clearflag FLAG_NO_WILD_RUNNING
	clearflag FLAG_SMART_WILD_AI
	clearflag JOHTO_FLAG_NO_SHINY
	release
	end

Route49_EventScript_Item_TMRockClimb::
	finditem ITEM_TM_ROCK_CLIMB
	end

