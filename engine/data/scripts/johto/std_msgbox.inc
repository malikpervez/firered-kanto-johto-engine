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
	setflag FLAG_SAFE_FOLLOWER_MOVEMENT
	lockall
	message NULL
	waitmessage
	waitbuttonpress
	releaseall
	clearflag FLAG_SAFE_FOLLOWER_MOVEMENT
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
	textcolor NPC_TEXT_COLOR_NEUTRAL
	call_if_eq VAR_0x8002, MUS_LEVEL_UP, J_EventScript_ReceivedItemFanfare1
	call_if_eq VAR_0x8002, MUS_RG_OBTAIN_KEY_ITEM, J_EventScript_ReceivedItemFanfare2
	message 0x0
	waitmessage
	waitfanfare
	call_if_eq VAR_0x8002, MUS_LEVEL_UP, J_EventScript_ReceivedItemWaitFanfare
	putitemaway VAR_0x8000, VAR_0x8001
	call J_EventScript_RestorePrevTextColor
	return

J_EventScript_ReceivedItemFanfare1::
	playfanfare MUS_LEVEL_UP
	return

J_EventScript_ReceivedItemFanfare2::
	playfanfare MUS_RG_OBTAIN_KEY_ITEM
	return

J_EventScript_ReceivedItemWaitFanfare::
	delay 50
	return

J_Std_MsgboxGetPoints:
	message NULL
	playfanfare MUS_OBTAIN_B_POINTS
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

