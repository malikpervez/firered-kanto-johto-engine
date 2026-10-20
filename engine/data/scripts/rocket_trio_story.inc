#ifdef FIRERED
@ James deliberately speaks from offscreen in JT01/JT04; no substitute actor
@ represents him. Jessie and Meowth use their actual graphics. The net is
@ conveyed by narration/Meowth's struggle, not a claimed net graphic.
@ JT03 retains its existing comic scene. JT02 offers a separate optional battle.
@ Genuine Jessie/James visual restore hooks are an atomic asset integration dependency.
JT_Return::
	return
JT_Release::
	releaseall
	end
JT01_Visibility::
	setflag FLAG_TEMP_1C
	callnative Special_CharacterStoryAdopt, requests_effects=1
	goto_if_eq VAR_RESULT, FALSE, JT_Return
	goto_if_unset FLAG_GOT_FOSSIL_FROM_MT_MOON, JT_Return
	goto_if_set FLAG_BADGE02_GET, JT_Return
	goto_if_set FLAG_SYS_GAME_CLEAR, JT_Return
	goto_if_set FLAG_JT01_SEEN, JT_Return
	goto_if_set FLAG_JT02_SEEN, JT_Return
	goto_if_set FLAG_JT03_SEEN, JT_Return
	clearflag FLAG_TEMP_1C
	return
JT01_Net::
	lockall
	faceplayer
	call JT01_Visibility
	goto_if_set FLAG_TEMP_1C, JT_Release
	msgbox JT01_Text_Jessie
	msgbox JT01_Text_OffscreenJames
	msgbox JT01_Text_James
	msgbox JT01_Text_Net
	applymovement 15, JT_Movement_TangledMeowth
	waitmovement 0
	msgbox JT01_Text_Meowth
	setflag FLAG_JT01_SEEN
	closemessage
	fadescreen FADE_TO_BLACK
	removeobject 14
	removeobject 15
	setflag FLAG_TEMP_1C
	fadescreen FADE_FROM_BLACK
	releaseall
	end
JT04_Visibility::
	setflag FLAG_TEMP_1C
	callnative Special_CharacterStoryAdopt, requests_effects=1
	goto_if_eq VAR_RESULT, FALSE, JT_Return
	@ This is the actual post-battle crisis receipt, never legacy exemption,
	@ native Lugia suppression, ownership, Dex entries or a link-only result.
	goto_if_unset FLAG_LG_FINAL_RESOLVED, JT_Return
	goto_if_set FLAG_JT04_SEEN, JT_Return
	callnative Special_RainbowStoryAllReplicasResolved, requests_effects=1
	goto_if_eq VAR_RESULT, FALSE, JT_Return
	clearflag FLAG_TEMP_1C
	return
JT04_Aftermath::
	lockall
	faceplayer
	call JT04_Visibility
	goto_if_set FLAG_TEMP_1C, JT_Release
	msgbox JT04_Text_Rescued
	playmoncry SPECIES_SEEL, 0
	waitmoncry
	msgbox JT04_Text_OffscreenJames
	msgbox JT04_Text_James
	msgbox JT04_Text_Jessie
	msgbox JT04_Text_Meowth
	applymovement 51, JT_Movement_FreedSeel
	waitmovement 0
	setflag FLAG_JT04_SEEN
	closemessage
	fadescreen FADE_TO_BLACK
	removeobject 49
	removeobject 50
	removeobject 51
	setflag FLAG_TEMP_1C
	fadescreen FADE_FROM_BLACK
	releaseall
	end
JT_Movement_TangledMeowth::
	walk_in_place_faster_left
	walk_in_place_faster_right
	walk_in_place_faster_left
	step_end
JT_Movement_FreedSeel::
	jump_in_place_down
	step_end
