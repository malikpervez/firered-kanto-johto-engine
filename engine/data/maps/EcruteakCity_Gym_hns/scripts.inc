@ Johto (data/maps/EcruteakCity_Gym_hns/scripts.inc), as built into the FireRed game.

EcruteakCity_Gym_hns_MapScripts::
	.byte 0

EcruteakCity_Gym_EventScript_GymGuy::
	lock
	faceplayer
	goto_if_set JOHTO_FLAG_DEFEATED_ECRUTEAK_CITY_GYM, EcruteakCity_Gym_EventScript_GymGuy2
	msgbox EcruteakCity_GymGuideText, MSGBOX_DEFAULT
	closemessage
	release
	end

EcruteakCity_Gym_EventScript_GymGuy2::
	msgbox EcruteakCity_GymGuideWinText, MSGBOX_DEFAULT
	release
	end

EcruteakCity_Gym_EventScript_Jeffrey::
	trainerbattle_single TRAINER_JOHTO_JEFFREY_HNS, SageJeffreySeenText, SageJeffreyBeatenText
	msgbox SageJeffreyAfterBattleText, MSGBOX_AUTOCLOSE
	end

EcruteakCity_Gym_EventScript_Ping::
	trainerbattle_single TRAINER_JOHTO_PING_HNS, SagePingSeenText, SagePingBeatenText
	msgbox SagePingAfterBattleText, MSGBOX_AUTOCLOSE
	end

EcruteakCity_Gym_EventScript_Martha::
	trainerbattle_single TRAINER_JOHTO_MARTHA_HNS, MediumMarthaSeenText, MediumMarthaBeatenText
	msgbox MediumMarthaAfterBattleText, MSGBOX_AUTOCLOSE
	end

EcruteakCity_Gym_EventScript_Grace::
	trainerbattle_single TRAINER_JOHTO_GRACE_HNS, MediumGraceSeenText, MediumGraceBeatenText
	msgbox MediumGraceAfterBattleText, MSGBOX_AUTOCLOSE
	end

EcruteakCity_Gym_EventScript_Morty::
	lock
	faceplayer
	goto_if_set JOHTO_FLAG_DEFEATED_ECRUTEAK_CITY_GYM, EcruteakCity_Gym_EventScript_Morty_Defeated
	msgbox MortyIntroText, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_JOHTO_MORTY_1_HNS, MortyWinLossText
	message Text_ReceivedFogBadge
	waitmessage
	call J_Common_EventScript_PlayGymBadgeFanfare
	msgbox MortyText_FogBadgeSpeech, MSGBOX_DEFAULT
	setflag JOHTO_FLAG_BADGE04_GET
	setflag JOHTO_FLAG_DEFEATED_ECRUTEAK_CITY_GYM
	addvar JOHTO_VAR_NUM_BADGES, 1
	setvar VAR_0x8008, 4
	call J_Common_EventScript_SetGymTrainers_hns
	giveitem ITEM_TM_SHADOW_BALL
	msgbox MortyText_ShadowBallSpeech, MSGBOX_DEFAULT
	setvar JOHTO_VAR_ECRUTEAK_CITY_STATE, 4
	closemessage
	release
	end

EcruteakCity_Gym_EventScript_Morty_Defeated::
	msgbox MortyFightDoneText, MSGBOX_DEFAULT
	closemessage
	release
	end

EcruteakCity_Gym_EventScript_Statue::
	lock
	goto_if_set JOHTO_FLAG_DEFEATED_ECRUTEAK_CITY_GYM, EcruteakCity_Gym_EventScript_Statue2
	msgbox EcruteakCity_Gym_Text_GymStatue, MSGBOX_DEFAULT
	closemessage
	release
	end

EcruteakCity_Gym_EventScript_Statue2::
	msgbox EcruteakCity_Gym_Text_GymStatueCertified, MSGBOX_DEFAULT
	closemessage
	release
	end

