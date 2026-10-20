@ Johto (data/maps/BlackthornCity_Gym_hns/scripts.inc), as built into the FireRed game.

BlackthornCity_Gym_hns_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, BlackthornGym_OnLoad
	.byte 0

BlackthornGym_OnLoad::
	call_if_eq JOHTO_VAR_BLACKTHORN_GYM_STATE, 1, BlackthornGym_MapScript_Var1
	call_if_eq JOHTO_VAR_BLACKTHORN_GYM_STATE, 2, BlackthornGym_MapScript_Var2
	call_if_eq JOHTO_VAR_BLACKTHORN_GYM_STATE, 3, BlackthornGym_MapScript_Var3
	call_if_eq JOHTO_VAR_BLACKTHORN_GYM_STATE, 4, BlackthornGym_MapScript_Var4
	end

BlackthornGym_MapScript_Var1::
	call BlackthornGym_MapScript_BuildBridge1
	end

BlackthornGym_MapScript_Var2::
	call BlackthornGym_MapScript_BuildBridge1
	call BlackthornGym_MapScript_BuildBridge2
	end

BlackthornGym_MapScript_Var3::
	call BlackthornGym_MapScript_BuildBridge1
	call BlackthornGym_MapScript_BuildBridge2
	call BlackthornGym_MapScript_BuildBridge3
	end

BlackthornGym_MapScript_Var4::
	call BlackthornGym_MapScript_BuildBridge1
	call BlackthornGym_MapScript_BuildBridge2
	call BlackthornGym_MapScript_BuildBridge3
	call BlackthornGym_MapScript_BuildBridge4
	end

BlackthornGym_TriggerBridge1::
	call BlackthornGym_MapScript_BuildBridge1
	playse SE_BANG
	special DrawWholeMapView
	setvar JOHTO_VAR_BLACKTHORN_GYM_STATE, 1
	end

BlackthornGym_MapScript_BuildBridge1::
	setmetatile 19, 47, 0x35A, FALSE
	setmetatile 19, 48, 0x35A, FALSE
	setmetatile 19, 49, 0x35A, FALSE
	setmetatile 19, 50, 0x35A, FALSE
	setmetatile 19, 51, 0x35A, FALSE
	setmetatile 19, 52, 0x35A, FALSE
	setmetatile 19, 53, 0x35A, FALSE
	setmetatile 19, 54, 0x35A, FALSE
	setmetatile 20, 47, 0x35A, FALSE
	setmetatile 20, 48, 0x35A, FALSE
	setmetatile 20, 49, 0x35A, FALSE
	setmetatile 20, 50, 0x35A, FALSE
	setmetatile 20, 51, 0x35A, FALSE
	setmetatile 20, 52, 0x35A, FALSE
	setmetatile 20, 53, 0x35A, FALSE
	setmetatile 20, 54, 0x35A, FALSE
	setmetatile 21, 47, 0x35A, FALSE
	setmetatile 21, 48, 0x35A, FALSE
	setmetatile 21, 49, 0x35A, FALSE
	setmetatile 21, 50, 0x35A, FALSE
	setmetatile 21, 51, 0x35A, FALSE
	setmetatile 21, 52, 0x35A, FALSE
	setmetatile 21, 53, 0x35A, FALSE
	setmetatile 21, 54, 0x35A, FALSE
	return

BlackthornGym_TriggerBridge2::
	call BlackthornGym_MapScript_BuildBridge2
	playse SE_BANG
	special DrawWholeMapView
	setvar JOHTO_VAR_BLACKTHORN_GYM_STATE, 2
	end

