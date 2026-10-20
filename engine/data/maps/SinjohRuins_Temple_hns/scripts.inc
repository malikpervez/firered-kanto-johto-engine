@ Johto (data/maps/SinjohRuins_Temple_hns/scripts.inc), as built into the FireRed game.

SinjohRuins_Temple_hns_MapScripts::
	map_script 1, SinjohRuins_Temple_OnLoad
	.byte 0

SinjohRuins_Temple_OnLoad::
	call_if_ge 20641, 5, SinjohRuins_Temple_OpenDoor
	end

SinjohRuins_Temple_OpenDoor::
	setmetatile 18, 7, 0x308, FALSE
	return

SinjohRuins_Temple_Text_Mon:
	.string "Som{SE_M_REVERSAL}kin{SE_M_WATERFALL}o{SE_M_ACID_ARMOR}ancien{SE_M_SPIT_UP}sensor.\n"
	.string "Wha{SE_M_SPIT_UP}i{SE_M_GRASSWHISTLE}i{SE_M_SPIT_UP}lookin{SE_M_SANDSTORM}for?$"

SinjohRuins_Temple_EventScript_RegiceScanner::
	lock
	goto_if_set 9127, SinjohRuins_Temple_EventScript_ScannerAlreadyDone
	msgbox SinjohRuins_Temple_Text_Mon, MSGBOX_AUTOCLOSE
	checkspecies 378
	goto_if_eq 32781, FALSE, SinjohRuins_Lab_EventScript_NoOp
	setflag 9127
	goto_if_eq 32781, TRUE, SinjohRuins_Temple_EventScript_SeenPokemon
	release
	end

SinjohRuins_Temple_EventScript_RegirockScanner::
	lock
	goto_if_set 9128, SinjohRuins_Temple_EventScript_ScannerAlreadyDone
	msgbox SinjohRuins_Temple_Text_Mon, MSGBOX_AUTOCLOSE
	checkspecies 377
	goto_if_eq 32781, FALSE, SinjohRuins_Lab_EventScript_NoOp
	setflag 9128
	goto_if_eq 32781, TRUE, SinjohRuins_Temple_EventScript_SeenPokemon
	release
	end

SinjohRuins_Temple_EventScript_RegisteelScanner::
	lock
	goto_if_set 9129, SinjohRuins_Temple_EventScript_ScannerAlreadyDone
	msgbox SinjohRuins_Temple_Text_Mon, MSGBOX_AUTOCLOSE
	checkspecies 379
	goto_if_eq 32781, FALSE, SinjohRuins_Lab_EventScript_NoOp
	setflag 9129
	goto_if_eq 32781, TRUE, SinjohRuins_Temple_EventScript_SeenPokemon
	release
	end

SinjohRuins_Temple_EventScript_RegielekiScanner::
	lock
	goto_if_set 9130, SinjohRuins_Temple_EventScript_ScannerAlreadyDone
	msgbox SinjohRuins_Temple_Text_Mon, MSGBOX_AUTOCLOSE
	checkspecies 894
	goto_if_eq 32781, FALSE, SinjohRuins_Lab_EventScript_NoOp
	setflag 9130
	goto_if_eq 32781, TRUE, SinjohRuins_Temple_EventScript_SeenPokemon
	release
	end

SinjohRuins_Temple_EventScript_RegidragoScanner::
	lock
	goto_if_set 9131, SinjohRuins_Temple_EventScript_ScannerAlreadyDone
	msgbox SinjohRuins_Temple_Text_Mon, MSGBOX_AUTOCLOSE
	checkspecies 895
	goto_if_eq 32781, FALSE, SinjohRuins_Lab_EventScript_NoOp
	setflag 9131
	goto_if_eq 32781, TRUE, SinjohRuins_Temple_EventScript_SeenPokemon
	release
	end

SinjohRuins_Temple_EventScript_SeenPokemon::
	playse 36
	waitse
	setvar 32772, 2
	setvar 32773, 2
	setvar 32774, 20
	setvar 32775, 4
	special ShakeCamera
	waitstate
	msgbox SinjohRuins_Temple_Text_Responds, MSGBOX_AUTOCLOSE
	addvar 20641, 1
	call_if_eq 20641, 5, SinjohRuins_Temple_EventScript_UnlockDoor
	release
	end

SinjohRuins_Temple_EventScript_UnlockDoor::
	setvar 32772, 2
	setvar 32773, 2
	setvar 32774, 20
	setvar 32775, 4
	special ShakeCamera
	waitstate
	setmetatile 18, 7, 0x308, FALSE
	special DrawWholeMapView
	msgbox SinjohRuins_Temple_Text_Door, MSGBOX_AUTOCLOSE
	return

SinjohRuins_Temple_EventScript_ScannerAlreadyDone::
	msgbox SinjohRuins_Temple_Text_ScannerAlreadyDone, MSGBOX_SIGN
	release
	end

SinjohRuins_Temple_Text_ScannerAlreadyDone:
	.string "Thi{SE_M_GRASSWHISTLE}senso{SE_M_SAND_TOMB}ha{SE_M_GRASSWHISTLE}alread{SE_M_YAWN}bee{SE_M_ATTRACT}activated.$"

SinjohRuins_Temple_Text_Responds:
	.string "Th{SE_M_REVERSAL}templ{SE_M_REVERSAL}respond{SE_M_GRASSWHISTLE}t{SE_M_ATTRACT2}you{SE_M_SAND_TOMB}actions.$"

SinjohRuins_Temple_Text_Door:
	.string "Th{SE_M_REVERSAL}wa{SE_M_YAWN}i{SE_M_GRASSWHISTLE}open.$"

