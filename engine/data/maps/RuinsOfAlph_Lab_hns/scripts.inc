@ Johto (data/maps/RuinsOfAlph_Lab_hns/scripts.inc), as built into the FireRed game.

RuinsOfAlph_Lab_hns_MapScripts::
	map_script 3, RuinsOfAlph_Lab_OnTransition
	.byte 0

RuinsOfAlph_Lab_OnTransition:
	call_if_eq 20660, 1, J_RustboroCity_DevonCorp_2F_EventScript_SetFossilReady
	end

RuinsOfAlph_Lab_EventScript_Scientist1::
	lock
	faceplayer
	msgbox RuinsOfAlph_Lab_Text_Scientist1, MSGBOX_DEFAULT
	release
	end

RuinsOfAlph_Lab_EventScript_Scientist2::
	lock
	faceplayer
	msgbox RuinsOfAlph_Lab_Text_Scientist2, MSGBOX_DEFAULT
	release
	end

RuinsOfAlph_Lab_EventScript_Fossils::
	lock
	msgbox RuinsOfAlph_Lab_Text_Fossils, MSGBOX_DEFAULT
	closemessage
	release
	end

RuinsOfAlph_Lab_Text_Scientist1:
	.string "Th{SE_M_REVERSAL}RUIN{SE_M_SKETCH}ar{SE_M_REVERSAL}abou{SE_M_SPIT_UP}150{SE_M_BITE}year{SE_M_GRASSWHISTLE}old.\p"
	.string "Bu{SE_M_SPIT_UP}it'{SE_M_GRASSWHISTLE}no{SE_M_SPIT_UP}know{SE_M_ATTRACT}wh{SE_M_YAWN}the{SE_M_YAWN}were\n"
	.string "built--o{SE_M_SAND_TOMB}b{SE_M_YAWN}whom.$"

RuinsOfAlph_Lab_Text_Scientist2:
	.string "Ther{SE_M_REVERSAL}ar{SE_M_REVERSAL}od{SE_M_WATERFALL}pattern{SE_M_GRASSWHISTLE}draw{SE_M_ATTRACT}on\n"
	.string "o{SE_M_ATTRACT}th{SE_M_REVERSAL}wall{SE_M_GRASSWHISTLE}o{SE_M_ACID_ARMOR}th{SE_M_REVERSAL}RUINS.\p"
	.string "The{SE_M_YAWN}mus{SE_M_SPIT_UP}b{SE_M_REVERSAL}th{SE_M_REVERSAL}key{SE_M_GRASSWHISTLE}for\n"
	.string "unravelin{SE_M_SANDSTORM}th{SE_M_REVERSAL}RUINS{SE_M_ABSORB}mystery.$"

RuinsOfAlph_Lab_Text_Fossils:
	.string "Fossil{SE_M_GRASSWHISTLE}foun{SE_M_WATERFALL}withi{SE_M_ATTRACT}th{SE_M_REVERSAL}RUINS.\n"
	.string "Mayb{SE_M_REVERSAL}ther{SE_M_REVERSAL}ar{SE_M_REVERSAL}mor{SE_M_REVERSAL}somewhere...$"

RuinsOfAlph_Lab_EventScript_FossilScientist::
	lock
	faceplayer
	goto_if_eq 20660, 2, RuinsOfAlph_Lab_EventScript_FossilMonReady
	goto_if_eq 20660, 1, RuinsOfAlph_Lab_EventScript_StillRegenerating
	msgbox RuinsOfAlph_Lab_Text_DevelopDeviceToResurrectFossils, MSGBOX_DEFAULT
	checkitem ITEM_ROOT_FOSSIL
	goto_if_eq 32781, TRUE, RuinsOfAlph_Lab_EventScript_NoticeRootFossil
	checkitem ITEM_CLAW_FOSSIL
	goto_if_eq 32781, TRUE, RuinsOfAlph_Lab_EventScript_NoticeClawFossil
	checkitem ITEM_HELIX_FOSSIL
	goto_if_eq 32781, TRUE, RuinsOfAlph_Lab_EventScript_NoticeHelixFossil
	checkitem ITEM_DOME_FOSSIL
	goto_if_eq 32781, TRUE, RuinsOfAlph_Lab_EventScript_NoticeDomeFossil
	checkitem ITEM_OLD_AMBER
	goto_if_eq 32781, TRUE, RuinsOfAlph_Lab_EventScript_NoticeOldAmber
	release
	end

RuinsOfAlph_Lab_EventScript_NoticeRootFossil::
	closemessage
	playse 21
	applymovement 3, J_Common_Movement_ExclamationMark
	delay 55
	waitmovement 3
	applymovement 3, J_Common_Movement_Delay48
	waitmovement 0
	msgbox RuinsOfAlph_Lab_Text_WantToBringFossilBackToLife, MSGBOX_YESNO
	goto_if_eq 32781, NO, RuinsOfAlph_Lab_EventScript_DeclineGiveFossil
	checkitem ITEM_CLAW_FOSSIL
	goto_if_eq 32781, TRUE, RuinsOfAlph_Lab_EventScript_ChooseFossil
	checkitem ITEM_HELIX_FOSSIL
	goto_if_eq 32781, TRUE, RuinsOfAlph_Lab_EventScript_ChooseFossil
	checkitem ITEM_DOME_FOSSIL
	goto_if_eq 32781, TRUE, RuinsOfAlph_Lab_EventScript_ChooseFossil
	checkitem ITEM_OLD_AMBER
	goto_if_eq 32781, TRUE, RuinsOfAlph_Lab_EventScript_ChooseFossil
	goto RuinsOfAlph_Lab_EventScript_GiveRootFossil
	end

RuinsOfAlph_Lab_EventScript_GiveRootFossil::
	bufferitemname STR_VAR_1, ITEM_ROOT_FOSSIL
	msgbox RuinsOfAlph_Lab_Text_HandedFossilToResearcher, MSGBOX_DEFAULT
	removeitem ITEM_ROOT_FOSSIL
	setvar 20660, 1
	setvar 20661, 1
	release
	end

