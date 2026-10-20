@ Johto (data/maps/Route30_MrPokemonsHouse_hns/scripts.inc), as built into the FireRed game.

Route30_MrPokemonsHouse_hns_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, MrPokemonHouse_OnFrame
	.byte 0

MrPokemonHouse_OnFrame::
	map_script_2 JOHTO_VAR_CHERRYGROVE_CITY_STATE, 1, MrPokemonHouse_EventScript_GiveEgg
	.2byte 0

MrPokemonHouse_EventScript_GiveEgg::
	lock
	playse SE_PIN
	applymovement LOCALID_MRPOKEMON, J_Common_Movement_ExclamationMark
	delay 55
	waitmovement LOCALID_MRPOKEMON
	turnobject LOCALID_MRPOKEMON, DIR_SOUTH
	msgbox MrPokemonHouse_Text_Intro1, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, MrPokemonHouse_Movement_MeetMrPokemon
	waitmovement 0
	msgbox MrPokemonHouse_Text_Intro2, MSGBOX_DEFAULT

	giveitem ITEM_MYSTERY_EGG
	goto_if_eq JOHTO_VAR_RESULT, FALSE, J_Common_EventScript_ShowBagIsFull

	msgbox MrPokemonHouse_Text_Intro3, MSGBOX_DEFAULT
	msgbox MrPokemonHouse_Text_Intro4, MSGBOX_DEFAULT
	turnobject LOCALID_ROUTE30_OAK, DIR_WEST
	msgbox MrPokemonHouse_Text_Intro5, MSGBOX_DEFAULT
	closemessage
	playbgm ((558 + 1) + 0x26), FALSE
	applymovement LOCALID_ROUTE30_OAK, MrPokemonHouse_Movement_OakToPlayer
	waitmovement 0
	turnobject OBJ_EVENT_ID_PLAYER, DIR_EAST
	msgbox MrPokemonHouse_Text_OakIntro, MSGBOX_DEFAULT




	msgbox MrPokemonHouse_Text_OakParting, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_ROUTE30_OAK, MrPokemonHouse_Movement_OakLeave
	waitmovement 0
	playse SE_EXIT
	removeobject LOCALID_ROUTE30_OAK
	setflag JOHTO_FLAG_DELIVERED_EGG
	turnobject 255 DIR_NORTH
	fadedefaultbgm
	msgbox MrPokemonHouse_Text_Heal, MSGBOX_DEFAULT
	call J_Common_EventScript_OutOfCenterPartyHeal
	msgbox MrPokemonHouse_Text_DependingOnYou, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_MRPOKEMON, MrPokemonHouse_Movement_MrPokemon_Leave
	waitmovement 0
	removeobject LOCALID_MRPOKEMON
	clearflag JOHTO_FLAG_HIDE_MRPOKEMON
	addobject LOCALID_MRPOKEMON2

	setvar JOHTO_VAR_NEWBARKTOWN_LABSTATE, 4
	setflag JOHTO_FLAG_HIDE_SILVER_NEWBARKTOWN
	clearflag JOHTO_FLAG_HIDE_LAB_POLICEMAN
	setvar JOHTO_VAR_CHERRYGROVE_CITY_STATE, 2
	setrespawn JOHTO_HEAL_LOCATION_CHERRYGROVE_CITY_HNS
	clearflag JOHTO_FLAG_HIDE_SILVER_CHERRYGROVE
	setflag JOHTO_FLAG_HIDE_GUIDE_GENT_CHERRYGROVE
	clearflag JOHTO_FLAG_HIDE_CHERRYGROVE_GUIDE_GENT_HOUSE
	release
	end

MrPokemonHouse_EventScript_MrPokemon::
	lock
	faceplayer
	checkitem ITEM_RED_SCALE
	goto_if_eq VAR_RESULT, TRUE, MrPokemonHouse_EventScript_MrPokemon_RedScale
	msgbox MrPokemonHouse_Text_AlwaysNewDiscoveries, MSGBOX_DEFAULT
	closemessage
	release
	end

MrPokemonHouse_EventScript_MrPokemon_RedScale::
	msgbox MrPokemonHouse_Text_GimmeTheScale, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, TRUE, MrPokemonHouse_EventScript_MrPokemon_RedScale_Accepted
	msgbox MrPokemonHouse_Text_Disappointed, MSGBOX_DEFAULT
	closemessage
	release
	end

MrPokemonHouse_EventScript_MrPokemon_RedScale_Accepted::
	removeitem ITEM_RED_SCALE
	giveitem ITEM_EXP_SHARE_SMALL
	goto_if_eq VAR_RESULT, FALSE, J_Common_EventScript_ShowBagIsFull
	release
	end