BlackthornGym_MapScript_BuildBridge2::
	setmetatile 17, 35, 0x35A, FALSE
	setmetatile 17, 36, 0x35A, FALSE
	setmetatile 17, 37, 0x35A, FALSE
	setmetatile 17, 38, 0x35A, FALSE
	setmetatile 17, 39, 0x35A, FALSE
	setmetatile 17, 40, 0x35A, FALSE
	setmetatile 18, 35, 0x35A, FALSE
	setmetatile 18, 36, 0x35A, FALSE
	setmetatile 18, 37, 0x35A, FALSE
	setmetatile 18, 38, 0x35A, FALSE
	setmetatile 18, 39, 0x35A, FALSE
	setmetatile 18, 40, 0x35A, FALSE
	setmetatile 19, 35, 0x35A, FALSE
	setmetatile 19, 36, 0x35A, FALSE
	setmetatile 19, 37, 0x35A, FALSE
	setmetatile 19, 38, 0x35A, FALSE
	setmetatile 19, 39, 0x35A, FALSE
	setmetatile 19, 40, 0x35A, FALSE
	setmetatile 20, 32, 0x359, FALSE
	setmetatile 21, 32, 0x359, FALSE
	setmetatile 22, 32, 0x359, FALSE
	setmetatile 20, 35, 0x361, TRUE
	setmetatile 21, 35, 0x361, TRUE
	setmetatile 22, 35, 0x361, TRUE
	setmetatile 20, 33, 0x35A, FALSE
	setmetatile 20, 34, 0x35A, FALSE
	setmetatile 21, 33, 0x35A, FALSE
	setmetatile 21, 34, 0x35A, FALSE
	setmetatile 22, 33, 0x35A, FALSE
	setmetatile 22, 34, 0x35A, FALSE
	return

BlackthornGym_TriggerBridge3::
	call BlackthornGym_MapScript_BuildBridge3
	playse SE_BANG
	special DrawWholeMapView
	setvar JOHTO_VAR_BLACKTHORN_GYM_STATE, 3
	end

BlackthornGym_MapScript_BuildBridge3::
	setmetatile 17, 26, 0x359, FALSE
	setmetatile 18, 26, 0x359, FALSE
	setmetatile 19, 26, 0x359, FALSE
	setmetatile 20, 26, 0x359, FALSE
	setmetatile 21, 26, 0x359, FALSE
	setmetatile 22, 26, 0x359, FALSE
	setmetatile 23, 26, 0x359, FALSE

	setmetatile 17, 29, 0x361, TRUE
	setmetatile 18, 29, 0x361, TRUE
	setmetatile 19, 29, 0x361, TRUE
	setmetatile 20, 29, 0x361, TRUE
	setmetatile 21, 29, 0x361, TRUE
	setmetatile 22, 29, 0x361, TRUE
	setmetatile 23, 29, 0x361, TRUE

	setmetatile 17, 27, 0x35A, FALSE
	setmetatile 17, 28, 0x35A, FALSE
	setmetatile 18, 27, 0x35A, FALSE
	setmetatile 18, 28, 0x35A, FALSE
	setmetatile 19, 27, 0x35A, FALSE
	setmetatile 19, 28, 0x35A, FALSE
	setmetatile 20, 27, 0x35A, FALSE
	setmetatile 20, 28, 0x35A, FALSE
	setmetatile 21, 27, 0x35A, FALSE
	setmetatile 21, 28, 0x35A, FALSE
	setmetatile 22, 27, 0x35A, FALSE
	setmetatile 22, 28, 0x35A, FALSE
	setmetatile 23, 27, 0x35A, FALSE
	setmetatile 23, 28, 0x35A, FALSE
	return

BlackthornGym_TriggerBridge4::
	call BlackthornGym_MapScript_BuildBridge4
	playse SE_BANG
	special DrawWholeMapView
	setvar JOHTO_VAR_BLACKTHORN_GYM_STATE, 4
	end

BlackthornGym_MapScript_BuildBridge4::
	setmetatile 19, 11, 0x35A, FALSE
	setmetatile 19, 12, 0x35A, FALSE
	setmetatile 19, 13, 0x35A, FALSE
	setmetatile 19, 14, 0x35A, FALSE
	setmetatile 19, 15, 0x35A, FALSE
	setmetatile 20, 11, 0x35A, FALSE
	setmetatile 20, 12, 0x35A, FALSE
	setmetatile 20, 13, 0x35A, FALSE
	setmetatile 20, 14, 0x35A, FALSE
	setmetatile 20, 15, 0x35A, FALSE
	setmetatile 21, 11, 0x35A, FALSE
	setmetatile 21, 12, 0x35A, FALSE
	setmetatile 21, 13, 0x35A, FALSE
	setmetatile 21, 14, 0x35A, FALSE
	setmetatile 21, 15, 0x35A, FALSE
	return

BlackthornGym_EventScript_Cody::
	trainerbattle_single TRAINER_JOHTO_CODY_HNS, BlackthornGym_Text_CooltrainermCodySeenText, BlackthornGym_Text_CooltrainermCodyBeatenText
	msgbox BlackthornGym_Text_CooltrainermCodyAfterBattleText, MSGBOX_AUTOCLOSE
	end

