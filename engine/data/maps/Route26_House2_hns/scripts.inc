@ Johto (data/maps/Route26_House2_hns/scripts.inc), as built into the FireRed game.

Route26_House2_hns_MapScripts::
	.byte 0

Route26_House2_EventScript_Book::
	lock
	msgbox DayOfWeekSiblingsHouse_Text_Pokedex1, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, TRUE, Route26_House2_EventScript_BookRead
	closemessage
	release
	end

Route26_House2_EventScript_BookRead::
	msgbox DayOfWeekSiblingsHouse_Text_Pokedex2, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, TRUE, Route26_House2_EventScript_BookRead2
	closemessage
	release
	end

Route26_House2_EventScript_BookRead2::
	msgbox DayOfWeekSiblingsHouse_Text_Pokedex3, MSGBOX_DEFAULT
	closemessage
	release
	end

DayOfWeekSiblingsHouse_Text_Pokedex1:
	.string "There'{SE_M_GRASSWHISTLE}somethin{SE_M_SANDSTORM}writte{SE_M_ATTRACT}here.\p"
	.string "Rea{SE_M_WATERFALL}it?$"

DayOfWeekSiblingsHouse_Text_Pokedex2:
	.string "T{SE_M_ATTRACT2}m{SE_M_YAWN}brother{SE_M_GRASSWHISTLE}an{SE_M_WATERFALL}sisters:\p"
	.string "W{SE_M_REVERSAL}tak{SE_M_REVERSAL}prid{SE_M_REVERSAL}i{SE_M_ATTRACT}servin{SE_M_SANDSTORM}POKéMON\n"
	.string "trainers.\p"
	.string "Whe{SE_M_ATTRACT}trainer{SE_M_GRASSWHISTLE}tal{SE_M_ENCORE2}t{SE_M_ATTRACT2}you{SE_M_SUPERSONIC}give\n"
	.string "the{SE_M_MILK_DRINK}somethin{SE_M_SANDSTORM}useful.\p"
	.string "Love,\n"
	.string "MONICA\p"
	.string "Kee{SE_M_MORNING_SUN}reading?$"

DayOfWeekSiblingsHouse_Text_Pokedex3:
	.string "Monday{SE_M_SUPERSONIC}MONICA\n"
	.string "ROUT{SE_M_SWORDS_DANCE}40\p"
	.string "Tuesday{SE_M_SUPERSONIC}TUSCANY\n"
	.string "ROUT{SE_M_SWORDS_DANCE}29\p"
	.string "Wednesday{SE_M_SUPERSONIC}WESLEY\n"
	.string "LAK{SE_M_SWORDS_DANCE}O{SE_M_LEER}RAGE\p"
	.string "Thursday{SE_M_SUPERSONIC}ARTHUR\n"
	.string "ROUT{SE_M_SWORDS_DANCE}36\p"
	.string "Friday{SE_M_SUPERSONIC}FRIEDA\n"
	.string "ROUT{SE_M_SWORDS_DANCE}32\p"
	.string "Saturday{SE_M_SUPERSONIC}SANTOS\n"
	.string "BLACKTHOR{SE_M_PSYBEAM2}CITY\p"
	.string "Sunday{SE_M_SUPERSONIC}SUNNY\n"
	.string "ROUT{SE_M_SWORDS_DANCE}37$"

