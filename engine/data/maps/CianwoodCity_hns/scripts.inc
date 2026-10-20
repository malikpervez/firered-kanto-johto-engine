@ Johto (data/maps/CianwoodCity_hns/scripts.inc), as built into the FireRed game.

CianwoodCity_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, CianwoodCity_EventScript_CityEnter
	map_script MAP_SCRIPT_ON_FRAME_TABLE, CianwoodCity_OnFrame
	map_script MAP_SCRIPT_ON_LOAD, CianwoodCity_EventScript_InitializeSuicune
	map_script MAP_SCRIPT_ON_RESUME, J_SetTimeEncounters
	.byte 0

CianwoodCity_RemoveEusine::
	setflag JOHTO_FLAG_HIDE_CIANWOOD_EUSINE
	end

CianwoodCity_OnFrame::
	map_script_2 JOHTO_VAR_GETFLY, 1, CianwoodCity_EventScript_Flytrigger
	.2byte 0

CianwoodCity_EventScript_CityEnter::
	setflag JOHTO_FLAG_VISITED_CIANWOOD_CITY
	callnative SetTimeBasedEncounters
	goto_if_ge JOHTO_VAR_OLIVINE_CITY_STATE, 5, OlivineCity_MapScript_ClearWeather
	end

CianwoodCity_EventScript_InitializeSuicune::
	goto_if_ge JOHTO_VAR_SUICUNE_ENCOUNTERS, 2, CianwoodCity_EventScript_InitializeNothing
	clearflag JOHTO_FLAG_HIDE_CIANWOOD_SUICUNE
	setflag JOHTO_FLAG_HIDE_CIANWOOD_EUSINE
	setvar VAR_TEMP_0, 1
	end

CianwoodCity_EventScript_InitializeNothing::
	setvar VAR_TEMP_0, 1
	end

CianwoodCity_EventScript_Flytrigger::
	lock
	playse SE_PIN
	applymovement LOCALID_CIANWOOD_CHUCKSWIFE, J_Common_Movement_ExclamationMark
	delay 55
	waitmovement LOCALID_CIANWOOD_CHUCKSWIFE
	applymovement LOCALID_CIANWOOD_CHUCKSWIFE, CianwoodCity_Movement_ChucksWife
	waitmovement 0
	msgbox CianwoodCity_Text_ChucksWifeGiveHM, MSGBOX_DEFAULT
	giveitem ITEM_HM_FLY
	msgbox CianwoodCity_Text_ChucksWifeFlySpeech, MSGBOX_DEFAULT
	closemessage
	setvar JOHTO_VAR_GETFLY, 2
	goto_if_eq JOHTO_VAR_TRIGGER_ELM_ROCKET_CALL, 1, Mahoganytown_EventScript_RocketTrigger
	release
	end

CianwoodCity_Movement_ChucksWife:
	walk_left
	walk_left
	walk_up
	walk_left
	face_up
	step_end

CianwoodCity_EventScript_Test::
	lock
	random 2
	call_if_eq VAR_RESULT, 1, J_EventScript_RockSmashHeartscale
	release
	end

CianwoodCity_EventScript_ChucksWife::
	lock
	faceplayer
	checkitem ITEM_HM_FLY
	goto_if_eq VAR_RESULT, TRUE, CianwoodCity_EventScript_ChucksWifeAlreadyHasFly
	msgbox CianwoodCity_Text_ChucksWifeEasierToFly, MSGBOX_DEFAULT
	goto_if_set JOHTO_FLAG_BADGE05_GET, CianwoodCity_EventScript_ChucksWifeGiveFly
	msgbox CianwoodCity_Text_ChucksWifeBeatChuck, MSGBOX_DEFAULT
	closemessage
	release
	end

CianwoodCity_EventScript_ChucksWifeGiveFly::
	msgbox CianwoodCity_Text_ChucksWifeGiveHM, MSGBOX_DEFAULT
	giveitem ITEM_HM_FLY
	msgbox CianwoodCity_Text_ChucksWifeFlySpeech, MSGBOX_DEFAULT
	closemessage
	release
	end

CianwoodCity_EventScript_ChucksWifeAlreadyHasFly::
	msgbox CianwoodCity_Text_ChucksWifeChubby, MSGBOX_DEFAULT
	closemessage
	release
	end