EcruteakCity_Gym_Text_GymStatue:
	.string "ECRUTEA{SE_M_SNORE}CIT{SE_M_MOONLIGHT}POKéMO{SE_M_PSYBEAM2}GYM$"

EcruteakCity_Gym_Text_GymStatueCertified:
	.string "ECRUTEA{SE_M_SNORE}CIT{SE_M_MOONLIGHT}POKéMO{SE_M_PSYBEAM2}GYM\p"
	.string "MORTY'{SE_M_SKETCH}CERTIFIE{SE_M_FAINT_ATTACK}TRAINERS:\n"
	.string "{PLAYER}$"

MortyIntroText:
	.string "Goo{SE_M_WATERFALL}o{SE_M_ACID_ARMOR}yo{SE_M_DIVE}t{SE_M_ATTRACT2}hav{SE_M_REVERSAL}come.\p"
	.string "Her{SE_M_REVERSAL}i{SE_M_ATTRACT}ECRUTEAK{SE_M_SUPERSONIC}POKéMO{SE_M_PSYBEAM2}have\n"
	.string "alway{SE_M_GRASSWHISTLE}bee{SE_M_ATTRACT}revered.\p"
	.string "It'{SE_M_GRASSWHISTLE}sai{SE_M_WATERFALL}tha{SE_M_SPIT_UP}{SE_M_CHARGE}rainbow-colored\n"
	.string "POKéMO{SE_M_PSYBEAM2}wil{SE_M_BATON_PASS}com{SE_M_REVERSAL}dow{SE_M_ATTRACT}to\l"
	.string "appea{SE_M_SAND_TOMB}befor{SE_M_REVERSAL}{SE_M_CHARGE}tru{SE_M_REVERSAL}Trainer.\p"
	.string "{SE_M_HEAL_BELL}believe{SE_M_WATERFALL}tha{SE_M_SPIT_UP}tale{SE_M_SUPERSONIC}s{SE_M_ATTRACT2}I've\n"
	.string "traine{SE_M_WATERFALL}her{SE_M_REVERSAL}i{SE_M_ATTRACT}secret.\p"
	.string "A{SE_M_GRASSWHISTLE}{SE_M_CHARGE}result{SE_M_SUPERSONIC}{SE_M_HEAL_BELL}ca{SE_M_ATTRACT}no{SE_M_TWISTER}se{SE_M_REVERSAL}what\n"
	.string "other{SE_M_GRASSWHISTLE}cannot.\p"
	.string "Jus{SE_M_SPIT_UP}{SE_M_CHARGE}bi{SE_M_SPIT_UP}more...\p"
	.string "Wit{SE_M_TRI_ATTACK}{SE_M_CHARGE}littl{SE_M_REVERSAL}more{SE_M_SUPERSONIC}{SE_M_HEAL_BELL}coul{SE_M_WATERFALL}see\n"
	.string "{SE_M_CHARGE}futur{SE_M_REVERSAL}wher{SE_M_REVERSAL}{SE_M_HEAL_BELL}mee{SE_M_SPIT_UP}the\l"
	.string "rainbow-colore{SE_M_WATERFALL}POKéMON.\p"
	.string "You'r{SE_M_REVERSAL}goin{SE_M_SANDSTORM}t{SE_M_ATTRACT2}hel{SE_M_MORNING_SUN}m{SE_M_REVERSAL}reach\n"
	.string "tha{SE_M_SPIT_UP}level!$"

MortyWinLossText:
	.string "I'{SE_M_MILK_DRINK}no{SE_M_SPIT_UP}goo{SE_M_WATERFALL}enoug{SE_M_TRI_ATTACK}yet...\p"
	.string "Al{SE_M_BATON_PASS}right{SE_M_PERISH_SONG}Thi{SE_M_GRASSWHISTLE}BADG{SE_M_SWORDS_DANCE}i{SE_M_GRASSWHISTLE}yours.$"

