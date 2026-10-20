@ Johto (data/scripts/cave_of_origin.inc), as built into the FireRed game.

J_CaveOfOrigin_EventScript_LegendaryCry::
	lockall
	waitse
	playmoncry SPECIES_KYOGRE, CRY_MODE_ENCOUNTER
	waitmoncry
	setvar VAR_TEMP_5, 1
	releaseall
	end

J_CaveOfOrigin_EventScript_Shake1::
	lockall
	setvar VAR_TEMP_1, 1
	goto J_CaveOfOrigin_EventScript_Shake
	end

J_CaveOfOrigin_EventScript_Shake2::
	lockall
	setvar VAR_TEMP_2, 1
	goto J_CaveOfOrigin_EventScript_Shake
	end

J_CaveOfOrigin_EventScript_Shake3::
	lockall
	setvar VAR_TEMP_3, 1
	goto J_CaveOfOrigin_EventScript_Shake
	end

J_CaveOfOrigin_EventScript_Shake::
	setvar VAR_0x8004, 1
	setvar VAR_0x8005, 1
	setvar VAR_0x8006, 8
	setvar VAR_0x8007, 5
	special ShakeCamera
	waitstate
	releaseall
	end

J_CaveOfOrigin_EventScript_DisableTriggers::
	setvar VAR_TEMP_1, 1
	setvar VAR_TEMP_2, 1
	setvar VAR_TEMP_3, 1
	setvar VAR_TEMP_4, 1
	setvar VAR_TEMP_5, 1
	return

