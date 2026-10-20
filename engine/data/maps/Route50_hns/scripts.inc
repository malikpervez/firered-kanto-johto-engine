@ Johto (data/maps/Route50_hns/scripts.inc), as built into the FireRed game.

Route50_hns_MapScripts::
	.byte 0

Route50_EventScript_BlackBelt1::
	msgbox Route50_Text_BlackBelt1, MSGBOX_NPC
	end

Route50_Text_BlackBelt1::
	.string "Th{SE_M_REVERSAL}bod{SE_M_YAWN}mus{SE_M_SPIT_UP}b{SE_M_REVERSAL}hardened\n"
	.string "an{SE_M_WATERFALL}th{SE_M_REVERSAL}min{SE_M_WATERFALL}strengthened\l"
	.string "i{SE_M_ATTRACT}th{SE_M_REVERSAL}harshes{SE_M_SPIT_UP}o{SE_M_ACID_ARMOR}conditions!$"

Route50_EventScript_BlackBelt2::
	msgbox Route50_Text_BlackBelt2, MSGBOX_NPC
	end

Route50_Text_BlackBelt2::
	.string "Phew!\p"
	.string "I'{SE_M_MILK_DRINK}no{SE_M_SPIT_UP}a{SE_M_GRASSWHISTLE}hardcor{SE_M_REVERSAL}a{SE_M_GRASSWHISTLE}h{SE_M_REVERSAL}is.\p"
	.string "There'{SE_M_GRASSWHISTLE}reall{SE_M_YAWN}no{SE_M_SPIT_UP}muc{SE_M_TRI_ATTACK}else\n"
	.string "t{SE_M_ATTRACT2}d{SE_M_ATTRACT2}her{SE_M_REVERSAL}bu{SE_M_SPIT_UP}train.$"

Route50_EventScript_Wessel::
	goto_if_defeated 1639, Route50_EventScript_WesselAfter
	msgbox Route50_Text_WesselBefore, MSGBOX_NPC
	goto_if_not_defeated 1639, Route50_EventScript_TryWesselBattle
	end

Route50_EventScript_TryWesselBattle::
	goto_if_eq 20639, 6, Route50_EventScript_WesselBattle
	end

Route50_EventScript_WesselBattle::
	lock
	msgbox Route50_Text_WesselBeforeBattle, MSGBOX_AUTOCLOSE
	trainerbattle_no_intro 1639, Route50_Text_WesselDefeat
	giveitem ITEM_IRON_PLATE
	addvar 20640, 1
	msgbox Route50_Text_WesselAfter, MSGBOX_AUTOCLOSE
	call_if_eq 20640, 3, SinjohRuins_Lab_EventScript_3Plates
	call_if_eq 20640, 6, SinjohRuins_Lab_EventScript_6Plates
	call_if_eq 20640, 9, SinjohRuins_Lab_EventScript_9Plates
	call_if_eq 20640, 12, SinjohRuins_Lab_EventScript_12Plates
	call_if_eq 20640, 15, SinjohRuins_Lab_EventScript_15Plates
	call_if_eq 20640, 16, SinjohRuins_Lab_EventScript_16Plates
	release
	end

Route50_EventScript_WesselAfter::
	msgbox Route50_Text_WesselAfter, MSGBOX_NPC
	end

