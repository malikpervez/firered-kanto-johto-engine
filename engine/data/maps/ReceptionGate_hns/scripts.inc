@ Johto (data/maps/ReceptionGate_hns/scripts.inc), as built into the FireRed game.

ReceptionGate_hns_MapScripts::
	.byte 0

ReceptionGate_EventScript_Janine::
	lock
	faceplayer
	msgbox ReceptionGate_Text_Janine, MSGBOX_DEFAULT
	closemessage
	fadescreenswapbuffers FADE_TO_BLACK
	setflag JOHTO_FLAG_HIDE_ROUTE22_JANINE
	removeobject LOCALID_INDIGOJUNCTION_JANINE
	fadescreenswapbuffers FADE_FROM_BLACK
	clearflag JOHTO_FLAG_HIDE_DOJO_JANINE
	release
	end

ReceptionGate_Text_Janine:
	.string "JANINE{SE_M_HEAT_WAVE}I'{SE_M_MILK_DRINK}o{SE_M_ATTRACT}th{SE_M_REVERSAL}wa{SE_M_YAWN}t{SE_M_ATTRACT2}m{SE_M_YAWN}dad's\n"
	.string "hous{SE_M_REVERSAL}t{SE_M_ATTRACT2}giv{SE_M_REVERSAL}hi{SE_M_MILK_DRINK}hi{SE_M_GRASSWHISTLE}lunch.\p"
	.string "Th{SE_M_REVERSAL}ELIT{SE_M_SWORDS_DANCE}FOU{SE_M_MINIMIZE}ha{SE_M_GRASSWHISTLE}n{SE_M_ATTRACT2}tim{SE_M_REVERSAL}t{SE_M_ATTRACT2}rest\n"
	.string "da{SE_M_YAWN}o{SE_M_SAND_TOMB}night{SE_M_PERISH_SONG}It'{SE_M_GRASSWHISTLE}suc{SE_M_TRI_ATTACK}har{SE_M_WATERFALL}work,\l"
	.string "yo{SE_M_DIVE}know?\p"
	.string "I{SE_M_ACID_ARMOR}you'r{SE_M_REVERSAL}read{SE_M_YAWN}fo{SE_M_SAND_TOMB}anothe{SE_M_SAND_TOMB}battle,\n"
	.string "I'l{SE_M_BATON_PASS}b{SE_M_REVERSAL}a{SE_M_SPIT_UP}th{SE_M_REVERSAL}DOJ{SE_M_SOLAR_BEAM}later.$"

ReceptionGate_EventScript_Officer::
	msgbox VictoryRoadGate_Text_EightBadges, MSGBOX_NPC
	end

ReceptionGate_Trigger::
	lock
	playse SE_PIN
	applymovement LOCALID_INDIGOJUNCTION_POLICEMAN, J_Common_Movement_ExclamationMark
	delay 55
	waitmovement LOCALID_INDIGOJUNCTION_POLICEMAN
	goto_if_lt JOHTO_VAR_ECRUTEAK_CITY_THEATER, 8, ReceptionGate_EventScript_Kimono
	msgbox VictoryRoadGate_Text_Officer, MSGBOX_DEFAULT
	goto_if_unset JOHTO_FLAG_BADGE08_GET, ReceptionGate_EventScript_NotEnough
	msgbox VictoryRoadGate_Text_EightBadges, MSGBOX_DEFAULT
	closemessage
	setvar JOHTO_VAR_ROUTE27_STATE, 2
	release
	end

ReceptionGate_EventScript_Kimono::
	msgbox VictoryRoadGate_Text_Kimono, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, J_Common_Movement_WalkDown1
	waitmovement 0
	release
	end

ReceptionGate_EventScript_NotEnough::
	msgbox VictoryRoadGate_Text_NotEnoughBadges, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, J_Common_Movement_WalkDown1
	waitmovement 0
	release
	end

ReceptionGate_EventScript_SilverGuard::
	msgbox VictoryRoadGate_Text_LeftBlackBelt, MSGBOX_NPC
	end

ReceptionGate_EventScript_KantoGuard::
	msgbox VictoryRoadGate_Text_RightBlackBelt, MSGBOX_NPC
	end

VictoryRoadGate_Text_Officer:
	.string "Onl{SE_M_YAWN}trainer{SE_M_GRASSWHISTLE}wh{SE_M_ATTRACT2}hav{SE_M_REVERSAL}proven\n"
	.string "themselve{SE_M_GRASSWHISTLE}ma{SE_M_YAWN}pass.$"

VictoryRoadGate_Text_Kimono:
	.string "Sorr{SE_M_YAWN}kid{SE_M_SUPERSONIC}thi{SE_M_GRASSWHISTLE}wa{SE_M_YAWN}i{SE_M_GRASSWHISTLE}close{SE_M_WATERFALL}until\n"
	.string "someon{SE_M_REVERSAL}deal{SE_M_GRASSWHISTLE}wit{SE_M_TRI_ATTACK}tha{SE_M_SPIT_UP}LEGENDARY\l"
	.string "POKéMON...$"

VictoryRoadGate_Text_NotEnoughBadges:
	.string "Yo{SE_M_DIVE}don'{SE_M_SPIT_UP}hav{SE_M_REVERSAL}al{SE_M_BATON_PASS}th{SE_M_REVERSAL}GY{SE_M_GIGA_DRAIN}BADGES\n"
	.string "o{SE_M_ACID_ARMOR}JOHTO.\p"
	.string "I'{SE_M_MILK_DRINK}sorry{SE_M_SUPERSONIC}bu{SE_M_SPIT_UP}{SE_M_HEAL_BELL}can'{SE_M_SPIT_UP}le{SE_M_SPIT_UP}yo{SE_M_DIVE}go\n"
	.string "through.$"

VictoryRoadGate_Text_EightBadges:
	.string "Oh{SE_M_DRAGON_RAGE}Th{SE_M_REVERSAL}eigh{SE_M_SPIT_UP}BADGE{SE_M_SKETCH}o{SE_M_ACID_ARMOR}JOHTO!\p"
	.string "Please{SE_M_SUPERSONIC}g{SE_M_ATTRACT2}righ{SE_M_SPIT_UP}o{SE_M_ATTRACT}through!$"

VictoryRoadGate_Text_LeftBlackBelt:
	.string "Thi{SE_M_GRASSWHISTLE}wa{SE_M_YAWN}lead{SE_M_GRASSWHISTLE}t{SE_M_ATTRACT2}MT.SILVER.\p"
	.string "You'l{SE_M_BATON_PASS}se{SE_M_REVERSAL}scary-stron{SE_M_SANDSTORM}POKéMO{SE_M_PSYBEAM2}out\n"
	.string "there.$"

VictoryRoadGate_Text_RightBlackBelt:
	.string "Of{SE_M_ACID_ARMOR}t{SE_M_ATTRACT2}th{SE_M_REVERSAL}POKéMO{SE_M_PSYBEAM2}LEAGUE{SE_M_SUPERSONIC}ar{SE_M_REVERSAL}you?\p"
	.string "Th{SE_M_REVERSAL}ELIT{SE_M_SWORDS_DANCE}FOU{SE_M_MINIMIZE}ar{SE_M_REVERSAL}s{SE_M_ATTRACT2}stron{SE_M_SANDSTORM}it's\n"
	.string "scary{SE_M_SUPERSONIC}an{SE_M_WATERFALL}they'r{SE_M_REVERSAL}read{SE_M_YAWN}fo{SE_M_SAND_TOMB}you!$"

