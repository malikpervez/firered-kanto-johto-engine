@ Optional conversations. Native quests, services and battle receipts own progress.
CG_Return::
	return
CG_Release::
	release
	end
CG_Depart::
	closemessage
	fadescreen FADE_TO_BLACK
	removeobject VAR_LAST_TALKED
	fadescreen FADE_FROM_BLACK
	release
	end

@ The same added BLUE actor supplies BL01 and BL03. Native lab scenes win.
CG_BlueLabVisibility::
	setflag FLAG_TEMP_1D
	callnative Special_CharacterStoryAdopt, requests_effects=1
	goto_if_eq VAR_RESULT, FALSE, CG_Return
	goto_if_unset FLAG_SYS_GAME_CLEAR, CG_Return
	goto_if_eq VAR_MAP_SCENE_PALLET_TOWN_OAK, 2, CG_Return
	goto_if_eq VAR_MAP_SCENE_PALLET_TOWN_PROFESSOR_OAKS_LAB, 7, CG_Return
	goto_if_eq VAR_MAP_SCENE_PALLET_TOWN_PROFESSOR_OAKS_LAB, 8, CG_Return
	goto_if_unset FLAG_HIDE_RIVAL_IN_LAB, CG_Return
	goto_if_unset FLAG_BL01_SEEN, CG_ShowActor
	callnative Special_CharacterStoryElmProgress, requests_effects=1
	goto_if_eq VAR_RESULT, TRUE, CG_ShowActor
	goto_if_set FLAG_BL02_SEEN, CG_ShowActor
	return
CG_ShowActor::
	clearflag FLAG_TEMP_1D
	return

CG_BlueRoute1Visibility::
	setflag FLAG_TEMP_1D
	callnative Special_CharacterStoryAdopt, requests_effects=1
	goto_if_eq VAR_RESULT, FALSE, CG_Return
	goto_if_unset FLAG_SYS_GAME_CLEAR, CG_Return
	goto_if_unset FLAG_BL01_SEEN, CG_Return
	goto_if_set FLAG_BL02_SEEN, CG_Return
	callnative Special_CharacterStoryElmProgress, requests_effects=1
	goto_if_eq VAR_RESULT, TRUE, CG_Return
	clearflag FLAG_TEMP_1D
	return

CG_BlueLab::
	lock
	faceplayer
	call CG_BlueLabVisibility
	goto_if_set FLAG_TEMP_1D, CG_Release
	goto_if_set FLAG_BL01_SEEN, CG_BlueLabAfterIntro
	msgbox CG_Text_BL01
	setflag FLAG_BL01_SEEN
	callnative Special_CharacterStoryElmProgress, requests_effects=1
	goto_if_eq VAR_RESULT, TRUE, CG_Release
	goto CG_Depart
CG_BlueLabAfterIntro::
	callnative Special_CharacterStoryElmProgress, requests_effects=1
	goto_if_eq VAR_RESULT, FALSE, CG_BlueLabRepeat
	goto_if_set FLAG_BL03_SEEN, CG_BlueLabRepeat
	msgbox CG_Text_BL03
	call_if_set FLAG_ST01_GIVEN, CG_BlueUmbreonNote
	setflag FLAG_BL03_SEEN
	release
	end
CG_BlueUmbreonNote::
	goto_if_unset FLAG_ST01_NEW_COHORT, CG_Return
	msgbox CG_Text_BlueUmbreon
	return
CG_BlueLabRepeat::
	msgbox CG_Text_BlueRepeat
	release
	end

CG_BlueRoute1::
	lock
	faceplayer
	call CG_BlueRoute1Visibility
	goto_if_set FLAG_TEMP_1D, CG_Release
	msgbox CG_Text_BL02
	msgbox CG_Text_BL02_Question, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, CG_BlueRoute1Later
	msgbox CG_Text_BL02_Answer
	goto CG_BlueRoute1Finish
CG_BlueRoute1Later::
	msgbox CG_Text_BL02_Later
CG_BlueRoute1Finish::
	setflag FLAG_BL02_SEEN
	goto CG_Depart

