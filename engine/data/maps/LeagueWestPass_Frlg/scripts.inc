@ The outdoor western League road opens after the native Kanto Championship.
@ Existing regional initialization is idempotent and preserves Kanto state.
LeagueWestPass_Frlg_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, LeagueWestPass_OnFrame
	.byte 0

LeagueWestPass_OnFrame::
	map_script_2 VAR_TEMP_0, 0, LeagueWestPass_EventScript_CheckEntry
	.2byte 0

LeagueWestPass_EventScript_CheckEntry::
	lockall
	goto_if_unset FLAG_SYS_GAME_CLEAR, LeagueWestPass_EventScript_Closed
	special Special_JohtoCampaignGetState
	goto_if_eq VAR_RESULT, TRUE, LeagueWestPass_EventScript_Ready
	special Special_JohtoCampaignInitialize
	goto_if_eq VAR_RESULT, FALSE, LeagueWestPass_EventScript_Unavailable
	msgbox LeagueWestPass_Text_ChampionWelcome, MSGBOX_DEFAULT
	closemessage

LeagueWestPass_EventScript_Ready::
	setvar VAR_TEMP_0, 1
	releaseall
	end

LeagueWestPass_EventScript_Closed::
	msgbox LeagueWestPass_Text_Closed, MSGBOX_DEFAULT
	goto LeagueWestPass_EventScript_ReturnToLeague

LeagueWestPass_EventScript_Unavailable::
	msgbox LeagueWestPass_Text_Unavailable, MSGBOX_DEFAULT

LeagueWestPass_EventScript_ReturnToLeague::
	closemessage
	warp MAP_INDIGO_PLATEAU_EXTERIOR, 11, 8
	waitstate
	releaseall
	end

LeagueWestPass_EventScript_Officer::
	lock
	faceplayer
	goto_if_unset FLAG_SYS_GAME_CLEAR, LeagueWestPass_EventScript_Closed
	msgbox LeagueWestPass_Text_Directions, MSGBOX_DEFAULT
	closemessage
	release
	end

LeagueWestPass_EventScript_Sign::
	msgbox LeagueWestPass_Text_Sign, MSGBOX_SIGN
	end

LeagueWestPass_EventScript_Traveller::
	lock
	faceplayer
	msgbox LeagueWestPass_Text_Traveller, MSGBOX_DEFAULT
	closemessage
	release
	end

LeagueWestPass_Text_ChampionWelcome::
	.string "OFFICER: Congratulations, {PLAYER}!\p"
	.string "PROF.OAK asked us to look out\n"
	.string "for you. You're off to meet ELM?\p"
	.string "The crew just finished repairing\n"
	.string "this western LEAGUE road.\p"
	.string "Follow it down through the woods\n"
	.string "to the coast on ROUTE 27.\p"
	.string "Bring a POKéMON that can SURF.\n"
	.string "Head west across the water.\p"
	.string "You'll reach NEW BARK TOWN,\n"
	.string "on the shore in JOHTO.\p"
	.string "ELM's lab is in the northwest\n"
	.string "part of town. He's expecting you!\p"
	.string "Take your time, CHAMPION. A new\n"
	.string "journey deserves a good beginning!$"

LeagueWestPass_Text_Closed::
	.string "OFFICER: The western road is\n"
	.string "closed for construction.\p"
	.string "Come back after your KANTO LEAGUE\n"
	.string "challenge. The crew will be done.\p"
	.string "Good luck against the ELITE FOUR!$"

LeagueWestPass_Text_Unavailable::
	.string "OFFICER: I can't clear your trip\n"
	.string "at the moment.\p"
	.string "Please return to INDIGO PLATEAU.\n"
	.string "Your journey can wait safely.$"

LeagueWestPass_Text_Directions::
	.string "Follow the road west and downhill\n"
	.string "to the coast on ROUTE 27.\p"
	.string "SURF west to NEW BARK TOWN.\n"
	.string "SURF east to return to this road.\p"
	.string "The road back east leads to\n"
	.string "INDIGO PLATEAU in KANTO.\p"
	.string "PROF.ELM's lab is in the northwest\n"
	.string "part of NEW BARK. Safe travels!$"

LeagueWestPass_Text_Sign::
	.string "WESTERN LEAGUE ROAD\p"
	.string "EAST: INDIGO PLATEAU\n"
	.string "DOWNHILL: ROUTE 27 COAST\p"
	.string "SURF WEST TO NEW BARK TOWN$"

LeagueWestPass_Text_Traveller::
	.string "Can you feel that breeze?\p"
	.string "It's coming across the water from\n"
	.string "NEW BARK, the town of new winds.\p"
	.string "Sounds like a fine place to start\n"
	.string "another adventure, doesn't it?$"
