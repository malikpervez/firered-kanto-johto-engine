@ Johto (data/maps/OlivineCity_PortInside_hns/scripts.inc), as built into the FireRed game.

OlivineCity_PortInside_hns_MapScripts::
	.byte 0

OlivineCity_PortInside_EventScript_Oak::
	lock
	playbgm ((558 + 1) + 0x26), FALSE
	playse 21
	applymovement2 7, J_Common_Movement_ExclamationMark
	delay 55
	waitmovement 7
	turnobject 7, DIR_NORTH
	msgbox OlivineCity_PortInside_Text_Nationaldex1, MSGBOX_DEFAULT
	closemessage
	applymovement2 7, OlivineCity_PortInside_Movement_OakFixDex
	waitmovement 0
	delay 30
	delay 50
	msgbox OlivineCity_PortInside_Text_Nationaldex3, MSGBOX_DEFAULT
	closemessage
	playse 21
	applymovement2 7, J_Common_Movement_ExclamationMark
	delay 55
	waitmovement 7
	msgbox OlivineCity_PortInside_Text_Nationaldex4, MSGBOX_DEFAULT
	closemessage
	applymovement 255, OlivineCity_PortInside_Movement_PlayerMoveOver
	waitmovement 0
	applymovement 7, OlivineCity_PortInside_Movement_OakLeave
	waitmovement 0
	setflag 8321
	playse 9
	removeobject 7
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
	.string "PROF.OAK{SE_M_HEAT_WAVE}Congratulations{SE_M_SUPERSONIC}{PLAYER}!\nYo{SE_M_DIVE}hav{SE_M_REVERSAL}becom{SE_M_REVERSAL}JOHTO'{SE_M_GRASSWHISTLE}CHAMPION.\pPROF.EL{SE_M_GIGA_DRAIN}tol{SE_M_WATERFALL}m{SE_M_REVERSAL}al{SE_M_BATON_PASS}abou{SE_M_SPIT_UP}your\njourney{SE_M_PERISH_SONG}{SE_M_HEAL_BELL}kne{SE_M_TWISTER}yo{SE_M_DIVE}woul{SE_M_WATERFALL}d{SE_M_ATTRACT2}well!$"

OlivineCity_PortInside_Text_Nationaldex2:
	.string "{PLAYER}'{SE_M_GRASSWHISTLE}POKéDE{SE_M_LOCK_ON}wa{SE_M_GRASSWHISTLE}upgraded\n"
	.string "wit{SE_M_TRI_ATTACK}th{SE_M_REVERSAL}NATIONA{SE_M_BRICK_BREAK}MODE!$"

OlivineCity_PortInside_Text_Nationaldex3:
	.string "You{SE_M_SAND_TOMB}POKéDE{SE_M_LOCK_ON}record{SE_M_GRASSWHISTLE}bot{SE_M_TRI_ATTACK}o{SE_M_ACID_ARMOR}your\njourneys{SE_M_PERISH_SONG}Kee{SE_M_MORNING_SUN}u{SE_M_MORNING_SUN}th{SE_M_REVERSAL}goo{SE_M_WATERFALL}work!\pCom{SE_M_REVERSAL}se{SE_M_REVERSAL}m{SE_M_REVERSAL}i{SE_M_ATTRACT}PALLE{SE_M_SWIFT}TOW{SE_M_PSYBEAM2}when\nyo{SE_M_DIVE}woul{SE_M_WATERFALL}lik{SE_M_REVERSAL}t{SE_M_ATTRACT2}discus{SE_M_GRASSWHISTLE}it.$"

OlivineCity_PortInside_Text_Nationaldex4:
	.string "{SE_M_HEAL_BELL}hav{SE_M_REVERSAL}{SE_M_CHARGE}radi{SE_M_ATTRACT2}sho{SE_M_TWISTER}t{SE_M_ATTRACT2}recor{SE_M_WATERFALL}at\nGOLDENRO{SE_M_FAINT_ATTACK}RADI{SE_M_SOLAR_BEAM}TOWER.\pEnjo{SE_M_YAWN}you{SE_M_SAND_TOMB}travels{SE_M_SUPERSONIC}an{SE_M_WATERFALL}com{SE_M_REVERSAL}visit\nm{SE_M_YAWN}POKéMO{SE_M_PSYBEAM2}RESEARC{SE_M_SWAGGER2}LA{SE_M_LICK}soon!$"

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
	goto_if_ge 20603, 7, OlivinePort_EventScript_Sailor_AfterKanto
	msgbox OlivinePort_Text_AskBoard, MSGBOX_YESNO
	goto_if_eq 32781, FALSE, OlivinePort_EventScript_Sailor_Refused
	checkitem ITEM_SS_TICKET
	goto_if_eq 32781, TRUE, OlivinePort_EventScript_Sailor_MaidenVoyage
	msgbox OlivinePort_Text_NoTicket, MSGBOX_DEFAULT
	closemessage
	release
	end

