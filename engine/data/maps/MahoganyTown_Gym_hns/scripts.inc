@ Johto (data/maps/MahoganyTown_Gym_hns/scripts.inc), as built into the FireRed game.

MahoganyTown_Gym_hns_MapScripts::
	.byte 0

MahoganyTown_Gym_EventScript_Statue::
	lock
	goto_if_set JOHTO_FLAG_DEFEATED_MAHOGANY_TOWN_GYM, MahoganyTown_Gym_EventScript_Statue2
	msgbox MahoganyTown_Gym_Text_GymStatue, MSGBOX_DEFAULT
	closemessage
	release
	end

MahoganyTown_Gym_EventScript_Statue2::
	msgbox MahoganyTown_Gym_Text_GymStatueCertified, MSGBOX_DEFAULT
	closemessage
	release
	end

MahoganyTown_Gym_Text_GymStatue:
	.string "MAHOGAN{SE_M_MOONLIGHT}TOW{SE_M_PSYBEAM2}POKéMO{SE_M_PSYBEAM2}GYM$"

MahoganyTown_Gym_Text_GymStatueCertified:
	.string "MAHOGAN{SE_M_MOONLIGHT}TOW{SE_M_PSYBEAM2}POKéMO{SE_M_PSYBEAM2}GYM\p"
	.string "PRYCE'{SE_M_SKETCH}CERTIFIE{SE_M_FAINT_ATTACK}TRAINERS:\n"
	.string "{PLAYER}$"

MahoganyTown_GymEventScript_GymGuy::
	lock
	faceplayer
	goto_if_set JOHTO_FLAG_DEFEATED_MAHOGANY_TOWN_GYM, MahoganyTown_Gym_EventScript_GymGuy2
	msgbox MahoganyTown_Gym_Text_Guide, MSGBOX_DEFAULT
	closemessage
	release
	end

MahoganyTown_Gym_EventScript_GymGuy2::
	msgbox MahoganyTown_Gym_Text_GuideWin, MSGBOX_DEFAULT
	release
	end

MahoganyTown_Gym_EventScript_Ronald::
	trainerbattle_single TRAINER_JOHTO_RONALD_HNS, MahoganyTown_Gym_Text_BoarderRonaldSeen, MahoganyTown_Gym_Text_BoarderRonaldBeaten
	msgbox MahoganyTown_Gym_Text_BoarderRonaldAfter, MSGBOX_AUTOCLOSE
	end

MahoganyTown_Gym_EventScript_Brad::
	trainerbattle_single TRAINER_JOHTO_BRAD_HNS, MahoganyTown_Gym_Text_BoarderBradSeen, MahoganyTown_Gym_Text_BoarderBradBeaten
	msgbox MahoganyTown_Gym_Text_BoarderBradAfter, MSGBOX_AUTOCLOSE
	end

MahoganyTown_Gym_EventScript_Douglas::
	trainerbattle_single TRAINER_JOHTO_DOUGLAS_HNS, MahoganyTown_Gym_Text_BoarderDouglasSeen, MahoganyTown_Gym_Text_BoarderDouglasBeaten
	msgbox MahoganyTown_Gym_Text_BoarderDouglasAfter, MSGBOX_AUTOCLOSE
	end

MahoganyTown_Gym_EventScript_Roxanne::
	trainerbattle_single TRAINER_JOHTO_ROXANNE_HNS, MahoganyTown_Gym_Text_SkierRoxanneSeen, MahoganyTown_Gym_Text_SkierRoxanneBeaten
	msgbox MahoganyTown_Gym_Text_SkierRoxanneAfter, MSGBOX_AUTOCLOSE
	end

MahoganyTown_Gym_EventScript_Clarissa::
	trainerbattle_single TRAINER_JOHTO_CLARISSA_HNS, MahoganyTown_Gym_Text_SkierClarissaSeen, MahoganyTown_Gym_Text_SkierClarissaBeaten
	msgbox MahoganyTown_Gym_Text_SkierClarissaAfter, MSGBOX_AUTOCLOSE
	end