Text_ReceivedFogBadge:
	.string "{PLAYER} receive{SE_M_WATERFALL}th{SE_M_REVERSAL}FOGBADGE.$"

MortyText_FogBadgeSpeech:
	.string "Wit{SE_M_TRI_ATTACK}th{SE_M_REVERSAL}FOGBADGE{SE_M_SUPERSONIC}POKéMO{SE_M_PSYBEAM2}up\n"
	.string "t{SE_M_ATTRACT2}Leve{SE_M_BATON_PASS}5{SE_M_BITE}wil{SE_M_BATON_PASS}obe{SE_M_YAWN}you.\p"
	.string "Also{SE_M_SUPERSONIC}an{SE_M_YAWN}POKéMO{SE_M_PSYBEAM2}tha{SE_M_SPIT_UP}knows\n"
	.string "SUR{SE_M_LEER}wil{SE_M_BATON_PASS}b{SE_M_REVERSAL}abl{SE_M_REVERSAL}t{SE_M_ATTRACT2}us{SE_M_REVERSAL}it\l"
	.string "anytime.\p"
	.string "{SE_M_HEAL_BELL}wan{SE_M_SPIT_UP}yo{SE_M_DIVE}t{SE_M_ATTRACT2}hav{SE_M_REVERSAL}thi{SE_M_GRASSWHISTLE}too.$"

MortyText_ShadowBallSpeech:
	.string "That'{SE_M_GRASSWHISTLE}SHADO{SE_M_DETECT}BALL.\n"
	.string "I{SE_M_SPIT_UP}cause{SE_M_GRASSWHISTLE}damag{SE_M_REVERSAL}an{SE_M_WATERFALL}may\l"
	.string "lowe{SE_M_SAND_TOMB}SP{SE_M_PERISH_SONG}DEF.\p"
	.string "Us{SE_M_REVERSAL}i{SE_M_SPIT_UP}i{SE_M_ACID_ARMOR}i{SE_M_SPIT_UP}suit{SE_M_GRASSWHISTLE}you.$"

MortyFightDoneText:
	.string "{SE_M_HEAL_BELL}see...\p"
	.string "You{SE_M_SAND_TOMB}journe{SE_M_YAWN}ha{SE_M_GRASSWHISTLE}take{SE_M_ATTRACT}yo{SE_M_DIVE}to\n"
	.string "far-of{SE_M_ACID_ARMOR}places.\p"
	.string "You'v{SE_M_REVERSAL}witnesse{SE_M_WATERFALL}mor{SE_M_REVERSAL}tha{SE_M_ATTRACT}I\n"
	.string "eve{SE_M_SAND_TOMB}have.\p"
	.string "{SE_M_HEAL_BELL}env{SE_M_YAWN}yo{SE_M_DIVE}fo{SE_M_SAND_TOMB}that...$"

MortyRematchText:
	.string "Ah{SE_M_SUPERSONIC}th{SE_M_REVERSAL}JOHT{SE_M_SOLAR_BEAM}CHAMPION!\n"
	.string "Goo{SE_M_WATERFALL}o{SE_M_ACID_ARMOR}yo{SE_M_DIVE}t{SE_M_ATTRACT2}come.\p"
	.string "You'v{SE_M_REVERSAL}show{SE_M_ATTRACT}strengt{SE_M_TRI_ATTACK}an{SE_M_WATERFALL}skill,\n"
	.string "bu{SE_M_SPIT_UP}hav{SE_M_REVERSAL}yo{SE_M_DIVE}grow{SE_M_ATTRACT}sinc{SE_M_REVERSAL}we\l"
	.string "las{SE_M_SPIT_UP}battled?\p"
	.string "I'v{SE_M_REVERSAL}traine{SE_M_WATERFALL}wit{SE_M_TRI_ATTACK}m{SE_M_YAWN}GHOST-type\n"
	.string "POKéMO{SE_M_PSYBEAM2}eve{SE_M_SAND_TOMB}since.\p"
	.string "Let'{SE_M_GRASSWHISTLE}se{SE_M_REVERSAL}i{SE_M_ACID_ARMOR}yo{SE_M_DIVE}ca{SE_M_ATTRACT}overcome\n"
	.string "th{SE_M_REVERSAL}shadow{SE_M_GRASSWHISTLE}again.\p"
	.string "Wan{SE_M_SPIT_UP}t{SE_M_ATTRACT2}hav{SE_M_REVERSAL}{SE_M_CHARGE}rematch?$"

