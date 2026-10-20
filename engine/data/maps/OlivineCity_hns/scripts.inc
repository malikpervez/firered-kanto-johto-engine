@ Johto (data/maps/OlivineCity_hns/scripts.inc), as built into the FireRed game.

OlivineCity_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, OlivineCity_MapScript_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, J_SetTimeEncounters
	map_script MAP_SCRIPT_ON_FRAME_TABLE, OlivineCity_OnFrame
	.byte 0

OlivineCity_MapScript_OnTransition::
	call RB_OlivineVisibility
	callnative SetTimeBasedEncounters
	goto_if_ge JOHTO_VAR_OLIVINE_CITY_STATE, 5, OlivineCity_MapScript_ClearWeather
	end

OlivineCity_MapScript_ClearWeather::
	setweather WEATHER_NONE
	end

OlivineCity_OnFrame::
	map_script_2 JOHTO_VAR_SAFARI_ZONE_GATE_STATE, 1, OlivineCity_EventScript_BaobaCall
	map_script_2 JOHTO_VAR_TRIGGER_ELM_ROCKET_CALL, 1, Mahoganytown_EventScript_RocketTrigger
	.2byte 0

OlivineCity_EventScript_BaobaCall::
	lock
	setspeaker OlivineCity_Text_BaobaName
	pokenavcall OlivineCity_Text_Baoba
	waitmessage
	delay 30
	setvar JOHTO_VAR_SAFARI_ZONE_GATE_STATE, 2
	release
	end

OlivineCity_Text_BaobaName:
	.string "BAOBA$"

OlivineCity_Text_Baoba:
	.string "{PLAYER}!\p"
	.string "Thi{SE_M_GRASSWHISTLE}i{SE_M_GRASSWHISTLE}WARDE{SE_M_PSYBEAM2}BAOBA.\p"
	.string "Sorr{SE_M_YAWN}t{SE_M_ATTRACT2}hav{SE_M_REVERSAL}kep{SE_M_SPIT_UP}yo{SE_M_DIVE}waiting.\n"
	.string "We'v{SE_M_REVERSAL}finall{SE_M_YAWN}opene{SE_M_WATERFALL}the\l"
	.string "SAFAR{SE_M_HEAL_BELL}ZONE!\p"
	.string "D{SE_M_ATTRACT2}yo{SE_M_DIVE}kno{SE_M_TWISTER}wher{SE_M_REVERSAL}i{SE_M_SPIT_UP}is?\p"
	.string "Yo{SE_M_DIVE}kno{SE_M_TWISTER}th{SE_M_REVERSAL}GAT{SE_M_SWORDS_DANCE}insid{SE_M_REVERSAL}th{SE_M_REVERSAL}cavern\n"
	.string "i{SE_M_ATTRACT}CIANWOO{SE_M_FAINT_ATTACK}CITY?\p"
	.string "I{SE_M_ACID_ARMOR}yo{SE_M_DIVE}g{SE_M_ATTRACT2}throug{SE_M_TRI_ATTACK}ther{SE_M_REVERSAL}an{SE_M_WATERFALL}wal{SE_M_ENCORE2}for\n"
	.string "{SE_M_CHARGE}shor{SE_M_SPIT_UP}while{SE_M_SUPERSONIC}yo{SE_M_DIVE}shoul{SE_M_WATERFALL}soo{SE_M_ATTRACT}see\l"
	.string "th{SE_M_REVERSAL}SAFAR{SE_M_HEAL_BELL}ZONE!\p"
	.string "We'r{SE_M_REVERSAL}{SE_M_CHARGE}littl{SE_M_REVERSAL}ou{SE_M_SPIT_UP}o{SE_M_ACID_ARMOR}th{SE_M_REVERSAL}way{SE_M_SUPERSONIC}but\n"
	.string "pleas{SE_M_REVERSAL}com{SE_M_REVERSAL}visit!$"