@ Early concern follows the native Burned Tower episode, before later lessons.
@ Appended SILVER51 / partner52 share FLAG_TEMP_1D; no native actor is moved.
CG_SilverEcruteakVisibility::
	setflag FLAG_TEMP_1D
	callnative Special_CharacterStoryAdopt, requests_effects=1
	goto_if_eq VAR_RESULT, FALSE, CG_Return
	goto_if_set FLAG_SV01_SEEN, CG_Return
	goto_if_unset JOHTO_FLAG_RELEASED_BEASTS, CG_Return
	goto_if_lt JOHTO_VAR_ECRUTEAK_CITY_STATE, 4, CG_Return
	goto_if_ge JOHTO_VAR_GOLDENROD_CITY_STATE, 9, CG_Return
	goto_if_ge JOHTO_VAR_ECRUTEAK_CITY_THEATER, 4, CG_Return
	goto_if_ge JOHTO_VAR_ROUTE27_STATE, 3, CG_Return
	setvar VAR_0x8004, 52
	setvar VAR_0x8005, 1
	callnative Special_CharacterStoryPartner, requests_effects=1
	goto_if_eq VAR_RESULT, FALSE, CG_Return
	clearflag FLAG_TEMP_1D
	return
CG_SilverEcruteak::
	lock
	faceplayer
	call CG_SilverEcruteakVisibility
	goto_if_set FLAG_TEMP_1D, CG_Release
	turnobject 51, DIR_EAST
	applymovement 52, CG_Movement_TiredPartner
	waitmovement 0
	msgbox CG_Text_SV01
	faceplayer
	msgbox CG_Text_SV01_Defensive
	setflag FLAG_SV01_SEEN
	closemessage
	fadescreen FADE_TO_BLACK
	removeobject 51
	removeobject 52
	fadescreen FADE_FROM_BLACK
	release
	end
CG_Movement_TiredPartner::
	walk_in_place_slow_down
	delay_16
	step_end

@ Goldenrod9 is written after Silver's original Lance/love/trust conversation.
@ This quiet waiting scene grants no healing or native progress.
CG_SilverGoldenrodVisibility::
	setflag FLAG_TEMP_1D
	callnative Special_CharacterStoryAdopt, requests_effects=1
	goto_if_eq VAR_RESULT, FALSE, CG_Return
	goto_if_lt JOHTO_VAR_GOLDENROD_CITY_STATE, 9, CG_Return
	goto_if_ge JOHTO_VAR_ECRUTEAK_CITY_THEATER, 4, CG_Return
	goto_if_ge JOHTO_VAR_ROUTE27_STATE, 3, CG_Return
	clearflag FLAG_TEMP_1D
	return
CG_SilverGoldenrod::
	lock
	faceplayer
	call CG_SilverGoldenrodVisibility
	goto_if_set FLAG_TEMP_1D, CG_Release
	goto_if_set FLAG_SV02_SEEN, CG_SilverGoldenrodRepeat
	msgbox CG_Text_SV02
	msgbox CG_Text_SV02_Question, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, CG_SilverGoldenrodLater
	msgbox CG_Text_SV02_Wait
	goto CG_SilverGoldenrodFinish
CG_SilverGoldenrodLater::
	msgbox CG_Text_SV02_Later
CG_SilverGoldenrodFinish::
	setflag FLAG_SV02_SEEN
	release
	end
CG_SilverGoldenrodRepeat::
	msgbox CG_Text_SV02_Repeat
	release
	end

@ Native actor33 remains owned by the Route42-to-Mahogany initialization.
@ Show this optional post-Victory-Road scene only while native33 is hidden.
@ Appended SILVER36 / partner37 preserve every original actor and flag.
CG_SilverDenVisibility::
	setflag FLAG_TEMP_1D
	callnative Special_CharacterStoryAdopt, requests_effects=1
	goto_if_eq VAR_RESULT, FALSE, CG_Return
	goto_if_lt JOHTO_VAR_ROUTE27_STATE, 3, CG_Return
	goto_if_unset JOHTO_FLAG_HIDE_DRAGONS_DEN_CAVERN_SILVER, CG_Return
	setvar VAR_0x8004, 37
	setvar VAR_0x8005, 2
	callnative Special_CharacterStoryPartner, requests_effects=1
	goto_if_eq VAR_RESULT, FALSE, CG_Return
	clearflag FLAG_TEMP_1D
	return
