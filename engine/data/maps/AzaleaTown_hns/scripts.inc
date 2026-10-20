@ Johto (data/maps/AzaleaTown_hns/scripts.inc), as built into the FireRed game.

AzaleaTown_hns_MapScripts::
	map_script 3, AzaleaTown_OnTransition
	map_script 2, AzaleaTown_OnFrame
	.byte 0

AzaleaTown_OnTransition::
	goto_if_eq 20547, 5, AzaleaTown_MapScript_Hide_Silver
	end

AzaleaTown_OnFrame::
	map_script_2 20547, 8, AzaleaTown_EventScript_GSBall
	.2byte 0

AzaleaTown_MapScript_Hide_Silver:
	setflag 8284
	removeobject 6
	end

AzaleaTown_EventScript_Trigger::
	setflag 10483
	setflag 8230
	setflag 8284
	setflag 8293
	setflag 8287
	setflag 8290
	setflag 8237
	setflag 8236
	setflag 8235
	setflag 8234
	setflag 8255
	setflag 8289
	setflag 8282
	setflag 8231
	setflag 8232
	setflag 8233


	clearflag 8288
	clearflag 8439
	clearflag 8283
	clearflag 8285
	clearflag 8292
	clearflag 8725
	clearflag 8229
	clearflag 8281
	clearflag 8781

	removeitem 684
	setvar 20547, 1
	end

AzaleaTown_EventScript_Rocket1::
	lock
	faceplayer
	msgbox AzaleaTown_Text_Rocket1, MSGBOX_DEFAULT
	closemessage
	release
	end

AzaleaTown_EventScript_Rocket2::
	lock
	faceplayer
	msgbox AzaleaTown_Text_Rocket2, MSGBOX_DEFAULT
	closemessage
	release
	end

AzaleaTown_EventScript_Gramps::
	lock
	faceplayer
	goto_if_set 8283, AzaleaTown_EventScript_Gramps2
	msgbox AzaleaTown_Text_GrampsBefore, MSGBOX_DEFAULT
	closemessage
	release
	end

AzaleaTown_EventScript_Gramps2::
	msgbox AzaleaTown_Text_GrampsAfter, MSGBOX_DEFAULT
	closemessage
	release
	end

AzaleaTown_EventScript_Lass::
	lock
	faceplayer
	msgbox AzaleaTown_Text_Teacher, MSGBOX_DEFAULT
	closemessage
	release
	end

AzaleaTown_EventScript_Youngster::
	lock
	faceplayer
	msgbox AzaleaTown_Text_Youngster, MSGBOX_DEFAULT
	closemessage
	release
	end

AzaleaTown_EventScript_Slowpoke::
	lock
	faceplayer
	waitse
	playmoncry 79, 0
	msgbox AzaleaTown_Text_Slowpoke1, MSGBOX_DEFAULT
	waitmoncry
	release
	end

AzaleaTown_EventScript_GymSign::
	lock
	msgbox AzaleaTown_Text_GymSign, MSGBOX_SIGN
	closemessage
	release
	end

AzaleaTown_EventScript_KurtSign::
	lock
	msgbox AzaleaTown_Text_KurtsHouseSign, MSGBOX_SIGN
	closemessage
	release
	end

AzaleaTown_EventScript_KilnSign::
	lock
	msgbox AzaleaTown_Text_CharcoalKilnSign, MSGBOX_SIGN
	closemessage
	release
	end

AzaleaTown_EventScript_IlexSign::
	lock
	msgbox AzaleaTown_Text_IlexForestSign, MSGBOX_SIGN
	closemessage
	release
	end

AzaleaTown_EventScript_WellSign::
	lock
	msgbox AzaleaTown_Text_SlowpokeWellSign, MSGBOX_SIGN
	closemessage
	release
	end

AzaleaTown_EventScript_AzaleaSign::
	lock
	msgbox AzaleaTown_Text_Sign, MSGBOX_SIGN
	closemessage
	release
	end