OlivineCity_EventScript_CityTrigger::
	setflag JOHTO_FLAG_HIDE_OLIVINE_CITY_GYM_JASMINE
	setflag JOHTO_FLAG_HIDE_OLIVINE_SILVER
	setflag JOHTO_FLAG_VISITED_OLIVINE_CITY
	clearflag JOHTO_FLAG_SAFARI_ZONE_WEST_EXPANSION
	clearflag JOHTO_FLAG_SAFARI_ZONE_EAST_EXPANSION
	clearflag JOHTO_FLAG_HIDE_BATTLEFRONTIER_ENGINEER
	clearflag JOHTO_FLAG_HIDE_LIGHTHOUSE_JASMINE
	clearflag JOHTO_FLAG_HIDE_WHIRL_ISLANDS_TENTACRUEL
	setvar JOHTO_VAR_GETFLY, 0

	setvar JOHTO_VAR_OLIVINE_CITY_STATE, 1


	setvar JOHTO_VAR_SUICUNE_ENCOUNTERS, 1
	clearflag JOHTO_FLAG_HIDE_CIANWOOD_SUICUNE
	setflag JOHTO_FLAG_HIDE_CIANWOOD_EUSINE
	setvar JOHTO_VAR_CIANWOOD_CITY_STATE, 1
	end

OlivineCity_EventScript_SilverTrigger::
	lock
	clearflag JOHTO_FLAG_HIDE_OLIVINE_SILVER
	opendoor 11, 27
	addobject LOCALID_OLIVINE_SILVER
	playbgm ((558 + 1) + 0x3B), FALSE
	delay 20
	closedoor 11, 27
	getplayerxy VAR_TEMP_0, VAR_TEMP_1
	call_if_eq VAR_TEMP_1, 28, OlivineCity_EventScript_SilverWalkToPlayer1
	call_if_eq VAR_TEMP_1, 29, OlivineCity_EventScript_SilverWalkToPlayer2
	call_if_eq VAR_TEMP_1, 30, OlivineCity_EventScript_SilverWalkToPlayer3
	msgbox OlivineCity_Text_SilverEncounter, MSGBOX_DEFAULT
	closemessage
	call_if_eq VAR_TEMP_1, 28, OlivineCity_EventScript_SilverLeaveAdjust1
	call_if_eq VAR_TEMP_1, 29, OlivineCity_EventScript_SilverLeaveAdjust2
	call_if_eq VAR_TEMP_1, 30, OlivineCity_EventScript_SilverLeaveAdjust2
	applymovement LOCALID_OLIVINE_SILVER, OlivineCity_Movement_SilverLeave
	waitmovement 0
	setvar JOHTO_VAR_OLIVINE_CITY_STATE, 2
	setflag JOHTO_FLAG_HIDE_OLIVINE_SILVER
	removeobject LOCALID_OLIVINE_SILVER
	fadedefaultbgm
	release
	end

OlivineCity_EventScript_SilverWalkToPlayer1::
	applymovement 4 OlivineCity_Movement_SilverWalkToPlayer1
	waitmovement 0
	return

OlivineCity_EventScript_SilverWalkToPlayer2::
	applymovement 4 OlivineCity_Movement_SilverWalkToPlayer2
	waitmovement 0
	return

OlivineCity_EventScript_SilverWalkToPlayer3::
	applymovement 4 OlivineCity_Movement_SilverWalkToPlayer3
	waitmovement 0
	return

OlivineCity_EventScript_SilverLeaveAdjust1::
	applymovement 4 J_Common_Movement_WalkDown1
	waitmovement 0
	return

OlivineCity_EventScript_SilverLeaveAdjust2::
	applymovement 4 J_Common_Movement_WalkUp1
	waitmovement 0
	return

OlivineCity_Movement_SilverWalkToPlayer1:
	walk_down
	walk_right
	walk_right
	walk_right
	step_end

OlivineCity_Movement_SilverWalkToPlayer2:
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	step_end

OlivineCity_Movement_SilverWalkToPlayer3:
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	step_end

OlivineCity_Movement_SilverLeave:
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