CianwoodCity_Text_ChucksWifeEasierToFly:
	.string "Yo{SE_M_DIVE}crosse{SE_M_WATERFALL}th{SE_M_REVERSAL}se{SE_M_CHARGE}t{SE_M_ATTRACT2}ge{SE_M_SPIT_UP}here?\p"
	.string "Tha{SE_M_SPIT_UP}mus{SE_M_SPIT_UP}hav{SE_M_REVERSAL}bee{SE_M_ATTRACT}hard.\p"
	.string "I{SE_M_SPIT_UP}woul{SE_M_WATERFALL}b{SE_M_REVERSAL}muc{SE_M_TRI_ATTACK}easie{SE_M_SAND_TOMB}i{SE_M_ACID_ARMOR}your\n"
	.string "POKéMO{SE_M_PSYBEAM2}kne{SE_M_TWISTER}ho{SE_M_TWISTER}t{SE_M_ATTRACT2}FLY...$"

CianwoodCity_Text_ChucksWifeBeatChuck:
	.string "Bu{SE_M_SPIT_UP}yo{SE_M_DIVE}can'{SE_M_SPIT_UP}us{SE_M_REVERSAL}FL{SE_M_MOONLIGHT}withou{SE_M_SPIT_UP}this\n"
	.string "city'{SE_M_GRASSWHISTLE}GY{SE_M_GIGA_DRAIN}BADGE.\p"
	.string "I{SE_M_ACID_ARMOR}yo{SE_M_DIVE}bea{SE_M_SPIT_UP}th{SE_M_REVERSAL}GY{SE_M_GIGA_DRAIN}LEADE{SE_M_MINIMIZE}here,\n"
	.string "com{SE_M_REVERSAL}se{SE_M_REVERSAL}me.\p"
	.string "I'l{SE_M_BATON_PASS}hav{SE_M_REVERSAL}{SE_M_CHARGE}nic{SE_M_REVERSAL}gif{SE_M_SPIT_UP}fo{SE_M_SAND_TOMB}you.$"

CianwoodCity_Text_ChucksWifeGiveHM:
	.string "That'{SE_M_GRASSWHISTLE}CIANWOOD'{SE_M_GRASSWHISTLE}GY{SE_M_GIGA_DRAIN}BADGE!\p"
	.string "The{SE_M_ATTRACT}yo{SE_M_DIVE}shoul{SE_M_WATERFALL}tak{SE_M_REVERSAL}thi{SE_M_GRASSWHISTLE}HM.$"

CianwoodCity_Text_ChucksWifeFlySpeech:
	.string "Teac{SE_M_TRI_ATTACK}FL{SE_M_MOONLIGHT}t{SE_M_ATTRACT2}you{SE_M_SAND_TOMB}POKéMON.\p"
	.string "Yo{SE_M_DIVE}wil{SE_M_BATON_PASS}b{SE_M_REVERSAL}abl{SE_M_REVERSAL}t{SE_M_ATTRACT2}FL{SE_M_MOONLIGHT}instantly\n"
	.string "t{SE_M_ATTRACT2}anywher{SE_M_REVERSAL}yo{SE_M_DIVE}hav{SE_M_REVERSAL}visited.$"

CianwoodCity_Text_ChucksWifeChubby:
	.string "M{SE_M_YAWN}husban{SE_M_WATERFALL}los{SE_M_SPIT_UP}t{SE_M_ATTRACT2}you{SE_M_SUPERSONIC}s{SE_M_ATTRACT2}h{SE_M_REVERSAL}needs\n"
	.string "t{SE_M_ATTRACT2}trai{SE_M_ATTRACT}harder.\p"
	.string "That'{SE_M_GRASSWHISTLE}good{SE_M_SUPERSONIC}sinc{SE_M_REVERSAL}h{SE_M_REVERSAL}wa{SE_M_GRASSWHISTLE}getting\n"
	.string "{SE_M_CHARGE}littl{SE_M_REVERSAL}chubby.$"

CianwoodCity_EventScript_Youngster::
	lock
	faceplayer
	msgbox CianwoodCity_Text_Youngster, MSGBOX_DEFAULT
	closemessage
	release
	end

CianwoodCity_Text_Youngster:
	.string "I{SE_M_ACID_ARMOR}yo{SE_M_DIVE}us{SE_M_REVERSAL}FLY{SE_M_SUPERSONIC}yo{SE_M_DIVE}ca{SE_M_ATTRACT}ge{SE_M_SPIT_UP}back\n"
	.string "t{SE_M_ATTRACT2}OLIVIN{SE_M_SWORDS_DANCE}instantly.$"

