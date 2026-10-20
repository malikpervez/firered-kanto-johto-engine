@ Johto (data/maps/GoldenrodCity_DepartmentStore_6F_hns/scripts.inc), as built into the FireRed game.

GoldenrodCity_DepartmentStore_6F_hns_MapScripts::
	map_script 2, GoldenrodDeptElevator_OnFrame
	.byte 0

GoldenrodDeptStore6_EventScript_Whitney::
	lock
	faceplayer
	msgbox GoldenrodDeptStore6_Text_Whitney, MSGBOX_DEFAULT
	closemessage
	fadescreenswapbuffers 1
	setflag 8304
	removeobject 4
	fadescreenswapbuffers 0
	clearflag 8401
	release
	end

GoldenrodDeptStore6_Text_Whitney:
	.string "{PLAYER}{SE_M_DRAGON_RAGE}Fanc{SE_M_YAWN}seein{SE_M_SANDSTORM}yo{SE_M_DIVE}here!\p"
	.string "I'{SE_M_MILK_DRINK}pickin{SE_M_SANDSTORM}u{SE_M_MORNING_SUN}somethin{SE_M_SANDSTORM}for\n"
	.string "m{SE_M_YAWN}MILTANK.\p"
	.string "I{SE_M_ACID_ARMOR}yo{SE_M_DIVE}wan{SE_M_SPIT_UP}anothe{SE_M_SAND_TOMB}battle{SE_M_SUPERSONIC}com{SE_M_REVERSAL}to\n"
	.string "th{SE_M_REVERSAL}FIGHTIN{SE_M_SWAGGER}DOJO!$"

GoldenrodCity_DepartmentStore_6F_EventScript_Jose::
	lock
	faceplayer
	goto_if_set 8771, GoldenrodCity_DepartmentStore_6F_EventScript_TradeCompleted
	ingame_trade INGAME_TRADE_MACHOP, GoldenrodCity_DepartmentStore_6F_Text_YouWillTradeWontYou, GoldenrodCity_DepartmentStore_6F_EventScript_DeclineTrade, GoldenrodCity_DepartmentStore_6F_EventScript_NotRequestedMon, GoldenrodCity_DepartmentStore_6F_Text_MonYouTakeCare
	setflag 8771
	release
	end

GoldenrodCity_DepartmentStore_6F_EventScript_DeclineTrade::
	msgbox GoldenrodCity_DepartmentStore_6F_Text_YouWontTradeMe, MSGBOX_DEFAULT
	release
	end

GoldenrodCity_DepartmentStore_6F_EventScript_NotRequestedMon::
	bufferspeciesname STR_VAR_1, 32777
	msgbox GoldenrodCity_DepartmentStore_6F_Text_ThisIsntAMon, MSGBOX_DEFAULT
	release
	end

GoldenrodCity_DepartmentStore_6F_EventScript_TradeCompleted::
	msgbox GoldenrodCity_DepartmentStore_6F_Text_After, MSGBOX_DEFAULT
	release
	end

GoldenrodCity_DepartmentStore_6F_Text_YouWillTradeWontYou:
	.string "{SE_M_HEAL_BELL}collec{SE_M_SPIT_UP}POKéMON!\n"
	.string "D{SE_M_ATTRACT2}yo{SE_M_DIVE}hav{SE_M_REVERSAL}{SE_M_CHARGE}{STR_VAR_1}?\p"
	.string "Wan{SE_M_SPIT_UP}t{SE_M_ATTRACT2}trad{SE_M_REVERSAL}i{SE_M_SPIT_UP}fo{SE_M_SAND_TOMB}my\n"
	.string "{STR_VAR_2}?$"

GoldenrodCity_DepartmentStore_6F_Text_MonYouTakeCare:
	.string "Yay{SE_M_DRAGON_RAGE}{SE_M_HEAL_BELL}go{SE_M_SPIT_UP}mysel{SE_M_ACID_ARMOR}{STR_VAR_1}!\p"
	.string "{STR_VAR_2}{SE_M_SUPERSONIC}yo{SE_M_DIVE}tak{SE_M_REVERSAL}care!$"

