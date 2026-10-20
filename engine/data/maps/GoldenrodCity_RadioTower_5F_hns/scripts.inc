@ Johto (data/maps/GoldenrodCity_RadioTower_5F_hns/scripts.inc), as built into the FireRed game.

GoldenrodCity_RadioTower_5F_hns_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, GoldenrodCity_RadioTower_5F_OnLoad
	.byte 0

GoldenrodCity_RadioTower_5F_OnLoad::
	call_if_eq JOHTO_VAR_GOLDENROD_CITY_STATE, 6, GoldenrodCity_RadioTower_5F_MapScript_HidePetrel
	end

GoldenrodCity_RadioTower_5F_MapScript_HidePetrel::
	clearflag JOHTO_FLAG_HIDE_GOLDENROD_RADIOTOWER_DIRECTOR
	setflag JOHTO_FLAG_HIDE_GOLDENROD_RADIOTOWER_PETREL
	return

GoldenrodCity_RadioTower_5F_EventScript_Petrel::
	lock
	goto_if_ge JOHTO_VAR_GOLDENROD_CITY_STATE, 10, GoldenrodCity_RadioTower_5F_EventScript_Director
	goto_if_eq VAR_FACING, DIR_SOUTH, GoldenrodCity_RadioTower_5F_EventScript_PetrelNorth
	faceplayer
	msgbox GoldenrodCity_RadioTower_5F_Text_FakeDirector1, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_DIRECTOR_OFFICE, GoldenrodCity_RadioTower_5F_Movement_Spin
	waitmovement 0
	setflag JOHTO_FLAG_HIDE_GOLDENROD_RADIOTOWER_DIRECTOR
	removeobject LOCALID_DIRECTOR_OFFICE
	clearflag JOHTO_FLAG_HIDE_GOLDENROD_RADIOTOWER_PETREL
	addobject LOCALID_PETREL_OFFICE
	applymovement LOCALID_PETREL_OFFICE, GoldenrodCity_RadioTower_5F_Movement_Spin2
	waitmovement 0
	msgbox GoldenrodCity_RadioTower_5F_Text_FakeDirector2, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_JOHTO_PETREL_2_HNS, GoldenrodCity_RadioTower_5F_Text_FakeDirectorWin
	msgbox GoldenrodCity_RadioTower_5F_Text_FakeDirectorAfter, MSGBOX_DEFAULT
	giveitem ITEM_BASEMENT_KEY
	setvar JOHTO_VAR_GOLDENROD_CITY_STATE, 7
	clearflag JOHTO_FLAG_HIDE_GOLDENROD_UNDERGROUND_KIMONO
	closemessage
	release
	end

GoldenrodCity_RadioTower_5F_EventScript_PetrelNorth::
	end

GoldenrodCity_RadioTower_5F_EventScript_Petrel2::
	lock
	faceplayer
	msgbox GoldenrodCity_RadioTower_5F_Text_FakeDirectorAfter2, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_RadioTower_5F_EventScript_Director::
	lock
	faceplayer
	msgbox GoldenrodCity_RadioTower_5F_Text_DirectorIntro, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_RadioTower_5F_Movement_Spin:
	face_right
	delay_8
	face_up
	delay_8
	face_left
	delay_8
	face_down
	delay_8
	face_right
	delay_4
	face_up
	delay_4
	face_left
	delay_4
	face_down
	delay_4
	face_right
	delay_2
	face_up
	delay_2
	face_left
	delay_2
	face_down
	step_end

GoldenrodCity_RadioTower_5F_Movement_Spin2:
	face_right
	delay_2
	face_up
	delay_2
	face_left
	delay_2
	face_down
	step_end

GoldenrodCity_RadioTower_5F_Text_FakeDirector1:
	.string "Y-you{SE_M_DRAGON_RAGE}Yo{SE_M_DIVE}cam{SE_M_REVERSAL}t{SE_M_ATTRACT2}rescu{SE_M_REVERSAL}me?$"

