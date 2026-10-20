@ Johto (data/maps/Route49_hns/scripts.inc), as built into the FireRed game.

Route49_hns_MapScripts::
	map_script 2, Route49_hns_OnFrame
	.byte 0

Route49_hns_OnFrame::
	map_script_2 20639, 3, Route49_EventScripts_KimonoGirl
	.2byte 0

Route49_EventScript_Skylar::
	goto_if_defeated 1640, Route49_EventScript_SkylarAfter
	msgbox Route49_Text_SkylarBefore, MSGBOX_NPC
	goto_if_not_defeated 1640, Route49_EventScript_TrySkylarBattle
	end

Route49_EventScript_TrySkylarBattle::
	goto_if_eq 20639, 6, Route49_EventScript_SkylarBattle
	end

Route49_EventScript_SkylarBattle::
	lock
	msgbox Route49_Text_SkylarBeforeBattle, MSGBOX_AUTOCLOSE
	trainerbattle_no_intro 1640, Route49_Text_SkylarDefeat
	giveitem ITEM_SKY_PLATE
	addvar 20640, 1
	msgbox Route49_Text_SkylarAfter, MSGBOX_AUTOCLOSE
	call_if_eq 20640, 3, SinjohRuins_Lab_EventScript_3Plates
	call_if_eq 20640, 6, SinjohRuins_Lab_EventScript_6Plates
	call_if_eq 20640, 9, SinjohRuins_Lab_EventScript_9Plates
	call_if_eq 20640, 12, SinjohRuins_Lab_EventScript_12Plates
	call_if_eq 20640, 15, SinjohRuins_Lab_EventScript_15Plates
	call_if_eq 20640, 16, SinjohRuins_Lab_EventScript_16Plates
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
	playse 21
	applymovement 3, J_Common_Movement_ExclamationMark
	waitmovement
	delay 20
	applymovement 3, Route49_KimonoGirl_Movement1
	waitmovement
	msgbox Route49_Text_KimonoGirl MSGBOX_DEFAULT
	closemessage
	applymovement 3, Route49_KimonoGitl_Movement2
	waitmovement
	setflag 9085
	setvar 20639, 4
	removeobject 3
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
	setobjectxyperm 11, 48, 42
	playse 209
	getplayerxy 16385, 16386
	dofieldeffectsparkle 16385, 16386, 0
	waitfieldeffect 54
	playse 21
	applymovement2 255, J_Common_Movement_ExclamationMark
	delay 55
	waitmovement 255
	msgbox SinjohRuins_Lab_Text_PlayFlute, MSGBOX_YESNO
	closemessage
	goto_if_eq 32781, FALSE, SinjohRuins_Lab_EventScript_NoOp
	playbgm ((((558 + 1) + 0xAF) + 1) + 0x00), FALSE
	delay 200
	fadedefaultbgm
	addobject 11
	clearflag 9117
	applymovement2 11, Route49_Movement_OverqwilEntrance1
	delay 10
	playmoncry 904, 0
	waitmoncry
	playmoncry 904, 0
	waitmoncry
	waitmovement 0
	applymovement2 11, Route49_Movement_OverqwilEntrance2
	delay 10
	playse 10
	delay 20
	waitmovement 11
	setvar 32772, 1
	setvar 32773, 1
	setvar 32774, 5
	setvar 32775, 2
	special ShakeCamera
	setobjectxyperm 11, 48, 44
	setvar 20645, 2
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
	playmoncry 904, 2
	waitmoncry
	setwildbossbattle species=904, level=80, item=ITEM_BLACK_SLUDGE, move1_1=MOVE_BARB_BARRAGE, move1_2=MOVE_LIQUIDATION, move1_3=MOVE_TOXIC_SPIKES move1_4=MOVE_CURSE
	settotemboost B_POSITION_OPPONENT_LEFT, 0, 2, 0, 0, 3, 0
	setflag 2411
	setflag 2410
	setflag 2409
	setflag 8804
	dowildbattle
	specialvar 32781, GetBattleOutcome
	goto_if_eq 32781, 4, Route49_EventScript_OverqwilRan
	bufferspeciesname STR_VAR_1, 904
	msgbox SinjohRuins_Lab_Text_DropedItem, MSGBOX_DEFAULT
	giveitem ITEM_DREAD_PLATE
	addvar 20640, 1
	fadescreenswapbuffers 1
	removeobject 11
	setflag 9117
	fadescreenswapbuffers 0
	call_if_eq 20640, 3, SinjohRuins_Lab_EventScript_3Plates
	call_if_eq 20640, 6, SinjohRuins_Lab_EventScript_6Plates
	call_if_eq 20640, 9, SinjohRuins_Lab_EventScript_9Plates
	call_if_eq 20640, 12, SinjohRuins_Lab_EventScript_12Plates
	call_if_eq 20640, 15, SinjohRuins_Lab_EventScript_15Plates
	call_if_eq 20640, 16, SinjohRuins_Lab_EventScript_16Plates
	clearflag 2411
	clearflag 2410
	clearflag 2409
	clearflag 8804
	release
	end

