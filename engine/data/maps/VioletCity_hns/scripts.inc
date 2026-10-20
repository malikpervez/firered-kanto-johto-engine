@ Johto (data/maps/VioletCity_hns/scripts.inc), as built into the FireRed game.

VioletCity_hns_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, VioletCity_OnFrame
	map_script MAP_SCRIPT_ON_TRANSITION, VioletCity_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, J_SetTimeEncounters
	.byte 0

VioletCity_OnFrame::
	map_script_2 JOHTO_VAR_VIOLET_CITY_KIMONO_GIRL, 1, VioletCity_EventScript_Kimono_Girl
	map_script_2 JOHTO_VAR_VIOLET_CITY_STATE, 3, VioletCity_EventScript_ElmCall_Trigger
	.2byte 0

VioletCity_OnTransition::
	callnative SetTimeBasedEncounters
	end

VioletCity_EventScript_Trigger::

	clearflag JOHTO_FLAG_RECEIVED_TOGEPI_EGG
	clearflag JOHTO_FLAG_VIOLET_NPC_TRADE_COMPLETED
	clearflag JOHTO_FLAG_HIDE_SPROUT_TOWER_SILVER
	clearflag JOHTO_FLAG_HIDE_JOHTO_GYM_LEADERS
	clearflag JOHTO_FLAG_HOOH_BROUGHT
	clearflag JOHTO_FLAG_OMANYTE_BROUGHT
	clearflag JOHTO_FLAG_AERODACTYL_BROUGHT
	clearflag JOHTO_FLAG_KABUTO_BROUGHT
	clearflag JOHTO_FLAG_HIDE_SUDOWOODO
	clearflag JOHTO_FLAG_GOT_HARD_STONE
	clearflag JOHTO_FLAG_GOT_POISON_BARB
	clearflag JOHTO_FLAG_HIDE_UNION_CAVE_LAPRAS
	clearflag JOHTO_FLAG_GOT_BLACK_GLASSES

	setvar JOHTO_VAR_SLOWPOKE_TAIL, 0
	setvar JOHTO_VAR_VIOLET_CITY_KIMONO_GIRL, 0
	setvar JOHTO_VAR_RUINSOFALPH_STATE, 0

	setflag JOHTO_FLAG_ITEM_GS_BALL
	setflag JOHTO_FLAG_ITEM_DOME_FOSSIL
	setflag JOHTO_FLAG_ITEM_HELIX_FOSSIL
	setflag JOHTO_FLAG_ITEM_OLD_AMBER
	setflag JOHTO_FLAG_HIDE_TRAINER_SCHOOL_EARL
	setflag JOHTO_FLAG_HIDE_VIOLET_CITY_AIDE
	setflag JOHTO_FLAG_VISITED_VIOLET_CITY
	setflag JOHTO_FLAG_HIDE_VIOLET_CITY_KIMONO_GIRL

	setvar JOHTO_VAR_SPROUT_TOWER, 0
	setvar JOHTO_VAR_VIOLET_CITY_STATE, 1
	end

VioletCity_EventScript_Earl::
	lock
	faceplayer
	applymovement LOCALID_VIOLETCITY_EARL, VioletCity_Movement_Earl_Spin
	waitmovement 0
	faceplayer
	msgbox VioletCity_Text_EarlAsksIfYouBeatFalkner, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, VioletCity_EventScript_EarlTrainerSchool
	msgbox VioletCity_Text_VeryNiceIndeed, MSGBOX_DEFAULT
	closemessage
	release
	end

VioletCity_EventScript_EarlTrainerSchool::
	msgbox VioletCity_Text_FollowEarl, MSGBOX_DEFAULT
	closemessage
	playbgm ((558 + 1) + 0x3A), FALSE
	switch VAR_FACING
	case DIR_NORTH, VioletCity_EventScript_EarlTrainerSchoolSouth
	case DIR_WEST, VioletCity_EventScript_EarlTrainerSchoolEast
	release
	end

VioletCity_EventScript_EarlTrainerSchoolSouth::
	applymovement LOCALID_VIOLETCITY_EARL, VioletCity_Movement_Earl_South_Adjustment
	waitmovement 0
	applymovement LOCALID_VIOLETCITY_EARL, VioletCity_Movement_Earl_Spin
	applymovement OBJ_EVENT_ID_PLAYER, VioletCity_Movement_Player_South_Adjustment
	waitmovement 0
	waitmovement 0
	goto VioletCity_EventScript_EarlTrainerSchoolTransition
	release
	end

