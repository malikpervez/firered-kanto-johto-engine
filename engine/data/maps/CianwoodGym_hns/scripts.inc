@ Johto (data/maps/CianwoodGym_hns/scripts.inc), as built into the FireRed game.

CianwoodGym_hns_MapScripts::
	.byte 0

CianwoodGym_EventScript_Statue::
	lock
	goto_if_set 8747, CianwoodGym_EventScript_Statue2
	msgbox CianwoodGym_Text_GymStatue, MSGBOX_DEFAULT
	closemessage
	release
	end

CianwoodGym_EventScript_Statue2::
	msgbox CianwoodGym_Text_GymStatueCertified, MSGBOX_DEFAULT
	closemessage
	release
	end

CianwoodGym_Text_GymStatue:
	.string "CIANWOO{SE_M_FAINT_ATTACK}CIT{SE_M_MOONLIGHT}POKéMO{SE_M_PSYBEAM2}GYM$"

CianwoodGym_Text_GymStatueCertified:
	.string "CIANWOO{SE_M_FAINT_ATTACK}CIT{SE_M_MOONLIGHT}POKéMO{SE_M_PSYBEAM2}GYM\p"
	.string "CHUCK'{SE_M_SKETCH}CERTIFIE{SE_M_FAINT_ATTACK}TRAINERS:\n"
	.string "{PLAYER}$"

CianwoodGym_EventScript_Chuck::
	lock
	faceplayer
	goto_if_unset 8390, CianwoodGym_EventScript_ChuckAtDojo
	goto_if_set 10500, CianwoodGym_EventScript_ChuckGotoDojo
	goto_if_set 8747, CianwoodGym_EventScript_Chuck_Defeated
	msgbox CianwoodGym_Text_ChuckIntro1, MSGBOX_DEFAULT
	applymovement 1, CianwoodGym_Movement_ChuckLeft
	waitmovement 0
	message CianwoodGym_Text_ChuckIntro2
	applymovement 10, J_Movement_SmashRock
	playse 131
	waitmovement 0

	delay 20

	applymovement 1, CianwoodGym_Movement_ChuckRight
	waitmovement 0
	applymovement 9, J_Movement_SmashRock
	playse 131
	waitmovement 0
	waitmessage
	turnobject 1, DIR_SOUTH
	msgbox CianwoodGym_Text_ChuckIntro3, MSGBOX_DEFAULT
	goto_if_set 8748, CianwoodGym_EventScript_OlivineCheckMahog
	goto_if_set 8749, CianwoodGym_EventScript_MahogCheckOlivine
	goto CianwoodGym_EventScript_Chuck_Battle1

CianwoodGym_EventScript_ChuckVictory::
	message CianwoodGym_Text_GetStormBadge
	waitmessage
	call J_Common_EventScript_PlayGymBadgeFanfare
	msgbox CianwoodGym_Text_ChuckBadgeSpeech, MSGBOX_DEFAULT
	setflag 10372
	setflag 8747
	addvar 20582, 1
	setvar 32776, 5
	call J_Common_EventScript_SetGymTrainers_hns
	giveitem 582
	msgbox CianwoodGym_Text_ChuckTMSpeech, MSGBOX_DEFAULT
	setvar 20568, 1
	setrespawn 135
	call_if_eq 20582, 7, MahoganyTown_Gym_EventScript_SetupElmRocketCall
	closemessage
	release
	end

CianwoodGym_EventScript_ChuckGotoDojo::
	msgbox CianwoodGym_Text_ChuckGotoDojo, MSGBOX_DEFAULT
	closemessage
	clearflag 8390
	release
	end

CianwoodGym_Text_ChuckGotoDojo:
	.string "WAHAHAH{SE_M_BONEMERANG}{PLAYER}!\n"
	.string "I'{SE_M_MILK_DRINK}i{SE_M_ATTRACT}th{SE_M_REVERSAL}middl{SE_M_REVERSAL}o{SE_M_ACID_ARMOR}m{SE_M_YAWN}training!\p"
	.string "I{SE_M_ACID_ARMOR}yo{SE_M_DIVE}wan{SE_M_SPIT_UP}anothe{SE_M_SAND_TOMB}match{SE_M_SUPERSONIC}com{SE_M_REVERSAL}to\n"
	.string "th{SE_M_REVERSAL}FIGHTIN{SE_M_SWAGGER}DOJ{SE_M_SOLAR_BEAM}i{SE_M_ATTRACT}SAFFRON!$"

