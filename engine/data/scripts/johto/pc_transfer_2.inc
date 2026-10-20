@ Johto (data/scripts/pc_transfer.inc), as built into the FireRed game.

J_Common_EventScript_GetGiftMonPartySlot::
	getpartysize
	subvar VAR_RESULT, 1
	copyvar VAR_0x8004, VAR_RESULT
	return

J_Common_EventScript_NameReceivedBoxMon::
	fadescreen FADE_TO_BLACK
	setvar VAR_0x8004, PC_MON_CHOSEN
	special ChangePokemonNickname
	waitstate
	lock
	faceplayer
	return

J_Common_EventScript_TransferredToPC::
	bufferboxname STR_VAR_1, VAR_PC_BOX_TO_SEND_MON
	bufferspeciesname STR_VAR_2, VAR_TEMP_TRANSFERRED_SPECIES
	call_if_unset JOHTO_FLAG_SYS_PC_LANETTE, J_EventScript_TransferredSomeonesPC
	call_if_set JOHTO_FLAG_SYS_PC_LANETTE, J_EventScript_TransferredLanettesPC
	return

J_EventScript_TransferredSomeonesPC::
	specialvar VAR_RESULT, ShouldShowBoxWasFullMessage
	goto_if_eq VAR_RESULT, TRUE, J_EventScript_SomeonesPCBoxFull
	msgbox J_gText_PkmnTransferredSomeonesPC, MSGBOX_DEFAULT
	return

J_EventScript_SomeonesPCBoxFull::
	specialvar VAR_RESULT, GetPCBoxToSendMon
	bufferboxname STR_VAR_3, VAR_RESULT
	msgbox J_gText_PkmnTransferredSomeonesPCBoxFull, MSGBOX_DEFAULT
	return

J_EventScript_TransferredLanettesPC::
	specialvar VAR_RESULT, ShouldShowBoxWasFullMessage
	goto_if_eq VAR_RESULT, TRUE, J_EventScript_LanettesPCBoxFull
	msgbox J_gText_PkmnTransferredLanettesPC, MSGBOX_DEFAULT
	return

J_EventScript_LanettesPCBoxFull::
	specialvar VAR_RESULT, GetPCBoxToSendMon
	bufferboxname STR_VAR_3, VAR_RESULT
	msgbox J_gText_PkmnTransferredLanettesPCBoxFull, MSGBOX_DEFAULT
	return

J_Common_EventScript_NoMoreRoomForPokemon::
	msgbox J_gText_NoMoreRoomForPokemon, MSGBOX_DEFAULT
	release
	end