CianwoodCity_EventScript_PokefanM::
	lock
	faceplayer
	msgbox CianwoodCity_Text_PokefanM, MSGBOX_DEFAULT
	call_if_ge JOHTO_VAR_GOLDENROD_CITY_STATE, 10, BlackTide_CoastalWarning
	closemessage
	release
	end

CianwoodCity_Text_PokefanM:
	.string "Boulder{SE_M_GRASSWHISTLE}t{SE_M_ATTRACT2}th{SE_M_REVERSAL}nort{SE_M_TRI_ATTACK}o{SE_M_ACID_ARMOR}tow{SE_M_ATTRACT}can\n"
	.string "b{SE_M_REVERSAL}crushed.\p"
	.string "The{SE_M_YAWN}ma{SE_M_YAWN}b{SE_M_REVERSAL}hidin{SE_M_SANDSTORM}something.\p"
	.string "You{SE_M_SAND_TOMB}POKéMO{SE_M_PSYBEAM2}coul{SE_M_WATERFALL}us{SE_M_REVERSAL}ROC{SE_M_SNORE}SMASH\n"
	.string "t{SE_M_ATTRACT2}brea{SE_M_ENCORE2}them.$"

CianwoodCity_EventScript_Lass::
	lock
	faceplayer
	msgbox CianwoodCity_Text_Lass, MSGBOX_DEFAULT
	closemessage
	release
	end

CianwoodCity_Text_Lass:
	.string "CHUCK{SE_M_SUPERSONIC}th{SE_M_REVERSAL}GY{SE_M_GIGA_DRAIN}LEADER{SE_M_SUPERSONIC}spar{SE_M_GRASSWHISTLE}with\n"
	.string "hi{SE_M_GRASSWHISTLE}fightin{SE_M_SANDSTORM}POKéMON.$"

CianwoodCity_EventScript_SuicuneTrigger::
	lock
	hidefollower 1
	playmoncry SPECIES_SUICUNE, CRY_MODE_NORMAL
	applymovement LOCALID_CIANWOOD_SUICUNE, CianwoodCity_Movement_Suicune1
	playse SE_LEDGE
	waitse
	playse SE_LEDGE
	waitse
	waitmovement 0
	waitmoncry
	playse SE_PIN
	applymovement OBJ_EVENT_ID_PLAYER, J_Common_Movement_ExclamationMark
	waitmovement OBJ_EVENT_ID_PLAYER
	applymovement LOCALID_CIANWOOD_SUICUNE, CianwoodCity_Movement_Suicune2
	playse SE_LEDGE
	delay 30
	playse SE_LEDGE
	delay 30
	playse SE_LEDGE
	delay 30
	waitmovement 0
	turnobject OBJ_EVENT_ID_PLAYER, DIR_SOUTH
	playmoncry SPECIES_SUICUNE, CRY_MODE_NORMAL
	waitmoncry
	applymovement LOCALID_CIANWOOD_SUICUNE, CianwoodCity_Movement_Suicune3
	playse SE_LEDGE
	delay 30
	playse SE_LEDGE
	delay 30
	playse SE_LEDGE
	delay 30
	playse SE_LEDGE
	delay 30
	playse SE_LEDGE
	delay 30
	waitmovement 0
	delay 30
	playbgm ((558 + 1) + 0x4B), FALSE
	clearflag JOHTO_FLAG_HIDE_CIANWOOD_EUSINE
	addobject LOCALID_CIANWOOD_EUSINE
	applymovement LOCALID_CIANWOOD_EUSINE, CianwoodCity_Movement_Eusine1
	waitmovement 0
	delay 55
	applymovement LOCALID_CIANWOOD_EUSINE, CianwoodCity_Movement_Eusine2
	waitmovement 0
	msgbox CianwoodCity_Text_EusineSuicune, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_JOHTO_EUSINE_HNS, CianwoodCity_Text_EusineBeaten
	playbgm ((558 + 1) + 0x4B), FALSE
	msgbox CianwoodCity_Text_EusineAfter, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_CIANWOOD_EUSINE, CianwoodCity_Movement_Eusine3
	waitmovement 0
	setflag JOHTO_FLAG_HIDE_CIANWOOD_EUSINE
	setflag JOHTO_FLAG_HIDE_CIANWOOD_SUICUNE
	removeobject LOCALID_CIANWOOD_SUICUNE
	removeobject LOCALID_CIANWOOD_EUSINE
	setvar JOHTO_VAR_SUICUNE_ENCOUNTERS, 2
	setvar JOHTO_VAR_CIANWOOD_CITY_STATE, 2
	fadedefaultbgm
	call_if_set JOHTO_FLAG_HIDE_ROUTE42_SUICUNE, CianwoodCity_EventScript_DoneJohtoSuicune
	release
	end

