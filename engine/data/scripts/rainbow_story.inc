RB_Return::
	return
RB_Release::
	release
	end
RB_Repeat::
	msgbox RB_Text_Repeat
	release
	end
RB_AsyncWait::
	waitstate
	return
RB_Text_Repeat::
	.string "There is room for more than one\nanswer. Travel safely.$"
RB_MewGlimpse::
	goto_if_set JOHTO_FLAG_CAUGHT_MEW, RB_Return
	goto_if_set JOHTO_FLAG_DEFEATED_MEW, RB_Return
	setvar VAR_0x8004, 0
	special Special_RainbowMewGlimpse
	call_if_eq VAR_RESULT, 1, RB_AsyncWait
	return
RB_MewtwoReveal::
	setvar VAR_0x8004, 1
	special Special_RainbowMewGlimpse
	call_if_eq VAR_RESULT, 1, RB_AsyncWait
	return
RB_Flyby::
	special Special_RainbowHoOhFlyby
	call_if_eq VAR_RESULT, 1, RB_AsyncWait
	return
RB_Route1Transition::
	setvar VAR_TEMP_E, 0
	setflag FLAG_TEMP_1E
	special Special_RainbowStoryAdopt
	goto_if_eq VAR_RESULT, FALSE, RB_Return
	call_if_set FLAG_RB_FRESH_COHORT, RB_TryOpening
	call_if_set FLAG_RB_LETTER_READ, RB_TryEpilogue
	return
RB_TryOpening::
	goto_if_set FLAG_RB_OPENING_SEEN, RB_Return
	goto_if_lt VAR_MAP_SCENE_PALLET_TOWN_PROFESSOR_OAKS_LAB, 4, RB_Return
	goto_if_set FLAG_SYS_POKEDEX_GET, RB_Return
	setvar VAR_TEMP_E, 1
	clearflag FLAG_TEMP_1E
	return
RB_TryEpilogue::
	goto_if_set FLAG_RB_EPILOGUE_SEEN, RB_Return
	clearflag FLAG_TEMP_1E
	return
RB_OpeningPidgey::
	lock
	faceplayer
	goto_if_set FLAG_RB_LETTER_READ, RB_PidgeyEpilogue
	msgbox RB_Text_Pidgey
	release
	end
RB_Route1Frame::
	lockall
	setvar VAR_TEMP_E, 0
	call RB_OpeningShelter
	closemessage
	delay 240
	call RB_Flyby
	goto_if_ne VAR_RESULT, TRUE, RB_OpeningRetry
	delay 420
	msgbox RB_Text_StillWind
	applymovement 9, RB_Movement_Pidgey
	waitmovement 0
	setflag FLAG_RB_OPENING_SEEN
	setflag FLAG_TEMP_1E
	removeobject 9
	releaseall
	end
RB_OpeningRetry::
	releaseall
	end
RB_OpeningShelter::
	goto_if_unset FLAG_ST01_GIVEN, RB_OpeningShelterOrdinary
	checkspecies SPECIES_PIKACHU
	goto_if_eq VAR_RESULT, FALSE, RB_OpeningShelterOrdinary
	showmonpic SPECIES_PIKACHU, 9, 1
	msgbox RB_Text_PikachuShelter
	hidemonpic
	return
RB_OpeningShelterOrdinary::
	msgbox RB_Text_Shelter
	return
RB_Movement_Pidgey::
	jump_in_place_up
	jump_in_place_left
	step_end
RB_Text_Shelter::
	.string "A PIDGEY struggles in the gusts.\pYou shelter it beside the path.\nIts trembling slowly eases.$"
RB_Text_PikachuShelter::
	.string "A PIDGEY struggles in the gusts.\pPIKACHU presses close, helping\nyou shelter it beside the path.\pIts trembling slowly eases.$"
RB_Text_StillWind::
	.string "For a moment, even the wind\nwas still.$"
RB_Text_Pidgey::
	.string "The PIDGEY watches the sky.$"
RB_PidgeyEpilogue::
	goto_if_set FLAG_RB_EPILOGUE_SEEN, RB_Repeat
	msgbox RB_Text_Epilogue
	setflag FLAG_RB_EPILOGUE_SEEN
	release
	end
