@ Johto (data/maps/TohjoFalls_GiovanniRoom_hns/scripts.inc), as built into the FireRed game.

TohjoFalls_GiovanniRoom_hns_MapScripts::
	map_script 3, TohjoFalls_GiovanniRoom_OnTransition
	.byte 0

TohjoFalls_GiovanniRoom_OnTransition::
	specialvar 32781, CheckCelebi
	goto_if_eq 32781, TRUE, TohjoFalls_GiovanniRoom_SetScene
	setvar 20605, 0
	end

TohjoFalls_GiovanniRoom_SetScene::
	setflag 8410
	goto_if_ne 20605, 0, TohjoFalls_GiovanniRoom_DoNothing
	setvar 20605, 1
	end

TohjoFalls_GiovanniRoom_DoNothing::
	end

TohjoFalls_GiovanniRoom_EventScript_Radio::
	msgbox TohjoFalls_GiovanniRoom_Text_RadioObject, MSGBOX_SIGN
	end

TohjoFalls_GiovanniRoom_Text_RadioObject::
	.string "{SE_M_BONEMERANG}radio...\n"
	.string "Th{SE_M_REVERSAL}batter{SE_M_YAWN}i{SE_M_GRASSWHISTLE}dead...$"

TohjoFalls_GiovanniRoom_CancelScene::
	setvar 20605, 0
	end

TohjoFalls_EventScript_GiovanniSceneRight::
	specialvar 32781, CheckCelebi
	goto_if_eq 32781, FALSE, TohjoFalls_GiovanniRoom_CancelScene
	lock
	applymovement2 255, J_Common_Movement_WalkLeft1
	waitmovement 0
	applymovement2 255, J_Common_Movement_WalkUp1
	waitmovement 0
	goto TohjoFalls_EventScript_GiovanniScene

TohjoFalls_EventScript_GiovanniSceneLeft::
	specialvar 32781, CheckCelebi
	goto_if_eq 32781, FALSE, TohjoFalls_GiovanniRoom_CancelScene
	lock
	applymovement2 255, J_Common_Movement_WalkRight1
	waitmovement 0
	applymovement2 255, J_Common_Movement_WalkUp1
	waitmovement 0
	goto TohjoFalls_EventScript_GiovanniScene

TohjoFalls_EventScript_GiovanniScene::
	specialvar 32781, CheckCelebi
	goto_if_eq 32781, FALSE, TohjoFalls_GiovanniRoom_CancelScene
	lock
	applymovement2 0xFE, TohjoFalls_Movement_CelebiBegin
	playse 10
	waitse
	playse 10
	waitse
	waitmovement 0
	playse 21
	applymovement2 255, J_Common_Movement_ExclamationMark
	waitmovement 255
	turnobject 255, DIR_SOUTH
	delay 20
	playse 21
	applymovement2 255, J_Common_Movement_QuestionMark
	waitmovement 255
	applymovement2 0xFE, TohjoFalls_Movement_CelebiSpin
	playse 10
	waitse
	playse 10
	waitse


	playse 10
	waitse
	playse 10
	waitmovement 0
	fadescreen 3
	playse 203
	waitse
	delay 60
	playse 203
	waitse
	clearflag 8410
	addobject 1
	waitse
	playbgm ((558 + 1) + 0x3F), FALSE
	fadescreen 2
	delay 50
	turnobject 255, DIR_NORTH
	msgbox TohjoFalls_GiovanniRoom_Text_Radio, MSGBOX_DEFAULT
	closemessage
	applymovement2 255, J_Common_Movement_WalkUp1
	applymovement2 0xFE, J_Common_Movement_WalkUp1
	waitmovement 0
	waitmovement 0xFE
	playse 21
	applymovement2 1, J_Common_Movement_ExclamationMark
	delay 55
	waitmovement 1
	turnobject 1, DIR_SOUTH
	msgbox TohjoFalls_GiovanniRoom_Text_GiovanniIntro, MSGBOX_DEFAULT
	applymovement2 1, J_Common_Movement_WalkDown1
	waitmovement 0
	msgbox TohjoFalls_GiovanniRoom_Text_GiovanniBeforeBattle, MSGBOX_DEFAULT
	trainerbattle_no_intro 1490, TohjoFalls_GiovanniRoom_Text_GiovanniDefeat
	playbgm ((558 + 1) + 0x3F), FALSE
	applymovement2 1, TohjoFalls_Movement_GiovanniTakenAback
	waitmovement 0
	msgbox TohjoFalls_GiovanniRoom_Text_GiovanniAfter, MSGBOX_DEFAULT
	closemessage
	applymovement2 1, TohjoFalls_Movement_GiovanniLeave
	waitmovement 0
	fadescreen 1
	removeobject 1
	playse 9
	fadescreen 0
	delay 30

	applymovement2 0xFE, TohjoFalls_Movement_CelebiBegin
	playse 10
	waitse
	playse 10
	waitse
	waitmovement 0
	playse 21
	applymovement2 255, J_Common_Movement_ExclamationMark
	waitmovement 255
	turnobject 255, DIR_SOUTH
	delay 20
	playse 21
	applymovement2 255, J_Common_Movement_QuestionMark
	waitmovement 255
	applymovement2 0xFE, TohjoFalls_Movement_CelebiSpin
	playse 10
	waitse
	playse 10
	waitse


	playse 10
	waitse
	playse 10
	waitmovement 0
	fadescreen 3
	playse 203
	waitse
	delay 60
	playse 203
	waitse
	fadedefaultbgm
	fadescreen 2
	setvar 20605, 2
	release
	end

