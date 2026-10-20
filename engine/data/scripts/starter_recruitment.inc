@ ST02–ST04: optional native gifts. No campaign, weather or party gate.
@ Map-local IDs are append-only and bound in the private placement manifest.

ST02_Caretaker::
	lockall
	faceplayer
	callnative Special_CharacterStoryAdopt, requests_effects=1
	goto_if_eq VAR_RESULT, FALSE, ST_GiftUnavailable
	goto_if_set FLAG_ST02_GIVEN, ST02_Repeat
	goto_if_set FLAG_ST02_CARE_DONE, ST02_Offer
	msgbox ST02_Text_Help, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, ST_GiftLater
	msgbox ST02_Text_Resident
	applymovement ST02_PIDGEY, ST_Movement_Question
	waitmovement 0
	delay 24
	playmoncry SPECIES_PIDGEY, CRY_MODE_NORMAL
	applymovement ST02_PIDGEY, ST_Movement_Heart
	waitmovement 0
	waitmoncry
	msgbox ST02_Text_Shelter
	applymovement ST02_SHELTER, ST_Movement_Lift
	waitmovement 0
	applymovement ST02_BULBASAUR, ST_Movement_Heart
	waitmovement 0
	setflag FLAG_ST02_CARE_DONE
ST02_Offer:
	msgbox ST02_Text_Offer, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, ST_GiftLater
	givemon SPECIES_BULBASAUR, 10
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PARTY, ST02_Delivered
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PC, ST02_Delivered
	goto ST_GiftNoRoom
ST02_Delivered:
	setflag FLAG_ST02_GIVEN
	removeobject ST02_BULBASAUR
	setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_BULBASAUR
	bufferspeciesname STR_VAR_1, SPECIES_BULBASAUR
	call Common_EventScript_GiftMon
	releaseall
	end
ST02_Repeat:
	msgbox ST02_Text_Repeat
	releaseall
	end

ST03_Traveler::
	lockall
	faceplayer
	callnative Special_CharacterStoryAdopt, requests_effects=1
	goto_if_eq VAR_RESULT, FALSE, ST_GiftUnavailable
	goto_if_set FLAG_ST03_GIVEN, ST03_Repeat
	goto_if_ne VAR_MAP_SCENE_ROUTE24, 1, ST03_BridgeFirst
	goto_if_set FLAG_ST03_SHELTER_DONE, ST03_Offer
	msgbox ST03_Text_Help, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, ST_GiftLater
	msgbox ST03_Text_Shelter
	applymovement ST03_SHELTER, ST_Movement_Lift
	waitmovement 0
	delay 32
	playmoncry SPECIES_CHARMANDER, CRY_MODE_NORMAL
	applymovement ST03_CHARMANDER, ST_Movement_Heart
	waitmovement 0
	waitmoncry
	setflag FLAG_ST03_SHELTER_DONE
ST03_Offer:
	msgbox ST03_Text_Offer, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, ST_GiftLater
	givemon SPECIES_CHARMANDER, 12
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PARTY, ST03_Delivered
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PC, ST03_Delivered
	goto ST_GiftNoRoom
ST03_Delivered:
	setflag FLAG_ST03_GIVEN
	removeobject ST03_CHARMANDER
	setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_CHARMANDER
	bufferspeciesname STR_VAR_1, SPECIES_CHARMANDER
	call Common_EventScript_GiftMon
	releaseall
	end
ST03_BridgeFirst:
	msgbox ST03_Text_Bridge
	releaseall
	end
ST03_Repeat:
	msgbox ST03_Text_Repeat
	releaseall
	end