VioletCity_EventScript_EarlTrainerSchoolEast::
	applymovement LOCALID_VIOLETCITY_EARL, VioletCity_Movement_Earl_East_Adjustment
	applymovement OBJ_EVENT_ID_PLAYER, VioletCity_Movement_Player_East_Adjustment
	waitmovement 0
	waitmovement 0
	goto VioletCity_EventScript_EarlTrainerSchoolTransition
	release
	end

VioletCity_EventScript_EarlTrainerSchoolTransition:
	applymovement LOCALID_VIOLETCITY_EARL, VioletCity_Movement_Walk_To_School
	applymovement OBJ_EVENT_ID_PLAYER, VioletCity_Movement_Walk_To_School
	waitmovement 0
	waitmovement 0
	applymovement LOCALID_VIOLETCITY_EARL, VioletCity_Movement_Earl_Spin
	waitmovement 0
	turnobject LOCALID_VIOLETCITY_EARL, DIR_WEST
	msgbox VioletCity_Text_HereTeacherIAm, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_VIOLETCITY_EARL, VioletCity_Movement_Earl_Walk_Inside
	delay 20
	opendoor 39, 36
	waitdooranim
	waitmovement 0
	setflag JOHTO_FLAG_HIDE_VIOLET_CITY_EARL
	removeobject LOCALID_VIOLETCITY_EARL
	closedoor 39, 36
	waitdooranim
	clearflag JOHTO_FLAG_HIDE_TRAINER_SCHOOL_EARL
	fadedefaultbgm
	release
	end

VioletCity_EventScript_Youngster::
	lock
	faceplayer
	msgbox VioletCity_Text_Youngster, MSGBOX_DEFAULT
	closemessage
	release
	end

VioletCity_EventScript_Boy::
	lock
	faceplayer
	msgbox VioletCity_Text_Boy, MSGBOX_DEFAULT
	closemessage
	release
	end

VioletCity_EventScript_Gramps::
	lock
	faceplayer
	msgbox VioletCity_Text_Gramps, MSGBOX_DEFAULT
	closemessage
	release
	end

VioletCity_EventScript_Lass::
	lock
	faceplayer
	msgbox VioletCity_Text_Lass, MSGBOX_DEFAULT
	closemessage
	release
	end

VioletCity_EventScript_Pichu::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_PICHU, CRY_MODE_NORMAL
	msgbox VioletCity_Text_Pichu, MSGBOX_DEFAULT
	waitmoncry
	release
	end

VioletCity_EventScript_Bellsprout::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_BELLSPROUT, CRY_MODE_NORMAL
	msgbox VioletCity_Text_Bellsprout, MSGBOX_DEFAULT
	waitmoncry
	release
	end

VioletCity_EventScript_Rattata::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_RATTATA, CRY_MODE_NORMAL
	msgbox VioletCity_Text_Rattata, MSGBOX_DEFAULT
	waitmoncry
	release
	end

VioletCity_EventScript_ElmCall_Trigger::
	lock
	setspeaker VioletCity_Text_ElmName
	pokenavcall VioletCity_Text_Elm_Call
	waitmessage
	delay 30
	clearflag JOHTO_FLAG_HIDE_VIOLET_CITY_AIDE
	setflag JOHTO_FLAG_HIDE_NEWBARKTOWN_LAB_AIDE
	setvar JOHTO_VAR_VIOLET_CITY_STATE, 4
	release
	end

VioletCity_EventScript_Kimono_Girl::
	lock
	playbgm ((558 + 1) + 0x85), FALSE
	playse SE_PIN
	applymovement LOCALID_VIOLET_KIMONO, J_Common_Movement_ExclamationMark
	delay 55
	waitmovement LOCALID_VIOLET_KIMONO
	applymovement LOCALID_VIOLET_KIMONO, VioletCity_Movement_Kimono_Girl_1
	waitmovement 0
	msgbox VioletCity_Text_Kimono_Girl1, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_VIOLET_KIMONO, VioletCity_Movement_Kimono_Girl_2
	waitmovement 0
	msgbox VioletCity_Text_Kimono_Girl2, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_VIOLET_KIMONO, VioletCity_Movement_Kimono_Girl_3
	waitmovement 0
	msgbox VioletCity_Text_Kimono_Girl3, MSGBOX_DEFAULT
	closemessage
	playse SE_M_PETAL_DANCE
	applymovement LOCALID_VIOLET_KIMONO, VioletCity_Movement_Kimono_Girl_4
	waitmovement 0
	msgbox VioletCity_Text_Kimono_Girl4, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_VIOLET_KIMONO, VioletCity_Movement_Kimono_Girl_5
	waitmovement 0
	fadedefaultbgm
	setvar JOHTO_VAR_VIOLET_CITY_KIMONO_GIRL, 2
	setflag JOHTO_FLAG_HIDE_VIOLET_CITY_KIMONO_GIRL
	removeobject LOCALID_VIOLET_KIMONO
	release
	end

