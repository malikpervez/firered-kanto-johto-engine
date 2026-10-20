@ Johto (data/maps/GoldenrodCity_House3_hns/scripts.inc), as built into the FireRed game.

GoldenrodCity_House3_hns_MapScripts::
	.byte 0

GoldenrodCity_House3_EventScript_PokefanM::
	lock
	faceplayer
	msgbox GoldenrodHappinessRater_Text_PokefanM, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_House3_EventScript_Twin::
	lock
	faceplayer
	msgbox GoldenrodHappinessRater_Text_Twin, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodHappinessRater_Text_PokefanM:
	.string "{SE_M_HEAL_BELL}kee{SE_M_MORNING_SUN}losin{SE_M_SANDSTORM}i{SE_M_ATTRACT}battles{SE_M_SUPERSONIC}an{SE_M_WATERFALL}my\n"
	.string "POKéMO{SE_M_PSYBEAM2}en{SE_M_WATERFALL}u{SE_M_MORNING_SUN}fainting…\p"
	.string "Mayb{SE_M_REVERSAL}that'{SE_M_GRASSWHISTLE}wh{SE_M_YAWN}m{SE_M_YAWN}POKéMO{SE_M_PSYBEAM2}don't\n"
	.string "lik{SE_M_REVERSAL}m{SE_M_REVERSAL}much…$"

GoldenrodHappinessRater_Text_Twin:
	.string "Whe{SE_M_ATTRACT}{SE_M_HEAL_BELL}us{SE_M_REVERSAL}a{SE_M_ATTRACT}ite{SE_M_MILK_DRINK}o{SE_M_ATTRACT}m{SE_M_YAWN}POKéMON,\n"
	.string "i{SE_M_SPIT_UP}act{SE_M_GRASSWHISTLE}reall{SE_M_YAWN}glad!$"