AzaleaTown_EventScript_SilverTriggerTop::
	lock
	clearflag 8284
	addobject 6
	playbgm ((558 + 1) + 0x3B), FALSE
	applymovement 6, AzaleaTown_Movement_Silver_EnterTop
	waitmovement 0
	turnobject 255, DIR_EAST
	msgbox AzaleaTown_Text_RivalBefore, MSGBOX_DEFAULT
	closemessage
	call_if_eq 20499, 0, AzaleaTown_Silver_Battle_Cyndaquil
	call_if_eq 20499, 1, AzaleaTown_Silver_Battle_Totodile
	call_if_eq 20499, 2, AzaleaTown_Silver_Battle_Chikorita
	msgbox AzaleaTown_Text_RivalAfter, MSGBOX_DEFAULT
	closemessage
	applymovement 255, AzaleaTown_Movement_Player_LeaveTop
	waitmovement 0
	applymovement 6, AzaleaTown_Movement_Silver_LeaveTop
	waitmovement 0
	playse 9
	setflag 8284
	removeobject 6
	setvar 20547, 6
	fadedefaultbgm
	release
	end

AzaleaTown_EventScript_SilverTriggerBot::
	lock
	clearflag 8284
	addobject 6
	playbgm ((558 + 1) + 0x3B), FALSE
	applymovement 6, AzaleaTown_Movement_Silver_EnterBot
	waitmovement 0
	turnobject 255, DIR_EAST
	msgbox AzaleaTown_Text_RivalBefore, MSGBOX_DEFAULT
	closemessage
	call_if_eq 20499, 0, AzaleaTown_Silver_Battle_Cyndaquil
	call_if_eq 20499, 1, AzaleaTown_Silver_Battle_Totodile
	call_if_eq 20499, 2, AzaleaTown_Silver_Battle_Chikorita
	playbgm ((558 + 1) + 0x3C), FALSE
	msgbox AzaleaTown_Text_RivalAfter, MSGBOX_DEFAULT
	closemessage
	applymovement 255, AzaleaTown_Movement_Player_LeaveBot
	waitmovement 0
	applymovement 6, AzaleaTown_Movement_Silver_LeaveBot
	waitmovement 0
	playse 9
	setflag 8284
	removeobject 6
	setvar 20547, 6
	fadedefaultbgm
	release
	end

AzaleaTown_Silver_Battle_Cyndaquil::
	trainerbattle_no_intro 1475, AzaleaTown_Text_RivalWin
	return

AzaleaTown_Silver_Battle_Totodile::
	trainerbattle_no_intro 1482, AzaleaTown_Text_RivalWin
	return

AzaleaTown_Silver_Battle_Chikorita::
	trainerbattle_no_intro 1468, AzaleaTown_Text_RivalWin
	return

AzaleaTown_EventScript_GSBall::
	lock
	applymovement 255, AzaleaTown_Movement_PlayerGSBall
	waitmovement 0
	clearflag 8282
	addobject 18
	opendoor 19, 11
	waitdooranim
	waitmovement 0
	closedoor 19, 11
	waitdooranim
	applymovement 18, AzaleaTown_Movement_Kurt2
	playse 202
	waitmovement 0
	msgbox AzaleaTown_Text_Kurt1, MSGBOX_DEFAULT
	closemessage
	playse 202
	msgbox AzaleaTown_Text_Kurt2, MSGBOX_DEFAULT
	giveitem ITEM_GS_BALL
	waitse
	playse 202
	turnobject 18, DIR_WEST
	turnobject 255, DIR_WEST
	playse 202
	waitse
	turnobject 18, DIR_SOUTH
	turnobject 255, DIR_NORTH
	msgbox AzaleaTown_Text_Kurt3, MSGBOX_DEFAULT
	closemessage
	applymovement 18, AzaleaTown_Movement_KurtLeave
	delay 60
	opendoor 19, 11
	waitdooranim
	waitmovement 0
	setflag 8282
	removeobject 18
	closedoor 19, 11
	waitdooranim
	setvar 20547, 9
	release
	end

AzaleaTown_Movement_Silver_EnterTop:
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	step_end

AzaleaTown_Movement_Silver_EnterBot:
	walk_fast_down
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	step_end

AzaleaTown_Movement_Silver_LeaveTop:
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	step_end

AzaleaTown_Movement_Silver_LeaveBot:
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_up
	walk_fast_left
	step_end

AzaleaTown_Movement_Player_LeaveTop:
	lock_facing_direction
	walk_fast_down
	unlock_facing_direction
	face_up
	step_end

