#ifdef FIRERED
CherrygroveCity_House1_hns_MapScripts::
	.byte 0

B3_CherrygroveHouse1_EventScript_Visitor::
	lock
	faceplayer
	msgbox B3_CherrygroveHouse1_EventScript_Visitor_Text, MSGBOX_DEFAULT
	closemessage
	release
	end

B3_CherrygroveHouse1_EventScript_Visitor_Text::
	.string "JOHTO has many POKéMON GYMS.\n"
	.string "Perhaps you will visit them one day.$"

#else
CherrygroveCity_House1_hns_MapScripts::
	.byte 0

CherrygroveCity_House1_EventScript_Baldingman::
	lock
	faceplayer
	msgbox CherrygroveCity_GymSpeechHouse_Text_PokefanM, MSGBOX_DEFAULT
	closemessage
	release
	end

CherrygroveCity_House1_EventScript_Kid::
	lock
	faceplayer
	msgbox CherrygroveCity_GymSpeechHouse_Text_BugCatcher, MSGBOX_DEFAULT
	closemessage
	release
	end

CherrygroveCity_GymSpeechHouse_Text_PokefanM:
	.string "You're trying to see how good\n"
	.string "you are as a POKéMON trainer?\p"
	.string "You better visit the POKéMON\n"
	.string "GYMS all over JOHTO and collect\l"
	.string "BADGES.$"

CherrygroveCity_GymSpeechHouse_Text_BugCatcher:
	.string "When I get older, I'm going to\n"
	.string "be a GYM LEADER!\p"
	.string "I make my POKéMON battle with\n"
	.string "my friend's to make them\l"
	.string "tougher!$"

#endif // FIRERED
