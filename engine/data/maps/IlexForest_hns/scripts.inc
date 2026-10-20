@ Johto (data/maps/IlexForest_hns/scripts.inc), as built into the FireRed game.

IlexForest_hns_MapScripts::
	map_script 3, IlexForest_OnTransition
	map_script 5, J_SetTimeEncounters
	.byte 0

IlexForest_OnTransition:
	call_if_eq 20571, 1, IlexForest_EventScript_ReenterWhenFarfetchdLeaving
	call_if_eq 20571, 2, IlexForest_EventScript_ReenterDuringCutScene
	callnative SetTimeBasedEncounters
	end

IlexForest_EventScript_ReenterWhenFarfetchdLeaving::
	setobjectxyperm 3, 33, 51
	return

IlexForest_EventScript_ReenterDuringCutScene::
	clearflag 8290
	clearflag 8287
	setobjectxyperm 3, 28, 42
	return

IlexForest_EventScript_Apprentice::
	lock
	faceplayer
	goto_if_eq 20571, 2, IlexForest_EventScript_Apprentice2
	goto_if_eq 20571, 3, IlexForest_EventScript_Apprentice2
	msgbox IlexForest_Text_ApprenticeIntro, MSGBOX_DEFAULT
	closemessage
	release
	end

IlexForest_EventScript_Apprentice2::
	msgbox IlexForest_Text_ApprenticeAfter, MSGBOX_DEFAULT
	closemessage
	release
	end

IlexForest_EventScript_Boss::
	lock
	faceplayer
	msgbox IlexForest_Text_CharcoalMasterTalkAfter, MSGBOX_DEFAULT
	closemessage
	release
	end

IlexForest_EventScript_Farfetchd_1A::
	lock
	faceplayer
	playmoncry 83, 0
	msgbox IlexForest_Text_Kwaaaa, MSGBOX_DEFAULT
	waitmoncry
	closemessage
	goto_if_eq 20571, 3, IlexForest_EventScript_Farfetchd_Done
	goto_if_eq 20571, 2, IlexForest_EventScript_Farfetchd_Done
	goto_if_eq 20571, 1, IlexForest_EventScript_Farfetchd_Leave
	goto_if_eq 32780, DIR_SOUTH, IlexForest_EventScript_Farfetchd_1B
	applymovement 3, IlexForest_Movement_Farfetchd_1A
	waitmovement 0
	setflag 8234
	removeobject 3

	clearflag 8235
	addobject 30
	release
	end

IlexForest_EventScript_Farfetchd_1B::
	applymovement 3, IlexForest_Movement_Farfetchd_1B
	waitmovement 0
	setvar 20571, 1
	setobjectxyperm 3, 33, 51
	release
	end

IlexForest_EventScript_Farfetchd_2A::
	lock
	faceplayer
	playmoncry 83, 0
	msgbox IlexForest_Text_Kwaaaa, MSGBOX_DEFAULT
	waitmoncry
	closemessage
	goto_if_eq 32780, DIR_SOUTH, IlexForest_EventScript_Farfetchd_2B
	applymovement 30, IlexForest_Movement_Farfetchd_2A
	waitmovement 0
	setflag 8235
	removeobject 30

	clearflag 8236
	addobject 32
	release
	end

IlexForest_EventScript_Farfetchd_2B::
	applymovement 30, IlexForest_Movement_Farfetchd_2B
	waitmovement 0
	setflag 8235
	removeobject 30

	clearflag 8234
	addobject 3
	release
	end

IlexForest_EventScript_Farfetchd_3A::
	lock
	faceplayer
	playmoncry 83, 0
	msgbox IlexForest_Text_Kwaaaa, MSGBOX_DEFAULT
	waitmoncry
	closemessage
	goto_if_eq 32780, DIR_SOUTH, IlexForest_EventScript_Farfetchd_3B
	applymovement 32, IlexForest_Movement_Farfetchd_3A
	waitmovement 0
	setflag 8236
	removeobject 32

	clearflag 8235
	addobject 30
	release
	end