OlivinePort_EventScript_Sailor_AfterKanto::
	message OlivinePort_Text_WhereSail
	multichoice 20, 0, 169, FALSE
	switch 32781
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
	goto_if_eq 32781, FALSE, OlivinePort_EventScript_Sailor_NoCredentials
	call OlivinePort_EventScript_EnterShip
	warpsilent MAP_VERMILION_CITY, 13, 26
	waitstate
	release
	end

OlivinePort_EventScript_ChoseSouthernIsland::
	closemessage
	delay 20
	checkitem ITEM_EON_TICKET
	bufferitemname STR_VAR_1, ITEM_EON_TICKET
	goto_if_eq 32781, FALSE, OlivinePort_EventScript_Sailor_NoCredentials
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
	goto_if_eq 32781, FALSE, OlivinePort_EventScript_Sailor_NoCredentials
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
	goto_if_eq 32781, FALSE, OlivinePort_EventScript_Sailor_NoCredentials
	call OlivinePort_EventScript_EnterShip
	warpsilent MAP_FARAWAY_ISLAND_ENTRANCE_HNS, 13, 38
	waitstate
	release
	end

OlivinePort_EventScript_Sailor_MaidenVoyage::
	msgbox OlivinePort_Text_FlashTicket, MSGBOX_DEFAULT
	call OlivinePort_EventScript_EnterShip
	setvar 20603, 1
	clearflag 8325
	setflag 8327

	clearflag 8328
	clearflag 8326

	warpsilent MAP_SSAQUA_1F_HNS, 29, 3
	waitstate
	release
	end

OlivinePort_EventScript_EnterShip::
	msgbox OlivinePort_Text_SailorGetOnBoard, MSGBOX_DEFAULT
	closemessage
	delay 20
	applymovement 1, OlivinePort_Movement_SailorEnterBoat
	waitmovement 0
	playse 9
	applymovement 255, OlivinePort_Movement_PlayerEnterBoat
	waitmovement 0
	special SpawnCameraObject
	playse 9
	removeobject 255
	delay 60
	applymovement 1, OlivinePort_Movement_BoatLeave
	applymovement 6, OlivinePort_Movement_BoatLeave
	waitmovement 6
	setrespawn 134
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
	.string "{PLAYER} trie{SE_M_WATERFALL}t{SE_M_ATTRACT2}sho{SE_M_TWISTER}the\n"
	.string "{STR_VAR_1}…\p"
	.string "…Bu{SE_M_SPIT_UP}n{SE_M_ATTRACT2}{STR_VAR_1}!\p"
	.string "Sorry!\n"
	.string "Yo{SE_M_DIVE}ma{SE_M_YAWN}boar{SE_M_WATERFALL}onl{SE_M_YAWN}i{SE_M_ACID_ARMOR}yo{SE_M_DIVE}hav{SE_M_REVERSAL}an\l"
	.string "{STR_VAR_1}.$"

OlivinePort_Text_SailorGetOnBoard:
	.string "We'r{SE_M_REVERSAL}departin{SE_M_SANDSTORM}soon.\n"
	.string "Pleas{SE_M_REVERSAL}ge{SE_M_SPIT_UP}o{SE_M_ATTRACT}board.$"

OlivinePort_Text_CantBoard:
	.string "Sorry{SE_M_PERISH_SONG}Yo{SE_M_DIVE}can'{SE_M_SPIT_UP}boar{SE_M_WATERFALL}now.$"

OlivinePort_Text_WhereSail:
	.string "Wher{SE_M_REVERSAL}woul{SE_M_WATERFALL}yo{SE_M_DIVE}lik{SE_M_REVERSAL}t{SE_M_ATTRACT2}sail?$"