VioletCity_EventScript_ItemRareCandy::
	finditem ITEM_RARE_CANDY
	end

VioletCity_EventScript_ItemPechaBerry::
	finditem ITEM_PECHA_BERRY
	end

VioletCity_EventScript_ItemHyperPotion::
	finditem ITEM_HYPER_POTION
	end

VioletCity_Movement_Earl_Spin:
	face_down
	face_right
	face_up
	face_left
	face_down
	face_right
	face_up
	face_left
	face_down
	face_right
	face_up
	face_left
	face_down
	step_end

VioletCity_Movement_Earl_East_Adjustment:
	walk_down
	walk_down
	walk_down
	walk_right
	step_end

VioletCity_Movement_Player_East_Adjustment:
	walk_down
	walk_down
	walk_left
	walk_down
	face_right
	step_end

VioletCity_Movement_Earl_South_Adjustment:
	walk_right
	walk_down
	walk_down
	walk_down
	face_right
	step_end

VioletCity_Movement_Player_South_Adjustment:
	walk_down
	walk_down
	step_end

VioletCity_Movement_Walk_To_School:
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	step_end

VioletCity_Movement_Walk_To_School_Player:
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
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

VioletCity_Movement_Earl_Walk_Inside:
	walk_up
	walk_up
	step_end

VioletCity_Movement_Kimono_Girl_1:
	walk_left
	walk_left
	walk_left
	walk_left
	face_up
	step_end

VioletCity_Movement_Kimono_Girl_2:
	walk_up
	step_end

VioletCity_Movement_Kimono_Girl_3:
	lock_facing_direction
	walk_down
	unlock_facing_direction
	step_end

VioletCity_Movement_Kimono_Girl_4:
	face_right
	delay_8
	face_down
	delay_8
	face_left
	delay_8
	face_up
	delay_8
	face_right
	delay_8
	face_down
	delay_8
	face_left
	delay_8
	face_up
	delay_8
	step_end

VioletCity_Movement_Kimono_Girl_5:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

VioletCity_EventScript_LiquidJustice::
	msgbox VioletCity_Text_LiquidJustice, MSGBOX_NPC
	end

VioletCity_EventScript_GymSign::
	msgbox VioletCity_Text_GymSign, MSGBOX_SIGN
	end

VioletCity_Text_LiquidJustice:
	.string "Loo{SE_M_ENCORE2}around!\p"
	.string "It'{SE_M_GRASSWHISTLE}eas{SE_M_YAWN}t{SE_M_ATTRACT2}se{SE_M_REVERSAL}wha{SE_M_SPIT_UP}POKéMON\n"
	.string "yo{SE_M_DIVE}ca{SE_M_ATTRACT}catc{SE_M_TRI_ATTACK}i{SE_M_ATTRACT}a{SE_M_ATTRACT}are{SE_M_CHARGE}without\l"
	.string "havin{SE_M_SANDSTORM}t{SE_M_ATTRACT2}ru{SE_M_ATTRACT}aroun{SE_M_WATERFALL}i{SE_M_ATTRACT}tall\l"
	.string "gras{SE_M_GRASSWHISTLE}al{SE_M_BATON_PASS}day!$"

VioletCity_Text_EarlAsksIfYouBeatFalkner:
	.string "Hello!\n"
	.string "Yo{SE_M_DIVE}ar{SE_M_REVERSAL}trainer?\p"
	.string "Battl{SE_M_REVERSAL}GY{SE_M_GIGA_DRAIN}LEADER,\n"
	.string "wi{SE_M_ATTRACT}yo{SE_M_DIVE}did?$"

VioletCity_Text_VeryNiceIndeed:
	.string "Ooh{SE_M_SUPERSONIC}l{SE_M_CHARGE}la!\n"
	.string "Ver{SE_M_YAWN}indee{SE_M_WATERFALL}nice!$"

