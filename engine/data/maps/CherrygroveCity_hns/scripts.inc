@ Johto (data/maps/CherrygroveCity_hns/scripts.inc), as built into the FireRed game.

CherrygroveCity_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, CherryGroveCity_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, J_SetTimeEncounters
	.byte 0

CherryGroveCity_OnTransition::
	callnative SetTimeBasedEncounters
	end

CherryGroveCity_EventScript_TriggerGent_Top::
	lock
	setflag JOHTO_FLAG_VISITED_CHERRYGROVE_CITY
	setflag JOHTO_FLAG_HIDE_CHERRYGROVE_GUIDE_GENT_HOUSE
	playse SE_PIN
	applymovement LOCALID_GUIDE_GENT, J_Common_Movement_ExclamationMark
	delay 55
	waitmovement LOCALID_GUIDE_GENT
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	msgbox CherrygroveCity_Text_GuideGentIntro, MSGBOX_YESNO
	waitmessage
	goto_if_eq VAR_RESULT, NO, CherryGroveCity_EventScript_TriggerGent_Cancel
	msgbox CherrygroveCity_Text_GuideGentTourStart, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, CherryGroveCity_Movement_Trigger_Top
	waitmovement 0
	applymovement LOCALID_GUIDE_GENT, CherryGroveCity_Movement_Trigger_Gent
	waitmovement 0
	goto CherryGroveCity_EventScript_GentTour
	release
	end

CherryGroveCity_EventScript_TriggerGent_Mid::
	lock
	setflag JOHTO_FLAG_VISITED_CHERRYGROVE_CITY
	setflag JOHTO_FLAG_HIDE_CHERRYGROVE_GUIDE_GENT_HOUSE
	playse SE_PIN
	applymovement LOCALID_GUIDE_GENT, J_Common_Movement_ExclamationMark
	delay 55
	waitmovement LOCALID_GUIDE_GENT
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	msgbox CherrygroveCity_Text_GuideGentIntro, MSGBOX_YESNO
	waitmessage
	goto_if_eq VAR_RESULT, NO, CherryGroveCity_EventScript_TriggerGent_Cancel
	msgbox CherrygroveCity_Text_GuideGentTourStart, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_GUIDE_GENT, CherryGroveCity_Movement_Trigger_Gent
	waitmovement 0
	turnobject OBJ_EVENT_ID_PLAYER, DIR_WEST
	goto CherryGroveCity_EventScript_GentTour
	release
	end

CherryGroveCity_EventScript_TriggerGent_Bottom::
	lock
	setflag JOHTO_FLAG_VISITED_CHERRYGROVE_CITY
	setflag JOHTO_FLAG_HIDE_CHERRYGROVE_GUIDE_GENT_HOUSE
	playse SE_PIN
	applymovement LOCALID_GUIDE_GENT, J_Common_Movement_ExclamationMark
	delay 55
	waitmovement LOCALID_GUIDE_GENT
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	msgbox CherrygroveCity_Text_GuideGentIntro, MSGBOX_YESNO
	waitmessage
	goto_if_eq VAR_RESULT, NO, CherryGroveCity_EventScript_TriggerGent_Cancel
	msgbox CherrygroveCity_Text_GuideGentTourStart, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_GUIDE_GENT, CherryGroveCity_Movement_Trigger_Gent
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, CherryGroveCity_Movement_Trigger_Bottom
	waitmovement 0
	goto CherryGroveCity_EventScript_GentTour
	release
	end

CherryGroveCity_EventScript_TriggerGent_Cancel::
	msgbox CherrygroveCity_Text_GuideGentDecline, MSGBOX_DEFAULT
	closemessage
	setvar JOHTO_VAR_CHERRYGROVE_CITY_STATE, 1
	release
	end

