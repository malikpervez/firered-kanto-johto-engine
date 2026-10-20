@ Johto (data/scripts/record_mix.inc), as built into the FireRed game.

J_EventScript_MixRecordsPrompt::
	lock
	faceplayer
	msgbox J_Text_WouldYouLikeToMixRecords, MSGBOX_YESNO
	goto_if_eq 32781, YES, J_EventScript_MixRecords
	goto_if_eq 32781, NO, J_EventScript_EndMixRecords
	goto J_EventScript_EndMixRecords

J_EventScript_MixRecords::
	special RecordMixingPlayerSpotTriggered
	waitstate
	lock
	faceplayer

J_EventScript_EndMixRecords::
	message J_Text_WeHopeToSeeYouAgain
	waitmessage
	waitbuttonpress
	release
	end

