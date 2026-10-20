@ Johto (data/maps/SinjohRuins_Temple_hns/scripts.inc), as built into the FireRed game.

SinjohRuins_Temple_hns_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, SinjohRuins_Temple_OnLoad
	.byte 0

SinjohRuins_Temple_OnLoad::
	call_if_ge JOHTO_VAR_REGIS_SCANNED, 5, SinjohRuins_Temple_OpenDoor
	end

SinjohRuins_Temple_OpenDoor::
	setmetatile 18, 7, 0x308, FALSE
	return

SinjohRuins_Temple_Text_Mon:
	.string "Som{SE_M_REVERSAL}kin{SE_M_WATERFALL}o{SE_M_ACID_ARMOR}ancien{SE_M_SPIT_UP}sensor.\n"
	.string "Wha{SE_M_SPIT_UP}i{SE_M_GRASSWHISTLE}i{SE_M_SPIT_UP}lookin{SE_M_SANDSTORM}for?$"

SinjohRuins_Temple_EventScript_RegiceScanner::
	lock
	goto_if_set JOHTO_FLAG_BROUGHT_REGICE, SinjohRuins_Temple_EventScript_ScannerAlreadyDone
	msgbox SinjohRuins_Temple_Text_Mon, MSGBOX_AUTOCLOSE
	checkspecies SPECIES_REGICE
	goto_if_eq VAR_RESULT, FALSE, SinjohRuins_Lab_EventScript_NoOp
	setflag JOHTO_FLAG_BROUGHT_REGICE
	goto_if_eq VAR_RESULT, TRUE, SinjohRuins_Temple_EventScript_SeenPokemon
	release
	end

SinjohRuins_Temple_EventScript_RegirockScanner::
	lock
	goto_if_set JOHTO_FLAG_BROUGHT_REGIROCK, SinjohRuins_Temple_EventScript_ScannerAlreadyDone
	msgbox SinjohRuins_Temple_Text_Mon, MSGBOX_AUTOCLOSE
	checkspecies SPECIES_REGIROCK
	goto_if_eq VAR_RESULT, FALSE, SinjohRuins_Lab_EventScript_NoOp
	setflag JOHTO_FLAG_BROUGHT_REGIROCK
	goto_if_eq VAR_RESULT, TRUE, SinjohRuins_Temple_EventScript_SeenPokemon
	release
	end

SinjohRuins_Temple_EventScript_RegisteelScanner::
	lock
	goto_if_set JOHTO_FLAG_BROUGHT_REGISTEEL, SinjohRuins_Temple_EventScript_ScannerAlreadyDone
	msgbox SinjohRuins_Temple_Text_Mon, MSGBOX_AUTOCLOSE
	checkspecies SPECIES_REGISTEEL
	goto_if_eq VAR_RESULT, FALSE, SinjohRuins_Lab_EventScript_NoOp
	setflag JOHTO_FLAG_BROUGHT_REGISTEEL
	goto_if_eq VAR_RESULT, TRUE, SinjohRuins_Temple_EventScript_SeenPokemon
	release
	end

SinjohRuins_Temple_EventScript_RegielekiScanner::
	lock
	goto_if_set JOHTO_FLAG_BROUGHT_REGIELEKI, SinjohRuins_Temple_EventScript_ScannerAlreadyDone
	msgbox SinjohRuins_Temple_Text_Mon, MSGBOX_AUTOCLOSE
	checkspecies SPECIES_REGIELEKI
	goto_if_eq VAR_RESULT, FALSE, SinjohRuins_Lab_EventScript_NoOp
	setflag JOHTO_FLAG_BROUGHT_REGIELEKI
	goto_if_eq VAR_RESULT, TRUE, SinjohRuins_Temple_EventScript_SeenPokemon
	release
	end

SinjohRuins_Temple_EventScript_RegidragoScanner::
	lock
	goto_if_set JOHTO_FLAG_BROUGHT_REGIDRAGO, SinjohRuins_Temple_EventScript_ScannerAlreadyDone
	msgbox SinjohRuins_Temple_Text_Mon, MSGBOX_AUTOCLOSE
	checkspecies SPECIES_REGIDRAGO
	goto_if_eq VAR_RESULT, FALSE, SinjohRuins_Lab_EventScript_NoOp
	setflag JOHTO_FLAG_BROUGHT_REGIDRAGO
	goto_if_eq VAR_RESULT, TRUE, SinjohRuins_Temple_EventScript_SeenPokemon
	release
	end

SinjohRuins_Temple_EventScript_SeenPokemon::
	playse SE_CLICK
	waitse
	setvar VAR_0x8004, 2
	setvar VAR_0x8005, 2
	setvar VAR_0x8006, 20
	setvar VAR_0x8007, 4
	special ShakeCamera
	waitstate
	msgbox SinjohRuins_Temple_Text_Responds, MSGBOX_AUTOCLOSE
	addvar JOHTO_VAR_REGIS_SCANNED, 1
	call_if_eq JOHTO_VAR_REGIS_SCANNED, 5, SinjohRuins_Temple_EventScript_UnlockDoor
	release
	end

SinjohRuins_Temple_EventScript_UnlockDoor::
	setvar VAR_0x8004, 2
	setvar VAR_0x8005, 2
	setvar VAR_0x8006, 20
	setvar VAR_0x8007, 4
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

