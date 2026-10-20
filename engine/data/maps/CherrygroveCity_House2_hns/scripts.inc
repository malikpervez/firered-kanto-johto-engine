#ifdef FIRERED
CherrygroveCity_House2_hns_MapScripts::
	.byte 0

B3_CherrygroveHouse2_EventScript_Visitor::
	lock
	faceplayer
	msgbox B3_CherrygroveHouse2_EventScript_Visitor_Text, MSGBOX_DEFAULT
	closemessage
	release
	end

B3_CherrygroveHouse2_EventScript_Visitor_Text::
	.string "The GUIDE outside loves helping\n"
	.string "trainers who are new to JOHTO.$"

#else
CherrygroveCity_House2_hns_MapScripts::
	.byte 0

CherrygroveCity_House2_EventScript_GuideGent::
	lock
	faceplayer
	msgbox CherrygroveCity_GuideHouse_Text_GuideGent, MSGBOX_DEFAULT
	closemessage
	release
	end

CherrygroveCity_GuideHouse_Text_GuideGent:
	.string "When I was a wee lad, I was a\n"
	.string "hotshot trainer!\p"
	.string "Here's a word of advice:\n"
	.string "Catch lots of POKéMON!\p"
	.string "Treat them all with kindness!$"

#endif // FIRERED