IlexForest_EventScript_Farfetchd_3B::
	applymovement 32, IlexForest_Movement_Farfetchd_3B
	waitmovement 0
	setflag 8236
	removeobject 32

	clearflag 8237
	addobject 31
	release
	end

IlexForest_EventScript_Farfetchd_4A::
	lock
	faceplayer
	playmoncry 83, 0
	msgbox IlexForest_Text_Kwaaaa, MSGBOX_DEFAULT
	waitmoncry
	closemessage
	goto_if_eq 32780, DIR_SOUTH, IlexForest_EventScript_Farfetchd_4B
	applymovement 31, IlexForest_Movement_Farfetchd_4A
	waitmovement 0
	setflag 8237
	removeobject 31

	clearflag 8236
	addobject 32
	release
	end

IlexForest_EventScript_Farfetchd_4B::
	applymovement 31, IlexForest_Movement_Farfetchd_4B
	waitmovement 0
	setflag 8237
	removeobject 31

	clearflag 8234
	addobject 3
	release
	end

IlexForest_EventScript_Farfetchd_Leave::
	goto_if_eq 32780, DIR_EAST, IlexForest_EventScript_Farfetchd_Return
	goto_if_eq 32780, DIR_SOUTH, IlexForest_EventScript_Farfetchd_Return
	applymovement 3, IlexForest_Movement_Farfetchd_Leave
	waitmovement 0
	setobjectxyperm 3, 28, 42
	setvar 20571, 2
	clearflag 8288
	clearflag 8290
	setflag 8281
	addobject 1
	release
	end

IlexForest_EventScript_Farfetchd_Return::
	setvar 20571, 0
	applymovement 3, IlexForest_Movement_Farfetchd_Return
	waitmovement 0
	setobjectxyperm 3, 42, 47
	release
	end

IlexForest_EventScript_Farfetchd_Done::
	release
	end

IlexForest_EventScript_TriggerBot::
	lock
	applymovement 255 J_Common_Movement_WalkUp
	waitmovement 0

IlexForest_EventScript_Trigger::
	lock
	turnobject 255, DIR_NORTH
	msgbox IlexForest_Text_CharcoalMasterIntro, MSGBOX_DEFAULT
	closemessage
	giveitem 682
	goto_if_eq 32781, FALSE, J_Common_EventScript_BagIsFull
	msgbox IlexForest_Text_CharcoalMasterOutro, MSGBOX_DEFAULT
	setflag 8693
	setflag 8290
	setflag 8287
	setflag 8234
	setvar 20571, 3
	setvar 20547, 7
	clearflag 8229
	clearflag 8281
	closemessage
	release
	end

IlexForest_EventScript_Picnicker::
	lock
	faceplayer
	msgbox IlexForest_Text_Lass, MSGBOX_DEFAULT
	closemessage
	release
	end

IlexForest_EventScript_BugcatcherWayne::
	trainerbattle_single 1199, IlexForest_Text_BugCatcherWayneSeen, IlexForest_Text_BugCatcherWayneBeaten
	msgbox IlexForest_Text_BugCatcherWayneAfter, MSGBOX_AUTOCLOSE
	end

IlexForest_EventScript_Shrine::
	lock
	goto_if_eq 20547, 9, IlexForest_EventScript_Celebi_Event
	msgbox IlexForest_Text_Shrine, MSGBOX_DEFAULT
	closemessage
	release
	end

IlexForest_EventScript_Celebi_Event::
	msgbox IlexForest_Text_ShrineCelebiEvent, MSGBOX_YESNO
	goto_if_eq 32781, FALSE, IlexForest_EventScript_Shrine_Cancel
	msgbox IlexForest_Text_InsertGSBall, MSGBOX_DEFAULT
	clearflag 8255
	addobject 7
	playse 202
	applymovement 7, IlexForest_Movement_Celebi1
	waitmovement 0
	playse 202
	applymovement 7, IlexForest_Movement_Celebi2
	turnobject 255, DIR_SOUTH
	waitmovement 0
	playse 202
	applymovement 7, IlexForest_Movement_Celebi3
	waitmovement 0
	turnobject 255, DIR_WEST
	playmoncry 251, 2
	delay 40
	waitmoncry
	seteventmon 251, 40
	special BattleSetup_StartLegendaryBattle
	waitstate
	specialvar 32781, GetBattleOutcome
	call_if_eq 32781, 7, IlexForest_EventScript_Shrine_Caught
	fadescreenswapbuffers 1
	removeobject 7
	setflag 8255
	special GivePartyMonNationalRibbon
	fadescreenswapbuffers 0