TohjoFalls_Movement_CelebiBegin:
	jump_in_place_up
	jump_in_place_up
	step_end

TohjoFalls_Movement_CelebiSpin:
	jump_in_place_up
	jump_in_place_up
	jump_in_place_up
	jump_in_place_up
	step_end

TohjoFalls_Movement_GiovanniTakenAback:
	lock_facing_direction
	walk_slow_up
	unlock_facing_direction
	walk_slow_right
	walk_slow_right
	step_end

TohjoFalls_Movement_GiovanniLeave:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	face_down
	walk_in_place_down
	step_end

TohjoFalls_GiovanniRoom_Text_Radio:
	.string "RADIO{SE_M_HEAT_WAVE}..{SE_M_PERISH_SONG}...\n"
	.string "Ahem{SE_M_SUPERSONIC}w{SE_M_REVERSAL}ar{SE_M_REVERSAL}TEA{SE_M_GIGA_DRAIN}ROCKET!\l"
	.string "Afte{SE_M_SAND_TOMB}thre{SE_M_REVERSAL}year{SE_M_GRASSWHISTLE}o{SE_M_ACID_ARMOR}preparation,\l"
	.string "w{SE_M_REVERSAL}hav{SE_M_REVERSAL}rise{SE_M_ATTRACT}agai{SE_M_ATTRACT}fro{SE_M_MILK_DRINK}th{SE_M_REVERSAL}ashes!\l"
	.string "GIOVANNI{SE_M_DRAGON_RAGE}Ca{SE_M_ATTRACT}yo{SE_M_DIVE}hea{SE_M_SAND_TOMB}us?\l"
	.string "W{SE_M_REVERSAL}di{SE_M_WATERFALL}it!\l"
	.string "Wher{SE_M_REVERSAL}i{SE_M_GRASSWHISTLE}ou{SE_M_SAND_TOMB}boss?\l"
	.string "I{SE_M_GRASSWHISTLE}h{SE_M_REVERSAL}listening?$"