BlackthornGym_EventScript_Fran::
	trainerbattle_single TRAINER_JOHTO_FRAN_HNS, BlackthornGym_Text_CooltrainerfFranSeenText, BlackthornGym_Text_CooltrainerfFranBeatenText
	msgbox BlackthornGym_Text_CooltrainerfFranAfterBattleText, MSGBOX_AUTOCLOSE
	end

BlackthornGym_EventScript_Paul::
	trainerbattle_single TRAINER_JOHTO_PAUL_HNS, BlackthornGym_Text_CooltrainermPaulSeenText, BlackthornGym_Text_CooltrainermPaulBeatenText
	msgbox BlackthornGym_Text_CooltrainermPaulAfterBattleText, MSGBOX_AUTOCLOSE
	end

BlackthornGym_EventScript_Mike::
	trainerbattle_single TRAINER_JOHTO_MIKE_HNS, BlackthornGym_Text_CooltrainermMikeSeenText, BlackthornGym_Text_CooltrainermMikeBeatenText
	msgbox BlackthornGym_Text_CooltrainermMikeAfterBattleText, MSGBOX_AUTOCLOSE
	end

BlackthornGym_EventScript_Lola::
	trainerbattle_single TRAINER_JOHTO_LOLA_HNS, BlackthornGym_Text_CooltrainerfLolaSeenText, BlackthornGym_Text_CooltrainerfLolaBeatenText
	msgbox BlackthornGym_Text_CooltrainerfLolaAfterBattleText, MSGBOX_AUTOCLOSE
	end

BlackthornGym_EventScript_Clair::
	lock
	faceplayer
	goto_if_set JOHTO_FLAG_IS_CHAMPION, BlackthornGym_EventScript_ClairAfterLeague
	goto_if_ge JOHTO_VAR_BLACKTHORN_CITY_STATE, 4, BlackthornGym_EventScript_Clair_Defeated
	goto_if_eq JOHTO_VAR_BLACKTHORN_CITY_STATE, 2, BlackthornGym_EventScript_ClairDuringChallenge
	msgbox BlackthornGym_Text_ClairIntroText, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_JOHTO_CLAIR_1_HNS, BlackthornGym_Text_ClairWinText
	msgbox BlackthornGym_Text_ClairText_GoToDragonsDen, MSGBOX_DEFAULT
	setflag JOHTO_FLAG_DEFEATED_BLACKTHORN_GYM
	setvar VAR_0x8008, 8
	call J_Common_EventScript_SetGymTrainers_hns
	setvar JOHTO_VAR_BLACKTHORN_CITY_STATE, 2
	closemessage
	release
	end

BlackthornGym_EventScript_ClairDuringChallenge::
	msgbox BlackthornGym_Text_ClairText_TooMuchToExpect, MSGBOX_DEFAULT
	closemessage
	release
	end

BlackthornGym_EventScript_Clair_Defeated::
	msgbox BlackthornGym_Text_ClairText_League, MSGBOX_DEFAULT
	closemessage
	release
	end

BlackthornGym_EventScript_ClairAfterLeague::
	msgbox BlackthornGym_Text_ClairAfterLeague, MSGBOX_DEFAULT
	closemessage
	release
	end

BlackthornGym_Text_ClairIntroText:
	.string "{SE_M_HEAL_BELL}a{SE_M_MILK_DRINK}CLAIR.\p"
	.string "Th{SE_M_REVERSAL}world'{SE_M_GRASSWHISTLE}bes{SE_M_SPIT_UP}drago{SE_M_ATTRACT}master.\p"
	.string "{SE_M_HEAL_BELL}ca{SE_M_ATTRACT}hol{SE_M_WATERFALL}m{SE_M_YAWN}ow{SE_M_ATTRACT}agains{SE_M_SPIT_UP}eve{SE_M_ATTRACT}the\n"
	.string "POKéMO{SE_M_PSYBEAM2}LEAGUE'{SE_M_GRASSWHISTLE}ELIT{SE_M_SWORDS_DANCE}FOUR.\p"
	.string "D{SE_M_ATTRACT2}yo{SE_M_DIVE}stil{SE_M_BATON_PASS}wan{SE_M_SPIT_UP}t{SE_M_ATTRACT2}tak{SE_M_REVERSAL}m{SE_M_REVERSAL}on?\p"
	.string "…Fine{SE_M_PERISH_SONG}Let'{SE_M_GRASSWHISTLE}d{SE_M_ATTRACT2}it!\p"
	.string "A{SE_M_GRASSWHISTLE}{SE_M_CHARGE}GY{SE_M_GIGA_DRAIN}LEADER{SE_M_SUPERSONIC}{SE_M_HEAL_BELL}wil{SE_M_BATON_PASS}us{SE_M_REVERSAL}m{SE_M_YAWN}full\n"
	.string "powe{SE_M_SAND_TOMB}agains{SE_M_SPIT_UP}an{SE_M_YAWN}opponent!$"

