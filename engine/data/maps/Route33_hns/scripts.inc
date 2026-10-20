@ Johto (data/maps/Route33_hns/scripts.inc), as built into the FireRed game.

Route33_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route33_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, J_SetTimeEncounters
	.byte 0

Route33_OnTransition:
	callnative SetTimeBasedEncounters
	end

Route33_EventScript_HikerAnthony::
	trainerbattle_single TRAINER_JOHTO_ANTHONY_HNS, Route33_Text_HikerAnthony2Seen, Route33_Text_HikerAnthony2Beaten, Route33_EventScript_RegisterAnthony
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, Route33_EventScript_RematchAnthony
	msgbox Route33_Text_HikerAnthony2After, MSGBOX_AUTOCLOSE
	end

Route33_EventScript_RegisterAnthony::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox Route33_Text_AnthonyRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_JOHTO_ANTHONY_HNS
	release
	end

Route33_EventScript_RematchAnthony::
	trainerbattle_rematch TRAINER_JOHTO_ANTHONY_HNS, Route33_Text_AnthonyRematchIntro, Route33_Text_AnthonyRematchDefeat
	msgbox Route33_Text_AnthonyPostRematch, MSGBOX_AUTOCLOSE
	end

Route33_EventScript_Lass::
	lock
	faceplayer
	msgbox Route33_Text_Lass, MSGBOX_DEFAULT
	closemessage
	release
	end

Route33_Text_HikerAnthony2Seen:
	.string "{SE_M_HEAL_BELL}cam{SE_M_REVERSAL}throug{SE_M_TRI_ATTACK}th{SE_M_REVERSAL}tunnel,\n"
	.string "bu{SE_M_SPIT_UP}{SE_M_HEAL_BELL}stil{SE_M_BATON_PASS}hav{SE_M_REVERSAL}plenty\l"
	.string "o{SE_M_ACID_ARMOR}energ{SE_M_YAWN}left.$"

Route33_Text_HikerAnthony2Beaten:
	.string "Whoa{SE_M_DRAGON_RAGE}You'v{SE_M_REVERSAL}go{SE_M_SPIT_UP}mor{SE_M_REVERSAL}zip\n"
	.string "tha{SE_M_ATTRACT}me!$"

Route33_Text_HikerAnthony2After:
	.string "W{SE_M_REVERSAL}HIKER{SE_M_SKETCH}ar{SE_M_REVERSAL}a{SE_M_SPIT_UP}ou{SE_M_SAND_TOMB}best\n"
	.string "i{SE_M_ATTRACT}th{SE_M_REVERSAL}mountains.$"

Route33_Text_AnthonyRegister:
	.string "W{SE_M_REVERSAL}HIKER{SE_M_SKETCH}ar{SE_M_REVERSAL}a{SE_M_SPIT_UP}ou{SE_M_SAND_TOMB}best\n"
	.string "i{SE_M_ATTRACT}th{SE_M_REVERSAL}mountains.$"

Route33_Text_AnthonyRematchIntro:
	.string "{SE_M_HEAL_BELL}cam{SE_M_REVERSAL}throug{SE_M_TRI_ATTACK}th{SE_M_REVERSAL}tunnel,\n"
	.string "bu{SE_M_SPIT_UP}{SE_M_HEAL_BELL}stil{SE_M_BATON_PASS}hav{SE_M_REVERSAL}plenty\l"
	.string "o{SE_M_ACID_ARMOR}energ{SE_M_YAWN}left.$"

Route33_Text_AnthonyRematchDefeat:
	.string "Whoa{SE_M_DRAGON_RAGE}You'v{SE_M_REVERSAL}go{SE_M_SPIT_UP}mor{SE_M_REVERSAL}zip\n"
	.string "tha{SE_M_ATTRACT}me!$"

Route33_Text_AnthonyPostRematch:
	.string "W{SE_M_REVERSAL}HIKER{SE_M_SKETCH}ar{SE_M_REVERSAL}a{SE_M_SPIT_UP}ou{SE_M_SAND_TOMB}best\n"
	.string "i{SE_M_ATTRACT}th{SE_M_REVERSAL}mountains.$"

Route33_Text_HikerAnthonyDunsparce:
	.string "Hey{SE_M_SUPERSONIC}di{SE_M_WATERFALL}yo{SE_M_DIVE}ge{SE_M_SPIT_UP}{SE_M_CHARGE}DUNSPARCE?\p"
	.string "{SE_M_HEAL_BELL}caugh{SE_M_SPIT_UP}on{SE_M_REVERSAL}too.\p"
	.string "Tak{SE_M_REVERSAL}{SE_M_CHARGE}loo{SE_M_ENCORE2}a{SE_M_SPIT_UP}i{SE_M_SPIT_UP}i{SE_M_ATTRACT}th{SE_M_REVERSAL}light.\n"
	.string "It'{SE_M_GRASSWHISTLE}go{SE_M_SPIT_UP}{SE_M_CHARGE}funn{SE_M_YAWN}face!$"

Route33_Text_Lass:
	.string "Pant{SE_M_SUPERSONIC}pant…\p"
	.string "Tha{SE_M_SPIT_UP}cav{SE_M_REVERSAL}wa{SE_M_GRASSWHISTLE}bigge{SE_M_SAND_TOMB}than\n"
	.string "I'{SE_M_WATERFALL}expected.\p"
	.string "{SE_M_HEAL_BELL}go{SE_M_SPIT_UP}to{SE_M_ATTRACT2}tire{SE_M_WATERFALL}exploring\n"
	.string "fo{SE_M_SAND_TOMB}MARILL{SE_M_SUPERSONIC}s{SE_M_ATTRACT2}{SE_M_HEAL_BELL}cam{SE_M_REVERSAL}outside.$"