OlivineCity_Text_SilverEncounter:
	.string "Yo{SE_M_DIVE}again?\n"
	.string "There'{SE_M_GRASSWHISTLE}n{SE_M_ATTRACT2}nee{SE_M_WATERFALL}t{SE_M_ATTRACT2}b{SE_M_REVERSAL}alert.\p"
	.string "{SE_M_HEAL_BELL}don'{SE_M_SPIT_UP}bothe{SE_M_SAND_TOMB}wit{SE_M_TRI_ATTACK}wimps\n"
	.string "lik{SE_M_REVERSAL}you.\p"
	.string "Speakin{SE_M_SANDSTORM}o{SE_M_ACID_ARMOR}weaklings{SE_M_SUPERSONIC}the\n"
	.string "city'{SE_M_GRASSWHISTLE}GY{SE_M_GIGA_DRAIN}LEADE{SE_M_MINIMIZE}isn'{SE_M_SPIT_UP}here,\l"
	.string "an{SE_M_WATERFALL}i{SE_M_GRASSWHISTLE}supposedl{SE_M_YAWN}takin{SE_M_SANDSTORM}care\l"
	.string "o{SE_M_ACID_ARMOR}{SE_M_CHARGE}sic{SE_M_ENCORE2}POKéMO{SE_M_PSYBEAM2}a{SE_M_SPIT_UP}the\l"
	.string "LIGHTHOUSE.\p"
	.string "Humph{SE_M_DRAGON_RAGE}Boo-hoo!\n"
	.string "Jus{SE_M_SPIT_UP}le{SE_M_SPIT_UP}sic{SE_M_ENCORE2}POKéMO{SE_M_PSYBEAM2}go!\p"
	.string "{SE_M_BONEMERANG}POKéMO{SE_M_PSYBEAM2}tha{SE_M_SPIT_UP}can'{SE_M_SPIT_UP}battle\n"
	.string "i{SE_M_GRASSWHISTLE}worthless!\p"
	.string "Wh{SE_M_YAWN}don'{SE_M_SPIT_UP}yo{SE_M_DIVE}g{SE_M_ATTRACT2}trai{SE_M_ATTRACT}a{SE_M_SPIT_UP}the\n"
	.string "LIGHTHOUSE?\p"
	.string "Wh{SE_M_ATTRACT2}knows{SE_M_SING}I{SE_M_SPIT_UP}ma{SE_M_YAWN}mak{SE_M_REVERSAL}yo{SE_M_DIVE}a\n"
	.string "bi{SE_M_SPIT_UP}o{SE_M_ACID_ARMOR}{SE_M_CHARGE}bette{SE_M_SAND_TOMB}Trainer!$"

OlivineCity_EventScript_Sailor1::
	lock
	faceplayer
	msgbox OlivineCity_Text_Sailor1, MSGBOX_DEFAULT
	call_if_ge JOHTO_VAR_GOLDENROD_CITY_STATE, 10, BlackTide_CoastalWarning
	closemessage
	release
	end

OlivineCity_EventScript_Sailor2::
	lock
	faceplayer
	msgbox OlivineCity_Text_Sailor2, MSGBOX_DEFAULT
	closemessage
	release
	end

OlivineCity_EventScript_Youngster::
	lock
	faceplayer
	msgbox OlivineCity_Text_YoungsterPokegear, MSGBOX_DEFAULT
	closemessage
	release
	end

OlivineCity_EventScript_Machoke::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_MACHOKE, CRY_MODE_NORMAL
	msgbox OlivineCity_Text_Machoke, MSGBOX_DEFAULT
	waitmoncry
	release
	end

OlivineCity_EventScript_Sign::
	lock
	msgbox OlivineCity_Text_Sign, MSGBOX_SIGN
	end

OlivineCity_EventScript_PortSign::
	lock
	msgbox OlivineCity_Text_PortSign, MSGBOX_SIGN
	end

OlivineCity_EventScript_CafeSign::
	msgbox OlivineCity_Text_CafeSign, MSGBOX_SIGN
	end

OlivineCity_EventScript_GymSign::
	lock
	msgbox OlivineCity_Text_GymSign, MSGBOX_SIGN
	end

OlivineCity_EventScript_LighthouseSign::
	lock
	msgbox OlivineCity_Text_LighthouseSign, MSGBOX_SIGN
	end

OlivineCity_EventScript_Item_ChargeBeam::
	finditem ITEM_TM_CHARGE_BEAM
	end

