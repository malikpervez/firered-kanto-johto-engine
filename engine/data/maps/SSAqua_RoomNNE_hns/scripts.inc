@ Johto (data/maps/SSAqua_RoomNNE_hns/scripts.inc), as built into the FireRed game.

SSAqua_RoomNNE_hns_MapScripts::
	.byte 0

SSAqua_RoomNNE_EventScript_Sean::
	trainerbattle_single TRAINER_JOHTO_SEAN_HNS, SSAqua_RoomNNE_Text_CooltrainermSeanSeen, SSAqua_RoomNNE_Text_CooltrainermSeanBeaten
	msgbox SSAqua_RoomNNE_Text_CooltrainermSeanAfterBattle, MSGBOX_AUTOCLOSE
	end

SSAqua_RoomNNE_EventScript_Carol::
	trainerbattle_single TRAINER_JOHTO_CAROL_HNS, SSAqua_RoomNNE_Text_CooltrainerfCarolSeen, SSAqua_RoomNNE_Text_CooltrainerfCarolBeaten
	msgbox SSAqua_RoomNNE_Text_CooltrainerfCarolAfterBattle, MSGBOX_AUTOCLOSE
	end

SSAqua_RoomNNE_Text_CooltrainermSeanSeen:
	.string "I'{SE_M_MILK_DRINK}goin{SE_M_SANDSTORM}t{SE_M_ATTRACT2}KANTO\n"
	.string "t{SE_M_ATTRACT2}tes{SE_M_SPIT_UP}m{SE_M_YAWN}skills.$"

SSAqua_RoomNNE_Text_CooltrainermSeanBeaten:
	.string "{SE_M_HEAL_BELL}wante{SE_M_WATERFALL}t{SE_M_ATTRACT2}win!$"

SSAqua_RoomNNE_Text_CooltrainermSeanAfterBattle:
	.string "Trainer{SE_M_GRASSWHISTLE}fro{SE_M_MILK_DRINK}JOHTO\n"
	.string "ca{SE_M_ATTRACT}battl{SE_M_REVERSAL}wit{SE_M_TRI_ATTACK}KANTO\l"
	.string "GY{SE_M_GIGA_DRAIN}LEADERS.$"

SSAqua_RoomNNE_Text_CooltrainerfCarolSeen:
	.string "I'{SE_M_MILK_DRINK}trainin{SE_M_SANDSTORM}to\n"
	.string "becom{SE_M_REVERSAL}th{SE_M_REVERSAL}CHAMP!$"

SSAqua_RoomNNE_Text_CooltrainerfCarolBeaten:
	.string "What'{SE_M_GRASSWHISTLE}s{SE_M_ATTRACT2}different\n"
	.string "betwee{SE_M_ATTRACT}us?$"

SSAqua_RoomNNE_Text_CooltrainerfCarolAfterBattle:
	.string "I'{SE_M_MILK_DRINK}goin{SE_M_SANDSTORM}t{SE_M_ATTRACT2}beat\n"
	.string "yo{SE_M_DIVE}someday!$"

