@ Johto (data/maps/EcruteakCity_Theater_hns/scripts.inc), as built into the FireRed game.

EcruteakCity_Theater_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, EcruteakCity_Theater_OnTransition
	.byte 0

EcruteakCity_Theater_OnTransition::
	call_if_eq JOHTO_VAR_ECRUTEAK_CITY_THEATER, 1, EcruteakCity_Theater_MapScript_SetRocketSceneActive
	call_if_eq JOHTO_VAR_ECRUTEAK_CITY_THEATER, 8, EcruteakCity_Theater_MapScript_SetKimonoMovement
	end

EcruteakCity_Theater_MapScript_SetRocketSceneActive::
	setobjectxyperm LOCALID_ECRUTEAK_ZUKI, 10, 2
	setobjectmovementtype LOCALID_ECRUTEAK_ROCKET, MOVEMENT_TYPE_TOWER_BEAM
	return

EcruteakCity_Theater_MapScript_SetKimonoMovement::
	setobjectmovementtype LOCALID_ECRUTEAK_ZUKI, MOVEMENT_TYPE_ROTATE_CLOCKWISE
	setobjectmovementtype LOCALID_ECRUTEAK_NAOKO, MOVEMENT_TYPE_ROTATE_CLOCKWISE
	setobjectmovementtype LOCALID_ECRUTEAK_MIKI, MOVEMENT_TYPE_ROTATE_CLOCKWISE
	setobjectmovementtype LOCALID_ECRUTEAK_SAYO, MOVEMENT_TYPE_ROTATE_COUNTERCLOCKWISE
	setobjectmovementtype LOCALID_ECRUTEAK_KUNI, MOVEMENT_TYPE_ROTATE_COUNTERCLOCKWISE
	setobjectmovementtype LOCALID_ECRUTEAK_SISTER, MOVEMENT_TYPE_ROTATE_CLOCKWISE
	return

EcruteakCity_Theater_EventScript_RocketEventTrigger::
	lockall
	playse SE_PIN
	applymovement OBJ_EVENT_ID_PLAYER, J_Common_Movement_ExclamationMark
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	delay 60
	turnobject LOCALID_ECRUTEAK_ROCKET, DIR_NORTH
	special SpawnCameraObject
	applymovement OBJ_EVENT_ID_CAMERA, EcruteakCity_Theater_Movement_CameraPanUp
	waitmovement 0
	msgbox EcruteakCity_Theater_Text_Rocket1, MSGBOX_DEFAULT
	closemessage
	msgbox EcruteakCity_Theater_Text_KimonoRocket1, MSGBOX_DEFAULT
	closemessage
	msgbox EcruteakCity_Theater_Text_Rocket2, MSGBOX_DEFAULT
	applymovement LOCALID_ECRUTEAK_ZUKI, EcruteakCity_Theater_Movement_KimonoGirlMoveBack
	waitmovement 0
	msgbox EcruteakCity_Theater_Text_Rocket3, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_ECRUTEAK_ROCKET, EcruteakCity_Theater_Movement_RocketDance
	delay 50
	applymovement OBJ_EVENT_ID_CAMERA, EcruteakCity_Theater_Movement_CameraPanDown
	waitmovement 0
	special RemoveCameraObject
	setobjectmovementtype LOCALID_ECRUTEAK_ROCKET, MOVEMENT_TYPE_TOWER_BEAM
	setobjectxyperm LOCALID_ECRUTEAK_ZUKI, 10, 2
	setvar JOHTO_VAR_ECRUTEAK_CITY_THEATER, 1
	releaseall
	end

EcruteakCity_Theater_Movement_RocketDance:
	walk_in_place_down
	delay_2
	walk_in_place_right
	delay_2
	face_up
	delay_2
	face_left
	delay_8
	walk_in_place_down
	delay_2
	walk_in_place_left
	delay_2
	face_up
	delay_8
	face_right
	step_end

EcruteakCity_Theater_Movement_CameraPanUp:
	slide_up
	slide_up
	slide_up
	slide_up
	slide_up
	slide_up
	slide_up
	slide_up
	slide_up
	slide_up
	slide_up
	slide_up
	step_end

EcruteakCity_Theater_Movement_CameraPanDown:
	slide_down
	slide_down
	slide_down
	slide_down
	slide_down
	slide_down
	slide_down
	slide_down
	slide_down
	slide_down
	slide_down
	slide_down
	step_end

EcruteakCity_Theater_Movement_KimonoGirlMoveBack:
	lock_facing_direction
	walk_up
	unlock_facing_direction
	step_end

EcruteakCity_Theater_Text_Rocket1:
	.string "ROCKET{SE_M_HEAT_WAVE}Sto{SE_M_MORNING_SUN}dancin{SE_M_SANDSTORM}suc{SE_M_TRI_ATTACK}{SE_M_CHARGE}serious\n"
	.string "dance{SE_M_DRAGON_RAGE}Sho{SE_M_TWISTER}m{SE_M_REVERSAL}somethin{SE_M_SANDSTORM}like\l"
	.string "{SE_M_CHARGE}hul{SE_M_CHARGE}dance!$"

EcruteakCity_Theater_Text_KimonoRocket1:
	.string "KIMON{SE_M_SOLAR_BEAM}GIRL{SE_M_HEAT_WAVE}...Yo{SE_M_DIVE}mustn'{SE_M_SPIT_UP}push\n"
	.string "suc{SE_M_TRI_ATTACK}{SE_M_CHARGE}reques{SE_M_SPIT_UP}o{SE_M_ATTRACT}me.$"

EcruteakCity_Theater_Text_Rocket2:
	.string "ROCKET{SE_M_HEAT_WAVE}Huh?\p"
	.string "Ar{SE_M_REVERSAL}yo{SE_M_DIVE}tellin{SE_M_SANDSTORM}m{SE_M_REVERSAL}yo{SE_M_DIVE}don't\n"
	.string "respec{SE_M_SPIT_UP}wha{SE_M_SPIT_UP}th{SE_M_REVERSAL}customer\l"
	.string "wants?$"

EcruteakCity_Theater_Text_Rocket3:
	.string "Well{SE_M_SUPERSONIC}the{SE_M_ATTRACT}I'l{SE_M_BATON_PASS}sho{SE_M_TWISTER}yo{SE_M_DIVE}how\n"
	.string "t{SE_M_ATTRACT2}dance{SE_M_PERISH_SONG}I'l{SE_M_BATON_PASS}sho{SE_M_TWISTER}yo{SE_M_DIVE}a\l"
	.string "grea{SE_M_SPIT_UP}one.\p"
	.string "Wahahaha!$"

EcruteakCity_Theater_EventScript_Rocket::
	lock
	faceplayer
	msgbox EcruteakCity_Theater_Text_RocketSeen, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_JOHTO_GRUNT_33_HNS, EcruteakCity_Theater_Text_RocketBeaten
	msgbox EcruteakCity_Theater_Text_RocketAfter, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_ECRUTEAK_ROCKET, EcruteakCity_Theater_Movement_RocketLeave
	waitmovement 0
	setflag JOHTO_FLAG_HIDE_ECRUTEAK_ROCKET
	removeobject LOCALID_ECRUTEAK_ROCKET
	call_if_eq VAR_FACING, DIR_EAST, EcruteakCity_Theater_EventScript_PostRocketLeft
	call_if_eq VAR_FACING, DIR_WEST, EcruteakCity_Theater_EventScript_PostRocketRight
	call_if_eq VAR_FACING, DIR_SOUTH, EcruteakCity_Theater_EventScript_PostRocketTop
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	msgbox EcruteakCity_Theater_Text_KimonoRocket3, MSGBOX_DEFAULT
	closemessage
	setvar JOHTO_VAR_ECRUTEAK_CITY_THEATER, 2
	release
	end