CherryGroveCity_EventScript_GentTour::
	playbgm ((558 + 1) + 0x3A), FALSE
	applymovement LOCALID_GUIDE_GENT, CherryGroveCity_Movement_Pokecenter
	applymovement OBJ_EVENT_ID_PLAYER, CherryGroveCity_Movement_Pokecenter
	waitmovement 0
	waitmovement 0
	msgbox CherrygroveCity_Text_GuideGentPokecenter, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_GUIDE_GENT, CherryGroveCity_Movement_Pokemart
	applymovement OBJ_EVENT_ID_PLAYER, CherryGroveCity_Movement_Pokemart
	waitmovement 0
	waitmovement 0
	msgbox CherrygroveCity_Text_GuideGentMart, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_GUIDE_GENT, CherryGroveCity_Movement_Route30
	applymovement OBJ_EVENT_ID_PLAYER, CherryGroveCity_Movement_Route30
	waitmovement 0
	waitmovement 0
	msgbox CherrygroveCity_Text_GuideGentRoute30, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_GUIDE_GENT, CherryGroveCity_Movement_Sea
	applymovement OBJ_EVENT_ID_PLAYER, CherryGroveCity_Movement_Sea
	waitmovement 0
	waitmovement 0
	msgbox CherrygroveCity_Text_GuideGentSea, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_GUIDE_GENT, CherryGroveCity_Movement_House_Gent
	applymovement OBJ_EVENT_ID_PLAYER, CherryGroveCity_Movement_House_Player
	waitmovement 0
	waitmovement 0
	delay 20
	msgbox CherrygroveCity_Text_GuideGentMap, MSGBOX_DEFAULT
	closemessage

	applymovement LOCALID_GUIDE_GENT, CherryGroveCity_Movement_Gent_Leave
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	delay 20
	opendoor 42, 14
	waitdooranim
	waitmovement 0
	removeobject LOCALID_GUIDE_GENT
	closedoor 42, 14
	waitdooranim

	clearflag JOHTO_FLAG_HIDE_CHERRYGROVE_GUIDE_GENT_HOUSE
	setflag JOHTO_FLAG_HIDE_GUIDE_GENT_CHERRYGROVE
	setvar JOHTO_VAR_CHERRYGROVE_CITY_STATE, 1
	fadedefaultbgm
	release
	end

CherryGroveCity_EventScript_Fisherman::
	lock
	faceplayer
	goto_if_set JOHTO_FLAG_GOT_MYSTICWATER, CherryGroveCity_EventScript_Fisherman2
	msgbox CherrygroveCity_Text_MysticWaterGuyBefore, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, CherryGroveCity_EventScript_Fisherman2
	giveitem ITEM_MYSTIC_WATER
	goto_if_eq VAR_RESULT, FALSE, J_Common_EventScript_ShowBagIsFull
	closemessage
	setflag JOHTO_FLAG_GOT_MYSTICWATER
	release
	end

CherryGroveCity_EventScript_Fisherman2::
	msgbox CherrygroveCity_Text_MysticWaterGuyAfter, MSGBOX_DEFAULT
	closemessage
	release
	end

CherryGroveCity_EventScript_Lass::
	lock
	faceplayer
	msgbox CherrygroveCity_Text_TeacherHaveMapCard, MSGBOX_DEFAULT
	closemessage
	release
	end

CherryGroveCity_EventScript_Boy::
	lock
	faceplayer
	goto_if_set FLAG_SYS_POKEDEX_GET, CherryGroveCity_EventScript_Boy2
	msgbox CherrygroveCity_Text_YoungsterNoPokedex, MSGBOX_DEFAULT
	closemessage
	release
	end

CherryGroveCity_EventScript_Boy2::
	msgbox CherrygroveCity_Text_YoungsterHavePokedex, MSGBOX_DEFAULT
	closemessage
	release
	end

CherryGroveCity_EventScript_Staryu::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_STARYU, CRY_MODE_NORMAL
	msgbox CherryGroveCity_Text_Staryu, MSGBOX_DEFAULT
	waitmoncry
	release
	end

CherryGroveCity_EventScript_Corsola::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_CORSOLA, CRY_MODE_NORMAL
	msgbox CherryGroveCity_Text_Corsola, MSGBOX_DEFAULT
	waitmoncry
	release
	end

CherryGroveCity_EventScript_Krabby::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_KRABBY, CRY_MODE_NORMAL
	msgbox CherryGroveCity_Text_Krabby, MSGBOX_DEFAULT
	waitmoncry
	release
	end

CherryGroveCity_EventScript_Sign::
	lock
	msgbox CherrygroveCity_Text_CitySign, MSGBOX_SIGN
	closemessage
	release
	end

