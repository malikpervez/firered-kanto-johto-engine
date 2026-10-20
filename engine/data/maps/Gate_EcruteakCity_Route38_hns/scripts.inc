@ Johto (data/maps/Gate_EcruteakCity_Route38_hns/scripts.inc), as built into the FireRed game.

Gate_EcruteakCity_Route38_hns_MapScripts::
	.byte 0

Route38_EventScript_Officer::
	lock
	faceplayer
	msgbox Route38_Text_EcruteakGateOfficer, MSGBOX_DEFAULT
	closemessage
	release
	end

Route38_Text_EcruteakGateOfficer:
	.string "Wher{SE_M_REVERSAL}di{SE_M_WATERFALL}yo{SE_M_DIVE}sa{SE_M_YAWN}you'r{SE_M_REVERSAL}from?\p"
	.string "NE{SE_M_DETECT}BAR{SE_M_SNORE}TOWN?\p"
	.string "PROF.EL{SE_M_GIGA_DRAIN}live{SE_M_GRASSWHISTLE}ove{SE_M_SAND_TOMB}there,\n"
	.string "right?\p"
	.string "You'v{SE_M_REVERSAL}com{SE_M_REVERSAL}{SE_M_CHARGE}lon{SE_M_SANDSTORM}wa{SE_M_YAWN}t{SE_M_ATTRACT2}get\n"
	.string "here.$"