BlackthornGym_Text_ClairWinText:
	.string "{SE_M_HEAL_BELL}lost?\p"
	.string "{SE_M_HEAL_BELL}don'{SE_M_SPIT_UP}believ{SE_M_REVERSAL}it{SE_M_PERISH_SONG}Ther{SE_M_REVERSAL}mus{SE_M_SPIT_UP}be\n"
	.string "som{SE_M_REVERSAL}mistake…$"

BlackthornGym_Text_ClairText_GoToDragonsDen:
	.string "{SE_M_HEAL_BELL}won'{SE_M_SPIT_UP}admi{SE_M_SPIT_UP}this.\p"
	.string "{SE_M_HEAL_BELL}ma{SE_M_YAWN}hav{SE_M_REVERSAL}lost{SE_M_SUPERSONIC}bu{SE_M_SPIT_UP}you'r{SE_M_REVERSAL}still\n"
	.string "no{SE_M_SPIT_UP}read{SE_M_YAWN}fo{SE_M_SAND_TOMB}th{SE_M_REVERSAL}POKéMO{SE_M_PSYBEAM2}LEAGUE.\p"
	.string "{SE_M_HEAL_BELL}know{SE_M_PERISH_SONG}Yo{SE_M_DIVE}shoul{SE_M_WATERFALL}tak{SE_M_REVERSAL}th{SE_M_REVERSAL}dragon-\n"
	.string "use{SE_M_SAND_TOMB}challenge.\p"
	.string "Behin{SE_M_WATERFALL}thi{SE_M_GRASSWHISTLE}GY{SE_M_GIGA_DRAIN}i{SE_M_GRASSWHISTLE}{SE_M_CHARGE}plac{SE_M_REVERSAL}called\n"
	.string "DRAGON'{SE_M_SKETCH}DEN.\p"
	.string "Ther{SE_M_REVERSAL}i{SE_M_GRASSWHISTLE}{SE_M_CHARGE}smal{SE_M_BATON_PASS}shrin{SE_M_REVERSAL}a{SE_M_SPIT_UP}its\n"
	.string "center{SE_M_PERISH_SONG}G{SE_M_ATTRACT2}there.\p"
	.string "I{SE_M_ACID_ARMOR}yo{SE_M_DIVE}ca{SE_M_ATTRACT}prov{SE_M_REVERSAL}tha{SE_M_SPIT_UP}you'v{SE_M_REVERSAL}lost\n"
	.string "you{SE_M_SAND_TOMB}laz{SE_M_YAWN}ideals{SE_M_SUPERSONIC}{SE_M_HEAL_BELL}wil{SE_M_BATON_PASS}recognize\l"
	.string "yo{SE_M_DIVE}a{SE_M_GRASSWHISTLE}{SE_M_CHARGE}traine{SE_M_SAND_TOMB}worth{SE_M_YAWN}o{SE_M_ACID_ARMOR}{SE_M_CHARGE}GYM\l"
	.string "BADGE!$"

BlackthornGym_Text_ClairText_TooMuchToExpect:
	.string "What'{SE_M_GRASSWHISTLE}th{SE_M_REVERSAL}matter?\p"
	.string "I{SE_M_GRASSWHISTLE}i{SE_M_SPIT_UP}to{SE_M_ATTRACT2}muc{SE_M_TRI_ATTACK}t{SE_M_ATTRACT2}expec{SE_M_SPIT_UP}o{SE_M_ACID_ARMOR}you?$"

BlackthornGym_Text_ClairText_YouKeptMeWaiting:
	.string "You'v{SE_M_REVERSAL}kep{SE_M_SPIT_UP}m{SE_M_REVERSAL}waiting!\p"
	.string "Here{SE_M_DRAGON_RAGE}Tak{SE_M_REVERSAL}this!$"

