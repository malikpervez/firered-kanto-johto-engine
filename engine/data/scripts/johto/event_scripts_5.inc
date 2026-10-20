@ Johto (data/event_scripts.s), as built into the FireRed game.

J_Common_EventScript_NameReceivedPartyMon::
	fadescreen FADE_TO_BLACK
	special ChangePokemonNickname
	waitstate
	return

J_Common_EventScript_GiftMon::
	call_if_eq VAR_RESULT, MON_GIVEN_TO_PARTY, J_Common_EventScript_RecieveMonParty
	call_if_eq VAR_RESULT, MON_GIVEN_TO_PC, J_Common_EventScript_ReceiveMonPC
	return

J_Common_EventScript_RecieveMonParty::
	playfanfare MUS_OBTAIN_ITEM
	message J_Common_Text_ReceivedMon
	waitmessage
	waitfanfare
	specialvar VAR_RESULT, IsNuzlockeNicknamingActive
	goto_if_eq VAR_RESULT, TRUE, J_Common_EventScript_ForceNameReceivedPartyMon
	msgbox J_gText_NicknameThisPokemon, MSGBOX_YESNO
	call_if_eq VAR_RESULT, TRUE, J_Common_EventScript_NameReceivedPartyMonFull
	setvar VAR_RESULT, 0
	return

J_Common_EventScript_ForceNameReceivedPartyMon::
	call J_Common_EventScript_NameReceivedPartyMonFull
	setvar VAR_RESULT, 0
	return

J_Common_EventScript_ReceiveMonPC::
	playfanfare MUS_OBTAIN_ITEM
	message J_Common_Text_ReceivedMon
	waitmessage
	waitfanfare
	specialvar VAR_RESULT, IsNuzlockeNicknamingActive
	goto_if_eq VAR_RESULT, TRUE, J_Common_EventScript_ForceNameReceivedBoxMon
	msgbox J_gText_NicknameThisPokemon, MSGBOX_YESNO
	call_if_eq VAR_RESULT, TRUE, J_Common_EventScript_NameReceivedBoxMon
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
	fadescreen FADE_TO_BLACK
	special ChangePokemonNickname
	waitstate
	return

J_Common_EventScript_GiftMonNamed::
	call_if_eq VAR_RESULT, MON_GIVEN_TO_PARTY, J_Common_EventScript_RecieveMonPartyNamed
	call_if_eq VAR_RESULT, MON_CANT_GIVE, J_Common_EventScript_PartyIsFull
	return

J_Common_EventScript_RecieveMonPartyNamed::
	playfanfare MUS_OBTAIN_ITEM
	message J_Common_Text_ReceivedMon
	waitmessage
	waitfanfare
	return

J_Common_EventScript_PartyIsFull::
	msgbox J_Common_Text_PartyIsFull, MSGBOX_DEFAULT
	closemessage
	end

J_Common_Text_ReceivedMon:
	.string "{PLAYER} received {STR_VAR_1}!$"

J_Common_Text_PartyIsFull:
	.string "Whoa, wait. You can't carry any\n"
	.string "more POKéMON.$"

J_Common_EventScript_PlayerHandedOverTheItem::
	bufferitemname STR_VAR_1, VAR_0x8004
	playfanfare MUS_OBTAIN_TMHM
	message J_gText_PlayerHandedOverTheItem
	waitmessage
	waitfanfare
	removeitem VAR_0x8004
	return

