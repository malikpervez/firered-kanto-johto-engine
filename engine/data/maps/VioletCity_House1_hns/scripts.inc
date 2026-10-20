@ Johto (data/maps/VioletCity_House1_hns/scripts.inc), as built into the FireRed game.

VioletCity_House1_hns_MapScripts::
	.byte 0

VioletCity_House1_EventScript_Kyle::
	lock
	faceplayer
	msgbox VioletCity_House1_Text_PokefanM, MSGBOX_DEFAULT
	closemessage
	release
	end

VioletCity_House1_EventScript_Rudy::
	lock
	faceplayer
	goto_if_set 8773, VioletCity_House1_EventScript_TradeCompleted
	ingame_trade INGAME_TRADE_ONIX, VioletCity_House1_Text_YouWillTradeWontYou, VioletCity_House1_EventScript_DeclineTrade, VioletCity_House1_EventScript_NotRequestedMon, VioletCity_House1_Text_MonYouTakeCare
	setflag 8773
	release
	end

VioletCity_House1_EventScript_DeclineTrade::
	msgbox VioletCity_House1_Text_YouWontTradeMe, MSGBOX_DEFAULT
	release
	end

VioletCity_House1_EventScript_NotRequestedMon::
	bufferspeciesname STR_VAR_1, 32777
	msgbox VioletCity_House1_Text_ThisIsntAMon, MSGBOX_DEFAULT
	release
	end

VioletCity_House1_EventScript_TradeCompleted::
	msgbox VioletCity_House1_Text_After, MSGBOX_DEFAULT
	release
	end

VioletCity_House1_Text_YouWillTradeWontYou:
	.string "{SE_M_HEAL_BELL}collec{SE_M_SPIT_UP}POKéMON!\n"
	.string "D{SE_M_ATTRACT2}yo{SE_M_DIVE}hav{SE_M_REVERSAL}{SE_M_CHARGE}{STR_VAR_1}?\p"
	.string "Wan{SE_M_SPIT_UP}t{SE_M_ATTRACT2}trad{SE_M_REVERSAL}i{SE_M_SPIT_UP}fo{SE_M_SAND_TOMB}my\n"
	.string "{STR_VAR_2}?$"

VioletCity_House1_Text_MonYouTakeCare:
	.string "Yay{SE_M_DRAGON_RAGE}{SE_M_HEAL_BELL}go{SE_M_SPIT_UP}mysel{SE_M_ACID_ARMOR}{STR_VAR_1}!\p"
	.string "{STR_VAR_2}{SE_M_SUPERSONIC}yo{SE_M_DIVE}tak{SE_M_REVERSAL}care!$"

VioletCity_House1_Text_ThisIsntAMon:
	.string "Uh{SE_M_SUPERSONIC}no{SE_M_SUPERSONIC}{SE_M_HEAL_BELL}don'{SE_M_SPIT_UP}thin{SE_M_ENCORE2}so.\n"
	.string "Tha{SE_M_SPIT_UP}isn'{SE_M_SPIT_UP}{SE_M_CHARGE}{STR_VAR_1}.$"

VioletCity_House1_Text_YouWontTradeMe:
	.string "Yo{SE_M_DIVE}don'{SE_M_SPIT_UP}wan{SE_M_SPIT_UP}t{SE_M_ATTRACT2}trade{SE_M_SING}Aww...$"

VioletCity_House1_Text_After:
	.string "Hi{SE_M_SUPERSONIC}how'{SE_M_GRASSWHISTLE}m{SE_M_YAWN}ol{SE_M_WATERFALL}ONI{SE_M_LOCK_ON}doing?$"

VioletCity_House1_Text_PokefanM:
	.string "{SE_M_BONEMERANG}POKéMO{SE_M_PSYBEAM2}yo{SE_M_DIVE}ge{SE_M_SPIT_UP}i{SE_M_ATTRACT}{SE_M_CHARGE}trade\n"
	.string "grow{SE_M_GRASSWHISTLE}quickly.\p"
	.string "Bu{SE_M_SPIT_UP}i{SE_M_ACID_ARMOR}yo{SE_M_DIVE}don'{SE_M_SPIT_UP}hav{SE_M_REVERSAL}th{SE_M_REVERSAL}right\n"
	.string "GY{SE_M_GIGA_DRAIN}BADGE{SE_M_SUPERSONIC}the{SE_M_YAWN}ma{SE_M_YAWN}disobe{SE_M_YAWN}you.$"

