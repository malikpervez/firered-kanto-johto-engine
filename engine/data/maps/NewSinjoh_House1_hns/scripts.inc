@ Johto (data/maps/NewSinjoh_House1_hns/scripts.inc), as built into the FireRed game.

NewSinjoh_House1_hns_MapScripts::
	.byte 0

NewSinjoh__House1_EventScripts_Elizabeth::
	lock
	faceplayer
	goto_if_set JOHTO_FLAG_NEWSINJOH_HOUSE1_ELIZABETH_GAVEWOOPER, NewSinjoh_House1_EventScript_Elizabeth_AfterGift
	msgbox NewSinjoh_House1_Text_Looking4Celebi MSGBOX_YESNO
	goto_if_eq VAR_RESULT, FALSE, NewSinjoh_House1_EventScript_Decline
	checkspecies SPECIES_CELEBI
	goto_if_eq VAR_RESULT, TRUE, NewSinjoh_House1_EventScript_GiveWooperPaldea
	msgbox NewSinjoh_House1_Text_NicePokemonButNotCelebi, MSGBOX_DEFAULT
	release
	end

NewSinjoh_House1_EventScript_Decline::
	msgbox NewSinjoh_House1_Text_Decline, MSGBOX_DEFAULT
	closemessage
	release
	end

NewSinjoh_House1_EventScript_GiveWooperPaldea::
	playse SE_PIN
	applymovement LOCALID_NEWSINJOH_HOUSE1_ELIZABETH, J_Common_Movement_ExclamationMark
	delay 55
	waitmovement LOCALID_NEWSINJOH_HOUSE1_ELIZABETH
	msgbox NewSinjoh_House1_OffersWooper MSGBOX_DEFAULT
	setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_WOOPER_PALDEA
	bufferspeciesname STR_VAR_1, SPECIES_WOOPER_PALDEA
	givemon SPECIES_WOOPER_PALDEA, 5
	call J_Common_EventScript_GiftMon
	setflag JOHTO_FLAG_NEWSINJOH_HOUSE1_ELIZABETH_GAVEWOOPER
	closemessage
	release
	end

NewSinjoh_House1_Text_Looking4Celebi:
	.string "He{SE_M_YAWN}there{SE_M_SUPERSONIC}Trainer!\p"
	.string "Yo{SE_M_DIVE}cam{SE_M_REVERSAL}al{SE_M_BATON_PASS}th{SE_M_REVERSAL}wa{SE_M_YAWN}from\n"
	.string "NE{SE_M_DETECT}BAR{SE_M_SNORE}TOWN?\p"
	.string "{SE_M_HEAL_BELL}hav{SE_M_REVERSAL}{SE_M_CHARGE}reques{SE_M_SPIT_UP}fo{SE_M_SAND_TOMB}someon{SE_M_REVERSAL}as\n"
	.string "wel{SE_M_BATON_PASS}travele{SE_M_WATERFALL}a{SE_M_GRASSWHISTLE}yo{SE_M_DIVE}are.\l"
	.string "Yo{SE_M_DIVE}see{SE_M_SUPERSONIC}m{SE_M_YAWN}favorit{SE_M_REVERSAL}POKEMO{SE_M_PSYBEAM2}i{SE_M_ATTRACT}the\l"
	.string "whol{SE_M_REVERSAL}worl{SE_M_WATERFALL}jus{SE_M_SPIT_UP}s{SE_M_ATTRACT2}happen{SE_M_GRASSWHISTLE}t{SE_M_ATTRACT2}be\l"
	.string "th{SE_M_REVERSAL}mythica{SE_M_BATON_PASS}POKEMO{SE_M_PSYBEAM2}know{SE_M_ATTRACT}a{SE_M_GRASSWHISTLE}CELEBI.\p"
	.string "I{SE_M_ACID_ARMOR}yo{SE_M_DIVE}happe{SE_M_ATTRACT}t{SE_M_ATTRACT2}hav{SE_M_REVERSAL}one{SE_M_SUPERSONIC}would\n"
	.string "yo{SE_M_DIVE}min{SE_M_WATERFALL}showin{SE_M_SANDSTORM}i{SE_M_SPIT_UP}t{SE_M_ATTRACT2}me?$"

NewSinjoh_House1_Text_NicePokemonButNotCelebi:
	.string "That'{SE_M_GRASSWHISTLE}{SE_M_CHARGE}ver{SE_M_YAWN}wonderfu{SE_M_BATON_PASS}POKEMON\n"
	.string "yo{SE_M_DIVE}hav{SE_M_REVERSAL}ther{SE_M_REVERSAL}bu{SE_M_SPIT_UP}that's\l"
	.string "no{SE_M_SPIT_UP}exactl{SE_M_YAWN}wha{SE_M_SPIT_UP}{SE_M_HEAL_BELL}wa{SE_M_GRASSWHISTLE}lookin{SE_M_SANDSTORM}for..$"

