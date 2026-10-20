@ Johto (data/maps/IcePath_1F_hns/scripts.inc), as built into the FireRed game.

IcePath_1F_hns_MapScripts::
	map_script 3, IcePath_1F_OnTransition
	map_script 5, J_SetTimeEncounters
	.byte 0

IcePath_1F_OnTransition:
	callnative SetTimeBasedEncounters
	end

IcePath_1F_EventScript_Item_PpUp::
	finditem ITEM_PP_UP
	end

IcePath_1F_EventScript_Item_Protein::
	finditem ITEM_PROTEIN
	end

IcePath_1F_EventScript_Item_HM_Waterfall::
	finditem 688
	end

IcePath_1F_EventScript_KimonoGirl::
	lock
	playbgm ((558 + 1) + 0x85), FALSE
	goto_if_eq 32780, DIR_SOUTH, IcePath_1F_EventScript_KimonoGirlPushPrompt
	msgbox IcePath_1F_Text_Stuck1, MSGBOX_DEFAULT
	closemessage
	fadedefaultbgm
	release
	end

IcePath_1F_Trigger_KimonoGirl::
	lock
	msgbox IcePath_1F_Text_Leave, MSGBOX_DEFAULT
	closemessage
	applymovement 255, J_Common_Movement_WalkUp1
	waitmovement 0
	release
	end

IcePath_1F_EventScript_KimonoGirlPushPrompt::
	msgbox IcePath_1F_Text_Stuck2, MSGBOX_YESNO
	goto_if_eq 32781, FALSE, IcePath_1F_EventScript_KimonoGirlRefused

IcePath_1F_EventScript_KimonoGirlPush::
	msgbox IcePath_1F_Text_Shove, MSGBOX_AUTOCLOSE
	closemessage
	playse 10
	applymovement 255, IcePath_Movement_PlayerJump
	waitmovement 0
	waitse
	playse 137
	applymovement 9, IcePath_Movement_KimonoSlide
	waitmovement 0
	msgbox IcePath_1F_Text_Thanks, MSGBOX_DEFAULT
	closemessage
	applymovement 9, IcePath_Movement_KimonoLeave
	waitmovement 9
	setflag 8355
	removeobject 9
	playse 9
	fadedefaultbgm
	setvar 20570, 1
	release
	end

IcePath_1F_EventScript_KimonoGirlRefused::
	msgbox IcePath_1F_Text_Cruel, MSGBOX_YESNO
	goto_if_eq 32781, TRUE, IcePath_1F_EventScript_KimonoGirlPush
	goto_if_eq 32781, FALSE, IcePath_1F_EventScript_KimonoGirlRefused

IcePath_Movement_PlayerJump:
	jump_in_place_down
	step_end

IcePath_Movement_KimonoSlide:
	slide_down
	slide_down
	slide_down
	slide_down
	walk_in_place_fast_down
	face_up
	walk_in_place_fast_up
	walk_in_place_fast_up
	step_end

IcePath_Movement_KimonoLeave:
	walk_down
	walk_down
	walk_down
	step_end

IcePath_1F_Text_Leave:
	.string "KIMON{SE_M_SOLAR_BEAM}GIRL{SE_M_HEAT_WAVE}.....................$"