GoldenrodCity_RadioTower_5F_Text_FakeDirector2:
	.string "I{SE_M_GRASSWHISTLE}tha{SE_M_SPIT_UP}wha{SE_M_SPIT_UP}yo{SE_M_DIVE}wer{SE_M_REVERSAL}expecting?\p"
	.string "Wrong{SE_M_DRAGON_RAGE}I'{SE_M_MILK_DRINK}a{SE_M_ATTRACT}imposter!\p"
	.string "{SE_M_HEAL_BELL}pretende{SE_M_WATERFALL}t{SE_M_ATTRACT2}b{SE_M_REVERSAL}th{SE_M_REVERSAL}rea{SE_M_BATON_PASS}thin{SE_M_SANDSTORM}to\n"
	.string "prepar{SE_M_REVERSAL}fo{SE_M_SAND_TOMB}ou{SE_M_SAND_TOMB}takeover.\p"
	.string "D{SE_M_ATTRACT2}yo{SE_M_DIVE}wan{SE_M_SPIT_UP}t{SE_M_ATTRACT2}kno{SE_M_TWISTER}wher{SE_M_REVERSAL}w{SE_M_REVERSAL}hid\n"
	.string "th{SE_M_REVERSAL}rea{SE_M_BATON_PASS}DIRECTOR?\p"
	.string "Sure{SE_M_SUPERSONIC}I'l{SE_M_BATON_PASS}tel{SE_M_BATON_PASS}you{SE_M_PERISH_SONG}Bu{SE_M_SPIT_UP}onl{SE_M_YAWN}i{SE_M_ACID_ARMOR}you\n"
	.string "ca{SE_M_ATTRACT}bea{SE_M_SPIT_UP}me!$"

GoldenrodCity_RadioTower_5F_Text_FakeDirectorWin:
	.string "OK{SE_M_SUPERSONIC}OK{SE_M_PERISH_SONG}I'l{SE_M_BATON_PASS}tel{SE_M_BATON_PASS}yo{SE_M_DIVE}wher{SE_M_REVERSAL}h{SE_M_REVERSAL}is.$"

GoldenrodCity_RadioTower_5F_Text_FakeDirectorAfter:
	.string "Th{SE_M_REVERSAL}bos{SE_M_GRASSWHISTLE}stashe{SE_M_WATERFALL}th{SE_M_REVERSAL}DIRECTO{SE_M_MINIMIZE}in\n"
	.string "th{SE_M_REVERSAL}UNDERGROUN{SE_M_FAINT_ATTACK}WAREHOUSE.\p"
	.string "It'{SE_M_GRASSWHISTLE}a{SE_M_SPIT_UP}th{SE_M_REVERSAL}fa{SE_M_SAND_TOMB}en{SE_M_WATERFALL}o{SE_M_ACID_ARMOR}th{SE_M_REVERSAL}UNDER-\n"
	.string "GROUND.\p"
	.string "{SE_M_HEAL_BELL}a{SE_M_MILK_DRINK}{SE_M_CHARGE}nic{SE_M_REVERSAL}guy{SE_M_SUPERSONIC}{SE_M_HEAL_BELL}wil{SE_M_BATON_PASS}giv{SE_M_REVERSAL}you\n"
	.string "th{SE_M_REVERSAL}BASEMEN{SE_M_SWIFT}KE{SE_M_MOONLIGHT}t{SE_M_ATTRACT2}ge{SE_M_SPIT_UP}t{SE_M_ATTRACT2}the\l"
	.string "UNDERGROUN{SE_M_FAINT_ATTACK}WAREHOUSE.\p"
	.string "Bu{SE_M_SPIT_UP}{SE_M_HEAL_BELL}doub{SE_M_SPIT_UP}you'l{SE_M_BATON_PASS}ge{SE_M_SPIT_UP}tha{SE_M_SPIT_UP}far.$"

GoldenrodCity_RadioTower_5F_Text_FakeDirectorAfter2:
	.string "Th{SE_M_REVERSAL}bos{SE_M_GRASSWHISTLE}stashe{SE_M_WATERFALL}th{SE_M_REVERSAL}DIRECTO{SE_M_MINIMIZE}in\n"
	.string "th{SE_M_REVERSAL}UNDERGROUN{SE_M_FAINT_ATTACK}WAREHOUSE.\p"
	.string "It'{SE_M_GRASSWHISTLE}a{SE_M_SPIT_UP}th{SE_M_REVERSAL}fa{SE_M_SAND_TOMB}en{SE_M_WATERFALL}o{SE_M_ACID_ARMOR}th{SE_M_REVERSAL}UNDER-\n"
	.string "GROUND.\p"
	.string "Yo{SE_M_DIVE}ca{SE_M_ATTRACT}us{SE_M_REVERSAL}th{SE_M_REVERSAL}BASEMEN{SE_M_SWIFT}KE{SE_M_MOONLIGHT}to\n"
	.string "ge{SE_M_SPIT_UP}t{SE_M_ATTRACT2}th{SE_M_REVERSAL}UNDERGROUN{SE_M_FAINT_ATTACK}WAREHOUSE.\p"
	.string "Bu{SE_M_SPIT_UP}{SE_M_HEAL_BELL}doub{SE_M_SPIT_UP}you'l{SE_M_BATON_PASS}ge{SE_M_SPIT_UP}tha{SE_M_SPIT_UP}far.$"

