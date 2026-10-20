@ Johto (data/maps/BlackthornCity_hns/scripts.inc), as built into the FireRed game.

BlackthornCity_hns_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, BlackthornCity_OnFrame
	map_script MAP_SCRIPT_ON_LOAD, BlackthornCity_OnLoad
	map_script MAP_SCRIPT_ON_TRANSITION, BlackthornCity_EventScript_CityEnter
	map_script MAP_SCRIPT_ON_RESUME, J_SetTimeEncounters
	.byte 0

BlackthornCity_OnLoad::
	goto_if_unset JOHTO_FLAG_BADGE05_GET, BlackThornCity_EventScript_MoveGymBoy
	goto_if_unset JOHTO_FLAG_BADGE06_GET, BlackThornCity_EventScript_MoveGymBoy
	goto_if_unset JOHTO_FLAG_BADGE07_GET, BlackThornCity_EventScript_MoveGymBoy
	end

BlackThornCity_EventScript_MoveGymBoy::
	setobjectxyperm LOCALID_BLACKTHORN_BOY, 24, 27
	end

BlackthornCity_OnFrame::
	map_script_2 JOHTO_VAR_BLACKTHORN_CITY_STATE, 4, BlackthornCity_EventScript_Call
	.2byte 0

BlackthornCity_EventScript_CityEnter::
	setflag JOHTO_FLAG_VISITED_BLACKTHORN_CITY
	callnative SetTimeBasedEncounters
	end

BlackthornCity_EventScript_Call::
	lock
	setspeaker BlackthornCity_Text_ElmName
	pokenavcall BlackthornCity_Text_ElmCall
	waitmessage
	delay 30
	setvar JOHTO_VAR_BLACKTHORN_CITY_STATE, 5
	setvar JOHTO_VAR_NEWBARKTOWN_LABSTATE, 7
	release
	end

BlackthornCity_Text_ElmName:
	.string "PROF.ELM$"

BlackthornCity_Text_BaobaCall:
	.string "WARDE{SE_M_PSYBEAM2}BAOBA{SE_M_HEAT_WAVE}{PLAYER}!\p"
	.string "Thi{SE_M_GRASSWHISTLE}i{SE_M_GRASSWHISTLE}WARDE{SE_M_PSYBEAM2}BAOBA.\p"
	.string "I'{SE_M_MILK_DRINK}callin{SE_M_SANDSTORM}t{SE_M_ATTRACT2}tel{SE_M_BATON_PASS}yo{SE_M_DIVE}that\n"
	.string "th{SE_M_REVERSAL}SAFAR{SE_M_HEAL_BELL}ZON{SE_M_SWORDS_DANCE}ha{SE_M_GRASSWHISTLE}expanded!\p"
	.string "Pleas{SE_M_REVERSAL}com{SE_M_REVERSAL}visit!$"

BlackthornCity_Text_ElmCall:
	.string "PROF.ELM{SE_M_HEAT_WAVE}Hello{SE_M_SUPERSONIC}{PLAYER}?\p"
	.string "{SE_M_HEAL_BELL}hav{SE_M_REVERSAL}somethin{SE_M_SANDSTORM}her{SE_M_REVERSAL}fo{SE_M_SAND_TOMB}you.\n"
	.string "Coul{SE_M_WATERFALL}yo{SE_M_DIVE}swin{SE_M_SANDSTORM}b{SE_M_YAWN}m{SE_M_YAWN}LAB?\p"
	.string "Se{SE_M_REVERSAL}yo{SE_M_DIVE}later!$"

BlackThornCity_EventScript_Sage::
	lock
	faceplayer
	goto_if_eq JOHTO_VAR_BLACKTHORN_CITY_STATE, 1, BlackThornCity_EventScript_SageRefuse
	msgbox BlackthornGrampsGrantsEntryText, MSGBOX_DEFAULT
	closemessage
	release
	end

BlackThornCity_EventScript_SageRefuse::
	msgbox BlackthornGrampsRefusesEntryText, MSGBOX_DEFAULT
	closemessage
	release
	end

