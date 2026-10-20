#ifdef FIRERED
Gate_Route29_Route46_hns_MapScripts::
	.byte 0

B3_Gate_EventScript_Route46Closed::
	lock
	faceplayer
	msgbox B3_Gate_EventScript_Route46Closed_Text, MSGBOX_DEFAULT
	closemessage
	release
	end

B3_Gate_EventScript_Route46Closed_Text::
	.string "ROUTE 46 is closed for repairs.\p"
	.string "Please return to ROUTE 29.$"

#else
Gate_Route29_Route46_hns_MapScripts::
	.byte 0

Gate_Route29_Route46_EventScript_Officer::
	lock
	faceplayer
	msgbox Gate_Route29_Route46_Text_Officer, MSGBOX_DEFAULT
	closemessage
	release
	end

Gate_Route29_Route46_EventScript_Youngster::
	lock
	faceplayer
	msgbox Gate_Route29_Route46_Text_Youngster, MSGBOX_DEFAULT
	closemessage
	release
	end

Gate_Route29_Route46_Text_Officer:
	.string "You can't climb ledges.\p"
	.string "But you can jump down from\n"
	.string "them to take a shortcut.$"

Gate_Route29_Route46_Text_Youngster:
	.string "Different kinds of POKéMON\n"
	.string "appear past here.\p"
	.string "If you want to catch them all,\n"
	.string "you have to look everywhere.$"

#endif // FIRERED