OlivinePort_Text_AskBoard:
	.string "Welcom{SE_M_REVERSAL}t{SE_M_ATTRACT2}FAS{SE_M_SWIFT}SHI{SE_M_PETAL_DANCE}S.S.AQUA.\p"
	.string "Wil{SE_M_BATON_PASS}yo{SE_M_DIVE}b{SE_M_REVERSAL}boardin{SE_M_SANDSTORM}today?$"

OlivinePort_Text_AskTicket:
	.string "Ma{SE_M_YAWN}{SE_M_HEAL_BELL}se{SE_M_REVERSAL}you{SE_M_SAND_TOMB}S.S.TICKET?$"

OlivinePort_Text_ComeAgain:
	.string "W{SE_M_REVERSAL}hop{SE_M_REVERSAL}t{SE_M_ATTRACT2}se{SE_M_REVERSAL}yo{SE_M_DIVE}again!$"

OlivinePort_Text_FlashTicket:
	.string "{PLAYER} flashe{SE_M_WATERFALL}th{SE_M_REVERSAL}S.S.TICKET.\p"
	.string "That'{SE_M_GRASSWHISTLE}it{SE_M_PERISH_SONG}Than{SE_M_ENCORE2}you!$"

OlivinePort_Text_NoTicket:
	.string "{PLAYER} trie{SE_M_WATERFALL}t{SE_M_ATTRACT2}sho{SE_M_TWISTER}the\n"
	.string "S.S.TICKET…\p"
	.string "…Bu{SE_M_SPIT_UP}n{SE_M_ATTRACT2}TICKET!\p"
	.string "Sorry!\n"
	.string "Yo{SE_M_DIVE}ma{SE_M_YAWN}boar{SE_M_WATERFALL}only\l"
	.string "i{SE_M_ACID_ARMOR}yo{SE_M_DIVE}hav{SE_M_REVERSAL}a{SE_M_ATTRACT}S.S.TICKET.$"

OlivinePort_Text_FishingGuru1:
	.string "SHELLDE{SE_M_MINIMIZE}ar{SE_M_REVERSAL}eas{SE_M_YAWN}t{SE_M_ATTRACT2}catc{SE_M_TRI_ATTACK}here.\p"
	.string "They'r{SE_M_REVERSAL}kin{SE_M_WATERFALL}o{SE_M_ACID_ARMOR}rar{SE_M_REVERSAL}elsewhere.$"

OlivinePort_Text_FishingGuru2:
	.string "Ho{SE_M_TWISTER}man{SE_M_YAWN}ROD{SE_M_SKETCH}d{SE_M_ATTRACT2}yo{SE_M_DIVE}have?\p"
	.string "Differen{SE_M_SPIT_UP}ROD{SE_M_SKETCH}catc{SE_M_TRI_ATTACK}different\n"
	.string "POKéMON.$"

OlivinePort_Text_Youngster:
	.string "S.S.AQU{SE_M_BONEMERANG}use{SE_M_GRASSWHISTLE}jet{SE_M_GRASSWHISTLE}t{SE_M_ATTRACT2}skim\n"
	.string "ove{SE_M_SAND_TOMB}th{SE_M_REVERSAL}waves!$"

OlivinePort_Text_CooltrainerF:
	.string "Ther{SE_M_REVERSAL}ar{SE_M_REVERSAL}lot{SE_M_GRASSWHISTLE}o{SE_M_ACID_ARMOR}POKéMO{SE_M_PSYBEAM2}i{SE_M_ATTRACT}KANTO.\p"
	.string "{SE_M_HEAL_BELL}wis{SE_M_TRI_ATTACK}{SE_M_HEAL_BELL}coul{SE_M_WATERFALL}go…$"

OlivinePort_Text_SailorBeforeHOF:
	.string "W{SE_M_REVERSAL}don'{SE_M_SPIT_UP}wan{SE_M_SPIT_UP}yo{SE_M_DIVE}t{SE_M_ATTRACT2}fal{SE_M_BATON_PASS}int{SE_M_ATTRACT2}the\n"
	.string "sea{SE_M_SUPERSONIC}s{SE_M_ATTRACT2}you'r{SE_M_REVERSAL}no{SE_M_SPIT_UP}allowe{SE_M_WATERFALL}in.$"