RuinsOfAlph_Lab_EventScript_NoticeClawFossil::
	closemessage
	playse 21
	applymovement 3, J_Common_Movement_ExclamationMark
	delay 55
	waitmovement 3
	applymovement 3, J_Common_Movement_Delay48
	waitmovement 0
	msgbox RuinsOfAlph_Lab_Text_WantToBringFossilBackToLife, MSGBOX_YESNO
	goto_if_eq 32781, NO, RuinsOfAlph_Lab_EventScript_DeclineGiveFossil
	checkitem ITEM_ROOT_FOSSIL
	goto_if_eq 32781, TRUE, RuinsOfAlph_Lab_EventScript_ChooseFossil
	checkitem ITEM_HELIX_FOSSIL
	goto_if_eq 32781, TRUE, RuinsOfAlph_Lab_EventScript_ChooseFossil
	checkitem ITEM_DOME_FOSSIL
	goto_if_eq 32781, TRUE, RuinsOfAlph_Lab_EventScript_ChooseFossil
	checkitem ITEM_OLD_AMBER
	goto_if_eq 32781, TRUE, RuinsOfAlph_Lab_EventScript_ChooseFossil
	goto RuinsOfAlph_Lab_EventScript_GiveClawFossil
	end

RuinsOfAlph_Lab_EventScript_GiveClawFossil::
	bufferitemname STR_VAR_1, ITEM_CLAW_FOSSIL
	msgbox RuinsOfAlph_Lab_Text_HandedFossilToResearcher, MSGBOX_DEFAULT
	removeitem ITEM_CLAW_FOSSIL
	setvar 20660, 1
	setvar 20661, 2
	release
	end

RuinsOfAlph_Lab_EventScript_NoticeHelixFossil::
	closemessage
	playse 21
	applymovement 3, J_Common_Movement_ExclamationMark
	delay 55
	waitmovement 3
	applymovement 3, J_Common_Movement_Delay48
	waitmovement 0
	msgbox RuinsOfAlph_Lab_Text_WantToBringFossilBackToLife, MSGBOX_YESNO
	goto_if_eq 32781, NO, RuinsOfAlph_Lab_EventScript_DeclineGiveFossil
	checkitem ITEM_ROOT_FOSSIL
	goto_if_eq 32781, TRUE, RuinsOfAlph_Lab_EventScript_ChooseFossil
	checkitem ITEM_CLAW_FOSSIL
	goto_if_eq 32781, TRUE, RuinsOfAlph_Lab_EventScript_ChooseFossil
	checkitem ITEM_DOME_FOSSIL
	goto_if_eq 32781, TRUE, RuinsOfAlph_Lab_EventScript_ChooseFossil
	checkitem ITEM_OLD_AMBER
	goto_if_eq 32781, TRUE, RuinsOfAlph_Lab_EventScript_ChooseFossil
	goto RuinsOfAlph_Lab_EventScript_GiveHelixFossil
	end

RuinsOfAlph_Lab_EventScript_GiveHelixFossil::
	bufferitemname STR_VAR_1, ITEM_HELIX_FOSSIL
	msgbox RuinsOfAlph_Lab_Text_HandedFossilToResearcher, MSGBOX_DEFAULT
	removeitem ITEM_HELIX_FOSSIL
	setvar 20660, 1
	setvar 20661, 3
	release
	end

RuinsOfAlph_Lab_EventScript_NoticeDomeFossil::
	closemessage
	playse 21
	applymovement 3, J_Common_Movement_ExclamationMark
	delay 55
	waitmovement 3
	applymovement 3, J_Common_Movement_Delay48
	waitmovement 0
	msgbox RuinsOfAlph_Lab_Text_WantToBringFossilBackToLife, MSGBOX_YESNO
	goto_if_eq 32781, NO, RuinsOfAlph_Lab_EventScript_DeclineGiveFossil
	checkitem ITEM_ROOT_FOSSIL
	goto_if_eq 32781, TRUE, RuinsOfAlph_Lab_EventScript_ChooseFossil
	checkitem ITEM_CLAW_FOSSIL
	goto_if_eq 32781, TRUE, RuinsOfAlph_Lab_EventScript_ChooseFossil
	checkitem ITEM_HELIX_FOSSIL
	goto_if_eq 32781, TRUE, RuinsOfAlph_Lab_EventScript_ChooseFossil
	checkitem ITEM_OLD_AMBER
	goto_if_eq 32781, TRUE, RuinsOfAlph_Lab_EventScript_ChooseFossil
	goto RuinsOfAlph_Lab_EventScript_GiveDomeFossil
	end

RuinsOfAlph_Lab_EventScript_GiveDomeFossil::
	bufferitemname STR_VAR_1, ITEM_DOME_FOSSIL
	msgbox RuinsOfAlph_Lab_Text_HandedFossilToResearcher, MSGBOX_DEFAULT
	removeitem ITEM_DOME_FOSSIL
	setvar 20660, 1
	setvar 20661, 4
	release
	end

RuinsOfAlph_Lab_EventScript_NoticeOldAmber::
	closemessage
	playse 21
	applymovement 3, J_Common_Movement_ExclamationMark
	delay 55
	waitmovement 3
	applymovement 3, J_Common_Movement_Delay48
	waitmovement 0
	msgbox RuinsOfAlph_Lab_Text_WantToBringFossilBackToLife, MSGBOX_YESNO
	goto_if_eq 32781, NO, RuinsOfAlph_Lab_EventScript_DeclineGiveFossil
	checkitem ITEM_ROOT_FOSSIL
	goto_if_eq 32781, TRUE, RuinsOfAlph_Lab_EventScript_ChooseFossil
	checkitem ITEM_CLAW_FOSSIL
	goto_if_eq 32781, TRUE, RuinsOfAlph_Lab_EventScript_ChooseFossil
	checkitem ITEM_HELIX_FOSSIL
	goto_if_eq 32781, TRUE, RuinsOfAlph_Lab_EventScript_ChooseFossil
	checkitem ITEM_DOME_FOSSIL
	goto_if_eq 32781, TRUE, RuinsOfAlph_Lab_EventScript_ChooseFossil
	goto RuinsOfAlph_Lab_EventScript_GiveOldAmber
	end