BlackThornCity_Trigger_Sage::
	lock
	turnobject LOCALID_BLACKTHORN_SAGE, DIR_EAST
	msgbox BlackthornGrampsRefusesEntryText, MSGBOX_DEFAULT
	closemessage
	applymovement 255 J_Common_Movement_WalkDown1
	waitmovement 0
	turnobject LOCALID_BLACKTHORN_SAGE, DIR_SOUTH
	release
	end

BlackthornCity_EventScript_GymBoy::
	lock
	faceplayer
	goto_if_unset JOHTO_FLAG_BADGE05_GET, BlackThornCity_EventScript_GymBoyNotReady
	goto_if_unset JOHTO_FLAG_BADGE06_GET, BlackThornCity_EventScript_GymBoyNotReady
	goto_if_unset JOHTO_FLAG_BADGE07_GET, BlackThornCity_EventScript_GymBoyNotReady
	goto_if_eq JOHTO_VAR_BLACKTHORN_CITY_STATE, 1, BlackThornCity_EventScript_GymBoyBefore
	msgbox BlackthornCity_Text_ClairIsBeaten, MSGBOX_DEFAULT
	closemessage
	release
	end

BlackThornCity_EventScript_GymBoyNotReady::
	msgbox BlackthornCity_Text_ClairNotReady, MSGBOX_DEFAULT
	closemessage
	release
	end

BlackThornCity_EventScript_GymBoyBefore::
	msgbox BlackthornCity_Text_ClairIsIn, MSGBOX_DEFAULT
	closemessage
	release
	end

BlackthornCity_EventScript_BlackBelt::
	msgbox BlackBeltText_VoicesInMyHead, MSGBOX_NPC
	end

BlackthornCity_EventScript_CoolTrainerF::
	msgbox BlackthornCooltrainerF1Text, MSGBOX_NPC
	end

BlackthornCity_EventScript_Youngster::
	msgbox BlackthornYoungsterText, MSGBOX_NPC
	end

BlackthornCity_EventScript_CoolTrainerF2::
	msgbox BlackthornCooltrainerF2Text, MSGBOX_NPC
	end

BlackthornCity_EventScript_CitySign::
	msgbox BlackthornCitySignText, MSGBOX_SIGN
	end

BlackthornCity_EventScript_GymSign::
	msgbox BlackthornGymSignText, MSGBOX_SIGN
	end

BlackthornCity_EventScript_MoveHouseSign::
	msgbox BlackthornCity_Text_MoveDeletersHouseSign, MSGBOX_SIGN
	end

BlackthornCity_EventScript_DragonsDenSign::
	msgbox BlackthornCity_Text_DragonDenSign, MSGBOX_SIGN
	end

BlackthornCity_EventScript_Santos::
	lock
	faceplayer
	goto_if_set JOHTO_FLAG_GOT_SPELL_TAG, BlackthornCity_EventScript_SantosCompleted
	msgbox BlackthornCity_MeetSantosText, MSGBOX_DEFAULT
	closemessage
	multichoice 20, 0, MULTI_DAYS_OF_WEEK, FALSE
	switch VAR_RESULT
	case 0, BlackthornCity_EventScript_SantosNope
	case 1, BlackthornCity_EventScript_SantosNope
	case 2, BlackthornCity_EventScript_SantosNope
	case 3, BlackthornCity_EventScript_SantosNope
	case 4, BlackthornCity_EventScript_SantosNope
	case 5, BlackthornCity_EventScript_SantosNope
	case 6, BlackthornCity_EventScript_SantosYes
	case 7 BlackthornCity_EventScript_SantosCancel
	case MULTI_B_PRESSED, BlackthornCity_EventScript_SantosCancel
	closemessage
	release
	end

BlackthornCity_EventScript_SantosYes::
	msgbox BlackthornCity_SantosGivesGiftText, MSGBOX_DEFAULT
	giveitem ITEM_SPELL_TAG
	goto_if_eq VAR_RESULT, FALSE, J_Common_EventScript_ShowBagIsFull
	setflag JOHTO_FLAG_GOT_SPELL_TAG
	msgbox BlackthornCity_SantosGaveGiftText, MSGBOX_DEFAULT
	closemessage
	release
	end