RB_Text_Epilogue::
	.string "A PIDGEY shelters a younger bird\nbeneath its wing.\pBeyond the trees, the western\nmountains are clear.$"
RB_OakStory::
	special Special_RainbowStoryAdopt
	goto_if_eq VAR_RESULT, FALSE, RB_Return
	goto_if_unset FLAG_SYS_POKEDEX_GET, RB_Return
	goto_if_eq VAR_MAP_SCENE_PALLET_TOWN_PROFESSOR_OAKS_LAB, 8, RB_Return
	goto_if_set JOHTO_FLAG_SYS_GAME_CLEAR, RB_OakLetter
	goto_if_set FLAG_SYS_GAME_CLEAR, RB_OakReferral
	call_if_set FLAG_RB_OPENING_SEEN, RB_OakBird
	return
RB_OakBird::
	msgbox RB_Text_OakBird
	return
RB_OakReferral::
	goto_if_unset FLAG_RB_OPENING_SEEN, RB_OakNoMemory
	msgbox RB_Text_OakWest
	return
RB_OakNoMemory::
	msgbox RB_Text_OakResearch
	return
RB_OakLetter::
	goto_if_unset FLAG_RB_WELCOME_SEEN, RB_Return
	goto_if_set FLAG_RB_LETTER_READ, RB_Return
	msgbox RB_Text_Letter
	setflag FLAG_RB_LETTER_READ
	return
RB_Text_OakBird::
	.string "OAK: Feathers like a rainbow?\nI cannot identify it from words.\pI will write down your sighting.\nKeep looking up, {PLAYER}!$"
RB_Text_OakWest::
	.string "OAK: That bird flew west. ELM\nmay help you understand why.\pYour LEAGUE victory has opened\na new road for both of you.$"
RB_Text_OakResearch::
	.string "OAK: JOHTO has its own stories.\nELM values careful observation.$"
RB_Text_Letter::
	.string "OAK: A letter from NAO!\pThe bells rang. Nothing was\nasked of the sky.\pThere was room for an answer.\nThank you for listening.\pOAK: Both regions are proud\nof you, {PLAYER}.$"
RB_PewterVisibility::
	@ One active NAO location, derived from native campaign progress.
	setflag FLAG_TEMP_1E
	special Special_RainbowStoryAdopt
	goto_if_eq VAR_RESULT, FALSE, RB_Return
goto_if_unset FLAG_SYS_POKEDEX_GET, RB_Return
	goto_if_set FLAG_SYS_GAME_CLEAR, RB_Return
	goto_if_set FLAG_HIDE_CELADON_ROCKETS, RB_Return
	goto_if_set FLAG_GOT_POKE_FLUTE, RB_Return
clearflag FLAG_TEMP_1E
	return
RB_NaoPewter::
	lock
	faceplayer
	special Special_RainbowStoryAdopt
	goto_if_eq VAR_RESULT, FALSE, RB_Release
call_if_unset FLAG_RB_NAO_INTRODUCED, RB_NaoIntro
	msgbox RB_Text_NaoQuestion, MSGBOX_YESNO
	call_if_eq VAR_RESULT, YES, RB_NaoBird
	call_if_eq VAR_RESULT, NO, RB_NaoHome
release
	end
RB_NaoIntro::
	goto_if_unset FLAG_RB_OPENING_SEEN, RB_NaoIntroNoMemory
	msgbox RB_Text_NaoSighting
RB_NaoIntroNoMemory::
	msgbox RB_Text_NaoIntro
	setflag FLAG_RB_NAO_INTRODUCED
	return
RB_NaoBird::
	msgbox RB_Text_NaoBird
	return
RB_NaoHome::
	msgbox RB_Text_NaoHome
	return
RB_Text_NaoSighting::
	.string "NAO: Gold wings? A long tail?\nAnd it was flying west?\pI crossed half of KANTO asking\nabout a bird like that!$"
RB_Text_NaoIntro::
	.string "NAO: I keep bells in ECRUTEAK.\nThis is Grandpa's practice bell.\pHear the crack? I collect sounds\nand stories from every town.$"