RuinsOfAlph_Lab_EventScript_GiveOldAmber::
	bufferitemname STR_VAR_1, ITEM_OLD_AMBER
	msgbox RuinsOfAlph_Lab_Text_HandedFossilToResearcher, MSGBOX_DEFAULT
	removeitem ITEM_OLD_AMBER
	setvar 20660, 1
	setvar 20661, 5
	release
	end

RuinsOfAlph_Lab_EventScript_DeclineGiveFossil::
	msgbox RuinsOfAlph_Lab_Text_OhIsThatSo, MSGBOX_DEFAULT
	release
	end

RuinsOfAlph_Lab_EventScript_DeclineGiveFossil2::
	msgbox RuinsOfAlph_Lab_Text_OhIsThatSo2, MSGBOX_DEFAULT
	release
	end

RuinsOfAlph_Lab_EventScript_StillRegenerating::
	msgbox RuinsOfAlph_Lab_Text_FossilRegeneratorTakesTime, MSGBOX_DEFAULT
	release
	end

RuinsOfAlph_Lab_EventScript_FossilMonReady::
	goto_if_eq 20661, 1, RuinsOfAlph_Lab_EventScript_LileepReady
	goto_if_eq 20661, 2, RuinsOfAlph_Lab_EventScript_AnorithReady
	goto_if_eq 20661, 3, RuinsOfAlph_Lab_EventScript_OmanyteReady
	goto_if_eq 20661, 4, RuinsOfAlph_Lab_EventScript_KabutoReady
	goto_if_eq 20661, 5, RuinsOfAlph_Lab_EventScript_AeroReady
	end

RuinsOfAlph_Lab_EventScript_LileepReady::
	bufferspeciesname STR_VAR_2, 345
	msgbox RuinsOfAlph_Lab_Text_FossilizedMonBroughtBackToLife, MSGBOX_DEFAULT
	goto RuinsOfAlph_Lab_EventScript_ReceiveLileep
	end

RuinsOfAlph_Lab_EventScript_AnorithReady::
	bufferspeciesname STR_VAR_2, 347
	msgbox RuinsOfAlph_Lab_Text_FossilizedMonBroughtBackToLife, MSGBOX_DEFAULT
	goto RuinsOfAlph_Lab_EventScript_ReceiveAnorith
	end

RuinsOfAlph_Lab_EventScript_OmanyteReady::
	bufferspeciesname STR_VAR_2, 138
	msgbox RuinsOfAlph_Lab_Text_FossilizedMonBroughtBackToLife, MSGBOX_DEFAULT
	goto RuinsOfAlph_Lab_EventScript_ReceiveOmanyte
	end

RuinsOfAlph_Lab_EventScript_KabutoReady::
	bufferspeciesname STR_VAR_2, 140
	msgbox RuinsOfAlph_Lab_Text_FossilizedMonBroughtBackToLife, MSGBOX_DEFAULT
	goto RuinsOfAlph_Lab_EventScript_ReceiveKabuto
	end

RuinsOfAlph_Lab_EventScript_AeroReady::
	bufferspeciesname STR_VAR_2, 142
	msgbox RuinsOfAlph_Lab_Text_FossilizedMonBroughtBackToLife, MSGBOX_DEFAULT
	goto RuinsOfAlph_Lab_EventScript_ReceiveAero
	end

RuinsOfAlph_Lab_EventScript_ReceiveLileep::
	setvar 16385, 345
	givemon 345, 20
	goto_if_eq 32781, 0, RuinsOfAlph_Lab_EventScript_ReceiveLileepParty
	goto_if_eq 32781, 1, RuinsOfAlph_Lab_EventScript_ReceiveLileepPC
	goto J_Common_EventScript_NoMoreRoomForPokemon
	end

RuinsOfAlph_Lab_EventScript_ReceiveLileepParty::
	call RuinsOfAlph_Lab_EventScript_ReceivedLileepFanfare
	specialvar 32781, IsNuzlockeNicknamingActive
	goto_if_eq 32781, TRUE, RuinsOfAlph_Lab_EventScript_ReceiveLileepParty_Nuzlocke
	msgbox J_gText_NicknameThisPokemon, MSGBOX_YESNO
	goto_if_eq 32781, NO, RuinsOfAlph_Lab_EventScript_FinishReceivingLileep
	call J_Common_EventScript_GetGiftMonPartySlot
	call J_Common_EventScript_NameReceivedPartyMon
	goto RuinsOfAlph_Lab_EventScript_FinishReceivingLileep
	end

RuinsOfAlph_Lab_EventScript_ReceiveLileepParty_Nuzlocke::
	call J_Common_EventScript_GetGiftMonPartySlot
	call J_Common_EventScript_NameReceivedPartyMon
	goto RuinsOfAlph_Lab_EventScript_FinishReceivingLileep
	end

RuinsOfAlph_Lab_EventScript_ReceiveLileepPC::
	call RuinsOfAlph_Lab_EventScript_ReceivedLileepFanfare
	specialvar 32781, IsNuzlockeNicknamingActive
	goto_if_eq 32781, TRUE, RuinsOfAlph_Lab_EventScript_ReceiveLileepPC_Nuzlocke
	msgbox J_gText_NicknameThisPokemon, MSGBOX_YESNO
	goto_if_eq 32781, NO, RuinsOfAlph_Lab_EventScript_TransferLileepToPC
	call J_Common_EventScript_NameReceivedBoxMon
	goto RuinsOfAlph_Lab_EventScript_TransferLileepToPC
	end

RuinsOfAlph_Lab_EventScript_ReceiveLileepPC_Nuzlocke::
	call J_Common_EventScript_NameReceivedBoxMon
	goto RuinsOfAlph_Lab_EventScript_TransferLileepToPC
	end

RuinsOfAlph_Lab_EventScript_TransferLileepToPC::
	call J_Common_EventScript_TransferredToPC
	goto RuinsOfAlph_Lab_EventScript_FinishReceivingLileep
	end

RuinsOfAlph_Lab_EventScript_ReceivedLileepFanfare::
	bufferspeciesname STR_VAR_2, 345
	playfanfare 370
	message RuinsOfAlph_Lab_Text_ReceivedMonFromResearcher
	waitmessage
	waitfanfare
	bufferspeciesname STR_VAR_1, 345
	return