EcruteakCity_Theater_EventScript_PostRocketLeft::
	applymovement LOCALID_ECRUTEAK_ZUKI, J_Common_Movement_WalkLeft1
	waitmovement 0
	applymovement LOCALID_ECRUTEAK_ZUKI, J_Common_Movement_WalkDown1
	waitmovement 0
	return

EcruteakCity_Theater_EventScript_PostRocketRight::
	applymovement LOCALID_ECRUTEAK_ZUKI, J_Common_Movement_WalkRight1
	waitmovement 0
	applymovement LOCALID_ECRUTEAK_ZUKI, J_Common_Movement_WalkDown1
	waitmovement 0
	return

EcruteakCity_Theater_EventScript_PostRocketTop::
	turnobject LOCALID_ECRUTEAK_ZUKI, DIR_SOUTH
	return

EcruteakCity_Theater_Movement_RocketLeave:
	jump_2_down
	walk_fast_left
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	step_end

EcruteakCity_Theater_Text_RocketSeen:
	.string "Huh{SE_M_SING}Wh{SE_M_ATTRACT2}ar{SE_M_REVERSAL}you?\n"
	.string "Yo{SE_M_DIVE}dar{SE_M_REVERSAL}t{SE_M_ATTRACT2}ge{SE_M_SPIT_UP}i{SE_M_ATTRACT}m{SE_M_YAWN}way?$"

EcruteakCity_Theater_Text_RocketBeaten:
	.string "Oh{SE_M_SUPERSONIC}no!\n"
	.string "Yo{SE_M_DIVE}mak{SE_M_REVERSAL}m{SE_M_REVERSAL}loo{SE_M_ENCORE2}lik{SE_M_REVERSAL}a\l"
	.string "villain!$"

EcruteakCity_Theater_Text_RocketAfter:
	.string "Oops{SE_M_DRAGON_RAGE}{SE_M_HEAL_BELL}hav{SE_M_REVERSAL}a{SE_M_ATTRACT}importan{SE_M_SPIT_UP}mission!\n"
	.string "I{SE_M_ACID_ARMOR}the{SE_M_YAWN}fin{SE_M_WATERFALL}ou{SE_M_SPIT_UP}{SE_M_HEAL_BELL}wa{SE_M_GRASSWHISTLE}wasting\l"
	.string "tim{SE_M_REVERSAL}here{SE_M_SUPERSONIC}they'l{SE_M_BATON_PASS}mak{SE_M_REVERSAL}m{SE_M_REVERSAL}start\l"
	.string "ove{SE_M_SAND_TOMB}a{SE_M_GRASSWHISTLE}th{SE_M_REVERSAL}lowes{SE_M_SPIT_UP}ROCKE{SE_M_SWIFT}GRUNT!\p"
	.string "{SE_M_HEAL_BELL}bette{SE_M_SAND_TOMB}leav{SE_M_REVERSAL}now!$"

EcruteakCity_Theater_Text_KimonoRocket3:
	.string "Yo{SE_M_DIVE}mus{SE_M_SPIT_UP}b{SE_M_REVERSAL}{PLAYER},\n"
	.string "correct{SE_M_SING}Tha{SE_M_SPIT_UP}wa{SE_M_GRASSWHISTLE}indeed\l"
	.string "excellent.\p"
	.string "Kin{SE_M_WATERFALL}an{SE_M_WATERFALL}strong..{SE_M_PERISH_SONG}Goo{SE_M_WATERFALL}at\n"
	.string "raisin{SE_M_SANDSTORM}POKéMO{SE_M_PSYBEAM2}a{SE_M_GRASSWHISTLE}well...\p"
	.string "Tha{SE_M_SPIT_UP}perso{SE_M_ATTRACT}doe{SE_M_GRASSWHISTLE}kno{SE_M_TWISTER}what\n"
	.string "t{SE_M_ATTRACT2}loo{SE_M_ENCORE2}fo{SE_M_SAND_TOMB}i{SE_M_ATTRACT}people...\p"
	.string "Ohoho{SE_M_DRAGON_RAGE}Tha{SE_M_SPIT_UP}wa{SE_M_GRASSWHISTLE}jus{SE_M_SPIT_UP}me\n"
	.string "talkin{SE_M_SANDSTORM}t{SE_M_ATTRACT2}myself.\l"
	.string "Neve{SE_M_SAND_TOMB}mind.$"

EcruteakCity_Theater_EventScript_KimonoGirl::
	lock
	faceplayer
	goto_if_eq JOHTO_VAR_ECRUTEAK_CITY_THEATER, 6, EcruteakCity_Theater_EventScript_KimonoGirlDuringEvent
	msgbox EcruteakCity_Theater_Text_KimonoDone, MSGBOX_DEFAULT
	closemessage
	release
	end

EcruteakCity_Theater_EventScript_KimonoGirlDuringEvent::
	msgbox EcruteakCity_Theater_Text_KimonoGirlsBeforeBattle, MSGBOX_DEFAULT
	closemessage
	release
	end

EcruteakCity_Theater_EventScript_Zuki::
	lock
	faceplayer
	goto_if_ge JOHTO_VAR_ECRUTEAK_CITY_THEATER, 8, EcruteakCity_Theater_EventScript_ZukiAfterLegendary
	goto_if_eq JOHTO_VAR_ECRUTEAK_CITY_THEATER, 6, EcruteakCity_Theater_EventScript_ZukiBattle
	goto_if_eq JOHTO_VAR_ECRUTEAK_CITY_THEATER, 1, EcruteakCity_Theater_EventScript_ZukiDuringRocket
	msgbox EcruteakCity_Theater_Text_Kimono, MSGBOX_DEFAULT
	closemessage
	release
	end

EcruteakCity_Theater_EventScript_ZukiAfterLegendary::
	msgbox EcruteakCity_Theater_Text_ZukiAfterAll, MSGBOX_DEFAULT
	closemessage
	release
	end

EcruteakCity_Theater_EventScript_ZukiDuringRocket::
	msgbox EcruteakCity_Theater_Text_KimonoGirlBeaten, MSGBOX_DEFAULT
	closemessage
	release
	end

EcruteakCity_Theater_Text_Kimono:
	.string "Fo{SE_M_SAND_TOMB}KIMON{SE_M_SOLAR_BEAM}GIRL{SE_M_SKETCH}lik{SE_M_REVERSAL}me,\n"
	.string "dancin{SE_M_SANDSTORM}i{SE_M_GRASSWHISTLE}everything.\p"
	.string "{SE_M_HEAL_BELL}hav{SE_M_REVERSAL}neve{SE_M_SAND_TOMB}gon{SE_M_REVERSAL}{SE_M_CHARGE}day\n"
	.string "withou{SE_M_SPIT_UP}{SE_M_CHARGE}danc{SE_M_REVERSAL}practice.\p"
	.string "POKéMO{SE_M_PSYBEAM2}ar{SE_M_REVERSAL}th{SE_M_REVERSAL}same.\n"
	.string "The{SE_M_YAWN}gro{SE_M_TWISTER}wit{SE_M_TRI_ATTACK}yo{SE_M_DIVE}little\l"
	.string "b{SE_M_YAWN}littl{SE_M_REVERSAL}eac{SE_M_TRI_ATTACK}day.$"

EcruteakCity_Theater_EventScript_SurfGuy::
	lock
	faceplayer
	goto_if_eq JOHTO_VAR_ECRUTEAK_CITY_THEATER, 1, EcruteakCity_Theater_EventScript_SurfGuyDuringRocket
	goto_if_unset JOHTO_FLAG_RECEIVED_HM_SURF, EcruteakCity_Theater_EventScript_SurfGuy_GiveSurf
	msgbox EcruteakCity_Theater_Text_SurfGuyAfter, MSGBOX_DEFAULT
	closemessage
	release
	end