BlackthornGym_Text_ClairText_DescribeTM:
	.string "Tha{SE_M_SPIT_UP}contain{SE_M_GRASSWHISTLE}DRAGO{SE_M_PSYBEAM2}CLAW.\p"
	.string "Yo{SE_M_DIVE}ca{SE_M_ATTRACT}figur{SE_M_REVERSAL}ou{SE_M_SPIT_UP}wha{SE_M_SPIT_UP}i{SE_M_SPIT_UP}does.$"

BlackthornGym_Text_ClairText_League:
	.string "What'{SE_M_GRASSWHISTLE}th{SE_M_REVERSAL}matter?\p"
	.string "Aren'{SE_M_SPIT_UP}yo{SE_M_DIVE}heade{SE_M_WATERFALL}t{SE_M_ATTRACT2}th{SE_M_REVERSAL}POKéMON\n"
	.string "LEAGUE?\p"
	.string "Don'{SE_M_SPIT_UP}yo{SE_M_DIVE}kno{SE_M_TWISTER}wher{SE_M_REVERSAL}i{SE_M_SPIT_UP}is?\p"
	.string "Fro{SE_M_MILK_DRINK}here{SE_M_SUPERSONIC}g{SE_M_ATTRACT2}t{SE_M_ATTRACT2}NE{SE_M_DETECT}BAR{SE_M_SNORE}TOWN.\p"
	.string "The{SE_M_ATTRACT}SUR{SE_M_LEER}east{SE_M_PERISH_SONG}Th{SE_M_REVERSAL}rout{SE_M_REVERSAL}ther{SE_M_REVERSAL}is\n"
	.string "ver{SE_M_YAWN}tough.\p"
	.string "Don'{SE_M_SPIT_UP}yo{SE_M_DIVE}dar{SE_M_REVERSAL}los{SE_M_REVERSAL}a{SE_M_SPIT_UP}th{SE_M_REVERSAL}POKéMON\n"
	.string "LEAGUE!\p"
	.string "I{SE_M_ACID_ARMOR}yo{SE_M_DIVE}do{SE_M_SUPERSONIC}I'l{SE_M_BATON_PASS}fee{SE_M_BATON_PASS}eve{SE_M_ATTRACT}worse\n"
	.string "abou{SE_M_SPIT_UP}havin{SE_M_SANDSTORM}los{SE_M_SPIT_UP}t{SE_M_ATTRACT2}you!\p"
	.string "Giv{SE_M_REVERSAL}i{SE_M_SPIT_UP}everythin{SE_M_SANDSTORM}you'v{SE_M_REVERSAL}got.$"

BlackthornGym_Text_ClairAfterLeague:
	.string "Yo{SE_M_DIVE}di{SE_M_WATERFALL}it{SE_M_SUPERSONIC}huh?\p"
	.string "Yo{SE_M_DIVE}ar{SE_M_REVERSAL}no{SE_M_TWISTER}th{SE_M_REVERSAL}JOHT{SE_M_SOLAR_BEAM}CHAMP.$"

BlackthornGym_Text_ClairRematchText:
	.string "Yo{SE_M_DIVE}di{SE_M_WATERFALL}it{SE_M_SUPERSONIC}huh?\p"
	.string "Yo{SE_M_DIVE}ar{SE_M_REVERSAL}no{SE_M_TWISTER}th{SE_M_REVERSAL}JOHT{SE_M_SOLAR_BEAM}CHAMP.\p"
	.string "You'v{SE_M_REVERSAL}prove{SE_M_ATTRACT}you{SE_M_SAND_TOMB}strengt{SE_M_TRI_ATTACK}bu{SE_M_SPIT_UP}can\n"
	.string "yo{SE_M_DIVE}handl{SE_M_REVERSAL}m{SE_M_REVERSAL}again?\p"
	.string "A{SE_M_GRASSWHISTLE}{SE_M_CHARGE}Drago{SE_M_ATTRACT}Master{SE_M_SUPERSONIC}{SE_M_HEAL_BELL}won'{SE_M_SPIT_UP}hold\n"
	.string "back.\p"
	.string "No{SE_M_SPIT_UP}thi{SE_M_GRASSWHISTLE}time.\p"
	.string "Wan{SE_M_SPIT_UP}t{SE_M_ATTRACT2}hav{SE_M_REVERSAL}{SE_M_CHARGE}rematc{SE_M_TRI_ATTACK}wit{SE_M_TRI_ATTACK}me?$"

