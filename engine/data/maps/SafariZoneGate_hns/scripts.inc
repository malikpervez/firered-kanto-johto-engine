@ Johto (data/maps/SafariZoneGate_hns/scripts.inc), as built into the FireRed game.

SafariZoneGate_hns_MapScripts::
	.byte 0

SafariZoneGate_EventScript_Trigger::
	setflag JOHTO_FLAG_VISITED_SAFARI_ZONE_GATE
	setvar JOHTO_VAR_SAFARI_ZONE_GATE_STATE, 3
	end

SafariZoneGate_EventScript_BackupTrigger::
	setflag JOHTO_FLAG_VISITED_SAFARI_ZONE_GATE
	setvar VAR_TEMP_0, 1
	end

SafariZoneGate_EventScript_WorkerM::
	lock
	faceplayer
	msgbox SafariZone_Text_ForeignFeeling, MSGBOX_DEFAULT
	closemessage
	release
	end

SafariZoneGate_EventScript_Silent::
	lock
	faceplayer
	msgbox SafariZone_Text_SilentNPC, MSGBOX_DEFAULT
	closemessage
	release
	end

SafariZoneGate_EventScript_Kangaskhan::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_KANGASKHAN, CRY_MODE_NORMAL
	msgbox SafariZone_Text_Kangaskhan, MSGBOX_DEFAULT
	waitmoncry
	release
	end

SafariZoneGate_EventScript_Engineer::
	lock
	faceplayer
	msgbox SafariZone_Text_JigglypuffTrainer, MSGBOX_DEFAULT
	closemessage
	release
	end

SafariZoneGate_EventScript_Girl::
	lock
	faceplayer
	msgbox SafariZone_Text_FirstCatch, MSGBOX_DEFAULT
	closemessage
	release
	end

SafariZoneGate_EventScript_SlowpokeLady::
	lock
	faceplayer
	msgbox SafariZone_Text_SlowpokeFan, MSGBOX_DEFAULT
	closemessage
	release
	end

SafariZone_Text_ForeignFeeling:
	.string "SAFAR{SE_M_HEAL_BELL}ZONE...\n"
	.string "I{SE_M_SPIT_UP}make{SE_M_GRASSWHISTLE}m{SE_M_REVERSAL}fee{SE_M_BATON_PASS}lik{SE_M_REVERSAL}{SE_M_HEAL_BELL}a{SE_M_MILK_DRINK}i{SE_M_ATTRACT}a\l"
	.string "foreig{SE_M_ATTRACT}country.\p"
	.string "I{SE_M_SPIT_UP}bring{SE_M_GRASSWHISTLE}u{SE_M_MORNING_SUN}{SE_M_CHARGE}strang{SE_M_REVERSAL}feeling.$"

SafariZone_Text_SilentNPC:
	.string "..................\p"
	.string "({SE_M_HEAL_BELL}a{SE_M_MILK_DRINK}no{SE_M_SPIT_UP}{SE_M_CHARGE}talker.)$"

SafariZone_Text_Kangaskhan:
	.string "KANGASKHAN{SE_M_HEAT_WAVE}..................$"

SafariZone_Text_JigglypuffTrainer:
	.string "Thi{SE_M_GRASSWHISTLE}SAFAR{SE_M_HEAL_BELL}ZON{SE_M_SWORDS_DANCE}i{SE_M_GRASSWHISTLE}great!\n"
	.string "{SE_M_HEAL_BELL}jus{SE_M_SPIT_UP}kep{SE_M_SPIT_UP}goin{SE_M_SANDSTORM}afte{SE_M_SAND_TOMB}POKéMON!\p"
	.string "Tha{SE_M_SPIT_UP}mad{SE_M_REVERSAL}m{SE_M_YAWN}JIGGLYPUF{SE_M_LEER}upse{SE_M_SPIT_UP}though.$"

SafariZone_Text_FirstCatch:
	.string "{SE_M_HEAL_BELL}hav{SE_M_REVERSAL}alway{SE_M_GRASSWHISTLE}wante{SE_M_WATERFALL}t{SE_M_ATTRACT2}catc{SE_M_TRI_ATTACK}m{SE_M_YAWN}first\n"
	.string "POKéMO{SE_M_PSYBEAM2}a{SE_M_SPIT_UP}th{SE_M_REVERSAL}SAFAR{SE_M_HEAL_BELL}ZONE.$"