ST04_Jenny::
	lock
	applymovement ST04_JENNY_ACTOR, Common_Movement_FacePlayer
	waitmovement 0
	callnative Special_CharacterStoryAdopt, requests_effects=1
	goto_if_eq VAR_RESULT, FALSE, ST_GiftUnavailable
	goto_if_set FLAG_ST04_GIVEN, ST04_Repeat
	call_if_unset FLAG_ST04_INTRO_SEEN, ST04_Introduction
	goto_if_unset FLAG_BADGE03_GET, ST04_BadgeFirst
	goto_if_set FLAG_ST04_RESCUE_DONE, ST04_Offer
	msgbox ST04_Text_Help, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, ST_GiftLater
	applymovement ST04_SQUIRTLE, ST_Movement_Question
	waitmovement 0
	msgbox ST04_Text_Crate
	applymovement ST04_CRATE, ST_Movement_Lift
	waitmovement 0
	removeobject ST04_CRATE
	applymovement ST04_FRIEND_A, ST_Movement_Lift
	applymovement ST04_FRIEND_B, ST_Movement_Lift
	waitmovement 0
	playmoncry SPECIES_SQUIRTLE, CRY_MODE_NORMAL
	applymovement ST04_SQUIRTLE, ST_Movement_Heart
	waitmovement 0
	waitmoncry
	setflag FLAG_ST04_RESCUE_DONE
ST04_Offer:
	msgbox ST04_Text_Offer, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, ST_GiftLater
	givemon SPECIES_SQUIRTLE, 15
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PARTY, ST04_Delivered
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PC, ST04_Delivered
	goto ST_GiftNoRoom
ST04_Delivered:
	setflag FLAG_ST04_GIVEN
	removeobject ST04_SQUIRTLE
	setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_SQUIRTLE
	bufferspeciesname STR_VAR_1, SPECIES_SQUIRTLE
	call Common_EventScript_GiftMon
	releaseall
	end
ST04_Introduction:
	msgbox ST04_Text_Introduction
	setflag FLAG_ST04_INTRO_SEEN
	return
ST04_BadgeFirst:
	msgbox ST04_Text_Badge
	releaseall
	end
ST04_Repeat:
	msgbox ST04_Text_Repeat
	releaseall
	end

ST_GiftLater:
	msgbox ST_Text_Later
	releaseall
	end
ST_GiftNoRoom:
	msgbox ST_Text_NoRoom
	releaseall
	end
ST_GiftUnavailable:
	msgbox ST_Text_Unavailable
	releaseall
	end

ST_Movement_Question:
	emote_question_mark
	step_end
ST_Movement_Heart:
	emote_heart
	step_end
ST_Movement_Lift:
	jump_in_place_down
	step_end

ST02_Text_Help:
	.string "CARETAKER: BULBASAUR guards the\n"
	.string "POKéMON recovering here.\p"
	.string "A gust frightened PIDGEY and\n"
	.string "knocked its little shelter over.\p"
	.string "Could you help me settle them?$"
ST02_Text_Resident:
	.string "You sit quietly beside PIDGEY.\n"
	.string "Its trembling slowly stops.$"
ST02_Text_Shelter:
	.string "You lift the shelter while the\n"
	.string "caretaker secures its loose roof.$"
ST02_Text_Offer:
	.string "CARETAKER: It usually stands\n"
	.string "between strangers and the others.\p"
	.string "Today it stood beside you.\n"
	.string "It wants to see the world.\p"
	.string "Will you take BULBASAUR with you?$"
ST02_Text_Repeat:
	.string "CARETAKER: The garden is peaceful.\n"
	.string "BULBASAUR chose a kind trainer.$"
ST03_Text_Bridge:
	.string "TRAVELER: Please give us a moment.\n"
	.string "Those bridge trainers need you.$"
ST03_Text_Help:
	.string "TRAVELER: The rain has passed,\n"
	.string "but this shelter still drips.\p"
	.string "CHARMANDER keeps waiting for a\n"
	.string "trainer who isn't coming back.\p"
	.string "Help me secure the roof and\n"
	.string "stay with it a little while?$"
ST03_Text_Shelter:
	.string "You hold the roof steady while\n"
	.string "the traveler fastens it.\p"
	.string "You wait beside CHARMANDER.\n"
	.string "At last it looks away from the road.$"