GoldenrodCity_RadioTower_5F_EventScript_Ben::
	lock
	faceplayer
	msgbox GoldenrodCity_RadioTower_5F_Text_Ben, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodRaidoTower4_EventScript_ARIANA::
	trainerbattle_single 1500 GoldenrodCity_RadioTower_5F_Text_ExecutiveF1Seen, GoldenrodCity_RadioTower_5F_Text_ExecutiveF1Beaten
	msgbox GoldenrodCity_RadioTower_5F_Text_ExecutiveF1After, MSGBOX_AUTOCLOSE
	end

GoldenrodCity_RadioTower_5F_EventScript_Archer::
	lock
	faceplayer
	msgbox GoldenrodCity_RadioTower_5F_Text_RocketBossSeen, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_JOHTO_ARCHER_HNS, GoldenrodCity_RadioTower_5F_Text_RocketBossBeaten
	msgbox GoldenrodCity_RadioTower_5F_Text_RocketBossAfter, MSGBOX_DEFAULT
	delay 55
	closemessage
	fadescreen FADE_TO_BLACK
	setflag JOHTO_FLAG_HIDE_GOLDENROD_ROCKETS
	playse SE_EXIT
	setvar JOHTO_VAR_GOLDENROD_CITY_STATE, 10
	removeobject LOCALID_GOLDENROD_ARCHER
	removeobject LOCALID_GOLDENROD_ARIANA
	setflag JOHTO_FLAG_HIDE_GOLDENROD_RADIOTOWER_PETREL
	clearflag JOHTO_FLAG_HIDE_GOLDENROD_RADIOTOWER_DIRECTOR
	removeobject LOCALID_PETREL_OFFICE
	addobject LOCALID_DIRECTOR_STUDIO
	playbgm ((558 + 1) + 0x0E), TRUE
	delay 120
	fadescreen FADE_FROM_BLACK
	goto_if_eq VAR_FACING, DIR_SOUTH, GoldenrodCity_RadioTower_5F_EventScript_WingTop
	goto_if_eq VAR_FACING, DIR_WEST, GoldenrodCity_RadioTower_5F_EventScript_WingMid
	goto_if_eq VAR_FACING, DIR_NORTH, GoldenrodCity_RadioTower_5F_EventScript_WingBot
	release
	end

GoldenrodCity_RadioTower_5F_EventScript_WingTop::
	applymovement LOCALID_DIRECTOR_STUDIO, GoldenrodCity_RadioTower_5F_Movement_WalkToPlayerTop
	waitmovement 0
	turnobject OBJ_EVENT_ID_PLAYER, DIR_EAST
	msgbox GoldenrodCity_RadioTower_5F_Text_DirectorThanks, MSGBOX_DEFAULT
	closemessage
	call_if_eq JOHTO_VAR_LUGIA_OR_HOOH, 1, GoldenrodCity_RadioTower_5F_EventScript_GiveTidalWing
	call_if_eq JOHTO_VAR_LUGIA_OR_HOOH, 2, GoldenrodCity_RadioTower_5F_EventScript_GiveClearWing
	applymovement LOCALID_DIRECTOR_STUDIO, GoldenrodCity_RadioTower_5F_Movement_LeaveTop
	waitmovement 0
	goto GoldenrodCity_RadioTower_5F_Fakeout
	end