BlackthornGym_Text_ClairRematchDefeatText:
	.string "{SE_M_HEAL_BELL}lost?\p"
	.string "Again?\p"
	.string "{SE_M_HEAL_BELL}don'{SE_M_SPIT_UP}believ{SE_M_REVERSAL}it{SE_M_PERISH_SONG}Ther{SE_M_REVERSAL}mus{SE_M_SPIT_UP}be\n"
	.string "som{SE_M_REVERSAL}mistake…$"

BlackthornGym_Text_CooltrainermCodySeenText:
	.string "{SE_M_HEAL_BELL}jus{SE_M_SPIT_UP}go{SE_M_SPIT_UP}acces{SE_M_GRASSWHISTLE}t{SE_M_ATTRACT2}us{SE_M_REVERSAL}DRAGON-\n"
	.string "typ{SE_M_REVERSAL}POKéMON!$"

BlackthornGym_Text_CooltrainermCodyBeatenText:
	.string "Rats{SE_M_DRAGON_RAGE}I{SE_M_ACID_ARMOR}onl{SE_M_YAWN}{SE_M_HEAL_BELL}ha{SE_M_WATERFALL}{SE_M_CHARGE}DRAGONITE!$"

BlackthornGym_Text_CooltrainermCodyAfterBattleText:
	.string "Member{SE_M_GRASSWHISTLE}o{SE_M_ACID_ARMOR}ou{SE_M_SAND_TOMB}dragon-use{SE_M_SAND_TOMB}clan\n"
	.string "ca{SE_M_ATTRACT}us{SE_M_REVERSAL}drago{SE_M_ATTRACT}POKéMO{SE_M_PSYBEAM2}onl{SE_M_YAWN}after\l"
	.string "ou{SE_M_SAND_TOMB}MASTE{SE_M_MINIMIZE}allow{SE_M_GRASSWHISTLE}it.$"

BlackthornGym_Text_CooltrainerfFranSeenText:
	.string "{SE_M_HEAL_BELL}can'{SE_M_SPIT_UP}allo{SE_M_TWISTER}{SE_M_CHARGE}nameles{SE_M_GRASSWHISTLE}trainer\n"
	.string "pas{SE_M_SPIT_UP}me!\p"
	.string "CLAI{SE_M_MINIMIZE}woul{SE_M_WATERFALL}b{SE_M_REVERSAL}livi{SE_M_WATERFALL}i{SE_M_ACID_ARMOR}{SE_M_HEAL_BELL}did!$"

BlackthornGym_Text_CooltrainerfFranBeatenText:
	.string "Awww{SE_M_DIZZY_PUNCH}{SE_M_HEAL_BELL}lost…$"

BlackthornGym_Text_CooltrainerfFranAfterBattleText:
	.string "Uh-oh{SE_M_DIZZY_PUNCH}CLAI{SE_M_MINIMIZE}i{SE_M_GRASSWHISTLE}goin{SE_M_SANDSTORM}t{SE_M_ATTRACT2}b{SE_M_REVERSAL}mad…$"

BlackthornGym_Text_CooltrainermPaulSeenText:
	.string "You{SE_M_SAND_TOMB}firs{SE_M_SPIT_UP}battl{SE_M_REVERSAL}agains{SE_M_SPIT_UP}dragons?\p"
	.string "I'l{SE_M_BATON_PASS}sho{SE_M_TWISTER}yo{SE_M_DIVE}ho{SE_M_TWISTER}toug{SE_M_TRI_ATTACK}the{SE_M_YAWN}are!$"

BlackthornGym_Text_CooltrainermPaulBeatenText:
	.string "M{SE_M_YAWN}drago{SE_M_ATTRACT}POKéMO{SE_M_PSYBEAM2}lost?$"

BlackthornGym_Text_CooltrainermPaulAfterBattleText:
	.string "LANC{SE_M_SWORDS_DANCE}tol{SE_M_WATERFALL}yo{SE_M_DIVE}tha{SE_M_SPIT_UP}he'{SE_M_WATERFALL}lik{SE_M_REVERSAL}to\n"
	.string "se{SE_M_REVERSAL}yo{SE_M_DIVE}again?\p"
	.string "No{SE_M_SPIT_UP}{SE_M_CHARGE}chance!$"

BlackthornGym_Text_CooltrainermMikeSeenText:
	.string "M{SE_M_YAWN}chanc{SE_M_REVERSAL}o{SE_M_ACID_ARMOR}losing{SE_M_SING}No{SE_M_SPIT_UP}eve{SE_M_ATTRACT}one\n"
	.string "percent!$"

