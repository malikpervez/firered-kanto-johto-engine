@ Johto (data/maps/OlivineCity_PortInside_hns/scripts.inc), as built into the FireRed game.

OlivineCity_PortInside_hns_MapScripts::
	.byte 0

OlivineCity_PortInside_EventScript_Oak::
	lock
	playbgm ((558 + 1) + 0x26), FALSE
	playse SE_PIN
	applymovement2 LOCALID_OLIVINEPORT_OAK, J_Common_Movement_ExclamationMark
	delay 55
	waitmovement LOCALID_OLIVINEPORT_OAK
	turnobject LOCALID_OLIVINEPORT_OAK, DIR_NORTH
	msgbox OlivineCity_PortInside_Text_Nationaldex1, MSGBOX_DEFAULT
	closemessage
	applymovement2 LOCALID_OLIVINEPORT_OAK, OlivineCity_PortInside_Movement_OakFixDex
	waitmovement 0
	delay 30
	delay 50
	msgbox OlivineCity_PortInside_Text_Nationaldex3, MSGBOX_DEFAULT
	closemessage
	playse SE_PIN
	applymovement2 LOCALID_OLIVINEPORT_OAK, J_Common_Movement_ExclamationMark
	delay 55
	waitmovement LOCALID_OLIVINEPORT_OAK
	msgbox OlivineCity_PortInside_Text_Nationaldex4, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, OlivineCity_PortInside_Movement_PlayerMoveOver
	waitmovement 0
	applymovement LOCALID_OLIVINEPORT_OAK, OlivineCity_PortInside_Movement_OakLeave
	waitmovement 0
	setflag JOHTO_FLAG_HIDE_OLIVINE_PORT_OAK
	playse SE_EXIT
	removeobject LOCALID_OLIVINEPORT_OAK
	fadedefaultbgm
	waitse
	release
	end

OlivineCity_PortInside_Movement_OakFixDex:
	walk_in_place_up
	walk_in_place_up
	step_end

OlivineCity_PortInside_Movement_PlayerMoveOver:
	walk_up
	walk_left
	face_right
	step_end

OlivineCity_PortInside_Movement_OakLeave:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

OlivineCity_PortInside_Text_Nationaldex1:
	.string "PROF.OAK: Congratulations, {PLAYER}!\nYou have become JOHTO's CHAMPION.\pPROF.ELM told me all about your\njourney. I knew you would do well!$"

OlivineCity_PortInside_Text_Nationaldex2:
	.string "{PLAYER}'s POKéDEX was upgraded\n"
	.string "with the NATIONAL MODE!$"

OlivineCity_PortInside_Text_Nationaldex3:
	.string "Your POKéDEX records both of your\njourneys. Keep up the good work!\pCome see me in PALLET TOWN when\nyou would like to discuss it.$"

OlivineCity_PortInside_Text_Nationaldex4:
	.string "I have a radio show to record at\nGOLDENROD RADIO TOWER.\pEnjoy your travels, and come visit\nmy POKéMON RESEARCH LAB soon!$"

OlivinePort_EventScript_CooltrainerF::
	msgbox OlivinePort_Text_CooltrainerF, MSGBOX_NPC
	end

OlivinePort_EventScript_Fisher1::
	msgbox OlivinePort_Text_FishingGuru1, MSGBOX_NPC
	end

OlivinePort_EventScript_Fisher2::
	msgbox OlivinePort_Text_FishingGuru2, MSGBOX_NPC
	end

OlivinePort_EventScript_Youngster::
	msgbox OlivinePort_Text_Youngster, MSGBOX_NPC
	end

OlivinePort_EventScript_Sailor::
	lock
	faceplayer
	goto_if_ge JOHTO_VAR_SSAQUA_STATE, 7, OlivinePort_EventScript_Sailor_AfterKanto
	msgbox OlivinePort_Text_AskBoard, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, FALSE, OlivinePort_EventScript_Sailor_Refused
	checkitem ITEM_SS_TICKET
	goto_if_eq VAR_RESULT, TRUE, OlivinePort_EventScript_Sailor_MaidenVoyage
	msgbox OlivinePort_Text_NoTicket, MSGBOX_DEFAULT
	closemessage
	release
	end

OlivinePort_EventScript_Sailor_AfterKanto::
	message OlivinePort_Text_WhereSail
	multichoice 20, 0, MULTI_OLIVINE_HARBOR, FALSE
	switch VAR_RESULT
	case 0, OlivinePort_EventScript_ChoseVermilion
	case 1, OlivinePort_EventScript_ChoseSouthernIsland
	case 2, OlivinePort_EventScript_ChoseBirthIsland
	case 3, OlivinePort_EventScript_ChoseFarawayIsland
	case 4, OlivinePort_EventScript_Sailor_Refused
	case 127, OlivinePort_EventScript_Sailor_Refused
	release
	end

OlivinePort_EventScript_ChoseVermilion::
	closemessage
	delay 20
	checkitem ITEM_SS_TICKET
	bufferitemname STR_VAR_1, ITEM_SS_TICKET
	goto_if_eq VAR_RESULT, FALSE, OlivinePort_EventScript_Sailor_NoCredentials
	call OlivinePort_EventScript_EnterShip
	warpsilent MAP_VERMILION_CITY, 38, 36
	waitstate
	release
	end

OlivinePort_EventScript_ChoseSouthernIsland::
	closemessage
	delay 20
	checkitem ITEM_EON_TICKET
	bufferitemname STR_VAR_1, ITEM_EON_TICKET
	goto_if_eq VAR_RESULT, FALSE, OlivinePort_EventScript_Sailor_NoCredentials
	call OlivinePort_EventScript_EnterShip
	warpsilent MAP_SOUTHERN_ISLAND_EXTERIOR_HNS, 13, 22
	waitstate
	release
	end

