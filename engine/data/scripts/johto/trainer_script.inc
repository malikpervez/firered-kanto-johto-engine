@ Johto (data/scripts/trainer_script.inc), as built into the FireRed game.

J_Std_RegisteredInMatchCall::
	buffertrainerclassname STR_VAR_1, VAR_0x8000
	buffertrainername STR_VAR_2, VAR_0x8000
	closemessage
	delay 30
	playfanfare MUS_REGISTER_MATCH_CALL
	msgbox J_gText_RegisteredTrainerinPokeNav, MSGBOX_DEFAULT
	waitfanfare
	closemessage
	delay 30
	return

J_EventScript_TryGetTrainerScript::
	special ShouldTryGetTrainerScript
	goto_if_eq VAR_RESULT, TRUE, J_EventScript_GotoTrainerScript
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