GoldenrodCity_RadioTower_5F_EventScript_WingMid::
	applymovement LOCALID_DIRECTOR_STUDIO, GoldenrodCity_RadioTower_5F_Movement_WalkToPlayerMid
	waitmovement 0
	turnobject OBJ_EVENT_ID_PLAYER, DIR_EAST
	msgbox GoldenrodCity_RadioTower_5F_Text_DirectorThanks, MSGBOX_DEFAULT
	closemessage
	call_if_eq JOHTO_VAR_LUGIA_OR_HOOH, 1, GoldenrodCity_RadioTower_5F_EventScript_GiveTidalWing
	call_if_eq JOHTO_VAR_LUGIA_OR_HOOH, 2, GoldenrodCity_RadioTower_5F_EventScript_GiveClearWing
	applymovement LOCALID_DIRECTOR_STUDIO, GoldenrodCity_RadioTower_5F_Movement_LeaveMid
	waitmovement 0
	goto GoldenrodCity_RadioTower_5F_Fakeout
	end

GoldenrodCity_RadioTower_5F_EventScript_WingBot::
	applymovement LOCALID_DIRECTOR_STUDIO, GoldenrodCity_RadioTower_5F_Movement_WalkToPlayerBot
	waitmovement 0
	turnobject OBJ_EVENT_ID_PLAYER, DIR_EAST
	msgbox GoldenrodCity_RadioTower_5F_Text_DirectorThanks, MSGBOX_DEFAULT
	closemessage
	call_if_eq JOHTO_VAR_LUGIA_OR_HOOH, 1, GoldenrodCity_RadioTower_5F_EventScript_GiveTidalWing
	call_if_eq JOHTO_VAR_LUGIA_OR_HOOH, 2, GoldenrodCity_RadioTower_5F_EventScript_GiveClearWing
	applymovement LOCALID_DIRECTOR_STUDIO, GoldenrodCity_RadioTower_5F_Movement_LeaveBot
	waitmovement 0
	goto GoldenrodCity_RadioTower_5F_Fakeout
	end

GoldenrodCity_RadioTower_5F_EventScript_GiveTidalWing::
	giveitem ITEM_SILVER_WING
	msgbox GoldenrodCity_RadioTower_5F_Text_DirectorTidalWingExplanation, MSGBOX_DEFAULT
	closemessage
	release
	return

GoldenrodCity_RadioTower_5F_EventScript_GiveClearWing::
	giveitem ITEM_RAINBOW_WING
	msgbox GoldenrodCity_RadioTower_5F_Text_DirectorClearWingExplanation, MSGBOX_DEFAULT
	closemessage
	release
	return

GoldenrodCity_RadioTower_5F_Fakeout::
	playse SE_PIN
	applymovement LOCALID_DIRECTOR_STUDIO, J_Common_Movement_ExclamationMark
	delay 60
	turnobject LOCALID_DIRECTOR_STUDIO, DIR_WEST
	msgbox GoldenrodCity_RadioTower_5F_Text_DirectorLegendary, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_DIRECTOR_STUDIO, GoldenrodCity_RadioTower_5F_Movement_Leave1
	waitmovement 0
	playse SE_PIN
	applymovement LOCALID_DIRECTOR_STUDIO, J_Common_Movement_ExclamationMark
	delay 60
	turnobject LOCALID_DIRECTOR_STUDIO, DIR_SOUTH
	msgbox GoldenrodCity_RadioTower_5F_Text_DirectorFakeout, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_DIRECTOR_STUDIO, GoldenrodCity_RadioTower_5F_Movement_Leave2
	waitmovement 0
	setflag JOHTO_FLAG_HIDE_GOLDENROD_RADIOTOWER_DIRECTOR_2
	removeobject LOCALID_DIRECTOR_STUDIO
	setvar JOHTO_VAR_MAHOGANY_TOWN_STATE, 17
	release
	end

GoldenrodCity_RadioTower_5F_EventScript_Trigger_NPCS::
	clearflag JOHTO_FLAG_HIDE_GOLDENROD_NPCS
	setvar JOHTO_VAR_GOLDENROD_CITY_STATE, 11
	end

GoldenrodCity_RadioTower_5F_Movement_WalkToPlayerTop:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	step_end

GoldenrodCity_RadioTower_5F_Movement_LeaveTop:
	walk_right
	walk_right
	walk_right
	step_end

GoldenrodCity_RadioTower_5F_Movement_WalkToPlayerMid:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	step_end

GoldenrodCity_RadioTower_5F_Movement_LeaveMid:
	walk_right
	walk_right
	step_end