IlexForest_EventScript_Kurt::
	clearflag 8289
	addobject 33
	applymovement 33, IlexForest_Movement_Kurt1
	waitmovement 0
	turnobject 255, DIR_SOUTH
	msgbox IlexForest_Text_KurtCaughtCelebi, MSGBOX_DEFAULT
	closemessage
	applymovement 33, IlexForest_Movement_Kurt2
	waitmovement 0
	setflag 8289
	removeobject 33
	setvar 20547, 10
	release
	end

IlexForest_EventScript_Shrine_Caught::
	setflag 8768
	return

IlexForest_EventScript_Shrine_Cancel::
	closemessage
	release
	end

IlexForest_EventScript_SecondCelebi::
	lock
	faceplayer
	playmoncry 251, 2
	delay 40
	waitmoncry
	seteventmon 251, 40
	special BattleSetup_StartLegendaryBattle
	waitstate
	specialvar 32781, GetBattleOutcome
	goto_if_eq 32781, 4, IlexForest_EventScript_SecondCelebiRan
	fadescreenswapbuffers 1
	removeobject 37
	setflag 8291
	fadescreenswapbuffers 0
	special GivePartyMonNationalRibbon
	release
	end

IlexForest_EventScript_SecondCelebiRan::
	release
	end

IlexForest_EventScript_Sign::
	lock
	msgbox IlexForest_Text_Signpost, MSGBOX_SIGN
	closemessage
	release
	end

IlexForest_EventScript_Kimono::
	lock
	playbgm ((558 + 1) + 0x85), FALSE
	playse 21
	turnobject 0xFE, DIR_NORTH
	applymovement2 35, J_Common_Movement_ExclamationMark
	delay 55
	waitmovement 35
	applymovement2 35, IlexForest_Movement_Kimono_Girl1
	waitmovement 0
	msgbox IlexForest_Text_Kimono_Girl1, MSGBOX_DEFAULT
	closemessage
	playse 202
	applymovement2 35, IlexForest_Movement_Kimono_Girl_Spin
	waitmovement 0
	turnobject 35, DIR_SOUTH
	msgbox IlexForest_Text_Kimono_Girl2, MSGBOX_YESNO
	closemessage
	msgbox IlexForest_Text_Kimono_Girl3, MSGBOX_DEFAULT
	closemessage
	playfirstmoncry
	applymovement2 0xFE, IlexForest_Movement_Follower1
	waitmovement 0
	playfirstmoncry
	turnobject 35, DIR_WEST
	msgbox IlexForest_Text_Kimono_Girl4, MSGBOX_DEFAULT
	closemessage
	turnobject 35, DIR_SOUTH
	delay 16
	msgbox IlexForest_Text_Kimono_Girl5, MSGBOX_DEFAULT
	closemessage
	delay 16
	playfirstmoncry
	applymovement2 0xFE, IlexForest_Movement_Follower2
	applymovement2 35, IlexForest_Movement_Kimono_Girl2
	waitmovement 0
	waitmovement 0
	fadedefaultbgm
	setvar 20571, 4
	setflag 8288
	removeobject 35
	playfirstmoncry
	applymovement 0xFE, IlexForest_Movement_Follower3
	waitmovement 0
	playfirstmoncry
	release
	end

IlexForest_EventScript_SuperPotion::
	finditem ITEM_SUPER_POTION
	end

IlexForest_EventScript_Ether::
	finditem ITEM_ETHER
	end

IlexForest_EventScript_FullHeal::
	finditem ITEM_FULL_HEAL
	end

IlexForest_EventScript_Item_FalseSwipe::
	finditem 635
	end

IlexForest_Movement_Kimono_Girl1:
	walk_right
	face_down
	step_end

