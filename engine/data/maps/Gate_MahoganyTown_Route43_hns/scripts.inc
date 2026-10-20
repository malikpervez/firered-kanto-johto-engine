@ Johto (data/maps/Gate_MahoganyTown_Route43_hns/scripts.inc), as built into the FireRed game.

Gate_MahoganyTown_Route43_hns_MapScripts::
	.byte 0

Gate_MahoganyTown_Route43_EventScript_Cop::
	goto_if_ge 20569, 11, Gate_MahoganyTown_Route43_EventScript_CopAfter
	msgbox Route43MahoganyGate_Text_Officer, MSGBOX_NPC
	end

Gate_MahoganyTown_Route43_EventScript_CopAfter::
	msgbox Route43MahoganyGate_Text_Officer_RocketsCleared, MSGBOX_NPC
	end

Route43MahoganyGate_Text_Officer:
	.string "Onl{SE_M_YAWN}peopl{SE_M_REVERSAL}heade{SE_M_WATERFALL}u{SE_M_MORNING_SUN}t{SE_M_ATTRACT2}LAK{SE_M_SWORDS_DANCE}OF\n"
	.string "RAG{SE_M_SWORDS_DANCE}hav{SE_M_REVERSAL}bee{SE_M_ATTRACT}throug{SE_M_TRI_ATTACK}her{SE_M_REVERSAL}lately.$"

Route43MahoganyGate_Text_Officer_RocketsCleared:
	.string "Nobod{SE_M_YAWN}goe{SE_M_GRASSWHISTLE}u{SE_M_MORNING_SUN}t{SE_M_ATTRACT2}LAK{SE_M_SWORDS_DANCE}O{SE_M_LEER}RAGE\n"
	.string "thes{SE_M_REVERSAL}days.$"