RuinsOfAlph_Lab_EventScript_FinishReceivingLileep::
	setvar 20660, 0
	setflag 8700
	release
	end

RuinsOfAlph_Lab_EventScript_ReceiveAnorith::
	setvar 16385, 347
	givemon 347, 20
	goto_if_eq 32781, 0, RuinsOfAlph_Lab_EventScript_ReceiveAnorithParty
	goto_if_eq 32781, 1, RuinsOfAlph_Lab_EventScript_ReceiveAnorithPC
	goto J_Common_EventScript_NoMoreRoomForPokemon
	end

RuinsOfAlph_Lab_EventScript_ReceiveAnorithParty::
	call RuinsOfAlph_Lab_EventScript_ReceivedAnorithFanfare
	msgbox J_gText_NicknameThisPokemon, MSGBOX_YESNO
	goto_if_eq 32781, NO, RuinsOfAlph_Lab_EventScript_FinishReceivingAnorith
	call J_Common_EventScript_GetGiftMonPartySlot
	call J_Common_EventScript_NameReceivedPartyMon
	goto RuinsOfAlph_Lab_EventScript_FinishReceivingAnorith
	end

RuinsOfAlph_Lab_EventScript_ReceiveAnorithPC::
	call RuinsOfAlph_Lab_EventScript_ReceivedAnorithFanfare
	msgbox J_gText_NicknameThisPokemon, MSGBOX_YESNO
	goto_if_eq 32781, NO, RuinsOfAlph_Lab_EventScript_TransferAnorithToPC
	call J_Common_EventScript_NameReceivedBoxMon
	goto RuinsOfAlph_Lab_EventScript_TransferAnorithToPC
	end

RuinsOfAlph_Lab_EventScript_TransferAnorithToPC::
	call J_Common_EventScript_TransferredToPC
	goto RuinsOfAlph_Lab_EventScript_FinishReceivingAnorith
	end

RuinsOfAlph_Lab_EventScript_ReceivedAnorithFanfare::
	bufferspeciesname STR_VAR_2, 347
	playfanfare 370
	message RuinsOfAlph_Lab_Text_ReceivedMonFromResearcher
	waitmessage
	waitfanfare
	bufferspeciesname STR_VAR_1, 347
	return

RuinsOfAlph_Lab_EventScript_FinishReceivingAnorith::
	setvar 20660, 0
	setflag 8700
	release
	end

RuinsOfAlph_Lab_EventScript_ReceiveOmanyte::
	setvar 16385, 138
	givemon 138, 20
	goto_if_eq 32781, 0, RuinsOfAlph_Lab_EventScript_ReceiveOmanyteParty
	goto_if_eq 32781, 1, RuinsOfAlph_Lab_EventScript_ReceiveOmanytePC
	goto J_Common_EventScript_NoMoreRoomForPokemon
	end

RuinsOfAlph_Lab_EventScript_ReceiveOmanyteParty::
	call RuinsOfAlph_Lab_EventScript_ReceivedOmanyteFanfare
	specialvar 32781, IsNuzlockeNicknamingActive
	goto_if_eq 32781, TRUE, RuinsOfAlph_Lab_EventScript_ReceiveOmanyteParty_Nuzlocke
	msgbox J_gText_NicknameThisPokemon, MSGBOX_YESNO
	goto_if_eq 32781, NO, RuinsOfAlph_Lab_EventScript_FinishReceivingOmanyte
	call J_Common_EventScript_GetGiftMonPartySlot
	call J_Common_EventScript_NameReceivedPartyMon
	goto RuinsOfAlph_Lab_EventScript_FinishReceivingOmanyte
	end

RuinsOfAlph_Lab_EventScript_ReceiveOmanyteParty_Nuzlocke::
	call J_Common_EventScript_GetGiftMonPartySlot
	call J_Common_EventScript_NameReceivedPartyMon
	goto RuinsOfAlph_Lab_EventScript_FinishReceivingOmanyte
	end

RuinsOfAlph_Lab_EventScript_ReceiveOmanytePC::
	call RuinsOfAlph_Lab_EventScript_ReceivedOmanyteFanfare
	specialvar 32781, IsNuzlockeNicknamingActive
	goto_if_eq 32781, TRUE, RuinsOfAlph_Lab_EventScript_ReceiveOmanytePC_Nuzlocke
	msgbox J_gText_NicknameThisPokemon, MSGBOX_YESNO
	goto_if_eq 32781, NO, RuinsOfAlph_Lab_EventScript_TransferOmanyteToPC
	call J_Common_EventScript_NameReceivedBoxMon
	goto RuinsOfAlph_Lab_EventScript_TransferOmanyteToPC
	end

RuinsOfAlph_Lab_EventScript_ReceiveOmanytePC_Nuzlocke::
	call J_Common_EventScript_NameReceivedBoxMon
	goto RuinsOfAlph_Lab_EventScript_TransferOmanyteToPC
	end

RuinsOfAlph_Lab_EventScript_TransferOmanyteToPC::
	call J_Common_EventScript_TransferredToPC
	goto RuinsOfAlph_Lab_EventScript_FinishReceivingOmanyte
	end

RuinsOfAlph_Lab_EventScript_ReceivedOmanyteFanfare::
	bufferspeciesname STR_VAR_2, 138
	playfanfare 370
	message RuinsOfAlph_Lab_Text_ReceivedMonFromResearcher
	waitmessage
	waitfanfare
	bufferspeciesname STR_VAR_1, 138
	return

RuinsOfAlph_Lab_EventScript_FinishReceivingOmanyte::
	setvar 20660, 0
	setflag 8700
	release
	end

RuinsOfAlph_Lab_EventScript_ReceiveKabuto::
	setvar 16385, 140
	call_if_unset 10371, RuinsOfAlph_Lab_EventScript_GiveEarlyKabuto
	call_if_set 10371, RuinsOfAlph_Lab_EventScript_GiveLateKabuto
	goto_if_eq 32781, 0, RuinsOfAlph_Lab_EventScript_ReceiveKabutoParty
	goto_if_eq 32781, 1, RuinsOfAlph_Lab_EventScript_ReceiveKabutoPC
	goto J_Common_EventScript_NoMoreRoomForPokemon
	end

