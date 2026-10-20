@ Johto (data/maps/CherrygroveCity_House3_hns/scripts.inc), as built into the FireRed game.

CherrygroveCity_House3_hns_MapScripts::
	.byte 0

CherrygroveCity_House3_EventScript_Boy::
	lock
	faceplayer
	msgbox CherrygroveCity_EvolutionHouse_Text_Youngster, MSGBOX_DEFAULT
	closemessage
	release
	end

CherrygroveCity_House3_EventScript_Girl::
	lock
	faceplayer
	msgbox CherrygroveCity_EvolutionHouse_Text_Lass, MSGBOX_DEFAULT
	closemessage
	release
	end

CherrygroveCity_EvolutionHouse_Text_Youngster:
	.string "POKéMO{SE_M_PSYBEAM2}gai{SE_M_ATTRACT}experienc{SE_M_REVERSAL}in\n"
	.string "battl{SE_M_REVERSAL}an{SE_M_WATERFALL}chang{SE_M_REVERSAL}thei{SE_M_SAND_TOMB}form.$"

CherrygroveCity_EvolutionHouse_Text_Lass:
	.string "POKéMO{SE_M_PSYBEAM2}change?\p"
	.string "{SE_M_HEAL_BELL}woul{SE_M_WATERFALL}b{SE_M_REVERSAL}shocke{SE_M_WATERFALL}i{SE_M_ACID_ARMOR}on{SE_M_REVERSAL}did\n"
	.string "that!$"