ST03_Text_Offer:
	.string "TRAVELER: You can leave whenever\n"
	.string "you're ready, little one.\p"
	.string "You don't have to keep\n"
	.string "waiting here.\p"
	.string "CHARMANDER steps toward you.\n"
	.string "Will you travel together?$"
ST03_Text_Repeat:
	.string "TRAVELER: Someone finally came\n"
	.string "back for it. Take care out there.$"
ST04_Text_Introduction:
	.string "JENNY: These SQUIRTLE keep taking\n"
	.string "the dockworkers' supplies.\p"
	.string "Their leader thinks my whistle\n"
	.string "is part of the game!$"
ST04_Text_Badge:
	.string "JENNY: I'll watch the harbor.\n"
	.string "Good luck at LT. SURGE's GYM.$"
ST04_Text_Help:
	.string "JENNY: A supply shed overheated!\n"
	.string "A fallen crate blocks the way.\p"
	.string "The SQUIRTLE can put it out,\n"
	.string "but they need a clear path.\p"
	.string "Will you help move the crate?$"
ST04_Text_Crate:
	.string "You lift the fallen crate aside.\n"
	.string "The SQUIRTLE rush to help.\p"
	.string "Working together, they cool\n"
	.string "the shed before anyone is hurt.$"
ST04_Text_Offer:
	.string "JENNY: You got them working\n"
	.string "together. That was the part\l"
	.string "my whistle couldn't manage.\p"
	.string "Their leader wants to join you.\n"
	.string "The others will help here.\p"
	.string "Will you take SQUIRTLE with you?$"
ST04_Text_Repeat:
	.string "JENNY: Its friends are keeping\n"
	.string "the harbor safe. A useful team!$"
ST_Text_Later:
	.string "That's all right. The POKéMON\n"
	.string "will be safe here until you return.$"
ST_Text_NoRoom:
	.string "Make room for this POKéMON,\n"
	.string "then come back to try again.\p"
	.string "The POKéMON will wait safely here.$"
ST_Text_Unavailable:
	.string "Everyone is resting safely.\n"
	.string "Please come back another time.$"
@ ST01: the existing0..2 native rival dispatch remains0 for new Pikachu games.
@ Only the actual new-game cohort receives this scene; older starter history wins.
ST01_LabVisibility::
	setflag FLAG_TEMP_1E
	callnative Special_CharacterStoryAdopt, requests_effects=1
	goto_if_eq VAR_RESULT, FALSE, ST01_Return
	callnative Special_CharacterStarterPreflight, requests_effects=1
	goto_if_eq VAR_RESULT, FALSE, ST01_Return
	goto_if_unset FLAG_ST01_NEW_COHORT, ST01_Return
	setflag FLAG_HIDE_BULBASAUR_BALL
	setflag FLAG_HIDE_SQUIRTLE_BALL
	goto_if_set FLAG_ST01_GIVEN, ST01_Return
	goto_if_set FLAG_SYS_POKEMON_GET, ST01_Return
	goto_if_ge VAR_MAP_SCENE_PALLET_TOWN_PROFESSOR_OAKS_LAB, 3, ST01_Return
	clearflag FLAG_TEMP_1E
ST01_Return:
	return

ST01_LabIntroduction::
	msgbox ST01_Text_Introduction
	applymovement ST01_PIKACHU, ST_Movement_Question
	waitmovement 0
	msgbox ST01_Text_BluePartner
	setvar VAR_MAP_SCENE_PALLET_TOWN_PROFESSOR_OAKS_LAB, 2
	releaseall
	end