AzaleaTown_Movement_Player_LeaveBot:
	lock_facing_direction
	walk_fast_up
	unlock_facing_direction
	face_down
	step_end

AzaleaTown_Movement_Kurt1:
	walk_down
	step_end

AzaleaTown_Movement_Kurt2:
	walk_down
	walk_down
	walk_down
	face_right
	delay_8
	face_left
	delay_8
	face_down
	step_end

AzaleaTown_Movement_PlayerGSBall:
	walk_down
	walk_down
	walk_down
	face_left
	delay_16
	face_right
	delay_8
	face_up
	step_end

AzaleaTown_Movement_KurtLeave:
	walk_up
	walk_up
	walk_up
	step_end

AzaleaTown_Text_RivalBefore:
	.string "…Tel{SE_M_BATON_PASS}m{SE_M_REVERSAL}something.\p"
	.string "I{SE_M_GRASSWHISTLE}i{SE_M_SPIT_UP}tru{SE_M_REVERSAL}tha{SE_M_SPIT_UP}TEA{SE_M_GIGA_DRAIN}ROCKET\n"
	.string "ha{SE_M_GRASSWHISTLE}returned?\p"
	.string "What{SE_M_SING}Yo{SE_M_DIVE}bea{SE_M_SPIT_UP}them{SE_M_SING}Hah{SE_M_DRAGON_RAGE}Quit\n"
	.string "lying.\p"
	.string "You'r{SE_M_REVERSAL}no{SE_M_SPIT_UP}joking?\n"
	.string "The{SE_M_ATTRACT}let'{SE_M_GRASSWHISTLE}se{SE_M_REVERSAL}ho{SE_M_TWISTER}goo{SE_M_WATERFALL}yo{SE_M_DIVE}are.$"

AzaleaTown_Text_RivalWin:
	.string "…Humph{SE_M_DRAGON_RAGE}Useles{SE_M_GRASSWHISTLE}POKéMON!\p"
	.string "Listen{SE_M_SUPERSONIC}you{SE_M_PERISH_SONG}Yo{SE_M_DIVE}onl{SE_M_YAWN}wo{SE_M_ATTRACT}because\n"
	.string "m{SE_M_YAWN}POKéMO{SE_M_PSYBEAM2}wer{SE_M_REVERSAL}weak.$"

AzaleaTown_Text_RivalAfter:
	.string "{SE_M_HEAL_BELL}hat{SE_M_REVERSAL}th{SE_M_REVERSAL}weak.\p"
	.string "POKéMON{SE_M_SUPERSONIC}trainers{SE_M_PERISH_SONG}I{SE_M_SPIT_UP}doesn't\n"
	.string "matte{SE_M_SAND_TOMB}wh{SE_M_ATTRACT2}o{SE_M_SAND_TOMB}what.\p"
	.string "I'{SE_M_MILK_DRINK}goin{SE_M_SANDSTORM}t{SE_M_ATTRACT2}b{SE_M_REVERSAL}stron{SE_M_SANDSTORM}an{SE_M_WATERFALL}wipe\n"
	.string "ou{SE_M_SPIT_UP}th{SE_M_REVERSAL}weak.\p"
	.string "Tha{SE_M_SPIT_UP}goe{SE_M_GRASSWHISTLE}fo{SE_M_SAND_TOMB}TEA{SE_M_GIGA_DRAIN}ROCKE{SE_M_SWIFT}too.\p"
	.string "The{SE_M_YAWN}ac{SE_M_SPIT_UP}bi{SE_M_SANDSTORM}an{SE_M_WATERFALL}toug{SE_M_TRI_ATTACK}i{SE_M_ATTRACT}{SE_M_CHARGE}group.\p"
	.string "Bu{SE_M_SPIT_UP}ge{SE_M_SPIT_UP}the{SE_M_MILK_DRINK}alone{SE_M_SUPERSONIC}an{SE_M_WATERFALL}they'r{SE_M_REVERSAL}weak.\n"
	.string "{SE_M_HEAL_BELL}hat{SE_M_REVERSAL}the{SE_M_MILK_DRINK}all.\p"
	.string "Yo{SE_M_DIVE}sta{SE_M_YAWN}ou{SE_M_SPIT_UP}o{SE_M_ACID_ARMOR}m{SE_M_YAWN}way{SE_M_PERISH_SONG}{SE_M_BONEMERANG}weakling\n"
	.string "lik{SE_M_REVERSAL}yo{SE_M_DIVE}i{SE_M_GRASSWHISTLE}onl{SE_M_YAWN}{SE_M_CHARGE}distraction.$"