BlackthornCity_EventScript_SantosNope::
	msgbox BlackthornCity_SantosNopeText, MSGBOX_DEFAULT
	closemessage
	release
	end

BlackthornCity_EventScript_SantosCancel::
	closemessage
	release
	end

BlackthornCity_EventScript_SantosCompleted::
	msgbox BlackthornCity_SantosSaturdayText, MSGBOX_DEFAULT
	closemessage
	release
	end

BlackthornCity_Text_ClairNotReady:
	.string "CLAIR{SE_M_SUPERSONIC}ou{SE_M_SAND_TOMB}GY{SE_M_GIGA_DRAIN}LEADER{SE_M_SUPERSONIC}ha{SE_M_GRASSWHISTLE}been\n"
	.string "followin{SE_M_SANDSTORM}you{SE_M_SAND_TOMB}progress.\p"
	.string "However{SE_M_SUPERSONIC}sh{SE_M_REVERSAL}onl{SE_M_YAWN}battle{SE_M_GRASSWHISTLE}trainers\n"
	.string "wh{SE_M_ATTRACT2}alread{SE_M_YAWN}hav{SE_M_REVERSAL}{SE_M_MIST}badges.$"

BlackthornCity_Text_ClairIsIn:
	.string "CLAIR{SE_M_SUPERSONIC}ou{SE_M_SAND_TOMB}GY{SE_M_GIGA_DRAIN}LEADER{SE_M_SUPERSONIC}i{SE_M_GRASSWHISTLE}waiting\n"
	.string "fo{SE_M_SAND_TOMB}you.\p"
	.string "However{SE_M_SUPERSONIC}i{SE_M_SPIT_UP}woul{SE_M_WATERFALL}b{SE_M_REVERSAL}impossibl{SE_M_REVERSAL}for\n"
	.string "{SE_M_CHARGE}run-of-the-mil{SE_M_BATON_PASS}traine{SE_M_SAND_TOMB}t{SE_M_ATTRACT2}win.$"

BlackthornCity_Text_ClairIsBeaten:
	.string "Yo{SE_M_DIVE}defeate{SE_M_WATERFALL}CLAIR?\p"
	.string "That'{SE_M_GRASSWHISTLE}amazing!\p"
	.string "I'v{SE_M_REVERSAL}neve{SE_M_SAND_TOMB}hear{SE_M_WATERFALL}o{SE_M_ACID_ARMOR}he{SE_M_SAND_TOMB}losin{SE_M_SANDSTORM}to\n"
	.string "anyon{SE_M_REVERSAL}othe{SE_M_SAND_TOMB}tha{SE_M_ATTRACT}LANCE.$"

BlackthornGrampsRefusesEntryText:
	.string "No{SE_M_PERISH_SONG}Onl{SE_M_YAWN}chose{SE_M_ATTRACT}trainer{SE_M_GRASSWHISTLE}ma{SE_M_YAWN}train\n"
	.string "here.\p"
	.string "Pleas{SE_M_REVERSAL}leave.$"

BlackthornGrampsGrantsEntryText:
	.string "I{SE_M_ACID_ARMOR}CLAI{SE_M_MINIMIZE}allow{SE_M_GRASSWHISTLE}it{SE_M_SUPERSONIC}he{SE_M_SAND_TOMB}grand-\n"
	.string "father--ou{SE_M_SAND_TOMB}MASTER--wil{SE_M_BATON_PASS}also.\p"
	.string "Yo{SE_M_DIVE}ma{SE_M_YAWN}enter.$"

BlackBeltText_VoicesInMyHead:
	.string "Arooo{SE_M_DRAGON_RAGE}Voice{SE_M_GRASSWHISTLE}i{SE_M_ATTRACT}m{SE_M_YAWN}head!\p"
	.string "Huh{SE_M_SING}I'{SE_M_MILK_DRINK}listenin{SE_M_SANDSTORM}t{SE_M_ATTRACT2}m{SE_M_YAWN}radio!$"