CianwoodGym_EventScript_ChuckAtDojo::
	msgbox CianwoodGym_Text_ChuckAtDojo, MSGBOX_DEFAULT
	closemessage
	release
	end

CianwoodGym_Text_ChuckAtDojo:
	.string "{SE_M_HEAL_BELL}wil{SE_M_BATON_PASS}se{SE_M_REVERSAL}yo{SE_M_DIVE}a{SE_M_SPIT_UP}th{SE_M_REVERSAL}DOJO!\n"
	.string "WAHAHAHAHAHA$"

CianwoodGym_EventScript_OlivineCheckMahog::
	goto_if_set 8749, CianwoodGym_EventScript_Chuck_Battle3
	goto CianwoodGym_EventScript_Chuck_Battle2

CianwoodGym_EventScript_MahogCheckOlivine::
	goto_if_set 8748, CianwoodGym_EventScript_Chuck_Battle3
	goto CianwoodGym_EventScript_Chuck_Battle2

CianwoodGym_EventScript_Chuck_Battle1::
	trainerbattle_no_intro 1442, CianwoodGym_Text_ChuckIntro2
	goto CianwoodGym_EventScript_ChuckVictory

CianwoodGym_EventScript_Chuck_Battle2::
	trainerbattle_no_intro 1444, CianwoodGym_Text_ChuckIntro2
	goto CianwoodGym_EventScript_ChuckVictory

CianwoodGym_EventScript_Chuck_Battle3::
	trainerbattle_no_intro 1445, CianwoodGym_Text_ChuckIntro2
	goto CianwoodGym_EventScript_ChuckVictory

CianwoodGym_EventScript_Chuck_Defeated::
	msgbox CianwoodGym_Text_ChuckAfter, MSGBOX_DEFAULT
	closemessage
	release
	end

CianwoodGym_Movement_ChuckLeft:
	jump_in_place_left
	step_end

CianwoodGym_Movement_ChuckRight:
	jump_in_place_right
	step_end

CianwoodGym_Text_ChuckIntro1:
	.string "WAHAHAH!\p"
	.string "S{SE_M_ATTRACT2}you'v{SE_M_REVERSAL}com{SE_M_REVERSAL}thi{SE_M_GRASSWHISTLE}far!\p"
	.string "Le{SE_M_SPIT_UP}m{SE_M_REVERSAL}tel{SE_M_BATON_PASS}you{SE_M_SUPERSONIC}I'{SE_M_MILK_DRINK}tough!\p"
	.string "M{SE_M_YAWN}POKéMO{SE_M_PSYBEAM2}wil{SE_M_BATON_PASS}crus{SE_M_TRI_ATTACK}stone{SE_M_GRASSWHISTLE}and\n"
	.string "shatte{SE_M_SAND_TOMB}bones!\p"
	.string "Watc{SE_M_TRI_ATTACK}this!$"

CianwoodGym_Text_ChuckIntro2:
	.string "CHUCK{SE_M_HEAT_WAVE}Urggh!\n"
	.string "…\p"
	.string "Oooarrgh!$"

CianwoodGym_Text_ChuckIntro3:
	.string "There{SE_M_DRAGON_RAGE}Scare{SE_M_WATERFALL}now{SE_M_SUPERSONIC}ar{SE_M_REVERSAL}you?\p"
	.string "What{SE_M_SING}I{SE_M_SPIT_UP}ha{SE_M_GRASSWHISTLE}nothin{SE_M_SANDSTORM}t{SE_M_ATTRACT2}d{SE_M_ATTRACT2}with\n"
	.string "POKéMON?\p"
	.string "That'{SE_M_GRASSWHISTLE}true!\p"
	.string "Com{SE_M_REVERSAL}on{SE_M_PERISH_SONG}W{SE_M_REVERSAL}shal{SE_M_BATON_PASS}d{SE_M_ATTRACT2}battle!$"

CianwoodGym_Text_ChuckLoss:
	.string "Wha{SE_M_SING}Huh{SE_M_SING}{SE_M_HEAL_BELL}lost?\p"
	.string "Ho{SE_M_TWISTER}abou{SE_M_SPIT_UP}that!\n"
	.string "You'r{SE_M_REVERSAL}worth{SE_M_YAWN}o{SE_M_ACID_ARMOR}STORMBADGE!$"