GoldenrodCity_DepartmentStore_6F_Text_ThisIsntAMon:
	.string "Uh{SE_M_SUPERSONIC}no{SE_M_SUPERSONIC}{SE_M_HEAL_BELL}don'{SE_M_SPIT_UP}thin{SE_M_ENCORE2}so.\n"
	.string "Tha{SE_M_SPIT_UP}isn'{SE_M_SPIT_UP}{SE_M_CHARGE}{STR_VAR_1}.$"

GoldenrodCity_DepartmentStore_6F_Text_YouWontTradeMe:
	.string "Yo{SE_M_DIVE}don'{SE_M_SPIT_UP}wan{SE_M_SPIT_UP}t{SE_M_ATTRACT2}trade{SE_M_SING}Aww...$"

GoldenrodCity_DepartmentStore_6F_Text_After:
	.string "Hi{SE_M_SUPERSONIC}how'{SE_M_GRASSWHISTLE}m{SE_M_YAWN}ol{SE_M_WATERFALL}MACHO{SE_M_PETAL_DANCE}doing?$"

GoldenrodDeptStore6_EventScript_Lass::
	lock
	faceplayer
	msgbox GoldenrodDeptStore_Text_6FLass, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodDeptStore6_EventScript_Nerd::
	lock
	faceplayer
	msgbox GoldenrodDeptStore_Text_6FSuperNerd, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodDeptStore6_EventScript_Sign::
	lock
	faceplayer
	msgbox GoldenrodDeptStore_Text_6FDirectory, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodDeptStore_Text_6FLass:
	.string "D{SE_M_ATTRACT2}yo{SE_M_DIVE}liste{SE_M_ATTRACT}t{SE_M_ATTRACT2}LUCK{SE_M_MOONLIGHT}CHANNEL?\p"
	.string "The{SE_M_YAWN}sa{SE_M_YAWN}i{SE_M_ACID_ARMOR}yo{SE_M_DIVE}wan{SE_M_SPIT_UP}t{SE_M_ATTRACT2}win,\n"
	.string "yo{SE_M_DIVE}shoul{SE_M_WATERFALL}trad{SE_M_REVERSAL}POKéMO{SE_M_PSYBEAM2}wit{SE_M_TRI_ATTACK}as\l"
	.string "man{SE_M_YAWN}peopl{SE_M_REVERSAL}a{SE_M_GRASSWHISTLE}possibl{SE_M_REVERSAL}t{SE_M_ATTRACT2}get\l"
	.string "differen{SE_M_SPIT_UP}I{SE_M_FAINT_ATTACK}numbers.\p"
	.string "However{SE_M_SUPERSONIC}tradin{SE_M_SANDSTORM}isn'{SE_M_SPIT_UP}a{SE_M_GRASSWHISTLE}widely\n"
	.string "availabl{SE_M_REVERSAL}a{SE_M_GRASSWHISTLE}i{SE_M_SPIT_UP}onc{SE_M_REVERSAL}was.$"

GoldenrodDeptStore_Text_6FSuperNerd:
	.string "I{SE_M_ACID_ARMOR}you'r{SE_M_REVERSAL}tired{SE_M_SUPERSONIC}tr{SE_M_YAWN}th{SE_M_REVERSAL}vending\n"
	.string "machine'{SE_M_GRASSWHISTLE}drinks.\p"
	.string "You{SE_M_SAND_TOMB}POKéMO{SE_M_PSYBEAM2}wil{SE_M_BATON_PASS}lov{SE_M_REVERSAL}the{SE_M_MILK_DRINK}too.$"

GoldenrodDeptStore_Text_6FDirectory:
	.string "Tak{SE_M_REVERSAL}{SE_M_CHARGE}Brea{SE_M_ENCORE2}fro{SE_M_MILK_DRINK}Shopping!\p"
	.string "6{SE_M_LEER}TRANQUI{SE_M_BRICK_BREAK}SQUARE$"

