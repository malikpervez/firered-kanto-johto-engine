@ Johto (data/scripts/cave_of_origin.inc), as built into the FireRed game.

J_CaveOfOrigin_EventScript_LegendaryCry::
	lockall
	waitse
	playmoncry 382, 2
	waitmoncry
	setvar 16389, 1
	releaseall
	end

J_CaveOfOrigin_EventScript_Shake1::
	lockall
	setvar 16385, 1
	goto J_CaveOfOrigin_EventScript_Shake
	end

J_CaveOfOrigin_EventScript_Shake2::
	lockall
	setvar 16386, 1
	goto J_CaveOfOrigin_EventScript_Shake
	end

J_CaveOfOrigin_EventScript_Shake3::
	lockall
	setvar 16387, 1
	goto J_CaveOfOrigin_EventScript_Shake
	end

J_CaveOfOrigin_EventScript_Shake::
	setvar 32772, 1
	setvar 32773, 1
	setvar 32774, 8
	setvar 32775, 5
	special ShakeCamera
	waitstate
	releaseall
	end

J_CaveOfOrigin_EventScript_DisableTriggers::
	setvar 16385, 1
	setvar 16386, 1
	setvar 16387, 1
	setvar 16388, 1
	setvar 16389, 1
	return

