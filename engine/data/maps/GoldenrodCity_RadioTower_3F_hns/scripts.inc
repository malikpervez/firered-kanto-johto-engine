@ Johto (data/maps/GoldenrodCity_RadioTower_3F_hns/scripts.inc), as built into the FireRed game.

GoldenrodCity_RadioTower_3F_hns_MapScripts::
	map_script 1, GoldenrodCity_RadioTower_3F_OnLoad
	.byte 0

GoldenrodCity_RadioTower_3F_OnLoad::
	call_if_set 8305, GoldenrodCity_RadioTower_3F_HideGate
	end

GoldenrodCity_RadioTower_3F_HideGate::
	setmetatile 25, 8, 0x335, FALSE
	setmetatile 25, 9, 0x335, FALSE

	setmetatile 26, 8, 0X334, FALSE
	setmetatile 26, 9, 0X334, FALSE

	setmetatile 27, 8, 0X334, FALSE
	setmetatile 27, 9, 0X334, FALSE

	setmetatile 28, 8, 0X334, FALSE
	setmetatile 28, 9, 0X334, FALSE

	setmetatile 29, 8, 0X334, FALSE
	setmetatile 29, 9, 0X334, FALSE

	setmetatile 30, 8, 0X334, FALSE
	setmetatile 30, 9, 0X334, FALSE

	setmetatile 31, 8, 0X334, FALSE
	setmetatile 31, 9, 0X334, FALSE
	return

GoldenrodRaidoTower3_EventScript_Grunt6::
	trainerbattle_single 1148, GoldenrodCity_RadioTower_3F_Text_GruntM7Seen, GoldenrodCity_RadioTower_3F_Text_GruntM7Beaten
	msgbox GoldenrodCity_RadioTower_3F_Text_GruntM7After, MSGBOX_AUTOCLOSE
	end

GoldenrodRaidoTower3_EventScript_Grunt7::
	trainerbattle_single 1149, GoldenrodCity_RadioTower_3F_Text_GruntM8Seen, GoldenrodCity_RadioTower_3F_Text_GruntM8Beaten
	msgbox GoldenrodCity_RadioTower_3F_Text_GruntM8After, MSGBOX_AUTOCLOSE
	end

GoldenrodRaidoTower3_EventScript_Grunt8::
	trainerbattle_single 1150, GoldenrodCity_RadioTower_3F_Text_GruntM9Seen, GoldenrodCity_RadioTower_3F_Text_GruntM9Beaten
	msgbox GoldenrodCity_RadioTower_3F_Text_GruntM9After, MSGBOX_AUTOCLOSE
	end

GoldenrodRaidoTower3_EventScript_Scientist::
	trainerbattle_single 1029, GoldenrodCity_RadioTower_3F_Text_ScientistMarcSeen, GoldenrodCity_RadioTower_3F_Text_ScientistMarcBeaten
	msgbox GoldenrodCity_RadioTower_3F_Text_ScientistMarcAfter, MSGBOX_AUTOCLOSE
	end

GoldenrodCity_RadioTower_3F_EventScript_Cooltrainer::
	lock
	faceplayer
	goto_if_set 8713, GoldenrodCity_RadioTower_3F_EventScript_Cooltrainer3
	goto_if_ge 20569, 10, GoldenrodCity_RadioTower_3F_EventScript_Cooltrainer2

	msgbox GoldenrodCity_RadioTower_3F_Text_CooltrainerFPleaseSave, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_RadioTower_3F_EventScript_Cooltrainer2::
	lock
	faceplayer
	msgbox GoldenrodCity_RadioTower_3F_Text_CooltrainerFHeroGift, MSGBOX_DEFAULT
	closemessage
	giveitem 592
	setflag 8713
	msgbox GoldenrodCity_RadioTower_3F_Text_CooltrainerFSunnyDay, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_RadioTower_3F_EventScript_Cooltrainer3::
	msgbox GoldenrodCity_RadioTower_3F_Text_CooltrainerFMarvelous, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_RadioTower_3F_EventScript_Nerd::
	lock
	faceplayer
	msgbox GoldenrodCity_RadioTower_3F_Text_SuperNerd, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_RadioTower_3F_EventScript_Gate::
	lock
	msgbox GoldenrodCity_RadioTower_3F_Text_CardKeySlot, MSGBOX_SIGN
	goto_if_set 8305, GoldenrodCity_RadioTower_3F_EventScript_GateOpened
	checkitem ITEM_CARD_KEY
	goto_if_eq 32781, TRUE, GoldenrodCity_RadioTower_3F_EventScript_OpenGate
	closemessage
	release
	end