CianwoodGym_Text_GetStormBadge:
	.string "{PLAYER} receive{SE_M_WATERFALL}STORMBADGE.$"

CianwoodGym_Text_ChuckBadgeSpeech:
	.string "STORMBADG{SE_M_SWORDS_DANCE}make{SE_M_GRASSWHISTLE}al{SE_M_BATON_PASS}POKéMO{SE_M_PSYBEAM2}u{SE_M_MORNING_SUN}to\n"
	.string "L7{SE_M_BITE}obey{SE_M_SUPERSONIC}eve{SE_M_ATTRACT}trade{SE_M_WATERFALL}ones.\p"
	.string "I{SE_M_SPIT_UP}als{SE_M_ATTRACT2}let{SE_M_GRASSWHISTLE}you{SE_M_SAND_TOMB}POKéMO{SE_M_PSYBEAM2}us{SE_M_REVERSAL}FLY\n"
	.string "whe{SE_M_ATTRACT}you'r{SE_M_REVERSAL}no{SE_M_SPIT_UP}i{SE_M_ATTRACT}{SE_M_CHARGE}battle.\p"
	.string "Here{SE_M_SUPERSONIC}tak{SE_M_REVERSAL}thi{SE_M_GRASSWHISTLE}too!$"

CianwoodGym_Text_ChuckTMSpeech:
	.string "Tha{SE_M_SPIT_UP}i{SE_M_GRASSWHISTLE}FOCU{SE_M_SKETCH}PUNCH.\p"
	.string "I{SE_M_SPIT_UP}move{SE_M_GRASSWHISTLE}slo{SE_M_TWISTER}bu{SE_M_SPIT_UP}deal{SE_M_GRASSWHISTLE}huge\n"
	.string "damage{SE_M_PERISH_SONG}Jus{SE_M_SPIT_UP}don'{SE_M_SPIT_UP}ge{SE_M_SPIT_UP}hi{SE_M_SPIT_UP}first!$"

CianwoodGym_Text_ChuckAfter:
	.string "WAHAHAH{SE_M_DRAGON_RAGE}{SE_M_HEAL_BELL}enjoye{SE_M_WATERFALL}battlin{SE_M_SANDSTORM}you!\p"
	.string "Bu{SE_M_SPIT_UP}{SE_M_CHARGE}los{SE_M_GRASSWHISTLE}i{SE_M_GRASSWHISTLE}{SE_M_CHARGE}loss!\p"
	.string "Fro{SE_M_MILK_DRINK}no{SE_M_TWISTER}on{SE_M_SUPERSONIC}I'{SE_M_MILK_DRINK}goin{SE_M_SANDSTORM}t{SE_M_ATTRACT2}train\n"
	.string "2{SE_M_WHIRLPOOL}hour{SE_M_GRASSWHISTLE}{SE_M_CHARGE}day!$"

CianwoodGym_Text_ChuckRematch:
	.string "WAHAHAH{SE_M_DRAGON_RAGE}JOHT{SE_M_SOLAR_BEAM}CHAMPION!\p"
	.string "You'v{SE_M_REVERSAL}com{SE_M_REVERSAL}bac{SE_M_ENCORE2}fo{SE_M_SAND_TOMB}more!\p"
	.string "{SE_M_HEAL_BELL}se{SE_M_REVERSAL}you{SE_M_SAND_TOMB}skill{SE_M_GRASSWHISTLE}hav{SE_M_REVERSAL}improved!\p"
	.string "Read{SE_M_YAWN}t{SE_M_ATTRACT2}se{SE_M_REVERSAL}who'{SE_M_GRASSWHISTLE}stronger?$"

CianwoodGym_Text_ChuckRematchDefeat:
	.string "Wha{SE_M_SING}Huh{SE_M_SING}{SE_M_HEAL_BELL}lost?\n"
	.string "Again?$"

CianwoodGym_EventScript_Yoshi::
	trainerbattle_single 1324, CianwoodGym_Text_BlackbeltYoshiSeen, CianwoodGym_Text_BlackbeltYoshiBeaten
	msgbox CianwoodGym_Text_BlackbeltYoshiAfter, MSGBOX_AUTOCLOSE
	end