CG_SilverDen::
	lock
	faceplayer
	call CG_SilverDenVisibility
	goto_if_set FLAG_TEMP_1D, CG_Release
	goto_if_set FLAG_SV03_SEEN, CG_SilverDenRepeat
	turnobject 36, DIR_EAST
	msgbox CG_Text_SV03_Partner
	applymovement 37, CG_Movement_WillingPartner
	waitmovement 0
	faceplayer
	msgbox CG_Text_SV03_Player
	setflag FLAG_SV03_SEEN
	release
	end
CG_SilverDenRepeat::
	msgbox CG_Text_SV03_Player
	release
	end
CG_Movement_WillingPartner::
	jump_in_place_up
	face_left
	step_end

@ GD01: Gold, the New Bark boy who took a starter beside the player's in Elm's lab ("Next time, I'll win!"),
@ waits outside Violet's Gym after the Zephyr Badge: Falkner beat him twice. The battle is optional; after it
@ he goes to heal and try Falkner again. Appended LOCALID_VIOLET_GOLD shares FLAG_TEMP_1D. He is gone once the
@ scene is played through (JOHTO_FLAG_GD01_SEEN) or once the player has a second Johto badge.
CG_GoldVioletVisibility::
	setflag FLAG_TEMP_1D
	callnative Special_CharacterStoryAdopt, requests_effects=1
	goto_if_eq VAR_RESULT, FALSE, CG_Return
	goto_if_set JOHTO_FLAG_GD01_SEEN, CG_Return
	goto_if_unset JOHTO_FLAG_BADGE01_GET, CG_Return
	goto_if_set JOHTO_FLAG_BADGE02_GET, CG_Return
	clearflag FLAG_TEMP_1D
	return
CG_GoldViolet::
	lock
	faceplayer
	call CG_GoldVioletVisibility
	goto_if_set FLAG_TEMP_1D, CG_Release
	msgbox CG_Text_GD01_Falkner
	msgbox CG_Text_GD01_Ask, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, CG_GoldVioletLater
	msgbox CG_Text_GD01_Go
	closemessage
	@ Gold took the starter the player's is strong against (JOHTO_VAR_STARTER_MON is the player's).
	goto_if_eq JOHTO_VAR_STARTER_MON, 1, CG_GoldVioletChikorita
	goto_if_eq JOHTO_VAR_STARTER_MON, 2, CG_GoldVioletCyndaquil
	trainerbattle_no_intro TRAINER_JOHTO_GOLD_VIOLET_TOTODILE_HNS, CG_Text_GD01_Defeat
	goto CG_GoldVioletAfter
CG_GoldVioletChikorita::
	trainerbattle_no_intro TRAINER_JOHTO_GOLD_VIOLET_CHIKORITA_HNS, CG_Text_GD01_Defeat
	goto CG_GoldVioletAfter
CG_GoldVioletCyndaquil::
	trainerbattle_no_intro TRAINER_JOHTO_GOLD_VIOLET_CYNDAQUIL_HNS, CG_Text_GD01_Defeat
CG_GoldVioletAfter::
	msgbox CG_Text_GD01_After
	call_if_ge JOHTO_VAR_NEWBARKTOWN_LABSTATE, 5, CG_GoldVioletTheft
	msgbox CG_Text_GD01_Bye
	closemessage
	setflag JOHTO_FLAG_GD01_SEEN
	@ He walks off east, toward the Center, round whichever side the player is talking from.
	goto_if_eq VAR_FACING, DIR_NORTH, CG_GoldVioletLeaveAround
	applymovement LOCALID_VIOLET_GOLD, CG_Movement_GoldLeavesViolet
	goto CG_GoldVioletGone
CG_GoldVioletLeaveAround::
	applymovement LOCALID_VIOLET_GOLD, CG_Movement_GoldLeavesVioletAround