MahoganyTown_Gym_EventScript_Pryce::
	lock
	faceplayer
	goto_if_set JOHTO_FLAG_DEFEATED_MAHOGANY_TOWN_GYM, MahoganyTown_Gym_EventScript_Pryce_Defeated
	msgbox MahoganyTown_Gym_Text_PryceIntro, MSGBOX_DEFAULT
	goto_if_set JOHTO_FLAG_DEFEATED_OLIVINE_CITY_GYM, MahoganyTown_Gym_EventScript_OlivineCheckCianwood
	goto_if_set JOHTO_FLAG_DEFEATED_CIANWOOD_GYM, MahoganyTown_Gym_EventScript_CianwoodCheckOlivine
	goto MahoganyTown_Gym_EventScript_Pryce_Battle1

MahoganyTown_Gym_EventScript_PryceVictory::
	message MahoganyTown_Gym_Text_ReceivedBadge
	waitmessage
	call J_Common_EventScript_PlayGymBadgeFanfare
	msgbox MahoganyTown_Gym_Text_GlacierBadgeSpeech, MSGBOX_DEFAULT
	setflag JOHTO_FLAG_BADGE07_GET
	setflag JOHTO_FLAG_DEFEATED_MAHOGANY_TOWN_GYM
	addvar JOHTO_VAR_NUM_BADGES, 1
	setvar VAR_0x8008, 7
	call J_Common_EventScript_SetGymTrainers_hns
	giveitem ITEM_TM_HAIL
	msgbox MahoganyTown_Gym_Text_HailSpeech, MSGBOX_DEFAULT
	setvar JOHTO_VAR_MAHOGANY_TOWN_STATE, 15
	setrespawn JOHTO_HEAL_LOCATION_MAHOGANY_TOWN_HNS
	call_if_eq JOHTO_VAR_NUM_BADGES, 7, MahoganyTown_Gym_EventScript_SetupElmRocketCall
	closemessage
	release
	end

MahoganyTown_Gym_EventScript_SetupElmRocketCall::
	setvar JOHTO_VAR_TRIGGER_ELM_ROCKET_CALL, 1
	return

MahoganyTown_Gym_EventScript_OlivineCheckCianwood::
	goto_if_set JOHTO_FLAG_DEFEATED_CIANWOOD_GYM, MahoganyTown_Gym_EventScript_Pryce_Battle3
	goto MahoganyTown_Gym_EventScript_Pryce_Battle2

MahoganyTown_Gym_EventScript_CianwoodCheckOlivine::
	goto_if_set JOHTO_FLAG_DEFEATED_OLIVINE_CITY_GYM, MahoganyTown_Gym_EventScript_Pryce_Battle3
	goto MahoganyTown_Gym_EventScript_Pryce_Battle2

MahoganyTown_Gym_EventScript_Pryce_Battle1::
	trainerbattle_no_intro TRAINER_JOHTO_PRYCE_1_HNS, MahoganyTown_Gym_Text_PryceImpressed
	goto MahoganyTown_Gym_EventScript_PryceVictory

MahoganyTown_Gym_EventScript_Pryce_Battle2::
	trainerbattle_no_intro TRAINER_JOHTO_PRYCE_1_2_HNS, MahoganyTown_Gym_Text_PryceImpressed
	goto MahoganyTown_Gym_EventScript_PryceVictory

MahoganyTown_Gym_EventScript_Pryce_Battle3::
	trainerbattle_no_intro TRAINER_JOHTO_PRYCE_1_3_HNS, MahoganyTown_Gym_Text_PryceImpressed
	goto MahoganyTown_Gym_EventScript_PryceVictory

MahoganyTown_Gym_EventScript_Pryce_Defeated::
	msgbox MahoganyTown_Gym_Text_CherishPokemon, MSGBOX_DEFAULT
	closemessage
	release
	end