GoldenrodCity_RadioTower_5F_Movement_WalkToPlayerBot:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	step_end

GoldenrodCity_RadioTower_5F_Movement_LeaveBot:
	walk_right
	walk_right
	walk_right
	step_end

GoldenrodCity_RadioTower_5F_Movement_Leave1:
	walk_up
	walk_up
	step_end

GoldenrodCity_RadioTower_5F_Movement_Leave2:
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

GoldenrodCity_RadioTower_5F_Text_ExecutiveF1Seen:
	.string "Remembe{SE_M_SAND_TOMB}m{SE_M_REVERSAL}fro{SE_M_MILK_DRINK}th{SE_M_REVERSAL}HIDEOU{SE_M_SWIFT}in\n"
	.string "MAHOGAN{SE_M_MOONLIGHT}TOWN?\p"
	.string "M{SE_M_YAWN}bos{SE_M_GRASSWHISTLE}scolde{SE_M_WATERFALL}m{SE_M_REVERSAL}bu{SE_M_SPIT_UP}I'{SE_M_MILK_DRINK}stronger.\p"
	.string "{SE_M_HEAL_BELL}los{SE_M_SPIT_UP}then{SE_M_SUPERSONIC}bu{SE_M_SPIT_UP}{SE_M_HEAL_BELL}won'{SE_M_SPIT_UP}thi{SE_M_GRASSWHISTLE}time.$"

GoldenrodCity_RadioTower_5F_Text_ExecutiveF1Beaten:
	.string "Thi{SE_M_GRASSWHISTLE}can'{SE_M_SPIT_UP}b{SE_M_REVERSAL}happening!\p"
	.string "{SE_M_HEAL_BELL}fough{SE_M_SPIT_UP}hard{SE_M_SUPERSONIC}bu{SE_M_SPIT_UP}{SE_M_HEAL_BELL}stil{SE_M_BATON_PASS}lost…\p"
	.string "I'{SE_M_MILK_DRINK}s{SE_M_ATTRACT2}sorr{SE_M_YAWN}GIOVANNI…$"

GoldenrodCity_RadioTower_5F_Text_ExecutiveF1After:
	.string "{PLAYER}{SE_M_SUPERSONIC}isn'{SE_M_SPIT_UP}it?\p"
	.string "{SE_M_BONEMERANG}bra{SE_M_SPIT_UP}lik{SE_M_REVERSAL}yo{SE_M_DIVE}won'{SE_M_SPIT_UP}appreciate\n"
	.string "th{SE_M_REVERSAL}magnificenc{SE_M_REVERSAL}o{SE_M_ACID_ARMOR}TEA{SE_M_GIGA_DRAIN}ROCKET.\p"
	.string "That'{SE_M_GRASSWHISTLE}to{SE_M_ATTRACT2}bad{SE_M_PERISH_SONG}{SE_M_HEAL_BELL}reall{SE_M_YAWN}admire\n"
	.string "you{SE_M_SAND_TOMB}power.$"

GoldenrodCity_RadioTower_5F_Text_RocketBossSeen:
	.string "Oh{SE_M_SING}Yo{SE_M_DIVE}manage{SE_M_WATERFALL}t{SE_M_ATTRACT2}ge{SE_M_SPIT_UP}thi{SE_M_GRASSWHISTLE}far?\p"
	.string "Yo{SE_M_DIVE}mus{SE_M_SPIT_UP}b{SE_M_REVERSAL}quit{SE_M_REVERSAL}th{SE_M_REVERSAL}trainer.\p"
	.string "W{SE_M_REVERSAL}inten{SE_M_WATERFALL}t{SE_M_ATTRACT2}tak{SE_M_REVERSAL}ove{SE_M_SAND_TOMB}thi{SE_M_GRASSWHISTLE}RADIO\n"
	.string "STATIO{SE_M_PSYBEAM2}an{SE_M_WATERFALL}announc{SE_M_REVERSAL}ou{SE_M_SAND_TOMB}comeback.\p"
	.string "Tha{SE_M_SPIT_UP}shoul{SE_M_WATERFALL}brin{SE_M_SANDSTORM}ou{SE_M_SAND_TOMB}bos{SE_M_GRASSWHISTLE}GIOVANNI\n"
	.string "bac{SE_M_ENCORE2}fro{SE_M_MILK_DRINK}hi{SE_M_GRASSWHISTLE}solitar{SE_M_YAWN}training.\p"
	.string "W{SE_M_REVERSAL}ar{SE_M_REVERSAL}goin{SE_M_SANDSTORM}t{SE_M_ATTRACT2}regai{SE_M_ATTRACT}ou{SE_M_SAND_TOMB}former\n"
	.string "glory...\p"
	.string "{SE_M_HEAL_BELL}won'{SE_M_SPIT_UP}allo{SE_M_TWISTER}yo{SE_M_DIVE}t{SE_M_ATTRACT2}interfer{SE_M_REVERSAL}with\n"
	.string "ou{SE_M_SAND_TOMB}meticulou{SE_M_GRASSWHISTLE}plans!$"