RB_Text_NaoQuestion::
	.string "NAO: Ask about the bird?\nOr shall I tell you of my home?$"
RB_Text_NaoBird::
	.string "NAO: It might be HO-OH.\nA possibility, not proof!\pPeople keep its bells even when\nthere is no sign it will return.$"
RB_Text_NaoHome::
	.string "NAO: ECRUTEAK has two towers.\nOne burned long ago.\pI want to know what we are\nwaiting for in the other.$"
RB_FujiVisibility::
	@ One active NAO location, derived from native campaign progress.
	setflag FLAG_TEMP_1E
	special Special_RainbowStoryAdopt
	goto_if_eq VAR_RESULT, FALSE, RB_Return
goto_if_unset FLAG_RESCUED_MR_FUJI, RB_Return
	goto_if_set FLAG_SYS_GAME_CLEAR, RB_Return
	goto_if_set FLAG_RB_FUJI_SCENE_SEEN, RB_Return
goto_if_unset FLAG_GOT_POKE_FLUTE, RB_Return
clearflag FLAG_TEMP_1E
	return
RB_NaoFuji::
	lock
	faceplayer
	special Special_RainbowStoryAdopt
	goto_if_eq VAR_RESULT, FALSE, RB_Release
goto_if_set FLAG_RB_FUJI_SCENE_SEEN, RB_Repeat
call_if_unset FLAG_RB_NAO_INTRODUCED, RB_NaoIntro
	msgbox RB_Text_Fuji
setflag FLAG_RB_FUJI_SCENE_SEEN
release
	end
RB_Text_Fuji::
	.string "NAO: If HO-OH restores lives,\nwhy must anyone lose anything?\pFUJI: I do not know why some\nstories are given miracles.\pThese POKéMON needed a home\nthis morning. And tomorrow, too.\pNAO: I came to ask of a legend.\nYou gave me useful work instead.$"
RB_CeladonNaoVisibility::
	@ One active NAO location, derived from native campaign progress.
	setflag FLAG_TEMP_1E
	special Special_RainbowStoryAdopt
	goto_if_eq VAR_RESULT, FALSE, RB_Return
goto_if_unset FLAG_HIDE_CELADON_ROCKETS, RB_Return
	goto_if_set FLAG_SYS_GAME_CLEAR, RB_Return
	goto_if_unset FLAG_GOT_POKE_FLUTE, RB_ShowCeladonNao
	goto_if_unset FLAG_RB_FUJI_SCENE_SEEN, RB_Return
RB_ShowCeladonNao::
clearflag FLAG_TEMP_1E
	return
RB_NaoCeladon::
	lock
	faceplayer
	special Special_RainbowStoryAdopt
	goto_if_eq VAR_RESULT, FALSE, RB_Release
goto_if_set FLAG_RB_NOTEBOOK_SCENE_SEEN, RB_Repeat
call_if_unset FLAG_RB_NAO_INTRODUCED, RB_NaoIntro
	msgbox RB_Text_Notebook
setflag FLAG_RB_NOTEBOOK_SCENE_SEEN
release
	end
RB_Text_Notebook::
	.string "NAO: A collector bought my bell\nnotes. He worked for ROCKET!\pI recovered my notebook after\nyou cleared their hideout.\pThese are my notes. That is not\nmy handwriting. Microphones...\pI wrote, Wait quietly and see\nwhat comes. They crossed out wait.$"
RB_SilphEquipment::
	msgbox RB_Text_Equipment
	return
RB_Text_Equipment::
	.string "SCIENTIST: ROCKET ordered devices\nto reproduce unusual calls.\pA sound can attract a POKéMON.\nIt cannot earn its trust.$"
RB_ElmBird::
	goto_if_unset FLAG_RB_OPENING_SEEN, RB_Return
	msgbox RB_Text_ElmBird
	return
RB_Text_ElmBird::
	.string "ELM: OAK mentioned your sighting.\nObservation begins with caring\lfor what is right in front of us.$"
RB_EcruteakVisibility::
	setflag FLAG_TEMP_1E
	special Special_RainbowStoryAdopt
	goto_if_eq VAR_RESULT, FALSE, RB_Return