MahoganyTown_Gym_Text_PryceIntro:
	.string "POKéMO{SE_M_PSYBEAM2}hav{SE_M_REVERSAL}man{SE_M_YAWN}experiences\n"
	.string "i{SE_M_ATTRACT}thei{SE_M_SAND_TOMB}lives{SE_M_SUPERSONIC}jus{SE_M_SPIT_UP}lik{SE_M_REVERSAL}w{SE_M_REVERSAL}do.\p"
	.string "I{SE_M_SUPERSONIC}too{SE_M_SUPERSONIC}hav{SE_M_REVERSAL}see{SE_M_ATTRACT}an{SE_M_WATERFALL}suffered\n"
	.string "muc{SE_M_TRI_ATTACK}i{SE_M_ATTRACT}m{SE_M_YAWN}life.\p"
	.string "Sinc{SE_M_REVERSAL}{SE_M_HEAL_BELL}a{SE_M_MILK_DRINK}you{SE_M_SAND_TOMB}elder{SE_M_SUPERSONIC}le{SE_M_SPIT_UP}me\n"
	.string "sho{SE_M_TWISTER}yo{SE_M_DIVE}wha{SE_M_SPIT_UP}{SE_M_HEAL_BELL}mean.\p"
	.string "{SE_M_HEAL_BELL}hav{SE_M_REVERSAL}bee{SE_M_ATTRACT}wit{SE_M_TRI_ATTACK}POKéMO{SE_M_PSYBEAM2}since\n"
	.string "befor{SE_M_REVERSAL}yo{SE_M_DIVE}wer{SE_M_REVERSAL}born.\p"
	.string "{SE_M_HEAL_BELL}d{SE_M_ATTRACT2}no{SE_M_SPIT_UP}los{SE_M_REVERSAL}easily.\p"
	.string "I{SE_M_SUPERSONIC}PRYCE--th{SE_M_REVERSAL}winte{SE_M_SAND_TOMB}trainer--\n"
	.string "shal{SE_M_BATON_PASS}demonstrat{SE_M_REVERSAL}m{SE_M_YAWN}power!$"

MahoganyTown_Gym_Text_PryceImpressed:
	.string "Ah{SE_M_SUPERSONIC}{SE_M_HEAL_BELL}a{SE_M_MILK_DRINK}impresse{SE_M_WATERFALL}b{SE_M_YAWN}your\n"
	.string "prowess.\p"
	.string "Wit{SE_M_TRI_ATTACK}you{SE_M_SAND_TOMB}stron{SE_M_SANDSTORM}will{SE_M_SUPERSONIC}{SE_M_HEAL_BELL}kno{SE_M_TWISTER}you\n"
	.string "wil{SE_M_BATON_PASS}overcom{SE_M_REVERSAL}al{SE_M_BATON_PASS}life'{SE_M_GRASSWHISTLE}obstacles.\p"
	.string "Yo{SE_M_DIVE}ar{SE_M_REVERSAL}worth{SE_M_YAWN}o{SE_M_ACID_ARMOR}thi{SE_M_GRASSWHISTLE}BADGE!$"

MahoganyTown_Gym_Text_ReceivedBadge:
	.string "{PLAYER} receive{SE_M_WATERFALL}GLACIERBADGE.$"

MahoganyTown_Gym_Text_GlacierBadgeSpeech:
	.string "Tha{SE_M_SPIT_UP}BADG{SE_M_SWORDS_DANCE}wil{SE_M_BATON_PASS}rais{SE_M_REVERSAL}th{SE_M_REVERSAL}SPECIAL\n"
	.string "ATTAC{SE_M_SNORE}o{SE_M_ACID_ARMOR}POKéMON.\p"
	.string "I{SE_M_SPIT_UP}als{SE_M_ATTRACT2}let{SE_M_GRASSWHISTLE}you{SE_M_SAND_TOMB}POKéMO{SE_M_PSYBEAM2}use\n"
	.string "WHIRLPOO{SE_M_BRICK_BREAK}t{SE_M_ATTRACT2}ge{SE_M_SPIT_UP}across\l"
	.string "rea{SE_M_BATON_PASS}whirlpools.\p"
	.string "An{SE_M_WATERFALL}this{SE_M_DIZZY_PUNCH}Thi{SE_M_GRASSWHISTLE}i{SE_M_GRASSWHISTLE}{SE_M_CHARGE}gif{SE_M_SPIT_UP}fro{SE_M_MILK_DRINK}me!$"