EcruteakCity_Theater_EventScript_SurfGuy_GiveSurf::
	msgbox EcruteakCity_Theater_Text_SurfGuyGiveSurf, MSGBOX_DEFAULT
	giveitem ITEM_HM_SURF
	setflag JOHTO_FLAG_RECEIVED_HM_SURF
	msgbox EcruteakCity_Theater_Text_SurfGuyGaveSurf
	closemessage
	setflag JOHTO_FLAG_RECEIVED_HM_SURF
	setvar JOHTO_VAR_ECRUTEAK_CITY_THEATER, 3
	release
	end

EcruteakCity_Theater_EventScript_SurfGuyDuringRocket::
	msgbox EcruteakCity_Theater_Text_SurfGuyRocket, MSGBOX_DEFAULT
	closemessage
	release
	end

EcruteakCity_Theater_EventScript_TriggerSurfGuy::
	lock
	applymovement LOCALID_SURF_GUY, EcruteakCity_Theater_Movement_SurfGuy1
	waitmovement 0
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	msgbox EcruteakCity_Theater_Text_SurfGuyGiveSurf, MSGBOX_DEFAULT
	giveitem ITEM_HM_SURF
	setflag JOHTO_FLAG_RECEIVED_HM_SURF
	msgbox EcruteakCity_Theater_Text_SurfGuyGaveSurf
	closemessage
	setflag JOHTO_FLAG_RECEIVED_HM_SURF
	setvar JOHTO_VAR_ECRUTEAK_CITY_THEATER, 3
	applymovement LOCALID_SURF_GUY, EcruteakCity_Theater_Movement_SurfGuy2
	waitmovement 0
	release
	end

EcruteakCity_Theater_EventScript_Psyduck::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_PSYDUCK, CRY_MODE_NORMAL
	msgbox EcruteakCity_Theater_Text_Psyduck, MSGBOX_DEFAULT
	waitmoncry
	release
	end

EcruteakCity_Theater_EventScript_Boy::
	lock
	faceplayer
	goto_if_eq JOHTO_VAR_ECRUTEAK_CITY_THEATER, 1, EcruteakCity_Theater_EventScript_BoyDuringRocket
	msgbox EcruteakCity_Theater_Text_Boy, MSGBOX_DEFAULT
	closemessage
	release
	end

EcruteakCity_Theater_EventScript_BoyDuringRocket::
	msgbox EcruteakCity_Theater_Text_BoyBefore, MSGBOX_DEFAULT
	closemessage
	release
	end

EcruteakCity_Theater_EventScript_Granny::
	lock
	faceplayer
	goto_if_eq JOHTO_VAR_ECRUTEAK_CITY_THEATER, 1, EcruteakCity_Theater_EventScript_GrannyDuringRocket
	msgbox EcruteakCity_Theater_Text_Granny, MSGBOX_DEFAULT
	closemessage
	release
	end

EcruteakCity_Theater_EventScript_GrannyDuringRocket::
	msgbox EcruteakCity_Theater_Text_GrannyBefore, MSGBOX_DEFAULT
	closemessage
	release
	end

EcruteakCity_Theater_EventScript_Gramps::
	lock
	faceplayer
	goto_if_eq JOHTO_VAR_ECRUTEAK_CITY_THEATER, 1, EcruteakCity_Theater_EventScript_GrampsDuringRocket
	msgbox EcruteakCity_Theater_Text_Gramps, MSGBOX_DEFAULT
	closemessage
	release
	end

EcruteakCity_Theater_EventScript_GrampsDuringRocket::
	msgbox EcruteakCity_Theater_Text_GrampsBefore, MSGBOX_DEFAULT
	closemessage
	release
	end

EcruteakCity_Theater_EventScript_Girl::
	lock
	faceplayer
	goto_if_eq JOHTO_VAR_ECRUTEAK_CITY_THEATER, 1, EcruteakCity_Theater_EventScript_GirlDuringRocket
	msgbox EcruteakCity_Theater_Text_Girl, MSGBOX_DEFAULT
	closemessage
	release
	end

EcruteakCity_Theater_EventScript_GirlDuringRocket::
	msgbox EcruteakCity_Theater_Text_GirlBefore, MSGBOX_DEFAULT
	closemessage
	release
	end

EcruteakCity_Theater_EventScript_FancyPanel::
	lock
	msgbox EcruteakCity_Theater_Text_FancyPanel, MSGBOX_DEFAULT
	closemessage
	release
	end

EcruteakCity_Theater_Movement_SurfGuy1:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_down
	step_end

EcruteakCity_Theater_Movement_SurfGuy2:
	walk_up
	walk_right
	walk_right
	walk_right
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

EcruteakCity_Theater_Text_SurfGuyRocket:
	.string "What'{SE_M_GRASSWHISTLE}th{SE_M_REVERSAL}dea{SE_M_BATON_PASS}wit{SE_M_TRI_ATTACK}that\n"
	.string "Tea{SE_M_MILK_DRINK}Rocke{SE_M_SPIT_UP}Grunt{SE_M_SUPERSONIC}messing\l"
	.string "wit{SE_M_TRI_ATTACK}tha{SE_M_SPIT_UP}KIMON{SE_M_SOLAR_BEAM}GIRL?\p"
	.string "Yo{SE_M_DIVE}ar{SE_M_REVERSAL}{SE_M_CHARGE}Trainer{SE_M_SUPERSONIC}right?\n"
	.string "Pleas{SE_M_REVERSAL}hel{SE_M_MORNING_SUN}her!$"

EcruteakCity_Theater_Text_SurfGuyGiveSurf:
	.string "Wonderful{SE_M_DRAGON_RAGE}Yo{SE_M_DIVE}wer{SE_M_REVERSAL}so\n"
	.string "courageou{SE_M_GRASSWHISTLE}fo{SE_M_SAND_TOMB}you{SE_M_SAND_TOMB}age!\p"
	.string "I{SE_M_SPIT_UP}wa{SE_M_GRASSWHISTLE}{SE_M_CHARGE}rar{SE_M_REVERSAL}sigh{SE_M_SPIT_UP}t{SE_M_ATTRACT2}see!\n"
	.string "{SE_M_HEAL_BELL}wan{SE_M_SPIT_UP}yo{SE_M_DIVE}t{SE_M_ATTRACT2}hav{SE_M_REVERSAL}this.\p"
	.string "Don'{SE_M_SPIT_UP}b{SE_M_REVERSAL}shy--tak{SE_M_REVERSAL}it!$"

EcruteakCity_Theater_Text_SurfGuyGaveSurf:
	.string "That'{SE_M_GRASSWHISTLE}SURF.\n"
	.string "It'{SE_M_GRASSWHISTLE}{SE_M_CHARGE}mov{SE_M_REVERSAL}tha{SE_M_SPIT_UP}let{SE_M_GRASSWHISTLE}POKéMON\l"
	.string "swi{SE_M_MILK_DRINK}acros{SE_M_GRASSWHISTLE}wate{SE_M_SAND_TOMB}wit{SE_M_TRI_ATTACK}ease.$"

EcruteakCity_Theater_Text_SurfGuyAfter:
	.string "No{SE_M_SPIT_UP}onl{SE_M_YAWN}ar{SE_M_REVERSAL}th{SE_M_REVERSAL}KIMON{SE_M_SOLAR_BEAM}GIRLS\n"
	.string "grea{SE_M_SPIT_UP}dancers{SE_M_SUPERSONIC}they'r{SE_M_REVERSAL}also\l"
	.string "skille{SE_M_WATERFALL}a{SE_M_SPIT_UP}POKéMON.\p"
	.string "Bu{SE_M_SPIT_UP}the{SE_M_YAWN}battl{SE_M_REVERSAL}onl{SE_M_YAWN}fo{SE_M_SAND_TOMB}good\n"
	.string "reasons.\p"
	.string "{SE_M_HEAL_BELL}don'{SE_M_SPIT_UP}kno{SE_M_TWISTER}i{SE_M_ACID_ARMOR}yo{SE_M_DIVE}coul{SE_M_WATERFALL}beat\n"
	.string "the{SE_M_MILK_DRINK}i{SE_M_ACID_ARMOR}the{SE_M_YAWN}showe{SE_M_WATERFALL}thei{SE_M_SAND_TOMB}skill...$"