GoldenrodCity_RadioTower_3F_EventScript_GateOpened::
	msgbox GoldenrodCity_RadioTower_3F_Text_Open, MSGBOX_SIGN
	closemessage
	release
	end

GoldenrodCity_RadioTower_3F_EventScript_OpenGate::
	msgbox GoldenrodCity_RadioTower_3F_Text_InsertedCardKey, MSGBOX_SIGN
	call GoldenrodCity_RadioTower_3F_HideGate
	playse 36
	special DrawWholeMapView
	msgbox GoldenrodCity_RadioTower_3F_Text_Open, MSGBOX_SIGN
	setflag 8305
	closemessage
	release
	end

GoldenrodCity_RadioTower_3F_EventScript_Sign1::
	lock
	msgbox GoldenrodCity_RadioTower_3F_Text_PersonnelSign, MSGBOX_SIGN
	closemessage
	release
	end

GoldenrodCity_RadioTower_3F_EventScript_Sign2::
	lock
	msgbox GoldenrodCity_RadioTower_3F_Text_PokemonMusicSign, MSGBOX_SIGN
	closemessage
	release
	end

GoldenrodCity_RadioTower_3F_Text_CardKeySlot:
	.string "It'{SE_M_GRASSWHISTLE}th{SE_M_REVERSAL}CAR{SE_M_FAINT_ATTACK}KE{SE_M_MOONLIGHT}slot.$"

GoldenrodCity_RadioTower_3F_Text_InsertedCardKey:
	.string "{PLAYER} inserte{SE_M_WATERFALL}th{SE_M_REVERSAL}CAR{SE_M_FAINT_ATTACK}KEY.$"

GoldenrodCity_RadioTower_3F_Text_Open:
	.string "Th{SE_M_REVERSAL}gat{SE_M_REVERSAL}i{SE_M_GRASSWHISTLE}open.$"

GoldenrodCity_RadioTower_3F_Text_PersonnelSign:
	.string "3{SE_M_LEER}PERSONNEL$"

GoldenrodCity_RadioTower_3F_Text_PokemonMusicSign:
	.string "POKéMO{SE_M_PSYBEAM2}MUSI{SE_M_PSYBEAM}wit{SE_M_TRI_ATTACK}Hos{SE_M_SPIT_UP}D{SE_M_CONFUSE_RAY}BEN$"

GoldenrodCity_RadioTower_3F_Text_SuperNerd:
	.string "W{SE_M_REVERSAL}hav{SE_M_REVERSAL}recording{SE_M_GRASSWHISTLE}o{SE_M_ACID_ARMOR}th{SE_M_REVERSAL}cries\n"
	.string "o{SE_M_ACID_ARMOR}al{SE_M_BATON_PASS}POKéMO{SE_M_PSYBEAM2}tha{SE_M_SPIT_UP}hav{SE_M_REVERSAL}been\l"
	.string "found.\p"
	.string "W{SE_M_REVERSAL}mus{SE_M_SPIT_UP}hav{SE_M_REVERSAL}abou{SE_M_SPIT_UP}40{SE_M_BITE}kinds.$"

GoldenrodCity_RadioTower_3F_Text_GymGuideRockets:
	.string "T{SE_M_ATTRACT2}trainers{SE_M_SUPERSONIC}POKéMO{SE_M_PSYBEAM2}ar{SE_M_REVERSAL}their\n"
	.string "belove{SE_M_WATERFALL}partners.\p"
	.string "It'{SE_M_GRASSWHISTLE}terribl{SE_M_REVERSAL}ho{SE_M_TWISTER}TEA{SE_M_GIGA_DRAIN}ROCKE{SE_M_SWIFT}is\n"
	.string "tryin{SE_M_SANDSTORM}t{SE_M_ATTRACT2}contro{SE_M_BATON_PASS}POKéMON.$"