JT_CeladonVisibility::
	setflag FLAG_TEMP_1C
	callnative Special_CharacterStoryAdopt, requests_effects=1
	goto_if_eq VAR_RESULT, FALSE, JT_Return
	goto_if_unset FLAG_HIDE_CELADON_ROCKETS, JT_Return
	checktrainerflag TRAINER_STORY_JESSIE
	goto_if FALSE, JT_CeladonShowDuo
	checktrainerflag TRAINER_STORY_JAMES
	goto_if TRUE, JT_Return
JT_CeladonShowDuo::
	clearflag FLAG_TEMP_1C
	return
JT_GoldenrodVisibility::
	setflag FLAG_TEMP_1C
	callnative Special_CharacterStoryAdopt, requests_effects=1
	goto_if_eq VAR_RESULT, FALSE, JT_Return
	goto_if_lt JOHTO_VAR_GOLDENROD_CITY_STATE, 1, JT_Return
	goto_if_ge JOHTO_VAR_GOLDENROD_CITY_STATE, 6, JT_Return
	goto_if_set FLAG_JT03_SEEN, JT_Return
	clearflag FLAG_TEMP_1C
	return
JT02_Researchers::
	lockall
	faceplayer
	call JT_CeladonVisibility
	goto_if_set FLAG_TEMP_1C, JT_Release
	goto_if_set FLAG_JT02_SEEN, JT02_DuoOffer
	msgbox JT02_Text_Survey
	msgbox JT02_Text_Cage
	msgbox JT02_Text_Booth
	msgbox JT02_Text_Question, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, JT02_Decline
	@ Both actors must remain for the independent optional duo offer.
	setvar VAR_0x8004, 20
	callnative Special_CharacterStoryTrioReveal, requests_effects=1
	msgbox JT02_Text_Reveal
	goto JT02_Depart
JT02_Decline::
	msgbox JT02_Text_Decline
JT02_Depart::
	@ Comedy completion is independent of accepting or winning the challenge.
	setflag FLAG_JT02_SEEN
	closemessage
JT02_DuoOffer::
	@ Asset integration must restore both genuine forms on repeat/map return.
	setvar VAR_0x8004, 20
	callnative Special_CharacterStoryTrioReveal, requests_effects=1
	msgbox JT02_Text_DuoChallenge, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, JT02_DuoDecline
	@ The native two-trainer macro skips the ordinary double-party preflight.
	special HasEnoughMonsForDoubleBattle
	goto_if_ne VAR_RESULT, PLAYER_HAS_TWO_USABLE_MONS, JT02_DuoTooFew
	@ Preserve any NPC escort instead of silently entering native partner mode.
	checkfollowernpc
	goto_if_eq VAR_RESULT, TRUE, JT02_DuoEscort
	msgbox JT02_Text_DuoJessieIntro
	msgbox JT02_Text_DuoJamesIntro
	closemessage
	trainerbattle_two_trainers TRAINER_STORY_JESSIE, JT02_Text_DuoJessieDefeat, TRAINER_STORY_JAMES, JT02_Text_DuoJamesDefeat
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_ne VAR_RESULT, B_OUTCOME_WON, JT02_DuoNoVictory
	checktrainerflag TRAINER_STORY_JESSIE
	goto_if FALSE, JT02_DuoNoVictory
	checktrainerflag TRAINER_STORY_JAMES
	goto_if FALSE, JT02_DuoNoVictory
	msgbox JT02_Text_DuoWon
	closemessage
	fadescreen FADE_TO_BLACK
	removeobject 20
	removeobject 21
	removeobject 22
	setflag FLAG_TEMP_1C
	fadescreen FADE_FROM_BLACK
	releaseall
	end
JT02_DuoDecline::
	msgbox JT02_Text_DuoLater
	releaseall
	end
JT02_DuoTooFew::
	msgbox JT02_Text_DuoNeedTwo
	releaseall
	end
JT02_DuoEscort::
	msgbox JT02_Text_DuoFinishEscort
	releaseall
	end
JT02_DuoNoVictory::
	@ Ordinary loss/forfeit already takes the native whiteout path, without
	@ setting these bits. Defensively reject any unexpected returned outcome.
	cleartrainerflag TRAINER_STORY_JESSIE
	cleartrainerflag TRAINER_STORY_JAMES
	msgbox JT02_Text_DuoRetry
	releaseall
	end