VioletCity_Text_FollowEarl:
	.string "I{SE_M_GRASSWHISTLE}tha{SE_M_SPIT_UP}so{SE_M_SING}The{SE_M_ATTRACT}stud{SE_M_YAWN}shall\n"
	.string "you{SE_M_DRAGON_RAGE}Follo{SE_M_TWISTER}me!$"

VioletCity_Text_HereTeacherIAm:
	.string "Here{SE_M_SUPERSONIC}teache{SE_M_SAND_TOMB}{SE_M_HEAL_BELL}am.\n"
	.string "Goo{SE_M_WATERFALL}i{SE_M_SPIT_UP}i{SE_M_GRASSWHISTLE}yo{SE_M_DIVE}stud{SE_M_YAWN}here!$"

VioletCity_Text_Lass:
	.string "Ghost{SE_M_GRASSWHISTLE}ar{SE_M_REVERSAL}rumore{SE_M_WATERFALL}t{SE_M_ATTRACT2}appear\n"
	.string "i{SE_M_ATTRACT}SPROU{SE_M_SWIFT}TOWER.\p"
	.string "The{SE_M_YAWN}sa{SE_M_YAWN}tha{SE_M_SPIT_UP}GHOST-type\n"
	.string "move{SE_M_GRASSWHISTLE}ca{SE_M_ATTRACT}bypas{SE_M_GRASSWHISTLE}th{SE_M_REVERSAL}defenses\p"
	.string "o{SE_M_ACID_ARMOR}toug{SE_M_TRI_ATTACK}POKéMO{SE_M_PSYBEAM2}lik{SE_M_REVERSAL}ONIX\n"
	.string "an{SE_M_WATERFALL}GEODUDE.$"

VioletCity_Text_Boy:
	.string "Hey{SE_M_SUPERSONIC}you'r{SE_M_REVERSAL}{SE_M_CHARGE}POKéMO{SE_M_PSYBEAM2}trainer?\p"
	.string "I{SE_M_ACID_ARMOR}yo{SE_M_DIVE}hea{SE_M_WATERFALL}t{SE_M_ATTRACT2}th{SE_M_REVERSAL}ACADEMY,\n"
	.string "yo{SE_M_DIVE}migh{SE_M_SPIT_UP}lear{SE_M_ATTRACT}somethin{SE_M_SANDSTORM}new!$"

VioletCity_Text_Gramps:
	.string "FALKNER{SE_M_SUPERSONIC}fro{SE_M_MILK_DRINK}th{SE_M_REVERSAL}VIOLET\n"
	.string "POKéMO{SE_M_PSYBEAM2}GYM{SE_M_SUPERSONIC}i{SE_M_GRASSWHISTLE}{SE_M_CHARGE}fin{SE_M_REVERSAL}trainer!\p"
	.string "H{SE_M_REVERSAL}inherite{SE_M_WATERFALL}hi{SE_M_GRASSWHISTLE}father'{SE_M_GRASSWHISTLE}gym\n"
	.string "an{SE_M_WATERFALL}ha{SE_M_GRASSWHISTLE}don{SE_M_REVERSAL}{SE_M_CHARGE}grea{SE_M_SPIT_UP}jo{SE_M_STRENGTH}with\l"
	.string "it.$"

VioletCity_Text_Youngster:
	.string "{SE_M_HEAL_BELL}sa{SE_M_TWISTER}{SE_M_CHARGE}wiggl{SE_M_YAWN}tre{SE_M_REVERSAL}u{SE_M_MORNING_SUN}ahead!\p"
	.string "I{SE_M_ACID_ARMOR}yo{SE_M_DIVE}touc{SE_M_TRI_ATTACK}it{SE_M_SUPERSONIC}i{SE_M_SPIT_UP}squirms\n"
	.string "an{SE_M_WATERFALL}dances{SE_M_DRAGON_RAGE}Cool!$"

VioletCity_Text_Sign:
	.string "VIOLE{SE_M_SWIFT}CITY\p"
	.string "Th{SE_M_REVERSAL}Cit{SE_M_YAWN}o{SE_M_ACID_ARMOR}Nostalgi{SE_M_HYPER_BEAM}Scents$"