Morty_RematchDefeatText:
	.string "I'{SE_M_MILK_DRINK}no{SE_M_SPIT_UP}goo{SE_M_WATERFALL}enoug{SE_M_TRI_ATTACK}yet...\p"
	.string "You'v{SE_M_REVERSAL}witnesse{SE_M_WATERFALL}mor{SE_M_REVERSAL}tha{SE_M_ATTRACT}I\n"
	.string "eve{SE_M_SAND_TOMB}have.\p"
	.string "{SE_M_HEAL_BELL}env{SE_M_YAWN}yo{SE_M_DIVE}fo{SE_M_SAND_TOMB}that...$"

SageJeffreySeenText:
	.string "{SE_M_HEAL_BELL}spen{SE_M_SPIT_UP}th{SE_M_REVERSAL}sprin{SE_M_SANDSTORM}wit{SE_M_TRI_ATTACK}my\n"
	.string "POKéMON.\p"
	.string "The{SE_M_ATTRACT}summer{SE_M_SUPERSONIC}fall{SE_M_SUPERSONIC}an{SE_M_WATERFALL}winter...\p"
	.string "The{SE_M_ATTRACT}sprin{SE_M_SANDSTORM}cam{SE_M_REVERSAL}again.\n"
	.string "We'v{SE_M_REVERSAL}bee{SE_M_ATTRACT}togethe{SE_M_SAND_TOMB}{SE_M_CHARGE}lon{SE_M_SANDSTORM}time.$"

SageJeffreyBeatenText:
	.string "Win{SE_M_GRASSWHISTLE}an{SE_M_WATERFALL}losses--I'v{SE_M_REVERSAL}known\n"
	.string "the{SE_M_MILK_DRINK}both.$"

SageJeffreyAfterBattleText:
	.string "Wher{SE_M_REVERSAL}di{SE_M_WATERFALL}POKéMO{SE_M_PSYBEAM2}com{SE_M_REVERSAL}from?$"

SagePingSeenText:
	.string "Ca{SE_M_ATTRACT}yo{SE_M_DIVE}inflic{SE_M_SPIT_UP}an{SE_M_YAWN}damage\n"
	.string "o{SE_M_ATTRACT}ou{SE_M_SAND_TOMB}POKéMON?$"

SagePingBeatenText:
	.string "Ah{SE_M_DRAGON_RAGE}Wel{SE_M_BATON_PASS}done!$"

SagePingAfterBattleText:
	.string "W{SE_M_REVERSAL}us{SE_M_REVERSAL}GHOST-typ{SE_M_REVERSAL}POKéMON.\p"
	.string "N{SE_M_ATTRACT2}NORMAL-typ{SE_M_REVERSAL}attack{SE_M_GRASSWHISTLE}can\n"
	.string "har{SE_M_MILK_DRINK}them!$"

MediumMarthaSeenText:
	.string "{SE_M_HEAL_BELL}shal{SE_M_BATON_PASS}win!$"

MediumMarthaBeatenText:
	.string "I..{SE_M_PERISH_SONG}I..{SE_M_PERISH_SONG}{SE_M_HEAL_BELL}lost!$"