JT03_Disguises::
	lockall
	faceplayer
	call JT_GoldenrodVisibility
	goto_if_set FLAG_TEMP_1C, JT_Release
	msgbox JT03_Text_Jessie
	msgbox JT03_Text_James
	goto_if_set FLAG_JT01_SEEN, JT03_Known
	goto_if_set FLAG_JT02_SEEN, JT03_Known
	msgbox JT03_Text_NewAudience
	goto JT03_Reveal
JT03_Known::
	msgbox JT03_Text_Known
JT03_Reveal::
	setvar VAR_0x8004, 41
	callnative Special_CharacterStoryTrioReveal, requests_effects=1
	delay 90
	setflag FLAG_JT03_SEEN
	closemessage
	fadescreen FADE_TO_BLACK
	removeobject 41
	removeobject 42
	removeobject 43
	setflag FLAG_TEMP_1C
	fadescreen FADE_FROM_BLACK
	releaseall
	end
JT02_Text_DuoChallenge::
	.string "JESSIE: Face us together?$"
JT02_Text_DuoLater::
	.string "JAMES: We'll be here!$"
JT02_Text_DuoNeedTwo::
	.string "Bring two healthy POKéMON.$"
JT02_Text_DuoFinishEscort::
	.string "Finish helping your companion first.$"
JT02_Text_DuoJessieIntro::
	.string "JESSIE: Prepare for trouble!$"
JT02_Text_DuoJamesIntro::
	.string "JAMES: And make it double!$"
JT02_Text_DuoJessieDefeat::
	.string "JESSIE: Our comeback...!$"
JT02_Text_DuoJamesDefeat::
	.string "JAMES: We kept the balloon!$"
JT02_Text_DuoWon::
	.string "MEOWTH: We still have bus fare!$"
JT02_Text_DuoRetry::
	.string "JAMES: Another time!$"
JT02_Text_Survey::
	.string "JAMES: We're conducting a\ncompletely official POKéMON survey.$"
JT02_Text_Cage::
	.string "JESSIE: Question one: would your\nPOKéMON like to stand in this\lconvenient cage?$"
JT02_Text_Booth::
	.string "MEOWTH: You were supposed to\nsay observation booth!$"
JT02_Text_Question::
	.string "Ask who sent them?\nNO: Decline the survey.$"
JT02_Text_Reveal::
	.string "JESSIE: This survey is closed!$"
JT02_Text_Decline::
	.string "JESSIE: Then this survey is closed!$"
JT03_Text_Jessie::
	.string "JESSIE: New region. New disguises.\nNew reputation.$"
JT03_Text_James::
	.string "JAMES: Same unpaid balloon bill.$"
JT03_Text_Known::
	.string "MEOWTH: And the same kid!$"
JT03_Text_NewAudience::
	.string "MEOWTH: And an audience!$"
JT01_Text_Jessie::
	.string "JESSIE: One rare POKéMON, and\nheadquarters will finally\lremember our names.$"
JT01_Text_OffscreenJames::
	.string "JAMES calls from inside the tunnel.$"
JT01_Text_James::
	.string "JAMES: They remember mine.\nI signed for the net.$"
JT01_Text_Net::
	.string "The net is tangled around MEOWTH!$"
JT01_Text_Meowth::
	.string "MEOWTH: Then help me\nout of it!$"
JT04_Text_Rescued::
	.string "A freed SEEL lingers by the passage.$"
JT04_Text_OffscreenJames::
	.string "JAMES calls from the passage.$"
JT04_Text_James::
	.string "JAMES: They had a whole room\nof frightened POKéMON.\pI couldn't leave the cages shut.$"
JT04_Text_Jessie::
	.string "JESSIE: We were inspecting\ncompany property.$"
JT04_Text_Meowth::
	.string "MEOWTH: Sure.\nWith all the doors open.$"
#endif