OlivineCity_EventScript_EonTicketWoman::
	lock
	faceplayer
	checkitem ITEM_AURORA_TICKET
	goto_if_eq VAR_RESULT, TRUE, OlivineCity_EventScript_EonTicketWomanAfter
	goto_if_set JOHTO_FLAG_IS_KANTO_CHAMPION, OlivineCity_EventScript_EonTicketWomanChamp
	msgbox OlivineCity_Text_EonTicketWoman1, MSGBOX_DEFAULT
	closemessage
	release
	end

OlivineCity_EventScript_EonTicketWomanChamp::
	msgbox OlivineCity_Text_EonTicketWoman2, MSGBOX_DEFAULT
	giveitem ITEM_AURORA_TICKET
	closemessage
	release
	end

OlivineCity_EventScript_EonTicketWomanAfter::
	msgbox OlivineCity_Text_EonTicketWoman3, MSGBOX_DEFAULT
	closemessage
	release
	end

OlivineCity_Text_CafeSign:
	.string "OLIVIN{SE_M_SWORDS_DANCE}CAFE\n"
	.string "WHER{SE_M_SWORDS_DANCE}STRON{SE_M_SWAGGER}SAILOR{SE_M_SKETCH}ENJOY\l"
	.string "HEART{SE_M_MOONLIGHT}MEAL{SE_M_SKETCH}O{SE_M_LEER}STRENGTH$"

OlivineCity_Text_EonTicketWoman1:
	.string "M{SE_M_YAWN}nam{SE_M_REVERSAL}i{SE_M_GRASSWHISTLE}MARY!\p"
	.string "Jus{SE_M_SPIT_UP}kidding{SE_M_SUPERSONIC}bu{SE_M_SPIT_UP}{SE_M_HEAL_BELL}lov{SE_M_REVERSAL}MARY's\n"
	.string "radi{SE_M_ATTRACT2}show!$"

OlivineCity_Text_EonTicketWoman2:
	.string "Yo{SE_M_DIVE}mus{SE_M_SPIT_UP}b{SE_M_REVERSAL}{PLAYER}!!!\p"
	.string "O{SE_M_TRI_ATTACK}m{SE_M_YAWN}goodness{SE_M_DRAGON_RAGE}Th{SE_M_REVERSAL}champion!\p"
	.string "{SE_M_HEAL_BELL}hear{SE_M_WATERFALL}abou{SE_M_SPIT_UP}yo{SE_M_DIVE}o{SE_M_ATTRACT}MARY's\n"
	.string "radi{SE_M_ATTRACT2}show!\p"
	.string "Here{SE_M_SUPERSONIC}tak{SE_M_REVERSAL}this!$"

OlivineCity_Text_EonTicketWoman3:
	.string "{SE_M_HEAL_BELL}can'{SE_M_SPIT_UP}believ{SE_M_REVERSAL}{SE_M_HEAL_BELL}me{SE_M_SPIT_UP}the\n"
	.string "champion!!!$"

OlivineCity_Text_Sailor1:
	.string "Dar{SE_M_ENCORE2}road{SE_M_GRASSWHISTLE}ar{SE_M_REVERSAL}dangerous\n"
	.string "a{SE_M_SPIT_UP}night.\p"
	.string "Bu{SE_M_SPIT_UP}i{SE_M_ATTRACT}th{SE_M_REVERSAL}pitch-blac{SE_M_ENCORE2}of\n"
	.string "night{SE_M_SUPERSONIC}th{SE_M_REVERSAL}se{SE_M_CHARGE}i{SE_M_GRASSWHISTLE}eve{SE_M_ATTRACT}more\l"
	.string "treacherous!\p"
	.string "Withou{SE_M_SPIT_UP}th{SE_M_REVERSAL}beaco{SE_M_ATTRACT}o{SE_M_ACID_ARMOR}the\n"
	.string "LIGHTHOUS{SE_M_SWORDS_DANCE}t{SE_M_ATTRACT2}guid{SE_M_REVERSAL}it,\l"
	.string "n{SE_M_ATTRACT2}shi{SE_M_MORNING_SUN}ca{SE_M_ATTRACT}sail.$"

