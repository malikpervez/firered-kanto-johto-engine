@ Johto (data/event_scripts.s), as built into the FireRed game.

J_Common_EventScript_NameReceivedPartyMon::
	fadescreen 1
	special ChangePokemonNickname
	waitstate
	return

J_Common_EventScript_GiftMon::
	call_if_eq 32781, 0, J_Common_EventScript_RecieveMonParty
	call_if_eq 32781, 1, J_Common_EventScript_ReceiveMonPC
	return

J_Common_EventScript_RecieveMonParty::
	playfanfare 370
	message J_Common_Text_ReceivedMon
	waitmessage
	waitfanfare
	specialvar 32781, IsNuzlockeNicknamingActive
	goto_if_eq 32781, TRUE, J_Common_EventScript_ForceNameReceivedPartyMon
	msgbox J_gText_NicknameThisPokemon, MSGBOX_YESNO
	call_if_eq 32781, TRUE, J_Common_EventScript_NameReceivedPartyMonFull
	setvar 32781, 0
	return

J_Common_EventScript_ForceNameReceivedPartyMon::
	call J_Common_EventScript_NameReceivedPartyMonFull
	setvar 32781, 0
	return

J_Common_EventScript_ReceiveMonPC::
	playfanfare 370
	message J_Common_Text_ReceivedMon
	waitmessage
	waitfanfare
	specialvar 32781, IsNuzlockeNicknamingActive
	goto_if_eq 32781, TRUE, J_Common_EventScript_ForceNameReceivedBoxMon
	msgbox J_gText_NicknameThisPokemon, MSGBOX_YESNO
	call_if_eq 32781, TRUE, J_Common_EventScript_NameReceivedBoxMon
	call J_Common_EventScript_TransferredToPC
	return

J_Common_EventScript_ForceNameReceivedBoxMon::
	call J_Common_EventScript_NameReceivedBoxMon
	call J_Common_EventScript_TransferredToPC
	return

J_Common_EventScript_NameReceivedPartyMonFull::
	call J_Common_EventScript_GetGiftMonPartySlot
	call J_Common_EventScript_NameReceivedPartyMon_2
	return

J_Common_EventScript_NameReceivedPartyMon_2::
	fadescreen 1
	special ChangePokemonNickname
	waitstate
	return

J_Common_EventScript_GiftMonNamed::
	call_if_eq 32781, 0, J_Common_EventScript_RecieveMonPartyNamed
	call_if_eq 32781, 2, J_Common_EventScript_PartyIsFull
	return

J_Common_EventScript_RecieveMonPartyNamed::
	playfanfare 370
	message J_Common_Text_ReceivedMon
	waitmessage
	waitfanfare
	return

J_Common_EventScript_PartyIsFull::
	msgbox J_Common_Text_PartyIsFull, MSGBOX_DEFAULT
	closemessage
	end

J_Common_Text_ReceivedMon:
	.string "{PLAYER} receive{SE_M_WATERFALL}{STR_VAR_1}!$"

J_Common_Text_PartyIsFull:
	.string "Whoa{SE_M_SUPERSONIC}wait{SE_M_PERISH_SONG}Yo{SE_M_DIVE}can'{SE_M_SPIT_UP}carr{SE_M_YAWN}any\n"
	.string "mor{SE_M_REVERSAL}POKéMON.$"

J_Common_EventScript_PlayerHandedOverTheItem::
	bufferitemname STR_VAR_1, 32772
	playfanfare 372
	message J_gText_PlayerHandedOverTheItem
	waitmessage
	waitfanfare
	removeitem 32772
	return