Route50_Text_WesselBefore:
	.string "Incredible{SE_M_SUPERSONIC}{SE_M_BONEMERANG}VOLTORB!\p"
	.string "Bu{SE_M_SPIT_UP}i{SE_M_SPIT_UP}appear{SE_M_GRASSWHISTLE}t{SE_M_ATTRACT2}b{SE_M_REVERSAL}made\n"
	.string "of..{SE_M_PERISH_SONG}Wood?\p"
	.string "M{SE_M_YAWN}hypothesi{SE_M_GRASSWHISTLE}tha{SE_M_SPIT_UP}thi{SE_M_GRASSWHISTLE}route\n"
	.string "woul{SE_M_WATERFALL}contai{SE_M_ATTRACT}man{SE_M_YAWN}STEE{SE_M_BRICK_BREAK}TYPE\l"
	.string "POKéMO{SE_M_PSYBEAM2}i{SE_M_GRASSWHISTLE}disprove{SE_M_ATTRACT}ye{SE_M_SPIT_UP}again.\p"
	.string "Bu{SE_M_SPIT_UP}wh{SE_M_YAWN}els{SE_M_REVERSAL}woul{SE_M_WATERFALL}{SE_M_HEAL_BELL}hav{SE_M_REVERSAL}found\n"
	.string "thi{SE_M_GRASSWHISTLE}STEE{SE_M_BRICK_BREAK}PLAT{SE_M_SWORDS_DANCE}here?\p"
	.string "{SE_M_HEAL_BELL}mus{SE_M_SPIT_UP}collec{SE_M_SPIT_UP}mor{SE_M_REVERSAL}data!$"

Route50_Text_WesselBeforeBattle:
	.string "Yo{SE_M_DIVE}wan{SE_M_SPIT_UP}thi{SE_M_GRASSWHISTLE}PLATE?\n"
	.string "Bu{SE_M_SPIT_UP}{SE_M_HEAL_BELL}haven'{SE_M_SPIT_UP}analyze{SE_M_WATERFALL}i{SE_M_SPIT_UP}yet!\p"
	.string "Fine{SE_M_SUPERSONIC}w{SE_M_REVERSAL}wil{SE_M_BATON_PASS}battl{SE_M_REVERSAL}fo{SE_M_SAND_TOMB}it.$"

Route50_Text_WesselDefeat:
	.string "M{SE_M_YAWN}hypothesi{SE_M_GRASSWHISTLE}wa{SE_M_GRASSWHISTLE}wrong...$"

Route50_Text_WesselAfter:
	.string "Tak{SE_M_REVERSAL}th{SE_M_REVERSAL}PLATE{SE_M_PERISH_SONG}{SE_M_HEAL_BELL}don'{SE_M_SPIT_UP}wan{SE_M_SPIT_UP}to\n"
	.string "tal{SE_M_ENCORE2}abou{SE_M_SPIT_UP}it.$"

Route50_EventScript_Finley::
	goto_if_defeated 1637, Route50_EventScript_FinleyAfter
	msgbox Route50_Text_FinleyBefore, MSGBOX_NPC
	goto_if_not_defeated 1637, Route50_EventScript_TryFinleyBattle
	end

Route50_EventScript_TryFinleyBattle::
	goto_if_eq 20639, 6, Route50_EventScript_FinleyBattle
	end

Route50_EventScript_FinleyBattle::
	lock
	msgbox Route50_Text_FinleyBeforeBattle, MSGBOX_AUTOCLOSE
	trainerbattle_no_intro 1637, Route50_Text_FinleyDefeat
	giveitem ITEM_DRACO_PLATE
	addvar 20640, 1
	msgbox Route50_Text_FinleyAfter, MSGBOX_AUTOCLOSE
	call_if_eq 20640, 3, SinjohRuins_Lab_EventScript_3Plates
	call_if_eq 20640, 6, SinjohRuins_Lab_EventScript_6Plates
	call_if_eq 20640, 9, SinjohRuins_Lab_EventScript_9Plates
	call_if_eq 20640, 12, SinjohRuins_Lab_EventScript_12Plates
	call_if_eq 20640, 15, SinjohRuins_Lab_EventScript_15Plates
	call_if_eq 20640, 16, SinjohRuins_Lab_EventScript_16Plates
	release
	end

Route50_EventScript_FinleyAfter::
	msgbox Route50_Text_FinleyAfter, MSGBOX_NPC
	end