IlexForest_Movement_Kimono_Girl_Spin:
	face_left
	delay_8
	face_up
	delay_8
	face_right
	delay_8
	face_down
	delay_8
	face_left
	delay_8
	face_up
	delay_8
	face_right
	delay_8
	face_down
	step_end

IlexForest_Movement_Follower1:
	walk_left
	jump_2_up
	walk_up
	face_right
	jump_in_place_right
	delay 16
	face_left
	jump_in_place_left
	delay 16
	face_right
	step_end

IlexForest_Movement_Follower2:
	face_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

IlexForest_Movement_Kimono_Girl2:
	face_left
	delay_16
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

IlexForest_Movement_Follower3:
	delay 16
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_down
	jump_2_down
	walk_right
	face_up
	step_end

IlexForest_Movement_Farfetchd_1A:
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	step_end

IlexForest_Movement_Farfetchd_1B:
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	step_end

IlexForest_Movement_Farfetchd_2A:
	walk_fast_up
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	step_end

IlexForest_Movement_Farfetchd_2B:
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	step_end

IlexForest_Movement_Farfetchd_3A:
	walk_fast_up
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	step_end

IlexForest_Movement_Farfetchd_3B:
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	step_end

IlexForest_Movement_Farfetchd_4A:
	walk_fast_up
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	step_end

IlexForest_Movement_Farfetchd_4B:
	walk_fast_down
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	step_end

IlexForest_Movement_Farfetchd_Leave:
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	face_down
	step_end

IlexForest_Movement_Farfetchd_Return:
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	step_end

IlexForest_Movement_Celebi1:
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	step_end

IlexForest_Movement_Celebi2:
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_up
	step_end

IlexForest_Movement_Celebi3:
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	step_end

IlexForest_Movement_Kurt1:
	walk_right
	walk_right
	walk_right
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

IlexForest_Movement_Kurt2:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	step_end

IlexForest_Text_ApprenticeIntro:
	.string "Oh{SE_M_SUPERSONIC}man{SE_M_DIZZY_PUNCH}M{SE_M_YAWN}bos{SE_M_GRASSWHISTLE}i{SE_M_GRASSWHISTLE}goin{SE_M_SANDSTORM}t{SE_M_ATTRACT2}be\n"
	.string "steaming…\p"
	.string "Th{SE_M_REVERSAL}FARFETCH'{SE_M_FAINT_ATTACK}tha{SE_M_SPIT_UP}CUT{SE_M_SKETCH}trees\n"
	.string "fo{SE_M_SAND_TOMB}charcoa{SE_M_BATON_PASS}too{SE_M_ENCORE2}of{SE_M_ACID_ARMOR}o{SE_M_ATTRACT}me.\p"
	.string "{SE_M_HEAL_BELL}can'{SE_M_SPIT_UP}g{SE_M_ATTRACT2}lookin{SE_M_SANDSTORM}fo{SE_M_SAND_TOMB}i{SE_M_SPIT_UP}here\n"
	.string "i{SE_M_ATTRACT}th{SE_M_REVERSAL}ILE{SE_M_LOCK_ON}FOREST.\p"
	.string "It'{SE_M_GRASSWHISTLE}to{SE_M_ATTRACT2}big{SE_M_SUPERSONIC}dar{SE_M_ENCORE2}an{SE_M_WATERFALL}scary\n"
	.string "fo{SE_M_SAND_TOMB}me…$"

IlexForest_Text_ApprenticeAfter:
	.string "Wow{SE_M_DRAGON_RAGE}Thank{SE_M_GRASSWHISTLE}{SE_M_CHARGE}whol{SE_M_REVERSAL}bunch!\p"
	.string "M{SE_M_YAWN}boss{SE_M_ABSORB}POKéMO{SE_M_PSYBEAM2}won'{SE_M_SPIT_UP}obe{SE_M_YAWN}me\n"
	.string "becaus{SE_M_REVERSAL}{SE_M_HEAL_BELL}don'{SE_M_SPIT_UP}hav{SE_M_REVERSAL}{SE_M_CHARGE}BADGE.$"