MahoganyTown_Gym_Text_HailSpeech:
	.string "Tha{SE_M_SPIT_UP}T{SE_M_GIGA_DRAIN}contain{SE_M_GRASSWHISTLE}HAIL.\p"
	.string "I{SE_M_SPIT_UP}inflict{SE_M_GRASSWHISTLE}damag{SE_M_REVERSAL}every\n"
	.string "tur{SE_M_ATTRACT}fo{SE_M_SAND_TOMB}{SE_M_HORN_ATTACK}turns.\p"
	.string "I{SE_M_SPIT_UP}demonstrate{SE_M_GRASSWHISTLE}th{SE_M_REVERSAL}harshness\n"
	.string "o{SE_M_ACID_ARMOR}winter.$"

MahoganyTown_Gym_Text_CherishPokemon:
	.string "Whe{SE_M_ATTRACT}th{SE_M_REVERSAL}ic{SE_M_REVERSAL}an{SE_M_WATERFALL}sno{SE_M_TWISTER}melt,\n"
	.string "sprin{SE_M_SANDSTORM}arrives.\p"
	.string "Yo{SE_M_DIVE}an{SE_M_WATERFALL}you{SE_M_SAND_TOMB}POKéMO{SE_M_PSYBEAM2}wil{SE_M_BATON_PASS}be\n"
	.string "togethe{SE_M_SAND_TOMB}fo{SE_M_SAND_TOMB}man{SE_M_YAWN}year{SE_M_GRASSWHISTLE}t{SE_M_ATTRACT2}come.\p"
	.string "Cheris{SE_M_TRI_ATTACK}you{SE_M_SAND_TOMB}tim{SE_M_REVERSAL}together!$"

MahoganyTown_Gym_Text_PryceRematch:
	.string "Ah{SE_M_SUPERSONIC}JOHT{SE_M_SOLAR_BEAM}CHAMPION!\p"
	.string "You{SE_M_SAND_TOMB}skill{SE_M_GRASSWHISTLE}ar{SE_M_REVERSAL}indeed\n"
	.string "remarkable.\p"
	.string "{SE_M_HEAL_BELL}a{SE_M_MILK_DRINK}impressed.\p"
	.string "Bu{SE_M_SPIT_UP}eve{SE_M_ATTRACT}now{SE_M_SUPERSONIC}ther{SE_M_REVERSAL}i{SE_M_GRASSWHISTLE}muc{SE_M_TRI_ATTACK}to\n"
	.string "lear{SE_M_ATTRACT}fro{SE_M_MILK_DRINK}eac{SE_M_TRI_ATTACK}other.\p"
	.string "I{SE_M_SUPERSONIC}PRYCE--th{SE_M_REVERSAL}winte{SE_M_SAND_TOMB}trainer--\n"
	.string "stil{SE_M_BATON_PASS}hav{SE_M_REVERSAL}{SE_M_CHARGE}fe{SE_M_TWISTER}trick{SE_M_GRASSWHISTLE}left.\p"
	.string "Wan{SE_M_SPIT_UP}t{SE_M_ATTRACT2}hav{SE_M_REVERSAL}{SE_M_CHARGE}rematc{SE_M_TRI_ATTACK}wit{SE_M_TRI_ATTACK}me?$"

MahoganyTown_Gym_Text_PryceRematchDefeat:
	.string "Ah{SE_M_SUPERSONIC}ye{SE_M_SPIT_UP}agai{SE_M_ATTRACT}I'{SE_M_MILK_DRINK}impresse{SE_M_WATERFALL}by\n"
	.string "you{SE_M_SAND_TOMB}prowess.\p"
	.string "Wit{SE_M_TRI_ATTACK}you{SE_M_SAND_TOMB}stron{SE_M_SANDSTORM}will{SE_M_SUPERSONIC}{SE_M_HEAL_BELL}kno{SE_M_TWISTER}you\n"
	.string "wil{SE_M_BATON_PASS}overcom{SE_M_REVERSAL}al{SE_M_BATON_PASS}life'{SE_M_GRASSWHISTLE}obstacles.$"