goto_if_unset JOHTO_FLAG_RELEASED_BEASTS, RB_Return
	goto_if_ge JOHTO_VAR_GOLDENROD_CITY_STATE, 10, RB_ShowEcruteak
	goto_if_unset FLAG_RB_ECRUTEAK_TRUTH_SEEN, RB_ShowEcruteak
	goto_if_set JOHTO_FLAG_AMPHAROS_HEALED, RB_Return
RB_ShowEcruteak::
clearflag FLAG_TEMP_1E
	return
RB_NaoEcruteak::
	lock
	faceplayer
	special Special_RainbowStoryAdopt
	goto_if_eq VAR_RESULT, FALSE, RB_Release
call_if_unset FLAG_RB_NAO_INTRODUCED, RB_NaoJohtoIntro
	goto_if_unset FLAG_RB_ECRUTEAK_TRUTH_SEEN, RB_TruthFirst
	goto_if_lt JOHTO_VAR_GOLDENROD_CITY_STATE, 10, RB_NaoWaiting
	goto_if_unset FLAG_RB_RECORDING_STOPPED, RB_RecordingFirst
	goto_if_set FLAG_RB_WELCOME_SEEN, RB_NaoWelcomeRepeat
	msgbox RB_Text_Ready, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, RB_Release
	call RB_Welcome
release
	end
RB_NaoJohtoIntro::
	msgbox RB_Text_JohtoIntro
	setflag FLAG_RB_NAO_INTRODUCED
	return
RB_Text_JohtoIntro::
	.string "NAO: I keep bells here. I have\nbeen collecting KANTOs stories.$"
RB_TruthFirst::
	call RB_EcruteakTruth
	release
	end
RB_RecordingFirst::
	call RB_Recording
	release
	end
RB_EcruteakTruth::
	msgbox RB_Text_Truth
	setflag FLAG_RB_ECRUTEAK_TRUTH_SEEN
	return
RB_Recording::
	msgbox RB_Text_Recording, MSGBOX_YESNO
	call_if_eq VAR_RESULT, YES, RB_Disconnect
	call_if_eq VAR_RESULT, NO, RB_DirectorDisconnect
	setflag FLAG_RB_RECORDING_STOPPED
	return
RB_Disconnect::
	msgbox RB_Text_Disconnect
	return
RB_DirectorDisconnect::
	msgbox RB_Text_DirectorDisconnect
	return
RB_NaoWaiting::
	msgbox RB_Text_Waiting
	release
	end
RB_NaoWelcomeRepeat::
	msgbox RB_Text_WelcomeRepeat
	release
	end
RB_Welcome::
	msgbox RB_Text_Welcome
	closemessage
	goto_if_set JOHTO_FLAG_CAUGHT_HO_OH, RB_WelcomeRainbow
	goto_if_set JOHTO_FLAG_DEFEATED_HO_OH, RB_WelcomeRainbow
	goto_if_eq JOHTO_VAR_COMPLETED_HO_OH, 1, RB_WelcomeDefer
	goto_if_eq JOHTO_VAR_COMPLETED_HO_OH, 2, RB_WelcomeDefer
	goto_if_eq JOHTO_VAR_LUGIA_OR_HOOH, 1, RB_WelcomeFly
	goto_if_eq JOHTO_VAR_COMPLETED_HO_OH, 3, RB_WelcomeRainbow
RB_WelcomeFly::
	call RB_Flyby
	goto_if_ne VAR_RESULT, TRUE, RB_WelcomeDefer
	msgbox RB_Text_WelcomeSky
	setflag FLAG_RB_WELCOME_SEEN
	return
RB_WelcomeRainbow::
	setvar VAR_0x8004, 2
	special Special_RainbowMewGlimpse
	call_if_eq VAR_RESULT, 1, RB_AsyncWait
	goto_if_ne VAR_RESULT, TRUE, RB_WelcomeDefer
	msgbox RB_Text_WelcomeRainbow
	setflag FLAG_RB_WELCOME_SEEN
	return
RB_WelcomeDefer::
	msgbox RB_Text_WelcomeDefer
	return