IcePath_1F_Text_Stuck1:
	.string "M{SE_M_REVERSAL}o{SE_M_TRI_ATTACK}my..{SE_M_PERISH_SONG}I{SE_M_GRASSWHISTLE}tha{SE_M_SPIT_UP}you{SE_M_SUPERSONIC}{PLAYER}?\n"
	.string "Fanc{SE_M_YAWN}meetin{SE_M_SANDSTORM}yo{SE_M_DIVE}here!\p"
	.string "T{SE_M_ATTRACT2}tel{SE_M_BATON_PASS}th{SE_M_REVERSAL}truth..{SE_M_PERISH_SONG}m{SE_M_YAWN}sandal{SE_M_GRASSWHISTLE}are\n"
	.string "froze{SE_M_ATTRACT}o{SE_M_ATTRACT}th{SE_M_REVERSAL}ice{SE_M_SUPERSONIC}an{SE_M_WATERFALL}{SE_M_HEAL_BELL}a{SE_M_MILK_DRINK}stuck.\p"
	.string "I{SE_M_ATTRACT}othe{SE_M_SAND_TOMB}words{SE_M_SUPERSONIC}m{SE_M_YAWN}flip-flop{SE_M_GRASSWHISTLE}are\n"
	.string "quick-froze{SE_M_ATTRACT}t{SE_M_ATTRACT2}th{SE_M_REVERSAL}ground.\p"
	.string "Te{SE_M_REVERSAL}hee.\p"
	.string "Well{SE_M_SUPERSONIC}it'{SE_M_GRASSWHISTLE}n{SE_M_ATTRACT2}laughin{SE_M_SANDSTORM}matter.\p"
	.string "Woul{SE_M_WATERFALL}yo{SE_M_DIVE}com{SE_M_REVERSAL}aroun{SE_M_WATERFALL}an{SE_M_WATERFALL}push\n"
	.string "m{SE_M_YAWN}back?$"

IcePath_1F_Text_Stuck2:
	.string "M{SE_M_REVERSAL}o{SE_M_TRI_ATTACK}my..{SE_M_PERISH_SONG}I{SE_M_GRASSWHISTLE}tha{SE_M_SPIT_UP}you{SE_M_SUPERSONIC}{PLAYER}?\n"
	.string "Fanc{SE_M_YAWN}meetin{SE_M_SANDSTORM}yo{SE_M_DIVE}here!\p"
	.string "T{SE_M_ATTRACT2}tel{SE_M_BATON_PASS}th{SE_M_REVERSAL}truth..{SE_M_PERISH_SONG}m{SE_M_YAWN}sandal{SE_M_GRASSWHISTLE}are\n"
	.string "froze{SE_M_ATTRACT}o{SE_M_ATTRACT}th{SE_M_REVERSAL}ice{SE_M_SUPERSONIC}an{SE_M_WATERFALL}{SE_M_HEAL_BELL}a{SE_M_MILK_DRINK}stuck.\p"
	.string "I{SE_M_ATTRACT}othe{SE_M_SAND_TOMB}words{SE_M_SUPERSONIC}m{SE_M_YAWN}flip-flop{SE_M_GRASSWHISTLE}are\n"
	.string "quick-froze{SE_M_ATTRACT}wit{SE_M_TRI_ATTACK}th{SE_M_REVERSAL}ground.\p"
	.string "Te{SE_M_REVERSAL}hee.\p"
	.string "Well{SE_M_SUPERSONIC}it'{SE_M_GRASSWHISTLE}n{SE_M_ATTRACT2}laughin{SE_M_SANDSTORM}matter.\n"
	.string "Woul{SE_M_WATERFALL}yo{SE_M_DIVE}pus{SE_M_TRI_ATTACK}m{SE_M_YAWN}back?$"

IcePath_1F_Text_Shove:
	.string "....SHOVE!....$"

IcePath_1F_Text_Cruel:
	.string "Don'{SE_M_SPIT_UP}b{SE_M_REVERSAL}s{SE_M_ATTRACT2}cruel.\n"
	.string "Yo{SE_M_DIVE}wil{SE_M_BATON_PASS}pus{SE_M_TRI_ATTACK}m{SE_M_YAWN}back{SE_M_SUPERSONIC}won'{SE_M_SPIT_UP}you?$"

IcePath_1F_Text_Thanks:
	.string "Yo{SE_M_DIVE}reall{SE_M_YAWN}ar{SE_M_REVERSAL}kind.\n"
	.string "Than{SE_M_ENCORE2}yo{SE_M_DIVE}s{SE_M_ATTRACT2}much!$"