CianwoodCity_EventScript_DoneJohtoSuicune::
	setvar JOHTO_VAR_SUICUNE_ENCOUNTERS, 3
	return

CianwoodCity_Movement_Suicune1:
	jump_in_place_right_left
	jump_in_place_right_left
	face_down
	step_end

CianwoodCity_Movement_Suicune2:
	jump_down
	jump_2_down
	jump_right
	face_up
	step_end

CianwoodCity_Movement_Suicune3:
	jump_2_down
	jump_2_right
	jump_2_right
	jump_2_right
	jump_2_right
	jump_2_right
	step_end

CianwoodCity_Movement_Eusine1:
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	face_right
	step_end

CianwoodCity_Movement_Eusine2:
	face_up
	walk_up
	walk_up
	step_end

CianwoodCity_Movement_Eusine3:
	face_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	step_end

CianwoodCity_Text_EusineSuicune:
	.string "EUSINE{SE_M_HEAT_WAVE}Yo{SE_M_SUPERSONIC}{PLAYER}.\p"
	.string "Wasn'{SE_M_SPIT_UP}tha{SE_M_SPIT_UP}SUICUN{SE_M_SWORDS_DANCE}jus{SE_M_SPIT_UP}now?\p"
	.string "{SE_M_HEAL_BELL}onl{SE_M_YAWN}caugh{SE_M_SPIT_UP}{SE_M_CHARGE}quic{SE_M_ENCORE2}glimpse{SE_M_SUPERSONIC}but\n"
	.string "{SE_M_HEAL_BELL}though{SE_M_SPIT_UP}{SE_M_HEAL_BELL}sa{SE_M_TWISTER}SUICUN{SE_M_SWORDS_DANCE}runnin{SE_M_SANDSTORM}on\l"
	.string "th{SE_M_REVERSAL}waves.\p"
	.string "SUICUN{SE_M_SWORDS_DANCE}i{SE_M_GRASSWHISTLE}beautifu{SE_M_BATON_PASS}an{SE_M_WATERFALL}grand.\p"
	.string "An{SE_M_WATERFALL}i{SE_M_SPIT_UP}race{SE_M_GRASSWHISTLE}throug{SE_M_TRI_ATTACK}town{SE_M_GRASSWHISTLE}and\n"
	.string "road{SE_M_GRASSWHISTLE}a{SE_M_SPIT_UP}simpl{SE_M_YAWN}awesom{SE_M_REVERSAL}speeds.\p"
	.string "It'{SE_M_GRASSWHISTLE}wonderful…\p"
	.string "{SE_M_HEAL_BELL}wan{SE_M_SPIT_UP}t{SE_M_ATTRACT2}se{SE_M_REVERSAL}SUICUN{SE_M_SWORDS_DANCE}u{SE_M_MORNING_SUN}close…\p"
	.string "I'v{SE_M_REVERSAL}decided.\p"
	.string "I'l{SE_M_BATON_PASS}battl{SE_M_REVERSAL}yo{SE_M_DIVE}a{SE_M_GRASSWHISTLE}{SE_M_CHARGE}traine{SE_M_SAND_TOMB}to\n"
	.string "ear{SE_M_ATTRACT}SUICUNE'{SE_M_GRASSWHISTLE}respect!\p"
	.string "Com{SE_M_REVERSAL}on{SE_M_SUPERSONIC}{PLAYER}{SE_M_PERISH_SONG}Let'{SE_M_GRASSWHISTLE}battl{SE_M_REVERSAL}now!$"

CianwoodCity_Text_EusineBeaten:
	.string "{SE_M_HEAL_BELL}hat{SE_M_REVERSAL}t{SE_M_ATTRACT2}admi{SE_M_SPIT_UP}it{SE_M_SUPERSONIC}bu{SE_M_SPIT_UP}yo{SE_M_DIVE}win.$"