IlexForest_Text_ItsTheMissingPokemon:
	.string "It'{SE_M_GRASSWHISTLE}th{SE_M_REVERSAL}missin{SE_M_SANDSTORM}POKéMON!$"

IlexForest_Text_Kwaaaa:
	.string "FARFETCH'D{SE_M_HEAT_WAVE}Kwaa!$"

IlexForest_Text_CharcoalMasterIntro:
	.string "Ah{SE_M_DRAGON_RAGE}M{SE_M_YAWN}FARFETCH'D!\p"
	.string "Yo{SE_M_DIVE}foun{SE_M_WATERFALL}i{SE_M_SPIT_UP}fo{SE_M_SAND_TOMB}us{SE_M_SUPERSONIC}kid?\p"
	.string "Withou{SE_M_SPIT_UP}it{SE_M_SUPERSONIC}w{SE_M_REVERSAL}wouldn'{SE_M_SPIT_UP}b{SE_M_REVERSAL}able\n"
	.string "t{SE_M_ATTRACT2}CU{SE_M_SWIFT}tree{SE_M_GRASSWHISTLE}fo{SE_M_SAND_TOMB}charcoal.\p"
	.string "Thanks{SE_M_SUPERSONIC}kid!\p"
	.string "Now{SE_M_SUPERSONIC}ho{SE_M_TWISTER}ca{SE_M_ATTRACT}{SE_M_HEAL_BELL}than{SE_M_ENCORE2}you…\p"
	.string "{SE_M_HEAL_BELL}know{SE_M_DRAGON_RAGE}Here{SE_M_SUPERSONIC}tak{SE_M_REVERSAL}this.$"

IlexForest_Text_CharcoalMasterOutro:
	.string "That'{SE_M_GRASSWHISTLE}th{SE_M_REVERSAL}CU{SE_M_SWIFT}HM.\n"
	.string "Teac{SE_M_TRI_ATTACK}tha{SE_M_SPIT_UP}t{SE_M_ATTRACT2}{SE_M_CHARGE}POKéMO{SE_M_PSYBEAM2}t{SE_M_ATTRACT2}clear\l"
	.string "smal{SE_M_BATON_PASS}trees.\p"
	.string "O{SE_M_ACID_ARMOR}course{SE_M_SUPERSONIC}yo{SE_M_DIVE}hav{SE_M_REVERSAL}t{SE_M_ATTRACT2}hav{SE_M_REVERSAL}the\n"
	.string "GY{SE_M_GIGA_DRAIN}BADG{SE_M_SWORDS_DANCE}fro{SE_M_MILK_DRINK}AZALE{SE_M_BONEMERANG}t{SE_M_ATTRACT2}us{SE_M_REVERSAL}it.$"

IlexForest_Text_CharcoalMasterTalkAfter:
	.string "D{SE_M_ATTRACT2}yo{SE_M_DIVE}wan{SE_M_SPIT_UP}t{SE_M_ATTRACT2}apprentic{SE_M_REVERSAL}a{SE_M_GRASSWHISTLE}a\n"
	.string "charcoa{SE_M_BATON_PASS}make{SE_M_SAND_TOMB}wit{SE_M_TRI_ATTACK}me?\p"
	.string "You'l{SE_M_BATON_PASS}b{SE_M_REVERSAL}first-rat{SE_M_REVERSAL}i{SE_M_ATTRACT}te{SE_M_ATTRACT}years!$"

IlexForest_Text_Lass:
	.string "Di{SE_M_WATERFALL}somethin{SE_M_SANDSTORM}happe{SE_M_ATTRACT}t{SE_M_ATTRACT2}the\n"
	.string "forest'{SE_M_GRASSWHISTLE}guardian?$"

IlexForest_Text_Signpost:
	.string "ILE{SE_M_LOCK_ON}FORES{SE_M_SWIFT}i{SE_M_GRASSWHISTLE}s{SE_M_ATTRACT2}overgrow{SE_M_ATTRACT}with\n"
	.string "tree{SE_M_GRASSWHISTLE}tha{SE_M_SPIT_UP}yo{SE_M_DIVE}can'{SE_M_SPIT_UP}se{SE_M_REVERSAL}th{SE_M_REVERSAL}sky.\p"
	.string "Pleas{SE_M_REVERSAL}watc{SE_M_TRI_ATTACK}ou{SE_M_SPIT_UP}fo{SE_M_SAND_TOMB}item{SE_M_GRASSWHISTLE}tha{SE_M_SPIT_UP}may\n"
	.string "hav{SE_M_REVERSAL}bee{SE_M_ATTRACT}dropped.$"