EcruteakCity_Theater_Text_Psyduck:
	.string "PSYDUCK{SE_M_HEAT_WAVE}Da{SE_M_DIVE}dau!$"

EcruteakCity_Theater_Text_BoyBefore:
	.string "Eeeeek!$"

EcruteakCity_Theater_Text_Boy:
	.string "{SE_M_HEAL_BELL}wa{SE_M_GRASSWHISTLE}suppose{SE_M_WATERFALL}t{SE_M_ATTRACT2}b{SE_M_REVERSAL}th{SE_M_REVERSAL}hero...!\n"
	.string "S{SE_M_ATTRACT2}muc{SE_M_TRI_ATTACK}fo{SE_M_SAND_TOMB}gettin{SE_M_SANDSTORM}clos{SE_M_REVERSAL}to\l"
	.string "{SE_M_CHARGE}KIMON{SE_M_SOLAR_BEAM}GIRL!$"

EcruteakCity_Theater_Text_Granny:
	.string "Tha{SE_M_SPIT_UP}man'{SE_M_GRASSWHISTLE}alway{SE_M_GRASSWHISTLE}wit{SE_M_TRI_ATTACK}his\n"
	.string "PSYDUCK.\p"
	.string "Say{SE_M_GRASSWHISTLE}h{SE_M_REVERSAL}want{SE_M_GRASSWHISTLE}{SE_M_CHARGE}POKéMO{SE_M_PSYBEAM2}that\n"
	.string "ca{SE_M_ATTRACT}SUR{SE_M_LEER}an{SE_M_WATERFALL}dance.\p"
	.string "I{SE_M_GRASSWHISTLE}h{SE_M_REVERSAL}tryin{SE_M_SANDSTORM}t{SE_M_ATTRACT2}mak{SE_M_REVERSAL}{SE_M_CHARGE}POKéMON\n"
	.string "tha{SE_M_SPIT_UP}star{SE_M_GRASSWHISTLE}i{SE_M_ATTRACT}synchronized\l"
	.string "swimming?$"

EcruteakCity_Theater_Text_GrannyBefore:
	.string "Oh..{SE_M_PERISH_SONG}Ouch...!\n"
	.string "Thi{SE_M_GRASSWHISTLE}stomachache!\p"
	.string "{SE_M_HEAL_BELL}wouldn'{SE_M_SPIT_UP}le{SE_M_SPIT_UP}thi{SE_M_GRASSWHISTLE}gu{SE_M_YAWN}ac{SE_M_SPIT_UP}like\n"
	.string "tha{SE_M_SPIT_UP}i{SE_M_ACID_ARMOR}no{SE_M_SPIT_UP}fo{SE_M_SAND_TOMB}thi{SE_M_GRASSWHISTLE}pain...!$"

EcruteakCity_Theater_Text_Gramps:
	.string "Th{SE_M_REVERSAL}KIMON{SE_M_SOLAR_BEAM}GIRL{SE_M_SKETCH}ar{SE_M_REVERSAL}so\n"
	.string "beautiful...\p"
	.string "Bu{SE_M_SPIT_UP}the{SE_M_YAWN}hav{SE_M_REVERSAL}t{SE_M_ATTRACT2}g{SE_M_ATTRACT2}through\n"
	.string "rigorou{SE_M_GRASSWHISTLE}training.\p"
	.string "An{SE_M_WATERFALL}the{SE_M_YAWN}hav{SE_M_REVERSAL}t{SE_M_ATTRACT2}lear{SE_M_ATTRACT}t{SE_M_ATTRACT2}follow\n"
	.string "custom{SE_M_GRASSWHISTLE}befor{SE_M_REVERSAL}appearin{SE_M_SANDSTORM}in\l"
	.string "public.\p"
	.string "Bu{SE_M_SPIT_UP}i{SE_M_ACID_ARMOR}yo{SE_M_DIVE}lov{SE_M_REVERSAL}something,\n"
	.string "anythin{SE_M_SANDSTORM}i{SE_M_GRASSWHISTLE}possible.$"

EcruteakCity_Theater_Text_GrampsBefore:
	.string "Oh..{SE_M_PERISH_SONG}Ouch...!\n"
	.string "Thi{SE_M_GRASSWHISTLE}bac{SE_M_ENCORE2}pain!\p"
	.string "{SE_M_HEAL_BELL}wouldn'{SE_M_SPIT_UP}le{SE_M_SPIT_UP}thi{SE_M_GRASSWHISTLE}gu{SE_M_YAWN}ac{SE_M_SPIT_UP}like\n"
	.string "tha{SE_M_SPIT_UP}i{SE_M_ACID_ARMOR}no{SE_M_SPIT_UP}fo{SE_M_SAND_TOMB}thi{SE_M_GRASSWHISTLE}pain...!$"

EcruteakCity_Theater_Text_Girl:
	.string "Th{SE_M_REVERSAL}KIMON{SE_M_SOLAR_BEAM}GIRL{SE_M_SKETCH}ar{SE_M_REVERSAL}m{SE_M_YAWN}big\n"
	.string "sisters{SE_M_DRAGON_RAGE}I'l{SE_M_BATON_PASS}b{SE_M_REVERSAL}lik{SE_M_REVERSAL}the{SE_M_MILK_DRINK}one\l"
	.string "day!$"

EcruteakCity_Theater_Text_GirlBefore:
	.string "{SE_M_HEAL_BELL}lik{SE_M_REVERSAL}tha{SE_M_SPIT_UP}funn{SE_M_YAWN}dance!$"

EcruteakCity_Theater_Text_FancyPanel:
	.string "It'{SE_M_GRASSWHISTLE}{SE_M_CHARGE}fanc{SE_M_YAWN}pane{SE_M_BATON_PASS}that's\n"
	.string "decorate{SE_M_WATERFALL}wit{SE_M_TRI_ATTACK}flowers.$"

EcruteakCity_Theater_Trigger_PreBattleCutsceneLeft::
	lock
	applymovement2 OBJ_EVENT_ID_PLAYER, EcruteakCity_Theater_Movement_PlayerWalkToZukiLeft
	applymovement2 OBJ_EVENT_ID_FOLLOWER, EcruteakCity_Theater_Movement_MonWalkToZukiLeft
	waitmovement OBJ_EVENT_ID_FOLLOWER
	waitmovement OBJ_EVENT_ID_PLAYER
	delay 10
	lockall
	goto EcruteakCity_Theater_EventScript_LegendaryCutscene

EcruteakCity_Theater_Trigger_PreBattleCutsceneTop::
	lock
	applymovement2 OBJ_EVENT_ID_PLAYER, EcruteakCity_Theater_Movement_PlayerWalkToZukiTop
	applymovement2 OBJ_EVENT_ID_FOLLOWER, EcruteakCity_Theater_Movement_MonWalkToZukiTop
	waitmovement OBJ_EVENT_ID_FOLLOWER
	waitmovement OBJ_EVENT_ID_PLAYER
	delay 10
	lockall
	goto EcruteakCity_Theater_EventScript_LegendaryCutscene

EcruteakCity_Theater_Trigger_PreBattleCutsceneRight::
	lock
	applymovement2 OBJ_EVENT_ID_PLAYER, EcruteakCity_Theater_Movement_PlayerWalkToZukiRight
	applymovement2 OBJ_EVENT_ID_FOLLOWER, EcruteakCity_Theater_Movement_MonWalkToZukiRight
	waitmovement OBJ_EVENT_ID_FOLLOWER
	waitmovement OBJ_EVENT_ID_PLAYER
	delay 10
	lockall
	goto EcruteakCity_Theater_EventScript_LegendaryCutscene