NewSinjoh_House1_OffersWooper:
	.string "That'{SE_M_GRASSWHISTLE}it{SE_M_DRAGON_RAGE}That'{SE_M_GRASSWHISTLE}{SE_M_CHARGE}rea{SE_M_BATON_PASS}livin{SE_M_SANDSTORM}CELEBI!!\p"
	.string "Than{SE_M_ENCORE2}yo{SE_M_DIVE}sho{SE_M_TWISTER}muc{SE_M_TRI_ATTACK}fo{SE_M_SAND_TOMB}bringin{SE_M_SANDSTORM}it\n"
	.string "al{SE_M_BATON_PASS}th{SE_M_REVERSAL}wa{SE_M_YAWN}u{SE_M_MORNING_SUN}nort{SE_M_TRI_ATTACK}fo{SE_M_SAND_TOMB}m{SE_M_REVERSAL}t{SE_M_ATTRACT2}see.\p"
	.string "Here{SE_M_SUPERSONIC}m{SE_M_YAWN}girlfrien{SE_M_WATERFALL}happene{SE_M_WATERFALL}to\n"
	.string "catc{SE_M_TRI_ATTACK}{SE_M_CHARGE}fe{SE_M_TWISTER}to{SE_M_ATTRACT2}man{SE_M_YAWN}o{SE_M_ACID_ARMOR}thes{SE_M_REVERSAL}during\l"
	.string "he{SE_M_SAND_TOMB}tri{SE_M_MORNING_SUN}t{SE_M_ATTRACT2}{SE_M_CHARGE}fa{SE_M_SAND_TOMB}awa{SE_M_YAWN}region..\p"
	.string "Pleas{SE_M_REVERSAL}tak{SE_M_REVERSAL}thi{SE_M_GRASSWHISTLE}specia{SE_M_BATON_PASS}WOOPE{SE_M_MINIMIZE}as\n"
	.string "thanks{SE_M_SUPERSONIC}{PLAYER}.$"

NewSinjoh_House1_Text_Decline:
	.string "That'{SE_M_GRASSWHISTLE}to{SE_M_ATTRACT2}bad{SE_M_PERISH_SONG}{SE_M_HEAL_BELL}reall{SE_M_YAWN}wanted\n"
	.string "t{SE_M_ATTRACT2}se{SE_M_REVERSAL}one.$"

NewSinjoh_House1_Text_TakeCareOfWooper:
	.string "Tak{SE_M_REVERSAL}goo{SE_M_WATERFALL}car{SE_M_REVERSAL}o{SE_M_ACID_ARMOR}tha{SE_M_SPIT_UP}WOOPER\n"
	.string "fo{SE_M_SAND_TOMB}m{SE_M_REVERSAL}okay?$"

NewSinjoh_House1_EventScript_Elizabeth_AfterGift::
	msgbox NewSinjoh_House1_Text_GoodToSeeYouAgain MSGBOX_DEFAULT
	release
	end

NewSinjoh_House1_Text_GoodToSeeYouAgain:
	.string "It'{SE_M_GRASSWHISTLE}goo{SE_M_WATERFALL}t{SE_M_ATTRACT2}se{SE_M_REVERSAL}yo{SE_M_DIVE}again,\n"
	.string "{PLAYER}.\p"
	.string "Ho{SE_M_TWISTER}hav{SE_M_REVERSAL}yo{SE_M_DIVE}bee{SE_M_ATTRACT}treatin{SE_M_SANDSTORM}that\n"
	.string "tha{SE_M_SPIT_UP}WOOPER?$"

NewSinjoh_House1_Bookshelf::
	lock
	msgbox NewSinjoh_House1_Bookshelf_Text MSGBOX_DEFAULT
	release
	end

NewSinjoh_House1_Bookshelf_Text:
	.string "It'{SE_M_GRASSWHISTLE}{SE_M_CHARGE}shel{SE_M_ACID_ARMOR}packe{SE_M_WATERFALL}ful{SE_M_BATON_PASS}of\n"
	.string "compute{SE_M_SAND_TOMB}game{SE_M_GRASSWHISTLE}an{SE_M_WATERFALL}graphi{SE_M_HYPER_BEAM}novels!$"

NewSinjoh_House1_Eevee::
	lock
	faceplayer
	playmoncry SPECIES_EEVEE, 0
	msgbox NewSinjoh_House1_Text_Eevee_Cry, MSGBOX_DEFAULT
	waitmoncry
	closemessage
	release
	end

NewSinjoh_House1_Text_Eevee_Cry:
	.string "Ve{SE_M_REVERSAL}Vee?$"