RuinsOfAlph_Lab_EventScript_GiveEarlyKabuto::
	givemon 140, 5
	return

RuinsOfAlph_Lab_EventScript_GiveLateKabuto::
	givemon 140, 20
	return

RuinsOfAlph_Lab_EventScript_ReceiveKabutoParty::
	call RuinsOfAlph_Lab_EventScript_ReceivedKabutoFanfare
	specialvar 32781, IsNuzlockeNicknamingActive
	goto_if_eq 32781, TRUE, RuinsOfAlph_Lab_EventScript_ReceiveKabutoParty_Nuzlocke
	msgbox J_gText_NicknameThisPokemon, MSGBOX_YESNO
	goto_if_eq 32781, NO, RuinsOfAlph_Lab_EventScript_FinishReceivingKabuto
	call J_Common_EventScript_GetGiftMonPartySlot
	call J_Common_EventScript_NameReceivedPartyMon
	goto RuinsOfAlph_Lab_EventScript_FinishReceivingKabuto
	end

RuinsOfAlph_Lab_EventScript_ReceiveKabutoParty_Nuzlocke::
	call J_Common_EventScript_GetGiftMonPartySlot
	call J_Common_EventScript_NameReceivedPartyMon
	goto RuinsOfAlph_Lab_EventScript_FinishReceivingKabuto
	end

RuinsOfAlph_Lab_EventScript_ReceiveKabutoPC::
	call RuinsOfAlph_Lab_EventScript_ReceivedKabutoFanfare
	specialvar 32781, IsNuzlockeNicknamingActive
	goto_if_eq 32781, TRUE, RuinsOfAlph_Lab_EventScript_ReceiveKabutoPC_Nuzlocke
	msgbox J_gText_NicknameThisPokemon, MSGBOX_YESNO
	goto_if_eq 32781, NO, RuinsOfAlph_Lab_EventScript_TransferKabutoToPC
	call J_Common_EventScript_NameReceivedBoxMon
	goto RuinsOfAlph_Lab_EventScript_TransferKabutoToPC
	end

RuinsOfAlph_Lab_EventScript_ReceiveKabutoPC_Nuzlocke::
	call J_Common_EventScript_NameReceivedBoxMon
	goto RuinsOfAlph_Lab_EventScript_TransferKabutoToPC
	end

RuinsOfAlph_Lab_EventScript_TransferKabutoToPC::
	call J_Common_EventScript_TransferredToPC
	goto RuinsOfAlph_Lab_EventScript_FinishReceivingKabuto
	end

RuinsOfAlph_Lab_EventScript_ReceivedKabutoFanfare::
	bufferspeciesname STR_VAR_2, 140
	playfanfare 370
	message RuinsOfAlph_Lab_Text_ReceivedMonFromResearcher
	waitmessage
	waitfanfare
	bufferspeciesname STR_VAR_1, 140
	return

RuinsOfAlph_Lab_EventScript_FinishReceivingKabuto::
	setvar 20660, 0
	setflag 8700
	release
	end

RuinsOfAlph_Lab_EventScript_ReceiveAero::
	setvar 16385, 142
	givemon 142, 20
	goto_if_eq 32781, 0, RuinsOfAlph_Lab_EventScript_ReceiveAeroParty
	goto_if_eq 32781, 1, RuinsOfAlph_Lab_EventScript_ReceiveAeroPC
	goto J_Common_EventScript_NoMoreRoomForPokemon
	end

RuinsOfAlph_Lab_EventScript_ReceiveAeroParty::
	call RuinsOfAlph_Lab_EventScript_ReceivedAeroFanfare
	specialvar 32781, IsNuzlockeNicknamingActive
	goto_if_eq 32781, TRUE, RuinsOfAlph_Lab_EventScript_ReceiveAeroParty_Nuzlocke
	msgbox J_gText_NicknameThisPokemon, MSGBOX_YESNO
	goto_if_eq 32781, NO, RuinsOfAlph_Lab_EventScript_FinishReceivingAero
	call J_Common_EventScript_GetGiftMonPartySlot
	call J_Common_EventScript_NameReceivedPartyMon
	goto RuinsOfAlph_Lab_EventScript_FinishReceivingAero
	end

RuinsOfAlph_Lab_EventScript_ReceiveAeroParty_Nuzlocke::
	call J_Common_EventScript_GetGiftMonPartySlot
	call J_Common_EventScript_NameReceivedPartyMon
	goto RuinsOfAlph_Lab_EventScript_FinishReceivingAero
	end

RuinsOfAlph_Lab_EventScript_ReceiveAeroPC::
	call RuinsOfAlph_Lab_EventScript_ReceivedAeroFanfare
	specialvar 32781, IsNuzlockeNicknamingActive
	goto_if_eq 32781, TRUE, RuinsOfAlph_Lab_EventScript_ReceiveAeroPC_Nuzlocke
	msgbox J_gText_NicknameThisPokemon, MSGBOX_YESNO
	goto_if_eq 32781, NO, RuinsOfAlph_Lab_EventScript_TransferAeroToPC
	call J_Common_EventScript_NameReceivedBoxMon
	goto RuinsOfAlph_Lab_EventScript_TransferAeroToPC
	end

RuinsOfAlph_Lab_EventScript_ReceiveAeroPC_Nuzlocke::
	call J_Common_EventScript_NameReceivedBoxMon
	goto RuinsOfAlph_Lab_EventScript_TransferAeroToPC
	end

RuinsOfAlph_Lab_EventScript_TransferAeroToPC::
	call J_Common_EventScript_TransferredToPC
	goto RuinsOfAlph_Lab_EventScript_FinishReceivingAero
	end

RuinsOfAlph_Lab_EventScript_ReceivedAeroFanfare::
	bufferspeciesname STR_VAR_2, 142
	playfanfare 370
	message RuinsOfAlph_Lab_Text_ReceivedMonFromResearcher
	waitmessage
	waitfanfare
	bufferspeciesname STR_VAR_1, 142
	return

RuinsOfAlph_Lab_EventScript_FinishReceivingAero::
	setvar 20660, 0
	setflag 8700
	release
	end