CherryGroveCity_EventScript_TriggerSilver_Top::
	lock
	applymovement OBJ_EVENT_ID_PLAYER, CherryGroveCity_Movement_Trigger_Silver_Top
	waitmovement 0
	goto CherryGroveCity_EventScript_TriggerSilver
	end

CherryGroveCity_EventScript_TriggerSilver_Bottom::
	lock
	applymovement OBJ_EVENT_ID_PLAYER, CherryGroveCity_Movement_Trigger_Silver_Bottom
	waitmovement 0
	goto CherryGroveCity_EventScript_TriggerSilver
	end

CherryGroveCity_EventScript_TriggerSilver::
	lock
	playbgm ((558 + 1) + 0x3B), FALSE
	applymovement LOCALID_CHERRYGROVE_SILVER, CherryGroveCity_Movement_Silver_Enter
	waitmovement 0
	msgbox CherrygroveCity_Text_RivalSeen, MSGBOX_DEFAULT
	closemessage
	goto_if_eq JOHTO_VAR_STARTER_MON, 0, CherryGroveCity_Silver_Battle_Cyndaquil
	goto_if_eq JOHTO_VAR_STARTER_MON, 1, CherryGroveCity_Silver_Battle_Totodile
	goto_if_eq JOHTO_VAR_STARTER_MON, 2, CherryGroveCity_Silver_Battle_Chikorita
	release
	end

CherryGroveCity_Silver_Battle_Cyndaquil::
	trainerbattle_no_intro TRAINER_JOHTO_RIVAL_CYNDAQUIL_1_HNS, CherrygroveCity_Text_SilverWin
	goto CherryGroveCity_Silver_AfterBattle

CherryGroveCity_Silver_Battle_Totodile::
	trainerbattle_no_intro TRAINER_JOHTO_RIVAL_TOTODILE_1_HNS, CherrygroveCity_Text_SilverWin
	goto CherryGroveCity_Silver_AfterBattle

CherryGroveCity_Silver_Battle_Chikorita::
	trainerbattle_no_intro TRAINER_JOHTO_RIVAL_CHIKORITA_1_HNS, CherrygroveCity_Text_SilverWin
	goto CherryGroveCity_Silver_AfterBattle

CherryGroveCity_Silver_AfterBattle::
	playbgm ((558 + 1) + 0x3C), FALSE
	msgbox CherrygroveCity_Text_RivalAfter, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, CherryGroveCity_Movement_Silver_Leave1Player
	applymovement LOCALID_CHERRYGROVE_SILVER, CherryGroveCity_Movement_Silver_Leave1
	waitmovement 0
	waitmovement 0
	playse SE_PIN
	applymovement LOCALID_CHERRYGROVE_SILVER, J_Common_Movement_ExclamationMark
	delay 55
	waitmovement LOCALID_CHERRYGROVE_SILVER
	turnobject LOCALID_CHERRYGROVE_SILVER, DIR_EAST
	delay 60
	turnobject LOCALID_CHERRYGROVE_SILVER, DIR_SOUTH
	delay 30
	applymovement LOCALID_CHERRYGROVE_SILVER, CherryGroveCity_Movement_Silver_Return
	waitmovement 0
	msgbox CherrygroveCity_Text_RivalID, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_CHERRYGROVE_SILVER, CherryGroveCity_Movement_Silver_Leave2
	waitmovement 0
	removeobject LOCALID_CHERRYGROVE_SILVER
	setflag JOHTO_FLAG_HIDE_SILVER_CHERRYGROVE
	setvar JOHTO_VAR_CHERRYGROVE_CITY_STATE, 4
	fadedefaultbgm
	release
	end

CherrygroveCity_Text_GuideGentIntro:
	.string "Welcome{SE_M_DRAGON_RAGE}You'r{SE_M_REVERSAL}ne{SE_M_TWISTER}to\nCHERRYGROVE{SE_M_SUPERSONIC}aren'{SE_M_SPIT_UP}you?\p{SE_M_HEAL_BELL}ca{SE_M_ATTRACT}sho{SE_M_TWISTER}yo{SE_M_DIVE}aroun{SE_M_WATERFALL}town\nbefor{SE_M_REVERSAL}yo{SE_M_DIVE}continu{SE_M_REVERSAL}you{SE_M_SAND_TOMB}journey.$"

