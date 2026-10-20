@ Johto (data/maps/MtMortar_2F_hns/scripts.inc), as built into the FireRed game.

MtMortar_2F_hns_MapScripts::
	map_script 3, MtMortar_2F_OnTransition
	map_script 5, J_SetTimeEncounters
	.byte 0

MtMortar_2F_OnTransition:
	callnative SetTimeBasedEncounters
	end

MtMortar_2F_EventScript_Item_Iron::
	finditem ITEM_IRON
	end

MtMortar_2F_EventScript_Item_MaxRevive::
	finditem ITEM_MAX_REVIVE
	end

MtMortar_2F_EventScript_Item_Ether::
	finditem ITEM_ETHER
	end

MtMortar_2F_EventScript_Item_RareCandy::
	finditem ITEM_RARE_CANDY
	end

MtMortar_2F_EventScript_Item_DragonScale::
	finditem ITEM_DRAGON_SCALE
	end

MtMortar_2F_EventScript_Item_Elixir::
	finditem ITEM_ELIXIR
	end

MtMortar_2F_EventScript_Nerd::
	trainerbattle_single 1278, MtMortar_2F_Text_SupernerdHughSeen, MtMortar_2F_Text_SupernerdHughBeaten
	msgbox MtMortar_2F_Text_SupernerdHughAfter, MSGBOX_AUTOCLOSE
	end

MtMortar_2F_Text_SupernerdHughSeen::
	.string "Yo{SE_M_DRAGON_RAGE}MARKUS!$"

MtMortar_2F_Text_SupernerdHughBeaten:
	.string "Sorry{SE_M_SUPERSONIC}m{SE_M_YAWN}mistake.\n"
	.string "{SE_M_HEAL_BELL}misjudge{SE_M_WATERFALL}you.$"

MtMortar_2F_Text_SupernerdHughAfter:
	.string "I'{SE_M_MILK_DRINK}investigatin{SE_M_SANDSTORM}MT.MORTAR,\n"
	.string "bu{SE_M_SPIT_UP}m{SE_M_YAWN}pal'{SE_M_GRASSWHISTLE}gon{SE_M_REVERSAL}AWOL.\p"
	.string "Hav{SE_M_REVERSAL}yo{SE_M_DIVE}see{SE_M_ATTRACT}{SE_M_CHARGE}traine{SE_M_SAND_TOMB}who\n"
	.string "ha{SE_M_GRASSWHISTLE}{SE_M_CHARGE}SLOWPOK{SE_M_SWORDS_DANCE}tha{SE_M_SPIT_UP}ca{SE_M_ATTRACT}use\l"
	.string "STRENGTH?$"

