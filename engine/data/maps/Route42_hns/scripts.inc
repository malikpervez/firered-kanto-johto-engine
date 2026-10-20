@ Johto (data/maps/Route42_hns/scripts.inc), as built into the FireRed game.

Route42_hns_MapScripts::
	map_script 3, Route42_MapScript_OnTransition
	map_script 5, J_SetTimeEncounters
	.byte 0

Route42_MapScript_OnTransition::
	call_if_set 8244, Route42_MapScript_HideTrigger
	callnative SetTimeBasedEncounters
	end

Route42_MapScript_HideTrigger::
	setvar 16384, 1
	return

Route42_EventScript_Suicune_Trigger::
	lock
	playmoncry 245, 0
	applymovement 17, Route42_Movement_Suicune1
	playse 10
	waitse
	playse 10
	waitse
	waitmovement 0
	waitmoncry
	playse 21
	applymovement 255, J_Common_Movement_ExclamationMark
	waitmovement 255
	applymovement 17, Route42_Movement_Suicune2
	playse 10
	delay 30
	playse 10
	delay 30
	playse 10
	delay 30
	playse 10
	delay 30
	waitmovement 0

	playmoncry 245, 0
	applymovement 17, Route42_Movement_Suicune3
	applymovement 255, Route42_Movement_Player
	playse 10
	delay 60
	playse 10
	delay 30
	playse 10
	delay 30
	playse 10
	delay 30
	playse 10
	delay 30
	playse 10
	waitmovement 17
	waitmovement 0
	delay 60
	removeobject 17
	setflag 8244
	clearflag 8366
	addobject 19
	playse 9
	turnobject 255, DIR_EAST
	applymovement 19, Route42_Movement_Eusine1
	waitmovement 0
	msgbox Route42_Text_EusineAdmireSuicune, MSGBOX_DEFAULT
	closemessage
	turnobject 19, DIR_WEST
	msgbox Route42_Text_EusineJealous, MSGBOX_DEFAULT
	turnobject 19, DIR_EAST
	msgbox Route42_Text_EusineWontGiveUp, MSGBOX_DEFAULT
	closemessage
	applymovement 19, Route42_Movement_Eusine2
	waitmovement 0
	setflag 8366
	removeobject 19
	setvar 16384, 1
	call_if_eq 20604, 2, Route42_EventScript_DoneJohtoSuicune
	release
	end

Route42_EventScript_DoneJohtoSuicune::
	setvar 20604, 3
	return

Route42_Movement_Suicune1:
	jump_in_place_right_left
	jump_in_place_right_left
	step_end

Route42_Movement_Suicune2:
	jump_2_left
	jump_2_left
	jump_2_left
	jump_2_up
	step_end

Route42_Movement_Suicune3:
	jump_in_place_up
	delay_2
	face_up
	jump_2_up
	jump_2_right
	jump_2_right
	jump_2_right
	jump_2_right
	jump_2_right
	step_end

Route42_Movement_Player:
	lock_facing_direction
	delay_2
	jump_2_up
	unlock_facing_direction
	step_end

Route42_Movement_Eusine1:
	walk_down
	walk_down
	walk_left
	face_right
	step_end

Route42_Movement_Eusine2:
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	step_end

Route42_Text_EusineAdmireSuicune:
	.string "EUSINE{SE_M_HEAT_WAVE}SUICUNE...\n"
	.string "Ho{SE_M_TWISTER}brav{SE_M_REVERSAL}i{SE_M_SPIT_UP}is!\p"
	.string "Ho{SE_M_TWISTER}refreshin{SE_M_SANDSTORM}i{SE_M_SPIT_UP}is!\n"
	.string "Ho{SE_M_TWISTER}beautifu{SE_M_BATON_PASS}i{SE_M_SPIT_UP}is!\p"
	.string "An{SE_M_WATERFALL}ho{SE_M_TWISTER}quickl{SE_M_YAWN}i{SE_M_SPIT_UP}moves!$"