RB_Text_Truth::
	.string "NAO: The fire took three lives.\nThe legend says HO-OH gave them\la second chance, then flew away.\pI wanted bells that could bring\nanything back. That was unfair\lto what is still here.$"
RB_Text_Recording::
	.string "NAO: The RADIO director recovered\nROCKET's copy of my recordings.\pThey thought the right call\ncould command a return.\pWill you disconnect the player?\nOr leave it to the director?$"
RB_Text_Disconnect::
	.string "The copied bell falls silent.\nNAO keeps her cracked bell.$"
RB_Text_DirectorDisconnect::
	.string "NAO: The director will stop it.\nNo sound should be a leash.$"
RB_Text_Waiting::
	.string "NAO: A bell can be an invitation.\nI am still learning to listen.$"
RB_Text_Ready::
	.string "NAO: We can welcome the sky\nwithout demanding an answer.\pShall we ring the bells now?\nWe can wait until you are ready.$"
RB_Text_Welcome::
	.string "Neighbors gather on the tower\ngrounds. NAO's small bell rings\lwith its familiar, uneven note.\pNobody calls for a POKéMON\nto obey. They simply listen.$"
RB_Text_WelcomeSky::
	.string "A golden shape crosses the sky.\nThen there is only open air.\pNAO: It came because it could.\nAnd it may leave.$"
RB_Text_WelcomeRainbow::
	.string "A rainbow rests above the roofs.\nThe bells need no reply.\pNAO: A welcome leaves room\nfor an answer.$"
RB_Text_WelcomeDefer::
	.string "NAO: The tower ritual is still\nin progress. Let us wait until\lthe grounds are quiet again.$"
RB_Text_WelcomeRepeat::
	.string "NAO: Grandpa heard the crack\nin my bell. He kept it anyway.\pI think I understand that now.$"
RB_OlivineVisibility::
	setflag FLAG_TEMP_1E
	special Special_RainbowStoryAdopt
	goto_if_eq VAR_RESULT, FALSE, RB_Return
goto_if_unset JOHTO_FLAG_AMPHAROS_HEALED, RB_Return
	goto_if_unset FLAG_RB_ECRUTEAK_TRUTH_SEEN, RB_Return
	goto_if_ge JOHTO_VAR_GOLDENROD_CITY_STATE, 10, RB_Return
clearflag FLAG_TEMP_1E
	return
RB_NaoOlivine::
	lock
	faceplayer
	special Special_RainbowStoryAdopt
	goto_if_eq VAR_RESULT, FALSE, RB_Release
msgbox RB_Text_Amphy, MSGBOX_YESNO
	call_if_eq VAR_RESULT, YES, RB_AmphyYes
	call_if_eq VAR_RESULT, NO, RB_AmphyNo
release
	end
RB_AmphyYes::
	msgbox RB_Text_AmphyYes
	return
RB_AmphyNo::
	msgbox RB_Text_AmphyNo
	return
RB_Text_Amphy::
	.string "NAO: AMPHY shines again because\nsomebody brought medicine.\pDo you think the bells will\nbring HO-OH home?$"
RB_Text_AmphyYes::
	.string "NAO: Perhaps. But I should make\na home worth returning to first.$"
RB_Text_AmphyNo::
	.string "NAO: Then we can still care\nfor the POKéMON already here.$"
MW01_Visibility::
	setflag FLAG_TEMP_1E
	goto_if_set FLAG_FOUGHT_MEWTWO, RB_Return
	goto_if_set FLAG_MW06_SEEN, RB_Return
	special Special_RainbowStoryAdopt
	goto_if_eq VAR_RESULT, FALSE, RB_Return
goto_if_set FLAG_MW01_SEEN, RB_Return
goto_if_unset FLAG_SYS_POKEDEX_GET, RB_Return
clearflag FLAG_TEMP_1E
	return
MW01_Talk::
	lock
	faceplayer
	special Special_RainbowStoryAdopt
	goto_if_eq VAR_RESULT, FALSE, RB_Release
goto_if_set FLAG_MW01_SEEN, RB_Repeat
goto_if_unset FLAG_RB_OPENING_SEEN, MW01_NoMemory
	msgbox MW01_Text_Bird
	goto MW01_Answer
MW01_NoMemory::
	msgbox MW01_Text_Generic