Route50_Text_FinleyBefore:
	.string "Ho{SE_M_TWISTER}ar{SE_M_REVERSAL}th{SE_M_REVERSAL}villager{SE_M_GRASSWHISTLE}treating\n"
	.string "you?\p"
	.string "The{SE_M_YAWN}ca{SE_M_ATTRACT}b{SE_M_REVERSAL}ver{SE_M_YAWN}unwelcomin{SE_M_SANDSTORM}to\n"
	.string "strangers.\p"
	.string "Bu{SE_M_SPIT_UP}meetin{SE_M_SANDSTORM}ne{SE_M_TWISTER}peopl{SE_M_REVERSAL}i{SE_M_GRASSWHISTLE}one\n"
	.string "o{SE_M_ACID_ARMOR}life'{SE_M_GRASSWHISTLE}greates{SE_M_SPIT_UP}joys.\p"
	.string "On{SE_M_REVERSAL}day{SE_M_SUPERSONIC}{SE_M_HEAL_BELL}hop{SE_M_REVERSAL}t{SE_M_ATTRACT2}mee{SE_M_SPIT_UP}CHAMPION\n"
	.string "LANCE.\p"
	.string "H{SE_M_REVERSAL}i{SE_M_GRASSWHISTLE}{SE_M_CHARGE}legendar{SE_M_YAWN}drago{SE_M_ATTRACT}tamer,\n"
	.string "muc{SE_M_TRI_ATTACK}lik{SE_M_REVERSAL}myself.\l"
	.string "Wh{SE_M_ATTRACT2}a{SE_M_MILK_DRINK}I?\p"
	.string "Well{SE_M_SUPERSONIC}{SE_M_HEAL_BELL}a{SE_M_MILK_DRINK}FINLEY{SE_M_SUPERSONIC}keepe{SE_M_SAND_TOMB}o{SE_M_ACID_ARMOR}the\n"
	.string "DRAC{SE_M_SOLAR_BEAM}PLATE.$"

Route50_Text_FinleyBeforeBattle:
	.string "{SE_M_HEAL_BELL}kno{SE_M_TWISTER}th{SE_M_REVERSAL}KIMONO'{SE_M_GRASSWHISTLE}hav{SE_M_REVERSAL}sen{SE_M_SPIT_UP}you\n"
	.string "t{SE_M_ATTRACT2}collec{SE_M_SPIT_UP}thes{SE_M_REVERSAL}PLATES.\p"
	.string "The{SE_M_YAWN}sa{SE_M_YAWN}yo{SE_M_DIVE}ar{SE_M_REVERSAL}worthy...\n"
	.string "Bu{SE_M_SPIT_UP}ca{SE_M_ATTRACT}yo{SE_M_DIVE}conque{SE_M_SAND_TOMB}m{SE_M_YAWN}dragons?$"

Route50_Text_FinleyDefeat:
	.string "M{SE_M_YAWN}dragon{SE_M_GRASSWHISTLE}fough{SE_M_SPIT_UP}well.$"

Route50_Text_FinleyAfter:
	.string "Perhap{SE_M_GRASSWHISTLE}yo{SE_M_DIVE}ar{SE_M_REVERSAL}eve{SE_M_ATTRACT}stron{SE_M_SANDSTORM}enough\n"
	.string "t{SE_M_ATTRACT2}bea{SE_M_SPIT_UP}LANCE...$"

Route50_EventScript_Item_ULtraBall::
	finditem ITEM_ULTRA_BALL
	end

Route50_EventScript_Item_Big_Nugget::
	finditem ITEM_BIG_NUGGET
	end

Route50_EventScript_ActivateKleavor::
	lock
	setobjectxyperm 1, 75, 12
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
	addobject 1
	clearflag 9121
	applymovement2 1, Route50_Movement_KleavorEntrance1
	delay 10
	playmoncry 900, 0
	waitmoncry
	playmoncry 900, 0
	waitmoncry
	waitmovement 0
	applymovement2 1, Route50_Movement_KleavorEntrance2
	delay 10
	playse 10
	delay 20
	waitmovement 1
	setvar 32772, 1
	setvar 32773, 1
	setvar 32774, 5
	setvar 32775, 2
	special ShakeCamera
	setobjectxyperm 1, 75, 14
	setvar 20649, 2
	release
	end