RuinsOfAlph_Lab_EventScript_ChooseFossil::
	message RuinsOfAlph_Lab_Text_TwoFossilsPickOne
	waitmessage
	multichoice 17, 0, 176, FALSE
	switch 32781
	case 0, RuinsOfAlph_Lab_EventScript_ChooseClawFossil
	case 1, RuinsOfAlph_Lab_EventScript_ChooseRootFossil
	case 2, RuinsOfAlph_Lab_EventScript_ChooseHelixFossil
	case 3, RuinsOfAlph_Lab_EventScript_ChooseDomeFossil
	case 4, RuinsOfAlph_Lab_EventScript_ChooseOldAmber
	case 5, RuinsOfAlph_Lab_EventScript_CancelFossilSelect
	case 127, RuinsOfAlph_Lab_EventScript_CancelFossilSelect
	end

RuinsOfAlph_Lab_EventScript_ChooseClawFossil::
	checkitem ITEM_CLAW_FOSSIL
	goto_if_eq 32781, TRUE, RuinsOfAlph_Lab_EventScript_GiveClawFossil
	goto_if_eq 32781, FALSE, RuinsOfAlph_Lab_EventScript_DeclineGiveFossil2
	end

RuinsOfAlph_Lab_EventScript_ChooseRootFossil::
	checkitem ITEM_ROOT_FOSSIL
	goto_if_eq 32781, TRUE, RuinsOfAlph_Lab_EventScript_GiveRootFossil
	goto_if_eq 32781, FALSE, RuinsOfAlph_Lab_EventScript_DeclineGiveFossil2
	end

RuinsOfAlph_Lab_EventScript_ChooseHelixFossil::
	checkitem ITEM_HELIX_FOSSIL
	goto_if_eq 32781, TRUE, RuinsOfAlph_Lab_EventScript_GiveHelixFossil
	goto_if_eq 32781, FALSE, RuinsOfAlph_Lab_EventScript_DeclineGiveFossil2
	end

RuinsOfAlph_Lab_EventScript_ChooseDomeFossil::
	checkitem ITEM_DOME_FOSSIL
	goto_if_eq 32781, TRUE, RuinsOfAlph_Lab_EventScript_GiveDomeFossil
	goto_if_eq 32781, FALSE, RuinsOfAlph_Lab_EventScript_DeclineGiveFossil2
	end

RuinsOfAlph_Lab_EventScript_ChooseOldAmber::
	checkitem ITEM_OLD_AMBER
	goto_if_eq 32781, TRUE, RuinsOfAlph_Lab_EventScript_GiveOldAmber
	goto_if_eq 32781, FALSE, RuinsOfAlph_Lab_EventScript_DeclineGiveFossil2
	end

RuinsOfAlph_Lab_EventScript_CancelFossilSelect::
	release
	end

RuinsOfAlph_Lab_EventScript_WorkOnNext::
	msgbox RuinsOfAlph_Lab_Text_WhatToWorkOnNext, MSGBOX_DEFAULT
	release
	end

RuinsOfAlph_Lab_Text_DeviceForTalkingToPokemon:
	.string "We'r{SE_M_REVERSAL}developin{SE_M_SANDSTORM}{SE_M_CHARGE}devic{SE_M_REVERSAL}fo{SE_M_SAND_TOMB}talking\n"
	.string "wit{SE_M_TRI_ATTACK}POKéMON.\p"
	.string "Bu{SE_M_SPIT_UP}w{SE_M_REVERSAL}haven'{SE_M_SPIT_UP}ha{SE_M_WATERFALL}muc{SE_M_TRI_ATTACK}success…$"

RuinsOfAlph_Lab_Text_DevelopingNewBalls:
	.string "I'{SE_M_MILK_DRINK}developin{SE_M_SANDSTORM}ne{SE_M_TWISTER}kind{SE_M_GRASSWHISTLE}of\n"
	.string "POK{SE_U}BALLS…\p"
	.string "Bu{SE_M_SPIT_UP}{SE_M_HEAL_BELL}haven'{SE_M_SPIT_UP}mad{SE_M_REVERSAL}muc{SE_M_TRI_ATTACK}headway…$"

RuinsOfAlph_Lab_Text_WeFinallyMadeNewBalls:
	.string "W{SE_M_REVERSAL}finall{SE_M_YAWN}mad{SE_M_REVERSAL}ne{SE_M_TWISTER}kind{SE_M_GRASSWHISTLE}of\n"
	.string "POK{SE_U}BALLS!\p"
	.string "Th{SE_M_REVERSAL}REPEA{SE_M_SWIFT}BAL{SE_M_BRICK_BREAK}make{SE_M_GRASSWHISTLE}i{SE_M_SPIT_UP}easie{SE_M_SAND_TOMB}to\n"
	.string "catc{SE_M_TRI_ATTACK}POKéMO{SE_M_PSYBEAM2}you'v{SE_M_REVERSAL}caugh{SE_M_SPIT_UP}before.\p"
	.string "Th{SE_M_REVERSAL}TIME{SE_M_MINIMIZE}BAL{SE_M_BRICK_BREAK}get{SE_M_GRASSWHISTLE}bette{SE_M_SAND_TOMB}a{SE_M_SPIT_UP}catching\n"
	.string "POKéMO{SE_M_PSYBEAM2}th{SE_M_REVERSAL}longe{SE_M_SAND_TOMB}{SE_M_CHARGE}battl{SE_M_REVERSAL}runs.\p"
	.string "Bot{SE_M_TRI_ATTACK}ar{SE_M_REVERSAL}proudl{SE_M_YAWN}develope{SE_M_WATERFALL}by\n"
	.string "th{SE_M_REVERSAL}DEVO{SE_M_PSYBEAM2}CORPORATION.\p"
	.string "Pleas{SE_M_REVERSAL}giv{SE_M_REVERSAL}the{SE_M_MILK_DRINK}{SE_M_CHARGE}try!$"

