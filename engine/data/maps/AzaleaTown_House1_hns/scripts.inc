@ Johto (data/maps/AzaleaTown_House1_hns/scripts.inc), as built into the FireRed game.

AzaleaTown_House1_hns_MapScripts::
	.byte 0

AzaleaTown_House1_EventScript_Boss::
	lock
	faceplayer
	goto_if_eq JOHTO_VAR_AZALEA_TOWN_STATE, 5, AzaleaTown_House1_EventScript_Boss3
	goto_if_eq JOHTO_VAR_AZALEA_TOWN_STATE, 6, AzaleaTown_House1_EventScript_Boss3
	goto_if_eq JOHTO_VAR_AZALEA_TOWN_STATE, 7, AzaleaTown_House1_EventScript_Boss4
	goto_if_set JOHTO_FLAG_HIDE_AZALEA_TOWN_ROCKETS, AzaleaTown_House1_EventScript_Boss2
	msgbox CharcoalKiln_Text_Boss1, MSGBOX_DEFAULT
	closemessage
	release
	end

AzaleaTown_House1_EventScript_Boss2::
	msgbox CharcoalKiln_Text_Boss2, MSGBOX_DEFAULT
	closemessage
	release
	end

AzaleaTown_House1_EventScript_Boss3::
	msgbox CharcoalKiln_Text_Boss3, MSGBOX_DEFAULT
	closemessage
	release
	end

AzaleaTown_House1_EventScript_Boss4::
	msgbox CharcoalKiln_Text_Boss4, MSGBOX_DEFAULT
	closemessage
	release
	end

AzaleaTown_House1_EventScript_Apprentice::
	lock
	faceplayer
	goto_if_ge JOHTO_VAR_AZALEA_TOWN_STATE, 7, AzaleaTown_House1_EventScript_Apprentice3
	goto_if_set JOHTO_FLAG_HIDE_AZALEA_TOWN_ROCKETS, AzaleaTown_House1_EventScript_Apprentice2
	msgbox CharcoalKiln_Text_Apprentice1, MSGBOX_DEFAULT
	closemessage
	release
	end

AzaleaTown_House1_EventScript_Apprentice2::
	msgbox CharcoalKiln_Text_Apprentice2, MSGBOX_DEFAULT
	closemessage
	release
	end

AzaleaTown_House1_EventScript_Apprentice3::
	goto_if_set JOHTO_FLAG_GOT_CHARCOAL, AzaleaTown_House1_EventScript_Apprentice4
	msgbox CharcoalKiln_Text_Apprentice3, MSGBOX_DEFAULT
	giveitem ITEM_CHARCOAL
	setflag JOHTO_FLAG_GOT_CHARCOAL
	closemessage
	release
	end

AzaleaTown_House1_EventScript_Apprentice4::
	msgbox CharcoalKiln_Text_Apprentice4, MSGBOX_DEFAULT
	closemessage
	release
	end

AzaleaTown_House1_EventScript_Farfetchd::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_FARFETCHD, CRY_MODE_NORMAL
	msgbox CharcoalKiln_Text_Farfetchd, MSGBOX_DEFAULT
	waitmoncry
	release
	end

CharcoalKiln_Text_Boss1:
	.string "Al{SE_M_BATON_PASS}th{SE_M_REVERSAL}SLOWPOK{SE_M_SWORDS_DANCE}hav{SE_M_REVERSAL}disappeared\n"
	.string "fro{SE_M_MILK_DRINK}th{SE_M_REVERSAL}town.\p"
	.string "Th{SE_M_REVERSAL}forest'{SE_M_GRASSWHISTLE}protecto{SE_M_SAND_TOMB}ma{SE_M_YAWN}be\n"
	.string "angr{SE_M_YAWN}wit{SE_M_TRI_ATTACK}us…\p"
	.string "I{SE_M_SPIT_UP}ma{SE_M_YAWN}b{SE_M_REVERSAL}{SE_M_CHARGE}ba{SE_M_WATERFALL}omen{SE_M_PERISH_SONG}W{SE_M_REVERSAL}should\n"
	.string "sta{SE_M_YAWN}in.$"