MW01_Answer::
	msgbox MW01_Text_Question, MSGBOX_YESNO
	msgbox MW01_Text_Answer
	call RB_MewGlimpse
	setflag FLAG_TEMP_1E
	removeobject LOCALID_VIRIDIAN_STRANGER
setflag FLAG_MW01_SEEN
release
	end
MW02_Visibility::
	setflag FLAG_TEMP_1E
	goto_if_set FLAG_FOUGHT_MEWTWO, RB_Return
	goto_if_set FLAG_MW06_SEEN, RB_Return
	special Special_RainbowStoryAdopt
	goto_if_eq VAR_RESULT, FALSE, RB_Return
goto_if_set FLAG_MW02_SEEN, RB_Return
goto_if_unset FLAG_GOT_FOSSIL_FROM_MT_MOON, RB_Return
clearflag FLAG_TEMP_1E
	return
MW02_Talk::
	lock
	faceplayer
	special Special_RainbowStoryAdopt
	goto_if_eq VAR_RESULT, FALSE, RB_Release
goto_if_set FLAG_MW02_SEEN, RB_Repeat
msgbox MW02_Text_Question, MSGBOX_YESNO
	msgbox MW02_Text_Answer
	applymovement 13, RB_Movement_Psychic
	waitmovement 0
	setflag FLAG_TEMP_1E
	removeobject 12
	removeobject 13
setflag FLAG_MW02_SEEN
release
	end
MW03_Visibility::
	setflag FLAG_TEMP_1E
	goto_if_set FLAG_FOUGHT_MEWTWO, RB_Return
	goto_if_set FLAG_MW06_SEEN, RB_Return
	special Special_RainbowStoryAdopt
	goto_if_eq VAR_RESULT, FALSE, RB_Return
goto_if_set FLAG_MW03_SEEN, RB_Return
goto_if_unset FLAG_GOT_POKE_FLUTE, RB_Return
clearflag FLAG_TEMP_1E
	return
MW03_Talk::
	lock
	faceplayer
	special Special_RainbowStoryAdopt
	goto_if_eq VAR_RESULT, FALSE, RB_Release
goto_if_set FLAG_MW03_SEEN, RB_Repeat
msgbox MW03_Text
	call RB_MewGlimpse
	setflag FLAG_TEMP_1E
	removeobject 13
setflag FLAG_MW03_SEEN
release
	end
MW04_Visibility::
	setflag FLAG_TEMP_1D
	goto_if_set FLAG_FOUGHT_MEWTWO, RB_Return
	goto_if_set FLAG_MW06_SEEN, RB_Return
	special Special_RainbowStoryAdopt
	goto_if_eq VAR_RESULT, FALSE, RB_Return
goto_if_set FLAG_MW04_SEEN, RB_Return
goto_if_unset FLAG_HIDE_CELADON_ROCKETS, RB_Return
clearflag FLAG_TEMP_1D
	return
MW04_Talk::
	lock
	faceplayer
	special Special_RainbowStoryAdopt
	goto_if_eq VAR_RESULT, FALSE, RB_Release
goto_if_set FLAG_MW04_SEEN, RB_Repeat
msgbox MW04_Text_Question, MSGBOX_YESNO
	msgbox MW04_Text_Answer
	setflag FLAG_TEMP_1D
	removeobject 19
setflag FLAG_MW04_SEEN
release
	end
MW05_Visibility::
	setflag FLAG_TEMP_1E
	goto_if_set FLAG_FOUGHT_MEWTWO, RB_Return
	goto_if_set FLAG_MW06_SEEN, RB_Return
	special Special_RainbowStoryAdopt
	goto_if_eq VAR_RESULT, FALSE, RB_Return
goto_if_set FLAG_MW05_SEEN, RB_Return
goto_if_unset FLAG_GOT_MASTER_BALL_FROM_SILPH, RB_Return
clearflag FLAG_TEMP_1E
	return
MW05_Talk::
	lock
	faceplayer
	special Special_RainbowStoryAdopt
	goto_if_eq VAR_RESULT, FALSE, RB_Release
goto_if_set FLAG_MW05_SEEN, RB_Repeat
	hideobjectat 2, MAP_SILPH_CO_1F