SafariZone_Text_SlowpokeFan:
	.string "Ther{SE_M_REVERSAL}ar{SE_M_REVERSAL}man{SE_M_YAWN}POKéMO{SE_M_PSYBEAM2}t{SE_M_ATTRACT2}choos{SE_M_REVERSAL}from,\n"
	.string "bu{SE_M_SPIT_UP}nothin{SE_M_SANDSTORM}beat{SE_M_GRASSWHISTLE}th{SE_M_REVERSAL}cutenes{SE_M_GRASSWHISTLE}of\l"
	.string "SLOWPOKE.\p"
	.string "Peopl{SE_M_REVERSAL}ofte{SE_M_ATTRACT}sa{SE_M_YAWN}tha{SE_M_SPIT_UP}{SE_M_HEAL_BELL}loo{SE_M_ENCORE2}lik{SE_M_REVERSAL}one!$"

SafariZone_Text_CustomSystem:
	.string "Yo{SE_M_DIVE}ma{SE_M_YAWN}b{SE_M_REVERSAL}unde{SE_M_SAND_TOMB}th{SE_M_REVERSAL}impressio{SE_M_ATTRACT}there\n"
	.string "i{SE_M_GRASSWHISTLE}{SE_M_CHARGE}sophisticate{SE_M_WATERFALL}syste{SE_M_MILK_DRINK}to\l"
	.string "customizin{SE_M_SANDSTORM}th{SE_M_REVERSAL}SAFAR{SE_M_HEAL_BELL}ZONE{SE_M_SUPERSONIC}right?\p"
	.string "Th{SE_M_REVERSAL}rea{SE_M_BATON_PASS}trut{SE_M_TRI_ATTACK}i{SE_M_GRASSWHISTLE}that...$"

SafariZone_Text_Sign:
	.string "SAFAR{SE_M_HEAL_BELL}ZONE\n"
	.string "Thi{SE_M_GRASSWHISTLE}i{SE_M_GRASSWHISTLE}wher{SE_M_REVERSAL}everythin{SE_M_SANDSTORM}i{SE_M_GRASSWHISTLE}thrilling.\p"
	.string "Fee{SE_M_BATON_PASS}fre{SE_M_REVERSAL}t{SE_M_ATTRACT2}com{SE_M_REVERSAL}b{SE_M_YAWN}an{SE_M_WATERFALL}experience\n"
	.string "th{SE_M_REVERSAL}wild!$"

SafariZoneGate_EventScript_IncenseClerk::
	goto_if_set JOHTO_FLAG_FINITE_TMS, SafariZoneGate_EventScript_IncenseClerkFinite
	lock
	faceplayer
	message J_gText_HowMayIServeYou
	waitmessage
	pokemart SafariZoneGate_Pokemart_Incenses
	msgbox J_gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2

SafariZoneGate_Pokemart_Incenses:
	.2byte ITEM_SEA_INCENSE
	.2byte ITEM_LAX_INCENSE
	.2byte ITEM_NONE
	release
	end

SafariZoneGate_EventScript_IncenseClerkFinite::
	lock
	faceplayer
	message J_gText_HowMayIServeYou
	waitmessage
	pokemart SafariZoneGate_Pokemart_Incenses2
	msgbox J_gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2

SafariZoneGate_Pokemart_Incenses2:
	.2byte 591
	.2byte 624
	.2byte ITEM_SEA_INCENSE
	.2byte ITEM_LAX_INCENSE
	.2byte ITEM_NONE
	release
	end

SafariZoneGate_EventScript_VitaminGuru::
	lock
	faceplayer
	message SafariZoneGate_Text_VitaminGuruSellWhatYouNeed
	waitmessage
	pokemart SafariZoneGate_Pokemart_VitaminGuru
	msgbox J_gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2

SafariZoneGate_Pokemart_VitaminGuru:
	.2byte ITEM_PROTEIN
	.2byte ITEM_IRON
	.2byte ITEM_CARBOS
	.2byte ITEM_ZINC
	.2byte ITEM_CALCIUM
	.2byte ITEM_HP_UP
	.2byte ITEM_NONE
	release
	end

SafariZoneGate_Text_VitaminGuruSellWhatYouNeed:
	.string "I'{SE_M_MILK_DRINK}th{SE_M_REVERSAL}ENERG{SE_M_MOONLIGHT}GURU{SE_M_DRAGON_RAGE}I'l{SE_M_BATON_PASS}g{SE_M_ATTRACT2}fo{SE_M_SAND_TOMB}i{SE_M_SPIT_UP}and\n"
	.string "sel{SE_M_BATON_PASS}yo{SE_M_DIVE}wha{SE_M_SPIT_UP}yo{SE_M_DIVE}need!$"

