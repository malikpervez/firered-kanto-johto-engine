@ Johto (data/maps/SSAqua_RoomSE_hns/scripts.inc), as built into the FireRed game.

SSAqua_RoomSE_hns_MapScripts::
	.byte 0

SSAqua_RoomSE_EventScript_Colin::
	trainerbattle_single TRAINER_JOHTO_COLIN_HNS, SSAqua_RoomSE_Text_PokefanmColinSeen, SSAqua_RoomSE_Text_PokefanmColinBeaten
	msgbox SSAqua_RoomSE_Text_PokefanmColinAfter, MSGBOX_AUTOCLOSE
	end

SSAqua_RoomSE_EventScript_Meg::
	trainerbattle_double TRAINER_JOHTO_MEG_AND_PEG_HNS, SSAqua_RoomSE_Text_TwinsMegandpeg1Seen, SSAqua_RoomSE_Text_TwinsMegandpeg1Beaten, J_Route104_Text_GinaNotEnoughMons
	special GetPlayerBigGuyGirlString
	msgbox SSAqua_RoomSE_Text_TwinsMegandpeg1After, MSGBOX_AUTOCLOSE
	end

SSAqua_RoomSE_EventScript_Peg::
	trainerbattle_double TRAINER_JOHTO_MEG_AND_PEG_HNS, SSAqua_RoomSE_Text_TwinsMegandpeg2Seen, SSAqua_RoomSE_Text_TwinsMegandpeg2Beaten, J_Route104_Text_GinaNotEnoughMons
	special GetPlayerBigGuyGirlString
	msgbox SSAqua_RoomSE_Text_TwinsMegandpeg2After, MSGBOX_AUTOCLOSE
	end

SSAqua_RoomSE_Text_PokefanmColinSeen:
	.string "Hey{SE_M_SUPERSONIC}kid{SE_M_DRAGON_RAGE}Wan{SE_M_SPIT_UP}t{SE_M_ATTRACT2}battle\n"
	.string "wit{SE_M_TRI_ATTACK}me?$"

SSAqua_RoomSE_Text_PokefanmColinBeaten:
	.string "You'r{SE_M_REVERSAL}strong!$"

SSAqua_RoomSE_Text_PokefanmColinAfter:
	.string "You'r{SE_M_REVERSAL}travelin{SE_M_SANDSTORM}al{SE_M_BATON_PASS}alone?\n"
	.string "Isn'{SE_M_SPIT_UP}you{SE_M_SAND_TOMB}mo{SE_M_MILK_DRINK}worried?$"

SSAqua_RoomSE_Text_TwinsMegandpeg1Seen:
	.string "Yo{SE_M_DIVE}thin{SE_M_ENCORE2}I'{SE_M_MILK_DRINK}{SE_M_CHARGE}baby?\n"
	.string "That'{SE_M_GRASSWHISTLE}no{SE_M_SPIT_UP}fair!$"

SSAqua_RoomSE_Text_TwinsMegandpeg1Beaten:
	.string "Oh{SE_M_DRAGON_RAGE}W{SE_M_REVERSAL}lost!$"

SSAqua_RoomSE_Text_TwinsMegandpeg1After:
	.string "Bab{SE_M_YAWN}i{SE_M_GRASSWHISTLE}{SE_M_CHARGE}rud{SE_M_REVERSAL}nam{SE_M_REVERSAL}t{SE_M_ATTRACT2}call\n"
	.string "u{SE_M_GRASSWHISTLE}girls!$"

SSAqua_RoomSE_Text_TwinsMegandpeg2Seen:
	.string "I'{SE_M_MILK_DRINK}no{SE_M_SPIT_UP}{SE_M_CHARGE}baby!\n"
	.string "That'{SE_M_GRASSWHISTLE}no{SE_M_SPIT_UP}nic{SE_M_REVERSAL}t{SE_M_ATTRACT2}sa{SE_M_YAWN}t{SE_M_ATTRACT2}{SE_M_CHARGE}lady!$"

SSAqua_RoomSE_Text_TwinsMegandpeg2Beaten:
	.string "Oh{SE_M_DRAGON_RAGE}W{SE_M_REVERSAL}lost!$"

SSAqua_RoomSE_Text_TwinsMegandpeg2After:
	.string "Sometimes{SE_M_SUPERSONIC}kid{SE_M_GRASSWHISTLE}ar{SE_M_REVERSAL}smarter\n"
	.string "tha{SE_M_ATTRACT}grown-ups!$"