CianwoodCity_Text_EusineAfter:
	.string "You'r{SE_M_REVERSAL}amazing{SE_M_SUPERSONIC}{PLAYER}!\p"
	.string "N{SE_M_ATTRACT2}wonde{SE_M_SAND_TOMB}POKéMO{SE_M_PSYBEAM2}gravitat{SE_M_REVERSAL}t{SE_M_ATTRACT2}you.\p"
	.string "{SE_M_HEAL_BELL}ge{SE_M_SPIT_UP}i{SE_M_SPIT_UP}now.\p"
	.string "I'{SE_M_MILK_DRINK}goin{SE_M_SANDSTORM}t{SE_M_ATTRACT2}kee{SE_M_MORNING_SUN}searchin{SE_M_SANDSTORM}for\n"
	.string "SUICUNE.\p"
	.string "I'{SE_M_MILK_DRINK}sur{SE_M_REVERSAL}we'l{SE_M_BATON_PASS}se{SE_M_REVERSAL}eac{SE_M_TRI_ATTACK}othe{SE_M_SAND_TOMB}again.\p"
	.string "Se{SE_M_REVERSAL}yo{SE_M_DIVE}around!$"

CianwoodCity_EventScript_CitySign::
	lock
	msgbox CianwoodCity_Text_Sign, MSGBOX_SIGN
	closemessage
	release
	end

CianwoodCity_Text_Sign:
	.string "CIANWOO{SE_M_FAINT_ATTACK}CITY\p"
	.string "{SE_M_BONEMERANG}Por{SE_M_SPIT_UP}Surrounde{SE_M_WATERFALL}b{SE_M_YAWN}Roug{SE_M_TRI_ATTACK}Seas$"

CianwoodCity_EventScript_GymSign::
	lock
	msgbox CianwoodCity_Text_GymSign, MSGBOX_SIGN
	closemessage
	release
	end

CianwoodCity_Text_GymSign:
	.string "CIANWOO{SE_M_FAINT_ATTACK}CIT{SE_M_MOONLIGHT}POKéMO{SE_M_PSYBEAM2}GYM\p"
	.string "LEADER{SE_M_HEAT_WAVE}CHUCK\p"
	.string "Hi{SE_M_GRASSWHISTLE}Roarin{SE_M_SANDSTORM}Fist{SE_M_GRASSWHISTLE}D{SE_M_ATTRACT2}th{SE_M_REVERSAL}Talking$"

CianwoodCity_EventScript_Pharmacy::
	lock
	msgbox CianwoodCity_Text_PharmacySign, MSGBOX_SIGN
	closemessage
	release
	end

CianwoodCity_Text_PharmacySign:
	.string "50{SE_M_BITE}Year{SE_M_GRASSWHISTLE}o{SE_M_ACID_ARMOR}Tradition\p"
	.string "CIANWOO{SE_M_FAINT_ATTACK}CIT{SE_M_MOONLIGHT}PHARMACY\p"
	.string "W{SE_M_REVERSAL}Awai{SE_M_SPIT_UP}You{SE_M_SAND_TOMB}Medicina{SE_M_BATON_PASS}Queries$"

CianwoodCity_EventScript_CaveSign::
	lock
	msgbox CianwoodCity_Text_Safari, MSGBOX_SIGN
	closemessage
	release
	end

CianwoodCity_EventScript_Engineer::
	lock
	faceplayer
	msgbox CianwoodCity_Text_Engineer, MSGBOX_DEFAULT
	closemessage
	release
	end

CianwoodCity_Text_Safari:
	.string "CLIF{SE_M_LEER}EDG{SE_M_SWORDS_DANCE}CAVE\n"
	.string "Roa{SE_M_WATERFALL}t{SE_M_ATTRACT2}th{SE_M_REVERSAL}SAFAR{SE_M_HEAL_BELL}ZONE.$"

CianwoodCity_Text_Engineer:
	.string "Thi{SE_M_GRASSWHISTLE}pat{SE_M_TRI_ATTACK}i{SE_M_GRASSWHISTLE}unde{SE_M_SAND_TOMB}construction.\n"
	.string "We'r{SE_M_REVERSAL}gettin{SE_M_SANDSTORM}th{SE_M_REVERSAL}ne{SE_M_TWISTER}SAFAR{SE_M_HEAL_BELL}ZONE\l"
	.string "u{SE_M_MORNING_SUN}an{SE_M_WATERFALL}running!$"

