@ Johto (data/scripts/std_msgbox.inc), as built into the FireRed game.

J_Std_MsgboxNPC:
	lock
	faceplayer
	message NULL
	waitmessage
	waitbuttonpress
	release
	return

J_Std_MsgboxSign:
	setflag 16389
	lockall
	message NULL
	waitmessage
	waitbuttonpress
	releaseall
	clearflag 16389
	return

J_Std_MsgboxDefault:
	message NULL
	waitmessage
	waitbuttonpress
	return

J_Std_MsgboxYesNo:
	message NULL
	waitmessage
	yesnobox 20, 8
	return

J_Std_ReceivedItem::
	textcolor 3
	call_if_eq 32770, 367, J_EventScript_ReceivedItemFanfare1
	call_if_eq 32770, 530, J_EventScript_ReceivedItemFanfare2
	message 0x0
	waitmessage
	waitfanfare
	call_if_eq 32770, 367, J_EventScript_ReceivedItemWaitFanfare
	putitemaway 32768, 32769
	call J_EventScript_RestorePrevTextColor
	return

J_EventScript_ReceivedItemFanfare1::
	playfanfare 367
	return

J_EventScript_ReceivedItemFanfare2::
	playfanfare 530
	return

J_EventScript_ReceivedItemWaitFanfare::
	delay 50
	return

J_Std_MsgboxGetPoints:
	message NULL
	playfanfare 459
	waitfanfare
	waitmessage
	return

J_Std_MsgboxPokenav:
	pokenavcall NULL
	waitmessage
	return

J_EventScript_UnusedReturn:
	return

J_Common_EventScript_SaveGame::
	special SaveGame
	waitstate
	return