MahoganyTown_Gym_Text_Guide:
	.string "PRYC{SE_M_SWORDS_DANCE}i{SE_M_GRASSWHISTLE}{SE_M_CHARGE}vetera{SE_M_ATTRACT}wh{SE_M_ATTRACT2}has\n"
	.string "traine{SE_M_WATERFALL}POKéMO{SE_M_PSYBEAM2}fo{SE_M_SAND_TOMB}som{SE_M_REVERSAL}5{SE_M_BITE}years.\p"
	.string "He'{SE_M_GRASSWHISTLE}go{SE_M_SPIT_UP}{SE_M_CHARGE}soli{SE_M_WATERFALL}lineu{SE_M_MORNING_SUN}of\n"
	.string "POKéMO{SE_M_PSYBEAM2}t{SE_M_ATTRACT2}cove{SE_M_SAND_TOMB}whatever\l"
	.string "yo{SE_M_DIVE}brin{SE_M_SANDSTORM}hi{SE_M_GRASSWHISTLE}way.\p"
	.string "Fir{SE_M_REVERSAL}i{SE_M_GRASSWHISTLE}{SE_M_CHARGE}goo{SE_M_WATERFALL}plac{SE_M_REVERSAL}t{SE_M_ATTRACT2}start,\n"
	.string "bu{SE_M_SPIT_UP}watc{SE_M_TRI_ATTACK}ou{SE_M_SPIT_UP}fo{SE_M_SAND_TOMB}th{SE_M_REVERSAL}rain!$"

MahoganyTown_Gym_Text_GuideWin:
	.string "PRYC{SE_M_SWORDS_DANCE}i{SE_M_GRASSWHISTLE}something{SE_M_SUPERSONIC}bu{SE_M_SPIT_UP}you're\n"
	.string "somethin{SE_M_SANDSTORM}else!\p"
	.string "Tha{SE_M_SPIT_UP}wa{SE_M_GRASSWHISTLE}{SE_M_CHARGE}ho{SE_M_SPIT_UP}battl{SE_M_REVERSAL}that\n"
	.string "bridge{SE_M_WATERFALL}th{SE_M_REVERSAL}generatio{SE_M_ATTRACT}gap!$"

MahoganyTown_Gym_Text_BoarderRonaldSeen:
	.string "I'l{SE_M_BATON_PASS}freez{SE_M_REVERSAL}you{SE_M_SAND_TOMB}POKéMON,\n"
	.string "s{SE_M_ATTRACT2}yo{SE_M_DIVE}can'{SE_M_SPIT_UP}d{SE_M_ATTRACT2}{SE_M_CHARGE}thing!$"

MahoganyTown_Gym_Text_BoarderRonaldBeaten:
	.string "Darn{SE_M_PERISH_SONG}{SE_M_HEAL_BELL}couldn'{SE_M_SPIT_UP}d{SE_M_ATTRACT2}{SE_M_CHARGE}thing.$"

MahoganyTown_Gym_Text_BoarderRonaldAfter:
	.string "{SE_M_HEAL_BELL}thin{SE_M_ENCORE2}there'{SE_M_GRASSWHISTLE}{SE_M_CHARGE}mov{SE_M_REVERSAL}a\n"
	.string "POKéMO{SE_M_PSYBEAM2}ca{SE_M_ATTRACT}us{SE_M_REVERSAL}whil{SE_M_REVERSAL}it's\l"
	.string "frozen.$"

MahoganyTown_Gym_Text_BoarderBradSeen:
	.string "Thi{SE_M_GRASSWHISTLE}GY{SE_M_GIGA_DRAIN}ha{SE_M_GRASSWHISTLE}{SE_M_CHARGE}slipper{SE_M_YAWN}floor.\p"
	.string "It'{SE_M_GRASSWHISTLE}fun{SE_M_SUPERSONIC}isn'{SE_M_SPIT_UP}it?\p"
	.string "Bu{SE_M_SPIT_UP}hey--we'r{SE_M_REVERSAL}no{SE_M_SPIT_UP}playing\n"
	.string "game{SE_M_GRASSWHISTLE}here!$"

MahoganyTown_Gym_Text_BoarderBradBeaten:
	.string "D{SE_M_ATTRACT2}yo{SE_M_DIVE}se{SE_M_REVERSAL}ho{SE_M_TWISTER}seriou{SE_M_GRASSWHISTLE}w{SE_M_REVERSAL}are?$"