OlivinePort_EventScript_ChoseBirthIsland::
	closemessage
	delay 20
	checkitem ITEM_AURORA_TICKET
	bufferitemname STR_VAR_1, ITEM_AURORA_TICKET
	goto_if_eq VAR_RESULT, FALSE, OlivinePort_EventScript_Sailor_NoCredentials
	call OlivinePort_EventScript_EnterShip
	warpsilent MAP_BIRTH_ISLAND_EXTERIOR_HNS, 13, 23
	waitstate
	release
	end

OlivinePort_EventScript_ChoseFarawayIsland::
	closemessage
	delay 20
	checkitem ITEM_OLD_SEA_MAP
	bufferitemname STR_VAR_1, ITEM_OLD_SEA_MAP
	goto_if_eq VAR_RESULT, FALSE, OlivinePort_EventScript_Sailor_NoCredentials
	call OlivinePort_EventScript_EnterShip
	warpsilent MAP_FARAWAY_ISLAND_ENTRANCE_HNS, 13, 38
	waitstate
	release
	end

OlivinePort_EventScript_Sailor_MaidenVoyage::
	msgbox OlivinePort_Text_FlashTicket, MSGBOX_DEFAULT
	call OlivinePort_EventScript_EnterShip
	setvar JOHTO_VAR_SSAQUA_STATE, 1
	clearflag JOHTO_FLAG_HIDE_SSAQUA_1F_GRANDPA
	setflag JOHTO_FLAG_HIDE_SSAQUA_ROOM_SSE_GRANDDAUGHTER

	clearflag JOHTO_FLAG_HIDE_SSAQUA_SAILOR
	clearflag JOHTO_FLAG_HIDE_SSAQUA_CAPTAINS_ROOM_GRANDDAUGHTER

	warpsilent MAP_SSAQUA_1F_HNS, 29, 3
	waitstate
	release
	end

OlivinePort_EventScript_EnterShip::
	msgbox OlivinePort_Text_SailorGetOnBoard, MSGBOX_DEFAULT
	closemessage
	delay 20
	applymovement LOCALID_OLIVINEPORT_SAILOR, OlivinePort_Movement_SailorEnterBoat
	waitmovement 0
	playse SE_EXIT
	applymovement OBJ_EVENT_ID_PLAYER, OlivinePort_Movement_PlayerEnterBoat
	waitmovement 0
	special SpawnCameraObject
	playse SE_EXIT
	removeobject OBJ_EVENT_ID_PLAYER
	delay 60
	applymovement LOCALID_OLIVINEPORT_SAILOR, OlivinePort_Movement_BoatLeave
	applymovement LOCALID_OLIVINEPORT_BOAT, OlivinePort_Movement_BoatLeave
	waitmovement LOCALID_OLIVINEPORT_BOAT
	setrespawn JOHTO_HEAL_LOCATION_OLIVINE_CITY_HNS
	return

OlivinePort_EventScript_Sailor_Refused::
	msgbox OlivinePort_Text_ComeAgain, MSGBOX_DEFAULT
	closemessage
	release
	end

OlivinePort_EventScript_Sailor_NoCredentials::
	msgbox OlivinePort_Text_NoPass, MSGBOX_DEFAULT
	closemessage
	release
	end

OlivinePort_Movement_SailorEnterBoat:
	walk_down
	walk_down
	step_end

OlivinePort_Movement_PlayerEnterBoat:
	walk_down
	walk_down
	walk_in_place_down
	step_end

OlivinePort_Movement_BoatLeave:
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

OlivinePort_Text_NoPass:
	.string "{PLAYER} tried to show the\n"
	.string "{STR_VAR_1}…\p"
	.string "…But no {STR_VAR_1}!\p"
	.string "Sorry!\n"
	.string "You may board only if you have an\l"
	.string "{STR_VAR_1}.$"

OlivinePort_Text_SailorGetOnBoard:
	.string "We're departing soon.\n"
	.string "Please get on board.$"

OlivinePort_Text_CantBoard:
	.string "Sorry. You can't board now.$"

OlivinePort_Text_WhereSail:
	.string "Where would you like to sail?$"

OlivinePort_Text_AskBoard:
	.string "Welcome to FAST SHIP S.S.AQUA.\p"
	.string "Will you be boarding today?$"

OlivinePort_Text_AskTicket:
	.string "May I see your S.S.TICKET?$"

OlivinePort_Text_ComeAgain:
	.string "We hope to see you again!$"

OlivinePort_Text_FlashTicket:
	.string "{PLAYER} flashed the S.S.TICKET.\p"
	.string "That's it. Thank you!$"

OlivinePort_Text_NoTicket:
	.string "{PLAYER} tried to show the\n"
	.string "S.S.TICKET…\p"
	.string "…But no TICKET!\p"
	.string "Sorry!\n"
	.string "You may board only\l"
	.string "if you have an S.S.TICKET.$"

OlivinePort_Text_FishingGuru1:
	.string "SHELLDER are easy to catch here.\p"
	.string "They're kind of rare elsewhere.$"

OlivinePort_Text_FishingGuru2:
	.string "How many RODS do you have?\p"
	.string "Different RODS catch different\n"
	.string "POKéMON.$"

OlivinePort_Text_Youngster:
	.string "S.S.AQUA uses jets to skim\n"
	.string "over the waves!$"

OlivinePort_Text_CooltrainerF:
	.string "There are lots of POKéMON in KANTO.\p"
	.string "I wish I could go…$"

OlivinePort_Text_SailorBeforeHOF:
	.string "We don't want you to fall into the\n"
	.string "sea, so you're not allowed in.$"