GoldenrodCity_RadioTower_3F_Text_GymGuide:
	.string "W{SE_M_REVERSAL}ru{SE_M_ATTRACT}2{SE_M_WHIRLPOOL}hour{SE_M_GRASSWHISTLE}{SE_M_CHARGE}da{SE_M_YAWN}t{SE_M_ATTRACT2}broadcast\n"
	.string "entertainin{SE_M_SANDSTORM}programs.\p"
	.string "I'l{SE_M_BATON_PASS}d{SE_M_ATTRACT2}m{SE_M_YAWN}bes{SE_M_SPIT_UP}t{SE_M_ATTRACT2}ru{SE_M_ATTRACT}aroun{SE_M_WATERFALL}the\n"
	.string "cloc{SE_M_ENCORE2}too!$"

GoldenrodCity_RadioTower_3F_Text_CooltrainerFPleaseSave:
	.string "Th{SE_M_REVERSAL}TEA{SE_M_GIGA_DRAIN}ROCKE{SE_M_SWIFT}bos{SE_M_GRASSWHISTLE}ha{SE_M_GRASSWHISTLE}locked\n"
	.string "himsel{SE_M_ACID_ARMOR}in.\p"
	.string "Bu{SE_M_SPIT_UP}th{SE_M_REVERSAL}DIRECTO{SE_M_MINIMIZE}ca{SE_M_ATTRACT}ope{SE_M_ATTRACT}it.\p"
	.string "He'{SE_M_GRASSWHISTLE}u{SE_M_MORNING_SUN}o{SE_M_ATTRACT}th{SE_M_REVERSAL}fift{SE_M_TRI_ATTACK}floor.\p"
	.string "Pleas{SE_M_REVERSAL}sav{SE_M_REVERSAL}him!$"

GoldenrodCity_RadioTower_3F_Text_CooltrainerFDirectorSafe:
	.string "I{SE_M_GRASSWHISTLE}th{SE_M_REVERSAL}DIRECTO{SE_M_MINIMIZE}safe?$"

GoldenrodCity_RadioTower_3F_Text_CooltrainerFHeroGift:
	.string "Than{SE_M_ENCORE2}you{SE_M_DRAGON_RAGE}You'r{SE_M_REVERSAL}m{SE_M_YAWN}hero!\p"
	.string "Thi{SE_M_GRASSWHISTLE}i{SE_M_GRASSWHISTLE}{SE_M_CHARGE}toke{SE_M_ATTRACT}o{SE_M_ACID_ARMOR}m{SE_M_YAWN}appreciation.$"

GoldenrodCity_RadioTower_3F_Text_CooltrainerFSunnyDay:
	.string "It'{SE_M_GRASSWHISTLE}SUNN{SE_M_MOONLIGHT}DAY.\p"
	.string "I{SE_M_SPIT_UP}power{SE_M_GRASSWHISTLE}u{SE_M_MORNING_SUN}fire-typ{SE_M_REVERSAL}moves\n"
	.string "fo{SE_M_SAND_TOMB}{SE_M_CHARGE}while.$"

GoldenrodCity_RadioTower_3F_Text_CooltrainerFMarvelous:
	.string "Yo{SE_M_DIVE}wer{SE_M_REVERSAL}simpl{SE_M_YAWN}marvelous!$"

GoldenrodCity_RadioTower_3F_Text_GruntM7Seen:
	.string "I'v{SE_M_REVERSAL}bee{SE_M_ATTRACT}give{SE_M_ATTRACT}stric{SE_M_SPIT_UP}orders.\p"
	.string "I'{SE_M_MILK_DRINK}t{SE_M_ATTRACT2}crus{SE_M_TRI_ATTACK}anyon{SE_M_REVERSAL}wh{SE_M_ATTRACT2}challenges\n"
	.string "TEA{SE_M_GIGA_DRAIN}ROCKET!$"