AzaleaTown_Text_RivalLoss:
	.string "…Humph{SE_M_DRAGON_RAGE}{SE_M_HEAL_BELL}kne{SE_M_TWISTER}yo{SE_M_DIVE}wer{SE_M_REVERSAL}lying.$"

AzaleaTown_Text_Rocket1:
	.string "It'{SE_M_GRASSWHISTLE}unsaf{SE_M_REVERSAL}t{SE_M_ATTRACT2}g{SE_M_ATTRACT2}i{SE_M_ATTRACT}there,\n"
	.string "s{SE_M_ATTRACT2}I'{SE_M_MILK_DRINK}standin{SE_M_SANDSTORM}guard.\p"
	.string "Aren'{SE_M_SPIT_UP}{SE_M_HEAL_BELL}{SE_M_CHARGE}goo{SE_M_WATERFALL}Samaritan?$"

AzaleaTown_Text_Rocket2:
	.string "D{SE_M_ATTRACT2}yo{SE_M_DIVE}kno{SE_M_TWISTER}abou{SE_M_SPIT_UP}SLOWPOKETAIL?\n"
	.string "{SE_M_HEAL_BELL}hear{SE_M_WATERFALL}it'{SE_M_GRASSWHISTLE}tasty!\p"
	.string "Aren'{SE_M_SPIT_UP}yo{SE_M_DIVE}gla{SE_M_WATERFALL}{SE_M_HEAL_BELL}tol{SE_M_WATERFALL}yo{SE_M_DIVE}that?$"

AzaleaTown_Text_GrampsBefore:
	.string "Th{SE_M_REVERSAL}SLOWPOK{SE_M_SWORDS_DANCE}hav{SE_M_REVERSAL}disappeared\n"
	.string "fro{SE_M_MILK_DRINK}town…\p"
	.string "{SE_M_HEAL_BELL}hear{SE_M_WATERFALL}thei{SE_M_SAND_TOMB}TAIL{SE_M_SKETCH}ar{SE_M_REVERSAL}being\n"
	.string "sol{SE_M_WATERFALL}somewhere.$"

AzaleaTown_Text_GrampsAfter:
	.string "Th{SE_M_REVERSAL}SLOWPOK{SE_M_SWORDS_DANCE}hav{SE_M_REVERSAL}returned.\p"
	.string "Knowin{SE_M_SANDSTORM}them{SE_M_SUPERSONIC}the{SE_M_YAWN}could'v{SE_M_REVERSAL}just\n"
	.string "bee{SE_M_ATTRACT}goofin{SE_M_SANDSTORM}of{SE_M_ACID_ARMOR}somewhere.$"

AzaleaTown_Text_Teacher:
	.string "Di{SE_M_WATERFALL}yo{SE_M_DIVE}com{SE_M_REVERSAL}t{SE_M_ATTRACT2}ge{SE_M_SPIT_UP}KUR{SE_M_SWIFT}t{SE_M_ATTRACT2}make\n"
	.string "som{SE_M_REVERSAL}BALLS?\p"
	.string "{SE_M_BONEMERANG}lo{SE_M_SPIT_UP}o{SE_M_ACID_ARMOR}peopl{SE_M_REVERSAL}d{SE_M_ATTRACT2}jus{SE_M_SPIT_UP}that.$"

AzaleaTown_Text_Youngster:
	.string "Cu{SE_M_SPIT_UP}throug{SE_M_TRI_ATTACK}AZALE{SE_M_BONEMERANG}an{SE_M_WATERFALL}you'l{SE_M_BATON_PASS}be\n"
	.string "i{SE_M_ATTRACT}ILE{SE_M_LOCK_ON}FOREST.\p"
	.string "Bu{SE_M_SPIT_UP}thes{SE_M_REVERSAL}skinn{SE_M_YAWN}tree{SE_M_GRASSWHISTLE}mak{SE_M_REVERSAL}it\n"
	.string "impossibl{SE_M_REVERSAL}t{SE_M_ATTRACT2}ge{SE_M_SPIT_UP}through.\p"
	.string "Th{SE_M_REVERSAL}CHARCOA{SE_M_BRICK_BREAK}MAN'{SE_M_GRASSWHISTLE}POKéMON\n"
	.string "ca{SE_M_ATTRACT}CU{SE_M_SWIFT}dow{SE_M_ATTRACT}trees.$"