IlexForest_Text_Shrine:
	.string "ILE{SE_M_LOCK_ON}FORES{SE_M_SWIFT}SHRINE…\p"
	.string "It'{SE_M_GRASSWHISTLE}i{SE_M_ATTRACT}hono{SE_M_SAND_TOMB}o{SE_M_ACID_ARMOR}th{SE_M_REVERSAL}forest's\n"
	.string "protector…$"

IlexForest_Text_ShrineCelebiEvent:
	.string "ILE{SE_M_LOCK_ON}FORES{SE_M_SWIFT}SHRINE…\p"
	.string "It'{SE_M_GRASSWHISTLE}i{SE_M_ATTRACT}hono{SE_M_SAND_TOMB}o{SE_M_ACID_ARMOR}th{SE_M_REVERSAL}forest's\n"
	.string "protector…\p"
	.string "Oh{SE_M_SING}Wha{SE_M_SPIT_UP}i{SE_M_GRASSWHISTLE}this?\p"
	.string "It'{SE_M_GRASSWHISTLE}{SE_M_CHARGE}hole.\n"
	.string "I{SE_M_SPIT_UP}look{SE_M_GRASSWHISTLE}lik{SE_M_REVERSAL}th{SE_M_REVERSAL}G{SE_M_SKETCH}BAL{SE_M_BRICK_BREAK}woul{SE_M_WATERFALL}fit\l"
	.string "insid{SE_M_REVERSAL}it.\p"
	.string "Wan{SE_M_SPIT_UP}t{SE_M_ATTRACT2}pu{SE_M_SPIT_UP}th{SE_M_REVERSAL}G{SE_M_SKETCH}BAL{SE_M_BRICK_BREAK}here?$"

IlexForest_Text_InsertGSBall:
	.string "{PLAYER} pu{SE_M_SPIT_UP}i{SE_M_ATTRACT}th{SE_M_REVERSAL}G{SE_M_SKETCH}BALL.$"

IlexForest_Text_KurtCaughtCelebi:
	.string "Whew{SE_M_SUPERSONIC}wasn'{SE_M_SPIT_UP}tha{SE_M_SPIT_UP}something!\p"
	.string "{PLAYER}{SE_M_SUPERSONIC}tha{SE_M_SPIT_UP}wa{SE_M_GRASSWHISTLE}fantastic{SE_M_PERISH_SONG}Thanks!\p"
	.string "Th{SE_M_REVERSAL}legend{SE_M_GRASSWHISTLE}abou{SE_M_SPIT_UP}tha{SE_M_SPIT_UP}SHRIN{SE_M_SWORDS_DANCE}were\n"
	.string "rea{SE_M_BATON_PASS}afte{SE_M_SAND_TOMB}all.\p"
	.string "{SE_M_HEAL_BELL}fee{SE_M_BATON_PASS}inspire{SE_M_WATERFALL}b{SE_M_YAWN}wha{SE_M_SPIT_UP}{SE_M_HEAL_BELL}jus{SE_M_SPIT_UP}saw.\p"
	.string "I{SE_M_SPIT_UP}motivate{SE_M_GRASSWHISTLE}m{SE_M_REVERSAL}t{SE_M_ATTRACT2}mak{SE_M_REVERSAL}bette{SE_M_SAND_TOMB}BALLS!\p"
	.string "I'{SE_M_MILK_DRINK}going!$"

IlexForest_Text_BugCatcherWayneSeen:
	.string "Don'{SE_M_SPIT_UP}snea{SE_M_ENCORE2}u{SE_M_MORNING_SUN}o{SE_M_ATTRACT}m{SE_M_REVERSAL}lik{SE_M_REVERSAL}that!\p"
	.string "Yo{SE_M_DIVE}frightene{SE_M_WATERFALL}{SE_M_CHARGE}POKéMO{SE_M_PSYBEAM2}away!$"