EcruteakCity_Theater_Movement_PlayerWalkToZukiLeft:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_left
	walk_left
	walk_left
	walk_up
	walk_up
	walk_up
	walk_right
	walk_right
	walk_right
	walk_right
	face_up
	step_end

EcruteakCity_Theater_Movement_MonWalkToZukiLeft:
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
	walk_up
	walk_left
	walk_left
	walk_left
	walk_up
	walk_up
	walk_up
	walk_right
	walk_right
	walk_right
	step_end

EcruteakCity_Theater_Movement_PlayerWalkToZukiTop:
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
	walk_left
	walk_left
	walk_left
	walk_up
	walk_up
	walk_up
	walk_right
	walk_right
	walk_right
	walk_right
	face_up
	step_end

EcruteakCity_Theater_Movement_MonWalkToZukiTop:
	walk_up
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
	walk_left
	walk_left
	walk_left
	walk_up
	walk_up
	walk_up
	walk_right
	walk_right
	walk_right
	step_end

EcruteakCity_Theater_Movement_PlayerWalkToZukiRight:
	walk_right
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_right
	walk_right
	walk_right
	walk_up
	walk_up
	walk_up
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	face_up
	step_end

EcruteakCity_Theater_Movement_MonWalkToZukiRight::
	walk_right
	walk_right
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_right
	walk_right
	walk_right
	walk_up
	walk_up
	walk_up
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

EcruteakCity_Theater_Movement_KimonoSpin:
	face_right
	delay_8
	face_up
	delay_8
	face_left
	delay_8
	face_down
	delay_8
	face_right
	delay_8
	face_up
	delay_8
	face_left
	delay_8
	face_down
	step_end

EcruteakCity_Theater_EventScript_LugiaBuffer::
	bufferspeciesname STR_VAR_1, SPECIES_LUGIA
	return

EcruteakCity_Theater_EventScript_HoohBuffer::
	bufferspeciesname STR_VAR_1, SPECIES_HO_OH
	return

EcruteakCity_Theater_EventScript_LegendaryCutscene::
	call_if_eq JOHTO_VAR_LUGIA_OR_HOOH, 1, EcruteakCity_Theater_EventScript_LugiaBuffer
	call_if_eq JOHTO_VAR_LUGIA_OR_HOOH, 2, EcruteakCity_Theater_EventScript_HoohBuffer
	msgbox EcruteakCity_Theater_Text_ZukiSeen, MSGBOX_DEFAULT
	closemessage
	delay 20
	playse SE_M_PETAL_DANCE
	applymovement2 LOCALID_ECRUTEAK_ZUKI, EcruteakCity_Theater_Movement_KimonoSpin
	waitmovement 0
	setvar JOHTO_VAR_ECRUTEAK_CITY_THEATER, 6

EcruteakCity_Theater_EventScript_ZukiBattle::
	msgbox EcruteakCity_Theater_Text_ZukiSeenAgain, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, FALSE, EcruteakCity_Theater_EventScript_LegendaryDenied
	call_if_eq VAR_FACING, DIR_SOUTH, EcruteakCity_Theater_Movement_SouthCorrection
	call_if_eq VAR_FACING, DIR_WEST, EcruteakCity_Theater_Movement_WestCorrection
	call_if_eq VAR_FACING, DIR_EAST, EcruteakCity_Theater_Movement_EastCorrection
	settotemboost B_POSITION_OPPONENT_LEFT, 0, 0, 1, 2, 0, 0
	trainerbattle_no_intro TRAINER_JOHTO_ZUKI_HNS, EcruteakCity_Theater_Text_KimonoGirlBeaten
	applymovement2 LOCALID_ECRUTEAK_ZUKI, EcruteakCity_Theater_Movement_ZukiWalkUp
	waitmovement 0

EcruteakCity_Theater_EventScript_NaokoBattle::
	playse SE_M_PETAL_DANCE
	applymovement2 LOCALID_ECRUTEAK_NAOKO, EcruteakCity_Theater_Movement_KimonoSpin
	waitmovement 0
	applymovement2 LOCALID_ECRUTEAK_NAOKO, EcruteakCity_Theater_Movement_NaokoWalkToPlayer
	waitmovement 0
	msgbox EcruteakCity_Theater_Text_NaokoSeen, MSGBOX_DEFAULT
	settotemboost B_POSITION_OPPONENT_LEFT, 0, 1, 0, 1, 1, 0
	trainerbattle_no_intro TRAINER_JOHTO_NAOKO_HNS, EcruteakCity_Theater_Text_KimonoGirlBeaten
	applymovement2 LOCALID_ECRUTEAK_NAOKO, EcruteakCity_Theater_Movement_NaokoWalkBack
	waitmovement 0

EcruteakCity_Theater_EventScript_MikiBattle::
	playse SE_M_PETAL_DANCE
	applymovement2 LOCALID_ECRUTEAK_MIKI, EcruteakCity_Theater_Movement_KimonoSpin
	waitmovement 0
	applymovement2 LOCALID_ECRUTEAK_MIKI, EcruteakCity_Theater_Movement_MikiWalkToPlayer
	waitmovement 0
	msgbox EcruteakCity_Theater_Text_MikiSeen, MSGBOX_DEFAULT
	settotemboost B_POSITION_OPPONENT_LEFT, 0, 0, 0, 1, 2, 0
	trainerbattle_no_intro TRAINER_JOHTO_MIKI_HNS, EcruteakCity_Theater_Text_KimonoGirlBeaten
	applymovement2 LOCALID_ECRUTEAK_MIKI, EcruteakCity_Theater_Movement_MikiWalkBack
	waitmovement 0

EcruteakCity_Theater_EventScript_SayoBattle::
	playse SE_M_PETAL_DANCE
	applymovement2 LOCALID_ECRUTEAK_SAYO, EcruteakCity_Theater_Movement_KimonoSpin
	waitmovement 0
	applymovement2 LOCALID_ECRUTEAK_SAYO, EcruteakCity_Theater_Movement_SayoWalkToPlayer
	waitmovement 0
	msgbox EcruteakCity_Theater_Text_SayoSeen, MSGBOX_DEFAULT
	settotemboost B_POSITION_OPPONENT_LEFT, 0, 0, 2, 1, 0, 0
	trainerbattle_no_intro TRAINER_JOHTO_SAYO_HNS, EcruteakCity_Theater_Text_KimonoGirlBeaten
	applymovement2 LOCALID_ECRUTEAK_SAYO, EcruteakCity_Theater_Movement_SayoWalkBack
	waitmovement 0

EcruteakCity_Theater_EventScript_KuniBattle::
	playse SE_M_PETAL_DANCE
	applymovement2 LOCALID_ECRUTEAK_KUNI, EcruteakCity_Theater_Movement_KimonoSpin
	waitmovement 0
	applymovement2 LOCALID_ECRUTEAK_KUNI, EcruteakCity_Theater_Movement_KuniWalkToPlayer
	waitmovement 0
	msgbox EcruteakCity_Theater_Text_KuniSeen, MSGBOX_DEFAULT
	settotemboost B_POSITION_OPPONENT_LEFT, 0, 2, 0, 0, 1, 0
	trainerbattle_no_intro TRAINER_JOHTO_KUNI_HNS, EcruteakCity_Theater_Text_KimonoGirlBeaten
	applymovement2 LOCALID_ECRUTEAK_KUNI, EcruteakCity_Theater_Movement_KuniWalkBack
	waitmovement 0