MahoganyTown_Gym_Text_BoarderBradAfter:
	.string "Thi{SE_M_GRASSWHISTLE}GY{SE_M_GIGA_DRAIN}i{SE_M_GRASSWHISTLE}great.\n"
	.string "{SE_M_HEAL_BELL}lov{SE_M_REVERSAL}boardin{SE_M_SANDSTORM}wit{SE_M_TRI_ATTACK}my\l"
	.string "POKéMON!$"

MahoganyTown_Gym_Text_BoarderDouglasSeen:
	.string "{SE_M_HEAL_BELL}kno{SE_M_TWISTER}PRYCE'{SE_M_GRASSWHISTLE}secret.$"

MahoganyTown_Gym_Text_BoarderDouglasBeaten:
	.string "OK{SE_M_PERISH_SONG}I'l{SE_M_BATON_PASS}tel{SE_M_BATON_PASS}yo{SE_M_DIVE}PRYCE'{SE_M_GRASSWHISTLE}secret.$"

MahoganyTown_Gym_Text_BoarderDouglasAfter:
	.string "Th{SE_M_REVERSAL}secre{SE_M_SPIT_UP}behin{SE_M_WATERFALL}PRYCE'{SE_M_GRASSWHISTLE}power…\p"
	.string "H{SE_M_REVERSAL}meditate{SE_M_GRASSWHISTLE}unde{SE_M_SAND_TOMB}{SE_M_CHARGE}waterfall\n"
	.string "dail{SE_M_YAWN}t{SE_M_ATTRACT2}strengthe{SE_M_ATTRACT}hi{SE_M_GRASSWHISTLE}mind\l"
	.string "an{SE_M_WATERFALL}body.$"

MahoganyTown_Gym_Text_SkierRoxanneSeen:
	.string "T{SE_M_ATTRACT2}ge{SE_M_SPIT_UP}t{SE_M_ATTRACT2}PRYCE{SE_M_SUPERSONIC}ou{SE_M_SAND_TOMB}GY{SE_M_GIGA_DRAIN}LEADER,\n"
	.string "yo{SE_M_DIVE}nee{SE_M_WATERFALL}t{SE_M_ATTRACT2}thin{SE_M_ENCORE2}befor{SE_M_REVERSAL}yo{SE_M_DIVE}skate.$"

MahoganyTown_Gym_Text_SkierRoxanneBeaten:
	.string "{SE_M_HEAL_BELL}wouldn'{SE_M_SPIT_UP}los{SE_M_REVERSAL}t{SE_M_ATTRACT2}yo{SE_M_DIVE}i{SE_M_ATTRACT}skiing!$"

MahoganyTown_Gym_Text_SkierRoxanneAfter:
	.string "I{SE_M_ACID_ARMOR}yo{SE_M_DIVE}don'{SE_M_SPIT_UP}skat{SE_M_REVERSAL}wit{SE_M_TRI_ATTACK}precision,\n"
	.string "yo{SE_M_DIVE}won'{SE_M_SPIT_UP}ge{SE_M_SPIT_UP}fa{SE_M_SAND_TOMB}i{SE_M_ATTRACT}thi{SE_M_GRASSWHISTLE}GYM.$"

MahoganyTown_Gym_Text_SkierClarissaSeen:
	.string "Chec{SE_M_ENCORE2}ou{SE_M_SPIT_UP}m{SE_M_YAWN}paralle{SE_M_BATON_PASS}turn!$"

MahoganyTown_Gym_Text_SkierClarissaBeaten:
	.string "No{SE_M_DRAGON_RAGE}Yo{SE_M_DIVE}mad{SE_M_REVERSAL}m{SE_M_REVERSAL}wip{SE_M_REVERSAL}out!$"

MahoganyTown_Gym_Text_SkierClarissaAfter:
	.string "{SE_M_HEAL_BELL}shouldn'{SE_M_SPIT_UP}hav{SE_M_REVERSAL}bee{SE_M_ATTRACT}bragging\n"
	.string "abou{SE_M_SPIT_UP}m{SE_M_YAWN}skiing…$"