ST01_Pikachu::
	lockall
	faceplayer
	callnative Special_CharacterStoryAdopt, requests_effects=1
	goto_if_eq VAR_RESULT, FALSE, ST_GiftUnavailable
	callnative Special_CharacterStarterPreflight, requests_effects=1
	goto_if_eq VAR_RESULT, FALSE, ST_GiftUnavailable
	goto_if_unset FLAG_ST01_NEW_COHORT, ST_GiftUnavailable
	goto_if_set FLAG_ST01_GIVEN, ST_GiftUnavailable
	goto_if_set FLAG_SYS_POKEMON_GET, ST_GiftUnavailable
	goto_if_ne VAR_MAP_SCENE_PALLET_TOWN_PROFESSOR_OAKS_LAB, 2, ST_GiftUnavailable
	msgbox ST01_Text_Space
	delay 24
	applymovement ST01_PIKACHU, ST_Movement_Heart
	waitmovement 0
	playmoncry SPECIES_PIKACHU, CRY_MODE_NORMAL
	waitmoncry
	msgbox ST01_Text_Offer, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, ST01_Decline
	setvar PLAYER_STARTER_NUM, 0
	setvar PLAYER_STARTER_SPECIES, SPECIES_PIKACHU
	setvar RIVAL_STARTER_SPECIES, SPECIES_EEVEE
	setvar RIVAL_STARTER_ID, LOCALID_CHARMANDER_BALL
	@ Preserve native lab's pre-givemon starter/challenge policy.
	setflag FLAG_SYS_POKEMON_GET
	givemon SPECIES_PIKACHU, 5
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PARTY, ST01_Delivered
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PC, ST01_Delivered
	clearflag FLAG_SYS_POKEMON_GET
	goto ST_GiftNoRoom
ST01_Delivered:
	setflag FLAG_ST01_GIVEN
	setflag FLAG_PALLET_LADY_NOT_BLOCKING_SIGN
	setvar VAR_STARTER_MON, 0
	removeobject ST01_PIKACHU
	setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_PIKACHU
	bufferspeciesname STR_VAR_1, SPECIES_PIKACHU
	call Common_EventScript_GiftMon
	@ Native PC-transfer species shares VAR_TEMP_1 with the lab starter index.
	setvar PLAYER_STARTER_NUM, 0
	setvar RIVAL_STARTER_SPECIES, SPECIES_EEVEE
	setvar RIVAL_STARTER_ID, LOCALID_CHARMANDER_BALL
	goto PalletTown_ProfessorOaksLab_EventScript_RivalPicksStarter
ST01_Decline:
	msgbox ST01_Text_Later
	releaseall
	end
ST01_ReservedBall::
	lockall
	faceplayer
	goto_if_lt VAR_MAP_SCENE_PALLET_TOWN_PROFESSOR_OAKS_LAB, 2, ST01_BallBeforeOak
	msgbox ST01_Text_Reserved
	releaseall
	end
ST01_BallBeforeOak:
	msgbox ST01_Text_BallBeforeOak
	releaseall
	end

ST01_OakRepeat::
	msgbox ST01_Text_Introduction
	release
	end
ST01_RivalWaiting::
	msgbox ST01_Text_RivalWaiting
	release
	end

ST01_Text_Introduction:
	.string "OAK: This PIKACHU is wary of\n"
	.string "new faces. Give it some space.\p"
	.string "A partnership begins by\n"
	.string "paying attention.$"
ST01_Text_BluePartner:
	.string "OAK: {RIVAL}, EEVEE is waiting\n"
	.string "in the BALL on the right.\p"
	.string "Let PIKACHU decide first.$"
ST01_Text_Space:
	.string "You wait quietly and let\n"
	.string "PIKACHU watch you.\p"
	.string "Its tense ears slowly relax.$"
ST01_Text_Offer:
	.string "OAK: It seems interested in you!\n"
	.string "Will you travel with PIKACHU?$"
ST01_Text_Later:
	.string "OAK: There's no need to rush.\n"
	.string "It will be here when you're ready.$"
ST01_Text_Reserved:
	.string "OAK: That EEVEE is for {RIVAL}.\n"
	.string "Go and meet PIKACHU.$"
ST01_Text_BallBeforeOak:
	.string "A POKé BALL rests here.\n"
	.string "Its label reads EEVEE.$"
ST01_Text_RivalWaiting:
	.string "{RIVAL}: Go on, {PLAYER}!\n"
	.string "PIKACHU is watching you.\p"
	.string "I have EEVEE to train!$"