CherrygroveCity_Text_GuideGentTourStart:
	.string "OK{SE_M_SUPERSONIC}then!\n"
	.string "Follo{SE_M_TWISTER}me!$"

CherrygroveCity_Text_GuideGentPokecenter:
	.string "Here'{SE_M_GRASSWHISTLE}CHERRYGROVE's\nPOKéMO{SE_M_PSYBEAM2}CENTER.\pYou{SE_M_SAND_TOMB}tea{SE_M_MILK_DRINK}ca{SE_M_ATTRACT}res{SE_M_SPIT_UP}her{SE_M_REVERSAL}between\ntrips{SE_M_SUPERSONIC}jus{SE_M_SPIT_UP}a{SE_M_GRASSWHISTLE}i{SE_M_SPIT_UP}di{SE_M_WATERFALL}i{SE_M_ATTRACT}KANTO.$"

CherrygroveCity_Text_GuideGentMart:
	.string "Thi{SE_M_GRASSWHISTLE}i{SE_M_GRASSWHISTLE}{SE_M_CHARGE}POKéMO{SE_M_PSYBEAM2}MART.\p"
	.string "The{SE_M_YAWN}sel{SE_M_BATON_PASS}BALL{SE_M_SKETCH}fo{SE_M_SAND_TOMB}catchin{SE_M_SANDSTORM}wild\n"
	.string "POKéMO{SE_M_PSYBEAM2}an{SE_M_WATERFALL}othe{SE_M_SAND_TOMB}usefu{SE_M_BATON_PASS}items.$"

CherrygroveCity_Text_GuideGentRoute30:
	.string "ROUT{SE_M_SWORDS_DANCE}3{SE_M_BITE}i{SE_M_GRASSWHISTLE}ou{SE_M_SPIT_UP}thi{SE_M_GRASSWHISTLE}way.\p"
	.string "Trainer{SE_M_GRASSWHISTLE}wil{SE_M_BATON_PASS}b{SE_M_REVERSAL}battling\n"
	.string "thei{SE_M_SAND_TOMB}prize{SE_M_WATERFALL}POKéMO{SE_M_PSYBEAM2}there.$"

CherrygroveCity_Text_GuideGentSea:
	.string "Thi{SE_M_GRASSWHISTLE}i{SE_M_GRASSWHISTLE}th{SE_M_REVERSAL}sea{SE_M_SUPERSONIC}a{SE_M_GRASSWHISTLE}yo{SE_M_DIVE}ca{SE_M_ATTRACT}see.\p"
	.string "Som{SE_M_REVERSAL}POKéMO{SE_M_PSYBEAM2}ar{SE_M_REVERSAL}foun{SE_M_WATERFALL}onl{SE_M_YAWN}in\n"
	.string "i{SE_M_ATTRACT}water.$"

CherrygroveCity_Text_GuideGentMap:
	.string "Here…\p"
	.string "It'{SE_M_GRASSWHISTLE}m{SE_M_YAWN}house{SE_M_DRAGON_RAGE}Thank{SE_M_GRASSWHISTLE}for\n"
	.string "you{SE_M_SAND_TOMB}company.\p"
	.string "Oh{SE_M_SUPERSONIC}an{SE_M_WATERFALL}i{SE_M_ACID_ARMOR}you'r{SE_M_REVERSAL}eve{SE_M_SAND_TOMB}lost{SE_M_SUPERSONIC}check\n"
	.string "th{SE_M_REVERSAL}MA{SE_M_PETAL_DANCE}o{SE_M_ATTRACT}you{SE_M_SAND_TOMB}POKéGEAR!\p"
	.string "{SE_M_HEAL_BELL}wis{SE_M_TRI_ATTACK}yo{SE_M_DIVE}luc{SE_M_ENCORE2}o{SE_M_ATTRACT}you{SE_M_SAND_TOMB}journey!$"