MrPokemonHouse_EventScript_Computer::
	lock
	msgbox MrPokemonHouse_Text_BrokenComputer, MSGBOX_SIGN
	release
	end

MrPokemonHouse_EventScript_Magazine::
	lock
	msgbox MrPokemonHouse_Text_ForeignMagazines, MSGBOX_SIGN
	release
	end

MrPokemonHouse_EventScript_Coins::
	lock
	msgbox MrPokemonHouse_Text_StrangeCoins, MSGBOX_SIGN
	release
	end

MrPokemonHouse_Movement_MeetMrPokemon:
	walk_up
	walk_up
	walk_right
	walk_right
	face_up
	step_end

MrPokemonHouse_Movement_OakToPlayer:
	walk_down
	face_left
	step_end

MrPokemonHouse_Movement_OakLeave:
	walk_down
	walk_left
	walk_left
	walk_left
	walk_down
	walk_in_place_down
	step_end

MrPokemonHouse_Movement_MrPokemon_Leave:
	walk_up
	walk_left
	walk_left
	step_end

MrPokemonHouse_Text_Intro1:
	.string "Welcome, {PLAYER}!\p"
	.string "PROF.ELM told me KANTO's\n"
	.string "CHAMPION was coming.\p"
	.string "He also said you were helping\n"
	.string "with his POKéMON research.$"

MrPokemonHouse_Text_Intro2:
	.string "This is what I want PROF.ELM\n"
	.string "to examine.$"

MrPokemonHouse_Text_GotEgg:
	.string "{PLAYER} received MYSTERY EGG.$"

MrPokemonHouse_Text_Intro3:
	.string "I know a couple who run a\n"
	.string "POKéMON DAY-CARE service.\p"
	.string "They gave me that EGG.\p"
	.string "I was intrigued, so I sent\n"
	.string "mail to PROF.ELM.\p"
	.string "For POKéMON evolution,\n"
	.string "PROF.ELM is the authority.$"

MrPokemonHouse_Text_Intro4:
	.string "Even PROF.OAK here recognizes\n"
	.string "that.$"

MrPokemonHouse_Text_Intro5:
	.string "If my assumption is correct,\n"
	.string "PROF.ELM will know it.$"

MrPokemonHouse_Text_Heal:
	.string "You are returning to PROF.ELM?\p"
	.string "Here. Your POKéMON should have\n"
	.string "some rest.$"

MrPokemonHouse_Text_DependingOnYou:
	.string "I'm depending on you!$"

MrPokemonHouse_Text_AlwaysNewDiscoveries:
	.string "Life is delightful!\n"
	.string "Always, new discoveries to be made.$"

MrPokemonHouse_Text_OakIntro::
	.string "OAK: {PLAYER}! Good to see you.\n"
	.string "How was the trip from KANTO?\p"
	.string "I was visiting my old friend\n"
	.string "MR.POKéMON when I heard that you\l"
	.string "were helping PROF.ELM.\p"
	.string "Your experience and care for\n"
	.string "POKéMON will serve him well.\p"
	.string "Keep recording the discoveries\n"
	.string "you make in your POKéDEX!$"

MrPokemonHouse_Text_OakParting:
	.string "Go meet many kinds of POKéMON and\n"
	.string "complete that POKéDEX!\p"
	.string "But I've stayed too long.\p"
	.string "I have to get to GOLDENROD\n"
	.string "for my usual radio show.\p"
	.string "{PLAYER}, I'm counting on you!$"

MrPokemonHouse_Text_GimmeTheScale:
	.string "Hm? That SCALE! What's that?\n"
	.string "A red GYARADOS?\p"
	.string "That's rare! I, I want it…\p"
	.string "{PLAYER}, would you care to\n"
	.string "trade it?\p"
	.string "I can offer this EXP.SHARE\n"
	.string "that I got from PROF.OAK.$"

MrPokemonHouse_Text_Disappointed:
	.string "That's disappointing.\n"
	.string "That happens to be very rare.$"

MrPokemonHouse_Text_ExpShare:
	.string "I also have a special item\n"
	.string "for you.$"

MrPokemonHouse_Text_ForeignMagazines:
	.string "It's packed with foreign\n"
	.string "magazines.\p"
	.string "Can't even read their titles…$"

MrPokemonHouse_Text_BrokenComputer:
	.string "It's a big computer.\n"
	.string "Hmm. It's broken.$"

MrPokemonHouse_Text_StrangeCoins:
	.string "A whole pile of strange coins!\p"
	.string "Maybe they're from another\n"
	.string "country…$"

MrPokemonHouse_Text_GotExpShare:
	.string "{PLAYER} received EXP. SHARE!$"