CharcoalKiln_Text_Boss2:
	.string "Th{SE_M_REVERSAL}SLOWPOK{SE_M_SWORDS_DANCE}hav{SE_M_REVERSAL}returned…$"

CharcoalKiln_Text_Boss3:
	.string "Th{SE_M_REVERSAL}SLOWPOK{SE_M_SWORDS_DANCE}hav{SE_M_REVERSAL}returned…\p"
	.string "Bu{SE_M_SPIT_UP}m{SE_M_YAWN}APPRENTIC{SE_M_SWORDS_DANCE}hasn'{SE_M_SPIT_UP}com{SE_M_REVERSAL}back\n"
	.string "fro{SE_M_MILK_DRINK}ILE{SE_M_LOCK_ON}FOREST.\p"
	.string "Wher{SE_M_REVERSAL}i{SE_M_ATTRACT}th{SE_M_REVERSAL}worl{SE_M_WATERFALL}i{SE_M_GRASSWHISTLE}tha{SE_M_SPIT_UP}laz{SE_M_YAWN}guy?$"

CharcoalKiln_Text_Boss4:
	.string "Yo{SE_M_DIVE}chase{SE_M_WATERFALL}of{SE_M_ACID_ARMOR}TEA{SE_M_GIGA_DRAIN}ROCKE{SE_M_SWIFT}and\n"
	.string "wen{SE_M_SPIT_UP}t{SE_M_ATTRACT2}ILE{SE_M_LOCK_ON}FORES{SE_M_SWIFT}alone?\p"
	.string "Tha{SE_M_SPIT_UP}take{SE_M_GRASSWHISTLE}guts{SE_M_DRAGON_RAGE}{SE_M_HEAL_BELL}lik{SE_M_REVERSAL}that.\n"
	.string "Com{SE_M_REVERSAL}trai{SE_M_ATTRACT}wit{SE_M_TRI_ATTACK}us.$"

CharcoalKiln_Text_Apprentice1:
	.string "Wher{SE_M_REVERSAL}hav{SE_M_REVERSAL}al{SE_M_BATON_PASS}th{SE_M_REVERSAL}SLOWPOK{SE_M_SWORDS_DANCE}gone?\p"
	.string "Ar{SE_M_REVERSAL}the{SE_M_YAWN}ou{SE_M_SPIT_UP}playin{SE_M_SANDSTORM}somewhere?$"

CharcoalKiln_Text_Apprentice2:
	.string "Th{SE_M_REVERSAL}SLOWPOK{SE_M_SWORDS_DANCE}cam{SE_M_REVERSAL}back!$"

CharcoalKiln_Text_Apprentice3:
	.string "I'{SE_M_MILK_DRINK}sorry--{SE_M_HEAL_BELL}forgo{SE_M_SPIT_UP}t{SE_M_ATTRACT2}than{SE_M_ENCORE2}you.\p"
	.string "Thi{SE_M_GRASSWHISTLE}i{SE_M_GRASSWHISTLE}CHARCOA{SE_M_BRICK_BREAK}tha{SE_M_SPIT_UP}{SE_M_HEAL_BELL}made.\p"
	.string "FIRE-typ{SE_M_REVERSAL}POKéMO{SE_M_PSYBEAM2}woul{SE_M_WATERFALL}b{SE_M_REVERSAL}happy\n"
	.string "t{SE_M_ATTRACT2}hol{SE_M_WATERFALL}that.$"

CharcoalKiln_Text_Apprentice4:
	.string "Th{SE_M_REVERSAL}SLOWPOK{SE_M_SWORDS_DANCE}cam{SE_M_REVERSAL}back{SE_M_SUPERSONIC}an{SE_M_WATERFALL}yo{SE_M_DIVE}even\n"
	.string "foun{SE_M_WATERFALL}FARFETCH'D.\p"
	.string "You'r{SE_M_REVERSAL}th{SE_M_REVERSAL}coolest{SE_M_SUPERSONIC}man!$"

CharcoalKiln_Text_Farfetchd:
	.string "FARFETCH'D{SE_M_HEAT_WAVE}Kwaa!$"