MediumMarthaAfterBattleText:
	.string "Th{SE_M_REVERSAL}on{SE_M_REVERSAL}wh{SE_M_ATTRACT2}want{SE_M_GRASSWHISTLE}t{SE_M_ATTRACT2}wi{SE_M_ATTRACT}the\n"
	.string "mos{SE_M_SPIT_UP}i{SE_M_GRASSWHISTLE}th{SE_M_REVERSAL}on{SE_M_REVERSAL}wh{SE_M_ATTRACT2}will!$"

MediumGraceSeenText:
	.string "Stumpe{SE_M_WATERFALL}b{SE_M_YAWN}ou{SE_M_SAND_TOMB}dar{SE_M_ENCORE2}corridors?\n"
	.string "Defea{SE_M_SPIT_UP}m{SE_M_REVERSAL}i{SE_M_ACID_ARMOR}yo{SE_M_DIVE}wan{SE_M_SPIT_UP}{SE_M_CHARGE}hint!$"

MediumGraceBeatenText:
	.string "Wha-what?$"

MediumGraceAfterBattleText:
	.string "Fine{SE_M_PERISH_SONG}I'l{SE_M_BATON_PASS}tel{SE_M_BATON_PASS}yo{SE_M_DIVE}th{SE_M_REVERSAL}secret\n"
	.string "o{SE_M_ACID_ARMOR}th{SE_M_REVERSAL}shadows.\p"
	.string "Th{SE_M_REVERSAL}pat{SE_M_TRI_ATTACK}i{SE_M_GRASSWHISTLE}righ{SE_M_SPIT_UP}i{SE_M_ATTRACT}fron{SE_M_SPIT_UP}of\n"
	.string "you{SE_M_SAND_TOMB}eyes!$"

EcruteakCity_GymGuideText:
	.string "He{SE_M_YAWN}CHAMP{SE_M_DRAGON_RAGE}You'r{SE_M_REVERSAL}almost\n"
	.string "halfwa{SE_M_YAWN}there!\p"
	.string "Trainer{SE_M_GRASSWHISTLE}her{SE_M_REVERSAL}us{SE_M_REVERSAL}GHOS{SE_M_SWIFT}and\n"
	.string "DARK-typ{SE_M_REVERSAL}POKéMON.\p"
	.string "Whil{SE_M_REVERSAL}MORT{SE_M_MOONLIGHT}i{SE_M_GRASSWHISTLE}{SE_M_CHARGE}GHOST-type\n"
	.string "expert{SE_M_SUPERSONIC}b{SE_M_REVERSAL}war{SE_M_YAWN}o{SE_M_ACID_ARMOR}hi{SE_M_GRASSWHISTLE}mystic\l"
	.string "deer.\p"
	.string "It'{SE_M_GRASSWHISTLE}sai{SE_M_WATERFALL}t{SE_M_ATTRACT2}caus{SE_M_REVERSAL}strange\n"
	.string "nightmares...$"

EcruteakCity_GymGuideWinText:
	.string "Whew{SE_M_SUPERSONIC}{PLAYER}{SE_M_PERISH_SONG}Yo{SE_M_DIVE}di{SE_M_WATERFALL}great!\p"
	.string "{SE_M_HEAL_BELL}wa{SE_M_GRASSWHISTLE}cowerin{SE_M_SANDSTORM}i{SE_M_ATTRACT}th{SE_M_REVERSAL}corner\n"
	.string "ou{SE_M_SPIT_UP}o{SE_M_ACID_ARMOR}pur{SE_M_REVERSAL}terror!$"

EcruteakCity_GymClosedText:
	.string "MORTY{SE_M_SUPERSONIC}th{SE_M_REVERSAL}GY{SE_M_GIGA_DRAIN}LEADER{SE_M_SUPERSONIC}is\n"
	.string "absent.\p"
	.string "Sorry{SE_M_SUPERSONIC}bu{SE_M_SPIT_UP}you'l{SE_M_BATON_PASS}hav{SE_M_REVERSAL}to\n"
	.string "leave.\p"
	.string "Hohohoho.$"