Route50_Movement_KleavorEntrance1:
	jump_in_place_down
	walk_in_place_fast_down
	walk_in_place_fast_down
	step_end

Route50_Movement_KleavorEntrance2:
	jump_2_down
	walk_in_place_slow_down
	walk_in_place_slow_down
	jump_in_place_down
	step_end

Route50_EventScript_Kleavor::
	lock
	faceplayer
	playmoncry 900, 2
	waitmoncry
	setwildbossbattle species=900, level=80, item=ITEM_SCOPE_LENS, move1_1=MOVE_STONE_AXE, move1_2=MOVE_CROSS_POISON, move1_3=MOVE_LUNGE move1_4=MOVE_FOCUS_ENERGY
	settotemboost B_POSITION_OPPONENT_LEFT, 1, 2, 0, 0, 2, 0
	setflag 2411
	setflag 2410
	setflag 2409
	setflag 8804
	dowildbattle
	specialvar 32781, GetBattleOutcome
	goto_if_eq 32781, 4, Route50_EventScript_KleavorRan
	bufferspeciesname STR_VAR_1, 900
	msgbox SinjohRuins_Lab_Text_DropedItem, MSGBOX_DEFAULT
	giveitem ITEM_INSECT_PLATE
	addvar 20640, 1
	fadescreenswapbuffers 1
	removeobject 1
	setflag 9121
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

Route50_EventScript_KleavorRan::
	clearflag 2411
	clearflag 2410
	clearflag 2409
	clearflag 8804
	release
	end

Route50_EventScript_ActivateElectrode::
	lock
	setobjectxyperm 29, 18, 26
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
	addobject 29
	clearflag 9120
	applymovement2 29, Route50_Movement_ElectrodeEntrance1
	delay 10
	playmoncry 996, 0
	waitmoncry
	playmoncry 996, 0
	waitmoncry
	waitmovement 0
	applymovement2 29, Route50_Movement_ElectrodeEntrance2
	delay 10
	playse 10
	delay 20
	waitmovement 0
	setvar 32772, 1
	setvar 32773, 1
	setvar 32774, 5
	setvar 32775, 2
	special ShakeCamera
	applymovement2 29, Route50_Movement_ElectrodeEntrance3
	waitmovement 29
	removeobject 29
	delay 20
	setobjectxyperm 29, 14, 31
	addobject 29
	clearflag 9120
	setvar 20650, 2
	release
	end

Route50_Movement_ElectrodeEntrance1:
	walk_right
	jump_in_place_right
	walk_in_place_fast_right
	walk_in_place_fast_right
	step_end

Route50_Movement_ElectrodeEntrance2:
	jump_2_right
	walk_in_place_slow_up
	walk_in_place_slow_up
	jump_in_place_down
	step_end

Route50_Movement_ElectrodeEntrance3:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

Route50_EventScript_Electrode::
	lock
	faceplayer
	playmoncry 996, 2
	waitmoncry
	setwildbossbattle species=996, level=80, item=ITEM_BRIGHT_POWDER, move1_1=MOVE_FOUL_PLAY, move1_2=MOVE_ELECTRO_BALL, move1_3=MOVE_ENERGY_BALL move1_4=MOVE_CHLOROBLAST
	settotemboost B_POSITION_OPPONENT_LEFT, 0, 3, 1, 0, 3, 0
	setflag 2411
	setflag 2410
	setflag 2409
	setflag 8804
	dowildbattle
	specialvar 32781, GetBattleOutcome
	goto_if_eq 32781, 4, Route50_EventScript_ElectrodeRan
	bufferspeciesname STR_VAR_1, 996
	msgbox SinjohRuins_Lab_Text_DropedItem, MSGBOX_DEFAULT
	giveitem ITEM_ZAP_PLATE
	addvar 20640, 1
	fadescreenswapbuffers 1
	removeobject 29
	setflag 9120
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

Route50_EventScript_ElectrodeRan::
	clearflag 2411
	clearflag 2410
	clearflag 2409
	clearflag 8804
	release
	end