EcruteakCity_Theater_EventScript_BeatGauntlet::
	applymovement2 LOCALID_ECRUTEAK_ZUKI, J_Common_Movement_WalkDown1
	waitmovement 0
	msgbox EcruteakCity_Theater_Text_ZukiDone, MSGBOX_DEFAULT
	goto_if_eq JOHTO_VAR_LUGIA_OR_HOOH, 1, EcruteakCity_Theater_EventScript_Lugia
	goto_if_eq JOHTO_VAR_LUGIA_OR_HOOH, 2, EcruteakCity_Theater_EventScript_Hooh

EcruteakCity_Theater_Movement_SouthCorrection::
	applymovement LOCALID_PLAYER, J_Common_Movement_WalkRight1
	waitmovement 0
	applymovement LOCALID_PLAYER, J_Common_Movement_WalkDown1
	waitmovement 0
	applymovement LOCALID_PLAYER, J_Common_Movement_WalkDown1
	waitmovement 0
	applymovement LOCALID_PLAYER, J_Common_Movement_WalkLeft1
	waitmovement 0
	turnobject LOCALID_PLAYER, DIR_NORTH
	turnobject LOCALID_ECRUTEAK_ZUKI, DIR_SOUTH
	return

EcruteakCity_Theater_Movement_WestCorrection::
	applymovement LOCALID_PLAYER, J_Common_Movement_WalkDown1
	waitmovement 0
	applymovement LOCALID_PLAYER, J_Common_Movement_WalkLeft1
	waitmovement 0
	turnobject LOCALID_PLAYER, DIR_NORTH
	turnobject LOCALID_ECRUTEAK_ZUKI, DIR_SOUTH
	return

EcruteakCity_Theater_Movement_EastCorrection::
	applymovement LOCALID_PLAYER, J_Common_Movement_WalkDown1
	waitmovement 0
	applymovement LOCALID_PLAYER, J_Common_Movement_WalkRight1
	waitmovement 0
	turnobject LOCALID_PLAYER, DIR_NORTH
	turnobject LOCALID_ECRUTEAK_ZUKI, DIR_SOUTH
	return

EcruteakCity_Theater_EventScript_Lugia::
	giveitem ITEM_TIDAL_BELL
	closemessage
	playse SE_M_RAZOR_WIND
	setvar VAR_0x8004, 1
	setvar VAR_0x8005, 1
	setvar VAR_0x8006, 20
	setvar VAR_0x8007, 6
	special ShakeCamera
	waitstate
	addobject LOCALID_ECRUTEAK_SISTER
	applymovement2 LOCALID_ECRUTEAK_SISTER, EcruteakCity_Theater_Movement_Sister
	waitmovement 0
	turnobject LOCALID_ECRUTEAK_ZUKI, DIR_WEST
	msgbox EcruteakCity_Theater_Text_GirlLugia, MSGBOX_DEFAULT
	closemessage
	playse SE_PIN
	applymovement LOCALID_ECRUTEAK_ZUKI, J_Common_Movement_ExclamationMark
	delay 55
	waitmovement LOCALID_ECRUTEAK_ZUKI
	turnobject LOCALID_ECRUTEAK_ZUKI, DIR_SOUTH
	msgbox EcruteakCity_Theater_Text_ZukiLugia, MSGBOX_DEFAULT
	closemessage
	fadescreenswapbuffers FADE_TO_BLACK

	removeobject LOCALID_ECRUTEAK_ZUKI
	removeobject LOCALID_ECRUTEAK_MIKI
	removeobject LOCALID_ECRUTEAK_NAOKO
	removeobject LOCALID_ECRUTEAK_KUNI
	removeobject LOCALID_ECRUTEAK_SAYO
	removeobject LOCALID_ECRUTEAK_MIKI

	removeobject LOCALID_ECRUTEAK_SISTER
	playse SE_EXIT
	delay 120
	fadescreenswapbuffers FADE_FROM_BLACK
	clearflag JOHTO_FLAG_HIDE_WHIRL_ISLANDS_KIMONO_GIRLS
	clearflag JOHTO_FLAG_HIDE_WHIRL_ISLANDS_TENTACRUEL
	setvar JOHTO_VAR_COMPLETED_LUGIA, 2
	setvar JOHTO_VAR_COMPLETED_HO_OH, 3
	setflag JOHTO_FLAG_HIDE_WHIRL_ISLANDS_TENTACRUEL
	setflag JOHTO_FLAG_HIDE_ECRUTEAK_CITY_THEATER_ZUKI
	setflag JOHTO_FLAG_HIDE_ECRUTEAK_CITY_THEATER_KIMONOS
	setvar JOHTO_VAR_NEWBARKTOWN_LABSTATE, 9
	setvar JOHTO_VAR_ECRUTEAK_CITY_THEATER, 7
	release
	end

EcruteakCity_Theater_EventScript_Hooh::
	giveitem ITEM_CLEAR_BELL
	closemessage
	playse SE_M_RAZOR_WIND
	setvar VAR_0x8004, 1
	setvar VAR_0x8005, 1
	setvar VAR_0x8006, 20
	setvar VAR_0x8007, 6
	special ShakeCamera
	waitstate
	addobject LOCALID_ECRUTEAK_SISTER
	applymovement2 LOCALID_ECRUTEAK_SISTER, EcruteakCity_Theater_Movement_Sister
	waitmovement 0
	msgbox EcruteakCity_Theater_Text_GirlHooh, MSGBOX_DEFAULT
	closemessage
	playse SE_PIN
	applymovement LOCALID_ECRUTEAK_ZUKI, J_Common_Movement_ExclamationMark
	delay 55
	waitmovement LOCALID_ECRUTEAK_ZUKI
	turnobject LOCALID_ECRUTEAK_ZUKI, DIR_SOUTH
	msgbox EcruteakCity_Theater_Text_ZukiHooh, MSGBOX_DEFAULT
	closemessage
	fadescreenswapbuffers FADE_TO_BLACK

	removeobject LOCALID_ECRUTEAK_ZUKI
	removeobject LOCALID_ECRUTEAK_MIKI
	removeobject LOCALID_ECRUTEAK_NAOKO
	removeobject LOCALID_ECRUTEAK_KUNI
	removeobject LOCALID_ECRUTEAK_SAYO
	removeobject LOCALID_ECRUTEAK_MIKI

	removeobject LOCALID_ECRUTEAK_SISTER
	playse SE_EXIT
	delay 120
	fadescreenswapbuffers FADE_FROM_BLACK

	clearflag JOHTO_FLAG_HIDE_TINTOWER_GUARD
	clearflag JOHTO_FLAG_HIDE_TIN_TOWER_KIMONO_GIRLS
	setvar JOHTO_VAR_COMPLETED_HO_OH, 2
	setvar JOHTO_VAR_COMPLETED_LUGIA, 3
	setflag JOHTO_FLAG_HIDE_ECRUTEAK_CITY_THEATER_ZUKI
	setflag JOHTO_FLAG_HIDE_ECRUTEAK_CITY_THEATER_KIMONOS
	setvar JOHTO_VAR_NEWBARKTOWN_LABSTATE, 9
	setvar JOHTO_VAR_ECRUTEAK_CITY_THEATER, 7
	release
	end

EcruteakCity_Theater_Movement_Sister:
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_up
	walk_fast_right
	step_end

EcruteakCity_Theater_EventScript_LegendaryDenied::
	msgbox EcruteakCity_Theater_Text_ZukiNo, MSGBOX_DEFAULT
	closemessage
	release
	end

EcruteakCity_Theater_Movement_ZukiWalkUp:
	lock_facing_direction
	walk_up
	unlock_facing_direction
	step_end

EcruteakCity_Theater_Movement_NaokoWalkToPlayer:
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	face_down
	step_end

EcruteakCity_Theater_Movement_NaokoWalkBack:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	face_down
	step_end

EcruteakCity_Theater_Movement_MikiWalkToPlayer:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	face_down
	step_end

