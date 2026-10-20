@ Johto (data/maps/NewBarkTown_House1_hns/scripts.inc), as built into the FireRed game.

NewBarkTown_House1_hns_MapScripts::
	.byte 0

NewBarkTown_House1_EventScript_Mother::
	lock
	faceplayer
	msgbox NewBarkTown_House1_Text_Neighbor, MSGBOX_DEFAULT
	closemessage
	release
	end

NewBarkTown_House1_EventScript_Daughter::
	lock
	faceplayer
	msgbox NewBarkTown_House1_Text_NeighborsDaughter, MSGBOX_DEFAULT
	closemessage
	release
	end

NewBarkTown_House1_Text_NeighborsDaughter:
	.string "PIKACH{SE_M_REFLECT}i{SE_M_GRASSWHISTLE}a{SE_M_ATTRACT}evolve{SE_M_WATERFALL}POKéMON.\p"
	.string "{SE_M_HEAL_BELL}wa{SE_M_GRASSWHISTLE}amaze{SE_M_WATERFALL}b{SE_M_YAWN}PROF.ELM's\n"
	.string "findings.\p"
	.string "He'{SE_M_GRASSWHISTLE}s{SE_M_ATTRACT2}famou{SE_M_GRASSWHISTLE}fo{SE_M_SAND_TOMB}hi{SE_M_GRASSWHISTLE}research\n"
	.string "o{SE_M_ATTRACT}POKéMO{SE_M_PSYBEAM2}evolution.\p"
	.string "…sigh…\p"
	.string "{SE_M_HEAL_BELL}wis{SE_M_TRI_ATTACK}{SE_M_HEAL_BELL}coul{SE_M_WATERFALL}b{SE_M_REVERSAL}{SE_M_CHARGE}researcher\n"
	.string "lik{SE_M_REVERSAL}him…$"

NewBarkTown_House1_Text_Neighbor:
	.string "M{SE_M_YAWN}daughte{SE_M_SAND_TOMB}i{SE_M_GRASSWHISTLE}adaman{SE_M_SPIT_UP}about\n"
	.string "becomin{SE_M_SANDSTORM}PROF.ELM'{SE_M_GRASSWHISTLE}assistant.\p"
	.string "Sh{SE_M_REVERSAL}reall{SE_M_YAWN}love{SE_M_GRASSWHISTLE}POKéMON!\p"
	.string "Bu{SE_M_SPIT_UP}then{SE_M_SUPERSONIC}s{SE_M_ATTRACT2}d{SE_M_ATTRACT2}I!$"