RuinsOfAlph_Lab_Text_IMadePokenav:
	.string "{SE_M_HEAL_BELL}mad{SE_M_REVERSAL}th{SE_M_REVERSAL}POKéNAV!\p"
	.string "A{SE_M_GRASSWHISTLE}a{SE_M_ATTRACT}engineer{SE_M_SUPERSONIC}{SE_M_HEAL_BELL}fee{SE_M_BATON_PASS}blesse{SE_M_WATERFALL}t{SE_M_ATTRACT2}have\n"
	.string "mad{SE_M_REVERSAL}somethin{SE_M_SANDSTORM}s{SE_M_ATTRACT2}great!$"

RuinsOfAlph_Lab_Text_WowThatsAPokenav:
	.string "Oh{SE_M_SUPERSONIC}wow!\n"
	.string "That'{SE_M_GRASSWHISTLE}{SE_M_CHARGE}POKéNAV!\p"
	.string "I{SE_M_SPIT_UP}cam{SE_M_REVERSAL}abou{SE_M_SPIT_UP}a{SE_M_GRASSWHISTLE}{SE_M_CHARGE}resul{SE_M_SPIT_UP}o{SE_M_ACID_ARMOR}our\n"
	.string "PRESIDENT'{SE_M_GRASSWHISTLE}desir{SE_M_REVERSAL}t{SE_M_ATTRACT2}lear{SE_M_ATTRACT}about\l"
	.string "th{SE_M_REVERSAL}feeling{SE_M_GRASSWHISTLE}o{SE_M_ACID_ARMOR}POKéMON.\p"
	.string "Woul{SE_M_WATERFALL}yo{SE_M_DIVE}lik{SE_M_REVERSAL}m{SE_M_REVERSAL}t{SE_M_ATTRACT2}describ{SE_M_REVERSAL}its\n"
	.string "feature{SE_M_GRASSWHISTLE}i{SE_M_ATTRACT}detail?\p"
	.string "No{SE_M_SUPERSONIC}no{SE_M_PERISH_SONG}{SE_M_HEAL_BELL}thin{SE_M_ENCORE2}you'l{SE_M_BATON_PASS}fin{SE_M_WATERFALL}ou{SE_M_SPIT_UP}jus{SE_M_SPIT_UP}by\n"
	.string "tryin{SE_M_SANDSTORM}th{SE_M_REVERSAL}POKéNA{SE_M_BARRIER}out.$"

RuinsOfAlph_Lab_Text_DeviceToVisualizePokemonDreams:
	.string "I'{SE_M_MILK_DRINK}tryin{SE_M_SANDSTORM}t{SE_M_ATTRACT2}develo{SE_M_MORNING_SUN}{SE_M_CHARGE}devic{SE_M_REVERSAL}that\n"
	.string "visuall{SE_M_YAWN}reproduce{SE_M_GRASSWHISTLE}th{SE_M_REVERSAL}dream{SE_M_GRASSWHISTLE}of\l"
	.string "POKéMON…\p"
	.string "Bu{SE_M_SPIT_UP}it'{SE_M_GRASSWHISTLE}no{SE_M_SPIT_UP}goin{SE_M_SANDSTORM}well.$"

RuinsOfAlph_Lab_Text_DevelopDeviceToResurrectFossils:
	.string "I'v{SE_M_REVERSAL}bee{SE_M_ATTRACT}tryin{SE_M_SANDSTORM}t{SE_M_ATTRACT2}develo{SE_M_MORNING_SUN}{SE_M_CHARGE}device\n"
	.string "tha{SE_M_SPIT_UP}resurrect{SE_M_GRASSWHISTLE}POKéMO{SE_M_PSYBEAM2}fro{SE_M_MILK_DRINK}fossils…\p"
	.string "And{SE_M_SUPERSONIC}it'{SE_M_GRASSWHISTLE}working!$"

RuinsOfAlph_Lab_Text_WantToBringFossilBackToLife:
	.string "Wait{SE_M_DRAGON_RAGE}Tha{SE_M_SPIT_UP}thin{SE_M_SANDSTORM}yo{SE_M_DIVE}hav{SE_M_REVERSAL}there…\n"
	.string "I{SE_M_GRASSWHISTLE}tha{SE_M_SPIT_UP}{SE_M_CHARGE}POKéMO{SE_M_PSYBEAM2}fossil?\p"
	.string "Woul{SE_M_WATERFALL}yo{SE_M_DIVE}lik{SE_M_REVERSAL}t{SE_M_ATTRACT2}brin{SE_M_SANDSTORM}tha{SE_M_SPIT_UP}POKéMON\n"
	.string "bac{SE_M_ENCORE2}t{SE_M_ATTRACT2}life?\p"
	.string "{SE_M_HEAL_BELL}ca{SE_M_ATTRACT}wit{SE_M_TRI_ATTACK}m{SE_M_YAWN}newl{SE_M_YAWN}developed\n"
	.string "FOSSI{SE_M_BRICK_BREAK}REGENERATOR.$"

RuinsOfAlph_Lab_Text_OhIsThatSo:
	.string "Oh{SE_M_SUPERSONIC}i{SE_M_GRASSWHISTLE}tha{SE_M_SPIT_UP}so?\p"
	.string "M{SE_M_YAWN}technologica{SE_M_BATON_PASS}expertise\n"
	.string "i{SE_M_GRASSWHISTLE}outstanding{SE_M_SUPERSONIC}{SE_M_HEAL_BELL}tel{SE_M_BATON_PASS}you.$"

RuinsOfAlph_Lab_Text_OhIsThatSo2:
	.string "Oh{SE_M_SUPERSONIC}yo{SE_M_DIVE}don'{SE_M_SPIT_UP}hav{SE_M_REVERSAL}thi{SE_M_GRASSWHISTLE}fossil.\n"
	.string "Com{SE_M_REVERSAL}bac{SE_M_ENCORE2}i{SE_M_ACID_ARMOR}yo{SE_M_DIVE}manag{SE_M_REVERSAL}t{SE_M_ATTRACT2}fin{SE_M_WATERFALL}it.$"