Route49_EventScript_OverqwilRan::
	clearflag 2411
	clearflag 2410
	clearflag 2409
	clearflag 8804
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
	setobjectxyperm 12, 59, 2
	playse 209
	getplayerxy 16385, 16386
	dofieldeffectsparkle 16385, 16386, 0
	waitfieldeffect 54
	playse 21
	applymovement2 255, J_Common_Movement_ExclamationMark
	delay 55
	waitmovement 255
	msgbox SinjohRuins_Lab_Text_PlayFlute, MSGBOX_YESNO
	closemessage
	goto_if_eq 32781, FALSE, SinjohRuins_Lab_EventScript_NoOp
	playbgm ((((558 + 1) + 0xAF) + 1) + 0x00), FALSE
	applymovement2 255, Route49_Movement_PlayerWyrdeerLeft
	delay 200
	waitmovement 0
	fadedefaultbgm
	addobject 12
	clearflag 9116
	applymovement2 12, Route49_Movement_WyrdeerEntrance1
	delay 10
	playmoncry 899, 0
	waitmoncry
	playmoncry 899, 0
	waitmoncry
	waitmovement 0
	applymovement2 12, Route49_Movement_WyrdeerEntrance2
	delay 90
	playse 10
	delay 20
	waitmovement 12
	setvar 32772, 1
	setvar 32773, 1
	setvar 32774, 5
	setvar 32775, 2
	special ShakeCamera
	setobjectxyperm 12, 59, 7
	setvar 20646, 2
	release
	end

Route49_EventScript_ActivateWyrdeerRight::
	lock
	setobjectxyperm 12, 59, 2
	playse 209
	getplayerxy 16385, 16386
	dofieldeffectsparkle 16385, 16386, 0
	waitfieldeffect 54
	playse 21
	applymovement2 255, J_Common_Movement_ExclamationMark
	delay 55
	waitmovement 255
	msgbox SinjohRuins_Lab_Text_PlayFlute, MSGBOX_YESNO
	closemessage
	goto_if_eq 32781, FALSE, SinjohRuins_Lab_EventScript_NoOp
	applymovement2 255, Route49_Movement_PlayerWyrdeerRight
	delay 200
	waitmovement 0
	fadedefaultbgm
	addobject 12
	clearflag 9116
	applymovement2 12, Route49_Movement_WyrdeerEntrance1
	delay 10
	playmoncry 899, 0
	waitmoncry
	playmoncry 899, 0
	waitmoncry
	waitmovement 0
	applymovement2 12, Route49_Movement_WyrdeerEntrance2
	delay 10
	playse 10
	delay 20
	waitmovement 12
	setvar 32772, 1
	setvar 32773, 1
	setvar 32774, 5
	setvar 32775, 2
	special ShakeCamera
	setobjectxyperm 12, 59, 7
	setvar 20646, 2
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
	playmoncry 899, 2
	waitmoncry
	setwildbossbattle species=899, level=80, item=ITEM_CLEAR_AMULET, move1_1=MOVE_PSYSHIELD_BASH, move1_2=MOVE_LUNGE, move1_3=MOVE_CALM_MIND move1_4=MOVE_THUNDERBOLT
	settotemboost B_POSITION_OPPONENT_LEFT, 0, 1, 2, 0, 1, 0
	setflag 2411
	setflag 2410
	setflag 2409
	setflag 8804
	dowildbattle
	specialvar 32781, GetBattleOutcome
	goto_if_eq 32781, 4, Route49_EventScript_WyrdeerRan
	bufferspeciesname STR_VAR_1, 899
	msgbox SinjohRuins_Lab_Text_DropedItem, MSGBOX_DEFAULT
	giveitem ITEM_MIND_PLATE
	addvar 20640, 1
	fadescreenswapbuffers 1
	removeobject 12
	setflag 9116
	fadescreenswapbuffers 0
	call_if_eq 20640, 3, SinjohRuins_Lab_EventScript_3Plates
	call_if_eq 20640, 6, SinjohRuins_Lab_EventScript_6Plates
	call_if_eq 20640, 9, SinjohRuins_Lab_EventScript_9Plates
	call_if_eq 20640, 12, SinjohRuins_Lab_EventScript_12Plates
	call_if_eq 20640, 15, SinjohRuins_Lab_EventScript_15Plates
	call_if_eq 20640, 16, SinjohRuins_Lab_EventScript_16Plates
	clearflag 2411
	clearflag 2410
	clearflag 2409
	clearflag 8804
	release
	end

Route49_EventScript_WyrdeerRan::
	clearflag 2411
	clearflag 2410
	clearflag 2409
	clearflag 8804
	release
	end

Route49_EventScript_Item_TMRockClimb::
	finditem 651
	end