Route42_Text_EusineJealous:
	.string "{PLAYER}!\p"
	.string "Yo{SE_M_DIVE}see{SE_M_MILK_DRINK}t{SE_M_ATTRACT2}b{SE_M_REVERSAL}aroun{SE_M_WATERFALL}where\n"
	.string "SUICUN{SE_M_SWORDS_DANCE}woul{SE_M_WATERFALL}appear.\p"
	.string "Well{SE_M_SUPERSONIC}that'{SE_M_GRASSWHISTLE}OK.\l"
	.string "M{SE_M_YAWN}desir{SE_M_REVERSAL}t{SE_M_ATTRACT2}searc{SE_M_TRI_ATTACK}for\n"
	.string "SUICUN{SE_M_SWORDS_DANCE}i{SE_M_GRASSWHISTLE}fa{SE_M_SAND_TOMB}beyon{SE_M_WATERFALL}yours...\p"
	.string "M{SE_M_YAWN}grandp{SE_M_CHARGE}was..{SE_M_PERISH_SONG}quit{SE_M_REVERSAL}into\n"
	.string "myths.\p"
	.string "I'v{SE_M_REVERSAL}hear{SE_M_WATERFALL}s{SE_M_ATTRACT2}man{SE_M_YAWN}stories\n"
	.string "abou{SE_M_SPIT_UP}SUICUN{SE_M_SWORDS_DANCE}fro{SE_M_MILK_DRINK}him.$"

Route42_Text_EusineWontGiveUp:
	.string "SUICUNE...\n"
	.string "{SE_M_HEAL_BELL}won'{SE_M_SPIT_UP}sto{SE_M_MORNING_SUN}followin{SE_M_SANDSTORM}you\l"
	.string "unti{SE_M_BATON_PASS}I'v{SE_M_REVERSAL}foun{SE_M_WATERFALL}ou{SE_M_SPIT_UP}what\l"
	.string "you'r{SE_M_REVERSAL}after...\p"
	.string "Yo{SE_M_DIVE}hea{SE_M_SAND_TOMB}me!$"

Route42_EventScript_Tully::
	trainerbattle_single 1206, Route42_Text_FisherTullySeen, Route42_Text_FisherTullyBeaten, Route42_EventScript_RegisterTully
	goto_if_set 8941, Route42_EventScript_TullyGiveItem
	specialvar 32781, ShouldTryRematchBattle
	goto_if_eq 32781, TRUE, Route42_EventScript_RematchTully
	msgbox Route42_Text_FisherTullyAfter, MSGBOX_AUTOCLOSE
	end

Route42_EventScript_RegisterTully::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox Route42_Text_TullyRegister, MSGBOX_DEFAULT
	register_matchcall 1206
	release
	end

Route42_EventScript_RematchTully::
	trainerbattle_rematch 1206, Route42_Text_TullyRematchIntro, Route42_Text_TullyRematchDefeat
	msgbox Route42_Text_TullyPostRematch, MSGBOX_AUTOCLOSE
	end

Route42_EventScript_TullyGiveItem::
	msgbox Route42_Text_TullyHasItem, MSGBOX_DEFAULT
	giveitem 20619
	goto_if_eq 32781, FALSE, Route42_EventScript_TullyNoRoom
	clearflag 8941
	msgbox Route42_Text_TullyGaveItem, MSGBOX_AUTOCLOSE
	end

Route42_EventScript_TullyNoRoom::
	msgbox Route42_Text_TullyNoRoom, MSGBOX_AUTOCLOSE
	end

Route42_EventScript_Ben::
	trainerbattle_single 1286, Route42_Text_HikerBenjaminSeen, Route42_Text_HikerBenjaminBeaten
	msgbox Route42_Text_HikerBenjaminAfter, MSGBOX_AUTOCLOSE
	end

Route42_EventScript_Shane::
	trainerbattle_single 1134, Route42_Text_PokemaniacShaneSeen, Route42_Text_PokemaniacShaneBeaten
	msgbox Route42_Text_PokemaniacShaneAfter, MSGBOX_AUTOCLOSE
	end

Route42_EventScript_Sign::
	lock
	msgbox Route42_Text_Sign1, MSGBOX_SIGN
	closemessage
	release
	end

Route42_EventScript_MortarSign::
	lock
	msgbox Route42_Text_MtMortarSign1, MSGBOX_SIGN
	closemessage
	release
	end

Route42_EventScript_Item_SuperPotion::
	finditem ITEM_SUPER_POTION
	end