TohjoFalls_GiovanniRoom_Text_GiovanniIntro:
	.string "GIOVANNI{SE_M_HEAT_WAVE}...\p"
	.string "{SE_M_HEAL_BELL}don'{SE_M_SPIT_UP}kno{SE_M_TWISTER}wh{SE_M_YAWN}yo{SE_M_DIVE}hav{SE_M_REVERSAL}come\n"
	.string "here.\p"
	.string "Anyway{SE_M_SUPERSONIC}{SE_M_HEAL_BELL}hav{SE_M_REVERSAL}t{SE_M_ATTRACT2}war{SE_M_ATTRACT}yo{SE_M_DIVE}that\n"
	.string "thi{SE_M_GRASSWHISTLE}i{SE_M_GRASSWHISTLE}no{SE_M_SPIT_UP}{SE_M_CHARGE}plac{SE_M_REVERSAL}fo{SE_M_SAND_TOMB}kid{SE_M_GRASSWHISTLE}like\l"
	.string "you.\p"
	.string "Yo{SE_M_DIVE}hav{SE_M_REVERSAL}{SE_M_CHARGE}certai{SE_M_ATTRACT}look.\n"
	.string "I{SE_M_SPIT_UP}remind{SE_M_GRASSWHISTLE}m{SE_M_REVERSAL}o{SE_M_ACID_ARMOR}th{SE_M_REVERSAL}ki{SE_M_WATERFALL}wh{SE_M_ATTRACT2}stood\l"
	.string "i{SE_M_ATTRACT}fron{SE_M_SPIT_UP}o{SE_M_ACID_ARMOR}m{SE_M_REVERSAL}thre{SE_M_REVERSAL}year{SE_M_GRASSWHISTLE}ago...\p"
	.string "Yo{SE_M_DIVE}hav{SE_M_REVERSAL}th{SE_M_REVERSAL}sam{SE_M_REVERSAL}eyes...\p"
	.string "...\p"
	.string "I'{SE_M_MILK_DRINK}o{SE_M_ATTRACT}m{SE_M_YAWN}wa{SE_M_YAWN}t{SE_M_ATTRACT2}GOLDENRO{SE_M_FAINT_ATTACK}CITY\n"
	.string "t{SE_M_ATTRACT2}answe{SE_M_SAND_TOMB}th{SE_M_REVERSAL}cal{SE_M_BATON_PASS}an{SE_M_WATERFALL}joi{SE_M_ATTRACT}m{SE_M_YAWN}team.\l"
	.string "Ar{SE_M_REVERSAL}yo{SE_M_DIVE}goin{SE_M_SANDSTORM}t{SE_M_ATTRACT2}ge{SE_M_SPIT_UP}i{SE_M_ATTRACT}m{SE_M_YAWN}way?$"

TohjoFalls_GiovanniRoom_Text_GiovanniBeforeBattle:
	.string "M{SE_M_YAWN}ol{SE_M_WATERFALL}associate{SE_M_GRASSWHISTLE}nee{SE_M_WATERFALL}me...\n"
	.string "W{SE_M_REVERSAL}wil{SE_M_BATON_PASS}no{SE_M_SPIT_UP}repea{SE_M_SPIT_UP}th{SE_M_REVERSAL}failur{SE_M_REVERSAL}of\l"
	.string "thre{SE_M_REVERSAL}year{SE_M_GRASSWHISTLE}ago!$"

TohjoFalls_GiovanniRoom_Text_GiovanniDefeat:
	.string "Wha{SE_M_SPIT_UP}i{SE_M_ATTRACT}th{SE_M_REVERSAL}worl{SE_M_WATERFALL}ar{SE_M_REVERSAL}you?$"

TohjoFalls_GiovanniRoom_Text_GiovanniAfter:
	.string "GIOVANNI{SE_M_HEAT_WAVE}Ho{SE_M_TWISTER}i{SE_M_GRASSWHISTLE}thi{SE_M_GRASSWHISTLE}possible...?\n"
	.string "Th{SE_M_REVERSAL}pas{SE_M_SPIT_UP}thre{SE_M_REVERSAL}year{SE_M_GRASSWHISTLE}hav{SE_M_REVERSAL}bee{SE_M_ATTRACT}a\l"
	.string "waste...?\p"
	.string "Ho{SE_M_TWISTER}ca{SE_M_ATTRACT}{SE_M_CHARGE}ki{SE_M_WATERFALL}lik{SE_M_REVERSAL}yo{SE_M_DIVE}manag{SE_M_REVERSAL}to\n"
	.string "destro{SE_M_YAWN}m{SE_M_YAWN}drea{SE_M_MILK_DRINK}onc{SE_M_REVERSAL}again?\p"
	.string "Th{SE_M_REVERSAL}preciou{SE_M_GRASSWHISTLE}drea{SE_M_MILK_DRINK}o{SE_M_ACID_ARMOR}TEA{SE_M_GIGA_DRAIN}ROCKET\n"
	.string "ha{SE_M_GRASSWHISTLE}becom{SE_M_REVERSAL}littl{SE_M_REVERSAL}mor{SE_M_REVERSAL}tha{SE_M_ATTRACT}an\l"
	.string "illusion...$"

