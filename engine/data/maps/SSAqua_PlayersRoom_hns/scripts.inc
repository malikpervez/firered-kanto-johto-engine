@ Johto (data/maps/SSAqua_PlayersRoom_hns/scripts.inc), as built into the FireRed game.

SSAqua_PlayersRoom_hns_MapScripts::
	.byte 0

SSAquaRooms_EventScript_Bed::
	specialvar VAR_RESULT, IsPokecenterChallengeActivated
	goto_if_eq VAR_RESULT, TRUE, SSAquaRooms_EventScript_Bed_PokecenterChallenge
	lockall
	msgbox SSAquaRooms_Text_TakeRestOnBed, MSGBOX_DEFAULT
	closemessage
	call J_Common_EventScript_OutOfCenterPartyHeal
	releaseall
	end

SSAquaRooms_EventScript_Bed_PokecenterChallenge::
	msgbox SSAquaRooms_Text_TakeRestOnBed_PokecenterChallenge, MSGBOX_DEFAULT
	closemessage
	release
	end

SSAquaRooms_Text_TakeRestOnBed_PokecenterChallenge:
	.string "Sorry{SE_M_SUPERSONIC}yo{SE_M_DIVE}ar{SE_M_REVERSAL}playin{SE_M_SANDSTORM}with\n"
	.string "th{SE_M_REVERSAL}POKéCENTE{SE_M_MINIMIZE}challenge!$"

SSAquaRooms_Text_TakeRestOnBed:
	.string "There'{SE_M_GRASSWHISTLE}{SE_M_CHARGE}bed…\n"
	.string "Let'{SE_M_GRASSWHISTLE}tak{SE_M_REVERSAL}{SE_M_CHARGE}rest.$"