GoldenrodCity_RadioTower_5F_Text_RocketBossBeaten:
	.string "No{SE_M_DRAGON_RAGE}Forgiv{SE_M_REVERSAL}me{SE_M_SUPERSONIC}GIOVANNI!$"

GoldenrodCity_RadioTower_5F_Text_RocketBossAfter:
	.string "Ho{SE_M_TWISTER}coul{SE_M_WATERFALL}thi{SE_M_GRASSWHISTLE}be?\p"
	.string "Ou{SE_M_SAND_TOMB}dream{SE_M_GRASSWHISTLE}hav{SE_M_REVERSAL}com{SE_M_REVERSAL}t{SE_M_ATTRACT2}naught.\p"
	.string "{SE_M_HEAL_BELL}wasn'{SE_M_SPIT_UP}u{SE_M_MORNING_SUN}t{SE_M_ATTRACT2}th{SE_M_REVERSAL}tas{SE_M_ENCORE2}afte{SE_M_SAND_TOMB}all.\p"
	.string "Lik{SE_M_REVERSAL}GIOVANN{SE_M_HEAL_BELL}di{SE_M_WATERFALL}befor{SE_M_REVERSAL}me{SE_M_SUPERSONIC}{SE_M_HEAL_BELL}will\n"
	.string "disban{SE_M_WATERFALL}TEA{SE_M_GIGA_DRAIN}ROCKE{SE_M_SWIFT}her{SE_M_REVERSAL}today.\p"
	.string "Farewell.$"

GoldenrodCity_RadioTower_5F_Text_DirectorThanks:
	.string "DIRECTOR{SE_M_HEAT_WAVE}{PLAYER}{SE_M_SUPERSONIC}than{SE_M_ENCORE2}you!\p"
	.string "You{SE_M_SAND_TOMB}courageou{SE_M_GRASSWHISTLE}action{SE_M_GRASSWHISTLE}hav{SE_M_REVERSAL}saved\n"
	.string "POKéMO{SE_M_PSYBEAM2}nationwide.\p"
	.string "{SE_M_HEAL_BELL}kno{SE_M_TWISTER}it'{SE_M_GRASSWHISTLE}no{SE_M_SPIT_UP}much{SE_M_SUPERSONIC}bu{SE_M_SPIT_UP}please\n"
	.string "tak{SE_M_REVERSAL}this.$"