RuinsOfAlph_Lab_Text_TwoFossilsPickOne:
	.string "Oh{SE_M_SUPERSONIC}no{SE_M_TWISTER}that'{SE_M_GRASSWHISTLE}{SE_M_CHARGE}surprise!\n"
	.string "Yo{SE_M_DIVE}hav{SE_M_REVERSAL}mor{SE_M_REVERSAL}tha{SE_M_ATTRACT}on{SE_M_REVERSAL}fossil?\p"
	.string "Unfortunately{SE_M_SUPERSONIC}m{SE_M_YAWN}machin{SE_M_REVERSAL}ca{SE_M_ATTRACT}only\n"
	.string "regenerat{SE_M_REVERSAL}on{SE_M_REVERSAL}POKéMO{SE_M_PSYBEAM2}a{SE_M_SPIT_UP}{SE_M_CHARGE}time.\p"
	.string "Whic{SE_M_TRI_ATTACK}fossi{SE_M_BATON_PASS}woul{SE_M_WATERFALL}yo{SE_M_DIVE}lik{SE_M_REVERSAL}to\n"
	.string "regenerate?$"

RuinsOfAlph_Lab_Text_HandedFossilToResearcher:
	.string "Excellent!\n"
	.string "Let'{SE_M_GRASSWHISTLE}d{SE_M_ATTRACT2}thi{SE_M_GRASSWHISTLE}righ{SE_M_SPIT_UP}away.\p"
	.string "{PLAYER} hande{SE_M_WATERFALL}th{SE_M_REVERSAL}{STR_VAR_1} to\n"
	.string "th{SE_M_REVERSAL}RUIN{SE_M_SKETCH}RESEARCHER.$"

RuinsOfAlph_Lab_Text_FossilRegeneratorTakesTime:
	.string "Th{SE_M_REVERSAL}FOSSI{SE_M_BRICK_BREAK}REGENERATOR{SE_M_SUPERSONIC}whic{SE_M_TRI_ATTACK}{SE_M_HEAL_BELL}made,\n"
	.string "i{SE_M_GRASSWHISTLE}incredible.\p"
	.string "Bu{SE_M_SPIT_UP}i{SE_M_SPIT_UP}ha{SE_M_GRASSWHISTLE}on{SE_M_REVERSAL}drawback--i{SE_M_SPIT_UP}takes\n"
	.string "{SE_M_CHARGE}lon{SE_M_SANDSTORM}tim{SE_M_REVERSAL}t{SE_M_ATTRACT2}work.\p"
	.string "So{SE_M_SUPERSONIC}uh{SE_M_DIZZY_PUNCH}Ho{SE_M_TWISTER}abou{SE_M_SPIT_UP}yo{SE_M_DIVE}g{SE_M_ATTRACT2}fo{SE_M_SAND_TOMB}{SE_M_CHARGE}stroll\n"
	.string "an{SE_M_WATERFALL}loo{SE_M_ENCORE2}aroun{SE_M_WATERFALL}fo{SE_M_SAND_TOMB}{SE_M_CHARGE}while?$"

RuinsOfAlph_Lab_Text_FossilizedMonBroughtBackToLife:
	.string "Thank{SE_M_GRASSWHISTLE}fo{SE_M_SAND_TOMB}waiting!\p"
	.string "You{SE_M_SAND_TOMB}fossilize{SE_M_WATERFALL}POKéMO{SE_M_PSYBEAM2}ha{SE_M_GRASSWHISTLE}been\n"
	.string "brough{SE_M_SPIT_UP}bac{SE_M_ENCORE2}t{SE_M_ATTRACT2}life!\p"
	.string "Th{SE_M_REVERSAL}fossi{SE_M_BATON_PASS}wa{SE_M_GRASSWHISTLE}a{SE_M_ATTRACT}ancien{SE_M_SPIT_UP}POKéMON.\n"
	.string "{STR_VAR_2}{SE_M_SUPERSONIC}i{SE_M_SPIT_UP}was!$"

RuinsOfAlph_Lab_Text_ReceivedMonFromResearcher:
	.string "{PLAYER} receive{SE_M_WATERFALL}{STR_VAR_2} from\n"
	.string "th{SE_M_REVERSAL}RESEARCHER.$"

RuinsOfAlph_Lab_Text_TooManyPokemon:
	.string "Uh-oh{SE_M_SUPERSONIC}you'v{SE_M_REVERSAL}go{SE_M_SPIT_UP}to{SE_M_ATTRACT2}man{SE_M_YAWN}POKéMON.\n"
	.string "Yo{SE_M_DIVE}hav{SE_M_REVERSAL}n{SE_M_ATTRACT2}roo{SE_M_MILK_DRINK}fo{SE_M_SAND_TOMB}thi{SE_M_GRASSWHISTLE}one.$"

RuinsOfAlph_Lab_Text_DevelopNewPokenavFeature:
	.string "I'{SE_M_MILK_DRINK}tryin{SE_M_SANDSTORM}t{SE_M_ATTRACT2}develo{SE_M_MORNING_SUN}{SE_M_CHARGE}ne{SE_M_TWISTER}feature\n"
	.string "fo{SE_M_SAND_TOMB}th{SE_M_REVERSAL}POKéNAV…\p"
	.string "Bu{SE_M_SPIT_UP}it'{SE_M_GRASSWHISTLE}no{SE_M_SPIT_UP}goin{SE_M_SANDSTORM}well.$"

RuinsOfAlph_Lab_Text_WhatToWorkOnNext:
	.string "Well{SE_M_SUPERSONIC}no{SE_M_TWISTER}wha{SE_M_SPIT_UP}shal{SE_M_BATON_PASS}{SE_M_HEAL_BELL}wor{SE_M_ENCORE2}on\n"
	.string "developin{SE_M_SANDSTORM}next?\p"
	.string "Ou{SE_M_SAND_TOMB}compan{SE_M_YAWN}allow{SE_M_GRASSWHISTLE}u{SE_M_GRASSWHISTLE}t{SE_M_ATTRACT2}mak{SE_M_REVERSAL}our\n"
	.string "inspiration{SE_M_GRASSWHISTLE}int{SE_M_ATTRACT2}reality.\p"
	.string "On{SE_M_REVERSAL}couldn'{SE_M_SPIT_UP}as{SE_M_ENCORE2}fo{SE_M_SAND_TOMB}{SE_M_CHARGE}better\n"
	.string "environmen{SE_M_SPIT_UP}a{SE_M_GRASSWHISTLE}a{SE_M_ATTRACT}engineer.$"

