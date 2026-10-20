@ Johto (data/maps/OlivineCity_House2_hns/scripts.inc), as built into the FireRed game.

OlivineCity_House2_hns_MapScripts::
	.byte 0

OlivineCity_EventScript_Punisher::
	lock
	faceplayer
	msgbox OlivineCity_Text_PunishmentBro, MSGBOX_DEFAULT
	closemessage
	release
	end

OlivineCity_EventScript_PunisherBoy::
	lock
	faceplayer
	msgbox OlivineCity_Text_PunishmentBoy, MSGBOX_DEFAULT
	closemessage
	release
	end

OlivineCity_Text_PunishmentBro:
	.string "Alon{SE_M_SANDSTORM}th{SE_M_REVERSAL}wa{SE_M_YAWN}t{SE_M_ATTRACT2}CIANWOOD,\n"
	.string "ther{SE_M_REVERSAL}ar{SE_M_REVERSAL}fou{SE_M_SAND_TOMB}deserte{SE_M_WATERFALL}islands.\p"
	.string "Ba{SE_M_WATERFALL}kid{SE_M_GRASSWHISTLE}ar{SE_M_REVERSAL}take{SE_M_ATTRACT}t{SE_M_ATTRACT2}those\n"
	.string "island{SE_M_GRASSWHISTLE}a{SE_M_GRASSWHISTLE}punishment!$"

OlivineCity_Text_PunishmentBoy:
	.string "Wheneve{SE_M_SAND_TOMB}{SE_M_HEAL_BELL}ge{SE_M_SPIT_UP}i{SE_M_ATTRACT}trouble,\n"
	.string "bi{SE_M_SANDSTORM}br{SE_M_ATTRACT2}alway{SE_M_GRASSWHISTLE}scare{SE_M_GRASSWHISTLE}me.$"