GoldenrodCity_RadioTower_5F_Text_DirectorClearWingExplanation:
	.string "Ther{SE_M_REVERSAL}use{SE_M_WATERFALL}t{SE_M_ATTRACT2}b{SE_M_REVERSAL}{SE_M_CHARGE}towe{SE_M_SAND_TOMB}righ{SE_M_SPIT_UP}here\n"
	.string "i{SE_M_ATTRACT}GOLDENRO{SE_M_FAINT_ATTACK}CITY.\p"
	.string "Bu{SE_M_SPIT_UP}i{SE_M_SPIT_UP}wa{SE_M_GRASSWHISTLE}ol{SE_M_WATERFALL}an{SE_M_WATERFALL}creaky.\p"
	.string "S{SE_M_ATTRACT2}w{SE_M_REVERSAL}replace{SE_M_WATERFALL}i{SE_M_SPIT_UP}wit{SE_M_TRI_ATTACK}ou{SE_M_SAND_TOMB}RADIO\n"
	.string "TOWER.\p"
	.string "W{SE_M_REVERSAL}du{SE_M_SANDSTORM}u{SE_M_MORNING_SUN}tha{SE_M_SPIT_UP}win{SE_M_SANDSTORM}during\n"
	.string "construction.\p"
	.string "{SE_M_HEAL_BELL}hear{SE_M_WATERFALL}tha{SE_M_SPIT_UP}al{SE_M_BATON_PASS}sort{SE_M_GRASSWHISTLE}o{SE_M_ACID_ARMOR}POKéMON\n"
	.string "live{SE_M_WATERFALL}i{SE_M_ATTRACT}GOLDENRO{SE_M_FAINT_ATTACK}i{SE_M_ATTRACT}th{SE_M_REVERSAL}past.\p"
	.string "Perhaps…\p"
	.string "Tha{SE_M_SPIT_UP}win{SE_M_SANDSTORM}ha{SE_M_GRASSWHISTLE}som{SE_M_REVERSAL}connectio{SE_M_ATTRACT}t{SE_M_ATTRACT2}the\n"
	.string "TI{SE_M_PSYBEAM2}TOWE{SE_M_MINIMIZE}i{SE_M_ATTRACT}ECRUTEA{SE_M_SNORE}CITY…\p"
	.string "OK{SE_M_SUPERSONIC}{SE_M_HEAL_BELL}bette{SE_M_SAND_TOMB}g{SE_M_ATTRACT2}t{SE_M_ATTRACT2}m{SE_M_YAWN}OFFICE.$"

GoldenrodCity_RadioTower_5F_Text_DirectorTidalWingExplanation:
	.string "Ther{SE_M_REVERSAL}use{SE_M_WATERFALL}t{SE_M_ATTRACT2}b{SE_M_REVERSAL}{SE_M_CHARGE}towe{SE_M_SAND_TOMB}righ{SE_M_SPIT_UP}here\n"
	.string "i{SE_M_ATTRACT}GOLDENRO{SE_M_FAINT_ATTACK}CITY.\p"
	.string "Bu{SE_M_SPIT_UP}i{SE_M_SPIT_UP}wa{SE_M_GRASSWHISTLE}ol{SE_M_WATERFALL}an{SE_M_WATERFALL}creaky.\p"
	.string "S{SE_M_ATTRACT2}w{SE_M_REVERSAL}replace{SE_M_WATERFALL}i{SE_M_SPIT_UP}wit{SE_M_TRI_ATTACK}ou{SE_M_SAND_TOMB}RADIO\n"
	.string "TOWER.\p"
	.string "W{SE_M_REVERSAL}du{SE_M_SANDSTORM}u{SE_M_MORNING_SUN}tha{SE_M_SPIT_UP}win{SE_M_SANDSTORM}during\n"
	.string "construction.\p"
	.string "{SE_M_HEAL_BELL}hear{SE_M_WATERFALL}tha{SE_M_SPIT_UP}al{SE_M_BATON_PASS}sort{SE_M_GRASSWHISTLE}o{SE_M_ACID_ARMOR}POKéMON\n"
	.string "live{SE_M_WATERFALL}i{SE_M_ATTRACT}GOLDENRO{SE_M_FAINT_ATTACK}i{SE_M_ATTRACT}th{SE_M_REVERSAL}past.\p"
	.string "Perhaps…\p"
	.string "Tha{SE_M_SPIT_UP}win{SE_M_SANDSTORM}ha{SE_M_GRASSWHISTLE}som{SE_M_REVERSAL}connectio{SE_M_ATTRACT}t{SE_M_ATTRACT2}the\n"
	.string "WHIR{SE_M_BRICK_BREAK}ISLAND{SE_M_SKETCH}nea{SE_M_SAND_TOMB}CIANWOO{SE_M_FAINT_ATTACK}CITY…\p"
	.string "OK{SE_M_SUPERSONIC}{SE_M_HEAL_BELL}bette{SE_M_SAND_TOMB}g{SE_M_ATTRACT2}t{SE_M_ATTRACT2}m{SE_M_YAWN}OFFICE.$"