CG_GoldVioletGone::
	waitmovement LOCALID_VIOLET_GOLD
	removeobject LOCALID_VIOLET_GOLD
	setflag FLAG_TEMP_1D
	release
	end
CG_GoldVioletTheft::
	msgbox CG_Text_GD01_Theft
	return
CG_GoldVioletLater::
	msgbox CG_Text_GD01_Later
	release
	end
CG_Movement_GoldLeavesViolet::
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end
CG_Movement_GoldLeavesVioletAround::
	walk_right
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

CG_Text_BL01::
	.string "{RIVAL}: Great battle, {PLAYER}!\pGrandpa's taking me on his next\nfield survey.\pI've already filled half a\nnotebook. Apparently I'm meant\lto leave room for the results!$"
CG_Text_BL02::
	.string "{RIVAL}: These PIDGEY use the\nsame tree when the wind changes.\pI'm trying to find out why.$"
CG_Text_BL02_Question::
	.string "Ask what he has learned?$"
CG_Text_BL02_Answer::
	.string "{RIVAL}: The youngest follow\nan older bird.\pTomorrow I'm watching who\nchooses first.$"
CG_Text_BL02_Later::
	.string "{RIVAL}: Tell me if you see\nthem farther down the route.$"
CG_Text_BL03::
	.string "{RIVAL}: Grandpa and I compare\nobservations from both regions.\pNext time we battle, I'm\nbringing a notebook.\pTry to give me something\ninteresting to write down!$"
CG_Text_BlueRepeat::
	.string "{RIVAL}: There's always\nsomething new to observe.$"
CG_Text_BlueUmbreon::
	.string "{RIVAL}: My EEVEE evolved into\nUMBREON during our JOHTO fieldwork.\pIt still enjoys a good battle!$"
CG_Text_SV01::
	.string "{RIVAL}: We're stopping here.\nCatch your breath.$"
CG_Text_SV01_Defensive::
	.string "{RIVAL}: What? You can't train\nproperly when you're exhausted.$"
CG_Text_SV02::
	.string "{RIVAL}: They said it'll\nbe fine.\pI'm waiting anyway.$"
CG_Text_SV02_Question::
	.string "Wait with him?$"
CG_Text_SV02_Wait::
	.string "{RIVAL}: ...Do what you want.$"
CG_Text_SV02_Later::
	.string "{RIVAL}: Yeah.$"
CG_Text_SV02_Repeat::
	.string "{RIVAL}: I'm waiting anyway.$"
CG_Text_SV03_Partner::
	.string "{RIVAL}: Another round?$"
CG_Text_SV03_Player::
	.string "{RIVAL}: We'll be ready\nnext time.$"
CG_Text_GD01_Falkner::
	.string "GOLD: {PLAYER}! You beat FALKNER\nalready?\pHe beat me. Twice! I even caught\na GEODUDE in DARK CAVE for him.\pRock beats flying. It just has to\nhit something first.$"
CG_Text_GD01_Ask::
	.string "GOLD: Show me how a CHAMPION does\nit? I did say I'd win next time!$"
CG_Text_GD01_Later::
	.string "GOLD: Okay! I'll be right here,\nwatching the GYM door.$"
CG_Text_GD01_Go::
	.string "GOLD: All right! Don't go easy\non me!$"
CG_Text_GD01_Defeat::
	.string "GOLD: Next time. Definitely\nnext time!$"
CG_Text_GD01_After::
	.string "GOLD: You waited. Every turn, you\nwatched what I did first.\pI just keep shouting moves.\nFALKNER said that, too.$"
CG_Text_GD01_Theft::
	.string "GOLD: Hey, did you hear? Someone\nbroke into PROF.ELM's lab.\pThey took the POKéMON that sat\nnext to mine on the table.\pThe officer said his name was\n{RIVAL}. If I see him, I'll tell\lhim what I think of that!$"
CG_Text_GD01_Bye::
	.string "GOLD: I'm healing up and trying\nFALKNER again. Third time!\pSee you around, CHAMPION!$"
