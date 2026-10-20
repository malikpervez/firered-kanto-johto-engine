@ Johto (data/maps/MtMortar_B1F_hns/scripts.inc), as built into the FireRed game.

MtMortar_B1F_hns_MapScripts::
	map_script 3, MtMortar_B1F_OnTransition
	map_script 5, J_SetTimeEncounters
	.byte 0

MtMortar_B1F_OnTransition:
	callnative SetTimeBasedEncounters
	end

MtMortar_B1F_EventScript_Item_HyperPotion::
	finditem ITEM_HYPER_POTION
	end

MtMortar_B1F_EventScript_Item_Carbos::
	finditem ITEM_CARBOS
	end

MtMortar_B1F_EventScript_Item_PPUp::
	finditem ITEM_PP_UP
	end

MtMortar_B1F_EventScript_Item_MaxEther::
	finditem ITEM_MAX_ETHER
	end

MtMortar_B1F_EventScript_Item_MaxRevive::
	finditem ITEM_MAX_REVIVE
	end

MountMortar4_EventScript_Kiyo::
	lock
	faceplayer
	goto_if_set 8709, MountMortar4_EventScript_KiyoAfter
	goto_if_set 8665, MountMortar4_EventScript_KiyoTryGiveTyrogue
	msgbox MountMortar4_Text_KiyoIntro, MSGBOX_DEFAULT
	trainerbattle_no_intro 1327, MountMortar4_Text_KiyoWin
	setflag 8665

MountMortar4_EventScript_KiyoTryGiveTyrogue::
	msgbox MountMortar4_Text_KiyoTyrogueReward, MSGBOX_DEFAULT

	setvar 16385, 236
	bufferspeciesname STR_VAR_1, 236
	givemon 236, 25
	call J_Common_EventScript_GiftMon
	setflag 8709

MountMortar4_EventScript_KiyoAfter::
	msgbox MountMortar4_Text_KiyoGotTyrogue, MSGBOX_DEFAULT
	closemessage
	release
	end

MountMortar4_Text_KiyoIntro:
	.string "Hey!\p"
	.string "{SE_M_HEAL_BELL}a{SE_M_MILK_DRINK}th{SE_M_REVERSAL}KARAT{SE_M_SWORDS_DANCE}KING!\n"
	.string "{SE_M_HEAL_BELL}trai{SE_M_ATTRACT}alon{SE_M_REVERSAL}her{SE_M_REVERSAL}i{SE_M_ATTRACT}th{SE_M_REVERSAL}dark!\p"
	.string "You{SE_M_DRAGON_RAGE}Battl{SE_M_REVERSAL}wit{SE_M_TRI_ATTACK}me!\n"
	.string "Hwaaarggh!$"

MountMortar4_Text_KiyoWin:
	.string "Waaaarggh!\n"
	.string "I'{SE_M_MILK_DRINK}beaten!$"

MountMortar4_Text_KiyoTyrogueReward:
	.string "I..{SE_M_PERISH_SONG}I'{SE_M_MILK_DRINK}crushed...\p"
	.string "M{SE_M_YAWN}trainin{SE_M_SANDSTORM}i{SE_M_GRASSWHISTLE}stil{SE_M_BATON_PASS}not\n"
	.string "enough...\p"
	.string "Bu{SE_M_SPIT_UP}{SE_M_CHARGE}los{SE_M_GRASSWHISTLE}i{SE_M_GRASSWHISTLE}{SE_M_CHARGE}loss.\n"
	.string "{SE_M_HEAL_BELL}admi{SE_M_SPIT_UP}it.\p"
	.string "A{SE_M_GRASSWHISTLE}proo{SE_M_ACID_ARMOR}tha{SE_M_SPIT_UP}yo{SE_M_DIVE}defeate{SE_M_WATERFALL}me,\n"
	.string "I'l{SE_M_BATON_PASS}giv{SE_M_REVERSAL}yo{SE_M_DIVE}{SE_M_CHARGE}rar{SE_M_REVERSAL}fighting\l"
	.string "POKéMON.$"

MountMortar4_Text_ReceiveTyrogue:
	.string "{PLAYER} receive{SE_M_WATERFALL}TYROGUE.$"

MountMortar4_Text_KiyoGotTyrogue:
	.string "TYROGU{SE_M_SWORDS_DANCE}i{SE_M_GRASSWHISTLE}{SE_M_CHARGE}FIGHTING-type.\p"
	.string "I{SE_M_SPIT_UP}evolve{SE_M_GRASSWHISTLE}int{SE_M_ATTRACT2}{SE_M_CHARGE}tougher\n"
	.string "POKéMON.\p"
	.string "Kee{SE_M_MORNING_SUN}u{SE_M_MORNING_SUN}th{SE_M_REVERSAL}har{SE_M_WATERFALL}work.\n"
	.string "I'l{SE_M_BATON_PASS}kee{SE_M_MORNING_SUN}trainin{SE_M_SANDSTORM}too.\p"
	.string "Farewell!$"

MountMortar4_Text_KiyoFullParty:
	.string "Yo{SE_M_DIVE}hav{SE_M_REVERSAL}n{SE_M_ATTRACT2}roo{SE_M_MILK_DRINK}i{SE_M_ATTRACT}you{SE_M_SAND_TOMB}party!$"