BlackthornCooltrainerF1Text:
	.string "Ar{SE_M_REVERSAL}yo{SE_M_DIVE}goin{SE_M_SANDSTORM}t{SE_M_ATTRACT2}mak{SE_M_REVERSAL}you{SE_M_SAND_TOMB}POKéMON\n"
	.string "remembe{SE_M_SAND_TOMB}som{SE_M_REVERSAL}moves?$"

BlackthornYoungsterText:
	.string "Drago{SE_M_ATTRACT}master{SE_M_GRASSWHISTLE}al{SE_M_BATON_PASS}com{SE_M_REVERSAL}fro{SE_M_MILK_DRINK}th{SE_M_REVERSAL}city\n"
	.string "o{SE_M_ACID_ARMOR}BLACKTHORN.$"

BlackthornCity_MeetSantosText:
	.string "SANTOS{SE_M_HEAT_WAVE}…\p"
	.string "I'{SE_M_MILK_DRINK}SANTO{SE_M_SKETCH}o{SE_M_ACID_ARMOR}th{SE_M_REVERSAL}weekda{SE_M_YAWN}family.\p"
	.string "Tak{SE_M_REVERSAL}{SE_M_CHARGE}guess.$"

BlackthornCity_SantosGivesGiftText:
	.string "Yo{SE_M_DIVE}ca{SE_M_ATTRACT}hav{SE_M_REVERSAL}this…$"

BlackthornCity_SantosGaveGiftText:
	.string "SANTOS{SE_M_HEAT_WAVE}…\p"
	.string "SPEL{SE_M_BRICK_BREAK}TAG…\p"
	.string "GHOST-typ{SE_M_REVERSAL}move{SE_M_GRASSWHISTLE}ge{SE_M_SPIT_UP}stronger…\p"
	.string "I{SE_M_SPIT_UP}wil{SE_M_BATON_PASS}frighte{SE_M_ATTRACT}you…$"

BlackthornCity_SantosSaturdayText:
	.string "SANTOS{SE_M_HEAT_WAVE}…\p"
	.string "Se{SE_M_REVERSAL}yo{SE_M_DIVE}agai{SE_M_ATTRACT}o{SE_M_ATTRACT}anothe{SE_M_SAND_TOMB}Saturday…\p"
	.string "{SE_M_HEAL_BELL}won'{SE_M_SPIT_UP}hav{SE_M_REVERSAL}an{SE_M_YAWN}mor{SE_M_REVERSAL}gifts…$"

BlackthornCity_SantosNopeText:
	.string "SANTOS{SE_M_HEAT_WAVE}No.$"

BlackthornCooltrainerF2Text:
	.string "Wow{SE_M_SUPERSONIC}yo{SE_M_DIVE}cam{SE_M_REVERSAL}throug{SE_M_TRI_ATTACK}th{SE_M_REVERSAL}IC{SE_M_SWORDS_DANCE}PATH?\p"
	.string "Yo{SE_M_DIVE}mus{SE_M_SPIT_UP}b{SE_M_REVERSAL}{SE_M_CHARGE}rea{SE_M_BATON_PASS}hotsho{SE_M_SPIT_UP}trainer!$"

BlackthornCitySignText:
	.string "BLACKTHOR{SE_M_PSYBEAM2}CITY\p"
	.string "{SE_M_BONEMERANG}Quie{SE_M_SPIT_UP}Mountai{SE_M_ATTRACT}Retreat$"

BlackthornGymSignText:
	.string "BLACKTHOR{SE_M_PSYBEAM2}CIT{SE_M_MOONLIGHT}POKéMO{SE_M_PSYBEAM2}GYM\n"
	.string "LEADER{SE_M_HEAT_WAVE}CLAIR\p"
	.string "Th{SE_M_REVERSAL}Blesse{SE_M_WATERFALL}Use{SE_M_SAND_TOMB}o{SE_M_ACID_ARMOR}Drago{SE_M_ATTRACT}POKéMON$"

BlackthornCity_Text_MoveDeletersHouseSign:
	.string "MOV{SE_M_SWORDS_DANCE}BROS{SE_M_ABSORB}HOUSE$"

BlackthornCity_Text_DragonDenSign:
	.string "DRAGON'{SE_M_SKETCH}DE{SE_M_PSYBEAM2}AHEAD$"

