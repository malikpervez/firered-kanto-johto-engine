@ Johto (data/scripts/pc_transfer.inc), as built into the FireRed game.

J_Common_EventScript_GetGiftMonPartySlot::
	getpartysize
	subvar 32781, 1
	copyvar 32772, 32781
	return

J_Common_EventScript_NameReceivedBoxMon::
	fadescreen 1
	setvar 32772, 0xFE
	special ChangePokemonNickname
	waitstate
	lock
	faceplayer
	return

J_Common_EventScript_TransferredToPC::
	bufferboxname STR_VAR_1, 16438
	bufferspeciesname STR_VAR_2, 16385
	call_if_unset 10391, J_EventScript_TransferredSomeonesPC
	call_if_set 10391, J_EventScript_TransferredLanettesPC
	return

J_EventScript_TransferredSomeonesPC::
	specialvar 32781, ShouldShowBoxWasFullMessage
	goto_if_eq 32781, TRUE, J_EventScript_SomeonesPCBoxFull
	msgbox J_gText_PkmnTransferredSomeonesPC, MSGBOX_DEFAULT
	return

J_EventScript_SomeonesPCBoxFull::
	specialvar 32781, GetPCBoxToSendMon
	bufferboxname STR_VAR_3, 32781
	msgbox J_gText_PkmnTransferredSomeonesPCBoxFull, MSGBOX_DEFAULT
	return

J_EventScript_TransferredLanettesPC::
	specialvar 32781, ShouldShowBoxWasFullMessage
	goto_if_eq 32781, TRUE, J_EventScript_LanettesPCBoxFull
	msgbox J_gText_PkmnTransferredLanettesPC, MSGBOX_DEFAULT
	return

J_EventScript_LanettesPCBoxFull::
	specialvar 32781, GetPCBoxToSendMon
	bufferboxname STR_VAR_3, 32781
	msgbox J_gText_PkmnTransferredLanettesPCBoxFull, MSGBOX_DEFAULT
	return

J_Common_EventScript_NoMoreRoomForPokemon::
	msgbox J_gText_NoMoreRoomForPokemon, MSGBOX_DEFAULT
	release
	end