VioletCity_Text_GymSign:
	.string "VIOLE{SE_M_SWIFT}CIT{SE_M_MOONLIGHT}POKéMO{SE_M_PSYBEAM2}GYM\p"
	.string "LEADER{SE_M_HEAT_WAVE}FALKNER{SE_M_SUPERSONIC}Th{SE_M_REVERSAL}Elegant\n"
	.string "Maste{SE_M_SAND_TOMB}o{SE_M_ACID_ARMOR}Flyin{SE_M_SANDSTORM}POKéMON$"

VioletCity_Text_SproutTowerSign:
	.string "SPROU{SE_M_SWIFT}TOWER\p"
	.string "Experienc{SE_M_REVERSAL}th{SE_M_REVERSAL}Wa{SE_M_YAWN}o{SE_M_ACID_ARMOR}POKéMON$"

VioletCity_Text_EarlsAcademySign:
	.string "EARL'{SE_M_SKETCH}POKéMO{SE_M_PSYBEAM2}ACADEMY$"

VioletCity_Text_Pichu:
	.string "PICHU{SE_M_HEAT_WAVE}Chuuuu!$"

VioletCity_Text_Bellsprout:
	.string "BELLSPROUT{SE_M_HEAT_WAVE}Sprouuuut.$"

VioletCity_Text_Rattata:
	.string "RATTATA{SE_M_HEAT_WAVE}RATTATARATTA!$"

VioletCity_Text_ElmName:
	.string "PROF.ELM$"

VioletCity_Text_Elm_Call:
	.string "PROF.ELM{SE_M_HEAT_WAVE}Hello{SE_M_SUPERSONIC}{PLAYER}{SE_M_SING}We\n"
	.string "discovere{SE_M_WATERFALL}somethin{SE_M_SANDSTORM}abou{SE_M_SPIT_UP}th{SE_M_REVERSAL}EGG!\p"
	.string "M{SE_M_YAWN}assistan{SE_M_SPIT_UP}i{SE_M_GRASSWHISTLE}a{SE_M_SPIT_UP}th{SE_M_REVERSAL}POKéMON\n"
	.string "CENTE{SE_M_MINIMIZE}i{SE_M_ATTRACT}VIOLE{SE_M_SWIFT}CITY.\p"
	.string "Coul{SE_M_WATERFALL}yo{SE_M_DIVE}tal{SE_M_ENCORE2}t{SE_M_ATTRACT2}him?$"

VioletCity_Text_Kimono_Girl1:
	.string "M{SE_M_REVERSAL}o{SE_M_TRI_ATTACK}my...\n"
	.string "Tha{SE_M_SPIT_UP}EG{SE_M_SWAGGER}mus{SE_M_SPIT_UP}be...!$"

VioletCity_Text_Kimono_Girl2:
	.string "{SE_M_HEAL_BELL}see...\p"
	.string "S{SE_M_ATTRACT2}i{SE_M_SPIT_UP}wa{SE_M_GRASSWHISTLE}hande{SE_M_WATERFALL}fro{SE_M_MILK_DRINK}MR{SE_M_PERISH_SONG}POKéMON\n"
	.string "t{SE_M_ATTRACT2}PROF.ELM{SE_M_SUPERSONIC}the{SE_M_ATTRACT}fro{SE_M_MILK_DRINK}\l"
	.string "PROF.EL{SE_M_GIGA_DRAIN}t{SE_M_ATTRACT2}you.\p"
	.string "No{SE_M_TWISTER}{SE_M_HEAL_BELL}ge{SE_M_SPIT_UP}it...$"

VioletCity_Text_Kimono_Girl3:
	.string "Tha{SE_M_SPIT_UP}EG{SE_M_SWAGGER}i{SE_M_GRASSWHISTLE}trul{SE_M_YAWN}a{SE_M_ATTRACT}importan{SE_M_SPIT_UP}EGG.\p"
	.string "Pleas{SE_M_REVERSAL}d{SE_M_ATTRACT2}tak{SE_M_REVERSAL}goo{SE_M_WATERFALL}car{SE_M_REVERSAL}o{SE_M_ACID_ARMOR}it\n"
	.string "fo{SE_M_SAND_TOMB}me{SE_M_PERISH_SONG}I{SE_M_GRASSWHISTLE}tha{SE_M_SPIT_UP}understood?$"

VioletCity_Text_Kimono_Girl4:
	.string "{SE_M_HEAL_BELL}a{SE_M_MILK_DRINK}countin{SE_M_SANDSTORM}o{SE_M_ATTRACT}you.$"