BlackthornGym_Text_CooltrainermMikeBeatenText:
	.string "That'{SE_M_GRASSWHISTLE}odd.$"

BlackthornGym_Text_CooltrainermMikeAfterBattleText:
	.string "{SE_M_HEAL_BELL}kno{SE_M_TWISTER}m{SE_M_YAWN}short-coming{SE_M_GRASSWHISTLE}now.\p"
	.string "Thank{SE_M_GRASSWHISTLE}fo{SE_M_SAND_TOMB}showin{SE_M_SANDSTORM}me!$"

BlackthornGym_Text_CooltrainerfLolaSeenText:
	.string "Dragon{SE_M_GRASSWHISTLE}ar{SE_M_REVERSAL}sacre{SE_M_WATERFALL}POKéMON.\p"
	.string "The{SE_M_YAWN}ar{SE_M_REVERSAL}ful{SE_M_BATON_PASS}o{SE_M_ACID_ARMOR}lif{SE_M_REVERSAL}energy.\p"
	.string "I{SE_M_ACID_ARMOR}you'r{SE_M_REVERSAL}no{SE_M_SPIT_UP}serious{SE_M_SUPERSONIC}yo{SE_M_DIVE}won't\n"
	.string "b{SE_M_REVERSAL}abl{SE_M_REVERSAL}t{SE_M_ATTRACT2}bea{SE_M_SPIT_UP}them.$"

BlackthornGym_Text_CooltrainerfLolaBeatenText:
	.string "Wa{SE_M_YAWN}t{SE_M_ATTRACT2}go!$"

BlackthornGym_Text_CooltrainerfLolaAfterBattleText:
	.string "Dragon{SE_M_GRASSWHISTLE}ar{SE_M_REVERSAL}wea{SE_M_ENCORE2}agains{SE_M_SPIT_UP}DRAGON-\n"
	.string "typ{SE_M_REVERSAL}moves.$"

BlackthornGym_EventScript_GymGuy::
	lock
	faceplayer
	goto_if_set JOHTO_FLAG_DEFEATED_BLACKTHORN_GYM, BlackthornGym_EventScript_GymGuy2
	msgbox BlackthornGym_Text_GuideText, MSGBOX_DEFAULT
	closemessage
	release
	end

BlackthornGym_EventScript_GymGuy2::
	goto_if_set JOHTO_FLAG_BADGE08_GET, BlackthornGym_EventScript_GymGuy3
	msgbox BlackthornGym_Text_GuideGotoDragonsDen, MSGBOX_DEFAULT
	release
	end

BlackthornGym_EventScript_GymGuy3::
	msgbox BlackthornGym_Text_GuideWinText, MSGBOX_DEFAULT
	release
	end

BlackthornGym_Text_GuideText:
	.string "Yo{SE_M_DRAGON_RAGE}CHAM{SE_M_PETAL_DANCE}i{SE_M_ATTRACT}making!\p"
	.string "It'{SE_M_GRASSWHISTLE}bee{SE_M_ATTRACT}{SE_M_CHARGE}lon{SE_M_SANDSTORM}journey{SE_M_SUPERSONIC}bu{SE_M_SPIT_UP}we\n"
	.string "ar{SE_M_REVERSAL}almos{SE_M_SPIT_UP}done{SE_M_DRAGON_RAGE}Coun{SE_M_SPIT_UP}o{SE_M_ATTRACT}me!\p"
	.string "Whil{SE_M_REVERSAL}CLAI{SE_M_MINIMIZE}look{SE_M_GRASSWHISTLE}u{SE_M_MORNING_SUN}t{SE_M_ATTRACT2}th{SE_M_REVERSAL}Dragon\n"
	.string "Master{SE_M_SUPERSONIC}LANCE{SE_M_SUPERSONIC}she'{SE_M_GRASSWHISTLE}manage{SE_M_WATERFALL}to\l"
	.string "creat{SE_M_REVERSAL}he{SE_M_SAND_TOMB}ow{SE_M_ATTRACT}identit{SE_M_YAWN}wit{SE_M_TRI_ATTACK}a\l"
	.string "tea{SE_M_MILK_DRINK}consistin{SE_M_SANDSTORM}o{SE_M_ACID_ARMOR}dragon{SE_M_GRASSWHISTLE}from\l"
	.string "th{SE_M_REVERSAL}sea.\p"
	.string "Dragon{SE_M_GRASSWHISTLE}ar{SE_M_REVERSAL}suppose{SE_M_WATERFALL}t{SE_M_ATTRACT2}be\n"
	.string "wea{SE_M_ENCORE2}agains{SE_M_SPIT_UP}ICE-typ{SE_M_REVERSAL}moves,\l"
	.string "bu{SE_M_SPIT_UP}you'l{SE_M_BATON_PASS}nee{SE_M_WATERFALL}som{SE_M_REVERSAL}DRAGON-type\l"
	.string "o{SE_M_SAND_TOMB}FAIRY-typ{SE_M_REVERSAL}move{SE_M_GRASSWHISTLE}o{SE_M_ACID_ARMOR}you{SE_M_SAND_TOMB}ow{SE_M_ATTRACT}if\l"
	.string "yo{SE_M_DIVE}wan{SE_M_SPIT_UP}t{SE_M_ATTRACT2}win.$"
	.string "Yo{SE_M_DIVE}go{SE_M_SPIT_UP}this!$"

