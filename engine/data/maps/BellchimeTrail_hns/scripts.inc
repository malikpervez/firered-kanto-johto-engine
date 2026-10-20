@ Johto (data/maps/BellchimeTrail_hns/scripts.inc), as built into the FireRed game.

BellchimeTrail_hns_MapScripts::
	.byte 0

BellchimeTrail_EventScript_Morty::
	lock
	faceplayer
	msgbox BellchimeTrail_Text_Morty, MSGBOX_DEFAULT
	closemessage
	fadescreenswapbuffers FADE_TO_BLACK
	setflag JOHTO_FLAG_HIDE_BELLCHIME_MORTY
	removeobject LOCALID_BELLCHIME_MORTY
	fadescreenswapbuffers FADE_FROM_BLACK
	clearflag JOHTO_FLAG_HIDE_DOJO_MORTY
	release
	end

BellchimeTrail_Text_Morty:
	.string "MORTY{SE_M_HEAT_WAVE}Th{SE_M_REVERSAL}legendar{SE_M_YAWN}POKéMON\n"
	.string "di{SE_M_WATERFALL}no{SE_M_SPIT_UP}choos{SE_M_REVERSAL}me...\p"
	.string "Bu{SE_M_SPIT_UP}tha{SE_M_SPIT_UP}doe{SE_M_GRASSWHISTLE}no{SE_M_SPIT_UP}mea{SE_M_ATTRACT}tha{SE_M_SPIT_UP}I\n"
	.string "hav{SE_M_REVERSAL}los{SE_M_SPIT_UP}ou{SE_M_SPIT_UP}o{SE_M_ATTRACT}m{SE_M_YAWN}future.\p"
	.string "{SE_M_HEAL_BELL}wil{SE_M_BATON_PASS}continu{SE_M_REVERSAL}m{SE_M_YAWN}trainin{SE_M_SANDSTORM}unti{SE_M_BATON_PASS}I\n"
	.string "{SE_M_HEAL_BELL}discove{SE_M_SAND_TOMB}{SE_M_CHARGE}ne{SE_M_TWISTER}futur{SE_M_REVERSAL}fo{SE_M_SAND_TOMB}me.\p"
	.string "I{SE_M_ACID_ARMOR}yo{SE_M_DIVE}see{SE_M_ENCORE2}anothe{SE_M_SAND_TOMB}battle{SE_M_SUPERSONIC}find\n"
	.string "m{SE_M_REVERSAL}a{SE_M_SPIT_UP}th{SE_M_REVERSAL}FIGHTIN{SE_M_SWAGGER}DOJO.$"

EcruteakBellchimeTrail_EventScript_Item_BigMushroom::
	finditem ITEM_BIG_MUSHROOM
	end

EcruteakBellchimeTrail_EventScript_DoorTrigger::
	lock
	opendoor 28, 12
	waitdooranim
	addobject OBJ_EVENT_ID_CAMERA
	removeobject OBJ_EVENT_ID_PLAYER
	closedoor 28, 12
	applymovement OBJ_EVENT_ID_CAMERA, EcruteakBellchimeTrail_Movement_CameraPanUp
	waitmovement 0
	warp MAP_TIN_TOWER_1F_HNS, 1
	release
	end

EcruteakBellchimeTrail_Movement_CameraPanUp::
	slide_up
	slide_up
	slide_up
	slide_up
	slide_up
	slide_up
	slide_up
	step_end