call RB_MewtwoReveal
	showobjectat 2, MAP_SILPH_CO_1F
	msgbox MW05_Text
	call RB_MewGlimpse
	setflag FLAG_TEMP_1E
	removeobject 2
setflag FLAG_MW05_SEEN
release
	end
MW06_Visibility::
	setflag FLAG_TEMP_1E
	goto_if_set FLAG_FOUGHT_MEWTWO, RB_Return
	special Special_RainbowStoryAdopt
	goto_if_eq VAR_RESULT, FALSE, RB_Return
goto_if_set FLAG_MW06_SEEN, RB_Return
goto_if_unset FLAG_HIDE_POKEMON_MANSION_B1F_SECRET_KEY, RB_Return
clearflag FLAG_TEMP_1E
	return
MW06_Talk::
	lock
	faceplayer
	special Special_RainbowStoryAdopt
	goto_if_eq VAR_RESULT, FALSE, RB_Release
goto_if_set FLAG_MW06_SEEN, RB_Repeat
msgbox MW06_Text_Journals
	setflag FLAG_TEMP_1E
	removeobject 15
	call RB_MewtwoReveal
	msgbox MW06_Text_Question, MSGBOX_YESNO
	call_if_eq VAR_RESULT, YES, MW06_Invitation
	call_if_eq VAR_RESULT, NO, MW06_Choice
	msgbox MW06_Text_Answer
	call RB_MewGlimpse
setflag FLAG_MW06_SEEN
release
	end
MW07_Visibility::
	setflag FLAG_TEMP_1E
	goto_if_set FLAG_FOUGHT_MEWTWO, RB_Return
	special Special_RainbowStoryAdopt
	goto_if_eq VAR_RESULT, FALSE, RB_Return
goto_if_set FLAG_MW07_SEEN, RB_Return
goto_if_unset FLAG_MW06_SEEN, RB_Return
goto_if_set FLAG_FOUGHT_MEWTWO, RB_Return
clearflag FLAG_TEMP_1E
	return
MW07_Talk::
	lock
	faceplayer
	special Special_RainbowStoryAdopt
	goto_if_eq VAR_RESULT, FALSE, RB_Release
goto_if_set FLAG_MW07_SEEN, RB_Repeat
goto_if_set FLAG_SYS_GAME_CLEAR, MW07_AfterLeague
	msgbox MW07_Text_Before
	goto MW07_Finish
MW07_AfterLeague::
	msgbox MW07_Text_After
MW07_Finish::
	setflag FLAG_TEMP_1E
	removeobject 7
setflag FLAG_MW07_SEEN
release
	end
RB_Movement_Psychic::
	levitate
	delay_16
	stop_levitate
	step_end
MW01_Text_Bird::
	.string "STRANGER: You helped that bird.\nYou did not catch it.\pWhat did you gain?$"
MW01_Text_Generic::
	.string "STRANGER: Why do you want\nto travel with POKéMON?$"
MW01_Text_Question::
	.string "Was helping reason enough?\nOr had you not thought about it?$"
MW01_Text_Answer::
	.string "STRANGER: I see.$"
MW02_Text_Question::
	.string "STRANGER: A fossil restored by\nhuman hands... Who decides\lwhat that life becomes?\pThe POKéMON? Or must both\nlearn together?$"
MW02_Text_Answer::
	.string "STRANGER: Together. Humans\nuse that word often.\pA loose stone trembles, rises\nan inch, then settles.$"
MW03_Text::
	.string "STRANGER: Nothing keeps them here.\pFUJI: Some leave when ready.\pSTRANGER: And you allow that?\pFUJI: It is a home, not a cage.\pThe traveler has no reply.$"
MW04_Text_Question::
	.string "STRANGER: They called POKéMON\nproperty. You opposed them.\pYet you carry POKé BALLS.\nDo you try to earn their trust?$"
MW04_Text_Answer::
	.string "STRANGER: Then I will judge\nhow you use them.$"
MW05_Text::
	.string "The traveler's outline wavers:\na long tail, an unfamiliar head.\pSTRANGER: They offered power.\nYou kept stopping to help.\pA pink shape passes the window.\nSTRANGER: We are not alone.$"