Route42_EventScript_Item_Shadow_Claw::
	finditem 646
	end

Route42_EventScript_Item_UltraBall::
	finditem ITEM_ULTRA_BALL
	end

Route42_Text_FisherTullySeen:
	.string "Le{SE_M_SPIT_UP}m{SE_M_REVERSAL}demonstrat{SE_M_REVERSAL}th{SE_M_REVERSAL}power\n"
	.string "o{SE_M_ACID_ARMOR}th{SE_M_REVERSAL}POKéMO{SE_M_PSYBEAM2}{SE_M_HEAL_BELL}caught!$"

Route42_Text_FisherTullyBeaten:
	.string "What{SE_M_SING}That'{SE_M_GRASSWHISTLE}no{SE_M_SPIT_UP}right.\n"
	.string "{SE_M_HEAL_BELL}can'{SE_M_SPIT_UP}believ{SE_M_REVERSAL}this!$"

Route42_Text_FisherTullyAfter:
	.string "{SE_M_HEAL_BELL}wan{SE_M_SPIT_UP}t{SE_M_ATTRACT2}becom{SE_M_REVERSAL}th{SE_M_REVERSAL}trainer\n"
	.string "CHAM{SE_M_PETAL_DANCE}usin{SE_M_SANDSTORM}th{SE_M_REVERSAL}POKéMO{SE_M_PSYBEAM2}I\l"
	.string "caugh{SE_M_SPIT_UP}myself.\p"
	.string "That'{SE_M_GRASSWHISTLE}th{SE_M_REVERSAL}bes{SE_M_SPIT_UP}par{SE_M_SPIT_UP}o{SE_M_ACID_ARMOR}fishing!$"

Route42_Text_HikerBenjaminSeen:
	.string "Ah{SE_M_SUPERSONIC}it'{SE_M_GRASSWHISTLE}goo{SE_M_WATERFALL}t{SE_M_ATTRACT2}b{SE_M_REVERSAL}outside!\n"
	.string "{SE_M_HEAL_BELL}fee{SE_M_BATON_PASS}s{SE_M_ATTRACT2}free!$"

Route42_Text_HikerBenjaminBeaten:
	.string "Gahahah{SE_M_DRAGON_RAGE}Tha{SE_M_SPIT_UP}wa{SE_M_GRASSWHISTLE}{SE_M_CHARGE}good\n"
	.string "battle!$"

Route42_Text_HikerBenjaminAfter:
	.string "Losin{SE_M_SANDSTORM}feel{SE_M_GRASSWHISTLE}insignificant\n"
	.string "i{SE_M_ACID_ARMOR}yo{SE_M_DIVE}loo{SE_M_ENCORE2}u{SE_M_MORNING_SUN}a{SE_M_SPIT_UP}th{SE_M_REVERSAL}bi{SE_M_SANDSTORM}sky!$"

Route42_Text_PokemaniacShaneSeen:
	.string "HEY!\p"
	.string "Thi{SE_M_GRASSWHISTLE}i{SE_M_GRASSWHISTLE}m{SE_M_YAWN}secre{SE_M_SPIT_UP}place!\n"
	.string "Ge{SE_M_SPIT_UP}lost{SE_M_SUPERSONIC}yo{SE_M_DIVE}outsider!$"

Route42_Text_PokemaniacShaneBeaten:
	.string "{SE_M_HEAL_BELL}shoul{SE_M_WATERFALL}hav{SE_M_REVERSAL}use{SE_M_WATERFALL}my\n"
	.string "MOO{SE_M_PSYBEAM2}STONE…$"

Route42_Text_PokemaniacShaneAfter:
	.string "You'r{SE_M_REVERSAL}workin{SE_M_SANDSTORM}o{SE_M_ATTRACT}{SE_M_CHARGE}POKéDEX?\p"
	.string "Wow{SE_M_SUPERSONIC}yo{SE_M_DIVE}mus{SE_M_SPIT_UP}kno{SE_M_TWISTER}some\n"
	.string "prett{SE_M_YAWN}rar{SE_M_REVERSAL}POKéMON!\p"
	.string "Ma{SE_M_YAWN}{SE_M_HEAL_BELL}pleas{SE_M_REVERSAL}se{SE_M_REVERSAL}it?\n"
	.string "Please?$"

