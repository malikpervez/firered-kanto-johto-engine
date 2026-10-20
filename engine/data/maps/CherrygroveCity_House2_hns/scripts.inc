@ Johto (data/maps/CherrygroveCity_House2_hns/scripts.inc), as built into the FireRed game.

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