CherrygroveCity_Text_GuideGentDecline:
	.string "Oh{SE_M_DIZZY_PUNCH}It'{SE_M_GRASSWHISTLE}somethin{SE_M_SANDSTORM}{SE_M_HEAL_BELL}enjoy\n"
	.string "doing…\p"
	.string "Fine{SE_M_PERISH_SONG}Com{SE_M_REVERSAL}se{SE_M_REVERSAL}m{SE_M_REVERSAL}whenever\n"
	.string "yo{SE_M_DIVE}like.$"

CherrygroveCity_Text_RivalSeen:
	.string "S{SE_M_ATTRACT2}you'r{SE_M_REVERSAL}{PLAYER}{SE_M_SUPERSONIC}the\nKANT{SE_M_SOLAR_BEAM}CHAMPION.\p{SE_M_BONEMERANG}titl{SE_M_REVERSAL}doesn'{SE_M_SPIT_UP}mak{SE_M_REVERSAL}yo{SE_M_DIVE}strong.\pI'v{SE_M_REVERSAL}go{SE_M_SPIT_UP}{SE_M_CHARGE}powerfu{SE_M_BATON_PASS}POKéMON.\nI'l{SE_M_BATON_PASS}sho{SE_M_TWISTER}yo{SE_M_DIVE}wha{SE_M_SPIT_UP}{SE_M_HEAL_BELL}mean!$"

CherrygroveCity_Text_SilverWin:
	.string "Humph{SE_M_PERISH_SONG}Ar{SE_M_REVERSAL}yo{SE_M_DIVE}happ{SE_M_YAWN}yo{SE_M_DIVE}won?$"

CherrygroveCity_Text_RivalAfter:
	.string "{SE_M_DIZZY_PUNCH}{SE_M_DIZZY_PUNCH}{SE_M_DIZZY_PUNCH}{SE_M_DIZZY_PUNCH}{SE_M_DIZZY_PUNCH}{SE_M_DIZZY_PUNCH}{SE_M_DIZZY_PUNCH}…\p"
	.string "D{SE_M_ATTRACT2}yo{SE_M_DIVE}wan{SE_M_SPIT_UP}t{SE_M_ATTRACT2}kno{SE_M_TWISTER}wh{SE_M_ATTRACT2}{SE_M_HEAL_BELL}am?\p"
	.string "I'{SE_M_MILK_DRINK}goin{SE_M_SANDSTORM}t{SE_M_ATTRACT2}b{SE_M_REVERSAL}th{SE_M_REVERSAL}world's\n"
	.string "greates{SE_M_SPIT_UP}POKéMO{SE_M_PSYBEAM2}trainer.$"

CherrygroveCity_Text_RivalID:
	.string "Giv{SE_M_REVERSAL}i{SE_M_SPIT_UP}back!\n"
	.string "That'{SE_M_GRASSWHISTLE}m{SE_M_YAWN}TRAINE{SE_M_MINIMIZE}CARD!\p"
	.string "O{SE_M_TRI_ATTACK}no!\n"
	.string "Yo{SE_M_DIVE}sa{SE_M_TWISTER}m{SE_M_YAWN}name...$"

CherrygroveCity_Text_TeacherHaveMapCard:
	.string "Whe{SE_M_ATTRACT}you'r{SE_M_REVERSAL}wit{SE_M_TRI_ATTACK}POKéMON,\n"
	.string "goin{SE_M_SANDSTORM}anywher{SE_M_REVERSAL}i{SE_M_GRASSWHISTLE}fun.$"

CherrygroveCity_Text_YoungsterNoPokedex:
	.string "MR{SE_M_PERISH_SONG}POKéMON'{SE_M_GRASSWHISTLE}hous{SE_M_REVERSAL}i{SE_M_GRASSWHISTLE}still\n"
	.string "farthe{SE_M_SAND_TOMB}u{SE_M_MORNING_SUN}ahead.$"

CherrygroveCity_Text_YoungsterHavePokedex:
	.string "{SE_M_HEAL_BELL}battle{SE_M_WATERFALL}th{SE_M_REVERSAL}trainer{SE_M_GRASSWHISTLE}o{SE_M_ATTRACT}the\n"
	.string "road.\p"
	.string "M{SE_M_YAWN}POKéMO{SE_M_PSYBEAM2}lost{SE_M_PERISH_SONG}They'r{SE_M_REVERSAL}a\n"
	.string "mess{SE_M_DRAGON_RAGE}{SE_M_HEAL_BELL}mus{SE_M_SPIT_UP}tak{SE_M_REVERSAL}the{SE_M_MILK_DRINK}t{SE_M_ATTRACT2}a\l"
	.string "POKéMO{SE_M_PSYBEAM2}CENTER.$"

