@ Johto (data/scripts/trainer_script.inc), as built into the FireRed game.

J_Std_RegisteredInMatchCall::
	buffertrainerclassname STR_VAR_1, 32768
	buffertrainername STR_VAR_2, 32768
	closemessage
	delay 30
	playfanfare 460
	msgbox J_gText_RegisteredTrainerinPokeNav, MSGBOX_DEFAULT
	waitfanfare
	closemessage
	delay 30
	return

J_EventScript_TryGetTrainerScript::
	special ShouldTryGetTrainerScript
	goto_if_eq 32781, TRUE, J_EventScript_GotoTrainerScript
	releaseall
	end

J_EventScript_GotoTrainerScript::
	gotobeatenscript
	releaseall
	end

J_EventScript_ObjectApproachPlayer::
	lock
	special DoTrainerApproach
	waitstate
	gotonative LoadTrainerObjectScript