AzaleaTown_Text_Slowpoke1:
	.string "SLOWPOKE:..........\p"
	.string "...............YAWN?$"

AzaleaTown_Text_Kurt1:
	.string "ILE{SE_M_LOCK_ON}FORES{SE_M_SWIFT}i{SE_M_GRASSWHISTLE}restless!\p"
	.string "Wha{SE_M_SPIT_UP}i{SE_M_GRASSWHISTLE}goin{SE_M_SANDSTORM}on?$"

AzaleaTown_Text_Kurt2:
	.string "{PLAYER}{SE_M_SUPERSONIC}here'{SE_M_GRASSWHISTLE}you{SE_M_SAND_TOMB}G{SE_M_SKETCH}BAL{SE_M_BRICK_BREAK}back!$"

AzaleaTown_Text_Kurt3:
	.string "Coul{SE_M_WATERFALL}yo{SE_M_DIVE}g{SE_M_ATTRACT2}se{SE_M_REVERSAL}wh{SE_M_YAWN}ILE{SE_M_LOCK_ON}FOREST\n"
	.string "i{SE_M_GRASSWHISTLE}s{SE_M_ATTRACT2}restless?$"

AzaleaTown_Text_Sign:
	.string "AZALE{SE_M_BONEMERANG}TOWN\n"
	.string "Wher{SE_M_REVERSAL}Peopl{SE_M_REVERSAL}an{SE_M_WATERFALL}POKéMO{SE_M_PSYBEAM2}Liv{SE_M_REVERSAL}in\l"
	.string "Happ{SE_M_YAWN}Harmony.$"

AzaleaTown_Text_KurtsHouseSign:
	.string "KURT'{SE_M_SKETCH}HOUSE$"

AzaleaTown_Text_GymSign:
	.string "AZALE{SE_M_BONEMERANG}TOWN\n"
	.string "POKéMO{SE_M_PSYBEAM2}GYM\p"
	.string "LEADER{SE_M_HEAT_WAVE}BUGSY\p"
	.string "Th{SE_M_REVERSAL}Walkin{SE_M_SANDSTORM}Bu{SE_M_SANDSTORM}POKéMON\n"
	.string "Encyclopedia$"

AzaleaTown_Text_SlowpokeWellSign:
	.string "SLOWPOK{SE_M_SWORDS_DANCE}WELL\p"
	.string "Als{SE_M_ATTRACT2}know{SE_M_ATTRACT}a{SE_M_GRASSWHISTLE}th{SE_M_REVERSAL}RAINMAKE{SE_M_MINIMIZE}WELL.\p"
	.string "Local{SE_M_GRASSWHISTLE}believ{SE_M_REVERSAL}tha{SE_M_SPIT_UP}{SE_M_CHARGE}SLOWPOKE's\n"
	.string "yaw{SE_M_ATTRACT}summon{SE_M_GRASSWHISTLE}rain.\p"
	.string "Record{SE_M_GRASSWHISTLE}sho{SE_M_TWISTER}tha{SE_M_SPIT_UP}{SE_M_CHARGE}SLOWPOKE's\n"
	.string "yaw{SE_M_ATTRACT}ende{SE_M_WATERFALL}{SE_M_CHARGE}drough{SE_M_SPIT_UP}40{SE_M_BITE}year{SE_M_GRASSWHISTLE}ago.$"

AzaleaTown_Text_CharcoalKilnSign:
	.string "CHARCOA{SE_M_BRICK_BREAK}KILN$"

AzaleaTown_Text_IlexForestSign:
	.string "ILE{SE_M_LOCK_ON}FOREST\p"
	.string "Ente{SE_M_SAND_TOMB}throug{SE_M_TRI_ATTACK}th{SE_M_REVERSAL}gate.$"