GoldenrodCity_RadioTower_5F_Text_DirectorLegendary:
	.string "Ah!\p"
	.string "Tha{SE_M_SPIT_UP}remind{SE_M_GRASSWHISTLE}me…\p"
	.string "Tha{SE_M_SPIT_UP}win{SE_M_SANDSTORM}{SE_M_HEAL_BELL}gav{SE_M_REVERSAL}you..{SE_M_PERISH_SONG}{SE_M_HEAL_BELL}think\n"
	.string "it'{SE_M_GRASSWHISTLE}relate{SE_M_WATERFALL}t{SE_M_ATTRACT2}th{SE_M_REVERSAL}LEGENDARY\l"
	.string "POKéMON.\p"
	.string "But{SE_M_DRAGON_RAGE}Th{SE_M_REVERSAL}LEGENDAR{SE_M_MOONLIGHT}POKéMO{SE_M_PSYBEAM2}won't\n"
	.string "appea{SE_M_SAND_TOMB}wit{SE_M_TRI_ATTACK}jus{SE_M_SPIT_UP}tha{SE_M_SPIT_UP}wing...\p"
	.string "Apparentl{SE_M_YAWN}ther{SE_M_REVERSAL}i{SE_M_GRASSWHISTLE}somethin{SE_M_SANDSTORM}else\n"
	.string "yo{SE_M_DIVE}need..{SE_M_PERISH_SONG}O{SE_M_SAND_TOMB}somethin{SE_M_SANDSTORM}lik{SE_M_REVERSAL}that.\p"
	.string "{SE_M_HEAL_BELL}wonde{SE_M_SAND_TOMB}wha{SE_M_SPIT_UP}i{SE_M_SPIT_UP}was...\p"
	.string "{SE_M_HEAL_BELL}can'{SE_M_SPIT_UP}remember.$"

GoldenrodCity_RadioTower_5F_Text_DirectorFakeout:
	.string "Ar{SE_M_REVERSAL}yo{SE_M_DIVE}expectin{SE_M_SANDSTORM}something?\n"
	.string "Thi{SE_M_GRASSWHISTLE}i{SE_M_GRASSWHISTLE}wha{SE_M_SPIT_UP}the{SE_M_YAWN}cal{SE_M_BATON_PASS}FAK{SE_M_SWORDS_DANCE}OUT.\p"
	.string "{SE_M_HEAL_BELL}reall{SE_M_YAWN}mus{SE_M_SPIT_UP}g{SE_M_ATTRACT2}bac{SE_M_ENCORE2}t{SE_M_ATTRACT2}m{SE_M_YAWN}OFFICE\n"
	.string "thi{SE_M_GRASSWHISTLE}time{SE_M_PERISH_SONG}Se{SE_M_REVERSAL}ya!$"

GoldenrodCity_RadioTower_5F_Text_DirectorIntro:
	.string "DIRECTOR{SE_M_HEAT_WAVE}Hello{SE_M_SUPERSONIC}{PLAYER}!\p"
	.string "Yo{SE_M_DIVE}know{SE_M_SUPERSONIC}{SE_M_HEAL_BELL}lov{SE_M_REVERSAL}POKéMON.\p"
	.string "{SE_M_HEAL_BELL}buil{SE_M_SPIT_UP}thi{SE_M_GRASSWHISTLE}RADI{SE_M_SOLAR_BEAM}TOWE{SE_M_MINIMIZE}s{SE_M_ATTRACT2}{SE_M_HEAL_BELL}could\n"
	.string "expres{SE_M_GRASSWHISTLE}m{SE_M_YAWN}lov{SE_M_REVERSAL}o{SE_M_ACID_ARMOR}POKéMON.\p"
	.string "I{SE_M_SPIT_UP}woul{SE_M_WATERFALL}b{SE_M_REVERSAL}nic{SE_M_REVERSAL}i{SE_M_ACID_ARMOR}peopl{SE_M_REVERSAL}enjoyed\n"
	.string "ou{SE_M_SAND_TOMB}programs.$"

GoldenrodCity_RadioTower_5F_Text_Ben:
	.string "BEN{SE_M_HEAT_WAVE}D{SE_M_ATTRACT2}yo{SE_M_DIVE}liste{SE_M_ATTRACT}t{SE_M_ATTRACT2}ou{SE_M_SAND_TOMB}music?$"

GoldenrodCity_RadioTower_5F_Text_DirectorOfficeSign:
	.string "5{SE_M_LEER}DIRECTOR'{SE_M_SKETCH}{MUS_DUMMY}OFFICE$"

GoldenrodCity_RadioTower_5F_Text_Studio1Sign:
	.string "5{SE_M_LEER}STUDI{SE_M_SOLAR_BEAM}1$"