OlivineCity_Text_YoungsterPokegear:
	.string "Tha{SE_M_SPIT_UP}thin{SE_M_SANDSTORM}yo{SE_M_DIVE}have--\n"
	.string "it'{SE_M_GRASSWHISTLE}{SE_M_CHARGE}POKéGEAR{SE_M_SUPERSONIC}right?\l"
	.string "Wow{SE_M_SUPERSONIC}that'{SE_M_GRASSWHISTLE}cool.$"

OlivineCity_Text_YoungsterPokedex:
	.string "Wow{SE_M_SUPERSONIC}yo{SE_M_DIVE}hav{SE_M_REVERSAL}{SE_M_CHARGE}POKéDEX!\p"
	.string "Tha{SE_M_SPIT_UP}i{SE_M_GRASSWHISTLE}jus{SE_M_SPIT_UP}s{SE_M_ATTRACT2}awesome.$"

OlivineCity_Text_Sailor2:
	.string "Th{SE_M_REVERSAL}leagu{SE_M_REVERSAL}ha{SE_M_GRASSWHISTLE}JASMINE\n"
	.string "pegge{SE_M_WATERFALL}a{SE_M_GRASSWHISTLE}th{SE_M_REVERSAL}sixth\l"
	.string "stronges{SE_M_SPIT_UP}GY{SE_M_GIGA_DRAIN}LEADER!\p"
	.string "Hah{SE_M_DRAGON_RAGE}That'{SE_M_GRASSWHISTLE}{SE_M_CHARGE}loa{SE_M_WATERFALL}o{SE_M_ACID_ARMOR}crud.\p"
	.string "There'{SE_M_GRASSWHISTLE}n{SE_M_ATTRACT2}wa{SE_M_YAWN}PRYC{SE_M_SWORDS_DANCE}could\n"
	.string "hur{SE_M_SPIT_UP}JASMINE'{SE_M_GRASSWHISTLE}STEEL-type\l"
	.string "POKéMON!\p"
	.string "Bureaucrac{SE_M_YAWN}i{SE_M_ACID_ARMOR}yo{SE_M_DIVE}as{SE_M_ENCORE2}me.\p"
	.string "She'{SE_M_GRASSWHISTLE}somethin{SE_M_SANDSTORM}t{SE_M_ATTRACT2}b{SE_M_REVERSAL}feared,\n"
	.string "that'{SE_M_GRASSWHISTLE}fo{SE_M_SAND_TOMB}sure!$"

OlivineCity_Text_Sign:
	.string "OLIVIN{SE_M_SWORDS_DANCE}CITY\p"
	.string "Th{SE_M_REVERSAL}Por{SE_M_SPIT_UP}Closes{SE_M_SPIT_UP}t{SE_M_ATTRACT2}Foreig{SE_M_ATTRACT}Lands$"

OlivineCity_Text_PortSign:
	.string "OLIVIN{SE_M_SWORDS_DANCE}PORT\n"
	.string "FAS{SE_M_SWIFT}SHI{SE_M_PETAL_DANCE}PIER$"

OlivineCity_Text_GymSign:
	.string "OLIVIN{SE_M_SWORDS_DANCE}CIT{SE_M_MOONLIGHT}POKéMO{SE_M_PSYBEAM2}GYM\n"
	.string "LEADER{SE_M_HEAT_WAVE}JASMINE\p"
	.string "Th{SE_M_REVERSAL}Steel-Cla{SE_M_WATERFALL}Defens{SE_M_REVERSAL}Girl$"

OlivineCity_Text_LighthouseSign:
	.string "OLIVIN{SE_M_SWORDS_DANCE}LIGHTHOUSE\n"
	.string "Als{SE_M_ATTRACT2}know{SE_M_ATTRACT}a{SE_M_GRASSWHISTLE}th{SE_M_REVERSAL}GLITTER\l"
	.string "LIGHTHOUSE$"

OlivineCity_Text_BattleTowerSign:
	.string "TRAINE{SE_M_MINIMIZE}HIL{SE_M_BRICK_BREAK}and\n"
	.string "BATTL{SE_M_SWORDS_DANCE}TENT{SE_M_SKETCH}AHEAD.\p"
	.string "Openin{SE_M_SANDSTORM}Now!$"

OlivineCity_Text_Machoke:
	.string "MACHOKE{SE_M_HEAT_WAVE}CHO!$"

