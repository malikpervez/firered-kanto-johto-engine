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
	@ applymovement2 leaves the companion PIKACHU out (applymovement would put it back in its BALL): the trio's next
	@ lines are about it walking beside the player.
	applymovement2 15, JT_Movement_TangledMeowth
	waitmovement 0
	msgbox JT01_Text_Meowth
	@ T6: they notice the companion PIKACHU (always behind the player); nobody tries to take it.
	msgbox JT01_Text_JessiePikachu
	msgbox JT01_Text_JamesPikachu
	msgbox JT01_Text_MeowthPikachu
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
	call_if_set JOHTO_FLAG_JT05_SEEN, JT04_JamesGoldenrod
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
JT04_JamesGoldenrod::
	msgbox JT04_Text_JamesGoldenrod
	return
@ JT05: during the takeover (Goldenrod state 6-9) ROCKET has hired the trio to guard its warehouse under GOLDENROD.
@ Talk to any of them; no battle, they leave in a fade. The two caged POKeMON beside the crates (FLAG_TEMP_1D) stay
@ until the tower is freed; talked to, each only cries. Sets JOHTO_FLAG_JT05_SEEN, which JT04 reads.
JT05_Visibility::
	setflag FLAG_TEMP_1C
	setflag FLAG_TEMP_1D
	callnative Special_CharacterStoryAdopt, requests_effects=1
	goto_if_eq VAR_RESULT, FALSE, JT_Return
	goto_if_lt JOHTO_VAR_GOLDENROD_CITY_STATE, 6, JT_Return
	goto_if_ge JOHTO_VAR_GOLDENROD_CITY_STATE, 10, JT_Return
	clearflag FLAG_TEMP_1D
	goto_if_set JOHTO_FLAG_JT05_SEEN, JT_Return
	clearflag FLAG_TEMP_1C
	return
JT05_GuardDuty::
	lockall
	faceplayer
	call JT05_Visibility
	goto_if_set FLAG_TEMP_1C, JT_Release
	goto_if_set FLAG_JT01_SEEN, JT05_Known
	goto_if_set FLAG_JT02_SEEN, JT05_Known
	goto_if_set FLAG_JT03_SEEN, JT05_Known
	msgbox JT05_Text_JessieHold
	goto JT05_Duty
JT05_Known::
	msgbox JT05_Text_JessieAgain
JT05_Duty::
	msgbox JT05_Text_James
	msgbox JT05_Text_Meowth
	playmoncry SPECIES_SENTRET, CRY_MODE_WEAK
	waitmoncry
	msgbox JT05_Text_Whimper
	applymovement LOCALID_GOLDENROD_STORAGE_JAMES, Common_Movement_FaceUp
	waitmovement 0
	msgbox JT05_Text_JamesBerries
	msgbox JT05_Text_Jessie
	msgbox JT05_Text_MeowthComing
	setflag JOHTO_FLAG_JT05_SEEN
	closemessage
	fadescreen FADE_TO_BLACK
	removeobject LOCALID_GOLDENROD_STORAGE_JESSIE
	removeobject LOCALID_GOLDENROD_STORAGE_JAMES
	removeobject LOCALID_GOLDENROD_STORAGE_MEOWTH
	setflag FLAG_TEMP_1C
	fadescreen FADE_FROM_BLACK
	releaseall
	end
JT05_CagedMarill::
	lock
	playmoncry SPECIES_MARILL, CRY_MODE_WEAK
	waitmoncry
	release
	end
JT05_CagedSentret::
	lock
	playmoncry SPECIES_SENTRET, CRY_MODE_WEAK
	waitmoncry
	release
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
	msgbox JT03_Text_StillHiring
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
	.string "MEOWTH: And the same kid! With the\n"
	.string "same smug PIKACHU!$"
JT03_Text_NewAudience::
	.string "MEOWTH: And an audience! With a\n"
	.string "PIKACHU, no less!$"
JT03_Text_StillHiring::
	.string "JESSIE: Somebody in JOHTO is still\n"
	.string "hiring ROCKETS. We'll be the best\l"
	.string "they've got!$"
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
JT01_Text_JessiePikachu::
	.string "JESSIE: …Wait. That PIKACHU walks\n"
	.string "beside the kid, without a BALL.$"
JT01_Text_JamesPikachu::
	.string "JAMES: A PIKACHU like that?\n"
	.string "Headquarters would remember US!$"
JT01_Text_MeowthPikachu::
	.string "MEOWTH: Headquarters can't even\n"
	.string "remember ME, and I can TALK!$"
JT04_Text_Rescued::
	.string "A freed SEEL lingers by the passage.$"
JT04_Text_OffscreenJames::
	.string "JAMES calls from the passage.$"
JT04_Text_James::
	.string "JAMES: They had a whole room\nof frightened POKéMON.\pI couldn't leave the cages shut.$"
JT04_Text_JamesGoldenrod::
	.string "JAMES: In GOLDENROD, I only fed\n"
	.string "them. This time I opened the doors.$"
JT04_Text_Jessie::
	.string "JESSIE: ARCHER quit. ARIANA was still\n"
	.string "hiring. We were only inspecting\l"
	.string "company property.$"
JT04_Text_Meowth::
	.string "MEOWTH: Sure.\nWith all the doors open.$"
JT05_Text_JessieAgain::
	.string "JESSIE: You again! This is a\n"
	.string "restricted storage area.\p"
	.string "We're on guard duty. Real\n"
	.string "uniforms, real pay.$"
JT05_Text_JessieHold::
	.string "JESSIE: Hold it! This is a\n"
	.string "restricted storage area.\p"
	.string "We're on guard duty. Real\n"
	.string "uniforms, real pay.$"
JT05_Text_James::
	.string "JAMES: ARCHER says the boss will be\n"
	.string "home as soon as he hears the\l"
	.string "broadcast.$"
JT05_Text_Meowth::
	.string "MEOWTH: And then the boss sees who\n"
	.string "stood watch. That's the plan.$"
JT05_Text_Whimper::
	.string "A POKéMON in one of the cages\n"
	.string "whimpers. JAMES looks over.$"
JT05_Text_JamesBerries::
	.string "JAMES: …They said not to feed these\n"
	.string "until after the broadcast.\p"
	.string "It's only a few BERRIES. Nobody\n"
	.string "needs to write that down.$"
JT05_Text_Jessie::
	.string "JESSIE: James! Not in front of\n"
	.string "the kid!$"
JT05_Text_MeowthComing::
	.string "MEOWTH: Shh! Somebody's coming!$"
