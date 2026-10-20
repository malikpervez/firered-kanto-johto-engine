@ Johto (data/maps/MtSilver_Outside_hns/scripts.inc), as built into the FireRed game.

MtSilver_Outside_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, MtSilver_Outside_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, J_SetTimeEncounters
	.byte 0

MtSilver_Outside_OnTransition:
	callnative SetTimeBasedEncounters
	setflag JOHTO_FLAG_VISITED_MT_SILVER
	end

MtSilver_Outside_EventScript_Sign::
	msgbox MtSilver_Outside_Text_Sign, MSGBOX_SIGN
	end

MtSilver_Outside_Text_Sign:
	.string "MT{SE_M_PERISH_SONG}SILVER$"