EcruteakCity_Theater_Movement_MikiWalkBack:
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	face_down
	step_end

EcruteakCity_Theater_Movement_SayoWalkToPlayer:
	walk_down
	walk_right
	walk_right
	walk_right
	face_down
	step_end

EcruteakCity_Theater_Movement_SayoWalkBack:
	walk_left
	walk_left
	walk_left
	walk_up
	face_down
	step_end

EcruteakCity_Theater_Movement_KuniWalkToPlayer:
	walk_down
	walk_left
	walk_left
	walk_left
	face_down
	step_end

EcruteakCity_Theater_Movement_KuniWalkBack:
	walk_right
	walk_right
	walk_right
	walk_up
	face_down
	step_end

EcruteakCity_Theater_Text_KimonoGirlBeaten:
	.string "...$"

EcruteakCity_Theater_Text_ZukiSeen:
	.string "Welcome{SE_M_PERISH_SONG}M{SE_M_YAWN}nam{SE_M_REVERSAL}i{SE_M_GRASSWHISTLE}ZUKI.\n"
	.string "{SE_M_HEAL_BELL}me{SE_M_SPIT_UP}yo{SE_M_DIVE}previousl{SE_M_YAWN}i{SE_M_ATTRACT}VIOLET\l"
	.string "CITY.\p"
	.string "T{SE_M_ATTRACT2}brin{SE_M_SANDSTORM}bac{SE_M_ENCORE2}{STR_VAR_1}{SE_M_SUPERSONIC}we\n"
	.string "neede{SE_M_WATERFALL}someon{SE_M_REVERSAL}wit{SE_M_TRI_ATTACK}th{SE_M_REVERSAL}righ{SE_M_SPIT_UP}bond\l"
	.string "wit{SE_M_TRI_ATTACK}POKéMON.\p"
	.string "W{SE_M_REVERSAL}aske{SE_M_WATERFALL}MR{SE_M_PERISH_SONG}POKéMO{SE_M_PSYBEAM2}t{SE_M_ATTRACT2}giv{SE_M_REVERSAL}this\n"
	.string "MYSTER{SE_M_MOONLIGHT}EG{SE_M_SWAGGER}to\l"
	.string "whoeve{SE_M_SAND_TOMB}showe{SE_M_WATERFALL}potential.\p"
	.string "Th{SE_M_REVERSAL}EG{SE_M_SWAGGER}wen{SE_M_SPIT_UP}fro{SE_M_MILK_DRINK}MR{SE_M_PERISH_SONG}POKéMON\n"
	.string "t{SE_M_ATTRACT2}PROF.ELM{SE_M_SUPERSONIC}the{SE_M_ATTRACT}t{SE_M_ATTRACT2}you.\p"
	.string "Bu{SE_M_SPIT_UP}bein{SE_M_SANDSTORM}pur{SE_M_REVERSAL}alon{SE_M_REVERSAL}i{SE_M_GRASSWHISTLE}no{SE_M_SPIT_UP}enough\n"
	.string "t{SE_M_ATTRACT2}fac{SE_M_REVERSAL}th{SE_M_REVERSAL}powe{SE_M_SAND_TOMB}o{SE_M_ACID_ARMOR}thi{SE_M_GRASSWHISTLE}POKéMON.$"

EcruteakCity_Theater_Text_ZukiSeenAgain:
	.string "{SE_M_HEAL_BELL}wil{SE_M_BATON_PASS}tes{SE_M_SPIT_UP}yo{SE_M_DIVE}t{SE_M_ATTRACT2}se{SE_M_REVERSAL}i{SE_M_ACID_ARMOR}yo{SE_M_DIVE}are\n"
	.string "{SE_M_CHARGE}goo{SE_M_WATERFALL}Trainer.\p"
	.string "Ar{SE_M_REVERSAL}yo{SE_M_DIVE}ready{SE_M_SUPERSONIC}{PLAYER}?$"

EcruteakCity_Theater_Text_ZukiNo:
	.string "Tha{SE_M_SPIT_UP}i{SE_M_GRASSWHISTLE}fine...\n"
	.string "{SE_M_HEAL_BELL}wil{SE_M_BATON_PASS}wai{SE_M_SPIT_UP}fo{SE_M_SAND_TOMB}yo{SE_M_DIVE}t{SE_M_ATTRACT2}get\l"
	.string "ready.$"

EcruteakCity_Theater_Text_NaokoSeen:
	.string "Yo{SE_M_DIVE}ar{SE_M_REVERSAL}quit{SE_M_REVERSAL}strong{SE_M_PERISH_SONG}Yo{SE_M_DIVE}helped\n"
	.string "m{SE_M_REVERSAL}i{SE_M_ATTRACT}th{SE_M_REVERSAL}ILE{SE_M_LOCK_ON}FOREST.\p"
	.string "I'{SE_M_MILK_DRINK}NAOKO--no{SE_M_SPIT_UP}s{SE_M_ATTRACT2}goo{SE_M_WATERFALL}with\n"
	.string "directions.\p"
	.string "{SE_M_HEAL_BELL}sa{SE_M_TWISTER}yo{SE_M_DIVE}defea{SE_M_SPIT_UP}Tea{SE_M_MILK_DRINK}Rocket\n"
	.string "whe{SE_M_ATTRACT}KUR{SE_M_SWIFT}wa{SE_M_GRASSWHISTLE}i{SE_M_ATTRACT}troubl{SE_M_REVERSAL}at\l"
	.string "th{SE_M_REVERSAL}SLOWPOK{SE_M_SWORDS_DANCE}WELL.\p"
	.string "Le{SE_M_SPIT_UP}m{SE_M_REVERSAL}challeng{SE_M_REVERSAL}yo{SE_M_DIVE}an{SE_M_WATERFALL}your\n"
	.string "POKéMON!$"

EcruteakCity_Theater_Text_MikiSeen:
	.string "You'r{SE_M_REVERSAL}quit{SE_M_REVERSAL}th{SE_M_REVERSAL}Trainer{SE_M_PERISH_SONG}I\n"
	.string "remembe{SE_M_SAND_TOMB}yo{SE_M_DIVE}chase{SE_M_WATERFALL}of{SE_M_ACID_ARMOR}that\l"
	.string "Rocke{SE_M_SPIT_UP}Grun{SE_M_SPIT_UP}fro{SE_M_MILK_DRINK}righ{SE_M_SPIT_UP}here.\p"
	.string "Than{SE_M_ENCORE2}yo{SE_M_DIVE}fo{SE_M_SAND_TOMB}that.\p"
	.string "Though{SE_M_SUPERSONIC}I'{SE_M_MILK_DRINK}{SE_M_CHARGE}Traine{SE_M_SAND_TOMB}too.\n"
	.string "Sh{SE_M_REVERSAL}wh{SE_M_ATTRACT2}know{SE_M_GRASSWHISTLE}th{SE_M_REVERSAL}mos{SE_M_SPIT_UP}speaks\l"
	.string "th{SE_M_REVERSAL}least!\p"
	.string "{SE_M_HEAL_BELL}a{SE_M_MILK_DRINK}MIKI--th{SE_M_REVERSAL}KIMON{SE_M_SOLAR_BEAM}GIRL!\p"
	.string "Le{SE_M_SPIT_UP}m{SE_M_REVERSAL}challeng{SE_M_REVERSAL}yo{SE_M_DIVE}an{SE_M_WATERFALL}your\n"
	.string "POKéMON!$"

