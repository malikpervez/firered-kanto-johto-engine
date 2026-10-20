@ Johto (data/maps/BlackthornCity_House2_hns/scripts.inc), as built into the FireRed game.

BlackthornCity_House2_hns_MapScripts::
	.byte 0

BlackthornCity_House2_EventScript_Emy::
	lock
	faceplayer
	goto_if_set JOHTO_FLAG_BLACKTHORN_NPC_TRADE_COMPLETED, BlackthornCity_House2_EventScript_TradeCompleted
	ingame_trade INGAME_TRADE_MR_MIME, BlackthornCity_House2_Text_YouWillTradeWontYou, BlackthornCity_House2_EventScript_DeclineTrade, BlackthornCity_House2_EventScript_NotRequestedMon, BlackthornCity_House2_Text_MonYouTakeCare
	setflag JOHTO_FLAG_BLACKTHORN_NPC_TRADE_COMPLETED
	release
	end

BlackthornCity_House2_EventScript_DeclineTrade::
	msgbox BlackthornCity_House2_Text_YouWontTradeMe, MSGBOX_DEFAULT
	release
	end

BlackthornCity_House2_EventScript_NotRequestedMon::
	bufferspeciesname STR_VAR_1, VAR_0x8009
	msgbox BlackthornCity_House2_Text_ThisIsntAMon, MSGBOX_DEFAULT
	release
	end

BlackthornCity_House2_EventScript_TradeCompleted::
	msgbox BlackthornCity_House2_Text_After, MSGBOX_DEFAULT
	release
	end

BlackthornCity_House2_Text_YouWillTradeWontYou:
	.string "{SE_M_HEAL_BELL}collec{SE_M_SPIT_UP}POKéMON!\n"
	.string "D{SE_M_ATTRACT2}yo{SE_M_DIVE}hav{SE_M_REVERSAL}{SE_M_CHARGE}{STR_VAR_1}?\p"
	.string "Wan{SE_M_SPIT_UP}t{SE_M_ATTRACT2}trad{SE_M_REVERSAL}i{SE_M_SPIT_UP}fo{SE_M_SAND_TOMB}my\n"
	.string "{STR_VAR_2}?$"

BlackthornCity_House2_Text_MonYouTakeCare:
	.string "Yay{SE_M_DRAGON_RAGE}{SE_M_HEAL_BELL}go{SE_M_SPIT_UP}mysel{SE_M_ACID_ARMOR}{STR_VAR_1}!\p"
	.string "{STR_VAR_2}{SE_M_SUPERSONIC}yo{SE_M_DIVE}tak{SE_M_REVERSAL}care!$"

BlackthornCity_House2_Text_ThisIsntAMon:
	.string "Uh{SE_M_SUPERSONIC}no{SE_M_SUPERSONIC}{SE_M_HEAL_BELL}don'{SE_M_SPIT_UP}thin{SE_M_ENCORE2}so.\n"
	.string "Tha{SE_M_SPIT_UP}isn'{SE_M_SPIT_UP}{SE_M_CHARGE}{STR_VAR_1}.$"

BlackthornCity_House2_Text_YouWontTradeMe:
	.string "Yo{SE_M_DIVE}don'{SE_M_SPIT_UP}wan{SE_M_SPIT_UP}t{SE_M_ATTRACT2}trade{SE_M_SING}Aww...$"

BlackthornCity_House2_Text_After:
	.string "Hi{SE_M_SUPERSONIC}how'{SE_M_GRASSWHISTLE}m{SE_M_YAWN}ol{SE_M_WATERFALL}M{SE_M_MINIMIZE}MIM{SE_M_SWORDS_DANCE}doing?$"