MW06_Text_Journals::
	.string "STRANGER: Those pages tell you\nwhat they hoped to create.\pThey cannot tell you who\nI will become.\pThe veil falls. MEWTWO stands\nwhere the traveler stood.$"
MW06_Text_Question::
	.string "MEWTWO: I expected possession.\nAnother reason to command.\pYou made that answer difficult.\pWould you invite MEWTWO to come?\nOr leave it to choose its path?$"
MW06_Invitation::
	msgbox MW06_Text_Invitation
	return
MW06_Choice::
	msgbox MW06_Text_Choice
	return
MW06_Text_Invitation::
	.string "MEWTWO: An invitation.\nI am not ready to accept it.$"
MW06_Text_Choice::
	.string "MEWTWO: Yes. That is what\nI intend to do.$"
MW06_Text_Answer::
	.string "MEWTWO: You do not speak for\nevery human. I no longer believe\levery human speaks for you.\pMEWTWO leaves to find\nsomewhere quiet.$"
MW07_Text_Before::
	.string "STRANGER: A CHAMPION commands\ngreat power. I wonder what\lyou will ask of it.$"
MW07_Text_After::
	.string "STRANGER: You reached the summit.\nDid it change what you ask\lof those beside you?$"
MW08_Intro::
	goto_if_unset FLAG_MW06_SEEN, MW08_Unfamiliar
	msgbox MW08_Text_Familiar
	goto MW08_Ask
MW08_Unfamiliar::
	msgbox MW08_Text_Unfamiliar
MW08_Ask::
	msgbox MW08_Text_Ask, MSGBOX_YESNO
	return
MW08_Text_Familiar::
	.string "MEWTWO: You found the quiet\nplace I chose.\pIf we battle, let it be\na choice we both make.$"
MW08_Text_Unfamiliar::
	.string "A powerful presence watches you.\nIt waits rather than attacks.$"
MW08_Text_Ask::
	.string "Face MEWTWO now?\nYou may leave and return.$"
MW08_Text_Caught::
	.string "The silence feels different.\nAn invitation was answered.$"
MW08_Text_Defeated::
	.string "The pressure in the cave eases.\nA quiet choice remains its own.$"
MW09_Transition::
	setvar VAR_TEMP_E, 0
	special Special_RainbowStoryAdopt
	goto_if_eq VAR_RESULT, FALSE, RB_Return
	goto_if_unset FLAG_FOUGHT_MEWTWO, RB_Return
	goto_if_set FLAG_MW09_SEEN, RB_Return
	setvar VAR_TEMP_E, 1
	return
MW09_Scene::
	lockall
	goto_if_unset FLAG_FOUGHT_MEWTWO, MW09_Release
	goto_if_set FLAG_MW09_SEEN, MW09_Release
	setvar VAR_TEMP_E, 0
	msgbox MW09_Text
	closemessage
	call RB_MewGlimpse
	setflag FLAG_MW09_SEEN
MW09_Release::
	releaseall
	end
MW09_Text::
	.string "At the mouth of the cave,\nthe wind moves freely again.\pThere is room for more than\none path through the world.$"


RB_RadioAftermath::
	special Special_RainbowStoryAdopt
	goto_if_eq VAR_RESULT, FALSE, RB_Return
	goto_if_lt JOHTO_VAR_GOLDENROD_CITY_STATE, 10, RB_Return
	goto_if_lt JOHTO_VAR_MAHOGANY_TOWN_STATE, 17, RB_Return
	goto_if_set FLAG_RB_RECORDING_STOPPED, RB_Return
	msgbox RB_Text_RadioAftermath, MSGBOX_YESNO
	call_if_eq VAR_RESULT, YES, RB_Disconnect
	call_if_eq VAR_RESULT, NO, RB_DirectorDisconnect
	setflag FLAG_RB_RECORDING_STOPPED
	return
RB_Text_RadioAftermath::
	.string "The DIRECTOR recovered a copied\nbell recording. NAO sent word:\pAn invitation leaves a choice.\nROCKET forgot that.\pWill you disconnect the player?\nOr leave it to the director?$"