CherrygroveCity_Text_MysticWaterGuyBefore:
	.string "{SE_M_BONEMERANG}POKéMO{SE_M_PSYBEAM2}{SE_M_HEAL_BELL}caugh{SE_M_SPIT_UP}ha{SE_M_WATERFALL}an\n"
	.string "item.\p"
	.string "{SE_M_HEAL_BELL}thin{SE_M_ENCORE2}it'{SE_M_GRASSWHISTLE}MYSTI{SE_M_PSYBEAM}WATER.\p"
	.string "{SE_M_HEAL_BELL}don'{SE_M_SPIT_UP}nee{SE_M_WATERFALL}it{SE_M_SUPERSONIC}s{SE_M_ATTRACT2}d{SE_M_ATTRACT2}you\n"
	.string "wan{SE_M_SPIT_UP}it?$"

CherrygroveCity_Text_MysticWaterGuyAfter:
	.string "Bac{SE_M_ENCORE2}t{SE_M_ATTRACT2}fishin{SE_M_SANDSTORM}fo{SE_M_SAND_TOMB}me{SE_M_SUPERSONIC}then.$"

CherrygroveCity_Text_CitySign:
	.string "CHERRYGROV{SE_M_SWORDS_DANCE}CITY\p"
	.string "Th{SE_M_REVERSAL}Cit{SE_M_YAWN}o{SE_M_ACID_ARMOR}Cute{SE_M_SUPERSONIC}Fragrant\n"
	.string "Flowers$"

CherrygroveCity_Text_GuideGentsHouseSign:
	.string "GUID{SE_M_SWORDS_DANCE}GENT'{SE_M_SKETCH}HOUSE$"

CherryGroveCity_Text_Staryu:
	.string "STARYU{SE_M_HEAT_WAVE}Yuuuuuuuu.$"

CherryGroveCity_Text_Corsola:
	.string "CORSOLA{SE_M_HEAT_WAVE}Corsola{SE_M_DRAGON_RAGE}La!$"

CherryGroveCity_Text_Krabby:
	.string "KRABBY{SE_M_HEAT_WAVE}KOOOOKEEE!$"

CherryGroveCity_Movement_Trigger_Gent:
	walk_down
	walk_left
	walk_down
	face_left
	step_end

CherryGroveCity_Movement_Trigger_Top:
	walk_down
	face_up
	step_end

CherryGroveCity_Movement_Trigger_Bottom:
	walk_up
	face_up
	step_end

CherryGroveCity_Movement_Pokecenter:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_up
	step_end

CherryGroveCity_Movement_Pokemart:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	face_up
	step_end

CherryGroveCity_Movement_Route30:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_up
	walk_up
	step_end

CherryGroveCity_Movement_Sea:
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_down
	walk_down
	walk_down
	walk_down
	walk_left
	step_end

CherryGroveCity_Movement_House_Gent:
	walk_down
	walk_right
	walk_down
	walk_down
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
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	face_up
	step_end

CherryGroveCity_Movement_House_Player:
	delay_16
	delay_16
	walk_down
	walk_down
	walk_down
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
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	face_up
	step_end

CherryGroveCity_Movement_Gent_Leave:
	walk_up
	walk_up
	step_end

CherryGroveCity_Movement_Trigger_Silver_Top:
	walk_down
	face_right
	step_end

CherryGroveCity_Movement_Trigger_Silver_Bottom:
	walk_up
	face_right
	step_end

CherryGroveCity_Movement_Silver_Enter:
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	step_end

CherryGroveCity_Movement_Silver_Leave1:
	delay_16
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	step_end

CherryGroveCity_Movement_Silver_Leave1Player:
	lock_facing_direction
	walk_fast_down
	unlock_facing_direction
	face_up
	step_end

CherryGroveCity_Movement_Silver_Return:
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	face_down
	step_end

CherryGroveCity_Movement_Silver_Leave2:
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	step_end