Route42_Text_Sign1:
	.string "ROUT{SE_M_SWORDS_DANCE}42\p"
	.string "ECRUTEA{SE_M_SNORE}CIT{SE_M_MOONLIGHT}{SE_M_PAY_DAY}MAHOGAN{SE_M_MOONLIGHT}TOWN$"

Route42_Text_MtMortarSign1:
	.string "MT.MORTAR\p"
	.string "WATERFAL{SE_M_BRICK_BREAK}CAV{SE_M_SWORDS_DANCE}INSIDE$"

Route42_Text_TullyRegister:
	.string "{SE_M_HEAL_BELL}wan{SE_M_SPIT_UP}t{SE_M_ATTRACT2}becom{SE_M_REVERSAL}th{SE_M_REVERSAL}trainer\n"
	.string "CHAM{SE_M_PETAL_DANCE}usin{SE_M_SANDSTORM}th{SE_M_REVERSAL}POKéMO{SE_M_PSYBEAM2}I\l"
	.string "caugh{SE_M_SPIT_UP}myself.\p"
	.string "That'{SE_M_GRASSWHISTLE}th{SE_M_REVERSAL}bes{SE_M_SPIT_UP}par{SE_M_SPIT_UP}o{SE_M_ACID_ARMOR}fishing!$"

Route42_Text_TullyRematchIntro:
	.string "Le{SE_M_SPIT_UP}m{SE_M_REVERSAL}demonstrat{SE_M_REVERSAL}th{SE_M_REVERSAL}power\n"
	.string "o{SE_M_ACID_ARMOR}th{SE_M_REVERSAL}POKéMO{SE_M_PSYBEAM2}{SE_M_HEAL_BELL}caught!$"

Route42_Text_TullyRematchDefeat:
	.string "What{SE_M_SING}That'{SE_M_GRASSWHISTLE}no{SE_M_SPIT_UP}right.\n"
	.string "{SE_M_HEAL_BELL}can'{SE_M_SPIT_UP}believ{SE_M_REVERSAL}this!$"

Route42_Text_TullyPostRematch:
	.string "{SE_M_HEAL_BELL}wan{SE_M_SPIT_UP}t{SE_M_ATTRACT2}becom{SE_M_REVERSAL}th{SE_M_REVERSAL}trainer\n"
	.string "CHAM{SE_M_PETAL_DANCE}usin{SE_M_SANDSTORM}th{SE_M_REVERSAL}POKéMO{SE_M_PSYBEAM2}I\l"
	.string "caugh{SE_M_SPIT_UP}myself.\p"
	.string "That'{SE_M_GRASSWHISTLE}th{SE_M_REVERSAL}bes{SE_M_SPIT_UP}par{SE_M_SPIT_UP}o{SE_M_ACID_ARMOR}fishing!$"

Route42_Text_TullyHasItem:
	.string "Hey{SE_M_DRAGON_RAGE}{SE_M_HEAL_BELL}foun{SE_M_WATERFALL}something\n"
	.string "whil{SE_M_REVERSAL}{SE_M_HEAL_BELL}wa{SE_M_GRASSWHISTLE}fishing!\p"
	.string "Here{SE_M_SUPERSONIC}yo{SE_M_DIVE}ca{SE_M_ATTRACT}hav{SE_M_REVERSAL}it!$"

Route42_Text_TullyGaveItem:
	.string "I'l{SE_M_BATON_PASS}le{SE_M_SPIT_UP}yo{SE_M_DIVE}kno{SE_M_TWISTER}i{SE_M_ACID_ARMOR}I\n"
	.string "ree{SE_M_BATON_PASS}i{SE_M_ATTRACT}anythin{SE_M_SANDSTORM}else!$"

Route42_Text_TullyNoRoom:
	.string "Hmm{SE_M_SUPERSONIC}you{SE_M_SAND_TOMB}BA{SE_M_SWAGGER}i{SE_M_GRASSWHISTLE}full.\p"
	.string "Com{SE_M_REVERSAL}bac{SE_M_ENCORE2}whe{SE_M_ATTRACT}yo{SE_M_DIVE}hav{SE_M_REVERSAL}room.$"