CianwoodGym_Text_BlackbeltYoshiSeen:
	.string "M{SE_M_YAWN}POKéMO{SE_M_PSYBEAM2}an{SE_M_WATERFALL}{SE_M_HEAL_BELL}ar{SE_M_REVERSAL}boun{SE_M_WATERFALL}togeth-\n"
	.string "e{SE_M_SAND_TOMB}b{SE_M_YAWN}friendship.\p"
	.string "Ou{SE_M_SAND_TOMB}bon{SE_M_WATERFALL}wil{SE_M_BATON_PASS}neve{SE_M_SAND_TOMB}b{SE_M_REVERSAL}broken!$"

CianwoodGym_Text_BlackbeltYoshiBeaten:
	.string "Thi{SE_M_GRASSWHISTLE}isn'{SE_M_SPIT_UP}real!$"

CianwoodGym_Text_BlackbeltYoshiAfter:
	.string "Yo{SE_M_DIVE}see{SE_M_MILK_DRINK}t{SE_M_ATTRACT2}hav{SE_M_REVERSAL}{SE_M_CHARGE}stron{SE_M_SANDSTORM}bond\n"
	.string "wit{SE_M_TRI_ATTACK}you{SE_M_SAND_TOMB}POKéMO{SE_M_PSYBEAM2}too!$"

CianwoodGym_EventScript_Lao::
	trainerbattle_single 1325, CianwoodGym_Text_BlackbeltLaoSeen, CianwoodGym_Text_BlackbeltLaoBeaten
	msgbox CianwoodGym_Text_BlackbeltLaoAfter, MSGBOX_AUTOCLOSE
	end

CianwoodGym_Text_BlackbeltLaoSeen:
	.string "W{SE_M_REVERSAL}martia{SE_M_BATON_PASS}artist{SE_M_GRASSWHISTLE}fea{SE_M_SAND_TOMB}nothing!$"

CianwoodGym_Text_BlackbeltLaoBeaten:
	.string "That'{SE_M_GRASSWHISTLE}shocking!$"

CianwoodGym_Text_BlackbeltLaoAfter:
	.string "Fightin{SE_M_SANDSTORM}POKéMO{SE_M_PSYBEAM2}ar{SE_M_REVERSAL}afrai{SE_M_WATERFALL}of\n"
	.string "psychics…$"

CianwoodGym_EventScript_Nob::
	trainerbattle_single 1326, CianwoodGym_Text_BlackbeltNobSeen, CianwoodGym_Text_BlackbeltNobBeaten
	msgbox CianwoodGym_Text_BlackbeltNobAfter, MSGBOX_AUTOCLOSE
	end

CianwoodGym_Text_BlackbeltNobSeen:
	.string "Word{SE_M_GRASSWHISTLE}ar{SE_M_REVERSAL}useless.\n"
	.string "Le{SE_M_SPIT_UP}you{SE_M_SAND_TOMB}fist{SE_M_GRASSWHISTLE}d{SE_M_ATTRACT2}th{SE_M_REVERSAL}talking!$"

CianwoodGym_Text_BlackbeltNobBeaten:
	.string "…$"

CianwoodGym_Text_BlackbeltNobAfter:
	.string "{SE_M_HEAL_BELL}lost{SE_M_DRAGON_RAGE}I'{SE_M_MILK_DRINK}speechless!$"

CianwoodGym_EventScript_Lung::
	trainerbattle_single 1328, CianwoodGym_Text_BlackbeltLungSeen, CianwoodGym_Text_BlackbeltLungBeaten
	msgbox CianwoodGym_Text_BlackbeltLungAfter, MSGBOX_AUTOCLOSE
	end

CianwoodGym_Text_BlackbeltLungSeen:
	.string "M{SE_M_YAWN}ragin{SE_M_SANDSTORM}fist{SE_M_GRASSWHISTLE}wil{SE_M_BATON_PASS}shatte{SE_M_SAND_TOMB}your\n"
	.string "POKéMON!$"

CianwoodGym_Text_BlackbeltLungBeaten:
	.string "{SE_M_HEAL_BELL}go{SE_M_SPIT_UP}shattered!$"

CianwoodGym_Text_BlackbeltLungAfter:
	.string "M{SE_M_YAWN}POKéMO{SE_M_PSYBEAM2}lost…\n"
	.string "My{SE_M_DIZZY_PUNCH}m{SE_M_YAWN}prid{SE_M_REVERSAL}i{SE_M_GRASSWHISTLE}shattered…$"