BlackthornGym_Text_GuideGotoDragonsDen:
	.string "Yo{SE_M_DIVE}wer{SE_M_REVERSAL}grea{SE_M_SPIT_UP}t{SE_M_ATTRACT2}bea{SE_M_SPIT_UP}CLAIR!\p"
	.string "Sh{SE_M_REVERSAL}ca{SE_M_ATTRACT}b{SE_M_REVERSAL}{SE_M_CHARGE}bi{SE_M_SPIT_UP}o{SE_M_ACID_ARMOR}{SE_M_CHARGE}sor{SE_M_REVERSAL}loser,\n"
	.string "though\p"
	.string "Sound{SE_M_GRASSWHISTLE}lik{SE_M_REVERSAL}yo{SE_M_DIVE}nee{SE_M_WATERFALL}t{SE_M_ATTRACT2}hea{SE_M_WATERFALL}t{SE_M_ATTRACT2}the\n"
	.string "DRAGON'{SE_M_SKETCH}DE{SE_M_PSYBEAM2}i{SE_M_ACID_ARMOR}yo{SE_M_DIVE}wan{SE_M_SPIT_UP}tha{SE_M_SPIT_UP}GY{SE_M_GIGA_DRAIN}BADGE!$"

BlackthornGym_Text_GuideWinText:
	.string "Yo{SE_M_DIVE}wer{SE_M_REVERSAL}grea{SE_M_SPIT_UP}t{SE_M_ATTRACT2}bea{SE_M_SPIT_UP}CLAIR!\p"
	.string "Al{SE_M_BATON_PASS}that'{SE_M_GRASSWHISTLE}lef{SE_M_SPIT_UP}i{SE_M_GRASSWHISTLE}th{SE_M_REVERSAL}POKéMON\n"
	.string "LEAGU{SE_M_SWORDS_DANCE}challenge.\p"
	.string "You'r{SE_M_REVERSAL}o{SE_M_ATTRACT}th{SE_M_REVERSAL}wa{SE_M_YAWN}t{SE_M_ATTRACT2}becomin{SE_M_SANDSTORM}the\n"
	.string "POKéMO{SE_M_PSYBEAM2}CHAMPION!$"

BlackthornGym_EventScript_Statue::
	lock
	goto_if_set JOHTO_FLAG_BADGE08_GET, BlackthornGym_EventScript_Statue2
	msgbox BlackthornGym_Text_GymStatue, MSGBOX_DEFAULT
	closemessage
	release
	end

BlackthornGym_EventScript_Statue2::
	msgbox BlackthornGym_Text_GymStatueCertified, MSGBOX_DEFAULT
	closemessage
	release
	end

BlackthornGym_Text_GymStatue:
	.string "BLACKTHOR{SE_M_PSYBEAM2}CIT{SE_M_MOONLIGHT}POKéMO{SE_M_PSYBEAM2}GYM$"

BlackthornGym_Text_GymStatueCertified:
	.string "BLACKTHOR{SE_M_PSYBEAM2}CIT{SE_M_MOONLIGHT}POKéMO{SE_M_PSYBEAM2}GYM\p"
	.string "CLAIR'{SE_M_SKETCH}CERTIFIE{SE_M_FAINT_ATTACK}TRAINERS:\n"
	.string "{PLAYER}$"