EcruteakCity_Theater_Text_SayoSeen:
	.string "Excellen{SE_M_SPIT_UP}spirit{SE_M_DRAGON_RAGE}Yo{SE_M_DIVE}go{SE_M_SPIT_UP}me\n"
	.string "of{SE_M_ACID_ARMOR}th{SE_M_REVERSAL}ic{SE_M_REVERSAL}b{SE_M_YAWN}pushin{SE_M_SANDSTORM}me.\p"
	.string "{SE_M_HEAL_BELL}skat{SE_M_REVERSAL}i{SE_M_ATTRACT}sandals.\n"
	.string "{SE_M_HEAL_BELL}a{SE_M_MILK_DRINK}SAYO--th{SE_M_REVERSAL}KIMON{SE_M_SOLAR_BEAM}GIRL!\p"
	.string "{SE_M_HEAL_BELL}listene{SE_M_WATERFALL}i{SE_M_ATTRACT}th{SE_M_REVERSAL}DRAGON'{SE_M_SKETCH}DEN\n"
	.string "whe{SE_M_ATTRACT}yo{SE_M_DIVE}passe{SE_M_WATERFALL}th{SE_M_REVERSAL}Elder'{SE_M_GRASSWHISTLE}test.\p"
	.string "Le{SE_M_SPIT_UP}m{SE_M_REVERSAL}challeng{SE_M_REVERSAL}yo{SE_M_DIVE}an{SE_M_WATERFALL}your\n"
	.string "POKéMON!$"

EcruteakCity_Theater_Text_KuniSeen:
	.string "I'{SE_M_MILK_DRINK}th{SE_M_REVERSAL}las{SE_M_SPIT_UP}one.\p"
	.string "Yo{SE_M_DIVE}wer{SE_M_REVERSAL}dependabl{SE_M_REVERSAL}a{SE_M_SPIT_UP}the\n"
	.string "GOLDENRO{SE_M_FAINT_ATTACK}TUNNEL.\p"
	.string "I'{SE_M_MILK_DRINK}th{SE_M_REVERSAL}on{SE_M_REVERSAL}wh{SE_M_ATTRACT2}twirl{SE_M_GRASSWHISTLE}even\n"
	.string "underground--KUNI!\p"
	.string "{SE_M_HEAL_BELL}sa{SE_M_TWISTER}yo{SE_M_DIVE}thwar{SE_M_SPIT_UP}Rocket's\n"
	.string "pla{SE_M_ATTRACT}t{SE_M_ATTRACT2}tak{SE_M_REVERSAL}th{SE_M_REVERSAL}Radi{SE_M_ATTRACT2}Tower.\p"
	.string "No{SE_M_TWISTER}sho{SE_M_TWISTER}m{SE_M_REVERSAL}you{SE_M_SAND_TOMB}strength!\n"
	.string "Le{SE_M_SPIT_UP}m{SE_M_REVERSAL}challeng{SE_M_REVERSAL}yo{SE_M_DIVE}an{SE_M_WATERFALL}your\l"
	.string "POKéMON!$"

EcruteakCity_Theater_Text_ZukiDone:
	.string "W{SE_M_REVERSAL}wer{SE_M_REVERSAL}no{SE_M_SPIT_UP}wron{SE_M_SANDSTORM}abou{SE_M_SPIT_UP}you.\n"
	.string "Yo{SE_M_DIVE}ar{SE_M_REVERSAL}indee{SE_M_WATERFALL}worth{SE_M_YAWN}o{SE_M_ACID_ARMOR}this...\p"
	.string "Pleas{SE_M_REVERSAL}tak{SE_M_REVERSAL}it.$"

EcruteakCity_Theater_Text_GirlHooh:
	.string "Bi{SE_M_SANDSTORM}sisters{SE_M_DRAGON_RAGE}{SE_M_HEAL_BELL}jus{SE_M_SPIT_UP}sa{SE_M_TWISTER}the\n"
	.string "bi{SE_M_SANDSTORM}shado{SE_M_TWISTER}o{SE_M_ACID_ARMOR}{SE_M_CHARGE}POKéMO{SE_M_PSYBEAM2}over\l"
	.string "th{SE_M_REVERSAL}TI{SE_M_PSYBEAM2}TOWER!\p"
	.string "I{SE_M_SPIT_UP}coul{SE_M_WATERFALL}be...$"

EcruteakCity_Theater_Text_GirlLugia:
	.string "Bi{SE_M_SANDSTORM}sisters{SE_M_DRAGON_RAGE}{SE_M_HEAL_BELL}jus{SE_M_SPIT_UP}sa{SE_M_TWISTER}the\n"
	.string "bi{SE_M_SANDSTORM}shado{SE_M_TWISTER}o{SE_M_ACID_ARMOR}{SE_M_CHARGE}POKéMO{SE_M_PSYBEAM2}i{SE_M_ATTRACT}the\l"
	.string "WHIR{SE_M_BRICK_BREAK}ISLANDS{SE_M_ABSORB}waters!\p"
	.string "I{SE_M_SPIT_UP}coul{SE_M_WATERFALL}be...$"

EcruteakCity_Theater_Text_ZukiHooh:
	.string "ZUKI{SE_M_HEAT_WAVE}{PLAYER}!\n"
	.string "We'l{SE_M_BATON_PASS}b{SE_M_REVERSAL}a{SE_M_SPIT_UP}th{SE_M_REVERSAL}TI{SE_M_PSYBEAM2}TOWER.\n"
	.string "Se{SE_M_REVERSAL}yo{SE_M_DIVE}there!$"

EcruteakCity_Theater_Text_ZukiLugia:
	.string "ZUKI{SE_M_HEAT_WAVE}{PLAYER}!\n"
	.string "We'l{SE_M_BATON_PASS}b{SE_M_REVERSAL}a{SE_M_SPIT_UP}th{SE_M_REVERSAL}WHIR{SE_M_BRICK_BREAK}ISLANDS.\l"
	.string "Se{SE_M_REVERSAL}yo{SE_M_DIVE}there!$"

EcruteakCity_Theater_Text_KimonoDone:
	.string "W{SE_M_REVERSAL}ar{SE_M_REVERSAL}rehearsin{SE_M_SANDSTORM}{SE_M_CHARGE}dance.$"

EcruteakCity_Theater_Text_ZukiAfterAll:
	.string "Than{SE_M_ENCORE2}yo{SE_M_DIVE}fo{SE_M_SAND_TOMB}you{SE_M_SAND_TOMB}hel{SE_M_MORNING_SUN}the\n"
	.string "othe{SE_M_SAND_TOMB}day.\p"
	.string "You'v{SE_M_REVERSAL}show{SE_M_ATTRACT}th{SE_M_REVERSAL}bon{SE_M_WATERFALL}between\n"
	.string "peopl{SE_M_REVERSAL}ca{SE_M_ATTRACT}gro{SE_M_TWISTER}wit{SE_M_TRI_ATTACK}POKéMON...\p"
	.string "W{SE_M_REVERSAL}appreciat{SE_M_REVERSAL}ho{SE_M_TWISTER}yo{SE_M_DIVE}live{SE_M_WATERFALL}up\n"
	.string "t{SE_M_ATTRACT2}ou{SE_M_SAND_TOMB}hopes{SE_M_SUPERSONIC}{PLAYER}!\p"
	.string "I{SE_M_ACID_ARMOR}yo{SE_M_DIVE}learne{SE_M_WATERFALL}anythin{SE_M_SANDSTORM}from\n"
	.string "this{SE_M_SUPERSONIC}than{SE_M_ENCORE2}MR{SE_M_PERISH_SONG}POKéMO{SE_M_PSYBEAM2}and\l"
	.string "PROF.ELM...$"

EcruteakCity_Theater_Text_KimonoGirlsBeforeBattle:
	.string "Tal{SE_M_ENCORE2}t{SE_M_ATTRACT2}ZUK{SE_M_HEAL_BELL}i{SE_M_ATTRACT}th{SE_M_REVERSAL}middle\n"
	.string "whe{SE_M_ATTRACT}yo{SE_M_DIVE}ar{SE_M_REVERSAL}ready.$"