GoldenrodCity_RadioTower_3F_Text_GruntM7Beaten:
	.string "What?!$"

GoldenrodCity_RadioTower_3F_Text_GruntM7After:
	.string "{SE_M_HEAL_BELL}faile{SE_M_WATERFALL}i{SE_M_ATTRACT}m{SE_M_YAWN}duties…\p"
	.string "ARCHE{SE_M_MINIMIZE}wil{SE_M_BATON_PASS}b{SE_M_REVERSAL}s{SE_M_ATTRACT2}upset...$"

GoldenrodCity_RadioTower_3F_Text_GruntM8Seen:
	.string "I{SE_M_SPIT_UP}feel{SE_M_GRASSWHISTLE}grea{SE_M_SPIT_UP}orderin{SE_M_SANDSTORM}POKéMON\n"
	.string "t{SE_M_ATTRACT2}commi{SE_M_SPIT_UP}crimes.$"

GoldenrodCity_RadioTower_3F_Text_GruntM8Beaten:
	.string "You'r{SE_M_REVERSAL}kidding!$"

GoldenrodCity_RadioTower_3F_Text_GruntM8After:
	.string "{SE_M_HEAL_BELL}fee{SE_M_BATON_PASS}lous{SE_M_YAWN}ove{SE_M_SAND_TOMB}losing!\p"
	.string "Dar{SE_M_ATTRACT}it{SE_M_DRAGON_RAGE}{SE_M_HEAL_BELL}hat{SE_M_REVERSAL}useles{SE_M_GRASSWHISTLE}POKéMON!$"

GoldenrodCity_RadioTower_3F_Text_GruntM9Seen:
	.string "Wh{SE_M_YAWN}di{SE_M_WATERFALL}th{SE_M_REVERSAL}shutte{SE_M_SAND_TOMB}open{SE_M_SING}Di{SE_M_WATERFALL}you\n"
	.string "hav{SE_M_REVERSAL}somethin{SE_M_SANDSTORM}t{SE_M_ATTRACT2}d{SE_M_ATTRACT2}wit{SE_M_TRI_ATTACK}this?$"

GoldenrodCity_RadioTower_3F_Text_GruntM9Beaten:
	.string "I'{SE_M_MILK_DRINK}don{SE_M_REVERSAL}for!$"

GoldenrodCity_RadioTower_3F_Text_GruntM9After:
	.string "What?{SE_M_DRAGON_RAGE}Yo{SE_M_DIVE}mad{SE_M_REVERSAL}i{SE_M_SPIT_UP}pas{SE_M_SPIT_UP}ou{SE_M_SAND_TOMB}me{SE_M_ATTRACT}in\n"
	.string "th{SE_M_REVERSAL}UNDERGROUND?\p"
	.string "Ho{SE_M_TWISTER}coul{SE_M_WATERFALL}you?$"

GoldenrodCity_RadioTower_3F_Text_ScientistMarcSeen:
	.string "A{SE_M_ATTRACT}unknow{SE_M_ATTRACT}chil{SE_M_WATERFALL}wanderin{SE_M_SANDSTORM}here?\p"
	.string "Wh{SE_M_ATTRACT2}ar{SE_M_REVERSAL}you?$"

GoldenrodCity_RadioTower_3F_Text_ScientistMarcBeaten:
	.string "Tch{SE_M_DRAGON_RAGE}{SE_M_HEAL_BELL}too{SE_M_ENCORE2}yo{SE_M_DIVE}to{SE_M_ATTRACT2}lightly!$"

GoldenrodCity_RadioTower_3F_Text_ScientistMarcAfter:
	.string "Bwahahaha…\p"
	.string "{SE_M_HEAL_BELL}ca{SE_M_ATTRACT}transmi{SE_M_SPIT_UP}a{SE_M_GRASSWHISTLE}stron{SE_M_SANDSTORM}{SE_M_CHARGE}signal\n"
	.string "a{SE_M_GRASSWHISTLE}{SE_M_HEAL_BELL}nee{SE_M_WATERFALL}fro{SE_M_MILK_DRINK}here.$"