IlexForest_Text_BugCatcherWayneBeaten:
	.string "{SE_M_HEAL_BELL}hadn'{SE_M_SPIT_UP}see{SE_M_ATTRACT}tha{SE_M_SPIT_UP}POKéMO{SE_M_PSYBEAM2}before…$"

IlexForest_Text_BugCatcherWayneAfter:
	.string "{SE_M_BONEMERANG}POKéMO{SE_M_PSYBEAM2}I'v{SE_M_REVERSAL}neve{SE_M_SAND_TOMB}see{SE_M_ATTRACT}before\n"
	.string "fel{SE_M_BATON_PASS}ou{SE_M_SPIT_UP}o{SE_M_ACID_ARMOR}th{SE_M_REVERSAL}tre{SE_M_REVERSAL}whe{SE_M_ATTRACT}{SE_M_HEAL_BELL}used\l"
	.string "HEADBUTT.\p"
	.string "{SE_M_HEAL_BELL}ough{SE_M_SPIT_UP}t{SE_M_ATTRACT2}us{SE_M_REVERSAL}HEADBUT{SE_M_SWIFT}i{SE_M_ATTRACT}other\n"
	.string "place{SE_M_GRASSWHISTLE}too.$"

IlexForest_Text_Kimono_Girl1:
	.string "KIMON{SE_M_SOLAR_BEAM}GIRL{SE_M_SUPERSONIC}KIMON{SE_M_SOLAR_BEAM}GIRL{SE_M_SUPERSONIC}los{SE_M_SPIT_UP}and\n"
	.string "al{SE_M_BATON_PASS}alone{SE_M_PERISH_SONG}Poo{SE_M_SAND_TOMB}gir{SE_M_BATON_PASS}los{SE_M_SPIT_UP}i{SE_M_ATTRACT}the\l"
	.string "dar{SE_M_ENCORE2}ILE{SE_M_LOCK_ON}FOREST.$"

IlexForest_Text_Kimono_Girl2:
	.string "Yo{SE_M_DIVE}remembe{SE_M_SAND_TOMB}m{SE_M_REVERSAL}fro{SE_M_MILK_DRINK}VIOLE{SE_M_SWIFT}CITY?\n"
	.string "Yo{SE_M_DIVE}mus{SE_M_SPIT_UP}b{SE_M_REVERSAL}imagining.\p"
	.string "Anyway{SE_M_SUPERSONIC}wil{SE_M_BATON_PASS}yo{SE_M_DIVE}sho{SE_M_TWISTER}m{SE_M_REVERSAL}ho{SE_M_TWISTER}to\n"
	.string "ge{SE_M_SPIT_UP}ou{SE_M_SPIT_UP}o{SE_M_ACID_ARMOR}thi{SE_M_GRASSWHISTLE}forest?$"

IlexForest_Text_Kimono_Girl3:
	.string "M{SE_M_REVERSAL}o{SE_M_TRI_ATTACK}my..{SE_M_PERISH_SONG}Yo{SE_M_DIVE}ar{SE_M_REVERSAL}los{SE_M_SPIT_UP}yourself,\n"
	.string "aren'{SE_M_SPIT_UP}you?$"

IlexForest_Text_Kimono_Girl4:
	.string "Wow{SE_M_DRAGON_RAGE}Ar{SE_M_REVERSAL}yo{SE_M_DIVE}goin{SE_M_SANDSTORM}t{SE_M_ATTRACT2}sho{SE_M_TWISTER}m{SE_M_REVERSAL}how\n"
	.string "t{SE_M_ATTRACT2}ge{SE_M_SPIT_UP}out?\p"
	.string "Yo{SE_M_DIVE}ar{SE_M_REVERSAL}suc{SE_M_TRI_ATTACK}{SE_M_CHARGE}smar{SE_M_SPIT_UP}POKéMON!$"

IlexForest_Text_Kimono_Girl5:
	.string "Se{SE_M_REVERSAL}you.$"

