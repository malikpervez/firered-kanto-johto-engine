@ Johto (data/maps/Gate_EcruteakCity_Route42_hns/scripts.inc), as built into the FireRed game.

Gate_EcruteakCity_Route42_hns_MapScripts::
	.byte 0

Gate_EcruteakCity_Route42_EventScript_Policeman::
	lock
	faceplayer
	msgbox Route42_Text_EcruteakGateOfficer, MSGBOX_DEFAULT
	closemessage
	release
	end

Route42_Text_EcruteakGateOfficer:
	.string "MT.MORTA{SE_M_MINIMIZE}i{SE_M_GRASSWHISTLE}lik{SE_M_REVERSAL}{SE_M_CHARGE}maze\n"
	.string "inside.\p"
	.string "B{SE_M_REVERSAL}careful{SE_M_PERISH_SONG}Don'{SE_M_SPIT_UP}ge{SE_M_SPIT_UP}lost\n"
	.string "i{SE_M_ATTRACT}there.$"

